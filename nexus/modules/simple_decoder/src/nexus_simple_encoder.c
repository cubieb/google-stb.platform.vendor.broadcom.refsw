/******************************************************************************
 *  Broadcom Proprietary and Confidential. (c)2016 Broadcom. All rights reserved.
 *
 *  This program is the proprietary software of Broadcom and/or its licensors,
 *  and may only be used, duplicated, modified or distributed pursuant to the terms and
 *  conditions of a separate, written license agreement executed between you and Broadcom
 *  (an "Authorized License").  Except as set forth in an Authorized License, Broadcom grants
 *  no license (express or implied), right to use, or waiver of any kind with respect to the
 *  Software, and Broadcom expressly reserves all rights in and to the Software and all
 *  intellectual property rights therein.  IF YOU HAVE NO AUTHORIZED LICENSE, THEN YOU
 *  HAVE NO RIGHT TO USE THIS SOFTWARE IN ANY WAY, AND SHOULD IMMEDIATELY
 *  NOTIFY BROADCOM AND DISCONTINUE ALL USE OF THE SOFTWARE.
 *
 *  Except as expressly set forth in the Authorized License,
 *
 *  1.     This program, including its structure, sequence and organization, constitutes the valuable trade
 *  secrets of Broadcom, and you shall use all reasonable efforts to protect the confidentiality thereof,
 *  and to use this information only in connection with your use of Broadcom integrated circuit products.
 *
 *  2.     TO THE MAXIMUM EXTENT PERMITTED BY LAW, THE SOFTWARE IS PROVIDED "AS IS"
 *  AND WITH ALL FAULTS AND BROADCOM MAKES NO PROMISES, REPRESENTATIONS OR
 *  WARRANTIES, EITHER EXPRESS, IMPLIED, STATUTORY, OR OTHERWISE, WITH RESPECT TO
 *  THE SOFTWARE.  BROADCOM SPECIFICALLY DISCLAIMS ANY AND ALL IMPLIED WARRANTIES
 *  OF TITLE, MERCHANTABILITY, NONINFRINGEMENT, FITNESS FOR A PARTICULAR PURPOSE,
 *  LACK OF VIRUSES, ACCURACY OR COMPLETENESS, QUIET ENJOYMENT, QUIET POSSESSION
 *  OR CORRESPONDENCE TO DESCRIPTION. YOU ASSUME THE ENTIRE RISK ARISING OUT OF
 *  USE OR PERFORMANCE OF THE SOFTWARE.
 *
 *  3.     TO THE MAXIMUM EXTENT PERMITTED BY LAW, IN NO EVENT SHALL BROADCOM OR ITS
 *  LICENSORS BE LIABLE FOR (i) CONSEQUENTIAL, INCIDENTAL, SPECIAL, INDIRECT, OR
 *  EXEMPLARY DAMAGES WHATSOEVER ARISING OUT OF OR IN ANY WAY RELATING TO YOUR
 *  USE OF OR INABILITY TO USE THE SOFTWARE EVEN IF BROADCOM HAS BEEN ADVISED OF
 *  THE POSSIBILITY OF SUCH DAMAGES; OR (ii) ANY AMOUNT IN EXCESS OF THE AMOUNT
 *  ACTUALLY PAID FOR THE SOFTWARE ITSELF OR U.S. $1, WHICHEVER IS GREATER. THESE
 *  LIMITATIONS SHALL APPLY NOTWITHSTANDING ANY FAILURE OF ESSENTIAL PURPOSE OF
 *  ANY LIMITED REMEDY.
 ******************************************************************************/
#include "nexus_simple_decoder_module.h"
#include "nexus_video_window.h"
#include "nexus_video_decoder.h"
#include "nexus_simple_audio_priv.h"
#include "nexus_simple_decoder_impl.h"
#include "nexus_client_resources.h"
#include "nexus_message.h"
#include "priv/nexus_core.h"
#include "priv/nexus_transport_priv.h"
#include "priv/nexus_pid_channel_priv.h"
#if NEXUS_HAS_STREAM_MUX
#include "priv/nexus_video_encoder_priv.h"
#endif
#ifdef NEXUS_NUM_DSP_VIDEO_ENCODERS
#include "nexus_video_adj.h"
#endif
#include "tshdrbuilder.h"

BDBG_MODULE(nexus_simple_encoder);

#define BDBG_MSG_TRACE(X)

struct NEXUS_SimpleEncoder
{
    NEXUS_OBJECT(NEXUS_SimpleEncoder);
    BLST_S_ENTRY(NEXUS_SimpleEncoder) link;
    unsigned index;
    bool acquired;
    bool clientStarted; /* user has called Start. if false, all other started variants must be false. */
    bool started; /* stream mux started */
    bool audioStarted, videoStarted;
    bool inputStarted; /* if true and 'started' is false, then only audio mux and mixer are started.
                          if true and 'started' is true, then audio, video and mux are started.
                          if false, then 'started' must be false. */
    NEXUS_SimpleEncoderServerSettings serverSettings;
    NEXUS_SimpleEncoderStartSettings startSettings;
    NEXUS_SimpleEncoderSettings settings;
    NEXUS_TaskCallbackHandle resourceChangedCallback;
    NEXUS_VideoWindowHandle transcodeWindow;
    struct {
        NEXUS_MemoryBlockHandle block;
        void *buffer;
        NEXUS_TimerHandle timer;
        unsigned ccValue;
    } psi;
    struct {
        bool video, audio;
    } wait;

    /* move structs off stack */
#if NEXUS_HAS_STREAM_MUX
    struct {
        NEXUS_VideoEncoderDelayRange videoDelay;
        NEXUS_VideoEncoderStartSettings videoEncoderStartSettings;
        NEXUS_AudioMuxOutputStartSettings audioMuxStartSettings;
        NEXUS_AudioMuxOutputDelayStatus audioDelayStatus;
    } stack;
#endif
    NEXUS_MessageHandle message[NEXUS_SIMPLE_ENCODER_NUM_PASSTHROUGH_PIDS];
};

static BLST_S_HEAD(NEXUS_SimpleEncoder_P_List, NEXUS_SimpleEncoder) g_encoders;

static NEXUS_Error nexus_simpleencoder_p_start( NEXUS_SimpleEncoderHandle handle );
#if NEXUS_HAS_STREAM_MUX
static NEXUS_Error nexus_simpleencoder_p_pre_start( NEXUS_SimpleEncoderHandle handle );
static NEXUS_Error nexus_simpleencoder_p_start_psi( NEXUS_SimpleEncoderHandle handle );
static void nexus_simpleencoder_p_stop_psi( NEXUS_SimpleEncoderHandle handle );
static NEXUS_StcChannelHandle nexus_simpleencoder_p_getStcChannel( NEXUS_SimpleEncoderHandle handle, NEXUS_SimpleDecoderType type );
#endif
static bool ready_to_start(NEXUS_SimpleEncoderHandle handle);

NEXUS_SimpleEncoderHandle NEXUS_SimpleEncoder_Create( unsigned index )
{
    NEXUS_SimpleEncoderHandle handle;

    /* find dup */
    for (handle=BLST_S_FIRST(&g_encoders); handle; handle=BLST_S_NEXT(handle, link)) {
        if (handle->index == index) {
            BERR_TRACE(NEXUS_INVALID_PARAMETER);
            return NULL;
        }
    }

    handle = BKNI_Malloc(sizeof(*handle));
    if (!handle) {
        BERR_TRACE(NEXUS_OUT_OF_SYSTEM_MEMORY);
        return NULL;
    }
    NEXUS_OBJECT_INIT(NEXUS_SimpleEncoder, handle);
    handle->index = index;
    NEXUS_OBJECT_REGISTER(NEXUS_SimpleEncoder, handle, Create);

    /* insert in order. not required, but makes debug easier */
    if (!BLST_S_FIRST(&g_encoders)) {
        BLST_S_INSERT_HEAD(&g_encoders, handle, link);
    }
    else {
        NEXUS_SimpleEncoderHandle prev;
        for (prev=BLST_S_FIRST(&g_encoders);;prev=BLST_S_NEXT(prev, link)) {
            if (!BLST_S_NEXT(prev, link)) {
                BLST_S_INSERT_AFTER(&g_encoders, prev, handle, link);
                break;
            }
        }
    }
    handle->resourceChangedCallback = NEXUS_TaskCallback_Create(handle, NULL);
    /* now a valid object */

    handle->settings.video.interlaced = false;
    handle->settings.video.refreshRate = 60000;
#if NEXUS_HAS_STREAM_MUX
    NEXUS_VideoEncoder_GetDefaultSettings(&handle->settings.videoEncoder);
    handle->settings.videoEncoder.variableFrameRate = false;
#if NEXUS_NUM_DSP_VIDEO_ENCODERS && !NEXUS_DSP_ENCODER_ACCELERATOR_SUPPORT
#define MAX_DSP_VIDEO_WINDOW_WIDTH 416
#define MAX_DSP_VIDEO_WINDOW_HEIGHT 224
    /* this is required for raaga video encode */
    handle->settings.videoEncoder.frameRate = NEXUS_VideoFrameRate_e29_97;
    handle->settings.video.width = MAX_DSP_VIDEO_WINDOW_WIDTH;
    handle->settings.video.height = MAX_DSP_VIDEO_WINDOW_HEIGHT;
    handle->settings.videoEncoder.bitrateMax = 400000; /* 400 Kbps for 416x224p30 dsp */
#else
    handle->settings.videoEncoder.frameRate = NEXUS_VideoFrameRate_e30;
    #if NEXUS_DSP_ENCODER_ACCELERATOR_SUPPORT /* default 480p dsp encoder accelerater */
    handle->settings.video.width  = 720;
    handle->settings.video.height = 480;
    handle->settings.videoEncoder.bitrateMax = 2000000; /* 2 Mbps for 480p30 dsp accelerator; TODO: optimize bit efficiency */
    #else
    handle->settings.video.width  = 1280;
    handle->settings.video.height = 720;
    handle->settings.videoEncoder.bitrateMax = 2500000; /* 2.5 Mbps for 720p30 vce */
    #endif
#endif
    handle->settings.videoEncoder.streamStructure.framesP = 29; /* 29 P frames per gop */
    handle->settings.videoEncoder.streamStructure.framesB = 0; /* IP gop */
    handle->settings.videoEncoder.enableFieldPairing = true;
#endif

    return handle;
}

static void NEXUS_SimpleEncoder_P_Release( NEXUS_SimpleEncoderHandle handle )
{
    NEXUS_OBJECT_ASSERT(NEXUS_SimpleEncoder, handle);
    if (handle->acquired) {
        NEXUS_SimpleEncoder_Release(handle);
    }
    BDBG_ASSERT(!handle->acquired);
    BDBG_ASSERT(!handle->started);
    NEXUS_OBJECT_UNREGISTER(NEXUS_SimpleEncoder, handle, Destroy);
    return;
}

static void NEXUS_SimpleEncoder_P_Finalizer( NEXUS_SimpleEncoderHandle handle )
{
    NEXUS_OBJECT_ASSERT(NEXUS_SimpleEncoder, handle);
    BLST_S_REMOVE(&g_encoders, handle, NEXUS_SimpleEncoder, link);
    if (handle->resourceChangedCallback) {
        NEXUS_TaskCallback_Destroy(handle->resourceChangedCallback);
    }
    NEXUS_OBJECT_DESTROY(NEXUS_SimpleEncoder, handle);
    BKNI_Free(handle);
    return;
}

NEXUS_OBJECT_CLASS_MAKE_WITH_RELEASE(NEXUS_SimpleEncoder, NEXUS_SimpleEncoder_Destroy);

void NEXUS_SimpleEncoder_GetServerSettings( NEXUS_SimpleEncoderHandle handle, NEXUS_SimpleEncoderServerSettings *pSettings )
{
    BDBG_OBJECT_ASSERT(handle, NEXUS_SimpleEncoder);
    *pSettings = handle->serverSettings;
}

NEXUS_Error NEXUS_SimpleEncoder_SetServerSettings( NEXUS_SimpleEncoderHandle handle, const NEXUS_SimpleEncoderServerSettings *pSettings )
{
    bool change;

    BDBG_OBJECT_ASSERT(handle, NEXUS_SimpleEncoder);

    change = (handle->serverSettings.videoEncoder != pSettings->videoEncoder);

    /* we might be losing our decoders, so disconnect */
    if (handle->serverSettings.videoEncoder) {
        nexus_simpleencoder_p_stop(handle);
    }

    handle->serverSettings = *pSettings;

    /* encoder cannot be automatically started here */

    if (change) {
        NEXUS_TaskCallback_Fire(handle->resourceChangedCallback);
    }

    return 0;
}

NEXUS_SimpleEncoderHandle NEXUS_SimpleEncoder_Acquire( unsigned index )
{
    NEXUS_SimpleEncoderHandle handle;

    for (handle=BLST_S_FIRST(&g_encoders); handle; handle = BLST_S_NEXT(handle, link)) {
        BDBG_OBJECT_ASSERT(handle, NEXUS_SimpleEncoder);
        if (handle->index == index) {
            int rc;
            if (handle->acquired) {
                BERR_TRACE(NEXUS_NOT_AVAILABLE);
                return NULL;
            }

            rc = NEXUS_CLIENT_RESOURCES_ACQUIRE(simpleEncoder,IdList,index);
            if (rc) { rc = BERR_TRACE(rc); return NULL; }

            handle->acquired = true;
            return handle;
        }
    }
    return NULL;
}

void NEXUS_SimpleEncoder_Release( NEXUS_SimpleEncoderHandle handle )
{
    BDBG_OBJECT_ASSERT(handle, NEXUS_SimpleEncoder);
    /* IPC handle validation will only allow this call if handle is owned by client.
    For non-IPC used, acquiring is not required, so acquired boolean is not checked in any other API. */
    if (!handle->acquired) {
        BERR_TRACE(NEXUS_NOT_AVAILABLE);
        return;
    }
    if (handle->clientStarted) {
        /* client settings are lost anyway, so force it */
        handle->settings.stopMode = NEXUS_SimpleEncoderStopMode_eAll;
        NEXUS_SimpleEncoder_Stop(handle);
    }

    NEXUS_CLIENT_RESOURCES_RELEASE(simpleEncoder,IdList,handle->index);
    handle->acquired = false;
}

void NEXUS_SimpleEncoder_GetDefaultStartSettings( NEXUS_SimpleEncoderStartSettings *pSettings )
{
    BKNI_Memset(pSettings, 0, sizeof(*pSettings));
    pSettings->output.video.pid = 0x11;
#if NEXUS_HAS_STREAM_MUX
    NEXUS_VideoEncoder_GetDefaultStartSettings(&pSettings->output.video.settings);
    pSettings->output.video.settings.codec = NEXUS_VideoCodec_eH264;
    pSettings->output.video.settings.profile = NEXUS_VideoCodecProfile_eMain;/* main/high profile enabled CABAC to improve bit efficiency */
    pSettings->output.video.settings.level = NEXUS_VideoCodecLevel_e31;
#endif
    pSettings->output.audio.pid = 0x14;
    pSettings->output.audio.codec = NEXUS_AudioCodec_eAac;
    pSettings->output.transport.type = NEXUS_TransportType_eTs;
    pSettings->output.transport.pcrPid = 0x15;
    pSettings->output.transport.pmtPid = 0x55;
    pSettings->output.transport.interval = 1000; /* 1 second */
}

NEXUS_Error NEXUS_SimpleEncoder_Start( NEXUS_SimpleEncoderHandle handle, const NEXUS_SimpleEncoderStartSettings *pSettings )
{
    NEXUS_Error rc;
    unsigned i;
    BDBG_OBJECT_ASSERT(handle, NEXUS_SimpleEncoder);

    if (handle->clientStarted) {
        return BERR_TRACE(NEXUS_NOT_AVAILABLE);
    }

#if NEXUS_HAS_STREAM_MUX
    if (handle->inputStarted) {
        /* NEXUS_SimpleEncoderStopMode_eVideoEncoderOnly was called. NEXUS_SimpleEncoderStartSettings must be the same. */
        if (BKNI_Memcmp(pSettings, &handle->startSettings, sizeof(*pSettings))) {
            return BERR_TRACE(NEXUS_INVALID_PARAMETER);
        }
        goto encoder_start;
    }
#endif

    if (!pSettings->input.video && !pSettings->input.audio && !pSettings->input.display) {
        return BERR_TRACE(NEXUS_INVALID_PARAMETER);
    }
    if (pSettings->input.display) {
        if (handle->serverSettings.nonRealTime) {
            return BERR_TRACE(NEXUS_INVALID_PARAMETER);
        }
        if (!handle->serverSettings.displayEncode.display) {
            return BERR_TRACE(NEXUS_INVALID_PARAMETER);
        }
        if (pSettings->input.video || pSettings->input.audio) {
            return BERR_TRACE(NEXUS_INVALID_PARAMETER);
        }
    }
    if (pSettings->output.transport.type == NEXUS_TransportType_eTs && !pSettings->recpump) {
        return BERR_TRACE(NEXUS_INVALID_PARAMETER);
    }

    handle->audioStarted = (pSettings->input.display || pSettings->input.audio) && (pSettings->output.audio.codec != NEXUS_AudioCodec_eUnknown);
    if (handle->audioStarted && !handle->serverSettings.audioMuxOutput) {
        handle->audioStarted = false;
        return BERR_TRACE(NEXUS_NOT_AVAILABLE);
    }
    handle->videoStarted = pSettings->input.display || pSettings->input.video;
    if (handle->videoStarted && !handle->serverSettings.videoEncoder) {
        handle->audioStarted = false;
        handle->videoStarted = false;
        return BERR_TRACE(NEXUS_NOT_AVAILABLE);
    }

    if (pSettings->input.video) {
        NEXUS_OBJECT_ACQUIRE(handle, NEXUS_SimpleVideoDecoder, pSettings->input.video);
    }
    if (pSettings->input.audio) {
        NEXUS_OBJECT_ACQUIRE(handle, NEXUS_SimpleAudioDecoder, pSettings->input.audio);
    }
    if ( pSettings->recpump ) {
        NEXUS_OBJECT_ACQUIRE(handle, NEXUS_Recpump, pSettings->recpump);
    }
    for (i=0;i<NEXUS_SIMPLE_ENCODER_NUM_PASSTHROUGH_PIDS;i++) {
        if (pSettings->passthrough[i]) {
            NEXUS_OBJECT_ACQUIRE(handle, NEXUS_PidChannel, pSettings->passthrough[i]);
        }
    }

    handle->clientStarted = true;
    handle->startSettings = *pSettings;

#if NEXUS_HAS_STREAM_MUX
    /* try to make defaults work out as much as possible */
    switch (handle->startSettings.output.video.settings.codec) {
    case NEXUS_VideoCodec_eMpeg2:
        /* this is the only profile and level supported, so default to it */
        handle->startSettings.output.video.settings.profile = NEXUS_VideoCodecProfile_eMain;
        handle->startSettings.output.video.settings.level = NEXUS_VideoCodecLevel_eMain;
        break;
    default:
        break;
    }

    rc = nexus_simpleencoder_p_pre_start(handle);
    if (rc) {
        rc = BERR_TRACE(rc);
        NEXUS_SimpleEncoder_Stop(handle);
        return rc;
    }

encoder_start:
    if (ready_to_start(handle)) {
        rc = nexus_simpleencoder_p_start(handle);
        if (rc) {
            NEXUS_SimpleEncoder_Stop(handle);
            return BERR_TRACE(rc);
        }
    }
#else
    BSTD_UNUSED(rc);
#endif

    /* now wait for decoders for actual start of encoder */

    return 0;
}

void NEXUS_SimpleEncoder_Stop( NEXUS_SimpleEncoderHandle handle )
{
    unsigned i;
    BDBG_OBJECT_ASSERT(handle, NEXUS_SimpleEncoder);

    if (!handle->clientStarted) return;

    handle->clientStarted = false;
    nexus_simpleencoder_p_stop(handle);
    handle->videoStarted = false;
    if(!handle->inputStarted) {
        handle->audioStarted = false;
        if (handle->startSettings.input.video) {
            NEXUS_OBJECT_RELEASE(handle, NEXUS_SimpleVideoDecoder, handle->startSettings.input.video);
        }
        if (handle->startSettings.input.audio) {
            NEXUS_OBJECT_RELEASE(handle, NEXUS_SimpleAudioDecoder, handle->startSettings.input.audio);
        }
        if (handle->startSettings.recpump) {
            NEXUS_OBJECT_RELEASE(handle, NEXUS_Recpump, handle->startSettings.recpump);
        }
        for (i=0;i<NEXUS_SIMPLE_ENCODER_NUM_PASSTHROUGH_PIDS;i++) {
            if (handle->startSettings.passthrough[i]) {
                NEXUS_OBJECT_RELEASE(handle, NEXUS_PidChannel, handle->startSettings.passthrough[i]);
            }
        }
        NEXUS_SimpleEncoder_GetDefaultStartSettings(&handle->startSettings);
    }
}

void NEXUS_SimpleEncoder_GetSettings( NEXUS_SimpleEncoderHandle handle, NEXUS_SimpleEncoderSettings *pSettings )
{
    BDBG_OBJECT_ASSERT(handle, NEXUS_SimpleEncoder);
    *pSettings = handle->settings;
}

NEXUS_Error NEXUS_SimpleEncoder_SetSettings( NEXUS_SimpleEncoderHandle handle, const NEXUS_SimpleEncoderSettings *pSettings )
{
    int rc;
    BDBG_OBJECT_ASSERT(handle, NEXUS_SimpleEncoder);
    NEXUS_TaskCallback_Set(handle->resourceChangedCallback, &pSettings->resourceChanged);

    if (!handle->clientStarted) {
        /* if client not started, we don't know if this is background or display encode, so defer */
        goto done;
    }
    if ((pSettings->stopMode == NEXUS_SimpleEncoderStopMode_eVideoEncoderOnly) &&
        (handle->startSettings.output.transport.type != NEXUS_TransportType_eEs || handle->serverSettings.nonRealTime)) {
        BDBG_ERR(("NEXUS_SimpleEncoderStopMode_eVideoEncoderOnly only supports ES output in RT mode."));
        return BERR_TRACE(NEXUS_INVALID_PARAMETER);
    }

#if NEXUS_HAS_STREAM_MUX
#if NEXUS_NUM_DSP_VIDEO_ENCODERS && !NEXUS_DSP_ENCODER_ACCELERATOR_SUPPORT
#else
    /* client doesn't change display format when encoding the display */
    if (handle->serverSettings.transcodeDisplay && !handle->startSettings.input.display) {
        NEXUS_DisplayCustomFormatSettings customFormatSettings;

        NEXUS_Display_GetDefaultCustomFormatSettings(&customFormatSettings);
        customFormatSettings.width = handle->settings.video.width;
        customFormatSettings.height = handle->settings.video.height;
        customFormatSettings.refreshRate = handle->settings.video.refreshRate;
        customFormatSettings.interlaced = handle->settings.video.interlaced;
        customFormatSettings.aspectRatio = NEXUS_DisplayAspectRatio_e16x9; /* don't care */
        customFormatSettings.dropFrameAllowed = true;
        rc = NEXUS_Display_SetCustomFormatSettings(handle->serverSettings.transcodeDisplay, NEXUS_VideoFormat_eCustom2, &customFormatSettings);
        if (rc) return BERR_TRACE(rc);
    }
    if (handle->transcodeWindow) {
        NEXUS_VideoWindowSettings windowSettings;
        NEXUS_VideoWindow_GetSettings(handle->transcodeWindow, &windowSettings);
        if (handle->settings.video.window.width && handle->settings.video.window.height) {
            windowSettings.position = handle->settings.video.window;
        }
        else {
            windowSettings.position.x = 0;
            windowSettings.position.y = 0;
            windowSettings.position.width = handle->settings.video.width;
            windowSettings.position.height = handle->settings.video.height;
        }
        windowSettings.sourceClip.left   = handle->settings.video.clip.left;
        windowSettings.sourceClip.right  = handle->settings.video.clip.right;
        windowSettings.sourceClip.top    = handle->settings.video.clip.top;
        windowSettings.sourceClip.bottom = handle->settings.video.clip.bottom;
        rc = NEXUS_VideoWindow_SetSettings(handle->transcodeWindow, &windowSettings);
        if (rc) return BERR_TRACE(rc);
    }
#endif

    /* TODO: handle->settings.audioEncoder */

    if (handle->serverSettings.videoEncoder) {
        rc = NEXUS_VideoEncoder_SetSettings(handle->serverSettings.videoEncoder, &pSettings->videoEncoder);
        if (rc) return BERR_TRACE(rc);
    }
#else
    BSTD_UNUSED(rc);
#endif

done:
    handle->settings = *pSettings;
    return 0;
}

static bool ready_to_start(NEXUS_SimpleEncoderHandle handle)
{
    return handle->clientStarted && !handle->wait.audio && !handle->wait.video && !handle->started;
}

NEXUS_Error nexus_simpleencoder_p_start_audio(NEXUS_SimpleEncoderHandle handle)
{
    BDBG_OBJECT_ASSERT(handle, NEXUS_SimpleEncoder);
    if (!handle->wait.audio) return false;
    handle->wait.audio = false;
    if (ready_to_start(handle)) {
        return nexus_simpleencoder_p_start(handle);
    }
    else {
        return 0;
    }
}

NEXUS_Error nexus_simpleencoder_p_start_video(NEXUS_SimpleEncoderHandle handle)
{
    BDBG_OBJECT_ASSERT(handle, NEXUS_SimpleEncoder);
    if (!handle->wait.video) return false;
    handle->wait.video = false;
    if (ready_to_start(handle)) {
        return nexus_simpleencoder_p_start(handle);
    }
    else {
        return 0;
    }
}

#if NEXUS_HAS_STREAM_MUX
/**
pre_start validates state, creates any window, and links the decoders. this allows the decoders to start.
**/
static NEXUS_Error nexus_simpleencoder_p_pre_start( NEXUS_SimpleEncoderHandle handle )
{
    int rc;

    if (handle->started) {
        return BERR_TRACE(NEXUS_NOT_AVAILABLE);
    }
    /* if (handle->startSettings.input.display), nothing to do for video */
    if (handle->startSettings.input.video) {
#if NEXUS_NUM_DSP_VIDEO_ENCODERS && !NEXUS_DSP_ENCODER_ACCELERATOR_SUPPORT
        NEXUS_VideoWindowSettings windowSettings;
#endif

        if (!handle->serverSettings.transcodeDisplay) {
            return BERR_TRACE(NEXUS_NOT_AVAILABLE);
        }
        handle->transcodeWindow = NEXUS_VideoWindow_Open(handle->serverSettings.transcodeDisplay, 0);
        if (!handle->transcodeWindow) {
            rc = BERR_TRACE(NEXUS_NOT_AVAILABLE);
            goto err_openwindow;
        }

#if NEXUS_NUM_DSP_VIDEO_ENCODERS && !NEXUS_DSP_ENCODER_ACCELERATOR_SUPPORT
        NEXUS_VideoWindow_GetSettings(handle->transcodeWindow, &windowSettings);
        if (handle->settings.video.width > MAX_DSP_VIDEO_WINDOW_WIDTH ||
            handle->settings.video.height > MAX_DSP_VIDEO_WINDOW_HEIGHT)
        {
            BDBG_ERR(("%dx%d exceeds DSP encoder limit of %dx%d", handle->settings.video.width, handle->settings.video.height,
                MAX_DSP_VIDEO_WINDOW_WIDTH, MAX_DSP_VIDEO_WINDOW_HEIGHT));
            return BERR_TRACE(NEXUS_INVALID_PARAMETER);
        }
        windowSettings.position.width = handle->settings.video.width;
        windowSettings.position.height = handle->settings.video.height;
        windowSettings.pixelFormat = NEXUS_PixelFormat_eCr8_Y18_Cb8_Y08;
        windowSettings.visible = false;
        rc = NEXUS_VideoWindow_SetSettings(handle->transcodeWindow, &windowSettings);
        if (rc) {rc = BERR_TRACE(rc); goto err_encodersettings;}
#endif

        /* call once at pre-start and a second time at start */
        rc = NEXUS_SimpleEncoder_SetSettings(handle, &handle->settings);
        if (rc) {rc = BERR_TRACE(rc); goto err_encodersettings;}

        rc = nexus_simplevideodecoder_p_add_encoder(handle->startSettings.input.video, handle->transcodeWindow, handle);
        if (rc) {rc = BERR_TRACE(rc); goto err_addinput;}

#if NEXUS_NUM_DSP_VIDEO_ENCODERS && !NEXUS_DSP_ENCODER_ACCELERATOR_SUPPORT
        /* DSP video encode requires waiting for decode to start */
        handle->wait.video = true;
#endif
    }

    if (handle->audioStarted) {
        if (handle->startSettings.input.display) {
            rc = nexus_simpleaudiodecoder_p_add_encoder(
                handle->serverSettings.displayEncode.masterAudio,
                handle->serverSettings.displayEncode.slaveAudio,
                handle->serverSettings.audioMuxOutput,
                handle->startSettings.output.audio.codec,
                handle->startSettings.output.audio.passthrough,
                handle->startSettings.output.audio.sampleRate,
                handle,
                handle->serverSettings.mixer,
                true);
            if (rc) {rc = BERR_TRACE(rc); goto err_addaudioinput;}
        }
        else {
            rc = nexus_simpleaudiodecoder_p_add_encoder(
                handle->startSettings.input.audio,
                NULL,
                handle->serverSettings.audioMuxOutput,
                handle->startSettings.output.audio.codec,
                handle->startSettings.output.audio.passthrough,
                handle->startSettings.output.audio.sampleRate,
                handle,
                handle->serverSettings.mixer,
                false);
            if (rc) {rc = BERR_TRACE(rc); goto err_addaudioinput;}
        }
#if 0
        handle->wait.audio = true;
#endif
    }

    return 0;

err_addaudioinput:
    if (handle->startSettings.input.video) {
        nexus_simplevideodecoder_p_remove_encoder(handle->startSettings.input.video, handle->transcodeWindow, handle);
    }
err_addinput:
err_encodersettings:
    if (handle->transcodeWindow) {
        NEXUS_VideoWindow_Close(handle->transcodeWindow);
        handle->transcodeWindow = NULL;
    }
err_openwindow:
    return rc;
}

static NEXUS_Error nexus_simpleencoder_p_set_playpump(NEXUS_PlaypumpHandle playpump, bool tts, bool pcr)
{
    NEXUS_PlaypumpSettings playpumpSettings;
    NEXUS_Playpump_GetSettings(playpump, &playpumpSettings);
    if (playpumpSettings.timestamp.forceRestamping != tts || playpumpSettings.blindSync != pcr) {
        playpumpSettings.timestamp.forceRestamping = tts;
        playpumpSettings.blindSync = pcr;
        return NEXUS_Playpump_SetSettings(playpump, &playpumpSettings);
    }
    else {
        /* no change */
        return 0;
    }
}

static NEXUS_Error nexus_simpleencoder_p_start_stream_mux(NEXUS_SimpleEncoderHandle handle)
{
    NEXUS_Error rc;
    NEXUS_StreamMuxStartSettings *pMuxStartSettings;
    NEXUS_StreamMuxOutput muxOutput;
    NEXUS_PidChannelHandle pidChannel;
    NEXUS_RecpumpSettings recpumpSettings;
    bool tts;
    unsigned i;

    pMuxStartSettings = BKNI_Malloc(sizeof(*pMuxStartSettings));
    if (!pMuxStartSettings) {
        return BERR_TRACE(NEXUS_OUT_OF_SYSTEM_MEMORY);
    }

    NEXUS_Recpump_GetSettings(handle->startSettings.recpump, &recpumpSettings);
    tts = (recpumpSettings.timestampType != NEXUS_TransportTimestampType_eNone);

    NEXUS_StreamMux_GetDefaultStartSettings(pMuxStartSettings);
    pMuxStartSettings->transportType = handle->startSettings.output.transport.type;
    pMuxStartSettings->stcChannel = nexus_simpleencoder_p_getStcChannel(handle, NEXUS_SimpleDecoderType_eVideo);
    if (!pMuxStartSettings->stcChannel) {
        pMuxStartSettings->stcChannel = nexus_simpleencoder_p_getStcChannel(handle, NEXUS_SimpleDecoderType_eAudio);
    }
    pMuxStartSettings->nonRealTime = handle->serverSettings.nonRealTime;
    pMuxStartSettings->nonRealTimeRate = 32 * NEXUS_NORMAL_PLAY_SPEED; /* AFAP */
    if (handle->videoStarted) {
        pMuxStartSettings->video[0].pid = handle->startSettings.output.video.pid;
        pMuxStartSettings->video[0].encoder = handle->serverSettings.videoEncoder;
        pMuxStartSettings->video[0].playpump = handle->serverSettings.playpump[0];
        nexus_simpleencoder_p_set_playpump(pMuxStartSettings->video[0].playpump, tts, false);
    }
    if (handle->audioStarted) {
        pMuxStartSettings->audio[0].pid = handle->startSettings.output.audio.pid;
        pMuxStartSettings->audio[0].muxOutput = handle->serverSettings.audioMuxOutput;
        pMuxStartSettings->audio[0].playpump = handle->serverSettings.playpump[1];
        nexus_simpleencoder_p_set_playpump(pMuxStartSettings->audio[0].playpump, tts, false);
    }
    if (handle->startSettings.output.transport.pcrPid) {
        pMuxStartSettings->pcr.pid = handle->startSettings.output.transport.pcrPid;
        pMuxStartSettings->pcr.playpump = handle->serverSettings.playpump[2];
        nexus_simpleencoder_p_set_playpump(pMuxStartSettings->pcr.playpump, tts, true);
        pMuxStartSettings->pcr.interval = 50;
    }
    for (i=0;i<NEXUS_SIMPLE_ENCODER_NUM_PASSTHROUGH_PIDS;i++) {
        if (handle->startSettings.passthrough[i]) {
            NEXUS_MessageSettings messageSettings;
            NEXUS_MessageStartSettings messageStartSettings;

            NEXUS_Message_GetDefaultSettings(&messageSettings);
            messageSettings.bufferSize = 512*1024;
            messageSettings.maxContiguousMessageSize = 0; /* to support TS capture and in-place operation */
            pMuxStartSettings->userdata[i].message = handle->message[i] = NEXUS_Message_Open(&messageSettings);
            if (!handle->message[i]) {rc = BERR_TRACE(NEXUS_NOT_AVAILABLE); goto err_message;}

            NEXUS_Message_GetDefaultStartSettings(handle->message[i], &messageStartSettings);
            messageStartSettings.format = NEXUS_MessageFormat_eTs;
            messageStartSettings.pidChannel = handle->startSettings.passthrough[i];
            rc = NEXUS_Message_Start(handle->message[i], &messageStartSettings);
            if (rc) {rc = BERR_TRACE(rc); goto err_message;}
        }
    }
    /* session display encode needs low latency */
    if(handle->startSettings.input.display) {
        pMuxStartSettings->servicePeriod    = 10;/* ms */
        pMuxStartSettings->latencyTolerance = 20;/* ms */
    }
    rc = NEXUS_StreamMux_Start(handle->serverSettings.streamMux, pMuxStartSettings, &muxOutput);
    if (rc) {rc = BERR_TRACE(rc); goto err_startmux;}

    BKNI_Free(pMuxStartSettings);
    pMuxStartSettings = NULL;

    if (handle->startSettings.output.transport.pcrPid) {
        pidChannel = NEXUS_Playpump_OpenPidChannel(handle->serverSettings.playpump[2], handle->startSettings.output.transport.pcrPid, NULL);
        if (!pidChannel) {rc = BERR_TRACE(NEXUS_UNKNOWN); goto err_openpid;}
        rc = NEXUS_Recpump_AddPidChannel(handle->startSettings.recpump, pidChannel, NULL);
        if (rc) {rc = BERR_TRACE(rc); goto err_openpid;}

        /* TTS format may adjust timestamp by pcr; however, client doesn't have access to pcr pid channel, so we set it here. */
        if (tts && recpumpSettings.adjustTimestampUsingPcrs) {
            recpumpSettings.pcrPidChannel = pidChannel;
            rc = NEXUS_Recpump_SetSettings(handle->startSettings.recpump, &recpumpSettings);
            if (rc) {rc = BERR_TRACE(rc); goto err_openpid;}
        }
    }

    if (handle->startSettings.output.transport.pmtPid) {
        pidChannel = NEXUS_Playpump_OpenPidChannel(handle->serverSettings.playpump[2], handle->startSettings.output.transport.pmtPid, NULL);
        if (!pidChannel) {rc = BERR_TRACE(NEXUS_UNKNOWN); goto err_openpid;}
        rc = NEXUS_Recpump_AddPidChannel(handle->startSettings.recpump, pidChannel, NULL);
        if (rc) {rc = BERR_TRACE(rc); goto err_openpid;}

        /* PAT, always pid 0x0 */
        pidChannel = NEXUS_Playpump_OpenPidChannel(handle->serverSettings.playpump[2], 0, NULL);
        if (!pidChannel) {rc = BERR_TRACE(NEXUS_UNKNOWN); goto err_openpid;}
        rc = NEXUS_Recpump_AddPidChannel(handle->startSettings.recpump, pidChannel, NULL);
        if (rc) {rc = BERR_TRACE(rc); goto err_openpid;}
    }
    for (i=0;i<NEXUS_SIMPLE_ENCODER_NUM_PASSTHROUGH_PIDS;i++) {
        if (handle->startSettings.passthrough[i]) {
            NEXUS_PidChannelStatus status;
            NEXUS_PidChannel_GetStatus(handle->startSettings.passthrough[i], &status);
            pidChannel = NEXUS_Playpump_OpenPidChannel(handle->serverSettings.playpump[2], status.remappedPid, NULL);
            if (!pidChannel) {rc = BERR_TRACE(NEXUS_UNKNOWN); goto err_openpid;}
            rc = NEXUS_Recpump_AddPidChannel(handle->startSettings.recpump, pidChannel, NULL);
            if (rc) {rc = BERR_TRACE(rc); goto err_openpid;}
        }
    }

    if (muxOutput.video[0]) {
        NEXUS_RecpumpAddPidChannelSettings settings;
        NEXUS_Recpump_GetDefaultAddPidChannelSettings(&settings);
        if (handle->startSettings.output.video.index) {
            settings.pidType = NEXUS_PidType_eVideo;
            settings.pidTypeSettings.video.index = true;
            settings.pidTypeSettings.video.codec = handle->startSettings.output.video.settings.codec;
        }
        rc = NEXUS_Recpump_AddPidChannel(handle->startSettings.recpump, muxOutput.video[0], &settings);
        if (rc) {rc = BERR_TRACE(rc); goto err_addpid;}

        /* may want user option for TPIT RAI indexing. required for HLS now. */
        if (handle->startSettings.output.video.raiIndex) {
            NEXUS_RecpumpTpitFilter filter;
            NEXUS_Recpump_GetDefaultTpitFilter(&filter);
            filter.config.mpeg.randomAccessIndicatorEnable = true;
            filter.config.mpeg.randomAccessIndicatorCompValue = true;
            rc = NEXUS_Recpump_SetTpitFilter(handle->startSettings.recpump, muxOutput.video[0], &filter);
            if (rc) {rc = BERR_TRACE(rc); goto err_addpid;}
        }
    }
    if (muxOutput.audio[0]) {
        rc = NEXUS_Recpump_AddPidChannel(handle->startSettings.recpump, muxOutput.audio[0], NULL);
        if (rc) {rc = BERR_TRACE(rc); goto err_addpid;}
    }

    return 0;

err_addpid:
    NEXUS_Recpump_RemoveAllPidChannels(handle->startSettings.recpump);
err_openpid:
    NEXUS_Playpump_CloseAllPidChannels(handle->serverSettings.playpump[2]);
    NEXUS_StreamMux_Stop(handle->serverSettings.streamMux);
err_startmux:
err_message:
    for (i=0;i<NEXUS_SIMPLE_ENCODER_NUM_PASSTHROUGH_PIDS;i++) {
        if (handle->message[i]) {
            NEXUS_Message_Close(handle->message[i]);
            handle->message[i] = NULL;
        }
    }
    if (pMuxStartSettings) {
        BKNI_Free(pMuxStartSettings);
    }
    return rc;
}

/* For real-time transcode, the encoder has its own StcChannel while video/audio decoders share.
For non-real-time transcode, video and audio need separate StcChannels and the encoder can share with video or audio. */
static NEXUS_StcChannelHandle nexus_simpleencoder_p_getStcChannel( NEXUS_SimpleEncoderHandle handle, NEXUS_SimpleDecoderType type )
{
    if (handle->serverSettings.nonRealTime) {
        NEXUS_SimpleStcChannelHandle simpleStcChannel = NULL;
        if (type == NEXUS_SimpleDecoderType_eVideo && handle->startSettings.input.video) {
            simpleStcChannel = NEXUS_SimpleVideoDecoder_P_GetStcChannel(handle->startSettings.input.video);
        }
        else if (type == NEXUS_SimpleDecoderType_eAudio && handle->startSettings.input.audio) {
            simpleStcChannel = NEXUS_SimpleAudioDecoder_P_GetStcChannel(handle->startSettings.input.audio);
        }
        if (simpleStcChannel) {
            return NEXUS_SimpleStcChannel_GetServerStcChannel_priv(simpleStcChannel, type);
        }
        else {
            return NULL;
        }
    }
    else {
        return handle->serverSettings.stcChannelTranscode;
    }
}

/**
actual start happens after decoders are started
**/
static NEXUS_Error nexus_simpleencoder_p_start( NEXUS_SimpleEncoderHandle handle )
{
    NEXUS_Error rc;

    BDBG_MSG(("nexus_simpleencoder_p_start %p", (void *)handle));
    if (handle->started) {
        return BERR_TRACE(NEXUS_NOT_AVAILABLE);
    }

    if (handle->videoStarted) {

        handle->stack.videoEncoderStartSettings = handle->startSettings.output.video.settings;
#ifdef NEXUS_NUM_DSP_VIDEO_ENCODERS
        handle->stack.videoEncoderStartSettings.bounds.inputDimension.max.width = handle->settings.video.width;
        handle->stack.videoEncoderStartSettings.bounds.inputDimension.max.height = handle->settings.video.height;
#endif
        handle->stack.videoEncoderStartSettings.stcChannel = nexus_simpleencoder_p_getStcChannel(handle, NEXUS_SimpleDecoderType_eVideo);

        if (handle->startSettings.input.display) {
            handle->stack.videoEncoderStartSettings.input = handle->serverSettings.displayEncode.display;
            /* session display encode needs low latency override:
                   1) rateBufferDelay - 0 defaults to large delay; overrides it with low latency default;
                   2) fieldPairing - increases encoder pre-process delay; turn it off for session encode;
                   3) adaptiveLowDelayMode - to reduce encode start latency;
                   */
            if(handle->stack.videoEncoderStartSettings.rateBufferDelay == 0) {
                handle->stack.videoEncoderStartSettings.rateBufferDelay        = 50;/* ms */
            }
            /* if decoder is not stopped, encoder stop/start with this mode ON might drop all frames;
               so leave it to app to control.*/
            /*videoEncoderStartSettings.adaptiveLowDelayMode = true;*/
            handle->settings.videoEncoder.enableFieldPairing = false;
        }
        else if (handle->startSettings.input.video) {
            handle->stack.videoEncoderStartSettings.input = handle->serverSettings.transcodeDisplay;
        }

        /* NOTE: video encoder delay is in 27MHz ticks */
        NEXUS_VideoEncoder_GetDelayRange(handle->serverSettings.videoEncoder, &handle->settings.videoEncoder, &handle->stack.videoEncoderStartSettings, &handle->stack.videoDelay);
        BDBG_WRN(("Video encoder end-to-end delay = [%u ~ %u] ms", handle->stack.videoDelay.min/27000, handle->stack.videoDelay.max/27000));

        if (handle->audioStarted) {
            unsigned Dee;

            rc = NEXUS_AudioMuxOutput_GetDelayStatus(handle->serverSettings.audioMuxOutput, handle->startSettings.output.audio.codec, &handle->stack.audioDelayStatus);
            BDBG_WRN(("Audio codec %d end-to-end delay = %u ms", handle->startSettings.output.audio.codec, handle->stack.audioDelayStatus.endToEndDelay));

            if (rc) {
                Dee = handle->stack.videoDelay.max;
            }
            else {
                Dee = handle->stack.audioDelayStatus.endToEndDelay * 27000; /* in 27MHz ticks */
            }
            if(Dee > handle->stack.videoDelay.min)
            {
                if(Dee > handle->stack.videoDelay.max)
                {
                    BDBG_ERR(("Audio Dee is way too big! Use video Dee max!"));
                    Dee = handle->stack.videoDelay.max;
                }
                else
                {
                    BDBG_WRN(("Use audio Dee %u ms %u ticks@27Mhz!", Dee/27000, Dee));
                }
            }
            else
            {
                Dee = handle->stack.videoDelay.min;
                BDBG_WRN(("Use video Dee %u ms %u ticks@27Mhz!", Dee/27000, Dee));
            }
            handle->settings.videoEncoder.encoderDelay = Dee;

            /* Start audio mux output */
            if(!handle->inputStarted) {
                NEXUS_AudioMuxOutput_GetDefaultStartSettings(&handle->stack.audioMuxStartSettings);
                handle->stack.audioMuxStartSettings.stcChannel = nexus_simpleencoder_p_getStcChannel(handle, NEXUS_SimpleDecoderType_eAudio);
                handle->stack.audioMuxStartSettings.presentationDelay = Dee/27000;/* in ms */
                handle->stack.audioMuxStartSettings.nonRealTime = nexus_simpleencoder_p_nonRealTime(handle);
                rc = NEXUS_AudioMuxOutput_Start(handle->serverSettings.audioMuxOutput, &handle->stack.audioMuxStartSettings);
                if (rc) {rc = BERR_TRACE(rc); goto err_startaudio;}
            }
        }
        else {
            handle->settings.videoEncoder.encoderDelay = handle->stack.videoDelay.min;
        }

        /* reapply settings with new encoderDelay */
        rc = NEXUS_SimpleEncoder_SetSettings(handle, &handle->settings);
        if (rc) {rc = BERR_TRACE(rc); goto err_encodersettings;}

        handle->stack.videoEncoderStartSettings.nonRealTime = nexus_simpleencoder_p_nonRealTime(handle);
        rc = NEXUS_VideoEncoder_Start(handle->serverSettings.videoEncoder, &handle->stack.videoEncoderStartSettings);
        if (rc) {rc = BERR_TRACE(rc); goto err_startvideoenc;}
    }
    else if(!handle->inputStarted) {
        /* Start audio mux output */
        NEXUS_AudioMuxOutput_GetDelayStatus(handle->serverSettings.audioMuxOutput, handle->startSettings.output.audio.codec, &handle->stack.audioDelayStatus);
        NEXUS_AudioMuxOutput_GetDefaultStartSettings(&handle->stack.audioMuxStartSettings);
        handle->stack.audioMuxStartSettings.stcChannel = nexus_simpleencoder_p_getStcChannel(handle, NEXUS_SimpleDecoderType_eAudio);
        handle->stack.audioMuxStartSettings.presentationDelay = handle->stack.audioDelayStatus.endToEndDelay;
        handle->stack.audioMuxStartSettings.nonRealTime = nexus_simpleencoder_p_nonRealTime(handle);
        rc = NEXUS_AudioMuxOutput_Start(handle->serverSettings.audioMuxOutput, &handle->stack.audioMuxStartSettings);
        if (rc) {rc = BERR_TRACE(rc); goto err_startaudio;}
    }

    if (handle->serverSettings.mixer && !handle->inputStarted) {
        /* must be started after NEXUS_AudioMuxOutput_Start */
        rc = NEXUS_AudioMixer_Start(handle->serverSettings.mixer);
        if (rc) {rc = BERR_TRACE(rc); goto err_mixer_start;}
    }

    if ( handle->startSettings.output.transport.type == NEXUS_TransportType_eTs ) {
        nexus_simpleencoder_p_start_psi(handle);

        rc = nexus_simpleencoder_p_start_stream_mux(handle);
        if (rc) {rc = BERR_TRACE(rc); goto err_stream_mux;}
    }

    handle->inputStarted = true;
    handle->started = true;
    return 0;

err_stream_mux:
    if ( handle->startSettings.output.transport.type == NEXUS_TransportType_eTs ) {
        nexus_simpleencoder_p_stop_psi(handle);
    }
    if (handle->serverSettings.mixer) {
        NEXUS_AudioMixer_Stop(handle->serverSettings.mixer);
    }
err_mixer_start:
    if (handle->videoStarted) {
        NEXUS_VideoEncoder_Stop(handle->serverSettings.videoEncoder, NULL);
    }
err_startvideoenc:
err_encodersettings:
    if (handle->audioStarted) {
        NEXUS_AudioMuxOutput_Stop(handle->serverSettings.audioMuxOutput);
    }
err_startaudio:
    BDBG_ASSERT(rc);
    return rc;
}

void nexus_simpleencoder_p_stop( NEXUS_SimpleEncoderHandle handle )
{
    BDBG_MSG(("nexus_simpleencoder_p_stop %p: %d %d %p %p", (void *)handle, handle->started, handle->audioStarted, (void *)handle->startSettings.input.video, (void *)handle->transcodeWindow));
    if (handle->started) {
        unsigned i;
        handle->started = false;
        if ( handle->startSettings.output.transport.type == NEXUS_TransportType_eTs ) {
            NEXUS_RecpumpSettings recpumpSettings;
            NEXUS_Recpump_RemoveAllPidChannels(handle->startSettings.recpump); /* TODO: remove only the pid channels we've added */
            NEXUS_Recpump_GetSettings(handle->startSettings.recpump, &recpumpSettings);
            if (recpumpSettings.pcrPidChannel) {
                recpumpSettings.pcrPidChannel = NULL;
                (void)NEXUS_Recpump_SetSettings(handle->startSettings.recpump, &recpumpSettings);
            }
            NEXUS_Playpump_CloseAllPidChannels(handle->serverSettings.playpump[2]);
            NEXUS_StreamMux_Stop(handle->serverSettings.streamMux);
            nexus_simpleencoder_p_stop_psi(handle);
        }
        for (i=0;i<NEXUS_SIMPLE_ENCODER_NUM_PASSTHROUGH_PIDS;i++) {
            if (handle->message[i]) {
                NEXUS_Message_Close(handle->message[i]);
                handle->message[i] = NULL;
            }
        }
        if (handle->videoStarted) {
            NEXUS_VideoEncoderStopSettings settings;
            NEXUS_VideoEncoder_GetDefaultStopSettings(&settings);
            settings.mode = NEXUS_VideoEncoderStopMode_eAbort; /* immediate */
            NEXUS_VideoEncoder_Stop(handle->serverSettings.videoEncoder, &settings);
        }
    }

    /* stop mode eVideoEncoderOnly needs to keep audio mixer/mux output continuous in RT mode */
    if (handle->settings.stopMode != NEXUS_SimpleEncoderStopMode_eVideoEncoderOnly && handle->inputStarted) {
        if (handle->serverSettings.mixer) {
            NEXUS_AudioMixer_Stop(handle->serverSettings.mixer);
        }
        if (handle->audioStarted) {
            NEXUS_AudioMuxOutput_Stop(handle->serverSettings.audioMuxOutput);
        }
        if (handle->audioStarted) {
            if (handle->startSettings.input.display) {
                nexus_simpleaudiodecoder_p_remove_encoder(handle->serverSettings.displayEncode.masterAudio);
            }
            else {
                nexus_simpleaudiodecoder_p_remove_encoder(handle->startSettings.input.audio);
            }
        }
        handle->inputStarted = false;
    }

    if (handle->startSettings.input.video) {
        nexus_simplevideodecoder_p_remove_encoder(handle->startSettings.input.video, handle->transcodeWindow, handle);
    }
    if (handle->transcodeWindow) {
        NEXUS_VideoWindow_Close(handle->transcodeWindow);
        handle->transcodeWindow = NULL;
    }
    handle->wait.video = false;
    handle->wait.audio = false;
}

/* TSHDRBUILDER has one extra byte at the beginning to describe the variable length TS header buffer */
#define BTST_TS_HEADER_BUF_LENGTH 189
#define NEXUS_SIMPLE_ENCODER_PSI_QUEUE_CNT 32 /* TODO: use GetComplete to recycle the queue */
#define PAT_PMT_PAIR_SIZE (BTST_TS_HEADER_BUF_LENGTH*2)

static void nexus_simpleencoder_p_psi_timer( void *context )
{
    NEXUS_StreamMuxSystemData psi[2];
    NEXUS_SimpleEncoderHandle handle = context;
    uint8_t *pat, *pmt;

    handle->psi.timer = NULL;

    pat = handle->psi.buffer;
    pat += (handle->psi.ccValue % NEXUS_SIMPLE_ENCODER_PSI_QUEUE_CNT) * PAT_PMT_PAIR_SIZE;
    pmt = pat+BTST_TS_HEADER_BUF_LENGTH;

    BKNI_Memset(psi, 0, sizeof(psi));
    psi[0].size = 188;
    psi[0].pData = pat+1;
    psi[0].timestampDelta = 0;
    psi[1].size = 188;
    psi[1].pData = pmt+1;
    psi[1].timestampDelta = 0;

    pat[4] = (pat[4] & 0xf0) | (handle->psi.ccValue & 0xf);
    NEXUS_Memory_FlushCache(&pat[4], 1);

    pmt[4] = (pmt[4] & 0xf0) | (handle->psi.ccValue & 0xf);
    NEXUS_Memory_FlushCache(&pmt[4], 1);

    NEXUS_StreamMux_AddSystemDataBuffer(handle->serverSettings.streamMux, &psi[0]);
    NEXUS_StreamMux_AddSystemDataBuffer(handle->serverSettings.streamMux, &psi[1]);
    BDBG_MSG(("%p: insert PSI ccPAT=%x ccPMT=%x", (void *)handle, pat[4]&0xf, pmt[4]&0xf));

    ++handle->psi.ccValue;
    handle->psi.timer = NEXUS_ScheduleTimer(handle->startSettings.output.transport.interval, nexus_simpleencoder_p_psi_timer, handle);
}

static NEXUS_Error nexus_simpleencoder_p_start_psi( NEXUS_SimpleEncoderHandle handle )
{
    uint8_t pat_pl_buf[BTST_TS_HEADER_BUF_LENGTH], pmt_pl_buf[BTST_TS_HEADER_BUF_LENGTH];
    size_t pat_pl_size, pmt_pl_size;
    unsigned streamNum;
    TS_PAT_state patState;
    TS_PSI_header psi_header;
    TS_PMT_state pmtState;
    TS_PAT_program program;
    TS_PMT_stream pmt_stream;
    uint8_t *pat, *pmt;
    int rc;
    unsigned i;

    /* if no pmtPid, then no PSI */
    if (!handle->startSettings.output.transport.pmtPid) {
        return 0;
    }

    /* == CREATE PSI TABLES == */
    TS_PSI_header_Init(&psi_header);
    TS_PAT_Init(&patState, &psi_header, pat_pl_buf, BTST_TS_HEADER_BUF_LENGTH);

    TS_PAT_program_Init(&program, 1, handle->startSettings.output.transport.pmtPid);
    TS_PAT_addProgram(&patState, &pmtState, &program, pmt_pl_buf, BTST_TS_HEADER_BUF_LENGTH);

    TS_PMT_setPcrPid(&pmtState, handle->startSettings.output.transport.pcrPid);

    if (handle->videoStarted) {
        unsigned vidStreamType;
        switch(handle->startSettings.output.video.settings.codec) {
        case NEXUS_VideoCodec_eMpeg2:         vidStreamType = 0x2; break;
        case NEXUS_VideoCodec_eMpeg4Part2:    vidStreamType = 0x10; break;
        case NEXUS_VideoCodec_eH264:          vidStreamType = 0x1b; break;
        case NEXUS_VideoCodec_eVc1SimpleMain: vidStreamType = 0xea; break;
        default:
            BDBG_ERR(("Video encoder codec %d is not supported!", handle->startSettings.output.video.settings.codec));
            return BERR_TRACE(NEXUS_NOT_SUPPORTED);
        }
        TS_PMT_stream_Init(&pmt_stream, vidStreamType, handle->startSettings.output.video.pid);
        TS_PMT_addStream(&pmtState, &pmt_stream, &streamNum);
    }

    if (handle->audioStarted) {
        unsigned audStreamType;
        switch(handle->startSettings.output.audio.codec) {
        case NEXUS_AudioCodec_eMpeg:         audStreamType = 0x4; break;
        case NEXUS_AudioCodec_eMp3:          audStreamType = 0x4; break;
        case NEXUS_AudioCodec_eAac:          audStreamType = 0xf; break; /* ADTS */
        case NEXUS_AudioCodec_eAacPlus:      audStreamType = 0x11; break;/* LOAS */
        /* MP2TS doesn't allow 14496-3 AAC+ADTS; here is placeholder to test AAC-HE before LOAS encode is supported; */
        case NEXUS_AudioCodec_eAacPlusAdts:  audStreamType = 0x11; break;
        case NEXUS_AudioCodec_eAc3:          audStreamType = 0x81; break;
        case NEXUS_AudioCodec_eLpcm1394:     audStreamType = 0x83; break;
        default:
            BDBG_ERR(("Audio encoder codec %d is not supported!", handle->startSettings.output.audio.codec));
            return BERR_TRACE(NEXUS_NOT_SUPPORTED);
        }

        TS_PMT_stream_Init(&pmt_stream, audStreamType, handle->startSettings.output.audio.pid);
        TS_PMT_addStream(&pmtState, &pmt_stream, &streamNum);
    }

    TS_PAT_finalize(&patState, &pat_pl_size);
    TS_PMT_finalize(&pmtState, &pmt_pl_size);

#if 0
    BDBG_MSG(("%p: PMT section:", handle));
    for(i=0; i<pmtState.size; i+=8) {
        BDBG_MSG(("%02x %02x %02x %02x %02x %02x %02x %02x", pmtState.buf[i], pmtState.buf[i+1], pmtState.buf[i+2], pmtState.buf[i+3],
            pmtState.buf[i+4], pmtState.buf[i+5], pmtState.buf[i+6], pmtState.buf[i+7]));
    }
#endif

#define PSI_BUFFER_SIZE (PAT_PMT_PAIR_SIZE*NEXUS_SIMPLE_ENCODER_PSI_QUEUE_CNT)

    handle->psi.block = NEXUS_MemoryBlock_Allocate(g_pCoreHandles->heap[g_pCoreHandles->defaultHeapIndex].nexus, PSI_BUFFER_SIZE, 0, NULL);
    if (!handle->psi.block) return BERR_TRACE(NEXUS_OUT_OF_DEVICE_MEMORY);
    rc = NEXUS_MemoryBlock_Lock(handle->psi.block, &handle->psi.buffer);
    if (rc) return BERR_TRACE(rc);

    pat = handle->psi.buffer;
    pmt = pat+BTST_TS_HEADER_BUF_LENGTH;

    /* == CREATE TS HEADERS FOR PSI INFORMATION == */
    /* Some Miracast client cannot handle AF in PSI transport packet */
    /* 1-byte offset at beggining for BTST_TS_HEADER_BUF_LENGTH */
    pat[1] = 0x47;
    pat[2] = 0x40; /* TEI = 0, Payload Unit Start = 1, Transport Priority = 0, 13 bit-pid# = 0 */
    pat[3] = 0x00;
    pat[4] = 0x10; /* scrambling = 0, adaptation field = 0, continuity counter = 0 */
    pat[5] = 0x00; /* pointer = 0 */
    BDBG_ASSERT(pat_pl_size <= BTST_TS_HEADER_BUF_LENGTH - 6); /* one packet PAT */
    BKNI_Memset(pat + 6, 0xff, BTST_TS_HEADER_BUF_LENGTH - 6); /* stuffing bytes */
    BKNI_Memcpy(pat + 6, pat_pl_buf, pat_pl_size); /* PAT table followed by stuffing bytes */

    /* Some Miracast client cannot handle AF in PSI transport packet */
    /* 1-byte offset at beggining for BTST_TS_HEADER_BUF_LENGTH */
    pmt[1] = 0x47;
    pmt[2] = 0x40 | ((handle->startSettings.output.transport.pmtPid >> 8) & 0x1f); /* TEI = 0, PUSI= 1, TP=0, 13-bit pid# */
    pmt[3] = handle->startSettings.output.transport.pmtPid & 0xff;
    pmt[4] = 0x10; /* scrambling = 0, AF = 0, continuity counter = 0 */
    pmt[5] = 0x00; /* pointer = 0 */
    BDBG_ASSERT(pmt_pl_size <= BTST_TS_HEADER_BUF_LENGTH - 6); /* one packet PMT */
    BKNI_Memset(pmt + 6, 0xff, BTST_TS_HEADER_BUF_LENGTH - 6); /* stuffing bytes */
    BKNI_Memcpy(pmt + 6, pmt_pl_buf, pmt_pl_size); /* PMT table followed by stuffing bytes */

#if 0
    BDBG_MSG(("%p: PMT packet:", handle));
    for(i=0; i < BTST_TS_HEADER_BUF_LENGTH; i+=8) {
        BDBG_MSG(("%02x %02x %02x %02x %02x %02x %02x %02x", *(pmt+i), *(pmt+i+1), *(pmt+i+2), *(pmt+i+3), *(pmt+i+4), *(pmt+i+5), *(pmt+i+6), *(pmt+i+7)));
    }
#endif

    /* copy from first to others */
    for (i=1;i<NEXUS_SIMPLE_ENCODER_PSI_QUEUE_CNT;i++) {
        BKNI_Memcpy((uint8_t*)handle->psi.buffer + PAT_PMT_PAIR_SIZE*i, handle->psi.buffer, PAT_PMT_PAIR_SIZE);
    }

    NEXUS_Memory_FlushCache(handle->psi.buffer, PSI_BUFFER_SIZE);

    handle->psi.ccValue = 0;
    nexus_simpleencoder_p_psi_timer(handle);

    return 0;
}

static void nexus_simpleencoder_p_stop_psi( NEXUS_SimpleEncoderHandle handle )
{
    if (handle->psi.timer) {
        NEXUS_CancelTimer(handle->psi.timer);
        handle->psi.timer = NULL;
    }
    if (handle->psi.block) {
        NEXUS_MemoryBlock_Free(handle->psi.block);
        handle->psi.block = NULL;
        handle->psi.buffer = NULL;
    }
}
#else
static NEXUS_Error nexus_simpleencoder_p_start( NEXUS_SimpleEncoderHandle handle )
{
    BDBG_OBJECT_ASSERT(handle, NEXUS_SimpleEncoder);
    return BERR_TRACE(NEXUS_NOT_SUPPORTED);
}

void nexus_simpleencoder_p_stop( NEXUS_SimpleEncoderHandle handle )
{
    BDBG_OBJECT_ASSERT(handle, NEXUS_SimpleEncoder);
}
#endif

/**
Summary:
Get a video encoder buffer if outputting to memory
**/
NEXUS_Error NEXUS_SimpleEncoder_GetVideoBuffer(
    NEXUS_SimpleEncoderHandle handle,
    const NEXUS_VideoEncoderDescriptor **pBuffer, /* [out] attr{memory=cached} pointer to NEXUS_VideoEncoderDescriptor structs */
    size_t *pSize, /* [out] number of NEXUS_VideoEncoderDescriptor elements in pBuffer */
    const NEXUS_VideoEncoderDescriptor **pBuffer2, /* [out] attr{memory=cached} pointer to NEXUS_VideoEncoderDescriptor structs after wrap around */
    size_t *pSize2 /* [out] number of NEXUS_VideoEncoderDescriptor elements in pBuffer2 */
    )
{
    BDBG_OBJECT_ASSERT(handle, NEXUS_SimpleEncoder);
#if NEXUS_HAS_STREAM_MUX
    if ( handle->serverSettings.videoEncoder)
    {
        return NEXUS_VideoEncoder_GetBuffer(handle->serverSettings.videoEncoder, pBuffer, pSize, pBuffer2, pSize2);
    }
    else
    {
        return BERR_NOT_SUPPORTED;
    }
#else
    BSTD_UNUSED(pBuffer);
    BSTD_UNUSED(pBuffer2);
    BSTD_UNUSED(pSize);
    BSTD_UNUSED(pSize2);
    return BERR_TRACE(BERR_NOT_SUPPORTED);
#endif
}

/**
Summary:
Return a video encoder buffer if outputting to memory
**/
NEXUS_Error NEXUS_SimpleEncoder_VideoReadComplete(
    NEXUS_SimpleEncoderHandle handle,
    unsigned descriptorsCompleted /* must be <= pSize+pSize2 returned by last NEXUS_SimpleEncoder_GetVideoBuffer call. */
    )
{
    BDBG_OBJECT_ASSERT(handle, NEXUS_SimpleEncoder);
#if NEXUS_HAS_STREAM_MUX
    if ( handle->serverSettings.videoEncoder)
    {
        return NEXUS_VideoEncoder_ReadComplete(handle->serverSettings.videoEncoder, descriptorsCompleted);
    }
    else
    {
        return BERR_NOT_SUPPORTED;
    }
#else
    BSTD_UNUSED(descriptorsCompleted);
    return BERR_TRACE(BERR_NOT_SUPPORTED);
#endif
}

/**
Summary:
Get an audio encoder buffer if outputting to memory
**/
NEXUS_Error NEXUS_SimpleEncoder_GetAudioBuffer(
    NEXUS_SimpleEncoderHandle handle,
    const NEXUS_AudioMuxOutputFrame **pBuffer, /* [out] attr{memory=cached} pointer to NEXUS_AudioMuxOutputFrame structs */
    size_t *pSize, /* [out] number of NEXUS_AudioMuxOutputFrame elements in pBuffer */
    const NEXUS_AudioMuxOutputFrame **pBuffer2, /* [out] attr{memory=cached} pointer to NEXUS_AudioMuxOutputFrame structs after wrap around */
    size_t *pSize2 /* [out] number of NEXUS_AudioMuxOutputFrame elements in pBuffer2 */
    )
{
    BDBG_OBJECT_ASSERT(handle, NEXUS_SimpleEncoder);
#if NEXUS_HAS_AUDIO
    if ( handle->serverSettings.audioMuxOutput)
    {
        return NEXUS_AudioMuxOutput_GetBuffer(handle->serverSettings.audioMuxOutput, pBuffer, pSize, pBuffer2, pSize2);
    }
    else
    {
        return BERR_NOT_SUPPORTED;
    }
#else
    BSTD_UNUSED(pBuffer);
    BSTD_UNUSED(pBuffer2);
    BSTD_UNUSED(pSize);
    BSTD_UNUSED(pSize2);
    return BERR_TRACE(BERR_NOT_SUPPORTED);
#endif
}

/**
Summary:
Return an audio encoder buffer if outputting to memory
**/
NEXUS_Error NEXUS_SimpleEncoder_AudioReadComplete(
    NEXUS_SimpleEncoderHandle handle,
    unsigned descriptorsCompleted /* must be <= pSize+pSize2 returned by last NEXUS_SimpleEncoder_GetAudioBuffer call. */
    )
{
    BDBG_OBJECT_ASSERT(handle, NEXUS_SimpleEncoder);
#if NEXUS_HAS_AUDIO
    if ( handle->serverSettings.audioMuxOutput )
    {
        return NEXUS_AudioMuxOutput_ReadComplete(handle->serverSettings.audioMuxOutput, descriptorsCompleted);
    }
    else
    {
        return BERR_NOT_SUPPORTED;
    }
#else
    BSTD_UNUSED(descriptorsCompleted);
    return BERR_TRACE(BERR_NOT_SUPPORTED);
#endif
}

/**
Summary:
**/
void NEXUS_SimpleEncoder_GetStatus(
    NEXUS_SimpleEncoderHandle handle,
    NEXUS_SimpleEncoderStatus *pStatus /* [out] */
    )
{
    BDBG_OBJECT_ASSERT(handle, NEXUS_SimpleEncoder);
    BKNI_Memset(pStatus, 0, sizeof(*pStatus));
#if NEXUS_HAS_STREAM_MUX
    if ( handle->serverSettings.videoEncoder )
    {
        BDBG_CASSERT(sizeof(pStatus->video) == sizeof(NEXUS_VideoEncoderStatus));
        NEXUS_VideoEncoder_GetStatus(handle->serverSettings.videoEncoder, (NEXUS_VideoEncoderStatus *)&pStatus->video);
        pStatus->videoEncoder.enabled = true;
        pStatus->videoEncoder.index = NEXUS_VideoEncoder_GetIndex_isrsafe(handle->serverSettings.videoEncoder);
    }
#endif
#if NEXUS_HAS_AUDIO
    if ( handle->serverSettings.audioMuxOutput )
    {
        BDBG_CASSERT(sizeof(pStatus->audio) == sizeof(NEXUS_AudioMuxOutputStatus));
        NEXUS_AudioMuxOutput_GetStatus(handle->serverSettings.audioMuxOutput, (NEXUS_AudioMuxOutputStatus *)(char *)&pStatus->audio);
    }
#endif
}

BDBG_FILE_MODULE(nexus_simple_decoder_proc);

void NEXUS_SimpleDecoderModule_P_PrintEncoder(void)
{
#if BDBG_DEBUG_BUILD
    NEXUS_SimpleEncoderHandle handle;

    for (handle=BLST_S_FIRST(&g_encoders); handle; handle = BLST_S_NEXT(handle, link)) {
        BDBG_MODULE_LOG(nexus_simple_decoder_proc, ("encode %u(%p)", handle->index, (void *)handle));
        BDBG_MODULE_LOG(nexus_simple_decoder_proc, ("  acquired %d, started %d, clientStarted %d",
            handle->acquired, handle->started, handle->clientStarted));
        BDBG_MODULE_LOG(nexus_simple_decoder_proc, ("  display %p, main display %p, audioMuxOutput %p, videoEncoder %p, streamMux %p, stcChannel %p",
            (void *)handle->serverSettings.transcodeDisplay,
            (void *)handle->serverSettings.displayEncode.display,
            (void *)handle->serverSettings.audioMuxOutput,
            (void *)handle->serverSettings.videoEncoder,
            (void *)handle->serverSettings.streamMux,
            (void *)handle->serverSettings.stcChannelTranscode));
    }
#endif
}

bool nexus_simpleencoder_p_nonRealTime(NEXUS_SimpleEncoderHandle encoder)
{
    return encoder && encoder->serverSettings.nonRealTime;
}

void NEXUS_SimpleEncoder_GetStcStatus_priv(NEXUS_SimpleEncoderHandle encoder, NEXUS_SimpleStcChannelEncoderStatus *pStatus)
{
    BKNI_Memset(pStatus, 0, sizeof(*pStatus));
    if (encoder) {
        pStatus->enabled = true;
        pStatus->timebase = encoder->serverSettings.timebase;
        pStatus->nonRealTime = encoder->serverSettings.nonRealTime;
    }
}

NEXUS_Error NEXUS_SimpleEncoder_GetCrcData( NEXUS_SimpleEncoderHandle handle, NEXUS_DisplayCrcData *pEntries, unsigned numEntries, unsigned *pNumReturned )
{
    NEXUS_DisplaySettings settings;
    int rc;
    if (!handle->serverSettings.transcodeDisplay) {
        return BERR_TRACE(NEXUS_NOT_AVAILABLE);
    }
    NEXUS_Display_GetSettings(handle->serverSettings.transcodeDisplay, &settings);
    if (settings.crcQueueSize == 0) {
        settings.crcQueueSize = 128;
        rc = NEXUS_Display_SetSettings(handle->serverSettings.transcodeDisplay, &settings);
        if (rc) return BERR_TRACE(rc);
    }
    return NEXUS_Display_GetCrcData(handle->serverSettings.transcodeDisplay, pEntries, numEntries, pNumReturned);
}

NEXUS_Error NEXUS_SimpleEncoder_InsertRandomAccessPoint( NEXUS_SimpleEncoderHandle handle )
{
    BDBG_OBJECT_ASSERT(handle, NEXUS_SimpleEncoder);
#if NEXUS_HAS_STREAM_MUX
    if (handle->serverSettings.videoEncoder) {
        return NEXUS_VideoEncoder_InsertRandomAccessPoint(handle->serverSettings.videoEncoder);
    }
#endif
    return BERR_TRACE(BERR_NOT_AVAILABLE);
}

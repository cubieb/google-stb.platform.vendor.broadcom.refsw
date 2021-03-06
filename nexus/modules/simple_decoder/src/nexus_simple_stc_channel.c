/***************************************************************************
 *     (c)2010-2013 Broadcom Corporation
 *
 *  This program is the proprietary software of Broadcom Corporation and/or its licensors,
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
 *
 * $brcm_Workfile: $
 * $brcm_Revision: $
 * $brcm_Date: $
 *
 * Module Description:
 *
 * Revision History:
 *
 * $brcm_Log: $
 *
 **************************************************************************/
#include "nexus_simple_decoder_module.h"
#include "nexus_simple_decoder_impl.h"
#include "priv/nexus_stc_channel_priv.h"
#include "priv/nexus_pid_channel_priv.h"
#include "nexus_platform_features.h" /* for NEXUS_NUM_VIDEO_WINDOWS */
#include "nexus_transport_capabilities.h"
#if NEXUS_HAS_ASTM
#include "nexus_astm.h"
#include "blst_queue.h"
#endif
#if NEXUS_HAS_SYNC_CHANNEL
#include "nexus_sync_channel.h"
#include "priv/nexus_sync_channel_priv.h"
#include "blst_queue.h"
#endif
#include "nexus_client_resources.h"

BDBG_MODULE(nexus_simple_stc_channel);

static NEXUS_Error NEXUS_SimpleStcChannel_P_SetSettings(NEXUS_SimpleStcChannelHandle handle, NEXUS_StcChannelHandle stcChannel, const NEXUS_SimpleStcChannelSettings *pSettings);

#if NEXUS_HAS_SYNC_CHANNEL
typedef struct NEXUS_AudioInputQueueEntry
{
    BLST_Q_ENTRY(NEXUS_AudioInputQueueEntry) link;
    NEXUS_AudioInput audioInput;
} NEXUS_AudioInputQueueEntry;
#endif

#if NEXUS_HAS_ASTM
typedef struct NEXUS_AudioDecoderQueueEntry
{
    BLST_Q_ENTRY(NEXUS_AudioDecoderQueueEntry) link;
    NEXUS_AudioDecoderHandle audioDecoder;
} NEXUS_AudioDecoderQueueEntry;
#endif

struct NEXUS_SimpleStcChannel
{
    NEXUS_OBJECT(NEXUS_SimpleStcChannel);
    NEXUS_SimpleStcChannelSettings settings;
    struct {
        uint32_t stc;
        bool frozen;
        unsigned increment, prescale;
    } state;
    NEXUS_StcChannelHandle stcChannel; /* video and (other than non-realtime transcode) audio stc */
    NEXUS_StcChannelHandle stcChannelAudio; /* audio stc if non-realtime transcode */
    NEXUS_SimpleVideoDecoderHandle video; /* used by astm and sync on start */
    NEXUS_SimpleAudioDecoderHandle audio; /* used by astm and sync on start */
#if NEXUS_HAS_ASTM
    struct {
        bool enabled;
        NEXUS_AstmHandle handle;
        BLST_Q_HEAD(NEXUS_FreeAudioDecoderQueue, NEXUS_AudioDecoderQueueEntry) freeAudioDecoderEntries;
        BLST_Q_HEAD(NEXUS_ConnectedAudioDecoderQueue, NEXUS_AudioDecoderQueueEntry) connectedAudioDecoders;
    } astm;
#endif
#if NEXUS_HAS_SYNC_CHANNEL
    struct {
        bool enabled;
        NEXUS_SyncChannelHandle handle;
        BLST_Q_HEAD(NEXUS_FreeAudioInputQueue, NEXUS_AudioInputQueueEntry) freeAudioInputEntries;
        BLST_Q_HEAD(NEXUS_ConnectedAudioInputQueue, NEXUS_AudioInputQueueEntry) connectedAudioInputs;
    } sync;
#endif
};

static NEXUS_SimpleStcChannelSettings g_default_settings;

void NEXUS_SimpleStcChannel_GetDefaultSettings( NEXUS_SimpleStcChannelSettings *pSettings )
{
    static bool set = false;
    if (!set) {
        NEXUS_StcChannelSettings s;
        NEXUS_StcChannel_GetDefaultSettings(0, &s);
        BKNI_Memset(&g_default_settings, 0, sizeof(g_default_settings));
        g_default_settings.mode = NEXUS_StcChannelMode_eAuto;
        g_default_settings.modeSettings.highJitter.mode = NEXUS_SimpleStcChannelHighJitterMode_eNone;
        g_default_settings.modeSettings.highJitter.threshold = 300; /* support max jitter of 300msec */
        g_default_settings.modeSettings.pcr = s.modeSettings.pcr;
        g_default_settings.modeSettings.Auto = s.modeSettings.Auto;
        g_default_settings.modeSettings.host = s.modeSettings.host;
        g_default_settings.sync = NEXUS_SimpleStcChannelSyncMode_eDefaultAdjustmentConcealment;
        set = true;
    }
    *pSettings = g_default_settings;
}

#if NEXUS_HAS_ASTM
static NEXUS_Error set_astm_control(NEXUS_SimpleStcChannelHandle handle, bool enabled)
{
    NEXUS_Error rc = NEXUS_SUCCESS;
    NEXUS_AstmSettings settings;

    NEXUS_OBJECT_ASSERT(NEXUS_SimpleStcChannel, handle);

    NEXUS_Astm_GetSettings(handle->astm.handle, &settings);
    settings.enabled = enabled;
    rc = NEXUS_Astm_SetSettings(handle->astm.handle, &settings);

    return rc;
}

static NEXUS_Error set_astm_stc(NEXUS_SimpleStcChannelHandle handle, NEXUS_StcChannelHandle stcChannel)
{
    NEXUS_Error rc = NEXUS_SUCCESS;
    NEXUS_AstmSettings settings;

    NEXUS_OBJECT_ASSERT(NEXUS_SimpleStcChannel, handle);

    NEXUS_Astm_GetSettings(handle->astm.handle, &settings);
    settings.stcChannel = stcChannel;
    rc = NEXUS_Astm_SetSettings(handle->astm.handle, &settings);

    return rc;
}

static void create_astm(NEXUS_SimpleStcChannelHandle handle)
{
    unsigned i = 0;
    NEXUS_AudioDecoderQueueEntry *pEntry = NULL;
    NEXUS_AstmSettings settings;

    /* disabled by default */
    handle->astm.enabled = false;

    NEXUS_Astm_GetDefaultSettings(&settings);
    settings.enableAutomaticLifecycleControl = true;
    settings.enabled = handle->astm.enabled;
    handle->astm.handle = NEXUS_Astm_Create(&settings);
    if (!handle->astm.handle)
    {
        BDBG_WRN(("Could not create ASTM instance. ASTM is disabled for stc channel %p", (void *)handle));
        return;
    }
    BLST_Q_INIT(&handle->astm.freeAudioDecoderEntries);
    BLST_Q_INIT(&handle->astm.connectedAudioDecoders);

    for (i = 0; i < NEXUS_ASTM_AUDIO_DECODERS; i++)
    {
        pEntry = BKNI_Malloc(sizeof(NEXUS_AudioDecoderQueueEntry));
        if (pEntry)
        {
            BKNI_Memset(pEntry, 0, sizeof(NEXUS_AudioDecoderQueueEntry));
            BLST_Q_INSERT_HEAD(&handle->astm.freeAudioDecoderEntries, pEntry, link);
        }
        else
        {
            BDBG_WRN(("Memory constrains ASTM to supporting %d audio decoders", i));
            break;
        }
    }
}
static void destroy_astm(NEXUS_SimpleStcChannelHandle handle)
{
    NEXUS_AudioDecoderQueueEntry *pEntry = NULL;

    if (handle->astm.handle)
    {
        NEXUS_AstmSettings settings;
        /*
         * need to explicitly clear handles here because Destroy
         * doesn't do a blocking call on finalize
         */
        NEXUS_Astm_GetSettings(handle->astm.handle, &settings);
        settings.stcChannel = NULL;
        settings.videoDecoder = NULL;
        settings.audioDecoder[0] = NULL;
        settings.audioDecoder[1] = NULL;
        (void)NEXUS_Astm_SetSettings(handle->astm.handle, &settings);

        NEXUS_Astm_Destroy(handle->astm.handle);
    }

    for (pEntry = BLST_Q_FIRST(&handle->astm.connectedAudioDecoders); pEntry; pEntry = BLST_Q_FIRST(&handle->astm.connectedAudioDecoders))
    {
        BLST_Q_REMOVE_HEAD(&handle->astm.connectedAudioDecoders, link);
        BKNI_Free(pEntry);
    }

    for (pEntry = BLST_Q_FIRST(&handle->astm.freeAudioDecoderEntries); pEntry; pEntry = BLST_Q_FIRST(&handle->astm.freeAudioDecoderEntries))
    {
        BLST_Q_REMOVE_HEAD(&handle->astm.freeAudioDecoderEntries, link);
        BKNI_Free(pEntry);
    }
}
#endif

static NEXUS_Error set_sync_mode(NEXUS_SimpleStcChannelHandle handle, NEXUS_SimpleStcChannelSyncMode sync)
{
    NEXUS_Error rc = NEXUS_SUCCESS;
    NEXUS_SyncChannelSettings settings;

    NEXUS_OBJECT_ASSERT(NEXUS_SimpleStcChannel, handle);

    NEXUS_SyncChannel_GetSettings(handle->sync.handle, &settings);
    switch (sync)
    {
        case NEXUS_SimpleStcChannelSyncMode_eNoAdjustmentConcealment:
        case NEXUS_SimpleStcChannelSyncMode_eAudioAdjustmentConcealment:
            settings.enableMuteControl = false;
            break;
        default:
            settings.enableMuteControl = true;
            break;
    }
    rc = NEXUS_SyncChannel_SetSettings(handle->sync.handle, &settings);
    if (rc) BERR_TRACE(rc);

    return rc;
}

#if NEXUS_HAS_SYNC_CHANNEL
static void create_sync(NEXUS_SimpleStcChannelHandle handle)
{
    unsigned i = 0;
    NEXUS_AudioInputQueueEntry *pEntry = NULL;

    /* enabled by default */
    handle->sync.enabled = true;

    handle->sync.handle = NEXUS_SyncChannel_Create(NULL);
    if (!handle->sync.handle)
    {
        BDBG_WRN(("Could not create SyncChannel instance. SyncChannel is disabled for stc channel %p", (void *)handle));
        return;
    }
    BLST_Q_INIT(&handle->sync.freeAudioInputEntries);
    BLST_Q_INIT(&handle->sync.connectedAudioInputs);

    for (i = 0; i < NEXUS_SYNC_CHANNEL_NUM_AUDIO_INPUTS; i++)
    {
        pEntry = BKNI_Malloc(sizeof(NEXUS_AudioInputQueueEntry));
        if (pEntry)
        {
            BKNI_Memset(pEntry, 0, sizeof(NEXUS_AudioInputQueueEntry));
            BLST_Q_INSERT_HEAD(&handle->sync.freeAudioInputEntries, pEntry, link);
        }
        else
        {
            BDBG_WRN(("Memory constrains SyncChannel to supporting %d audio decoders", i));
            break;
        }
    }
    set_sync_mode(handle, handle->settings.sync);
}
static void destroy_sync(NEXUS_SimpleStcChannelHandle handle)
{
    NEXUS_AudioInputQueueEntry *pEntry = NULL;

    if (handle->sync.handle)
    {
        NEXUS_SyncChannelSettings settings;
        /*
         * need to explicitly clear handles here because Destroy
         * doesn't do a blocking call on finalize
         */
        NEXUS_SyncChannel_GetSettings(handle->sync.handle, &settings);
        settings.videoInput = NULL;
        settings.audioInput[0] = NULL;
        settings.audioInput[1] = NULL;
        (void)NEXUS_SyncChannel_SetSettings(handle->sync.handle, &settings);
        NEXUS_SyncChannel_Destroy(handle->sync.handle);
    }

    for (pEntry = BLST_Q_FIRST(&handle->sync.connectedAudioInputs); pEntry; pEntry = BLST_Q_FIRST(&handle->sync.connectedAudioInputs))
    {
        BLST_Q_REMOVE_HEAD(&handle->sync.connectedAudioInputs, link);
        BKNI_Free(pEntry);
    }

    for (pEntry = BLST_Q_FIRST(&handle->sync.freeAudioInputEntries); pEntry; pEntry = BLST_Q_FIRST(&handle->sync.freeAudioInputEntries))
    {
        BLST_Q_REMOVE_HEAD(&handle->sync.freeAudioInputEntries, link);
        BKNI_Free(pEntry);
    }
}
#endif

static NEXUS_Error validateSettings(const NEXUS_SimpleStcChannelSettings *pSettings)
{
    if (pSettings->mode == NEXUS_StcChannelMode_ePcr) {
        if (NULL == pSettings->modeSettings.pcr.pidChannel) {
            return BERR_TRACE(NEXUS_INVALID_PARAMETER);
        }
    }
    else if (pSettings->modeSettings.pcr.pidChannel) {
        /* don't fail. it will be unused, so we don't ACQUIRE/RELEASE either. */
    }
    return 0;
}

/* do acquire/release on any resource stored in handle->settings */
static void doSettingsAccounting(NEXUS_SimpleStcChannelHandle handle, const NEXUS_SimpleStcChannelSettings *pSettings)
{
    NEXUS_PidChannelHandle acq;
    NEXUS_PidChannelHandle rel;

    if (pSettings && pSettings->mode == NEXUS_StcChannelMode_ePcr) {
        acq = pSettings->modeSettings.pcr.pidChannel;
    }
    else {
        acq = NULL;
    }
    if (handle->settings.mode == NEXUS_StcChannelMode_ePcr) {
        rel = handle->settings.modeSettings.pcr.pidChannel;
    }
    else {
        rel = NULL;
    }
    if (acq != rel) {
        if (rel) {
            NEXUS_OBJECT_RELEASE(handle, NEXUS_PidChannel, rel);
        }
        if (acq) {
            NEXUS_OBJECT_ACQUIRE(handle, NEXUS_PidChannel, acq);
        }
    }
}

NEXUS_SimpleStcChannelHandle NEXUS_SimpleStcChannel_Create(const NEXUS_SimpleStcChannelSettings *pSettings )
{
    NEXUS_SimpleStcChannelHandle handle;
    int rc;

    if (pSettings && validateSettings(pSettings)) {
        return NULL;
    }

    rc = NEXUS_CLIENT_RESOURCES_ACQUIRE(simpleStcChannel,Count,NEXUS_ANY_ID);
    if (rc) { rc = BERR_TRACE(rc); return NULL; }

    handle = BKNI_Malloc(sizeof(*handle));
    if (!handle) {
        BERR_TRACE(NEXUS_OUT_OF_SYSTEM_MEMORY);
        NEXUS_CLIENT_RESOURCES_RELEASE(simpleStcChannel,Count,NEXUS_ANY_ID);
        return NULL;
    }
    NEXUS_OBJECT_INIT(NEXUS_SimpleStcChannel, handle);
    handle->state.increment = 0x1;
    if (pSettings) {
        doSettingsAccounting(handle, pSettings);
        handle->settings = *pSettings;
    }
    else {
        NEXUS_SimpleStcChannel_GetDefaultSettings(&handle->settings);
    }

#if NEXUS_HAS_ASTM
    create_astm(handle);
#endif
#if NEXUS_HAS_SYNC_CHANNEL
    create_sync(handle);
#endif

    return handle;
}

static void NEXUS_SimpleStcChannel_P_Release( NEXUS_SimpleStcChannelHandle handle )
{
    if (handle->stcChannel && handle->settings.mode != NEXUS_StcChannelMode_eAuto) {
        NEXUS_SimpleStcChannelSettings settings = handle->settings;
        settings.mode = NEXUS_StcChannelMode_eAuto;
        NEXUS_SimpleStcChannel_P_SetSettings(handle, handle->stcChannel, &settings);
    }
}

NEXUS_OBJECT_CLASS_MAKE_WITH_RELEASE(NEXUS_SimpleStcChannel, NEXUS_SimpleStcChannel_Destroy);

static void NEXUS_SimpleStcChannel_P_Finalizer( NEXUS_SimpleStcChannelHandle handle )
{
    NEXUS_SimpleStcChannelSettings settings;
    NEXUS_OBJECT_ASSERT(NEXUS_SimpleStcChannel, handle);

    /* ensure RELEASE is called */
    NEXUS_SimpleStcChannel_GetDefaultSettings(&settings);
    NEXUS_SimpleStcChannel_SetSettings(handle, &settings);

#if NEXUS_HAS_SYNC_CHANNEL
    destroy_sync(handle);
#endif

#if NEXUS_HAS_ASTM
    destroy_astm(handle);
#endif

    if (handle->stcChannel)
    {
        NEXUS_StcChannel_Close(handle->stcChannel);
        handle->stcChannel = NULL;
    }
    if (handle->stcChannelAudio)
    {
        NEXUS_StcChannel_Close(handle->stcChannelAudio);
        handle->stcChannelAudio = NULL;
    }

    NEXUS_CLIENT_RESOURCES_RELEASE(simpleStcChannel,Count,NEXUS_ANY_ID);
    NEXUS_OBJECT_DESTROY(NEXUS_SimpleStcChannel, handle);
    BKNI_Free(handle);
}

void NEXUS_SimpleStcChannel_GetSettings( NEXUS_SimpleStcChannelHandle handle, NEXUS_SimpleStcChannelSettings *pSettings )
{
    NEXUS_OBJECT_ASSERT(NEXUS_SimpleStcChannel, handle);
    *pSettings = handle->settings;
}

#if 0
/* commenting this out as we think default timese settings should be like this only: free-running */
/* TODO: take this code out once we verify the above assumption */
static void configureOutputTimebase(NEXUS_Timebase outputTimebase, NEXUS_TimebaseSettings *timebaseSettings)
{
    /* configure timebase to free-run */
    timebaseSettings->sourceType = NEXUS_TimebaseSourceType_eFreeRun;
    timebaseSettings->freeze = true;
    timebaseSettings->sourceSettings.pcr.trackRange = NEXUS_TimebaseTrackRange_e61ppm;
    BDBG_MSG(("Configured timebase %d for free-run", outputTimebase));
}
#endif

static void configureHighJitterTimebase(NEXUS_Timebase highJitterTimebase, const NEXUS_SimpleStcChannelSettings *pSettings, NEXUS_TimebaseSettings *timebaseSettings)
{
    /* program the timebase: increase its track range & max pcr errors */
    timebaseSettings->sourceType = NEXUS_TimebaseSourceType_ePcr;
    timebaseSettings->freeze = false;
    timebaseSettings->sourceSettings.pcr.pidChannel = pSettings->modeSettings.pcr.pidChannel;
    timebaseSettings->sourceSettings.pcr.maxPcrError = pSettings->modeSettings.highJitter.threshold * 183/2;    /* in milliseconds: based on 90Khz clock */
    timebaseSettings->sourceSettings.pcr.trackRange = NEXUS_TimebaseTrackRange_e244ppm;
    timebaseSettings->sourceSettings.pcr.jitterCorrection = NEXUS_TristateEnable_eDisable;
    BDBG_MSG(("Configured timebase %d for highJtter value of %d msec", highJitterTimebase, pSettings->modeSettings.highJitter.threshold));
}

static void configureHighJitterStc(NEXUS_Timebase highJitterTimebase, const NEXUS_SimpleStcChannelSettings *pSettings, NEXUS_StcChannelSettings *stcChannelSettings)
{
    /* Update STC Channel Settings to accomodate Network Jitter */
    stcChannelSettings->timebase = highJitterTimebase;
    stcChannelSettings->mode = NEXUS_StcChannelMode_ePcr; /* Live Mode */
    /* offset threshold: uses upper 32 bits (183ticks/msec) of PCR clock */
    stcChannelSettings->modeSettings.pcr.offsetThreshold = pSettings->modeSettings.highJitter.threshold * 183;
    /* max pcr error: uses upper 32 bits (183ticks/msec) of PCR clock */
    stcChannelSettings->modeSettings.pcr.maxPcrError =  pSettings->modeSettings.highJitter.threshold * 183;
    stcChannelSettings->modeSettings.pcr.pidChannel = pSettings->modeSettings.pcr.pidChannel;
    /*  PCR Offset "Jitter Adjustment" is not suitable for use with IP channels Channels, so disable it */
    stcChannelSettings->modeSettings.pcr.disableJitterAdjustment = true;
    /* Disable Auto Timestamp correction for PCR Jitter */
    stcChannelSettings->modeSettings.pcr.disableTimestampCorrection = true;
    /* We want to manually configure the Timebase, so turn off auto timebase config */
    stcChannelSettings->autoConfigTimebase = false;
    BDBG_MSG(("Configured stcChannel for highJtter value of %d msec", pSettings->modeSettings.highJitter.threshold));
}

static void printTimebaseSettings(NEXUS_Timebase timebase)
{
    NEXUS_TimebaseSettings timebaseSettings;
    NEXUS_Timebase_GetSettings(timebase, &timebaseSettings);
    BDBG_MSG(("timebase %d: source type %d, freeze %d, maxPcrError %d, trackRange %d, jitterCorrection %d",
                timebase,
                timebaseSettings.sourceType,
                timebaseSettings.freeze,
                timebaseSettings.sourceSettings.pcr.maxPcrError,
                timebaseSettings.sourceSettings.pcr.trackRange,
                timebaseSettings.sourceSettings.pcr.jitterCorrection));

}

static void printStcChannelSettings(NEXUS_SimpleStcChannelHandle handle)
{
    BDBG_MSG(("mode %d, highJitterMode %d, highJitterThreshold %d",
                handle->settings.mode,
                handle->settings.modeSettings.highJitter.mode,
                handle->settings.modeSettings.highJitter.threshold));
    if (handle->stcChannel) {
        NEXUS_StcChannelSettings stcChannelSettings;
        NEXUS_StcChannel_GetSettings(handle->stcChannel, &stcChannelSettings);
        BDBG_MSG(("stc: timebase %d, mode %d, offsetThreshold %d, maxPcrError %d disableJitterAdjustment %d disableTimestampCorrection %d, autoConfigTimebase %d",
                    stcChannelSettings.timebase,
                    stcChannelSettings.mode,
                    stcChannelSettings.modeSettings.pcr.offsetThreshold,
                    stcChannelSettings.modeSettings.pcr.maxPcrError,
                    stcChannelSettings.modeSettings.pcr.disableJitterAdjustment,
                    stcChannelSettings.modeSettings.pcr.disableTimestampCorrection,
                    stcChannelSettings.autoConfigTimebase
                    ));
    }
}


static NEXUS_Error NEXUS_SimpleStcChannel_P_GetEncoderTimebase(NEXUS_SimpleStcChannelHandle handle, NEXUS_Timebase *pTimebase)
{
    if (handle->video) {
        NEXUS_SimpleStcChannelDecoderStatus videoStatus;
        NEXUS_SimpleVideoDecoder_GetStcStatus_priv(handle->video, &videoStatus);
        if (videoStatus.connected && videoStatus.encoder.enabled) {
            *pTimebase = videoStatus.encoder.timebase;
            return 0;
        }
    }
    else if (handle->audio) {
        NEXUS_SimpleStcChannelDecoderStatus audioStatus;
        NEXUS_SimpleAudioDecoder_GetStcStatus_priv(handle->audio, &audioStatus);
        if (audioStatus.connected && audioStatus.encoder.enabled) {
            *pTimebase = audioStatus.encoder.timebase;
            return 0;
        }
    }
    return -1; /* not an error */
}

static NEXUS_Error NEXUS_SimpleStcChannel_P_SetSettings(NEXUS_SimpleStcChannelHandle handle, NEXUS_StcChannelHandle stcChannel, const NEXUS_SimpleStcChannelSettings *pSettings)
{
    NEXUS_StcChannelSettings settings;
    NEXUS_TimebaseSettings timebaseSettings;
    int rc;
    NEXUS_Timebase releaseTimebase = NEXUS_Timebase_eInvalid;
    bool manualTimebaseConfig = false;

    NEXUS_StcChannel_GetSettings(stcChannel, &settings);
    if (!settings.autoConfigTimebase) {
        /* if the last setting was manual, we need to unhook any pcr pid channel that was connected */
        releaseTimebase = settings.timebase;
    }

    settings.mode = pSettings->mode;
    settings.modeSettings.pcr = pSettings->modeSettings.pcr;
    settings.modeSettings.Auto = pSettings->modeSettings.Auto;
    settings.modeSettings.host = pSettings->modeSettings.host;
    settings.underflowHandling = pSettings->underflowHandling;

    if (!NEXUS_SimpleStcChannel_P_GetEncoderTimebase(handle, &settings.timebase)) {
        settings.mode = NEXUS_StcChannelMode_eAuto;
        /* TODO: do we or don't we want to autoConfig for this timebase? */
        goto set_settings;
    }

    if (handle->video) {
        NEXUS_SimpleStcChannelDecoderStatus videoStatus;
        NEXUS_SimpleVideoDecoder_GetStcStatus_priv(handle->video, &videoStatus);
        if (videoStatus.hdDviInput) {
            NEXUS_Timebase_GetSettings(settings.timebase, &timebaseSettings);
            timebaseSettings.sourceType = NEXUS_TimebaseSourceType_eHdDviIn;
            manualTimebaseConfig = true;
            goto set_settings;
        }
    }

    /* now customize the stcSettings based on the mode */
    switch (pSettings->mode) {
        case NEXUS_StcChannelMode_eAuto:
            /* DVR is freerun, so timebase is a don't care */
            settings.timebase = NEXUS_Timebase_eInvalid;
            /*
             * TODO: I think we don't want to autoconfig the default timebase,
             * but this just leaves it sticky from previous config
             */
            break;
        case NEXUS_StcChannelMode_ePcr:
            /* manage timebase through system-wide settings, not individual client control */
            switch (pSettings->modeSettings.highJitter.mode) {
                case NEXUS_SimpleStcChannelHighJitterMode_eNone:
                    /* no jitter on PCRs, so use same timebase for both AV decoders and display/audio outputs */
                    settings.timebase = NEXUS_Timebase_e0 + settings.stcIndex;
                    /* we want to auto config timebase for no-jitter pcr tracking */
                    settings.autoConfigTimebase = true;
                    break;
                case NEXUS_SimpleStcChannelHighJitterMode_eDirect:
                    /* jittered PCR packets are directly fed to transport,
                       so we can't use jittered timebase for display/audio outputs.
                       We use different timebase from display and audio outputs
                       NEXUS_NUM_VIDEO_WINDOWS is 2 for PIP systems, 1 for non-PIP systems.
                       So, for PIP systems, high jitter timebase is 2 and 3; for non-PIP, high jitter timebase is 1. */
                    if (pSettings->modeSettings.highJitter.threshold == 0) {
                        BDBG_ERR(("NEXUS SimpleStcChannelHighJitterMode_eDirect requires caller to specify non-zero highJitterThreshold"));
                        return NEXUS_INVALID_PARAMETER;
                    }
                    /* select the highJitter timebase */
                    settings.timebase = NEXUS_Timebase_e0 + NEXUS_NUM_VIDEO_WINDOWS + settings.stcIndex;
                    /* manually configure this timebase */
                    NEXUS_Timebase_GetSettings(settings.timebase, &timebaseSettings);
                    configureHighJitterTimebase(settings.timebase, pSettings, &timebaseSettings);
                    manualTimebaseConfig = true;
                    /* now configure the STC */
                    configureHighJitterStc(settings.timebase, pSettings, &settings);
                    break;
                default:
                    BDBG_ERR(("NEXUS SimpleStcChannelHighJitterMode_eDirect requires caller to specify non-zero highJitterThreshold"));
                    return NEXUS_INVALID_PARAMETER;
                    break;
            }
            break;
        default:
            break;
    }
set_settings:
    rc = NEXUS_StcChannel_SetSettings(stcChannel, &settings);
    if (rc) return BERR_TRACE(rc);
    if (manualTimebaseConfig)
    {
        /*
         * switching from autoconfig to manual config will reset the timebase
         * that was autoconfigd during the call to StcChannel_SetSettings.  This
         * will apply the manual timebase settings to the now-free timebase afterwards
         */
        rc = NEXUS_Timebase_SetSettings(settings.timebase, &timebaseSettings);
        if (rc) return BERR_TRACE(rc);
    }
    if (releaseTimebase != settings.timebase && releaseTimebase != NEXUS_Timebase_eInvalid) {
        /* and this unconfigures the old timebase we manually configured last time -- if different */
        NEXUS_Timebase_GetSettings(releaseTimebase, &timebaseSettings);
        timebaseSettings.sourceType = NEXUS_TimebaseSourceType_eFreeRun;
        NEXUS_Timebase_SetSettings(releaseTimebase, &timebaseSettings);
    }
    printTimebaseSettings(settings.timebase);
    return 0;
}

NEXUS_Error NEXUS_SimpleStcChannel_SetSettings( NEXUS_SimpleStcChannelHandle handle, const NEXUS_SimpleStcChannelSettings *pSettings )
{
    int rc;

    NEXUS_OBJECT_ASSERT(NEXUS_SimpleStcChannel, handle);
    rc = validateSettings(pSettings);
    if (rc) return BERR_TRACE(rc);

    if (handle->stcChannel) {
#if NEXUS_HAS_ASTM
        /* must disconnect from astm first, due to potential of losing timebase
         * or switching user stc modes
         */
        set_astm_stc(handle, NULL);
#endif
        rc = NEXUS_SimpleStcChannel_P_SetSettings(handle, handle->stcChannel, pSettings);
        if (rc) return BERR_TRACE(rc);
#if NEXUS_HAS_ASTM
        /* must reconnect to astm again */
        set_astm_stc(handle, handle->stcChannel);
#endif
        BDBG_MSG(("%p: apply %s mode to stcChannel %p", (void *)handle, pSettings->mode==NEXUS_StcChannelMode_ePcr?"pcr":"auto", (void *)handle->stcChannel));
        printStcChannelSettings(handle);
    }
    if (handle->stcChannelAudio) {
        rc = NEXUS_SimpleStcChannel_P_SetSettings(handle, handle->stcChannelAudio, pSettings);
        if (rc) return BERR_TRACE(rc);
    }

#if NEXUS_HAS_SYNC_CHANNEL
    handle->sync.enabled = (pSettings->sync > NEXUS_SimpleStcChannelSyncMode_eOff) && !NEXUS_GetEnv("sync_disabled") && !NEXUS_GetEnv("force_vsync");
    BDBG_MSG(("sync %s", handle->sync.enabled ? "enabled" : "disabled"));
    set_sync_mode(handle, pSettings->sync);
#endif
#if NEXUS_HAS_ASTM
    handle->astm.enabled = (pSettings->astm || NEXUS_GetEnv("astm_enabled")) && !NEXUS_GetEnv("force_vsync");
    BDBG_MSG(("ASTM %s", handle->astm.enabled ? "enabled" : "disabled"));
    set_astm_control(handle, handle->astm.enabled);
#endif

    /* must do after any use of pidChannel in case this releases it */
    doSettingsAccounting(handle, pSettings);
    handle->settings = *pSettings;
    return 0;
}

NEXUS_Error NEXUS_SimpleStcChannel_Invalidate( NEXUS_SimpleStcChannelHandle handle )
{
    NEXUS_OBJECT_ASSERT(NEXUS_SimpleStcChannel, handle);
    if (handle->stcChannel) {
        int rc = NEXUS_StcChannel_Invalidate(handle->stcChannel);
        if (rc) return BERR_TRACE(rc);
        handle->state.stc = 0xFAFAFAFA; /* invalid value */
    }
    if (handle->stcChannelAudio) {
        int rc = NEXUS_StcChannel_Invalidate(handle->stcChannelAudio);
        if (rc) return BERR_TRACE(rc);
    }
    return 0;
}

void NEXUS_SimpleStcChannel_GetStc( NEXUS_SimpleStcChannelHandle handle, uint32_t *pStc )
{
    NEXUS_OBJECT_ASSERT(NEXUS_SimpleStcChannel, handle);
    if (handle->stcChannel) {
        NEXUS_StcChannel_GetStc(handle->stcChannel, &handle->state.stc);
    }
    *pStc = handle->state.stc;
}

NEXUS_Error NEXUS_SimpleStcChannel_SetStc( NEXUS_SimpleStcChannelHandle handle, uint32_t stc )
{
    NEXUS_OBJECT_ASSERT(NEXUS_SimpleStcChannel, handle);
    if (handle->stcChannel) {
        int rc = NEXUS_StcChannel_SetStc(handle->stcChannel, stc);
        if (rc) return BERR_TRACE(rc);
    }
    /* not supported for stcChannelAudio */
    handle->state.stc = stc;
    return 0;
}

NEXUS_Error NEXUS_SimpleStcChannel_Freeze( NEXUS_SimpleStcChannelHandle handle, bool frozen )
{
    NEXUS_OBJECT_ASSERT(NEXUS_SimpleStcChannel, handle);
    if (handle->stcChannel) {
        int rc = NEXUS_StcChannel_Freeze(handle->stcChannel, frozen);
        if (rc) return BERR_TRACE(rc);
    }
    if (handle->stcChannelAudio) {
        int rc = NEXUS_StcChannel_Freeze(handle->stcChannelAudio, frozen);
        if (rc) return BERR_TRACE(rc);
    }
    handle->state.frozen = frozen;
    return 0;
}

NEXUS_Error NEXUS_SimpleStcChannel_SetRate( NEXUS_SimpleStcChannelHandle handle, unsigned increment, unsigned prescale )
{
    NEXUS_OBJECT_ASSERT(NEXUS_SimpleStcChannel, handle);
    if (handle->stcChannel) {
        int rc = NEXUS_StcChannel_SetRate(handle->stcChannel, increment, prescale);
        if (rc) return BERR_TRACE(rc);
    }
    if (handle->stcChannelAudio) {
        int rc = NEXUS_StcChannel_SetRate(handle->stcChannelAudio, increment, prescale);
        if (rc) return BERR_TRACE(rc);
    }
    handle->state.increment = increment;
    handle->state.prescale = prescale;
    return 0;
}

static NEXUS_Error apply_settings(NEXUS_SimpleStcChannelHandle handle)
{
    int rc = 0;

    NEXUS_OBJECT_ASSERT(NEXUS_SimpleStcChannel, handle);

    if (handle->stcChannel)
    {
        int temp_rc; /* last non-zero rc will be returned to caller, but all settings will be applied */

        temp_rc = NEXUS_SimpleStcChannel_Freeze(handle, handle->state.frozen);
        if (temp_rc) rc = BERR_TRACE(temp_rc);
        temp_rc = NEXUS_SimpleStcChannel_SetRate(handle, handle->state.increment, handle->state.prescale);
        if (temp_rc) rc = BERR_TRACE(temp_rc);
        rc = NEXUS_SimpleStcChannel_SetSettings(handle, &handle->settings);
        if (temp_rc) rc = BERR_TRACE(temp_rc);
        /* do not set handle->state.stc; instead, invalidate. */
        rc = NEXUS_SimpleStcChannel_Invalidate(handle);
        if (temp_rc) rc = BERR_TRACE(temp_rc);
    }

    return rc;
}

static void init_decoder_stc_status(NEXUS_SimpleStcChannelDecoderStatus * pStatus)
{
    if (pStatus)
    {
        BKNI_Memset(pStatus, 0, sizeof(NEXUS_SimpleStcChannelDecoderStatus));
        pStatus->stcIndex = -1;
    }
}

static int resolve_stc_index(NEXUS_SimpleStcChannelDecoderStatus * videoStatus, NEXUS_SimpleStcChannelDecoderStatus * audioStatus)
{
    int stcIndex = -1;

    if (videoStatus->connected && videoStatus->stcIndex != -1)
    {
        stcIndex = videoStatus->stcIndex;
    }
    else if (audioStatus->connected && audioStatus->stcIndex != -1)
    {
        stcIndex = audioStatus->stcIndex;
    }
    else if (videoStatus->primer)
    {
        /* primer test needs to be after video and audio connection tests as
         * we can have all conditions at the same time.
         * primer doesn't need a separate counter, so we use the default
         */
        stcIndex = 0;
    }
    else
    {
        BERR_TRACE(NEXUS_NOT_SUPPORTED);
    }

    return stcIndex;
}

static NEXUS_Error resolve_server_stc(NEXUS_SimpleStcChannelHandle handle)
{
    int rc = 0;
    bool change = false;
    NEXUS_SimpleStcChannelDecoderStatus videoStatus;
    NEXUS_SimpleStcChannelDecoderStatus audioStatus;
    NEXUS_StcChannelSettings settings;

    NEXUS_OBJECT_ASSERT(NEXUS_SimpleStcChannel, handle);

    init_decoder_stc_status(&videoStatus);
    init_decoder_stc_status(&audioStatus);

    if (handle->video) {
        NEXUS_SimpleVideoDecoder_GetStcStatus_priv(handle->video, &videoStatus);
    }

    if (handle->audio) {
        NEXUS_SimpleAudioDecoder_GetStcStatus_priv(handle->audio, &audioStatus);
    }

    BDBG_MSG(("%p: video %s:%s:%d; audio %s:%s:%d; primer:%s",
        (void *)handle,
        videoStatus.connected ? "connected" : "disconnected",
        videoStatus.started ? "started" : "stopped",
        videoStatus.stcIndex,
        audioStatus.connected ? "connected" : "disconnected",
        audioStatus.started ? "started" : "stopped",
        audioStatus.stcIndex,
        videoStatus.primer ? "priming" : "not priming"
        ));

    if (handle->stcChannel && handle->stcChannelAudio) {
        NEXUS_StcChannelPairSettings stcAudioVideoPair;
        NEXUS_StcChannel_GetDefaultPairSettings(&stcAudioVideoPair);
        stcAudioVideoPair.connected = false;
        NEXUS_StcChannel_SetPairSettings(handle->stcChannel, handle->stcChannelAudio, &stcAudioVideoPair);
    }

    /* non-realtime encoding requires stcChannelAudio */
    if (videoStatus.connected && audioStatus.connected
        && videoStatus.stcIndex >= 0 && audioStatus.stcIndex >= 0
        && videoStatus.stcIndex != audioStatus.stcIndex
        && videoStatus.encoder.nonRealTime)
    {
        if (!handle->stcChannelAudio) {
            NEXUS_StcChannel_GetDefaultSettings(0, &settings);
            settings.stcIndex = audioStatus.stcIndex;
            handle->stcChannelAudio = NEXUS_StcChannel_Open(NEXUS_ANY_ID, &settings);
            if (!handle->stcChannelAudio) { rc = BERR_TRACE(NEXUS_NOT_AVAILABLE); }
            BDBG_MSG(("%p open NRT audio %p: %d", (void *)handle, (void *)handle->stcChannelAudio, settings.stcIndex));
        }
    }
    else {
        if (handle->stcChannelAudio) {
            NEXUS_StcChannel_Close(handle->stcChannelAudio);
            BDBG_MSG(("%p close NRT audio %p", (void *)handle, (void *)handle->stcChannelAudio));
            handle->stcChannelAudio = NULL;
        }
    }

    if (videoStatus.connected || videoStatus.primer || audioStatus.connected)
    {
        bool autoConfigTimebase = (!videoStatus.primer && !videoStatus.hdDviInput);
        if (handle->stcChannel)
        {
            NEXUS_StcChannel_GetSettings(handle->stcChannel, &settings);

            BDBG_ASSERT(settings.stcIndex != -1);
            if (settings.stcIndex == -1)
            {
                BDBG_ERR(("An stc channel is attached to this simple stc channel, but has an invalid stc index"));
                rc = BERR_TRACE(NEXUS_NOT_SUPPORTED);
                goto error;
            }

            /*
             * stc channel already allocated, check stc index compatibility
             */
            if ((videoStatus.connected && videoStatus.stcIndex >= 0 && videoStatus.stcIndex != settings.stcIndex)
                ||
                (audioStatus.connected && audioStatus.stcIndex >= 0 && audioStatus.stcIndex != settings.stcIndex)
                ||
                (videoStatus.primer && settings.stcIndex != 0))
            {
                /*
                 * stcIndex cannot change after open on older platforms, and can't reopen stc channel
                 * if any decoders or primers are started
                 */
                if (!videoStatus.started && !videoStatus.primer && !audioStatus.started)
                {
                    /* keep current settings, except index */
#if NEXUS_HAS_ASTM
                    set_astm_stc(handle, NULL);
#endif
                    NEXUS_StcChannel_Close(handle->stcChannel);
                    handle->stcChannel = NULL;

                    change = true;

                    /* open new channel with correct index */
                    settings.stcIndex = resolve_stc_index(&videoStatus, &audioStatus);
                    if (settings.stcIndex != -1)
                    {
                        settings.autoConfigTimebase = autoConfigTimebase;
                        handle->stcChannel = NEXUS_StcChannel_Open(NEXUS_ANY_ID, &settings);
                        if (!handle->stcChannel) { rc = BERR_TRACE(NEXUS_NOT_AVAILABLE); }
                        BDBG_MSG(("%p re-open %p: %d for %p,%p", (void *)handle, (void *)handle->stcChannel, settings.stcIndex, (void *)handle->video, (void *)handle->audio));
                    }
                }
                else
                {
#if NEXUS_NUM_MOSAIC_DECODES > 0
                    int oldStcIndex;
                    /*
                     * stc channel now supports deferred index change
                     * this depends on # mosaic decodes because in the PI
                     * the ability to change stc index also depends on a similar
                     * flag: BXPT_HAS_MOSAIC_SUPPORT.
                     */
                    oldStcIndex = settings.stcIndex;
                    settings.stcIndex = resolve_stc_index(&videoStatus, &audioStatus);
                    if (settings.stcIndex != -1)
                    {
                        settings.autoConfigTimebase = autoConfigTimebase;
                        rc = NEXUS_StcChannel_SetSettings(handle->stcChannel, &settings);
                        BDBG_MSG(("%p stc index change %p: %d -> %d for %p,%p", (void *)handle, (void *)handle->stcChannel, oldStcIndex, settings.stcIndex, (void *)handle->video, (void *)handle->audio));
                        if (rc) { rc = BERR_TRACE(rc); }
                    }
#else
                    BDBG_ERR(("%p: StcIndex mismatch after decoder start: StcChannel %d, VideoDecoder %p StcIndex %d; INVALID use case", handle,
                        settings.stcIndex, handle->video, videoStatus.stcIndex));
                    BDBG_ERR(("Please stop decoders before coupling them via stc channel"));
                    BDBG_ERR(("It is likely that you will experience subtle problems in the current state"));
                    rc = NEXUS_INVALID_PARAMETER;
#endif
                }
            }
            else if (settings.autoConfigTimebase != autoConfigTimebase) {
                settings.autoConfigTimebase = autoConfigTimebase;
                (void)NEXUS_StcChannel_SetSettings(handle->stcChannel, &settings);
            }
        }
        else
        {
            /* no stc channel allocated yet */

            NEXUS_StcChannel_GetDefaultSettings(0, &settings);
            change = true;

            settings.stcIndex = resolve_stc_index(&videoStatus, &audioStatus);

            if (settings.stcIndex != -1)
            {
                /* open new channel with correct index */
                settings.autoConfigTimebase = autoConfigTimebase;
                handle->stcChannel = NEXUS_StcChannel_Open(NEXUS_ANY_ID, &settings);
                if (!handle->stcChannel) { rc = BERR_TRACE(NEXUS_NOT_AVAILABLE); }
                BDBG_MSG(("%p open %p: %d for %p,%p", (void *)handle, (void *)handle->stcChannel, settings.stcIndex, (void *)handle->video, (void *)handle->audio));
            }
        }
    }
    else
    {
        if (handle->stcChannel)
        {
            NEXUS_StcChannelSettings settings;

            NEXUS_StcChannel_GetSettings(handle->stcChannel, &settings);
            BDBG_MSG(("Closing unused STC ch %p:%u", (void *)handle->stcChannel, settings.stcIndex));
#if NEXUS_HAS_ASTM
            set_astm_stc(handle, NULL);
#endif
            /* we can dispose of the server stc channel if no one is using it */
            NEXUS_StcChannel_Close(handle->stcChannel);
            handle->stcChannel = NULL;
        }
    }

    if (videoStatus.hdDviInput) {
        /* need call into NEXUS_SimpleStcChannel_P_SetSettings to set NEXUS_TimebaseSourceType_eHdDviIn */
        change = true;
    }

    if (change && handle->stcChannel)
    {
        BDBG_MSG(("%p: assigned stcChannel %p", (void *)handle, (void *)handle->stcChannel));

#if NEXUS_HAS_ASTM
        set_astm_stc(handle, handle->stcChannel);
#endif

        /* apply current settings */
        rc = apply_settings(handle);
        if (rc) { BERR_TRACE(rc); }
    }

    if (handle->stcChannel && handle->stcChannelAudio) {
        NEXUS_StcChannelPairSettings stcAudioVideoPair;
        NEXUS_StcChannel_GetDefaultPairSettings(&stcAudioVideoPair);
        stcAudioVideoPair.connected = true;
        NEXUS_StcChannel_SetPairSettings(handle->stcChannel, handle->stcChannelAudio, &stcAudioVideoPair);
    }

error:
    return rc;
}

NEXUS_StcChannelHandle NEXUS_SimpleStcChannel_GetServerStcChannel_priv(NEXUS_SimpleStcChannelHandle handle, NEXUS_SimpleDecoderType type)
{
    NEXUS_OBJECT_ASSERT(NEXUS_SimpleStcChannel, handle);
    if (type == NEXUS_SimpleDecoderType_eAudio && handle->stcChannelAudio) {
        return handle->stcChannelAudio;
    }
    else {
        return handle->stcChannel;
    }
}

void NEXUS_SimpleStcChannel_SetVideo_priv(NEXUS_SimpleStcChannelHandle handle, NEXUS_SimpleVideoDecoderHandle video)
{
    int rc = 0;

    NEXUS_OBJECT_ASSERT(NEXUS_SimpleStcChannel, handle);

    handle->video = video;

    rc = resolve_server_stc(handle);
    if (rc) { BERR_TRACE(rc); }

#if NEXUS_HAS_SYNC_CHANNEL
    if (handle->sync.enabled)
    {
        if (video)
        {
            NEXUS_SyncChannel_SimpleVideoConnected_priv(handle->sync.handle);
        }
        else
        {
            NEXUS_SyncChannel_SimpleVideoDisconnected_priv(handle->sync.handle);
        }
    }
#endif
}

void NEXUS_SimpleStcChannel_SetAudio_priv(NEXUS_SimpleStcChannelHandle handle, NEXUS_SimpleAudioDecoderHandle audio)
{
    int rc = 0;

    NEXUS_OBJECT_ASSERT(NEXUS_SimpleStcChannel, handle);

    handle->audio = audio;

    rc = resolve_server_stc(handle);
    if (rc) { BERR_TRACE(rc); }

#if NEXUS_HAS_SYNC_CHANNEL
    if (handle->sync.enabled)
    {
        if (audio)
        {
            NEXUS_SyncChannel_SimpleAudioConnected_priv(handle->sync.handle);
        }
        else
        {
            NEXUS_SyncChannel_SimpleAudioDisconnected_priv(handle->sync.handle);
        }
    }
#endif
}

#if NEXUS_HAS_ASTM
NEXUS_Error NEXUS_SimpleStcChannel_SetAstmVideo_priv(NEXUS_SimpleStcChannelHandle handle, NEXUS_VideoDecoderHandle videoDecoder)
{
    NEXUS_Error rc = NEXUS_SUCCESS;
    NEXUS_AstmSettings astmSettings;

    NEXUS_OBJECT_ASSERT(NEXUS_SimpleStcChannel, handle);

    BDBG_MSG(("Setting astm %p video decoder to %p", (void *)handle->astm.handle, (void *)videoDecoder));
    NEXUS_Astm_GetSettings(handle->astm.handle, &astmSettings);
    astmSettings.videoDecoder = videoDecoder;
    rc = NEXUS_Astm_SetSettings(handle->astm.handle, &astmSettings);

    return rc;
}

static bool isAudioDecoderInAstmQueue(NEXUS_SimpleStcChannelHandle handle, NEXUS_AudioDecoderHandle audioDecoder)
{
    bool inQueue = false;
    NEXUS_AudioDecoderQueueEntry * pEntry = NULL;

    NEXUS_OBJECT_ASSERT(NEXUS_SimpleStcChannel, handle);

    if (!BLST_Q_EMPTY(&handle->astm.connectedAudioDecoders))
    {
        for (pEntry = BLST_Q_FIRST(&handle->astm.connectedAudioDecoders); pEntry; pEntry = BLST_Q_NEXT(pEntry, link))
        {
            if (pEntry->audioDecoder == audioDecoder)
            {
                inQueue = true;
                break;
            }
        }
    }

    return inQueue;
}

static NEXUS_Error insertAstmAudioQueueEntry(NEXUS_SimpleStcChannelHandle handle, NEXUS_AudioDecoderHandle audioDecoder)
{
    NEXUS_Error rc = NEXUS_SUCCESS;
    NEXUS_AudioDecoderQueueEntry * pEntry = NULL;

    NEXUS_OBJECT_ASSERT(NEXUS_SimpleStcChannel, handle);

    if (!BLST_Q_EMPTY(&handle->astm.freeAudioDecoderEntries))
    {
        pEntry = BLST_Q_FIRST(&handle->astm.freeAudioDecoderEntries);
        BLST_Q_REMOVE_HEAD(&handle->astm.freeAudioDecoderEntries, link);
        BKNI_Memset(pEntry, 0, sizeof(NEXUS_AudioDecoderQueueEntry));
        pEntry->audioDecoder = audioDecoder;
        BLST_Q_INSERT_TAIL(&handle->astm.connectedAudioDecoders, pEntry, link);
    }
    else
    {
        BDBG_WRN(("ASTM audio decoder list full; decoder %p not managed by ASTM", (void *)audioDecoder));
        rc = BERR_TRACE(NEXUS_NOT_AVAILABLE);
        goto error;
    }

error:
    return rc;
}

static NEXUS_Error setAstmSettingsFromAudioQueue(NEXUS_SimpleStcChannelHandle handle)
{
    NEXUS_Error rc = NEXUS_SUCCESS;
    unsigned i = 0;
    NEXUS_AudioDecoderQueueEntry * pEntry = NULL;
    NEXUS_AstmSettings astmSettings;

    NEXUS_Astm_GetSettings(handle->astm.handle, &astmSettings);
    for (i = 0; i < NEXUS_ASTM_AUDIO_DECODERS; i++)
    {
        astmSettings.audioDecoder[i] = NULL;
    }
    for (pEntry = BLST_Q_FIRST(&handle->astm.connectedAudioDecoders), i = 0; (pEntry != NULL) && (i < NEXUS_ASTM_AUDIO_DECODERS); pEntry = BLST_Q_NEXT(pEntry, link), i++)
    {
        BDBG_MSG(("Setting audio decoder %p as astm audio index %d", (void *)pEntry->audioDecoder, i));
        astmSettings.audioDecoder[i] = pEntry->audioDecoder;
    }
    rc = NEXUS_Astm_SetSettings(handle->astm.handle, &astmSettings);

    return rc;
}

NEXUS_Error NEXUS_SimpleStcChannel_AddAstmAudio_priv(NEXUS_SimpleStcChannelHandle handle, NEXUS_AudioDecoderHandle audioDecoder)
{
    NEXUS_Error rc = NEXUS_SUCCESS;

    NEXUS_OBJECT_ASSERT(NEXUS_SimpleStcChannel, handle);

    if (!isAudioDecoderInAstmQueue(handle, audioDecoder))
    {
        rc = insertAstmAudioQueueEntry(handle, audioDecoder);
        if (rc) { rc = BERR_TRACE(rc); goto error; }

        rc = setAstmSettingsFromAudioQueue(handle);
        if (rc) { rc = BERR_TRACE(rc); goto error; }
    }

error:
    return rc;
}

static void removeAstmAudioQueueEntry(NEXUS_SimpleStcChannelHandle handle, NEXUS_AudioDecoderHandle audioDecoder)
{
    NEXUS_AudioDecoderQueueEntry * pEntry = NULL;

    NEXUS_OBJECT_ASSERT(NEXUS_SimpleStcChannel, handle);

    for (pEntry = BLST_Q_FIRST(&handle->astm.connectedAudioDecoders); pEntry != NULL; pEntry = BLST_Q_NEXT(pEntry, link))
    {
        if (pEntry->audioDecoder == audioDecoder)
        {
            break;
        }
    }

    if (pEntry)
    {
        BDBG_MSG(("Removing audio decoder %p from astm", (void*)pEntry->audioDecoder));
        BLST_Q_REMOVE(&handle->astm.connectedAudioDecoders, pEntry, link);
        pEntry->audioDecoder = NULL;
        BLST_Q_INSERT_HEAD(&handle->astm.freeAudioDecoderEntries, pEntry, link);
    }
}

void NEXUS_SimpleStcChannel_RemoveAstmAudio_priv(NEXUS_SimpleStcChannelHandle handle, NEXUS_AudioDecoderHandle audioDecoder)
{
    NEXUS_Error rc = NEXUS_SUCCESS;

    NEXUS_OBJECT_ASSERT(NEXUS_SimpleStcChannel, handle);

    removeAstmAudioQueueEntry(handle, audioDecoder);

    rc = setAstmSettingsFromAudioQueue(handle);
    if (rc) { rc = BERR_TRACE(rc); }
}
#endif

#if NEXUS_HAS_SYNC_CHANNEL
NEXUS_Error NEXUS_SimpleStcChannel_SetSyncVideo_priv(NEXUS_SimpleStcChannelHandle handle, NEXUS_VideoInput videoInput)
{
    NEXUS_Error rc = NEXUS_SUCCESS;

    NEXUS_OBJECT_ASSERT(NEXUS_SimpleStcChannel, handle);

    if (handle->sync.enabled)
    {
        NEXUS_SyncChannelSettings syncSettings;
        BDBG_MSG(("Setting sync %p video input to %p", (void *)handle->sync.handle, (void *)videoInput));
        NEXUS_SyncChannel_GetSettings(handle->sync.handle, &syncSettings);
        syncSettings.videoInput = videoInput;
        rc = NEXUS_SyncChannel_SetSettings(handle->sync.handle, &syncSettings);
    }

    return rc;
}

#if 0
void printSyncAudioQueue(NEXUS_SimpleStcChannelHandle handle)
{
    NEXUS_AudioInputQueueEntry * pEntry = NULL;

    NEXUS_OBJECT_ASSERT(NEXUS_SimpleStcChannel, handle);

    BDBG_MSG(("SimpleStcChannel %p: sync audio input queue {"));
    for (pEntry = BLST_Q_FIRST(&handle->sync.connectedAudioInputs); pEntry != NULL; pEntry = BLST_Q_NEXT(pEntry, link))
    {
        BDBG_MSG(("%p", pEntry->audioInput));
    }
    BDBG_MSG(("}"));
}
#endif

static bool isAudioInputInSyncQueue(NEXUS_SimpleStcChannelHandle handle, NEXUS_AudioInput audioInput)
{
    bool inQueue = false;
    NEXUS_AudioInputQueueEntry * pEntry = NULL;

    NEXUS_OBJECT_ASSERT(NEXUS_SimpleStcChannel, handle);

    if (!BLST_Q_EMPTY(&handle->sync.connectedAudioInputs))
    {
        for (pEntry = BLST_Q_FIRST(&handle->sync.connectedAudioInputs); pEntry; pEntry = BLST_Q_NEXT(pEntry, link))
        {
            if (pEntry->audioInput == audioInput)
            {
                inQueue = true;
                break;
            }
        }
    }

    return inQueue;
}

static NEXUS_Error insertSyncAudioQueueEntry(NEXUS_SimpleStcChannelHandle handle, NEXUS_AudioInput audioInput)
{
    NEXUS_Error rc = NEXUS_SUCCESS;
    NEXUS_AudioInputQueueEntry * pEntry = NULL;

    NEXUS_OBJECT_ASSERT(NEXUS_SimpleStcChannel, handle);

    if (!BLST_Q_EMPTY(&handle->sync.freeAudioInputEntries))
    {
        pEntry = BLST_Q_FIRST(&handle->sync.freeAudioInputEntries);
        BLST_Q_REMOVE_HEAD(&handle->sync.freeAudioInputEntries, link);
        BKNI_Memset(pEntry, 0, sizeof(NEXUS_AudioInputQueueEntry));
        pEntry->audioInput = audioInput;
        BLST_Q_INSERT_TAIL(&handle->sync.connectedAudioInputs, pEntry, link);
        BDBG_MSG(("Added audio input %p to sync %p", (void *)pEntry->audioInput, (void*)handle->sync.handle));
    }
    else
    {
        BDBG_WRN(("SyncChannel audio input list full; input %p not managed by SyncChannel", (void *)audioInput));
        rc = BERR_TRACE(NEXUS_NOT_AVAILABLE);
        goto error;
    }

error:
    return rc;
}

static NEXUS_Error setSyncSettingsFromAudioQueue(NEXUS_SimpleStcChannelHandle handle)
{
    NEXUS_Error rc = NEXUS_SUCCESS;
    unsigned i = 0;
    NEXUS_AudioInputQueueEntry * pEntry = NULL;
    NEXUS_SyncChannelSettings syncSettings;

    NEXUS_SyncChannel_GetSettings(handle->sync.handle, &syncSettings);
    for (i = 0; i < NEXUS_SYNC_CHANNEL_NUM_AUDIO_INPUTS; i++)
    {
        BDBG_MSG(("Setting sync %p audio index %d to %p", (void *)handle->sync.handle, i, NULL));
        syncSettings.audioInput[i] = NULL;
    }
    for (pEntry = BLST_Q_FIRST(&handle->sync.connectedAudioInputs), i = 0; (pEntry != NULL) && (i < NEXUS_SYNC_CHANNEL_NUM_AUDIO_INPUTS); pEntry = BLST_Q_NEXT(pEntry, link), i++)
    {
        BDBG_MSG(("Setting sync %p audio index %d to %p", (void *)handle->sync.handle, i, (void *)pEntry->audioInput));
        syncSettings.audioInput[i] = pEntry->audioInput;
    }
    rc = NEXUS_SyncChannel_SetSettings(handle->sync.handle, &syncSettings);

    return rc;
}

NEXUS_Error NEXUS_SimpleStcChannel_AddSyncAudio_priv(NEXUS_SimpleStcChannelHandle handle, NEXUS_AudioInput audioInput)
{
    NEXUS_Error rc = NEXUS_SUCCESS;

    NEXUS_OBJECT_ASSERT(NEXUS_SimpleStcChannel, handle);

    if (handle->sync.enabled)
    {
        if (!isAudioInputInSyncQueue(handle, audioInput))
        {
            rc = insertSyncAudioQueueEntry(handle, audioInput);
            if (rc) { rc = BERR_TRACE(rc); goto error; }

            rc = setSyncSettingsFromAudioQueue(handle);
            if (rc) { rc = BERR_TRACE(rc); goto error; }
        }
    }

error:
    return rc;
}

static void removeSyncAudioQueueEntry(NEXUS_SimpleStcChannelHandle handle, NEXUS_AudioInput audioInput)
{
    NEXUS_AudioInputQueueEntry * pEntry = NULL;

    NEXUS_OBJECT_ASSERT(NEXUS_SimpleStcChannel, handle);

    for (pEntry = BLST_Q_FIRST(&handle->sync.connectedAudioInputs); pEntry != NULL; pEntry = BLST_Q_NEXT(pEntry, link))
    {
        if (pEntry->audioInput == audioInput)
        {
            break;
        }
    }

    if (pEntry)
    {
        BLST_Q_REMOVE(&handle->sync.connectedAudioInputs, pEntry, link);
        BDBG_MSG(("Removed audio input %p from sync %p", (void *)pEntry->audioInput, (void *)handle->sync.handle));
        pEntry->audioInput = NULL;
        BLST_Q_INSERT_HEAD(&handle->sync.freeAudioInputEntries, pEntry, link);
    }
}

void NEXUS_SimpleStcChannel_RemoveSyncAudio_priv(NEXUS_SimpleStcChannelHandle handle, NEXUS_AudioInput audioInput)
{
    NEXUS_Error rc = NEXUS_SUCCESS;

    NEXUS_OBJECT_ASSERT(NEXUS_SimpleStcChannel, handle);

    if (handle->sync.enabled)
    {
        removeSyncAudioQueueEntry(handle, audioInput);

        rc = setSyncSettingsFromAudioQueue(handle);
        if (rc) { rc = BERR_TRACE(rc); }
    }
}
#endif

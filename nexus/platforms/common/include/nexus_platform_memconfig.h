/***************************************************************************
*     (c)2004-2014 Broadcom Corporation
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
* Revision History:
*
* $brcm_Log: $
*
***************************************************************************/
#ifndef NEXUS_PLATFORM_MEMCONFIG_H__
#define NEXUS_PLATFORM_MEMCONFIG_H__

#include "nexus_types.h"
#if NEXUS_HAS_VIDEO_DECODER
#include "nexus_video_decoder_types.h"
#endif
#if NEXUS_HAS_DISPLAY
#include "nexus_display_init.h"
#endif
#if NEXUS_HAS_VIDEO_ENCODER
#include "nexus_video_encoder_init.h"
#endif
#if NEXUS_HAS_AUDIO
#include "nexus_audio_init.h"
#endif

#ifdef __cplusplus
extern "C"
{
#endif

/**
Summary:
Input from user for NEXUS_Platform_MemConfigInit

Description:
Some platforms (for instance, 65nm) do not support this memconfig API. To tell if memconfig is supported, do the following:

    NEXUS_MemoryConfigurationSettings memConfigSettings;
    NEXUS_GetDefaultMemoryConfigurationSettings(&memConfigSettings);
    if (memConfigSettings.display[0].maxFormat == NEXUS_VideoFormat_eUnknown) {
        // should assume memconfig not supported on this platform. don't use memConfigSettings.
    }
**/
typedef struct NEXUS_MemoryConfigurationSettings
{
#if NEXUS_HAS_VIDEO_DECODER
    NEXUS_VideoDecoderMemory videoDecoder[NEXUS_MAX_VIDEO_DECODERS]; /* typically 0 is main, 1 is PIP. mapping from videoDecoder[] to AVD can vary, but we support a generic mapping. */
    NEXUS_VideoDecoderMemory stillDecoder[NEXUS_MAX_STILL_DECODERS];
#endif
#if NEXUS_HAS_DISPLAY
    NEXUS_DisplayMemConfig display[NEXUS_MAX_DISPLAYS];
#endif
    struct {
        bool hdDvi;
        bool ccir656;
    } videoInputs;
#if NEXUS_HAS_VIDEO_ENCODER
    NEXUS_VideoEncoderMemory videoEncoder[NEXUS_MAX_VIDEO_ENCODERS];
#endif

#if NEXUS_HAS_AUDIO
    NEXUS_AudioModuleUsageSettings audio;
#endif
} NEXUS_MemoryConfigurationSettings;

/**
Summary:
HW/RTS capabilities of the system. NEXUS_MemoryConfigurationSettings decisions can be made based on this.
**/
typedef struct NEXUS_PlatformCapabilities
{
#if NEXUS_HAS_DISPLAY
    struct {
        bool supported;
        bool encoder; /* if true, this is only for encoder use */
    } display[NEXUS_MAX_DISPLAYS];
#endif
#if NEXUS_HAS_VIDEO_ENCODER
    struct {
        bool supported;
        unsigned displayIndex;
    } videoEncoder[NEXUS_MAX_VIDEO_ENCODERS];
#endif
    unsigned unused;
} NEXUS_PlatformCapabilities;


#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* #ifndef NEXUS_PLATFORM_MEMCONFIG_H__ */

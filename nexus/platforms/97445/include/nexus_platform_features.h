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
 * Module Description:
 *
 * Revision History:
 *
 * $brcm_Log: $
 *
 ***************************************************************************/
#ifndef NEXUS_PLATFORM_FEATURES_H__
#define NEXUS_PLATFORM_FEATURES_H__

#include "bstd.h"

#include "nexus_platform_generic_features_priv.h"

/* Transport Features */
#define NEXUS_NUM_PARSER_BANDS 24    /* Was 6. There are 24 avaliable */
#define NEXUS_NUM_PID_CHANNELS 768
#define NEXUS_NUM_VCXOS 3
#define NEXUS_NUM_MESSAGE_FILTERS 256
#define NEXUS_NUM_PLAYPUMPS 32  /* 6*4 for headless config, 32 available */

#define NEXUS_NUM_VIDEO_DECODERS  6         /* 2 each for HEVD and each HVD */

/* Audio Features */
#define NEXUS_NUM_AUDIO_DECODERS 12 /* Increased from 6 to 12 for SW7445-2423 */
#define NEXUS_NUM_AUDIO_INPUT_CAPTURES 2 /* Number of external inputs active at a time */
#define NEXUS_NUM_AUDIO_DACS 1
#define NEXUS_NUM_SPDIF_INPUTS 1
#define NEXUS_NUM_SPDIF_OUTPUTS 2
#define NEXUS_NUM_AUDIO_DUMMY_OUTPUTS 8
#define NEXUS_NUM_AUDIO_MIXERS 14

#define NEXUS_NUM_I2S_INPUTS 1
#define NEXUS_NUM_I2S_OUTPUTS 2
#define NEXUS_NUM_AUDIO_CAPTURE_CHANNELS 1
#define NEXUS_NUM_AUDIO_CAPTURES 1
#define NEXUS_NUM_AUDIO_PLAYBACKS 3
#define NEXUS_NUM_AUDIO_CRCS 2

#define NEXUS_HAS_AUDIO_MUX_OUTPUT 1

/* Display Features */
#define NEXUS_NUM_656_OUTPUTS 1
#define NEXUS_NUM_COMPONENT_OUTPUTS 1
#define NEXUS_NUM_COMPOSITE_OUTPUTS 1
#define NEXUS_NUM_SVIDEO_OUTPUTS 0

#define NEXUS_NUM_VCE_DEVICES    2
#define NEXUS_NUM_VCE_CHANNELS   3 /* per device */
#define NEXUS_NUM_VIDEO_ENCODERS   (NEXUS_NUM_VCE_CHANNELS * NEXUS_NUM_VCE_DEVICES)

/* Max number of displays and windows supported
by this platform. Actual numbers may vary depeding
upon the chip usage. See below */
#define NEXUS_NUM_DISPLAYS 7 /* C0/C1 for local HD/SD simul,C2 for display 3 & c3,c4,c5,c6  for quad transcodes */
#define NEXUS_NUM_VIDEO_WINDOWS   2 /* per display */

#define NEXUS_MAX_FRONTENDS NEXUS_NUM_PARSER_BANDS
/* Cable Frontend */
/* The maximum number of input bands on 7425 are 9. Also 3128 has 8 DS + 1 OB */
#if NEXUS_FRONTEND_3128
#define NEXUS_3128_MAX_DOWNSTREAM_CHANNELS 8
#elif NEXUS_FRONTEND_3124
#define NEXUS_3128_MAX_DOWNSTREAM_CHANNELS 4
#elif NEXUS_FRONTEND_3123
#define NEXUS_3128_MAX_DOWNSTREAM_CHANNELS 3
#endif
#if NEXUS_USE_FRONTEND_DAUGHTER_CARD
#define NEXUS_NUM_FRONTEND_CARD_SLOTS 1
#endif

#define NEXUS_MAX_3255_ADSCHN 8
#define NEXUS_3255_OOB_TUNER_IFFREQ (1250000)/* 1.25 MHz */
#define NEXUS_SHARED_FRONTEND_INTERRUPT 1




/* I2C Channels */
#define NEXUS_NUM_I2C_CHANNELS 5

#if NEXUS_USE_7445_DBS
/* SPI Channels */
#define NEXUS_NUM_SPI_CHANNELS 3
#endif

/* I2C channel usage assignments. Refer to BSC table in the board schematics. */
#define NEXUS_I2C_CHANNEL_HDMI_TX         0
#define NEXUS_I2C_CHANNEL_LNA             3  /* BCM3405 */
#define NEXUS_I2C_CHANNEL_EXT_RFM         3  /* External RFM */
#define NEXUS_I2C_CHANNEL_DSTRM_TUNER     4  /* BCM3128(for VMS board) */

/* SMARTCARD CHANNELS */
#define NEXUS_NUM_SMARTCARD_CHANNELS 2

/* DVB-CI Details */
#define NEXUS_DVB_CI_MEMORY_BASE (0xEFF00000)
#define NEXUS_DVB_CI_MEMORY_LENGTH (1024*1024)

/* Memory features */
#define NEXUS_NUM_MEMC 3

/* default heap indices, refer to memory map document  */
#define NEXUS_MEMC0_MAIN_HEAP           0
#define NEXUS_VIDEO_SECURE_HEAP         1
#define NEXUS_MEMC0_PICTURE_BUFFER_HEAP 2
#define NEXUS_MEMC0_GRAPHICS_HEAP       3
#define NEXUS_SAGE_SECURE_HEAP          4
#define NEXUS_MEMC1_GRAPHICS_HEAP       5
#define NEXUS_MEMC1_PICTURE_BUFFER_HEAP 6
#define NEXUS_MEMC1_DRIVER_HEAP         7
#define NEXUS_MEMC2_GRAPHICS_HEAP       8
#define NEXUS_MEMC2_PICTURE_BUFFER_HEAP 9
#define NEXUS_MEMC2_DRIVER_HEAP         10
#define NEXUS_MEMC0_SECURE_PICTURE_BUFFER_HEAP 11
#define NEXUS_MEMC1_SECURE_PICTURE_BUFFER_HEAP 12
#define NEXUS_MEMC2_SECURE_PICTURE_BUFFER_HEAP 13

#define NEXUS_PLATFORM_P_GET_FRAMEBUFFER_HEAP_INDEX 1

#define NEXUS_AVS_MONITOR           0
#endif /* #ifndef NEXUS_PLATFORM_FEATURES_H__ */

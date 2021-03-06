/******************************************************************************
 *    (c)2007-2015 Broadcom Corporation
 *
 * This program is the proprietary software of Broadcom Corporation and/or its licensors,
 * and may only be used, duplicated, modified or distributed pursuant to the terms and
 * conditions of a separate, written license agreement executed between you and Broadcom
 * (an "Authorized License").  Except as set forth in an Authorized License, Broadcom grants
 * no license (express or implied), right to use, or waiver of any kind with respect to the
 * Software, and Broadcom expressly reserves all rights in and to the Software and all
 * intellectual property rights therein.  IF YOU HAVE NO AUTHORIZED LICENSE, THEN YOU
 * HAVE NO RIGHT TO USE THIS SOFTWARE IN ANY WAY, AND SHOULD IMMEDIATELY
 * NOTIFY BROADCOM AND DISCONTINUE ALL USE OF THE SOFTWARE.
 *
 * Except as expressly set forth in the Authorized License,
 *
 * 1.     This program, including its structure, sequence and organization, constitutes the valuable trade
 * secrets of Broadcom, and you shall use all reasonable efforts to protect the confidentiality thereof,
 * and to use this information only in connection with your use of Broadcom integrated circuit products.
 *
 * 2.     TO THE MAXIMUM EXTENT PERMITTED BY LAW, THE SOFTWARE IS PROVIDED "AS IS"
 * AND WITH ALL FAULTS AND BROADCOM MAKES NO PROMISES, REPRESENTATIONS OR
 * WARRANTIES, EITHER EXPRESS, IMPLIED, STATUTORY, OR OTHERWISE, WITH RESPECT TO
 * THE SOFTWARE.  BROADCOM SPECIFICALLY DISCLAIMS ANY AND ALL IMPLIED WARRANTIES
 * OF TITLE, MERCHANTABILITY, NONINFRINGEMENT, FITNESS FOR A PARTICULAR PURPOSE,
 * LACK OF VIRUSES, ACCURACY OR COMPLETENESS, QUIET ENJOYMENT, QUIET POSSESSION
 * OR CORRESPONDENCE TO DESCRIPTION. YOU ASSUME THE ENTIRE RISK ARISING OUT OF
 * USE OR PERFORMANCE OF THE SOFTWARE.
 *
 * 3.     TO THE MAXIMUM EXTENT PERMITTED BY LAW, IN NO EVENT SHALL BROADCOM OR ITS
 * LICENSORS BE LIABLE FOR (i) CONSEQUENTIAL, INCIDENTAL, SPECIAL, INDIRECT, OR
 * EXEMPLARY DAMAGES WHATSOEVER ARISING OUT OF OR IN ANY WAY RELATING TO YOUR
 * USE OF OR INABILITY TO USE THE SOFTWARE EVEN IF BROADCOM HAS BEEN ADVISED OF
 * THE POSSIBILITY OF SUCH DAMAGES; OR (ii) ANY AMOUNT IN EXCESS OF THE AMOUNT
 * ACTUALLY PAID FOR THE SOFTWARE ITSELF OR U.S. $1, WHICHEVER IS GREATER. THESE
 * LIMITATIONS SHALL APPLY NOTWITHSTANDING ANY FAILURE OF ESSENTIAL PURPOSE OF
 * ANY LIMITED REMEDY.
 *
 *****************************************************************************/
 /* Example m2m AES-CBC  encryption  record with keyladder   */
 /* This example makes a pair with  playback using "m2m_aescbc_keyladder_playback.c " */

#if NEXUS_HAS_SECURITY  && (NEXUS_SECURITY_ZEUS_VERSION_MAJOR >= 1) && NEXUS_HAS_VIDEO_DECODER

#include "nexus_platform.h"
#include "nexus_pid_channel.h"
#include "nexus_parser_band.h"
#include "nexus_recpump.h"
#if NEXUS_HAS_RECORD
#include "nexus_record.h"
#endif

#if NEXUS_HAS_PLAYBACK
#include "nexus_playback.h"
#include "nexus_file.h"
#endif
#include "nexus_dma.h"
#include "nexus_security.h"
#include "nexus_keyladder.h"

#include <stdio.h>
#include "bstd.h"
#include "bkni.h"
#include "bkni_multi.h"
#include <assert.h>

/* A clear stream, or stream with a clear program to be played and recorded to an encrpted stream. */
#define PLAY_FILE     "/mnt/nfs/video/576i50_2min.ts"

/* Any location that can be accessed by the STB
 * to record the encrypted stream with a clear program in the above stream. */
#define RECORDED_FILE "/mnt/nfs/video/recorded_stream_aescbc.mpg"

/* The video pid value and parameters that match a clear pid in PLAY_FILE. */
#define TRANSPORT_TYPE NEXUS_TransportType_eTs
#define VIDEO_CODEC NEXUS_VideoCodec_eMpeg2
#define AUDIO_CODEC NEXUS_AudioCodec_eMpeg

/* The audio pid of the clear program to be recorded and encrypted in PLAY_FILE. */
#define AUDIO_PID (2317 )
/* The video pid of the clear program to be recorded and encrypted in PLAY_FILE. */
#define VIDEO_PID (2316 )

static BERR_Code playpump_setup ( NEXUS_VideoDecoderHandle * videoDecoder,
                                  NEXUS_AudioDecoderHandle * audioDecoder,
                                  NEXUS_PidChannelHandle * pVideoPidChannel,
                                  NEXUS_StcChannelHandle * pStcChannel,
                                  NEXUS_PlaybackHandle * pPlayback, NEXUS_PlaypumpHandle * pPlaypump );

static int      keySlotSetup ( NEXUS_KeySlotHandle* keyHandle, NEXUS_SecurityOperation operation, NEXUS_SecurityVirtualKeyladderID vklId );

static int Security_AllocateVkl ( NEXUS_SecurityCustomerSubMode custSubMode, NEXUS_SecurityVirtualKeyladderID * vkl,
                                  NEXUS_VirtualKeyLadderHandle * vklHandle )
{
    NEXUS_SecurityVKLSettings vklSettings;
    NEXUS_VirtualKeyLadderInfo vklInfo;

    BDBG_ASSERT ( vkl );
    BDBG_ASSERT ( vklHandle );

    NEXUS_Security_GetDefaultVKLSettings ( &vklSettings );

    /* For pre Zeus 3.0, please set vklSettings.custSubMode */
    vklSettings.custSubMode = custSubMode;

    *vklHandle = NEXUS_Security_AllocateVKL ( &vklSettings );

    if ( !( *vklHandle ) )
    {
        printf ( "\nAllocate VKL failed \n" );
        return 1;
    }

    NEXUS_Security_GetVKLInfo ( *vklHandle, &vklInfo );
    printf ( "\nVKL Handle %p is allocated for VKL#%d\n", ( void * ) *vklHandle, vklInfo.vkl & 0x7F );

    /* For Zeus 4.2 or later
     * if ((vklInfo.vkl & 0x7F ) >= NEXUS_SecurityVirtualKeyLadderID_eMax)
     * {
     * printf ( "\nAllocate VKL failed with invalid VKL Id.\n" );
     * return 1;
     * }
     */

    *vkl = vklInfo.vkl;

    return 0;
}

int main ( void )
{
#if (NEXUS_HAS_RECORD  && NEXUS_HAS_PLAYBACK)
    NEXUS_PlatformSettings platformSettings;
    NEXUS_FileRecordHandle recordfile;
    NEXUS_FilePlayHandle playfile;
    NEXUS_RecpumpOpenSettings recpumpOpenSettings;
    NEXUS_RecpumpHandle recpump;
    NEXUS_RecordSettings recordCfg;
    NEXUS_RecordHandle record;

    NEXUS_VideoDecoderHandle videoDecoder;
    NEXUS_AudioDecoderHandle audioDecoder;

    NEXUS_StcChannelHandle stcChannel;
    NEXUS_KeySlotHandle keyHandle;
    NEXUS_SecurityVirtualKeyladderID vklId;
    NEXUS_VirtualKeyLadderHandle vklHandle;

    NEXUS_PlaypumpHandle playpump;

    NEXUS_PlaybackHandle playback;
    NEXUS_PidChannelHandle videoPidChannel;

    NEXUS_RecordPidChannelSettings pidSettings;

    const char     *recfname = RECORDED_FILE;
    const char     *playfname = PLAY_FILE;

    /* No front and AV output are used in the test. */
    NEXUS_Platform_GetDefaultSettings ( &platformSettings );
    platformSettings.openFrontend = false;
    platformSettings.openOutputs = false;
    platformSettings.openCec = false;
    NEXUS_Platform_Init ( &platformSettings );

    playfile = NEXUS_FilePlay_OpenPosix ( playfname, NULL );
    if ( !playfile )
    {
        fprintf ( stderr, "can't open file:%s\n", playfname );
        return -1;
    }

    /* set up the source */
    playpump_setup ( &videoDecoder, &audioDecoder, &videoPidChannel, &stcChannel, &playback, &playpump );

    if ( !videoPidChannel )
    {
        printf ( "\nError: null video pid channel.\n" );
        return -1;
    }

	/* Request for an VKL to use */
	if ( Security_AllocateVkl ( NEXUS_SecurityCustomerSubMode_eGeneric_CP_128_4, &vklId, &vklHandle ) )
	{
		printf ( "\nAllocate VKL failed.\n" );
		return 1;
	}

    /* Setup the security */
    /* Allocate AV keyslots */
    /* configure the key slot and set up the key ladder for decryption */
    if ( keySlotSetup ( &keyHandle, NEXUS_SecurityOperation_eEncrypt, vklId ) )
    {
        printf ( "\nKeyslot setup for decryption failed \n" );
        return 1;
    }

    /* Setup the record */
    NEXUS_Recpump_GetDefaultOpenSettings ( &recpumpOpenSettings );

    /* set threshold to 30%. with band hold enabled, it is a bandhold threshold. */
    recpumpOpenSettings.data.dataReadyThreshold = recpumpOpenSettings.data.bufferSize * 3 / 10;
    recpumpOpenSettings.index.dataReadyThreshold = recpumpOpenSettings.index.bufferSize * 3 / 10;
    recpump = NEXUS_Recpump_Open ( NEXUS_ANY_ID, &recpumpOpenSettings );

    record = NEXUS_Record_Create (  );
    NEXUS_Record_GetSettings ( record, &recordCfg );
    recordCfg.recpump = recpump;

    /* enable bandhold. required for record from playback. */
    recordCfg.recpumpSettings.bandHold = NEXUS_RecpumpFlowControl_eEnable;
    NEXUS_Record_SetSettings ( record, &recordCfg );

    recordfile = NEXUS_FileRecord_OpenPosix ( recfname, NULL );
    if ( !recordfile )
    {
        fprintf ( stderr, "can't open file:%s \n", recfname );
        return -1;
    }

    NEXUS_Record_GetDefaultPidChannelSettings ( &pidSettings );
    pidSettings.recpumpSettings.pidType = NEXUS_PidType_eVideo;
    pidSettings.recpumpSettings.pidTypeSettings.video.index = true;
    pidSettings.recpumpSettings.pidTypeSettings.video.codec = NEXUS_VideoCodec_eMpeg2;
    NEXUS_Record_AddPidChannel ( record, videoPidChannel, &pidSettings );

    NEXUS_Record_Start ( record, recordfile );

    /* Start playback */
    NEXUS_Playback_Start ( playback, playfile, NULL );

    /* Wait for the two seconds for the record of the short stream completes. */
    sleep ( 2 );

    printf
        ( "Record has been created with files %s. Use m2m_aescbc_keyladder_playback to inspect the encrypted stream on HDMI.\n",
          RECORDED_FILE );

    /* Tear down the devices chain */
    NEXUS_Record_Stop ( record );
    NEXUS_Record_RemoveAllPidChannels ( record );

    NEXUS_FileRecord_Close ( recordfile );
    NEXUS_Record_Destroy ( record );
    NEXUS_Recpump_Close ( recpump );

    NEXUS_Playback_Stop ( playback );
    NEXUS_Playback_ClosePidChannel ( playback, videoPidChannel );
    NEXUS_FilePlay_Close ( playfile );
    NEXUS_Playback_Destroy ( playback );
    NEXUS_Playpump_Close ( playpump );

    NEXUS_VideoDecoder_Close ( videoDecoder );
    NEXUS_AudioDecoder_Close ( audioDecoder );
    NEXUS_StcChannel_Close ( stcChannel );

    NEXUS_Security_FreeKeySlot ( keyHandle );
    NEXUS_Security_FreeVKL ( vklHandle );

    NEXUS_Platform_Uninit (  );

#else
    printf ( "This application is not supported on this platform!\n" );
#endif
    return 0;
}

static BERR_Code playpump_setup ( NEXUS_VideoDecoderHandle * videoDecoder,
                                  NEXUS_AudioDecoderHandle * audioDecoder,
                                  NEXUS_PidChannelHandle * pVideoPidChannel,
                                  NEXUS_StcChannelHandle * pStcChannel,
                                  NEXUS_PlaybackHandle * pPlayback, NEXUS_PlaypumpHandle * pPlaypump )
{
    NEXUS_PidChannelHandle videoPidChannel, audioPidChannel;

    NEXUS_StcChannelSettings stcSettings;
    NEXUS_StcChannelHandle stcChannel;

    NEXUS_PlaypumpHandle playpump;
    NEXUS_PlaybackHandle playback;
    NEXUS_PlaybackSettings playbackSettings;
    NEXUS_PlaybackPidChannelSettings playbackPidSettings;

    /* set up the source */
    playpump = NEXUS_Playpump_Open ( NEXUS_ANY_ID, NULL );
    assert ( playpump );
    playback = NEXUS_Playback_Create (  );
    assert ( playback );

    NEXUS_StcChannel_GetDefaultSettings ( 0, &stcSettings );
    stcSettings.timebase = NEXUS_Timebase_e0;
    stcSettings.mode = NEXUS_StcChannelMode_eAuto;
    stcChannel = NEXUS_StcChannel_Open ( 0, &stcSettings );
    *pStcChannel = stcChannel;

    NEXUS_Playback_GetSettings ( playback, &playbackSettings );
    playbackSettings.playpump = playpump;
    playbackSettings.playpumpSettings.transportType = TRANSPORT_TYPE;

    playbackSettings.stcChannel = stcChannel;
    NEXUS_Playback_SetSettings ( playback, &playbackSettings );

    *videoDecoder = NEXUS_VideoDecoder_Open ( 0, NULL );        /* take default capabilities */

    /* Open the audio and video pid channels */
    NEXUS_Playback_GetDefaultPidChannelSettings ( &playbackPidSettings );
    playbackPidSettings.pidSettings.pidType = NEXUS_PidType_eVideo;
    playbackPidSettings.pidTypeSettings.video.codec = VIDEO_CODEC;
    playbackPidSettings.pidTypeSettings.video.index = true;
    playbackPidSettings.pidTypeSettings.video.decoder = *videoDecoder;

    /* configure the video pid for indexing */
    videoPidChannel = NEXUS_Playback_OpenPidChannel ( playback, VIDEO_PID, &playbackPidSettings );

    *audioDecoder = NEXUS_AudioDecoder_Open ( 0, NULL );

    NEXUS_Playback_GetDefaultPidChannelSettings ( &playbackPidSettings );
    playbackPidSettings.pidSettings.pidType = NEXUS_PidType_eAudio;
    playbackPidSettings.pidTypeSettings.audio.primary = *audioDecoder;
    audioPidChannel = NEXUS_Playback_OpenPidChannel ( playback, AUDIO_PID, &playbackPidSettings );

    *pVideoPidChannel = videoPidChannel;

    *pPlayback = playback;
    *pPlaypump = playpump;
    return 0;
}

static int      keySlotSetup ( NEXUS_KeySlotHandle* pKeyHandle, NEXUS_SecurityOperation operation, NEXUS_SecurityVirtualKeyladderID vklId )
{
	NEXUS_KeySlotHandle keyHandle;
    NEXUS_SecurityInvalidateKeySettings invSettings;
	NEXUS_SecurityAlgorithmSettings NexusConfig;
    NEXUS_SecurityEncryptedSessionKey encryptedSessionkey;
    NEXUS_SecurityEncryptedControlWord encrytedCW;
    NEXUS_SecurityKeySlotSettings keySettings;

    unsigned char   ucProcInForKey3[16] = {
        0x0f, 0x09, 0xa2, 0x06, 0x19, 0x88, 0xb6, 0x89,
        0x28, 0xeb, 0x90, 0x2e, 0xb2, 0x36, 0x18, 0x88
    };

    unsigned char   ucProcInForKey4[16] = {
        0xe4, 0x62, 0x75, 0x1b, 0x5d, 0xd4, 0xbc, 0x02,
        0x27, 0x9e, 0xc9, 0x6c, 0xc8, 0x66, 0xec, 0x10
    };

    NEXUS_SecurityClearKey key;
    uint8_t         ivkeys[16] =
        { 0xad, 0xd6, 0x9e, 0xa3, 0x89, 0xc8, 0x17, 0x72, 0x1e, 0xd4, 0x0e, 0xab, 0x3d, 0xbc, 0x7a, 0xf2 };

    NEXUS_Security_GetDefaultKeySlotSettings ( &keySettings );
    keySettings.keySlotEngine = NEXUS_SecurityEngine_eM2m;
    keySettings.keySlotType = NEXUS_SecurityKeySlotType_eType2;
    keyHandle = NEXUS_Security_AllocateKeySlot ( &keySettings );
    if ( !keyHandle )
    {
        printf ( "\nAllocate enc keyslot failed \n" );
        return 1;
    }

    *pKeyHandle = keyHandle;

    /* Invalidate all the keys. */
    NEXUS_Security_GetDefaultInvalidateKeySettings ( &invSettings );
    invSettings.invalidateAllEntries = true;
    invSettings.invalidateKeyType = NEXUS_SecurityInvalidateKeyFlag_eDestKeyOnly;
    NEXUS_Security_InvalidateKey ( keyHandle, &invSettings );

    /* configure the key slot */
    NEXUS_Security_GetDefaultAlgorithmSettings ( &NexusConfig );
    NexusConfig.algorithm = NEXUS_SecurityAlgorithm_eAes;
    NexusConfig.algorithmVar = NEXUS_SecurityAlgorithmVariant_eCbc;
    NexusConfig.terminationMode = NEXUS_SecurityTerminationMode_eClear;
    NexusConfig.ivMode = NEXUS_SecurityIVMode_eRegular;
    NexusConfig.solitarySelect = NEXUS_SecuritySolitarySelect_eClear;
    NexusConfig.caVendorID = 0x1234;
    NexusConfig.askmModuleID = NEXUS_SecurityAskmModuleID_eModuleID_4;
    NexusConfig.otpId = NEXUS_SecurityOtpId_eOtpVal;
    NexusConfig.key2Select = NEXUS_SecurityKey2Select_eReserved1;
    NexusConfig.operation = operation;
    NexusConfig.keyDestEntryType = NEXUS_SecurityKeyType_eOdd;
    NexusConfig.dest = NEXUS_SecurityAlgorithmConfigDestination_eMem2Mem;

    if ( NEXUS_Security_ConfigAlgorithm ( keyHandle, &NexusConfig ) != 0 )
    {
        printf ( "\nConfigAlg clear keyslot failed \n" );
        return 1;
    }

    /* set up the key ladder to route out the key for (operation) */
    NEXUS_Security_GetDefaultSessionKeySettings ( &encryptedSessionkey );
    encryptedSessionkey.keyladderType = NEXUS_SecurityKeyladderType_e3Des;
    encryptedSessionkey.swizzleType = NEXUS_SecuritySwizzleType_eNone;
    encryptedSessionkey.cusKeyL = 0x00;
    encryptedSessionkey.cusKeyH = 0x00;
    encryptedSessionkey.cusKeyVarL = 0x00;
    encryptedSessionkey.cusKeyVarH = 0xFF;
    encryptedSessionkey.keyGenCmdID = NEXUS_SecurityKeyGenCmdID_eKeyGen;
    encryptedSessionkey.sessionKeyOp = NEXUS_SecuritySessionKeyOp_eNoProcess;
    encryptedSessionkey.bASKMMode = false;
    encryptedSessionkey.rootKeySrc = NEXUS_SecurityRootKeySrc_eOtpKeyA;
    encryptedSessionkey.bSwapAESKey = false;
    encryptedSessionkey.keyDestIVType = NEXUS_SecurityKeyIVType_eNoIV;
    encryptedSessionkey.bRouteKey = false;
    encryptedSessionkey.operation = NEXUS_SecurityOperation_eDecrypt;
    encryptedSessionkey.operationKey2 = NEXUS_SecurityOperation_eEncrypt;
    encryptedSessionkey.keyEntryType = NEXUS_SecurityKeyType_eOdd;

    encryptedSessionkey.custSubMode = NEXUS_SecurityCustomerSubMode_eGeneric_CP_128_4;
    encryptedSessionkey.virtualKeyLadderID = vklId;
    encryptedSessionkey.keyMode = NEXUS_SecurityKeyMode_eRegular;
    encryptedSessionkey.dest = NEXUS_SecurityAlgorithmConfigDestination_eMem2Mem;

    BKNI_Memcpy ( encryptedSessionkey.keyData, ucProcInForKey3, sizeof ( ucProcInForKey3 ) );

    if ( NEXUS_Security_GenerateSessionKey ( keyHandle, &encryptedSessionkey ) != 0 )
    {
        printf ( "\nLoading session key failed \n" );
        return 1;
    }

    /* Load CW - key4 -- routed out */
    NEXUS_Security_GetDefaultControlWordSettings ( &encrytedCW );

    encrytedCW.keyladderType = NEXUS_SecurityKeyladderType_e3Des;
    encrytedCW.keySize = sizeof ( ucProcInForKey4 );
    encrytedCW.keyEntryType = NEXUS_SecurityKeyType_eOdd;

    encrytedCW.custSubMode = NEXUS_SecurityCustomerSubMode_eGeneric_CP_128_4;
    encrytedCW.virtualKeyLadderID = vklId;
    encrytedCW.keyMode = NEXUS_SecurityKeyMode_eRegular;

    BKNI_Memcpy ( encrytedCW.keyData, ucProcInForKey4, encrytedCW.keySize );
    encrytedCW.operation = NEXUS_SecurityOperation_eDecrypt;
    encrytedCW.bRouteKey = true;
    encrytedCW.keyDestIVType = NEXUS_SecurityKeyIVType_eNoIV;
    encrytedCW.keyGenCmdID = NEXUS_SecurityKeyGenCmdID_eKeyGen;
    encrytedCW.bSwapAESKey = false;
    encrytedCW.bASKMMode = false;
    encrytedCW.dest = NEXUS_SecurityAlgorithmConfigDestination_eMem2Mem;

    if ( NEXUS_Security_GenerateControlWord ( keyHandle, &encrytedCW ) )
    {
        printf ( "\nGenerate Control Word failed for Key Slot Handle %x\n", ( unsigned int ) keyHandle );
        return 1;
    }

    NEXUS_Security_GetDefaultClearKey ( &key );
    key.keySize = 16;
    key.keyEntryType = NEXUS_SecurityKeyType_eOdd;
    key.keyIVType = NEXUS_SecurityKeyIVType_eIV;
    key.dest = NEXUS_SecurityAlgorithmConfigDestination_eMem2Mem;
    BKNI_Memcpy ( key.keyData, ivkeys, key.keySize );
    NEXUS_Security_LoadClearKey ( keyHandle, &key );

    return ( 0 );

}

#else /* NEXUS_HAS_SECURITY && ... */
#include <stdio.h>
int main ( void )
{
    printf ( "This application is not supported on this platform!\n" );
    return -1;
}
#endif

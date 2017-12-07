/******************************************************************************
 * Copyright (C) 2017 Broadcom.  The term "Broadcom" refers to Broadcom Limited and/or its subsidiaries.
 *
 * This program is the proprietary software of Broadcom and/or its licensors,
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
 *****************************************************************************/

#if NEXUS_HAS_SECURITY && (NEXUS_SECURITY_API_VERSION==2)

#include "nexus_security.h"
#include "nexus_keyslot.h"
#include "nexus_keyladder.h"
#include "security_utils.h"
#include "nexus_security_datatypes.h"
#include "security_test_vectors_clear_key.h"

typedef struct security_keyladderTestData {
    NEXUS_KeyLadderRootType rootType;
    NEXUS_KeyLadderLevelKey levelKey;
    NEXUS_KeyLadderSettings settings;
    NEXUS_KeyLadderHandle handle;
    NEXUS_CryptographicAlgorithmMode algorithmMode;
    unsigned      data_size;
    uint8_t      *pSrc;
    uint8_t      *pDest;
} security_keyladderTestData;

static int test_keyladder_SetKeyslot(
    NEXUS_KeySlotBlockEntry slotEntry,
    NEXUS_CryptographicAlgorithm algorithm,
    NEXUS_CryptographicAlgorithmMode algorithmMode,
    NEXUS_KeySlotHandle * pKeyslotHandle )
{
    NEXUS_KeySlotAllocateSettings keyslotAllocSettings;
    NEXUS_KeySlotSettings keyslotSettings;
    NEXUS_KeySlotEntrySettings keyslotEntrySettings;
    NEXUS_KeySlotHandle keyslotHandle = NULL;
    NEXUS_Error rc = NEXUS_UNKNOWN;

    /* allocate keyslot */
    NEXUS_KeySlot_GetDefaultAllocateSettings( &keyslotAllocSettings );
    keyslotAllocSettings.owner = NEXUS_SecurityCpuContext_eHost;
    keyslotAllocSettings.slotType = NEXUS_KeySlotType_eIvPerBlock;
    keyslotAllocSettings.useWithDma = true;
    keyslotHandle = NEXUS_KeySlot_Allocate( &keyslotAllocSettings );
    if( !keyslotHandle ) { return BERR_TRACE( NEXUS_NOT_AVAILABLE ); }

    /*configure keyslot parameters */
    NEXUS_KeySlot_GetSettings( keyslotHandle, &keyslotSettings );
    rc = NEXUS_KeySlot_SetSettings( keyslotHandle, &keyslotSettings );
    if( rc != NEXUS_SUCCESS ) { BERR_TRACE( rc ); goto exit; }

    /*configure keyslot entry parameters */
    NEXUS_KeySlot_GetEntrySettings( keyslotHandle, slotEntry, &keyslotEntrySettings );
    keyslotEntrySettings.algorithm = algorithm;
    keyslotEntrySettings.algorithmMode = algorithmMode;
    keyslotEntrySettings.terminationMode = NEXUS_KeySlotTerminationMode_eClear;
    keyslotEntrySettings.rPipeEnable = true;
    keyslotEntrySettings.gPipeEnable = true;
    rc = NEXUS_KeySlot_SetEntrySettings( keyslotHandle, slotEntry, &keyslotEntrySettings );
    if( rc != NEXUS_SUCCESS ) { BERR_TRACE( rc ); }

exit:
    *pKeyslotHandle = keyslotHandle;

    return rc;
}

static int test_keyladder_GenerateLevelKeyIv(
    NEXUS_KeySlotHandle keyslotHandle,
    NEXUS_KeySlotBlockEntry slotEntry,
    NEXUS_CryptographicAlgorithm algorithm,
    NEXUS_KeyLadderRootType rootType,
    NEXUS_KeyLadderMode mode,
    NEXUS_KeyLadderDestination destination,
    NEXUS_KeyLadderHandle * keyLadderhandle )
{
    NEXUS_KeyLadderAllocateSettings ladderAllocSettings;
    NEXUS_KeyLadderSettings ladderSettings;
    NEXUS_KeyLadderInfo keyLadderInfo;
    NEXUS_KeyLadderLevelKey levelKey;
    NEXUS_KeyLadderHandle handle = NULL;
    uint8_t procIn[16] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 };
    NEXUS_Error rc = NEXUS_UNKNOWN;

    if( !keyLadderhandle ) { return BERR_TRACE(NEXUS_INVALID_PARAMETER); }

    /* allocate a new key ladder */
    if( !(*keyLadderhandle) ) {

        NEXUS_KeyLadder_GetDefaultAllocateSettings( &ladderAllocSettings );
        ladderAllocSettings.owner = NEXUS_SecurityCpuContext_eHost;

        handle = NEXUS_KeyLadder_Allocate( NEXUS_ANY_ID, &ladderAllocSettings );
        if( !handle ) { return BERR_TRACE( NEXUS_NOT_AVAILABLE ); }

        rc = NEXUS_KeyLadder_GetInfo( handle, &keyLadderInfo );
        if( rc != NEXUS_SUCCESS ) { return BERR_TRACE( rc ); }
        printf( "KEYLADDER: Allocate Index[%d].\n", keyLadderInfo.index );

        *keyLadderhandle = handle;
    }
    else {
        handle = *keyLadderhandle;

        rc = NEXUS_KeyLadder_GetInfo( handle, &keyLadderInfo );
        if( rc != NEXUS_SUCCESS ) { return BERR_TRACE( rc ); }
    }

    NEXUS_KeyLadder_GetSettings( handle, &ladderSettings );
    ladderSettings.algorithm = algorithm;
    ladderSettings.operation = NEXUS_CryptographicOperation_eDecrypt;
    if( destination == NEXUS_KeyLadderDestination_eKeyslotIv || destination == NEXUS_KeyLadderDestination_eKeyslotIv2 ) {
        ladderSettings.mode = NEXUS_KeyLadderMode_eGeneralPurpose1;
    }
    else {
        ladderSettings.mode = mode;
    }


    printf( "KEYLADDER: Configure Index[%d].\n", keyLadderInfo.index );

    ladderSettings.root.type = rootType;
    ladderSettings.root.otpKeyIndex = 0;
    ladderSettings.root.askm.caVendorId = 0x1234;
    ladderSettings.root.askm.caVendorIdScope = NEXUS_KeyladderCaVendorIdScope_eFixed;
    ladderSettings.root.askm.stbOwnerSelect = NEXUS_KeyLadderStbOwnerIdSelect_eOne;
    rc = NEXUS_KeyLadder_SetSettings( handle, &ladderSettings );
    if( rc != NEXUS_SUCCESS ) { return BERR_TRACE( rc ); }

    printf( "KEYLADDER: Set Key Level 3  Index[%d].\n", keyLadderInfo.index );

    /* Set the keyladder level keys */
    NEXUS_KeyLadder_GetLevelKeyDefault( &levelKey );
    levelKey.level = 3;
    levelKey.ladderKeySize = 128;
    BKNI_Memcpy( levelKey.ladderKey, procIn, sizeof( levelKey.ladderKey ) );
    rc = NEXUS_KeyLadder_GenerateLevelKey( handle, &levelKey );
    if( rc != NEXUS_SUCCESS ) { return  BERR_TRACE( rc ); }

    printf( "KEYLADDER: Set Key Level 4  Index[%d]. destination[%d] entry[%d] \n", keyLadderInfo.index, destination, slotEntry );

    NEXUS_KeyLadder_GetLevelKeyDefault( &levelKey );
    levelKey.level = 4;
    levelKey.ladderKeySize = 128;
    levelKey.route.destination = destination;
    levelKey.route.keySlot.handle = keyslotHandle;
    levelKey.route.keySlot.entry = slotEntry;
    BKNI_Memcpy( levelKey.ladderKey, procIn, sizeof( levelKey.ladderKey ) );
    rc = NEXUS_KeyLadder_GenerateLevelKey( handle, &levelKey );
    if( rc != NEXUS_SUCCESS ) { return BERR_TRACE( rc ); }

    return rc;
}

static int test_keyladder_DMATransferUsingLevelKey(
    security_keyladderTestData * config )
{
    NEXUS_Error rc = NEXUS_UNKNOWN;

    rc = test_keyladder_SetKeyslot( config->levelKey.route.keySlot.entry,
                                    config->settings.algorithm,
                                    config->algorithmMode, &config->levelKey.route.keySlot.handle );
    if( rc != NEXUS_SUCCESS ) { BERR_TRACE( rc ); goto exit; }
    if( !config->levelKey.route.keySlot.handle ) { BERR_TRACE( rc ); goto exit; }

    rc = test_keyladder_GenerateLevelKeyIv( config->levelKey.route.keySlot.handle,
                                            config->levelKey.route.keySlot.entry,
                                            config->settings.algorithm,
                                            config->rootType,
                                            config->settings.mode,
                                            config->levelKey.route.destination, &config->handle );
    if( rc != NEXUS_SUCCESS ) { BERR_TRACE( rc ); goto exit; }
    if( !config->handle ) { BERR_TRACE( rc ); goto exit; }

    rc = securityUtil_DmaTransfer( config->levelKey.route.keySlot.handle, config->pSrc, config->pDest,
                                   NEXUS_DmaDataFormat_eBlock, config->data_size, false );
    if( rc != NEXUS_SUCCESS ) { BERR_TRACE( rc ); }

exit:
    NEXUS_KeySlot_Free( config->levelKey.route.keySlot.handle );
    config->levelKey.route.keySlot.handle = 0;

    NEXUS_KeyLadder_Free( config->handle );
    config->handle = 0;

    return rc;
}

int main(int argc, char **argv)
{
    security_keyladderTestData config;
    NEXUS_CryptographicAlgorithm algorithm[] = {
        NEXUS_CryptographicAlgorithm_e3DesAba,
        NEXUS_CryptographicAlgorithm_eAes128
    };

    NEXUS_KeyLadderMode mode[] = {
        NEXUS_KeyLadderMode_eCp_64_4,
        NEXUS_KeyLadderMode_eCp_128_4
    };

    unsigned      a,
                  m;
    NEXUS_Error   rc = NEXUS_UNKNOWN;

    BSTD_UNUSED(argc);
    BSTD_UNUSED(argv);

    /* Start NEXUS. */
    securityUtil_PlatformInit( false );

    BKNI_Memset( &config, 0, sizeof( config ) );
    config.data_size = sizeof( plainText );
    config.rootType = NEXUS_KeyLadderRootType_eCustomerKey;

    NEXUS_Memory_Allocate( config.data_size, NULL, ( void ** ) &config.pSrc );
    NEXUS_Memory_Allocate( config.data_size, NULL, ( void ** ) &config.pDest );

    /* Iterate and test the listed sub modes. */
    for( a = 0; a < sizeof( algorithm ) / sizeof( NEXUS_CryptographicAlgorithm ); a++ ) {
        for( m = 0; m < sizeof( mode ) / sizeof( NEXUS_KeyLadderMode ); m++ ) {
            config.settings.algorithm = algorithm[a];
            config.settings.mode = mode[m];

            /* AES Ecb mode */
            config.algorithmMode = NEXUS_CryptographicAlgorithmMode_eEcb;

            /* Using Otp key as the root key to encrypt the plain text. */
            config.levelKey.route.keySlot.entry = NEXUS_KeySlotBlockEntry_eCpsClear;
            config.levelKey.route.destination = NEXUS_KeyLadderDestination_eKeyslotKey;

            BKNI_Memcpy( config.pSrc, plainText, config.data_size );
            BKNI_Memset( config.pDest, 0, config.data_size );

            rc = test_keyladder_DMATransferUsingLevelKey( &config );
            if( rc != NEXUS_SUCCESS ) {
                printf( "ERROR with encryption of data\n" );
                goto exit;
            }

            if( !BKNI_Memcmp( config.pDest, plainText, config.data_size ) ) {
                printf( "    Test FAILED! plainText has not been encrypted. line[%d] \n", __LINE__ );
                rc = NEXUS_INVALID_PARAMETER;
                goto exit;
            }

            /* Using Otp key as the root key to decrypt the cipher text. */
            config.levelKey.route.keySlot.entry = NEXUS_KeySlotBlockEntry_eCpdClear;
            BKNI_Memcpy( config.pSrc, config.pDest, config.data_size );
            BKNI_Memset( config.pDest, 0, config.data_size );
            rc = test_keyladder_DMATransferUsingLevelKey( &config );
            if( rc != NEXUS_SUCCESS ) { printf( "ERROR with decryption of data\n" ); goto exit; }

            if( !BKNI_Memcmp( config.pDest, config.pSrc, config.data_size ) ) {
                printf( "    Test FAILED! cipher text has not been decrypted.\n" );
                rc = NEXUS_INVALID_PARAMETER;
                goto exit;
            }

            /* Check the decryption of the cipher is the same as the plain text. */
            if( BKNI_Memcmp( config.pDest, plainText, config.data_size ) ) {
                printf( "Test FAILED! The final result is not the expected values.\n" );
                DEBUG_PRINT_ARRAY( "PlainText:", config.data_size, plainText );
                DEBUG_PRINT_ARRAY( "Destination", config.data_size, config.pDest );
                rc = NEXUS_INVALID_PARAMETER;
                goto exit;
            }
            else {
                printf( "    Test PASSED with algorithm [%d], keyladder mode [%d]!\n", config.settings.algorithm,
                        config.settings.mode );
                rc = NEXUS_SUCCESS;
            }
        }
    }

  exit:

    if( config.pSrc ) NEXUS_Memory_Free( config.pSrc );
    if( config.pDest ) NEXUS_Memory_Free( config.pDest );

    /* Stop NEXUS. */
    securityUtil_PlatformUnInit( );

    return rc;
}

#else /* NEXUS_HAS_SECURITY */

#include <stdio.h>
int main(void)
{
    printf("This application is not supported on this platform!\n");
    return -1;
}

#endif

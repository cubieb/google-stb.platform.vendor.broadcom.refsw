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

#include "nexus_security_module.h"
#include "priv/nexus_security_priv.h"
#include "priv/nexus_core.h"
#include "bhsm.h"
#include "bhsm_verify_reg.h"
#include "bhsm_misc.h"
#include "bhsm_otpmsp.h"
#include "bsp_s_otp_common.h"
#include "nexus_security_regver_signatures.h"
#include "nexus_security_regver_key.h"


#if NEXUS_REGION_VERIFICATION_DUMP_FIRMWARE || NEXUS_REGION_VERIFICATION_DUMP_FIRMWARE_RAW
#include <stdio.h>
#endif


#define MIN(a,b) ((a<b)?(a):(b))

/* OTP enums */
#define OTP_ENUM_RAVE   (78)
#define OTP_ENUM_RAAGA0 (76)
#define OTP_ENUM_VIDEO  (77)
#define OTP_ENUM_RAAGA1 (193)
#define OTP_ENUM_VICE   (131)
#define OTP_ENUM_SID    (142)
#define OTP_ENUM_SAGE_FSBL (209)

/* Offset to paramters in signature header. */
#define SIGNATURE_HEADER_OFFSET_SVP_REL_VER    (1)
#define SIGNATURE_HEADER_OFFSET_CPU_TYPE       (2)
#define SIGNATURE_HEADER_OFFSET_MARKET_ID      (4)
#define SIGNATURE_HEADER_OFFSET_MARKET_ID_MASK (8)
#define SIGNATURE_HEADER_OFFSET_EPOCH_SELECT   (13)
#define SIGNATURE_HEADER_OFFSET_EPOCH_MASK     (14)
#define SIGNATURE_HEADER_OFFSET_EPOCH          (15)
#define SIGNATURE_HEADER_OFFSET_SIG_VERSION    (16)
#define SIGNATURE_HEADER_OFFSET_SIG_TYPE       (17)

#define DEFAULT_RSA_KEY_INDEX                  (2)
#define INVALID_RSA_KEY_INDEX                  (0xFFFFFFFF)

/*
    Data within a signature header.
*/
typedef struct {

    BCMD_MemAuth_CpuType_e cpuType;

    uint32_t marketId;
    uint32_t marketIdMask;

    uint8_t  epoch;
    uint8_t  epochMask;

   #if BHSM_ZEUS_VERSION >= BHSM_ZEUS_VERSION_CALC(4,2)
    uint8_t  svpFwReleaseVersion;
    BCMD_SignatureType_e signatureType;
    uint8_t  signatureVersion;
    uint8_t  epochSelect;
   #endif

}signatureHeaderData_t;



/*
    Verification data and state for one region.
*/
typedef struct {
    bool verificationSupported;               /* Region verifcation is supported for this component. */
    NEXUS_SecurityRegverRegionID regionId;    /* The Id of this region. */
    bool verificationRequired;                /* OTP requires region to be verifed. */
    bool verified;                            /* Region has been verifed. */
    bool configured;                          /* The region verification client has configured the region. */

    char* pSignature;                         /* points to signature of region. Includes header at end. */

    unsigned rsaKeyIndex;                     /* The RSA key index */
    bool enableInstructionChecker;            /* Required for SAGE/BHSM_SUPPORT_HDDTA */
    bool enableBackgroundChecker;             /* Required for SAGE */
    unsigned scmVersion;                      /* Required for BHSM_SUPPORT_HDDTA */

    uint8_t epochSelect;                      /* todo ... will be read from signature file */

    NEXUS_SecurityVirtualKeyladderID  keyLadderId;     /* Requried for SCPU FSBL region */
    NEXUS_SecurityKeySource           keyLadderLayer;  /* Requried for SCPU FSBL region*/

    char description[30];                     /* textual description of region. */

}regionData_t;

/*  Region Verification module data.  */
typedef struct {

    regionData_t region[NEXUS_REGVER_MAX_REGIONS];
    bool moduleInitialised;              /* the Module has previously been initialised. */
    bool defaultRsaKeyLoaded;

}regionVerificationModuleData_t;

static regionVerificationModuleData_t gRegVerModuleData; /* module data instance. */


BDBG_MODULE(nexus_security_verify_reg);

#if BHSM_ZEUS_VERSION >= BHSM_ZEUS_VERSION_CALC(4,1)
    #define NEXUS_REGVER_SIGNATURE_HEADER_SIZE (20)
#else
    #define NEXUS_REGVER_SIGNATURE_HEADER_SIZE (16)
#endif

#define NEXUS_REGVER_SIGNATURE_SIZE (256)
#define NEXUS_REGVER_SIGNATURE_PLUS_HEADER_SIZE (NEXUS_REGVER_SIGNATURE_SIZE+NEXUS_REGVER_SIGNATURE_HEADER_SIZE)


static NEXUS_Error verifyRegion( NEXUS_SecurityRegverRegionID regionId, void *pRegionAddress, unsigned regionSize );
static NEXUS_Error calculateCpuType( BCMD_MemAuth_CpuType_e *pCpuType, NEXUS_SecurityRegverRegionID region );
#define initialiseRegion(region,otpIndex) initialiseRegion_dbg(region,otpIndex,#region)
static void initialiseRegion_dbg( NEXUS_SecurityRegverRegionID regionId,
                                     BCMD_Otp_CmdMsp_e otpIndex,
                                     char * pRegionStr );
static regionData_t* getRegionData( NEXUS_SecurityRegverRegionID regionId );
static NEXUS_Error disableRegion( NEXUS_SecurityRegverRegionID regionId );

static void parseSignatureHeader( signatureHeaderData_t *pSigHeader, char* pSignature );


#if NEXUS_REGION_VERIFICATION_DUMP_FIRMWARE || NEXUS_REGION_VERIFICATION_DUMP_FIRMWARE_RAW
static void dumpFirmwareBinary( NEXUS_SecurityRegverRegionID regionId, void* pRegionAddress, unsigned regionSize );
#endif


static NEXUS_Error loadDefaultRegionVerificationKey(void);

/* load an individual predefined region signature. */
static NEXUS_Error loadSignature( unsigned regionId,  const uint8_t *pSigData )
{
    NEXUS_Error rc = NEXUS_SUCCESS;
    NEXUS_MemoryAllocationSettings memSetting;
    regionData_t *pRegionData = NULL;
    void **ppSig;

    BDBG_ENTER( loadSignature );

    BDBG_ASSERT( regionId < NEXUS_REGVER_MAX_REGIONS );

    pRegionData = getRegionData( regionId );

    if( pRegionData == NULL )
    {
        return NEXUS_SUCCESS; /* nothing to do .. region not enabled.*/
    }

    ppSig = (void**)(&pRegionData->pSignature);

    NEXUS_Memory_GetDefaultAllocationSettings( &memSetting );
    memSetting.alignment = 32;
    rc = NEXUS_Memory_Allocate( NEXUS_REGVER_SIGNATURE_PLUS_HEADER_SIZE, &memSetting, ppSig );
    if( rc != NEXUS_SUCCESS )
    {
        return BERR_TRACE( NEXUS_OUT_OF_DEVICE_MEMORY );
    }

    BKNI_Memcpy( *ppSig, pSigData, NEXUS_REGVER_SIGNATURE_PLUS_HEADER_SIZE );

    pRegionData->rsaKeyIndex = DEFAULT_RSA_KEY_INDEX; /* hardcoded signatures are signed with the default RSA KEY. */

    NEXUS_FlushCache( *ppSig, NEXUS_REGVER_SIGNATURE_PLUS_HEADER_SIZE );

    BDBG_LEAVE( loadSignature );
    return NEXUS_SUCCESS;
}

NEXUS_Error InitialiseSignatures( void )
{
    NEXUS_Error rc = NEXUS_SUCCESS;

    BDBG_ENTER( InitialiseSignatures );

    #ifdef SIGNATURE_REGION_0x00
    rc = loadSignature( 0x00, signatureRegion_0x00 );
    if( rc != NEXUS_SUCCESS ) { return BERR_TRACE( rc ); }
    #endif

    #ifdef SIGNATURE_REGION_0x01
    rc = loadSignature( 0x01, signatureRegion_0x01 );
    if( rc != NEXUS_SUCCESS ) { return BERR_TRACE( rc ); }
    #endif

    #ifdef SIGNATURE_REGION_0x02
    rc = loadSignature( 0x02, signatureRegion_0x02 );
    if( rc != NEXUS_SUCCESS ) { return BERR_TRACE( rc ); }
    #endif

    #ifdef SIGNATURE_REGION_0x03
    rc = loadSignature( 0x03, signatureRegion_0x03 );
    if( rc != NEXUS_SUCCESS ) { return BERR_TRACE( rc ); }
    #endif

    #ifdef SIGNATURE_REGION_0x04
    rc = loadSignature( 0x04, signatureRegion_0x04 );
    if( rc != NEXUS_SUCCESS ) { return BERR_TRACE( rc ); }
    #endif

    #ifdef SIGNATURE_REGION_0x05
    rc = loadSignature( 0x05, signatureRegion_0x05 );
    if( rc != NEXUS_SUCCESS ) { return BERR_TRACE( rc ); }
    #endif

    #ifdef SIGNATURE_REGION_0x06
    rc = loadSignature( 0x06, signatureRegion_0x06 );
    if( rc != NEXUS_SUCCESS ) { return BERR_TRACE( rc ); }
    #endif

    #ifdef SIGNATURE_REGION_0x07
    rc = loadSignature( 0x07, signatureRegion_0x07 );
    if( rc != NEXUS_SUCCESS ) { return BERR_TRACE( rc ); }
    #endif

    #ifdef SIGNATURE_REGION_0x08
    rc = loadSignature( 0x08, signatureRegion_0x08 );
    if( rc != NEXUS_SUCCESS ) { return BERR_TRACE( rc ); }
    #endif

    #ifdef SIGNATURE_REGION_0x09
    rc = loadSignature( 0x09, signatureRegion_0x09 );
    if( rc != NEXUS_SUCCESS ) { return BERR_TRACE( rc ); }
    #endif

    #ifdef SIGNATURE_REGION_0x0A
    rc = loadSignature( 0x0A, signatureRegion_0x0A );
    if( rc != NEXUS_SUCCESS ) { return BERR_TRACE( rc ); }
    #endif

    #ifdef SIGNATURE_REGION_0x0B
    rc = loadSignature( 0x0B, signatureRegion_0x0B );
    if( rc != NEXUS_SUCCESS ) { return BERR_TRACE( rc ); }
    #endif

    #ifdef SIGNATURE_REGION_0x0C
    rc = loadSignature( 0x0C, signatureRegion_0x0C );
    if( rc != NEXUS_SUCCESS ) { return BERR_TRACE( rc ); }
    #endif

    #ifdef SIGNATURE_REGION_0x0D
    rc = loadSignature( 0x0D, signatureRegion_0x0D );
    if( rc != NEXUS_SUCCESS ) { return BERR_TRACE( rc ); }
    #endif

    #ifdef SIGNATURE_REGION_0x0E
    rc = loadSignature( 0x0E, signatureRegion_0x0E );
    if( rc != NEXUS_SUCCESS ) { return BERR_TRACE( rc ); }
    #endif

    #ifdef SIGNATURE_REGION_0x0F
    rc = loadSignature( 0x0F, signatureRegion_0x0F );
    if( rc != NEXUS_SUCCESS ) { return BERR_TRACE( rc ); }
    #endif

    #ifdef SIGNATURE_REGION_0x10
    rc = loadSignature( 0x10, signatureRegion_0x10 );
    if( rc != NEXUS_SUCCESS ) { return BERR_TRACE( rc ); }
    #endif

    #ifdef SIGNATURE_REGION_0x11
    rc = loadSignature( 0x11, signatureRegion_0x11 );
    if( rc != NEXUS_SUCCESS ) { return BERR_TRACE( rc ); }
    #endif

    #ifdef SIGNATURE_REGION_0x12
    rc = loadSignature( 0x12, signatureRegion_0x12 );
    if( rc != NEXUS_SUCCESS ) { return BERR_TRACE( rc ); }
    #endif

    #ifdef SIGNATURE_REGION_0x13
    rc = loadSignature( 0x13, signatureRegion_0x13 );
    if( rc != NEXUS_SUCCESS ) { return BERR_TRACE( rc ); }
    #endif

    #ifdef SIGNATURE_REGION_0x14
    rc = loadSignature( 0x14, signatureRegion_0x14 );
    if( rc != NEXUS_SUCCESS ) { return BERR_TRACE( rc ); }
    #endif

    #ifdef SIGNATURE_REGION_0x15
    rc = loadSignature( 0x15, signatureRegion_0x15 );
    if( rc != NEXUS_SUCCESS ) { return BERR_TRACE( rc ); }
    #endif

    #ifdef SIGNATURE_REGION_0x16
    rc = loadSignature( 0x16, signatureRegion_0x16 );
    if( rc != NEXUS_SUCCESS ) { return BERR_TRACE( rc ); }
    #endif

    #ifdef SIGNATURE_REGION_0x17
    rc = loadSignature( 0x17, signatureRegion_0x17 );
    if( rc != NEXUS_SUCCESS ) { return BERR_TRACE( rc ); }
    #endif

    #ifdef SIGNATURE_REGION_0x18
    rc = loadSignature( 0x18, signatureRegion_0x18 );
    if( rc != NEXUS_SUCCESS ) { return BERR_TRACE( rc ); }
    #endif

    #ifdef SIGNATURE_REGION_0x19
    rc = loadSignature( 0x19, signatureRegion_0x19 );
    if( rc != NEXUS_SUCCESS ) { return BERR_TRACE( rc ); }
    #endif

    #ifdef SIGNATURE_REGION_0x1A
    rc = loadSignature( 0x1A, signatureRegion_0x1A );
    if( rc != NEXUS_SUCCESS ) { return BERR_TRACE( rc ); }
    #endif

    #ifdef SIGNATURE_REGION_0x1B
    rc = loadSignature( 0x1B, signatureRegion_0x1B );
    if( rc != NEXUS_SUCCESS ) { return BERR_TRACE( rc ); }
    #endif

    #ifdef SIGNATURE_REGION_0x1C
    rc = loadSignature( 0x1C, signatureRegion_0x1C );
    if( rc != NEXUS_SUCCESS ) { return BERR_TRACE( rc ); }
    #endif

    #ifdef SIGNATURE_REGION_0x1D
    rc = loadSignature( 0x1D, signatureRegion_0x1D );
    if( rc != NEXUS_SUCCESS ) { return BERR_TRACE( rc ); }
    #endif

    #ifdef SIGNATURE_REGION_0x1E
    rc = loadSignature( 0x1E, signatureRegion_0x1E );
    if( rc != NEXUS_SUCCESS ) { return BERR_TRACE( rc ); }
    #endif

    #ifdef SIGNATURE_REGION_0x1F
    rc = loadSignature( 0x1F, signatureRegion_0x1F );
    if( rc != NEXUS_SUCCESS ) { return BERR_TRACE( rc ); }
    #endif

    BDBG_LEAVE( InitialiseSignatures );
    return NEXUS_SUCCESS;
}


NEXUS_Error NEXUS_Security_RegionVerification_Init_priv( void )
{
    NEXUS_SecurityRegionInfoQuery  regionSatus;
    regionData_t *pRegionData;
    unsigned x;
    NEXUS_Error rc;

    BDBG_ENTER( NEXUS_Security_RegionVerification_Init_priv );
    NEXUS_ASSERT_MODULE();

    if( gRegVerModuleData.moduleInitialised == false )
    {
        BKNI_Memset( &gRegVerModuleData, 0, sizeof(gRegVerModuleData) );

        /* initialise module data. */
        initialiseRegion( BHSM_VerificationRegionId_eRave,          OTP_ENUM_RAVE   );
        initialiseRegion( BHSM_VerificationRegionId_eRaaga0,        OTP_ENUM_RAAGA0 );
        #if BHSM_ZEUS_VERSION >= BHSM_ZEUS_VERSION_CALC(3,0)
        initialiseRegion( BHSM_VerificationRegionId_eRaaga1,        OTP_ENUM_RAAGA1 );
        #endif

        #if BHSM_ZEUS_VERSION >= BHSM_ZEUS_VERSION_CALC(4,2)
        initialiseRegion( BHSM_VerificationRegionId_eVdec0_Il2A,    OTP_ENUM_VIDEO );
        initialiseRegion( BHSM_VerificationRegionId_eVdec0_Ila,     OTP_ENUM_VIDEO );
        initialiseRegion( BHSM_VerificationRegionId_eVdec0_Ola,     OTP_ENUM_VIDEO );
        initialiseRegion( BHSM_VerificationRegionId_eVdec1_Ils,     OTP_ENUM_VIDEO );
        initialiseRegion( BHSM_VerificationRegionId_eVdec1_Ols,     OTP_ENUM_VIDEO );
        initialiseRegion( BHSM_VerificationRegionId_eVdec2_Ila,     OTP_ENUM_VIDEO );
        initialiseRegion( BHSM_VerificationRegionId_eVdec2_Ola,     OTP_ENUM_VIDEO );
        #else
        initialiseRegion( BHSM_VerificationRegionId_eAvd0Inner,     OTP_ENUM_VIDEO );
        initialiseRegion( BHSM_VerificationRegionId_eAvd0Outer,     OTP_ENUM_VIDEO );
        initialiseRegion( BHSM_VerificationRegionId_eHvd0_Ila,      OTP_ENUM_VIDEO );
        initialiseRegion( BHSM_VerificationRegionId_eHvd0_Ola,      OTP_ENUM_VIDEO );
        initialiseRegion( BHSM_VerificationRegionId_eSvd0Bl,        OTP_ENUM_VIDEO );
        #endif
        initialiseRegion( BHSM_VerificationRegionId_eVice0Pic,      OTP_ENUM_VICE );
        initialiseRegion( BHSM_VerificationRegionId_eVice0MacroBlk, OTP_ENUM_VICE );
        initialiseRegion( BHSM_VerificationRegionId_eVice1Pic,      OTP_ENUM_VICE );
        initialiseRegion( BHSM_VerificationRegionId_eVice1MacroBlk, OTP_ENUM_VICE );
        initialiseRegion( BHSM_VerificationRegionId_eSid0,          OTP_ENUM_SID );

        #if BHSM_ZEUS_VERSION >= BHSM_ZEUS_VERSION_CALC(4,0)
        initialiseRegion( BHSM_VerificationRegionId_eScpuFsbl,      OTP_ENUM_SAGE_FSBL );
        #endif

        /* load static signatures. */
        if( ( rc = InitialiseSignatures( ) ) != NEXUS_SUCCESS )
        {
            return BERR_TRACE( rc ); /*failed to initailse signatures*/
        }

        /* Cleanup after abnormal applicaiton termination. (including Crtl^C app exit) */
        NEXUS_Security_RegionQueryInformation_priv( &regionSatus );
        for( x = 0; x < NEXUS_REGVER_MAX_REGIONS; x++ )
        {
            pRegionData = getRegionData( x );

            if( pRegionData && pRegionData->verificationSupported )
            {
                BDBG_MSG(("Region Status [0x%02X] [%02X] [%s] %s %s %s %s %s %s %s %s %s %s", x, regionSatus.regionStatus[x]
                                                           , pRegionData->description
                                                           , regionSatus.regionStatus[x] & REGION_STATUS_DEFINED       ? "defined"   :""
                                                           , regionSatus.regionStatus[x] & REGION_STATUS_VERIFIED      ? "verified"  :""
                                                           , regionSatus.regionStatus[x] & REGION_STATUS_ENABLED       ? "enabled"   :""
                                                           , regionSatus.regionStatus[x] & REGION_STATUS_FASTCHKSTART  ? "FtCkStart" :""
                                                           , regionSatus.regionStatus[x] & REGION_STATUS_FASTCHKFINISH ? "FtCkFin"   :""
                                                           , regionSatus.regionStatus[x] & REGION_STATUS_FASTCHKPADDINGRESULT ? "FtCkPaddingRes":""
                                                           , regionSatus.regionStatus[x] & REGION_STATUS_FASTCHKRESULT ? "FtCkBk"    :""
                                                           , regionSatus.regionStatus[x] & REGION_STATUS_BKCHKSTART    ? "BkCkStart" :""
                                                           , regionSatus.regionStatus[x] & REGION_STATUS_BHCHKFINISH   ? "BkCkFin"   :""
                                                           , regionSatus.regionStatus[x] & REGION_STATUS_BKCHKRESULT   ? "BkResult"  :"" ));

                if( regionSatus.regionStatus[x] & REGION_STATUS_ENABLED )
                {
                    disableRegion( pRegionData->regionId );
                }
            }
        }

        gRegVerModuleData.moduleInitialised = true;
    }
    else
    {
        /* lite initialisation if already initialised. Will be executed on exit from S3*/
        for( x = 0; x < NEXUS_REGVER_MAX_REGIONS; x++ )
        {
            pRegionData = getRegionData( x );

            if( pRegionData && pRegionData->verificationSupported )
            {
                pRegionData->verified = false;
                pRegionData->configured = false;
            }
        }
        gRegVerModuleData.defaultRsaKeyLoaded = false; /*default rsa key needs to be reloaded. */
    }

    BDBG_LEAVE( NEXUS_Security_RegionVerification_Init_priv );
    return NEXUS_SUCCESS;
}

void NEXUS_Security_RegionVerification_UnInit_priv( void )
{
    regionData_t *pRegionData;
    unsigned regionId = 0;

    BDBG_ENTER( NEXUS_Security_RegionVerification_UnInit_priv );
    NEXUS_ASSERT_MODULE();

    /* Disable region verification  */
    for( regionId = 0; regionId < NEXUS_REGVER_MAX_REGIONS; regionId++ )
    {
        pRegionData = getRegionData( regionId );
        if( pRegionData )
        {
            if( pRegionData->verificationSupported && pRegionData->verified )
            {
                disableRegion( regionId );
            }

            /* Free the signature memory */
            if( pRegionData->pSignature != NULL )
            {
                NEXUS_Memory_Free( pRegionData->pSignature );
                pRegionData->pSignature = NULL;
            }
        }
    }

    gRegVerModuleData.moduleInitialised = false;

    BDBG_LEAVE( NEXUS_Security_RegionVerification_UnInit_priv );
    return;
}



void NEXUS_Security_RegionGetDefaultConfig_priv ( NEXUS_SecurityRegverRegionID regionId, /* defaults may be region specific. */
                                                      NEXUS_SecurityRegionConfiguration *pConfiguration )
{
    BSTD_UNUSED( regionId );
    BDBG_ENTER( NEXUS_Security_RegionGetDefaultConfig_priv );
    NEXUS_ASSERT_MODULE();

    if( pConfiguration == NULL )
    {
       BERR_TRACE( NEXUS_INVALID_PARAMETER );
       return;
    }

    BKNI_Memset( pConfiguration, 0, sizeof( *pConfiguration ) );
    pConfiguration->rsaKeyIndex = DEFAULT_RSA_KEY_INDEX;

    /* By default, VKL is not used. When it is used, client will specify and configure it. */
    pConfiguration->keyLadderId = NEXUS_SecurityVirtualKeyladderID_eVKLDummy;

    BDBG_LEAVE( NEXUS_Security_RegionGetDefaultConfig_priv );
    return;
}

NEXUS_Error NEXUS_Security_RegionConfig_priv( NEXUS_SecurityRegverRegionID regionId, const NEXUS_SecurityRegionConfiguration *pConfiguration )
{
    NEXUS_MemoryAllocationSettings memSetting;
    regionData_t *pRegionData;
    NEXUS_Error rc = NEXUS_SUCCESS;

    BDBG_ENTER( NEXUS_Security_RegionConfig_priv );
    NEXUS_ASSERT_MODULE();

    if( pConfiguration == NULL ) { return BERR_TRACE(NEXUS_INVALID_PARAMETER); }

    pRegionData = getRegionData( regionId );
    if( pRegionData == NULL ) {
        BDBG_ERR(("[%s] Region [0x%02X] is NOT supported.", __FUNCTION__, regionId ));
        return NEXUS_INVALID_PARAMETER;
    }

    if( pRegionData->verificationRequired == false ) {
        BDBG_MSG(("[%s] Region [0x%02X][%s] Verification not required.", __FUNCTION__, regionId, pRegionData->description ));
        return NEXUS_SUCCESS;
    }

    if( pRegionData->configured )
    {
        /*BDBG_MSG(("REGION [0x%02X][%s] reconfiguring.", regionId, pRegionData->description ));*/
        /* continue */
    }

    pRegionData->rsaKeyIndex              = pConfiguration->rsaKeyIndex;
    pRegionData->enableInstructionChecker = pConfiguration->enableInstructionChecker;
    pRegionData->enableBackgroundChecker  = pConfiguration->enableBackgroundChecker;
    pRegionData->scmVersion               = pConfiguration->scmVersion;
    pRegionData->keyLadderId              = pConfiguration->keyLadderId;
    pRegionData->keyLadderLayer           = pConfiguration->keyLadderLayer;

    if( pConfiguration->signature.size > 0 )
    {
        if( pConfiguration->signature.size > NEXUS_REGVER_SIGNATURE_PLUS_HEADER_SIZE )
        {
            return BERR_TRACE( NEXUS_INVALID_PARAMETER );
        }

        if( pRegionData->pSignature == NULL ) /* Allocate memory for signature and header. */
        {
            NEXUS_Memory_GetDefaultAllocationSettings(&memSetting);
            memSetting.alignment = 32;
            rc = NEXUS_Memory_Allocate( NEXUS_REGVER_SIGNATURE_PLUS_HEADER_SIZE, &memSetting, (void **)&pRegionData->pSignature );
            if( rc != NEXUS_SUCCESS )
            {
                return BERR_TRACE( NEXUS_OUT_OF_DEVICE_MEMORY );
            }
        }

        BKNI_Memcpy( pRegionData->pSignature, pConfiguration->signature.p, pConfiguration->signature.size );
        NEXUS_FlushCache( (const void*)pRegionData->pSignature, pConfiguration->signature.size );
    }

    pRegionData->configured = true;

    BDBG_LEAVE( NEXUS_Security_RegionConfig_priv );
    return NEXUS_SUCCESS;
}


/*
Summary
    Verify the specifed region.
*/
NEXUS_Error NEXUS_Security_RegionVerifyEnable_priv( NEXUS_SecurityRegverRegionID regionId, void*pRegionAddress, unsigned regionSize )
{
    BERR_Code rc;
    BHSM_Handle hHsm;
    unsigned loopCount = 0;
    BHSM_RegionStatus_t regionStatus;
    regionData_t *pRegionData;

    BDBG_ENTER( NEXUS_Security_RegionVerifyEnable_priv );
    NEXUS_ASSERT_MODULE();

    #if NEXUS_REGION_VERIFICATION_DUMP_FIRMWARE || NEXUS_REGION_VERIFICATION_DUMP_FIRMWARE_RAW /*dump binaries */
     dumpFirmwareBinary( regionId, pRegionAddress, regionSize );
    #endif

    NEXUS_Security_GetHsm_priv( &hHsm );
    if( !hHsm )
    {
        return BERR_TRACE( NEXUS_INVALID_PARAMETER );
    }

    pRegionData = getRegionData( regionId );
    if( pRegionData == NULL ) {
        return BERR_TRACE( NEXUS_INVALID_PARAMETER ); /* Currently unsupported Region ID */
    }

    BDBG_MSG(("REGION [0x%02X][%s] Verifying  p[%p]size[%d].", regionId, pRegionData->description, pRegionAddress, regionSize ));
    BDBG_MSG(("REGION [0x%02X][%s] VKL#%d, Verifying  p[%p]size[%d].", regionId, pRegionData->description, pRegionData->keyLadderId, pRegionAddress, regionSize ));

    if( pRegionData->verificationRequired == false ) {
        BDBG_MSG(("[%s] Region [0x%02X][%s] Verification not required.", __FUNCTION__, regionId, pRegionData->description ));
        return NEXUS_SUCCESS;
    }

    if( pRegionData->verified == true ) {
        BDBG_WRN(("[%s] Region [0x%02X][%s] Already verified.", __FUNCTION__, regionId, pRegionData->description  ));
        return NEXUS_SUCCESS;
    }

    rc = verifyRegion( regionId, pRegionAddress, regionSize );
    if ( rc != NEXUS_SUCCESS )
    {
        if( rc == NEXUS_SECURITY_REGION_NOT_OTP_ENABLED )
        {
            BDBG_WRN(("Region [0x%02X][%s] not OTP enabled.", regionId, pRegionData->description ));
            return NEXUS_SUCCESS; /* region verification not requried */
        }

        return BERR_TRACE( NEXUS_INVALID_PARAMETER ); /* Region verificaiton failed. */
    }

    if( BHSM_RegionVerification_Enable( hHsm ) != BERR_SUCCESS )
    {
        return BERR_TRACE( NEXUS_INVALID_PARAMETER );
    }

    loopCount = 100;
    do
    {
        BKNI_Memset( &regionStatus, 0, sizeof(regionStatus) );

        rc = BHSM_RegionVerification_Status( hHsm, regionId, &regionStatus );
        if ( rc != NEXUS_SUCCESS ) /* fail */
        {
            BDBG_WRN(("[%s] Verification of region [0x%02x][%s] failed.", __FUNCTION__, regionId, pRegionData->description ));
            break;
        }

        if( regionStatus.state == BHSM_RegionVerificationStatus_eVerified )  /* pass */
        {
            break;
        }

        if( regionStatus.state == BHSM_RegionVerificationStatus_eInProgress ) /* in proress */
        {
            BKNI_Sleep (5);
            continue; /* go end of while loop */
        }

        /* fail */
        rc = BERR_TRACE( NEXUS_UNKNOWN );  /* region verification requried and not enabled. */
        BDBG_ERR(("[%s] region[%d][%s] status[0x%02X].", __FUNCTION__, regionId, pRegionData->description, regionStatus.state ));
        break;

    } while( loopCount-- );

    if( loopCount == 0 )
    {
        return BERR_TRACE( NEXUS_UNKNOWN );  /* Timed out waiting for region verification to complete. */
    }

    pRegionData->verified = true;

    BDBG_LEAVE( NEXUS_Security_RegionVerifyEnable_priv );
    return NEXUS_SUCCESS;
}


/*
Summary
    Disable region verification. Loop until verifcation has been disabled.
*/
void NEXUS_Security_RegionVerifyDisable_priv( NEXUS_SecurityRegverRegionID regionId )
{
    BHSM_Handle hHsm;
    regionData_t *pRegionData;

    BDBG_ENTER( NEXUS_Security_RegionVerifyDisable_priv );
    NEXUS_ASSERT_MODULE();

    NEXUS_Security_GetHsm_priv( &hHsm );
    if( !hHsm )
    {
        BERR_TRACE( NEXUS_INVALID_PARAMETER );
        return;
    }

    pRegionData = getRegionData( regionId );
    if( pRegionData == NULL ) {
        BERR_TRACE( NEXUS_INVALID_PARAMETER ); /* Currently unsupported Region ID */
        return;
    }

    if( pRegionData->verificationRequired == false ) {
        BDBG_MSG(("[%s] Region [0x%02X][%s] Verification not OTP enalbed.", __FUNCTION__, regionId, pRegionData->description ));
        return;
    }

    if( pRegionData->verified != true ) {
        BDBG_WRN(("[%s] Region [0x%02X][%s] Not verified.", __FUNCTION__, regionId, pRegionData->description ));
        return;
    }

    if( disableRegion( regionId ) != NEXUS_SUCCESS )
    {
        BERR_TRACE( NEXUS_UNKNOWN );
    }

    BDBG_LEAVE( NEXUS_Security_RegionVerifyDisable_priv );
    return;
}






static NEXUS_Error verifyRegion( NEXUS_SecurityRegverRegionID regionId, void *pRegionAddress, unsigned regionSize )
{
    BHSM_Handle hHsm;
    BHSM_RegionConfiguration_t  regionConfiguration;
    BERR_Code rc = BERR_SUCCESS;
    regionData_t *pRegionData;
    NEXUS_Addr startAddress = 0;
    NEXUS_Addr endAddress = 0;
    signatureHeaderData_t sigHeader;

    BDBG_ENTER( verifyRegion );

    NEXUS_Security_GetHsm_priv (&hHsm);
    if ( !hHsm || !pRegionAddress )
    {
        return BERR_TRACE( NEXUS_INVALID_PARAMETER );
    }

    pRegionData = getRegionData( regionId );
    if( pRegionData == NULL ) {
        return BERR_TRACE( NEXUS_INVALID_PARAMETER ); /* Currently unsupported Region ID */
    }

    if( pRegionData->pSignature == NULL )
    {
        BDBG_ERR(("No signature for Region [0x%02X].", regionId ));
        return BERR_TRACE( NEXUS_INVALID_PARAMETER ); /* Signature not defined; neither statically, nor via NEXUS_Security_RegionConfig_priv */
    }

    if( gRegVerModuleData.defaultRsaKeyLoaded == false && pRegionData->rsaKeyIndex == DEFAULT_RSA_KEY_INDEX )
    {
        rc = loadDefaultRegionVerificationKey( );
        if( rc != NEXUS_SUCCESS )
        {
            /* failed to load default key required to authenticate region verification signatures. */
            return BERR_TRACE( NEXUS_SECURITY_FAILED_TO_LOAD_REGVER_KEY );
        }

        gRegVerModuleData.defaultRsaKeyLoaded = true;
    }

    /* parse the configuration parameters that are associated with the signature. */
    parseSignatureHeader( &sigHeader, pRegionData->pSignature );

    BKNI_Memset( &regionConfiguration, 0, sizeof(regionConfiguration));

    if( regionId == NEXUS_SecurityRegverRegionID_eRave )
    {
        regionConfiguration.region.startAddress = 0;
        regionConfiguration.region.startAddressMsb = 0;
        regionConfiguration.region.endAddress = regionSize -1;
        regionConfiguration.region.endAddressMsb = 0;
    }
    else
    {
        startAddress = NEXUS_AddrToOffset( pRegionAddress );
        endAddress = NEXUS_AddrToOffset((void*)((char*)pRegionAddress + regionSize - 1));
        regionConfiguration.region.startAddress       = (uint32_t)(startAddress & 0xFFFFFFFF);
        regionConfiguration.region.startAddressMsb    = (uint32_t)((startAddress>>32) & 0xFF);
        regionConfiguration.region.endAddress         = (uint32_t)(endAddress & 0xFFFFFFFF);
        regionConfiguration.region.endAddressMsb      = (uint32_t)((endAddress>>32) & 0xFF);
    }
    startAddress = NEXUS_AddrToOffset( pRegionData->pSignature );
    endAddress   = NEXUS_AddrToOffset((void*)((char*)pRegionData->pSignature + NEXUS_REGVER_SIGNATURE_SIZE - 1));
    regionConfiguration.signature.startAddress    = (uint32_t)(startAddress & 0xFFFFFFFF);
    regionConfiguration.signature.startAddressMsb = (uint32_t)((startAddress>>32) & 0xFF);
    regionConfiguration.signature.endAddress      = (uint32_t)(endAddress & 0xFFFFFFFF);
    regionConfiguration.signature.endAddressMsb   = (uint32_t)((endAddress>>32) & 0xFF);
    regionConfiguration.ucIntervalCheckBw        = 0x10;
    regionConfiguration.SCBBurstSize             = BCMD_ScbBurstSize_e64;
    regionConfiguration.unRSAKeyID               = pRegionData->rsaKeyIndex;
    regionConfiguration.codeRelocatable          = BHSM_CodeLocationRule_eRelocatable;

    if( calculateCpuType ( &(regionConfiguration.cpuType), regionId ) != NEXUS_SUCCESS )
    {
        return BERR_TRACE( NEXUS_INVALID_PARAMETER ); /* Unsupported region. */
    }

    regionConfiguration.unEpoch                  = sigHeader.epoch;
   #if BHSM_ZEUS_VERSION >= BHSM_ZEUS_VERSION_CALC(4,2)
    regionConfiguration.svpFwReleaseVersion  = sigHeader.svpFwReleaseVersion;
    regionConfiguration.ucEpochSel              = sigHeader.epochSelect;
    regionConfiguration.ucSigVersion         = sigHeader.signatureVersion;
    regionConfiguration.ucSigType            = sigHeader.signatureType;
   #endif
   #if BHSM_ZEUS_VERSION >= BHSM_ZEUS_VERSION_CALC(2,0)
    regionConfiguration.verifyFailAction         = BCMD_MemAuth_ResetOnVerifyFailure_eNoReset; /* Ignored for  most region IDs*/
    regionConfiguration.unEpochMask              = sigHeader.epochMask;
    regionConfiguration.unMarketID               = sigHeader.marketId;
    regionConfiguration.unMarketIDMask           = sigHeader.marketIdMask;
   #endif
   #if BHSM_ZEUS_VERSION >= BHSM_ZEUS_VERSION_CALC(3,0)
    if ( regionConfiguration.cpuType == BCMD_MemAuth_CpuType_eScpu )  /* Support for SCPU */
    {
        regionConfiguration.keyLayer                 = pRegionData->keyLadderLayer;
        regionConfiguration.vkl                      = pRegionData->keyLadderId;
        regionConfiguration.bgCheck                  = pRegionData->enableBackgroundChecker;
        regionConfiguration.instrChecker             = pRegionData->enableInstructionChecker;
        regionConfiguration.SCMVersion               = pRegionData->scmVersion;
    }
   #endif

    rc = BHSM_RegionVerification_Configure( hHsm, regionId, &regionConfiguration );
    if( rc == BHSM_STATUS_REGION_VERIFICATION_NOT_ENABLED )
    {
        BDBG_MSG(("[%s] Region [0x%02X] not OTP enabled.", __FUNCTION__, regionId));
        return NEXUS_SECURITY_REGION_NOT_OTP_ENABLED;
    }
    if ( rc != BERR_SUCCESS )
    {
        return BERR_TRACE( NEXUS_NOT_SUPPORTED );
    }

    BDBG_LEAVE( verifyRegion );
    return NEXUS_SUCCESS;
}



NEXUS_Error disableRegion( NEXUS_SecurityRegverRegionID regionId )
{
    BHSM_Handle hHsm;
    BHSM_VerifcationStatus_t verificationStatus;
    bool regionDefined = true;
    BERR_Code rc = BERR_SUCCESS;
    regionData_t *pRegionData;
    unsigned loopCount;

    BDBG_ENTER( disableRegion );

    NEXUS_Security_GetHsm_priv( &hHsm );
    if ( hHsm == NULL )
    {
        return BERR_TRACE( NEXUS_INVALID_PARAMETER );
    }

    pRegionData = getRegionData( regionId );
    if( pRegionData == NULL ) {
        return BERR_TRACE( NEXUS_INVALID_PARAMETER ); /* Currently unsupported Region ID */
    }

    if( pRegionData->verificationRequired == false ) {
        BDBG_MSG(("[%s] Region [0x%02X][%s] Verification not required.", __FUNCTION__, regionId,pRegionData->description  ));
        return NEXUS_SUCCESS;
    }

    BDBG_MSG(("REGION [0x%02X][%s] disabling", regionId, pRegionData->description ));

    /* disable even if pRegionData->verified indicates that its not currently enabled. */

    rc = BHSM_RegionVerification_Disable( hHsm, regionId );
    if( rc == BHSM_STATUS_REGION_VERIFICATION_NOT_ENABLED )
    {
        BDBG_WRN(("[%s]Region [0x%02X][%s] not OTP enabled.", __FUNCTION__, regionId, pRegionData->description ));
        return NEXUS_SECURITY_REGION_NOT_OTP_ENABLED;
    }
    if( rc != BERR_SUCCESS )
    {
        return BERR_TRACE( NEXUS_NOT_SUPPORTED );
    }

    BKNI_Memset( &verificationStatus, 0, sizeof(verificationStatus) );

    loopCount = 100;

    /* wait until the region becomes undefined. */
    do
    {
        if( ( rc = BHSM_RegionVerification_QueryStatus( hHsm, &verificationStatus ) ) != BERR_SUCCESS )
        {
            return BERR_TRACE( NEXUS_NOT_SUPPORTED );   /* error reading status of verification regions */
        }

        if( verificationStatus.region[regionId] & REGION_STATUS_DEFINED ||
            verificationStatus.region[regionId] & REGION_STATUS_ENABLED )
        {
            BKNI_Sleep(5);
        }
        else
        {
            regionDefined = false;  /* region has become undefined */
        }

    } while( regionDefined && --loopCount );

    pRegionData->verified = false;

    BDBG_LEAVE( disableRegion );
    return NEXUS_SUCCESS;
}



NEXUS_Error NEXUS_Security_RegionQueryInformation_priv( NEXUS_SecurityRegionInfoQuery  *pRegionQuery )
{
    BHSM_Handle hHsm;
    BERR_Code rc;
    uint32_t index = 0;
    BHSM_VerifcationStatus_t status;

    BDBG_ENTER( NEXUS_Security_RegionQueryInformation_priv );
    NEXUS_ASSERT_MODULE();

    if( !pRegionQuery ) {
        return BERR_TRACE( NEXUS_INVALID_PARAMETER );
    }

    NEXUS_Security_GetHsm_priv (&hHsm);
    if( !hHsm ){
        return BERR_TRACE( NEXUS_INVALID_PARAMETER );
    }

    BKNI_Memset( &status, 0, sizeof(status) );

    if( ( rc = BHSM_RegionVerification_QueryStatus( hHsm,  &status ) ) != BERR_SUCCESS )
    {
        return BERR_TRACE( MAKE_HSM_ERR( rc ) );
    }

    BDBG_MSG(("[%s] Query Complete", __FUNCTION__ ));

    BDBG_CASSERT( MAX_REGION_NUMBER == NEXUS_REGVER_MAX_REGIONS );

    for (index = 0; index < NEXUS_REGVER_MAX_REGIONS; index++)
    {
        pRegionQuery->regionStatus[index] = status.region[index];
    }

    BDBG_LEAVE( NEXUS_Security_RegionQueryInformation_priv );
    return NEXUS_SUCCESS;
}

/*
Summary
    Determine the CPU type from the region ID
*/
static NEXUS_Error calculateCpuType( BCMD_MemAuth_CpuType_e *pCpuType, NEXUS_SecurityRegverRegionID region )
{
    BERR_Code rc = NEXUS_SUCCESS;

    BDBG_ENTER( calculateCpuType );

    switch( region )
    {
        case NEXUS_SecurityRegverRegionID_eRave:
        {
            *pCpuType = BCMD_MemAuth_CpuType_eRave;
            break;
        }
        case NEXUS_SecurityRegverRegionID_eVice0Pic:
        case NEXUS_SecurityRegverRegionID_eVice0MacroBlk:
        case NEXUS_SecurityRegverRegionID_eVice1Pic:
        case NEXUS_SecurityRegverRegionID_eVice1MacroBlk:
        {
            *pCpuType = BCMD_MemAuth_CpuType_eVice;
            break;
        }
        case NEXUS_SecurityRegverRegionID_eRaaga0:
        case NEXUS_SecurityRegverRegionID_eRaaga1:
        {
            *pCpuType = BCMD_MemAuth_CpuType_eRaaga;
            break;
        }
        case NEXUS_SecurityRegverRegionID_eSid0:
        {
            *pCpuType = BCMD_MemAuth_CpuType_eSid;
            break;
        }

        #if BHSM_ZEUS_VERSION >= BHSM_ZEUS_VERSION_CALC(3,0)
        case NEXUS_SecurityRegverRegionID_eScpuFsbl:
        case NEXUS_SecurityRegverRegionID_eScpuOsApp:
        case NEXUS_SecurityRegverRegionID_eScpuGeneric:
        case NEXUS_SecurityRegverRegionID_eScpuScm:
        {
            *pCpuType = BCMD_MemAuth_CpuType_eScpu;
            break;
        }
        #endif

        #if BHSM_ZEUS_VERSION <= BHSM_ZEUS_VERSION_CALC(4,1)
        case NEXUS_SecurityRegverRegionID_eAvd0Inner:
        case NEXUS_SecurityRegverRegionID_eAvd0Outer:
        {
            *pCpuType = BCMD_MemAuth_CpuType_eAvd;
            break;
        }
        #endif

        #if BHSM_ZEUS_VERSION <= BHSM_ZEUS_VERSION_CALC(3,0)
        case NEXUS_SecurityRegverRegionID_eSvd0Inner:
        case NEXUS_SecurityRegverRegionID_eSvd0Outer:
        case NEXUS_SecurityRegverRegionID_eSvd0Bl:
        {
            *pCpuType = BCMD_MemAuth_CpuType_eSvd;
            break;
        }
        #endif
        #if BHSM_ZEUS_VERSION == BHSM_ZEUS_VERSION_CALC(4,1) /*only supported on Zeus4.1*/
        case NEXUS_SecurityRegverRegionID_eHVD1_ILA:
        case NEXUS_SecurityRegverRegionID_eHVD1_OLA:
        case NEXUS_SecurityRegverRegionID_eHVD2_ILA:
        case NEXUS_SecurityRegverRegionID_eHVD2_OLA:
        {
            *pCpuType = BCMD_MemAuth_CpuType_eHvd;
            break;
        }
        #endif
        #if BHSM_ZEUS_VERSION >= BHSM_ZEUS_VERSION_CALC(4,2)
        case NEXUS_SecurityRegverRegionID_eVDEC0_IL2A:
        case NEXUS_SecurityRegverRegionID_eVDEC0_ILA:
        case NEXUS_SecurityRegverRegionID_eVDEC0_OLA:
        case NEXUS_SecurityRegverRegionID_eVDEC1_ILA:
        case NEXUS_SecurityRegverRegionID_eVDEC1_OLA:
        case NEXUS_SecurityRegverRegionID_eVDEC2_ILA:
        case NEXUS_SecurityRegverRegionID_eVDEC2_OLA:
        {
            *pCpuType = BCMD_MemAuth_CpuType_eVdec;
            break;
        }
        #endif
        #if 0
        case NEXUS_SecurityRegverRegionID_eHvdIla:
        case NEXUS_SecurityRegverRegionID_eHvdOla:
        case NEXUS_SecurityRegverRegionID_eVDEC0_OLA:
        case NEXUS_SecurityRegverRegionID_eSvd0Bl:
        case NEXUS_SecurityRegverRegionID_eRaaga0IntScm:
        case NEXUS_SecurityRegverRegionID_eRaaga0IntAud:
        #endif
        default:
        {
            BDBG_ERR(("Region [0x%02X] not mapped to CPU type", region ));
            rc = BERR_TRACE( NEXUS_INVALID_PARAMETER ); /* Unsuported region. */
        }
    }

    BDBG_LEAVE( calculateCpuType );
    return rc;
}


/*
Summary
    Function to dump the FIRMWARE binary to file.
*/
#if NEXUS_REGION_VERIFICATION_DUMP_FIRMWARE || NEXUS_REGION_VERIFICATION_DUMP_FIRMWARE_RAW
static void dumpFirmwareBinary( NEXUS_SecurityRegverRegionID regionId, void* pRegionAddress, unsigned regionSize )
{
    FILE *pFile = NULL;
    char fileName[256] = {0};
    unsigned written = 0;
    BCMD_MemAuth_CpuType_e cpuType;
    NEXUS_Error rc;
    char buffer[4];
    unsigned i;
    regionData_t *pRegionData;

    BDBG_ENTER( dumpFirmwareBinary );

    pRegionData = getRegionData( regionId );
    if( pRegionData == NULL ) {
        BERR_TRACE( NEXUS_INVALID_PARAMETER ); /* Currently unsupported Region ID */
        return;
    }

    if( regionSize > 0)
    {
        rc = calculateCpuType( &cpuType, regionId );
        if( rc != NEXUS_SUCCESS )
        {
            BERR_TRACE(rc);
            return;
        }

        sprintf( fileName, "firmware_zeus%d%d_cpuType%02d_region0x%02X_%s%s.bin", NEXUS_SECURITY_ZEUS_VERSION_MAJOR
                                                                             , NEXUS_SECURITY_ZEUS_VERSION_MINOR
                                                                             , (unsigned)cpuType
                                                                             , regionId
                                                                             , pRegionData->description
                                                                             #if NEXUS_REGION_VERIFICATION_DUMP_FIRMWARE_RAW
                                                                             , "_raw"
                                                                             #else
                                                                             , "_formatted"
                                                                             #endif
                                                                             );

        BDBG_WRN(( "Dumping Firmware to %s %p size[%d]", fileName, pRegionAddress, regionSize ));

        pFile = fopen( fileName, "wb" );

        if( pFile == NULL )
        {
            BDBG_ERR(( "Could not open file %s to dump firmware. Make sure to do chmod 777 -R <directory from which the app executable is being run>" ));
            return;
        }

        if( regionId == NEXUS_SecurityRegverRegionID_eRave )  /* reverse endian for RAVE .. and mask out some bytes!*/
        {
            for ( i = 0; i < (regionSize/4); i++ )
            {
                unsigned tmp = ((uint32_t*)pRegionAddress)[i];
                buffer[0] = 0/*tmp >> 24*/;
                buffer[1] = (tmp>>16) & 0x3F;
                buffer[2] = (tmp>>8 ) & 0xFF;
                buffer[3] = (tmp    ) & 0xFF;
                written += fwrite( buffer, 1, 4, pFile );
            }
        }
        else
        {
            for ( i = 0; i < (regionSize/4); i++ )
            {
                unsigned tmp = ((uint32_t*)pRegionAddress)[i];
                buffer[0] = (tmp >> 24);
                buffer[1] = (tmp >> 16) & 0xFF;
                buffer[2] = (tmp >> 8 ) & 0xFF;
                buffer[3] = (tmp      ) & 0xFF;
                written += fwrite( buffer, 1, 4, pFile );
            }
        }

        if( written != regionSize )
        {
            BDBG_ERR(( "*****Failed to write FW [%s] size[%d] written[%d]", fileName, regionSize, written ));
        }
    }

    #ifndef NEXUS_REGION_VERIFICATION_DUMP_FIRMWARE_RAW
    {
        uint8_t header[256] = {0}; /* data to be added to end of firmware file for signing. */
        unsigned headerLength = 0;

        /* See command manual for description of header*/
        header[SIGNATURE_HEADER_OFFSET_CPU_TYPE]  = cpuType & 0xFF;
        BKNI_Memset( &header[SIGNATURE_HEADER_OFFSET_MARKET_ID_MASK], 0xFF, 4);
        header[SIGNATURE_HEADER_OFFSET_EPOCH_MASK]   = 0xFF;
        headerLength = 16;
       #if BHSM_ZEUS_VERSION >= BHSM_ZEUS_VERSION_CALC(4,2)
        header[SIGNATURE_HEADER_OFFSET_EPOCH_SELECT] = pRegionData->epochSelect;
        header[SIGNATURE_HEADER_OFFSET_SIG_VERSION]  = 0x01;  /*Default signature version*/
        header[SIGNATURE_HEADER_OFFSET_SIG_TYPE]     = BCMD_SigType_eCode; /* Default signature type */
        headerLength = 20; /*update length*/
       #endif

        for( i = 0, written = 0; i < headerLength; i++ )
        {
            written += fwrite( &header[i], 1, 1, pFile );
        }

        if( written != headerLength )
        {
            BDBG_ERR(( "*****Failed to write FW extension [%s] size[%d] written[%d]", fileName, headerLength, written ));
        }
    }
    #endif

    if( pFile ) fclose( pFile );

    BDBG_LEAVE( dumpFirmwareBinary );
    return;
}
#endif

/*
Summary
    Extract configuration paramters embedded in the augmented/extended signature.
*/
static void parseSignatureHeader( signatureHeaderData_t *pSigHeader, char* pSignature )
{
    uint8_t *pRaw;

    BDBG_ASSERT( pSigHeader );
    BDBG_ASSERT( pSignature );

    BDBG_ENTER( parseSignatureHeader );

    BKNI_Memset( pSigHeader, 0, sizeof(*pSigHeader) );

    pRaw = (uint8_t*)(pSignature + NEXUS_REGVER_SIGNATURE_SIZE); /* header is just after the signature */


    pSigHeader->cpuType  = pRaw[SIGNATURE_HEADER_OFFSET_CPU_TYPE];
    pSigHeader->marketId =     (pRaw[SIGNATURE_HEADER_OFFSET_MARKET_ID+0] << 24) +
                               (pRaw[SIGNATURE_HEADER_OFFSET_MARKET_ID+1] << 16) +
                               (pRaw[SIGNATURE_HEADER_OFFSET_MARKET_ID+2] << 8)  +
                               (pRaw[SIGNATURE_HEADER_OFFSET_MARKET_ID+3] << 0);

    pSigHeader->marketIdMask = (pRaw[SIGNATURE_HEADER_OFFSET_MARKET_ID_MASK+0] << 24) +
                               (pRaw[SIGNATURE_HEADER_OFFSET_MARKET_ID_MASK+1] << 16) +
                               (pRaw[SIGNATURE_HEADER_OFFSET_MARKET_ID_MASK+2] << 8)  +
                               (pRaw[SIGNATURE_HEADER_OFFSET_MARKET_ID_MASK+3] << 0);

    pSigHeader->epochMask =  pRaw[SIGNATURE_HEADER_OFFSET_EPOCH_MASK];
    pSigHeader->epoch =  pRaw[SIGNATURE_HEADER_OFFSET_EPOCH];
   #if BHSM_ZEUS_VERSION >= BHSM_ZEUS_VERSION_CALC(4,2)
    pSigHeader->svpFwReleaseVersion = pRaw[SIGNATURE_HEADER_OFFSET_SVP_REL_VER];
    pSigHeader->epochSelect = pRaw[SIGNATURE_HEADER_OFFSET_EPOCH_SELECT];
    pSigHeader->signatureVersion =  pRaw[SIGNATURE_HEADER_OFFSET_SIG_VERSION];
    pSigHeader->signatureType =  pRaw[SIGNATURE_HEADER_OFFSET_SIG_TYPE];
   #endif

    BDBG_LEAVE( parseSignatureHeader );
    return;
}

/*
Summary
    Copy the last part of a enumerator from string ... i.e., "Description" from  "Enumerator_eDescription"
*/
void cropDescriptionFromStr( char* pDest, unsigned destSize, char* pStr )
{
    char* pLocation = NULL;
    unsigned boundsCheck = 120; /*stop run away*/

    if(!pDest) return;

    BKNI_Memset( pDest, 0, destSize );

    if(!pStr) return;

    while( *pStr && boundsCheck-- )
    {
        if(*pStr == '_' && *(pStr+1) == 'e')
        {
            pLocation = pStr+2;
        }
        pStr++;
    }

    if((pLocation == NULL) || (boundsCheck == 0)) /*nothing found or runaway*/
    {
        BKNI_Memcpy( pDest, "unknown", 7 );
        return;
    }

    BKNI_Memcpy( pDest, pLocation, MIN( (unsigned)(destSize-1), (unsigned)(pStr-pLocation)) );

    return;
}

/*
Summary
    Return module data associated with region.
*/
static regionData_t* getRegionData( NEXUS_SecurityRegverRegionID regionId )
{
    regionData_t* pRegionData = NULL;

    if( regionId >= NEXUS_REGVER_MAX_REGIONS ){
        BERR_TRACE( NEXUS_UNKNOWN );
        return NULL;
    }

    pRegionData = &gRegVerModuleData.region[regionId];

    if( pRegionData->verificationSupported == false ){
        return NULL;
    }

    return pRegionData;
}


/*
Summary
    Load key2 for region verification
*/
static BERR_Code loadDefaultRegionVerificationKey( void )
{
    NEXUS_Error rc;
    unsigned char *pKey = NULL;
    NEXUS_MemoryAllocationSettings memSetting;
    unsigned int inBuffer[16], outBuffer[16], actualOutSize;

    BDBG_ENTER( loadDefaultRegionVerificationKey );

    NEXUS_Memory_GetDefaultAllocationSettings(&memSetting);
    memSetting.alignment = 32;
    rc = NEXUS_Memory_Allocate( sizeof(gRegionVerificationKey2), &memSetting, (void**)&pKey );
    if ( rc != NEXUS_SUCCESS || pKey == NULL )
    {
        return BERR_TRACE( NEXUS_OUT_OF_DEVICE_MEMORY ); /* failed to allocate memory for region verification key.  */
    }
    BKNI_Memcpy( pKey, gRegionVerificationKey2, sizeof(gRegionVerificationKey2) );
    NEXUS_FlushCache( (const void*)pKey, sizeof(gRegionVerificationKey2) );

    inBuffer[0] = 0x00000010;
    inBuffer[1] = 0x00000022;
    inBuffer[2] = 0xabcdef00;
    inBuffer[3] = 0xc955aa36;
    inBuffer[4] = 0x789a000c;
    inBuffer[5] = 0x00000002;
    inBuffer[6] = 0x00000000;
    inBuffer[7] = NEXUS_AddrToOffset( (void *)pKey );


    rc = NEXUS_Security_SubmitRawCommand (
            inBuffer,    /* attr{nelem=sizeInBuffer;reserved=90} */
            8,        /* size of pInBuffer in integers */
            outBuffer,         /* [out] attr{nelem=sizeOutBuffer;reserved=90} */
            6,        /* size of pOutBuffer in integers */
            &actualOutSize      /* [out] number of integers written into pOutBuffer */
    );
    NEXUS_Memory_Free( pKey );

    if ( rc || (outBuffer[5]!=0 ) )
    {
        BDBG_WRN(( "Failed to load Region Verification Key, key2" ));
        return NEXUS_INVALID_PARAMETER;
    }

    BDBG_LEAVE( loadDefaultRegionVerificationKey );
    return NEXUS_SUCCESS;
}


/*
Summary
    initialiseRegion_dbg is the debug implementation of initialiseRegion. It configure the initial state of each region. I needs to be called during platform initialisation.
*/
static void initialiseRegion_dbg( NEXUS_SecurityRegverRegionID regionId,
                                     BCMD_Otp_CmdMsp_e otpIndex,
                                     char * pRegionStr )
{
    BHSM_ReadMspIO_t otp;
    BERR_Code rc = BERR_SUCCESS;
    BHSM_Handle hHsm;
    regionData_t *pRegionData;

    BDBG_ENTER(initialiseRegion );

    BDBG_ASSERT( regionId < NEXUS_REGVER_MAX_REGIONS );

    pRegionData = &gRegVerModuleData.region[regionId];
    pRegionData->regionId = regionId;
    pRegionData->verificationSupported = true;
    pRegionData->verificationRequired  = false; /* may change below. */
    pRegionData->rsaKeyIndex = INVALID_RSA_KEY_INDEX; /* initialise to invalid rsa key index. */

    NEXUS_Security_GetHsm_priv (&hHsm);
    if( !hHsm ) {
        BERR_TRACE( NEXUS_INVALID_PARAMETER );
        return;
    }

    otp.readMspEnum = otpIndex;
    rc = BHSM_ReadMSP( hHsm, &otp );
    if( rc != BERR_SUCCESS ) {
        BERR_TRACE( rc ); /* ERROR reading OTP. Verification of Region is assumed to be not required.  */
        return;
    }

    if( otp.aucMspData[3] ) /* OTP in BYTE 3, LSB */
    {
        pRegionData->verificationRequired = true;
    }

    cropDescriptionFromStr( pRegionData->description, sizeof(pRegionData->description), pRegionStr );

    BDBG_LEAVE( initialiseRegion );

    BDBG_MSG(("Region Verification [0x%02X][%s] %s", regionId, pRegionData->description, pRegionData->verificationRequired?"REQUIRED":"NOT required" ));
    return;
}

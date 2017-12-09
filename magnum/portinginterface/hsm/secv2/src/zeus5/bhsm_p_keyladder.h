/******************************************************************************
 *  Copyright (C) 2017 Broadcom. The term "Broadcom" refers to Broadcom Limited and/or its subsidiaries.
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

/* This file is autogenerated, do not edit. */

#ifndef BHSM_P_KEYLADDER__H
#define BHSM_P_KEYLADDER__H

#ifdef __cplusplus
extern "C"
{
#endif


#include "bhsm.h"

typedef struct BHSM_P_KeyLadderRouteKey
{
    /* input */
    struct {
        uint8_t    blockType;
        uint8_t    entryType;
        uint8_t    keySlotType;
        uint8_t    keySlotNumber;
        uint8_t    sc01ModeWordMapping;
        uint8_t    gPipeSc01EntryType;
        uint8_t    rPipeSc01EntryType;
        uint8_t    keyMode;
        uint32_t    modeWords[4];
        uint16_t    extIvPtr;
        uint8_t    vklId;
        uint8_t    keyLayer;
        uint8_t    swapAesKey;
    }in;
} BHSM_P_KeyLadderRouteKey;

typedef struct BHSM_P_KeyLadderRootConfig
{
    /* input */
    struct {
        uint8_t    vklId;
        uint8_t    askm3DesKlRootKeySwapEnable;
        uint8_t    keyLadderType;
        uint8_t    rootKeySrc;
        uint8_t    customerSel;
        uint8_t    askmSel;
        uint8_t    kdfVersion;
        uint8_t    keyLadderOperation;
        uint8_t    globalKeyOwnerIdSelect;
        uint8_t    globalKeyIndex;
        uint8_t    keySize;
        uint32_t    procIn[8];
        uint16_t    caVendorId;
        uint8_t    stbOwnerIdSel;
        uint8_t    askmMaskKeySel;
    }in;
} BHSM_P_KeyLadderRootConfig;

typedef struct BHSM_P_KeyLadderLayerSet
{
    /* input */
    struct {
        uint8_t    vklId;
        uint8_t    keyLadderType;
        uint8_t    destinationKeyLayer;
        uint8_t    keyLadderOperation;
        uint32_t    procIn[8];
        uint8_t    keySize;
    }in;
} BHSM_P_KeyLadderLayerSet;

typedef struct BHSM_P_KeyLadderRouteIv
{
    /* input */
    struct {
        uint8_t    blockType;
        uint8_t    entryType;
        uint8_t    keySlotType;
        uint8_t    keySlotNumber;
        uint8_t    vklId;
        uint8_t    keyLayer;
        uint8_t    ivType;
    }in;
} BHSM_P_KeyLadderRouteIv;

typedef struct BHSM_P_KeyLadderFwklQuery
{

    /* output */
    struct {
        uint8_t    fwklOwnership[8];
        uint8_t    fwklSubCustomerMode[8];
    }out;
} BHSM_P_KeyLadderFwklQuery;

typedef struct BHSM_P_KeyLadderFwklInvalidate
{
    /* input */
    struct {
        uint8_t    keyLayer;
        uint8_t    vklId;
        uint8_t    clearAllKeyLayer;
        uint8_t    freeOwnership;
    }in;
} BHSM_P_KeyLadderFwklInvalidate;

typedef struct BHSM_P_KeyLadderKladChallenge
{
    /* input */
    struct {
        uint8_t    otpKeyId;
    }in;

    /* output */
    struct {
        uint32_t    idHi;
        uint32_t    idLo;
        uint32_t    stbOwnerId;
    }out;
} BHSM_P_KeyLadderKladChallenge;

typedef struct BHSM_P_KeyLadderKladResponse
{
    /* input */
    struct {
        uint8_t    keyLayer;
        uint8_t    vklId;
        uint8_t    kladMode;
        uint32_t    nonce[4];
    }in;

    /* output */
    struct {
        uint32_t    response[4];
    }out;
} BHSM_P_KeyLadderKladResponse;
BERR_Code BHSM_P_KeyLadder_RouteKey( BHSM_Handle hHsm, BHSM_P_KeyLadderRouteKey *pParam );
BERR_Code BHSM_P_KeyLadder_RootConfig( BHSM_Handle hHsm, BHSM_P_KeyLadderRootConfig *pParam );
BERR_Code BHSM_P_KeyLadder_LayerSet( BHSM_Handle hHsm, BHSM_P_KeyLadderLayerSet *pParam );
BERR_Code BHSM_P_KeyLadder_RouteIv( BHSM_Handle hHsm, BHSM_P_KeyLadderRouteIv *pParam );
BERR_Code BHSM_P_KeyLadder_FwklQuery( BHSM_Handle hHsm, BHSM_P_KeyLadderFwklQuery *pParam );
BERR_Code BHSM_P_KeyLadder_FwklInvalidate( BHSM_Handle hHsm, BHSM_P_KeyLadderFwklInvalidate *pParam );
BERR_Code BHSM_P_KeyLadder_KladChallenge( BHSM_Handle hHsm, BHSM_P_KeyLadderKladChallenge *pParam );
BERR_Code BHSM_P_KeyLadder_KladResponse( BHSM_Handle hHsm, BHSM_P_KeyLadderKladResponse *pParam );

#ifdef __cplusplus
}
#endif
#endif
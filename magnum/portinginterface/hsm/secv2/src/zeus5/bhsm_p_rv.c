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

#include "../bhsm_bsp_msg.h"
#include "bsp_components.h"
#include "bsp_rv.h"
#include "bhsm_p_rv.h"


BDBG_MODULE(BHSMa);


BERR_Code BHSM_P_Rv_RsaKeySet( BHSM_Handle hHsm, BHSM_P_RvRsaKeySet *pParam )
{
    BERR_Code rc = BERR_SUCCESS;
    BHSM_BspMsg_h hMsg = NULL;
    uint16_t bspError = 0;
    BHSM_BspMsgCreate_t msgCreate;
    BHSM_BspMsgConfigure_t msgConfig;
    Bsp_CmdRv_RsaKeySet_InFields_t *pSend = NULL;

    BDBG_ENTER( BHSM_P_Rv_RsaKeySet );

    BKNI_Memset( &msgCreate, 0, sizeof(msgCreate) );
    BKNI_Memset( &msgConfig, 0, sizeof(msgConfig) );

    hMsg = BHSM_BspMsg_Create( hHsm, &msgCreate );
    if( !hMsg ) { return BERR_TRACE( BERR_NOT_AVAILABLE ); }

    pSend = (Bsp_CmdRv_RsaKeySet_InFields_t*)msgCreate.pSend;

    msgConfig.component = Bsp_CmdComponent_eRv;
    msgConfig.command = Bsp_CmdRv_eRsaKeySet;

    rc = BHSM_BspMsg_Configure( hMsg, &msgConfig );
    if( rc != BERR_SUCCESS ) { BERR_TRACE( rc ); goto BHSM_P_DONE_LABEL; }

    /* pack input paramters */
    pSend->rsaKeyId = pParam->in.rsaKeyId;
    pSend->rootKeySrc = pParam->in.rootKeySrc;
    pSend->multiTierKey = pParam->in.multiTierKey;
    pSend->rovf = pParam->in.rovf;
    pSend->addressMsb = pParam->in.addressMsb;
    pSend->address = pParam->in.address;

    rc = BHSM_BspMsg_SubmitCommand ( hMsg, &bspError );
    if( rc != BERR_SUCCESS ) { BERR_TRACE( rc ); goto BHSM_P_DONE_LABEL; }

    if( bspError != 0 ) {
        rc = BHSM_STATUS_BSP_ERROR;
        BDBG_ERR(("%s BSP Status error [0x%X]", BSTD_FUNCTION, bspError ));
        goto BHSM_P_DONE_LABEL;
    }


BHSM_P_DONE_LABEL:

    (void)BHSM_BspMsg_Destroy( hMsg );

    BDBG_LEAVE( BHSM_P_Rv_RsaKeySet );

    return rc;
}


BERR_Code BHSM_P_Rv_RsaKeyClear( BHSM_Handle hHsm, BHSM_P_RvRsaKeyClear *pParam )
{
    BERR_Code rc = BERR_SUCCESS;
    BHSM_BspMsg_h hMsg = NULL;
    uint16_t bspError = 0;
    BHSM_BspMsgCreate_t msgCreate;
    BHSM_BspMsgConfigure_t msgConfig;
    Bsp_CmdRv_RsaKeyClear_InFields_t *pSend = NULL;

    BDBG_ENTER( BHSM_P_Rv_RsaKeyClear );

    BKNI_Memset( &msgCreate, 0, sizeof(msgCreate) );
    BKNI_Memset( &msgConfig, 0, sizeof(msgConfig) );

    hMsg = BHSM_BspMsg_Create( hHsm, &msgCreate );
    if( !hMsg ) { return BERR_TRACE( BERR_NOT_AVAILABLE ); }

    pSend = (Bsp_CmdRv_RsaKeyClear_InFields_t*)msgCreate.pSend;

    msgConfig.component = Bsp_CmdComponent_eRv;
    msgConfig.command = Bsp_CmdRv_eRsaKeyClear;

    rc = BHSM_BspMsg_Configure( hMsg, &msgConfig );
    if( rc != BERR_SUCCESS ) { BERR_TRACE( rc ); goto BHSM_P_DONE_LABEL; }

    /* pack input paramters */
    pSend->rsaKeyId = pParam->in.rsaKeyId;

    rc = BHSM_BspMsg_SubmitCommand ( hMsg, &bspError );
    if( rc != BERR_SUCCESS ) { BERR_TRACE( rc ); goto BHSM_P_DONE_LABEL; }

    if( bspError != 0 ) {
        rc = BHSM_STATUS_BSP_ERROR;
        BDBG_ERR(("%s BSP Status error [0x%X]", BSTD_FUNCTION, bspError ));
        goto BHSM_P_DONE_LABEL;
    }


BHSM_P_DONE_LABEL:

    (void)BHSM_BspMsg_Destroy( hMsg );

    BDBG_LEAVE( BHSM_P_Rv_RsaKeyClear );

    return rc;
}


BERR_Code BHSM_P_Rv_QueryRegion( BHSM_Handle hHsm, BHSM_P_RvQueryRegion *pParam )
{
    BERR_Code rc = BERR_SUCCESS;
    BHSM_BspMsg_h hMsg = NULL;
    uint16_t bspError = 0;
    BHSM_BspMsgCreate_t msgCreate;
    BHSM_BspMsgConfigure_t msgConfig;
    Bsp_CmdRv_QueryRegion_InFields_t *pSend = NULL;
    Bsp_CmdRv_QueryRegion_OutFields_t *pReceive = NULL;

    BDBG_ENTER( BHSM_P_Rv_QueryRegion );

    BKNI_Memset( &msgCreate, 0, sizeof(msgCreate) );
    BKNI_Memset( &msgConfig, 0, sizeof(msgConfig) );

    hMsg = BHSM_BspMsg_Create( hHsm, &msgCreate );
    if( !hMsg ) { return BERR_TRACE( BERR_NOT_AVAILABLE ); }

    pSend = (Bsp_CmdRv_QueryRegion_InFields_t*)msgCreate.pSend;
    pReceive = (Bsp_CmdRv_QueryRegion_OutFields_t*)msgCreate.pReceive;

    msgConfig.component = Bsp_CmdComponent_eRv;
    msgConfig.command = Bsp_CmdRv_eQueryRegion;

    rc = BHSM_BspMsg_Configure( hMsg, &msgConfig );
    if( rc != BERR_SUCCESS ) { BERR_TRACE( rc ); goto BHSM_P_DONE_LABEL; }

    /* pack input paramters */
    pSend->regionId = pParam->in.regionId;

    rc = BHSM_BspMsg_SubmitCommand ( hMsg, &bspError );
    if( rc != BERR_SUCCESS ) { BERR_TRACE( rc ); goto BHSM_P_DONE_LABEL; }

    if( bspError != 0 ) {
        rc = BHSM_STATUS_BSP_ERROR;
        BDBG_ERR(("%s BSP Status error [0x%X]", BSTD_FUNCTION, bspError ));
        goto BHSM_P_DONE_LABEL;
    }

    /* extract output paramters */
    pParam->out.regionStatus = pReceive->regionStatus;
    pParam->out.bgChkCount = pReceive->bgChkCount;
    pParam->out.itchId = pReceive->itchId;
    pParam->out.wrchId = pReceive->wrchId;
    pParam->out.startAddrMsb0 = pReceive->startAddrMsb0;
    pParam->out.startAddr0 = pReceive->startAddr0;
    pParam->out.endAddrMsb0 = pReceive->endAddrMsb0;
    pParam->out.endAddr0 = pReceive->endAddr0;
    pParam->out.sigStartAddrMsb = pReceive->sigStartAddrMsb;
    pParam->out.sigStartAddr = pReceive->sigStartAddr;
    pParam->out.sigEndAddrMsb = pReceive->sigEndAddrMsb;
    pParam->out.sigEndAddr = pReceive->sigEndAddr;
    pParam->out.startAddrMsb1 = pReceive->startAddrMsb1;
    pParam->out.startAddr1 = pReceive->startAddr1;
    pParam->out.endAddrMsb1 = pReceive->endAddrMsb1;
    pParam->out.endAddr1 = pReceive->endAddr1;

BHSM_P_DONE_LABEL:

    (void)BHSM_BspMsg_Destroy( hMsg );

    BDBG_LEAVE( BHSM_P_Rv_QueryRegion );

    return rc;
}


BERR_Code BHSM_P_Rv_QueryAllRegions( BHSM_Handle hHsm, BHSM_P_RvQueryAllRegions *pParam )
{
    BERR_Code rc = BERR_SUCCESS;
    BHSM_BspMsg_h hMsg = NULL;
    uint16_t bspError = 0;
    BHSM_BspMsgCreate_t msgCreate;
    BHSM_BspMsgConfigure_t msgConfig;
    Bsp_CmdRv_QueryAllRegions_OutFields_t *pReceive = NULL;

    BDBG_ENTER( BHSM_P_Rv_QueryAllRegions );

    BKNI_Memset( &msgCreate, 0, sizeof(msgCreate) );
    BKNI_Memset( &msgConfig, 0, sizeof(msgConfig) );

    hMsg = BHSM_BspMsg_Create( hHsm, &msgCreate );
    if( !hMsg ) { return BERR_TRACE( BERR_NOT_AVAILABLE ); }

    pReceive = (Bsp_CmdRv_QueryAllRegions_OutFields_t*)msgCreate.pReceive;

    msgConfig.component = Bsp_CmdComponent_eRv;
    msgConfig.command = Bsp_CmdRv_eQueryAllRegions;

    rc = BHSM_BspMsg_Configure( hMsg, &msgConfig );
    if( rc != BERR_SUCCESS ) { BERR_TRACE( rc ); goto BHSM_P_DONE_LABEL; }

    rc = BHSM_BspMsg_SubmitCommand ( hMsg, &bspError );
    if( rc != BERR_SUCCESS ) { BERR_TRACE( rc ); goto BHSM_P_DONE_LABEL; }

    if( bspError != 0 ) {
        rc = BHSM_STATUS_BSP_ERROR;
        BDBG_ERR(("%s BSP Status error [0x%X]", BSTD_FUNCTION, bspError ));
        goto BHSM_P_DONE_LABEL;
    }

    /* extract output paramters */
    BKNI_Memcpy( pParam->out.regionStatus, pReceive->regionStatus, 124 );

BHSM_P_DONE_LABEL:

    (void)BHSM_BspMsg_Destroy( hMsg );

    BDBG_LEAVE( BHSM_P_Rv_QueryAllRegions );

    return rc;
}


BERR_Code BHSM_P_Rv_EnableRegion( BHSM_Handle hHsm, BHSM_P_RvEnableRegion *pParam )
{
    BERR_Code rc = BERR_SUCCESS;
    BHSM_BspMsg_h hMsg = NULL;
    uint16_t bspError = 0;
    BHSM_BspMsgCreate_t msgCreate;
    BHSM_BspMsgConfigure_t msgConfig;
    Bsp_CmdRv_EnableRegion_InFields_t *pSend = NULL;

    BDBG_ENTER( BHSM_P_Rv_EnableRegion );

    BKNI_Memset( &msgCreate, 0, sizeof(msgCreate) );
    BKNI_Memset( &msgConfig, 0, sizeof(msgConfig) );

    hMsg = BHSM_BspMsg_Create( hHsm, &msgCreate );
    if( !hMsg ) { return BERR_TRACE( BERR_NOT_AVAILABLE ); }

    pSend = (Bsp_CmdRv_EnableRegion_InFields_t*)msgCreate.pSend;

    msgConfig.component = Bsp_CmdComponent_eRv;
    msgConfig.command = Bsp_CmdRv_eEnableRegion;

    rc = BHSM_BspMsg_Configure( hMsg, &msgConfig );
    if( rc != BERR_SUCCESS ) { BERR_TRACE( rc ); goto BHSM_P_DONE_LABEL; }

    /* pack input paramters */
    pSend->regionId = pParam->in.regionId;
    pSend->startAddrMsb = pParam->in.startAddrMsb;
    pSend->startAddr = pParam->in.startAddr;
    pSend->endAddrMsb = pParam->in.endAddrMsb;
    pSend->endAddr = pParam->in.endAddr;
    pSend->secondRangeStartAddrMsb = pParam->in.secondRangeStartAddrMsb;
    pSend->secondRangeStartAddr = pParam->in.secondRangeStartAddr;
    pSend->secondRangeEndAddrMsb = pParam->in.secondRangeEndAddrMsb;
    pSend->secondRangeEndAddr = pParam->in.secondRangeEndAddr;
    pSend->sigStartAddrMsb = pParam->in.sigStartAddrMsb;
    pSend->sigStartAddr = pParam->in.sigStartAddr;
    pSend->intervalCheckBw = pParam->in.intervalCheckBw;
    pSend->secondRangeAvailable = pParam->in.secondRangeAvailable;
    pSend->resetOnVerifyFailure = pParam->in.resetOnVerifyFailure;
    pSend->rsaKeyId = pParam->in.rsaKeyId;
    pSend->decryptionSel = pParam->in.decryptionSel;
    pSend->keyLayer = pParam->in.keyLayer;
    pSend->vklId = pParam->in.vklId;
    pSend->bgCheck = pParam->in.bgCheck;
    pSend->allowRegionDisable = pParam->in.allowRegionDisable;
    pSend->enforceAuth = pParam->in.enforceAuth;
    pSend->sigMetaDataStartAddrMsb = pParam->in.sigMetaDataStartAddrMsb;
    pSend->sigMetaDataStartAddr = pParam->in.sigMetaDataStartAddr;
    pSend->dstStartAddrMsb = pParam->in.dstStartAddrMsb;
    pSend->dstStartAddr = pParam->in.dstStartAddr;
    pSend->secondDstStartAddrMsb = pParam->in.secondDstStartAddrMsb;
    pSend->secondDstStartAddr = pParam->in.secondDstStartAddr;
    BKNI_Memcpy( pSend->decryptionKey, pParam->in.decryptionKey, 16 );
    BKNI_Memcpy( pSend->decryptionIv, pParam->in.decryptionIv, 16 );
    pSend->sageCodeEncryptEnable = pParam->in.sageCodeEncryptEnable;

    rc = BHSM_BspMsg_SubmitCommand ( hMsg, &bspError );
    if( rc != BERR_SUCCESS ) { BERR_TRACE( rc ); goto BHSM_P_DONE_LABEL; }

    if( bspError != 0 ) {
        rc = BHSM_STATUS_BSP_ERROR;
        BDBG_ERR(("%s BSP Status error [0x%X]", BSTD_FUNCTION, bspError ));
        goto BHSM_P_DONE_LABEL;
    }


BHSM_P_DONE_LABEL:

    (void)BHSM_BspMsg_Destroy( hMsg );

    BDBG_LEAVE( BHSM_P_Rv_EnableRegion );

    return rc;
}


BERR_Code BHSM_P_Rv_DisableRegion( BHSM_Handle hHsm, BHSM_P_RvDisableRegion *pParam )
{
    BERR_Code rc = BERR_SUCCESS;
    BHSM_BspMsg_h hMsg = NULL;
    uint16_t bspError = 0;
    BHSM_BspMsgCreate_t msgCreate;
    BHSM_BspMsgConfigure_t msgConfig;
    Bsp_CmdRv_DisableRegion_InFields_t *pSend = NULL;

    BDBG_ENTER( BHSM_P_Rv_DisableRegion );

    BKNI_Memset( &msgCreate, 0, sizeof(msgCreate) );
    BKNI_Memset( &msgConfig, 0, sizeof(msgConfig) );

    hMsg = BHSM_BspMsg_Create( hHsm, &msgCreate );
    if( !hMsg ) { return BERR_TRACE( BERR_NOT_AVAILABLE ); }

    pSend = (Bsp_CmdRv_DisableRegion_InFields_t*)msgCreate.pSend;

    msgConfig.component = Bsp_CmdComponent_eRv;
    msgConfig.command = Bsp_CmdRv_eDisableRegion;

    rc = BHSM_BspMsg_Configure( hMsg, &msgConfig );
    if( rc != BERR_SUCCESS ) { BERR_TRACE( rc ); goto BHSM_P_DONE_LABEL; }

    /* pack input paramters */
    pSend->regionId = pParam->in.regionId;

    rc = BHSM_BspMsg_SubmitCommand ( hMsg, &bspError );
    if( rc != BERR_SUCCESS ) { BERR_TRACE( rc ); goto BHSM_P_DONE_LABEL; }

    if( bspError != 0 ) {
        rc = BHSM_STATUS_BSP_ERROR;
        BDBG_ERR(("%s BSP Status error [0x%X]", BSTD_FUNCTION, bspError ));
        goto BHSM_P_DONE_LABEL;
    }


BHSM_P_DONE_LABEL:

    (void)BHSM_BspMsg_Destroy( hMsg );

    BDBG_LEAVE( BHSM_P_Rv_DisableRegion );

    return rc;
}


BERR_Code BHSM_P_Rv_HostItchDisable( BHSM_Handle hHsm, BHSM_P_RvHostItchDisable *pParam )
{
    BERR_Code rc = BERR_SUCCESS;
    BHSM_BspMsg_h hMsg = NULL;
    uint16_t bspError = 0;
    BHSM_BspMsgCreate_t msgCreate;
    BHSM_BspMsgConfigure_t msgConfig;
    BSTD_UNUSED( pParam );

    BDBG_ENTER( BHSM_P_Rv_HostItchDisable );

    BKNI_Memset( &msgCreate, 0, sizeof(msgCreate) );
    BKNI_Memset( &msgConfig, 0, sizeof(msgConfig) );

    hMsg = BHSM_BspMsg_Create( hHsm, &msgCreate );
    if( !hMsg ) { return BERR_TRACE( BERR_NOT_AVAILABLE ); }


    msgConfig.component = Bsp_CmdComponent_eRv;
    msgConfig.command = Bsp_CmdRv_eHostItchDisable;

    rc = BHSM_BspMsg_Configure( hMsg, &msgConfig );
    if( rc != BERR_SUCCESS ) { BERR_TRACE( rc ); goto BHSM_P_DONE_LABEL; }

    rc = BHSM_BspMsg_SubmitCommand ( hMsg, &bspError );
    if( rc != BERR_SUCCESS ) { BERR_TRACE( rc ); goto BHSM_P_DONE_LABEL; }

    if( bspError != 0 ) {
        rc = BHSM_STATUS_BSP_ERROR;
        BDBG_ERR(("%s BSP Status error [0x%X]", BSTD_FUNCTION, bspError ));
        goto BHSM_P_DONE_LABEL;
    }


BHSM_P_DONE_LABEL:

    (void)BHSM_BspMsg_Destroy( hMsg );

    BDBG_LEAVE( BHSM_P_Rv_HostItchDisable );

    return rc;
}

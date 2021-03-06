/******************************************************************************
 * (c) 2006-2016 Broadcom Corporation
 *
 * This program is the proprietary software of Broadcom Corporation and/or its
 * licensors, and may only be used, duplicated, modified or distributed pursuant
 * to the terms and conditions of a separate, written license agreement executed
 * between you and Broadcom (an "Authorized License").  Except as set forth in
 * an Authorized License, Broadcom grants no license (express or implied), right
 * to use, or waiver of any kind with respect to the Software, and Broadcom
 * expressly reserves all rights in and to the Software and all intellectual
 * property rights therein.  IF YOU HAVE NO AUTHORIZED LICENSE, THEN YOU
 * HAVE NO RIGHT TO USE THIS SOFTWARE IN ANY WAY, AND SHOULD IMMEDIATELY
 * NOTIFY BROADCOM AND DISCONTINUE ALL USE OF THE SOFTWARE.
 *
 * Except as expressly set forth in the Authorized License,
 *
 * 1. This program, including its structure, sequence and organization,
 *    constitutes the valuable trade secrets of Broadcom, and you shall use all
 *    reasonable efforts to protect the confidentiality thereof, and to use
 *    this information only in connection with your use of Broadcom integrated
 *    circuit products.
 *
 * 2. TO THE MAXIMUM EXTENT PERMITTED BY LAW, THE SOFTWARE IS PROVIDED "AS IS"
 *    AND WITH ALL FAULTS AND BROADCOM MAKES NO PROMISES, REPRESENTATIONS OR
 *    WARRANTIES, EITHER EXPRESS, IMPLIED, STATUTORY, OR OTHERWISE, WITH RESPECT
 *    TO THE SOFTWARE.  BROADCOM SPECIFICALLY DISCLAIMS ANY AND ALL IMPLIED
 *    WARRANTIES OF TITLE, MERCHANTABILITY, NONINFRINGEMENT, FITNESS FOR A
 *    PARTICULAR PURPOSE, LACK OF VIRUSES, ACCURACY OR COMPLETENESS, QUIET
 *    ENJOYMENT, QUIET POSSESSION OR CORRESPONDENCE TO DESCRIPTION. YOU ASSUME
 *    THE ENTIRE RISK ARISING OUT OF USE OR PERFORMANCE OF THE SOFTWARE.
 *
 * 3. TO THE MAXIMUM EXTENT PERMITTED BY LAW, IN NO EVENT SHALL BROADCOM OR ITS
 *    LICENSORS BE LIABLE FOR (i) CONSEQUENTIAL, INCIDENTAL, SPECIAL, INDIRECT,
 *    OR EXEMPLARY DAMAGES WHATSOEVER ARISING OUT OF OR IN ANY WAY RELATING TO
 *    YOUR USE OF OR INABILITY TO USE THE SOFTWARE EVEN IF BROADCOM HAS BEEN
 *    ADVISED OF THE POSSIBILITY OF SUCH DAMAGES; OR (ii) ANY AMOUNT IN EXCESS
 *    OF THE AMOUNT ACTUALLY PAID FOR THE SOFTWARE ITSELF OR U.S. $1, WHICHEVER
 *    IS GREATER. THESE LIMITATIONS SHALL APPLY NOTWITHSTANDING ANY FAILURE OF
 *    ESSENTIAL PURPOSE OF ANY LIMITED REMEDY.
 *
 *****************************************************************************/


/* #define RAAGA_UART_ENABLE */

#include "bdsp_raaga_priv.h"
#include "bdsp_raaga_fw_algo.h"
#include "bdsp_raaga_fw_cit.h"
#include "bdsp_raaga_fwdownload_priv.h"
#include "bdsp_raaga_int_priv.h"
#include "bdsp_raaga_fw.h"
#include "bdsp_common_priv.h"
#include "bdsp_common_mm_priv.h"
#include "bchp_sun_top_ctrl.h"
#include "bchp_aud_fmm_bf_ctrl.h"
#include "bdsp.h"
#include "bdsp_raaga_version.h"

#ifdef RAAGA_UART_ENABLE
#include "bchp.h"
#include "bchp_priv.h"
#if (BCHP_CHIP == 7445)
#include "bchp_7445.h"
#endif
#if (BCHP_CHIP == 7231)
#include "bchp_7231.h"
#endif
#if (BCHP_CHIP == 7346)
#include "bchp_7346.h"
#endif
#include "bchp_sun_top_ctrl.h"
#endif

#if BCHP_PWR_SUPPORT
#include "bchp_pwr.h"
#endif

BDBG_MODULE(bdsp_raaga_priv);

BDBG_OBJECT_ID(BDSP_Raaga);
BDBG_OBJECT_ID(BDSP_RaagaContext);
BDBG_OBJECT_ID(BDSP_RaagaTask);
BDBG_OBJECT_ID(BDSP_RaagaStage);
BDBG_OBJECT_ID(BDSP_RaagaTaskStageInput);
BDBG_OBJECT_ID(BDSP_RaagaExternalInterrupt);
BDBG_OBJECT_ID(BDSP_RaagaRdbRegister);
BDBG_OBJECT_ID(BDSP_P_InterTaskBuffer);
BDBG_OBJECT_ID(BDSP_RaagaCapture);
BDBG_OBJECT_ID(BDSP_RaagaQueue);

#define BDSP_BDBG_MSG_LVL1(x) if(0){ BDBG_MSG(x);}

/*****************************************************************************/
/**************Audio Codec structure details ****************************/
/*****************************************************************************/

const BDSP_Version BDSP_sRaagaVersion = {BDSP_RAAGA_MAJOR_VERSION, BDSP_RAAGA_MINOR_VERSION, BDSP_RAAGA_BRANCH_VERSION, BDSP_RAAGA_BRANCH_SUBVERSION};

#define FRAMESYNC_TSM_NODE_INDEX                0

static void BDSP_Raaga_P_GetDistinctOpTypeAndNumChans(
    BDSP_DataType dataType, /* [in] */
    unsigned *numChans, /* [out] */
    BDSP_AF_P_DistinctOpType *distinctOp /* [out] */
    )
{
    switch(dataType)
    {
        case BDSP_DataType_ePcmMono:
            *distinctOp = BDSP_AF_P_DistinctOpType_eMono_PCM;
            *numChans = 1;
            break;
        case BDSP_DataType_eIec61937:
            *distinctOp = BDSP_AF_P_DistinctOpType_eCompressed;
            *numChans = 1;
            break;
        case BDSP_DataType_eIec61937x16:
            *distinctOp = BDSP_AF_P_DistinctOpType_eCompressedHBR;
            *numChans = 1;
            break;
        case BDSP_DataType_eIec61937x4:
            *distinctOp = BDSP_AF_P_DistinctOpType_eCompressed4x;
            *numChans = 1;
            break;
        case BDSP_DataType_eCompressedRaw:
            *distinctOp = BDSP_AF_P_DistinctOpType_eCdb;
            *numChans = 1;
            break;
        case BDSP_DataType_ePcmRf:
            *distinctOp = BDSP_AF_P_DistinctOpType_eCompressed4x;
            *numChans = 1;
            break;
        case BDSP_DataType_eRave:
            *distinctOp = BDSP_AF_P_DistinctOpType_eCdb;
            *numChans = 1;
            break;
        case BDSP_DataType_ePcm5_1:
            *distinctOp = BDSP_AF_P_DistinctOpType_e5_1_PCM;
            *numChans = 6;
            break;
        case BDSP_DataType_eDolbyTranscodeData:
            *distinctOp = BDSP_AF_P_DistinctOpType_eDolbyReEncodeAuxDataOut;
            *numChans = 6;
#if (BDSP_MS12_SUPPORT == 65)
            *numChans = 8;
#endif
            break;
        case BDSP_DataType_ePcm7_1:
            *distinctOp = BDSP_AF_P_DistinctOpType_e7_1_PCM;
            *numChans = 8;
            break;
        case BDSP_DataType_eRdbCdb:
            *distinctOp = BDSP_AF_P_DistinctOpType_eCdb;
            *numChans = 1;
            break;
        case BDSP_DataType_eRdbItb:
            *distinctOp = BDSP_AF_P_DistinctOpType_eItb;
            *numChans = 1;
            break;
        case BDSP_DataType_eRdbAnc:
            *distinctOp = BDSP_AF_P_DistinctOpType_eAncillaryData;
            *numChans = 1;
            break;
        case BDSP_DataType_eRDBPool:
            *distinctOp = BDSP_AF_P_DistinctOpType_eDescriptorQueue;
            *numChans = 1;
            break;
        case BDSP_DataType_ePcmStereo:
        default:
            *distinctOp = BDSP_AF_P_DistinctOpType_eStereo_PCM;
            *numChans = 2;
            break;
    }

    return;
}
/***********************************************************************
Name        :   BDSP_Raaga_P_GetDefaultClkRate

Input       :   pDeviceHandle
                dsp Index

Output      :   Default Dsp Clock Rate

Function    :   This function is used for dynamic frequency scaling.
                Here we obtain the default clock rate of the DSP.
***********************************************************************/
BERR_Code BDSP_Raaga_P_GetDefaultClkRate(void * pDeviceHandle, unsigned dspIndex, unsigned *pDefaultDspClkRate )
{
    BDSP_Raaga *pDevice = (BDSP_Raaga *)pDeviceHandle;
    BERR_Code err = BERR_NOT_INITIALIZED;

    BDBG_ASSERT((dspIndex + 1) <= BDSP_RAAGA_MAX_DSP);

    if( dspIndex == 0 )
    {
        #ifdef BCHP_PWR_RESOURCE_RAAGA0_DSP
            err = BCHP_PWR_GetDefaultClockRate(pDevice->chpHandle, BCHP_PWR_RESOURCE_RAAGA0_DSP, pDefaultDspClkRate );
        #else
            BSTD_UNUSED(pDevice);
            BSTD_UNUSED(pDefaultDspClkRate);
        #endif
    }
    else if( dspIndex == 1 )
    {
        #ifdef BCHP_PWR_RESOURCE_RAAGA1_DSP
            err = BCHP_PWR_GetDefaultClockRate(pDevice->chpHandle, BCHP_PWR_RESOURCE_RAAGA1_DSP, pDefaultDspClkRate );
        #endif
    }

    return err;
}
/***********************************************************************
Name        :   BDSP_Raaga_P_SetDspClkRate

Input       :   pDeviceHandle
                expectedDspClkRate
                dsp Index

Function    :   This function is used for dynamic frequency scaling.
                This will be required as part of power management until we
                decouple the AIO RBUS bridge from the  DSP0 and have
                independent control.

                dspIndex decides which DSPs frequency is being updated.
                In case BCHP_PWR doesn't have support for dynamic freq
                scaling, the apis will return BERR_NOT_SUPPORTED.

Return      :   void
***********************************************************************/
static void BDSP_Raaga_P_SetDspClkRate( void *pDeviceHandle, unsigned expectedDspClkRate, unsigned dspIndex )
{
    BDSP_Raaga *pDevice = (BDSP_Raaga*)pDeviceHandle;
    BERR_Code err = BERR_NOT_SUPPORTED;
    unsigned currentDspClkRate=0;

    BDBG_ASSERT((dspIndex + 1) <= BDSP_RAAGA_MAX_DSP);

    if( dspIndex == 0 )
    {
        #ifdef BCHP_PWR_RESOURCE_RAAGA0_DSP
            /* GetClk is done before SetClk to detect if DSP is already running at expected frequency,
                to avoid invoking the glitchless circuit */
            err = BCHP_PWR_GetClockRate(pDevice->chpHandle, BCHP_PWR_RESOURCE_RAAGA0_DSP, &currentDspClkRate );
            if( (err == BERR_SUCCESS) && \
                ( currentDspClkRate !=  expectedDspClkRate))
            {
                err = BCHP_PWR_SetClockRate(pDevice->chpHandle, BCHP_PWR_RESOURCE_RAAGA0_DSP, expectedDspClkRate );
            }
        #else
            BSTD_UNUSED(pDeviceHandle);
            BSTD_UNUSED(pDevice);
            BSTD_UNUSED(expectedDspClkRate);
            BSTD_UNUSED(currentDspClkRate);
            BSTD_UNUSED(dspIndex);
        #endif
    }
    else if( dspIndex == 1 )
    {
        #ifdef BCHP_PWR_RESOURCE_RAAGA1_DSP
            err = BCHP_PWR_GetClockRate(pDevice->chpHandle, BCHP_PWR_RESOURCE_RAAGA1_DSP, &currentDspClkRate );
            if( (err == BERR_SUCCESS) && \
                ( currentDspClkRate !=  expectedDspClkRate))
            {
                err = BCHP_PWR_SetClockRate(pDevice->chpHandle, BCHP_PWR_RESOURCE_RAAGA1_DSP, expectedDspClkRate );
            }
        #endif
    }

    if( err == BERR_SUCCESS)
            BDBG_MSG(("PWR: DSP%d current ClkRate = %d Hz ",dspIndex, expectedDspClkRate));
    return;
}
/***********************************************************************
Name        :   BDSP_Raaga_P_GetLowerDspClkRate

Input       :   Default Raaga DSP frequency

Output      :   1/16th the input parameter-defaultDspClkRate

Funtion     :   After measuring power at different clock frequencies it
                was decided to have a 1/16th frequency for lower power
                consumption. So whenever DSP is not in use, before taking
                off the clock we will reduce the Clock frequency to
                1/16th the default.

***********************************************************************/

void    BDSP_Raaga_P_GetLowerDspClkRate(unsigned dspClkRate, unsigned *lowerDspClkRate)
{
    *lowerDspClkRate = dspClkRate/16;
}
/***********************************************************************
Name            :   BDSP_Raaga_P_Close

Type            :   PI Interface

Input           :   pDeviceHandle -Device Handle which needs to be closed.

Return          :   None

Functionality       :
    1)  Destroy any Context, Interrupt Handle, RDB register left Open.
    2)  UnInstall Acknowledgment for the DSP.
    3)  De-Allocate Scratch, Interstage & Interstage interface memory requirements.
    4)  Destroy the Mutexs for task, capture, Fifos, DspInterrupt, RDB, Watchdog.
    5)  Free the Firmware Executables.
    6)  De-Allocate memories for CIT Buffers, Command Queue and Generic Response Queue.
    7)  Disable the Watchdog timer.
    8)  Reset the Hardware for each DSP.
    9)  Free the memory allocated for Device Handle.
***********************************************************************/

void BDSP_Raaga_P_Close(
    void *pDeviceHandle
    )
{
    BDSP_Raaga *pDevice = (BDSP_Raaga *)pDeviceHandle;
    BDSP_RaagaContext *pRaagaContext;
    BDSP_RaagaExternalInterrupt *pRaagaExtInterrput;
    BDSP_RaagaRdbRegister *pRaagaRdbRegister;
    BDSP_Status sStatus;
    unsigned uiDspIndex=0;
    BERR_Code   err=BERR_SUCCESS;
    unsigned j;
    void *pAddress = NULL;

    BDBG_OBJECT_ASSERT(pDevice, BDSP_Raaga);
    BDBG_ENTER(BDSP_Raaga_P_Close);

#ifdef BDSP_FW_RBUF_CAPTURE
    /* Specific to FW Ring Buffer capture required for their unit testing */
    if(Rbuf_Setting.rbuf_init != NULL && Rbuf_Setting.rbuf_uninit != NULL)
    {
        Rbuf_Setting.rbuf_uninit();
    }
#endif

    BKNI_AcquireMutex(pDevice->captureMutex);

    /* Destroy any contexts left open */
    while ( (pRaagaContext = BLST_S_FIRST(&pDevice->contextList)) )
    {
        BDSP_Context_Destroy(&pRaagaContext->context);
    }

    /* Free up any interrupt handle left open */
    while( (pRaagaExtInterrput = BLST_S_FIRST(&pDevice->interruptList)) )
    {
        BDSP_FreeExternalInterrupt(&pRaagaExtInterrput->extInterrupt);
    }

    /* Free up any rdb register handle left open */
    while( (pRaagaRdbRegister = BLST_S_FIRST(&pDevice->rdbRegisterList)) )
    {
        BDSP_FreeRdbRegisters(&pRaagaRdbRegister->rdbRegister);
    }

    pDevice->device.getStatus(pDeviceHandle,&sStatus);

    for (uiDspIndex =0 ; uiDspIndex < pDevice->numDsp; uiDspIndex++)
    {
        err = BDSP_Raaga_P_DestroyMsgQueue(pDevice->hCmdQueue[uiDspIndex],
            pDevice->regHandle, pDevice->dspOffset[uiDspIndex]);
        if (BERR_SUCCESS != err)
        {
            BDBG_ERR(("BDSP_Raaga_P_Close: CMD queue destroy failed!"));
            err = BERR_TRACE(err);
        }

        err = BDSP_Raaga_P_DestroyMsgQueue(pDevice->hGenRspQueue[uiDspIndex],
            pDevice->regHandle, pDevice->dspOffset[uiDspIndex]);
        if (BERR_SUCCESS != err)
        {
            BDBG_ERR(("BDSP_Raaga_P_Close: Generic RSP queue destroy failed!"));
            err = BERR_TRACE(err);
        }
        if (pDevice->memInfo.sScratchandISBuff[uiDspIndex].ui32DspScratchMemGrant.ui32BufferSizeInBytes)
        {
            pAddress = NULL;
            BDSP_MEM_P_ConvertOffsetToCacheAddr(
                    pDevice->memHandle,
                    pDevice->memInfo.sScratchandISBuff[uiDspIndex].ui32DspScratchMemGrant.ui32DramBufferAddress,
                    &pAddress);
            BDSP_MEM_P_FreeMemory((void *)pDevice->memHandle, pAddress);
        }

        for(j = 0; j<BDSP_RAAGA_MAX_BRANCH_PER_TASK; j++)
        {
            pAddress = NULL;
            BDSP_MEM_P_ConvertOffsetToCacheAddr(
                pDevice->memHandle,
                pDevice->memInfo.sScratchandISBuff[uiDspIndex].InterStageIOBuff[j].sCircBuffer[0].ui32BaseAddr,
                &pAddress);
            BDSP_MEM_P_FreeMemory((void *)pDevice->memHandle, pAddress);

            pAddress = NULL;
            BDSP_MEM_P_ConvertOffsetToCacheAddr(
                pDevice->memHandle,
                pDevice->memInfo.sScratchandISBuff[uiDspIndex].InterStageIOGenericBuff[j].sCircBuffer.ui32BaseAddr,
                &pAddress);
            BDSP_MEM_P_FreeMemory((void *)pDevice->memHandle, pAddress);
        }

        BKNI_DestroyMutex((pDevice->fifoIdMutex[uiDspIndex]));
        BKNI_DestroyMutex((pDevice->dspInterruptMutex[uiDspIndex]));
        BKNI_DestroyMutex((pDevice->rdbRegistersMutex[uiDspIndex]));
    }
    BKNI_DestroyMutex((pDevice->watchdogMutex));
    BDSP_Raaga_P_FreeInitMemory(pDeviceHandle);

    BKNI_ReleaseMutex(pDevice->captureMutex);

    BKNI_DestroyMutex((pDevice->taskDetails.taskIdMutex));
    BKNI_DestroyMutex((pDevice->captureMutex));

    /*Disable watchdog*/
    BDSP_Raaga_P_EnableAndSaveStateWatchdogTimer(pDeviceHandle,false);

    BDSP_Raaga_P_Reset(pDeviceHandle);

    BDSP_Raaga_P_EnableAllPwrResource(pDeviceHandle, false);
    /* Invalidate and free the device structure */
    BDBG_OBJECT_DESTROY(pDevice, BDSP_Raaga);
    BKNI_Free(pDevice);
    BDBG_LEAVE(BDSP_Raaga_P_Close);
}

/***********************************************************************
Name        :   BDSP_Raaga_P_GetStatus

Type        :   PI Interface

Input       :   pDeviceHandle -Device Handle which needs to be closed.
                pStatus - pointer where the Data will be filled and returned to PI

Return      :   None

Functionality   :   Return the following data to the PI.
    1)  Number of DSPs supported.
    2)  Number of Watchdog Events.
    3)  Details of Firmware version.
***********************************************************************/

void BDSP_Raaga_P_GetStatus(
    void *pDeviceHandle,
    BDSP_Status *pStatus
    )
{
    BDSP_Raaga *pDevice = (BDSP_Raaga *)pDeviceHandle;
    BDBG_OBJECT_ASSERT(pDevice, BDSP_Raaga);
    pStatus->numDsp = pDevice->numDsp;
    pStatus->numWatchdogEvents=0;
    pStatus->firmwareVersion.majorVersion = BDSP_sRaagaVersion.majorVersion;
    pStatus->firmwareVersion.minorVersion = BDSP_sRaagaVersion.minorVersion;
    pStatus->firmwareVersion.branchVersion = BDSP_sRaagaVersion.branchVersion;
    pStatus->firmwareVersion.branchSubVersion = BDSP_sRaagaVersion.branchSubVersion;

#if 0
    BDBG_LOG(("BDSP Firmware Version %dp%dp%dp%d",
                                pStatus->firmwareVersion.majorVersion,
                                pStatus->firmwareVersion.minorVersion,
                                pStatus->firmwareVersion.branchVersion,
                                pStatus->firmwareVersion.branchSubVersion));
#endif

    return;
}

/***********************************************************************
Name        :   BDSP_Raaga_P_GetAlgorithmInfo

Type        :   PI Interface

Input       :   algorithm -The algorithm for the which the data is requested by PI.
                pInfo - Pointer where the specific data releated to algorithm is returned back to the PI.

Return      :   None

Functionality   :   Returns the following data back to the PI.
    1)  Name of the algorithm.
    2)  Whether the algorithm is supported or not.
    3)  To which category the algothm belongs to.
    4)  The size of the User Configuration required by the algorithm.
    5)  The size of the Status Buffer required by the algorithm.
***********************************************************************/

void BDSP_Raaga_P_GetAlgorithmInfo(
    BDSP_Algorithm algorithm,
    BDSP_AlgorithmInfo *pInfo /* [out] */
    )
{
    const BDSP_Raaga_P_AlgorithmInfo *pAlgoInfo;

    BDBG_ASSERT(pInfo);

    pAlgoInfo = BDSP_Raaga_P_LookupAlgorithmInfo(algorithm);
    pInfo->pName = pAlgoInfo->pName;
    pInfo->supported = pAlgoInfo->supported;
    pInfo->type = pAlgoInfo->type;
    pInfo->settingsSize = pAlgoInfo->userConfigSize;
    pInfo->statusSize = pAlgoInfo->statusBufferSize;
}

/***********************************************************************
Name        :   BDSP_Raaga_P_GetDefaultContextSettings

Type        :   PI Interface

Input       :   pDeviceHandle -Device Handle which needs to be closed.
                contextType - The Type of context to be opened like Audio/Video Decode/Video Encode/SCM
                pSettings - pointer where the Default Data will be filled and returned to PI.

Return      :   None

Functionality   :   Returns the default date for create settings to the PI depending the type of Context to be created.
                Mostly the default data is zeros unless specifically programed.
***********************************************************************/

void BDSP_Raaga_P_GetDefaultContextSettings(
    void *pDeviceHandle,
    BDSP_ContextType contextType,
    BDSP_ContextCreateSettings *pSettings
    )
{
    BDSP_Raaga *pDevice = (BDSP_Raaga *)pDeviceHandle;

    BDBG_OBJECT_ASSERT(pDevice, BDSP_Raaga);
    BKNI_Memset(pSettings, 0, sizeof(*pSettings));

    if (contextType == BDSP_ContextType_eAudio)
    {
        pSettings->maxTasks = BDSP_RAAGA_MAX_FW_TASK_PER_CTXT;
        pSettings->contextType = contextType;
        pSettings->maxBranch = BDSP_RAAGA_MAX_BRANCH;
        pSettings->maxStagePerBranch = BDSP_RAAGA_MAX_STAGE_PER_BRANCH;
    }
    else if (contextType == BDSP_ContextType_eVideo)
    {
        pSettings->maxTasks = BDSP_RAAGA_MAX_FW_TASK_PER_CTXT;
        pSettings->contextType = contextType;
        pSettings->maxBranch = BDSP_RAAGA_MAX_BRANCH;
        pSettings->maxStagePerBranch = BDSP_RAAGA_MAX_STAGE_PER_BRANCH;
    }
    else if (contextType == BDSP_ContextType_eScm)
    {
        pSettings->maxTasks = BDSP_RAAGA_MAX_FW_TASK_PER_SCM_CTXT;
        pSettings->contextType = contextType;
        pSettings->maxBranch = BDSP_RAAGA_MAX_BRANCH_SCM;
        pSettings->maxStagePerBranch = BDSP_RAAGA_MAX_STAGE_PER_BRANCH_SCM;
    }
    else if (BDSP_ContextType_eVideoEncode == contextType)
    {
        pSettings->maxTasks = BDSP_RAAGA_MAX_FW_TASK_PER_VIDEO_ENCODE_CTXT;
        pSettings->contextType = contextType;
        pSettings->maxBranch = BDSP_RAAGA_MAX_BRANCH_VIDEO_ENCODE;
        pSettings->maxStagePerBranch = BDSP_RAAGA_MAX_STAGE_PER_BRANCH_VIDEO_ENCODE;
    }
}

BERR_Code BDSP_Raaga_P_PopulateGateOpenFMMStages(
                                void *pPrimaryStageHandle,
                                BDSP_AF_P_TASK_sFMM_GATE_OPEN_CONFIG *sTaskFmmGateOpenConfig,
                                uint32_t ui32MaxIndepDelay
                            )
{
    BERR_Code errCode = BERR_SUCCESS;
    unsigned output;
    unsigned ui32NumPorts = 0, channel, ui32FMMContentType, ui32FMMDstType;
    unsigned ui32BufferDepthThreshold;
    BDSP_RaagaStage *pRaagaPrimaryStage = (BDSP_RaagaStage *)pPrimaryStageHandle;

    BDBG_ASSERT(NULL != pRaagaPrimaryStage);

    BDSP_STAGE_TRAVERSE_LOOP_BEGIN(pRaagaPrimaryStage, pRaagaConnectStage)
    BSTD_UNUSED(macroBrId);
    BSTD_UNUSED(macroStId);
    {
        for(output=0;output<BDSP_AF_P_MAX_OP_FORKS;output++)
        {
            if(pRaagaConnectStage->sStageOutput[output].eConnectionType == BDSP_ConnectionType_eFmmBuffer &&
                pRaagaConnectStage->sStageOutput[output].eNodeValid==BDSP_AF_P_eValid)
            {
                switch ( pRaagaConnectStage->eStageOpBuffDataType[output])
                {
                case BDSP_AF_P_DistinctOpType_e7_1_MixPcm:
                case BDSP_AF_P_DistinctOpType_e5_1_MixPcm:
                case BDSP_AF_P_DistinctOpType_eStereo_MixPcm:
                case BDSP_AF_P_DistinctOpType_e7_1_PCM:
                case BDSP_AF_P_DistinctOpType_e5_1_PCM:
                case BDSP_AF_P_DistinctOpType_eStereo_PCM:
                case BDSP_AF_P_DistinctOpType_eMono_PCM:
                    ui32FMMContentType = BDSP_AF_P_FmmContentType_ePcm;
                    ui32FMMDstType = BDSP_AF_P_FmmDstFsRate_eBaseRate;
                    ui32BufferDepthThreshold = (BDSP_CIT_P_STANDARD_BUFFER_THRESHOLD + BDSP_CIT_P_MAXIMUM_RESIDUAL_COLLECTION);
                    break;
                case BDSP_AF_P_DistinctOpType_eCompressed:
                case BDSP_AF_P_DistinctOpType_eAuxilaryDataOut:
                case BDSP_AF_P_DistinctOpType_eGenericIsData:
                case BDSP_AF_P_DistinctOpType_eCdb:
                case BDSP_AF_P_DistinctOpType_eItb:
                case BDSP_AF_P_DistinctOpType_eDolbyReEncodeAuxDataOut:
                    ui32FMMContentType = BDSP_AF_P_FmmContentType_eCompressed;
                    ui32FMMDstType = BDSP_AF_P_FmmDstFsRate_eBaseRate;
                    ui32BufferDepthThreshold = (BDSP_CIT_P_STANDARD_BUFFER_THRESHOLD + BDSP_CIT_P_MAXIMUM_RESIDUAL_COLLECTION);
                    break;
                case BDSP_AF_P_DistinctOpType_eCompressed4x:
                /*SW7425-6056: It is based on ui32FMMContentType that the FW decides on a type of zero fill.
                Without this check, Spdif preambles were filled in during a zero fill for BTSC
                SWRAA-162: New FMM Dest type added to address the same*/
                    if (pRaagaConnectStage->algorithm == BDSP_Algorithm_eBtscEncoder)
                    {
                        ui32FMMContentType = BDSP_AF_P_FmmContentType_eAnalogCompressed;
                    }else{
                        ui32FMMContentType = BDSP_AF_P_FmmContentType_eCompressed;
                    }
                    ui32FMMDstType = BDSP_AF_P_FmmDstFsRate_e4xBaseRate;
                    ui32BufferDepthThreshold = (BDSP_CIT_P_COMPRESSED4X_BUFFER_THRESHOLD + BDSP_CIT_P_MAXIMUM_RESIDUAL_COLLECTION);
                    break;
                case BDSP_AF_P_DistinctOpType_eCompressedHBR:
                    ui32FMMContentType = BDSP_AF_P_FmmContentType_eCompressed;
                    ui32FMMDstType = BDSP_AF_P_FmmDstFsRate_e16xBaseRate;
                    if(pRaagaConnectStage->algorithm == BDSP_Algorithm_eMlpPassthrough)
                    {
                        /* Note: MLP Passthru uses a different logic for threshold and hence no need to add residual collection. The calculation is explained in the macro defination*/
                        ui32BufferDepthThreshold = BDSP_CIT_P_COMPRESSED16X_MLP_BUFFER_THRESHOLD;
                    }
                    else
                    {
                        ui32BufferDepthThreshold = (BDSP_CIT_P_COMPRESSED16X_BUFFER_THRESHOLD + BDSP_CIT_P_MAXIMUM_RESIDUAL_COLLECTION);
                    }
                    break;
                default:
                    ui32FMMContentType = BDSP_AF_P_FmmContentType_eInvalid;
                    ui32FMMDstType = BDSP_AF_P_FmmDstFsRate_eInvalid;
                    ui32BufferDepthThreshold = 0;
                    break;
                }

                for(channel=0;channel<pRaagaConnectStage->sStageOutput[output].IoBuffer.ui32NumBuffers ;channel++)
                {   /*the buffer itself was allocated by PI and sent as FMM descriptor, just passed on here for GATE Open configuration*/
                    sTaskFmmGateOpenConfig->sFmmGateOpenConfig[ui32NumPorts].uin32RingBufStartWrPointAddr[channel] = pRaagaConnectStage->sStageOutput[output].IoBuffer.sCircBuffer[channel].ui32ReadAddr + 20;
                }

                sTaskFmmGateOpenConfig->sFmmGateOpenConfig[ui32NumPorts].uin32DramIoConfigAddr = pRaagaConnectStage->sStageOutput[output].ui32StageIOBuffCfgAddr;
                sTaskFmmGateOpenConfig->sFmmGateOpenConfig[ui32NumPorts].ui32IndepDelay= pRaagaConnectStage->sStageOutput[output].connectionDetails.fmm.descriptor.delay;
                sTaskFmmGateOpenConfig->sFmmGateOpenConfig[ui32NumPorts].eFMMContentType = ui32FMMContentType;
                sTaskFmmGateOpenConfig->sFmmGateOpenConfig[ui32NumPorts].eFmmDstFsRate = ui32FMMDstType;
                sTaskFmmGateOpenConfig->sFmmGateOpenConfig[ui32NumPorts].ui32BufferDepthThreshold = ui32BufferDepthThreshold;
                ui32NumPorts++;
            }
        }
    }
    BDSP_STAGE_TRAVERSE_LOOP_END(pRaagaConnectStage)

    sTaskFmmGateOpenConfig->ui32NumPorts = ui32NumPorts;
    sTaskFmmGateOpenConfig->ui32MaxIndepDelay = ui32MaxIndepDelay;

    return errCode;
}

BERR_Code BDSP_Raaga_P_RetrieveGateOpenSettings(
                            void *pTaskHandle,
                            BDSP_TaskGateOpenSettings *pSettings   /* [out] */
    )
{
    BERR_Code errCode = BERR_SUCCESS;
    BDSP_RaagaTask *pRaagaTask = (BDSP_RaagaTask *)pTaskHandle;
    BDSP_AF_P_TASK_sFMM_GATE_OPEN_CONFIG sTaskFmmGateOpenConfig;

    if(pRaagaTask->startSettings.gateOpenReqd == true)
    {
        BDBG_ERR(("BDSP_Raaga_P_RetrieveGateOpenSettings: Trying to retrieve Gate Open Settings for a task whose Gate Open already performed"));
        return BERR_INVALID_PARAMETER;
    }

    BKNI_Memset(&sTaskFmmGateOpenConfig,0,sizeof(BDSP_AF_P_TASK_sFMM_GATE_OPEN_CONFIG));
    errCode = BDSP_Raaga_P_PopulateGateOpenFMMStages((void *)pRaagaTask->startSettings.primaryStage->pStageHandle,
        &sTaskFmmGateOpenConfig,
        pRaagaTask->startSettings.maxIndependentDelay);

    if(errCode != BERR_SUCCESS)
    {
        BDBG_ERR(("BDSP_Raaga_P_RetrieveGateOpenSettings: Error in Retrieving the GateOpen Settings for the Task Requested"));
        return errCode;
    }

    pSettings->ui32NumPorts      = sTaskFmmGateOpenConfig.ui32NumPorts;
    pSettings->ui32MaxIndepDelay = sTaskFmmGateOpenConfig.ui32MaxIndepDelay;
    BKNI_Memcpy(pSettings->psFmmGateOpenConfig,
        (void *)&sTaskFmmGateOpenConfig.sFmmGateOpenConfig[0],
        (sTaskFmmGateOpenConfig.ui32NumPorts*sizeof(BDSP_AF_P_sFMM_GATE_OPEN_CONFIG)));

    return errCode;
}

/***********************************************************************
Name        :   BDSP_Raaga_P_GetDefaultTaskStartSettings

Type        :   PI Interface

Input       :   pTaskHandle -   Handle of the Task for which default start settings is required.
                pSettings       -   Pointer to the memory where default start settings are filled.

Return      :   None

Functionality   :   Following are the operations performed.
        1)  Set the Scheduling mode to Standalone, task realtime mode to Realtime.
        2)  Set the primary stage for the task as NULL and Master task as NULL.
        3)  Disable PPM correction and Gate Open at Start to False.
        4)  Disable the STC trigger and external interrupts.
        5)  Reset the STC address and RDB address for Video Encode.
        5)  Set the Maximum Independent delay to 500ms.
***********************************************************************/

void BDSP_Raaga_P_GetDefaultTaskStartSettings(
    void *pTaskHandle,
    BDSP_TaskStartSettings *pSettings    /* [out] */
    )
{

    BDSP_RaagaTask *pRaagaTask;

    pRaagaTask = (BDSP_RaagaTask *)pTaskHandle;

    BDBG_OBJECT_ASSERT(pRaagaTask, BDSP_RaagaTask);
    BDBG_ASSERT(NULL != pSettings);

    BKNI_Memset((void *)pSettings,0,sizeof(BDSP_TaskStartSettings));

    pSettings->primaryStage = NULL;
    pSettings->schedulingMode = BDSP_TaskSchedulingMode_eStandalone;
    pSettings->realtimeMode = BDSP_TaskRealtimeMode_eRealTime;
    pSettings->masterTask = NULL;
    pSettings->audioTaskDelayMode = BDSP_AudioTaskDelayMode_eDefault;
    pSettings->timeBaseType = BDSP_AF_P_TimeBaseType_e45Khz;
    pSettings->ppmCorrection = false;
    pSettings->openGateAtStart = false;
    pSettings->stcIncrementConfig.enableStcTrigger = false;
    pSettings->extInterruptConfig.enableInterrupts = false;
    /*Enable Zero Phase Correction in default settings*/
    pSettings->eZeroPhaseCorrEnable=true;

    pSettings->pSampleRateMap = NULL;
    pSettings->maxIndependentDelay = BDSP_AF_P_MAX_INDEPENDENT_DELAY;

    pSettings->gateOpenReqd = true;
}

/***********************************************************************
Name        :   BDSP_Raaga_P_GetDefaultStageCreateSettings

Type        :   PI Interface

Input       :   algoType        -   The algorithm type of the stage for which default settings is requested.
                pSettings       -   Stage creating settings pointer where the default settings is filled and returned to PI.

Return      :   None

Functionality   :   Following are the operations performed.
        1)  Validate if the algorithm type is supported or not.
        2)  Fill the maximum inputs and ouputs supported for the algorithm type requested.
***********************************************************************/

void BDSP_Raaga_P_GetDefaultStageCreateSettings(
    BDSP_AlgorithmType algoType,
    BDSP_StageCreateSettings *pSettings /* [out] */
    )
{
    int i;

    const BDSP_Raaga_P_AlgorithmInfo *pAlgoInfo;

    BDBG_ASSERT(NULL != pSettings);
    BDBG_ASSERT(algoType < BDSP_AlgorithmType_eMax);

    pSettings->algoType = algoType;

    for (i = 0; i < BDSP_Algorithm_eMax; i++)
    {
        pAlgoInfo = BDSP_Raaga_P_LookupAlgorithmInfo(i);

        if (pSettings->algoType == pAlgoInfo->type)
        {
            pSettings->algorithmSupported[i] = pAlgoInfo->supported;
        }
        else
        {
            pSettings->algorithmSupported[i] = false;
        }
    }

    switch (algoType)
    {
        case BDSP_AlgorithmType_eAudioDecode:
            pSettings->maxInputs = 1;
            pSettings->maxOutputs = 3;
            break;
        case BDSP_AlgorithmType_eAudioPassthrough:  /* Enable all supported audio passthrough codecs by default. Max inputs = 2 */
            pSettings->maxInputs = 1;
            pSettings->maxOutputs = 1;
            break;
        case BDSP_AlgorithmType_eAudioEncode: /* Enable all supported audio encode codecs by default. Max inputs = 1 */
            pSettings->maxInputs = 1;
            pSettings->maxOutputs = 1;
            break;
        case BDSP_AlgorithmType_eAudioMixer: /* Enable mixer algorithm by default.  Max inputs = 3 */
            pSettings->maxInputs = 3;
            pSettings->maxOutputs = 1;
            break;
        case BDSP_AlgorithmType_eAudioEchoCanceller: /* Enable all echo cancellation algorithms by default.  Max inputs = 2 */
            pSettings->maxInputs = 2;
            pSettings->maxOutputs = 1;
            break;
        case BDSP_AlgorithmType_eAudioProcessing: /* Nothing enabled by default.  Max inputs = 1 */
            pSettings->maxInputs = 1;
            pSettings->maxOutputs = 2;
            break;
        case BDSP_AlgorithmType_eVideoDecode: /* Enable all video decode algorithms by default. Max inputs = 2 */
            /* TBD: Video CIT refactoring : Need to assign the appropriate values for max inputs and outputs */
            pSettings->maxInputs = 1;
            pSettings->maxOutputs = 1;
            break;
        case BDSP_AlgorithmType_eVideoEncode: /* Enable all video encode algorithms by default. Max inputs = 1 */
            /* TBD: Video CIT refactoring : Need to assign the appropriate values for max inputs and outputs */
            pSettings->maxInputs = 1;
            pSettings->maxOutputs = 1;
            break;
        case BDSP_AlgorithmType_eSecurity: /* Enable all security algorithms by default. Max inputs = 1 */
            /* TBD: Security CIT refactoring : Need to assign the appropriate values for max inputs and outputs */
            pSettings->maxInputs = 0;
            pSettings->maxOutputs = 0;
            break;
        case BDSP_AlgorithmType_eCustom: /* Nothing enabled by default.  Max inputs = 1 */
            pSettings->maxInputs = 1;
            pSettings->maxOutputs = 1;
            break;
        default:
            /* Nothing to be done because the assert at start will ensure the default case is never hit */
            break;
    }
}

/***********************************************************************
Name        :   BDSP_Raaga_P_CreateStage

Type        :   PI Interface

Input       :   pContextHandle  -   Handle of the Context for which the stage needs to created.
                pSettings           -   Settings of the Stage to be created.
                pStageHandle        -   Handle of the Stage which is returned back to PI.

Return      :   Error Code to return SUCCESS or FAILURE

Functionality   :   Following are the operations performed.
        1)  Allocate and Intialise the memory for the Stage Descriptor.
        2)  Allocate the memory required for the Stage.
        3)  Intialise all the function pointers which will be used by the PI for further processing.
        4)  Set the Algorithm for the Stage.
        5)  Perform Error Handling if any required.
***********************************************************************/

BERR_Code BDSP_Raaga_P_CreateStage(
    void *pContextHandle,
    const BDSP_StageCreateSettings *pSettings,
    BDSP_StageHandle *pStageHandle /* [out] */
    )
{
    BERR_Code errCode = BERR_SUCCESS;
    BDSP_RaagaStage *pStage;
    unsigned i;

    pStage = BKNI_Malloc(sizeof(BDSP_RaagaStage));
    if ( NULL == pStage )
    {
        errCode = BERR_TRACE(BERR_OUT_OF_SYSTEM_MEMORY);
        goto err_malloc_stage;
    }

    BKNI_Memset(pStage, 0, sizeof(*pStage));
    pStage->algorithm = BDSP_Algorithm_eMax;
    /*BDBG_OBJECT_SET(pStage, BDSP_RaagaStage);*/

    BDSP_P_InitStage(&pStage->stage, pStage);
    pStage->settings = *pSettings;
    pStage->pContext = pContextHandle;

    errCode = BDSP_Raaga_P_AllocateStageMemory((void *)pStage);
    if ( errCode )
    {
        errCode = BERR_TRACE(errCode);
        goto err_stage_memory;
    }

    /* Initialize the stage apis */
    pStage->stage.destroy = BDSP_Raaga_P_DestroyStage;
    pStage->stage.setAlgorithm = BDSP_Raaga_P_SetAlgorithm;
    pStage->stage.getStageSettings = BDSP_Raaga_P_GetStageSettings;
    pStage->stage.setStageSettings = BDSP_Raaga_P_SetStageSettings;
    pStage->stage.getStageStatus = BDSP_Raaga_P_GetStageStatus;

    pStage->stage.getTsmSettings_isr = BDSP_Raaga_P_GetTsmSettings_isr;
    pStage->stage.setTsmSettings_isr = BDSP_Raaga_P_SetTsmSettings_isr;
    pStage->stage.getTsmStatus_isr = BDSP_Raaga_P_GetTsmStatus_isr;
    pStage->stage.getDatasyncSettings = BDSP_Raaga_P_GetDatasyncSettings;
    pStage->stage.setDatasyncSettings = BDSP_Raaga_P_SetDatasyncSettings;
    pStage->stage.getDatasyncStatus_isr = BDSP_Raaga_P_GetDatasyncStatus_isr;

    pStage->stage.addFmmOutput = BDSP_Raaga_P_AddFmmOutput;
    pStage->stage.addRaveOutput = BDSP_Raaga_P_AddRaveOutput;
    pStage->stage.addOutputStage = BDSP_Raaga_P_AddOutputStage;
    pStage->stage.removeOutput = BDSP_Raaga_P_RemoveOutput;
    pStage->stage.removeAllOutputs = BDSP_Raaga_P_RemoveAllOutputs;
    pStage->stage.addFmmInput = BDSP_Raaga_P_AddFmmInput;
    pStage->stage.addRaveInput = BDSP_Raaga_P_AddRaveInput;
    pStage->stage.removeInput = BDSP_Raaga_P_RemoveInput;
    pStage->stage.removeAllInputs = BDSP_Raaga_P_RemoveAllInputs;

    pStage->stage.addInterTaskBufferInput = BDSP_Raaga_P_AddInterTaskBufferInput;
    pStage->stage.addInterTaskBufferOutput = BDSP_Raaga_P_AddInterTaskBufferOutput;

    pStage->stage.addQueueInput = BDSP_Raaga_P_AddQueueInput;
    pStage->stage.addQueueOutput = BDSP_Raaga_P_AddQueueOutput;
    if (BDSP_ContextType_eVideoEncode == pStage->pContext->settings.contextType)
    {
        pStage->stage.getVideoEncodeDatasyncSettings = BDSP_Raaga_P_GetVideoEncodeDatasyncSettings;
        pStage->stage.setVideoEncodeDatasyncSettings = BDSP_Raaga_P_SetVideoEncodeDatasyncSettings;
    }


    pStage->running = false;
    pStage->pRaagaTask = NULL;

    pStage->totalInputs = 0;
    pStage->totalOutputs = 0;
    for (i = 0; i < BDSP_ConnectionType_eMax; i++)
    {
        pStage->numInputs[i] = 0;
        pStage->numOutputs[i] = 0;
    }

    BDBG_OBJECT_SET(pStage, BDSP_RaagaStage);

    errCode = BERR_INVALID_PARAMETER;
    for ( i = 0; i < BDSP_Algorithm_eMax; i++ )
    {
        if (pSettings->algorithmSupported[i])
        {
            errCode = BDSP_Raaga_P_SetAlgorithm(pStage, i);
            break;
        }
    }

    if ( errCode )
    {
        errCode = BERR_TRACE(errCode);
        goto err_algorithm;
    }

    /* Sucess, assign the handle. This should be done just before we exit with success */
    *pStageHandle=&pStage->stage;
    return BERR_SUCCESS;

err_algorithm:
    BDSP_Raaga_P_FreeStageMemory(pStage);
    BDBG_OBJECT_DESTROY(pStage, BDSP_RaagaStage);
err_stage_memory:
    BKNI_Free(pStage);
err_malloc_stage:

    return errCode;
}

/***********************************************************************
Name        :   BDSP_Raaga_P_DestroyStage

Type        :   PI Interface

Input       :   pStageHandle        -   Handle of the Stage which needs to be destroyed.

Return      :   None

Functionality   :   Following are the operations performed.
        1)  Free all the memory was allocated/associated with the Stage.
        2)  Free the Stage Descriptor memory.
***********************************************************************/

void BDSP_Raaga_P_DestroyStage(
    void *pStageHandle
    )
{
    BDSP_RaagaStage *pRaagaStage = (BDSP_RaagaStage *)pStageHandle;
    BDSP_Raaga_P_FreeStageMemory(pRaagaStage);
    BDBG_OBJECT_DESTROY(pRaagaStage, BDSP_RaagaStage);
    BKNI_Free(pRaagaStage);
}

/***********************************************************************
Name        :   BDSP_Raaga_GetAlgorithmDefaultSettings

Type        :   PI Interface

Input       :   pDeviceHandle -Device Handle which needs to be closed.
                algorithm - Algorithms for which default userconfig is requested by PI.
                pSettingsBuffer - Pointer where default userconfig is returned to PI.
                settingsBufferSize - Size of the default userconfig is requested by PI.

Return      :   None

Functionality   :   Return the Default UserConfig of the algorithm requested by the PI.
***********************************************************************/

void BDSP_Raaga_GetAlgorithmDefaultSettings(
    void *pDeviceHandle,
    BDSP_Algorithm algorithm,
    void *pSettingsBuffer,        /* [out] */
    size_t settingsBufferSize
    )
{
    const BDSP_Raaga_P_AlgorithmInfo *pAlgoInfo;
    BDSP_Raaga *pDevice =(BDSP_Raaga *)pDeviceHandle;


    BDBG_ASSERT(NULL != pSettingsBuffer);
    BDBG_ASSERT(algorithm < BDSP_Algorithm_eMax);

    pAlgoInfo = BDSP_Raaga_P_LookupAlgorithmInfo(algorithm);

    if(pAlgoInfo->userConfigSize != settingsBufferSize)
    {
        BDBG_ERR(("settingsBufferSize (%lu) is not equal to Config size (%lu) of Algorithm %s",
            (unsigned long)settingsBufferSize,(unsigned long)pAlgoInfo->userConfigSize,
            pAlgoInfo->pName));
        BDBG_ASSERT(0);
    }

    BKNI_Memcpy((void *)pSettingsBuffer, (void *)pAlgoInfo->pDefaultUserConfig, settingsBufferSize);
    BDSP_MEM_P_FlushCache(pDevice->memHandle, (void *)pSettingsBuffer, settingsBufferSize);

}

/***********************************************************************
Name        :   BDSP_Raaga_P_SetAlgorithm

Type        :   PI Interface

Input       :   pStageHandle        -   Handle of the Stage whose algorithm needs to be Set.
                algorithm           -   Algorithm to be Set for the Stage

Return      :   Error Code to return SUCCESS or FAILURE

Functionality   :   Following are the operations performed.
        1)  Retreive the information for algorithm provided by the PI and the algorithm already set for the Stage.
        2)  Check if algorithm is supported or if Stage is already running.
        3)  Check if total inputs and outputs are non-zero for the Stage.
        4)  Check if there is an attempt to change the Algorithm Type for the stage.
        5)  Load the default algorithm settings for the stage.
        6)  Load the default ids settings if IDS is required for the algorithm.
        7)  Reset the Status buffer for the Algorithm.
***********************************************************************/

BERR_Code BDSP_Raaga_P_SetAlgorithm(
    void *pStageHandle,
    BDSP_Algorithm algorithm
    )
{
    BDSP_RaagaStage *pRaagaStage;
    const BDSP_Raaga_P_AlgorithmInfo *pAlgoInfo;
    const BDSP_Raaga_P_AlgorithmInfo *pCurrAlgoInfo;
    void *pUserCfgAddr, *pStatusBuffAddr;
    bool validType;

    BDSP_Raaga *pDevice;

    BDBG_ENTER(BDSP_Raaga_P_SetAlgorithm);

    BDBG_ASSERT(NULL != pStageHandle);

    pRaagaStage = (BDSP_RaagaStage *)pStageHandle;
    pAlgoInfo = BDSP_Raaga_P_LookupAlgorithmInfo(algorithm);
    pCurrAlgoInfo = BDSP_Raaga_P_LookupAlgorithmInfo(pRaagaStage->algorithm);
    pDevice = pRaagaStage->pContext->pDevice;

    BDBG_MSG(("Setting Algorithm to %s(%u) for stage %p", pAlgoInfo->pName,algorithm, (void *)pStageHandle));

    /*  Returns error if the algorithm is not supported */
    if (!(pAlgoInfo->supported))
    {
        BDBG_ERR(("BDSP_Algorithm (%d) not supported", algorithm));
        return BERR_TRACE(BERR_NOT_SUPPORTED);
    }

    if (pRaagaStage->totalOutputs)
    {
        BDBG_ERR(("Stage has non-zero (%d) output connections at set algorithm", pRaagaStage->totalOutputs));
        return BERR_TRACE(BERR_NOT_SUPPORTED);
    }

    if (pRaagaStage->totalInputs)
    {
        BDBG_ERR(("Stage has non-zero (%d) input connections at set algorithm", pRaagaStage->totalInputs));
        return BERR_TRACE(BERR_NOT_SUPPORTED);
    }

    /*  Return error if the stage is running.*/
    if (pRaagaStage->running)
    {
        BDBG_ERR(("Cannot set algorithm when the stage is running : stage handle = 0x%p : Current algo = %s",
                   pStageHandle, pCurrAlgoInfo->pName));
        return BERR_TRACE(BERR_NOT_SUPPORTED);
    }

    if( !pRaagaStage->settings.algorithmSupported[algorithm])
    {
        BDBG_ERR((" algorithm %s (%d) being passed in %s was not enabled during CreateStage call ",
                    pAlgoInfo->pName,algorithm, __FUNCTION__));
        return BERR_TRACE(BERR_NOT_SUPPORTED);
    }

    /*  Return error if there is an attempt to change the stage type */
    if ( pRaagaStage->settings.algoType == BDSP_AlgorithmType_eAudioDecode )
    {
        switch ( pAlgoInfo->type )
        {
        case BDSP_AlgorithmType_eAudioDecode:
        case BDSP_AlgorithmType_eAudioPassthrough:
            validType = true;
            break;
        default:
            validType = false;
            break;
        }
    }
    else
    {
        validType = (pRaagaStage->settings.algoType == pAlgoInfo->type) ? true : false;
    }
    if ( !validType )
    {
        BDBG_ERR(("Cannot change the algo type of the stage from %d (%s) to %d (%s)",
                    pCurrAlgoInfo->type, pCurrAlgoInfo->pName, pAlgoInfo->type, pAlgoInfo->pName));
        return BERR_TRACE(BERR_NOT_SUPPORTED);
    }

    pRaagaStage->algorithm = pAlgoInfo->algorithm;

    if(pAlgoInfo->userConfigSize)
    {
    /* Load the default algorithm settings */
    BDSP_MEM_P_ConvertOffsetToCacheAddr(pDevice->memHandle,
        pRaagaStage->sDramUserConfigBuffer.ui32DramBufferAddress, (void **)&pUserCfgAddr);

    BDSP_Raaga_GetAlgorithmDefaultSettings((void *)pDevice,
        pRaagaStage->algorithm,
        pUserCfgAddr,
        pAlgoInfo->userConfigSize);
    }

    /* Load the default ids settings */
    if (pAlgoInfo->idsConfigSize)
    {
        uint32_t fsBufAddr;

        fsBufAddr = pRaagaStage->sDramUserConfigBuffer.ui32DramBufferAddress +
                    pRaagaStage->sFrameSyncOffset.ui32UserCfgOffset;

        BDSP_MEM_P_ConvertOffsetToCacheAddr(pDevice->memHandle, fsBufAddr, (void **)&pUserCfgAddr);

        BKNI_Memcpy((void *)pUserCfgAddr, (void *)pAlgoInfo->pDefaultIdsConfig, pAlgoInfo->idsConfigSize);
        BDSP_MEM_P_FlushCache(pDevice->memHandle, (void *)pUserCfgAddr, pAlgoInfo->idsConfigSize);

        /* Initilaise both the HOST and DSP Frame Sync Settings to maintain consistence while the Stage is Stopped.
             Get Settings retrieves the data from HOST buffer(spare) and if this data is not initialised then, there may be case
             of junk data fed to the FW. */

        fsBufAddr = pRaagaStage->sDramUserConfigSpareBuffer.ui32DramBufferAddress +
                    pRaagaStage->sFrameSyncOffset.ui32UserCfgOffset;

        BDSP_MEM_P_ConvertOffsetToCacheAddr(pDevice->memHandle, fsBufAddr, (void **)&pUserCfgAddr);

        BKNI_Memcpy((void *)pUserCfgAddr, (void *)pAlgoInfo->pDefaultIdsConfig, pAlgoInfo->idsConfigSize);
        BDSP_MEM_P_FlushCache(pDevice->memHandle, (void *)pUserCfgAddr, pAlgoInfo->idsConfigSize);
    }


    /* Reset the Status buffer */
    if( pRaagaStage->sDramStatusBuffer.ui32BufferSizeInBytes)
    {
    BDSP_MEM_P_ConvertOffsetToCacheAddr(pDevice->memHandle,
        pRaagaStage->sDramStatusBuffer.ui32DramBufferAddress, (void **)&pStatusBuffAddr);

    BKNI_Memset((void *)pStatusBuffAddr, 0xFF, pRaagaStage->sDramStatusBuffer.ui32BufferSizeInBytes);
    BDSP_MEM_P_FlushCache(pDevice->memHandle, (void *)pStatusBuffAddr, pRaagaStage->sDramStatusBuffer.ui32BufferSizeInBytes);
    }

    BDBG_LEAVE(BDSP_Raaga_P_SetAlgorithm);
    return BERR_SUCCESS;
}

/***********************************************************************
Name        :   BDSP_Raaga_P_InterTaskBuffer_Create

Type        :   PI Interface

Input       :   pContextHandle  -   Context handle provided by the PI.
                dataType            -   Type of data which will be present in the Intertask buffer.
                pInterTaskBufferHandle  -   Handle of the Intertask buffer returned back to PI.

Return      :   Error Code to return SUCCESS or FAILURE

Functionality   :   Following are the operations performed.
        1)  Allocate and initilaise the memory for the Intertask buffer descriptor structure.
        2)  Allocate the memory for I/O buffer depending on the number of channels.
        3)  Allocate the memory for the I/O Generic buffer.
        4)  Allocate the memory for the I/O and I/O Generic descriptors.
        5)  Populate the I/O and I/O Generic descriptors with the data.
        6)  Intialise the function pointers for destroy and flush which will be used by the PI for further processing.
        7)  Fill the Intertask buffer handle for further use by PI.
***********************************************************************/

BERR_Code BDSP_Raaga_P_InterTaskBuffer_Create(
    void *pContextHandle,
    BDSP_DataType dataType,
    BDSP_BufferType bufferType,
    BDSP_InterTaskBufferHandle *pInterTaskBufferHandle
    )
{
    BERR_Code errCode = BERR_SUCCESS;
    BDSP_P_InterTaskBuffer *pInterTaskBuffer;
    BDSP_AF_P_DistinctOpType distinctOp;
    BDSP_RaagaContext *pContext;
    unsigned memReqd, channels, i;
    raaga_dramaddr physAddr;
    void *pIoAddress, *pIoGenAddress;
    BDSP_AF_P_sIO_BUFFER *pIoBuffDesc_Cached = NULL;
    BDSP_AF_P_sIO_GENERIC_BUFFER *pIoGenBuffDesc_Cached = NULL;
    unsigned  ui32RegOffset = 0;
    signed  i32FifoId;
    unsigned ui32DspOffset = 0;

    BDBG_ENTER(BDSP_Raaga_P_InterTaskBuffer_Create);
    if((bufferType != BDSP_BufferType_eRDB)&&(bufferType != BDSP_BufferType_eDRAM))
    {
        BDBG_ERR(("Only DRAM and RDB handle for InterTask buffer supported in Raaga!"));
        errCode = BERR_TRACE(BERR_INVALID_PARAMETER);
        goto err_buffer_type;
    }

    pContext = (BDSP_RaagaContext *)pContextHandle;

    pInterTaskBuffer = BKNI_Malloc(sizeof(BDSP_P_InterTaskBuffer));
    if ( NULL == pInterTaskBuffer )
    {
        BDBG_ERR(("Unable to Allocate memory for BDSP_P_InterTaskBuffer !"));
        errCode = BERR_TRACE(BERR_OUT_OF_SYSTEM_MEMORY);
        goto err_malloc_inter_task_buffer;
    }
    BKNI_Memset(pInterTaskBuffer, 0, sizeof(*pInterTaskBuffer));

    BDSP_P_InitInterTaskBuffer(&pInterTaskBuffer->interTaskBuffer, pInterTaskBuffer);
    pInterTaskBuffer->inUse = false;
    pInterTaskBuffer->dataType = dataType;
    pInterTaskBuffer->srcHandle = NULL;
    pInterTaskBuffer->dstHandle = NULL;
    pInterTaskBuffer->srcIndex = -1;
    pInterTaskBuffer->dstIndex = -1;
    pInterTaskBuffer->pContext = pContextHandle;
    /* Allocate the IO buffer and populate the IO buffer descriptor */
    BDSP_Raaga_P_GetDistinctOpTypeAndNumChans(dataType, &channels, &distinctOp);
    pInterTaskBuffer->numChans = channels;
    pInterTaskBuffer->distinctOp = distinctOp;

    memReqd = channels*BDSP_AF_P_INTERTASK_IOBUFFER_SIZE;

    pIoAddress = BDSP_MEM_P_AllocateAlignedMemory(pContext->pDevice->memHandle, memReqd, 5, 0);    /* 32 bit aligned*/
    if ( NULL == pIoAddress )
    {
        BDBG_ERR(("Unable to Allocate memory for inter task io Buffer !"));
        errCode = BERR_TRACE(BERR_OUT_OF_DEVICE_MEMORY);
        goto err_io_buff_malloc;
    }

    pInterTaskBuffer->pIoBuffer = pIoAddress;


    /* Allocate the IO Generic buffer and populate the IO generic buffer descriptor */
    BDSP_Raaga_P_GetDistinctOpTypeAndNumChans(dataType, &channels, &distinctOp);
    memReqd = BDSP_AF_P_INTERTASK_IOGENBUFFER_SIZE;

    pIoGenAddress = BDSP_MEM_P_AllocateAlignedMemory(pContext->pDevice->memHandle, memReqd, 5, 0);    /* 32 bit aligned*/
    if ( NULL == pIoGenAddress )
    {
        BDBG_ERR(("Unable to Allocate memory for inter task generic Buffer !"));
        errCode = BERR_TRACE(BERR_OUT_OF_DEVICE_MEMORY);
        goto err_io_gen_buff_malloc;
    }

    pInterTaskBuffer->pIoGenBuffer = pIoGenAddress;

    /* Allocate the descriptors */
    pInterTaskBuffer->pIoBufferDesc = BDSP_MEM_P_AllocateAlignedMemory(
        pContext->pDevice->memHandle,
        sizeof(BDSP_AF_P_sIO_BUFFER) + sizeof(BDSP_AF_P_sIO_GENERIC_BUFFER), 2, 0);
    if (NULL == pInterTaskBuffer->pIoBufferDesc)
    {
        BDBG_ERR(("Unable to Allocate memory for inter task buffer descriptors!"));
        errCode = BERR_TRACE(BERR_OUT_OF_DEVICE_MEMORY);
        goto err_desc_alloc;
    }

    pIoBuffDesc_Cached = (BDSP_AF_P_sIO_BUFFER *)pInterTaskBuffer->pIoBufferDesc;
    pIoBuffDesc_Cached->ui32NumBuffers= channels;

    if(BDSP_BufferType_eRDB == bufferType)
    {
        pIoBuffDesc_Cached->eBufferType = BDSP_AF_P_BufferType_eRDB;
        pInterTaskBuffer->pMsgQueueParams = BDSP_MEM_P_AllocateAlignedMemory(pContext->pDevice->memHandle,(channels + 1)*SIZEOF(BDSP_Raaga_P_MsgQueueParams),5,0);/* Channel +1 is for BDSP_AF_P_sIO_BUFFER*/
        if (NULL == pInterTaskBuffer->pMsgQueueParams)
        {
            BDBG_ERR(("Unable to Allocate memory for inter task MsgQueueParams!"));
            errCode = BERR_TRACE(BERR_OUT_OF_DEVICE_MEMORY);
            goto err_msg_params_alloc;
        }
        ui32DspOffset = pContext->pDevice->dspOffset[BDSP_RAAGA_DSP_INDEX_INTERTASK];/* DSPindex is assumed to be zero*/
        ui32RegOffset = BCHP_RAAGA_DSP_FW_CFG_FIFO_1_BASE_ADDR - \
            BCHP_RAAGA_DSP_FW_CFG_FIFO_0_BASE_ADDR;
    }
    else
    {
        pIoBuffDesc_Cached->eBufferType = BDSP_AF_P_BufferType_eDRAM;
    }

    BDSP_MEM_P_ConvertAddressToOffset(pContext->pDevice->memHandle, pIoAddress, &physAddr);

    for (i = 0; i < channels; i++)
    {
        if(BDSP_BufferType_eRDB == bufferType)
        {
            BDSP_Raaga_P_MsgQueueParams *pMsgQueueParam;
            pMsgQueueParam = (BDSP_Raaga_P_MsgQueueParams *)(((BDSP_Raaga_P_MsgQueueParams *)pInterTaskBuffer->pMsgQueueParams)+i);

            errCode = BDSP_Raaga_P_AssignFreeFIFO(pContext->pDevice, BDSP_RAAGA_DSP_INDEX_INTERTASK, &i32FifoId, 1 );/* DSPindex is assumed to be zero*/
            if(errCode)
            {
                BDBG_ERR(("Unable to find a free FIFO for Intertask Buffer channel Number %d !!!!",i));
                goto err_rdb_alloc_io;
            }
            pMsgQueueParam->i32FifoId = i32FifoId;
            pMsgQueueParam->pBaseAddr = (void *)((uint8_t *)pIoAddress+ (i*BDSP_AF_P_INTERTASK_IOBUFFER_SIZE));
            pMsgQueueParam->uiMsgQueueSize = BDSP_AF_P_INTERTASK_IOBUFFER_SIZE;

            BDSP_Write32(
                pContext->pDevice->regHandle,
                BCHP_RAAGA_DSP_FW_CFG_FIFO_0_BASE_ADDR +
                (ui32RegOffset * i32FifoId) +
                BDSP_RAAGA_P_FIFO_BASE_OFFSET + ui32DspOffset,
                physAddr + i*BDSP_AF_P_INTERTASK_IOBUFFER_SIZE); /* base */

            BDSP_Write32(
                pContext->pDevice->regHandle,
                BCHP_RAAGA_DSP_FW_CFG_FIFO_0_BASE_ADDR +
                (ui32RegOffset * i32FifoId) +
                BDSP_RAAGA_P_FIFO_END_OFFSET + ui32DspOffset,
                physAddr + (i+1)*BDSP_AF_P_INTERTASK_IOBUFFER_SIZE - 4); /* end */

            BDSP_Write32(
                pContext->pDevice->regHandle,
                BCHP_RAAGA_DSP_FW_CFG_FIFO_0_BASE_ADDR +
                (ui32RegOffset * i32FifoId) +
                BDSP_RAAGA_P_FIFO_READ_OFFSET + ui32DspOffset,
                physAddr + i*BDSP_AF_P_INTERTASK_IOBUFFER_SIZE); /* read */

            BDSP_Write32(
                pContext->pDevice->regHandle,
                BCHP_RAAGA_DSP_FW_CFG_FIFO_0_BASE_ADDR +
                (ui32RegOffset * i32FifoId) +
                BDSP_RAAGA_P_FIFO_WRITE_OFFSET + ui32DspOffset,
                physAddr + i*BDSP_AF_P_INTERTASK_IOBUFFER_SIZE); /* write */


            pIoBuffDesc_Cached->sCircBuffer[i].ui32BaseAddr = BDSP_RAAGA_REGSET_PHY_ADDR_FOR_DSP(BCHP_RAAGA_DSP_FW_CFG_FIFO_0_BASE_ADDR +
                                                                (ui32RegOffset * i32FifoId) + BDSP_RAAGA_P_FIFO_BASE_OFFSET + ui32DspOffset);
            pIoBuffDesc_Cached->sCircBuffer[i].ui32EndAddr = BDSP_RAAGA_REGSET_PHY_ADDR_FOR_DSP(BCHP_RAAGA_DSP_FW_CFG_FIFO_0_BASE_ADDR +
                                                                (ui32RegOffset * i32FifoId) + BDSP_RAAGA_P_FIFO_END_OFFSET + ui32DspOffset);
            pIoBuffDesc_Cached->sCircBuffer[i].ui32ReadAddr = BDSP_RAAGA_REGSET_PHY_ADDR_FOR_DSP(BCHP_RAAGA_DSP_FW_CFG_FIFO_0_BASE_ADDR +
                                                                (ui32RegOffset * i32FifoId) + BDSP_RAAGA_P_FIFO_READ_OFFSET + ui32DspOffset);
            pIoBuffDesc_Cached->sCircBuffer[i].ui32WriteAddr = BDSP_RAAGA_REGSET_PHY_ADDR_FOR_DSP(BCHP_RAAGA_DSP_FW_CFG_FIFO_0_BASE_ADDR +
                                                                (ui32RegOffset * i32FifoId) + BDSP_RAAGA_P_FIFO_WRITE_OFFSET + ui32DspOffset);
            pIoBuffDesc_Cached->sCircBuffer[i].ui32WrapAddr = BDSP_RAAGA_REGSET_PHY_ADDR_FOR_DSP(BCHP_RAAGA_DSP_FW_CFG_FIFO_0_BASE_ADDR +
                                                                (ui32RegOffset * i32FifoId) + BDSP_RAAGA_P_FIFO_END_OFFSET + ui32DspOffset);
        }
        else
        {
            pIoBuffDesc_Cached->sCircBuffer[i].ui32BaseAddr = physAddr + i*BDSP_AF_P_INTERTASK_IOBUFFER_SIZE;
            pIoBuffDesc_Cached->sCircBuffer[i].ui32EndAddr = physAddr + (i+1)*BDSP_AF_P_INTERTASK_IOBUFFER_SIZE - 4;
            pIoBuffDesc_Cached->sCircBuffer[i].ui32ReadAddr = physAddr + i*BDSP_AF_P_INTERTASK_IOBUFFER_SIZE;
            pIoBuffDesc_Cached->sCircBuffer[i].ui32WriteAddr = physAddr + i*BDSP_AF_P_INTERTASK_IOBUFFER_SIZE;
            pIoBuffDesc_Cached->sCircBuffer[i].ui32WrapAddr = physAddr + (i+1)*BDSP_AF_P_INTERTASK_IOBUFFER_SIZE - 4;
        }

    }
    BDSP_MEM_P_FlushCache(pContext->pDevice->memHandle, (void *)pIoBuffDesc_Cached, sizeof(*pIoBuffDesc_Cached));

    pInterTaskBuffer->pIoBufferGenericDesc = (void *)((uint8_t *)pInterTaskBuffer->pIoBufferDesc + sizeof(BDSP_AF_P_sIO_BUFFER));


    pIoGenBuffDesc_Cached = pInterTaskBuffer->pIoBufferGenericDesc;

    pIoGenBuffDesc_Cached->ui32NumBuffers = 1;

    if(BDSP_BufferType_eRDB == bufferType)
    {
        pIoGenBuffDesc_Cached->eBufferType = BDSP_AF_P_BufferType_eRDB;
    }
    else
    {
        pIoGenBuffDesc_Cached->eBufferType = BDSP_AF_P_BufferType_eDRAM;
    }
    BDSP_MEM_P_ConvertAddressToOffset(pContext->pDevice->memHandle, pIoGenAddress, &physAddr);
    if(BDSP_BufferType_eRDB == bufferType)
    {
        BDSP_Raaga_P_MsgQueueParams *pMsgQueueParam;
        pMsgQueueParam = (BDSP_Raaga_P_MsgQueueParams *)(((BDSP_Raaga_P_MsgQueueParams *)pInterTaskBuffer->pMsgQueueParams)+i);

        errCode = BDSP_Raaga_P_AssignFreeFIFO(pContext->pDevice, BDSP_RAAGA_DSP_INDEX_INTERTASK, &i32FifoId, 1 );/* SR: DSPindex is assumed to be zero*/
        if(errCode)
        {
            BDBG_ERR(("Unable to find a free FIFO for Intertask Buffer's IO Generic buffer !!!!"));
            goto err_rdb_alloc_iogen;
        }
        pMsgQueueParam->i32FifoId = i32FifoId;
        pMsgQueueParam->pBaseAddr = pIoGenAddress;
        pMsgQueueParam->uiMsgQueueSize = BDSP_AF_P_INTERTASK_IOGENBUFFER_SIZE;

        BDSP_Write32(
            pContext->pDevice->regHandle,
            BCHP_RAAGA_DSP_FW_CFG_FIFO_0_BASE_ADDR +
            (ui32RegOffset * i32FifoId) +
            BDSP_RAAGA_P_FIFO_BASE_OFFSET + ui32DspOffset,
            physAddr); /* base */

        BDSP_Write32(
            pContext->pDevice->regHandle,
            BCHP_RAAGA_DSP_FW_CFG_FIFO_0_BASE_ADDR +
            (ui32RegOffset * i32FifoId) +
            BDSP_RAAGA_P_FIFO_END_OFFSET + ui32DspOffset,
            physAddr + BDSP_AF_P_INTERTASK_IOGENBUFFER_SIZE - 4); /* end */

        BDSP_Write32(
            pContext->pDevice->regHandle,
            BCHP_RAAGA_DSP_FW_CFG_FIFO_0_BASE_ADDR +
            (ui32RegOffset * i32FifoId) +
            BDSP_RAAGA_P_FIFO_READ_OFFSET + ui32DspOffset,
            physAddr); /* read */

        BDSP_Write32(
            pContext->pDevice->regHandle,
            BCHP_RAAGA_DSP_FW_CFG_FIFO_0_BASE_ADDR +
            (ui32RegOffset * i32FifoId) +
            BDSP_RAAGA_P_FIFO_WRITE_OFFSET + ui32DspOffset,
            physAddr ); /* write */

        pIoGenBuffDesc_Cached->sCircBuffer.ui32BaseAddr = BDSP_RAAGA_REGSET_PHY_ADDR_FOR_DSP(BCHP_RAAGA_DSP_FW_CFG_FIFO_0_BASE_ADDR +
                                                            (ui32RegOffset * i32FifoId) + BDSP_RAAGA_P_FIFO_BASE_OFFSET + ui32DspOffset);
        pIoGenBuffDesc_Cached->sCircBuffer.ui32EndAddr = BDSP_RAAGA_REGSET_PHY_ADDR_FOR_DSP(BCHP_RAAGA_DSP_FW_CFG_FIFO_0_BASE_ADDR +
                                                            (ui32RegOffset * i32FifoId) + BDSP_RAAGA_P_FIFO_END_OFFSET + ui32DspOffset);
        pIoGenBuffDesc_Cached->sCircBuffer.ui32ReadAddr = BDSP_RAAGA_REGSET_PHY_ADDR_FOR_DSP(BCHP_RAAGA_DSP_FW_CFG_FIFO_0_BASE_ADDR +
                                                            (ui32RegOffset * i32FifoId) + BDSP_RAAGA_P_FIFO_READ_OFFSET + ui32DspOffset);
        pIoGenBuffDesc_Cached->sCircBuffer.ui32WriteAddr = BDSP_RAAGA_REGSET_PHY_ADDR_FOR_DSP(BCHP_RAAGA_DSP_FW_CFG_FIFO_0_BASE_ADDR +
                                                            (ui32RegOffset * i32FifoId) + BDSP_RAAGA_P_FIFO_WRITE_OFFSET + ui32DspOffset);
        pIoGenBuffDesc_Cached->sCircBuffer.ui32WrapAddr = BDSP_RAAGA_REGSET_PHY_ADDR_FOR_DSP(BCHP_RAAGA_DSP_FW_CFG_FIFO_0_BASE_ADDR +
                                                            (ui32RegOffset * i32FifoId) + BDSP_RAAGA_P_FIFO_END_OFFSET + ui32DspOffset);
    }
    else
    {

        pIoGenBuffDesc_Cached->sCircBuffer.ui32BaseAddr = physAddr;
        pIoGenBuffDesc_Cached->sCircBuffer.ui32EndAddr = physAddr + BDSP_AF_P_INTERTASK_IOGENBUFFER_SIZE - 4;
        pIoGenBuffDesc_Cached->sCircBuffer.ui32ReadAddr = physAddr;
        pIoGenBuffDesc_Cached->sCircBuffer.ui32WriteAddr = physAddr;
        pIoGenBuffDesc_Cached->sCircBuffer.ui32WrapAddr = physAddr + BDSP_AF_P_INTERTASK_IOGENBUFFER_SIZE - 4;
    }
    BDSP_MEM_P_FlushCache(pContext->pDevice->memHandle, (void *)pIoGenBuffDesc_Cached, sizeof(*pIoGenBuffDesc_Cached));


    /* Initialize the inter task buffer apis */
    pInterTaskBuffer->interTaskBuffer.destroy = BDSP_Raaga_P_InterTaskBuffer_Destroy;
    pInterTaskBuffer->interTaskBuffer.flush = BDSP_Raaga_P_InterTaskBuffer_Flush;

    *pInterTaskBufferHandle = &pInterTaskBuffer->interTaskBuffer;
    BDBG_OBJECT_SET(pInterTaskBuffer, BDSP_P_InterTaskBuffer);

    goto intertask_buffer_create_success;

err_rdb_alloc_io:
err_rdb_alloc_iogen:
    if(BDSP_BufferType_eRDB == bufferType)
    {
        while(i != 0)
        {
            BDSP_Raaga_P_MsgQueueParams *pMsgQueueParam;
            i--;
            pMsgQueueParam = (BDSP_Raaga_P_MsgQueueParams *)(((BDSP_Raaga_P_MsgQueueParams *)pInterTaskBuffer->pMsgQueueParams)+i);
            BDSP_Raaga_P_ReleaseFIFO(pContext->pDevice, BDSP_RAAGA_DSP_INDEX_INTERTASK,&(pMsgQueueParam->i32FifoId),1);
        }
        BDSP_MEM_P_FreeMemory(pContext->pDevice->memHandle, pInterTaskBuffer->pMsgQueueParams);
    }
err_msg_params_alloc:
    BDSP_MEM_P_FreeMemory(pContext->pDevice->memHandle, pInterTaskBuffer->pIoBufferDesc);

err_desc_alloc:
    BDSP_MEM_P_FreeMemory(pContext->pDevice->memHandle, pIoGenAddress);
err_io_gen_buff_malloc:
    BDSP_MEM_P_FreeMemory(pContext->pDevice->memHandle, pIoAddress);
err_io_buff_malloc:
    BKNI_Free(pInterTaskBuffer);
err_buffer_type:
err_malloc_inter_task_buffer:
intertask_buffer_create_success:
    BDBG_LEAVE(BDSP_Raaga_P_InterTaskBuffer_Create);
    return errCode;
}

/***********************************************************************
Name        :   BDSP_Raaga_P_InterTaskBuffer_Destroy

Type        :   PI Interface

Input       :   pInterTaskBufferHandle  -   Handle of the Intertask buffer to be destroyed by the PI.

Return      :   None

Functionality   :   Following are the operations performed.
        1)  Validate if the Intertask buffer is not connected to any stage at its input or ouput before destroying.
        2)  Retrieve the I/O buffer address from I/O descriptor and free the memory.
        3)  Retrieve the I/O Generic buffer address from I/O Generic descriptor and free the memory.
        4)  Free the memory of the I/O and I/O Generic descriptors.
        5)  Free the memory allocated to Intertask buffer descriptor structure.
***********************************************************************/

void BDSP_Raaga_P_InterTaskBuffer_Destroy(
    void *pInterTaskBufferHandle
    )
{
    BDSP_P_InterTaskBuffer *pRaagaInterTaskBuffer;
    void *pAddress = NULL;
    BDSP_AF_P_sIO_BUFFER *pIoBufferDesc = NULL;
    BDSP_AF_P_sIO_GENERIC_BUFFER *pIoBufferGenericDesc = NULL;
    signed  i;
    BDSP_RaagaContext *pRaagaContext;
    BDSP_Raaga *pDevice;

    BDBG_ENTER(BDSP_Raaga_P_InterTaskBuffer_Destroy);

    pRaagaInterTaskBuffer = (BDSP_P_InterTaskBuffer *)pInterTaskBufferHandle;
    BDBG_OBJECT_ASSERT(pRaagaInterTaskBuffer, BDSP_P_InterTaskBuffer);

    if (pRaagaInterTaskBuffer->dstHandle || pRaagaInterTaskBuffer->srcHandle)
    {
        BDBG_ERR(("Cannot destroy inter task buffer when in use. Please disconnect any input/output stages"));
        BDBG_ERR(("Handles connected to intertask buf - dst 0x%p src 0x%p",(void *)pRaagaInterTaskBuffer->dstHandle,(void *)pRaagaInterTaskBuffer->srcHandle));
        BERR_TRACE(BERR_NOT_AVAILABLE);
        return;
    }

    pRaagaContext = (BDSP_RaagaContext *)pRaagaInterTaskBuffer->pContext;
    BDBG_OBJECT_ASSERT(pRaagaContext, BDSP_RaagaContext);
    pDevice = (BDSP_Raaga *)pRaagaContext->pDevice;
    BDBG_OBJECT_ASSERT(pDevice, BDSP_Raaga);
    pIoBufferDesc = (BDSP_AF_P_sIO_BUFFER *)pRaagaInterTaskBuffer->pIoBufferDesc;
    pIoBufferGenericDesc = (BDSP_AF_P_sIO_GENERIC_BUFFER *)pRaagaInterTaskBuffer->pIoBufferGenericDesc;

    if( BDSP_AF_P_BufferType_eRDB == pIoBufferDesc->eBufferType)
    {
        BDSP_Raaga_P_MsgQueueParams *pMsgQueueParam;
        pMsgQueueParam= (BDSP_Raaga_P_MsgQueueParams *)pRaagaInterTaskBuffer->pMsgQueueParams;
        BDSP_MEM_P_FreeMemory(pDevice->memHandle, pMsgQueueParam->pBaseAddr);

        for(i=0;i<(signed)pIoBufferDesc->ui32NumBuffers;i++)
        {
            BDSP_Raaga_P_ReleaseFIFO(pDevice,BDSP_RAAGA_DSP_INDEX_INTERTASK,&((pMsgQueueParam+i)->i32FifoId),1);
        }

        pMsgQueueParam= (BDSP_Raaga_P_MsgQueueParams *)(((BDSP_Raaga_P_MsgQueueParams *)pRaagaInterTaskBuffer->pMsgQueueParams)+i);
        BDSP_MEM_P_FreeMemory(pDevice->memHandle, pMsgQueueParam->pBaseAddr);

        BDSP_Raaga_P_ReleaseFIFO(pDevice,BDSP_RAAGA_DSP_INDEX_INTERTASK,&(pMsgQueueParam->i32FifoId),1);/* SR: DSPindex is assumed to be zero*/
        BDSP_MEM_P_FreeMemory (pDevice->memHandle, pRaagaInterTaskBuffer->pMsgQueueParams);
    }
    else
    {
        /* Free the inter task io buffer */
        BDSP_MEM_P_ConvertOffsetToCacheAddr(pDevice->memHandle, pIoBufferDesc->sCircBuffer[0].ui32BaseAddr, &pAddress);
        BDSP_MEM_P_FreeMemory (pDevice->memHandle, pAddress);

        /* Free the inter task io generic buffer */
        pAddress = NULL;
        BDSP_MEM_P_ConvertOffsetToCacheAddr(pDevice->memHandle, pIoBufferGenericDesc->sCircBuffer.ui32BaseAddr, &pAddress);
        BDSP_MEM_P_FreeMemory (pDevice->memHandle, pAddress);
    }

    BDSP_MEM_P_FlushCache(pDevice->memHandle, (void *)pIoBufferDesc, sizeof(*pIoBufferDesc));
    BDSP_MEM_P_FlushCache(pDevice->memHandle, (void *)pIoBufferGenericDesc, sizeof(*pIoBufferGenericDesc));

    /* Free the descriptor memory */
    BDSP_MEM_P_FreeMemory (pDevice->memHandle, pRaagaInterTaskBuffer->pIoBufferDesc);

    BDBG_OBJECT_DESTROY(pRaagaInterTaskBuffer, BDSP_P_InterTaskBuffer);

    /* Free the inter task buffer handle */
    BKNI_Free(pRaagaInterTaskBuffer);

    BDBG_LEAVE(BDSP_Raaga_P_InterTaskBuffer_Destroy);
}

/***********************************************************************
Name        :   BDSP_Raaga_P_InterTaskBuffer_Flush

Type        :   PI Interface

Input       :   pInterTaskBufferHandle  -   Handle of the Intertask buffer to be flushed.

Return      :   None

Functionality   :   To flush any buffer, we need to reset the Read, Write and Wrap pointers.
        1)  For every I/O buffer (number of channels), Reset Read and Write to Start Address and Wrap to End Address.
        2)  For the only I/O Generic buffer, Reset Read and Write to Start Address and Wrap to End Address.
***********************************************************************/

void BDSP_Raaga_P_InterTaskBuffer_Flush(
    void *pInterTaskBufferHandle
    )
{
    BDSP_P_InterTaskBuffer *pRaagaInterTaskBuffer;
    unsigned i;
    BDSP_Raaga *pDevice;
    BDSP_RaagaContext *pRaagaContext;
    BDSP_AF_P_sIO_BUFFER *pIoBuffDesc = NULL;
    BDSP_AF_P_sIO_GENERIC_BUFFER *pIoGenBuffDesc = NULL;
    raaga_dramaddr ui32BaseAddr;

    BDBG_ENTER(BDSP_Raaga_P_InterTaskBuffer_Flush);

    pRaagaInterTaskBuffer = (BDSP_P_InterTaskBuffer *)pInterTaskBufferHandle;
    BDBG_OBJECT_ASSERT(pRaagaInterTaskBuffer, BDSP_P_InterTaskBuffer);
    pRaagaContext = (BDSP_RaagaContext *)pRaagaInterTaskBuffer->pContext;
    BDBG_OBJECT_ASSERT(pRaagaContext, BDSP_RaagaContext);
    pDevice = (BDSP_Raaga *)pRaagaContext->pDevice;
    BDBG_OBJECT_ASSERT(pDevice, BDSP_Raaga);

    if (pRaagaInterTaskBuffer->inUse)
    {
        BDBG_ERR(("Cannot flush inter task buffer when in use"));
        return;
    }

    pIoGenBuffDesc = (BDSP_AF_P_sIO_GENERIC_BUFFER *)pRaagaInterTaskBuffer->pIoBufferGenericDesc;
    pIoBuffDesc = (BDSP_AF_P_sIO_BUFFER *)pRaagaInterTaskBuffer->pIoBufferDesc;


    /* Reset the read and write pointers to base and wrap pointer to end to flush the inter task buffer */
    if( BDSP_AF_P_BufferType_eRDB == pIoBuffDesc->eBufferType)
    {
        BDSP_Raaga_P_MsgQueueParams *pMsgQueueParam;
        for (i = 0; i < pRaagaInterTaskBuffer->numChans; i++)
        {
            pMsgQueueParam = (BDSP_Raaga_P_MsgQueueParams *)(((BDSP_Raaga_P_MsgQueueParams *)pRaagaInterTaskBuffer->pMsgQueueParams)+i);
            BDSP_MEM_P_ConvertAddressToOffset(pDevice->memHandle, (void *)(pMsgQueueParam->pBaseAddr), &ui32BaseAddr);

            BDSP_Write32(
                pDevice->regHandle,
                BDSP_RAAGA_REGSET_OFFSET_ADDR_FOR_HOST(pIoBuffDesc->sCircBuffer[i].ui32ReadAddr),
                ui32BaseAddr); /* read */

            BDSP_Write32(
                pDevice->regHandle,
                BDSP_RAAGA_REGSET_OFFSET_ADDR_FOR_HOST(pIoBuffDesc->sCircBuffer[i].ui32WriteAddr),
                ui32BaseAddr); /* write */
        }

        pMsgQueueParam = (BDSP_Raaga_P_MsgQueueParams *)(((BDSP_Raaga_P_MsgQueueParams *)pRaagaInterTaskBuffer->pMsgQueueParams)+i);
        BDSP_MEM_P_ConvertAddressToOffset(pDevice->memHandle, (void *)(pMsgQueueParam->pBaseAddr), &ui32BaseAddr);

        BDSP_Write32(
            pDevice->regHandle,
            BDSP_RAAGA_REGSET_OFFSET_ADDR_FOR_HOST(pIoGenBuffDesc->sCircBuffer.ui32ReadAddr),
            ui32BaseAddr); /* read */

        BDSP_Write32(
            pDevice->regHandle,
            BDSP_RAAGA_REGSET_OFFSET_ADDR_FOR_HOST(pIoGenBuffDesc->sCircBuffer.ui32WriteAddr),
            ui32BaseAddr); /* write */
    }
    else
    {
        for (i = 0; i < pRaagaInterTaskBuffer->numChans; i++)
        {
            pIoBuffDesc->sCircBuffer[i].ui32ReadAddr  = pIoBuffDesc->sCircBuffer[i].ui32BaseAddr;
            pIoBuffDesc->sCircBuffer[i].ui32WriteAddr = pIoBuffDesc->sCircBuffer[i].ui32BaseAddr;
            pIoBuffDesc->sCircBuffer[i].ui32WrapAddr  = pIoBuffDesc->sCircBuffer[i].ui32EndAddr;
        }
        pIoGenBuffDesc->sCircBuffer.ui32ReadAddr  = pIoGenBuffDesc->sCircBuffer.ui32BaseAddr;
        pIoGenBuffDesc->sCircBuffer.ui32WriteAddr = pIoGenBuffDesc->sCircBuffer.ui32BaseAddr;
        pIoGenBuffDesc->sCircBuffer.ui32WrapAddr  = pIoGenBuffDesc->sCircBuffer.ui32EndAddr;
    }

    BDSP_MEM_P_FlushCache(pDevice->memHandle, (void *)pIoBuffDesc, sizeof(*pIoBuffDesc));
    BDSP_MEM_P_FlushCache(pDevice->memHandle, (void *)pIoGenBuffDesc, sizeof(*pIoGenBuffDesc));

    BDBG_LEAVE(BDSP_Raaga_P_InterTaskBuffer_Flush);
}

/***********************************************************************
Name        :   BDSP_Raaga_P_GetDefaultCreateQueueSettings

Type        :   PI Interface

Input       :   pContextHandle  -   Handle of the Context for which the Queue needs to created.
                pSettings           -   Settings for creating the Queue.

Return      :   Error Code to return SUCCESS or FAILURE

Functionality   :   Clear the memory provided by the PI as part of this function.
***********************************************************************/

BERR_Code BDSP_Raaga_P_GetDefaultCreateQueueSettings(
                                    void                     *pContextHandle,
                                    BDSP_QueueCreateSettings *pSettings)
{
    BERR_Code errCode = BERR_SUCCESS;

    BDSP_RaagaContext *pRaagaContext = (BDSP_RaagaContext *)pContextHandle;
    BDBG_ENTER(BDSP_Raaga_P_GetDefaultCreateQueueSettings);

    BDBG_OBJECT_ASSERT(pRaagaContext, BDSP_RaagaContext);

    BKNI_Memset(pSettings, 0, sizeof(BDSP_QueueCreateSettings));

    BDBG_LEAVE(BDSP_Raaga_P_GetDefaultCreateQueueSettings);
    return errCode;
}

/***********************************************************************
Name        :   BDSP_Raaga_P_CreateMsgQueueHandle

Type        :   BDSP Internal

Input       :   psMsgQueueParams    -   Pointer to the data releated to buffer provided by calling function.
                hHeap               -   Heap Handle
                hRegister               -   Register Handle.
                ui32DspOffset           -   Offset the DSP on which Queue handle needs to be created.
                hMsgQueue                   -     Queue Handle returned back to the caller.
                bWdgRecovery              -     Flag indicating whether we are in watchdog recovery or not

Return      :   Error Code to return SUCCESS or FAILURE

Functionality   :   Following are the operations performed.
        1)  Allocate and Initialise the memory for the Queue Handle if not in watchdog recovery else reuse the pointer.
        2)  Convert the virtual address of the buffer to physical and store the same in the FIFO base address index.
        3)  Update the Read, Write and End address appropriately using the data provided by the caller.
        4)    Store all the neccessary information releated to the buffer and Queue in the Queue handle for future Use.
     Note: In the Queue handle all the addresses are of the physical FIFOs used, so that APP can easily use it.
***********************************************************************/

BERR_Code BDSP_Raaga_P_CreateMsgQueueHandle(
                                BDSP_Raaga_P_MsgQueueParams    *psMsgQueueParams,   /* [in]*/
                                BMEM_Handle                     hHeap,              /* [in] */
                                BREG_Handle                     hRegister,          /* [in] */
                                uint32_t                        ui32DspOffset,      /* [in] */
                                BDSP_Raaga_P_MsgQueueHandle    *hMsgQueue,          /* [out]*/
                                bool                            bWdgRecovery        /* [in] */
                                )
{

    BERR_Code err=BERR_SUCCESS;

    raaga_dramaddr  ui32BaseAddr=0;
    raaga_dramaddr  ui32EndAddr=0;
    BDSP_Raaga_P_MsgQueueHandle  hHandle = NULL;
    uint32_t    ui32RegOffset = 0;

    BDBG_ENTER(BDSP_Raaga_P_CreateMsgQueueHandle);

    BDBG_ASSERT(psMsgQueueParams);
    BDBG_ASSERT(hHeap);
    BDBG_ASSERT(hRegister);
    BDBG_ASSERT(hMsgQueue);
    BDBG_ASSERT((unsigned)psMsgQueueParams->i32FifoId != BDSP_RAAGA_FIFO_INVALID);

    BDBG_MSG(("psMsgQueueParams->i32FifoId > %d",
                psMsgQueueParams->i32FifoId));

    if(false == bWdgRecovery)
    {

        /* Allocate memory for the Message Queue */
        hHandle =(BDSP_Raaga_P_MsgQueueHandle)
                  BKNI_Malloc(sizeof(struct BDSP_Raaga_P_MsgQueue));

        if(hHandle == NULL)
        {
            err = BERR_TRACE(BERR_OUT_OF_SYSTEM_MEMORY);
            goto exit;
        }
        BKNI_Memset (hHandle, 0, sizeof(struct BDSP_Raaga_P_MsgQueue));
    }
    else
    {
        hHandle = *hMsgQueue;
    }

    /* Conversion of address from virtual to physical*/
    BDSP_MEM_P_ConvertAddressToOffset(
            hHeap,psMsgQueueParams->pBaseAddr,&ui32BaseAddr);

    BKNI_Memset( psMsgQueueParams->pBaseAddr, 0,psMsgQueueParams->uiMsgQueueSize);
    BDSP_MEM_P_FlushCache(hHeap, psMsgQueueParams->pBaseAddr, psMsgQueueParams->uiMsgQueueSize);

    /*Initializing attributes of message queue in DRAM (device memory)*/

    ui32RegOffset = BCHP_RAAGA_DSP_FW_CFG_FIFO_1_BASE_ADDR - \
                    BCHP_RAAGA_DSP_FW_CFG_FIFO_0_BASE_ADDR;
    BDSP_Write32(
        hRegister,
        BCHP_RAAGA_DSP_FW_CFG_FIFO_0_BASE_ADDR +
            (ui32RegOffset * psMsgQueueParams->i32FifoId) +
            BDSP_RAAGA_P_FIFO_BASE_OFFSET + ui32DspOffset,
        ui32BaseAddr); /* base */

    ui32EndAddr = ui32BaseAddr + (psMsgQueueParams->uiMsgQueueSize);

    BDSP_Write32(
        hRegister,
        BCHP_RAAGA_DSP_FW_CFG_FIFO_0_BASE_ADDR +
            (ui32RegOffset * psMsgQueueParams->i32FifoId) +
            BDSP_RAAGA_P_FIFO_END_OFFSET + ui32DspOffset,
        ui32EndAddr); /* end */

    BDSP_Write32(
        hRegister,
        BCHP_RAAGA_DSP_FW_CFG_FIFO_0_BASE_ADDR +
            (ui32RegOffset * psMsgQueueParams->i32FifoId) +
            BDSP_RAAGA_P_FIFO_READ_OFFSET + ui32DspOffset,
        ui32BaseAddr); /* read */

    BDSP_Write32(
        hRegister,
        BCHP_RAAGA_DSP_FW_CFG_FIFO_0_BASE_ADDR +
            (ui32RegOffset * psMsgQueueParams->i32FifoId) +
            BDSP_RAAGA_P_FIFO_WRITE_OFFSET + ui32DspOffset,
        ui32BaseAddr); /* write */

    /* Initializes attributes in the local copy(handle) in system memory*/

    hHandle->hHeap          = hHeap;
    hHandle->hRegister      = hRegister;
    hHandle->ui32BaseAddr     = (BCHP_RAAGA_DSP_FW_CFG_FIFO_0_BASE_ADDR +
                                (ui32RegOffset * psMsgQueueParams->i32FifoId) +
                                 BDSP_RAAGA_P_FIFO_BASE_OFFSET + ui32DspOffset);
    hHandle->ui32EndAddr      = (BCHP_RAAGA_DSP_FW_CFG_FIFO_0_BASE_ADDR +
                                (ui32RegOffset * psMsgQueueParams->i32FifoId) +
                                 BDSP_RAAGA_P_FIFO_END_OFFSET + ui32DspOffset);
    hHandle->ui32ReadAddr      = (BCHP_RAAGA_DSP_FW_CFG_FIFO_0_BASE_ADDR +
                                (ui32RegOffset * psMsgQueueParams->i32FifoId) +
                                 BDSP_RAAGA_P_FIFO_READ_OFFSET + ui32DspOffset);
    hHandle->ui32WriteAddr     = (BCHP_RAAGA_DSP_FW_CFG_FIFO_0_BASE_ADDR +
                                (ui32RegOffset * psMsgQueueParams->i32FifoId) +
                                 BDSP_RAAGA_P_FIFO_WRITE_OFFSET + ui32DspOffset);
    hHandle->i32FifoId     = psMsgQueueParams->i32FifoId;
    hHandle->ui32DspOffset = ui32DspOffset;
    hHandle->pBaseAddr     = psMsgQueueParams->pBaseAddr;
    hHandle->ui32Size      = psMsgQueueParams->uiMsgQueueSize;

    if(false == bWdgRecovery)
    {
        *hMsgQueue = hHandle;
    }

exit:

   BDBG_LEAVE(BDSP_Raaga_P_CreateMsgQueueHandle);
   return err;

}

/***********************************************************************
Name        :   BDSP_Raaga_P_Queue_Create

Type        :   PI Interface

Input       :   pContextHandle  -   Handle of the Context for which the Queue needs to created.
                dspIndex            -   Index of the DSP.
                pSettings           -   Settings for creating the Queue.
                pQueueHandle        -   Queue Handle returned back to the PI.

Return      :   Error Code to return SUCCESS or FAILURE

Functionality   :   Following are the operations performed.
        1)  Allocate and Initialise the memory for the Queue Descriptor.
        2)  Depending on whether the Data is CDB or ITB for which the Queue is to be created, assign the FIFO-ID.
        3)  Create the Queue using the internal BDSP function with given settings.
        4)  Intialise all the function pointers  for Flush and Destroy, which will be used by the PI.
***********************************************************************/

BERR_Code BDSP_Raaga_P_Queue_Create( void *pContextHandle,
                                           unsigned dspIndex,
                                           BDSP_QueueCreateSettings *pSettings,
                                           BDSP_QueueHandle *pQueueHandle)
{
    BERR_Code errCode = BERR_SUCCESS;
    BDSP_RaagaQueue *pQueue;
    BDSP_AF_P_DistinctOpType distinctOp;
    BDSP_RaagaContext  *pContext;
    unsigned channels, i;
    BDSP_Raaga_P_MsgQueueParams sMsgQueueParam;

    BDBG_ENTER(BDSP_Raaga_P_Queue_Create);

    pContext = (BDSP_RaagaContext *)pContextHandle;
    pQueue   = BKNI_Malloc(sizeof(BDSP_RaagaQueue));
    if ( NULL == pQueue )
    {
        errCode = BERR_TRACE(BERR_OUT_OF_SYSTEM_MEMORY);
        goto err_malloc_queue;
    }

    BKNI_Memset(pQueue, 0, sizeof(*pQueue));

    BDSP_P_InitQueue(&pQueue->Queue, pQueue);

    pQueue->inUse = false;
    pQueue->dataType = pSettings->dataType;
    pQueue->input = pSettings->input;
    pQueue->srcHandle = NULL;
    pQueue->dstHandle = NULL;
    pQueue->srcIndex = -1;
    pQueue->dstIndex = -1;
    pQueue->pRaagaContext = pContext;
    pQueue->numBuf   = pSettings->numBuffers;
    pQueue->dspIndex = dspIndex;

    BDSP_Raaga_P_GetDistinctOpTypeAndNumChans(pSettings->dataType, &channels, &distinctOp);
    pQueue->numChans = channels;
    pQueue->distinctOp = distinctOp;

    for(i = 0; i< pSettings->numBuffers; i++)
    {
        /* Get FIFO for each buffer from the DSP depending on the Number of buffers required */

        errCode = BDSP_Raaga_P_AssignFreeFIFO(pContext->pDevice,dspIndex,&(sMsgQueueParam.i32FifoId),1);
        if(errCode)
        {
            BDBG_ERR(("Unable to find a free FIFO for CDB/ITB/ANCILLARY DATA QUEUE!!!!"));
            goto err_assign_queue_fifo;
        }

        sMsgQueueParam.uiMsgQueueSize = pSettings->bufferInfo[i].bufferSize;
        BDSP_MEM_P_ConvertOffsetToCacheAddr(
                            pContext->pDevice->memHandle,
                            pSettings->bufferInfo[i].bufferAddress,
                            (void **)&sMsgQueueParam.pBaseAddr);


        /* Calculate the Buffer addresses provided and write it into the registers */
        /* Convert the FIFO into address (4) and store it in Queue Handle */
        errCode = BDSP_Raaga_P_CreateMsgQueueHandle(&sMsgQueueParam,
                        pContext->pDevice->memHandle,
                        pContext->pDevice->regHandle,
                        pContext->pDevice->dspOffset[dspIndex],
                        &(pQueue->FIFOdata[i]),
                        false);
        if (BERR_SUCCESS != errCode)
        {
            BDBG_ERR(("BDSP_Raaga_P_Queue_Create: Queue Creation failed!"));
            errCode = BERR_TRACE(errCode);
            goto err_queue_creation;
        }

    }

    /* Initialize the Queue apis */
    pQueue->Queue.destroy = BDSP_Raaga_P_Queue_Destroy;
    pQueue->Queue.flush   = BDSP_Raaga_P_Queue_Flush;
    pQueue->Queue.getIoBuffer = BDSP_Raaga_P_Queue_GetIoBuffer;
    pQueue->Queue.getBuffer = BDSP_Raaga_P_Queue_GetBuffer;
    pQueue->Queue.consumeData = BDSP_Raaga_P_Queue_ConsumeData;
    pQueue->Queue.commitData = BDSP_Raaga_P_Queue_CommitData;
    pQueue->Queue.getOpBufferAddr = BDSP_Raaga_P_Queue_GetBufferAddr;

    *pQueueHandle = &pQueue->Queue;
    BDBG_OBJECT_SET(pQueue, BDSP_RaagaQueue);

    goto queue_create_success;

err_queue_creation:
    BKNI_AcquireMutex(pContext->pDevice->fifoIdMutex[dspIndex]);
    pContext->pDevice->dspFifo[dspIndex][sMsgQueueParam.i32FifoId - BDSP_RAAGA_FIFO_0_INDEX] = false;
    BKNI_ReleaseMutex(pContext->pDevice->fifoIdMutex[dspIndex]);
err_assign_queue_fifo:

    BKNI_AcquireMutex(pContext->pDevice->fifoIdMutex[dspIndex]);
    while(i != 0)
    {
        i--;
        pContext->pDevice->dspFifo[dspIndex][(pQueue->FIFOdata[i]->i32FifoId - BDSP_RAAGA_FIFO_0_INDEX)] = false;
        /*Delete the Allocated FIFOdata for each buffer */
        if(pQueue->FIFOdata[i])
        {
            BKNI_Free(pQueue->FIFOdata[i]);
        }
    }
    BKNI_ReleaseMutex(pContext->pDevice->fifoIdMutex[dspIndex]);
err_malloc_queue:
queue_create_success:

    BDBG_LEAVE(BDSP_Raaga_P_Queue_Create);
    return errCode;
}

/***********************************************************************
Name        :   BDSP_Raaga_P_Queue_Destroy

Type        :   PI Interface

Input       :   pQueueHandle        -   Queue Handle returned back to the PI.

Return      :   NONE

Functionality   :   Following are the operations performed.
        1)  Chech whether the Queue you intended to destroy is in Use.
        2)  Depending on the number of buffers, release all the FIFOs.
        3)  Destroy the Queue Handle and Free the memory used to store the data structure.
***********************************************************************/
void BDSP_Raaga_P_Queue_Destroy( void *pQueueHandle)
{
    BDSP_RaagaQueue *pQueue;
    unsigned i;

    pQueue = (BDSP_RaagaQueue *)pQueueHandle;
    BDBG_OBJECT_ASSERT(pQueue, BDSP_RaagaQueue);

    BDBG_ENTER(BDSP_Raaga_P_Queue_Destroy);

    if (pQueue->inUse)
    {
        BDBG_ERR(("Cannot destroy Queue when in use. Please disconnect any input/output stages"));
        BDBG_ASSERT(0);
    }

    /* Free the Queue Handle Allocated */
    for(i = 0; i< pQueue->numBuf ; i++)
    {
        if(pQueue->FIFOdata[i])
        {
            BDSP_Raaga_P_ReleaseFIFO(pQueue->pRaagaContext->pDevice, pQueue->dspIndex, &(pQueue->FIFOdata[i]->i32FifoId), 1);
            BKNI_Free(pQueue->FIFOdata[i]);
        }
    }
    BDBG_OBJECT_DESTROY(pQueue, BDSP_RaagaQueue);

    /* Free the Queue buffer handle */
    BKNI_Free(pQueue);

    BDBG_LEAVE(BDSP_Raaga_P_Queue_Destroy);
}

/***********************************************************************
Name        :   BDSP_Raaga_P_Queue_Flush

Type        :   PI Interface

Input       :   pQueueHandle        -   Queue Handle returned back to the PI.

Return      :   NONE

Functionality   :   Following are the operations performed.
        1)  For all the buffers restore the Base, Read, Write pointers to the Base address of the buffer.
        2)    Derive the End address using the size stored in the Queue handle and update the End pointer.
***********************************************************************/

void BDSP_Raaga_P_Queue_Flush( void *pQueueHandle )
{
    BDSP_RaagaQueue *pRaagaQueue;
    unsigned i;
    uint32_t regVal=0;

    BDBG_ENTER(BDSP_Raaga_P_Queue_Flush);

    pRaagaQueue = (BDSP_RaagaQueue *)pQueueHandle;
    BDBG_OBJECT_ASSERT(pRaagaQueue, BDSP_RaagaQueue);

    if (pRaagaQueue->inUse)
    {
        BDBG_ERR(("Cannot flush Queue when in use"));
        return;
    }

    /* Reset the Read, Write and Base pointers to Start and End pointer to End to ensure flush of the Queue based Buffer */
    for (i = 0; i < pRaagaQueue->numBuf; i++)
    {
        BDSP_MEM_P_ConvertAddressToOffset(pRaagaQueue->FIFOdata[i]->hHeap,
            pRaagaQueue->FIFOdata[i]->pBaseAddr,
            &regVal);

        BDSP_Write32( pRaagaQueue->FIFOdata[i]->hRegister, pRaagaQueue->FIFOdata[i]->ui32BaseAddr, regVal); /* Base  */
        BDSP_Write32( pRaagaQueue->FIFOdata[i]->hRegister, pRaagaQueue->FIFOdata[i]->ui32WriteAddr, regVal); /* Write  */
        BDSP_Write32( pRaagaQueue->FIFOdata[i]->hRegister, pRaagaQueue->FIFOdata[i]->ui32ReadAddr,  regVal); /* Read  */
        regVal = regVal + pRaagaQueue->FIFOdata[i]->ui32Size;
        BDSP_Write32( pRaagaQueue->FIFOdata[i]->hRegister, pRaagaQueue->FIFOdata[i]->ui32EndAddr,  regVal); /* End  */
    }

    BDBG_LEAVE(BDSP_Raaga_P_Queue_Flush);
}

/***********************************************************************
Name        :   BDSP_Raaga_P_Queue_GetBufferAddr

Type        :   PI Interface

Input       :   pQueueHandle        -   Handle of the Queue for whose addresses needs to be returned back to PI.
                numbuffers      -   Number of buffers in the Queue.
                pBuffer             -   Pointer provided by PI which needs to filled back and returned.

Return      :   Error Code to return SUCCESS or FAILURE

Functionality   :   Following are the operations performed.
        1)  Return the Base Address, End Address, Wrap Address, Read Pointer and Write Pointer back to the
            PI depending on the numbers of buffers in the Queue by writing into the pointer provided by the PI.
***********************************************************************/

BERR_Code BDSP_Raaga_P_Queue_GetBufferAddr(void *pQueueHandle, unsigned numbuffers, void *pBuffer /*[out] */)
{
    BERR_Code errCode = BERR_SUCCESS;
    BDSP_RaagaQueue *pQueue;
    BDSP_AF_P_sDRAM_CIRCULAR_BUFFER *psCircBuffer;
    unsigned i;

    BDBG_ENTER(BDSP_Raaga_P_Queue_GetBufferAddr);

    pQueue = (BDSP_RaagaQueue *)pQueueHandle;
    BDBG_OBJECT_ASSERT(pQueue, BDSP_RaagaQueue);

    BDBG_ASSERT(pBuffer);
    BDBG_ASSERT(numbuffers == pQueue->numBuf);
    psCircBuffer = (BDSP_AF_P_sDRAM_CIRCULAR_BUFFER *)pBuffer;

    for(i= 0; i<numbuffers; i++)
    {
        psCircBuffer->ui32BaseAddr  = pQueue->FIFOdata[i]->ui32BaseAddr;
        psCircBuffer->ui32EndAddr   = pQueue->FIFOdata[i]->ui32EndAddr;
        psCircBuffer->ui32ReadAddr  = pQueue->FIFOdata[i]->ui32ReadAddr;
        psCircBuffer->ui32WriteAddr = pQueue->FIFOdata[i]->ui32WriteAddr;
        psCircBuffer->ui32WrapAddr  = pQueue->FIFOdata[i]->ui32EndAddr;
        psCircBuffer++;
    }

    BDBG_LEAVE(BDSP_Raaga_P_Queue_GetBufferAddr);
    return errCode;
}

/***********************************************************************
Name        :   BDSP_Raaga_P_AddRaveInput

Type        :   PI Interface

Input       :   pStageHandle        -   Handle of the Stage for which input must be fed from RAVE Buffer.
                pContextMap     -   Context map of the XPT.
                pInputIndex     -   Index of the input for this Stage returned back to PI.

Return      :   Error Code to return SUCCESS or FAILURE

Functionality   :   Following are the operations performed.
        1)  Retreive the free input index for the stage which can be used for this RAVE buffer.
        2)  Treat the CDB and ITB buffers as two buffers for same input Index.
        3)  Populate the Source details for the Stage with appropriate values using the XPT descriptor, each for CDB and ITB buffer.
        4)  Populate the Address of the I/O buffers, each for CDB and ITB buffer.
        5)  Increment the number of inputs for this stage (both CDB and ITB are treated as 1 input) and
            also the number of RAVE buffers (as 1 for both CDB and ITB) in the eco-system.
        6)  Fill the Input index pointer for the PI for later use (only 1 as both CDB and ITB are treated as same input).
***********************************************************************/

BERR_Code BDSP_Raaga_P_AddRaveInput(
    void *pStageHandle,
    const BAVC_XptContextMap *pContextMap,
    unsigned *pInputIndex
    )
{
    BDSP_RaagaStage *pRaagaStage = (BDSP_RaagaStage *)pStageHandle;

    BDSP_RaagaContext   *pRaagaContext = (BDSP_RaagaContext   *)pRaagaStage->pContext; /*src or dest*/
    BDSP_Raaga *pDevice = (BDSP_Raaga *)pRaagaContext->pDevice;

    BERR_Code errCode=BERR_SUCCESS;

    unsigned numBuffers=2, ipIndex;

    BDBG_ENTER(BDSP_Raaga_P_AddRaveInput);

    BDSP_Raaga_P_GetFreeInputPortIndex(pRaagaStage, &ipIndex);
    BDBG_ASSERT(ipIndex < BDSP_AF_P_MAX_IP_FORKS);

    pRaagaStage->sStageInput[ipIndex].eNodeValid=BDSP_AF_P_eValid;
    pRaagaStage->sStageInput[ipIndex].IoBuffer.ui32NumBuffers=numBuffers;/*CDB and ITB*/
    pRaagaStage->sStageInput[ipIndex].IoBuffer.eBufferType=BDSP_AF_P_BufferType_eRAVE;

    pRaagaStage->sStageInput[ipIndex].eConnectionType=BDSP_ConnectionType_eRaveBuffer;
    pRaagaStage->sStageInput[ipIndex].connectionHandle = (BDSP_StageHandle)NULL;
    pRaagaStage->sStageInput[ipIndex].connectionDetails.rave.pContextMap=(BAVC_XptContextMap *)pContextMap;

    pRaagaStage->sStageInput[ipIndex].IoBuffer.eBufferType=BDSP_AF_P_BufferType_eRAVE;
    pRaagaStage->sStageInput[ipIndex].IoBuffer.ui32NumBuffers=numBuffers;


    /*not required to explicitly mention this, I guess pkr*/
    pRaagaStage->sStageInput[ipIndex].Metadata.IoGenericBuffer.ui32NumBuffers=0;


    pRaagaStage->sStageInput[ipIndex].IoBuffer.sCircBuffer[0].ui32BaseAddr= BCHP_PHYSICAL_OFFSET + pContextMap->CDB_Base;
    pRaagaStage->sStageInput[ipIndex].IoBuffer.sCircBuffer[0].ui32EndAddr= BCHP_PHYSICAL_OFFSET + pContextMap->CDB_End;
    pRaagaStage->sStageInput[ipIndex].IoBuffer.sCircBuffer[0].ui32ReadAddr= BCHP_PHYSICAL_OFFSET + pContextMap->CDB_Read;
    pRaagaStage->sStageInput[ipIndex].IoBuffer.sCircBuffer[0].ui32WrapAddr= BCHP_PHYSICAL_OFFSET + pContextMap->CDB_Wrap;
    pRaagaStage->sStageInput[ipIndex].IoBuffer.sCircBuffer[0].ui32WriteAddr= BCHP_PHYSICAL_OFFSET + pContextMap->CDB_Valid;

    pRaagaStage->sStageInput[ipIndex].IoBuffer.sCircBuffer[1].ui32BaseAddr= BCHP_PHYSICAL_OFFSET + pContextMap->ITB_Base;
    pRaagaStage->sStageInput[ipIndex].IoBuffer.sCircBuffer[1].ui32EndAddr= BCHP_PHYSICAL_OFFSET + pContextMap->ITB_End;
    pRaagaStage->sStageInput[ipIndex].IoBuffer.sCircBuffer[1].ui32ReadAddr= BCHP_PHYSICAL_OFFSET + pContextMap->ITB_Read;
    pRaagaStage->sStageInput[ipIndex].IoBuffer.sCircBuffer[1].ui32WrapAddr= BCHP_PHYSICAL_OFFSET + pContextMap->ITB_Wrap;
    pRaagaStage->sStageInput[ipIndex].IoBuffer.sCircBuffer[1].ui32WriteAddr= BCHP_PHYSICAL_OFFSET + pContextMap->ITB_Valid;

    BDSP_MEM_P_ConvertAddressToOffset(pDevice->memHandle,
        pRaagaStage->sStageInput[ipIndex].pIoBuffDesc,
        &pRaagaStage->sStageInput[ipIndex].ui32StageIOBuffCfgAddr);

    BDSP_MEM_P_ConvertAddressToOffset(pDevice->memHandle,
        pRaagaStage->sStageInput[ipIndex].pIoGenBuffDesc,
        &pRaagaStage->sStageInput[ipIndex].ui32StageIOGenericDataBuffCfgAddr);

    /*I think ContextIdx is not required to be populated*/

    pRaagaStage->numInputs[BDSP_ConnectionType_eRaveBuffer]+=1;

    *pInputIndex = ipIndex;/*Total inputs from RAVE, always 1, as of now*/
    pRaagaStage->totalInputs+=1;

    BDBG_LEAVE(BDSP_Raaga_P_AddRaveInput);
    return(errCode);
}

/***********************************************************************
Name        :   BDSP_Raaga_P_AddFmmOutput

Type        :   PI Interface

Input       :   pStageHandle        -   Handle of the Stage for which output must be fed to FMM Buffer.
                dataType            -   Type of data that will fed into FMM buffer.
                pDescriptor     -   Descriptor for the FMM buffer.
                pOutputIndex        -   Index of the Ouput from this Stage returned back to PI.

Return      :   Error Code to return SUCCESS or FAILURE

Functionality   :   Following are the operations performed.
        1)  Retreive the the free output index for the stage which can be used for this FMM buffer.
        2)  Depending on the datatype, figure out the number of channels and output type.
        3)  Populate the Dstination details for the Stage with appropriate values using the FMM descriptor provided by the PI.
        4)  Populate the Address of the I/O buffers and rate control data.
        5)  Increment the number of ouputs from this stage and also the number of FMM buffers in the eco-system.
        6)  Fill the Ouput index pointer for the PI for later use.
***********************************************************************/

BERR_Code BDSP_Raaga_P_AddFmmOutput(
    void *pStageHandle,
    BDSP_DataType dataType,
    const BDSP_FmmBufferDescriptor *pDescriptor,
    unsigned *pOutputIndex
    )
{
    BDSP_RaagaStage *pRaagaStage = (BDSP_RaagaStage *)pStageHandle;

    BERR_Code errCode=BERR_SUCCESS;

    BDSP_RaagaContext   *pRaagaContext = (BDSP_RaagaContext   *)pRaagaStage->pContext; /*src or dest*/
    BDSP_Raaga *pDevice = (BDSP_Raaga *)pRaagaContext->pDevice;

    unsigned channels=0, i, opIndex;

    BDBG_ENTER(BDSP_Raaga_P_AddFmmOutput);

    BDSP_Raaga_P_GetFreeOutputPortIndex(pRaagaStage, &opIndex);
    BDBG_ASSERT(opIndex < BDSP_AF_P_MAX_OP_FORKS);

    BDSP_Raaga_P_GetDistinctOpTypeAndNumChans(dataType, &channels, &pRaagaStage->eStageOpBuffDataType[opIndex]);
    if(channels!=pDescriptor->numBuffers)
    {
        errCode=BERR_TRACE(BERR_INVALID_PARAMETER);
        BDBG_ERR(("BDSP_Raaga_P_AddFmmOutput::FMM Output not added!"));
        goto err_valid_channels;
    }

    /*lots of checks need to be put in place- Ramanathan*/

    pRaagaStage->sStageOutput[opIndex].eNodeValid=BDSP_AF_P_eValid;
    pRaagaStage->sStageOutput[opIndex].IoBuffer.ui32NumBuffers=pDescriptor->numBuffers;
    pRaagaStage->sStageOutput[opIndex].IoBuffer.eBufferType=BDSP_AF_P_BufferType_eFMM;

    pRaagaStage->sStageOutput[opIndex].eConnectionType=BDSP_ConnectionType_eFmmBuffer;
    pRaagaStage->sStageOutput[opIndex].connectionHandle = (BDSP_StageHandle)NULL;
    pRaagaStage->sStageOutput[opIndex].connectionDetails.fmm.descriptor = *pDescriptor;

    pRaagaStage->sStageOutput[opIndex].IoBuffer.eBufferType=BDSP_AF_P_BufferType_eFMM;
    pRaagaStage->sStageOutput[opIndex].IoBuffer.ui32NumBuffers=channels;

    /*not required to explicitly mention this, I guess pkr*/
    pRaagaStage->sStageOutput[opIndex].Metadata.IoGenericBuffer.ui32NumBuffers=0;

    for(i=0;i<pDescriptor->numBuffers;i++)/*audio channels*/
    {
        pRaagaStage->sStageOutput[opIndex].IoBuffer.sCircBuffer[i].ui32BaseAddr = BDSP_RAAGA_REGSET_ADDR_FOR_DSP( pDescriptor->buffers[i].base );
        pRaagaStage->sStageOutput[opIndex].IoBuffer.sCircBuffer[i].ui32EndAddr = BDSP_RAAGA_REGSET_ADDR_FOR_DSP( pDescriptor->buffers[i].end );
        pRaagaStage->sStageOutput[opIndex].IoBuffer.sCircBuffer[i].ui32ReadAddr = BDSP_RAAGA_REGSET_ADDR_FOR_DSP( pDescriptor->buffers[i].read );
        pRaagaStage->sStageOutput[opIndex].IoBuffer.sCircBuffer[i].ui32WrapAddr = BDSP_RAAGA_REGSET_ADDR_FOR_DSP( pDescriptor->buffers[i].end );
        pRaagaStage->sStageOutput[opIndex].IoBuffer.sCircBuffer[i].ui32WriteAddr = BDSP_RAAGA_REGSET_ADDR_FOR_DSP( pDescriptor->buffers[i].write );
    }

    for(i=0;i<BDSP_AF_P_MAX_CHANNEL_PAIR;i++)/*rate controller Initialize per pair of channels*/
    {
        pRaagaStage->sStageOutput[opIndex].Metadata.rateController[i].wrcnt=-1;/*Initialise*/
    }

    for(i=0;i<((pDescriptor->numBuffers+1)>>1);i++)/*rate controller per pair of channels*/
    {
        pRaagaStage->sStageOutput[opIndex].Metadata.rateController[i].wrcnt=pDescriptor->rateControllers[i].wrcnt;
    }

    BDSP_MEM_P_ConvertAddressToOffset(pDevice->memHandle,
        pRaagaStage->sStageOutput[opIndex].pIoBuffDesc,
        &pRaagaStage->sStageOutput[opIndex].ui32StageIOBuffCfgAddr);

    BDSP_MEM_P_ConvertAddressToOffset(pDevice->memHandle,
        pRaagaStage->sStageOutput[opIndex].pIoGenBuffDesc,
        &pRaagaStage->sStageOutput[opIndex].ui32StageIOGenericDataBuffCfgAddr);

    pRaagaStage->numOutputs[BDSP_ConnectionType_eFmmBuffer]+=1;

    *pOutputIndex = opIndex;/*Total outputs going out from this stage, both IS and FMM*/
    pRaagaStage->totalOutputs+=1;

err_valid_channels:

    BDBG_LEAVE(BDSP_Raaga_P_AddFmmOutput);
    return(errCode);
}

/***********************************************************************
Name        :   BDSP_Raaga_P_AddRaveOutput

Type        :   PI Interface

Input       :   pStageHandle        -   Handle of the Stage for which output must be fed to RAVE Buffer.
                pContextMap     -   Context map of the XPT.
                pOutputIndex        -   Index of the Ouput from this Stage returned back to PI.

Return      :   Error Code to return SUCCESS or FAILURE

Functionality   :   Following are the operations performed.
        1)  Retreive the the free output index for the stage which can be used for this RAVE buffer.
        2)  Populate the Destination details for the Stage with appropriate values using the XPT descriptor, each for CDB and ITB buffer.
        3)  Populate the Address of the I/O buffers, each for CDB and ITB buffer.
        4)  Increment the number of ouputs from this stage (each for CDB and ITB)  and also the number of RAVE buffers (each for CDB and ITB) in the eco-system.
        5)  Fill the Ouput index pointer for the PI for later use (each for CDB and ITB).
***********************************************************************/

BERR_Code BDSP_Raaga_P_AddRaveOutput(
    void *pStageHandle,
    const BAVC_XptContextMap *pContextMap,
    unsigned *pOutputIndex /* [out] */
    )
{
    BDSP_RaagaStage *pRaagaStage = (BDSP_RaagaStage *)pStageHandle;
    BERR_Code errCode = BERR_SUCCESS;
    BDSP_RaagaContext   *pRaagaContext; /*src or dest*/
    BDSP_Raaga *pDevice;
    unsigned opIndex;

    BDBG_ENTER(BDSP_Raaga_P_AddRaveOutput);

    BDBG_ASSERT(NULL != pRaagaStage);
    BDBG_ASSERT(NULL != pContextMap);
    BDBG_ASSERT(NULL != pOutputIndex);

    pRaagaContext = (BDSP_RaagaContext   *)pRaagaStage->pContext; /*src or dest*/
    pDevice = (BDSP_Raaga *)pRaagaContext->pDevice;

    BDSP_Raaga_P_GetFreeOutputPortIndex(pRaagaStage, &opIndex);
    BDBG_ASSERT(opIndex < BDSP_AF_P_MAX_OP_FORKS);

    /* CDB output */
    pRaagaStage->sStageOutput[opIndex].eNodeValid = BDSP_AF_P_eValid;
    pRaagaStage->sStageOutput[opIndex].IoBuffer.ui32NumBuffers = 1;
    pRaagaStage->sStageOutput[opIndex].IoBuffer.eBufferType = BDSP_AF_P_BufferType_eRAVE;

    pRaagaStage->sStageOutput[opIndex].eConnectionType = BDSP_ConnectionType_eRaveBuffer;
    pRaagaStage->sStageOutput[opIndex].connectionHandle = (BDSP_StageHandle)NULL;
    pRaagaStage->sStageOutput[opIndex].connectionDetails.rave.pContextMap=(BAVC_XptContextMap *)pContextMap;
    pRaagaStage->sStageOutput[opIndex].Metadata.IoGenericBuffer.ui32NumBuffers=0;

    pRaagaStage->sStageOutput[opIndex].IoBuffer.sCircBuffer[0].ui32BaseAddr = BCHP_PHYSICAL_OFFSET + pContextMap->CDB_Base;
    pRaagaStage->sStageOutput[opIndex].IoBuffer.sCircBuffer[0].ui32EndAddr = BCHP_PHYSICAL_OFFSET + pContextMap->CDB_End;
    pRaagaStage->sStageOutput[opIndex].IoBuffer.sCircBuffer[0].ui32ReadAddr = BCHP_PHYSICAL_OFFSET + pContextMap->CDB_Read;
    pRaagaStage->sStageOutput[opIndex].IoBuffer.sCircBuffer[0].ui32WrapAddr = BCHP_PHYSICAL_OFFSET + pContextMap->CDB_Wrap;
    pRaagaStage->sStageOutput[opIndex].IoBuffer.sCircBuffer[0].ui32WriteAddr = BCHP_PHYSICAL_OFFSET + pContextMap->CDB_Valid;

    pRaagaStage->eStageOpBuffDataType[opIndex] = BDSP_AF_P_DistinctOpType_eCdb;

    /* This needs to be done only for non-interstage connections, since the interstage buffer descriptors
        are allocated with the interstage buffers */
    BDSP_MEM_P_ConvertAddressToOffset(pDevice->memHandle,
        pRaagaStage->sStageOutput[opIndex].pIoBuffDesc,
        &pRaagaStage->sStageOutput[opIndex].ui32StageIOBuffCfgAddr);

    BDSP_MEM_P_ConvertAddressToOffset(pDevice->memHandle,
        pRaagaStage->sStageOutput[opIndex].pIoGenBuffDesc,
        &pRaagaStage->sStageOutput[opIndex].ui32StageIOGenericDataBuffCfgAddr);

    pRaagaStage->numOutputs[BDSP_ConnectionType_eRaveBuffer]+=1;
    pRaagaStage->totalOutputs+=1;

    /* ITB is a different output */
    BDSP_Raaga_P_GetFreeOutputPortIndex(pRaagaStage, &opIndex);
    BDBG_ASSERT(opIndex < BDSP_AF_P_MAX_OP_FORKS);

    /* ITB output */
    pRaagaStage->sStageOutput[opIndex].eNodeValid = BDSP_AF_P_eValid;
    pRaagaStage->sStageOutput[opIndex].IoBuffer.ui32NumBuffers = 1;
    pRaagaStage->sStageOutput[opIndex].IoBuffer.eBufferType = BDSP_AF_P_BufferType_eRAVE;

    pRaagaStage->sStageOutput[opIndex].eConnectionType = BDSP_ConnectionType_eRaveBuffer;
    pRaagaStage->sStageOutput[opIndex].connectionHandle = (BDSP_StageHandle)NULL;
    pRaagaStage->sStageOutput[opIndex].connectionDetails.rave.pContextMap=(BAVC_XptContextMap *)pContextMap;
    pRaagaStage->sStageOutput[opIndex].Metadata.IoGenericBuffer.ui32NumBuffers=0;

    pRaagaStage->sStageOutput[opIndex].IoBuffer.sCircBuffer[0].ui32BaseAddr = BCHP_PHYSICAL_OFFSET + pContextMap->ITB_Base;
    pRaagaStage->sStageOutput[opIndex].IoBuffer.sCircBuffer[0].ui32EndAddr = BCHP_PHYSICAL_OFFSET + pContextMap->ITB_End;
    pRaagaStage->sStageOutput[opIndex].IoBuffer.sCircBuffer[0].ui32ReadAddr = BCHP_PHYSICAL_OFFSET + pContextMap->ITB_Read;
    pRaagaStage->sStageOutput[opIndex].IoBuffer.sCircBuffer[0].ui32WrapAddr = BCHP_PHYSICAL_OFFSET + pContextMap->ITB_Wrap;
    pRaagaStage->sStageOutput[opIndex].IoBuffer.sCircBuffer[0].ui32WriteAddr = BCHP_PHYSICAL_OFFSET + pContextMap->ITB_Valid;

    pRaagaStage->eStageOpBuffDataType[opIndex] = BDSP_AF_P_DistinctOpType_eItb;

    /* This needs to be done only for non-interstage connections, since the interstage buffer descriptors
        are allocated with the interstage buffers */
    BDSP_MEM_P_ConvertAddressToOffset(pDevice->memHandle,
        pRaagaStage->sStageOutput[opIndex].pIoBuffDesc,
        &pRaagaStage->sStageOutput[opIndex].ui32StageIOBuffCfgAddr);

    BDSP_MEM_P_ConvertAddressToOffset(pDevice->memHandle,
        pRaagaStage->sStageOutput[opIndex].pIoGenBuffDesc,
        &pRaagaStage->sStageOutput[opIndex].ui32StageIOGenericDataBuffCfgAddr);

    /* The index returned is always the ITB output index, so at remove output,
    the stage output for index-1 is also invalidated */
    *pOutputIndex = opIndex;/*Total outputs going out from this stage, both IS and FMM*/

    pRaagaStage->numOutputs[BDSP_ConnectionType_eRaveBuffer]+=1;
    pRaagaStage->totalOutputs+=1;

    BDBG_LEAVE(BDSP_Raaga_P_AddRaveOutput);
    return(errCode);
}

/***********************************************************************
Name        :   BDSP_Raaga_P_AddQueueInput

Type        :   PI Interface

Input       :   pStageHandle        -   Handle of the Stage whose input will be from a Queue/RDB Buffer.
                pQueueHandle        -   Handle of the Queue provided by the PI.
                pInputIndex         -   Index of the input for this stage provided back to PI.

Return      :   Error Code to return SUCCESS or FAILURE

Functionality   :   Following are the operations performed.
        1)  Retreive the the free input index for the stage which can be used for this Queue.
        2)  Populate the Source details for the Stage with appropriate values using the Queue descriptor provided by the PI.
            The type of input will be treated as RDB type each for CDB and ITB. Separate buffers are allocated for CDB and ITB
            and not treated as individual/seperate inputs.
        3)  Populate the Address of the I/O buffer using the FIFO address filled during Create Queue. There is no I/O Generic buffer.
        4)  Increment the number of inputs from RDB buffer for this stage and total inputs to the stage.
        5)  Fill the input index pointer for the PI for later use.
***********************************************************************/

BERR_Code BDSP_Raaga_P_AddQueueInput(
                                    void     *pStageHandle,
                                    void     *pQueueHandle,
                                    unsigned *pInputIndex /* [out] */
                                    )
{
    BDSP_RaagaStage *pRaagaStage = (BDSP_RaagaStage *)pStageHandle;
    BDSP_RaagaQueue *pRaagaQueue = (BDSP_RaagaQueue *)pQueueHandle;
    BERR_Code errCode = BERR_SUCCESS;
    BDSP_RaagaContext   *pRaagaContext; /*src or dest*/
    BDSP_Raaga *pDevice;
    unsigned ipIndex, i;

    BDBG_ASSERT(NULL != pRaagaStage);
    BDBG_ASSERT(NULL != pQueueHandle);
    BDBG_ASSERT(NULL != pInputIndex);

    BDBG_ENTER(BDSP_Raaga_P_AddQueueInput);

    pRaagaContext = (BDSP_RaagaContext *)pRaagaStage->pContext; /*src or dest*/
    pDevice = (BDSP_Raaga *)pRaagaContext->pDevice;

    BDSP_Raaga_P_GetFreeInputPortIndex(pRaagaStage, &ipIndex);
    BDBG_ASSERT(ipIndex < BDSP_AF_P_MAX_IP_FORKS);

    /* Note CDB and ITB are separate Index/Queue Handle - Needs to be taken care */
    pRaagaStage->sStageInput[ipIndex].eNodeValid = BDSP_AF_P_eValid;
    pRaagaStage->sStageInput[ipIndex].IoBuffer.ui32NumBuffers = pRaagaQueue->numBuf;
    pRaagaStage->sStageInput[ipIndex].IoBuffer.eBufferType = BDSP_AF_P_BufferType_eRDB;

    pRaagaStage->sStageInput[ipIndex].eConnectionType = BDSP_ConnectionType_eRDBBuffer;
    pRaagaStage->sStageInput[ipIndex].connectionHandle = (BDSP_StageHandle)NULL;
    pRaagaStage->sStageInput[ipIndex].connectionDetails.rdb.pQHandle = (void *)pRaagaQueue; /* Need to verify the warning */

    /*not required to explicitly mention this, I guess pkr*/
    pRaagaStage->sStageInput[ipIndex].Metadata.IoGenericBuffer.ui32NumBuffers=0;

    for(i= 0; i< pRaagaQueue->numBuf; i++)
    {
        pRaagaStage->sStageInput[ipIndex].IoBuffer.sCircBuffer[i].ui32BaseAddr  = BDSP_RAAGA_REGSET_ADDR_FOR_DSP( pRaagaQueue->FIFOdata[i]->ui32BaseAddr );
        pRaagaStage->sStageInput[ipIndex].IoBuffer.sCircBuffer[i].ui32EndAddr   = BDSP_RAAGA_REGSET_ADDR_FOR_DSP( pRaagaQueue->FIFOdata[i]->ui32EndAddr );
        pRaagaStage->sStageInput[ipIndex].IoBuffer.sCircBuffer[i].ui32ReadAddr  = BDSP_RAAGA_REGSET_ADDR_FOR_DSP( pRaagaQueue->FIFOdata[i]->ui32ReadAddr );
        pRaagaStage->sStageInput[ipIndex].IoBuffer.sCircBuffer[i].ui32WrapAddr  = BDSP_RAAGA_REGSET_ADDR_FOR_DSP( pRaagaQueue->FIFOdata[i]->ui32EndAddr );
        pRaagaStage->sStageInput[ipIndex].IoBuffer.sCircBuffer[i].ui32WriteAddr = BDSP_RAAGA_REGSET_ADDR_FOR_DSP( pRaagaQueue->FIFOdata[i]->ui32WriteAddr );
    }

    pRaagaStage->eStageOpBuffDataType[ipIndex] = pRaagaQueue->distinctOp;

    BDSP_MEM_P_ConvertAddressToOffset(pDevice->memHandle,
        pRaagaStage->sStageInput[ipIndex].pIoBuffDesc,
        &pRaagaStage->sStageInput[ipIndex].ui32StageIOBuffCfgAddr);

    BDSP_MEM_P_ConvertAddressToOffset(pDevice->memHandle,
        pRaagaStage->sStageInput[ipIndex].pIoGenBuffDesc,
        &pRaagaStage->sStageInput[ipIndex].ui32StageIOGenericDataBuffCfgAddr);

    /*I think ContextIdx is not required to be populated*/
    pRaagaStage->numInputs[BDSP_ConnectionType_eRDBBuffer]+=1;

    *pInputIndex = ipIndex;/*Total inputs from RDB, always 1, as of now*/
    pRaagaStage->totalInputs+=1;

    BDBG_LEAVE(BDSP_Raaga_P_AddQueueInput);
    return(errCode);
}

/***********************************************************************
Name        :   BDSP_Raaga_P_AddQueueOutput

Type        :   PI Interface

Input       :   pStageHandle        -   Handle of the Stage whose output will be to a Queue/RDB Buffer.
                pQueueHandle        -   Handle of the Queue provided by the PI.
                pOutputIndex        -   Index of the output from this stage provided back to PI.

Return      :   Error Code to return SUCCESS or FAILURE

Functionality   :   Following are the operations performed.
        1)  Retreive the the free output index for the stage which can be used for this Queue.
        2)  Populate the Destination details for the Stage with appropriate values using the Queue descriptor provided by the PI.
            The type of output will be treated as RDB type each for CDB and ITB. Separate buffers are allocated for CDB and ITB
            and not treated as individual/seperate outputs.
        3)  Populate the Address of the I/O buffer using the FIFO address filled during Create Queue. There is no I/O Generic buffer.
        4)  Increment the number of outputs to RDB buffer for this stage and total outputs for the stage.
        5)  Fill the output index pointer for the PI for later use.
***********************************************************************/

BERR_Code BDSP_Raaga_P_AddQueueOutput(
                                    void     *pStageHandle,
                                    void     *pQueueHandle,
                                    unsigned *pOutputIndex /* [out] */
                                    )
{
    BDSP_RaagaStage *pRaagaStage = (BDSP_RaagaStage *)pStageHandle;
    BDSP_RaagaQueue *pRaagaQueue = (BDSP_RaagaQueue *)pQueueHandle;
    BERR_Code errCode = BERR_SUCCESS;
    BDSP_RaagaContext   *pRaagaContext; /*src or dest*/
    BDSP_Raaga *pDevice;
    unsigned opIndex, i;

    BDBG_ENTER(BDSP_Raaga_P_AddQueueOutput);

    BDBG_ASSERT(NULL != pRaagaStage);
    BDBG_ASSERT(NULL != pQueueHandle);
    BDBG_ASSERT(NULL != pOutputIndex);

    pRaagaContext = (BDSP_RaagaContext *)pRaagaStage->pContext; /*src or dest*/
    pDevice = (BDSP_Raaga *)pRaagaContext->pDevice;

    BDSP_Raaga_P_GetFreeOutputPortIndex(pRaagaStage, &opIndex);
    BDBG_ASSERT(opIndex < BDSP_AF_P_MAX_OP_FORKS);

    /* Note CDB and ITB are separate Index/Queue Handle - Needs to be taken care */
    /* Output */
    pRaagaStage->sStageOutput[opIndex].eNodeValid = BDSP_AF_P_eValid;
    pRaagaStage->sStageOutput[opIndex].IoBuffer.ui32NumBuffers = pRaagaQueue->numBuf;
    pRaagaStage->sStageOutput[opIndex].IoBuffer.eBufferType = BDSP_AF_P_BufferType_eRDB;
    if(pRaagaQueue->dataType == BDSP_DataType_eRDBPool)
        {
            pRaagaStage->sStageOutput[opIndex].IoBuffer.eBufferType = BDSP_AF_P_BufferType_eRDBPool;
        }

    pRaagaStage->sStageOutput[opIndex].eConnectionType = BDSP_ConnectionType_eRDBBuffer;
    pRaagaStage->sStageOutput[opIndex].connectionHandle = (BDSP_StageHandle)NULL;
    pRaagaStage->sStageOutput[opIndex].connectionDetails.rdb.pQHandle = (void *)pRaagaQueue; /* Need to verify the warning */

    /*not required to explicitly mention this, I guess pkr*/
    pRaagaStage->sStageOutput[opIndex].Metadata.IoGenericBuffer.ui32NumBuffers=0;


    for(i = 0; i< pRaagaQueue->numBuf; i++)
    {
        pRaagaStage->sStageOutput[opIndex].IoBuffer.sCircBuffer[i].ui32BaseAddr  = BDSP_RAAGA_REGSET_ADDR_FOR_DSP(  pRaagaQueue->FIFOdata[i]->ui32BaseAddr );
        pRaagaStage->sStageOutput[opIndex].IoBuffer.sCircBuffer[i].ui32EndAddr   = BDSP_RAAGA_REGSET_ADDR_FOR_DSP(  pRaagaQueue->FIFOdata[i]->ui32EndAddr );
        pRaagaStage->sStageOutput[opIndex].IoBuffer.sCircBuffer[i].ui32ReadAddr  = BDSP_RAAGA_REGSET_ADDR_FOR_DSP(  pRaagaQueue->FIFOdata[i]->ui32ReadAddr );
        pRaagaStage->sStageOutput[opIndex].IoBuffer.sCircBuffer[i].ui32WrapAddr  = BDSP_RAAGA_REGSET_ADDR_FOR_DSP(  pRaagaQueue->FIFOdata[i]->ui32EndAddr );
        pRaagaStage->sStageOutput[opIndex].IoBuffer.sCircBuffer[i].ui32WriteAddr = BDSP_RAAGA_REGSET_ADDR_FOR_DSP(  pRaagaQueue->FIFOdata[i]->ui32WriteAddr );
    }

    pRaagaStage->eStageOpBuffDataType[opIndex] = pRaagaQueue->distinctOp;

    /* This needs to be done only for non-interstage connections, since the interstage buffer descriptors
        are allocated with the interstage buffers */
    BDSP_MEM_P_ConvertAddressToOffset(pDevice->memHandle,
        pRaagaStage->sStageOutput[opIndex].pIoBuffDesc,
        &pRaagaStage->sStageOutput[opIndex].ui32StageIOBuffCfgAddr);

    BDSP_MEM_P_ConvertAddressToOffset(pDevice->memHandle,
        pRaagaStage->sStageOutput[opIndex].pIoGenBuffDesc,
        &pRaagaStage->sStageOutput[opIndex].ui32StageIOGenericDataBuffCfgAddr);

    pRaagaStage->numOutputs[BDSP_ConnectionType_eRDBBuffer]+=1;
    pRaagaStage->totalOutputs+=1;

    /* The index returned is always the ITB output index, so at remove output,
            the stage output for index-1 is also invalidated */
    *pOutputIndex = opIndex;/*Total outputs going out from this stage, both IS and FMM*/

    BDBG_LEAVE(BDSP_Raaga_P_AddQueueOutput);
    return(errCode);
}

/***********************************************************************
Name        :   BDSP_Raaga_P_RemoveOutput

Type        :   PI Interface

Input       :   pStageHandle        -   Handle of the Stage for which output must be removed.
                outputIndex     -   The index of the Output in the Stage.

Return      :   None

Functionality   :   Following are the operations performed.
        1)  Make sure the Stage is not running, when attempt is made to remove the output.
        2)  Retrieve the Connection type used at the output.
        3)  If the connection type is Intertask task buffer, remove the source handle of the intertask buffer.
        4)  If destination handle of the intertask buffer is NULL, then inUse variable is set to false.
            Now the Intertask buffer can be destroyed by PI later.
        5)  Special handling is required if in watchdog recovery, Intertask buffer needs to be destroyed.
        6)  Disconnect the Output but resetting Stage Output structure.
        7)  If the Output is RAVE buffer then disconnection needs to be done for both CDB and ITB buffer.
***********************************************************************/

void BDSP_Raaga_P_RemoveOutput(
    void *pStageHandle,
    unsigned outputIndex)
{
    BDSP_RaagaStage *pRaagaStage = (BDSP_RaagaStage *)pStageHandle;
    BDSP_ConnectionType connectionType;

    BDBG_ENTER(BDSP_Raaga_P_RemoveOutput);

    BDBG_OBJECT_ASSERT(pRaagaStage, BDSP_RaagaStage);
    BDBG_ASSERT(outputIndex < BDSP_AF_P_MAX_OP_FORKS);

    connectionType = pRaagaStage->sStageOutput[outputIndex].eConnectionType;

    if ((pRaagaStage->running)
        && (connectionType != BDSP_ConnectionType_eInterTaskBuffer))
    {
        BDBG_ERR(("Cannot remove outputs when the stage is running"));
        return;
    }

    /* For inter task connections if the dest stage is running, then
    a cit reconfiguration command needs to be sent */
    if (connectionType == BDSP_ConnectionType_eInterTaskBuffer)
    {
        BDSP_P_InterTaskBuffer *pRaagaInterTaskBuffer;

        /* Get the inter task buffer handle */
        pRaagaInterTaskBuffer = (BDSP_P_InterTaskBuffer *)pRaagaStage->sStageOutput[outputIndex].connectionDetails.interTask.hInterTask->pInterTaskBufferHandle;

        pRaagaInterTaskBuffer->srcHandle = NULL;
        pRaagaInterTaskBuffer->srcIndex = -1;

        if (NULL == pRaagaInterTaskBuffer->dstHandle)
        {
            pRaagaInterTaskBuffer->inUse = false;
            pRaagaInterTaskBuffer->distinctOp = BDSP_AF_P_DistinctOpType_eMax;
        }
    }

    /* Reset the last stage output structure */
    pRaagaStage->sStageOutput[outputIndex].eNodeValid = false;
    pRaagaStage->sStageOutput[outputIndex].eConnectionType = BDSP_ConnectionType_eMax;
    pRaagaStage->sStageOutput[outputIndex].connectionHandle = NULL;

    BKNI_Memset(&pRaagaStage->sStageOutput[outputIndex].connectionDetails, 0,
                sizeof(pRaagaStage->sStageOutput[outputIndex].connectionDetails));

    pRaagaStage->eStageOpBuffDataType[outputIndex] = BDSP_AF_P_DistinctOpType_eMax;
    pRaagaStage->numOutputs[connectionType] -= 1;
    pRaagaStage->totalOutputs--;

    /* If connection is rave, then there will be 2 outputs, CDB and ITB. Remove the second one */
    if (connectionType == BDSP_ConnectionType_eRaveBuffer)
    {
        /* Reset the CDB output */
        pRaagaStage->sStageOutput[outputIndex-1].eNodeValid = false;
        pRaagaStage->sStageOutput[outputIndex-1].eConnectionType = BDSP_ConnectionType_eMax;
        pRaagaStage->sStageOutput[outputIndex-1].connectionHandle = NULL;

        BKNI_Memset(&pRaagaStage->sStageOutput[outputIndex-1].connectionDetails, 0,
                    sizeof(pRaagaStage->sStageOutput[outputIndex-1].connectionDetails));

        pRaagaStage->eStageOpBuffDataType[outputIndex-1] = BDSP_AF_P_DistinctOpType_eMax;
        pRaagaStage->numOutputs[connectionType] -= 1;
        pRaagaStage->totalOutputs--;
    }

    BDBG_LEAVE(BDSP_Raaga_P_RemoveOutput);
}

/***********************************************************************
Name        :   BDSP_Raaga_P_RemoveAllOutputs

Type        :   PI Interface

Input       :   pStageHandle        -   Handle of the Stage for which all outputs must be removed.

Return      :   None

Functionality   :   Following are the operations performed.
        1)  Recursively remove the all the outputs connected to the stage.
        2)  Special handling is done for RAVE buffer as both the outputs CDB and ITB buffers are removed in one instance.
***********************************************************************/

void BDSP_Raaga_P_RemoveAllOutputs(
    void *pStageHandle)
{
    BDSP_RaagaStage *pRaagaStage = (BDSP_RaagaStage *)pStageHandle;
    unsigned i, numOutputs;

    BDBG_ENTER(BDSP_Raaga_P_RemoveAllOutputs);

    BDBG_OBJECT_ASSERT(pRaagaStage, BDSP_RaagaStage);
    numOutputs = pRaagaStage->totalOutputs;

    for (i = 0; i < numOutputs; i++)
    {
        /* A rave output implies CDB and ITB output ports - Removing the ITB output will
        automatically remove the CDB output. So remove only the ITB output port */
        if (pRaagaStage->sStageOutput[i].eConnectionType == BDSP_ConnectionType_eRaveBuffer)
        {
            i++;
        }
        BDSP_Raaga_P_RemoveOutput(pStageHandle, i);
    }

    BDBG_ASSERT(0 == pRaagaStage->totalOutputs);

    for (i = 0; i < BDSP_ConnectionType_eMax; i++)
    {
        BDBG_ASSERT(pRaagaStage->numOutputs[i] == 0);
    }

    BDBG_LEAVE(BDSP_Raaga_P_RemoveAllOutputs);
}

/***********************************************************************
Name        :   BDSP_Raaga_P_AddFmmInput

Type        :   PI Interface

Input       :   pStageHandle        -   Handle of the Stage for which FMM buffer needs to be connected at input.
                dataType            -   Type of data present in the FMM buffer.
                pDescriptor     -   FMM buffer descriptor provided by the PI.
                pInputIndex     -   Index of the input which is associated for the FMM buffer.

Return      :   Error Code to return SUCCESS or FAILURE

Functionality   :   Following are the operations performed.
        1)  Retreive the the free input index for the stage which can be used for this FMM buffer.
        2)  Depending on the datatype, figure out the number of channels and input type.
        3)  Populate the Source details for the Stage with appropriate values using the FMM descriptor provided by the PI.
        4)  Populate the Address of the I/O buffers.
        5)  Increment the number of inputs for this stage and also the number of FMM buffers in the eco-system.
        6)  Fill the input index pointer for the PI for later use.
        7)  IF the stage is already running/ watchdog recovery then perform the CIT reconfigure.
***********************************************************************/

BERR_Code BDSP_Raaga_P_AddFmmInput(
    void *pStageHandle,
    BDSP_DataType dataType,
    const BDSP_FmmBufferDescriptor *pDescriptor,
    unsigned *pInputIndex)
{
    BDSP_RaagaStage *pRaagaStage = (BDSP_RaagaStage *)pStageHandle;
    BDSP_AF_P_DistinctOpType distinctOp;

    BDSP_RaagaContext   *pRaagaContext = (BDSP_RaagaContext   *)pRaagaStage->pContext; /*src or dest*/
    BDSP_Raaga *pDevice = (BDSP_Raaga *)pRaagaContext->pDevice;

    BERR_Code errCode=BERR_SUCCESS;
    unsigned i, ipIndex;
    unsigned numBuffers;
    BDSP_AF_P_sIO_BUFFER *pIoBuffDesc_Cached = NULL;
    BDSP_AF_P_sIO_GENERIC_BUFFER *pIoGenBuffDesc_Cached = NULL;

    BDBG_ENTER(BDSP_Raaga_P_AddFmmInput);

    BDSP_Raaga_P_GetFreeInputPortIndex(pRaagaStage, &ipIndex);
    BDBG_ASSERT(ipIndex < BDSP_AF_P_MAX_IP_FORKS);

    BDSP_Raaga_P_GetDistinctOpTypeAndNumChans(dataType, &numBuffers, &distinctOp);
    BDBG_ASSERT(numBuffers == pDescriptor->numBuffers);

    pRaagaStage->sStageInput[ipIndex].eNodeValid = BDSP_AF_P_eValid;
    pRaagaStage->sStageInput[ipIndex].IoBuffer.ui32NumBuffers = pDescriptor->numBuffers;
    pRaagaStage->sStageInput[ipIndex].IoBuffer.eBufferType = BDSP_AF_P_BufferType_eFMM;

    pRaagaStage->sStageInput[ipIndex].eConnectionType=BDSP_ConnectionType_eFmmBuffer;
    pRaagaStage->sStageInput[ipIndex].connectionHandle = (BDSP_StageHandle)NULL;
    pRaagaStage->sStageInput[ipIndex].connectionDetails.fmm.descriptor = *pDescriptor;

    /*not required to explicitly mention this, I guess pkr*/
    pRaagaStage->sStageInput[ipIndex].Metadata.IoGenericBuffer.ui32NumBuffers = 0;


    for (i = 0; i < pDescriptor->numBuffers; i++)
    {
        pRaagaStage->sStageInput[ipIndex].IoBuffer.sCircBuffer[i].ui32BaseAddr = BDSP_RAAGA_REGSET_ADDR_FOR_DSP( pDescriptor->buffers[i].base );
        pRaagaStage->sStageInput[ipIndex].IoBuffer.sCircBuffer[i].ui32EndAddr = BDSP_RAAGA_REGSET_ADDR_FOR_DSP( pDescriptor->buffers[i].end );
        pRaagaStage->sStageInput[ipIndex].IoBuffer.sCircBuffer[i].ui32ReadAddr = BDSP_RAAGA_REGSET_ADDR_FOR_DSP( pDescriptor->buffers[i].read );
        pRaagaStage->sStageInput[ipIndex].IoBuffer.sCircBuffer[i].ui32WrapAddr = BDSP_RAAGA_REGSET_ADDR_FOR_DSP( pDescriptor->buffers[i].end );
        pRaagaStage->sStageInput[ipIndex].IoBuffer.sCircBuffer[i].ui32WriteAddr = BDSP_RAAGA_REGSET_ADDR_FOR_DSP( pDescriptor->buffers[i].write );
    }


    pIoBuffDesc_Cached = pRaagaStage->sStageInput[ipIndex].pIoBuffDesc;
    pIoGenBuffDesc_Cached = pRaagaStage->sStageInput[ipIndex].pIoGenBuffDesc;
    for (i = 0; i < pDescriptor->numBuffers; i++)
    {
        pIoBuffDesc_Cached->sCircBuffer[i].ui32BaseAddr = BDSP_RAAGA_REGSET_ADDR_FOR_DSP( pDescriptor->buffers[i].base );
        pIoBuffDesc_Cached->sCircBuffer[i].ui32EndAddr = BDSP_RAAGA_REGSET_ADDR_FOR_DSP( pDescriptor->buffers[i].end );
        pIoBuffDesc_Cached->sCircBuffer[i].ui32ReadAddr = BDSP_RAAGA_REGSET_ADDR_FOR_DSP( pDescriptor->buffers[i].read );
        pIoBuffDesc_Cached->sCircBuffer[i].ui32WrapAddr = BDSP_RAAGA_REGSET_ADDR_FOR_DSP( pDescriptor->buffers[i].end );
        pIoBuffDesc_Cached->sCircBuffer[i].ui32WriteAddr = BDSP_RAAGA_REGSET_ADDR_FOR_DSP( pDescriptor->buffers[i].write );
    }

    pIoBuffDesc_Cached->ui32NumBuffers = pDescriptor->numBuffers;
    pIoBuffDesc_Cached->eBufferType = BDSP_AF_P_BufferType_eFMM;
    pIoGenBuffDesc_Cached->ui32NumBuffers = 0;
    pIoGenBuffDesc_Cached->eBufferType = BDSP_AF_P_BufferType_eFMM;
    BDSP_MEM_P_FlushCache(pDevice->memHandle, (void *)pIoBuffDesc_Cached, sizeof(*pIoBuffDesc_Cached));
    BDSP_MEM_P_FlushCache(pDevice->memHandle, (void *)pIoGenBuffDesc_Cached, sizeof(*pIoGenBuffDesc_Cached));

    BDSP_MEM_P_ConvertAddressToOffset(pDevice->memHandle,
        pRaagaStage->sStageInput[ipIndex].pIoBuffDesc,
        &pRaagaStage->sStageInput[ipIndex].ui32StageIOBuffCfgAddr);

    BDSP_MEM_P_ConvertAddressToOffset(pDevice->memHandle,
        pRaagaStage->sStageInput[ipIndex].pIoGenBuffDesc,
        &pRaagaStage->sStageInput[ipIndex].ui32StageIOGenericDataBuffCfgAddr);

    pRaagaStage->numInputs[BDSP_ConnectionType_eFmmBuffer] += 1;
    pRaagaStage->eStageOpBuffDataType[ipIndex] = distinctOp;

    *pInputIndex = ipIndex;
    pRaagaStage->totalInputs += 1;

    /* Send the cit re-configuration command to the DSP to indicate an added input port */
    /* if the dest stage is running and Watchdog recovery is not underway */
    if ((pRaagaStage->running)&&(!pRaagaStage->pContext->contextWatchdogFlag))
    {
        BDSP_RaagaTask *pRaagaTask = pRaagaStage->pRaagaTask;
        BDSP_AF_P_sNODE_CONFIG  *psNodeConfig;
        raaga_dramaddr  ui32NodeIpBuffCfgAddr, ui32NodeIpGenericDataBuffCfgAddr;
        BDSP_AF_P_sTASK_CONFIG  *psWorkingTaskCitBuffAddr_Cached = NULL;


        BDBG_OBJECT_ASSERT(pRaagaTask, BDSP_RaagaTask);

        psWorkingTaskCitBuffAddr_Cached  = (BDSP_AF_P_sTASK_CONFIG *)pRaagaTask->taskMemGrants.sSpareCitStruct.pBaseAddr;

        /* Assuming that the input FMM buffer will be added only to stage 0 */
        BDBG_ASSERT(pRaagaStage == (BDSP_RaagaStage *)pRaagaTask->startSettings.primaryStage->pStageHandle);

        BDSP_MEM_P_ConvertAddressToOffset(pRaagaStage->pContext->pDevice->memHandle,
            pRaagaStage->sStageInput[ipIndex].pIoBuffDesc,
            &ui32NodeIpBuffCfgAddr);

        BDSP_MEM_P_ConvertAddressToOffset(pRaagaStage->pContext->pDevice->memHandle,
            pRaagaStage->sStageInput[ipIndex].pIoGenBuffDesc,
            &ui32NodeIpGenericDataBuffCfgAddr);

        psNodeConfig = &psWorkingTaskCitBuffAddr_Cached->sNodeConfig[0];

        /* Making the Input port valid */
        psNodeConfig->eNodeIpValidFlag[ipIndex] = BDSP_AF_P_eValid;
        /* Setting the IO and IO Generic buffer structure addresses for the Node 0 */
        psNodeConfig->ui32NodeIpBuffCfgAddr[ipIndex] = ui32NodeIpBuffCfgAddr;
        psNodeConfig->ui32NodeIpGenericDataBuffCfgAddr[ipIndex] = ui32NodeIpGenericDataBuffCfgAddr;
        psNodeConfig->ui32NumSrc++;

        /* Setting the IO and IO Generic buffer structure addresses and enabling the Valid Flag for the Node 1 */
        psNodeConfig = &psWorkingTaskCitBuffAddr_Cached->sNodeConfig[BDSP_CIT_P_NUM_SPECIAL_NODES];
        psNodeConfig->ui32NodeIpBuffCfgAddr[ipIndex] = ui32NodeIpBuffCfgAddr;
        psNodeConfig->ui32NodeIpGenericDataBuffCfgAddr[ipIndex] = ui32NodeIpGenericDataBuffCfgAddr;
        psNodeConfig->eNodeIpValidFlag[ipIndex] = BDSP_AF_P_eValid;
        psNodeConfig->ui32NumSrc++;
        BDSP_MEM_P_FlushCache(pDevice->memHandle, (void *)psWorkingTaskCitBuffAddr_Cached, sizeof(*psWorkingTaskCitBuffAddr_Cached));

        /* Send the cit re-configuration command to DSP */
        errCode = BDSP_Raaga_P_SendCitReconfigCommand(pRaagaTask, psWorkingTaskCitBuffAddr_Cached);
        if (errCode)
        {
            goto end;
        }
    }

end:
    BDBG_LEAVE(BDSP_Raaga_P_AddFmmInput);
    return(errCode);
}

/***********************************************************************
Name        :   BDSP_Raaga_P_RemoveInput

Type        :   PI Interface

Input       :   pStageHandle        -   Handle of the Stage from which the input must be removed.
                inputIndex      -   The index of the input for the Stage.

Return      :   None

Functionality   :   Following are the operations performed.
        1)  Retrieve the Connection type used at the input.
        2)  Make sure the Stage is not running if the input is FMM or Intertask buffer, when attempt is made to remove the input.
        3)  If the Stage is running or in Wtachdog recovery, then CIT Reconfigure needs to be performed.
        4)  If the connection type is Intertask task buffer, remove the destination handle of the intertask buffer.
        5)  If source handle of the intertask buffer is NULL, then inUse variable is set to false.
            Now the Intertask buffer can be destroyed by PI later.
        6)  Special handling is required if in watchdog recovery, Intertask buffer needs to be destroyed.
        7)  Disconnect the Input but resetting Stage Input structure.
***********************************************************************/

void BDSP_Raaga_P_RemoveInput(
    void *pStageHandle,
    unsigned inputIndex)
{
    BERR_Code err;
    BDSP_RaagaStage *pRaagaStage = (BDSP_RaagaStage *)pStageHandle;
    BDSP_ConnectionType connectionType;
    BDSP_P_InterTaskBuffer *pRaagaInterTaskBuffer=NULL;
    BDSP_Raaga *pDevice = pRaagaStage->pContext->pDevice;
    BDSP_AF_P_sIO_BUFFER *pIoBuffDesc_Cached = NULL;

    BDBG_ENTER(BDSP_Raaga_P_RemoveInput);

    BDBG_OBJECT_ASSERT(pRaagaStage, BDSP_RaagaStage);
    BDBG_ASSERT(inputIndex < BDSP_AF_P_MAX_IP_FORKS);

    if ( pRaagaStage->totalInputs == 0 )
    {
        return;
    }

    connectionType = pRaagaStage->sStageInput[inputIndex].eConnectionType;

    if ((pRaagaStage->running)
        && ((connectionType != BDSP_ConnectionType_eInterTaskBuffer)
         && (connectionType != BDSP_ConnectionType_eFmmBuffer)))
    {
        BDBG_ERR(("Cannot remove inputs when the stage is running"));
        return;
    }

    /* Get the inter task buffer handle */

    /* Update the node config and send the cit reconfiguration command if the
            dest stage is running and Watchdog recovery is not underway */
    if ((pRaagaStage->running)&&(!pRaagaStage->pContext->contextWatchdogFlag))
    {
        BDSP_RaagaTask *pRaagaTask = pRaagaStage->pRaagaTask;
        BDSP_AF_P_sNODE_CONFIG  *psNodeConfig;
        BDSP_AF_P_sTASK_CONFIG  *psWorkingTaskCitBuffAddr_Cached = NULL;

        BDBG_OBJECT_ASSERT(pRaagaTask, BDSP_RaagaTask);

        psWorkingTaskCitBuffAddr_Cached = (BDSP_AF_P_sTASK_CONFIG *)pRaagaTask->taskMemGrants.sSpareCitStruct.pBaseAddr;

        /* For inter task connections, the output from the source stage
        also needs to be removed. */
        if (connectionType == BDSP_ConnectionType_eInterTaskBuffer)
        {
            pRaagaInterTaskBuffer = (BDSP_P_InterTaskBuffer *)pRaagaStage->sStageInput[inputIndex].connectionDetails.interTask.hInterTask->pInterTaskBufferHandle;
            pRaagaInterTaskBuffer->dstHandle = NULL;
            pRaagaInterTaskBuffer->dstIndex  = -1;
            pIoBuffDesc_Cached = (BDSP_AF_P_sIO_BUFFER *)pRaagaInterTaskBuffer->pIoBufferDesc;

            /* SIPS is only supported if the Inter task buffer type is DRAM */
            if (pIoBuffDesc_Cached->eBufferType != BDSP_AF_P_BufferType_eDRAM)
            {
                BDBG_ERR(("Cannot remove input port seamlessly for non-dram type (%d) buffers",
                    pIoBuffDesc_Cached->eBufferType));
            }

        }
        psNodeConfig = &psWorkingTaskCitBuffAddr_Cached->sNodeConfig[0];
        /* Making the Input port invalid */
        psNodeConfig->eNodeIpValidFlag[inputIndex] = BDSP_AF_P_eInvalid;
        /* Setting the IO and IO Generic buffer structure addresses for the Node 0 */
        psNodeConfig->ui32NodeIpBuffCfgAddr[inputIndex] = 0;
        psNodeConfig->ui32NodeIpGenericDataBuffCfgAddr[inputIndex] = 0;
        if( psNodeConfig->ui32NumSrc != 0 )
        psNodeConfig->ui32NumSrc--;

        /* Setting the IO and IO Generic buffer structure addresses and enabling the Valid Flag for the Node 1 */
        psNodeConfig = &psWorkingTaskCitBuffAddr_Cached->sNodeConfig[BDSP_CIT_P_NUM_SPECIAL_NODES];
        psNodeConfig->ui32NodeIpBuffCfgAddr[inputIndex] = 0;
        psNodeConfig->ui32NodeIpGenericDataBuffCfgAddr[inputIndex] = 0;
        psNodeConfig->eNodeIpValidFlag[inputIndex] = BDSP_AF_P_eInvalid;
        if( psNodeConfig->ui32NumSrc != 0 )
        psNodeConfig->ui32NumSrc--;
        BDSP_MEM_P_FlushCache(pDevice->memHandle, (void *)psWorkingTaskCitBuffAddr_Cached, sizeof(*psWorkingTaskCitBuffAddr_Cached));

        /* Send the cit re-configuration command to DSP */
        err = BDSP_Raaga_P_SendCitReconfigCommand(pRaagaTask, psWorkingTaskCitBuffAddr_Cached);

        if (err)
        {
            BDBG_ERR(("Failed to re-configure the cit after removing input"));
            return;
        }
    }

    if ((connectionType == BDSP_ConnectionType_eInterTaskBuffer))
    {
        pRaagaInterTaskBuffer = (BDSP_P_InterTaskBuffer *)pRaagaStage->sStageInput[inputIndex].connectionDetails.interTask.hInterTask->pInterTaskBufferHandle;
        pRaagaInterTaskBuffer->dstHandle = NULL;
        pRaagaInterTaskBuffer->dstIndex  = -1;
        if(NULL == pRaagaInterTaskBuffer->srcHandle)
        {
            /* Update inter task buffer structure */
            pRaagaInterTaskBuffer->inUse = false;
            pRaagaInterTaskBuffer->distinctOp = BDSP_AF_P_DistinctOpType_eMax;
        }
    }

    /* Reset the stage input structure */
    pRaagaStage->sStageInput[inputIndex].eNodeValid = false;
    pRaagaStage->sStageInput[inputIndex].eConnectionType = BDSP_ConnectionType_eMax;
    pRaagaStage->sStageInput[inputIndex].connectionHandle = NULL;

    BKNI_Memset(&pRaagaStage->sStageInput[inputIndex].connectionDetails, 0,
                sizeof(pRaagaStage->sStageInput[inputIndex].connectionDetails));

    pRaagaStage->numInputs[connectionType] -= 1;
    pRaagaStage->totalInputs--;

    BDBG_LEAVE(BDSP_Raaga_P_RemoveInput);
    return;
}

/***********************************************************************
Name        :   BDSP_Raaga_P_RemoveAllInputs

Type        :   PI Interface

Input       :   pStageHandle        -   Handle of the Stage for which all inputs must be removed.

Return      :   None

Functionality   :   Following are the operations performed.
        1)  Recursively remove the all the inputs connected to the stage.
***********************************************************************/

void BDSP_Raaga_P_RemoveAllInputs(
    void *pStageHandle)
{
    BDSP_RaagaStage *pRaagaStage = (BDSP_RaagaStage *)pStageHandle;
    unsigned i, numInputs;

    BDBG_ENTER(BDSP_Raaga_P_RemoveAllInputs);

    BDBG_OBJECT_ASSERT(pRaagaStage, BDSP_RaagaStage);
    numInputs = pRaagaStage->totalInputs;

    for (i = 0; i < numInputs; i++)
    {
        BDSP_Raaga_P_RemoveInput(pStageHandle, i);
    }

    BDBG_ASSERT(0 == pRaagaStage->totalInputs);

    for (i = 0; i < BDSP_ConnectionType_eMax; i++)
    {
        BDBG_ASSERT(pRaagaStage->numInputs[i] == 0);
    }

    BDBG_LEAVE(BDSP_Raaga_P_RemoveAllInputs);
    return;
}

/***********************************************************************
Name        :   BDSP_Raaga_P_AddInterTaskBufferInput

Type        :   PI Interface

Input       :   pStageHandle        -   Handle of the Stage whose input will be Intertask buffer.
                dataType            -   Type of data present in the Intertask buffer.
                pBufferHandle       -   Intertask buffer descriptor provided by the PI.
                pInputIndex     -   Index of the input which is associated for the Intertask buffer.

Return      :   Error Code to return SUCCESS or FAILURE

Functionality   :   Following are the operations performed.
        1)  Retreive the the free input index for the stage which can be used for this Intertask buffer.
        2)  Populate the Source details for the Stage with appropriate values using the Intertask descriptor provided by the PI.
        3)  Populate the Address of the I/O and I/O Generic buffers.
        4)  Increment the number of inputs from Intertask buffer for this stage and total inputs to stage.
        5)  Set the Intertask buffer's InUse variable if some stage is already connected to feed data into the Intertask buffer.
        6)  Fill the input index pointer for the PI for later use.
        7)  If the stage is already running/inside watchdog recovery then perform the CIT reconfiguration.
***********************************************************************/

BERR_Code BDSP_Raaga_P_AddInterTaskBufferInput(
    void *pStageHandle,
    BDSP_DataType dataType,
    const BDSP_InterTaskBuffer *pBufferHandle,
    unsigned *pInputIndex)
{
    BERR_Code err = BERR_SUCCESS;
    BDSP_RaagaStage *pRaagaStage = (BDSP_RaagaStage *)pStageHandle;
    BDSP_P_InterTaskBuffer *pRaagaInterTaskBuffer = (BDSP_P_InterTaskBuffer *)pBufferHandle;
    unsigned ipIndex;

    BDBG_ENTER(BDSP_Raaga_P_AddInterTaskBufferInput);

    BDBG_OBJECT_ASSERT(pRaagaStage, BDSP_RaagaStage);
    BDBG_OBJECT_ASSERT(pRaagaInterTaskBuffer, BDSP_P_InterTaskBuffer);
    BDBG_ASSERT(NULL != pInputIndex);
    BDBG_ASSERT(dataType == pRaagaInterTaskBuffer->dataType);

    BDSP_Raaga_P_GetFreeInputPortIndex(pRaagaStage, &ipIndex);
    BDBG_ASSERT(ipIndex < BDSP_AF_P_MAX_IP_FORKS);

    /* Connect the inter-task buffer to the destination stage's input */
    pRaagaStage->sStageInput[ipIndex].eNodeValid = BDSP_AF_P_eValid;
    pRaagaStage->sStageInput[ipIndex].eConnectionType = BDSP_ConnectionType_eInterTaskBuffer;
    pRaagaStage->sStageInput[ipIndex].connectionHandle = NULL;
    pRaagaStage->sStageInput[ipIndex].connectionDetails.interTask.hInterTask
        = (BDSP_InterTaskBufferHandle)&pRaagaInterTaskBuffer->interTaskBuffer;

    BDSP_MEM_P_ConvertAddressToOffset(pRaagaStage->pContext->pDevice->memHandle,
        pRaagaInterTaskBuffer->pIoBufferDesc,
        &pRaagaStage->sStageInput[ipIndex].ui32StageIOBuffCfgAddr);

    BDSP_MEM_P_ConvertAddressToOffset(pRaagaStage->pContext->pDevice->memHandle,
        pRaagaInterTaskBuffer->pIoBufferGenericDesc,
        &pRaagaStage->sStageInput[ipIndex].ui32StageIOGenericDataBuffCfgAddr);

    pRaagaStage->numInputs[BDSP_ConnectionType_eInterTaskBuffer] += 1;

    pRaagaInterTaskBuffer->dstIndex = ipIndex;
    pRaagaInterTaskBuffer->dstHandle = pStageHandle;

    *pInputIndex = ipIndex;
    pRaagaStage->totalInputs++;

    /* Send the cit re-configuration command to the DSP to indicate an added input port */
    /* if the dest stage is running and Watchdog recovery is not underway */
    if ((pRaagaStage->running)&&(!pRaagaStage->pContext->contextWatchdogFlag))
    {
        BDSP_RaagaTask *pRaagaTask = pRaagaStage->pRaagaTask;


        BDSP_AF_P_sNODE_CONFIG  *psNodeConfig;
        raaga_dramaddr  ui32NodeIpBuffCfgAddr, ui32NodeIpGenericDataBuffCfgAddr;
        BDSP_AF_P_sTASK_CONFIG  *psWorkingTaskCitBuffAddr_Cached = NULL;

        BDBG_OBJECT_ASSERT(pRaagaTask, BDSP_RaagaTask);

        psWorkingTaskCitBuffAddr_Cached = (BDSP_AF_P_sTASK_CONFIG *)pRaagaTask->taskMemGrants.sSpareCitStruct.pBaseAddr;


        BDSP_MEM_P_ConvertAddressToOffset(pRaagaStage->pContext->pDevice->memHandle,
            pRaagaInterTaskBuffer->pIoBufferDesc,
            &ui32NodeIpBuffCfgAddr);

        BDSP_MEM_P_ConvertAddressToOffset(pRaagaStage->pContext->pDevice->memHandle,
            pRaagaInterTaskBuffer->pIoBufferGenericDesc,
            &ui32NodeIpGenericDataBuffCfgAddr);


        psNodeConfig = &psWorkingTaskCitBuffAddr_Cached->sNodeConfig[0];
        /* Making the Input port valid */
        psNodeConfig->eNodeIpValidFlag[ipIndex] = BDSP_AF_P_eValid;
        /* Setting the IO and IO Generic buffer structure addresses for the Node 0 */
        psNodeConfig->ui32NodeIpBuffCfgAddr[ipIndex] = ui32NodeIpBuffCfgAddr;
        psNodeConfig->ui32NodeIpGenericDataBuffCfgAddr[ipIndex] = ui32NodeIpGenericDataBuffCfgAddr;
        psNodeConfig->ui32NumSrc++;

        /* Setting the IO and IO Generic buffer structure addresses and enabling the Valid Flag for the Node 1 */
        psNodeConfig = &psWorkingTaskCitBuffAddr_Cached->sNodeConfig[BDSP_CIT_P_NUM_SPECIAL_NODES];
        psNodeConfig->ui32NodeIpBuffCfgAddr[ipIndex] = ui32NodeIpBuffCfgAddr;
        psNodeConfig->ui32NodeIpGenericDataBuffCfgAddr[ipIndex] = ui32NodeIpGenericDataBuffCfgAddr;
        psNodeConfig->eNodeIpValidFlag[ipIndex] = BDSP_AF_P_eValid;
        psNodeConfig->ui32NumSrc++;
        BDSP_MEM_P_FlushCache(pRaagaStage->pContext->pDevice->memHandle, (void *)psWorkingTaskCitBuffAddr_Cached, sizeof(*psWorkingTaskCitBuffAddr_Cached));

        /* Send the cit re-configuration command to DSP */
        err = BDSP_Raaga_P_SendCitReconfigCommand(pRaagaTask, psWorkingTaskCitBuffAddr_Cached);

        if (err)
        {
            goto err;
        }
    }
    if (pRaagaInterTaskBuffer->srcHandle)
    {
        pRaagaInterTaskBuffer->inUse = true;
    }

    goto end;

err:
    *pInputIndex = BDSP_AF_P_MAX_IP_FORKS;
    pRaagaStage->totalInputs--;
    pRaagaStage->eStageOpBuffDataType[ipIndex] = BDSP_AF_P_DistinctOpType_eMax;
    pRaagaInterTaskBuffer->dstIndex = -1;
    pRaagaInterTaskBuffer->dstHandle = NULL;
    pRaagaStage->numInputs[BDSP_ConnectionType_eInterTaskBuffer] -= 1;

    pRaagaStage->sStageInput[ipIndex].eNodeValid = false;
    pRaagaStage->sStageInput[ipIndex].eConnectionType = BDSP_ConnectionType_eMax;
    pRaagaStage->sStageInput[ipIndex].connectionHandle = NULL;

    BKNI_Memset(&pRaagaStage->sStageInput[ipIndex].connectionDetails, 0,
                sizeof(pRaagaStage->sStageInput[ipIndex].connectionDetails));

end:
    BDBG_LEAVE(BDSP_Raaga_P_AddInterTaskBufferInput);
    return err;
}

/***********************************************************************
Name        :   BDSP_Raaga_P_AddInterTaskBufferOutput

Type        :   PI Interface

Input       :   pStageHandle        -   Handle of the Stage whose output will be Intertask buffer.
                dataType            -   Type of data present in the Intertask buffer.
                pBufferHandle       -   Intertask buffer descriptor provided by the PI.
                pOutputIndex        -   Index of the output which is associated for the Intertask buffer.

Return      :   Error Code to return SUCCESS or FAILURE

Functionality   :   Following are the operations performed.
        1)  Retreive the the free output index for the stage which can be used for this Intertask buffer.
        2)  Populate the Destination details for the Stage with appropriate values using the Intertask descriptor provided by the PI.
        3)  Populate the Address of the I/O and I/O Generic buffers.
        4)  Increment the number of outputs to Intertask buffer from this stage and total outputs from this stage.
        5)  Set the Intertask buffer's InUse variable if some stage is already connected to consume data from this  Intertask buffer.
        6)  Fill the input index pointer for the PI for later use.
***********************************************************************/

BERR_Code BDSP_Raaga_P_AddInterTaskBufferOutput(
    void *pStageHandle,
    BDSP_DataType dataType,
    const BDSP_InterTaskBuffer *pBufferHandle,
    unsigned *pOutputIndex)
{
    BERR_Code err = BERR_SUCCESS;
    BDSP_RaagaStage *pRaagaStage = (BDSP_RaagaStage *)pStageHandle;
    BDSP_P_InterTaskBuffer *pRaagaInterTaskBuffer = (BDSP_P_InterTaskBuffer *)pBufferHandle;
    unsigned opIndex;

    BDBG_ENTER(BDSP_Raaga_P_AddInterTaskBufferOutput);
    BDBG_OBJECT_ASSERT(pRaagaStage, BDSP_RaagaStage);
    BDBG_OBJECT_ASSERT(pRaagaInterTaskBuffer, BDSP_P_InterTaskBuffer);
    BDBG_ASSERT(NULL != pOutputIndex);
    BDBG_ASSERT(dataType == pRaagaInterTaskBuffer->dataType);

    BDSP_Raaga_P_GetFreeOutputPortIndex(pRaagaStage, &opIndex);
    BDBG_ASSERT(opIndex < BDSP_AF_P_MAX_OP_FORKS);

    /* Connect the inter-task buffer to the source stage's output */
    pRaagaStage->sStageOutput[opIndex].eNodeValid = true;
    pRaagaStage->sStageOutput[opIndex].eConnectionType = BDSP_ConnectionType_eInterTaskBuffer;
    pRaagaStage->sStageOutput[opIndex].connectionHandle = NULL;
    pRaagaStage->sStageOutput[opIndex].connectionDetails.interTask.hInterTask
        = (BDSP_InterTaskBufferHandle)&pRaagaInterTaskBuffer->interTaskBuffer;

    BDSP_MEM_P_ConvertAddressToOffset(pRaagaStage->pContext->pDevice->memHandle,
        pRaagaInterTaskBuffer->pIoBufferDesc,
        &pRaagaStage->sStageOutput[opIndex].ui32StageIOBuffCfgAddr);

    BDSP_MEM_P_ConvertAddressToOffset(pRaagaStage->pContext->pDevice->memHandle,
        pRaagaInterTaskBuffer->pIoBufferGenericDesc,
        &pRaagaStage->sStageOutput[opIndex].ui32StageIOGenericDataBuffCfgAddr);

    pRaagaStage->numOutputs[BDSP_ConnectionType_eInterTaskBuffer] += 1;
    pRaagaStage->eStageOpBuffDataType[opIndex] = pRaagaInterTaskBuffer->distinctOp;

    pRaagaInterTaskBuffer->srcIndex = opIndex;
    pRaagaInterTaskBuffer->srcHandle = pStageHandle;

    if (pRaagaInterTaskBuffer->dstHandle)
    {
        pRaagaInterTaskBuffer->inUse = true;
    }

    *pOutputIndex = opIndex;
    pRaagaStage->totalOutputs++;

    BDBG_LEAVE(BDSP_Raaga_P_AddInterTaskBufferOutput);

    return err;
}

/***********************************************************************
Name        :   BDSP_Raaga_P_SendCitReconfigCommand

Type        :   BDSP Internal

Input       :   pRaagaTask      -   Handle of the Task for which the config change command needs to sent.
                psWorkingTaskCitBuffAddr_Cached -   Cached address of the working CIT buffer.

Return      :   Error Code to return SUCCESS or FAILURE

Functionality   :   Following are the operations performed.
        1)  Analyse the CIT network and flush the data into working CIT buffer.
        2)  Update the command with the new structures.
        3)  Issue the command and wait for it.
    Note: This command is used when we need to reconfigure the running task.
***********************************************************************/

BERR_Code BDSP_Raaga_P_SendCitReconfigCommand(
    BDSP_RaagaTask *pRaagaTask,
    BDSP_AF_P_sTASK_CONFIG  *psWorkingTaskCitBuffAddr_Cached
    )
{
    BERR_Code err = BERR_SUCCESS;
    BDSP_Raaga  *pDevice;
    BDSP_Raaga_P_Command sCommand;
    BDSP_Raaga_P_MsgType eMsgType;
    BDSP_Raaga_P_Response sRsp;


    BDBG_ENTER(BDSP_Raaga_P_SendCitReconfigCommand);

    pDevice = pRaagaTask->pContext->pDevice;

    /*  Analyze the Reconfigured CIT : First level Information */


    BDSP_P_AnalyseCit(pDevice->memHandle, psWorkingTaskCitBuffAddr_Cached);
    BDSP_MEM_P_FlushCache(pDevice->memHandle, (void *)psWorkingTaskCitBuffAddr_Cached, sizeof(*psWorkingTaskCitBuffAddr_Cached));

    /*Prepare command to stop the task */
    sCommand.sCommandHeader.ui32CommandID = BDSP_RAAGA_RECONFIGURATION_COMMAND_ID;
    sCommand.sCommandHeader.ui32CommandCounter = 0;
    sCommand.sCommandHeader.ui32TaskID = pRaagaTask->taskId;
    sCommand.sCommandHeader.eResponseType = BDSP_Raaga_P_ResponseType_eResponseRequired;
    sCommand.sCommandHeader.ui32CommandSizeInBytes =  sizeof(BDSP_Raaga_P_Command);

    BDSP_MEM_P_ConvertAddressToOffset(pDevice->memHandle, (void *)(psWorkingTaskCitBuffAddr_Cached),
        &(sCommand.uCommand.sCitReconfigCommand.ui32ModifiedCitAddr));

    BDSP_MEM_P_ConvertAddressToOffset(pDevice->memHandle,
        (pRaagaTask->taskMemGrants.sCitStruct.pBaseAddr),
        &(sCommand.uCommand.sCitReconfigCommand.ui32RunningTaskCitAddr));

    sCommand.uCommand.sCitReconfigCommand.ui32SizeInBytes = pRaagaTask->taskMemGrants.sCitStruct.ui32Size;

    pRaagaTask->lastEventType = sCommand.sCommandHeader.ui32CommandID;
    BKNI_ResetEvent(pRaagaTask->hEvent);
    err = BDSP_Raaga_P_SendCommand(pDevice->hCmdQueue[pRaagaTask->settings.dspIndex], &sCommand,(void *)pRaagaTask);

    if (BERR_SUCCESS != err)
    {
        BDBG_ERR(("BDSP_Raaga_P_SendCitReconfigCommand: CFG_Command failed!"));
        err = BERR_TRACE(err);
        goto end;
    }
    /* Wait for Ack_Response_Received event w/ timeout */
    err = BKNI_WaitForEvent(pRaagaTask->hEvent, BDSP_RAAGA_EVENT_TIMEOUT_IN_MS);
    if (BERR_TIMEOUT == err)
    {
        BDBG_ERR(("BDSP_Raaga_P_SendCitReconfigCommand: CFG_Command TIMEOUT!"));
        err = BERR_TRACE(err);
        goto end;
    }

    eMsgType = BDSP_Raaga_P_MsgType_eSyn;
    err = BDSP_Raaga_P_GetMsg(pRaagaTask->hSyncMsgQueue, (void *)&sRsp,eMsgType);

    if (BERR_SUCCESS != err)
    {
        BDBG_ERR(("BDSP_Raaga_P_SendCitReconfigCommand: Unable to read ACK!"));
        err = BERR_TRACE(err);
        goto end;
    }

    if ((sRsp.sCommonAckResponseHeader.eStatus != BERR_SUCCESS)||
        (sRsp.sCommonAckResponseHeader.ui32ResponseID != BDSP_RAAGA_RECONFIGURATION_RESPONSE_ID)||
        (sRsp.sCommonAckResponseHeader.ui32TaskID != pRaagaTask->taskId))
    {

        BDBG_ERR(("BDSP_Raaga_P_SendCitReconfigCommand: CFG_Command ACK not received successfully!eStatus = %d , ui32ResponseID = %d , ui32TaskID %d ",
            sRsp.sCommonAckResponseHeader.eStatus,sRsp.sCommonAckResponseHeader.ui32ResponseID,sRsp.sCommonAckResponseHeader.ui32TaskID));
        err = BERR_TRACE(sRsp.sCommonAckResponseHeader.eStatus);
        goto end;
    }

    BDBG_LEAVE(BDSP_Raaga_P_SendCitReconfigCommand);
end:
    return err;
}

/***********************************************************************
Name        :   BDSP_InitFmmBufferDescriptor

Type        :   PI Interface

Input       :   pDescriptor -   Handle of the FMM buffer.

Return      :   Error Code to return SUCCESS or FAILURE

Functionality   :   Following are the operations performed.
        1)   Allocate the memory for the FMM descriptor and reset the memory..
***********************************************************************/

BERR_Code BDSP_InitFmmBufferDescriptor(
    BDSP_FmmBufferDescriptor *pDescriptor /* [out] */
    )
{
    BERR_Code errCode=BERR_SUCCESS;

    pDescriptor = BKNI_Malloc(sizeof(BDSP_FmmBufferDescriptor));
    if ( NULL == pDescriptor )
    {
        errCode = BERR_TRACE(BERR_OUT_OF_SYSTEM_MEMORY);
        BDBG_ERR(("BDSP_InitFmmBufferDescriptor::Memory not allocated!"));
        goto err_malloc_initFmmBuffer;
    }
    BKNI_Memset(pDescriptor, 0, sizeof(*pDescriptor));

err_malloc_initFmmBuffer:

    return(errCode); /*its void type actually*/

}

/***********************************************************************
Name        :   BDSP_Raaga_P_GetFreeInputPortIndex

Type        :   BDSP Internal

Input       :   pStage      -   Handle of the Stage for which we need to return the Input port index
                index              -    Index returned back.

Return      :   Error Code to return SUCCESS or FAILURE

Functionality   :   Following are the operations performed.
        1)  Return the first free input index for the stage and return the same to the caller.
***********************************************************************/

void BDSP_Raaga_P_GetFreeInputPortIndex(BDSP_RaagaStage *pStage, unsigned *index)
{
    unsigned i;

    for (i = 0; i < BDSP_AF_P_MAX_IP_FORKS; i++)
    {
        if (pStage->sStageInput[i].eNodeValid != BDSP_AF_P_eValid)
        {
            break;
        }
    }

    *index = i;
}

/***********************************************************************
Name        :   BDSP_Raaga_P_GetFreeOutputPortIndex

Type        :   BDSP Internal

Input       :   pStage      -   Handle of the Stage for which we need to return the Output port index
                index              -    Index returned back.

Return      :   Error Code to return SUCCESS or FAILURE

Functionality   :   Following are the operations performed.
        1)  Return the first free output index for the stage and return the same to the caller.
***********************************************************************/

void BDSP_Raaga_P_GetFreeOutputPortIndex(BDSP_RaagaStage *pStage, unsigned *index)
{
    unsigned i;

    for (i = 0; i < BDSP_AF_P_MAX_OP_FORKS; i++)
    {
        if (pStage->sStageOutput[i].eNodeValid != BDSP_AF_P_eValid)
        {
            break;
        }
    }

    *index = i;
}

/***********************************************************************
Name        :   BDSP_Raaga_P_AddOutputStage

Type        :   PI Interface

Input       :   pSrcStageHandle -   Handle of the Source Stage for which output must be fed to another Stage.
                dataType            -   Type of Data which is output of the Stage.
                pDstStageHandle -   Handle of the Destination Stage which must be connected at Output.
                pSourceOutputIndex  -   Index of the Ouput for the Source Stage.
                pDestinationInputIndex  -   Index of the Input for the Destination Stage.

Return      :   Error Code to return SUCCESS or FAILURE

Functionality   :   Following are the operations performed.
        1)  Retreive the the free output and index for the Source and Destination Stage respectively.
        2)  Interconnect the Stages but populating the Output and Input structures of Source Stage and Destination Stage using a InterStage Buffer.
        3)  Return the Source Output index and Destination Intput Index.
***********************************************************************/

BERR_Code BDSP_Raaga_P_AddOutputStage(
    void *pSrcStageHandle,
    BDSP_DataType dataType,
    void *pDstStageHandle,
    unsigned *pSourceOutputIndex,
    unsigned *pDestinationInputIndex
    )
{
    BDSP_AF_P_sIO_BUFFER *pIoBuffDesc_Cached = NULL;
    BDSP_AF_P_sIO_GENERIC_BUFFER *pIoGenBuffDesc_Cached = NULL;
    BDSP_RaagaContext *pRaagaContext = NULL;
    BDSP_Raaga *pDevice = NULL;
    BDSP_RaagaStage *pRaagaSrcStage = pSrcStageHandle;
    BDSP_RaagaStage *pRaagaDstStage = pDstStageHandle;
    BERR_Code errCode = BERR_SUCCESS;
    unsigned numBuffers = 1, ipIndex, opIndex;

    BDBG_ASSERT(pSrcStageHandle);
    BDBG_ASSERT(pDstStageHandle);

    BDBG_ASSERT(pRaagaSrcStage);
    pRaagaContext = (BDSP_RaagaContext   *)pRaagaSrcStage->pContext; /*src or dest*/
    BDBG_ASSERT(pRaagaContext);
    pDevice = (BDSP_Raaga *)pRaagaContext->pDevice;
    BDBG_ASSERT(pDevice);

    BDSP_Raaga_P_GetFreeInputPortIndex(pRaagaDstStage, &ipIndex);
    BDBG_ASSERT(ipIndex < BDSP_AF_P_MAX_IP_FORKS);

    BDSP_Raaga_P_GetFreeOutputPortIndex(pRaagaSrcStage, &opIndex);
    BDBG_ASSERT(opIndex < BDSP_AF_P_MAX_OP_FORKS);

    /*Populate the distinct output type which can be used to prepare node configuration*/
    BDSP_Raaga_P_GetDistinctOpTypeAndNumChans(dataType, &numBuffers, &pRaagaSrcStage->eStageOpBuffDataType[opIndex]);

    pRaagaSrcStage->sStageOutput[opIndex].eNodeValid=BDSP_AF_P_eValid;
    pRaagaSrcStage->sStageOutput[opIndex].eConnectionType=BDSP_ConnectionType_eStage;
    pRaagaSrcStage->sStageOutput[opIndex].connectionHandle = &pRaagaDstStage->stage;
    pRaagaSrcStage->sStageOutput[opIndex].connectionDetails.stage.hStage=&pRaagaDstStage->stage;

    pIoBuffDesc_Cached = pRaagaSrcStage->sStageOutput[opIndex].pIoBuffDesc;
    pIoGenBuffDesc_Cached = pRaagaSrcStage->sStageOutput[opIndex].pIoGenBuffDesc;

    pIoBuffDesc_Cached->eBufferType = BDSP_AF_P_BufferType_eDRAM_IS;
    pIoBuffDesc_Cached->ui32NumBuffers = numBuffers;

    /* DDRE does a DMA out to the input buffers and the core code always runs as 5.1. For a stereo case this will fail in the new CIT
    as we will only allocate stereo buffers. Hardcoding to 8 for now and this will have to be removed once the DDRE implementation
    is changed to DMA required data to scratch and use the scratch space instead of the input buffer */

    if (pRaagaDstStage->algorithm == BDSP_Algorithm_eDdre)
    {
        pIoBuffDesc_Cached->ui32NumBuffers = 8;
    }

    /*the actual buffers itself allocated will be assigned during start time as we dont know the node network now*/
    pIoGenBuffDesc_Cached->eBufferType = BDSP_AF_P_BufferType_eDRAM_IS;
    pIoGenBuffDesc_Cached->ui32NumBuffers = 1;

    BDSP_MEM_P_FlushCache(pDevice->memHandle, (void *)pIoBuffDesc_Cached, sizeof(*pIoBuffDesc_Cached));
    BDSP_MEM_P_FlushCache(pDevice->memHandle, (void *)pIoGenBuffDesc_Cached, sizeof(*pIoGenBuffDesc_Cached));

    BDSP_MEM_P_ConvertAddressToOffset(pDevice->memHandle,
                                pRaagaSrcStage->sStageOutput[opIndex].pIoBuffDesc,
                                &pRaagaSrcStage->sStageOutput[opIndex].ui32StageIOBuffCfgAddr);

    BDSP_MEM_P_ConvertAddressToOffset(pDevice->memHandle,
                                pRaagaSrcStage->sStageOutput[opIndex].pIoGenBuffDesc,
                                &pRaagaSrcStage->sStageOutput[opIndex].ui32StageIOGenericDataBuffCfgAddr);

    pRaagaDstStage->sStageInput[ipIndex].eNodeValid=BDSP_AF_P_eValid;
    pRaagaDstStage->sStageInput[ipIndex].eConnectionType=BDSP_ConnectionType_eStage;
    pRaagaDstStage->sStageInput[ipIndex].connectionHandle = &pRaagaSrcStage->stage;
    pRaagaDstStage->sStageInput[ipIndex].connectionDetails.stage.hStage=&pRaagaSrcStage->stage;

    /*We have allocated one descriptor for every input and output,
    so for a connection we have one o/p descriptor from the input stage and one i/p descriptor for the output stage*/
    /*ONE DESCRIPTOR FOR ONE CONNECTION AND LET THAT BE THE INPUT(SRC) STAGE'S OUTPUT DESCRIPTOR ie pRaagaSrcStage->sStageOutput*/

    /*the actual buffers itself allocated will be assigned during start time as we dont know the node network now*/
    pRaagaDstStage->sStageInput[ipIndex].ui32StageIOBuffCfgAddr
        = pRaagaSrcStage->sStageOutput[opIndex].ui32StageIOBuffCfgAddr;
    pRaagaDstStage->sStageInput[ipIndex].ui32StageIOGenericDataBuffCfgAddr
        = pRaagaSrcStage->sStageOutput[opIndex].ui32StageIOGenericDataBuffCfgAddr;


    pRaagaSrcStage->numOutputs[BDSP_ConnectionType_eStage]+=1;

    *pSourceOutputIndex = opIndex;
    pRaagaSrcStage->totalOutputs+=1;


    pRaagaDstStage->numInputs[BDSP_ConnectionType_eStage]+=1;

    *pDestinationInputIndex = ipIndex;
    pRaagaDstStage->totalInputs+=1;

    /*The Interstage buffers that are allocated during open time can be assigned to stages in the start time fw download during traversing
    or during the actual cit generation itself*/

    return(errCode);
}

/***********************************************************************
Name        :   BDSP_Raaga_P_CreateContext

Type        :   PI Interface

Input       :   pDeviceHandle - Device handle for which the context needs to created.
                pSettings - input settings for creating the context.
                pContextHandle -pointer returned to the PI for its use.

Return      :   Error Code to return SUCCESS or FAILURE

Functionality   :   Following are the operations performed.
        1)  Allocate the memory that is required for holding the properties of the context.
        2)  Intialise the Context handle for the context to store the address.
        3)  Intialise all the function pointers which will be used by the PI for further processing.
        4)  Install the interrupts used at the Context level.
        5)  Allocate the Context level memory(VOM table) required for the context.
        6)  Error handling if any errors occurs.
***********************************************************************/

BERR_Code BDSP_Raaga_P_CreateContext(
    void *pDeviceHandle,
    const BDSP_ContextCreateSettings *pSettings,
    BDSP_ContextHandle *pContextHandle
    )
{
    BDSP_Raaga *pDevice = (BDSP_Raaga *)pDeviceHandle;
    BDSP_RaagaContext *pRaagaContext;
    BERR_Code errCode=BERR_SUCCESS;

    BDBG_ENTER( BDSP_Raaga_P_CreateContext );
    BDBG_OBJECT_ASSERT(pDevice, BDSP_Raaga);

    /* Alloc raaga context */
    pRaagaContext = BKNI_Malloc(sizeof(BDSP_RaagaContext));
    if ( NULL == pRaagaContext )
    {
        errCode = BERR_TRACE(BERR_OUT_OF_SYSTEM_MEMORY);
        goto end;
    }
    BKNI_Memset(pRaagaContext, 0, sizeof(*pRaagaContext));
    BDBG_OBJECT_SET(pRaagaContext, BDSP_RaagaContext);
    BLST_S_INIT(&pRaagaContext->freeTaskList);
    BKNI_AcquireMutex(pDevice->captureMutex);
    BLST_S_INIT(&pRaagaContext->allocTaskList);
    BKNI_ReleaseMutex(pDevice->captureMutex);
    pRaagaContext->pDevice = pDevice;

    /* Init context */
    BDSP_P_InitContext(&pRaagaContext->context, pRaagaContext);
    pRaagaContext->context.destroy = BDSP_Raaga_P_DestroyContext;
    pRaagaContext->context.getDefaultTaskSettings = BDSP_Raaga_P_GetDefaultTaskSettings;
    pRaagaContext->context.getInterruptHandlers = BDSP_Raaga_P_GetInterruptHandlers;
    pRaagaContext->context.setInterruptHandlers= BDSP_Raaga_P_SetInterruptHandlers;
    pRaagaContext->context.processWatchdogInterrupt= BDSP_Raaga_P_ProcessWatchdogInterrupt;
    pRaagaContext->context.createInterTaskBuffer = BDSP_Raaga_P_InterTaskBuffer_Create;

    pRaagaContext->context.getDefaultStageCreateSettings = BDSP_Raaga_P_GetDefaultStageCreateSettings;
    pRaagaContext->context.createStage = BDSP_Raaga_P_CreateStage;
    pRaagaContext->context.createTask = BDSP_Raaga_P_CreateTask;
    pRaagaContext->context.createCapture = BDSP_Raaga_P_AudioCaptureCreate;

    /* Support for RDB Queue Addition */
    pRaagaContext->context.createQueue = BDSP_Raaga_P_Queue_Create;
    pRaagaContext->context.getDefaultQueueSettings = BDSP_Raaga_P_GetDefaultCreateQueueSettings;

    errCode = BDSP_Raaga_P_ContextInterruptInstall((void *)pRaagaContext);
    if ( BERR_SUCCESS!=errCode )
    {
        goto err_interrupt_install;
    }

    pRaagaContext->settings = *pSettings;

    /*In the new CIT, BDSP_Context_Create() will no longer allocate any task memory or scratch memory
    Essentially, contexts will simply be for handling watchdog distribution to multiple PIs
    So the existing task creation will go the the task_create function*/

    errCode = BDSP_Raaga_P_AllocateContextMemory((void *)pRaagaContext);
    if ( errCode != BERR_SUCCESS )
    {
        errCode = BERR_TRACE(BERR_OUT_OF_SYSTEM_MEMORY);
        goto err_context_mem;
    }
    /* Success, add to device's context list */
    BKNI_AcquireMutex(pDevice->captureMutex);
    BLST_S_INSERT_HEAD(&pDevice->contextList, pRaagaContext, node);
    *pContextHandle= &pRaagaContext->context;
    BKNI_ReleaseMutex(pDevice->captureMutex);
    goto end;

err_context_mem:

    BDSP_Raaga_P_FreeContextMemory((void *)pRaagaContext);
    /* Remove myself from the device's context list */

err_interrupt_install:

    BDSP_Raaga_P_ContextInterruptUninstall((void *)pRaagaContext);

    /* Invalidate and free object */
    BDBG_OBJECT_DESTROY(pRaagaContext, BDSP_RaagaContext);
    BKNI_Free(pRaagaContext);

end:

    BDBG_LEAVE( BDSP_Raaga_P_CreateContext );
    return errCode;
}

/***********************************************************************
Name        :   BDSP_Raaga_P_DestroyContext

Type        :   PI Interface

Input       :   pContextHandle - Context handle which needs to be closed.

Return      :   None

Functionality   :   Following are the operations performed.
        1)  Free the memory that was allocated for holding the Context level memory(VOM table) for the context.
        2)  Free any that was accidently left open under the Context.
        3)  Un-Install the interrupts used at the Context level.
        4)  Free the Context memory that was allocated.
***********************************************************************/

void BDSP_Raaga_P_DestroyContext(
    void *pContextHandle
    )
{
    BDSP_RaagaContext *pRaagaContext = (BDSP_RaagaContext *)pContextHandle;
    BDSP_RaagaTask *pTask;
    BDSP_Raaga *pDevice = pRaagaContext->pDevice;

    BDBG_ENTER(BDSP_Raaga_P_DestroyContext);

    BDBG_OBJECT_ASSERT(pRaagaContext, BDSP_RaagaContext);

    BDSP_Raaga_P_FreeContextMemory(pContextHandle);


    BKNI_AcquireMutex(pDevice->captureMutex);
    /* Free all tasks */
    while ( (pTask = BLST_S_FIRST(&pRaagaContext->allocTaskList)) )
    {
        /* Remove from list */
        BLST_S_REMOVE_HEAD(&pRaagaContext->allocTaskList, node);

        BDSP_Raaga_P_FreeTaskMemory((void *)pTask);

        /* Destroy task, this will move it to the free list */
        BDSP_Task_Destroy(&pTask->task);
    }

    while ( (pTask = BLST_S_FIRST(&pRaagaContext->freeTaskList)) )
    {
        /* Remove from list */
        BLST_S_REMOVE_HEAD(&pRaagaContext->freeTaskList, node);

        BDBG_ERR(("Free Task list is not empty in %s ", __FUNCTION__));

        /* Destroy task */
        BDBG_OBJECT_DESTROY(pTask, BDSP_RaagaTask);
        BKNI_Free(pTask);
    }

    /* Remove myself from the device's context list */
    BLST_S_REMOVE(&pDevice->contextList, pRaagaContext, BDSP_RaagaContext, node);
    BKNI_ReleaseMutex(pDevice->captureMutex);

    BDSP_Raaga_P_ContextInterruptUninstall(pContextHandle);


    /* Invalidate and free context */
    BDBG_OBJECT_DESTROY(pRaagaContext, BDSP_RaagaContext);
    BKNI_Free(pRaagaContext);
    BDBG_LEAVE(BDSP_Raaga_P_DestroyContext);
}

/***********************************************************************
Name        :   BDSP_Raaga_P_GetDefaultTaskSettings

Type        :   PI Interface

Input       :   pContextHandle  -   Context handle of the task for which settings are required.
                pSettings           -   Pointer of Task Create settings which needs to set to default settings.

Return      :   None

Functionality   :   Following are the operations performed.
        1)  Clear the memory that was provided by PI.
        2)  Set the master task variable by default as FALSE.
***********************************************************************/

void BDSP_Raaga_P_GetDefaultTaskSettings(
    void *pContextHandle,
    BDSP_TaskCreateSettings *pSettings
    )
{
    BDSP_RaagaContext *pRaagaContext = (BDSP_RaagaContext *)pContextHandle;

    BDBG_OBJECT_ASSERT(pRaagaContext, BDSP_RaagaContext);
    BKNI_Memset(pSettings, 0, sizeof(*pSettings));
    pSettings->masterTask = false;
}

/***********************************************************************
Name        :   BDSP_DSP_P_InterframeRunLengthDecode

Type        :   PI Interface

Input       :   pSrc                    -   Pointer to Source Array which is encoded using Run Length Algorithm
                pDst                    -   Pointer to Memory Location in DRAM where the uncompressed array needs to be copied.
                ui32IfBuffEncodedSize   -   Size of encoded Inter-Frame array
                ui32AllocatedBufferSize -   Size of Memory Allocated in Dram.

Return      :   BERR_Code

Functionality   :   Following are the operations performed.
        1)  Uncompress the Inter-Frame Array using the Run Length Decode Algorithm
        2)  Confirm that enough size has been allocated in DRAM by BDSP.
        3)  Copy the original uncompressed opcodes into DRAM
***********************************************************************/

static BERR_Code BDSP_DSP_P_InterframeRunLengthDecode(void *pSrc, void *pDst, uint32_t ui32IfBuffEncodedSize, uint32_t ui32AllocatedBufferSize)
{
    BERR_Code   rc = BERR_SUCCESS;
    uint32_t ui32IfBuffActualSize = 0;
    uint32_t i =0, j =0;
    uint32_t * pTempSrc = (uint32_t *) pSrc;
    uint32_t * pTempDest = (uint32_t *) pDst;

    BDBG_ENTER(BDSP_DSP_P_InterframeRunLengthDecode);
    BDBG_ASSERT(( ui32IfBuffEncodedSize % 8 == 0)); /* Any array that has been encoded using the run length encode has to be in multiples of 8. Otherwise something has gone wrong */

    for (i = 0; i < (ui32IfBuffEncodedSize >> 3); i++)
    {
        ui32IfBuffActualSize += pTempSrc[2*i + 1];
    }

    /* Size has already been allocated in DRAM. Confirm whether it is big enough. */
    if (ui32AllocatedBufferSize < ui32IfBuffActualSize)
    {
        BDBG_ERR(("Allocated memory (%d) for interframe buffer is less than required (%d)",
                    ui32AllocatedBufferSize,
                    ui32IfBuffActualSize
                 ));
        return BERR_TRACE(BERR_INVALID_PARAMETER);
    }

    /* Then start copying in chunks element by element */
    for (i = 0; i < (ui32IfBuffEncodedSize >> 3); i++)
    {
        for (j = 0; j < pTempSrc[2*i + 1]; j++)
        {
            *pTempDest++ = pTempSrc[2*i];
        }
    }
    BDBG_LEAVE(BDSP_DSP_P_InterframeRunLengthDecode);
    return rc;
}

static BERR_Code BDSP_DSP_P_InitInterframeBuffer(void *pStageHandle)
{
    BERR_Code   rc = BERR_SUCCESS;
    uint32_t ui32ImgId;

    BDSP_RaagaStage *pRaagaStage;
    BDSP_Raaga  *pDevice;
    void *pIfAddr;
    uint32_t ui32IfAddr, ui32IfBuffSize;
    BDSP_AF_P_AlgoId algoId;
    void *pIfAddr_Cached = NULL;
    void *pMemory_Cached = NULL;
    const BDSP_Raaga_P_AlgorithmInfo *pAlgoInfo;

    uint32_t ui32IfBuffEncodedSize = 0;
    BDBG_ENTER(BDSP_DSP_P_InitInterframeBuffer);

    BDBG_ASSERT(NULL != pStageHandle);
    pRaagaStage = (BDSP_RaagaStage *)pStageHandle;
    pDevice = pRaagaStage->pContext->pDevice;

    BDSP_STAGE_TRAVERSE_LOOP_BEGIN(pRaagaStage, pStageIterator)
    BSTD_UNUSED(macroStId);
    BSTD_UNUSED(macroBrId);
    {
        pAlgoInfo = BDSP_Raaga_P_LookupAlgorithmInfo(pStageIterator->algorithm);
        /* Load the interframe for decoder */
        algoId = pAlgoInfo->algoExecInfo.eAlgoIds[1];
        ui32IfAddr = pStageIterator->sDramInterFrameBuffer.ui32DramBufferAddress;
        ui32IfBuffSize = pStageIterator->sDramInterFrameBuffer.ui32BufferSizeInBytes;

        if (algoId == BDSP_AF_P_AlgoId_eInvalid)
        {
            BDBG_ERR(("You are here as there was a problem in the connection handles between stages. "));
            BDBG_ERR(("The Algo Id is invalid for this stage algo %d", pStageIterator->algorithm));
            BDBG_ASSERT(0);
        }
        BDSP_MEM_P_ConvertOffsetToCacheAddr(pDevice->memHandle, ui32IfAddr, &pIfAddr);
        ui32ImgId = BDSP_IMG_ID_IFRAME(algoId);

        pIfAddr_Cached = pIfAddr;
        pMemory_Cached = pDevice->imgCache[ui32ImgId].pMemory ;
        ui32IfBuffEncodedSize = pDevice->imgCache[ui32ImgId].size; /* This is size of the run length encoded inter-frame array. Actual size is calculated below */

        rc = BDSP_DSP_P_InterframeRunLengthDecode(pMemory_Cached, pIfAddr_Cached, ui32IfBuffEncodedSize, ui32IfBuffSize);
        if (rc != BERR_SUCCESS)
        {
        BDBG_ERR(("Error in decoding the inter-frame array for algoid=%d", algoId));;
        return BERR_TRACE(rc);
        }
        BDSP_MEM_P_FlushCache(pDevice->memHandle, (void *)pIfAddr_Cached, ui32IfBuffSize);


        /* Load the interframe for datasync */
        algoId = pAlgoInfo->algoExecInfo.eAlgoIds[0];
        if (algoId != BDSP_AF_P_AlgoId_eInvalid)
        {
            ui32IfAddr = pStageIterator->sDramInterFrameBuffer.ui32DramBufferAddress +
                pStageIterator->sFrameSyncOffset.ui32IfOffset;
            ui32IfBuffSize = pStageIterator->sDramInterFrameBuffer.ui32BufferSizeInBytes -
                pStageIterator->sFrameSyncOffset.ui32IfOffset;


            BDSP_MEM_P_ConvertOffsetToCacheAddr(pDevice->memHandle, ui32IfAddr, &pIfAddr);
            ui32ImgId = BDSP_IMG_ID_IFRAME(algoId);

            pIfAddr_Cached = pIfAddr ;
            pMemory_Cached = pDevice->imgCache[ui32ImgId].pMemory;
            ui32IfBuffEncodedSize = pDevice->imgCache[ui32ImgId].size; /* This is size of the run length encoded inter-frame array. Actual size is calculated below */

            rc = BDSP_DSP_P_InterframeRunLengthDecode(pMemory_Cached, pIfAddr_Cached, ui32IfBuffEncodedSize, ui32IfBuffSize);
            if (rc != BERR_SUCCESS)
            {
                BDBG_ERR(("Error in decoding the inter-frame array for algoid=%d", algoId));;
                return BERR_TRACE(rc);
            }

            BDSP_MEM_P_FlushCache(pDevice->memHandle, (void *)pIfAddr_Cached, ui32IfBuffSize);
        }
    }
    BDSP_STAGE_TRAVERSE_LOOP_END(pStageIterator)

    BDBG_LEAVE(BDSP_DSP_P_InitInterframeBuffer);
    return rc;
}

static BERR_Code BDSP_DSPCHN_P_SendVOMChangeCommand(
    void *pTaskHandle
    )
{
    BDSP_Raaga_P_Command sCommand;
    BDSP_VOM_Table  *pVOMTableInDRAM = NULL;
    raaga_dramaddr    physAddress = 0;
    unsigned int i,j,index = 0;
    BERR_Code err = BERR_SUCCESS;
    BDSP_RaagaTask *pRaagaTask = (BDSP_RaagaTask *)pTaskHandle;
    BDSP_Raaga  *pDevice= pRaagaTask->pContext->pDevice;


    BDBG_ENTER (BDSP_DSPCHN_P_SendVOMChangeCommand);
    BDBG_OBJECT_ASSERT(pRaagaTask, BDSP_RaagaTask);


    pVOMTableInDRAM = (BDSP_VOM_Table *)pRaagaTask->pContext->contextMemInfo.sVomTableInfo.pBaseAddr;

    if (NULL == pVOMTableInDRAM)
    {
        BDBG_ERR (("BDSP_DSPCHN_P_SendVOMChangeCommand :: The allocated address"
            " for VOM table is not proper. Please check the allocation"
            " in BDSP_MM_RequestMemoryAllocation"));

        return BERR_TRACE (BDSP_ERR_BAD_DEVICE_STATE);
    }

    BKNI_Memset(pVOMTableInDRAM, 0,(sizeof(BDSP_VOM_Table)));
    BKNI_Memset(&sCommand,0,sizeof(sCommand));
    for (i=0; i<BDSP_AF_P_AlgoId_eMax; i++)
    {
        unsigned imgId;

        switch ( i )
        {
            /* Special cases for system algorithms present in VOM */
        case BDSP_AF_P_AlgoId_eSysLib:
            imgId = BDSP_SystemImgId_eSyslibCode;
            break;
        case BDSP_AF_P_AlgoId_eAlgoLib:
            imgId = BDSP_SystemImgId_eAlgolibCode;
            break;
        case BDSP_AF_P_AlgoId_eIDSCommonLib:
            imgId = BDSP_SystemImgId_eCommonIdsCode;
            break;
        case BDSP_AF_P_AlgoId_eVidIDSCommonLib:
            imgId = BDSP_SystemImgId_eCommonVideoEncodeIdsCode;
            break;
        case BDSP_AF_P_AlgoId_eScmTask:
            imgId = BDSP_SystemImgId_eScm_Task_Code;
            break;
        case BDSP_AF_P_AlgoId_eVideoDecodeTask:
            imgId = BDSP_SystemImgId_eVideo_Decode_Task_Code;
            break;
        case BDSP_AF_P_AlgoId_eVideoEncodeTask:
            imgId = BDSP_SystemImgId_eVideo_Encode_Task_Code;
            break;
        default:
            imgId = BDSP_IMG_ID_CODE(i);
            break;
        }

        if ( pDevice->imgCache[imgId].pMemory )
        {
            BDSP_BDBG_MSG_LVL1 (("The algo ID %d is valid. So make an index for it in "
                "VOM Table",i));

            pVOMTableInDRAM->sVomTableDetail[index].ui32PageStart = \
                BDSP_sVomTable.sVomTableDetail[i].ui32PageStart;

            pVOMTableInDRAM->sVomTableDetail[index].ui32PageEnd = \
                BDSP_sVomTable.sVomTableDetail[i].ui32PageEnd;

            pVOMTableInDRAM->sVomTableDetail[index].ui32DramAddr = pDevice->imgCache[imgId].offset;
            index++;
        }
    }

    /* Sort the VOM Table based on the Page Start address */
    if (index > 1)
    {
        BDSP_VOM_Table_Entry tempEntry;

        for (i=0;i<index-1;i++)
        {
            for (j=i; j<index;j++)
            {
                if (pVOMTableInDRAM->sVomTableDetail[i].ui32PageStart >
                    pVOMTableInDRAM->sVomTableDetail[j].ui32PageStart)
                {
                    tempEntry = pVOMTableInDRAM->sVomTableDetail[i];
                    pVOMTableInDRAM->sVomTableDetail[i] = \
                        pVOMTableInDRAM->sVomTableDetail[j];
                    pVOMTableInDRAM->sVomTableDetail[j] = tempEntry;
                }
            }
        }
    }

    /* Print VOM for debug */
    BDSP_BDBG_MSG_LVL1 (("VOM TABLE ... with %d valid entries",index));
    for (i=0; i<index; i++)
    {
        BDSP_BDBG_MSG_LVL1 (("Entry ID: %d, Page Start:%x, Page End:%x, DRAM:%x",
            i, pVOMTableInDRAM->sVomTableDetail[i].ui32PageStart,
            pVOMTableInDRAM->sVomTableDetail[i].ui32PageEnd,
            pVOMTableInDRAM->sVomTableDetail[i].ui32DramAddr));
    }

    BDSP_MEM_P_FlushCache(pDevice->memHandle, pVOMTableInDRAM, sizeof(BDSP_VOM_Table));
    BDSP_MEM_P_ConvertAddressToOffset(
        pDevice->memHandle, pRaagaTask->pContext->contextMemInfo.sVomTableInfo.pBaseAddr, &physAddress);

    BDBG_MSG (("VOM Table's location in DRAM : %x",physAddress));

    sCommand.sCommandHeader.ui32CommandID = BDSP_RAAGA_GET_VOM_TABLE_COMMAND_ID;
    sCommand.sCommandHeader.ui32CommandCounter = pRaagaTask->commandCounter++;
    sCommand.sCommandHeader.ui32TaskID = pRaagaTask->taskId;
    sCommand.sCommandHeader.eResponseType = BDSP_Raaga_P_ResponseType_eNone;
    sCommand.sCommandHeader.ui32CommandSizeInBytes =  sizeof(BDSP_Raaga_P_Command);

    sCommand.uCommand.sGetVomTable.ui32NumEntries = index;
    sCommand.uCommand.sGetVomTable.ui32HostVomTableAddr = physAddress;

    err = BDSP_Raaga_P_SendCommand(
        pDevice->hCmdQueue[pRaagaTask->settings.dspIndex], &sCommand,(void *)pRaagaTask);

    if (BERR_SUCCESS != err)
    {
        BDBG_ERR(("VOM Command failed!"));
        return BERR_TRACE(err);
    }

    BDBG_LEAVE (BDSP_DSPCHN_P_SendVOMChangeCommand);
    return BERR_SUCCESS;
}

/***********************************************************************
Name        :   BDSP_Raaga_P_ReleaseFIFO

Type        :   BDSP Internal

Input       :   pDevice     -   Handle of the Device.
                dspIndex        -   Index of the DSP.
                i32Fifo     -   Start index of the FIFO's Allocated.
                numfifos        -   Number of FIFO's allocated.

Return      :   Error Code to return SUCCESS or FAILURE

Functionality   :   Following are the operations performed.
        1)  Acquire the FIFOID mutex of the DSP.
        2)  Free the FIFOs by setting the array to FALSE.
        3)  Release the Mutex before returning.
***********************************************************************/
BERR_Code BDSP_Raaga_P_ReleaseFIFO(BDSP_Raaga   *pDevice, unsigned dspIndex, int32_t* i32Fifo, unsigned numfifos )
{
    unsigned i;
    BKNI_AcquireMutex(pDevice->fifoIdMutex[dspIndex]);
    for(i=0; i < numfifos; i++)
    {
        BDBG_MSG(("Freeing (Fifo)RDB %d", (*i32Fifo+i-BDSP_RAAGA_FIFO_0_INDEX)));
        pDevice->dspFifo[dspIndex][(*i32Fifo+i-BDSP_RAAGA_FIFO_0_INDEX)] = false;
    }
    *i32Fifo = BDSP_RAAGA_INVALID_INDEX;
    BKNI_ReleaseMutex(pDevice->fifoIdMutex[dspIndex]);
    return BERR_SUCCESS;
}

/***********************************************************************
Name        :   BDSP_Raaga_P_AssignFreeFIFO

Type        :   BDSP Internal

Input       :   pDevice     -   Handle of the Device.
                dspIndex        -   Index of the DSP.
                i32Fifo     -   Start index of the FIFO's Allocated to be returned back.
                numfifosreqd    -   Number of FIFO's requested.

Return      :   Error Code to return SUCCESS or FAILURE

Functionality   :   Following are the operations performed.
        1)  Acquire the FIFOID mutex of the DSP.
        2)  Poll for the contiguous free FIFOs requested for in the DSP list.
        3)  Acquire the FIFOs if available by setting the value to TRUE.
        4)  Return the start index of the FIFOs from where the contiguous list is free.
        4)  Release the Mutex before returning.
***********************************************************************/
BERR_Code BDSP_Raaga_P_AssignFreeFIFO(BDSP_Raaga    *pDevice, unsigned dspIndex, int32_t* i32Fifo, unsigned numfifosreqd )
{
    BERR_Code   err=BERR_SUCCESS;
    unsigned count = 0;
    int32_t i =0, start_index = 0;
    BKNI_AcquireMutex(pDevice->fifoIdMutex[dspIndex]);
    /* Find free Fifo Ids */
    for (i=0; i < (int32_t)BDSP_RAAGA_NUM_FIFOS; i++)
    {
        if (false == pDevice->dspFifo[dspIndex][i])
        {
            count++;
            /* Found enough contiguous RDBs. Remember 1 FIFO has 4 RDBs */
            if(count >= numfifosreqd)
            {
                break;
            }
        }
        else
        {
            count = 0;
        }
    }
    if (i >= (int32_t)BDSP_RAAGA_NUM_FIFOS)
    {
        BKNI_ReleaseMutex(pDevice->fifoIdMutex[dspIndex]);
        err = BERR_TRACE(BERR_OUT_OF_DEVICE_MEMORY);
        return err;
    }
    else
    {
        start_index =  i - numfifosreqd + 1;
        for(;i >= start_index; i--)
        {
            BDBG_MSG(("Allocating fifo (RDB) %d", i));
            pDevice->dspFifo[dspIndex][i] = true;
        }
        /* This is the fifo ID from where RDBs are free */
        *i32Fifo = BDSP_RAAGA_FIFO_0_INDEX + start_index;
    }
    BKNI_ReleaseMutex(pDevice->fifoIdMutex[dspIndex]);
    return BERR_SUCCESS;
}

BERR_Code   BDSP_Raaga_P_CreateTaskQueues(void *pTaskHandle,
    unsigned dspIndex
    )
{
    BERR_Code   err=BERR_SUCCESS;
    BDSP_RaagaTask *pRaagaTask = (BDSP_RaagaTask *)pTaskHandle;
    BDSP_RaagaContext *pRaagaContext = (BDSP_RaagaContext *)pRaagaTask->pContext;
    BDSP_Raaga  *pDevice= pRaagaContext->pDevice;
    unsigned uiOffset;
    uint32_t ui32RegOffset = 0;

    BDBG_ENTER(BDSP_Raaga_P_CreateTaskQueues);

    BDBG_OBJECT_ASSERT(pRaagaTask, BDSP_RaagaTask);
    BDBG_OBJECT_ASSERT(pRaagaContext, BDSP_RaagaContext);
    BDBG_OBJECT_ASSERT(pDevice, BDSP_Raaga);

    uiOffset = pDevice->dspOffset[dspIndex];

    err = BDSP_Raaga_P_CreateMsgQueue(&(pRaagaTask->taskMemGrants.sTaskQueue.sTaskSyncQueue),
        pDevice->memHandle, pDevice->regHandle, uiOffset, &(pRaagaTask->hSyncMsgQueue));
    if (BERR_SUCCESS != err)
    {
        BDBG_ERR(("BDSP_Raaga_P_InitParams_StartTask: SYNC RSP queue creation failed!"));
        err = BERR_TRACE(err);
        goto err_create_syncqueue;
    }

    err = BDSP_Raaga_P_CreateMsgQueue(&(pRaagaTask->taskMemGrants.sTaskQueue.sTaskAsyncQueue),
        pDevice->memHandle, pDevice->regHandle, uiOffset, &(pRaagaTask->hAsyncMsgQueue));
    if (BERR_SUCCESS != err)
    {
        BDBG_ERR(("BDSP_Raaga_P_InitParams_StartTask: ASYNC RSP queue creation failed!"));
        err = BERR_TRACE(err);
        goto err_create_asyncqueue;
    }

    if (pRaagaContext->settings.contextType == BDSP_ContextType_eVideo)
    {
        /* Picture delivery queue */
        err = BDSP_Raaga_P_CreateMsgQueue(&(pRaagaTask->taskMemGrants.sTaskQueue.sPDQueue), pDevice->memHandle,
            pDevice->regHandle, uiOffset,&(pRaagaTask->hPDQueue));
        if (BERR_SUCCESS != err)
        {
            BDBG_ERR(("BDSP_Raaga_P_InitParams_StartTask: Picture delivery queue creation failed!"));
            goto err_create_PDQueue;

        }

        /*Picture release queue*/
        err = BDSP_Raaga_P_CreateMsgQueue(&(pRaagaTask->taskMemGrants.sTaskQueue.sPRQueue), pDevice->memHandle,
            pDevice->regHandle, uiOffset,&(pRaagaTask->hPRQueue));
        if (BERR_SUCCESS != err)
        {
            BDBG_ERR(("BDSP_Raaga_P_InitParams_StartTask: Picture release queue creation failed!"));
            goto err_create_PRQueue;

        }

        /*Display  queue*/
        err = BDSP_Raaga_P_CreateMsgQueue(&(pRaagaTask->taskMemGrants.sTaskQueue.sDSQueue), pDevice->memHandle,
            pDevice->regHandle, uiOffset,&(pRaagaTask->hDSQueue));
        if (BERR_SUCCESS != err)
        {
            BDBG_ERR(("BDSP_Raaga_P_InitParams_StartTask: display queue creation failed!"));
            goto err_create_DSQueue;

        }
    }

    /* Video encode context needs xtra Q's namely RDQ and RRQ. Creating them here */
    else if (BDSP_ContextType_eVideoEncode == pRaagaContext->settings.contextType)
    {
        /* Raw Picture delivery queue */
        /* This is not going to be a MsgQueue in real sense. This will hold RDB addresses now. */
        err = BDSP_Raaga_P_AssignFreeFIFO(pDevice,dspIndex,&(pRaagaTask->taskMemGrants.sTaskQueue.sRDQueue.startIndexOfFreeFifo),(BDSP_RAAGA_REALVIDEO_MAX_MSGS_PER_QUEUE >> 2));
        if(err)
        {
            BDBG_ERR(("Unable to find free RDBs for allocating RDQ for raaga encode!!"));
            err = BERR_TRACE(BERR_OUT_OF_DEVICE_MEMORY);
            goto err_find_free_Fifos_RDQueue;
        }

        err = BDSP_Raaga_P_CreateRdbQueue(&(pRaagaTask->taskMemGrants.sTaskQueue.sRDQueue), pDevice->memHandle,
            pDevice->regHandle, uiOffset,&(pRaagaTask->hRDQueue));
        if (BERR_SUCCESS != err)
        {
            BDBG_ERR(("BDSP_Raaga_P_InitParams_StartTask: Raw Picture delivery queue creation failed!"));
            goto err_create_RDQueue;
        }

        /* Raw Picture release queue*/
        err = BDSP_Raaga_P_CreateMsgQueue(&(pRaagaTask->taskMemGrants.sTaskQueue.sRRQueue), pDevice->memHandle,
            pDevice->regHandle, uiOffset,&(pRaagaTask->hRRQueue));
        if (BERR_SUCCESS != err)
        {
            BDBG_ERR(("BDSP_Raaga_P_InitParams_StartTask: Raw Picture release queue creation failed!"));
            goto err_create_RRQueue;
        }

        /* RRQ should start with full buffer capacity */
        ui32RegOffset = BCHP_RAAGA_DSP_FW_CFG_FIFO_1_BASE_ADDR - \
                        BCHP_RAAGA_DSP_FW_CFG_FIFO_0_BASE_ADDR;
        BDSP_Write32(pRaagaTask->hRRQueue->hRegister,
                BCHP_RAAGA_DSP_FW_CFG_FIFO_0_BASE_ADDR + (ui32RegOffset * pRaagaTask->hRRQueue->i32FifoId) + BDSP_RAAGA_P_FIFO_WRITE_OFFSET + uiOffset,
                pRaagaTask->hRRQueue->ui32BaseAddr + (BDSP_FWMAX_VIDEO_BUFF_AVAIL*4));

        /* CC data delivery queue*/
        err = BDSP_Raaga_P_CreateMsgQueue(&(pRaagaTask->taskMemGrants.sTaskQueue.sCCDQueue), pDevice->memHandle,
            pDevice->regHandle, uiOffset,&(pRaagaTask->hCCDQueue));
        if (BERR_SUCCESS != err)
        {
            BDBG_ERR(("BDSP_Raaga_P_AllocateAndInitTask: CCD queue creation failed!"));
            goto err_create_CCDQueue;
        }
    }
    goto end;
err_create_DSQueue:
    if (pRaagaContext->settings.contextType == BDSP_ContextType_eVideo)
    {
        BDSP_Raaga_P_DestroyMsgQueue(pRaagaTask->hDSQueue,
            pDevice->regHandle, uiOffset);
    }
err_create_PRQueue:
    if (pRaagaContext->settings.contextType == BDSP_ContextType_eVideo)
    {
        BDSP_Raaga_P_DestroyMsgQueue(pRaagaTask->hPRQueue,
            pDevice->regHandle, uiOffset);
    }
err_create_PDQueue:
    if (pRaagaContext->settings.contextType == BDSP_ContextType_eVideo)
    {
        BDSP_Raaga_P_DestroyMsgQueue(pRaagaTask->hPDQueue,
            pDevice->regHandle, uiOffset);
    }
err_create_CCDQueue:
    if (BDSP_ContextType_eVideoEncode == pRaagaContext->settings.contextType)
    {
        BDSP_Raaga_P_DestroyMsgQueue(pRaagaTask->hCCDQueue,
            pDevice->regHandle, uiOffset);
    }
err_create_RRQueue:
    if (BDSP_ContextType_eVideoEncode == pRaagaContext->settings.contextType)
    {
        BDSP_Raaga_P_DestroyMsgQueue(pRaagaTask->hRRQueue,
            pDevice->regHandle, uiOffset);
    }
err_create_RDQueue:
    if (BDSP_ContextType_eVideoEncode == pRaagaContext->settings.contextType)
    {
        BDSP_Raaga_P_DestroyRdbQueue(pRaagaTask->hRDQueue,
                pDevice->regHandle, uiOffset);
    }
err_find_free_Fifos_RDQueue:
err_create_asyncqueue:
    BDSP_Raaga_P_DestroyMsgQueue(pRaagaTask->hAsyncMsgQueue,
        pDevice->regHandle, uiOffset);
err_create_syncqueue:
    BDSP_Raaga_P_DestroyMsgQueue(pRaagaTask->hSyncMsgQueue,
        pDevice->regHandle, uiOffset);
end:
    BDBG_LEAVE(BDSP_Raaga_P_CreateTaskQueues);
    return err;
}

BERR_Code   BDSP_Raaga_P_FreeTaskQueues(void *pTaskHandle)
{
    BERR_Code   err=BERR_SUCCESS;
    BDSP_RaagaTask *pRaagaTask = (BDSP_RaagaTask *)pTaskHandle;
    BDSP_RaagaContext *pRaagaContext = pRaagaTask->pContext;
    BDSP_Raaga  *pDevice= pRaagaContext->pDevice;
    unsigned uiOffset;

    BDBG_ENTER(BDSP_Raaga_P_FreeTaskQueues);

    BDBG_OBJECT_ASSERT(pRaagaTask, BDSP_RaagaTask);
    BDBG_OBJECT_ASSERT(pRaagaContext, BDSP_RaagaContext);
    BDBG_OBJECT_ASSERT(pDevice, BDSP_Raaga);

    uiOffset = pDevice->dspOffset[pRaagaTask->settings.dspIndex];

    if (pRaagaContext->settings.contextType == BDSP_ContextType_eVideo)
    {
        err = BDSP_Raaga_P_DestroyMsgQueue(pRaagaTask->hPDQueue,
            pDevice->regHandle, uiOffset);
        if (BERR_SUCCESS != err)
        {
            BDBG_ERR(("BDSP_Raaga_P_FreeTaskQueues: Picture delivery queue destroy failed!"));
            err = BERR_TRACE(err);
        }

        err = BDSP_Raaga_P_DestroyMsgQueue(pRaagaTask->hPRQueue,
            pDevice->regHandle, uiOffset);
        if (BERR_SUCCESS != err)
        {
            BDBG_ERR(("BDSP_Raaga_P_FreeTaskQueues: Picture release queue destroy failed!"));
            err = BERR_TRACE(err);
        }

        err = BDSP_Raaga_P_DestroyMsgQueue(pRaagaTask->hDSQueue,
            pDevice->regHandle, uiOffset);
        if (BERR_SUCCESS != err)
        {
            BDBG_ERR(("BDSP_Raaga_P_FreeAndInvalidateTask: Display queue destroy failed!"));
            err = BERR_TRACE(err);
        }
        BDSP_Raaga_P_ReleaseFIFO(pDevice, pRaagaTask->settings.dspIndex,&(pRaagaTask->taskMemGrants.sTaskQueue.sPDQueue.i32FifoId),1);
        BDSP_Raaga_P_ReleaseFIFO(pDevice, pRaagaTask->settings.dspIndex,&(pRaagaTask->taskMemGrants.sTaskQueue.sPRQueue.i32FifoId),1);
        BDSP_Raaga_P_ReleaseFIFO(pDevice, pRaagaTask->settings.dspIndex,&(pRaagaTask->taskMemGrants.sTaskQueue.sDSQueue.i32FifoId),1);
    }
    if (BDSP_ContextType_eVideoEncode == pRaagaContext->settings.contextType )
    {
        err = BDSP_Raaga_P_DestroyRdbQueue(pRaagaTask->hRDQueue,
            pDevice->regHandle, uiOffset);
        if (BERR_SUCCESS != err)
        {
            BDBG_ERR(("BDSP_Raaga_P_FreeTaskQueues: Raw Picture delivery queue destroy failed!"));
            err = BERR_TRACE(err);
        }

        /* RDQ is now in RDB so free the fifo ids for it */
        BDSP_Raaga_P_ReleaseFIFO(pDevice, pRaagaTask->settings.dspIndex, &(pRaagaTask->taskMemGrants.sTaskQueue.sRDQueue.startIndexOfFreeFifo),(BDSP_RAAGA_REALVIDEO_MAX_MSGS_PER_QUEUE >> 2));
        err = BDSP_Raaga_P_DestroyMsgQueue(pRaagaTask->hRRQueue,
            pDevice->regHandle, uiOffset);
        if (BERR_SUCCESS != err)
        {
            BDBG_ERR(("BDSP_Raaga_P_FreeTaskQueues: Raw Picture release queue destroy failed!"));
            err = BERR_TRACE(err);
        }

        err = BDSP_Raaga_P_DestroyMsgQueue(pRaagaTask->hCCDQueue,
            pDevice->regHandle, uiOffset);
        if (BERR_SUCCESS != err)
        {
            BDBG_ERR(("BDSP_Raaga_P_FreeTaskQueues: CC data delivery queue destroy failed!"));
            err = BERR_TRACE(err);
        }
        BDSP_Raaga_P_ReleaseFIFO(pDevice, pRaagaTask->settings.dspIndex,&(pRaagaTask->taskMemGrants.sTaskQueue.sRDQueue.i32FifoId),1);
        BDSP_Raaga_P_ReleaseFIFO(pDevice, pRaagaTask->settings.dspIndex,&(pRaagaTask->taskMemGrants.sTaskQueue.sRRQueue.i32FifoId),1);
        BDSP_Raaga_P_ReleaseFIFO(pDevice, pRaagaTask->settings.dspIndex,&(pRaagaTask->taskMemGrants.sTaskQueue.sCCDQueue.i32FifoId),1);
    }

    err = BDSP_Raaga_P_DestroyMsgQueue(pRaagaTask->hAsyncMsgQueue, pDevice->regHandle, uiOffset);
    if (BERR_SUCCESS != err)
    {
        BDBG_ERR(("BDSP_Raaga_P_FreeTaskQueues: Async queue destroy failed!"));
        err = BERR_TRACE(err);
    }

    err = BDSP_Raaga_P_DestroyMsgQueue(pRaagaTask->hSyncMsgQueue, pDevice->regHandle, uiOffset);
    if (BERR_SUCCESS != err)
    {
        BDBG_ERR(("BDSP_Raaga_P_FreeTaskQueues: Sync queue destroy failed!"));
        err = BERR_TRACE(err);
    }
    BDSP_Raaga_P_ReleaseFIFO(pDevice, pRaagaTask->settings.dspIndex,&(pRaagaTask->taskMemGrants.sTaskQueue.sTaskSyncQueue.i32FifoId),1);
    BDSP_Raaga_P_ReleaseFIFO(pDevice, pRaagaTask->settings.dspIndex,&(pRaagaTask->taskMemGrants.sTaskQueue.sTaskAsyncQueue.i32FifoId),1);
    BDBG_LEAVE(BDSP_Raaga_P_FreeTaskQueues);

    return err;
}

static BERR_Code   BDSP_Raaga_P_InitParams_CreateTask(
    void *pContextHandle,
    void *pTaskHandle,
    const BDSP_TaskCreateSettings *pSettings
    )
{
    BERR_Code   err=BERR_SUCCESS;
    BDSP_RaagaContext *pRaagaContext = (BDSP_RaagaContext *)pContextHandle;
    BDSP_RaagaTask *pRaagaTask = (BDSP_RaagaTask *)pTaskHandle;
    BDSP_Raaga  *pDevice= pRaagaContext->pDevice;

    BDBG_ENTER(BDSP_Raaga_P_InitParams_CreateTask);

    BDBG_OBJECT_ASSERT(pRaagaContext, BDSP_RaagaContext);
    BDBG_OBJECT_ASSERT(pRaagaTask, BDSP_RaagaTask);

    /* Mark task as in use and save settings */
    BLST_S_REMOVE_HEAD(&pRaagaContext->freeTaskList, node);
    BKNI_AcquireMutex(pDevice->captureMutex);
    BLST_S_INSERT_HEAD(&pRaagaContext->allocTaskList, pRaagaTask, node);
    pRaagaTask->allocated = true;
    BKNI_Memcpy(&pRaagaTask->settings, pSettings, sizeof(*pSettings));
    BKNI_Memset(&pRaagaTask->audioInterruptHandlers, 0, sizeof(pRaagaTask->audioInterruptHandlers));

    pRaagaTask->isStopped = true;
    pRaagaTask->lastEventType= 0xFFFF;
    pRaagaTask->settings = *pSettings;
    pRaagaTask->commandCounter =0;
    pRaagaTask->paused=false;
    pRaagaTask->frozen=false;
    pRaagaTask->decLocked=false;

    BKNI_ReleaseMutex(pDevice->captureMutex);
    BDBG_LEAVE(BDSP_Raaga_P_InitParams_CreateTask);
    return err;
}


static BERR_Code   BDSP_Raaga_P_InitParams_StartTask(
    void *pContextHandle,
    void *pTaskHandle,
    const BDSP_TaskStartSettings *pStartSettings
    )
{
    BERR_Code   err=BERR_SUCCESS;
    BDSP_RaagaContext *pRaagaContext = (BDSP_RaagaContext *)pContextHandle;
    BDSP_RaagaTask *pRaagaTask = (BDSP_RaagaTask *)pTaskHandle;
    BDSP_Raaga  *pDevice= pRaagaContext->pDevice;
    unsigned taskId;
    BDSP_RaagaTask *pMasterRaagaTask;

    BDBG_OBJECT_ASSERT(pRaagaContext, BDSP_RaagaContext);
    BDBG_OBJECT_ASSERT(pRaagaTask, BDSP_RaagaTask);

    BKNI_Memcpy(&pRaagaTask->startSettings, pStartSettings, sizeof(*pStartSettings));

    pRaagaTask->masterTaskId = BDSP_RAAGA_P_INVALID_TASK_ID;
    pRaagaTask->schedulingMode = pStartSettings->schedulingMode;

    if ( pStartSettings->schedulingMode != BDSP_TaskSchedulingMode_eSlave && pStartSettings->masterTask != NULL )
    {
        BDBG_ERR(("master task handle should be set only for Slave scheduling mode"));
        err = BERR_TRACE(BERR_INVALID_PARAMETER);
        goto end;
    }

    if ((pStartSettings->schedulingMode== BDSP_TaskSchedulingMode_eSlave) && (pStartSettings->masterTask !=NULL))
    {
        pMasterRaagaTask = (BDSP_RaagaTask *)(pStartSettings->masterTask->pTaskHandle);
        BDBG_OBJECT_ASSERT(pMasterRaagaTask, BDSP_RaagaTask);
        pRaagaTask->masterTaskId = pMasterRaagaTask->taskId;
        pRaagaTask->pFeedbackBuffer = pMasterRaagaTask->pFeedbackBuffer;
    }
    else if (pStartSettings->schedulingMode == BDSP_TaskSchedulingMode_eMaster)
    {
        pRaagaTask->masterTaskId = BDSP_RAAGA_P_INVALID_TASK_ID;
        /*feedback buffer allocated during create task time*/
    }


    BKNI_AcquireMutex(pDevice->taskDetails.taskIdMutex);
    for (taskId = 0 ; taskId < BDSP_RAAGA_MAX_FW_TASK_PER_DSP; taskId++)
    {
        if (pDevice->taskDetails.taskId[pRaagaTask->settings.dspIndex][taskId] == true)
        {
            pDevice->taskDetails.taskId[pRaagaTask->settings.dspIndex][taskId] = false;
            break;
        }
    }

    if (taskId >=BDSP_RAAGA_MAX_FW_TASK_PER_DSP)
    {
        BKNI_ReleaseMutex(pDevice->taskDetails.taskIdMutex);
        BDBG_ERR(("Unable to find free Task Instance!"));
        err = BERR_TRACE(BERR_OUT_OF_DEVICE_MEMORY);
        goto end;
    }

    pRaagaTask->taskId  = taskId + BDSP_RAAGA_TASK_ID_START_OFFSET;

    pDevice->taskDetails.pRaagaTask[pRaagaTask->settings.dspIndex][taskId]  = pRaagaTask;

    BKNI_ReleaseMutex(pDevice->taskDetails.taskIdMutex);

    err = BKNI_CreateEvent(&(pRaagaTask->hEvent));
    if (BERR_SUCCESS != err)
    {
        BDBG_ERR(("BDSP_Raaga_P_InitParams_StartTask: Unable to create event"));
        err = BERR_TRACE(err);
        goto end;
    }

    BKNI_ResetEvent(pRaagaTask->hEvent);

end:
    return err;
}

static BERR_Code   BDSP_Raaga_P_FreeAndInvalidateTask(
    void *pTaskHandle
    )
{
    BERR_Code   err=BERR_SUCCESS;
    BDSP_RaagaTask *pRaagaTask = (BDSP_RaagaTask *)pTaskHandle;
    BDSP_RaagaContext *pRaagaContext = pRaagaTask->pContext;
    BDSP_Raaga  *pDevice= pRaagaContext->pDevice;

    BDBG_OBJECT_ASSERT(pRaagaTask, BDSP_RaagaTask);

    /* Mark task as free */
    BKNI_Memset(&pRaagaTask->audioInterruptHandlers, 0, sizeof(pRaagaTask->audioInterruptHandlers));
    BKNI_AcquireMutex(pDevice->captureMutex);
    BLST_S_REMOVE(&pRaagaTask->pContext->allocTaskList, pRaagaTask, BDSP_RaagaTask, node);
    BKNI_ReleaseMutex(pDevice->captureMutex);
    BLST_S_INSERT_HEAD(&pRaagaTask->pContext->freeTaskList, pRaagaTask, node);
    pRaagaTask->allocated = false;

    return err;
}

static BERR_Code BDSP_Raaga_P_FindSlaveTaskSchedulingBuffer(
            const BDSP_TaskStartSettings *pStartSettings,
            raaga_dramaddr   *pui32DramSchedulingBuffCfgAddr,
            BDSP_AF_P_BufferType    *pBufferType)
{
    BERR_Code   err = BERR_SUCCESS;
    unsigned i;

    *pBufferType = BDSP_AF_P_BufferType_eDRAM;
    *pui32DramSchedulingBuffCfgAddr = 0;

    BDSP_STAGE_TRAVERSE_LOOP_BEGIN((BDSP_RaagaStage *)pStartSettings->primaryStage->pStageHandle, pStageIterator)
    BSTD_UNUSED(macroStId);
    BSTD_UNUSED(macroBrId);
    {
        for (i = 0; i < pStageIterator->totalOutputs; i++)
        {
            if (pStageIterator->sStageOutput[i].eConnectionType == BDSP_ConnectionType_eInterTaskBuffer)
            {
                BDSP_P_InterTaskBuffer *pRaagaInterTaskBuffer;
                pRaagaInterTaskBuffer = (BDSP_P_InterTaskBuffer *)pStageIterator->sStageOutput[i].connectionDetails.interTask.hInterTask->pInterTaskBufferHandle;

                BDSP_MEM_P_ConvertAddressToOffset(pStageIterator->pContext->pDevice->memHandle,
                        pRaagaInterTaskBuffer->pIoBufferDesc,
                        pui32DramSchedulingBuffCfgAddr);
                break;
            }
        }
    }
    BDSP_STAGE_TRAVERSE_LOOP_END(pStageIterator)

    if (*pui32DramSchedulingBuffCfgAddr == 0)
    {
        err = BERR_TRACE(BERR_INVALID_PARAMETER);
    }

    return err;
}

static BERR_Code BDSP_Raaga_P_FindSchedulingBuffer(
    const BDSP_TaskCreateSettings *pSettings,
    const BDSP_TaskStartSettings *pStartSettings,
    BDSP_CIT_P_FwStgSrcDstType    *eSchedulingBufferType,
    unsigned *pBufferId,
    BDSP_AF_P_sDRAM_CIRCULAR_BUFFER    *pBufferPtr,
    unsigned *pDelay,
    BDSP_AF_P_FmmDstFsRate *pDstRate,
    unsigned *pSchedulingBufferthreshold
    )
{
    unsigned compressed=(unsigned)-1, compressedDelay=0;
    BDSP_AF_P_FmmDstFsRate compressedRate=BDSP_AF_P_FmmDstFsRate_eBaseRate;
    /* Holds the list of stage handles that have not been examined */
    uint32_t i, ui32Buff0AddrStart, ui32Buff2BuffOffset;
    BDSP_RaagaQueue* pRaagaQueue;
    unsigned int uiSchedulingBufferThreshold = (BDSP_CIT_P_STANDARD_BUFFER_THRESHOLD + BDSP_CIT_P_MAXIMUM_RESIDUAL_COLLECTION);

    BDBG_ASSERT(NULL != pSettings);
    BDBG_ASSERT(NULL != pBufferId);
    BDBG_ASSERT(NULL != pDelay);
    BDBG_ASSERT(NULL != pDstRate);
    *pBufferId = 0;
    *pDelay = 0;
    *pDstRate = BDSP_AF_P_FmmDstFsRate_eBaseRate;
    *pSchedulingBufferthreshold = (BDSP_CIT_P_STANDARD_BUFFER_THRESHOLD + BDSP_CIT_P_MAXIMUM_RESIDUAL_COLLECTION);

    BDSP_STAGE_TRAVERSE_LOOP_BEGIN((BDSP_RaagaStage *)pStartSettings->primaryStage->pStageHandle, pStageIterator)
    BSTD_UNUSED(macroStId);
    BSTD_UNUSED(macroBrId);
    {
        /* Check if the current stage has any PCM/Compressed FMM outputs
            if Yes, Found scheduling buffer -> Break */
        for (i = 0; i < BDSP_AF_P_MAX_OP_FORKS; i++)
        {
            if (pStartSettings->realtimeMode == BDSP_TaskRealtimeMode_eNonRealTime)
            {
                if (pStageIterator->sStageOutput[i].eConnectionType == BDSP_ConnectionType_eRaveBuffer &&
                    pStageIterator->sStageOutput[i].eNodeValid == BDSP_AF_P_eValid)
                {
                    *eSchedulingBufferType = BDSP_CIT_P_FwStgSrcDstType_eRaveBuf;
                    pBufferPtr->ui32BaseAddr = BCHP_PHYSICAL_OFFSET + pStageIterator->sStageOutput[i].connectionDetails.rave.pContextMap->CDB_Base;
                    pBufferPtr->ui32EndAddr = BCHP_PHYSICAL_OFFSET + pStageIterator->sStageOutput[i].connectionDetails.rave.pContextMap->CDB_End;
                    pBufferPtr->ui32ReadAddr = BCHP_PHYSICAL_OFFSET + pStageIterator->sStageOutput[i].connectionDetails.rave.pContextMap->CDB_Read;
                    pBufferPtr->ui32WriteAddr = BCHP_PHYSICAL_OFFSET + pStageIterator->sStageOutput[i].connectionDetails.rave.pContextMap->CDB_Valid;
                    pBufferPtr->ui32WrapAddr = BCHP_PHYSICAL_OFFSET + pStageIterator->sStageOutput[i].connectionDetails.rave.pContextMap->CDB_Wrap;
                    *pDelay = 0;
                    return BERR_SUCCESS;
                }
                else if(pStageIterator->sStageOutput[i].eConnectionType == BDSP_ConnectionType_eRDBBuffer &&
                        pStageIterator->sStageOutput[i].eNodeValid == BDSP_AF_P_eValid)
                {
                    pRaagaQueue = (BDSP_RaagaQueue *)pStageIterator->sStageOutput[i].connectionDetails.rdb.pQHandle;
                    *eSchedulingBufferType = BDSP_CIT_P_FwStgSrcDstType_eRDB;
                            pBufferPtr->ui32BaseAddr = BDSP_RAAGA_REGSET_ADDR_FOR_DSP( pRaagaQueue->FIFOdata[0]->ui32BaseAddr );
                            pBufferPtr->ui32EndAddr = BDSP_RAAGA_REGSET_ADDR_FOR_DSP( pRaagaQueue->FIFOdata[0]->ui32EndAddr );
                            pBufferPtr->ui32ReadAddr = BDSP_RAAGA_REGSET_ADDR_FOR_DSP( pRaagaQueue->FIFOdata[0]->ui32ReadAddr );
                            pBufferPtr->ui32WriteAddr = BDSP_RAAGA_REGSET_ADDR_FOR_DSP( pRaagaQueue->FIFOdata[0]->ui32WriteAddr );
                            pBufferPtr->ui32WrapAddr = BDSP_RAAGA_REGSET_ADDR_FOR_DSP( pRaagaQueue->FIFOdata[0]->ui32EndAddr );
                    *pDelay = 0;
                    return BERR_SUCCESS;
                }
            }
            else if(pStartSettings->realtimeMode == BDSP_TaskRealtimeMode_eOnDemand)
                {
                    if(pStageIterator->sStageOutput[i].eConnectionType == BDSP_ConnectionType_eRDBBuffer &&
                       pStageIterator->sStageOutput[i].eNodeValid == BDSP_AF_P_eValid && pStageIterator->algorithm == BDSP_Algorithm_eOutputFormatter)
                        {
                            pRaagaQueue = (BDSP_RaagaQueue *)pStageIterator->sStageOutput[i].connectionDetails.rdb.pQHandle;
                            *eSchedulingBufferType = BDSP_CIT_P_FwStgSrcDstType_eRDBPool;
                            pBufferPtr->ui32BaseAddr = BDSP_RAAGA_REGSET_ADDR_FOR_DSP( pRaagaQueue->FIFOdata[0]->ui32BaseAddr );
                            pBufferPtr->ui32EndAddr = BDSP_RAAGA_REGSET_ADDR_FOR_DSP( pRaagaQueue->FIFOdata[0]->ui32EndAddr );
                            pBufferPtr->ui32ReadAddr = BDSP_RAAGA_REGSET_ADDR_FOR_DSP( pRaagaQueue->FIFOdata[0]->ui32ReadAddr );
                            pBufferPtr->ui32WriteAddr = BDSP_RAAGA_REGSET_ADDR_FOR_DSP( pRaagaQueue->FIFOdata[0]->ui32WriteAddr );
                            pBufferPtr->ui32WrapAddr = BDSP_RAAGA_REGSET_ADDR_FOR_DSP( pRaagaQueue->FIFOdata[0]->ui32EndAddr );
                            *pDelay = 0;
                            BDBG_MSG(("sched,readptr = %x,writeptr = %x",pBufferPtr->ui32ReadAddr,pBufferPtr->ui32WriteAddr));
                            return BERR_SUCCESS;
                        }
                }
            else
            {
                if (pStageIterator->sStageOutput[i].eConnectionType == BDSP_ConnectionType_eFmmBuffer &&
                    pStageIterator->sStageOutput[i].eNodeValid == BDSP_AF_P_eValid)
                {
#ifdef BCHP_AUD_FMM_BF_CTRL_RINGBUF_0_RDADDR
                    ui32Buff0AddrStart  = BCHP_AUD_FMM_BF_CTRL_RINGBUF_0_RDADDR;
                    ui32Buff2BuffOffset = BCHP_AUD_FMM_BF_CTRL_RINGBUF_1_RDADDR -
                                                BCHP_AUD_FMM_BF_CTRL_RINGBUF_0_RDADDR;
#else
                    ui32Buff0AddrStart  = BCHP_AUD_FMM_BF_CTRL_SOURCECH_RINGBUF_0_RDADDR;
                    ui32Buff2BuffOffset = BCHP_AUD_FMM_BF_CTRL_SOURCECH_RINGBUF_1_RDADDR -
                                                BCHP_AUD_FMM_BF_CTRL_SOURCECH_RINGBUF_0_RDADDR;
#endif
                    if ( (pStageIterator->eStageOpBuffDataType[i] == BDSP_AF_P_DistinctOpType_eCompressed)
                         || (pStageIterator->eStageOpBuffDataType[i] == BDSP_AF_P_DistinctOpType_eCompressed4x)
                         || (pStageIterator->eStageOpBuffDataType[i] == BDSP_AF_P_DistinctOpType_eCompressedHBR))
                    {
                        if ( compressed == (unsigned)-1 )
                        {
                            compressed = (pStageIterator->sStageOutput[i].connectionDetails.fmm.descriptor.buffers[0].read - ui32Buff0AddrStart)/(ui32Buff2BuffOffset);
                            compressedDelay = pStageIterator->sStageOutput[i].connectionDetails.fmm.descriptor.delay;

                            /* Changes for setting up the eFmmDstFsRate compressed passthru / BTSC Encoder */
                            if (pStageIterator->eStageOpBuffDataType[i] == BDSP_AF_P_DistinctOpType_eCompressedHBR)
                            {
                                compressedRate = BDSP_AF_P_FmmDstFsRate_e16xBaseRate;
                                if(pStageIterator->algorithm == BDSP_Algorithm_eMlpPassthrough)
                                {
                                    /* Note: MLP Passthru uses a different logic for threshold and hence no need to add residual collection. The calculation is explained in the macro defination*/
                                    uiSchedulingBufferThreshold = BDSP_CIT_P_COMPRESSED16X_MLP_BUFFER_THRESHOLD;
                                }
                                else
                                {
                                    uiSchedulingBufferThreshold = (BDSP_CIT_P_COMPRESSED16X_BUFFER_THRESHOLD + BDSP_CIT_P_MAXIMUM_RESIDUAL_COLLECTION);
                                }
                            }
                            else if (pStageIterator->eStageOpBuffDataType[i] == BDSP_AF_P_DistinctOpType_eCompressed4x)
                            {
                                compressedRate = BDSP_AF_P_FmmDstFsRate_e4xBaseRate;
                                uiSchedulingBufferThreshold = (BDSP_CIT_P_COMPRESSED4X_BUFFER_THRESHOLD + BDSP_CIT_P_MAXIMUM_RESIDUAL_COLLECTION);
                            }
                            else
                            {
                                compressedRate = BDSP_AF_P_FmmDstFsRate_eBaseRate;
                                uiSchedulingBufferThreshold = (BDSP_CIT_P_STANDARD_BUFFER_THRESHOLD + BDSP_CIT_P_MAXIMUM_RESIDUAL_COLLECTION);
                            }

                            if ((pStageIterator->eStageOpBuffDataType[i] == BDSP_AF_P_DistinctOpType_eCompressed)
                                && (pStageIterator->algorithm == BDSP_Algorithm_eBtscEncoder))
                            {
                                compressedRate = BDSP_AF_P_FmmDstFsRate_e4xBaseRate;
                                uiSchedulingBufferThreshold = (BDSP_CIT_P_STANDARD_BUFFER_THRESHOLD + BDSP_CIT_P_MAXIMUM_RESIDUAL_COLLECTION);
                            }
                        }
                        BDBG_MSG(("Scheduling buffer associated with %s(%d)",BDSP_Raaga_P_LookupAlgorithmInfo(pStageIterator->algorithm)->pName,pStageIterator->algorithm ));

                    }
                    else
                    {
                        *pBufferId = (pStageIterator->sStageOutput[i].connectionDetails.fmm.descriptor.buffers[0].read - ui32Buff0AddrStart)/(ui32Buff2BuffOffset);
                        *pDelay = pStageIterator->sStageOutput[i].connectionDetails.fmm.descriptor.delay;
                        *pDstRate = BDSP_AF_P_FmmDstFsRate_eBaseRate;
                        *eSchedulingBufferType = BDSP_CIT_P_FwStgSrcDstType_eFMMBuf;
                        *pSchedulingBufferthreshold = (BDSP_CIT_P_STANDARD_BUFFER_THRESHOLD + BDSP_CIT_P_MAXIMUM_RESIDUAL_COLLECTION);

                        BDBG_MSG(("Scheduling buffer: associated with %s(%d)",BDSP_Raaga_P_LookupAlgorithmInfo(pStageIterator->algorithm)->pName,pStageIterator->algorithm ));
                        BDBG_MSG(("Scheduling buffer: *pBufferId=%d, *pDelay=%d, ",*pBufferId,*pDelay));
                        return BERR_SUCCESS;
                    }
                }
            }
        }
    }
    BDSP_STAGE_TRAVERSE_LOOP_END(pStageIterator)

    /* If we reach here, return success if we found a compressed buffer */
    if ( compressed != (unsigned)-1 )
    {
        *pBufferId = compressed;
        *pDelay = compressedDelay;
        *pDstRate = compressedRate;
        *eSchedulingBufferType = BDSP_CIT_P_FwStgSrcDstType_eFMMBuf;
        *pSchedulingBufferthreshold = uiSchedulingBufferThreshold ;
        BDBG_MSG(("Find Sch buffer,*pBufferId=%d, *pDelay=%d, *pDstRate=%d",*pBufferId,*pDelay, *pDstRate));

        return BERR_SUCCESS;
    }
    /* Nothing to schedule off */
    return BERR_TRACE(BERR_INVALID_PARAMETER);
}


BERR_Code BDSP_Raaga_P_CalcThresholdZeroFillTimeAudOffset_isrsafe(
                    BDSP_CTB_Input                  *pCtbInput,
                    void                            *pStageHandle,
                    BDSP_CTB_Output                 *psCTB_OutputStructure
                )
{
    BDSP_RaagaStage *pRaagaStage = (BDSP_RaagaStage *)pStageHandle;
    BERR_Code   err=BERR_SUCCESS;
    BDSP_AudioTaskDelayMode eDelayMode;

    BDBG_ENTER(BDSP_Raaga_P_CalcThresholdZeroFillTimeAudOffset_isrsafe);
    BDBG_OBJECT_ASSERT (pRaagaStage, BDSP_RaagaStage);

    eDelayMode = pCtbInput->audioTaskDelayMode;
    psCTB_OutputStructure->ui32Threshold = (BDSP_CIT_P_MINIMUM_ALGO_THRESHOLD + BDSP_CIT_P_MAXIMUM_RESIDUAL_COLLECTION);
    if (pRaagaStage->algorithm == BDSP_Algorithm_eMlpPassthrough)
    {
        psCTB_OutputStructure->ui32Threshold = BDSP_CIT_P_INDEPENDENT_MAT_THRESHOLD;
        BDBG_MSG(("\n\n**** Increasing threshold value to increase zero fill ... Old Threshold = %d, New Threshold = %d******\n\n",\
                (BDSP_CIT_P_MINIMUM_ALGO_THRESHOLD + BDSP_CIT_P_MAXIMUM_RESIDUAL_COLLECTION), BDSP_CIT_P_INDEPENDENT_MAT_THRESHOLD));
    }
    if(eDelayMode == BDSP_AudioTaskDelayMode_eDefault)
    {
        psCTB_OutputStructure->ui32BlockTime = 42;
        psCTB_OutputStructure->ui32AudOffset = 128;
    }
    else if(eDelayMode == BDSP_AudioTaskDelayMode_WD_eLow )
    {
        /*Original Values from earlier times :
        psCTB_OutputStructure->ui32BlockTime = 19;
        psCTB_OutputStructure->ui32AudOffset = psCTB_OutputStructure->ui32BlockTime * 2;
        */
        /*SW7445-2474 : New Values have to be used for AC3 hdmi input since we have to account for input buffer
        fill time (which is also frame time):
        48 ms - i/p buffer fill time
        5 ms - Decode time (50 mhz for 1 sec ac3 decoding when clock frequency is 550 Mhz. So  we need 1/10th of 1sec for 1 sec audio , therefore for one frame it will be 48ms/10 (5ms approx).
        10ms- o/p buffering (because of decode time and other possible firmware delays)
        2 ms- FMM jitter
        Total AUD offset = 65ms (48+5+10+2=65);
        Zero fill Buffer =10ms i.e. Block time is 5ms.*/
        /*Amongst other things this is a special state where
        1. There is only single task to be considered.
        2. No Post processing has been considered.
        3. No Compressed mode out -(transcoding to DD considered)*/
        psCTB_OutputStructure->ui32BlockTime = 5;
        psCTB_OutputStructure->ui32AudOffset = 65;
    }
    else if(eDelayMode == BDSP_AudioTaskDelayMode_WD_eLowest )
    {
        switch(pRaagaStage->algorithm)
        {
            case BDSP_Algorithm_eAc3Decode:
                psCTB_OutputStructure->ui32BlockTime = 19;
                psCTB_OutputStructure->ui32AudOffset = psCTB_OutputStructure->ui32BlockTime * 2;
                break;

            case BDSP_Algorithm_eAacAdtsDecode:
            case BDSP_Algorithm_eAacLoasDecode:
            case BDSP_Algorithm_eDolbyPulseAdtsDecode:
            case BDSP_Algorithm_eDolbyPulseLoasDecode:
                psCTB_OutputStructure->ui32BlockTime = 14;
                psCTB_OutputStructure->ui32AudOffset = psCTB_OutputStructure->ui32BlockTime * 2;
                break;

            case BDSP_Algorithm_eLpcm1394Decode:
                psCTB_OutputStructure->ui32BlockTime = 7;
                psCTB_OutputStructure->ui32AudOffset = psCTB_OutputStructure->ui32BlockTime * 2;
                break;

            default:
                BDBG_ERR((" Algo format ( %s )is not supported in Low Delay Mode",(BDSP_Raaga_P_LookupAlgorithmInfo(pRaagaStage->algorithm))->pName ));
                err=BERR_NOT_SUPPORTED;
                psCTB_OutputStructure->ui32BlockTime = 42;
                psCTB_OutputStructure->ui32AudOffset = 128;
                break;
        }
    }

    if( pCtbInput->realtimeMode == BDSP_TaskRealtimeMode_eNonRealTime )
    {
        psCTB_OutputStructure->ui32BlockTime = 0;
        psCTB_OutputStructure->ui32AudOffset = 0;
    }

    BDBG_LEAVE(BDSP_Raaga_P_CalcThresholdZeroFillTimeAudOffset_isrsafe);
    return err;

}

BERR_Code BDSP_Raaga_P_CheckConfigLimitations(BDSP_AudioTaskDelayMode eDelayMode,
                                                void *pTaskHandle)
{
    BDSP_RaagaTask *pRaagaTask = (BDSP_RaagaTask *)pTaskHandle;
    BDSP_CIT_P_Output   *psCitOp = &(pRaagaTask->citOutput);
    BDSP_RaagaStage *pPrimaryHandle = (BDSP_RaagaStage *)pRaagaTask->startSettings.primaryStage->pStageHandle;
    BERR_Code err=BERR_SUCCESS;

    if((eDelayMode == BDSP_AudioTaskDelayMode_WD_eLow )||
        (eDelayMode == BDSP_AudioTaskDelayMode_WD_eLowest ))
        {
            if(psCitOp->sCit.sGlobalTaskConfig.ui32NumberOfNodesInTask > 2)
            {
                BDBG_ERR(("In the Wifi Display low/least delay mode only single decode context is supported"));
                BDBG_ERR(("Disable any postprocess or passthru enabled apart from a single main decode "));
                err = BERR_NOT_SUPPORTED;
            }

            if(!((pPrimaryHandle->algorithm == BDSP_Algorithm_eAc3Decode)||\
                (pPrimaryHandle->algorithm == BDSP_Algorithm_eAacAdtsDecode) ||\
                (pPrimaryHandle->algorithm == BDSP_Algorithm_eAacLoasDecode ) ||\
                (pPrimaryHandle->algorithm == BDSP_Algorithm_eDolbyPulseAdtsDecode ) ||\
                (pPrimaryHandle->algorithm == BDSP_Algorithm_eDolbyPulseLoasDecode ) ||\
                (pPrimaryHandle->algorithm == BDSP_Algorithm_eLpcm1394Decode )))
            {
                BDBG_ERR((" Algo format ( %s )is not supported in Low Delay Mode",(BDSP_Raaga_P_LookupAlgorithmInfo(pPrimaryHandle->algorithm))->pName ));
                err = BERR_NOT_SUPPORTED;
            }
        }

    return err;
}

/***********************************************************************
Name        :   BDSP_Raaga_P_StartTask

Type        :   PI Interface

Input       :   pTaskHandle     -   Handle of the Task which needs to be Stopped.
                pStartSettings      -   Settings to be used for Starting the Task.

Return      :   Error Code to return SUCCESS or FAILURE

Functionality   :   Following are the operations performed.
        1)  Reset all the MSG Queues to Base Address and RRQ to full buffer capacity, done to take care of Watchdog recovery.
        2)  Initialse the Start settings of Task with the parameters provided by the PI as part of "BDSP_Raaga_P_InitParams_StartTask"
        3)  Fill the Master task and scheduling mode the task as part of "BDSP_Raaga_P_InitParams_StartTask"
        4)  Download the FW at start time if it is not preloaded.
        5)  Fill the Node Configuration and Global task configuration as part of CIT network and copy it to DRAM.
            Incase of Audio only, copy the network into CIT Buffer and Spare CIT Buffer. Spare will be used for CIT Reconfig.
        6)  Initialize the interframe buffers for all the stages in the Context
        7)  Calculate the Audio Zero fill time for only Audio Context.
        8)  Send the VOM change command.
        9)  Fill up start task parameters like Scheduling details, Gate status, etc depending on the settings provided.
            Note: The details will vary according to the Context type.
        10) Send the Start Task Command to the FW and wait for the acknowledgement.
***********************************************************************/

BERR_Code BDSP_Raaga_P_StartTask(
    void *pTaskHandle,
    BDSP_TaskStartSettings *pStartSettings    /* [out] */
    )
{
    /*A major part of create task should come in here*/
    BDSP_RaagaTask *pRaagaTask = (BDSP_RaagaTask *)pTaskHandle;
    BDSP_Raaga_P_Command sCommand;
    BDSP_Raaga_P_Response sRsp;
    BDSP_RaagaContext *pRaagaContext = (BDSP_RaagaContext *)pRaagaTask->pContext;
    BDSP_Raaga  *pDevice= pRaagaContext->pDevice;
    BDSP_RaagaStage *pRaagaPrimaryStage;
    BDSP_Raaga_P_TaskParamInfo *pTaskParams = NULL;
    BDSP_Raaga_P_MsgType      eMsgType;
    unsigned ui32RbufOffset, uiSchedulingBufId, uiSchedulingBufDelay;
    raaga_dramaddr    ui32PhysAddr, i = 0;
    unsigned int    uiSchedulingBufferThreshold = 0;
    unsigned int    ui32BlockTime = 0;
    unsigned        uiOffset = 0;
    uint32_t        ui32RegOffset = 0;
    unsigned        dspIndex=0;

    BERR_Code   err=BERR_SUCCESS;
    BDSP_AF_P_FmmDstFsRate schedulingBufferRate=BDSP_AF_P_FmmDstFsRate_eBaseRate;
    BDSP_CTB_Input ctbInput;

    BDBG_ENTER(BDSP_Raaga_P_StartTask);

    BDBG_OBJECT_ASSERT(pRaagaTask, BDSP_RaagaTask);
    BDBG_OBJECT_ASSERT(pRaagaContext, BDSP_RaagaContext);

    BKNI_Memset(&sCommand,0,sizeof(sCommand));
    BKNI_Memset(&sRsp,0,sizeof(sRsp));

    BDBG_MSG(("Start task: DSP %d",pRaagaTask->settings.dspIndex));

    dspIndex = pRaagaTask->settings.dspIndex;
    pRaagaTask->startSettings = *pStartSettings;

    pRaagaPrimaryStage = (BDSP_RaagaStage *)pStartSettings->primaryStage->pStageHandle;

    /* RESETTING THE QUEUE ADDRESS  for WATCHDOG RECOVER - START */
    /* This is required for successful Watchdog recovery where-in we need to reset the Read/Write pointers of the
         MSG Queues created at the time of Create Task to Base pointer. */
    uiOffset = pDevice->dspOffset[pRaagaTask->settings.dspIndex];

    if( !pDevice->taskDetails.numActiveTasks[dspIndex] )
    {
        BDSP_Raaga_P_SetDspClkRate( (void *)pDevice, pDevice->dpmInfo.defaultDspClkRate[dspIndex], dspIndex );
    }
    pDevice->taskDetails.numActiveTasks[dspIndex]++;


    err = BDSP_Raaga_P_InitMsgQueue(&(pRaagaTask->taskMemGrants.sTaskQueue.sTaskSyncQueue),
        pDevice->memHandle, pDevice->regHandle, uiOffset, &(pRaagaTask->hSyncMsgQueue));
    if (BERR_SUCCESS != err)
    {
        BDBG_ERR(("BDSP_Raaga_P_StartTask: Sync Queue Init failed!"));
        err = BERR_TRACE(err);
    }

    err = BDSP_Raaga_P_InitMsgQueue(&(pRaagaTask->taskMemGrants.sTaskQueue.sTaskAsyncQueue),
        pDevice->memHandle, pDevice->regHandle, uiOffset, &(pRaagaTask->hAsyncMsgQueue));
    if (BERR_SUCCESS != err)
    {
        BDBG_ERR(("BDSP_Raaga_P_StartTask: ASync Queue Init failed!"));
        err = BERR_TRACE(err);
    }
    if (pRaagaContext->settings.contextType == BDSP_ContextType_eVideo)
    {
        /* Picture delivery queue */
        err = BDSP_Raaga_P_InitMsgQueue(&(pRaagaTask->taskMemGrants.sTaskQueue.sPDQueue), pDevice->memHandle,
            pDevice->regHandle, uiOffset,&(pRaagaTask->hPDQueue));
        if (BERR_SUCCESS != err)
        {
            BDBG_ERR(("BDSP_Raaga_P_StartTask: Picture delivery queue Init failed!"));
            err = BERR_TRACE(err);
        }

        /*Picture release queue*/
        err = BDSP_Raaga_P_InitMsgQueue(&(pRaagaTask->taskMemGrants.sTaskQueue.sPRQueue), pDevice->memHandle,
            pDevice->regHandle, uiOffset,&(pRaagaTask->hPRQueue));
        if (BERR_SUCCESS != err)
        {
            BDBG_ERR(("BDSP_Raaga_P_StartTask: Picture release queue Init failed!"));
            err = BERR_TRACE(err);
        }

        /*Display  queue*/
        err = BDSP_Raaga_P_InitMsgQueue(&(pRaagaTask->taskMemGrants.sTaskQueue.sDSQueue), pDevice->memHandle,
            pDevice->regHandle, uiOffset,&(pRaagaTask->hDSQueue));
        if (BERR_SUCCESS != err)
        {
            BDBG_ERR(("BDSP_Raaga_P_StartTask: display queue Init failed!"));
            err = BERR_TRACE(err);
        }
    }
    if (pRaagaContext->settings.contextType == BDSP_ContextType_eVideoEncode)
    {
        err = BDSP_Raaga_P_InitRdbQueue(&(pRaagaTask->taskMemGrants.sTaskQueue.sRDQueue), pDevice->memHandle,
            pDevice->regHandle, uiOffset,&(pRaagaTask->hRDQueue));
        if (BERR_SUCCESS != err)
        {
            BDBG_ERR(("BDSP_Raaga_P_StartTask: Raw Picture delivery queue Init failed!"));
            err = BERR_TRACE(err);
        }

        /* Raw Picture release queue*/
        err = BDSP_Raaga_P_InitMsgQueue(&(pRaagaTask->taskMemGrants.sTaskQueue.sRRQueue), pDevice->memHandle,
            pDevice->regHandle, uiOffset,&(pRaagaTask->hRRQueue));
        if (BERR_SUCCESS != err)
        {
            BDBG_ERR(("BDSP_Raaga_P_StartTask: Raw Picture release queue Init failed!"));
            err = BERR_TRACE(err);
        }

        /* RRQ should start with full buffer capacity */
        ui32RegOffset = BCHP_RAAGA_DSP_FW_CFG_FIFO_1_BASE_ADDR - \
                        BCHP_RAAGA_DSP_FW_CFG_FIFO_0_BASE_ADDR;
        BDSP_Write32(pRaagaTask->hRRQueue->hRegister,
                BCHP_RAAGA_DSP_FW_CFG_FIFO_0_BASE_ADDR + (ui32RegOffset * pRaagaTask->hRRQueue->i32FifoId) + BDSP_RAAGA_P_FIFO_WRITE_OFFSET + uiOffset,
                pRaagaTask->hRRQueue->ui32BaseAddr + (BDSP_FWMAX_VIDEO_BUFF_AVAIL*4));

        /* CC data delivery queue*/
        err = BDSP_Raaga_P_InitMsgQueue(&(pRaagaTask->taskMemGrants.sTaskQueue.sCCDQueue), pDevice->memHandle,
            pDevice->regHandle, uiOffset,&(pRaagaTask->hCCDQueue));
        if (BERR_SUCCESS != err)
        {
            BDBG_ERR(("BDSP_Raaga_P_StartTask: CCD queue Init failed!"));
            err = BERR_TRACE(err);
        }
    }
    /* RESETTING THE QUEUE ADDRESS  for WATCHDOG RECOVER - END */

    BDSP_Raaga_P_InitParams_StartTask((void *)pRaagaContext, (void *)pRaagaTask, pStartSettings);

    /* Populate the branch and stage id */
    BDBG_ASSERT(NULL != pRaagaPrimaryStage);
    BDSP_STAGE_TRAVERSE_LOOP_V1_BEGIN(pRaagaPrimaryStage, pStageIterator, branchId, stageId)
    BSTD_UNUSED(branchId);
    BSTD_UNUSED(stageId);
    {
        pStageIterator->ui32BranchId = branchId;
        pStageIterator->ui32StageId = stageId;
    }
    BDSP_STAGE_TRAVERSE_LOOP_END(pStageIterator)

    /*In new CIT:*/
    /*Keep this Download Time FWExec during Start time, as only then all info related to stages of a Task will be known
    Previously it was done based on the Task create settings, where the branch info was known, now it will be done based on the Stage handles.*/
    if (false == pDevice->memInfo.sDwnldMemInfo.IsImagePreLoaded)
    {
        /* Download the firmware binaries required by the complete network */
        err = BDSP_Raaga_P_DownloadStartTimeFWExec((void*)pRaagaContext, (void*)pStartSettings->primaryStage->pStageHandle);
        if ( BERR_SUCCESS !=err )
        {
            err = BERR_TRACE(BDSP_ERR_DOWNLOAD_FAILED);
            goto err_download_fw;
        }
    }

/* In the new CI_REFAC, the following section of code comes from the Task Create*/
    /* Initialize to eDisable by default */
    sCommand.uCommand.sStartTask.eOpenGateAtStart = BDSP_AF_P_eDisable;


    if (pRaagaContext->settings.contextType == BDSP_ContextType_eAudio)
    {
        {
        BDSP_RaagaCapture *pRaagaCapture;
        int j;

        /* Print the initialized captur info structure */
        BDBG_MSG(("CAPTURE BUFFER INFORMATION (%d)", pRaagaTask->taskId));
        BDBG_MSG(("--------------------------"));

        BKNI_AcquireMutex(pDevice->captureMutex);
        BDSP_STAGE_TRAVERSE_LOOP_BEGIN((BDSP_RaagaStage *)pStartSettings->primaryStage->pStageHandle, pStageIterator)
        BSTD_UNUSED(macroStId);
        BSTD_UNUSED(macroBrId);
        {
            for ( pRaagaCapture = BLST_S_FIRST(&pStageIterator->captureList);
                pRaagaCapture != NULL;
                pRaagaCapture = BLST_S_NEXT(pRaagaCapture, node) )
            {

                BDBG_ERR(("Cap buff info for capture handle (%p)", (void *)pRaagaCapture));
                BDBG_ERR(("Enabled          = %d", pRaagaCapture->enabled));
                BDBG_ERR(("numBuffers       = %d", pRaagaCapture->numBuffers));
                BDBG_ERR(("updateRead       = %d", pRaagaCapture->updateRead));
                BDBG_ERR(("eBuffType        = %d", pRaagaCapture->eBuffType));

                for (j = 0; j < pRaagaCapture->numBuffers; j++)
                {
                    BDBG_ERR(("Op  ptrs : 0x%08x , 0x%08x , 0x%08x , 0x%08x , 0x%08x",
                        pRaagaCapture->capPtrs[j].outputBufferPtr.ui32BaseAddr,
                        pRaagaCapture->capPtrs[j].outputBufferPtr.ui32ReadAddr,
                        pRaagaCapture->capPtrs[j].outputBufferPtr.ui32WriteAddr,
                        pRaagaCapture->capPtrs[j].outputBufferPtr.ui32EndAddr,
                        pRaagaCapture->capPtrs[j].outputBufferPtr.ui32WrapAddr));
                    BDBG_ERR(("Cap ptrs : 0x%p , 0x%p , 0x%p , 0x%p , 0x%p",
                        pRaagaCapture->capPtrs[j].captureBufferPtr.pBasePtr,
                        pRaagaCapture->capPtrs[j].captureBufferPtr.pReadPtr,
                        pRaagaCapture->capPtrs[j].captureBufferPtr.pWritePtr,
                        pRaagaCapture->capPtrs[j].captureBufferPtr.pEndPtr,
                        pRaagaCapture->capPtrs[j].captureBufferPtr.pWrapPtr));
                    BDBG_ERR(("Cap pointer shadow read : 0x%08x", pRaagaCapture->capPtrs[j].shadowRead));
                }
            }
        }
        BDSP_STAGE_TRAVERSE_LOOP_END(pStageIterator)
        BKNI_ReleaseMutex(pDevice->captureMutex);
        }


    BDBG_ASSERT(NULL != ((BDSP_RaagaTask *)pTaskHandle)->startSettings.primaryStage);


    err = BDSP_P_GenNewCit(pTaskHandle);

    if (BERR_SUCCESS != err)
    {
        BDBG_ERR(("ERROR returned from Cit module %d!",err));
        err =BERR_TRACE(err);
        goto err_gen_citinput;
    }

    ctbInput.audioTaskDelayMode = pStartSettings->audioTaskDelayMode;
    ctbInput.realtimeMode = pStartSettings->realtimeMode;

    err = BDSP_Raaga_P_CalcThresholdZeroFillTimeAudOffset(
        &ctbInput,
        (void*)pStartSettings->primaryStage->pStageHandle, &(pRaagaTask->ctbOutput));

    if( err != BERR_SUCCESS)
        return BERR_TRACE(err);

    err = BDSP_Raaga_P_CheckConfigLimitations(pStartSettings->audioTaskDelayMode,
                                                pTaskHandle);
    if( err != BERR_SUCCESS)
        return BERR_TRACE(err);

    BDSP_P_AnalyseCit(pDevice->memHandle, &(pRaagaTask->citOutput.sCit));

    /* Download CIT structure into DSP/RUNNING CIT Buffer DRAM */
    err = BDSP_P_CopyDataToDram(
        pDevice->memHandle,
        (uint32_t *)(&(pRaagaTask->citOutput.sCit)),
        pRaagaTask->taskMemGrants.sCitStruct.pBaseAddr,
        pRaagaTask->taskMemGrants.sCitStruct.ui32Size
        );

    if (BERR_SUCCESS != err)
    {
        BDBG_ERR(("Error in Copying data to  CIT Buffer DRAM"));
        err = BERR_TRACE(err);
        goto err_gen_citinput;
    }

    /* Download CIT structure into HOST/SPARE CIT Buffer DRAM */
    err = BDSP_P_CopyDataToDram(
        pDevice->memHandle,
        (uint32_t *)(&(pRaagaTask->citOutput.sCit)),
        pRaagaTask->taskMemGrants.sSpareCitStruct.pBaseAddr,
        pRaagaTask->taskMemGrants.sSpareCitStruct.ui32Size
        );

    if (BERR_SUCCESS != err)
    {
        BDBG_ERR(("Error in Copying data to SPARE CIT Buffer DRAM"));
        err = BERR_TRACE(err);
        goto err_gen_citinput;
    }

    /* Initialize interframe buffers for all the nodes */

    err = BDSP_DSP_P_InitInterframeBuffer((void *)pStartSettings->primaryStage->pStageHandle);

    if (BERR_SUCCESS != err)
    {
        BDBG_ERR(("Error in initializing Interframe buffers for Task id %d",pRaagaTask->taskId));
        err = BERR_TRACE(err);
        goto err_gen_citinput;
    }

    pRaagaTask->eventEnabledMask |= BDSP_RAAGA_DEFAULT_EVENTS_ENABLE_MASK;


    /* Success */

    /*  this is Task start time, so no need to pass the task pointer*/
        /**pTask = &pRaagaTask->task;*/

        /* goto start_task_success;*/
    }
    else if (pRaagaContext->settings.contextType == BDSP_ContextType_eVideo)
    {
        {
            BDSP_RaagaCapture *pRaagaCapture;
            int j;

            /* Print the initialized captur info structure */
            BDBG_MSG(("CAPTURE BUFFER INFORMATION (%d)", pRaagaTask->taskId));
            BDBG_MSG(("--------------------------"));

            BKNI_AcquireMutex(pDevice->captureMutex);
            BDSP_STAGE_TRAVERSE_LOOP_BEGIN((BDSP_RaagaStage *)pStartSettings->primaryStage->pStageHandle, pStageIterator)
            BSTD_UNUSED(macroStId);
            BSTD_UNUSED(macroBrId);
            {
                for ( pRaagaCapture = BLST_S_FIRST(&pStageIterator->captureList);
                    pRaagaCapture != NULL;
                    pRaagaCapture = BLST_S_NEXT(pRaagaCapture, node) )
                {

                    BDBG_ERR(("Cap buff info for capture handle (%p)", (void *)pRaagaCapture));
                    BDBG_ERR(("Enabled          = %d", pRaagaCapture->enabled));
                    BDBG_ERR(("numBuffers       = %d", pRaagaCapture->numBuffers));
                    BDBG_ERR(("updateRead       = %d", pRaagaCapture->updateRead));
                    BDBG_ERR(("eBuffType        = %d", pRaagaCapture->eBuffType));

                    for (j = 0; j < pRaagaCapture->numBuffers; j++)
                    {
                        BDBG_ERR(("Op  ptrs : 0x%08x , 0x%08x , 0x%08x , 0x%08x , 0x%08x",
                            pRaagaCapture->capPtrs[j].outputBufferPtr.ui32BaseAddr,
                            pRaagaCapture->capPtrs[j].outputBufferPtr.ui32ReadAddr,
                            pRaagaCapture->capPtrs[j].outputBufferPtr.ui32WriteAddr,
                            pRaagaCapture->capPtrs[j].outputBufferPtr.ui32EndAddr,
                            pRaagaCapture->capPtrs[j].outputBufferPtr.ui32WrapAddr));
                        BDBG_ERR(("Cap ptrs : 0x%p , 0x%p , 0x%p , 0x%p , 0x%p",
                            (void *)pRaagaCapture->capPtrs[j].captureBufferPtr.pBasePtr,
                            (void *)pRaagaCapture->capPtrs[j].captureBufferPtr.pReadPtr,
                            (void *)pRaagaCapture->capPtrs[j].captureBufferPtr.pWritePtr,
                            (void *)pRaagaCapture->capPtrs[j].captureBufferPtr.pEndPtr,
                            (void *)pRaagaCapture->capPtrs[j].captureBufferPtr.pWrapPtr));
                        BDBG_ERR(("Cap pointer shadow read : 0x%08x", pRaagaCapture->capPtrs[j].shadowRead));
                    }
                }
            }
            BDSP_STAGE_TRAVERSE_LOOP_END(pStageIterator)
            BKNI_ReleaseMutex(pDevice->captureMutex);
        }
        BDBG_ASSERT(NULL != ((BDSP_RaagaTask *)pTaskHandle)->startSettings.primaryStage);

        err =BDSP_P_GenNewVideoCit(pTaskHandle, BDSP_AlgorithmType_eVideoDecode);

        if (BERR_SUCCESS != err)
        {
            BDBG_ERR(("ERROR returned from Cit module %d!",err));
            err =BERR_TRACE(err);
            goto err_gen_citinput;
        }

        BDSP_P_AnalyseVideoCit(pDevice->memHandle, &(pRaagaTask->videoCitOutput.uVideoCit), BDSP_AlgorithmType_eVideoDecode);

        BDBG_MSG(("Analyse VIDEO CIT DONE"));

        /* Download CIT structure into DRAM */
        err = BDSP_P_CopyDataToDram(
            pDevice->memHandle,
            (uint32_t *)(&(pRaagaTask->videoCitOutput.uVideoCit.sVideoDecTaskConfig)),
            pRaagaTask->taskMemGrants.sCitStruct.pBaseAddr,
            pRaagaTask->taskMemGrants.sCitStruct.ui32Size
            );

        if (BERR_SUCCESS != err)
        {
            BDBG_ERR(("Error in Copying data to DRAM"));
            err = BERR_TRACE(err);
            goto err_gen_citinput;
        }

        /* Initialize interframe buffers for all the nodes */
        err = BDSP_DSP_P_InitInterframeBuffer((void *)pStartSettings->primaryStage->pStageHandle);

        if (BERR_SUCCESS != err)
        {
            BDBG_ERR(("Error in initializing Interframe buffers for Task id %d",pRaagaTask->taskId));
            err = BERR_TRACE(err);
            goto err_gen_citinput;
        }

        pRaagaTask->eventEnabledMask |= BDSP_RAAGA_DEFAULT_EVENTS_ENABLE_MASK;

        /* Success */
        /* This is Task start time, so no need to pass the task pointer*/
        /**pTask = &pRaagaTask->task;*/

        /* goto start_task_success;*/
    }
    else if (pRaagaContext->settings.contextType == BDSP_ContextType_eVideoEncode)
    {
        {
            BDSP_RaagaCapture *pRaagaCapture;
            int j;

            /* Print the initialized captur info structure */
            BDBG_MSG(("CAPTURE BUFFER INFORMATION (%d)", pRaagaTask->taskId));
            BDBG_MSG(("--------------------------"));

            BKNI_AcquireMutex(pDevice->captureMutex);
            BDSP_STAGE_TRAVERSE_LOOP_BEGIN((BDSP_RaagaStage *)pStartSettings->primaryStage->pStageHandle, pStageIterator)
            BSTD_UNUSED(macroStId);
            BSTD_UNUSED(macroBrId);
            {
                for ( pRaagaCapture = BLST_S_FIRST(&pStageIterator->captureList);
                    pRaagaCapture != NULL;
                    pRaagaCapture = BLST_S_NEXT(pRaagaCapture, node) )
                {
                    BDBG_ERR(("Cap buff info for capture handle (%p)", (void *)pRaagaCapture));
                    BDBG_ERR(("Enabled          = %d", pRaagaCapture->enabled));
                    BDBG_ERR(("numBuffers       = %d", pRaagaCapture->numBuffers));
                    BDBG_ERR(("updateRead       = %d", pRaagaCapture->updateRead));
                    BDBG_ERR(("eBuffType        = %d", pRaagaCapture->eBuffType));

                    for (j = 0; j < pRaagaCapture->numBuffers; j++)
                    {
                        BDBG_ERR(("Op  ptrs : 0x%08x , 0x%08x , 0x%08x , 0x%08x , 0x%08x",
                            pRaagaCapture->capPtrs[j].outputBufferPtr.ui32BaseAddr,
                            pRaagaCapture->capPtrs[j].outputBufferPtr.ui32ReadAddr,
                            pRaagaCapture->capPtrs[j].outputBufferPtr.ui32WriteAddr,
                            pRaagaCapture->capPtrs[j].outputBufferPtr.ui32EndAddr,
                            pRaagaCapture->capPtrs[j].outputBufferPtr.ui32WrapAddr));
                        BDBG_ERR(("Cap ptrs : 0x%p , 0x%p , 0x%p , 0x%p , 0x%p",
                            (void *)pRaagaCapture->capPtrs[j].captureBufferPtr.pBasePtr,
                            (void *)pRaagaCapture->capPtrs[j].captureBufferPtr.pReadPtr,
                            (void *)pRaagaCapture->capPtrs[j].captureBufferPtr.pWritePtr,
                            (void *)pRaagaCapture->capPtrs[j].captureBufferPtr.pEndPtr,
                            (void *)pRaagaCapture->capPtrs[j].captureBufferPtr.pWrapPtr));
                        BDBG_ERR(("Cap pointer shadow read : 0x%08x", pRaagaCapture->capPtrs[j].shadowRead));
                    }
                }
            }
            BDSP_STAGE_TRAVERSE_LOOP_END(pStageIterator)
            BKNI_ReleaseMutex(pDevice->captureMutex);
        }
        BDBG_ASSERT(NULL != ((BDSP_RaagaTask *)pTaskHandle)->startSettings.primaryStage);

        err =BDSP_P_GenNewVideoCit(pTaskHandle, BDSP_AlgorithmType_eVideoEncode);

        if (BERR_SUCCESS != err)
        {
            BDBG_ERR(("ERROR returned from Cit module %d!",err));
            err =BERR_TRACE(err);
            goto err_gen_citinput;
        }

        BDSP_P_AnalyseVideoCit(pDevice->memHandle, &(pRaagaTask->videoCitOutput.uVideoCit), BDSP_AlgorithmType_eVideoEncode);

        BDBG_MSG(("Analyse VIDEO CIT DONE"));

        /* Download CIT structure into DRAM */
        err = BDSP_P_CopyDataToDram(
            pDevice->memHandle,
            (uint32_t *)(&(pRaagaTask->videoCitOutput.uVideoCit.sVideoDecTaskConfig)),
            pRaagaTask->taskMemGrants.sCitStruct.pBaseAddr,
            pRaagaTask->taskMemGrants.sCitStruct.ui32Size
            );

        if (BERR_SUCCESS != err)
        {
            BDBG_ERR(("Error in Copying data to DRAM"));
            err = BERR_TRACE(err);
            goto err_gen_citinput;
        }

        /* Initialize interframe buffers for all the nodes */
        err = BDSP_DSP_P_InitInterframeBuffer((void *)pStartSettings->primaryStage->pStageHandle);

        if (BERR_SUCCESS != err)
        {
            BDBG_ERR(("Error in initializing Interframe buffers for Task id %d",pRaagaTask->taskId));
            err = BERR_TRACE(err);
            goto err_gen_citinput;
        }

        pRaagaTask->eventEnabledMask |= BDSP_RAAGA_DEFAULT_EVENTS_ENABLE_MASK;

        /* Success */
        /* This is Task start time, so no need to pass the task pointer*/
        /**pTask = &pRaagaTask->task;*/

        /* goto start_task_success;*/
    }
    else if (pRaagaContext->settings.contextType == BDSP_ContextType_eScm)
    {
        BDBG_ASSERT(NULL != ((BDSP_RaagaTask *)pTaskHandle)->startSettings.primaryStage);

        err = BDSP_P_GenNewScmCit(pTaskHandle);

        if (BERR_SUCCESS != err)
        {
            BDBG_ERR(("ERROR returned from Cit module %d!",err));
            err =BERR_TRACE(err);
            goto err_gen_citinput;
        }

        BDSP_P_AnalyseScmCit(pDevice->memHandle, &(pRaagaTask->scmCitOutput.sScmCit));

        /* Download CIT structure into DRAM */
        err = BDSP_P_CopyDataToDram(
            pDevice->memHandle,
            (uint32_t *)(&(pRaagaTask->scmCitOutput.sScmCit)),
            pRaagaTask->taskMemGrants.sCitStruct.pBaseAddr,
            pRaagaTask->taskMemGrants.sCitStruct.ui32Size
            );

        if (BERR_SUCCESS != err)
        {
            BDBG_ERR(("Error in Copying data to DRAM"));
            err = BERR_TRACE(err);
            goto err_gen_citinput;
        }


        if (BERR_SUCCESS != err)
        {
            BDBG_ERR(("Error in initializing Interframe buffers for Task id %d",pRaagaTask->taskId));
            err = BERR_TRACE(err);
            goto err_gen_citinput;
        }

        pRaagaTask->eventEnabledMask |= BDSP_RAAGA_DEFAULT_EVENTS_ENABLE_MASK;

    }


/*the above stuff came from create task to start task*/
    /* Send VOM change Command */
    BDSP_DSPCHN_P_SendVOMChangeCommand (pRaagaTask);

    BDBG_MSG(("Context Type = %d",pRaagaContext->settings.contextType));
    BDBG_MSG(("Task Id = %d",pRaagaTask->taskId));

    if (pRaagaContext->settings.contextType  == BDSP_ContextType_eAudio)
    {
        /* Send Start Task Command */
        sCommand.sCommandHeader.ui32CommandID = BDSP_RAAGA_START_TASK_COMMAND_ID;
        sCommand.sCommandHeader.ui32CommandCounter = pRaagaTask->commandCounter++;
        sCommand.sCommandHeader.ui32TaskID = pRaagaTask->taskId;
        sCommand.sCommandHeader.eResponseType = BDSP_Raaga_P_ResponseType_eResponseRequired;
        sCommand.sCommandHeader.ui32CommandSizeInBytes =  sizeof(BDSP_Raaga_P_Command);
        /*SWRAA-154: Add ZeroPhase enable flag-default is true*/
        sCommand.uCommand.sStartTask.eZeroPhaseCorrEnable = pStartSettings->eZeroPhaseCorrEnable;

        switch ( BDSP_RAAGA_P_ALGORITHM_TYPE(((BDSP_RaagaStage *)pStartSettings->primaryStage->pStageHandle)->algorithm) )
        {
            default:
            case BDSP_AlgorithmType_eAudioMixer:
            case BDSP_AlgorithmType_eAudioDecode:
                sCommand.uCommand.sStartTask.eTaskAlgoType = BDSP_Raaga_P_AlgoType_eDecode;
                sCommand.uCommand.sStartTask.ePPMCorrEnable = pStartSettings->ppmCorrection;
                break;
            case BDSP_AlgorithmType_eAudioPassthrough:
                /*Till FW adds proper programming */
                /*                sCommand.uCommand.sStartTask.eTaskAlgoType = BDSP_Raaga_P_AlgoType_ePassThru; */
                /*                sCommand.uCommand.sStartTask.eDeadlineComputationFuncType =
                                BDSP_Raaga_P_DeadLineComputeFuncType_ePassthrough;*/
                sCommand.uCommand.sStartTask.eTaskAlgoType = BDSP_Raaga_P_AlgoType_eDecode;
                sCommand.uCommand.sStartTask.ePPMCorrEnable = BDSP_AF_P_eDisable;
                break;
            case BDSP_AlgorithmType_eAudioProcessing:
            case BDSP_AlgorithmType_eAudioEchoCanceller:
                sCommand.uCommand.sStartTask.eTaskAlgoType = BDSP_Raaga_P_AlgoType_eDecode;
                sCommand.uCommand.sStartTask.ePPMCorrEnable = BDSP_AF_P_eDisable;
                break;
        }

        /* Enable mute frame rendering at start based on the flag openGateAtStart */
        if (pStartSettings->openGateAtStart)
        {
            sCommand.uCommand.sStartTask.eOpenGateAtStart = BDSP_AF_P_eEnable;
        }
        else
        {
            sCommand.uCommand.sStartTask.eOpenGateAtStart = BDSP_AF_P_eDisable;
        }


        /* Fill up start task parameters */
        pTaskParams = (BDSP_Raaga_P_TaskParamInfo *)(pRaagaTask->taskMemGrants.sTaskInfo.pBaseAddr);

        if (pRaagaTask->startSettings.realtimeMode== BDSP_TaskRealtimeMode_eNonRealTime)
        {
            sCommand.uCommand.sStartTask.eDeadlineComputationFuncType =
                BDSP_Raaga_P_DeadLineComputeFuncType_eNonRealtimeDecode;
            sCommand.uCommand.sStartTask.eTaskType = BDSP_Raaga_P_TaskType_eNonRealtime;

            pTaskParams->sNonRealTimeTaskParams.ui32MaxTimeSlice = 1350;
            pTaskParams->sNonRealTimeTaskParams.ui32MinTimeThreshold = 45;
        }
        else if(pRaagaTask->startSettings.realtimeMode== BDSP_TaskRealtimeMode_eOnDemand)
        {
            sCommand.uCommand.sStartTask.eTaskType = BDSP_Raaga_P_TaskType_eOnDemand;
            sCommand.uCommand.sStartTask.eDeadlineComputationFuncType =
                BDSP_Raaga_P_DeadLineComputeFuncType_eOnDemand;
        }
        else
        {
            sCommand.uCommand.sStartTask.eTaskType = BDSP_Raaga_P_TaskType_eRealtime;
            sCommand.uCommand.sStartTask.eDeadlineComputationFuncType =
                BDSP_Raaga_P_DeadLineComputeFuncType_eRealtimeDecode;
        }

        if (pRaagaTask->startSettings.schedulingMode == BDSP_TaskSchedulingMode_eSlave)
        {
            sCommand.uCommand.sStartTask.eSchedulingMode = BDSP_Raaga_P_SchedulingMode_eSlave;
        }
        else
        {
            sCommand.uCommand.sStartTask.eSchedulingMode = BDSP_Raaga_P_SchedulingMode_eMaster;
        }

        if ((pRaagaTask->startSettings.schedulingMode== BDSP_TaskSchedulingMode_eSlave)&&(pRaagaTask->masterTaskId != BDSP_RAAGA_P_INVALID_TASK_ID))
        {
            sCommand.uCommand.sStartTask.ui32MasterTaskId = pRaagaTask->masterTaskId;
        }
        else
        {
            sCommand.uCommand.sStartTask.ui32MasterTaskId = BDSP_RAAGA_P_INVALID_TASK_ID;
        }

        BDSP_MEM_P_ConvertAddressToOffset(pDevice->memHandle,
            pRaagaTask->taskMemGrants.sTaskInfo.pBaseAddr,
            &ui32PhysAddr);
        sCommand.uCommand.sStartTask.ui32DramDeadlineConfigStructAddr = ui32PhysAddr;

        BDSP_MEM_P_ConvertAddressToOffset(pDevice->memHandle,
            pRaagaTask->taskMemGrants.sCitStruct.pBaseAddr,
            &ui32PhysAddr);
        sCommand.uCommand.sStartTask.ui32DramTaskConfigAddr = ui32PhysAddr;
        sCommand.uCommand.sStartTask.ui32SyncQueueId = pRaagaTask->hSyncMsgQueue->i32FifoId;
        sCommand.uCommand.sStartTask.ui32AsyncQueueId = pRaagaTask->hAsyncMsgQueue->i32FifoId;

        BDSP_MEM_P_ConvertAddressToOffset(pDevice->memHandle,
            pRaagaTask->taskMemGrants.sStackSwapBuff.pBaseAddr,
            &ui32PhysAddr);
        sCommand.uCommand.sStartTask.sDramStackBuffer.ui32DramBufferAddress = ui32PhysAddr;
        sCommand.uCommand.sStartTask.sDramStackBuffer.ui32BufferSizeInBytes = pRaagaTask->taskMemGrants.sStackSwapBuff.ui32Size;

        pTaskParams->ui32SamplingFrequency = 48000;
        pTaskParams->ui32SchedulingBufferThreshold = pRaagaTask->ctbOutput.ui32Threshold;
        pTaskParams->ui32BlockTime = pRaagaTask->ctbOutput.ui32BlockTime;

        /*TODO : ui32FrameSize is not required anymore by FW. remove this parameter */
        pTaskParams->ui32FrameSize = 1536;
        pTaskParams->eBufferType = BDSP_AF_P_BufferType_eFMM;


        if (pRaagaTask->schedulingMode == BDSP_TaskSchedulingMode_eSlave)
        {
            err = BDSP_Raaga_P_FindSlaveTaskSchedulingBuffer(&pRaagaTask->startSettings, &pTaskParams->sDspSchedulingBuffInfo.ui32DramSchedulingBuffCfgAddr, &pTaskParams->eBufferType);
            if (BERR_SUCCESS != err)
            {
                BDBG_ERR(("Unable to find scheduling buffer for the slave task : %d", pRaagaTask->taskId));
                err = BERR_TRACE(err);
                goto end;
            }
            pTaskParams->ui32IndepDelay = 0;
            pTaskParams->ui32MaxIndepDelay = 0;
        }
        else
        {
            BDSP_CIT_P_FwStgSrcDstType    eSchedulingBufferType;
            BDSP_AF_P_sDRAM_CIRCULAR_BUFFER    sBufferPtr;
            BKNI_Memset(&sBufferPtr,0,sizeof(BDSP_AF_P_sDRAM_CIRCULAR_BUFFER));

            eSchedulingBufferType = BDSP_CIT_P_FwStgSrcDstType_eInvalid;

            err = BDSP_Raaga_P_FindSchedulingBuffer(&pRaagaTask->settings, &pRaagaTask->startSettings, &eSchedulingBufferType, &uiSchedulingBufId, &sBufferPtr,&uiSchedulingBufDelay, &schedulingBufferRate, &uiSchedulingBufferThreshold);
            if ( (BERR_SUCCESS != err) || (eSchedulingBufferType == BDSP_CIT_P_FwStgSrcDstType_eInvalid) )
            {
                BDBG_ERR(("Unable to find scheduling buffer: err=%d", err));
                err=BERR_TRACE(err);
                goto end;
            }
            if (eSchedulingBufferType == BDSP_CIT_P_FwStgSrcDstType_eFMMBuf)
            {

#ifdef BCHP_AUD_FMM_BF_CTRL_RINGBUF_0_BASEADDR
                /* Traditional RDB naming conventions */
                ui32RbufOffset = ((BCHP_AUD_FMM_BF_CTRL_RINGBUF_1_BASEADDR - BCHP_AUD_FMM_BF_CTRL_RINGBUF_0_BASEADDR) * uiSchedulingBufId);
                pTaskParams->sDspSchedulingBuffInfo.sRdbBasedSchedulingBuffer.ui32BaseAddr = BDSP_RAAGA_REGSET_ADDR_FOR_DSP( BCHP_AUD_FMM_BF_CTRL_RINGBUF_0_BASEADDR + ui32RbufOffset );
                pTaskParams->sDspSchedulingBuffInfo.sRdbBasedSchedulingBuffer.ui32EndAddr = BDSP_RAAGA_REGSET_ADDR_FOR_DSP( BCHP_AUD_FMM_BF_CTRL_RINGBUF_0_ENDADDR + ui32RbufOffset );
                pTaskParams->sDspSchedulingBuffInfo.sRdbBasedSchedulingBuffer.ui32ReadAddr = BDSP_RAAGA_REGSET_ADDR_FOR_DSP( BCHP_AUD_FMM_BF_CTRL_RINGBUF_0_RDADDR + ui32RbufOffset );
                pTaskParams->sDspSchedulingBuffInfo.sRdbBasedSchedulingBuffer.ui32WriteAddr = BDSP_RAAGA_REGSET_ADDR_FOR_DSP( BCHP_AUD_FMM_BF_CTRL_RINGBUF_0_WRADDR + ui32RbufOffset );
                pTaskParams->sDspSchedulingBuffInfo.sRdbBasedSchedulingBuffer.ui32WrapAddr = BDSP_RAAGA_REGSET_ADDR_FOR_DSP( BCHP_AUD_FMM_BF_CTRL_RINGBUF_0_ENDADDR + ui32RbufOffset );

#else
                ui32RbufOffset = ((BCHP_AUD_FMM_BF_CTRL_SOURCECH_RINGBUF_1_BASEADDR - BCHP_AUD_FMM_BF_CTRL_SOURCECH_RINGBUF_0_BASEADDR) * uiSchedulingBufId);

                pTaskParams->sDspSchedulingBuffInfo.sRdbBasedSchedulingBuffer.ui32BaseAddr = BDSP_RAAGA_REGSET_ADDR_FOR_DSP( BCHP_AUD_FMM_BF_CTRL_SOURCECH_RINGBUF_0_BASEADDR + ui32RbufOffset );
                pTaskParams->sDspSchedulingBuffInfo.sRdbBasedSchedulingBuffer.ui32EndAddr = BDSP_RAAGA_REGSET_ADDR_FOR_DSP( BCHP_AUD_FMM_BF_CTRL_SOURCECH_RINGBUF_0_ENDADDR + ui32RbufOffset );
                pTaskParams->sDspSchedulingBuffInfo.sRdbBasedSchedulingBuffer.ui32ReadAddr = BDSP_RAAGA_REGSET_ADDR_FOR_DSP( BCHP_AUD_FMM_BF_CTRL_SOURCECH_RINGBUF_0_RDADDR + ui32RbufOffset );
                pTaskParams->sDspSchedulingBuffInfo.sRdbBasedSchedulingBuffer.ui32WriteAddr = BDSP_RAAGA_REGSET_ADDR_FOR_DSP( BCHP_AUD_FMM_BF_CTRL_SOURCECH_RINGBUF_0_WRADDR + ui32RbufOffset );
                pTaskParams->sDspSchedulingBuffInfo.sRdbBasedSchedulingBuffer.ui32WrapAddr = BDSP_RAAGA_REGSET_ADDR_FOR_DSP( BCHP_AUD_FMM_BF_CTRL_SOURCECH_RINGBUF_0_ENDADDR + ui32RbufOffset );
#endif
            }
            else if (eSchedulingBufferType == BDSP_CIT_P_FwStgSrcDstType_eRaveBuf)
            {
                pTaskParams->eBufferType = BDSP_AF_P_BufferType_eRAVE;
                pTaskParams->sDspSchedulingBuffInfo.sRdbBasedSchedulingBuffer.ui32BaseAddr = sBufferPtr.ui32BaseAddr;
                pTaskParams->sDspSchedulingBuffInfo.sRdbBasedSchedulingBuffer.ui32EndAddr = sBufferPtr.ui32EndAddr;
                pTaskParams->sDspSchedulingBuffInfo.sRdbBasedSchedulingBuffer.ui32ReadAddr = sBufferPtr.ui32ReadAddr;
                pTaskParams->sDspSchedulingBuffInfo.sRdbBasedSchedulingBuffer.ui32WriteAddr = sBufferPtr.ui32WriteAddr;
                pTaskParams->sDspSchedulingBuffInfo.sRdbBasedSchedulingBuffer.ui32WrapAddr = sBufferPtr.ui32WrapAddr;
            }
            else if (eSchedulingBufferType == BDSP_CIT_P_FwStgSrcDstType_eRDBPool)
            {
                pTaskParams->eBufferType = BDSP_AF_P_BufferType_eRDBPool;
                pTaskParams->sDspSchedulingBuffInfo.sRdbBasedSchedulingBuffer.ui32BaseAddr = sBufferPtr.ui32BaseAddr;
                pTaskParams->sDspSchedulingBuffInfo.sRdbBasedSchedulingBuffer.ui32EndAddr = sBufferPtr.ui32EndAddr;
                pTaskParams->sDspSchedulingBuffInfo.sRdbBasedSchedulingBuffer.ui32ReadAddr = sBufferPtr.ui32ReadAddr;
                pTaskParams->sDspSchedulingBuffInfo.sRdbBasedSchedulingBuffer.ui32WriteAddr = sBufferPtr.ui32WriteAddr;
                pTaskParams->sDspSchedulingBuffInfo.sRdbBasedSchedulingBuffer.ui32WrapAddr = sBufferPtr.ui32WrapAddr;
            }
            else if (eSchedulingBufferType == BDSP_CIT_P_FwStgSrcDstType_eRDB)
            {
                pTaskParams->eBufferType = BDSP_AF_P_BufferType_eRDB;
                pTaskParams->sDspSchedulingBuffInfo.sRdbBasedSchedulingBuffer.ui32BaseAddr = sBufferPtr.ui32BaseAddr;
                pTaskParams->sDspSchedulingBuffInfo.sRdbBasedSchedulingBuffer.ui32EndAddr = sBufferPtr.ui32EndAddr;
                pTaskParams->sDspSchedulingBuffInfo.sRdbBasedSchedulingBuffer.ui32ReadAddr = sBufferPtr.ui32ReadAddr;
                pTaskParams->sDspSchedulingBuffInfo.sRdbBasedSchedulingBuffer.ui32WriteAddr = sBufferPtr.ui32WriteAddr;
                pTaskParams->sDspSchedulingBuffInfo.sRdbBasedSchedulingBuffer.ui32WrapAddr = sBufferPtr.ui32WrapAddr;
            }
            BDBG_MSG(("Scheduling Rbuf BaseAddr: %x", pTaskParams->sDspSchedulingBuffInfo.sRdbBasedSchedulingBuffer.ui32BaseAddr));
            pTaskParams->ui32IndepDelay = uiSchedulingBufDelay;
            pTaskParams->ui32SchedulingBufferThreshold = uiSchedulingBufferThreshold;


        /* For slave task ui32IndepDelay and ui32MaxIndepDelay should be 0*/
            pTaskParams->ui32MaxIndepDelay = pStartSettings->maxIndependentDelay;
        }
            BDBG_MSG(("pTaskParams->ui32IndepDelay (SchedulingBufDly ) =  %d pTaskParams->ui32MaxIndepDelay = %d", pTaskParams->ui32IndepDelay, pTaskParams->ui32MaxIndepDelay ));
        pTaskParams->eFmmDstFsRate = schedulingBufferRate;

        if ((pRaagaTask->schedulingMode== BDSP_TaskSchedulingMode_eMaster)
            ||(pRaagaTask->schedulingMode == BDSP_TaskSchedulingMode_eSlave))
        {
            BDSP_MEM_P_ConvertAddressToOffset(pDevice->memHandle,
                (void *)(pRaagaTask->pFeedbackBuffer),
                &(pTaskParams->ui32MasterTaskFeedbackBuffCfgAddr));
            pTaskParams->ui32MasterTaskFeedbackBuffValid = 1;
            BDBG_MSG(("%s: pTaskParams->ui32MasterTaskFeedbackBuffCfgAddr = 0x%x",(sCommand.uCommand.sStartTask.eSchedulingMode == BDSP_Raaga_P_SchedulingMode_eSlave)?"slave":"master", pTaskParams->ui32MasterTaskFeedbackBuffCfgAddr));
        }
        /* Feedback buffer setting */
        else
        {
            pTaskParams->ui32MasterTaskFeedbackBuffCfgAddr = 0;
            pTaskParams->ui32MasterTaskFeedbackBuffValid = 0;
            BDBG_MSG(("%s: pTaskParams->ui32MasterTaskFeedbackBuffCfgAddr = 0x%x",(sCommand.uCommand.sStartTask.eSchedulingMode == BDSP_Raaga_P_SchedulingMode_eSlave)?"slave":"master", pTaskParams->ui32MasterTaskFeedbackBuffCfgAddr));
        }

        BDSP_MEM_P_FlushCache(pDevice->memHandle, pTaskParams, sizeof(BDSP_Raaga_P_TaskParamInfo));
        sCommand.uCommand.sStartTask.ui32EventEnableMask = pRaagaTask->eventEnabledMask ;

        pRaagaTask->lastEventType = sCommand.sCommandHeader.ui32CommandID;

        BKNI_ResetEvent(pRaagaTask->hEvent);

        BDBG_MSG(("\n"));
        BDBG_MSG(("===========Command information============="));
        BDBG_MSG(("==========================================="));
        BDBG_MSG(("sCommand.uCommand.sStartTask.eTaskAlgoType = %d",sCommand.uCommand.sStartTask.eTaskAlgoType));
        BDBG_MSG(("sCommand.uCommand.sStartTask.eTaskType = %d",sCommand.uCommand.sStartTask.eTaskType));
        BDBG_MSG(("sCommand.uCommand.sStartTask.eSchedulingMode = %d",sCommand.uCommand.sStartTask.eSchedulingMode));
        BDBG_MSG(("sCommand.uCommand.sStartTask.ui32MasterTaskId = %d",sCommand.uCommand.sStartTask.ui32MasterTaskId));
        BDBG_MSG(("sCommand.uCommand.sStartTask.eDeadlineComputationFuncType = %d",sCommand.uCommand.sStartTask.eDeadlineComputationFuncType));
        BDBG_MSG(("sCommand.uCommand.sStartTask.ui32DramDeadlineConfigStructAddr = 0x%x",sCommand.uCommand.sStartTask.ui32DramDeadlineConfigStructAddr));
        BDBG_MSG(("sCommand.uCommand.sStartTask.ui32DramTaskConfigAddr = 0x%x",sCommand.uCommand.sStartTask.ui32DramTaskConfigAddr));
        BDBG_MSG(("sCommand.uCommand.sStartTask.ui32SyncQueueId = %d",sCommand.uCommand.sStartTask.ui32SyncQueueId));
        BDBG_MSG(("sCommand.uCommand.sStartTask.ui32AsyncQueueId = %d",sCommand.uCommand.sStartTask.ui32AsyncQueueId));
        BDBG_MSG(("sCommand.uCommand.sStartTask.sDramStackBuffer.ui32DramBufferAddress = 0x%x",sCommand.uCommand.sStartTask.sDramStackBuffer.ui32DramBufferAddress));
        BDBG_MSG(("sCommand.uCommand.sStartTask.sDramStackBuffer.ui32BufferSizeInBytes = %d",sCommand.uCommand.sStartTask.sDramStackBuffer.ui32BufferSizeInBytes));
        BDBG_MSG(("sCommand.uCommand.sStartTask.ui32EventEnableMask = %d",sCommand.uCommand.sStartTask.ui32EventEnableMask));
        BDBG_MSG(("sCommand.uCommand.sStartTask.ePPMCorrEnable = %d",sCommand.uCommand.sStartTask.ePPMCorrEnable));
        BDBG_MSG(("sCommand.uCommand.sStartTask.eOpenGateAtStart = %d\n\n",sCommand.uCommand.sStartTask.eOpenGateAtStart));

        err = BDSP_Raaga_P_SendCommand(pDevice->hCmdQueue[pRaagaTask->settings.dspIndex], &sCommand,(void *)pRaagaTask);
        /*Accept the other Commands , After posting Start task Command */

        if (BERR_SUCCESS != err)
        {
            BDBG_ERR(("BDSP_Raaga_P_StartTask: START_TASK creation failed!"));
            err = BERR_TRACE(err);
            goto end;
        }
        /* Wait for Ack_Response_Received event w/ timeout */
        err = BKNI_WaitForEvent(pRaagaTask->hEvent, BDSP_RAAGA_START_STOP_EVENT_TIMEOUT_IN_MS);
        if (BERR_TIMEOUT == err)
        {
            BDBG_ERR(("BDSP_Raaga_P_StartTask: START_TASK ACK timeout!"));
            err = BERR_TRACE(err);
            goto end;
        }

        /* Send command for the task , Only if the ack for the Start of the task is recieved */
        pRaagaTask->isStopped = false;

        eMsgType = BDSP_Raaga_P_MsgType_eSyn;
        err = BDSP_Raaga_P_GetMsg(pRaagaTask->hSyncMsgQueue, (void *)&sRsp,eMsgType);

        if (BERR_SUCCESS != err)
        {
            BDBG_ERR(("BDSP_Raaga_P_StartTask: Unable to read ACK!"));
            err = BERR_TRACE(err);
            goto end;
        }

        if ((sRsp.sCommonAckResponseHeader.eStatus != BERR_SUCCESS)||
            (sRsp.sCommonAckResponseHeader.ui32ResponseID != BDSP_RAAGA_START_TASK_RESPONSE_ID)||
            (sRsp.sCommonAckResponseHeader.ui32TaskID != pRaagaTask->taskId))
        {

            BDBG_ERR(("BDSP_Raaga_P_StartTask: START_TASK ACK not received successfully!eStatus = %d , ui32ResponseID = %d , ui32TaskID %d ",
                sRsp.sCommonAckResponseHeader.eStatus,sRsp.sCommonAckResponseHeader.ui32ResponseID,sRsp.sCommonAckResponseHeader.ui32TaskID));
            err = BERR_TRACE(sRsp.sCommonAckResponseHeader.eStatus);
            goto end;
        }
    }
    else if (pRaagaContext->settings.contextType  == BDSP_ContextType_eVideo)
    {
        /* Send Start Task Command */
        sCommand.sCommandHeader.ui32CommandID = BDSP_RAAGA_START_TASK_COMMAND_ID;
        sCommand.sCommandHeader.ui32CommandCounter = 0;
        sCommand.sCommandHeader.ui32TaskID = pRaagaTask->taskId;
        sCommand.sCommandHeader.eResponseType = BDSP_Raaga_P_ResponseType_eResponseRequired;
        sCommand.sCommandHeader.ui32CommandSizeInBytes =  sizeof(BDSP_Raaga_P_Command);

        sCommand.uCommand.sStartTask.eTaskAlgoType = BDSP_Raaga_P_AlgoType_eVideoDecode;
        sCommand.uCommand.sStartTask.eDeadlineComputationFuncType =  BDSP_Raaga_P_DeadLineComputeFuncType_eNonRealtimeDecode;

        if (pRaagaTask->startSettings.schedulingMode == BDSP_TaskSchedulingMode_eSlave)
        {
            sCommand.uCommand.sStartTask.eSchedulingMode = BDSP_Raaga_P_SchedulingMode_eSlave;
        }
        else
        {
            sCommand.uCommand.sStartTask.eSchedulingMode = BDSP_Raaga_P_SchedulingMode_eMaster;
        }

        sCommand.uCommand.sStartTask.eTaskType = BDSP_Raaga_P_TaskType_eSoftRealtime;

        BDSP_MEM_P_ConvertAddressToOffset(pDevice->memHandle,
            pRaagaTask->taskMemGrants.sTaskInfo.pBaseAddr,
            &ui32PhysAddr);
        sCommand.uCommand.sStartTask.ui32DramDeadlineConfigStructAddr = ui32PhysAddr;


        BDSP_MEM_P_ConvertAddressToOffset(pDevice->memHandle,
            pRaagaTask->taskMemGrants.sCitStruct.pBaseAddr,
            &ui32PhysAddr);
        sCommand.uCommand.sStartTask.ui32DramTaskConfigAddr = ui32PhysAddr;
        sCommand.uCommand.sStartTask.ui32SyncQueueId = pRaagaTask->hSyncMsgQueue->i32FifoId;
        sCommand.uCommand.sStartTask.ui32AsyncQueueId = pRaagaTask->hAsyncMsgQueue->i32FifoId;

        BDSP_MEM_P_ConvertAddressToOffset(pDevice->memHandle,
            pRaagaTask->taskMemGrants.sStackSwapBuff.pBaseAddr,
            &ui32PhysAddr);
        sCommand.uCommand.sStartTask.sDramStackBuffer.ui32DramBufferAddress = ui32PhysAddr;
        sCommand.uCommand.sStartTask.sDramStackBuffer.ui32BufferSizeInBytes = pRaagaTask->taskMemGrants.sStackSwapBuff.ui32Size;

        /* Fill up start task parameters */
        pTaskParams = (BDSP_Raaga_P_TaskParamInfo *)(pRaagaTask->taskMemGrants.sTaskInfo.pBaseAddr);

        pTaskParams->ui32SchedulingBufferThreshold = uiSchedulingBufferThreshold;
        pTaskParams->ui32BlockTime = ui32BlockTime;

        pTaskParams->sNonRealTimeTaskParams.ui32MaxTimeSlice = 1350;
        pTaskParams->sNonRealTimeTaskParams.ui32MinTimeThreshold = 45;

        /*TODO : ui32FrameSize is not required anymore by FW. remove this parameter */
        pTaskParams->ui32FrameSize = 1536;
        pTaskParams->eBufferType = BDSP_AF_P_BufferType_eFMM;

        ui32RbufOffset = BCHP_RAAGA_DSP_FW_CFG_FIFO_1_BASE_ADDR - \
            BCHP_RAAGA_DSP_FW_CFG_FIFO_0_BASE_ADDR;

        ui32RbufOffset = BCHP_RAAGA_DSP_FW_CFG_FIFO_0_BASE_ADDR + \
            (ui32RbufOffset * BDSP_RAAGA_DSP_P_FIFO_PDQ);

        pTaskParams->sDspSchedulingBuffInfo.sRdbBasedSchedulingBuffer.ui32BaseAddr = BDSP_RAAGA_REGSET_ADDR_FOR_DSP( ui32RbufOffset + BDSP_RAAGA_P_FIFO_BASE_OFFSET );
        BDBG_MSG(("pTaskParams->sCircBuffer.ui32BaseAddr > %x", pTaskParams->sDspSchedulingBuffInfo.sRdbBasedSchedulingBuffer.ui32BaseAddr));

        pTaskParams->sDspSchedulingBuffInfo.sRdbBasedSchedulingBuffer.ui32EndAddr = BDSP_RAAGA_REGSET_ADDR_FOR_DSP( ui32RbufOffset + BDSP_RAAGA_P_FIFO_END_OFFSET );
        pTaskParams->sDspSchedulingBuffInfo.sRdbBasedSchedulingBuffer.ui32ReadAddr = BDSP_RAAGA_REGSET_ADDR_FOR_DSP( ui32RbufOffset + BDSP_RAAGA_P_FIFO_READ_OFFSET );
        pTaskParams->sDspSchedulingBuffInfo.sRdbBasedSchedulingBuffer.ui32WriteAddr = BDSP_RAAGA_REGSET_ADDR_FOR_DSP( ui32RbufOffset + BDSP_RAAGA_P_FIFO_WRITE_OFFSET );
        pTaskParams->sDspSchedulingBuffInfo.sRdbBasedSchedulingBuffer.ui32WrapAddr = BDSP_RAAGA_REGSET_ADDR_FOR_DSP( ui32RbufOffset + BDSP_RAAGA_P_FIFO_END_OFFSET );
        BDSP_MEM_P_FlushCache(pDevice->memHandle, pTaskParams, sizeof(BDSP_Raaga_P_TaskParamInfo));

        sCommand.uCommand.sStartTask.ui32EventEnableMask = pRaagaTask->eventEnabledMask ;

        pRaagaTask->lastEventType = sCommand.sCommandHeader.ui32CommandID;

        BKNI_ResetEvent(pRaagaTask->hEvent);

        BDBG_MSG(("\n"));
        BDBG_MSG(("===========Command information============="));
        BDBG_MSG(("==========================================="));
        BDBG_MSG(("sCommand.uCommand.sStartTask.eTaskAlgoType = %d",sCommand.uCommand.sStartTask.eTaskAlgoType));
        BDBG_MSG(("sCommand.uCommand.sStartTask.eTaskType = %d",sCommand.uCommand.sStartTask.eTaskType));
        BDBG_MSG(("sCommand.uCommand.sStartTask.ui32MasterTaskId = %d",sCommand.uCommand.sStartTask.ui32MasterTaskId));
        BDBG_MSG(("sCommand.uCommand.sStartTask.eDeadlineComputationFuncType = %d",sCommand.uCommand.sStartTask.eDeadlineComputationFuncType));
        BDBG_MSG(("sCommand.uCommand.sStartTask.ui32DramDeadlineConfigStructAddr = 0x%x",sCommand.uCommand.sStartTask.ui32DramDeadlineConfigStructAddr));
        BDBG_MSG(("sCommand.uCommand.sStartTask.ui32DramTaskConfigAddr = 0x%x",sCommand.uCommand.sStartTask.ui32DramTaskConfigAddr));
        BDBG_MSG(("sCommand.uCommand.sStartTask.ui32SyncQueueId = %d",sCommand.uCommand.sStartTask.ui32SyncQueueId));
        BDBG_MSG(("sCommand.uCommand.sStartTask.ui32AsyncQueueId = %d",sCommand.uCommand.sStartTask.ui32AsyncQueueId));
        BDBG_MSG(("sCommand.uCommand.sStartTask.sDramStackBuffer.ui32DramBufferAddress = 0x%x",sCommand.uCommand.sStartTask.sDramStackBuffer.ui32DramBufferAddress));
        BDBG_MSG(("sCommand.uCommand.sStartTask.sDramStackBuffer.ui32BufferSizeInBytes = %d",sCommand.uCommand.sStartTask.sDramStackBuffer.ui32BufferSizeInBytes));
        BDBG_MSG(("sCommand.uCommand.sStartTask.ui32EventEnableMask = %d",sCommand.uCommand.sStartTask.ui32EventEnableMask));
        BDBG_MSG(("sCommand.uCommand.sStartTask.ePPMCorrEnable = %d\n\n",sCommand.uCommand.sStartTask.ePPMCorrEnable));
        BDBG_MSG(("sCommand.uCommand.sStartTask.eOpenGateAtStart = %d\n\n",sCommand.uCommand.sStartTask.eOpenGateAtStart));

        err = BDSP_Raaga_P_SendCommand(pDevice->hCmdQueue[pRaagaTask->settings.dspIndex], &sCommand,(void *)pRaagaTask);
        /*Accept the other Commands , After posting Start task Command */
        if (BERR_SUCCESS != err)
        {
            BDBG_ERR(("BDSP_Raaga_P_StartTask: START_TASK creation failed!"));
            err = BERR_TRACE(err);
            goto end;
        }

        /* Wait for Ack_Response_Received event w/ timeout */
        err = BKNI_WaitForEvent(pRaagaTask->hEvent, BDSP_RAAGA_START_STOP_EVENT_TIMEOUT_IN_MS);
        if (BERR_TIMEOUT == err)
        {
            BDBG_ERR(("BDSP_Raaga_P_StartTask: START_TASK ACK timeout!"));
            err = BERR_TRACE(err);
            goto end;
        }

        /* Send command for the task , Only if the ack for the Start of the task is recieved */
        pRaagaTask->isStopped = false;

        eMsgType = BDSP_Raaga_P_MsgType_eSyn;
        err = BDSP_Raaga_P_GetMsg(pRaagaTask->hSyncMsgQueue, (void *)&sRsp,eMsgType);

        if (BERR_SUCCESS != err)
        {
            BDBG_ERR(("BDSP_Raaga_P_StartTask: Unable to read ACK!"));
            err = BERR_TRACE(err);
            goto end;
        }

        if ((sRsp.sCommonAckResponseHeader.eStatus != BERR_SUCCESS)||
            (sRsp.sCommonAckResponseHeader.ui32ResponseID != BDSP_RAAGA_START_TASK_RESPONSE_ID)||
            (sRsp.sCommonAckResponseHeader.ui32TaskID != pRaagaTask->taskId))
        {

            BDBG_ERR(("BDSP_Raaga_P_StartTask: START_TASK ACK not received successfully!eStatus = %d , ui32ResponseID = %d , ui32TaskID %d ",
                sRsp.sCommonAckResponseHeader.eStatus,sRsp.sCommonAckResponseHeader.ui32ResponseID,sRsp.sCommonAckResponseHeader.ui32TaskID));
            err = BERR_TRACE(sRsp.sCommonAckResponseHeader.eStatus);
            goto end;
        }
    }
    else if (BDSP_ContextType_eVideoEncode == pRaagaContext->settings.contextType )
    {
        /* Send Start Task Command */
        sCommand.sCommandHeader.ui32CommandID = BDSP_RAAGA_START_TASK_COMMAND_ID;
        sCommand.sCommandHeader.ui32CommandCounter = 0;
        sCommand.sCommandHeader.ui32TaskID = pRaagaTask->taskId;
        sCommand.sCommandHeader.eResponseType = BDSP_Raaga_P_ResponseType_eResponseRequired;
        sCommand.sCommandHeader.ui32CommandSizeInBytes =  sizeof(BDSP_Raaga_P_Command);

        sCommand.uCommand.sStartTask.eTaskAlgoType = BDSP_Raaga_P_AlgoType_eVideoEncode;
        sCommand.uCommand.sStartTask.eDeadlineComputationFuncType =  BDSP_Raaga_P_DeadLineComputeFuncType_eNonRealtimeDecode;

        sCommand.uCommand.sStartTask.eTaskType = BDSP_Raaga_P_TaskType_eSoftRealtime;

        BDSP_MEM_P_ConvertAddressToOffset(pDevice->memHandle,
            pRaagaTask->taskMemGrants.sTaskInfo.pBaseAddr,
            &ui32PhysAddr);
        sCommand.uCommand.sStartTask.ui32DramDeadlineConfigStructAddr = ui32PhysAddr;


        BDSP_MEM_P_ConvertAddressToOffset(pDevice->memHandle,
            pRaagaTask->taskMemGrants.sCitStruct.pBaseAddr,
            &ui32PhysAddr);
        sCommand.uCommand.sStartTask.ui32DramTaskConfigAddr = ui32PhysAddr;
        sCommand.uCommand.sStartTask.ui32SyncQueueId = pRaagaTask->hSyncMsgQueue->i32FifoId;
        sCommand.uCommand.sStartTask.ui32AsyncQueueId = pRaagaTask->hAsyncMsgQueue->i32FifoId;

        BDSP_MEM_P_ConvertAddressToOffset(pDevice->memHandle,
            pRaagaTask->taskMemGrants.sStackSwapBuff.pBaseAddr,
            &ui32PhysAddr);
        sCommand.uCommand.sStartTask.sDramStackBuffer.ui32DramBufferAddress = ui32PhysAddr;
        sCommand.uCommand.sStartTask.sDramStackBuffer.ui32BufferSizeInBytes = pRaagaTask->taskMemGrants.sStackSwapBuff.ui32Size;

        /* Fill up start task parameters */
        pTaskParams = (BDSP_Raaga_P_TaskParamInfo *)(pRaagaTask->taskMemGrants.sTaskInfo.pBaseAddr);

        pTaskParams->ui32SchedulingBufferThreshold = uiSchedulingBufferThreshold;
        pTaskParams->ui32BlockTime = ui32BlockTime;

        pTaskParams->sNonRealTimeTaskParams.ui32MaxTimeSlice = 1350;
        pTaskParams->sNonRealTimeTaskParams.ui32MinTimeThreshold = 45;

        /*TODO : ui32FrameSize is not required anymore by FW. remove this parameter */
        pTaskParams->ui32FrameSize = 1536;
        pTaskParams->eBufferType = BDSP_AF_P_BufferType_eRDB;
        ui32RbufOffset = BCHP_RAAGA_DSP_FW_CFG_FIFO_1_BASE_ADDR - \
            BCHP_RAAGA_DSP_FW_CFG_FIFO_0_BASE_ADDR;

        ui32RbufOffset = BCHP_RAAGA_DSP_FW_CFG_FIFO_0_BASE_ADDR + \
            (ui32RbufOffset * BDSP_RAAGA_DSP_P_FIFO_PDQ);

        pTaskParams->sDspSchedulingBuffInfo.sRdbBasedSchedulingBuffer.ui32BaseAddr = BDSP_RAAGA_REGSET_ADDR_FOR_DSP( ui32RbufOffset + BDSP_RAAGA_P_FIFO_BASE_OFFSET );
        BDBG_MSG(("pTaskParams->sCircBuffer.ui32BaseAddr > %x", pTaskParams->sDspSchedulingBuffInfo.sRdbBasedSchedulingBuffer.ui32BaseAddr));

        pTaskParams->sDspSchedulingBuffInfo.sRdbBasedSchedulingBuffer.ui32EndAddr = BDSP_RAAGA_REGSET_ADDR_FOR_DSP( ui32RbufOffset + BDSP_RAAGA_P_FIFO_END_OFFSET );
        pTaskParams->sDspSchedulingBuffInfo.sRdbBasedSchedulingBuffer.ui32ReadAddr = BDSP_RAAGA_REGSET_ADDR_FOR_DSP( ui32RbufOffset + BDSP_RAAGA_P_FIFO_READ_OFFSET );
        pTaskParams->sDspSchedulingBuffInfo.sRdbBasedSchedulingBuffer.ui32WriteAddr = BDSP_RAAGA_REGSET_ADDR_FOR_DSP( ui32RbufOffset + BDSP_RAAGA_P_FIFO_WRITE_OFFSET );
        pTaskParams->sDspSchedulingBuffInfo.sRdbBasedSchedulingBuffer.ui32WrapAddr = BDSP_RAAGA_REGSET_ADDR_FOR_DSP( ui32RbufOffset + BDSP_RAAGA_P_FIFO_END_OFFSET );

        BDSP_MEM_P_FlushCache(pDevice->memHandle, pTaskParams, sizeof(BDSP_Raaga_P_TaskParamInfo));
        sCommand.uCommand.sStartTask.ui32EventEnableMask = pRaagaTask->eventEnabledMask ;

        pRaagaTask->lastEventType = sCommand.sCommandHeader.ui32CommandID;

        BKNI_ResetEvent(pRaagaTask->hEvent);

        BDBG_MSG(("\n"));
        BDBG_MSG(("===========Command information============="));
        BDBG_MSG(("==========================================="));
        BDBG_MSG(("sCommand.uCommand.sStartTask.eTaskAlgoType = %d",sCommand.uCommand.sStartTask.eTaskAlgoType));
        BDBG_MSG(("sCommand.uCommand.sStartTask.eTaskType = %d",sCommand.uCommand.sStartTask.eTaskType));
        BDBG_MSG(("sCommand.uCommand.sStartTask.ui32MasterTaskId = %d",sCommand.uCommand.sStartTask.ui32MasterTaskId));
        BDBG_MSG(("sCommand.uCommand.sStartTask.eDeadlineComputationFuncType = %d",sCommand.uCommand.sStartTask.eDeadlineComputationFuncType));
        BDBG_MSG(("sCommand.uCommand.sStartTask.ui32DramDeadlineConfigStructAddr = 0x%x",sCommand.uCommand.sStartTask.ui32DramDeadlineConfigStructAddr));
        BDBG_MSG(("sCommand.uCommand.sStartTask.ui32DramTaskConfigAddr = 0x%x",sCommand.uCommand.sStartTask.ui32DramTaskConfigAddr));
        BDBG_MSG(("sCommand.uCommand.sStartTask.ui32SyncQueueId = %d",sCommand.uCommand.sStartTask.ui32SyncQueueId));
        BDBG_MSG(("sCommand.uCommand.sStartTask.ui32AsyncQueueId = %d",sCommand.uCommand.sStartTask.ui32AsyncQueueId));
        BDBG_MSG(("sCommand.uCommand.sStartTask.sDramStackBuffer.ui32DramBufferAddress = 0x%x",sCommand.uCommand.sStartTask.sDramStackBuffer.ui32DramBufferAddress));
        BDBG_MSG(("sCommand.uCommand.sStartTask.sDramStackBuffer.ui32BufferSizeInBytes = %d",sCommand.uCommand.sStartTask.sDramStackBuffer.ui32BufferSizeInBytes));
        BDBG_MSG(("sCommand.uCommand.sStartTask.ui32EventEnableMask = %d",sCommand.uCommand.sStartTask.ui32EventEnableMask));
        BDBG_MSG(("sCommand.uCommand.sStartTask.ePPMCorrEnable = %d\n\n",sCommand.uCommand.sStartTask.ePPMCorrEnable));
        BDBG_MSG(("sCommand.uCommand.sStartTask.eOpenGateAtStart = %d\n\n",sCommand.uCommand.sStartTask.eOpenGateAtStart));


        err = BDSP_Raaga_P_SendCommand(pDevice->hCmdQueue[pRaagaTask->settings.dspIndex], &sCommand,(void *)pRaagaTask);
        /*Accept the other Commands , After posting Start task Command */
        if (BERR_SUCCESS != err)
        {
            BDBG_ERR(("BDSP_Raaga_P_StartTask: START_TASK creation failed!"));
            err = BERR_TRACE(err);
            goto end;
        }

        /* Wait for Ack_Response_Received event w/ timeout */
        err = BKNI_WaitForEvent(pRaagaTask->hEvent, BDSP_RAAGA_START_STOP_EVENT_TIMEOUT_IN_MS);
        if (BERR_TIMEOUT == err)
        {
            BDBG_ERR(("BDSP_Raaga_P_StartTask: START_TASK ACK timeout!"));
            err = BERR_TRACE(err);
            goto end;
        }

        /* Send command for the task , Only if the ack for the Start of the task is recieved */
        pRaagaTask->isStopped = false;

        eMsgType = BDSP_Raaga_P_MsgType_eSyn;
        err = BDSP_Raaga_P_GetMsg(pRaagaTask->hSyncMsgQueue, (void *)&sRsp,eMsgType);

        if (BERR_SUCCESS != err)
        {
            BDBG_ERR(("BDSP_Raaga_P_StartTask: Unable to read ACK!"));
            err = BERR_TRACE(err);
            goto end;
        }

        if ((sRsp.sCommonAckResponseHeader.eStatus != BERR_SUCCESS)||
            (sRsp.sCommonAckResponseHeader.ui32ResponseID != BDSP_RAAGA_START_TASK_RESPONSE_ID)||
            (sRsp.sCommonAckResponseHeader.ui32TaskID != pRaagaTask->taskId))
        {

            BDBG_ERR(("BDSP_Raaga_P_StartTask: START_TASK ACK not received successfully!eStatus = %d , ui32ResponseID = %d , ui32TaskID %d ",
                sRsp.sCommonAckResponseHeader.eStatus,sRsp.sCommonAckResponseHeader.ui32ResponseID,sRsp.sCommonAckResponseHeader.ui32TaskID));
            err = BERR_TRACE(sRsp.sCommonAckResponseHeader.eStatus);
            goto end;
        }
        /* Unmask any interrupt that task might be using */
        if( true == pStartSettings->extInterruptConfig.enableInterrupts)
        {
            /* for all the enabled interrupts */
            for(i = 0; i < pStartSettings->extInterruptConfig.numInterrupts; i++)
            {
                BDSP_Write32(pDevice->regHandle, \
                    BCHP_RAAGA_DSP_ESR_SI_MASK_CLEAR + pDevice->dspOffset[pRaagaTask->settings.dspIndex], \
                    (1 << pStartSettings->extInterruptConfig.interruptInfo[i].interruptBit));
            }
        }
    }
    else if (BDSP_ContextType_eScm == pRaagaContext->settings.contextType )
    {
        /* Send Start Task Command */
        sCommand.sCommandHeader.ui32CommandID = BDSP_RAAGA_START_TASK_COMMAND_ID;
        sCommand.sCommandHeader.ui32CommandCounter = 0;
        sCommand.sCommandHeader.ui32TaskID = pRaagaTask->taskId;
        sCommand.sCommandHeader.eResponseType = BDSP_Raaga_P_ResponseType_eResponseRequired;
        sCommand.sCommandHeader.ui32CommandSizeInBytes =  sizeof(BDSP_Raaga_P_Command);

        sCommand.uCommand.sStartTask.eTaskAlgoType = BDSP_Raaga_P_AlgoType_eScm;
        sCommand.uCommand.sStartTask.eDeadlineComputationFuncType =  BDSP_Raaga_P_DeadLineComputeFuncType_eScmTask;

        sCommand.uCommand.sStartTask.eTaskType = BDSP_Raaga_P_TaskType_eRealtime;

        BDSP_MEM_P_ConvertAddressToOffset(pDevice->memHandle,
            pRaagaTask->taskMemGrants.sTaskInfo.pBaseAddr,
            &ui32PhysAddr);
        sCommand.uCommand.sStartTask.ui32DramDeadlineConfigStructAddr = ui32PhysAddr;


        BDSP_MEM_P_ConvertAddressToOffset(pDevice->memHandle,
            pRaagaTask->taskMemGrants.sCitStruct.pBaseAddr,
            &ui32PhysAddr);
        sCommand.uCommand.sStartTask.ui32DramTaskConfigAddr = ui32PhysAddr;
        sCommand.uCommand.sStartTask.ui32SyncQueueId = pRaagaTask->hSyncMsgQueue->i32FifoId;
        sCommand.uCommand.sStartTask.ui32AsyncQueueId = pRaagaTask->hAsyncMsgQueue->i32FifoId;

        BDSP_MEM_P_ConvertAddressToOffset(pDevice->memHandle,
           pRaagaTask->taskMemGrants.sStackSwapBuff.pBaseAddr,
            &ui32PhysAddr);
        sCommand.uCommand.sStartTask.sDramStackBuffer.ui32DramBufferAddress = ui32PhysAddr;
        sCommand.uCommand.sStartTask.sDramStackBuffer.ui32BufferSizeInBytes =  pRaagaTask->taskMemGrants.sStackSwapBuff.ui32Size;

        /* Fill up start task parameters */
        pTaskParams = (BDSP_Raaga_P_TaskParamInfo *)(pRaagaTask->taskMemGrants.sTaskInfo.pBaseAddr);

        /* just an init..this variable is not used for scm */
        pTaskParams->ui32SamplingFrequency = 48000;

        pTaskParams->ui32SchedulingBufferThreshold = 0;
        pTaskParams->ui32BlockTime = 0;
        pTaskParams->ui32MasterTaskFeedbackBuffValid = 0;

        /*TODO : ui32FrameSize is not required anymore by FW. remove this parameter */
        pTaskParams->ui32FrameSize = 1536;
        pTaskParams->eBufferType = BDSP_AF_P_BufferType_eRDB;

        ui32RbufOffset = BCHP_RAAGA_DSP_FW_CFG_FIFO_1_BASE_ADDR - \
            BCHP_RAAGA_DSP_FW_CFG_FIFO_0_BASE_ADDR;

        ui32RbufOffset = BCHP_RAAGA_DSP_FW_CFG_FIFO_0_BASE_ADDR + \
            (ui32RbufOffset * BDSP_RAAGA_DSP_P_FIFO_PDQ);

        pTaskParams->sDspSchedulingBuffInfo.sRdbBasedSchedulingBuffer.ui32BaseAddr = BDSP_RAAGA_REGSET_ADDR_FOR_DSP( ui32RbufOffset + BDSP_RAAGA_P_FIFO_BASE_OFFSET );
        BDBG_MSG(("pTaskParams->sCircBuffer.ui32BaseAddr > %x", pTaskParams->sDspSchedulingBuffInfo.sRdbBasedSchedulingBuffer.ui32BaseAddr));

        pTaskParams->sDspSchedulingBuffInfo.sRdbBasedSchedulingBuffer.ui32EndAddr = BDSP_RAAGA_REGSET_ADDR_FOR_DSP( ui32RbufOffset + BDSP_RAAGA_P_FIFO_END_OFFSET );
        pTaskParams->sDspSchedulingBuffInfo.sRdbBasedSchedulingBuffer.ui32ReadAddr = BDSP_RAAGA_REGSET_ADDR_FOR_DSP( ui32RbufOffset + BDSP_RAAGA_P_FIFO_READ_OFFSET );
        pTaskParams->sDspSchedulingBuffInfo.sRdbBasedSchedulingBuffer.ui32WriteAddr = BDSP_RAAGA_REGSET_ADDR_FOR_DSP( ui32RbufOffset + BDSP_RAAGA_P_FIFO_WRITE_OFFSET );
        pTaskParams->sDspSchedulingBuffInfo.sRdbBasedSchedulingBuffer.ui32WrapAddr = BDSP_RAAGA_REGSET_ADDR_FOR_DSP( ui32RbufOffset + BDSP_RAAGA_P_FIFO_END_OFFSET );

        BDSP_MEM_P_FlushCache(pDevice->memHandle, pTaskParams, sizeof(BDSP_Raaga_P_TaskParamInfo));

        sCommand.uCommand.sStartTask.ui32EventEnableMask = pRaagaTask->eventEnabledMask ;

        pRaagaTask->lastEventType = sCommand.sCommandHeader.ui32CommandID;

        BKNI_ResetEvent(pRaagaTask->hEvent);

        BDBG_MSG(("\n"));
        BDBG_MSG(("===========Command information============="));
        BDBG_MSG(("==========================================="));
        BDBG_MSG(("sCommand.uCommand.sStartTask.eTaskAlgoType = %d",sCommand.uCommand.sStartTask.eTaskAlgoType));
        BDBG_MSG(("sCommand.uCommand.sStartTask.eTaskType = %d",sCommand.uCommand.sStartTask.eTaskType));
        BDBG_MSG(("sCommand.uCommand.sStartTask.ui32MasterTaskId = %d",sCommand.uCommand.sStartTask.ui32MasterTaskId));
        BDBG_MSG(("sCommand.uCommand.sStartTask.eDeadlineComputationFuncType = %d",sCommand.uCommand.sStartTask.eDeadlineComputationFuncType));
        BDBG_MSG(("sCommand.uCommand.sStartTask.ui32DramDeadlineConfigStructAddr = 0x%x",sCommand.uCommand.sStartTask.ui32DramDeadlineConfigStructAddr));
        BDBG_MSG(("sCommand.uCommand.sStartTask.ui32DramTaskConfigAddr = 0x%x",sCommand.uCommand.sStartTask.ui32DramTaskConfigAddr));
        BDBG_MSG(("sCommand.uCommand.sStartTask.ui32SyncQueueId = %d",sCommand.uCommand.sStartTask.ui32SyncQueueId));
        BDBG_MSG(("sCommand.uCommand.sStartTask.ui32AsyncQueueId = %d",sCommand.uCommand.sStartTask.ui32AsyncQueueId));
        BDBG_MSG(("sCommand.uCommand.sStartTask.sDramStackBuffer.ui32DramBufferAddress = 0x%x",sCommand.uCommand.sStartTask.sDramStackBuffer.ui32DramBufferAddress));
        BDBG_MSG(("sCommand.uCommand.sStartTask.sDramStackBuffer.ui32BufferSizeInBytes = %d",sCommand.uCommand.sStartTask.sDramStackBuffer.ui32BufferSizeInBytes));
        BDBG_MSG(("sCommand.uCommand.sStartTask.ui32EventEnableMask = %d",sCommand.uCommand.sStartTask.ui32EventEnableMask));
        BDBG_MSG(("sCommand.uCommand.sStartTask.ePPMCorrEnable = %d\n\n",sCommand.uCommand.sStartTask.ePPMCorrEnable));


        err = BDSP_Raaga_P_SendCommand(pDevice->hCmdQueue[pRaagaTask->settings.dspIndex], &sCommand,(void *)pRaagaTask);
        /*Accept the other Commands , After posting Start task Command */

  if (BERR_SUCCESS != err)
        {
            BDBG_ERR(("BDSP_Raaga_P_StartTask: START_TASK creation failed!"));
            err = BERR_TRACE(err);
            goto end;
        }

        /* Wait for Ack_Response_Received event w/ timeout */
        err = BKNI_WaitForEvent(pRaagaTask->hEvent, BDSP_RAAGA_START_STOP_EVENT_TIMEOUT_IN_MS);
        if (BERR_TIMEOUT == err)
        {
            BDBG_ERR(("BDSP_Raaga_P_StartTask: START_TASK ACK timeout! -- Interrupts to be tested"));
            err = BERR_TRACE(err);
            goto end;
        }

        /* Send command for the task , Only if the ack for the Start of the task is recieved */
        pRaagaTask->isStopped = false;

        eMsgType = BDSP_Raaga_P_MsgType_eSyn;
        err = BDSP_Raaga_P_GetMsg(pRaagaTask->hSyncMsgQueue, (void *)&sRsp,eMsgType);

        if (BERR_SUCCESS != err)
        {
            BDBG_ERR(("BDSP_Raaga_P_StartTask: Unable to read ACK!"));
            err = BERR_TRACE(err);
            goto end;
        }
        if ((sRsp.sCommonAckResponseHeader.eStatus != BERR_SUCCESS)||
            (sRsp.sCommonAckResponseHeader.ui32ResponseID != BDSP_RAAGA_START_TASK_RESPONSE_ID)||
            (sRsp.sCommonAckResponseHeader.ui32TaskID != pRaagaTask->taskId))
        {

            BDBG_ERR(("BDSP_Raaga_P_StartTask: START_TASK ACK not received successfully!eStatus = %d , ui32ResponseID = %d , ui32TaskID %d ",
                sRsp.sCommonAckResponseHeader.eStatus,sRsp.sCommonAckResponseHeader.ui32ResponseID,sRsp.sCommonAckResponseHeader.ui32TaskID));
            err = BERR_TRACE(sRsp.sCommonAckResponseHeader.eStatus);
            goto end;
        }

    }
    else if (pRaagaContext->settings.contextType  == BDSP_ContextType_eGraphics)
    {

    }

    /* Traverse through all stages in the task and set the running flag and task handle */
    BDSP_STAGE_TRAVERSE_LOOP_BEGIN(pRaagaTask->startSettings.primaryStage->pStageHandle, pStageIterator)
    BSTD_UNUSED(macroStId);
    BSTD_UNUSED(macroBrId);
    {
        BDBG_ASSERT(NULL != pStageIterator);
        pStageIterator->running = true;
        pStageIterator->pRaagaTask = pRaagaTask;
    }
    BDSP_STAGE_TRAVERSE_LOOP_END(pStageIterator);
    goto ret_success;

end:
err_gen_citinput:
err_download_fw:
    pDevice->taskDetails.numActiveTasks[dspIndex]--;

ret_success:
    BDBG_LEAVE(BDSP_Raaga_P_StartTask);
    return err;
}

/***********************************************************************
Name        :   BDSP_Raaga_P_StopTask

Type        :   PI Interface

Input       :   pTaskHandle -   Handle of the Task which needs to be Stopped.

Return      :   Error Code to return SUCCESS or FAILURE

Functionality   :   Following are the operations performed.
        1)  Send the Stop Command for the task depending on the Context of the task.
        2)  Set the Stopped variable.
        3)  Reset Paused, Command Counter and Decoder locked variables.
        4)  Set the Master task and Last event for the task as Invalid.
        5)  Clear the Start Settings for the Task.
***********************************************************************/

BERR_Code BDSP_Raaga_P_StopTask(
    void *pTaskHandle
    )
{
    BDSP_RaagaTask *pRaagaTask = (BDSP_RaagaTask *)pTaskHandle;
    BDSP_Raaga_P_Command sCommand;
    BDSP_Raaga_P_Response sRsp;
    BDSP_RaagaContext *pRaagaContext = (BDSP_RaagaContext *)pRaagaTask->pContext;
    BDSP_RaagaStage *pRaagaPrimaryStage = (BDSP_RaagaStage *)pRaagaTask->startSettings.primaryStage->pStageHandle;
    BDSP_Raaga  *pDevice= pRaagaContext->pDevice;
    BDSP_Raaga_P_MsgType      eMsgType;
    unsigned i = 0, dspIndex =0, lowerDspClkRate = 0;
    BERR_Code   err=BERR_SUCCESS;

    BDBG_ENTER(BDSP_Raaga_P_StopTask);

    BDBG_OBJECT_ASSERT(pRaagaTask, BDSP_RaagaTask);

    BKNI_Memset(&sCommand,0,sizeof(sCommand));
    BKNI_Memset(&sRsp,0,sizeof(sRsp));
    dspIndex = pRaagaTask->settings.dspIndex;

    BDBG_MSG(("Stop task: DSP %d",dspIndex));

    /* Traverse through all stages in the task and reset the running flag and task handle */
    BDSP_STAGE_TRAVERSE_LOOP_BEGIN(pRaagaTask->startSettings.primaryStage->pStageHandle, pStageIterator)
    BSTD_UNUSED(macroStId);
    BSTD_UNUSED(macroBrId);
    {
        pStageIterator->running = false;
        pStageIterator->pRaagaTask = NULL;
        if(pRaagaContext->contextWatchdogFlag != true)
        {
            /* Don't Release the Algorithm explicity here in Watchdog recovery.
                 All the algorithms are released together in Raaga Open during such recovery.
                 In a normal routine each task will release their algorithms individually*/
            BDSP_Raaga_P_ReleaseAlgorithm(pDevice, pStageIterator->algorithm);
        }
    }
    BDSP_STAGE_TRAVERSE_LOOP_END(pStageIterator)


    if (pRaagaContext->settings.contextType  == BDSP_ContextType_eAudio)
    {
        BDSP_RaagaCapture *pRaagaCapture;

        BKNI_AcquireMutex(pDevice->captureMutex);
        /* Disable all captures */
        BDSP_STAGE_TRAVERSE_LOOP_BEGIN(pRaagaTask->startSettings.primaryStage->pStageHandle, pStageIterator)
        BSTD_UNUSED(macroStId);
        BSTD_UNUSED(macroBrId);
        {
            for ( pRaagaCapture = BLST_S_FIRST(&pStageIterator->captureList);
                pRaagaCapture != NULL;
                pRaagaCapture = BLST_S_NEXT(pRaagaCapture, node) )
            {
                pRaagaCapture->enabled = false;
            }
        }
        BDSP_STAGE_TRAVERSE_LOOP_END(pStageIterator)
        BKNI_ReleaseMutex(pDevice->captureMutex);

        if (pRaagaContext->contextWatchdogFlag== false)
        {

            /* Send stop Task Command */
            sCommand.sCommandHeader.ui32CommandID = BDSP_RAAGA_STOP_TASK_COMMAND_ID;
            sCommand.sCommandHeader.ui32CommandCounter = pRaagaTask->commandCounter++;
            sCommand.sCommandHeader.ui32TaskID = pRaagaTask->taskId;
            sCommand.sCommandHeader.eResponseType = BDSP_Raaga_P_ResponseType_eResponseRequired;
            sCommand.sCommandHeader.ui32CommandSizeInBytes =  sizeof(BDSP_Raaga_P_Command);


            if (pRaagaTask->masterTaskId != BDSP_RAAGA_P_INVALID_TASK_ID)
            {
                sCommand.uCommand.sStopTask.eSchedulingMode = BDSP_Raaga_P_SchedulingMode_eSlave;
                sCommand.uCommand.sStopTask.ui32MasterTaskId = pRaagaTask->masterTaskId;
            }
            else
            {
                sCommand.uCommand.sStopTask.eSchedulingMode = BDSP_Raaga_P_SchedulingMode_eMaster;
                sCommand.uCommand.sStopTask.ui32MasterTaskId = BDSP_RAAGA_P_INVALID_TASK_ID;
            }

            if (pRaagaTask->startSettings.realtimeMode == BDSP_TaskRealtimeMode_eNonRealTime)
            {
                sCommand.uCommand.sStopTask.eTaskType = BDSP_Raaga_P_TaskType_eNonRealtime;
            }
            else
            {
                sCommand.uCommand.sStopTask.eTaskType = BDSP_Raaga_P_TaskType_eRealtime;
            }

            pRaagaTask->lastEventType = sCommand.sCommandHeader.ui32CommandID;

            BKNI_ResetEvent(pRaagaTask->hEvent);

            BKNI_EnterCriticalSection();
            err = BDSP_Raaga_P_SendCommand_isr(pDevice->hCmdQueue[dspIndex], &sCommand,(void *)pRaagaTask);
            /*Accept the other Commands , After posting Start task Command */
            pRaagaTask->isStopped = true;
            BKNI_LeaveCriticalSection();


            if (BERR_SUCCESS != err)
            {
                BDBG_ERR(("BDSP_Raaga_P_StopTask: STOP_TASK creation failed!"));
                err = BERR_TRACE(err);
                goto end;
            }
            /* Wait for Ack_Response_Received event w/ timeout */
            err = BKNI_WaitForEvent(pRaagaTask->hEvent, BDSP_RAAGA_START_STOP_EVENT_TIMEOUT_IN_MS);
            if (BERR_TIMEOUT == err)
            {
                BDBG_ERR(("BDSP_Raaga_P_StopTask: STOP_TASK ACK timeout!"));
                err = BERR_TRACE(err);
                goto end;
            }

            /* Send command for the task , Only if the ack for the Start of the task is recieved */

            eMsgType = BDSP_Raaga_P_MsgType_eSyn;
            err = BDSP_Raaga_P_GetMsg(pRaagaTask->hSyncMsgQueue, (void *)&sRsp,eMsgType);

            if (BERR_SUCCESS != err)
            {
                BDBG_ERR(("BDSP_Raaga_P_StopTask: Unable to read ACK!"));
                err = BERR_TRACE(err);
                goto end;
            }

            if ((sRsp.sCommonAckResponseHeader.eStatus != BERR_SUCCESS)||
                (sRsp.sCommonAckResponseHeader.ui32ResponseID != BDSP_RAAGA_STOP_TASK_RESPONSE_ID)||
                (sRsp.sCommonAckResponseHeader.ui32TaskID != pRaagaTask->taskId))
            {

                BDBG_ERR(("BDSP_Raaga_P_StopTask: STOP_TASK ACK not received successfully!eStatus = %d , ui32ResponseID = %d , ui32TaskID %d ",
                    sRsp.sCommonAckResponseHeader.eStatus,sRsp.sCommonAckResponseHeader.ui32ResponseID,sRsp.sCommonAckResponseHeader.ui32TaskID));
                err = BERR_TRACE(sRsp.sCommonAckResponseHeader.eStatus);
                goto end;
            }
        }
        else
        {
            pRaagaTask->isStopped = true;
        }
    }
    else if (pRaagaContext->settings.contextType  == BDSP_ContextType_eVideo)
    {
        if (pRaagaContext->contextWatchdogFlag== false)
        {

            /* Send stop Task Command */
            sCommand.sCommandHeader.ui32CommandID = BDSP_RAAGA_STOP_TASK_COMMAND_ID;
            sCommand.sCommandHeader.ui32CommandCounter = pRaagaTask->commandCounter++;
            sCommand.sCommandHeader.ui32TaskID = pRaagaTask->taskId;
            sCommand.sCommandHeader.eResponseType = BDSP_Raaga_P_ResponseType_eResponseRequired;
            sCommand.sCommandHeader.ui32CommandSizeInBytes =  sizeof(BDSP_Raaga_P_Command);


            if (pRaagaTask->startSettings.realtimeMode == BDSP_TaskRealtimeMode_eNonRealTime)
            {
                sCommand.uCommand.sStopTask.eTaskType = BDSP_Raaga_P_TaskType_eNonRealtime;
            }
            else
            {
                sCommand.uCommand.sStopTask.eTaskType = BDSP_Raaga_P_TaskType_eRealtime;
            }

            if (pRaagaTask->masterTaskId != BDSP_RAAGA_P_INVALID_TASK_ID)
            {
                sCommand.uCommand.sStopTask.eSchedulingMode = BDSP_Raaga_P_SchedulingMode_eSlave;
                sCommand.uCommand.sStopTask.ui32MasterTaskId = pRaagaTask->masterTaskId;
            }
            else
            {
                sCommand.uCommand.sStopTask.eSchedulingMode = BDSP_Raaga_P_SchedulingMode_eMaster;
                sCommand.uCommand.sStopTask.ui32MasterTaskId = BDSP_RAAGA_P_INVALID_TASK_ID;
            }

            pRaagaTask->lastEventType = sCommand.sCommandHeader.ui32CommandID;

            BKNI_ResetEvent(pRaagaTask->hEvent);

            BKNI_EnterCriticalSection();
            err = BDSP_Raaga_P_SendCommand_isr(pDevice->hCmdQueue[dspIndex], &sCommand,(void *)pRaagaTask);
            /*Accept the other Commands , After posting Start task Command */
            pRaagaTask->isStopped = true;
            BKNI_LeaveCriticalSection();


            if (BERR_SUCCESS != err)
            {
                BDBG_ERR(("BDSP_Raaga_P_StopTask: STOP_TASK creation failed!"));
                err = BERR_TRACE(err);
                goto end;
            }
            /* Wait for Ack_Response_Received event w/ timeout */
            err = BKNI_WaitForEvent(pRaagaTask->hEvent, BDSP_RAAGA_START_STOP_EVENT_TIMEOUT_IN_MS);
            if (BERR_TIMEOUT == err)
            {
                BDBG_ERR(("BDSP_Raaga_P_StopTask: STOP_TASK ACK timeout!"));
                err = BERR_TRACE(err);
                goto end;
            }

            /* Send command for the task , Only if the ack for the Start of the task is recieved */

            eMsgType = BDSP_Raaga_P_MsgType_eSyn;
            err = BDSP_Raaga_P_GetMsg(pRaagaTask->hSyncMsgQueue, (void *)&sRsp,eMsgType);

            if (BERR_SUCCESS != err)
            {
                BDBG_ERR(("BDSP_Raaga_P_StopTask: Unable to read ACK!"));
                err = BERR_TRACE(err);
                goto end;
            }

            if ((sRsp.sCommonAckResponseHeader.eStatus != BERR_SUCCESS)||
                (sRsp.sCommonAckResponseHeader.ui32ResponseID != BDSP_RAAGA_STOP_TASK_RESPONSE_ID)||
                (sRsp.sCommonAckResponseHeader.ui32TaskID != pRaagaTask->taskId))
            {

                BDBG_ERR(("BDSP_Raaga_P_StopTask: STOP_TASK ACK not received successfully!eStatus = %d , ui32ResponseID = %d , ui32TaskID %d ",
                    sRsp.sCommonAckResponseHeader.eStatus,sRsp.sCommonAckResponseHeader.ui32ResponseID,sRsp.sCommonAckResponseHeader.ui32TaskID));
                err = BERR_TRACE(sRsp.sCommonAckResponseHeader.eStatus);
                goto end;
            }
        }
        else
        {
            pRaagaTask->isStopped = true;
        }
    }
    else if (pRaagaContext->settings.contextType  == BDSP_ContextType_eVideoEncode)
    {
        /*Decrementing implictly the number of input for the VIDEO ENCODE case as we add the input internally in the START TASK*/
        pRaagaPrimaryStage->totalInputs--;

        if (pRaagaContext->contextWatchdogFlag== false)
        {

            /* Mask any interrupt that task might be using */
            if( true == pRaagaTask->startSettings.extInterruptConfig.enableInterrupts)
            {
                /* for all the enabled interrupts */
                for(i = 0; i < pRaagaTask->startSettings.extInterruptConfig.numInterrupts; i++)
                {
                    BDSP_Write32(pDevice->regHandle, \
                        BCHP_RAAGA_DSP_ESR_SI_MASK_SET + pDevice->dspOffset[dspIndex], \
                        (1 << pRaagaTask->startSettings.extInterruptConfig.interruptInfo[i].interruptBit));
                }
            }

            /* Send stop Task Command */
            sCommand.sCommandHeader.ui32CommandID = BDSP_RAAGA_STOP_TASK_COMMAND_ID;
            sCommand.sCommandHeader.ui32CommandCounter = pRaagaTask->commandCounter++;
            sCommand.sCommandHeader.ui32TaskID = pRaagaTask->taskId;
            sCommand.sCommandHeader.eResponseType = BDSP_Raaga_P_ResponseType_eResponseRequired;
            sCommand.sCommandHeader.ui32CommandSizeInBytes =  sizeof(BDSP_Raaga_P_Command);


            if (pRaagaTask->startSettings.realtimeMode == BDSP_TaskRealtimeMode_eNonRealTime)
            {
                sCommand.uCommand.sStopTask.eTaskType = BDSP_Raaga_P_TaskType_eNonRealtime;
            }
            else
            {
                sCommand.uCommand.sStopTask.eTaskType = BDSP_Raaga_P_TaskType_eRealtime;
            }

            if (pRaagaTask->masterTaskId != BDSP_RAAGA_P_INVALID_TASK_ID)
            {
                sCommand.uCommand.sStopTask.eSchedulingMode = BDSP_Raaga_P_SchedulingMode_eSlave;
                sCommand.uCommand.sStopTask.ui32MasterTaskId = pRaagaTask->masterTaskId;
            }
            else
            {
                sCommand.uCommand.sStopTask.eSchedulingMode = BDSP_Raaga_P_SchedulingMode_eMaster;
                sCommand.uCommand.sStopTask.ui32MasterTaskId = BDSP_RAAGA_P_INVALID_TASK_ID;
            }

            pRaagaTask->lastEventType = sCommand.sCommandHeader.ui32CommandID;

            BKNI_ResetEvent(pRaagaTask->hEvent);

            BKNI_EnterCriticalSection();
            err = BDSP_Raaga_P_SendCommand_isr(pDevice->hCmdQueue[dspIndex], &sCommand,(void *)pRaagaTask);
            /*Accept the other Commands , After posting Start task Command */
            pRaagaTask->isStopped = true;
            BKNI_LeaveCriticalSection();


            if (BERR_SUCCESS != err)
            {
                BDBG_ERR(("BDSP_Raaga_P_StopTask: STOP_TASK creation failed!"));
                err = BERR_TRACE(err);
                goto end;
            }
            /* Wait for Ack_Response_Received event w/ timeout */
            err = BKNI_WaitForEvent(pRaagaTask->hEvent, BDSP_RAAGA_START_STOP_EVENT_TIMEOUT_IN_MS);
            if (BERR_TIMEOUT == err)
            {
                BDBG_ERR(("BDSP_Raaga_P_StopTask: STOP_TASK ACK timeout!"));
                err = BERR_TRACE(err);
                goto end;
            }

            /* Send command for the task , Only if the ack for the Start of the task is recieved */

            eMsgType = BDSP_Raaga_P_MsgType_eSyn;
            err = BDSP_Raaga_P_GetMsg(pRaagaTask->hSyncMsgQueue, (void *)&sRsp,eMsgType);

            if (BERR_SUCCESS != err)
            {
                BDBG_ERR(("BDSP_Raaga_P_StopTask: Unable to read ACK!"));
                err = BERR_TRACE(err);
                goto end;
            }

            if ((sRsp.sCommonAckResponseHeader.eStatus != BERR_SUCCESS)||
                (sRsp.sCommonAckResponseHeader.ui32ResponseID != BDSP_RAAGA_STOP_TASK_RESPONSE_ID)||
                (sRsp.sCommonAckResponseHeader.ui32TaskID != pRaagaTask->taskId))
            {

                BDBG_ERR(("BDSP_Raaga_P_StopTask: STOP_TASK ACK not received successfully!eStatus = %d , ui32ResponseID = %d , ui32TaskID %d ",
                    sRsp.sCommonAckResponseHeader.eStatus,sRsp.sCommonAckResponseHeader.ui32ResponseID,sRsp.sCommonAckResponseHeader.ui32TaskID));
                err = BERR_TRACE(sRsp.sCommonAckResponseHeader.eStatus);
                goto end;
            }
        }
        else
        {
            pRaagaTask->isStopped = true;
        }
    }
    else if (pRaagaContext->settings.contextType  == BDSP_ContextType_eGraphics)
    {

    }

    else if (pRaagaContext->settings.contextType  == BDSP_ContextType_eScm)
    {
        if (pRaagaContext->contextWatchdogFlag== false)
        {

            /* Send stop Task Command */
            sCommand.sCommandHeader.ui32CommandID = BDSP_RAAGA_STOP_TASK_COMMAND_ID;
            sCommand.sCommandHeader.ui32CommandCounter = pRaagaTask->commandCounter++;
            sCommand.sCommandHeader.ui32TaskID = pRaagaTask->taskId;
            sCommand.sCommandHeader.eResponseType = BDSP_Raaga_P_ResponseType_eResponseRequired;
            sCommand.sCommandHeader.ui32CommandSizeInBytes =  sizeof(BDSP_Raaga_P_Command);


            if (pRaagaTask->startSettings.realtimeMode == BDSP_TaskRealtimeMode_eNonRealTime)
            {
                sCommand.uCommand.sStopTask.eTaskType = BDSP_Raaga_P_TaskType_eNonRealtime;
            }
            else
            {
                sCommand.uCommand.sStopTask.eTaskType = BDSP_Raaga_P_TaskType_eRealtime;
            }

            if (pRaagaTask->masterTaskId != BDSP_RAAGA_P_INVALID_TASK_ID)
            {
                sCommand.uCommand.sStopTask.eSchedulingMode = BDSP_Raaga_P_SchedulingMode_eSlave;
                sCommand.uCommand.sStopTask.ui32MasterTaskId = pRaagaTask->masterTaskId;
            }
            else
            {
                sCommand.uCommand.sStopTask.eSchedulingMode = BDSP_Raaga_P_SchedulingMode_eMaster;
                sCommand.uCommand.sStopTask.ui32MasterTaskId = BDSP_RAAGA_P_INVALID_TASK_ID;
            }

            pRaagaTask->lastEventType = sCommand.sCommandHeader.ui32CommandID;

            BKNI_ResetEvent(pRaagaTask->hEvent);

            BKNI_EnterCriticalSection();
            err = BDSP_Raaga_P_SendCommand_isr(pDevice->hCmdQueue[dspIndex], &sCommand,(void *)pRaagaTask);
            /*Accept the other Commands , After posting Start task Command */
            pRaagaTask->isStopped = true;
            BKNI_LeaveCriticalSection();


            if (BERR_SUCCESS != err)
            {
                BDBG_ERR(("BDSP_Raaga_P_StopTask: STOP_TASK creation failed!"));
                err = BERR_TRACE(err);
                goto end;
            }
            /* Wait for Ack_Response_Received event w/ timeout */
            err = BKNI_WaitForEvent(pRaagaTask->hEvent, BDSP_RAAGA_START_STOP_EVENT_TIMEOUT_IN_MS);
            if (BERR_TIMEOUT == err)
            {
                BDBG_ERR(("BDSP_Raaga_P_StopTask: STOP_TASK ACK timeout! -- Interrupts to be tested"));
                err = BERR_TRACE(err);
                goto end;
            }

            /* Send command for the task , Only if the ack for the Start of the task is recieved */

            eMsgType = BDSP_Raaga_P_MsgType_eSyn;
            err = BDSP_Raaga_P_GetMsg(pRaagaTask->hSyncMsgQueue, (void *)&sRsp,eMsgType);

            if (BERR_SUCCESS != err)
            {
                BDBG_ERR(("BDSP_Raaga_P_StopTask: Unable to read ACK!"));
                err = BERR_TRACE(err);
                goto end;
            }

            if ((sRsp.sCommonAckResponseHeader.eStatus != BERR_SUCCESS)||
                (sRsp.sCommonAckResponseHeader.ui32ResponseID != BDSP_RAAGA_STOP_TASK_RESPONSE_ID)||
                (sRsp.sCommonAckResponseHeader.ui32TaskID != pRaagaTask->taskId))
            {

                BDBG_ERR(("BDSP_Raaga_P_StopTask: STOP_TASK ACK not received successfully!eStatus = %d , ui32ResponseID = %d , ui32TaskID %d ",
                    sRsp.sCommonAckResponseHeader.eStatus,sRsp.sCommonAckResponseHeader.ui32ResponseID,sRsp.sCommonAckResponseHeader.ui32TaskID));
                err = BERR_TRACE(sRsp.sCommonAckResponseHeader.eStatus);
                goto end;
            }
        }
        else
        {
            pRaagaTask->isStopped = true;
        }
    }

    pRaagaTask->commandCounter     = 0;

    if(pRaagaContext->contextWatchdogFlag == false)
    {
        /* During normal scenario, unregister the task from the device where it is running on and clear the start settings*/
        pDevice->taskDetails.pRaagaTask[dspIndex][BDSP_RAAGA_GET_TASK_INDEX(pRaagaTask->taskId)]  = NULL;
        BKNI_AcquireMutex(pDevice->taskDetails.taskIdMutex);
        pDevice->taskDetails.taskId[dspIndex][BDSP_RAAGA_GET_TASK_INDEX(pRaagaTask->taskId)]   = true;
        BKNI_ReleaseMutex(pDevice->taskDetails.taskIdMutex);
        BKNI_Memset((void *)&pRaagaTask->startSettings, 0, sizeof(pRaagaTask->startSettings));
    }

    pRaagaTask->isStopped = true;
    pRaagaTask->lastEventType= 0xFFFF;
    pRaagaTask->masterTaskId= BDSP_RAAGA_P_INVALID_TASK_ID;
    pRaagaTask->commandCounter =0;
    pRaagaTask->paused=false;
    pRaagaTask->decLocked=false;

    if((pDevice->deviceWatchdogFlag == false) && (pRaagaContext->contextWatchdogFlag == true))
    {
        /* This is done to take care of stop task which is in watchdog recovery but device open has already happened.
             Imagine the scenario of both VEE and APE involved.
                   Book keeping functionalities like unregistering themselves from the Device is already happened at RaagaOpen
                   Stop Task now just need to clear the startsettings */
        BKNI_Memset((void *)&pRaagaTask->startSettings, 0, sizeof(pRaagaTask->startSettings));
    }

end:
    BKNI_DestroyEvent(pRaagaTask->hEvent);

    if( err == BERR_SUCCESS )
    {
        pDevice->taskDetails.numActiveTasks[dspIndex]--;
        if( !pDevice->taskDetails.numActiveTasks[dspIndex] )
        {
            BDSP_Raaga_P_GetLowerDspClkRate(pDevice->dpmInfo.defaultDspClkRate[dspIndex], &lowerDspClkRate);
            BDSP_Raaga_P_SetDspClkRate( (void * )pDevice, lowerDspClkRate, dspIndex );
        }
    }

    BDBG_LEAVE(BDSP_Raaga_P_StopTask);
    return err;
}

/***********************************************************************
Name        :   BDSP_Raaga_P_CreateTask

Type        :   PI Interface

Input       :   pContextHandle  -   Handle of the Context for which the task needs to created.
                pSettings           -   Settings of the Task to be created.
                pTask           -   Handle of the Task which is returned back to PI.

Return      :   Error Code to return SUCCESS or FAILURE

Functionality   :   Following are the operations performed.
        1)  Allocate and Intialise the memory for the Task Descriptor.
        2)  Intialise all the function pointers which will be used by the PI for further processing.
        3)  Allocate the Task related memory - CIT/Queues/Swap Buffer,etc.
        4)  Initliase the Task related parameters of Task Descriptors.
        5)  Install the Task Related Interrupts.
        6)  Error Handling if any required.
***********************************************************************/

BERR_Code BDSP_Raaga_P_CreateTask(
    void *pContextHandle,
    const BDSP_TaskCreateSettings *pSettings,
    BDSP_TaskHandle *pTask
    )
{
    BDSP_RaagaContext *pRaagaContext = (BDSP_RaagaContext *)pContextHandle;
    BDSP_RaagaTask *pRaagaTask, *pRaagaTask1;
    BERR_Code   err=BERR_SUCCESS;

    BDBG_ENTER(BDSP_Raaga_P_CreateTask);

    BDBG_OBJECT_ASSERT(pRaagaContext, BDSP_RaagaContext);

    *pTask = NULL;

    /*In the new CIT, BDSP_Context_Create() will no longer allocate any task memory or scratch memory
    Essentially, contexts will simply be for handling watchdog distribution to multiple PIs
    So the existing task creation has come to the the task_create function*/

    /* Allocate task structures and add to free task list */

    /*Allocation for one task only: not all like the context create time*/
/*  for ( i = 0; i < pSettings->maxTasks; i++ )*/
    {
        pRaagaTask = BKNI_Malloc(sizeof(BDSP_RaagaTask));
        if ( NULL == pRaagaTask )
        {
            BDBG_ERR(("No more tasks are available for this context.  Please increase the value of BDSP_ContextCreateSettings.maxTasks (currently %u).",
                pRaagaContext->settings.maxTasks));
            err = BERR_TRACE(BERR_OUT_OF_SYSTEM_MEMORY);
            goto err_malloc_task;
        }
        BKNI_Memset(pRaagaTask, 0, sizeof(BDSP_RaagaTask));
        BDBG_OBJECT_SET(pRaagaTask, BDSP_RaagaTask);

        /* Init task */
        BDSP_P_InitTask(&pRaagaTask->task, pRaagaTask);
        pRaagaTask->task.destroy = BDSP_Raaga_P_DestroyTask;
        pRaagaTask->task.start = BDSP_Raaga_P_StartTask;
        pRaagaTask->task.stop = BDSP_Raaga_P_StopTask;
        pRaagaTask->task.getDefaultTaskStartSettings = BDSP_Raaga_P_GetDefaultTaskStartSettings;
        pRaagaTask->task.retreiveGateOpenSettings = BDSP_Raaga_P_RetrieveGateOpenSettings;

        pRaagaTask->pContext = pRaagaContext;

        if (pRaagaContext->settings.contextType == BDSP_ContextType_eAudio)
        {
            pRaagaTask->task.pause= BDSP_Raaga_P_Pause;
            pRaagaTask->task.resume = BDSP_Raaga_P_Resume;
            pRaagaTask->task.advance = BDSP_Raaga_P_Advance;
            pRaagaTask->task.getAudioInterruptHandlers_isr = BDSP_Raaga_P_GetAudioInterruptHandlers_isr;
            pRaagaTask->task.setAudioInterruptHandlers_isr = BDSP_Raaga_P_SetAudioInterruptHandlers_isr;
            pRaagaTask->task.audioGapFill = BDSP_Raaga_P_AudioGapFill;
/* PAUSE-UNPAUSE */
            pRaagaTask->task.freeze = BDSP_Raaga_P_Freeze;
            pRaagaTask->task.unfreeze = BDSP_Raaga_P_UnFreeze;
/* PAUSE-UNPAUSE */
        }
        else if (pRaagaContext->settings.contextType == BDSP_ContextType_eVideo)
        {
            pRaagaTask->task.getPictureCount_isr = BDSP_Raaga_P_GetPictureCount_isr;
            pRaagaTask->task.peekAtPicture_isr = BDSP_Raaga_P_PeekAtPicture_isr;
            pRaagaTask->task.getNextPicture_isr = BDSP_Raaga_P_GetNextPicture_isr;
            pRaagaTask->task.releasePicture_isr = BDSP_Raaga_P_ReleasePicture_isr;
            pRaagaTask->task.getPictureDropPendingCount_isr = BDSP_Raaga_P_GetPictureDropPendingCount_isr;
            pRaagaTask->task.requestPictureDrop_isr = BDSP_Raaga_P_RequestPictureDrop_isr;
            pRaagaTask->task.displayInterruptEvent_isr = BDSP_Raaga_P_DisplayInterruptEvent_isr;
        }
        else if (BDSP_ContextType_eVideoEncode == pRaagaContext->settings.contextType)
        {
            pRaagaTask->task.getPictureBuffer_isr = BDSP_Raaga_P_GetPictureBuffer_isr;
            pRaagaTask->task.inputPictureBufferCount_isr = BDSP_Raaga_P_InputPictureBufferCount_isr;
            pRaagaTask->task.putPicture_isr = BDSP_Raaga_P_PutPicture_isr;
            pRaagaTask->task.putCcData_isr  = BDSP_Raaga_P_Put_CC_Data_isr;
/* PAUSE-UNPAUSE */
            pRaagaTask->task.getAudioInterruptHandlers_isr = BDSP_Raaga_P_GetAudioInterruptHandlers_isr;
            pRaagaTask->task.setAudioInterruptHandlers_isr = BDSP_Raaga_P_SetAudioInterruptHandlers_isr;
/* PAUSE-UNPAUSE */
        }
        else if (pRaagaContext->settings.contextType == BDSP_ContextType_eScm)
        {
            pRaagaTask->task.sendScmCommand = BDSP_Raaga_P_SendScmCommand;
        }

        err = BDSP_Raaga_P_AllocateTaskMemory((void *)pRaagaTask, pSettings);
        if ( err != BERR_SUCCESS )
        {
            err = BERR_TRACE(BERR_OUT_OF_SYSTEM_MEMORY);
            goto err_task_mem;
        }

        pRaagaTask1=pRaagaTask;
        /* Add to free task list */
        BLST_S_INSERT_HEAD(&pRaagaContext->freeTaskList, pRaagaTask1, node);
    }

    /* Find a free task, not required now: just start with the Task created above */
    /* pRaagaTask = BLST_S_FIRST(&pRaagaContext->freeTaskList);*/
    /* err =BDSP_Raaga_P_AllocateAndInitTask(pContextHandle,(void *)pRaagaTask,pSettings);*/

    /*BDSP_Raaga_P_AllocateAndInitTask is divided into BDSP_Raaga_P_InitParams_CreateTask during the task create and
           BDSP_Raaga_P_InitParams_StartTask during the Task Start*/
    err =BDSP_Raaga_P_InitParams_CreateTask(pContextHandle,(void *)pRaagaTask,pSettings);

    if ( BERR_SUCCESS!=err )
    {
        err = BERR_TRACE(err);
        goto err_init_task;
    }

    err = BDSP_Raaga_P_InterruptInstall((void *)pRaagaTask);
    if ( BERR_SUCCESS!=err )
    {
        err = BERR_TRACE(err);
        goto err_interrupt_install;
    }

    *pTask = &pRaagaTask->task;


    /*In the new CIT, contents from Context create, 'memory required for a task' will come here to Task create*/
    goto create_task_success;

err_interrupt_install:
err_init_task:
    BDSP_Raaga_P_FreeAndInvalidateTask((void *)pRaagaTask);
err_task_mem:

    /* Free this task, not all, since done in the task create */
    /*while ( (pTask = BLST_S_FIRST(&pRaagaContext->freeTaskList)) )*/
    {
        BDSP_Raaga_P_FreeTaskMemory((void *)pRaagaTask);
        /* Remove from list */
        BLST_S_REMOVE_HEAD(&pRaagaContext->freeTaskList, node);

        /* Destroy task */
        BDBG_OBJECT_DESTROY(pRaagaTask, BDSP_RaagaTask);
        BKNI_Free(pRaagaTask);
    }

err_malloc_task:
create_task_success:

    BDBG_LEAVE(BDSP_Raaga_P_CreateTask);
    return err;
}

/***********************************************************************
Name        :   BDSP_Raaga_P_DestroyTask

Type        :   PI Interface

Input       :   pTaskHandle -   Handle of the Task which needs to be destroyed.

Return      :   None

Functionality   :   Following are the operations performed.
        1)  Stop the task if it was not, before Destroying it.
        2)  Unistall the Interrupts for the task.
        3)  Remove the task from the allocated list for the Context.
        4)  Free the Task related memory - CIT/Queues/Swap Buffer,etc.
        5)  Free the Task descriptor.
***********************************************************************/

void BDSP_Raaga_P_DestroyTask(
    void *pTaskHandle
    )
{
    BDSP_RaagaTask *pTask = (BDSP_RaagaTask *)pTaskHandle;
    BERR_Code err;

    BDBG_ENTER(BDSP_Raaga_P_DestroyTask);

    BDBG_OBJECT_ASSERT(pTask, BDSP_RaagaTask);
    BDBG_ASSERT(pTask->allocated);

    if (pTask->isStopped == false)
    {
        BDBG_WRN(("BDSP_Raaga_P_DestroyTask: Task is till in Start state. Stopping it."));
        BDSP_Raaga_P_StopTask(pTaskHandle);
    }

    err = BDSP_Raaga_P_InterruptUninstall(pTaskHandle);
    if ( BERR_SUCCESS!=err )
    {
        err = BERR_TRACE(err);
    }

    err =BDSP_Raaga_P_FreeAndInvalidateTask(pTaskHandle);
    if ( BERR_SUCCESS!=err )
    {
        err = BERR_TRACE(err);
    }

    err = BDSP_Raaga_P_FreeTaskMemory(pTaskHandle);
    if ( BERR_SUCCESS!=err )
    {
        err = BERR_TRACE(err);
    }

    /* Destroy task */
    BLST_S_REMOVE_HEAD(&pTask->pContext->freeTaskList, node);
    BDBG_OBJECT_DESTROY(pTask, BDSP_RaagaTask);
    BKNI_Free(pTask);

    BDBG_LEAVE(BDSP_Raaga_P_DestroyTask);

    return;
}

static BERR_Code BDSP_DSP_P_DmaIn(  void *pDeviceHandle,
    uint8_t dataType,
    uint8_t swapType,
    uint32_t size,
    uint32_t src_addr,
    uint32_t dst_addr,
    unsigned uiDspOffset)
{
    uint32_t regVal, dmaCount = 0;
    BERR_Code err = BERR_SUCCESS;
    uint32_t tempsrc, tempdst, tempsize=0;

    BDSP_Raaga *pDevice = (BDSP_Raaga *)pDeviceHandle;

    BDBG_OBJECT_ASSERT(pDevice, BDSP_Raaga);

    BDSP_BDBG_MSG_LVL1 (("DMA In SRC = 0x%x, DST = 0x%x, SIZE = 0x%x", src_addr, dst_addr, size));

    tempsrc = src_addr;
    tempdst = dst_addr;
    tempsize = 0;

    while (size != 0)
    {
        tempsrc = tempsrc + tempsize;
        tempdst = tempdst + tempsize;

        if (size > BDSP_RAAGA_DMA_SIZE_PER_TRANSFER)
            tempsize = BDSP_RAAGA_DMA_SIZE_PER_TRANSFER;
        else
            tempsize = size;

        size = size - tempsize;

        BDSP_Write32(pDevice->regHandle,BCHP_RAAGA_DSP_DMA_SRC_ADDR_Q0 + uiDspOffset,tempsrc);
        BDSP_Write32(pDevice->regHandle,BCHP_RAAGA_DSP_DMA_DEST_ADDR_Q0 + uiDspOffset,tempdst);

        regVal = 0x0;
        regVal = (regVal & ~(BCHP_MASK(RAAGA_DSP_DMA_TRANSFER_Q0,SWAP_TYPE)))|
            (BCHP_FIELD_DATA(RAAGA_DSP_DMA_TRANSFER_Q0,SWAP_TYPE,swapType));
        regVal = (regVal & ~(BCHP_MASK(RAAGA_DSP_DMA_TRANSFER_Q0,DATA_TYPE)))|
            (BCHP_FIELD_DATA(RAAGA_DSP_DMA_TRANSFER_Q0,DATA_TYPE,dataType));
        regVal = (regVal & ~(BCHP_MASK(RAAGA_DSP_DMA_TRANSFER_Q0,TRANSFER_TYPE)))|
            (BCHP_FIELD_ENUM(RAAGA_DSP_DMA_TRANSFER_Q0,TRANSFER_TYPE,DMA_READ));
        regVal = (regVal & ~(BCHP_MASK(RAAGA_DSP_DMA_TRANSFER_Q0,TRANSFER_SIZE)))|
            (BCHP_FIELD_DATA(RAAGA_DSP_DMA_TRANSFER_Q0,TRANSFER_SIZE,tempsize));
        BDSP_Write32(pDevice->regHandle,BCHP_RAAGA_DSP_DMA_TRANSFER_Q0 + uiDspOffset,regVal);

        regVal = BDSP_RAAGA_DMA_BUSY;
        while (regVal)
        {
            regVal = BDSP_Read32(pDevice->regHandle,BCHP_RAAGA_DSP_DMA_STATUS + uiDspOffset);
            regVal = BCHP_GET_FIELD_DATA(regVal, RAAGA_DSP_DMA_STATUS, Q0_BUSY);
            dmaCount++;
            if (dmaCount==BDSP_RAAGA_DMA_TIMEOUT_COUNT)
            {
                BDBG_ERR(("DMA timeout: SRC Adr = 0x%x, DST Adr = 0x%x, "
                    "size = 0x%x", tempsrc, tempdst, tempsize));
                return BERR_TRACE(BERR_TIMEOUT);
            }
            BKNI_Delay(10);
        }

        BDSP_BDBG_MSG_LVL1(("DMA Done! for TempSRC Adr = 0x%x, TempDST Adr = 0x%x, "
            "Tempsize = 0x%x", tempsrc, tempdst, tempsize));
    }

    /* Clearing the Token ID for Queue 0/1/2/3. This needs to be done for other
        queues if they are used above. Clearning the token bits directly
        since the Q0_BUSY is dealt with above. */
#ifdef FIREPATH_BM
    regVal = 0;
#else
    regVal = BDSP_Read32 (pDevice->regHandle,
        BCHP_RAAGA_DSP_DMA_TOKEN_ID_CLR_Q0 + uiDspOffset);

    regVal &= ~(BCHP_MASK (RAAGA_DSP_DMA_TOKEN_ID_CLR_Q0,TOKEN_ID_BITS));
#endif
    regVal |= BCHP_FIELD_DATA(RAAGA_DSP_DMA_TOKEN_ID_CLR_Q0,TOKEN_ID_BITS,0xFFFFFFFF);

    BDSP_Write32 (pDevice->regHandle,
        BCHP_RAAGA_DSP_DMA_TOKEN_ID_CLR_Q0 + uiDspOffset,regVal);

#ifdef FIREPATH_BM
    regVal = 0;
#else
    regVal = BDSP_Read32 (pDevice->regHandle,
        BCHP_RAAGA_DSP_DMA_TOKEN_ID_CLR_Q1 + uiDspOffset);

    regVal &= ~(BCHP_MASK (RAAGA_DSP_DMA_TOKEN_ID_CLR_Q1,TOKEN_ID_BITS));
#endif
    regVal |= BCHP_FIELD_DATA(RAAGA_DSP_DMA_TOKEN_ID_CLR_Q1,TOKEN_ID_BITS,0xFFFFFFFF);

    BDSP_Write32 (pDevice->regHandle,
        BCHP_RAAGA_DSP_DMA_TOKEN_ID_CLR_Q1 + uiDspOffset,regVal);

#ifdef FIREPATH_BM
    regVal = 0;
#else
    regVal = BDSP_Read32 (pDevice->regHandle,
        BCHP_RAAGA_DSP_DMA_TOKEN_ID_CLR_Q2 + uiDspOffset);

    regVal &= ~(BCHP_MASK (RAAGA_DSP_DMA_TOKEN_ID_CLR_Q2,TOKEN_ID_BITS));
#endif
    regVal |= BCHP_FIELD_DATA(RAAGA_DSP_DMA_TOKEN_ID_CLR_Q2,TOKEN_ID_BITS,0xFFFFFFFF);

    BDSP_Write32 (pDevice->regHandle,
        BCHP_RAAGA_DSP_DMA_TOKEN_ID_CLR_Q2 + uiDspOffset,regVal);

#ifdef FIREPATH_BM
    regVal = 0;
#else
    regVal = BDSP_Read32 (pDevice->regHandle,
        BCHP_RAAGA_DSP_DMA_TOKEN_ID_CLR_Q3 + uiDspOffset);

    regVal &= ~(BCHP_MASK (RAAGA_DSP_DMA_TOKEN_ID_CLR_Q3,TOKEN_ID_BITS));
#endif
regVal |= BCHP_FIELD_DATA(RAAGA_DSP_DMA_TOKEN_ID_CLR_Q3,TOKEN_ID_BITS,0xFFFFFFFF);
    BDSP_Write32 (pDevice->regHandle,
        BCHP_RAAGA_DSP_DMA_TOKEN_ID_CLR_Q3 + uiDspOffset,regVal);


    return err;
}



/**********************************************************
Function: BDSP_Raaga_P_ResetHardware

Description : Reset's Raaga core and restores interrupts
                to the state it was before the reset

**********************************************************/
uint32_t BDSP_Raaga_P_ResetHardware(
    void        *pDeviceHandle,
    uint32_t    uiDspIndex)
{

    BDSP_Raaga_P_ResetRaagaCore(pDeviceHandle, uiDspIndex );

    BKNI_EnterCriticalSection();
    BDSP_Raaga_P_RestoreInterrupts_isr(pDeviceHandle, uiDspIndex );
    BKNI_LeaveCriticalSection();

    return BERR_SUCCESS;
}

/**********************************************************
Function: BDSP_Raaga_P_ResetHardware_isr

Description : To be called inside an isr-
                Reset's Raaga core and restores interrupts
                to the state it was before the reset

**********************************************************/
uint32_t BDSP_Raaga_P_ResetHardware_isr(
    void        *pDeviceHandle,
    uint32_t    uiDspIndex)
{

    BDSP_Raaga_P_ResetRaagaCore_isr(pDeviceHandle, uiDspIndex );

    BDSP_Raaga_P_RestoreInterrupts_isr(pDeviceHandle, uiDspIndex );

    return BERR_SUCCESS;
}

/**********************************************************
Function: BDSP_Raaga_P_ResetRaagaCore

Description : Reset's Raaga core.
                It masks watchdog interrupt too.

**********************************************************/
BERR_Code BDSP_Raaga_P_ResetRaagaCore(
    void                *pDeviceHandle,
    uint32_t    uiDspIndex)
{

    uint32_t regVal,uiOffset;
    BDSP_Raaga *pDevice = (BDSP_Raaga *)pDeviceHandle;

    BDBG_OBJECT_ASSERT(pDevice, BDSP_Raaga);

    /* Reset DSP processor and its peripherals */
    regVal = 0;
    uiOffset = pDevice->dspOffset[uiDspIndex];

#if BCHP_RAAGA_DSP_MISC_SOFT_RESET
    regVal = BDSP_Read32(pDevice->regHandle,BCHP_RAAGA_DSP_MISC_SOFT_RESET + uiOffset) ;
    regVal = (regVal & ~(BCHP_MASK(RAAGA_DSP_MISC_SOFT_RESET,RESET_DMA_B)))|
        (BCHP_FIELD_DATA(RAAGA_DSP_MISC_SOFT_RESET,RESET_DMA_B,0));
    regVal = (regVal & ~(BCHP_MASK(RAAGA_DSP_MISC_SOFT_RESET,RESET_PROC_B)))|
        (BCHP_FIELD_DATA(RAAGA_DSP_MISC_SOFT_RESET,RESET_PROC_B,0));
    regVal = (regVal & ~(BCHP_MASK(RAAGA_DSP_MISC_SOFT_RESET,RESET_B)))|
        (BCHP_FIELD_DATA(RAAGA_DSP_MISC_SOFT_RESET,RESET_B,0));
    BDSP_Write32(pDevice->regHandle,BCHP_RAAGA_DSP_MISC_SOFT_RESET + uiOffset, regVal);

#elif BCHP_RAAGA_DSP_MISC_1_REG_START


    regVal = BDSP_Read32(pDevice->regHandle,BCHP_RAAGA_DSP_MISC_SOFT_INIT + uiOffset) ;
    regVal = (regVal & ~(BCHP_MASK(RAAGA_DSP_MISC_SOFT_INIT, DO_SW_INIT)))|
     (BCHP_FIELD_DATA(RAAGA_DSP_MISC_SOFT_INIT, DO_SW_INIT,1));
    BDSP_Write32(pDevice->regHandle,BCHP_RAAGA_DSP_MISC_SOFT_INIT + uiOffset, regVal);

    regVal = BDSP_Read32(pDevice->regHandle,BCHP_RAAGA_DSP_MISC_REVISION + uiOffset) ;
    regVal = BDSP_Read32(pDevice->regHandle,BCHP_RAAGA_DSP_MISC_REVISION + uiOffset) ;

    BDBG_MSG(("REV ID VAL = 0x%x", regVal));

    regVal = BDSP_Read32(pDevice->regHandle,BCHP_RAAGA_DSP_MISC_SOFT_INIT + uiOffset) ;
    regVal &=  ~(BCHP_MASK(RAAGA_DSP_MISC_SOFT_INIT,INIT_PROC_B));
    BDSP_Write32(pDevice->regHandle,BCHP_RAAGA_DSP_MISC_SOFT_INIT + uiOffset, regVal);

    if( 0 == uiDspIndex )
    {
        /*RDB says no need of Read modify write.*/
        regVal = 0;
        regVal = (BCHP_FIELD_DATA(SUN_TOP_CTRL_SW_INIT_0_SET,    raaga0_sw_init,1));
        BDSP_Write32(pDevice->regHandle,BCHP_SUN_TOP_CTRL_SW_INIT_0_SET, regVal);

        BKNI_Delay(2);

        /*RDB says no need of Read modify write.*/
        regVal = 0;
        regVal = (BCHP_FIELD_DATA(SUN_TOP_CTRL_SW_INIT_0_CLEAR, raaga0_sw_init,1));
        BDSP_Write32(pDevice->regHandle,BCHP_SUN_TOP_CTRL_SW_INIT_0_CLEAR, regVal);

    }
    else if ( 1 == uiDspIndex )
    {
        /*RDB says no need of Read modify write.*/
        regVal = 0;
        regVal = (BCHP_FIELD_DATA(SUN_TOP_CTRL_SW_INIT_0_SET,    raaga1_sw_init,1));
        BDSP_Write32(pDevice->regHandle,BCHP_SUN_TOP_CTRL_SW_INIT_0_SET, regVal);

        BKNI_Delay(2);

        /*RDB says no need of Read modify write.*/
        regVal = 0;
        regVal = (BCHP_FIELD_DATA(SUN_TOP_CTRL_SW_INIT_0_CLEAR, raaga1_sw_init,1));
        BDSP_Write32(pDevice->regHandle,BCHP_SUN_TOP_CTRL_SW_INIT_0_CLEAR, regVal);
    }

#elif BCHP_RAAGA_DSP_MISC_SOFT_INIT
    regVal = BDSP_Read32(pDevice->regHandle,BCHP_RAAGA_DSP_MISC_SOFT_INIT + uiOffset) ;
    regVal = (regVal & ~(BCHP_MASK(RAAGA_DSP_MISC_SOFT_INIT, DO_SW_INIT)))|
       (BCHP_FIELD_DATA(RAAGA_DSP_MISC_SOFT_INIT, DO_SW_INIT,1));
    BDSP_Write32(pDevice->regHandle,BCHP_RAAGA_DSP_MISC_SOFT_INIT + uiOffset, regVal);

    regVal = BDSP_Read32(pDevice->regHandle,BCHP_RAAGA_DSP_MISC_REVISION + uiOffset) ;
    regVal = BDSP_Read32(pDevice->regHandle,BCHP_RAAGA_DSP_MISC_REVISION + uiOffset) ;
    BDBG_MSG((" BDSP REV ID value = 0x%x", regVal));


    regVal = BDSP_Read32(pDevice->regHandle,BCHP_RAAGA_DSP_MISC_SOFT_INIT + uiOffset) ;
    regVal &=  ~(BCHP_MASK(RAAGA_DSP_MISC_SOFT_INIT,INIT_PROC_B));
    BDSP_Write32(pDevice->regHandle,BCHP_RAAGA_DSP_MISC_SOFT_INIT + uiOffset, regVal);

        /*RDB says no need of Read modify write.*/
    regVal = 0;
#if BCHP_SUN_TOP_CTRL_SW_INIT_0_SET_raaga0_sw_init_MASK
    regVal = (BCHP_FIELD_DATA(SUN_TOP_CTRL_SW_INIT_0_SET, raaga0_sw_init,1));
#else
    regVal = (BCHP_FIELD_DATA(SUN_TOP_CTRL_SW_INIT_0_SET, raaga_sw_init,1));
#endif
    BDSP_Write32(pDevice->regHandle,BCHP_SUN_TOP_CTRL_SW_INIT_0_SET + uiOffset, regVal);

    BKNI_Delay(2);

    /*RDB says no need of Read modify write.*/
    regVal = 0;
#if BCHP_SUN_TOP_CTRL_SW_INIT_0_SET_raaga0_sw_init_MASK
    regVal = (BCHP_FIELD_DATA(SUN_TOP_CTRL_SW_INIT_0_CLEAR, raaga0_sw_init,1));
#else
    regVal = (BCHP_FIELD_DATA(SUN_TOP_CTRL_SW_INIT_0_CLEAR, raaga_sw_init,1));
#endif
    BDSP_Write32(pDevice->regHandle,BCHP_SUN_TOP_CTRL_SW_INIT_0_CLEAR + uiOffset, regVal);

#else
#error
#endif

    #ifdef BCHP_RAAGA_DSP_MISC_SOFT_RESET
                /* Withdraw only RESET_B reset */
        regVal = 0;
        regVal = (regVal & ~(BCHP_MASK(RAAGA_DSP_MISC_SOFT_RESET,RESET_B)))|
            (BCHP_FIELD_DATA(RAAGA_DSP_MISC_SOFT_RESET,RESET_B,1));
        BDSP_Write32(pDevice->regHandle,BCHP_RAAGA_DSP_MISC_SOFT_RESET + uiOffset, regVal);
        BDSP_BDBG_MSG_LVL1(("\nSoft reset: reset0_b withdrawn = 0x%x",regVal));

        regVal = BDSP_Read32(pDevice->regHandle,BCHP_RAAGA_DSP_MISC_SOFT_RESET + uiOffset);
        regVal = (regVal & ~(BCHP_MASK(RAAGA_DSP_MISC_SOFT_RESET,RESET_DMA_B)))|
            (BCHP_FIELD_DATA(RAAGA_DSP_MISC_SOFT_RESET,RESET_DMA_B,1));
        BDSP_Write32(pDevice->regHandle,BCHP_RAAGA_DSP_MISC_SOFT_RESET + uiOffset, regVal);
        BDSP_BDBG_MSG_LVL1(("\nSoft reset: SCBDMA withdrawn = 0x%x ****",regVal));
    #endif

    BDSP_BDBG_MSG_LVL1(("\nReady for code download on DSP %d ", uiDspIndex));

return BERR_SUCCESS;
}

/**********************************************************
Function: BDSP_Raaga_P_ResetRaagaCore_isr

Description : Reset's Raaga core.
                It masks watchdog interrupt too.

**********************************************************/
BERR_Code BDSP_Raaga_P_ResetRaagaCore_isr(
    void                *pDeviceHandle,
    uint32_t    uiDspIndex)
{

    uint32_t regVal,uiOffset;
    BDSP_Raaga *pDevice = (BDSP_Raaga *)pDeviceHandle;

    BDBG_OBJECT_ASSERT(pDevice, BDSP_Raaga);

    /* Reset DSP processor and its peripherals */
    regVal = 0;
    uiOffset = pDevice->dspOffset[uiDspIndex];

#if BCHP_RAAGA_DSP_MISC_SOFT_RESET
    regVal = BDSP_Read32_isr(pDevice->regHandle,BCHP_RAAGA_DSP_MISC_SOFT_RESET + uiOffset) ;
    regVal = (regVal & ~(BCHP_MASK(RAAGA_DSP_MISC_SOFT_RESET,RESET_DMA_B)))|
        (BCHP_FIELD_DATA(RAAGA_DSP_MISC_SOFT_RESET,RESET_DMA_B,0));
    regVal = (regVal & ~(BCHP_MASK(RAAGA_DSP_MISC_SOFT_RESET,RESET_PROC_B)))|
        (BCHP_FIELD_DATA(RAAGA_DSP_MISC_SOFT_RESET,RESET_PROC_B,0));
    regVal = (regVal & ~(BCHP_MASK(RAAGA_DSP_MISC_SOFT_RESET,RESET_B)))|
        (BCHP_FIELD_DATA(RAAGA_DSP_MISC_SOFT_RESET,RESET_B,0));
    BDSP_Write32_isr(pDevice->regHandle,BCHP_RAAGA_DSP_MISC_SOFT_RESET + uiOffset, regVal);

#elif BCHP_RAAGA_DSP_MISC_1_REG_START


    regVal = BDSP_Read32_isr(pDevice->regHandle,BCHP_RAAGA_DSP_MISC_SOFT_INIT + uiOffset) ;
    regVal = (regVal & ~(BCHP_MASK(RAAGA_DSP_MISC_SOFT_INIT, DO_SW_INIT)))|
     (BCHP_FIELD_DATA(RAAGA_DSP_MISC_SOFT_INIT, DO_SW_INIT,1));
    BDSP_Write32_isr(pDevice->regHandle,BCHP_RAAGA_DSP_MISC_SOFT_INIT + uiOffset, regVal);

    regVal = BDSP_Read32_isr(pDevice->regHandle,BCHP_RAAGA_DSP_MISC_REVISION + uiOffset) ;
    regVal = BDSP_Read32_isr(pDevice->regHandle,BCHP_RAAGA_DSP_MISC_REVISION + uiOffset) ;

    BDBG_MSG(("REV ID VAL = 0x%x", regVal));

    regVal = BDSP_Read32_isr(pDevice->regHandle,BCHP_RAAGA_DSP_MISC_SOFT_INIT + uiOffset) ;
    regVal &=  ~(BCHP_MASK(RAAGA_DSP_MISC_SOFT_INIT,INIT_PROC_B));
    BDSP_Write32_isr(pDevice->regHandle,BCHP_RAAGA_DSP_MISC_SOFT_INIT + uiOffset, regVal);

    if( 0 == uiDspIndex )
    {
        /*RDB says no need of Read modify write.*/
        regVal = 0;
        regVal = (BCHP_FIELD_DATA(SUN_TOP_CTRL_SW_INIT_0_SET,    raaga0_sw_init,1));
        BDSP_Write32_isr(pDevice->regHandle,BCHP_SUN_TOP_CTRL_SW_INIT_0_SET, regVal);

        BKNI_Delay(2);

        /*RDB says no need of Read modify write.*/
        regVal = 0;
        regVal = (BCHP_FIELD_DATA(SUN_TOP_CTRL_SW_INIT_0_CLEAR, raaga0_sw_init,1));
        BDSP_Write32_isr(pDevice->regHandle,BCHP_SUN_TOP_CTRL_SW_INIT_0_CLEAR, regVal);

    }
    else if ( 1 == uiDspIndex )
    {
        /*RDB says no need of Read modify write.*/
        regVal = 0;
        regVal = (BCHP_FIELD_DATA(SUN_TOP_CTRL_SW_INIT_0_SET,    raaga1_sw_init,1));
        BDSP_Write32_isr(pDevice->regHandle,BCHP_SUN_TOP_CTRL_SW_INIT_0_SET, regVal);

        BKNI_Delay(2);

        /*RDB says no need of Read modify write.*/
        regVal = 0;
        regVal = (BCHP_FIELD_DATA(SUN_TOP_CTRL_SW_INIT_0_CLEAR, raaga1_sw_init,1));
        BDSP_Write32_isr(pDevice->regHandle,BCHP_SUN_TOP_CTRL_SW_INIT_0_CLEAR, regVal);
    }

#elif BCHP_RAAGA_DSP_MISC_SOFT_INIT
    regVal = BDSP_Read32_isr(pDevice->regHandle,BCHP_RAAGA_DSP_MISC_SOFT_INIT + uiOffset) ;
    regVal = (regVal & ~(BCHP_MASK(RAAGA_DSP_MISC_SOFT_INIT, DO_SW_INIT)))|
       (BCHP_FIELD_DATA(RAAGA_DSP_MISC_SOFT_INIT, DO_SW_INIT,1));
    BDSP_Write32_isr(pDevice->regHandle,BCHP_RAAGA_DSP_MISC_SOFT_INIT + uiOffset, regVal);

    regVal = BDSP_Read32_isr(pDevice->regHandle,BCHP_RAAGA_DSP_MISC_REVISION + uiOffset) ;
    regVal = BDSP_Read32_isr(pDevice->regHandle,BCHP_RAAGA_DSP_MISC_REVISION + uiOffset) ;
    BDBG_MSG((" BDSP REV ID value = 0x%x", regVal));


    regVal = BDSP_Read32_isr(pDevice->regHandle,BCHP_RAAGA_DSP_MISC_SOFT_INIT + uiOffset) ;
    regVal &=  ~(BCHP_MASK(RAAGA_DSP_MISC_SOFT_INIT,INIT_PROC_B));
    BDSP_Write32_isr(pDevice->regHandle,BCHP_RAAGA_DSP_MISC_SOFT_INIT + uiOffset, regVal);

        /*RDB says no need of Read modify write.*/
    regVal = 0;
#if BCHP_SUN_TOP_CTRL_SW_INIT_0_SET_raaga0_sw_init_MASK
    regVal = (BCHP_FIELD_DATA(SUN_TOP_CTRL_SW_INIT_0_SET, raaga0_sw_init,1));
#else
    regVal = (BCHP_FIELD_DATA(SUN_TOP_CTRL_SW_INIT_0_SET, raaga_sw_init,1));
#endif
    BDSP_Write32_isr(pDevice->regHandle,BCHP_SUN_TOP_CTRL_SW_INIT_0_SET + uiOffset, regVal);

    BKNI_Delay(2);

    /*RDB says no need of Read modify write.*/
    regVal = 0;
#if BCHP_SUN_TOP_CTRL_SW_INIT_0_SET_raaga0_sw_init_MASK
    regVal = (BCHP_FIELD_DATA(SUN_TOP_CTRL_SW_INIT_0_CLEAR, raaga0_sw_init,1));
#else
    regVal = (BCHP_FIELD_DATA(SUN_TOP_CTRL_SW_INIT_0_CLEAR, raaga_sw_init,1));
#endif
    BDSP_Write32_isr(pDevice->regHandle,BCHP_SUN_TOP_CTRL_SW_INIT_0_CLEAR + uiOffset, regVal);

#else
#error
#endif

    #ifdef BCHP_RAAGA_DSP_MISC_SOFT_RESET
        /* Withdraw only RESET_B reset */
        regVal = 0;
        regVal = (regVal & ~(BCHP_MASK(RAAGA_DSP_MISC_SOFT_RESET,RESET_B)))|
            (BCHP_FIELD_DATA(RAAGA_DSP_MISC_SOFT_RESET,RESET_B,1));
        BDSP_Write32_isr(pDevice->regHandle,BCHP_RAAGA_DSP_MISC_SOFT_RESET + uiOffset, regVal);
        BDBG_MSG(("\n**** Soft reset: reset0_b withdrawn = 0x%x",regVal));

        regVal = BDSP_Read32_isr(pDevice->regHandle,BCHP_RAAGA_DSP_MISC_SOFT_RESET + uiOffset);
        regVal = (regVal & ~(BCHP_MASK(RAAGA_DSP_MISC_SOFT_RESET,RESET_DMA_B)))|
            (BCHP_FIELD_DATA(RAAGA_DSP_MISC_SOFT_RESET,RESET_DMA_B,1));
        BDSP_Write32_isr(pDevice->regHandle,BCHP_RAAGA_DSP_MISC_SOFT_RESET + uiOffset, regVal);
        BDBG_MSG(("\n**** Soft reset: SCBDMA withdrawn = 0x%x ****",regVal));
    #endif

    BDBG_MSG(("\n**** Ready for code download on DSP %d ", uiDspIndex));


return BERR_SUCCESS;
}


BERR_Code BDSP_Raaga_P_InitRaagaCore (void *pDeviceHandle,
                    unsigned uiDspIndex)
{

    unsigned uiOffset;
    BDSP_Raaga *pDevice = (BDSP_Raaga *)pDeviceHandle;
    BCHP_MemoryInfo stMemoryInfo;
    unsigned uiMemsize;
#ifdef BCHP_RAAGA_DSP_DMA_SCB_IF_CONFIG
    unsigned regVal;
#endif
    BDBG_OBJECT_ASSERT(pDevice, BDSP_Raaga);

    uiOffset = pDevice->dspOffset[uiDspIndex];

    BDSP_Write32(pDevice->regHandle, BCHP_RAAGA_DSP_DMA_MAX_SCB_BURST_SIZE_Q0 + uiOffset,
                    BCHP_RAAGA_DSP_DMA_MAX_SCB_BURST_SIZE_Q0_BURST_16JW);
    BDSP_Write32(pDevice->regHandle, BCHP_RAAGA_DSP_DMA_MAX_SCB_BURST_SIZE_Q1 + uiOffset,
                    BCHP_RAAGA_DSP_DMA_MAX_SCB_BURST_SIZE_Q0_BURST_16JW);
    BDSP_Write32(pDevice->regHandle, BCHP_RAAGA_DSP_DMA_MAX_SCB_BURST_SIZE_Q2 + uiOffset,
                    BCHP_RAAGA_DSP_DMA_MAX_SCB_BURST_SIZE_Q0_BURST_16JW);
    BDSP_Write32(pDevice->regHandle, BCHP_RAAGA_DSP_DMA_MAX_SCB_BURST_SIZE_Q3 + uiOffset,
                    BCHP_RAAGA_DSP_DMA_MAX_SCB_BURST_SIZE_Q0_BURST_16JW);

#if BCHP_RAAGA_DSP_DMA_MAX_SCB_BURST_SIZE_VQ4
    BDSP_Write32(pDevice->regHandle, BCHP_RAAGA_DSP_DMA_MAX_SCB_BURST_SIZE_VQ4 + uiOffset,
                    BCHP_RAAGA_DSP_DMA_MAX_SCB_BURST_SIZE_Q0_BURST_16JW);
#endif

#if BCHP_RAAGA_DSP_DMA_MAX_SCB_BURST_SIZE_VQ5
    BDSP_Write32(pDevice->regHandle, BCHP_RAAGA_DSP_DMA_MAX_SCB_BURST_SIZE_VQ5 + uiOffset,
                    BCHP_RAAGA_DSP_DMA_MAX_SCB_BURST_SIZE_Q0_BURST_16JW);
#endif

    BCHP_GetMemoryInfo(pDevice->regHandle, &stMemoryInfo);
    uiMemsize = 0;

    /* SCB0 Programming */
    if (stMemoryInfo.memc[0].size)
    {
        uiMemsize = (stMemoryInfo.memc[0].size >> 28);
        if (uiMemsize > 0x4)
        {
#ifdef BCHP_RAAGA_DSP_DMA_SCB_IF_CONFIG
            regVal = BDSP_Read32(pDevice->regHandle,BCHP_RAAGA_DSP_DMA_SCB_IF_CONFIG + uiOffset);
            BCHP_SET_FIELD_DATA( regVal, RAAGA_DSP_DMA_SCB_IF_CONFIG, SCB0_MS4BITS, (uiMemsize - 1) );
            BDSP_Write32(pDevice->regHandle,BCHP_RAAGA_DSP_DMA_SCB_IF_CONFIG + uiOffset, regVal);
#endif
        }
    }
    /* SCB1 Programming */
    if (stMemoryInfo.memc[1].size)
    {
        uiMemsize = ((stMemoryInfo.memc[0].size + stMemoryInfo.memc[1].size)  >> 28);
        if (uiMemsize > 0x8)
        {
#ifdef BCHP_RAAGA_DSP_DMA_SCB_IF_CONFIG
            regVal = BDSP_Read32(pDevice->regHandle,BCHP_RAAGA_DSP_DMA_SCB_IF_CONFIG + uiOffset);
            BCHP_SET_FIELD_DATA( regVal, RAAGA_DSP_DMA_SCB_IF_CONFIG, SCB1_MS4BITS, (uiMemsize - 1) );
            BDSP_Write32(pDevice->regHandle,BCHP_RAAGA_DSP_DMA_SCB_IF_CONFIG + uiOffset, regVal);
#endif
        }
    }

    /* SCB2 Programming */
    /* Nothing to do as of now. No register field definitions present */

return BERR_SUCCESS;
}

BERR_Code BDSP_Raaga_P_UnresetRaagaCore(void *pDeviceHandle,
                    unsigned uiDspIndex)
{

    unsigned uiOffset;
    uint32_t    regVal = 0;
    BDSP_Raaga *pDevice = (BDSP_Raaga *)pDeviceHandle;
    BDBG_OBJECT_ASSERT(pDevice, BDSP_Raaga);

    uiOffset = pDevice->dspOffset[uiDspIndex];

    /* Withdraw processor resets */
#if BCHP_RAAGA_DSP_MISC_SOFT_RESET
        regVal = BDSP_Read32(pDevice->regHandle,BCHP_RAAGA_DSP_MISC_SOFT_RESET + uiOffset);
        regVal = (regVal & ~(BCHP_MASK(RAAGA_DSP_MISC_SOFT_RESET,RESET_PROC_B)))|
            (BCHP_FIELD_DATA(RAAGA_DSP_MISC_SOFT_RESET,RESET_PROC_B,1));
        BDSP_Write32(pDevice->regHandle,BCHP_RAAGA_DSP_MISC_SOFT_RESET + uiOffset, regVal);


#elif BCHP_RAAGA_DSP_MISC_1_REG_START

    /*  uiOffset will decide whether dsp0 is being reset or dsp1  */
    regVal = BDSP_Read32(pDevice->regHandle,BCHP_RAAGA_DSP_MISC_SOFT_INIT + uiOffset);
        regVal = (regVal & ~(BCHP_MASK(RAAGA_DSP_MISC_SOFT_INIT,INIT_PROC_B)))|
            (BCHP_FIELD_DATA(RAAGA_DSP_MISC_SOFT_INIT,INIT_PROC_B,1));
        BDSP_Write32(pDevice->regHandle,BCHP_RAAGA_DSP_MISC_SOFT_INIT + uiOffset, regVal);


#elif BCHP_RAAGA_DSP_MISC_SOFT_INIT
        regVal = BDSP_Read32(pDevice->regHandle,BCHP_RAAGA_DSP_MISC_SOFT_INIT + uiOffset);
        regVal = (regVal & ~(BCHP_MASK(RAAGA_DSP_MISC_SOFT_INIT,INIT_PROC_B)))|
            (BCHP_FIELD_DATA(RAAGA_DSP_MISC_SOFT_INIT,INIT_PROC_B,1));
        BDSP_Write32(pDevice->regHandle,BCHP_RAAGA_DSP_MISC_SOFT_INIT + uiOffset, regVal);
#else
#error
#endif

return BERR_SUCCESS;

}

/**********************************************************
Function: BDSP_Raaga_P_DwnldResidentCode

Description : Resident code is downloaded into Raaga code
            and data space

**********************************************************/

BERR_Code BDSP_Raaga_P_DwnldResidentCode( void *pDeviceHandle,
                                                    uint32_t    uiDspIndex)

{
    BERR_Code err = BERR_SUCCESS;

    uint32_t    size;
    uint8_t     dmaDataType, swapType;
    raaga_dramaddr  physAddress;
    uint32_t    ui32ImemAddr = 0;
    unsigned uiOffset = 0;

    BDSP_Raaga *pDevice = (BDSP_Raaga *)pDeviceHandle;
    BDBG_OBJECT_ASSERT(pDevice, BDSP_Raaga);

    BDBG_ENTER(BDSP_Raaga_P_DwnldResidentCode);

    uiOffset = pDevice->dspOffset[uiDspIndex];

    /* Boot the processor */
    dmaDataType = 2;
    swapType = 0;

    /* DMA System code into SRAM */
    /* with SDK 1.22 onwards, sdk would do a imem to dmem copy */
    /* we need to ensure rdb vars is copied properly */
    ui32ImemAddr = 0x0;
    physAddress = pDevice->imgCache[BDSP_SystemImgId_eSystemCode].offset;
    size = pDevice->imgCache[BDSP_SystemImgId_eSystemCode].size;
    err = BDSP_DSP_P_DmaIn(pDeviceHandle, dmaDataType, swapType, size,  physAddress, ui32ImemAddr,uiOffset);
    if(err != BERR_SUCCESS){
        err = BERR_TRACE(err);
        goto dma_err;
    }

    /* DMA RDB Vars into IMEM */
    ui32ImemAddr = size - 1024;
    physAddress = pDevice->imgCache[BDSP_SystemImgId_eSystemRdbvars].offset;
    size = pDevice->imgCache[BDSP_SystemImgId_eSystemRdbvars].size;
    BDBG_ASSERT(1024 == size);
    err = BDSP_DSP_P_DmaIn(pDeviceHandle, dmaDataType, swapType, size, physAddress, ui32ImemAddr,uiOffset);
    if(err != BERR_SUCCESS){
        err = BERR_TRACE(err);
        goto dma_err;
    }

    dma_err:
    return err;
}


BERR_Code BDSP_Raaga_P_SetupDspBoot(void *pDeviceHandle,
                                uint32_t ui32DspIndex)
{
    BERR_Code err = BERR_SUCCESS;
    unsigned regVal, uiOffset = 0;

    BDSP_Raaga *pDevice = (BDSP_Raaga *)pDeviceHandle;

    uiOffset = pDevice->dspOffset[ui32DspIndex];

    BDSP_Raaga_P_InitRaagaCore (pDeviceHandle, ui32DspIndex);

    /* Initialize Mailbox5 register to zero */
    regVal = 0;
    BDSP_Write32(pDevice->regHandle,BCHP_RAAGA_DSP_PERI_SW_MAILBOX5 + uiOffset,
                            BDSP_RAAGA_PREBOOT_MAILBOX_PATTERN);
    regVal = BDSP_Read32(pDevice->regHandle,BCHP_RAAGA_DSP_PERI_SW_MAILBOX5 + uiOffset);
    if(regVal != BDSP_RAAGA_PREBOOT_MAILBOX_PATTERN)
    {
        BDBG_ASSERT(0);
    }
    BDSP_Write32(pDevice->regHandle,BCHP_RAAGA_DSP_PERI_SW_MAILBOX0 + uiOffset,
                            BDSP_RAAGA_PREBOOT_MAILBOX_PATTERN);
    regVal = BDSP_Read32(pDevice->regHandle,BCHP_RAAGA_DSP_PERI_SW_MAILBOX0 + uiOffset);
    if(regVal != BDSP_RAAGA_PREBOOT_MAILBOX_PATTERN)
    {
        BDBG_ASSERT(0);
    }

    err = BDSP_Raaga_P_DwnldResidentCode(pDeviceHandle, ui32DspIndex);
    if(err != BERR_SUCCESS)
        goto err_dwnld;



err_dwnld:
    return err;
}

BERR_Code BDSP_Raaga_P_BootDsp(void *pDeviceHandle,
                                uint32_t ui32DspIndex)
{
    BERR_Code err = BERR_SUCCESS;

    err = BDSP_Raaga_P_SetupDspBoot(pDeviceHandle, ui32DspIndex);
    if(err != BERR_SUCCESS)
        goto err_boot;

    BDSP_Raaga_P_UnresetRaagaCore (pDeviceHandle,ui32DspIndex);

err_boot:
    return err;
}
/**********************************************************
Function: BDSP_Raaga_P_Boot

Description : Downloads the resident code, Inits Raaga hardware with
            the settings which are different from default and Unresets
            Raaga.

**********************************************************/

BERR_Code BDSP_Raaga_P_Boot(
    void *pDeviceHandle)
{

    BERR_Code err = BERR_SUCCESS;
    unsigned uiDspIndex = 0;

    BDSP_Raaga *pDevice = (BDSP_Raaga *)pDeviceHandle;
    BDBG_OBJECT_ASSERT(pDevice, BDSP_Raaga);

    BDBG_ENTER(BDSP_Raaga_P_Boot);

    for(uiDspIndex = 0; uiDspIndex < pDevice->numDsp; uiDspIndex++)
    {
        err = BDSP_Raaga_P_BootDsp( pDeviceHandle, uiDspIndex);
    }

    BDBG_LEAVE(BDSP_Raaga_P_Boot);
    return err;
}

void BDSP_Raaga_P_Validate_Open_settings(void *pDeviceHandle)
{
    BDSP_Raaga *pDevice = (BDSP_Raaga *)pDeviceHandle;
    unsigned i=0;

    BDBG_OBJECT_ASSERT(pDevice, BDSP_Raaga);

    for(i=0;i<BDSP_AlgorithmType_eMax ; i++ )
    {
        if (pDevice->settings.maxAlgorithms[i] > BDSP_RAAGA_MAX_DWNLD_BUFS )
        {
            BDBG_ERR((" Please make sure the max Algorithms per algo, in Raaga open settings, is less than %d",BDSP_RAAGA_MAX_DWNLD_BUFS ));
            BDBG_ERR((" Try increasing the define -BDSP_RAAGA_MAX_DWNLD_BUFS,in bdsp_raaga_mm_priv.h, to continue testing"));
            BDBG_ASSERT(0);
        }
    }
    /*All Post process are always downloaded so hardcode it to 1 */
    pDevice->settings.maxAlgorithms[BDSP_AlgorithmType_eAudioProcessing] = 1;
}


void BDSP_Raaga_P_FreeScratchISbuffer(
            void *pDeviceHandle
            )
{
    int32_t i32DspIndex = 0,j=0;
    BDSP_Raaga *pDevice = (BDSP_Raaga *)pDeviceHandle;
    void *pAddress = NULL;

    for (i32DspIndex =0 ; i32DspIndex < (int32_t)pDevice->numDsp ; i32DspIndex++)
    {
        pAddress = NULL;
        BDSP_MEM_P_ConvertOffsetToCacheAddr(
            pDevice->memHandle,
            pDevice->memInfo.sScratchandISBuff[i32DspIndex].ui32DspScratchMemGrant.ui32DramBufferAddress,
            &pAddress);
        BDSP_MEM_P_FreeMemory((void *)pDevice->memHandle, pAddress);

        for(j = 0; j<BDSP_RAAGA_MAX_BRANCH_PER_TASK; j++)
        {
            pAddress = NULL;
            BDSP_MEM_P_ConvertOffsetToCacheAddr(
                pDevice->memHandle,
                pDevice->memInfo.sScratchandISBuff[i32DspIndex].InterStageIOBuff[j].sCircBuffer[0].ui32BaseAddr,
                &pAddress);
            BDSP_MEM_P_FreeMemory((void *)pDevice->memHandle, pAddress);

            pAddress = NULL;
            BDSP_MEM_P_ConvertOffsetToCacheAddr(
                pDevice->memHandle,
                pDevice->memInfo.sScratchandISBuff[i32DspIndex].InterStageIOGenericBuff[j].sCircBuffer.ui32BaseAddr,
                &pAddress);
            BDSP_MEM_P_FreeMemory((void *)pDevice->memHandle, pAddress);
        }
    }

    return;

}

/***********************************************************************
Name        :   BDSP_Raaga_P_Open

Type        :   BDSP Internal

Input       :   pDeviceHandle -Device Handle which needs to be opened/created

Return      :   Error Code to return SUCCESS or FAILURE

Functionality   :
    1)  Create the Mutexs for task, capture, Fifos, DspInterrupt, RDB, Watchdog.
    2)  Allocate and intitialise memories for CIT Buffers, Command Queue and Generic Response Queue.
    3)  Calculate and Allocate Scratch, Interstage & Interstage interface memory requirements.
    4)  Download the Firmware Executables.
    5)  Create/Initialise Command Queue for each DSP.
    6)  Create/Initialise Response Queue for each DSP.
    7)  Initialise the Hardware for each DSP.
    8)  Install Acknowledgment for each DSP.
***********************************************************************/
BERR_Code BDSP_Raaga_P_Open(
    void *pDeviceHandle
    )
{
    BERR_Code ret = BERR_SUCCESS;
    unsigned uiOffset=0, index=0,dspCfgRamSize=0,i=0;
    raaga_dramaddr  ui32PhysicalAddr=0;
    uint8_t *pFifoPtr=0;
    int32_t i32DspIndex = 0;
    uint32_t    ui32DebugFifoOffset=0,ui32DebugType=0;
    BDSP_Raaga_P_MsgQueueHandle hMsgQueue;
    BDSP_Raaga_P_Command sCommand;

    BDSP_Raaga *pDevice = (BDSP_Raaga *)pDeviceHandle;
    BDBG_OBJECT_ASSERT(pDevice, BDSP_Raaga);

    BDBG_ENTER(BDSP_Raaga_P_Open);

    BDBG_MSG((" device settings : auth enabled = %d", pDevice->settings.authenticationEnabled));

    BDSP_Raaga_P_Validate_Open_settings(pDeviceHandle);

    if (pDevice->deviceWatchdogFlag == false)
    {
        if (pDevice->settings.authenticationEnabled == true)
            pDevice->settings.preloadImages = true;

        ret = BKNI_CreateMutex(&(pDevice->taskDetails.taskIdMutex));
        BDBG_ASSERT(ret == BERR_SUCCESS);
        ret = BKNI_CreateMutex(&(pDevice->captureMutex));
        BDBG_ASSERT(ret == BERR_SUCCESS);

        for (i=0 ; i < pDevice->numDsp; i++)
        {
            for (index=0 ; index< BDSP_RAAGA_MAX_FW_TASK_PER_DSP; index++)
            {
                pDevice->taskDetails.taskId[i][index] =true;
                pDevice->taskDetails.pRaagaTask[i][index] =NULL;
            }

            for (index=0;index<BDSP_RAAGA_NUM_FIFOS;index++)
            {
                pDevice->dspFifo[i][index] = false;
            }

            ret = BKNI_CreateMutex(&(pDevice->fifoIdMutex[i]));
            BDBG_ASSERT(ret == BERR_SUCCESS);

            /* Initialize (free) all interrupts to dsp */
            for (index=0;index<BDSP_RAAGA_MAX_INTERRUPTS_PER_DSP;index++)
            {
                pDevice->dspInterrupts[i][index] = false;
            }
            ret = BKNI_CreateMutex(&(pDevice->dspInterruptMutex[i]));
            BDBG_ASSERT(ret == BERR_SUCCESS);
            /* Initialize (free) all RDB of DSP */
            for (index=0;index<BDSP_RAAGA_RDB_REGISTERS;index++)
            {
                pDevice->rdbRegisters[i][index] = false;
            }
            ret = BKNI_CreateMutex(&(pDevice->rdbRegistersMutex[i]));
            BDBG_ASSERT(ret == BERR_SUCCESS);
        }
        ret = BKNI_CreateMutex(&(pDevice->watchdogMutex));
        BDBG_ASSERT(ret == BERR_SUCCESS);

        ret = BDSP_Raaga_P_AllocateInitMemory (pDeviceHandle);
        if (ret != BERR_SUCCESS)
        {
            ret = BERR_TRACE(ret);
            goto err_allocate_initmem;
        }
        ret = BDSP_MM_P_CalcandAllocScratchISbufferReq(pDevice);/*allocation of =DSP scratch+InterstageIO+IO Generic*/
        if (ret != BERR_SUCCESS)
        {
            ret = BERR_TRACE(ret);
            goto err_allocate_scratchISmem;
        }
    }
    /* Intialise libDspControl handle */
    {
        DSP_PARAMETERS dsp_parameters;
        DSP_RET  eRetVal;
        dsp_parameters.hReg = ((BDSP_Raaga *)pDeviceHandle)->regHandle;      /* a BREG_Handle */
        dsp_parameters.hMem = ((BDSP_Raaga *)pDeviceHandle)->memHandle;      /* a BMEM_Heap_Handle */
        eRetVal = DSP_init(&(((BDSP_Raaga *)pDeviceHandle)->memInfo.sLibDsp), &dsp_parameters);
        BDBG_ASSERT(eRetVal == DSP_SUCCESS);

    }

    /* If Fw verification is enabled, then don't download the Executable again
    in watchdog recovery */
    if (!((pDevice->settings.authenticationEnabled == true)
        && (pDevice->deviceWatchdogFlag == true)))
    {
        ret = BDSP_Raaga_P_Alloc_DwnldFwExec(pDeviceHandle);
        if (ret != BERR_SUCCESS)
        {
            ret = BERR_TRACE(BDSP_ERR_DOWNLOAD_FAILED);
            goto err_downloadfw;
        }
    }

    for (i32DspIndex =0 ; i32DspIndex < (int32_t)pDevice->numDsp ; i32DspIndex++)
    {
        /*For Multi DSP Chips, uiOffset needs to be initialized as per RDB address.*/
        uiOffset = pDevice->dspOffset[i32DspIndex] ;

        /* Initialize entire DSP configuration RAM to zero */
        /* Skip overwriting 17 as that is used for FW dbg buffer */
        /*RAAGA_FIFO_DRAMLOGS is the first debug FIFO after the 64 FIFO's in new RDB*/
        dspCfgRamSize = BCHP_RAAGA_DSP_FW_CFG_FIFO_DRAMLOGS_READ_ADDR - RAAGA_DSP_FW_CFG_PAGE_START;
        for (index = 0; index < dspCfgRamSize; index+=4)
        {
            BDSP_Write32(pDevice->regHandle, RAAGA_DSP_FW_CFG_PAGE_START +
                uiOffset + index, 0x0);
        }

        BDSP_MEM_P_ConvertAddressToOffset(pDevice->memHandle,pDevice->memInfo.pDSPFifoAddrStruct[i32DspIndex], &ui32PhysicalAddr);

        BDSP_Write32(pDevice->regHandle,BCHP_RAAGA_DSP_FW_CFG_HOST2DSPCMD_FIFO0_BASEADDR +
            uiOffset, ui32PhysicalAddr + (BDSP_RAAGA_NUM_EXTRA_FIFOS*sizeof(BDSP_AF_P_sDRAM_CIRCULAR_BUFFER)));
        /* Fill up this structure */
        ui32PhysicalAddr = BDSP_RAAGA_REGSET_ADDR_FOR_DSP(BCHP_RAAGA_DSP_FW_CFG_FIFO_0_BASE_ADDR + uiOffset + BDSP_RAAGA_FIFO_0_INDEX*(BCHP_RAAGA_DSP_FW_CFG_FIFO_1_BASE_ADDR-BCHP_RAAGA_DSP_FW_CFG_FIFO_0_BASE_ADDR));
        pFifoPtr = (uint8_t *)pDevice->memInfo.pDSPFifoAddrStruct[i32DspIndex];
        for (i=0;i<BDSP_RAAGA_NUM_FIFOS;i++)
        {
            BDSP_P_MemWrite32(pDevice->memHandle,pFifoPtr,ui32PhysicalAddr); /* base */
            pFifoPtr += 4;
            BDSP_P_MemWrite32(pDevice->memHandle,pFifoPtr,ui32PhysicalAddr + 4); /* end */
            pFifoPtr += 4;
            BDSP_P_MemWrite32(pDevice->memHandle,pFifoPtr,ui32PhysicalAddr + 12); /* read */
            pFifoPtr += 4;
            BDSP_P_MemWrite32(pDevice->memHandle,pFifoPtr,ui32PhysicalAddr + 8); /* write */
            pFifoPtr += 4;
            BDSP_P_MemWrite32(pDevice->memHandle,pFifoPtr,ui32PhysicalAddr + 4); /* wrap */
            pFifoPtr += 4;
            ui32PhysicalAddr += 4*(BDSP_RAAGA_NUM_PTR_PER_FIFO-1);
        }

        for (ui32DebugType = 0; ui32DebugType < BDSP_Raaga_DebugType_eLast; ui32DebugType++)
        {
            ui32DebugFifoOffset = (BCHP_RAAGA_DSP_FW_CFG_FIFO_1_BASE_ADDR - BCHP_RAAGA_DSP_FW_CFG_FIFO_0_BASE_ADDR)*(BDSP_RAAGA_DEBUG_FIFO_START_INDEX + ui32DebugType);
            BDSP_MEM_P_ConvertAddressToOffset(pDevice->memHandle,(void *)pDevice->memInfo.pFwDebugBuf[i32DspIndex][ui32DebugType].pAddr, &ui32PhysicalAddr);

            /*BDBG_ERR(("uiVirtualAddr%d = %x\n\n", ui32DebugType, pDevice->memInfo.pFwDebugBuf[i32DspIndex][ui32DebugType].ui32Addr));
            BDBG_ERR(("ui32PhysicalAddr%d = %x\n\n", ui32DebugType, ui32PhysicalAddr));
            BDBG_ERR(("FIFO BASE%d = %x\n\n", ui32DebugType, BCHP_RAAGA_DSP_FW_CFG_FIFO_0_BASE_ADDR + ui32DebugFifoOffset +uiOffset));*/
            if(ui32DebugType != BDSP_Raaga_DebugType_eTargetPrintf)
            {
                BDSP_Write32(pDevice->regHandle,BCHP_RAAGA_DSP_FW_CFG_FIFO_0_BASE_ADDR + ui32DebugFifoOffset +
                    uiOffset, ui32PhysicalAddr);
                BDSP_Write32(pDevice->regHandle,BCHP_RAAGA_DSP_FW_CFG_FIFO_0_READ_ADDR + ui32DebugFifoOffset +
                    uiOffset, ui32PhysicalAddr);
                BDSP_Write32(pDevice->regHandle,BCHP_RAAGA_DSP_FW_CFG_FIFO_0_WRITE_ADDR + ui32DebugFifoOffset +
                    uiOffset, ui32PhysicalAddr);
                BDSP_MEM_P_ConvertAddressToOffset(pDevice->memHandle,
                    (void *)((uint8_t *)pDevice->memInfo.pFwDebugBuf[i32DspIndex][ui32DebugType].pAddr +
                    pDevice->memInfo.pFwDebugBuf[i32DspIndex][ui32DebugType].ui32Size), &ui32PhysicalAddr);
                BDSP_Write32(pDevice->regHandle,BCHP_RAAGA_DSP_FW_CFG_FIFO_0_END_ADDR + ui32DebugFifoOffset +
                    uiOffset, ui32PhysicalAddr);
            }
            else{
                    TB_init(&(((BDSP_Raaga *)pDeviceHandle)->memInfo.sTbTargetPrint[i32DspIndex]),
                            &(((BDSP_Raaga *)pDeviceHandle)->memInfo.sLibDsp),
                            BCHP_RAAGA_DSP_FW_CFG_FIFO_0_BASE_ADDR + ui32DebugFifoOffset + uiOffset,
                            DSP_ADDRSPACE_SHARED,
                            ui32PhysicalAddr,
                            DSP_ADDRSPACE_SYSTEM,
                            pDevice->memInfo.pFwDebugBuf[i32DspIndex][ui32DebugType].ui32Size / 1024,
                            TB_NO_NAME);

            }
        }

        if (pDevice->deviceWatchdogFlag == true)
        {
            hMsgQueue =  pDevice->hCmdQueue[i32DspIndex];
        }
        /*Command Queue*/
        if(pDevice->deviceWatchdogFlag)
        {
            ret = BDSP_Raaga_P_InitMsgQueue(&(pDevice->memInfo.cmdQueueParams[i32DspIndex]), pDevice->memHandle,
                pDevice->regHandle, uiOffset,&hMsgQueue);
        }
        else
        {
            ret = BDSP_Raaga_P_CreateMsgQueue(&(pDevice->memInfo.cmdQueueParams[i32DspIndex]), pDevice->memHandle,
                pDevice->regHandle, uiOffset,&hMsgQueue);
        }
        if (BERR_SUCCESS != ret)
        {
            BDBG_ERR(("BDSP_RAAGA_P_Open: Cmd queue creation failed!"));
            goto err_create_cmdqueue;

        }
        if (pDevice->deviceWatchdogFlag == false)
        {
            pDevice->hCmdQueue[i32DspIndex] = hMsgQueue;
        }

        if (pDevice->deviceWatchdogFlag == true)
        {
            hMsgQueue = pDevice->hGenRspQueue[i32DspIndex] ;
        }
        /*Generic response Queue*/
        if(pDevice->deviceWatchdogFlag)
        {
            ret = BDSP_Raaga_P_InitMsgQueue(&(pDevice->memInfo.genRspQueueParams[i32DspIndex]), pDevice->memHandle,
                pDevice->regHandle, uiOffset,&hMsgQueue);
        }
        else
        {
            ret = BDSP_Raaga_P_CreateMsgQueue(&(pDevice->memInfo.genRspQueueParams[i32DspIndex]), pDevice->memHandle,
                pDevice->regHandle, uiOffset,&hMsgQueue);
        }

        /* Program command queue & generic response queue */
        BDSP_Write32(pDevice->regHandle,BCHP_RAAGA_DSP_FW_CFG_HOST2DSPCMD_FIFO_ID +
            uiOffset, pDevice->memInfo.cmdQueueParams[i32DspIndex].i32FifoId);
        BDSP_Write32(pDevice->regHandle,BCHP_RAAGA_DSP_FW_CFG_SW_UNUSED1 +
            uiOffset, pDevice->memInfo.genRspQueueParams[i32DspIndex].i32FifoId);

        if (BERR_SUCCESS != ret)
        {
            BDBG_ERR(("BDSP_RAAGA_P_Open: Generic Response queue creation failed!"));
            goto err_create_genqueue;
        }
        if (pDevice->deviceWatchdogFlag == false)
        {
            pDevice->hGenRspQueue[i32DspIndex] = hMsgQueue;
        }
        if (pDevice->deviceWatchdogFlag == false)
        {
            for (i=0;i<BDSP_RAAGA_NUM_FIFOS;i++)
            {
                pDevice->dspFifo[i32DspIndex][i] = false;
            }
            pDevice->dspFifo[i32DspIndex][BDSP_RAAGA_FIFO_CMD-BDSP_RAAGA_FIFO_0_INDEX] = true;
            pDevice->dspFifo[i32DspIndex][BDSP_RAAGA_FIFO_GENERIC_RSP-BDSP_RAAGA_FIFO_0_INDEX] = true;
            pDevice->dspFifo[i32DspIndex][BDSP_RAAGA_FIFO_DRAMLOGS] = true;
        }

        /* Need to send a command to send the Swap Memory Address */
        sCommand.sCommandHeader.ui32CommandID           = BDSP_RAAGA_GET_SYSTEM_SWAP_MEMORY_COMMAND_ID;
        sCommand.sCommandHeader.ui32CommandCounter      = 0;
        sCommand.sCommandHeader.ui32TaskID              = 0;
        sCommand.sCommandHeader.eResponseType           = BDSP_Raaga_P_ResponseType_eNone;
        sCommand.sCommandHeader.ui32CommandSizeInBytes  =  sizeof(BDSP_Raaga_P_Command);

        BDSP_MEM_P_ConvertAddressToOffset(pDevice->memHandle,(void *)pDevice->memInfo.sRaagaSwapMemoryBuf[i32DspIndex].pAddr, &ui32PhysicalAddr);
        sCommand.uCommand.sSystemSwapMemCommand.ui32SystemSwapDramMemAddr           = ui32PhysicalAddr;

        BDBG_MSG(("System Swap memory DRAM address is 0x%x", ui32PhysicalAddr));
        ret = BDSP_Raaga_P_SendCommand(
                        pDevice->hCmdQueue[i32DspIndex], &sCommand,(void *)NULL);

    }

    BDBG_LOG(("BDSP Firmware Version %dp%dp%dp%d",
                                BDSP_sRaagaVersion.majorVersion,
                                BDSP_sRaagaVersion.minorVersion,
                                BDSP_sRaagaVersion.branchVersion,
                                BDSP_sRaagaVersion.branchSubVersion));
    goto open_success;

err_create_genqueue:
    BDSP_Raaga_P_DestroyMsgQueue(pDevice->hCmdQueue[i32DspIndex],
        pDevice->regHandle, pDevice->dspOffset[i32DspIndex]);
err_create_cmdqueue:
    i32DspIndex--;
    for(;i32DspIndex >= 0; i32DspIndex--)
    {
        BDSP_Raaga_P_DestroyMsgQueue(pDevice->hGenRspQueue[i32DspIndex],
            pDevice->regHandle, pDevice->dspOffset[i32DspIndex]);
        BDSP_Raaga_P_DestroyMsgQueue(pDevice->hCmdQueue[i32DspIndex],
            pDevice->regHandle, pDevice->dspOffset[i32DspIndex]);
    }
err_downloadfw:
    BDSP_Raaga_P_FreeScratchISbuffer(pDeviceHandle);
err_allocate_scratchISmem:
    BDSP_Raaga_P_FreeInitMemory(pDeviceHandle);

err_allocate_initmem:
    if (pDevice->deviceWatchdogFlag == false)
    {
        BKNI_DestroyMutex(pDevice->taskDetails.taskIdMutex);
        BKNI_DestroyMutex(pDevice->captureMutex);
        for (i=0 ; i < pDevice->numDsp; i++)
        {
            BKNI_DestroyMutex(pDevice->fifoIdMutex[i]);
            BKNI_DestroyMutex(pDevice->dspInterruptMutex[i]);
            BKNI_DestroyMutex(pDevice->rdbRegistersMutex[i]);
        }
        BKNI_DestroyMutex(pDevice->watchdogMutex);
    }

open_success:
    BDBG_LEAVE(BDSP_Raaga_P_Open);
    return ret;
}

void BDSP_Raaga_P_Reset(void *pDeviceHandle)
{
    uint32_t ui32DspIndex;
    BDSP_Raaga *pDevice = (BDSP_Raaga *)pDeviceHandle;

    for(ui32DspIndex = 0; ui32DspIndex < pDevice->numDsp; ui32DspIndex++)
        BDSP_Raaga_P_ResetHardware(pDeviceHandle, ui32DspIndex);
    return;
}

/***********************************************************************
Name        :   BDSP_Raaga_P_GetNumberOfDsp

Type        :   BDSP Internal

Input       :   boxHandle   -   Box Handle provided by the PI.
                pNumDsp -   Pointer to return the number of DSP in the System.

Return      :   Error Code to return SUCCESS or FAILURE

Functionality   :   Following are the operations performed.
        1)  Calculate the Number of DSP based on the BOX MODE.
***********************************************************************/

static BERR_Code BDSP_Raaga_P_GetNumberOfDsp( BBOX_Handle boxHandle, unsigned *pNumDsp )
{
    BBOX_Config *pConfig;
	BERR_Code ret = BERR_SUCCESS;

	pConfig = BKNI_Malloc(sizeof(BBOX_Config));
    BKNI_Memset(pConfig, 0 , sizeof(BBOX_Config));

	ret = BBOX_GetConfig(boxHandle, pConfig);
	if(BERR_SUCCESS != ret)
	{
		BDBG_ERR(("BDSP_Raaga_P_GetNumberOfDsp: Error in retrieving the Num DSP from BOX MODE"));
	}
	else
	{
		*pNumDsp = pConfig->stAudio.numDsps;
	}
	BKNI_Free(pConfig);
    return ret;
}

/***********************************************************************
Name        :   BDSP_Raaga_P_GetMemoryEstimate

Type        :   PI Interface

Input       :   pSettings       -   Handle of the Stage whose settings needs to be retrieved.
                pUsage      -   Pointer to usage case scenario from which we determine the runtime memory.
                boxHandle   -     BOX Mode Handle for which the memory needs to be estimated.
                pEstimate   -   Pointer to the memory where the Stage Settings are filled.

Return      :   Error Code to return SUCCESS or FAILURE

Functionality   :   Following are the operations performed.
        1)  Calculate the Init memory required for the system.
        2)  Calculate Scratch, InterstageIO and InterstageIOGen for the system.
        3)  Calculate the Firware memory requied by the system.
        4)  Return the Firmware memory and the Heap memory required by the system.
***********************************************************************/

BERR_Code BDSP_Raaga_P_GetMemoryEstimate(
    const BDSP_RaagaSettings     *pSettings,
    const BDSP_RaagaUsageOptions *pUsage,
	BBOX_Handle                   boxHandle,
    BDSP_RaagaMemoryEstimate     *pEstimate /*[out]*/
)
{
    BERR_Code ret= BERR_SUCCESS;
    uint32_t ui32Scratch = 0, ui32InterStageIO = 0, ui32InterStageIOGen = 0, ui32NumCh = 0;
    int32_t i32DspIndex =0, i32BranchIndex =0;
    unsigned NumDsp = BDSP_RAAGA_MAX_DSP;
    unsigned ContextMemory = 0, TaskMemory = 0, IntertaskBufferMemory = 0;
    unsigned DecodeMemory = 0, MixerMemory = 0, PostProcessingMemory = 0, EchocancellerMemory = 0, AudioEncoderMemory = 0, PassthruMemory =0;
    unsigned VideoDecodeMemory = 0, VideoEncodeMemory =0;
    unsigned NumChannels = 0;
    BDSP_AF_P_DistinctOpType distinctOp;

    BDSP_Raaga_P_DwnldMemInfo   *psDwnldMemInfo;
    BDSP_RaagaImgCacheEntry     *pImgCache;

    /* This allocation is done to reuse the functionality of BDSP_MM_P_GetFwMemRequired and nothing else*/
    psDwnldMemInfo = BKNI_Malloc(sizeof(BDSP_Raaga_P_DwnldMemInfo));
    BKNI_Memset(psDwnldMemInfo, 0 , sizeof(BDSP_Raaga_P_DwnldMemInfo));

    pImgCache = BKNI_Malloc(sizeof(BDSP_RaagaImgCacheEntry)*BDSP_IMG_ID_MAX);
    BKNI_Memset(pImgCache, 0 , sizeof(BDSP_RaagaImgCacheEntry)*BDSP_IMG_ID_MAX);

    /* Initialise the values */
    pEstimate->FirmwareMemory = 0;
    pEstimate->GeneralMemory  = 0;

    /* Get the Number of DSP's present in the system */
    if(NULL != boxHandle)
    {
        ret = BDSP_Raaga_P_GetNumberOfDsp(boxHandle,&NumDsp);
    }
    else
    {
        NumDsp = pSettings->NumDsp;
    }

    /*Calculate the Init Memory Required for the whole System */
    ret = BDSP_Raaga_P_CalculateInitMemory(&pEstimate->GeneralMemory,NumDsp);

    /*Calculate the maximum Scratch, Interstage and Interstage Generic buffer*/
    ret = BDSP_MM_P_CalcScratchAndISbufferReq_MemToolAPI(&ui32Scratch, &ui32InterStageIO, &ui32InterStageIOGen, &ui32NumCh, pUsage);
    /* Allocation is done per DSP basis
        Scratch buffer - 1
        InterstageIO buffer -1 per task and max task supported is 3
        InterstageIOGen buffer -1 per task and max task supported is 3*/
    for(i32DspIndex=0;i32DspIndex < (int32_t)NumDsp;i32DspIndex++)
    {
        pEstimate->GeneralMemory += ui32Scratch;
        for(i32BranchIndex=0; i32BranchIndex<BDSP_RAAGA_MAX_BRANCH_PER_TASK; i32BranchIndex++)
        {
            pEstimate->GeneralMemory += (ui32InterStageIO*ui32NumCh);
            pEstimate->GeneralMemory += ui32InterStageIOGen;
        }
    }

    /*Calculate the FIRMWARE heap memory required by the system */
    ret = BDSP_MM_P_GetFwMemRequired(pSettings, psDwnldMemInfo,(void *) pImgCache, false, pUsage);
    pEstimate->FirmwareMemory = psDwnldMemInfo->ui32AllocwithGuardBand;

    /* Memory Allocated for Context - VOM table */
    ret = BDSP_Raaga_P_CalculateContextMemory(&ContextMemory);
    pEstimate->GeneralMemory += ContextMemory;

    /* Memory Allocated for Task per task is calculated.
         Worst Case Estimate is taken for 12 tasks */
    ret = BDSP_Raaga_P_CalculateTaskMemory(&TaskMemory);
    pEstimate->GeneralMemory += (TaskMemory * BDSP_RAAGA_MAX_FW_TASK_PER_DSP);

    /* Memory Allocation for Inter-task buffer */
    BDSP_Raaga_P_GetDistinctOpTypeAndNumChans(pUsage->IntertaskBufferDataType, &NumChannels, &distinctOp);
    ret = BDSP_Raaga_P_CalculateInterTaskBufferMemory(&IntertaskBufferMemory, NumChannels);

    /* Memory Allocation associated with Decoder */
    if(pUsage->NumAudioDecoders)
    {
        ret = BDSP_Raaga_P_CalculateStageMemory(BDSP_AlgorithmType_eAudioDecode, &DecodeMemory, pUsage);
        pEstimate->GeneralMemory += (DecodeMemory*pUsage->NumAudioDecoders);
    }

    /* Memory Allocation associated with Post Processing */
    if(pUsage->NumAudioPostProcesses)
    {
        ret = BDSP_Raaga_P_CalculateStageMemory(BDSP_AlgorithmType_eAudioProcessing, &PostProcessingMemory, pUsage);
        pEstimate->GeneralMemory += (PostProcessingMemory*pUsage->NumAudioPostProcesses);
    }

    /* Memory Allocation associated with Passthru */
    if(pUsage->NumAudioPassthru)
    {
        ret = BDSP_Raaga_P_CalculateStageMemory(BDSP_AlgorithmType_eAudioPassthrough, &PassthruMemory, pUsage);
        pEstimate->GeneralMemory += (PassthruMemory*pUsage->NumAudioPassthru);
    }

    /* Memory Allocation associated with Audio Encoder */
    if(pUsage->NumAudioEncoders)
    {
        ret = BDSP_Raaga_P_CalculateStageMemory(BDSP_AlgorithmType_eAudioEncode, &AudioEncoderMemory, pUsage);
        pEstimate->GeneralMemory += (AudioEncoderMemory*pUsage->NumAudioEncoders);
    }

    /* Memory Allocation associated with Mixer
         We estimate that we can connect atmost 3 Intertask buffers per Mixer*/
    if(pUsage->NumAudioMixers)
    {
        ret = BDSP_Raaga_P_CalculateStageMemory(BDSP_AlgorithmType_eAudioMixer, &MixerMemory, pUsage);
        pEstimate->GeneralMemory += (MixerMemory*pUsage->NumAudioMixers);
        pEstimate->GeneralMemory += (IntertaskBufferMemory*pUsage->NumAudioMixers*BDSP_MAX_INTERTASKBUFFER_INPUT_TO_MIXER);
    }

    /* Memory Allocation associated with Echocanceller
         We estimate that we can connect atmost 1 Intertask buffers per Echocanceller*/
    if(pUsage->NumAudioEchocancellers)
    {
        ret = BDSP_Raaga_P_CalculateStageMemory(BDSP_AlgorithmType_eAudioEchoCanceller, &EchocancellerMemory, pUsage);
        pEstimate->GeneralMemory += (EchocancellerMemory*pUsage->NumAudioEchocancellers);
        pEstimate->GeneralMemory += (IntertaskBufferMemory*pUsage->NumAudioEchocancellers*BDSP_MAX_INTERTASKBUFFER_INPUT_TO_ECHOCANCELLER);
    }

    /* Memory Allocation associated with Video Decoder */
    if(pUsage->NumVideoDecoders)
    {
        ret = BDSP_Raaga_P_CalculateStageMemory(BDSP_AlgorithmType_eVideoDecode, &VideoDecodeMemory, pUsage);
        pEstimate->GeneralMemory += (VideoDecodeMemory*pUsage->NumVideoDecoders);
    }

    /* Memory Allocation associated with Video Encoder */
    if(pUsage->NumVideoEncoders)
    {
        ret = BDSP_Raaga_P_CalculateStageMemory(BDSP_AlgorithmType_eVideoEncode, &VideoEncodeMemory, pUsage);
        pEstimate->GeneralMemory += (VideoEncodeMemory*pUsage->NumVideoEncoders);
    }

    BDBG_MSG(("Memory Required FIRMWARE = %d \t GENERAL = %d\n",pEstimate->FirmwareMemory, pEstimate->GeneralMemory));
    BKNI_Free(psDwnldMemInfo);
    BKNI_Free(pImgCache);

    return ret;
}

/***********************************************************************
Name        :   BDSP_Raaga_P_GetStageSettings

Type        :   PI Interface

Input       :   pStageHandle        -   Handle of the Stage whose settings needs to be retrieved.
                pSettingsBuffer -   Pointer to the memory where the Stage Settings are filled.
                settingsSize        -   Size of the Settings buffer provided by PI.

Return      :   Error Code to return SUCCESS or FAILURE

Functionality   :   Following are the operations performed.
        1)  Retrieve the Algorithm Settings of the Stage using the BDSP_Raaga_P_GetAlgorithmSettings call.
***********************************************************************/

BERR_Code BDSP_Raaga_P_GetStageSettings(
    void *pStageHandle,
    void *pSettingsBuffer,
    size_t settingsSize)
{
    BDSP_RaagaStage *pRaagaStage = (BDSP_RaagaStage *)pStageHandle;
    void *pAddress;
    BERR_Code errCode;

    BDBG_OBJECT_ASSERT(pRaagaStage, BDSP_RaagaStage);
    BDBG_ASSERT(pSettingsBuffer);

    BDBG_ASSERT(pRaagaStage->algorithm < BDSP_Algorithm_eMax);

    BDSP_MEM_P_ConvertOffsetToCacheAddr(pRaagaStage->pContext->pDevice->memHandle, pRaagaStage->sDramUserConfigBuffer.ui32DramBufferAddress, &pAddress);

    errCode = BDSP_Raaga_P_GetAlgorithmSettings(
        pRaagaStage->pContext->pDevice->memHandle,
        pRaagaStage->algorithm,
        pAddress,
        /* Since the buffer is shared between ids and decode stage, the
        buffer size available for the decode stage is the offset to ids buffer */
        pRaagaStage->sFrameSyncOffset.ui32UserCfgOffset, /*pRaagaStage->sDramUserConfigBuffer.ui32BufferSizeInBytes,*/
        pSettingsBuffer,
        settingsSize);

    if ( errCode )
    {
        return BERR_TRACE(errCode);
    }

    return BERR_SUCCESS;
}

/***********************************************************************
Name        :   BDSP_Raaga_P_SetStageSettings

Type        :   PI Interface

Input       :   pStageHandle        -   Handle of the Stage for which settings need to be applied.
                pSettingsBuffer -   Pointer to the memory where the settings are provided by the PI .
                settingsSize        -   Size of the Settings buffer provided by PI.

Return      :   Error Code to return SUCCESS or FAILURE

Functionality   :   Following are the operations performed.
        1)  Set the Algorithm settings for the stage.
        2)  If the Stage is already running then use spare config buffer else config buffer.
        3)  If the Satge is already running then, CFG change command is issued to apply the settings.
***********************************************************************/

BERR_Code BDSP_Raaga_P_SetStageSettings(
    void *pStageHandle,
    const void *pSettingsBuffer,
    size_t settingsSize)
{
    BDSP_RaagaStage *pRaagaStage;
    BDSP_Raaga  *pDevice;
    BERR_Code err = BERR_SUCCESS;
    unsigned int  uiConfigBufAddr =0;
    unsigned int  uiConfigBufSize;
    BDSP_Raaga_P_Command sCommand;
    BDSP_Raaga_P_Response sRsp;
    BDSP_Raaga_P_MsgType      eMsgType;
    void *pAddress;

    pRaagaStage = (BDSP_RaagaStage *)pStageHandle;
    pDevice = pRaagaStage->pContext->pDevice;

    BDBG_OBJECT_ASSERT(pRaagaStage, BDSP_RaagaStage);
    BDBG_ASSERT(pSettingsBuffer);

    BDBG_ASSERT(pRaagaStage->algorithm < BDSP_Algorithm_eMax);

    if (pRaagaStage->running)
    {
        uiConfigBufAddr = pRaagaStage->sDramUserConfigSpareBuffer.ui32DramBufferAddress;
        uiConfigBufSize = pRaagaStage->sFrameSyncOffset.ui32UserCfgOffset;
    }
    else
    {
        uiConfigBufAddr = pRaagaStage->sDramUserConfigBuffer.ui32DramBufferAddress;
        /* Since the buffer is shared between ids and decode stage, the
        buffer size availabel for the decode stage is the offset to ids buffer */
        uiConfigBufSize = pRaagaStage->sFrameSyncOffset.ui32UserCfgOffset; /* pRaagaStage->sDramUserConfigBuffer.ui32BufferSizeInBytes;*/
    }

    BDSP_MEM_P_ConvertOffsetToCacheAddr(pRaagaStage->pContext->pDevice->memHandle, uiConfigBufAddr, &pAddress);

    err = BDSP_Raaga_P_SetAlgorithmSettings(
        pDevice->memHandle,
        pRaagaStage->algorithm,
        pAddress,
        uiConfigBufSize,
        pSettingsBuffer,
        settingsSize);
    if ( err )
    {
        return BERR_TRACE(err);
    }

    if (pRaagaStage->running)
    {
        /*Send CFG Change Command to FW*/
        sCommand.sCommandHeader.ui32CommandID = BDSP_RAAGA_ALGO_PARAMS_CFG_COMMAND_ID;
        sCommand.sCommandHeader.ui32CommandCounter = pRaagaStage->pRaagaTask->commandCounter++;
        sCommand.sCommandHeader.ui32TaskID = pRaagaStage->pRaagaTask->taskId;
        sCommand.sCommandHeader.eResponseType = BDSP_Raaga_P_ResponseType_eResponseRequired;
        sCommand.sCommandHeader.ui32CommandSizeInBytes =  sizeof(BDSP_Raaga_P_Command);

        sCommand.uCommand.sCfgChange.ui32HostConfigParamBuffAddr = uiConfigBufAddr;
        sCommand.uCommand.sCfgChange.ui32DspConfigParamBuffAddr = pRaagaStage->sDramUserConfigBuffer.ui32DramBufferAddress;

        sCommand.uCommand.sCfgChange.ui32SizeInBytes = settingsSize;

        pRaagaStage->pRaagaTask->lastEventType = sCommand.sCommandHeader.ui32CommandID;
        BKNI_ResetEvent(pRaagaStage->pRaagaTask->hEvent);
        err = BDSP_Raaga_P_SendCommand(pDevice->hCmdQueue[pRaagaStage->pRaagaTask->settings.dspIndex], &sCommand,(void *)pRaagaStage->pRaagaTask);

        if (BERR_SUCCESS != err)
        {
            BDBG_ERR(("BDSP_Raaga_P_SetStageSettings: CFG_Command failed!"));
            err = BERR_TRACE(err);
            goto end;
        }
        /* Wait for Ack_Response_Received event w/ timeout */
        err = BKNI_WaitForEvent(pRaagaStage->pRaagaTask->hEvent, BDSP_RAAGA_EVENT_TIMEOUT_IN_MS);
        if (BERR_TIMEOUT == err)
        {
            BDBG_ERR(("BDSP_Raaga_P_SetStageSettings: CFG_Command TIMEOUT!"));
            err = BERR_TRACE(err);
            goto end;
        }

        eMsgType = BDSP_Raaga_P_MsgType_eSyn;
        err = BDSP_Raaga_P_GetMsg(pRaagaStage->pRaagaTask->hSyncMsgQueue, (void *)&sRsp,eMsgType);

        if (BERR_SUCCESS != err)
        {
            BDBG_ERR(("BDSP_Raaga_P_SetStageSettings: Unable to read ACK!"));
            err = BERR_TRACE(err);
            goto end;
        }

        if ((sRsp.sCommonAckResponseHeader.eStatus != BERR_SUCCESS)||
            (sRsp.sCommonAckResponseHeader.ui32ResponseID != BDSP_RAAGA_ALGO_PARAMS_CFG_RESPONSE_ID)||
            (sRsp.sCommonAckResponseHeader.ui32TaskID != pRaagaStage->pRaagaTask->taskId))
        {

            BDBG_ERR(("BDSP_Raaga_P_SetStageSettings: CFG_Command ACK not received successfully!eStatus = %d , ui32ResponseID = %d , ui32TaskID %d ",
                sRsp.sCommonAckResponseHeader.eStatus,sRsp.sCommonAckResponseHeader.ui32ResponseID,sRsp.sCommonAckResponseHeader.ui32TaskID));
            err = BERR_TRACE(sRsp.sCommonAckResponseHeader.eStatus);
            goto end;
        }
    }

end:
    return err;
}

/***********************************************************************
Name        :   BDSP_Raaga_P_GetDatasyncSettings

Type        :   PI Interface

Input       :   pStageHandle        -   Handle of the Stage for getting data sync settings.
                pSettings           -   Pointer of memory where the data is filled.

Return      :   Error Code to return SUCCESS or FAILURE

Functionality   :   This is a leaf function, which will internally call the BDSP_Raaga_P_GetDatasyncSettings_isr ISR call.
***********************************************************************/

BERR_Code BDSP_Raaga_P_GetDatasyncSettings(
    void *pStageHandle,
    BDSP_AudioTaskDatasyncSettings *pSettings)
{
    BERR_Code err = BERR_SUCCESS;
    BDBG_ASSERT(pStageHandle);
    BDBG_ASSERT(pSettings);

    BKNI_EnterCriticalSection();
    err =BDSP_Raaga_P_GetDatasyncSettings_isr(pStageHandle, pSettings);
    BKNI_LeaveCriticalSection();
    return err;
}

/***********************************************************************
Name        :   BDSP_Raaga_P_SetDatasyncSettings

Type        :   PI Interface

Input       :   pStageHandle        -   Handle of the Stage for setting data sync settings.
                pSettings           -   Pointer of data to be Set

Return      :   Error Code to return SUCCESS or FAILURE

Functionality   :   This is a leaf function, which will internally call the BDSP_Raaga_P_SetDatasyncSettings_isr ISR call.
***********************************************************************/

BERR_Code BDSP_Raaga_P_SetDatasyncSettings(
    void *pStageHandle,
    const BDSP_AudioTaskDatasyncSettings *pSettings)
{
    BERR_Code err=BERR_SUCCESS;
    BDBG_ASSERT(pStageHandle);
    BDBG_ASSERT(pSettings);

    BKNI_EnterCriticalSection();
    err =BDSP_Raaga_P_SetDatasyncSettings_isr(pStageHandle, pSettings);
    BKNI_LeaveCriticalSection();
    return err;
}

/***********************************************************************
Name        :   BDSP_Raaga_P_GetDatasyncSettings_isr
Type        :   ISR
Input       :   pStageHandle        -   Handle of the Stage for which Data Sync settings are requested.
                pSettings           -   Pointer to which the data is filled and returned.
Return      :   Error Code to return SUCCESS or FAILURE
Functionality   :   Following are the operations performed.
        1)  Retreive the Frame Sync and TSM settings using the BDSP_Raaga_P_GetFrameSyncTsmStageConfigParams_isr" call.
        2)  Note the information to be retrieved is from HOST/Spare Config buffer and not DSP/Config buffer to avoid RACE condition.
        3)  Return only the Audio Data Sync Settings back to the PI.
Design Note:
        a)  Inside "BDSP_Raaga_P_SetDatasyncSettings_isr", if the stage is running, then the data is copied from
            HOST to DSP buffer by the FW. HOST needs to only modify the HOST/Spare buffer only.
        b)  Inside "BDSP_Raaga_P_SetDatasyncSettings_isr", if the Stage is not running, then the data is Copied
        both into HOST/DSP buffer. This is required for consistency of the data.
        c)  The "BDSP_Raaga_P_GetDatasyncSettings_isr" will retrieve the information from HOST
        buffer only.
***********************************************************************/

BERR_Code BDSP_Raaga_P_GetDatasyncSettings_isr(
    void *pStageHandle,
    BDSP_AudioTaskDatasyncSettings *pSettings)
{
    uint32_t        fsUserCfgSize;
    void *pUserCfg;
    BERR_Code       err = BERR_SUCCESS;
    BDSP_RaagaStage *pRaagaStage = (BDSP_RaagaStage *)pStageHandle;
    BDSP_Raaga_Audio_FrameSyncTsmConfigParams  sFrameSyncTsmConfigParams;


    BDBG_OBJECT_ASSERT(pRaagaStage, BDSP_RaagaStage);
    BDBG_ASSERT(pSettings);

    pUserCfg = (void *)((uint8_t *)pRaagaStage->sDramUserConfigSpareBuffer.pDramBufferAddress+
                    pRaagaStage->sFrameSyncOffset.ui32UserCfgOffset);

    fsUserCfgSize = pRaagaStage->sDramUserConfigSpareBuffer.ui32BufferSizeInBytes -
                    pRaagaStage->sFrameSyncOffset.ui32UserCfgOffset;

    BDSP_Raaga_P_GetFrameSyncTsmStageConfigParams_isr(
        pRaagaStage->pContext->pDevice->memHandle,
        pRaagaStage->algorithm, pUserCfg, fsUserCfgSize,
        &sFrameSyncTsmConfigParams, sizeof(sFrameSyncTsmConfigParams));

    BKNI_Memcpy((void *)(volatile void*)pSettings,
        (void *)&sFrameSyncTsmConfigParams.sFrameSyncConfigParams,
        sizeof(BDSP_AudioTaskDatasyncSettings));

    return err;
}

/***********************************************************************
Name        :   BDSP_Raaga_P_SetDatasyncSettings_isr

Type        :   ISR

Input       :   pStageHandle        -   Handle of the Stage for which Data Sync settings needs to be Set.
                pSettings           -   Pointer of the Settings provided by PI.

Return      :   Error Code to return SUCCESS or FAILURE

Functionality   :   Following are the operations performed.
        1)  Retrieve the whole Frame Sync information from HOST/Spare buffer  into a local buffer using
            "BDSP_Raaga_P_GetFrameSyncTsmStageConfigParams_isr".
        2)  Update the Data Sync settings only into the local buffer.
        3)  If the Stage is Stopped, then update the both DSP/Config buffer and HOST/Spare buffer else
            update only the HOST/Spare buffer only.
        4)  If the Stage is running then send the Config change command and don't wait for response.

 Design Note:
    a)  Inside "BDSP_Raaga_P_SetDatasyncSettings_isr", if the stage is running, then the data is copied from
            HOST to DSP buffer by the FW. HOST needs to only modify the HOST/Spare buffer only.
        b)  Inside "BDSP_Raaga_P_SetDatasyncSettings_isr", if the Stage is not running, then the data is Copied
        both into HOST/DSP buffer. This is required for consistency of the data.
        c)  The "BDSP_Raaga_P_GetDatasyncSettings_isr" will retrieve the information from HOST
        buffer only.
***********************************************************************/

BERR_Code BDSP_Raaga_P_SetDatasyncSettings_isr(
    void *pStageHandle,
    const BDSP_AudioTaskDatasyncSettings *pSettings)
{
    BDSP_RaagaStage *pRaagaStage;
    BDSP_Raaga  *pDevice;
    BERR_Code err = BERR_SUCCESS;
    void            *pConfigBuf;
    raaga_dramaddr  ui32ConfigBufAddr;
    unsigned int    uiConfigBufSize=0;
    BDSP_Raaga_P_Command sCommand;
    BDSP_Raaga_Audio_FrameSyncTsmConfigParams   sFrameSyncTsmConfigParams;

    void            *pTsmUserCfg;
    raaga_dramaddr  TsmBufAddr;
    uint32_t        fsTsmUserCfgSize;

    pRaagaStage = (BDSP_RaagaStage *)pStageHandle;
    pDevice = pRaagaStage->pContext->pDevice;

    BDBG_OBJECT_ASSERT(pRaagaStage, BDSP_RaagaStage);
    BDBG_ASSERT(pSettings);

    /*HOST Buffer details */
    pConfigBuf = (void *)((uint8_t *)pRaagaStage->sDramUserConfigSpareBuffer.pDramBufferAddress+pRaagaStage->sFrameSyncOffset.ui32UserCfgOffset);
    uiConfigBufSize = pRaagaStage->sDramUserConfigSpareBuffer.ui32BufferSizeInBytes - pRaagaStage->sFrameSyncOffset.ui32UserCfgOffset;

    /*DSP Buffer details */
    pTsmUserCfg = (void *)((uint8_t *)pRaagaStage->sDramUserConfigBuffer.pDramBufferAddress+ pRaagaStage->sFrameSyncOffset.ui32UserCfgOffset);
    fsTsmUserCfgSize = pRaagaStage->sDramUserConfigBuffer.ui32BufferSizeInBytes - pRaagaStage->sFrameSyncOffset.ui32UserCfgOffset;

    BDSP_Raaga_P_GetFrameSyncTsmStageConfigParams_isr(
        pDevice->memHandle, pRaagaStage->algorithm,
        pConfigBuf, uiConfigBufSize,
        &sFrameSyncTsmConfigParams, sizeof(sFrameSyncTsmConfigParams));

    BKNI_Memcpy((void *)(volatile void*)&(sFrameSyncTsmConfigParams.sFrameSyncConfigParams) ,(void *)pSettings ,sizeof(BDSP_AudioTaskDatasyncSettings));

    if ( !pRaagaStage->running )
    {
        /* If the Task is not running then write the data into DSP buffer too */
        BDSP_Raaga_P_SetFrameSyncTsmStageConfigParams_isr(
            pDevice->memHandle, pRaagaStage->algorithm,
            pTsmUserCfg, fsTsmUserCfgSize,
            &sFrameSyncTsmConfigParams, sizeof(sFrameSyncTsmConfigParams));
    }
    /*Always write the data into HOST buffer*/
    BDSP_Raaga_P_SetFrameSyncTsmStageConfigParams_isr(
        pDevice->memHandle, pRaagaStage->algorithm,
        pConfigBuf, uiConfigBufSize,
        &sFrameSyncTsmConfigParams, sizeof(sFrameSyncTsmConfigParams));

    if (pRaagaStage->running)
    {

        ui32ConfigBufAddr = pRaagaStage->sDramUserConfigSpareBuffer.ui32DramBufferAddress + pRaagaStage->sFrameSyncOffset.ui32UserCfgOffset;
        TsmBufAddr = pRaagaStage->sDramUserConfigBuffer.ui32DramBufferAddress +
                       pRaagaStage->sFrameSyncOffset.ui32UserCfgOffset;

        /*Send CFG Change Command to FW*/
        sCommand.sCommandHeader.ui32CommandID = BDSP_RAAGA_ALGO_PARAMS_CFG_COMMAND_ID;
        sCommand.sCommandHeader.ui32CommandCounter = pRaagaStage->pRaagaTask->commandCounter++;
        sCommand.sCommandHeader.ui32TaskID = pRaagaStage->pRaagaTask->taskId;
        sCommand.sCommandHeader.eResponseType = BDSP_Raaga_P_ResponseType_eNone;
        sCommand.sCommandHeader.ui32CommandSizeInBytes =  sizeof(BDSP_Raaga_P_Command);
        sCommand.uCommand.sCfgChange.ui32HostConfigParamBuffAddr = ui32ConfigBufAddr;
        sCommand.uCommand.sCfgChange.ui32DspConfigParamBuffAddr = TsmBufAddr;
        sCommand.uCommand.sCfgChange.ui32SizeInBytes = sizeof(BDSP_Raaga_Audio_FrameSyncTsmConfigParams);

        pRaagaStage->pRaagaTask->lastEventType = sCommand.sCommandHeader.ui32CommandID;
        err = BDSP_Raaga_P_SendCommand_isr(pDevice->hCmdQueue[pRaagaStage->pRaagaTask->settings.dspIndex], &sCommand,(void *)pRaagaStage->pRaagaTask);

        if (BERR_SUCCESS != err)
        {
            BDBG_ERR(("BDSP_Raaga_P_SetStageSettings: CFG_Command failed!"));
            err = BERR_TRACE(err);
            goto end;
        }
    }
end:

    return err;
}

/***********************************************************************
Name        :   BDSP_Raaga_P_GetTsmSettings_isr

Type        :   PI Interface/ISR

Input       :   pStageHandle        -   Handle of the Stage for which TSM settings are requested.
                pSettings           -   Pointer to which the data is filled and returned.

Return      :   Error Code to return SUCCESS or FAILURE

Functionality   :   Following are the operations performed.
        1)  Retreive the Frame Sync and TSM settings using the BDSP_Raaga_P_GetFrameSyncTsmStageConfigParams_isr" call.
        2)  Note the information to be retrieved is from HOST/Spare Config buffer and not DSP/Config buffer to avoid RACE condition.
        3)  Return only the TSM settings back to the PI.

 Design Note:
        a)  Inside "BDSP_Raaga_P_SetTsmSettings_isr", if the stage is running, then the data is copied from
            HOST to DSP buffer by the FW. HOST needs to only modify the HOST/Spare buffer only.
        b)  Inside "BDSP_Raaga_P_SetTsmSettings_isr", if the Stage is not running, then the data is Copied
        both into HOST/DSP buffer. This is required for consistency of the data.
        c)  The "BDSP_Raaga_P_GetTsmSettings_isr" will retrieve the information from HOST
        buffer only.
***********************************************************************/

BERR_Code BDSP_Raaga_P_GetTsmSettings_isr(
    void *pStageHandle,
    BDSP_AudioTaskTsmSettings    *pSettings)
{
    void        *pTsmUserCfg;
    uint32_t       fsTsmUserCfgSize;
    BERR_Code       err = BERR_SUCCESS;
    BDSP_RaagaStage *pRaagaStage = (BDSP_RaagaStage *)pStageHandle;
    BDSP_Raaga_Audio_FrameSyncTsmConfigParams   sFrameSyncTsmConfigParams;


    BDBG_OBJECT_ASSERT(pRaagaStage, BDSP_RaagaStage);
    BDBG_ASSERT(pSettings);

    pTsmUserCfg = (void *)((uint8_t *)pRaagaStage->sDramUserConfigSpareBuffer.pDramBufferAddress+
                       pRaagaStage->sFrameSyncOffset.ui32UserCfgOffset);

    fsTsmUserCfgSize = pRaagaStage->sDramUserConfigSpareBuffer.ui32BufferSizeInBytes -
                       pRaagaStage->sFrameSyncOffset.ui32UserCfgOffset;
    /* Read the settings from the host buffer to avoid race conditions */
    BDSP_Raaga_P_GetFrameSyncTsmStageConfigParams_isr(
        pRaagaStage->pContext->pDevice->memHandle,
        pRaagaStage->algorithm, pTsmUserCfg, fsTsmUserCfgSize,
        &sFrameSyncTsmConfigParams, sizeof(sFrameSyncTsmConfigParams));

    BKNI_Memcpy((void *)(volatile void*)pSettings,
        &(sFrameSyncTsmConfigParams.sTsmConfigParams),
        sizeof(BDSP_AudioTaskTsmSettings));

    return err;
}

/***********************************************************************
Name        :   BDSP_Raaga_P_SetTsmSettings_isr

Type        :   PI Interface/ISR

Input       :   pStageHandle        -   Handle of the Stage for which TSM settings needs to be Set.
                pSettings           -   Pointer of the Settings provided by PI.

Return      :   Error Code to return SUCCESS or FAILURE

Functionality   :   Following are the operations performed.
        1)  Retrieve the whole Frame Sync information from HOST/Spare Config buffer  into a local buffer using
            "BDSP_Raaga_P_GetFrameSyncTsmStageConfigParams_isr".
        2)  Update the TSM settings only into the local buffer.
        3)  If the Stage is Stopped, then update the both DSP/Config buffer and HOST/Spare buffer else
            update only the HOST/Spare buffer only.
        4)  If the Stage is running then send the Config change command and don't wait for response.

 Design Note:
    a)  Inside "BDSP_Raaga_P_SetTsmSettings_isr", if the stage is running, then the data is copied from
            HOST to DSP buffer by the FW. HOST needs to only modify the HOST/Spare buffer.
        b)  Inside "BDSP_Raaga_P_SetTsmSettings_isr", if the Stage is not running, then the data is Copied
        both into HOST/DSP buffer. This is required for consistency of the data.
        c)  The "BDSP_Raaga_P_GetTsmSettings_isr" will retrieve the information from HOST
        buffer only.
***********************************************************************/

BERR_Code BDSP_Raaga_P_SetTsmSettings_isr(
    void *pStageHandle,
    const BDSP_AudioTaskTsmSettings *pSettings)
{
    BDSP_RaagaStage *pRaagaStage;
    BDSP_Raaga  *pDevice;
    BERR_Code err = BERR_SUCCESS;
    void *pConfigBuf =0;
    raaga_dramaddr  ui32ConfigBufAddr, ui32TsmUserCfgAddr;
    unsigned int            uiConfigBufSize=0;
    BDSP_Raaga_P_Command sCommand;
    BDSP_Raaga_Audio_FrameSyncTsmConfigParams   sFrameSyncTsmConfigParams;


    void  *pTsmUserCfgr=0;
    uint32_t fsTsmUserCfgSize;

    pRaagaStage = (BDSP_RaagaStage *)pStageHandle;
    pDevice = pRaagaStage->pContext->pDevice;

    BDBG_OBJECT_ASSERT(pRaagaStage, BDSP_RaagaStage);
    BDBG_ASSERT(pSettings);

    /*HOST Buffer details */
    pConfigBuf = (void *)((uint8_t *)pRaagaStage->sDramUserConfigSpareBuffer.pDramBufferAddress+pRaagaStage->sFrameSyncOffset.ui32UserCfgOffset);
    uiConfigBufSize = pRaagaStage->sDramUserConfigSpareBuffer.ui32BufferSizeInBytes - pRaagaStage->sFrameSyncOffset.ui32UserCfgOffset;

    /*DSP Buffer details */
    pTsmUserCfgr = (void *)((uint8_t *)pRaagaStage->sDramUserConfigBuffer.pDramBufferAddress+ pRaagaStage->sFrameSyncOffset.ui32UserCfgOffset);
    fsTsmUserCfgSize = pRaagaStage->sDramUserConfigBuffer.ui32BufferSizeInBytes - pRaagaStage->sFrameSyncOffset.ui32UserCfgOffset;

    BDSP_Raaga_P_GetFrameSyncTsmStageConfigParams_isr(
        pDevice->memHandle, pRaagaStage->algorithm,
        pConfigBuf, uiConfigBufSize,
        &sFrameSyncTsmConfigParams, sizeof(sFrameSyncTsmConfigParams));

    BKNI_Memcpy((void *)(volatile void*)&(sFrameSyncTsmConfigParams.sTsmConfigParams) ,(void *)pSettings ,sizeof(BDSP_AudioTaskTsmSettings));

    if ( !pRaagaStage->running )
    {
        /* If the Task is not running then write the data into DSP buffer too */
        BDSP_Raaga_P_SetFrameSyncTsmStageConfigParams_isr(
            pDevice->memHandle, pRaagaStage->algorithm,
            pTsmUserCfgr, fsTsmUserCfgSize,
            &sFrameSyncTsmConfigParams, sizeof(sFrameSyncTsmConfigParams));
    }
    /*Always write the data into HOST buffer*/
    BDSP_Raaga_P_SetFrameSyncTsmStageConfigParams_isr(
        pDevice->memHandle, pRaagaStage->algorithm,
        pConfigBuf, uiConfigBufSize,
        &sFrameSyncTsmConfigParams, sizeof(sFrameSyncTsmConfigParams));

    if (pRaagaStage->running)
    {
        ui32TsmUserCfgAddr = pRaagaStage->sDramUserConfigBuffer.ui32DramBufferAddress + pRaagaStage->sFrameSyncOffset.ui32UserCfgOffset;
        ui32ConfigBufAddr = pRaagaStage->sDramUserConfigSpareBuffer.ui32DramBufferAddress + pRaagaStage->sFrameSyncOffset.ui32UserCfgOffset;

        /*Send CFG Change Command to FW*/
        sCommand.sCommandHeader.ui32CommandID = BDSP_RAAGA_ALGO_PARAMS_CFG_COMMAND_ID;
        sCommand.sCommandHeader.ui32CommandCounter = pRaagaStage->pRaagaTask->commandCounter++;
        sCommand.sCommandHeader.ui32TaskID = pRaagaStage->pRaagaTask->taskId;
        sCommand.sCommandHeader.eResponseType = BDSP_Raaga_P_ResponseType_eNone;
        sCommand.sCommandHeader.ui32CommandSizeInBytes =  sizeof(BDSP_Raaga_P_Command);
        sCommand.uCommand.sCfgChange.ui32HostConfigParamBuffAddr = ui32ConfigBufAddr;
        sCommand.uCommand.sCfgChange.ui32DspConfigParamBuffAddr = ui32TsmUserCfgAddr;

        sCommand.uCommand.sCfgChange.ui32SizeInBytes = sizeof(BDSP_Raaga_Audio_FrameSyncTsmConfigParams);

        pRaagaStage->pRaagaTask->lastEventType = sCommand.sCommandHeader.ui32CommandID;
        err = BDSP_Raaga_P_SendCommand_isr(pDevice->hCmdQueue[pRaagaStage->pRaagaTask->settings.dspIndex], &sCommand,(void *)pRaagaStage->pRaagaTask);

        if (BERR_SUCCESS != err)
        {
            BDBG_ERR(("BDSP_Raaga_P_SetStageSettings: CFG_Command failed!"));
            err = BERR_TRACE(err);
            goto end;
        }
    }

end:

    return err;
}

/***********************************************************************
Name        :   BDSP_Raaga_P_GetVideoEncodeDatasyncSettings

Type        :   PI Interface

Input       :   pStageHandle        -   Handle of the Stage for getting Video Encode data sync.
                pSettings           -   Pointer of memory where the data is filled.

Return      :   Error Code to return SUCCESS or FAILURE

Functionality   :   This is a leaf function, which will internally call the GetVideoEncodeDatasyncSettings ISR call.
***********************************************************************/

BERR_Code BDSP_Raaga_P_GetVideoEncodeDatasyncSettings(
    void *pStageHandle,
    BDSP_VideoEncodeTaskDatasyncSettings *pSettings)
{
    BERR_Code err = BERR_SUCCESS;
    BDBG_ASSERT(pStageHandle);
    BDBG_ASSERT(pSettings);

    BDBG_ENTER( BDSP_Raaga_P_GetVideoEncodeDatasyncSettings );

    BKNI_EnterCriticalSection();
    err =BDSP_Raaga_P_GetVideoEncodeDatasyncSettings_isr(pStageHandle, pSettings);
    BKNI_LeaveCriticalSection();

    BDBG_LEAVE( BDSP_Raaga_P_GetVideoEncodeDatasyncSettings );

    return err;
}

/***********************************************************************
Name        :   BDSP_Raaga_P_SetVideoEncodeDatasyncSettings

Type        :   PI Interface

Input       :   pStageHandle        -   Handle of the Stage for setting Video Encode data sync.
                pSettings           -   Pointer containg the data to be Set.

Return      :   Error Code to return SUCCESS or FAILURE

Functionality   :   This is a leaf function, which will internally call the SetVideoEncodeDatasyncSettings ISR call.
***********************************************************************/

BERR_Code BDSP_Raaga_P_SetVideoEncodeDatasyncSettings(
    void *pStageHandle,
    const BDSP_VideoEncodeTaskDatasyncSettings *pSettings)
{
    BERR_Code err=BERR_SUCCESS;
    BDBG_ASSERT(pStageHandle);
    BDBG_ASSERT(pSettings);

    BDBG_ENTER( BDSP_Raaga_P_SetVideoEncodeDatasyncSettings );

    BKNI_EnterCriticalSection();
    err =BDSP_Raaga_P_SetVideoEncodeDatasyncSettings_isr(pStageHandle, pSettings);
    BKNI_LeaveCriticalSection();

    BDBG_LEAVE( BDSP_Raaga_P_SetVideoEncodeDatasyncSettings );

    return err;
}

/***********************************************************************
Name        :   BDSP_Raaga_P_GetVideoEncodeDatasyncSettings_isr

Type        :   ISR

Input       :   pStageHandle        -   Handle of the Stage for which Data Sync settings are requested.
                pSettings           -   Pointer to which the data is filled and returned.

Return      :   Error Code to return SUCCESS or FAILURE

Functionality   :   Following are the operations performed.
        1)  Retreive the Data Sync settings using the BDSP_Raaga_P_GetFrameSyncTsmStageConfigParams_isr" call.
        2)  Note the information to be retrieved is from HOST/Spare Config buffer and not DSP/Config buffer to avoid RACE condition.
        3)  Return the Video Data Sync Settings back to the PI.

 Design Note:
        a)  Inside "BDSP_Raaga_P_SetDatasyncSettings_isr", if the stage is running, then the data is copied from
            HOST to DSP buffer by the FW. HOST needs to only modify the HOST/Spare buffer only.
        b)  Inside "BDSP_Raaga_P_SetDatasyncSettings_isr", if the Stage is not running, then the data is Copied
        both into HOST/DSP buffer. This is required for consistency of the data.
        c)  The "BDSP_Raaga_P_GetDatasyncSettings_isr" will retrieve the information from HOST
        buffer only.
***********************************************************************/

BERR_Code BDSP_Raaga_P_GetVideoEncodeDatasyncSettings_isr(
    void *pStageHandle,
    BDSP_VideoEncodeTaskDatasyncSettings *pSettings)
{
    void            *pUserCfg;
    uint32_t        fsUserCfgSize;
    BERR_Code       err = BERR_SUCCESS;
    BDSP_RaagaStage *pRaagaStage = (BDSP_RaagaStage *)pStageHandle;
    BDSP_VideoEncodeTaskDatasyncSettings  sFrameSyncTsmConfigParams;


    BDBG_ENTER( BDSP_Raaga_P_GetVideoEncodeDatasyncSettings_isr );

    BDBG_OBJECT_ASSERT(pRaagaStage, BDSP_RaagaStage);
    BDBG_ASSERT(pSettings);

    pUserCfg = (void *)((uint8_t *)pRaagaStage->sDramUserConfigSpareBuffer.pDramBufferAddress+
                    pRaagaStage->sFrameSyncOffset.ui32UserCfgOffset);

    fsUserCfgSize = pRaagaStage->sDramUserConfigSpareBuffer.ui32BufferSizeInBytes -
                    pRaagaStage->sFrameSyncOffset.ui32UserCfgOffset;

    BDSP_Raaga_P_GetFrameSyncTsmStageConfigParams_isr(
        pRaagaStage->pContext->pDevice->memHandle,
        pRaagaStage->algorithm, pUserCfg, fsUserCfgSize,
        &sFrameSyncTsmConfigParams, sizeof(sFrameSyncTsmConfigParams));

    BKNI_Memcpy((void *)(volatile void*)pSettings,
        (void *)&sFrameSyncTsmConfigParams.eEnableStc,
        sizeof(BDSP_VideoEncodeTaskDatasyncSettings));

    BDBG_LEAVE( BDSP_Raaga_P_GetVideoEncodeDatasyncSettings_isr );

    return err;
}

/***********************************************************************
Name        :   BDSP_Raaga_P_SetVideoEncodeDatasyncSettings_isr

Type        :   ISR

Input       :   pStageHandle        -   Handle of the Stage for which Data Sync settings needs to be Set.
                pSettings           -   Pointer of the Settings provided by PI.

Return      :   Error Code to return SUCCESS or FAILURE

Functionality   :   Following are the operations performed.
        1)  If the Stage is Stopped, then update the both DSP/Config buffer and HOST/Spare buffer else
            update only the HOST/Spare buffer only.
        2)  If the Stage is running then send the Config change command and don't wait for response.

 Design Note:
        a)  Inside "BDSP_Raaga_P_SetDatasyncSettings_isr", if the stage is running, then the data is copied from
            HOST to DSP buffer by the FW. HOST needs to only modify the HOST/Spare buffer only.
        b)  Inside "BDSP_Raaga_P_SetDatasyncSettings_isr", if the Stage is not running, then the data is Copied
        both into HOST/DSP buffer. This is required for consistency of the data.
        c)  The "BDSP_Raaga_P_GetDatasyncSettings_isr" will retrieve the information from HOST
        buffer only.
***********************************************************************/

BERR_Code BDSP_Raaga_P_SetVideoEncodeDatasyncSettings_isr(
    void *pStageHandle,
    const BDSP_VideoEncodeTaskDatasyncSettings *pSettings)
{
    BDSP_RaagaStage *pRaagaStage;
    BDSP_Raaga  *pDevice;
    BERR_Code err = BERR_SUCCESS;
    void            *pConfigBuf =0;
    unsigned int            uiConfigBufSize=0;
    BDSP_Raaga_P_Command    sCommand;

    void *pTsmUserCfg;
    uint32_t fsTsmUserCfgSize;
    raaga_dramaddr  ui32TsmUserCfgAddr,ui32ConfigBufAddr;

    BDBG_ENTER( BDSP_Raaga_P_SetVideoEncodeDatasyncSettings_isr );

    pRaagaStage = (BDSP_RaagaStage *)pStageHandle;
    pDevice = pRaagaStage->pContext->pDevice;

    BDBG_OBJECT_ASSERT(pRaagaStage, BDSP_RaagaStage);
    BDBG_ASSERT(pSettings);

    /*HOST Buffer details */
    pConfigBuf = (void *)((uint8_t *)pRaagaStage->sDramUserConfigSpareBuffer.pDramBufferAddress+pRaagaStage->sFrameSyncOffset.ui32UserCfgOffset);
    uiConfigBufSize = pRaagaStage->sDramUserConfigSpareBuffer.ui32BufferSizeInBytes - pRaagaStage->sFrameSyncOffset.ui32UserCfgOffset;

    /*DSP Buffer details */
    pTsmUserCfg = (void *)((uint8_t *)pRaagaStage->sDramUserConfigBuffer.pDramBufferAddress+ pRaagaStage->sFrameSyncOffset.ui32UserCfgOffset);
    fsTsmUserCfgSize = pRaagaStage->sDramUserConfigBuffer.ui32BufferSizeInBytes - pRaagaStage->sFrameSyncOffset.ui32UserCfgOffset;
    if ( !pRaagaStage->running )
    {
        /* If the Task is not running then write the data into DSP buffer too */
        BDSP_Raaga_P_SetFrameSyncTsmStageConfigParams_isr(
            pDevice->memHandle, pRaagaStage->algorithm,
            pTsmUserCfg, fsTsmUserCfgSize,
            pSettings, sizeof(BDSP_VideoEncodeTaskDatasyncSettings));
    }
    /*Always write the data into HOST buffer*/
    BDSP_Raaga_P_SetFrameSyncTsmStageConfigParams_isr(
        pDevice->memHandle, pRaagaStage->algorithm,
        pConfigBuf, uiConfigBufSize,
        &pSettings, sizeof(BDSP_VideoEncodeTaskDatasyncSettings));

    if (pRaagaStage->running)
    {
        ui32TsmUserCfgAddr = pRaagaStage->sDramUserConfigBuffer.ui32DramBufferAddress + pRaagaStage->sFrameSyncOffset.ui32UserCfgOffset;
        ui32ConfigBufAddr = pRaagaStage->sDramUserConfigSpareBuffer.ui32DramBufferAddress + pRaagaStage->sFrameSyncOffset.ui32UserCfgOffset;

        /*Send CFG Change Command to FW*/
        sCommand.sCommandHeader.ui32CommandID = BDSP_RAAGA_ALGO_PARAMS_CFG_COMMAND_ID;
        sCommand.sCommandHeader.ui32CommandCounter = pRaagaStage->pRaagaTask->commandCounter++;
        sCommand.sCommandHeader.ui32TaskID = pRaagaStage->pRaagaTask->taskId;
        sCommand.sCommandHeader.eResponseType = BDSP_Raaga_P_ResponseType_eNone;
        sCommand.sCommandHeader.ui32CommandSizeInBytes =  sizeof(BDSP_Raaga_P_Command);
        sCommand.uCommand.sCfgChange.ui32HostConfigParamBuffAddr = ui32ConfigBufAddr;
        sCommand.uCommand.sCfgChange.ui32DspConfigParamBuffAddr = ui32TsmUserCfgAddr;
        sCommand.uCommand.sCfgChange.ui32SizeInBytes = sizeof(BDSP_VideoEncodeTaskDatasyncSettings);

        pRaagaStage->pRaagaTask->lastEventType = sCommand.sCommandHeader.ui32CommandID;
        err = BDSP_Raaga_P_SendCommand_isr(pDevice->hCmdQueue[pRaagaStage->pRaagaTask->settings.dspIndex], &sCommand,(void *)pRaagaStage->pRaagaTask);

        if (BERR_SUCCESS != err)
        {
            BDBG_ERR(("BDSP_Raaga_P_SetStageSettings: CFG_Command failed!"));
            err = BERR_TRACE(err);
            goto end;
        }
    }
end:

    BDBG_LEAVE( BDSP_Raaga_P_SetVideoEncodeDatasyncSettings_isr );

    return err;
}

/***********************************************************************
Name        :   BDSP_Raaga_P_GetStageStatus

Type        :   PI Interface

Input       :   pStageHandle        -   Handle of the Stage for which status is requested.
                pStatusBuffer       -   Pointer to the memory where the Status provided back to the PI .
                statusSize      -   Size of the Status buffer provided by PI.

Return      :   Error Code to return SUCCESS or FAILURE

Functionality   :   Following are the operations performed.
        1)  Return the Algorithm status of the Stage.
***********************************************************************/

BERR_Code BDSP_Raaga_P_GetStageStatus(
    void *pStageHandle,
    void *pStatusBuffer,
    size_t statusSize)
{
    BDSP_RaagaStage *pRaagaStage = (BDSP_RaagaStage *)pStageHandle;
    BERR_Code err = BERR_SUCCESS;
    void *pAddress;

    BDBG_OBJECT_ASSERT(pRaagaStage, BDSP_RaagaStage);
    BDBG_ASSERT(pStatusBuffer);

    BDSP_MEM_P_ConvertOffsetToCacheAddr(pRaagaStage->pContext->pDevice->memHandle, pRaagaStage->sDramStatusBuffer.ui32DramBufferAddress, &pAddress);

    err = BDSP_Raaga_P_GetAlgorithmStatus(
        pRaagaStage->pContext->pDevice->memHandle,
        pRaagaStage->algorithm, pAddress,
        /* Since the buffer is shared between ids(tsm) and decode stage, the
        buffer size available for the decode stage is the offset to ids buffer */
        pRaagaStage->sFrameSyncOffset.ui32StatusOffset, /*pRaagaStage->sDramStatusBuffer.ui32BufferSizeInBytes,*/
        pStatusBuffer, statusSize);

    if ( err )
    {
        goto end;
    }

end:
    return err;
}

BERR_Code BDSP_Raaga_P_GetDatasyncStatus_isr(
    void *pStageHandle,
    BDSP_AudioTaskDatasyncStatus *pStatusBuffer)
{
    BDSP_RaagaStage *pRaagaStage = (BDSP_RaagaStage *)pStageHandle;
    void *pDatasyncStatus;

    BERR_Code err = BERR_SUCCESS;
    BDSP_Raaga_Audio_IdsTsmInfo sIdsTsmInfo;

    BDBG_OBJECT_ASSERT(pRaagaStage, BDSP_RaagaStage);
    BDBG_ASSERT(pStatusBuffer);

    pDatasyncStatus = (void *)((uint8_t *)pRaagaStage->sDramStatusBuffer.pDramBufferAddress +
                    pRaagaStage->sFrameSyncOffset.ui32StatusOffset);
    BDSP_P_CopyDataFromDram_isr(pRaagaStage->pContext->pDevice->memHandle,
                                  (void *)&sIdsTsmInfo,
                                  pDatasyncStatus, sizeof(sIdsTsmInfo));

    BKNI_Memcpy((void *)(volatile void*)pStatusBuffer,
        (void *)&(sIdsTsmInfo.sDatasyncInfo),
        sizeof(BDSP_AudioTaskDatasyncStatus));

    if (0 != ((BDSP_AudioTaskDatasyncStatus *)pStatusBuffer)->ui32StatusValid)
    {
        BDBG_MSG(("BDSP_Raaga_P_GetDatasyncStatus_isr: Datasync Status buffer is not in valid status"));
        err = (BDSP_ERR_BAD_DEVICE_STATE);
        goto end;
    }

end:
    return err;
}

BERR_Code BDSP_Raaga_P_GetTsmStatus_isr(
    void *pStageHandle,
    BDSP_AudioTaskTsmStatus *pStatusBuffer)
{
    BDSP_RaagaStage *pRaagaStage = (BDSP_RaagaStage *)pStageHandle;
    void *ptsmStatus;


    BERR_Code err = BERR_SUCCESS;
    BDSP_Raaga_Audio_IdsTsmInfo  sIdsTsmInfo;

    BDBG_OBJECT_ASSERT(pRaagaStage, BDSP_RaagaStage);
    BDBG_ASSERT(pStatusBuffer);

    ptsmStatus = (void *)((uint8_t *)pRaagaStage->sDramStatusBuffer.pDramBufferAddress+
                    pRaagaStage->sFrameSyncOffset.ui32StatusOffset);
    BDSP_P_CopyDataFromDram_isr(pRaagaStage->pContext->pDevice->memHandle,
                                  (void *)&sIdsTsmInfo,
                                  ptsmStatus, sizeof(sIdsTsmInfo));
    BKNI_Memcpy((void *)(volatile void*)pStatusBuffer,
        (void *)&(sIdsTsmInfo.sTsmInfo),
        sizeof(BDSP_AudioTaskTsmStatus));

    if (0 != ((BDSP_AudioTaskTsmStatus *)pStatusBuffer)->ui32StatusValid)
    {
        BDBG_MSG(("BDSP_Raaga_P_GetTsmStatus_isr: TSM Status buffer is not in valid status"));
        err = (BDSP_ERR_BAD_DEVICE_STATE);
        goto end;
    }

end:
    return err;
}

/***********************************************************************
Name        :   BDSP_Raaga_P_Pause

Type        :   PI Interface

Input       :   pTaskHandle -   Handle of the Task which needs to be Paused.

Return      :   Error Code to return SUCCESS or FAILURE

Functionality   :   Following are the operations performed.
        1)  Check if the task is started and not already paused.
        2)  Send the Pause Command to the FW and wait for the acknowledgement.
***********************************************************************/

BERR_Code BDSP_Raaga_P_Pause(void *pTaskHandle)
{
    BDSP_RaagaTask *pRaagaTask = (BDSP_RaagaTask *)pTaskHandle;
    BDSP_Raaga  *pDevice= pRaagaTask->pContext->pDevice;
    BERR_Code err=BERR_SUCCESS;
    BDSP_Raaga_P_MsgType      eMsgType;
    BDSP_Raaga_P_Command sCommand;
    BDSP_Raaga_P_Response sRsp;

    BDBG_OBJECT_ASSERT(pRaagaTask, BDSP_RaagaTask);

    if (pRaagaTask->isStopped == true)
    {
        BDBG_WRN(("Task is not started yet. Ignoring the Pause command"));
        goto end;
    }
    else
    {
        if (pRaagaTask->paused == true)
        {
            BDBG_WRN(("Task is already in Pause state. Ignoring the Pause command"));
            goto end;
        }
        else
        {
            /* Create Pause command */
            BKNI_Memset((void *)&sRsp,0,sizeof(BDSP_Raaga_P_Response));
            BKNI_Memset((void *)&sCommand,0,sizeof(BDSP_Raaga_P_Command));

            sCommand.sCommandHeader.ui32CommandID = BDSP_RAAGA_PAUSE_COMMAND_ID;
            sCommand.sCommandHeader.ui32CommandCounter =  pRaagaTask->commandCounter++;
            sCommand.sCommandHeader.ui32TaskID =  pRaagaTask->taskId;
            sCommand.sCommandHeader.eResponseType = BDSP_Raaga_P_ResponseType_eAckRequired;
            sCommand.sCommandHeader.ui32CommandSizeInBytes =  sizeof(BDSP_Raaga_P_Command);

            pRaagaTask->lastEventType = sCommand.sCommandHeader.ui32CommandID;
            BKNI_ResetEvent(pRaagaTask->hEvent);

            err = BDSP_Raaga_P_SendCommand(
                pDevice->hCmdQueue[pRaagaTask->settings.dspIndex],
                &sCommand,pRaagaTask);
            if (BERR_SUCCESS != err)
            {
                BDBG_ERR(("BDSP_Raaga_P_Pause: Pause Command failed!"));
                err = BERR_TRACE(err);
                goto end;
            }
            /* Wait for Ack_Response_Received event w/ timeout */
            err = BKNI_WaitForEvent(pRaagaTask->hEvent, BDSP_RAAGA_EVENT_TIMEOUT_IN_MS);
            if (BERR_TIMEOUT == err)
            {
                BDBG_ERR(("BDSP_Raaga_P_Pause: Pause Command ACK timeout! Triggering Watchdog"));
                err = BERR_TRACE(err);
                goto end;
            }

            eMsgType = BDSP_Raaga_P_MsgType_eSyn;
            err = BDSP_Raaga_P_GetMsg(pRaagaTask->hSyncMsgQueue, (void *)&sRsp, eMsgType);
            if (BERR_SUCCESS != err)
            {
                BDBG_ERR(("BDSP_Raaga_P_Pause: Unable to read ACK!"));
                err = BERR_TRACE(err);
                goto end;
            }

            if ((sRsp.sCommonAckResponseHeader.eStatus != BERR_SUCCESS)||
                (sRsp.sCommonAckResponseHeader.ui32ResponseID != BDSP_RAAGA_PAUSE_ACK_ID)||
                (sRsp.sCommonAckResponseHeader.ui32TaskID != pRaagaTask->taskId))
            {
                BDBG_ERR(("sRsp.sCommonAckResponseHeader.eStatus =%d",sRsp.sCommonAckResponseHeader.eStatus));
                BDBG_ERR(("BDSP_Raaga_P_Pause: Pause Command response not received successfully!"));
                err = BERR_TRACE(sRsp.sCommonAckResponseHeader.eStatus);
                goto end;
            }
            pRaagaTask->paused = true;
        }
    }
    end:
    return err;
}

/***********************************************************************
Name        :   BDSP_Raaga_P_Resume

Type        :   PI Interface

Input       :   pTaskHandle -   Handle of the Task which needs to be Resumed.

Return      :   Error Code to return SUCCESS or FAILURE

Functionality   :   Following are the operations performed.
        1)  Check if the task is started and in Paused state.
        2)  Send the Resume Command to the FW and wait for the acknowledgement.
***********************************************************************/

BERR_Code BDSP_Raaga_P_Resume(void *pTaskHandle)
{
    BDSP_RaagaTask *pRaagaTask = (BDSP_RaagaTask *)pTaskHandle;
    BDSP_Raaga  *pDevice= pRaagaTask->pContext->pDevice;
    BERR_Code err=BERR_SUCCESS;
    BDSP_Raaga_P_MsgType      eMsgType;
    BDSP_Raaga_P_Command sCommand;
    BDSP_Raaga_P_Response sRsp;

    BDBG_OBJECT_ASSERT(pRaagaTask, BDSP_RaagaTask);

    if (pRaagaTask->isStopped == true)
    {
        BDBG_WRN(("Task is not started yet. Ignoring the Resume command"));
        goto end;
    }
    else
    {
        if (pRaagaTask->paused == false)
        {
            BDBG_WRN(("Task is already in Resume state. Ignoring the Resume command"));
            goto end;
        }
        else
        {
            /* Create Resume command */
            BKNI_Memset((void *)&sRsp,0,sizeof(BDSP_Raaga_P_Response));
            BKNI_Memset((void *)&sCommand,0,sizeof(BDSP_Raaga_P_Command));

            sCommand.sCommandHeader.ui32CommandID = BDSP_RAAGA_RESUME_COMMAND_ID;
            sCommand.sCommandHeader.ui32CommandCounter =  pRaagaTask->commandCounter++;
            sCommand.sCommandHeader.ui32TaskID =  pRaagaTask->taskId;
            sCommand.sCommandHeader.eResponseType = BDSP_Raaga_P_ResponseType_eAckRequired;
            sCommand.sCommandHeader.ui32CommandSizeInBytes =  sizeof(BDSP_Raaga_P_Command);

            pRaagaTask->lastEventType = sCommand.sCommandHeader.ui32CommandID;
            BKNI_ResetEvent(pRaagaTask->hEvent);

            err = BDSP_Raaga_P_SendCommand(
                pDevice->hCmdQueue[pRaagaTask->settings.dspIndex],
                &sCommand,pRaagaTask);
            if (BERR_SUCCESS != err)
            {
                BDBG_ERR(("BDSP_Raaga_P_Resume: Resume Command failed!"));
                err = BERR_TRACE(err);
                goto end;
            }
            /* Wait for Ack_Response_Received event w/ timeout */
            err = BKNI_WaitForEvent(pRaagaTask->hEvent, BDSP_RAAGA_EVENT_TIMEOUT_IN_MS);
            if (BERR_TIMEOUT == err)
            {
                BDBG_ERR(("BDSP_Raaga_P_Resume: Resume Command ACK timeout! Triggering Watchdog"));
                err = BERR_TRACE(err);
                goto end;
            }

            eMsgType = BDSP_Raaga_P_MsgType_eSyn;
            err = BDSP_Raaga_P_GetMsg(pRaagaTask->hSyncMsgQueue, (void *)&sRsp, eMsgType);
            if (BERR_SUCCESS != err)
            {
                BDBG_ERR(("BDSP_Raaga_P_Resume: Unable to read ACK!"));
                err = BERR_TRACE(err);
                goto end;
            }

            if ((sRsp.sCommonAckResponseHeader.eStatus != BERR_SUCCESS)||
                (sRsp.sCommonAckResponseHeader.ui32ResponseID != BDSP_RAAGA_RESUME_ACK_ID)||
                (sRsp.sCommonAckResponseHeader.ui32TaskID != pRaagaTask->taskId))
            {
                BDBG_ERR(("sRsp.sCommonAckResponseHeader.eStatus =%d",sRsp.sCommonAckResponseHeader.eStatus));
                BDBG_ERR(("BDSP_Raaga_P_Resume: Resume Command response not received successfully!"));
                err = BERR_TRACE(sRsp.sCommonAckResponseHeader.eStatus);
                goto end;
            }
            pRaagaTask->paused = false;
        }
    }
    end:
    return err;
}

/***********************************************************************
Name        :   BDSP_Raaga_P_Advance

Type        :   PI Interface

Input       :   pTaskHandle -   Handle of the Task which needs to be Advanced.
                ms          -   Time provided to advance in milli-seconds.

Return      :   Error Code to return SUCCESS or FAILURE

Functionality   :   Following are the operations performed.
        1)  Check if the task is started and in Paused state.
        2)  Send the Advance Command to the FW with time and wait for the acknowledgement.
***********************************************************************/

BERR_Code BDSP_Raaga_P_Advance(
    void *pTaskHandle,
    unsigned ms)
{
    BDSP_RaagaTask *pRaagaTask = (BDSP_RaagaTask *)pTaskHandle;
    BDSP_Raaga  *pDevice= pRaagaTask->pContext->pDevice;
    BERR_Code err=BERR_SUCCESS;
    BDSP_Raaga_P_MsgType      eMsgType;
    BDSP_Raaga_P_Command sCommand;
    BDSP_Raaga_P_Response sRsp;

    BDBG_OBJECT_ASSERT(pRaagaTask, BDSP_RaagaTask);

    if (pRaagaTask->isStopped == true)
    {
        BDBG_WRN(("Task is not started yet. Ignoring the Advance command"));
        goto end;
    }
    else
    {
        if (pRaagaTask->paused == false)
        {
            BDBG_WRN(("Task 0x%p is not in Pause state. Ignoring the Advance command", (void *)pRaagaTask));
            goto end;
        }
        else
        {
            /* Advance command */
            BKNI_Memset((void *)&sRsp,0,sizeof(BDSP_Raaga_P_Response));
            BKNI_Memset((void *)&sCommand,0,sizeof(BDSP_Raaga_P_Command));

            sCommand.sCommandHeader.ui32CommandID = BDSP_RAAGA_FRAME_ADVANCE_COMMAND_ID;
            sCommand.sCommandHeader.ui32CommandCounter =  pRaagaTask->commandCounter++;
            sCommand.sCommandHeader.ui32TaskID =  pRaagaTask->taskId;
            sCommand.sCommandHeader.eResponseType = BDSP_Raaga_P_ResponseType_eAckRequired;
            sCommand.sCommandHeader.ui32CommandSizeInBytes =  sizeof(BDSP_Raaga_P_Command);

            sCommand.uCommand.sFrameAdvance.ui32DurationOfFrameAdv = ms * 45;

            pRaagaTask->lastEventType = sCommand.sCommandHeader.ui32CommandID;
            BKNI_ResetEvent(pRaagaTask->hEvent);

            err = BDSP_Raaga_P_SendCommand(
                pDevice->hCmdQueue[pRaagaTask->settings.dspIndex],
                &sCommand,pRaagaTask);
            if (BERR_SUCCESS != err)
            {
                BDBG_ERR(("BDSP_Raaga_P_Advance: Advance Command failed!"));
                err = BERR_TRACE(err);
                goto end;
            }
            /* Wait for Ack_Response_Received event w/ timeout */
            err = BKNI_WaitForEvent(pRaagaTask->hEvent, BDSP_RAAGA_EVENT_TIMEOUT_IN_MS);
            if (BERR_TIMEOUT == err)
            {
                BDBG_ERR(("BDSP_Raaga_P_Advance: Advance Command ACK timeout! Triggering Watchdog"));
                err = BERR_TRACE(err);
                goto end;
            }

            eMsgType = BDSP_Raaga_P_MsgType_eSyn;
            err = BDSP_Raaga_P_GetMsg(pRaagaTask->hSyncMsgQueue, (void *)&sRsp, eMsgType);
            if (BERR_SUCCESS != err)
            {
                BDBG_ERR(("BDSP_Raaga_P_Advance: Unable to read ACK!"));
                err = BERR_TRACE(err);
                goto end;
            }

            if ((sRsp.sCommonAckResponseHeader.eStatus != BERR_SUCCESS)||
                (sRsp.sCommonAckResponseHeader.ui32ResponseID != BDSP_RAAGA_FRAME_ADVANCE_ACK_ID)||
                (sRsp.sCommonAckResponseHeader.ui32TaskID != pRaagaTask->taskId))
            {
                BDBG_ERR(("sRsp.sCommonAckResponseHeader.eStatus =%d",sRsp.sCommonAckResponseHeader.eStatus));
                BDBG_ERR(("BDSP_Raaga_P_Advance: Advance Command response not received successfully!"));
                err = BERR_TRACE(sRsp.sCommonAckResponseHeader.eStatus);
                goto end;
            }
        }
    }
    end:
    return err;
}

BERR_Code BDSP_Raaga_P_GetPictureQueueCount_isr(
    void *pTaskHandle,
    unsigned *pPictureCount,
    BDSP_Raaga_P_MsgQueueHandle      hPictureQueue
    )
{
    BDSP_RaagaTask *pRaagaTask = (BDSP_RaagaTask *)pTaskHandle;
    BERR_Code err=BERR_SUCCESS;
    raaga_dramaddr  dramReadAddr=0;
    raaga_dramaddr  dramWriteAddr=0;
    raaga_dramaddr  maskReadAddr=0;
    raaga_dramaddr  maskWriteAddr=0;


    BDBG_OBJECT_ASSERT(pRaagaTask, BDSP_RaagaTask);

    if (pRaagaTask->isStopped == true)
    {
        BDBG_MSG(("%s : Task is not started yet.", __FUNCTION__));
        goto end;
    }

    dramReadAddr=BDSP_Read32_isr(hPictureQueue->hRegister,BCHP_RAAGA_DSP_FW_CFG_FIFO_0_BASE_ADDR + 4 * 4 * hPictureQueue->i32FifoId +
        BDSP_RAAGA_P_FIFO_READ_OFFSET + hPictureQueue->ui32DspOffset);

    dramWriteAddr=BDSP_Read32_isr(hPictureQueue->hRegister,BCHP_RAAGA_DSP_FW_CFG_FIFO_0_BASE_ADDR + 4 * 4 * hPictureQueue->i32FifoId +
        BDSP_RAAGA_P_FIFO_WRITE_OFFSET + hPictureQueue->ui32DspOffset);

    BDBG_MSG(("dramReadAddr > %x", dramReadAddr));
    BDBG_MSG(("dramWriteAddr > %x", dramWriteAddr));

    maskReadAddr=dramReadAddr;
    maskWriteAddr=dramWriteAddr;

    /*Sanity check*/
    /*Checking boundness of read pointer- if((readptr>endaddr) OR (readptr<baseaddr)) read ptr not within bound*/
    if ((maskReadAddr>hPictureQueue->ui32EndAddr)||(maskReadAddr<hPictureQueue->ui32BaseAddr))
    {
        BDBG_ERR(("Read pointer not within bounds in Message Queue"));
        goto end;
    }

    /*Checking boundness of write pointer - if((writeptr>endaddr) OR (writeptr<baseaddr))  write ptr not within bound*/
    if ((maskWriteAddr>hPictureQueue->ui32EndAddr)||(maskWriteAddr<hPictureQueue->ui32BaseAddr))
    {
        BDBG_ERR(("Write pointer not within bounds in Message Queue"));
        goto end;
    }

    /* checking write ptrs */
    if (hPictureQueue->ui32ReadAddr!=maskReadAddr)
    {
        BDBG_ERR(("Read pointer corrupted in the Message Queue"));
        err =  BERR_TRACE(BDSP_ERR_BAD_DEVICE_STATE);
        goto end;
    }
    /* End of Sanity Check */


    /*Calc Picture count in the message queue*/

    /* Case1:if(maskwriteptr>maskreadptr)*/
    if (maskWriteAddr > maskReadAddr)
    {
        *pPictureCount = (maskWriteAddr - maskReadAddr)>>2;/* Diving by 4*/
    }


    /* Case2:if(maskreadptr>maskwriteptr) */
    if (maskReadAddr>maskWriteAddr)
    {
        *pPictureCount = ((hPictureQueue->ui32EndAddr-maskReadAddr)+
            (maskWriteAddr-hPictureQueue->ui32BaseAddr))>>2;
    }


    /* Case3:if(maskreadptr==maskwriteptr) */
    if (maskReadAddr==maskWriteAddr)
    {
        /* The buffer is empty */
        *pPictureCount = 0x0;
    }

    end:
    return err;
}

BERR_Code BDSP_Raaga_P_GetPictureCount_isr(
    void *pTaskHandle,
    unsigned *pPictureCount)
{
    BDSP_RaagaTask *pRaagaTask = (BDSP_RaagaTask *)pTaskHandle;
    BERR_Code err=BERR_SUCCESS;
    BDBG_ENTER(BDSP_Raaga_P_GetPictureCount_isr);
    BDBG_OBJECT_ASSERT(pRaagaTask, BDSP_RaagaTask);

    if (pRaagaTask->isStopped == true)
    {
        BDBG_MSG(("%s : Task is not started yet.", __FUNCTION__));
        goto end;
    }

    err = BDSP_Raaga_P_GetPictureQueueCount_isr(pTaskHandle,pPictureCount,pRaagaTask->hPDQueue);
    end:
    BDBG_LEAVE(BDSP_Raaga_P_GetPictureCount_isr);
    return err;
}

BERR_Code BDSP_Raaga_P_PeekAtPicture_isr(
    void *pTaskHandle,
    unsigned index,
    raaga_dramaddr   **pUnifiedPictureAddr)
{
    BDSP_RaagaTask *pRaagaTask = (BDSP_RaagaTask *)pTaskHandle;
    BERR_Code err=BERR_SUCCESS;
    unsigned long ulTemp = 0;
    raaga_dramaddr  uiUPBPhysicalAddr=0;
    raaga_dramaddr  ui32dramReadAddr=0;
    raaga_dramaddr  ui32dramWriteAddr=0;
    raaga_dramaddr  ui32maskReadAddr=0;
    raaga_dramaddr  ui32maskWriteAddr=0;
    int32_t i32BytesToBeRead=0;
    void *pvMsgQueueReadAddr=NULL;

    BDBG_ENTER(BDSP_Raaga_P_PeekAtPicture_isr);
    BDBG_OBJECT_ASSERT(pRaagaTask, BDSP_RaagaTask);
    BSTD_UNUSED( index );

    if (pRaagaTask->isStopped == true)
    {
        BDBG_MSG(("BDSP_Raaga_P_PeekAtPicture_isr: Task is not started yet. "));
        goto end;
    }

    ui32dramReadAddr=BDSP_Read32_isr(pRaagaTask->hPDQueue->hRegister,BCHP_RAAGA_DSP_FW_CFG_FIFO_0_BASE_ADDR + 4 * 4 * pRaagaTask->hPDQueue->i32FifoId +
        BDSP_RAAGA_P_FIFO_READ_OFFSET + pRaagaTask->hPDQueue->ui32DspOffset);

    ui32dramWriteAddr=BDSP_Read32_isr(pRaagaTask->hPDQueue->hRegister,BCHP_RAAGA_DSP_FW_CFG_FIFO_0_BASE_ADDR + 4 * 4 * pRaagaTask->hPDQueue->i32FifoId +
        BDSP_RAAGA_P_FIFO_WRITE_OFFSET + pRaagaTask->hPDQueue->ui32DspOffset);

    BDBG_MSG(("ui32dramReadAddr > %x", ui32dramReadAddr));
    BDBG_MSG(("ui32dramWriteAddr > %x", ui32dramWriteAddr));
    ui32maskReadAddr=ui32dramReadAddr;
    ui32maskWriteAddr=ui32dramWriteAddr;

    /*Sanity check*/
    /* checking write ptr boundness- if((writeptr>endaddr)|(writeptr<baseaddr)) write ptr is not within bound*/
    if ((ui32maskWriteAddr>pRaagaTask->hPDQueue->ui32EndAddr)||(ui32maskWriteAddr<pRaagaTask->hPDQueue->ui32BaseAddr))
    {
        BDBG_ERR(("Write pointer not within bounds in Message Queue"));
        err = BERR_TRACE(BDSP_ERR_BAD_DEVICE_STATE);
        goto end;
    }


    /* checking read ptr boundness- if((readptr>endaddr)|(readptr<baseaddr)) read ptr is not within bound*/
    if ((ui32maskReadAddr>pRaagaTask->hPDQueue->ui32EndAddr)||(ui32maskReadAddr<pRaagaTask->hPDQueue->ui32BaseAddr))
    {
        BDBG_ERR(("Read pointer not within bounds in Message Queue"));
        err = BERR_TRACE(BDSP_ERR_BAD_DEVICE_STATE);
        goto end;
    }

    /*Updating write ptr */
    pRaagaTask->hPDQueue->ui32WriteAddr= ui32maskWriteAddr;

    /* checking read ptrs to see if they are the same */
    if ((pRaagaTask->hPDQueue->ui32ReadAddr)!=ui32maskReadAddr)
    {
        BDBG_ERR(("Read pointer corrupted in the Message Queue"));
        err = BERR_TRACE(BDSP_ERR_BAD_DEVICE_STATE );
        goto end;
    }

    /* End of Sanity Check */

    /*******************************************************************
   Different cases:

    If maskreadptr>maskwriteptr
     ReadPtrMSB   WritePtrMSB
        0                   0                   This condn. is not possible
        0                   1                   (end-read)+(write-base)
        1                   0                     (end-read)+(write-base)
        1                   1                      this condn. is not possible

  If maskwriteptr>maskreadptr
   ReadptrMSB   WritePtrMSB
    0                   0               write-read
    0                   1                  this condn. not possible
    1                   0                  this condn. not possible
    1                   1                  write-read

  If maskreadptr==maskwriteptr
  If the toggle bits are the same,no message to read
  If the toggle bits are different all the messages have to be read


 ***********************************************************************/
    /*Condn. for reading messages from the message queue into the message buffer*/
    /* If no msg is to be read, generate a BRAP_ERR_BUFFER_EMPTY error(new error defined in brap.h)*/

    /* Checking if a msg is present */

    /* Case1:if(readptr>writeptr)*/
    if (ui32maskReadAddr > ui32maskWriteAddr)
    {
        i32BytesToBeRead=(pRaagaTask->hPDQueue->ui32EndAddr-ui32maskReadAddr)+
            (ui32maskWriteAddr-pRaagaTask->hPDQueue->ui32BaseAddr);
    }

    /* Case2:if(writeptr>readptr) */
    if (ui32maskWriteAddr>ui32maskReadAddr)
    {
        i32BytesToBeRead=ui32maskWriteAddr-ui32maskReadAddr;
    }

    /*Case 3:if readptr == writeptr */
    if (ui32maskWriteAddr ==ui32maskReadAddr)
    {
        /*All messages have to be read*/
        i32BytesToBeRead=pRaagaTask->hPDQueue->ui32EndAddr-pRaagaTask->hPDQueue->ui32BaseAddr;
    }
    if (i32BytesToBeRead < 0)
    {
        BDBG_ERR(("The Message Queue is empty.No message is present."));
        err = BERR_TRACE(BDSP_ERR_BUFFER_EMPTY);
        goto end;
    }

    BDBG_MSG(("ui32maskReadAddr = 0x%x",ui32maskReadAddr));

    pvMsgQueueReadAddr = (void *)((uint8_t *)pRaagaTask->hPDQueue->pBaseAddr + (ui32maskReadAddr - pRaagaTask->hPDQueue->ui32BaseAddr ));

    /*Reading Message from the message queue into the message buffer*/
    uiUPBPhysicalAddr=BDSP_P_MemRead32_isr(pRaagaTask->hPDQueue->hHeap,pvMsgQueueReadAddr);

    BDBG_MSG(("uiUPBPhysicalAddr = 0x%x",uiUPBPhysicalAddr));

    ulTemp = (unsigned long)uiUPBPhysicalAddr;
    *pUnifiedPictureAddr = (uint32_t *)ulTemp;

    BDBG_MSG(("*pUnifiedPictureAddr = 0x%p",(void *)(*pUnifiedPictureAddr)));

    end:
    BDBG_LEAVE(BDSP_Raaga_P_PeekAtPicture_isr);
    return err;
}

BERR_Code BDSP_Raaga_P_GetNextPicture_isr(
    void *pTaskHandle,
    uint32_t   **pUnifiedPictureAddr)
{
    BDSP_RaagaTask *pRaagaTask = (BDSP_RaagaTask *)pTaskHandle;
    BERR_Code err=BERR_SUCCESS;
    bool bReadUpdate = true;
    raaga_dramaddr  uiUPBPhysicalAddr=0;
    unsigned long   ulTemp = 0;
    raaga_dramaddr  ui32dramReadAddr=0;
    raaga_dramaddr  ui32dramWriteAddr=0;
    raaga_dramaddr  ui32maskReadAddr=0;
    raaga_dramaddr  ui32maskWriteAddr=0;
    int32_t i32BytesToBeRead=0;
    void *pvMsgQueueReadAddr=NULL;


    BDBG_ENTER(BDSP_Raaga_P_GetNextPicture_isr);
    BDBG_OBJECT_ASSERT(pRaagaTask, BDSP_RaagaTask);

    if (pRaagaTask->isStopped == true)
    {
        BDBG_MSG(("BDSP_Raaga_P_GetNextPicture_isr : Task is not started yet. "));
        goto end;
    }


    ui32dramReadAddr=BDSP_Read32_isr(pRaagaTask->hPDQueue->hRegister,BCHP_RAAGA_DSP_FW_CFG_FIFO_0_BASE_ADDR + 4 * 4 * pRaagaTask->hPDQueue->i32FifoId +
        BDSP_RAAGA_P_FIFO_READ_OFFSET + pRaagaTask->hPDQueue->ui32DspOffset);

    ui32dramWriteAddr=BDSP_Read32_isr(pRaagaTask->hPDQueue->hRegister,BCHP_RAAGA_DSP_FW_CFG_FIFO_0_BASE_ADDR + 4 * 4 * pRaagaTask->hPDQueue->i32FifoId +
        BDSP_RAAGA_P_FIFO_WRITE_OFFSET + pRaagaTask->hPDQueue->ui32DspOffset);

    BDBG_MSG(("ui32dramReadAddr > %x", ui32dramReadAddr));
    BDBG_MSG(("ui32dramWriteAddr > %x", ui32dramWriteAddr));
    ui32maskReadAddr=ui32dramReadAddr;
    ui32maskWriteAddr=ui32dramWriteAddr;

    /*Sanity check*/
    /* checking write ptr boundness- if((writeptr>endaddr)|(writeptr<baseaddr)) write ptr is not within bound*/
    if ((ui32maskWriteAddr>pRaagaTask->hPDQueue->ui32EndAddr)||(ui32maskWriteAddr<pRaagaTask->hPDQueue->ui32BaseAddr))
    {
        BDBG_ERR(("Write pointer not within bounds in Message Queue"));
        BDBG_ASSERT(0);
        err = BERR_TRACE(BDSP_ERR_BAD_DEVICE_STATE);
        goto end;
    }


    /* checking read ptr boundness- if((readptr>endaddr)|(readptr<baseaddr)) read ptr is not within bound*/
    if ((ui32maskReadAddr>pRaagaTask->hPDQueue->ui32EndAddr)||(ui32maskReadAddr<pRaagaTask->hPDQueue->ui32BaseAddr))
    {
        BDBG_ERR(("Read pointer not within bounds in Message Queue"));
        BDBG_ASSERT(0);
        err = BERR_TRACE(BDSP_ERR_BAD_DEVICE_STATE);
        goto end;
    }

    /*Updating write ptr */
    pRaagaTask->hPDQueue->ui32WriteAddr= ui32maskWriteAddr;

    /* checking read ptrs to see if they are the same */
    if ((pRaagaTask->hPDQueue->ui32ReadAddr)!=ui32maskReadAddr)
    {
        BDBG_ERR(("Read pointer corrupted in the Message Queue"));
        BDBG_ASSERT(0);
        err = BERR_TRACE(BDSP_ERR_BAD_DEVICE_STATE );
        goto end;
    }

    /* End of Sanity Check */

    /*******************************************************************
    Different cases:

    If maskreadptr>maskwriteptr
    ReadPtrMSB   WritePtrMSB
       0                   0                   This condn. is not possible
       0                   1                   (end-read)+(write-base)
       1                   0                     (end-read)+(write-base)
       1                   1                      this condn. is not possible

    If maskwriteptr>maskreadptr
    ReadptrMSB   WritePtrMSB
    0                   0               write-read
    0                   1                  this condn. not possible
    1                   0                  this condn. not possible
    1                   1                  write-read

    If maskreadptr==maskwriteptr
    If the toggle bits are the same,no message to read
    If the toggle bits are different all the messages have to be read


    ***********************************************************************/
    /*Condn. for reading messages from the message queue into the message buffer*/
    /* If no msg is to be read, generate a BRAP_ERR_BUFFER_EMPTY error(new error defined in brap.h)*/

    /* Checking if a msg is present */

    /* Case1:if(readptr>writeptr)*/
    if (ui32maskReadAddr > ui32maskWriteAddr)
    {
        i32BytesToBeRead=(pRaagaTask->hPDQueue->ui32EndAddr-ui32maskReadAddr)+
            (ui32maskWriteAddr-pRaagaTask->hPDQueue->ui32BaseAddr);
    }

    /* Case2:if(writeptr>readptr) */
    if (ui32maskWriteAddr>ui32maskReadAddr)
    {
        i32BytesToBeRead=ui32maskWriteAddr-ui32maskReadAddr;
    }

    /*Case 3:if readptr == writeptr */
    if (ui32maskWriteAddr ==ui32maskReadAddr)
    {
        /*All messages have to be read*/
        i32BytesToBeRead=pRaagaTask->hPDQueue->ui32EndAddr-pRaagaTask->hPDQueue->ui32BaseAddr;
    }
    if (i32BytesToBeRead < 0)
    {
        BDBG_ERR(("The Message Queue is empty.No message is present."));
        BDBG_ASSERT(0);
        err = BERR_TRACE(BDSP_ERR_BUFFER_EMPTY);
        goto end;
    }

    pvMsgQueueReadAddr = (void *)((uint8_t *)pRaagaTask->hPDQueue->pBaseAddr + (ui32maskReadAddr - pRaagaTask->hPDQueue->ui32BaseAddr ));



    /*Reading Message from the message queue into the message buffer*/
    uiUPBPhysicalAddr=BDSP_P_MemRead32_isr(pRaagaTask->hPDQueue->hHeap,pvMsgQueueReadAddr);

    BDBG_MSG(("In BRAP_VID_GetNextPicture_isr uiUPBPhysicalAddr = 0x%x",uiUPBPhysicalAddr));

    ulTemp = (unsigned long)uiUPBPhysicalAddr;
    *pUnifiedPictureAddr = (uint32_t *)ulTemp;

    BDBG_MSG(("In BDSP_Raaga_P_GetNextPicture_isr *pUnifiedPictureAddr = 0x%p",(void *)*pUnifiedPictureAddr));

    if (bReadUpdate == true)
    {
        ui32dramReadAddr=ui32dramReadAddr+4;
        if (ui32dramReadAddr==pRaagaTask->hPDQueue->ui32EndAddr)
            ui32dramReadAddr=pRaagaTask->hPDQueue->ui32BaseAddr;

        /*updating read ptr in the Queue Attribute Structure*/
        BDSP_Write32_isr(pRaagaTask->hPDQueue->hRegister,BCHP_RAAGA_DSP_FW_CFG_FIFO_0_BASE_ADDR + 4 * 4 * pRaagaTask->hPDQueue->i32FifoId +
            BDSP_RAAGA_P_FIFO_READ_OFFSET + pRaagaTask->hPDQueue->ui32DspOffset, ui32dramReadAddr);
        BDBG_MSG(("ui32dramReadAddr > %x", ui32dramReadAddr));
        BDBG_MSG(("ui32dramWriteAddr > %x", ui32dramWriteAddr));

        /*updating read ptr in the handle*/
        pRaagaTask->hPDQueue->ui32ReadAddr = ui32dramReadAddr;
    }

    end:
    BDBG_LEAVE(BDSP_Raaga_P_GetNextPicture_isr);
    return err;
}

BERR_Code BDSP_Raaga_P_ReleasePicture_isr(
    void *pTaskHandle,
    uint32_t *pUnifiedPicture)
{
    BDSP_RaagaTask *pRaagaTask = (BDSP_RaagaTask *)pTaskHandle;
    unsigned int    uiBuffSize = 4;
    uint32_t    *temp = pUnifiedPicture;
    BERR_Code err=BERR_SUCCESS;

    BDBG_ENTER(BDSP_Raaga_P_ReleasePicture_isr);
    BDBG_OBJECT_ASSERT(pRaagaTask, BDSP_RaagaTask);

    if (pRaagaTask->isStopped == true)
    {
        BDBG_MSG(("BDSP_Raaga_P_ReleasePicture_isr : Task is not started yet. "));
        goto end;
    }

    BDBG_MSG(("In BDSP_Raaga_P_ReleasePicture_isr pUnifiedPicture = 0x%p",(void *)pUnifiedPicture));

    err = BDSP_Raaga_P_WriteVideoMsg_isr(pRaagaTask->hDSQueue, (void *)&temp,uiBuffSize);

    end:
    BDBG_LEAVE(BDSP_Raaga_P_ReleasePicture_isr);
    return err;
}

BERR_Code BDSP_Raaga_P_GetPictureDropPendingCount_isr(
    void *pTaskHandle,
    unsigned *pPictureDropPendingCount)
{
    BDSP_RaagaTask *pRaagaTask = (BDSP_RaagaTask *)pTaskHandle;
    BERR_Code err=BERR_SUCCESS;
    uint32_t ui32NumBranchesValid = 0, ui32NumStagesValid = 0;
    unsigned int uiBranchId = 0, uiStageId = 0;
    unsigned long ulStatusBufAddr;
    BDSP_CIT_P_OpStgInfo *psOpStgInfo = NULL;

    BDBG_ENTER(BDSP_Raaga_P_GetPictureDropPendingCount_isr);
    BDBG_OBJECT_ASSERT(pRaagaTask, BDSP_RaagaTask);

    if (pRaagaTask->isStopped == true)
    {
        BDBG_MSG(("BDSP_Raaga_P_GetPictureDropPendingCount_isr: Task is not started yet. "));
        *pPictureDropPendingCount = 0;
        goto end;
    }

    ui32NumBranchesValid = pRaagaTask->videoCitOutput.ui32NumBranches;

    for (uiBranchId = 0; uiBranchId < ui32NumBranchesValid; uiBranchId++)
    {
        /* Get the status buffer address for this stage */
        ui32NumStagesValid = pRaagaTask->videoCitOutput.sCitBranchInfo[uiBranchId].ui32NumStages;
        for (uiStageId = 0; uiStageId < ui32NumStagesValid; uiStageId++)
        {
            psOpStgInfo = &(pRaagaTask->videoCitOutput.sCitBranchInfo[uiBranchId].sCitStgInfo[uiStageId]);
            /* use docode node status buffer */
            /* TODO: Replace this hardcoding with proper define */
            BDBG_WRN(("uint32_t being converted to a pointer. Needs to be corrected"));
            ulStatusBufAddr = (unsigned long)psOpStgInfo->sFwOpNodeInfo[1].ui32StatusBufAdr;

            /* Check if this is a decode stage */
            if (BDSP_RAAGA_P_ALGORITHM_TYPE(psOpStgInfo->eAlgorithm) == BDSP_AlgorithmType_eVideoDecode)
            {
                *pPictureDropPendingCount = (unsigned)ulStatusBufAddr;
                BDSP_MEM_P_FlushCache_isr(pRaagaTask->pContext->pDevice->memHandle, (void *)ulStatusBufAddr, sizeof(*pPictureDropPendingCount));
            }
        }
    }

    end:
    BDBG_LEAVE(BDSP_Raaga_P_GetPictureDropPendingCount_isr);
    return err;
}

BERR_Code BDSP_Raaga_P_RequestPictureDrop_isr(
    void *pTaskHandle,
    unsigned *pPictureDropRequestCount)
{
    BDSP_RaagaTask *pRaagaTask = (BDSP_RaagaTask *)pTaskHandle;
    BDSP_Raaga  *pDevice= pRaagaTask->pContext->pDevice;
    BERR_Code err=BERR_SUCCESS;
    BDSP_Raaga_P_Command sCommand;

    BDBG_ENTER(BDSP_Raaga_P_RequestPictureDrop_isr);
    BDBG_OBJECT_ASSERT(pRaagaTask, BDSP_RaagaTask);

    if (pRaagaTask->isStopped == true)
    {
        BDBG_MSG(("BDSP_Raaga_P_RequestPictureDrop_isr: Task is not started yet. "));
        goto end;
    }

    /* Create Pause command */
    sCommand.sCommandHeader.ui32CommandID = BDSP_RAAGA_NUM_PIC_TO_DROP_COMMAND_ID;
    /* TODO: Need to check the use of it!!! */
    sCommand.sCommandHeader.ui32CommandCounter =  pRaagaTask->commandCounter++;
    sCommand.sCommandHeader.ui32TaskID =  pRaagaTask->taskId;
    sCommand.sCommandHeader.eResponseType = BDSP_Raaga_P_ResponseType_eNone;
    sCommand.uCommand.sNumPicToDropCommand.ui32NumPicToDrop = *pPictureDropRequestCount;

    pRaagaTask->lastEventType = sCommand.sCommandHeader.ui32CommandID;

    err = BDSP_Raaga_P_SendCommand_isr(
        pDevice->hCmdQueue[pRaagaTask->settings.dspIndex],
        &sCommand,pRaagaTask);
    if (BERR_SUCCESS != err)
    {
        BDBG_ERR(("BDSP_Raaga_P_RequestPictureDrop_isr: Request picture drop Command failed!"));
        err = BERR_TRACE(err);
        goto end;
    }

    end:
    BDBG_LEAVE(BDSP_Raaga_P_RequestPictureDrop_isr);
    return err;
}

BERR_Code BDSP_Raaga_P_DisplayInterruptEvent_isr(
    void *pTaskHandle)
{
    BDSP_RaagaTask *pRaagaTask = (BDSP_RaagaTask *)pTaskHandle;
    BERR_Code err=BERR_SUCCESS;
    bool bRealUpdate = true;
    unsigned int    uiBuffSize = 4;
    uint32_t puiPictureCount=0;
    uint32_t pGetUPB=0;
    raaga_dramaddr physaddr=0;

    BDBG_ENTER(BDSP_Raaga_P_DisplayInterruptEvent_isr);
    BDBG_OBJECT_ASSERT(pRaagaTask, BDSP_RaagaTask);

    if (pRaagaTask->isStopped == true)
    {
        BDBG_MSG(("BDSP_Raaga_P_DisplayInterruptEvent_isr : Task is not started yet. "));
        goto end;
    }

    err = BDSP_Raaga_P_GetPictureQueueCount_isr(pTaskHandle,&puiPictureCount,pRaagaTask->hDSQueue);

    if (puiPictureCount != 0)
    {
        err = BDSP_Raaga_P_GetVideoMsg_isr(pRaagaTask->hDSQueue,&pGetUPB,bRealUpdate);

        physaddr=pGetUPB;

        BDBG_MSG(("pGetUPB = 0x%x physaddr = 0x%x\n",pGetUPB,physaddr));

        err  = BDSP_Raaga_P_WriteVideoMsg_isr(pRaagaTask->hPRQueue, &physaddr,uiBuffSize);
    }

    end:
    BDBG_LEAVE(BDSP_Raaga_P_DisplayInterruptEvent_isr);
    return err;
}

BERR_Code BDSP_Raaga_P_InputPictureBufferCount_isr(
    void *pTaskHandle,
    uint32_t *pPictureBuffAvail)
{
        BDSP_RaagaTask *pRaagaTask = (BDSP_RaagaTask *)pTaskHandle;
        BERR_Code err = BERR_SUCCESS;
        raaga_dramaddr  ui32dramReadAddr=0;
        raaga_dramaddr  ui32dramWriteAddr=0;
        raaga_dramaddr  ui32maskReadAddr=0;
        raaga_dramaddr  ui32maskWriteAddr=0;
        int32_t i32BytesToBeRead=0;

        BDBG_OBJECT_ASSERT(pRaagaTask, BDSP_RaagaTask);

        if ((pRaagaTask->isStopped == true)||(pRaagaTask->pContext->contextWatchdogFlag == true))
        {
            BDBG_ERR(("BDSP_Raaga_P_InputPictureBufferCount_isr : Task is not started yet. "));
            goto end;
        }


        ui32dramReadAddr=BDSP_Read32_isr(pRaagaTask->hRDQueue->hRegister,BCHP_RAAGA_DSP_FW_CFG_FIFO_0_BASE_ADDR + 4 * 4 * pRaagaTask->hRDQueue->i32FifoId +
            BDSP_RAAGA_P_FIFO_READ_OFFSET + pRaagaTask->hRDQueue->ui32DspOffset);

        ui32dramWriteAddr=BDSP_Read32_isr(pRaagaTask->hRDQueue->hRegister,BCHP_RAAGA_DSP_FW_CFG_FIFO_0_BASE_ADDR + 4 * 4 * pRaagaTask->hRDQueue->i32FifoId +
            BDSP_RAAGA_P_FIFO_WRITE_OFFSET + pRaagaTask->hRDQueue->ui32DspOffset);

        BDBG_MSG(("ui32dramReadAddr > %x", ui32dramReadAddr));
        BDBG_MSG(("ui32dramWriteAddr > %x", ui32dramWriteAddr));
        ui32maskReadAddr=ui32dramReadAddr;
        ui32maskWriteAddr=ui32dramWriteAddr;

        /*Sanity check*/
        /* checking write ptr boundness- if((writeptr>endaddr)|(writeptr<baseaddr)) write ptr is not within bound*/
        if ((ui32maskWriteAddr>pRaagaTask->hRDQueue->ui32EndAddr)||(ui32maskWriteAddr<pRaagaTask->hRDQueue->ui32BaseAddr))
        {
            BDBG_ERR(("Write pointer not within bounds in Message Queue"));
            BDBG_ASSERT(0);
            err = BERR_TRACE(BDSP_ERR_BAD_DEVICE_STATE);
            goto end;
        }


        /* checking read ptr boundness- if((readptr>endaddr)|(readptr<baseaddr)) read ptr is not within bound*/
        if ((ui32maskReadAddr>pRaagaTask->hRDQueue->ui32EndAddr)||(ui32maskReadAddr<pRaagaTask->hRDQueue->ui32BaseAddr))
        {
            BDBG_ERR(("Read pointer not within bounds in Message Queue"));
            BDBG_ASSERT(0);
            err = BERR_TRACE(BDSP_ERR_BAD_DEVICE_STATE);
            goto end;
        }

        /*Updating write ptr */
        pRaagaTask->hRDQueue->ui32WriteAddr= ui32maskWriteAddr;

        /* End of Sanity Check */

        /*******************************************************************
        Different cases:

        If maskreadptr>maskwriteptr
        ReadPtrMSB   WritePtrMSB
           0                   0                   This condn. is not possible
           0                   1                   (end-read)+(write-base)
           1                   0                     (end-read)+(write-base)
           1                   1                      this condn. is not possible

        If maskwriteptr>maskreadptr
        ReadptrMSB   WritePtrMSB
        0                   0               write-read
        0                   1                  this condn. not possible
        1                   0                  this condn. not possible
        1                   1                  write-read

        If maskreadptr==maskwriteptr
        If the toggle bits are the same,no message to read
        If the toggle bits are different all the messages have to be read


        ***********************************************************************/
        /*Condn. for reading messages from the message queue into the message buffer*/
        /* If no msg is to be read, generate a BRAP_ERR_BUFFER_EMPTY error(new error defined in brap.h)*/

        /* Checking if a msg is present */

        /* Case1:if(readptr>writeptr)*/
        if (ui32maskReadAddr > ui32maskWriteAddr)
        {
            i32BytesToBeRead=(pRaagaTask->hRDQueue->ui32EndAddr-ui32maskReadAddr)+
                (ui32maskWriteAddr-pRaagaTask->hRDQueue->ui32BaseAddr);
        }

        /* Case2:if(writeptr>readptr) */
        if (ui32maskWriteAddr>ui32maskReadAddr)
        {
            i32BytesToBeRead=ui32maskWriteAddr-ui32maskReadAddr;
        }

        /*Case 3:if readptr == writeptr */
        if (ui32maskWriteAddr ==ui32maskReadAddr)
        {
            /* The queue is empty */
            i32BytesToBeRead = 0;
        }

    *pPictureBuffAvail = (i32BytesToBeRead>>2);
    end:
    return err;
}

BERR_Code BDSP_Raaga_P_GetPictureBuffer_isr(
    void *pTaskHandle,
    raaga_dramaddr  *pPictureParmBuf)
{
    BDSP_RaagaTask *pRaagaTask = (BDSP_RaagaTask *)pTaskHandle;
    BERR_Code err=BERR_SUCCESS;
    bool bReadUpdate = true;
    raaga_dramaddr  uiPPBPhysicalAddr=0;
    raaga_dramaddr  ui32dramReadAddr=0;
    raaga_dramaddr  ui32dramWriteAddr=0;
    raaga_dramaddr  ui32ReadAddr=0;
    raaga_dramaddr  ui32WriteAddr=0;
    int32_t i32BytesToBeRead=0;
    void *pvMsgQueueReadAddr=NULL;

    BDBG_OBJECT_ASSERT(pRaagaTask, BDSP_RaagaTask);

    if ((pRaagaTask->isStopped == true)||(pRaagaTask->pContext->contextWatchdogFlag == true))
    {
        BDBG_ERR(("BDSP_Raaga_P_GetPictureBuffer_isr : Task is not started yet. "));
        goto end;
    }


    ui32dramReadAddr=BDSP_Read32_isr(pRaagaTask->hRRQueue->hRegister,BCHP_RAAGA_DSP_FW_CFG_FIFO_0_BASE_ADDR + 4 * 4 * pRaagaTask->hRRQueue->i32FifoId +
        BDSP_RAAGA_P_FIFO_READ_OFFSET + pRaagaTask->hRRQueue->ui32DspOffset);

    ui32dramWriteAddr=BDSP_Read32_isr(pRaagaTask->hRRQueue->hRegister,BCHP_RAAGA_DSP_FW_CFG_FIFO_0_BASE_ADDR + 4 * 4 * pRaagaTask->hRRQueue->i32FifoId +
        BDSP_RAAGA_P_FIFO_WRITE_OFFSET + pRaagaTask->hRRQueue->ui32DspOffset);

    BDBG_MSG(("ui32ReadAddr > %x", ui32ReadAddr));
    BDBG_MSG(("ui32WriteAddr > %x", ui32WriteAddr));

    ui32ReadAddr=ui32dramReadAddr;
    ui32WriteAddr=ui32dramWriteAddr;

    /*Sanity check*/
    /* checking write ptr boundness- if((writeptr>endaddr)|(writeptr<baseaddr)) write ptr is not within bound*/
    if ((ui32WriteAddr>pRaagaTask->hRRQueue->ui32EndAddr)||(ui32WriteAddr<pRaagaTask->hRRQueue->ui32BaseAddr))
    {
        BDBG_ERR(("Write pointer not within bounds in Message Queue"));
        BDBG_ASSERT(0);
        err = BERR_TRACE(BDSP_ERR_BAD_DEVICE_STATE);
        goto end;
    }


    /* checking read ptr boundness- if((readptr>endaddr)|(readptr<baseaddr)) read ptr is not within bound*/
    if ((ui32ReadAddr>pRaagaTask->hRRQueue->ui32EndAddr)||(ui32ReadAddr<pRaagaTask->hRRQueue->ui32BaseAddr))
    {
        BDBG_ERR(("Read pointer not within bounds in Message Queue"));
        BDBG_ASSERT(0);
        err = BERR_TRACE(BDSP_ERR_BAD_DEVICE_STATE);
        goto end;
    }

    /*Updating write ptr */
    pRaagaTask->hRRQueue->ui32WriteAddr= ui32WriteAddr;

    /* checking read ptrs to see if they are the same */
    if ((pRaagaTask->hRRQueue->ui32ReadAddr)!=ui32ReadAddr)
    {
        BDBG_ERR(("Read pointer corrupted in the Message Queue"));
        BDBG_ASSERT(0);
        err = BERR_TRACE(BDSP_ERR_BAD_DEVICE_STATE );
        goto end;
    }

    /* End of Sanity Check */

    /*******************************************************************
    Different cases:

    If maskreadptr>maskwriteptr
    ReadPtrMSB   WritePtrMSB
       0                   0                   This condn. is not possible
       0                   1                   (end-read)+(write-base)
       1                   0                     (end-read)+(write-base)
       1                   1                      this condn. is not possible

    If maskwriteptr>maskreadptr
    ReadptrMSB   WritePtrMSB
    0                   0               write-read
    0                   1                  this condn. not possible
    1                   0                  this condn. not possible
    1                   1                  write-read

    If maskreadptr==maskwriteptr
    If the toggle bits are the same,no message to read
    If the toggle bits are different all the messages have to be read


    ***********************************************************************/
    /*Condn. for reading messages from the message queue into the message buffer*/
    /* If no msg is to be read, generate a BRAP_ERR_BUFFER_EMPTY error(new error defined in brap.h)*/

    /* Checking if a msg is present */

    /* Case1:if(readptr>writeptr)*/
    if (ui32ReadAddr > ui32WriteAddr)
    {
        i32BytesToBeRead=(pRaagaTask->hRRQueue->ui32EndAddr-ui32ReadAddr)+
            (ui32WriteAddr-pRaagaTask->hRRQueue->ui32BaseAddr);
    }

    /* Case2:if(writeptr>readptr) */
    if (ui32WriteAddr>ui32ReadAddr)
    {
        i32BytesToBeRead=ui32WriteAddr-ui32ReadAddr;
    }

    /*Case 3:if readptr == writeptr. Queue is empty in this case. */
    if (ui32WriteAddr ==ui32ReadAddr)
    {
        i32BytesToBeRead=0;
    }
    if (i32BytesToBeRead <= 0)
    {
        *pPictureParmBuf = 0;
        /*
            BDBG_ERR(("The PRQ Queue is empty. No buffers available."));
            BDBG_ASSERT(0);
            err = BERR_TRACE(BDSP_ERR_BUFFER_EMPTY);
           */
        goto end;
    }


    /* This conversion is done to pass a virtual address to BDSP_Raaga_P_MemRead32_isr */
    pvMsgQueueReadAddr = (void *)((uint8_t *)pRaagaTask->hRRQueue->pBaseAddr + (ui32ReadAddr - pRaagaTask->hRRQueue->ui32BaseAddr ));

    /*Reading Message from the message queue into the message buffer*/
    uiPPBPhysicalAddr=BDSP_P_MemRead32_isr(pRaagaTask->hRRQueue->hHeap,pvMsgQueueReadAddr);

    /* pvMsgQueueReadAddr = BMMA_UnlockOffset_isr(uiPPBPhysicalAddr,0); */

    *pPictureParmBuf =  uiPPBPhysicalAddr;

    if (bReadUpdate == true)
    {
        ui32ReadAddr=ui32ReadAddr+4;
        if (ui32ReadAddr==pRaagaTask->hRRQueue->ui32EndAddr)
            ui32ReadAddr=pRaagaTask->hRRQueue->ui32BaseAddr;

        /*updating read ptr in the Queue Attribute Structure*/
        BDSP_Write32_isr(pRaagaTask->hRRQueue->hRegister,BCHP_RAAGA_DSP_FW_CFG_FIFO_0_BASE_ADDR + 4 * 4 * pRaagaTask->hRRQueue->i32FifoId +
            BDSP_RAAGA_P_FIFO_READ_OFFSET + pRaagaTask->hRRQueue->ui32DspOffset, ui32ReadAddr);
        BDBG_MSG(("ui32dramReadAddr > %x", ui32dramReadAddr));
        BDBG_MSG(("ui32dramWriteAddr > %x", ui32dramWriteAddr));

        /*updating read ptr in the handle*/
        pRaagaTask->hRRQueue->ui32ReadAddr = ui32ReadAddr;
    }

    end:
    return err;
}

/* This one is not needed as BVN will scale and write the picture in DRAM buffer and directly interrupt DSP which in turn will update RDQ */
BERR_Code BDSP_Raaga_P_PutPicture_isr(
    void        *pTaskHandle,
    raaga_dramaddr  pPPBAddr
    )
{
    BDSP_RaagaTask *pRaagaTask = (BDSP_RaagaTask *)pTaskHandle;
    BERR_Code err=BERR_SUCCESS;
    bool bWriteUpdate = true;
    raaga_dramaddr  ui32dramReadAddr=0;
    raaga_dramaddr  ui32dramWriteAddr=0;
    raaga_dramaddr  ui32maskReadAddr=0;
    raaga_dramaddr  ui32maskWriteAddr=0;
    int32_t i32BytesToBeRead=0;

    BDBG_OBJECT_ASSERT(pRaagaTask, BDSP_RaagaTask);

    if ((pRaagaTask->isStopped == true)||(pRaagaTask->pContext->contextWatchdogFlag == true))
    {
        BDBG_ERR(("BDSP_Raaga_P_PutPicture_isr : Task is not started yet. "));
        goto end;
    }


    ui32dramReadAddr=BDSP_Read32_isr(pRaagaTask->hRDQueue->hRegister,BCHP_RAAGA_DSP_FW_CFG_FIFO_0_BASE_ADDR + 4 * 4 * pRaagaTask->hRDQueue->i32FifoId +
        BDSP_RAAGA_P_FIFO_READ_OFFSET + pRaagaTask->hRDQueue->ui32DspOffset);

    ui32dramWriteAddr=BDSP_Read32_isr(pRaagaTask->hRDQueue->hRegister,BCHP_RAAGA_DSP_FW_CFG_FIFO_0_BASE_ADDR + 4 * 4 * pRaagaTask->hRDQueue->i32FifoId +
        BDSP_RAAGA_P_FIFO_WRITE_OFFSET + pRaagaTask->hRDQueue->ui32DspOffset);

    BDBG_MSG(("ui32dramReadAddr > %x", ui32dramReadAddr));
    BDBG_MSG(("ui32dramWriteAddr > %x", ui32dramWriteAddr));
    ui32maskReadAddr=ui32dramReadAddr;
    ui32maskWriteAddr=ui32dramWriteAddr;

    /*Sanity check*/
    /* checking write ptr boundness- if((writeptr>endaddr)|(writeptr<baseaddr)) write ptr is not within bound*/
    if ((ui32maskWriteAddr>pRaagaTask->hRDQueue->ui32EndAddr)||(ui32maskWriteAddr<pRaagaTask->hRDQueue->ui32BaseAddr))
    {
        BDBG_ERR(("Write pointer not within bounds in Message Queue"));
        BDBG_ASSERT(0);
        err = BERR_TRACE(BDSP_ERR_BAD_DEVICE_STATE);
        goto end;
    }


    /* checking read ptr boundness- if((readptr>endaddr)|(readptr<baseaddr)) read ptr is not within bound*/
    if ((ui32maskReadAddr>pRaagaTask->hRDQueue->ui32EndAddr)||(ui32maskReadAddr<pRaagaTask->hRDQueue->ui32BaseAddr))
    {
        BDBG_ERR(("Read pointer not within bounds in Message Queue"));
        BDBG_ASSERT(0);
        err = BERR_TRACE(BDSP_ERR_BAD_DEVICE_STATE);
        goto end;
    }

    /*Updating write ptr */
    pRaagaTask->hRDQueue->ui32WriteAddr= ui32maskWriteAddr;

    /* End of Sanity Check */

    /*******************************************************************
    Different cases:

    If maskreadptr>maskwriteptr
    ReadPtrMSB   WritePtrMSB
       0                   0                   This condn. is not possible
       0                   1                   (end-read)+(write-base)
       1                   0                     (end-read)+(write-base)
       1                   1                      this condn. is not possible

    If maskwriteptr>maskreadptr
    ReadptrMSB   WritePtrMSB
    0                   0               write-read
    0                   1                  this condn. not possible
    1                   0                  this condn. not possible
    1                   1                  write-read

    If maskreadptr==maskwriteptr
    If the toggle bits are the same,no message to read
    If the toggle bits are different all the messages have to be read


    ***********************************************************************/
    /*Condn. for reading messages from the message queue into the message buffer*/
    /* If no msg is to be read, generate a BRAP_ERR_BUFFER_EMPTY error(new error defined in brap.h)*/

    /* Checking if a msg is present */

    /* Case1:if(readptr>writeptr)*/
    if (ui32maskReadAddr > ui32maskWriteAddr)
    {
        i32BytesToBeRead=(pRaagaTask->hRDQueue->ui32EndAddr-ui32maskReadAddr)+
            (ui32maskWriteAddr-pRaagaTask->hRDQueue->ui32BaseAddr);
    }

    /* Case2:if(writeptr>readptr) */
    if (ui32maskWriteAddr>ui32maskReadAddr)
    {
        i32BytesToBeRead=ui32maskWriteAddr-ui32maskReadAddr;
    }

    /*Case 3:if readptr == writeptr */
    if (ui32maskWriteAddr ==ui32maskReadAddr)
    {
        /* The queue is empty */
        i32BytesToBeRead = 0;
    }
    /*
    if (i32BytesToBeRead == 4)
    {
        BDBG_ERR(("The PDQ Queue is empty. No buffers available."));
        BDBG_ASSERT(0);
        err = BERR_TRACE(BDSP_ERR_BUFFER_EMPTY);
        goto end;
    }
    */
    if (i32BytesToBeRead == (int32_t)((pRaagaTask->hRDQueue->ui32EndAddr - pRaagaTask->hRDQueue->ui32BaseAddr)-4) )
    {
        BDBG_ERR(("RDQ is full and RRQ available. Encoder slow???"));
        goto end;
    }

    /* Put the buffer in PDQ */

    /* Now ui32dramWriteAddr is NOT a dram pointer but an RDB address */
        BDSP_Write32_isr(pRaagaTask->hRDQueue->hRegister, BDSP_ADDR_FOR_HOSTCPU_FROM_RAAGA_REGSET(ui32dramWriteAddr) + pRaagaTask->pContext->pDevice->dspOffset[pRaagaTask->settings.dspIndex], pPPBAddr);

    /* Update the write pointer of PDQ */
    if (bWriteUpdate == true)
    {
        ui32dramWriteAddr = ui32dramWriteAddr + 4;
        if (ui32dramWriteAddr==pRaagaTask->hRDQueue->ui32EndAddr)
            ui32dramWriteAddr=pRaagaTask->hRDQueue->ui32BaseAddr;

        /*updating write ptr in the Queue Attribute Structure*/
        BDSP_Write32_isr(pRaagaTask->hRDQueue->hRegister,BCHP_RAAGA_DSP_FW_CFG_FIFO_0_BASE_ADDR + 4 * 4 * pRaagaTask->hRDQueue->i32FifoId +
            BDSP_RAAGA_P_FIFO_WRITE_OFFSET + pRaagaTask->hRDQueue->ui32DspOffset, ui32dramWriteAddr);
        BDBG_MSG(("ui32dramReadAddr > %x", ui32dramReadAddr));
        BDBG_MSG(("ui32dramWriteAddr > %x", ui32dramWriteAddr));

        /*updating read ptr in the handle*/
        pRaagaTask->hRDQueue->ui32ReadAddr = ui32dramReadAddr;
    }

    end:
    return err;
}


/* This function is used to copy the CC data struct into the DRAM queue */
BERR_Code BDSP_Raaga_P_Put_CC_Data_isr(
    void    *pTask,
    void    *pCCDAddress
    )
{
    BDSP_RaagaTask *pRaagaTask = (BDSP_RaagaTask *)(pTask);
    BERR_Code err=BERR_SUCCESS;
    raaga_dramaddr  ui32dramReadAddr=0;
    raaga_dramaddr  ui32dramWriteAddr=0;
    uint32_t ui32dramBasePtr=0;
    uint32_t ui32dramEndPtr=0;
    raaga_dramaddr  ui32maskReadAddr=0;
    raaga_dramaddr  ui32maskWriteAddr=0;
    int32_t i32BytesToWrite=0;
    void *pCcdAddr_Cached = 0;



    BDBG_OBJECT_ASSERT(pRaagaTask, BDSP_RaagaTask);

    if((pRaagaTask->isStopped == true)||(pRaagaTask->pContext->contextWatchdogFlag == true))
    {
        BDBG_ERR(("BDSP_Raaga_P_Put_CC_Data_isr : Task is not started yet. "));
        goto end;
    }


    ui32dramReadAddr=BDSP_Read32_isr(pRaagaTask->hCCDQueue->hRegister,BCHP_RAAGA_DSP_FW_CFG_FIFO_0_BASE_ADDR + 4 * 4 * pRaagaTask->hCCDQueue->i32FifoId +
        BDSP_RAAGA_P_FIFO_READ_OFFSET + pRaagaTask->hCCDQueue->ui32DspOffset);

    ui32dramWriteAddr=BDSP_Read32_isr(pRaagaTask->hCCDQueue->hRegister,BCHP_RAAGA_DSP_FW_CFG_FIFO_0_BASE_ADDR + 4 * 4 * pRaagaTask->hCCDQueue->i32FifoId +
        BDSP_RAAGA_P_FIFO_WRITE_OFFSET + pRaagaTask->hCCDQueue->ui32DspOffset);

    ui32dramBasePtr = BDSP_Read32_isr(pRaagaTask->hCCDQueue->hRegister,BCHP_RAAGA_DSP_FW_CFG_FIFO_0_BASE_ADDR + 4 * 4 * pRaagaTask->hCCDQueue->i32FifoId +
        BDSP_RAAGA_P_FIFO_BASE_OFFSET + pRaagaTask->hCCDQueue->ui32DspOffset);

    ui32dramEndPtr = BDSP_Read32_isr(pRaagaTask->hCCDQueue->hRegister,BCHP_RAAGA_DSP_FW_CFG_FIFO_0_BASE_ADDR + 4 * 4 * pRaagaTask->hCCDQueue->i32FifoId +
        BDSP_RAAGA_P_FIFO_END_OFFSET + pRaagaTask->hCCDQueue->ui32DspOffset);

    BDBG_MSG(("ui32dramReadAddr > %x", ui32dramReadAddr));
    BDBG_MSG(("ui32dramWriteAddr > %x", ui32dramWriteAddr));
    BDBG_MSG(("ui32dramBasePtr > %x", ui32dramBasePtr));
    BDBG_MSG(("ui32dramEndPtr > %x", ui32dramEndPtr));
    ui32maskReadAddr=ui32dramReadAddr;
    ui32maskWriteAddr=ui32dramWriteAddr;

    /*Sanity check*/
    /* checking write ptr boundness- if((writeptr>endaddr)|(writeptr<baseaddr)) write ptr is not within bound*/
    if ((ui32maskWriteAddr>pRaagaTask->hCCDQueue->ui32EndAddr)||(ui32maskWriteAddr<pRaagaTask->hCCDQueue->ui32BaseAddr))
    {
        BDBG_ERR(("Write pointer not within bounds in Message Queue"));
        BDBG_ASSERT(0);
        err = BERR_TRACE(BDSP_ERR_BAD_DEVICE_STATE);
        goto end;
    }


    /* checking read ptr boundness- if((readptr>endaddr)|(readptr<baseaddr)) read ptr is not within bound*/
    if ((ui32maskReadAddr>pRaagaTask->hCCDQueue->ui32EndAddr)||(ui32maskReadAddr<pRaagaTask->hCCDQueue->ui32BaseAddr))
    {
        BDBG_ERR(("Read pointer not within bounds in Message Queue"));
        BDBG_ASSERT(0);
        err = BERR_TRACE(BDSP_ERR_BAD_DEVICE_STATE);
        goto end;
    }

    /*Updating write ptr */
    pRaagaTask->hCCDQueue->ui32WriteAddr= ui32maskWriteAddr;

    /* End of Sanity Check */

    /*******************************************************************
    Different cases:

    If maskreadptr>maskwriteptr
    ReadPtrMSB   WritePtrMSB
       0                   0                   This condn. is not possible
       0                   1                   (end-read)+(write-base)
       1                   0                     (end-read)+(write-base)
       1                   1                      this condn. is not possible

    If maskwriteptr>maskreadptr
    ReadptrMSB   WritePtrMSB
    0                   0               write-read
    0                   1                  this condn. not possible
    1                   0                  this condn. not possible
    1                   1                  write-read

    If maskreadptr==maskwriteptr
    If the toggle bits are the same,no message to read
    If the toggle bits are different all the messages have to be read


    ***********************************************************************/
    /*Condn. for reading messages from the message queue into the message buffer*/
    /* If no msg is to be read, generate a BRAP_ERR_BUFFER_EMPTY error(new error defined in brap.h)*/

    /* Checking if a msg is present */

    /* Case1:if(readptr>writeptr)*/
    if (ui32maskReadAddr > ui32maskWriteAddr)
    {
        i32BytesToWrite=(ui32dramReadAddr - ui32dramWriteAddr);

    }

    /* Case2:if(writeptr>readptr) */
    if (ui32maskWriteAddr>ui32maskReadAddr)
    {
        i32BytesToWrite=((ui32dramEndPtr - ui32dramWriteAddr)+(ui32dramReadAddr - ui32dramBasePtr));
    }

    /*Case 3:if readptr == writeptr */
    if (ui32maskWriteAddr ==ui32maskReadAddr)
    {
        /* The queue is empty */
        i32BytesToWrite = ui32dramEndPtr - ui32dramBasePtr;
    }

    if (i32BytesToWrite <= (int32_t)(SIZEOF(BDSP_Raaga_Video_DCCparse_ccdata)) )
    {
        BDBG_ERR(("CC data queue is full. Encoder slow???"));
        goto end;
    }

    /* Put the CC data in the CCDQueue */
    if((ui32dramWriteAddr+SIZEOF(BDSP_Raaga_Video_DCCparse_ccdata)) >= ui32dramEndPtr)
    {
        i32BytesToWrite = ui32dramEndPtr - ui32dramWriteAddr;

        pCcdAddr_Cached = (void *)((uint8_t *)pRaagaTask->hCCDQueue->pBaseAddr + (ui32dramWriteAddr - pRaagaTask->hCCDQueue->ui32BaseAddr ));
        BKNI_Memcpy(pCcdAddr_Cached, pCCDAddress, i32BytesToWrite);
        BDSP_MEM_P_FlushCache_isr(pRaagaTask->hCCDQueue->hHeap, pCcdAddr_Cached, i32BytesToWrite);

        pCcdAddr_Cached = pRaagaTask->hCCDQueue->pBaseAddr ;
        BKNI_Memcpy(pCcdAddr_Cached, (void *)((uint8_t *)pCCDAddress+i32BytesToWrite), SIZEOF(BDSP_Raaga_Video_DCCparse_ccdata)-i32BytesToWrite);
        BDSP_MEM_P_FlushCache_isr(pRaagaTask->hCCDQueue->hHeap, pCcdAddr_Cached, SIZEOF(BDSP_Raaga_Video_DCCparse_ccdata)-i32BytesToWrite);

        /* Update the write pointer of CCD queue*/
        ui32dramWriteAddr = ui32dramBasePtr+SIZEOF(BDSP_Raaga_Video_DCCparse_ccdata)-i32BytesToWrite;

        /*updating write ptr in the Queue Attribute Structure*/
        BDSP_Write32_isr(pRaagaTask->hCCDQueue->hRegister,BCHP_RAAGA_DSP_FW_CFG_FIFO_0_BASE_ADDR + 4 * 4 * pRaagaTask->hCCDQueue->i32FifoId +
            BDSP_RAAGA_P_FIFO_WRITE_OFFSET + pRaagaTask->hCCDQueue->ui32DspOffset, ui32dramWriteAddr);
        BDBG_MSG(("ui32dramReadAddr > %x", ui32dramReadAddr));
        BDBG_MSG(("ui32dramWriteAddr > %x", ui32dramWriteAddr));

        /*updating read ptr in the handle*/
        pRaagaTask->hCCDQueue->ui32ReadAddr = ui32dramReadAddr;

    }
    else
    {
        pCcdAddr_Cached = (void *)((uint8_t *)pRaagaTask->hCCDQueue->pBaseAddr + (ui32dramWriteAddr - pRaagaTask->hCCDQueue->ui32BaseAddr ));

        BKNI_Memcpy(pCcdAddr_Cached, pCCDAddress, SIZEOF(BDSP_Raaga_Video_DCCparse_ccdata));
        BDSP_MEM_P_FlushCache_isr(pRaagaTask->hCCDQueue->hHeap, pCcdAddr_Cached, SIZEOF(BDSP_Raaga_Video_DCCparse_ccdata));

        /* Update the write pointer of CCD queue*/
        ui32dramWriteAddr = ui32dramWriteAddr+SIZEOF(BDSP_Raaga_Video_DCCparse_ccdata);
        if (ui32dramWriteAddr==pRaagaTask->hCCDQueue->ui32EndAddr)
            ui32dramWriteAddr=pRaagaTask->hCCDQueue->ui32BaseAddr;

        /*updating write ptr in the Queue Attribute Structure*/

        BDSP_Write32_isr(pRaagaTask->hCCDQueue->hRegister,BCHP_RAAGA_DSP_FW_CFG_FIFO_0_BASE_ADDR + 4 * 4 * pRaagaTask->hCCDQueue->i32FifoId +
            BDSP_RAAGA_P_FIFO_WRITE_OFFSET + pRaagaTask->hCCDQueue->ui32DspOffset, ui32dramWriteAddr);
        BDBG_MSG(("ui32dramReadAddr > %x", ui32dramReadAddr));
        BDBG_MSG(("ui32dramWriteAddr > %x", ui32dramWriteAddr));

        /*updating read ptr in the handle*/
        pRaagaTask->hCCDQueue->ui32ReadAddr = ui32dramReadAddr;


    }

    end:
    return err;
}

/***********************************************************************
Name        :   BDSP_Raaga_P_PowerStandby

Type        :   PI Interface

Input       :   pDeviceHandle -Device Handle which needs to be closed.
                pSettings - pointer where the Default Data will be filled and returned to PI.

Return      :   Error Code to return SUCCESS or FAILURE

Functionality   :   To check if all the task for the DSP is closed.
                Then disable the Watchdog timer, Reset the Hardware and relanquish the resources.
***********************************************************************/

BERR_Code BDSP_Raaga_P_PowerStandby(
    void *pDeviceHandle,
    BDSP_StandbySettings    *pSettings)
{
    BDSP_Raaga *pDevice = (BDSP_Raaga *)pDeviceHandle;
    BERR_Code err=BERR_SUCCESS;

    BDBG_OBJECT_ASSERT(pDevice, BDSP_Raaga);
    BDBG_ENTER(BDSP_Raaga_P_PowerStandby);

    if (pSettings)
        BSTD_UNUSED(pSettings);


    if (!pDevice->powerStandby)
    {
        BDSP_RaagaContext *pRaagaContext=NULL;
        BDSP_RaagaTask  *pRaagaTask=NULL;

        for ( pRaagaContext = BLST_S_FIRST(&pDevice->contextList);
            pRaagaContext != NULL;
            pRaagaContext = BLST_S_NEXT(pRaagaContext, node) )
        {
            for ( pRaagaTask = BLST_S_FIRST(&pRaagaContext->allocTaskList);
                pRaagaTask != NULL;
                pRaagaTask = BLST_S_NEXT(pRaagaTask, node) )
            {
                if (pRaagaTask->isStopped == false)
                {
                    BDBG_ERR(("Task %p is not stopped. Can not go in standby",(void *)pRaagaTask));
                    err = BERR_INVALID_PARAMETER;
                    goto end;
                }
            }
        }
        /*Disable watchdog*/
        BDSP_Raaga_P_EnableWatchdogTimer(pDeviceHandle,false);

        BDSP_Raaga_P_Reset(pDeviceHandle);

        pDevice->powerStandby = true;

        BDSP_Raaga_P_EnableAllPwrResource(pDeviceHandle, false);
    }
    else
    {
        BDBG_WRN(("Already in standby mode"));
        err = BERR_INVALID_PARAMETER;
        goto end;
    }

    end:

    BDBG_LEAVE(("BDSP_Raaga_P_PowerStandby"));

    return err;
}

/***********************************************************************
Name        :   BDSP_Raaga_P_PowerResume

Type        :   PI Interface

Input       :   pDeviceHandle -Device Handle which needs to be closed.

Return      :   Error Code to return SUCCESS or FAILURE

Functionality   :   Acquire the resources for the DSP. Reboot and initialize DSP, then Enable the Watchdog timer.
***********************************************************************/

BERR_Code BDSP_Raaga_P_PowerResume(
    void *pDeviceHandle)
{
    BDSP_Raaga *pDevice = (BDSP_Raaga *)pDeviceHandle;
    BERR_Code err=BERR_SUCCESS;

    BDBG_ENTER(BDSP_Raaga_P_PowerResume);
    BDBG_OBJECT_ASSERT(pDevice, BDSP_Raaga);

    /* if we reach here, then no channels are active. we can power down */
    if (pDevice->powerStandby)
    {
        BDSP_Raaga_P_EnableAllPwrResource(pDeviceHandle, true);

        /*Reboot and initialize DSP and its configurations*/
        pDevice->deviceWatchdogFlag = true;
        BDSP_Raaga_P_Reset(pDevice);
        BDSP_Raaga_P_Open(pDevice);
        if(pDevice->settings.authenticationEnabled == false)
        {
            err = BDSP_Raaga_P_Boot(pDevice);

            if (err!=BERR_SUCCESS)
            {
                err= BERR_TRACE(err);
                goto end;
            }
        }
        pDevice->deviceWatchdogFlag = false;

        /*Enable Watchdog*/
        BDSP_Raaga_P_RestoreWatchdogTimer(pDeviceHandle);

        pDevice->powerStandby = false;
    }
    else
    {
        BDBG_WRN(("Not in standby mode"));
        err = BERR_INVALID_PARAMETER;
        goto end;
    }
    BDBG_LEAVE(BDSP_Raaga_P_PowerResume);
    end:

    return err;
}

/***********************************************************************
Name        :   BDSP_Raaga_P_AudioGapFill

Type        :   PI Interface

Input       :   pTaskHandle -   Handle of the Task which needs to be zero Gap fill.

Return      :   Error Code to return SUCCESS or FAILURE

Functionality   :   Following are the operations performed.
        This command puts FW in zero fill mode. This is needed to handle NRT Xcode case. In NRT xcode, decoder
        has to trigger STC to move it forward and if there is no data in the input CDB, it is supposed to do nothing
        so if there is an audio gap, audio stalls and does not trigger STC which in turn stall video also by virtue of
        AV_WINDOW. This command will be called by upper layer when it detects such kind of gap in stream and
        this will make sure aduio fills zeroes and STC moves forward avoiding the deadlock.
***********************************************************************/

BERR_Code BDSP_Raaga_P_AudioGapFill(void *pTaskHandle)
{
    BDSP_RaagaTask *pRaagaTask = (BDSP_RaagaTask *)pTaskHandle;
    BDSP_Raaga  *pDevice= pRaagaTask->pContext->pDevice;
    BERR_Code err=BERR_SUCCESS;
    BDSP_Raaga_P_Command sCommand;
    BDSP_Raaga_P_Response sRsp;

    BDBG_OBJECT_ASSERT(pRaagaTask, BDSP_RaagaTask);

    if (pRaagaTask->isStopped == true)
    {
        BDBG_WRN(("Task is not started yet. Ignoring the Audio Gap Fill command"));
        goto end;
    }
    else
    {
        if (pRaagaTask->paused == true)
        {
            BDBG_WRN(("Task is already in Pause state. Ignoring the Audio Gap Fill command"));
            goto end;
        }
        else
        {
            /* Create Pause command */
            BKNI_Memset((void *)&sRsp,0,sizeof(BDSP_Raaga_P_Response));
            BKNI_Memset((void *)&sCommand,0,sizeof(BDSP_Raaga_P_Command));

            sCommand.sCommandHeader.ui32CommandID = BDSP_RAAGA_AUDIO_GAP_FILL_COMMAND_ID;
            sCommand.sCommandHeader.ui32CommandCounter =  pRaagaTask->commandCounter++;
            sCommand.sCommandHeader.ui32TaskID =  pRaagaTask->taskId;
            sCommand.sCommandHeader.eResponseType = BDSP_Raaga_P_ResponseType_eNone;
            sCommand.sCommandHeader.ui32CommandSizeInBytes =  sizeof(BDSP_Raaga_P_Command);

            pRaagaTask->lastEventType = sCommand.sCommandHeader.ui32CommandID;
            BKNI_ResetEvent(pRaagaTask->hEvent);

            err = BDSP_Raaga_P_SendCommand(
                pDevice->hCmdQueue[pRaagaTask->settings.dspIndex],
                &sCommand,pRaagaTask);
            if (BERR_SUCCESS != err)
            {
                BDBG_ERR(("BDSP_Raaga_P_AudioGapFill: Audio Gap Fill Command failed!"));
                err = BERR_TRACE(err);
                goto end;
            }
            /* Wait for Ack_Response_Received event w/ timeout */
            /* As of now, we do not need any ACK or RESPONSE for this command */
        }
    }
    end:
    return err;
}

/***********************************************************************
Name        :   BDSP_Raaga_P_AllocateExternalInterrupt

Type        :   PI Interface

Input       :   pDeviceHandle -Device Handle for the Device.
                dspIndex - Index of the DSP
                pInterruptHandle - pointer which is returned after allocating the Intterupt

Return      :   Error Code to return SUCCESS or FAILURE

Functionality   :   Allocate the required memory for thre External interrupt. Provide the Interrupt
                bit for which the External Interrupt is hoooked, with error handling.
***********************************************************************/

BERR_Code BDSP_Raaga_P_AllocateExternalInterrupt(void *pDeviceHandle, uint32_t dspIndex, BDSP_ExternalInterruptHandle *pInterruptHandle)
{
    BDSP_Raaga *pDevice = (BDSP_Raaga *)pDeviceHandle;
    BERR_Code err=BERR_SUCCESS;
    BDSP_RaagaExternalInterrupt *pRaagaExtInterrupt;
    uint32_t    j;

    BDBG_ENTER(BDSP_Raaga_P_AllocateExternalInterrupt);

    BDBG_OBJECT_ASSERT(pDevice, BDSP_Raaga);
    /* Allocate the InterruptHandle first */
    pRaagaExtInterrupt = BKNI_Malloc(sizeof(BDSP_RaagaExternalInterrupt));
    if ( NULL == pRaagaExtInterrupt )
    {
        return BERR_TRACE(BERR_OUT_OF_SYSTEM_MEMORY);
    }
    BKNI_Memset((void *)pRaagaExtInterrupt, 0, sizeof(BDSP_RaagaExternalInterrupt));

    /* Success, add to device's interrupt list */
    BLST_S_INSERT_HEAD(&pDevice->interruptList, pRaagaExtInterrupt, node);
    *pInterruptHandle = &pRaagaExtInterrupt->extInterrupt;

    /* Find a free interrupt */
    BKNI_AcquireMutex(pDevice->dspInterruptMutex[dspIndex]);
    for (j=0; j<BDSP_RAAGA_MAX_INTERRUPTS_PER_DSP; j++)
    {
        if (false == pDevice->dspInterrupts[dspIndex][j])
            break;
    }

    if (j >= BDSP_RAAGA_MAX_INTERRUPTS_PER_DSP)
    {
        BKNI_ReleaseMutex(pDevice->dspInterruptMutex[dspIndex]);
        BDBG_ERR(("BDSP_Raaga_P_AllocateExternalInterrupt: Unable to find free interrupt to dsp!"));
        err = BERR_TRACE(BERR_NOT_SUPPORTED);
        goto err_interrupt_alloc_fail;
    }
    else
    {
        pDevice->dspInterrupts[dspIndex][j] = true;
    }
    BKNI_ReleaseMutex(pDevice->dspInterruptMutex[dspIndex]);

    /* Got the interrupt bit. Populate interrupt handle now */
    BDBG_MSG(("Found free interrupt bit number %d of ESR_SI for dsp %d", j, dspIndex));
    pRaagaExtInterrupt->InterruptInfo.bitNum = j;
    pRaagaExtInterrupt->InterruptInfo.address = BCHP_RAAGA_DSP_ESR_SI_INT_SET + pDevice->dspOffset[dspIndex];
    pRaagaExtInterrupt->dspIndex = dspIndex;
    pRaagaExtInterrupt->extInterrupt.hDsp = &pDevice->device;
    pRaagaExtInterrupt->extInterrupt.pExtInterruptHandle = (void *)pRaagaExtInterrupt;
    pRaagaExtInterrupt->pDevice = pDevice;

    /* Done, mark objects as valid */
    BDBG_OBJECT_SET(pRaagaExtInterrupt, BDSP_RaagaExternalInterrupt);
    BDBG_OBJECT_SET(&pRaagaExtInterrupt->extInterrupt, BDSP_ExternalInterrupt);
    goto end;

err_interrupt_alloc_fail:
    *pInterruptHandle = NULL;
    BLST_S_REMOVE(&pDevice->interruptList, pRaagaExtInterrupt, BDSP_RaagaExternalInterrupt, node);
    BKNI_Free(pRaagaExtInterrupt);

end:
    BDBG_LEAVE(BDSP_Raaga_P_AllocateExternalInterrupt);
    return err;
}

/***********************************************************************
Name        :   BDSP_Raaga_P_FreeExternalInterrupt

Type        :   PI Interface

Input       :   pInterruptHandle - Pointer of the Intterupt which needs to be unhooked.

Return      :   Error Code to return SUCCESS or FAILURE

Functionality   :   Unhook the external interrupt and free the memory which was allocated.
***********************************************************************/

BERR_Code BDSP_Raaga_P_FreeExternalInterrupt(void *pInterruptHandle)
{
    BERR_Code err=BERR_SUCCESS;
    BDSP_RaagaExternalInterrupt *pExtInterrupt = (BDSP_RaagaExternalInterrupt *)pInterruptHandle;
    BDSP_Raaga *pRaaga = pExtInterrupt->pDevice;
    BDBG_ENTER(BDSP_Raaga_P_FreeExternalInterrupt);

    BDBG_OBJECT_ASSERT(pExtInterrupt, BDSP_RaagaExternalInterrupt);

    /* Free-up the interrupt bit */
    BDBG_MSG(("Freeing up interrupt bit number %d of ESR_SI for dsp %d", pExtInterrupt->InterruptInfo.bitNum, pExtInterrupt->dspIndex));
    pRaaga->dspInterrupts[pExtInterrupt->dspIndex][pExtInterrupt->InterruptInfo.bitNum] = false;

    /* Remove the handle from device's list */
    BLST_S_REMOVE(&pRaaga->interruptList, pExtInterrupt, BDSP_RaagaExternalInterrupt, node);
    BKNI_Free(pExtInterrupt);

    BDBG_LEAVE(BDSP_Raaga_P_FreeExternalInterrupt);

    return err;

}

/***********************************************************************
Name        :   BDSP_Raaga_P_GetExternalInterruptInfo

Type        :   PI Interface

Input       :   pInterruptHandle - Pointer of the Interrupt information is required by the PI.
                pInfo - Pointer to which data is filled and returned to PI.

Return      :   Error Code to return SUCCESS or FAILURE

Functionality   :   Return the information for the Interrupt provided by the PI.
***********************************************************************/

BERR_Code BDSP_Raaga_P_GetExternalInterruptInfo(void *pInterruptHandle, BDSP_ExternalInterruptInfo **pInfo)
{
    BERR_Code err=BERR_SUCCESS;
    BDSP_RaagaExternalInterrupt *pRaagaExtInterrupt = (BDSP_RaagaExternalInterrupt *)pInterruptHandle;
    BDBG_ENTER(BDSP_Raaga_P_GetExternalInterruptInfo);

    BDBG_OBJECT_ASSERT(pRaagaExtInterrupt, BDSP_RaagaExternalInterrupt);

    *pInfo = &pRaagaExtInterrupt->InterruptInfo;

    BDBG_LEAVE(BDSP_Raaga_P_GetExternalInterruptInfo);
    return err;
}

/***********************************************************************
Name        :   BDSP_Raaga_P_AllocateRdbRegisters

Type        :   PI Interface

Input       :   pDeviceHandle - Handle for the Device for which the RDB registers needs to be allocated.
                dspIndex - Index of the DSP.
                numRegs - Number of RDB Registers requested.
                pRdbRegisterHandle - Pointer/Handle for the RDB Registers returned back to PI.

Return      :   Error Code to return SUCCESS or FAILURE

Functionality   :   Allocate the RDB registers requested by PI. Return the RDB register handle after
                booking and error handling.
***********************************************************************/

BERR_Code BDSP_Raaga_P_AllocateRdbRegisters(
        void *pDeviceHandle,
        uint32_t dspIndex,
        uint32_t numRegs,
        BDSP_RdbRegisterHandle *pRdbRegisterHandle /* out */
        )
{
    BDSP_Raaga *pDevice = (BDSP_Raaga *)pDeviceHandle;
    BERR_Code err=BERR_SUCCESS;
    BDSP_RaagaRdbRegister *pRaagaRdbRegister;
    int32_t j, freeRegs = 0;

    BDBG_ENTER(BDSP_Raaga_P_AllocateRdbRegisters);

    BDBG_OBJECT_ASSERT(pDevice, BDSP_Raaga);
    /* Allocate the RDB register handle first */
    pRaagaRdbRegister = BKNI_Malloc(sizeof(BDSP_RaagaRdbRegister));
    if ( NULL == pRaagaRdbRegister )
    {
        return BERR_TRACE(BERR_OUT_OF_SYSTEM_MEMORY);
    }
    BKNI_Memset((void *)pRaagaRdbRegister, 0, sizeof(BDSP_RaagaRdbRegister));

    /* Success, add to device's rdb register list */
    BLST_S_INSERT_HEAD(&pDevice->rdbRegisterList, pRaagaRdbRegister, node);
    *pRdbRegisterHandle = &pRaagaRdbRegister->rdbRegister;

    /* Find a chunk of free Rdb Registers */
    BKNI_AcquireMutex(pDevice->rdbRegistersMutex[dspIndex]);
    for (j=0; j<BDSP_RAAGA_RDB_REGISTERS; j++)
    {
        /* Find a continuous spread of Rdb Registers */
        if (false == pDevice->rdbRegisters[dspIndex][j])
        {
            freeRegs++;
            if(freeRegs == (int32_t)numRegs)
                break;
        }
        else
        {
            freeRegs = 0;
        }
    }
    /* Find free register start index */
    freeRegs = j - numRegs + 1;
    if (j >= BDSP_RAAGA_RDB_REGISTERS)
    {
        BKNI_ReleaseMutex(pDevice->rdbRegistersMutex[dspIndex]);
        BDBG_ERR(("BDSP_Raaga_P_AllocateRdbRegisters: Unable to find free Rdb registers in dsp page!"));
        err = BERR_TRACE(BERR_NOT_SUPPORTED);
        goto err_rdb_alloc_fail;
    }
    else
    {
        for(;j >= freeRegs; j--)
        {
            pDevice->rdbRegisters[dspIndex][j] = true;
        }
    }
    BKNI_ReleaseMutex(pDevice->rdbRegistersMutex[dspIndex]);

    /* Got the interrupt bit. Populate interrupt handle now */
    BDBG_MSG(("BDSP_Raaga_P_AllocateRdbRegisters: Found free rdb register at index %x ", freeRegs));
    pRaagaRdbRegister->RdbRegisterInfo.addressOfBaseRdb = RAAGA_DSP_FW_CFG_PAGE_START + (freeRegs*4) + pDevice->dspOffset[dspIndex];
    pRaagaRdbRegister->dspIndex = dspIndex;
    pRaagaRdbRegister->numRegisters = numRegs;
    pRaagaRdbRegister->startIndex = freeRegs;
    pRaagaRdbRegister->rdbRegister.hDsp = &pDevice->device;
    pRaagaRdbRegister->rdbRegister.pRdbRegisterHandle = (void *)pRaagaRdbRegister;
    pRaagaRdbRegister->pDevice = pDevice;

    /* Done, mark objects as valid */
    BDBG_OBJECT_SET(pRaagaRdbRegister, BDSP_RaagaRdbRegister);
    BDBG_OBJECT_SET(&pRaagaRdbRegister->rdbRegister, BDSP_RdbRegister);
    goto end;

err_rdb_alloc_fail:
    *pRdbRegisterHandle = NULL;
    BLST_S_REMOVE(&pDevice->rdbRegisterList, pRaagaRdbRegister, BDSP_RaagaRdbRegister, node);
    BKNI_Free(pRaagaRdbRegister);

end:
    BDBG_LEAVE(BDSP_Raaga_P_AllocateRdbRegisters);
    return err;

}

/***********************************************************************
Name        :   BDSP_Raaga_P_FreeRdbRegisters

Type        :   PI Interface

Input       :   pRdbRegisterHandle - Pointer/Handle for the RDB Registers provided by PI to be deleted..

Return      :   Error Code to return SUCCESS or FAILURE

Functionality   :   Free the numbers of RDB registers provided in the Handle and free the memory allocated.
***********************************************************************/

BERR_Code BDSP_Raaga_P_FreeRdbRegisters(
    void  *pRdbRegisterHandle
    )
{
    BERR_Code err=BERR_SUCCESS;
    int32_t j;
    BDSP_RaagaRdbRegister *pRaagaRdbRegister = (BDSP_RaagaRdbRegister *)pRdbRegisterHandle;
    BDSP_Raaga *pRaaga = pRaagaRdbRegister->pDevice;
    BDBG_ENTER(BDSP_Raaga_P_FreeRdbRegisters);

    BDBG_OBJECT_ASSERT(pRaagaRdbRegister, BDSP_RaagaRdbRegister);

    /* Free-up the allocated RDB */
    BDBG_MSG(("Freeing up %d registers from index %d", pRaagaRdbRegister->numRegisters, pRaagaRdbRegister->startIndex));
    for(j = 0; j < (int32_t)pRaagaRdbRegister->numRegisters; j++)
    {
        pRaaga->rdbRegisters[pRaagaRdbRegister->dspIndex][pRaagaRdbRegister->startIndex+j] = false;
    }

    /* Remove the handle from device's list */
    BLST_S_REMOVE(&pRaaga->rdbRegisterList, pRaagaRdbRegister, BDSP_RaagaRdbRegister, node);
    BKNI_Free(pRaagaRdbRegister);

    BDBG_LEAVE(BDSP_Raaga_P_FreeRdbRegisters);

    return err;
}

/***********************************************************************
Name        :   BDSP_Raaga_P_GetRdbRegistersInfo

Type        :   PI Interface

Input       :   pRdbRegisterHandle - Handle of the RDB Register.
                pInfo - Pointer to which data is filled and returned to PI.

Return      :   Error Code to return SUCCESS or FAILURE

Functionality   :   Return the information for the RDB Register provided by the PI.
***********************************************************************/

BERR_Code BDSP_Raaga_P_GetRdbRegistersInfo(
    void *pRdbRegisterHandle,
    BDSP_RdbRegisterInfo **pInfo    /* out */
    )
{
    BERR_Code err=BERR_SUCCESS;
    BDSP_RaagaRdbRegister *pRaagaRdbRegister = (BDSP_RaagaRdbRegister *)pRdbRegisterHandle;
    BDBG_ENTER(BDSP_Raaga_P_GetRdbRegistersInfo);

    BDBG_OBJECT_ASSERT(pRaagaRdbRegister, BDSP_RaagaRdbRegister);

    *pInfo = &pRaagaRdbRegister->RdbRegisterInfo;

    BDBG_LEAVE(BDSP_Raaga_P_GetRdbRegistersInfo);
    return err;

}

/***********************************************************************
Name        :   BDSP_Raaga_P_SendScmCommand

Type        :   PI Interface

Input       :   pTaskHandle     -   Handle of the Task which needs to be Freezed.
                pScmCmdPayload  -   Data for the SCM command

Return      :   Error Code to return SUCCESS or FAILURE

Functionality   :   Following are the operations performed.
        1)  Check if the task is started.
        2)  Send the UnFreeze Command with SCM Payload details to the FW and wait for the acknowledgement.
***********************************************************************/

BERR_Code BDSP_Raaga_P_SendScmCommand(
                                        void *pTaskHandle,
                                        BDSP_Raaga_P_SCM_CmdPayload *pScmCmdPayload
                                        )
{
    BERR_Code ret = BERR_SUCCESS;


    BDSP_RaagaTask *pRaagaTask = (BDSP_RaagaTask *)pTaskHandle;
    BDSP_Raaga_P_Command sCommand;
    BDSP_Raaga_P_Response sRsp;
    BDSP_RaagaContext *pRaagaContext = pRaagaTask->pContext;
    BDSP_Raaga *pDevice = pRaagaContext->pDevice;
    BDSP_Raaga_P_MsgType eMsgType;

    BDBG_ENTER(BDSP_Raaga_P_SendScmCommand);
    BDBG_ASSERT(pTaskHandle);

    BKNI_Memset((void *)&sCommand,0,sizeof(BDSP_Raaga_P_Command));

    if (true == pRaagaTask->isStopped)
    {
        BDBG_ERR(("BDSP_Raaga_P_SendScmCommand: SCM Task = %p is not started", (void *)pRaagaTask));
        ret = BERR_TRACE(BERR_INVALID_PARAMETER);
        goto end;
    }
    else
    {
        BKNI_Memset((void *)&sRsp,0,sizeof(BDSP_Raaga_P_Response));
        /*  BKNI_Memset((void *)&sScmStatusBuf,0xFF,sizeof(BRAP_FWIF_P_ScmStageStatus));    */

        /* Create SCM FW command */
        sCommand.sCommandHeader.ui32CommandID = BDSP_RAAGA_BSP_SCM_COMMAND_ID;
        sCommand.sCommandHeader.ui32CommandCounter = pRaagaTask->commandCounter++;
        sCommand.sCommandHeader.ui32TaskID =  pRaagaTask->taskId;
        sCommand.sCommandHeader.eResponseType = BDSP_Raaga_P_ResponseType_eResponseRequired;
        sCommand.sCommandHeader.ui32CommandSizeInBytes =  sizeof(BDSP_Raaga_P_Command);
        /*One command is going to come at a time...App is doing the buffering if even it comes*/
        sCommand.uCommand.sScmCmd.sCmdBufferInfo.ui32DramCmdBufAddress = pScmCmdPayload->ui32DramCmdBufAddress;
        sCommand.uCommand.sScmCmd.sCmdBufferInfo.ui32DramRespBufAddress = pScmCmdPayload->ui32DramRespBufAddress;

        sCommand.uCommand.sScmCmd.sCmdBufferInfo.ui32DramCmdBufSize     = pScmCmdPayload->ui32DramCmdBufSize;
        sCommand.uCommand.sScmCmd.sCmdBufferInfo.ui32DramRespBufSize    = pScmCmdPayload->ui32DramRespBufSize;

        pRaagaTask->lastEventType = sCommand.sCommandHeader.ui32CommandID;
        ret = BERR_SUCCESS;

        ret = BDSP_Raaga_P_SendCommand(pDevice->hCmdQueue[0], &sCommand, (void *)pRaagaTask);

        if(BERR_SUCCESS != ret)
        {
            if((pRaagaContext->contextWatchdogFlag == false)
            &&(pRaagaTask->isStopped == false))
            {
                BDBG_ERR(("BDSP_Raaga_P_SendScmCommand: Send_Command failed!"));
                ret = BERR_TRACE(ret);
                goto end;
            }
            else
                ret = BERR_SUCCESS;
        }

        /* Wait for Response_Received event with timeout */
        ret = BKNI_WaitForEvent(pRaagaTask->hEvent, BDSP_RAAGA_EVENT_TIMEOUT_IN_MS);
                /* TODO: Ashok Add watchdog enable write above !! */


        if (BERR_TIMEOUT == ret)
        {

            if((pRaagaContext->contextWatchdogFlag == false ))
            {
                /* Please note that, If the code reaches at this point then there is a potential Bug in Fw
                        code which needs to be debugged. However Watchdog is being triggered to recover the system*/
                BDBG_WRN(("BDSP_Raaga_P_SendScmCommand: Triggering Watchdog"));

                /* BDSP_Write32(pDevice->regHandle, BCHP_AUD_DSP_INTH0_R5F_SET+ hDsp->ui32Offset,0x1); */
                /* TODO: Vijay Add watchdog enable write above !! */
                pRaagaContext->contextWatchdogFlag = true;
                ret = BERR_SUCCESS;
            }
            else
                ret = BERR_SUCCESS;
        }


                /* TODO: Ashok watchdog enable write above !! */

        eMsgType = BDSP_Raaga_P_MsgType_eSyn;

        if(pRaagaContext->contextWatchdogFlag == false)
        {
            ret = BDSP_Raaga_P_GetMsg(pRaagaTask->hSyncMsgQueue, (void *)&sRsp,eMsgType);
        }

        if(BERR_SUCCESS != ret)
        {
            if((pRaagaContext->contextWatchdogFlag == false ))
            {
                BDBG_ERR(("BDSP_Raaga_P_SendScmCommand: Unable to read Response!"));
                ret = BERR_TRACE(ret);
                goto end;
            }
            else
                ret = BERR_SUCCESS;
        }
        if((sRsp.sCommonAckResponseHeader.eStatus != BERR_SUCCESS)||
            (sRsp.sCommonAckResponseHeader.ui32ResponseID != BDSP_RAAGA_BSP_SCM_COMMAND_RESPONSE_ID)||
            (sRsp.sCommonAckResponseHeader.ui32TaskID != pRaagaTask->taskId))
        {
            if((pRaagaContext->contextWatchdogFlag == false))
            {
               BDBG_ERR(("BDSP_Raaga_P_SendScmCommand: RESPONSE not received successfully!eStatus = %d , ui32ResponseID = %d , ui32TaskID %d ",
                    sRsp.sCommonAckResponseHeader.eStatus,sRsp.sCommonAckResponseHeader.ui32ResponseID,sRsp.sCommonAckResponseHeader.ui32TaskID));
                ret = BERR_TRACE(sRsp.sCommonAckResponseHeader.eStatus);
                goto end;
            }
            else
                ret = BERR_SUCCESS;
        }


    }

end:

    BDBG_LEAVE(BDSP_Raaga_P_SendScmCommand);
    return ret;

}

/***********************************************************************
Name        :   BDSP_Raaga_P_AudioCaptureCreate

Type        :   PI Interface

Input       :   pContextHandle      -   Handle of the Context for which the capture needs to created.
                pCaptureCreateSettings  -   Settings of the Creating the capture.
                pCapture                -   Handle of the Capture which is returned back to PI.

Return      :   Error Code to return SUCCESS or FAILURE

Functionality   :   T.B.D
***********************************************************************/

BERR_Code BDSP_Raaga_P_AudioCaptureCreate(
    void *pContextHandle,
    const BDSP_AudioCaptureCreateSettings *pCaptureCreateSettings,
    BDSP_AudioCaptureHandle *pCapture)
{
    BERR_Code errCode = BERR_SUCCESS;
    BDSP_RaagaContext *pRaagaContext = (BDSP_RaagaContext *)pContextHandle;
    BDSP_RaagaCapture *pRaagaCapture;

    BDBG_OBJECT_ASSERT(pRaagaContext, BDSP_RaagaContext);
    *pCapture = NULL;

    /* Allocate capture structure and add it to the task's capture list */
    pRaagaCapture = (BDSP_RaagaCapture *)BKNI_Malloc(sizeof(BDSP_RaagaCapture));
    if ( NULL == pRaagaCapture )
    {
        errCode = BERR_TRACE(BERR_OUT_OF_SYSTEM_MEMORY);
        goto err_malloc_stage;
    }

    /* Update the capture information using the capture create settings */
    BKNI_Memset((void *)pRaagaCapture, 0, sizeof(*pRaagaCapture));
    pRaagaCapture->capture.pCapHandle = pRaagaCapture;
    /* Use the heap provided */
    if (pCaptureCreateSettings->hHeap)
    {
        pRaagaCapture->hHeap = pCaptureCreateSettings->hHeap;
    }
    else
    {
        pRaagaCapture->hHeap = pRaagaContext->pDevice->memHandle;
    }

    pRaagaCapture->pDevice = pRaagaContext->pDevice;

    errCode = BDSP_Raaga_P_InitAudioCaptureInfo(pRaagaCapture, pCaptureCreateSettings);

    pRaagaCapture->capture.destroy = BDSP_Raaga_P_AudioCaptureDestroy;
    pRaagaCapture->capture.addToStage = BDSP_Raaga_P_AudioCaptureAddToStage;
    pRaagaCapture->capture.removeFromStage = BDSP_Raaga_P_AudioCaptureRemoveFromStage;
    pRaagaCapture->capture.getBuffer = BDSP_Raaga_P_AudioCaptureGetBuffer;
    pRaagaCapture->capture.consumeData = BDSP_Raaga_P_AudioCaptureConsumeData;

    BDBG_OBJECT_SET(pRaagaCapture, BDSP_RaagaCapture);

    *pCapture = &pRaagaCapture->capture;

err_malloc_stage:
    return errCode;
}

void BDSP_Raaga_P_AudioCaptureDestroy (
    void *pCapHandle
    )
{
    BDSP_RaagaCapture *pRaagaCapture = pCapHandle;

    BDBG_OBJECT_ASSERT(pRaagaCapture, BDSP_RaagaCapture);

    if ( NULL != pRaagaCapture->pStage)
    {
        BDBG_ERR(("Please call BDSP_AudioTask_RemoveCapture() before calling BDSP_AudioCapture_Destroy()"));
        BDBG_ASSERT(NULL == pRaagaCapture->pStage);
    }

    pRaagaCapture->enabled = false;
    BDSP_MEM_P_FreeMemory(pRaagaCapture->hHeap, pRaagaCapture->capPtrs[0].captureBufferPtr.pBasePtr);
    BKNI_Free(pRaagaCapture);
}

BERR_Code BDSP_Raaga_P_AudioCaptureAddToStage(
    void *pCapHandle,
    void *pStageHandle,
    unsigned outputId,
    const BDSP_StageAudioCaptureSettings *pSettings
    )
{
    BERR_Code err = BERR_SUCCESS;
    int j;
    BDSP_RaagaCapture *pRaagaCapture = pCapHandle;
    BDSP_RaagaStage *pRaagaStage = pStageHandle;
    BDSP_AF_P_CIRCULAR_BUFFER *pBuffer;

    BDBG_ASSERT(NULL != pSettings);
    BDBG_ASSERT(NULL != pRaagaCapture);
    if ( outputId >= BDSP_AF_P_MAX_OP_FORKS )
    {
        return BERR_TRACE(BERR_INVALID_PARAMETER);
    }

    BKNI_AcquireMutex(pRaagaCapture->pDevice->captureMutex);
    BLST_S_INSERT_HEAD(&pRaagaStage->captureList, pRaagaCapture, node);

    /* Populate the output buffer type, num buffers and the output buffer pointers */
    err = BDSP_Raaga_P_GetAudioOutputPointers(&pRaagaStage->sStageOutput[outputId], pRaagaCapture);
    if (err != BERR_SUCCESS)
    {
        BLST_S_REMOVE(&pRaagaStage->captureList, pRaagaCapture, BDSP_RaagaCapture, node);
        BKNI_ReleaseMutex(pRaagaCapture->pDevice->captureMutex);
        BDBG_ERR(("Cannot add capture for an invalid output of the stage (%p)", (void *)pRaagaStage));
        return BERR_TRACE(BERR_NOT_SUPPORTED);
    }

    pRaagaCapture->pStage = pRaagaStage;

    BKNI_ReleaseMutex(pRaagaCapture->pDevice->captureMutex);

    pRaagaCapture->updateRead = pSettings->updateRead;

    /* Initialize the read/write pointers to base */
    for (j = 0; j < (int)BDSP_AF_P_MAX_CHANNELS; j++)
    {
        pBuffer = &pRaagaCapture->capPtrs[j].captureBufferPtr;
        pBuffer->pReadPtr = pBuffer->pBasePtr;
        pBuffer->pWritePtr = pBuffer->pBasePtr;
    }

    /* Set the shadow read pointers and last write pointer */
    switch (pRaagaCapture->eBuffType)
    {
        case BDSP_AF_P_BufferType_eFMM:
        case BDSP_AF_P_BufferType_eRDB:
        case BDSP_AF_P_BufferType_eRAVE:
            for (j = 0; j < pRaagaCapture->numBuffers; j++)
            {
                pRaagaCapture->capPtrs[j].shadowRead = BREG_Read32(
                    pRaagaCapture->pStage->pContext->pDevice->regHandle,
                    pRaagaCapture->capPtrs[j].outputBufferPtr.ui32BaseAddr);
                pRaagaCapture->capPtrs[j].lastWrite = BREG_Read32(
                    pRaagaCapture->pStage->pContext->pDevice->regHandle,
                    pRaagaCapture->capPtrs[j].outputBufferPtr.ui32WriteAddr);
            }
            break;
        case BDSP_AF_P_BufferType_eDRAM:
        default:
            for (j = 0; j < pRaagaCapture->numBuffers; j++)
            {
                pRaagaCapture->capPtrs[j].shadowRead = pRaagaCapture->capPtrs[j].outputBufferPtr.ui32BaseAddr;
                pRaagaCapture->capPtrs[j].lastWrite = pRaagaCapture->capPtrs[j].outputBufferPtr.ui32WriteAddr;
            }
            break;
    }

    /* Enable the capture */
    pRaagaCapture->enabled = true;

    return BERR_SUCCESS;
}

void BDSP_Raaga_P_AudioCaptureRemoveFromStage(
    void *pCapHandle,
    void *pStageHandle
    )
{
    BDSP_RaagaCapture *pRaagaCapture = pCapHandle;
    BDSP_RaagaStage *pRaagaStage = pStageHandle;

    BSTD_UNUSED(pRaagaStage);

    BDBG_OBJECT_ASSERT(pRaagaCapture, BDSP_RaagaCapture);
    /*BDBG_ASSERT(pStageHandle == pRaagaCapture->pStage);*/

    BKNI_AcquireMutex(pRaagaCapture->pDevice->captureMutex);
    /*BLST_S_REMOVE(&pRaagaStage->captureList, pRaagaCapture, BDSP_RaagaCapture, node);*/
    BLST_S_REMOVE(&pRaagaCapture->pStage->captureList, pRaagaCapture, BDSP_RaagaCapture, node);
    BKNI_ReleaseMutex(pRaagaCapture->pDevice->captureMutex);

    pRaagaCapture->enabled = false;
    pRaagaCapture->pStage = NULL;
}

static bool BDSP_Raaga_P_CheckAudioCaptureIsReady(
    void *pCapHandle,
    BREG_Handle hReg)
{

    BDSP_RaagaCapture *pRaagaCapture = pCapHandle;
    bool retval = false;
    int j;
    raaga_dramaddr  ui32WriteAddr, ui32StartWriteAddr;

    j = pRaagaCapture->numBuffers - 1;


    ui32StartWriteAddr = BREG_Read32(hReg, pRaagaCapture->capPtrs[j].ui32StartWriteAddr);
    ui32WriteAddr = BREG_Read32(hReg, pRaagaCapture->capPtrs[j].outputBufferPtr.ui32WriteAddr);

    if(ui32WriteAddr >= ui32StartWriteAddr)
    {
        retval = true;
    }
    else
    {
        retval = false;
    }

    return retval;
}

/***********************************************************************
Name        :   BDSP_Raaga_P_ProcessAudioCapture

Type        :   PI Interface

Input       :   pDevice - Void pointer of the device to be typecasted and used.

Return      :   Error Code to return SUCCESS or FAILURE

Functionality   :   T.B.D
***********************************************************************/

BERR_Code BDSP_Raaga_P_ProcessAudioCapture(
    void *pDevice /* [in] device handle */
    )
{
    int j;
    BERR_Code err = BERR_SUCCESS;

    BDSP_Raaga *pRaagaDevice = (BDSP_Raaga *)pDevice;
    BDSP_RaagaTask *pRaagaTask = NULL;
    BDSP_RaagaContext *pRaagaContext = NULL;
    BDSP_RaagaCapture *pRaagaCapture = NULL;

    bool retval;
    size_t opBuffDepth, capBuffSpace, bytesToCopy;
    uint8_t  *pCaptureWrite, *pCaptureRead, *pCaptureBase;

    void *readAddr;

    BDBG_ASSERT(NULL != pRaagaDevice);

    /* Need to iterate through all contexts -> tasks -> captures and
    copy the data from output buffers to capture buffers */

    BKNI_AcquireMutex(pRaagaDevice->captureMutex);
    for ( pRaagaContext = BLST_S_FIRST(&pRaagaDevice->contextList);
        pRaagaContext != NULL;
        pRaagaContext = BLST_S_NEXT(pRaagaContext, node) )
    {
        for ( pRaagaTask = BLST_S_FIRST(&pRaagaContext->allocTaskList);
            pRaagaTask != NULL;
            pRaagaTask = BLST_S_NEXT(pRaagaTask, node) )
        {
            if (!(pRaagaTask->isStopped))
            {
                BDSP_STAGE_TRAVERSE_LOOP_BEGIN(pRaagaTask->startSettings.primaryStage->pStageHandle, pStageIterator)
                BSTD_UNUSED(macroStId);
                BSTD_UNUSED(macroBrId);
                {
                    for ( pRaagaCapture = BLST_S_FIRST(&pStageIterator->captureList);
                        pRaagaCapture != NULL;
                        pRaagaCapture = BLST_S_NEXT(pRaagaCapture, node) )
                    {
                        if (pRaagaCapture->enabled)
                        {
                            if(pRaagaCapture->eBuffType == BDSP_AF_P_BufferType_eFMM && pRaagaCapture->StartCapture == false)
                            {

                                pRaagaCapture->StartCapture = BDSP_Raaga_P_CheckAudioCaptureIsReady(pRaagaCapture,
                                                                        pRaagaCapture->pStage->pContext->pDevice->regHandle);

                            }
                            else
                            {
                                pRaagaCapture->StartCapture = true;

                            }
                            if(true == pRaagaCapture->StartCapture)
                            {
                                for (j = 0; j < pRaagaCapture->numBuffers; j++)
                                {
                                    /* Detect read crossing shadow read and print debug error */
                                    retval = BDSP_Raaga_P_DetectAudioCaptureError(&pRaagaCapture->capPtrs[j].outputBufferPtr,
                                                                     pRaagaCapture->capPtrs[j].shadowRead,
                                                                     pRaagaCapture->capPtrs[j].lastWrite,
                                                                     pRaagaCapture->eBuffType,
                                                                     pRaagaCapture->pStage->pContext->pDevice->regHandle);

                                    if (retval)
                                    {
                                        BDBG_ERR(("!!! Capture error detected for buffer [%d] in capture %p", j, (void *)pRaagaCapture));
                                        continue;
                                    }

                                    /* GetBufferDepth of output buffer */
                                    opBuffDepth = BDSP_Raaga_P_GetAudioBufferDepthLinear(&pRaagaCapture->capPtrs[j].outputBufferPtr,
                                                                            pRaagaCapture->capPtrs[j].shadowRead,
                                                                            pRaagaCapture->eBuffType,
                                                                            pRaagaCapture->pStage->pContext->pDevice->regHandle);

                                    /* GetFreeSpace to end in the capture buffer */
                                    capBuffSpace = BDSP_Raaga_P_GetAudioCaptureBufferFreeSpaceLinear(&pRaagaCapture->capPtrs[j].captureBufferPtr);

                                    /* Copy the minimum */
                                    bytesToCopy = (opBuffDepth < capBuffSpace) ? opBuffDepth : capBuffSpace;

                                    /* Copy the data from the output buffers to the capture buffers */
                                    pCaptureWrite = pRaagaCapture->capPtrs[j].captureBufferPtr.pWritePtr;

                                    /* Convert physical offset to virtual address */
                                    if (pRaagaCapture->eBuffType == BDSP_AF_P_BufferType_eFMM)
                                    {
                                        /* Clear the wrap bit while copying the data from FMM buffers */
                                        BDSP_MEM_P_ConvertOffsetToCacheAddr(pRaagaCapture->pStage->pContext->pDevice->memHandle,
                                                                    (pRaagaCapture->capPtrs[j].shadowRead & 0x7FFFFFFF),
                                                                    &readAddr);
                                    }
                                    else
                                    {
                                        BDSP_MEM_P_ConvertOffsetToCacheAddr(pRaagaCapture->pStage->pContext->pDevice->memHandle,
                                                                    pRaagaCapture->capPtrs[j].shadowRead,
                                                                    &readAddr);
                                    }
                                    BDSP_MEM_P_FlushCache(pRaagaCapture->pStage->pContext->pDevice->memHandle, (void *)readAddr, bytesToCopy);
                                    BKNI_Memcpy((void *)pCaptureWrite, readAddr, bytesToCopy);


                                    /* Update the capture buffer write pointer and detect capture buffer overflow */
                                    pCaptureWrite += bytesToCopy;
                                    pCaptureBase = pRaagaCapture->capPtrs[j].captureBufferPtr.pBasePtr;
                                    pCaptureRead = pRaagaCapture->capPtrs[j].captureBufferPtr.pReadPtr;
                                    if (pCaptureWrite > pRaagaCapture->capPtrs[j].captureBufferPtr.pEndPtr)
                                    {
                                        BDBG_ERR(("!!! Error in capture logic: non-contiguous capture detected"));
                                    }

                                    if (pCaptureWrite == pRaagaCapture->capPtrs[j].captureBufferPtr.pEndPtr)
                                    {
                                        if (pCaptureBase == pCaptureRead)
                                        {
                                            BDBG_ERR(("!!! Capture buffer overflow for buffer [%d] for capture %p", j, (void *)pRaagaCapture));
                                            continue;
                                        }
                                        else
                                        {
                                            pCaptureWrite = pCaptureBase;
                                        }
                                    }

                                    pRaagaCapture->capPtrs[j].captureBufferPtr.pWritePtr = pCaptureWrite;

                                    /* Update the shadow read pointer and last write pointer */
                                    BDSP_Raaga_P_GetUpdatedShadowReadAndLastWrite(&pRaagaCapture->capPtrs[j].outputBufferPtr,
                                                                          &pRaagaCapture->capPtrs[j].shadowRead,
                                                                          &pRaagaCapture->capPtrs[j].lastWrite,
                                                                          pRaagaCapture->eBuffType,
                                                                          bytesToCopy,
                                                                          pRaagaTask->pContext->pDevice->regHandle);

                                    /* Update the output buffer read pointer in required */
                                    if (pRaagaCapture->updateRead)
                                    {
                                        BDSP_Raaga_P_UpdateReadPointer(&pRaagaCapture->capPtrs[j].outputBufferPtr,
                                                               pRaagaCapture->eBuffType,
                                                               pRaagaCapture->capPtrs[j].shadowRead,
                                                               pRaagaTask->pContext->pDevice->regHandle);
                                    }
                                } /* Looping through numBuffers */
                            }
                        } /* if capture is enabled */
                    } /* Looping through captureList*/
                } /* looping through stage */
                BDSP_STAGE_TRAVERSE_LOOP_END(pStageIterator)
            } /* if Task is running */
        } /* looping through tasklooping through context */
    } /* looping through context */
    BKNI_ReleaseMutex(pRaagaDevice->captureMutex);

    return err;
}

BERR_Code BDSP_Raaga_P_AudioCaptureGetBuffer(
    void *pCapture,   /* [in] capture handle */
    BDSP_BufferDescriptor *pBuffers     /* [out] pointer to buffer descriptor */
    )
{
    int j;
    uint32_t size, minSize, chunk1 = 0;
    uint8_t *base = 0, *read = 0, *end = 0, *write = 0;
    BDSP_RaagaCapture *pRaagaCapture;
    BERR_Code err = BERR_SUCCESS;

    pRaagaCapture = (BDSP_RaagaCapture *)pCapture;

    BDBG_ASSERT(NULL != pRaagaCapture);

    pBuffers->interleaved = false;
    pBuffers->numBuffers = pRaagaCapture->numBuffers;

    if (pRaagaCapture->enabled)
    {
        minSize = 0xFFFFFFFF;
        for (j = 0; j < pRaagaCapture->numBuffers; j++)
        {
            base = pRaagaCapture->capPtrs[j].captureBufferPtr.pBasePtr;
            end = pRaagaCapture->capPtrs[j].captureBufferPtr.pEndPtr;
            read = pRaagaCapture->capPtrs[j].captureBufferPtr.pReadPtr;
            write = pRaagaCapture->capPtrs[j].captureBufferPtr.pWritePtr;

            size = write - read;
            chunk1 = size;
            if (read > write)
            {
                chunk1 = end - read;
                size = chunk1 + (write - base);
            }

            if (size < minSize)
            {
                minSize = size;
            }
            pBuffers->buffers[j].pBuffer = (void *)read;
            pBuffers->buffers[j].pWrapBuffer = (void *)base;
        }

        /* Use chunk1 size from the last buffer as this
        is expected to be the same for all buffers */
        if (minSize <= chunk1)
        {
            /* Atleast one buffer did not wrap around */
            for (j = 0; j < pRaagaCapture->numBuffers; j++)
            {
                pBuffers->buffers[j].pWrapBuffer = NULL;
            }
            pBuffers->bufferSize = minSize;
            pBuffers->wrapBufferSize = 0;
        }
        else
        {
            pBuffers->bufferSize = chunk1;
            pBuffers->wrapBufferSize = minSize - pBuffers->bufferSize;
        }
    }
    else
    {
        pBuffers->bufferSize = 0;
        pBuffers->wrapBufferSize = 0;
    }

    return err;
}

BERR_Code BDSP_Raaga_P_AudioCaptureConsumeData(
    void *pCapture, /* [in] capture handle */
    uint32_t numBytes /* [in] sizes of data read from each intermediate buffer */
    )
{
    int j;
    uint8_t *pCaptureRead;
    BDSP_RaagaCapture *pRaagaCapture;
    BERR_Code err = BERR_SUCCESS;

    pRaagaCapture = (BDSP_RaagaCapture *)pCapture;

    BDBG_ASSERT(NULL != pRaagaCapture);

    if (pRaagaCapture->enabled)
    {
        for (j = 0; j < pRaagaCapture->numBuffers; j++)
        {
            pCaptureRead = pRaagaCapture->capPtrs[j].captureBufferPtr.pReadPtr;
            pCaptureRead += numBytes;
            if (pCaptureRead >= pRaagaCapture->capPtrs[j].captureBufferPtr.pEndPtr)
            {
                pCaptureRead = pRaagaCapture->capPtrs[j].captureBufferPtr.pBasePtr +
                               (pCaptureRead - pRaagaCapture->capPtrs[j].captureBufferPtr.pEndPtr);
            }
            pRaagaCapture->capPtrs[j].captureBufferPtr.pReadPtr = pCaptureRead;
        }
    }

    return err;
}

uint32_t BDSP_Raaga_P_GetAudioBufferDepthLinear(
    BDSP_AF_P_sDRAM_CIRCULAR_BUFFER *pBuffer,
    uint32_t ui32ShadowRead,
    BDSP_AF_P_BufferType eType,
    BREG_Handle hReg)
{
    uint32_t depth;
    raaga_dramaddr ui32BaseAddr, ui32EndAddr, ui32ReadAddr, ui32WriteAddr, ui32WrapAddr;

    switch (eType)
    {
        case BDSP_AF_P_BufferType_eRAVE:
            ui32BaseAddr = BREG_Read32(hReg, pBuffer->ui32BaseAddr);
            ui32EndAddr = BREG_Read32(hReg, pBuffer->ui32EndAddr);
            ui32ReadAddr = ui32ShadowRead;
            ui32WriteAddr = BREG_Read32(hReg, pBuffer->ui32WriteAddr);
            ui32WrapAddr = BREG_Read32(hReg, pBuffer->ui32WrapAddr);

            if (ui32WrapAddr == 0)
                ui32WrapAddr = ui32EndAddr;

            depth = ui32WriteAddr - ui32ReadAddr;
            if (ui32WriteAddr < ui32ReadAddr)
            {
                /* Return only the contiguous chunk size */
                depth = (ui32WrapAddr - ui32ReadAddr) + 1;
            }
            break;

        case BDSP_AF_P_BufferType_eFMM:
            ui32BaseAddr = BREG_Read32(hReg, pBuffer->ui32BaseAddr);
            ui32EndAddr = BREG_Read32(hReg, pBuffer->ui32EndAddr);
            ui32WriteAddr = BREG_Read32(hReg, pBuffer->ui32WriteAddr);
            ui32ReadAddr = ui32ShadowRead;

            /* Buffer full condition */
            if ((ui32ReadAddr ^ ui32WriteAddr) == 0x80000000)
            {
                depth = (ui32EndAddr - ui32BaseAddr) + 1;
            }
            else
            {
                ui32ReadAddr &= 0x7FFFFFFF;
                ui32WriteAddr &= 0x7FFFFFFF;

                depth = ui32WriteAddr - ui32ReadAddr;
                if (ui32WriteAddr < ui32ReadAddr)
                {
                    /* Return only the contiguous chunk size */
                    depth = (ui32EndAddr - ui32ReadAddr) + 1;
                }
            }

            break;

        case BDSP_AF_P_BufferType_eRDB:
            ui32BaseAddr = BREG_Read32(hReg, pBuffer->ui32BaseAddr);
            ui32EndAddr = BREG_Read32(hReg, pBuffer->ui32EndAddr);
            ui32ReadAddr = ui32ShadowRead;
            ui32WriteAddr = BREG_Read32(hReg, pBuffer->ui32WriteAddr);

            depth = ui32WriteAddr - ui32ReadAddr;
            if (ui32WriteAddr < ui32ReadAddr)
            {
                /* Return only the contiguous chunk size */
                depth = (ui32EndAddr - ui32ReadAddr);
            }
            break;

        case BDSP_AF_P_BufferType_eDRAM:
        default:
            ui32BaseAddr = pBuffer->ui32BaseAddr;
            ui32EndAddr = pBuffer->ui32EndAddr;
            ui32ReadAddr = ui32ShadowRead;
            ui32WriteAddr = pBuffer->ui32WriteAddr;

            depth = ui32WriteAddr - ui32ReadAddr;
            if (ui32WriteAddr < ui32ReadAddr)
            {
                /* Return only the contiguous chunk size */
                depth = (ui32EndAddr - ui32ReadAddr);
            }
            break;
    }

    return depth;
}

size_t BDSP_Raaga_P_GetAudioCaptureBufferFreeSpaceLinear(BDSP_AF_P_CIRCULAR_BUFFER *pBuffer)
{
    size_t space;
    uint8_t *pEndPtr, *pReadPtr, *pWritePtr;

    pEndPtr = pBuffer->pEndPtr;
    pReadPtr = pBuffer->pReadPtr;
    pWritePtr = pBuffer->pWritePtr;

    space = pReadPtr - pWritePtr;
    if (pWritePtr >= pReadPtr)
    {
        space = pEndPtr - pWritePtr;
    }

    return space;
}

bool BDSP_Raaga_P_DetectAudioCaptureError(
    BDSP_AF_P_sDRAM_CIRCULAR_BUFFER *pBuffer,
    uint32_t ui32ShadowRead,
    uint32_t ui32LastWrite,
    BDSP_AF_P_BufferType eType,
    BREG_Handle hReg)
{
    bool retval = false;
    raaga_dramaddr ui32WriteAddr;

    switch (eType)
    {
        case BDSP_AF_P_BufferType_eRAVE:
            ui32WriteAddr = BREG_Read32(hReg, pBuffer->ui32WriteAddr);
            break;
        case BDSP_AF_P_BufferType_eFMM:
            ui32WriteAddr = BREG_Read32(hReg, pBuffer->ui32WriteAddr);
            /* Clear the wrap bit */
            ui32WriteAddr &= 0x7FFFFFFF;
            ui32ShadowRead &= 0x7FFFFFFF;
            break;
        case BDSP_AF_P_BufferType_eRDB:
            ui32WriteAddr = BREG_Read32(hReg, pBuffer->ui32WriteAddr);
            break;
        case BDSP_AF_P_BufferType_eDRAM:
        default:
            ui32WriteAddr = pBuffer->ui32WriteAddr;
            break;
    }

    /* It is not possible to detect a capture error if shadow read and last write are the same */
    if (ui32ShadowRead == ui32LastWrite)
    {
        retval = false;
    }
    else
    {
        if (ui32ShadowRead > ui32LastWrite)
        {
            if ((ui32WriteAddr > ui32ShadowRead)
                || (ui32WriteAddr < ui32LastWrite))
            {
                retval = true;
            }
        }
        else
        {
            if ((ui32WriteAddr > ui32ShadowRead)
                && (ui32WriteAddr < ui32LastWrite))
            {
                retval = true;
            }
        }
    }

    if (retval)
    {
        BDBG_ERR(("shadow = %x : write = %x : last wr = %x", ui32ShadowRead, ui32WriteAddr, ui32LastWrite));
    }

    return retval;
}


void BDSP_Raaga_P_GetUpdatedShadowReadAndLastWrite(
    BDSP_AF_P_sDRAM_CIRCULAR_BUFFER *pBuffer,
    raaga_dramaddr *pShadowRead,
    raaga_dramaddr *pLastWrite,
    BDSP_AF_P_BufferType eType,
    uint32_t bytesRead,
    BREG_Handle hReg)
{
    raaga_dramaddr shadowReadAddr;
    raaga_dramaddr baseAddr, endAddr;

    shadowReadAddr = *pShadowRead + bytesRead;

    switch (eType)
    {
        case BDSP_AF_P_BufferType_eRAVE:
            *pLastWrite = BREG_Read32(hReg, pBuffer->ui32WriteAddr);
            baseAddr = BREG_Read32(hReg, pBuffer->ui32BaseAddr);
            endAddr = BREG_Read32(hReg, pBuffer->ui32WrapAddr);
            if (endAddr == 0)
            {
                endAddr = BREG_Read32(hReg, pBuffer->ui32EndAddr);
            }

            /* TBD: Need to verify if this is correct. Code borrowed from raaga test */
            if (shadowReadAddr >= endAddr)
            {
                shadowReadAddr = baseAddr + (shadowReadAddr - endAddr);
            }
            break;
        case BDSP_AF_P_BufferType_eFMM:
            *pLastWrite = BREG_Read32(hReg, pBuffer->ui32WriteAddr);
            /* Clear the wrap bit */
            *pLastWrite &= 0x7FFFFFFF;
            baseAddr = BREG_Read32(hReg, pBuffer->ui32BaseAddr);
            endAddr = BREG_Read32(hReg, pBuffer->ui32EndAddr);

            if ((shadowReadAddr & 0x7FFFFFFF) > endAddr)
            {
                shadowReadAddr = baseAddr + (shadowReadAddr - endAddr) - 1;
                /* Flip bit 31 on a wrap */
                shadowReadAddr ^= 0x80000000;
            }
            break;
        case BDSP_AF_P_BufferType_eRDB:
            *pLastWrite = BREG_Read32(hReg, pBuffer->ui32WriteAddr);
            baseAddr = BREG_Read32(hReg, pBuffer->ui32BaseAddr);
            endAddr = BREG_Read32(hReg, pBuffer->ui32EndAddr);

            if (shadowReadAddr >= endAddr)
            {
                shadowReadAddr = baseAddr + (shadowReadAddr - endAddr);
            }
            break;
        case BDSP_AF_P_BufferType_eDRAM:
        default:
            *pLastWrite = pBuffer->ui32WriteAddr;
            baseAddr = pBuffer->ui32BaseAddr;
            endAddr = pBuffer->ui32EndAddr;
            if (shadowReadAddr >= endAddr)
            {
                shadowReadAddr = baseAddr + (shadowReadAddr - endAddr);
            }
            break;
    }

    *pShadowRead = shadowReadAddr;
}

void BDSP_Raaga_P_UpdateReadPointer(
    BDSP_AF_P_sDRAM_CIRCULAR_BUFFER *pBuffer,
    BDSP_AF_P_BufferType eType,
    raaga_dramaddr ui32ReadAddr,
    BREG_Handle hReg)
{
    switch (eType)
    {
        case BDSP_AF_P_BufferType_eRAVE:
        case BDSP_AF_P_BufferType_eFMM:
        case BDSP_AF_P_BufferType_eRDB:
            BREG_Write32(hReg, pBuffer->ui32ReadAddr, ui32ReadAddr);
            break;
        case BDSP_AF_P_BufferType_eDRAM:
        default:
            pBuffer->ui32ReadAddr = ui32ReadAddr;
            break;
    }
}

BERR_Code BDSP_Raaga_P_InitAudioCaptureInfo(BDSP_RaagaCapture *pRaagaCapture, const BDSP_AudioCaptureCreateSettings *pSettings)
{
    unsigned j;
    uint32_t memRequired;
    BERR_Code err = BERR_SUCCESS;
    uint8_t *captureMem;
    BDSP_AF_P_CIRCULAR_BUFFER *pBuffer;

    BDBG_ENTER(BDSP_Raaga_P_InitAudioCaptureInfo);

    BDBG_ASSERT(NULL != pRaagaCapture);

    pRaagaCapture->enabled = false;
    pRaagaCapture->maxBuffers = pSettings->maxChannels;

    /* Allocate memory for the worst case output */
    memRequired = pSettings->maxChannels*pSettings->channelBufferSize;

    /* Allocate the intermediate capture buffers */
    captureMem = (uint8_t *)BDSP_MEM_P_AllocateAlignedMemory(pRaagaCapture->hHeap, (memRequired + 32), 5, 0);
    if (NULL == captureMem)
    {
        BDBG_ERR(("Unable to Allocate memory for Capture buffers !"));
        err = BERR_TRACE(BERR_OUT_OF_DEVICE_MEMORY);
        return err;
    }

    /* Split the allocated space into individual capture buffers */
    for (j = 0; j < pSettings->maxChannels; j++)
    {
        pBuffer = &pRaagaCapture->capPtrs[j].captureBufferPtr;
        pBuffer->pBasePtr = captureMem + j*pSettings->channelBufferSize;
        pBuffer->pReadPtr = captureMem + j*pSettings->channelBufferSize;
        pBuffer->pWritePtr = captureMem + j*pSettings->channelBufferSize;
        pBuffer->pEndPtr = captureMem + (j+1)*pSettings->channelBufferSize;
        pBuffer->pWrapPtr = captureMem + (j+1)*pSettings->channelBufferSize;
    }

    /* Reset the pointers for the rest of the buffers */
    for ( ; j < BDSP_AF_P_MAX_CHANNELS; j++)
    {
        pBuffer = &pRaagaCapture->capPtrs[j].captureBufferPtr;
        pBuffer->pBasePtr = 0;
        pBuffer->pReadPtr = 0;
        pBuffer->pWritePtr = 0;
        pBuffer->pEndPtr = 0;
        pBuffer->pWrapPtr = 0;
    }

    BDBG_LEAVE(BDSP_Raaga_P_InitAudioCaptureInfo);
    return err;
}

BERR_Code BDSP_Raaga_P_GetAudioOutputPointers(BDSP_StageSrcDstDetails *pDstDetails, BDSP_RaagaCapture *pRaagaCapture)
{
    int i, numBuffers;
    BERR_Code err = BERR_SUCCESS;
    BDSP_AF_P_sDRAM_CIRCULAR_BUFFER *psCircBuffer;
    BDSP_P_InterTaskBuffer *pRaagaInterTaskBuffer;

    if (pDstDetails->eNodeValid != BDSP_AF_P_eValid)
    {
        BDBG_ERR(("Cannot add capture for an invalid output of the stage"));
        return BERR_TRACE(BERR_NOT_SUPPORTED);
    }

    BDBG_ENTER(BDSP_Raaga_P_GetAudioOutputPointers);

    switch (pDstDetails->eConnectionType)
    {
        case BDSP_ConnectionType_eFmmBuffer:
            numBuffers = pDstDetails->connectionDetails.fmm.descriptor.numBuffers;
            for(i = 0; i < numBuffers; i++)
            {
                psCircBuffer = &pRaagaCapture->capPtrs[i].outputBufferPtr;
                psCircBuffer->ui32ReadAddr  = pDstDetails->connectionDetails.fmm.descriptor.buffers[i].read;
                psCircBuffer->ui32WriteAddr = pDstDetails->connectionDetails.fmm.descriptor.buffers[i].write;
                psCircBuffer->ui32BaseAddr  = pDstDetails->connectionDetails.fmm.descriptor.buffers[i].base;
                psCircBuffer->ui32EndAddr   = pDstDetails->connectionDetails.fmm.descriptor.buffers[i].end;
                psCircBuffer->ui32WrapAddr = pDstDetails->connectionDetails.fmm.descriptor.buffers[i].end;

                pRaagaCapture->capPtrs[i].ui32StartWriteAddr = psCircBuffer->ui32EndAddr + 8;
            }

            pRaagaCapture->StartCapture =  false;/** Will only set to true once write pointer is >= start write pointer  **/
            pRaagaCapture->eBuffType = BDSP_AF_P_BufferType_eFMM;
            break;

        case BDSP_ConnectionType_eInterTaskBuffer:
            pRaagaInterTaskBuffer = (BDSP_P_InterTaskBuffer *)pDstDetails->connectionDetails.interTask.hInterTask->pInterTaskBufferHandle;

            numBuffers = pRaagaInterTaskBuffer->numChans;
            for(i = 0; i < numBuffers; i++)
            {
                psCircBuffer = &pRaagaCapture->capPtrs[i].outputBufferPtr;
                *psCircBuffer = ((BDSP_AF_P_sIO_BUFFER *)(pRaagaInterTaskBuffer->pIoBufferDesc))->sCircBuffer[i];
            }

            pRaagaCapture->eBuffType = BDSP_AF_P_BufferType_eDRAM;
            break;

        case BDSP_ConnectionType_eRaveBuffer:
            numBuffers = pDstDetails->IoBuffer.ui32NumBuffers;

            for (i = 0; i < numBuffers; i++)
            {
                psCircBuffer = &pRaagaCapture->capPtrs[i].outputBufferPtr;
                /* The rave pointers are programmed with the chip physical offset added. Masking the same */
                psCircBuffer->ui32BaseAddr = pDstDetails->IoBuffer.sCircBuffer[i].ui32BaseAddr & 0x0FFFFFFF;
                psCircBuffer->ui32ReadAddr = pDstDetails->IoBuffer.sCircBuffer[i].ui32ReadAddr & 0x0FFFFFFF;
                psCircBuffer->ui32WriteAddr = pDstDetails->IoBuffer.sCircBuffer[i].ui32WriteAddr & 0x0FFFFFFF;
                psCircBuffer->ui32EndAddr = pDstDetails->IoBuffer.sCircBuffer[i].ui32EndAddr & 0x0FFFFFFF;
                psCircBuffer->ui32WrapAddr = pDstDetails->IoBuffer.sCircBuffer[i].ui32WrapAddr & 0x0FFFFFFF;
            }

            pRaagaCapture->eBuffType = BDSP_AF_P_BufferType_eRAVE;
            break;
        default:
            BDBG_ERR(("Output Capture not supported for buffer type (%d)", pDstDetails->eConnectionType));
            return BERR_TRACE(BERR_INVALID_PARAMETER);
            break;
    }

    pRaagaCapture->numBuffers = numBuffers;

    BDBG_LEAVE(BDSP_Raaga_P_GetAudioOutputPointers);

    return err;
}

/***********************************************************************
Name        :   BDSP_Raaga_P_Freeze

Type        :   PI Interface

Input       :   pTaskHandle -   Handle of the Task which needs to be Freezed.
                pSettings       -   Setting to be used to Freeze

Return      :   Error Code to return SUCCESS or FAILURE

Functionality   :   Following are the operations performed.
        1)  Check if the task is started and not in frozen state.
        2)  Retreive the STC address ( lower 32 bit) and provide it to FW for internal processing of STC snapshotting.
        3)  Send the Freeze Command with dummy FMM port details to the FW and wait for the acknowledgement.
***********************************************************************/

BERR_Code BDSP_Raaga_P_Freeze(
    void *hTask,
    const BDSP_AudioTaskFreezeSettings *pSettings
    )
{
    BDSP_RaagaTask *pRaagaTask = (BDSP_RaagaTask *)hTask;
    BDSP_Raaga  *pDevice= pRaagaTask->pContext->pDevice;
    BERR_Code err=BERR_SUCCESS;
    BDSP_Raaga_P_MsgType      eMsgType;
    BDSP_Raaga_P_Command sCommand;
    BDSP_Raaga_P_Response sRsp;
    BDSP_AudioTaskTsmSettings sTsmSettings;

    BDBG_OBJECT_ASSERT(pRaagaTask, BDSP_RaagaTask);

    if (pRaagaTask->isStopped == true)
    {
        BDBG_WRN(("Task is not started yet. Ignoring the Freeze command"));
        goto end;
    }
    else
    {
    if (pRaagaTask->frozen == true)
        {
            BDBG_WRN(("Task is already in Frozen state. Ignoring the Freeze command"));
            goto end;
        }
        else
        {
            /* Create Freeze command */
            BKNI_Memset((void *)&sRsp,0,sizeof(BDSP_Raaga_P_Response));
            BKNI_Memset((void *)&sCommand,0,sizeof(BDSP_Raaga_P_Command));

            /* Populate command headers */
            sCommand.sCommandHeader.ui32CommandID = BDSP_RAAGA_AUDIO_OUTPUT_FREEZE_COMMAND_ID;
            sCommand.sCommandHeader.ui32CommandCounter =  pRaagaTask->commandCounter++;
            sCommand.sCommandHeader.ui32TaskID =  pRaagaTask->taskId;
            sCommand.sCommandHeader.eResponseType = BDSP_Raaga_P_ResponseType_eAckRequired;
            sCommand.sCommandHeader.ui32CommandSizeInBytes =  sizeof(BDSP_Raaga_P_Command);

            /* Populate command payload */
            sCommand.uCommand.sFreezeCommand.ui32AudFmmOutputPortAddr = pSettings->fmmOutputAddress;
            sCommand.uCommand.sFreezeCommand.ui32AudFmmOutputPortMask= pSettings->fmmOutputMask;
            sCommand.uCommand.sFreezeCommand.ui32AudFmmOutputPortValue= pSettings->fmmOutputValue;

            /* Populate STC Address from TSM settings buffer */
            BKNI_EnterCriticalSection();

            /* Hardcoding branch and stage to 0, 0 */
            BDSP_Raaga_P_GetTsmSettings_isr(pRaagaTask->startSettings.primaryStage->pStageHandle, &sTsmSettings);

            BKNI_LeaveCriticalSection();

            /* TBD: Currently we use only 32 bit STC. So hardcoding the higher to 0 as there is no provision exposed in TSM settings for now */
            sCommand.uCommand.sFreezeCommand.ui32StcHiAddress = 0;
            sCommand.uCommand.sFreezeCommand.ui32StcLoAddress = sTsmSettings.ui32STCAddr;

            pRaagaTask->lastEventType = sCommand.sCommandHeader.ui32CommandID;
            BKNI_ResetEvent(pRaagaTask->hEvent);
            err = BDSP_Raaga_P_SendCommand(
                pDevice->hCmdQueue[pRaagaTask->settings.dspIndex],
                &sCommand,pRaagaTask);

            if (BERR_SUCCESS != err)
            {
                BDBG_ERR(("BDSP_Raaga_P_Freeze: Freeze Command failed!"));
                err = BERR_TRACE(err);
                goto end;
            }
            /* Wait for Ack_Response_Received event w/ timeout */
            err = BKNI_WaitForEvent(pRaagaTask->hEvent, BDSP_RAAGA_EVENT_TIMEOUT_IN_MS);
            if (BERR_TIMEOUT == err)
            {
                BDBG_ERR(("BDSP_Raaga_P_Freeze: Freeze Command ACK timeout! "));
                /* TBD: Trigger Watchdog */
                err = BERR_TRACE(err);
                goto end;
            }

            eMsgType = BDSP_Raaga_P_MsgType_eSyn;
            err = BDSP_Raaga_P_GetMsg(pRaagaTask->hSyncMsgQueue, (void *)&sRsp, eMsgType);
            if (BERR_SUCCESS != err)
            {
                BDBG_ERR(("BDSP_Raaga_P_Freeze: Unable to read ACK!"));
                err = BERR_TRACE(err);
                goto end;
            }

            if ((sRsp.sCommonAckResponseHeader.eStatus != BERR_SUCCESS)||
                (sRsp.sCommonAckResponseHeader.ui32ResponseID != BDSP_RAAGA_AUDIO_OUTPUT_FREEZE_COMMAND_ACK_ID)||
                (sRsp.sCommonAckResponseHeader.ui32TaskID != pRaagaTask->taskId))
            {
                BDBG_ERR(("sRsp.sCommonAckResponseHeader.eStatus =%d",sRsp.sCommonAckResponseHeader.eStatus));
                BDBG_ERR(("BDSP_Raaga_P_Freeze: Freeze Command response not received successfully!"));
                err = BERR_TRACE(sRsp.sCommonAckResponseHeader.eStatus);
                goto end;
            }
            pRaagaTask->frozen = true;
        }
    }
    end:
    return err;



}

/***********************************************************************
Name        :   BDSP_Raaga_P_UnFreeze

Type        :   PI Interface

Input       :   pTaskHandle -   Handle of the Task which needs to be Freezed.
                pSettings       -   Setting to be used to Un-Freeze

Return      :   Error Code to return SUCCESS or FAILURE

Functionality   :   Following are the operations performed.
        1)  Check if the task is started and in frozen state.
        2)  Retreive the STC address ( lower 32 bit) and provide it to FW for internal processing of STC snapshotting.
        3)  Send the UnFreeze Command with dummy FMM port details to the FW and wait for the acknowledgement.
***********************************************************************/

BERR_Code BDSP_Raaga_P_UnFreeze(
    void * hTask,
    const BDSP_AudioTaskUnFreezeSettings *pSettings
    )
{
    BDSP_RaagaTask *pRaagaTask = (BDSP_RaagaTask *)hTask;
    BDSP_Raaga  *pDevice= pRaagaTask->pContext->pDevice;
    BERR_Code err=BERR_SUCCESS;
    BDSP_Raaga_P_MsgType      eMsgType;
    BDSP_Raaga_P_Command sCommand;
    BDSP_Raaga_P_Response sRsp;
    BDSP_AudioTaskTsmSettings sTsmSettings;
    int i;

    BDBG_OBJECT_ASSERT(pRaagaTask, BDSP_RaagaTask);

    if (pRaagaTask->isStopped == true)
    {
        BDBG_WRN(("Task is not started yet. Ignoring the UnFreeze command"));
        goto end;
    }
    else
    {
    if (pRaagaTask->frozen == false)
        {
            BDBG_WRN(("Task is already running normally. Ignoring the UnFreeze command"));
            goto end;
        }
        else
        {
            /* Create UnFreeze command */
            BKNI_Memset((void *)&sRsp,0,sizeof(BDSP_Raaga_P_Response));
            BKNI_Memset((void *)&sCommand,0,sizeof(BDSP_Raaga_P_Command));

            /* Populate command headers */
            sCommand.sCommandHeader.ui32CommandID = BDSP_RAAGA_AUDIO_OUTPUT_UNFREEZE_COMMAND_ID;
            sCommand.sCommandHeader.ui32CommandCounter =  pRaagaTask->commandCounter++;
            sCommand.sCommandHeader.ui32TaskID =  pRaagaTask->taskId;
            sCommand.sCommandHeader.eResponseType = BDSP_Raaga_P_ResponseType_eAckRequired;
            sCommand.sCommandHeader.ui32CommandSizeInBytes =  sizeof(BDSP_Raaga_P_Command);

            /* Populate command payload */
            sCommand.uCommand.uUnFreezeCommand.sUnFreezeHostToDspCmd.ui32AudFmmOutputPortAddr = pSettings->fmmOutputAddress;
            sCommand.uCommand.uUnFreezeCommand.sUnFreezeHostToDspCmd.ui32AudFmmOutputPortMask= pSettings->fmmOutputMask;
            sCommand.uCommand.uUnFreezeCommand.sUnFreezeHostToDspCmd.ui32AudFmmOutputPortValue= pSettings->fmmOutputValue;

            sCommand.uCommand.uUnFreezeCommand.sUnFreezeHostToDspCmd.ui32NumDummySinkBuffers= pSettings->ui32NumBuffers;
                if (sCommand.uCommand.uUnFreezeCommand.sUnFreezeHostToDspCmd.ui32NumDummySinkBuffers > 2)
            {
              sCommand.uCommand.uUnFreezeCommand.sUnFreezeHostToDspCmd.ui32NumDummySinkBuffers = 2;
              BDBG_ERR(("Number of Dummy Sink channels greater than 2. DSP will hardcode it to 2. Please revisit configuration."));
                          BDBG_ERR(("NumDummyBuffers = %d",sCommand.uCommand.uUnFreezeCommand.sUnFreezeHostToDspCmd.ui32NumDummySinkBuffers ));
            }

            for (i=0; i<1; i++ ) /*sCommand.uCommand.uUnFreezeCommand.sUnFreezeHostToDspCmd.ui32NumDummySinkBuffers; i++)  */
            {
                sCommand.uCommand.uUnFreezeCommand.sUnFreezeHostToDspCmd.sCircBuffer[i].ui32ReadAddr = pSettings->sCircBuffer[i].ui32ReadAddr;
                sCommand.uCommand.uUnFreezeCommand.sUnFreezeHostToDspCmd.sCircBuffer[i].ui32WriteAddr = pSettings->sCircBuffer[i].ui32WriteAddr;
                sCommand.uCommand.uUnFreezeCommand.sUnFreezeHostToDspCmd.sCircBuffer[i].ui32BaseAddr = pSettings->sCircBuffer[i].ui32BaseAddr;
                sCommand.uCommand.uUnFreezeCommand.sUnFreezeHostToDspCmd.sCircBuffer[i].ui32EndAddr = pSettings->sCircBuffer[i].ui32EndAddr;
                sCommand.uCommand.uUnFreezeCommand.sUnFreezeHostToDspCmd.sCircBuffer[i].ui32WrapAddr = pSettings->sCircBuffer[i].ui32WrapAddr;
            }



            /* Populate STC Address from TSM settings buffer */
            BKNI_EnterCriticalSection();
            BDSP_Raaga_P_GetTsmSettings_isr(pRaagaTask->startSettings.primaryStage->pStageHandle, &sTsmSettings);

            BKNI_LeaveCriticalSection();

            /* TBD: Currently we use only 32 bit STC. So hardcoding the higher to 0 as there is no provision exposed in TSM settings for now */
            sCommand.uCommand.uUnFreezeCommand.sUnFreezeHostToDspCmd.ui32StcHiAddress = 0;
            sCommand.uCommand.uUnFreezeCommand.sUnFreezeHostToDspCmd.ui32StcLoAddress = sTsmSettings.ui32STCAddr;

            pRaagaTask->lastEventType = sCommand.sCommandHeader.ui32CommandID;
            BKNI_ResetEvent(pRaagaTask->hEvent);

            err = BDSP_Raaga_P_SendCommand(
                pDevice->hCmdQueue[pRaagaTask->settings.dspIndex],
                &sCommand,pRaagaTask);

            if (BERR_SUCCESS != err)
            {
                BDBG_ERR(("BDSP_Raaga_P_UnFreeze: UnFreeze Command failed!"));
                err = BERR_TRACE(err);
                goto end;
            }
            /* Wait for Ack_Response_Received event w/ timeout */
            err = BKNI_WaitForEvent(pRaagaTask->hEvent, BDSP_RAAGA_EVENT_TIMEOUT_IN_MS);
            if (BERR_TIMEOUT == err)
            {
                BDBG_ERR(("BDSP_Raaga_P_UnFreeze: UnFreeze Command ACK timeout!"));
                /* TBD: Trigger Watchdog */
                err = BERR_TRACE(err);
                goto end;
            }

            eMsgType = BDSP_Raaga_P_MsgType_eSyn;
            err = BDSP_Raaga_P_GetMsg(pRaagaTask->hSyncMsgQueue, (void *)&sRsp, eMsgType);
            if (BERR_SUCCESS != err)
            {
                BDBG_ERR(("BDSP_Raaga_P_UnFreeze: Unable to read ACK!"));
                err = BERR_TRACE(err);
                goto end;
            }

            if ((sRsp.sCommonAckResponseHeader.eStatus != BERR_SUCCESS)||
                (sRsp.sCommonAckResponseHeader.ui32ResponseID != BDSP_RAAGA_AUDIO_OUTPUT_UNFREEZE_COMMAND_ACK_ID)||
                (sRsp.sCommonAckResponseHeader.ui32TaskID != pRaagaTask->taskId))
            {
                BDBG_ERR(("sRsp.sCommonAckResponseHeader.eStatus =%d",sRsp.sCommonAckResponseHeader.eStatus));
                BDBG_ERR(("BDSP_Raaga_P_UnFreeze: UnFreeze Command response not received successfully!"));
                err = BERR_TRACE(sRsp.sCommonAckResponseHeader.eStatus);
                goto end;
            }
            pRaagaTask->frozen = false;
        }
    }
    end:
    return err;
}



void BDSP_Raaga_P_Queue_GetIoBuffer(
    void *pQueueHandle,
    BDSP_AF_P_sIO_BUFFER *pBuffer /*[out]*/
    )
{
    BDSP_RaagaQueue *pRaagaQueue;
    BDSP_Raaga_P_MsgQueueHandle hAncDataMsgQueue[BDSP_AF_P_MAX_CHANNELS];
    unsigned i=0;
    BDBG_ENTER(BDSP_Raaga_P_Queue_GetIoBuffer);

    pRaagaQueue = (BDSP_RaagaQueue *)pQueueHandle;
    BDBG_OBJECT_ASSERT(pRaagaQueue, BDSP_RaagaQueue);


    /* Assuming it is RDB Addresses */
    pBuffer->ui32NumBuffers = pRaagaQueue->numChans;
    pBuffer->eBufferType = BDSP_AF_P_BufferType_eRDB;

    for (i=0; i < pRaagaQueue->numChans; i++)
    {
        hAncDataMsgQueue[i] = pRaagaQueue->FIFOdata[i];
        pBuffer->sCircBuffer[i].ui32BaseAddr = BDSP_RAAGA_REGSET_ADDR_FOR_DSP( hAncDataMsgQueue[i]->ui32BaseAddr );
        pBuffer->sCircBuffer[i].ui32EndAddr = BDSP_RAAGA_REGSET_ADDR_FOR_DSP( hAncDataMsgQueue[i]->ui32EndAddr );
        pBuffer->sCircBuffer[i].ui32ReadAddr = BDSP_RAAGA_REGSET_ADDR_FOR_DSP( hAncDataMsgQueue[i]->ui32ReadAddr );
        pBuffer->sCircBuffer[i].ui32WriteAddr = BDSP_RAAGA_REGSET_ADDR_FOR_DSP( hAncDataMsgQueue[i]->ui32WriteAddr );
        pBuffer->sCircBuffer[i].ui32WrapAddr = BDSP_RAAGA_REGSET_ADDR_FOR_DSP( hAncDataMsgQueue[i]->ui32EndAddr );

    }

    BDBG_LEAVE(BDSP_Raaga_P_Queue_GetIoBuffer);
}


BERR_Code BDSP_Raaga_P_Queue_GetBuffer(
    void *pQueueHandle,
    BDSP_BufferDescriptor *pDescriptor /*[out] */
)
{
    BDSP_RaagaQueue *pRaagaQueue;
    BERR_Code errCode=BERR_SUCCESS;
    BDSP_Raaga_P_MsgQueueHandle hAncDataMsgQueue;
    raaga_dramaddr ui32BaseAddr, ui32EndAddr, ui32ReadAddr, ui32WriteAddr = 0;
    uint32_t ui32Size, ui32WrapSize = 0;
    BDBG_ENTER(BDSP_Raaga_P_Queue_GetBuffer);

    pRaagaQueue = (BDSP_RaagaQueue *)pQueueHandle;
    BDBG_OBJECT_ASSERT(pRaagaQueue, BDSP_RaagaQueue);

    hAncDataMsgQueue = pRaagaQueue->FIFOdata[0];

    ui32BaseAddr = BDSP_Read32(hAncDataMsgQueue->hRegister, hAncDataMsgQueue->ui32BaseAddr);
    ui32EndAddr = BDSP_Read32(hAncDataMsgQueue->hRegister, hAncDataMsgQueue->ui32EndAddr);
    ui32ReadAddr = BDSP_Read32(hAncDataMsgQueue->hRegister, hAncDataMsgQueue->ui32ReadAddr);
    ui32WriteAddr = BDSP_Read32(hAncDataMsgQueue->hRegister, hAncDataMsgQueue->ui32WriteAddr);

    if ( pRaagaQueue->input )
    {
        if (ui32ReadAddr > ui32WriteAddr)
        {
            ui32Size = ui32ReadAddr - ui32WriteAddr;
            ui32WrapSize = 0;
        }
        else
        {
            ui32Size = ui32EndAddr - ui32WriteAddr;
            ui32WrapSize = ui32ReadAddr - ui32BaseAddr;
        }
        BMEM_ConvertOffsetToAddress(hAncDataMsgQueue->hHeap, ui32WriteAddr, &(pDescriptor->buffers[0].pBuffer));
    }
    else
    {

        if (ui32WriteAddr >= ui32ReadAddr)
        {
            ui32Size = ui32WriteAddr - ui32ReadAddr;
            ui32WrapSize = 0;
        }
        else
        {
            ui32Size = ui32EndAddr - ui32ReadAddr;
            ui32WrapSize = ui32WriteAddr - ui32BaseAddr;
        }
        BMEM_ConvertOffsetToAddress(hAncDataMsgQueue->hHeap, ui32ReadAddr, &(pDescriptor->buffers[0].pBuffer));
    }
    pDescriptor->numBuffers = 1;
    pDescriptor->interleaved = false;
    pDescriptor->bufferSize = ui32Size;
    pDescriptor->wrapBufferSize = ui32WrapSize;

    if (ui32WrapSize)
    {
     BMEM_ConvertOffsetToAddress(hAncDataMsgQueue->hHeap, ui32BaseAddr, &(pDescriptor->buffers[0].pWrapBuffer));
    }
    else
    {
    pDescriptor->buffers[0].pWrapBuffer = NULL;
    }
    BDBG_LEAVE(BDSP_Raaga_P_Queue_GetBuffer);
    return errCode;
}

BERR_Code BDSP_Raaga_P_Queue_CommitData(
    void *pQueueHandle,
    size_t bytesWritten
    )
{
    BDSP_RaagaQueue *pRaagaQueue;
    BDSP_Raaga_P_MsgQueueHandle hMsgQueue;
    BERR_Code errCode=BERR_SUCCESS;
    BDSP_AF_P_sDRAM_CIRCULAR_BUFFER sCircBuff;
    uint32_t  ui32TempAddr = 0;
    uint32_t    ui32RegOffset = 0;
    BDBG_ENTER(BDSP_Raaga_P_Queue_CommitData);
    pRaagaQueue = (BDSP_RaagaQueue *)pQueueHandle;
    BDBG_OBJECT_ASSERT(pRaagaQueue, BDSP_RaagaQueue);
    hMsgQueue = pRaagaQueue->FIFOdata[0];

    if ( !pRaagaQueue->input )
    {
        return BERR_TRACE(BERR_NOT_SUPPORTED);
    }

    sCircBuff.ui32BaseAddr = BDSP_Read32(hMsgQueue->hRegister, hMsgQueue->ui32BaseAddr);
    sCircBuff.ui32EndAddr = BDSP_Read32(hMsgQueue->hRegister, hMsgQueue->ui32EndAddr);
    sCircBuff.ui32ReadAddr = BDSP_Read32(hMsgQueue->hRegister, hMsgQueue->ui32ReadAddr);
    sCircBuff.ui32WriteAddr = BDSP_Read32(hMsgQueue->hRegister, hMsgQueue->ui32WriteAddr);
    sCircBuff.ui32WrapAddr = BDSP_Read32(hMsgQueue->hRegister, hMsgQueue->ui32EndAddr); /* check logic for wrap in case of RDB buffers */

    ui32TempAddr = sCircBuff.ui32WriteAddr + bytesWritten;

    if (ui32TempAddr >=  sCircBuff.ui32EndAddr)  /* Check equality case */
    {
    ui32TempAddr = sCircBuff.ui32BaseAddr + (ui32TempAddr - sCircBuff.ui32EndAddr);
    }
    /* Now that we have the write address to be updated, we write it to the Write Register */
         ui32RegOffset = BCHP_RAAGA_DSP_FW_CFG_FIFO_1_BASE_ADDR - \
                    BCHP_RAAGA_DSP_FW_CFG_FIFO_0_BASE_ADDR;
    /* BDBG_ASSERT(hAncDataMsgQueue->i32FifoId == 0); */

    BDSP_Write32(
        hMsgQueue->hRegister,
        BCHP_RAAGA_DSP_FW_CFG_FIFO_0_BASE_ADDR +
            (ui32RegOffset * hMsgQueue->i32FifoId) +
            BDSP_RAAGA_P_FIFO_WRITE_OFFSET + hMsgQueue->ui32DspOffset,
        ui32TempAddr); /* Read Offset */

    BDBG_LEAVE(BDSP_Raaga_P_Queue_CommitData);
    return errCode;
}

BERR_Code BDSP_Raaga_P_Queue_ConsumeData(
    void *pQueueHandle,
    size_t readBytes
    )
{
    BDSP_RaagaQueue *pRaagaQueue;
    BDSP_Raaga_P_MsgQueueHandle hAncDataMsgQueue;
    BERR_Code errCode=BERR_SUCCESS;
    BDSP_AF_P_sDRAM_CIRCULAR_BUFFER sAncCircBuff;
    uint32_t  ui32TempAddr = 0;
    uint32_t    ui32RegOffset = 0;
    BDBG_ENTER(BDSP_Raaga_P_Queue_ConsumeData);
    pRaagaQueue = (BDSP_RaagaQueue *)pQueueHandle;
    BDBG_OBJECT_ASSERT(pRaagaQueue, BDSP_RaagaQueue);
    hAncDataMsgQueue = pRaagaQueue->FIFOdata[0];

    if ( pRaagaQueue->input )
    {
        return BERR_TRACE(BERR_NOT_SUPPORTED);
    }

    sAncCircBuff.ui32BaseAddr = BDSP_Read32(hAncDataMsgQueue->hRegister, hAncDataMsgQueue->ui32BaseAddr);
    sAncCircBuff.ui32EndAddr = BDSP_Read32(hAncDataMsgQueue->hRegister, hAncDataMsgQueue->ui32EndAddr);
    sAncCircBuff.ui32ReadAddr = BDSP_Read32(hAncDataMsgQueue->hRegister, hAncDataMsgQueue->ui32ReadAddr);
    sAncCircBuff.ui32WriteAddr = BDSP_Read32(hAncDataMsgQueue->hRegister, hAncDataMsgQueue->ui32WriteAddr);
    sAncCircBuff.ui32WrapAddr = BDSP_Read32(hAncDataMsgQueue->hRegister, hAncDataMsgQueue->ui32EndAddr); /* check logic for wrap in case of RDB buffers */

    ui32TempAddr = sAncCircBuff.ui32ReadAddr + readBytes;

    if (ui32TempAddr >=  sAncCircBuff.ui32EndAddr)  /* Check equality case */
    {
    ui32TempAddr = sAncCircBuff.ui32BaseAddr + (ui32TempAddr - sAncCircBuff.ui32EndAddr);
    }
    /* Now that we have the read address to be updated, we write it to the Read Register */
         ui32RegOffset = BCHP_RAAGA_DSP_FW_CFG_FIFO_1_BASE_ADDR - \
                    BCHP_RAAGA_DSP_FW_CFG_FIFO_0_BASE_ADDR;

    BDSP_Write32(
        hAncDataMsgQueue->hRegister,
        BCHP_RAAGA_DSP_FW_CFG_FIFO_0_BASE_ADDR +
            (ui32RegOffset * hAncDataMsgQueue->i32FifoId) +
            BDSP_RAAGA_P_FIFO_READ_OFFSET + hAncDataMsgQueue->ui32DspOffset,
        ui32TempAddr); /* Read Offset */

    BDBG_LEAVE(BDSP_Raaga_P_Queue_ConsumeData);
    return errCode;
}
/**************************************************************************
Name: BDSP_Raaga_P_InitDeviceSettings

Functionality: Initialize the device handle with settings related to the device before we
proceed with other funcitonalities in BDSP_Raaga_P_Open
***************************************************************************/

void BDSP_Raaga_P_InitDeviceSettings(void * pDeviceHandle)
{

    BDSP_Raaga *pRaaga = (BDSP_Raaga *)pDeviceHandle;
    unsigned dspIndex;
    unsigned lowerDspClkRate;
    BERR_Code err = BERR_SUCCESS;

    pRaaga->numDsp = BDSP_RAAGA_MAX_DSP;

    for (dspIndex=0 ; dspIndex < pRaaga->numDsp; dspIndex++)
    {
        err = BDSP_Raaga_P_GetDefaultClkRate(pDeviceHandle, dspIndex, &pRaaga->dpmInfo.defaultDspClkRate[dspIndex] );
        if( err == BERR_SUCCESS )
        {
            BDSP_Raaga_P_GetLowerDspClkRate(pRaaga->dpmInfo.defaultDspClkRate[dspIndex], &lowerDspClkRate);
            BDSP_Raaga_P_SetDspClkRate( pDeviceHandle, lowerDspClkRate, dspIndex );
            BDBG_MSG(("PWR: Dynamic frequency scaling enabled for DSP %d", dspIndex));
        }
        else
        {
            BDBG_MSG(("PWR: Dynamic frequency scaling not enabled for DSP %d", dspIndex));
        }
    }

    err = BDSP_Raaga_P_GetNumberOfDsp( pRaaga->boxHandle, &pRaaga->numDsp );
	if(err != BERR_SUCCESS)
	{
		BDBG_ERR(("INIT: Error in retreiving the Number of RAAGA DSP from BOX MODE, hence using the default value"));
	}

    for (dspIndex=0 ; dspIndex < pRaaga->numDsp; dspIndex++)
    {
#if defined BCHP_RAAGA_DSP_RGR_1_REG_START
        pRaaga->dspOffset[dspIndex] = dspIndex * (BCHP_RAAGA_DSP_RGR_1_REVISION - BCHP_RAAGA_DSP_RGR_REVISION);
#else
        pRaaga->dspOffset[dspIndex] = dspIndex * 0 /*(BCHP_RAAGA_DSP1_RGR_REVISION - BCHP_RAAGA_DSP0_RGR_REVISION)*/;
#endif
    }
    return;
}

/***************************************************************************
Summary:
Directs the raaga uart to Uart1 which is by default set for AVD uart. This function is dummy
by default. To enable this feature #define RAAGA_UART_ENABLE has to be uncommented in
bdsp_raaga.h
Supports chips 7231 and 7346.
***************************************************************************/
#ifdef RAAGA_UART_ENABLE
BERR_Code BDSP_Raaga_P_DirectRaagaUartToPort1(BREG_Handle regHandle)
{
    BERR_Code err=BERR_SUCCESS;

#if (BCHP_CHIP == 7445)
    unsigned int                regVal=0;

        regVal = BREG_Read32(regHandle, BCHP_SUN_TOP_CTRL_UART_ROUTER_SEL_0);
        regVal = (regVal & ~(BCHP_MASK(SUN_TOP_CTRL_UART_ROUTER_SEL_0, port_5_cpu_sel)))
                        | BCHP_FIELD_DATA(SUN_TOP_CTRL_UART_ROUTER_SEL_0, port_5_cpu_sel, BCHP_SUN_TOP_CTRL_UART_ROUTER_SEL_0_port_5_cpu_sel_AUDIO_FP0);
        BREG_Write32(regHandle, BCHP_SUN_TOP_CTRL_UART_ROUTER_SEL_0, regVal);
        regVal = BREG_Read32(regHandle, BCHP_SUN_TOP_CTRL_PIN_MUX_CTRL_12);
        regVal = (regVal & ~(BCHP_MASK(SUN_TOP_CTRL_PIN_MUX_CTRL_12, gpio_041)))
                        | BCHP_FIELD_DATA(SUN_TOP_CTRL_PIN_MUX_CTRL_12, gpio_041, 4);
        BREG_Write32(regHandle, BCHP_SUN_TOP_CTRL_PIN_MUX_CTRL_12, regVal);
        regVal = BREG_Read32(regHandle, BCHP_SUN_TOP_CTRL_PIN_MUX_CTRL_13);
        regVal = (regVal & ~(BCHP_MASK(SUN_TOP_CTRL_PIN_MUX_CTRL_13, gpio_042)))
                        | BCHP_FIELD_DATA(SUN_TOP_CTRL_PIN_MUX_CTRL_13, gpio_042, 4);
        BREG_Write32(regHandle, BCHP_SUN_TOP_CTRL_PIN_MUX_CTRL_13, regVal);

#elif (BCHP_CHIP == 7231)
        regVal = (regVal & ~(BCHP_MASK(SUN_TOP_CTRL_UART_ROUTER_SEL, port_1_cpu_sel)))
                        | BCHP_FIELD_DATA(SUN_TOP_CTRL_UART_ROUTER_SEL, port_1_cpu_sel, BCHP_SUN_TOP_CTRL_UART_ROUTER_SEL_port_1_cpu_sel_AUDIO_FP);
        BREG_Write32(regHandle, BCHP_SUN_TOP_CTRL_UART_ROUTER_SEL, regVal);

        regVal = BREG_Read32(regHandle, BCHP_SUN_TOP_CTRL_PIN_MUX_CTRL_11);
        regVal = (regVal & ~(BCHP_MASK(SUN_TOP_CTRL_PIN_MUX_CTRL_11, gpio_94)))
                        | BCHP_FIELD_DATA(SUN_TOP_CTRL_PIN_MUX_CTRL_11, gpio_94, 4);
        BREG_Write32(regHandle, BCHP_SUN_TOP_CTRL_PIN_MUX_CTRL_11, regVal);

        regVal = BREG_Read32(regHandle, BCHP_SUN_TOP_CTRL_PIN_MUX_CTRL_11);
        regVal = (regVal & ~(BCHP_MASK(SUN_TOP_CTRL_PIN_MUX_CTRL_11, gpio_95)))
                        | BCHP_FIELD_DATA(SUN_TOP_CTRL_PIN_MUX_CTRL_11, gpio_95, 5);
        BREG_Write32(regHandle, BCHP_SUN_TOP_CTRL_PIN_MUX_CTRL_11, regVal);
        /*
        BREG_Write32(hReg, BCHP_SUN_TOP_CTRL_TEST_PORT_CTRL, );
        */

#elif (BCHP_CHIP == 7346)

    unsigned int                regVal;
        regVal = BREG_Read32(regHandle, BCHP_SUN_TOP_CTRL_UART_ROUTER_SEL);
        regVal = (regVal & ~(BCHP_MASK(SUN_TOP_CTRL_UART_ROUTER_SEL, port_1_cpu_sel)))
                        | BCHP_FIELD_DATA(SUN_TOP_CTRL_UART_ROUTER_SEL, port_1_cpu_sel, BCHP_SUN_TOP_CTRL_UART_ROUTER_SEL_port_1_cpu_sel_AUDIO_FP);
        BREG_Write32(regHandle, BCHP_SUN_TOP_CTRL_UART_ROUTER_SEL, regVal);

        regVal = BREG_Read32(regHandle, BCHP_SUN_TOP_CTRL_PIN_MUX_CTRL_9);
        regVal = (regVal & ~(BCHP_MASK(SUN_TOP_CTRL_PIN_MUX_CTRL_9, gpio_018)))
                        | BCHP_FIELD_DATA(SUN_TOP_CTRL_PIN_MUX_CTRL_9, gpio_018, 5);
        BREG_Write32(regHandle, BCHP_SUN_TOP_CTRL_PIN_MUX_CTRL_9, regVal);

        regVal = BREG_Read32(regHandle, BCHP_SUN_TOP_CTRL_PIN_MUX_CTRL_9);
        regVal = (regVal & ~(BCHP_MASK(SUN_TOP_CTRL_PIN_MUX_CTRL_9, gpio_017)))
                        | BCHP_FIELD_DATA(SUN_TOP_CTRL_PIN_MUX_CTRL_9, gpio_017, 5);
        BREG_Write32(regHandle, BCHP_SUN_TOP_CTRL_PIN_MUX_CTRL_9, regVal);
        /*
        BREG_Write32(hReg, BCHP_SUN_TOP_CTRL_TEST_PORT_CTRL, );
        */
#else
        BSTD_UNUSED(regHandle);
#endif

    return err;
}
#endif
/***********************************************************************
Name        :   BDSP_Raaga_P_EnableAllPwrResource

Input       :   pDeviceHandle
                Enable/Disable

Function    :   Enable/Disable the power resources Raaga,Raaga_sram and
                DSP.

Return      :   void

***********************************************************************/
void BDSP_Raaga_P_EnableAllPwrResource(void *pDeviceHandle,
                                    bool bEnable)
{
    BDSP_Raaga *pDevice = pDeviceHandle;

    if( bEnable == true )
    {
        #ifdef  BCHP_PWR_RESOURCE_RAAGA0_SRAM
        BCHP_PWR_AcquireResource(pDevice->chpHandle, BCHP_PWR_RESOURCE_RAAGA0_SRAM);
        #endif
        #ifdef BCHP_PWR_RESOURCE_RAAGA1_SRAM
        BCHP_PWR_AcquireResource(pDevice->chpHandle, BCHP_PWR_RESOURCE_RAAGA1_SRAM);
        #endif
        #ifdef BCHP_PWR_RESOURCE_RAAGA0_CLK
        BCHP_PWR_AcquireResource(pDevice->chpHandle, BCHP_PWR_RESOURCE_RAAGA0_CLK);
        #else
        BSTD_UNUSED(pDevice);
        #endif
        #ifdef BCHP_PWR_RESOURCE_RAAGA1_CLK
        BCHP_PWR_AcquireResource(pDevice->chpHandle, BCHP_PWR_RESOURCE_RAAGA1_CLK);
        #endif
        #ifdef BCHP_PWR_RESOURCE_RAAGA0_DSP
        BCHP_PWR_AcquireResource(pDevice->chpHandle, BCHP_PWR_RESOURCE_RAAGA0_DSP);
        #endif
        #ifdef BCHP_PWR_RESOURCE_RAAGA1_DSP
        BCHP_PWR_AcquireResource(pDevice->chpHandle, BCHP_PWR_RESOURCE_RAAGA1_DSP);
        #endif
    }
    else
    {
        #ifdef  BCHP_PWR_RESOURCE_RAAGA0_SRAM
        BCHP_PWR_ReleaseResource(pDevice->chpHandle, BCHP_PWR_RESOURCE_RAAGA0_SRAM);
        #endif
        #ifdef BCHP_PWR_RESOURCE_RAAGA1_SRAM
        BCHP_PWR_ReleaseResource(pDevice->chpHandle, BCHP_PWR_RESOURCE_RAAGA1_SRAM);
        #endif
        #ifdef BCHP_PWR_RESOURCE_RAAGA0_CLK
        BCHP_PWR_ReleaseResource(pDevice->chpHandle, BCHP_PWR_RESOURCE_RAAGA0_CLK);
        #else
        BSTD_UNUSED(pDevice);
        #endif
        #ifdef BCHP_PWR_RESOURCE_RAAGA1_CLK
        BCHP_PWR_ReleaseResource(pDevice->chpHandle, BCHP_PWR_RESOURCE_RAAGA1_CLK);
        #endif
        #ifdef BCHP_PWR_RESOURCE_RAAGA0_DSP
        BCHP_PWR_ReleaseResource(pDevice->chpHandle, BCHP_PWR_RESOURCE_RAAGA0_DSP);
        #endif
        #ifdef BCHP_PWR_RESOURCE_RAAGA1_DSP
        BCHP_PWR_ReleaseResource(pDevice->chpHandle, BCHP_PWR_RESOURCE_RAAGA1_DSP);
        #endif
    }
}

/******************************************************************************
 * (c) 2006-2015 Broadcom Corporation
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


#ifndef BDSP_CONTEXT_H_
#define BDSP_CONTEXT_H_

#include "bchp.h"
#include "bint.h"
#include "bmem.h"
#include "breg_mem.h"
#include "btmr.h"
#include "bimg.h"
#include "bdsp.h"

/***************************************************************************
Summary:
DSP Audio Context Settings
***************************************************************************/
typedef struct BDSP_ContextCreateAudioSettings
{
    unsigned maxNumAudioDatasyncDownloadBuffer;
    unsigned maxNumAudioPassthruDownloadBuffer;
    unsigned maxNumAudioDecodeDownloadBuffer;
    unsigned maxNumAudioProcessingDownloadBuffer;
    unsigned maxNumAudioEncodeDownloadBuffer;
} BDSP_ContextCreateAudioSettings;

/***************************************************************************
Summary:
DSP Video Context Settings
***************************************************************************/
typedef struct BDSP_ContextCreateVideoSettings
{
    unsigned maxNumVideoDecodeDownloadBuffer;
} BDSP_ContextCreateVideoSettings;

/***************************************************************************
Summary:
DSP Video Encode Context Settings
***************************************************************************/
typedef struct BDSP_ContextCreateVideoEncodeSettings
{
    unsigned maxNumVideoEncodeDownloadBuffer;
} BDSP_ContextCreateVideoEncodeSettings;

typedef struct BDSP_ContextCreateScmSettings
{
    unsigned maxNumScmDecodeDownloadBuffer;
} BDSP_ContextCreateScmSettings;
typedef struct BDSP_ContextCreateSettings
{
    unsigned maxTasks;
    BDSP_ContextType    contextType;
    unsigned maxBranch;
    unsigned maxStagePerBranch;
} BDSP_ContextCreateSettings;

/***************************************************************************
Summary:
Get Default DSP Context Settings
***************************************************************************/
void BDSP_Context_GetDefaultCreateSettings(
    BDSP_Handle dsp,
    BDSP_ContextType contextType,
    BDSP_ContextCreateSettings *pSettings     /* [out] */
    );

/***************************************************************************
Summary:
Create a DSP context
***************************************************************************/
BERR_Code BDSP_Context_Create(
    BDSP_Handle dsp,
    const BDSP_ContextCreateSettings *pSettings,
    BDSP_ContextHandle *pContext    /* [out] */
    );

/***************************************************************************
Summary:
Destroy a DSP context
***************************************************************************/
void BDSP_Context_Destroy(
    BDSP_ContextHandle context
    );

/***************************************************************************
Summary:
Context Level Interrupts
***************************************************************************/
typedef struct BDSP_ContextInterruptHandlers
{
    struct
    {
        void (*pCallback_isr)(void *pParam1, int param2);
        void *pParam1;
        int param2;
    } watchdog;
} BDSP_ContextInterruptHandlers;

/***************************************************************************
Summary:
Get Currently Registered Interrupt Handlers
***************************************************************************/
void BDSP_Context_GetInterruptHandlers(
    BDSP_ContextHandle context,
    BDSP_ContextInterruptHandlers *pInterrupts     /* [out] */
    );

/***************************************************************************
Summary:
Set Interrupt Handlers

Description:
To disable any unwanted interrupt, pass NULL for its callback routine
***************************************************************************/
BERR_Code BDSP_Context_SetInterruptHandlers(
    BDSP_ContextHandle context,
    const BDSP_ContextInterruptHandlers *pInterrupts
    );

/***************************************************************************
Summary:
Process a watchdog interrupt for this context
***************************************************************************/
BERR_Code BDSP_Context_ProcessWatchdogInterrupt(
    BDSP_ContextHandle context
    );


/*BDSP_DataType  and BDSP_StageCreateSettings has gone into bdsp_types.h*/
#endif

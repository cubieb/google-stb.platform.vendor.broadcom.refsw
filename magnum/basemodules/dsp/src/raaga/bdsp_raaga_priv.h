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


#ifndef BDSP_RAAGA_PRIV_H_
#define BDSP_RAAGA_PRIV_H_

#include "bdsp.h"
#include "../src/bdsp_priv.h" /* FIXME: Remove the priv file dependency */
#include "bdsp_raaga.h"
#include "blst_slist.h"
#include "bdsp_raaga_img.h"
#include "bdsp_raaga_fw.h"
#include "bdsp_raaga_types.h"
#include "bdsp_raaga_fwinterface_priv.h"
#include "bdsp_raaga_mm_priv.h"
#include "bdsp_raaga_util.h"
#include "bdsp_audio_task.h"
#include "bdsp_raaga_cmdresp_priv.h"
#include "bdsp_raaga_fwdownload_priv.h"
#include "bdsp_raaga_fw_algo.h"
#include "bdsp_common_priv.h"


BDBG_OBJECT_ID_DECLARE(BDSP_Raaga);
BDBG_OBJECT_ID_DECLARE(BDSP_RaagaContext);
BDBG_OBJECT_ID_DECLARE(BDSP_RaagaTask);
BDBG_OBJECT_ID_DECLARE(BDSP_RaagaExternalInterrupt);
BDBG_OBJECT_ID_DECLARE(BDSP_RaagaRdbRegister);



#define BDSP_RAAGA_DSP_INDEX_INTERTASK              0

#define BDSP_RAAGA_PREBOOT_MAILBOX_PATTERN          0xA5A5
#define BDSP_RAAGA_DMA_BUSY                         1
#ifdef FIREPATH_BM
#define BDSP_RAAGA_DMA_TIMEOUT_COUNT                50000
#else
#define BDSP_RAAGA_DMA_TIMEOUT_COUNT                500
#endif
#define BDSP_RAAGA_DMA_SIZE_PER_TRANSFER            0xFFFF

#define BDSP_RAAGA_EVENT_TIMEOUT_IN_MS               400
#define BDSP_RAAGA_START_STOP_EVENT_TIMEOUT_IN_MS    400

/* SW7425-4031: Interrim HACK! To be removed once the bint.h support is available
                Added to address short term build problems */
#define BINT_GetCallbackStatus_isr BINT_GetCallbackStatus


/***** DSPCHN_PRIV_H*****/
/********* New Changes***************/


/* Inter-channel delay user param buffer size */
#define BDSP_RAAGA_DBG_BUF_SIZE     2*1024*1024

/* Number of extra FIFOS that can be used below the actual FIFO 0 */
#define BDSP_RAAGA_NUM_EXTRA_FIFOS      (uint32_t)0

#define BDSP_RAAGA_FIFO_0_INDEX         (int32_t)-BDSP_RAAGA_NUM_EXTRA_FIFOS

/*0-58 FIFO's and 59th is DramLogs, 60th is UART, 61st is Coredump and 62nd is TargetPrint*/
#define BDSP_RAAGA_DEBUG_FIFO_START_INDEX           59

/*total Fifo's available for tasks*//*+4 Include the Debug, UARt, coredump and Targetprint Fifo's also*/
#define BDSP_RAAGA_TOTAL_FIFOS          (BDSP_RAAGA_DEBUG_FIFO_START_INDEX + 4)
/* It should till the point where debug fifos start */
#define BDSP_RAAGA_NUM_FIFOS                (BDSP_RAAGA_TOTAL_FIFOS+BDSP_RAAGA_NUM_EXTRA_FIFOS)
/* Fifos actually needed for tasks */
#define BDSP_RAAGA_MAX_TASK_SUPPORTED       16
/* 2 FIFOs (Async and Sync Queues per task) */
#define BDSP_RAAGA_MAX_TASK_FIFO_REQUIRED   (2*BDSP_RAAGA_MAX_TASK_SUPPORTED)

#define BDSP_RAAGA_NUM_PTR_PER_FIFO     5

/* Hardcode cmd queue as FIFO 0 */
#define BDSP_RAAGA_FIFO_CMD     (BDSP_RAAGA_FIFO_0_INDEX+0)
/* Hardcode response queue which doesn't have any task id associated */
#define BDSP_RAAGA_FIFO_GENERIC_RSP     (BDSP_RAAGA_FIFO_0_INDEX+1)

#define BDSP_RAAGA_FIFO_DRAMLOGS        (BDSP_RAAGA_DEBUG_FIFO_START_INDEX+0)
#define BDSP_RAAGA_FIFO_UART            (BDSP_RAAGA_DEBUG_FIFO_START_INDEX+1)
#define BDSP_RAAGA_FIFO_COREDUMP        (BDSP_RAAGA_DEBUG_FIFO_START_INDEX+2)
#define BDSP_RAAGA_FIFO_TARGETPRINT     (BDSP_RAAGA_DEBUG_FIFO_START_INDEX+3)

#define BDSP_RAAGA_FIFO_INVALID         ((unsigned int)(-1))

#define BDSP_RAAGA_GET_TASK_INDEX(taskId) (taskId -BDSP_RAAGA_TASK_ID_START_OFFSET)

#define BDSP_RAAGA_INVALID_INDEX                    (unsigned int)-1

#define BDSP_RAAGA_DSP_P_FIFO_PDQ   15
#define BDSP_RAAGA_DSP_P_FIFO_PRQ   16
#define BDSP_RAAGA_DSP_P_FIFO_DSQ   14
#define BDSP_RAAGA_DSP_P_FIFO_CCDQ  14 /* Video encode and decode doesn't happen together so same ID for DSQ and CCDQ */


#define BDSP_RAAGA_MAX_INTERRUPTS_PER_DSP   32
#define BDSP_RAAGA_RDB_REGISTERS    15
#define BDSP_ENCODE_OUTPUT_CDB_FIFO     9
#define BDSP_ENCODE_OUTPUT_ITB_FIFO     10
#define BDSP_MAX_INTERTASKBUFFER_INPUT_TO_MIXER 3
#define BDSP_MAX_INTERTASKBUFFER_INPUT_TO_ECHOCANCELLER 1


#ifdef BDSP_FW_RBUF_CAPTURE
/* Specific to FW Ring Buffer capture required for their unit testing */
typedef enum BDSP_P_RbufType
{
    BDSP_P_RbufType_eDecode,
    BDSP_P_RbufType_ePassthru,
    BDSP_P_RbufType_eMixer,
    BDSP_P_RbufType_eEncoder,
    BDSP_P_RbufType_eTranscode,
    BDSP_P_RbufType_eSM
}BDSP_P_RbufType;

typedef struct BDSP_P_RbufCapture
{
    uint8_t (*rbuf_init)(BREG_Handle hRegister, BMEM_Handle hMem);
    uint8_t (*rbuf_uninit)(void);
    uint8_t (*rbuf_capture_channel_start)(uint32_t ui32Channel, uint32_t ui32Path, uint32_t ui32RbufId, BDSP_P_RbufType eRbufType);
    uint8_t (*rbuf_capture_stop_channel)(uint32_t ui32Channel, uint32_t ui32Path, uint32_t ui32RbufId, BDSP_P_RbufType eRbufType);

}BDSP_P_RbufCapture;

extern BDSP_P_RbufCapture Rbuf_Setting;

void BDSP_P_RbufSetup(
    BDSP_P_RbufCapture sRbufCap
);

#endif


/***************************************************************************
Summary:
    This structure is one to one mapping between Exec_Image_Id and the Exec_Id
    (BAF Ids) common between PI and FW. This will also contain the sizes of the
    Exec_image.
        Since for the Exec_Image_Id of Decode table, there is no Exec_Id, so it will store
    the if its already downloaded.

    Also interframeImgId stores the Image id of interframe Fw image for each ExecId.
***************************************************************************/
typedef struct BDSP_Raaga_P_ImgIdMappingArrays
{
    uint32_t    codeImgId[BDSP_AF_P_AlgoId_eMax];
    uint32_t    ui32CodeSize[BDSP_AF_P_AlgoId_eMax];
    uint32_t    tableImgId[BDSP_AF_P_AlgoId_eMax];
    uint32_t    tableSize[BDSP_AF_P_AlgoId_eMax];
    uint32_t    interframeImgId[BDSP_AF_P_AlgoId_eMax];
    uint32_t    interframeSize[BDSP_AF_P_AlgoId_eMax];
} BDSP_Raaga_P_ImgIdMappingArrays;

#define BDSP_RAAGA_ALIGN(x,alignbits)               (((x) + \
                                                 ((1 << (alignbits)) - 1)) & \
                                                 ~((1 << (alignbits)) - 1))

struct BDSP_RaagaTask;


typedef struct BDSP_Raaga_P_TaskInfo
{
    bool    taskId[BDSP_RAAGA_MAX_DSP][BDSP_RAAGA_MAX_FW_TASK_PER_DSP];
    struct BDSP_RaagaTask    *pRaagaTask[BDSP_RAAGA_MAX_DSP][BDSP_RAAGA_MAX_FW_TASK_PER_DSP];
    BKNI_MutexHandle taskIdMutex;
    unsigned numActiveTasks[BDSP_RAAGA_MAX_DSP];
}BDSP_Raaga_P_TaskInfo;


typedef struct BDSP_Raaga_P_DPM
{
    unsigned defaultDspClkRate[BDSP_RAAGA_MAX_DSP];
    unsigned dynFreqSclRefCnt[BDSP_RAAGA_MAX_DSP];
    bool bWatchdogTimerStatus;
}BDSP_Raaga_P_DPM;

typedef struct BDSP_Raaga
{
    BDBG_OBJECT(BDSP_Raaga)
    BDSP_Device device;
    BDSP_RaagaSettings settings;
    BCHP_Handle chpHandle;
    BREG_Handle regHandle;
    BMEM_Handle memHandle;
    BINT_Handle intHandle;
    BBOX_Handle boxHandle;
    uint32_t dspOffset[BDSP_RAAGA_MAX_DSP];
    BINT_CallbackHandle     ackCallbackHandle[BDSP_RAAGA_MAX_DSP];    /* This will install the Callback for Ping the DSp*/
    BDSP_Raaga_P_DPM dpmInfo;

    void *pFwHeapMemory;
    size_t fwHeapSize;
    BMEM_ModuleHandle hFwMemModule;
    BMEM_Handle hFwHeap;
    BDSP_RaagaImgCacheEntry imgCache[BDSP_IMG_ID_MAX];
    BDSP_Raaga_P_MemoryGrant memInfo;

    BDSP_Raaga_P_TaskInfo taskDetails;
    unsigned numDsp;

    bool dspFifo[BDSP_RAAGA_MAX_DSP][BDSP_RAAGA_NUM_FIFOS];
    BKNI_MutexHandle fifoIdMutex[BDSP_RAAGA_MAX_DSP];
    BKNI_MutexHandle    watchdogMutex;
    BDSP_Raaga_P_MsgQueueHandle      hCmdQueue[BDSP_RAAGA_MAX_DSP];      /* Cmd queue handle*/
    BDSP_Raaga_P_MsgQueueHandle      hGenRspQueue[BDSP_RAAGA_MAX_DSP];      /* Generic Response queue handle*/
    BINT_CallbackHandle             hWatchdogCallback[BDSP_RAAGA_MAX_DSP];
    bool                    deviceWatchdogFlag;
    BLST_S_HEAD(BDSP_RaagaContextList, BDSP_RaagaContext) contextList;
    bool    powerStandby;/*True if DSP is in standby*/
    bool                        dspInterrupts[BDSP_RAAGA_MAX_DSP][BDSP_RAAGA_MAX_INTERRUPTS_PER_DSP];
    BKNI_MutexHandle            dspInterruptMutex[BDSP_RAAGA_MAX_DSP];
    BLST_S_HEAD(BDSP_RaagaExtInterruptList, BDSP_RaagaExternalInterrupt) interruptList;
    /* Rdb register handle */
    bool                        rdbRegisters[BDSP_RAAGA_MAX_DSP][BDSP_RAAGA_RDB_REGISTERS];
    BKNI_MutexHandle            rdbRegistersMutex[BDSP_RAAGA_MAX_DSP];
    BLST_S_HEAD(BDSP_RaagaRdbRegisterList, BDSP_RaagaRdbRegister) rdbRegisterList;
    BKNI_MutexHandle            captureMutex;

}BDSP_Raaga;

/* Handle for External interrupt to DSP */
typedef struct BDSP_RaagaRdbRegister
{
    BDBG_OBJECT(BDSP_RaagaRdbRegister)
    BDSP_RdbRegister    rdbRegister;
    struct BDSP_Raaga *pDevice;
    BLST_S_ENTRY(BDSP_RaagaRdbRegister) node;
    uint32_t    dspIndex;
    uint32_t    numRegisters;
    uint32_t    startIndex;
    BDSP_RdbRegisterInfo RdbRegisterInfo;
}BDSP_RaagaRdbRegister;


/* Handle for External interrupt to DSP */
typedef struct BDSP_RaagaExternalInterrupt
{
    BDBG_OBJECT(BDSP_RaagaExternalInterrupt)
    BDSP_ExternalInterrupt  extInterrupt;
    struct BDSP_Raaga *pDevice;
    BLST_S_ENTRY(BDSP_RaagaExternalInterrupt) node;
    uint32_t    dspIndex;
    BDSP_ExternalInterruptInfo InterruptInfo;
}BDSP_RaagaExternalInterrupt;


typedef struct BDSP_RaagaContext
{
    BDBG_OBJECT(BDSP_RaagaContext)
    BDSP_Context context;
    struct BDSP_Raaga *pDevice;
    BDSP_ContextCreateSettings settings;
    BDSP_ContextInterruptHandlers interruptHandlers;
    BLST_S_ENTRY(BDSP_RaagaContext) node;
    BLST_S_HEAD(BDSP_RaagaAllocTaskList, BDSP_RaagaTask) allocTaskList;
    BLST_S_HEAD(BDSP_RaagaFreeTaskList, BDSP_RaagaTask) freeTaskList;
    BDSP_Raaga_P_ContextMemoryGrant  contextMemInfo;
    bool                    contextWatchdogFlag;
    /* TODO: More context-level info */
}BDSP_RaagaContext;

typedef struct BDSP_Raaga_P_TaskCallBacks
{
    BINT_CallbackHandle     hDSPAsync[BDSP_RAAGA_MAX_DSP];
                                    /* DSP Async Interrupt callback */
    BINT_CallbackHandle     hDSPSync[BDSP_RAAGA_MAX_DSP];
                                    /* DSP SYNC interrupt callback */
}BDSP_Raaga_P_TaskCallBacks;

 typedef struct BDSP_RaagaTask
{
    BDBG_OBJECT(BDSP_RaagaTask)
    BDSP_Task task;
    struct BDSP_RaagaContext *pContext;
    BDSP_TaskCreateSettings settings;
    BDSP_TaskStartSettings startSettings;

    BDSP_AudioInterruptHandlers audioInterruptHandlers;
    bool allocated;
    BLST_S_ENTRY(BDSP_RaagaTask) node;
    unsigned int    taskId;
    BDSP_CIT_P_Output   citOutput;
    BDSP_CIT_P_VideoCITOutput   videoCitOutput;
    BDSP_CIT_P_ScmCITOutput   scmCitOutput;
    BDSP_Raaga_P_MsgQueueHandle hAsyncMsgQueue; /* Asynchronous message queue
                                                belonging to this task */
    BDSP_Raaga_P_MsgQueueHandle hSyncMsgQueue; /* Synchronous message queue
                                               belonging to this task */
    bool isStopped;  /* TRUE : If the stop command for this task has been sent,
                                                But the Processing of stop is still under process. Keep it in true state untill the hDspCh is started*/
    unsigned int lastEventType;
    unsigned int    masterTaskId;
    BKNI_EventHandle hEvent;
    BDSP_Raaga_P_TaskCallBacks    interruptCallbacks;
    unsigned commandCounter;
    BDSP_CTB_Output ctbOutput;
    bool    decLocked;
    bool    paused;
    BDSP_Raaga_P_TaskMemoryInfo taskMemGrants;                  /* Memory for contiguous Async Msgs */
    uint32_t        eventEnabledMask;  /* Contains information abt. event ids already enabled */
    BDSP_TaskSchedulingMode schedulingMode;
    void                                *pFeedbackBuffer;               /* Feedback buffer between Tasks(Master writes-Slaves read) */
    BDSP_Raaga_P_MsgQueueHandle      hPDQueue;      /* Picture Delivery queue(PDQ)*/
    BDSP_Raaga_P_MsgQueueHandle      hPRQueue;      /* Picture Release queue(PRQ)*/
    BDSP_Raaga_P_MsgQueueHandle      hDSQueue;      /* Display queue(DSQ)*/
    /* Handles for video encoder queue's */
    BDSP_Raaga_P_MsgQueueHandle      hRDQueue;      /* Raw Picture Delivery queue(RDQ)*/
    BDSP_Raaga_P_MsgQueueHandle      hRRQueue;      /* Raw Picture Release queue(RRQ)*/
    BDSP_Raaga_P_MsgQueueHandle      hCCDQueue;     /* CC data queue(CCDQ)*/
/* PAUSE-UNPAUSE */
    bool frozen;
/* PAUSE-UNPAUSE */
} BDSP_RaagaTask;

/***************************************************************************
Summary:
Capture pointers structure
***************************************************************************/
typedef struct BDSP_RaagaCapturePointerInfo
{
    BDSP_AF_P_sDRAM_CIRCULAR_BUFFER outputBufferPtr; /* Structure containing pointers to the output buffers
                                                   from which the data has to be captured */
    uint32_t    ui32StartWriteAddr;

    BDSP_AF_P_CIRCULAR_BUFFER captureBufferPtr; /* Structure containing the pointers to the intermediate
                                                    buffer into which the captured data is written */
    uint32_t shadowRead; /* The shadow read pointer for the output buffer */
    uint32_t lastWrite; /* The last value of the write pointer; will be used for capture error detection*/
} BDSP_RaagaCapturePointerInfo;

struct BDSP_RaagaStage;

BDBG_OBJECT_ID_DECLARE(BDSP_RaagaCapture);

typedef struct BDSP_RaagaCapture
{
    BDBG_OBJECT(BDSP_RaagaCapture)
    BDSP_AudioCapture    capture;
    struct BDSP_RaagaStage *pStage;
    BDSP_Raaga      *pDevice;

    BLST_S_ENTRY(BDSP_RaagaCapture) node;

    BMEM_Handle     hHeap; /* Heap from which the capture buffers need to be allocated */

    BDSP_AF_P_BufferType eBuffType; /* The buffer type of the the output buffer (RAVE, FMM, DRAM etc ...) */
    bool updateRead; /* If true then the read pointers of the output buffer are updated in the capture
                          thread. This can be set to true when there is not consumer for the output data */
    bool enabled; /* Flag to indicate whether the capture is enabled or disabled */
    uint8_t numBuffers; /* Number of valid buffers */
    uint8_t maxBuffers; /* Maximum number of buffers */

    bool StartCapture;

    BDSP_RaagaCapturePointerInfo capPtrs[BDSP_AF_P_MAX_CHANNELS]; /* Capture pointer info for all the output capture ports */
} BDSP_RaagaCapture;

typedef struct BDSP_AlgoBufferOffsets
{
    uint32_t ui32IfOffset;      /* Offset to the interframe buffer */
    uint32_t ui32UserCfgOffset; /* Offset to the user config buffer */
    uint32_t ui32StatusOffset;  /* Offset to the status buffer */
}BDSP_AlgoBufferOffsets;

 BDBG_OBJECT_ID_DECLARE(BDSP_RaagaStage);

typedef struct BDSP_AF_P_sDRAM_BUFFER_isr
{
    raaga_dramaddr              ui32DramBufferAddress;
    uint32_t                    ui32BufferSizeInBytes;
    void                       *pDramBufferAddress;
}BDSP_AF_P_sDRAM_BUFFER_isr;

typedef struct BDSP_RaagaStage
{
    BDBG_OBJECT(BDSP_RaagaStage)
    BDSP_Stage stage;

    BDSP_RaagaContext *pContext; /*this is NULL during stage create and connections. Enabled during the Task Start time only*/

    /* task handle will only be valid when the stage is in use */
    BDSP_RaagaTask *pRaagaTask;

    BDSP_Algorithm algorithm;
    BDSP_StageCreateSettings settings;

    unsigned ui32StageId;/*stage ID in for this branch id; can be used for filling in node network*/
    unsigned ui32BranchId;/*stores the branch information during traversing; can be used for filling in node network*/

    /*Alloc these buffers during Stage create*/
    BDSP_AF_P_sDRAM_BUFFER_isr   sDramUserConfigBuffer;
    BDSP_AF_P_sDRAM_BUFFER   sDramInterFrameBuffer;
    BDSP_AF_P_sDRAM_BUFFER_isr   sDramStatusBuffer;

    /* The offsets to the interframe, status and user cfg buffer for the framsync node */
    BDSP_AlgoBufferOffsets   sFrameSyncOffset;

    /* Extra buffer to on-the-fly program cfg params */
    BDSP_AF_P_sDRAM_BUFFER_isr   sDramUserConfigSpareBuffer;

    unsigned                     totalInputs;
    unsigned                     totalOutputs; /* Outputs of any type */
    unsigned                     numOutputs[BDSP_ConnectionType_eMax]; /* Outputs of each particular type */
    unsigned                     numInputs[BDSP_ConnectionType_eMax]; /* Inputs of each particular type */

    BDSP_StageSrcDstDetails      sStageInput[BDSP_AF_P_MAX_IP_FORKS];
    BDSP_StageSrcDstDetails      sStageOutput[BDSP_AF_P_MAX_OP_FORKS];
    BDSP_StageSrcDstDetails      sIdsStageOutput;

    BDSP_AF_P_DistinctOpType     eStageOpBuffDataType[BDSP_AF_P_MAX_OP_FORKS];

    /*uint32_t StageMemReq;*/
    BDSP_Raaga_P_StageMemoryReqd  stageMemInfo;

    bool running; /* Flag to indicate if the stage is a part of running task */

    /* Capture information for the stage */
    BLST_S_HEAD(BDSP_RaagaCaptureList, BDSP_RaagaCapture) captureList;

    /* TODO: More context-level info */
}BDSP_RaagaStage;

BDBG_OBJECT_ID_DECLARE(BDSP_RaagaQueue);
typedef struct BDSP_RaagaQueue
{
    BDBG_OBJECT(BDSP_RaagaQueue)
    BDSP_Queue Queue;

    BDSP_RaagaContext  *pRaagaContext;

    bool inUse; /* Flag to indicate if the Queue is in use */
    bool input; /* True if the queue is for host input */
    BDSP_DataType dataType; /* Type of data in the Queue */
    unsigned      numChans; /* Number of channels in the Queue */
    BDSP_AF_P_DistinctOpType distinctOp; /* Distinct output type of the Queue */
    unsigned      numBuf;
    BDSP_Raaga_P_MsgQueueHandle FIFOdata[BDSP_AF_P_MAX_CHANNELS];
    BDSP_RaagaStage *srcHandle; /* Source Stage handle */
    BDSP_RaagaStage *dstHandle; /* Destination Stage Handle */
    int32_t    srcIndex; /* Index of the src Stage output to which the Queue is connected */
    int32_t    dstIndex; /* Index of the dst Stage input to which theQueue is conneceted */
    unsigned   dspIndex; /* Index of DSP on which the Queue is created */
} BDSP_RaagaQueue;

 BDBG_OBJECT_ID_DECLARE(BDSP_RaagaTaskStageInput);

 typedef struct BDSP_RaagaTaskStageInput
 {
    BDBG_OBJECT(BDSP_RaagaTaskStageInput)
    BDSP_TaskStageInput        stageInput;
    unsigned branchId;
    unsigned stageId;
    BDSP_CIT_P_FwStgSrcDstType      inputType;      /* input type */
    unsigned inputIndex;
    BDSP_AF_P_sIO_BUFFER  *pIoBuffer;
    BDSP_AF_P_sIO_GENERIC_BUFFER *pIoGenericBuffer;
 }BDSP_RaagaTaskStageInput;

void BDSP_Raaga_P_Close(
    void *pDeviceHandle);

void BDSP_Raaga_P_GetDefaultContextSettings(
    void *pDeviceHandle,
    BDSP_ContextType contextType,
    BDSP_ContextCreateSettings *pSettings);

BERR_Code BDSP_Stage_Create(
BDSP_ContextHandle hContext,
const BDSP_StageCreateSettings *pSettings,
BDSP_StageHandle *pHandle /* [out] */
);

BERR_Code BDSP_Raaga_P_CreateContext(
    void *pDeviceHandle,
    const BDSP_ContextCreateSettings *pSettings,
    BDSP_ContextHandle *pContextHandle);

void BDSP_Raaga_P_GetStatus(
    void *pDeviceHandle,
    BDSP_Status *pStatus);

void BDSP_Raaga_P_DestroyContext(
    void *pContextHandle);

void BDSP_Raaga_P_GetDefaultTaskSettings(
    void *pContextHandle,
    BDSP_TaskCreateSettings *pSettings);

BERR_Code BDSP_Raaga_P_CreateTask(
    void *pContextHandle,
    const BDSP_TaskCreateSettings *pSettings,
    BDSP_TaskHandle *pTask);

BERR_Code BDSP_Raaga_P_GetMemoryEstimate(
    const BDSP_RaagaSettings     *pSettings,
    const BDSP_RaagaUsageOptions *pUsage,
    BBOX_Handle                   boxHandle,
    BDSP_RaagaMemoryEstimate     *pEstimate /*[out]*/
);

void BDSP_Raaga_P_EnableAllPwrResource(
    void *pDeviceHandle,
    bool bEnable);

BERR_Code BDSP_Raaga_P_Open(
    void *pDeviceHandle);

void BDSP_Raaga_P_DestroyTask(
    void *pTaskHandle);

BERR_Code BDSP_Raaga_P_StartTask(
    void *pTaskHandle,
    BDSP_TaskStartSettings *pStartSettings);

BERR_Code BDSP_Raaga_P_StopTask(
    void *pTaskHandle);

BERR_Code BDSP_Raaga_P_PopulateGateOpenFMMStages(
    void *pPrimaryStageHandle,
    BDSP_AF_P_TASK_sFMM_GATE_OPEN_CONFIG *sTaskFmmGateOpenConfig,
    uint32_t ui32MaxIndepDelay
    );

BERR_Code BDSP_Raaga_P_RetrieveGateOpenSettings(
    void *pTaskHandle,
    BDSP_TaskGateOpenSettings *pSettings   /* [out] */
    );

void BDSP_Raaga_P_GetDefaultTaskStartSettings(
    void *pTaskHandle,
    BDSP_TaskStartSettings *pSettings    /* [out] */
    );

void BDSP_Raaga_GetAlgorithmDefaultSettings(
    void *pDeviceHandle,
    BDSP_Algorithm algorithm,
    void *pSettingsBuffer,        /* [out] */
    size_t settingsBufferSize
    );

BERR_Code BDSP_Raaga_P_SetAlgorithm(
    void *pStageHandle,
    BDSP_Algorithm algorithm
    );

BERR_Code BDSP_Raaga_P_GetFWSize(
    const BIMG_Interface *iface,
    void *context,
    unsigned firmware_id,
    uint32_t *size
    );

void BDSP_Raaga_P_GetDefaultStageCreateSettings(
    BDSP_AlgorithmType algoType,
    BDSP_StageCreateSettings *pSettings /* [out] */
    );

BERR_Code BDSP_Raaga_P_CreateStage(
    void *pContextHandle,
    const BDSP_StageCreateSettings *pSettings,
    BDSP_StageHandle *pStageHandle /* [out] */
    );

void BDSP_Raaga_P_DestroyStage(
    void *pStageHandle
    );

BERR_Code BDSP_Raaga_P_GetStageSettings(
    void *pStageHandle,
    void *pSettingsBuffer,
    size_t settingsSize);

BERR_Code BDSP_Raaga_P_SetStageSettings(
    void *pStageHandle,
    const void *pSettingsBuffer,
    size_t settingsSize);

/* Stage specific apis */
BERR_Code BDSP_Raaga_P_AddRaveInput(
    void *pStageHandle,
    const BAVC_XptContextMap *pContextMap,
    unsigned *pInputIndex
    );

BERR_Code BDSP_Raaga_P_AddFmmOutput(
    void *pStageHandle,
    BDSP_DataType dataType,
    const BDSP_FmmBufferDescriptor *pDescriptor,
    unsigned *pOutputIndex);

BERR_Code BDSP_Raaga_P_AddRaveOutput(
    void *pStageHandle,
    const BAVC_XptContextMap *pContext,
    unsigned *pOutputIndex /* [out] */
    );

void BDSP_Raaga_P_RemoveOutput(
    void *pStageHandle,
    unsigned outputIndex);

void BDSP_Raaga_P_GetFreeInputPortIndex(
    BDSP_RaagaStage *pStage,
    unsigned *index);

void BDSP_Raaga_P_GetFreeOutputPortIndex(
    BDSP_RaagaStage *pStage,
    unsigned *index);

BERR_Code BDSP_Raaga_P_AddOutputStage(
    void *pSrcStageHandle,
    BDSP_DataType dataType,
    void *pDstStageHandle,
    unsigned *pSourceOutputIndex,
    unsigned *pDestinationInputIndex
    );

void BDSP_Raaga_P_RemoveAllOutputs(
    void *pStageHandle);

BERR_Code BDSP_Raaga_P_AddFmmInput(
    void *pStageHandle,
    BDSP_DataType dataType,
    const BDSP_FmmBufferDescriptor *pDescriptor,
    unsigned *pOutputIndex);

void BDSP_Raaga_P_RemoveInput(
    void *pStageHandle,
    unsigned inputIndex);

void BDSP_Raaga_P_RemoveAllInputs(
    void *pStageHandle);

BERR_Code BDSP_Raaga_P_AddInterTaskBufferInput(
    void *pStageHandle,
    BDSP_DataType dataType,
    const BDSP_InterTaskBuffer *pBufferHandle,
    unsigned *pInputIndex);

BERR_Code BDSP_Raaga_P_AddInterTaskBufferOutput(
    void *pStageHandle,
    BDSP_DataType dataType,
    const BDSP_InterTaskBuffer *pBufferHandle,
    unsigned *pOutputIndex);

BERR_Code BDSP_Raaga_P_SendCitReconfigCommand(
    BDSP_RaagaTask *pRaagaTask,
    BDSP_AF_P_sTASK_CONFIG  *psWorkingTaskCitBuffAddr
    );

BERR_Code BDSP_Raaga_P_GetDatasyncSettings(
    void *pStageHandle,
    BDSP_AudioTaskDatasyncSettings *pSettings);

BERR_Code BDSP_Raaga_P_SetDatasyncSettings(
    void *pStageHandle,
    const BDSP_AudioTaskDatasyncSettings *pSettings);

BERR_Code BDSP_Raaga_P_GetDatasyncSettings_isr(
    void *pStageHandle,
    BDSP_AudioTaskDatasyncSettings *pSettings);

BERR_Code BDSP_Raaga_P_SetDatasyncSettings_isr(
    void *pStageHandle,
    const BDSP_AudioTaskDatasyncSettings *pSettings);
BERR_Code BDSP_Raaga_P_GetVideoEncodeDatasyncSettings(
    void *pStageHandle,
    BDSP_VideoEncodeTaskDatasyncSettings *pSettings);

BERR_Code BDSP_Raaga_P_SetVideoEncodeDatasyncSettings(
    void *pStageHandle,
    const BDSP_VideoEncodeTaskDatasyncSettings *pSettings);

BERR_Code BDSP_Raaga_P_GetVideoEncodeDatasyncSettings_isr(
    void *pStageHandle,
    BDSP_VideoEncodeTaskDatasyncSettings *pSettings);

BERR_Code BDSP_Raaga_P_SetVideoEncodeDatasyncSettings_isr(
    void *pStageHandle,
    const BDSP_VideoEncodeTaskDatasyncSettings *pSettings);

BERR_Code BDSP_Raaga_P_GetDefaultCreateQueueSettings(
                                    void                     *pContextHandle,
                                    BDSP_QueueCreateSettings *pSettings);

BERR_Code BDSP_Raaga_P_Queue_Create( void *pContextHandle,
                                           unsigned dspIndex,
                                           BDSP_QueueCreateSettings *pSettings,
                                           BDSP_QueueHandle *pQueueHandle);

void BDSP_Raaga_P_Queue_Destroy( void *pQueueHandle );

void BDSP_Raaga_P_Queue_Flush( void *pQueueHandle );

void BDSP_Raaga_P_Queue_GetIoBuffer( void *pQueueHandle, BDSP_AF_P_sIO_BUFFER *pBuffer /*[out]*/);

BERR_Code BDSP_Raaga_P_Queue_GetBuffer( void *pQueueHandle, BDSP_BufferDescriptor *pDescriptor /*[out] */);

BERR_Code BDSP_Raaga_P_Queue_ConsumeData( void *pQueueHandle, size_t readBytes );

BERR_Code BDSP_Raaga_P_Queue_CommitData( void *pQueueHandle, size_t bytesWritten );

BERR_Code BDSP_Raaga_P_Queue_GetBufferAddr(void *pQueueHandle, unsigned numbuffers, void *pBuffer /*[out] */);

BERR_Code BDSP_Raaga_P_AddQueueInput(
                                    void     *pStageHandle,
                                    void     *pQueueHandle,
                                    unsigned *pInputIndex /* [out] */
                                    );


BERR_Code BDSP_Raaga_P_AddQueueOutput(
                                    void     *pStageHandle,
                                    void     *pQueueHandle,
                                    unsigned *pOutputIndex /* [out] */
                                    );
BERR_Code BDSP_Raaga_P_CreateMsgQueueHandle(
                                    BDSP_Raaga_P_MsgQueueParams     *psMsgQueueParams,  /* [in]*/
                                    BMEM_Handle                      hHeap,             /* [in] */
                                    BREG_Handle                      hRegister,         /* [in] */
                                    uint32_t                         ui32DspOffset,     /* [in] */
                                    BDSP_Raaga_P_MsgQueueHandle     *hMsgQueue,         /* [out]*/
                                    bool                             bWdgRecovery       /* [in] */
                                    );

BERR_Code BDSP_Raaga_P_SetTsmSettings_isr(
    void *pStageHandle,
    const BDSP_AudioTaskTsmSettings *pSettings);

BERR_Code BDSP_Raaga_P_GetTsmSettings_isr(
    void *pStageHandle,
    BDSP_AudioTaskTsmSettings    *pSettings);

BERR_Code BDSP_Raaga_P_GetStageStatus(
    void *pStageHandle,
    void *pStatusBuffer,
    size_t statusSize);

BERR_Code BDSP_Raaga_P_GetTsmStatus_isr(
    void *pStageHandle,
    BDSP_AudioTaskTsmStatus *pStatusBuffer);

BERR_Code BDSP_Raaga_P_GetDatasyncStatus_isr(
    void *pStageHandle,
    BDSP_AudioTaskDatasyncStatus *pStatusBuffer);

BERR_Code BDSP_Raaga_P_Pause(
    void *pTaskHandle);

BERR_Code BDSP_Raaga_P_Resume(
    void *pTaskHandle);

BERR_Code BDSP_Raaga_P_Advance(
    void *pTaskHandle,
    unsigned ms);

BERR_Code BDSP_Raaga_P_LoadScm(
    void *pDeviceHandle,
    unsigned uiDspIndex,
    unsigned uiScmIndex);

BERR_Code BDSP_Raaga_P_GetPictureCount_isr(
    void *pTaskHandle,
    unsigned *pPictureCount);

BERR_Code BDSP_Raaga_P_PeekAtPicture_isr(
    void *pTaskHandle,
    unsigned index,
    uint32_t **pUnifiedPicture);

BERR_Code BDSP_Raaga_P_GetNextPicture_isr(
    void *pTaskHandle,
    uint32_t **pUnifiedPicture);

BERR_Code BDSP_Raaga_P_ReleasePicture_isr(
    void *pTaskHandle,
    uint32_t *pUnifiedPicture);

BERR_Code BDSP_Raaga_P_GetPictureDropPendingCount_isr(
    void *pTaskHandle,
    unsigned *pPictureDropPendingCount);
BERR_Code BDSP_Raaga_P_RequestPictureDrop_isr(
    void *pTaskHandle,
    unsigned *pPictureDropRequestCount);

BERR_Code BDSP_Raaga_P_InputPictureBufferCount_isr(
    void *pTaskHandle,
    uint32_t *pPictureBuffAvail);

BERR_Code BDSP_Raaga_P_GetPictureBuffer_isr(
    void *pTaskHandle,
    raaga_dramaddr *pPictureParmBuf);

BERR_Code BDSP_Raaga_P_PutPicture_isr(
    void        *pTaskHandle,
    raaga_dramaddr pPPBAddress
    );

BERR_Code BDSP_Raaga_P_Put_CC_Data_isr(
    void    *pTask,
    void    *pCCDAddress
    );

BERR_Code BDSP_Raaga_P_DisplayInterruptEvent_isr(
    void *pTaskHandle);
BERR_Code BDSP_Raaga_P_PowerStandby(
    void *pDeviceHandle,
    BDSP_StandbySettings    *pSettings);
BERR_Code BDSP_Raaga_P_PowerResume(
    void *pDeviceHandle);

BERR_Code BDSP_Raaga_P_ResetRaagaCore(
   void *pDeviceHandle,
   uint32_t ui32DspIndex);

BERR_Code BDSP_Raaga_P_ResetRaagaCore_isr(
   void *pDeviceHandle,
   uint32_t ui32DspIndex);

uint32_t BDSP_Raaga_P_ResetHardware(
    void *pDeviceHandle,
   uint32_t ui32DspIndex);


uint32_t BDSP_Raaga_P_ResetHardware_isr(
   void *pDeviceHandle,
   uint32_t ui32DspIndex);

void BDSP_Raaga_P_Reset(
    void *pDeviceHandle
    );

BERR_Code BDSP_Raaga_P_Boot(
    void *pDeviceHandle
    );

BERR_Code BDSP_Raaga_P_SetupDspBoot(
    void *pDeviceHandle,
    uint32_t ui32DspIndex
    );


uint32_t BDSP_Raaga_P_RestoreInterrupts(
   void *pDeviceHandle,
   uint32_t ui32DspIndex);


uint32_t BDSP_Raaga_P_RestoreInterrupts_isr(
   void *pDeviceHandle,
   uint32_t ui32DspIndex);


void BDSP_Raaga_P_GetAlgorithmInfo(
    BDSP_Algorithm algorithm,
    BDSP_AlgorithmInfo *pInfo /* [out] */
    );

BERR_Code BDSP_Raaga_P_SendScmCommand(
    void *pTaskHandle,
    BDSP_Raaga_P_SCM_CmdPayload *pScmCmdPayload
    );

BERR_Code BDSP_Raaga_P_AudioGapFill(
    void *pTaskHandle
    );

BERR_Code BDSP_Raaga_P_AllocateExternalInterrupt(
    void        *pDeviceHandle, /* in */
    uint32_t    dspIndex, /* in */
    BDSP_ExternalInterruptHandle *pInterruptHandle  /* out */
    );

BERR_Code BDSP_Raaga_P_FreeExternalInterrupt(
    void *pInterruptHandle
    );

BERR_Code BDSP_Raaga_P_GetExternalInterruptInfo(
    void *pInterruptHandle,
    BDSP_ExternalInterruptInfo **pInfo
    );

BERR_Code BDSP_Raaga_P_AllocateRdbRegisters(
    void *pDeviceHandle,
    uint32_t dspIndex,
    uint32_t numRegs,
    BDSP_RdbRegisterHandle *pRdbRegisterHandle /* out */
    );

BERR_Code BDSP_Raaga_P_FreeRdbRegisters(
    void  *pRdbRegisterHandle
    );

BERR_Code BDSP_Raaga_P_GetRdbRegistersInfo(
    void *pRdbRegisterHandle,
    BDSP_RdbRegisterInfo **pInfo    /* out */
    );

BERR_Code BDSP_Raaga_P_InitAudioCaptureInfo(
    BDSP_RaagaCapture *pRaagaCapture, /* [in] capture handle*/
    const BDSP_AudioCaptureCreateSettings *pSettings /* [in] capture create settings */
    );


BERR_Code BDSP_Raaga_P_GetAudioOutputPointers(
    BDSP_StageSrcDstDetails *pDstDetails, /* [in] Desination details of the output port to be captured */
    BDSP_RaagaCapture *pRaagaCap /* [out] Capture Handle */
    );

BERR_Code BDSP_Raaga_P_AudioCaptureCreate(
    void *pTaskHandle,
    const BDSP_AudioCaptureCreateSettings *pCaptureCreateSettings,
    BDSP_AudioCaptureHandle *pCapture);

void BDSP_Raaga_P_AudioCaptureDestroy (
    void *pCapHandle
    );

BERR_Code BDSP_Raaga_P_AudioCaptureAddToStage(
    void *pCapHandle,
    void *pStageHandle,
    unsigned outputId,
    const BDSP_StageAudioCaptureSettings *pSettings
    );

void BDSP_Raaga_P_AudioCaptureRemoveFromStage(
    void *pCapHandle,
    void *pStageHandle
    );

/***************************************************************************
Summary:
Function to copy data from output buffer to intermediate buffers
***************************************************************************/
BERR_Code BDSP_Raaga_P_ProcessAudioCapture(
    void *pDevice /* [in] task handle */
    );

/***************************************************************************
Summary:
Function that returns the pointers from where the data can be read and
written to file.
***************************************************************************/
BERR_Code BDSP_Raaga_P_AudioCaptureGetBuffer(
    void *pCapHandle,   /* [in] capture handle */
    BDSP_BufferDescriptor *pBuffers     /* [out] pointer to the structure
                        with address and size of the intermediate buffer from
                        which the data can be written into the file */
    );

/***************************************************************************
Summary:
Function to update the read pointers for the intermediate buffers.
***************************************************************************/
BERR_Code BDSP_Raaga_P_AudioCaptureConsumeData(
    void *pCapture, /* [in] capture handle */
    uint32_t numBytes /* [in] sizes of data read from each intermediate buffer */
    );

/***************************************************************************
Summary:
Function to determine the buffer depth as one continuous chunk based on the
buffer type and a specified read pointer
***************************************************************************/
uint32_t BDSP_Raaga_P_GetAudioBufferDepthLinear(
    BDSP_AF_P_sDRAM_CIRCULAR_BUFFER *pBuffer, /* [in] pointer to circular buffer */
    uint32_t ui32ShadowRead, /* [in] read pointer */
    BDSP_AF_P_BufferType eType, /* [in] buffer type */
    BREG_Handle hReg
    ); /* [in] register handle */

/***************************************************************************
Summary:
Function to determine the free space as one continuous chunk based on the
buffer type
***************************************************************************/
size_t BDSP_Raaga_P_GetAudioCaptureBufferFreeSpaceLinear(
    BDSP_AF_P_CIRCULAR_BUFFER *pBuffer /* [in] pointer to circular buffer */
    );

/***************************************************************************
Summary:
Function to detect a capture error by checking if the write pointer has
overtaken the shadow read pointer
***************************************************************************/
bool BDSP_Raaga_P_DetectAudioCaptureError(
    BDSP_AF_P_sDRAM_CIRCULAR_BUFFER *pBuffer, /* [in] pointer to circular buffer */
    uint32_t ui32ShadowRead, /* shadow read pointer value */
    uint32_t ui32LastWrite, /* last read value of the write pointer */
    BDSP_AF_P_BufferType eType, /* [in] buffer type */
    BREG_Handle hReg /* [in] register handle */
    );

/***************************************************************************
Summary:
Function to update the shadow read pointer with the bytes read and snapshot
write pointer
***************************************************************************/
void BDSP_Raaga_P_GetUpdatedShadowReadAndLastWrite(
    BDSP_AF_P_sDRAM_CIRCULAR_BUFFER *pBuffer, /* [in] pointer to circular buffer */
    raaga_dramaddr *pShadowRead, /* [in/out] shadow read pointer */
    raaga_dramaddr *pLastWrite, /* [out] snapshot of the write pointer */
    BDSP_AF_P_BufferType eType, /* [in] buffer type */
    uint32_t bytesRead, /* [in] number of bytes to update the shadow read with */
    BREG_Handle hReg /* [in] register handle */
    );

/***************************************************************************
Summary:
Function to update the output buffer read pointer
***************************************************************************/
void BDSP_Raaga_P_UpdateReadPointer(
    BDSP_AF_P_sDRAM_CIRCULAR_BUFFER *pBuffer, /* [out] pointer to circular buffer */
    BDSP_AF_P_BufferType eType, /* [in] buffer type */
    raaga_dramaddr ui32ReadAddr, /* Value of read pointer to update with */
    BREG_Handle hReg /* [in] register handle */
    );

BERR_Code BDSP_Raaga_P_UnresetRaagaCore(
    void *pDeviceHandle,
    unsigned uiDspIndex
    );

BERR_Code BDSP_Raaga_P_InitRaagaCore (
    void *pDeviceHandle,
    unsigned uiDspIndex
    );

BERR_Code BDSP_Raaga_P_ReleaseFIFO(
    BDSP_Raaga  *pDevice,
    unsigned dspIndex,
    int32_t* i32Fifo,
    unsigned numfifos
    );

BERR_Code BDSP_Raaga_P_AssignFreeFIFO(
    BDSP_Raaga  *pDevice,
    unsigned dspIndex,
    int32_t* i32Fifo,
    unsigned numfifosreqd
    );

BERR_Code   BDSP_Raaga_P_CreateTaskQueues(void *pTaskHandle,
    unsigned dspIndex
    ) ;

BERR_Code   BDSP_Raaga_P_FreeTaskQueues(void *pTaskHandle) ;

/* Inter task buffer apis */
BERR_Code BDSP_Raaga_P_InterTaskBuffer_Create(
    void *pContextHandle,
    BDSP_DataType dataType,
    BDSP_BufferType bufferType,
    BDSP_InterTaskBufferHandle *pHandle
    );

void BDSP_Raaga_P_InterTaskBuffer_Destroy(
    void *pInterTaskBufferHandle
    );

void BDSP_Raaga_P_InterTaskBuffer_Flush(
    void *pInterTaskBufferHandle
    );

/* PAUSE-UNPAUSE */
BERR_Code BDSP_Raaga_P_Freeze(
    void *hTask,
    const BDSP_AudioTaskFreezeSettings *pSettings
    );

BERR_Code BDSP_Raaga_P_UnFreeze(
    void *hTask,
    const BDSP_AudioTaskUnFreezeSettings *pSettings
    );

void BDSP_Raaga_P_InitDeviceSettings(
    void * pDeviceHandle
    );

/* PAUSE-UNPAUSE */

/***************************************************************************
Summary:
Directs the raaga uart to Uart1 which is by default set for AVD uart. This function is dummy
by default. To enable this feature #define RAAGA_UART_ENABLE has to be uncommented in
bdsp_raaga_priv.c
Supports chips 7231 and 7346.
***************************************************************************/
#ifdef RAAGA_UART_ENABLE
BERR_Code BDSP_Raaga_P_DirectRaagaUartToPort1(BREG_Handle regHandle);
#endif

/* Macro for traversing through the stages in a task */
#define BDSP_MAX_STAGES_PER_TASK    10
#define BDSP_STAGE_TRAVERSE_LOOP_V1_BEGIN(A, B, C, D)                           \
    {                                                                           \
        BDSP_RaagaStage *macroVarStackOfStages[BDSP_MAX_STAGES_PER_TASK];       \
        BDSP_RaagaStage *B;                                                     \
        uint32_t    macroVarStackDepth, macroVari, macroVarNumStOps;            \
        uint32_t   macroVarBrId, macroVarStId, C, D;                            \
                                                                                \
        macroVarStackOfStages[0] = A;                                           \
        macroVarStackDepth = 1;                                                 \
        macroVarBrId = 0;                                                       \
        macroVarStId = -1;                                                      \
        while (macroVarStackDepth != 0)                                         \
        {                                                                       \
            macroVarStackDepth--;                                               \
            B = macroVarStackOfStages[macroVarStackDepth];                   \
            C = macroVarBrId;                                                   \
            D = macroVarStId++;                                                 \
            BDBG_OBJECT_ASSERT(B, BDSP_RaagaStage);                             \

            /* Push all connected stage handles into the stack */
            /* For loop in reverse order as the stack is a lifo structure */
#define BDSP_STAGE_TRAVERSE_LOOP_END(B)                                         \
            macroVarNumStOps = 0;                                               \
            for(macroVari = BDSP_AF_P_MAX_OP_FORKS; macroVari >=1 ; macroVari--)\
            {                                                                   \
                if ((B->sStageOutput[macroVari-1].eConnectionType               \
                        == BDSP_ConnectionType_eStage)                          \
                    && (B->sStageOutput[macroVari-1].eNodeValid ==              \
                        BDSP_AF_P_eValid))                                      \
                {                                                               \
                    macroVarNumStOps++;                                         \
                    macroVarStackOfStages[macroVarStackDepth] = (BDSP_RaagaStage *)B->sStageOutput[macroVari-1].connectionDetails.stage.hStage->pStageHandle; \
                    macroVarStackDepth++;                                       \
                    BDBG_ASSERT(macroVarStackDepth < 10);                       \
                }                                                               \
            }                                                                   \
                                                                                \
            if (macroVarNumStOps == 0)                                          \
            {                                                                   \
                macroVarBrId++;                                                 \
                macroVarStId = -1;                                              \
            }                                                                   \
        }                                                                       \
    }

#define BDSP_STAGE_TRAVERSE_LOOP_BEGIN(A, B)                                    \
    BDSP_STAGE_TRAVERSE_LOOP_V1_BEGIN(A, B, macroBrId, macroStId)

#define BDSP_RAAGA_P_ALGORITHM_SUPPORTED(a) (BDSP_Raaga_P_LookupAlgorithmInfo_isrsafe(a)->supported)
#define BDSP_RAAGA_P_ALGORITHM_NAME(a)      (BDSP_Raaga_P_LookupAlgorithmInfo_isrsafe(a)->pName)
#define BDSP_RAAGA_P_ALGORITHM_TYPE(a)      (BDSP_Raaga_P_LookupAlgorithmInfo_isrsafe(a)->type)

BERR_Code BDSP_Raaga_P_CalcThresholdZeroFillTimeAudOffset_isrsafe(
                            BDSP_CTB_Input                  *pCtbInput,
                            void                            *pStageHandle,
                            BDSP_CTB_Output             *psCTB_OutputStructure
                        );
#define BDSP_Raaga_P_CalcThresholdZeroFillTimeAudOffset BDSP_Raaga_P_CalcThresholdZeroFillTimeAudOffset_isrsafe
/***************************************************************************
Summary:
    Various global data structures that are shared between source files.
***************************************************************************/
extern  const BDSP_VOM_Algo_Start_Addr                      BDSP_sAlgoStartAddr;
extern  const BDSP_VOM_Table                                BDSP_sVomTable;
extern const BDSP_Version BDSP_sRaagaVersion;
#endif /* #ifndef BDSP_RAAGA_PRIV_H_*/

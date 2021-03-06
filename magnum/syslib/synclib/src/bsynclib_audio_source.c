/***************************************************************************
*	  Copyright (c) 2004-2012, Broadcom Corporation
*	  All Rights Reserved
*	  Confidential Property of Broadcom Corporation
*
*  THIS SOFTWARE MAY ONLY BE USED SUBJECT TO AN EXECUTED SOFTWARE LICENSE
*  AGREEMENT  BETWEEN THE USER AND BROADCOM.  YOU HAVE NO RIGHT TO USE OR
*  EXPLOIT THIS MATERIAL EXCEPT SUBJECT TO THE TERMS OF SUCH AN AGREEMENT.
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

#include "bstd.h"
#include "bsynclib_priv.h"
#include "bsynclib_channel_priv.h"
#include "bsynclib_audio_source.h"
#include "bsynclib_mute_control.h"

BDBG_MODULE(synclib);

BSYNClib_AudioSource * BSYNClib_AudioSource_Create(void)
{
	BSYNClib_AudioSource * psSource = NULL;

	BDBG_ENTER(BSYNClib_AudioSource_Create);

	psSource = (BSYNClib_AudioSource *)BKNI_Malloc(sizeof(BSYNClib_AudioSource));

	if (psSource)
	{
		BKNI_Memset(psSource, 0, sizeof(BSYNClib_AudioSource));
		BSYNClib_DelayElement_Init(&psSource->sElement);
		BSYNClib_AudioSource_GetDefaultConfig(&psSource->sConfig);
		BSYNClib_AudioSource_P_GetDefaultStatus(&psSource->sStatus);
	}

	BDBG_LEAVE(BSYNClib_AudioSource_Create);
	return psSource;
}

void BSYNClib_AudioSource_Destroy(BSYNClib_AudioSource * psSource)
{
	BDBG_ENTER(BSYNClib_AudioSource_Destroy);

	BDBG_ASSERT(psSource);

	BKNI_Free(psSource);

	BDBG_LEAVE(BSYNClib_AudioSource_Destroy);
}

bool BSYNClib_AudioSource_SyncCheck(BSYNClib_AudioSource * psSource)
{
	bool bPass = false;
	
	BDBG_ENTER(BSYNClib_AudioSource_SyncCheck);

	BDBG_ASSERT(psSource);

	bPass = !psSource->sElement.sSnapshot.bSynchronize
		|| (psSource->sElement.sSnapshot.bStarted /* must be started */
		&& psSource->sSnapshot.bSamplingRateReceived /* have received a sampling rate */
		&& psSource->sElement.sDelay.sSnapshot.bValid /* have a valid measured delay */
		&& psSource->sElement.sDelay.sResults.bAccepted); /* and be accepted */

	BDBG_MSG(("[%d] Audio source %u sync check:", psSource->sElement.hParent->iIndex, psSource->sElement.uiIndex));
	BDBG_MSG(("[%d]  %s", psSource->sElement.hParent->iIndex, psSource->sElement.sSnapshot.bSynchronize ? "synchronized" : "ignored"));
	BDBG_MSG(("[%d]  %s", psSource->sElement.hParent->iIndex, psSource->sElement.sSnapshot.bStarted ? "started" : "stopped"));
	BDBG_MSG(("[%d]  sampling rate %s", psSource->sElement.hParent->iIndex, psSource->sSnapshot.bSamplingRateReceived ? "received" : "not received"));
	BDBG_MSG(("[%d]  delay %s, %s", psSource->sElement.hParent->iIndex, psSource->sElement.sDelay.sSnapshot.bValid ? "valid" : "invalid", 
		psSource->sElement.sDelay.sResults.bAccepted ? "accepted" : "unaccepted"));

	BDBG_LEAVE(BSYNClib_AudioSource_SyncCheck);
	return bPass;
}

void BSYNClib_AudioSource_Reset_isr(BSYNClib_AudioSource * psSource)
{
	BDBG_ENTER(BSYNClib_AudioSource_Reset_isr);

	BDBG_ASSERT(psSource);

	psSource->sData.bSamplingRateReceived = false;

	BDBG_LEAVE(BSYNClib_AudioSource_Reset_isr);
}

BERR_Code BSYNClib_AudioSource_SetMute(BSYNClib_AudioSource * psSource, bool bMute)
{
	BERR_Code rc = BERR_SUCCESS;
	BSYNClib_Channel_Handle hChn;
	BSYNClib_Channel_MuteCallback * pcbMute;

	BDBG_ENTER(BSYNClib_AudioSource_SetMute);
	
	BDBG_ASSERT(psSource);
	
	hChn = psSource->sElement.hParent;
	pcbMute = &hChn->sSettings.sAudio.sSource.cbMute;

	BKNI_EnterCriticalSection();
	psSource->sResults.bMutePending = false;
	
	/* cancel any pending unmute timer */
	rc = BSYNClib_Channel_P_CancelTimer_isr(hChn, psSource->psUnmuteTimer);
	BKNI_LeaveCriticalSection();
	if (rc) goto end;

	/* cancel any pending unconditional unmute timer */
	if (!bMute)
	{
		BKNI_EnterCriticalSection();
		rc = BSYNClib_Channel_P_CancelTimer_isr(hChn, psSource->psUnconditionalUnmuteTimer);
		BKNI_LeaveCriticalSection();
		if (rc) goto end;
	}

	if (psSource->sConfig.bSynchronize && pcbMute->pfSetMute)/* at mute time, no snapshot has been made */
	{
		rc = pcbMute->pfSetMute(pcbMute->pvParm1, pcbMute->iParm2, psSource->sElement.uiIndex, bMute);
		if(rc) goto end;
		psSource->sStatus.bMuted = bMute;
	}

end:
	BDBG_LEAVE(BSYNClib_AudioSource_SetMute);
	return rc;
}

void BSYNClib_AudioSource_GetDefaultConfig(
	BSYNClib_AudioSource_Config * psConfig
)
{
	BDBG_ENTER(BSYNClib_AudioSource_GetDefaultConfig);

	BDBG_ASSERT(psConfig);
	
	BKNI_Memset(psConfig, 0, sizeof(BSYNClib_AudioSource_Config));

	psConfig->bDigital = true;

	BDBG_LEAVE(BSYNClib_AudioSource_GetDefaultConfig);
}

void BSYNClib_AudioSource_P_SelfClearConfig_isr(
	BSYNClib_AudioSource * psSource
)
{
	BDBG_ENTER(BSYNClib_AudioSource_P_SelfClearConfig_isr);

	BDBG_ASSERT(psSource);
	
	psSource->sConfig.sDelay.bReceived = false;
	psSource->sConfig.bSamplingRateReceived = false;

	BDBG_LEAVE(BSYNClib_AudioSource_P_SelfClearConfig_isr);
}

BERR_Code BSYNClib_AudioSource_P_ProcessConfig_isr(
	BSYNClib_AudioSource * psSource
)
{
	BERR_Code rc = BERR_SUCCESS;
	BSYNClib_AudioSource_Config * psConfig;
	BSYNClib_Channel_Handle hChn;
	bool bChanged = false;
	BSYNClib_DelayElement sDesired;
	BSYNClib_DelayElement * psCurrent;
	BSYNClib_DelayElement_DiffResults sElementDiffResults;

	BDBG_ENTER(BSYNClib_AudioSource_P_ProcessConfig_isr);
	
	BDBG_ASSERT(psSource);
	
	hChn = psSource->sElement.hParent;
	psConfig = &psSource->sConfig;
	psCurrent = &psSource->sElement;

	BKNI_Memset(&sElementDiffResults, 0, sizeof(BSYNClib_DelayElement_DiffResults));

	/* check lifecycle first */
	BSYNClib_DelayElement_CheckLifecycle_isr(psConfig->bStarted, psCurrent, &sElementDiffResults);
	if (sElementDiffResults.eLifecycleEvent == BSYNClib_DelayElement_LifecycleEvent_eStarted)
	{
		BSYNClib_DelayElement_Reset_isr(psCurrent);
	}

	/* create "desired" delay element config */
	sDesired = *psCurrent;
	sDesired.sData.bStarted = psConfig->bStarted;
	sDesired.sData.bSynchronize = psConfig->bSynchronize;
	sDesired.sDelay.sData.uiMeasured = BSYNClib_P_Convert_isr(psConfig->sDelay.sMeasured.uiValue, psConfig->sDelay.sMeasured.eUnits, BSYNClib_Units_e27MhzTicks);
	sDesired.sDelay.sData.uiCustom = BSYNClib_P_Convert_isr(psConfig->sDelay.sCustom.uiValue, psConfig->sDelay.sCustom.eUnits, BSYNClib_Units_e27MhzTicks);
	sDesired.sDelay.sData.eOriginalUnits = psConfig->sDelay.sMeasured.eUnits;
	sDesired.sNotification.sData.bReceived = psConfig->sDelay.bReceived;

	BSYNClib_DelayElement_Diff_isr(&sDesired, &psSource->sElement, &sElementDiffResults);

	if (sElementDiffResults.bChanged)
	{
		bChanged = true;
		BSYNClib_DelayElement_Patch_isr(&sDesired, &psSource->sElement, &sElementDiffResults);
	}

	/* if we want to synchronize this source, tell mute control */
	/* must do this on sync change, not on start, otherwise it's too late */
	switch (sElementDiffResults.eSynchronizationEvent)
	{
		case BSYNClib_DelayElement_SynchronizationEvent_eSynchronized:
			/* SW7420-2314: do not mute if synchronizing but already started */
			if (!psSource->sElement.sData.bStarted)
			{
				psSource->sResults.bMutePending = true;
			}
			else
			{
				psSource->sResults.bMutePending = false;
			}
			break;
		case BSYNClib_DelayElement_SynchronizationEvent_eIgnored:
			psSource->sResults.bMutePending = false;
			break;
		case BSYNClib_DelayElement_SynchronizationEvent_eNone:
		default:
			break;
	}
	
	if (sElementDiffResults.eLifecycleEvent == BSYNClib_DelayElement_LifecycleEvent_eStarted)
	{
		/* reset source data */
		BSYNClib_AudioSource_Reset_isr(psSource);

		/* NOTE: no changing digital on the fly */
		/* source digital or analog */
		if (psConfig->bDigital != psSource->sData.bDigital)
		{
			bChanged = true;
			psSource->sData.bDigital = psConfig->bDigital;
		}

        if (hChn->sConfig.sMuteControl.bEnabled)
        {
            if (psConfig->bSynchronize)
            {
                /* we expect to start muted via sending the mute command once already on synchronization connection, but
                this will ensure the state after stop/start is correct */
                psSource->sResults.bMutePending = true;
            }

            /* assume we started muted, as nexus sync channel will do this */
		    psSource->sStatus.bMuted = true;
		}
	}

	/* received sampling rate info, edge triggered */
	if (psConfig->bSamplingRateReceived)
	{
		if (!psSource->sData.bSamplingRateReceived)
		{
			bChanged = true;
		}
		psSource->sData.bSamplingRateReceived = true;
	}

	/* all audio delays are accepted immediately */
	/* TODO: when we add dynamic audio delays, we need to revisit immediate acceptance */
	if (sElementDiffResults.bDelayReceived)
	{
		/* this should not indicate changed */
		psSource->sElement.sDelay.sResults.bAccepted = true;
	}
	
	if (bChanged)
	{
		BDBG_MSG(("[%d] Audio source %u properties changed:", psSource->sElement.hParent->iIndex, psSource->sElement.uiIndex));
		if (sElementDiffResults.eSynchronizationEvent != BSYNClib_DelayElement_SynchronizationEvent_eNone)
		{
			BDBG_MSG(("[%d]  %s", psSource->sElement.hParent->iIndex, BSYNClib_DelayElement_SynchronizationEventNames[sElementDiffResults.eSynchronizationEvent]));
		}
		if (sElementDiffResults.eLifecycleEvent != BSYNClib_DelayElement_LifecycleEvent_eNone)
		{
			BDBG_MSG(("[%d]  %s", psSource->sElement.hParent->iIndex, BSYNClib_DelayElement_LifecycleEventNames[sElementDiffResults.eLifecycleEvent]));
		}
		BDBG_MSG(("[%d]  measured delay %u ms", psSource->sElement.hParent->iIndex, BSYNClib_P_Convert_isr(psSource->sElement.sDelay.sData.uiMeasured, BSYNClib_Units_e27MhzTicks, BSYNClib_Units_eMilliseconds)));
		BDBG_MSG(("[%d]  custom delay %u ms", psSource->sElement.hParent->iIndex, BSYNClib_P_Convert_isr(psSource->sElement.sDelay.sData.uiCustom, BSYNClib_Units_e27MhzTicks, BSYNClib_Units_eMilliseconds)));
		BDBG_MSG(("[%d]  %s", psSource->sElement.hParent->iIndex, psSource->sData.bDigital ? "digital" : "analog"));
		BDBG_MSG(("[%d]  sampling rate %s", psSource->sElement.hParent->iIndex, psSource->sData.bSamplingRateReceived ? "received" : "not received"));
		if (psSource->sResults.bMutePending)
		{
				BDBG_MSG(("[%d]  mute pending", psSource->sElement.hParent->iIndex));
		}
	}

	if (psSource->sResults.bMutePending)
	{
		/* TODO: probably should do this as a dynamic bind so we don't depend upwards, but ... */
		BSYNClib_MuteControl_ScheduleTask_isr(hChn);
	}

    if (bChanged)
    {
        if (BSYNClib_Channel_P_Enabled_isr(hChn))
        {
            /* immediate reprocessing based on current state */
            BSYNClib_Channel_P_ScheduleTask_isr(hChn);
        }
        else
        {
            /* reprocessing based on current state deferred until re-enabled */
            BSYNClib_Channel_P_EnqueueTaskRequest_isr(hChn);
        }
	}
	
	BDBG_LEAVE(BSYNClib_AudioSource_P_ProcessConfig_isr);
	return rc;
}

void BSYNClib_AudioSource_Snapshot_isr(BSYNClib_AudioSource * psSource)
{
	BDBG_ENTER(BSYNClib_AudioSource_Snapshot_isr);

	BDBG_ASSERT(psSource);

	psSource->sSnapshot = psSource->sData;
	
	BSYNClib_DelayElement_Snapshot_isr(&psSource->sElement);

	BDBG_LEAVE(BSYNClib_AudioSource_Snapshot_isr);
}

void BSYNClib_AudioSource_P_GetDefaultStatus(
	BSYNClib_Source_Status * psStatus
)
{
	BDBG_ENTER(BSYNClib_AudioSource_P_GetDefaultStatus);

	BDBG_ASSERT(psStatus);

	psStatus->bMuted = false;
	psStatus->sDelayNotification.bEnabled = false;
	psStatus->sDelayNotification.sThreshold.uiValue = 0;
	psStatus->sAppliedDelay.uiValue = 0;

	BDBG_LEAVE(BSYNClib_AudioSource_P_GetDefaultStatus);
}


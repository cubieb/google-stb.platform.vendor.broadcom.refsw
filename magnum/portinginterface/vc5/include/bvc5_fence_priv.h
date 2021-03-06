/***************************************************************************
 *     (c)2014 Broadcom Corporation
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
 **************************************************************************/
#ifndef BVC5_FENCE_H__
#define BVC5_FENCE_H__

struct BVC5_P_FenceArray;

typedef struct BVC5_P_FenceArray *BVC5_FenceArrayHandle;


/* Note: The following 4 functions should not be called in android.
 * In android fences cannot be signaled from user space and the only way to
 * create a fence in android is queing a job with the scheduler;
 */

/* Create a fence that can be signaled from user space; Once a fence is
 * created, the caller must guarantee that it will call SignalFromUser. The
 * caller becomes the owner of the fence and it must also either call
 * CloseFence(after an optional WaitFence) or create a job that will wait on
 * that fence (in this case, the scheduler becomes the owner of the fence and
 * it responsible for closing it).
 */
int BVC5_P_FenceCreateToSignalFromUser(BVC5_FenceArrayHandle hFenceArr, uint32_t uiClientId);
void BVC5_P_FenceSignalFromUser(BVC5_FenceArrayHandle hFenceArr, int iFenceId);

void BVC5_P_FenceAddCallback(BVC5_FenceArrayHandle hFenceArr, int iFenceId,
   void (*pfnCallback)(void *, void *), void *pContext, void *pParam);

void BVC5_P_FenceRemoveCallback(BVC5_FenceArrayHandle hFenceArr,
   int iFenceId
);


/*****************************************************************************/
BERR_Code BVC5_P_FenceArrayCreate(BVC5_FenceArrayHandle *phFenceArr);

void BVC5_P_FenceArrayDestroy(BVC5_FenceArrayHandle hFenceArr);

/*****************************************************************************/

/* A fence created this way must be notified by the scheduler when to be signaled
 * by calling BVC5_P_FenceSignalAndCleanup with the returned dataToSignal.
 * The fence returned by this function can be waited on in user space (and closed).
 * When the fence is closed and dataToSignal signaled (in whatever order this
 * happens), the underlying fence struct gets freed.
 */
int BVC5_P_FenceCreate(BVC5_FenceArrayHandle hFenceArr, uint32_t uiClientId,
   void **dataToSignal);

/* close the fence passed in from user space */
void BVC5_P_FenceClose(BVC5_FenceArrayHandle hFenceArr,int iFenceId);


/* dataToSignal will be freed this call, so the caller must not  use it again
 */
void BVC5_P_FenceSignalAndCleanup(BVC5_FenceArrayHandle hFenceArr, void *dataToSignal);

/* Function to be called by the scheduler when it wants to be notified
 * that a fence passed in from user space is signaled.
 * Return code:
 *    < 0: some error occured while trying to install an async callback on this fence iFenceId
 *    == 0: the fence is not yet signalled, callback will be made when signalled
 *     > 0: fence was already signalled, callback will not be made
 *
 * If this call succeeds (return code == 0), iFenceId will be closed after this call and the
 * scheduler must not use it anymore.
 * The scheduler can use the returned data to check if the fence was signaled,.
 * The scheduler  must call BVC5_P_FenceWaitAsyncCleanup when done with returned waitData.
 */
int BVC5_P_FenceWaitAsync(BVC5_FenceArrayHandle hFenceArr, uint32_t uiClientId,
   int iFenceId,
   void (*pfnCallback)(void *, void *), void *pContext, void *pParam,
   void **waitData
);

/* returns 1 if the fence we are waiting for has been signalled */
int BVC5_P_FenceWaitAsyncIsSignaled(BVC5_FenceArrayHandle hFenceArr, void *waitData);
void BVC5_P_FenceWaitAsyncCleanup(BVC5_FenceArrayHandle hFenceArr, void *waitData);

/* Remove all fences associated with a client */
void BVC5_P_FenceClientDestroy(BVC5_FenceArrayHandle hFenceArr, uint32_t uiClientId);
void BVC5_P_FenceClientCheckDestroy(BVC5_FenceArrayHandle hFenceArr, uint32_t uiClientId);

#endif /* BVC5_FENCE_H__ */

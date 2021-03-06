/******************************************************************************
 * (c) 2015 Broadcom Corporation
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

/* base modules */
#include "bstd.h"           /* standard types */
#include "bdbg.h"           /* debug interface */
#include "berr.h"           /* error code */
#include "bkni.h"           /* kernel interface */

#include "bxvd_auth.h"
#include "bafl.h"
#include "bxvd_image_priv.h"

const uint32_t BXVD_P_CoreDeviceID[] =
{
   BXVD_P_OL,
   BXVD_P_IL,
#if ((BCHP_CHIP == 7135) || \
     (BCHP_CHIP == 7231) || \
     (BCHP_CHIP == 7344) || \
     (BCHP_CHIP == 7346) || \
     (BCHP_CHIP == 7422) || \
     (BCHP_CHIP == 7425) || \
     (BCHP_CHIP == 7429) || \
     (BCHP_CHIP == 7435))
   BXVD_P_BL,
#endif
};

BERR_Code
BXVD_DumpImage(
   unsigned uiFirmwareId,
   void *pBuffer,
   unsigned uiBufferSize,
   void **pvCodeStart,
   unsigned *puiCodeSize
)
{
   BERR_Code rc = BERR_SUCCESS;
   BAFL_FirmwareLoadInfo stFWLoadInfo;

   BDBG_ASSERT( pvCodeStart );
   BDBG_ASSERT( puiCodeSize );

   BKNI_Memset(&stFWLoadInfo, 0, sizeof(stFWLoadInfo));

   rc = BAFL_Load(
      BXVD_P_CoreDeviceID[uiFirmwareId],
      &BXVD_IMAGE_Interface,
      (void**) BXVD_IMAGE_Context,
      uiFirmwareId,
      pBuffer, /* Virtual Address */
      uiBufferSize,
      false,
      &stFWLoadInfo
      );

   *pvCodeStart = stFWLoadInfo.stCode.pStartAddress;
   *puiCodeSize = stFWLoadInfo.stCode.uiSize;

   return BERR_TRACE(rc);
}

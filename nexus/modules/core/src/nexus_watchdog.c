/***************************************************************************
*     (c)2004-2013 Broadcom Corporation
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
* $brcm_Workfile: $
* $brcm_Revision: $
* $brcm_Date: $
*
* API Description:
*   API name: Watchdog
*    Specific APIs related to HW watchdog
*
* Revision History:
*
* $brcm_Log: $
* 
***************************************************************************/
#include "nexus_core_module.h"
#include "bchp_common.h"
#include "bchp_timer.h" /* TODO: we are assuming that this is available on all platforms and the register
                           names are identical. this appears to be the case at least for now */
#include "bchp_sun_top_ctrl.h"
#include "bchp_int_id_timer.h"

BDBG_MODULE(nexus_watchdog);

#define NEXUS_WATCHDOG_TIMER_FREQ 27000000 /* 27 MHz */

static struct {
    bool started;
    unsigned timeout;
    NEXUS_WatchdogSettings settings;
    BINT_CallbackHandle intCallback;
    NEXUS_IsrCallbackHandle callback;
} g_watchdog;

NEXUS_Error NEXUS_Watchdog_P_Init(void)
{
    BKNI_Memset(&g_watchdog, 0, sizeof(g_watchdog));
    g_watchdog.callback = NEXUS_IsrCallback_Create(NULL, NULL);
    /* must issue magic stop sequence to get control again */
    NEXUS_Watchdog_StopTimer();
    return 0;
}

void NEXUS_Watchdog_P_Uninit(void)
{
    NEXUS_Watchdog_StopTimer();
    NEXUS_IsrCallback_Destroy(g_watchdog.callback);
    BKNI_Memset(&g_watchdog, 0, sizeof(g_watchdog));
}

static void nexus_p_watchdog_isr(void *context, int param)
{
    BSTD_UNUSED(context);
    BSTD_UNUSED(param);
    /* level-triggered, so disable till stop */
    BINT_DisableCallback_isr(g_watchdog.intCallback);
    NEXUS_IsrCallback_Fire_isr(g_watchdog.callback);
}

static void nexus_watchdog_p_stop_callback(void);

static NEXUS_Error nexus_watchdog_p_start_callback(void)
{
    if (!g_watchdog.intCallback) {
        int rc;
        rc = BINT_CreateCallback(&g_watchdog.intCallback, g_pCoreHandles->bint, BCHP_INT_ID_WDINT, nexus_p_watchdog_isr, NULL, 0);
        if (rc) return BERR_TRACE(rc);
    }
    (void)BINT_EnableCallback(g_watchdog.intCallback);
    return 0;
}

static void nexus_watchdog_p_stop_callback(void)
{
    if (g_watchdog.intCallback) {
        BINT_DestroyCallback(g_watchdog.intCallback);
        g_watchdog.intCallback = NULL;
    }
}

NEXUS_Error NEXUS_Watchdog_SetTimeout(unsigned timeout)
{
    if (g_watchdog.started) { /* the HW already protects against this, but it doesn't hurt to stop it in SW */
        BDBG_ERR(("NEXUS_Watchdog_SetTimeout: Timeout cannot be set while timer is counting"));
        return BERR_TRACE(NEXUS_NOT_INITIALIZED);
    }

    if (timeout<NEXUS_WATCHDOG_MIN_TIMEOUT || timeout>NEXUS_WATCHDOG_MAX_TIMEOUT) {
        BDBG_ERR(("NEXUS_Watchdog_SetTimeout: Invalid timeout value specified"));
        return BERR_TRACE(NEXUS_NOT_INITIALIZED);
    }

    BDBG_ASSERT(g_NexusCore.publicHandles.reg);
    /* write timeout value to register */
    BREG_Write32(g_NexusCore.publicHandles.reg, BCHP_TIMER_WDTIMEOUT, timeout*NEXUS_WATCHDOG_TIMER_FREQ);

    /* WD_COUNT_MODE 0 = one-shot
       WD_EVENT_MODE 0 = reset (it also gives a maskable midpoint interrupt) */
    BREG_Write32(g_NexusCore.publicHandles.reg, BCHP_TIMER_WDCTRL, 0);

    g_watchdog.timeout = timeout;
    return NEXUS_SUCCESS;
}

NEXUS_Error NEXUS_Watchdog_StartTimer(void)
{
    int rc;

    if (g_watchdog.timeout==0) {
        BDBG_ERR(("NEXUS_Watchdog_StartTimer: Timeout value was not previously set"));
        return BERR_TRACE(NEXUS_NOT_INITIALIZED);
    }

#if defined(BCHP_SUN_TOP_CTRL_RESET_CTRL_watchdog_reset_enable_SHIFT)
    if (!(BREG_Read32(g_pCoreHandles->reg, BCHP_SUN_TOP_CTRL_RESET_CTRL) & BCHP_SUN_TOP_CTRL_RESET_CTRL_watchdog_reset_enable_MASK)) {
        BDBG_ERR(("NEXUS_Watchdog_StartTimer requires that BCHP_SUN_TOP_CTRL_RESET_CTRL_watchdog_reset_enable be 1. Set this in nexus_platform_pinmux.c or in your application."));
        return BERR_TRACE(NEXUS_NOT_INITIALIZED);
    }
#endif

    rc = nexus_watchdog_p_start_callback();
    if (rc) return BERR_TRACE(rc);

    /* magic start sequence */
    BREG_Write32(g_NexusCore.publicHandles.reg, BCHP_TIMER_WDCMD, 0xff00);
    BREG_Write32(g_NexusCore.publicHandles.reg, BCHP_TIMER_WDCMD, 0x00ff);

    g_watchdog.started = true;

    return NEXUS_SUCCESS;
}

NEXUS_Error NEXUS_Watchdog_StopTimer(void)
{
    /* allow already-stopped timer to re-issue stop. needed for re-init system. */
    /* magic stop sequence */
    BREG_Write32(g_NexusCore.publicHandles.reg, BCHP_TIMER_WDCMD, 0xee00);
    BREG_Write32(g_NexusCore.publicHandles.reg, BCHP_TIMER_WDCMD, 0x00ee);
    nexus_watchdog_p_stop_callback();
    g_watchdog.started = false;
    return NEXUS_SUCCESS;
}

#if defined(BCHP_AON_CTRL_REG_START)
#include "bchp_aon_ctrl.h"
/* SUN_TOP_CTRL_RESET_HISTORY is NOT USED in chips that have a sys_aon always-on power island module.
   They use the reset history feature in sys_aon. */
void NEXUS_Watchdog_GetLastResetStatus(bool *pStatus)
{
    uint32_t ulVal;
    BDBG_ASSERT(g_NexusCore.publicHandles.reg);
    ulVal = BREG_Read32(g_NexusCore.publicHandles.reg, BCHP_AON_CTRL_RESET_HISTORY);
#ifdef BCHP_AON_CTRL_RESET_HISTORY_host_watchdog_timer_reset_MASK
    ulVal = BCHP_GET_FIELD_DATA(ulVal, AON_CTRL_RESET_HISTORY,  host_watchdog_timer_reset);
#else
    ulVal = BCHP_GET_FIELD_DATA(ulVal, AON_CTRL_RESET_HISTORY,  watchdog_timer_reset);
#endif
    *pStatus = (ulVal!=0);
    ulVal = BREG_Read32(g_NexusCore.publicHandles.reg, BCHP_AON_CTRL_RESET_CTRL);
    BCHP_SET_FIELD_DATA( ulVal, AON_CTRL_RESET_CTRL, clear_reset_history, 1 );
    BREG_Write32(g_NexusCore.publicHandles.reg, BCHP_AON_CTRL_RESET_CTRL,ulVal); /* clear status */

    return;
}
#else
void NEXUS_Watchdog_GetLastResetStatus(bool *pStatus)
{
    uint32_t ulVal;
    BDBG_ASSERT(g_NexusCore.publicHandles.reg);
    ulVal = BREG_Read32(g_NexusCore.publicHandles.reg, BCHP_SUN_TOP_CTRL_RESET_HISTORY);
    ulVal = BCHP_GET_FIELD_DATA(ulVal, SUN_TOP_CTRL_RESET_HISTORY,  watchdog_timer_reset);
    *pStatus = (ulVal!=0);
    ulVal = BREG_Read32(g_NexusCore.publicHandles.reg, BCHP_SUN_TOP_CTRL_RESET_CTRL);
    BCHP_SET_FIELD_DATA( ulVal, SUN_TOP_CTRL_RESET_CTRL, clear_reset_history, 1 );
    BREG_Write32(g_NexusCore.publicHandles.reg, BCHP_SUN_TOP_CTRL_RESET_CTRL,ulVal); /* clear status */

    return;
}
#endif

void NEXUS_Watchdog_GetSettings( NEXUS_WatchdogSettings *pSettings )
{
    *pSettings = g_watchdog.settings;
}

NEXUS_Error NEXUS_Watchdog_SetSettings( const NEXUS_WatchdogSettings *pSettings )
{
    NEXUS_IsrCallback_Set(g_watchdog.callback, &pSettings->midpointCallback);
    g_watchdog.settings = *pSettings;
    return NEXUS_SUCCESS;
}

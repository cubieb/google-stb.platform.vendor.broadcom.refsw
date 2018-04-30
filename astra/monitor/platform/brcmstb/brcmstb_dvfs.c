/******************************************************************************
 * Copyright (C) 2017 Broadcom.  The term "Broadcom" refers to Broadcom Limited and/or its subsidiaries.
 *
 * This program is the proprietary software of Broadcom and/or its licensors,
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
 *****************************************************************************/

#include "monitor.h"
#include "platform_dvfs.h"
#include "brcmstb_svc.h"
#include "brcmstb_dvfs.h"
#include "brcmstb_priv.h"
#include "avs.h"

bool avs_init_done;

void plat_dvfs_init(void)
{
    uintptr_t mbox_base    = BRCMSTB_RGROUP_BASE(AVS_CPU_DATA_MEM);
    uintptr_t host_l2_base = BRCMSTB_RGROUP_BASE(AVS_HOST_L2);
    uintptr_t avs_l2_base  = BRCMSTB_RGROUP_BASE(AVS_CPU_L2);

    avs_init(mbox_base, host_l2_base, avs_l2_base);
    avs_init_done = true;
}

int plat_cpu_pstate_set(uint32_t pstate)
{
    return avs_cpu_pstate_set(pstate);
}

int plat_cpu_pstate_get(uint32_t *ppstate)
{
    return avs_cpu_pstate_get(ppstate);
}

int plat_cpu_freq_get(uint32_t *pfreq)
{
    uint32_t cpu_freq;
    int ret;

    if (avs_init_done) {
        /* AVS API rev2 */
        uint32_t cpu_pstate;

        ret = avs_cpu_pstate_get(&cpu_pstate);
        if (ret)
            return ret;

        ret = avs_cpu_pstate_freq(cpu_pstate, &cpu_freq);
        if (ret)
            return ret;
    }
    else {
        /* AVS API rev1 */
        uintptr_t mbox_base = BRCMSTB_RGROUP_BASE(AVS_CPU_DATA_MEM);

        ret = avs_rev1_cpu_freq(mbox_base, &cpu_freq);
        if (ret)
            return ret;
    }

    if (pfreq)
        *pfreq = cpu_freq;

    return MON_OK;
}

int plat_cpu_pstate_freqs(
    size_t *pcount,
    uint32_t *pfreqs)
{
    return avs_cpu_pstate_freqs(pcount, pfreqs);
}

static void brcmstb_svc_dvfs_init(void)
{
}

static void brcmstb_svc_dvfs_proc(
    uint32_t fid,
    uint64_t *ctx,
    uint64_t flags)
{
    UNUSED(fid);
    UNUSED(ctx);
    UNUSED(flags);
}

service_mod_desc_t brcmstb_svc_dvfs_desc = {
    BRCMSTB_SVC_DVFS_MAX,
    NULL,
    brcmstb_svc_dvfs_init,
    brcmstb_svc_dvfs_proc
};

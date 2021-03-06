/******************************************************************************
*    (c)2011-2013 Broadcom Corporation
*
* This program is the proprietary software of Broadcom Corporation and/or its licensors,
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
*
* $brcm_Workfile: $
* $brcm_Revision: $
* $brcm_Date: $
*
* Module Description:
*
* Revision History:
*
* $brcm_Log: $
*
*****************************************************************************/
#ifndef _BDSQ_45308_H_
#define _BDSQ_45308_H_


#ifdef __cplusplus
extern "C" {
#endif


/* device configuration parameters */
enum {
   /* TBD: add new device configuration parameters here... */
   BDSQ_45308_CONFIG_MAX
};


/* channel configuration parameters */
enum {
   BDSQ_45308_CONFIG_RRTO_US,              /* diseqc receive reply timeout in usecs */
   BDSQ_45308_CONFIG_BIT_THRESHOLD_US,     /* threshold for diseqc rx bit detection in usecs */
   BDSQ_45308_CONFIG_TONE_THRESHOLD,       /* threshold for diseqc energy tone detect in units of 0.16 counts per mV */
   BDSQ_45308_CONFIG_PRETX_DELAY_MS,       /* delay time in msecs before transmitting diseqc command */
   BDSQ_45308_CONFIG_VSENSE_THRESHOLD_HI,  /* voltage detect overvoltage threshold */
   BDSQ_45308_CONFIG_VSENSE_THRESHOLD_LO,  /* voltage detect undervoltage threshold */
   BDSQ_45308_CONFIG_PGA_GAIN,             /* receiver pga gain */
   BDSQ_45308_CONFIG_ENABLE_LNBPU,         /* 0=LNBPU not used , 1=LNBPU on TXEN pin */
   BDSQ_45308_CHAN_CONFIG_MAX
};


/* chip-specific functions */
BERR_Code BDSQ_45308_GetDefaultSettings(BDSQ_Settings *pDefSettings);
BERR_Code BDSQ_45308_GetChannelDefaultSettings(BDSQ_Handle h, uint32_t chnNo, BDSQ_ChannelSettings *pChnDefSettings);

#ifdef __cplusplus
}
#endif

#endif /* _BDSQ_45308_H_ */

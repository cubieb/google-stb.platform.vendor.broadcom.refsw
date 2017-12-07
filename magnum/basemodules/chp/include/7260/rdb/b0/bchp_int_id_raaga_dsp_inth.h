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
 *
 * Module Description:
 *                     DO NOT EDIT THIS FILE DIRECTLY
 *
 * This module was generated magically with RDB from a source description
 * file. You must edit the source file for changes to be made to this file.
 *
 * The launch point for all information concerning RDB is found at:
 *   http://bcgbu.broadcom.com/RDB/SitePages/Home.aspx
 *
 * Date:           Generated on               Tue Jun 27 10:53:30 2017
 *                 Full Compile MD5 Checksum  af3866631f175583174954751d5be73f
 *                     (minus title and desc)
 *                 MD5 Checksum               c1c002d58c98961746a53c856520a690
 *
 * lock_release:   r_1255
 * Compiled with:  RDB Utility                unknown
 *                 RDB.pm                     1570
 *                 generate_int_id.pl         1.0
 *                 Perl Interpreter           5.014001
 *                 Operating System           linux
 *                 Script Source              home/pntruong/sbin/generate_int_id.pl
 *                 DVTSWVER                   LOCAL home/pntruong/sbin/generate_int_id.pl
 *
 *
********************************************************************************/

#include "bchp.h"
#include "bchp_raaga_dsp_inth.h"

#ifndef BCHP_INT_ID_RAAGA_DSP_INTH_H__
#define BCHP_INT_ID_RAAGA_DSP_INTH_H__

#define BCHP_INT_ID_AX_DONE_INT               BCHP_INT_ID_CREATE(BCHP_RAAGA_DSP_INTH_HOST_STATUS, BCHP_RAAGA_DSP_INTH_HOST_STATUS_AX_DONE_INT_SHIFT)
#define BCHP_INT_ID_AX_ERROR_INT              BCHP_INT_ID_CREATE(BCHP_RAAGA_DSP_INTH_HOST_STATUS, BCHP_RAAGA_DSP_INTH_HOST_STATUS_AX_ERROR_INT_SHIFT)
#define BCHP_INT_ID_DMA_Q0                    BCHP_INT_ID_CREATE(BCHP_RAAGA_DSP_INTH_HOST_STATUS, BCHP_RAAGA_DSP_INTH_HOST_STATUS_DMA_Q0_SHIFT)
#define BCHP_INT_ID_DMA_Q1                    BCHP_INT_ID_CREATE(BCHP_RAAGA_DSP_INTH_HOST_STATUS, BCHP_RAAGA_DSP_INTH_HOST_STATUS_DMA_Q1_SHIFT)
#define BCHP_INT_ID_DMA_Q2                    BCHP_INT_ID_CREATE(BCHP_RAAGA_DSP_INTH_HOST_STATUS, BCHP_RAAGA_DSP_INTH_HOST_STATUS_DMA_Q2_SHIFT)
#define BCHP_INT_ID_DMA_Q3                    BCHP_INT_ID_CREATE(BCHP_RAAGA_DSP_INTH_HOST_STATUS, BCHP_RAAGA_DSP_INTH_HOST_STATUS_DMA_Q3_SHIFT)
#define BCHP_INT_ID_DMA_Q4                    BCHP_INT_ID_CREATE(BCHP_RAAGA_DSP_INTH_HOST_STATUS, BCHP_RAAGA_DSP_INTH_HOST_STATUS_DMA_Q4_SHIFT)
#define BCHP_INT_ID_DMA_Q5                    BCHP_INT_ID_CREATE(BCHP_RAAGA_DSP_INTH_HOST_STATUS, BCHP_RAAGA_DSP_INTH_HOST_STATUS_DMA_Q5_SHIFT)
#define BCHP_INT_ID_ERROR_INT                 BCHP_INT_ID_CREATE(BCHP_RAAGA_DSP_INTH_HOST_STATUS, BCHP_RAAGA_DSP_INTH_HOST_STATUS_ERROR_INT_SHIFT)
#define BCHP_INT_ID_MEM_PEEK_POKE             BCHP_INT_ID_CREATE(BCHP_RAAGA_DSP_INTH_HOST_STATUS, BCHP_RAAGA_DSP_INTH_HOST_STATUS_MEM_PEEK_POKE_SHIFT)
#define BCHP_INT_ID_PRQ_WATERMARK             BCHP_INT_ID_CREATE(BCHP_RAAGA_DSP_INTH_HOST_STATUS, BCHP_RAAGA_DSP_INTH_HOST_STATUS_PRQ_WATERMARK_SHIFT)
#define BCHP_INT_ID_RICH                      BCHP_INT_ID_CREATE(BCHP_RAAGA_DSP_INTH_HOST_STATUS, BCHP_RAAGA_DSP_INTH_HOST_STATUS_RICH_SHIFT)
#define BCHP_INT_ID_SEC_PROT_VIOL             BCHP_INT_ID_CREATE(BCHP_RAAGA_DSP_INTH_HOST_STATUS, BCHP_RAAGA_DSP_INTH_HOST_STATUS_SEC_PROT_VIOL_SHIFT)
#define BCHP_INT_ID_TIMER_INT                 BCHP_INT_ID_CREATE(BCHP_RAAGA_DSP_INTH_HOST_STATUS, BCHP_RAAGA_DSP_INTH_HOST_STATUS_TIMER_INT_SHIFT)
#define BCHP_INT_ID_UART_RX                   BCHP_INT_ID_CREATE(BCHP_RAAGA_DSP_INTH_HOST_STATUS, BCHP_RAAGA_DSP_INTH_HOST_STATUS_UART_RX_SHIFT)
#define BCHP_INT_ID_UART_TX                   BCHP_INT_ID_CREATE(BCHP_RAAGA_DSP_INTH_HOST_STATUS, BCHP_RAAGA_DSP_INTH_HOST_STATUS_UART_TX_SHIFT)
#define BCHP_INT_ID_VOM_MISS_INT              BCHP_INT_ID_CREATE(BCHP_RAAGA_DSP_INTH_HOST_STATUS, BCHP_RAAGA_DSP_INTH_HOST_STATUS_VOM_MISS_INT_SHIFT)
#define BCHP_INT_ID_WATCHDOG_TIMER_ATTN       BCHP_INT_ID_CREATE(BCHP_RAAGA_DSP_INTH_HOST_STATUS, BCHP_RAAGA_DSP_INTH_HOST_STATUS_WATCHDOG_TIMER_ATTN_SHIFT)

#endif /* #ifndef BCHP_INT_ID_RAAGA_DSP_INTH_H__ */

/* End of File */

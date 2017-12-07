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
 * Date:           Generated on               Tue Jun 27 10:52:40 2017
 *                 Full Compile MD5 Checksum  de13a1e8011803b5a40ab14e4d71d071
 *                     (minus title and desc)
 *                 MD5 Checksum               b694fcab41780597392ed5a8f558ad3e
 *
 * lock_release:   r_1255
 * Compiled with:  RDB Utility                combo_header.pl
 *                 RDB.pm                     1570
 *                 unknown                    unknown
 *                 Perl Interpreter           5.014001
 *                 Operating System           linux
 *                 Script Source              home/pntruong/sbin/combo_header.pl
 *                 DVTSWVER                   LOCAL home/pntruong/sbin/combo_header.pl
 *
 *
********************************************************************************/

#ifndef BCHP_RAAGA_DSP_PERI_DBG_CTRL_H__
#define BCHP_RAAGA_DSP_PERI_DBG_CTRL_H__

/***************************************************************************
 *RAAGA_DSP_PERI_DBG_CTRL - Raaga DSP Debug Control Registers
 ***************************************************************************/
#define BCHP_RAAGA_DSP_PERI_DBG_CTRL_UART_STATUS 0x20c21080 /* [RO][32] DSP Subsystem UART Status */
#define BCHP_RAAGA_DSP_PERI_DBG_CTRL_UART_RCV_DATA 0x20c21084 /* [RO][32] DSP Subsystem UART Receive Data */
#define BCHP_RAAGA_DSP_PERI_DBG_CTRL_UART_XMIT_DATA 0x20c21088 /* [RW][32] DSP Subsystem UART Transmit Data */
#define BCHP_RAAGA_DSP_PERI_DBG_CTRL_UART_CTRL   0x20c2108c /* [RW][32] DSP Subsystem UART Control */

/***************************************************************************
 *UART_STATUS - DSP Subsystem UART Status
 ***************************************************************************/
/* RAAGA_DSP_PERI_DBG_CTRL :: UART_STATUS :: reserved0 [31:24] */
#define BCHP_RAAGA_DSP_PERI_DBG_CTRL_UART_STATUS_reserved0_MASK    0xff000000
#define BCHP_RAAGA_DSP_PERI_DBG_CTRL_UART_STATUS_reserved0_SHIFT   24

/* RAAGA_DSP_PERI_DBG_CTRL :: UART_STATUS :: XMIT_FIFO_AVAIL [23:16] */
#define BCHP_RAAGA_DSP_PERI_DBG_CTRL_UART_STATUS_XMIT_FIFO_AVAIL_MASK 0x00ff0000
#define BCHP_RAAGA_DSP_PERI_DBG_CTRL_UART_STATUS_XMIT_FIFO_AVAIL_SHIFT 16

/* RAAGA_DSP_PERI_DBG_CTRL :: UART_STATUS :: reserved1 [15:05] */
#define BCHP_RAAGA_DSP_PERI_DBG_CTRL_UART_STATUS_reserved1_MASK    0x0000ffe0
#define BCHP_RAAGA_DSP_PERI_DBG_CTRL_UART_STATUS_reserved1_SHIFT   5

/* RAAGA_DSP_PERI_DBG_CTRL :: UART_STATUS :: RCV_OVERFLOW [04:04] */
#define BCHP_RAAGA_DSP_PERI_DBG_CTRL_UART_STATUS_RCV_OVERFLOW_MASK 0x00000010
#define BCHP_RAAGA_DSP_PERI_DBG_CTRL_UART_STATUS_RCV_OVERFLOW_SHIFT 4

/* RAAGA_DSP_PERI_DBG_CTRL :: UART_STATUS :: XMIT_OVERFLOW [03:03] */
#define BCHP_RAAGA_DSP_PERI_DBG_CTRL_UART_STATUS_XMIT_OVERFLOW_MASK 0x00000008
#define BCHP_RAAGA_DSP_PERI_DBG_CTRL_UART_STATUS_XMIT_OVERFLOW_SHIFT 3

/* RAAGA_DSP_PERI_DBG_CTRL :: UART_STATUS :: XMIT_ACTIVE [02:02] */
#define BCHP_RAAGA_DSP_PERI_DBG_CTRL_UART_STATUS_XMIT_ACTIVE_MASK  0x00000004
#define BCHP_RAAGA_DSP_PERI_DBG_CTRL_UART_STATUS_XMIT_ACTIVE_SHIFT 2

/* RAAGA_DSP_PERI_DBG_CTRL :: UART_STATUS :: XMIT_FULL [01:01] */
#define BCHP_RAAGA_DSP_PERI_DBG_CTRL_UART_STATUS_XMIT_FULL_MASK    0x00000002
#define BCHP_RAAGA_DSP_PERI_DBG_CTRL_UART_STATUS_XMIT_FULL_SHIFT   1

/* RAAGA_DSP_PERI_DBG_CTRL :: UART_STATUS :: RCV_EMPTY [00:00] */
#define BCHP_RAAGA_DSP_PERI_DBG_CTRL_UART_STATUS_RCV_EMPTY_MASK    0x00000001
#define BCHP_RAAGA_DSP_PERI_DBG_CTRL_UART_STATUS_RCV_EMPTY_SHIFT   0

/***************************************************************************
 *UART_RCV_DATA - DSP Subsystem UART Receive Data
 ***************************************************************************/
/* RAAGA_DSP_PERI_DBG_CTRL :: UART_RCV_DATA :: reserved0 [31:08] */
#define BCHP_RAAGA_DSP_PERI_DBG_CTRL_UART_RCV_DATA_reserved0_MASK  0xffffff00
#define BCHP_RAAGA_DSP_PERI_DBG_CTRL_UART_RCV_DATA_reserved0_SHIFT 8

/* RAAGA_DSP_PERI_DBG_CTRL :: UART_RCV_DATA :: RCV_DATA [07:00] */
#define BCHP_RAAGA_DSP_PERI_DBG_CTRL_UART_RCV_DATA_RCV_DATA_MASK   0x000000ff
#define BCHP_RAAGA_DSP_PERI_DBG_CTRL_UART_RCV_DATA_RCV_DATA_SHIFT  0

/***************************************************************************
 *UART_XMIT_DATA - DSP Subsystem UART Transmit Data
 ***************************************************************************/
/* RAAGA_DSP_PERI_DBG_CTRL :: UART_XMIT_DATA :: reserved0 [31:08] */
#define BCHP_RAAGA_DSP_PERI_DBG_CTRL_UART_XMIT_DATA_reserved0_MASK 0xffffff00
#define BCHP_RAAGA_DSP_PERI_DBG_CTRL_UART_XMIT_DATA_reserved0_SHIFT 8

/* RAAGA_DSP_PERI_DBG_CTRL :: UART_XMIT_DATA :: XMIT_DATA [07:00] */
#define BCHP_RAAGA_DSP_PERI_DBG_CTRL_UART_XMIT_DATA_XMIT_DATA_MASK 0x000000ff
#define BCHP_RAAGA_DSP_PERI_DBG_CTRL_UART_XMIT_DATA_XMIT_DATA_SHIFT 0
#define BCHP_RAAGA_DSP_PERI_DBG_CTRL_UART_XMIT_DATA_XMIT_DATA_DEFAULT 0x00000000

/***************************************************************************
 *UART_CTRL - DSP Subsystem UART Control
 ***************************************************************************/
/* RAAGA_DSP_PERI_DBG_CTRL :: UART_CTRL :: XMIT_FIFO_LEVEL [31:24] */
#define BCHP_RAAGA_DSP_PERI_DBG_CTRL_UART_CTRL_XMIT_FIFO_LEVEL_MASK 0xff000000
#define BCHP_RAAGA_DSP_PERI_DBG_CTRL_UART_CTRL_XMIT_FIFO_LEVEL_SHIFT 24
#define BCHP_RAAGA_DSP_PERI_DBG_CTRL_UART_CTRL_XMIT_FIFO_LEVEL_DEFAULT 0x00000000

/* RAAGA_DSP_PERI_DBG_CTRL :: UART_CTRL :: reserved0 [23:18] */
#define BCHP_RAAGA_DSP_PERI_DBG_CTRL_UART_CTRL_reserved0_MASK      0x00fc0000
#define BCHP_RAAGA_DSP_PERI_DBG_CTRL_UART_CTRL_reserved0_SHIFT     18

/* RAAGA_DSP_PERI_DBG_CTRL :: UART_CTRL :: TX_FIFO_RESET [17:17] */
#define BCHP_RAAGA_DSP_PERI_DBG_CTRL_UART_CTRL_TX_FIFO_RESET_MASK  0x00020000
#define BCHP_RAAGA_DSP_PERI_DBG_CTRL_UART_CTRL_TX_FIFO_RESET_SHIFT 17
#define BCHP_RAAGA_DSP_PERI_DBG_CTRL_UART_CTRL_TX_FIFO_RESET_DEFAULT 0x00000000

/* RAAGA_DSP_PERI_DBG_CTRL :: UART_CTRL :: ENABLE [16:16] */
#define BCHP_RAAGA_DSP_PERI_DBG_CTRL_UART_CTRL_ENABLE_MASK         0x00010000
#define BCHP_RAAGA_DSP_PERI_DBG_CTRL_UART_CTRL_ENABLE_SHIFT        16
#define BCHP_RAAGA_DSP_PERI_DBG_CTRL_UART_CTRL_ENABLE_DEFAULT      0x00000000

/* RAAGA_DSP_PERI_DBG_CTRL :: UART_CTRL :: reserved1 [15:12] */
#define BCHP_RAAGA_DSP_PERI_DBG_CTRL_UART_CTRL_reserved1_MASK      0x0000f000
#define BCHP_RAAGA_DSP_PERI_DBG_CTRL_UART_CTRL_reserved1_SHIFT     12

/* RAAGA_DSP_PERI_DBG_CTRL :: UART_CTRL :: BAUD_RATE_DIV [11:00] */
#define BCHP_RAAGA_DSP_PERI_DBG_CTRL_UART_CTRL_BAUD_RATE_DIV_MASK  0x00000fff
#define BCHP_RAAGA_DSP_PERI_DBG_CTRL_UART_CTRL_BAUD_RATE_DIV_SHIFT 0
#define BCHP_RAAGA_DSP_PERI_DBG_CTRL_UART_CTRL_BAUD_RATE_DIV_DEFAULT 0x00000000

#endif /* #ifndef BCHP_RAAGA_DSP_PERI_DBG_CTRL_H__ */

/* End of File */

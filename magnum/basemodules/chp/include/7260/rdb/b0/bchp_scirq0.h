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
 * Date:           Generated on               Tue Jun 27 10:52:38 2017
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

#ifndef BCHP_SCIRQ0_H__
#define BCHP_SCIRQ0_H__

/***************************************************************************
 *SCIRQ0 - Smart Card Level 2 CPU Interrupt Enable/Status
 ***************************************************************************/
#define BCHP_SCIRQ0_SCIRQEN                      0x2040b200 /* [RW][32] SMART CARD L2 INTERRUPT ENABLE */
#define BCHP_SCIRQ0_SCIRQSTAT                    0x2040b204 /* [RW][32] SMART CARD L2 INTERRUPT STATUS */

/***************************************************************************
 *SCIRQEN - SMART CARD L2 INTERRUPT ENABLE
 ***************************************************************************/
/* SCIRQ0 :: SCIRQEN :: reserved0 [31:02] */
#define BCHP_SCIRQ0_SCIRQEN_reserved0_MASK                         0xfffffffc
#define BCHP_SCIRQ0_SCIRQEN_reserved0_SHIFT                        2

/* SCIRQ0 :: SCIRQEN :: scb_irqen [01:01] */
#define BCHP_SCIRQ0_SCIRQEN_scb_irqen_MASK                         0x00000002
#define BCHP_SCIRQ0_SCIRQEN_scb_irqen_SHIFT                        1
#define BCHP_SCIRQ0_SCIRQEN_scb_irqen_DEFAULT                      0x00000000

/* SCIRQ0 :: SCIRQEN :: sca_irqen [00:00] */
#define BCHP_SCIRQ0_SCIRQEN_sca_irqen_MASK                         0x00000001
#define BCHP_SCIRQ0_SCIRQEN_sca_irqen_SHIFT                        0
#define BCHP_SCIRQ0_SCIRQEN_sca_irqen_DEFAULT                      0x00000000

/***************************************************************************
 *SCIRQSTAT - SMART CARD L2 INTERRUPT STATUS
 ***************************************************************************/
/* SCIRQ0 :: SCIRQSTAT :: reserved0 [31:02] */
#define BCHP_SCIRQ0_SCIRQSTAT_reserved0_MASK                       0xfffffffc
#define BCHP_SCIRQ0_SCIRQSTAT_reserved0_SHIFT                      2

/* SCIRQ0 :: SCIRQSTAT :: scbirq [01:01] */
#define BCHP_SCIRQ0_SCIRQSTAT_scbirq_MASK                          0x00000002
#define BCHP_SCIRQ0_SCIRQSTAT_scbirq_SHIFT                         1
#define BCHP_SCIRQ0_SCIRQSTAT_scbirq_DEFAULT                       0x00000000

/* SCIRQ0 :: SCIRQSTAT :: scairq [00:00] */
#define BCHP_SCIRQ0_SCIRQSTAT_scairq_MASK                          0x00000001
#define BCHP_SCIRQ0_SCIRQSTAT_scairq_SHIFT                         0
#define BCHP_SCIRQ0_SCIRQSTAT_scairq_DEFAULT                       0x00000000

#endif /* #ifndef BCHP_SCIRQ0_H__ */

/* End of File */

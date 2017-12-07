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

#ifndef BCHP_XPT_RAVE_ITB_LOWER_THRESH_CX00_31_L2_INTR_H__
#define BCHP_XPT_RAVE_ITB_LOWER_THRESH_CX00_31_L2_INTR_H__

/***************************************************************************
 *XPT_RAVE_ITB_LOWER_THRESH_CX00_31_L2_INTR - Context 0 to 31
 ***************************************************************************/
#define BCHP_XPT_RAVE_ITB_LOWER_THRESH_CX00_31_L2_INTR_CPU_STATUS_0_31 0x20a4f580 /* [RO][32] CPU interrupt Status Register */
#define BCHP_XPT_RAVE_ITB_LOWER_THRESH_CX00_31_L2_INTR_CPU_SET_0_31 0x20a4f584 /* [WO][32] CPU interrupt Set Register */
#define BCHP_XPT_RAVE_ITB_LOWER_THRESH_CX00_31_L2_INTR_CPU_CLEAR_0_31 0x20a4f588 /* [WO][32] CPU interrupt Clear Register */
#define BCHP_XPT_RAVE_ITB_LOWER_THRESH_CX00_31_L2_INTR_CPU_MASK_STATUS_0_31 0x20a4f58c /* [RO][32] CPU interrupt Mask Status Register */
#define BCHP_XPT_RAVE_ITB_LOWER_THRESH_CX00_31_L2_INTR_CPU_MASK_SET_0_31 0x20a4f590 /* [WO][32] CPU interrupt Mask Set Register */
#define BCHP_XPT_RAVE_ITB_LOWER_THRESH_CX00_31_L2_INTR_CPU_MASK_CLEAR_0_31 0x20a4f594 /* [WO][32] CPU interrupt Mask Clear Register */
#define BCHP_XPT_RAVE_ITB_LOWER_THRESH_CX00_31_L2_INTR_PCI_STATUS_0_31 0x20a4f598 /* [RO][32] PCI interrupt Status Register */
#define BCHP_XPT_RAVE_ITB_LOWER_THRESH_CX00_31_L2_INTR_PCI_SET_0_31 0x20a4f59c /* [WO][32] PCI interrupt Set Register */
#define BCHP_XPT_RAVE_ITB_LOWER_THRESH_CX00_31_L2_INTR_PCI_CLEAR_0_31 0x20a4f5a0 /* [WO][32] PCI interrupt Clear Register */
#define BCHP_XPT_RAVE_ITB_LOWER_THRESH_CX00_31_L2_INTR_PCI_MASK_STATUS_0_31 0x20a4f5a4 /* [RO][32] PCI interrupt Mask Status Register */
#define BCHP_XPT_RAVE_ITB_LOWER_THRESH_CX00_31_L2_INTR_PCI_MASK_SET_0_31 0x20a4f5a8 /* [WO][32] PCI interrupt Mask Set Register */
#define BCHP_XPT_RAVE_ITB_LOWER_THRESH_CX00_31_L2_INTR_PCI_MASK_CLEAR_0_31 0x20a4f5ac /* [WO][32] PCI interrupt Mask Clear Register */

#endif /* #ifndef BCHP_XPT_RAVE_ITB_LOWER_THRESH_CX00_31_L2_INTR_H__ */

/* End of File */

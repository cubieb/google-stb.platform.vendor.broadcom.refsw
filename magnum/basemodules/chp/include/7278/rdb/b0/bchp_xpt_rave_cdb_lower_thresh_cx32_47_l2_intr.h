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
 * Date:           Generated on               Thu Apr 13 10:09:29 2017
 *                 Full Compile MD5 Checksum  7f180d7646477bba2bae1a701efd9ef5
 *                     (minus title and desc)
 *                 MD5 Checksum               a2a4a53aa20c0c2f46073b879159b85d
 *
 * lock_release:   n/a
 * Compiled with:  RDB Utility                combo_header.pl
 *                 RDB.pm                     1395
 *                 unknown                    unknown
 *                 Perl Interpreter           5.008008
 *                 Operating System           linux
 *                 Script Source              tools/dvtsw/current/Linux/combo_header.pl
 *                 DVTSWVER                   LOCAL tools/dvtsw/current/Linux/combo_header.pl
 *
 *
********************************************************************************/

#ifndef BCHP_XPT_RAVE_CDB_LOWER_THRESH_CX32_47_L2_INTR_H__
#define BCHP_XPT_RAVE_CDB_LOWER_THRESH_CX32_47_L2_INTR_H__

/***************************************************************************
 *XPT_RAVE_CDB_LOWER_THRESH_CX32_47_L2_INTR - Context 32 to 47
 ***************************************************************************/
#define BCHP_XPT_RAVE_CDB_LOWER_THRESH_CX32_47_L2_INTR_CPU_STATUS_32_47 0x0225f4c0 /* [RO][32] CPU interrupt Status Register */
#define BCHP_XPT_RAVE_CDB_LOWER_THRESH_CX32_47_L2_INTR_CPU_SET_32_47 0x0225f4c4 /* [WO][32] CPU interrupt Set Register */
#define BCHP_XPT_RAVE_CDB_LOWER_THRESH_CX32_47_L2_INTR_CPU_CLEAR_32_47 0x0225f4c8 /* [WO][32] CPU interrupt Clear Register */
#define BCHP_XPT_RAVE_CDB_LOWER_THRESH_CX32_47_L2_INTR_CPU_MASK_STATUS_32_47 0x0225f4cc /* [RO][32] CPU interrupt Mask Status Register */
#define BCHP_XPT_RAVE_CDB_LOWER_THRESH_CX32_47_L2_INTR_CPU_MASK_SET_32_47 0x0225f4d0 /* [WO][32] CPU interrupt Mask Set Register */
#define BCHP_XPT_RAVE_CDB_LOWER_THRESH_CX32_47_L2_INTR_CPU_MASK_CLEAR_32_47 0x0225f4d4 /* [WO][32] CPU interrupt Mask Clear Register */
#define BCHP_XPT_RAVE_CDB_LOWER_THRESH_CX32_47_L2_INTR_PCI_STATUS_32_47 0x0225f4d8 /* [RO][32] PCI interrupt Status Register */
#define BCHP_XPT_RAVE_CDB_LOWER_THRESH_CX32_47_L2_INTR_PCI_SET_32_47 0x0225f4dc /* [WO][32] PCI interrupt Set Register */
#define BCHP_XPT_RAVE_CDB_LOWER_THRESH_CX32_47_L2_INTR_PCI_CLEAR_32_47 0x0225f4e0 /* [WO][32] PCI interrupt Clear Register */
#define BCHP_XPT_RAVE_CDB_LOWER_THRESH_CX32_47_L2_INTR_PCI_MASK_STATUS_32_47 0x0225f4e4 /* [RO][32] PCI interrupt Mask Status Register */
#define BCHP_XPT_RAVE_CDB_LOWER_THRESH_CX32_47_L2_INTR_PCI_MASK_SET_32_47 0x0225f4e8 /* [WO][32] PCI interrupt Mask Set Register */
#define BCHP_XPT_RAVE_CDB_LOWER_THRESH_CX32_47_L2_INTR_PCI_MASK_CLEAR_32_47 0x0225f4ec /* [WO][32] PCI interrupt Mask Clear Register */

#endif /* #ifndef BCHP_XPT_RAVE_CDB_LOWER_THRESH_CX32_47_L2_INTR_H__ */

/* End of File */

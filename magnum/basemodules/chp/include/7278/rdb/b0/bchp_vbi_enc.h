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
 * Date:           Generated on               Thu Apr 13 10:09:30 2017
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

#ifndef BCHP_VBI_ENC_H__
#define BCHP_VBI_ENC_H__

/***************************************************************************
 *VBI_ENC - VBI_ENC  registers
 ***************************************************************************/
#define BCHP_VBI_ENC_VBI_ANCIL_0_CORE_0_SEL      0x000ea000 /* [RW][32] Core select for VBI_ANCIL_0_CORE_0 */
#define BCHP_VBI_ENC_VBI_ANCIL_0_CORE_1_SEL      0x000ea004 /* [RW][32] Core select for VBI_ANCIL_0_CORE_1 */
#define BCHP_VBI_ENC_VBI_ANCIL_0_CORE_2_SEL      0x000ea008 /* [RW][32] Core select for VBI_ANCIL_0_CORE_2 */
#define BCHP_VBI_ENC_VBI_ANCIL_0_CORE_3_SEL      0x000ea00c /* [RW][32] Core select for VBI_ANCIL_0_CORE_3 */
#define BCHP_VBI_ENC_VBI_ANCIL_0_CORE_4_SEL      0x000ea010 /* [RW][32] Core select for VBI_ANCIL_0_CORE_4 */
#define BCHP_VBI_ENC_VBI_ANCIL_0_CORE_5_SEL      0x000ea014 /* [RW][32] Core select for VBI_ANCIL_0_CORE_5 */
#define BCHP_VBI_ENC_VBI_ANCIL_0_INTR_CTRL       0x000ea018 /* [RW][32] for Interrupt control for VBI_ANCIL_0 */
#define BCHP_VBI_ENC_VBI_ANCIL_0_PASS_THROUGH    0x000ea01c /* [RW][32] Video Encoder VBI_ANCIL_0  Pass through Control for Top Field */

/***************************************************************************
 *VBI_ANCIL_0_CORE_0_SEL - Core select for VBI_ANCIL_0_CORE_0
 ***************************************************************************/
/* VBI_ENC :: VBI_ANCIL_0_CORE_0_SEL :: reserved0 [31:03] */
#define BCHP_VBI_ENC_VBI_ANCIL_0_CORE_0_SEL_reserved0_MASK         0xfffffff8
#define BCHP_VBI_ENC_VBI_ANCIL_0_CORE_0_SEL_reserved0_SHIFT        3

/* VBI_ENC :: VBI_ANCIL_0_CORE_0_SEL :: SEL [02:00] */
#define BCHP_VBI_ENC_VBI_ANCIL_0_CORE_0_SEL_SEL_MASK               0x00000007
#define BCHP_VBI_ENC_VBI_ANCIL_0_CORE_0_SEL_SEL_SHIFT              0
#define BCHP_VBI_ENC_VBI_ANCIL_0_CORE_0_SEL_SEL_DEFAULT            0x00000006
#define BCHP_VBI_ENC_VBI_ANCIL_0_CORE_0_SEL_SEL_CCE_ANCIL_0        0
#define BCHP_VBI_ENC_VBI_ANCIL_0_CORE_0_SEL_SEL_WSE_ANCIL_0        1
#define BCHP_VBI_ENC_VBI_ANCIL_0_CORE_0_SEL_SEL_TTE_ANCIL_0        2
#define BCHP_VBI_ENC_VBI_ANCIL_0_CORE_0_SEL_SEL_GSE_ANCIL_0        3
#define BCHP_VBI_ENC_VBI_ANCIL_0_CORE_0_SEL_SEL_AMOLE_ANCIL_0      4
#define BCHP_VBI_ENC_VBI_ANCIL_0_CORE_0_SEL_SEL_PASSTHRU_ANCIL_0   5
#define BCHP_VBI_ENC_VBI_ANCIL_0_CORE_0_SEL_SEL_DISABLE            6

/***************************************************************************
 *VBI_ANCIL_0_CORE_1_SEL - Core select for VBI_ANCIL_0_CORE_1
 ***************************************************************************/
/* VBI_ENC :: VBI_ANCIL_0_CORE_1_SEL :: reserved0 [31:03] */
#define BCHP_VBI_ENC_VBI_ANCIL_0_CORE_1_SEL_reserved0_MASK         0xfffffff8
#define BCHP_VBI_ENC_VBI_ANCIL_0_CORE_1_SEL_reserved0_SHIFT        3

/* VBI_ENC :: VBI_ANCIL_0_CORE_1_SEL :: SEL [02:00] */
#define BCHP_VBI_ENC_VBI_ANCIL_0_CORE_1_SEL_SEL_MASK               0x00000007
#define BCHP_VBI_ENC_VBI_ANCIL_0_CORE_1_SEL_SEL_SHIFT              0
#define BCHP_VBI_ENC_VBI_ANCIL_0_CORE_1_SEL_SEL_DEFAULT            0x00000006
#define BCHP_VBI_ENC_VBI_ANCIL_0_CORE_1_SEL_SEL_CCE_ANCIL_0        0
#define BCHP_VBI_ENC_VBI_ANCIL_0_CORE_1_SEL_SEL_WSE_ANCIL_0        1
#define BCHP_VBI_ENC_VBI_ANCIL_0_CORE_1_SEL_SEL_TTE_ANCIL_0        2
#define BCHP_VBI_ENC_VBI_ANCIL_0_CORE_1_SEL_SEL_GSE_ANCIL_0        3
#define BCHP_VBI_ENC_VBI_ANCIL_0_CORE_1_SEL_SEL_AMOLE_ANCIL_0      4
#define BCHP_VBI_ENC_VBI_ANCIL_0_CORE_1_SEL_SEL_PASSTHRU_ANCIL_0   5
#define BCHP_VBI_ENC_VBI_ANCIL_0_CORE_1_SEL_SEL_DISABLE            6

/***************************************************************************
 *VBI_ANCIL_0_CORE_2_SEL - Core select for VBI_ANCIL_0_CORE_2
 ***************************************************************************/
/* VBI_ENC :: VBI_ANCIL_0_CORE_2_SEL :: reserved0 [31:03] */
#define BCHP_VBI_ENC_VBI_ANCIL_0_CORE_2_SEL_reserved0_MASK         0xfffffff8
#define BCHP_VBI_ENC_VBI_ANCIL_0_CORE_2_SEL_reserved0_SHIFT        3

/* VBI_ENC :: VBI_ANCIL_0_CORE_2_SEL :: SEL [02:00] */
#define BCHP_VBI_ENC_VBI_ANCIL_0_CORE_2_SEL_SEL_MASK               0x00000007
#define BCHP_VBI_ENC_VBI_ANCIL_0_CORE_2_SEL_SEL_SHIFT              0
#define BCHP_VBI_ENC_VBI_ANCIL_0_CORE_2_SEL_SEL_DEFAULT            0x00000006
#define BCHP_VBI_ENC_VBI_ANCIL_0_CORE_2_SEL_SEL_CCE_ANCIL_0        0
#define BCHP_VBI_ENC_VBI_ANCIL_0_CORE_2_SEL_SEL_WSE_ANCIL_0        1
#define BCHP_VBI_ENC_VBI_ANCIL_0_CORE_2_SEL_SEL_TTE_ANCIL_0        2
#define BCHP_VBI_ENC_VBI_ANCIL_0_CORE_2_SEL_SEL_GSE_ANCIL_0        3
#define BCHP_VBI_ENC_VBI_ANCIL_0_CORE_2_SEL_SEL_AMOLE_ANCIL_0      4
#define BCHP_VBI_ENC_VBI_ANCIL_0_CORE_2_SEL_SEL_PASSTHRU_ANCIL_0   5
#define BCHP_VBI_ENC_VBI_ANCIL_0_CORE_2_SEL_SEL_DISABLE            6

/***************************************************************************
 *VBI_ANCIL_0_CORE_3_SEL - Core select for VBI_ANCIL_0_CORE_3
 ***************************************************************************/
/* VBI_ENC :: VBI_ANCIL_0_CORE_3_SEL :: reserved0 [31:03] */
#define BCHP_VBI_ENC_VBI_ANCIL_0_CORE_3_SEL_reserved0_MASK         0xfffffff8
#define BCHP_VBI_ENC_VBI_ANCIL_0_CORE_3_SEL_reserved0_SHIFT        3

/* VBI_ENC :: VBI_ANCIL_0_CORE_3_SEL :: SEL [02:00] */
#define BCHP_VBI_ENC_VBI_ANCIL_0_CORE_3_SEL_SEL_MASK               0x00000007
#define BCHP_VBI_ENC_VBI_ANCIL_0_CORE_3_SEL_SEL_SHIFT              0
#define BCHP_VBI_ENC_VBI_ANCIL_0_CORE_3_SEL_SEL_DEFAULT            0x00000006
#define BCHP_VBI_ENC_VBI_ANCIL_0_CORE_3_SEL_SEL_CCE_ANCIL_0        0
#define BCHP_VBI_ENC_VBI_ANCIL_0_CORE_3_SEL_SEL_WSE_ANCIL_0        1
#define BCHP_VBI_ENC_VBI_ANCIL_0_CORE_3_SEL_SEL_TTE_ANCIL_0        2
#define BCHP_VBI_ENC_VBI_ANCIL_0_CORE_3_SEL_SEL_GSE_ANCIL_0        3
#define BCHP_VBI_ENC_VBI_ANCIL_0_CORE_3_SEL_SEL_AMOLE_ANCIL_0      4
#define BCHP_VBI_ENC_VBI_ANCIL_0_CORE_3_SEL_SEL_PASSTHRU_ANCIL_0   5
#define BCHP_VBI_ENC_VBI_ANCIL_0_CORE_3_SEL_SEL_DISABLE            6

/***************************************************************************
 *VBI_ANCIL_0_CORE_4_SEL - Core select for VBI_ANCIL_0_CORE_4
 ***************************************************************************/
/* VBI_ENC :: VBI_ANCIL_0_CORE_4_SEL :: reserved0 [31:03] */
#define BCHP_VBI_ENC_VBI_ANCIL_0_CORE_4_SEL_reserved0_MASK         0xfffffff8
#define BCHP_VBI_ENC_VBI_ANCIL_0_CORE_4_SEL_reserved0_SHIFT        3

/* VBI_ENC :: VBI_ANCIL_0_CORE_4_SEL :: SEL [02:00] */
#define BCHP_VBI_ENC_VBI_ANCIL_0_CORE_4_SEL_SEL_MASK               0x00000007
#define BCHP_VBI_ENC_VBI_ANCIL_0_CORE_4_SEL_SEL_SHIFT              0
#define BCHP_VBI_ENC_VBI_ANCIL_0_CORE_4_SEL_SEL_DEFAULT            0x00000006
#define BCHP_VBI_ENC_VBI_ANCIL_0_CORE_4_SEL_SEL_CCE_ANCIL_0        0
#define BCHP_VBI_ENC_VBI_ANCIL_0_CORE_4_SEL_SEL_WSE_ANCIL_0        1
#define BCHP_VBI_ENC_VBI_ANCIL_0_CORE_4_SEL_SEL_TTE_ANCIL_0        2
#define BCHP_VBI_ENC_VBI_ANCIL_0_CORE_4_SEL_SEL_GSE_ANCIL_0        3
#define BCHP_VBI_ENC_VBI_ANCIL_0_CORE_4_SEL_SEL_AMOLE_ANCIL_0      4
#define BCHP_VBI_ENC_VBI_ANCIL_0_CORE_4_SEL_SEL_PASSTHRU_ANCIL_0   5
#define BCHP_VBI_ENC_VBI_ANCIL_0_CORE_4_SEL_SEL_DISABLE            6

/***************************************************************************
 *VBI_ANCIL_0_CORE_5_SEL - Core select for VBI_ANCIL_0_CORE_5
 ***************************************************************************/
/* VBI_ENC :: VBI_ANCIL_0_CORE_5_SEL :: reserved0 [31:03] */
#define BCHP_VBI_ENC_VBI_ANCIL_0_CORE_5_SEL_reserved0_MASK         0xfffffff8
#define BCHP_VBI_ENC_VBI_ANCIL_0_CORE_5_SEL_reserved0_SHIFT        3

/* VBI_ENC :: VBI_ANCIL_0_CORE_5_SEL :: SEL [02:00] */
#define BCHP_VBI_ENC_VBI_ANCIL_0_CORE_5_SEL_SEL_MASK               0x00000007
#define BCHP_VBI_ENC_VBI_ANCIL_0_CORE_5_SEL_SEL_SHIFT              0
#define BCHP_VBI_ENC_VBI_ANCIL_0_CORE_5_SEL_SEL_DEFAULT            0x00000006
#define BCHP_VBI_ENC_VBI_ANCIL_0_CORE_5_SEL_SEL_CCE_ANCIL_0        0
#define BCHP_VBI_ENC_VBI_ANCIL_0_CORE_5_SEL_SEL_WSE_ANCIL_0        1
#define BCHP_VBI_ENC_VBI_ANCIL_0_CORE_5_SEL_SEL_TTE_ANCIL_0        2
#define BCHP_VBI_ENC_VBI_ANCIL_0_CORE_5_SEL_SEL_GSE_ANCIL_0        3
#define BCHP_VBI_ENC_VBI_ANCIL_0_CORE_5_SEL_SEL_AMOLE_ANCIL_0      4
#define BCHP_VBI_ENC_VBI_ANCIL_0_CORE_5_SEL_SEL_PASSTHRU_ANCIL_0   5
#define BCHP_VBI_ENC_VBI_ANCIL_0_CORE_5_SEL_SEL_DISABLE            6

/***************************************************************************
 *VBI_ANCIL_0_INTR_CTRL - for Interrupt control for VBI_ANCIL_0
 ***************************************************************************/
/* VBI_ENC :: VBI_ANCIL_0_INTR_CTRL :: reserved_for_eco0 [31:28] */
#define BCHP_VBI_ENC_VBI_ANCIL_0_INTR_CTRL_reserved_for_eco0_MASK  0xf0000000
#define BCHP_VBI_ENC_VBI_ANCIL_0_INTR_CTRL_reserved_for_eco0_SHIFT 28
#define BCHP_VBI_ENC_VBI_ANCIL_0_INTR_CTRL_reserved_for_eco0_DEFAULT 0x00000000

/* VBI_ENC :: VBI_ANCIL_0_INTR_CTRL :: INTR1_LINE [27:16] */
#define BCHP_VBI_ENC_VBI_ANCIL_0_INTR_CTRL_INTR1_LINE_MASK         0x0fff0000
#define BCHP_VBI_ENC_VBI_ANCIL_0_INTR_CTRL_INTR1_LINE_SHIFT        16
#define BCHP_VBI_ENC_VBI_ANCIL_0_INTR_CTRL_INTR1_LINE_DEFAULT      0x00000000

/* VBI_ENC :: VBI_ANCIL_0_INTR_CTRL :: reserved_for_eco1 [15:12] */
#define BCHP_VBI_ENC_VBI_ANCIL_0_INTR_CTRL_reserved_for_eco1_MASK  0x0000f000
#define BCHP_VBI_ENC_VBI_ANCIL_0_INTR_CTRL_reserved_for_eco1_SHIFT 12
#define BCHP_VBI_ENC_VBI_ANCIL_0_INTR_CTRL_reserved_for_eco1_DEFAULT 0x00000000

/* VBI_ENC :: VBI_ANCIL_0_INTR_CTRL :: INTR0_LINE [11:00] */
#define BCHP_VBI_ENC_VBI_ANCIL_0_INTR_CTRL_INTR0_LINE_MASK         0x00000fff
#define BCHP_VBI_ENC_VBI_ANCIL_0_INTR_CTRL_INTR0_LINE_SHIFT        0
#define BCHP_VBI_ENC_VBI_ANCIL_0_INTR_CTRL_INTR0_LINE_DEFAULT      0x00000000

/***************************************************************************
 *VBI_ANCIL_0_PASS_THROUGH - Video Encoder VBI_ANCIL_0  Pass through Control for Top Field
 ***************************************************************************/
/* VBI_ENC :: VBI_ANCIL_0_PASS_THROUGH :: reserved0 [31:30] */
#define BCHP_VBI_ENC_VBI_ANCIL_0_PASS_THROUGH_reserved0_MASK       0xc0000000
#define BCHP_VBI_ENC_VBI_ANCIL_0_PASS_THROUGH_reserved0_SHIFT      30

/* VBI_ENC :: VBI_ANCIL_0_PASS_THROUGH :: MULT [29:22] */
#define BCHP_VBI_ENC_VBI_ANCIL_0_PASS_THROUGH_MULT_MASK            0x3fc00000
#define BCHP_VBI_ENC_VBI_ANCIL_0_PASS_THROUGH_MULT_SHIFT           22
#define BCHP_VBI_ENC_VBI_ANCIL_0_PASS_THROUGH_MULT_DEFAULT         0x000000ff

/* VBI_ENC :: VBI_ANCIL_0_PASS_THROUGH :: LINE_START [21:11] */
#define BCHP_VBI_ENC_VBI_ANCIL_0_PASS_THROUGH_LINE_START_MASK      0x003ff800
#define BCHP_VBI_ENC_VBI_ANCIL_0_PASS_THROUGH_LINE_START_SHIFT     11
#define BCHP_VBI_ENC_VBI_ANCIL_0_PASS_THROUGH_LINE_START_DEFAULT   0x00000014

/* VBI_ENC :: VBI_ANCIL_0_PASS_THROUGH :: COUNT [10:00] */
#define BCHP_VBI_ENC_VBI_ANCIL_0_PASS_THROUGH_COUNT_MASK           0x000007ff
#define BCHP_VBI_ENC_VBI_ANCIL_0_PASS_THROUGH_COUNT_SHIFT          0
#define BCHP_VBI_ENC_VBI_ANCIL_0_PASS_THROUGH_COUNT_DEFAULT        0x00000000

#endif /* #ifndef BCHP_VBI_ENC_H__ */

/* End of File */

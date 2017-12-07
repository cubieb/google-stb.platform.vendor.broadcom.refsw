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

#ifndef BCHP_AUD_FMM_IOP_OUT_I2S_0_H__
#define BCHP_AUD_FMM_IOP_OUT_I2S_0_H__

/***************************************************************************
 *AUD_FMM_IOP_OUT_I2S_0
 ***************************************************************************/
#define BCHP_AUD_FMM_IOP_OUT_I2S_0_STREAM_CFG_0  0x010b0000 /* [RW][32] Stream configuration */
#define BCHP_AUD_FMM_IOP_OUT_I2S_0_I2S_CFG       0x010b0004 /* [RW][32] I2S formatter configuration */
#define BCHP_AUD_FMM_IOP_OUT_I2S_0_I2S_CROSSBAR  0x010b0008 /* [RW][32] I2S crossbar control */
#define BCHP_AUD_FMM_IOP_OUT_I2S_0_MCLK_CFG_0    0x010b000c /* [RW][32] I2S MCLK configuration */
#define BCHP_AUD_FMM_IOP_OUT_I2S_0_SAMPLE_COUNT  0x010b0010 /* [RO][32] I2S Sample Counter */
#define BCHP_AUD_FMM_IOP_OUT_I2S_0_THRESHOLD_SAMPLE_COUNT 0x010b0014 /* [RW][32] I2S Threshold Sample Count */
#define BCHP_AUD_FMM_IOP_OUT_I2S_0_SAMPLE_COUNT_CTRL 0x010b0018 /* [RW][32] I2S Sample Counter Control */
#define BCHP_AUD_FMM_IOP_OUT_I2S_0_I2S_LEGACY    0x010b001c /* [RW][32] Legacy Master Mode I2S Transmitter */
#define BCHP_AUD_FMM_IOP_OUT_I2S_0_ESR_STATUS    0x010b0020 /* [RO][32] Error Status Register */
#define BCHP_AUD_FMM_IOP_OUT_I2S_0_ESR_STATUS_SET 0x010b0024 /* [WO][32] Error Set Register */
#define BCHP_AUD_FMM_IOP_OUT_I2S_0_ESR_STATUS_CLEAR 0x010b0028 /* [WO][32] Error Clear Register */
#define BCHP_AUD_FMM_IOP_OUT_I2S_0_ESR_MASK      0x010b002c /* [RO][32] Mask Status Register */
#define BCHP_AUD_FMM_IOP_OUT_I2S_0_ESR_MASK_SET  0x010b0030 /* [WO][32] Mask Set Register */
#define BCHP_AUD_FMM_IOP_OUT_I2S_0_ESR_MASK_CLEAR 0x010b0034 /* [WO][32] Mask Clear Register */

/***************************************************************************
 *STREAM_CFG_0 - Stream configuration
 ***************************************************************************/
/* AUD_FMM_IOP_OUT_I2S_0 :: STREAM_CFG_0 :: ENA [31:31] */
#define BCHP_AUD_FMM_IOP_OUT_I2S_0_STREAM_CFG_0_ENA_MASK           0x80000000
#define BCHP_AUD_FMM_IOP_OUT_I2S_0_STREAM_CFG_0_ENA_SHIFT          31
#define BCHP_AUD_FMM_IOP_OUT_I2S_0_STREAM_CFG_0_ENA_DEFAULT        0x00000000

/* AUD_FMM_IOP_OUT_I2S_0 :: STREAM_CFG_0 :: reserved0 [30:28] */
#define BCHP_AUD_FMM_IOP_OUT_I2S_0_STREAM_CFG_0_reserved0_MASK     0x70000000
#define BCHP_AUD_FMM_IOP_OUT_I2S_0_STREAM_CFG_0_reserved0_SHIFT    28

/* AUD_FMM_IOP_OUT_I2S_0 :: STREAM_CFG_0 :: CHANNEL_GROUPING [27:24] */
#define BCHP_AUD_FMM_IOP_OUT_I2S_0_STREAM_CFG_0_CHANNEL_GROUPING_MASK 0x0f000000
#define BCHP_AUD_FMM_IOP_OUT_I2S_0_STREAM_CFG_0_CHANNEL_GROUPING_SHIFT 24
#define BCHP_AUD_FMM_IOP_OUT_I2S_0_STREAM_CFG_0_CHANNEL_GROUPING_DEFAULT 0x00000001

/* AUD_FMM_IOP_OUT_I2S_0 :: STREAM_CFG_0 :: GROUP_ID [23:20] */
#define BCHP_AUD_FMM_IOP_OUT_I2S_0_STREAM_CFG_0_GROUP_ID_MASK      0x00f00000
#define BCHP_AUD_FMM_IOP_OUT_I2S_0_STREAM_CFG_0_GROUP_ID_SHIFT     20
#define BCHP_AUD_FMM_IOP_OUT_I2S_0_STREAM_CFG_0_GROUP_ID_DEFAULT   0x00000000

/* AUD_FMM_IOP_OUT_I2S_0 :: STREAM_CFG_0 :: STREAM_BIT_RESOLUTION [19:16] */
#define BCHP_AUD_FMM_IOP_OUT_I2S_0_STREAM_CFG_0_STREAM_BIT_RESOLUTION_MASK 0x000f0000
#define BCHP_AUD_FMM_IOP_OUT_I2S_0_STREAM_CFG_0_STREAM_BIT_RESOLUTION_SHIFT 16
#define BCHP_AUD_FMM_IOP_OUT_I2S_0_STREAM_CFG_0_STREAM_BIT_RESOLUTION_DEFAULT 0x00000008
#define BCHP_AUD_FMM_IOP_OUT_I2S_0_STREAM_CFG_0_STREAM_BIT_RESOLUTION_Res_16_Bit 0
#define BCHP_AUD_FMM_IOP_OUT_I2S_0_STREAM_CFG_0_STREAM_BIT_RESOLUTION_Res_17_Bit 1
#define BCHP_AUD_FMM_IOP_OUT_I2S_0_STREAM_CFG_0_STREAM_BIT_RESOLUTION_Res_18_Bit 2
#define BCHP_AUD_FMM_IOP_OUT_I2S_0_STREAM_CFG_0_STREAM_BIT_RESOLUTION_Res_19_Bit 3
#define BCHP_AUD_FMM_IOP_OUT_I2S_0_STREAM_CFG_0_STREAM_BIT_RESOLUTION_Res_20_Bit 4
#define BCHP_AUD_FMM_IOP_OUT_I2S_0_STREAM_CFG_0_STREAM_BIT_RESOLUTION_Res_21_Bit 5
#define BCHP_AUD_FMM_IOP_OUT_I2S_0_STREAM_CFG_0_STREAM_BIT_RESOLUTION_Res_22_Bit 6
#define BCHP_AUD_FMM_IOP_OUT_I2S_0_STREAM_CFG_0_STREAM_BIT_RESOLUTION_Res_23_Bit 7
#define BCHP_AUD_FMM_IOP_OUT_I2S_0_STREAM_CFG_0_STREAM_BIT_RESOLUTION_Res_24_Bit 8

/* AUD_FMM_IOP_OUT_I2S_0 :: STREAM_CFG_0 :: WAIT_FOR_VALID [15:15] */
#define BCHP_AUD_FMM_IOP_OUT_I2S_0_STREAM_CFG_0_WAIT_FOR_VALID_MASK 0x00008000
#define BCHP_AUD_FMM_IOP_OUT_I2S_0_STREAM_CFG_0_WAIT_FOR_VALID_SHIFT 15
#define BCHP_AUD_FMM_IOP_OUT_I2S_0_STREAM_CFG_0_WAIT_FOR_VALID_DEFAULT 0x00000000
#define BCHP_AUD_FMM_IOP_OUT_I2S_0_STREAM_CFG_0_WAIT_FOR_VALID_Holdoff_request 1
#define BCHP_AUD_FMM_IOP_OUT_I2S_0_STREAM_CFG_0_WAIT_FOR_VALID_Keep_requesting 0

/* AUD_FMM_IOP_OUT_I2S_0 :: STREAM_CFG_0 :: IGNORE_FIRST_UNDERFLOW [14:14] */
#define BCHP_AUD_FMM_IOP_OUT_I2S_0_STREAM_CFG_0_IGNORE_FIRST_UNDERFLOW_MASK 0x00004000
#define BCHP_AUD_FMM_IOP_OUT_I2S_0_STREAM_CFG_0_IGNORE_FIRST_UNDERFLOW_SHIFT 14
#define BCHP_AUD_FMM_IOP_OUT_I2S_0_STREAM_CFG_0_IGNORE_FIRST_UNDERFLOW_DEFAULT 0x00000001
#define BCHP_AUD_FMM_IOP_OUT_I2S_0_STREAM_CFG_0_IGNORE_FIRST_UNDERFLOW_Ignore 1
#define BCHP_AUD_FMM_IOP_OUT_I2S_0_STREAM_CFG_0_IGNORE_FIRST_UNDERFLOW_Dont_ignore 0

/* AUD_FMM_IOP_OUT_I2S_0 :: STREAM_CFG_0 :: INIT_SM [13:13] */
#define BCHP_AUD_FMM_IOP_OUT_I2S_0_STREAM_CFG_0_INIT_SM_MASK       0x00002000
#define BCHP_AUD_FMM_IOP_OUT_I2S_0_STREAM_CFG_0_INIT_SM_SHIFT      13
#define BCHP_AUD_FMM_IOP_OUT_I2S_0_STREAM_CFG_0_INIT_SM_DEFAULT    0x00000000
#define BCHP_AUD_FMM_IOP_OUT_I2S_0_STREAM_CFG_0_INIT_SM_Init       1
#define BCHP_AUD_FMM_IOP_OUT_I2S_0_STREAM_CFG_0_INIT_SM_Normal     0

/* AUD_FMM_IOP_OUT_I2S_0 :: STREAM_CFG_0 :: INS_INVAL [12:12] */
#define BCHP_AUD_FMM_IOP_OUT_I2S_0_STREAM_CFG_0_INS_INVAL_MASK     0x00001000
#define BCHP_AUD_FMM_IOP_OUT_I2S_0_STREAM_CFG_0_INS_INVAL_SHIFT    12
#define BCHP_AUD_FMM_IOP_OUT_I2S_0_STREAM_CFG_0_INS_INVAL_DEFAULT  0x00000000
#define BCHP_AUD_FMM_IOP_OUT_I2S_0_STREAM_CFG_0_INS_INVAL_Invalid  1
#define BCHP_AUD_FMM_IOP_OUT_I2S_0_STREAM_CFG_0_INS_INVAL_Valid    0

/* AUD_FMM_IOP_OUT_I2S_0 :: STREAM_CFG_0 :: reserved1 [11:10] */
#define BCHP_AUD_FMM_IOP_OUT_I2S_0_STREAM_CFG_0_reserved1_MASK     0x00000c00
#define BCHP_AUD_FMM_IOP_OUT_I2S_0_STREAM_CFG_0_reserved1_SHIFT    10

/* AUD_FMM_IOP_OUT_I2S_0 :: STREAM_CFG_0 :: FCI_ID [09:00] */
#define BCHP_AUD_FMM_IOP_OUT_I2S_0_STREAM_CFG_0_FCI_ID_MASK        0x000003ff
#define BCHP_AUD_FMM_IOP_OUT_I2S_0_STREAM_CFG_0_FCI_ID_SHIFT       0
#define BCHP_AUD_FMM_IOP_OUT_I2S_0_STREAM_CFG_0_FCI_ID_DEFAULT     0x000003ff

/***************************************************************************
 *I2S_CFG - I2S formatter configuration
 ***************************************************************************/
/* AUD_FMM_IOP_OUT_I2S_0 :: I2S_CFG :: TDM_MODE [31:31] */
#define BCHP_AUD_FMM_IOP_OUT_I2S_0_I2S_CFG_TDM_MODE_MASK           0x80000000
#define BCHP_AUD_FMM_IOP_OUT_I2S_0_I2S_CFG_TDM_MODE_SHIFT          31
#define BCHP_AUD_FMM_IOP_OUT_I2S_0_I2S_CFG_TDM_MODE_DEFAULT        0x00000000
#define BCHP_AUD_FMM_IOP_OUT_I2S_0_I2S_CFG_TDM_MODE_TDM_MODE       1
#define BCHP_AUD_FMM_IOP_OUT_I2S_0_I2S_CFG_TDM_MODE_I2S_MODE       0

/* AUD_FMM_IOP_OUT_I2S_0 :: I2S_CFG :: SLAVE_MODE [30:30] */
#define BCHP_AUD_FMM_IOP_OUT_I2S_0_I2S_CFG_SLAVE_MODE_MASK         0x40000000
#define BCHP_AUD_FMM_IOP_OUT_I2S_0_I2S_CFG_SLAVE_MODE_SHIFT        30
#define BCHP_AUD_FMM_IOP_OUT_I2S_0_I2S_CFG_SLAVE_MODE_DEFAULT      0x00000000
#define BCHP_AUD_FMM_IOP_OUT_I2S_0_I2S_CFG_SLAVE_MODE_SLAVE_MODE   1
#define BCHP_AUD_FMM_IOP_OUT_I2S_0_I2S_CFG_SLAVE_MODE_MASTER_MODE  0

/* AUD_FMM_IOP_OUT_I2S_0 :: I2S_CFG :: SCLKS_PER_1FS_DIV32 [29:26] */
#define BCHP_AUD_FMM_IOP_OUT_I2S_0_I2S_CFG_SCLKS_PER_1FS_DIV32_MASK 0x3c000000
#define BCHP_AUD_FMM_IOP_OUT_I2S_0_I2S_CFG_SCLKS_PER_1FS_DIV32_SHIFT 26
#define BCHP_AUD_FMM_IOP_OUT_I2S_0_I2S_CFG_SCLKS_PER_1FS_DIV32_DEFAULT 0x00000002
#define BCHP_AUD_FMM_IOP_OUT_I2S_0_I2S_CFG_SCLKS_PER_1FS_DIV32_512_SCLK 0
#define BCHP_AUD_FMM_IOP_OUT_I2S_0_I2S_CFG_SCLKS_PER_1FS_DIV32_384_SCLK 12
#define BCHP_AUD_FMM_IOP_OUT_I2S_0_I2S_CFG_SCLKS_PER_1FS_DIV32_256_SCLK 8
#define BCHP_AUD_FMM_IOP_OUT_I2S_0_I2S_CFG_SCLKS_PER_1FS_DIV32_128_SCLK 4
#define BCHP_AUD_FMM_IOP_OUT_I2S_0_I2S_CFG_SCLKS_PER_1FS_DIV32_64_SCLK 2
#define BCHP_AUD_FMM_IOP_OUT_I2S_0_I2S_CFG_SCLKS_PER_1FS_DIV32_32_SCLK 1

/* AUD_FMM_IOP_OUT_I2S_0 :: I2S_CFG :: FSYNC_WIDTH [25:18] */
#define BCHP_AUD_FMM_IOP_OUT_I2S_0_I2S_CFG_FSYNC_WIDTH_MASK        0x03fc0000
#define BCHP_AUD_FMM_IOP_OUT_I2S_0_I2S_CFG_FSYNC_WIDTH_SHIFT       18
#define BCHP_AUD_FMM_IOP_OUT_I2S_0_I2S_CFG_FSYNC_WIDTH_DEFAULT     0x00000001
#define BCHP_AUD_FMM_IOP_OUT_I2S_0_I2S_CFG_FSYNC_WIDTH_256_SCLK    0
#define BCHP_AUD_FMM_IOP_OUT_I2S_0_I2S_CFG_FSYNC_WIDTH_255_SCLK    255
#define BCHP_AUD_FMM_IOP_OUT_I2S_0_I2S_CFG_FSYNC_WIDTH_254_SCLK    254
#define BCHP_AUD_FMM_IOP_OUT_I2S_0_I2S_CFG_FSYNC_WIDTH_2_SCLK      2
#define BCHP_AUD_FMM_IOP_OUT_I2S_0_I2S_CFG_FSYNC_WIDTH_1_SCLK      1

/* AUD_FMM_IOP_OUT_I2S_0 :: I2S_CFG :: VALID_SLOT [17:14] */
#define BCHP_AUD_FMM_IOP_OUT_I2S_0_I2S_CFG_VALID_SLOT_MASK         0x0003c000
#define BCHP_AUD_FMM_IOP_OUT_I2S_0_I2S_CFG_VALID_SLOT_SHIFT        14
#define BCHP_AUD_FMM_IOP_OUT_I2S_0_I2S_CFG_VALID_SLOT_DEFAULT      0x00000001
#define BCHP_AUD_FMM_IOP_OUT_I2S_0_I2S_CFG_VALID_SLOT_32_Slots     0
#define BCHP_AUD_FMM_IOP_OUT_I2S_0_I2S_CFG_VALID_SLOT_30_Slots     15
#define BCHP_AUD_FMM_IOP_OUT_I2S_0_I2S_CFG_VALID_SLOT_28_Slots     14
#define BCHP_AUD_FMM_IOP_OUT_I2S_0_I2S_CFG_VALID_SLOT_26_Slots     13
#define BCHP_AUD_FMM_IOP_OUT_I2S_0_I2S_CFG_VALID_SLOT_10_Slots     5
#define BCHP_AUD_FMM_IOP_OUT_I2S_0_I2S_CFG_VALID_SLOT_8_Slots      4
#define BCHP_AUD_FMM_IOP_OUT_I2S_0_I2S_CFG_VALID_SLOT_6_Slots      3
#define BCHP_AUD_FMM_IOP_OUT_I2S_0_I2S_CFG_VALID_SLOT_4_Slots      2
#define BCHP_AUD_FMM_IOP_OUT_I2S_0_I2S_CFG_VALID_SLOT_2_Slots      1

/* AUD_FMM_IOP_OUT_I2S_0 :: I2S_CFG :: BITS_PER_SLOT [13:13] */
#define BCHP_AUD_FMM_IOP_OUT_I2S_0_I2S_CFG_BITS_PER_SLOT_MASK      0x00002000
#define BCHP_AUD_FMM_IOP_OUT_I2S_0_I2S_CFG_BITS_PER_SLOT_SHIFT     13
#define BCHP_AUD_FMM_IOP_OUT_I2S_0_I2S_CFG_BITS_PER_SLOT_DEFAULT   0x00000000
#define BCHP_AUD_FMM_IOP_OUT_I2S_0_I2S_CFG_BITS_PER_SLOT_16_Bits   1
#define BCHP_AUD_FMM_IOP_OUT_I2S_0_I2S_CFG_BITS_PER_SLOT_32_Bits   0

/* AUD_FMM_IOP_OUT_I2S_0 :: I2S_CFG :: BITS_PER_SAMPLE [12:08] */
#define BCHP_AUD_FMM_IOP_OUT_I2S_0_I2S_CFG_BITS_PER_SAMPLE_MASK    0x00001f00
#define BCHP_AUD_FMM_IOP_OUT_I2S_0_I2S_CFG_BITS_PER_SAMPLE_SHIFT   8
#define BCHP_AUD_FMM_IOP_OUT_I2S_0_I2S_CFG_BITS_PER_SAMPLE_DEFAULT 0x00000018
#define BCHP_AUD_FMM_IOP_OUT_I2S_0_I2S_CFG_BITS_PER_SAMPLE_Bitwidth24 24
#define BCHP_AUD_FMM_IOP_OUT_I2S_0_I2S_CFG_BITS_PER_SAMPLE_Bitwidth20 20
#define BCHP_AUD_FMM_IOP_OUT_I2S_0_I2S_CFG_BITS_PER_SAMPLE_Bitwidth18 18
#define BCHP_AUD_FMM_IOP_OUT_I2S_0_I2S_CFG_BITS_PER_SAMPLE_Bitwidth16 16
#define BCHP_AUD_FMM_IOP_OUT_I2S_0_I2S_CFG_BITS_PER_SAMPLE_Bitwidth12 12
#define BCHP_AUD_FMM_IOP_OUT_I2S_0_I2S_CFG_BITS_PER_SAMPLE_Bitwidth01 1

/* AUD_FMM_IOP_OUT_I2S_0 :: I2S_CFG :: DATA_JUSTIFICATION [07:07] */
#define BCHP_AUD_FMM_IOP_OUT_I2S_0_I2S_CFG_DATA_JUSTIFICATION_MASK 0x00000080
#define BCHP_AUD_FMM_IOP_OUT_I2S_0_I2S_CFG_DATA_JUSTIFICATION_SHIFT 7
#define BCHP_AUD_FMM_IOP_OUT_I2S_0_I2S_CFG_DATA_JUSTIFICATION_DEFAULT 0x00000000
#define BCHP_AUD_FMM_IOP_OUT_I2S_0_I2S_CFG_DATA_JUSTIFICATION_LSB  1
#define BCHP_AUD_FMM_IOP_OUT_I2S_0_I2S_CFG_DATA_JUSTIFICATION_MSB  0

/* AUD_FMM_IOP_OUT_I2S_0 :: I2S_CFG :: DATA_ALIGNMENT [06:06] */
#define BCHP_AUD_FMM_IOP_OUT_I2S_0_I2S_CFG_DATA_ALIGNMENT_MASK     0x00000040
#define BCHP_AUD_FMM_IOP_OUT_I2S_0_I2S_CFG_DATA_ALIGNMENT_SHIFT    6
#define BCHP_AUD_FMM_IOP_OUT_I2S_0_I2S_CFG_DATA_ALIGNMENT_DEFAULT  0x00000001
#define BCHP_AUD_FMM_IOP_OUT_I2S_0_I2S_CFG_DATA_ALIGNMENT_Delayed  1
#define BCHP_AUD_FMM_IOP_OUT_I2S_0_I2S_CFG_DATA_ALIGNMENT_Aligned  0

/* AUD_FMM_IOP_OUT_I2S_0 :: I2S_CFG :: SCLK_POLARITY [05:05] */
#define BCHP_AUD_FMM_IOP_OUT_I2S_0_I2S_CFG_SCLK_POLARITY_MASK      0x00000020
#define BCHP_AUD_FMM_IOP_OUT_I2S_0_I2S_CFG_SCLK_POLARITY_SHIFT     5
#define BCHP_AUD_FMM_IOP_OUT_I2S_0_I2S_CFG_SCLK_POLARITY_DEFAULT   0x00000000
#define BCHP_AUD_FMM_IOP_OUT_I2S_0_I2S_CFG_SCLK_POLARITY_Rising_aligned_with_sdata 1
#define BCHP_AUD_FMM_IOP_OUT_I2S_0_I2S_CFG_SCLK_POLARITY_Falling_aligned_with_sdata 0

/* AUD_FMM_IOP_OUT_I2S_0 :: I2S_CFG :: LRCK_POLARITY [04:04] */
#define BCHP_AUD_FMM_IOP_OUT_I2S_0_I2S_CFG_LRCK_POLARITY_MASK      0x00000010
#define BCHP_AUD_FMM_IOP_OUT_I2S_0_I2S_CFG_LRCK_POLARITY_SHIFT     4
#define BCHP_AUD_FMM_IOP_OUT_I2S_0_I2S_CFG_LRCK_POLARITY_DEFAULT   0x00000000
#define BCHP_AUD_FMM_IOP_OUT_I2S_0_I2S_CFG_LRCK_POLARITY_High_for_left 1
#define BCHP_AUD_FMM_IOP_OUT_I2S_0_I2S_CFG_LRCK_POLARITY_Low_for_left 0

/* AUD_FMM_IOP_OUT_I2S_0 :: I2S_CFG :: reserved0 [03:02] */
#define BCHP_AUD_FMM_IOP_OUT_I2S_0_I2S_CFG_reserved0_MASK          0x0000000c
#define BCHP_AUD_FMM_IOP_OUT_I2S_0_I2S_CFG_reserved0_SHIFT         2

/* AUD_FMM_IOP_OUT_I2S_0 :: I2S_CFG :: DATA_ENABLE [01:01] */
#define BCHP_AUD_FMM_IOP_OUT_I2S_0_I2S_CFG_DATA_ENABLE_MASK        0x00000002
#define BCHP_AUD_FMM_IOP_OUT_I2S_0_I2S_CFG_DATA_ENABLE_SHIFT       1
#define BCHP_AUD_FMM_IOP_OUT_I2S_0_I2S_CFG_DATA_ENABLE_DEFAULT     0x00000000
#define BCHP_AUD_FMM_IOP_OUT_I2S_0_I2S_CFG_DATA_ENABLE_Enable      1
#define BCHP_AUD_FMM_IOP_OUT_I2S_0_I2S_CFG_DATA_ENABLE_Disable     0

/* AUD_FMM_IOP_OUT_I2S_0 :: I2S_CFG :: CLOCK_ENABLE [00:00] */
#define BCHP_AUD_FMM_IOP_OUT_I2S_0_I2S_CFG_CLOCK_ENABLE_MASK       0x00000001
#define BCHP_AUD_FMM_IOP_OUT_I2S_0_I2S_CFG_CLOCK_ENABLE_SHIFT      0
#define BCHP_AUD_FMM_IOP_OUT_I2S_0_I2S_CFG_CLOCK_ENABLE_DEFAULT    0x00000000
#define BCHP_AUD_FMM_IOP_OUT_I2S_0_I2S_CFG_CLOCK_ENABLE_Enable     1
#define BCHP_AUD_FMM_IOP_OUT_I2S_0_I2S_CFG_CLOCK_ENABLE_Disable    0

/***************************************************************************
 *I2S_CROSSBAR - I2S crossbar control
 ***************************************************************************/
/* AUD_FMM_IOP_OUT_I2S_0 :: I2S_CROSSBAR :: reserved0 [31:05] */
#define BCHP_AUD_FMM_IOP_OUT_I2S_0_I2S_CROSSBAR_reserved0_MASK     0xffffffe0
#define BCHP_AUD_FMM_IOP_OUT_I2S_0_I2S_CROSSBAR_reserved0_SHIFT    5

/* AUD_FMM_IOP_OUT_I2S_0 :: I2S_CROSSBAR :: OUT_R [04:04] */
#define BCHP_AUD_FMM_IOP_OUT_I2S_0_I2S_CROSSBAR_OUT_R_MASK         0x00000010
#define BCHP_AUD_FMM_IOP_OUT_I2S_0_I2S_CROSSBAR_OUT_R_SHIFT        4
#define BCHP_AUD_FMM_IOP_OUT_I2S_0_I2S_CROSSBAR_OUT_R_DEFAULT      0x00000001
#define BCHP_AUD_FMM_IOP_OUT_I2S_0_I2S_CROSSBAR_OUT_R_In_l         0
#define BCHP_AUD_FMM_IOP_OUT_I2S_0_I2S_CROSSBAR_OUT_R_In_r         1

/* AUD_FMM_IOP_OUT_I2S_0 :: I2S_CROSSBAR :: reserved1 [03:01] */
#define BCHP_AUD_FMM_IOP_OUT_I2S_0_I2S_CROSSBAR_reserved1_MASK     0x0000000e
#define BCHP_AUD_FMM_IOP_OUT_I2S_0_I2S_CROSSBAR_reserved1_SHIFT    1

/* AUD_FMM_IOP_OUT_I2S_0 :: I2S_CROSSBAR :: OUT_L [00:00] */
#define BCHP_AUD_FMM_IOP_OUT_I2S_0_I2S_CROSSBAR_OUT_L_MASK         0x00000001
#define BCHP_AUD_FMM_IOP_OUT_I2S_0_I2S_CROSSBAR_OUT_L_SHIFT        0
#define BCHP_AUD_FMM_IOP_OUT_I2S_0_I2S_CROSSBAR_OUT_L_DEFAULT      0x00000000
#define BCHP_AUD_FMM_IOP_OUT_I2S_0_I2S_CROSSBAR_OUT_L_In_l         0
#define BCHP_AUD_FMM_IOP_OUT_I2S_0_I2S_CROSSBAR_OUT_L_In_r         1

/***************************************************************************
 *MCLK_CFG_0 - I2S MCLK configuration
 ***************************************************************************/
/* AUD_FMM_IOP_OUT_I2S_0 :: MCLK_CFG_0 :: reserved0 [31:20] */
#define BCHP_AUD_FMM_IOP_OUT_I2S_0_MCLK_CFG_0_reserved0_MASK       0xfff00000
#define BCHP_AUD_FMM_IOP_OUT_I2S_0_MCLK_CFG_0_reserved0_SHIFT      20

/* AUD_FMM_IOP_OUT_I2S_0 :: MCLK_CFG_0 :: MCLK_RATE [19:16] */
#define BCHP_AUD_FMM_IOP_OUT_I2S_0_MCLK_CFG_0_MCLK_RATE_MASK       0x000f0000
#define BCHP_AUD_FMM_IOP_OUT_I2S_0_MCLK_CFG_0_MCLK_RATE_SHIFT      16
#define BCHP_AUD_FMM_IOP_OUT_I2S_0_MCLK_CFG_0_MCLK_RATE_DEFAULT    0x00000002
#define BCHP_AUD_FMM_IOP_OUT_I2S_0_MCLK_CFG_0_MCLK_RATE_Divide_By_32 0
#define BCHP_AUD_FMM_IOP_OUT_I2S_0_MCLK_CFG_0_MCLK_RATE_Divide_By_30 15
#define BCHP_AUD_FMM_IOP_OUT_I2S_0_MCLK_CFG_0_MCLK_RATE_Divide_By_28 14
#define BCHP_AUD_FMM_IOP_OUT_I2S_0_MCLK_CFG_0_MCLK_RATE_Divide_By_8 4
#define BCHP_AUD_FMM_IOP_OUT_I2S_0_MCLK_CFG_0_MCLK_RATE_Divide_By_6 3
#define BCHP_AUD_FMM_IOP_OUT_I2S_0_MCLK_CFG_0_MCLK_RATE_Divide_By_4 2
#define BCHP_AUD_FMM_IOP_OUT_I2S_0_MCLK_CFG_0_MCLK_RATE_Divide_By_2 1

/* AUD_FMM_IOP_OUT_I2S_0 :: MCLK_CFG_0 :: reserved1 [15:04] */
#define BCHP_AUD_FMM_IOP_OUT_I2S_0_MCLK_CFG_0_reserved1_MASK       0x0000fff0
#define BCHP_AUD_FMM_IOP_OUT_I2S_0_MCLK_CFG_0_reserved1_SHIFT      4

/* AUD_FMM_IOP_OUT_I2S_0 :: MCLK_CFG_0 :: PLLCLKSEL [03:00] */
#define BCHP_AUD_FMM_IOP_OUT_I2S_0_MCLK_CFG_0_PLLCLKSEL_MASK       0x0000000f
#define BCHP_AUD_FMM_IOP_OUT_I2S_0_MCLK_CFG_0_PLLCLKSEL_SHIFT      0
#define BCHP_AUD_FMM_IOP_OUT_I2S_0_MCLK_CFG_0_PLLCLKSEL_DEFAULT    0x00000001
#define BCHP_AUD_FMM_IOP_OUT_I2S_0_MCLK_CFG_0_PLLCLKSEL_PLL0_ch1   0
#define BCHP_AUD_FMM_IOP_OUT_I2S_0_MCLK_CFG_0_PLLCLKSEL_PLL0_ch2   1
#define BCHP_AUD_FMM_IOP_OUT_I2S_0_MCLK_CFG_0_PLLCLKSEL_PLL0_ch3   2
#define BCHP_AUD_FMM_IOP_OUT_I2S_0_MCLK_CFG_0_PLLCLKSEL_PLL1_ch1   3
#define BCHP_AUD_FMM_IOP_OUT_I2S_0_MCLK_CFG_0_PLLCLKSEL_PLL1_ch2   4
#define BCHP_AUD_FMM_IOP_OUT_I2S_0_MCLK_CFG_0_PLLCLKSEL_PLL1_ch3   5
#define BCHP_AUD_FMM_IOP_OUT_I2S_0_MCLK_CFG_0_PLLCLKSEL_NCO_0      6
#define BCHP_AUD_FMM_IOP_OUT_I2S_0_MCLK_CFG_0_PLLCLKSEL_NCO_1      7
#define BCHP_AUD_FMM_IOP_OUT_I2S_0_MCLK_CFG_0_PLLCLKSEL_NCO_2      8

/***************************************************************************
 *SAMPLE_COUNT - I2S Sample Counter
 ***************************************************************************/
/* AUD_FMM_IOP_OUT_I2S_0 :: SAMPLE_COUNT :: COUNT [31:00] */
#define BCHP_AUD_FMM_IOP_OUT_I2S_0_SAMPLE_COUNT_COUNT_MASK         0xffffffff
#define BCHP_AUD_FMM_IOP_OUT_I2S_0_SAMPLE_COUNT_COUNT_SHIFT        0

/***************************************************************************
 *THRESHOLD_SAMPLE_COUNT - I2S Threshold Sample Count
 ***************************************************************************/
/* AUD_FMM_IOP_OUT_I2S_0 :: THRESHOLD_SAMPLE_COUNT :: COUNT [31:00] */
#define BCHP_AUD_FMM_IOP_OUT_I2S_0_THRESHOLD_SAMPLE_COUNT_COUNT_MASK 0xffffffff
#define BCHP_AUD_FMM_IOP_OUT_I2S_0_THRESHOLD_SAMPLE_COUNT_COUNT_SHIFT 0
#define BCHP_AUD_FMM_IOP_OUT_I2S_0_THRESHOLD_SAMPLE_COUNT_COUNT_DEFAULT 0xffffffff

/***************************************************************************
 *SAMPLE_COUNT_CTRL - I2S Sample Counter Control
 ***************************************************************************/
/* AUD_FMM_IOP_OUT_I2S_0 :: SAMPLE_COUNT_CTRL :: reserved0 [31:02] */
#define BCHP_AUD_FMM_IOP_OUT_I2S_0_SAMPLE_COUNT_CTRL_reserved0_MASK 0xfffffffc
#define BCHP_AUD_FMM_IOP_OUT_I2S_0_SAMPLE_COUNT_CTRL_reserved0_SHIFT 2

/* AUD_FMM_IOP_OUT_I2S_0 :: SAMPLE_COUNT_CTRL :: COUNT_CLEAR [01:01] */
#define BCHP_AUD_FMM_IOP_OUT_I2S_0_SAMPLE_COUNT_CTRL_COUNT_CLEAR_MASK 0x00000002
#define BCHP_AUD_FMM_IOP_OUT_I2S_0_SAMPLE_COUNT_CTRL_COUNT_CLEAR_SHIFT 1
#define BCHP_AUD_FMM_IOP_OUT_I2S_0_SAMPLE_COUNT_CTRL_COUNT_CLEAR_DEFAULT 0x00000000
#define BCHP_AUD_FMM_IOP_OUT_I2S_0_SAMPLE_COUNT_CTRL_COUNT_CLEAR_Clear 1
#define BCHP_AUD_FMM_IOP_OUT_I2S_0_SAMPLE_COUNT_CTRL_COUNT_CLEAR_Not_Clear 0

/* AUD_FMM_IOP_OUT_I2S_0 :: SAMPLE_COUNT_CTRL :: COUNT_START [00:00] */
#define BCHP_AUD_FMM_IOP_OUT_I2S_0_SAMPLE_COUNT_CTRL_COUNT_START_MASK 0x00000001
#define BCHP_AUD_FMM_IOP_OUT_I2S_0_SAMPLE_COUNT_CTRL_COUNT_START_SHIFT 0
#define BCHP_AUD_FMM_IOP_OUT_I2S_0_SAMPLE_COUNT_CTRL_COUNT_START_DEFAULT 0x00000000
#define BCHP_AUD_FMM_IOP_OUT_I2S_0_SAMPLE_COUNT_CTRL_COUNT_START_Start_count 1
#define BCHP_AUD_FMM_IOP_OUT_I2S_0_SAMPLE_COUNT_CTRL_COUNT_START_Stop_count 0

/***************************************************************************
 *I2S_LEGACY - Legacy Master Mode I2S Transmitter
 ***************************************************************************/
/* AUD_FMM_IOP_OUT_I2S_0 :: I2S_LEGACY :: reserved0 [31:01] */
#define BCHP_AUD_FMM_IOP_OUT_I2S_0_I2S_LEGACY_reserved0_MASK       0xfffffffe
#define BCHP_AUD_FMM_IOP_OUT_I2S_0_I2S_LEGACY_reserved0_SHIFT      1

/* AUD_FMM_IOP_OUT_I2S_0 :: I2S_LEGACY :: EN_LEGACY_I2S [00:00] */
#define BCHP_AUD_FMM_IOP_OUT_I2S_0_I2S_LEGACY_EN_LEGACY_I2S_MASK   0x00000001
#define BCHP_AUD_FMM_IOP_OUT_I2S_0_I2S_LEGACY_EN_LEGACY_I2S_SHIFT  0
#define BCHP_AUD_FMM_IOP_OUT_I2S_0_I2S_LEGACY_EN_LEGACY_I2S_DEFAULT 0x00000001
#define BCHP_AUD_FMM_IOP_OUT_I2S_0_I2S_LEGACY_EN_LEGACY_I2S_Enable 1
#define BCHP_AUD_FMM_IOP_OUT_I2S_0_I2S_LEGACY_EN_LEGACY_I2S_Disable 0

/***************************************************************************
 *ESR_STATUS - Error Status Register
 ***************************************************************************/
/* AUD_FMM_IOP_OUT_I2S_0 :: ESR_STATUS :: reserved0 [31:03] */
#define BCHP_AUD_FMM_IOP_OUT_I2S_0_ESR_STATUS_reserved0_MASK       0xfffffff8
#define BCHP_AUD_FMM_IOP_OUT_I2S_0_ESR_STATUS_reserved0_SHIFT      3

/* AUD_FMM_IOP_OUT_I2S_0 :: ESR_STATUS :: SAMPLE_COUNT_THRESHOLD [02:02] */
#define BCHP_AUD_FMM_IOP_OUT_I2S_0_ESR_STATUS_SAMPLE_COUNT_THRESHOLD_MASK 0x00000004
#define BCHP_AUD_FMM_IOP_OUT_I2S_0_ESR_STATUS_SAMPLE_COUNT_THRESHOLD_SHIFT 2
#define BCHP_AUD_FMM_IOP_OUT_I2S_0_ESR_STATUS_SAMPLE_COUNT_THRESHOLD_DEFAULT 0x00000000

/* AUD_FMM_IOP_OUT_I2S_0 :: ESR_STATUS :: SAMPLE_COUNT_ROLLOVER [01:01] */
#define BCHP_AUD_FMM_IOP_OUT_I2S_0_ESR_STATUS_SAMPLE_COUNT_ROLLOVER_MASK 0x00000002
#define BCHP_AUD_FMM_IOP_OUT_I2S_0_ESR_STATUS_SAMPLE_COUNT_ROLLOVER_SHIFT 1
#define BCHP_AUD_FMM_IOP_OUT_I2S_0_ESR_STATUS_SAMPLE_COUNT_ROLLOVER_DEFAULT 0x00000000

/* AUD_FMM_IOP_OUT_I2S_0 :: ESR_STATUS :: STREAM_UNDERFLOW [00:00] */
#define BCHP_AUD_FMM_IOP_OUT_I2S_0_ESR_STATUS_STREAM_UNDERFLOW_MASK 0x00000001
#define BCHP_AUD_FMM_IOP_OUT_I2S_0_ESR_STATUS_STREAM_UNDERFLOW_SHIFT 0
#define BCHP_AUD_FMM_IOP_OUT_I2S_0_ESR_STATUS_STREAM_UNDERFLOW_DEFAULT 0x00000000

/***************************************************************************
 *ESR_STATUS_SET - Error Set Register
 ***************************************************************************/
/* AUD_FMM_IOP_OUT_I2S_0 :: ESR_STATUS_SET :: reserved0 [31:03] */
#define BCHP_AUD_FMM_IOP_OUT_I2S_0_ESR_STATUS_SET_reserved0_MASK   0xfffffff8
#define BCHP_AUD_FMM_IOP_OUT_I2S_0_ESR_STATUS_SET_reserved0_SHIFT  3

/* AUD_FMM_IOP_OUT_I2S_0 :: ESR_STATUS_SET :: SAMPLE_COUNT_THRESHOLD [02:02] */
#define BCHP_AUD_FMM_IOP_OUT_I2S_0_ESR_STATUS_SET_SAMPLE_COUNT_THRESHOLD_MASK 0x00000004
#define BCHP_AUD_FMM_IOP_OUT_I2S_0_ESR_STATUS_SET_SAMPLE_COUNT_THRESHOLD_SHIFT 2
#define BCHP_AUD_FMM_IOP_OUT_I2S_0_ESR_STATUS_SET_SAMPLE_COUNT_THRESHOLD_DEFAULT 0x00000000

/* AUD_FMM_IOP_OUT_I2S_0 :: ESR_STATUS_SET :: SAMPLE_COUNT_ROLLOVER [01:01] */
#define BCHP_AUD_FMM_IOP_OUT_I2S_0_ESR_STATUS_SET_SAMPLE_COUNT_ROLLOVER_MASK 0x00000002
#define BCHP_AUD_FMM_IOP_OUT_I2S_0_ESR_STATUS_SET_SAMPLE_COUNT_ROLLOVER_SHIFT 1
#define BCHP_AUD_FMM_IOP_OUT_I2S_0_ESR_STATUS_SET_SAMPLE_COUNT_ROLLOVER_DEFAULT 0x00000000

/* AUD_FMM_IOP_OUT_I2S_0 :: ESR_STATUS_SET :: STREAM_UNDERFLOW [00:00] */
#define BCHP_AUD_FMM_IOP_OUT_I2S_0_ESR_STATUS_SET_STREAM_UNDERFLOW_MASK 0x00000001
#define BCHP_AUD_FMM_IOP_OUT_I2S_0_ESR_STATUS_SET_STREAM_UNDERFLOW_SHIFT 0
#define BCHP_AUD_FMM_IOP_OUT_I2S_0_ESR_STATUS_SET_STREAM_UNDERFLOW_DEFAULT 0x00000000

/***************************************************************************
 *ESR_STATUS_CLEAR - Error Clear Register
 ***************************************************************************/
/* AUD_FMM_IOP_OUT_I2S_0 :: ESR_STATUS_CLEAR :: reserved0 [31:03] */
#define BCHP_AUD_FMM_IOP_OUT_I2S_0_ESR_STATUS_CLEAR_reserved0_MASK 0xfffffff8
#define BCHP_AUD_FMM_IOP_OUT_I2S_0_ESR_STATUS_CLEAR_reserved0_SHIFT 3

/* AUD_FMM_IOP_OUT_I2S_0 :: ESR_STATUS_CLEAR :: SAMPLE_COUNT_THRESHOLD [02:02] */
#define BCHP_AUD_FMM_IOP_OUT_I2S_0_ESR_STATUS_CLEAR_SAMPLE_COUNT_THRESHOLD_MASK 0x00000004
#define BCHP_AUD_FMM_IOP_OUT_I2S_0_ESR_STATUS_CLEAR_SAMPLE_COUNT_THRESHOLD_SHIFT 2
#define BCHP_AUD_FMM_IOP_OUT_I2S_0_ESR_STATUS_CLEAR_SAMPLE_COUNT_THRESHOLD_DEFAULT 0x00000000

/* AUD_FMM_IOP_OUT_I2S_0 :: ESR_STATUS_CLEAR :: SAMPLE_COUNT_ROLLOVER [01:01] */
#define BCHP_AUD_FMM_IOP_OUT_I2S_0_ESR_STATUS_CLEAR_SAMPLE_COUNT_ROLLOVER_MASK 0x00000002
#define BCHP_AUD_FMM_IOP_OUT_I2S_0_ESR_STATUS_CLEAR_SAMPLE_COUNT_ROLLOVER_SHIFT 1
#define BCHP_AUD_FMM_IOP_OUT_I2S_0_ESR_STATUS_CLEAR_SAMPLE_COUNT_ROLLOVER_DEFAULT 0x00000000

/* AUD_FMM_IOP_OUT_I2S_0 :: ESR_STATUS_CLEAR :: STREAM_UNDERFLOW [00:00] */
#define BCHP_AUD_FMM_IOP_OUT_I2S_0_ESR_STATUS_CLEAR_STREAM_UNDERFLOW_MASK 0x00000001
#define BCHP_AUD_FMM_IOP_OUT_I2S_0_ESR_STATUS_CLEAR_STREAM_UNDERFLOW_SHIFT 0
#define BCHP_AUD_FMM_IOP_OUT_I2S_0_ESR_STATUS_CLEAR_STREAM_UNDERFLOW_DEFAULT 0x00000000

/***************************************************************************
 *ESR_MASK - Mask Status Register
 ***************************************************************************/
/* AUD_FMM_IOP_OUT_I2S_0 :: ESR_MASK :: reserved0 [31:03] */
#define BCHP_AUD_FMM_IOP_OUT_I2S_0_ESR_MASK_reserved0_MASK         0xfffffff8
#define BCHP_AUD_FMM_IOP_OUT_I2S_0_ESR_MASK_reserved0_SHIFT        3

/* AUD_FMM_IOP_OUT_I2S_0 :: ESR_MASK :: SAMPLE_COUNT_THRESHOLD [02:02] */
#define BCHP_AUD_FMM_IOP_OUT_I2S_0_ESR_MASK_SAMPLE_COUNT_THRESHOLD_MASK 0x00000004
#define BCHP_AUD_FMM_IOP_OUT_I2S_0_ESR_MASK_SAMPLE_COUNT_THRESHOLD_SHIFT 2
#define BCHP_AUD_FMM_IOP_OUT_I2S_0_ESR_MASK_SAMPLE_COUNT_THRESHOLD_DEFAULT 0x00000001

/* AUD_FMM_IOP_OUT_I2S_0 :: ESR_MASK :: SAMPLE_COUNT_ROLLOVER [01:01] */
#define BCHP_AUD_FMM_IOP_OUT_I2S_0_ESR_MASK_SAMPLE_COUNT_ROLLOVER_MASK 0x00000002
#define BCHP_AUD_FMM_IOP_OUT_I2S_0_ESR_MASK_SAMPLE_COUNT_ROLLOVER_SHIFT 1
#define BCHP_AUD_FMM_IOP_OUT_I2S_0_ESR_MASK_SAMPLE_COUNT_ROLLOVER_DEFAULT 0x00000001

/* AUD_FMM_IOP_OUT_I2S_0 :: ESR_MASK :: STREAM_UNDERFLOW [00:00] */
#define BCHP_AUD_FMM_IOP_OUT_I2S_0_ESR_MASK_STREAM_UNDERFLOW_MASK  0x00000001
#define BCHP_AUD_FMM_IOP_OUT_I2S_0_ESR_MASK_STREAM_UNDERFLOW_SHIFT 0
#define BCHP_AUD_FMM_IOP_OUT_I2S_0_ESR_MASK_STREAM_UNDERFLOW_DEFAULT 0x00000001

/***************************************************************************
 *ESR_MASK_SET - Mask Set Register
 ***************************************************************************/
/* AUD_FMM_IOP_OUT_I2S_0 :: ESR_MASK_SET :: reserved0 [31:03] */
#define BCHP_AUD_FMM_IOP_OUT_I2S_0_ESR_MASK_SET_reserved0_MASK     0xfffffff8
#define BCHP_AUD_FMM_IOP_OUT_I2S_0_ESR_MASK_SET_reserved0_SHIFT    3

/* AUD_FMM_IOP_OUT_I2S_0 :: ESR_MASK_SET :: SAMPLE_COUNT_THRESHOLD [02:02] */
#define BCHP_AUD_FMM_IOP_OUT_I2S_0_ESR_MASK_SET_SAMPLE_COUNT_THRESHOLD_MASK 0x00000004
#define BCHP_AUD_FMM_IOP_OUT_I2S_0_ESR_MASK_SET_SAMPLE_COUNT_THRESHOLD_SHIFT 2
#define BCHP_AUD_FMM_IOP_OUT_I2S_0_ESR_MASK_SET_SAMPLE_COUNT_THRESHOLD_DEFAULT 0x00000001

/* AUD_FMM_IOP_OUT_I2S_0 :: ESR_MASK_SET :: SAMPLE_COUNT_ROLLOVER [01:01] */
#define BCHP_AUD_FMM_IOP_OUT_I2S_0_ESR_MASK_SET_SAMPLE_COUNT_ROLLOVER_MASK 0x00000002
#define BCHP_AUD_FMM_IOP_OUT_I2S_0_ESR_MASK_SET_SAMPLE_COUNT_ROLLOVER_SHIFT 1
#define BCHP_AUD_FMM_IOP_OUT_I2S_0_ESR_MASK_SET_SAMPLE_COUNT_ROLLOVER_DEFAULT 0x00000001

/* AUD_FMM_IOP_OUT_I2S_0 :: ESR_MASK_SET :: STREAM_UNDERFLOW [00:00] */
#define BCHP_AUD_FMM_IOP_OUT_I2S_0_ESR_MASK_SET_STREAM_UNDERFLOW_MASK 0x00000001
#define BCHP_AUD_FMM_IOP_OUT_I2S_0_ESR_MASK_SET_STREAM_UNDERFLOW_SHIFT 0
#define BCHP_AUD_FMM_IOP_OUT_I2S_0_ESR_MASK_SET_STREAM_UNDERFLOW_DEFAULT 0x00000001

/***************************************************************************
 *ESR_MASK_CLEAR - Mask Clear Register
 ***************************************************************************/
/* AUD_FMM_IOP_OUT_I2S_0 :: ESR_MASK_CLEAR :: reserved0 [31:03] */
#define BCHP_AUD_FMM_IOP_OUT_I2S_0_ESR_MASK_CLEAR_reserved0_MASK   0xfffffff8
#define BCHP_AUD_FMM_IOP_OUT_I2S_0_ESR_MASK_CLEAR_reserved0_SHIFT  3

/* AUD_FMM_IOP_OUT_I2S_0 :: ESR_MASK_CLEAR :: SAMPLE_COUNT_THRESHOLD [02:02] */
#define BCHP_AUD_FMM_IOP_OUT_I2S_0_ESR_MASK_CLEAR_SAMPLE_COUNT_THRESHOLD_MASK 0x00000004
#define BCHP_AUD_FMM_IOP_OUT_I2S_0_ESR_MASK_CLEAR_SAMPLE_COUNT_THRESHOLD_SHIFT 2
#define BCHP_AUD_FMM_IOP_OUT_I2S_0_ESR_MASK_CLEAR_SAMPLE_COUNT_THRESHOLD_DEFAULT 0x00000001

/* AUD_FMM_IOP_OUT_I2S_0 :: ESR_MASK_CLEAR :: SAMPLE_COUNT_ROLLOVER [01:01] */
#define BCHP_AUD_FMM_IOP_OUT_I2S_0_ESR_MASK_CLEAR_SAMPLE_COUNT_ROLLOVER_MASK 0x00000002
#define BCHP_AUD_FMM_IOP_OUT_I2S_0_ESR_MASK_CLEAR_SAMPLE_COUNT_ROLLOVER_SHIFT 1
#define BCHP_AUD_FMM_IOP_OUT_I2S_0_ESR_MASK_CLEAR_SAMPLE_COUNT_ROLLOVER_DEFAULT 0x00000001

/* AUD_FMM_IOP_OUT_I2S_0 :: ESR_MASK_CLEAR :: STREAM_UNDERFLOW [00:00] */
#define BCHP_AUD_FMM_IOP_OUT_I2S_0_ESR_MASK_CLEAR_STREAM_UNDERFLOW_MASK 0x00000001
#define BCHP_AUD_FMM_IOP_OUT_I2S_0_ESR_MASK_CLEAR_STREAM_UNDERFLOW_SHIFT 0
#define BCHP_AUD_FMM_IOP_OUT_I2S_0_ESR_MASK_CLEAR_STREAM_UNDERFLOW_DEFAULT 0x00000001

#endif /* #ifndef BCHP_AUD_FMM_IOP_OUT_I2S_0_H__ */

/* End of File */

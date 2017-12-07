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

#ifndef BCHP_CCE_0_H__
#define BCHP_CCE_0_H__

/***************************************************************************
 *CCE_0 - CCE_0 registers
 ***************************************************************************/
#define BCHP_CCE_0_RevID                         0x206ea400 /* [RO][32] CC Encoder Revision ID Register */
#define BCHP_CCE_0_Active_Lines                  0x206ea408 /* [RW][32] Active Lines Register */
#define BCHP_CCE_0_Control                       0x206ea40c /* [RW][32] Control Register */
#define BCHP_CCE_0_Active_Lines_1                0x206ea410 /* [RW][32] Active Lines 1(SCTE) Register */
#define BCHP_CCE_0_Gain_Delay                    0x206ea414 /* [RW][32] Gain and Delay Register */
#define BCHP_CCE_0_SCTE_Base_Lines               0x206ea418 /* [RW][32] SCTE Base Lines Register */
#define BCHP_CCE_0_Data0                         0x206ea41c /* [RW][32] Data Register 0 */
#define BCHP_CCE_0_Data1                         0x206ea420 /* [RW][32] Data Register 1 */
#define BCHP_CCE_0_Data2                         0x206ea424 /* [RW][32] Data Register 2 */
#define BCHP_CCE_0_Data3                         0x206ea428 /* [RW][32] Data Register 3 */
#define BCHP_CCE_0_Data4                         0x206ea42c /* [RW][32] Data Register 4 */
#define BCHP_CCE_0_Data5                         0x206ea430 /* [RW][32] Data Register 5 */
#define BCHP_CCE_0_Data6                         0x206ea434 /* [RW][32] Data Register 6 */
#define BCHP_CCE_0_Data7                         0x206ea438 /* [RW][32] Data Register 7 */
#define BCHP_CCE_0_Data8                         0x206ea43c /* [RW][32] Data Register 8 */
#define BCHP_CCE_0_Data9                         0x206ea440 /* [RW][32] Data Register 9 */
#define BCHP_CCE_0_Data10                        0x206ea444 /* [RW][32] Data Register 10 */
#define BCHP_CCE_0_Data11                        0x206ea448 /* [RW][32] Data Register 11 */
#define BCHP_CCE_0_Data12                        0x206ea44c /* [RW][32] Data Register 12 */
#define BCHP_CCE_0_Data13                        0x206ea450 /* [RW][32] Data Register 13 */
#define BCHP_CCE_0_Data14                        0x206ea454 /* [RW][32] Data Register 14 */
#define BCHP_CCE_0_Data15                        0x206ea458 /* [RW][32] Data Register 15 */

/***************************************************************************
 *RevID - CC Encoder Revision ID Register
 ***************************************************************************/
/* CCE_0 :: RevID :: reserved0 [31:16] */
#define BCHP_CCE_0_RevID_reserved0_MASK                            0xffff0000
#define BCHP_CCE_0_RevID_reserved0_SHIFT                           16

/* CCE_0 :: RevID :: REVID [15:00] */
#define BCHP_CCE_0_RevID_REVID_MASK                                0x0000ffff
#define BCHP_CCE_0_RevID_REVID_SHIFT                               0
#define BCHP_CCE_0_RevID_REVID_DEFAULT                             0x00004000

/***************************************************************************
 *Active_Lines - Active Lines Register
 ***************************************************************************/
/* union - case SCTE_ON [31:00] */
/* CCE_0 :: Active_Lines :: SCTE_ON :: SCTE_TOP_ACTIVE [31:00] */
#define BCHP_CCE_0_Active_Lines_SCTE_ON_SCTE_TOP_ACTIVE_MASK       0xffffffff
#define BCHP_CCE_0_Active_Lines_SCTE_ON_SCTE_TOP_ACTIVE_SHIFT      0
#define BCHP_CCE_0_Active_Lines_SCTE_ON_SCTE_TOP_ACTIVE_DEFAULT    0x00000000

/* union - case SCTE_OFF [31:00] */
/* CCE_0 :: Active_Lines :: SCTE_OFF :: BOT_ACTIVE [31:16] */
#define BCHP_CCE_0_Active_Lines_SCTE_OFF_BOT_ACTIVE_MASK           0xffff0000
#define BCHP_CCE_0_Active_Lines_SCTE_OFF_BOT_ACTIVE_SHIFT          16
#define BCHP_CCE_0_Active_Lines_SCTE_OFF_BOT_ACTIVE_DEFAULT        0x00000000

/* CCE_0 :: Active_Lines :: SCTE_OFF :: TOP_ACTIVE [15:00] */
#define BCHP_CCE_0_Active_Lines_SCTE_OFF_TOP_ACTIVE_MASK           0x0000ffff
#define BCHP_CCE_0_Active_Lines_SCTE_OFF_TOP_ACTIVE_SHIFT          0
#define BCHP_CCE_0_Active_Lines_SCTE_OFF_TOP_ACTIVE_DEFAULT        0x00000000

/* union - case default [31:00] */
/* CCE_0 :: Active_Lines :: default :: BOT_ACTIVE [31:16] */
#define BCHP_CCE_0_Active_Lines_default_BOT_ACTIVE_MASK            0xffff0000
#define BCHP_CCE_0_Active_Lines_default_BOT_ACTIVE_SHIFT           16
#define BCHP_CCE_0_Active_Lines_default_BOT_ACTIVE_DEFAULT         0x00000000

/* CCE_0 :: Active_Lines :: default :: TOP_ACTIVE [15:00] */
#define BCHP_CCE_0_Active_Lines_default_TOP_ACTIVE_MASK            0x0000ffff
#define BCHP_CCE_0_Active_Lines_default_TOP_ACTIVE_SHIFT           0
#define BCHP_CCE_0_Active_Lines_default_TOP_ACTIVE_DEFAULT         0x00000000

/***************************************************************************
 *Control - Control Register
 ***************************************************************************/
/* CCE_0 :: Control :: reserved0 [31:26] */
#define BCHP_CCE_0_Control_reserved0_MASK                          0xfc000000
#define BCHP_CCE_0_Control_reserved0_SHIFT                         26

/* CCE_0 :: Control :: reserved_for_eco1 [25:21] */
#define BCHP_CCE_0_Control_reserved_for_eco1_MASK                  0x03e00000
#define BCHP_CCE_0_Control_reserved_for_eco1_SHIFT                 21
#define BCHP_CCE_0_Control_reserved_for_eco1_DEFAULT               0x00000000

/* CCE_0 :: Control :: SCTE_MODE [20:20] */
#define BCHP_CCE_0_Control_SCTE_MODE_MASK                          0x00100000
#define BCHP_CCE_0_Control_SCTE_MODE_SHIFT                         20
#define BCHP_CCE_0_Control_SCTE_MODE_DEFAULT                       0x00000000
#define BCHP_CCE_0_Control_SCTE_MODE_SCTE_ON                       1
#define BCHP_CCE_0_Control_SCTE_MODE_SCTE_OFF                      0

/* CCE_0 :: Control :: TOP_FLD_PARITY [19:19] */
#define BCHP_CCE_0_Control_TOP_FLD_PARITY_MASK                     0x00080000
#define BCHP_CCE_0_Control_TOP_FLD_PARITY_SHIFT                    19
#define BCHP_CCE_0_Control_TOP_FLD_PARITY_DEFAULT                  0x00000000
#define BCHP_CCE_0_Control_TOP_FLD_PARITY_MANUAL                   0
#define BCHP_CCE_0_Control_TOP_FLD_PARITY_AUTOMATIC                1

/* CCE_0 :: Control :: BOT_FLD_PARITY [18:18] */
#define BCHP_CCE_0_Control_BOT_FLD_PARITY_MASK                     0x00040000
#define BCHP_CCE_0_Control_BOT_FLD_PARITY_SHIFT                    18
#define BCHP_CCE_0_Control_BOT_FLD_PARITY_DEFAULT                  0x00000000
#define BCHP_CCE_0_Control_BOT_FLD_PARITY_MANUAL                   0
#define BCHP_CCE_0_Control_BOT_FLD_PARITY_AUTOMATIC                1

/* CCE_0 :: Control :: TOP_FLD_STAT [17:17] */
#define BCHP_CCE_0_Control_TOP_FLD_STAT_MASK                       0x00020000
#define BCHP_CCE_0_Control_TOP_FLD_STAT_SHIFT                      17
#define BCHP_CCE_0_Control_TOP_FLD_STAT_DEFAULT                    0x00000000
#define BCHP_CCE_0_Control_TOP_FLD_STAT_DATA_TRANSMITTED           0
#define BCHP_CCE_0_Control_TOP_FLD_STAT_DATA_NOT_TRANSMITTED       1

/* CCE_0 :: Control :: BOT_FLD_STAT [16:16] */
#define BCHP_CCE_0_Control_BOT_FLD_STAT_MASK                       0x00010000
#define BCHP_CCE_0_Control_BOT_FLD_STAT_SHIFT                      16
#define BCHP_CCE_0_Control_BOT_FLD_STAT_DEFAULT                    0x00000000
#define BCHP_CCE_0_Control_BOT_FLD_STAT_DATA_TRANSMITTED           0
#define BCHP_CCE_0_Control_BOT_FLD_STAT_DATA_NOT_TRANSMITTED       1

/* CCE_0 :: Control :: NULL_CHARACTER [15:08] */
#define BCHP_CCE_0_Control_NULL_CHARACTER_MASK                     0x0000ff00
#define BCHP_CCE_0_Control_NULL_CHARACTER_SHIFT                    8
#define BCHP_CCE_0_Control_NULL_CHARACTER_DEFAULT                  0x00000000

/* CCE_0 :: Control :: BYTEIF_ENDIAN_ORDER [07:07] */
#define BCHP_CCE_0_Control_BYTEIF_ENDIAN_ORDER_MASK                0x00000080
#define BCHP_CCE_0_Control_BYTEIF_ENDIAN_ORDER_SHIFT               7
#define BCHP_CCE_0_Control_BYTEIF_ENDIAN_ORDER_DEFAULT             0x00000000
#define BCHP_CCE_0_Control_BYTEIF_ENDIAN_ORDER_MAINTAIN            0
#define BCHP_CCE_0_Control_BYTEIF_ENDIAN_ORDER_SWAP                1

/* CCE_0 :: Control :: VIDEO_FORMAT [06:06] */
#define BCHP_CCE_0_Control_VIDEO_FORMAT_MASK                       0x00000040
#define BCHP_CCE_0_Control_VIDEO_FORMAT_SHIFT                      6
#define BCHP_CCE_0_Control_VIDEO_FORMAT_DEFAULT                    0x00000000
#define BCHP_CCE_0_Control_VIDEO_FORMAT_NTSC                       0
#define BCHP_CCE_0_Control_VIDEO_FORMAT_PAL                        1

/* CCE_0 :: Control :: BYTE_SWAP [05:05] */
#define BCHP_CCE_0_Control_BYTE_SWAP_MASK                          0x00000020
#define BCHP_CCE_0_Control_BYTE_SWAP_SHIFT                         5
#define BCHP_CCE_0_Control_BYTE_SWAP_DEFAULT                       0x00000000
#define BCHP_CCE_0_Control_BYTE_SWAP_LITTLE_ENDIAN                 0
#define BCHP_CCE_0_Control_BYTE_SWAP_BIG_ENDIAN                    1

/* CCE_0 :: Control :: SHIFT_DIRECTION [04:04] */
#define BCHP_CCE_0_Control_SHIFT_DIRECTION_MASK                    0x00000010
#define BCHP_CCE_0_Control_SHIFT_DIRECTION_SHIFT                   4
#define BCHP_CCE_0_Control_SHIFT_DIRECTION_DEFAULT                 0x00000000
#define BCHP_CCE_0_Control_SHIFT_DIRECTION_LSB2MSB                 0
#define BCHP_CCE_0_Control_SHIFT_DIRECTION_MSB2LSB                 1

/* CCE_0 :: Control :: reserved2 [03:02] */
#define BCHP_CCE_0_Control_reserved2_MASK                          0x0000000c
#define BCHP_CCE_0_Control_reserved2_SHIFT                         2

/* CCE_0 :: Control :: REGISTER_USE_MODE [01:01] */
#define BCHP_CCE_0_Control_REGISTER_USE_MODE_MASK                  0x00000002
#define BCHP_CCE_0_Control_REGISTER_USE_MODE_SHIFT                 1
#define BCHP_CCE_0_Control_REGISTER_USE_MODE_DEFAULT               0x00000000
#define BCHP_CCE_0_Control_REGISTER_USE_MODE_SPLIT                 0
#define BCHP_CCE_0_Control_REGISTER_USE_MODE_SHARE                 1

/* CCE_0 :: Control :: ENABLE_CLOSED_CAPTION [00:00] */
#define BCHP_CCE_0_Control_ENABLE_CLOSED_CAPTION_MASK              0x00000001
#define BCHP_CCE_0_Control_ENABLE_CLOSED_CAPTION_SHIFT             0
#define BCHP_CCE_0_Control_ENABLE_CLOSED_CAPTION_DEFAULT           0x00000000
#define BCHP_CCE_0_Control_ENABLE_CLOSED_CAPTION_DISABLED          0
#define BCHP_CCE_0_Control_ENABLE_CLOSED_CAPTION_ENABLED           1

/***************************************************************************
 *Active_Lines_1 - Active Lines 1(SCTE) Register
 ***************************************************************************/
/* CCE_0 :: Active_Lines_1 :: SCTE_BOT_ACTIVE [31:00] */
#define BCHP_CCE_0_Active_Lines_1_SCTE_BOT_ACTIVE_MASK             0xffffffff
#define BCHP_CCE_0_Active_Lines_1_SCTE_BOT_ACTIVE_SHIFT            0
#define BCHP_CCE_0_Active_Lines_1_SCTE_BOT_ACTIVE_DEFAULT          0x00000000

/***************************************************************************
 *Gain_Delay - Gain and Delay Register
 ***************************************************************************/
/* CCE_0 :: Gain_Delay :: reserved0 [31:24] */
#define BCHP_CCE_0_Gain_Delay_reserved0_MASK                       0xff000000
#define BCHP_CCE_0_Gain_Delay_reserved0_SHIFT                      24

/* CCE_0 :: Gain_Delay :: DELAY_COUNT [23:16] */
#define BCHP_CCE_0_Gain_Delay_DELAY_COUNT_MASK                     0x00ff0000
#define BCHP_CCE_0_Gain_Delay_DELAY_COUNT_SHIFT                    16
#define BCHP_CCE_0_Gain_Delay_DELAY_COUNT_DEFAULT                  0x00000000

/* CCE_0 :: Gain_Delay :: GAIN [15:08] */
#define BCHP_CCE_0_Gain_Delay_GAIN_MASK                            0x0000ff00
#define BCHP_CCE_0_Gain_Delay_GAIN_SHIFT                           8
#define BCHP_CCE_0_Gain_Delay_GAIN_DEFAULT                         0x000000ff

/* CCE_0 :: Gain_Delay :: reserved1 [07:00] */
#define BCHP_CCE_0_Gain_Delay_reserved1_MASK                       0x000000ff
#define BCHP_CCE_0_Gain_Delay_reserved1_SHIFT                      0

/***************************************************************************
 *SCTE_Base_Lines - SCTE Base Lines Register
 ***************************************************************************/
/* CCE_0 :: SCTE_Base_Lines :: reserved0 [31:24] */
#define BCHP_CCE_0_SCTE_Base_Lines_reserved0_MASK                  0xff000000
#define BCHP_CCE_0_SCTE_Base_Lines_reserved0_SHIFT                 24

/* CCE_0 :: SCTE_Base_Lines :: LINE_BOT [23:12] */
#define BCHP_CCE_0_SCTE_Base_Lines_LINE_BOT_MASK                   0x00fff000
#define BCHP_CCE_0_SCTE_Base_Lines_LINE_BOT_SHIFT                  12
#define BCHP_CCE_0_SCTE_Base_Lines_LINE_BOT_DEFAULT                0x00000110

/* CCE_0 :: SCTE_Base_Lines :: LINE_TOP [11:00] */
#define BCHP_CCE_0_SCTE_Base_Lines_LINE_TOP_MASK                   0x00000fff
#define BCHP_CCE_0_SCTE_Base_Lines_LINE_TOP_SHIFT                  0
#define BCHP_CCE_0_SCTE_Base_Lines_LINE_TOP_DEFAULT                0x00000009

/***************************************************************************
 *Data0 - Data Register 0
 ***************************************************************************/
/* CCE_0 :: Data0 :: WORD1 [31:16] */
#define BCHP_CCE_0_Data0_WORD1_MASK                                0xffff0000
#define BCHP_CCE_0_Data0_WORD1_SHIFT                               16
#define BCHP_CCE_0_Data0_WORD1_DEFAULT                             0x00000000

/* CCE_0 :: Data0 :: WORD0 [15:00] */
#define BCHP_CCE_0_Data0_WORD0_MASK                                0x0000ffff
#define BCHP_CCE_0_Data0_WORD0_SHIFT                               0
#define BCHP_CCE_0_Data0_WORD0_DEFAULT                             0x00000000

/***************************************************************************
 *Data1 - Data Register 1
 ***************************************************************************/
/* CCE_0 :: Data1 :: WORD1 [31:16] */
#define BCHP_CCE_0_Data1_WORD1_MASK                                0xffff0000
#define BCHP_CCE_0_Data1_WORD1_SHIFT                               16
#define BCHP_CCE_0_Data1_WORD1_DEFAULT                             0x00000000

/* CCE_0 :: Data1 :: WORD0 [15:00] */
#define BCHP_CCE_0_Data1_WORD0_MASK                                0x0000ffff
#define BCHP_CCE_0_Data1_WORD0_SHIFT                               0
#define BCHP_CCE_0_Data1_WORD0_DEFAULT                             0x00000000

/***************************************************************************
 *Data2 - Data Register 2
 ***************************************************************************/
/* CCE_0 :: Data2 :: WORD1 [31:16] */
#define BCHP_CCE_0_Data2_WORD1_MASK                                0xffff0000
#define BCHP_CCE_0_Data2_WORD1_SHIFT                               16
#define BCHP_CCE_0_Data2_WORD1_DEFAULT                             0x00000000

/* CCE_0 :: Data2 :: WORD0 [15:00] */
#define BCHP_CCE_0_Data2_WORD0_MASK                                0x0000ffff
#define BCHP_CCE_0_Data2_WORD0_SHIFT                               0
#define BCHP_CCE_0_Data2_WORD0_DEFAULT                             0x00000000

/***************************************************************************
 *Data3 - Data Register 3
 ***************************************************************************/
/* CCE_0 :: Data3 :: WORD1 [31:16] */
#define BCHP_CCE_0_Data3_WORD1_MASK                                0xffff0000
#define BCHP_CCE_0_Data3_WORD1_SHIFT                               16
#define BCHP_CCE_0_Data3_WORD1_DEFAULT                             0x00000000

/* CCE_0 :: Data3 :: WORD0 [15:00] */
#define BCHP_CCE_0_Data3_WORD0_MASK                                0x0000ffff
#define BCHP_CCE_0_Data3_WORD0_SHIFT                               0
#define BCHP_CCE_0_Data3_WORD0_DEFAULT                             0x00000000

/***************************************************************************
 *Data4 - Data Register 4
 ***************************************************************************/
/* CCE_0 :: Data4 :: WORD1 [31:16] */
#define BCHP_CCE_0_Data4_WORD1_MASK                                0xffff0000
#define BCHP_CCE_0_Data4_WORD1_SHIFT                               16
#define BCHP_CCE_0_Data4_WORD1_DEFAULT                             0x00000000

/* CCE_0 :: Data4 :: WORD0 [15:00] */
#define BCHP_CCE_0_Data4_WORD0_MASK                                0x0000ffff
#define BCHP_CCE_0_Data4_WORD0_SHIFT                               0
#define BCHP_CCE_0_Data4_WORD0_DEFAULT                             0x00000000

/***************************************************************************
 *Data5 - Data Register 5
 ***************************************************************************/
/* CCE_0 :: Data5 :: WORD1 [31:16] */
#define BCHP_CCE_0_Data5_WORD1_MASK                                0xffff0000
#define BCHP_CCE_0_Data5_WORD1_SHIFT                               16
#define BCHP_CCE_0_Data5_WORD1_DEFAULT                             0x00000000

/* CCE_0 :: Data5 :: WORD0 [15:00] */
#define BCHP_CCE_0_Data5_WORD0_MASK                                0x0000ffff
#define BCHP_CCE_0_Data5_WORD0_SHIFT                               0
#define BCHP_CCE_0_Data5_WORD0_DEFAULT                             0x00000000

/***************************************************************************
 *Data6 - Data Register 6
 ***************************************************************************/
/* CCE_0 :: Data6 :: WORD1 [31:16] */
#define BCHP_CCE_0_Data6_WORD1_MASK                                0xffff0000
#define BCHP_CCE_0_Data6_WORD1_SHIFT                               16
#define BCHP_CCE_0_Data6_WORD1_DEFAULT                             0x00000000

/* CCE_0 :: Data6 :: WORD0 [15:00] */
#define BCHP_CCE_0_Data6_WORD0_MASK                                0x0000ffff
#define BCHP_CCE_0_Data6_WORD0_SHIFT                               0
#define BCHP_CCE_0_Data6_WORD0_DEFAULT                             0x00000000

/***************************************************************************
 *Data7 - Data Register 7
 ***************************************************************************/
/* CCE_0 :: Data7 :: WORD1 [31:16] */
#define BCHP_CCE_0_Data7_WORD1_MASK                                0xffff0000
#define BCHP_CCE_0_Data7_WORD1_SHIFT                               16
#define BCHP_CCE_0_Data7_WORD1_DEFAULT                             0x00000000

/* CCE_0 :: Data7 :: WORD0 [15:00] */
#define BCHP_CCE_0_Data7_WORD0_MASK                                0x0000ffff
#define BCHP_CCE_0_Data7_WORD0_SHIFT                               0
#define BCHP_CCE_0_Data7_WORD0_DEFAULT                             0x00000000

/***************************************************************************
 *Data8 - Data Register 8
 ***************************************************************************/
/* CCE_0 :: Data8 :: WORD1 [31:16] */
#define BCHP_CCE_0_Data8_WORD1_MASK                                0xffff0000
#define BCHP_CCE_0_Data8_WORD1_SHIFT                               16
#define BCHP_CCE_0_Data8_WORD1_DEFAULT                             0x00000000

/* CCE_0 :: Data8 :: WORD0 [15:00] */
#define BCHP_CCE_0_Data8_WORD0_MASK                                0x0000ffff
#define BCHP_CCE_0_Data8_WORD0_SHIFT                               0
#define BCHP_CCE_0_Data8_WORD0_DEFAULT                             0x00000000

/***************************************************************************
 *Data9 - Data Register 9
 ***************************************************************************/
/* CCE_0 :: Data9 :: WORD1 [31:16] */
#define BCHP_CCE_0_Data9_WORD1_MASK                                0xffff0000
#define BCHP_CCE_0_Data9_WORD1_SHIFT                               16
#define BCHP_CCE_0_Data9_WORD1_DEFAULT                             0x00000000

/* CCE_0 :: Data9 :: WORD0 [15:00] */
#define BCHP_CCE_0_Data9_WORD0_MASK                                0x0000ffff
#define BCHP_CCE_0_Data9_WORD0_SHIFT                               0
#define BCHP_CCE_0_Data9_WORD0_DEFAULT                             0x00000000

/***************************************************************************
 *Data10 - Data Register 10
 ***************************************************************************/
/* CCE_0 :: Data10 :: WORD1 [31:16] */
#define BCHP_CCE_0_Data10_WORD1_MASK                               0xffff0000
#define BCHP_CCE_0_Data10_WORD1_SHIFT                              16
#define BCHP_CCE_0_Data10_WORD1_DEFAULT                            0x00000000

/* CCE_0 :: Data10 :: WORD0 [15:00] */
#define BCHP_CCE_0_Data10_WORD0_MASK                               0x0000ffff
#define BCHP_CCE_0_Data10_WORD0_SHIFT                              0
#define BCHP_CCE_0_Data10_WORD0_DEFAULT                            0x00000000

/***************************************************************************
 *Data11 - Data Register 11
 ***************************************************************************/
/* CCE_0 :: Data11 :: WORD1 [31:16] */
#define BCHP_CCE_0_Data11_WORD1_MASK                               0xffff0000
#define BCHP_CCE_0_Data11_WORD1_SHIFT                              16
#define BCHP_CCE_0_Data11_WORD1_DEFAULT                            0x00000000

/* CCE_0 :: Data11 :: WORD0 [15:00] */
#define BCHP_CCE_0_Data11_WORD0_MASK                               0x0000ffff
#define BCHP_CCE_0_Data11_WORD0_SHIFT                              0
#define BCHP_CCE_0_Data11_WORD0_DEFAULT                            0x00000000

/***************************************************************************
 *Data12 - Data Register 12
 ***************************************************************************/
/* CCE_0 :: Data12 :: WORD1 [31:16] */
#define BCHP_CCE_0_Data12_WORD1_MASK                               0xffff0000
#define BCHP_CCE_0_Data12_WORD1_SHIFT                              16
#define BCHP_CCE_0_Data12_WORD1_DEFAULT                            0x00000000

/* CCE_0 :: Data12 :: WORD0 [15:00] */
#define BCHP_CCE_0_Data12_WORD0_MASK                               0x0000ffff
#define BCHP_CCE_0_Data12_WORD0_SHIFT                              0
#define BCHP_CCE_0_Data12_WORD0_DEFAULT                            0x00000000

/***************************************************************************
 *Data13 - Data Register 13
 ***************************************************************************/
/* CCE_0 :: Data13 :: WORD1 [31:16] */
#define BCHP_CCE_0_Data13_WORD1_MASK                               0xffff0000
#define BCHP_CCE_0_Data13_WORD1_SHIFT                              16
#define BCHP_CCE_0_Data13_WORD1_DEFAULT                            0x00000000

/* CCE_0 :: Data13 :: WORD0 [15:00] */
#define BCHP_CCE_0_Data13_WORD0_MASK                               0x0000ffff
#define BCHP_CCE_0_Data13_WORD0_SHIFT                              0
#define BCHP_CCE_0_Data13_WORD0_DEFAULT                            0x00000000

/***************************************************************************
 *Data14 - Data Register 14
 ***************************************************************************/
/* CCE_0 :: Data14 :: WORD1 [31:16] */
#define BCHP_CCE_0_Data14_WORD1_MASK                               0xffff0000
#define BCHP_CCE_0_Data14_WORD1_SHIFT                              16
#define BCHP_CCE_0_Data14_WORD1_DEFAULT                            0x00000000

/* CCE_0 :: Data14 :: WORD0 [15:00] */
#define BCHP_CCE_0_Data14_WORD0_MASK                               0x0000ffff
#define BCHP_CCE_0_Data14_WORD0_SHIFT                              0
#define BCHP_CCE_0_Data14_WORD0_DEFAULT                            0x00000000

/***************************************************************************
 *Data15 - Data Register 15
 ***************************************************************************/
/* CCE_0 :: Data15 :: WORD1 [31:16] */
#define BCHP_CCE_0_Data15_WORD1_MASK                               0xffff0000
#define BCHP_CCE_0_Data15_WORD1_SHIFT                              16
#define BCHP_CCE_0_Data15_WORD1_DEFAULT                            0x00000000

/* CCE_0 :: Data15 :: WORD0 [15:00] */
#define BCHP_CCE_0_Data15_WORD0_MASK                               0x0000ffff
#define BCHP_CCE_0_Data15_WORD0_SHIFT                              0
#define BCHP_CCE_0_Data15_WORD0_DEFAULT                            0x00000000

#endif /* #ifndef BCHP_CCE_0_H__ */

/* End of File */

/***************************************************************************
 *     Copyright (c) 1999-2007, Broadcom Corporation
 *     All Rights Reserved
 *     Confidential Property of Broadcom Corporation
 *
 *
 * THIS SOFTWARE MAY ONLY BE USED SUBJECT TO AN EXECUTED SOFTWARE LICENSE
 * AGREEMENT  BETWEEN THE USER AND BROADCOM.  YOU HAVE NO RIGHT TO USE OR
 * EXPLOIT THIS MATERIAL EXCEPT SUBJECT TO THE TERMS OF SUCH AN AGREEMENT.
 *
 * $brcm_Workfile: $
 * $brcm_Revision: $
 * $brcm_Date: $
 *
 * Module Description:
 *                     DO NOT EDIT THIS FILE DIRECTLY
 *
 * This module was generated magically with RDB from a source description
 * file. You must edit the source file for changes to be made to this file.
 *
 *
 * Date:           Generated on         Mon Jul 23 12:01:56 2007
 *                 MD5 Checksum         61f9c4d8dcdcd06017506dddbf23f434
 *
 * Compiled with:  RDB Utility          combo_header.pl
 *                 RDB Parser           3.0
 *                 unknown              unknown
 *                 Perl Interpreter     5.008004
 *                 Operating System     linux
 *
 * Revision History:
 *
 * $brcm_Log: $
 * 
 ***************************************************************************/

#ifndef BCHP_AMOLE_656_H__
#define BCHP_AMOLE_656_H__

/***************************************************************************
 *AMOLE_656 - Amol Encoder
 ***************************************************************************/
#define BCHP_AMOLE_656_REVID                     0x0018a300 /* AMOL Encoder Revision ID Register */
#define BCHP_AMOLE_656_CONTROL                   0x0018a308 /* Control Register */
#define BCHP_AMOLE_656_ACT_LINE_BASE_TOP         0x0018a30c /* Top Field Active Line and Base Register */
#define BCHP_AMOLE_656_ACT_LINE_BASE_BOT         0x0018a310 /* Bottom Field Active Line and Base Register */
#define BCHP_AMOLE_656_DATA_WORD0_BANK0          0x0018a31c /* Bank 0 Word 0 Data Register */
#define BCHP_AMOLE_656_DATA_WORD1_BANK0          0x0018a320 /* Bank 0 Word 1 Data Register */
#define BCHP_AMOLE_656_DATA_WORD2_BANK0          0x0018a324 /* Bank 0 Word 2 Data Register */
#define BCHP_AMOLE_656_DATA_WORD3_BANK0          0x0018a328 /* Bank 0 Word 3 Data Register */
#define BCHP_AMOLE_656_DATA_WORD4_BANK0          0x0018a32c /* Bank 0 Word 4 Data Register */
#define BCHP_AMOLE_656_DATA_WORD5_BANK0          0x0018a330 /* Bank 0 Word 5 Data Register */
#define BCHP_AMOLE_656_DATA_WORD0_BANK1          0x0018a334 /* Bank 1 Word 0 Data Register */
#define BCHP_AMOLE_656_DATA_WORD1_BANK1          0x0018a338 /* Bank 1 Word 1 Data Register */
#define BCHP_AMOLE_656_DATA_WORD2_BANK1          0x0018a33c /* Bank 1 Word 2 Data Register */
#define BCHP_AMOLE_656_DATA_WORD3_BANK1          0x0018a340 /* Bank 1 Word 3 Data Register */
#define BCHP_AMOLE_656_DATA_WORD4_BANK1          0x0018a344 /* Bank 1 Word 4 Data Register */
#define BCHP_AMOLE_656_DATA_WORD5_BANK1          0x0018a348 /* Bank 1 Word 5 Data Register */
#define BCHP_AMOLE_656_DATA_WORD0_BANK2          0x0018a34c /* Bank 2 Word 0 Data Register */
#define BCHP_AMOLE_656_DATA_WORD1_BANK2          0x0018a350 /* Bank 2 Word 1 Data Register */
#define BCHP_AMOLE_656_DATA_WORD2_BANK2          0x0018a354 /* Bank 2 Word 2 Data Register */
#define BCHP_AMOLE_656_DATA_WORD3_BANK2          0x0018a358 /* Bank 2 Word 3 Data Register */
#define BCHP_AMOLE_656_DATA_WORD4_BANK2          0x0018a35c /* Bank 2 Word 4 Data Register */
#define BCHP_AMOLE_656_DATA_WORD5_BANK2          0x0018a360 /* Bank 2 Word 5 Data Register */
#define BCHP_AMOLE_656_DATA_WORD0_BANK3          0x0018a364 /* Bank 3 Word 0 Data Register */
#define BCHP_AMOLE_656_DATA_WORD1_BANK3          0x0018a368 /* Bank 3 Word 1 Data Register */
#define BCHP_AMOLE_656_DATA_WORD2_BANK3          0x0018a36c /* Bank 3 Word 2 Data Register */
#define BCHP_AMOLE_656_DATA_WORD3_BANK3          0x0018a370 /* Bank 3 Word 3 Data Register */
#define BCHP_AMOLE_656_DATA_WORD4_BANK3          0x0018a374 /* Bank 3 Word 4 Data Register */
#define BCHP_AMOLE_656_DATA_WORD5_BANK3          0x0018a378 /* Bank 3 Word 5 Data Register */
#define BCHP_AMOLE_656_BYTES_PER_LINE            0x0018a37c /* Bytes Per Line */
#define BCHP_AMOLE_656_NULL                      0x0018a380 /* NULL Register */
#define BCHP_AMOLE_656_WRPTR                     0x0018a384 /* Write Pointer Register */
#define BCHP_AMOLE_656_RDPTR                     0x0018a388 /* Read Pointer Register */
#define BCHP_AMOLE_656_STATUS                    0x0018a38c /* Status Register */

/***************************************************************************
 *REVID - AMOL Encoder Revision ID Register
 ***************************************************************************/
/* AMOLE_656 :: REVID :: reserved0 [31:16] */
#define BCHP_AMOLE_656_REVID_reserved0_MASK                        0xffff0000
#define BCHP_AMOLE_656_REVID_reserved0_SHIFT                       16

/* AMOLE_656 :: REVID :: REVID [15:00] */
#define BCHP_AMOLE_656_REVID_REVID_MASK                            0x0000ffff
#define BCHP_AMOLE_656_REVID_REVID_SHIFT                           0

/***************************************************************************
 *CONTROL - Control Register
 ***************************************************************************/
/* AMOLE_656 :: CONTROL :: reserved0 [31:20] */
#define BCHP_AMOLE_656_CONTROL_reserved0_MASK                      0xfff00000
#define BCHP_AMOLE_656_CONTROL_reserved0_SHIFT                     20

/* AMOLE_656 :: CONTROL :: reserved_for_eco1 [19:16] */
#define BCHP_AMOLE_656_CONTROL_reserved_for_eco1_MASK              0x000f0000
#define BCHP_AMOLE_656_CONTROL_reserved_for_eco1_SHIFT             16

/* AMOLE_656 :: CONTROL :: reserved2 [15:03] */
#define BCHP_AMOLE_656_CONTROL_reserved2_MASK                      0x0000fff8
#define BCHP_AMOLE_656_CONTROL_reserved2_SHIFT                     3

/* AMOLE_656 :: CONTROL :: FIFO_FREEZE [02:02] */
#define BCHP_AMOLE_656_CONTROL_FIFO_FREEZE_MASK                    0x00000004
#define BCHP_AMOLE_656_CONTROL_FIFO_FREEZE_SHIFT                   2

/* AMOLE_656 :: CONTROL :: NULL_MODE [01:01] */
#define BCHP_AMOLE_656_CONTROL_NULL_MODE_MASK                      0x00000002
#define BCHP_AMOLE_656_CONTROL_NULL_MODE_SHIFT                     1

/* AMOLE_656 :: CONTROL :: ENABLE [00:00] */
#define BCHP_AMOLE_656_CONTROL_ENABLE_MASK                         0x00000001
#define BCHP_AMOLE_656_CONTROL_ENABLE_SHIFT                        0
#define BCHP_AMOLE_656_CONTROL_ENABLE_OFF                          0
#define BCHP_AMOLE_656_CONTROL_ENABLE_ON                           1

/***************************************************************************
 *ACT_LINE_BASE_TOP - Top Field Active Line and Base Register
 ***************************************************************************/
/* AMOLE_656 :: ACT_LINE_BASE_TOP :: reserved0 [31:24] */
#define BCHP_AMOLE_656_ACT_LINE_BASE_TOP_reserved0_MASK            0xff000000
#define BCHP_AMOLE_656_ACT_LINE_BASE_TOP_reserved0_SHIFT           24

/* AMOLE_656 :: ACT_LINE_BASE_TOP :: ACTIVE_LINE [23:08] */
#define BCHP_AMOLE_656_ACT_LINE_BASE_TOP_ACTIVE_LINE_MASK          0x00ffff00
#define BCHP_AMOLE_656_ACT_LINE_BASE_TOP_ACTIVE_LINE_SHIFT         8

/* AMOLE_656 :: ACT_LINE_BASE_TOP :: reserved1 [07:07] */
#define BCHP_AMOLE_656_ACT_LINE_BASE_TOP_reserved1_MASK            0x00000080
#define BCHP_AMOLE_656_ACT_LINE_BASE_TOP_reserved1_SHIFT           7

/* AMOLE_656 :: ACT_LINE_BASE_TOP :: BASE [06:00] */
#define BCHP_AMOLE_656_ACT_LINE_BASE_TOP_BASE_MASK                 0x0000007f
#define BCHP_AMOLE_656_ACT_LINE_BASE_TOP_BASE_SHIFT                0

/***************************************************************************
 *ACT_LINE_BASE_BOT - Bottom Field Active Line and Base Register
 ***************************************************************************/
/* AMOLE_656 :: ACT_LINE_BASE_BOT :: reserved0 [31:24] */
#define BCHP_AMOLE_656_ACT_LINE_BASE_BOT_reserved0_MASK            0xff000000
#define BCHP_AMOLE_656_ACT_LINE_BASE_BOT_reserved0_SHIFT           24

/* AMOLE_656 :: ACT_LINE_BASE_BOT :: ACTIVE_LINE [23:08] */
#define BCHP_AMOLE_656_ACT_LINE_BASE_BOT_ACTIVE_LINE_MASK          0x00ffff00
#define BCHP_AMOLE_656_ACT_LINE_BASE_BOT_ACTIVE_LINE_SHIFT         8

/* AMOLE_656 :: ACT_LINE_BASE_BOT :: reserved1 [07:07] */
#define BCHP_AMOLE_656_ACT_LINE_BASE_BOT_reserved1_MASK            0x00000080
#define BCHP_AMOLE_656_ACT_LINE_BASE_BOT_reserved1_SHIFT           7

/* AMOLE_656 :: ACT_LINE_BASE_BOT :: BASE [06:00] */
#define BCHP_AMOLE_656_ACT_LINE_BASE_BOT_BASE_MASK                 0x0000007f
#define BCHP_AMOLE_656_ACT_LINE_BASE_BOT_BASE_SHIFT                0

/***************************************************************************
 *DATA_WORD0_BANK0 - Bank 0 Word 0 Data Register
 ***************************************************************************/
/* AMOLE_656 :: DATA_WORD0_BANK0 :: VALUE [31:00] */
#define BCHP_AMOLE_656_DATA_WORD0_BANK0_VALUE_MASK                 0xffffffff
#define BCHP_AMOLE_656_DATA_WORD0_BANK0_VALUE_SHIFT                0

/***************************************************************************
 *DATA_WORD1_BANK0 - Bank 0 Word 1 Data Register
 ***************************************************************************/
/* AMOLE_656 :: DATA_WORD1_BANK0 :: VALUE [31:00] */
#define BCHP_AMOLE_656_DATA_WORD1_BANK0_VALUE_MASK                 0xffffffff
#define BCHP_AMOLE_656_DATA_WORD1_BANK0_VALUE_SHIFT                0

/***************************************************************************
 *DATA_WORD2_BANK0 - Bank 0 Word 2 Data Register
 ***************************************************************************/
/* AMOLE_656 :: DATA_WORD2_BANK0 :: VALUE [31:00] */
#define BCHP_AMOLE_656_DATA_WORD2_BANK0_VALUE_MASK                 0xffffffff
#define BCHP_AMOLE_656_DATA_WORD2_BANK0_VALUE_SHIFT                0

/***************************************************************************
 *DATA_WORD3_BANK0 - Bank 0 Word 3 Data Register
 ***************************************************************************/
/* AMOLE_656 :: DATA_WORD3_BANK0 :: VALUE [31:00] */
#define BCHP_AMOLE_656_DATA_WORD3_BANK0_VALUE_MASK                 0xffffffff
#define BCHP_AMOLE_656_DATA_WORD3_BANK0_VALUE_SHIFT                0

/***************************************************************************
 *DATA_WORD4_BANK0 - Bank 0 Word 4 Data Register
 ***************************************************************************/
/* AMOLE_656 :: DATA_WORD4_BANK0 :: VALUE [31:00] */
#define BCHP_AMOLE_656_DATA_WORD4_BANK0_VALUE_MASK                 0xffffffff
#define BCHP_AMOLE_656_DATA_WORD4_BANK0_VALUE_SHIFT                0

/***************************************************************************
 *DATA_WORD5_BANK0 - Bank 0 Word 5 Data Register
 ***************************************************************************/
/* AMOLE_656 :: DATA_WORD5_BANK0 :: VALUE [31:00] */
#define BCHP_AMOLE_656_DATA_WORD5_BANK0_VALUE_MASK                 0xffffffff
#define BCHP_AMOLE_656_DATA_WORD5_BANK0_VALUE_SHIFT                0

/***************************************************************************
 *DATA_WORD0_BANK1 - Bank 1 Word 0 Data Register
 ***************************************************************************/
/* AMOLE_656 :: DATA_WORD0_BANK1 :: VALUE [31:00] */
#define BCHP_AMOLE_656_DATA_WORD0_BANK1_VALUE_MASK                 0xffffffff
#define BCHP_AMOLE_656_DATA_WORD0_BANK1_VALUE_SHIFT                0

/***************************************************************************
 *DATA_WORD1_BANK1 - Bank 1 Word 1 Data Register
 ***************************************************************************/
/* AMOLE_656 :: DATA_WORD1_BANK1 :: VALUE [31:00] */
#define BCHP_AMOLE_656_DATA_WORD1_BANK1_VALUE_MASK                 0xffffffff
#define BCHP_AMOLE_656_DATA_WORD1_BANK1_VALUE_SHIFT                0

/***************************************************************************
 *DATA_WORD2_BANK1 - Bank 1 Word 2 Data Register
 ***************************************************************************/
/* AMOLE_656 :: DATA_WORD2_BANK1 :: VALUE [31:00] */
#define BCHP_AMOLE_656_DATA_WORD2_BANK1_VALUE_MASK                 0xffffffff
#define BCHP_AMOLE_656_DATA_WORD2_BANK1_VALUE_SHIFT                0

/***************************************************************************
 *DATA_WORD3_BANK1 - Bank 1 Word 3 Data Register
 ***************************************************************************/
/* AMOLE_656 :: DATA_WORD3_BANK1 :: VALUE [31:00] */
#define BCHP_AMOLE_656_DATA_WORD3_BANK1_VALUE_MASK                 0xffffffff
#define BCHP_AMOLE_656_DATA_WORD3_BANK1_VALUE_SHIFT                0

/***************************************************************************
 *DATA_WORD4_BANK1 - Bank 1 Word 4 Data Register
 ***************************************************************************/
/* AMOLE_656 :: DATA_WORD4_BANK1 :: VALUE [31:00] */
#define BCHP_AMOLE_656_DATA_WORD4_BANK1_VALUE_MASK                 0xffffffff
#define BCHP_AMOLE_656_DATA_WORD4_BANK1_VALUE_SHIFT                0

/***************************************************************************
 *DATA_WORD5_BANK1 - Bank 1 Word 5 Data Register
 ***************************************************************************/
/* AMOLE_656 :: DATA_WORD5_BANK1 :: VALUE [31:00] */
#define BCHP_AMOLE_656_DATA_WORD5_BANK1_VALUE_MASK                 0xffffffff
#define BCHP_AMOLE_656_DATA_WORD5_BANK1_VALUE_SHIFT                0

/***************************************************************************
 *DATA_WORD0_BANK2 - Bank 2 Word 0 Data Register
 ***************************************************************************/
/* AMOLE_656 :: DATA_WORD0_BANK2 :: VALUE [31:00] */
#define BCHP_AMOLE_656_DATA_WORD0_BANK2_VALUE_MASK                 0xffffffff
#define BCHP_AMOLE_656_DATA_WORD0_BANK2_VALUE_SHIFT                0

/***************************************************************************
 *DATA_WORD1_BANK2 - Bank 2 Word 1 Data Register
 ***************************************************************************/
/* AMOLE_656 :: DATA_WORD1_BANK2 :: VALUE [31:00] */
#define BCHP_AMOLE_656_DATA_WORD1_BANK2_VALUE_MASK                 0xffffffff
#define BCHP_AMOLE_656_DATA_WORD1_BANK2_VALUE_SHIFT                0

/***************************************************************************
 *DATA_WORD2_BANK2 - Bank 2 Word 2 Data Register
 ***************************************************************************/
/* AMOLE_656 :: DATA_WORD2_BANK2 :: VALUE [31:00] */
#define BCHP_AMOLE_656_DATA_WORD2_BANK2_VALUE_MASK                 0xffffffff
#define BCHP_AMOLE_656_DATA_WORD2_BANK2_VALUE_SHIFT                0

/***************************************************************************
 *DATA_WORD3_BANK2 - Bank 2 Word 3 Data Register
 ***************************************************************************/
/* AMOLE_656 :: DATA_WORD3_BANK2 :: VALUE [31:00] */
#define BCHP_AMOLE_656_DATA_WORD3_BANK2_VALUE_MASK                 0xffffffff
#define BCHP_AMOLE_656_DATA_WORD3_BANK2_VALUE_SHIFT                0

/***************************************************************************
 *DATA_WORD4_BANK2 - Bank 2 Word 4 Data Register
 ***************************************************************************/
/* AMOLE_656 :: DATA_WORD4_BANK2 :: VALUE [31:00] */
#define BCHP_AMOLE_656_DATA_WORD4_BANK2_VALUE_MASK                 0xffffffff
#define BCHP_AMOLE_656_DATA_WORD4_BANK2_VALUE_SHIFT                0

/***************************************************************************
 *DATA_WORD5_BANK2 - Bank 2 Word 5 Data Register
 ***************************************************************************/
/* AMOLE_656 :: DATA_WORD5_BANK2 :: VALUE [31:00] */
#define BCHP_AMOLE_656_DATA_WORD5_BANK2_VALUE_MASK                 0xffffffff
#define BCHP_AMOLE_656_DATA_WORD5_BANK2_VALUE_SHIFT                0

/***************************************************************************
 *DATA_WORD0_BANK3 - Bank 3 Word 0 Data Register
 ***************************************************************************/
/* AMOLE_656 :: DATA_WORD0_BANK3 :: VALUE [31:00] */
#define BCHP_AMOLE_656_DATA_WORD0_BANK3_VALUE_MASK                 0xffffffff
#define BCHP_AMOLE_656_DATA_WORD0_BANK3_VALUE_SHIFT                0

/***************************************************************************
 *DATA_WORD1_BANK3 - Bank 3 Word 1 Data Register
 ***************************************************************************/
/* AMOLE_656 :: DATA_WORD1_BANK3 :: VALUE [31:00] */
#define BCHP_AMOLE_656_DATA_WORD1_BANK3_VALUE_MASK                 0xffffffff
#define BCHP_AMOLE_656_DATA_WORD1_BANK3_VALUE_SHIFT                0

/***************************************************************************
 *DATA_WORD2_BANK3 - Bank 3 Word 2 Data Register
 ***************************************************************************/
/* AMOLE_656 :: DATA_WORD2_BANK3 :: VALUE [31:00] */
#define BCHP_AMOLE_656_DATA_WORD2_BANK3_VALUE_MASK                 0xffffffff
#define BCHP_AMOLE_656_DATA_WORD2_BANK3_VALUE_SHIFT                0

/***************************************************************************
 *DATA_WORD3_BANK3 - Bank 3 Word 3 Data Register
 ***************************************************************************/
/* AMOLE_656 :: DATA_WORD3_BANK3 :: VALUE [31:00] */
#define BCHP_AMOLE_656_DATA_WORD3_BANK3_VALUE_MASK                 0xffffffff
#define BCHP_AMOLE_656_DATA_WORD3_BANK3_VALUE_SHIFT                0

/***************************************************************************
 *DATA_WORD4_BANK3 - Bank 3 Word 4 Data Register
 ***************************************************************************/
/* AMOLE_656 :: DATA_WORD4_BANK3 :: VALUE [31:00] */
#define BCHP_AMOLE_656_DATA_WORD4_BANK3_VALUE_MASK                 0xffffffff
#define BCHP_AMOLE_656_DATA_WORD4_BANK3_VALUE_SHIFT                0

/***************************************************************************
 *DATA_WORD5_BANK3 - Bank 3 Word 5 Data Register
 ***************************************************************************/
/* AMOLE_656 :: DATA_WORD5_BANK3 :: VALUE [31:00] */
#define BCHP_AMOLE_656_DATA_WORD5_BANK3_VALUE_MASK                 0xffffffff
#define BCHP_AMOLE_656_DATA_WORD5_BANK3_VALUE_SHIFT                0

/***************************************************************************
 *BYTES_PER_LINE - Bytes Per Line
 ***************************************************************************/
/* AMOLE_656 :: BYTES_PER_LINE :: reserved0 [31:08] */
#define BCHP_AMOLE_656_BYTES_PER_LINE_reserved0_MASK               0xffffff00
#define BCHP_AMOLE_656_BYTES_PER_LINE_reserved0_SHIFT              8

/* AMOLE_656 :: BYTES_PER_LINE :: LINE22_BANK3 [07:07] */
#define BCHP_AMOLE_656_BYTES_PER_LINE_LINE22_BANK3_MASK            0x00000080
#define BCHP_AMOLE_656_BYTES_PER_LINE_LINE22_BANK3_SHIFT           7
#define BCHP_AMOLE_656_BYTES_PER_LINE_LINE22_BANK3_SIX_BYTES       0
#define BCHP_AMOLE_656_BYTES_PER_LINE_LINE22_BANK3_TWELVE_BYTES    1

/* AMOLE_656 :: BYTES_PER_LINE :: LINE20_BANK3 [06:06] */
#define BCHP_AMOLE_656_BYTES_PER_LINE_LINE20_BANK3_MASK            0x00000040
#define BCHP_AMOLE_656_BYTES_PER_LINE_LINE20_BANK3_SHIFT           6
#define BCHP_AMOLE_656_BYTES_PER_LINE_LINE20_BANK3_SIX_BYTES       0
#define BCHP_AMOLE_656_BYTES_PER_LINE_LINE20_BANK3_TWELVE_BYTES    1

/* AMOLE_656 :: BYTES_PER_LINE :: LINE22_BANK2 [05:05] */
#define BCHP_AMOLE_656_BYTES_PER_LINE_LINE22_BANK2_MASK            0x00000020
#define BCHP_AMOLE_656_BYTES_PER_LINE_LINE22_BANK2_SHIFT           5
#define BCHP_AMOLE_656_BYTES_PER_LINE_LINE22_BANK2_SIX_BYTES       0
#define BCHP_AMOLE_656_BYTES_PER_LINE_LINE22_BANK2_TWELVE_BYTES    1

/* AMOLE_656 :: BYTES_PER_LINE :: LINE20_BANK2 [04:04] */
#define BCHP_AMOLE_656_BYTES_PER_LINE_LINE20_BANK2_MASK            0x00000010
#define BCHP_AMOLE_656_BYTES_PER_LINE_LINE20_BANK2_SHIFT           4
#define BCHP_AMOLE_656_BYTES_PER_LINE_LINE20_BANK2_SIX_BYTES       0
#define BCHP_AMOLE_656_BYTES_PER_LINE_LINE20_BANK2_TWELVE_BYTES    1

/* AMOLE_656 :: BYTES_PER_LINE :: LINE22_BANK1 [03:03] */
#define BCHP_AMOLE_656_BYTES_PER_LINE_LINE22_BANK1_MASK            0x00000008
#define BCHP_AMOLE_656_BYTES_PER_LINE_LINE22_BANK1_SHIFT           3
#define BCHP_AMOLE_656_BYTES_PER_LINE_LINE22_BANK1_SIX_BYTES       0
#define BCHP_AMOLE_656_BYTES_PER_LINE_LINE22_BANK1_TWELVE_BYTES    1

/* AMOLE_656 :: BYTES_PER_LINE :: LINE20_BANK1 [02:02] */
#define BCHP_AMOLE_656_BYTES_PER_LINE_LINE20_BANK1_MASK            0x00000004
#define BCHP_AMOLE_656_BYTES_PER_LINE_LINE20_BANK1_SHIFT           2
#define BCHP_AMOLE_656_BYTES_PER_LINE_LINE20_BANK1_SIX_BYTES       0
#define BCHP_AMOLE_656_BYTES_PER_LINE_LINE20_BANK1_TWELVE_BYTES    1

/* AMOLE_656 :: BYTES_PER_LINE :: LINE22_BANK0 [01:01] */
#define BCHP_AMOLE_656_BYTES_PER_LINE_LINE22_BANK0_MASK            0x00000002
#define BCHP_AMOLE_656_BYTES_PER_LINE_LINE22_BANK0_SHIFT           1
#define BCHP_AMOLE_656_BYTES_PER_LINE_LINE22_BANK0_SIX_BYTES       0
#define BCHP_AMOLE_656_BYTES_PER_LINE_LINE22_BANK0_TWELVE_BYTES    1

/* AMOLE_656 :: BYTES_PER_LINE :: LINE20_BANK0 [00:00] */
#define BCHP_AMOLE_656_BYTES_PER_LINE_LINE20_BANK0_MASK            0x00000001
#define BCHP_AMOLE_656_BYTES_PER_LINE_LINE20_BANK0_SHIFT           0
#define BCHP_AMOLE_656_BYTES_PER_LINE_LINE20_BANK0_SIX_BYTES       0
#define BCHP_AMOLE_656_BYTES_PER_LINE_LINE20_BANK0_TWELVE_BYTES    1

/***************************************************************************
 *NULL - NULL Register
 ***************************************************************************/
/* AMOLE_656 :: NULL :: reserved0 [31:12] */
#define BCHP_AMOLE_656_NULL_reserved0_MASK                         0xfffff000
#define BCHP_AMOLE_656_NULL_reserved0_SHIFT                        12

/* AMOLE_656 :: NULL :: NULL_ENABLE_BANK3 [11:11] */
#define BCHP_AMOLE_656_NULL_NULL_ENABLE_BANK3_MASK                 0x00000800
#define BCHP_AMOLE_656_NULL_NULL_ENABLE_BANK3_SHIFT                11

/* AMOLE_656 :: NULL :: NULL_ENABLE_BANK2 [10:10] */
#define BCHP_AMOLE_656_NULL_NULL_ENABLE_BANK2_MASK                 0x00000400
#define BCHP_AMOLE_656_NULL_NULL_ENABLE_BANK2_SHIFT                10

/* AMOLE_656 :: NULL :: NULL_ENABLE_BANK1 [09:09] */
#define BCHP_AMOLE_656_NULL_NULL_ENABLE_BANK1_MASK                 0x00000200
#define BCHP_AMOLE_656_NULL_NULL_ENABLE_BANK1_SHIFT                9

/* AMOLE_656 :: NULL :: NULL_ENABLE_BANK0 [08:08] */
#define BCHP_AMOLE_656_NULL_NULL_ENABLE_BANK0_MASK                 0x00000100
#define BCHP_AMOLE_656_NULL_NULL_ENABLE_BANK0_SHIFT                8

/* AMOLE_656 :: NULL :: CHARACTER [07:00] */
#define BCHP_AMOLE_656_NULL_CHARACTER_MASK                         0x000000ff
#define BCHP_AMOLE_656_NULL_CHARACTER_SHIFT                        0

/***************************************************************************
 *WRPTR - Write Pointer Register
 ***************************************************************************/
/* AMOLE_656 :: WRPTR :: reserved0 [31:03] */
#define BCHP_AMOLE_656_WRPTR_reserved0_MASK                        0xfffffff8
#define BCHP_AMOLE_656_WRPTR_reserved0_SHIFT                       3

/* AMOLE_656 :: WRPTR :: VALUE [02:00] */
#define BCHP_AMOLE_656_WRPTR_VALUE_MASK                            0x00000007
#define BCHP_AMOLE_656_WRPTR_VALUE_SHIFT                           0

/***************************************************************************
 *RDPTR - Read Pointer Register
 ***************************************************************************/
/* AMOLE_656 :: RDPTR :: reserved0 [31:03] */
#define BCHP_AMOLE_656_RDPTR_reserved0_MASK                        0xfffffff8
#define BCHP_AMOLE_656_RDPTR_reserved0_SHIFT                       3

/* AMOLE_656 :: RDPTR :: VALUE [02:00] */
#define BCHP_AMOLE_656_RDPTR_VALUE_MASK                            0x00000007
#define BCHP_AMOLE_656_RDPTR_VALUE_SHIFT                           0

/***************************************************************************
 *STATUS - Status Register
 ***************************************************************************/
/* AMOLE_656 :: STATUS :: reserved0 [31:06] */
#define BCHP_AMOLE_656_STATUS_reserved0_MASK                       0xffffffc0
#define BCHP_AMOLE_656_STATUS_reserved0_SHIFT                      6

/* AMOLE_656 :: STATUS :: FIFO_OVERFLOW [05:05] */
#define BCHP_AMOLE_656_STATUS_FIFO_OVERFLOW_MASK                   0x00000020
#define BCHP_AMOLE_656_STATUS_FIFO_OVERFLOW_SHIFT                  5

/* AMOLE_656 :: STATUS :: FIFO_UNDERFLOW [04:04] */
#define BCHP_AMOLE_656_STATUS_FIFO_UNDERFLOW_MASK                  0x00000010
#define BCHP_AMOLE_656_STATUS_FIFO_UNDERFLOW_SHIFT                 4

/* AMOLE_656 :: STATUS :: BANK3_656_ANCIL_DATA [03:03] */
#define BCHP_AMOLE_656_STATUS_BANK3_656_ANCIL_DATA_MASK            0x00000008
#define BCHP_AMOLE_656_STATUS_BANK3_656_ANCIL_DATA_SHIFT           3
#define BCHP_AMOLE_656_STATUS_BANK3_656_ANCIL_DATA_XMIT            1
#define BCHP_AMOLE_656_STATUS_BANK3_656_ANCIL_DATA_NOT_XMIT        0

/* AMOLE_656 :: STATUS :: BANK2_656_ANCIL_DATA [02:02] */
#define BCHP_AMOLE_656_STATUS_BANK2_656_ANCIL_DATA_MASK            0x00000004
#define BCHP_AMOLE_656_STATUS_BANK2_656_ANCIL_DATA_SHIFT           2
#define BCHP_AMOLE_656_STATUS_BANK2_656_ANCIL_DATA_XMIT            1
#define BCHP_AMOLE_656_STATUS_BANK2_656_ANCIL_DATA_NOT_XMIT        0

/* AMOLE_656 :: STATUS :: BANK1_656_ANCIL_DATA [01:01] */
#define BCHP_AMOLE_656_STATUS_BANK1_656_ANCIL_DATA_MASK            0x00000002
#define BCHP_AMOLE_656_STATUS_BANK1_656_ANCIL_DATA_SHIFT           1
#define BCHP_AMOLE_656_STATUS_BANK1_656_ANCIL_DATA_XMIT            1
#define BCHP_AMOLE_656_STATUS_BANK1_656_ANCIL_DATA_NOT_XMIT        0

/* AMOLE_656 :: STATUS :: BANK0_656_ANCIL_DATA [00:00] */
#define BCHP_AMOLE_656_STATUS_BANK0_656_ANCIL_DATA_MASK            0x00000001
#define BCHP_AMOLE_656_STATUS_BANK0_656_ANCIL_DATA_SHIFT           0
#define BCHP_AMOLE_656_STATUS_BANK0_656_ANCIL_DATA_XMIT            1
#define BCHP_AMOLE_656_STATUS_BANK0_656_ANCIL_DATA_NOT_XMIT        0

#endif /* #ifndef BCHP_AMOLE_656_H__ */

/* End of File */

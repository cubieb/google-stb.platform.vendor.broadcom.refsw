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
 * Date:           Generated on               Tue Jun 27 10:52:39 2017
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

#ifndef BCHP_XPT_WAKEUP_H__
#define BCHP_XPT_WAKEUP_H__

/***************************************************************************
 *XPT_WAKEUP - XPT WAKEUP Control Registers
 ***************************************************************************/
#define BCHP_XPT_WAKEUP_CTRL                     0x20a01000 /* [RW][32] Wake-up packet detection control */
#define BCHP_XPT_WAKEUP_STATUS                   0x20a01004 /* [RW][32] Wake-up packet detection control */
#define BCHP_XPT_WAKEUP_INTR_STATUS_REG          0x20a01008 /* [RW][32] Wake-up packet detection control */
#define BCHP_XPT_WAKEUP_INTR_STATUS_REG_EN       0x20a0100c /* [RW][32] Wake-up packet detection control */

/***************************************************************************
 *CTRL - Wake-up packet detection control
 ***************************************************************************/
/* XPT_WAKEUP :: CTRL :: reserved0 [31:17] */
#define BCHP_XPT_WAKEUP_CTRL_reserved0_MASK                        0xfffe0000
#define BCHP_XPT_WAKEUP_CTRL_reserved0_SHIFT                       17

/* XPT_WAKEUP :: CTRL :: INPUT_SEL_MSB [16:16] */
#define BCHP_XPT_WAKEUP_CTRL_INPUT_SEL_MSB_MASK                    0x00010000
#define BCHP_XPT_WAKEUP_CTRL_INPUT_SEL_MSB_SHIFT                   16
#define BCHP_XPT_WAKEUP_CTRL_INPUT_SEL_MSB_DEFAULT                 0x00000000

/* XPT_WAKEUP :: CTRL :: PKT_LENGTH [15:08] */
#define BCHP_XPT_WAKEUP_CTRL_PKT_LENGTH_MASK                       0x0000ff00
#define BCHP_XPT_WAKEUP_CTRL_PKT_LENGTH_SHIFT                      8
#define BCHP_XPT_WAKEUP_CTRL_PKT_LENGTH_DEFAULT                    0x000000bc

/* XPT_WAKEUP :: CTRL :: INPUT_SEL [07:04] */
#define BCHP_XPT_WAKEUP_CTRL_INPUT_SEL_MASK                        0x000000f0
#define BCHP_XPT_WAKEUP_CTRL_INPUT_SEL_SHIFT                       4
#define BCHP_XPT_WAKEUP_CTRL_INPUT_SEL_DEFAULT                     0x00000000

/* XPT_WAKEUP :: CTRL :: reserved1 [03:02] */
#define BCHP_XPT_WAKEUP_CTRL_reserved1_MASK                        0x0000000c
#define BCHP_XPT_WAKEUP_CTRL_reserved1_SHIFT                       2

/* XPT_WAKEUP :: CTRL :: ERROR_INPUT_IGNORE [01:01] */
#define BCHP_XPT_WAKEUP_CTRL_ERROR_INPUT_IGNORE_MASK               0x00000002
#define BCHP_XPT_WAKEUP_CTRL_ERROR_INPUT_IGNORE_SHIFT              1
#define BCHP_XPT_WAKEUP_CTRL_ERROR_INPUT_IGNORE_DEFAULT            0x00000000

/* XPT_WAKEUP :: CTRL :: PKT_DETECT_EN [00:00] */
#define BCHP_XPT_WAKEUP_CTRL_PKT_DETECT_EN_MASK                    0x00000001
#define BCHP_XPT_WAKEUP_CTRL_PKT_DETECT_EN_SHIFT                   0
#define BCHP_XPT_WAKEUP_CTRL_PKT_DETECT_EN_DEFAULT                 0x00000000

/***************************************************************************
 *STATUS - Wake-up packet detection control
 ***************************************************************************/
/* XPT_WAKEUP :: STATUS :: reserved0 [31:16] */
#define BCHP_XPT_WAKEUP_STATUS_reserved0_MASK                      0xffff0000
#define BCHP_XPT_WAKEUP_STATUS_reserved0_SHIFT                     16

/* XPT_WAKEUP :: STATUS :: PACKET_COUNT [15:08] */
#define BCHP_XPT_WAKEUP_STATUS_PACKET_COUNT_MASK                   0x0000ff00
#define BCHP_XPT_WAKEUP_STATUS_PACKET_COUNT_SHIFT                  8
#define BCHP_XPT_WAKEUP_STATUS_PACKET_COUNT_DEFAULT                0x00000000

/* XPT_WAKEUP :: STATUS :: reserved1 [07:07] */
#define BCHP_XPT_WAKEUP_STATUS_reserved1_MASK                      0x00000080
#define BCHP_XPT_WAKEUP_STATUS_reserved1_SHIFT                     7

/* XPT_WAKEUP :: STATUS :: PKT_FOUND_TYPE [06:04] */
#define BCHP_XPT_WAKEUP_STATUS_PKT_FOUND_TYPE_MASK                 0x00000070
#define BCHP_XPT_WAKEUP_STATUS_PKT_FOUND_TYPE_SHIFT                4
#define BCHP_XPT_WAKEUP_STATUS_PKT_FOUND_TYPE_DEFAULT              0x00000000

/* XPT_WAKEUP :: STATUS :: reserved2 [03:01] */
#define BCHP_XPT_WAKEUP_STATUS_reserved2_MASK                      0x0000000e
#define BCHP_XPT_WAKEUP_STATUS_reserved2_SHIFT                     1

/* XPT_WAKEUP :: STATUS :: PKT_FOUND [00:00] */
#define BCHP_XPT_WAKEUP_STATUS_PKT_FOUND_MASK                      0x00000001
#define BCHP_XPT_WAKEUP_STATUS_PKT_FOUND_SHIFT                     0
#define BCHP_XPT_WAKEUP_STATUS_PKT_FOUND_DEFAULT                   0x00000000

/***************************************************************************
 *INTR_STATUS_REG - Wake-up packet detection control
 ***************************************************************************/
/* XPT_WAKEUP :: INTR_STATUS_REG :: reserved0 [31:01] */
#define BCHP_XPT_WAKEUP_INTR_STATUS_REG_reserved0_MASK             0xfffffffe
#define BCHP_XPT_WAKEUP_INTR_STATUS_REG_reserved0_SHIFT            1

/* XPT_WAKEUP :: INTR_STATUS_REG :: PKT_DETECT [00:00] */
#define BCHP_XPT_WAKEUP_INTR_STATUS_REG_PKT_DETECT_MASK            0x00000001
#define BCHP_XPT_WAKEUP_INTR_STATUS_REG_PKT_DETECT_SHIFT           0
#define BCHP_XPT_WAKEUP_INTR_STATUS_REG_PKT_DETECT_DEFAULT         0x00000000

/***************************************************************************
 *INTR_STATUS_REG_EN - Wake-up packet detection control
 ***************************************************************************/
/* XPT_WAKEUP :: INTR_STATUS_REG_EN :: reserved0 [31:01] */
#define BCHP_XPT_WAKEUP_INTR_STATUS_REG_EN_reserved0_MASK          0xfffffffe
#define BCHP_XPT_WAKEUP_INTR_STATUS_REG_EN_reserved0_SHIFT         1

/* XPT_WAKEUP :: INTR_STATUS_REG_EN :: PKT_DETECT [00:00] */
#define BCHP_XPT_WAKEUP_INTR_STATUS_REG_EN_PKT_DETECT_MASK         0x00000001
#define BCHP_XPT_WAKEUP_INTR_STATUS_REG_EN_PKT_DETECT_SHIFT        0
#define BCHP_XPT_WAKEUP_INTR_STATUS_REG_EN_PKT_DETECT_DEFAULT      0x00000000

/***************************************************************************
 *PKT_MEM_%i - Wake-up Packet Memory
 ***************************************************************************/
#define BCHP_XPT_WAKEUP_PKT_MEM_i_ARRAY_BASE                       0x20a01020
#define BCHP_XPT_WAKEUP_PKT_MEM_i_ARRAY_START                      0
#define BCHP_XPT_WAKEUP_PKT_MEM_i_ARRAY_END                        199
#define BCHP_XPT_WAKEUP_PKT_MEM_i_ARRAY_ELEMENT_SIZE               32

/***************************************************************************
 *PKT_MEM_%i - Wake-up Packet Memory
 ***************************************************************************/
/* XPT_WAKEUP :: PKT_MEM_i :: reserved0 [31:08] */
#define BCHP_XPT_WAKEUP_PKT_MEM_i_reserved0_MASK                   0xffffff00
#define BCHP_XPT_WAKEUP_PKT_MEM_i_reserved0_SHIFT                  8

/* XPT_WAKEUP :: PKT_MEM_i :: PKT_BYTE [07:00] */
#define BCHP_XPT_WAKEUP_PKT_MEM_i_PKT_BYTE_MASK                    0x000000ff
#define BCHP_XPT_WAKEUP_PKT_MEM_i_PKT_BYTE_SHIFT                   0


/***************************************************************************
 *PKT_TYPE0_%i - Wake-up Packet Type0 Config Table
 ***************************************************************************/
#define BCHP_XPT_WAKEUP_PKT_TYPE0_i_ARRAY_BASE                     0x20a01340
#define BCHP_XPT_WAKEUP_PKT_TYPE0_i_ARRAY_START                    0
#define BCHP_XPT_WAKEUP_PKT_TYPE0_i_ARRAY_END                      199
#define BCHP_XPT_WAKEUP_PKT_TYPE0_i_ARRAY_ELEMENT_SIZE             32

/***************************************************************************
 *PKT_TYPE0_%i - Wake-up Packet Type0 Config Table
 ***************************************************************************/
/* XPT_WAKEUP :: PKT_TYPE0_i :: reserved0 [31:18] */
#define BCHP_XPT_WAKEUP_PKT_TYPE0_i_reserved0_MASK                 0xfffc0000
#define BCHP_XPT_WAKEUP_PKT_TYPE0_i_reserved0_SHIFT                18

/* XPT_WAKEUP :: PKT_TYPE0_i :: COMPARE_MASK_TYPE [17:16] */
#define BCHP_XPT_WAKEUP_PKT_TYPE0_i_COMPARE_MASK_TYPE_MASK         0x00030000
#define BCHP_XPT_WAKEUP_PKT_TYPE0_i_COMPARE_MASK_TYPE_SHIFT        16

/* XPT_WAKEUP :: PKT_TYPE0_i :: COMPARE_MASK [15:08] */
#define BCHP_XPT_WAKEUP_PKT_TYPE0_i_COMPARE_MASK_MASK              0x0000ff00
#define BCHP_XPT_WAKEUP_PKT_TYPE0_i_COMPARE_MASK_SHIFT             8

/* XPT_WAKEUP :: PKT_TYPE0_i :: COMPARE_BYTE [07:00] */
#define BCHP_XPT_WAKEUP_PKT_TYPE0_i_COMPARE_BYTE_MASK              0x000000ff
#define BCHP_XPT_WAKEUP_PKT_TYPE0_i_COMPARE_BYTE_SHIFT             0


/***************************************************************************
 *PKT_TYPE1_%i - Wake-up Packet Type1 Config Table
 ***************************************************************************/
#define BCHP_XPT_WAKEUP_PKT_TYPE1_i_ARRAY_BASE                     0x20a01660
#define BCHP_XPT_WAKEUP_PKT_TYPE1_i_ARRAY_START                    0
#define BCHP_XPT_WAKEUP_PKT_TYPE1_i_ARRAY_END                      199
#define BCHP_XPT_WAKEUP_PKT_TYPE1_i_ARRAY_ELEMENT_SIZE             32

/***************************************************************************
 *PKT_TYPE1_%i - Wake-up Packet Type1 Config Table
 ***************************************************************************/
/* XPT_WAKEUP :: PKT_TYPE1_i :: reserved0 [31:18] */
#define BCHP_XPT_WAKEUP_PKT_TYPE1_i_reserved0_MASK                 0xfffc0000
#define BCHP_XPT_WAKEUP_PKT_TYPE1_i_reserved0_SHIFT                18

/* XPT_WAKEUP :: PKT_TYPE1_i :: COMPARE_MASK_TYPE [17:16] */
#define BCHP_XPT_WAKEUP_PKT_TYPE1_i_COMPARE_MASK_TYPE_MASK         0x00030000
#define BCHP_XPT_WAKEUP_PKT_TYPE1_i_COMPARE_MASK_TYPE_SHIFT        16

/* XPT_WAKEUP :: PKT_TYPE1_i :: COMPARE_MASK [15:08] */
#define BCHP_XPT_WAKEUP_PKT_TYPE1_i_COMPARE_MASK_MASK              0x0000ff00
#define BCHP_XPT_WAKEUP_PKT_TYPE1_i_COMPARE_MASK_SHIFT             8

/* XPT_WAKEUP :: PKT_TYPE1_i :: COMPARE_BYTE [07:00] */
#define BCHP_XPT_WAKEUP_PKT_TYPE1_i_COMPARE_BYTE_MASK              0x000000ff
#define BCHP_XPT_WAKEUP_PKT_TYPE1_i_COMPARE_BYTE_SHIFT             0


/***************************************************************************
 *PKT_TYPE2_%i - Wake-up Packet Type2 Config Table
 ***************************************************************************/
#define BCHP_XPT_WAKEUP_PKT_TYPE2_i_ARRAY_BASE                     0x20a01980
#define BCHP_XPT_WAKEUP_PKT_TYPE2_i_ARRAY_START                    0
#define BCHP_XPT_WAKEUP_PKT_TYPE2_i_ARRAY_END                      199
#define BCHP_XPT_WAKEUP_PKT_TYPE2_i_ARRAY_ELEMENT_SIZE             32

/***************************************************************************
 *PKT_TYPE2_%i - Wake-up Packet Type2 Config Table
 ***************************************************************************/
/* XPT_WAKEUP :: PKT_TYPE2_i :: reserved0 [31:18] */
#define BCHP_XPT_WAKEUP_PKT_TYPE2_i_reserved0_MASK                 0xfffc0000
#define BCHP_XPT_WAKEUP_PKT_TYPE2_i_reserved0_SHIFT                18

/* XPT_WAKEUP :: PKT_TYPE2_i :: COMPARE_MASK_TYPE [17:16] */
#define BCHP_XPT_WAKEUP_PKT_TYPE2_i_COMPARE_MASK_TYPE_MASK         0x00030000
#define BCHP_XPT_WAKEUP_PKT_TYPE2_i_COMPARE_MASK_TYPE_SHIFT        16

/* XPT_WAKEUP :: PKT_TYPE2_i :: COMPARE_MASK [15:08] */
#define BCHP_XPT_WAKEUP_PKT_TYPE2_i_COMPARE_MASK_MASK              0x0000ff00
#define BCHP_XPT_WAKEUP_PKT_TYPE2_i_COMPARE_MASK_SHIFT             8

/* XPT_WAKEUP :: PKT_TYPE2_i :: COMPARE_BYTE [07:00] */
#define BCHP_XPT_WAKEUP_PKT_TYPE2_i_COMPARE_BYTE_MASK              0x000000ff
#define BCHP_XPT_WAKEUP_PKT_TYPE2_i_COMPARE_BYTE_SHIFT             0


/***************************************************************************
 *PKT_TYPE3_%i - Wake-up Packet Type3 Config Table
 ***************************************************************************/
#define BCHP_XPT_WAKEUP_PKT_TYPE3_i_ARRAY_BASE                     0x20a01ca0
#define BCHP_XPT_WAKEUP_PKT_TYPE3_i_ARRAY_START                    0
#define BCHP_XPT_WAKEUP_PKT_TYPE3_i_ARRAY_END                      199
#define BCHP_XPT_WAKEUP_PKT_TYPE3_i_ARRAY_ELEMENT_SIZE             32

/***************************************************************************
 *PKT_TYPE3_%i - Wake-up Packet Type3 Config Table
 ***************************************************************************/
/* XPT_WAKEUP :: PKT_TYPE3_i :: reserved0 [31:18] */
#define BCHP_XPT_WAKEUP_PKT_TYPE3_i_reserved0_MASK                 0xfffc0000
#define BCHP_XPT_WAKEUP_PKT_TYPE3_i_reserved0_SHIFT                18

/* XPT_WAKEUP :: PKT_TYPE3_i :: COMPARE_MASK_TYPE [17:16] */
#define BCHP_XPT_WAKEUP_PKT_TYPE3_i_COMPARE_MASK_TYPE_MASK         0x00030000
#define BCHP_XPT_WAKEUP_PKT_TYPE3_i_COMPARE_MASK_TYPE_SHIFT        16

/* XPT_WAKEUP :: PKT_TYPE3_i :: COMPARE_MASK [15:08] */
#define BCHP_XPT_WAKEUP_PKT_TYPE3_i_COMPARE_MASK_MASK              0x0000ff00
#define BCHP_XPT_WAKEUP_PKT_TYPE3_i_COMPARE_MASK_SHIFT             8

/* XPT_WAKEUP :: PKT_TYPE3_i :: COMPARE_BYTE [07:00] */
#define BCHP_XPT_WAKEUP_PKT_TYPE3_i_COMPARE_BYTE_MASK              0x000000ff
#define BCHP_XPT_WAKEUP_PKT_TYPE3_i_COMPARE_BYTE_SHIFT             0


#endif /* #ifndef BCHP_XPT_WAKEUP_H__ */

/* End of File */

/***************************************************************************
 *     Copyright (c) 1999-2011, Broadcom Corporation
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
 * Date:           Generated on         Mon Sep 19 21:47:01 2011
 *                 MD5 Checksum         e020a976c1177b900eff0f3d00f22e40
 *
 * Compiled with:  RDB Utility          combo_header.pl
 *                 RDB Parser           3.0
 *                 unknown              unknown
 *                 Perl Interpreter     5.008008
 *                 Operating System     linux
 *
 * Revision History:
 *
 * $brcm_Log: $
 * 
 ***************************************************************************/

#ifndef BCHP_MEM_DMA_0_H__
#define BCHP_MEM_DMA_0_H__

/***************************************************************************
 *MEM_DMA_0 - MEM_DMA_0 Registers
 ***************************************************************************/
#define BCHP_MEM_DMA_0_REVISION                  0x00360200 /* MEM_DMA REVISION */
#define BCHP_MEM_DMA_0_FIRST_DESC                0x00360204 /* MEM_DMA First Descriptor Address Register */
#define BCHP_MEM_DMA_0_CTRL                      0x00360208 /* MEM_DMA Control Register */
#define BCHP_MEM_DMA_0_WAKE_CTRL                 0x0036020c /* MEM_DMA Wake Control Register */
#define BCHP_MEM_DMA_0_STATUS                    0x00360214 /* MEM_DMA Status Register */
#define BCHP_MEM_DMA_0_CUR_DESC                  0x00360218 /* MEM_DMA Current Descriptor Address Register */
#define BCHP_MEM_DMA_0_CUR_BYTE                  0x0036021c /* MEM_DMA Current Byte Count Register */
#define BCHP_MEM_DMA_0_SCRATCH                   0x00360224 /* MEM_DMA Scratch Register */

/***************************************************************************
 *REVISION - MEM_DMA REVISION
 ***************************************************************************/
/* MEM_DMA_0 :: REVISION :: reserved0 [31:16] */
#define BCHP_MEM_DMA_0_REVISION_reserved0_MASK                     0xffff0000
#define BCHP_MEM_DMA_0_REVISION_reserved0_SHIFT                    16

/* MEM_DMA_0 :: REVISION :: MAJOR [15:08] */
#define BCHP_MEM_DMA_0_REVISION_MAJOR_MASK                         0x0000ff00
#define BCHP_MEM_DMA_0_REVISION_MAJOR_SHIFT                        8
#define BCHP_MEM_DMA_0_REVISION_MAJOR_DEFAULT                      2

/* MEM_DMA_0 :: REVISION :: MINOR [07:00] */
#define BCHP_MEM_DMA_0_REVISION_MINOR_MASK                         0x000000ff
#define BCHP_MEM_DMA_0_REVISION_MINOR_SHIFT                        0
#define BCHP_MEM_DMA_0_REVISION_MINOR_DEFAULT                      10

/***************************************************************************
 *FIRST_DESC - MEM_DMA First Descriptor Address Register
 ***************************************************************************/
/* MEM_DMA_0 :: FIRST_DESC :: ADDR [31:00] */
#define BCHP_MEM_DMA_0_FIRST_DESC_ADDR_MASK                        0xffffffff
#define BCHP_MEM_DMA_0_FIRST_DESC_ADDR_SHIFT                       0
#define BCHP_MEM_DMA_0_FIRST_DESC_ADDR_DEFAULT                     0

/***************************************************************************
 *CTRL - MEM_DMA Control Register
 ***************************************************************************/
/* MEM_DMA_0 :: CTRL :: reserved0 [31:01] */
#define BCHP_MEM_DMA_0_CTRL_reserved0_MASK                         0xfffffffe
#define BCHP_MEM_DMA_0_CTRL_reserved0_SHIFT                        1

/* MEM_DMA_0 :: CTRL :: RUN [00:00] */
#define BCHP_MEM_DMA_0_CTRL_RUN_MASK                               0x00000001
#define BCHP_MEM_DMA_0_CTRL_RUN_SHIFT                              0
#define BCHP_MEM_DMA_0_CTRL_RUN_DEFAULT                            0

/***************************************************************************
 *WAKE_CTRL - MEM_DMA Wake Control Register
 ***************************************************************************/
/* MEM_DMA_0 :: WAKE_CTRL :: reserved0 [31:02] */
#define BCHP_MEM_DMA_0_WAKE_CTRL_reserved0_MASK                    0xfffffffc
#define BCHP_MEM_DMA_0_WAKE_CTRL_reserved0_SHIFT                   2

/* MEM_DMA_0 :: WAKE_CTRL :: WAKE_MODE [01:01] */
#define BCHP_MEM_DMA_0_WAKE_CTRL_WAKE_MODE_MASK                    0x00000002
#define BCHP_MEM_DMA_0_WAKE_CTRL_WAKE_MODE_SHIFT                   1
#define BCHP_MEM_DMA_0_WAKE_CTRL_WAKE_MODE_DEFAULT                 0

/* MEM_DMA_0 :: WAKE_CTRL :: WAKE [00:00] */
#define BCHP_MEM_DMA_0_WAKE_CTRL_WAKE_MASK                         0x00000001
#define BCHP_MEM_DMA_0_WAKE_CTRL_WAKE_SHIFT                        0
#define BCHP_MEM_DMA_0_WAKE_CTRL_WAKE_DEFAULT                      0

/***************************************************************************
 *STATUS - MEM_DMA Status Register
 ***************************************************************************/
/* MEM_DMA_0 :: STATUS :: reserved0 [31:02] */
#define BCHP_MEM_DMA_0_STATUS_reserved0_MASK                       0xfffffffc
#define BCHP_MEM_DMA_0_STATUS_reserved0_SHIFT                      2

/* MEM_DMA_0 :: STATUS :: DMA_STATUS [01:00] */
#define BCHP_MEM_DMA_0_STATUS_DMA_STATUS_MASK                      0x00000003
#define BCHP_MEM_DMA_0_STATUS_DMA_STATUS_SHIFT                     0
#define BCHP_MEM_DMA_0_STATUS_DMA_STATUS_DEFAULT                   0
#define BCHP_MEM_DMA_0_STATUS_DMA_STATUS_Idle                      0
#define BCHP_MEM_DMA_0_STATUS_DMA_STATUS_Busy                      1
#define BCHP_MEM_DMA_0_STATUS_DMA_STATUS_Sleep                     2
#define BCHP_MEM_DMA_0_STATUS_DMA_STATUS_Reserved                  3

/***************************************************************************
 *CUR_DESC - MEM_DMA Current Descriptor Address Register
 ***************************************************************************/
/* MEM_DMA_0 :: CUR_DESC :: ADDR [31:00] */
#define BCHP_MEM_DMA_0_CUR_DESC_ADDR_MASK                          0xffffffff
#define BCHP_MEM_DMA_0_CUR_DESC_ADDR_SHIFT                         0
#define BCHP_MEM_DMA_0_CUR_DESC_ADDR_DEFAULT                       0

/***************************************************************************
 *CUR_BYTE - MEM_DMA Current Byte Count Register
 ***************************************************************************/
/* MEM_DMA_0 :: CUR_BYTE :: reserved0 [31:25] */
#define BCHP_MEM_DMA_0_CUR_BYTE_reserved0_MASK                     0xfe000000
#define BCHP_MEM_DMA_0_CUR_BYTE_reserved0_SHIFT                    25

/* MEM_DMA_0 :: CUR_BYTE :: COUNT [24:00] */
#define BCHP_MEM_DMA_0_CUR_BYTE_COUNT_MASK                         0x01ffffff
#define BCHP_MEM_DMA_0_CUR_BYTE_COUNT_SHIFT                        0
#define BCHP_MEM_DMA_0_CUR_BYTE_COUNT_DEFAULT                      0

/***************************************************************************
 *SCRATCH - MEM_DMA Scratch Register
 ***************************************************************************/
/* MEM_DMA_0 :: SCRATCH :: SCRATCH_BIT [31:00] */
#define BCHP_MEM_DMA_0_SCRATCH_SCRATCH_BIT_MASK                    0xffffffff
#define BCHP_MEM_DMA_0_SCRATCH_SCRATCH_BIT_SHIFT                   0
#define BCHP_MEM_DMA_0_SCRATCH_SCRATCH_BIT_DEFAULT                 0

#endif /* #ifndef BCHP_MEM_DMA_0_H__ */

/* End of File */

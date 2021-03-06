/****************************************************************************
 *     Copyright (c) 1999-2015, Broadcom Corporation
 *     All Rights Reserved
 *     Confidential Property of Broadcom Corporation
 *
 *
 * THIS SOFTWARE MAY ONLY BE USED SUBJECT TO AN EXECUTED SOFTWARE LICENSE
 * AGREEMENT  BETWEEN THE USER AND BROADCOM.  YOU HAVE NO RIGHT TO USE OR
 * EXPLOIT THIS MATERIAL EXCEPT SUBJECT TO THE TERMS OF SUCH AN AGREEMENT.
 *
 * Module Description:
 *                     DO NOT EDIT THIS FILE DIRECTLY
 *
 * This module was generated magically with RDB from a source description
 * file. You must edit the source file for changes to be made to this file.
 *
 *
 * Date:           Generated on               Tue Mar 10 21:58:49 2015
 *                 Full Compile MD5 Checksum  5e1590010d5c1b57e50bc6f4261c6964
 *                     (minus title and desc)
 *                 MD5 Checksum               48022a5123f15fb90760ff6d5877a474
 *
 * Compiled with:  RDB Utility                combo_header.pl
 *                 RDB.pm                     15839
 *                 unknown                    unknown
 *                 Perl Interpreter           5.008008
 *                 Operating System           linux
 *
 *
 ***************************************************************************/

#ifndef BCHP_BSP_CONTROL_INTR2_H__
#define BCHP_BSP_CONTROL_INTR2_H__

/***************************************************************************
 *BSP_CONTROL_INTR2 - BSP to HOST L2 interrupt control registers
 ***************************************************************************/
#define BCHP_BSP_CONTROL_INTR2_CPU_STATUS        0x0032b800 /* [RO] CPU interrupt Status Register */
#define BCHP_BSP_CONTROL_INTR2_CPU_SET           0x0032b804 /* [WO] CPU interrupt Set Register */
#define BCHP_BSP_CONTROL_INTR2_CPU_CLEAR         0x0032b808 /* [WO] CPU interrupt Clear Register */
#define BCHP_BSP_CONTROL_INTR2_CPU_MASK_STATUS   0x0032b80c /* [RO] CPU interrupt Mask Status Register */
#define BCHP_BSP_CONTROL_INTR2_CPU_MASK_SET      0x0032b810 /* [WO] CPU interrupt Mask Set Register */
#define BCHP_BSP_CONTROL_INTR2_CPU_MASK_CLEAR    0x0032b814 /* [WO] CPU interrupt Mask Clear Register */
#define BCHP_BSP_CONTROL_INTR2_PCI_STATUS        0x0032b818 /* [RO] PCI interrupt Status Register */
#define BCHP_BSP_CONTROL_INTR2_PCI_SET           0x0032b81c /* [WO] PCI interrupt Set Register */
#define BCHP_BSP_CONTROL_INTR2_PCI_CLEAR         0x0032b820 /* [WO] PCI interrupt Clear Register */
#define BCHP_BSP_CONTROL_INTR2_PCI_MASK_STATUS   0x0032b824 /* [RO] PCI interrupt Mask Status Register */
#define BCHP_BSP_CONTROL_INTR2_PCI_MASK_SET      0x0032b828 /* [WO] PCI interrupt Mask Set Register */
#define BCHP_BSP_CONTROL_INTR2_PCI_MASK_CLEAR    0x0032b82c /* [WO] PCI interrupt Mask Clear Register */

/***************************************************************************
 *CPU_STATUS - CPU interrupt Status Register
 ***************************************************************************/
/* BSP_CONTROL_INTR2 :: CPU_STATUS :: reserved0 [31:08] */
#define BCHP_BSP_CONTROL_INTR2_CPU_STATUS_reserved0_MASK           0xffffff00
#define BCHP_BSP_CONTROL_INTR2_CPU_STATUS_reserved0_SHIFT          8

/* BSP_CONTROL_INTR2 :: CPU_STATUS :: SECTOP_GR_ERROR_INTR [07:07] */
#define BCHP_BSP_CONTROL_INTR2_CPU_STATUS_SECTOP_GR_ERROR_INTR_MASK 0x00000080
#define BCHP_BSP_CONTROL_INTR2_CPU_STATUS_SECTOP_GR_ERROR_INTR_SHIFT 7
#define BCHP_BSP_CONTROL_INTR2_CPU_STATUS_SECTOP_GR_ERROR_INTR_DEFAULT 0x00000000

/* BSP_CONTROL_INTR2 :: CPU_STATUS :: MEM_DMA_0_INTR [06:06] */
#define BCHP_BSP_CONTROL_INTR2_CPU_STATUS_MEM_DMA_0_INTR_MASK      0x00000040
#define BCHP_BSP_CONTROL_INTR2_CPU_STATUS_MEM_DMA_0_INTR_SHIFT     6
#define BCHP_BSP_CONTROL_INTR2_CPU_STATUS_MEM_DMA_0_INTR_DEFAULT   0x00000000

/* BSP_CONTROL_INTR2 :: CPU_STATUS :: PKL_INTR [05:05] */
#define BCHP_BSP_CONTROL_INTR2_CPU_STATUS_PKL_INTR_MASK            0x00000020
#define BCHP_BSP_CONTROL_INTR2_CPU_STATUS_PKL_INTR_SHIFT           5
#define BCHP_BSP_CONTROL_INTR2_CPU_STATUS_PKL_INTR_DEFAULT         0x00000000

/* BSP_CONTROL_INTR2 :: CPU_STATUS :: BSP_TO_HOST_INTR [04:04] */
#define BCHP_BSP_CONTROL_INTR2_CPU_STATUS_BSP_TO_HOST_INTR_MASK    0x00000010
#define BCHP_BSP_CONTROL_INTR2_CPU_STATUS_BSP_TO_HOST_INTR_SHIFT   4
#define BCHP_BSP_CONTROL_INTR2_CPU_STATUS_BSP_TO_HOST_INTR_DEFAULT 0x00000000

/* BSP_CONTROL_INTR2 :: CPU_STATUS :: NSK_INTR [03:03] */
#define BCHP_BSP_CONTROL_INTR2_CPU_STATUS_NSK_INTR_MASK            0x00000008
#define BCHP_BSP_CONTROL_INTR2_CPU_STATUS_NSK_INTR_SHIFT           3
#define BCHP_BSP_CONTROL_INTR2_CPU_STATUS_NSK_INTR_DEFAULT         0x00000000

/* BSP_CONTROL_INTR2 :: CPU_STATUS :: OCMDQUE_CR_INTR [02:02] */
#define BCHP_BSP_CONTROL_INTR2_CPU_STATUS_OCMDQUE_CR_INTR_MASK     0x00000004
#define BCHP_BSP_CONTROL_INTR2_CPU_STATUS_OCMDQUE_CR_INTR_SHIFT    2
#define BCHP_BSP_CONTROL_INTR2_CPU_STATUS_OCMDQUE_CR_INTR_DEFAULT  0x00000000

/* BSP_CONTROL_INTR2 :: CPU_STATUS :: OCMDQUE2_INTR [01:01] */
#define BCHP_BSP_CONTROL_INTR2_CPU_STATUS_OCMDQUE2_INTR_MASK       0x00000002
#define BCHP_BSP_CONTROL_INTR2_CPU_STATUS_OCMDQUE2_INTR_SHIFT      1
#define BCHP_BSP_CONTROL_INTR2_CPU_STATUS_OCMDQUE2_INTR_DEFAULT    0x00000000

/* BSP_CONTROL_INTR2 :: CPU_STATUS :: OCMDQUE1_INTR [00:00] */
#define BCHP_BSP_CONTROL_INTR2_CPU_STATUS_OCMDQUE1_INTR_MASK       0x00000001
#define BCHP_BSP_CONTROL_INTR2_CPU_STATUS_OCMDQUE1_INTR_SHIFT      0
#define BCHP_BSP_CONTROL_INTR2_CPU_STATUS_OCMDQUE1_INTR_DEFAULT    0x00000000

/***************************************************************************
 *CPU_SET - CPU interrupt Set Register
 ***************************************************************************/
/* BSP_CONTROL_INTR2 :: CPU_SET :: reserved0 [31:08] */
#define BCHP_BSP_CONTROL_INTR2_CPU_SET_reserved0_MASK              0xffffff00
#define BCHP_BSP_CONTROL_INTR2_CPU_SET_reserved0_SHIFT             8

/* BSP_CONTROL_INTR2 :: CPU_SET :: SECTOP_GR_ERROR_INTR [07:07] */
#define BCHP_BSP_CONTROL_INTR2_CPU_SET_SECTOP_GR_ERROR_INTR_MASK   0x00000080
#define BCHP_BSP_CONTROL_INTR2_CPU_SET_SECTOP_GR_ERROR_INTR_SHIFT  7
#define BCHP_BSP_CONTROL_INTR2_CPU_SET_SECTOP_GR_ERROR_INTR_DEFAULT 0x00000000

/* BSP_CONTROL_INTR2 :: CPU_SET :: MEM_DMA_0_INTR [06:06] */
#define BCHP_BSP_CONTROL_INTR2_CPU_SET_MEM_DMA_0_INTR_MASK         0x00000040
#define BCHP_BSP_CONTROL_INTR2_CPU_SET_MEM_DMA_0_INTR_SHIFT        6
#define BCHP_BSP_CONTROL_INTR2_CPU_SET_MEM_DMA_0_INTR_DEFAULT      0x00000000

/* BSP_CONTROL_INTR2 :: CPU_SET :: PKL_INTR [05:05] */
#define BCHP_BSP_CONTROL_INTR2_CPU_SET_PKL_INTR_MASK               0x00000020
#define BCHP_BSP_CONTROL_INTR2_CPU_SET_PKL_INTR_SHIFT              5
#define BCHP_BSP_CONTROL_INTR2_CPU_SET_PKL_INTR_DEFAULT            0x00000000

/* BSP_CONTROL_INTR2 :: CPU_SET :: BSP_TO_HOST_INTR [04:04] */
#define BCHP_BSP_CONTROL_INTR2_CPU_SET_BSP_TO_HOST_INTR_MASK       0x00000010
#define BCHP_BSP_CONTROL_INTR2_CPU_SET_BSP_TO_HOST_INTR_SHIFT      4
#define BCHP_BSP_CONTROL_INTR2_CPU_SET_BSP_TO_HOST_INTR_DEFAULT    0x00000000

/* BSP_CONTROL_INTR2 :: CPU_SET :: NSK_INTR [03:03] */
#define BCHP_BSP_CONTROL_INTR2_CPU_SET_NSK_INTR_MASK               0x00000008
#define BCHP_BSP_CONTROL_INTR2_CPU_SET_NSK_INTR_SHIFT              3
#define BCHP_BSP_CONTROL_INTR2_CPU_SET_NSK_INTR_DEFAULT            0x00000000

/* BSP_CONTROL_INTR2 :: CPU_SET :: OCMDQUE_CR_INTR [02:02] */
#define BCHP_BSP_CONTROL_INTR2_CPU_SET_OCMDQUE_CR_INTR_MASK        0x00000004
#define BCHP_BSP_CONTROL_INTR2_CPU_SET_OCMDQUE_CR_INTR_SHIFT       2
#define BCHP_BSP_CONTROL_INTR2_CPU_SET_OCMDQUE_CR_INTR_DEFAULT     0x00000000

/* BSP_CONTROL_INTR2 :: CPU_SET :: OCMDQUE2_INTR [01:01] */
#define BCHP_BSP_CONTROL_INTR2_CPU_SET_OCMDQUE2_INTR_MASK          0x00000002
#define BCHP_BSP_CONTROL_INTR2_CPU_SET_OCMDQUE2_INTR_SHIFT         1
#define BCHP_BSP_CONTROL_INTR2_CPU_SET_OCMDQUE2_INTR_DEFAULT       0x00000000

/* BSP_CONTROL_INTR2 :: CPU_SET :: OCMDQUE1_INTR [00:00] */
#define BCHP_BSP_CONTROL_INTR2_CPU_SET_OCMDQUE1_INTR_MASK          0x00000001
#define BCHP_BSP_CONTROL_INTR2_CPU_SET_OCMDQUE1_INTR_SHIFT         0
#define BCHP_BSP_CONTROL_INTR2_CPU_SET_OCMDQUE1_INTR_DEFAULT       0x00000000

/***************************************************************************
 *CPU_CLEAR - CPU interrupt Clear Register
 ***************************************************************************/
/* BSP_CONTROL_INTR2 :: CPU_CLEAR :: reserved0 [31:08] */
#define BCHP_BSP_CONTROL_INTR2_CPU_CLEAR_reserved0_MASK            0xffffff00
#define BCHP_BSP_CONTROL_INTR2_CPU_CLEAR_reserved0_SHIFT           8

/* BSP_CONTROL_INTR2 :: CPU_CLEAR :: SECTOP_GR_ERROR_INTR [07:07] */
#define BCHP_BSP_CONTROL_INTR2_CPU_CLEAR_SECTOP_GR_ERROR_INTR_MASK 0x00000080
#define BCHP_BSP_CONTROL_INTR2_CPU_CLEAR_SECTOP_GR_ERROR_INTR_SHIFT 7
#define BCHP_BSP_CONTROL_INTR2_CPU_CLEAR_SECTOP_GR_ERROR_INTR_DEFAULT 0x00000000

/* BSP_CONTROL_INTR2 :: CPU_CLEAR :: MEM_DMA_0_INTR [06:06] */
#define BCHP_BSP_CONTROL_INTR2_CPU_CLEAR_MEM_DMA_0_INTR_MASK       0x00000040
#define BCHP_BSP_CONTROL_INTR2_CPU_CLEAR_MEM_DMA_0_INTR_SHIFT      6
#define BCHP_BSP_CONTROL_INTR2_CPU_CLEAR_MEM_DMA_0_INTR_DEFAULT    0x00000000

/* BSP_CONTROL_INTR2 :: CPU_CLEAR :: PKL_INTR [05:05] */
#define BCHP_BSP_CONTROL_INTR2_CPU_CLEAR_PKL_INTR_MASK             0x00000020
#define BCHP_BSP_CONTROL_INTR2_CPU_CLEAR_PKL_INTR_SHIFT            5
#define BCHP_BSP_CONTROL_INTR2_CPU_CLEAR_PKL_INTR_DEFAULT          0x00000000

/* BSP_CONTROL_INTR2 :: CPU_CLEAR :: BSP_TO_HOST_INTR [04:04] */
#define BCHP_BSP_CONTROL_INTR2_CPU_CLEAR_BSP_TO_HOST_INTR_MASK     0x00000010
#define BCHP_BSP_CONTROL_INTR2_CPU_CLEAR_BSP_TO_HOST_INTR_SHIFT    4
#define BCHP_BSP_CONTROL_INTR2_CPU_CLEAR_BSP_TO_HOST_INTR_DEFAULT  0x00000000

/* BSP_CONTROL_INTR2 :: CPU_CLEAR :: NSK_INTR [03:03] */
#define BCHP_BSP_CONTROL_INTR2_CPU_CLEAR_NSK_INTR_MASK             0x00000008
#define BCHP_BSP_CONTROL_INTR2_CPU_CLEAR_NSK_INTR_SHIFT            3
#define BCHP_BSP_CONTROL_INTR2_CPU_CLEAR_NSK_INTR_DEFAULT          0x00000000

/* BSP_CONTROL_INTR2 :: CPU_CLEAR :: OCMDQUE_CR_INTR [02:02] */
#define BCHP_BSP_CONTROL_INTR2_CPU_CLEAR_OCMDQUE_CR_INTR_MASK      0x00000004
#define BCHP_BSP_CONTROL_INTR2_CPU_CLEAR_OCMDQUE_CR_INTR_SHIFT     2
#define BCHP_BSP_CONTROL_INTR2_CPU_CLEAR_OCMDQUE_CR_INTR_DEFAULT   0x00000000

/* BSP_CONTROL_INTR2 :: CPU_CLEAR :: OCMDQUE2_INTR [01:01] */
#define BCHP_BSP_CONTROL_INTR2_CPU_CLEAR_OCMDQUE2_INTR_MASK        0x00000002
#define BCHP_BSP_CONTROL_INTR2_CPU_CLEAR_OCMDQUE2_INTR_SHIFT       1
#define BCHP_BSP_CONTROL_INTR2_CPU_CLEAR_OCMDQUE2_INTR_DEFAULT     0x00000000

/* BSP_CONTROL_INTR2 :: CPU_CLEAR :: OCMDQUE1_INTR [00:00] */
#define BCHP_BSP_CONTROL_INTR2_CPU_CLEAR_OCMDQUE1_INTR_MASK        0x00000001
#define BCHP_BSP_CONTROL_INTR2_CPU_CLEAR_OCMDQUE1_INTR_SHIFT       0
#define BCHP_BSP_CONTROL_INTR2_CPU_CLEAR_OCMDQUE1_INTR_DEFAULT     0x00000000

/***************************************************************************
 *CPU_MASK_STATUS - CPU interrupt Mask Status Register
 ***************************************************************************/
/* BSP_CONTROL_INTR2 :: CPU_MASK_STATUS :: reserved0 [31:08] */
#define BCHP_BSP_CONTROL_INTR2_CPU_MASK_STATUS_reserved0_MASK      0xffffff00
#define BCHP_BSP_CONTROL_INTR2_CPU_MASK_STATUS_reserved0_SHIFT     8

/* BSP_CONTROL_INTR2 :: CPU_MASK_STATUS :: SECTOP_GR_ERROR_INTR [07:07] */
#define BCHP_BSP_CONTROL_INTR2_CPU_MASK_STATUS_SECTOP_GR_ERROR_INTR_MASK 0x00000080
#define BCHP_BSP_CONTROL_INTR2_CPU_MASK_STATUS_SECTOP_GR_ERROR_INTR_SHIFT 7
#define BCHP_BSP_CONTROL_INTR2_CPU_MASK_STATUS_SECTOP_GR_ERROR_INTR_DEFAULT 0x00000001

/* BSP_CONTROL_INTR2 :: CPU_MASK_STATUS :: MEM_DMA_0_INTR [06:06] */
#define BCHP_BSP_CONTROL_INTR2_CPU_MASK_STATUS_MEM_DMA_0_INTR_MASK 0x00000040
#define BCHP_BSP_CONTROL_INTR2_CPU_MASK_STATUS_MEM_DMA_0_INTR_SHIFT 6
#define BCHP_BSP_CONTROL_INTR2_CPU_MASK_STATUS_MEM_DMA_0_INTR_DEFAULT 0x00000001

/* BSP_CONTROL_INTR2 :: CPU_MASK_STATUS :: PKL_INTR [05:05] */
#define BCHP_BSP_CONTROL_INTR2_CPU_MASK_STATUS_PKL_INTR_MASK       0x00000020
#define BCHP_BSP_CONTROL_INTR2_CPU_MASK_STATUS_PKL_INTR_SHIFT      5
#define BCHP_BSP_CONTROL_INTR2_CPU_MASK_STATUS_PKL_INTR_DEFAULT    0x00000001

/* BSP_CONTROL_INTR2 :: CPU_MASK_STATUS :: BSP_TO_HOST_INTR [04:04] */
#define BCHP_BSP_CONTROL_INTR2_CPU_MASK_STATUS_BSP_TO_HOST_INTR_MASK 0x00000010
#define BCHP_BSP_CONTROL_INTR2_CPU_MASK_STATUS_BSP_TO_HOST_INTR_SHIFT 4
#define BCHP_BSP_CONTROL_INTR2_CPU_MASK_STATUS_BSP_TO_HOST_INTR_DEFAULT 0x00000001

/* BSP_CONTROL_INTR2 :: CPU_MASK_STATUS :: NSK_INTR [03:03] */
#define BCHP_BSP_CONTROL_INTR2_CPU_MASK_STATUS_NSK_INTR_MASK       0x00000008
#define BCHP_BSP_CONTROL_INTR2_CPU_MASK_STATUS_NSK_INTR_SHIFT      3
#define BCHP_BSP_CONTROL_INTR2_CPU_MASK_STATUS_NSK_INTR_DEFAULT    0x00000001

/* BSP_CONTROL_INTR2 :: CPU_MASK_STATUS :: OCMDQUE_CR_INTR [02:02] */
#define BCHP_BSP_CONTROL_INTR2_CPU_MASK_STATUS_OCMDQUE_CR_INTR_MASK 0x00000004
#define BCHP_BSP_CONTROL_INTR2_CPU_MASK_STATUS_OCMDQUE_CR_INTR_SHIFT 2
#define BCHP_BSP_CONTROL_INTR2_CPU_MASK_STATUS_OCMDQUE_CR_INTR_DEFAULT 0x00000001

/* BSP_CONTROL_INTR2 :: CPU_MASK_STATUS :: OCMDQUE2_INTR [01:01] */
#define BCHP_BSP_CONTROL_INTR2_CPU_MASK_STATUS_OCMDQUE2_INTR_MASK  0x00000002
#define BCHP_BSP_CONTROL_INTR2_CPU_MASK_STATUS_OCMDQUE2_INTR_SHIFT 1
#define BCHP_BSP_CONTROL_INTR2_CPU_MASK_STATUS_OCMDQUE2_INTR_DEFAULT 0x00000001

/* BSP_CONTROL_INTR2 :: CPU_MASK_STATUS :: OCMDQUE1_INTR [00:00] */
#define BCHP_BSP_CONTROL_INTR2_CPU_MASK_STATUS_OCMDQUE1_INTR_MASK  0x00000001
#define BCHP_BSP_CONTROL_INTR2_CPU_MASK_STATUS_OCMDQUE1_INTR_SHIFT 0
#define BCHP_BSP_CONTROL_INTR2_CPU_MASK_STATUS_OCMDQUE1_INTR_DEFAULT 0x00000001

/***************************************************************************
 *CPU_MASK_SET - CPU interrupt Mask Set Register
 ***************************************************************************/
/* BSP_CONTROL_INTR2 :: CPU_MASK_SET :: reserved0 [31:08] */
#define BCHP_BSP_CONTROL_INTR2_CPU_MASK_SET_reserved0_MASK         0xffffff00
#define BCHP_BSP_CONTROL_INTR2_CPU_MASK_SET_reserved0_SHIFT        8

/* BSP_CONTROL_INTR2 :: CPU_MASK_SET :: SECTOP_GR_ERROR_INTR [07:07] */
#define BCHP_BSP_CONTROL_INTR2_CPU_MASK_SET_SECTOP_GR_ERROR_INTR_MASK 0x00000080
#define BCHP_BSP_CONTROL_INTR2_CPU_MASK_SET_SECTOP_GR_ERROR_INTR_SHIFT 7
#define BCHP_BSP_CONTROL_INTR2_CPU_MASK_SET_SECTOP_GR_ERROR_INTR_DEFAULT 0x00000001

/* BSP_CONTROL_INTR2 :: CPU_MASK_SET :: MEM_DMA_0_INTR [06:06] */
#define BCHP_BSP_CONTROL_INTR2_CPU_MASK_SET_MEM_DMA_0_INTR_MASK    0x00000040
#define BCHP_BSP_CONTROL_INTR2_CPU_MASK_SET_MEM_DMA_0_INTR_SHIFT   6
#define BCHP_BSP_CONTROL_INTR2_CPU_MASK_SET_MEM_DMA_0_INTR_DEFAULT 0x00000001

/* BSP_CONTROL_INTR2 :: CPU_MASK_SET :: PKL_INTR [05:05] */
#define BCHP_BSP_CONTROL_INTR2_CPU_MASK_SET_PKL_INTR_MASK          0x00000020
#define BCHP_BSP_CONTROL_INTR2_CPU_MASK_SET_PKL_INTR_SHIFT         5
#define BCHP_BSP_CONTROL_INTR2_CPU_MASK_SET_PKL_INTR_DEFAULT       0x00000001

/* BSP_CONTROL_INTR2 :: CPU_MASK_SET :: BSP_TO_HOST_INTR [04:04] */
#define BCHP_BSP_CONTROL_INTR2_CPU_MASK_SET_BSP_TO_HOST_INTR_MASK  0x00000010
#define BCHP_BSP_CONTROL_INTR2_CPU_MASK_SET_BSP_TO_HOST_INTR_SHIFT 4
#define BCHP_BSP_CONTROL_INTR2_CPU_MASK_SET_BSP_TO_HOST_INTR_DEFAULT 0x00000001

/* BSP_CONTROL_INTR2 :: CPU_MASK_SET :: NSK_INTR [03:03] */
#define BCHP_BSP_CONTROL_INTR2_CPU_MASK_SET_NSK_INTR_MASK          0x00000008
#define BCHP_BSP_CONTROL_INTR2_CPU_MASK_SET_NSK_INTR_SHIFT         3
#define BCHP_BSP_CONTROL_INTR2_CPU_MASK_SET_NSK_INTR_DEFAULT       0x00000001

/* BSP_CONTROL_INTR2 :: CPU_MASK_SET :: OCMDQUE_CR_INTR [02:02] */
#define BCHP_BSP_CONTROL_INTR2_CPU_MASK_SET_OCMDQUE_CR_INTR_MASK   0x00000004
#define BCHP_BSP_CONTROL_INTR2_CPU_MASK_SET_OCMDQUE_CR_INTR_SHIFT  2
#define BCHP_BSP_CONTROL_INTR2_CPU_MASK_SET_OCMDQUE_CR_INTR_DEFAULT 0x00000001

/* BSP_CONTROL_INTR2 :: CPU_MASK_SET :: OCMDQUE2_INTR [01:01] */
#define BCHP_BSP_CONTROL_INTR2_CPU_MASK_SET_OCMDQUE2_INTR_MASK     0x00000002
#define BCHP_BSP_CONTROL_INTR2_CPU_MASK_SET_OCMDQUE2_INTR_SHIFT    1
#define BCHP_BSP_CONTROL_INTR2_CPU_MASK_SET_OCMDQUE2_INTR_DEFAULT  0x00000001

/* BSP_CONTROL_INTR2 :: CPU_MASK_SET :: OCMDQUE1_INTR [00:00] */
#define BCHP_BSP_CONTROL_INTR2_CPU_MASK_SET_OCMDQUE1_INTR_MASK     0x00000001
#define BCHP_BSP_CONTROL_INTR2_CPU_MASK_SET_OCMDQUE1_INTR_SHIFT    0
#define BCHP_BSP_CONTROL_INTR2_CPU_MASK_SET_OCMDQUE1_INTR_DEFAULT  0x00000001

/***************************************************************************
 *CPU_MASK_CLEAR - CPU interrupt Mask Clear Register
 ***************************************************************************/
/* BSP_CONTROL_INTR2 :: CPU_MASK_CLEAR :: reserved0 [31:08] */
#define BCHP_BSP_CONTROL_INTR2_CPU_MASK_CLEAR_reserved0_MASK       0xffffff00
#define BCHP_BSP_CONTROL_INTR2_CPU_MASK_CLEAR_reserved0_SHIFT      8

/* BSP_CONTROL_INTR2 :: CPU_MASK_CLEAR :: SECTOP_GR_ERROR_INTR [07:07] */
#define BCHP_BSP_CONTROL_INTR2_CPU_MASK_CLEAR_SECTOP_GR_ERROR_INTR_MASK 0x00000080
#define BCHP_BSP_CONTROL_INTR2_CPU_MASK_CLEAR_SECTOP_GR_ERROR_INTR_SHIFT 7
#define BCHP_BSP_CONTROL_INTR2_CPU_MASK_CLEAR_SECTOP_GR_ERROR_INTR_DEFAULT 0x00000001

/* BSP_CONTROL_INTR2 :: CPU_MASK_CLEAR :: MEM_DMA_0_INTR [06:06] */
#define BCHP_BSP_CONTROL_INTR2_CPU_MASK_CLEAR_MEM_DMA_0_INTR_MASK  0x00000040
#define BCHP_BSP_CONTROL_INTR2_CPU_MASK_CLEAR_MEM_DMA_0_INTR_SHIFT 6
#define BCHP_BSP_CONTROL_INTR2_CPU_MASK_CLEAR_MEM_DMA_0_INTR_DEFAULT 0x00000001

/* BSP_CONTROL_INTR2 :: CPU_MASK_CLEAR :: PKL_INTR [05:05] */
#define BCHP_BSP_CONTROL_INTR2_CPU_MASK_CLEAR_PKL_INTR_MASK        0x00000020
#define BCHP_BSP_CONTROL_INTR2_CPU_MASK_CLEAR_PKL_INTR_SHIFT       5
#define BCHP_BSP_CONTROL_INTR2_CPU_MASK_CLEAR_PKL_INTR_DEFAULT     0x00000001

/* BSP_CONTROL_INTR2 :: CPU_MASK_CLEAR :: BSP_TO_HOST_INTR [04:04] */
#define BCHP_BSP_CONTROL_INTR2_CPU_MASK_CLEAR_BSP_TO_HOST_INTR_MASK 0x00000010
#define BCHP_BSP_CONTROL_INTR2_CPU_MASK_CLEAR_BSP_TO_HOST_INTR_SHIFT 4
#define BCHP_BSP_CONTROL_INTR2_CPU_MASK_CLEAR_BSP_TO_HOST_INTR_DEFAULT 0x00000001

/* BSP_CONTROL_INTR2 :: CPU_MASK_CLEAR :: NSK_INTR [03:03] */
#define BCHP_BSP_CONTROL_INTR2_CPU_MASK_CLEAR_NSK_INTR_MASK        0x00000008
#define BCHP_BSP_CONTROL_INTR2_CPU_MASK_CLEAR_NSK_INTR_SHIFT       3
#define BCHP_BSP_CONTROL_INTR2_CPU_MASK_CLEAR_NSK_INTR_DEFAULT     0x00000001

/* BSP_CONTROL_INTR2 :: CPU_MASK_CLEAR :: OCMDQUE_CR_INTR [02:02] */
#define BCHP_BSP_CONTROL_INTR2_CPU_MASK_CLEAR_OCMDQUE_CR_INTR_MASK 0x00000004
#define BCHP_BSP_CONTROL_INTR2_CPU_MASK_CLEAR_OCMDQUE_CR_INTR_SHIFT 2
#define BCHP_BSP_CONTROL_INTR2_CPU_MASK_CLEAR_OCMDQUE_CR_INTR_DEFAULT 0x00000001

/* BSP_CONTROL_INTR2 :: CPU_MASK_CLEAR :: OCMDQUE2_INTR [01:01] */
#define BCHP_BSP_CONTROL_INTR2_CPU_MASK_CLEAR_OCMDQUE2_INTR_MASK   0x00000002
#define BCHP_BSP_CONTROL_INTR2_CPU_MASK_CLEAR_OCMDQUE2_INTR_SHIFT  1
#define BCHP_BSP_CONTROL_INTR2_CPU_MASK_CLEAR_OCMDQUE2_INTR_DEFAULT 0x00000001

/* BSP_CONTROL_INTR2 :: CPU_MASK_CLEAR :: OCMDQUE1_INTR [00:00] */
#define BCHP_BSP_CONTROL_INTR2_CPU_MASK_CLEAR_OCMDQUE1_INTR_MASK   0x00000001
#define BCHP_BSP_CONTROL_INTR2_CPU_MASK_CLEAR_OCMDQUE1_INTR_SHIFT  0
#define BCHP_BSP_CONTROL_INTR2_CPU_MASK_CLEAR_OCMDQUE1_INTR_DEFAULT 0x00000001

/***************************************************************************
 *PCI_STATUS - PCI interrupt Status Register
 ***************************************************************************/
/* BSP_CONTROL_INTR2 :: PCI_STATUS :: reserved0 [31:08] */
#define BCHP_BSP_CONTROL_INTR2_PCI_STATUS_reserved0_MASK           0xffffff00
#define BCHP_BSP_CONTROL_INTR2_PCI_STATUS_reserved0_SHIFT          8

/* BSP_CONTROL_INTR2 :: PCI_STATUS :: SECTOP_GR_ERROR_INTR [07:07] */
#define BCHP_BSP_CONTROL_INTR2_PCI_STATUS_SECTOP_GR_ERROR_INTR_MASK 0x00000080
#define BCHP_BSP_CONTROL_INTR2_PCI_STATUS_SECTOP_GR_ERROR_INTR_SHIFT 7
#define BCHP_BSP_CONTROL_INTR2_PCI_STATUS_SECTOP_GR_ERROR_INTR_DEFAULT 0x00000000

/* BSP_CONTROL_INTR2 :: PCI_STATUS :: MEM_DMA_0_INTR [06:06] */
#define BCHP_BSP_CONTROL_INTR2_PCI_STATUS_MEM_DMA_0_INTR_MASK      0x00000040
#define BCHP_BSP_CONTROL_INTR2_PCI_STATUS_MEM_DMA_0_INTR_SHIFT     6
#define BCHP_BSP_CONTROL_INTR2_PCI_STATUS_MEM_DMA_0_INTR_DEFAULT   0x00000000

/* BSP_CONTROL_INTR2 :: PCI_STATUS :: PKL_INTR [05:05] */
#define BCHP_BSP_CONTROL_INTR2_PCI_STATUS_PKL_INTR_MASK            0x00000020
#define BCHP_BSP_CONTROL_INTR2_PCI_STATUS_PKL_INTR_SHIFT           5
#define BCHP_BSP_CONTROL_INTR2_PCI_STATUS_PKL_INTR_DEFAULT         0x00000000

/* BSP_CONTROL_INTR2 :: PCI_STATUS :: BSP_TO_HOST_INTR [04:04] */
#define BCHP_BSP_CONTROL_INTR2_PCI_STATUS_BSP_TO_HOST_INTR_MASK    0x00000010
#define BCHP_BSP_CONTROL_INTR2_PCI_STATUS_BSP_TO_HOST_INTR_SHIFT   4
#define BCHP_BSP_CONTROL_INTR2_PCI_STATUS_BSP_TO_HOST_INTR_DEFAULT 0x00000000

/* BSP_CONTROL_INTR2 :: PCI_STATUS :: NSK_INTR [03:03] */
#define BCHP_BSP_CONTROL_INTR2_PCI_STATUS_NSK_INTR_MASK            0x00000008
#define BCHP_BSP_CONTROL_INTR2_PCI_STATUS_NSK_INTR_SHIFT           3
#define BCHP_BSP_CONTROL_INTR2_PCI_STATUS_NSK_INTR_DEFAULT         0x00000000

/* BSP_CONTROL_INTR2 :: PCI_STATUS :: OCMDQUE_CR_INTR [02:02] */
#define BCHP_BSP_CONTROL_INTR2_PCI_STATUS_OCMDQUE_CR_INTR_MASK     0x00000004
#define BCHP_BSP_CONTROL_INTR2_PCI_STATUS_OCMDQUE_CR_INTR_SHIFT    2
#define BCHP_BSP_CONTROL_INTR2_PCI_STATUS_OCMDQUE_CR_INTR_DEFAULT  0x00000000

/* BSP_CONTROL_INTR2 :: PCI_STATUS :: OCMDQUE2_INTR [01:01] */
#define BCHP_BSP_CONTROL_INTR2_PCI_STATUS_OCMDQUE2_INTR_MASK       0x00000002
#define BCHP_BSP_CONTROL_INTR2_PCI_STATUS_OCMDQUE2_INTR_SHIFT      1
#define BCHP_BSP_CONTROL_INTR2_PCI_STATUS_OCMDQUE2_INTR_DEFAULT    0x00000000

/* BSP_CONTROL_INTR2 :: PCI_STATUS :: OCMDQUE1_INTR [00:00] */
#define BCHP_BSP_CONTROL_INTR2_PCI_STATUS_OCMDQUE1_INTR_MASK       0x00000001
#define BCHP_BSP_CONTROL_INTR2_PCI_STATUS_OCMDQUE1_INTR_SHIFT      0
#define BCHP_BSP_CONTROL_INTR2_PCI_STATUS_OCMDQUE1_INTR_DEFAULT    0x00000000

/***************************************************************************
 *PCI_SET - PCI interrupt Set Register
 ***************************************************************************/
/* BSP_CONTROL_INTR2 :: PCI_SET :: reserved0 [31:08] */
#define BCHP_BSP_CONTROL_INTR2_PCI_SET_reserved0_MASK              0xffffff00
#define BCHP_BSP_CONTROL_INTR2_PCI_SET_reserved0_SHIFT             8

/* BSP_CONTROL_INTR2 :: PCI_SET :: SECTOP_GR_ERROR_INTR [07:07] */
#define BCHP_BSP_CONTROL_INTR2_PCI_SET_SECTOP_GR_ERROR_INTR_MASK   0x00000080
#define BCHP_BSP_CONTROL_INTR2_PCI_SET_SECTOP_GR_ERROR_INTR_SHIFT  7
#define BCHP_BSP_CONTROL_INTR2_PCI_SET_SECTOP_GR_ERROR_INTR_DEFAULT 0x00000000

/* BSP_CONTROL_INTR2 :: PCI_SET :: MEM_DMA_0_INTR [06:06] */
#define BCHP_BSP_CONTROL_INTR2_PCI_SET_MEM_DMA_0_INTR_MASK         0x00000040
#define BCHP_BSP_CONTROL_INTR2_PCI_SET_MEM_DMA_0_INTR_SHIFT        6
#define BCHP_BSP_CONTROL_INTR2_PCI_SET_MEM_DMA_0_INTR_DEFAULT      0x00000000

/* BSP_CONTROL_INTR2 :: PCI_SET :: PKL_INTR [05:05] */
#define BCHP_BSP_CONTROL_INTR2_PCI_SET_PKL_INTR_MASK               0x00000020
#define BCHP_BSP_CONTROL_INTR2_PCI_SET_PKL_INTR_SHIFT              5
#define BCHP_BSP_CONTROL_INTR2_PCI_SET_PKL_INTR_DEFAULT            0x00000000

/* BSP_CONTROL_INTR2 :: PCI_SET :: BSP_TO_HOST_INTR [04:04] */
#define BCHP_BSP_CONTROL_INTR2_PCI_SET_BSP_TO_HOST_INTR_MASK       0x00000010
#define BCHP_BSP_CONTROL_INTR2_PCI_SET_BSP_TO_HOST_INTR_SHIFT      4
#define BCHP_BSP_CONTROL_INTR2_PCI_SET_BSP_TO_HOST_INTR_DEFAULT    0x00000000

/* BSP_CONTROL_INTR2 :: PCI_SET :: NSK_INTR [03:03] */
#define BCHP_BSP_CONTROL_INTR2_PCI_SET_NSK_INTR_MASK               0x00000008
#define BCHP_BSP_CONTROL_INTR2_PCI_SET_NSK_INTR_SHIFT              3
#define BCHP_BSP_CONTROL_INTR2_PCI_SET_NSK_INTR_DEFAULT            0x00000000

/* BSP_CONTROL_INTR2 :: PCI_SET :: OCMDQUE_CR_INTR [02:02] */
#define BCHP_BSP_CONTROL_INTR2_PCI_SET_OCMDQUE_CR_INTR_MASK        0x00000004
#define BCHP_BSP_CONTROL_INTR2_PCI_SET_OCMDQUE_CR_INTR_SHIFT       2
#define BCHP_BSP_CONTROL_INTR2_PCI_SET_OCMDQUE_CR_INTR_DEFAULT     0x00000000

/* BSP_CONTROL_INTR2 :: PCI_SET :: OCMDQUE2_INTR [01:01] */
#define BCHP_BSP_CONTROL_INTR2_PCI_SET_OCMDQUE2_INTR_MASK          0x00000002
#define BCHP_BSP_CONTROL_INTR2_PCI_SET_OCMDQUE2_INTR_SHIFT         1
#define BCHP_BSP_CONTROL_INTR2_PCI_SET_OCMDQUE2_INTR_DEFAULT       0x00000000

/* BSP_CONTROL_INTR2 :: PCI_SET :: OCMDQUE1_INTR [00:00] */
#define BCHP_BSP_CONTROL_INTR2_PCI_SET_OCMDQUE1_INTR_MASK          0x00000001
#define BCHP_BSP_CONTROL_INTR2_PCI_SET_OCMDQUE1_INTR_SHIFT         0
#define BCHP_BSP_CONTROL_INTR2_PCI_SET_OCMDQUE1_INTR_DEFAULT       0x00000000

/***************************************************************************
 *PCI_CLEAR - PCI interrupt Clear Register
 ***************************************************************************/
/* BSP_CONTROL_INTR2 :: PCI_CLEAR :: reserved0 [31:08] */
#define BCHP_BSP_CONTROL_INTR2_PCI_CLEAR_reserved0_MASK            0xffffff00
#define BCHP_BSP_CONTROL_INTR2_PCI_CLEAR_reserved0_SHIFT           8

/* BSP_CONTROL_INTR2 :: PCI_CLEAR :: SECTOP_GR_ERROR_INTR [07:07] */
#define BCHP_BSP_CONTROL_INTR2_PCI_CLEAR_SECTOP_GR_ERROR_INTR_MASK 0x00000080
#define BCHP_BSP_CONTROL_INTR2_PCI_CLEAR_SECTOP_GR_ERROR_INTR_SHIFT 7
#define BCHP_BSP_CONTROL_INTR2_PCI_CLEAR_SECTOP_GR_ERROR_INTR_DEFAULT 0x00000000

/* BSP_CONTROL_INTR2 :: PCI_CLEAR :: MEM_DMA_0_INTR [06:06] */
#define BCHP_BSP_CONTROL_INTR2_PCI_CLEAR_MEM_DMA_0_INTR_MASK       0x00000040
#define BCHP_BSP_CONTROL_INTR2_PCI_CLEAR_MEM_DMA_0_INTR_SHIFT      6
#define BCHP_BSP_CONTROL_INTR2_PCI_CLEAR_MEM_DMA_0_INTR_DEFAULT    0x00000000

/* BSP_CONTROL_INTR2 :: PCI_CLEAR :: PKL_INTR [05:05] */
#define BCHP_BSP_CONTROL_INTR2_PCI_CLEAR_PKL_INTR_MASK             0x00000020
#define BCHP_BSP_CONTROL_INTR2_PCI_CLEAR_PKL_INTR_SHIFT            5
#define BCHP_BSP_CONTROL_INTR2_PCI_CLEAR_PKL_INTR_DEFAULT          0x00000000

/* BSP_CONTROL_INTR2 :: PCI_CLEAR :: BSP_TO_HOST_INTR [04:04] */
#define BCHP_BSP_CONTROL_INTR2_PCI_CLEAR_BSP_TO_HOST_INTR_MASK     0x00000010
#define BCHP_BSP_CONTROL_INTR2_PCI_CLEAR_BSP_TO_HOST_INTR_SHIFT    4
#define BCHP_BSP_CONTROL_INTR2_PCI_CLEAR_BSP_TO_HOST_INTR_DEFAULT  0x00000000

/* BSP_CONTROL_INTR2 :: PCI_CLEAR :: NSK_INTR [03:03] */
#define BCHP_BSP_CONTROL_INTR2_PCI_CLEAR_NSK_INTR_MASK             0x00000008
#define BCHP_BSP_CONTROL_INTR2_PCI_CLEAR_NSK_INTR_SHIFT            3
#define BCHP_BSP_CONTROL_INTR2_PCI_CLEAR_NSK_INTR_DEFAULT          0x00000000

/* BSP_CONTROL_INTR2 :: PCI_CLEAR :: OCMDQUE_CR_INTR [02:02] */
#define BCHP_BSP_CONTROL_INTR2_PCI_CLEAR_OCMDQUE_CR_INTR_MASK      0x00000004
#define BCHP_BSP_CONTROL_INTR2_PCI_CLEAR_OCMDQUE_CR_INTR_SHIFT     2
#define BCHP_BSP_CONTROL_INTR2_PCI_CLEAR_OCMDQUE_CR_INTR_DEFAULT   0x00000000

/* BSP_CONTROL_INTR2 :: PCI_CLEAR :: OCMDQUE2_INTR [01:01] */
#define BCHP_BSP_CONTROL_INTR2_PCI_CLEAR_OCMDQUE2_INTR_MASK        0x00000002
#define BCHP_BSP_CONTROL_INTR2_PCI_CLEAR_OCMDQUE2_INTR_SHIFT       1
#define BCHP_BSP_CONTROL_INTR2_PCI_CLEAR_OCMDQUE2_INTR_DEFAULT     0x00000000

/* BSP_CONTROL_INTR2 :: PCI_CLEAR :: OCMDQUE1_INTR [00:00] */
#define BCHP_BSP_CONTROL_INTR2_PCI_CLEAR_OCMDQUE1_INTR_MASK        0x00000001
#define BCHP_BSP_CONTROL_INTR2_PCI_CLEAR_OCMDQUE1_INTR_SHIFT       0
#define BCHP_BSP_CONTROL_INTR2_PCI_CLEAR_OCMDQUE1_INTR_DEFAULT     0x00000000

/***************************************************************************
 *PCI_MASK_STATUS - PCI interrupt Mask Status Register
 ***************************************************************************/
/* BSP_CONTROL_INTR2 :: PCI_MASK_STATUS :: reserved0 [31:08] */
#define BCHP_BSP_CONTROL_INTR2_PCI_MASK_STATUS_reserved0_MASK      0xffffff00
#define BCHP_BSP_CONTROL_INTR2_PCI_MASK_STATUS_reserved0_SHIFT     8

/* BSP_CONTROL_INTR2 :: PCI_MASK_STATUS :: SECTOP_GR_ERROR_INTR [07:07] */
#define BCHP_BSP_CONTROL_INTR2_PCI_MASK_STATUS_SECTOP_GR_ERROR_INTR_MASK 0x00000080
#define BCHP_BSP_CONTROL_INTR2_PCI_MASK_STATUS_SECTOP_GR_ERROR_INTR_SHIFT 7
#define BCHP_BSP_CONTROL_INTR2_PCI_MASK_STATUS_SECTOP_GR_ERROR_INTR_DEFAULT 0x00000001

/* BSP_CONTROL_INTR2 :: PCI_MASK_STATUS :: MEM_DMA_0_INTR [06:06] */
#define BCHP_BSP_CONTROL_INTR2_PCI_MASK_STATUS_MEM_DMA_0_INTR_MASK 0x00000040
#define BCHP_BSP_CONTROL_INTR2_PCI_MASK_STATUS_MEM_DMA_0_INTR_SHIFT 6
#define BCHP_BSP_CONTROL_INTR2_PCI_MASK_STATUS_MEM_DMA_0_INTR_DEFAULT 0x00000001

/* BSP_CONTROL_INTR2 :: PCI_MASK_STATUS :: PKL_INTR [05:05] */
#define BCHP_BSP_CONTROL_INTR2_PCI_MASK_STATUS_PKL_INTR_MASK       0x00000020
#define BCHP_BSP_CONTROL_INTR2_PCI_MASK_STATUS_PKL_INTR_SHIFT      5
#define BCHP_BSP_CONTROL_INTR2_PCI_MASK_STATUS_PKL_INTR_DEFAULT    0x00000001

/* BSP_CONTROL_INTR2 :: PCI_MASK_STATUS :: BSP_TO_HOST_INTR [04:04] */
#define BCHP_BSP_CONTROL_INTR2_PCI_MASK_STATUS_BSP_TO_HOST_INTR_MASK 0x00000010
#define BCHP_BSP_CONTROL_INTR2_PCI_MASK_STATUS_BSP_TO_HOST_INTR_SHIFT 4
#define BCHP_BSP_CONTROL_INTR2_PCI_MASK_STATUS_BSP_TO_HOST_INTR_DEFAULT 0x00000001

/* BSP_CONTROL_INTR2 :: PCI_MASK_STATUS :: NSK_INTR [03:03] */
#define BCHP_BSP_CONTROL_INTR2_PCI_MASK_STATUS_NSK_INTR_MASK       0x00000008
#define BCHP_BSP_CONTROL_INTR2_PCI_MASK_STATUS_NSK_INTR_SHIFT      3
#define BCHP_BSP_CONTROL_INTR2_PCI_MASK_STATUS_NSK_INTR_DEFAULT    0x00000001

/* BSP_CONTROL_INTR2 :: PCI_MASK_STATUS :: OCMDQUE_CR_INTR [02:02] */
#define BCHP_BSP_CONTROL_INTR2_PCI_MASK_STATUS_OCMDQUE_CR_INTR_MASK 0x00000004
#define BCHP_BSP_CONTROL_INTR2_PCI_MASK_STATUS_OCMDQUE_CR_INTR_SHIFT 2
#define BCHP_BSP_CONTROL_INTR2_PCI_MASK_STATUS_OCMDQUE_CR_INTR_DEFAULT 0x00000001

/* BSP_CONTROL_INTR2 :: PCI_MASK_STATUS :: OCMDQUE2_INTR [01:01] */
#define BCHP_BSP_CONTROL_INTR2_PCI_MASK_STATUS_OCMDQUE2_INTR_MASK  0x00000002
#define BCHP_BSP_CONTROL_INTR2_PCI_MASK_STATUS_OCMDQUE2_INTR_SHIFT 1
#define BCHP_BSP_CONTROL_INTR2_PCI_MASK_STATUS_OCMDQUE2_INTR_DEFAULT 0x00000001

/* BSP_CONTROL_INTR2 :: PCI_MASK_STATUS :: OCMDQUE1_INTR [00:00] */
#define BCHP_BSP_CONTROL_INTR2_PCI_MASK_STATUS_OCMDQUE1_INTR_MASK  0x00000001
#define BCHP_BSP_CONTROL_INTR2_PCI_MASK_STATUS_OCMDQUE1_INTR_SHIFT 0
#define BCHP_BSP_CONTROL_INTR2_PCI_MASK_STATUS_OCMDQUE1_INTR_DEFAULT 0x00000001

/***************************************************************************
 *PCI_MASK_SET - PCI interrupt Mask Set Register
 ***************************************************************************/
/* BSP_CONTROL_INTR2 :: PCI_MASK_SET :: reserved0 [31:08] */
#define BCHP_BSP_CONTROL_INTR2_PCI_MASK_SET_reserved0_MASK         0xffffff00
#define BCHP_BSP_CONTROL_INTR2_PCI_MASK_SET_reserved0_SHIFT        8

/* BSP_CONTROL_INTR2 :: PCI_MASK_SET :: SECTOP_GR_ERROR_INTR [07:07] */
#define BCHP_BSP_CONTROL_INTR2_PCI_MASK_SET_SECTOP_GR_ERROR_INTR_MASK 0x00000080
#define BCHP_BSP_CONTROL_INTR2_PCI_MASK_SET_SECTOP_GR_ERROR_INTR_SHIFT 7
#define BCHP_BSP_CONTROL_INTR2_PCI_MASK_SET_SECTOP_GR_ERROR_INTR_DEFAULT 0x00000001

/* BSP_CONTROL_INTR2 :: PCI_MASK_SET :: MEM_DMA_0_INTR [06:06] */
#define BCHP_BSP_CONTROL_INTR2_PCI_MASK_SET_MEM_DMA_0_INTR_MASK    0x00000040
#define BCHP_BSP_CONTROL_INTR2_PCI_MASK_SET_MEM_DMA_0_INTR_SHIFT   6
#define BCHP_BSP_CONTROL_INTR2_PCI_MASK_SET_MEM_DMA_0_INTR_DEFAULT 0x00000001

/* BSP_CONTROL_INTR2 :: PCI_MASK_SET :: PKL_INTR [05:05] */
#define BCHP_BSP_CONTROL_INTR2_PCI_MASK_SET_PKL_INTR_MASK          0x00000020
#define BCHP_BSP_CONTROL_INTR2_PCI_MASK_SET_PKL_INTR_SHIFT         5
#define BCHP_BSP_CONTROL_INTR2_PCI_MASK_SET_PKL_INTR_DEFAULT       0x00000001

/* BSP_CONTROL_INTR2 :: PCI_MASK_SET :: BSP_TO_HOST_INTR [04:04] */
#define BCHP_BSP_CONTROL_INTR2_PCI_MASK_SET_BSP_TO_HOST_INTR_MASK  0x00000010
#define BCHP_BSP_CONTROL_INTR2_PCI_MASK_SET_BSP_TO_HOST_INTR_SHIFT 4
#define BCHP_BSP_CONTROL_INTR2_PCI_MASK_SET_BSP_TO_HOST_INTR_DEFAULT 0x00000001

/* BSP_CONTROL_INTR2 :: PCI_MASK_SET :: NSK_INTR [03:03] */
#define BCHP_BSP_CONTROL_INTR2_PCI_MASK_SET_NSK_INTR_MASK          0x00000008
#define BCHP_BSP_CONTROL_INTR2_PCI_MASK_SET_NSK_INTR_SHIFT         3
#define BCHP_BSP_CONTROL_INTR2_PCI_MASK_SET_NSK_INTR_DEFAULT       0x00000001

/* BSP_CONTROL_INTR2 :: PCI_MASK_SET :: OCMDQUE_CR_INTR [02:02] */
#define BCHP_BSP_CONTROL_INTR2_PCI_MASK_SET_OCMDQUE_CR_INTR_MASK   0x00000004
#define BCHP_BSP_CONTROL_INTR2_PCI_MASK_SET_OCMDQUE_CR_INTR_SHIFT  2
#define BCHP_BSP_CONTROL_INTR2_PCI_MASK_SET_OCMDQUE_CR_INTR_DEFAULT 0x00000001

/* BSP_CONTROL_INTR2 :: PCI_MASK_SET :: OCMDQUE2_INTR [01:01] */
#define BCHP_BSP_CONTROL_INTR2_PCI_MASK_SET_OCMDQUE2_INTR_MASK     0x00000002
#define BCHP_BSP_CONTROL_INTR2_PCI_MASK_SET_OCMDQUE2_INTR_SHIFT    1
#define BCHP_BSP_CONTROL_INTR2_PCI_MASK_SET_OCMDQUE2_INTR_DEFAULT  0x00000001

/* BSP_CONTROL_INTR2 :: PCI_MASK_SET :: OCMDQUE1_INTR [00:00] */
#define BCHP_BSP_CONTROL_INTR2_PCI_MASK_SET_OCMDQUE1_INTR_MASK     0x00000001
#define BCHP_BSP_CONTROL_INTR2_PCI_MASK_SET_OCMDQUE1_INTR_SHIFT    0
#define BCHP_BSP_CONTROL_INTR2_PCI_MASK_SET_OCMDQUE1_INTR_DEFAULT  0x00000001

/***************************************************************************
 *PCI_MASK_CLEAR - PCI interrupt Mask Clear Register
 ***************************************************************************/
/* BSP_CONTROL_INTR2 :: PCI_MASK_CLEAR :: reserved0 [31:08] */
#define BCHP_BSP_CONTROL_INTR2_PCI_MASK_CLEAR_reserved0_MASK       0xffffff00
#define BCHP_BSP_CONTROL_INTR2_PCI_MASK_CLEAR_reserved0_SHIFT      8

/* BSP_CONTROL_INTR2 :: PCI_MASK_CLEAR :: SECTOP_GR_ERROR_INTR [07:07] */
#define BCHP_BSP_CONTROL_INTR2_PCI_MASK_CLEAR_SECTOP_GR_ERROR_INTR_MASK 0x00000080
#define BCHP_BSP_CONTROL_INTR2_PCI_MASK_CLEAR_SECTOP_GR_ERROR_INTR_SHIFT 7
#define BCHP_BSP_CONTROL_INTR2_PCI_MASK_CLEAR_SECTOP_GR_ERROR_INTR_DEFAULT 0x00000001

/* BSP_CONTROL_INTR2 :: PCI_MASK_CLEAR :: MEM_DMA_0_INTR [06:06] */
#define BCHP_BSP_CONTROL_INTR2_PCI_MASK_CLEAR_MEM_DMA_0_INTR_MASK  0x00000040
#define BCHP_BSP_CONTROL_INTR2_PCI_MASK_CLEAR_MEM_DMA_0_INTR_SHIFT 6
#define BCHP_BSP_CONTROL_INTR2_PCI_MASK_CLEAR_MEM_DMA_0_INTR_DEFAULT 0x00000001

/* BSP_CONTROL_INTR2 :: PCI_MASK_CLEAR :: PKL_INTR [05:05] */
#define BCHP_BSP_CONTROL_INTR2_PCI_MASK_CLEAR_PKL_INTR_MASK        0x00000020
#define BCHP_BSP_CONTROL_INTR2_PCI_MASK_CLEAR_PKL_INTR_SHIFT       5
#define BCHP_BSP_CONTROL_INTR2_PCI_MASK_CLEAR_PKL_INTR_DEFAULT     0x00000001

/* BSP_CONTROL_INTR2 :: PCI_MASK_CLEAR :: BSP_TO_HOST_INTR [04:04] */
#define BCHP_BSP_CONTROL_INTR2_PCI_MASK_CLEAR_BSP_TO_HOST_INTR_MASK 0x00000010
#define BCHP_BSP_CONTROL_INTR2_PCI_MASK_CLEAR_BSP_TO_HOST_INTR_SHIFT 4
#define BCHP_BSP_CONTROL_INTR2_PCI_MASK_CLEAR_BSP_TO_HOST_INTR_DEFAULT 0x00000001

/* BSP_CONTROL_INTR2 :: PCI_MASK_CLEAR :: NSK_INTR [03:03] */
#define BCHP_BSP_CONTROL_INTR2_PCI_MASK_CLEAR_NSK_INTR_MASK        0x00000008
#define BCHP_BSP_CONTROL_INTR2_PCI_MASK_CLEAR_NSK_INTR_SHIFT       3
#define BCHP_BSP_CONTROL_INTR2_PCI_MASK_CLEAR_NSK_INTR_DEFAULT     0x00000001

/* BSP_CONTROL_INTR2 :: PCI_MASK_CLEAR :: OCMDQUE_CR_INTR [02:02] */
#define BCHP_BSP_CONTROL_INTR2_PCI_MASK_CLEAR_OCMDQUE_CR_INTR_MASK 0x00000004
#define BCHP_BSP_CONTROL_INTR2_PCI_MASK_CLEAR_OCMDQUE_CR_INTR_SHIFT 2
#define BCHP_BSP_CONTROL_INTR2_PCI_MASK_CLEAR_OCMDQUE_CR_INTR_DEFAULT 0x00000001

/* BSP_CONTROL_INTR2 :: PCI_MASK_CLEAR :: OCMDQUE2_INTR [01:01] */
#define BCHP_BSP_CONTROL_INTR2_PCI_MASK_CLEAR_OCMDQUE2_INTR_MASK   0x00000002
#define BCHP_BSP_CONTROL_INTR2_PCI_MASK_CLEAR_OCMDQUE2_INTR_SHIFT  1
#define BCHP_BSP_CONTROL_INTR2_PCI_MASK_CLEAR_OCMDQUE2_INTR_DEFAULT 0x00000001

/* BSP_CONTROL_INTR2 :: PCI_MASK_CLEAR :: OCMDQUE1_INTR [00:00] */
#define BCHP_BSP_CONTROL_INTR2_PCI_MASK_CLEAR_OCMDQUE1_INTR_MASK   0x00000001
#define BCHP_BSP_CONTROL_INTR2_PCI_MASK_CLEAR_OCMDQUE1_INTR_SHIFT  0
#define BCHP_BSP_CONTROL_INTR2_PCI_MASK_CLEAR_OCMDQUE1_INTR_DEFAULT 0x00000001

#endif /* #ifndef BCHP_BSP_CONTROL_INTR2_H__ */

/* End of File */

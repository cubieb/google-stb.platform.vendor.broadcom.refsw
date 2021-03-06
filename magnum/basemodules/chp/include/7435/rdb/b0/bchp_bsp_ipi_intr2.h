/***************************************************************************
 *     Copyright (c) 1999-2012, Broadcom Corporation
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
 * Date:           Generated on         Wed May  9 08:36:42 2012
 *                 MD5 Checksum         d41d8cd98f00b204e9800998ecf8427e
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

#ifndef BCHP_BSP_IPI_INTR2_H__
#define BCHP_BSP_IPI_INTR2_H__

/***************************************************************************
 *BSP_IPI_INTR2 - BSP to SCPU Inter-Processor Level 2 Interrupt Controller Registers
 ***************************************************************************/
#define BCHP_BSP_IPI_INTR2_CPU_STATUS            0x003084c0 /* CPU interrupt Status Register */
#define BCHP_BSP_IPI_INTR2_CPU_SET               0x003084c4 /* CPU interrupt Set Register */
#define BCHP_BSP_IPI_INTR2_CPU_CLEAR             0x003084c8 /* CPU interrupt Clear Register */
#define BCHP_BSP_IPI_INTR2_CPU_MASK_STATUS       0x003084cc /* CPU interrupt Mask Status Register */
#define BCHP_BSP_IPI_INTR2_CPU_MASK_SET          0x003084d0 /* CPU interrupt Mask Set Register */
#define BCHP_BSP_IPI_INTR2_CPU_MASK_CLEAR        0x003084d4 /* CPU interrupt Mask Clear Register */
#define BCHP_BSP_IPI_INTR2_PCI_STATUS            0x003084d8 /* PCI interrupt Status Register */
#define BCHP_BSP_IPI_INTR2_PCI_SET               0x003084dc /* PCI interrupt Set Register */
#define BCHP_BSP_IPI_INTR2_PCI_CLEAR             0x003084e0 /* PCI interrupt Clear Register */
#define BCHP_BSP_IPI_INTR2_PCI_MASK_STATUS       0x003084e4 /* PCI interrupt Mask Status Register */
#define BCHP_BSP_IPI_INTR2_PCI_MASK_SET          0x003084e8 /* PCI interrupt Mask Set Register */
#define BCHP_BSP_IPI_INTR2_PCI_MASK_CLEAR        0x003084ec /* PCI interrupt Mask Clear Register */

/***************************************************************************
 *CPU_STATUS - CPU interrupt Status Register
 ***************************************************************************/
/* BSP_IPI_INTR2 :: CPU_STATUS :: SPARE_IPI [31:02] */
#define BCHP_BSP_IPI_INTR2_CPU_STATUS_SPARE_IPI_MASK               0xfffffffc
#define BCHP_BSP_IPI_INTR2_CPU_STATUS_SPARE_IPI_SHIFT              2
#define BCHP_BSP_IPI_INTR2_CPU_STATUS_SPARE_IPI_DEFAULT            0x00000000

/* BSP_IPI_INTR2 :: CPU_STATUS :: BSP_SCPU_OLOAD [01:01] */
#define BCHP_BSP_IPI_INTR2_CPU_STATUS_BSP_SCPU_OLOAD_MASK          0x00000002
#define BCHP_BSP_IPI_INTR2_CPU_STATUS_BSP_SCPU_OLOAD_SHIFT         1
#define BCHP_BSP_IPI_INTR2_CPU_STATUS_BSP_SCPU_OLOAD_DEFAULT       0x00000000

/* BSP_IPI_INTR2 :: CPU_STATUS :: BSP_SCPU_DRDY [00:00] */
#define BCHP_BSP_IPI_INTR2_CPU_STATUS_BSP_SCPU_DRDY_MASK           0x00000001
#define BCHP_BSP_IPI_INTR2_CPU_STATUS_BSP_SCPU_DRDY_SHIFT          0
#define BCHP_BSP_IPI_INTR2_CPU_STATUS_BSP_SCPU_DRDY_DEFAULT        0x00000000

/***************************************************************************
 *CPU_SET - CPU interrupt Set Register
 ***************************************************************************/
/* BSP_IPI_INTR2 :: CPU_SET :: SPARE_IPI [31:02] */
#define BCHP_BSP_IPI_INTR2_CPU_SET_SPARE_IPI_MASK                  0xfffffffc
#define BCHP_BSP_IPI_INTR2_CPU_SET_SPARE_IPI_SHIFT                 2
#define BCHP_BSP_IPI_INTR2_CPU_SET_SPARE_IPI_DEFAULT               0x00000000

/* BSP_IPI_INTR2 :: CPU_SET :: BSP_SCPU_OLOAD [01:01] */
#define BCHP_BSP_IPI_INTR2_CPU_SET_BSP_SCPU_OLOAD_MASK             0x00000002
#define BCHP_BSP_IPI_INTR2_CPU_SET_BSP_SCPU_OLOAD_SHIFT            1
#define BCHP_BSP_IPI_INTR2_CPU_SET_BSP_SCPU_OLOAD_DEFAULT          0x00000000

/* BSP_IPI_INTR2 :: CPU_SET :: BSP_SCPU_DRDY [00:00] */
#define BCHP_BSP_IPI_INTR2_CPU_SET_BSP_SCPU_DRDY_MASK              0x00000001
#define BCHP_BSP_IPI_INTR2_CPU_SET_BSP_SCPU_DRDY_SHIFT             0
#define BCHP_BSP_IPI_INTR2_CPU_SET_BSP_SCPU_DRDY_DEFAULT           0x00000000

/***************************************************************************
 *CPU_CLEAR - CPU interrupt Clear Register
 ***************************************************************************/
/* BSP_IPI_INTR2 :: CPU_CLEAR :: SPARE_IPI [31:02] */
#define BCHP_BSP_IPI_INTR2_CPU_CLEAR_SPARE_IPI_MASK                0xfffffffc
#define BCHP_BSP_IPI_INTR2_CPU_CLEAR_SPARE_IPI_SHIFT               2
#define BCHP_BSP_IPI_INTR2_CPU_CLEAR_SPARE_IPI_DEFAULT             0x00000000

/* BSP_IPI_INTR2 :: CPU_CLEAR :: BSP_SCPU_OLOAD [01:01] */
#define BCHP_BSP_IPI_INTR2_CPU_CLEAR_BSP_SCPU_OLOAD_MASK           0x00000002
#define BCHP_BSP_IPI_INTR2_CPU_CLEAR_BSP_SCPU_OLOAD_SHIFT          1
#define BCHP_BSP_IPI_INTR2_CPU_CLEAR_BSP_SCPU_OLOAD_DEFAULT        0x00000000

/* BSP_IPI_INTR2 :: CPU_CLEAR :: BSP_SCPU_DRDY [00:00] */
#define BCHP_BSP_IPI_INTR2_CPU_CLEAR_BSP_SCPU_DRDY_MASK            0x00000001
#define BCHP_BSP_IPI_INTR2_CPU_CLEAR_BSP_SCPU_DRDY_SHIFT           0
#define BCHP_BSP_IPI_INTR2_CPU_CLEAR_BSP_SCPU_DRDY_DEFAULT         0x00000000

/***************************************************************************
 *CPU_MASK_STATUS - CPU interrupt Mask Status Register
 ***************************************************************************/
/* BSP_IPI_INTR2 :: CPU_MASK_STATUS :: SPARE_IPI [31:02] */
#define BCHP_BSP_IPI_INTR2_CPU_MASK_STATUS_SPARE_IPI_MASK          0xfffffffc
#define BCHP_BSP_IPI_INTR2_CPU_MASK_STATUS_SPARE_IPI_SHIFT         2
#define BCHP_BSP_IPI_INTR2_CPU_MASK_STATUS_SPARE_IPI_DEFAULT       0x3fffffff

/* BSP_IPI_INTR2 :: CPU_MASK_STATUS :: BSP_SCPU_OLOAD [01:01] */
#define BCHP_BSP_IPI_INTR2_CPU_MASK_STATUS_BSP_SCPU_OLOAD_MASK     0x00000002
#define BCHP_BSP_IPI_INTR2_CPU_MASK_STATUS_BSP_SCPU_OLOAD_SHIFT    1
#define BCHP_BSP_IPI_INTR2_CPU_MASK_STATUS_BSP_SCPU_OLOAD_DEFAULT  0x00000001

/* BSP_IPI_INTR2 :: CPU_MASK_STATUS :: BSP_SCPU_DRDY [00:00] */
#define BCHP_BSP_IPI_INTR2_CPU_MASK_STATUS_BSP_SCPU_DRDY_MASK      0x00000001
#define BCHP_BSP_IPI_INTR2_CPU_MASK_STATUS_BSP_SCPU_DRDY_SHIFT     0
#define BCHP_BSP_IPI_INTR2_CPU_MASK_STATUS_BSP_SCPU_DRDY_DEFAULT   0x00000001

/***************************************************************************
 *CPU_MASK_SET - CPU interrupt Mask Set Register
 ***************************************************************************/
/* BSP_IPI_INTR2 :: CPU_MASK_SET :: SPARE_IPI [31:02] */
#define BCHP_BSP_IPI_INTR2_CPU_MASK_SET_SPARE_IPI_MASK             0xfffffffc
#define BCHP_BSP_IPI_INTR2_CPU_MASK_SET_SPARE_IPI_SHIFT            2
#define BCHP_BSP_IPI_INTR2_CPU_MASK_SET_SPARE_IPI_DEFAULT          0x3fffffff

/* BSP_IPI_INTR2 :: CPU_MASK_SET :: BSP_SCPU_OLOAD [01:01] */
#define BCHP_BSP_IPI_INTR2_CPU_MASK_SET_BSP_SCPU_OLOAD_MASK        0x00000002
#define BCHP_BSP_IPI_INTR2_CPU_MASK_SET_BSP_SCPU_OLOAD_SHIFT       1
#define BCHP_BSP_IPI_INTR2_CPU_MASK_SET_BSP_SCPU_OLOAD_DEFAULT     0x00000001

/* BSP_IPI_INTR2 :: CPU_MASK_SET :: BSP_SCPU_DRDY [00:00] */
#define BCHP_BSP_IPI_INTR2_CPU_MASK_SET_BSP_SCPU_DRDY_MASK         0x00000001
#define BCHP_BSP_IPI_INTR2_CPU_MASK_SET_BSP_SCPU_DRDY_SHIFT        0
#define BCHP_BSP_IPI_INTR2_CPU_MASK_SET_BSP_SCPU_DRDY_DEFAULT      0x00000001

/***************************************************************************
 *CPU_MASK_CLEAR - CPU interrupt Mask Clear Register
 ***************************************************************************/
/* BSP_IPI_INTR2 :: CPU_MASK_CLEAR :: SPARE_IPI [31:02] */
#define BCHP_BSP_IPI_INTR2_CPU_MASK_CLEAR_SPARE_IPI_MASK           0xfffffffc
#define BCHP_BSP_IPI_INTR2_CPU_MASK_CLEAR_SPARE_IPI_SHIFT          2
#define BCHP_BSP_IPI_INTR2_CPU_MASK_CLEAR_SPARE_IPI_DEFAULT        0x3fffffff

/* BSP_IPI_INTR2 :: CPU_MASK_CLEAR :: BSP_SCPU_OLOAD [01:01] */
#define BCHP_BSP_IPI_INTR2_CPU_MASK_CLEAR_BSP_SCPU_OLOAD_MASK      0x00000002
#define BCHP_BSP_IPI_INTR2_CPU_MASK_CLEAR_BSP_SCPU_OLOAD_SHIFT     1
#define BCHP_BSP_IPI_INTR2_CPU_MASK_CLEAR_BSP_SCPU_OLOAD_DEFAULT   0x00000001

/* BSP_IPI_INTR2 :: CPU_MASK_CLEAR :: BSP_SCPU_DRDY [00:00] */
#define BCHP_BSP_IPI_INTR2_CPU_MASK_CLEAR_BSP_SCPU_DRDY_MASK       0x00000001
#define BCHP_BSP_IPI_INTR2_CPU_MASK_CLEAR_BSP_SCPU_DRDY_SHIFT      0
#define BCHP_BSP_IPI_INTR2_CPU_MASK_CLEAR_BSP_SCPU_DRDY_DEFAULT    0x00000001

/***************************************************************************
 *PCI_STATUS - PCI interrupt Status Register
 ***************************************************************************/
/* BSP_IPI_INTR2 :: PCI_STATUS :: UNUSED [31:00] */
#define BCHP_BSP_IPI_INTR2_PCI_STATUS_UNUSED_MASK                  0xffffffff
#define BCHP_BSP_IPI_INTR2_PCI_STATUS_UNUSED_SHIFT                 0
#define BCHP_BSP_IPI_INTR2_PCI_STATUS_UNUSED_DEFAULT               0x00000000

/***************************************************************************
 *PCI_SET - PCI interrupt Set Register
 ***************************************************************************/
/* BSP_IPI_INTR2 :: PCI_SET :: UNUSED [31:00] */
#define BCHP_BSP_IPI_INTR2_PCI_SET_UNUSED_MASK                     0xffffffff
#define BCHP_BSP_IPI_INTR2_PCI_SET_UNUSED_SHIFT                    0
#define BCHP_BSP_IPI_INTR2_PCI_SET_UNUSED_DEFAULT                  0x00000000

/***************************************************************************
 *PCI_CLEAR - PCI interrupt Clear Register
 ***************************************************************************/
/* BSP_IPI_INTR2 :: PCI_CLEAR :: UNUSED [31:00] */
#define BCHP_BSP_IPI_INTR2_PCI_CLEAR_UNUSED_MASK                   0xffffffff
#define BCHP_BSP_IPI_INTR2_PCI_CLEAR_UNUSED_SHIFT                  0
#define BCHP_BSP_IPI_INTR2_PCI_CLEAR_UNUSED_DEFAULT                0x00000000

/***************************************************************************
 *PCI_MASK_STATUS - PCI interrupt Mask Status Register
 ***************************************************************************/
/* BSP_IPI_INTR2 :: PCI_MASK_STATUS :: UNUSED [31:00] */
#define BCHP_BSP_IPI_INTR2_PCI_MASK_STATUS_UNUSED_MASK             0xffffffff
#define BCHP_BSP_IPI_INTR2_PCI_MASK_STATUS_UNUSED_SHIFT            0
#define BCHP_BSP_IPI_INTR2_PCI_MASK_STATUS_UNUSED_DEFAULT          0xffffffff

/***************************************************************************
 *PCI_MASK_SET - PCI interrupt Mask Set Register
 ***************************************************************************/
/* BSP_IPI_INTR2 :: PCI_MASK_SET :: UNUSED [31:00] */
#define BCHP_BSP_IPI_INTR2_PCI_MASK_SET_UNUSED_MASK                0xffffffff
#define BCHP_BSP_IPI_INTR2_PCI_MASK_SET_UNUSED_SHIFT               0
#define BCHP_BSP_IPI_INTR2_PCI_MASK_SET_UNUSED_DEFAULT             0xffffffff

/***************************************************************************
 *PCI_MASK_CLEAR - PCI interrupt Mask Clear Register
 ***************************************************************************/
/* BSP_IPI_INTR2 :: PCI_MASK_CLEAR :: UNUSED [31:00] */
#define BCHP_BSP_IPI_INTR2_PCI_MASK_CLEAR_UNUSED_MASK              0xffffffff
#define BCHP_BSP_IPI_INTR2_PCI_MASK_CLEAR_UNUSED_SHIFT             0
#define BCHP_BSP_IPI_INTR2_PCI_MASK_CLEAR_UNUSED_DEFAULT           0xffffffff

#endif /* #ifndef BCHP_BSP_IPI_INTR2_H__ */

/* End of File */

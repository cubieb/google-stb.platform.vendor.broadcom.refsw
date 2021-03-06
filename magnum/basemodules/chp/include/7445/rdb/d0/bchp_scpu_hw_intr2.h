/***************************************************************************
 *     Copyright (c) 1999-2013, Broadcom Corporation
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
 * Date:           Generated on              Tue Oct 15 10:16:03 2013
 *                 Full Compile MD5 Checksum b60ac7dfc280cb4bf0d80e3267cd40cf
 *                   (minus title and desc)
 *                 MD5 Checksum              3f170c7b9754bf2f738d4d5d54ee17b6
 *
 * Compiled with:  RDB Utility               combo_header.pl
 *                 RDB Parser                3.0
 *                 unknown                   unknown
 *                 Perl Interpreter          5.008008
 *                 Operating System          linux
 *
 * Revision History:
 *
 * $brcm_Log: $
 *
 ***************************************************************************/

#ifndef BCHP_SCPU_HW_INTR2_H__
#define BCHP_SCPU_HW_INTR2_H__

/***************************************************************************
 *SCPU_HW_INTR2 - BSP to SCPU Inter-Processor Level 2 Interrupt Controller Registers
 ***************************************************************************/
#define BCHP_SCPU_HW_INTR2_CPU_STATUS            0x00310540 /* CPU interrupt Status Register */
#define BCHP_SCPU_HW_INTR2_CPU_SET               0x00310544 /* CPU interrupt Set Register */
#define BCHP_SCPU_HW_INTR2_CPU_CLEAR             0x00310548 /* CPU interrupt Clear Register */
#define BCHP_SCPU_HW_INTR2_CPU_MASK_STATUS       0x0031054c /* CPU interrupt Mask Status Register */
#define BCHP_SCPU_HW_INTR2_CPU_MASK_SET          0x00310550 /* CPU interrupt Mask Set Register */
#define BCHP_SCPU_HW_INTR2_CPU_MASK_CLEAR        0x00310554 /* CPU interrupt Mask Clear Register */
#define BCHP_SCPU_HW_INTR2_PCI_STATUS            0x00310558 /* PCI interrupt Status Register */
#define BCHP_SCPU_HW_INTR2_PCI_SET               0x0031055c /* PCI interrupt Set Register */
#define BCHP_SCPU_HW_INTR2_PCI_CLEAR             0x00310560 /* PCI interrupt Clear Register */
#define BCHP_SCPU_HW_INTR2_PCI_MASK_STATUS       0x00310564 /* PCI interrupt Mask Status Register */
#define BCHP_SCPU_HW_INTR2_PCI_MASK_SET          0x00310568 /* PCI interrupt Mask Set Register */
#define BCHP_SCPU_HW_INTR2_PCI_MASK_CLEAR        0x0031056c /* PCI interrupt Mask Clear Register */

/***************************************************************************
 *CPU_STATUS - CPU interrupt Status Register
 ***************************************************************************/
/* SCPU_HW_INTR2 :: CPU_STATUS :: SPARE_IPI [31:04] */
#define BCHP_SCPU_HW_INTR2_CPU_STATUS_SPARE_IPI_MASK               0xfffffff0
#define BCHP_SCPU_HW_INTR2_CPU_STATUS_SPARE_IPI_SHIFT              4
#define BCHP_SCPU_HW_INTR2_CPU_STATUS_SPARE_IPI_DEFAULT            0x00000000

/* SCPU_HW_INTR2 :: CPU_STATUS :: HDMI_RX1_INTR [03:03] */
#define BCHP_SCPU_HW_INTR2_CPU_STATUS_HDMI_RX1_INTR_MASK           0x00000008
#define BCHP_SCPU_HW_INTR2_CPU_STATUS_HDMI_RX1_INTR_SHIFT          3
#define BCHP_SCPU_HW_INTR2_CPU_STATUS_HDMI_RX1_INTR_DEFAULT        0x00000000

/* SCPU_HW_INTR2 :: CPU_STATUS :: HDMI_RX0_INTR [02:02] */
#define BCHP_SCPU_HW_INTR2_CPU_STATUS_HDMI_RX0_INTR_MASK           0x00000004
#define BCHP_SCPU_HW_INTR2_CPU_STATUS_HDMI_RX0_INTR_SHIFT          2
#define BCHP_SCPU_HW_INTR2_CPU_STATUS_HDMI_RX0_INTR_DEFAULT        0x00000000

/* SCPU_HW_INTR2 :: CPU_STATUS :: HDMI_TX1_INTR [01:01] */
#define BCHP_SCPU_HW_INTR2_CPU_STATUS_HDMI_TX1_INTR_MASK           0x00000002
#define BCHP_SCPU_HW_INTR2_CPU_STATUS_HDMI_TX1_INTR_SHIFT          1
#define BCHP_SCPU_HW_INTR2_CPU_STATUS_HDMI_TX1_INTR_DEFAULT        0x00000000

/* SCPU_HW_INTR2 :: CPU_STATUS :: HDMI_TX0_INTR [00:00] */
#define BCHP_SCPU_HW_INTR2_CPU_STATUS_HDMI_TX0_INTR_MASK           0x00000001
#define BCHP_SCPU_HW_INTR2_CPU_STATUS_HDMI_TX0_INTR_SHIFT          0
#define BCHP_SCPU_HW_INTR2_CPU_STATUS_HDMI_TX0_INTR_DEFAULT        0x00000000

/***************************************************************************
 *CPU_SET - CPU interrupt Set Register
 ***************************************************************************/
/* SCPU_HW_INTR2 :: CPU_SET :: SPARE_IPI [31:04] */
#define BCHP_SCPU_HW_INTR2_CPU_SET_SPARE_IPI_MASK                  0xfffffff0
#define BCHP_SCPU_HW_INTR2_CPU_SET_SPARE_IPI_SHIFT                 4
#define BCHP_SCPU_HW_INTR2_CPU_SET_SPARE_IPI_DEFAULT               0x00000000

/* SCPU_HW_INTR2 :: CPU_SET :: HDMI_RX1_INTR [03:03] */
#define BCHP_SCPU_HW_INTR2_CPU_SET_HDMI_RX1_INTR_MASK              0x00000008
#define BCHP_SCPU_HW_INTR2_CPU_SET_HDMI_RX1_INTR_SHIFT             3
#define BCHP_SCPU_HW_INTR2_CPU_SET_HDMI_RX1_INTR_DEFAULT           0x00000000

/* SCPU_HW_INTR2 :: CPU_SET :: HDMI_RX0_INTR [02:02] */
#define BCHP_SCPU_HW_INTR2_CPU_SET_HDMI_RX0_INTR_MASK              0x00000004
#define BCHP_SCPU_HW_INTR2_CPU_SET_HDMI_RX0_INTR_SHIFT             2
#define BCHP_SCPU_HW_INTR2_CPU_SET_HDMI_RX0_INTR_DEFAULT           0x00000000

/* SCPU_HW_INTR2 :: CPU_SET :: HDMI_TX1_INTR [01:01] */
#define BCHP_SCPU_HW_INTR2_CPU_SET_HDMI_TX1_INTR_MASK              0x00000002
#define BCHP_SCPU_HW_INTR2_CPU_SET_HDMI_TX1_INTR_SHIFT             1
#define BCHP_SCPU_HW_INTR2_CPU_SET_HDMI_TX1_INTR_DEFAULT           0x00000000

/* SCPU_HW_INTR2 :: CPU_SET :: HDMI_TX0_INTR [00:00] */
#define BCHP_SCPU_HW_INTR2_CPU_SET_HDMI_TX0_INTR_MASK              0x00000001
#define BCHP_SCPU_HW_INTR2_CPU_SET_HDMI_TX0_INTR_SHIFT             0
#define BCHP_SCPU_HW_INTR2_CPU_SET_HDMI_TX0_INTR_DEFAULT           0x00000000

/***************************************************************************
 *CPU_CLEAR - CPU interrupt Clear Register
 ***************************************************************************/
/* SCPU_HW_INTR2 :: CPU_CLEAR :: SPARE_IPI [31:04] */
#define BCHP_SCPU_HW_INTR2_CPU_CLEAR_SPARE_IPI_MASK                0xfffffff0
#define BCHP_SCPU_HW_INTR2_CPU_CLEAR_SPARE_IPI_SHIFT               4
#define BCHP_SCPU_HW_INTR2_CPU_CLEAR_SPARE_IPI_DEFAULT             0x00000000

/* SCPU_HW_INTR2 :: CPU_CLEAR :: HDMI_RX1_INTR [03:03] */
#define BCHP_SCPU_HW_INTR2_CPU_CLEAR_HDMI_RX1_INTR_MASK            0x00000008
#define BCHP_SCPU_HW_INTR2_CPU_CLEAR_HDMI_RX1_INTR_SHIFT           3
#define BCHP_SCPU_HW_INTR2_CPU_CLEAR_HDMI_RX1_INTR_DEFAULT         0x00000000

/* SCPU_HW_INTR2 :: CPU_CLEAR :: HDMI_RX0_INTR [02:02] */
#define BCHP_SCPU_HW_INTR2_CPU_CLEAR_HDMI_RX0_INTR_MASK            0x00000004
#define BCHP_SCPU_HW_INTR2_CPU_CLEAR_HDMI_RX0_INTR_SHIFT           2
#define BCHP_SCPU_HW_INTR2_CPU_CLEAR_HDMI_RX0_INTR_DEFAULT         0x00000000

/* SCPU_HW_INTR2 :: CPU_CLEAR :: HDMI_TX1_INTR [01:01] */
#define BCHP_SCPU_HW_INTR2_CPU_CLEAR_HDMI_TX1_INTR_MASK            0x00000002
#define BCHP_SCPU_HW_INTR2_CPU_CLEAR_HDMI_TX1_INTR_SHIFT           1
#define BCHP_SCPU_HW_INTR2_CPU_CLEAR_HDMI_TX1_INTR_DEFAULT         0x00000000

/* SCPU_HW_INTR2 :: CPU_CLEAR :: HDMI_TX0_INTR [00:00] */
#define BCHP_SCPU_HW_INTR2_CPU_CLEAR_HDMI_TX0_INTR_MASK            0x00000001
#define BCHP_SCPU_HW_INTR2_CPU_CLEAR_HDMI_TX0_INTR_SHIFT           0
#define BCHP_SCPU_HW_INTR2_CPU_CLEAR_HDMI_TX0_INTR_DEFAULT         0x00000000

/***************************************************************************
 *CPU_MASK_STATUS - CPU interrupt Mask Status Register
 ***************************************************************************/
/* SCPU_HW_INTR2 :: CPU_MASK_STATUS :: SPARE_IPI [31:04] */
#define BCHP_SCPU_HW_INTR2_CPU_MASK_STATUS_SPARE_IPI_MASK          0xfffffff0
#define BCHP_SCPU_HW_INTR2_CPU_MASK_STATUS_SPARE_IPI_SHIFT         4
#define BCHP_SCPU_HW_INTR2_CPU_MASK_STATUS_SPARE_IPI_DEFAULT       0x0fffffff

/* SCPU_HW_INTR2 :: CPU_MASK_STATUS :: HDMI_RX1_INTR [03:03] */
#define BCHP_SCPU_HW_INTR2_CPU_MASK_STATUS_HDMI_RX1_INTR_MASK      0x00000008
#define BCHP_SCPU_HW_INTR2_CPU_MASK_STATUS_HDMI_RX1_INTR_SHIFT     3
#define BCHP_SCPU_HW_INTR2_CPU_MASK_STATUS_HDMI_RX1_INTR_DEFAULT   0x00000001

/* SCPU_HW_INTR2 :: CPU_MASK_STATUS :: HDMI_RX0_INTR [02:02] */
#define BCHP_SCPU_HW_INTR2_CPU_MASK_STATUS_HDMI_RX0_INTR_MASK      0x00000004
#define BCHP_SCPU_HW_INTR2_CPU_MASK_STATUS_HDMI_RX0_INTR_SHIFT     2
#define BCHP_SCPU_HW_INTR2_CPU_MASK_STATUS_HDMI_RX0_INTR_DEFAULT   0x00000001

/* SCPU_HW_INTR2 :: CPU_MASK_STATUS :: HDMI_TX1_INTR [01:01] */
#define BCHP_SCPU_HW_INTR2_CPU_MASK_STATUS_HDMI_TX1_INTR_MASK      0x00000002
#define BCHP_SCPU_HW_INTR2_CPU_MASK_STATUS_HDMI_TX1_INTR_SHIFT     1
#define BCHP_SCPU_HW_INTR2_CPU_MASK_STATUS_HDMI_TX1_INTR_DEFAULT   0x00000001

/* SCPU_HW_INTR2 :: CPU_MASK_STATUS :: HDMI_TX0_INTR [00:00] */
#define BCHP_SCPU_HW_INTR2_CPU_MASK_STATUS_HDMI_TX0_INTR_MASK      0x00000001
#define BCHP_SCPU_HW_INTR2_CPU_MASK_STATUS_HDMI_TX0_INTR_SHIFT     0
#define BCHP_SCPU_HW_INTR2_CPU_MASK_STATUS_HDMI_TX0_INTR_DEFAULT   0x00000001

/***************************************************************************
 *CPU_MASK_SET - CPU interrupt Mask Set Register
 ***************************************************************************/
/* SCPU_HW_INTR2 :: CPU_MASK_SET :: SPARE_IPI [31:04] */
#define BCHP_SCPU_HW_INTR2_CPU_MASK_SET_SPARE_IPI_MASK             0xfffffff0
#define BCHP_SCPU_HW_INTR2_CPU_MASK_SET_SPARE_IPI_SHIFT            4
#define BCHP_SCPU_HW_INTR2_CPU_MASK_SET_SPARE_IPI_DEFAULT          0x0fffffff

/* SCPU_HW_INTR2 :: CPU_MASK_SET :: HDMI_RX1_INTR [03:03] */
#define BCHP_SCPU_HW_INTR2_CPU_MASK_SET_HDMI_RX1_INTR_MASK         0x00000008
#define BCHP_SCPU_HW_INTR2_CPU_MASK_SET_HDMI_RX1_INTR_SHIFT        3
#define BCHP_SCPU_HW_INTR2_CPU_MASK_SET_HDMI_RX1_INTR_DEFAULT      0x00000001

/* SCPU_HW_INTR2 :: CPU_MASK_SET :: HDMI_RX0_INTR [02:02] */
#define BCHP_SCPU_HW_INTR2_CPU_MASK_SET_HDMI_RX0_INTR_MASK         0x00000004
#define BCHP_SCPU_HW_INTR2_CPU_MASK_SET_HDMI_RX0_INTR_SHIFT        2
#define BCHP_SCPU_HW_INTR2_CPU_MASK_SET_HDMI_RX0_INTR_DEFAULT      0x00000001

/* SCPU_HW_INTR2 :: CPU_MASK_SET :: HDMI_TX1_INTR [01:01] */
#define BCHP_SCPU_HW_INTR2_CPU_MASK_SET_HDMI_TX1_INTR_MASK         0x00000002
#define BCHP_SCPU_HW_INTR2_CPU_MASK_SET_HDMI_TX1_INTR_SHIFT        1
#define BCHP_SCPU_HW_INTR2_CPU_MASK_SET_HDMI_TX1_INTR_DEFAULT      0x00000001

/* SCPU_HW_INTR2 :: CPU_MASK_SET :: HDMI_TX0_INTR [00:00] */
#define BCHP_SCPU_HW_INTR2_CPU_MASK_SET_HDMI_TX0_INTR_MASK         0x00000001
#define BCHP_SCPU_HW_INTR2_CPU_MASK_SET_HDMI_TX0_INTR_SHIFT        0
#define BCHP_SCPU_HW_INTR2_CPU_MASK_SET_HDMI_TX0_INTR_DEFAULT      0x00000001

/***************************************************************************
 *CPU_MASK_CLEAR - CPU interrupt Mask Clear Register
 ***************************************************************************/
/* SCPU_HW_INTR2 :: CPU_MASK_CLEAR :: SPARE_IPI [31:04] */
#define BCHP_SCPU_HW_INTR2_CPU_MASK_CLEAR_SPARE_IPI_MASK           0xfffffff0
#define BCHP_SCPU_HW_INTR2_CPU_MASK_CLEAR_SPARE_IPI_SHIFT          4
#define BCHP_SCPU_HW_INTR2_CPU_MASK_CLEAR_SPARE_IPI_DEFAULT        0x0fffffff

/* SCPU_HW_INTR2 :: CPU_MASK_CLEAR :: HDMI_RX1_INTR [03:03] */
#define BCHP_SCPU_HW_INTR2_CPU_MASK_CLEAR_HDMI_RX1_INTR_MASK       0x00000008
#define BCHP_SCPU_HW_INTR2_CPU_MASK_CLEAR_HDMI_RX1_INTR_SHIFT      3
#define BCHP_SCPU_HW_INTR2_CPU_MASK_CLEAR_HDMI_RX1_INTR_DEFAULT    0x00000001

/* SCPU_HW_INTR2 :: CPU_MASK_CLEAR :: HDMI_RX0_INTR [02:02] */
#define BCHP_SCPU_HW_INTR2_CPU_MASK_CLEAR_HDMI_RX0_INTR_MASK       0x00000004
#define BCHP_SCPU_HW_INTR2_CPU_MASK_CLEAR_HDMI_RX0_INTR_SHIFT      2
#define BCHP_SCPU_HW_INTR2_CPU_MASK_CLEAR_HDMI_RX0_INTR_DEFAULT    0x00000001

/* SCPU_HW_INTR2 :: CPU_MASK_CLEAR :: HDMI_TX1_INTR [01:01] */
#define BCHP_SCPU_HW_INTR2_CPU_MASK_CLEAR_HDMI_TX1_INTR_MASK       0x00000002
#define BCHP_SCPU_HW_INTR2_CPU_MASK_CLEAR_HDMI_TX1_INTR_SHIFT      1
#define BCHP_SCPU_HW_INTR2_CPU_MASK_CLEAR_HDMI_TX1_INTR_DEFAULT    0x00000001

/* SCPU_HW_INTR2 :: CPU_MASK_CLEAR :: HDMI_TX0_INTR [00:00] */
#define BCHP_SCPU_HW_INTR2_CPU_MASK_CLEAR_HDMI_TX0_INTR_MASK       0x00000001
#define BCHP_SCPU_HW_INTR2_CPU_MASK_CLEAR_HDMI_TX0_INTR_SHIFT      0
#define BCHP_SCPU_HW_INTR2_CPU_MASK_CLEAR_HDMI_TX0_INTR_DEFAULT    0x00000001

/***************************************************************************
 *PCI_STATUS - PCI interrupt Status Register
 ***************************************************************************/
/* SCPU_HW_INTR2 :: PCI_STATUS :: UNUSED [31:00] */
#define BCHP_SCPU_HW_INTR2_PCI_STATUS_UNUSED_MASK                  0xffffffff
#define BCHP_SCPU_HW_INTR2_PCI_STATUS_UNUSED_SHIFT                 0
#define BCHP_SCPU_HW_INTR2_PCI_STATUS_UNUSED_DEFAULT               0x00000000

/***************************************************************************
 *PCI_SET - PCI interrupt Set Register
 ***************************************************************************/
/* SCPU_HW_INTR2 :: PCI_SET :: UNUSED [31:00] */
#define BCHP_SCPU_HW_INTR2_PCI_SET_UNUSED_MASK                     0xffffffff
#define BCHP_SCPU_HW_INTR2_PCI_SET_UNUSED_SHIFT                    0
#define BCHP_SCPU_HW_INTR2_PCI_SET_UNUSED_DEFAULT                  0x00000000

/***************************************************************************
 *PCI_CLEAR - PCI interrupt Clear Register
 ***************************************************************************/
/* SCPU_HW_INTR2 :: PCI_CLEAR :: UNUSED [31:00] */
#define BCHP_SCPU_HW_INTR2_PCI_CLEAR_UNUSED_MASK                   0xffffffff
#define BCHP_SCPU_HW_INTR2_PCI_CLEAR_UNUSED_SHIFT                  0
#define BCHP_SCPU_HW_INTR2_PCI_CLEAR_UNUSED_DEFAULT                0x00000000

/***************************************************************************
 *PCI_MASK_STATUS - PCI interrupt Mask Status Register
 ***************************************************************************/
/* SCPU_HW_INTR2 :: PCI_MASK_STATUS :: UNUSED [31:00] */
#define BCHP_SCPU_HW_INTR2_PCI_MASK_STATUS_UNUSED_MASK             0xffffffff
#define BCHP_SCPU_HW_INTR2_PCI_MASK_STATUS_UNUSED_SHIFT            0
#define BCHP_SCPU_HW_INTR2_PCI_MASK_STATUS_UNUSED_DEFAULT          0xffffffff

/***************************************************************************
 *PCI_MASK_SET - PCI interrupt Mask Set Register
 ***************************************************************************/
/* SCPU_HW_INTR2 :: PCI_MASK_SET :: UNUSED [31:00] */
#define BCHP_SCPU_HW_INTR2_PCI_MASK_SET_UNUSED_MASK                0xffffffff
#define BCHP_SCPU_HW_INTR2_PCI_MASK_SET_UNUSED_SHIFT               0
#define BCHP_SCPU_HW_INTR2_PCI_MASK_SET_UNUSED_DEFAULT             0xffffffff

/***************************************************************************
 *PCI_MASK_CLEAR - PCI interrupt Mask Clear Register
 ***************************************************************************/
/* SCPU_HW_INTR2 :: PCI_MASK_CLEAR :: UNUSED [31:00] */
#define BCHP_SCPU_HW_INTR2_PCI_MASK_CLEAR_UNUSED_MASK              0xffffffff
#define BCHP_SCPU_HW_INTR2_PCI_MASK_CLEAR_UNUSED_SHIFT             0
#define BCHP_SCPU_HW_INTR2_PCI_MASK_CLEAR_UNUSED_DEFAULT           0xffffffff

#endif /* #ifndef BCHP_SCPU_HW_INTR2_H__ */

/* End of File */

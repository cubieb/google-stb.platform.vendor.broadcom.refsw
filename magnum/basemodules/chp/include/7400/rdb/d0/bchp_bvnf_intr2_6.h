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
 * Date:           Generated on         Mon Jul 23 12:03:04 2007
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

#ifndef BCHP_BVNF_INTR2_6_H__
#define BCHP_BVNF_INTR2_6_H__

/***************************************************************************
 *BVNF_INTR2_6 - BVN Front Interrupt Controller 6 (BVN Errors INTR to CPU) Registers
 ***************************************************************************/
#define BCHP_BVNF_INTR2_6_R5F_STATUS             0x00103600 /* R5f interrupt Status Register */
#define BCHP_BVNF_INTR2_6_R5F_SET                0x00103604 /* R5f interrupt Set Register */
#define BCHP_BVNF_INTR2_6_R5F_CLEAR              0x00103608 /* R5f interrupt Clear Register */
#define BCHP_BVNF_INTR2_6_R5F_MASK_STATUS        0x0010360c /* R5f interrupt Mask Status Register */
#define BCHP_BVNF_INTR2_6_R5F_MASK_SET           0x00103610 /* R5f interrupt Mask Set Register */
#define BCHP_BVNF_INTR2_6_R5F_MASK_CLEAR         0x00103614 /* R5f interrupt Mask Clear Register */
#define BCHP_BVNF_INTR2_6_PCI_STATUS             0x00103618 /* PCI interrupt Status Register */
#define BCHP_BVNF_INTR2_6_PCI_SET                0x0010361c /* PCI interrupt Set Register */
#define BCHP_BVNF_INTR2_6_PCI_CLEAR              0x00103620 /* PCI interrupt Clear Register */
#define BCHP_BVNF_INTR2_6_PCI_MASK_STATUS        0x00103624 /* PCI interrupt Mask Status Register */
#define BCHP_BVNF_INTR2_6_PCI_MASK_SET           0x00103628 /* PCI interrupt Mask Set Register */
#define BCHP_BVNF_INTR2_6_PCI_MASK_CLEAR         0x0010362c /* PCI interrupt Mask Clear Register */

/***************************************************************************
 *R5F_STATUS - R5f interrupt Status Register
 ***************************************************************************/
/* BVNF_INTR2_6 :: R5F_STATUS :: reserved0 [31:01] */
#define BCHP_BVNF_INTR2_6_R5F_STATUS_reserved0_MASK                0xfffffffe
#define BCHP_BVNF_INTR2_6_R5F_STATUS_reserved0_SHIFT               1

/* BVNF_INTR2_6 :: R5F_STATUS :: FGT_0_ERR_INTR [00:00] */
#define BCHP_BVNF_INTR2_6_R5F_STATUS_FGT_0_ERR_INTR_MASK           0x00000001
#define BCHP_BVNF_INTR2_6_R5F_STATUS_FGT_0_ERR_INTR_SHIFT          0

/***************************************************************************
 *R5F_SET - R5f interrupt Set Register
 ***************************************************************************/
/* BVNF_INTR2_6 :: R5F_SET :: reserved0 [31:01] */
#define BCHP_BVNF_INTR2_6_R5F_SET_reserved0_MASK                   0xfffffffe
#define BCHP_BVNF_INTR2_6_R5F_SET_reserved0_SHIFT                  1

/* BVNF_INTR2_6 :: R5F_SET :: FGT_0_ERR_INTR [00:00] */
#define BCHP_BVNF_INTR2_6_R5F_SET_FGT_0_ERR_INTR_MASK              0x00000001
#define BCHP_BVNF_INTR2_6_R5F_SET_FGT_0_ERR_INTR_SHIFT             0

/***************************************************************************
 *R5F_CLEAR - R5f interrupt Clear Register
 ***************************************************************************/
/* BVNF_INTR2_6 :: R5F_CLEAR :: reserved0 [31:01] */
#define BCHP_BVNF_INTR2_6_R5F_CLEAR_reserved0_MASK                 0xfffffffe
#define BCHP_BVNF_INTR2_6_R5F_CLEAR_reserved0_SHIFT                1

/* BVNF_INTR2_6 :: R5F_CLEAR :: FGT_0_ERR_INTR [00:00] */
#define BCHP_BVNF_INTR2_6_R5F_CLEAR_FGT_0_ERR_INTR_MASK            0x00000001
#define BCHP_BVNF_INTR2_6_R5F_CLEAR_FGT_0_ERR_INTR_SHIFT           0

/***************************************************************************
 *R5F_MASK_STATUS - R5f interrupt Mask Status Register
 ***************************************************************************/
/* BVNF_INTR2_6 :: R5F_MASK_STATUS :: reserved0 [31:01] */
#define BCHP_BVNF_INTR2_6_R5F_MASK_STATUS_reserved0_MASK           0xfffffffe
#define BCHP_BVNF_INTR2_6_R5F_MASK_STATUS_reserved0_SHIFT          1

/* BVNF_INTR2_6 :: R5F_MASK_STATUS :: FGT_0_ERR_INTR [00:00] */
#define BCHP_BVNF_INTR2_6_R5F_MASK_STATUS_FGT_0_ERR_INTR_MASK      0x00000001
#define BCHP_BVNF_INTR2_6_R5F_MASK_STATUS_FGT_0_ERR_INTR_SHIFT     0

/***************************************************************************
 *R5F_MASK_SET - R5f interrupt Mask Set Register
 ***************************************************************************/
/* BVNF_INTR2_6 :: R5F_MASK_SET :: reserved0 [31:01] */
#define BCHP_BVNF_INTR2_6_R5F_MASK_SET_reserved0_MASK              0xfffffffe
#define BCHP_BVNF_INTR2_6_R5F_MASK_SET_reserved0_SHIFT             1

/* BVNF_INTR2_6 :: R5F_MASK_SET :: FGT_0_ERR_INTR [00:00] */
#define BCHP_BVNF_INTR2_6_R5F_MASK_SET_FGT_0_ERR_INTR_MASK         0x00000001
#define BCHP_BVNF_INTR2_6_R5F_MASK_SET_FGT_0_ERR_INTR_SHIFT        0

/***************************************************************************
 *R5F_MASK_CLEAR - R5f interrupt Mask Clear Register
 ***************************************************************************/
/* BVNF_INTR2_6 :: R5F_MASK_CLEAR :: reserved0 [31:01] */
#define BCHP_BVNF_INTR2_6_R5F_MASK_CLEAR_reserved0_MASK            0xfffffffe
#define BCHP_BVNF_INTR2_6_R5F_MASK_CLEAR_reserved0_SHIFT           1

/* BVNF_INTR2_6 :: R5F_MASK_CLEAR :: FGT_0_ERR_INTR [00:00] */
#define BCHP_BVNF_INTR2_6_R5F_MASK_CLEAR_FGT_0_ERR_INTR_MASK       0x00000001
#define BCHP_BVNF_INTR2_6_R5F_MASK_CLEAR_FGT_0_ERR_INTR_SHIFT      0

/***************************************************************************
 *PCI_STATUS - PCI interrupt Status Register
 ***************************************************************************/
/* BVNF_INTR2_6 :: PCI_STATUS :: reserved0 [31:01] */
#define BCHP_BVNF_INTR2_6_PCI_STATUS_reserved0_MASK                0xfffffffe
#define BCHP_BVNF_INTR2_6_PCI_STATUS_reserved0_SHIFT               1

/* BVNF_INTR2_6 :: PCI_STATUS :: FGT_0_ERR_INTR [00:00] */
#define BCHP_BVNF_INTR2_6_PCI_STATUS_FGT_0_ERR_INTR_MASK           0x00000001
#define BCHP_BVNF_INTR2_6_PCI_STATUS_FGT_0_ERR_INTR_SHIFT          0

/***************************************************************************
 *PCI_SET - PCI interrupt Set Register
 ***************************************************************************/
/* BVNF_INTR2_6 :: PCI_SET :: reserved0 [31:01] */
#define BCHP_BVNF_INTR2_6_PCI_SET_reserved0_MASK                   0xfffffffe
#define BCHP_BVNF_INTR2_6_PCI_SET_reserved0_SHIFT                  1

/* BVNF_INTR2_6 :: PCI_SET :: FGT_0_ERR_INTR [00:00] */
#define BCHP_BVNF_INTR2_6_PCI_SET_FGT_0_ERR_INTR_MASK              0x00000001
#define BCHP_BVNF_INTR2_6_PCI_SET_FGT_0_ERR_INTR_SHIFT             0

/***************************************************************************
 *PCI_CLEAR - PCI interrupt Clear Register
 ***************************************************************************/
/* BVNF_INTR2_6 :: PCI_CLEAR :: reserved0 [31:01] */
#define BCHP_BVNF_INTR2_6_PCI_CLEAR_reserved0_MASK                 0xfffffffe
#define BCHP_BVNF_INTR2_6_PCI_CLEAR_reserved0_SHIFT                1

/* BVNF_INTR2_6 :: PCI_CLEAR :: FGT_0_ERR_INTR [00:00] */
#define BCHP_BVNF_INTR2_6_PCI_CLEAR_FGT_0_ERR_INTR_MASK            0x00000001
#define BCHP_BVNF_INTR2_6_PCI_CLEAR_FGT_0_ERR_INTR_SHIFT           0

/***************************************************************************
 *PCI_MASK_STATUS - PCI interrupt Mask Status Register
 ***************************************************************************/
/* BVNF_INTR2_6 :: PCI_MASK_STATUS :: reserved0 [31:01] */
#define BCHP_BVNF_INTR2_6_PCI_MASK_STATUS_reserved0_MASK           0xfffffffe
#define BCHP_BVNF_INTR2_6_PCI_MASK_STATUS_reserved0_SHIFT          1

/* BVNF_INTR2_6 :: PCI_MASK_STATUS :: FGT_0_ERR_INTR [00:00] */
#define BCHP_BVNF_INTR2_6_PCI_MASK_STATUS_FGT_0_ERR_INTR_MASK      0x00000001
#define BCHP_BVNF_INTR2_6_PCI_MASK_STATUS_FGT_0_ERR_INTR_SHIFT     0

/***************************************************************************
 *PCI_MASK_SET - PCI interrupt Mask Set Register
 ***************************************************************************/
/* BVNF_INTR2_6 :: PCI_MASK_SET :: reserved0 [31:01] */
#define BCHP_BVNF_INTR2_6_PCI_MASK_SET_reserved0_MASK              0xfffffffe
#define BCHP_BVNF_INTR2_6_PCI_MASK_SET_reserved0_SHIFT             1

/* BVNF_INTR2_6 :: PCI_MASK_SET :: FGT_0_ERR_INTR [00:00] */
#define BCHP_BVNF_INTR2_6_PCI_MASK_SET_FGT_0_ERR_INTR_MASK         0x00000001
#define BCHP_BVNF_INTR2_6_PCI_MASK_SET_FGT_0_ERR_INTR_SHIFT        0

/***************************************************************************
 *PCI_MASK_CLEAR - PCI interrupt Mask Clear Register
 ***************************************************************************/
/* BVNF_INTR2_6 :: PCI_MASK_CLEAR :: reserved0 [31:01] */
#define BCHP_BVNF_INTR2_6_PCI_MASK_CLEAR_reserved0_MASK            0xfffffffe
#define BCHP_BVNF_INTR2_6_PCI_MASK_CLEAR_reserved0_SHIFT           1

/* BVNF_INTR2_6 :: PCI_MASK_CLEAR :: FGT_0_ERR_INTR [00:00] */
#define BCHP_BVNF_INTR2_6_PCI_MASK_CLEAR_FGT_0_ERR_INTR_MASK       0x00000001
#define BCHP_BVNF_INTR2_6_PCI_MASK_CLEAR_FGT_0_ERR_INTR_SHIFT      0

#endif /* #ifndef BCHP_BVNF_INTR2_6_H__ */

/* End of File */

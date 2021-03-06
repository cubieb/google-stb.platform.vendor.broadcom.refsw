/****************************************************************************
 *     Copyright (c) 1999-2014, Broadcom Corporation
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
 * Date:           Generated on               Wed Feb 11 10:14:00 2015
 *                 Full Compile MD5 Checksum  f7f4bd55341805fcfe958ba5e47e65f4
 *                     (minus title and desc)
 *                 MD5 Checksum               95b679a9655597a92593cae55222c397
 *
 * Compiled with:  RDB Utility                combo_header.pl
 *                 RDB.pm                     15653
 *                 unknown                    unknown
 *                 Perl Interpreter           5.008008
 *                 Operating System           linux
 *
 *
 ***************************************************************************/

#ifndef BCHP_UPG_AUX_AON_INTR2_H__
#define BCHP_UPG_AUX_AON_INTR2_H__

/***************************************************************************
 *UPG_AUX_AON_INTR2 - UPG AUX AON Level 2 Interrupt Registers
 ***************************************************************************/
#define BCHP_UPG_AUX_AON_INTR2_CPU_STATUS        0x00417400 /* [RO] CPU interrupt Status Register */
#define BCHP_UPG_AUX_AON_INTR2_CPU_SET           0x00417404 /* [WO] CPU interrupt Set Register */
#define BCHP_UPG_AUX_AON_INTR2_CPU_CLEAR         0x00417408 /* [WO] CPU interrupt Clear Register */
#define BCHP_UPG_AUX_AON_INTR2_CPU_MASK_STATUS   0x0041740c /* [RO] CPU interrupt Mask Status Register */
#define BCHP_UPG_AUX_AON_INTR2_CPU_MASK_SET      0x00417410 /* [WO] CPU interrupt Mask Set Register */
#define BCHP_UPG_AUX_AON_INTR2_CPU_MASK_CLEAR    0x00417414 /* [WO] CPU interrupt Mask Clear Register */
#define BCHP_UPG_AUX_AON_INTR2_PCI_STATUS        0x00417418 /* [RO] PCI interrupt Status Register */
#define BCHP_UPG_AUX_AON_INTR2_PCI_SET           0x0041741c /* [WO] PCI interrupt Set Register */
#define BCHP_UPG_AUX_AON_INTR2_PCI_CLEAR         0x00417420 /* [WO] PCI interrupt Clear Register */
#define BCHP_UPG_AUX_AON_INTR2_PCI_MASK_STATUS   0x00417424 /* [RO] PCI interrupt Mask Status Register */
#define BCHP_UPG_AUX_AON_INTR2_PCI_MASK_SET      0x00417428 /* [WO] PCI interrupt Mask Set Register */
#define BCHP_UPG_AUX_AON_INTR2_PCI_MASK_CLEAR    0x0041742c /* [WO] PCI interrupt Mask Clear Register */

/***************************************************************************
 *CPU_STATUS - CPU interrupt Status Register
 ***************************************************************************/
/* UPG_AUX_AON_INTR2 :: CPU_STATUS :: reserved0 [31:09] */
#define BCHP_UPG_AUX_AON_INTR2_CPU_STATUS_reserved0_MASK           0xfffffe00
#define BCHP_UPG_AUX_AON_INTR2_CPU_STATUS_reserved0_SHIFT          9

/* UPG_AUX_AON_INTR2 :: CPU_STATUS :: WKTMR_ALARM_INTR [08:08] */
#define BCHP_UPG_AUX_AON_INTR2_CPU_STATUS_WKTMR_ALARM_INTR_MASK    0x00000100
#define BCHP_UPG_AUX_AON_INTR2_CPU_STATUS_WKTMR_ALARM_INTR_SHIFT   8
#define BCHP_UPG_AUX_AON_INTR2_CPU_STATUS_WKTMR_ALARM_INTR_DEFAULT 0x00000000

/* UPG_AUX_AON_INTR2 :: CPU_STATUS :: reserved_for_eco1 [07:07] */
#define BCHP_UPG_AUX_AON_INTR2_CPU_STATUS_reserved_for_eco1_MASK   0x00000080
#define BCHP_UPG_AUX_AON_INTR2_CPU_STATUS_reserved_for_eco1_SHIFT  7
#define BCHP_UPG_AUX_AON_INTR2_CPU_STATUS_reserved_for_eco1_DEFAULT 0x00000000

/* UPG_AUX_AON_INTR2 :: CPU_STATUS :: BICAP_FIFO_OF_INTR [06:06] */
#define BCHP_UPG_AUX_AON_INTR2_CPU_STATUS_BICAP_FIFO_OF_INTR_MASK  0x00000040
#define BCHP_UPG_AUX_AON_INTR2_CPU_STATUS_BICAP_FIFO_OF_INTR_SHIFT 6
#define BCHP_UPG_AUX_AON_INTR2_CPU_STATUS_BICAP_FIFO_OF_INTR_DEFAULT 0x00000000

/* UPG_AUX_AON_INTR2 :: CPU_STATUS :: BICAP_FIFO_LVL_INTR [05:05] */
#define BCHP_UPG_AUX_AON_INTR2_CPU_STATUS_BICAP_FIFO_LVL_INTR_MASK 0x00000020
#define BCHP_UPG_AUX_AON_INTR2_CPU_STATUS_BICAP_FIFO_LVL_INTR_SHIFT 5
#define BCHP_UPG_AUX_AON_INTR2_CPU_STATUS_BICAP_FIFO_LVL_INTR_DEFAULT 0x00000000

/* UPG_AUX_AON_INTR2 :: CPU_STATUS :: BICAP_FIFO_INACT_INTR [04:04] */
#define BCHP_UPG_AUX_AON_INTR2_CPU_STATUS_BICAP_FIFO_INACT_INTR_MASK 0x00000010
#define BCHP_UPG_AUX_AON_INTR2_CPU_STATUS_BICAP_FIFO_INACT_INTR_SHIFT 4
#define BCHP_UPG_AUX_AON_INTR2_CPU_STATUS_BICAP_FIFO_INACT_INTR_DEFAULT 0x00000000

/* UPG_AUX_AON_INTR2 :: CPU_STATUS :: BICAP_TIMEOUT3_INTR [03:03] */
#define BCHP_UPG_AUX_AON_INTR2_CPU_STATUS_BICAP_TIMEOUT3_INTR_MASK 0x00000008
#define BCHP_UPG_AUX_AON_INTR2_CPU_STATUS_BICAP_TIMEOUT3_INTR_SHIFT 3
#define BCHP_UPG_AUX_AON_INTR2_CPU_STATUS_BICAP_TIMEOUT3_INTR_DEFAULT 0x00000000

/* UPG_AUX_AON_INTR2 :: CPU_STATUS :: BICAP_TIMEOUT2_INTR [02:02] */
#define BCHP_UPG_AUX_AON_INTR2_CPU_STATUS_BICAP_TIMEOUT2_INTR_MASK 0x00000004
#define BCHP_UPG_AUX_AON_INTR2_CPU_STATUS_BICAP_TIMEOUT2_INTR_SHIFT 2
#define BCHP_UPG_AUX_AON_INTR2_CPU_STATUS_BICAP_TIMEOUT2_INTR_DEFAULT 0x00000000

/* UPG_AUX_AON_INTR2 :: CPU_STATUS :: BICAP_TIMEOUT1_INTR [01:01] */
#define BCHP_UPG_AUX_AON_INTR2_CPU_STATUS_BICAP_TIMEOUT1_INTR_MASK 0x00000002
#define BCHP_UPG_AUX_AON_INTR2_CPU_STATUS_BICAP_TIMEOUT1_INTR_SHIFT 1
#define BCHP_UPG_AUX_AON_INTR2_CPU_STATUS_BICAP_TIMEOUT1_INTR_DEFAULT 0x00000000

/* UPG_AUX_AON_INTR2 :: CPU_STATUS :: BICAP_TIMEOUT0_INTR [00:00] */
#define BCHP_UPG_AUX_AON_INTR2_CPU_STATUS_BICAP_TIMEOUT0_INTR_MASK 0x00000001
#define BCHP_UPG_AUX_AON_INTR2_CPU_STATUS_BICAP_TIMEOUT0_INTR_SHIFT 0
#define BCHP_UPG_AUX_AON_INTR2_CPU_STATUS_BICAP_TIMEOUT0_INTR_DEFAULT 0x00000000

/***************************************************************************
 *CPU_SET - CPU interrupt Set Register
 ***************************************************************************/
/* UPG_AUX_AON_INTR2 :: CPU_SET :: reserved0 [31:09] */
#define BCHP_UPG_AUX_AON_INTR2_CPU_SET_reserved0_MASK              0xfffffe00
#define BCHP_UPG_AUX_AON_INTR2_CPU_SET_reserved0_SHIFT             9

/* UPG_AUX_AON_INTR2 :: CPU_SET :: WKTMR_ALARM_INTR [08:08] */
#define BCHP_UPG_AUX_AON_INTR2_CPU_SET_WKTMR_ALARM_INTR_MASK       0x00000100
#define BCHP_UPG_AUX_AON_INTR2_CPU_SET_WKTMR_ALARM_INTR_SHIFT      8
#define BCHP_UPG_AUX_AON_INTR2_CPU_SET_WKTMR_ALARM_INTR_DEFAULT    0x00000000

/* UPG_AUX_AON_INTR2 :: CPU_SET :: reserved_for_eco1 [07:07] */
#define BCHP_UPG_AUX_AON_INTR2_CPU_SET_reserved_for_eco1_MASK      0x00000080
#define BCHP_UPG_AUX_AON_INTR2_CPU_SET_reserved_for_eco1_SHIFT     7
#define BCHP_UPG_AUX_AON_INTR2_CPU_SET_reserved_for_eco1_DEFAULT   0x00000000

/* UPG_AUX_AON_INTR2 :: CPU_SET :: BICAP_FIFO_OF_INTR [06:06] */
#define BCHP_UPG_AUX_AON_INTR2_CPU_SET_BICAP_FIFO_OF_INTR_MASK     0x00000040
#define BCHP_UPG_AUX_AON_INTR2_CPU_SET_BICAP_FIFO_OF_INTR_SHIFT    6
#define BCHP_UPG_AUX_AON_INTR2_CPU_SET_BICAP_FIFO_OF_INTR_DEFAULT  0x00000000

/* UPG_AUX_AON_INTR2 :: CPU_SET :: BICAP_FIFO_LVL_INTR [05:05] */
#define BCHP_UPG_AUX_AON_INTR2_CPU_SET_BICAP_FIFO_LVL_INTR_MASK    0x00000020
#define BCHP_UPG_AUX_AON_INTR2_CPU_SET_BICAP_FIFO_LVL_INTR_SHIFT   5
#define BCHP_UPG_AUX_AON_INTR2_CPU_SET_BICAP_FIFO_LVL_INTR_DEFAULT 0x00000000

/* UPG_AUX_AON_INTR2 :: CPU_SET :: BICAP_FIFO_INACT_INTR [04:04] */
#define BCHP_UPG_AUX_AON_INTR2_CPU_SET_BICAP_FIFO_INACT_INTR_MASK  0x00000010
#define BCHP_UPG_AUX_AON_INTR2_CPU_SET_BICAP_FIFO_INACT_INTR_SHIFT 4
#define BCHP_UPG_AUX_AON_INTR2_CPU_SET_BICAP_FIFO_INACT_INTR_DEFAULT 0x00000000

/* UPG_AUX_AON_INTR2 :: CPU_SET :: BICAP_TIMEOUT3_INTR [03:03] */
#define BCHP_UPG_AUX_AON_INTR2_CPU_SET_BICAP_TIMEOUT3_INTR_MASK    0x00000008
#define BCHP_UPG_AUX_AON_INTR2_CPU_SET_BICAP_TIMEOUT3_INTR_SHIFT   3
#define BCHP_UPG_AUX_AON_INTR2_CPU_SET_BICAP_TIMEOUT3_INTR_DEFAULT 0x00000000

/* UPG_AUX_AON_INTR2 :: CPU_SET :: BICAP_TIMEOUT2_INTR [02:02] */
#define BCHP_UPG_AUX_AON_INTR2_CPU_SET_BICAP_TIMEOUT2_INTR_MASK    0x00000004
#define BCHP_UPG_AUX_AON_INTR2_CPU_SET_BICAP_TIMEOUT2_INTR_SHIFT   2
#define BCHP_UPG_AUX_AON_INTR2_CPU_SET_BICAP_TIMEOUT2_INTR_DEFAULT 0x00000000

/* UPG_AUX_AON_INTR2 :: CPU_SET :: BICAP_TIMEOUT1_INTR [01:01] */
#define BCHP_UPG_AUX_AON_INTR2_CPU_SET_BICAP_TIMEOUT1_INTR_MASK    0x00000002
#define BCHP_UPG_AUX_AON_INTR2_CPU_SET_BICAP_TIMEOUT1_INTR_SHIFT   1
#define BCHP_UPG_AUX_AON_INTR2_CPU_SET_BICAP_TIMEOUT1_INTR_DEFAULT 0x00000000

/* UPG_AUX_AON_INTR2 :: CPU_SET :: BICAP_TIMEOUT0_INTR [00:00] */
#define BCHP_UPG_AUX_AON_INTR2_CPU_SET_BICAP_TIMEOUT0_INTR_MASK    0x00000001
#define BCHP_UPG_AUX_AON_INTR2_CPU_SET_BICAP_TIMEOUT0_INTR_SHIFT   0
#define BCHP_UPG_AUX_AON_INTR2_CPU_SET_BICAP_TIMEOUT0_INTR_DEFAULT 0x00000000

/***************************************************************************
 *CPU_CLEAR - CPU interrupt Clear Register
 ***************************************************************************/
/* UPG_AUX_AON_INTR2 :: CPU_CLEAR :: reserved0 [31:09] */
#define BCHP_UPG_AUX_AON_INTR2_CPU_CLEAR_reserved0_MASK            0xfffffe00
#define BCHP_UPG_AUX_AON_INTR2_CPU_CLEAR_reserved0_SHIFT           9

/* UPG_AUX_AON_INTR2 :: CPU_CLEAR :: WKTMR_ALARM_INTR [08:08] */
#define BCHP_UPG_AUX_AON_INTR2_CPU_CLEAR_WKTMR_ALARM_INTR_MASK     0x00000100
#define BCHP_UPG_AUX_AON_INTR2_CPU_CLEAR_WKTMR_ALARM_INTR_SHIFT    8
#define BCHP_UPG_AUX_AON_INTR2_CPU_CLEAR_WKTMR_ALARM_INTR_DEFAULT  0x00000000

/* UPG_AUX_AON_INTR2 :: CPU_CLEAR :: reserved_for_eco1 [07:07] */
#define BCHP_UPG_AUX_AON_INTR2_CPU_CLEAR_reserved_for_eco1_MASK    0x00000080
#define BCHP_UPG_AUX_AON_INTR2_CPU_CLEAR_reserved_for_eco1_SHIFT   7
#define BCHP_UPG_AUX_AON_INTR2_CPU_CLEAR_reserved_for_eco1_DEFAULT 0x00000000

/* UPG_AUX_AON_INTR2 :: CPU_CLEAR :: BICAP_FIFO_OF_INTR [06:06] */
#define BCHP_UPG_AUX_AON_INTR2_CPU_CLEAR_BICAP_FIFO_OF_INTR_MASK   0x00000040
#define BCHP_UPG_AUX_AON_INTR2_CPU_CLEAR_BICAP_FIFO_OF_INTR_SHIFT  6
#define BCHP_UPG_AUX_AON_INTR2_CPU_CLEAR_BICAP_FIFO_OF_INTR_DEFAULT 0x00000000

/* UPG_AUX_AON_INTR2 :: CPU_CLEAR :: BICAP_FIFO_LVL_INTR [05:05] */
#define BCHP_UPG_AUX_AON_INTR2_CPU_CLEAR_BICAP_FIFO_LVL_INTR_MASK  0x00000020
#define BCHP_UPG_AUX_AON_INTR2_CPU_CLEAR_BICAP_FIFO_LVL_INTR_SHIFT 5
#define BCHP_UPG_AUX_AON_INTR2_CPU_CLEAR_BICAP_FIFO_LVL_INTR_DEFAULT 0x00000000

/* UPG_AUX_AON_INTR2 :: CPU_CLEAR :: BICAP_FIFO_INACT_INTR [04:04] */
#define BCHP_UPG_AUX_AON_INTR2_CPU_CLEAR_BICAP_FIFO_INACT_INTR_MASK 0x00000010
#define BCHP_UPG_AUX_AON_INTR2_CPU_CLEAR_BICAP_FIFO_INACT_INTR_SHIFT 4
#define BCHP_UPG_AUX_AON_INTR2_CPU_CLEAR_BICAP_FIFO_INACT_INTR_DEFAULT 0x00000000

/* UPG_AUX_AON_INTR2 :: CPU_CLEAR :: BICAP_TIMEOUT3_INTR [03:03] */
#define BCHP_UPG_AUX_AON_INTR2_CPU_CLEAR_BICAP_TIMEOUT3_INTR_MASK  0x00000008
#define BCHP_UPG_AUX_AON_INTR2_CPU_CLEAR_BICAP_TIMEOUT3_INTR_SHIFT 3
#define BCHP_UPG_AUX_AON_INTR2_CPU_CLEAR_BICAP_TIMEOUT3_INTR_DEFAULT 0x00000000

/* UPG_AUX_AON_INTR2 :: CPU_CLEAR :: BICAP_TIMEOUT2_INTR [02:02] */
#define BCHP_UPG_AUX_AON_INTR2_CPU_CLEAR_BICAP_TIMEOUT2_INTR_MASK  0x00000004
#define BCHP_UPG_AUX_AON_INTR2_CPU_CLEAR_BICAP_TIMEOUT2_INTR_SHIFT 2
#define BCHP_UPG_AUX_AON_INTR2_CPU_CLEAR_BICAP_TIMEOUT2_INTR_DEFAULT 0x00000000

/* UPG_AUX_AON_INTR2 :: CPU_CLEAR :: BICAP_TIMEOUT1_INTR [01:01] */
#define BCHP_UPG_AUX_AON_INTR2_CPU_CLEAR_BICAP_TIMEOUT1_INTR_MASK  0x00000002
#define BCHP_UPG_AUX_AON_INTR2_CPU_CLEAR_BICAP_TIMEOUT1_INTR_SHIFT 1
#define BCHP_UPG_AUX_AON_INTR2_CPU_CLEAR_BICAP_TIMEOUT1_INTR_DEFAULT 0x00000000

/* UPG_AUX_AON_INTR2 :: CPU_CLEAR :: BICAP_TIMEOUT0_INTR [00:00] */
#define BCHP_UPG_AUX_AON_INTR2_CPU_CLEAR_BICAP_TIMEOUT0_INTR_MASK  0x00000001
#define BCHP_UPG_AUX_AON_INTR2_CPU_CLEAR_BICAP_TIMEOUT0_INTR_SHIFT 0
#define BCHP_UPG_AUX_AON_INTR2_CPU_CLEAR_BICAP_TIMEOUT0_INTR_DEFAULT 0x00000000

/***************************************************************************
 *CPU_MASK_STATUS - CPU interrupt Mask Status Register
 ***************************************************************************/
/* UPG_AUX_AON_INTR2 :: CPU_MASK_STATUS :: reserved0 [31:09] */
#define BCHP_UPG_AUX_AON_INTR2_CPU_MASK_STATUS_reserved0_MASK      0xfffffe00
#define BCHP_UPG_AUX_AON_INTR2_CPU_MASK_STATUS_reserved0_SHIFT     9

/* UPG_AUX_AON_INTR2 :: CPU_MASK_STATUS :: WKTMR_ALARM_INTR [08:08] */
#define BCHP_UPG_AUX_AON_INTR2_CPU_MASK_STATUS_WKTMR_ALARM_INTR_MASK 0x00000100
#define BCHP_UPG_AUX_AON_INTR2_CPU_MASK_STATUS_WKTMR_ALARM_INTR_SHIFT 8
#define BCHP_UPG_AUX_AON_INTR2_CPU_MASK_STATUS_WKTMR_ALARM_INTR_DEFAULT 0x00000001

/* UPG_AUX_AON_INTR2 :: CPU_MASK_STATUS :: reserved_for_eco1 [07:07] */
#define BCHP_UPG_AUX_AON_INTR2_CPU_MASK_STATUS_reserved_for_eco1_MASK 0x00000080
#define BCHP_UPG_AUX_AON_INTR2_CPU_MASK_STATUS_reserved_for_eco1_SHIFT 7
#define BCHP_UPG_AUX_AON_INTR2_CPU_MASK_STATUS_reserved_for_eco1_DEFAULT 0x00000000

/* UPG_AUX_AON_INTR2 :: CPU_MASK_STATUS :: BICAP_FIFO_OF_INTR [06:06] */
#define BCHP_UPG_AUX_AON_INTR2_CPU_MASK_STATUS_BICAP_FIFO_OF_INTR_MASK 0x00000040
#define BCHP_UPG_AUX_AON_INTR2_CPU_MASK_STATUS_BICAP_FIFO_OF_INTR_SHIFT 6
#define BCHP_UPG_AUX_AON_INTR2_CPU_MASK_STATUS_BICAP_FIFO_OF_INTR_DEFAULT 0x00000001

/* UPG_AUX_AON_INTR2 :: CPU_MASK_STATUS :: BICAP_FIFO_IRQ_INTR [05:05] */
#define BCHP_UPG_AUX_AON_INTR2_CPU_MASK_STATUS_BICAP_FIFO_IRQ_INTR_MASK 0x00000020
#define BCHP_UPG_AUX_AON_INTR2_CPU_MASK_STATUS_BICAP_FIFO_IRQ_INTR_SHIFT 5
#define BCHP_UPG_AUX_AON_INTR2_CPU_MASK_STATUS_BICAP_FIFO_IRQ_INTR_DEFAULT 0x00000001

/* UPG_AUX_AON_INTR2 :: CPU_MASK_STATUS :: BICAP_CPU_TIMEOUT_INTR [04:04] */
#define BCHP_UPG_AUX_AON_INTR2_CPU_MASK_STATUS_BICAP_CPU_TIMEOUT_INTR_MASK 0x00000010
#define BCHP_UPG_AUX_AON_INTR2_CPU_MASK_STATUS_BICAP_CPU_TIMEOUT_INTR_SHIFT 4
#define BCHP_UPG_AUX_AON_INTR2_CPU_MASK_STATUS_BICAP_CPU_TIMEOUT_INTR_DEFAULT 0x00000001

/* UPG_AUX_AON_INTR2 :: CPU_MASK_STATUS :: BICAP_EDGE_TIMEOUT_INTR [03:00] */
#define BCHP_UPG_AUX_AON_INTR2_CPU_MASK_STATUS_BICAP_EDGE_TIMEOUT_INTR_MASK 0x0000000f
#define BCHP_UPG_AUX_AON_INTR2_CPU_MASK_STATUS_BICAP_EDGE_TIMEOUT_INTR_SHIFT 0
#define BCHP_UPG_AUX_AON_INTR2_CPU_MASK_STATUS_BICAP_EDGE_TIMEOUT_INTR_DEFAULT 0x00000001

/***************************************************************************
 *CPU_MASK_SET - CPU interrupt Mask Set Register
 ***************************************************************************/
/* UPG_AUX_AON_INTR2 :: CPU_MASK_SET :: reserved0 [31:09] */
#define BCHP_UPG_AUX_AON_INTR2_CPU_MASK_SET_reserved0_MASK         0xfffffe00
#define BCHP_UPG_AUX_AON_INTR2_CPU_MASK_SET_reserved0_SHIFT        9

/* UPG_AUX_AON_INTR2 :: CPU_MASK_SET :: WKTMR_ALARM_INTR [08:08] */
#define BCHP_UPG_AUX_AON_INTR2_CPU_MASK_SET_WKTMR_ALARM_INTR_MASK  0x00000100
#define BCHP_UPG_AUX_AON_INTR2_CPU_MASK_SET_WKTMR_ALARM_INTR_SHIFT 8
#define BCHP_UPG_AUX_AON_INTR2_CPU_MASK_SET_WKTMR_ALARM_INTR_DEFAULT 0x00000001

/* UPG_AUX_AON_INTR2 :: CPU_MASK_SET :: reserved_for_eco1 [07:07] */
#define BCHP_UPG_AUX_AON_INTR2_CPU_MASK_SET_reserved_for_eco1_MASK 0x00000080
#define BCHP_UPG_AUX_AON_INTR2_CPU_MASK_SET_reserved_for_eco1_SHIFT 7
#define BCHP_UPG_AUX_AON_INTR2_CPU_MASK_SET_reserved_for_eco1_DEFAULT 0x00000000

/* UPG_AUX_AON_INTR2 :: CPU_MASK_SET :: BICAP_FIFO_OF_INTR [06:06] */
#define BCHP_UPG_AUX_AON_INTR2_CPU_MASK_SET_BICAP_FIFO_OF_INTR_MASK 0x00000040
#define BCHP_UPG_AUX_AON_INTR2_CPU_MASK_SET_BICAP_FIFO_OF_INTR_SHIFT 6
#define BCHP_UPG_AUX_AON_INTR2_CPU_MASK_SET_BICAP_FIFO_OF_INTR_DEFAULT 0x00000001

/* UPG_AUX_AON_INTR2 :: CPU_MASK_SET :: BICAP_FIFO_IRQ_INTR [05:05] */
#define BCHP_UPG_AUX_AON_INTR2_CPU_MASK_SET_BICAP_FIFO_IRQ_INTR_MASK 0x00000020
#define BCHP_UPG_AUX_AON_INTR2_CPU_MASK_SET_BICAP_FIFO_IRQ_INTR_SHIFT 5
#define BCHP_UPG_AUX_AON_INTR2_CPU_MASK_SET_BICAP_FIFO_IRQ_INTR_DEFAULT 0x00000001

/* UPG_AUX_AON_INTR2 :: CPU_MASK_SET :: BICAP_CPU_TIMEOUT_INTR [04:04] */
#define BCHP_UPG_AUX_AON_INTR2_CPU_MASK_SET_BICAP_CPU_TIMEOUT_INTR_MASK 0x00000010
#define BCHP_UPG_AUX_AON_INTR2_CPU_MASK_SET_BICAP_CPU_TIMEOUT_INTR_SHIFT 4
#define BCHP_UPG_AUX_AON_INTR2_CPU_MASK_SET_BICAP_CPU_TIMEOUT_INTR_DEFAULT 0x00000001

/* UPG_AUX_AON_INTR2 :: CPU_MASK_SET :: BICAP_EDGE_TIMEOUT_INTR [03:00] */
#define BCHP_UPG_AUX_AON_INTR2_CPU_MASK_SET_BICAP_EDGE_TIMEOUT_INTR_MASK 0x0000000f
#define BCHP_UPG_AUX_AON_INTR2_CPU_MASK_SET_BICAP_EDGE_TIMEOUT_INTR_SHIFT 0
#define BCHP_UPG_AUX_AON_INTR2_CPU_MASK_SET_BICAP_EDGE_TIMEOUT_INTR_DEFAULT 0x00000001

/***************************************************************************
 *CPU_MASK_CLEAR - CPU interrupt Mask Clear Register
 ***************************************************************************/
/* UPG_AUX_AON_INTR2 :: CPU_MASK_CLEAR :: reserved0 [31:09] */
#define BCHP_UPG_AUX_AON_INTR2_CPU_MASK_CLEAR_reserved0_MASK       0xfffffe00
#define BCHP_UPG_AUX_AON_INTR2_CPU_MASK_CLEAR_reserved0_SHIFT      9

/* UPG_AUX_AON_INTR2 :: CPU_MASK_CLEAR :: WKTMR_ALARM_INTR [08:08] */
#define BCHP_UPG_AUX_AON_INTR2_CPU_MASK_CLEAR_WKTMR_ALARM_INTR_MASK 0x00000100
#define BCHP_UPG_AUX_AON_INTR2_CPU_MASK_CLEAR_WKTMR_ALARM_INTR_SHIFT 8
#define BCHP_UPG_AUX_AON_INTR2_CPU_MASK_CLEAR_WKTMR_ALARM_INTR_DEFAULT 0x00000001

/* UPG_AUX_AON_INTR2 :: CPU_MASK_CLEAR :: reserved_for_eco1 [07:07] */
#define BCHP_UPG_AUX_AON_INTR2_CPU_MASK_CLEAR_reserved_for_eco1_MASK 0x00000080
#define BCHP_UPG_AUX_AON_INTR2_CPU_MASK_CLEAR_reserved_for_eco1_SHIFT 7
#define BCHP_UPG_AUX_AON_INTR2_CPU_MASK_CLEAR_reserved_for_eco1_DEFAULT 0x00000000

/* UPG_AUX_AON_INTR2 :: CPU_MASK_CLEAR :: BICAP_FIFO_OF_INTR [06:06] */
#define BCHP_UPG_AUX_AON_INTR2_CPU_MASK_CLEAR_BICAP_FIFO_OF_INTR_MASK 0x00000040
#define BCHP_UPG_AUX_AON_INTR2_CPU_MASK_CLEAR_BICAP_FIFO_OF_INTR_SHIFT 6
#define BCHP_UPG_AUX_AON_INTR2_CPU_MASK_CLEAR_BICAP_FIFO_OF_INTR_DEFAULT 0x00000001

/* UPG_AUX_AON_INTR2 :: CPU_MASK_CLEAR :: BICAP_FIFO_IRQ_INTR [05:05] */
#define BCHP_UPG_AUX_AON_INTR2_CPU_MASK_CLEAR_BICAP_FIFO_IRQ_INTR_MASK 0x00000020
#define BCHP_UPG_AUX_AON_INTR2_CPU_MASK_CLEAR_BICAP_FIFO_IRQ_INTR_SHIFT 5
#define BCHP_UPG_AUX_AON_INTR2_CPU_MASK_CLEAR_BICAP_FIFO_IRQ_INTR_DEFAULT 0x00000001

/* UPG_AUX_AON_INTR2 :: CPU_MASK_CLEAR :: BICAP_CPU_TIMEOUT_INTR [04:04] */
#define BCHP_UPG_AUX_AON_INTR2_CPU_MASK_CLEAR_BICAP_CPU_TIMEOUT_INTR_MASK 0x00000010
#define BCHP_UPG_AUX_AON_INTR2_CPU_MASK_CLEAR_BICAP_CPU_TIMEOUT_INTR_SHIFT 4
#define BCHP_UPG_AUX_AON_INTR2_CPU_MASK_CLEAR_BICAP_CPU_TIMEOUT_INTR_DEFAULT 0x00000001

/* UPG_AUX_AON_INTR2 :: CPU_MASK_CLEAR :: BICAP_EDGE_TIMEOUT_INTR [03:00] */
#define BCHP_UPG_AUX_AON_INTR2_CPU_MASK_CLEAR_BICAP_EDGE_TIMEOUT_INTR_MASK 0x0000000f
#define BCHP_UPG_AUX_AON_INTR2_CPU_MASK_CLEAR_BICAP_EDGE_TIMEOUT_INTR_SHIFT 0
#define BCHP_UPG_AUX_AON_INTR2_CPU_MASK_CLEAR_BICAP_EDGE_TIMEOUT_INTR_DEFAULT 0x00000001

/***************************************************************************
 *PCI_STATUS - PCI interrupt Status Register
 ***************************************************************************/
/* UPG_AUX_AON_INTR2 :: PCI_STATUS :: reserved0 [31:09] */
#define BCHP_UPG_AUX_AON_INTR2_PCI_STATUS_reserved0_MASK           0xfffffe00
#define BCHP_UPG_AUX_AON_INTR2_PCI_STATUS_reserved0_SHIFT          9

/* UPG_AUX_AON_INTR2 :: PCI_STATUS :: WKTMR_ALARM_INTR [08:08] */
#define BCHP_UPG_AUX_AON_INTR2_PCI_STATUS_WKTMR_ALARM_INTR_MASK    0x00000100
#define BCHP_UPG_AUX_AON_INTR2_PCI_STATUS_WKTMR_ALARM_INTR_SHIFT   8
#define BCHP_UPG_AUX_AON_INTR2_PCI_STATUS_WKTMR_ALARM_INTR_DEFAULT 0x00000000

/* UPG_AUX_AON_INTR2 :: PCI_STATUS :: reserved_for_eco1 [07:07] */
#define BCHP_UPG_AUX_AON_INTR2_PCI_STATUS_reserved_for_eco1_MASK   0x00000080
#define BCHP_UPG_AUX_AON_INTR2_PCI_STATUS_reserved_for_eco1_SHIFT  7
#define BCHP_UPG_AUX_AON_INTR2_PCI_STATUS_reserved_for_eco1_DEFAULT 0x00000000

/* UPG_AUX_AON_INTR2 :: PCI_STATUS :: BICAP_FIFO_OF_INTR [06:06] */
#define BCHP_UPG_AUX_AON_INTR2_PCI_STATUS_BICAP_FIFO_OF_INTR_MASK  0x00000040
#define BCHP_UPG_AUX_AON_INTR2_PCI_STATUS_BICAP_FIFO_OF_INTR_SHIFT 6
#define BCHP_UPG_AUX_AON_INTR2_PCI_STATUS_BICAP_FIFO_OF_INTR_DEFAULT 0x00000000

/* UPG_AUX_AON_INTR2 :: PCI_STATUS :: BICAP_FIFO_LVL_INTR [05:05] */
#define BCHP_UPG_AUX_AON_INTR2_PCI_STATUS_BICAP_FIFO_LVL_INTR_MASK 0x00000020
#define BCHP_UPG_AUX_AON_INTR2_PCI_STATUS_BICAP_FIFO_LVL_INTR_SHIFT 5
#define BCHP_UPG_AUX_AON_INTR2_PCI_STATUS_BICAP_FIFO_LVL_INTR_DEFAULT 0x00000000

/* UPG_AUX_AON_INTR2 :: PCI_STATUS :: BICAP_FIFO_INACT_INTR [04:04] */
#define BCHP_UPG_AUX_AON_INTR2_PCI_STATUS_BICAP_FIFO_INACT_INTR_MASK 0x00000010
#define BCHP_UPG_AUX_AON_INTR2_PCI_STATUS_BICAP_FIFO_INACT_INTR_SHIFT 4
#define BCHP_UPG_AUX_AON_INTR2_PCI_STATUS_BICAP_FIFO_INACT_INTR_DEFAULT 0x00000000

/* UPG_AUX_AON_INTR2 :: PCI_STATUS :: BICAP_TIMEOUT3_INTR [03:03] */
#define BCHP_UPG_AUX_AON_INTR2_PCI_STATUS_BICAP_TIMEOUT3_INTR_MASK 0x00000008
#define BCHP_UPG_AUX_AON_INTR2_PCI_STATUS_BICAP_TIMEOUT3_INTR_SHIFT 3
#define BCHP_UPG_AUX_AON_INTR2_PCI_STATUS_BICAP_TIMEOUT3_INTR_DEFAULT 0x00000000

/* UPG_AUX_AON_INTR2 :: PCI_STATUS :: BICAP_TIMEOUT2_INTR [02:02] */
#define BCHP_UPG_AUX_AON_INTR2_PCI_STATUS_BICAP_TIMEOUT2_INTR_MASK 0x00000004
#define BCHP_UPG_AUX_AON_INTR2_PCI_STATUS_BICAP_TIMEOUT2_INTR_SHIFT 2
#define BCHP_UPG_AUX_AON_INTR2_PCI_STATUS_BICAP_TIMEOUT2_INTR_DEFAULT 0x00000000

/* UPG_AUX_AON_INTR2 :: PCI_STATUS :: BICAP_TIMEOUT1_INTR [01:01] */
#define BCHP_UPG_AUX_AON_INTR2_PCI_STATUS_BICAP_TIMEOUT1_INTR_MASK 0x00000002
#define BCHP_UPG_AUX_AON_INTR2_PCI_STATUS_BICAP_TIMEOUT1_INTR_SHIFT 1
#define BCHP_UPG_AUX_AON_INTR2_PCI_STATUS_BICAP_TIMEOUT1_INTR_DEFAULT 0x00000000

/* UPG_AUX_AON_INTR2 :: PCI_STATUS :: BICAP_TIMEOUT0_INTR [00:00] */
#define BCHP_UPG_AUX_AON_INTR2_PCI_STATUS_BICAP_TIMEOUT0_INTR_MASK 0x00000001
#define BCHP_UPG_AUX_AON_INTR2_PCI_STATUS_BICAP_TIMEOUT0_INTR_SHIFT 0
#define BCHP_UPG_AUX_AON_INTR2_PCI_STATUS_BICAP_TIMEOUT0_INTR_DEFAULT 0x00000000

/***************************************************************************
 *PCI_SET - PCI interrupt Set Register
 ***************************************************************************/
/* UPG_AUX_AON_INTR2 :: PCI_SET :: reserved0 [31:09] */
#define BCHP_UPG_AUX_AON_INTR2_PCI_SET_reserved0_MASK              0xfffffe00
#define BCHP_UPG_AUX_AON_INTR2_PCI_SET_reserved0_SHIFT             9

/* UPG_AUX_AON_INTR2 :: PCI_SET :: WKTMR_ALARM_INTR [08:08] */
#define BCHP_UPG_AUX_AON_INTR2_PCI_SET_WKTMR_ALARM_INTR_MASK       0x00000100
#define BCHP_UPG_AUX_AON_INTR2_PCI_SET_WKTMR_ALARM_INTR_SHIFT      8
#define BCHP_UPG_AUX_AON_INTR2_PCI_SET_WKTMR_ALARM_INTR_DEFAULT    0x00000000

/* UPG_AUX_AON_INTR2 :: PCI_SET :: reserved_for_eco1 [07:07] */
#define BCHP_UPG_AUX_AON_INTR2_PCI_SET_reserved_for_eco1_MASK      0x00000080
#define BCHP_UPG_AUX_AON_INTR2_PCI_SET_reserved_for_eco1_SHIFT     7
#define BCHP_UPG_AUX_AON_INTR2_PCI_SET_reserved_for_eco1_DEFAULT   0x00000000

/* UPG_AUX_AON_INTR2 :: PCI_SET :: BICAP_FIFO_OF_INTR [06:06] */
#define BCHP_UPG_AUX_AON_INTR2_PCI_SET_BICAP_FIFO_OF_INTR_MASK     0x00000040
#define BCHP_UPG_AUX_AON_INTR2_PCI_SET_BICAP_FIFO_OF_INTR_SHIFT    6
#define BCHP_UPG_AUX_AON_INTR2_PCI_SET_BICAP_FIFO_OF_INTR_DEFAULT  0x00000000

/* UPG_AUX_AON_INTR2 :: PCI_SET :: BICAP_FIFO_LVL_INTR [05:05] */
#define BCHP_UPG_AUX_AON_INTR2_PCI_SET_BICAP_FIFO_LVL_INTR_MASK    0x00000020
#define BCHP_UPG_AUX_AON_INTR2_PCI_SET_BICAP_FIFO_LVL_INTR_SHIFT   5
#define BCHP_UPG_AUX_AON_INTR2_PCI_SET_BICAP_FIFO_LVL_INTR_DEFAULT 0x00000000

/* UPG_AUX_AON_INTR2 :: PCI_SET :: BICAP_FIFO_INACT_INTR [04:04] */
#define BCHP_UPG_AUX_AON_INTR2_PCI_SET_BICAP_FIFO_INACT_INTR_MASK  0x00000010
#define BCHP_UPG_AUX_AON_INTR2_PCI_SET_BICAP_FIFO_INACT_INTR_SHIFT 4
#define BCHP_UPG_AUX_AON_INTR2_PCI_SET_BICAP_FIFO_INACT_INTR_DEFAULT 0x00000000

/* UPG_AUX_AON_INTR2 :: PCI_SET :: BICAP_TIMEOUT3_INTR [03:03] */
#define BCHP_UPG_AUX_AON_INTR2_PCI_SET_BICAP_TIMEOUT3_INTR_MASK    0x00000008
#define BCHP_UPG_AUX_AON_INTR2_PCI_SET_BICAP_TIMEOUT3_INTR_SHIFT   3
#define BCHP_UPG_AUX_AON_INTR2_PCI_SET_BICAP_TIMEOUT3_INTR_DEFAULT 0x00000000

/* UPG_AUX_AON_INTR2 :: PCI_SET :: BICAP_TIMEOUT2_INTR [02:02] */
#define BCHP_UPG_AUX_AON_INTR2_PCI_SET_BICAP_TIMEOUT2_INTR_MASK    0x00000004
#define BCHP_UPG_AUX_AON_INTR2_PCI_SET_BICAP_TIMEOUT2_INTR_SHIFT   2
#define BCHP_UPG_AUX_AON_INTR2_PCI_SET_BICAP_TIMEOUT2_INTR_DEFAULT 0x00000000

/* UPG_AUX_AON_INTR2 :: PCI_SET :: BICAP_TIMEOUT1_INTR [01:01] */
#define BCHP_UPG_AUX_AON_INTR2_PCI_SET_BICAP_TIMEOUT1_INTR_MASK    0x00000002
#define BCHP_UPG_AUX_AON_INTR2_PCI_SET_BICAP_TIMEOUT1_INTR_SHIFT   1
#define BCHP_UPG_AUX_AON_INTR2_PCI_SET_BICAP_TIMEOUT1_INTR_DEFAULT 0x00000000

/* UPG_AUX_AON_INTR2 :: PCI_SET :: BICAP_TIMEOUT0_INTR [00:00] */
#define BCHP_UPG_AUX_AON_INTR2_PCI_SET_BICAP_TIMEOUT0_INTR_MASK    0x00000001
#define BCHP_UPG_AUX_AON_INTR2_PCI_SET_BICAP_TIMEOUT0_INTR_SHIFT   0
#define BCHP_UPG_AUX_AON_INTR2_PCI_SET_BICAP_TIMEOUT0_INTR_DEFAULT 0x00000000

/***************************************************************************
 *PCI_CLEAR - PCI interrupt Clear Register
 ***************************************************************************/
/* UPG_AUX_AON_INTR2 :: PCI_CLEAR :: reserved0 [31:09] */
#define BCHP_UPG_AUX_AON_INTR2_PCI_CLEAR_reserved0_MASK            0xfffffe00
#define BCHP_UPG_AUX_AON_INTR2_PCI_CLEAR_reserved0_SHIFT           9

/* UPG_AUX_AON_INTR2 :: PCI_CLEAR :: WKTMR_ALARM_INTR [08:08] */
#define BCHP_UPG_AUX_AON_INTR2_PCI_CLEAR_WKTMR_ALARM_INTR_MASK     0x00000100
#define BCHP_UPG_AUX_AON_INTR2_PCI_CLEAR_WKTMR_ALARM_INTR_SHIFT    8
#define BCHP_UPG_AUX_AON_INTR2_PCI_CLEAR_WKTMR_ALARM_INTR_DEFAULT  0x00000000

/* UPG_AUX_AON_INTR2 :: PCI_CLEAR :: reserved_for_eco1 [07:07] */
#define BCHP_UPG_AUX_AON_INTR2_PCI_CLEAR_reserved_for_eco1_MASK    0x00000080
#define BCHP_UPG_AUX_AON_INTR2_PCI_CLEAR_reserved_for_eco1_SHIFT   7
#define BCHP_UPG_AUX_AON_INTR2_PCI_CLEAR_reserved_for_eco1_DEFAULT 0x00000000

/* UPG_AUX_AON_INTR2 :: PCI_CLEAR :: BICAP_FIFO_OF_INTR [06:06] */
#define BCHP_UPG_AUX_AON_INTR2_PCI_CLEAR_BICAP_FIFO_OF_INTR_MASK   0x00000040
#define BCHP_UPG_AUX_AON_INTR2_PCI_CLEAR_BICAP_FIFO_OF_INTR_SHIFT  6
#define BCHP_UPG_AUX_AON_INTR2_PCI_CLEAR_BICAP_FIFO_OF_INTR_DEFAULT 0x00000000

/* UPG_AUX_AON_INTR2 :: PCI_CLEAR :: BICAP_FIFO_LVL_INTR [05:05] */
#define BCHP_UPG_AUX_AON_INTR2_PCI_CLEAR_BICAP_FIFO_LVL_INTR_MASK  0x00000020
#define BCHP_UPG_AUX_AON_INTR2_PCI_CLEAR_BICAP_FIFO_LVL_INTR_SHIFT 5
#define BCHP_UPG_AUX_AON_INTR2_PCI_CLEAR_BICAP_FIFO_LVL_INTR_DEFAULT 0x00000000

/* UPG_AUX_AON_INTR2 :: PCI_CLEAR :: BICAP_FIFO_INACT_INTR [04:04] */
#define BCHP_UPG_AUX_AON_INTR2_PCI_CLEAR_BICAP_FIFO_INACT_INTR_MASK 0x00000010
#define BCHP_UPG_AUX_AON_INTR2_PCI_CLEAR_BICAP_FIFO_INACT_INTR_SHIFT 4
#define BCHP_UPG_AUX_AON_INTR2_PCI_CLEAR_BICAP_FIFO_INACT_INTR_DEFAULT 0x00000000

/* UPG_AUX_AON_INTR2 :: PCI_CLEAR :: BICAP_TIMEOUT3_INTR [03:03] */
#define BCHP_UPG_AUX_AON_INTR2_PCI_CLEAR_BICAP_TIMEOUT3_INTR_MASK  0x00000008
#define BCHP_UPG_AUX_AON_INTR2_PCI_CLEAR_BICAP_TIMEOUT3_INTR_SHIFT 3
#define BCHP_UPG_AUX_AON_INTR2_PCI_CLEAR_BICAP_TIMEOUT3_INTR_DEFAULT 0x00000000

/* UPG_AUX_AON_INTR2 :: PCI_CLEAR :: BICAP_TIMEOUT2_INTR [02:02] */
#define BCHP_UPG_AUX_AON_INTR2_PCI_CLEAR_BICAP_TIMEOUT2_INTR_MASK  0x00000004
#define BCHP_UPG_AUX_AON_INTR2_PCI_CLEAR_BICAP_TIMEOUT2_INTR_SHIFT 2
#define BCHP_UPG_AUX_AON_INTR2_PCI_CLEAR_BICAP_TIMEOUT2_INTR_DEFAULT 0x00000000

/* UPG_AUX_AON_INTR2 :: PCI_CLEAR :: BICAP_TIMEOUT1_INTR [01:01] */
#define BCHP_UPG_AUX_AON_INTR2_PCI_CLEAR_BICAP_TIMEOUT1_INTR_MASK  0x00000002
#define BCHP_UPG_AUX_AON_INTR2_PCI_CLEAR_BICAP_TIMEOUT1_INTR_SHIFT 1
#define BCHP_UPG_AUX_AON_INTR2_PCI_CLEAR_BICAP_TIMEOUT1_INTR_DEFAULT 0x00000000

/* UPG_AUX_AON_INTR2 :: PCI_CLEAR :: BICAP_TIMEOUT0_INTR [00:00] */
#define BCHP_UPG_AUX_AON_INTR2_PCI_CLEAR_BICAP_TIMEOUT0_INTR_MASK  0x00000001
#define BCHP_UPG_AUX_AON_INTR2_PCI_CLEAR_BICAP_TIMEOUT0_INTR_SHIFT 0
#define BCHP_UPG_AUX_AON_INTR2_PCI_CLEAR_BICAP_TIMEOUT0_INTR_DEFAULT 0x00000000

/***************************************************************************
 *PCI_MASK_STATUS - PCI interrupt Mask Status Register
 ***************************************************************************/
/* UPG_AUX_AON_INTR2 :: PCI_MASK_STATUS :: reserved0 [31:09] */
#define BCHP_UPG_AUX_AON_INTR2_PCI_MASK_STATUS_reserved0_MASK      0xfffffe00
#define BCHP_UPG_AUX_AON_INTR2_PCI_MASK_STATUS_reserved0_SHIFT     9

/* UPG_AUX_AON_INTR2 :: PCI_MASK_STATUS :: WKTMR_ALARM_INTR [08:08] */
#define BCHP_UPG_AUX_AON_INTR2_PCI_MASK_STATUS_WKTMR_ALARM_INTR_MASK 0x00000100
#define BCHP_UPG_AUX_AON_INTR2_PCI_MASK_STATUS_WKTMR_ALARM_INTR_SHIFT 8
#define BCHP_UPG_AUX_AON_INTR2_PCI_MASK_STATUS_WKTMR_ALARM_INTR_DEFAULT 0x00000001

/* UPG_AUX_AON_INTR2 :: PCI_MASK_STATUS :: reserved_for_eco1 [07:07] */
#define BCHP_UPG_AUX_AON_INTR2_PCI_MASK_STATUS_reserved_for_eco1_MASK 0x00000080
#define BCHP_UPG_AUX_AON_INTR2_PCI_MASK_STATUS_reserved_for_eco1_SHIFT 7
#define BCHP_UPG_AUX_AON_INTR2_PCI_MASK_STATUS_reserved_for_eco1_DEFAULT 0x00000000

/* UPG_AUX_AON_INTR2 :: PCI_MASK_STATUS :: BICAP_FIFO_OF_INTR [06:06] */
#define BCHP_UPG_AUX_AON_INTR2_PCI_MASK_STATUS_BICAP_FIFO_OF_INTR_MASK 0x00000040
#define BCHP_UPG_AUX_AON_INTR2_PCI_MASK_STATUS_BICAP_FIFO_OF_INTR_SHIFT 6
#define BCHP_UPG_AUX_AON_INTR2_PCI_MASK_STATUS_BICAP_FIFO_OF_INTR_DEFAULT 0x00000001

/* UPG_AUX_AON_INTR2 :: PCI_MASK_STATUS :: BICAP_FIFO_IRQ_INTR [05:05] */
#define BCHP_UPG_AUX_AON_INTR2_PCI_MASK_STATUS_BICAP_FIFO_IRQ_INTR_MASK 0x00000020
#define BCHP_UPG_AUX_AON_INTR2_PCI_MASK_STATUS_BICAP_FIFO_IRQ_INTR_SHIFT 5
#define BCHP_UPG_AUX_AON_INTR2_PCI_MASK_STATUS_BICAP_FIFO_IRQ_INTR_DEFAULT 0x00000001

/* UPG_AUX_AON_INTR2 :: PCI_MASK_STATUS :: BICAP_CPU_TIMEOUT_INTR [04:04] */
#define BCHP_UPG_AUX_AON_INTR2_PCI_MASK_STATUS_BICAP_CPU_TIMEOUT_INTR_MASK 0x00000010
#define BCHP_UPG_AUX_AON_INTR2_PCI_MASK_STATUS_BICAP_CPU_TIMEOUT_INTR_SHIFT 4
#define BCHP_UPG_AUX_AON_INTR2_PCI_MASK_STATUS_BICAP_CPU_TIMEOUT_INTR_DEFAULT 0x00000001

/* UPG_AUX_AON_INTR2 :: PCI_MASK_STATUS :: BICAP_EDGE_TIMEOUT_INTR [03:00] */
#define BCHP_UPG_AUX_AON_INTR2_PCI_MASK_STATUS_BICAP_EDGE_TIMEOUT_INTR_MASK 0x0000000f
#define BCHP_UPG_AUX_AON_INTR2_PCI_MASK_STATUS_BICAP_EDGE_TIMEOUT_INTR_SHIFT 0
#define BCHP_UPG_AUX_AON_INTR2_PCI_MASK_STATUS_BICAP_EDGE_TIMEOUT_INTR_DEFAULT 0x00000001

/***************************************************************************
 *PCI_MASK_SET - PCI interrupt Mask Set Register
 ***************************************************************************/
/* UPG_AUX_AON_INTR2 :: PCI_MASK_SET :: reserved0 [31:09] */
#define BCHP_UPG_AUX_AON_INTR2_PCI_MASK_SET_reserved0_MASK         0xfffffe00
#define BCHP_UPG_AUX_AON_INTR2_PCI_MASK_SET_reserved0_SHIFT        9

/* UPG_AUX_AON_INTR2 :: PCI_MASK_SET :: WKTMR_ALARM_INTR [08:08] */
#define BCHP_UPG_AUX_AON_INTR2_PCI_MASK_SET_WKTMR_ALARM_INTR_MASK  0x00000100
#define BCHP_UPG_AUX_AON_INTR2_PCI_MASK_SET_WKTMR_ALARM_INTR_SHIFT 8
#define BCHP_UPG_AUX_AON_INTR2_PCI_MASK_SET_WKTMR_ALARM_INTR_DEFAULT 0x00000001

/* UPG_AUX_AON_INTR2 :: PCI_MASK_SET :: reserved_for_eco1 [07:07] */
#define BCHP_UPG_AUX_AON_INTR2_PCI_MASK_SET_reserved_for_eco1_MASK 0x00000080
#define BCHP_UPG_AUX_AON_INTR2_PCI_MASK_SET_reserved_for_eco1_SHIFT 7
#define BCHP_UPG_AUX_AON_INTR2_PCI_MASK_SET_reserved_for_eco1_DEFAULT 0x00000000

/* UPG_AUX_AON_INTR2 :: PCI_MASK_SET :: BICAP_FIFO_OF_INTR [06:06] */
#define BCHP_UPG_AUX_AON_INTR2_PCI_MASK_SET_BICAP_FIFO_OF_INTR_MASK 0x00000040
#define BCHP_UPG_AUX_AON_INTR2_PCI_MASK_SET_BICAP_FIFO_OF_INTR_SHIFT 6
#define BCHP_UPG_AUX_AON_INTR2_PCI_MASK_SET_BICAP_FIFO_OF_INTR_DEFAULT 0x00000001

/* UPG_AUX_AON_INTR2 :: PCI_MASK_SET :: BICAP_FIFO_IRQ_INTR [05:05] */
#define BCHP_UPG_AUX_AON_INTR2_PCI_MASK_SET_BICAP_FIFO_IRQ_INTR_MASK 0x00000020
#define BCHP_UPG_AUX_AON_INTR2_PCI_MASK_SET_BICAP_FIFO_IRQ_INTR_SHIFT 5
#define BCHP_UPG_AUX_AON_INTR2_PCI_MASK_SET_BICAP_FIFO_IRQ_INTR_DEFAULT 0x00000001

/* UPG_AUX_AON_INTR2 :: PCI_MASK_SET :: BICAP_CPU_TIMEOUT_INTR [04:04] */
#define BCHP_UPG_AUX_AON_INTR2_PCI_MASK_SET_BICAP_CPU_TIMEOUT_INTR_MASK 0x00000010
#define BCHP_UPG_AUX_AON_INTR2_PCI_MASK_SET_BICAP_CPU_TIMEOUT_INTR_SHIFT 4
#define BCHP_UPG_AUX_AON_INTR2_PCI_MASK_SET_BICAP_CPU_TIMEOUT_INTR_DEFAULT 0x00000001

/* UPG_AUX_AON_INTR2 :: PCI_MASK_SET :: BICAP_EDGE_TIMEOUT_INTR [03:00] */
#define BCHP_UPG_AUX_AON_INTR2_PCI_MASK_SET_BICAP_EDGE_TIMEOUT_INTR_MASK 0x0000000f
#define BCHP_UPG_AUX_AON_INTR2_PCI_MASK_SET_BICAP_EDGE_TIMEOUT_INTR_SHIFT 0
#define BCHP_UPG_AUX_AON_INTR2_PCI_MASK_SET_BICAP_EDGE_TIMEOUT_INTR_DEFAULT 0x00000001

/***************************************************************************
 *PCI_MASK_CLEAR - PCI interrupt Mask Clear Register
 ***************************************************************************/
/* UPG_AUX_AON_INTR2 :: PCI_MASK_CLEAR :: reserved0 [31:09] */
#define BCHP_UPG_AUX_AON_INTR2_PCI_MASK_CLEAR_reserved0_MASK       0xfffffe00
#define BCHP_UPG_AUX_AON_INTR2_PCI_MASK_CLEAR_reserved0_SHIFT      9

/* UPG_AUX_AON_INTR2 :: PCI_MASK_CLEAR :: WKTMR_ALARM_INTR [08:08] */
#define BCHP_UPG_AUX_AON_INTR2_PCI_MASK_CLEAR_WKTMR_ALARM_INTR_MASK 0x00000100
#define BCHP_UPG_AUX_AON_INTR2_PCI_MASK_CLEAR_WKTMR_ALARM_INTR_SHIFT 8
#define BCHP_UPG_AUX_AON_INTR2_PCI_MASK_CLEAR_WKTMR_ALARM_INTR_DEFAULT 0x00000001

/* UPG_AUX_AON_INTR2 :: PCI_MASK_CLEAR :: reserved_for_eco1 [07:07] */
#define BCHP_UPG_AUX_AON_INTR2_PCI_MASK_CLEAR_reserved_for_eco1_MASK 0x00000080
#define BCHP_UPG_AUX_AON_INTR2_PCI_MASK_CLEAR_reserved_for_eco1_SHIFT 7
#define BCHP_UPG_AUX_AON_INTR2_PCI_MASK_CLEAR_reserved_for_eco1_DEFAULT 0x00000000

/* UPG_AUX_AON_INTR2 :: PCI_MASK_CLEAR :: BICAP_FIFO_OF_INTR [06:06] */
#define BCHP_UPG_AUX_AON_INTR2_PCI_MASK_CLEAR_BICAP_FIFO_OF_INTR_MASK 0x00000040
#define BCHP_UPG_AUX_AON_INTR2_PCI_MASK_CLEAR_BICAP_FIFO_OF_INTR_SHIFT 6
#define BCHP_UPG_AUX_AON_INTR2_PCI_MASK_CLEAR_BICAP_FIFO_OF_INTR_DEFAULT 0x00000001

/* UPG_AUX_AON_INTR2 :: PCI_MASK_CLEAR :: BICAP_FIFO_IRQ_INTR [05:05] */
#define BCHP_UPG_AUX_AON_INTR2_PCI_MASK_CLEAR_BICAP_FIFO_IRQ_INTR_MASK 0x00000020
#define BCHP_UPG_AUX_AON_INTR2_PCI_MASK_CLEAR_BICAP_FIFO_IRQ_INTR_SHIFT 5
#define BCHP_UPG_AUX_AON_INTR2_PCI_MASK_CLEAR_BICAP_FIFO_IRQ_INTR_DEFAULT 0x00000001

/* UPG_AUX_AON_INTR2 :: PCI_MASK_CLEAR :: BICAP_CPU_TIMEOUT_INTR [04:04] */
#define BCHP_UPG_AUX_AON_INTR2_PCI_MASK_CLEAR_BICAP_CPU_TIMEOUT_INTR_MASK 0x00000010
#define BCHP_UPG_AUX_AON_INTR2_PCI_MASK_CLEAR_BICAP_CPU_TIMEOUT_INTR_SHIFT 4
#define BCHP_UPG_AUX_AON_INTR2_PCI_MASK_CLEAR_BICAP_CPU_TIMEOUT_INTR_DEFAULT 0x00000001

/* UPG_AUX_AON_INTR2 :: PCI_MASK_CLEAR :: BICAP_EDGE_TIMEOUT_INTR [03:00] */
#define BCHP_UPG_AUX_AON_INTR2_PCI_MASK_CLEAR_BICAP_EDGE_TIMEOUT_INTR_MASK 0x0000000f
#define BCHP_UPG_AUX_AON_INTR2_PCI_MASK_CLEAR_BICAP_EDGE_TIMEOUT_INTR_SHIFT 0
#define BCHP_UPG_AUX_AON_INTR2_PCI_MASK_CLEAR_BICAP_EDGE_TIMEOUT_INTR_DEFAULT 0x00000001

#endif /* #ifndef BCHP_UPG_AUX_AON_INTR2_H__ */

/* End of File */

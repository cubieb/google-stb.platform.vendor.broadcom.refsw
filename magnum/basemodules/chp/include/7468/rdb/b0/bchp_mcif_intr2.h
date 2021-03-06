/***************************************************************************
 *     Copyright (c) 1999-2010, Broadcom Corporation
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
 * Date:           Generated on         Fri May  7 20:17:52 2010
 *                 MD5 Checksum         9170aeef162fecc7d1a70fbd8134c303
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

#ifndef BCHP_MCIF_INTR2_H__
#define BCHP_MCIF_INTR2_H__

/***************************************************************************
 *MCIF_INTR2 - MCIF Level 2 Interrupt Registers
 ***************************************************************************/
#define BCHP_MCIF_INTR2_CPU_STATUS               0x00307080 /* CPU interrupt Status Register */
#define BCHP_MCIF_INTR2_CPU_SET                  0x00307084 /* CPU interrupt Set Register */
#define BCHP_MCIF_INTR2_CPU_CLEAR                0x00307088 /* CPU interrupt Clear Register */
#define BCHP_MCIF_INTR2_CPU_MASK_STATUS          0x0030708c /* CPU interrupt Mask Status Register */
#define BCHP_MCIF_INTR2_CPU_MASK_SET             0x00307090 /* CPU interrupt Mask Set Register */
#define BCHP_MCIF_INTR2_CPU_MASK_CLEAR           0x00307094 /* CPU interrupt Mask Clear Register */
#define BCHP_MCIF_INTR2_PCI_STATUS               0x00307098 /* PCI interrupt Status Register */
#define BCHP_MCIF_INTR2_PCI_SET                  0x0030709c /* PCI interrupt Set Register */
#define BCHP_MCIF_INTR2_PCI_CLEAR                0x003070a0 /* PCI interrupt Clear Register */
#define BCHP_MCIF_INTR2_PCI_MASK_STATUS          0x003070a4 /* PCI interrupt Mask Status Register */
#define BCHP_MCIF_INTR2_PCI_MASK_SET             0x003070a8 /* PCI interrupt Mask Set Register */
#define BCHP_MCIF_INTR2_PCI_MASK_CLEAR           0x003070ac /* PCI interrupt Mask Clear Register */

/***************************************************************************
 *CPU_STATUS - CPU interrupt Status Register
 ***************************************************************************/
/* MCIF_INTR2 :: CPU_STATUS :: reserved0 [31:22] */
#define BCHP_MCIF_INTR2_CPU_STATUS_reserved0_MASK                  0xffc00000
#define BCHP_MCIF_INTR2_CPU_STATUS_reserved0_SHIFT                 22

/* MCIF_INTR2 :: CPU_STATUS :: WKTMR_ALARM_INTR [21:21] */
#define BCHP_MCIF_INTR2_CPU_STATUS_WKTMR_ALARM_INTR_MASK           0x00200000
#define BCHP_MCIF_INTR2_CPU_STATUS_WKTMR_ALARM_INTR_SHIFT          21

/* MCIF_INTR2 :: CPU_STATUS :: reserved1 [20:19] */
#define BCHP_MCIF_INTR2_CPU_STATUS_reserved1_MASK                  0x00180000
#define BCHP_MCIF_INTR2_CPU_STATUS_reserved1_SHIFT                 19

/* MCIF_INTR2 :: CPU_STATUS :: reserved_for_eco2 [18:18] */
#define BCHP_MCIF_INTR2_CPU_STATUS_reserved_for_eco2_MASK          0x00040000
#define BCHP_MCIF_INTR2_CPU_STATUS_reserved_for_eco2_SHIFT         18

/* MCIF_INTR2 :: CPU_STATUS :: BICAP1_FIFO_OF_INTR [17:17] */
#define BCHP_MCIF_INTR2_CPU_STATUS_BICAP1_FIFO_OF_INTR_MASK        0x00020000
#define BCHP_MCIF_INTR2_CPU_STATUS_BICAP1_FIFO_OF_INTR_SHIFT       17

/* MCIF_INTR2 :: CPU_STATUS :: BICAP1_FIFO_LVL_INTR [16:16] */
#define BCHP_MCIF_INTR2_CPU_STATUS_BICAP1_FIFO_LVL_INTR_MASK       0x00010000
#define BCHP_MCIF_INTR2_CPU_STATUS_BICAP1_FIFO_LVL_INTR_SHIFT      16

/* MCIF_INTR2 :: CPU_STATUS :: BICAP1_FIFO_INACT_INTR [15:15] */
#define BCHP_MCIF_INTR2_CPU_STATUS_BICAP1_FIFO_INACT_INTR_MASK     0x00008000
#define BCHP_MCIF_INTR2_CPU_STATUS_BICAP1_FIFO_INACT_INTR_SHIFT    15

/* MCIF_INTR2 :: CPU_STATUS :: BICAP1_TIMEOUT3_INTR [14:14] */
#define BCHP_MCIF_INTR2_CPU_STATUS_BICAP1_TIMEOUT3_INTR_MASK       0x00004000
#define BCHP_MCIF_INTR2_CPU_STATUS_BICAP1_TIMEOUT3_INTR_SHIFT      14

/* MCIF_INTR2 :: CPU_STATUS :: BICAP1_TIMEOUT2_INTR [13:13] */
#define BCHP_MCIF_INTR2_CPU_STATUS_BICAP1_TIMEOUT2_INTR_MASK       0x00002000
#define BCHP_MCIF_INTR2_CPU_STATUS_BICAP1_TIMEOUT2_INTR_SHIFT      13

/* MCIF_INTR2 :: CPU_STATUS :: BICAP1_TIMEOUT1_INTR [12:12] */
#define BCHP_MCIF_INTR2_CPU_STATUS_BICAP1_TIMEOUT1_INTR_MASK       0x00001000
#define BCHP_MCIF_INTR2_CPU_STATUS_BICAP1_TIMEOUT1_INTR_SHIFT      12

/* MCIF_INTR2 :: CPU_STATUS :: BICAP1_TIMEOUT0_INTR [11:11] */
#define BCHP_MCIF_INTR2_CPU_STATUS_BICAP1_TIMEOUT0_INTR_MASK       0x00000800
#define BCHP_MCIF_INTR2_CPU_STATUS_BICAP1_TIMEOUT0_INTR_SHIFT      11

/* MCIF_INTR2 :: CPU_STATUS :: reserved3 [10:00] */
#define BCHP_MCIF_INTR2_CPU_STATUS_reserved3_MASK                  0x000007ff
#define BCHP_MCIF_INTR2_CPU_STATUS_reserved3_SHIFT                 0

/***************************************************************************
 *CPU_SET - CPU interrupt Set Register
 ***************************************************************************/
/* MCIF_INTR2 :: CPU_SET :: reserved0 [31:22] */
#define BCHP_MCIF_INTR2_CPU_SET_reserved0_MASK                     0xffc00000
#define BCHP_MCIF_INTR2_CPU_SET_reserved0_SHIFT                    22

/* MCIF_INTR2 :: CPU_SET :: WKTMR_ALARM_INTR [21:21] */
#define BCHP_MCIF_INTR2_CPU_SET_WKTMR_ALARM_INTR_MASK              0x00200000
#define BCHP_MCIF_INTR2_CPU_SET_WKTMR_ALARM_INTR_SHIFT             21

/* MCIF_INTR2 :: CPU_SET :: reserved1 [20:19] */
#define BCHP_MCIF_INTR2_CPU_SET_reserved1_MASK                     0x00180000
#define BCHP_MCIF_INTR2_CPU_SET_reserved1_SHIFT                    19

/* MCIF_INTR2 :: CPU_SET :: reserved_for_eco2 [18:18] */
#define BCHP_MCIF_INTR2_CPU_SET_reserved_for_eco2_MASK             0x00040000
#define BCHP_MCIF_INTR2_CPU_SET_reserved_for_eco2_SHIFT            18

/* MCIF_INTR2 :: CPU_SET :: BICAP1_FIFO_OF_INTR [17:17] */
#define BCHP_MCIF_INTR2_CPU_SET_BICAP1_FIFO_OF_INTR_MASK           0x00020000
#define BCHP_MCIF_INTR2_CPU_SET_BICAP1_FIFO_OF_INTR_SHIFT          17

/* MCIF_INTR2 :: CPU_SET :: BICAP1_FIFO_LVL_INTR [16:16] */
#define BCHP_MCIF_INTR2_CPU_SET_BICAP1_FIFO_LVL_INTR_MASK          0x00010000
#define BCHP_MCIF_INTR2_CPU_SET_BICAP1_FIFO_LVL_INTR_SHIFT         16

/* MCIF_INTR2 :: CPU_SET :: BICAP1_FIFO_INACT_INTR [15:15] */
#define BCHP_MCIF_INTR2_CPU_SET_BICAP1_FIFO_INACT_INTR_MASK        0x00008000
#define BCHP_MCIF_INTR2_CPU_SET_BICAP1_FIFO_INACT_INTR_SHIFT       15

/* MCIF_INTR2 :: CPU_SET :: BICAP1_TIMEOUT3_INTR [14:14] */
#define BCHP_MCIF_INTR2_CPU_SET_BICAP1_TIMEOUT3_INTR_MASK          0x00004000
#define BCHP_MCIF_INTR2_CPU_SET_BICAP1_TIMEOUT3_INTR_SHIFT         14

/* MCIF_INTR2 :: CPU_SET :: BICAP1_TIMEOUT2_INTR [13:13] */
#define BCHP_MCIF_INTR2_CPU_SET_BICAP1_TIMEOUT2_INTR_MASK          0x00002000
#define BCHP_MCIF_INTR2_CPU_SET_BICAP1_TIMEOUT2_INTR_SHIFT         13

/* MCIF_INTR2 :: CPU_SET :: BICAP1_TIMEOUT1_INTR [12:12] */
#define BCHP_MCIF_INTR2_CPU_SET_BICAP1_TIMEOUT1_INTR_MASK          0x00001000
#define BCHP_MCIF_INTR2_CPU_SET_BICAP1_TIMEOUT1_INTR_SHIFT         12

/* MCIF_INTR2 :: CPU_SET :: BICAP1_TIMEOUT0_INTR [11:11] */
#define BCHP_MCIF_INTR2_CPU_SET_BICAP1_TIMEOUT0_INTR_MASK          0x00000800
#define BCHP_MCIF_INTR2_CPU_SET_BICAP1_TIMEOUT0_INTR_SHIFT         11

/* MCIF_INTR2 :: CPU_SET :: reserved3 [10:00] */
#define BCHP_MCIF_INTR2_CPU_SET_reserved3_MASK                     0x000007ff
#define BCHP_MCIF_INTR2_CPU_SET_reserved3_SHIFT                    0

/***************************************************************************
 *CPU_CLEAR - CPU interrupt Clear Register
 ***************************************************************************/
/* MCIF_INTR2 :: CPU_CLEAR :: reserved0 [31:22] */
#define BCHP_MCIF_INTR2_CPU_CLEAR_reserved0_MASK                   0xffc00000
#define BCHP_MCIF_INTR2_CPU_CLEAR_reserved0_SHIFT                  22

/* MCIF_INTR2 :: CPU_CLEAR :: WKTMR_ALARM_INTR [21:21] */
#define BCHP_MCIF_INTR2_CPU_CLEAR_WKTMR_ALARM_INTR_MASK            0x00200000
#define BCHP_MCIF_INTR2_CPU_CLEAR_WKTMR_ALARM_INTR_SHIFT           21

/* MCIF_INTR2 :: CPU_CLEAR :: reserved1 [20:19] */
#define BCHP_MCIF_INTR2_CPU_CLEAR_reserved1_MASK                   0x00180000
#define BCHP_MCIF_INTR2_CPU_CLEAR_reserved1_SHIFT                  19

/* MCIF_INTR2 :: CPU_CLEAR :: reserved_for_eco2 [18:18] */
#define BCHP_MCIF_INTR2_CPU_CLEAR_reserved_for_eco2_MASK           0x00040000
#define BCHP_MCIF_INTR2_CPU_CLEAR_reserved_for_eco2_SHIFT          18

/* MCIF_INTR2 :: CPU_CLEAR :: BICAP1_FIFO_OF_INTR [17:17] */
#define BCHP_MCIF_INTR2_CPU_CLEAR_BICAP1_FIFO_OF_INTR_MASK         0x00020000
#define BCHP_MCIF_INTR2_CPU_CLEAR_BICAP1_FIFO_OF_INTR_SHIFT        17

/* MCIF_INTR2 :: CPU_CLEAR :: BICAP1_FIFO_LVL_INTR [16:16] */
#define BCHP_MCIF_INTR2_CPU_CLEAR_BICAP1_FIFO_LVL_INTR_MASK        0x00010000
#define BCHP_MCIF_INTR2_CPU_CLEAR_BICAP1_FIFO_LVL_INTR_SHIFT       16

/* MCIF_INTR2 :: CPU_CLEAR :: BICAP1_FIFO_INACT_INTR [15:15] */
#define BCHP_MCIF_INTR2_CPU_CLEAR_BICAP1_FIFO_INACT_INTR_MASK      0x00008000
#define BCHP_MCIF_INTR2_CPU_CLEAR_BICAP1_FIFO_INACT_INTR_SHIFT     15

/* MCIF_INTR2 :: CPU_CLEAR :: BICAP1_TIMEOUT3_INTR [14:14] */
#define BCHP_MCIF_INTR2_CPU_CLEAR_BICAP1_TIMEOUT3_INTR_MASK        0x00004000
#define BCHP_MCIF_INTR2_CPU_CLEAR_BICAP1_TIMEOUT3_INTR_SHIFT       14

/* MCIF_INTR2 :: CPU_CLEAR :: BICAP1_TIMEOUT2_INTR [13:13] */
#define BCHP_MCIF_INTR2_CPU_CLEAR_BICAP1_TIMEOUT2_INTR_MASK        0x00002000
#define BCHP_MCIF_INTR2_CPU_CLEAR_BICAP1_TIMEOUT2_INTR_SHIFT       13

/* MCIF_INTR2 :: CPU_CLEAR :: BICAP1_TIMEOUT1_INTR [12:12] */
#define BCHP_MCIF_INTR2_CPU_CLEAR_BICAP1_TIMEOUT1_INTR_MASK        0x00001000
#define BCHP_MCIF_INTR2_CPU_CLEAR_BICAP1_TIMEOUT1_INTR_SHIFT       12

/* MCIF_INTR2 :: CPU_CLEAR :: BICAP1_TIMEOUT0_INTR [11:11] */
#define BCHP_MCIF_INTR2_CPU_CLEAR_BICAP1_TIMEOUT0_INTR_MASK        0x00000800
#define BCHP_MCIF_INTR2_CPU_CLEAR_BICAP1_TIMEOUT0_INTR_SHIFT       11

/* MCIF_INTR2 :: CPU_CLEAR :: reserved3 [10:00] */
#define BCHP_MCIF_INTR2_CPU_CLEAR_reserved3_MASK                   0x000007ff
#define BCHP_MCIF_INTR2_CPU_CLEAR_reserved3_SHIFT                  0

/***************************************************************************
 *CPU_MASK_STATUS - CPU interrupt Mask Status Register
 ***************************************************************************/
/* MCIF_INTR2 :: CPU_MASK_STATUS :: reserved0 [31:22] */
#define BCHP_MCIF_INTR2_CPU_MASK_STATUS_reserved0_MASK             0xffc00000
#define BCHP_MCIF_INTR2_CPU_MASK_STATUS_reserved0_SHIFT            22

/* MCIF_INTR2 :: CPU_MASK_STATUS :: WKTMR_ALARM_INTR [21:21] */
#define BCHP_MCIF_INTR2_CPU_MASK_STATUS_WKTMR_ALARM_INTR_MASK      0x00200000
#define BCHP_MCIF_INTR2_CPU_MASK_STATUS_WKTMR_ALARM_INTR_SHIFT     21

/* MCIF_INTR2 :: CPU_MASK_STATUS :: reserved1 [20:19] */
#define BCHP_MCIF_INTR2_CPU_MASK_STATUS_reserved1_MASK             0x00180000
#define BCHP_MCIF_INTR2_CPU_MASK_STATUS_reserved1_SHIFT            19

/* MCIF_INTR2 :: CPU_MASK_STATUS :: reserved_for_eco2 [18:18] */
#define BCHP_MCIF_INTR2_CPU_MASK_STATUS_reserved_for_eco2_MASK     0x00040000
#define BCHP_MCIF_INTR2_CPU_MASK_STATUS_reserved_for_eco2_SHIFT    18

/* MCIF_INTR2 :: CPU_MASK_STATUS :: BICAP0_FIFO_OF_INTR [17:17] */
#define BCHP_MCIF_INTR2_CPU_MASK_STATUS_BICAP0_FIFO_OF_INTR_MASK   0x00020000
#define BCHP_MCIF_INTR2_CPU_MASK_STATUS_BICAP0_FIFO_OF_INTR_SHIFT  17

/* MCIF_INTR2 :: CPU_MASK_STATUS :: BICAP0_FIFO_IRQ_INTR [16:16] */
#define BCHP_MCIF_INTR2_CPU_MASK_STATUS_BICAP0_FIFO_IRQ_INTR_MASK  0x00010000
#define BCHP_MCIF_INTR2_CPU_MASK_STATUS_BICAP0_FIFO_IRQ_INTR_SHIFT 16

/* MCIF_INTR2 :: CPU_MASK_STATUS :: BICAP0_CPU_TIMEOUT_INTR [15:15] */
#define BCHP_MCIF_INTR2_CPU_MASK_STATUS_BICAP0_CPU_TIMEOUT_INTR_MASK 0x00008000
#define BCHP_MCIF_INTR2_CPU_MASK_STATUS_BICAP0_CPU_TIMEOUT_INTR_SHIFT 15

/* MCIF_INTR2 :: CPU_MASK_STATUS :: BICAP0_EDGE_TIMEOUT_INTR [14:11] */
#define BCHP_MCIF_INTR2_CPU_MASK_STATUS_BICAP0_EDGE_TIMEOUT_INTR_MASK 0x00007800
#define BCHP_MCIF_INTR2_CPU_MASK_STATUS_BICAP0_EDGE_TIMEOUT_INTR_SHIFT 11

/* MCIF_INTR2 :: CPU_MASK_STATUS :: reserved3 [10:00] */
#define BCHP_MCIF_INTR2_CPU_MASK_STATUS_reserved3_MASK             0x000007ff
#define BCHP_MCIF_INTR2_CPU_MASK_STATUS_reserved3_SHIFT            0

/***************************************************************************
 *CPU_MASK_SET - CPU interrupt Mask Set Register
 ***************************************************************************/
/* MCIF_INTR2 :: CPU_MASK_SET :: reserved0 [31:22] */
#define BCHP_MCIF_INTR2_CPU_MASK_SET_reserved0_MASK                0xffc00000
#define BCHP_MCIF_INTR2_CPU_MASK_SET_reserved0_SHIFT               22

/* MCIF_INTR2 :: CPU_MASK_SET :: WKTMR_ALARM_INTR [21:21] */
#define BCHP_MCIF_INTR2_CPU_MASK_SET_WKTMR_ALARM_INTR_MASK         0x00200000
#define BCHP_MCIF_INTR2_CPU_MASK_SET_WKTMR_ALARM_INTR_SHIFT        21

/* MCIF_INTR2 :: CPU_MASK_SET :: reserved1 [20:19] */
#define BCHP_MCIF_INTR2_CPU_MASK_SET_reserved1_MASK                0x00180000
#define BCHP_MCIF_INTR2_CPU_MASK_SET_reserved1_SHIFT               19

/* MCIF_INTR2 :: CPU_MASK_SET :: reserved_for_eco2 [18:18] */
#define BCHP_MCIF_INTR2_CPU_MASK_SET_reserved_for_eco2_MASK        0x00040000
#define BCHP_MCIF_INTR2_CPU_MASK_SET_reserved_for_eco2_SHIFT       18

/* MCIF_INTR2 :: CPU_MASK_SET :: BICAP0_FIFO_OF_INTR [17:17] */
#define BCHP_MCIF_INTR2_CPU_MASK_SET_BICAP0_FIFO_OF_INTR_MASK      0x00020000
#define BCHP_MCIF_INTR2_CPU_MASK_SET_BICAP0_FIFO_OF_INTR_SHIFT     17

/* MCIF_INTR2 :: CPU_MASK_SET :: BICAP0_FIFO_IRQ_INTR [16:16] */
#define BCHP_MCIF_INTR2_CPU_MASK_SET_BICAP0_FIFO_IRQ_INTR_MASK     0x00010000
#define BCHP_MCIF_INTR2_CPU_MASK_SET_BICAP0_FIFO_IRQ_INTR_SHIFT    16

/* MCIF_INTR2 :: CPU_MASK_SET :: BICAP0_CPU_TIMEOUT_INTR [15:15] */
#define BCHP_MCIF_INTR2_CPU_MASK_SET_BICAP0_CPU_TIMEOUT_INTR_MASK  0x00008000
#define BCHP_MCIF_INTR2_CPU_MASK_SET_BICAP0_CPU_TIMEOUT_INTR_SHIFT 15

/* MCIF_INTR2 :: CPU_MASK_SET :: BICAP0_EDGE_TIMEOUT_INTR [14:11] */
#define BCHP_MCIF_INTR2_CPU_MASK_SET_BICAP0_EDGE_TIMEOUT_INTR_MASK 0x00007800
#define BCHP_MCIF_INTR2_CPU_MASK_SET_BICAP0_EDGE_TIMEOUT_INTR_SHIFT 11

/* MCIF_INTR2 :: CPU_MASK_SET :: reserved3 [10:00] */
#define BCHP_MCIF_INTR2_CPU_MASK_SET_reserved3_MASK                0x000007ff
#define BCHP_MCIF_INTR2_CPU_MASK_SET_reserved3_SHIFT               0

/***************************************************************************
 *CPU_MASK_CLEAR - CPU interrupt Mask Clear Register
 ***************************************************************************/
/* MCIF_INTR2 :: CPU_MASK_CLEAR :: reserved0 [31:22] */
#define BCHP_MCIF_INTR2_CPU_MASK_CLEAR_reserved0_MASK              0xffc00000
#define BCHP_MCIF_INTR2_CPU_MASK_CLEAR_reserved0_SHIFT             22

/* MCIF_INTR2 :: CPU_MASK_CLEAR :: WKTMR_ALARM_INTR [21:21] */
#define BCHP_MCIF_INTR2_CPU_MASK_CLEAR_WKTMR_ALARM_INTR_MASK       0x00200000
#define BCHP_MCIF_INTR2_CPU_MASK_CLEAR_WKTMR_ALARM_INTR_SHIFT      21

/* MCIF_INTR2 :: CPU_MASK_CLEAR :: reserved1 [20:19] */
#define BCHP_MCIF_INTR2_CPU_MASK_CLEAR_reserved1_MASK              0x00180000
#define BCHP_MCIF_INTR2_CPU_MASK_CLEAR_reserved1_SHIFT             19

/* MCIF_INTR2 :: CPU_MASK_CLEAR :: reserved_for_eco2 [18:18] */
#define BCHP_MCIF_INTR2_CPU_MASK_CLEAR_reserved_for_eco2_MASK      0x00040000
#define BCHP_MCIF_INTR2_CPU_MASK_CLEAR_reserved_for_eco2_SHIFT     18

/* MCIF_INTR2 :: CPU_MASK_CLEAR :: BICAP0_FIFO_OF_INTR [17:17] */
#define BCHP_MCIF_INTR2_CPU_MASK_CLEAR_BICAP0_FIFO_OF_INTR_MASK    0x00020000
#define BCHP_MCIF_INTR2_CPU_MASK_CLEAR_BICAP0_FIFO_OF_INTR_SHIFT   17

/* MCIF_INTR2 :: CPU_MASK_CLEAR :: BICAP0_FIFO_IRQ_INTR [16:16] */
#define BCHP_MCIF_INTR2_CPU_MASK_CLEAR_BICAP0_FIFO_IRQ_INTR_MASK   0x00010000
#define BCHP_MCIF_INTR2_CPU_MASK_CLEAR_BICAP0_FIFO_IRQ_INTR_SHIFT  16

/* MCIF_INTR2 :: CPU_MASK_CLEAR :: BICAP0_CPU_TIMEOUT_INTR [15:15] */
#define BCHP_MCIF_INTR2_CPU_MASK_CLEAR_BICAP0_CPU_TIMEOUT_INTR_MASK 0x00008000
#define BCHP_MCIF_INTR2_CPU_MASK_CLEAR_BICAP0_CPU_TIMEOUT_INTR_SHIFT 15

/* MCIF_INTR2 :: CPU_MASK_CLEAR :: BICAP0_EDGE_TIMEOUT_INTR [14:11] */
#define BCHP_MCIF_INTR2_CPU_MASK_CLEAR_BICAP0_EDGE_TIMEOUT_INTR_MASK 0x00007800
#define BCHP_MCIF_INTR2_CPU_MASK_CLEAR_BICAP0_EDGE_TIMEOUT_INTR_SHIFT 11

/* MCIF_INTR2 :: CPU_MASK_CLEAR :: reserved3 [10:00] */
#define BCHP_MCIF_INTR2_CPU_MASK_CLEAR_reserved3_MASK              0x000007ff
#define BCHP_MCIF_INTR2_CPU_MASK_CLEAR_reserved3_SHIFT             0

/***************************************************************************
 *PCI_STATUS - PCI interrupt Status Register
 ***************************************************************************/
/* MCIF_INTR2 :: PCI_STATUS :: reserved0 [31:22] */
#define BCHP_MCIF_INTR2_PCI_STATUS_reserved0_MASK                  0xffc00000
#define BCHP_MCIF_INTR2_PCI_STATUS_reserved0_SHIFT                 22

/* MCIF_INTR2 :: PCI_STATUS :: WKTMR_ALARM_INTR [21:21] */
#define BCHP_MCIF_INTR2_PCI_STATUS_WKTMR_ALARM_INTR_MASK           0x00200000
#define BCHP_MCIF_INTR2_PCI_STATUS_WKTMR_ALARM_INTR_SHIFT          21

/* MCIF_INTR2 :: PCI_STATUS :: reserved1 [20:19] */
#define BCHP_MCIF_INTR2_PCI_STATUS_reserved1_MASK                  0x00180000
#define BCHP_MCIF_INTR2_PCI_STATUS_reserved1_SHIFT                 19

/* MCIF_INTR2 :: PCI_STATUS :: reserved_for_eco2 [18:18] */
#define BCHP_MCIF_INTR2_PCI_STATUS_reserved_for_eco2_MASK          0x00040000
#define BCHP_MCIF_INTR2_PCI_STATUS_reserved_for_eco2_SHIFT         18

/* MCIF_INTR2 :: PCI_STATUS :: BICAP1_FIFO_OF_INTR [17:17] */
#define BCHP_MCIF_INTR2_PCI_STATUS_BICAP1_FIFO_OF_INTR_MASK        0x00020000
#define BCHP_MCIF_INTR2_PCI_STATUS_BICAP1_FIFO_OF_INTR_SHIFT       17

/* MCIF_INTR2 :: PCI_STATUS :: BICAP1_FIFO_LVL_INTR [16:16] */
#define BCHP_MCIF_INTR2_PCI_STATUS_BICAP1_FIFO_LVL_INTR_MASK       0x00010000
#define BCHP_MCIF_INTR2_PCI_STATUS_BICAP1_FIFO_LVL_INTR_SHIFT      16

/* MCIF_INTR2 :: PCI_STATUS :: BICAP1_FIFO_INACT_INTR [15:15] */
#define BCHP_MCIF_INTR2_PCI_STATUS_BICAP1_FIFO_INACT_INTR_MASK     0x00008000
#define BCHP_MCIF_INTR2_PCI_STATUS_BICAP1_FIFO_INACT_INTR_SHIFT    15

/* MCIF_INTR2 :: PCI_STATUS :: BICAP1_TIMEOUT3_INTR [14:14] */
#define BCHP_MCIF_INTR2_PCI_STATUS_BICAP1_TIMEOUT3_INTR_MASK       0x00004000
#define BCHP_MCIF_INTR2_PCI_STATUS_BICAP1_TIMEOUT3_INTR_SHIFT      14

/* MCIF_INTR2 :: PCI_STATUS :: BICAP1_TIMEOUT2_INTR [13:13] */
#define BCHP_MCIF_INTR2_PCI_STATUS_BICAP1_TIMEOUT2_INTR_MASK       0x00002000
#define BCHP_MCIF_INTR2_PCI_STATUS_BICAP1_TIMEOUT2_INTR_SHIFT      13

/* MCIF_INTR2 :: PCI_STATUS :: BICAP1_TIMEOUT1_INTR [12:12] */
#define BCHP_MCIF_INTR2_PCI_STATUS_BICAP1_TIMEOUT1_INTR_MASK       0x00001000
#define BCHP_MCIF_INTR2_PCI_STATUS_BICAP1_TIMEOUT1_INTR_SHIFT      12

/* MCIF_INTR2 :: PCI_STATUS :: BICAP1_TIMEOUT0_INTR [11:11] */
#define BCHP_MCIF_INTR2_PCI_STATUS_BICAP1_TIMEOUT0_INTR_MASK       0x00000800
#define BCHP_MCIF_INTR2_PCI_STATUS_BICAP1_TIMEOUT0_INTR_SHIFT      11

/* MCIF_INTR2 :: PCI_STATUS :: reserved3 [10:00] */
#define BCHP_MCIF_INTR2_PCI_STATUS_reserved3_MASK                  0x000007ff
#define BCHP_MCIF_INTR2_PCI_STATUS_reserved3_SHIFT                 0

/***************************************************************************
 *PCI_SET - PCI interrupt Set Register
 ***************************************************************************/
/* MCIF_INTR2 :: PCI_SET :: reserved0 [31:22] */
#define BCHP_MCIF_INTR2_PCI_SET_reserved0_MASK                     0xffc00000
#define BCHP_MCIF_INTR2_PCI_SET_reserved0_SHIFT                    22

/* MCIF_INTR2 :: PCI_SET :: WKTMR_ALARM_INTR [21:21] */
#define BCHP_MCIF_INTR2_PCI_SET_WKTMR_ALARM_INTR_MASK              0x00200000
#define BCHP_MCIF_INTR2_PCI_SET_WKTMR_ALARM_INTR_SHIFT             21

/* MCIF_INTR2 :: PCI_SET :: reserved1 [20:19] */
#define BCHP_MCIF_INTR2_PCI_SET_reserved1_MASK                     0x00180000
#define BCHP_MCIF_INTR2_PCI_SET_reserved1_SHIFT                    19

/* MCIF_INTR2 :: PCI_SET :: reserved_for_eco2 [18:18] */
#define BCHP_MCIF_INTR2_PCI_SET_reserved_for_eco2_MASK             0x00040000
#define BCHP_MCIF_INTR2_PCI_SET_reserved_for_eco2_SHIFT            18

/* MCIF_INTR2 :: PCI_SET :: BICAP1_FIFO_OF_INTR [17:17] */
#define BCHP_MCIF_INTR2_PCI_SET_BICAP1_FIFO_OF_INTR_MASK           0x00020000
#define BCHP_MCIF_INTR2_PCI_SET_BICAP1_FIFO_OF_INTR_SHIFT          17

/* MCIF_INTR2 :: PCI_SET :: BICAP1_FIFO_LVL_INTR [16:16] */
#define BCHP_MCIF_INTR2_PCI_SET_BICAP1_FIFO_LVL_INTR_MASK          0x00010000
#define BCHP_MCIF_INTR2_PCI_SET_BICAP1_FIFO_LVL_INTR_SHIFT         16

/* MCIF_INTR2 :: PCI_SET :: BICAP1_FIFO_INACT_INTR [15:15] */
#define BCHP_MCIF_INTR2_PCI_SET_BICAP1_FIFO_INACT_INTR_MASK        0x00008000
#define BCHP_MCIF_INTR2_PCI_SET_BICAP1_FIFO_INACT_INTR_SHIFT       15

/* MCIF_INTR2 :: PCI_SET :: BICAP1_TIMEOUT3_INTR [14:14] */
#define BCHP_MCIF_INTR2_PCI_SET_BICAP1_TIMEOUT3_INTR_MASK          0x00004000
#define BCHP_MCIF_INTR2_PCI_SET_BICAP1_TIMEOUT3_INTR_SHIFT         14

/* MCIF_INTR2 :: PCI_SET :: BICAP1_TIMEOUT2_INTR [13:13] */
#define BCHP_MCIF_INTR2_PCI_SET_BICAP1_TIMEOUT2_INTR_MASK          0x00002000
#define BCHP_MCIF_INTR2_PCI_SET_BICAP1_TIMEOUT2_INTR_SHIFT         13

/* MCIF_INTR2 :: PCI_SET :: BICAP1_TIMEOUT1_INTR [12:12] */
#define BCHP_MCIF_INTR2_PCI_SET_BICAP1_TIMEOUT1_INTR_MASK          0x00001000
#define BCHP_MCIF_INTR2_PCI_SET_BICAP1_TIMEOUT1_INTR_SHIFT         12

/* MCIF_INTR2 :: PCI_SET :: BICAP1_TIMEOUT0_INTR [11:11] */
#define BCHP_MCIF_INTR2_PCI_SET_BICAP1_TIMEOUT0_INTR_MASK          0x00000800
#define BCHP_MCIF_INTR2_PCI_SET_BICAP1_TIMEOUT0_INTR_SHIFT         11

/* MCIF_INTR2 :: PCI_SET :: reserved3 [10:00] */
#define BCHP_MCIF_INTR2_PCI_SET_reserved3_MASK                     0x000007ff
#define BCHP_MCIF_INTR2_PCI_SET_reserved3_SHIFT                    0

/***************************************************************************
 *PCI_CLEAR - PCI interrupt Clear Register
 ***************************************************************************/
/* MCIF_INTR2 :: PCI_CLEAR :: reserved0 [31:22] */
#define BCHP_MCIF_INTR2_PCI_CLEAR_reserved0_MASK                   0xffc00000
#define BCHP_MCIF_INTR2_PCI_CLEAR_reserved0_SHIFT                  22

/* MCIF_INTR2 :: PCI_CLEAR :: WKTMR_ALARM_INTR [21:21] */
#define BCHP_MCIF_INTR2_PCI_CLEAR_WKTMR_ALARM_INTR_MASK            0x00200000
#define BCHP_MCIF_INTR2_PCI_CLEAR_WKTMR_ALARM_INTR_SHIFT           21

/* MCIF_INTR2 :: PCI_CLEAR :: reserved1 [20:19] */
#define BCHP_MCIF_INTR2_PCI_CLEAR_reserved1_MASK                   0x00180000
#define BCHP_MCIF_INTR2_PCI_CLEAR_reserved1_SHIFT                  19

/* MCIF_INTR2 :: PCI_CLEAR :: reserved_for_eco2 [18:18] */
#define BCHP_MCIF_INTR2_PCI_CLEAR_reserved_for_eco2_MASK           0x00040000
#define BCHP_MCIF_INTR2_PCI_CLEAR_reserved_for_eco2_SHIFT          18

/* MCIF_INTR2 :: PCI_CLEAR :: BICAP1_FIFO_OF_INTR [17:17] */
#define BCHP_MCIF_INTR2_PCI_CLEAR_BICAP1_FIFO_OF_INTR_MASK         0x00020000
#define BCHP_MCIF_INTR2_PCI_CLEAR_BICAP1_FIFO_OF_INTR_SHIFT        17

/* MCIF_INTR2 :: PCI_CLEAR :: BICAP1_FIFO_LVL_INTR [16:16] */
#define BCHP_MCIF_INTR2_PCI_CLEAR_BICAP1_FIFO_LVL_INTR_MASK        0x00010000
#define BCHP_MCIF_INTR2_PCI_CLEAR_BICAP1_FIFO_LVL_INTR_SHIFT       16

/* MCIF_INTR2 :: PCI_CLEAR :: BICAP1_FIFO_INACT_INTR [15:15] */
#define BCHP_MCIF_INTR2_PCI_CLEAR_BICAP1_FIFO_INACT_INTR_MASK      0x00008000
#define BCHP_MCIF_INTR2_PCI_CLEAR_BICAP1_FIFO_INACT_INTR_SHIFT     15

/* MCIF_INTR2 :: PCI_CLEAR :: BICAP1_TIMEOUT3_INTR [14:14] */
#define BCHP_MCIF_INTR2_PCI_CLEAR_BICAP1_TIMEOUT3_INTR_MASK        0x00004000
#define BCHP_MCIF_INTR2_PCI_CLEAR_BICAP1_TIMEOUT3_INTR_SHIFT       14

/* MCIF_INTR2 :: PCI_CLEAR :: BICAP1_TIMEOUT2_INTR [13:13] */
#define BCHP_MCIF_INTR2_PCI_CLEAR_BICAP1_TIMEOUT2_INTR_MASK        0x00002000
#define BCHP_MCIF_INTR2_PCI_CLEAR_BICAP1_TIMEOUT2_INTR_SHIFT       13

/* MCIF_INTR2 :: PCI_CLEAR :: BICAP1_TIMEOUT1_INTR [12:12] */
#define BCHP_MCIF_INTR2_PCI_CLEAR_BICAP1_TIMEOUT1_INTR_MASK        0x00001000
#define BCHP_MCIF_INTR2_PCI_CLEAR_BICAP1_TIMEOUT1_INTR_SHIFT       12

/* MCIF_INTR2 :: PCI_CLEAR :: BICAP1_TIMEOUT0_INTR [11:11] */
#define BCHP_MCIF_INTR2_PCI_CLEAR_BICAP1_TIMEOUT0_INTR_MASK        0x00000800
#define BCHP_MCIF_INTR2_PCI_CLEAR_BICAP1_TIMEOUT0_INTR_SHIFT       11

/* MCIF_INTR2 :: PCI_CLEAR :: reserved3 [10:00] */
#define BCHP_MCIF_INTR2_PCI_CLEAR_reserved3_MASK                   0x000007ff
#define BCHP_MCIF_INTR2_PCI_CLEAR_reserved3_SHIFT                  0

/***************************************************************************
 *PCI_MASK_STATUS - PCI interrupt Mask Status Register
 ***************************************************************************/
/* MCIF_INTR2 :: PCI_MASK_STATUS :: reserved0 [31:22] */
#define BCHP_MCIF_INTR2_PCI_MASK_STATUS_reserved0_MASK             0xffc00000
#define BCHP_MCIF_INTR2_PCI_MASK_STATUS_reserved0_SHIFT            22

/* MCIF_INTR2 :: PCI_MASK_STATUS :: WKTMR_ALARM_INTR [21:21] */
#define BCHP_MCIF_INTR2_PCI_MASK_STATUS_WKTMR_ALARM_INTR_MASK      0x00200000
#define BCHP_MCIF_INTR2_PCI_MASK_STATUS_WKTMR_ALARM_INTR_SHIFT     21

/* MCIF_INTR2 :: PCI_MASK_STATUS :: reserved1 [20:19] */
#define BCHP_MCIF_INTR2_PCI_MASK_STATUS_reserved1_MASK             0x00180000
#define BCHP_MCIF_INTR2_PCI_MASK_STATUS_reserved1_SHIFT            19

/* MCIF_INTR2 :: PCI_MASK_STATUS :: reserved_for_eco2 [18:18] */
#define BCHP_MCIF_INTR2_PCI_MASK_STATUS_reserved_for_eco2_MASK     0x00040000
#define BCHP_MCIF_INTR2_PCI_MASK_STATUS_reserved_for_eco2_SHIFT    18

/* MCIF_INTR2 :: PCI_MASK_STATUS :: BICAP0_FIFO_OF_INTR [17:17] */
#define BCHP_MCIF_INTR2_PCI_MASK_STATUS_BICAP0_FIFO_OF_INTR_MASK   0x00020000
#define BCHP_MCIF_INTR2_PCI_MASK_STATUS_BICAP0_FIFO_OF_INTR_SHIFT  17

/* MCIF_INTR2 :: PCI_MASK_STATUS :: BICAP0_FIFO_IRQ_INTR [16:16] */
#define BCHP_MCIF_INTR2_PCI_MASK_STATUS_BICAP0_FIFO_IRQ_INTR_MASK  0x00010000
#define BCHP_MCIF_INTR2_PCI_MASK_STATUS_BICAP0_FIFO_IRQ_INTR_SHIFT 16

/* MCIF_INTR2 :: PCI_MASK_STATUS :: BICAP0_CPU_TIMEOUT_INTR [15:15] */
#define BCHP_MCIF_INTR2_PCI_MASK_STATUS_BICAP0_CPU_TIMEOUT_INTR_MASK 0x00008000
#define BCHP_MCIF_INTR2_PCI_MASK_STATUS_BICAP0_CPU_TIMEOUT_INTR_SHIFT 15

/* MCIF_INTR2 :: PCI_MASK_STATUS :: BICAP0_EDGE_TIMEOUT_INTR [14:11] */
#define BCHP_MCIF_INTR2_PCI_MASK_STATUS_BICAP0_EDGE_TIMEOUT_INTR_MASK 0x00007800
#define BCHP_MCIF_INTR2_PCI_MASK_STATUS_BICAP0_EDGE_TIMEOUT_INTR_SHIFT 11

/* MCIF_INTR2 :: PCI_MASK_STATUS :: reserved3 [10:00] */
#define BCHP_MCIF_INTR2_PCI_MASK_STATUS_reserved3_MASK             0x000007ff
#define BCHP_MCIF_INTR2_PCI_MASK_STATUS_reserved3_SHIFT            0

/***************************************************************************
 *PCI_MASK_SET - PCI interrupt Mask Set Register
 ***************************************************************************/
/* MCIF_INTR2 :: PCI_MASK_SET :: reserved0 [31:22] */
#define BCHP_MCIF_INTR2_PCI_MASK_SET_reserved0_MASK                0xffc00000
#define BCHP_MCIF_INTR2_PCI_MASK_SET_reserved0_SHIFT               22

/* MCIF_INTR2 :: PCI_MASK_SET :: WKTMR_ALARM_INTR [21:21] */
#define BCHP_MCIF_INTR2_PCI_MASK_SET_WKTMR_ALARM_INTR_MASK         0x00200000
#define BCHP_MCIF_INTR2_PCI_MASK_SET_WKTMR_ALARM_INTR_SHIFT        21

/* MCIF_INTR2 :: PCI_MASK_SET :: reserved1 [20:19] */
#define BCHP_MCIF_INTR2_PCI_MASK_SET_reserved1_MASK                0x00180000
#define BCHP_MCIF_INTR2_PCI_MASK_SET_reserved1_SHIFT               19

/* MCIF_INTR2 :: PCI_MASK_SET :: reserved_for_eco2 [18:18] */
#define BCHP_MCIF_INTR2_PCI_MASK_SET_reserved_for_eco2_MASK        0x00040000
#define BCHP_MCIF_INTR2_PCI_MASK_SET_reserved_for_eco2_SHIFT       18

/* MCIF_INTR2 :: PCI_MASK_SET :: BICAP0_FIFO_OF_INTR [17:17] */
#define BCHP_MCIF_INTR2_PCI_MASK_SET_BICAP0_FIFO_OF_INTR_MASK      0x00020000
#define BCHP_MCIF_INTR2_PCI_MASK_SET_BICAP0_FIFO_OF_INTR_SHIFT     17

/* MCIF_INTR2 :: PCI_MASK_SET :: BICAP0_FIFO_IRQ_INTR [16:16] */
#define BCHP_MCIF_INTR2_PCI_MASK_SET_BICAP0_FIFO_IRQ_INTR_MASK     0x00010000
#define BCHP_MCIF_INTR2_PCI_MASK_SET_BICAP0_FIFO_IRQ_INTR_SHIFT    16

/* MCIF_INTR2 :: PCI_MASK_SET :: BICAP0_CPU_TIMEOUT_INTR [15:15] */
#define BCHP_MCIF_INTR2_PCI_MASK_SET_BICAP0_CPU_TIMEOUT_INTR_MASK  0x00008000
#define BCHP_MCIF_INTR2_PCI_MASK_SET_BICAP0_CPU_TIMEOUT_INTR_SHIFT 15

/* MCIF_INTR2 :: PCI_MASK_SET :: BICAP0_EDGE_TIMEOUT_INTR [14:11] */
#define BCHP_MCIF_INTR2_PCI_MASK_SET_BICAP0_EDGE_TIMEOUT_INTR_MASK 0x00007800
#define BCHP_MCIF_INTR2_PCI_MASK_SET_BICAP0_EDGE_TIMEOUT_INTR_SHIFT 11

/* MCIF_INTR2 :: PCI_MASK_SET :: reserved3 [10:00] */
#define BCHP_MCIF_INTR2_PCI_MASK_SET_reserved3_MASK                0x000007ff
#define BCHP_MCIF_INTR2_PCI_MASK_SET_reserved3_SHIFT               0

/***************************************************************************
 *PCI_MASK_CLEAR - PCI interrupt Mask Clear Register
 ***************************************************************************/
/* MCIF_INTR2 :: PCI_MASK_CLEAR :: reserved0 [31:22] */
#define BCHP_MCIF_INTR2_PCI_MASK_CLEAR_reserved0_MASK              0xffc00000
#define BCHP_MCIF_INTR2_PCI_MASK_CLEAR_reserved0_SHIFT             22

/* MCIF_INTR2 :: PCI_MASK_CLEAR :: WKTMR_ALARM_INTR [21:21] */
#define BCHP_MCIF_INTR2_PCI_MASK_CLEAR_WKTMR_ALARM_INTR_MASK       0x00200000
#define BCHP_MCIF_INTR2_PCI_MASK_CLEAR_WKTMR_ALARM_INTR_SHIFT      21

/* MCIF_INTR2 :: PCI_MASK_CLEAR :: reserved1 [20:19] */
#define BCHP_MCIF_INTR2_PCI_MASK_CLEAR_reserved1_MASK              0x00180000
#define BCHP_MCIF_INTR2_PCI_MASK_CLEAR_reserved1_SHIFT             19

/* MCIF_INTR2 :: PCI_MASK_CLEAR :: reserved_for_eco2 [18:18] */
#define BCHP_MCIF_INTR2_PCI_MASK_CLEAR_reserved_for_eco2_MASK      0x00040000
#define BCHP_MCIF_INTR2_PCI_MASK_CLEAR_reserved_for_eco2_SHIFT     18

/* MCIF_INTR2 :: PCI_MASK_CLEAR :: BICAP0_FIFO_OF_INTR [17:17] */
#define BCHP_MCIF_INTR2_PCI_MASK_CLEAR_BICAP0_FIFO_OF_INTR_MASK    0x00020000
#define BCHP_MCIF_INTR2_PCI_MASK_CLEAR_BICAP0_FIFO_OF_INTR_SHIFT   17

/* MCIF_INTR2 :: PCI_MASK_CLEAR :: BICAP0_FIFO_IRQ_INTR [16:16] */
#define BCHP_MCIF_INTR2_PCI_MASK_CLEAR_BICAP0_FIFO_IRQ_INTR_MASK   0x00010000
#define BCHP_MCIF_INTR2_PCI_MASK_CLEAR_BICAP0_FIFO_IRQ_INTR_SHIFT  16

/* MCIF_INTR2 :: PCI_MASK_CLEAR :: BICAP0_CPU_TIMEOUT_INTR [15:15] */
#define BCHP_MCIF_INTR2_PCI_MASK_CLEAR_BICAP0_CPU_TIMEOUT_INTR_MASK 0x00008000
#define BCHP_MCIF_INTR2_PCI_MASK_CLEAR_BICAP0_CPU_TIMEOUT_INTR_SHIFT 15

/* MCIF_INTR2 :: PCI_MASK_CLEAR :: BICAP0_EDGE_TIMEOUT_INTR [14:11] */
#define BCHP_MCIF_INTR2_PCI_MASK_CLEAR_BICAP0_EDGE_TIMEOUT_INTR_MASK 0x00007800
#define BCHP_MCIF_INTR2_PCI_MASK_CLEAR_BICAP0_EDGE_TIMEOUT_INTR_SHIFT 11

/* MCIF_INTR2 :: PCI_MASK_CLEAR :: reserved3 [10:00] */
#define BCHP_MCIF_INTR2_PCI_MASK_CLEAR_reserved3_MASK              0x000007ff
#define BCHP_MCIF_INTR2_PCI_MASK_CLEAR_reserved3_SHIFT             0

#endif /* #ifndef BCHP_MCIF_INTR2_H__ */

/* End of File */

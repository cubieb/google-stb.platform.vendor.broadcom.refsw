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
 * Date:           Generated on               Wed Feb 11 10:13:59 2015
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

#ifndef BCHP_SYMCNT7_L2_H__
#define BCHP_SYMCNT7_L2_H__

/***************************************************************************
 *SYMCNT7_L2 - SYMCNT7 Interrupt (MAC_L2_7) registers
 ***************************************************************************/
#define BCHP_SYMCNT7_L2_CPU_STATUS               0x014e0d00 /* [RO] CPU interrupt Status Register */
#define BCHP_SYMCNT7_L2_CPU_SET                  0x014e0d04 /* [WO] CPU interrupt Set Register */
#define BCHP_SYMCNT7_L2_CPU_CLEAR                0x014e0d08 /* [WO] CPU interrupt Clear Register */
#define BCHP_SYMCNT7_L2_CPU_MASK_STATUS          0x014e0d0c /* [RO] CPU interrupt Mask Status Register */
#define BCHP_SYMCNT7_L2_CPU_MASK_SET             0x014e0d10 /* [WO] CPU interrupt Mask Set Register */
#define BCHP_SYMCNT7_L2_CPU_MASK_CLEAR           0x014e0d14 /* [WO] CPU interrupt Mask Clear Register */

/***************************************************************************
 *CPU_STATUS - CPU interrupt Status Register
 ***************************************************************************/
/* SYMCNT7_L2 :: CPU_STATUS :: RSVD [31:01] */
#define BCHP_SYMCNT7_L2_CPU_STATUS_RSVD_MASK                       0xfffffffe
#define BCHP_SYMCNT7_L2_CPU_STATUS_RSVD_SHIFT                      1
#define BCHP_SYMCNT7_L2_CPU_STATUS_RSVD_DEFAULT                    0x00000000

/* SYMCNT7_L2 :: CPU_STATUS :: SYMBOL_COUNTER_INTR_7 [00:00] */
#define BCHP_SYMCNT7_L2_CPU_STATUS_SYMBOL_COUNTER_INTR_7_MASK      0x00000001
#define BCHP_SYMCNT7_L2_CPU_STATUS_SYMBOL_COUNTER_INTR_7_SHIFT     0
#define BCHP_SYMCNT7_L2_CPU_STATUS_SYMBOL_COUNTER_INTR_7_DEFAULT   0x00000000

/***************************************************************************
 *CPU_SET - CPU interrupt Set Register
 ***************************************************************************/
/* SYMCNT7_L2 :: CPU_SET :: RSVD [31:01] */
#define BCHP_SYMCNT7_L2_CPU_SET_RSVD_MASK                          0xfffffffe
#define BCHP_SYMCNT7_L2_CPU_SET_RSVD_SHIFT                         1
#define BCHP_SYMCNT7_L2_CPU_SET_RSVD_DEFAULT                       0x00000000

/* SYMCNT7_L2 :: CPU_SET :: SYMBOL_COUNTER_INTR_7 [00:00] */
#define BCHP_SYMCNT7_L2_CPU_SET_SYMBOL_COUNTER_INTR_7_MASK         0x00000001
#define BCHP_SYMCNT7_L2_CPU_SET_SYMBOL_COUNTER_INTR_7_SHIFT        0
#define BCHP_SYMCNT7_L2_CPU_SET_SYMBOL_COUNTER_INTR_7_DEFAULT      0x00000000

/***************************************************************************
 *CPU_CLEAR - CPU interrupt Clear Register
 ***************************************************************************/
/* SYMCNT7_L2 :: CPU_CLEAR :: RSVD [31:01] */
#define BCHP_SYMCNT7_L2_CPU_CLEAR_RSVD_MASK                        0xfffffffe
#define BCHP_SYMCNT7_L2_CPU_CLEAR_RSVD_SHIFT                       1
#define BCHP_SYMCNT7_L2_CPU_CLEAR_RSVD_DEFAULT                     0x00000000

/* SYMCNT7_L2 :: CPU_CLEAR :: SYMBOL_COUNTER_INTR_7 [00:00] */
#define BCHP_SYMCNT7_L2_CPU_CLEAR_SYMBOL_COUNTER_INTR_7_MASK       0x00000001
#define BCHP_SYMCNT7_L2_CPU_CLEAR_SYMBOL_COUNTER_INTR_7_SHIFT      0
#define BCHP_SYMCNT7_L2_CPU_CLEAR_SYMBOL_COUNTER_INTR_7_DEFAULT    0x00000000

/***************************************************************************
 *CPU_MASK_STATUS - CPU interrupt Mask Status Register
 ***************************************************************************/
/* SYMCNT7_L2 :: CPU_MASK_STATUS :: RSVD [31:01] */
#define BCHP_SYMCNT7_L2_CPU_MASK_STATUS_RSVD_MASK                  0xfffffffe
#define BCHP_SYMCNT7_L2_CPU_MASK_STATUS_RSVD_SHIFT                 1
#define BCHP_SYMCNT7_L2_CPU_MASK_STATUS_RSVD_DEFAULT               0x000000ff

/* SYMCNT7_L2 :: CPU_MASK_STATUS :: SYMBOL_COUNTER_INTR_7 [00:00] */
#define BCHP_SYMCNT7_L2_CPU_MASK_STATUS_SYMBOL_COUNTER_INTR_7_MASK 0x00000001
#define BCHP_SYMCNT7_L2_CPU_MASK_STATUS_SYMBOL_COUNTER_INTR_7_SHIFT 0
#define BCHP_SYMCNT7_L2_CPU_MASK_STATUS_SYMBOL_COUNTER_INTR_7_DEFAULT 0x00000001

/***************************************************************************
 *CPU_MASK_SET - CPU interrupt Mask Set Register
 ***************************************************************************/
/* SYMCNT7_L2 :: CPU_MASK_SET :: RSVD [31:01] */
#define BCHP_SYMCNT7_L2_CPU_MASK_SET_RSVD_MASK                     0xfffffffe
#define BCHP_SYMCNT7_L2_CPU_MASK_SET_RSVD_SHIFT                    1
#define BCHP_SYMCNT7_L2_CPU_MASK_SET_RSVD_DEFAULT                  0x000000ff

/* SYMCNT7_L2 :: CPU_MASK_SET :: SYMBOL_COUNTER_INTR_7 [00:00] */
#define BCHP_SYMCNT7_L2_CPU_MASK_SET_SYMBOL_COUNTER_INTR_7_MASK    0x00000001
#define BCHP_SYMCNT7_L2_CPU_MASK_SET_SYMBOL_COUNTER_INTR_7_SHIFT   0
#define BCHP_SYMCNT7_L2_CPU_MASK_SET_SYMBOL_COUNTER_INTR_7_DEFAULT 0x00000001

/***************************************************************************
 *CPU_MASK_CLEAR - CPU interrupt Mask Clear Register
 ***************************************************************************/
/* SYMCNT7_L2 :: CPU_MASK_CLEAR :: RSVD [31:01] */
#define BCHP_SYMCNT7_L2_CPU_MASK_CLEAR_RSVD_MASK                   0xfffffffe
#define BCHP_SYMCNT7_L2_CPU_MASK_CLEAR_RSVD_SHIFT                  1
#define BCHP_SYMCNT7_L2_CPU_MASK_CLEAR_RSVD_DEFAULT                0x000000ff

/* SYMCNT7_L2 :: CPU_MASK_CLEAR :: SYMBOL_COUNTER_INTR_7 [00:00] */
#define BCHP_SYMCNT7_L2_CPU_MASK_CLEAR_SYMBOL_COUNTER_INTR_7_MASK  0x00000001
#define BCHP_SYMCNT7_L2_CPU_MASK_CLEAR_SYMBOL_COUNTER_INTR_7_SHIFT 0
#define BCHP_SYMCNT7_L2_CPU_MASK_CLEAR_SYMBOL_COUNTER_INTR_7_DEFAULT 0x00000001

#endif /* #ifndef BCHP_SYMCNT7_L2_H__ */

/* End of File */

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
 * Date:           Generated on              Mon Sep 23 09:50:32 2013
 *                 Full Compile MD5 Checksum fcccce298b546dd6a1f4cbad288478da
 *                   (minus title and desc)  
 *                 MD5 Checksum              211556602e37a33262598b3d5eeba81c
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

#ifndef BCHP_RAAGA_DSP_MISC_H__
#define BCHP_RAAGA_DSP_MISC_H__

/***************************************************************************
 *RAAGA_DSP_MISC - Raaga DSP MISC Registers
 ***************************************************************************/
#define BCHP_RAAGA_DSP_MISC_REVISION             0x00c20000 /* Audio DSP System Revision Register */
#define BCHP_RAAGA_DSP_MISC_SOFT_INIT            0x00c20004 /* Audio DSP System Soft Reset Control */
#define BCHP_RAAGA_DSP_MISC_CORE_ID              0x00c20008 /* DSP Core ID */
#define BCHP_RAAGA_DSP_MISC_PROC_ID              0x00c2000c /* DSP Processor ID */
#define BCHP_RAAGA_DSP_MISC_FP_INTG_TEST_0       0x00c20010 /* FP Integration test register */
#define BCHP_RAAGA_DSP_MISC_FP_INTG_TEST_1       0x00c20014 /* FP Integration test register */
#define BCHP_RAAGA_DSP_MISC_FP_INTG_TEST_2       0x00c20018 /* FP Integration test register */
#define BCHP_RAAGA_DSP_MISC_FP_INTG_TEST_3       0x00c2001c /* FP Integration test register */
#define BCHP_RAAGA_DSP_MISC_SCRATCH_0            0x00c20020 /* Raaga Scratch register */
#define BCHP_RAAGA_DSP_MISC_SCRATCH_1            0x00c20024 /* Raaga Scratch register */
#define BCHP_RAAGA_DSP_MISC_SCRATCH_2            0x00c20028 /* Raaga Scratch register */
#define BCHP_RAAGA_DSP_MISC_SCRATCH_3            0x00c2002c /* Raaga Scratch register */
#define BCHP_RAAGA_DSP_MISC_MBIST_TM             0x00c20030 /* Audio DSP System MBIST Control */
#define BCHP_RAAGA_DSP_MISC_MISC_DBG_STATUS      0x00c2040c /* Misc module status reg */
#define BCHP_RAAGA_DSP_MISC_SOFTBIST_STATUS      0x00c2044c /* Softbist Status reg */

/***************************************************************************
 *REVISION - Audio DSP System Revision Register
 ***************************************************************************/
/* RAAGA_DSP_MISC :: REVISION :: reserved0 [31:16] */
#define BCHP_RAAGA_DSP_MISC_REVISION_reserved0_MASK                0xffff0000
#define BCHP_RAAGA_DSP_MISC_REVISION_reserved0_SHIFT               16

/* RAAGA_DSP_MISC :: REVISION :: MAJOR [15:08] */
#define BCHP_RAAGA_DSP_MISC_REVISION_MAJOR_MASK                    0x0000ff00
#define BCHP_RAAGA_DSP_MISC_REVISION_MAJOR_SHIFT                   8
#define BCHP_RAAGA_DSP_MISC_REVISION_MAJOR_DEFAULT                 0x00000016

/* RAAGA_DSP_MISC :: REVISION :: MINOR [07:00] */
#define BCHP_RAAGA_DSP_MISC_REVISION_MINOR_MASK                    0x000000ff
#define BCHP_RAAGA_DSP_MISC_REVISION_MINOR_SHIFT                   0
#define BCHP_RAAGA_DSP_MISC_REVISION_MINOR_DEFAULT                 0x00000010

/***************************************************************************
 *SOFT_INIT - Audio DSP System Soft Reset Control
 ***************************************************************************/
/* RAAGA_DSP_MISC :: SOFT_INIT :: reserved0 [31:17] */
#define BCHP_RAAGA_DSP_MISC_SOFT_INIT_reserved0_MASK               0xfffe0000
#define BCHP_RAAGA_DSP_MISC_SOFT_INIT_reserved0_SHIFT              17

/* RAAGA_DSP_MISC :: SOFT_INIT :: CLIENT_INIT_DONE [16:16] */
#define BCHP_RAAGA_DSP_MISC_SOFT_INIT_CLIENT_INIT_DONE_MASK        0x00010000
#define BCHP_RAAGA_DSP_MISC_SOFT_INIT_CLIENT_INIT_DONE_SHIFT       16
#define BCHP_RAAGA_DSP_MISC_SOFT_INIT_CLIENT_INIT_DONE_DEFAULT     0x00000000

/* RAAGA_DSP_MISC :: SOFT_INIT :: reserved1 [15:10] */
#define BCHP_RAAGA_DSP_MISC_SOFT_INIT_reserved1_MASK               0x0000fc00
#define BCHP_RAAGA_DSP_MISC_SOFT_INIT_reserved1_SHIFT              10

/* RAAGA_DSP_MISC :: SOFT_INIT :: DO_CLIENT_INIT [09:09] */
#define BCHP_RAAGA_DSP_MISC_SOFT_INIT_DO_CLIENT_INIT_MASK          0x00000200
#define BCHP_RAAGA_DSP_MISC_SOFT_INIT_DO_CLIENT_INIT_SHIFT         9
#define BCHP_RAAGA_DSP_MISC_SOFT_INIT_DO_CLIENT_INIT_DEFAULT       0x00000000

/* RAAGA_DSP_MISC :: SOFT_INIT :: DO_SW_INIT [08:08] */
#define BCHP_RAAGA_DSP_MISC_SOFT_INIT_DO_SW_INIT_MASK              0x00000100
#define BCHP_RAAGA_DSP_MISC_SOFT_INIT_DO_SW_INIT_SHIFT             8
#define BCHP_RAAGA_DSP_MISC_SOFT_INIT_DO_SW_INIT_DEFAULT           0x00000000

/* RAAGA_DSP_MISC :: SOFT_INIT :: reserved2 [07:02] */
#define BCHP_RAAGA_DSP_MISC_SOFT_INIT_reserved2_MASK               0x000000fc
#define BCHP_RAAGA_DSP_MISC_SOFT_INIT_reserved2_SHIFT              2

/* RAAGA_DSP_MISC :: SOFT_INIT :: INIT_PROC_B [01:01] */
#define BCHP_RAAGA_DSP_MISC_SOFT_INIT_INIT_PROC_B_MASK             0x00000002
#define BCHP_RAAGA_DSP_MISC_SOFT_INIT_INIT_PROC_B_SHIFT            1
#define BCHP_RAAGA_DSP_MISC_SOFT_INIT_INIT_PROC_B_DEFAULT          0x00000000

/* RAAGA_DSP_MISC :: SOFT_INIT :: reserved3 [00:00] */
#define BCHP_RAAGA_DSP_MISC_SOFT_INIT_reserved3_MASK               0x00000001
#define BCHP_RAAGA_DSP_MISC_SOFT_INIT_reserved3_SHIFT              0

/***************************************************************************
 *CORE_ID - DSP Core ID
 ***************************************************************************/
/* RAAGA_DSP_MISC :: CORE_ID :: reserved0 [31:08] */
#define BCHP_RAAGA_DSP_MISC_CORE_ID_reserved0_MASK                 0xffffff00
#define BCHP_RAAGA_DSP_MISC_CORE_ID_reserved0_SHIFT                8

/* RAAGA_DSP_MISC :: CORE_ID :: ID [07:00] */
#define BCHP_RAAGA_DSP_MISC_CORE_ID_ID_MASK                        0x000000ff
#define BCHP_RAAGA_DSP_MISC_CORE_ID_ID_SHIFT                       0

/***************************************************************************
 *PROC_ID - DSP Processor ID
 ***************************************************************************/
/* RAAGA_DSP_MISC :: PROC_ID :: reserved0 [31:08] */
#define BCHP_RAAGA_DSP_MISC_PROC_ID_reserved0_MASK                 0xffffff00
#define BCHP_RAAGA_DSP_MISC_PROC_ID_reserved0_SHIFT                8

/* RAAGA_DSP_MISC :: PROC_ID :: ID [07:00] */
#define BCHP_RAAGA_DSP_MISC_PROC_ID_ID_MASK                        0x000000ff
#define BCHP_RAAGA_DSP_MISC_PROC_ID_ID_SHIFT                       0

/***************************************************************************
 *FP_INTG_TEST_0 - FP Integration test register
 ***************************************************************************/
/* RAAGA_DSP_MISC :: FP_INTG_TEST_0 :: VALUE [31:00] */
#define BCHP_RAAGA_DSP_MISC_FP_INTG_TEST_0_VALUE_MASK              0xffffffff
#define BCHP_RAAGA_DSP_MISC_FP_INTG_TEST_0_VALUE_SHIFT             0
#define BCHP_RAAGA_DSP_MISC_FP_INTG_TEST_0_VALUE_DEFAULT           0x00000000

/***************************************************************************
 *FP_INTG_TEST_1 - FP Integration test register
 ***************************************************************************/
/* RAAGA_DSP_MISC :: FP_INTG_TEST_1 :: VALUE [31:00] */
#define BCHP_RAAGA_DSP_MISC_FP_INTG_TEST_1_VALUE_MASK              0xffffffff
#define BCHP_RAAGA_DSP_MISC_FP_INTG_TEST_1_VALUE_SHIFT             0
#define BCHP_RAAGA_DSP_MISC_FP_INTG_TEST_1_VALUE_DEFAULT           0x00000000

/***************************************************************************
 *FP_INTG_TEST_2 - FP Integration test register
 ***************************************************************************/
/* RAAGA_DSP_MISC :: FP_INTG_TEST_2 :: VALUE [31:00] */
#define BCHP_RAAGA_DSP_MISC_FP_INTG_TEST_2_VALUE_MASK              0xffffffff
#define BCHP_RAAGA_DSP_MISC_FP_INTG_TEST_2_VALUE_SHIFT             0
#define BCHP_RAAGA_DSP_MISC_FP_INTG_TEST_2_VALUE_DEFAULT           0x00000000

/***************************************************************************
 *FP_INTG_TEST_3 - FP Integration test register
 ***************************************************************************/
/* RAAGA_DSP_MISC :: FP_INTG_TEST_3 :: VALUE [31:00] */
#define BCHP_RAAGA_DSP_MISC_FP_INTG_TEST_3_VALUE_MASK              0xffffffff
#define BCHP_RAAGA_DSP_MISC_FP_INTG_TEST_3_VALUE_SHIFT             0
#define BCHP_RAAGA_DSP_MISC_FP_INTG_TEST_3_VALUE_DEFAULT           0x00000000

/***************************************************************************
 *SCRATCH_0 - Raaga Scratch register
 ***************************************************************************/
/* RAAGA_DSP_MISC :: SCRATCH_0 :: VALUE [31:00] */
#define BCHP_RAAGA_DSP_MISC_SCRATCH_0_VALUE_MASK                   0xffffffff
#define BCHP_RAAGA_DSP_MISC_SCRATCH_0_VALUE_SHIFT                  0
#define BCHP_RAAGA_DSP_MISC_SCRATCH_0_VALUE_DEFAULT                0x00000000

/***************************************************************************
 *SCRATCH_1 - Raaga Scratch register
 ***************************************************************************/
/* RAAGA_DSP_MISC :: SCRATCH_1 :: VALUE [31:00] */
#define BCHP_RAAGA_DSP_MISC_SCRATCH_1_VALUE_MASK                   0xffffffff
#define BCHP_RAAGA_DSP_MISC_SCRATCH_1_VALUE_SHIFT                  0
#define BCHP_RAAGA_DSP_MISC_SCRATCH_1_VALUE_DEFAULT                0x00000000

/***************************************************************************
 *SCRATCH_2 - Raaga Scratch register
 ***************************************************************************/
/* RAAGA_DSP_MISC :: SCRATCH_2 :: VALUE [31:00] */
#define BCHP_RAAGA_DSP_MISC_SCRATCH_2_VALUE_MASK                   0xffffffff
#define BCHP_RAAGA_DSP_MISC_SCRATCH_2_VALUE_SHIFT                  0
#define BCHP_RAAGA_DSP_MISC_SCRATCH_2_VALUE_DEFAULT                0x00000000

/***************************************************************************
 *SCRATCH_3 - Raaga Scratch register
 ***************************************************************************/
/* RAAGA_DSP_MISC :: SCRATCH_3 :: VALUE [31:00] */
#define BCHP_RAAGA_DSP_MISC_SCRATCH_3_VALUE_MASK                   0xffffffff
#define BCHP_RAAGA_DSP_MISC_SCRATCH_3_VALUE_SHIFT                  0
#define BCHP_RAAGA_DSP_MISC_SCRATCH_3_VALUE_DEFAULT                0x00000000

/***************************************************************************
 *MBIST_TM - Audio DSP System MBIST Control
 ***************************************************************************/
/* RAAGA_DSP_MISC :: MBIST_TM :: reserved0 [31:02] */
#define BCHP_RAAGA_DSP_MISC_MBIST_TM_reserved0_MASK                0xfffffffc
#define BCHP_RAAGA_DSP_MISC_MBIST_TM_reserved0_SHIFT               2

/* RAAGA_DSP_MISC :: MBIST_TM :: FP_TST_TM [01:00] */
#define BCHP_RAAGA_DSP_MISC_MBIST_TM_FP_TST_TM_MASK                0x00000003
#define BCHP_RAAGA_DSP_MISC_MBIST_TM_FP_TST_TM_SHIFT               0
#define BCHP_RAAGA_DSP_MISC_MBIST_TM_FP_TST_TM_DEFAULT             0x00000000

/***************************************************************************
 *MISC_DBG_STATUS - Misc module status reg
 ***************************************************************************/
/* RAAGA_DSP_MISC :: MISC_DBG_STATUS :: reserved0 [31:04] */
#define BCHP_RAAGA_DSP_MISC_MISC_DBG_STATUS_reserved0_MASK         0xfffffff0
#define BCHP_RAAGA_DSP_MISC_MISC_DBG_STATUS_reserved0_SHIFT        4

/* RAAGA_DSP_MISC :: MISC_DBG_STATUS :: PMEM_STATE [03:00] */
#define BCHP_RAAGA_DSP_MISC_MISC_DBG_STATUS_PMEM_STATE_MASK        0x0000000f
#define BCHP_RAAGA_DSP_MISC_MISC_DBG_STATUS_PMEM_STATE_SHIFT       0

/***************************************************************************
 *SOFTBIST_STATUS - Softbist Status reg
 ***************************************************************************/
/* RAAGA_DSP_MISC :: SOFTBIST_STATUS :: reserved0 [31:02] */
#define BCHP_RAAGA_DSP_MISC_SOFTBIST_STATUS_reserved0_MASK         0xfffffffc
#define BCHP_RAAGA_DSP_MISC_SOFTBIST_STATUS_reserved0_SHIFT        2

/* RAAGA_DSP_MISC :: SOFTBIST_STATUS :: SOFTBIST_PASS [01:01] */
#define BCHP_RAAGA_DSP_MISC_SOFTBIST_STATUS_SOFTBIST_PASS_MASK     0x00000002
#define BCHP_RAAGA_DSP_MISC_SOFTBIST_STATUS_SOFTBIST_PASS_SHIFT    1

/* RAAGA_DSP_MISC :: SOFTBIST_STATUS :: SOFTBIST_DONE [00:00] */
#define BCHP_RAAGA_DSP_MISC_SOFTBIST_STATUS_SOFTBIST_DONE_MASK     0x00000001
#define BCHP_RAAGA_DSP_MISC_SOFTBIST_STATUS_SOFTBIST_DONE_SHIFT    0

#endif /* #ifndef BCHP_RAAGA_DSP_MISC_H__ */

/* End of File */

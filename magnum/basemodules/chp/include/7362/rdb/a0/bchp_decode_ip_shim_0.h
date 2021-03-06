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
 * Date:           Generated on         Thu Apr 18 11:11:12 2013
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

#ifndef BCHP_DECODE_IP_SHIM_0_H__
#define BCHP_DECODE_IP_SHIM_0_H__

/***************************************************************************
 *DECODE_IP_SHIM_0 - 0 AVD Shim Registers
 ***************************************************************************/
#define BCHP_DECODE_IP_SHIM_0_STC0_REG           0x00060000 /* Serial Time Stamp PTS register */
#define BCHP_DECODE_IP_SHIM_0_STC1_REG           0x00060004 /* Serial Time Stamp PTS register */
#define BCHP_DECODE_IP_SHIM_0_ENDIAN_REG         0x00060008 /* Stream Endian Control Register */
#define BCHP_DECODE_IP_SHIM_0_BVN_INT_REG        0x0006000c /* BVN Interrupt Register */
#define BCHP_DECODE_IP_SHIM_0_CPU_ID             0x00060010 /* CPU ID Regsiter */
#define BCHP_DECODE_IP_SHIM_0_REG_AVD_CLK_GATE   0x00060014 /* Clock Gate Register */
#define BCHP_DECODE_IP_SHIM_0_PFRI_REG           0x00060018 /* PFRI Register */
#define BCHP_DECODE_IP_SHIM_0_SCB_REG            0x0006001c /* SCB Register */
#define BCHP_DECODE_IP_SHIM_0_SW_RESET_REG       0x00060020 /* SW RESET Register */
#define BCHP_DECODE_IP_SHIM_0_INT_PAGE_REG       0x00060028 /* Interrupt Page Register */
#define BCHP_DECODE_IP_SHIM_0_DEBUG_REG          0x00060030 /* DEBUG_REG */
#define BCHP_DECODE_IP_SHIM_0_SVC_BLD_STORE_MODE_REG 0x00060034 /* BLD_STORE_MODE_REG */
#define BCHP_DECODE_IP_SHIM_0_STC2_REG           0x00060050 /* Serial Time Stamp PTS register */
#define BCHP_DECODE_IP_SHIM_0_STC3_REG           0x00060054 /* Serial Time Stamp PTS register */
#define BCHP_DECODE_IP_SHIM_0_STC4_REG           0x00060058 /* Serial Time Stamp PTS register */
#define BCHP_DECODE_IP_SHIM_0_STC5_REG           0x0006005c /* Serial Time Stamp PTS register */
#define BCHP_DECODE_IP_SHIM_0_STC6_REG           0x00060060 /* Serial Time Stamp PTS register */
#define BCHP_DECODE_IP_SHIM_0_STC7_REG           0x00060064 /* Serial Time Stamp PTS register */
#define BCHP_DECODE_IP_SHIM_0_SCB2_REG           0x00060068 /* SCB2 Register */
#define BCHP_DECODE_IP_SHIM_0_HST_SCRATCH_RAM_ADDR_REG 0x00060070 /* Scratch RAM Address */
#define BCHP_DECODE_IP_SHIM_0_ARC_SCRATCH_RAM_ADDR_REG 0x00060074 /* Scratch RAM Address */
#define BCHP_DECODE_IP_SHIM_0_HST_SCRATCH_RAM_DATA_REG 0x00060078 /* Scratch RAM Data */
#define BCHP_DECODE_IP_SHIM_0_ARC_SCRATCH_RAM_DATA_REG 0x0006007c /* Scratch RAM Data */
#define BCHP_DECODE_IP_SHIM_0_SOFTSHUTDOWN_CTRL_REG 0x00060080 /* SOFTSHUTDOWN_CTRL_REG */
#define BCHP_DECODE_IP_SHIM_0_OTP_CTL_REG        0x00060084 /* OTP Control Bits */

/***************************************************************************
 *STC0_REG - Serial Time Stamp PTS register
 ***************************************************************************/
/* DECODE_IP_SHIM_0 :: STC0_REG :: STC [31:00] */
#define BCHP_DECODE_IP_SHIM_0_STC0_REG_STC_MASK                    0xffffffff
#define BCHP_DECODE_IP_SHIM_0_STC0_REG_STC_SHIFT                   0

/***************************************************************************
 *STC1_REG - Serial Time Stamp PTS register
 ***************************************************************************/
/* DECODE_IP_SHIM_0 :: STC1_REG :: STC [31:00] */
#define BCHP_DECODE_IP_SHIM_0_STC1_REG_STC_MASK                    0xffffffff
#define BCHP_DECODE_IP_SHIM_0_STC1_REG_STC_SHIFT                   0

/***************************************************************************
 *ENDIAN_REG - Stream Endian Control Register
 ***************************************************************************/
/* DECODE_IP_SHIM_0 :: ENDIAN_REG :: reserved0 [31:01] */
#define BCHP_DECODE_IP_SHIM_0_ENDIAN_REG_reserved0_MASK            0xfffffffe
#define BCHP_DECODE_IP_SHIM_0_ENDIAN_REG_reserved0_SHIFT           1

/* DECODE_IP_SHIM_0 :: ENDIAN_REG :: B1L0 [00:00] */
#define BCHP_DECODE_IP_SHIM_0_ENDIAN_REG_B1L0_MASK                 0x00000001
#define BCHP_DECODE_IP_SHIM_0_ENDIAN_REG_B1L0_SHIFT                0

/***************************************************************************
 *BVN_INT_REG - BVN Interrupt Register
 ***************************************************************************/
/* DECODE_IP_SHIM_0 :: BVN_INT_REG :: reserved0 [31:02] */
#define BCHP_DECODE_IP_SHIM_0_BVN_INT_REG_reserved0_MASK           0xfffffffc
#define BCHP_DECODE_IP_SHIM_0_BVN_INT_REG_reserved0_SHIFT          2

/* DECODE_IP_SHIM_0 :: BVN_INT_REG :: desc [01:01] */
#define BCHP_DECODE_IP_SHIM_0_BVN_INT_REG_desc_MASK                0x00000002
#define BCHP_DECODE_IP_SHIM_0_BVN_INT_REG_desc_SHIFT               1

/* DECODE_IP_SHIM_0 :: BVN_INT_REG :: trigger [00:00] */
#define BCHP_DECODE_IP_SHIM_0_BVN_INT_REG_trigger_MASK             0x00000001
#define BCHP_DECODE_IP_SHIM_0_BVN_INT_REG_trigger_SHIFT            0

/***************************************************************************
 *CPU_ID - CPU ID Regsiter
 ***************************************************************************/
/* DECODE_IP_SHIM_0 :: CPU_ID :: reserved0 [31:25] */
#define BCHP_DECODE_IP_SHIM_0_CPU_ID_reserved0_MASK                0xfe000000
#define BCHP_DECODE_IP_SHIM_0_CPU_ID_reserved0_SHIFT               25

/* DECODE_IP_SHIM_0 :: CPU_ID :: BLD_ID [24:24] */
#define BCHP_DECODE_IP_SHIM_0_CPU_ID_BLD_ID_MASK                   0x01000000
#define BCHP_DECODE_IP_SHIM_0_CPU_ID_BLD_ID_SHIFT                  24

/* DECODE_IP_SHIM_0 :: CPU_ID :: reserved1 [23:17] */
#define BCHP_DECODE_IP_SHIM_0_CPU_ID_reserved1_MASK                0x00fe0000
#define BCHP_DECODE_IP_SHIM_0_CPU_ID_reserved1_SHIFT               17

/* DECODE_IP_SHIM_0 :: CPU_ID :: AVD_ID [16:16] */
#define BCHP_DECODE_IP_SHIM_0_CPU_ID_AVD_ID_MASK                   0x00010000
#define BCHP_DECODE_IP_SHIM_0_CPU_ID_AVD_ID_SHIFT                  16

/* DECODE_IP_SHIM_0 :: CPU_ID :: ILCPU_ID [15:08] */
#define BCHP_DECODE_IP_SHIM_0_CPU_ID_ILCPU_ID_MASK                 0x0000ff00
#define BCHP_DECODE_IP_SHIM_0_CPU_ID_ILCPU_ID_SHIFT                8

/* DECODE_IP_SHIM_0 :: CPU_ID :: OLCPU_ID [07:00] */
#define BCHP_DECODE_IP_SHIM_0_CPU_ID_OLCPU_ID_MASK                 0x000000ff
#define BCHP_DECODE_IP_SHIM_0_CPU_ID_OLCPU_ID_SHIFT                0

/***************************************************************************
 *REG_AVD_CLK_GATE - Clock Gate Register
 ***************************************************************************/
/* DECODE_IP_SHIM_0 :: REG_AVD_CLK_GATE :: reserved0 [31:11] */
#define BCHP_DECODE_IP_SHIM_0_REG_AVD_CLK_GATE_reserved0_MASK      0xfffff800
#define BCHP_DECODE_IP_SHIM_0_REG_AVD_CLK_GATE_reserved0_SHIFT     11

/* DECODE_IP_SHIM_0 :: REG_AVD_CLK_GATE :: clk_bld [10:10] */
#define BCHP_DECODE_IP_SHIM_0_REG_AVD_CLK_GATE_clk_bld_MASK        0x00000400
#define BCHP_DECODE_IP_SHIM_0_REG_AVD_CLK_GATE_clk_bld_SHIFT       10
#define BCHP_DECODE_IP_SHIM_0_REG_AVD_CLK_GATE_clk_bld_DEFAULT     0x00000000

/* DECODE_IP_SHIM_0 :: REG_AVD_CLK_GATE :: clk_ka [09:09] */
#define BCHP_DECODE_IP_SHIM_0_REG_AVD_CLK_GATE_clk_ka_MASK         0x00000200
#define BCHP_DECODE_IP_SHIM_0_REG_AVD_CLK_GATE_clk_ka_SHIFT        9
#define BCHP_DECODE_IP_SHIM_0_REG_AVD_CLK_GATE_clk_ka_DEFAULT      0x00000000

/* DECODE_IP_SHIM_0 :: REG_AVD_CLK_GATE :: clk_ils [08:08] */
#define BCHP_DECODE_IP_SHIM_0_REG_AVD_CLK_GATE_clk_ils_MASK        0x00000100
#define BCHP_DECODE_IP_SHIM_0_REG_AVD_CLK_GATE_clk_ils_SHIFT       8
#define BCHP_DECODE_IP_SHIM_0_REG_AVD_CLK_GATE_clk_ils_DEFAULT     0x00000000

/* DECODE_IP_SHIM_0 :: REG_AVD_CLK_GATE :: clk_cab [07:07] */
#define BCHP_DECODE_IP_SHIM_0_REG_AVD_CLK_GATE_clk_cab_MASK        0x00000080
#define BCHP_DECODE_IP_SHIM_0_REG_AVD_CLK_GATE_clk_cab_SHIFT       7
#define BCHP_DECODE_IP_SHIM_0_REG_AVD_CLK_GATE_clk_cab_DEFAULT     0x00000000

/* DECODE_IP_SHIM_0 :: REG_AVD_CLK_GATE :: clk_intra [06:06] */
#define BCHP_DECODE_IP_SHIM_0_REG_AVD_CLK_GATE_clk_intra_MASK      0x00000040
#define BCHP_DECODE_IP_SHIM_0_REG_AVD_CLK_GATE_clk_intra_SHIFT     6
#define BCHP_DECODE_IP_SHIM_0_REG_AVD_CLK_GATE_clk_intra_DEFAULT   0x00000000

/* DECODE_IP_SHIM_0 :: REG_AVD_CLK_GATE :: clk_vframe [05:05] */
#define BCHP_DECODE_IP_SHIM_0_REG_AVD_CLK_GATE_clk_vframe_MASK     0x00000020
#define BCHP_DECODE_IP_SHIM_0_REG_AVD_CLK_GATE_clk_vframe_SHIFT    5
#define BCHP_DECODE_IP_SHIM_0_REG_AVD_CLK_GATE_clk_vframe_DEFAULT  0x00000000

/* DECODE_IP_SHIM_0 :: REG_AVD_CLK_GATE :: clk_avc [04:04] */
#define BCHP_DECODE_IP_SHIM_0_REG_AVD_CLK_GATE_clk_avc_MASK        0x00000010
#define BCHP_DECODE_IP_SHIM_0_REG_AVD_CLK_GATE_clk_avc_SHIFT       4
#define BCHP_DECODE_IP_SHIM_0_REG_AVD_CLK_GATE_clk_avc_DEFAULT     0x00000000

/* DECODE_IP_SHIM_0 :: REG_AVD_CLK_GATE :: clk_vc1 [03:03] */
#define BCHP_DECODE_IP_SHIM_0_REG_AVD_CLK_GATE_clk_vc1_MASK        0x00000008
#define BCHP_DECODE_IP_SHIM_0_REG_AVD_CLK_GATE_clk_vc1_SHIFT       3
#define BCHP_DECODE_IP_SHIM_0_REG_AVD_CLK_GATE_clk_vc1_DEFAULT     0x00000000

/* DECODE_IP_SHIM_0 :: REG_AVD_CLK_GATE :: clk_vc1_db [02:02] */
#define BCHP_DECODE_IP_SHIM_0_REG_AVD_CLK_GATE_clk_vc1_db_MASK     0x00000004
#define BCHP_DECODE_IP_SHIM_0_REG_AVD_CLK_GATE_clk_vc1_db_SHIFT    2
#define BCHP_DECODE_IP_SHIM_0_REG_AVD_CLK_GATE_clk_vc1_db_DEFAULT  0x00000000

/* DECODE_IP_SHIM_0 :: REG_AVD_CLK_GATE :: clk_mp4 [01:01] */
#define BCHP_DECODE_IP_SHIM_0_REG_AVD_CLK_GATE_clk_mp4_MASK        0x00000002
#define BCHP_DECODE_IP_SHIM_0_REG_AVD_CLK_GATE_clk_mp4_SHIFT       1
#define BCHP_DECODE_IP_SHIM_0_REG_AVD_CLK_GATE_clk_mp4_DEFAULT     0x00000000

/* DECODE_IP_SHIM_0 :: REG_AVD_CLK_GATE :: clk_mp2 [00:00] */
#define BCHP_DECODE_IP_SHIM_0_REG_AVD_CLK_GATE_clk_mp2_MASK        0x00000001
#define BCHP_DECODE_IP_SHIM_0_REG_AVD_CLK_GATE_clk_mp2_SHIFT       0
#define BCHP_DECODE_IP_SHIM_0_REG_AVD_CLK_GATE_clk_mp2_DEFAULT     0x00000000

/***************************************************************************
 *PFRI_REG - PFRI Register
 ***************************************************************************/
/* DECODE_IP_SHIM_0 :: PFRI_REG :: reserved0 [31:30] */
#define BCHP_DECODE_IP_SHIM_0_PFRI_REG_reserved0_MASK              0xc0000000
#define BCHP_DECODE_IP_SHIM_0_PFRI_REG_reserved0_SHIFT             30

/* DECODE_IP_SHIM_0 :: PFRI_REG :: Internal0_MBZ [29:29] */
#define BCHP_DECODE_IP_SHIM_0_PFRI_REG_Internal0_MBZ_MASK          0x20000000
#define BCHP_DECODE_IP_SHIM_0_PFRI_REG_Internal0_MBZ_SHIFT         29

/* DECODE_IP_SHIM_0 :: PFRI_REG :: SCB_status_client [28:26] */
#define BCHP_DECODE_IP_SHIM_0_PFRI_REG_SCB_status_client_MASK      0x1c000000
#define BCHP_DECODE_IP_SHIM_0_PFRI_REG_SCB_status_client_SHIFT     26

/* DECODE_IP_SHIM_0 :: PFRI_REG :: SCB_debug_select [25:24] */
#define BCHP_DECODE_IP_SHIM_0_PFRI_REG_SCB_debug_select_MASK       0x03000000
#define BCHP_DECODE_IP_SHIM_0_PFRI_REG_SCB_debug_select_SHIFT      24

/* DECODE_IP_SHIM_0 :: PFRI_REG :: reserved1 [23:17] */
#define BCHP_DECODE_IP_SHIM_0_PFRI_REG_reserved1_MASK              0x00fe0000
#define BCHP_DECODE_IP_SHIM_0_PFRI_REG_reserved1_SHIFT             17

/* DECODE_IP_SHIM_0 :: PFRI_REG :: SCB_ERROR [16:16] */
#define BCHP_DECODE_IP_SHIM_0_PFRI_REG_SCB_ERROR_MASK              0x00010000
#define BCHP_DECODE_IP_SHIM_0_PFRI_REG_SCB_ERROR_SHIFT             16

/* DECODE_IP_SHIM_0 :: PFRI_REG :: reserved2 [15:09] */
#define BCHP_DECODE_IP_SHIM_0_PFRI_REG_reserved2_MASK              0x0000fe00
#define BCHP_DECODE_IP_SHIM_0_PFRI_REG_reserved2_SHIFT             9

/* DECODE_IP_SHIM_0 :: PFRI_REG :: SCB_status_sel [08:08] */
#define BCHP_DECODE_IP_SHIM_0_PFRI_REG_SCB_status_sel_MASK         0x00000100
#define BCHP_DECODE_IP_SHIM_0_PFRI_REG_SCB_status_sel_SHIFT        8

/* DECODE_IP_SHIM_0 :: PFRI_REG :: reserved3 [07:06] */
#define BCHP_DECODE_IP_SHIM_0_PFRI_REG_reserved3_MASK              0x000000c0
#define BCHP_DECODE_IP_SHIM_0_PFRI_REG_reserved3_SHIFT             6

/* DECODE_IP_SHIM_0 :: PFRI_REG :: Rst_pfri_error [05:00] */
#define BCHP_DECODE_IP_SHIM_0_PFRI_REG_Rst_pfri_error_MASK         0x0000003f
#define BCHP_DECODE_IP_SHIM_0_PFRI_REG_Rst_pfri_error_SHIFT        0

/***************************************************************************
 *SCB_REG - SCB Register
 ***************************************************************************/
/* DECODE_IP_SHIM_0 :: SCB_REG :: SCBreg [31:00] */
#define BCHP_DECODE_IP_SHIM_0_SCB_REG_SCBreg_MASK                  0xffffffff
#define BCHP_DECODE_IP_SHIM_0_SCB_REG_SCBreg_SHIFT                 0

/***************************************************************************
 *SW_RESET_REG - SW RESET Register
 ***************************************************************************/
/* DECODE_IP_SHIM_0 :: SW_RESET_REG :: reserved0 [31:01] */
#define BCHP_DECODE_IP_SHIM_0_SW_RESET_REG_reserved0_MASK          0xfffffffe
#define BCHP_DECODE_IP_SHIM_0_SW_RESET_REG_reserved0_SHIFT         1

/* DECODE_IP_SHIM_0 :: SW_RESET_REG :: ILSI_reset [00:00] */
#define BCHP_DECODE_IP_SHIM_0_SW_RESET_REG_ILSI_reset_MASK         0x00000001
#define BCHP_DECODE_IP_SHIM_0_SW_RESET_REG_ILSI_reset_SHIFT        0

/***************************************************************************
 *INT_PAGE_REG - Interrupt Page Register
 ***************************************************************************/
/* DECODE_IP_SHIM_0 :: INT_PAGE_REG :: reserved0 [31:01] */
#define BCHP_DECODE_IP_SHIM_0_INT_PAGE_REG_reserved0_MASK          0xfffffffe
#define BCHP_DECODE_IP_SHIM_0_INT_PAGE_REG_reserved0_SHIFT         1

/* DECODE_IP_SHIM_0 :: INT_PAGE_REG :: ID [00:00] */
#define BCHP_DECODE_IP_SHIM_0_INT_PAGE_REG_ID_MASK                 0x00000001
#define BCHP_DECODE_IP_SHIM_0_INT_PAGE_REG_ID_SHIFT                0

/***************************************************************************
 *DEBUG_REG - DEBUG_REG
 ***************************************************************************/
/* DECODE_IP_SHIM_0 :: DEBUG_REG :: reserved0 [31:01] */
#define BCHP_DECODE_IP_SHIM_0_DEBUG_REG_reserved0_MASK             0xfffffffe
#define BCHP_DECODE_IP_SHIM_0_DEBUG_REG_reserved0_SHIFT            1

/* DECODE_IP_SHIM_0 :: DEBUG_REG :: Shim_debug [00:00] */
#define BCHP_DECODE_IP_SHIM_0_DEBUG_REG_Shim_debug_MASK            0x00000001
#define BCHP_DECODE_IP_SHIM_0_DEBUG_REG_Shim_debug_SHIFT           0

/***************************************************************************
 *SVC_BLD_STORE_MODE_REG - BLD_STORE_MODE_REG
 ***************************************************************************/
/* DECODE_IP_SHIM_0 :: SVC_BLD_STORE_MODE_REG :: reserved0 [31:02] */
#define BCHP_DECODE_IP_SHIM_0_SVC_BLD_STORE_MODE_REG_reserved0_MASK 0xfffffffc
#define BCHP_DECODE_IP_SHIM_0_SVC_BLD_STORE_MODE_REG_reserved0_SHIFT 2

/* DECODE_IP_SHIM_0 :: SVC_BLD_STORE_MODE_REG :: svc_ilace_fr_mode [01:01] */
#define BCHP_DECODE_IP_SHIM_0_SVC_BLD_STORE_MODE_REG_svc_ilace_fr_mode_MASK 0x00000002
#define BCHP_DECODE_IP_SHIM_0_SVC_BLD_STORE_MODE_REG_svc_ilace_fr_mode_SHIFT 1

/* DECODE_IP_SHIM_0 :: SVC_BLD_STORE_MODE_REG :: svc_ilace_half_height [00:00] */
#define BCHP_DECODE_IP_SHIM_0_SVC_BLD_STORE_MODE_REG_svc_ilace_half_height_MASK 0x00000001
#define BCHP_DECODE_IP_SHIM_0_SVC_BLD_STORE_MODE_REG_svc_ilace_half_height_SHIFT 0

/***************************************************************************
 *STC2_REG - Serial Time Stamp PTS register
 ***************************************************************************/
/* DECODE_IP_SHIM_0 :: STC2_REG :: STC [31:00] */
#define BCHP_DECODE_IP_SHIM_0_STC2_REG_STC_MASK                    0xffffffff
#define BCHP_DECODE_IP_SHIM_0_STC2_REG_STC_SHIFT                   0

/***************************************************************************
 *STC3_REG - Serial Time Stamp PTS register
 ***************************************************************************/
/* DECODE_IP_SHIM_0 :: STC3_REG :: STC [31:00] */
#define BCHP_DECODE_IP_SHIM_0_STC3_REG_STC_MASK                    0xffffffff
#define BCHP_DECODE_IP_SHIM_0_STC3_REG_STC_SHIFT                   0

/***************************************************************************
 *STC4_REG - Serial Time Stamp PTS register
 ***************************************************************************/
/* DECODE_IP_SHIM_0 :: STC4_REG :: STC [31:00] */
#define BCHP_DECODE_IP_SHIM_0_STC4_REG_STC_MASK                    0xffffffff
#define BCHP_DECODE_IP_SHIM_0_STC4_REG_STC_SHIFT                   0

/***************************************************************************
 *STC5_REG - Serial Time Stamp PTS register
 ***************************************************************************/
/* DECODE_IP_SHIM_0 :: STC5_REG :: STC [31:00] */
#define BCHP_DECODE_IP_SHIM_0_STC5_REG_STC_MASK                    0xffffffff
#define BCHP_DECODE_IP_SHIM_0_STC5_REG_STC_SHIFT                   0

/***************************************************************************
 *STC6_REG - Serial Time Stamp PTS register
 ***************************************************************************/
/* DECODE_IP_SHIM_0 :: STC6_REG :: STC [31:00] */
#define BCHP_DECODE_IP_SHIM_0_STC6_REG_STC_MASK                    0xffffffff
#define BCHP_DECODE_IP_SHIM_0_STC6_REG_STC_SHIFT                   0

/***************************************************************************
 *STC7_REG - Serial Time Stamp PTS register
 ***************************************************************************/
/* DECODE_IP_SHIM_0 :: STC7_REG :: STC [31:00] */
#define BCHP_DECODE_IP_SHIM_0_STC7_REG_STC_MASK                    0xffffffff
#define BCHP_DECODE_IP_SHIM_0_STC7_REG_STC_SHIFT                   0

/***************************************************************************
 *SCB2_REG - SCB2 Register
 ***************************************************************************/
/* DECODE_IP_SHIM_0 :: SCB2_REG :: SCBreg [31:00] */
#define BCHP_DECODE_IP_SHIM_0_SCB2_REG_SCBreg_MASK                 0xffffffff
#define BCHP_DECODE_IP_SHIM_0_SCB2_REG_SCBreg_SHIFT                0

/***************************************************************************
 *HST_SCRATCH_RAM_ADDR_REG - Scratch RAM Address
 ***************************************************************************/
/* DECODE_IP_SHIM_0 :: HST_SCRATCH_RAM_ADDR_REG :: reserved0 [31:07] */
#define BCHP_DECODE_IP_SHIM_0_HST_SCRATCH_RAM_ADDR_REG_reserved0_MASK 0xffffff80
#define BCHP_DECODE_IP_SHIM_0_HST_SCRATCH_RAM_ADDR_REG_reserved0_SHIFT 7

/* DECODE_IP_SHIM_0 :: HST_SCRATCH_RAM_ADDR_REG :: Addr [06:00] */
#define BCHP_DECODE_IP_SHIM_0_HST_SCRATCH_RAM_ADDR_REG_Addr_MASK   0x0000007f
#define BCHP_DECODE_IP_SHIM_0_HST_SCRATCH_RAM_ADDR_REG_Addr_SHIFT  0

/***************************************************************************
 *ARC_SCRATCH_RAM_ADDR_REG - Scratch RAM Address
 ***************************************************************************/
/* DECODE_IP_SHIM_0 :: ARC_SCRATCH_RAM_ADDR_REG :: reserved0 [31:07] */
#define BCHP_DECODE_IP_SHIM_0_ARC_SCRATCH_RAM_ADDR_REG_reserved0_MASK 0xffffff80
#define BCHP_DECODE_IP_SHIM_0_ARC_SCRATCH_RAM_ADDR_REG_reserved0_SHIFT 7

/* DECODE_IP_SHIM_0 :: ARC_SCRATCH_RAM_ADDR_REG :: Addr [06:00] */
#define BCHP_DECODE_IP_SHIM_0_ARC_SCRATCH_RAM_ADDR_REG_Addr_MASK   0x0000007f
#define BCHP_DECODE_IP_SHIM_0_ARC_SCRATCH_RAM_ADDR_REG_Addr_SHIFT  0

/***************************************************************************
 *HST_SCRATCH_RAM_DATA_REG - Scratch RAM Data
 ***************************************************************************/
/* DECODE_IP_SHIM_0 :: HST_SCRATCH_RAM_DATA_REG :: Data [31:00] */
#define BCHP_DECODE_IP_SHIM_0_HST_SCRATCH_RAM_DATA_REG_Data_MASK   0xffffffff
#define BCHP_DECODE_IP_SHIM_0_HST_SCRATCH_RAM_DATA_REG_Data_SHIFT  0

/***************************************************************************
 *ARC_SCRATCH_RAM_DATA_REG - Scratch RAM Data
 ***************************************************************************/
/* DECODE_IP_SHIM_0 :: ARC_SCRATCH_RAM_DATA_REG :: Data [31:00] */
#define BCHP_DECODE_IP_SHIM_0_ARC_SCRATCH_RAM_DATA_REG_Data_MASK   0xffffffff
#define BCHP_DECODE_IP_SHIM_0_ARC_SCRATCH_RAM_DATA_REG_Data_SHIFT  0

/***************************************************************************
 *SOFTSHUTDOWN_CTRL_REG - SOFTSHUTDOWN_CTRL_REG
 ***************************************************************************/
/* DECODE_IP_SHIM_0 :: SOFTSHUTDOWN_CTRL_REG :: reserved0 [31:01] */
#define BCHP_DECODE_IP_SHIM_0_SOFTSHUTDOWN_CTRL_REG_reserved0_MASK 0xfffffffe
#define BCHP_DECODE_IP_SHIM_0_SOFTSHUTDOWN_CTRL_REG_reserved0_SHIFT 1

/* DECODE_IP_SHIM_0 :: SOFTSHUTDOWN_CTRL_REG :: Enable [00:00] */
#define BCHP_DECODE_IP_SHIM_0_SOFTSHUTDOWN_CTRL_REG_Enable_MASK    0x00000001
#define BCHP_DECODE_IP_SHIM_0_SOFTSHUTDOWN_CTRL_REG_Enable_SHIFT   0
#define BCHP_DECODE_IP_SHIM_0_SOFTSHUTDOWN_CTRL_REG_Enable_DEFAULT 0x00000001

/***************************************************************************
 *OTP_CTL_REG - OTP Control Bits
 ***************************************************************************/
/* DECODE_IP_SHIM_0 :: OTP_CTL_REG :: reserved0 [31:01] */
#define BCHP_DECODE_IP_SHIM_0_OTP_CTL_REG_reserved0_MASK           0xfffffffe
#define BCHP_DECODE_IP_SHIM_0_OTP_CTL_REG_reserved0_SHIFT          1

/* DECODE_IP_SHIM_0 :: OTP_CTL_REG :: disable_RV9 [00:00] */
#define BCHP_DECODE_IP_SHIM_0_OTP_CTL_REG_disable_RV9_MASK         0x00000001
#define BCHP_DECODE_IP_SHIM_0_OTP_CTL_REG_disable_RV9_SHIFT        0

#endif /* #ifndef BCHP_DECODE_IP_SHIM_0_H__ */

/* End of File */

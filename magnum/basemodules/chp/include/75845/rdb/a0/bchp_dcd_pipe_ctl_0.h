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
 * Date:           Generated on               Tue Mar 10 17:57:37 2015
 *                 Full Compile MD5 Checksum  cac1d82e0ea60ac191e5eb0deb00af85
 *                     (minus title and desc)
 *                 MD5 Checksum               e839fde353a1ae191e2e40126f6846c9
 *
 * Compiled with:  RDB Utility                combo_header.pl
 *                 RDB.pm                     15839
 *                 unknown                    unknown
 *                 Perl Interpreter           5.008008
 *                 Operating System           linux
 *
 *
 ***************************************************************************/

#ifndef BCHP_DCD_PIPE_CTL_0_H__
#define BCHP_DCD_PIPE_CTL_0_H__

/***************************************************************************
 *DCD_PIPE_CTL_0
 ***************************************************************************/
#define BCHP_DCD_PIPE_CTL_0_CORE_CONFIG          0x00026000 /* [RO] Decoder Core configuration information */
#define BCHP_DCD_PIPE_CTL_0_AVD_CLK_GATE         0x00026004 /* [RW] pipe clock gating */
#define BCHP_DCD_PIPE_CTL_0_SW_RESET_REG         0x00026008 /* [XRW] Software reset register */
#define BCHP_DCD_PIPE_CTL_0_BLD_CLK_GATE         0x0002600c /* [RW] BLD pipe clock gating */
#define BCHP_DCD_PIPE_CTL_0_OUTPUT_CLIENT_SEL    0x00026010 /* [RW] Output SCB Client Selection */
#define BCHP_DCD_PIPE_CTL_0_MULTIPIPE_PFRI_ARB_CTL 0x00026014 /* [RW] Multipipe PFRI Arbiter Controls */
#define BCHP_DCD_PIPE_CTL_0_IL_RM2_ARB_TIMEOUT   0x00026024 /* [RW] RM2 ARBITER TIMEOUT Register */
#define BCHP_DCD_PIPE_CTL_0_IL_RM2_ARB_TIMEOUT_SEEN 0x00026028 /* [XRW] Arbiter timeout detected */
#define BCHP_DCD_PIPE_CTL_0_IPCOMM_L2R_TRANSMIT  0x00026030 /* [RW] Inter-CPU L2R Transmit Data Register */
#define BCHP_DCD_PIPE_CTL_0_IPCOMM_L2R_RECEIVE   0x00026034 /* [RO] Inter-CPU L2R Receive Data Register */
#define BCHP_DCD_PIPE_CTL_0_IPCOMM_L2R_STATUS    0x00026038 /* [RW] Inter-CPU L2R Status Register */
#define BCHP_DCD_PIPE_CTL_0_IPCOMM_R2L_TRANSMIT  0x0002603c /* [RW] Inter-CPU R2L Transmit Data Register */
#define BCHP_DCD_PIPE_CTL_0_IPCOMM_R2L_RECEIVE   0x00026040 /* [RO] Inter-CPU R2L Receive Data Register */
#define BCHP_DCD_PIPE_CTL_0_IPCOMM_R2L_STATUS    0x00026044 /* [RW] Inter-CPU R2L Status Register */
#define BCHP_DCD_PIPE_CTL_0_RECON_DEBUG_REG      0x00026080 /* [RW] Reconstructor debug register */
#define BCHP_DCD_PIPE_CTL_0_IXFORM_DEBUG_REG     0x00026084 /* [RW] Ixform debug register */
#define BCHP_DCD_PIPE_CTL_0_ILSI_DEBUG_REG       0x00026088 /* [RW] ILSI debug register */
#define BCHP_DCD_PIPE_CTL_0_SHIM_DEBUG_CTL       0x0002608c /* [RW] SCB Shim debug register */
#define BCHP_DCD_PIPE_CTL_0_SHIM_DEBUG_READ      0x00026090 /* [RO] SCB Shim debug register */
#define BCHP_DCD_PIPE_CTL_0_SHIM_ERROR_REG       0x00026094 /* [RO] SCB Shim error register */
#define BCHP_DCD_PIPE_CTL_0_DBLK_STRIPE_HEIGHT   0x00026100 /* [RW] Legacy deblock stripe height */
#define BCHP_DCD_PIPE_CTL_0_DBLK_STRIPE_WIDTH    0x00026180 /* [RW] Legacy deblock stripe width */
#define BCHP_DCD_PIPE_CTL_0_DBLK_PICT_BASE_LUMA  0x00026400 /* [WO] Legacy deblock luma picture base */
#define BCHP_DCD_PIPE_CTL_0_DBLK_PICT_BASE_CHROMA 0x00026404 /* [WO] Legacy deblock chroma picture base */

/***************************************************************************
 *CORE_CONFIG - Decoder Core configuration information
 ***************************************************************************/
/* DCD_PIPE_CTL_0 :: CORE_CONFIG :: reserved0 [31:20] */
#define BCHP_DCD_PIPE_CTL_0_CORE_CONFIG_reserved0_MASK             0xfff00000
#define BCHP_DCD_PIPE_CTL_0_CORE_CONFIG_reserved0_SHIFT            20

/* DCD_PIPE_CTL_0 :: CORE_CONFIG :: Pipe_Num [19:16] */
#define BCHP_DCD_PIPE_CTL_0_CORE_CONFIG_Pipe_Num_MASK              0x000f0000
#define BCHP_DCD_PIPE_CTL_0_CORE_CONFIG_Pipe_Num_SHIFT             16

/* DCD_PIPE_CTL_0 :: CORE_CONFIG :: HEVD_SplitLumaChroma [15:15] */
#define BCHP_DCD_PIPE_CTL_0_CORE_CONFIG_HEVD_SplitLumaChroma_MASK  0x00008000
#define BCHP_DCD_PIPE_CTL_0_CORE_CONFIG_HEVD_SplitLumaChroma_SHIFT 15

/* DCD_PIPE_CTL_0 :: CORE_CONFIG :: HEVD_dualpipe [14:14] */
#define BCHP_DCD_PIPE_CTL_0_CORE_CONFIG_HEVD_dualpipe_MASK         0x00004000
#define BCHP_DCD_PIPE_CTL_0_CORE_CONFIG_HEVD_dualpipe_SHIFT        14

/* DCD_PIPE_CTL_0 :: CORE_CONFIG :: HEVD_10bit [13:13] */
#define BCHP_DCD_PIPE_CTL_0_CORE_CONFIG_HEVD_10bit_MASK            0x00002000
#define BCHP_DCD_PIPE_CTL_0_CORE_CONFIG_HEVD_10bit_SHIFT           13

/* DCD_PIPE_CTL_0 :: CORE_CONFIG :: AVD_present [12:12] */
#define BCHP_DCD_PIPE_CTL_0_CORE_CONFIG_AVD_present_MASK           0x00001000
#define BCHP_DCD_PIPE_CTL_0_CORE_CONFIG_AVD_present_SHIFT          12

/* DCD_PIPE_CTL_0 :: CORE_CONFIG :: SID_present [11:11] */
#define BCHP_DCD_PIPE_CTL_0_CORE_CONFIG_SID_present_MASK           0x00000800
#define BCHP_DCD_PIPE_CTL_0_CORE_CONFIG_SID_present_SHIFT          11

/* DCD_PIPE_CTL_0 :: CORE_CONFIG :: HEVD_4K [10:10] */
#define BCHP_DCD_PIPE_CTL_0_CORE_CONFIG_HEVD_4K_MASK               0x00000400
#define BCHP_DCD_PIPE_CTL_0_CORE_CONFIG_HEVD_4K_SHIFT              10

/* DCD_PIPE_CTL_0 :: CORE_CONFIG :: HEVD_present [09:09] */
#define BCHP_DCD_PIPE_CTL_0_CORE_CONFIG_HEVD_present_MASK          0x00000200
#define BCHP_DCD_PIPE_CTL_0_CORE_CONFIG_HEVD_present_SHIFT         9

/* DCD_PIPE_CTL_0 :: CORE_CONFIG :: BLD_present [08:08] */
#define BCHP_DCD_PIPE_CTL_0_CORE_CONFIG_BLD_present_MASK           0x00000100
#define BCHP_DCD_PIPE_CTL_0_CORE_CONFIG_BLD_present_SHIFT          8

/* DCD_PIPE_CTL_0 :: CORE_CONFIG :: ID [07:00] */
#define BCHP_DCD_PIPE_CTL_0_CORE_CONFIG_ID_MASK                    0x000000ff
#define BCHP_DCD_PIPE_CTL_0_CORE_CONFIG_ID_SHIFT                   0

/***************************************************************************
 *AVD_CLK_GATE - pipe clock gating
 ***************************************************************************/
/* DCD_PIPE_CTL_0 :: AVD_CLK_GATE :: reserved0 [31:13] */
#define BCHP_DCD_PIPE_CTL_0_AVD_CLK_GATE_reserved0_MASK            0xffffe000
#define BCHP_DCD_PIPE_CTL_0_AVD_CLK_GATE_reserved0_SHIFT           13

/* DCD_PIPE_CTL_0 :: AVD_CLK_GATE :: clk_hevd [12:12] */
#define BCHP_DCD_PIPE_CTL_0_AVD_CLK_GATE_clk_hevd_MASK             0x00001000
#define BCHP_DCD_PIPE_CTL_0_AVD_CLK_GATE_clk_hevd_SHIFT            12
#define BCHP_DCD_PIPE_CTL_0_AVD_CLK_GATE_clk_hevd_DEFAULT          0x00000000

/* DCD_PIPE_CTL_0 :: AVD_CLK_GATE :: clk_avd [11:11] */
#define BCHP_DCD_PIPE_CTL_0_AVD_CLK_GATE_clk_avd_MASK              0x00000800
#define BCHP_DCD_PIPE_CTL_0_AVD_CLK_GATE_clk_avd_SHIFT             11
#define BCHP_DCD_PIPE_CTL_0_AVD_CLK_GATE_clk_avd_DEFAULT           0x00000000

/* DCD_PIPE_CTL_0 :: AVD_CLK_GATE :: reserved1 [10:10] */
#define BCHP_DCD_PIPE_CTL_0_AVD_CLK_GATE_reserved1_MASK            0x00000400
#define BCHP_DCD_PIPE_CTL_0_AVD_CLK_GATE_reserved1_SHIFT           10

/* DCD_PIPE_CTL_0 :: AVD_CLK_GATE :: clk_ka [09:09] */
#define BCHP_DCD_PIPE_CTL_0_AVD_CLK_GATE_clk_ka_MASK               0x00000200
#define BCHP_DCD_PIPE_CTL_0_AVD_CLK_GATE_clk_ka_SHIFT              9
#define BCHP_DCD_PIPE_CTL_0_AVD_CLK_GATE_clk_ka_DEFAULT            0x00000000

/* DCD_PIPE_CTL_0 :: AVD_CLK_GATE :: clk_ils [08:08] */
#define BCHP_DCD_PIPE_CTL_0_AVD_CLK_GATE_clk_ils_MASK              0x00000100
#define BCHP_DCD_PIPE_CTL_0_AVD_CLK_GATE_clk_ils_SHIFT             8
#define BCHP_DCD_PIPE_CTL_0_AVD_CLK_GATE_clk_ils_DEFAULT           0x00000000

/* DCD_PIPE_CTL_0 :: AVD_CLK_GATE :: reserved2 [07:07] */
#define BCHP_DCD_PIPE_CTL_0_AVD_CLK_GATE_reserved2_MASK            0x00000080
#define BCHP_DCD_PIPE_CTL_0_AVD_CLK_GATE_reserved2_SHIFT           7

/* DCD_PIPE_CTL_0 :: AVD_CLK_GATE :: clk_intra [06:06] */
#define BCHP_DCD_PIPE_CTL_0_AVD_CLK_GATE_clk_intra_MASK            0x00000040
#define BCHP_DCD_PIPE_CTL_0_AVD_CLK_GATE_clk_intra_SHIFT           6
#define BCHP_DCD_PIPE_CTL_0_AVD_CLK_GATE_clk_intra_DEFAULT         0x00000000

/* DCD_PIPE_CTL_0 :: AVD_CLK_GATE :: clk_vframe [05:05] */
#define BCHP_DCD_PIPE_CTL_0_AVD_CLK_GATE_clk_vframe_MASK           0x00000020
#define BCHP_DCD_PIPE_CTL_0_AVD_CLK_GATE_clk_vframe_SHIFT          5
#define BCHP_DCD_PIPE_CTL_0_AVD_CLK_GATE_clk_vframe_DEFAULT        0x00000000

/* DCD_PIPE_CTL_0 :: AVD_CLK_GATE :: clk_avc [04:04] */
#define BCHP_DCD_PIPE_CTL_0_AVD_CLK_GATE_clk_avc_MASK              0x00000010
#define BCHP_DCD_PIPE_CTL_0_AVD_CLK_GATE_clk_avc_SHIFT             4
#define BCHP_DCD_PIPE_CTL_0_AVD_CLK_GATE_clk_avc_DEFAULT           0x00000000

/* DCD_PIPE_CTL_0 :: AVD_CLK_GATE :: clk_vc1 [03:03] */
#define BCHP_DCD_PIPE_CTL_0_AVD_CLK_GATE_clk_vc1_MASK              0x00000008
#define BCHP_DCD_PIPE_CTL_0_AVD_CLK_GATE_clk_vc1_SHIFT             3
#define BCHP_DCD_PIPE_CTL_0_AVD_CLK_GATE_clk_vc1_DEFAULT           0x00000000

/* DCD_PIPE_CTL_0 :: AVD_CLK_GATE :: clk_vc1_db [02:02] */
#define BCHP_DCD_PIPE_CTL_0_AVD_CLK_GATE_clk_vc1_db_MASK           0x00000004
#define BCHP_DCD_PIPE_CTL_0_AVD_CLK_GATE_clk_vc1_db_SHIFT          2
#define BCHP_DCD_PIPE_CTL_0_AVD_CLK_GATE_clk_vc1_db_DEFAULT        0x00000000

/* DCD_PIPE_CTL_0 :: AVD_CLK_GATE :: clk_mp4 [01:01] */
#define BCHP_DCD_PIPE_CTL_0_AVD_CLK_GATE_clk_mp4_MASK              0x00000002
#define BCHP_DCD_PIPE_CTL_0_AVD_CLK_GATE_clk_mp4_SHIFT             1
#define BCHP_DCD_PIPE_CTL_0_AVD_CLK_GATE_clk_mp4_DEFAULT           0x00000000

/* DCD_PIPE_CTL_0 :: AVD_CLK_GATE :: clk_mp2 [00:00] */
#define BCHP_DCD_PIPE_CTL_0_AVD_CLK_GATE_clk_mp2_MASK              0x00000001
#define BCHP_DCD_PIPE_CTL_0_AVD_CLK_GATE_clk_mp2_SHIFT             0
#define BCHP_DCD_PIPE_CTL_0_AVD_CLK_GATE_clk_mp2_DEFAULT           0x00000000

/***************************************************************************
 *SW_RESET_REG - Software reset register
 ***************************************************************************/
/* DCD_PIPE_CTL_0 :: SW_RESET_REG :: reserved0 [31:08] */
#define BCHP_DCD_PIPE_CTL_0_SW_RESET_REG_reserved0_MASK            0xffffff00
#define BCHP_DCD_PIPE_CTL_0_SW_RESET_REG_reserved0_SHIFT           8

/* DCD_PIPE_CTL_0 :: SW_RESET_REG :: SCB_arb_reset [07:07] */
#define BCHP_DCD_PIPE_CTL_0_SW_RESET_REG_SCB_arb_reset_MASK        0x00000080
#define BCHP_DCD_PIPE_CTL_0_SW_RESET_REG_SCB_arb_reset_SHIFT       7
#define BCHP_DCD_PIPE_CTL_0_SW_RESET_REG_SCB_arb_reset_DEFAULT     0x00000000

/* DCD_PIPE_CTL_0 :: SW_RESET_REG :: AVD_hard_reset [06:06] */
#define BCHP_DCD_PIPE_CTL_0_SW_RESET_REG_AVD_hard_reset_MASK       0x00000040
#define BCHP_DCD_PIPE_CTL_0_SW_RESET_REG_AVD_hard_reset_SHIFT      6
#define BCHP_DCD_PIPE_CTL_0_SW_RESET_REG_AVD_hard_reset_DEFAULT    0x00000000

/* DCD_PIPE_CTL_0 :: SW_RESET_REG :: DBshim_reset [05:05] */
#define BCHP_DCD_PIPE_CTL_0_SW_RESET_REG_DBshim_reset_MASK         0x00000020
#define BCHP_DCD_PIPE_CTL_0_SW_RESET_REG_DBshim_reset_SHIFT        5
#define BCHP_DCD_PIPE_CTL_0_SW_RESET_REG_DBshim_reset_DEFAULT      0x00000000

/* DCD_PIPE_CTL_0 :: SW_RESET_REG :: HEVD_be_hard_reset [04:04] */
#define BCHP_DCD_PIPE_CTL_0_SW_RESET_REG_HEVD_be_hard_reset_MASK   0x00000010
#define BCHP_DCD_PIPE_CTL_0_SW_RESET_REG_HEVD_be_hard_reset_SHIFT  4
#define BCHP_DCD_PIPE_CTL_0_SW_RESET_REG_HEVD_be_hard_reset_DEFAULT 0x00000000

/* DCD_PIPE_CTL_0 :: SW_RESET_REG :: HEVD_fe_hard_reset [03:03] */
#define BCHP_DCD_PIPE_CTL_0_SW_RESET_REG_HEVD_fe_hard_reset_MASK   0x00000008
#define BCHP_DCD_PIPE_CTL_0_SW_RESET_REG_HEVD_fe_hard_reset_SHIFT  3
#define BCHP_DCD_PIPE_CTL_0_SW_RESET_REG_HEVD_fe_hard_reset_DEFAULT 0x00000000

/* DCD_PIPE_CTL_0 :: SW_RESET_REG :: HEVD_be_reset [02:02] */
#define BCHP_DCD_PIPE_CTL_0_SW_RESET_REG_HEVD_be_reset_MASK        0x00000004
#define BCHP_DCD_PIPE_CTL_0_SW_RESET_REG_HEVD_be_reset_SHIFT       2
#define BCHP_DCD_PIPE_CTL_0_SW_RESET_REG_HEVD_be_reset_DEFAULT     0x00000000

/* DCD_PIPE_CTL_0 :: SW_RESET_REG :: HEVD_fe_reset [01:01] */
#define BCHP_DCD_PIPE_CTL_0_SW_RESET_REG_HEVD_fe_reset_MASK        0x00000002
#define BCHP_DCD_PIPE_CTL_0_SW_RESET_REG_HEVD_fe_reset_SHIFT       1
#define BCHP_DCD_PIPE_CTL_0_SW_RESET_REG_HEVD_fe_reset_DEFAULT     0x00000000

/* DCD_PIPE_CTL_0 :: SW_RESET_REG :: ILSI_reset [00:00] */
#define BCHP_DCD_PIPE_CTL_0_SW_RESET_REG_ILSI_reset_MASK           0x00000001
#define BCHP_DCD_PIPE_CTL_0_SW_RESET_REG_ILSI_reset_SHIFT          0
#define BCHP_DCD_PIPE_CTL_0_SW_RESET_REG_ILSI_reset_DEFAULT        0x00000000

/***************************************************************************
 *BLD_CLK_GATE - BLD pipe clock gating
 ***************************************************************************/
/* DCD_PIPE_CTL_0 :: BLD_CLK_GATE :: reserved0 [31:01] */
#define BCHP_DCD_PIPE_CTL_0_BLD_CLK_GATE_reserved0_MASK            0xfffffffe
#define BCHP_DCD_PIPE_CTL_0_BLD_CLK_GATE_reserved0_SHIFT           1

/* DCD_PIPE_CTL_0 :: BLD_CLK_GATE :: clk_bld [00:00] */
#define BCHP_DCD_PIPE_CTL_0_BLD_CLK_GATE_clk_bld_MASK              0x00000001
#define BCHP_DCD_PIPE_CTL_0_BLD_CLK_GATE_clk_bld_SHIFT             0
#define BCHP_DCD_PIPE_CTL_0_BLD_CLK_GATE_clk_bld_DEFAULT           0x00000000

/***************************************************************************
 *OUTPUT_CLIENT_SEL - Output SCB Client Selection
 ***************************************************************************/
/* DCD_PIPE_CTL_0 :: OUTPUT_CLIENT_SEL :: reserved0 [31:01] */
#define BCHP_DCD_PIPE_CTL_0_OUTPUT_CLIENT_SEL_reserved0_MASK       0xfffffffe
#define BCHP_DCD_PIPE_CTL_0_OUTPUT_CLIENT_SEL_reserved0_SHIFT      1

/* DCD_PIPE_CTL_0 :: OUTPUT_CLIENT_SEL :: output_client [00:00] */
#define BCHP_DCD_PIPE_CTL_0_OUTPUT_CLIENT_SEL_output_client_MASK   0x00000001
#define BCHP_DCD_PIPE_CTL_0_OUTPUT_CLIENT_SEL_output_client_SHIFT  0
#define BCHP_DCD_PIPE_CTL_0_OUTPUT_CLIENT_SEL_output_client_DEFAULT 0x00000000

/***************************************************************************
 *MULTIPIPE_PFRI_ARB_CTL - Multipipe PFRI Arbiter Controls
 ***************************************************************************/
/* DCD_PIPE_CTL_0 :: MULTIPIPE_PFRI_ARB_CTL :: reserved0 [31:19] */
#define BCHP_DCD_PIPE_CTL_0_MULTIPIPE_PFRI_ARB_CTL_reserved0_MASK  0xfff80000
#define BCHP_DCD_PIPE_CTL_0_MULTIPIPE_PFRI_ARB_CTL_reserved0_SHIFT 19

/* DCD_PIPE_CTL_0 :: MULTIPIPE_PFRI_ARB_CTL :: remap_shift [18:17] */
#define BCHP_DCD_PIPE_CTL_0_MULTIPIPE_PFRI_ARB_CTL_remap_shift_MASK 0x00060000
#define BCHP_DCD_PIPE_CTL_0_MULTIPIPE_PFRI_ARB_CTL_remap_shift_SHIFT 17
#define BCHP_DCD_PIPE_CTL_0_MULTIPIPE_PFRI_ARB_CTL_remap_shift_DEFAULT 0x00000000

/* DCD_PIPE_CTL_0 :: MULTIPIPE_PFRI_ARB_CTL :: end_of_line_delta [16:12] */
#define BCHP_DCD_PIPE_CTL_0_MULTIPIPE_PFRI_ARB_CTL_end_of_line_delta_MASK 0x0001f000
#define BCHP_DCD_PIPE_CTL_0_MULTIPIPE_PFRI_ARB_CTL_end_of_line_delta_SHIFT 12
#define BCHP_DCD_PIPE_CTL_0_MULTIPIPE_PFRI_ARB_CTL_end_of_line_delta_DEFAULT 0x00000000

/* DCD_PIPE_CTL_0 :: MULTIPIPE_PFRI_ARB_CTL :: pipe0_offset [11:02] */
#define BCHP_DCD_PIPE_CTL_0_MULTIPIPE_PFRI_ARB_CTL_pipe0_offset_MASK 0x00000ffc
#define BCHP_DCD_PIPE_CTL_0_MULTIPIPE_PFRI_ARB_CTL_pipe0_offset_SHIFT 2
#define BCHP_DCD_PIPE_CTL_0_MULTIPIPE_PFRI_ARB_CTL_pipe0_offset_DEFAULT 0x00000000

/* DCD_PIPE_CTL_0 :: MULTIPIPE_PFRI_ARB_CTL :: arb_enable [01:01] */
#define BCHP_DCD_PIPE_CTL_0_MULTIPIPE_PFRI_ARB_CTL_arb_enable_MASK 0x00000002
#define BCHP_DCD_PIPE_CTL_0_MULTIPIPE_PFRI_ARB_CTL_arb_enable_SHIFT 1
#define BCHP_DCD_PIPE_CTL_0_MULTIPIPE_PFRI_ARB_CTL_arb_enable_DEFAULT 0x00000000

/* DCD_PIPE_CTL_0 :: MULTIPIPE_PFRI_ARB_CTL :: picture_start [00:00] */
#define BCHP_DCD_PIPE_CTL_0_MULTIPIPE_PFRI_ARB_CTL_picture_start_MASK 0x00000001
#define BCHP_DCD_PIPE_CTL_0_MULTIPIPE_PFRI_ARB_CTL_picture_start_SHIFT 0
#define BCHP_DCD_PIPE_CTL_0_MULTIPIPE_PFRI_ARB_CTL_picture_start_DEFAULT 0x00000000

/***************************************************************************
 *IL_RM2_ARB_TIMEOUT - RM2 ARBITER TIMEOUT Register
 ***************************************************************************/
/* DCD_PIPE_CTL_0 :: IL_RM2_ARB_TIMEOUT :: RM2_arbiter_timeout_value [31:08] */
#define BCHP_DCD_PIPE_CTL_0_IL_RM2_ARB_TIMEOUT_RM2_arbiter_timeout_value_MASK 0xffffff00
#define BCHP_DCD_PIPE_CTL_0_IL_RM2_ARB_TIMEOUT_RM2_arbiter_timeout_value_SHIFT 8
#define BCHP_DCD_PIPE_CTL_0_IL_RM2_ARB_TIMEOUT_RM2_arbiter_timeout_value_DEFAULT 0x000003ff

/* DCD_PIPE_CTL_0 :: IL_RM2_ARB_TIMEOUT :: reserved0 [07:00] */
#define BCHP_DCD_PIPE_CTL_0_IL_RM2_ARB_TIMEOUT_reserved0_MASK      0x000000ff
#define BCHP_DCD_PIPE_CTL_0_IL_RM2_ARB_TIMEOUT_reserved0_SHIFT     0

/***************************************************************************
 *IL_RM2_ARB_TIMEOUT_SEEN - Arbiter timeout detected
 ***************************************************************************/
/* DCD_PIPE_CTL_0 :: IL_RM2_ARB_TIMEOUT_SEEN :: reserved0 [31:01] */
#define BCHP_DCD_PIPE_CTL_0_IL_RM2_ARB_TIMEOUT_SEEN_reserved0_MASK 0xfffffffe
#define BCHP_DCD_PIPE_CTL_0_IL_RM2_ARB_TIMEOUT_SEEN_reserved0_SHIFT 1

/* DCD_PIPE_CTL_0 :: IL_RM2_ARB_TIMEOUT_SEEN :: TimeoutSeen [00:00] */
#define BCHP_DCD_PIPE_CTL_0_IL_RM2_ARB_TIMEOUT_SEEN_TimeoutSeen_MASK 0x00000001
#define BCHP_DCD_PIPE_CTL_0_IL_RM2_ARB_TIMEOUT_SEEN_TimeoutSeen_SHIFT 0
#define BCHP_DCD_PIPE_CTL_0_IL_RM2_ARB_TIMEOUT_SEEN_TimeoutSeen_DEFAULT 0x00000000

/***************************************************************************
 *IPCOMM_L2R_TRANSMIT - Inter-CPU L2R Transmit Data Register
 ***************************************************************************/
/* DCD_PIPE_CTL_0 :: IPCOMM_L2R_TRANSMIT :: Data [31:00] */
#define BCHP_DCD_PIPE_CTL_0_IPCOMM_L2R_TRANSMIT_Data_MASK          0xffffffff
#define BCHP_DCD_PIPE_CTL_0_IPCOMM_L2R_TRANSMIT_Data_SHIFT         0
#define BCHP_DCD_PIPE_CTL_0_IPCOMM_L2R_TRANSMIT_Data_DEFAULT       0x00000000

/***************************************************************************
 *IPCOMM_L2R_RECEIVE - Inter-CPU L2R Receive Data Register
 ***************************************************************************/
/* DCD_PIPE_CTL_0 :: IPCOMM_L2R_RECEIVE :: Data [31:00] */
#define BCHP_DCD_PIPE_CTL_0_IPCOMM_L2R_RECEIVE_Data_MASK           0xffffffff
#define BCHP_DCD_PIPE_CTL_0_IPCOMM_L2R_RECEIVE_Data_SHIFT          0
#define BCHP_DCD_PIPE_CTL_0_IPCOMM_L2R_RECEIVE_Data_DEFAULT        0x00000000

/***************************************************************************
 *IPCOMM_L2R_STATUS - Inter-CPU L2R Status Register
 ***************************************************************************/
/* DCD_PIPE_CTL_0 :: IPCOMM_L2R_STATUS :: reserved0 [31:03] */
#define BCHP_DCD_PIPE_CTL_0_IPCOMM_L2R_STATUS_reserved0_MASK       0xfffffff8
#define BCHP_DCD_PIPE_CTL_0_IPCOMM_L2R_STATUS_reserved0_SHIFT      3

/* DCD_PIPE_CTL_0 :: IPCOMM_L2R_STATUS :: xmit_err [02:02] */
#define BCHP_DCD_PIPE_CTL_0_IPCOMM_L2R_STATUS_xmit_err_MASK        0x00000004
#define BCHP_DCD_PIPE_CTL_0_IPCOMM_L2R_STATUS_xmit_err_SHIFT       2
#define BCHP_DCD_PIPE_CTL_0_IPCOMM_L2R_STATUS_xmit_err_DEFAULT     0x00000000

/* DCD_PIPE_CTL_0 :: IPCOMM_L2R_STATUS :: rcv_full [01:01] */
#define BCHP_DCD_PIPE_CTL_0_IPCOMM_L2R_STATUS_rcv_full_MASK        0x00000002
#define BCHP_DCD_PIPE_CTL_0_IPCOMM_L2R_STATUS_rcv_full_SHIFT       1
#define BCHP_DCD_PIPE_CTL_0_IPCOMM_L2R_STATUS_rcv_full_DEFAULT     0x00000000

/* DCD_PIPE_CTL_0 :: IPCOMM_L2R_STATUS :: xmit_ok [00:00] */
#define BCHP_DCD_PIPE_CTL_0_IPCOMM_L2R_STATUS_xmit_ok_MASK         0x00000001
#define BCHP_DCD_PIPE_CTL_0_IPCOMM_L2R_STATUS_xmit_ok_SHIFT        0
#define BCHP_DCD_PIPE_CTL_0_IPCOMM_L2R_STATUS_xmit_ok_DEFAULT      0x00000000

/***************************************************************************
 *IPCOMM_R2L_TRANSMIT - Inter-CPU R2L Transmit Data Register
 ***************************************************************************/
/* DCD_PIPE_CTL_0 :: IPCOMM_R2L_TRANSMIT :: Data [31:00] */
#define BCHP_DCD_PIPE_CTL_0_IPCOMM_R2L_TRANSMIT_Data_MASK          0xffffffff
#define BCHP_DCD_PIPE_CTL_0_IPCOMM_R2L_TRANSMIT_Data_SHIFT         0
#define BCHP_DCD_PIPE_CTL_0_IPCOMM_R2L_TRANSMIT_Data_DEFAULT       0x00000000

/***************************************************************************
 *IPCOMM_R2L_RECEIVE - Inter-CPU R2L Receive Data Register
 ***************************************************************************/
/* DCD_PIPE_CTL_0 :: IPCOMM_R2L_RECEIVE :: Data [31:00] */
#define BCHP_DCD_PIPE_CTL_0_IPCOMM_R2L_RECEIVE_Data_MASK           0xffffffff
#define BCHP_DCD_PIPE_CTL_0_IPCOMM_R2L_RECEIVE_Data_SHIFT          0
#define BCHP_DCD_PIPE_CTL_0_IPCOMM_R2L_RECEIVE_Data_DEFAULT        0x00000000

/***************************************************************************
 *IPCOMM_R2L_STATUS - Inter-CPU R2L Status Register
 ***************************************************************************/
/* DCD_PIPE_CTL_0 :: IPCOMM_R2L_STATUS :: reserved0 [31:03] */
#define BCHP_DCD_PIPE_CTL_0_IPCOMM_R2L_STATUS_reserved0_MASK       0xfffffff8
#define BCHP_DCD_PIPE_CTL_0_IPCOMM_R2L_STATUS_reserved0_SHIFT      3

/* DCD_PIPE_CTL_0 :: IPCOMM_R2L_STATUS :: xmit_err [02:02] */
#define BCHP_DCD_PIPE_CTL_0_IPCOMM_R2L_STATUS_xmit_err_MASK        0x00000004
#define BCHP_DCD_PIPE_CTL_0_IPCOMM_R2L_STATUS_xmit_err_SHIFT       2
#define BCHP_DCD_PIPE_CTL_0_IPCOMM_R2L_STATUS_xmit_err_DEFAULT     0x00000000

/* DCD_PIPE_CTL_0 :: IPCOMM_R2L_STATUS :: rcv_full [01:01] */
#define BCHP_DCD_PIPE_CTL_0_IPCOMM_R2L_STATUS_rcv_full_MASK        0x00000002
#define BCHP_DCD_PIPE_CTL_0_IPCOMM_R2L_STATUS_rcv_full_SHIFT       1
#define BCHP_DCD_PIPE_CTL_0_IPCOMM_R2L_STATUS_rcv_full_DEFAULT     0x00000000

/* DCD_PIPE_CTL_0 :: IPCOMM_R2L_STATUS :: xmit_ok [00:00] */
#define BCHP_DCD_PIPE_CTL_0_IPCOMM_R2L_STATUS_xmit_ok_MASK         0x00000001
#define BCHP_DCD_PIPE_CTL_0_IPCOMM_R2L_STATUS_xmit_ok_SHIFT        0
#define BCHP_DCD_PIPE_CTL_0_IPCOMM_R2L_STATUS_xmit_ok_DEFAULT      0x00000000

/***************************************************************************
 *RECON_DEBUG_REG - Reconstructor debug register
 ***************************************************************************/
/* DCD_PIPE_CTL_0 :: RECON_DEBUG_REG :: Recon_debug_data [31:00] */
#define BCHP_DCD_PIPE_CTL_0_RECON_DEBUG_REG_Recon_debug_data_MASK  0xffffffff
#define BCHP_DCD_PIPE_CTL_0_RECON_DEBUG_REG_Recon_debug_data_SHIFT 0

/***************************************************************************
 *IXFORM_DEBUG_REG - Ixform debug register
 ***************************************************************************/
/* DCD_PIPE_CTL_0 :: IXFORM_DEBUG_REG :: Ixform_debug_data [31:00] */
#define BCHP_DCD_PIPE_CTL_0_IXFORM_DEBUG_REG_Ixform_debug_data_MASK 0xffffffff
#define BCHP_DCD_PIPE_CTL_0_IXFORM_DEBUG_REG_Ixform_debug_data_SHIFT 0

/***************************************************************************
 *ILSI_DEBUG_REG - ILSI debug register
 ***************************************************************************/
/* DCD_PIPE_CTL_0 :: ILSI_DEBUG_REG :: ILSI_debug_data [31:00] */
#define BCHP_DCD_PIPE_CTL_0_ILSI_DEBUG_REG_ILSI_debug_data_MASK    0xffffffff
#define BCHP_DCD_PIPE_CTL_0_ILSI_DEBUG_REG_ILSI_debug_data_SHIFT   0

/***************************************************************************
 *SHIM_DEBUG_CTL - SCB Shim debug register
 ***************************************************************************/
/* DCD_PIPE_CTL_0 :: SHIM_DEBUG_CTL :: DB_Shim_active [31:31] */
#define BCHP_DCD_PIPE_CTL_0_SHIM_DEBUG_CTL_DB_Shim_active_MASK     0x80000000
#define BCHP_DCD_PIPE_CTL_0_SHIM_DEBUG_CTL_DB_Shim_active_SHIFT    31
#define BCHP_DCD_PIPE_CTL_0_SHIM_DEBUG_CTL_DB_Shim_active_DEFAULT  0x00000000

/* DCD_PIPE_CTL_0 :: SHIM_DEBUG_CTL :: reserved0 [30:14] */
#define BCHP_DCD_PIPE_CTL_0_SHIM_DEBUG_CTL_reserved0_MASK          0x7fffc000
#define BCHP_DCD_PIPE_CTL_0_SHIM_DEBUG_CTL_reserved0_SHIFT         14

/* DCD_PIPE_CTL_0 :: SHIM_DEBUG_CTL :: SCB_debug [13:13] */
#define BCHP_DCD_PIPE_CTL_0_SHIM_DEBUG_CTL_SCB_debug_MASK          0x00002000
#define BCHP_DCD_PIPE_CTL_0_SHIM_DEBUG_CTL_SCB_debug_SHIFT         13
#define BCHP_DCD_PIPE_CTL_0_SHIM_DEBUG_CTL_SCB_debug_DEFAULT       0x00000000

/* DCD_PIPE_CTL_0 :: SHIM_DEBUG_CTL :: reserved1 [12:10] */
#define BCHP_DCD_PIPE_CTL_0_SHIM_DEBUG_CTL_reserved1_MASK          0x00001c00
#define BCHP_DCD_PIPE_CTL_0_SHIM_DEBUG_CTL_reserved1_SHIFT         10

/* DCD_PIPE_CTL_0 :: SHIM_DEBUG_CTL :: SCB_debug_select [09:08] */
#define BCHP_DCD_PIPE_CTL_0_SHIM_DEBUG_CTL_SCB_debug_select_MASK   0x00000300
#define BCHP_DCD_PIPE_CTL_0_SHIM_DEBUG_CTL_SCB_debug_select_SHIFT  8
#define BCHP_DCD_PIPE_CTL_0_SHIM_DEBUG_CTL_SCB_debug_select_DEFAULT 0x00000000

/* DCD_PIPE_CTL_0 :: SHIM_DEBUG_CTL :: reserved2 [07:03] */
#define BCHP_DCD_PIPE_CTL_0_SHIM_DEBUG_CTL_reserved2_MASK          0x000000f8
#define BCHP_DCD_PIPE_CTL_0_SHIM_DEBUG_CTL_reserved2_SHIFT         3

/* DCD_PIPE_CTL_0 :: SHIM_DEBUG_CTL :: SCB_status_sel [02:01] */
#define BCHP_DCD_PIPE_CTL_0_SHIM_DEBUG_CTL_SCB_status_sel_MASK     0x00000006
#define BCHP_DCD_PIPE_CTL_0_SHIM_DEBUG_CTL_SCB_status_sel_SHIFT    1
#define BCHP_DCD_PIPE_CTL_0_SHIM_DEBUG_CTL_SCB_status_sel_DEFAULT  0x00000000

/* DCD_PIPE_CTL_0 :: SHIM_DEBUG_CTL :: SCB_err_enable [00:00] */
#define BCHP_DCD_PIPE_CTL_0_SHIM_DEBUG_CTL_SCB_err_enable_MASK     0x00000001
#define BCHP_DCD_PIPE_CTL_0_SHIM_DEBUG_CTL_SCB_err_enable_SHIFT    0
#define BCHP_DCD_PIPE_CTL_0_SHIM_DEBUG_CTL_SCB_err_enable_DEFAULT  0x00000000

/***************************************************************************
 *SHIM_DEBUG_READ - SCB Shim debug register
 ***************************************************************************/
/* DCD_PIPE_CTL_0 :: SHIM_DEBUG_READ :: SCB_shim_debug_data [31:00] */
#define BCHP_DCD_PIPE_CTL_0_SHIM_DEBUG_READ_SCB_shim_debug_data_MASK 0xffffffff
#define BCHP_DCD_PIPE_CTL_0_SHIM_DEBUG_READ_SCB_shim_debug_data_SHIFT 0

/***************************************************************************
 *SHIM_ERROR_REG - SCB Shim error register
 ***************************************************************************/
/* DCD_PIPE_CTL_0 :: SHIM_ERROR_REG :: SCB_shim_error [31:00] */
#define BCHP_DCD_PIPE_CTL_0_SHIM_ERROR_REG_SCB_shim_error_MASK     0xffffffff
#define BCHP_DCD_PIPE_CTL_0_SHIM_ERROR_REG_SCB_shim_error_SHIFT    0

/***************************************************************************
 *DBLK_STRIPE_HEIGHT - Legacy deblock stripe height
 ***************************************************************************/
/* DCD_PIPE_CTL_0 :: DBLK_STRIPE_HEIGHT :: reserved0 [31:27] */
#define BCHP_DCD_PIPE_CTL_0_DBLK_STRIPE_HEIGHT_reserved0_MASK      0xf8000000
#define BCHP_DCD_PIPE_CTL_0_DBLK_STRIPE_HEIGHT_reserved0_SHIFT     27

/* DCD_PIPE_CTL_0 :: DBLK_STRIPE_HEIGHT :: Chroma_Height [26:16] */
#define BCHP_DCD_PIPE_CTL_0_DBLK_STRIPE_HEIGHT_Chroma_Height_MASK  0x07ff0000
#define BCHP_DCD_PIPE_CTL_0_DBLK_STRIPE_HEIGHT_Chroma_Height_SHIFT 16

/* DCD_PIPE_CTL_0 :: DBLK_STRIPE_HEIGHT :: reserved1 [15:13] */
#define BCHP_DCD_PIPE_CTL_0_DBLK_STRIPE_HEIGHT_reserved1_MASK      0x0000e000
#define BCHP_DCD_PIPE_CTL_0_DBLK_STRIPE_HEIGHT_reserved1_SHIFT     13

/* DCD_PIPE_CTL_0 :: DBLK_STRIPE_HEIGHT :: Height [12:02] */
#define BCHP_DCD_PIPE_CTL_0_DBLK_STRIPE_HEIGHT_Height_MASK         0x00001ffc
#define BCHP_DCD_PIPE_CTL_0_DBLK_STRIPE_HEIGHT_Height_SHIFT        2

/* DCD_PIPE_CTL_0 :: DBLK_STRIPE_HEIGHT :: reserved2 [01:00] */
#define BCHP_DCD_PIPE_CTL_0_DBLK_STRIPE_HEIGHT_reserved2_MASK      0x00000003
#define BCHP_DCD_PIPE_CTL_0_DBLK_STRIPE_HEIGHT_reserved2_SHIFT     0

/***************************************************************************
 *DBLK_STRIPE_WIDTH - Legacy deblock stripe width
 ***************************************************************************/
/* DCD_PIPE_CTL_0 :: DBLK_STRIPE_WIDTH :: reserved0 [31:02] */
#define BCHP_DCD_PIPE_CTL_0_DBLK_STRIPE_WIDTH_reserved0_MASK       0xfffffffc
#define BCHP_DCD_PIPE_CTL_0_DBLK_STRIPE_WIDTH_reserved0_SHIFT      2

/* DCD_PIPE_CTL_0 :: DBLK_STRIPE_WIDTH :: Stripe_Width [01:00] */
#define BCHP_DCD_PIPE_CTL_0_DBLK_STRIPE_WIDTH_Stripe_Width_MASK    0x00000003
#define BCHP_DCD_PIPE_CTL_0_DBLK_STRIPE_WIDTH_Stripe_Width_SHIFT   0
#define BCHP_DCD_PIPE_CTL_0_DBLK_STRIPE_WIDTH_Stripe_Width_DEFAULT 0x00000000

/***************************************************************************
 *DBLK_PICT_BASE_LUMA - Legacy deblock luma picture base
 ***************************************************************************/
/* DCD_PIPE_CTL_0 :: DBLK_PICT_BASE_LUMA :: Addr [31:12] */
#define BCHP_DCD_PIPE_CTL_0_DBLK_PICT_BASE_LUMA_Addr_MASK          0xfffff000
#define BCHP_DCD_PIPE_CTL_0_DBLK_PICT_BASE_LUMA_Addr_SHIFT         12

/* DCD_PIPE_CTL_0 :: DBLK_PICT_BASE_LUMA :: reserved0 [11:00] */
#define BCHP_DCD_PIPE_CTL_0_DBLK_PICT_BASE_LUMA_reserved0_MASK     0x00000fff
#define BCHP_DCD_PIPE_CTL_0_DBLK_PICT_BASE_LUMA_reserved0_SHIFT    0

/***************************************************************************
 *DBLK_PICT_BASE_CHROMA - Legacy deblock chroma picture base
 ***************************************************************************/
/* DCD_PIPE_CTL_0 :: DBLK_PICT_BASE_CHROMA :: Addr [31:12] */
#define BCHP_DCD_PIPE_CTL_0_DBLK_PICT_BASE_CHROMA_Addr_MASK        0xfffff000
#define BCHP_DCD_PIPE_CTL_0_DBLK_PICT_BASE_CHROMA_Addr_SHIFT       12

/* DCD_PIPE_CTL_0 :: DBLK_PICT_BASE_CHROMA :: reserved0 [11:00] */
#define BCHP_DCD_PIPE_CTL_0_DBLK_PICT_BASE_CHROMA_reserved0_MASK   0x00000fff
#define BCHP_DCD_PIPE_CTL_0_DBLK_PICT_BASE_CHROMA_reserved0_SHIFT  0

#endif /* #ifndef BCHP_DCD_PIPE_CTL_0_H__ */

/* End of File */

/***************************************************************************
 *     Copyright (c) 1999-2011, Broadcom Corporation
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
 * Date:           Generated on         Mon Sep 19 21:43:45 2011
 *                 MD5 Checksum         e020a976c1177b900eff0f3d00f22e40
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

#ifndef BCHP_SDS_BL_H__
#define BCHP_SDS_BL_H__

/***************************************************************************
 *SDS_BL - SDS Baud Loop Register Set
 ***************************************************************************/
#define BCHP_SDS_BL_BLPCTL                       0x00700140 /* Baud Loop Control (Formerly, BLSCCP,BLPCTL3,BLPCTL2,BLPCTL1) */
#define BCHP_SDS_BL_PFCTL                        0x00700144 /* Baud Loop Pre-filter Control */
#define BCHP_SDS_BL_BRSW                         0x00700148 /* Baud Loop Sweep Configuration */
#define BCHP_SDS_BL_BRLC                         0x0070014c /* Baud Loop Linear Coefficient */
#define BCHP_SDS_BL_BRIC                         0x00700150 /* Baud Loop Integrator Coefficient */
#define BCHP_SDS_BL_BRI                          0x00700154 /* Baud Loop Integrator Value */
#define BCHP_SDS_BL_BFOS                         0x00700158 /* Baud Loop Frequency Offset */
#define BCHP_SDS_BL_BRFO                         0x0070015c /* Baud Loop Filter Output */
#define BCHP_SDS_BL_BNCO                         0x00700160 /* Baud Loop NCO Contents */

/***************************************************************************
 *BLPCTL - Baud Loop Control (Formerly, BLSCCP,BLPCTL3,BLPCTL2,BLPCTL1)
 ***************************************************************************/
/* SDS_BL :: BLPCTL :: clip_thd [31:24] */
#define BCHP_SDS_BL_BLPCTL_clip_thd_MASK                           0xff000000
#define BCHP_SDS_BL_BLPCTL_clip_thd_SHIFT                          24
#define BCHP_SDS_BL_BLPCTL_clip_thd_DEFAULT                        255

/* SDS_BL :: BLPCTL :: tv_dly [23:21] */
#define BCHP_SDS_BL_BLPCTL_tv_dly_MASK                             0x00e00000
#define BCHP_SDS_BL_BLPCTL_tv_dly_SHIFT                            21
#define BCHP_SDS_BL_BLPCTL_tv_dly_DEFAULT                          0

/* SDS_BL :: BLPCTL :: reserved_for_eco0 [20:19] */
#define BCHP_SDS_BL_BLPCTL_reserved_for_eco0_MASK                  0x00180000
#define BCHP_SDS_BL_BLPCTL_reserved_for_eco0_SHIFT                 19
#define BCHP_SDS_BL_BLPCTL_reserved_for_eco0_DEFAULT               0

/* SDS_BL :: BLPCTL :: tv_dly_ov [18:18] */
#define BCHP_SDS_BL_BLPCTL_tv_dly_ov_MASK                          0x00040000
#define BCHP_SDS_BL_BLPCTL_tv_dly_ov_SHIFT                         18
#define BCHP_SDS_BL_BLPCTL_tv_dly_ov_DEFAULT                       0

/* SDS_BL :: BLPCTL :: mu_phase [17:17] */
#define BCHP_SDS_BL_BLPCTL_mu_phase_MASK                           0x00020000
#define BCHP_SDS_BL_BLPCTL_mu_phase_SHIFT                          17
#define BCHP_SDS_BL_BLPCTL_mu_phase_DEFAULT                        1

/* SDS_BL :: BLPCTL :: use_valid [16:16] */
#define BCHP_SDS_BL_BLPCTL_use_valid_MASK                          0x00010000
#define BCHP_SDS_BL_BLPCTL_use_valid_SHIFT                         16
#define BCHP_SDS_BL_BLPCTL_use_valid_DEFAULT                       0

/* SDS_BL :: BLPCTL :: x2_vclk [15:15] */
#define BCHP_SDS_BL_BLPCTL_x2_vclk_MASK                            0x00008000
#define BCHP_SDS_BL_BLPCTL_x2_vclk_SHIFT                           15
#define BCHP_SDS_BL_BLPCTL_x2_vclk_DEFAULT                         0

/* SDS_BL :: BLPCTL :: ip_sel [14:14] */
#define BCHP_SDS_BL_BLPCTL_ip_sel_MASK                             0x00004000
#define BCHP_SDS_BL_BLPCTL_ip_sel_SHIFT                            14
#define BCHP_SDS_BL_BLPCTL_ip_sel_DEFAULT                          0

/* SDS_BL :: BLPCTL :: reserved_for_eco1 [13:13] */
#define BCHP_SDS_BL_BLPCTL_reserved_for_eco1_MASK                  0x00002000
#define BCHP_SDS_BL_BLPCTL_reserved_for_eco1_SHIFT                 13
#define BCHP_SDS_BL_BLPCTL_reserved_for_eco1_DEFAULT               0

/* SDS_BL :: BLPCTL :: i_mu_offen [12:12] */
#define BCHP_SDS_BL_BLPCTL_i_mu_offen_MASK                         0x00001000
#define BCHP_SDS_BL_BLPCTL_i_mu_offen_SHIFT                        12
#define BCHP_SDS_BL_BLPCTL_i_mu_offen_DEFAULT                      0

/* SDS_BL :: BLPCTL :: q_mu_offen [11:11] */
#define BCHP_SDS_BL_BLPCTL_q_mu_offen_MASK                         0x00000800
#define BCHP_SDS_BL_BLPCTL_q_mu_offen_SHIFT                        11
#define BCHP_SDS_BL_BLPCTL_q_mu_offen_DEFAULT                      0

/* SDS_BL :: BLPCTL :: blp_obw [10:09] */
#define BCHP_SDS_BL_BLPCTL_blp_obw_MASK                            0x00000600
#define BCHP_SDS_BL_BLPCTL_blp_obw_SHIFT                           9
#define BCHP_SDS_BL_BLPCTL_blp_obw_DEFAULT                         0

/* SDS_BL :: BLPCTL :: blp_rst [08:08] */
#define BCHP_SDS_BL_BLPCTL_blp_rst_MASK                            0x00000100
#define BCHP_SDS_BL_BLPCTL_blp_rst_SHIFT                           8
#define BCHP_SDS_BL_BLPCTL_blp_rst_DEFAULT                         0

/* SDS_BL :: BLPCTL :: pd_ovd [07:07] */
#define BCHP_SDS_BL_BLPCTL_pd_ovd_MASK                             0x00000080
#define BCHP_SDS_BL_BLPCTL_pd_ovd_SHIFT                            7
#define BCHP_SDS_BL_BLPCTL_pd_ovd_DEFAULT                          0

/* SDS_BL :: BLPCTL :: pd_stat [06:06] */
#define BCHP_SDS_BL_BLPCTL_pd_stat_MASK                            0x00000040
#define BCHP_SDS_BL_BLPCTL_pd_stat_SHIFT                           6
#define BCHP_SDS_BL_BLPCTL_pd_stat_DEFAULT                         0

/* SDS_BL :: BLPCTL :: zr_stat [05:05] */
#define BCHP_SDS_BL_BLPCTL_zr_stat_MASK                            0x00000020
#define BCHP_SDS_BL_BLPCTL_zr_stat_SHIFT                           5
#define BCHP_SDS_BL_BLPCTL_zr_stat_DEFAULT                         0

/* SDS_BL :: BLPCTL :: blp_freeze [04:04] */
#define BCHP_SDS_BL_BLPCTL_blp_freeze_MASK                         0x00000010
#define BCHP_SDS_BL_BLPCTL_blp_freeze_SHIFT                        4
#define BCHP_SDS_BL_BLPCTL_blp_freeze_DEFAULT                      1

/* SDS_BL :: BLPCTL :: oqpsk [03:03] */
#define BCHP_SDS_BL_BLPCTL_oqpsk_MASK                              0x00000008
#define BCHP_SDS_BL_BLPCTL_oqpsk_SHIFT                             3
#define BCHP_SDS_BL_BLPCTL_oqpsk_DEFAULT                           0

/* SDS_BL :: BLPCTL :: pass_q [02:02] */
#define BCHP_SDS_BL_BLPCTL_pass_q_MASK                             0x00000004
#define BCHP_SDS_BL_BLPCTL_pass_q_SHIFT                            2
#define BCHP_SDS_BL_BLPCTL_pass_q_DEFAULT                          0

/* SDS_BL :: BLPCTL :: pass_i [01:01] */
#define BCHP_SDS_BL_BLPCTL_pass_i_MASK                             0x00000002
#define BCHP_SDS_BL_BLPCTL_pass_i_SHIFT                            1
#define BCHP_SDS_BL_BLPCTL_pass_i_DEFAULT                          0

/* SDS_BL :: BLPCTL :: blp_en [00:00] */
#define BCHP_SDS_BL_BLPCTL_blp_en_MASK                             0x00000001
#define BCHP_SDS_BL_BLPCTL_blp_en_SHIFT                            0
#define BCHP_SDS_BL_BLPCTL_blp_en_DEFAULT                          0

/***************************************************************************
 *PFCTL - Baud Loop Pre-filter Control
 ***************************************************************************/
/* SDS_BL :: PFCTL :: reserved0 [31:08] */
#define BCHP_SDS_BL_PFCTL_reserved0_MASK                           0xffffff00
#define BCHP_SDS_BL_PFCTL_reserved0_SHIFT                          8

/* SDS_BL :: PFCTL :: reserved_for_eco1 [07:03] */
#define BCHP_SDS_BL_PFCTL_reserved_for_eco1_MASK                   0x000000f8
#define BCHP_SDS_BL_PFCTL_reserved_for_eco1_SHIFT                  3
#define BCHP_SDS_BL_PFCTL_reserved_for_eco1_DEFAULT                0

/* SDS_BL :: PFCTL :: pf_byp [02:02] */
#define BCHP_SDS_BL_PFCTL_pf_byp_MASK                              0x00000004
#define BCHP_SDS_BL_PFCTL_pf_byp_SHIFT                             2
#define BCHP_SDS_BL_PFCTL_pf_byp_DEFAULT                           0

/* SDS_BL :: PFCTL :: pd_sel [01:01] */
#define BCHP_SDS_BL_PFCTL_pd_sel_MASK                              0x00000002
#define BCHP_SDS_BL_PFCTL_pd_sel_SHIFT                             1
#define BCHP_SDS_BL_PFCTL_pd_sel_DEFAULT                           0

/* SDS_BL :: PFCTL :: pf_ebw [00:00] */
#define BCHP_SDS_BL_PFCTL_pf_ebw_MASK                              0x00000001
#define BCHP_SDS_BL_PFCTL_pf_ebw_SHIFT                             0
#define BCHP_SDS_BL_PFCTL_pf_ebw_DEFAULT                           0

/***************************************************************************
 *BRSW - Baud Loop Sweep Configuration
 ***************************************************************************/
/* SDS_BL :: BRSW :: sweep_range [31:16] */
#define BCHP_SDS_BL_BRSW_sweep_range_MASK                          0xffff0000
#define BCHP_SDS_BL_BRSW_sweep_range_SHIFT                         16
#define BCHP_SDS_BL_BRSW_sweep_range_DEFAULT                       0

/* SDS_BL :: BRSW :: sweep_delta [15:00] */
#define BCHP_SDS_BL_BRSW_sweep_delta_MASK                          0x0000ffff
#define BCHP_SDS_BL_BRSW_sweep_delta_SHIFT                         0
#define BCHP_SDS_BL_BRSW_sweep_delta_DEFAULT                       0

/***************************************************************************
 *BRLC - Baud Loop Linear Coefficient
 ***************************************************************************/
/* SDS_BL :: BRLC :: bl_lin_coef [31:08] */
#define BCHP_SDS_BL_BRLC_bl_lin_coef_MASK                          0xffffff00
#define BCHP_SDS_BL_BRLC_bl_lin_coef_SHIFT                         8
#define BCHP_SDS_BL_BRLC_bl_lin_coef_DEFAULT                       0

/* SDS_BL :: BRLC :: reserved0 [07:00] */
#define BCHP_SDS_BL_BRLC_reserved0_MASK                            0x000000ff
#define BCHP_SDS_BL_BRLC_reserved0_SHIFT                           0

/***************************************************************************
 *BRIC - Baud Loop Integrator Coefficient
 ***************************************************************************/
/* SDS_BL :: BRIC :: bl_int_coef [31:00] */
#define BCHP_SDS_BL_BRIC_bl_int_coef_MASK                          0xffffffff
#define BCHP_SDS_BL_BRIC_bl_int_coef_SHIFT                         0
#define BCHP_SDS_BL_BRIC_bl_int_coef_DEFAULT                       0

/***************************************************************************
 *BRI - Baud Loop Integrator Value
 ***************************************************************************/
/* SDS_BL :: BRI :: bl_int [31:00] */
#define BCHP_SDS_BL_BRI_bl_int_MASK                                0xffffffff
#define BCHP_SDS_BL_BRI_bl_int_SHIFT                               0
#define BCHP_SDS_BL_BRI_bl_int_DEFAULT                             0

/***************************************************************************
 *BFOS - Baud Loop Frequency Offset
 ***************************************************************************/
/* SDS_BL :: BFOS :: bl_fos [31:08] */
#define BCHP_SDS_BL_BFOS_bl_fos_MASK                               0xffffff00
#define BCHP_SDS_BL_BFOS_bl_fos_SHIFT                              8
#define BCHP_SDS_BL_BFOS_bl_fos_DEFAULT                            786432

/* SDS_BL :: BFOS :: reserved0 [07:00] */
#define BCHP_SDS_BL_BFOS_reserved0_MASK                            0x000000ff
#define BCHP_SDS_BL_BFOS_reserved0_SHIFT                           0

/***************************************************************************
 *BRFO - Baud Loop Filter Output
 ***************************************************************************/
/* SDS_BL :: BRFO :: bl_lpfilt_out [31:08] */
#define BCHP_SDS_BL_BRFO_bl_lpfilt_out_MASK                        0xffffff00
#define BCHP_SDS_BL_BRFO_bl_lpfilt_out_SHIFT                       8
#define BCHP_SDS_BL_BRFO_bl_lpfilt_out_DEFAULT                     0

/* SDS_BL :: BRFO :: reserved0 [07:00] */
#define BCHP_SDS_BL_BRFO_reserved0_MASK                            0x000000ff
#define BCHP_SDS_BL_BRFO_reserved0_SHIFT                           0

/***************************************************************************
 *BNCO - Baud Loop NCO Contents
 ***************************************************************************/
/* SDS_BL :: BNCO :: bl_nco [31:00] */
#define BCHP_SDS_BL_BNCO_bl_nco_MASK                               0xffffffff
#define BCHP_SDS_BL_BNCO_bl_nco_SHIFT                              0
#define BCHP_SDS_BL_BNCO_bl_nco_DEFAULT                            0

#endif /* #ifndef BCHP_SDS_BL_H__ */

/* End of File */

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
 * Date:           Generated on               Wed Apr 15 16:00:30 2015
 *                 Full Compile MD5 Checksum  798b3ac22e50cf765b00b72a7779366d
 *                     (minus title and desc)
 *                 MD5 Checksum               ccf80b3ba114a13bf874c64a54245c9a
 *
 * Compiled with:  RDB Utility                combo_header.pl
 *                 RDB.pm                     16006
 *                 unknown                    unknown
 *                 Perl Interpreter           5.008008
 *                 Operating System           linux
 *                 Script Source              /tools/dvtsw/current/Linux/combo_header.pl
 *                 DVTSWVER                   current
 *
 *
 ***************************************************************************/

#ifndef BCHP_SDS_FE_0_H__
#define BCHP_SDS_FE_0_H__

/***************************************************************************
 *SDS_FE_0 - SDS Frontend Register Set
 ***************************************************************************/
#define BCHP_SDS_FE_0_ADCPCTL                    0x04000080 /* [RW] ADC Capture Control (Formerly, ADCDBIT, ADCPCLP, ADCPCTL) */
#define BCHP_SDS_FE_0_DCOCTL                     0x04000088 /* [RW] DC Offset Cancellor Control (Formerly, DCOLKCTL, DCOCTL2, DCOCTL1) */
#define BCHP_SDS_FE_0_DCOI                       0x0400008c /* [RW] DCO Integrator Values (Formerly, DCO) */
#define BCHP_SDS_FE_0_IQCTL                      0x04000094 /* [RW] I/Q Imbalance Control (Formerly, IQAMP, IQPHS) */
#define BCHP_SDS_FE_0_IQAEST                     0x04000098 /* [RW] IQ Imbalance Amplitude Integrator Value (Formerly, AEST) */
#define BCHP_SDS_FE_0_IQPEST                     0x0400009c /* [RW] IQ Imbalance Phase Integrator Value (Formerly, PEST) */
#define BCHP_SDS_FE_0_MIXCTL                     0x040000a0 /* [RW] Frontend Mixer Control */
#define BCHP_SDS_FE_0_DSTGCTL                    0x040000a4 /* [RW] Destagger Control */
#define BCHP_SDS_FE_0_FILTCTL                    0x040000a8 /* [RW] Decimating Halfband Filter/Non-decimating Filter Control (Formerly, NDFCTL,FILTCTL) */
#define BCHP_SDS_FE_0_DFCTL                      0x040000ac /* [RW] Decimation Filter Bank Upsampling Control */
#define BCHP_SDS_FE_0_AGFCTL                     0x040000b0 /* [RW] Automatic Fine Gain Control */
#define BCHP_SDS_FE_0_AGF                        0x040000b4 /* [RW] AGF Gain and Threshold Control */
#define BCHP_SDS_FE_0_AIF                        0x040000b8 /* [RW] AGF Integrator Value */
#define BCHP_SDS_FE_0_NVCTL                      0x040000bc /* [RW] Nyquist and VID Filter Control */

/***************************************************************************
 *ADCPCTL - ADC Capture Control (Formerly, ADCDBIT, ADCPCLP, ADCPCTL)
 ***************************************************************************/
/* SDS_FE_0 :: ADCPCTL :: reserved0 [31:24] */
#define BCHP_SDS_FE_0_ADCPCTL_reserved0_MASK                       0xff000000
#define BCHP_SDS_FE_0_ADCPCTL_reserved0_SHIFT                      24

/* SDS_FE_0 :: ADCPCTL :: reserved_for_eco1 [23:23] */
#define BCHP_SDS_FE_0_ADCPCTL_reserved_for_eco1_MASK               0x00800000
#define BCHP_SDS_FE_0_ADCPCTL_reserved_for_eco1_SHIFT              23
#define BCHP_SDS_FE_0_ADCPCTL_reserved_for_eco1_DEFAULT            0x00000000

/* SDS_FE_0 :: ADCPCTL :: adc_out_shift [22:21] */
#define BCHP_SDS_FE_0_ADCPCTL_adc_out_shift_MASK                   0x00600000
#define BCHP_SDS_FE_0_ADCPCTL_adc_out_shift_SHIFT                  21
#define BCHP_SDS_FE_0_ADCPCTL_adc_out_shift_DEFAULT                0x00000000

/* SDS_FE_0 :: ADCPCTL :: ob_tc [20:20] */
#define BCHP_SDS_FE_0_ADCPCTL_ob_tc_MASK                           0x00100000
#define BCHP_SDS_FE_0_ADCPCTL_ob_tc_SHIFT                          20
#define BCHP_SDS_FE_0_ADCPCTL_ob_tc_DEFAULT                        0x00000001

/* SDS_FE_0 :: ADCPCTL :: zero_ctl [19:16] */
#define BCHP_SDS_FE_0_ADCPCTL_zero_ctl_MASK                        0x000f0000
#define BCHP_SDS_FE_0_ADCPCTL_zero_ctl_SHIFT                       16
#define BCHP_SDS_FE_0_ADCPCTL_zero_ctl_DEFAULT                     0x0000000f

/* SDS_FE_0 :: ADCPCTL :: reserved_for_eco2 [15:13] */
#define BCHP_SDS_FE_0_ADCPCTL_reserved_for_eco2_MASK               0x0000e000
#define BCHP_SDS_FE_0_ADCPCTL_reserved_for_eco2_SHIFT              13
#define BCHP_SDS_FE_0_ADCPCTL_reserved_for_eco2_DEFAULT            0x00000000

/* SDS_FE_0 :: ADCPCTL :: q_noclip [12:12] */
#define BCHP_SDS_FE_0_ADCPCTL_q_noclip_MASK                        0x00001000
#define BCHP_SDS_FE_0_ADCPCTL_q_noclip_SHIFT                       12
#define BCHP_SDS_FE_0_ADCPCTL_q_noclip_DEFAULT                     0x00000000

/* SDS_FE_0 :: ADCPCTL :: i_noclip [11:11] */
#define BCHP_SDS_FE_0_ADCPCTL_i_noclip_MASK                        0x00000800
#define BCHP_SDS_FE_0_ADCPCTL_i_noclip_SHIFT                       11
#define BCHP_SDS_FE_0_ADCPCTL_i_noclip_DEFAULT                     0x00000000

/* SDS_FE_0 :: ADCPCTL :: reserved_for_eco3 [10:10] */
#define BCHP_SDS_FE_0_ADCPCTL_reserved_for_eco3_MASK               0x00000400
#define BCHP_SDS_FE_0_ADCPCTL_reserved_for_eco3_SHIFT              10
#define BCHP_SDS_FE_0_ADCPCTL_reserved_for_eco3_DEFAULT            0x00000000

/* SDS_FE_0 :: ADCPCTL :: iq_qi [09:09] */
#define BCHP_SDS_FE_0_ADCPCTL_iq_qi_MASK                           0x00000200
#define BCHP_SDS_FE_0_ADCPCTL_iq_qi_SHIFT                          9
#define BCHP_SDS_FE_0_ADCPCTL_iq_qi_DEFAULT                        0x00000000

/* SDS_FE_0 :: ADCPCTL :: adc_int [08:08] */
#define BCHP_SDS_FE_0_ADCPCTL_adc_int_MASK                         0x00000100
#define BCHP_SDS_FE_0_ADCPCTL_adc_int_SHIFT                        8
#define BCHP_SDS_FE_0_ADCPCTL_adc_int_DEFAULT                      0x00000000

/* SDS_FE_0 :: ADCPCTL :: smpl8_mode [07:07] */
#define BCHP_SDS_FE_0_ADCPCTL_smpl8_mode_MASK                      0x00000080
#define BCHP_SDS_FE_0_ADCPCTL_smpl8_mode_SHIFT                     7
#define BCHP_SDS_FE_0_ADCPCTL_smpl8_mode_DEFAULT                   0x00000000

/* SDS_FE_0 :: ADCPCTL :: iq_phase_sel [06:06] */
#define BCHP_SDS_FE_0_ADCPCTL_iq_phase_sel_MASK                    0x00000040
#define BCHP_SDS_FE_0_ADCPCTL_iq_phase_sel_SHIFT                   6
#define BCHP_SDS_FE_0_ADCPCTL_iq_phase_sel_DEFAULT                 0x00000000

/* SDS_FE_0 :: ADCPCTL :: clkinv [05:05] */
#define BCHP_SDS_FE_0_ADCPCTL_clkinv_MASK                          0x00000020
#define BCHP_SDS_FE_0_ADCPCTL_clkinv_SHIFT                         5
#define BCHP_SDS_FE_0_ADCPCTL_clkinv_DEFAULT                       0x00000001

/* SDS_FE_0 :: ADCPCTL :: reserved_for_eco4 [04:04] */
#define BCHP_SDS_FE_0_ADCPCTL_reserved_for_eco4_MASK               0x00000010
#define BCHP_SDS_FE_0_ADCPCTL_reserved_for_eco4_SHIFT              4
#define BCHP_SDS_FE_0_ADCPCTL_reserved_for_eco4_DEFAULT            0x00000000

/* SDS_FE_0 :: ADCPCTL :: fe_fifo_byp [03:03] */
#define BCHP_SDS_FE_0_ADCPCTL_fe_fifo_byp_MASK                     0x00000008
#define BCHP_SDS_FE_0_ADCPCTL_fe_fifo_byp_SHIFT                    3
#define BCHP_SDS_FE_0_ADCPCTL_fe_fifo_byp_DEFAULT                  0x00000000

/* SDS_FE_0 :: ADCPCTL :: Insel [02:01] */
#define BCHP_SDS_FE_0_ADCPCTL_Insel_MASK                           0x00000006
#define BCHP_SDS_FE_0_ADCPCTL_Insel_SHIFT                          1
#define BCHP_SDS_FE_0_ADCPCTL_Insel_DEFAULT                        0x00000003

/* SDS_FE_0 :: ADCPCTL :: Reset [00:00] */
#define BCHP_SDS_FE_0_ADCPCTL_Reset_MASK                           0x00000001
#define BCHP_SDS_FE_0_ADCPCTL_Reset_SHIFT                          0
#define BCHP_SDS_FE_0_ADCPCTL_Reset_DEFAULT                        0x00000000

/***************************************************************************
 *DCOCTL - DC Offset Cancellor Control (Formerly, DCOLKCTL, DCOCTL2, DCOCTL1)
 ***************************************************************************/
/* SDS_FE_0 :: DCOCTL :: reserved0 [31:24] */
#define BCHP_SDS_FE_0_DCOCTL_reserved0_MASK                        0xff000000
#define BCHP_SDS_FE_0_DCOCTL_reserved0_SHIFT                       24

/* SDS_FE_0 :: DCOCTL :: dco_leak_ctl [23:16] */
#define BCHP_SDS_FE_0_DCOCTL_dco_leak_ctl_MASK                     0x00ff0000
#define BCHP_SDS_FE_0_DCOCTL_dco_leak_ctl_SHIFT                    16
#define BCHP_SDS_FE_0_DCOCTL_dco_leak_ctl_DEFAULT                  0x00000003

/* SDS_FE_0 :: DCOCTL :: reserved_for_eco1 [15:15] */
#define BCHP_SDS_FE_0_DCOCTL_reserved_for_eco1_MASK                0x00008000
#define BCHP_SDS_FE_0_DCOCTL_reserved_for_eco1_SHIFT               15
#define BCHP_SDS_FE_0_DCOCTL_reserved_for_eco1_DEFAULT             0x00000000

/* SDS_FE_0 :: DCOCTL :: dco_ds_inv [14:14] */
#define BCHP_SDS_FE_0_DCOCTL_dco_ds_inv_MASK                       0x00004000
#define BCHP_SDS_FE_0_DCOCTL_dco_ds_inv_SHIFT                      14
#define BCHP_SDS_FE_0_DCOCTL_dco_ds_inv_DEFAULT                    0x00000000

/* SDS_FE_0 :: DCOCTL :: dco_ctl [13:10] */
#define BCHP_SDS_FE_0_DCOCTL_dco_ctl_MASK                          0x00003c00
#define BCHP_SDS_FE_0_DCOCTL_dco_ctl_SHIFT                         10
#define BCHP_SDS_FE_0_DCOCTL_dco_ctl_DEFAULT                       0x00000000

/* SDS_FE_0 :: DCOCTL :: dco_rst [09:09] */
#define BCHP_SDS_FE_0_DCOCTL_dco_rst_MASK                          0x00000200
#define BCHP_SDS_FE_0_DCOCTL_dco_rst_SHIFT                         9
#define BCHP_SDS_FE_0_DCOCTL_dco_rst_DEFAULT                       0x00000000

/* SDS_FE_0 :: DCOCTL :: dco_ds_rst [08:08] */
#define BCHP_SDS_FE_0_DCOCTL_dco_ds_rst_MASK                       0x00000100
#define BCHP_SDS_FE_0_DCOCTL_dco_ds_rst_SHIFT                      8
#define BCHP_SDS_FE_0_DCOCTL_dco_ds_rst_DEFAULT                    0x00000001

/* SDS_FE_0 :: DCOCTL :: if_mode [07:07] */
#define BCHP_SDS_FE_0_DCOCTL_if_mode_MASK                          0x00000080
#define BCHP_SDS_FE_0_DCOCTL_if_mode_SHIFT                         7
#define BCHP_SDS_FE_0_DCOCTL_if_mode_DEFAULT                       0x00000000

/* SDS_FE_0 :: DCOCTL :: reserved_for_eco2 [06:06] */
#define BCHP_SDS_FE_0_DCOCTL_reserved_for_eco2_MASK                0x00000040
#define BCHP_SDS_FE_0_DCOCTL_reserved_for_eco2_SHIFT               6
#define BCHP_SDS_FE_0_DCOCTL_reserved_for_eco2_DEFAULT             0x00000000

/* SDS_FE_0 :: DCOCTL :: ext_dco [05:05] */
#define BCHP_SDS_FE_0_DCOCTL_ext_dco_MASK                          0x00000020
#define BCHP_SDS_FE_0_DCOCTL_ext_dco_SHIFT                         5
#define BCHP_SDS_FE_0_DCOCTL_ext_dco_DEFAULT                       0x00000000

/* SDS_FE_0 :: DCOCTL :: dco_freeze [04:04] */
#define BCHP_SDS_FE_0_DCOCTL_dco_freeze_MASK                       0x00000010
#define BCHP_SDS_FE_0_DCOCTL_dco_freeze_SHIFT                      4
#define BCHP_SDS_FE_0_DCOCTL_dco_freeze_DEFAULT                    0x00000001

/* SDS_FE_0 :: DCOCTL :: reserved_for_eco3 [03:03] */
#define BCHP_SDS_FE_0_DCOCTL_reserved_for_eco3_MASK                0x00000008
#define BCHP_SDS_FE_0_DCOCTL_reserved_for_eco3_SHIFT               3
#define BCHP_SDS_FE_0_DCOCTL_reserved_for_eco3_DEFAULT             0x00000000

/* SDS_FE_0 :: DCOCTL :: dco_out_dec [02:01] */
#define BCHP_SDS_FE_0_DCOCTL_dco_out_dec_MASK                      0x00000006
#define BCHP_SDS_FE_0_DCOCTL_dco_out_dec_SHIFT                     1
#define BCHP_SDS_FE_0_DCOCTL_dco_out_dec_DEFAULT                   0x00000000

/* SDS_FE_0 :: DCOCTL :: dco_byp [00:00] */
#define BCHP_SDS_FE_0_DCOCTL_dco_byp_MASK                          0x00000001
#define BCHP_SDS_FE_0_DCOCTL_dco_byp_SHIFT                         0
#define BCHP_SDS_FE_0_DCOCTL_dco_byp_DEFAULT                       0x00000000

/***************************************************************************
 *DCOI - DCO Integrator Values (Formerly, DCO)
 ***************************************************************************/
/* SDS_FE_0 :: DCOI :: dco_int_val_q [31:16] */
#define BCHP_SDS_FE_0_DCOI_dco_int_val_q_MASK                      0xffff0000
#define BCHP_SDS_FE_0_DCOI_dco_int_val_q_SHIFT                     16
#define BCHP_SDS_FE_0_DCOI_dco_int_val_q_DEFAULT                   0x00000000

/* SDS_FE_0 :: DCOI :: dco_int_val_i [15:00] */
#define BCHP_SDS_FE_0_DCOI_dco_int_val_i_MASK                      0x0000ffff
#define BCHP_SDS_FE_0_DCOI_dco_int_val_i_SHIFT                     0
#define BCHP_SDS_FE_0_DCOI_dco_int_val_i_DEFAULT                   0x00000000

/***************************************************************************
 *IQCTL - I/Q Imbalance Control (Formerly, IQAMP, IQPHS)
 ***************************************************************************/
/* SDS_FE_0 :: IQCTL :: reserved0 [31:16] */
#define BCHP_SDS_FE_0_IQCTL_reserved0_MASK                         0xffff0000
#define BCHP_SDS_FE_0_IQCTL_reserved0_SHIFT                        16

/* SDS_FE_0 :: IQCTL :: iqphs_shift [15:12] */
#define BCHP_SDS_FE_0_IQCTL_iqphs_shift_MASK                       0x0000f000
#define BCHP_SDS_FE_0_IQCTL_iqphs_shift_SHIFT                      12
#define BCHP_SDS_FE_0_IQCTL_iqphs_shift_DEFAULT                    0x00000000

/* SDS_FE_0 :: IQCTL :: reserved_for_eco1 [11:10] */
#define BCHP_SDS_FE_0_IQCTL_reserved_for_eco1_MASK                 0x00000c00
#define BCHP_SDS_FE_0_IQCTL_reserved_for_eco1_SHIFT                10
#define BCHP_SDS_FE_0_IQCTL_reserved_for_eco1_DEFAULT              0x00000000

/* SDS_FE_0 :: IQCTL :: iqphs_byp [09:09] */
#define BCHP_SDS_FE_0_IQCTL_iqphs_byp_MASK                         0x00000200
#define BCHP_SDS_FE_0_IQCTL_iqphs_byp_SHIFT                        9
#define BCHP_SDS_FE_0_IQCTL_iqphs_byp_DEFAULT                      0x00000001

/* SDS_FE_0 :: IQCTL :: iqphs_freeze [08:08] */
#define BCHP_SDS_FE_0_IQCTL_iqphs_freeze_MASK                      0x00000100
#define BCHP_SDS_FE_0_IQCTL_iqphs_freeze_SHIFT                     8
#define BCHP_SDS_FE_0_IQCTL_iqphs_freeze_DEFAULT                   0x00000001

/* SDS_FE_0 :: IQCTL :: iqamp_shift [07:04] */
#define BCHP_SDS_FE_0_IQCTL_iqamp_shift_MASK                       0x000000f0
#define BCHP_SDS_FE_0_IQCTL_iqamp_shift_SHIFT                      4
#define BCHP_SDS_FE_0_IQCTL_iqamp_shift_DEFAULT                    0x00000000

/* SDS_FE_0 :: IQCTL :: reserved_for_eco2 [03:03] */
#define BCHP_SDS_FE_0_IQCTL_reserved_for_eco2_MASK                 0x00000008
#define BCHP_SDS_FE_0_IQCTL_reserved_for_eco2_SHIFT                3
#define BCHP_SDS_FE_0_IQCTL_reserved_for_eco2_DEFAULT              0x00000000

/* SDS_FE_0 :: IQCTL :: iqamp_byp [02:02] */
#define BCHP_SDS_FE_0_IQCTL_iqamp_byp_MASK                         0x00000004
#define BCHP_SDS_FE_0_IQCTL_iqamp_byp_SHIFT                        2
#define BCHP_SDS_FE_0_IQCTL_iqamp_byp_DEFAULT                      0x00000001

/* SDS_FE_0 :: IQCTL :: iqamp_freeze [01:01] */
#define BCHP_SDS_FE_0_IQCTL_iqamp_freeze_MASK                      0x00000002
#define BCHP_SDS_FE_0_IQCTL_iqamp_freeze_SHIFT                     1
#define BCHP_SDS_FE_0_IQCTL_iqamp_freeze_DEFAULT                   0x00000001

/* SDS_FE_0 :: IQCTL :: iq_rst [00:00] */
#define BCHP_SDS_FE_0_IQCTL_iq_rst_MASK                            0x00000001
#define BCHP_SDS_FE_0_IQCTL_iq_rst_SHIFT                           0
#define BCHP_SDS_FE_0_IQCTL_iq_rst_DEFAULT                         0x00000000

/***************************************************************************
 *IQAEST - IQ Imbalance Amplitude Integrator Value (Formerly, AEST)
 ***************************************************************************/
/* SDS_FE_0 :: IQAEST :: iq_amp_int [31:00] */
#define BCHP_SDS_FE_0_IQAEST_iq_amp_int_MASK                       0xffffffff
#define BCHP_SDS_FE_0_IQAEST_iq_amp_int_SHIFT                      0
#define BCHP_SDS_FE_0_IQAEST_iq_amp_int_DEFAULT                    0x00000000

/***************************************************************************
 *IQPEST - IQ Imbalance Phase Integrator Value (Formerly, PEST)
 ***************************************************************************/
/* SDS_FE_0 :: IQPEST :: iq_phs_int [31:00] */
#define BCHP_SDS_FE_0_IQPEST_iq_phs_int_MASK                       0xffffffff
#define BCHP_SDS_FE_0_IQPEST_iq_phs_int_SHIFT                      0
#define BCHP_SDS_FE_0_IQPEST_iq_phs_int_DEFAULT                    0x00000000

/***************************************************************************
 *MIXCTL - Frontend Mixer Control
 ***************************************************************************/
/* SDS_FE_0 :: MIXCTL :: reserved0 [31:08] */
#define BCHP_SDS_FE_0_MIXCTL_reserved0_MASK                        0xffffff00
#define BCHP_SDS_FE_0_MIXCTL_reserved0_SHIFT                       8

/* SDS_FE_0 :: MIXCTL :: reserved_for_eco1 [07:05] */
#define BCHP_SDS_FE_0_MIXCTL_reserved_for_eco1_MASK                0x000000e0
#define BCHP_SDS_FE_0_MIXCTL_reserved_for_eco1_SHIFT               5
#define BCHP_SDS_FE_0_MIXCTL_reserved_for_eco1_DEFAULT             0x00000000

/* SDS_FE_0 :: MIXCTL :: mixer_byp [04:04] */
#define BCHP_SDS_FE_0_MIXCTL_mixer_byp_MASK                        0x00000010
#define BCHP_SDS_FE_0_MIXCTL_mixer_byp_SHIFT                       4
#define BCHP_SDS_FE_0_MIXCTL_mixer_byp_DEFAULT                     0x00000000

/* SDS_FE_0 :: MIXCTL :: reserved_for_eco2 [03:02] */
#define BCHP_SDS_FE_0_MIXCTL_reserved_for_eco2_MASK                0x0000000c
#define BCHP_SDS_FE_0_MIXCTL_reserved_for_eco2_SHIFT               2
#define BCHP_SDS_FE_0_MIXCTL_reserved_for_eco2_DEFAULT             0x00000000

/* SDS_FE_0 :: MIXCTL :: spinv_pre [01:01] */
#define BCHP_SDS_FE_0_MIXCTL_spinv_pre_MASK                        0x00000002
#define BCHP_SDS_FE_0_MIXCTL_spinv_pre_SHIFT                       1
#define BCHP_SDS_FE_0_MIXCTL_spinv_pre_DEFAULT                     0x00000000

/* SDS_FE_0 :: MIXCTL :: mix_shift [00:00] */
#define BCHP_SDS_FE_0_MIXCTL_mix_shift_MASK                        0x00000001
#define BCHP_SDS_FE_0_MIXCTL_mix_shift_SHIFT                       0
#define BCHP_SDS_FE_0_MIXCTL_mix_shift_DEFAULT                     0x00000001

/***************************************************************************
 *DSTGCTL - Destagger Control
 ***************************************************************************/
/* SDS_FE_0 :: DSTGCTL :: reserved0 [31:08] */
#define BCHP_SDS_FE_0_DSTGCTL_reserved0_MASK                       0xffffff00
#define BCHP_SDS_FE_0_DSTGCTL_reserved0_SHIFT                      8

/* SDS_FE_0 :: DSTGCTL :: reserved_for_eco1 [07:03] */
#define BCHP_SDS_FE_0_DSTGCTL_reserved_for_eco1_MASK               0x000000f8
#define BCHP_SDS_FE_0_DSTGCTL_reserved_for_eco1_SHIFT              3
#define BCHP_SDS_FE_0_DSTGCTL_reserved_for_eco1_DEFAULT            0x00000000

/* SDS_FE_0 :: DSTGCTL :: iq_swap_back [02:02] */
#define BCHP_SDS_FE_0_DSTGCTL_iq_swap_back_MASK                    0x00000004
#define BCHP_SDS_FE_0_DSTGCTL_iq_swap_back_SHIFT                   2
#define BCHP_SDS_FE_0_DSTGCTL_iq_swap_back_DEFAULT                 0x00000000

/* SDS_FE_0 :: DSTGCTL :: iq_swap_front [01:01] */
#define BCHP_SDS_FE_0_DSTGCTL_iq_swap_front_MASK                   0x00000002
#define BCHP_SDS_FE_0_DSTGCTL_iq_swap_front_SHIFT                  1
#define BCHP_SDS_FE_0_DSTGCTL_iq_swap_front_DEFAULT                0x00000000

/* SDS_FE_0 :: DSTGCTL :: destag_bypass [00:00] */
#define BCHP_SDS_FE_0_DSTGCTL_destag_bypass_MASK                   0x00000001
#define BCHP_SDS_FE_0_DSTGCTL_destag_bypass_SHIFT                  0
#define BCHP_SDS_FE_0_DSTGCTL_destag_bypass_DEFAULT                0x00000000

/***************************************************************************
 *FILTCTL - Decimating Halfband Filter/Non-decimating Filter Control (Formerly, NDFCTL,FILTCTL)
 ***************************************************************************/
/* SDS_FE_0 :: FILTCTL :: reserved0 [31:16] */
#define BCHP_SDS_FE_0_FILTCTL_reserved0_MASK                       0xffff0000
#define BCHP_SDS_FE_0_FILTCTL_reserved0_SHIFT                      16

/* SDS_FE_0 :: FILTCTL :: hf_sel [15:14] */
#define BCHP_SDS_FE_0_FILTCTL_hf_sel_MASK                          0x0000c000
#define BCHP_SDS_FE_0_FILTCTL_hf_sel_SHIFT                         14
#define BCHP_SDS_FE_0_FILTCTL_hf_sel_DEFAULT                       0x00000000

/* SDS_FE_0 :: FILTCTL :: hf_mask [13:08] */
#define BCHP_SDS_FE_0_FILTCTL_hf_mask_MASK                         0x00003f00
#define BCHP_SDS_FE_0_FILTCTL_hf_mask_SHIFT                        8
#define BCHP_SDS_FE_0_FILTCTL_hf_mask_DEFAULT                      0x00000000

/* SDS_FE_0 :: FILTCTL :: byp_he2 [07:07] */
#define BCHP_SDS_FE_0_FILTCTL_byp_he2_MASK                         0x00000080
#define BCHP_SDS_FE_0_FILTCTL_byp_he2_SHIFT                        7
#define BCHP_SDS_FE_0_FILTCTL_byp_he2_DEFAULT                      0x00000001

/* SDS_FE_0 :: FILTCTL :: byp_h0 [06:06] */
#define BCHP_SDS_FE_0_FILTCTL_byp_h0_MASK                          0x00000040
#define BCHP_SDS_FE_0_FILTCTL_byp_h0_SHIFT                         6
#define BCHP_SDS_FE_0_FILTCTL_byp_h0_DEFAULT                       0x00000001

/* SDS_FE_0 :: FILTCTL :: byp_hf [05:05] */
#define BCHP_SDS_FE_0_FILTCTL_byp_hf_MASK                          0x00000020
#define BCHP_SDS_FE_0_FILTCTL_byp_hf_SHIFT                         5
#define BCHP_SDS_FE_0_FILTCTL_byp_hf_DEFAULT                       0x00000000

/* SDS_FE_0 :: FILTCTL :: byp_he1 [04:04] */
#define BCHP_SDS_FE_0_FILTCTL_byp_he1_MASK                         0x00000010
#define BCHP_SDS_FE_0_FILTCTL_byp_he1_SHIFT                        4
#define BCHP_SDS_FE_0_FILTCTL_byp_he1_DEFAULT                      0x00000001

/* SDS_FE_0 :: FILTCTL :: byp_hd [03:03] */
#define BCHP_SDS_FE_0_FILTCTL_byp_hd_MASK                          0x00000008
#define BCHP_SDS_FE_0_FILTCTL_byp_hd_SHIFT                         3
#define BCHP_SDS_FE_0_FILTCTL_byp_hd_DEFAULT                       0x00000001

/* SDS_FE_0 :: FILTCTL :: byp_hc [02:02] */
#define BCHP_SDS_FE_0_FILTCTL_byp_hc_MASK                          0x00000004
#define BCHP_SDS_FE_0_FILTCTL_byp_hc_SHIFT                         2
#define BCHP_SDS_FE_0_FILTCTL_byp_hc_DEFAULT                       0x00000001

/* SDS_FE_0 :: FILTCTL :: byp_hb [01:01] */
#define BCHP_SDS_FE_0_FILTCTL_byp_hb_MASK                          0x00000002
#define BCHP_SDS_FE_0_FILTCTL_byp_hb_SHIFT                         1
#define BCHP_SDS_FE_0_FILTCTL_byp_hb_DEFAULT                       0x00000001

/* SDS_FE_0 :: FILTCTL :: byp_ha [00:00] */
#define BCHP_SDS_FE_0_FILTCTL_byp_ha_MASK                          0x00000001
#define BCHP_SDS_FE_0_FILTCTL_byp_ha_SHIFT                         0
#define BCHP_SDS_FE_0_FILTCTL_byp_ha_DEFAULT                       0x00000001

/***************************************************************************
 *DFCTL - Decimation Filter Bank Upsampling Control
 ***************************************************************************/
/* SDS_FE_0 :: DFCTL :: reserved0 [31:08] */
#define BCHP_SDS_FE_0_DFCTL_reserved0_MASK                         0xffffff00
#define BCHP_SDS_FE_0_DFCTL_reserved0_SHIFT                        8

/* SDS_FE_0 :: DFCTL :: reserved_for_eco1 [07:06] */
#define BCHP_SDS_FE_0_DFCTL_reserved_for_eco1_MASK                 0x000000c0
#define BCHP_SDS_FE_0_DFCTL_reserved_for_eco1_SHIFT                6
#define BCHP_SDS_FE_0_DFCTL_reserved_for_eco1_DEFAULT              0x00000000

/* SDS_FE_0 :: DFCTL :: dec_gain [05:04] */
#define BCHP_SDS_FE_0_DFCTL_dec_gain_MASK                          0x00000030
#define BCHP_SDS_FE_0_DFCTL_dec_gain_SHIFT                         4
#define BCHP_SDS_FE_0_DFCTL_dec_gain_DEFAULT                       0x00000000

/* SDS_FE_0 :: DFCTL :: reserved_for_eco2 [03:01] */
#define BCHP_SDS_FE_0_DFCTL_reserved_for_eco2_MASK                 0x0000000e
#define BCHP_SDS_FE_0_DFCTL_reserved_for_eco2_SHIFT                1
#define BCHP_SDS_FE_0_DFCTL_reserved_for_eco2_DEFAULT              0x00000000

/* SDS_FE_0 :: DFCTL :: Upsample [00:00] */
#define BCHP_SDS_FE_0_DFCTL_Upsample_MASK                          0x00000001
#define BCHP_SDS_FE_0_DFCTL_Upsample_SHIFT                         0
#define BCHP_SDS_FE_0_DFCTL_Upsample_DEFAULT                       0x00000000

/***************************************************************************
 *AGFCTL - Automatic Fine Gain Control
 ***************************************************************************/
/* SDS_FE_0 :: AGFCTL :: reserved0 [31:08] */
#define BCHP_SDS_FE_0_AGFCTL_reserved0_MASK                        0xffffff00
#define BCHP_SDS_FE_0_AGFCTL_reserved0_SHIFT                       8

/* SDS_FE_0 :: AGFCTL :: use_status [07:07] */
#define BCHP_SDS_FE_0_AGFCTL_use_status_MASK                       0x00000080
#define BCHP_SDS_FE_0_AGFCTL_use_status_SHIFT                      7
#define BCHP_SDS_FE_0_AGFCTL_use_status_DEFAULT                    0x00000000

/* SDS_FE_0 :: AGFCTL :: Status [06:06] */
#define BCHP_SDS_FE_0_AGFCTL_Status_MASK                           0x00000040
#define BCHP_SDS_FE_0_AGFCTL_Status_SHIFT                          6
#define BCHP_SDS_FE_0_AGFCTL_Status_DEFAULT                        0x00000000

/* SDS_FE_0 :: AGFCTL :: reserved_for_eco1 [05:03] */
#define BCHP_SDS_FE_0_AGFCTL_reserved_for_eco1_MASK                0x00000038
#define BCHP_SDS_FE_0_AGFCTL_reserved_for_eco1_SHIFT               3
#define BCHP_SDS_FE_0_AGFCTL_reserved_for_eco1_DEFAULT             0x00000000

/* SDS_FE_0 :: AGFCTL :: agf_frz [02:02] */
#define BCHP_SDS_FE_0_AGFCTL_agf_frz_MASK                          0x00000004
#define BCHP_SDS_FE_0_AGFCTL_agf_frz_SHIFT                         2
#define BCHP_SDS_FE_0_AGFCTL_agf_frz_DEFAULT                       0x00000001

/* SDS_FE_0 :: AGFCTL :: agf_byp [01:01] */
#define BCHP_SDS_FE_0_AGFCTL_agf_byp_MASK                          0x00000002
#define BCHP_SDS_FE_0_AGFCTL_agf_byp_SHIFT                         1
#define BCHP_SDS_FE_0_AGFCTL_agf_byp_DEFAULT                       0x00000000

/* SDS_FE_0 :: AGFCTL :: agf_rst [00:00] */
#define BCHP_SDS_FE_0_AGFCTL_agf_rst_MASK                          0x00000001
#define BCHP_SDS_FE_0_AGFCTL_agf_rst_SHIFT                         0
#define BCHP_SDS_FE_0_AGFCTL_agf_rst_DEFAULT                       0x00000000

/***************************************************************************
 *AGF - AGF Gain and Threshold Control
 ***************************************************************************/
/* SDS_FE_0 :: AGF :: reserved0 [31:28] */
#define BCHP_SDS_FE_0_AGF_reserved0_MASK                           0xf0000000
#define BCHP_SDS_FE_0_AGF_reserved0_SHIFT                          28

/* SDS_FE_0 :: AGF :: agf_ctl [27:24] */
#define BCHP_SDS_FE_0_AGF_agf_ctl_MASK                             0x0f000000
#define BCHP_SDS_FE_0_AGF_agf_ctl_SHIFT                            24
#define BCHP_SDS_FE_0_AGF_agf_ctl_DEFAULT                          0x0000000d

/* SDS_FE_0 :: AGF :: agf_threshold [23:08] */
#define BCHP_SDS_FE_0_AGF_agf_threshold_MASK                       0x00ffff00
#define BCHP_SDS_FE_0_AGF_agf_threshold_SHIFT                      8
#define BCHP_SDS_FE_0_AGF_agf_threshold_DEFAULT                    0x00002000

/* SDS_FE_0 :: AGF :: reserved1 [07:00] */
#define BCHP_SDS_FE_0_AGF_reserved1_MASK                           0x000000ff
#define BCHP_SDS_FE_0_AGF_reserved1_SHIFT                          0

/***************************************************************************
 *AIF - AGF Integrator Value
 ***************************************************************************/
/* SDS_FE_0 :: AIF :: agf_int_val [31:08] */
#define BCHP_SDS_FE_0_AIF_agf_int_val_MASK                         0xffffff00
#define BCHP_SDS_FE_0_AIF_agf_int_val_SHIFT                        8
#define BCHP_SDS_FE_0_AIF_agf_int_val_DEFAULT                      0x00100000

/* SDS_FE_0 :: AIF :: reserved0 [07:00] */
#define BCHP_SDS_FE_0_AIF_reserved0_MASK                           0x000000ff
#define BCHP_SDS_FE_0_AIF_reserved0_SHIFT                          0

/***************************************************************************
 *NVCTL - Nyquist and VID Filter Control
 ***************************************************************************/
/* SDS_FE_0 :: NVCTL :: reserved0 [31:10] */
#define BCHP_SDS_FE_0_NVCTL_reserved0_MASK                         0xfffffc00
#define BCHP_SDS_FE_0_NVCTL_reserved0_SHIFT                        10

/* SDS_FE_0 :: NVCTL :: nyq_alpha [09:08] */
#define BCHP_SDS_FE_0_NVCTL_nyq_alpha_MASK                         0x00000300
#define BCHP_SDS_FE_0_NVCTL_nyq_alpha_SHIFT                        8
#define BCHP_SDS_FE_0_NVCTL_nyq_alpha_DEFAULT                      0x00000000

/* SDS_FE_0 :: NVCTL :: vid_alpha [07:06] */
#define BCHP_SDS_FE_0_NVCTL_vid_alpha_MASK                         0x000000c0
#define BCHP_SDS_FE_0_NVCTL_vid_alpha_SHIFT                        6
#define BCHP_SDS_FE_0_NVCTL_vid_alpha_DEFAULT                      0x00000001

/* SDS_FE_0 :: NVCTL :: nyq_byp [05:05] */
#define BCHP_SDS_FE_0_NVCTL_nyq_byp_MASK                           0x00000020
#define BCHP_SDS_FE_0_NVCTL_nyq_byp_SHIFT                          5
#define BCHP_SDS_FE_0_NVCTL_nyq_byp_DEFAULT                        0x00000000

/* SDS_FE_0 :: NVCTL :: nyq_gain [04:03] */
#define BCHP_SDS_FE_0_NVCTL_nyq_gain_MASK                          0x00000018
#define BCHP_SDS_FE_0_NVCTL_nyq_gain_SHIFT                         3
#define BCHP_SDS_FE_0_NVCTL_nyq_gain_DEFAULT                       0x00000000

/* SDS_FE_0 :: NVCTL :: reserved_for_eco1 [02:02] */
#define BCHP_SDS_FE_0_NVCTL_reserved_for_eco1_MASK                 0x00000004
#define BCHP_SDS_FE_0_NVCTL_reserved_for_eco1_SHIFT                2
#define BCHP_SDS_FE_0_NVCTL_reserved_for_eco1_DEFAULT              0x00000000

/* SDS_FE_0 :: NVCTL :: vid_byp [01:00] */
#define BCHP_SDS_FE_0_NVCTL_vid_byp_MASK                           0x00000003
#define BCHP_SDS_FE_0_NVCTL_vid_byp_SHIFT                          0
#define BCHP_SDS_FE_0_NVCTL_vid_byp_DEFAULT                        0x00000000

#endif /* #ifndef BCHP_SDS_FE_0_H__ */

/* End of File */

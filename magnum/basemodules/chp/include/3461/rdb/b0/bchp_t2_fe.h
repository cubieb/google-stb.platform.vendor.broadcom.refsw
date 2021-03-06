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
 * Date:           Generated on         Thu May  5 11:23:20 2011
 *                 MD5 Checksum         9989cc87dbf3a85de8aa1d7c29dab260
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

#ifndef BCHP_T2_FE_H__
#define BCHP_T2_FE_H__

/***************************************************************************
 *T2_FE - T2 Frontend Registers
 ***************************************************************************/
#define BCHP_T2_FE_FE                            0x000d0200 /* Front End Control */
#define BCHP_T2_FE_IMPE                          0x000d0204 /* Impulse Erasure Control */
#define BCHP_T2_FE_IMPE_ERASE                    0x000d0208 /* Impulse Erasure Values */
#define BCHP_T2_FE_IMPE_INST_THR                 0x000d020c /* Impulse Erasure Instantaneous Threshold */
#define BCHP_T2_FE_IMPE_MA_THR                   0x000d0210 /* Impulse Erasure Moving Average Threshold */
#define BCHP_T2_FE_IMPE_ERASE_CNT                0x000d0214 /* Impulse Erasure Count */
#define BCHP_T2_FE_CL                            0x000d0218 /* Carrier Loop Control */
#define BCHP_T2_FE_CL_FCW                        0x000d021c /* Carrier Loop Frequency Control Word */
#define BCHP_T2_FE_CL_COEF                       0x000d0220 /* Carrier Loop Coefficients */
#define BCHP_T2_FE_CL_FEST                       0x000d0224 /* Carrier Loop Fractional Estimates */
#define BCHP_T2_FE_CL_IEST                       0x000d0228 /* Carrier Loop Integer Estimate */
#define BCHP_T2_FE_CL_INT                        0x000d022c /* Carrier Loop Integrator */
#define BCHP_T2_FE_CL_LFO                        0x000d0230 /* Carrier Loop Filter Output */
#define BCHP_T2_FE_CL_PA                         0x000d0234 /* Carrier Loop Phase Accumulator */
#define BCHP_T2_FE_TL_FCW                        0x000d0238 /* Timing Loop Frequency Control Word */
#define BCHP_T2_FE_TL_COEF                       0x000d023c /* Timing Loop Coefficients */
#define BCHP_T2_FE_TL_EST                        0x000d0240 /* Timing Loop Estimate */
#define BCHP_T2_FE_TL_INT                        0x000d0244 /* Timing Loop Integrator */
#define BCHP_T2_FE_TL_LFO                        0x000d0248 /* Timing Loop Filter Output */
#define BCHP_T2_FE_TL_NCO                        0x000d024c /* Timing Loop NCO */
#define BCHP_T2_FE_DAGC                          0x000d0250 /* Digital AGC2 Loop Control */
#define BCHP_T2_FE_DAGC_INT                      0x000d0254 /* Digital AGC2 Loop Filter Output */
#define BCHP_T2_FE_DAGC_UPDATE                   0x000d0258 /* Digital AGC2 Loop Update Control */
#define BCHP_T2_FE_NOTCH_CTL                     0x000d025c /* Notch Control */
#define BCHP_T2_FE_NOTCH_WIDTH                   0x000d0260 /* Notch Width */
#define BCHP_T2_FE_NOTCH_DEPTH                   0x000d0264 /* Notch Depth */
#define BCHP_T2_FE_NOTCH0_FCW                    0x000d0268 /* Notch0 Frequency Control Word */
#define BCHP_T2_FE_NOTCH1_FCW                    0x000d026c /* Notch1 Frequency Control Word */
#define BCHP_T2_FE_NOTCH2_FCW                    0x000d0270 /* Notch2 Frequency Control Word */
#define BCHP_T2_FE_NOTCH3_FCW                    0x000d0274 /* Notch3 Frequency Control Word */
#define BCHP_T2_FE_NOTCH4_FCW                    0x000d0278 /* Notch4 Frequency Control Word */
#define BCHP_T2_FE_NOTCH5_FCW                    0x000d027c /* Notch5 Frequency Control Word */
#define BCHP_T2_FE_NOTCH0_INT                    0x000d0280 /* Notch0 Integrator */
#define BCHP_T2_FE_NOTCH1_INT                    0x000d0284 /* Notch1 Integrator */
#define BCHP_T2_FE_NOTCH2_INT                    0x000d0288 /* Notch2 Integrator */
#define BCHP_T2_FE_NOTCH3_INT                    0x000d028c /* Notch3 Integrator */
#define BCHP_T2_FE_NOTCH4_INT                    0x000d0290 /* Notch4 Integrator */
#define BCHP_T2_FE_ECO_SPARE0                    0x000d0294 /* ECO Spare 0 Register */
#define BCHP_T2_FE_ECO_SPARE1                    0x000d0298 /* ECO Spare 1 Register */

/***************************************************************************
 *FE - Front End Control
 ***************************************************************************/
/* T2_FE :: FE :: reserved0 [31:08] */
#define BCHP_T2_FE_FE_reserved0_MASK                               0xffffff00
#define BCHP_T2_FE_FE_reserved0_SHIFT                              8

/* T2_FE :: FE :: INPUT_CLKINV [07:07] */
#define BCHP_T2_FE_FE_INPUT_CLKINV_MASK                            0x00000080
#define BCHP_T2_FE_FE_INPUT_CLKINV_SHIFT                           7
#define BCHP_T2_FE_FE_INPUT_CLKINV_DEFAULT                         0

/* T2_FE :: FE :: INPUT_ALIGN [06:05] */
#define BCHP_T2_FE_FE_INPUT_ALIGN_MASK                             0x00000060
#define BCHP_T2_FE_FE_INPUT_ALIGN_SHIFT                            5
#define BCHP_T2_FE_FE_INPUT_ALIGN_DEFAULT                          0

/* T2_FE :: FE :: SWAP_IQ [04:04] */
#define BCHP_T2_FE_FE_SWAP_IQ_MASK                                 0x00000010
#define BCHP_T2_FE_FE_SWAP_IQ_SHIFT                                4
#define BCHP_T2_FE_FE_SWAP_IQ_DEFAULT                              0

/* T2_FE :: FE :: NEGATE_I [03:03] */
#define BCHP_T2_FE_FE_NEGATE_I_MASK                                0x00000008
#define BCHP_T2_FE_FE_NEGATE_I_SHIFT                               3
#define BCHP_T2_FE_FE_NEGATE_I_DEFAULT                             0

/* T2_FE :: FE :: NEGATE_Q [02:02] */
#define BCHP_T2_FE_FE_NEGATE_Q_MASK                                0x00000004
#define BCHP_T2_FE_FE_NEGATE_Q_SHIFT                               2
#define BCHP_T2_FE_FE_NEGATE_Q_DEFAULT                             0

/* T2_FE :: FE :: SPINV [01:01] */
#define BCHP_T2_FE_FE_SPINV_MASK                                   0x00000002
#define BCHP_T2_FE_FE_SPINV_SHIFT                                  1
#define BCHP_T2_FE_FE_SPINV_DEFAULT                                0

/* T2_FE :: FE :: INPUT_EDGE [00:00] */
#define BCHP_T2_FE_FE_INPUT_EDGE_MASK                              0x00000001
#define BCHP_T2_FE_FE_INPUT_EDGE_SHIFT                             0
#define BCHP_T2_FE_FE_INPUT_EDGE_DEFAULT                           0

/***************************************************************************
 *IMPE - Impulse Erasure Control
 ***************************************************************************/
/* T2_FE :: IMPE :: reserved0 [31:03] */
#define BCHP_T2_FE_IMPE_reserved0_MASK                             0xfffffff8
#define BCHP_T2_FE_IMPE_reserved0_SHIFT                            3

/* T2_FE :: IMPE :: NSEL [02:00] */
#define BCHP_T2_FE_IMPE_NSEL_MASK                                  0x00000007
#define BCHP_T2_FE_IMPE_NSEL_SHIFT                                 0
#define BCHP_T2_FE_IMPE_NSEL_DEFAULT                               0

/***************************************************************************
 *IMPE_ERASE - Impulse Erasure Values
 ***************************************************************************/
/* T2_FE :: IMPE_ERASE :: reserved0 [31:30] */
#define BCHP_T2_FE_IMPE_ERASE_reserved0_MASK                       0xc0000000
#define BCHP_T2_FE_IMPE_ERASE_reserved0_SHIFT                      30

/* T2_FE :: IMPE_ERASE :: VAL_I [29:16] */
#define BCHP_T2_FE_IMPE_ERASE_VAL_I_MASK                           0x3fff0000
#define BCHP_T2_FE_IMPE_ERASE_VAL_I_SHIFT                          16
#define BCHP_T2_FE_IMPE_ERASE_VAL_I_DEFAULT                        0

/* T2_FE :: IMPE_ERASE :: reserved1 [15:14] */
#define BCHP_T2_FE_IMPE_ERASE_reserved1_MASK                       0x0000c000
#define BCHP_T2_FE_IMPE_ERASE_reserved1_SHIFT                      14

/* T2_FE :: IMPE_ERASE :: VAL_Q [13:00] */
#define BCHP_T2_FE_IMPE_ERASE_VAL_Q_MASK                           0x00003fff
#define BCHP_T2_FE_IMPE_ERASE_VAL_Q_SHIFT                          0
#define BCHP_T2_FE_IMPE_ERASE_VAL_Q_DEFAULT                        0

/***************************************************************************
 *IMPE_INST_THR - Impulse Erasure Instantaneous Threshold
 ***************************************************************************/
/* T2_FE :: IMPE_INST_THR :: reserved0 [31:24] */
#define BCHP_T2_FE_IMPE_INST_THR_reserved0_MASK                    0xff000000
#define BCHP_T2_FE_IMPE_INST_THR_reserved0_SHIFT                   24

/* T2_FE :: IMPE_INST_THR :: INST_THR [23:00] */
#define BCHP_T2_FE_IMPE_INST_THR_INST_THR_MASK                     0x00ffffff
#define BCHP_T2_FE_IMPE_INST_THR_INST_THR_SHIFT                    0
#define BCHP_T2_FE_IMPE_INST_THR_INST_THR_DEFAULT                  263390

/***************************************************************************
 *IMPE_MA_THR - Impulse Erasure Moving Average Threshold
 ***************************************************************************/
/* T2_FE :: IMPE_MA_THR :: reserved0 [31:24] */
#define BCHP_T2_FE_IMPE_MA_THR_reserved0_MASK                      0xff000000
#define BCHP_T2_FE_IMPE_MA_THR_reserved0_SHIFT                     24

/* T2_FE :: IMPE_MA_THR :: MA_THR [23:00] */
#define BCHP_T2_FE_IMPE_MA_THR_MA_THR_MASK                         0x00ffffff
#define BCHP_T2_FE_IMPE_MA_THR_MA_THR_SHIFT                        0
#define BCHP_T2_FE_IMPE_MA_THR_MA_THR_DEFAULT                      632137

/***************************************************************************
 *IMPE_ERASE_CNT - Impulse Erasure Count
 ***************************************************************************/
/* T2_FE :: IMPE_ERASE_CNT :: ERASE_CNT [31:00] */
#define BCHP_T2_FE_IMPE_ERASE_CNT_ERASE_CNT_MASK                   0xffffffff
#define BCHP_T2_FE_IMPE_ERASE_CNT_ERASE_CNT_SHIFT                  0
#define BCHP_T2_FE_IMPE_ERASE_CNT_ERASE_CNT_DEFAULT                0

/***************************************************************************
 *CL - Carrier Loop Control
 ***************************************************************************/
/* T2_FE :: CL :: reserved0 [31:01] */
#define BCHP_T2_FE_CL_reserved0_MASK                               0xfffffffe
#define BCHP_T2_FE_CL_reserved0_SHIFT                              1

/* T2_FE :: CL :: LFO_NEG [00:00] */
#define BCHP_T2_FE_CL_LFO_NEG_MASK                                 0x00000001
#define BCHP_T2_FE_CL_LFO_NEG_SHIFT                                0
#define BCHP_T2_FE_CL_LFO_NEG_DEFAULT                              0

/***************************************************************************
 *CL_FCW - Carrier Loop Frequency Control Word
 ***************************************************************************/
/* T2_FE :: CL_FCW :: FCW [31:00] */
#define BCHP_T2_FE_CL_FCW_FCW_MASK                                 0xffffffff
#define BCHP_T2_FE_CL_FCW_FCW_SHIFT                                0
#define BCHP_T2_FE_CL_FCW_FCW_DEFAULT                              1073741824

/***************************************************************************
 *CL_COEF - Carrier Loop Coefficients
 ***************************************************************************/
/* T2_FE :: CL_COEF :: KI [31:16] */
#define BCHP_T2_FE_CL_COEF_KI_MASK                                 0xffff0000
#define BCHP_T2_FE_CL_COEF_KI_SHIFT                                16
#define BCHP_T2_FE_CL_COEF_KI_DEFAULT                              0

/* T2_FE :: CL_COEF :: KL [15:00] */
#define BCHP_T2_FE_CL_COEF_KL_MASK                                 0x0000ffff
#define BCHP_T2_FE_CL_COEF_KL_SHIFT                                0
#define BCHP_T2_FE_CL_COEF_KL_DEFAULT                              0

/***************************************************************************
 *CL_FEST - Carrier Loop Fractional Estimates
 ***************************************************************************/
/* T2_FE :: CL_FEST :: reserved0 [31:16] */
#define BCHP_T2_FE_CL_FEST_reserved0_MASK                          0xffff0000
#define BCHP_T2_FE_CL_FEST_reserved0_SHIFT                         16

/* T2_FE :: CL_FEST :: FRAC_EST [15:00] */
#define BCHP_T2_FE_CL_FEST_FRAC_EST_MASK                           0x0000ffff
#define BCHP_T2_FE_CL_FEST_FRAC_EST_SHIFT                          0
#define BCHP_T2_FE_CL_FEST_FRAC_EST_DEFAULT                        0

/***************************************************************************
 *CL_IEST - Carrier Loop Integer Estimate
 ***************************************************************************/
/* T2_FE :: CL_IEST :: reserved0 [31:30] */
#define BCHP_T2_FE_CL_IEST_reserved0_MASK                          0xc0000000
#define BCHP_T2_FE_CL_IEST_reserved0_SHIFT                         30

/* T2_FE :: CL_IEST :: INT_EST [29:00] */
#define BCHP_T2_FE_CL_IEST_INT_EST_MASK                            0x3fffffff
#define BCHP_T2_FE_CL_IEST_INT_EST_SHIFT                           0
#define BCHP_T2_FE_CL_IEST_INT_EST_DEFAULT                         0

/***************************************************************************
 *CL_INT - Carrier Loop Integrator
 ***************************************************************************/
/* T2_FE :: CL_INT :: INT [31:00] */
#define BCHP_T2_FE_CL_INT_INT_MASK                                 0xffffffff
#define BCHP_T2_FE_CL_INT_INT_SHIFT                                0
#define BCHP_T2_FE_CL_INT_INT_DEFAULT                              0

/***************************************************************************
 *CL_LFO - Carrier Loop Filter Output
 ***************************************************************************/
/* T2_FE :: CL_LFO :: LFO [31:00] */
#define BCHP_T2_FE_CL_LFO_LFO_MASK                                 0xffffffff
#define BCHP_T2_FE_CL_LFO_LFO_SHIFT                                0
#define BCHP_T2_FE_CL_LFO_LFO_DEFAULT                              0

/***************************************************************************
 *CL_PA - Carrier Loop Phase Accumulator
 ***************************************************************************/
/* T2_FE :: CL_PA :: PA [31:00] */
#define BCHP_T2_FE_CL_PA_PA_MASK                                   0xffffffff
#define BCHP_T2_FE_CL_PA_PA_SHIFT                                  0
#define BCHP_T2_FE_CL_PA_PA_DEFAULT                                0

/***************************************************************************
 *TL_FCW - Timing Loop Frequency Control Word
 ***************************************************************************/
/* T2_FE :: TL_FCW :: FCW [31:00] */
#define BCHP_T2_FE_TL_FCW_FCW_MASK                                 0xffffffff
#define BCHP_T2_FE_TL_FCW_FCW_SHIFT                                0
#define BCHP_T2_FE_TL_FCW_FCW_DEFAULT                              2147483648

/***************************************************************************
 *TL_COEF - Timing Loop Coefficients
 ***************************************************************************/
/* T2_FE :: TL_COEF :: KI [31:16] */
#define BCHP_T2_FE_TL_COEF_KI_MASK                                 0xffff0000
#define BCHP_T2_FE_TL_COEF_KI_SHIFT                                16
#define BCHP_T2_FE_TL_COEF_KI_DEFAULT                              0

/* T2_FE :: TL_COEF :: KL [15:00] */
#define BCHP_T2_FE_TL_COEF_KL_MASK                                 0x0000ffff
#define BCHP_T2_FE_TL_COEF_KL_SHIFT                                0
#define BCHP_T2_FE_TL_COEF_KL_DEFAULT                              0

/***************************************************************************
 *TL_EST - Timing Loop Estimate
 ***************************************************************************/
/* T2_FE :: TL_EST :: reserved0 [31:16] */
#define BCHP_T2_FE_TL_EST_reserved0_MASK                           0xffff0000
#define BCHP_T2_FE_TL_EST_reserved0_SHIFT                          16

/* T2_FE :: TL_EST :: FRAC_EST [15:00] */
#define BCHP_T2_FE_TL_EST_FRAC_EST_MASK                            0x0000ffff
#define BCHP_T2_FE_TL_EST_FRAC_EST_SHIFT                           0
#define BCHP_T2_FE_TL_EST_FRAC_EST_DEFAULT                         0

/***************************************************************************
 *TL_INT - Timing Loop Integrator
 ***************************************************************************/
/* T2_FE :: TL_INT :: INT [31:00] */
#define BCHP_T2_FE_TL_INT_INT_MASK                                 0xffffffff
#define BCHP_T2_FE_TL_INT_INT_SHIFT                                0
#define BCHP_T2_FE_TL_INT_INT_DEFAULT                              0

/***************************************************************************
 *TL_LFO - Timing Loop Filter Output
 ***************************************************************************/
/* T2_FE :: TL_LFO :: LFO [31:00] */
#define BCHP_T2_FE_TL_LFO_LFO_MASK                                 0xffffffff
#define BCHP_T2_FE_TL_LFO_LFO_SHIFT                                0
#define BCHP_T2_FE_TL_LFO_LFO_DEFAULT                              0

/***************************************************************************
 *TL_NCO - Timing Loop NCO
 ***************************************************************************/
/* T2_FE :: TL_NCO :: NCO [31:00] */
#define BCHP_T2_FE_TL_NCO_NCO_MASK                                 0xffffffff
#define BCHP_T2_FE_TL_NCO_NCO_SHIFT                                0
#define BCHP_T2_FE_TL_NCO_NCO_DEFAULT                              0

/***************************************************************************
 *DAGC - Digital AGC2 Loop Control
 ***************************************************************************/
/* T2_FE :: DAGC :: reserved0 [31:28] */
#define BCHP_T2_FE_DAGC_reserved0_MASK                             0xf0000000
#define BCHP_T2_FE_DAGC_reserved0_SHIFT                            28

/* T2_FE :: DAGC :: K [27:24] */
#define BCHP_T2_FE_DAGC_K_MASK                                     0x0f000000
#define BCHP_T2_FE_DAGC_K_SHIFT                                    24
#define BCHP_T2_FE_DAGC_K_DEFAULT                                  5

/* T2_FE :: DAGC :: reserved1 [23:22] */
#define BCHP_T2_FE_DAGC_reserved1_MASK                             0x00c00000
#define BCHP_T2_FE_DAGC_reserved1_SHIFT                            22

/* T2_FE :: DAGC :: BETA [21:20] */
#define BCHP_T2_FE_DAGC_BETA_MASK                                  0x00300000
#define BCHP_T2_FE_DAGC_BETA_SHIFT                                 20
#define BCHP_T2_FE_DAGC_BETA_DEFAULT                               2

/* T2_FE :: DAGC :: reserved2 [19:19] */
#define BCHP_T2_FE_DAGC_reserved2_MASK                             0x00080000
#define BCHP_T2_FE_DAGC_reserved2_SHIFT                            19

/* T2_FE :: DAGC :: THRESH [18:00] */
#define BCHP_T2_FE_DAGC_THRESH_MASK                                0x0007ffff
#define BCHP_T2_FE_DAGC_THRESH_SHIFT                               0
#define BCHP_T2_FE_DAGC_THRESH_DEFAULT                             131072

/***************************************************************************
 *DAGC_INT - Digital AGC2 Loop Filter Output
 ***************************************************************************/
/* T2_FE :: DAGC_INT :: INT [31:00] */
#define BCHP_T2_FE_DAGC_INT_INT_MASK                               0xffffffff
#define BCHP_T2_FE_DAGC_INT_INT_SHIFT                              0
#define BCHP_T2_FE_DAGC_INT_INT_DEFAULT                            33554432

/***************************************************************************
 *DAGC_UPDATE - Digital AGC2 Loop Update Control
 ***************************************************************************/
/* T2_FE :: DAGC_UPDATE :: reserved0 [31:24] */
#define BCHP_T2_FE_DAGC_UPDATE_reserved0_MASK                      0xff000000
#define BCHP_T2_FE_DAGC_UPDATE_reserved0_SHIFT                     24

/* T2_FE :: DAGC_UPDATE :: DURATION [23:08] */
#define BCHP_T2_FE_DAGC_UPDATE_DURATION_MASK                       0x00ffff00
#define BCHP_T2_FE_DAGC_UPDATE_DURATION_SHIFT                      8
#define BCHP_T2_FE_DAGC_UPDATE_DURATION_DEFAULT                    1

/* T2_FE :: DAGC_UPDATE :: reserved1 [07:01] */
#define BCHP_T2_FE_DAGC_UPDATE_reserved1_MASK                      0x000000fe
#define BCHP_T2_FE_DAGC_UPDATE_reserved1_SHIFT                     1

/* T2_FE :: DAGC_UPDATE :: MODE [00:00] */
#define BCHP_T2_FE_DAGC_UPDATE_MODE_MASK                           0x00000001
#define BCHP_T2_FE_DAGC_UPDATE_MODE_SHIFT                          0
#define BCHP_T2_FE_DAGC_UPDATE_MODE_DEFAULT                        0

/***************************************************************************
 *NOTCH_CTL - Notch Control
 ***************************************************************************/
/* T2_FE :: NOTCH_CTL :: reserved0 [31:02] */
#define BCHP_T2_FE_NOTCH_CTL_reserved0_MASK                        0xfffffffc
#define BCHP_T2_FE_NOTCH_CTL_reserved0_SHIFT                       2

/* T2_FE :: NOTCH_CTL :: FCW0_ADJ_NEG [01:01] */
#define BCHP_T2_FE_NOTCH_CTL_FCW0_ADJ_NEG_MASK                     0x00000002
#define BCHP_T2_FE_NOTCH_CTL_FCW0_ADJ_NEG_SHIFT                    1
#define BCHP_T2_FE_NOTCH_CTL_FCW0_ADJ_NEG_DEFAULT                  0

/* T2_FE :: NOTCH_CTL :: FCW0_ADJ_EN [00:00] */
#define BCHP_T2_FE_NOTCH_CTL_FCW0_ADJ_EN_MASK                      0x00000001
#define BCHP_T2_FE_NOTCH_CTL_FCW0_ADJ_EN_SHIFT                     0
#define BCHP_T2_FE_NOTCH_CTL_FCW0_ADJ_EN_DEFAULT                   0

/***************************************************************************
 *NOTCH_WIDTH - Notch Width
 ***************************************************************************/
/* T2_FE :: NOTCH_WIDTH :: reserved0 [31:20] */
#define BCHP_T2_FE_NOTCH_WIDTH_reserved0_MASK                      0xfff00000
#define BCHP_T2_FE_NOTCH_WIDTH_reserved0_SHIFT                     20

/* T2_FE :: NOTCH_WIDTH :: WIDTH4 [19:16] */
#define BCHP_T2_FE_NOTCH_WIDTH_WIDTH4_MASK                         0x000f0000
#define BCHP_T2_FE_NOTCH_WIDTH_WIDTH4_SHIFT                        16
#define BCHP_T2_FE_NOTCH_WIDTH_WIDTH4_DEFAULT                      0

/* T2_FE :: NOTCH_WIDTH :: WIDTH3 [15:12] */
#define BCHP_T2_FE_NOTCH_WIDTH_WIDTH3_MASK                         0x0000f000
#define BCHP_T2_FE_NOTCH_WIDTH_WIDTH3_SHIFT                        12
#define BCHP_T2_FE_NOTCH_WIDTH_WIDTH3_DEFAULT                      0

/* T2_FE :: NOTCH_WIDTH :: WIDTH2 [11:08] */
#define BCHP_T2_FE_NOTCH_WIDTH_WIDTH2_MASK                         0x00000f00
#define BCHP_T2_FE_NOTCH_WIDTH_WIDTH2_SHIFT                        8
#define BCHP_T2_FE_NOTCH_WIDTH_WIDTH2_DEFAULT                      0

/* T2_FE :: NOTCH_WIDTH :: WIDTH1 [07:04] */
#define BCHP_T2_FE_NOTCH_WIDTH_WIDTH1_MASK                         0x000000f0
#define BCHP_T2_FE_NOTCH_WIDTH_WIDTH1_SHIFT                        4
#define BCHP_T2_FE_NOTCH_WIDTH_WIDTH1_DEFAULT                      0

/* T2_FE :: NOTCH_WIDTH :: WIDTH0 [03:00] */
#define BCHP_T2_FE_NOTCH_WIDTH_WIDTH0_MASK                         0x0000000f
#define BCHP_T2_FE_NOTCH_WIDTH_WIDTH0_SHIFT                        0
#define BCHP_T2_FE_NOTCH_WIDTH_WIDTH0_DEFAULT                      0

/***************************************************************************
 *NOTCH_DEPTH - Notch Depth
 ***************************************************************************/
/* T2_FE :: NOTCH_DEPTH :: reserved0 [31:20] */
#define BCHP_T2_FE_NOTCH_DEPTH_reserved0_MASK                      0xfff00000
#define BCHP_T2_FE_NOTCH_DEPTH_reserved0_SHIFT                     20

/* T2_FE :: NOTCH_DEPTH :: DEPTH4 [19:16] */
#define BCHP_T2_FE_NOTCH_DEPTH_DEPTH4_MASK                         0x000f0000
#define BCHP_T2_FE_NOTCH_DEPTH_DEPTH4_SHIFT                        16
#define BCHP_T2_FE_NOTCH_DEPTH_DEPTH4_DEFAULT                      0

/* T2_FE :: NOTCH_DEPTH :: DEPTH3 [15:12] */
#define BCHP_T2_FE_NOTCH_DEPTH_DEPTH3_MASK                         0x0000f000
#define BCHP_T2_FE_NOTCH_DEPTH_DEPTH3_SHIFT                        12
#define BCHP_T2_FE_NOTCH_DEPTH_DEPTH3_DEFAULT                      0

/* T2_FE :: NOTCH_DEPTH :: DEPTH2 [11:08] */
#define BCHP_T2_FE_NOTCH_DEPTH_DEPTH2_MASK                         0x00000f00
#define BCHP_T2_FE_NOTCH_DEPTH_DEPTH2_SHIFT                        8
#define BCHP_T2_FE_NOTCH_DEPTH_DEPTH2_DEFAULT                      0

/* T2_FE :: NOTCH_DEPTH :: DEPTH1 [07:04] */
#define BCHP_T2_FE_NOTCH_DEPTH_DEPTH1_MASK                         0x000000f0
#define BCHP_T2_FE_NOTCH_DEPTH_DEPTH1_SHIFT                        4
#define BCHP_T2_FE_NOTCH_DEPTH_DEPTH1_DEFAULT                      0

/* T2_FE :: NOTCH_DEPTH :: DEPTH0 [03:00] */
#define BCHP_T2_FE_NOTCH_DEPTH_DEPTH0_MASK                         0x0000000f
#define BCHP_T2_FE_NOTCH_DEPTH_DEPTH0_SHIFT                        0
#define BCHP_T2_FE_NOTCH_DEPTH_DEPTH0_DEFAULT                      0

/***************************************************************************
 *NOTCH0_FCW - Notch0 Frequency Control Word
 ***************************************************************************/
/* T2_FE :: NOTCH0_FCW :: FCW [31:12] */
#define BCHP_T2_FE_NOTCH0_FCW_FCW_MASK                             0xfffff000
#define BCHP_T2_FE_NOTCH0_FCW_FCW_SHIFT                            12
#define BCHP_T2_FE_NOTCH0_FCW_FCW_DEFAULT                          0

/* T2_FE :: NOTCH0_FCW :: reserved0 [11:00] */
#define BCHP_T2_FE_NOTCH0_FCW_reserved0_MASK                       0x00000fff
#define BCHP_T2_FE_NOTCH0_FCW_reserved0_SHIFT                      0

/***************************************************************************
 *NOTCH1_FCW - Notch1 Frequency Control Word
 ***************************************************************************/
/* T2_FE :: NOTCH1_FCW :: FCW [31:12] */
#define BCHP_T2_FE_NOTCH1_FCW_FCW_MASK                             0xfffff000
#define BCHP_T2_FE_NOTCH1_FCW_FCW_SHIFT                            12
#define BCHP_T2_FE_NOTCH1_FCW_FCW_DEFAULT                          0

/* T2_FE :: NOTCH1_FCW :: reserved0 [11:00] */
#define BCHP_T2_FE_NOTCH1_FCW_reserved0_MASK                       0x00000fff
#define BCHP_T2_FE_NOTCH1_FCW_reserved0_SHIFT                      0

/***************************************************************************
 *NOTCH2_FCW - Notch2 Frequency Control Word
 ***************************************************************************/
/* T2_FE :: NOTCH2_FCW :: FCW [31:12] */
#define BCHP_T2_FE_NOTCH2_FCW_FCW_MASK                             0xfffff000
#define BCHP_T2_FE_NOTCH2_FCW_FCW_SHIFT                            12
#define BCHP_T2_FE_NOTCH2_FCW_FCW_DEFAULT                          0

/* T2_FE :: NOTCH2_FCW :: reserved0 [11:00] */
#define BCHP_T2_FE_NOTCH2_FCW_reserved0_MASK                       0x00000fff
#define BCHP_T2_FE_NOTCH2_FCW_reserved0_SHIFT                      0

/***************************************************************************
 *NOTCH3_FCW - Notch3 Frequency Control Word
 ***************************************************************************/
/* T2_FE :: NOTCH3_FCW :: FCW [31:12] */
#define BCHP_T2_FE_NOTCH3_FCW_FCW_MASK                             0xfffff000
#define BCHP_T2_FE_NOTCH3_FCW_FCW_SHIFT                            12
#define BCHP_T2_FE_NOTCH3_FCW_FCW_DEFAULT                          0

/* T2_FE :: NOTCH3_FCW :: reserved0 [11:00] */
#define BCHP_T2_FE_NOTCH3_FCW_reserved0_MASK                       0x00000fff
#define BCHP_T2_FE_NOTCH3_FCW_reserved0_SHIFT                      0

/***************************************************************************
 *NOTCH4_FCW - Notch4 Frequency Control Word
 ***************************************************************************/
/* T2_FE :: NOTCH4_FCW :: FCW [31:12] */
#define BCHP_T2_FE_NOTCH4_FCW_FCW_MASK                             0xfffff000
#define BCHP_T2_FE_NOTCH4_FCW_FCW_SHIFT                            12
#define BCHP_T2_FE_NOTCH4_FCW_FCW_DEFAULT                          0

/* T2_FE :: NOTCH4_FCW :: reserved0 [11:00] */
#define BCHP_T2_FE_NOTCH4_FCW_reserved0_MASK                       0x00000fff
#define BCHP_T2_FE_NOTCH4_FCW_reserved0_SHIFT                      0

/***************************************************************************
 *NOTCH5_FCW - Notch5 Frequency Control Word
 ***************************************************************************/
/* T2_FE :: NOTCH5_FCW :: FCW [31:12] */
#define BCHP_T2_FE_NOTCH5_FCW_FCW_MASK                             0xfffff000
#define BCHP_T2_FE_NOTCH5_FCW_FCW_SHIFT                            12
#define BCHP_T2_FE_NOTCH5_FCW_FCW_DEFAULT                          0

/* T2_FE :: NOTCH5_FCW :: reserved0 [11:00] */
#define BCHP_T2_FE_NOTCH5_FCW_reserved0_MASK                       0x00000fff
#define BCHP_T2_FE_NOTCH5_FCW_reserved0_SHIFT                      0

/***************************************************************************
 *NOTCH0_INT - Notch0 Integrator
 ***************************************************************************/
/* T2_FE :: NOTCH0_INT :: INT_I [31:16] */
#define BCHP_T2_FE_NOTCH0_INT_INT_I_MASK                           0xffff0000
#define BCHP_T2_FE_NOTCH0_INT_INT_I_SHIFT                          16
#define BCHP_T2_FE_NOTCH0_INT_INT_I_DEFAULT                        0

/* T2_FE :: NOTCH0_INT :: INT_Q [15:00] */
#define BCHP_T2_FE_NOTCH0_INT_INT_Q_MASK                           0x0000ffff
#define BCHP_T2_FE_NOTCH0_INT_INT_Q_SHIFT                          0
#define BCHP_T2_FE_NOTCH0_INT_INT_Q_DEFAULT                        0

/***************************************************************************
 *NOTCH1_INT - Notch1 Integrator
 ***************************************************************************/
/* T2_FE :: NOTCH1_INT :: INT_I [31:16] */
#define BCHP_T2_FE_NOTCH1_INT_INT_I_MASK                           0xffff0000
#define BCHP_T2_FE_NOTCH1_INT_INT_I_SHIFT                          16
#define BCHP_T2_FE_NOTCH1_INT_INT_I_DEFAULT                        0

/* T2_FE :: NOTCH1_INT :: INT_Q [15:00] */
#define BCHP_T2_FE_NOTCH1_INT_INT_Q_MASK                           0x0000ffff
#define BCHP_T2_FE_NOTCH1_INT_INT_Q_SHIFT                          0
#define BCHP_T2_FE_NOTCH1_INT_INT_Q_DEFAULT                        0

/***************************************************************************
 *NOTCH2_INT - Notch2 Integrator
 ***************************************************************************/
/* T2_FE :: NOTCH2_INT :: INT_I [31:16] */
#define BCHP_T2_FE_NOTCH2_INT_INT_I_MASK                           0xffff0000
#define BCHP_T2_FE_NOTCH2_INT_INT_I_SHIFT                          16
#define BCHP_T2_FE_NOTCH2_INT_INT_I_DEFAULT                        0

/* T2_FE :: NOTCH2_INT :: INT_Q [15:00] */
#define BCHP_T2_FE_NOTCH2_INT_INT_Q_MASK                           0x0000ffff
#define BCHP_T2_FE_NOTCH2_INT_INT_Q_SHIFT                          0
#define BCHP_T2_FE_NOTCH2_INT_INT_Q_DEFAULT                        0

/***************************************************************************
 *NOTCH3_INT - Notch3 Integrator
 ***************************************************************************/
/* T2_FE :: NOTCH3_INT :: INT_I [31:16] */
#define BCHP_T2_FE_NOTCH3_INT_INT_I_MASK                           0xffff0000
#define BCHP_T2_FE_NOTCH3_INT_INT_I_SHIFT                          16
#define BCHP_T2_FE_NOTCH3_INT_INT_I_DEFAULT                        0

/* T2_FE :: NOTCH3_INT :: INT_Q [15:00] */
#define BCHP_T2_FE_NOTCH3_INT_INT_Q_MASK                           0x0000ffff
#define BCHP_T2_FE_NOTCH3_INT_INT_Q_SHIFT                          0
#define BCHP_T2_FE_NOTCH3_INT_INT_Q_DEFAULT                        0

/***************************************************************************
 *NOTCH4_INT - Notch4 Integrator
 ***************************************************************************/
/* T2_FE :: NOTCH4_INT :: INT_I [31:16] */
#define BCHP_T2_FE_NOTCH4_INT_INT_I_MASK                           0xffff0000
#define BCHP_T2_FE_NOTCH4_INT_INT_I_SHIFT                          16
#define BCHP_T2_FE_NOTCH4_INT_INT_I_DEFAULT                        0

/* T2_FE :: NOTCH4_INT :: INT_Q [15:00] */
#define BCHP_T2_FE_NOTCH4_INT_INT_Q_MASK                           0x0000ffff
#define BCHP_T2_FE_NOTCH4_INT_INT_Q_SHIFT                          0
#define BCHP_T2_FE_NOTCH4_INT_INT_Q_DEFAULT                        0

/***************************************************************************
 *ECO_SPARE0 - ECO Spare 0 Register
 ***************************************************************************/
/* T2_FE :: ECO_SPARE0 :: SPARE [31:00] */
#define BCHP_T2_FE_ECO_SPARE0_SPARE_MASK                           0xffffffff
#define BCHP_T2_FE_ECO_SPARE0_SPARE_SHIFT                          0
#define BCHP_T2_FE_ECO_SPARE0_SPARE_DEFAULT                        0

/***************************************************************************
 *ECO_SPARE1 - ECO Spare 1 Register
 ***************************************************************************/
/* T2_FE :: ECO_SPARE1 :: SPARE [31:00] */
#define BCHP_T2_FE_ECO_SPARE1_SPARE_MASK                           0xffffffff
#define BCHP_T2_FE_ECO_SPARE1_SPARE_SHIFT                          0
#define BCHP_T2_FE_ECO_SPARE1_SPARE_DEFAULT                        0

#endif /* #ifndef BCHP_T2_FE_H__ */

/* End of File */

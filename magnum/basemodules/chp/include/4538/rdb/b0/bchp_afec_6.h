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
 * Date:           Generated on         Thu Mar 14 11:46:10 2013
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

#ifndef BCHP_AFEC_6_H__
#define BCHP_AFEC_6_H__

/***************************************************************************
 *AFEC_6 - 6 AFEC Register Set
 ***************************************************************************/
#define BCHP_AFEC_6_RST                          0x000e6000 /* AFEC core reset register */
#define BCHP_AFEC_6_CNTR_CTRL                    0x000e6004 /* AFEC counter-control register */
#define BCHP_AFEC_6_TEST_CONFIG                  0x000e6008 /* AFEC Test Configuration Register */
#define BCHP_AFEC_6_BIST_TEST_CONFIG             0x000e600c /* AFEC Bist Test Configuration Register */
#define BCHP_AFEC_6_ACM_MAX_ITER_OVERIDE         0x000e6104 /* ACM Controller MODCOD MAX_ITER_OVERIDE selection register */
#define BCHP_AFEC_6_ACM_MODCOD_1                 0x000e6030 /* ACM Controller MODCOD Configuration Register 1 */
#define BCHP_AFEC_6_ACM_MODCOD_2                 0x000e6034 /* ACM Controller MODCOD Configuration Register 2 */
#define BCHP_AFEC_6_ACM_MODCOD_3                 0x000e6038 /* ACM Controller MODCOD Configuration Register 3 */
#define BCHP_AFEC_6_ACM_MODCOD_4                 0x000e603c /* ACM Controller MODCOD Configuration Register 4 */
#define BCHP_AFEC_6_ACM_MODCOD_5                 0x000e6040 /* ACM Controller MODCOD Configuration Register 5 */
#define BCHP_AFEC_6_ACM_MODCOD_6                 0x000e6044 /* ACM Controller MODCOD Configuration Register 6 */
#define BCHP_AFEC_6_ACM_MODCOD_7                 0x000e6048 /* ACM Controller MODCOD Configuration Register 7 */
#define BCHP_AFEC_6_ACM_MODCOD_8                 0x000e604c /* ACM Controller MODCOD Configuration Register 8 */
#define BCHP_AFEC_6_ACM_MODCOD_9                 0x000e6050 /* ACM Controller MODCOD Configuration Register 9 */
#define BCHP_AFEC_6_ACM_MODCOD_10                0x000e6054 /* ACM Controller MODCOD Configuration Register 10 */
#define BCHP_AFEC_6_ACM_MODCOD_11                0x000e6058 /* ACM Controller MODCOD Configuration Register 11 */
#define BCHP_AFEC_6_ACM_MODCOD_12                0x000e605c /* ACM Controller MODCOD Configuration Register 12 */
#define BCHP_AFEC_6_ACM_MODCOD_13                0x000e6060 /* ACM Controller MODCOD Configuration Register 13 */
#define BCHP_AFEC_6_ACM_MODCOD_14                0x000e6064 /* ACM Controller MODCOD Configuration Register 14 */
#define BCHP_AFEC_6_ACM_MODCOD_15                0x000e6068 /* ACM Controller MODCOD Configuration Register 15 */
#define BCHP_AFEC_6_ACM_MODCOD_16                0x000e606c /* ACM Controller MODCOD Configuration Register 16 */
#define BCHP_AFEC_6_ACM_MODCOD_17                0x000e6070 /* ACM Controller MODCOD Configuration Register 17 */
#define BCHP_AFEC_6_ACM_MODCOD_18                0x000e6074 /* ACM Controller MODCOD Configuration Register 18 */
#define BCHP_AFEC_6_ACM_MODCOD_19                0x000e6078 /* ACM Controller MODCOD Configuration Register 19 */
#define BCHP_AFEC_6_ACM_MODCOD_20                0x000e607c /* ACM Controller MODCOD Configuration Register 20 */
#define BCHP_AFEC_6_ACM_MODCOD_21                0x000e6080 /* ACM Controller MODCOD Configuration Register 21 */
#define BCHP_AFEC_6_ACM_MODCOD_22                0x000e6084 /* ACM Controller MODCOD Configuration Register 22 */
#define BCHP_AFEC_6_ACM_MODCOD_23                0x000e6088 /* ACM Controller MODCOD Configuration Register 23 */
#define BCHP_AFEC_6_ACM_MODCOD_24                0x000e608c /* ACM Controller MODCOD Configuration Register 24 */
#define BCHP_AFEC_6_ACM_MODCOD_25                0x000e6090 /* ACM Controller MODCOD Configuration Register 25 */
#define BCHP_AFEC_6_ACM_MODCOD_26                0x000e6094 /* ACM Controller MODCOD Configuration Register 26 */
#define BCHP_AFEC_6_ACM_MODCOD_27                0x000e6098 /* ACM Controller MODCOD Configuration Register 27 */
#define BCHP_AFEC_6_ACM_MODCOD_28                0x000e609c /* ACM Controller MODCOD Configuration Register 28 */
#define BCHP_AFEC_6_ACM_MODCOD_29_EXT            0x000e60a0 /* ACM Controller MODCOD Configuration Register 29 Extension */
#define BCHP_AFEC_6_ACM_MODCOD_29_LDPC0_EXT      0x000e60a4 /* ACM Controller LDPC Configuration Register */
#define BCHP_AFEC_6_ACM_MODCOD_30_EXT            0x000e60a8 /* ACM Controller MODCOD Configuration Register 30 Extension */
#define BCHP_AFEC_6_ACM_MODCOD_30_LDPC0_EXT      0x000e60ac /* ACM Controller LDPC Configuration Register */
#define BCHP_AFEC_6_ACM_MODCOD_31_EXT            0x000e60b0 /* ACM Controller MODCOD Configuration Register 31 Extension */
#define BCHP_AFEC_6_ACM_MODCOD_31_LDPC0_EXT      0x000e60b4 /* ACM Controller LDPC Configuration Register */
#define BCHP_AFEC_6_ACM_SYM_CNT_0                0x000e60b8 /* ACM Controller symbol counter */
#define BCHP_AFEC_6_ACM_SYM_CNT_1                0x000e60bc /* ACM Controller symbol counter */
#define BCHP_AFEC_6_ACM_SYM_CNT_2                0x000e60c0 /* ACM Controller symbol counter */
#define BCHP_AFEC_6_ACM_CYCLE_CNT_0              0x000e60c4 /* ACM Controller LDPC clk counter for QPSK */
#define BCHP_AFEC_6_ACM_CYCLE_CNT_1              0x000e60c8 /* ACM Controller LDPC clk counter for 8PSK */
#define BCHP_AFEC_6_ACM_CYCLE_CNT_2              0x000e60cc /* ACM Controller LDPC clk counter for 16APSK */
#define BCHP_AFEC_6_ACM_CYCLE_CNT_3              0x000e60d0 /* ACM Controller LDPC clk counter for 32APSK */
#define BCHP_AFEC_6_ACM_CYCLE_CNT_4              0x000e60d4 /* ACM Controller LDPC clk counter for BPSK */
#define BCHP_AFEC_6_ACM_MISC_0                   0x000e60d8 /* ACM Controller MISC_0 register */
#define BCHP_AFEC_6_ACM_MISC_1                   0x000e60dc /* ACM Controller MISC_1 register */
#define BCHP_AFEC_6_ACM_MODCOD_OVERIDE           0x000e60e0 /* ACM Controller MODCOD Overide Configuration Register */
#define BCHP_AFEC_6_ACM_MODCOD_STATS_CONFIG      0x000e60ec /* ACM MODCOD statistics configuration block */
#define BCHP_AFEC_6_ACM_DONT_DEC_CNT             0x000e60f0 /* ACM Dont decode counter */
#define BCHP_AFEC_6_ACM_LDPC_ITER_CNT            0x000e60f4 /* ACM Iteration counter */
#define BCHP_AFEC_6_ACM_LDPC_FAIL_CNT            0x000e60f8 /* ACM LDPC FAIL COUNTER */
#define BCHP_AFEC_6_ACM_LDPC_FRM_CNT             0x000e60fc /* ACM LDPC FRAME COUNTER */
#define BCHP_AFEC_6_LDPC_CONFIG_0                0x000e6300 /* LDPC Configuration Register 0 */
#define BCHP_AFEC_6_LDPC_STATUS                  0x000e6328 /* LDPC Status Register */
#define BCHP_AFEC_6_LDPC_MET_CRC                 0x000e632c /* Metric Generator Signature */
#define BCHP_AFEC_6_LDPC_EDGE_CRC                0x000e6330 /* Edge Output Signature */
#define BCHP_AFEC_6_LDPC_PSL_CTL                 0x000e6334 /* Power Saving Loop Control register */
#define BCHP_AFEC_6_LDPC_PSL_INT_THRES           0x000e6338 /* PSL Integrator Threshold */
#define BCHP_AFEC_6_LDPC_PSL_INT                 0x000e633c /* PSL Integrator Value */
#define BCHP_AFEC_6_LDPC_PSL_AVE                 0x000e6340 /* PSL Integrator Average Value */
#define BCHP_AFEC_6_LDPC_PSL_XCS                 0x000e6344 /* PSL Excess Value */
#define BCHP_AFEC_6_LDPC_PSL_FILTER              0x000e6348 /* PSL Filter for ACM */
#define BCHP_AFEC_6_LDPC_MEM_POWER               0x000e634c /* Dynamic memory shut down */
#define BCHP_AFEC_6_BCH_TPCTL                    0x000e63bc /* BCH Block Testport Control Register */
#define BCHP_AFEC_6_BCH_TPSIG                    0x000e63c0 /* BCH Block Signature Analyzer */
#define BCHP_AFEC_6_BCH_CTRL                     0x000e63c4 /* BCH Decoder Control Register */
#define BCHP_AFEC_6_BCH_DECNBLK                  0x000e63c8 /* BCH Number of Block Counter */
#define BCHP_AFEC_6_BCH_DECCBLK                  0x000e63cc /* BCH Number of Corrected Block Counter */
#define BCHP_AFEC_6_BCH_DECBBLK                  0x000e63d0 /* BCH Number of Bad Block Counter */
#define BCHP_AFEC_6_BCH_DECCBIT                  0x000e63d4 /* BCH Number of Corrected Bit Counter */
#define BCHP_AFEC_6_BCH_DECMCOR                  0x000e63d8 /* BCH Number of Miscorrected Block Counter */
#define BCHP_AFEC_6_BCH_BBHDR0                   0x000e63dc /* BBHEADER Register 0 */
#define BCHP_AFEC_6_BCH_BBHDR1                   0x000e63e0 /* BBHEADER Register 1 */
#define BCHP_AFEC_6_BCH_BBHDR2                   0x000e63e4 /* BBHEADER Register 2 */
#define BCHP_AFEC_6_BCH_BBHDR3                   0x000e63e8 /* BBHEADER Register 3 */
#define BCHP_AFEC_6_BCH_BBHDR4                   0x000e63ec /* BBHEADER Register 4 */
#define BCHP_AFEC_6_BCH_BBHDR5                   0x000e63f0 /* BBHEADER Register 5 */
#define BCHP_AFEC_6_BCH_MPLCK                    0x000e63f4 /* MPEG Lock Detector Configuration Register */
#define BCHP_AFEC_6_BCH_MPCFG                    0x000e63f8 /* MPEG Packetizer Configuration Register */
#define BCHP_AFEC_6_BCH_SMCFG                    0x000e63fc /* Smoother FIFO Configuration Register */

#endif /* #ifndef BCHP_AFEC_6_H__ */

/* End of File */

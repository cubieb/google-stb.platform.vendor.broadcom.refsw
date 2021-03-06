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
 * Date:           Generated on         Fri Apr 19 14:05:35 2013
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

#ifndef BCHP_AFEC1_1_H__
#define BCHP_AFEC1_1_H__

/***************************************************************************
 *AFEC1_1 - 1 AFEC Register Set for Channel 1
 ***************************************************************************/
#define BCHP_AFEC1_1_RST                         0x0125a000 /* AFEC core channel-based reset register */
#define BCHP_AFEC1_1_CNTR_CTRL                   0x0125a004 /* AFEC counter-control register */
#define BCHP_AFEC1_1_MODCOD_PARAM_0              0x0125a008 /* AFEC MODCOD parameter register */
#define BCHP_AFEC1_1_MODCOD_PARAM_1              0x0125a00c /* AFEC MODCOD parameter register */
#define BCHP_AFEC1_1_MODCOD_STATS_CONFIG         0x0125a010 /* MODCOD statistics configuration block */
#define BCHP_AFEC1_1_LDPC_ITER_CNT               0x0125a014 /* LDPC Iteration counter */
#define BCHP_AFEC1_1_LDPC_FAIL_CNT               0x0125a018 /* LDPC FAIL COUNTER */
#define BCHP_AFEC1_1_LDPC_FRM_CNT                0x0125a01c /* LDPC FRAME COUNTER */
#define BCHP_AFEC1_1_LDPC_CONFIG                 0x0125a020 /* LDPC Configuration Register */
#define BCHP_AFEC1_1_LDPC_STATUS                 0x0125a024 /* LDPC Status Register */
#define BCHP_AFEC1_1_LDPC_MET_CRC                0x0125a028 /* Metric Generator Signature */
#define BCHP_AFEC1_1_LDPC_EDGE_CRC               0x0125a02c /* Edge Output Signature */
#define BCHP_AFEC1_1_LDPC_PSL_CTL                0x0125a030 /* Power Saving Loop Control register */
#define BCHP_AFEC1_1_LDPC_PSL_INT_THRES          0x0125a034 /* PSL Integrator Threshold */
#define BCHP_AFEC1_1_LDPC_PSL_INT                0x0125a038 /* PSL Integrator Value */
#define BCHP_AFEC1_1_LDPC_PSL_AVE                0x0125a03c /* PSL Integrator Average Value */
#define BCHP_AFEC1_1_LDPC_PSL_XCS                0x0125a040 /* PSL Excess Value */
#define BCHP_AFEC1_1_LDPC_PSL_FILTER             0x0125a044 /* PSL Filter for ACM */
#define BCHP_AFEC1_1_BCH_TPSIG                   0x0125a050 /* BCH Block Signature Analyzer */
#define BCHP_AFEC1_1_BCH_SMTH_FIFO_MIN_LEVEL     0x0125a054 /* BCH Smoother Fifo Min Level */
#define BCHP_AFEC1_1_BCH_SMTH_FIFO_MAX_LEVEL     0x0125a058 /* BCH Smoother Fifo Max Level */
#define BCHP_AFEC1_1_BCH_CTRL                    0x0125a064 /* BCH Decoder Control Register */
#define BCHP_AFEC1_1_BCH_DECNBLK                 0x0125a068 /* BCH Number of Block Counter */
#define BCHP_AFEC1_1_BCH_DECCBLK                 0x0125a06c /* BCH Number of Corrected Block Counter */
#define BCHP_AFEC1_1_BCH_DECBBLK                 0x0125a070 /* BCH Number of Bad Block Counter */
#define BCHP_AFEC1_1_BCH_DECCBIT                 0x0125a074 /* BCH Number of Corrected Bit Counter */
#define BCHP_AFEC1_1_BCH_DECMCOR                 0x0125a078 /* BCH Number of Miscorrected Block Counter */
#define BCHP_AFEC1_1_BCH_BBHDR0                  0x0125a07c /* BBHEADER Register 0 */
#define BCHP_AFEC1_1_BCH_BBHDR1                  0x0125a080 /* BBHEADER Register 1 */
#define BCHP_AFEC1_1_BCH_BBHDR2                  0x0125a084 /* BBHEADER Register 2 */
#define BCHP_AFEC1_1_BCH_BBHDR3                  0x0125a088 /* BBHEADER Register 3 */
#define BCHP_AFEC1_1_BCH_BBHDR4                  0x0125a08c /* BBHEADER Register 4 */
#define BCHP_AFEC1_1_BCH_BBHDR5                  0x0125a0c0 /* BBHEADER Register 5 */
#define BCHP_AFEC1_1_BCH_MPLCK                   0x0125a0c4 /* MPEG Lock Detector Configuration Register */
#define BCHP_AFEC1_1_BCH_MPCFG                   0x0125a0c8 /* MPEG Packetizer Configuration Register */
#define BCHP_AFEC1_1_BCH_SMCFG                   0x0125a0cc /* Smoother FIFO Configuration Register */
#define BCHP_AFEC1_1_CH_FRMCYCLES                0x0125aa00 /* Channel frame period  Register */
#define BCHP_AFEC1_1_BIST_PARAM_0                0x0125aa04 /* Channel-based BIST Configuration Register 0 */
#define BCHP_AFEC1_1_BIST_PARAM_1                0x0125aa08 /* Channel-based BIST Configuration Register 1 */
#define BCHP_AFEC1_1_FAKEFRM_PARAM               0x0125aa0c /* Parameters related to the fake frame generation during early termination */

#endif /* #ifndef BCHP_AFEC1_1_H__ */

/* End of File */

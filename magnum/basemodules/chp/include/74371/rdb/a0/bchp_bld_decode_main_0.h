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
 * Date:           Generated on               Mon Nov 17 11:53:47 2014
 *                 Full Compile MD5 Checksum  7c712d144f2919fdac508431993b36d7
 *                     (minus title and desc)
 *                 MD5 Checksum               bc950b877a17d97d6325a810f8bd832e
 *
 * Compiled with:  RDB Utility                combo_header.pl
 *                 RDB.pm                     15193
 *                 unknown                    unknown
 *                 Perl Interpreter           5.008008
 *                 Operating System           linux
 *
 *
 ***************************************************************************/

#ifndef BCHP_BLD_DECODE_MAIN_0_H__
#define BCHP_BLD_DECODE_MAIN_0_H__

/***************************************************************************
 *BLD_DECODE_MAIN_0
 ***************************************************************************/
#define BCHP_BLD_DECODE_MAIN_0_REG_MAINCTL       0x00128100 /* [RW] Decoder Control */
#define BCHP_BLD_DECODE_MAIN_0_REG_FRAMESIZE     0x00128104 /* [RW] Size of the picture being decoded */
#define BCHP_BLD_DECODE_MAIN_0_REG_DEC_VERSION   0x00128108 /* [RO] Version of the decoder core */
#define BCHP_BLD_DECODE_MAIN_0_REG_STATUS        0x00128110 /* [RO] Provides back-end decoder processing status */
#define BCHP_BLD_DECODE_MAIN_0_REG_PMONCTL       0x00128120 /* [RW] Performance Monitoring */
#define BCHP_BLD_DECODE_MAIN_0_REG_PMONCNT0      0x00128124 /* [RO] REG_PMONCNT0 */
#define BCHP_BLD_DECODE_MAIN_0_REG_PMONCNT1      0x00128128 /* [RO] REG_PMONCNT1 */
#define BCHP_BLD_DECODE_MAIN_0_REG_PMON_MBCTL    0x0012812c /* [RW] REG_PMON_MBCTL */
#define BCHP_BLD_DECODE_MAIN_0_DBLK_BUFF_CONTROL 0x00128130 /* [RW] DBLK_BUFF_CONTROL */
#define BCHP_BLD_DECODE_MAIN_0_CRC_CONTROL       0x00128134 /* [RW] DBLK CRC CONTROL register */
#define BCHP_BLD_DECODE_MAIN_0_CRC_SEED          0x00128138 /* [RW] DBLK CRC SEED register */
#define BCHP_BLD_DECODE_MAIN_0_CRC_CHKSUM_Y      0x0012813c /* [RO] DBLK Luma CRC/Checksum result register */
#define BCHP_BLD_DECODE_MAIN_0_CRC_CHKSUM_CB     0x00128140 /* [RO] DBLK Chroma (Cb) CRC/Checksum result register */
#define BCHP_BLD_DECODE_MAIN_0_CRC_CHKSUM_CR     0x00128144 /* [RO] DBLK Chroma (Cr) CRC/Checksum result register */
#define BCHP_BLD_DECODE_MAIN_0_REG_VP6_MCOM_CONTROL 0x00128150 /* [RW] VP6 Mocomp Control */
#define BCHP_BLD_DECODE_MAIN_0_REG_VP6_MCOM_AUTO 0x00128154 /* [RW] VP6 Mocomp Auto Filter Selection */
#define BCHP_BLD_DECODE_MAIN_0_REG_VP6_MCOM_ALPHA 0x00128158 /* [RW] VP6 Mocomp Alpha Filter Selection */
#define BCHP_BLD_DECODE_MAIN_0_REG_VP6_MCOM_FLIMIT 0x0012815c /* [RW] VP6 Mocomp Flimit Control */
#define BCHP_BLD_DECODE_MAIN_0_REG_BACKEND_DEBUG 0x00128160 /* [RW] Backend debug Select */
#define BCHP_BLD_DECODE_MAIN_0_REG_VC1_MC_DEBUG  0x00128164 /* [RO] VC1 Mocomp Debug */
#define BCHP_BLD_DECODE_MAIN_0_REG_QPEL_FIFO_DEBUG 0x00128168 /* [RO] Qpel FIFO Debug */
#define BCHP_BLD_DECODE_MAIN_0_REG_MAIN_END      0x001281fc /* [RW] REG_MAIN_END */

#endif /* #ifndef BCHP_BLD_DECODE_MAIN_0_H__ */

/* End of File */

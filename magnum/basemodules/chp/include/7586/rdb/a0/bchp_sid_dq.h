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
 * Date:           Generated on               Wed Feb 11 10:13:57 2015
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

#ifndef BCHP_SID_DQ_H__
#define BCHP_SID_DQ_H__

/***************************************************************************
 *SID_DQ
 ***************************************************************************/
#define BCHP_SID_DQ_RAM_START                    0x00bc0400 /* [RW] Start of DQ RAM */
#define BCHP_SID_DQ_RAM_END                      0x00bc04bc /* [RW] End of DQ RAM */

/***************************************************************************
 *RAM_START - Start of DQ RAM
 ***************************************************************************/
/* SID_DQ :: RAM_START :: DequantIndex0 [31:24] */
#define BCHP_SID_DQ_RAM_START_DequantIndex0_MASK                   0xff000000
#define BCHP_SID_DQ_RAM_START_DequantIndex0_SHIFT                  24

/* SID_DQ :: RAM_START :: DequantIndex1 [23:16] */
#define BCHP_SID_DQ_RAM_START_DequantIndex1_MASK                   0x00ff0000
#define BCHP_SID_DQ_RAM_START_DequantIndex1_SHIFT                  16

/* SID_DQ :: RAM_START :: DequantIndex2 [15:08] */
#define BCHP_SID_DQ_RAM_START_DequantIndex2_MASK                   0x0000ff00
#define BCHP_SID_DQ_RAM_START_DequantIndex2_SHIFT                  8

/* SID_DQ :: RAM_START :: DequantIndex3 [07:00] */
#define BCHP_SID_DQ_RAM_START_DequantIndex3_MASK                   0x000000ff
#define BCHP_SID_DQ_RAM_START_DequantIndex3_SHIFT                  0

/***************************************************************************
 *RAM_END - End of DQ RAM
 ***************************************************************************/
/* SID_DQ :: RAM_END :: DequantIndex0 [31:24] */
#define BCHP_SID_DQ_RAM_END_DequantIndex0_MASK                     0xff000000
#define BCHP_SID_DQ_RAM_END_DequantIndex0_SHIFT                    24

/* SID_DQ :: RAM_END :: DequantIndex1 [23:16] */
#define BCHP_SID_DQ_RAM_END_DequantIndex1_MASK                     0x00ff0000
#define BCHP_SID_DQ_RAM_END_DequantIndex1_SHIFT                    16

/* SID_DQ :: RAM_END :: DequantIndex2 [15:08] */
#define BCHP_SID_DQ_RAM_END_DequantIndex2_MASK                     0x0000ff00
#define BCHP_SID_DQ_RAM_END_DequantIndex2_SHIFT                    8

/* SID_DQ :: RAM_END :: DequantIndex3 [07:00] */
#define BCHP_SID_DQ_RAM_END_DequantIndex3_MASK                     0x000000ff
#define BCHP_SID_DQ_RAM_END_DequantIndex3_SHIFT                    0

#endif /* #ifndef BCHP_SID_DQ_H__ */

/* End of File */

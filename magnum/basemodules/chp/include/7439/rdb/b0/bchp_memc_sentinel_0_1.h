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
 * Date:           Generated on               Mon Jul 28 13:33:55 2014
 *                 Full Compile MD5 Checksum  c5ff84748c7fa0d54c801cf0c03aeeca
 *                     (minus title and desc)
 *                 MD5 Checksum               62ec62fd8717a3b00aa7784ade95abce
 *
 * Compiled with:  RDB Utility                combo_header.pl
 *                 RDB.pm                     14541
 *                 unknown                    unknown
 *                 Perl Interpreter           5.008008
 *                 Operating System           linux
 *
 *
 ***************************************************************************/

#ifndef BCHP_MEMC_SENTINEL_0_1_H__
#define BCHP_MEMC_SENTINEL_0_1_H__

/***************************************************************************
 *MEMC_SENTINEL_0_1 - TraceLog Sentinel Register Range
 ***************************************************************************/
#define BCHP_MEMC_SENTINEL_0_1_SENTINEL_RANGE_START 0x011c0000 /* [RW] Sentinel Start Address */
#define BCHP_MEMC_SENTINEL_0_1_SENTINEL_RANGE_END 0x011ffffc /* [RW] Sentinel End Address */

/***************************************************************************
 *SENTINEL_RANGE_START - Sentinel Start Address
 ***************************************************************************/
/* MEMC_SENTINEL_0_1 :: SENTINEL_RANGE_START :: ADDRESS [31:00] */
#define BCHP_MEMC_SENTINEL_0_1_SENTINEL_RANGE_START_ADDRESS_MASK   0xffffffff
#define BCHP_MEMC_SENTINEL_0_1_SENTINEL_RANGE_START_ADDRESS_SHIFT  0

/***************************************************************************
 *SENTINEL_RANGE_END - Sentinel End Address
 ***************************************************************************/
/* MEMC_SENTINEL_0_1 :: SENTINEL_RANGE_END :: ADDRESS [31:00] */
#define BCHP_MEMC_SENTINEL_0_1_SENTINEL_RANGE_END_ADDRESS_MASK     0xffffffff
#define BCHP_MEMC_SENTINEL_0_1_SENTINEL_RANGE_END_ADDRESS_SHIFT    0

#endif /* #ifndef BCHP_MEMC_SENTINEL_0_1_H__ */

/* End of File */

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
 * Date:           Generated on               Tue Aug 26 10:56:51 2014
 *                 Full Compile MD5 Checksum  fe5bf937ded6451208bcd12a03dadcff
 *                     (minus title and desc)
 *                 MD5 Checksum               e67548d0bfc4c43233ca60dd5a6dc076
 *
 * Compiled with:  RDB Utility                combo_header.pl
 *                 RDB.pm                     14541
 *                 unknown                    unknown
 *                 Perl Interpreter           5.014001
 *                 Operating System           linux
 *
 *
 ***************************************************************************/

#ifndef BCHP_RVC_2_0_H__
#define BCHP_RVC_2_0_H__

/***************************************************************************
 *RVC_2_0
 ***************************************************************************/
#define BCHP_RVC_2_0_CTL                         0x00146c00 /* [RW] Control register */
#define BCHP_RVC_2_0_PUT                         0x00146c04 /* [RO] Put pointer */
#define BCHP_RVC_2_0_GET                         0x00146c08 /* [RW] Get pointer */
#define BCHP_RVC_2_0_BASE                        0x00146c0c /* [RW] Circular buffer base address */
#define BCHP_RVC_2_0_END                         0x00146c10 /* [RW] Circular buffer end address */
#define BCHP_RVC_2_0_RANGE1_START                0x00146c14 /* [RW] Address range start */
#define BCHP_RVC_2_0_RANGE1_END                  0x00146c18 /* [RW] Address range end */
#define BCHP_RVC_2_0_RANGE2_START                0x00146c1c /* [RW] Address range start */
#define BCHP_RVC_2_0_RANGE2_END                  0x00146c20 /* [RW] Address range end */

#endif /* #ifndef BCHP_RVC_2_0_H__ */

/* End of File */

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
 * Date:           Generated on               Mon Jul 28 13:28:41 2014
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

#ifndef BCHP_V3D_VPM_H__
#define BCHP_V3D_VPM_H__

/***************************************************************************
 *V3D_VPM - V3D Vertex Pipe Memory Allocation Registers
 ***************************************************************************/
#define BCHP_V3D_VPM_VPACNTL                     0x00bea500 /* [RW] VPM Allocator Control */
#define BCHP_V3D_VPM_VPMBASE                     0x00bea504 /* [RW] VPM base (user) memory reservation */

/***************************************************************************
 *VPACNTL - VPM Allocator Control
 ***************************************************************************/
/* V3D_VPM :: VPACNTL :: reserved0 [31:14] */
#define BCHP_V3D_VPM_VPACNTL_reserved0_MASK                        0xffffc000
#define BCHP_V3D_VPM_VPACNTL_reserved0_SHIFT                       14

/* V3D_VPM :: VPACNTL :: VPATOEN [13:13] */
#define BCHP_V3D_VPM_VPACNTL_VPATOEN_MASK                          0x00002000
#define BCHP_V3D_VPM_VPACNTL_VPATOEN_SHIFT                         13
#define BCHP_V3D_VPM_VPACNTL_VPATOEN_DEFAULT                       0x00000000

/* V3D_VPM :: VPACNTL :: VPALIMEN [12:12] */
#define BCHP_V3D_VPM_VPACNTL_VPALIMEN_MASK                         0x00001000
#define BCHP_V3D_VPM_VPACNTL_VPALIMEN_SHIFT                        12
#define BCHP_V3D_VPM_VPACNTL_VPALIMEN_DEFAULT                      0x00000000

/* V3D_VPM :: VPACNTL :: VPABATO [11:09] */
#define BCHP_V3D_VPM_VPACNTL_VPABATO_MASK                          0x00000e00
#define BCHP_V3D_VPM_VPACNTL_VPABATO_SHIFT                         9
#define BCHP_V3D_VPM_VPACNTL_VPABATO_DEFAULT                       0x00000000

/* V3D_VPM :: VPACNTL :: VPARATO [08:06] */
#define BCHP_V3D_VPM_VPACNTL_VPARATO_MASK                          0x000001c0
#define BCHP_V3D_VPM_VPACNTL_VPARATO_SHIFT                         6
#define BCHP_V3D_VPM_VPACNTL_VPARATO_DEFAULT                       0x00000000

/* V3D_VPM :: VPACNTL :: VPABALIM [05:03] */
#define BCHP_V3D_VPM_VPACNTL_VPABALIM_MASK                         0x00000038
#define BCHP_V3D_VPM_VPACNTL_VPABALIM_SHIFT                        3
#define BCHP_V3D_VPM_VPACNTL_VPABALIM_DEFAULT                      0x00000000

/* V3D_VPM :: VPACNTL :: VPARALIM [02:00] */
#define BCHP_V3D_VPM_VPACNTL_VPARALIM_MASK                         0x00000007
#define BCHP_V3D_VPM_VPACNTL_VPARALIM_SHIFT                        0
#define BCHP_V3D_VPM_VPACNTL_VPARALIM_DEFAULT                      0x00000000

/***************************************************************************
 *VPMBASE - VPM base (user) memory reservation
 ***************************************************************************/
/* V3D_VPM :: VPMBASE :: reserved0 [31:06] */
#define BCHP_V3D_VPM_VPMBASE_reserved0_MASK                        0xffffffc0
#define BCHP_V3D_VPM_VPMBASE_reserved0_SHIFT                       6

/* V3D_VPM :: VPMBASE :: VPMURSV [05:00] */
#define BCHP_V3D_VPM_VPMBASE_VPMURSV_MASK                          0x0000003f
#define BCHP_V3D_VPM_VPMBASE_VPMURSV_SHIFT                         0
#define BCHP_V3D_VPM_VPMBASE_VPMURSV_DEFAULT                       0x00000000

#endif /* #ifndef BCHP_V3D_VPM_H__ */

/* End of File */

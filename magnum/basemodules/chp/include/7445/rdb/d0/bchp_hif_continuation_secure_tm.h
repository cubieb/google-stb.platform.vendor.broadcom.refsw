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
 * Date:           Generated on              Mon Sep 23 09:50:36 2013
 *                 Full Compile MD5 Checksum fcccce298b546dd6a1f4cbad288478da
 *                   (minus title and desc)  
 *                 MD5 Checksum              211556602e37a33262598b3d5eeba81c
 *
 * Compiled with:  RDB Utility               combo_header.pl
 *                 RDB Parser                3.0
 *                 unknown                   unknown
 *                 Perl Interpreter          5.008008
 *                 Operating System          linux
 *
 * Revision History:
 *
 * $brcm_Log: $
 * 
 ***************************************************************************/

#ifndef BCHP_HIF_CONTINUATION_SECURE_TM_H__
#define BCHP_HIF_CONTINUATION_SECURE_TM_H__

/***************************************************************************
 *HIF_CONTINUATION_SECURE_TM - Secure HIF Boot Continuation register for Test Mode 1, 2, 8
 ***************************************************************************/
#define BCHP_HIF_CONTINUATION_SECURE_TM_STB_BOOT_HI_ADDR0 0x003e3600 /* Higher 8-bit of HIF's STB Boot Continuation Address 0 Register */
#define BCHP_HIF_CONTINUATION_SECURE_TM_STB_BOOT_ADDR0 0x003e3604 /* Lower 32-bit of HIF's STB Boot Continuation Address 0 Register */

/***************************************************************************
 *STB_BOOT_HI_ADDR0 - Higher 8-bit of HIF's STB Boot Continuation Address 0 Register
 ***************************************************************************/
/* HIF_CONTINUATION_SECURE_TM :: STB_BOOT_HI_ADDR0 :: reserved0 [31:08] */
#define BCHP_HIF_CONTINUATION_SECURE_TM_STB_BOOT_HI_ADDR0_reserved0_MASK 0xffffff00
#define BCHP_HIF_CONTINUATION_SECURE_TM_STB_BOOT_HI_ADDR0_reserved0_SHIFT 8

/* HIF_CONTINUATION_SECURE_TM :: STB_BOOT_HI_ADDR0 :: ADDRESS [07:00] */
#define BCHP_HIF_CONTINUATION_SECURE_TM_STB_BOOT_HI_ADDR0_ADDRESS_MASK 0x000000ff
#define BCHP_HIF_CONTINUATION_SECURE_TM_STB_BOOT_HI_ADDR0_ADDRESS_SHIFT 0
#define BCHP_HIF_CONTINUATION_SECURE_TM_STB_BOOT_HI_ADDR0_ADDRESS_DEFAULT 0x00000000

/***************************************************************************
 *STB_BOOT_ADDR0 - Lower 32-bit of HIF's STB Boot Continuation Address 0 Register
 ***************************************************************************/
/* HIF_CONTINUATION_SECURE_TM :: STB_BOOT_ADDR0 :: ADDRESS [31:00] */
#define BCHP_HIF_CONTINUATION_SECURE_TM_STB_BOOT_ADDR0_ADDRESS_MASK 0xffffffff
#define BCHP_HIF_CONTINUATION_SECURE_TM_STB_BOOT_ADDR0_ADDRESS_SHIFT 0
#define BCHP_HIF_CONTINUATION_SECURE_TM_STB_BOOT_ADDR0_ADDRESS_DEFAULT 0xe0000000

#endif /* #ifndef BCHP_HIF_CONTINUATION_SECURE_TM_H__ */

/* End of File */

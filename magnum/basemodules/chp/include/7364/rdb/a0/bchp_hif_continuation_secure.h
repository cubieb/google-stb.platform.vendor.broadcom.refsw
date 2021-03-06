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
 * Date:           Generated on               Fri Aug 15 15:20:55 2014
 *                 Full Compile MD5 Checksum  a68bc62e9dd3be19fcad480c369d60fd
 *                     (minus title and desc)
 *                 MD5 Checksum               14382795d76d8497c2dd1bcf3f5d36da
 *
 * Compiled with:  RDB Utility                combo_header.pl
 *                 RDB.pm                     14541
 *                 unknown                    unknown
 *                 Perl Interpreter           5.008008
 *                 Operating System           linux
 *
 *
 ***************************************************************************/

#ifndef BCHP_HIF_CONTINUATION_SECURE_H__
#define BCHP_HIF_CONTINUATION_SECURE_H__

/***************************************************************************
 *HIF_CONTINUATION_SECURE - Secure HIF Boot Continuation register
 ***************************************************************************/
#define BCHP_HIF_CONTINUATION_SECURE_STB_BOOT_HI_ADDR0 0x00431000 /* [RW] Higher 8-bit of HIF's STB Boot Continuation Address 0 Register */
#define BCHP_HIF_CONTINUATION_SECURE_STB_BOOT_ADDR0 0x00431004 /* [RW] Lower 32-bit of HIF's STB Boot Continuation Address 0 Register */

/***************************************************************************
 *STB_BOOT_HI_ADDR0 - Higher 8-bit of HIF's STB Boot Continuation Address 0 Register
 ***************************************************************************/
/* HIF_CONTINUATION_SECURE :: STB_BOOT_HI_ADDR0 :: reserved0 [31:08] */
#define BCHP_HIF_CONTINUATION_SECURE_STB_BOOT_HI_ADDR0_reserved0_MASK 0xffffff00
#define BCHP_HIF_CONTINUATION_SECURE_STB_BOOT_HI_ADDR0_reserved0_SHIFT 8

/* HIF_CONTINUATION_SECURE :: STB_BOOT_HI_ADDR0 :: ADDRESS [07:00] */
#define BCHP_HIF_CONTINUATION_SECURE_STB_BOOT_HI_ADDR0_ADDRESS_MASK 0x000000ff
#define BCHP_HIF_CONTINUATION_SECURE_STB_BOOT_HI_ADDR0_ADDRESS_SHIFT 0
#define BCHP_HIF_CONTINUATION_SECURE_STB_BOOT_HI_ADDR0_ADDRESS_DEFAULT 0x00000000

/***************************************************************************
 *STB_BOOT_ADDR0 - Lower 32-bit of HIF's STB Boot Continuation Address 0 Register
 ***************************************************************************/
/* HIF_CONTINUATION_SECURE :: STB_BOOT_ADDR0 :: ADDRESS [31:00] */
#define BCHP_HIF_CONTINUATION_SECURE_STB_BOOT_ADDR0_ADDRESS_MASK   0xffffffff
#define BCHP_HIF_CONTINUATION_SECURE_STB_BOOT_ADDR0_ADDRESS_SHIFT  0
#define BCHP_HIF_CONTINUATION_SECURE_STB_BOOT_ADDR0_ADDRESS_DEFAULT 0xe0000000

#endif /* #ifndef BCHP_HIF_CONTINUATION_SECURE_H__ */

/* End of File */

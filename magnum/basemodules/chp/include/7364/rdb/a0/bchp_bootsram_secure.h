/***************************************************************************
 *     Copyright (c) 1999-2014, Broadcom Corporation
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
 * Date:           Generated on              Mon Dec 30 11:35:09 2013
 *                 Full Compile MD5 Checksum c9693f7b56342ee7130ead5124f6e958
 *                   (minus title and desc)
 *                 MD5 Checksum              b532d876ba16be9c59997d81558bdc63
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

#ifndef BCHP_BOOTSRAM_SECURE_H__
#define BCHP_BOOTSRAM_SECURE_H__

/***************************************************************************
 *BOOTSRAM_SECURE - Secure CPU BOOTSRAM array
 ***************************************************************************/

/***************************************************************************
 *DATA_ARRAY%i - CPU BootSRAM Data Array of size 4KB. Depending on bootmodes and chip operating sequences, this BootSRAM content may become inaccessible. In such scenarios, any read access to the BootSRAM will return 0x0.
 ***************************************************************************/
#define BCHP_BOOTSRAM_SECURE_DATA_ARRAYi_ARRAY_BASE                0x00420000
#define BCHP_BOOTSRAM_SECURE_DATA_ARRAYi_ARRAY_START               0
#define BCHP_BOOTSRAM_SECURE_DATA_ARRAYi_ARRAY_END                 16383
#define BCHP_BOOTSRAM_SECURE_DATA_ARRAYi_ARRAY_ELEMENT_SIZE        32

/***************************************************************************
 *DATA_ARRAY%i - CPU BootSRAM Data Array of size 4KB. Depending on bootmodes and chip operating sequences, this BootSRAM content may become inaccessible. In such scenarios, any read access to the BootSRAM will return 0x0.
 ***************************************************************************/
/* BOOTSRAM_SECURE :: DATA_ARRAYi :: WORD [31:00] */
#define BCHP_BOOTSRAM_SECURE_DATA_ARRAYi_WORD_MASK                 0xffffffff
#define BCHP_BOOTSRAM_SECURE_DATA_ARRAYi_WORD_SHIFT                0


#endif /* #ifndef BCHP_BOOTSRAM_SECURE_H__ */

/* End of File */

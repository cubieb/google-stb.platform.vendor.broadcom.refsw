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
 * Date:           Generated on              Mon Dec 23 13:19:21 2013
 *                 Full Compile MD5 Checksum e5d1378cc1475b750905e70cb70c73d9
 *                   (minus title and desc)  
 *                 MD5 Checksum              aa943f3142a624837db5321711723fcf
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

#ifndef BCHP_DVI_MISC_0_H__
#define BCHP_DVI_MISC_0_H__

/***************************************************************************
 *DVI_MISC_0 - DVI Misc block 0
 ***************************************************************************/
#define BCHP_DVI_MISC_0_CSC_BYPASS_OVERRIDE_CONTROL 0x006a3600 /* CSC Bypass Override Control Register */

/***************************************************************************
 *CSC_BYPASS_OVERRIDE_CONTROL - CSC Bypass Override Control Register
 ***************************************************************************/
/* DVI_MISC_0 :: CSC_BYPASS_OVERRIDE_CONTROL :: reserved0 [31:02] */
#define BCHP_DVI_MISC_0_CSC_BYPASS_OVERRIDE_CONTROL_reserved0_MASK 0xfffffffc
#define BCHP_DVI_MISC_0_CSC_BYPASS_OVERRIDE_CONTROL_reserved0_SHIFT 2

/* DVI_MISC_0 :: CSC_BYPASS_OVERRIDE_CONTROL :: OVERRIDE_ENABLE [01:01] */
#define BCHP_DVI_MISC_0_CSC_BYPASS_OVERRIDE_CONTROL_OVERRIDE_ENABLE_MASK 0x00000002
#define BCHP_DVI_MISC_0_CSC_BYPASS_OVERRIDE_CONTROL_OVERRIDE_ENABLE_SHIFT 1
#define BCHP_DVI_MISC_0_CSC_BYPASS_OVERRIDE_CONTROL_OVERRIDE_ENABLE_DEFAULT 0x00000000

/* DVI_MISC_0 :: CSC_BYPASS_OVERRIDE_CONTROL :: OVERRIDE_VALUE [00:00] */
#define BCHP_DVI_MISC_0_CSC_BYPASS_OVERRIDE_CONTROL_OVERRIDE_VALUE_MASK 0x00000001
#define BCHP_DVI_MISC_0_CSC_BYPASS_OVERRIDE_CONTROL_OVERRIDE_VALUE_SHIFT 0
#define BCHP_DVI_MISC_0_CSC_BYPASS_OVERRIDE_CONTROL_OVERRIDE_VALUE_DEFAULT 0x00000000

#endif /* #ifndef BCHP_DVI_MISC_0_H__ */

/* End of File */

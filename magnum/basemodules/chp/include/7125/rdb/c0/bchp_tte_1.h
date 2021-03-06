/***************************************************************************
 *     Copyright (c) 1999-2010, Broadcom Corporation
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
 * Date:           Generated on         Fri Jan 22 20:15:42 2010
 *                 MD5 Checksum         a2d1f2163f65e87d228a0fb491cb442d
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

#ifndef BCHP_TTE_1_H__
#define BCHP_TTE_1_H__

/***************************************************************************
 *TTE_1 - TTE_1 registers
 ***************************************************************************/
#define BCHP_TTE_1_status                        0x00888b04 /* teletext_status Register */
#define BCHP_TTE_1_control                       0x00888b08 /* teletext_control Register */
#define BCHP_TTE_1_lines_active                  0x00888b0c /* teletext_lines_active Register */
#define BCHP_TTE_1_read_address_top              0x00888b10 /* Base Address of top Teletext buffer */
#define BCHP_TTE_1_read_address_bottom           0x00888b14 /* Base Address of bottom Teletext buffer */
#define BCHP_TTE_1_output_format                 0x00888b1c /* teletext_output_format Register */
#define BCHP_TTE_1_top_mask                      0x00888b20 /* Teletext Top Mask Register */
#define BCHP_TTE_1_bottom_mask                   0x00888b24 /* Teletext Top Mask Register */
#define BCHP_TTE_1_revid                         0x00888b28 /* Teletext Encoder Revision ID Register */

#endif /* #ifndef BCHP_TTE_1_H__ */

/* End of File */

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
 * Date:           Generated on         Thu Apr 22 17:26:20 2010
 *                 MD5 Checksum         e645cb91be669b614b9400e5da71f4fa
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
#define BCHP_TTE_1_status                        0x007a8e04 /* teletext_status Register */
#define BCHP_TTE_1_control                       0x007a8e08 /* teletext_control Register */
#define BCHP_TTE_1_lines_active                  0x007a8e0c /* teletext_lines_active Register */
#define BCHP_TTE_1_read_address_top              0x007a8e10 /* Base Address of top Teletext buffer */
#define BCHP_TTE_1_read_address_bottom           0x007a8e14 /* Base Address of bottom Teletext buffer */
#define BCHP_TTE_1_output_format                 0x007a8e1c /* teletext_output_format Register */
#define BCHP_TTE_1_top_mask                      0x007a8e20 /* Teletext Top Mask Register */
#define BCHP_TTE_1_bottom_mask                   0x007a8e24 /* Teletext Top Mask Register */
#define BCHP_TTE_1_revid                         0x007a8e28 /* Teletext Encoder Revision ID Register */

#endif /* #ifndef BCHP_TTE_1_H__ */

/* End of File */

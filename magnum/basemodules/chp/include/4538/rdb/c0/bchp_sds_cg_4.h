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
 * Date:           Generated on              Fri Oct 18 11:45:08 2013
 *                 Full Compile MD5 Checksum 32c6546d3ec1c83fbf8bc6d4e3ec46d1
 *                   (minus title and desc)  
 *                 MD5 Checksum              839f407f1c04ba70b32cb458815eb9b4
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

#ifndef BCHP_SDS_CG_4_H__
#define BCHP_SDS_CG_4_H__

/***************************************************************************
 *SDS_CG_4 - SDS Clockgen Register Set
 ***************************************************************************/
#define BCHP_SDS_CG_4_RSTCTL                     0x000d8000 /* Reset Control */
#define BCHP_SDS_CG_4_CGDIV00                    0x000d8010 /* Clock Generator Divider register 0 (Formerly,CGDIV4,CGDIV3,CGDIV7[7:4],CGMISC,CGCTRL) */
#define BCHP_SDS_CG_4_CGDIV01                    0x000d8014 /* Clock Generator Divider register 1 (Formerly,CGDIV11,CGDIV10,CGDIV9,CGDIV8) */
#define BCHP_SDS_CG_4_SPLL_NPDIV                 0x000d8020 /* Sample Clock PLL Feedback Divider Control */
#define BCHP_SDS_CG_4_SPLL_MDIV_CTRL             0x000d8024 /* Sample Clock PLL Post-divider Control */
#define BCHP_SDS_CG_4_SPLL_CTRL                  0x000d8028 /* Sample Clock PLL Control */
#define BCHP_SDS_CG_4_SPLL_SSC_CTRL1             0x000d802c /* Sample Clock PLL Spread Spectrum Control 1 */
#define BCHP_SDS_CG_4_SPLL_SSC_CTRL0             0x000d8030 /* Sample Clock PLL Spread Spectrum Control 0 */
#define BCHP_SDS_CG_4_SPLL_STATUS                0x000d8034 /* Sample Clock PLL Status */
#define BCHP_SDS_CG_4_SPLL_PWRDN_RST             0x000d8038 /* Sample Clock PLL Power Down and Reset Control */

#endif /* #ifndef BCHP_SDS_CG_4_H__ */

/* End of File */

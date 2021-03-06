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
 * Date:           Generated on         Thu Apr 22 17:40:01 2010
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

#ifndef BCHP_ITU656_CSC_0_H__
#define BCHP_ITU656_CSC_0_H__

/***************************************************************************
 *ITU656_CSC_0 - ITU 656 Color Space Converter
 ***************************************************************************/
#define BCHP_ITU656_CSC_0_CSC_REV_ID             0x007a5b40 /* Revision ID register */
#define BCHP_ITU656_CSC_0_CSC_MODE               0x007a5b48 /* Color space converter mode register */
#define BCHP_ITU656_CSC_0_CSC_MIN_MAX            0x007a5b4c /* Color space converter min_max clamp register */
#define BCHP_ITU656_CSC_0_CSC_COEFF_C01_C00      0x007a5b50 /* Video Encoder Color Matrix coefficients c01 and c00 */
#define BCHP_ITU656_CSC_0_CSC_COEFF_C03_C02      0x007a5b54 /* Video Encoder Color Matrix coefficients c03 and c02 */
#define BCHP_ITU656_CSC_0_CSC_COEFF_C11_C10      0x007a5b58 /* Video Encoder Color Matrix coefficients c11 and c10 */
#define BCHP_ITU656_CSC_0_CSC_COEFF_C13_C12      0x007a5b5c /* Video Encoder Color Matrix coefficients c13 and c12 */
#define BCHP_ITU656_CSC_0_CSC_COEFF_C21_C20      0x007a5b60 /* Video Encoder Color Matrix coefficients c21 and c20 */
#define BCHP_ITU656_CSC_0_CSC_COEFF_C23_C22      0x007a5b64 /* Video Encoder Color Matrix coefficients c23 and c22 */
#define BCHP_ITU656_CSC_0_DITHER_CONTROL         0x007a5b68 /* Color Space Converter Dither Control */
#define BCHP_ITU656_CSC_0_DITHER_LFSR            0x007a5b6c /* Color Space Converter Dither LFSR Control */
#define BCHP_ITU656_CSC_0_DITHER_LFSR_INIT       0x007a5b70 /* Color Space Converter Dither LFSR Init value and control */

#endif /* #ifndef BCHP_ITU656_CSC_0_H__ */

/* End of File */

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
 * Date:           Generated on              Mon Sep 23 09:50:35 2013
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

#ifndef BCHP_HEVD_PFRI_0_H__
#define BCHP_HEVD_PFRI_0_H__

/***************************************************************************
 *HEVD_PFRI_0
 ***************************************************************************/
#define BCHP_HEVD_PFRI_0_INFO                    0x00026a00 /* PFRI Information */
#define BCHP_HEVD_PFRI_0_STRIPE_HEIGHT           0x00026a04 /* SDRAM Stripe Height Control */
#define BCHP_HEVD_PFRI_0_STRIPE_WIDTH            0x00026a08 /* SDRAM Stripe Width Control */

/***************************************************************************
 *INFO - PFRI Information
 ***************************************************************************/
/* HEVD_PFRI_0 :: INFO :: reserved0 [31:06] */
#define BCHP_HEVD_PFRI_0_INFO_reserved0_MASK                       0xffffffc0
#define BCHP_HEVD_PFRI_0_INFO_reserved0_SHIFT                      6

/* HEVD_PFRI_0 :: INFO :: pfri_bank_height [05:04] */
#define BCHP_HEVD_PFRI_0_INFO_pfri_bank_height_MASK                0x00000030
#define BCHP_HEVD_PFRI_0_INFO_pfri_bank_height_SHIFT               4

/* HEVD_PFRI_0 :: INFO :: pfri_data_width [03:02] */
#define BCHP_HEVD_PFRI_0_INFO_pfri_data_width_MASK                 0x0000000c
#define BCHP_HEVD_PFRI_0_INFO_pfri_data_width_SHIFT                2
#define BCHP_HEVD_PFRI_0_INFO_pfri_data_width_DEFAULT              0x00000002

/* HEVD_PFRI_0 :: INFO :: pfri_source [01:00] */
#define BCHP_HEVD_PFRI_0_INFO_pfri_source_MASK                     0x00000003
#define BCHP_HEVD_PFRI_0_INFO_pfri_source_SHIFT                    0
#define BCHP_HEVD_PFRI_0_INFO_pfri_source_DEFAULT                  0x00000000

/***************************************************************************
 *STRIPE_HEIGHT - SDRAM Stripe Height Control
 ***************************************************************************/
/* HEVD_PFRI_0 :: STRIPE_HEIGHT :: reserved0 [31:27] */
#define BCHP_HEVD_PFRI_0_STRIPE_HEIGHT_reserved0_MASK              0xf8000000
#define BCHP_HEVD_PFRI_0_STRIPE_HEIGHT_reserved0_SHIFT             27

/* HEVD_PFRI_0 :: STRIPE_HEIGHT :: Chroma_Height [26:16] */
#define BCHP_HEVD_PFRI_0_STRIPE_HEIGHT_Chroma_Height_MASK          0x07ff0000
#define BCHP_HEVD_PFRI_0_STRIPE_HEIGHT_Chroma_Height_SHIFT         16

/* HEVD_PFRI_0 :: STRIPE_HEIGHT :: reserved1 [15:13] */
#define BCHP_HEVD_PFRI_0_STRIPE_HEIGHT_reserved1_MASK              0x0000e000
#define BCHP_HEVD_PFRI_0_STRIPE_HEIGHT_reserved1_SHIFT             13

/* HEVD_PFRI_0 :: STRIPE_HEIGHT :: Height [12:00] */
#define BCHP_HEVD_PFRI_0_STRIPE_HEIGHT_Height_MASK                 0x00001fff
#define BCHP_HEVD_PFRI_0_STRIPE_HEIGHT_Height_SHIFT                0

/***************************************************************************
 *STRIPE_WIDTH - SDRAM Stripe Width Control
 ***************************************************************************/
/* HEVD_PFRI_0 :: STRIPE_WIDTH :: reserved0 [31:02] */
#define BCHP_HEVD_PFRI_0_STRIPE_WIDTH_reserved0_MASK               0xfffffffc
#define BCHP_HEVD_PFRI_0_STRIPE_WIDTH_reserved0_SHIFT              2

/* HEVD_PFRI_0 :: STRIPE_WIDTH :: Stripe_Width [01:00] */
#define BCHP_HEVD_PFRI_0_STRIPE_WIDTH_Stripe_Width_MASK            0x00000003
#define BCHP_HEVD_PFRI_0_STRIPE_WIDTH_Stripe_Width_SHIFT           0
#define BCHP_HEVD_PFRI_0_STRIPE_WIDTH_Stripe_Width_DEFAULT         0x00000000

/***************************************************************************
 *PICT_BASE_Y%i - SDRAM Picture Base Registers
 ***************************************************************************/
#define BCHP_HEVD_PFRI_0_PICT_BASE_Yi_ARRAY_BASE                   0x00026a80
#define BCHP_HEVD_PFRI_0_PICT_BASE_Yi_ARRAY_START                  0
#define BCHP_HEVD_PFRI_0_PICT_BASE_Yi_ARRAY_END                    22
#define BCHP_HEVD_PFRI_0_PICT_BASE_Yi_ARRAY_ELEMENT_SIZE           32

/***************************************************************************
 *PICT_BASE_Y%i - SDRAM Picture Base Registers
 ***************************************************************************/
/* HEVD_PFRI_0 :: PICT_BASE_Yi :: Addr [31:12] */
#define BCHP_HEVD_PFRI_0_PICT_BASE_Yi_Addr_MASK                    0xfffff000
#define BCHP_HEVD_PFRI_0_PICT_BASE_Yi_Addr_SHIFT                   12
#define BCHP_HEVD_PFRI_0_PICT_BASE_Yi_Addr_DEFAULT                 0x00000000

/* HEVD_PFRI_0 :: PICT_BASE_Yi :: reserved0 [11:00] */
#define BCHP_HEVD_PFRI_0_PICT_BASE_Yi_reserved0_MASK               0x00000fff
#define BCHP_HEVD_PFRI_0_PICT_BASE_Yi_reserved0_SHIFT              0


/***************************************************************************
 *PICT_BASE_UV%i - SDRAM Picture Base Registers
 ***************************************************************************/
#define BCHP_HEVD_PFRI_0_PICT_BASE_UVi_ARRAY_BASE                  0x00026b00
#define BCHP_HEVD_PFRI_0_PICT_BASE_UVi_ARRAY_START                 0
#define BCHP_HEVD_PFRI_0_PICT_BASE_UVi_ARRAY_END                   22
#define BCHP_HEVD_PFRI_0_PICT_BASE_UVi_ARRAY_ELEMENT_SIZE          32

/***************************************************************************
 *PICT_BASE_UV%i - SDRAM Picture Base Registers
 ***************************************************************************/
/* HEVD_PFRI_0 :: PICT_BASE_UVi :: Addr [31:12] */
#define BCHP_HEVD_PFRI_0_PICT_BASE_UVi_Addr_MASK                   0xfffff000
#define BCHP_HEVD_PFRI_0_PICT_BASE_UVi_Addr_SHIFT                  12
#define BCHP_HEVD_PFRI_0_PICT_BASE_UVi_Addr_DEFAULT                0x00000000

/* HEVD_PFRI_0 :: PICT_BASE_UVi :: reserved0 [11:00] */
#define BCHP_HEVD_PFRI_0_PICT_BASE_UVi_reserved0_MASK              0x00000fff
#define BCHP_HEVD_PFRI_0_PICT_BASE_UVi_reserved0_SHIFT             0


#endif /* #ifndef BCHP_HEVD_PFRI_0_H__ */

/* End of File */

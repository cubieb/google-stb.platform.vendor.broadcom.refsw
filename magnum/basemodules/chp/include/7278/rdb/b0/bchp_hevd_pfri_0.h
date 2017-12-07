/******************************************************************************
 *  Copyright (C) 2017 Broadcom. The term "Broadcom" refers to Broadcom Limited and/or its subsidiaries.
 *
 *  This program is the proprietary software of Broadcom and/or its licensors,
 *  and may only be used, duplicated, modified or distributed pursuant to the terms and
 *  conditions of a separate, written license agreement executed between you and Broadcom
 *  (an "Authorized License").  Except as set forth in an Authorized License, Broadcom grants
 *  no license (express or implied), right to use, or waiver of any kind with respect to the
 *  Software, and Broadcom expressly reserves all rights in and to the Software and all
 *  intellectual property rights therein.  IF YOU HAVE NO AUTHORIZED LICENSE, THEN YOU
 *  HAVE NO RIGHT TO USE THIS SOFTWARE IN ANY WAY, AND SHOULD IMMEDIATELY
 *  NOTIFY BROADCOM AND DISCONTINUE ALL USE OF THE SOFTWARE.
 *
 *  Except as expressly set forth in the Authorized License,
 *
 *  1.     This program, including its structure, sequence and organization, constitutes the valuable trade
 *  secrets of Broadcom, and you shall use all reasonable efforts to protect the confidentiality thereof,
 *  and to use this information only in connection with your use of Broadcom integrated circuit products.
 *
 *  2.     TO THE MAXIMUM EXTENT PERMITTED BY LAW, THE SOFTWARE IS PROVIDED "AS IS"
 *  AND WITH ALL FAULTS AND BROADCOM MAKES NO PROMISES, REPRESENTATIONS OR
 *  WARRANTIES, EITHER EXPRESS, IMPLIED, STATUTORY, OR OTHERWISE, WITH RESPECT TO
 *  THE SOFTWARE.  BROADCOM SPECIFICALLY DISCLAIMS ANY AND ALL IMPLIED WARRANTIES
 *  OF TITLE, MERCHANTABILITY, NONINFRINGEMENT, FITNESS FOR A PARTICULAR PURPOSE,
 *  LACK OF VIRUSES, ACCURACY OR COMPLETENESS, QUIET ENJOYMENT, QUIET POSSESSION
 *  OR CORRESPONDENCE TO DESCRIPTION. YOU ASSUME THE ENTIRE RISK ARISING OUT OF
 *  USE OR PERFORMANCE OF THE SOFTWARE.
 *
 *  3.     TO THE MAXIMUM EXTENT PERMITTED BY LAW, IN NO EVENT SHALL BROADCOM OR ITS
 *  LICENSORS BE LIABLE FOR (i) CONSEQUENTIAL, INCIDENTAL, SPECIAL, INDIRECT, OR
 *  EXEMPLARY DAMAGES WHATSOEVER ARISING OUT OF OR IN ANY WAY RELATING TO YOUR
 *  USE OF OR INABILITY TO USE THE SOFTWARE EVEN IF BROADCOM HAS BEEN ADVISED OF
 *  THE POSSIBILITY OF SUCH DAMAGES; OR (ii) ANY AMOUNT IN EXCESS OF THE AMOUNT
 *  ACTUALLY PAID FOR THE SOFTWARE ITSELF OR U.S. $1, WHICHEVER IS GREATER. THESE
 *  LIMITATIONS SHALL APPLY NOTWITHSTANDING ANY FAILURE OF ESSENTIAL PURPOSE OF
 *  ANY LIMITED REMEDY.
 *
 * Module Description:
 *                     DO NOT EDIT THIS FILE DIRECTLY
 *
 * This module was generated magically with RDB from a source description
 * file. You must edit the source file for changes to be made to this file.
 *
 * The launch point for all information concerning RDB is found at:
 *   http://bcgbu.broadcom.com/RDB/SitePages/Home.aspx
 *
 * Date:           Generated on               Thu Apr 13 10:09:31 2017
 *                 Full Compile MD5 Checksum  7f180d7646477bba2bae1a701efd9ef5
 *                     (minus title and desc)
 *                 MD5 Checksum               a2a4a53aa20c0c2f46073b879159b85d
 *
 * lock_release:   n/a
 * Compiled with:  RDB Utility                combo_header.pl
 *                 RDB.pm                     1395
 *                 unknown                    unknown
 *                 Perl Interpreter           5.008008
 *                 Operating System           linux
 *                 Script Source              tools/dvtsw/current/Linux/combo_header.pl
 *                 DVTSWVER                   LOCAL tools/dvtsw/current/Linux/combo_header.pl
 *
 *
********************************************************************************/

#ifndef BCHP_HEVD_PFRI_0_H__
#define BCHP_HEVD_PFRI_0_H__

/***************************************************************************
 *HEVD_PFRI_0
 ***************************************************************************/
#define BCHP_HEVD_PFRI_0_INFO                    0x00c26800 /* [CFG][32] PFRI Information */
#define BCHP_HEVD_PFRI_0_STRIPE_HEIGHT           0x00c26804 /* [CFG][32] SDRAM Stripe Height Control */
#define BCHP_HEVD_PFRI_0_STRIPE_WIDTH            0x00c26808 /* [CFG][32] SDRAM Stripe Width Control */

/***************************************************************************
 *INFO - PFRI Information
 ***************************************************************************/
/* HEVD_PFRI_0 :: INFO :: reserved0 [31:16] */
#define BCHP_HEVD_PFRI_0_INFO_reserved0_MASK                       0xffff0000
#define BCHP_HEVD_PFRI_0_INFO_reserved0_SHIFT                      16

/* HEVD_PFRI_0 :: INFO :: pfri_max_group [15:11] */
#define BCHP_HEVD_PFRI_0_INFO_pfri_max_group_MASK                  0x0000f800
#define BCHP_HEVD_PFRI_0_INFO_pfri_max_group_SHIFT                 11
#define BCHP_HEVD_PFRI_0_INFO_pfri_max_group_DEFAULT               0x00000000

/* HEVD_PFRI_0 :: INFO :: pfri_groupages_en [10:10] */
#define BCHP_HEVD_PFRI_0_INFO_pfri_groupages_en_MASK               0x00000400
#define BCHP_HEVD_PFRI_0_INFO_pfri_groupages_en_SHIFT              10
#define BCHP_HEVD_PFRI_0_INFO_pfri_groupages_en_DEFAULT            0x00000000

/* HEVD_PFRI_0 :: INFO :: reserved1 [09:08] */
#define BCHP_HEVD_PFRI_0_INFO_reserved1_MASK                       0x00000300
#define BCHP_HEVD_PFRI_0_INFO_reserved1_SHIFT                      8

/* HEVD_PFRI_0 :: INFO :: pfri_num_banks [07:06] */
#define BCHP_HEVD_PFRI_0_INFO_pfri_num_banks_MASK                  0x000000c0
#define BCHP_HEVD_PFRI_0_INFO_pfri_num_banks_SHIFT                 6
#define BCHP_HEVD_PFRI_0_INFO_pfri_num_banks_DEFAULT               0x00000000

/* HEVD_PFRI_0 :: INFO :: pfri_bank_height [05:04] */
#define BCHP_HEVD_PFRI_0_INFO_pfri_bank_height_MASK                0x00000030
#define BCHP_HEVD_PFRI_0_INFO_pfri_bank_height_SHIFT               4
#define BCHP_HEVD_PFRI_0_INFO_pfri_bank_height_DEFAULT             0x00000000

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
/* HEVD_PFRI_0 :: STRIPE_HEIGHT :: reserved0 [31:28] */
#define BCHP_HEVD_PFRI_0_STRIPE_HEIGHT_reserved0_MASK              0xf0000000
#define BCHP_HEVD_PFRI_0_STRIPE_HEIGHT_reserved0_SHIFT             28

/* HEVD_PFRI_0 :: STRIPE_HEIGHT :: Chroma_Height [27:16] */
#define BCHP_HEVD_PFRI_0_STRIPE_HEIGHT_Chroma_Height_MASK          0x0fff0000
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
#define BCHP_HEVD_PFRI_0_PICT_BASE_Yi_ARRAY_BASE                   0x00c26880
#define BCHP_HEVD_PFRI_0_PICT_BASE_Yi_ARRAY_START                  0
#define BCHP_HEVD_PFRI_0_PICT_BASE_Yi_ARRAY_END                    22
#define BCHP_HEVD_PFRI_0_PICT_BASE_Yi_ARRAY_ELEMENT_SIZE           64

/***************************************************************************
 *PICT_BASE_Y%i - SDRAM Picture Base Registers
 ***************************************************************************/
/* HEVD_PFRI_0 :: PICT_BASE_Yi :: reserved0 [63:40] */
#define BCHP_HEVD_PFRI_0_PICT_BASE_Yi_reserved0_MASK               BCHP_UINT64_C(0xffffff00, 0x00000000)
#define BCHP_HEVD_PFRI_0_PICT_BASE_Yi_reserved0_SHIFT              40

/* HEVD_PFRI_0 :: PICT_BASE_Yi :: Addr [39:12] */
#define BCHP_HEVD_PFRI_0_PICT_BASE_Yi_Addr_MASK                    BCHP_UINT64_C(0x000000ff, 0xfffff000)
#define BCHP_HEVD_PFRI_0_PICT_BASE_Yi_Addr_SHIFT                   12
#define BCHP_HEVD_PFRI_0_PICT_BASE_Yi_Addr_DEFAULT                 0

/* HEVD_PFRI_0 :: PICT_BASE_Yi :: reserved1 [11:01] */
#define BCHP_HEVD_PFRI_0_PICT_BASE_Yi_reserved1_MASK               BCHP_UINT64_C(0x00000000, 0x00000ffe)
#define BCHP_HEVD_PFRI_0_PICT_BASE_Yi_reserved1_SHIFT              1

/* HEVD_PFRI_0 :: PICT_BASE_Yi :: IllegalBuffer [00:00] */
#define BCHP_HEVD_PFRI_0_PICT_BASE_Yi_IllegalBuffer_MASK           BCHP_UINT64_C(0x00000000, 0x00000001)
#define BCHP_HEVD_PFRI_0_PICT_BASE_Yi_IllegalBuffer_SHIFT          0
#define BCHP_HEVD_PFRI_0_PICT_BASE_Yi_IllegalBuffer_DEFAULT        0


/***************************************************************************
 *PICT_BASE_UV%i - SDRAM Picture Base Registers
 ***************************************************************************/
#define BCHP_HEVD_PFRI_0_PICT_BASE_UVi_ARRAY_BASE                  0x00c26980
#define BCHP_HEVD_PFRI_0_PICT_BASE_UVi_ARRAY_START                 0
#define BCHP_HEVD_PFRI_0_PICT_BASE_UVi_ARRAY_END                   22
#define BCHP_HEVD_PFRI_0_PICT_BASE_UVi_ARRAY_ELEMENT_SIZE          64

/***************************************************************************
 *PICT_BASE_UV%i - SDRAM Picture Base Registers
 ***************************************************************************/
/* HEVD_PFRI_0 :: PICT_BASE_UVi :: reserved0 [63:40] */
#define BCHP_HEVD_PFRI_0_PICT_BASE_UVi_reserved0_MASK              BCHP_UINT64_C(0xffffff00, 0x00000000)
#define BCHP_HEVD_PFRI_0_PICT_BASE_UVi_reserved0_SHIFT             40

/* HEVD_PFRI_0 :: PICT_BASE_UVi :: Addr [39:12] */
#define BCHP_HEVD_PFRI_0_PICT_BASE_UVi_Addr_MASK                   BCHP_UINT64_C(0x000000ff, 0xfffff000)
#define BCHP_HEVD_PFRI_0_PICT_BASE_UVi_Addr_SHIFT                  12
#define BCHP_HEVD_PFRI_0_PICT_BASE_UVi_Addr_DEFAULT                0

/* HEVD_PFRI_0 :: PICT_BASE_UVi :: reserved1 [11:01] */
#define BCHP_HEVD_PFRI_0_PICT_BASE_UVi_reserved1_MASK              BCHP_UINT64_C(0x00000000, 0x00000ffe)
#define BCHP_HEVD_PFRI_0_PICT_BASE_UVi_reserved1_SHIFT             1

/* HEVD_PFRI_0 :: PICT_BASE_UVi :: IllegalBuffer [00:00] */
#define BCHP_HEVD_PFRI_0_PICT_BASE_UVi_IllegalBuffer_MASK          BCHP_UINT64_C(0x00000000, 0x00000001)
#define BCHP_HEVD_PFRI_0_PICT_BASE_UVi_IllegalBuffer_SHIFT         0
#define BCHP_HEVD_PFRI_0_PICT_BASE_UVi_IllegalBuffer_DEFAULT       0


#endif /* #ifndef BCHP_HEVD_PFRI_0_H__ */

/* End of File */

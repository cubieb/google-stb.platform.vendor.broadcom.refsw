/***************************************************************************
 *     Copyright (c) 1999-2008, Broadcom Corporation
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
 * Date:           Generated on         Wed Jan  9 08:54:09 2008
 *                 MD5 Checksum         847dc12a9d71c4c68a648bbf19a883e3
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

#ifndef BCHP_SMARTCARD_PLL_H__
#define BCHP_SMARTCARD_PLL_H__

/***************************************************************************
 *SMARTCARD_PLL - Smart Card PLL
 ***************************************************************************/
#define BCHP_SMARTCARD_PLL_MACRO                 0x00041380 /* Smart Card PLL Sample Rate Macro Select */
#define BCHP_SMARTCARD_PLL_CONTROL               0x00041384 /* Smart Card PLL Control */
#define BCHP_SMARTCARD_PLL_USER_DIV1             0x00041388 /* Smart Card PLL User Divider Settings 1 */
#define BCHP_SMARTCARD_PLL_USER_DIV2             0x0004138c /* Smart Card PLL User Divider Settings 2 */
#define BCHP_SMARTCARD_PLL_ACTIVE_DIV1           0x00041394 /* Smart Card PLL Active Divider Settings 1 */
#define BCHP_SMARTCARD_PLL_ACTIVE_DIV2           0x00041398 /* Smart Card PLL Active Divider Settings 2 */

/***************************************************************************
 *MACRO - Smart Card PLL Sample Rate Macro Select
 ***************************************************************************/
/* SMARTCARD_PLL :: MACRO :: reserved0 [31:03] */
#define BCHP_SMARTCARD_PLL_MACRO_reserved0_MASK                    0xfffffff8
#define BCHP_SMARTCARD_PLL_MACRO_reserved0_SHIFT                   3

/* SMARTCARD_PLL :: MACRO :: MACRO_SELECT [02:00] */
#define BCHP_SMARTCARD_PLL_MACRO_MACRO_SELECT_MASK                 0x00000007
#define BCHP_SMARTCARD_PLL_MACRO_MACRO_SELECT_SHIFT                0
#define BCHP_SMARTCARD_PLL_MACRO_MACRO_SELECT_freq_36p864MHz       0
#define BCHP_SMARTCARD_PLL_MACRO_MACRO_SELECT_freq_27MHz           1
#define BCHP_SMARTCARD_PLL_MACRO_MACRO_SELECT_freq_24MHz           2
#define BCHP_SMARTCARD_PLL_MACRO_MACRO_SELECT_User                 7

/***************************************************************************
 *CONTROL - Smart Card PLL Control
 ***************************************************************************/
/* SMARTCARD_PLL :: CONTROL :: reserved0 [31:06] */
#define BCHP_SMARTCARD_PLL_CONTROL_reserved0_MASK                  0xffffffc0
#define BCHP_SMARTCARD_PLL_CONTROL_reserved0_SHIFT                 6

/* SMARTCARD_PLL :: CONTROL :: REFERENCE_SELECT [05:04] */
#define BCHP_SMARTCARD_PLL_CONTROL_REFERENCE_SELECT_MASK           0x00000030
#define BCHP_SMARTCARD_PLL_CONTROL_REFERENCE_SELECT_SHIFT          4
#define BCHP_SMARTCARD_PLL_CONTROL_REFERENCE_SELECT_VCXO_0         0
#define BCHP_SMARTCARD_PLL_CONTROL_REFERENCE_SELECT_VCXO_1         1
#define BCHP_SMARTCARD_PLL_CONTROL_REFERENCE_SELECT_RSRVD          2
#define BCHP_SMARTCARD_PLL_CONTROL_REFERENCE_SELECT_CLKGEN         3

/* SMARTCARD_PLL :: CONTROL :: reserved1 [03:01] */
#define BCHP_SMARTCARD_PLL_CONTROL_reserved1_MASK                  0x0000000e
#define BCHP_SMARTCARD_PLL_CONTROL_reserved1_SHIFT                 1

/* SMARTCARD_PLL :: CONTROL :: USER_UPDATE_DIVIDERS [00:00] */
#define BCHP_SMARTCARD_PLL_CONTROL_USER_UPDATE_DIVIDERS_MASK       0x00000001
#define BCHP_SMARTCARD_PLL_CONTROL_USER_UPDATE_DIVIDERS_SHIFT      0
#define BCHP_SMARTCARD_PLL_CONTROL_USER_UPDATE_DIVIDERS_Update_now 1
#define BCHP_SMARTCARD_PLL_CONTROL_USER_UPDATE_DIVIDERS_Dont_update 0

/***************************************************************************
 *USER_DIV1 - Smart Card PLL User Divider Settings 1
 ***************************************************************************/
/* SMARTCARD_PLL :: USER_DIV1 :: reserved0 [31:24] */
#define BCHP_SMARTCARD_PLL_USER_DIV1_reserved0_MASK                0xff000000
#define BCHP_SMARTCARD_PLL_USER_DIV1_reserved0_SHIFT               24

/* SMARTCARD_PLL :: USER_DIV1 :: M3DIV [23:16] */
#define BCHP_SMARTCARD_PLL_USER_DIV1_M3DIV_MASK                    0x00ff0000
#define BCHP_SMARTCARD_PLL_USER_DIV1_M3DIV_SHIFT                   16

/* SMARTCARD_PLL :: USER_DIV1 :: M2DIV [15:08] */
#define BCHP_SMARTCARD_PLL_USER_DIV1_M2DIV_MASK                    0x0000ff00
#define BCHP_SMARTCARD_PLL_USER_DIV1_M2DIV_SHIFT                   8

/* SMARTCARD_PLL :: USER_DIV1 :: M1DIV [07:00] */
#define BCHP_SMARTCARD_PLL_USER_DIV1_M1DIV_MASK                    0x000000ff
#define BCHP_SMARTCARD_PLL_USER_DIV1_M1DIV_SHIFT                   0

/***************************************************************************
 *USER_DIV2 - Smart Card PLL User Divider Settings 2
 ***************************************************************************/
/* SMARTCARD_PLL :: USER_DIV2 :: reserved0 [31:14] */
#define BCHP_SMARTCARD_PLL_USER_DIV2_reserved0_MASK                0xffffc000
#define BCHP_SMARTCARD_PLL_USER_DIV2_reserved0_SHIFT               14

/* SMARTCARD_PLL :: USER_DIV2 :: VCORNG [13:12] */
#define BCHP_SMARTCARD_PLL_USER_DIV2_VCORNG_MASK                   0x00003000
#define BCHP_SMARTCARD_PLL_USER_DIV2_VCORNG_SHIFT                  12

/* SMARTCARD_PLL :: USER_DIV2 :: reserved1 [11:09] */
#define BCHP_SMARTCARD_PLL_USER_DIV2_reserved1_MASK                0x00000e00
#define BCHP_SMARTCARD_PLL_USER_DIV2_reserved1_SHIFT               9

/* SMARTCARD_PLL :: USER_DIV2 :: NDIV_INT [08:00] */
#define BCHP_SMARTCARD_PLL_USER_DIV2_NDIV_INT_MASK                 0x000001ff
#define BCHP_SMARTCARD_PLL_USER_DIV2_NDIV_INT_SHIFT                0

/***************************************************************************
 *ACTIVE_DIV1 - Smart Card PLL Active Divider Settings 1
 ***************************************************************************/
/* SMARTCARD_PLL :: ACTIVE_DIV1 :: reserved0 [31:24] */
#define BCHP_SMARTCARD_PLL_ACTIVE_DIV1_reserved0_MASK              0xff000000
#define BCHP_SMARTCARD_PLL_ACTIVE_DIV1_reserved0_SHIFT             24

/* SMARTCARD_PLL :: ACTIVE_DIV1 :: M3DIV [23:16] */
#define BCHP_SMARTCARD_PLL_ACTIVE_DIV1_M3DIV_MASK                  0x00ff0000
#define BCHP_SMARTCARD_PLL_ACTIVE_DIV1_M3DIV_SHIFT                 16

/* SMARTCARD_PLL :: ACTIVE_DIV1 :: M2DIV [15:08] */
#define BCHP_SMARTCARD_PLL_ACTIVE_DIV1_M2DIV_MASK                  0x0000ff00
#define BCHP_SMARTCARD_PLL_ACTIVE_DIV1_M2DIV_SHIFT                 8

/* SMARTCARD_PLL :: ACTIVE_DIV1 :: M1DIV [07:00] */
#define BCHP_SMARTCARD_PLL_ACTIVE_DIV1_M1DIV_MASK                  0x000000ff
#define BCHP_SMARTCARD_PLL_ACTIVE_DIV1_M1DIV_SHIFT                 0

/***************************************************************************
 *ACTIVE_DIV2 - Smart Card PLL Active Divider Settings 2
 ***************************************************************************/
/* SMARTCARD_PLL :: ACTIVE_DIV2 :: reserved0 [31:17] */
#define BCHP_SMARTCARD_PLL_ACTIVE_DIV2_reserved0_MASK              0xfffe0000
#define BCHP_SMARTCARD_PLL_ACTIVE_DIV2_reserved0_SHIFT             17

/* SMARTCARD_PLL :: ACTIVE_DIV2 :: LOCK [16:16] */
#define BCHP_SMARTCARD_PLL_ACTIVE_DIV2_LOCK_MASK                   0x00010000
#define BCHP_SMARTCARD_PLL_ACTIVE_DIV2_LOCK_SHIFT                  16
#define BCHP_SMARTCARD_PLL_ACTIVE_DIV2_LOCK_Unlocked               0
#define BCHP_SMARTCARD_PLL_ACTIVE_DIV2_LOCK_Locked                 1

/* SMARTCARD_PLL :: ACTIVE_DIV2 :: reserved1 [15:14] */
#define BCHP_SMARTCARD_PLL_ACTIVE_DIV2_reserved1_MASK              0x0000c000
#define BCHP_SMARTCARD_PLL_ACTIVE_DIV2_reserved1_SHIFT             14

/* SMARTCARD_PLL :: ACTIVE_DIV2 :: VCORNG [13:12] */
#define BCHP_SMARTCARD_PLL_ACTIVE_DIV2_VCORNG_MASK                 0x00003000
#define BCHP_SMARTCARD_PLL_ACTIVE_DIV2_VCORNG_SHIFT                12

/* SMARTCARD_PLL :: ACTIVE_DIV2 :: reserved2 [11:09] */
#define BCHP_SMARTCARD_PLL_ACTIVE_DIV2_reserved2_MASK              0x00000e00
#define BCHP_SMARTCARD_PLL_ACTIVE_DIV2_reserved2_SHIFT             9

/* SMARTCARD_PLL :: ACTIVE_DIV2 :: NDIV_INT [08:00] */
#define BCHP_SMARTCARD_PLL_ACTIVE_DIV2_NDIV_INT_MASK               0x000001ff
#define BCHP_SMARTCARD_PLL_ACTIVE_DIV2_NDIV_INT_SHIFT              0

#endif /* #ifndef BCHP_SMARTCARD_PLL_H__ */

/* End of File */

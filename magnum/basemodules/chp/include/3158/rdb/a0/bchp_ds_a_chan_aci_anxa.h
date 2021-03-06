/****************************************************************************
 *     Copyright (c) 1999-2015, Broadcom Corporation
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
 * Date:           Generated on               Tue May 12 15:31:57 2015
 *                 Full Compile MD5 Checksum  654f5b1025c3f32e1ac79a0158cb9296
 *                     (minus title and desc)
 *                 MD5 Checksum               f5dfcaebcf2741b1de57e2e58f246be2
 *
 * Compiled with:  RDB Utility                combo_header.pl
 *                 RDB.pm                     16053
 *                 unknown                    unknown
 *                 Perl Interpreter           5.008008
 *                 Operating System           linux
 *                 Script Source              /home/pntruong/sbin/combo_header.pl
 *                 DVTSWVER                   n/a
 *
 *
 ***************************************************************************/

#ifndef BCHP_DS_A_CHAN_ACI_ANXA_H__
#define BCHP_DS_A_CHAN_ACI_ANXA_H__

/***************************************************************************
 *DS_A_CHAN_ACI_ANXA - Channel Isolation Processor ACI Filter Coefficients A Registers
 ***************************************************************************/
#define BCHP_DS_A_CHAN_ACI_ANXA_COEFFS_0         0x04310100 /* [CFG] Channel Isolation Processor Programmable ACI Filter Coefficient Register 0 */
#define BCHP_DS_A_CHAN_ACI_ANXA_COEFFS_1         0x04310104 /* [CFG] Channel Isolation Processor Programmable ACI Filter Coefficient Register 1 */
#define BCHP_DS_A_CHAN_ACI_ANXA_COEFFS_2         0x04310108 /* [CFG] Channel Isolation Processor Programmable ACI Filter Coefficient Register 2 */
#define BCHP_DS_A_CHAN_ACI_ANXA_COEFFS_3         0x0431010c /* [CFG] Channel Isolation Processor Programmable ACI Filter Coefficient Register 3 */
#define BCHP_DS_A_CHAN_ACI_ANXA_COEFFS_4         0x04310110 /* [CFG] Channel Isolation Processor Programmable ACI Filter Coefficient Register 4 */
#define BCHP_DS_A_CHAN_ACI_ANXA_COEFFS_5         0x04310114 /* [CFG] Channel Isolation Processor Programmable ACI Filter Coefficient Register 5 */
#define BCHP_DS_A_CHAN_ACI_ANXA_COEFFS_6         0x04310118 /* [CFG] Channel Isolation Processor Programmable ACI Filter Coefficient Register 6 */
#define BCHP_DS_A_CHAN_ACI_ANXA_COEFFS_7         0x0431011c /* [CFG] Channel Isolation Processor Programmable ACI Filter Coefficient Register 7 */
#define BCHP_DS_A_CHAN_ACI_ANXA_COEFFS_8         0x04310120 /* [CFG] Channel Isolation Processor Programmable ACI Filter Coefficient Register 8 */
#define BCHP_DS_A_CHAN_ACI_ANXA_COEFFS_9         0x04310124 /* [CFG] Channel Isolation Processor Programmable ACI Filter Coefficient Register 9 */
#define BCHP_DS_A_CHAN_ACI_ANXA_COEFFS_10        0x04310128 /* [CFG] Channel Isolation Processor Programmable ACI Filter Coefficient Register 10 */
#define BCHP_DS_A_CHAN_ACI_ANXA_COEFFS_11        0x0431012c /* [CFG] Channel Isolation Processor Programmable ACI Filter Coefficient Register 11 */
#define BCHP_DS_A_CHAN_ACI_ANXA_COEFFS_12        0x04310130 /* [CFG] Channel Isolation Processor Programmable ACI Filter Coefficient Register 12 */
#define BCHP_DS_A_CHAN_ACI_ANXA_COEFFS_13        0x04310134 /* [CFG] Channel Isolation Processor Programmable ACI Filter Coefficient Register 13 */
#define BCHP_DS_A_CHAN_ACI_ANXA_COEFFS_14        0x04310138 /* [CFG] Channel Isolation Processor Programmable ACI Filter Coefficient Register 14 */
#define BCHP_DS_A_CHAN_ACI_ANXA_COEFFS_15        0x0431013c /* [CFG] Channel Isolation Processor Programmable ACI Filter Coefficient Register 15 */
#define BCHP_DS_A_CHAN_ACI_ANXA_COEFFS_16        0x04310140 /* [CFG] Channel Isolation Processor Programmable ACI Filter Coefficient Register 16 */
#define BCHP_DS_A_CHAN_ACI_ANXA_COEFFS_17        0x04310144 /* [CFG] Channel Isolation Processor Programmable ACI Filter Coefficient Register 17 */

/***************************************************************************
 *COEFFS_0 - Channel Isolation Processor Programmable ACI Filter Coefficient Register 0
 ***************************************************************************/
/* DS_A_CHAN_ACI_ANXA :: COEFFS_0 :: ECO_SPARE_0 [31:16] */
#define BCHP_DS_A_CHAN_ACI_ANXA_COEFFS_0_ECO_SPARE_0_MASK          0xffff0000
#define BCHP_DS_A_CHAN_ACI_ANXA_COEFFS_0_ECO_SPARE_0_SHIFT         16
#define BCHP_DS_A_CHAN_ACI_ANXA_COEFFS_0_ECO_SPARE_0_DEFAULT       0x00000000

/* DS_A_CHAN_ACI_ANXA :: COEFFS_0 :: COEFFS [15:00] */
#define BCHP_DS_A_CHAN_ACI_ANXA_COEFFS_0_COEFFS_MASK               0x0000ffff
#define BCHP_DS_A_CHAN_ACI_ANXA_COEFFS_0_COEFFS_SHIFT              0
#define BCHP_DS_A_CHAN_ACI_ANXA_COEFFS_0_COEFFS_DEFAULT            0x00000000

/***************************************************************************
 *COEFFS_1 - Channel Isolation Processor Programmable ACI Filter Coefficient Register 1
 ***************************************************************************/
/* DS_A_CHAN_ACI_ANXA :: COEFFS_1 :: ECO_SPARE_0 [31:16] */
#define BCHP_DS_A_CHAN_ACI_ANXA_COEFFS_1_ECO_SPARE_0_MASK          0xffff0000
#define BCHP_DS_A_CHAN_ACI_ANXA_COEFFS_1_ECO_SPARE_0_SHIFT         16
#define BCHP_DS_A_CHAN_ACI_ANXA_COEFFS_1_ECO_SPARE_0_DEFAULT       0x00000000

/* DS_A_CHAN_ACI_ANXA :: COEFFS_1 :: COEFFS [15:00] */
#define BCHP_DS_A_CHAN_ACI_ANXA_COEFFS_1_COEFFS_MASK               0x0000ffff
#define BCHP_DS_A_CHAN_ACI_ANXA_COEFFS_1_COEFFS_SHIFT              0
#define BCHP_DS_A_CHAN_ACI_ANXA_COEFFS_1_COEFFS_DEFAULT            0x00000000

/***************************************************************************
 *COEFFS_2 - Channel Isolation Processor Programmable ACI Filter Coefficient Register 2
 ***************************************************************************/
/* DS_A_CHAN_ACI_ANXA :: COEFFS_2 :: ECO_SPARE_0 [31:16] */
#define BCHP_DS_A_CHAN_ACI_ANXA_COEFFS_2_ECO_SPARE_0_MASK          0xffff0000
#define BCHP_DS_A_CHAN_ACI_ANXA_COEFFS_2_ECO_SPARE_0_SHIFT         16
#define BCHP_DS_A_CHAN_ACI_ANXA_COEFFS_2_ECO_SPARE_0_DEFAULT       0x00000000

/* DS_A_CHAN_ACI_ANXA :: COEFFS_2 :: COEFFS [15:00] */
#define BCHP_DS_A_CHAN_ACI_ANXA_COEFFS_2_COEFFS_MASK               0x0000ffff
#define BCHP_DS_A_CHAN_ACI_ANXA_COEFFS_2_COEFFS_SHIFT              0
#define BCHP_DS_A_CHAN_ACI_ANXA_COEFFS_2_COEFFS_DEFAULT            0x00000000

/***************************************************************************
 *COEFFS_3 - Channel Isolation Processor Programmable ACI Filter Coefficient Register 3
 ***************************************************************************/
/* DS_A_CHAN_ACI_ANXA :: COEFFS_3 :: ECO_SPARE_0 [31:16] */
#define BCHP_DS_A_CHAN_ACI_ANXA_COEFFS_3_ECO_SPARE_0_MASK          0xffff0000
#define BCHP_DS_A_CHAN_ACI_ANXA_COEFFS_3_ECO_SPARE_0_SHIFT         16
#define BCHP_DS_A_CHAN_ACI_ANXA_COEFFS_3_ECO_SPARE_0_DEFAULT       0x00000000

/* DS_A_CHAN_ACI_ANXA :: COEFFS_3 :: COEFFS [15:00] */
#define BCHP_DS_A_CHAN_ACI_ANXA_COEFFS_3_COEFFS_MASK               0x0000ffff
#define BCHP_DS_A_CHAN_ACI_ANXA_COEFFS_3_COEFFS_SHIFT              0
#define BCHP_DS_A_CHAN_ACI_ANXA_COEFFS_3_COEFFS_DEFAULT            0x00000000

/***************************************************************************
 *COEFFS_4 - Channel Isolation Processor Programmable ACI Filter Coefficient Register 4
 ***************************************************************************/
/* DS_A_CHAN_ACI_ANXA :: COEFFS_4 :: ECO_SPARE_0 [31:16] */
#define BCHP_DS_A_CHAN_ACI_ANXA_COEFFS_4_ECO_SPARE_0_MASK          0xffff0000
#define BCHP_DS_A_CHAN_ACI_ANXA_COEFFS_4_ECO_SPARE_0_SHIFT         16
#define BCHP_DS_A_CHAN_ACI_ANXA_COEFFS_4_ECO_SPARE_0_DEFAULT       0x00000000

/* DS_A_CHAN_ACI_ANXA :: COEFFS_4 :: COEFFS [15:00] */
#define BCHP_DS_A_CHAN_ACI_ANXA_COEFFS_4_COEFFS_MASK               0x0000ffff
#define BCHP_DS_A_CHAN_ACI_ANXA_COEFFS_4_COEFFS_SHIFT              0
#define BCHP_DS_A_CHAN_ACI_ANXA_COEFFS_4_COEFFS_DEFAULT            0x00000000

/***************************************************************************
 *COEFFS_5 - Channel Isolation Processor Programmable ACI Filter Coefficient Register 5
 ***************************************************************************/
/* DS_A_CHAN_ACI_ANXA :: COEFFS_5 :: ECO_SPARE_0 [31:16] */
#define BCHP_DS_A_CHAN_ACI_ANXA_COEFFS_5_ECO_SPARE_0_MASK          0xffff0000
#define BCHP_DS_A_CHAN_ACI_ANXA_COEFFS_5_ECO_SPARE_0_SHIFT         16
#define BCHP_DS_A_CHAN_ACI_ANXA_COEFFS_5_ECO_SPARE_0_DEFAULT       0x00000000

/* DS_A_CHAN_ACI_ANXA :: COEFFS_5 :: COEFFS [15:00] */
#define BCHP_DS_A_CHAN_ACI_ANXA_COEFFS_5_COEFFS_MASK               0x0000ffff
#define BCHP_DS_A_CHAN_ACI_ANXA_COEFFS_5_COEFFS_SHIFT              0
#define BCHP_DS_A_CHAN_ACI_ANXA_COEFFS_5_COEFFS_DEFAULT            0x00000000

/***************************************************************************
 *COEFFS_6 - Channel Isolation Processor Programmable ACI Filter Coefficient Register 6
 ***************************************************************************/
/* DS_A_CHAN_ACI_ANXA :: COEFFS_6 :: ECO_SPARE_0 [31:16] */
#define BCHP_DS_A_CHAN_ACI_ANXA_COEFFS_6_ECO_SPARE_0_MASK          0xffff0000
#define BCHP_DS_A_CHAN_ACI_ANXA_COEFFS_6_ECO_SPARE_0_SHIFT         16
#define BCHP_DS_A_CHAN_ACI_ANXA_COEFFS_6_ECO_SPARE_0_DEFAULT       0x00000000

/* DS_A_CHAN_ACI_ANXA :: COEFFS_6 :: COEFFS [15:00] */
#define BCHP_DS_A_CHAN_ACI_ANXA_COEFFS_6_COEFFS_MASK               0x0000ffff
#define BCHP_DS_A_CHAN_ACI_ANXA_COEFFS_6_COEFFS_SHIFT              0
#define BCHP_DS_A_CHAN_ACI_ANXA_COEFFS_6_COEFFS_DEFAULT            0x00000000

/***************************************************************************
 *COEFFS_7 - Channel Isolation Processor Programmable ACI Filter Coefficient Register 7
 ***************************************************************************/
/* DS_A_CHAN_ACI_ANXA :: COEFFS_7 :: ECO_SPARE_0 [31:16] */
#define BCHP_DS_A_CHAN_ACI_ANXA_COEFFS_7_ECO_SPARE_0_MASK          0xffff0000
#define BCHP_DS_A_CHAN_ACI_ANXA_COEFFS_7_ECO_SPARE_0_SHIFT         16
#define BCHP_DS_A_CHAN_ACI_ANXA_COEFFS_7_ECO_SPARE_0_DEFAULT       0x00000000

/* DS_A_CHAN_ACI_ANXA :: COEFFS_7 :: COEFFS [15:00] */
#define BCHP_DS_A_CHAN_ACI_ANXA_COEFFS_7_COEFFS_MASK               0x0000ffff
#define BCHP_DS_A_CHAN_ACI_ANXA_COEFFS_7_COEFFS_SHIFT              0
#define BCHP_DS_A_CHAN_ACI_ANXA_COEFFS_7_COEFFS_DEFAULT            0x00000000

/***************************************************************************
 *COEFFS_8 - Channel Isolation Processor Programmable ACI Filter Coefficient Register 8
 ***************************************************************************/
/* DS_A_CHAN_ACI_ANXA :: COEFFS_8 :: ECO_SPARE_0 [31:16] */
#define BCHP_DS_A_CHAN_ACI_ANXA_COEFFS_8_ECO_SPARE_0_MASK          0xffff0000
#define BCHP_DS_A_CHAN_ACI_ANXA_COEFFS_8_ECO_SPARE_0_SHIFT         16
#define BCHP_DS_A_CHAN_ACI_ANXA_COEFFS_8_ECO_SPARE_0_DEFAULT       0x00000000

/* DS_A_CHAN_ACI_ANXA :: COEFFS_8 :: COEFFS [15:00] */
#define BCHP_DS_A_CHAN_ACI_ANXA_COEFFS_8_COEFFS_MASK               0x0000ffff
#define BCHP_DS_A_CHAN_ACI_ANXA_COEFFS_8_COEFFS_SHIFT              0
#define BCHP_DS_A_CHAN_ACI_ANXA_COEFFS_8_COEFFS_DEFAULT            0x00000000

/***************************************************************************
 *COEFFS_9 - Channel Isolation Processor Programmable ACI Filter Coefficient Register 9
 ***************************************************************************/
/* DS_A_CHAN_ACI_ANXA :: COEFFS_9 :: ECO_SPARE_0 [31:16] */
#define BCHP_DS_A_CHAN_ACI_ANXA_COEFFS_9_ECO_SPARE_0_MASK          0xffff0000
#define BCHP_DS_A_CHAN_ACI_ANXA_COEFFS_9_ECO_SPARE_0_SHIFT         16
#define BCHP_DS_A_CHAN_ACI_ANXA_COEFFS_9_ECO_SPARE_0_DEFAULT       0x00000000

/* DS_A_CHAN_ACI_ANXA :: COEFFS_9 :: COEFFS [15:00] */
#define BCHP_DS_A_CHAN_ACI_ANXA_COEFFS_9_COEFFS_MASK               0x0000ffff
#define BCHP_DS_A_CHAN_ACI_ANXA_COEFFS_9_COEFFS_SHIFT              0
#define BCHP_DS_A_CHAN_ACI_ANXA_COEFFS_9_COEFFS_DEFAULT            0x00000000

/***************************************************************************
 *COEFFS_10 - Channel Isolation Processor Programmable ACI Filter Coefficient Register 10
 ***************************************************************************/
/* DS_A_CHAN_ACI_ANXA :: COEFFS_10 :: ECO_SPARE_0 [31:16] */
#define BCHP_DS_A_CHAN_ACI_ANXA_COEFFS_10_ECO_SPARE_0_MASK         0xffff0000
#define BCHP_DS_A_CHAN_ACI_ANXA_COEFFS_10_ECO_SPARE_0_SHIFT        16
#define BCHP_DS_A_CHAN_ACI_ANXA_COEFFS_10_ECO_SPARE_0_DEFAULT      0x00000000

/* DS_A_CHAN_ACI_ANXA :: COEFFS_10 :: COEFFS [15:00] */
#define BCHP_DS_A_CHAN_ACI_ANXA_COEFFS_10_COEFFS_MASK              0x0000ffff
#define BCHP_DS_A_CHAN_ACI_ANXA_COEFFS_10_COEFFS_SHIFT             0
#define BCHP_DS_A_CHAN_ACI_ANXA_COEFFS_10_COEFFS_DEFAULT           0x00000000

/***************************************************************************
 *COEFFS_11 - Channel Isolation Processor Programmable ACI Filter Coefficient Register 11
 ***************************************************************************/
/* DS_A_CHAN_ACI_ANXA :: COEFFS_11 :: ECO_SPARE_0 [31:16] */
#define BCHP_DS_A_CHAN_ACI_ANXA_COEFFS_11_ECO_SPARE_0_MASK         0xffff0000
#define BCHP_DS_A_CHAN_ACI_ANXA_COEFFS_11_ECO_SPARE_0_SHIFT        16
#define BCHP_DS_A_CHAN_ACI_ANXA_COEFFS_11_ECO_SPARE_0_DEFAULT      0x00000000

/* DS_A_CHAN_ACI_ANXA :: COEFFS_11 :: COEFFS [15:00] */
#define BCHP_DS_A_CHAN_ACI_ANXA_COEFFS_11_COEFFS_MASK              0x0000ffff
#define BCHP_DS_A_CHAN_ACI_ANXA_COEFFS_11_COEFFS_SHIFT             0
#define BCHP_DS_A_CHAN_ACI_ANXA_COEFFS_11_COEFFS_DEFAULT           0x00000000

/***************************************************************************
 *COEFFS_12 - Channel Isolation Processor Programmable ACI Filter Coefficient Register 12
 ***************************************************************************/
/* DS_A_CHAN_ACI_ANXA :: COEFFS_12 :: ECO_SPARE_0 [31:16] */
#define BCHP_DS_A_CHAN_ACI_ANXA_COEFFS_12_ECO_SPARE_0_MASK         0xffff0000
#define BCHP_DS_A_CHAN_ACI_ANXA_COEFFS_12_ECO_SPARE_0_SHIFT        16
#define BCHP_DS_A_CHAN_ACI_ANXA_COEFFS_12_ECO_SPARE_0_DEFAULT      0x00000000

/* DS_A_CHAN_ACI_ANXA :: COEFFS_12 :: COEFFS [15:00] */
#define BCHP_DS_A_CHAN_ACI_ANXA_COEFFS_12_COEFFS_MASK              0x0000ffff
#define BCHP_DS_A_CHAN_ACI_ANXA_COEFFS_12_COEFFS_SHIFT             0
#define BCHP_DS_A_CHAN_ACI_ANXA_COEFFS_12_COEFFS_DEFAULT           0x00000000

/***************************************************************************
 *COEFFS_13 - Channel Isolation Processor Programmable ACI Filter Coefficient Register 13
 ***************************************************************************/
/* DS_A_CHAN_ACI_ANXA :: COEFFS_13 :: ECO_SPARE_0 [31:16] */
#define BCHP_DS_A_CHAN_ACI_ANXA_COEFFS_13_ECO_SPARE_0_MASK         0xffff0000
#define BCHP_DS_A_CHAN_ACI_ANXA_COEFFS_13_ECO_SPARE_0_SHIFT        16
#define BCHP_DS_A_CHAN_ACI_ANXA_COEFFS_13_ECO_SPARE_0_DEFAULT      0x00000000

/* DS_A_CHAN_ACI_ANXA :: COEFFS_13 :: COEFFS [15:00] */
#define BCHP_DS_A_CHAN_ACI_ANXA_COEFFS_13_COEFFS_MASK              0x0000ffff
#define BCHP_DS_A_CHAN_ACI_ANXA_COEFFS_13_COEFFS_SHIFT             0
#define BCHP_DS_A_CHAN_ACI_ANXA_COEFFS_13_COEFFS_DEFAULT           0x00000000

/***************************************************************************
 *COEFFS_14 - Channel Isolation Processor Programmable ACI Filter Coefficient Register 14
 ***************************************************************************/
/* DS_A_CHAN_ACI_ANXA :: COEFFS_14 :: ECO_SPARE_0 [31:16] */
#define BCHP_DS_A_CHAN_ACI_ANXA_COEFFS_14_ECO_SPARE_0_MASK         0xffff0000
#define BCHP_DS_A_CHAN_ACI_ANXA_COEFFS_14_ECO_SPARE_0_SHIFT        16
#define BCHP_DS_A_CHAN_ACI_ANXA_COEFFS_14_ECO_SPARE_0_DEFAULT      0x00000000

/* DS_A_CHAN_ACI_ANXA :: COEFFS_14 :: COEFFS [15:00] */
#define BCHP_DS_A_CHAN_ACI_ANXA_COEFFS_14_COEFFS_MASK              0x0000ffff
#define BCHP_DS_A_CHAN_ACI_ANXA_COEFFS_14_COEFFS_SHIFT             0
#define BCHP_DS_A_CHAN_ACI_ANXA_COEFFS_14_COEFFS_DEFAULT           0x00000000

/***************************************************************************
 *COEFFS_15 - Channel Isolation Processor Programmable ACI Filter Coefficient Register 15
 ***************************************************************************/
/* DS_A_CHAN_ACI_ANXA :: COEFFS_15 :: ECO_SPARE_0 [31:16] */
#define BCHP_DS_A_CHAN_ACI_ANXA_COEFFS_15_ECO_SPARE_0_MASK         0xffff0000
#define BCHP_DS_A_CHAN_ACI_ANXA_COEFFS_15_ECO_SPARE_0_SHIFT        16
#define BCHP_DS_A_CHAN_ACI_ANXA_COEFFS_15_ECO_SPARE_0_DEFAULT      0x00000000

/* DS_A_CHAN_ACI_ANXA :: COEFFS_15 :: COEFFS [15:00] */
#define BCHP_DS_A_CHAN_ACI_ANXA_COEFFS_15_COEFFS_MASK              0x0000ffff
#define BCHP_DS_A_CHAN_ACI_ANXA_COEFFS_15_COEFFS_SHIFT             0
#define BCHP_DS_A_CHAN_ACI_ANXA_COEFFS_15_COEFFS_DEFAULT           0x00000000

/***************************************************************************
 *COEFFS_16 - Channel Isolation Processor Programmable ACI Filter Coefficient Register 16
 ***************************************************************************/
/* DS_A_CHAN_ACI_ANXA :: COEFFS_16 :: ECO_SPARE_0 [31:16] */
#define BCHP_DS_A_CHAN_ACI_ANXA_COEFFS_16_ECO_SPARE_0_MASK         0xffff0000
#define BCHP_DS_A_CHAN_ACI_ANXA_COEFFS_16_ECO_SPARE_0_SHIFT        16
#define BCHP_DS_A_CHAN_ACI_ANXA_COEFFS_16_ECO_SPARE_0_DEFAULT      0x00000000

/* DS_A_CHAN_ACI_ANXA :: COEFFS_16 :: COEFFS [15:00] */
#define BCHP_DS_A_CHAN_ACI_ANXA_COEFFS_16_COEFFS_MASK              0x0000ffff
#define BCHP_DS_A_CHAN_ACI_ANXA_COEFFS_16_COEFFS_SHIFT             0
#define BCHP_DS_A_CHAN_ACI_ANXA_COEFFS_16_COEFFS_DEFAULT           0x00000000

/***************************************************************************
 *COEFFS_17 - Channel Isolation Processor Programmable ACI Filter Coefficient Register 17
 ***************************************************************************/
/* DS_A_CHAN_ACI_ANXA :: COEFFS_17 :: ECO_SPARE_0 [31:16] */
#define BCHP_DS_A_CHAN_ACI_ANXA_COEFFS_17_ECO_SPARE_0_MASK         0xffff0000
#define BCHP_DS_A_CHAN_ACI_ANXA_COEFFS_17_ECO_SPARE_0_SHIFT        16
#define BCHP_DS_A_CHAN_ACI_ANXA_COEFFS_17_ECO_SPARE_0_DEFAULT      0x00000000

/* DS_A_CHAN_ACI_ANXA :: COEFFS_17 :: COEFFS [15:00] */
#define BCHP_DS_A_CHAN_ACI_ANXA_COEFFS_17_COEFFS_MASK              0x0000ffff
#define BCHP_DS_A_CHAN_ACI_ANXA_COEFFS_17_COEFFS_SHIFT             0
#define BCHP_DS_A_CHAN_ACI_ANXA_COEFFS_17_COEFFS_DEFAULT           0x00000000

#endif /* #ifndef BCHP_DS_A_CHAN_ACI_ANXA_H__ */

/* End of File */

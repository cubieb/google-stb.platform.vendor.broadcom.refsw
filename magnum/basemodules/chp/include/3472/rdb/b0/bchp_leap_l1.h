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
 * Date:           Generated on         Wed Jan 16 10:32:29 2013
 *                 MD5 Checksum         d41d8cd98f00b204e9800998ecf8427e
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

#ifndef BCHP_LEAP_L1_H__
#define BCHP_LEAP_L1_H__

/***************************************************************************
 *LEAP_L1 - L1 Interrupt Controller Registers
 ***************************************************************************/
#define BCHP_LEAP_L1_INTR_STATUS                 0x00080200 /* Interrupt Status Register */
#define BCHP_LEAP_L1_INTR_MASK_STATUS            0x00080208 /* Interrupt Mask Status Register */
#define BCHP_LEAP_L1_INTR_MASK_SET               0x00080210 /* Interrupt Mask Set Register */
#define BCHP_LEAP_L1_INTR_MASK_CLEAR             0x00080218 /* Interrupt Mask Clear Register */

/***************************************************************************
 *INTR_STATUS - Interrupt Status Register
 ***************************************************************************/
/* LEAP_L1 :: INTR_STATUS :: reserved0 [31:08] */
#define BCHP_LEAP_L1_INTR_STATUS_reserved0_MASK                    0xffffff00
#define BCHP_LEAP_L1_INTR_STATUS_reserved0_SHIFT                   8

/* LEAP_L1 :: INTR_STATUS :: THD1_B_INTR [07:07] */
#define BCHP_LEAP_L1_INTR_STATUS_THD1_B_INTR_MASK                  0x00000080
#define BCHP_LEAP_L1_INTR_STATUS_THD1_B_INTR_SHIFT                 7
#define BCHP_LEAP_L1_INTR_STATUS_THD1_B_INTR_DEFAULT               0x00000000

/* LEAP_L1 :: INTR_STATUS :: THD1_A_INTR [06:06] */
#define BCHP_LEAP_L1_INTR_STATUS_THD1_A_INTR_MASK                  0x00000040
#define BCHP_LEAP_L1_INTR_STATUS_THD1_A_INTR_SHIFT                 6
#define BCHP_LEAP_L1_INTR_STATUS_THD1_A_INTR_DEFAULT               0x00000000

/* LEAP_L1 :: INTR_STATUS :: UFE1_INTR [05:05] */
#define BCHP_LEAP_L1_INTR_STATUS_UFE1_INTR_MASK                    0x00000020
#define BCHP_LEAP_L1_INTR_STATUS_UFE1_INTR_SHIFT                   5
#define BCHP_LEAP_L1_INTR_STATUS_UFE1_INTR_DEFAULT                 0x00000000

/* LEAP_L1 :: INTR_STATUS :: THD0_B_INTR [04:04] */
#define BCHP_LEAP_L1_INTR_STATUS_THD0_B_INTR_MASK                  0x00000010
#define BCHP_LEAP_L1_INTR_STATUS_THD0_B_INTR_SHIFT                 4
#define BCHP_LEAP_L1_INTR_STATUS_THD0_B_INTR_DEFAULT               0x00000000

/* LEAP_L1 :: INTR_STATUS :: THD0_A_INTR [03:03] */
#define BCHP_LEAP_L1_INTR_STATUS_THD0_A_INTR_MASK                  0x00000008
#define BCHP_LEAP_L1_INTR_STATUS_THD0_A_INTR_SHIFT                 3
#define BCHP_LEAP_L1_INTR_STATUS_THD0_A_INTR_DEFAULT               0x00000000

/* LEAP_L1 :: INTR_STATUS :: UFE0_INTR [02:02] */
#define BCHP_LEAP_L1_INTR_STATUS_UFE0_INTR_MASK                    0x00000004
#define BCHP_LEAP_L1_INTR_STATUS_UFE0_INTR_SHIFT                   2
#define BCHP_LEAP_L1_INTR_STATUS_UFE0_INTR_DEFAULT                 0x00000000

/* LEAP_L1 :: INTR_STATUS :: PERIPH_INTR [01:01] */
#define BCHP_LEAP_L1_INTR_STATUS_PERIPH_INTR_MASK                  0x00000002
#define BCHP_LEAP_L1_INTR_STATUS_PERIPH_INTR_SHIFT                 1
#define BCHP_LEAP_L1_INTR_STATUS_PERIPH_INTR_DEFAULT               0x00000000

/* LEAP_L1 :: INTR_STATUS :: LEAP_INTR [00:00] */
#define BCHP_LEAP_L1_INTR_STATUS_LEAP_INTR_MASK                    0x00000001
#define BCHP_LEAP_L1_INTR_STATUS_LEAP_INTR_SHIFT                   0
#define BCHP_LEAP_L1_INTR_STATUS_LEAP_INTR_DEFAULT                 0x00000000

/***************************************************************************
 *INTR_MASK_STATUS - Interrupt Mask Status Register
 ***************************************************************************/
/* LEAP_L1 :: INTR_MASK_STATUS :: reserved0 [31:08] */
#define BCHP_LEAP_L1_INTR_MASK_STATUS_reserved0_MASK               0xffffff00
#define BCHP_LEAP_L1_INTR_MASK_STATUS_reserved0_SHIFT              8

/* LEAP_L1 :: INTR_MASK_STATUS :: THD1_B_INTR [07:07] */
#define BCHP_LEAP_L1_INTR_MASK_STATUS_THD1_B_INTR_MASK             0x00000080
#define BCHP_LEAP_L1_INTR_MASK_STATUS_THD1_B_INTR_SHIFT            7
#define BCHP_LEAP_L1_INTR_MASK_STATUS_THD1_B_INTR_DEFAULT          0x00000001

/* LEAP_L1 :: INTR_MASK_STATUS :: THD1_A_INTR [06:06] */
#define BCHP_LEAP_L1_INTR_MASK_STATUS_THD1_A_INTR_MASK             0x00000040
#define BCHP_LEAP_L1_INTR_MASK_STATUS_THD1_A_INTR_SHIFT            6
#define BCHP_LEAP_L1_INTR_MASK_STATUS_THD1_A_INTR_DEFAULT          0x00000001

/* LEAP_L1 :: INTR_MASK_STATUS :: UFE1_INTR [05:05] */
#define BCHP_LEAP_L1_INTR_MASK_STATUS_UFE1_INTR_MASK               0x00000020
#define BCHP_LEAP_L1_INTR_MASK_STATUS_UFE1_INTR_SHIFT              5
#define BCHP_LEAP_L1_INTR_MASK_STATUS_UFE1_INTR_DEFAULT            0x00000001

/* LEAP_L1 :: INTR_MASK_STATUS :: THD0_B_INTR [04:04] */
#define BCHP_LEAP_L1_INTR_MASK_STATUS_THD0_B_INTR_MASK             0x00000010
#define BCHP_LEAP_L1_INTR_MASK_STATUS_THD0_B_INTR_SHIFT            4
#define BCHP_LEAP_L1_INTR_MASK_STATUS_THD0_B_INTR_DEFAULT          0x00000001

/* LEAP_L1 :: INTR_MASK_STATUS :: THD0_A_INTR [03:03] */
#define BCHP_LEAP_L1_INTR_MASK_STATUS_THD0_A_INTR_MASK             0x00000008
#define BCHP_LEAP_L1_INTR_MASK_STATUS_THD0_A_INTR_SHIFT            3
#define BCHP_LEAP_L1_INTR_MASK_STATUS_THD0_A_INTR_DEFAULT          0x00000001

/* LEAP_L1 :: INTR_MASK_STATUS :: UFE0_INTR [02:02] */
#define BCHP_LEAP_L1_INTR_MASK_STATUS_UFE0_INTR_MASK               0x00000004
#define BCHP_LEAP_L1_INTR_MASK_STATUS_UFE0_INTR_SHIFT              2
#define BCHP_LEAP_L1_INTR_MASK_STATUS_UFE0_INTR_DEFAULT            0x00000001

/* LEAP_L1 :: INTR_MASK_STATUS :: PERIPH_INTR [01:01] */
#define BCHP_LEAP_L1_INTR_MASK_STATUS_PERIPH_INTR_MASK             0x00000002
#define BCHP_LEAP_L1_INTR_MASK_STATUS_PERIPH_INTR_SHIFT            1
#define BCHP_LEAP_L1_INTR_MASK_STATUS_PERIPH_INTR_DEFAULT          0x00000001

/* LEAP_L1 :: INTR_MASK_STATUS :: LEAP_INTR [00:00] */
#define BCHP_LEAP_L1_INTR_MASK_STATUS_LEAP_INTR_MASK               0x00000001
#define BCHP_LEAP_L1_INTR_MASK_STATUS_LEAP_INTR_SHIFT              0
#define BCHP_LEAP_L1_INTR_MASK_STATUS_LEAP_INTR_DEFAULT            0x00000001

/***************************************************************************
 *INTR_MASK_SET - Interrupt Mask Set Register
 ***************************************************************************/
/* LEAP_L1 :: INTR_MASK_SET :: reserved0 [31:08] */
#define BCHP_LEAP_L1_INTR_MASK_SET_reserved0_MASK                  0xffffff00
#define BCHP_LEAP_L1_INTR_MASK_SET_reserved0_SHIFT                 8

/* LEAP_L1 :: INTR_MASK_SET :: THD1_B_INTR [07:07] */
#define BCHP_LEAP_L1_INTR_MASK_SET_THD1_B_INTR_MASK                0x00000080
#define BCHP_LEAP_L1_INTR_MASK_SET_THD1_B_INTR_SHIFT               7
#define BCHP_LEAP_L1_INTR_MASK_SET_THD1_B_INTR_DEFAULT             0x00000001

/* LEAP_L1 :: INTR_MASK_SET :: THD1_A_INTR [06:06] */
#define BCHP_LEAP_L1_INTR_MASK_SET_THD1_A_INTR_MASK                0x00000040
#define BCHP_LEAP_L1_INTR_MASK_SET_THD1_A_INTR_SHIFT               6
#define BCHP_LEAP_L1_INTR_MASK_SET_THD1_A_INTR_DEFAULT             0x00000001

/* LEAP_L1 :: INTR_MASK_SET :: UFE1_INTR [05:05] */
#define BCHP_LEAP_L1_INTR_MASK_SET_UFE1_INTR_MASK                  0x00000020
#define BCHP_LEAP_L1_INTR_MASK_SET_UFE1_INTR_SHIFT                 5
#define BCHP_LEAP_L1_INTR_MASK_SET_UFE1_INTR_DEFAULT               0x00000001

/* LEAP_L1 :: INTR_MASK_SET :: THD0_B_INTR [04:04] */
#define BCHP_LEAP_L1_INTR_MASK_SET_THD0_B_INTR_MASK                0x00000010
#define BCHP_LEAP_L1_INTR_MASK_SET_THD0_B_INTR_SHIFT               4
#define BCHP_LEAP_L1_INTR_MASK_SET_THD0_B_INTR_DEFAULT             0x00000001

/* LEAP_L1 :: INTR_MASK_SET :: THD0_A_INTR [03:03] */
#define BCHP_LEAP_L1_INTR_MASK_SET_THD0_A_INTR_MASK                0x00000008
#define BCHP_LEAP_L1_INTR_MASK_SET_THD0_A_INTR_SHIFT               3
#define BCHP_LEAP_L1_INTR_MASK_SET_THD0_A_INTR_DEFAULT             0x00000001

/* LEAP_L1 :: INTR_MASK_SET :: UFE0_INTR [02:02] */
#define BCHP_LEAP_L1_INTR_MASK_SET_UFE0_INTR_MASK                  0x00000004
#define BCHP_LEAP_L1_INTR_MASK_SET_UFE0_INTR_SHIFT                 2
#define BCHP_LEAP_L1_INTR_MASK_SET_UFE0_INTR_DEFAULT               0x00000001

/* LEAP_L1 :: INTR_MASK_SET :: PERIPH_INTR [01:01] */
#define BCHP_LEAP_L1_INTR_MASK_SET_PERIPH_INTR_MASK                0x00000002
#define BCHP_LEAP_L1_INTR_MASK_SET_PERIPH_INTR_SHIFT               1
#define BCHP_LEAP_L1_INTR_MASK_SET_PERIPH_INTR_DEFAULT             0x00000001

/* LEAP_L1 :: INTR_MASK_SET :: LEAP_INTR [00:00] */
#define BCHP_LEAP_L1_INTR_MASK_SET_LEAP_INTR_MASK                  0x00000001
#define BCHP_LEAP_L1_INTR_MASK_SET_LEAP_INTR_SHIFT                 0
#define BCHP_LEAP_L1_INTR_MASK_SET_LEAP_INTR_DEFAULT               0x00000001

/***************************************************************************
 *INTR_MASK_CLEAR - Interrupt Mask Clear Register
 ***************************************************************************/
/* LEAP_L1 :: INTR_MASK_CLEAR :: reserved0 [31:08] */
#define BCHP_LEAP_L1_INTR_MASK_CLEAR_reserved0_MASK                0xffffff00
#define BCHP_LEAP_L1_INTR_MASK_CLEAR_reserved0_SHIFT               8

/* LEAP_L1 :: INTR_MASK_CLEAR :: THD1_B_INTR [07:07] */
#define BCHP_LEAP_L1_INTR_MASK_CLEAR_THD1_B_INTR_MASK              0x00000080
#define BCHP_LEAP_L1_INTR_MASK_CLEAR_THD1_B_INTR_SHIFT             7
#define BCHP_LEAP_L1_INTR_MASK_CLEAR_THD1_B_INTR_DEFAULT           0x00000001

/* LEAP_L1 :: INTR_MASK_CLEAR :: THD1_A_INTR [06:06] */
#define BCHP_LEAP_L1_INTR_MASK_CLEAR_THD1_A_INTR_MASK              0x00000040
#define BCHP_LEAP_L1_INTR_MASK_CLEAR_THD1_A_INTR_SHIFT             6
#define BCHP_LEAP_L1_INTR_MASK_CLEAR_THD1_A_INTR_DEFAULT           0x00000001

/* LEAP_L1 :: INTR_MASK_CLEAR :: UFE1_INTR [05:05] */
#define BCHP_LEAP_L1_INTR_MASK_CLEAR_UFE1_INTR_MASK                0x00000020
#define BCHP_LEAP_L1_INTR_MASK_CLEAR_UFE1_INTR_SHIFT               5
#define BCHP_LEAP_L1_INTR_MASK_CLEAR_UFE1_INTR_DEFAULT             0x00000001

/* LEAP_L1 :: INTR_MASK_CLEAR :: THD0_B_INTR [04:04] */
#define BCHP_LEAP_L1_INTR_MASK_CLEAR_THD0_B_INTR_MASK              0x00000010
#define BCHP_LEAP_L1_INTR_MASK_CLEAR_THD0_B_INTR_SHIFT             4
#define BCHP_LEAP_L1_INTR_MASK_CLEAR_THD0_B_INTR_DEFAULT           0x00000001

/* LEAP_L1 :: INTR_MASK_CLEAR :: THD0_A_INTR [03:03] */
#define BCHP_LEAP_L1_INTR_MASK_CLEAR_THD0_A_INTR_MASK              0x00000008
#define BCHP_LEAP_L1_INTR_MASK_CLEAR_THD0_A_INTR_SHIFT             3
#define BCHP_LEAP_L1_INTR_MASK_CLEAR_THD0_A_INTR_DEFAULT           0x00000001

/* LEAP_L1 :: INTR_MASK_CLEAR :: UFE0_INTR [02:02] */
#define BCHP_LEAP_L1_INTR_MASK_CLEAR_UFE0_INTR_MASK                0x00000004
#define BCHP_LEAP_L1_INTR_MASK_CLEAR_UFE0_INTR_SHIFT               2
#define BCHP_LEAP_L1_INTR_MASK_CLEAR_UFE0_INTR_DEFAULT             0x00000001

/* LEAP_L1 :: INTR_MASK_CLEAR :: PERIPH_INTR [01:01] */
#define BCHP_LEAP_L1_INTR_MASK_CLEAR_PERIPH_INTR_MASK              0x00000002
#define BCHP_LEAP_L1_INTR_MASK_CLEAR_PERIPH_INTR_SHIFT             1
#define BCHP_LEAP_L1_INTR_MASK_CLEAR_PERIPH_INTR_DEFAULT           0x00000001

/* LEAP_L1 :: INTR_MASK_CLEAR :: LEAP_INTR [00:00] */
#define BCHP_LEAP_L1_INTR_MASK_CLEAR_LEAP_INTR_MASK                0x00000001
#define BCHP_LEAP_L1_INTR_MASK_CLEAR_LEAP_INTR_SHIFT               0
#define BCHP_LEAP_L1_INTR_MASK_CLEAR_LEAP_INTR_DEFAULT             0x00000001

#endif /* #ifndef BCHP_LEAP_L1_H__ */

/* End of File */

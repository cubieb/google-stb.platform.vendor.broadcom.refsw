/***************************************************************************
 *     Copyright (c) 1999-2007, Broadcom Corporation
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
 * Date:           Generated on         Mon Jul 23 11:58:16 2007
 *                 MD5 Checksum         61f9c4d8dcdcd06017506dddbf23f434
 *
 * Compiled with:  RDB Utility          combo_header.pl
 *                 RDB Parser           3.0
 *                 unknown              unknown
 *                 Perl Interpreter     5.008004
 *                 Operating System     linux
 *
 * Revision History:
 *
 * $brcm_Log: $
 * 
 ***************************************************************************/

#ifndef BCHP_SEC_RM_H__
#define BCHP_SEC_RM_H__

/***************************************************************************
 *SEC_RM - Secondary Rate Manger
 ***************************************************************************/
#define BCHP_SEC_RM_CONTROL                      0x001805c0 /* Rate Manager Controls */
#define BCHP_SEC_RM_RATE_RATIO                   0x001805c4 /* Rate Manager Output Rate Setting I */
#define BCHP_SEC_RM_SAMPLE_INC                   0x001805c8 /* Rate Manager Output Rate Setting II */
#define BCHP_SEC_RM_PHASE_INC                    0x001805cc /* Rate Manager NCO Phase Increment */
#define BCHP_SEC_RM_INTEGRATOR                   0x001805d0 /* Loop Filter Integrator Value */

/***************************************************************************
 *CONTROL - Rate Manager Controls
 ***************************************************************************/
/* SEC_RM :: CONTROL :: reserved0 [31:11] */
#define BCHP_SEC_RM_CONTROL_reserved0_MASK                         0xfffff800
#define BCHP_SEC_RM_CONTROL_reserved0_SHIFT                        11

/* SEC_RM :: CONTROL :: RESET [10:10] */
#define BCHP_SEC_RM_CONTROL_RESET_MASK                             0x00000400
#define BCHP_SEC_RM_CONTROL_RESET_SHIFT                            10
#define BCHP_SEC_RM_CONTROL_RESET_RESET_ON                         1
#define BCHP_SEC_RM_CONTROL_RESET_RESET_OFF                        0

/* SEC_RM :: CONTROL :: INT_GAIN [09:07] */
#define BCHP_SEC_RM_CONTROL_INT_GAIN_MASK                          0x00000380
#define BCHP_SEC_RM_CONTROL_INT_GAIN_SHIFT                         7

/* SEC_RM :: CONTROL :: DIRECT_GAIN [06:04] */
#define BCHP_SEC_RM_CONTROL_DIRECT_GAIN_MASK                       0x00000070
#define BCHP_SEC_RM_CONTROL_DIRECT_GAIN_SHIFT                      4

/* SEC_RM :: CONTROL :: DITHER [03:03] */
#define BCHP_SEC_RM_CONTROL_DITHER_MASK                            0x00000008
#define BCHP_SEC_RM_CONTROL_DITHER_SHIFT                           3
#define BCHP_SEC_RM_CONTROL_DITHER_DITHER_ON                       1
#define BCHP_SEC_RM_CONTROL_DITHER_DITHER_OFF                      0

/* SEC_RM :: CONTROL :: FREE_RUN [02:02] */
#define BCHP_SEC_RM_CONTROL_FREE_RUN_MASK                          0x00000004
#define BCHP_SEC_RM_CONTROL_FREE_RUN_SHIFT                         2
#define BCHP_SEC_RM_CONTROL_FREE_RUN_FREE_RUN_ON                   1
#define BCHP_SEC_RM_CONTROL_FREE_RUN_TIMEBASE                      0

/* SEC_RM :: CONTROL :: TIMEBASE [01:00] */
#define BCHP_SEC_RM_CONTROL_TIMEBASE_MASK                          0x00000003
#define BCHP_SEC_RM_CONTROL_TIMEBASE_SHIFT                         0
#define BCHP_SEC_RM_CONTROL_TIMEBASE_TIMEBASE_3                    3
#define BCHP_SEC_RM_CONTROL_TIMEBASE_TIMEBASE_2                    2
#define BCHP_SEC_RM_CONTROL_TIMEBASE_TIMEBASE_1                    1
#define BCHP_SEC_RM_CONTROL_TIMEBASE_TIMEBASE_0                    0

/***************************************************************************
 *RATE_RATIO - Rate Manager Output Rate Setting I
 ***************************************************************************/
/* SEC_RM :: RATE_RATIO :: MAX_ERR [31:24] */
#define BCHP_SEC_RM_RATE_RATIO_MAX_ERR_MASK                        0xff000000
#define BCHP_SEC_RM_RATE_RATIO_MAX_ERR_SHIFT                       24

/* SEC_RM :: RATE_RATIO :: MIN_ERR [23:16] */
#define BCHP_SEC_RM_RATE_RATIO_MIN_ERR_MASK                        0x00ff0000
#define BCHP_SEC_RM_RATE_RATIO_MIN_ERR_SHIFT                       16

/* SEC_RM :: RATE_RATIO :: DENOMINATOR [15:00] */
#define BCHP_SEC_RM_RATE_RATIO_DENOMINATOR_MASK                    0x0000ffff
#define BCHP_SEC_RM_RATE_RATIO_DENOMINATOR_SHIFT                   0

/***************************************************************************
 *SAMPLE_INC - Rate Manager Output Rate Setting II
 ***************************************************************************/
/* SEC_RM :: SAMPLE_INC :: NUMERATOR [31:16] */
#define BCHP_SEC_RM_SAMPLE_INC_NUMERATOR_MASK                      0xffff0000
#define BCHP_SEC_RM_SAMPLE_INC_NUMERATOR_SHIFT                     16

/* SEC_RM :: SAMPLE_INC :: reserved0 [15:08] */
#define BCHP_SEC_RM_SAMPLE_INC_reserved0_MASK                      0x0000ff00
#define BCHP_SEC_RM_SAMPLE_INC_reserved0_SHIFT                     8

/* SEC_RM :: SAMPLE_INC :: SAMPLE_INC [07:00] */
#define BCHP_SEC_RM_SAMPLE_INC_SAMPLE_INC_MASK                     0x000000ff
#define BCHP_SEC_RM_SAMPLE_INC_SAMPLE_INC_SHIFT                    0

/***************************************************************************
 *PHASE_INC - Rate Manager NCO Phase Increment
 ***************************************************************************/
/* SEC_RM :: PHASE_INC :: reserved0 [31:24] */
#define BCHP_SEC_RM_PHASE_INC_reserved0_MASK                       0xff000000
#define BCHP_SEC_RM_PHASE_INC_reserved0_SHIFT                      24

/* SEC_RM :: PHASE_INC :: PHASE_INC [23:00] */
#define BCHP_SEC_RM_PHASE_INC_PHASE_INC_MASK                       0x00ffffff
#define BCHP_SEC_RM_PHASE_INC_PHASE_INC_SHIFT                      0

/***************************************************************************
 *INTEGRATOR - Loop Filter Integrator Value
 ***************************************************************************/
/* SEC_RM :: INTEGRATOR :: INTEGRATOR [31:00] */
#define BCHP_SEC_RM_INTEGRATOR_INTEGRATOR_MASK                     0xffffffff
#define BCHP_SEC_RM_INTEGRATOR_INTEGRATOR_SHIFT                    0

#endif /* #ifndef BCHP_SEC_RM_H__ */

/* End of File */

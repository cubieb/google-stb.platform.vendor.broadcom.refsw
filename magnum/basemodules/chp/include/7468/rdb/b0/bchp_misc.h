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
 * Date:           Generated on         Fri May  7 20:15:54 2010
 *                 MD5 Checksum         9170aeef162fecc7d1a70fbd8134c303
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

#ifndef BCHP_MISC_H__
#define BCHP_MISC_H__

/***************************************************************************
 *MISC - VEC Registers
 ***************************************************************************/
#define BCHP_MISC_MISC_REVISION_ID               0x00480000 /* Revision ID Register */
#define BCHP_MISC_DAC_0_CFG                      0x00480004 /* Config register for DAC_0 */
#define BCHP_MISC_DAC_1_CFG                      0x00480008 /* Config register for DAC_1 */
#define BCHP_MISC_DAC_2_CFG                      0x0048000c /* Config register for DAC_2 */
#define BCHP_MISC_DAC_3_CFG                      0x00480010 /* Config register for DAC_3 */
#define BCHP_MISC_SYNC_0_CFG                     0x00480014 /* Config Register for Sync Port 0 */
#define BCHP_MISC_IT_0_MASTER_SEL                0x00480018 /* Master Select for IT_0 */
#define BCHP_MISC_IT_1_MASTER_SEL                0x0048001c /* Master Select for IT_1 */
#define BCHP_MISC_DVI_DTG_0_MASTER_SEL           0x00480020 /* Master Select for DVI DTG_0 */
#define BCHP_MISC_DVI_0_SA_CONFIG                0x00480024 /* SA config for DVI 0 */
#define BCHP_MISC_DVI_0_SA_CH0_STATUS            0x00480028 /* SA status for channel 0 for DVI 0 */
#define BCHP_MISC_DVI_0_SA_CH1_STATUS            0x0048002c /* SA status for channel 1 for DVI 0 */
#define BCHP_MISC_DVI_0_SA_CH2_STATUS            0x00480030 /* SA status for channel 2 for DVI 0 */
#define BCHP_MISC_DAC_BG_CTRL_0                  0x00480034 /* DAC Bandgap Control Register */
#define BCHP_MISC_DAC_0_CTRL                     0x00480038 /* DAC_0 Control Register */
#define BCHP_MISC_DAC_1_CTRL                     0x0048003c /* DAC_1 Control Register */
#define BCHP_MISC_DAC_2_CTRL                     0x00480040 /* DAC_2 Control Register */
#define BCHP_MISC_DAC_3_CTRL                     0x00480044 /* DAC_3 Control Register */

/***************************************************************************
 *MISC_REVISION_ID - Revision ID Register
 ***************************************************************************/
/* MISC :: MISC_REVISION_ID :: reserved0 [31:16] */
#define BCHP_MISC_MISC_REVISION_ID_reserved0_MASK                  0xffff0000
#define BCHP_MISC_MISC_REVISION_ID_reserved0_SHIFT                 16

/* MISC :: MISC_REVISION_ID :: REVISION_ID [15:00] */
#define BCHP_MISC_MISC_REVISION_ID_REVISION_ID_MASK                0x0000ffff
#define BCHP_MISC_MISC_REVISION_ID_REVISION_ID_SHIFT               0

/***************************************************************************
 *DAC_0_CFG - Config register for DAC_0
 ***************************************************************************/
/* MISC :: DAC_0_CFG :: reserved0 [31:26] */
#define BCHP_MISC_DAC_0_CFG_reserved0_MASK                         0xfc000000
#define BCHP_MISC_DAC_0_CFG_reserved0_SHIFT                        26

/* MISC :: DAC_0_CFG :: CONST [25:16] */
#define BCHP_MISC_DAC_0_CFG_CONST_MASK                             0x03ff0000
#define BCHP_MISC_DAC_0_CFG_CONST_SHIFT                            16

/* MISC :: DAC_0_CFG :: reserved1 [15:13] */
#define BCHP_MISC_DAC_0_CFG_reserved1_MASK                         0x0000e000
#define BCHP_MISC_DAC_0_CFG_reserved1_SHIFT                        13

/* MISC :: DAC_0_CFG :: SINC [12:12] */
#define BCHP_MISC_DAC_0_CFG_SINC_MASK                              0x00001000
#define BCHP_MISC_DAC_0_CFG_SINC_SHIFT                             12
#define BCHP_MISC_DAC_0_CFG_SINC_ON                                1
#define BCHP_MISC_DAC_0_CFG_SINC_OFF                               0

/* MISC :: DAC_0_CFG :: DELAY [11:08] */
#define BCHP_MISC_DAC_0_CFG_DELAY_MASK                             0x00000f00
#define BCHP_MISC_DAC_0_CFG_DELAY_SHIFT                            8

/* MISC :: DAC_0_CFG :: SEL [07:00] */
#define BCHP_MISC_DAC_0_CFG_SEL_MASK                               0x000000ff
#define BCHP_MISC_DAC_0_CFG_SEL_SHIFT                              0
#define BCHP_MISC_DAC_0_CFG_SEL_SDSRC_0_CH0                        0
#define BCHP_MISC_DAC_0_CFG_SEL_SDSRC_0_CH1                        1
#define BCHP_MISC_DAC_0_CFG_SEL_SDSRC_0_CH2                        2
#define BCHP_MISC_DAC_0_CFG_SEL_HDSRC_0_CH0                        3
#define BCHP_MISC_DAC_0_CFG_SEL_HDSRC_0_CH1                        4
#define BCHP_MISC_DAC_0_CFG_SEL_HDSRC_0_CH2                        5
#define BCHP_MISC_DAC_0_CFG_SEL_HDSRC_0_HSYNC                      6
#define BCHP_MISC_DAC_0_CFG_SEL_CONST                              7

/***************************************************************************
 *DAC_1_CFG - Config register for DAC_1
 ***************************************************************************/
/* MISC :: DAC_1_CFG :: reserved0 [31:26] */
#define BCHP_MISC_DAC_1_CFG_reserved0_MASK                         0xfc000000
#define BCHP_MISC_DAC_1_CFG_reserved0_SHIFT                        26

/* MISC :: DAC_1_CFG :: CONST [25:16] */
#define BCHP_MISC_DAC_1_CFG_CONST_MASK                             0x03ff0000
#define BCHP_MISC_DAC_1_CFG_CONST_SHIFT                            16

/* MISC :: DAC_1_CFG :: reserved1 [15:13] */
#define BCHP_MISC_DAC_1_CFG_reserved1_MASK                         0x0000e000
#define BCHP_MISC_DAC_1_CFG_reserved1_SHIFT                        13

/* MISC :: DAC_1_CFG :: SINC [12:12] */
#define BCHP_MISC_DAC_1_CFG_SINC_MASK                              0x00001000
#define BCHP_MISC_DAC_1_CFG_SINC_SHIFT                             12
#define BCHP_MISC_DAC_1_CFG_SINC_ON                                1
#define BCHP_MISC_DAC_1_CFG_SINC_OFF                               0

/* MISC :: DAC_1_CFG :: DELAY [11:08] */
#define BCHP_MISC_DAC_1_CFG_DELAY_MASK                             0x00000f00
#define BCHP_MISC_DAC_1_CFG_DELAY_SHIFT                            8

/* MISC :: DAC_1_CFG :: SEL [07:00] */
#define BCHP_MISC_DAC_1_CFG_SEL_MASK                               0x000000ff
#define BCHP_MISC_DAC_1_CFG_SEL_SHIFT                              0
#define BCHP_MISC_DAC_1_CFG_SEL_SDSRC_0_CH0                        0
#define BCHP_MISC_DAC_1_CFG_SEL_SDSRC_0_CH1                        1
#define BCHP_MISC_DAC_1_CFG_SEL_SDSRC_0_CH2                        2
#define BCHP_MISC_DAC_1_CFG_SEL_HDSRC_0_CH0                        3
#define BCHP_MISC_DAC_1_CFG_SEL_HDSRC_0_CH1                        4
#define BCHP_MISC_DAC_1_CFG_SEL_HDSRC_0_CH2                        5
#define BCHP_MISC_DAC_1_CFG_SEL_HDSRC_0_HSYNC                      6
#define BCHP_MISC_DAC_1_CFG_SEL_CONST                              7

/***************************************************************************
 *DAC_2_CFG - Config register for DAC_2
 ***************************************************************************/
/* MISC :: DAC_2_CFG :: reserved0 [31:26] */
#define BCHP_MISC_DAC_2_CFG_reserved0_MASK                         0xfc000000
#define BCHP_MISC_DAC_2_CFG_reserved0_SHIFT                        26

/* MISC :: DAC_2_CFG :: CONST [25:16] */
#define BCHP_MISC_DAC_2_CFG_CONST_MASK                             0x03ff0000
#define BCHP_MISC_DAC_2_CFG_CONST_SHIFT                            16

/* MISC :: DAC_2_CFG :: reserved1 [15:13] */
#define BCHP_MISC_DAC_2_CFG_reserved1_MASK                         0x0000e000
#define BCHP_MISC_DAC_2_CFG_reserved1_SHIFT                        13

/* MISC :: DAC_2_CFG :: SINC [12:12] */
#define BCHP_MISC_DAC_2_CFG_SINC_MASK                              0x00001000
#define BCHP_MISC_DAC_2_CFG_SINC_SHIFT                             12
#define BCHP_MISC_DAC_2_CFG_SINC_ON                                1
#define BCHP_MISC_DAC_2_CFG_SINC_OFF                               0

/* MISC :: DAC_2_CFG :: DELAY [11:08] */
#define BCHP_MISC_DAC_2_CFG_DELAY_MASK                             0x00000f00
#define BCHP_MISC_DAC_2_CFG_DELAY_SHIFT                            8

/* MISC :: DAC_2_CFG :: SEL [07:00] */
#define BCHP_MISC_DAC_2_CFG_SEL_MASK                               0x000000ff
#define BCHP_MISC_DAC_2_CFG_SEL_SHIFT                              0
#define BCHP_MISC_DAC_2_CFG_SEL_SDSRC_0_CH0                        0
#define BCHP_MISC_DAC_2_CFG_SEL_SDSRC_0_CH1                        1
#define BCHP_MISC_DAC_2_CFG_SEL_SDSRC_0_CH2                        2
#define BCHP_MISC_DAC_2_CFG_SEL_HDSRC_0_CH0                        3
#define BCHP_MISC_DAC_2_CFG_SEL_HDSRC_0_CH1                        4
#define BCHP_MISC_DAC_2_CFG_SEL_HDSRC_0_CH2                        5
#define BCHP_MISC_DAC_2_CFG_SEL_HDSRC_0_HSYNC                      6
#define BCHP_MISC_DAC_2_CFG_SEL_CONST                              7

/***************************************************************************
 *DAC_3_CFG - Config register for DAC_3
 ***************************************************************************/
/* MISC :: DAC_3_CFG :: reserved0 [31:26] */
#define BCHP_MISC_DAC_3_CFG_reserved0_MASK                         0xfc000000
#define BCHP_MISC_DAC_3_CFG_reserved0_SHIFT                        26

/* MISC :: DAC_3_CFG :: CONST [25:16] */
#define BCHP_MISC_DAC_3_CFG_CONST_MASK                             0x03ff0000
#define BCHP_MISC_DAC_3_CFG_CONST_SHIFT                            16

/* MISC :: DAC_3_CFG :: reserved1 [15:13] */
#define BCHP_MISC_DAC_3_CFG_reserved1_MASK                         0x0000e000
#define BCHP_MISC_DAC_3_CFG_reserved1_SHIFT                        13

/* MISC :: DAC_3_CFG :: SINC [12:12] */
#define BCHP_MISC_DAC_3_CFG_SINC_MASK                              0x00001000
#define BCHP_MISC_DAC_3_CFG_SINC_SHIFT                             12
#define BCHP_MISC_DAC_3_CFG_SINC_ON                                1
#define BCHP_MISC_DAC_3_CFG_SINC_OFF                               0

/* MISC :: DAC_3_CFG :: DELAY [11:08] */
#define BCHP_MISC_DAC_3_CFG_DELAY_MASK                             0x00000f00
#define BCHP_MISC_DAC_3_CFG_DELAY_SHIFT                            8

/* MISC :: DAC_3_CFG :: SEL [07:00] */
#define BCHP_MISC_DAC_3_CFG_SEL_MASK                               0x000000ff
#define BCHP_MISC_DAC_3_CFG_SEL_SHIFT                              0
#define BCHP_MISC_DAC_3_CFG_SEL_SDSRC_0_CH0                        0
#define BCHP_MISC_DAC_3_CFG_SEL_SDSRC_0_CH1                        1
#define BCHP_MISC_DAC_3_CFG_SEL_SDSRC_0_CH2                        2
#define BCHP_MISC_DAC_3_CFG_SEL_HDSRC_0_CH0                        3
#define BCHP_MISC_DAC_3_CFG_SEL_HDSRC_0_CH1                        4
#define BCHP_MISC_DAC_3_CFG_SEL_HDSRC_0_CH2                        5
#define BCHP_MISC_DAC_3_CFG_SEL_HDSRC_0_HSYNC                      6
#define BCHP_MISC_DAC_3_CFG_SEL_CONST                              7

/***************************************************************************
 *SYNC_0_CFG - Config Register for Sync Port 0
 ***************************************************************************/
/* MISC :: SYNC_0_CFG :: reserved0 [31:16] */
#define BCHP_MISC_SYNC_0_CFG_reserved0_MASK                        0xffff0000
#define BCHP_MISC_SYNC_0_CFG_reserved0_SHIFT                       16

/* MISC :: SYNC_0_CFG :: VS_DELAY [15:12] */
#define BCHP_MISC_SYNC_0_CFG_VS_DELAY_MASK                         0x0000f000
#define BCHP_MISC_SYNC_0_CFG_VS_DELAY_SHIFT                        12

/* MISC :: SYNC_0_CFG :: HS_DELAY [11:08] */
#define BCHP_MISC_SYNC_0_CFG_HS_DELAY_MASK                         0x00000f00
#define BCHP_MISC_SYNC_0_CFG_HS_DELAY_SHIFT                        8

/* MISC :: SYNC_0_CFG :: SEL [07:00] */
#define BCHP_MISC_SYNC_0_CFG_SEL_MASK                              0x000000ff
#define BCHP_MISC_SYNC_0_CFG_SEL_SHIFT                             0
#define BCHP_MISC_SYNC_0_CFG_SEL_SDSRC_0                           0

/***************************************************************************
 *IT_0_MASTER_SEL - Master Select for IT_0
 ***************************************************************************/
/* MISC :: IT_0_MASTER_SEL :: reserved0 [31:02] */
#define BCHP_MISC_IT_0_MASTER_SEL_reserved0_MASK                   0xfffffffc
#define BCHP_MISC_IT_0_MASTER_SEL_reserved0_SHIFT                  2

/* MISC :: IT_0_MASTER_SEL :: SELECT [01:00] */
#define BCHP_MISC_IT_0_MASTER_SEL_SELECT_MASK                      0x00000003
#define BCHP_MISC_IT_0_MASTER_SEL_SELECT_SHIFT                     0
#define BCHP_MISC_IT_0_MASTER_SEL_SELECT_IT_0                      0
#define BCHP_MISC_IT_0_MASTER_SEL_SELECT_IT_1                      1
#define BCHP_MISC_IT_0_MASTER_SEL_SELECT_DVI_DTG_0                 2

/***************************************************************************
 *IT_1_MASTER_SEL - Master Select for IT_1
 ***************************************************************************/
/* MISC :: IT_1_MASTER_SEL :: reserved0 [31:02] */
#define BCHP_MISC_IT_1_MASTER_SEL_reserved0_MASK                   0xfffffffc
#define BCHP_MISC_IT_1_MASTER_SEL_reserved0_SHIFT                  2

/* MISC :: IT_1_MASTER_SEL :: SELECT [01:00] */
#define BCHP_MISC_IT_1_MASTER_SEL_SELECT_MASK                      0x00000003
#define BCHP_MISC_IT_1_MASTER_SEL_SELECT_SHIFT                     0
#define BCHP_MISC_IT_1_MASTER_SEL_SELECT_IT_0                      0
#define BCHP_MISC_IT_1_MASTER_SEL_SELECT_IT_1                      1
#define BCHP_MISC_IT_1_MASTER_SEL_SELECT_DVI_DTG_0                 2

/***************************************************************************
 *DVI_DTG_0_MASTER_SEL - Master Select for DVI DTG_0
 ***************************************************************************/
/* MISC :: DVI_DTG_0_MASTER_SEL :: reserved0 [31:03] */
#define BCHP_MISC_DVI_DTG_0_MASTER_SEL_reserved0_MASK              0xfffffff8
#define BCHP_MISC_DVI_DTG_0_MASTER_SEL_reserved0_SHIFT             3

/* MISC :: DVI_DTG_0_MASTER_SEL :: FREERUN [02:02] */
#define BCHP_MISC_DVI_DTG_0_MASTER_SEL_FREERUN_MASK                0x00000004
#define BCHP_MISC_DVI_DTG_0_MASTER_SEL_FREERUN_SHIFT               2

/* MISC :: DVI_DTG_0_MASTER_SEL :: SELECT [01:00] */
#define BCHP_MISC_DVI_DTG_0_MASTER_SEL_SELECT_MASK                 0x00000003
#define BCHP_MISC_DVI_DTG_0_MASTER_SEL_SELECT_SHIFT                0
#define BCHP_MISC_DVI_DTG_0_MASTER_SEL_SELECT_IT_0                 0
#define BCHP_MISC_DVI_DTG_0_MASTER_SEL_SELECT_IT_1                 1
#define BCHP_MISC_DVI_DTG_0_MASTER_SEL_SELECT_DVI_DTG_0            2

/***************************************************************************
 *DVI_0_SA_CONFIG - SA config for DVI 0
 ***************************************************************************/
/* MISC :: DVI_0_SA_CONFIG :: reserved0 [31:11] */
#define BCHP_MISC_DVI_0_SA_CONFIG_reserved0_MASK                   0xfffff800
#define BCHP_MISC_DVI_0_SA_CONFIG_reserved0_SHIFT                  11

/* MISC :: DVI_0_SA_CONFIG :: EDGE_SELECT [10:09] */
#define BCHP_MISC_DVI_0_SA_CONFIG_EDGE_SELECT_MASK                 0x00000600
#define BCHP_MISC_DVI_0_SA_CONFIG_EDGE_SELECT_SHIFT                9
#define BCHP_MISC_DVI_0_SA_CONFIG_EDGE_SELECT_RISE_EDGE            0
#define BCHP_MISC_DVI_0_SA_CONFIG_EDGE_SELECT_FALL_EDGE            1
#define BCHP_MISC_DVI_0_SA_CONFIG_EDGE_SELECT_BOTH_EDGES           2
#define BCHP_MISC_DVI_0_SA_CONFIG_EDGE_SELECT_NOT_DEFINED          3

/* MISC :: DVI_0_SA_CONFIG :: SA_CH0_EN [08:08] */
#define BCHP_MISC_DVI_0_SA_CONFIG_SA_CH0_EN_MASK                   0x00000100
#define BCHP_MISC_DVI_0_SA_CONFIG_SA_CH0_EN_SHIFT                  8
#define BCHP_MISC_DVI_0_SA_CONFIG_SA_CH0_EN_ON                     1
#define BCHP_MISC_DVI_0_SA_CONFIG_SA_CH0_EN_OFF                    0

/* MISC :: DVI_0_SA_CONFIG :: SA_CH1_EN [07:07] */
#define BCHP_MISC_DVI_0_SA_CONFIG_SA_CH1_EN_MASK                   0x00000080
#define BCHP_MISC_DVI_0_SA_CONFIG_SA_CH1_EN_SHIFT                  7
#define BCHP_MISC_DVI_0_SA_CONFIG_SA_CH1_EN_ON                     1
#define BCHP_MISC_DVI_0_SA_CONFIG_SA_CH1_EN_OFF                    0

/* MISC :: DVI_0_SA_CONFIG :: SA_CH2_EN [06:06] */
#define BCHP_MISC_DVI_0_SA_CONFIG_SA_CH2_EN_MASK                   0x00000040
#define BCHP_MISC_DVI_0_SA_CONFIG_SA_CH2_EN_SHIFT                  6
#define BCHP_MISC_DVI_0_SA_CONFIG_SA_CH2_EN_ON                     1
#define BCHP_MISC_DVI_0_SA_CONFIG_SA_CH2_EN_OFF                    0

/* MISC :: DVI_0_SA_CONFIG :: SA_CH0_CLEAR [05:05] */
#define BCHP_MISC_DVI_0_SA_CONFIG_SA_CH0_CLEAR_MASK                0x00000020
#define BCHP_MISC_DVI_0_SA_CONFIG_SA_CH0_CLEAR_SHIFT               5
#define BCHP_MISC_DVI_0_SA_CONFIG_SA_CH0_CLEAR_ON                  1
#define BCHP_MISC_DVI_0_SA_CONFIG_SA_CH0_CLEAR_OFF                 0

/* MISC :: DVI_0_SA_CONFIG :: SA_CH1_CLEAR [04:04] */
#define BCHP_MISC_DVI_0_SA_CONFIG_SA_CH1_CLEAR_MASK                0x00000010
#define BCHP_MISC_DVI_0_SA_CONFIG_SA_CH1_CLEAR_SHIFT               4
#define BCHP_MISC_DVI_0_SA_CONFIG_SA_CH1_CLEAR_ON                  1
#define BCHP_MISC_DVI_0_SA_CONFIG_SA_CH1_CLEAR_OFF                 0

/* MISC :: DVI_0_SA_CONFIG :: SA_CH2_CLEAR [03:03] */
#define BCHP_MISC_DVI_0_SA_CONFIG_SA_CH2_CLEAR_MASK                0x00000008
#define BCHP_MISC_DVI_0_SA_CONFIG_SA_CH2_CLEAR_SHIFT               3
#define BCHP_MISC_DVI_0_SA_CONFIG_SA_CH2_CLEAR_ON                  1
#define BCHP_MISC_DVI_0_SA_CONFIG_SA_CH2_CLEAR_OFF                 0

/* MISC :: DVI_0_SA_CONFIG :: SA_PROBE_RATE [02:00] */
#define BCHP_MISC_DVI_0_SA_CONFIG_SA_PROBE_RATE_MASK               0x00000007
#define BCHP_MISC_DVI_0_SA_CONFIG_SA_PROBE_RATE_SHIFT              0
#define BCHP_MISC_DVI_0_SA_CONFIG_SA_PROBE_RATE_ZERO               0
#define BCHP_MISC_DVI_0_SA_CONFIG_SA_PROBE_RATE_PER_WINDOW         1
#define BCHP_MISC_DVI_0_SA_CONFIG_SA_PROBE_RATE_PER_2WINDOWS       2
#define BCHP_MISC_DVI_0_SA_CONFIG_SA_PROBE_RATE_PER_3WINDOWS       3
#define BCHP_MISC_DVI_0_SA_CONFIG_SA_PROBE_RATE_PER_4WINDOWS       4
#define BCHP_MISC_DVI_0_SA_CONFIG_SA_PROBE_RATE_PER_5WINDOWS       5
#define BCHP_MISC_DVI_0_SA_CONFIG_SA_PROBE_RATE_PER_6WINDOWS       6
#define BCHP_MISC_DVI_0_SA_CONFIG_SA_PROBE_RATE_PER_7WINDOWS       7

/***************************************************************************
 *DVI_0_SA_CH0_STATUS - SA status for channel 0 for DVI 0
 ***************************************************************************/
/* MISC :: DVI_0_SA_CH0_STATUS :: STATUS [31:00] */
#define BCHP_MISC_DVI_0_SA_CH0_STATUS_STATUS_MASK                  0xffffffff
#define BCHP_MISC_DVI_0_SA_CH0_STATUS_STATUS_SHIFT                 0

/***************************************************************************
 *DVI_0_SA_CH1_STATUS - SA status for channel 1 for DVI 0
 ***************************************************************************/
/* MISC :: DVI_0_SA_CH1_STATUS :: STATUS [31:00] */
#define BCHP_MISC_DVI_0_SA_CH1_STATUS_STATUS_MASK                  0xffffffff
#define BCHP_MISC_DVI_0_SA_CH1_STATUS_STATUS_SHIFT                 0

/***************************************************************************
 *DVI_0_SA_CH2_STATUS - SA status for channel 2 for DVI 0
 ***************************************************************************/
/* MISC :: DVI_0_SA_CH2_STATUS :: STATUS [31:00] */
#define BCHP_MISC_DVI_0_SA_CH2_STATUS_STATUS_MASK                  0xffffffff
#define BCHP_MISC_DVI_0_SA_CH2_STATUS_STATUS_SHIFT                 0

/***************************************************************************
 *DAC_BG_CTRL_0 - DAC Bandgap Control Register
 ***************************************************************************/
/* MISC :: DAC_BG_CTRL_0 :: reserved0 [31:16] */
#define BCHP_MISC_DAC_BG_CTRL_0_reserved0_MASK                     0xffff0000
#define BCHP_MISC_DAC_BG_CTRL_0_reserved0_SHIFT                    16

/* MISC :: DAC_BG_CTRL_0 :: UNUSED [15:11] */
#define BCHP_MISC_DAC_BG_CTRL_0_UNUSED_MASK                        0x0000f800
#define BCHP_MISC_DAC_BG_CTRL_0_UNUSED_SHIFT                       11

/* MISC :: DAC_BG_CTRL_0 :: PWRDN [10:10] */
#define BCHP_MISC_DAC_BG_CTRL_0_PWRDN_MASK                         0x00000400
#define BCHP_MISC_DAC_BG_CTRL_0_PWRDN_SHIFT                        10
#define BCHP_MISC_DAC_BG_CTRL_0_PWRDN_PWRUP                        0
#define BCHP_MISC_DAC_BG_CTRL_0_PWRDN_PWRDN                        1

/* MISC :: DAC_BG_CTRL_0 :: CORE_ADJ [09:07] */
#define BCHP_MISC_DAC_BG_CTRL_0_CORE_ADJ_MASK                      0x00000380
#define BCHP_MISC_DAC_BG_CTRL_0_CORE_ADJ_SHIFT                     7
#define BCHP_MISC_DAC_BG_CTRL_0_CORE_ADJ_ZERO                      0
#define BCHP_MISC_DAC_BG_CTRL_0_CORE_ADJ_ONE                       1
#define BCHP_MISC_DAC_BG_CTRL_0_CORE_ADJ_TWO                       2
#define BCHP_MISC_DAC_BG_CTRL_0_CORE_ADJ_THREE                     3
#define BCHP_MISC_DAC_BG_CTRL_0_CORE_ADJ_FOUR                      4
#define BCHP_MISC_DAC_BG_CTRL_0_CORE_ADJ_FIVE                      5
#define BCHP_MISC_DAC_BG_CTRL_0_CORE_ADJ_SIX                       6
#define BCHP_MISC_DAC_BG_CTRL_0_CORE_ADJ_SEVEN                     7

/* MISC :: DAC_BG_CTRL_0 :: BANDGAP_BYP [06:06] */
#define BCHP_MISC_DAC_BG_CTRL_0_BANDGAP_BYP_MASK                   0x00000040
#define BCHP_MISC_DAC_BG_CTRL_0_BANDGAP_BYP_SHIFT                  6
#define BCHP_MISC_DAC_BG_CTRL_0_BANDGAP_BYP_BANDGAP                0
#define BCHP_MISC_DAC_BG_CTRL_0_BANDGAP_BYP_AVDD2P5BY2             1

/* MISC :: DAC_BG_CTRL_0 :: IREF_ADJ [05:01] */
#define BCHP_MISC_DAC_BG_CTRL_0_IREF_ADJ_MASK                      0x0000003e
#define BCHP_MISC_DAC_BG_CTRL_0_IREF_ADJ_SHIFT                     1
#define BCHP_MISC_DAC_BG_CTRL_0_IREF_ADJ_ZERO                      0
#define BCHP_MISC_DAC_BG_CTRL_0_IREF_ADJ_ONE                       1
#define BCHP_MISC_DAC_BG_CTRL_0_IREF_ADJ_TWO                       2
#define BCHP_MISC_DAC_BG_CTRL_0_IREF_ADJ_THREE                     3
#define BCHP_MISC_DAC_BG_CTRL_0_IREF_ADJ_FOUR                      4
#define BCHP_MISC_DAC_BG_CTRL_0_IREF_ADJ_FIVE                      5
#define BCHP_MISC_DAC_BG_CTRL_0_IREF_ADJ_SIX                       6
#define BCHP_MISC_DAC_BG_CTRL_0_IREF_ADJ_SEVEN                     7
#define BCHP_MISC_DAC_BG_CTRL_0_IREF_ADJ_EIGHT                     8
#define BCHP_MISC_DAC_BG_CTRL_0_IREF_ADJ_NINE                      9
#define BCHP_MISC_DAC_BG_CTRL_0_IREF_ADJ_TEN                       10
#define BCHP_MISC_DAC_BG_CTRL_0_IREF_ADJ_ELEVEN                    11
#define BCHP_MISC_DAC_BG_CTRL_0_IREF_ADJ_TWELVE                    12
#define BCHP_MISC_DAC_BG_CTRL_0_IREF_ADJ_THIRTEEN                  13
#define BCHP_MISC_DAC_BG_CTRL_0_IREF_ADJ_FOURTEEN                  14
#define BCHP_MISC_DAC_BG_CTRL_0_IREF_ADJ_FIFTEEN                   15
#define BCHP_MISC_DAC_BG_CTRL_0_IREF_ADJ_SIXTEEN                   16
#define BCHP_MISC_DAC_BG_CTRL_0_IREF_ADJ_SEVENTEEN                 17
#define BCHP_MISC_DAC_BG_CTRL_0_IREF_ADJ_EIGHTEEN                  18
#define BCHP_MISC_DAC_BG_CTRL_0_IREF_ADJ_NINETEEN                  19
#define BCHP_MISC_DAC_BG_CTRL_0_IREF_ADJ_TWENTY                    20
#define BCHP_MISC_DAC_BG_CTRL_0_IREF_ADJ_TWENTY_ONE                21
#define BCHP_MISC_DAC_BG_CTRL_0_IREF_ADJ_TWENTY_TWO                22
#define BCHP_MISC_DAC_BG_CTRL_0_IREF_ADJ_TWENTY_THREE              23
#define BCHP_MISC_DAC_BG_CTRL_0_IREF_ADJ_TWENTY_FOUR               24
#define BCHP_MISC_DAC_BG_CTRL_0_IREF_ADJ_TWENTY_FIVE               25
#define BCHP_MISC_DAC_BG_CTRL_0_IREF_ADJ_TWENTY_SIX                26
#define BCHP_MISC_DAC_BG_CTRL_0_IREF_ADJ_TWENTY_SEVEN              27
#define BCHP_MISC_DAC_BG_CTRL_0_IREF_ADJ_TWENTY_EIGHT              28
#define BCHP_MISC_DAC_BG_CTRL_0_IREF_ADJ_TWENTY_NINE               29
#define BCHP_MISC_DAC_BG_CTRL_0_IREF_ADJ_THIRTY                    30
#define BCHP_MISC_DAC_BG_CTRL_0_IREF_ADJ_THIRTY_ONE                31

/* MISC :: DAC_BG_CTRL_0 :: PWRDN_REFAMP [00:00] */
#define BCHP_MISC_DAC_BG_CTRL_0_PWRDN_REFAMP_MASK                  0x00000001
#define BCHP_MISC_DAC_BG_CTRL_0_PWRDN_REFAMP_SHIFT                 0
#define BCHP_MISC_DAC_BG_CTRL_0_PWRDN_REFAMP_POWER_DOWN            1
#define BCHP_MISC_DAC_BG_CTRL_0_PWRDN_REFAMP_POWER_UP              0

/***************************************************************************
 *DAC_0_CTRL - DAC_0 Control Register
 ***************************************************************************/
/* MISC :: DAC_0_CTRL :: reserved0 [31:16] */
#define BCHP_MISC_DAC_0_CTRL_reserved0_MASK                        0xffff0000
#define BCHP_MISC_DAC_0_CTRL_reserved0_SHIFT                       16

/* MISC :: DAC_0_CTRL :: UNUSED [15:15] */
#define BCHP_MISC_DAC_0_CTRL_UNUSED_MASK                           0x00008000
#define BCHP_MISC_DAC_0_CTRL_UNUSED_SHIFT                          15

/* MISC :: DAC_0_CTRL :: PWRUP_BAIS [14:14] */
#define BCHP_MISC_DAC_0_CTRL_PWRUP_BAIS_MASK                       0x00004000
#define BCHP_MISC_DAC_0_CTRL_PWRUP_BAIS_SHIFT                      14
#define BCHP_MISC_DAC_0_CTRL_PWRUP_BAIS_PWRDN                      0
#define BCHP_MISC_DAC_0_CTRL_PWRUP_BAIS_PWRUP                      1

/* MISC :: DAC_0_CTRL :: PWRDN [13:13] */
#define BCHP_MISC_DAC_0_CTRL_PWRDN_MASK                            0x00002000
#define BCHP_MISC_DAC_0_CTRL_PWRDN_SHIFT                           13
#define BCHP_MISC_DAC_0_CTRL_PWRDN_PWRUP                           0
#define BCHP_MISC_DAC_0_CTRL_PWRDN_PWRDN                           1

/* MISC :: DAC_0_CTRL :: CLKINV [12:12] */
#define BCHP_MISC_DAC_0_CTRL_CLKINV_MASK                           0x00001000
#define BCHP_MISC_DAC_0_CTRL_CLKINV_SHIFT                          12

/* MISC :: DAC_0_CTRL :: TCOBB [11:11] */
#define BCHP_MISC_DAC_0_CTRL_TCOBB_MASK                            0x00000800
#define BCHP_MISC_DAC_0_CTRL_TCOBB_SHIFT                           11
#define BCHP_MISC_DAC_0_CTRL_TCOBB_OFFSET                          0
#define BCHP_MISC_DAC_0_CTRL_TCOBB_COMP                            1

/* MISC :: DAC_0_CTRL :: DCWORD [10:01] */
#define BCHP_MISC_DAC_0_CTRL_DCWORD_MASK                           0x000007fe
#define BCHP_MISC_DAC_0_CTRL_DCWORD_SHIFT                          1

/* MISC :: DAC_0_CTRL :: DCENBL [00:00] */
#define BCHP_MISC_DAC_0_CTRL_DCENBL_MASK                           0x00000001
#define BCHP_MISC_DAC_0_CTRL_DCENBL_SHIFT                          0
#define BCHP_MISC_DAC_0_CTRL_DCENBL_NORM                           0
#define BCHP_MISC_DAC_0_CTRL_DCENBL_ON                             1

/***************************************************************************
 *DAC_1_CTRL - DAC_1 Control Register
 ***************************************************************************/
/* MISC :: DAC_1_CTRL :: reserved0 [31:16] */
#define BCHP_MISC_DAC_1_CTRL_reserved0_MASK                        0xffff0000
#define BCHP_MISC_DAC_1_CTRL_reserved0_SHIFT                       16

/* MISC :: DAC_1_CTRL :: UNUSED [15:15] */
#define BCHP_MISC_DAC_1_CTRL_UNUSED_MASK                           0x00008000
#define BCHP_MISC_DAC_1_CTRL_UNUSED_SHIFT                          15

/* MISC :: DAC_1_CTRL :: PWRUP_BAIS [14:14] */
#define BCHP_MISC_DAC_1_CTRL_PWRUP_BAIS_MASK                       0x00004000
#define BCHP_MISC_DAC_1_CTRL_PWRUP_BAIS_SHIFT                      14
#define BCHP_MISC_DAC_1_CTRL_PWRUP_BAIS_PWRDN                      0
#define BCHP_MISC_DAC_1_CTRL_PWRUP_BAIS_PWRUP                      1

/* MISC :: DAC_1_CTRL :: PWRDN [13:13] */
#define BCHP_MISC_DAC_1_CTRL_PWRDN_MASK                            0x00002000
#define BCHP_MISC_DAC_1_CTRL_PWRDN_SHIFT                           13
#define BCHP_MISC_DAC_1_CTRL_PWRDN_PWRUP                           0
#define BCHP_MISC_DAC_1_CTRL_PWRDN_PWRDN                           1

/* MISC :: DAC_1_CTRL :: CLKINV [12:12] */
#define BCHP_MISC_DAC_1_CTRL_CLKINV_MASK                           0x00001000
#define BCHP_MISC_DAC_1_CTRL_CLKINV_SHIFT                          12

/* MISC :: DAC_1_CTRL :: TCOBB [11:11] */
#define BCHP_MISC_DAC_1_CTRL_TCOBB_MASK                            0x00000800
#define BCHP_MISC_DAC_1_CTRL_TCOBB_SHIFT                           11
#define BCHP_MISC_DAC_1_CTRL_TCOBB_OFFSET                          0
#define BCHP_MISC_DAC_1_CTRL_TCOBB_COMP                            1

/* MISC :: DAC_1_CTRL :: DCWORD [10:01] */
#define BCHP_MISC_DAC_1_CTRL_DCWORD_MASK                           0x000007fe
#define BCHP_MISC_DAC_1_CTRL_DCWORD_SHIFT                          1

/* MISC :: DAC_1_CTRL :: DCENBL [00:00] */
#define BCHP_MISC_DAC_1_CTRL_DCENBL_MASK                           0x00000001
#define BCHP_MISC_DAC_1_CTRL_DCENBL_SHIFT                          0
#define BCHP_MISC_DAC_1_CTRL_DCENBL_NORM                           0
#define BCHP_MISC_DAC_1_CTRL_DCENBL_ON                             1

/***************************************************************************
 *DAC_2_CTRL - DAC_2 Control Register
 ***************************************************************************/
/* MISC :: DAC_2_CTRL :: reserved0 [31:16] */
#define BCHP_MISC_DAC_2_CTRL_reserved0_MASK                        0xffff0000
#define BCHP_MISC_DAC_2_CTRL_reserved0_SHIFT                       16

/* MISC :: DAC_2_CTRL :: UNUSED [15:15] */
#define BCHP_MISC_DAC_2_CTRL_UNUSED_MASK                           0x00008000
#define BCHP_MISC_DAC_2_CTRL_UNUSED_SHIFT                          15

/* MISC :: DAC_2_CTRL :: PWRUP_BAIS [14:14] */
#define BCHP_MISC_DAC_2_CTRL_PWRUP_BAIS_MASK                       0x00004000
#define BCHP_MISC_DAC_2_CTRL_PWRUP_BAIS_SHIFT                      14
#define BCHP_MISC_DAC_2_CTRL_PWRUP_BAIS_PWRDN                      0
#define BCHP_MISC_DAC_2_CTRL_PWRUP_BAIS_PWRUP                      1

/* MISC :: DAC_2_CTRL :: PWRDN [13:13] */
#define BCHP_MISC_DAC_2_CTRL_PWRDN_MASK                            0x00002000
#define BCHP_MISC_DAC_2_CTRL_PWRDN_SHIFT                           13
#define BCHP_MISC_DAC_2_CTRL_PWRDN_PWRUP                           0
#define BCHP_MISC_DAC_2_CTRL_PWRDN_PWRDN                           1

/* MISC :: DAC_2_CTRL :: CLKINV [12:12] */
#define BCHP_MISC_DAC_2_CTRL_CLKINV_MASK                           0x00001000
#define BCHP_MISC_DAC_2_CTRL_CLKINV_SHIFT                          12

/* MISC :: DAC_2_CTRL :: TCOBB [11:11] */
#define BCHP_MISC_DAC_2_CTRL_TCOBB_MASK                            0x00000800
#define BCHP_MISC_DAC_2_CTRL_TCOBB_SHIFT                           11
#define BCHP_MISC_DAC_2_CTRL_TCOBB_OFFSET                          0
#define BCHP_MISC_DAC_2_CTRL_TCOBB_COMP                            1

/* MISC :: DAC_2_CTRL :: DCWORD [10:01] */
#define BCHP_MISC_DAC_2_CTRL_DCWORD_MASK                           0x000007fe
#define BCHP_MISC_DAC_2_CTRL_DCWORD_SHIFT                          1

/* MISC :: DAC_2_CTRL :: DCENBL [00:00] */
#define BCHP_MISC_DAC_2_CTRL_DCENBL_MASK                           0x00000001
#define BCHP_MISC_DAC_2_CTRL_DCENBL_SHIFT                          0
#define BCHP_MISC_DAC_2_CTRL_DCENBL_NORM                           0
#define BCHP_MISC_DAC_2_CTRL_DCENBL_ON                             1

/***************************************************************************
 *DAC_3_CTRL - DAC_3 Control Register
 ***************************************************************************/
/* MISC :: DAC_3_CTRL :: reserved0 [31:16] */
#define BCHP_MISC_DAC_3_CTRL_reserved0_MASK                        0xffff0000
#define BCHP_MISC_DAC_3_CTRL_reserved0_SHIFT                       16

/* MISC :: DAC_3_CTRL :: UNUSED [15:15] */
#define BCHP_MISC_DAC_3_CTRL_UNUSED_MASK                           0x00008000
#define BCHP_MISC_DAC_3_CTRL_UNUSED_SHIFT                          15

/* MISC :: DAC_3_CTRL :: PWRUP_BAIS [14:14] */
#define BCHP_MISC_DAC_3_CTRL_PWRUP_BAIS_MASK                       0x00004000
#define BCHP_MISC_DAC_3_CTRL_PWRUP_BAIS_SHIFT                      14
#define BCHP_MISC_DAC_3_CTRL_PWRUP_BAIS_PWRDN                      0
#define BCHP_MISC_DAC_3_CTRL_PWRUP_BAIS_PWRUP                      1

/* MISC :: DAC_3_CTRL :: PWRDN [13:13] */
#define BCHP_MISC_DAC_3_CTRL_PWRDN_MASK                            0x00002000
#define BCHP_MISC_DAC_3_CTRL_PWRDN_SHIFT                           13
#define BCHP_MISC_DAC_3_CTRL_PWRDN_PWRUP                           0
#define BCHP_MISC_DAC_3_CTRL_PWRDN_PWRDN                           1

/* MISC :: DAC_3_CTRL :: CLKINV [12:12] */
#define BCHP_MISC_DAC_3_CTRL_CLKINV_MASK                           0x00001000
#define BCHP_MISC_DAC_3_CTRL_CLKINV_SHIFT                          12

/* MISC :: DAC_3_CTRL :: TCOBB [11:11] */
#define BCHP_MISC_DAC_3_CTRL_TCOBB_MASK                            0x00000800
#define BCHP_MISC_DAC_3_CTRL_TCOBB_SHIFT                           11
#define BCHP_MISC_DAC_3_CTRL_TCOBB_OFFSET                          0
#define BCHP_MISC_DAC_3_CTRL_TCOBB_COMP                            1

/* MISC :: DAC_3_CTRL :: DCWORD [10:01] */
#define BCHP_MISC_DAC_3_CTRL_DCWORD_MASK                           0x000007fe
#define BCHP_MISC_DAC_3_CTRL_DCWORD_SHIFT                          1

/* MISC :: DAC_3_CTRL :: DCENBL [00:00] */
#define BCHP_MISC_DAC_3_CTRL_DCENBL_MASK                           0x00000001
#define BCHP_MISC_DAC_3_CTRL_DCENBL_SHIFT                          0
#define BCHP_MISC_DAC_3_CTRL_DCENBL_NORM                           0
#define BCHP_MISC_DAC_3_CTRL_DCENBL_ON                             1

#endif /* #ifndef BCHP_MISC_H__ */

/* End of File */

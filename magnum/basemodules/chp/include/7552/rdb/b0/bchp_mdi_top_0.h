/***************************************************************************
 *     Copyright (c) 1999-2012, Broadcom Corporation
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
 * Date:           Generated on         Tue Feb  7 10:59:54 2012
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

#ifndef BCHP_MDI_TOP_0_H__
#define BCHP_MDI_TOP_0_H__

/***************************************************************************
 *MDI_TOP_0 - MADR Top Control Block Registers 0
 ***************************************************************************/
#define BCHP_MDI_TOP_0_REVISION_ID               0x00662000 /* MADR Revision register */
#define BCHP_MDI_TOP_0_HW_CONFIGURATION          0x00662004 /* Hardware Configuration Register */
#define BCHP_MDI_TOP_0_ENABLE_CONTROL            0x00662008 /* Enable Control register */
#define BCHP_MDI_TOP_0_MODE_CONTROL_0            0x0066200c /* Operation Mode Set 0 */
#define BCHP_MDI_TOP_0_SRC_PIC_SIZE              0x00662010 /* MADR Source Picture Size Information */
#define BCHP_MDI_TOP_0_PIXEL_FIELD_MSTART_0      0x00662014 /* MAD-R Pixel Field 0 Buffer Starting Address */
#define BCHP_MDI_TOP_0_PIXEL_FIELD_MSTART_1      0x00662018 /* MAD-R Pixel Field 1 Buffer Starting Address */
#define BCHP_MDI_TOP_0_PIXEL_FIELD_MSTART_2      0x0066201c /* MAD-R Pixel Field 2 Buffer Starting Address */
#define BCHP_MDI_TOP_0_OSD_POSITION              0x00662024 /* MADR On Screen Display Position */
#define BCHP_MDI_TOP_0_BVB_IN_STATUS             0x00662028 /* MADR Broadcom Video Bus Input Status */
#define BCHP_MDI_TOP_0_BVB_IN_STATUS_CLEAR       0x0066202c /* MADR Broadcom Video Bus Input Status Clear */
#define BCHP_MDI_TOP_0_TEST_PORT_DATA            0x00662030 /* Testport data register */
#define BCHP_MDI_TOP_0_TEST_PORT_CONTROL         0x00662034 /* Testportl control register */
#define BCHP_MDI_TOP_0_QM_FIELD_MSTART_1         0x00662038 /* MADR Quantized Motion Field 1 Buffer Starting Address */
#define BCHP_MDI_TOP_0_QM_FIELD_MSTART_2         0x0066203c /* MADR Quantized Motion Field 2 Buffer Starting Address */
#define BCHP_MDI_TOP_0_QM_FIELD_MSTART_3         0x00662040 /* MADR Quantized Motion Field 3 Buffer Starting Address */
#define BCHP_MDI_TOP_0_QM_FIELD_MSTART_4         0x00662044 /* MADR Quantized Motion Field 4 Buffer Starting Address */

/***************************************************************************
 *REVISION_ID - MADR Revision register
 ***************************************************************************/
/* MDI_TOP_0 :: REVISION_ID :: reserved0 [31:16] */
#define BCHP_MDI_TOP_0_REVISION_ID_reserved0_MASK                  0xffff0000
#define BCHP_MDI_TOP_0_REVISION_ID_reserved0_SHIFT                 16

/* MDI_TOP_0 :: REVISION_ID :: MAJOR [15:08] */
#define BCHP_MDI_TOP_0_REVISION_ID_MAJOR_MASK                      0x0000ff00
#define BCHP_MDI_TOP_0_REVISION_ID_MAJOR_SHIFT                     8
#define BCHP_MDI_TOP_0_REVISION_ID_MAJOR_DEFAULT                   0x00000000

/* MDI_TOP_0 :: REVISION_ID :: MINOR [07:00] */
#define BCHP_MDI_TOP_0_REVISION_ID_MINOR_MASK                      0x000000ff
#define BCHP_MDI_TOP_0_REVISION_ID_MINOR_SHIFT                     0
#define BCHP_MDI_TOP_0_REVISION_ID_MINOR_DEFAULT                   0x00000003

/***************************************************************************
 *HW_CONFIGURATION - Hardware Configuration Register
 ***************************************************************************/
/* MDI_TOP_0 :: HW_CONFIGURATION :: reserved0 [31:11] */
#define BCHP_MDI_TOP_0_HW_CONFIGURATION_reserved0_MASK             0xfffff800
#define BCHP_MDI_TOP_0_HW_CONFIGURATION_reserved0_SHIFT            11

/* MDI_TOP_0 :: HW_CONFIGURATION :: PICTURE_MEASUREMENT [10:10] */
#define BCHP_MDI_TOP_0_HW_CONFIGURATION_PICTURE_MEASUREMENT_MASK   0x00000400
#define BCHP_MDI_TOP_0_HW_CONFIGURATION_PICTURE_MEASUREMENT_SHIFT  10
#define BCHP_MDI_TOP_0_HW_CONFIGURATION_PICTURE_MEASUREMENT_DEFAULT 0x00000000
#define BCHP_MDI_TOP_0_HW_CONFIGURATION_PICTURE_MEASUREMENT_NOT_SUPPORT 0
#define BCHP_MDI_TOP_0_HW_CONFIGURATION_PICTURE_MEASUREMENT_SUPPORT 1

/* MDI_TOP_0 :: HW_CONFIGURATION :: REGION_BASED_PP_CORRECTION [09:09] */
#define BCHP_MDI_TOP_0_HW_CONFIGURATION_REGION_BASED_PP_CORRECTION_MASK 0x00000200
#define BCHP_MDI_TOP_0_HW_CONFIGURATION_REGION_BASED_PP_CORRECTION_SHIFT 9
#define BCHP_MDI_TOP_0_HW_CONFIGURATION_REGION_BASED_PP_CORRECTION_DEFAULT 0x00000000
#define BCHP_MDI_TOP_0_HW_CONFIGURATION_REGION_BASED_PP_CORRECTION_NOT_SUPPORT 0
#define BCHP_MDI_TOP_0_HW_CONFIGURATION_REGION_BASED_PP_CORRECTION_SUPPORT 1

/* MDI_TOP_0 :: HW_CONFIGURATION :: QUANTIZED_MOTION [08:08] */
#define BCHP_MDI_TOP_0_HW_CONFIGURATION_QUANTIZED_MOTION_MASK      0x00000100
#define BCHP_MDI_TOP_0_HW_CONFIGURATION_QUANTIZED_MOTION_SHIFT     8
#define BCHP_MDI_TOP_0_HW_CONFIGURATION_QUANTIZED_MOTION_DEFAULT   0x00000001
#define BCHP_MDI_TOP_0_HW_CONFIGURATION_QUANTIZED_MOTION_NOT_SUPPORT 0
#define BCHP_MDI_TOP_0_HW_CONFIGURATION_QUANTIZED_MOTION_SUPPORT   1

/* MDI_TOP_0 :: HW_CONFIGURATION :: WWC [07:07] */
#define BCHP_MDI_TOP_0_HW_CONFIGURATION_WWC_MASK                   0x00000080
#define BCHP_MDI_TOP_0_HW_CONFIGURATION_WWC_SHIFT                  7
#define BCHP_MDI_TOP_0_HW_CONFIGURATION_WWC_DEFAULT                0x00000000
#define BCHP_MDI_TOP_0_HW_CONFIGURATION_WWC_NOT_SUPPORT            0
#define BCHP_MDI_TOP_0_HW_CONFIGURATION_WWC_SUPPORT                1

/* MDI_TOP_0 :: HW_CONFIGURATION :: UP_IT [06:06] */
#define BCHP_MDI_TOP_0_HW_CONFIGURATION_UP_IT_MASK                 0x00000040
#define BCHP_MDI_TOP_0_HW_CONFIGURATION_UP_IT_SHIFT                6
#define BCHP_MDI_TOP_0_HW_CONFIGURATION_UP_IT_DEFAULT              0x00000000
#define BCHP_MDI_TOP_0_HW_CONFIGURATION_UP_IT_NOT_SUPPORT          0
#define BCHP_MDI_TOP_0_HW_CONFIGURATION_UP_IT_SUPPORT              1

/* MDI_TOP_0 :: HW_CONFIGURATION :: FRC_SIDELOCK [05:05] */
#define BCHP_MDI_TOP_0_HW_CONFIGURATION_FRC_SIDELOCK_MASK          0x00000020
#define BCHP_MDI_TOP_0_HW_CONFIGURATION_FRC_SIDELOCK_SHIFT         5
#define BCHP_MDI_TOP_0_HW_CONFIGURATION_FRC_SIDELOCK_DEFAULT       0x00000000
#define BCHP_MDI_TOP_0_HW_CONFIGURATION_FRC_SIDELOCK_NOT_SUPPORT   0
#define BCHP_MDI_TOP_0_HW_CONFIGURATION_FRC_SIDELOCK_SUPPORT       1

/* MDI_TOP_0 :: HW_CONFIGURATION :: MCDI_SIDELOCK [04:04] */
#define BCHP_MDI_TOP_0_HW_CONFIGURATION_MCDI_SIDELOCK_MASK         0x00000010
#define BCHP_MDI_TOP_0_HW_CONFIGURATION_MCDI_SIDELOCK_SHIFT        4
#define BCHP_MDI_TOP_0_HW_CONFIGURATION_MCDI_SIDELOCK_DEFAULT      0x00000000
#define BCHP_MDI_TOP_0_HW_CONFIGURATION_MCDI_SIDELOCK_NOT_SUPPORT  0
#define BCHP_MDI_TOP_0_HW_CONFIGURATION_MCDI_SIDELOCK_SUPPORT      1

/* MDI_TOP_0 :: HW_CONFIGURATION :: TYPE [03:00] */
#define BCHP_MDI_TOP_0_HW_CONFIGURATION_TYPE_MASK                  0x0000000f
#define BCHP_MDI_TOP_0_HW_CONFIGURATION_TYPE_SHIFT                 0
#define BCHP_MDI_TOP_0_HW_CONFIGURATION_TYPE_DEFAULT               0x00000001
#define BCHP_MDI_TOP_0_HW_CONFIGURATION_TYPE_MAD                   0
#define BCHP_MDI_TOP_0_HW_CONFIGURATION_TYPE_MADR                  1
#define BCHP_MDI_TOP_0_HW_CONFIGURATION_TYPE_MCDI_1D               2
#define BCHP_MDI_TOP_0_HW_CONFIGURATION_TYPE_MCDI_2D               3
#define BCHP_MDI_TOP_0_HW_CONFIGURATION_TYPE_RESERVED0             4
#define BCHP_MDI_TOP_0_HW_CONFIGURATION_TYPE_RESERVED1             5
#define BCHP_MDI_TOP_0_HW_CONFIGURATION_TYPE_RESERVED2             6
#define BCHP_MDI_TOP_0_HW_CONFIGURATION_TYPE_RESERVED3             7
#define BCHP_MDI_TOP_0_HW_CONFIGURATION_TYPE_RESERVED4             8
#define BCHP_MDI_TOP_0_HW_CONFIGURATION_TYPE_RESERVED5             9
#define BCHP_MDI_TOP_0_HW_CONFIGURATION_TYPE_RESERVED6             10
#define BCHP_MDI_TOP_0_HW_CONFIGURATION_TYPE_RESERVED7             11
#define BCHP_MDI_TOP_0_HW_CONFIGURATION_TYPE_RESERVED8             12
#define BCHP_MDI_TOP_0_HW_CONFIGURATION_TYPE_RESERVED9             13
#define BCHP_MDI_TOP_0_HW_CONFIGURATION_TYPE_RESERVED10            14
#define BCHP_MDI_TOP_0_HW_CONFIGURATION_TYPE_RESERVED11            15

/***************************************************************************
 *ENABLE_CONTROL - Enable Control register
 ***************************************************************************/
/* MDI_TOP_0 :: ENABLE_CONTROL :: reserved0 [31:02] */
#define BCHP_MDI_TOP_0_ENABLE_CONTROL_reserved0_MASK               0xfffffffc
#define BCHP_MDI_TOP_0_ENABLE_CONTROL_reserved0_SHIFT              2

/* MDI_TOP_0 :: ENABLE_CONTROL :: MODE [01:01] */
#define BCHP_MDI_TOP_0_ENABLE_CONTROL_MODE_MASK                    0x00000002
#define BCHP_MDI_TOP_0_ENABLE_CONTROL_MODE_SHIFT                   1
#define BCHP_MDI_TOP_0_ENABLE_CONTROL_MODE_DEFAULT                 0x00000000
#define BCHP_MDI_TOP_0_ENABLE_CONTROL_MODE_STOP_ON_FIELD_COMPLETION 0
#define BCHP_MDI_TOP_0_ENABLE_CONTROL_MODE_CONTINUOUS_FOR_TEST     1

/* MDI_TOP_0 :: ENABLE_CONTROL :: ENABLE [00:00] */
#define BCHP_MDI_TOP_0_ENABLE_CONTROL_ENABLE_MASK                  0x00000001
#define BCHP_MDI_TOP_0_ENABLE_CONTROL_ENABLE_SHIFT                 0
#define BCHP_MDI_TOP_0_ENABLE_CONTROL_ENABLE_DEFAULT               0x00000000
#define BCHP_MDI_TOP_0_ENABLE_CONTROL_ENABLE_OFF                   0
#define BCHP_MDI_TOP_0_ENABLE_CONTROL_ENABLE_ON                    1

/***************************************************************************
 *MODE_CONTROL_0 - Operation Mode Set 0
 ***************************************************************************/
/* MDI_TOP_0 :: MODE_CONTROL_0 :: reserved0 [31:09] */
#define BCHP_MDI_TOP_0_MODE_CONTROL_0_reserved0_MASK               0xfffffe00
#define BCHP_MDI_TOP_0_MODE_CONTROL_0_reserved0_SHIFT              9

/* MDI_TOP_0 :: MODE_CONTROL_0 :: FEEDER_PRE_FETCH [08:08] */
#define BCHP_MDI_TOP_0_MODE_CONTROL_0_FEEDER_PRE_FETCH_MASK        0x00000100
#define BCHP_MDI_TOP_0_MODE_CONTROL_0_FEEDER_PRE_FETCH_SHIFT       8
#define BCHP_MDI_TOP_0_MODE_CONTROL_0_FEEDER_PRE_FETCH_DEFAULT     0x00000001
#define BCHP_MDI_TOP_0_MODE_CONTROL_0_FEEDER_PRE_FETCH_OFF         0
#define BCHP_MDI_TOP_0_MODE_CONTROL_0_FEEDER_PRE_FETCH_ON          1

/* MDI_TOP_0 :: MODE_CONTROL_0 :: ON_SCREEN_MC_OVERRIDE_ENABLE [07:07] */
#define BCHP_MDI_TOP_0_MODE_CONTROL_0_ON_SCREEN_MC_OVERRIDE_ENABLE_MASK 0x00000080
#define BCHP_MDI_TOP_0_MODE_CONTROL_0_ON_SCREEN_MC_OVERRIDE_ENABLE_SHIFT 7
#define BCHP_MDI_TOP_0_MODE_CONTROL_0_ON_SCREEN_MC_OVERRIDE_ENABLE_DEFAULT 0x00000000
#define BCHP_MDI_TOP_0_MODE_CONTROL_0_ON_SCREEN_MC_OVERRIDE_ENABLE_OFF 0
#define BCHP_MDI_TOP_0_MODE_CONTROL_0_ON_SCREEN_MC_OVERRIDE_ENABLE_ON 1

/* MDI_TOP_0 :: MODE_CONTROL_0 :: BVB_VIDEO [06:05] */
#define BCHP_MDI_TOP_0_MODE_CONTROL_0_BVB_VIDEO_MASK               0x00000060
#define BCHP_MDI_TOP_0_MODE_CONTROL_0_BVB_VIDEO_SHIFT              5
#define BCHP_MDI_TOP_0_MODE_CONTROL_0_BVB_VIDEO_DEFAULT            0x00000000
#define BCHP_MDI_TOP_0_MODE_CONTROL_0_BVB_VIDEO_MODE_2D            0
#define BCHP_MDI_TOP_0_MODE_CONTROL_0_BVB_VIDEO_MODE_3D_LEFT_RIGHT 1
#define BCHP_MDI_TOP_0_MODE_CONTROL_0_BVB_VIDEO_MODE_3D_OVER_UNDER 2

/* MDI_TOP_0 :: MODE_CONTROL_0 :: ON_SCREEN_PP_ENABLE [04:04] */
#define BCHP_MDI_TOP_0_MODE_CONTROL_0_ON_SCREEN_PP_ENABLE_MASK     0x00000010
#define BCHP_MDI_TOP_0_MODE_CONTROL_0_ON_SCREEN_PP_ENABLE_SHIFT    4
#define BCHP_MDI_TOP_0_MODE_CONTROL_0_ON_SCREEN_PP_ENABLE_DEFAULT  0x00000000
#define BCHP_MDI_TOP_0_MODE_CONTROL_0_ON_SCREEN_PP_ENABLE_OFF      0
#define BCHP_MDI_TOP_0_MODE_CONTROL_0_ON_SCREEN_PP_ENABLE_ON       1

/* MDI_TOP_0 :: MODE_CONTROL_0 :: UPDATE_SEL [03:03] */
#define BCHP_MDI_TOP_0_MODE_CONTROL_0_UPDATE_SEL_MASK              0x00000008
#define BCHP_MDI_TOP_0_MODE_CONTROL_0_UPDATE_SEL_SHIFT             3
#define BCHP_MDI_TOP_0_MODE_CONTROL_0_UPDATE_SEL_DEFAULT           0x00000000
#define BCHP_MDI_TOP_0_MODE_CONTROL_0_UPDATE_SEL_UPDATE_BY_PICTURE 1
#define BCHP_MDI_TOP_0_MODE_CONTROL_0_UPDATE_SEL_ALWAYS_UPDATE     0

/* MDI_TOP_0 :: MODE_CONTROL_0 :: LOW_DELAY_COUNT [02:01] */
#define BCHP_MDI_TOP_0_MODE_CONTROL_0_LOW_DELAY_COUNT_MASK         0x00000006
#define BCHP_MDI_TOP_0_MODE_CONTROL_0_LOW_DELAY_COUNT_SHIFT        1
#define BCHP_MDI_TOP_0_MODE_CONTROL_0_LOW_DELAY_COUNT_DEFAULT      0x00000002
#define BCHP_MDI_TOP_0_MODE_CONTROL_0_LOW_DELAY_COUNT_ZERO_FIELD_DELAY 0
#define BCHP_MDI_TOP_0_MODE_CONTROL_0_LOW_DELAY_COUNT_ONE_FIELD_DELY 1
#define BCHP_MDI_TOP_0_MODE_CONTROL_0_LOW_DELAY_COUNT_NORMAL_DELAY 2

/* MDI_TOP_0 :: MODE_CONTROL_0 :: ON_SCREEN_STATUS_ENABLE [00:00] */
#define BCHP_MDI_TOP_0_MODE_CONTROL_0_ON_SCREEN_STATUS_ENABLE_MASK 0x00000001
#define BCHP_MDI_TOP_0_MODE_CONTROL_0_ON_SCREEN_STATUS_ENABLE_SHIFT 0
#define BCHP_MDI_TOP_0_MODE_CONTROL_0_ON_SCREEN_STATUS_ENABLE_DEFAULT 0x00000000
#define BCHP_MDI_TOP_0_MODE_CONTROL_0_ON_SCREEN_STATUS_ENABLE_OFF  0
#define BCHP_MDI_TOP_0_MODE_CONTROL_0_ON_SCREEN_STATUS_ENABLE_ON   1

/***************************************************************************
 *SRC_PIC_SIZE - MADR Source Picture Size Information
 ***************************************************************************/
/* MDI_TOP_0 :: SRC_PIC_SIZE :: reserved0 [31:27] */
#define BCHP_MDI_TOP_0_SRC_PIC_SIZE_reserved0_MASK                 0xf8000000
#define BCHP_MDI_TOP_0_SRC_PIC_SIZE_reserved0_SHIFT                27

/* MDI_TOP_0 :: SRC_PIC_SIZE :: HSIZE [26:16] */
#define BCHP_MDI_TOP_0_SRC_PIC_SIZE_HSIZE_MASK                     0x07ff0000
#define BCHP_MDI_TOP_0_SRC_PIC_SIZE_HSIZE_SHIFT                    16
#define BCHP_MDI_TOP_0_SRC_PIC_SIZE_HSIZE_DEFAULT                  0x000002d0

/* MDI_TOP_0 :: SRC_PIC_SIZE :: reserved1 [15:12] */
#define BCHP_MDI_TOP_0_SRC_PIC_SIZE_reserved1_MASK                 0x0000f000
#define BCHP_MDI_TOP_0_SRC_PIC_SIZE_reserved1_SHIFT                12

/* MDI_TOP_0 :: SRC_PIC_SIZE :: VSIZE [11:00] */
#define BCHP_MDI_TOP_0_SRC_PIC_SIZE_VSIZE_MASK                     0x00000fff
#define BCHP_MDI_TOP_0_SRC_PIC_SIZE_VSIZE_SHIFT                    0
#define BCHP_MDI_TOP_0_SRC_PIC_SIZE_VSIZE_DEFAULT                  0x000000f0

/***************************************************************************
 *PIXEL_FIELD_MSTART_0 - MAD-R Pixel Field 0 Buffer Starting Address
 ***************************************************************************/
/* MDI_TOP_0 :: PIXEL_FIELD_MSTART_0 :: ADDRESS [31:05] */
#define BCHP_MDI_TOP_0_PIXEL_FIELD_MSTART_0_ADDRESS_MASK           0xffffffe0
#define BCHP_MDI_TOP_0_PIXEL_FIELD_MSTART_0_ADDRESS_SHIFT          5
#define BCHP_MDI_TOP_0_PIXEL_FIELD_MSTART_0_ADDRESS_DEFAULT        0x00000000

/* MDI_TOP_0 :: PIXEL_FIELD_MSTART_0 :: reserved0 [04:00] */
#define BCHP_MDI_TOP_0_PIXEL_FIELD_MSTART_0_reserved0_MASK         0x0000001f
#define BCHP_MDI_TOP_0_PIXEL_FIELD_MSTART_0_reserved0_SHIFT        0

/***************************************************************************
 *PIXEL_FIELD_MSTART_1 - MAD-R Pixel Field 1 Buffer Starting Address
 ***************************************************************************/
/* MDI_TOP_0 :: PIXEL_FIELD_MSTART_1 :: ADDRESS [31:05] */
#define BCHP_MDI_TOP_0_PIXEL_FIELD_MSTART_1_ADDRESS_MASK           0xffffffe0
#define BCHP_MDI_TOP_0_PIXEL_FIELD_MSTART_1_ADDRESS_SHIFT          5
#define BCHP_MDI_TOP_0_PIXEL_FIELD_MSTART_1_ADDRESS_DEFAULT        0x00000000

/* MDI_TOP_0 :: PIXEL_FIELD_MSTART_1 :: reserved0 [04:00] */
#define BCHP_MDI_TOP_0_PIXEL_FIELD_MSTART_1_reserved0_MASK         0x0000001f
#define BCHP_MDI_TOP_0_PIXEL_FIELD_MSTART_1_reserved0_SHIFT        0

/***************************************************************************
 *PIXEL_FIELD_MSTART_2 - MAD-R Pixel Field 2 Buffer Starting Address
 ***************************************************************************/
/* MDI_TOP_0 :: PIXEL_FIELD_MSTART_2 :: ADDRESS [31:05] */
#define BCHP_MDI_TOP_0_PIXEL_FIELD_MSTART_2_ADDRESS_MASK           0xffffffe0
#define BCHP_MDI_TOP_0_PIXEL_FIELD_MSTART_2_ADDRESS_SHIFT          5
#define BCHP_MDI_TOP_0_PIXEL_FIELD_MSTART_2_ADDRESS_DEFAULT        0x00000000

/* MDI_TOP_0 :: PIXEL_FIELD_MSTART_2 :: reserved0 [04:00] */
#define BCHP_MDI_TOP_0_PIXEL_FIELD_MSTART_2_reserved0_MASK         0x0000001f
#define BCHP_MDI_TOP_0_PIXEL_FIELD_MSTART_2_reserved0_SHIFT        0

/***************************************************************************
 *OSD_POSITION - MADR On Screen Display Position
 ***************************************************************************/
/* MDI_TOP_0 :: OSD_POSITION :: reserved0 [31:27] */
#define BCHP_MDI_TOP_0_OSD_POSITION_reserved0_MASK                 0xf8000000
#define BCHP_MDI_TOP_0_OSD_POSITION_reserved0_SHIFT                27

/* MDI_TOP_0 :: OSD_POSITION :: HPOS [26:16] */
#define BCHP_MDI_TOP_0_OSD_POSITION_HPOS_MASK                      0x07ff0000
#define BCHP_MDI_TOP_0_OSD_POSITION_HPOS_SHIFT                     16
#define BCHP_MDI_TOP_0_OSD_POSITION_HPOS_DEFAULT                   0x00000168

/* MDI_TOP_0 :: OSD_POSITION :: reserved1 [15:12] */
#define BCHP_MDI_TOP_0_OSD_POSITION_reserved1_MASK                 0x0000f000
#define BCHP_MDI_TOP_0_OSD_POSITION_reserved1_SHIFT                12

/* MDI_TOP_0 :: OSD_POSITION :: VPOS [11:00] */
#define BCHP_MDI_TOP_0_OSD_POSITION_VPOS_MASK                      0x00000fff
#define BCHP_MDI_TOP_0_OSD_POSITION_VPOS_SHIFT                     0
#define BCHP_MDI_TOP_0_OSD_POSITION_VPOS_DEFAULT                   0x00000002

/***************************************************************************
 *BVB_IN_STATUS - MADR Broadcom Video Bus Input Status
 ***************************************************************************/
/* MDI_TOP_0 :: BVB_IN_STATUS :: reserved0 [31:08] */
#define BCHP_MDI_TOP_0_BVB_IN_STATUS_reserved0_MASK                0xffffff00
#define BCHP_MDI_TOP_0_BVB_IN_STATUS_reserved0_SHIFT               8

/* MDI_TOP_0 :: BVB_IN_STATUS :: ENABLE_ERROR [07:07] */
#define BCHP_MDI_TOP_0_BVB_IN_STATUS_ENABLE_ERROR_MASK             0x00000080
#define BCHP_MDI_TOP_0_BVB_IN_STATUS_ENABLE_ERROR_SHIFT            7

/* MDI_TOP_0 :: BVB_IN_STATUS :: reserved1 [06:05] */
#define BCHP_MDI_TOP_0_BVB_IN_STATUS_reserved1_MASK                0x00000060
#define BCHP_MDI_TOP_0_BVB_IN_STATUS_reserved1_SHIFT               5

/* MDI_TOP_0 :: BVB_IN_STATUS :: MISSING_SYNC [04:04] */
#define BCHP_MDI_TOP_0_BVB_IN_STATUS_MISSING_SYNC_MASK             0x00000010
#define BCHP_MDI_TOP_0_BVB_IN_STATUS_MISSING_SYNC_SHIFT            4

/* MDI_TOP_0 :: BVB_IN_STATUS :: LONG_SOURCE [03:03] */
#define BCHP_MDI_TOP_0_BVB_IN_STATUS_LONG_SOURCE_MASK              0x00000008
#define BCHP_MDI_TOP_0_BVB_IN_STATUS_LONG_SOURCE_SHIFT             3

/* MDI_TOP_0 :: BVB_IN_STATUS :: SHORT_SOURCE [02:02] */
#define BCHP_MDI_TOP_0_BVB_IN_STATUS_SHORT_SOURCE_MASK             0x00000004
#define BCHP_MDI_TOP_0_BVB_IN_STATUS_SHORT_SOURCE_SHIFT            2

/* MDI_TOP_0 :: BVB_IN_STATUS :: LONG_LINE [01:01] */
#define BCHP_MDI_TOP_0_BVB_IN_STATUS_LONG_LINE_MASK                0x00000002
#define BCHP_MDI_TOP_0_BVB_IN_STATUS_LONG_LINE_SHIFT               1

/* MDI_TOP_0 :: BVB_IN_STATUS :: SHORT_LINE [00:00] */
#define BCHP_MDI_TOP_0_BVB_IN_STATUS_SHORT_LINE_MASK               0x00000001
#define BCHP_MDI_TOP_0_BVB_IN_STATUS_SHORT_LINE_SHIFT              0

/***************************************************************************
 *BVB_IN_STATUS_CLEAR - MADR Broadcom Video Bus Input Status Clear
 ***************************************************************************/
/* MDI_TOP_0 :: BVB_IN_STATUS_CLEAR :: reserved0 [31:08] */
#define BCHP_MDI_TOP_0_BVB_IN_STATUS_CLEAR_reserved0_MASK          0xffffff00
#define BCHP_MDI_TOP_0_BVB_IN_STATUS_CLEAR_reserved0_SHIFT         8

/* MDI_TOP_0 :: BVB_IN_STATUS_CLEAR :: ENABLE_ERROR [07:07] */
#define BCHP_MDI_TOP_0_BVB_IN_STATUS_CLEAR_ENABLE_ERROR_MASK       0x00000080
#define BCHP_MDI_TOP_0_BVB_IN_STATUS_CLEAR_ENABLE_ERROR_SHIFT      7
#define BCHP_MDI_TOP_0_BVB_IN_STATUS_CLEAR_ENABLE_ERROR_DEFAULT    0x00000000

/* MDI_TOP_0 :: BVB_IN_STATUS_CLEAR :: reserved1 [06:05] */
#define BCHP_MDI_TOP_0_BVB_IN_STATUS_CLEAR_reserved1_MASK          0x00000060
#define BCHP_MDI_TOP_0_BVB_IN_STATUS_CLEAR_reserved1_SHIFT         5

/* MDI_TOP_0 :: BVB_IN_STATUS_CLEAR :: MISSING_SYNC [04:04] */
#define BCHP_MDI_TOP_0_BVB_IN_STATUS_CLEAR_MISSING_SYNC_MASK       0x00000010
#define BCHP_MDI_TOP_0_BVB_IN_STATUS_CLEAR_MISSING_SYNC_SHIFT      4
#define BCHP_MDI_TOP_0_BVB_IN_STATUS_CLEAR_MISSING_SYNC_DEFAULT    0x00000000

/* MDI_TOP_0 :: BVB_IN_STATUS_CLEAR :: LONG_SOURCE [03:03] */
#define BCHP_MDI_TOP_0_BVB_IN_STATUS_CLEAR_LONG_SOURCE_MASK        0x00000008
#define BCHP_MDI_TOP_0_BVB_IN_STATUS_CLEAR_LONG_SOURCE_SHIFT       3
#define BCHP_MDI_TOP_0_BVB_IN_STATUS_CLEAR_LONG_SOURCE_DEFAULT     0x00000000

/* MDI_TOP_0 :: BVB_IN_STATUS_CLEAR :: SHORT_SOURCE [02:02] */
#define BCHP_MDI_TOP_0_BVB_IN_STATUS_CLEAR_SHORT_SOURCE_MASK       0x00000004
#define BCHP_MDI_TOP_0_BVB_IN_STATUS_CLEAR_SHORT_SOURCE_SHIFT      2
#define BCHP_MDI_TOP_0_BVB_IN_STATUS_CLEAR_SHORT_SOURCE_DEFAULT    0x00000000

/* MDI_TOP_0 :: BVB_IN_STATUS_CLEAR :: LONG_LINE [01:01] */
#define BCHP_MDI_TOP_0_BVB_IN_STATUS_CLEAR_LONG_LINE_MASK          0x00000002
#define BCHP_MDI_TOP_0_BVB_IN_STATUS_CLEAR_LONG_LINE_SHIFT         1
#define BCHP_MDI_TOP_0_BVB_IN_STATUS_CLEAR_LONG_LINE_DEFAULT       0x00000000

/* MDI_TOP_0 :: BVB_IN_STATUS_CLEAR :: SHORT_LINE [00:00] */
#define BCHP_MDI_TOP_0_BVB_IN_STATUS_CLEAR_SHORT_LINE_MASK         0x00000001
#define BCHP_MDI_TOP_0_BVB_IN_STATUS_CLEAR_SHORT_LINE_SHIFT        0
#define BCHP_MDI_TOP_0_BVB_IN_STATUS_CLEAR_SHORT_LINE_DEFAULT      0x00000000

/***************************************************************************
 *TEST_PORT_DATA - Testport data register
 ***************************************************************************/
/* MDI_TOP_0 :: TEST_PORT_DATA :: VALUE [31:00] */
#define BCHP_MDI_TOP_0_TEST_PORT_DATA_VALUE_MASK                   0xffffffff
#define BCHP_MDI_TOP_0_TEST_PORT_DATA_VALUE_SHIFT                  0
#define BCHP_MDI_TOP_0_TEST_PORT_DATA_VALUE_DEFAULT                0x00000000

/***************************************************************************
 *TEST_PORT_CONTROL - Testportl control register
 ***************************************************************************/
/* MDI_TOP_0 :: TEST_PORT_CONTROL :: reserved0 [31:03] */
#define BCHP_MDI_TOP_0_TEST_PORT_CONTROL_reserved0_MASK            0xfffffff8
#define BCHP_MDI_TOP_0_TEST_PORT_CONTROL_reserved0_SHIFT           3

/* MDI_TOP_0 :: TEST_PORT_CONTROL :: TP_ADDR [02:00] */
#define BCHP_MDI_TOP_0_TEST_PORT_CONTROL_TP_ADDR_MASK              0x00000007
#define BCHP_MDI_TOP_0_TEST_PORT_CONTROL_TP_ADDR_SHIFT             0
#define BCHP_MDI_TOP_0_TEST_PORT_CONTROL_TP_ADDR_DEFAULT           0x00000000
#define BCHP_MDI_TOP_0_TEST_PORT_CONTROL_TP_ADDR_FCB_0             0
#define BCHP_MDI_TOP_0_TEST_PORT_CONTROL_TP_ADDR_FCB_1             1
#define BCHP_MDI_TOP_0_TEST_PORT_CONTROL_TP_ADDR_FCB_2             2
#define BCHP_MDI_TOP_0_TEST_PORT_CONTROL_TP_ADDR_PDB_0             3
#define BCHP_MDI_TOP_0_TEST_PORT_CONTROL_TP_ADDR_PDB_1             4
#define BCHP_MDI_TOP_0_TEST_PORT_CONTROL_TP_ADDR_PPB               5
#define BCHP_MDI_TOP_0_TEST_PORT_CONTROL_TP_ADDR_BIC               6
#define BCHP_MDI_TOP_0_TEST_PORT_CONTROL_TP_ADDR_BOC               7

/***************************************************************************
 *QM_FIELD_MSTART_1 - MADR Quantized Motion Field 1 Buffer Starting Address
 ***************************************************************************/
/* MDI_TOP_0 :: QM_FIELD_MSTART_1 :: ADDRESS [31:05] */
#define BCHP_MDI_TOP_0_QM_FIELD_MSTART_1_ADDRESS_MASK              0xffffffe0
#define BCHP_MDI_TOP_0_QM_FIELD_MSTART_1_ADDRESS_SHIFT             5
#define BCHP_MDI_TOP_0_QM_FIELD_MSTART_1_ADDRESS_DEFAULT           0x00000000

/* MDI_TOP_0 :: QM_FIELD_MSTART_1 :: reserved0 [04:00] */
#define BCHP_MDI_TOP_0_QM_FIELD_MSTART_1_reserved0_MASK            0x0000001f
#define BCHP_MDI_TOP_0_QM_FIELD_MSTART_1_reserved0_SHIFT           0

/***************************************************************************
 *QM_FIELD_MSTART_2 - MADR Quantized Motion Field 2 Buffer Starting Address
 ***************************************************************************/
/* MDI_TOP_0 :: QM_FIELD_MSTART_2 :: ADDRESS [31:05] */
#define BCHP_MDI_TOP_0_QM_FIELD_MSTART_2_ADDRESS_MASK              0xffffffe0
#define BCHP_MDI_TOP_0_QM_FIELD_MSTART_2_ADDRESS_SHIFT             5
#define BCHP_MDI_TOP_0_QM_FIELD_MSTART_2_ADDRESS_DEFAULT           0x00000000

/* MDI_TOP_0 :: QM_FIELD_MSTART_2 :: reserved0 [04:00] */
#define BCHP_MDI_TOP_0_QM_FIELD_MSTART_2_reserved0_MASK            0x0000001f
#define BCHP_MDI_TOP_0_QM_FIELD_MSTART_2_reserved0_SHIFT           0

/***************************************************************************
 *QM_FIELD_MSTART_3 - MADR Quantized Motion Field 3 Buffer Starting Address
 ***************************************************************************/
/* MDI_TOP_0 :: QM_FIELD_MSTART_3 :: ADDRESS [31:05] */
#define BCHP_MDI_TOP_0_QM_FIELD_MSTART_3_ADDRESS_MASK              0xffffffe0
#define BCHP_MDI_TOP_0_QM_FIELD_MSTART_3_ADDRESS_SHIFT             5
#define BCHP_MDI_TOP_0_QM_FIELD_MSTART_3_ADDRESS_DEFAULT           0x00000000

/* MDI_TOP_0 :: QM_FIELD_MSTART_3 :: reserved0 [04:00] */
#define BCHP_MDI_TOP_0_QM_FIELD_MSTART_3_reserved0_MASK            0x0000001f
#define BCHP_MDI_TOP_0_QM_FIELD_MSTART_3_reserved0_SHIFT           0

/***************************************************************************
 *QM_FIELD_MSTART_4 - MADR Quantized Motion Field 4 Buffer Starting Address
 ***************************************************************************/
/* MDI_TOP_0 :: QM_FIELD_MSTART_4 :: ADDRESS [31:05] */
#define BCHP_MDI_TOP_0_QM_FIELD_MSTART_4_ADDRESS_MASK              0xffffffe0
#define BCHP_MDI_TOP_0_QM_FIELD_MSTART_4_ADDRESS_SHIFT             5
#define BCHP_MDI_TOP_0_QM_FIELD_MSTART_4_ADDRESS_DEFAULT           0x00000000

/* MDI_TOP_0 :: QM_FIELD_MSTART_4 :: reserved0 [04:00] */
#define BCHP_MDI_TOP_0_QM_FIELD_MSTART_4_reserved0_MASK            0x0000001f
#define BCHP_MDI_TOP_0_QM_FIELD_MSTART_4_reserved0_SHIFT           0

#endif /* #ifndef BCHP_MDI_TOP_0_H__ */

/* End of File */

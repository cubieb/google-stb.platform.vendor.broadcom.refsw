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
 * Date:           Generated on         Mon Jul 23 11:55:15 2007
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

#ifndef BCHP_BSP_GLB_CONTROL_H__
#define BCHP_BSP_GLB_CONTROL_H__

/***************************************************************************
 *BSP_GLB_CONTROL - BSP GLOBAL Control Register
 ***************************************************************************/
#define BCHP_BSP_GLB_CONTROL_GLB_REVISION        0x0030b000 /* Revision Register */
#define BCHP_BSP_GLB_CONTROL_GLB_TIMER           0x0030b004 /* Timer */
#define BCHP_BSP_GLB_CONTROL_GLB_IRDY            0x0030b008 /* Input Command Buffer Ready */
#define BCHP_BSP_GLB_CONTROL_GLB_ORDY            0x0030b00c /* Output Command Buffer Ready */
#define BCHP_BSP_GLB_CONTROL_GLB_HOST_INTR_STATUS 0x0030b010 /* Host CPU Interrupt Status */
#define BCHP_BSP_GLB_CONTROL_GLB_HOST_INTR_EN    0x0030b014 /* Host CPU Interrupt Enable */
#define BCHP_BSP_GLB_CONTROL_GLB_OLOAD2          0x0030b020 /* Output Command Buffer 2 Loaded */
#define BCHP_BSP_GLB_CONTROL_GLB_OLOAD1          0x0030b024 /* Output Command Buffer 1 Loaded */
#define BCHP_BSP_GLB_CONTROL_GLB_ILOAD2          0x0030b028 /* Input Command Buffer 2 Loaded */
#define BCHP_BSP_GLB_CONTROL_GLB_ILOAD1          0x0030b02c /* Input Command Buffer 1 Loaded */
#define BCHP_BSP_GLB_CONTROL_OTP_TP_SEL          0x0030b030 /* OTP Wrapper Test Output Port Selection Register */
#define BCHP_BSP_GLB_CONTROL_HOST_TO_BSP_GENERAL_INTR 0x0030b034 /* HOST to BSP Processor General Interrupt Trigger Register */
#define BCHP_BSP_GLB_CONTROL_OTP_WDATA0          0x0030b038 /* OTP Write Data */
#define BCHP_BSP_GLB_CONTROL_OTP_WDATA1          0x0030b03c /* OTP Write Data */
#define BCHP_BSP_GLB_CONTROL_OTP_WDATA2          0x0030b040 /* OTP Write Data */
#define BCHP_BSP_GLB_CONTROL_OTP_WDATA3          0x0030b044 /* OTP Write Data */
#define BCHP_BSP_GLB_CONTROL_OTP_WDATA4          0x0030b048 /* OTP Write Data */
#define BCHP_BSP_GLB_CONTROL_OTP_WDATA5          0x0030b04c /* OTP Write Data */
#define BCHP_BSP_GLB_CONTROL_OTP_WDATA6          0x0030b050 /* OTP Write Data */
#define BCHP_BSP_GLB_CONTROL_OTP_WDATA7          0x0030b054 /* OTP Write Data */
#define BCHP_BSP_GLB_CONTROL_GLB_OLOAD_CR        0x0030b058 /* Challenge/Response Output Command Buffer Loaded */
#define BCHP_BSP_GLB_CONTROL_GLB_ILOAD_CR        0x0030b05c /* Challenge/Response Input Command Buffer Loaded */
#define BCHP_BSP_GLB_CONTROL_GLB_MEM0            0x0030b060 /* TM Memory Control Register */
#define BCHP_BSP_GLB_CONTROL_GLB_MEM1            0x0030b064 /* TM Memory Control Register */
#define BCHP_BSP_GLB_CONTROL_GLB_MEM2            0x0030b068 /* TM Memory Control Register */
#define BCHP_BSP_GLB_CONTROL_GLB_MEM3            0x0030b06c /* TM Memory Control Register */
#define BCHP_BSP_GLB_CONTROL_GLB_DWNLD_ERR       0x0030b070 /* Download Error flags */
#define BCHP_BSP_GLB_CONTROL_GLB_DWNLD_STATUS    0x0030b074 /* Download Status flags */

/***************************************************************************
 *GLB_REVISION - Revision Register
 ***************************************************************************/
/* BSP_GLB_CONTROL :: GLB_REVISION :: reserved0 [31:16] */
#define BCHP_BSP_GLB_CONTROL_GLB_REVISION_reserved0_MASK           0xffff0000
#define BCHP_BSP_GLB_CONTROL_GLB_REVISION_reserved0_SHIFT          16

/* BSP_GLB_CONTROL :: GLB_REVISION :: MAJOR_REV_NUMBER [15:08] */
#define BCHP_BSP_GLB_CONTROL_GLB_REVISION_MAJOR_REV_NUMBER_MASK    0x0000ff00
#define BCHP_BSP_GLB_CONTROL_GLB_REVISION_MAJOR_REV_NUMBER_SHIFT   8

/* BSP_GLB_CONTROL :: GLB_REVISION :: MINOR_REV_NUMBER [07:00] */
#define BCHP_BSP_GLB_CONTROL_GLB_REVISION_MINOR_REV_NUMBER_MASK    0x000000ff
#define BCHP_BSP_GLB_CONTROL_GLB_REVISION_MINOR_REV_NUMBER_SHIFT   0

/***************************************************************************
 *GLB_TIMER - Timer
 ***************************************************************************/
/* BSP_GLB_CONTROL :: GLB_TIMER :: TIMER [31:00] */
#define BCHP_BSP_GLB_CONTROL_GLB_TIMER_TIMER_MASK                  0xffffffff
#define BCHP_BSP_GLB_CONTROL_GLB_TIMER_TIMER_SHIFT                 0

/***************************************************************************
 *GLB_IRDY - Input Command Buffer Ready
 ***************************************************************************/
/* BSP_GLB_CONTROL :: GLB_IRDY :: reserved0 [31:03] */
#define BCHP_BSP_GLB_CONTROL_GLB_IRDY_reserved0_MASK               0xfffffff8
#define BCHP_BSP_GLB_CONTROL_GLB_IRDY_reserved0_SHIFT              3

/* BSP_GLB_CONTROL :: GLB_IRDY :: CMD_IDRY_CR [02:02] */
#define BCHP_BSP_GLB_CONTROL_GLB_IRDY_CMD_IDRY_CR_MASK             0x00000004
#define BCHP_BSP_GLB_CONTROL_GLB_IRDY_CMD_IDRY_CR_SHIFT            2

/* BSP_GLB_CONTROL :: GLB_IRDY :: CMD_IDRY2 [01:01] */
#define BCHP_BSP_GLB_CONTROL_GLB_IRDY_CMD_IDRY2_MASK               0x00000002
#define BCHP_BSP_GLB_CONTROL_GLB_IRDY_CMD_IDRY2_SHIFT              1

/* BSP_GLB_CONTROL :: GLB_IRDY :: CMD_IDRY1 [00:00] */
#define BCHP_BSP_GLB_CONTROL_GLB_IRDY_CMD_IDRY1_MASK               0x00000001
#define BCHP_BSP_GLB_CONTROL_GLB_IRDY_CMD_IDRY1_SHIFT              0

/***************************************************************************
 *GLB_ORDY - Output Command Buffer Ready
 ***************************************************************************/
/* BSP_GLB_CONTROL :: GLB_ORDY :: reserved0 [31:03] */
#define BCHP_BSP_GLB_CONTROL_GLB_ORDY_reserved0_MASK               0xfffffff8
#define BCHP_BSP_GLB_CONTROL_GLB_ORDY_reserved0_SHIFT              3

/* BSP_GLB_CONTROL :: GLB_ORDY :: CMD_ODRY_CR [02:02] */
#define BCHP_BSP_GLB_CONTROL_GLB_ORDY_CMD_ODRY_CR_MASK             0x00000004
#define BCHP_BSP_GLB_CONTROL_GLB_ORDY_CMD_ODRY_CR_SHIFT            2

/* BSP_GLB_CONTROL :: GLB_ORDY :: CMD_ODRY2 [01:01] */
#define BCHP_BSP_GLB_CONTROL_GLB_ORDY_CMD_ODRY2_MASK               0x00000002
#define BCHP_BSP_GLB_CONTROL_GLB_ORDY_CMD_ODRY2_SHIFT              1

/* BSP_GLB_CONTROL :: GLB_ORDY :: CMD_ODRY1 [00:00] */
#define BCHP_BSP_GLB_CONTROL_GLB_ORDY_CMD_ODRY1_MASK               0x00000001
#define BCHP_BSP_GLB_CONTROL_GLB_ORDY_CMD_ODRY1_SHIFT              0

/***************************************************************************
 *GLB_HOST_INTR_STATUS - Host CPU Interrupt Status
 ***************************************************************************/
/* BSP_GLB_CONTROL :: GLB_HOST_INTR_STATUS :: reserved0 [31:03] */
#define BCHP_BSP_GLB_CONTROL_GLB_HOST_INTR_STATUS_reserved0_MASK   0xfffffff8
#define BCHP_BSP_GLB_CONTROL_GLB_HOST_INTR_STATUS_reserved0_SHIFT  3

/* BSP_GLB_CONTROL :: GLB_HOST_INTR_STATUS :: OLOAD_CR_INT [02:02] */
#define BCHP_BSP_GLB_CONTROL_GLB_HOST_INTR_STATUS_OLOAD_CR_INT_MASK 0x00000004
#define BCHP_BSP_GLB_CONTROL_GLB_HOST_INTR_STATUS_OLOAD_CR_INT_SHIFT 2

/* BSP_GLB_CONTROL :: GLB_HOST_INTR_STATUS :: OLOAD2_INT [01:01] */
#define BCHP_BSP_GLB_CONTROL_GLB_HOST_INTR_STATUS_OLOAD2_INT_MASK  0x00000002
#define BCHP_BSP_GLB_CONTROL_GLB_HOST_INTR_STATUS_OLOAD2_INT_SHIFT 1

/* BSP_GLB_CONTROL :: GLB_HOST_INTR_STATUS :: OLOAD1_INT [00:00] */
#define BCHP_BSP_GLB_CONTROL_GLB_HOST_INTR_STATUS_OLOAD1_INT_MASK  0x00000001
#define BCHP_BSP_GLB_CONTROL_GLB_HOST_INTR_STATUS_OLOAD1_INT_SHIFT 0

/***************************************************************************
 *GLB_HOST_INTR_EN - Host CPU Interrupt Enable
 ***************************************************************************/
/* BSP_GLB_CONTROL :: GLB_HOST_INTR_EN :: reserved0 [31:02] */
#define BCHP_BSP_GLB_CONTROL_GLB_HOST_INTR_EN_reserved0_MASK       0xfffffffc
#define BCHP_BSP_GLB_CONTROL_GLB_HOST_INTR_EN_reserved0_SHIFT      2

/* BSP_GLB_CONTROL :: GLB_HOST_INTR_EN :: HOST_INTR_STATUS_EN [01:00] */
#define BCHP_BSP_GLB_CONTROL_GLB_HOST_INTR_EN_HOST_INTR_STATUS_EN_MASK 0x00000003
#define BCHP_BSP_GLB_CONTROL_GLB_HOST_INTR_EN_HOST_INTR_STATUS_EN_SHIFT 0

/***************************************************************************
 *GLB_OLOAD2 - Output Command Buffer 2 Loaded
 ***************************************************************************/
/* BSP_GLB_CONTROL :: GLB_OLOAD2 :: reserved0 [31:01] */
#define BCHP_BSP_GLB_CONTROL_GLB_OLOAD2_reserved0_MASK             0xfffffffe
#define BCHP_BSP_GLB_CONTROL_GLB_OLOAD2_reserved0_SHIFT            1

/* BSP_GLB_CONTROL :: GLB_OLOAD2 :: CMD_OLOAD2 [00:00] */
#define BCHP_BSP_GLB_CONTROL_GLB_OLOAD2_CMD_OLOAD2_MASK            0x00000001
#define BCHP_BSP_GLB_CONTROL_GLB_OLOAD2_CMD_OLOAD2_SHIFT           0

/***************************************************************************
 *GLB_OLOAD1 - Output Command Buffer 1 Loaded
 ***************************************************************************/
/* BSP_GLB_CONTROL :: GLB_OLOAD1 :: reserved0 [31:01] */
#define BCHP_BSP_GLB_CONTROL_GLB_OLOAD1_reserved0_MASK             0xfffffffe
#define BCHP_BSP_GLB_CONTROL_GLB_OLOAD1_reserved0_SHIFT            1

/* BSP_GLB_CONTROL :: GLB_OLOAD1 :: CMD_OLOAD1 [00:00] */
#define BCHP_BSP_GLB_CONTROL_GLB_OLOAD1_CMD_OLOAD1_MASK            0x00000001
#define BCHP_BSP_GLB_CONTROL_GLB_OLOAD1_CMD_OLOAD1_SHIFT           0

/***************************************************************************
 *GLB_ILOAD2 - Input Command Buffer 2 Loaded
 ***************************************************************************/
/* BSP_GLB_CONTROL :: GLB_ILOAD2 :: reserved0 [31:01] */
#define BCHP_BSP_GLB_CONTROL_GLB_ILOAD2_reserved0_MASK             0xfffffffe
#define BCHP_BSP_GLB_CONTROL_GLB_ILOAD2_reserved0_SHIFT            1

/* BSP_GLB_CONTROL :: GLB_ILOAD2 :: CMD_ILOAD2 [00:00] */
#define BCHP_BSP_GLB_CONTROL_GLB_ILOAD2_CMD_ILOAD2_MASK            0x00000001
#define BCHP_BSP_GLB_CONTROL_GLB_ILOAD2_CMD_ILOAD2_SHIFT           0

/***************************************************************************
 *GLB_ILOAD1 - Input Command Buffer 1 Loaded
 ***************************************************************************/
/* BSP_GLB_CONTROL :: GLB_ILOAD1 :: reserved0 [31:01] */
#define BCHP_BSP_GLB_CONTROL_GLB_ILOAD1_reserved0_MASK             0xfffffffe
#define BCHP_BSP_GLB_CONTROL_GLB_ILOAD1_reserved0_SHIFT            1

/* BSP_GLB_CONTROL :: GLB_ILOAD1 :: CMD_ILOAD1 [00:00] */
#define BCHP_BSP_GLB_CONTROL_GLB_ILOAD1_CMD_ILOAD1_MASK            0x00000001
#define BCHP_BSP_GLB_CONTROL_GLB_ILOAD1_CMD_ILOAD1_SHIFT           0

/***************************************************************************
 *OTP_TP_SEL - OTP Wrapper Test Output Port Selection Register
 ***************************************************************************/
/* BSP_GLB_CONTROL :: OTP_TP_SEL :: reserved0 [31:03] */
#define BCHP_BSP_GLB_CONTROL_OTP_TP_SEL_reserved0_MASK             0xfffffff8
#define BCHP_BSP_GLB_CONTROL_OTP_TP_SEL_reserved0_SHIFT            3

/* BSP_GLB_CONTROL :: OTP_TP_SEL :: TP_SEL [02:00] */
#define BCHP_BSP_GLB_CONTROL_OTP_TP_SEL_TP_SEL_MASK                0x00000007
#define BCHP_BSP_GLB_CONTROL_OTP_TP_SEL_TP_SEL_SHIFT               0

/***************************************************************************
 *HOST_TO_BSP_GENERAL_INTR - HOST to BSP Processor General Interrupt Trigger Register
 ***************************************************************************/
/* BSP_GLB_CONTROL :: HOST_TO_BSP_GENERAL_INTR :: reserved0 [31:01] */
#define BCHP_BSP_GLB_CONTROL_HOST_TO_BSP_GENERAL_INTR_reserved0_MASK 0xfffffffe
#define BCHP_BSP_GLB_CONTROL_HOST_TO_BSP_GENERAL_INTR_reserved0_SHIFT 1

/* BSP_GLB_CONTROL :: HOST_TO_BSP_GENERAL_INTR :: HOST_TO_BSP_INTR [00:00] */
#define BCHP_BSP_GLB_CONTROL_HOST_TO_BSP_GENERAL_INTR_HOST_TO_BSP_INTR_MASK 0x00000001
#define BCHP_BSP_GLB_CONTROL_HOST_TO_BSP_GENERAL_INTR_HOST_TO_BSP_INTR_SHIFT 0

/***************************************************************************
 *OTP_WDATA0 - OTP Write Data
 ***************************************************************************/
/* BSP_GLB_CONTROL :: OTP_WDATA0 :: reserved0 [31:26] */
#define BCHP_BSP_GLB_CONTROL_OTP_WDATA0_reserved0_MASK             0xfc000000
#define BCHP_BSP_GLB_CONTROL_OTP_WDATA0_reserved0_SHIFT            26

/* BSP_GLB_CONTROL :: OTP_WDATA0 :: WRITE_DATA_0 [25:00] */
#define BCHP_BSP_GLB_CONTROL_OTP_WDATA0_WRITE_DATA_0_MASK          0x03ffffff
#define BCHP_BSP_GLB_CONTROL_OTP_WDATA0_WRITE_DATA_0_SHIFT         0

/***************************************************************************
 *OTP_WDATA1 - OTP Write Data
 ***************************************************************************/
/* BSP_GLB_CONTROL :: OTP_WDATA1 :: reserved0 [31:28] */
#define BCHP_BSP_GLB_CONTROL_OTP_WDATA1_reserved0_MASK             0xf0000000
#define BCHP_BSP_GLB_CONTROL_OTP_WDATA1_reserved0_SHIFT            28

/* BSP_GLB_CONTROL :: OTP_WDATA1 :: WRITE_DATA_1 [27:00] */
#define BCHP_BSP_GLB_CONTROL_OTP_WDATA1_WRITE_DATA_1_MASK          0x0fffffff
#define BCHP_BSP_GLB_CONTROL_OTP_WDATA1_WRITE_DATA_1_SHIFT         0

/***************************************************************************
 *OTP_WDATA2 - OTP Write Data
 ***************************************************************************/
/* BSP_GLB_CONTROL :: OTP_WDATA2 :: reserved0 [31:26] */
#define BCHP_BSP_GLB_CONTROL_OTP_WDATA2_reserved0_MASK             0xfc000000
#define BCHP_BSP_GLB_CONTROL_OTP_WDATA2_reserved0_SHIFT            26

/* BSP_GLB_CONTROL :: OTP_WDATA2 :: WRITE_DATA_2 [25:00] */
#define BCHP_BSP_GLB_CONTROL_OTP_WDATA2_WRITE_DATA_2_MASK          0x03ffffff
#define BCHP_BSP_GLB_CONTROL_OTP_WDATA2_WRITE_DATA_2_SHIFT         0

/***************************************************************************
 *OTP_WDATA3 - OTP Write Data
 ***************************************************************************/
/* BSP_GLB_CONTROL :: OTP_WDATA3 :: reserved0 [31:28] */
#define BCHP_BSP_GLB_CONTROL_OTP_WDATA3_reserved0_MASK             0xf0000000
#define BCHP_BSP_GLB_CONTROL_OTP_WDATA3_reserved0_SHIFT            28

/* BSP_GLB_CONTROL :: OTP_WDATA3 :: WRITE_DATA_3 [27:00] */
#define BCHP_BSP_GLB_CONTROL_OTP_WDATA3_WRITE_DATA_3_MASK          0x0fffffff
#define BCHP_BSP_GLB_CONTROL_OTP_WDATA3_WRITE_DATA_3_SHIFT         0

/***************************************************************************
 *OTP_WDATA4 - OTP Write Data
 ***************************************************************************/
/* BSP_GLB_CONTROL :: OTP_WDATA4 :: reserved0 [31:26] */
#define BCHP_BSP_GLB_CONTROL_OTP_WDATA4_reserved0_MASK             0xfc000000
#define BCHP_BSP_GLB_CONTROL_OTP_WDATA4_reserved0_SHIFT            26

/* BSP_GLB_CONTROL :: OTP_WDATA4 :: WRITE_DATA_4 [25:00] */
#define BCHP_BSP_GLB_CONTROL_OTP_WDATA4_WRITE_DATA_4_MASK          0x03ffffff
#define BCHP_BSP_GLB_CONTROL_OTP_WDATA4_WRITE_DATA_4_SHIFT         0

/***************************************************************************
 *OTP_WDATA5 - OTP Write Data
 ***************************************************************************/
/* BSP_GLB_CONTROL :: OTP_WDATA5 :: reserved0 [31:28] */
#define BCHP_BSP_GLB_CONTROL_OTP_WDATA5_reserved0_MASK             0xf0000000
#define BCHP_BSP_GLB_CONTROL_OTP_WDATA5_reserved0_SHIFT            28

/* BSP_GLB_CONTROL :: OTP_WDATA5 :: WRITE_DATA_5 [27:00] */
#define BCHP_BSP_GLB_CONTROL_OTP_WDATA5_WRITE_DATA_5_MASK          0x0fffffff
#define BCHP_BSP_GLB_CONTROL_OTP_WDATA5_WRITE_DATA_5_SHIFT         0

/***************************************************************************
 *OTP_WDATA6 - OTP Write Data
 ***************************************************************************/
/* BSP_GLB_CONTROL :: OTP_WDATA6 :: reserved0 [31:26] */
#define BCHP_BSP_GLB_CONTROL_OTP_WDATA6_reserved0_MASK             0xfc000000
#define BCHP_BSP_GLB_CONTROL_OTP_WDATA6_reserved0_SHIFT            26

/* BSP_GLB_CONTROL :: OTP_WDATA6 :: WRITE_DATA_6 [25:00] */
#define BCHP_BSP_GLB_CONTROL_OTP_WDATA6_WRITE_DATA_6_MASK          0x03ffffff
#define BCHP_BSP_GLB_CONTROL_OTP_WDATA6_WRITE_DATA_6_SHIFT         0

/***************************************************************************
 *OTP_WDATA7 - OTP Write Data
 ***************************************************************************/
/* BSP_GLB_CONTROL :: OTP_WDATA7 :: reserved0 [31:28] */
#define BCHP_BSP_GLB_CONTROL_OTP_WDATA7_reserved0_MASK             0xf0000000
#define BCHP_BSP_GLB_CONTROL_OTP_WDATA7_reserved0_SHIFT            28

/* BSP_GLB_CONTROL :: OTP_WDATA7 :: WRITE_DATA_7 [27:00] */
#define BCHP_BSP_GLB_CONTROL_OTP_WDATA7_WRITE_DATA_7_MASK          0x0fffffff
#define BCHP_BSP_GLB_CONTROL_OTP_WDATA7_WRITE_DATA_7_SHIFT         0

/***************************************************************************
 *GLB_OLOAD_CR - Challenge/Response Output Command Buffer Loaded
 ***************************************************************************/
/* BSP_GLB_CONTROL :: GLB_OLOAD_CR :: reserved0 [31:01] */
#define BCHP_BSP_GLB_CONTROL_GLB_OLOAD_CR_reserved0_MASK           0xfffffffe
#define BCHP_BSP_GLB_CONTROL_GLB_OLOAD_CR_reserved0_SHIFT          1

/* BSP_GLB_CONTROL :: GLB_OLOAD_CR :: CMD_OLOAD_CR [00:00] */
#define BCHP_BSP_GLB_CONTROL_GLB_OLOAD_CR_CMD_OLOAD_CR_MASK        0x00000001
#define BCHP_BSP_GLB_CONTROL_GLB_OLOAD_CR_CMD_OLOAD_CR_SHIFT       0

/***************************************************************************
 *GLB_ILOAD_CR - Challenge/Response Input Command Buffer Loaded
 ***************************************************************************/
/* BSP_GLB_CONTROL :: GLB_ILOAD_CR :: reserved0 [31:01] */
#define BCHP_BSP_GLB_CONTROL_GLB_ILOAD_CR_reserved0_MASK           0xfffffffe
#define BCHP_BSP_GLB_CONTROL_GLB_ILOAD_CR_reserved0_SHIFT          1

/* BSP_GLB_CONTROL :: GLB_ILOAD_CR :: CMD_ILOAD_CR [00:00] */
#define BCHP_BSP_GLB_CONTROL_GLB_ILOAD_CR_CMD_ILOAD_CR_MASK        0x00000001
#define BCHP_BSP_GLB_CONTROL_GLB_ILOAD_CR_CMD_ILOAD_CR_SHIFT       0

/***************************************************************************
 *GLB_MEM0 - TM Memory Control Register
 ***************************************************************************/
/* BSP_GLB_CONTROL :: GLB_MEM0 :: reserved0 [31:30] */
#define BCHP_BSP_GLB_CONTROL_GLB_MEM0_reserved0_MASK               0xc0000000
#define BCHP_BSP_GLB_CONTROL_GLB_MEM0_reserved0_SHIFT              30

/* BSP_GLB_CONTROL :: GLB_MEM0 :: TM5 [29:25] */
#define BCHP_BSP_GLB_CONTROL_GLB_MEM0_TM5_MASK                     0x3e000000
#define BCHP_BSP_GLB_CONTROL_GLB_MEM0_TM5_SHIFT                    25

/* BSP_GLB_CONTROL :: GLB_MEM0 :: TM4 [24:20] */
#define BCHP_BSP_GLB_CONTROL_GLB_MEM0_TM4_MASK                     0x01f00000
#define BCHP_BSP_GLB_CONTROL_GLB_MEM0_TM4_SHIFT                    20

/* BSP_GLB_CONTROL :: GLB_MEM0 :: TM3 [19:15] */
#define BCHP_BSP_GLB_CONTROL_GLB_MEM0_TM3_MASK                     0x000f8000
#define BCHP_BSP_GLB_CONTROL_GLB_MEM0_TM3_SHIFT                    15

/* BSP_GLB_CONTROL :: GLB_MEM0 :: TM2 [14:10] */
#define BCHP_BSP_GLB_CONTROL_GLB_MEM0_TM2_MASK                     0x00007c00
#define BCHP_BSP_GLB_CONTROL_GLB_MEM0_TM2_SHIFT                    10

/* BSP_GLB_CONTROL :: GLB_MEM0 :: TM1 [09:05] */
#define BCHP_BSP_GLB_CONTROL_GLB_MEM0_TM1_MASK                     0x000003e0
#define BCHP_BSP_GLB_CONTROL_GLB_MEM0_TM1_SHIFT                    5

/* BSP_GLB_CONTROL :: GLB_MEM0 :: TM0 [04:00] */
#define BCHP_BSP_GLB_CONTROL_GLB_MEM0_TM0_MASK                     0x0000001f
#define BCHP_BSP_GLB_CONTROL_GLB_MEM0_TM0_SHIFT                    0

/***************************************************************************
 *GLB_MEM1 - TM Memory Control Register
 ***************************************************************************/
/* BSP_GLB_CONTROL :: GLB_MEM1 :: reserved0 [31:23] */
#define BCHP_BSP_GLB_CONTROL_GLB_MEM1_reserved0_MASK               0xff800000
#define BCHP_BSP_GLB_CONTROL_GLB_MEM1_reserved0_SHIFT              23

/* BSP_GLB_CONTROL :: GLB_MEM1 :: TM3 [22:15] */
#define BCHP_BSP_GLB_CONTROL_GLB_MEM1_TM3_MASK                     0x007f8000
#define BCHP_BSP_GLB_CONTROL_GLB_MEM1_TM3_SHIFT                    15

/* BSP_GLB_CONTROL :: GLB_MEM1 :: TM2 [14:10] */
#define BCHP_BSP_GLB_CONTROL_GLB_MEM1_TM2_MASK                     0x00007c00
#define BCHP_BSP_GLB_CONTROL_GLB_MEM1_TM2_SHIFT                    10

/* BSP_GLB_CONTROL :: GLB_MEM1 :: TM1 [09:05] */
#define BCHP_BSP_GLB_CONTROL_GLB_MEM1_TM1_MASK                     0x000003e0
#define BCHP_BSP_GLB_CONTROL_GLB_MEM1_TM1_SHIFT                    5

/* BSP_GLB_CONTROL :: GLB_MEM1 :: TM0 [04:00] */
#define BCHP_BSP_GLB_CONTROL_GLB_MEM1_TM0_MASK                     0x0000001f
#define BCHP_BSP_GLB_CONTROL_GLB_MEM1_TM0_SHIFT                    0

/***************************************************************************
 *GLB_MEM2 - TM Memory Control Register
 ***************************************************************************/
/* BSP_GLB_CONTROL :: GLB_MEM2 :: TM3 [31:24] */
#define BCHP_BSP_GLB_CONTROL_GLB_MEM2_TM3_MASK                     0xff000000
#define BCHP_BSP_GLB_CONTROL_GLB_MEM2_TM3_SHIFT                    24

/* BSP_GLB_CONTROL :: GLB_MEM2 :: TM2 [23:16] */
#define BCHP_BSP_GLB_CONTROL_GLB_MEM2_TM2_MASK                     0x00ff0000
#define BCHP_BSP_GLB_CONTROL_GLB_MEM2_TM2_SHIFT                    16

/* BSP_GLB_CONTROL :: GLB_MEM2 :: TM1 [15:08] */
#define BCHP_BSP_GLB_CONTROL_GLB_MEM2_TM1_MASK                     0x0000ff00
#define BCHP_BSP_GLB_CONTROL_GLB_MEM2_TM1_SHIFT                    8

/* BSP_GLB_CONTROL :: GLB_MEM2 :: TM0 [07:00] */
#define BCHP_BSP_GLB_CONTROL_GLB_MEM2_TM0_MASK                     0x000000ff
#define BCHP_BSP_GLB_CONTROL_GLB_MEM2_TM0_SHIFT                    0

/***************************************************************************
 *GLB_MEM3 - TM Memory Control Register
 ***************************************************************************/
/* BSP_GLB_CONTROL :: GLB_MEM3 :: reserved0 [31:28] */
#define BCHP_BSP_GLB_CONTROL_GLB_MEM3_reserved0_MASK               0xf0000000
#define BCHP_BSP_GLB_CONTROL_GLB_MEM3_reserved0_SHIFT              28

/* BSP_GLB_CONTROL :: GLB_MEM3 :: TM4 [27:20] */
#define BCHP_BSP_GLB_CONTROL_GLB_MEM3_TM4_MASK                     0x0ff00000
#define BCHP_BSP_GLB_CONTROL_GLB_MEM3_TM4_SHIFT                    20

/* BSP_GLB_CONTROL :: GLB_MEM3 :: TM3 [19:15] */
#define BCHP_BSP_GLB_CONTROL_GLB_MEM3_TM3_MASK                     0x000f8000
#define BCHP_BSP_GLB_CONTROL_GLB_MEM3_TM3_SHIFT                    15

/* BSP_GLB_CONTROL :: GLB_MEM3 :: TM2 [14:10] */
#define BCHP_BSP_GLB_CONTROL_GLB_MEM3_TM2_MASK                     0x00007c00
#define BCHP_BSP_GLB_CONTROL_GLB_MEM3_TM2_SHIFT                    10

/* BSP_GLB_CONTROL :: GLB_MEM3 :: TM1 [09:05] */
#define BCHP_BSP_GLB_CONTROL_GLB_MEM3_TM1_MASK                     0x000003e0
#define BCHP_BSP_GLB_CONTROL_GLB_MEM3_TM1_SHIFT                    5

/* BSP_GLB_CONTROL :: GLB_MEM3 :: TM0 [04:00] */
#define BCHP_BSP_GLB_CONTROL_GLB_MEM3_TM0_MASK                     0x0000001f
#define BCHP_BSP_GLB_CONTROL_GLB_MEM3_TM0_SHIFT                    0

/***************************************************************************
 *GLB_DWNLD_ERR - Download Error flags
 ***************************************************************************/
/* BSP_GLB_CONTROL :: GLB_DWNLD_ERR :: reserved0 [31:01] */
#define BCHP_BSP_GLB_CONTROL_GLB_DWNLD_ERR_reserved0_MASK          0xfffffffe
#define BCHP_BSP_GLB_CONTROL_GLB_DWNLD_ERR_reserved0_SHIFT         1

/* BSP_GLB_CONTROL :: GLB_DWNLD_ERR :: DISASTER_RECOVER [00:00] */
#define BCHP_BSP_GLB_CONTROL_GLB_DWNLD_ERR_DISASTER_RECOVER_MASK   0x00000001
#define BCHP_BSP_GLB_CONTROL_GLB_DWNLD_ERR_DISASTER_RECOVER_SHIFT  0

/***************************************************************************
 *GLB_DWNLD_STATUS - Download Status flags
 ***************************************************************************/
/* BSP_GLB_CONTROL :: GLB_DWNLD_STATUS :: reserved0 [31:02] */
#define BCHP_BSP_GLB_CONTROL_GLB_DWNLD_STATUS_reserved0_MASK       0xfffffffc
#define BCHP_BSP_GLB_CONTROL_GLB_DWNLD_STATUS_reserved0_SHIFT      2

/* BSP_GLB_CONTROL :: GLB_DWNLD_STATUS :: SECOND_STAGE_LOADED [01:01] */
#define BCHP_BSP_GLB_CONTROL_GLB_DWNLD_STATUS_SECOND_STAGE_LOADED_MASK 0x00000002
#define BCHP_BSP_GLB_CONTROL_GLB_DWNLD_STATUS_SECOND_STAGE_LOADED_SHIFT 1

/* BSP_GLB_CONTROL :: GLB_DWNLD_STATUS :: SECOND_STAGE [00:00] */
#define BCHP_BSP_GLB_CONTROL_GLB_DWNLD_STATUS_SECOND_STAGE_MASK    0x00000001
#define BCHP_BSP_GLB_CONTROL_GLB_DWNLD_STATUS_SECOND_STAGE_SHIFT   0

#endif /* #ifndef BCHP_BSP_GLB_CONTROL_H__ */

/* End of File */

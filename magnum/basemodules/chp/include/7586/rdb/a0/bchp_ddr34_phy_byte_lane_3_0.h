/****************************************************************************
 *     Copyright (c) 1999-2014, Broadcom Corporation
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
 * Date:           Generated on               Wed Feb 11 10:13:57 2015
 *                 Full Compile MD5 Checksum  f7f4bd55341805fcfe958ba5e47e65f4
 *                     (minus title and desc)
 *                 MD5 Checksum               95b679a9655597a92593cae55222c397
 *
 * Compiled with:  RDB Utility                combo_header.pl
 *                 RDB.pm                     15653
 *                 unknown                    unknown
 *                 Perl Interpreter           5.008008
 *                 Operating System           linux
 *
 *
 ***************************************************************************/

#ifndef BCHP_DDR34_PHY_BYTE_LANE_3_0_H__
#define BCHP_DDR34_PHY_BYTE_LANE_3_0_H__

/***************************************************************************
 *DDR34_PHY_BYTE_LANE_3_0 - DDR34 Byte Lane #3 control registers
 ***************************************************************************/
#define BCHP_DDR34_PHY_BYTE_LANE_3_0_VDL_CONTROL_WR_DQS 0x00920a00 /* [RW] Write channel DQS VDL control register */
#define BCHP_DDR34_PHY_BYTE_LANE_3_0_VDL_CONTROL_WR_DQ0 0x00920a04 /* [RW] Write channel DQ0 VDL control register */
#define BCHP_DDR34_PHY_BYTE_LANE_3_0_VDL_CONTROL_WR_DQ1 0x00920a08 /* [RW] Write channel DQ1 VDL control register */
#define BCHP_DDR34_PHY_BYTE_LANE_3_0_VDL_CONTROL_WR_DQ2 0x00920a0c /* [RW] Write channel DQ2 VDL control register */
#define BCHP_DDR34_PHY_BYTE_LANE_3_0_VDL_CONTROL_WR_DQ3 0x00920a10 /* [RW] Write channel DQ3 VDL control register */
#define BCHP_DDR34_PHY_BYTE_LANE_3_0_VDL_CONTROL_WR_DQ4 0x00920a14 /* [RW] Write channel DQ4 VDL control register */
#define BCHP_DDR34_PHY_BYTE_LANE_3_0_VDL_CONTROL_WR_DQ5 0x00920a18 /* [RW] Write channel DQ5 VDL control register */
#define BCHP_DDR34_PHY_BYTE_LANE_3_0_VDL_CONTROL_WR_DQ6 0x00920a1c /* [RW] Write channel DQ6 VDL control register */
#define BCHP_DDR34_PHY_BYTE_LANE_3_0_VDL_CONTROL_WR_DQ7 0x00920a20 /* [RW] Write channel DQ7 VDL control register */
#define BCHP_DDR34_PHY_BYTE_LANE_3_0_VDL_CONTROL_WR_DM 0x00920a24 /* [RW] Write channel DM VDL control register */
#define BCHP_DDR34_PHY_BYTE_LANE_3_0_VDL_CONTROL_WR_EDC 0x00920a28 /* [RW] Write channel EDC VDL control register */
#define BCHP_DDR34_PHY_BYTE_LANE_3_0_VDL_CONTROL_RD_DQSP 0x00920a2c /* [RW] Read channel DQSP VDL control register */
#define BCHP_DDR34_PHY_BYTE_LANE_3_0_VDL_CONTROL_RD_DQSN 0x00920a30 /* [RW] Read channel DQSP VDL control register */
#define BCHP_DDR34_PHY_BYTE_LANE_3_0_VDL_CONTROL_RD_DQ0P 0x00920a34 /* [RW] Read channel DQ0-P VDL control register */
#define BCHP_DDR34_PHY_BYTE_LANE_3_0_VDL_CONTROL_RD_DQ0N 0x00920a38 /* [RW] Read channel DQ0-N VDL control register */
#define BCHP_DDR34_PHY_BYTE_LANE_3_0_VDL_CONTROL_RD_DQ1P 0x00920a3c /* [RW] Read channel DQ1-P VDL control register */
#define BCHP_DDR34_PHY_BYTE_LANE_3_0_VDL_CONTROL_RD_DQ1N 0x00920a40 /* [RW] Read channel DQ1-N VDL control register */
#define BCHP_DDR34_PHY_BYTE_LANE_3_0_VDL_CONTROL_RD_DQ2P 0x00920a44 /* [RW] Read channel DQ2-P VDL control register */
#define BCHP_DDR34_PHY_BYTE_LANE_3_0_VDL_CONTROL_RD_DQ2N 0x00920a48 /* [RW] Read channel DQ2-N VDL control register */
#define BCHP_DDR34_PHY_BYTE_LANE_3_0_VDL_CONTROL_RD_DQ3P 0x00920a4c /* [RW] Read channel DQ3-P VDL control register */
#define BCHP_DDR34_PHY_BYTE_LANE_3_0_VDL_CONTROL_RD_DQ3N 0x00920a50 /* [RW] Read channel DQ3-N VDL control register */
#define BCHP_DDR34_PHY_BYTE_LANE_3_0_VDL_CONTROL_RD_DQ4P 0x00920a54 /* [RW] Read channel DQ4-P VDL control register */
#define BCHP_DDR34_PHY_BYTE_LANE_3_0_VDL_CONTROL_RD_DQ4N 0x00920a58 /* [RW] Read channel DQ4-N VDL control register */
#define BCHP_DDR34_PHY_BYTE_LANE_3_0_VDL_CONTROL_RD_DQ5P 0x00920a5c /* [RW] Read channel DQ5-P VDL control register */
#define BCHP_DDR34_PHY_BYTE_LANE_3_0_VDL_CONTROL_RD_DQ5N 0x00920a60 /* [RW] Read channel DQ5-N VDL control register */
#define BCHP_DDR34_PHY_BYTE_LANE_3_0_VDL_CONTROL_RD_DQ6P 0x00920a64 /* [RW] Read channel DQ6-P VDL control register */
#define BCHP_DDR34_PHY_BYTE_LANE_3_0_VDL_CONTROL_RD_DQ6N 0x00920a68 /* [RW] Read channel DQ6-N VDL control register */
#define BCHP_DDR34_PHY_BYTE_LANE_3_0_VDL_CONTROL_RD_DQ7P 0x00920a6c /* [RW] Read channel DQ7-P VDL control register */
#define BCHP_DDR34_PHY_BYTE_LANE_3_0_VDL_CONTROL_RD_DQ7N 0x00920a70 /* [RW] Read channel DQ7-N VDL control register */
#define BCHP_DDR34_PHY_BYTE_LANE_3_0_VDL_CONTROL_RD_DMP 0x00920a74 /* [RW] Read channel DM-P VDL control register */
#define BCHP_DDR34_PHY_BYTE_LANE_3_0_VDL_CONTROL_RD_DMN 0x00920a78 /* [RW] Read channel DM-N VDL control register */
#define BCHP_DDR34_PHY_BYTE_LANE_3_0_VDL_CONTROL_RD_EDCP 0x00920a7c /* [RW] Read channel EDC-P VDL control register */
#define BCHP_DDR34_PHY_BYTE_LANE_3_0_VDL_CONTROL_RD_EDCN 0x00920a80 /* [RW] Read channel EDC-P VDL control register */
#define BCHP_DDR34_PHY_BYTE_LANE_3_0_VDL_CONTROL_RD_EN_CS0 0x00920a84 /* [RW] Read channel CS_N[0] read enable VDL control register */
#define BCHP_DDR34_PHY_BYTE_LANE_3_0_VDL_CONTROL_RD_EN_CS1 0x00920a88 /* [RW] Read channel CS_N[1] read enable VDL control register (used for reads when only cs1_n is active) */
#define BCHP_DDR34_PHY_BYTE_LANE_3_0_VDL_CONTROL_RD_EN_CRC 0x00920a8c /* [RW] Read channel GDDR5 CRC read enable VDL control register */
#define BCHP_DDR34_PHY_BYTE_LANE_3_0_VDL_CLK_CONTROL 0x00920a90 /* [RW] DDR interface signal Write Leveling CLK VDL control register */
#define BCHP_DDR34_PHY_BYTE_LANE_3_0_VDL_LDE_CONTROL 0x00920a94 /* [RW] DDR interface signal Write Leveling Capture Enable VDL control register */
#define BCHP_DDR34_PHY_BYTE_LANE_3_0_RD_EN_DLY_CYC 0x00920a98 /* [RW] Read enable bit-clock cycle delay control register */
#define BCHP_DDR34_PHY_BYTE_LANE_3_0_WR_CHAN_DLY_CYC 0x00920a9c /* [RW] Write leveling bit-clock cycle delay control register */
#define BCHP_DDR34_PHY_BYTE_LANE_3_0_READ_CONTROL 0x00920aa0 /* [RW] Read channel datapath control register */
#define BCHP_DDR34_PHY_BYTE_LANE_3_0_READ_FIFO_ADDR 0x00920aa4 /* [RW] Read fifo addresss pointer register */
#define BCHP_DDR34_PHY_BYTE_LANE_3_0_READ_FIFO_DATA 0x00920aa8 /* [RO] Read fifo data register */
#define BCHP_DDR34_PHY_BYTE_LANE_3_0_READ_FIFO_DM_DBI 0x00920aac /* [RO] Read fifo dm/dbi register */
#define BCHP_DDR34_PHY_BYTE_LANE_3_0_READ_FIFO_STATUS 0x00920ab0 /* [RO] Read fifo status register */
#define BCHP_DDR34_PHY_BYTE_LANE_3_0_READ_FIFO_CLEAR 0x00920ab4 /* [WO] Read fifo status clear register */
#define BCHP_DDR34_PHY_BYTE_LANE_3_0_IDLE_PAD_CONTROL 0x00920ab8 /* [RW] Idle mode SSTL pad control register */
#define BCHP_DDR34_PHY_BYTE_LANE_3_0_DRIVE_PAD_CTL 0x00920abc /* [RW] DQ, DM pad drive characteristics control register */
#define BCHP_DDR34_PHY_BYTE_LANE_3_0_DQSP_DRIVE_PAD_CTL 0x00920ac0 /* [RW] DQS pad P rail  drive characteristics control register */
#define BCHP_DDR34_PHY_BYTE_LANE_3_0_DQSN_DRIVE_PAD_CTL 0x00920ac4 /* [RW] DQS pad N rail  drive characteristics control register */
#define BCHP_DDR34_PHY_BYTE_LANE_3_0_EDC_DRIVE_PAD_CTL 0x00920ac8 /* [RW] EDC pad drive characteristics control register */
#define BCHP_DDR34_PHY_BYTE_LANE_3_0_RD_EN_DRIVE_PAD_CTL 0x00920acc /* [RW] RD_EN, EDC_RD_EN read enable pad drive characteristics control register */
#define BCHP_DDR34_PHY_BYTE_LANE_3_0_STATIC_PAD_CTL 0x00920ad0 /* [RW] pad rx and tx characteristics control register */
#define BCHP_DDR34_PHY_BYTE_LANE_3_0_DQ_RX_TRIM  0x00920ad4 /* [RW] Receiver trim for DQ */
#define BCHP_DDR34_PHY_BYTE_LANE_3_0_MISC_RX_TRIM 0x00920ad8 /* [RW] Receiver trim for miscellaneous pins */
#define BCHP_DDR34_PHY_BYTE_LANE_3_0_DQS_RX_TRIM 0x00920adc /* [RW] Rreceiver trim for DQS */
#define BCHP_DDR34_PHY_BYTE_LANE_3_0_WR_PREAMBLE_MODE 0x00920ae0 /* [RW] Write cycle preamble control register */
#define BCHP_DDR34_PHY_BYTE_LANE_3_0_ODT_CONTROL 0x00920ae4 /* [RW] Read channel ODT control register */
#define BCHP_DDR34_PHY_BYTE_LANE_3_0_LDO_CONFIG  0x00920ae8 /* [RW] LDO Configuration register */
#define BCHP_DDR34_PHY_BYTE_LANE_3_0_EDC_DPD_CONTROL 0x00920aec /* [RW] GDDR5M EDC digital phase detector control register */
#define BCHP_DDR34_PHY_BYTE_LANE_3_0_EDC_DPD_STATUS 0x00920af0 /* [RO] GDDR5M EDC digital phase detector status register */
#define BCHP_DDR34_PHY_BYTE_LANE_3_0_EDC_DPD_OUT_CONTROL 0x00920af4 /* [RW] GDDR5M EDC digital phase detector output signal control register */
#define BCHP_DDR34_PHY_BYTE_LANE_3_0_EDC_DPD_OUT_STATUS 0x00920af8 /* [RO] GDDR5M EDC digital phase detector output signal status register */
#define BCHP_DDR34_PHY_BYTE_LANE_3_0_EDC_DPD_OUT_STATUS_CLEAR 0x00920afc /* [WO] GDDR5M EDC digital phase detector output signal status clear register */
#define BCHP_DDR34_PHY_BYTE_LANE_3_0_EDC_CRC_CONTROL 0x00920b00 /* [RW] GDDR5M EDC signal path CRC control register */
#define BCHP_DDR34_PHY_BYTE_LANE_3_0_EDC_CRC_STATUS 0x00920b04 /* [RO] GDDR5M EDC signal path CRC status register */
#define BCHP_DDR34_PHY_BYTE_LANE_3_0_EDC_CRC_COUNT 0x00920b08 /* [RO] GDDR5M EDC signal path CRC counter register */
#define BCHP_DDR34_PHY_BYTE_LANE_3_0_EDC_CRC_STATUS_CLEAR 0x00920b0c /* [WO] GDDR5M EDC signal path CRC counter register */
#define BCHP_DDR34_PHY_BYTE_LANE_3_0_CLOCK_ENABLE 0x00920b10 /* [RW] Clock Enable Register */
#define BCHP_DDR34_PHY_BYTE_LANE_3_0_CLOCK_IDLE  0x00920b14 /* [RW] Clock Idle Register */
#define BCHP_DDR34_PHY_BYTE_LANE_3_0_BL_SPARE_REG 0x00920b18 /* [RW] Byte-Lane Spare register */

#endif /* #ifndef BCHP_DDR34_PHY_BYTE_LANE_3_0_H__ */

/* End of File */

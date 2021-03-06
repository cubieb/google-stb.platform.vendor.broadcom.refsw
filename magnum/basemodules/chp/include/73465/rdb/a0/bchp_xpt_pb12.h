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
 * Date:           Generated on               Tue Aug 25 10:46:54 2015
 *                 Full Compile MD5 Checksum  add20cb7888302c2ee8be1277223a4e4
 *                     (minus title and desc)
 *                 MD5 Checksum               f64b4ec86ad9ad7523e5d75b1dc732c5
 *
 * Compiled with:  RDB Utility                combo_header.pl
 *                 RDB.pm                     126
 *                 unknown                    unknown
 *                 Perl Interpreter           5.008008
 *                 Operating System           linux
 *                 Script Source              /tools/dvtsw/current/Linux/combo_header.pl
 *                 DVTSWVER                   current
 *
 *
 ***************************************************************************/

#ifndef BCHP_XPT_PB12_H__
#define BCHP_XPT_PB12_H__

/***************************************************************************
 *XPT_PB12 - Playback 12 Control Registers
 ***************************************************************************/
#define BCHP_XPT_PB12_CTRL1                      0x00a08700 /* [RW] Playback Control 1 Register */
#define BCHP_XPT_PB12_CTRL2                      0x00a08704 /* [RW] Playback Control 2 Register */
#define BCHP_XPT_PB12_CTRL3                      0x00a08708 /* [RW] Playback Control 3 Register */
#define BCHP_XPT_PB12_CTRL4                      0x00a0870c /* [RW] Playback Control 4 Register */
#define BCHP_XPT_PB12_FIRST_DESC_ADDR            0x00a08710 /* [RW] Playback First Descriptor Address Register */
#define BCHP_XPT_PB12_CURR_DESC_ADDR             0x00a08714 /* [RO] Playback Current Descriptor Address Register */
#define BCHP_XPT_PB12_CURR_BUFF_ADDR             0x00a08718 /* [RO] Playback Current Buffer Address Register */
#define BCHP_XPT_PB12_BLOCKOUT                   0x00a0871c /* [RW] Data Transport Playback Block Out Control */
#define BCHP_XPT_PB12_PKTZ_CONTEXT0              0x00a08720 /* [RW] Data Transport Playback Packetize Mode Context 0 Control */
#define BCHP_XPT_PB12_TS_ERR_BOUND_EARLY         0x00a08724 /* [RW] Data Transport Playback Timestamp Error Bound Register */
#define BCHP_XPT_PB12_TS_ERR_BOUND_LATE          0x00a08728 /* [RW] Data Transport Playback Timestamp Error Bound Register */
#define BCHP_XPT_PB12_PARSER_CTRL1               0x00a0872c /* [RW] Data Transport Playback Parser Control Register */
#define BCHP_XPT_PB12_PARSER_CTRL2               0x00a08730 /* [RW] Data Transport Playback Parser Control Register 2 */
#define BCHP_XPT_PB12_PARSER_TIMESTAMP           0x00a08734 /* [RO] Data Transport Playback Parser Local Timestamp */
#define BCHP_XPT_PB12_INTR                       0x00a08738 /* [RW] Playback Processing Error and Status Interrupt Register */
#define BCHP_XPT_PB12_INTR_EN                    0x00a0873c /* [RW] Playback Processing Error and Status Interrupt Enable Register */
#define BCHP_XPT_PB12_INTR_TAGS                  0x00a08740 /* [RW] Playback Interrupt Tag Register */
#define BCHP_XPT_PB12_PACING_PCR_PID             0x00a08744 /* [RW] Playback PCR Based Pacing PCR Pid */
#define BCHP_XPT_PB12_PWR_CTRL                   0x00a08748 /* [RW] Playback Power Control Register */
#define BCHP_XPT_PB12_MISC_STATUS_REG            0x00a0874c /* [RW] Miscellaneous Playback Status Registers */
#define BCHP_XPT_PB12_ASF_CTRL                   0x00a08750 /* [RW] ASF Control Register */
#define BCHP_XPT_PB12_ASF_DATA_PACKET_LENGTH     0x00a08754 /* [RW] ASF_DATA_PACKET_LENGTH */
#define BCHP_XPT_PB12_ASF_SUB_PAYLOAD_PKT_TYPE   0x00a08758 /* [RW] ASF_SUB_PAYLOAD_PKT_TYPE */
#define BCHP_XPT_PB12_ASF_PAYLOAD_PKT_TYPE       0x00a0875c /* [RW] ASF_PAYLOAD_PKT_TYPE */
#define BCHP_XPT_PB12_PLAYBACK_PARSER_BAND_ID    0x00a08760 /* [RW] PLAYBACK_PARSER_BAND_ID */
#define BCHP_XPT_PB12_NEXT_PACKET_PACING_TIMESTAMP 0x00a08764 /* [RW] Next Packet Pacing Timestamp Value */
#define BCHP_XPT_PB12_PKT2PKT_PACING_TIMESTAMP_DELTA 0x00a08768 /* [RW] PKT2PKT Pacing TimeStamp Delta */
#define BCHP_XPT_PB12_PACING_COUNTER             0x00a0876c /* [RW] Pacing Counter Instantaneous value */
#define BCHP_XPT_PB12_ERROR_VALUE_WATERMARK      0x00a08770 /* [RW] WaterMark level of the Pacing Error Bound Reached */
#define BCHP_XPT_PB12_PES_BASED_PACING_CTRL      0x00a08774 /* [RW] PES Based Pacing Controls */

#endif /* #ifndef BCHP_XPT_PB12_H__ */

/* End of File */

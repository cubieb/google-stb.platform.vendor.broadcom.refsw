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
 * Date:           Generated on         Tue Feb 28 11:03:19 2012
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

#ifndef BCHP_XPT_PB10_H__
#define BCHP_XPT_PB10_H__

/***************************************************************************
 *XPT_PB10 - Playback 10 Control Registers
 ***************************************************************************/
#define BCHP_XPT_PB10_CTRL1                      0x00948600 /* Playback Control 1 Register */
#define BCHP_XPT_PB10_CTRL2                      0x00948604 /* Playback Control 2 Register */
#define BCHP_XPT_PB10_CTRL3                      0x00948608 /* Playback Control 3 Register */
#define BCHP_XPT_PB10_CTRL4                      0x0094860c /* Playback Control 4 Register */
#define BCHP_XPT_PB10_FIRST_DESC_ADDR            0x00948610 /* Playback First Descriptor Address Register */
#define BCHP_XPT_PB10_CURR_DESC_ADDR             0x00948614 /* Playback Current Descriptor Address Register */
#define BCHP_XPT_PB10_CURR_BUFF_ADDR             0x00948618 /* Playback Current Buffer Address Register */
#define BCHP_XPT_PB10_BLOCKOUT                   0x0094861c /* Data Transport Playback Block Out Control */
#define BCHP_XPT_PB10_PKTZ_CONTEXT0              0x00948620 /* Data Transport Playback Packetize Mode Context 0 Control */
#define BCHP_XPT_PB10_TS_ERR_BOUND_EARLY         0x00948624 /* Data Transport Playback Timestamp Error Bound Register */
#define BCHP_XPT_PB10_TS_ERR_BOUND_LATE          0x00948628 /* Data Transport Playback Timestamp Error Bound Register */
#define BCHP_XPT_PB10_PARSER_CTRL1               0x0094862c /* Data Transport Playback Parser Control Register */
#define BCHP_XPT_PB10_PARSER_CTRL2               0x00948630 /* Data Transport Playback Parser Control Register 2 */
#define BCHP_XPT_PB10_PARSER_TIMESTAMP           0x00948634 /* Data Transport Playback Parser Local Timestamp */
#define BCHP_XPT_PB10_INTR                       0x00948638 /* Playback Processing Error and Status Interrupt Register */
#define BCHP_XPT_PB10_INTR_EN                    0x0094863c /* Playback Processing Error and Status Interrupt Enable Register */
#define BCHP_XPT_PB10_INTR_TAGS                  0x00948640 /* Playback Interrupt Tag Register */
#define BCHP_XPT_PB10_PACING_PCR_PID             0x00948644 /* Playback PCR Based Pacing PCR Pid */
#define BCHP_XPT_PB10_PWR_CTRL                   0x00948648 /* Playback Power Control Register */
#define BCHP_XPT_PB10_MISC_STATUS_REG            0x0094864c /* Miscellaneous Playback Status Registers */
#define BCHP_XPT_PB10_ASF_CTRL                   0x00948650 /* ASF Control Register */
#define BCHP_XPT_PB10_ASF_DATA_PACKET_LENGTH     0x00948654 /* ASF_DATA_PACKET_LENGTH */
#define BCHP_XPT_PB10_ASF_SUB_PAYLOAD_PKT_TYPE   0x00948658 /* ASF_SUB_PAYLOAD_PKT_TYPE */
#define BCHP_XPT_PB10_ASF_PAYLOAD_PKT_TYPE       0x0094865c /* ASF_PAYLOAD_PKT_TYPE */
#define BCHP_XPT_PB10_PLAYBACK_PARSER_BAND_ID    0x00948660 /* PLAYBACK_PARSER_BAND_ID */
#define BCHP_XPT_PB10_NEXT_PACKET_PACING_TIMESTAMP 0x00948664 /* Next Packet Pacing Timestamp Value */
#define BCHP_XPT_PB10_PKT2PKT_PACING_TIMESTAMP_DELTA 0x00948668 /* PKT2PKT Pacing TimeStamp Delta */
#define BCHP_XPT_PB10_PACING_COUNTER             0x0094866c /* Pacing Counter Instantaneous value */
#define BCHP_XPT_PB10_ERROR_VALUE_WATERMARK      0x00948670 /* WaterMark level of the Pacing Error Bound Reached */
#define BCHP_XPT_PB10_PES_BASED_PACING_CTRL      0x00948674 /* PES Based Pacing Controls */

#endif /* #ifndef BCHP_XPT_PB10_H__ */

/* End of File */

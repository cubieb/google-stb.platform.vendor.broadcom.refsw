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
 * Date:           Generated on               Wed Feb 11 10:13:59 2015
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

#ifndef BCHP_DMA_IO2MEM_SUBCH_MAC_RX_SUBCH15_H__
#define BCHP_DMA_IO2MEM_SUBCH_MAC_RX_SUBCH15_H__

/***************************************************************************
 *DMA_IO2MEM_SUBCH_MAC_RX_SUBCH15 - DMA_IO2MEM_SUBCH registers
 ***************************************************************************/
#define BCHP_DMA_IO2MEM_SUBCH_MAC_RX_SUBCH15_SUBCH_CONTROL 0x00ff4400 /* [RW] Subchannel Control Register */
#define BCHP_DMA_IO2MEM_SUBCH_MAC_RX_SUBCH15_LLM_CMD 0x00ff4404 /* [RW] "LLM Command Register.,Contains set of commands/parameters DMA should pass to LLM while issuing various LLM commands." */
#define BCHP_DMA_IO2MEM_SUBCH_MAC_RX_SUBCH15_FREE_DESC_REQ_NUM 0x00ff4408 /* [RW] Free Descriptors Information Register */
#define BCHP_DMA_IO2MEM_SUBCH_MAC_RX_SUBCH15_DESC_THRESHOLD 0x00ff440c /* [RW] Descriptor Threshold Register. */
#define BCHP_DMA_IO2MEM_SUBCH_MAC_RX_SUBCH15_FC_THRESHOLD 0x00ff4410 /* [RW] Flow Control threshold Register */
#define BCHP_DMA_IO2MEM_SUBCH_MAC_RX_SUBCH15_BUFF_SIZE 0x00ff4414 /* [RW] "Buffer Size.,Indicates a buffer size multiplicator accociated with specific sub channel. Given in a units of 64 Bytes." */
#define BCHP_DMA_IO2MEM_SUBCH_MAC_RX_SUBCH15_DROP_PACKET_STAT 0x00ff4418 /* [RO] Dropped Packets Statistics Status Register */
#define BCHP_DMA_IO2MEM_SUBCH_MAC_RX_SUBCH15_DROP_PACKET_STAT_RESET 0x00ff441c /* [WO] Reset Dropped Packets Statistics Register */
#define BCHP_DMA_IO2MEM_SUBCH_MAC_RX_SUBCH15_DEBUG_REG1 0x00ff4420 /* [RO] Debug Register #1 */
#define BCHP_DMA_IO2MEM_SUBCH_MAC_RX_SUBCH15_DEBUG_REG2 0x00ff4424 /* [RO] Debug Register #2 */
#define BCHP_DMA_IO2MEM_SUBCH_MAC_RX_SUBCH15_DEBUG_REG3 0x00ff4428 /* [RO] Debug Register #3 */
#define BCHP_DMA_IO2MEM_SUBCH_MAC_RX_SUBCH15_DEBUG_REG4 0x00ff442c /* [RO] Debug Register #4 */

#endif /* #ifndef BCHP_DMA_IO2MEM_SUBCH_MAC_RX_SUBCH15_H__ */

/* End of File */

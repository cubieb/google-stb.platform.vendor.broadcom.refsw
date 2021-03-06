/***************************************************************************
 *     Copyright (c) 1999-2008, Broadcom Corporation
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
 * Date:           Generated on         Wed Jan  9 09:02:03 2008
 *                 MD5 Checksum         847dc12a9d71c4c68a648bbf19a883e3
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

#ifndef BCHP_DECODE_CPUREGS_1_H__
#define BCHP_DECODE_CPUREGS_1_H__

/***************************************************************************
 *DECODE_CPUREGS_1 - Inner Loop CPU Registers 1
 ***************************************************************************/
#define BCHP_DECODE_CPUREGS_1_REG_HST2CPU_MBX    0x00e00f00 /* Host 2 CPU mailbox register */
#define BCHP_DECODE_CPUREGS_1_REG_CPU2HST_MBX    0x00e00f04 /* CPU to Host mailbox register */
#define BCHP_DECODE_CPUREGS_1_REG_MBX_STAT       0x00e00f08 /* Mailbox status flags */
#define BCHP_DECODE_CPUREGS_1_REG_INST_BASE      0x00e00f0c /* Instruction base address register */
#define BCHP_DECODE_CPUREGS_1_REG_CPU_INT_ENA    0x00e00f10 /* CPU interrupt enable */
#define BCHP_DECODE_CPUREGS_1_REG_CPU_INT_STAT   0x00e00f14 /* CPU interrupt status */
#define BCHP_DECODE_CPUREGS_1_REG_HST2CPU_STAT   0x00e00f18 /* Host to CPU status register */
#define BCHP_DECODE_CPUREGS_1_REG_CPU2HST_STAT   0x00e00f1c /* CPU to Host status register */
#define BCHP_DECODE_CPUREGS_1_REG_CPU_INTGEN_SET 0x00e00f20 /* CPU interrupt set register */
#define BCHP_DECODE_CPUREGS_1_REG_CPU_INTGEN_CLR 0x00e00f24 /* CPU interrupt clear register */
#define BCHP_DECODE_CPUREGS_1_REG_CPU_ICACHE_MISS 0x00e00f28 /* Instruction cache miss counter */
#define BCHP_DECODE_CPUREGS_1_REG_CPU_INTGEN_MASK 0x00e00f2c /* CPU interrupt mask register */
#define BCHP_DECODE_CPUREGS_1_REG_END_OF_CODE    0x00e00f34 /* End of code register */
#define BCHP_DECODE_CPUREGS_1_REG_GLOBAL_IO_BASE 0x00e00f38 /* Global IO base register */
#define BCHP_DECODE_CPUREGS_1_REG_DEBUG_TRACE_FIFO_WR 0x00e00f3c /* CPU debug trace fifo write */
#define BCHP_DECODE_CPUREGS_1_REG_DEBUG_TRACE_FIFO_RD 0x00e00f40 /* CPU debug trace fifo read */
#define BCHP_DECODE_CPUREGS_1_REG_DEBUG_TRACE_FIFO_CTL 0x00e00f44 /* CPU debug trace fifo control */
#define BCHP_DECODE_CPUREGS_1_REG_WATCHDOG_TMR   0x00e00f4c /* Watchdog timer register */
#define BCHP_DECODE_CPUREGS_1_REG_SDRAM_STATUS   0x00e00f50 /* SDRAM Status register */
#define BCHP_DECODE_CPUREGS_1_REG_CPUREGS_END    0x00e00f7c /* Dummy end */

#endif /* #ifndef BCHP_DECODE_CPUREGS_1_H__ */

/* End of File */

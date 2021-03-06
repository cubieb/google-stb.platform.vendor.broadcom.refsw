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
 * Date:           Generated on               Thu Dec  4 13:58:59 2014
 *                 Full Compile MD5 Checksum  7f8620d6db569529bdb0529f9fa1fcf2
 *                     (minus title and desc)
 *                 MD5 Checksum               48c8fdf2af4291bac0fa2b0d5245d05c
 *
 * Compiled with:  RDB Utility                combo_header.pl
 *                 RDB.pm                     15262
 *                 unknown                    unknown
 *                 Perl Interpreter           5.008008
 *                 Operating System           linux
 *
 *
 ***************************************************************************/

#ifndef BCHP_HEVD_OL_CPU_REGS_2_H__
#define BCHP_HEVD_OL_CPU_REGS_2_H__

/***************************************************************************
 *HEVD_OL_CPU_REGS_2
 ***************************************************************************/
#define BCHP_HEVD_OL_CPU_REGS_2_HST2CPU_MBX      0x00200000 /* [RW] Host 2 CPU mailbox register */
#define BCHP_HEVD_OL_CPU_REGS_2_CPU2HST_MBX      0x00200004 /* [RW] CPU to Host mailbox register */
#define BCHP_HEVD_OL_CPU_REGS_2_MBX_STAT         0x00200008 /* [RO] Mailbox status flags */
#define BCHP_HEVD_OL_CPU_REGS_2_INST_BASE        0x0020000c /* [RW] Instruction base address register */
#define BCHP_HEVD_OL_CPU_REGS_2_CPU_INT_ENA      0x00200010 /* [RW] CPU interrupt enable */
#define BCHP_HEVD_OL_CPU_REGS_2_CPU_INT_STAT     0x00200014 /* [RO] CPU interrupt status */
#define BCHP_HEVD_OL_CPU_REGS_2_HST2CPU_STAT     0x00200018 /* [RW] Host to CPU status register */
#define BCHP_HEVD_OL_CPU_REGS_2_CPU2HST_STAT     0x0020001c /* [RW] CPU to Host status register */
#define BCHP_HEVD_OL_CPU_REGS_2_CPU_INTGEN_SET   0x00200020 /* [WO] CPU interrupt set register */
#define BCHP_HEVD_OL_CPU_REGS_2_CPU_INTGEN_CLR   0x00200024 /* [WO] CPU interrupt clear register */
#define BCHP_HEVD_OL_CPU_REGS_2_CPU_ICACHE_MISS  0x00200028 /* [RW] Instruction cache miss counter */
#define BCHP_HEVD_OL_CPU_REGS_2_CPU_INTGEN_MASK  0x0020002c /* [RW] CPU interrupt mask register */
#define BCHP_HEVD_OL_CPU_REGS_2_DRAM_RD_CNTR     0x00200030 /* [RW] CPU DRAM Read access Counter */
#define BCHP_HEVD_OL_CPU_REGS_2_END_OF_CODE      0x00200034 /* [RW] End of code register */
#define BCHP_HEVD_OL_CPU_REGS_2_GLOBAL_IO_BASE   0x00200038 /* [RW] Global IO base register */
#define BCHP_HEVD_OL_CPU_REGS_2_DEBUG_TRACE_FIFO_WR 0x0020003c /* [RW] CPU debug trace fifo write */
#define BCHP_HEVD_OL_CPU_REGS_2_DEBUG_TRACE_FIFO_RD 0x00200040 /* [RW] CPU debug trace fifo read */
#define BCHP_HEVD_OL_CPU_REGS_2_DEBUG_TRACE_FIFO_CTL 0x00200044 /* [RW] CPU debug trace fifo control */
#define BCHP_HEVD_OL_CPU_REGS_2_DRAM_WR_CNTR     0x00200048 /* [RW] CPU DRAM Write access Counter */
#define BCHP_HEVD_OL_CPU_REGS_2_WATCHDOG_TMR     0x0020004c /* [RW] Watchdog timer register */
#define BCHP_HEVD_OL_CPU_REGS_2_SDRAM_STATUS     0x00200050 /* [RO] SDRAM Status register */
#define BCHP_HEVD_OL_CPU_REGS_2_DEBUG_CTL        0x00200054 /* [RW] Debug Control */
#define BCHP_HEVD_OL_CPU_REGS_2_CMD_REG0         0x00200060 /* [RW] Command register 0 */
#define BCHP_HEVD_OL_CPU_REGS_2_CMD_REG1         0x00200064 /* [RW] Command register 1 */
#define BCHP_HEVD_OL_CPU_REGS_2_CMD_REG2         0x00200068 /* [RW] Command register 2 */
#define BCHP_HEVD_OL_CPU_REGS_2_CMD_REG3         0x0020006c /* [RW] Command register 3 */
#define BCHP_HEVD_OL_CPU_REGS_2_DEC_VERSION      0x00200108 /* [RO] Decoder versions */

#endif /* #ifndef BCHP_HEVD_OL_CPU_REGS_2_H__ */

/* End of File */

/******************************************************************************
 *  Copyright (C) 2017 Broadcom. The term "Broadcom" refers to Broadcom Limited and/or its subsidiaries.
 *
 *  This program is the proprietary software of Broadcom and/or its licensors,
 *  and may only be used, duplicated, modified or distributed pursuant to the terms and
 *  conditions of a separate, written license agreement executed between you and Broadcom
 *  (an "Authorized License").  Except as set forth in an Authorized License, Broadcom grants
 *  no license (express or implied), right to use, or waiver of any kind with respect to the
 *  Software, and Broadcom expressly reserves all rights in and to the Software and all
 *  intellectual property rights therein.  IF YOU HAVE NO AUTHORIZED LICENSE, THEN YOU
 *  HAVE NO RIGHT TO USE THIS SOFTWARE IN ANY WAY, AND SHOULD IMMEDIATELY
 *  NOTIFY BROADCOM AND DISCONTINUE ALL USE OF THE SOFTWARE.
 *
 *  Except as expressly set forth in the Authorized License,
 *
 *  1.     This program, including its structure, sequence and organization, constitutes the valuable trade
 *  secrets of Broadcom, and you shall use all reasonable efforts to protect the confidentiality thereof,
 *  and to use this information only in connection with your use of Broadcom integrated circuit products.
 *
 *  2.     TO THE MAXIMUM EXTENT PERMITTED BY LAW, THE SOFTWARE IS PROVIDED "AS IS"
 *  AND WITH ALL FAULTS AND BROADCOM MAKES NO PROMISES, REPRESENTATIONS OR
 *  WARRANTIES, EITHER EXPRESS, IMPLIED, STATUTORY, OR OTHERWISE, WITH RESPECT TO
 *  THE SOFTWARE.  BROADCOM SPECIFICALLY DISCLAIMS ANY AND ALL IMPLIED WARRANTIES
 *  OF TITLE, MERCHANTABILITY, NONINFRINGEMENT, FITNESS FOR A PARTICULAR PURPOSE,
 *  LACK OF VIRUSES, ACCURACY OR COMPLETENESS, QUIET ENJOYMENT, QUIET POSSESSION
 *  OR CORRESPONDENCE TO DESCRIPTION. YOU ASSUME THE ENTIRE RISK ARISING OUT OF
 *  USE OR PERFORMANCE OF THE SOFTWARE.
 *
 *  3.     TO THE MAXIMUM EXTENT PERMITTED BY LAW, IN NO EVENT SHALL BROADCOM OR ITS
 *  LICENSORS BE LIABLE FOR (i) CONSEQUENTIAL, INCIDENTAL, SPECIAL, INDIRECT, OR
 *  EXEMPLARY DAMAGES WHATSOEVER ARISING OUT OF OR IN ANY WAY RELATING TO YOUR
 *  USE OF OR INABILITY TO USE THE SOFTWARE EVEN IF BROADCOM HAS BEEN ADVISED OF
 *  THE POSSIBILITY OF SUCH DAMAGES; OR (ii) ANY AMOUNT IN EXCESS OF THE AMOUNT
 *  ACTUALLY PAID FOR THE SOFTWARE ITSELF OR U.S. $1, WHICHEVER IS GREATER. THESE
 *  LIMITATIONS SHALL APPLY NOTWITHSTANDING ANY FAILURE OF ESSENTIAL PURPOSE OF
 *  ANY LIMITED REMEDY.
 *
 * Module Description:
 *                     DO NOT EDIT THIS FILE DIRECTLY
 *
 * This module was generated magically with RDB from a source description
 * file. You must edit the source file for changes to be made to this file.
 *
 * The launch point for all information concerning RDB is found at:
 *   http://bcgbu.broadcom.com/RDB/SitePages/Home.aspx
 *
 * Date:           Generated on               Thu Apr 13 10:09:30 2017
 *                 Full Compile MD5 Checksum  7f180d7646477bba2bae1a701efd9ef5
 *                     (minus title and desc)
 *                 MD5 Checksum               a2a4a53aa20c0c2f46073b879159b85d
 *
 * lock_release:   n/a
 * Compiled with:  RDB Utility                combo_header.pl
 *                 RDB.pm                     1395
 *                 unknown                    unknown
 *                 Perl Interpreter           5.008008
 *                 Operating System           linux
 *                 Script Source              tools/dvtsw/current/Linux/combo_header.pl
 *                 DVTSWVER                   LOCAL tools/dvtsw/current/Linux/combo_header.pl
 *
 *
********************************************************************************/

#ifndef BCHP_HEVD_IL_CPU_REGS_2_0_H__
#define BCHP_HEVD_IL_CPU_REGS_2_0_H__

/***************************************************************************
 *HEVD_IL_CPU_REGS_2_0
 ***************************************************************************/
#define BCHP_HEVD_IL_CPU_REGS_2_0_HST2CPU_MBX    0x00c50000 /* [RW][32] Host 2 CPU mailbox register */
#define BCHP_HEVD_IL_CPU_REGS_2_0_CPU2HST_MBX    0x00c50004 /* [RW][32] CPU to Host mailbox register */
#define BCHP_HEVD_IL_CPU_REGS_2_0_MBX_STAT       0x00c50008 /* [RO][32] Mailbox status flags */
#define BCHP_HEVD_IL_CPU_REGS_2_0_INST_BASE      0x00c50010 /* [RW][64] Instruction base address register */
#define BCHP_HEVD_IL_CPU_REGS_2_0_CPU_INT_ENA    0x00c50018 /* [RW][32] CPU interrupt enable */
#define BCHP_HEVD_IL_CPU_REGS_2_0_CPU_INT_STAT   0x00c5001c /* [RO][32] CPU interrupt status */
#define BCHP_HEVD_IL_CPU_REGS_2_0_HST2CPU_STAT   0x00c50020 /* [RW][32] Host to CPU status register */
#define BCHP_HEVD_IL_CPU_REGS_2_0_CPU2HST_STAT   0x00c50024 /* [RW][32] CPU to Host status register */
#define BCHP_HEVD_IL_CPU_REGS_2_0_CPU_INTGEN_SET 0x00c50028 /* [RW][32] CPU interrupt set register */
#define BCHP_HEVD_IL_CPU_REGS_2_0_CPU_INTGEN_CLR 0x00c5002c /* [RW][32] CPU interrupt clear register */
#define BCHP_HEVD_IL_CPU_REGS_2_0_CPU_ICACHE_MISS 0x00c50030 /* [RW][32] Instruction cache miss counter */
#define BCHP_HEVD_IL_CPU_REGS_2_0_CPU_INTGEN_MASK 0x00c50034 /* [RW][32] CPU interrupt mask register */
#define BCHP_HEVD_IL_CPU_REGS_2_0_DRAM_RD_CNTR   0x00c50038 /* [RW][32] CPU DRAM Read access Counter */
#define BCHP_HEVD_IL_CPU_REGS_2_0_END_OF_CODE    0x00c5003c /* [RW][32] End of code register */
#define BCHP_HEVD_IL_CPU_REGS_2_0_GLOBAL_IO_BASE 0x00c50040 /* [RW][64] Global IO base register */
#define BCHP_HEVD_IL_CPU_REGS_2_0_DRAM_WR_CNTR   0x00c50048 /* [RW][32] CPU DRAM Write access Counter */
#define BCHP_HEVD_IL_CPU_REGS_2_0_WATCHDOG_TMR   0x00c5004c /* [RW][32] Watchdog timer register */
#define BCHP_HEVD_IL_CPU_REGS_2_0_SDRAM_STATUS   0x00c50050 /* [RO][32] SDRAM Status register */
#define BCHP_HEVD_IL_CPU_REGS_2_0_DEBUG_CTL      0x00c50054 /* [RW][32] Debug Control */
#define BCHP_HEVD_IL_CPU_REGS_2_0_CMD_REG0       0x00c50060 /* [RW][32] Command register 0 */
#define BCHP_HEVD_IL_CPU_REGS_2_0_CMD_REG1       0x00c50064 /* [RW][32] Command register 1 */
#define BCHP_HEVD_IL_CPU_REGS_2_0_CMD_REG2       0x00c50068 /* [RW][32] Command register 2 */
#define BCHP_HEVD_IL_CPU_REGS_2_0_CMD_REG3       0x00c5006c /* [RW][32] Command register 3 */
#define BCHP_HEVD_IL_CPU_REGS_2_0_CMD_REG4       0x00c50070 /* [RW][32] Command register 4 */
#define BCHP_HEVD_IL_CPU_REGS_2_0_CMD_REG5       0x00c50074 /* [RW][32] Command register 5 */
#define BCHP_HEVD_IL_CPU_REGS_2_0_CMD_REG6       0x00c50078 /* [RW][32] Command register 6 */
#define BCHP_HEVD_IL_CPU_REGS_2_0_CMD_REG7       0x00c5007c /* [RW][32] Command register 7 */
#define BCHP_HEVD_IL_CPU_REGS_2_0_GENERAL_TMR    0x00c50080 /* [RW][32] General purpose timer register */
#define BCHP_HEVD_IL_CPU_REGS_2_0_RM2_ARB_TIMEOUT 0x00c50084 /* [RW][32] RM2 ARBITER TIMEOUT Register */
#define BCHP_HEVD_IL_CPU_REGS_2_0_RM2_ARB_TIMEOUT_SLICE 0x00c50088 /* [RW][32] RM2 ARBITER TIMEOUT SLICE Register */
#define BCHP_HEVD_IL_CPU_REGS_2_0_RBUS_ERROR_LOW 0x00c5008c /* [RW][32] RBUS_ERROR LOW register */
#define BCHP_HEVD_IL_CPU_REGS_2_0_RBUS_ERROR_HI  0x00c50090 /* [RW][32] RBUS_ERROR HI register */
#define BCHP_HEVD_IL_CPU_REGS_2_0_DEC_VERSION    0x00c50108 /* [RO][32] Decoder versions */
#define BCHP_HEVD_IL_CPU_REGS_2_0_SDRAM_ADDR0    0x00c50110 /* [RW][64] SDRAM address register 0 */
#define BCHP_HEVD_IL_CPU_REGS_2_0_SDRAM_DATA0    0x00c50118 /* [RW][32] SDRAM data register 0 */
#define BCHP_HEVD_IL_CPU_REGS_2_0_SDRAM_ADDR1    0x00c50120 /* [RW][64] SDRAM address register 1 */
#define BCHP_HEVD_IL_CPU_REGS_2_0_SDRAM_DATA1    0x00c50128 /* [RW][32] SDRAM data register 1 */
#define BCHP_HEVD_IL_CPU_REGS_2_0_SDRAM_WINDOW   0x00c50130 /* [RW][64] SDRAM window register */

#endif /* #ifndef BCHP_HEVD_IL_CPU_REGS_2_0_H__ */

/* End of File */

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
 * Date:           Generated on               Tue Aug 26 10:56:51 2014
 *                 Full Compile MD5 Checksum  fe5bf937ded6451208bcd12a03dadcff
 *                     (minus title and desc)
 *                 MD5 Checksum               e67548d0bfc4c43233ca60dd5a6dc076
 *
 * Compiled with:  RDB Utility                combo_header.pl
 *                 RDB.pm                     14541
 *                 unknown                    unknown
 *                 Perl Interpreter           5.014001
 *                 Operating System           linux
 *
 *
 ***************************************************************************/

#ifndef BCHP_UARTB_H__
#define BCHP_UARTB_H__

/***************************************************************************
 *UARTB - UART B
 ***************************************************************************/
#define BCHP_UARTB_RBR                           0x0040b440 /* [RO] Receive Buffer Register */
#define BCHP_UARTB_THR                           0x0040b440 /* [WO] Transmit Holding Register */
#define BCHP_UARTB_DLH                           0x0040b444 /* [RW] Divisor Latch High */
#define BCHP_UARTB_DLL                           0x0040b440 /* [RW] Divisor Latch Low */
#define BCHP_UARTB_IER                           0x0040b444 /* [RW] Interrupt Enable Register */
#define BCHP_UARTB_IIR                           0x0040b448 /* [RO] Interrupt Identity Register */
#define BCHP_UARTB_FCR                           0x0040b448 /* [WO] FIFO Control Register */
#define BCHP_UARTB_LCR                           0x0040b44c /* [RW] Line Control Register */
#define BCHP_UARTB_MCR                           0x0040b450 /* [RW] Modem Control Register */
#define BCHP_UARTB_LSR                           0x0040b454 /* [RO] Line Status Register */
#define BCHP_UARTB_MSR                           0x0040b458 /* [RO] Modem Status Register */
#define BCHP_UARTB_SCR                           0x0040b45c /* [RW] Scratchpad Register */

#endif /* #ifndef BCHP_UARTB_H__ */

/* End of File */

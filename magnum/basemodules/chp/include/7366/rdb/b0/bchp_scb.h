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
 * Date:           Generated on               Thu Feb 12 15:22:02 2015
 *                 Full Compile MD5 Checksum  10187d4079392bab2546025f43274d34
 *                     (minus title and desc)
 *                 MD5 Checksum               c1587c5e16f21f52e852e7c7a65c7811
 *
 * Compiled with:  RDB Utility                combo_header.pl
 *                 RDB.pm                     15653
 *                 unknown                    unknown
 *                 Perl Interpreter           5.008008
 *                 Operating System           linux
 *
 *
 ***************************************************************************/

#ifndef BCHP_SCB_H__
#define BCHP_SCB_H__

/***************************************************************************
 *SCB - Smart Card B
 ***************************************************************************/
#define BCHP_SCB_UART_CMD                        0x0040ad00 /* [RW] Smart Card Uart Command */
#define BCHP_SCB_IF_CMD                          0x0040ad04 /* [RW] Smart Card Interface Command */
#define BCHP_SCB_CLK_CMD                         0x0040ad08 /* [RW] Smart Card Clock Command */
#define BCHP_SCB_PROTO_CMD                       0x0040ad0c /* [RW] Smart Card Protocol Command */
#define BCHP_SCB_PRESCALE                        0x0040ad10 /* [RW] Smart Card Clock Prescale */
#define BCHP_SCB_TGUARD                          0x0040ad14 /* [RW] Smart Card Transmit Guard Time */
#define BCHP_SCB_TRANSMIT                        0x0040ad18 /* [RW] Smart Card Transmit */
#define BCHP_SCB_RECEIVE                         0x0040ad1c /* [RO] Smart Card Receive */
#define BCHP_SCB_TLEN                            0x0040ad24 /* [RW] Smart Card Transmit Length */
#define BCHP_SCB_FLOW_CMD                        0x0040ad28 /* [RW] Smart Card Flow Command */
#define BCHP_SCB_RLEN                            0x0040ad30 /* [RO] Smart Card Receive Length */
#define BCHP_SCB_STATUS                          0x0040ad34 /* [RO] Smart Card Status */
#define BCHP_SCB_BGT                             0x0040ad44 /* [RW] Smart Card Block Guard Time */
#define BCHP_SCB_TIMER_CMD                       0x0040ad48 /* [RW] Smart Card Timer Command */
#define BCHP_SCB_INTR_EN                         0x0040ad50 /* [RW] Smart Card Interrupt Enable */
#define BCHP_SCB_INTR_STAT                       0x0040ad58 /* [RO] Smart Card Interrupt Status */
#define BCHP_SCB_TIMER_CMP                       0x0040ad60 /* [RW] Smart Card General Purpose Timer Compare */
#define BCHP_SCB_TIMER_CNT                       0x0040ad68 /* [RO] Smart Card General Purpose Timer Count */
#define BCHP_SCB_WAIT                            0x0040ad70 /* [RW] Smart Card Waiting Timer */
#define BCHP_SCB_EVENT1_CNT                      0x0040ad80 /* [RO] Smart Card Event 1 Count */
#define BCHP_SCB_EVENT1_CMP                      0x0040ad88 /* [RW] Smart Card Event 1 Compare */
#define BCHP_SCB_EVENT1_CMD                      0x0040ad90 /* [RW] Smart Card Event 1 Command */
#define BCHP_SCB_EVENT2_CMP                      0x0040ada0 /* [RW] Smart Card Event 2 Compare */
#define BCHP_SCB_EVENT2_CNT                      0x0040ada8 /* [RO] Smart Card Event 2 Count */
#define BCHP_SCB_EVENT2_CMD                      0x0040adb0 /* [RW] Smart Card Event 2 Command */
#define BCHP_SCB_SMODE_TICK                      0x0040adc0 /* [RW] Smart Card Synchronous Mode Timebase */
#define BCHP_SCB_IOIF_TICK                       0x0040adc4 /* [RW] Smart Card I/O Interface Timebase */
#define BCHP_SCB_SMODE_RLEN                      0x0040adc8 /* [RW] Smart Card Synchronous Receive Length */
#define BCHP_SCB_AFE_CMD_1                       0x0040adcc /* [RW] Smart Card Analog Front End Command 1 */
#define BCHP_SCB_AFE_CMD_2                       0x0040add0 /* [RW] Smart Card Analog Front End Command 2 */
#define BCHP_SCB_TMON_CMP                        0x0040add4 /* [RW] Smart Card Temperature Monitor Compare Threshold */
#define BCHP_SCB_TMON_TEMP                       0x0040add8 /* [RO] Smart Card Interface Contact Temperature */
#define BCHP_SCB_REVISION_ID                     0x0040adfc /* [RO] Smart Card Revision ID */

#endif /* #ifndef BCHP_SCB_H__ */

/* End of File */

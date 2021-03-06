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
 * Date:           Generated on               Thu Feb 12 15:15:52 2015
 *                 Full Compile MD5 Checksum  ca339b82db08da0250a17ca09932699d
 *                     (minus title and desc)
 *                 MD5 Checksum               502556bfbdc2f4341f93db8b4326b3ab
 *
 * Compiled with:  RDB Utility                combo_header.pl
 *                 RDB.pm                     15653
 *                 unknown                    unknown
 *                 Perl Interpreter           5.008008
 *                 Operating System           linux
 *
 *
 ***************************************************************************/

#ifndef BCHP_WEBHIF_TIMER_H__
#define BCHP_WEBHIF_TIMER_H__

/***************************************************************************
 *WEBHIF_TIMER - WEBHIF timers and watchdog registers
 ***************************************************************************/
#define BCHP_WEBHIF_TIMER_TIMER_IS               0x00464900 /* [RW] TIMER INTERRUPT STATUS REGISTER */
#define BCHP_WEBHIF_TIMER_TIMER_IE0              0x00464904 /* [RW] TIMER CPU INTERRUPT ENABLE REGISTER */
#define BCHP_WEBHIF_TIMER_TIMER0_CTRL            0x00464908 /* [RW] TIMER0 CONTROL REGISTER */
#define BCHP_WEBHIF_TIMER_TIMER1_CTRL            0x0046490c /* [RW] TIMER1 CONTROL REGISTER */
#define BCHP_WEBHIF_TIMER_TIMER2_CTRL            0x00464910 /* [RW] TIMER2 CONTROL REGISTER */
#define BCHP_WEBHIF_TIMER_TIMER3_CTRL            0x00464914 /* [RW] TIMER3 CONTROL REGISTER */
#define BCHP_WEBHIF_TIMER_TIMER0_STAT            0x00464918 /* [RO] TIMER0 STATUS REGISTER */
#define BCHP_WEBHIF_TIMER_TIMER1_STAT            0x0046491c /* [RO] TIMER1 STATUS REGISTER */
#define BCHP_WEBHIF_TIMER_TIMER2_STAT            0x00464920 /* [RO] TIMER2 STATUS REGISTER */
#define BCHP_WEBHIF_TIMER_TIMER3_STAT            0x00464924 /* [RO] TIMER3 STATUS REGISTER */
#define BCHP_WEBHIF_TIMER_WDTIMEOUT              0x00464928 /* [RW] WATCHDOG TIMEOUT REGISTER */
#define BCHP_WEBHIF_TIMER_WDCMD                  0x0046492c /* [WO] WATCHDOG COMMAND REGISTER */
#define BCHP_WEBHIF_TIMER_WDCHIPRST_CNT          0x00464930 /* [RW] WATCHDOG CHIP RESET COUNT REGISTER */
#define BCHP_WEBHIF_TIMER_TIMER_IE1              0x00464938 /* [RW] TIMER PCI INTERRUPT ENABLE REGISTER */
#define BCHP_WEBHIF_TIMER_WDCTRL                 0x0046493c /* [RW] WATCHDOG CONTROL REGISTER */

#endif /* #ifndef BCHP_WEBHIF_TIMER_H__ */

/* End of File */

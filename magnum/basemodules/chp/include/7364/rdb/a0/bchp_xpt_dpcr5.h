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
 * Date:           Generated on               Fri Aug 15 15:20:54 2014
 *                 Full Compile MD5 Checksum  a68bc62e9dd3be19fcad480c369d60fd
 *                     (minus title and desc)
 *                 MD5 Checksum               14382795d76d8497c2dd1bcf3f5d36da
 *
 * Compiled with:  RDB Utility                combo_header.pl
 *                 RDB.pm                     14541
 *                 unknown                    unknown
 *                 Perl Interpreter           5.008008
 *                 Operating System           linux
 *
 *
 ***************************************************************************/

#ifndef BCHP_XPT_DPCR5_H__
#define BCHP_XPT_DPCR5_H__

/***************************************************************************
 *XPT_DPCR5 - XPT DPCR5 Control Registers
 ***************************************************************************/
#define BCHP_XPT_DPCR5_PID_CH                    0x00a02280 /* [RW] Data Transport PCR PID Channel Register */
#define BCHP_XPT_DPCR5_CTRL                      0x00a02284 /* [RW] Data Transport PCR Control Register */
#define BCHP_XPT_DPCR5_INTR_STATUS_REG           0x00a02288 /* [RW] Interrupt Status Register */
#define BCHP_XPT_DPCR5_INTR_STATUS_REG_EN        0x00a0228c /* [RW] Interrupt Status Enable Register */
#define BCHP_XPT_DPCR5_STC_EXT_CTRL              0x00a02290 /* [RW] Data Transport PCR STC Extension Control Register */
#define BCHP_XPT_DPCR5_MAX_PCR_ERROR             0x00a022a0 /* [RW] Data Transport PCR Max PCR Error Register */
#define BCHP_XPT_DPCR5_SEND_BASE                 0x00a022a4 /* [RW] Data Transport PCR Send Base Register */
#define BCHP_XPT_DPCR5_SEND_EXT                  0x00a022a8 /* [RW] Data Transport PCR Send Extension Register */
#define BCHP_XPT_DPCR5_STC_EXT_CTRL27            0x00a022ac /* [RO] Data Transport PCR STC Extension Control Register (Test Only) */
#define BCHP_XPT_DPCR5_STC_HI                    0x00a022b0 /* [RO] Data Transport PCR STC MSBs Register */
#define BCHP_XPT_DPCR5_STC_LO                    0x00a022b4 /* [RO] Data Transport PCR STC LSBs Register */
#define BCHP_XPT_DPCR5_PWM_CTRLVALUE             0x00a022b8 /* [RO] Data Transport PCR PWM Control Value Register */
#define BCHP_XPT_DPCR5_LAST_PCR_HI               0x00a022bc /* [RO] Data Transport PCR Last PCR MSBs Register */
#define BCHP_XPT_DPCR5_LAST_PCR_LO               0x00a022c0 /* [RO] Data Transport PCR Last PCR LSBs Register */
#define BCHP_XPT_DPCR5_STC_BASE_LSBS             0x00a022c8 /* [RO] Data Transport PCR STC Base LSBs Register */
#define BCHP_XPT_DPCR5_PHASE_ERROR               0x00a022cc /* [RO] Timebase Last Phase Error */
#define BCHP_XPT_DPCR5_LOOP_CTRL                 0x00a022d0 /* [RW] Timebase Control */
#define BCHP_XPT_DPCR5_REF_PCR_PRESCALE          0x00a022d4 /* [RW] Timebase Frequency Reference Prescale Control */
#define BCHP_XPT_DPCR5_REF_PCR_INC               0x00a022d8 /* [RW] Timebase Frequency Reference Increment Control */
#define BCHP_XPT_DPCR5_CENTER                    0x00a022dc /* [RW] Timebase Center Frequency */
#define BCHP_XPT_DPCR5_ACCUM_VALUE               0x00a022e0 /* [RW] Timebase Loop Filter Integrator */
#define BCHP_XPT_DPCR5_PCR_COUNT                 0x00a022e4 /* [RO] Data Transport PCR Phase Error Register */
#define BCHP_XPT_DPCR5_SOFT_PCR_CTRL             0x00a022e8 /* [RW] Data Transport Soft PCR Control Register */
#define BCHP_XPT_DPCR5_SOFT_PCR_BASE             0x00a022ec /* [RW] Data Transport Soft PCR BASE Register */
#define BCHP_XPT_DPCR5_SOFT_PCR_EXT              0x00a022f0 /* [RW] Data Transport Soft PCR Extension Register */
#define BCHP_XPT_DPCR5_PHASE_ERROR_CLAMP         0x00a022f4 /* [RW] Timebase Phase Error Control */
#define BCHP_XPT_DPCR5_TIMEBASE_INPUT_SEL        0x00a022f8 /* [RW] Timebase Input Select for Timebase Loop */

#endif /* #ifndef BCHP_XPT_DPCR5_H__ */

/* End of File */

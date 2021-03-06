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
 * Date:           Generated on               Tue Jan 27 12:19:21 2015
 *                 Full Compile MD5 Checksum  3788d4127f6320d7294fc780a1f038a5
 *                     (minus title and desc)
 *                 MD5 Checksum               bc21cc7e43ef60b83e7c02281647c8e6
 *
 * Compiled with:  RDB Utility                combo_header.pl
 *                 RDB.pm                     15579
 *                 unknown                    unknown
 *                 Perl Interpreter           5.008008
 *                 Operating System           linux
 *
 *
 ***************************************************************************/

#ifndef BCHP_XPT_DPCR2_H__
#define BCHP_XPT_DPCR2_H__

/***************************************************************************
 *XPT_DPCR2 - XPT DPCR2 Control Registers
 ***************************************************************************/
#define BCHP_XPT_DPCR2_PID_CH                    0x00a06100 /* [RW] Data Transport PCR PID Channel Register */
#define BCHP_XPT_DPCR2_CTRL                      0x00a06104 /* [RW] Data Transport PCR Control Register */
#define BCHP_XPT_DPCR2_INTR_STATUS_REG           0x00a06108 /* [RW] Interrupt Status Register */
#define BCHP_XPT_DPCR2_INTR_STATUS_REG_EN        0x00a0610c /* [RW] Interrupt Status Enable Register */
#define BCHP_XPT_DPCR2_STC_EXT_CTRL              0x00a06110 /* [RW] Data Transport PCR STC Extension Control Register */
#define BCHP_XPT_DPCR2_MAX_PCR_ERROR             0x00a06120 /* [RW] Data Transport PCR Max PCR Error Register */
#define BCHP_XPT_DPCR2_SEND_BASE                 0x00a06124 /* [RW] Data Transport PCR Send Base Register */
#define BCHP_XPT_DPCR2_SEND_EXT                  0x00a06128 /* [RW] Data Transport PCR Send Extension Register */
#define BCHP_XPT_DPCR2_STC_EXT_CTRL27            0x00a0612c /* [RO] Data Transport PCR STC Extension Control Register (Test Only) */
#define BCHP_XPT_DPCR2_STC_HI                    0x00a06130 /* [RO] Data Transport PCR STC MSBs Register */
#define BCHP_XPT_DPCR2_STC_LO                    0x00a06134 /* [RO] Data Transport PCR STC LSBs Register */
#define BCHP_XPT_DPCR2_PWM_CTRLVALUE             0x00a06138 /* [RO] Data Transport PCR PWM Control Value Register */
#define BCHP_XPT_DPCR2_LAST_PCR_HI               0x00a0613c /* [RO] Data Transport PCR Last PCR MSBs Register */
#define BCHP_XPT_DPCR2_LAST_PCR_LO               0x00a06140 /* [RO] Data Transport PCR Last PCR LSBs Register */
#define BCHP_XPT_DPCR2_STC_BASE_LSBS             0x00a06148 /* [RO] Data Transport PCR STC Base LSBs Register */
#define BCHP_XPT_DPCR2_PHASE_ERROR               0x00a0614c /* [RO] Timebase Last Phase Error */
#define BCHP_XPT_DPCR2_LOOP_CTRL                 0x00a06150 /* [RW] Timebase Control */
#define BCHP_XPT_DPCR2_REF_PCR_PRESCALE          0x00a06154 /* [RW] Timebase Frequency Reference Prescale Control */
#define BCHP_XPT_DPCR2_REF_PCR_INC               0x00a06158 /* [RW] Timebase Frequency Reference Increment Control */
#define BCHP_XPT_DPCR2_CENTER                    0x00a0615c /* [RW] Timebase Center Frequency */
#define BCHP_XPT_DPCR2_ACCUM_VALUE               0x00a06160 /* [RW] Timebase Loop Filter Integrator */
#define BCHP_XPT_DPCR2_PCR_COUNT                 0x00a06164 /* [RO] Data Transport PCR Phase Error Register */
#define BCHP_XPT_DPCR2_SOFT_PCR_CTRL             0x00a06168 /* [RW] Data Transport Soft PCR Control Register */
#define BCHP_XPT_DPCR2_SOFT_PCR_BASE             0x00a0616c /* [RW] Data Transport Soft PCR BASE Register */
#define BCHP_XPT_DPCR2_SOFT_PCR_EXT              0x00a06170 /* [RW] Data Transport Soft PCR Extension Register */
#define BCHP_XPT_DPCR2_PHASE_ERROR_CLAMP         0x00a06174 /* [RW] Timebase Phase Error Control */

#endif /* #ifndef BCHP_XPT_DPCR2_H__ */

/* End of File */

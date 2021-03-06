/***************************************************************************
 *     Copyright (c) 1999-2013, Broadcom Corporation
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
 * Date:           Generated on              Mon Dec 23 13:19:22 2013
 *                 Full Compile MD5 Checksum e5d1378cc1475b750905e70cb70c73d9
 *                   (minus title and desc)  
 *                 MD5 Checksum              aa943f3142a624837db5321711723fcf
 *
 * Compiled with:  RDB Utility               combo_header.pl
 *                 RDB Parser                3.0
 *                 unknown                   unknown
 *                 Perl Interpreter          5.008008
 *                 Operating System          linux
 *
 * Revision History:
 *
 * $brcm_Log: $
 * 
 ***************************************************************************/

#ifndef BCHP_XPT_DPCR6_H__
#define BCHP_XPT_DPCR6_H__

/***************************************************************************
 *XPT_DPCR6 - XPT DPCR6 Control Registers
 ***************************************************************************/
#define BCHP_XPT_DPCR6_PID_CH                    0x00a02300 /* Data Transport PCR PID Channel Register */
#define BCHP_XPT_DPCR6_CTRL                      0x00a02304 /* Data Transport PCR Control Register */
#define BCHP_XPT_DPCR6_INTR_STATUS_REG           0x00a02308 /* Interrupt Status Register */
#define BCHP_XPT_DPCR6_INTR_STATUS_REG_EN        0x00a0230c /* Interrupt Status Enable Register */
#define BCHP_XPT_DPCR6_STC_EXT_CTRL              0x00a02310 /* Data Transport PCR STC Extension Control Register */
#define BCHP_XPT_DPCR6_MAX_PCR_ERROR             0x00a02320 /* Data Transport PCR Max PCR Error Register */
#define BCHP_XPT_DPCR6_SEND_BASE                 0x00a02324 /* Data Transport PCR Send Base Register */
#define BCHP_XPT_DPCR6_SEND_EXT                  0x00a02328 /* Data Transport PCR Send Extension Register */
#define BCHP_XPT_DPCR6_STC_EXT_CTRL27            0x00a0232c /* Data Transport PCR STC Extension Control Register (Test Only) */
#define BCHP_XPT_DPCR6_STC_HI                    0x00a02330 /* Data Transport PCR STC MSBs Register */
#define BCHP_XPT_DPCR6_STC_LO                    0x00a02334 /* Data Transport PCR STC LSBs Register */
#define BCHP_XPT_DPCR6_PWM_CTRLVALUE             0x00a02338 /* Data Transport PCR PWM Control Value Register */
#define BCHP_XPT_DPCR6_LAST_PCR_HI               0x00a0233c /* Data Transport PCR Last PCR MSBs Register */
#define BCHP_XPT_DPCR6_LAST_PCR_LO               0x00a02340 /* Data Transport PCR Last PCR LSBs Register */
#define BCHP_XPT_DPCR6_STC_BASE_LSBS             0x00a02348 /* Data Transport PCR STC Base LSBs Register */
#define BCHP_XPT_DPCR6_PHASE_ERROR               0x00a0234c /* Timebase Last Phase Error */
#define BCHP_XPT_DPCR6_LOOP_CTRL                 0x00a02350 /* Timebase Control */
#define BCHP_XPT_DPCR6_REF_PCR_PRESCALE          0x00a02354 /* Timebase Frequency Reference Prescale Control */
#define BCHP_XPT_DPCR6_REF_PCR_INC               0x00a02358 /* Timebase Frequency Reference Increment Control */
#define BCHP_XPT_DPCR6_CENTER                    0x00a0235c /* Timebase Center Frequency */
#define BCHP_XPT_DPCR6_ACCUM_VALUE               0x00a02360 /* Timebase Loop Filter Integrator */
#define BCHP_XPT_DPCR6_PCR_COUNT                 0x00a02364 /* Data Transport PCR Phase Error Register */
#define BCHP_XPT_DPCR6_SOFT_PCR_CTRL             0x00a02368 /* Data Transport Soft PCR Control Register */
#define BCHP_XPT_DPCR6_SOFT_PCR_BASE             0x00a0236c /* Data Transport Soft PCR BASE Register */
#define BCHP_XPT_DPCR6_SOFT_PCR_EXT              0x00a02370 /* Data Transport Soft PCR Extension Register */
#define BCHP_XPT_DPCR6_PHASE_ERROR_CLAMP         0x00a02374 /* Timebase Phase Error Control */

#endif /* #ifndef BCHP_XPT_DPCR6_H__ */

/* End of File */

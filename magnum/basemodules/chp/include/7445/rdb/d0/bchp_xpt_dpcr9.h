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
 * Date:           Generated on              Mon Sep 23 09:50:32 2013
 *                 Full Compile MD5 Checksum fcccce298b546dd6a1f4cbad288478da
 *                   (minus title and desc)  
 *                 MD5 Checksum              211556602e37a33262598b3d5eeba81c
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

#ifndef BCHP_XPT_DPCR9_H__
#define BCHP_XPT_DPCR9_H__

/***************************************************************************
 *XPT_DPCR9 - XPT DPCR9 Control Registers
 ***************************************************************************/
#define BCHP_XPT_DPCR9_PID_CH                    0x00a02480 /* Data Transport PCR PID Channel Register */
#define BCHP_XPT_DPCR9_CTRL                      0x00a02484 /* Data Transport PCR Control Register */
#define BCHP_XPT_DPCR9_INTR_STATUS_REG           0x00a02488 /* Interrupt Status Register */
#define BCHP_XPT_DPCR9_INTR_STATUS_REG_EN        0x00a0248c /* Interrupt Status Enable Register */
#define BCHP_XPT_DPCR9_STC_EXT_CTRL              0x00a02490 /* Data Transport PCR STC Extension Control Register */
#define BCHP_XPT_DPCR9_MAX_PCR_ERROR             0x00a024a0 /* Data Transport PCR Max PCR Error Register */
#define BCHP_XPT_DPCR9_SEND_BASE                 0x00a024a4 /* Data Transport PCR Send Base Register */
#define BCHP_XPT_DPCR9_SEND_EXT                  0x00a024a8 /* Data Transport PCR Send Extension Register */
#define BCHP_XPT_DPCR9_STC_EXT_CTRL27            0x00a024ac /* Data Transport PCR STC Extension Control Register (Test Only) */
#define BCHP_XPT_DPCR9_STC_HI                    0x00a024b0 /* Data Transport PCR STC MSBs Register */
#define BCHP_XPT_DPCR9_STC_LO                    0x00a024b4 /* Data Transport PCR STC LSBs Register */
#define BCHP_XPT_DPCR9_PWM_CTRLVALUE             0x00a024b8 /* Data Transport PCR PWM Control Value Register */
#define BCHP_XPT_DPCR9_LAST_PCR_HI               0x00a024bc /* Data Transport PCR Last PCR MSBs Register */
#define BCHP_XPT_DPCR9_LAST_PCR_LO               0x00a024c0 /* Data Transport PCR Last PCR LSBs Register */
#define BCHP_XPT_DPCR9_STC_BASE_LSBS             0x00a024c8 /* Data Transport PCR STC Base LSBs Register */
#define BCHP_XPT_DPCR9_PHASE_ERROR               0x00a024cc /* Timebase Last Phase Error */
#define BCHP_XPT_DPCR9_LOOP_CTRL                 0x00a024d0 /* Timebase Control */
#define BCHP_XPT_DPCR9_REF_PCR_PRESCALE          0x00a024d4 /* Timebase Frequency Reference Prescale Control */
#define BCHP_XPT_DPCR9_REF_PCR_INC               0x00a024d8 /* Timebase Frequency Reference Increment Control */
#define BCHP_XPT_DPCR9_CENTER                    0x00a024dc /* Timebase Center Frequency */
#define BCHP_XPT_DPCR9_ACCUM_VALUE               0x00a024e0 /* Timebase Loop Filter Integrator */
#define BCHP_XPT_DPCR9_PCR_COUNT                 0x00a024e4 /* Data Transport PCR Phase Error Register */
#define BCHP_XPT_DPCR9_SOFT_PCR_CTRL             0x00a024e8 /* Data Transport Soft PCR Control Register */
#define BCHP_XPT_DPCR9_SOFT_PCR_BASE             0x00a024ec /* Data Transport Soft PCR BASE Register */
#define BCHP_XPT_DPCR9_SOFT_PCR_EXT              0x00a024f0 /* Data Transport Soft PCR Extension Register */
#define BCHP_XPT_DPCR9_PHASE_ERROR_CLAMP         0x00a024f4 /* Timebase Phase Error Control */

#endif /* #ifndef BCHP_XPT_DPCR9_H__ */

/* End of File */

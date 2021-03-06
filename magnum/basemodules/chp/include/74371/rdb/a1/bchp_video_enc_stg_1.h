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
 * Date:           Generated on               Fri Feb 20 00:05:23 2015
 *                 Full Compile MD5 Checksum  f4a546a20d0bd1f244e0d6a139e85ce0
 *                     (minus title and desc)
 *                 MD5 Checksum               a9d9eeea3a1c30a122d08de69d07786c
 *
 * Compiled with:  RDB Utility                combo_header.pl
 *                 RDB.pm                     15715
 *                 unknown                    unknown
 *                 Perl Interpreter           5.008008
 *                 Operating System           linux
 *
 *
 ***************************************************************************/

#ifndef BCHP_VIDEO_ENC_STG_1_H__
#define BCHP_VIDEO_ENC_STG_1_H__

/***************************************************************************
 *VIDEO_ENC_STG_1 - VEC Simple Trigger Generator Controls
 ***************************************************************************/
#define BCHP_VIDEO_ENC_STG_1_REVISION_ID         0x006a6d00 /* [RO] STG REVISION ID register */
#define BCHP_VIDEO_ENC_STG_1_BVB_SIZE            0x006a6d04 /* [RW] BVB Size Register. */
#define BCHP_VIDEO_ENC_STG_1_BVB_RSTATUS         0x006a6d08 /* [RO] BVB status read Register. */
#define BCHP_VIDEO_ENC_STG_1_BVB_CSTATUS         0x006a6d0c /* [WO] BVB status clear Register. */
#define BCHP_VIDEO_ENC_STG_1_CONTROL             0x006a6d10 /* [RW] STG CONTROL Register */
#define BCHP_VIDEO_ENC_STG_1_DOWN_SAMP           0x006a6d14 /* [RW] STG DOWN SAMPLING Register */
#define BCHP_VIDEO_ENC_STG_1_STATUS              0x006a6d18 /* [RO] STG STATUS Register */
#define BCHP_VIDEO_ENC_STG_1_STATUS_CLR          0x006a6d1c /* [WO] STG STATUS CLEAR Register */
#define BCHP_VIDEO_ENC_STG_1_HOST_ARM            0x006a6d20 /* [RW] STG  HOST ARM register */
#define BCHP_VIDEO_ENC_STG_1_FRAME_SIZE          0x006a6d24 /* [RW] STG  Frame size */
#define BCHP_VIDEO_ENC_STG_1_CRC_SIG             0x006a6d28 /* [RO] STG  CRC signature */
#define BCHP_VIDEO_ENC_STG_1_FORCE_EOP_TOP_TRIG  0x006a6d2c /* [WO] STG FORCE EOP Trigger */
#define BCHP_VIDEO_ENC_STG_1_FORCE_EOP_BOT_TRIG  0x006a6d30 /* [WO] STG FORCE EOP Trigger */
#define BCHP_VIDEO_ENC_STG_1_FORCE_TIMER_TOP_TRIG 0x006a6d34 /* [WO] STG FORCE TIMER Trigger */
#define BCHP_VIDEO_ENC_STG_1_FORCE_TIMER_BOT_TRIG 0x006a6d38 /* [WO] STG FORCE TIMER Trigger */
#define BCHP_VIDEO_ENC_STG_1_STC_CONTROL         0x006a6d3c /* [RW] STG STC control register */
#define BCHP_VIDEO_ENC_STG_1_CRC_CONTROL         0x006a6d40 /* [RW] STG CRC control register */
#define BCHP_VIDEO_ENC_STG_1_REPEAT_POLARITY     0x006a6d44 /* [RW] STG REPEAT POLARITY register */
#define BCHP_VIDEO_ENC_STG_1_EOP_TRIGGER_DELAY   0x006a6d48 /* [RW] STG EOP TRIGGER DELAY register */

#endif /* #ifndef BCHP_VIDEO_ENC_STG_1_H__ */

/* End of File */

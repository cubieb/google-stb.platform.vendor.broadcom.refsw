/***************************************************************************
 *     Copyright (c) 1999-2012, Broadcom Corporation
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
 * Date:           Generated on         Fri Jul 20 11:24:20 2012
 *                 MD5 Checksum         d41d8cd98f00b204e9800998ecf8427e
 *
 * Compiled with:  RDB Utility          combo_header.pl
 *                 RDB Parser           3.0
 *                 unknown              unknown
 *                 Perl Interpreter     5.008008
 *                 Operating System     linux
 *
 * Revision History:
 *
 * $brcm_Log: $
 * 
 ***************************************************************************/

#ifndef BCHP_SDS_HP_4_H__
#define BCHP_SDS_HP_4_H__

/***************************************************************************
 *SDS_HP_4 - SDS Header Processor Register Set 4
 ***************************************************************************/
#define BCHP_SDS_HP_4_HPCONTROL                  0x000d8300 /* Header Processor control */
#define BCHP_SDS_HP_4_HPCONFIG                   0x000d8304 /* Header Processor configuration */
#define BCHP_SDS_HP_4_FNORM                      0x000d8308 /* Fs/Fb ratio used in divider to scale carrier offset measured in symbol rate to sample rate */
#define BCHP_SDS_HP_4_HPOVERRIDE                 0x000d8314 /* Software override of header processor control outputs */
#define BCHP_SDS_HP_4_FROF1                      0x000d8318 /* DAFE frequency offset estimate based on SOF symbols only during acquisition */
#define BCHP_SDS_HP_4_FROF2                      0x000d831c /* DAFE frequency offset estimate based on all 90 DVB-S2 header symbols averaged over a number of frames during acquisition */
#define BCHP_SDS_HP_4_FROF3                      0x000d8320 /* DAFE frequency offset estimate based on all 90 DVB-S2 header symbols during tracking */
#define BCHP_SDS_HP_4_FROF1_SW                   0x000d8324 /* DAFE frequency offset estimate based on SOF symbols only during acquisition */
#define BCHP_SDS_HP_4_FROF2_SW                   0x000d8328 /* DAFE frequency offset estimate based on all 90 DVB-S2 header symbols averaged over a number of frames during acquisition */
#define BCHP_SDS_HP_4_FROF3_SW                   0x000d832c /* DAFE frequency offset estimate based on all 90 DVB-S2 header symbols during tracking */
#define BCHP_SDS_HP_4_M_N_PEAK_VERIFY            0x000d8330 /* N and M parameters for Peak Verify state */
#define BCHP_SDS_HP_4_M_N_RECEIVER_VERIFY        0x000d8334 /* N and M parameters for Receiver Verify state */
#define BCHP_SDS_HP_4_M_N_RECEIVER_LOCK          0x000d8338 /* N and M parameters for Receiver Lock state */
#define BCHP_SDS_HP_4_DCORR_THRESHOLD            0x000d833c /* Differential correlator threshold */
#define BCHP_SDS_HP_4_PLHDRSCR1                  0x000d8370 /* PL Header Scrambling Sequence 1 */
#define BCHP_SDS_HP_4_PLHDRSCR2                  0x000d8374 /* PL Header Scrambling Sequence 2 */
#define BCHP_SDS_HP_4_PLHDRSCR3                  0x000d8378 /* PL Header Scrambling Sequence 3 */
#define BCHP_SDS_HP_4_ACM_CHECK                  0x000d837c /* ACM modcod, type, and spectrum inversion parameter status */
#define BCHP_SDS_HP_4_FRAME_LENGTH_INITIAL       0x000d8380 /* Frame length during initial acquisition for FECFRAME=normal or FECFRAME=short. */
#define BCHP_SDS_HP_4_FRAME_LENGTH_DUMMY_NORMAL  0x000d8384 /* Dummy frame length for FECFRAME=normal. */
#define BCHP_SDS_HP_4_FRAME_LENGTH_QPSK_NORMAL   0x000d8388 /* QPSK frame length for FECFRAME=normal. */
#define BCHP_SDS_HP_4_FRAME_LENGTH_8PSK_NORMAL   0x000d838c /* 8PSK frame length for FECFRAME=normal. */
#define BCHP_SDS_HP_4_FRAME_LENGTH_16APSK_NORMAL 0x000d8390 /* 16APSK frame length for FECFRAME=normal. */
#define BCHP_SDS_HP_4_FRAME_LENGTH_32APSK_NORMAL 0x000d8394 /* 32APSK frame length for FECFRAME=normal. */
#define BCHP_SDS_HP_4_FRAME_LENGTH_RESERVED_29_NORMAL 0x000d8398 /* MODCOD=29 frame length for FECFRAME=normal. */
#define BCHP_SDS_HP_4_FRAME_LENGTH_RESERVED_30_NORMAL 0x000d839c /* MODCOD=30 frame length for FECFRAME=normal. */
#define BCHP_SDS_HP_4_FRAME_LENGTH_RESERVED_31_NORMAL 0x000d83a0 /* MODCOD=31 frame length for FECFRAME=normal. */
#define BCHP_SDS_HP_4_FRAME_LENGTH_DUMMY_SHORT   0x000d83a8 /* Dummy frame length for FECFRAME=short. */
#define BCHP_SDS_HP_4_FRAME_LENGTH_QPSK_SHORT    0x000d83ac /* QPSK frame length for FECFRAME=short. */
#define BCHP_SDS_HP_4_FRAME_LENGTH_8PSK_SHORT    0x000d83b0 /* 8PSK frame length for FECFRAME=short. */
#define BCHP_SDS_HP_4_FRAME_LENGTH_16APSK_SHORT  0x000d83b4 /* 16APSK frame length for FECFRAME=short. */
#define BCHP_SDS_HP_4_FRAME_LENGTH_32APSK_SHORT  0x000d83b8 /* 32APSK frame length for FECFRAME=short. */
#define BCHP_SDS_HP_4_FRAME_LENGTH_RESERVED_29_SHORT 0x000d83bc /* MODCOD=29 frame length for FECFRAME=short. */
#define BCHP_SDS_HP_4_FRAME_LENGTH_RESERVED_30_SHORT 0x000d83c0 /* MODCOD=30 frame length for FECFRAME=short. */
#define BCHP_SDS_HP_4_FRAME_LENGTH_RESERVED_31_SHORT 0x000d83c4 /* MODCOD=31 frame length for FECFRAME=short. */
#define BCHP_SDS_HP_4_FRAME_LENGTH_SAMPLE        0x000d83c8 /* Frame length for running peak sampling logic. */
#define BCHP_SDS_HP_4_PEAK_SAMPLE_0              0x000d83d0 /* Peak sampling amplitude 0. Sample 0 is the smallest amplitude. */
#define BCHP_SDS_HP_4_PEAK_SAMPLE_1              0x000d83d4 /* Peak sampling amplitude 1. */
#define BCHP_SDS_HP_4_PEAK_SAMPLE_2              0x000d83d8 /* Peak sampling amplitude 2. */
#define BCHP_SDS_HP_4_PEAK_SAMPLE_3              0x000d83dc /* Peak sampling amplitude 3. Sample 3 is the largest amplitude. */
#define BCHP_SDS_HP_4_HP_DAFE                    0x000d83e0 /* DAFE parameter control */
#define BCHP_SDS_HP_4_NEW_STATE                  0x000d83e4 /* State machine control for new state */
#define BCHP_SDS_HP_4_IGNORE_PHI_FROM_DAFE       0x000d83e8 /* RM Decoder derotation control */

#endif /* #ifndef BCHP_SDS_HP_4_H__ */

/* End of File */

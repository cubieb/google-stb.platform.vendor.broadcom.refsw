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
 * Date:           Generated on               Fri Aug 15 15:20:56 2014
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

#ifndef BCHP_SDS_HP_1_H__
#define BCHP_SDS_HP_1_H__

/***************************************************************************
 *SDS_HP_1 - SDS Header Processor Register Set
 ***************************************************************************/
#define BCHP_SDS_HP_1_HPCONTROL                  0x01241300 /* [RW] Header Processor control */
#define BCHP_SDS_HP_1_HPCONFIG                   0x01241304 /* [RW] Header Processor configuration */
#define BCHP_SDS_HP_1_FNORM                      0x01241308 /* [RW] Fs/Fb ratio used in divider to scale carrier offset measured in symbol rate to sample rate */
#define BCHP_SDS_HP_1_HPOVERRIDE                 0x01241314 /* [RW] Software override of header processor control outputs */
#define BCHP_SDS_HP_1_FROF1                      0x01241318 /* [RO] DAFE frequency offset estimate based on SOF symbols only during acquisition */
#define BCHP_SDS_HP_1_FROF2                      0x0124131c /* [RO] DAFE frequency offset estimate based on all 90 DVB-S2 header symbols averaged over a number of frames during acquisition */
#define BCHP_SDS_HP_1_FROF3                      0x01241320 /* [RO] DAFE frequency offset estimate based on all 90 DVB-S2 header symbols during tracking */
#define BCHP_SDS_HP_1_FROF1_SW                   0x01241324 /* [RW] DAFE frequency offset estimate based on SOF symbols only during acquisition */
#define BCHP_SDS_HP_1_FROF2_SW                   0x01241328 /* [RW] DAFE frequency offset estimate based on all 90 DVB-S2 header symbols averaged over a number of frames during acquisition */
#define BCHP_SDS_HP_1_FROF3_SW                   0x0124132c /* [RW] DAFE frequency offset estimate based on all 90 DVB-S2 header symbols during tracking */
#define BCHP_SDS_HP_1_M_N_PEAK_VERIFY            0x01241330 /* [RW] N and M parameters for Peak Verify state */
#define BCHP_SDS_HP_1_M_N_RECEIVER_VERIFY        0x01241334 /* [RW] N and M parameters for Receiver Verify state */
#define BCHP_SDS_HP_1_M_N_RECEIVER_LOCK          0x01241338 /* [RW] N and M parameters for Receiver Lock state */
#define BCHP_SDS_HP_1_DCORR_THRESHOLD            0x0124133c /* [RW] Differential correlator threshold */
#define BCHP_SDS_HP_1_PLHDRSCR1                  0x01241370 /* [RW] PL Header Scrambling Sequence 1 */
#define BCHP_SDS_HP_1_PLHDRSCR2                  0x01241374 /* [RW] PL Header Scrambling Sequence 2 */
#define BCHP_SDS_HP_1_PLHDRSCR3                  0x01241378 /* [RW] PL Header Scrambling Sequence 3 */
#define BCHP_SDS_HP_1_ACM_CHECK                  0x0124137c /* [RO] ACM modcod, type, and spectrum inversion parameter status */
#define BCHP_SDS_HP_1_FRAME_LENGTH_INITIAL       0x01241380 /* [RW] Frame length during initial acquisition for FECFRAME=normal or FECFRAME=short. */
#define BCHP_SDS_HP_1_FRAME_LENGTH_DUMMY_NORMAL  0x01241384 /* [RW] Dummy frame length for FECFRAME=normal. */
#define BCHP_SDS_HP_1_FRAME_LENGTH_QPSK_NORMAL   0x01241388 /* [RW] QPSK frame length for FECFRAME=normal. */
#define BCHP_SDS_HP_1_FRAME_LENGTH_8PSK_NORMAL   0x0124138c /* [RW] 8PSK frame length for FECFRAME=normal. */
#define BCHP_SDS_HP_1_FRAME_LENGTH_16APSK_NORMAL 0x01241390 /* [RW] 16APSK frame length for FECFRAME=normal. */
#define BCHP_SDS_HP_1_FRAME_LENGTH_32APSK_NORMAL 0x01241394 /* [RW] 32APSK frame length for FECFRAME=normal. */
#define BCHP_SDS_HP_1_FRAME_LENGTH_RESERVED_29_NORMAL 0x01241398 /* [RW] MODCOD=29 frame length for FECFRAME=normal. */
#define BCHP_SDS_HP_1_FRAME_LENGTH_RESERVED_30_NORMAL 0x0124139c /* [RW] MODCOD=30 frame length for FECFRAME=normal. */
#define BCHP_SDS_HP_1_FRAME_LENGTH_RESERVED_31_NORMAL 0x012413a0 /* [RW] MODCOD=31 frame length for FECFRAME=normal. */
#define BCHP_SDS_HP_1_FRAME_LENGTH_DUMMY_SHORT   0x012413a8 /* [RW] Dummy frame length for FECFRAME=short. */
#define BCHP_SDS_HP_1_FRAME_LENGTH_QPSK_SHORT    0x012413ac /* [RW] QPSK frame length for FECFRAME=short. */
#define BCHP_SDS_HP_1_FRAME_LENGTH_8PSK_SHORT    0x012413b0 /* [RW] 8PSK frame length for FECFRAME=short. */
#define BCHP_SDS_HP_1_FRAME_LENGTH_16APSK_SHORT  0x012413b4 /* [RW] 16APSK frame length for FECFRAME=short. */
#define BCHP_SDS_HP_1_FRAME_LENGTH_32APSK_SHORT  0x012413b8 /* [RW] 32APSK frame length for FECFRAME=short. */
#define BCHP_SDS_HP_1_FRAME_LENGTH_RESERVED_29_SHORT 0x012413bc /* [RW] MODCOD=29 frame length for FECFRAME=short. */
#define BCHP_SDS_HP_1_FRAME_LENGTH_RESERVED_30_SHORT 0x012413c0 /* [RW] MODCOD=30 frame length for FECFRAME=short. */
#define BCHP_SDS_HP_1_FRAME_LENGTH_RESERVED_31_SHORT 0x012413c4 /* [RW] MODCOD=31 frame length for FECFRAME=short. */
#define BCHP_SDS_HP_1_FRAME_LENGTH_SAMPLE        0x012413c8 /* [RW] Frame length for running peak sampling logic. */
#define BCHP_SDS_HP_1_PEAK_SAMPLE_0              0x012413d0 /* [RO] Peak sampling amplitude 0. Sample 0 is the smallest amplitude. */
#define BCHP_SDS_HP_1_PEAK_SAMPLE_1              0x012413d4 /* [RO] Peak sampling amplitude 1. */
#define BCHP_SDS_HP_1_PEAK_SAMPLE_2              0x012413d8 /* [RO] Peak sampling amplitude 2. */
#define BCHP_SDS_HP_1_PEAK_SAMPLE_3              0x012413dc /* [RO] Peak sampling amplitude 3. Sample 3 is the largest amplitude. */
#define BCHP_SDS_HP_1_HP_DAFE                    0x012413e0 /* [RW] DAFE parameter control */
#define BCHP_SDS_HP_1_NEW_STATE                  0x012413e4 /* [RW] State machine control for new state */
#define BCHP_SDS_HP_1_IGNORE_PHI_FROM_DAFE       0x012413e8 /* [RW] RM Decoder derotation control */

#endif /* #ifndef BCHP_SDS_HP_1_H__ */

/* End of File */

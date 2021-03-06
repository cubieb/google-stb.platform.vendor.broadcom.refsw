/***************************************************************************
 *     Copyright (c) 1999-2011, Broadcom Corporation
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
 * Date:           Generated on         Wed Jan 12 18:41:25 2011
 *                 MD5 Checksum         6e6727f6c827233acdd395c9a9032c98
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

#ifndef BCHP_SDS_VIT_5_H__
#define BCHP_SDS_VIT_5_H__

/***************************************************************************
 *SDS_VIT_5 - SDS Viterbi Decoder Register Set 5
 ***************************************************************************/
#define BCHP_SDS_VIT_5_VTCTL                     0x000d8400 /* Viterbi Decoder Configuration Register (Formerly,VTCTL2,VTCTL1) */
#define BCHP_SDS_VIT_5_V10                       0x000d8404 /* Viterbi decoder sync error threshold 1/0 (Formerly, V1,V0, DVB/DTV 2/3, DC 1/2 */
#define BCHP_SDS_VIT_5_V32                       0x000d8408 /* Viterbi decoder sync error threshold 3/2 (Formerly, V3,V2, DVB/DTV 5/6, DC 2/3 */
#define BCHP_SDS_VIT_5_V54                       0x000d840c /* Viterbi decoder sync error threshold 5/4 (Formerly, V5,V4, DVB/DTV 7/8, DC 4/5 */
#define BCHP_SDS_VIT_5_V76                       0x000d8410 /* Viterbi decoder sync error threshold 7/6 (Formerly, V7,V6, DVB/DTV unused, DC 7/8 */
#define BCHP_SDS_VIT_5_VINT                      0x000d8414 /* Viterbi decoder sync integration period */
#define BCHP_SDS_VIT_5_VCNT                      0x000d8418 /* Viterbi decoder integration counter value */
#define BCHP_SDS_VIT_5_VSTC                      0x000d841c /* Viterbi decoder state change counter values */
#define BCHP_SDS_VIT_5_VST                       0x000d8420 /* Viterbi decoder internal status monitor */
#define BCHP_SDS_VIT_5_VREC                      0x000d8424 /* Viterbi re-encoding register error value */
#define BCHP_SDS_VIT_5_VRCV                      0x000d8428 /* Viterbi re-encoding register count value */

#endif /* #ifndef BCHP_SDS_VIT_5_H__ */

/* End of File */

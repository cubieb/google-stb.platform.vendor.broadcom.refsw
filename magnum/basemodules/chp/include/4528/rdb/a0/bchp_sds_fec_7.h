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
 * Date:           Generated on         Wed Jan 12 18:41:07 2011
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

#ifndef BCHP_SDS_FEC_7_H__
#define BCHP_SDS_FEC_7_H__

/***************************************************************************
 *SDS_FEC_7 - SDS FEC Register Set 7
 ***************************************************************************/
#define BCHP_SDS_FEC_7_FECTL                     0x000e8440 /* Reed-Solomon Control Register */
#define BCHP_SDS_FEC_7_FSYN                      0x000e8444 /* RS sync acquisition/retention total and bad headers */
#define BCHP_SDS_FEC_7_FRS                       0x000e8448 /* RS sync retention total and bad blocks and sync inverse max */
#define BCHP_SDS_FEC_7_FMOD                      0x000e844c /* RS Mode */
#define BCHP_SDS_FEC_7_FERR                      0x000e8450 /* RS correctable and uncorrectable blocks */
#define BCHP_SDS_FEC_7_FRSV                      0x000e8454 /* RS Digicipher II packet header reserved words */

#endif /* #ifndef BCHP_SDS_FEC_7_H__ */

/* End of File */

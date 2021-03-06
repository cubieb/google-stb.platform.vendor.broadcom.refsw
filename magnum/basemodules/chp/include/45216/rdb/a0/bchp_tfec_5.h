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
 * Date:           Generated on              Thu Feb 20 15:33:52 2014
 *                 Full Compile MD5 Checksum 1766fea499add5f6ee91330ef96d35c5
 *                   (minus title and desc)
 *                 MD5 Checksum              4c358fb5b94802f03aec82d8df2c9afa
 *
 * Compiled with:  RDB Utility               combo_header.pl
 *                 RDB Parser                3.0
 *                 unknown                   unknown
 *                 Perl Interpreter          5.008008
 *                 Operating System          linux
 *
 *
 ***************************************************************************/



/****************************************************************************
 ***************************************************************************/

#ifndef BCHP_TFEC_5_H__
#define BCHP_TFEC_5_H__

/***************************************************************************
 *TFEC_5 - SDS TFEC Register Set
 ***************************************************************************/
#define BCHP_TFEC_5_TFECTL                       0x05500000 /* Advanced FEC Control */
#define BCHP_TFEC_5_TNBLK                        0x05500014 /* RS total block count */
#define BCHP_TFEC_5_TCBLK                        0x05500018 /* RS corrected block count */
#define BCHP_TFEC_5_TBBLK                        0x0550001c /* RS bad block count */
#define BCHP_TFEC_5_TCSYM                        0x05500020 /* RS corrected symbol count */
#define BCHP_TFEC_5_TFMT                         0x05500024 /* RS parameters */
#define BCHP_TFEC_5_TPAK                         0x05500028 /* MPEG packetizer parameters */
#define BCHP_TFEC_5_TSSQ                         0x0550002c /* Advanced FEC symbol sequence */
#define BCHP_TFEC_5_TSYN                         0x05500030 /* MPEG synchronizer parameters */
#define BCHP_TFEC_5_TTUR                         0x05500034 /* Advanced FEC configuration parameters */
#define BCHP_TFEC_5_TZPK                         0x05500038 /* RS synchronizer parameters */
#define BCHP_TFEC_5_TZSY                         0x0550003c /* RS synchronizer aquisition and retention parameters */
#define BCHP_TFEC_5_TITR                         0x05500040 /* Iterative decoder parameters */
#define BCHP_TFEC_5_TCIL                         0x05500044 /* Iterative decoder parameters */
#define BCHP_TFEC_5_TRSD                         0x05500048 /* RS decoder parameters */
#define BCHP_TFEC_5_TPN                          0x0550004c /* Iterative decoder internal point signature analyzer output */
#define BCHP_TFEC_5_TSIGCNT                      0x05500050 /* Signature analyzer data length count */
#define BCHP_TFEC_5_TSIGITD                      0x05500054 /* Iterative decoder signature analyzer output */
#define BCHP_TFEC_5_TSIGXPT                      0x05500058 /* Transport output signature analyzer output */
#define BCHP_TFEC_5_TTPCTL                       0x0550005c /* Advanced FEC testport control */
#define BCHP_TFEC_5_TRAWISR                      0x05500060 /* Advanced FEC raw interrupt status */

#endif /* #ifndef BCHP_TFEC_5_H__ */

/* End of File */

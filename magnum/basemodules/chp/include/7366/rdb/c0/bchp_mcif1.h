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
 * Date:           Generated on               Thu Feb 12 15:15:50 2015
 *                 Full Compile MD5 Checksum  ca339b82db08da0250a17ca09932699d
 *                     (minus title and desc)
 *                 MD5 Checksum               502556bfbdc2f4341f93db8b4326b3ab
 *
 * Compiled with:  RDB Utility                combo_header.pl
 *                 RDB.pm                     15653
 *                 unknown                    unknown
 *                 Perl Interpreter           5.008008
 *                 Operating System           linux
 *
 *
 ***************************************************************************/

#ifndef BCHP_MCIF1_H__
#define BCHP_MCIF1_H__

/***************************************************************************
 *MCIF1 - M-CARD CPU Interface - Channel 1
 ***************************************************************************/
#define BCHP_MCIF1_CONTROL                       0x0040aa80 /* [RW] MCIF CONTROL REGISTER */
#define BCHP_MCIF1_TX_BUF_PTR_LO                 0x0040aa84 /* [RW] STARTING ADDRESS OF DATA TO BE WRITTEN TO M-CARD */
#define BCHP_MCIF1_TX_BUF_PTR_HI                 0x0040aa88 /* [RW] STARTING ADDRESS OF DATA TO BE WRITTEN TO M-CARD */
#define BCHP_MCIF1_RX_BUF_PTR_LO                 0x0040aa8c /* [RW] STARTING ADDRESS OF BUFFER FOR DATA READ FROM M-CARD */
#define BCHP_MCIF1_RX_BUF_PTR_HI                 0x0040aa90 /* [RW] STARTING ADDRESS OF BUFFER FOR DATA READ FROM M-CARD */
#define BCHP_MCIF1_TX_LEN                        0x0040aa94 /* [RW] M-CARD WRITE LENGTH REGISTER */
#define BCHP_MCIF1_TX_CTRL                       0x0040aa98 /* [RW] M-CARD WRITE CONTROL REGISTER */
#define BCHP_MCIF1_RX_TEST                       0x0040aa9c /* [RO] M-CARD READ DATA STATUS FOR TEST */
#define BCHP_MCIF1_RX_STATUS                     0x0040aaa0 /* [RW] M-CARD HOST READY TO RECEIVE STATUS REGISTER */
#define BCHP_MCIF1_RX_DATA_STATUS                0x0040aaa4 /* [RO] M-CARD READ DATA STATUS REGISTER */
#define BCHP_MCIF1_SPARE                         0x0040aaa8 /* [RW] RESERVED */

#endif /* #ifndef BCHP_MCIF1_H__ */

/* End of File */

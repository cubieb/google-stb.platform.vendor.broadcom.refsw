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
 * Date:           Generated on               Thu Dec  4 13:59:01 2014
 *                 Full Compile MD5 Checksum  7f8620d6db569529bdb0529f9fa1fcf2
 *                     (minus title and desc)
 *                 MD5 Checksum               48c8fdf2af4291bac0fa2b0d5245d05c
 *
 * Compiled with:  RDB Utility                combo_header.pl
 *                 RDB.pm                     15262
 *                 unknown                    unknown
 *                 Perl Interpreter           5.008008
 *                 Operating System           linux
 *
 *
 ***************************************************************************/

#ifndef BCHP_CGMSAE_1_H__
#define BCHP_CGMSAE_1_H__

/***************************************************************************
 *CGMSAE_1 - CGMSAE_1 registers
 ***************************************************************************/
#define BCHP_CGMSAE_1_Top_Control                0x006e8904 /* [RW] CGMS-A Top-Field Control Register */
#define BCHP_CGMSAE_1_Bot_Control                0x006e8908 /* [RW] CGMS-A Bottom-Field Control Register */
#define BCHP_CGMSAE_1_Top_Format                 0x006e890c /* [RW] CGMS-A Top-Field Format Register */
#define BCHP_CGMSAE_1_Bot_Format                 0x006e8910 /* [RW] CGMS-A Bottom-Field Format Register */
#define BCHP_CGMSAE_1_Top_Data                   0x006e8914 /* [RW] CGMS-A Top-Field Data Register */
#define BCHP_CGMSAE_1_Bot_Data                   0x006e8918 /* [RW] CGMS-A Bottom-Field Data Register */
#define BCHP_CGMSAE_1_RevID                      0x006e891c /* [RO] CGMS-A Encoder Revision ID Register */
#define BCHP_CGMSAE_1_Top_Control_B              0x006e8920 /* [RW] CGMS-B Top-Field Control Register */
#define BCHP_CGMSAE_1_Bot_Control_B              0x006e8924 /* [RW] CGMS-B Bottom-Field Control Register */
#define BCHP_CGMSAE_1_Top_Format_B               0x006e8928 /* [RW] CGMS-B Top-Field Format Register */
#define BCHP_CGMSAE_1_Bot_Format_B               0x006e892c /* [RW] CGMS-B Bottom-Field Format Register */
#define BCHP_CGMSAE_1_Top_Data_B0                0x006e8930 /* [RW] CGMS-B Top-Field Data Register for 31:0 bits */
#define BCHP_CGMSAE_1_Top_Data_B1                0x006e8934 /* [RW] CGMS-B Top-Field Data Register for 63:32 bits */
#define BCHP_CGMSAE_1_Top_Data_B2                0x006e8938 /* [RW] CGMS-B Top-Field Data Register for 95:64 bits */
#define BCHP_CGMSAE_1_Top_Data_B3                0x006e893c /* [RW] CGMS-B Top-Field Data Register for 127:96 bits */
#define BCHP_CGMSAE_1_Top_Data_B4                0x006e8940 /* [RW] CGMS-B Top-Field Data Register for 159:128 bits */
#define BCHP_CGMSAE_1_Bot_Data_B0                0x006e8944 /* [RW] CGMS-B Bottom-Field Data Register for 31:0 bits */
#define BCHP_CGMSAE_1_Bot_Data_B1                0x006e8948 /* [RW] CGMS-B Bottom-Field Data Register for 63:32 bits */
#define BCHP_CGMSAE_1_Bot_Data_B2                0x006e894c /* [RW] CGMS-B Bottom-Field Data Register for 95:64 bits */
#define BCHP_CGMSAE_1_Bot_Data_B3                0x006e8950 /* [RW] CGMS-B Bottom-Field Data Register for 127:96 bits */
#define BCHP_CGMSAE_1_Bot_Data_B4                0x006e8954 /* [RW] CGMS-B Bottom-Field Data Register for 159:128 bits */
#define BCHP_CGMSAE_1_Reg_updt                   0x006e8958 /* [RW] Data Update Register */

#endif /* #ifndef BCHP_CGMSAE_1_H__ */

/* End of File */

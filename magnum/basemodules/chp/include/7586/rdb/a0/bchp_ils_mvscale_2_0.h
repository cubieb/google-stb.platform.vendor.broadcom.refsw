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
 * Date:           Generated on               Wed Feb 11 10:13:59 2015
 *                 Full Compile MD5 Checksum  f7f4bd55341805fcfe958ba5e47e65f4
 *                     (minus title and desc)
 *                 MD5 Checksum               95b679a9655597a92593cae55222c397
 *
 * Compiled with:  RDB Utility                combo_header.pl
 *                 RDB.pm                     15653
 *                 unknown                    unknown
 *                 Perl Interpreter           5.008008
 *                 Operating System           linux
 *
 *
 ***************************************************************************/

#ifndef BCHP_ILS_MVSCALE_2_0_H__
#define BCHP_ILS_MVSCALE_2_0_H__

/***************************************************************************
 *ILS_MVSCALE_2_0 - Spatial Scaler Fill Registers
 ***************************************************************************/
#define BCHP_ILS_MVSCALE_2_0_MODE                0x00147200 /* [RW] MVSCALE_MODE */
#define BCHP_ILS_MVSCALE_2_0_MVS_CTL             0x00147204 /* [RW] MVSCALE_CTL */
#define BCHP_ILS_MVSCALE_2_0_DMA_ADDR            0x00147208 /* [RW] MVSCALE_DMA_ADDR */
#define BCHP_ILS_MVSCALE_2_0_X                   0x0014720c /* [RW] MVSCALE_X */
#define BCHP_ILS_MVSCALE_2_0_Y                   0x00147210 /* [RW] MVSCALE_Y */
#define BCHP_ILS_MVSCALE_2_0_STAT                0x00147214 /* [RO] MVSCALE_STAT */
#define BCHP_ILS_MVSCALE_2_0_VECTOR_MEM_SEL      0x00147218 /* [RW] MVSCALE_VECTOR_MEM_SEL */
#define BCHP_ILS_MVSCALE_2_0_STATE_DEBUG         0x0014721c /* [RO] MVSCALE_STATE_DEBUG */
#define BCHP_ILS_MVSCALE_2_0_REFIDL0             0x00147220 /* [RO] MVSCALE_REFIDL0 */
#define BCHP_ILS_MVSCALE_2_0_REFIDL1             0x00147224 /* [RO] MVSCALE_REFIDL1 */
#define BCHP_ILS_MVSCALE_2_0_MVSCALE_DEBUG       0x00147228 /* [RO] MVSCALE_DEBUG */
#define BCHP_ILS_MVSCALE_2_0_END                 0x0014738c /* [RW] MVSCALE_END */

/***************************************************************************
 *VECTOR_MEM_%i - MVSCALE_VECTOR_MEM_0..33
 ***************************************************************************/
#define BCHP_ILS_MVSCALE_2_0_VECTOR_MEM_i_ARRAY_BASE               0x00147300
#define BCHP_ILS_MVSCALE_2_0_VECTOR_MEM_i_ARRAY_START              0
#define BCHP_ILS_MVSCALE_2_0_VECTOR_MEM_i_ARRAY_END                33
#define BCHP_ILS_MVSCALE_2_0_VECTOR_MEM_i_ARRAY_ELEMENT_SIZE       32

/***************************************************************************
 *VECTOR_MEM_%i - MVSCALE_VECTOR_MEM_0..33
 ***************************************************************************/
/* ILS_MVSCALE_2_0 :: VECTOR_MEM_i :: mvscale_ram [31:00] */
#define BCHP_ILS_MVSCALE_2_0_VECTOR_MEM_i_mvscale_ram_MASK         0xffffffff
#define BCHP_ILS_MVSCALE_2_0_VECTOR_MEM_i_mvscale_ram_SHIFT        0


#endif /* #ifndef BCHP_ILS_MVSCALE_2_0_H__ */

/* End of File */

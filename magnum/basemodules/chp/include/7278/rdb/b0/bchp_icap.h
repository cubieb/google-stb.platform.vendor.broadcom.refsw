/******************************************************************************
 *  Copyright (C) 2017 Broadcom. The term "Broadcom" refers to Broadcom Limited and/or its subsidiaries.
 *
 *  This program is the proprietary software of Broadcom and/or its licensors,
 *  and may only be used, duplicated, modified or distributed pursuant to the terms and
 *  conditions of a separate, written license agreement executed between you and Broadcom
 *  (an "Authorized License").  Except as set forth in an Authorized License, Broadcom grants
 *  no license (express or implied), right to use, or waiver of any kind with respect to the
 *  Software, and Broadcom expressly reserves all rights in and to the Software and all
 *  intellectual property rights therein.  IF YOU HAVE NO AUTHORIZED LICENSE, THEN YOU
 *  HAVE NO RIGHT TO USE THIS SOFTWARE IN ANY WAY, AND SHOULD IMMEDIATELY
 *  NOTIFY BROADCOM AND DISCONTINUE ALL USE OF THE SOFTWARE.
 *
 *  Except as expressly set forth in the Authorized License,
 *
 *  1.     This program, including its structure, sequence and organization, constitutes the valuable trade
 *  secrets of Broadcom, and you shall use all reasonable efforts to protect the confidentiality thereof,
 *  and to use this information only in connection with your use of Broadcom integrated circuit products.
 *
 *  2.     TO THE MAXIMUM EXTENT PERMITTED BY LAW, THE SOFTWARE IS PROVIDED "AS IS"
 *  AND WITH ALL FAULTS AND BROADCOM MAKES NO PROMISES, REPRESENTATIONS OR
 *  WARRANTIES, EITHER EXPRESS, IMPLIED, STATUTORY, OR OTHERWISE, WITH RESPECT TO
 *  THE SOFTWARE.  BROADCOM SPECIFICALLY DISCLAIMS ANY AND ALL IMPLIED WARRANTIES
 *  OF TITLE, MERCHANTABILITY, NONINFRINGEMENT, FITNESS FOR A PARTICULAR PURPOSE,
 *  LACK OF VIRUSES, ACCURACY OR COMPLETENESS, QUIET ENJOYMENT, QUIET POSSESSION
 *  OR CORRESPONDENCE TO DESCRIPTION. YOU ASSUME THE ENTIRE RISK ARISING OUT OF
 *  USE OR PERFORMANCE OF THE SOFTWARE.
 *
 *  3.     TO THE MAXIMUM EXTENT PERMITTED BY LAW, IN NO EVENT SHALL BROADCOM OR ITS
 *  LICENSORS BE LIABLE FOR (i) CONSEQUENTIAL, INCIDENTAL, SPECIAL, INDIRECT, OR
 *  EXEMPLARY DAMAGES WHATSOEVER ARISING OUT OF OR IN ANY WAY RELATING TO YOUR
 *  USE OF OR INABILITY TO USE THE SOFTWARE EVEN IF BROADCOM HAS BEEN ADVISED OF
 *  THE POSSIBILITY OF SUCH DAMAGES; OR (ii) ANY AMOUNT IN EXCESS OF THE AMOUNT
 *  ACTUALLY PAID FOR THE SOFTWARE ITSELF OR U.S. $1, WHICHEVER IS GREATER. THESE
 *  LIMITATIONS SHALL APPLY NOTWITHSTANDING ANY FAILURE OF ESSENTIAL PURPOSE OF
 *  ANY LIMITED REMEDY.
 *
 * Module Description:
 *                     DO NOT EDIT THIS FILE DIRECTLY
 *
 * This module was generated magically with RDB from a source description
 * file. You must edit the source file for changes to be made to this file.
 *
 * The launch point for all information concerning RDB is found at:
 *   http://bcgbu.broadcom.com/RDB/SitePages/Home.aspx
 *
 * Date:           Generated on               Thu Apr 13 10:09:30 2017
 *                 Full Compile MD5 Checksum  7f180d7646477bba2bae1a701efd9ef5
 *                     (minus title and desc)
 *                 MD5 Checksum               a2a4a53aa20c0c2f46073b879159b85d
 *
 * lock_release:   n/a
 * Compiled with:  RDB Utility                combo_header.pl
 *                 RDB.pm                     1395
 *                 unknown                    unknown
 *                 Perl Interpreter           5.008008
 *                 Operating System           linux
 *                 Script Source              tools/dvtsw/current/Linux/combo_header.pl
 *                 DVTSWVER                   LOCAL tools/dvtsw/current/Linux/combo_header.pl
 *
 *
********************************************************************************/

#ifndef BCHP_ICAP_H__
#define BCHP_ICAP_H__

/***************************************************************************
 *ICAP - Input Capture
 ***************************************************************************/
#define BCHP_ICAP_INEDGE                         0x0041a0c0 /* [RW][32] ICAP INEDGE REGISTER */
#define BCHP_ICAP_RCNT0                          0x0041a0c4 /* [RW][32] ICAP RCNT0 REGISTERS */
#define BCHP_ICAP_RCNT1                          0x0041a0c8 /* [RW][32] ICAP RCNT1 REGISTERS */
#define BCHP_ICAP_RCNT2                          0x0041a0cc /* [RW][32] ICAP RCNT2 REGISTERS */
#define BCHP_ICAP_MASK                           0x0041a0d0 /* [RW][32] ICAP MASK REGISTERS */
#define BCHP_ICAP_TCNT0MSB                       0x0041a0d4 /* [RO][32] ICAP TCNT0MSB REGISTERS */
#define BCHP_ICAP_TCNT0LSB                       0x0041a0d8 /* [RO][32] ICAP TCNT0LSB REGISTERS */
#define BCHP_ICAP_TCNT1MSB                       0x0041a0dc /* [RO][32] ICAP TCNT1MSB REGISTERS */
#define BCHP_ICAP_TCNT1LSB                       0x0041a0e0 /* [RO][32] ICAP TCNT1LSB REGISTERS */
#define BCHP_ICAP_TCNT2MSB                       0x0041a0e4 /* [RO][32] ICAP TCNT2MSB REGISTERS */
#define BCHP_ICAP_TCNT2LSB                       0x0041a0e8 /* [RO][32] ICAP TCNT2LSB REGISTERS */
#define BCHP_ICAP_RCNT3                          0x0041a0ec /* [RW][32] ICAP RCNT3 REGISTERS */
#define BCHP_ICAP_TCNT3MSB                       0x0041a0f0 /* [RO][32] ICAP TCNT3MSB REGISTERS */
#define BCHP_ICAP_TCNT3LSB                       0x0041a0f4 /* [RO][32] ICAP TCNT3LSB REGISTERS */
#define BCHP_ICAP_RST                            0x0041a0f8 /* [WO][32] ICAP RST REGISTERS */
#define BCHP_ICAP_INSTATUS                       0x0041a0fc /* [RO][32] ICAP INSTATUS REGISTERS */

/***************************************************************************
 *INEDGE - ICAP INEDGE REGISTER
 ***************************************************************************/
/* ICAP :: INEDGE :: reserved0 [31:08] */
#define BCHP_ICAP_INEDGE_reserved0_MASK                            0xffffff00
#define BCHP_ICAP_INEDGE_reserved0_SHIFT                           8

/* ICAP :: INEDGE :: icap_pedgedet [07:04] */
#define BCHP_ICAP_INEDGE_icap_pedgedet_MASK                        0x000000f0
#define BCHP_ICAP_INEDGE_icap_pedgedet_SHIFT                       4
#define BCHP_ICAP_INEDGE_icap_pedgedet_DEFAULT                     0x00000000

/* ICAP :: INEDGE :: icap_nedgedet [03:00] */
#define BCHP_ICAP_INEDGE_icap_nedgedet_MASK                        0x0000000f
#define BCHP_ICAP_INEDGE_icap_nedgedet_SHIFT                       0
#define BCHP_ICAP_INEDGE_icap_nedgedet_DEFAULT                     0x00000000

/***************************************************************************
 *RCNT0 - ICAP RCNT0 REGISTERS
 ***************************************************************************/
/* ICAP :: RCNT0 :: reserved0 [31:04] */
#define BCHP_ICAP_RCNT0_reserved0_MASK                             0xfffffff0
#define BCHP_ICAP_RCNT0_reserved0_SHIFT                            4

/* ICAP :: RCNT0 :: icap_rcntx [03:00] */
#define BCHP_ICAP_RCNT0_icap_rcntx_MASK                            0x0000000f
#define BCHP_ICAP_RCNT0_icap_rcntx_SHIFT                           0
#define BCHP_ICAP_RCNT0_icap_rcntx_DEFAULT                         0x00000000

/***************************************************************************
 *RCNT1 - ICAP RCNT1 REGISTERS
 ***************************************************************************/
/* ICAP :: RCNT1 :: reserved0 [31:04] */
#define BCHP_ICAP_RCNT1_reserved0_MASK                             0xfffffff0
#define BCHP_ICAP_RCNT1_reserved0_SHIFT                            4

/* ICAP :: RCNT1 :: icap_rcntx [03:00] */
#define BCHP_ICAP_RCNT1_icap_rcntx_MASK                            0x0000000f
#define BCHP_ICAP_RCNT1_icap_rcntx_SHIFT                           0
#define BCHP_ICAP_RCNT1_icap_rcntx_DEFAULT                         0x00000000

/***************************************************************************
 *RCNT2 - ICAP RCNT2 REGISTERS
 ***************************************************************************/
/* ICAP :: RCNT2 :: reserved0 [31:04] */
#define BCHP_ICAP_RCNT2_reserved0_MASK                             0xfffffff0
#define BCHP_ICAP_RCNT2_reserved0_SHIFT                            4

/* ICAP :: RCNT2 :: icap_rcntx [03:00] */
#define BCHP_ICAP_RCNT2_icap_rcntx_MASK                            0x0000000f
#define BCHP_ICAP_RCNT2_icap_rcntx_SHIFT                           0
#define BCHP_ICAP_RCNT2_icap_rcntx_DEFAULT                         0x00000000

/***************************************************************************
 *MASK - ICAP MASK REGISTERS
 ***************************************************************************/
/* ICAP :: MASK :: reserved0 [31:04] */
#define BCHP_ICAP_MASK_reserved0_MASK                              0xfffffff0
#define BCHP_ICAP_MASK_reserved0_SHIFT                             4

/* ICAP :: MASK :: icap_mask [03:00] */
#define BCHP_ICAP_MASK_icap_mask_MASK                              0x0000000f
#define BCHP_ICAP_MASK_icap_mask_SHIFT                             0
#define BCHP_ICAP_MASK_icap_mask_DEFAULT                           0x00000000

/***************************************************************************
 *TCNT0MSB - ICAP TCNT0MSB REGISTERS
 ***************************************************************************/
/* ICAP :: TCNT0MSB :: reserved0 [31:08] */
#define BCHP_ICAP_TCNT0MSB_reserved0_MASK                          0xffffff00
#define BCHP_ICAP_TCNT0MSB_reserved0_SHIFT                         8

/* ICAP :: TCNT0MSB :: icap_tcnt0 [07:00] */
#define BCHP_ICAP_TCNT0MSB_icap_tcnt0_MASK                         0x000000ff
#define BCHP_ICAP_TCNT0MSB_icap_tcnt0_SHIFT                        0
#define BCHP_ICAP_TCNT0MSB_icap_tcnt0_DEFAULT                      0x00000000

/***************************************************************************
 *TCNT0LSB - ICAP TCNT0LSB REGISTERS
 ***************************************************************************/
/* ICAP :: TCNT0LSB :: reserved0 [31:08] */
#define BCHP_ICAP_TCNT0LSB_reserved0_MASK                          0xffffff00
#define BCHP_ICAP_TCNT0LSB_reserved0_SHIFT                         8

/* ICAP :: TCNT0LSB :: icap_tcnt0 [07:00] */
#define BCHP_ICAP_TCNT0LSB_icap_tcnt0_MASK                         0x000000ff
#define BCHP_ICAP_TCNT0LSB_icap_tcnt0_SHIFT                        0
#define BCHP_ICAP_TCNT0LSB_icap_tcnt0_DEFAULT                      0x00000000

/***************************************************************************
 *TCNT1MSB - ICAP TCNT1MSB REGISTERS
 ***************************************************************************/
/* ICAP :: TCNT1MSB :: reserved0 [31:08] */
#define BCHP_ICAP_TCNT1MSB_reserved0_MASK                          0xffffff00
#define BCHP_ICAP_TCNT1MSB_reserved0_SHIFT                         8

/* ICAP :: TCNT1MSB :: icap_tcnt1 [07:00] */
#define BCHP_ICAP_TCNT1MSB_icap_tcnt1_MASK                         0x000000ff
#define BCHP_ICAP_TCNT1MSB_icap_tcnt1_SHIFT                        0
#define BCHP_ICAP_TCNT1MSB_icap_tcnt1_DEFAULT                      0x00000000

/***************************************************************************
 *TCNT1LSB - ICAP TCNT1LSB REGISTERS
 ***************************************************************************/
/* ICAP :: TCNT1LSB :: reserved0 [31:08] */
#define BCHP_ICAP_TCNT1LSB_reserved0_MASK                          0xffffff00
#define BCHP_ICAP_TCNT1LSB_reserved0_SHIFT                         8

/* ICAP :: TCNT1LSB :: icap_tcnt1 [07:00] */
#define BCHP_ICAP_TCNT1LSB_icap_tcnt1_MASK                         0x000000ff
#define BCHP_ICAP_TCNT1LSB_icap_tcnt1_SHIFT                        0
#define BCHP_ICAP_TCNT1LSB_icap_tcnt1_DEFAULT                      0x00000000

/***************************************************************************
 *TCNT2MSB - ICAP TCNT2MSB REGISTERS
 ***************************************************************************/
/* ICAP :: TCNT2MSB :: reserved0 [31:08] */
#define BCHP_ICAP_TCNT2MSB_reserved0_MASK                          0xffffff00
#define BCHP_ICAP_TCNT2MSB_reserved0_SHIFT                         8

/* ICAP :: TCNT2MSB :: icap_tcnt2 [07:00] */
#define BCHP_ICAP_TCNT2MSB_icap_tcnt2_MASK                         0x000000ff
#define BCHP_ICAP_TCNT2MSB_icap_tcnt2_SHIFT                        0
#define BCHP_ICAP_TCNT2MSB_icap_tcnt2_DEFAULT                      0x00000000

/***************************************************************************
 *TCNT2LSB - ICAP TCNT2LSB REGISTERS
 ***************************************************************************/
/* ICAP :: TCNT2LSB :: reserved0 [31:08] */
#define BCHP_ICAP_TCNT2LSB_reserved0_MASK                          0xffffff00
#define BCHP_ICAP_TCNT2LSB_reserved0_SHIFT                         8

/* ICAP :: TCNT2LSB :: icap_tcnt2 [07:00] */
#define BCHP_ICAP_TCNT2LSB_icap_tcnt2_MASK                         0x000000ff
#define BCHP_ICAP_TCNT2LSB_icap_tcnt2_SHIFT                        0
#define BCHP_ICAP_TCNT2LSB_icap_tcnt2_DEFAULT                      0x00000000

/***************************************************************************
 *RCNT3 - ICAP RCNT3 REGISTERS
 ***************************************************************************/
/* ICAP :: RCNT3 :: reserved0 [31:04] */
#define BCHP_ICAP_RCNT3_reserved0_MASK                             0xfffffff0
#define BCHP_ICAP_RCNT3_reserved0_SHIFT                            4

/* ICAP :: RCNT3 :: icap_rcntx [03:00] */
#define BCHP_ICAP_RCNT3_icap_rcntx_MASK                            0x0000000f
#define BCHP_ICAP_RCNT3_icap_rcntx_SHIFT                           0
#define BCHP_ICAP_RCNT3_icap_rcntx_DEFAULT                         0x00000000

/***************************************************************************
 *TCNT3MSB - ICAP TCNT3MSB REGISTERS
 ***************************************************************************/
/* ICAP :: TCNT3MSB :: reserved0 [31:08] */
#define BCHP_ICAP_TCNT3MSB_reserved0_MASK                          0xffffff00
#define BCHP_ICAP_TCNT3MSB_reserved0_SHIFT                         8

/* ICAP :: TCNT3MSB :: icap_tcnt3 [07:00] */
#define BCHP_ICAP_TCNT3MSB_icap_tcnt3_MASK                         0x000000ff
#define BCHP_ICAP_TCNT3MSB_icap_tcnt3_SHIFT                        0
#define BCHP_ICAP_TCNT3MSB_icap_tcnt3_DEFAULT                      0x00000000

/***************************************************************************
 *TCNT3LSB - ICAP TCNT3LSB REGISTERS
 ***************************************************************************/
/* ICAP :: TCNT3LSB :: reserved0 [31:08] */
#define BCHP_ICAP_TCNT3LSB_reserved0_MASK                          0xffffff00
#define BCHP_ICAP_TCNT3LSB_reserved0_SHIFT                         8

/* ICAP :: TCNT3LSB :: icap_tcnt3 [07:00] */
#define BCHP_ICAP_TCNT3LSB_icap_tcnt3_MASK                         0x000000ff
#define BCHP_ICAP_TCNT3LSB_icap_tcnt3_SHIFT                        0
#define BCHP_ICAP_TCNT3LSB_icap_tcnt3_DEFAULT                      0x00000000

/***************************************************************************
 *RST - ICAP RST REGISTERS
 ***************************************************************************/
/* ICAP :: RST :: reserved0 [31:04] */
#define BCHP_ICAP_RST_reserved0_MASK                               0xfffffff0
#define BCHP_ICAP_RST_reserved0_SHIFT                              4

/* ICAP :: RST :: icap_rst [03:00] */
#define BCHP_ICAP_RST_icap_rst_MASK                                0x0000000f
#define BCHP_ICAP_RST_icap_rst_SHIFT                               0
#define BCHP_ICAP_RST_icap_rst_DEFAULT                             0x00000000

/***************************************************************************
 *INSTATUS - ICAP INSTATUS REGISTERS
 ***************************************************************************/
/* ICAP :: INSTATUS :: reserved0 [31:04] */
#define BCHP_ICAP_INSTATUS_reserved0_MASK                          0xfffffff0
#define BCHP_ICAP_INSTATUS_reserved0_SHIFT                         4

/* ICAP :: INSTATUS :: icap_irq [03:00] */
#define BCHP_ICAP_INSTATUS_icap_irq_MASK                           0x0000000f
#define BCHP_ICAP_INSTATUS_icap_irq_SHIFT                          0
#define BCHP_ICAP_INSTATUS_icap_irq_DEFAULT                        0x00000000

#endif /* #ifndef BCHP_ICAP_H__ */

/* End of File */

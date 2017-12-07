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
 * Date:           Generated on               Tue Jun 27 10:52:38 2017
 *                 Full Compile MD5 Checksum  de13a1e8011803b5a40ab14e4d71d071
 *                     (minus title and desc)
 *                 MD5 Checksum               b694fcab41780597392ed5a8f558ad3e
 *
 * lock_release:   r_1255
 * Compiled with:  RDB Utility                combo_header.pl
 *                 RDB.pm                     1570
 *                 unknown                    unknown
 *                 Perl Interpreter           5.014001
 *                 Operating System           linux
 *                 Script Source              home/pntruong/sbin/combo_header.pl
 *                 DVTSWVER                   LOCAL home/pntruong/sbin/combo_header.pl
 *
 *
********************************************************************************/

#ifndef BCHP_GIO_H__
#define BCHP_GIO_H__

/***************************************************************************
 *GIO - GPIO
 ***************************************************************************/
#define BCHP_GIO_ODEN_LO                         0x2040a400 /* [RW][32] GENERAL PURPOSE I/O OPEN DRAIN ENABLE FOR GPIO[31:0] */
#define BCHP_GIO_DATA_LO                         0x2040a404 /* [RW][32] GENERAL PURPOSE I/O DATA FOR GPIO[31:0] */
#define BCHP_GIO_IODIR_LO                        0x2040a408 /* [RW][32] GENERAL PURPOSE I/O DIRECTION FOR GPIO[31:0] */
#define BCHP_GIO_EC_LO                           0x2040a40c /* [RW][32] GENERAL PURPOSE I/O EDGE CONFIGURATION FOR GPIO[31:0] */
#define BCHP_GIO_EI_LO                           0x2040a410 /* [RW][32] GENERAL PURPOSE I/O EDGE INSENSITIVE FOR GPIO[31:0] */
#define BCHP_GIO_MASK_LO                         0x2040a414 /* [RW][32] GENERAL PURPOSE I/O INTERRUPT MASK FOR GPIO[31:0] */
#define BCHP_GIO_LEVEL_LO                        0x2040a418 /* [RW][32] GENERAL PURPOSE I/O INTERRUPT TYPE FOR GPIO[31:0] */
#define BCHP_GIO_STAT_LO                         0x2040a41c /* [RW][32] GENERAL PURPOSE I/O INTERRUPT STATUS FOR GPIO[31:0] */
#define BCHP_GIO_ODEN_HI                         0x2040a420 /* [RW][32] GENERAL PURPOSE I/O OPEN DRAIN ENABLE FOR GPIO[63:32] */
#define BCHP_GIO_DATA_HI                         0x2040a424 /* [RW][32] GENERAL PURPOSE I/O DATA FOR GPIO[63:32] */
#define BCHP_GIO_IODIR_HI                        0x2040a428 /* [RW][32] GENERAL PURPOSE I/O DIRECTION FOR GPIO[63:32] */
#define BCHP_GIO_EC_HI                           0x2040a42c /* [RW][32] GENERAL PURPOSE I/O EDGE CONFIGURATION FOR GPIO[63:32] */
#define BCHP_GIO_EI_HI                           0x2040a430 /* [RW][32] GENERAL PURPOSE I/O EDGE INSENSITIVE FOR GPIO[63:32] */
#define BCHP_GIO_MASK_HI                         0x2040a434 /* [RW][32] GENERAL PURPOSE I/O INTERRUPT MASK FOR GPIO[63:32] */
#define BCHP_GIO_LEVEL_HI                        0x2040a438 /* [RW][32] GENERAL PURPOSE I/O INTERRUPT TYPE FOR GPIO[63:32] */
#define BCHP_GIO_STAT_HI                         0x2040a43c /* [RW][32] GENERAL PURPOSE I/O INTERRUPT STATUS FOR GPIO[63:32] */
#define BCHP_GIO_ODEN_EXT_HI                     0x2040a440 /* [RW][32] GENERAL PURPOSE I/O OPEN DRAIN ENABLE FOR GPIO[82:64] */
#define BCHP_GIO_DATA_EXT_HI                     0x2040a444 /* [RW][32] GENERAL PURPOSE I/O DATA FOR GPIO[82:64] */
#define BCHP_GIO_IODIR_EXT_HI                    0x2040a448 /* [RW][32] GENERAL PURPOSE I/O DIRECTION FOR GPIO[82:64] */
#define BCHP_GIO_EC_EXT_HI                       0x2040a44c /* [RW][32] GENERAL PURPOSE I/O EDGE CONFIGURATION FOR GPIO[82:64] */
#define BCHP_GIO_EI_EXT_HI                       0x2040a450 /* [RW][32] GENERAL PURPOSE I/O EDGE INSENSITIVE FOR GPIO[82:64] */
#define BCHP_GIO_MASK_EXT_HI                     0x2040a454 /* [RW][32] GENERAL PURPOSE I/O INTERRUPT MASK FOR GPIO[82:64] */
#define BCHP_GIO_LEVEL_EXT_HI                    0x2040a458 /* [RW][32] GENERAL PURPOSE I/O INTERRUPT TYPE FOR GPIO[82:64] */
#define BCHP_GIO_STAT_EXT_HI                     0x2040a45c /* [RW][32] GENERAL PURPOSE I/O INTERRUPT STATUS FOR GPIO[82:64] */

/***************************************************************************
 *ODEN_LO - GENERAL PURPOSE I/O OPEN DRAIN ENABLE FOR GPIO[31:0]
 ***************************************************************************/
/* GIO :: ODEN_LO :: oden [31:00] */
#define BCHP_GIO_ODEN_LO_oden_MASK                                 0xffffffff
#define BCHP_GIO_ODEN_LO_oden_SHIFT                                0
#define BCHP_GIO_ODEN_LO_oden_DEFAULT                              0x00000000

/***************************************************************************
 *DATA_LO - GENERAL PURPOSE I/O DATA FOR GPIO[31:0]
 ***************************************************************************/
/* GIO :: DATA_LO :: data [31:00] */
#define BCHP_GIO_DATA_LO_data_MASK                                 0xffffffff
#define BCHP_GIO_DATA_LO_data_SHIFT                                0
#define BCHP_GIO_DATA_LO_data_DEFAULT                              0x00000000

/***************************************************************************
 *IODIR_LO - GENERAL PURPOSE I/O DIRECTION FOR GPIO[31:0]
 ***************************************************************************/
/* GIO :: IODIR_LO :: iodir [31:00] */
#define BCHP_GIO_IODIR_LO_iodir_MASK                               0xffffffff
#define BCHP_GIO_IODIR_LO_iodir_SHIFT                              0
#define BCHP_GIO_IODIR_LO_iodir_DEFAULT                            0xffffffff

/***************************************************************************
 *EC_LO - GENERAL PURPOSE I/O EDGE CONFIGURATION FOR GPIO[31:0]
 ***************************************************************************/
/* GIO :: EC_LO :: edge_config [31:00] */
#define BCHP_GIO_EC_LO_edge_config_MASK                            0xffffffff
#define BCHP_GIO_EC_LO_edge_config_SHIFT                           0
#define BCHP_GIO_EC_LO_edge_config_DEFAULT                         0x00000000

/***************************************************************************
 *EI_LO - GENERAL PURPOSE I/O EDGE INSENSITIVE FOR GPIO[31:0]
 ***************************************************************************/
/* GIO :: EI_LO :: edge_insensitive [31:00] */
#define BCHP_GIO_EI_LO_edge_insensitive_MASK                       0xffffffff
#define BCHP_GIO_EI_LO_edge_insensitive_SHIFT                      0
#define BCHP_GIO_EI_LO_edge_insensitive_DEFAULT                    0x00000000

/***************************************************************************
 *MASK_LO - GENERAL PURPOSE I/O INTERRUPT MASK FOR GPIO[31:0]
 ***************************************************************************/
/* GIO :: MASK_LO :: irq_mask [31:00] */
#define BCHP_GIO_MASK_LO_irq_mask_MASK                             0xffffffff
#define BCHP_GIO_MASK_LO_irq_mask_SHIFT                            0
#define BCHP_GIO_MASK_LO_irq_mask_DEFAULT                          0x00000000

/***************************************************************************
 *LEVEL_LO - GENERAL PURPOSE I/O INTERRUPT TYPE FOR GPIO[31:0]
 ***************************************************************************/
/* GIO :: LEVEL_LO :: level [31:00] */
#define BCHP_GIO_LEVEL_LO_level_MASK                               0xffffffff
#define BCHP_GIO_LEVEL_LO_level_SHIFT                              0
#define BCHP_GIO_LEVEL_LO_level_DEFAULT                            0x00000000

/***************************************************************************
 *STAT_LO - GENERAL PURPOSE I/O INTERRUPT STATUS FOR GPIO[31:0]
 ***************************************************************************/
/* GIO :: STAT_LO :: irq_status [31:00] */
#define BCHP_GIO_STAT_LO_irq_status_MASK                           0xffffffff
#define BCHP_GIO_STAT_LO_irq_status_SHIFT                          0
#define BCHP_GIO_STAT_LO_irq_status_DEFAULT                        0x00000000

/***************************************************************************
 *ODEN_HI - GENERAL PURPOSE I/O OPEN DRAIN ENABLE FOR GPIO[63:32]
 ***************************************************************************/
/* GIO :: ODEN_HI :: oden [31:00] */
#define BCHP_GIO_ODEN_HI_oden_MASK                                 0xffffffff
#define BCHP_GIO_ODEN_HI_oden_SHIFT                                0
#define BCHP_GIO_ODEN_HI_oden_DEFAULT                              0x00000000

/***************************************************************************
 *DATA_HI - GENERAL PURPOSE I/O DATA FOR GPIO[63:32]
 ***************************************************************************/
/* GIO :: DATA_HI :: data [31:00] */
#define BCHP_GIO_DATA_HI_data_MASK                                 0xffffffff
#define BCHP_GIO_DATA_HI_data_SHIFT                                0
#define BCHP_GIO_DATA_HI_data_DEFAULT                              0x00000000

/***************************************************************************
 *IODIR_HI - GENERAL PURPOSE I/O DIRECTION FOR GPIO[63:32]
 ***************************************************************************/
/* GIO :: IODIR_HI :: iodir [31:00] */
#define BCHP_GIO_IODIR_HI_iodir_MASK                               0xffffffff
#define BCHP_GIO_IODIR_HI_iodir_SHIFT                              0
#define BCHP_GIO_IODIR_HI_iodir_DEFAULT                            0xffffffff

/***************************************************************************
 *EC_HI - GENERAL PURPOSE I/O EDGE CONFIGURATION FOR GPIO[63:32]
 ***************************************************************************/
/* GIO :: EC_HI :: edge_config [31:00] */
#define BCHP_GIO_EC_HI_edge_config_MASK                            0xffffffff
#define BCHP_GIO_EC_HI_edge_config_SHIFT                           0
#define BCHP_GIO_EC_HI_edge_config_DEFAULT                         0x00000000

/***************************************************************************
 *EI_HI - GENERAL PURPOSE I/O EDGE INSENSITIVE FOR GPIO[63:32]
 ***************************************************************************/
/* GIO :: EI_HI :: edge_insensitive [31:00] */
#define BCHP_GIO_EI_HI_edge_insensitive_MASK                       0xffffffff
#define BCHP_GIO_EI_HI_edge_insensitive_SHIFT                      0
#define BCHP_GIO_EI_HI_edge_insensitive_DEFAULT                    0x00000000

/***************************************************************************
 *MASK_HI - GENERAL PURPOSE I/O INTERRUPT MASK FOR GPIO[63:32]
 ***************************************************************************/
/* GIO :: MASK_HI :: irq_mask [31:00] */
#define BCHP_GIO_MASK_HI_irq_mask_MASK                             0xffffffff
#define BCHP_GIO_MASK_HI_irq_mask_SHIFT                            0
#define BCHP_GIO_MASK_HI_irq_mask_DEFAULT                          0x00000000

/***************************************************************************
 *LEVEL_HI - GENERAL PURPOSE I/O INTERRUPT TYPE FOR GPIO[63:32]
 ***************************************************************************/
/* GIO :: LEVEL_HI :: level [31:00] */
#define BCHP_GIO_LEVEL_HI_level_MASK                               0xffffffff
#define BCHP_GIO_LEVEL_HI_level_SHIFT                              0
#define BCHP_GIO_LEVEL_HI_level_DEFAULT                            0x00000000

/***************************************************************************
 *STAT_HI - GENERAL PURPOSE I/O INTERRUPT STATUS FOR GPIO[63:32]
 ***************************************************************************/
/* GIO :: STAT_HI :: irq_status [31:00] */
#define BCHP_GIO_STAT_HI_irq_status_MASK                           0xffffffff
#define BCHP_GIO_STAT_HI_irq_status_SHIFT                          0
#define BCHP_GIO_STAT_HI_irq_status_DEFAULT                        0x00000000

/***************************************************************************
 *ODEN_EXT_HI - GENERAL PURPOSE I/O OPEN DRAIN ENABLE FOR GPIO[82:64]
 ***************************************************************************/
/* GIO :: ODEN_EXT_HI :: reserved0 [31:19] */
#define BCHP_GIO_ODEN_EXT_HI_reserved0_MASK                        0xfff80000
#define BCHP_GIO_ODEN_EXT_HI_reserved0_SHIFT                       19

/* GIO :: ODEN_EXT_HI :: oden [18:00] */
#define BCHP_GIO_ODEN_EXT_HI_oden_MASK                             0x0007ffff
#define BCHP_GIO_ODEN_EXT_HI_oden_SHIFT                            0
#define BCHP_GIO_ODEN_EXT_HI_oden_DEFAULT                          0x00000000

/***************************************************************************
 *DATA_EXT_HI - GENERAL PURPOSE I/O DATA FOR GPIO[82:64]
 ***************************************************************************/
/* GIO :: DATA_EXT_HI :: reserved0 [31:19] */
#define BCHP_GIO_DATA_EXT_HI_reserved0_MASK                        0xfff80000
#define BCHP_GIO_DATA_EXT_HI_reserved0_SHIFT                       19

/* GIO :: DATA_EXT_HI :: data [18:00] */
#define BCHP_GIO_DATA_EXT_HI_data_MASK                             0x0007ffff
#define BCHP_GIO_DATA_EXT_HI_data_SHIFT                            0
#define BCHP_GIO_DATA_EXT_HI_data_DEFAULT                          0x00000000

/***************************************************************************
 *IODIR_EXT_HI - GENERAL PURPOSE I/O DIRECTION FOR GPIO[82:64]
 ***************************************************************************/
/* GIO :: IODIR_EXT_HI :: reserved0 [31:19] */
#define BCHP_GIO_IODIR_EXT_HI_reserved0_MASK                       0xfff80000
#define BCHP_GIO_IODIR_EXT_HI_reserved0_SHIFT                      19

/* GIO :: IODIR_EXT_HI :: iodir [18:00] */
#define BCHP_GIO_IODIR_EXT_HI_iodir_MASK                           0x0007ffff
#define BCHP_GIO_IODIR_EXT_HI_iodir_SHIFT                          0
#define BCHP_GIO_IODIR_EXT_HI_iodir_DEFAULT                        0x0007ffff

/***************************************************************************
 *EC_EXT_HI - GENERAL PURPOSE I/O EDGE CONFIGURATION FOR GPIO[82:64]
 ***************************************************************************/
/* GIO :: EC_EXT_HI :: reserved0 [31:19] */
#define BCHP_GIO_EC_EXT_HI_reserved0_MASK                          0xfff80000
#define BCHP_GIO_EC_EXT_HI_reserved0_SHIFT                         19

/* GIO :: EC_EXT_HI :: edge_config [18:00] */
#define BCHP_GIO_EC_EXT_HI_edge_config_MASK                        0x0007ffff
#define BCHP_GIO_EC_EXT_HI_edge_config_SHIFT                       0
#define BCHP_GIO_EC_EXT_HI_edge_config_DEFAULT                     0x00000000

/***************************************************************************
 *EI_EXT_HI - GENERAL PURPOSE I/O EDGE INSENSITIVE FOR GPIO[82:64]
 ***************************************************************************/
/* GIO :: EI_EXT_HI :: reserved0 [31:19] */
#define BCHP_GIO_EI_EXT_HI_reserved0_MASK                          0xfff80000
#define BCHP_GIO_EI_EXT_HI_reserved0_SHIFT                         19

/* GIO :: EI_EXT_HI :: edge_insensitive [18:00] */
#define BCHP_GIO_EI_EXT_HI_edge_insensitive_MASK                   0x0007ffff
#define BCHP_GIO_EI_EXT_HI_edge_insensitive_SHIFT                  0
#define BCHP_GIO_EI_EXT_HI_edge_insensitive_DEFAULT                0x00000000

/***************************************************************************
 *MASK_EXT_HI - GENERAL PURPOSE I/O INTERRUPT MASK FOR GPIO[82:64]
 ***************************************************************************/
/* GIO :: MASK_EXT_HI :: reserved0 [31:19] */
#define BCHP_GIO_MASK_EXT_HI_reserved0_MASK                        0xfff80000
#define BCHP_GIO_MASK_EXT_HI_reserved0_SHIFT                       19

/* GIO :: MASK_EXT_HI :: irq_mask [18:00] */
#define BCHP_GIO_MASK_EXT_HI_irq_mask_MASK                         0x0007ffff
#define BCHP_GIO_MASK_EXT_HI_irq_mask_SHIFT                        0
#define BCHP_GIO_MASK_EXT_HI_irq_mask_DEFAULT                      0x00000000

/***************************************************************************
 *LEVEL_EXT_HI - GENERAL PURPOSE I/O INTERRUPT TYPE FOR GPIO[82:64]
 ***************************************************************************/
/* GIO :: LEVEL_EXT_HI :: reserved0 [31:19] */
#define BCHP_GIO_LEVEL_EXT_HI_reserved0_MASK                       0xfff80000
#define BCHP_GIO_LEVEL_EXT_HI_reserved0_SHIFT                      19

/* GIO :: LEVEL_EXT_HI :: level [18:00] */
#define BCHP_GIO_LEVEL_EXT_HI_level_MASK                           0x0007ffff
#define BCHP_GIO_LEVEL_EXT_HI_level_SHIFT                          0
#define BCHP_GIO_LEVEL_EXT_HI_level_DEFAULT                        0x00000000

/***************************************************************************
 *STAT_EXT_HI - GENERAL PURPOSE I/O INTERRUPT STATUS FOR GPIO[82:64]
 ***************************************************************************/
/* GIO :: STAT_EXT_HI :: reserved0 [31:19] */
#define BCHP_GIO_STAT_EXT_HI_reserved0_MASK                        0xfff80000
#define BCHP_GIO_STAT_EXT_HI_reserved0_SHIFT                       19

/* GIO :: STAT_EXT_HI :: irq_status [18:00] */
#define BCHP_GIO_STAT_EXT_HI_irq_status_MASK                       0x0007ffff
#define BCHP_GIO_STAT_EXT_HI_irq_status_SHIFT                      0
#define BCHP_GIO_STAT_EXT_HI_irq_status_DEFAULT                    0x00000000

#endif /* #ifndef BCHP_GIO_H__ */

/* End of File */

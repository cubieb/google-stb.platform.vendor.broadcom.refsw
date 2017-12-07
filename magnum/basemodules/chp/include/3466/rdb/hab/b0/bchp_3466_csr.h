/******************************************************************************
 * Copyright (C) 2017 Broadcom. The term "Broadcom" refers to Broadcom Limited and/or its subsidiaries.
 *
 * This program is the proprietary software of Broadcom and/or its licensors,
 * and may only be used, duplicated, modified or distributed pursuant to the terms and
 * conditions of a separate, written license agreement executed between you and Broadcom
 * (an "Authorized License").  Except as set forth in an Authorized License, Broadcom grants
 * no license (express or implied), right to use, or waiver of any kind with respect to the
 * Software, and Broadcom expressly reserves all rights in and to the Software and all
 * intellectual property rights therein.  IF YOU HAVE NO AUTHORIZED LICENSE, THEN YOU
 * HAVE NO RIGHT TO USE THIS SOFTWARE IN ANY WAY, AND SHOULD IMMEDIATELY
 * NOTIFY BROADCOM AND DISCONTINUE ALL USE OF THE SOFTWARE.
 *
 * Except as expressly set forth in the Authorized License,
 *
 * 1.     This program, including its structure, sequence and organization, constitutes the valuable trade
 * secrets of Broadcom, and you shall use all reasonable efforts to protect the confidentiality thereof,
 * and to use this information only in connection with your use of Broadcom integrated circuit products.
 *
 * 2.     TO THE MAXIMUM EXTENT PERMITTED BY LAW, THE SOFTWARE IS PROVIDED "AS IS"
 * AND WITH ALL FAULTS AND BROADCOM MAKES NO PROMISES, REPRESENTATIONS OR
 * WARRANTIES, EITHER EXPRESS, IMPLIED, STATUTORY, OR OTHERWISE, WITH RESPECT TO
 * THE SOFTWARE.  BROADCOM SPECIFICALLY DISCLAIMS ANY AND ALL IMPLIED WARRANTIES
 * OF TITLE, MERCHANTABILITY, NONINFRINGEMENT, FITNESS FOR A PARTICULAR PURPOSE,
 * LACK OF VIRUSES, ACCURACY OR COMPLETENESS, QUIET ENJOYMENT, QUIET POSSESSION
 * OR CORRESPONDENCE TO DESCRIPTION. YOU ASSUME THE ENTIRE RISK ARISING OUT OF
 * USE OR PERFORMANCE OF THE SOFTWARE.
 *
 * 3.     TO THE MAXIMUM EXTENT PERMITTED BY LAW, IN NO EVENT SHALL BROADCOM OR ITS
 * LICENSORS BE LIABLE FOR (i) CONSEQUENTIAL, INCIDENTAL, SPECIAL, INDIRECT, OR
 * EXEMPLARY DAMAGES WHATSOEVER ARISING OUT OF OR IN ANY WAY RELATING TO YOUR
 * USE OF OR INABILITY TO USE THE SOFTWARE EVEN IF BROADCOM HAS BEEN ADVISED OF
 * THE POSSIBILITY OF SUCH DAMAGES; OR (ii) ANY AMOUNT IN EXCESS OF THE AMOUNT
 * ACTUALLY PAID FOR THE SOFTWARE ITSELF OR U.S. $1, WHICHEVER IS GREATER. THESE
 * LIMITATIONS SHALL APPLY NOTWITHSTANDING ANY FAILURE OF ESSENTIAL PURPOSE OF
 * ANY LIMITED REMEDY.
 *
 * Module Description:
 *
 *****************************************************************************/
/*
 * Module Description:
 *                     DO NOT EDIT THIS FILE DIRECTLY
 *
 * This module was generated magically with RDB from a source description
 * file. You must edit the source file for changes to be made to this file.
 *
 *
 * Date:           Generated on               Wed Nov 11 20:00:00 2015
 *                 Full Compile MD5 Checksum  b74202058cf9cd0223995cede36bc98a
 *                     (minus title and desc)
 *                 MD5 Checksum               188ac691b54e29dbfb16eefad4c82f1d
 *
 * Compiled with:  RDB Utility                combo_header.pl
 *                 RDB.pm                     473
 *                 unknown                    unknown
 *                 Perl Interpreter           5.008008
 *                 Operating System           linux
 *                 Script Source              /tools/dvtsw/current/Linux/combo_header.pl
 *                 DVTSWVER                   current
 *
 *
 ***************************************************************************/

#ifndef BCHP_CSR_H__
#define BCHP_CSR_H__

/***************************************************************************
 *CSR - BBSI Control & Status Registers
 ***************************************************************************/
#define BCHP_CSR_SER_PROT_REV                    0x00000000 /* [RO] Serial protocol revision ID */
#define BCHP_CSR_CHIP_FAM0                       0x00000001 /* [RO] Bits [15:08] of the 32-bit chip family ID */
#define BCHP_CSR_CHIP_FAM1                       0x00000002 /* [RO] Bits [07:00] of the 32-bit chip family ID */
#define BCHP_CSR_CHIP_FAM2                       0x00000003 /* [RO] Bits [15:08] of the 32-bit chip family ID */
#define BCHP_CSR_CHIP_FAM3                       0x00000004 /* [RO] Bits [07:00] of the 32-bit chip family ID */
#define BCHP_CSR_PROGRAM                         0x00000005 /* [RW] Program status register */
#define BCHP_CSR_STATUS                          0x00000006 /* [RO] Status register of the serial interface */
#define BCHP_CSR_CONFIG                          0x00000007 /* [RW] Configuration register of the serial interface */
#define BCHP_CSR_RBUS_ADDR0                      0x00000008 /* [RW] Bits [31:24] of the 32-bit RBUS address */
#define BCHP_CSR_RBUS_ADDR1                      0x00000009 /* [RW] Bits [23:16] of the 32-bit RBUS address */
#define BCHP_CSR_RBUS_ADDR2                      0x0000000a /* [RW] Bits [15:08] of the 32-bit RBUS address */
#define BCHP_CSR_RBUS_ADDR3                      0x0000000b /* [RW] Bits [07:00] of the 32-bit RBUS address */
#define BCHP_CSR_RBUS_DATA0                      0x0000000c /* [RW] Bits [31:24] of the 32-bit RBUS data */
#define BCHP_CSR_RBUS_DATA1                      0x0000000d /* [RW] Bits [23:16] of the 32-bit RBUS data */
#define BCHP_CSR_RBUS_DATA2                      0x0000000e /* [RW] Bits [15:08] of the 32-bit RBUS data */
#define BCHP_CSR_RBUS_DATA3                      0x0000000f /* [RW] Bits [07:00] of the 32-bit RBUS data */
#define BCHP_CSR_CHIP_PROD0                      0x00000010 /* [RO] Bits [31:24] of the 32-bit chip product ID */
#define BCHP_CSR_CHIP_PROD1                      0x00000011 /* [RO] Bits [23:16] of the 32-bit chip product ID */
#define BCHP_CSR_CHIP_PROD2                      0x00000012 /* [RO] Bits [15:08] of the 32-bit chip product ID */
#define BCHP_CSR_CHIP_PROD3                      0x00000013 /* [RO] Bits [07:00] of the 32-bit chip product ID internal revision */

/***************************************************************************
 *SER_PROT_REV - Serial protocol revision ID
 ***************************************************************************/
/* CSR :: SER_PROT_REV :: SER_PROT_REV [07:00] */
#define BCHP_CSR_SER_PROT_REV_SER_PROT_REV_MASK                    0xff
#define BCHP_CSR_SER_PROT_REV_SER_PROT_REV_SHIFT                   0
#define BCHP_CSR_SER_PROT_REV_SER_PROT_REV_DEFAULT                 0x08

/***************************************************************************
 *CHIP_FAM0 - Bits [15:08] of the 32-bit chip family ID
 ***************************************************************************/
/* CSR :: CHIP_FAM0 :: CHIP_FAMILY [07:00] */
#define BCHP_CSR_CHIP_FAM0_CHIP_FAMILY_MASK                        0xff
#define BCHP_CSR_CHIP_FAM0_CHIP_FAMILY_SHIFT                       0
#define BCHP_CSR_CHIP_FAM0_CHIP_FAMILY_DEFAULT                     0x31

/***************************************************************************
 *CHIP_FAM1 - Bits [07:00] of the 32-bit chip family ID
 ***************************************************************************/
/* CSR :: CHIP_FAM1 :: CHIP_FAMILY [07:00] */
#define BCHP_CSR_CHIP_FAM1_CHIP_FAMILY_MASK                        0xff
#define BCHP_CSR_CHIP_FAM1_CHIP_FAMILY_SHIFT                       0
#define BCHP_CSR_CHIP_FAM1_CHIP_FAMILY_DEFAULT                     0x58

/***************************************************************************
 *CHIP_FAM2 - Bits [15:08] of the 32-bit chip family ID
 ***************************************************************************/
/* CSR :: CHIP_FAM2 :: CHIP_REV [07:00] */
#define BCHP_CSR_CHIP_FAM2_CHIP_REV_MASK                           0xff
#define BCHP_CSR_CHIP_FAM2_CHIP_REV_SHIFT                          0
#define BCHP_CSR_CHIP_FAM2_CHIP_REV_DEFAULT                        0x00

/***************************************************************************
 *CHIP_FAM3 - Bits [07:00] of the 32-bit chip family ID
 ***************************************************************************/
/* CSR :: CHIP_FAM3 :: CHIP_REV [07:00] */
#define BCHP_CSR_CHIP_FAM3_CHIP_REV_MASK                           0xff
#define BCHP_CSR_CHIP_FAM3_CHIP_REV_SHIFT                          0
#define BCHP_CSR_CHIP_FAM3_CHIP_REV_DEFAULT                        0x00

/***************************************************************************
 *PROGRAM - Program status register
 ***************************************************************************/
/* CSR :: PROGRAM :: reserved0 [07:01] */
#define BCHP_CSR_PROGRAM_reserved0_MASK                            0xfe
#define BCHP_CSR_PROGRAM_reserved0_SHIFT                           1

/* CSR :: PROGRAM :: LOADED [00:00] */
#define BCHP_CSR_PROGRAM_LOADED_MASK                               0x01
#define BCHP_CSR_PROGRAM_LOADED_SHIFT                              0
#define BCHP_CSR_PROGRAM_LOADED_DEFAULT                            0x00

/***************************************************************************
 *STATUS - Status register of the serial interface
 ***************************************************************************/
/* CSR :: STATUS :: reserved0 [07:07] */
#define BCHP_CSR_STATUS_reserved0_MASK                             0x80
#define BCHP_CSR_STATUS_reserved0_SHIFT                            7

/* CSR :: STATUS :: CPU_RUNNING [06:06] */
#define BCHP_CSR_STATUS_CPU_RUNNING_MASK                           0x40
#define BCHP_CSR_STATUS_CPU_RUNNING_SHIFT                          6
#define BCHP_CSR_STATUS_CPU_RUNNING_DEFAULT                        0x00

/* CSR :: STATUS :: HAB_REQ [05:05] */
#define BCHP_CSR_STATUS_HAB_REQ_MASK                               0x20
#define BCHP_CSR_STATUS_HAB_REQ_SHIFT                              5
#define BCHP_CSR_STATUS_HAB_REQ_DEFAULT                            0x00

/* CSR :: STATUS :: BUSY [04:04] */
#define BCHP_CSR_STATUS_BUSY_MASK                                  0x10
#define BCHP_CSR_STATUS_BUSY_SHIFT                                 4
#define BCHP_CSR_STATUS_BUSY_DEFAULT                               0x00

/* CSR :: STATUS :: RBUS_UNEXP_TX [03:03] */
#define BCHP_CSR_STATUS_RBUS_UNEXP_TX_MASK                         0x08
#define BCHP_CSR_STATUS_RBUS_UNEXP_TX_SHIFT                        3
#define BCHP_CSR_STATUS_RBUS_UNEXP_TX_DEFAULT                      0x00

/* CSR :: STATUS :: RBUS_TIMEOUT [02:02] */
#define BCHP_CSR_STATUS_RBUS_TIMEOUT_MASK                          0x04
#define BCHP_CSR_STATUS_RBUS_TIMEOUT_SHIFT                         2
#define BCHP_CSR_STATUS_RBUS_TIMEOUT_DEFAULT                       0x00

/* CSR :: STATUS :: RBUS_ERR_ACK [01:01] */
#define BCHP_CSR_STATUS_RBUS_ERR_ACK_MASK                          0x02
#define BCHP_CSR_STATUS_RBUS_ERR_ACK_SHIFT                         1
#define BCHP_CSR_STATUS_RBUS_ERR_ACK_DEFAULT                       0x00

/* CSR :: STATUS :: ERROR [00:00] */
#define BCHP_CSR_STATUS_ERROR_MASK                                 0x01
#define BCHP_CSR_STATUS_ERROR_SHIFT                                0
#define BCHP_CSR_STATUS_ERROR_DEFAULT                              0x00

/***************************************************************************
 *CONFIG - Configuration register of the serial interface
 ***************************************************************************/
/* CSR :: CONFIG :: reserved0 [07:05] */
#define BCHP_CSR_CONFIG_reserved0_MASK                             0xe0
#define BCHP_CSR_CONFIG_reserved0_SHIFT                            5

/* CSR :: CONFIG :: TRANSFER_MODE [04:03] */
#define BCHP_CSR_CONFIG_TRANSFER_MODE_MASK                         0x18
#define BCHP_CSR_CONFIG_TRANSFER_MODE_SHIFT                        3
#define BCHP_CSR_CONFIG_TRANSFER_MODE_DEFAULT                      0x00

/* CSR :: CONFIG :: NO_RBUS_ADDR_INC [02:02] */
#define BCHP_CSR_CONFIG_NO_RBUS_ADDR_INC_MASK                      0x04
#define BCHP_CSR_CONFIG_NO_RBUS_ADDR_INC_SHIFT                     2
#define BCHP_CSR_CONFIG_NO_RBUS_ADDR_INC_DEFAULT                   0x00

/* CSR :: CONFIG :: SPECULATIVE_READ_EN [01:01] */
#define BCHP_CSR_CONFIG_SPECULATIVE_READ_EN_MASK                   0x02
#define BCHP_CSR_CONFIG_SPECULATIVE_READ_EN_SHIFT                  1
#define BCHP_CSR_CONFIG_SPECULATIVE_READ_EN_DEFAULT                0x00

/* CSR :: CONFIG :: READ_RBUS [00:00] */
#define BCHP_CSR_CONFIG_READ_RBUS_MASK                             0x01
#define BCHP_CSR_CONFIG_READ_RBUS_SHIFT                            0
#define BCHP_CSR_CONFIG_READ_RBUS_DEFAULT                          0x00

/***************************************************************************
 *RBUS_ADDR0 - Bits [31:24] of the 32-bit RBUS address
 ***************************************************************************/
/* CSR :: RBUS_ADDR0 :: RBUS_ADDR0 [07:00] */
#define BCHP_CSR_RBUS_ADDR0_RBUS_ADDR0_MASK                        0xff
#define BCHP_CSR_RBUS_ADDR0_RBUS_ADDR0_SHIFT                       0
#define BCHP_CSR_RBUS_ADDR0_RBUS_ADDR0_DEFAULT                     0x00

/***************************************************************************
 *RBUS_ADDR1 - Bits [23:16] of the 32-bit RBUS address
 ***************************************************************************/
/* CSR :: RBUS_ADDR1 :: RBUS_ADDR1 [07:00] */
#define BCHP_CSR_RBUS_ADDR1_RBUS_ADDR1_MASK                        0xff
#define BCHP_CSR_RBUS_ADDR1_RBUS_ADDR1_SHIFT                       0
#define BCHP_CSR_RBUS_ADDR1_RBUS_ADDR1_DEFAULT                     0x00

/***************************************************************************
 *RBUS_ADDR2 - Bits [15:08] of the 32-bit RBUS address
 ***************************************************************************/
/* CSR :: RBUS_ADDR2 :: RBUS_ADDR2 [07:00] */
#define BCHP_CSR_RBUS_ADDR2_RBUS_ADDR2_MASK                        0xff
#define BCHP_CSR_RBUS_ADDR2_RBUS_ADDR2_SHIFT                       0
#define BCHP_CSR_RBUS_ADDR2_RBUS_ADDR2_DEFAULT                     0x00

/***************************************************************************
 *RBUS_ADDR3 - Bits [07:00] of the 32-bit RBUS address
 ***************************************************************************/
/* CSR :: RBUS_ADDR3 :: RBUS_ADDR3 [07:02] */
#define BCHP_CSR_RBUS_ADDR3_RBUS_ADDR3_MASK                        0xfc
#define BCHP_CSR_RBUS_ADDR3_RBUS_ADDR3_SHIFT                       2
#define BCHP_CSR_RBUS_ADDR3_RBUS_ADDR3_DEFAULT                     0x00

/* CSR :: RBUS_ADDR3 :: RBUS_ADDR3_LSB [01:00] */
#define BCHP_CSR_RBUS_ADDR3_RBUS_ADDR3_LSB_MASK                    0x03
#define BCHP_CSR_RBUS_ADDR3_RBUS_ADDR3_LSB_SHIFT                   0
#define BCHP_CSR_RBUS_ADDR3_RBUS_ADDR3_LSB_DEFAULT                 0x00

/***************************************************************************
 *RBUS_DATA0 - Bits [31:24] of the 32-bit RBUS data
 ***************************************************************************/
/* CSR :: RBUS_DATA0 :: RBUS_DATA0 [07:00] */
#define BCHP_CSR_RBUS_DATA0_RBUS_DATA0_MASK                        0xff
#define BCHP_CSR_RBUS_DATA0_RBUS_DATA0_SHIFT                       0
#define BCHP_CSR_RBUS_DATA0_RBUS_DATA0_DEFAULT                     0x00

/***************************************************************************
 *RBUS_DATA1 - Bits [23:16] of the 32-bit RBUS data
 ***************************************************************************/
/* CSR :: RBUS_DATA1 :: RBUS_DATA1 [07:00] */
#define BCHP_CSR_RBUS_DATA1_RBUS_DATA1_MASK                        0xff
#define BCHP_CSR_RBUS_DATA1_RBUS_DATA1_SHIFT                       0
#define BCHP_CSR_RBUS_DATA1_RBUS_DATA1_DEFAULT                     0x00

/***************************************************************************
 *RBUS_DATA2 - Bits [15:08] of the 32-bit RBUS data
 ***************************************************************************/
/* CSR :: RBUS_DATA2 :: RBUS_DATA2 [07:00] */
#define BCHP_CSR_RBUS_DATA2_RBUS_DATA2_MASK                        0xff
#define BCHP_CSR_RBUS_DATA2_RBUS_DATA2_SHIFT                       0
#define BCHP_CSR_RBUS_DATA2_RBUS_DATA2_DEFAULT                     0x00

/***************************************************************************
 *RBUS_DATA3 - Bits [07:00] of the 32-bit RBUS data
 ***************************************************************************/
/* CSR :: RBUS_DATA3 :: RBUS_DATA3 [07:00] */
#define BCHP_CSR_RBUS_DATA3_RBUS_DATA3_MASK                        0xff
#define BCHP_CSR_RBUS_DATA3_RBUS_DATA3_SHIFT                       0
#define BCHP_CSR_RBUS_DATA3_RBUS_DATA3_DEFAULT                     0x00

/***************************************************************************
 *CHIP_PROD0 - Bits [31:24] of the 32-bit chip product ID
 ***************************************************************************/
/* CSR :: CHIP_PROD0 :: CHIP_PRODUCT [07:00] */
#define BCHP_CSR_CHIP_PROD0_CHIP_PRODUCT_MASK                      0xff
#define BCHP_CSR_CHIP_PROD0_CHIP_PRODUCT_SHIFT                     0
#define BCHP_CSR_CHIP_PROD0_CHIP_PRODUCT_DEFAULT                   0x00

/***************************************************************************
 *CHIP_PROD1 - Bits [23:16] of the 32-bit chip product ID
 ***************************************************************************/
/* CSR :: CHIP_PROD1 :: CHIP_PRODUCT [07:00] */
#define BCHP_CSR_CHIP_PROD1_CHIP_PRODUCT_MASK                      0xff
#define BCHP_CSR_CHIP_PROD1_CHIP_PRODUCT_SHIFT                     0
#define BCHP_CSR_CHIP_PROD1_CHIP_PRODUCT_DEFAULT                   0x31

/***************************************************************************
 *CHIP_PROD2 - Bits [15:08] of the 32-bit chip product ID
 ***************************************************************************/
/* CSR :: CHIP_PROD2 :: CHIP_PRODUCT [07:00] */
#define BCHP_CSR_CHIP_PROD2_CHIP_PRODUCT_MASK                      0xff
#define BCHP_CSR_CHIP_PROD2_CHIP_PRODUCT_SHIFT                     0
#define BCHP_CSR_CHIP_PROD2_CHIP_PRODUCT_DEFAULT                   0x58

/***************************************************************************
 *CHIP_PROD3 - Bits [07:00] of the 32-bit chip product ID internal revision
 ***************************************************************************/
/* CSR :: CHIP_PROD3 :: CHIP_PRODUCT [07:00] */
#define BCHP_CSR_CHIP_PROD3_CHIP_PRODUCT_MASK                      0xff
#define BCHP_CSR_CHIP_PROD3_CHIP_PRODUCT_SHIFT                     0
#define BCHP_CSR_CHIP_PROD3_CHIP_PRODUCT_DEFAULT                   0x00

#endif /* #ifndef BCHP_CSR_H__ */

/* End of File */

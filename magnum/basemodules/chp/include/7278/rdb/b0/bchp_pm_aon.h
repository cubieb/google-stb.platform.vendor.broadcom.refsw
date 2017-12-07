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
 * Date:           Generated on               Tue May 30 14:59:07 2017
 *                 Full Compile MD5 Checksum  7b93739e9789c2097ae90e6947c515c2
 *                     (minus title and desc)
 *                 MD5 Checksum               3b7d1fd87398453917c32bfd8b23852c
 *
 * lock_release:   n/a
 * Compiled with:  RDB Utility                combo_header.pl
 *                 RDB.pm                     1481
 *                 unknown                    unknown
 *                 Perl Interpreter           5.014001
 *                 Operating System           linux
 *                 Script Source              home/pntruong/sbin/combo_header.pl
 *                 DVTSWVER                   LOCAL home/pntruong/sbin/combo_header.pl
 *
 *
********************************************************************************/

#ifndef BCHP_PM_AON_H__
#define BCHP_PM_AON_H__

/***************************************************************************
 *PM_AON - Peripheral Module Configuration
 ***************************************************************************/
#define BCHP_PM_AON_CONFIG                       0x0041a080 /* [RW][32] PERIPHERAL MODULE CONFIGURATION REGISTER */
#define BCHP_PM_AON_CLK_CTRL                     0x0041a084 /* [RW][32] UPG Clock control register */
#define BCHP_PM_AON_RST_CTRL                     0x0041a088 /* [RW][32] UPG reset control register */

/***************************************************************************
 *CONFIG - PERIPHERAL MODULE CONFIGURATION REGISTER
 ***************************************************************************/
/* PM_AON :: CONFIG :: reserved_for_eco0 [31:10] */
#define BCHP_PM_AON_CONFIG_reserved_for_eco0_MASK                  0xfffffc00
#define BCHP_PM_AON_CONFIG_reserved_for_eco0_SHIFT                 10
#define BCHP_PM_AON_CONFIG_reserved_for_eco0_DEFAULT               0x00000000

/* PM_AON :: CONFIG :: bicap1_sel [09:08] */
#define BCHP_PM_AON_CONFIG_bicap1_sel_MASK                         0x00000300
#define BCHP_PM_AON_CONFIG_bicap1_sel_SHIFT                        8
#define BCHP_PM_AON_CONFIG_bicap1_sel_DEFAULT                      0x00000000
#define BCHP_PM_AON_CONFIG_bicap1_sel_IR_IN0                       0
#define BCHP_PM_AON_CONFIG_bicap1_sel_IR_IN1                       1
#define BCHP_PM_AON_CONFIG_bicap1_sel_NONE                         2

/* PM_AON :: CONFIG :: bicap0_sel [07:06] */
#define BCHP_PM_AON_CONFIG_bicap0_sel_MASK                         0x000000c0
#define BCHP_PM_AON_CONFIG_bicap0_sel_SHIFT                        6
#define BCHP_PM_AON_CONFIG_bicap0_sel_DEFAULT                      0x00000000
#define BCHP_PM_AON_CONFIG_bicap0_sel_IR_IN0                       0
#define BCHP_PM_AON_CONFIG_bicap0_sel_IR_IN1                       1
#define BCHP_PM_AON_CONFIG_bicap0_sel_NONE                         2

/* PM_AON :: CONFIG :: irr2_in [05:04] */
#define BCHP_PM_AON_CONFIG_irr2_in_MASK                            0x00000030
#define BCHP_PM_AON_CONFIG_irr2_in_SHIFT                           4
#define BCHP_PM_AON_CONFIG_irr2_in_DEFAULT                         0x00000000
#define BCHP_PM_AON_CONFIG_irr2_in_NONE                            0
#define BCHP_PM_AON_CONFIG_irr2_in_AON_GPIO_12                     1
#define BCHP_PM_AON_CONFIG_irr2_in_IR_IN0                          2
#define BCHP_PM_AON_CONFIG_irr2_in_IR_IN1                          3

/* PM_AON :: CONFIG :: irr1_in [03:02] */
#define BCHP_PM_AON_CONFIG_irr1_in_MASK                            0x0000000c
#define BCHP_PM_AON_CONFIG_irr1_in_SHIFT                           2
#define BCHP_PM_AON_CONFIG_irr1_in_DEFAULT                         0x00000000
#define BCHP_PM_AON_CONFIG_irr1_in_IR_IN1                          0
#define BCHP_PM_AON_CONFIG_irr1_in_NONE                            1
#define BCHP_PM_AON_CONFIG_irr1_in_AON_GPIO_12                     2
#define BCHP_PM_AON_CONFIG_irr1_in_IR_IN0                          3

/* PM_AON :: CONFIG :: irr0_in [01:00] */
#define BCHP_PM_AON_CONFIG_irr0_in_MASK                            0x00000003
#define BCHP_PM_AON_CONFIG_irr0_in_SHIFT                           0
#define BCHP_PM_AON_CONFIG_irr0_in_DEFAULT                         0x00000000
#define BCHP_PM_AON_CONFIG_irr0_in_IR_IN0                          0
#define BCHP_PM_AON_CONFIG_irr0_in_IR_IN1                          1
#define BCHP_PM_AON_CONFIG_irr0_in_NONE                            2
#define BCHP_PM_AON_CONFIG_irr0_in_AON_GPIO_12                     3

/***************************************************************************
 *CLK_CTRL - UPG Clock control register
 ***************************************************************************/
/* PM_AON :: CLK_CTRL :: reserved0 [31:10] */
#define BCHP_PM_AON_CLK_CTRL_reserved0_MASK                        0xfffffc00
#define BCHP_PM_AON_CLK_CTRL_reserved0_SHIFT                       10

/* PM_AON :: CLK_CTRL :: bicap [09:09] */
#define BCHP_PM_AON_CLK_CTRL_bicap_MASK                            0x00000200
#define BCHP_PM_AON_CLK_CTRL_bicap_SHIFT                           9
#define BCHP_PM_AON_CLK_CTRL_bicap_DEFAULT                         0x00000001

/* PM_AON :: CLK_CTRL :: gpio [08:08] */
#define BCHP_PM_AON_CLK_CTRL_gpio_MASK                             0x00000100
#define BCHP_PM_AON_CLK_CTRL_gpio_SHIFT                            8
#define BCHP_PM_AON_CLK_CTRL_gpio_DEFAULT                          0x00000001

/* PM_AON :: CLK_CTRL :: icap [07:07] */
#define BCHP_PM_AON_CLK_CTRL_icap_MASK                             0x00000080
#define BCHP_PM_AON_CLK_CTRL_icap_SHIFT                            7
#define BCHP_PM_AON_CLK_CTRL_icap_DEFAULT                          0x00000001

/* PM_AON :: CLK_CTRL :: mspi [06:06] */
#define BCHP_PM_AON_CLK_CTRL_mspi_MASK                             0x00000040
#define BCHP_PM_AON_CLK_CTRL_mspi_SHIFT                            6
#define BCHP_PM_AON_CLK_CTRL_mspi_DEFAULT                          0x00000001

/* PM_AON :: CLK_CTRL :: ldk [05:05] */
#define BCHP_PM_AON_CLK_CTRL_ldk_MASK                              0x00000020
#define BCHP_PM_AON_CLK_CTRL_ldk_SHIFT                             5
#define BCHP_PM_AON_CLK_CTRL_ldk_DEFAULT                           0x00000001

/* PM_AON :: CLK_CTRL :: kbd3 [04:04] */
#define BCHP_PM_AON_CLK_CTRL_kbd3_MASK                             0x00000010
#define BCHP_PM_AON_CLK_CTRL_kbd3_SHIFT                            4
#define BCHP_PM_AON_CLK_CTRL_kbd3_DEFAULT                          0x00000001

/* PM_AON :: CLK_CTRL :: kbd2 [03:03] */
#define BCHP_PM_AON_CLK_CTRL_kbd2_MASK                             0x00000008
#define BCHP_PM_AON_CLK_CTRL_kbd2_SHIFT                            3
#define BCHP_PM_AON_CLK_CTRL_kbd2_DEFAULT                          0x00000001

/* PM_AON :: CLK_CTRL :: kbd1 [02:02] */
#define BCHP_PM_AON_CLK_CTRL_kbd1_MASK                             0x00000004
#define BCHP_PM_AON_CLK_CTRL_kbd1_SHIFT                            2
#define BCHP_PM_AON_CLK_CTRL_kbd1_DEFAULT                          0x00000001

/* PM_AON :: CLK_CTRL :: bscc [01:01] */
#define BCHP_PM_AON_CLK_CTRL_bscc_MASK                             0x00000002
#define BCHP_PM_AON_CLK_CTRL_bscc_SHIFT                            1
#define BCHP_PM_AON_CLK_CTRL_bscc_DEFAULT                          0x00000001

/* PM_AON :: CLK_CTRL :: bscb [00:00] */
#define BCHP_PM_AON_CLK_CTRL_bscb_MASK                             0x00000001
#define BCHP_PM_AON_CLK_CTRL_bscb_SHIFT                            0
#define BCHP_PM_AON_CLK_CTRL_bscb_DEFAULT                          0x00000001

/***************************************************************************
 *RST_CTRL - UPG reset control register
 ***************************************************************************/
/* PM_AON :: RST_CTRL :: reserved0 [31:10] */
#define BCHP_PM_AON_RST_CTRL_reserved0_MASK                        0xfffffc00
#define BCHP_PM_AON_RST_CTRL_reserved0_SHIFT                       10

/* PM_AON :: RST_CTRL :: bicap [09:09] */
#define BCHP_PM_AON_RST_CTRL_bicap_MASK                            0x00000200
#define BCHP_PM_AON_RST_CTRL_bicap_SHIFT                           9
#define BCHP_PM_AON_RST_CTRL_bicap_DEFAULT                         0x00000000

/* PM_AON :: RST_CTRL :: gpio [08:08] */
#define BCHP_PM_AON_RST_CTRL_gpio_MASK                             0x00000100
#define BCHP_PM_AON_RST_CTRL_gpio_SHIFT                            8
#define BCHP_PM_AON_RST_CTRL_gpio_DEFAULT                          0x00000000

/* PM_AON :: RST_CTRL :: icap [07:07] */
#define BCHP_PM_AON_RST_CTRL_icap_MASK                             0x00000080
#define BCHP_PM_AON_RST_CTRL_icap_SHIFT                            7
#define BCHP_PM_AON_RST_CTRL_icap_DEFAULT                          0x00000000

/* PM_AON :: RST_CTRL :: mspi [06:06] */
#define BCHP_PM_AON_RST_CTRL_mspi_MASK                             0x00000040
#define BCHP_PM_AON_RST_CTRL_mspi_SHIFT                            6
#define BCHP_PM_AON_RST_CTRL_mspi_DEFAULT                          0x00000000

/* PM_AON :: RST_CTRL :: ldk [05:05] */
#define BCHP_PM_AON_RST_CTRL_ldk_MASK                              0x00000020
#define BCHP_PM_AON_RST_CTRL_ldk_SHIFT                             5
#define BCHP_PM_AON_RST_CTRL_ldk_DEFAULT                           0x00000000

/* PM_AON :: RST_CTRL :: kbd3 [04:04] */
#define BCHP_PM_AON_RST_CTRL_kbd3_MASK                             0x00000010
#define BCHP_PM_AON_RST_CTRL_kbd3_SHIFT                            4
#define BCHP_PM_AON_RST_CTRL_kbd3_DEFAULT                          0x00000000

/* PM_AON :: RST_CTRL :: kbd2 [03:03] */
#define BCHP_PM_AON_RST_CTRL_kbd2_MASK                             0x00000008
#define BCHP_PM_AON_RST_CTRL_kbd2_SHIFT                            3
#define BCHP_PM_AON_RST_CTRL_kbd2_DEFAULT                          0x00000000

/* PM_AON :: RST_CTRL :: kbd1 [02:02] */
#define BCHP_PM_AON_RST_CTRL_kbd1_MASK                             0x00000004
#define BCHP_PM_AON_RST_CTRL_kbd1_SHIFT                            2
#define BCHP_PM_AON_RST_CTRL_kbd1_DEFAULT                          0x00000000

/* PM_AON :: RST_CTRL :: bscc [01:01] */
#define BCHP_PM_AON_RST_CTRL_bscc_MASK                             0x00000002
#define BCHP_PM_AON_RST_CTRL_bscc_SHIFT                            1
#define BCHP_PM_AON_RST_CTRL_bscc_DEFAULT                          0x00000000

/* PM_AON :: RST_CTRL :: bscb [00:00] */
#define BCHP_PM_AON_RST_CTRL_bscb_MASK                             0x00000001
#define BCHP_PM_AON_RST_CTRL_bscb_SHIFT                            0
#define BCHP_PM_AON_RST_CTRL_bscb_DEFAULT                          0x00000000

#endif /* #ifndef BCHP_PM_AON_H__ */

/* End of File */

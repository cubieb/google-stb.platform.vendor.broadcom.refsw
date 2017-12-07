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

#ifndef BCHP_KBD1_H__
#define BCHP_KBD1_H__

/***************************************************************************
 *KBD1 - IR Keyboard/Remote Receiver 1
 ***************************************************************************/
#define BCHP_KBD1_STATUS                         0x20417100 /* [RW][32] KEYBOARD/REMOTE RECEIVER STATUS REGISTER */
#define BCHP_KBD1_DIVISOR                        0x20417104 /* [RW][32] KEYBOARD/REMOTE RECEIVER DIVISOR */
#define BCHP_KBD1_FILTER1                        0x20417108 /* [RW][32] KEYBOARD FILTER1 */
#define BCHP_KBD1_DATA1                          0x2041710c /* [RW][32] KEYBOARD/REMOTE RECEIVER DATA WORD 1 (MS Word) */
#define BCHP_KBD1_DATA0                          0x20417110 /* [RW][32] KEYBOARD/REMOTE RECEIVER DATA WORD 0 (LS Word) */
#define BCHP_KBD1_CMD                            0x20417114 /* [RW][32] KEYBOARD/REMOTE RECEIVER COMMAND REGISTER */
#define BCHP_KBD1_CIR_ADDR                       0x20417118 /* [RW][32] CONSUMER IR DECODER ADDRESS REGISTER */
#define BCHP_KBD1_CIR_DATA                       0x2041711c /* [RW][32] CONSUMER IR DECODER DATA (LSB) */
#define BCHP_KBD1_KBD_MASK0                      0x20417120 /* [RW][32] KEBOARD INPUT MASK 0 */
#define BCHP_KBD1_KBD_MASK1                      0x20417124 /* [RW][32] KEBOARD INPUT MASK 1 */
#define BCHP_KBD1_KBD_MASK2                      0x20417128 /* [RW][32] KEBOARD INPUT MASK 2 */
#define BCHP_KBD1_KBD_PAT0                       0x2041712c /* [RW][32] KEBOARD INPUT PATTERN MATCH 0 */
#define BCHP_KBD1_KBD_PAT1                       0x20417130 /* [RW][32] KEBOARD INPUT PATTERN MATCH 1 */
#define BCHP_KBD1_KBD_PAT2                       0x20417134 /* [RW][32] KEBOARD INPUT PATTERN MATCH 2 */
#define BCHP_KBD1_STATUS2                        0x2041713c /* [RO][32] KEYBOARD/REMOTE RECEIVER STATUS2 REGISTER */

/***************************************************************************
 *STATUS - KEYBOARD/REMOTE RECEIVER STATUS REGISTER
 ***************************************************************************/
/* KBD1 :: STATUS :: reserved0 [31:08] */
#define BCHP_KBD1_STATUS_reserved0_MASK                            0xffffff00
#define BCHP_KBD1_STATUS_reserved0_SHIFT                           8

/* KBD1 :: STATUS :: lflag [07:07] */
#define BCHP_KBD1_STATUS_lflag_MASK                                0x00000080
#define BCHP_KBD1_STATUS_lflag_SHIFT                               7
#define BCHP_KBD1_STATUS_lflag_DEFAULT                             0x00000000

/* KBD1 :: STATUS :: cir_pa [06:06] */
#define BCHP_KBD1_STATUS_cir_pa_MASK                               0x00000040
#define BCHP_KBD1_STATUS_cir_pa_SHIFT                              6
#define BCHP_KBD1_STATUS_cir_pa_DEFAULT                            0x00000000

/* KBD1 :: STATUS :: cir_pb [05:05] */
#define BCHP_KBD1_STATUS_cir_pb_MASK                               0x00000020
#define BCHP_KBD1_STATUS_cir_pb_SHIFT                              5
#define BCHP_KBD1_STATUS_cir_pb_DEFAULT                            0x00000000

/* KBD1 :: STATUS :: device [04:02] */
#define BCHP_KBD1_STATUS_device_MASK                               0x0000001c
#define BCHP_KBD1_STATUS_device_SHIFT                              2
#define BCHP_KBD1_STATUS_device_DEFAULT                            0x00000000

/* KBD1 :: STATUS :: rflag [01:01] */
#define BCHP_KBD1_STATUS_rflag_MASK                                0x00000002
#define BCHP_KBD1_STATUS_rflag_SHIFT                               1
#define BCHP_KBD1_STATUS_rflag_DEFAULT                             0x00000000

/* KBD1 :: STATUS :: irq [00:00] */
#define BCHP_KBD1_STATUS_irq_MASK                                  0x00000001
#define BCHP_KBD1_STATUS_irq_SHIFT                                 0
#define BCHP_KBD1_STATUS_irq_DEFAULT                               0x00000000

/***************************************************************************
 *DIVISOR - KEYBOARD/REMOTE RECEIVER DIVISOR
 ***************************************************************************/
/* KBD1 :: DIVISOR :: reserved0 [31:06] */
#define BCHP_KBD1_DIVISOR_reserved0_MASK                           0xffffffc0
#define BCHP_KBD1_DIVISOR_reserved0_SHIFT                          6

/* KBD1 :: DIVISOR :: divisor [05:00] */
#define BCHP_KBD1_DIVISOR_divisor_MASK                             0x0000003f
#define BCHP_KBD1_DIVISOR_divisor_SHIFT                            0
#define BCHP_KBD1_DIVISOR_divisor_DEFAULT                          0x0000001f

/***************************************************************************
 *FILTER1 - KEYBOARD FILTER1
 ***************************************************************************/
/* KBD1 :: FILTER1 :: reserved0 [31:07] */
#define BCHP_KBD1_FILTER1_reserved0_MASK                           0xffffff80
#define BCHP_KBD1_FILTER1_reserved0_SHIFT                          7

/* KBD1 :: FILTER1 :: filter_en [06:06] */
#define BCHP_KBD1_FILTER1_filter_en_MASK                           0x00000040
#define BCHP_KBD1_FILTER1_filter_en_SHIFT                          6
#define BCHP_KBD1_FILTER1_filter_en_DEFAULT                        0x00000000

/* KBD1 :: FILTER1 :: filter_width [05:00] */
#define BCHP_KBD1_FILTER1_filter_width_MASK                        0x0000003f
#define BCHP_KBD1_FILTER1_filter_width_SHIFT                       0
#define BCHP_KBD1_FILTER1_filter_width_DEFAULT                     0x00000000

/***************************************************************************
 *DATA1 - KEYBOARD/REMOTE RECEIVER DATA WORD 1 (MS Word)
 ***************************************************************************/
/* KBD1 :: DATA1 :: reserved0 [31:08] */
#define BCHP_KBD1_DATA1_reserved0_MASK                             0xffffff00
#define BCHP_KBD1_DATA1_reserved0_SHIFT                            8

/* KBD1 :: DATA1 :: data [07:00] */
#define BCHP_KBD1_DATA1_data_MASK                                  0x000000ff
#define BCHP_KBD1_DATA1_data_SHIFT                                 0
#define BCHP_KBD1_DATA1_data_DEFAULT                               0x00000000

/***************************************************************************
 *DATA0 - KEYBOARD/REMOTE RECEIVER DATA WORD 0 (LS Word)
 ***************************************************************************/
/* KBD1 :: DATA0 :: data [31:00] */
#define BCHP_KBD1_DATA0_data_MASK                                  0xffffffff
#define BCHP_KBD1_DATA0_data_SHIFT                                 0
#define BCHP_KBD1_DATA0_data_DEFAULT                               0x00000000

/***************************************************************************
 *CMD - KEYBOARD/REMOTE RECEIVER COMMAND REGISTER
 ***************************************************************************/
/* KBD1 :: CMD :: reserved0 [31:09] */
#define BCHP_KBD1_CMD_reserved0_MASK                               0xfffffe00
#define BCHP_KBD1_CMD_reserved0_SHIFT                              9

/* KBD1 :: CMD :: data_filtering [08:08] */
#define BCHP_KBD1_CMD_data_filtering_MASK                          0x00000100
#define BCHP_KBD1_CMD_data_filtering_SHIFT                         8
#define BCHP_KBD1_CMD_data_filtering_DEFAULT                       0x00000000

/* KBD1 :: CMD :: test_mode [07:07] */
#define BCHP_KBD1_CMD_test_mode_MASK                               0x00000080
#define BCHP_KBD1_CMD_test_mode_SHIFT                              7
#define BCHP_KBD1_CMD_test_mode_DEFAULT                            0x00000000

/* KBD1 :: CMD :: alt_table [06:06] */
#define BCHP_KBD1_CMD_alt_table_MASK                               0x00000040
#define BCHP_KBD1_CMD_alt_table_SHIFT                              6
#define BCHP_KBD1_CMD_alt_table_DEFAULT                            0x00000000

/* KBD1 :: CMD :: kbd_irqen [05:05] */
#define BCHP_KBD1_CMD_kbd_irqen_MASK                               0x00000020
#define BCHP_KBD1_CMD_kbd_irqen_SHIFT                              5
#define BCHP_KBD1_CMD_kbd_irqen_DEFAULT                            0x00000000

/* KBD1 :: CMD :: device_en [04:00] */
#define BCHP_KBD1_CMD_device_en_MASK                               0x0000001f
#define BCHP_KBD1_CMD_device_en_SHIFT                              0
#define BCHP_KBD1_CMD_device_en_DEFAULT                            0x00000007

/***************************************************************************
 *CIR_ADDR - CONSUMER IR DECODER ADDRESS REGISTER
 ***************************************************************************/
/* KBD1 :: CIR_ADDR :: reserved0 [31:05] */
#define BCHP_KBD1_CIR_ADDR_reserved0_MASK                          0xffffffe0
#define BCHP_KBD1_CIR_ADDR_reserved0_SHIFT                         5

/* KBD1 :: CIR_ADDR :: cir_addr [04:00] */
#define BCHP_KBD1_CIR_ADDR_cir_addr_MASK                           0x0000001f
#define BCHP_KBD1_CIR_ADDR_cir_addr_SHIFT                          0
#define BCHP_KBD1_CIR_ADDR_cir_addr_DEFAULT                        0x00000000

/***************************************************************************
 *CIR_DATA - CONSUMER IR DECODER DATA (LSB)
 ***************************************************************************/
/* KBD1 :: CIR_DATA :: cir_data [31:00] */
#define BCHP_KBD1_CIR_DATA_cir_data_MASK                           0xffffffff
#define BCHP_KBD1_CIR_DATA_cir_data_SHIFT                          0
#define BCHP_KBD1_CIR_DATA_cir_data_DEFAULT                        0x00000000

/***************************************************************************
 *KBD_MASK0 - KEBOARD INPUT MASK 0
 ***************************************************************************/
/* KBD1 :: KBD_MASK0 :: kbd_mask0 [31:00] */
#define BCHP_KBD1_KBD_MASK0_kbd_mask0_MASK                         0xffffffff
#define BCHP_KBD1_KBD_MASK0_kbd_mask0_SHIFT                        0
#define BCHP_KBD1_KBD_MASK0_kbd_mask0_DEFAULT                      0xffffffff

/***************************************************************************
 *KBD_MASK1 - KEBOARD INPUT MASK 1
 ***************************************************************************/
/* KBD1 :: KBD_MASK1 :: kbd_mask1 [31:00] */
#define BCHP_KBD1_KBD_MASK1_kbd_mask1_MASK                         0xffffffff
#define BCHP_KBD1_KBD_MASK1_kbd_mask1_SHIFT                        0
#define BCHP_KBD1_KBD_MASK1_kbd_mask1_DEFAULT                      0xffffffff

/***************************************************************************
 *KBD_MASK2 - KEBOARD INPUT MASK 2
 ***************************************************************************/
/* KBD1 :: KBD_MASK2 :: kbd_mask0 [31:00] */
#define BCHP_KBD1_KBD_MASK2_kbd_mask0_MASK                         0xffffffff
#define BCHP_KBD1_KBD_MASK2_kbd_mask0_SHIFT                        0
#define BCHP_KBD1_KBD_MASK2_kbd_mask0_DEFAULT                      0xffffffff

/***************************************************************************
 *KBD_PAT0 - KEBOARD INPUT PATTERN MATCH 0
 ***************************************************************************/
/* KBD1 :: KBD_PAT0 :: kbd_pat0 [31:00] */
#define BCHP_KBD1_KBD_PAT0_kbd_pat0_MASK                           0xffffffff
#define BCHP_KBD1_KBD_PAT0_kbd_pat0_SHIFT                          0
#define BCHP_KBD1_KBD_PAT0_kbd_pat0_DEFAULT                        0x00000000

/***************************************************************************
 *KBD_PAT1 - KEBOARD INPUT PATTERN MATCH 1
 ***************************************************************************/
/* KBD1 :: KBD_PAT1 :: kbd_pat1 [31:00] */
#define BCHP_KBD1_KBD_PAT1_kbd_pat1_MASK                           0xffffffff
#define BCHP_KBD1_KBD_PAT1_kbd_pat1_SHIFT                          0
#define BCHP_KBD1_KBD_PAT1_kbd_pat1_DEFAULT                        0x00000000

/***************************************************************************
 *KBD_PAT2 - KEBOARD INPUT PATTERN MATCH 2
 ***************************************************************************/
/* KBD1 :: KBD_PAT2 :: kbd_pat0 [31:00] */
#define BCHP_KBD1_KBD_PAT2_kbd_pat0_MASK                           0xffffffff
#define BCHP_KBD1_KBD_PAT2_kbd_pat0_SHIFT                          0
#define BCHP_KBD1_KBD_PAT2_kbd_pat0_DEFAULT                        0x00000000

/***************************************************************************
 *STATUS2 - KEYBOARD/REMOTE RECEIVER STATUS2 REGISTER
 ***************************************************************************/
/* KBD1 :: STATUS2 :: reserved0 [31:07] */
#define BCHP_KBD1_STATUS2_reserved0_MASK                           0xffffff80
#define BCHP_KBD1_STATUS2_reserved0_SHIFT                          7

/* KBD1 :: STATUS2 :: cir_nbits_rcvd [06:00] */
#define BCHP_KBD1_STATUS2_cir_nbits_rcvd_MASK                      0x0000007f
#define BCHP_KBD1_STATUS2_cir_nbits_rcvd_SHIFT                     0
#define BCHP_KBD1_STATUS2_cir_nbits_rcvd_DEFAULT                   0x00000000

#endif /* #ifndef BCHP_KBD1_H__ */

/* End of File */

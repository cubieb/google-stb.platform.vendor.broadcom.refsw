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
 * Date:           Generated on               Thu Apr 13 10:09:31 2017
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

#ifndef BCHP_V3D_ERR_0_H__
#define BCHP_V3D_ERR_0_H__

/***************************************************************************
 *V3D_ERR_0 - V3D Error Registers
 ***************************************************************************/
#define BCHP_V3D_ERR_0_FDBGO                     0x01708f04 /* [RO][32] FEP Overrun Error Signals */
#define BCHP_V3D_ERR_0_FDBGB                     0x01708f08 /* [RO][32] FEP Interface Ready and Stall Signals, FEP Busy Signals */
#define BCHP_V3D_ERR_0_FDBGR                     0x01708f0c /* [RO][32] FEP Internal Ready Signals */
#define BCHP_V3D_ERR_0_FDBGS                     0x01708f10 /* [RO][32] FEP Internal Stall Input Signals */
#define BCHP_V3D_ERR_0_STAT                      0x01708f20 /* [RO][32] Miscellaneous Error Signals (VPM, VDW, VCD, VCM, L2C) */
#define BCHP_V3D_ERR_0_FPGA_BUILD0               0x01708fe8 /* [RW][32] FPGA Only - FPGA build number */
#define BCHP_V3D_ERR_0_FPGA_BUILD1               0x01708fec /* [RW][32] FPGA Only - FPGA build timestamp */
#define BCHP_V3D_ERR_0_FLOW0                     0x01708ff0 /* [RW][32] FPGA Only - something... */
#define BCHP_V3D_ERR_0_FLOW1                     0x01708ff4 /* [RW][32] FPGA Only - something... */
#define BCHP_V3D_ERR_0_FLOW2                     0x01708ff8 /* [RW][32] FPGA Only - something... */
#define BCHP_V3D_ERR_0_FLOW3                     0x01708ffc /* [RW][32] FPGA Only - something... */

/***************************************************************************
 *FDBGO - FEP Overrun Error Signals
 ***************************************************************************/
/* V3D_ERR_0 :: FDBGO :: reserved0 [31:29] */
#define BCHP_V3D_ERR_0_FDBGO_reserved0_MASK                        0xe0000000
#define BCHP_V3D_ERR_0_FDBGO_reserved0_SHIFT                       29

/* V3D_ERR_0 :: FDBGO :: EZREQ_FIFO_IP_ORUN [28:28] */
#define BCHP_V3D_ERR_0_FDBGO_EZREQ_FIFO_IP_ORUN_MASK               0x10000000
#define BCHP_V3D_ERR_0_FDBGO_EZREQ_FIFO_IP_ORUN_SHIFT              28

/* V3D_ERR_0 :: FDBGO :: QXYF_FIFO_OP_URUN [27:27] */
#define BCHP_V3D_ERR_0_FDBGO_QXYF_FIFO_OP_URUN_MASK                0x08000000
#define BCHP_V3D_ERR_0_FDBGO_QXYF_FIFO_OP_URUN_SHIFT               27

/* V3D_ERR_0 :: FDBGO :: EZVAL_FIFO_IP_ORUN [26:26] */
#define BCHP_V3D_ERR_0_FDBGO_EZVAL_FIFO_IP_ORUN_MASK               0x04000000
#define BCHP_V3D_ERR_0_FDBGO_EZVAL_FIFO_IP_ORUN_SHIFT              26

/* V3D_ERR_0 :: FDBGO :: DEPTHO_FIFO_OP_URUN [25:25] */
#define BCHP_V3D_ERR_0_FDBGO_DEPTHO_FIFO_OP_URUN_MASK              0x02000000
#define BCHP_V3D_ERR_0_FDBGO_DEPTHO_FIFO_OP_URUN_SHIFT             25

/* V3D_ERR_0 :: FDBGO :: ZMINMAXIX_OP_URUN [24:24] */
#define BCHP_V3D_ERR_0_FDBGO_ZMINMAXIX_OP_URUN_MASK                0x01000000
#define BCHP_V3D_ERR_0_FDBGO_ZMINMAXIX_OP_URUN_SHIFT               24

/* V3D_ERR_0 :: FDBGO :: ZCOEFF_FIFO_OP_URUN [23:23] */
#define BCHP_V3D_ERR_0_FDBGO_ZCOEFF_FIFO_OP_URUN_MASK              0x00800000
#define BCHP_V3D_ERR_0_FDBGO_ZCOEFF_FIFO_OP_URUN_SHIFT             23

/* V3D_ERR_0 :: FDBGO :: ZABCOEFF_FIFO_IP_ORUN [22:22] */
#define BCHP_V3D_ERR_0_FDBGO_ZABCOEFF_FIFO_IP_ORUN_MASK            0x00400000
#define BCHP_V3D_ERR_0_FDBGO_ZABCOEFF_FIFO_IP_ORUN_SHIFT           22

/* V3D_ERR_0 :: FDBGO :: ZABCOEFF_FIFO_OP_URUN [21:21] */
#define BCHP_V3D_ERR_0_FDBGO_ZABCOEFF_FIFO_OP_URUN_MASK            0x00200000
#define BCHP_V3D_ERR_0_FDBGO_ZABCOEFF_FIFO_OP_URUN_SHIFT           21

/* V3D_ERR_0 :: FDBGO :: XYRELW_FIFO_IP_ORUN [20:20] */
#define BCHP_V3D_ERR_0_FDBGO_XYRELW_FIFO_IP_ORUN_MASK              0x00100000
#define BCHP_V3D_ERR_0_FDBGO_XYRELW_FIFO_IP_ORUN_SHIFT             20

/* V3D_ERR_0 :: FDBGO :: XYRELW_FIFO_OP_URUN [19:19] */
#define BCHP_V3D_ERR_0_FDBGO_XYRELW_FIFO_OP_URUN_MASK              0x00080000
#define BCHP_V3D_ERR_0_FDBGO_XYRELW_FIFO_OP_URUN_SHIFT             19

/* V3D_ERR_0 :: FDBGO :: WCOEFF_FIFO_OP_URUN [18:18] */
#define BCHP_V3D_ERR_0_FDBGO_WCOEFF_FIFO_OP_URUN_MASK              0x00040000
#define BCHP_V3D_ERR_0_FDBGO_WCOEFF_FIFO_OP_URUN_SHIFT             18

/* V3D_ERR_0 :: FDBGO :: STCLBITS13_OP_URUN [17:17] */
#define BCHP_V3D_ERR_0_FDBGO_STCLBITS13_OP_URUN_MASK               0x00020000
#define BCHP_V3D_ERR_0_FDBGO_STCLBITS13_OP_URUN_SHIFT              17

/* V3D_ERR_0 :: FDBGO :: BLNDBITS13_OP_URUN [16:16] */
#define BCHP_V3D_ERR_0_FDBGO_BLNDBITS13_OP_URUN_MASK               0x00010000
#define BCHP_V3D_ERR_0_FDBGO_BLNDBITS13_OP_URUN_SHIFT              16

/* V3D_ERR_0 :: FDBGO :: CFGBITS1_CHANGE [15:15] */
#define BCHP_V3D_ERR_0_FDBGO_CFGBITS1_CHANGE_MASK                  0x00008000
#define BCHP_V3D_ERR_0_FDBGO_CFGBITS1_CHANGE_SHIFT                 15

/* V3D_ERR_0 :: FDBGO :: STCLBITS1_CHANGE [14:14] */
#define BCHP_V3D_ERR_0_FDBGO_STCLBITS1_CHANGE_MASK                 0x00004000
#define BCHP_V3D_ERR_0_FDBGO_STCLBITS1_CHANGE_SHIFT                14

/* V3D_ERR_0 :: FDBGO :: ISOLASTS2_FIFO_IP_ORUN [13:13] */
#define BCHP_V3D_ERR_0_FDBGO_ISOLASTS2_FIFO_IP_ORUN_MASK           0x00002000
#define BCHP_V3D_ERR_0_FDBGO_ISOLASTS2_FIFO_IP_ORUN_SHIFT          13

/* V3D_ERR_0 :: FDBGO :: CTRL2_FIFO_IP_ORUN [12:12] */
#define BCHP_V3D_ERR_0_FDBGO_CTRL2_FIFO_IP_ORUN_MASK               0x00001000
#define BCHP_V3D_ERR_0_FDBGO_CTRL2_FIFO_IP_ORUN_SHIFT              12

/* V3D_ERR_0 :: FDBGO :: STCLTAG2_FIFO_IP_ORUN [11:11] */
#define BCHP_V3D_ERR_0_FDBGO_STCLTAG2_FIFO_IP_ORUN_MASK            0x00000800
#define BCHP_V3D_ERR_0_FDBGO_STCLTAG2_FIFO_IP_ORUN_SHIFT           11

/* V3D_ERR_0 :: FDBGO :: BLNDTAG2_FIFO_IP_ORUN [10:10] */
#define BCHP_V3D_ERR_0_FDBGO_BLNDTAG2_FIFO_IP_ORUN_MASK            0x00000400
#define BCHP_V3D_ERR_0_FDBGO_BLNDTAG2_FIFO_IP_ORUN_SHIFT           10

/* V3D_ERR_0 :: FDBGO :: QD2_FIFO_IP_ORUN [09:09] */
#define BCHP_V3D_ERR_0_FDBGO_QD2_FIFO_IP_ORUN_MASK                 0x00000200
#define BCHP_V3D_ERR_0_FDBGO_QD2_FIFO_IP_ORUN_SHIFT                9

/* V3D_ERR_0 :: FDBGO :: QD2_FIFO_OP_URUN [08:08] */
#define BCHP_V3D_ERR_0_FDBGO_QD2_FIFO_OP_URUN_MASK                 0x00000100
#define BCHP_V3D_ERR_0_FDBGO_QD2_FIFO_OP_URUN_SHIFT                8

/* V3D_ERR_0 :: FDBGO :: WO3_FIFO_OP_URUN [07:07] */
#define BCHP_V3D_ERR_0_FDBGO_WO3_FIFO_OP_URUN_MASK                 0x00000080
#define BCHP_V3D_ERR_0_FDBGO_WO3_FIFO_OP_URUN_SHIFT                7

/* V3D_ERR_0 :: FDBGO :: ZABADD_IP_ORUN [06:06] */
#define BCHP_V3D_ERR_0_FDBGO_ZABADD_IP_ORUN_MASK                   0x00000040
#define BCHP_V3D_ERR_0_FDBGO_ZABADD_IP_ORUN_SHIFT                  6

/* V3D_ERR_0 :: FDBGO :: QD3_FIFO_IP_ORUN [05:05] */
#define BCHP_V3D_ERR_0_FDBGO_QD3_FIFO_IP_ORUN_MASK                 0x00000020
#define BCHP_V3D_ERR_0_FDBGO_QD3_FIFO_IP_ORUN_SHIFT                5

/* V3D_ERR_0 :: FDBGO :: QD3_FIFO_OP_URUN [04:04] */
#define BCHP_V3D_ERR_0_FDBGO_QD3_FIFO_OP_URUN_MASK                 0x00000010
#define BCHP_V3D_ERR_0_FDBGO_QD3_FIFO_OP_URUN_SHIFT                4

/* V3D_ERR_0 :: FDBGO :: XYRELO3_FIFO_IP_ORUN [03:03] */
#define BCHP_V3D_ERR_0_FDBGO_XYRELO3_FIFO_IP_ORUN_MASK             0x00000008
#define BCHP_V3D_ERR_0_FDBGO_XYRELO3_FIFO_IP_ORUN_SHIFT            3

/* V3D_ERR_0 :: FDBGO :: XYRELO3_FIFO_OP_URUN [02:02] */
#define BCHP_V3D_ERR_0_FDBGO_XYRELO3_FIFO_OP_URUN_MASK             0x00000004
#define BCHP_V3D_ERR_0_FDBGO_XYRELO3_FIFO_OP_URUN_SHIFT            2

/* V3D_ERR_0 :: FDBGO :: FSNV_URUN [01:01] */
#define BCHP_V3D_ERR_0_FDBGO_FSNV_URUN_MASK                        0x00000002
#define BCHP_V3D_ERR_0_FDBGO_FSNV_URUN_SHIFT                       1

/* V3D_ERR_0 :: FDBGO :: TILEST_URUN [00:00] */
#define BCHP_V3D_ERR_0_FDBGO_TILEST_URUN_MASK                      0x00000001
#define BCHP_V3D_ERR_0_FDBGO_TILEST_URUN_SHIFT                     0

/***************************************************************************
 *FDBGB - FEP Interface Ready and Stall Signals, FEP Busy Signals
 ***************************************************************************/
/* V3D_ERR_0 :: FDBGB :: reserved0 [31:28] */
#define BCHP_V3D_ERR_0_FDBGB_reserved0_MASK                        0xf0000000
#define BCHP_V3D_ERR_0_FDBGB_reserved0_SHIFT                       28

/* V3D_ERR_0 :: FDBGB :: QCTRL_FIFO_OP_READY [27:27] */
#define BCHP_V3D_ERR_0_FDBGB_QCTRL_FIFO_OP_READY_MASK              0x08000000
#define BCHP_V3D_ERR_0_FDBGB_QCTRL_FIFO_OP_READY_SHIFT             27

/* V3D_ERR_0 :: FDBGB :: RAST_BUSY [26:26] */
#define BCHP_V3D_ERR_0_FDBGB_RAST_BUSY_MASK                        0x04000000
#define BCHP_V3D_ERR_0_FDBGB_RAST_BUSY_SHIFT                       26

/* V3D_ERR_0 :: FDBGB :: EZ_XY_READY [25:25] */
#define BCHP_V3D_ERR_0_FDBGB_EZ_XY_READY_MASK                      0x02000000
#define BCHP_V3D_ERR_0_FDBGB_EZ_XY_READY_SHIFT                     25

/* V3D_ERR_0 :: FDBGB :: reserved1 [24:24] */
#define BCHP_V3D_ERR_0_FDBGB_reserved1_MASK                        0x01000000
#define BCHP_V3D_ERR_0_FDBGB_reserved1_SHIFT                       24

/* V3D_ERR_0 :: FDBGB :: EZ_DATA_READY [23:23] */
#define BCHP_V3D_ERR_0_FDBGB_EZ_DATA_READY_MASK                    0x00800000
#define BCHP_V3D_ERR_0_FDBGB_EZ_DATA_READY_SHIFT                   23

/* V3D_ERR_0 :: FDBGB :: reserved2 [22:08] */
#define BCHP_V3D_ERR_0_FDBGB_reserved2_MASK                        0x007fff00
#define BCHP_V3D_ERR_0_FDBGB_reserved2_SHIFT                       8

/* V3D_ERR_0 :: FDBGB :: ZRWPE_READY [07:07] */
#define BCHP_V3D_ERR_0_FDBGB_ZRWPE_READY_MASK                      0x00000080
#define BCHP_V3D_ERR_0_FDBGB_ZRWPE_READY_SHIFT                     7

/* V3D_ERR_0 :: FDBGB :: ZRWPE_STALL [06:06] */
#define BCHP_V3D_ERR_0_FDBGB_ZRWPE_STALL_MASK                      0x00000040
#define BCHP_V3D_ERR_0_FDBGB_ZRWPE_STALL_SHIFT                     6

/* V3D_ERR_0 :: FDBGB :: EDGES_CTRLID [05:03] */
#define BCHP_V3D_ERR_0_FDBGB_EDGES_CTRLID_MASK                     0x00000038
#define BCHP_V3D_ERR_0_FDBGB_EDGES_CTRLID_SHIFT                    3

/* V3D_ERR_0 :: FDBGB :: EDGES_ISCTRL [02:02] */
#define BCHP_V3D_ERR_0_FDBGB_EDGES_ISCTRL_MASK                     0x00000004
#define BCHP_V3D_ERR_0_FDBGB_EDGES_ISCTRL_SHIFT                    2

/* V3D_ERR_0 :: FDBGB :: EDGES_READY [01:01] */
#define BCHP_V3D_ERR_0_FDBGB_EDGES_READY_MASK                      0x00000002
#define BCHP_V3D_ERR_0_FDBGB_EDGES_READY_SHIFT                     1

/* V3D_ERR_0 :: FDBGB :: EDGES_STALL [00:00] */
#define BCHP_V3D_ERR_0_FDBGB_EDGES_STALL_MASK                      0x00000001
#define BCHP_V3D_ERR_0_FDBGB_EDGES_STALL_SHIFT                     0

/***************************************************************************
 *FDBGR - FEP Internal Ready Signals
 ***************************************************************************/
/* V3D_ERR_0 :: FDBGR :: reserved0 [31:29] */
#define BCHP_V3D_ERR_0_FDBGR_reserved0_MASK                        0xe0000000
#define BCHP_V3D_ERR_0_FDBGR_reserved0_SHIFT                       29

/* V3D_ERR_0 :: FDBGR :: RECIPW_READY [28:28] */
#define BCHP_V3D_ERR_0_FDBGR_RECIPW_READY_MASK                     0x10000000
#define BCHP_V3D_ERR_0_FDBGR_RECIPW_READY_SHIFT                    28

/* V3D_ERR_0 :: FDBGR :: INTERPRW_READY [27:27] */
#define BCHP_V3D_ERR_0_FDBGR_INTERPRW_READY_MASK                   0x08000000
#define BCHP_V3D_ERR_0_FDBGR_INTERPRW_READY_SHIFT                  27

/* V3D_ERR_0 :: FDBGR :: reserved1 [26:25] */
#define BCHP_V3D_ERR_0_FDBGR_reserved1_MASK                        0x06000000
#define BCHP_V3D_ERR_0_FDBGR_reserved1_SHIFT                       25

/* V3D_ERR_0 :: FDBGR :: INTERPZ_READY [24:24] */
#define BCHP_V3D_ERR_0_FDBGR_INTERPZ_READY_MASK                    0x01000000
#define BCHP_V3D_ERR_0_FDBGR_INTERPZ_READY_SHIFT                   24

/* V3D_ERR_0 :: FDBGR :: reserved2 [23:22] */
#define BCHP_V3D_ERR_0_FDBGR_reserved2_MASK                        0x00c00000
#define BCHP_V3D_ERR_0_FDBGR_reserved2_SHIFT                       22

/* V3D_ERR_0 :: FDBGR :: XYNRM_LAST [21:21] */
#define BCHP_V3D_ERR_0_FDBGR_XYNRM_LAST_MASK                       0x00200000
#define BCHP_V3D_ERR_0_FDBGR_XYNRM_LAST_SHIFT                      21

/* V3D_ERR_0 :: FDBGR :: XYNRM_READY [20:20] */
#define BCHP_V3D_ERR_0_FDBGR_XYNRM_READY_MASK                      0x00100000
#define BCHP_V3D_ERR_0_FDBGR_XYNRM_READY_SHIFT                     20

/* V3D_ERR_0 :: FDBGR :: EZFLOAT__READY [19:19] */
#define BCHP_V3D_ERR_0_FDBGR_EZFLOAT__READY_MASK                   0x00080000
#define BCHP_V3D_ERR_0_FDBGR_EZFLOAT__READY_SHIFT                  19

/* V3D_ERR_0 :: FDBGR :: reserved3 [18:18] */
#define BCHP_V3D_ERR_0_FDBGR_reserved3_MASK                        0x00040000
#define BCHP_V3D_ERR_0_FDBGR_reserved3_SHIFT                       18

/* V3D_ERR_0 :: FDBGR :: RAST_LAST [17:17] */
#define BCHP_V3D_ERR_0_FDBGR_RAST_LAST_MASK                        0x00020000
#define BCHP_V3D_ERR_0_FDBGR_RAST_LAST_SHIFT                       17

/* V3D_ERR_0 :: FDBGR :: RAST_READY [16:16] */
#define BCHP_V3D_ERR_0_FDBGR_RAST_READY_MASK                       0x00010000
#define BCHP_V3D_ERR_0_FDBGR_RAST_READY_SHIFT                      16

/* V3D_ERR_0 :: FDBGR :: reserved4 [15:12] */
#define BCHP_V3D_ERR_0_FDBGR_reserved4_MASK                        0x0000f000
#define BCHP_V3D_ERR_0_FDBGR_reserved4_SHIFT                       12

/* V3D_ERR_0 :: FDBGR :: XYRELO3_FIFO_READY [11:11] */
#define BCHP_V3D_ERR_0_FDBGR_XYRELO3_FIFO_READY_MASK               0x00000800
#define BCHP_V3D_ERR_0_FDBGR_XYRELO3_FIFO_READY_SHIFT              11

/* V3D_ERR_0 :: FDBGR :: reserved5 [10:08] */
#define BCHP_V3D_ERR_0_FDBGR_reserved5_MASK                        0x00000700
#define BCHP_V3D_ERR_0_FDBGR_reserved5_SHIFT                       8

/* V3D_ERR_0 :: FDBGR :: WCOEFF_FIFO_READY [07:07] */
#define BCHP_V3D_ERR_0_FDBGR_WCOEFF_FIFO_READY_MASK                0x00000080
#define BCHP_V3D_ERR_0_FDBGR_WCOEFF_FIFO_READY_SHIFT               7

/* V3D_ERR_0 :: FDBGR :: XYRELW_FIFO_READY [06:06] */
#define BCHP_V3D_ERR_0_FDBGR_XYRELW_FIFO_READY_MASK                0x00000040
#define BCHP_V3D_ERR_0_FDBGR_XYRELW_FIFO_READY_SHIFT               6

/* V3D_ERR_0 :: FDBGR :: ZCOEFF_FIFO_READY [05:05] */
#define BCHP_V3D_ERR_0_FDBGR_ZCOEFF_FIFO_READY_MASK                0x00000020
#define BCHP_V3D_ERR_0_FDBGR_ZCOEFF_FIFO_READY_SHIFT               5

/* V3D_ERR_0 :: FDBGR :: REFXY_FIFO_READY [04:04] */
#define BCHP_V3D_ERR_0_FDBGR_REFXY_FIFO_READY_MASK                 0x00000010
#define BCHP_V3D_ERR_0_FDBGR_REFXY_FIFO_READY_SHIFT                4

/* V3D_ERR_0 :: FDBGR :: DEPTHO_FIFO_READY [03:03] */
#define BCHP_V3D_ERR_0_FDBGR_DEPTHO_FIFO_READY_MASK                0x00000008
#define BCHP_V3D_ERR_0_FDBGR_DEPTHO_FIFO_READY_SHIFT               3

/* V3D_ERR_0 :: FDBGR :: EZVAL_FIFO_READY [02:02] */
#define BCHP_V3D_ERR_0_FDBGR_EZVAL_FIFO_READY_MASK                 0x00000004
#define BCHP_V3D_ERR_0_FDBGR_EZVAL_FIFO_READY_SHIFT                2

/* V3D_ERR_0 :: FDBGR :: EZREQ_FIFO_READY [01:01] */
#define BCHP_V3D_ERR_0_FDBGR_EZREQ_FIFO_READY_MASK                 0x00000002
#define BCHP_V3D_ERR_0_FDBGR_EZREQ_FIFO_READY_SHIFT                1

/* V3D_ERR_0 :: FDBGR :: QCTRL_FIFO_READY [00:00] */
#define BCHP_V3D_ERR_0_FDBGR_QCTRL_FIFO_READY_MASK                 0x00000001
#define BCHP_V3D_ERR_0_FDBGR_QCTRL_FIFO_READY_SHIFT                0

/***************************************************************************
 *FDBGS - FEP Internal Stall Input Signals
 ***************************************************************************/
/* V3D_ERR_0 :: FDBGS :: reserved0 [31:18] */
#define BCHP_V3D_ERR_0_FDBGS_reserved0_MASK                        0xfffc0000
#define BCHP_V3D_ERR_0_FDBGS_reserved0_SHIFT                       18

/* V3D_ERR_0 :: FDBGS :: INTERPZ_IP_STALL [17:17] */
#define BCHP_V3D_ERR_0_FDBGS_INTERPZ_IP_STALL_MASK                 0x00020000
#define BCHP_V3D_ERR_0_FDBGS_INTERPZ_IP_STALL_SHIFT                17

/* V3D_ERR_0 :: FDBGS :: DEPTHO_FIFO_IP_STALL [16:16] */
#define BCHP_V3D_ERR_0_FDBGS_DEPTHO_FIFO_IP_STALL_MASK             0x00010000
#define BCHP_V3D_ERR_0_FDBGS_DEPTHO_FIFO_IP_STALL_SHIFT            16

/* V3D_ERR_0 :: FDBGS :: reserved1 [15:15] */
#define BCHP_V3D_ERR_0_FDBGS_reserved1_MASK                        0x00008000
#define BCHP_V3D_ERR_0_FDBGS_reserved1_SHIFT                       15

/* V3D_ERR_0 :: FDBGS :: XYNRM_IP_STALL [14:14] */
#define BCHP_V3D_ERR_0_FDBGS_XYNRM_IP_STALL_MASK                   0x00004000
#define BCHP_V3D_ERR_0_FDBGS_XYNRM_IP_STALL_SHIFT                  14

/* V3D_ERR_0 :: FDBGS :: EZREQ_FIFO_OP_VALID [13:13] */
#define BCHP_V3D_ERR_0_FDBGS_EZREQ_FIFO_OP_VALID_MASK              0x00002000
#define BCHP_V3D_ERR_0_FDBGS_EZREQ_FIFO_OP_VALID_SHIFT             13

/* V3D_ERR_0 :: FDBGS :: QXYF_FIFO_OP_VALID [12:12] */
#define BCHP_V3D_ERR_0_FDBGS_QXYF_FIFO_OP_VALID_MASK               0x00001000
#define BCHP_V3D_ERR_0_FDBGS_QXYF_FIFO_OP_VALID_SHIFT              12

/* V3D_ERR_0 :: FDBGS :: QXYF_FIFO_OP_LAST [11:11] */
#define BCHP_V3D_ERR_0_FDBGS_QXYF_FIFO_OP_LAST_MASK                0x00000800
#define BCHP_V3D_ERR_0_FDBGS_QXYF_FIFO_OP_LAST_SHIFT               11

/* V3D_ERR_0 :: FDBGS :: reserved2 [10:08] */
#define BCHP_V3D_ERR_0_FDBGS_reserved2_MASK                        0x00000700
#define BCHP_V3D_ERR_0_FDBGS_reserved2_SHIFT                       8

/* V3D_ERR_0 :: FDBGS :: EZTEST_ANYQVALID [07:07] */
#define BCHP_V3D_ERR_0_FDBGS_EZTEST_ANYQVALID_MASK                 0x00000080
#define BCHP_V3D_ERR_0_FDBGS_EZTEST_ANYQVALID_SHIFT                7

/* V3D_ERR_0 :: FDBGS :: EZTEST_PASS [06:06] */
#define BCHP_V3D_ERR_0_FDBGS_EZTEST_PASS_MASK                      0x00000040
#define BCHP_V3D_ERR_0_FDBGS_EZTEST_PASS_SHIFT                     6

/* V3D_ERR_0 :: FDBGS :: EZTEST_QREADY [05:05] */
#define BCHP_V3D_ERR_0_FDBGS_EZTEST_QREADY_MASK                    0x00000020
#define BCHP_V3D_ERR_0_FDBGS_EZTEST_QREADY_SHIFT                   5

/* V3D_ERR_0 :: FDBGS :: EZTEST_VLF_OKNOVALID [04:04] */
#define BCHP_V3D_ERR_0_FDBGS_EZTEST_VLF_OKNOVALID_MASK             0x00000010
#define BCHP_V3D_ERR_0_FDBGS_EZTEST_VLF_OKNOVALID_SHIFT            4

/* V3D_ERR_0 :: FDBGS :: EZTEST_QSTALL [03:03] */
#define BCHP_V3D_ERR_0_FDBGS_EZTEST_QSTALL_MASK                    0x00000008
#define BCHP_V3D_ERR_0_FDBGS_EZTEST_QSTALL_SHIFT                   3

/* V3D_ERR_0 :: FDBGS :: EZTEST_IP_VLFSTALL [02:02] */
#define BCHP_V3D_ERR_0_FDBGS_EZTEST_IP_VLFSTALL_MASK               0x00000004
#define BCHP_V3D_ERR_0_FDBGS_EZTEST_IP_VLFSTALL_SHIFT              2

/* V3D_ERR_0 :: FDBGS :: EZTEST_IP_PRSTALL [01:01] */
#define BCHP_V3D_ERR_0_FDBGS_EZTEST_IP_PRSTALL_MASK                0x00000002
#define BCHP_V3D_ERR_0_FDBGS_EZTEST_IP_PRSTALL_SHIFT               1

/* V3D_ERR_0 :: FDBGS :: EZTEST_IP_QSTALL [00:00] */
#define BCHP_V3D_ERR_0_FDBGS_EZTEST_IP_QSTALL_MASK                 0x00000001
#define BCHP_V3D_ERR_0_FDBGS_EZTEST_IP_QSTALL_SHIFT                0

/***************************************************************************
 *STAT - Miscellaneous Error Signals (VPM, VDW, VCD, VCM, L2C)
 ***************************************************************************/
/* V3D_ERR_0 :: STAT :: reserved0 [31:16] */
#define BCHP_V3D_ERR_0_STAT_reserved0_MASK                         0xffff0000
#define BCHP_V3D_ERR_0_STAT_reserved0_SHIFT                        16

/* V3D_ERR_0 :: STAT :: L2CARE [15:15] */
#define BCHP_V3D_ERR_0_STAT_L2CARE_MASK                            0x00008000
#define BCHP_V3D_ERR_0_STAT_L2CARE_SHIFT                           15
#define BCHP_V3D_ERR_0_STAT_L2CARE_DEFAULT                         0x00000000

/* V3D_ERR_0 :: STAT :: VCMBE [14:14] */
#define BCHP_V3D_ERR_0_STAT_VCMBE_MASK                             0x00004000
#define BCHP_V3D_ERR_0_STAT_VCMBE_SHIFT                            14
#define BCHP_V3D_ERR_0_STAT_VCMBE_DEFAULT                          0x00000000

/* V3D_ERR_0 :: STAT :: VCMRE [13:13] */
#define BCHP_V3D_ERR_0_STAT_VCMRE_MASK                             0x00002000
#define BCHP_V3D_ERR_0_STAT_VCMRE_SHIFT                            13
#define BCHP_V3D_ERR_0_STAT_VCMRE_DEFAULT                          0x00000000

/* V3D_ERR_0 :: STAT :: VCDI [12:12] */
#define BCHP_V3D_ERR_0_STAT_VCDI_MASK                              0x00001000
#define BCHP_V3D_ERR_0_STAT_VCDI_SHIFT                             12
#define BCHP_V3D_ERR_0_STAT_VCDI_DEFAULT                           0x00000001

/* V3D_ERR_0 :: STAT :: VCDE [11:11] */
#define BCHP_V3D_ERR_0_STAT_VCDE_MASK                              0x00000800
#define BCHP_V3D_ERR_0_STAT_VCDE_SHIFT                             11
#define BCHP_V3D_ERR_0_STAT_VCDE_DEFAULT                           0x00000000

/* V3D_ERR_0 :: STAT :: VDWE [10:10] */
#define BCHP_V3D_ERR_0_STAT_VDWE_MASK                              0x00000400
#define BCHP_V3D_ERR_0_STAT_VDWE_SHIFT                             10
#define BCHP_V3D_ERR_0_STAT_VDWE_DEFAULT                           0x00000000

/* V3D_ERR_0 :: STAT :: VPMEAS [09:09] */
#define BCHP_V3D_ERR_0_STAT_VPMEAS_MASK                            0x00000200
#define BCHP_V3D_ERR_0_STAT_VPMEAS_SHIFT                           9
#define BCHP_V3D_ERR_0_STAT_VPMEAS_DEFAULT                         0x00000000

/* V3D_ERR_0 :: STAT :: VPMEFNA [08:08] */
#define BCHP_V3D_ERR_0_STAT_VPMEFNA_MASK                           0x00000100
#define BCHP_V3D_ERR_0_STAT_VPMEFNA_SHIFT                          8
#define BCHP_V3D_ERR_0_STAT_VPMEFNA_DEFAULT                        0x00000000

/* V3D_ERR_0 :: STAT :: VPMEWNA [07:07] */
#define BCHP_V3D_ERR_0_STAT_VPMEWNA_MASK                           0x00000080
#define BCHP_V3D_ERR_0_STAT_VPMEWNA_SHIFT                          7
#define BCHP_V3D_ERR_0_STAT_VPMEWNA_DEFAULT                        0x00000000

/* V3D_ERR_0 :: STAT :: VPMERNA [06:06] */
#define BCHP_V3D_ERR_0_STAT_VPMERNA_MASK                           0x00000040
#define BCHP_V3D_ERR_0_STAT_VPMERNA_SHIFT                          6
#define BCHP_V3D_ERR_0_STAT_VPMERNA_DEFAULT                        0x00000000

/* V3D_ERR_0 :: STAT :: VPMERR [05:05] */
#define BCHP_V3D_ERR_0_STAT_VPMERR_MASK                            0x00000020
#define BCHP_V3D_ERR_0_STAT_VPMERR_SHIFT                           5
#define BCHP_V3D_ERR_0_STAT_VPMERR_DEFAULT                         0x00000000

/* V3D_ERR_0 :: STAT :: VPMEWR [04:04] */
#define BCHP_V3D_ERR_0_STAT_VPMEWR_MASK                            0x00000010
#define BCHP_V3D_ERR_0_STAT_VPMEWR_SHIFT                           4
#define BCHP_V3D_ERR_0_STAT_VPMEWR_DEFAULT                         0x00000000

/* V3D_ERR_0 :: STAT :: VPAERRGL [03:03] */
#define BCHP_V3D_ERR_0_STAT_VPAERRGL_MASK                          0x00000008
#define BCHP_V3D_ERR_0_STAT_VPAERRGL_SHIFT                         3
#define BCHP_V3D_ERR_0_STAT_VPAERRGL_DEFAULT                       0x00000000

/* V3D_ERR_0 :: STAT :: VPAEBRGL [02:02] */
#define BCHP_V3D_ERR_0_STAT_VPAEBRGL_MASK                          0x00000004
#define BCHP_V3D_ERR_0_STAT_VPAEBRGL_SHIFT                         2
#define BCHP_V3D_ERR_0_STAT_VPAEBRGL_DEFAULT                       0x00000000

/* V3D_ERR_0 :: STAT :: VPAERGS [01:01] */
#define BCHP_V3D_ERR_0_STAT_VPAERGS_MASK                           0x00000002
#define BCHP_V3D_ERR_0_STAT_VPAERGS_SHIFT                          1
#define BCHP_V3D_ERR_0_STAT_VPAERGS_DEFAULT                        0x00000000

/* V3D_ERR_0 :: STAT :: VPAEABB [00:00] */
#define BCHP_V3D_ERR_0_STAT_VPAEABB_MASK                           0x00000001
#define BCHP_V3D_ERR_0_STAT_VPAEABB_SHIFT                          0
#define BCHP_V3D_ERR_0_STAT_VPAEABB_DEFAULT                        0x00000000

/***************************************************************************
 *FPGA_BUILD0 - FPGA Only - FPGA build number
 ***************************************************************************/
/* V3D_ERR_0 :: FPGA_BUILD0 :: DBG [31:00] */
#define BCHP_V3D_ERR_0_FPGA_BUILD0_DBG_MASK                        0xffffffff
#define BCHP_V3D_ERR_0_FPGA_BUILD0_DBG_SHIFT                       0

/***************************************************************************
 *FPGA_BUILD1 - FPGA Only - FPGA build timestamp
 ***************************************************************************/
/* V3D_ERR_0 :: FPGA_BUILD1 :: DBG [31:00] */
#define BCHP_V3D_ERR_0_FPGA_BUILD1_DBG_MASK                        0xffffffff
#define BCHP_V3D_ERR_0_FPGA_BUILD1_DBG_SHIFT                       0

/***************************************************************************
 *FLOW0 - FPGA Only - something...
 ***************************************************************************/
/* V3D_ERR_0 :: FLOW0 :: DBG [31:00] */
#define BCHP_V3D_ERR_0_FLOW0_DBG_MASK                              0xffffffff
#define BCHP_V3D_ERR_0_FLOW0_DBG_SHIFT                             0

/***************************************************************************
 *FLOW1 - FPGA Only - something...
 ***************************************************************************/
/* V3D_ERR_0 :: FLOW1 :: DBG [31:00] */
#define BCHP_V3D_ERR_0_FLOW1_DBG_MASK                              0xffffffff
#define BCHP_V3D_ERR_0_FLOW1_DBG_SHIFT                             0

/***************************************************************************
 *FLOW2 - FPGA Only - something...
 ***************************************************************************/
/* V3D_ERR_0 :: FLOW2 :: DBG [31:00] */
#define BCHP_V3D_ERR_0_FLOW2_DBG_MASK                              0xffffffff
#define BCHP_V3D_ERR_0_FLOW2_DBG_SHIFT                             0

/***************************************************************************
 *FLOW3 - FPGA Only - something...
 ***************************************************************************/
/* V3D_ERR_0 :: FLOW3 :: DBG [31:00] */
#define BCHP_V3D_ERR_0_FLOW3_DBG_MASK                              0xffffffff
#define BCHP_V3D_ERR_0_FLOW3_DBG_SHIFT                             0

#endif /* #ifndef BCHP_V3D_ERR_0_H__ */

/* End of File */

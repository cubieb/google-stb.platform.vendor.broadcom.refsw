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
 ******************************************************************************
 *
 *                            Do Not Edit Directly
 * Auto-Generated from RTS environment:
 *   at: Fri Mar 10 22:12:54 2017 GMT
 *   by: kranawet
 *   for: Box 3_LPDDR4_2133
 *         MemC 0 (32-bit LPDDR4@1067MHz) w/432MHz clock
 *
 *   Run from /projects/bbvlsi_core1/rts/rev1_0/snapshot/rts_shell2/rts_code/rts_shell_v3.pl
 *     /projects/bbvlsi_core1/Architecture/Chips/7271/rts/sim/BCM7271.cfg
 *     /projects/bbvlsi_core1/Architecture/Chips/7271/rts/sim/BCM7271boxes.cfg
 *     /projects/bbvlsi_core1/rts/rev1_0/snapshot/rts_shell2/rts_code/timing_model/MEMC_b2r8_timingd_CLwc.lib
 *     /projects/bbvlsi_core1/Architecture/Chips/7271/rts/sim/BCM7271BvnLib_7271Custom.cfg
 *     /projects/bbvlsi_core1/rts/rev1_0/snapshot/rts_shell2/rts_code/timing_model/VideoDecoder_rS2b.cfg
 *     /projects/bbvlsi_core1/Architecture/Chips/7271/rts/sim/BCM7271Client.cfg
 *     /projects/bbvlsi_core1/Architecture/Chips/7271/rts/sim/BCM7271ClientGroups.cfg
 *
 *****************************************************************************/

#include "bchp_memc_gen_0.h"  /* located in /TBD directory */

#include "bbox.h"  /* located in /magnum/commonutils/box/include directory */

static const uint32_t aulMemc0_20170310221254_3_LPDDR4_2133[] = {
           0x00fa8017,  /*   0: XPT_WR_RS 9283ns */
           0x80c9702c,  /*   1: XPT_WR_XC RR 7915ns */
           0x80e7e016,  /*   2: XPT_WR_CDB RR 8594ns */
           0x82c89033,  /*   3: XPT_WR_ITB_MSG RR 27981ns */
           0x8488101d,  /*   4: XPT_RD_RS RR 42971ns */
           0x8fdca01f,  /*   5: XPT_RD_XC_RMX_MSG RR 150400ns */
           0x80e7e015,  /*   6: XPT_RD_XC_RAVE RR 8594ns */
           0x8092d026,  /*   7: XPT_RD_PB RR 5769ns */
           0x84750034,  /*   8: XPT_WR_MEMDMA RR 44800ns */
           0x3ffff0ff,  /*   9: UNASSIGNED off */
           0x81a26019,  /*  10: GENET0_WR RR 15500ns */
           0x87881038,  /*  11: GENET0_RD RR 75700ns */
           0x81a2601a,  /*  12: GENET1_WR RR 15500ns */
           0x82829032,  /*  13: GENET1_RD RR 25233ns */
           0x3ffff0ff,  /*  14: UNASSIGNED off */
           0x3ffff0ff,  /*  15: UNASSIGNED off */
           0x3ffff0ff,  /*  16: UNASSIGNED off */
           0x8129e02f,  /*  17: SATA RR 11700ns */
           0x3ffff0ff,  /*  18: UNASSIGNED off */
           0x3ffff0ff,  /*  19: UNASSIGNED off */
           0x3ffff0ff,  /*  20: UNASSIGNED off */
           0x3ffff0ff,  /*  21: UNASSIGNED off */
           0x8545e01e,  /*  22: BSP RR 50000ns */
           0x80ad9028,  /*  23: SAGE RR 6820ns */
           0x86449035,  /*  24: FLASH_DMA RR 63000ns */
           0x3ffff0ff,  /*  25: UNASSIGNED off */
           0x86449037,  /*  26: SDIO_EMMC RR 63000ns */
           0x86449036,  /*  27: SDIO_CARD RR 63000ns */
           0xbffff0ff,  /*  28: TPCAP RR */
           0x3ffff0ff,  /*  29: UNASSIGNED off */
           0x3ffff0ff,  /*  30: UNASSIGNED off */
           0xbffff0ff,  /*  31: UART_DMA_RD RR */
           0xbffff0ff,  /*  32: UART_DMA_WR RR */
           0x810db02e,  /*  33: USB_HI_0 RR 10593ns */
           0xbffff0ff,  /*  34: USB_LO_0 RR */
           0x815c5031,  /*  35: USB_X_WRITE_0 RR 13680ns */
           0x815c5030,  /*  36: USB_X_READ_0 RR 13680ns */
           0x80ae1029,  /*  37: USB_X_CTRL_0 RR 6840ns */
           0x810db02d,  /*  38: USB_BDC RR 10593ns */
           0x3ffff0ff,  /*  39: UNASSIGNED off */
           0x803d0022,  /*  40: RAAGA RR 2400ns */
           0x89f30039,  /*  41: RAAGA_1 RR 100000ns */
           0x3ffff0ff,  /*  42: UNASSIGNED off */
           0x3ffff0ff,  /*  43: UNASSIGNED off */
           0x80b0a02a,  /*  44: AUD_AIO RR 6940ns */
           0x3ffff0ff,  /*  45: UNASSIGNED off */
           0x3ffff0ff,  /*  46: UNASSIGNED off */
           0x3ffff0ff,  /*  47: UNASSIGNED off */
           0x3ffff0ff,  /*  48: UNASSIGNED off */
           0x3ffff0ff,  /*  49: UNASSIGNED off */
           0x3ffff0ff,  /*  50: UNASSIGNED off */
           0x3ffff0ff,  /*  51: UNASSIGNED off */
           0x3ffff0ff,  /*  52: UNASSIGNED off */
           0x3ffff0ff,  /*  53: UNASSIGNED off */
           0x3ffff0ff,  /*  54: UNASSIGNED off */
           0xbffff0ff,  /*  55: VEC_VIP0 RR */
           0xbffff0ff,  /*  56: VEC_VIP1 RR */
           0x3ffff0ff,  /*  57: UNASSIGNED off */
           0x3ffff0ff,  /*  58: UNASSIGNED off */
           0x3ffff0ff,  /*  59: UNASSIGNED off */
           0x3ffff0ff,  /*  60: UNASSIGNED off */
           0x3ffff0ff,  /*  61: UNASSIGNED off */
           0x3ffff0ff,  /*  62: UNASSIGNED off */
           0x3ffff0ff,  /*  63: UNASSIGNED off */
           0x3ffff0ff,  /*  64: UNASSIGNED off */
           0x3ffff0ff,  /*  65: UNASSIGNED off */
           0x3ffff0ff,  /*  66: UNASSIGNED off */
           0x3ffff0ff,  /*  67: UNASSIGNED off */
           0x3ffff0ff,  /*  68: UNASSIGNED off */
           0x3ffff0ff,  /*  69: UNASSIGNED off */
           0x3ffff0ff,  /*  70: UNASSIGNED off */
           0x3ffff0ff,  /*  71: UNASSIGNED off */
           0x3ffff0ff,  /*  72: UNASSIGNED off */
           0x8015103b,  /*  73: HVD0_DBLK_0 RR 0ns */
           0x8015103c,  /*  74: HVD0_DBLK_1 RR 0ns */
           0x808c6024,  /*  75: HVD0_ILCPU RR 5204ns */
           0x805a6023,  /*  76: HVD0_OLCPU RR 3553ns */
           0x006b4009,  /*  77: HVD0_CAB 3977ns */
           0x0071f00a,  /*  78: HVD0_ILSI 4226ns */
           0x808c6025,  /*  79: HVD0_ILCPU_p2 RR 5204ns */
           0x0071f00b,  /*  80: HVD0_ILSI_p2 4226ns */
           0x3ffff0ff,  /*  81: UNASSIGNED off */
           0x3ffff0ff,  /*  82: UNASSIGNED off */
           0x3ffff0ff,  /*  83: UNASSIGNED off */
           0x3ffff0ff,  /*  84: UNASSIGNED off */
           0x3ffff0ff,  /*  85: UNASSIGNED off */
           0x3ffff0ff,  /*  86: UNASSIGNED off */
           0xbffff0ff,  /*  87: SID RR */
           0x3ffff0ff,  /*  88: UNASSIGNED off */
           0x3ffff0ff,  /*  89: UNASSIGNED off */
           0x3ffff0ff,  /*  90: UNASSIGNED off */
           0x3ffff0ff,  /*  91: UNASSIGNED off */
           0x3ffff0ff,  /*  92: UNASSIGNED off */
           0x3ffff0ff,  /*  93: UNASSIGNED off */
           0x005e3007,  /*  94: BVN_MAD_PIX_FD 3511ns +HRT(0.5%) */
           0x00848011,  /*  95: BVN_MAD_QUANT 4938ns +HRT(0.5%) */
           0x00bc8014,  /*  96: BVN_MAD_PIX_CAP 7023ns +HRT(0.5%) */
           0x005e3006,  /*  97: BVN_MAD1_PIX_FD 3511ns +HRT(0.5%) */
           0x00848010,  /*  98: BVN_MAD1_QUANT 4938ns +HRT(0.5%) */
           0x00bc8013,  /*  99: BVN_MAD1_PIX_CAP 7023ns +HRT(0.5%) */
           0x3ffff0ff,  /* 100: UNASSIGNED off */
           0x3ffff0ff,  /* 101: UNASSIGNED off */
           0x3ffff0ff,  /* 102: UNASSIGNED off */
           0x3ffff0ff,  /* 103: UNASSIGNED off */
           0x3ffff0ff,  /* 104: UNASSIGNED off */
           0x3ffff0ff,  /* 105: UNASSIGNED off */
           0x0085300e,  /* 106: BVN_MFD0 4938ns */
           0x0058c004,  /* 107: BVN_MFD0_1 3292ns */
           0x0085300f,  /* 108: BVN_MFD1 4938ns */
           0x0058c005,  /* 109: BVN_MFD1_1 3292ns */
           0x3ffff0ff,  /* 110: UNASSIGNED off */
           0x3ffff0ff,  /* 111: UNASSIGNED off */
           0x3ffff0ff,  /* 112: UNASSIGNED off */
           0x3ffff0ff,  /* 113: UNASSIGNED off */
           0x3ffff0ff,  /* 114: UNASSIGNED off */
           0x3ffff0ff,  /* 115: UNASSIGNED off */
           0x3ffff0ff,  /* 116: UNASSIGNED off */
           0x3ffff0ff,  /* 117: UNASSIGNED off */
           0x003fd002,  /* 118: BVN_VFD0 2370ns */
           0x001fd000,  /* 119: BVN_VFD1 1185ns */
           0x3ffff0ff,  /* 120: UNASSIGNED off */
           0x3ffff0ff,  /* 121: UNASSIGNED off */
           0x3ffff0ff,  /* 122: UNASSIGNED off */
           0x3ffff0ff,  /* 123: UNASSIGNED off */
           0x3ffff0ff,  /* 124: UNASSIGNED off */
           0x3ffff0ff,  /* 125: UNASSIGNED off */
           0x007f300c,  /* 126: BVN_CAP0 4741ns +HRT(0.5%) */
           0x007f300d,  /* 127: BVN_CAP1 4741ns +HRT(0.5%) */
           0x3ffff0ff,  /* 128: UNASSIGNED off */
           0x3ffff0ff,  /* 129: UNASSIGNED off */
           0x3ffff0ff,  /* 130: UNASSIGNED off */
           0x3ffff0ff,  /* 131: UNASSIGNED off */
           0x3ffff0ff,  /* 132: UNASSIGNED off */
           0x3ffff0ff,  /* 133: UNASSIGNED off */
           0x0031d001,  /* 134: BVN_GFD0 1851ns */
           0x01ac701b,  /* 135: BVN_GFD1 15873ns */
           0x3ffff0ff,  /* 136: UNASSIGNED off */
           0x3ffff0ff,  /* 137: UNASSIGNED off */
           0x3ffff0ff,  /* 138: UNASSIGNED off */
           0x3ffff0ff,  /* 139: UNASSIGNED off */
           0x3ffff0ff,  /* 140: UNASSIGNED off */
           0x3ffff0ff,  /* 141: UNASSIGNED off */
           0x3ffff0ff,  /* 142: UNASSIGNED off */
           0x3ffff0ff,  /* 143: UNASSIGNED off */
           0x00571003,  /* 144: BVN_RDC 3230ns */
           0x0352601c,  /* 145: VEC_VBI_ENC0 31500ns */
           0x0179e018,  /* 146: VEC_HDR0 14000ns */
           0xbffff0ff,  /* 147: M2MC_0 RR */
           0xbffff0ff,  /* 148: M2MC_1 RR */
           0xbffff0ff,  /* 149: M2MC_2 RR */
           0x3ffff0ff,  /* 150: UNASSIGNED off */
           0xbffff0ff,  /* 151: PCIe_0 RR */
           0x3ffff0ff,  /* 152: UNASSIGNED off */
           0x3ffff0ff,  /* 153: UNASSIGNED off */
           0x3ffff0ff,  /* 154: UNASSIGNED off */
           0x8015103d,  /* 155: HVD0_DBLK_p2_0 RR 0ns */
           0x8015103e,  /* 156: HVD0_DBLK_p2_1 RR 0ns */
           0x3ffff0ff,  /* 157: UNASSIGNED off */
           0x3ffff0ff,  /* 158: UNASSIGNED off */
           0x3ffff0ff,  /* 159: UNASSIGNED off */
           0x80b9d02b,  /* 160: WIFI_CTRL_WR RR 7300ns */
           0x80939027,  /* 161: WIFI_CTRL_RD RR 5800ns */
           0x3ffff0ff,  /* 162: WIFI_WR off */
           0x3ffff0ff,  /* 163: WIFI_RD_1 off */
           0x3ffff0ff,  /* 164: UNASSIGNED off */
           0x3ffff0ff,  /* 165: UNASSIGNED off */
           0x008b5012,  /* 166: CMP0 5166ns */
           0x3ffff0ff,  /* 167: UNASSIGNED off */
           0x3ffff0ff,  /* 168: UNASSIGNED off */
           0x3ffff0ff,  /* 169: UNASSIGNED off */
           0x3ffff0ff,  /* 170: UNASSIGNED off */
           0x3ffff0ff,  /* 171: UNASSIGNED off */
           0x3ffff0ff,  /* 172: UNASSIGNED off */
           0x3ffff0ff,  /* 173: UNASSIGNED off */
           0x3ffff0ff,  /* 174: UNASSIGNED off */
           0x3ffff0ff,  /* 175: UNASSIGNED off */
           0x3ffff0ff,  /* 176: UNASSIGNED off */
           0x3ffff0ff,  /* 177: UNASSIGNED off */
           0x3ffff0ff,  /* 178: UNASSIGNED off */
           0x3ffff0ff,  /* 179: UNASSIGNED off */
           0x3ffff0ff,  /* 180: UNASSIGNED off */
           0x3ffff0ff,  /* 181: UNASSIGNED off */
           0x3ffff0ff,  /* 182: UNASSIGNED off */
           0x3ffff0ff,  /* 183: UNASSIGNED off */
           0x3ffff0ff,  /* 184: UNASSIGNED off */
           0x3ffff0ff,  /* 185: UNASSIGNED off */
           0x3ffff0ff,  /* 186: UNASSIGNED off */
           0x3ffff0ff,  /* 187: UNASSIGNED off */
           0x3ffff0ff,  /* 188: UNASSIGNED off */
           0x3ffff0ff,  /* 189: UNASSIGNED off */
           0x3ffff0ff,  /* 190: UNASSIGNED off */
           0x3ffff0ff,  /* 191: UNASSIGNED off */
           0x3ffff0ff,  /* 192: UNASSIGNED off */
           0x3ffff0ff,  /* 193: UNASSIGNED off */
           0x3ffff0ff,  /* 194: UNASSIGNED off */
           0x3ffff0ff,  /* 195: UNASSIGNED off */
           0x3ffff0ff,  /* 196: UNASSIGNED off */
           0x3ffff0ff,  /* 197: UNASSIGNED off */
           0x3ffff0ff,  /* 198: UNASSIGNED off */
           0x3ffff0ff,  /* 199: UNASSIGNED off */
           0x801e4020,  /* 200: CPU_MCP_RD_HIGH RR 1125ns */
           0x80000041,  /* 201: CPU_MCP_RD_LOW RR */
           0x803ca021,  /* 202: CPU_MCP_WR_HIGH RR 2250ns */
           0x80000042,  /* 203: CPU_MCP_WR_LOW RR */
           0xbffff0ff,  /* 204: V3D_MCP_RD_HIGH RR */
           0xbffff0ff,  /* 205: V3D_MCP_RD_LOW RR */
           0xbffff0ff,  /* 206: V3D_MCP_WR_HIGH RR */
           0xbffff0ff,  /* 207: V3D_MCP_WR_LOW RR */
           0x3ffff0ff,  /* 208: UNASSIGNED off */
           0x3ffff0ff,  /* 209: UNASSIGNED off */
           0x3ffff0ff,  /* 210: UNASSIGNED off */
           0x3ffff0ff,  /* 211: UNASSIGNED off */
           0x3ffff0ff,  /* 212: UNASSIGNED off */
           0x3ffff0ff,  /* 213: UNASSIGNED off */
           0x3ffff0ff,  /* 214: UNASSIGNED off */
           0x3ffff0ff,  /* 215: UNASSIGNED off */
           0x8000003f,  /* 216: HVD0_PFRI RR 0ns */
           0x3ffff0ff,  /* 217: UNASSIGNED off */
           0x3ffff0ff,  /* 218: UNASSIGNED off */
           0x3ffff0ff,  /* 219: UNASSIGNED off */
           0x3ffff0ff,  /* 220: UNASSIGNED off */
           0x3ffff0ff,  /* 221: UNASSIGNED off */
           0x3ffff0ff,  /* 222: UNASSIGNED off */
           0x3ffff0ff,  /* 223: UNASSIGNED off */
           0x3ffff0ff,  /* 224: UNASSIGNED off */
           0x3ffff0ff,  /* 225: UNASSIGNED off */
           0x3ffff0ff,  /* 226: UNASSIGNED off */
           0x3ffff0ff,  /* 227: UNASSIGNED off */
           0x3ffff0ff,  /* 228: UNASSIGNED off */
           0x3ffff0ff,  /* 229: UNASSIGNED off */
           0x3ffff0ff,  /* 230: UNASSIGNED off */
           0x3ffff0ff,  /* 231: UNASSIGNED off */
           0x3ffff0ff,  /* 232: UNASSIGNED off */
           0x3ffff0ff,  /* 233: UNASSIGNED off */
           0x3ffff0ff,  /* 234: UNASSIGNED off */
           0x3ffff0ff,  /* 235: UNASSIGNED off */
           0x3ffff0ff,  /* 236: UNASSIGNED off */
           0x3ffff0ff,  /* 237: UNASSIGNED off */
           0x3ffff0ff,  /* 238: UNASSIGNED off */
           0x3ffff0ff,  /* 239: UNASSIGNED off */
           0x3ffff0ff,  /* 240: UNASSIGNED off */
           0x3ffff0ff,  /* 241: UNASSIGNED off */
           0x3ffff0ff,  /* 242: UNASSIGNED off */
           0x3ffff0ff,  /* 243: UNASSIGNED off */
           0x3ffff0ff,  /* 244: UNASSIGNED off */
           0x3ffff0ff,  /* 245: UNASSIGNED off */
           0x3ffff0ff,  /* 246: UNASSIGNED off */
           0x3ffff0ff,  /* 247: UNASSIGNED off */
           0xbffff0ff,  /* 248: MEMC_TRACELOG RR */
           0x3ffff0ff,  /* 249: UNASSIGNED off */
           0xbfffe03a,  /* 250: MEMC_ZQCS RR 1000000ns */
           0xbffff0ff,  /* 251: MEMC_MSA RR */
           0xbffff0ff,  /* 252: MEMC_DIS0 RR */
           0xbffff0ff,  /* 253: MEMC_DIS1 RR */
           0xbffff0ff,  /* 254: MEMC_DRAM_INIT_ZQCS RR */
           0x00694008   /* 255: REFRESH 3904ns */
         };


static const BBOX_Rts_PfriClient stBoxRts_PfriClient_20170310221254_3_LPDDR4_2133[] = {
  {BCHP_MEMC_GEN_0_PFRI_0_THROTTLE_CONFIG,      0x80400903}, /* HVD0_PFRI (gHVC) 471360.00 ns/40 */
  {BCHP_MEMC_GEN_0_PFRI_0_THROTTLE_FILTER_CTRL, 0x400004f8}, /* d: 4; p: 1272.66875 */
  {BCHP_MEMC_GEN_0_PFRI_0_THROTTLE_THRESH0,     0x00001500}, /* 5376 */
  {BCHP_MEMC_GEN_0_PFRI_0_THROTTLE_THRESH1,     0x00000c99}  /* 60% * 5376 */
};

static const uint32_t* const paulMemc_box3[] = { &aulMemc0_20170310221254_3_LPDDR4_2133[0]};

const BBOX_Rts stBoxRts_3_LPDDR4_2133_box3 = {
  "20170310221254_3_LPDDR4_2133_box3",
  7271,
  3,
  1,
  256,
  (const uint32_t**)&paulMemc_box3[0],
  4,
  stBoxRts_PfriClient_20170310221254_3_LPDDR4_2133
};

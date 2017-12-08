/*******************************************************************************
 * Copyright (C) 2017 Broadcom.  The term "Broadcom" refers to Broadcom Limited and/or its subsidiaries.
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
 ******************************************************************************/

#include "bchp.h"
const uint32_t BDSP_IMG_adpcm_decode_array1[] = {
	0x8ea873cf,
	0x96ac75cf,
	0xba1cc457,
	0x46018117,
	0xd804e570,
	0xba1cc047,
	0xba1ccc77,
	0xe03a17cb,
	0xba1cc867,
	0xba1cd087,
	0xba1cd497,
	0xba1cd8a7,
	0xa75e89d7,
	0x001dfab3,
	0x07a47f03,
	0x013fffff,
	0xa03fff27,
	0x3083480b,
	0xe01bfffb,
	0xa7388dd7,
	0x001dfab5,
	0x461ffe17,
	0x3d88412f,
	0x2b807e07,
	0x00102af0,
	0x2bd47e0f,
	0x00302b14,
	0xa77509d7,
	0x001dfab6,
	0x94004507,
	0x94044307,
	0x94024f07,
	0x94064707,
	0x3d907207,
	0x2a817e0f,
	0xfe2646d3,
	0x945c7f0f,
	0x07b07f0f,
	0xa73589d7,
	0x001dfab1,
	0x74000107,
	0x461ffe27,
	0xfe072e8b,
	0xfe37879b,
	0xd8381c02,
	0xc6abf643,
	0x07bffe07,
	0x3fdc454f,
	0xa72b8dd7,
	0x001dfab1,
	0x6520010f,
	0x461ffe37,
	0x461fc217,
	0x07bffe2f,
	0xdc001160,
	0xdc381362,
	0xd95815a0,
	0xd84015c0,
	0x3fae4563,
	0xc6abff53,
	0x07bffe03,
	0xa72889d7,
	0x001dfab1,
	0x74020107,
	0x2b2e7e1f,
	0x461ffe27,
	0x07bffe37,
	0xfe07168b,
	0xc6ac0d4b,
	0x07bffe03,
	0xa7260dd7,
	0x001dfab1,
	0x74000107,
	0x07b37e0f,
	0x2b047e13,
	0xc6abfb63,
	0x74000107,
	0x2b017e17,
	0x07b4fe0b,
	0xc6abfc7b,
	0x07b4fe07,
	0x3d88440f,
	0xc6ac0a5b,
	0x07b67e07,
	0x3d9e440f,
	0xc6ac0a43,
	0x75248103,
	0x15088043,
	0xb61f01f8,
	0xd8a40088,
	0xb62001f8,
	0x946c4107,
	0x0000009b,
	0xd8185f20,
	0xa75f0dd3,
	0x07a47f43,
	0x74040107,
	0x740e0307,
	0xd8681c20,
	0x25015017,
	0x941c7f07,
	0xd9981162,
	0x74000007,
	0x3d8c7357,
	0x94120707,
	0x3d88735f,
	0x2b00ff6b,
	0xc6ac1bb3,
	0x74040107,
	0x461ffe27,
	0xff86c788,
	0xf411fed3,
	0x941e1103,
	0xc6ac0ad3,
	0x07bffe03,
	0xa71b09d7,
	0x001dfab1,
	0x74040d07,
	0x74000707,
	0x940a7fcf,
	0x940e7fcf,
	0xe2115713,
	0x940851cf,
	0x940c45cf,
	0x46158c03,
	0x94205037,
	0x94384437,
	0x94027e37,
	0x94227e37,
	0x943a7e33,
	0xc6abf2eb,
	0x74040107,
	0x74000707,
	0xf4055e8b,
	0x2b02fe23,
	0xc6abf2c3,
	0x74000707,
	0x74040107,
	0xf4055e8b,
	0x2b047e27,
	0x94087fcf,
	0xc6abf293,
	0x7404171f,
	0x74080b3f,
	0x74421507,
	0x00000003,
	0x46117e17,
	0x4610cc07,
	0xfe07ffa3,
	0x947e1707,
	0x15008b87,
	0x944e1507,
	0x03e2fe60,
	0x946a1507,
	0x946e1907,
	0x07bffe2f,
	0x94607f07,
	0x942a5107,
	0x944c7d07,
	0x94507d07,
	0x94525b07,
	0xc6ac0113,
	0x07bffe03,
	0xa70f09d7,
	0x001dfab1,
	0x4610d207,
	0x3f96441f,
	0xfe47ff13,
	0x07bffe33,
	0xc6ac00d3,
	0x07bffe03,
	0xa70d09d7,
	0x001dfab1,
	0x753b0f07,
	0x7404111f,
	0x2b10fe4f,
	0x4610d807,
	0x94521307,
	0x3f96441f,
	0xfe07ff93,
	0x944e0f07,
	0x461ffe27,
	0x946a0f07,
	0x947e1107,
	0xc6ac005b,
	0x07bffe03,
	0xa7090dd7,
	0x001dfab1,
	0x74000107,
	0x07b2fe0f,
	0xf811fed3,
	0x461ffe27,
	0x07bffe37,
	0x94085b03,
	0xc6abf2ab,
	0x07bffe03,
	0xa7068dd7,
	0x001dfab1,
	0x07b07e03,
	0xa76b8dd7,
	0x001dfab3,
	0xf219fffb,
	0x760475cf,
	0x540441cf,
	0x07bffe43,
	0x540545cf,
	0x540649cf,
	0x54074dcf,
	0x540851cf,
	0x540955cf,
	0x540a59cf,
	0xa9fd0fff,
	0x3dd873cf,
	0x94484107,
	0x0000009c,
	0xd8185f20,
	0xc6001e0b,
	0xb6e10dff,
	0x07a47f47,
	0x94484107,
	0x0000009c,
	0xd8185f20,
	0xc600326b,
	0xb6df8dff,
	0x07a47f47,
	0x72030e0f,
	0x72040a0f,
	0x72000c0f,
	0x7201080f,
	0x07a0fe1f,
	0x0eff840f,
	0x158404c7,
	0x1584050f,
	0x07a0fe13,
	0x40a30e37,
	0x40a20a27,
	0x3f880211,
	0x07a17e08,
	0x3d86020f,
	0x74050a1f,
	0x2100820b,
	0x7a020c1f,
	0x08430827,
	0x08408007,
	0x23040827,
	0x40430413,
	0x08420413,
	0x117f8407,
	0x00ffff7f,
	0x5d000414,
	0x00ffff80,
	0x117f8587,
	0x0000007f,
	0x5d7f8414,
	0x0000007f,
	0x8b01042b,
	0x72020203,
	0x7203081f,
	0x7202001f,
	0x94050a1f,
	0x9203041f,
	0x9204081f,
	0x40a00207,
	0x013fffff,
	0x23040007,
	0x013fffff,
	0x10878187,
	0x9202001f,
	0x2a887e00,
	0xa9fd0fff,
	0x92020018,
	0x8ed473cf,
	0x96d875cf,
	0x962851cf,
	0x2480841f,
	0xba1cc017,
	0xba1cc427,
	0x4f7f8617,
	0x07a07f1f,
	0xba1ccc47,
	0xba1cc837,
	0x07a0ff33,
	0x72074e07,
	0x3d860407,
	0x013fffff,
	0x2100810f,
	0x013fffff,
	0x0850c70f,
	0x14814e43,
	0xa0bf8f38,
	0x1b3fce43,
	0xb61f05f8,
	0x7203170f,
	0x3f870337,
	0x3dea4747,
	0x0000002f,
	0x3d82502f,
	0x3d8a4307,
	0xde6afd40,
	0x24841653,
	0x1083158f,
	0x28ff964f,
	0x5c831445,
	0x10831387,
	0x0eff9037,
	0x5c831238,
	0xd9a23ee2,
	0x8321011f,
	0x0eff8f27,
	0x3d82041b,
	0xdeb23ee1,
	0x2100860b,
	0xd8ac7ce3,
	0x8332bd1f,
	0x0840c6ef,
	0xdab23f02,
	0x2100c4fb,
	0x084fc6db,
	0x92553d1f,
	0x0000008f,
	0x720338eb,
	0x924f391f,
	0x0000008f,
	0x720334db,
	0x9256351f,
	0x0000008f,
	0x7204330b,
	0x208432c3,
	0x248432bb,
	0x07abb0b3,
	0x92502d1f,
	0x0000008f,
	0x72052b0b,
	0x20842aa3,
	0x24842a9b,
	0x07a9a893,
	0x9257251f,
	0x0000008f,
	0x7206230b,
	0x2084227b,
	0x24842283,
	0x07a81e3b,
	0x92510f1f,
	0x0000008f,
	0x72071d0b,
	0x20841c63,
	0x24841c6b,
	0x07a69803,
	0xd8ac7d83,
	0x7208170b,
	0x2084164b,
	0x24841653,
	0x07a51243,
	0xd8747d23,
	0x72090d0b,
	0xd8717ea3,
	0x926b0f1f,
	0x0000002f,
	0xda0c7d33,
	0x20840c1b,
	0x24840c13,
	0x07a1060b,
	0xd9547d93,
	0xd952fd23,
	0xd8aafd33,
	0xd9cc7da3,
	0x0effcf3f,
	0x2500cd37,
	0x2101ce17,
	0x1a3fcc07,
	0x0a53840f,
	0x07bfff17,
	0x21008203,
	0x3ddc470f,
	0x0000008f,
	0x3f8e432f,
	0x08404727,
	0xdeb47ce0,
	0xb40501f8,
	0x72000d07,
	0x4612c207,
	0x3d00c513,
	0x24860c13,
	0xa7d80dd3,
	0x78008b07,
	0x46124207,
	0x28878a13,
	0xa7d70dd3,
	0x72000907,
	0x4612c207,
	0x2282081b,
	0x28878613,
	0xa7d609d3,
	0x63010507,
	0x46124207,
	0x28878413,
	0xa7d509d3,
	0x1a314c03,
	0xb6fb09f8,
	0x2100ce27,
	0x760475cf,
	0x08538817,
	0x540141cf,
	0x2104041b,
	0x943a511f,
	0x0000008f,
	0x0a41060f,
	0x540349cf,
	0x21020203,
	0x0840513f,
	0x762851cf,
	0x943c4f1f,
	0x0000008f,
	0x540245cf,
	0x54044dcf,
	0xa9fd0fff,
	0x3dac73cf,
	0x7203010f,
	0x3d874307,
	0x3ddc4717,
	0x0000008f,
	0x3dea4747,
	0x0000002f,
	0x3d82504f,
	0x3f8e4527,
	0x2484000f,
	0x3f844d37,
	0x10830387,
	0x28ff8087,
	0x5c8302cc,
	0x07b17e07,
	0x0effb2c7,
	0x07b27e0f,
	0x3dee30bf,
	0x00000047,
	0x832ba91b,
	0x3d822eb3,
	0x2100acab,
	0x084ac69b,
	0x924e291f,
	0x0000008f,
	0x7203249b,
	0x924f251f,
	0x0000008f,
	0x7204230b,
	0x2dffa27b,
	0x07a7a073,
	0x92501d1f,
	0x0000008f,
	0x72051b0f,
	0x7004190f,
	0x2dff9a5b,
	0x07a61653,
	0x9251151f,
	0x0000008f,
	0x7206110f,
	0x70050f0f,
	0x926b151f,
	0x0000002f,
	0x9453131f,
	0x0000008f,
	0x2dff9033,
	0x07a38c2b,
	0x92520b1f,
	0x0000008f,
	0x926a0b1f,
	0x0000002f,
	0x7206090b,
	0x2282081b,
	0x28878613,
	0xa7c289d3,
	0x7206050f,
	0x46124407,
	0x28878413,
	0xa7c189d3,
	0xb6e489fb,
	0x8e9c73cf,
	0x96a075cf,
	0x966065cf,
	0x2a82fe0f,
	0xba1cc447,
	0xba1cc037,
	0xe0380613,
	0x747a4207,
	0x0000008f,
	0xba1cc857,
	0xba1ccc67,
	0x2a817e03,
	0xba1cd077,
	0xba1cd487,
	0xba1cd897,
	0xba1cdca7,
	0xba1ce0b3,
	0x8b6a0317,
	0x0000002f,
	0x07b17e0f,
	0x92010107,
	0xd8003fa0,
	0x8d027e0b,
	0xe02a0830,
	0xb6ff0dfa,
	0x74020f0b,
	0xdba47ba0,
	0xdba47bc0,
	0xdba47be0,
	0x740e5c3b,
	0xdba47c00,
	0xdba47c20,
	0xdba47c40,
	0xdba47c60,
	0xdba47c80,
	0xdba47ca0,
	0xdba47cc0,
	0x1b5f5c43,
	0xb60085f8,
	0x11005c87,
	0x00000001,
	0xb41c81f8,
	0x2b00ff7f,
	0x3000ff1f,
	0x7408003b,
	0x15008043,
	0xb61e05f8,
	0x461ffe27,
	0x07a3fe07,
	0xfe37e79b,
	0xd81c7dc1,
	0x07bffe17,
	0x3d887327,
	0xc6abec3b,
	0x07bffe07,
	0x3d824187,
	0xa7328dd7,
	0x001dfab0,
	0x74001f0f,
	0x07b27e0f,
	0x760c1c7b,
	0x76101a7f,
	0x740a047f,
	0x7414187f,
	0x3d8c1e07,
	0x96081dcb,
	0x960c1bcb,
	0x941019cb,
	0xc6abef93,
	0x7524170f,
	0x7400150f,
	0xd8800861,
	0x30047e4f,
	0x2b0d7e3f,
	0xda300821,
	0x15009787,
	0x740a0257,
	0x5d001234,
	0x0000000c,
	0x1a428d0f,
	0x03ff8e20,
	0x03e28d1d,
	0x08426017,
	0xf201fe1b,
	0x461fc627,
	0x461ffe37,
	0x940c11cb,
	0xc6abdb83,
	0x07bffe03,
	0xa72a89d7,
	0x001dfab0,
	0x720e0707,
	0x7524030f,
	0x20840617,
	0x15008387,
	0x24840603,
	0xb45c81fc,
	0x07a00417,
	0x740e070f,
	0x7410090f,
	0x07b1fe2b,
	0x94080707,
	0x92070907,
	0x4f7f840f,
	0x07b07e07,
	0xd96c8020,
	0x0a408a0b,
	0xdbec8010,
	0xa7b189d3,
	0xd8247d30,
	0x7404070f,
	0x7416050f,
	0xd8148010,
	0x0a510363,
	0x2300d967,
	0x3d808417,
	0x940a590f,
	0x9400461f,
	0x1a3f8187,
	0x9416050f,
	0xb62005fc,
	0x07b67f77,
	0x083f007f,
	0x085f5877,
	0x4f7f9e6f,
	0x083f5867,
	0x21009a17,
	0x21011c27,
	0x0846845f,
	0x4f7f9857,
	0x21041617,
	0x08424427,
	0x0a45844f,
	0x21011447,
	0x2101122f,
	0x0a44081f,
	0x0842d83f,
	0x3f82061f,
	0xdc1afd02,
	0xf0a81743,
	0x08400c37,
	0x1a3fd98f,
	0xb60181f9,
	0x07a27e03,
	0x6aff040b,
	0x21080413,
	0x8dfe0403,
	0x1b418183,
	0xb6fe8df8,
	0xdd017e80,
	0x1b430847,
	0x3d870a2f,
	0xd8c17e83,
	0xb61805f8,
	0xdd5c7d31,
	0xb6fc89fb,
	0x11405d03,
	0xb64b01f8,
	0x2500dd1f,
	0x3000fe07,
	0x07b1fe0b,
	0xa75c0cff,
	0x0019faa4,
	0x07a47f7f,
	0x7408003f,
	0x013fffff,
	0x15008047,
	0xb4e185f8,
	0x7418050f,
	0x7404030f,
	0x9538ff0f,
	0x1b5f5d87,
	0xd8301da1,
	0x3d808407,
	0x94007e0f,
	0xb45381fc,
	0x9418010f,
	0xd8105f11,
	0x1b3f8043,
	0xb45005f8,
	0x7538010f,
	0x21015d37,
	0x1a3f8183,
	0xb64281f8,
	0x0a51fe17,
	0x1b5fdc47,
	0x2101040f,
	0x21015d37,
	0xded03ee1,
	0x2b187f5f,
	0x3902038f,
	0x07bfff2f,
	0x0858db8f,
	0x39825b87,
	0xa09f8f90,
	0x83328107,
	0x2100cb67,
	0x1a3f8183,
	0xb63805f8,
	0x0852d827,
	0x21014b4f,
	0x2101881f,
	0x0852d34f,
	0x0a52860f,
	0x21015217,
	0x21010207,
	0x0841413f,
	0x3de40157,
	0x00000002,
	0xffcf5f03,
	0x3dba4f3f,
	0x0000008f,
	0xb60509ff,
	0x08554357,
	0x0852522f,
	0x46125407,
	0xdd491ee0,
	0x2101081f,
	0x461ffe37,
	0x0841c017,
	0x461fcc27,
	0x74020417,
	0x07bffe1f,
	0x39025147,
	0x3d824f3f,
	0xc6abf393,
	0x07bffe03,
	0xa70809d7,
	0x001dfab0,
	0x83328307,
	0x3d00c807,
	0x3d80c923,
	0x1a200203,
	0xb42f81f8,
	0xd8105f11,
	0x1b3f8183,
	0xb4fa05f8,
	0x7400010f,
	0x07b47e17,
	0x461ffe27,
	0x07b6fe0f,
	0xff66279b,
	0xc6abe13b,
	0x07bffe03,
	0xa7038dd7,
	0x001dfab0,
	0x7400053f,
	0x46186207,
	0xf6071f1b,
	0xa74609d3,
	0xb6f68dfb,
	0xd8105f01,
	0x2a80fe0b,
	0xd9505f11,
	0x1b3f8043,
	0xb43a81f8,
	0x7538010f,
	0x21015937,
	0x1a3f8183,
	0xb61b05f8,
	0x1a3fd987,
	0x07b67f97,
	0xa09f8e3c,
	0x1b5fd847,
	0x3dee424f,
	0x00000003,
	0x941413cf,
	0xa09f8e00,
	0x90168fcf,
	0x901601cf,
	0x21015937,
	0x07b0ff6f,
	0x2b187f7f,
	0x07bfff2f,
	0x3980d95f,
	0x2b407f4f,
	0x83328107,
	0x2100cb8f,
	0x1a3f8183,
	0xb60f81f8,
	0x0852e267,
	0x21014b47,
	0x2101985f,
	0x0852d147,
	0x0a52964f,
	0x21015057,
	0x21011207,
	0x0845413f,
	0x3de40157,
	0x00000002,
	0xfe3f7ee3,
	0x3dba4f3f,
	0x0000008f,
	0xb6080dff,
	0x08554357,
	0x0851d01b,
	0xd8c11ee2,
	0xd600440a,
	0x74020203,
	0x7400010f,
	0x07b27e17,
	0x461ffe27,
	0x0855820f,
	0xff66279b,
	0x39024927,
	0x3d824f3f,
	0xc6abe04b,
	0x07bffe03,
	0xa7738dd7,
	0x001dfaaf,
	0x0851d02f,
	0x4611d407,
	0xdd491ee0,
	0x2101081f,
	0x461ffe37,
	0x0841c017,
	0x461fcc27,
	0x74020417,
	0x07bffe1f,
	0xc6abf0a3,
	0x07bffe03,
	0xa77089d7,
	0x001dfaaf,
	0x83328307,
	0x3d00c607,
	0x3d80c71b,
	0x1a200203,
	0xb40381f8,
	0xd8105f01,
	0x1b3f8183,
	0x74000138,
	0x741403cc,
	0x3000fe18,
	0x07a07e10,
	0xa72d05d0,
	0x1080c783,
	0xb4f589f8,
	0x7538816b,
	0x1b5f8183,
	0xb60e05f8,
	0xb6f50dff,
	0x7400033f,
	0xd7981988,
	0xb60101f8,
	0x46115803,
	0x8d027e0b,
	0xe02a0830,
	0xb6ff0dfa,
	0x0852e217,
	0x2b07fe0f,
	0xf0541e9a,
	0x0a528627,
	0x07bffe1f,
	0xf2ac1730,
	0xdda01641,
	0x0842c207,
	0x461ffe37,
	0x07bffe2f,
	0x3d965b6f,
	0xc6abef63,
	0x07bffe07,
	0x390a5f7f,
	0xa7660dd7,
	0x001dfaaf,
	0x7538010f,
	0x3d00ca0f,
	0x3d80cb2b,
	0x1a208183,
	0xb4e885f8,
	0xd8105f01,
	0x1b3f8043,
	0xb60005f8,
	0xd8585f01,
	0x7414090f,
	0x2b017e1f,
	0xd84c8020,
	0xdb5c8010,
	0xd8081c21,
	0xe4713443,
	0x540959cf,
	0x540b61cf,
	0x08570973,
	0x94145d0f,
	0x940c070f,
	0x940e050f,
	0x9410030f,
	0x9412010f,
	0x766065cf,
	0x540341cf,
	0x540445cf,
	0x540549cf,
	0x54064dcf,
	0x540751cf,
	0x540855cf,
	0x540a5dcf,
	0x3de473cf,
	0xa9fd0ffb,
	0x0851d027,
	0x701681cf,
	0xd9011ee3,
	0xd6008433,
	0x7402040f,
	0xa1000fc7,
	0x7446096f,
	0x00000003,
	0xb60301f8,
	0x083f641f,
	0x1a3fe587,
	0x4f7f860b,
	0xf9b00e41,
	0x5f008000,
	0xa8017403,
	0x65020c13,
	0x40c20c33,
	0x238f8c33,
	0x6d748c03,
	0x579ff81b,
	0x8d02060b,
	0x0851d027,
	0x07b87e0f,
	0xd9011ee3,
	0xd6008413,
	0xb6e08dff,
	0x94026007,
	0xa1190fc3,
	0xb60101f8,
	0x46115c03,
	0x8d027e0b,
	0xe02a0830,
	0xb6ff0dfa,
	0x0852d817,
	0x2b07fe0f,
	0xf0541e9a,
	0x0a528627,
	0x07bffe1f,
	0xf2ac1730,
	0xdda01641,
	0x0842c207,
	0x461ffe37,
	0x07bffe2f,
	0x390a575f,
	0xc6abecd3,
	0x07bffe03,
	0xa75209d7,
	0x001dfaaf,
	0x7538010f,
	0x3d00ca0f,
	0x3d80cb2b,
	0x1a208183,
	0xb4c005f8,
	0xd8105f11,
	0x1b3f8183,
	0x2a80fe00,
	0x9270010c,
	0x0000000b,
	0x92717f0c,
	0x0000000b,
	0xb6ea8dfb,
	0x1b5fdd87,
	0x07bfff1f,
	0x3000fe04,
	0x2b00ff7f,
	0x07b77e0c,
	0x07b77f18,
	0xa71080fc,
	0x0019faa4,
	0xb69609ff,
	0x07a47f78,
	0x72081907,
	0x74041707,
	0x72071507,
	0x3f8d462f,
	0x2084183f,
	0x25081637,
	0x2484184f,
	0x2108160f,
	0x20841427,
	0x24841447,
	0x07a48e1f,
	0x07a08c07,
	0x4f7f861f,
	0x07a40827,
	0x94040107,
	0x92070907,
	0x10810987,
	0x94080707,
	0xb6a001f8,
	0xe04c1703,
	0xb69f0dff,
	0x92070107,
	0x7402010f,
	0x3000fe17,
	0xd8781ee1,
	0x3901841f,
	0x461ffe27,
	0x07bffe33,
	0xc6abde63,
	0x07bffe03,
	0xa7440dd7,
	0x001dfaaf,
	0xb6c28dfb,
	0xe3660e13,
	0xd8781ee1,
	0x3901841f,
	0x461ffe27,
	0x07bffe33,
	0xc6abde13,
	0x07bffe03,
	0xa7418dd7,
	0x001dfaaf,
	0xb6ad0dfb,
	0x7408010b,
	0xdfd83fa2,
	0x1b5f8183,
	0xb6ab0dff,
	0x740a5d08,
	0x1b5f8643,
	0xb60281f8,
	0xfe9ff733,
	0x21010c2b,
	0x0842820b,
	0xa801741b,
	0x84420e07,
	0x65fe0c0f,
	0x3d808823,
	0x6d630e03,
	0x580ff82b,
	0x8d020a13,
	0xa9fd0fff,
	0x07bffe47,
	0x1b5f8643,
	0xb60285f8,
	0x085f0637,
	0x21010827,
	0x21010c2b,
	0x08428003,
	0xa801741b,
	0x74000c0f,
	0x65fe0e07,
	0x0842020b,
	0x6d630e03,
	0x580ff82b,
	0x8d020a13,
	0xa9fd0fff,
	0x07bffe47,
	0x4f7f8417,
	0x7201060f,
	0x2903843b,
	0x83238a03,
	0x013fffff,
	0x0eff8637,
	0x013fffff,
	0x3d840c27,
	0x0822861f,
	0x87220807,
	0x9201060b,
	0x10ac0783,
	0xb60705f8,
	0x2aac7e03,
	0x9201000b,
	0x23018837,
	0x15820507,
	0x7402000b,
	0x15810507,
	0x08420c30,
	0x23008818,
	0x08418c34,
	0x15808507,
	0x013fffff,
	0x23010820,
	0x7a00080f,
	0x08420c30,
	0x15840503,
	0x08420c2b,
	0x0a430828,
	0x117f8a07,
	0x00ffff7f,
	0x5d000a14,
	0x00ffff80,
	0x117f8587,
	0x0000007f,
	0x5d7f841c,
	0x0000007f,
	0x8b010603,
	0x9402000f,
	0x9200060f,
	0xa9fd0ffb,
	0x1a21fe03,
	0xb6f889ff,
	0x92017e08,
	0x8ecc73cf,
	0x96d075cf,
	0x963055cf,
	0x2480842f,
	0xba1cc427,
	0xba1ccc47,
	0x07a07f3f,
	0x4f7f8a27,
	0xba1cd057,
	0xba1cc017,
	0x3d86081b,
	0x21008617,
	0xba1cc837,
	0x08414f1b,
	0x3d83471f,
	0x72070007,
	0x3df44f57,
	0x0000002f,
	0x013fffff,
	0x1481004f,
	0x1a3f8187,
	0xa0bf8f49,
	0xb60801f8,
	0xfe473e83,
	0x2aac7e3b,
	0x3df44f57,
	0x0000002f,
	0x7200171f,
	0x08415467,
	0x013fffff,
	0x3d811837,
	0x2084164b,
	0x24841653,
	0x07a51243,
	0x926c1007,
	0x0000008f,
	0x70018b1f,
	0x3d82471f,
	0x926d0a07,
	0x0000008f,
	0x9d151013,
	0xda047ed0,
	0xdb8c7ee0,
	0x10ac0983,
	0x1a227e0b,
	0xb60f85f8,
	0x926d0e07,
	0x0000008f,
	0x7207093f,
	0x3d00861f,
	0x3f82020f,
	0x3d840007,
	0xd8897f22,
	0x1a218803,
	0xb6f901f8,
	0x25010347,
	0x07bfff37,
	0x1a3fd187,
	0x07bfff27,
	0x3df44f17,
	0x0000008f,
	0xb40089f8,
	0xb60789fb,
	0x07f4cd33,
	0x0effcc0f,
	0x3d82472f,
	0xd8b08fd8,
	0x2101810f,
	0x07b1ff07,
	0x0850cf0b,
	0x78008d07,
	0x4610c407,
	0x28878c13,
	0xa7e20dd3,
	0x72000b07,
	0x4610c407,
	0x24860a13,
	0xa7e10dd3,
	0x72000907,
	0x4610c407,
	0x28878813,
	0xa7e00dd3,
	0x63010707,
	0x4610c407,
	0x22820613,
	0x28878413,
	0xa7df09d3,
	0x1b52c183,
	0xb6fb05f8,
	0x3d00c927,
	0x3d82471f,
	0x1a325183,
	0xb4f889f8,
	0xd8517f22,
	0x9458553f,
	0x0000008f,
	0x760475cf,
	0x540141cf,
	0x40a15213,
	0x540245cf,
	0x540349cf,
	0x540551cb,
	0x08550553,
	0x945a553f,
	0x0000008f,
	0x763055cf,
	0x54044dcf,
	0xa9fd0fff,
	0x3db473cf,
	0x926d7e05,
	0x0000008f,
	0xb6f009fb,
	0x8e9c73cf,
	0x96a075cf,
	0x966065cf,
	0x2a82fe0f,
	0xba1cc447,
	0xba1cc037,
	0xe0380613,
	0x74564207,
	0x00000090,
	0xba1cc857,
	0xba1ccc67,
	0x2a817e03,
	0xba1cd077,
	0xba1cd487,
	0xba1cd897,
	0xba1cdca7,
	0xba1ce0b3,
	0x8b740317,
	0x0000002f,
	0x07b17e0f,
	0x92010107,
	0xd8003fc8,
	0x8d027e0b,
	0xe02a0830,
	0xb6ff0dfa,
	0x74020f0b,
	0xdba47d80,
	0xdba47da0,
	0xdba47dc0,
	0x740e5c3b,
	0xdba47de0,
	0xdba47e00,
	0xdba47e20,
	0xdba47e40,
	0xdba47e60,
	0xdba47e80,
	0xdba47ea0,
	0x1b5f5c43,
	0xb60085f8,
	0x11005c87,
	0x00000001,
	0xb41d05f8,
	0x2b00ff7f,
	0x3000ff1f,
	0x7408003b,
	0x15008043,
	0xb61f01f8,
	0x461ffe27,
	0x07a3fe07,
	0x2b627e1f,
	0x07bffe37,
	0xd81c7f41,
	0x2b1e7e17,
	0x3d887327,
	0xc6abd643,
	0x07bffe07,
	0x3d824187,
	0xa70309d7,
	0x001dfaaf,
	0x74001f0f,
	0x07b27e0f,
	0x760c1c7b,
	0x76101a7f,
	0x740a047f,
	0x7414187f,
	0x3d8c1e07,
	0x96081dcb,
	0x960c1bcb,
	0x941019cb,
	0xc6abd99b,
	0x7524170f,
	0x7400150f,
	0xd8800861,
	0x30047e4f,
	0x2b0d7e3f,
	0xda300821,
	0x15009787,
	0x740a0257,
	0x5d001234,
	0x0000000c,
	0x1a428d0f,
	0x03ff8e20,
	0x03e28d1d,
	0x08426017,
	0xf201fe1b,
	0x461fc627,
	0x461ffe37,
	0x940c11cb,
	0xc6abc58b,
	0x07bffe03,
	0xa77a8dd7,
	0x001dfaae,
	0x720e0707,
	0x7524030f,
	0x20840617,
	0x15008387,
	0x24840603,
	0xb45c05fc,
	0x07a00417,
	0x740e070f,
	0x7410090f,
	0x07b1fe2b,
	0x94080707,
	0x92070907,
	0x4f7f840f,
	0x07b07e07,
	0xd96c85e0,
	0x0a408a0b,
	0xdbec85d0,
	0xa7c889d3,
	0xd8247ee0,
	0x7404070f,
	0x7416050f,
	0xd81485d0,
	0x0a510363,
	0x2300d967,
	0x3d808417,
	0x940a590f,
	0x9400461f,
	0x1a3f8187,
	0x9416050f,
	0xb62081fc,
	0x07b67f77,
	0x083f0087,
	0x085f587f,
	0x4f7fa02f,
	0x083f586f,
	0x21008a77,
	0x21011e27,
	0x08429c67,
	0x4f7f9a57,
	0x2103985f,
	0x08424427,
	0x0a429617,
	0x2101144f,
	0x21018417,
	0x0a44881f,
	0x08428447,
	0x3f82061f,
	0x0844583f,
	0x07b07e2f,
	0xdc1afe42,
	0x21010e07,
	0x1a3fd98f,
	0x08400c33,
	0xb60181f9,
	0x07a27e03,
	0x6aff040b,
	0x21080413,
	0x8dfe0403,
	0x1b418183,
	0xb6fe8df8,
	0xdd017f20,
	0x1b430847,
	0x3d840a2f,
	0xd8c17f23,
	0xb61801f8,
	0xdd5c7ee1,
	0xb6fc89fb,
	0x11405d03,
	0xb64a05f8,
	0x2500dd1f,
	0x3000fe07,
	0x07b1fe0b,
	0xa72c08ff,
	0x0019faa3,
	0x07a47f7f,
	0x7408003f,
	0x013fffff,
	0x15008047,
	0xb4e101f8,
	0x7418050f,
	0x7404030f,
	0x9538ff0f,
	0x1b5f5d87,
	0xd8301da1,
	0x3d808407,
	0x94007e0f,
	0xb45285fc,
	0x9418010f,
	0xd8105f11,
	0x1b3f8043,
	0xb44f81f8,
	0x7538010f,
	0x21015d37,
	0x1a3f8183,
	0xb64185f8,
	0x0a51fe17,
	0x1b5fdc47,
	0x2101040f,
	0x21015d37,
	0xded03ee1,
	0x2b187f5f,
	0x3902038f,
	0x07bfff2f,
	0x0858db8f,
	0x39825b87,
	0xa09f8f90,
	0x83328107,
	0x2100cb67,
	0x1a3f8183,
	0xb63781f8,
	0x0852d827,
	0x21014b4f,
	0x2101881f,
	0x0852d34f,
	0x0a528617,
	0x2101520f,
	0x21010407,
	0x07b5ff47,
	0x3dd8033f,
	0x0000008f,
	0x3de40157,
	0x00000002,
	0x07bfff27,
	0x0853c13f,
	0xb60489ff,
	0x08554357,
	0x0852521f,
	0x46125407,
	0xd8c11f62,
	0x84410507,
	0x07bffe1f,
	0x461fcc27,
	0x461ffe37,
	0x39025147,
	0x3d824f3f,
	0xc6abdd93,
	0x07bffe03,
	0xa75809d7,
	0x001dfaae,
	0x83328307,
	0x3d00c807,
	0x3d80c923,
	0x1a200203,
	0xb42f01f8,
	0xd8105f11,
	0x1b3f8183,
	0xb4fa85f8,
	0x7400010f,
	0x07b47e17,
	0x461ffe27,
	0x07b6fe0f,
	0xff66279b,
	0xc6abcb3b,
	0x07bffe03,
	0xa7538dd7,
	0x001dfaae,
	0x7400053f,
	0x46186207,
	0xf6071f1b,
	0xa79609d3,
	0xb6f70dfb,
	0xd8105f01,
	0x2a80fe0b,
	0xd9505f11,
	0x1b3f8043,
	0xb43a01f8,
	0x7538010f,
	0x21015937,
	0x1a3f8183,
	0xb61b01f8,
	0x1a3fd987,
	0x07b67f97,
	0xa09f8e3c,
	0x1b5fd847,
	0x3dee424f,
	0x00000003,
	0x941413cf,
	0xa09f8e00,
	0x90168fcf,
	0x901601cf,
	0x21015937,
	0x07b0ff6f,
	0x2b187f7f,
	0x07bfff2f,
	0x3980d95f,
	0x2b407f4f,
	0x83328107,
	0x2100cb8f,
	0x1a3f8183,
	0xb60f05f8,
	0x0852e267,
	0x21014b47,
	0x2101985f,
	0x0852d147,
	0x0a529657,
	0x2101504f,
	0x21011407,
	0x07b7ff27,
	0x3dd8133f,
	0x0000008f,
	0x3de40157,
	0x00000002,
	0x07bfff1f,
	0x0853c13f,
	0xb6078dff,
	0x08554357,
	0x0851d00b,
	0xd8b11f60,
	0x84400303,
	0x7400010f,
	0x07b27e17,
	0x0855820f,
	0x30027e1f,
	0x461ffe27,
	0x07bffe37,
	0x39024927,
	0x3d824f3f,
	0xc6abca43,
	0x07bffe03,
	0xa74389d7,
	0x001dfaae,
	0x0851d01f,
	0x4611d407,
	0xd8c11f62,
	0x84410507,
	0x07bffe1f,
	0x461fcc27,
	0x461ffe37,
	0xc6abdaab,
	0x07bffe03,
	0xa7408dd7,
	0x001dfaae,
	0x83328307,
	0x3d00c607,
	0x3d80c71b,
	0x1a200203,
	0xb40381f8,
	0xd8105f01,
	0x1b3f8183,
	0x74000138,
	0x741403cc,
	0x3000fe18,
	0x07a07e10,
	0xc4ffefb0,
	0x1080c783,
	0xb4f609f8,
	0x7538816b,
	0x1b5f8183,
	0xb60e05f8,
	0xb6f589ff,
	0x7400033f,
	0xd7981988,
	0xb60101f8,
	0x46115803,
	0x8d027e0b,
	0xe02a0830,
	0xb6ff0dfa,
	0x0852e217,
	0x2b07fe0f,
	0xf0541e9a,
	0x0a528627,
	0x07bffe1f,
	0xf2ac1730,
	0xdda01641,
	0x0842c207,
	0x461ffe37,
	0x07bffe2f,
	0x3d965b6f,
	0xc6abd96b,
	0x07bffe07,
	0x390a5f7f,
	0xa73689d7,
	0x001dfaae,
	0x7538010f,
	0x3d00ca0f,
	0x3d80cb2b,
	0x1a208183,
	0xb4e901f8,
	0xd8105f01,
	0x1b3f8043,
	0xb60005f8,
	0xd8585f01,
	0x7414090f,
	0x2b08fe1f,
	0xd84c85e0,
	0xdb5c85d0,
	0xd8081c21,
	0xe4713443,
	0x540959cf,
	0x540b61cf,
	0x08570973,
	0x94145d0f,
	0x940c070f,
	0x940e050f,
	0x9410030f,
	0x9412010f,
	0x766065cf,
	0x540341cf,
	0x540445cf,
	0x540549cf,
	0x54064dcf,
	0x540751cf,
	0x540855cf,
	0x540a5dcf,
	0x3de473cf,
	0xa9fd0ffb,
	0x0851d017,
	0x701681cf,
	0xd8891f61,
	0x84408503,
	0x7446096f,
	0x00000003,
	0x013fffff,
	0xa1000fc7,
	0xb60301f8,
	0x083f641f,
	0x1a3fe587,
	0x4f7f860b,
	0xf9b00e41,
	0x5f008000,
	0xa8017403,
	0x65020c13,
	0x40c20c33,
	0x238f8c33,
	0x6d748c03,
	0x579ff81b,
	0x8d02060b,
	0x0851d017,
	0x07b87e0f,
	0xd8891f60,
	0xb6e10dff,
	0x9e406107,
	0xa1190fc3,
	0xb60101f8,
	0x46115c03,
	0x8d027e0b,
	0xe02a0830,
	0xb6ff0dfa,
	0x0852d817,
	0x2b07fe0f,
	0xf0541e9a,
	0x0a528627,
	0x07bffe1f,
	0xf2ac1730,
	0xdda01641,
	0x0842c207,
	0x461ffe37,
	0x07bffe2f,
	0x390a575f,
	0xc6abd6e3,
	0x07bffe03,
	0xa72289d7,
	0x001dfaae,
	0x7538010f,
	0x3d00ca0f,
	0x3d80cb2b,
	0x1a208183,
	0xb4c101f8,
	0xd8105f11,
	0x1b3f8183,
	0x2a80fe00,
	0x9270010c,
	0x0000000b,
	0x92717f0c,
	0x0000000b,
	0xb6eb09fb,
	0x1b5fdd87,
	0x07bfff1f,
	0x3000fe04,
	0x2b00ff7f,
	0x07b77e0c,
	0x07b77f18,
	0xa76100fc,
	0x0019faa2,
	0xb69609ff,
	0x07a47f78,
	0x72081907,
	0x74041707,
	0x72071507,
	0x3f8d462f,
	0x2084183f,
	0x25081637,
	0x2484184f,
	0x2108160f,
	0x20841427,
	0x24841447,
	0x07a48e1f,
	0x07a08c07,
	0x4f7f861f,
	0x07a40827,
	0x94040107,
	0x92070907,
	0x10810987,
	0x94080707,
	0xb6a005f8,
	0xe04c1703,
	0xb69f89ff,
	0x92070107,
	0x7402010f,
	0x3000fe17,
	0xd8781ee1,
	0x3901841f,
	0x461ffe27,
	0x07bffe33,
	0xc6abc873,
	0x07bffe03,
	0xa7148dd7,
	0x001dfaae,
	0xb6c30dfb,
	0xe3660e13,
	0xd8781ee1,
	0x3901841f,
	0x461ffe27,
	0x07bffe33,
	0xc6abc823,
	0x07bffe03,
	0xa7120dd7,
	0x001dfaae,
	0xb6ae09fb,
	0x7408010b,
	0xdfd83fca,
	0x1b5f8183,
	0xb6ac09ff,
	0x740a5d08,
	0x7201060f,
	0x2903843f,
	0x013fffff,
	0x83238a07,
	0x0eff8633,
	0x3d840c27,
	0x0822861f,
	0x87220807,
	0x10ac0787,
	0xb60781fc,
	0x9201060f,
	0x2aac7e03,
	0x9201000b,
	0x23018837,
	0x4f7f843f,
	0x7402000f,
	0x15820f07,
	0x15810f07,
	0x08420c30,
	0x23008818,
	0x08418c34,
	0x15808f07,
	0x013fffff,
	0x23010820,
	0x7a00080f,
	0x08420c30,
	0x15840f03,
	0x08420c2b,
	0x0a430828,
	0x117f8a07,
	0x00ffff7f,
	0x5d000a14,
	0x00ffff80,
	0x117f8587,
	0x0000007f,
	0x5d7f841c,
	0x0000007f,
	0x8b010603,
	0x9402000f,
	0x9200060f,
	0xa9fd0ffb,
	0x1a21fe03,
	0xb6f80dff,
	0x92017e08,
	0x2bf8fe17,
	0x00f0f0f0,
	0x41c10213,
	0x8ec473cf,
	0x96c875cf,
	0x963859cb,
	0xba1cc427,
	0xba1cd057,
	0x07bfff43,
	0xba1cd467,
	0xba1ccc47,
	0x07a07f3f,
	0x2aac7f57,
	0xba1cc017,
	0xba1cc837,
	0x2590054f,
	0x3d8f4f1f,
	0x2503534f,
	0x72070007,
	0x3df44f5f,
	0x0000002f,
	0xdbc2fe61,
	0x946e573f,
	0x0000008f,
	0xdc647f23,
	0x1b5fd247,
	0x07a07f67,
	0x3df44f17,
	0x0000008f,
	0xb60b05f8,
	0x1a3f8187,
	0x3d914727,
	0xfe3f3fab,
	0xb60981f8,
	0x72ef0b27,
	0x3f90491f,
	0x3dfdcc07,
	0x00000011,
	0x2101810b,
	0x0850cf0b,
	0x28bf8a23,
	0x0eff881f,
	0x2dbf8a0f,
	0xde647ed1,
	0x10ac0603,
	0xdd547ec1,
	0x926d552c,
	0x0000008f,
	0x6301411f,
	0x4610c407,
	0x2284401b,
	0x28878613,
	0xa7e78dd3,
	0x4610c407,
	0x24864017,
	0xa7e709d3,
	0x4610c407,
	0x2887c017,
	0xa7e60dd3,
	0x22824017,
	0x4610c407,
	0x28878413,
	0xa7e50dd3,
	0x1b524783,
	0xb6fb8df8,
	0x7207013f,
	0x3d00cc0f,
	0x3d914727,
	0x3d80cd37,
	0x3d844b2b,
	0x1a208003,
	0xb6f681f8,
	0x3d80d143,
	0x1a545383,
	0xb4f48df8,
	0x14815847,
	0x760475cf,
	0xa0bf8e1c,
	0x763859cf,
	0x21008647,
	0x540141cf,
	0x0841903b,
	0x21038e37,
	0x540245cf,
	0x0a418c2b,
	0x21018a27,
	0x540349cf,
	0x08418813,
	0x2101040f,
	0x540551cf,
	0x0840d603,
	0x9458573f,
	0x0000008f,
	0xdc2c7da3,
	0x540655cf,
	0x54044dcf,
	0xa9fd0fff,
	0x3dbc73cf,
	0x8e9c73cf,
	0x96a075cf,
	0x966065cf,
	0x2a82fe0f,
	0xba1cc447,
	0xba1cc037,
	0xe0380613,
	0x74564207,
	0x00000090,
	0xba1cc857,
	0xba1ccc67,
	0x2a817e03,
	0xba1cd077,
	0xba1cd487,
	0xba1cd897,
	0xba1cdca7,
	0xba1ce0b3,
	0x8b740317,
	0x0000002f,
	0x07b17e0f,
	0x92010107,
	0xd8007f90,
	0x8d027e0b,
	0xe02a0830,
	0xb6ff0dfa,
	0x74020f0b,
	0xdba47d80,
	0xdba47da0,
	0xdba47dc0,
	0x740e543b,
	0xdba47de0,
	0xdba47e00,
	0xdba47e20,
	0xdba47e40,
	0xdba47e60,
	0xdba47e80,
	0xdba47ea0,
	0x1b5f5443,
	0xb60085f8,
	0x11005487,
	0x00000001,
	0xb41c01f8,
	0x2b00ff87,
	0x3000ff1f,
	0x7408003b,
	0x15008043,
	0xb61d85f8,
	0x461ffe27,
	0x07a3fe07,
	0x2b627e1f,
	0x07bffe37,
	0xd81c7f41,
	0x2b1e7e17,
	0x3d887327,
	0xc6abc1b3,
	0x07bffe07,
	0x3d824187,
	0xa75e89d7,
	0x001dfaad,
	0x7400190f,
	0x07b27e0f,
	0x760c1663,
	0x76101467,
	0x740a0467,
	0x74141267,
	0x3d8c1807,
	0x960817cb,
	0x960c15cb,
	0x941013cb,
	0xc6abc50b,
	0x75240f0f,
	0x7400030f,
	0xd8b80861,
	0x30087e37,
	0x2b0d7e2f,
	0xda300821,
	0x15008f87,
	0x740a020f,
	0x5d000c1c,
	0x00000014,
	0x1a42070f,
	0x03ff8a10,
	0x03e2071d,
	0x07b27e07,
	0x08416017,
	0x07bffe1f,
	0x461fc627,
	0x461ffe37,
	0x940c11cb,
	0xc6abb0f3,
	0x07bffe03,
	0xa75609d7,
	0x001dfaad,
	0x7524010b,
	0x15008183,
	0xb45b81f8,
	0x740e010f,
	0x7410050f,
	0x07b1fe0b,
	0x94080107,
	0x92070507,
	0xd82c85e0,
	0xd9ec85d0,
	0x07b07e03,
	0xa7cd0dd3,
	0xd8247ee0,
	0x7404070f,
	0x7416050f,
	0xd81485d0,
	0x0a51036b,
	0x2300db6f,
	0x3d808417,
	0x940a5b0f,
	0x9400461f,
	0x1a3f8187,
	0x9416050f,
	0xb62505fc,
	0x07b6ff57,
	0x083f0087,
	0x085f5a7f,
	0x4f7fa02f,
	0x083f5a6f,
	0x21008a77,
	0x21011e27,
	0x08429c67,
	0x4f7f9a57,
	0x2103985f,
	0x08424427,
	0x0a429617,
	0x2101144f,
	0x21018417,
	0x0a44881f,
	0x08428447,
	0x3f82061f,
	0x08445a3f,
	0x07b07e2f,
	0xdc1afe42,
	0x21010e07,
	0x1a3fdb8f,
	0x08400c33,
	0xb60181f9,
	0x07a27e03,
	0x6aff040b,
	0x21080413,
	0x8dfe0403,
	0x1b418183,
	0xb6fe8df8,
	0xdd017f20,
	0x1b430847,
	0x3d840a2f,
	0xd8c17f23,
	0xb61c85f8,
	0xdd5c7ee1,
	0xb6fc89fb,
	0x11405503,
	0xb64a01f8,
	0x2500d51f,
	0x3000fe07,
	0x07b1fe0b,
	0xa7088cff,
	0x0019faa2,
	0x07a47f87,
	0x7408003f,
	0x013fffff,
	0x15008047,
	0xb4e205f8,
	0x7418050f,
	0x7404030f,
	0x9538ff0f,
	0x1b5f5587,
	0xd8301da1,
	0x3d808407,
	0x94007e0f,
	0xb45281fc,
	0x9418010f,
	0xd8105f11,
	0x1b3f8043,
	0xb44f05f8,
	0x7538010f,
	0x21015537,
	0x1a3f8183,
	0xb61305f8,
	0x0a51fe17,
	0x1b5fd447,
	0x2101040f,
	0x21015537,
	0xded03ee3,
	0x2b187f6f,
	0x39020397,
	0x07bfff2f,
	0x08595f97,
	0x39825f8f,
	0xa09f8f60,
	0x83328107,
	0x2100cb77,
	0x1a3f8183,
	0xb60a81f8,
	0x0852dc27,
	0x21014b4f,
	0x2101881f,
	0x0852d34f,
	0x0a528617,
	0x2101520f,
	0x21010407,
	0x07b6ff47,
	0x3dd8033f,
	0x0000008f,
	0x3de4015f,
	0x00000002,
	0x07bfff27,
	0x0853c13f,
	0x0855c35b,
	0xd8105f11,
	0x1b3f8183,
	0xb63785f8,
	0xa1160fc3,
	0xb60101f8,
	0x46115403,
	0x8d027e0b,
	0xe02a0830,
	0xb6ff0dfa,
	0x0852521f,
	0x46125607,
	0xd8c11f62,
	0x84410507,
	0x07bffe1f,
	0x461fcc27,
	0x461ffe37,
	0x39025147,
	0x3d824f3f,
	0xc6abc8eb,
	0x07bffe03,
	0xa7328dd7,
	0x001dfaad,
	0x83328307,
	0x3d00c807,
	0x3d80c923,
	0x1a200203,
	0xb6f90df8,
	0x0852dc17,
	0x2b07fe0f,
	0xf0541e9a,
	0x0a528627,
	0x07bffe1f,
	0xf2ac1730,
	0xdda01641,
	0x0842c207,
	0x461ffe37,
	0x07bffe2f,
	0x390a5b6f,
	0xc6abc84b,
	0x07bffe03,
	0xa72d8dd7,
	0x001dfaad,
	0x7538010f,
	0x3d00ca0f,
	0x3d80cb2b,
	0x1a208183,
	0xb4ef81f8,
	0xd8105f11,
	0x1b3f8183,
	0x2a80fe00,
	0x9270010c,
	0x0000000b,
	0x92717f0c,
	0x0000000b,
	0xb61e0dfb,
	0xd8105f01,
	0x2a80fe0b,
	0xd9505f11,
	0x1b3f8043,
	0xb43501f8,
	0x7538010f,
	0x21015b37,
	0x1a3f8183,
	0xb61b01f8,
	0x1a3fdb87,
	0x07b6ff97,
	0xa09f8e3c,
	0x1b5fda47,
	0x3dee424f,
	0x00000003,
	0x941413cf,
	0xa09f8e00,
	0x90168fcf,
	0x901601cf,
	0x21015b37,
	0x07b0ff77,
	0x2b187f7f,
	0x07bfff2f,
	0x3980db67,
	0x2b407f4f,
	0x83328107,
	0x2100cb8f,
	0x1a3f8183,
	0xb60f05f8,
	0x0852e267,
	0x21014b47,
	0x2101985f,
	0x0852d147,
	0x0a529657,
	0x2101504f,
	0x21011407,
	0x07b7ff27,
	0x3dd8133f,
	0x0000008f,
	0x3de4015f,
	0x00000002,
	0x07bfff1f,
	0x0853c13f,
	0xb6078dff,
	0x0855c35f,
	0x0851d00b,
	0xd8b11f60,
	0x84400303,
	0x7400010f,
	0x07b27e17,
	0x0856020f,
	0x30027e1f,
	0x461ffe27,
	0x07bffe37,
	0x39024927,
	0x3d824f3f,
	0xc6abb543,
	0x07bffe03,
	0xa71b89d7,
	0x001dfaad,
	0x0851d01f,
	0x4611d607,
	0xd8c11f62,
	0x84410507,
	0x07bffe1f,
	0x461fcc27,
	0x461ffe37,
	0xc6abc5ab,
	0x07bffe03,
	0xa7188dd7,
	0x001dfaad,
	0x83328307,
	0x3d00c607,
	0x3d80c71b,
	0x1a200203,
	0xb40381f8,
	0xd8105f01,
	0x1b3f8183,
	0x74000138,
	0x741403cc,
	0x3000fe18,
	0x07a07e10,
	0xc4ffdab0,
	0x1080c783,
	0xb4f609f8,
	0x75388173,
	0x1b5f8183,
	0xb60e05f8,
	0xb6f589ff,
	0x7400033f,
	0xd7981988,
	0xb60101f8,
	0x46115a03,
	0x8d027e0b,
	0xe02a0830,
	0xb6ff0dfa,
	0x0852e217,
	0x2b07fe0f,
	0xf0541e9a,
	0x0a528627,
	0x07bffe1f,
	0xf2ac1730,
	0xdda01641,
	0x0842c207,
	0x461ffe37,
	0x07bffe2f,
	0x3d965d77,
	0xc6abc46b,
	0x07bffe07,
	0x390a5f7f,
	0xa70e89d7,
	0x001dfaad,
	0x7538010f,
	0x3d00ca0f,
	0x3d80cb2b,
	0x1a208183,
	0xb4e901f8,
	0xd8105f01,
	0x1b3f8043,
	0xb60005f8,
	0xd8585f01,
	0x7414090f,
	0x2b08fe1f,
	0xd84c85e0,
	0xdb5c85d0,
	0xd8081c21,
	0xe4713443,
	0x540a5dcf,
	0x540b61cf,
	0x08550953,
	0x9414550f,
	0x940c070f,
	0x940e050f,
	0x9410030f,
	0x9412010f,
	0x766065cf,
	0x540341cf,
	0x540445cf,
	0x540549cf,
	0x54064dcf,
	0x540751cf,
	0x540855cf,
	0x540959cf,
	0x3de473cf,
	0xa9fd0ffb,
	0x0851d017,
	0x701681cf,
	0xd8891f61,
	0x84408503,
	0x74460977,
	0x00000003,
	0x013fffff,
	0xa1000fc7,
	0xb60301f8,
	0x083f641f,
	0x1a3fe587,
	0x4f7f860b,
	0xf9b00e41,
	0x5f008000,
	0xa8017403,
	0x65020c13,
	0x40c20c33,
	0x238f8c33,
	0x6d748c03,
	0x579ff81b,
	0x8d02060b,
	0x0851d017,
	0x07b87e0f,
	0xd8891f60,
	0xb6e10dff,
	0x9e406107,
	0x7400010f,
	0x07b47e17,
	0x461ffe27,
	0x07b7fe0f,
	0xff66279b,
	0xc6abb073,
	0x07bffe03,
	0xa77d89d7,
	0x001dfaac,
	0x7400053f,
	0x4618e407,
	0xf8011f1b,
	0xc6ffd7fb,
	0xb6c48dfb,
	0x1b5fd587,
	0x07bfff1f,
	0x3000fe04,
	0x2b00ff87,
	0x07b57e0c,
	0x07b57f18,
	0xa73e00fc,
	0x0019faa1,
	0xb69789ff,
	0x07a47f80,
	0x72081707,
	0x74041507,
	0x72071307,
	0x3f8d460f,
	0x2084163f,
	0x25081447,
	0x24841637,
	0x21081427,
	0x2084122f,
	0x24841217,
	0x07a30e07,
	0x07a2101f,
	0x4f7f8007,
	0x07a10a17,
	0x94040707,
	0x92070507,
	0x10810587,
	0x94080107,
	0xb6a101f8,
	0xe04c169b,
	0xb6a00dff,
	0x92070707,
	0x7402010f,
	0x3000fe17,
	0xd8781ee1,
	0x3901841f,
	0x461ffe27,
	0x07bffe33,
	0xc6abb413,
	0x07bffe03,
	0xa7718dd7,
	0x001dfaac,
	0xb6c80dfb,
	0xe3660e13,
	0xd8781ee1,
	0x3901841f,
	0x461ffe27,
	0x07bffe33,
	0xc6abb3c3,
	0x07bffe03,
	0xa76f0dd7,
	0x001dfaac,
	0xb6ae0dfb,
	0x7408010b,
	0xdbd83fca,
	0x1b5f8183,
	0xb6ac0dff,
	0x740a5508
};
const uint32_t BDSP_IMG_adpcm_decode_header [2] = {sizeof(BDSP_IMG_adpcm_decode_array1), 1};
const void * const BDSP_IMG_adpcm_decode [2] = {BDSP_IMG_adpcm_decode_header, BDSP_IMG_adpcm_decode_array1};
const uint32_t BDSP_IMG_adpcm_decode_tables_array1[] = {
	0x02000100,
	0x00c00000,
	0x01cc00f0,
	0x00000188,
	0x0000ff00,
	0x00000040,
	0xff18ff30,
	0x00e600e6,
	0x00e600e6,
	0x01990133,
	0x02660200,
	0x02660300,
	0x01990200,
	0x00e60133,
	0x00e600e6,
	0xffffffff,
	0xffffffff,
	0x00040002,
	0x00080006,
	0x00080007,
	0x000a0009,
	0x000c000b,
	0x000e000d,
	0x00110010,
	0x00150013,
	0x00190017,
	0x001f001c,
	0x00250022,
	0x002d0029,
	0x00370032,
	0x0042003c,
	0x00500049,
	0x00610058,
	0x0076006b,
	0x008f0082,
	0x00ad009d,
	0x00d100be,
	0x00fd00e6,
	0x01330117,
	0x01730151,
	0x01c10198,
	0x022001ee,
	0x02920256,
	0x031c02d4,
	0x03c3036c,
	0x048e0424,
	0x05830502,
	0x06ab0610,
	0x08120756,
	0x09c308e0,
	0x0bd00abd,
	0x0e4c0cff,
	0x114c0fba,
	0x14ee1307,
	0x19541706,
	0x1ea51bdc,
	0x251521b6,
	0x2cdf28ca,
	0x364b315b,
	0x41b23bb9,
	0x4f7e4844,
	0x602f5771,
	0x746269ce,
	0x00007fff,
	0x7fff7e01,
	0x7ffb6e1a,
	0x7ff34ea4,
	0x7fe7204d,
	0x7fd6e41c,
	0x7fc29b6d,
	0x7faa47f5,
	0x7f8debbd,
	0x7f6d8928,
	0x7f4922ec,
	0x7f20bc18,
	0x7ef4580c,
	0x7ec3fa83,
	0x7e8fa787,
	0x7e57637b,
	0x7e1b3310,
	0x7ddb1b50,
	0x7d972194,
	0x7d4f4b87,
	0x7d039f25,
	0x7cb422bc,
	0x7c60dce7,
	0x7c09d493,
	0x7baf10f7,
	0x7b50999b,
	0x7aee7651,
	0x7a88af36,
	0x7a1f4cb1,
	0x79b25775,
	0x7941d879,
	0x78cdd8ff,
	0x7856628c,
	0x77db7eeb,
	0x775d382a,
	0x76db989c,
	0x7656aad1,
	0x75ce799c,
	0x7543100d,
	0x74b47973,
	0x7422c157,
	0x738df37e,
	0x72f61be5,
	0x725b46c2,
	0x71bd807f,
	0x711cd5be,
	0x70795353,
	0x6fd30641,
	0x6f29fbc0,
	0x6e7e4133,
	0x6dcfe42c,
	0x6d1ef268,
	0x6c6b79cd,
	0x6bb5886b,
	0x6afd2c77,
	0x6a42744c,
	0x69856e68,
	0x68c6296a,
	0x6804b412,
	0x67411d3c,
	0x667b73e4,
	0x65b3c71e,
	0x64ea2617,
	0x641ea016,
	0x63514473,
	0x6282229f,
	0x61b14a18,
	0x60deca70,
	0x600ab345,
	0x5f351444,
	0x5e5dfd24,
	0x5d857da4,
	0x5caba58b,
	0x5bd084a8,
	0x5af42acb,
	0x5a16a7c7,
	0x59380b70,
	0x58586599,
	0x5777c611,
	0x56963ca2,
	0x55b3d912,
	0x54d0ab1b,
	0x53ecc272,
	0x53082ebb,
	0x5222ff91,
	0x513d447f,
	0x50570d00,
	0x4f70687a,
	0x4e896644,
	0x4da2159c,
	0x4cba85ab,
	0x4bd2c581,
	0x4aeae414,
	0x4a02f03f,
	0x491af8c1,
	0x48330c38,
	0x474b3925,
	0x46638de6,
	0x457c18b8,
	0x4494e7b2,
	0x43ae08c6,
	0x42c789c2,
	0x41e17849,
	0x40fbe1d7,
	0x4016d3bb,
	0x3f325b1b,
	0x3e4e84f0,
	0x3d6b5e03,
	0x3c88f2f0,
	0x3ba75023,
	0x3ac681d4,
	0x39e6940d,
	0x390792a2,
	0x38298933,
	0x374c832d,
	0x36708bc5,
	0x3595adfa,
	0x34bbf493,
	0x33e36a21,
	0x330c18f9,
	0x32360b37,
	0x31614abe,
	0x308de134,
	0x2fbbd806,
	0x2eeb3861,
	0x2e1c0b38,
	0x2d4e5941,
	0x2c822af2,
	0x2bb78887,
	0x2aee79f8,
	0x2a270704,
	0x29613727,
	0x289d119f,
	0x27da9d6a,
	0x2719e148,
	0x265ae3b7,
	0x259daaf7,
	0x24e23d06,
	0x24289fa3,
	0x2370d84e,
	0x22baec45,
	0x2206e088,
	0x2154b9d5,
	0x20a47cae,
	0x1ff62d52,
	0x1f49cfc2,
	0x1e9f67c1,
	0x1df6f8d2,
	0x1d50863c,
	0x1cac1305,
	0x1c09a1f8,
	0x1b6935a2,
	0x1acad054,
	0x1a2e7422,
	0x199422e6,
	0x18fbde3d,
	0x1865a78c,
	0x17d17ffd,
	0x173f6881,
	0x16af61d1,
	0x16216c6f,
	0x159588a6,
	0x150bb68a,
	0x1483f5fc,
	0x13fe46a5,
	0x137aa800,
	0x12f91950,
	0x127999aa,
	0x11fc27f1,
	0x1180c2d8,
	0x110768e5,
	0x1090186f,
	0x101acfa0,
	0x0fa78c78,
	0x0f364ccc,
	0x0ec70e47,
	0x0e59ce6c,
	0x0dee8a97,
	0x0d854001,
	0x0d1debb9,
	0x0cb88aae,
	0x0c5519ac,
	0x0bf3955f,
	0x0b93fa51,
	0x0b3644ef,
	0x0ada7189,
	0x0a807c52,
	0x0a286161,
	0x09d21cb8,
	0x097daa3c,
	0x092b05be,
	0x08da2af9,
	0x088b1593,
	0x083dc120,
	0x07f22922,
	0x07a8490c,
	0x07601c40,
	0x07199e14,
	0x06d4c9d1,
	0x06919ab7,
	0x06500bfa,
	0x061018c7,
	0x05d1bc45,
	0x0594f193,
	0x0559b3cf,
	0x051ffe10,
	0x04e7cb70,
	0x04b11706,
	0x047bdbea,
	0x04481537,
	0x0415be0a,
	0x03e4d188,
	0x03b54ad9,
	0x0387252d,
	0x035a5bbd,
	0x032ee9cb,
	0x0304caa5,
	0x02dbf9a4,
	0x02b4722d,
	0x028e2fb7,
	0x02692dc5,
	0x024567eb,
	0x0222d9d0,
	0x02017f2d,
	0x01e153ce,
	0x01c25394,
	0x01a47a77,
	0x0187c485,
	0x016c2de1,
	0x0151b2cb,
	0x01384f99,
	0x012000bc,
	0x0108c2c2,
	0x00f29252,
	0x00dd6c32,
	0x00c94d44,
	0x00b6328a,
	0x00a41922,
	0x0092fe4d,
	0x0082df69,
	0x0073b9f8,
	0x00658b9b,
	0x00585215,
	0x004c0b4d,
	0x0040b54c,
	0x00364e3f,
	0x002cd475,
	0x00244664,
	0x001ca2a5,
	0x0015e7f6,
	0x00101539,
	0x000b2979,
	0x000723e3,
	0x000403cb,
	0x0001c8ac,
	0x00007226,
	0x00000000
};
const uint32_t BDSP_IMG_adpcm_decode_tables_header [2] = {sizeof(BDSP_IMG_adpcm_decode_tables_array1), 1};
const void * const BDSP_IMG_adpcm_decode_tables [2] = {BDSP_IMG_adpcm_decode_tables_header, BDSP_IMG_adpcm_decode_tables_array1};
const uint32_t BDSP_IMG_adpcm_decode_inter_frame_array1[] = {
	0x00000000,
	0x00000f0c
};
const uint32_t BDSP_IMG_adpcm_decode_inter_frame_header [2] = {sizeof(BDSP_IMG_adpcm_decode_inter_frame_array1), 1};
const void * const BDSP_IMG_adpcm_decode_inter_frame [2] = {BDSP_IMG_adpcm_decode_inter_frame_header, BDSP_IMG_adpcm_decode_inter_frame_array1};
/* End of File */

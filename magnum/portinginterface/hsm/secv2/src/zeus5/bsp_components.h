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
******************************************************************************/

/* This file is autogenerated, do not edit. */

#ifndef BSP_COMPONENTS__H
#define BSP_COMPONENTS__H

#ifdef __cplusplus
extern "C"
{
#endif

/* BSP Components. Reserved components are resolved in Ca Vendor specific header files.*/
typedef enum
{
    Bsp_CmdComponent_eRedacted_0x00   = 0x00,
    Bsp_CmdComponent_eRedacted_0x01   = 0x01,
    Bsp_CmdComponent_eRv             = 0x02,
    Bsp_CmdComponent_eOtpMsp         = 0x03,
    Bsp_CmdComponent_eControl        = 0x04,
    Bsp_CmdComponent_eKeySlot        = 0x05,
    Bsp_CmdComponent_eKeyLadder      = 0x06,
    Bsp_CmdComponent_eRedacted_0x07   = 0x07,
    Bsp_CmdComponent_eOtpMisc        = 0x08,
    Bsp_CmdComponent_eOtpMode0       = 0x09,
    Bsp_CmdComponent_eOtpDataSection = 0x0a,
    Bsp_CmdComponent_eMemcArch       = 0x0b,
    Bsp_CmdComponent_eGisbBlocker    = 0x0c,
    Bsp_CmdComponent_eBiuChecker     = 0x0d,
    Bsp_CmdComponent_eCrypto         = 0x11,
    Bsp_CmdComponent_eEtsi5          = 0x15,
    Bsp_CmdComponent_eRedacted_0x18   = 0x18,
    Bsp_CmdComponent_eRedacted_0x19   = 0x19,
    Bsp_CmdComponent_eRedacted_0x1a   = 0x1a,
    Bsp_CmdComponent_eRedacted_0x1b   = 0x1b,
    Bsp_CmdComponent_eRedacted_0x1c   = 0x1c,
    Bsp_CmdComponent_eHdcp1x         = 0x1e,
    Bsp_CmdComponent_eHdcp22         = 0x1f,
    Bsp_CmdComponent_eRpmb           = 0x20,
    Bsp_CmdComponent_eRedacted_0x21   = 0x21,
    Bsp_CmdComponent_eHwkl           = 0x22,
    Bsp_CmdComponent_eMax            = 0xff
}Bsp_CmdComponent_e;

#ifdef __cplusplus
}
#endif
#endif
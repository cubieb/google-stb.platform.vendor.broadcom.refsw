/***************************************************************************
 *     (c)2013 Broadcom Corporation
 *
 *  This program is the proprietary software of Broadcom Corporation and/or its licensors,
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
 * $brcm_Workfile: utility_ids.h $
 * $brcm_Revision: 1 $
 * $brcm_Date: 4/10/14 5:18p $
 *
 **************************************************************************/

#ifndef UTILITY_H__
#define UTILITY_H__

/* utility module IDs  */
typedef enum Utility_ModuleId_e{
    Utility_ModuleId_eHeartbeat = 0x01,
    Utility_ModuleId_eRsa       = 0x02,
    Utility_ModuleId_eKeyLoader = 0x03
}Utility_ModuleId_e;

enum {
    /* Heartbeat command IDs */
    Heartbeat_CommandId_eTakePulse = 0x001,
    Heartbeat_CommandId_eMax,

    /* Rsa command IDs */
    Rsa_CommandId_eGetPublicKey   = 0x100,
    Rsa_CommandId_eVerify         = 0x101,
    Rsa_CommandId_eSign           = 0x102,
    Rsa_CommandId_ePublicEncrypt  = 0x103,
    Rsa_CommandId_ePublicDecrypt  = 0x104,
    Rsa_CommandId_ePrivateEncrypt = 0x105,
    Rsa_CommandId_ePrivateDecrypt = 0x106,
    Rsa_CommandId_eMax,

    /* Key Loader command IDs */
    KeyLoader_CommandId_eAllocAndConfig = 0x200,
    KeyLoader_CommandId_eLoadWrappedKey = 0x201,
    KeyLoader_CommandId_eFreeKeyslot    = 0x202,
    KeyLoader_CommandId_eUpdateIv       = 0x203,
    KeyLoader_CommandId_eMax
};


#endif /* #ifndef UTILITY_H__ */

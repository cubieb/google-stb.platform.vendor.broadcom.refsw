/***************************************************************************
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
 *
 * [File Description:]
 *
 ***************************************************************************/
#ifndef _BXVD_CORE_AVD_REVT0_H_
#define _BXVD_CORE_AVD_REVT0_H_

#include "bxvd_image.h"
#include "bxvd_him.h"
#include "bxvd_core_avd_common.h"

#ifdef __cplusplus
extern "C" {
#endif

#define BXVD_P_READ_DISPLAY_INFO(hXvdDipCh, stDisplayInfo)                              \
   BXVD_P_ReadDisplayInfo_HIM_API_isr(hXvdDipCh->stChannelSettings.hXvd,                \
                                      hXvdDipCh->stChannelSettings.uiDisplayInfoOffset, \
                                      &stDisplayInfo);

#define BXVD_P_READ_HIM(hXvd, wordOffset, value)                                          \
   value = BXVD_Reg_Read32_isr(hXvd,                                                      \
                               hXvd->stPlatformInfo.stReg.uiOL_CTL_Him_Base+(wordOffset));

#define BXVD_P_WRITE_HIM(hXvd, wordOffset, value)                                   \
   BXVD_Reg_Write32_isr(hXvd,                                                       \
                        hXvd->stPlatformInfo.stReg.uiOL_CTL_Him_Base+(wordOffset),  \
                        value);


#define BXVD_P_SAVE_DIP_INFO_STC(hXvdDispCh, stDisplayInfo)                                \
   for (i=0; i< BXVD_P_STC_MAX; i++)                                                       \
   {                                                                                       \
      hXvdDipCh->stDisplayInterruptInfo.astSTC[i].uiValue = stDisplayInfo.stc_snapshot[i]; \
      hXvdDipCh->stDisplayInterruptInfo.astSTC[i].bValid = true;                           \
   }

#define BXVD_P_DBG_MSG_DISP_INFO_OFFSET(hXvd, pInitRsp)                                    \
   BXVD_DBG_MSG(hXvd, (" display_info_0_offset: %#x", pInitRsp->display_info_0_offset));   \
   BXVD_DBG_MSG(hXvd, (" display_info_1_offset: %#x", pInitRsp->display_info_1_offset));

#define BXVD_P_SAVE_DISPLAY_INFO(hXvd, pInitRsp)                   \
   hXvd->uiDisplayInfo0_Offset = pInitRsp->display_info_0_offset;  \
   hXvd->uiDisplayInfo1_Offset = pInitRsp->display_info_1_offset;  \
   hXvd->uiDisplayInfo2_Offset = pInitRsp->display_info_2_offset;


#define BXVD_P_SAVE_XVD_CHANNEL_DISPLAY_INFO_0(hXvdCh, hXvd)  hXvdCh=hXvdCh


#define BXVD_P_SAVE_XVD_CHANNEL_DISPLAY_INFO_1(hXvdCh, hXvd)  hXvdCh=hXvdCh

#define BXVD_P_SAVE_XVD_CHANNEL_DISPLAY_INFO_2(hXvdCh, hXvd)  hXvdCh=hXvdCh


#define BXVD_P_SAVE_DIP_CHANNEL_DISPLAY_INFO_0(stXvdDipChSettings, hXvd)  \
   stXvdDipChSettings.uiDisplayInfoOffset = hXvd->uiDisplayInfo0_Offset;


#define BXVD_P_SAVE_DIP_CHANNEL_DISPLAY_INFO_1(stXvdDipChSettings, hXvd)  \
   stXvdDipChSettings.uiDisplayInfoOffset = hXvd->uiDisplayInfo1_Offset;

#define BXVD_P_SAVE_DIP_CHANNEL_DISPLAY_INFO_2(stXvdDipChSettings, hXvd)  \
   stXvdDipChSettings.uiDisplayInfoOffset = hXvd->uiDisplayInfo2_Offset;

/* Core Firmware */
typedef struct
{
      BXVD_IMAGE_FirmwareID outerELFFirmwareID;
      BXVD_IMAGE_FirmwareID innerELFFirmwareID;
      BXVD_IMAGE_FirmwareID authenticatedFirmwareID;
} BXVD_P_CoreFirmware_RevT0;

/* Platform Register Maps */
typedef struct
{
      uint32_t uiSun_SWInitSet;
      uint32_t uiSun_SWInitSetAvdMask;
      uint32_t uiSun_SWInitClear;
      uint32_t uiSun_SWInitClearAvdMask;

      uint32_t uiAvd_SoftShutdownCtrl;
      uint32_t uiAvd_SoftShutdownCtrlMask;
      uint32_t uiAvd_SoftShutdownStatus;
      uint32_t uiAvd_SoftShutdownStatusMask;

      uint32_t uiDecode_IPShim_AvdClkGate;
      uint32_t uiDecode_IPShim_OtpCtl;
      uint32_t uiDecode_IPShim_OtpCtl_DisableRV9;
      uint32_t uiDecode_CPUId;
      uint32_t uiDecode_CPUId_BldIdMask;
      uint32_t uiDecode_CPUId_HEVD_dualpipeMask;

      uint32_t uiAvd_CPUL2InterruptSet;

      uint32_t uiBvnf_Intr2_0_R5fStatus;

      uint32_t uiBvnf_Intr2_3_AvdStatus;
      uint32_t uiBvnf_Intr2_3_AvdClear;
      uint32_t uiBvnf_Intr2_3_AvdMaskClear;
      uint32_t uiBvnf_Intr2_11_AvdStatus;
      uint32_t uiBvnf_Intr2_11_AvdClear;
      uint32_t uiBvnf_Intr2_11_AvdMaskClear;

      uint32_t uiInterrupt_PicDataRdy;
      uint32_t uiInterrupt_PicDataRdy1;
      uint32_t uiInterrupt_PicDataRdy2;
      uint32_t uiInterrupt_Mailbox;
      uint32_t uiInterrupt_StereoSeqError;
      uint32_t uiInterrupt_StillPictureRdy;
      uint32_t uiInterrupt_OuterWatchdog;
      uint32_t uiInterrupt_VICReg;
      uint32_t uiInterrupt_VICSCBWr;
      uint32_t uiInterrupt_VICInstrRd;
      uint32_t uiInterrupt_VICILInstrRd;

      uint32_t uiDecode_InnerInstructionBase;
      uint32_t uiDecode_InnerEndOfCode;
      uint32_t uiDecode_InnerGlobalIOBase;
      uint32_t uiDecode_InnerCPUDebug;
      uint32_t uiDecode_InnerCPUAux;

      uint32_t uiDecode_OuterInstructionBase;
      uint32_t uiDecode_OuterEndOfCode;
      uint32_t uiDecode_OuterGlobalIOBase;
      uint32_t uiDecode_OuterCPUDebug;
      uint32_t uiDecode_OuterCPUAux;
      uint32_t uiDecode_OuterInterruptMask;
      uint32_t uiDecode_OuterInterruptClear;
      uint32_t uiDecode_OuterWatchdogTimer;
      uint32_t uiDecode_OuterCPU2HostMailbox;
      uint32_t uiDecode_OuterHost2CPUMailbox;
      uint32_t uiDecode_OuterCPU2HostStatus;

      uint32_t uiDecode_Inner2InstructionBase;
      uint32_t uiDecode_Inner2EndOfCode;
      uint32_t uiDecode_Inner2GlobalIOBase;
      uint32_t uiDecode_Inner2CPUDebug;
      uint32_t uiDecode_Inner2CPUAux;

#if 0
      uint32_t uiDecode_CabacBinDepth;

      uint32_t uiDecode_CabacBinCtl;
      uint32_t uiDecode_CabacBinCtl_ResetMask;

      uint32_t uiDecode_SintStrmSts;
      uint32_t uiDecode_SintStrmSts_ResetMask;
#endif
      uint32_t uiDecode_OLSintStrmSts;
      uint32_t uiDecode_OLSintStrmSts_ResetMask;
#if 0
      uint32_t uiDecode_MainCtl;
      uint32_t uiDecode_MainCtl_ResetMask;
#endif
      uint32_t uiDecode_SWReset;
      uint32_t uiDecode_SWReset_ILSIResetMask;

      uint32_t uiSunGisbArb_ReqMask;
      uint32_t uiSunGisbArb_ReqMaskAVDMask;

      uint32_t uiDecode_StripeWidth;
      uint32_t uiDecode_StripeWidthShift;

      uint32_t uiPFRIInfo;
      uint32_t uiPFRIInfo_DataBusWidthMask;
      uint32_t uiPFRIInfo_DataBusWidthShift;
      uint32_t uiPFRIInfo_BankHeightMask;
      uint32_t uiPFRIInfo_BankHeightShift;
      uint32_t uiPFRIInfo_PFRIGroupagesEnaMask;
      uint32_t uiPFRIInfo_PFRIGroupagesEnaShift;
      uint32_t uiPFRIInfo_PFRINumBanksMask;
      uint32_t uiPFRIInfo_PFRINumBanksShift;

      uint32_t uiAVD_PcacheMode;
      uint32_t uiAVD_PcacheModeMap8Mask;
      uint32_t uiAVD_PcacheModeMap8Shift;
      uint32_t uiAVD_PcacheModeYGranMask;
      uint32_t uiAVD_PcacheModeYGranShift;
      uint32_t uiAVD_PcacheModeXGranMask;
      uint32_t uiAVD_PcacheModeXGranShift;

      uint32_t uiDecode_StripeWidth_P2;
      uint32_t uiPFRIInfo_P2;
      uint32_t uiAVD_PcacheMode_P2;

      uint32_t uiDecode_RVCCtl;
      uint32_t uiDecode_RVCPut;
      uint32_t uiDecode_RVCGet;
      uint32_t uiDecode_RVCBase;
      uint32_t uiDecode_RVCEnd;

      uint32_t uiOL_CTL_Him_Base;
} BXVD_P_PlatformReg_RevT0;

typedef struct
{
	BXVD_P_CoreFirmware_RevT0 stFirmware;
	BXVD_P_PlatformReg_RevT0 stReg;
} BXVD_P_PlatformInfo_RevT0;

#define BXVD_P_CONTEXT_PLATFORM BXVD_P_PlatformInfo_RevT0 stPlatformInfo;

#define BXVD_P_HOSTINTERFACEMEMORY_COOK_OFFSETS( _stOffsets_, _ulByteCount_ )             \
{                                                                                         \
   /* Size of the data element. */                                                        \
   _stOffsets_.ulBytesPerValue = _ulByteCount_;                                           \
                                                                                          \
   /* Create a mask based on the size of the data element. */                             \
   switch( _ulByteCount_ )                                                                \
   {                                                                                      \
      case 1:  _stOffsets_.ulByteMask = 0xFF ;        break;                              \
      case 2:  _stOffsets_.ulByteMask = 0xFFFF ;      break;                              \
      case 3:  _stOffsets_.ulByteMask = 0xFFFFFF ;    break;                              \
      case 4:  _stOffsets_.ulByteMask = 0xFFFFFFFF ;  break;                              \
      default:  _stOffsets_.ulByteMask = 0xFF ;       break;                              \
   }                                                                                      \
                                                                                          \
   /* Divide by 4 to turn the HIM byte offset into a word offset. */                      \
   _stOffsets_.ulWordOffset = ( _stOffsets_.ulByteOffset & 0xfffffffc );                  \
                                                                                          \
   /* Extract the two low order bits and multiply                                         \
    * by 8 to get the byte shift */                                                       \
   _stOffsets_.ulByteShift = (( _stOffsets_.ulByteOffset & 0x3 ) *  8 );                  \
                                                                                          \
   /* Create the inverse of the mask for read-modify-write operations */                  \
   _stOffsets_.ulInverseMask = ~( _stOffsets_.ulByteMask << _stOffsets_.ulByteShift  );   \
}

/*
 * Macro for retrieving the Cabac Bin Fullness..
 */
#define BXVD_AVD_P_GET_CABAC_BIN_FULLNESS( _hXvdCh_, _ulCabacBinFullness_ )                                    \
{                                                                                                              \
   BXVD_AVD_P_HOSTINTERFACEMEMORY_READ( _hXvdCh_, _hXvdCh_->stCabacBinFullnessIndex, &_ulCabacBinFullness_ );  \
   _ulCabacBinFullness_ *= 512;                                                                                \
}

#ifdef __cplusplus
}
#endif

#endif /* _BXVD_CORE_AVD_REVT0_H_ */

/******************************************************************************
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
* Module Description:
*
*****************************************************************************/

#include "bdsq.h"
#include "bdsq_priv.h"
#include "bdsq_g1_priv.h"
#include "bdsq_7366_priv.h"
#include "bchp_avs_top_ctrl.h"

BDBG_MODULE(bdsq_7366_priv);


const uint32_t BDSQ_g1_ChannelIntrID[BDSQ_NUM_CHANNELS][BDSQ_g1_MaxIntID] = {
   {
      /* DSEC channel 0 interrupts */
      BCHP_INT_ID_DSEC_TIMER1_0,
      BCHP_INT_ID_DSEC_TIMER2_0,
      BCHP_INT_ID_DSEC_DONE_0,
      BCHP_INT_ID_DSEC_TX_A_EMPTY_0,
      BCHP_INT_ID_DSEC_RX_A_EMPTY_0,
      BCHP_INT_ID_DSEC_ACW_DONE_0,
      BCHP_INT_ID_DSEC_VOL_LT_THRESH_0,
      BCHP_INT_ID_DSEC_VOL_GT_THRESH_0,
      BCHP_INT_ID_DSEC_TONE_RISE_0,
      BCHP_INT_ID_DSEC_TONE_FALL_0,
      BCHP_INT_ID_DSEC_IDLE_TIMEOUT_0
   },
   {
      /* DSEC channel 1 interrupts */
      BCHP_INT_ID_DSEC_TIMER1_1,
      BCHP_INT_ID_DSEC_TIMER2_1,
      BCHP_INT_ID_DSEC_DONE_1,
      BCHP_INT_ID_DSEC_TX_A_EMPTY_1,
      BCHP_INT_ID_DSEC_RX_A_EMPTY_1,
      BCHP_INT_ID_DSEC_ACW_DONE_1,
      BCHP_INT_ID_DSEC_VOL_LT_THRESH_1,
      BCHP_INT_ID_DSEC_VOL_GT_THRESH_1,
      BCHP_INT_ID_DSEC_TONE_RISE_1,
      BCHP_INT_ID_DSEC_TONE_FALL_1,
      BCHP_INT_ID_DSEC_IDLE_TIMEOUT_1
   },
#if (BCHP_VER<BCHP_VER_B0)
   {
      /* DSEC channel 2 interrupts */
      BCHP_INT_ID_DSEC_TIMER1_2,
      BCHP_INT_ID_DSEC_TIMER2_2,
      BCHP_INT_ID_DSEC_DONE_2,
      BCHP_INT_ID_DSEC_TX_A_EMPTY_2,
      BCHP_INT_ID_DSEC_RX_A_EMPTY_2,
      BCHP_INT_ID_DSEC_ACW_DONE_2,
      BCHP_INT_ID_DSEC_VOL_LT_THRESH_2,
      BCHP_INT_ID_DSEC_VOL_GT_THRESH_2,
      BCHP_INT_ID_DSEC_TONE_RISE_2,
      BCHP_INT_ID_DSEC_TONE_FALL_2,
      BCHP_INT_ID_DSEC_IDLE_TIMEOUT_2
   },
   {
      /* DSEC channel 3 interrupts */
      BCHP_INT_ID_DSEC_TIMER1_3,
      BCHP_INT_ID_DSEC_TIMER2_3,
      BCHP_INT_ID_DSEC_DONE_3,
      BCHP_INT_ID_DSEC_TX_A_EMPTY_3,
      BCHP_INT_ID_DSEC_RX_A_EMPTY_3,
      BCHP_INT_ID_DSEC_ACW_DONE_3,
      BCHP_INT_ID_DSEC_VOL_LT_THRESH_3,
      BCHP_INT_ID_DSEC_VOL_GT_THRESH_3,
      BCHP_INT_ID_DSEC_TONE_RISE_3,
      BCHP_INT_ID_DSEC_TONE_FALL_3,
      BCHP_INT_ID_DSEC_IDLE_TIMEOUT_3
   }
#endif
};


/******************************************************************************
 BDSQ_P_GetRegisterAddress()
******************************************************************************/
BERR_Code BDSQ_P_GetRegisterAddress(BDSQ_ChannelHandle h, uint32_t reg, uint32_t *pAddr)
{
   BERR_Code retCode = BERR_SUCCESS;
   *pAddr = reg;

   if ((reg < 0x1218000) || (reg > 0x1218158))
      return BERR_INVALID_PARAMETER;

   *pAddr += h->channel * 0x1000;

   /*BDBG_MSG(("GetRegisterAddress(%d): %08X -> %08X", h->channel, reg, *pAddr)); */
   return retCode;
}


/******************************************************************************
 BDSQ_P_ReadRegister_isrsafe()
******************************************************************************/
BERR_Code BDSQ_P_ReadRegister_isrsafe(
   BDSQ_ChannelHandle h,      /* [in] BDSQ channel handle */
   uint32_t           reg,    /* [in] address of register to read */
   uint32_t           *val    /* [out] contains data that was read */
)
{
   BDSQ_g1_P_Handle *hDev = h->pDevice->pImpl;
   BERR_Code retCode = BERR_SUCCESS;
   uint32_t addr;

   retCode = BDSQ_P_GetRegisterAddress(h, reg, &addr);
   *val = BREG_Read32(hDev->hRegister, addr);

   return retCode;
}


/******************************************************************************
 BDSQ_P_WriteRegister_isrsafe()
******************************************************************************/
BERR_Code BDSQ_P_WriteRegister_isrsafe(
   BDSQ_ChannelHandle h,      /* [in] BDSQ channel handle */
   uint32_t           reg,    /* [in] address of register to write */
   uint32_t           val     /* [in] contains data to be written */
)
{
   BDSQ_g1_P_Handle *hDev = h->pDevice->pImpl;
   BERR_Code retCode = BERR_SUCCESS;
   uint32_t addr;

   retCode = BDSQ_P_GetRegisterAddress(h, reg, &addr);
   BREG_Write32(hDev->hRegister, addr, val);

   return retCode;
}


/******************************************************************************
 BDSQ_P_GetDsecSramPowerRegister()
******************************************************************************/
uint32_t BDSQ_P_GetDsecSramPowerRegister(BDSQ_ChannelHandle h)
{
   uint32_t addr = 0;

#if (BCHP_VER>=BCHP_VER_B0)
   if (h->channel == 0)
      addr = BCHP_AVS_TOP_CTRL_SRAM_POWER_GATE_IN_FTMDSEC0;
   else
      addr = BCHP_AVS_TOP_CTRL_SRAM_POWER_GATE_IN_FTMDSEC1;
#else
   addr = 0;
#endif
   return addr;
}


/******************************************************************************
 BDSQ_P_PowerDownDsecPhy()
******************************************************************************/
BERR_Code BDSQ_P_PowerDownDsecPhy(BDSQ_ChannelHandle h)
{
   BDSQ_g1_P_ChannelHandle *hChn = (BDSQ_g1_P_ChannelHandle *)(h->pImpl);
   uint32_t addrSram;

   /* power down rx phy */
   BDSQ_P_OrRegister(h, BCHP_SDS_DSEC_DS_COMMON_CONTROL, 0x00000002);

   /* disable rx input */
   BDSQ_P_OrRegister(h, BCHP_SDS_DSEC_DS_COMMON_CONTROL, 0x00000040);

   /* power down sram if both dsec and vsense off */
   if (!hChn->bVsenseEnabled)
   {
      addrSram = BDSQ_P_GetDsecSramPowerRegister(h);
      BDSQ_P_OrRegister(h, addrSram, 0x00000001);
   }

	return BERR_SUCCESS;
}


/******************************************************************************
 BDSQ_P_PowerUpDsecPhy()
******************************************************************************/
BERR_Code BDSQ_P_PowerUpDsecPhy(BDSQ_ChannelHandle h)
{
   BDSQ_g1_P_Handle *hDev = h->pDevice->pImpl;
   BDSQ_g1_P_ChannelHandle *hChn = (BDSQ_g1_P_ChannelHandle *)(h->pImpl);
   uint32_t addrSram;

#if 1
   /* power up sram */
   addrSram = BDSQ_P_GetDsecSramPowerRegister(h);
   BDSQ_P_AndRegister(h, addrSram, ~0x00000001);
#else
   /* power up sram */
   BCHP_PWR_AcquireResource(hDev->hChip, h->channel ? BCHP_PWR_RESOURCE_DSEC1_SRAM : BCHP_PWR_RESOURCE_DSEC0_SRAM);
#endif

   /* update pga gain */
   BDSQ_P_ReadModifyWriteRegister(h, BCHP_SDS_DSEC_AP_ANA_CTL, ~0x00000078, (hChn->configParam[BDSQ_g1_CONFIG_PGA_GAIN] & 0xF) << 3);

   /* power up rx phy */
   BDSQ_P_AndRegister(h, BCHP_SDS_DSEC_DS_COMMON_CONTROL, ~0x00000002);
   BDSQ_P_ToggleBit(h, BCHP_SDS_DSEC_DS_COMMON_CONTROL, 0x00000001); /* reset rx phy  */

   /* enable rx input */
   BDSQ_P_OrRegister(h, BCHP_SDS_DSEC_DS_COMMON_CONTROL, 0x00000040);

	return BERR_SUCCESS;
}


/******************************************************************************
 BDSQ_P_PowerDownVsensePhy()
******************************************************************************/
BERR_Code BDSQ_P_PowerDownVsensePhy(BDSQ_ChannelHandle h)
{
   BDSQ_g1_P_ChannelHandle *hChn = (BDSQ_g1_P_ChannelHandle *)(h->pImpl);
   BERR_Code retCode = BERR_SUCCESS;
   uint32_t addrSram;

   /* power down vsense phy */
   BDSQ_P_OrRegister(h, BCHP_SDS_DSEC_DS_COMMON_CONTROL, 0x00000008);

   /* disable vsense input */
   BDSQ_P_AndRegister(h, BCHP_SDS_DSEC_DS_COMMON_CONTROL, ~0x00000080);

   /* stop vsense adc */
   BDSQ_P_ReadModifyWriteRegister(h, BCHP_SDS_DSEC_DS_COMMON_CONTROL, ~0x00000100, 0x00000200);

   /* power down sram if both dsec and vsense off */
   if (!h->bEnabled)
   {
      addrSram = BDSQ_P_GetDsecSramPowerRegister(h);
      BDSQ_P_OrRegister(h, addrSram, 0x00000001);
   }

	return retCode;
}


/******************************************************************************
 BDSQ_P_PowerUpVsensePhy()
******************************************************************************/
BERR_Code BDSQ_P_PowerUpVsensePhy(BDSQ_ChannelHandle h)
{
   BDSQ_g1_P_ChannelHandle *hChn = (BDSQ_g1_P_ChannelHandle *)(h->pImpl);
   BERR_Code retCode = BERR_SUCCESS;
   uint32_t addrSram, val;

   /* power up sram */
   addrSram = BDSQ_P_GetDsecSramPowerRegister(h);
   BDSQ_P_AndRegister(h, addrSram, ~0x00000001);

   /* update vsense hi threshold */
   val = hChn->configParam[BDSQ_g1_CONFIG_VSENSE_THRESHOLD_HI] + 0x80;  /* convert to 2's comp */
   BDSQ_P_ReadModifyWriteRegister(h, BCHP_SDS_DSEC_DS_SAR_THRSH, ~0x0000FF00, (val & 0xFF) << 8);

   /* update vsense lo threshold */
   val = hChn->configParam[BDSQ_g1_CONFIG_VSENSE_THRESHOLD_LO] + 0x80;  /* convert to 2's comp */
   BDSQ_P_ReadModifyWriteRegister(h, BCHP_SDS_DSEC_DS_SAR_THRSH, ~0x000000FF, val & 0xFF);

   /* power up vsense phy */
   BDSQ_P_AndRegister(h, BCHP_SDS_DSEC_DS_COMMON_CONTROL, ~0x00000008);
   BDSQ_P_ToggleBit(h, BCHP_SDS_DSEC_DS_COMMON_CONTROL, 0x00000004); /* reset vsense phy  */

   /* set lpf alpha for vsense operation, configure sar format to offset binary */
   BDSQ_P_ReadModifyWriteRegister(h, BCHP_SDS_DSEC_DS_SAR_CONTROL, ~0x00000F10, 0x00000500);

   /* enable vsense input */
   BDSQ_P_OrRegister(h, BCHP_SDS_DSEC_DS_COMMON_CONTROL, 0x00000080);

   /* start vsense adc */
   BDSQ_P_ReadModifyWriteRegister(h, BCHP_SDS_DSEC_DS_COMMON_CONTROL, ~0x00000200, 0x00000100);

	return retCode;
}


/******************************************************************************
 BDSQ_P_ReadVsenseAdc()
******************************************************************************/
BERR_Code BDSQ_P_ReadVsenseAdc(BDSQ_ChannelHandle h, uint16_t *pVal)
{
   uint32_t val;

   BDSQ_P_ReadRegister_isrsafe(h, BCHP_SDS_DSEC_DS_SAR_DATA_OUT, &val);

   /* 8-bit vsense adc, offset binary format */
   *pVal = (uint16_t)(val & 0xFF);

   return BERR_SUCCESS;
}

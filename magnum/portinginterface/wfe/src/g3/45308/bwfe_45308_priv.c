/***************************************************************************
 *     Copyright (c) 2005-2014, Broadcom Corporation
 *     All Rights Reserved
 *     Confidential Property of Broadcom Corporation
 *
 *  THIS SOFTWARE MAY ONLY BE USED SUBJECT TO AN EXECUTED SOFTWARE LICENSE
 *  AGREEMENT  BETWEEN THE USER AND BROADCOM.  YOU HAVE NO RIGHT TO USE OR
 *  EXPLOIT THIS MATERIAL EXCEPT SUBJECT TO THE TERMS OF SUCH AN AGREEMENT.
 *
 * $brcm_Workfile: $
 * $brcm_Revision: $
 * $brcm_Date: $
 *
 * [File Description:]
 *
 * Revision History:
 *
 * $brcm_Log: $
 *
 ***************************************************************************/
#include "bwfe.h"
#include "bwfe_priv.h"
#include "bwfe_g3_priv.h"
#include "bwfe_45308_priv.h"

BDBG_MODULE(bwfe_45308_priv);


uint32_t BWFE_g3_ChannelIntrID[BWFE_NUM_CHANNELS][BWFE_g3_MaxIntID] = {
   {
      /* wfe channel 0 interrupts */
      BCHP_INT_ID_WFE_TIMER0_0,
      BCHP_INT_ID_WFE_TIMER1_0,
      BCHP_INT_ID_WFE_CORRDONE_0,
      BCHP_INT_ID_WFE_CLPDTR_PO_SLC0_0,
      BCHP_INT_ID_WFE_CLPDTR_PI_SLC0_0
   },
   {
      /* wfe channel 1 interrupts */
      BCHP_INT_ID_WFE_TIMER0_1,
      BCHP_INT_ID_WFE_TIMER1_1,
      BCHP_INT_ID_WFE_CORRDONE_1,
      BCHP_INT_ID_WFE_CLPDTR_PO_SLC0_1,
      BCHP_INT_ID_WFE_CLPDTR_PI_SLC0_1
   }
};


/******************************************************************************
 BWFE_P_InitConfig()
******************************************************************************/
BERR_Code BWFE_P_InitConfig(BWFE_ChannelHandle h)
{
   BWFE_g3_P_ChannelHandle *hChn = (BWFE_g3_P_ChannelHandle *)h->pImpl;
   BERR_Code retCode = BERR_SUCCESS;

   /* set default sample rate */
   hChn->adcSampleFreqKhz = h->pDevice->settings.xtalFreqKhz * 92;

   return retCode;
}


/******************************************************************************
 BWFE_P_GetRegisterAddress()
******************************************************************************/
BERR_Code BWFE_P_GetRegisterAddress(BWFE_ChannelHandle h, uint32_t reg, uint32_t *pAddr)
{
   BERR_Code retCode = BERR_SUCCESS;
   uint8_t channel = h->channel;
   *pAddr = reg;

   if (!h->bReference)
   {
      if ((reg >= BCHP_AIF_WB_SAT_CORE0_RSTCTL) && (reg <= BCHP_AIF_WB_SAT_CORE_INTR2_0_PCI_MASK_CLEAR))
      {
         /* AIF register access */
         *pAddr &= ~0x00007000;
         *pAddr |= (channel & 0x1) << 12;
      }
      else if ((reg >= BCHP_AIF_WB_SAT_ANA_RFFE0_WRITER01) && (reg <= BCHP_AIF_WB_SAT_ANA_SW_SPARE1))
      {
         /* ANA register access */
         switch (reg)
         {
            case BCHP_WFE_ANA_RFFE_WRITER01:
            case BCHP_WFE_ANA_RFFE_WRITER02:
            case BCHP_WFE_ANA_RFFE_WRITER03:
               *pAddr = reg + (channel & 0x1) * 0xC;
               break;
            case BCHP_WFE_ANA_ADC_CNTL0:
            case BCHP_WFE_ANA_ADC_CNTL1:
            case BCHP_WFE_ANA_ADC_CNTL2:
            case BCHP_WFE_ANA_ADC_CNTL3:
            case BCHP_WFE_ANA_ADC_CNTL4:
            case BCHP_WFE_ANA_ADC_CNTL5:
            case BCHP_WFE_ANA_ADC_CNTL6:
            case BCHP_WFE_ANA_ADC_CNTL7:
            case BCHP_WFE_ANA_ADC_CNTL8:
            case BCHP_WFE_ANA_ADC_CNTL9:
            case BCHP_WFE_ANA_ADC_CNTL10:
            case BCHP_WFE_ANA_ADC_CNTL11:
            case BCHP_WFE_ANA_ADC_CNTL12:
            case BCHP_WFE_ANA_ADC_CNTL13:
               *pAddr = reg + (channel & 0x1) * 0x38;
               break;
            case BCHP_WFE_ANA_SYS_CNTL:
            case BCHP_WFE_ANA_CLK_CTRL:
            case BCHP_WFE_ANA_PGA_GAIN:
               *pAddr = reg + (channel & 0x1) * 0x4;
               break;
         }
      }
   }
   else
   {
      /* no reference adc on 45308 */
      BDBG_ERR(("BWFE_GetRegisterAddress(%d): %08X cannot be reference adc!", h->channel, reg));
      return BERR_INVALID_PARAMETER;
   }

   /*BDBG_MSG(("GetRegisterAddress(%d): %08X -> %08X", h->channel, reg, *pAddr)); */
   return retCode;
}


/******************************************************************************
 BWFE_P_ReadRegister()
******************************************************************************/
BERR_Code BWFE_P_ReadRegister(
   BWFE_ChannelHandle h,      /* [in] BWFE channel handle */
   uint32_t           reg,    /* [in] address of register to read */
   uint32_t           *val    /* [out] contains data that was read */
)
{
   BWFE_g3_P_Handle *hDev = h->pDevice->pImpl;
   uint32_t addr;

   BWFE_P_GetRegisterAddress(h, reg, &addr);
   *val = BREG_Read32(hDev->hRegister, addr);

   return BERR_SUCCESS;
}


/******************************************************************************
 BWFE_P_WriteRegister()
******************************************************************************/
BERR_Code BWFE_P_WriteRegister(
   BWFE_ChannelHandle h,      /* [in] BWFE channel handle */
   uint32_t           reg,    /* [in] address of register to write */
   uint32_t           val     /* [in] contains data to be written */
)
{
   BWFE_g3_P_Handle *hDev = h->pDevice->pImpl;
   uint32_t addr;

   BWFE_P_GetRegisterAddress(h, reg, &addr);
   BREG_Write32(hDev->hRegister, addr, val);

   return BERR_SUCCESS;
}


/******************************************************************************
 BWFE_P_GetSliceRegisterAddress()
******************************************************************************/
BERR_Code BWFE_P_GetSliceRegisterAddress(BWFE_ChannelHandle h, uint8_t slice, uint32_t reg, uint32_t *pAddr)
{
   *pAddr = reg;

   BSTD_UNUSED(h);
   BDBG_ASSERT(slice < BWFE_NUM_SLICES);
   BSTD_UNUSED(reg);
   BSTD_UNUSED(pAddr);

   /* slice mappings */
   switch (reg)
   {
      case BCHP_WFE_CORE_DGSCTL_PI_SLC:
      case BCHP_WFE_CORE_DGSCTL_PO_SLC:
      case BCHP_WFE_CORE_DGSCLP_PI_SLC:
      case BCHP_WFE_CORE_DGSCLP_PO_SLC:
      case BCHP_WFE_CORE_DGSHIST_PI_SLC:
      case BCHP_WFE_CORE_DGSHIST_PO_SLC:
      case BCHP_WFE_CORE_DGSCLPCNT_PI_SLC:
      case BCHP_WFE_CORE_DGSCLPCNT_PO_SLC:
      case BCHP_WFE_CORE_DGSACCUM_PI_SLC:
      case BCHP_WFE_CORE_DGSACCUM_PO_SLC:
      case BCHP_WFE_CORE_DGSCOEFD_SLC:
      case BCHP_WFE_CORE_DGSCOEFA_SLC:
         *pAddr = reg + slice * 0x8;
         break;

      case BCHP_WFE_CORE_DGSLMS_SLC:
      case BCHP_WFE_CORE_DGSBGLMS_SLC:
      case BCHP_WFE_CORE_DGSLMSMU_SLC:
      case BCHP_WFE_CORE_DGSCOEFEN_SLC:
      case BCHP_WFE_CORE_MDACSA_SLC:
      case BCHP_WFE_CORE_MDACSADU_SLC:
      case BCHP_WFE_CORE_MDACSAOUT_SLC:
         *pAddr = reg + slice * 0x4;
         break;

      case BCHP_WFE_CORE_DGSLUT011_PI_SLC:
      case BCHP_WFE_CORE_DGSLUT010_PI_SLC:
      case BCHP_WFE_CORE_DGSLUT001_PI_SLC:
      case BCHP_WFE_CORE_DGSLUT000_PI_SLC:
      case BCHP_WFE_CORE_DGSLUT111_PI_SLC:
      case BCHP_WFE_CORE_DGSLUT110_PI_SLC:
      case BCHP_WFE_CORE_DGSLUT101_PI_SLC:
      case BCHP_WFE_CORE_DGSLUT100_PI_SLC:
      case BCHP_WFE_CORE_DGSLUT011_PO_SLC:
      case BCHP_WFE_CORE_DGSLUT010_PO_SLC:
      case BCHP_WFE_CORE_DGSLUT001_PO_SLC:
      case BCHP_WFE_CORE_DGSLUT000_PO_SLC:
      case BCHP_WFE_CORE_DGSLUT111_PO_SLC:
      case BCHP_WFE_CORE_DGSLUT110_PO_SLC:
      case BCHP_WFE_CORE_DGSLUT101_PO_SLC:
      case BCHP_WFE_CORE_DGSLUT100_PO_SLC:
         *pAddr = reg + slice * 0x40;
         break;

      case BCHP_WFE_CORE_CORRI0_DMX0_PI_SLC:
      case BCHP_WFE_CORE_CORRI1_DMX0_PI_SLC:
      case BCHP_WFE_CORE_CORRI0_DMX0_PO_SLC:
      case BCHP_WFE_CORE_CORRI1_DMX0_PO_SLC:
      case BCHP_WFE_CORE_CORRI0_DMX1_PI_SLC:
      case BCHP_WFE_CORE_CORRI1_DMX1_PI_SLC:
      case BCHP_WFE_CORE_CORRI0_DMX1_PO_SLC:
      case BCHP_WFE_CORE_CORRI1_DMX1_PO_SLC:
      case BCHP_WFE_CORE_CORRI0_DMX2_PI_SLC:
      case BCHP_WFE_CORE_CORRI1_DMX2_PI_SLC:
      case BCHP_WFE_CORE_CORRI0_DMX2_PO_SLC:
      case BCHP_WFE_CORE_CORRI1_DMX2_PO_SLC:
      case BCHP_WFE_CORE_CORRI0_DMX3_PI_SLC:
      case BCHP_WFE_CORE_CORRI1_DMX3_PI_SLC:
      case BCHP_WFE_CORE_CORRI0_DMX3_PO_SLC:
      case BCHP_WFE_CORE_CORRI1_DMX3_PO_SLC:
      case BCHP_WFE_CORE_CORRQ0_DMX0_PI_SLC:
      case BCHP_WFE_CORE_CORRQ1_DMX0_PI_SLC:
      case BCHP_WFE_CORE_CORRQ0_DMX0_PO_SLC:
      case BCHP_WFE_CORE_CORRQ1_DMX0_PO_SLC:
      case BCHP_WFE_CORE_CORRQ0_DMX1_PI_SLC:
      case BCHP_WFE_CORE_CORRQ1_DMX1_PI_SLC:
      case BCHP_WFE_CORE_CORRQ0_DMX1_PO_SLC:
      case BCHP_WFE_CORE_CORRQ1_DMX1_PO_SLC:
      case BCHP_WFE_CORE_CORRQ0_DMX2_PI_SLC:
      case BCHP_WFE_CORE_CORRQ1_DMX2_PI_SLC:
      case BCHP_WFE_CORE_CORRQ0_DMX2_PO_SLC:
      case BCHP_WFE_CORE_CORRQ1_DMX2_PO_SLC:
      case BCHP_WFE_CORE_CORRQ0_DMX3_PI_SLC:
      case BCHP_WFE_CORE_CORRQ1_DMX3_PI_SLC:
      case BCHP_WFE_CORE_CORRQ0_DMX3_PO_SLC:
      case BCHP_WFE_CORE_CORRQ1_DMX3_PO_SLC:
      case BCHP_WFE_CORE_CORRP0_DMX0_PI_SLC:
      case BCHP_WFE_CORE_CORRP1_DMX0_PI_SLC:
      case BCHP_WFE_CORE_CORRP0_DMX0_PO_SLC:
      case BCHP_WFE_CORE_CORRP1_DMX0_PO_SLC:
      case BCHP_WFE_CORE_CORRP0_DMX1_PI_SLC:
      case BCHP_WFE_CORE_CORRP1_DMX1_PI_SLC:
      case BCHP_WFE_CORE_CORRP0_DMX1_PO_SLC:
      case BCHP_WFE_CORE_CORRP1_DMX1_PO_SLC:
      case BCHP_WFE_CORE_CORRP0_DMX2_PI_SLC:
      case BCHP_WFE_CORE_CORRP1_DMX2_PI_SLC:
      case BCHP_WFE_CORE_CORRP0_DMX2_PO_SLC:
      case BCHP_WFE_CORE_CORRP1_DMX2_PO_SLC:
      case BCHP_WFE_CORE_CORRP0_DMX3_PI_SLC:
      case BCHP_WFE_CORE_CORRP1_DMX3_PI_SLC:
      case BCHP_WFE_CORE_CORRP0_DMX3_PO_SLC:
      case BCHP_WFE_CORE_CORRP1_DMX3_PO_SLC:
         *pAddr = reg + slice * 0x8;
         break;

      case BCHP_WFE_CORE_DGSEPCTL_SLC:
      case BCHP_WFE_CORE_REG_DGSEP_DMX0_PI_SLC_INT_WDATA:
      case BCHP_WFE_CORE_REG_DGSEP_DMX0_PO_SLC_INT_WDATA:
      case BCHP_WFE_CORE_REG_DGSEP_DMX1_PI_SLC_INT_WDATA:
      case BCHP_WFE_CORE_REG_DGSEP_DMX1_PO_SLC_INT_WDATA:
      case BCHP_WFE_CORE_REG_DGSEP_S1_DMX0_PI_SLC_ERRP:
      case BCHP_WFE_CORE_REG_DGSEP_S2_DMX0_PI_SLC_ERRP:
      case BCHP_WFE_CORE_REG_DGSEP_S1_DMX0_PO_SLC_ERRP:
      case BCHP_WFE_CORE_REG_DGSEP_S2_DMX0_PO_SLC_ERRP:
      case BCHP_WFE_CORE_REG_DGSEP_S1_DMX1_PI_SLC_ERRP:
      case BCHP_WFE_CORE_REG_DGSEP_S2_DMX1_PI_SLC_ERRP:
      case BCHP_WFE_CORE_REG_DGSEP_S1_DMX1_PO_SLC_ERRP:
      case BCHP_WFE_CORE_REG_DGSEP_S2_DMX1_PO_SLC_ERRP:
         *pAddr = reg + slice * 0x64;
         break;

      case BCHP_WFE_CORE_NRDCOCTL_PI_SLC:
      case BCHP_WFE_CORE_REG_NR_DCO_INT_WDATA_PI_SLC:
      case BCHP_WFE_CORE_NRDCOCTL_PO_SLC:
      case BCHP_WFE_CORE_REG_NR_DCO_INT_WDATA_PO_SLC:
      case BCHP_WFE_CORE_NRNOTCHCTL_PI_SLC:
      case BCHP_WFE_CORE_REG_NR_NOTCH_INT_WDATA_PI_SLC:
      case BCHP_WFE_CORE_NRNOTCHCTL_PO_SLC:
      case BCHP_WFE_CORE_REG_NR_NOTCH_INT_WDATA_PO_SLC:
         *pAddr = reg + slice * 0x10;
         break;

      case BCHP_WFE_CORE_NRAGCCTL_PI_SLC:
      case BCHP_WFE_CORE_REG_NR_AGC_LF_INT_WDATA_PI_SLC:
      case BCHP_WFE_CORE_REG_NR_AGC_LA_INT_WDATA_PI_SLC:
      case BCHP_WFE_CORE_NRAGCCTL_PO_SLC:
      case BCHP_WFE_CORE_REG_NR_AGC_LF_INT_WDATA_PO_SLC:
      case BCHP_WFE_CORE_REG_NR_AGC_LA_INT_WDATA_PO_SLC:
         *pAddr = reg + slice * 0x18;
         break;

      default:
         return BERR_INVALID_PARAMETER;
   }

   /* BDBG_MSG(("GetSliceRegisterAddress(%d) %08X -> %08X", slice, reg, *pAddr)); */
   return BERR_SUCCESS;
}


/******************************************************************************
 BWFE_P_ReadSliceRegister()
******************************************************************************/
BERR_Code BWFE_P_ReadSliceRegister(
   BWFE_ChannelHandle h,     /* [in] BWFE channel handle */
   uint8_t            slice, /* [in] slice number */
   uint32_t           reg,   /* [in] address of register to read */
   uint32_t           *val   /* [out] contains data that was read */
)
{
   BERR_Code retCode = BERR_SUCCESS;
   uint32_t addr;

   if (slice >= BWFE_NUM_SLICES)
      return BERR_INVALID_PARAMETER;

   /* look up slice register */
   BWFE_CHK_RETCODE(BWFE_P_GetSliceRegisterAddress(h, slice, reg, &addr));
   reg = addr;

   /* map register to channel */
   BWFE_CHK_RETCODE(BWFE_P_ReadRegister(h, reg, val));

   done:
   return retCode;
}


/******************************************************************************
 BWFE_P_WriteSliceRegister()
******************************************************************************/
BERR_Code BWFE_P_WriteSliceRegister(
   BWFE_ChannelHandle h,     /* [in] BWFE channel handle */
   uint8_t            slice, /* [in] slice number */
   uint32_t           reg,   /* [in] address of register to write */
   uint32_t           val    /* [in] contains data to be written */
)
{
   BERR_Code retCode = BERR_SUCCESS;
   uint32_t addr;

   if (slice >= BWFE_NUM_SLICES)
      return BERR_INVALID_PARAMETER;

   /* look up slice register */
   BWFE_CHK_RETCODE(BWFE_P_GetSliceRegisterAddress(h, slice, reg, &addr));
   reg = addr;

   /* map register to channel */
   BWFE_CHK_RETCODE(BWFE_P_WriteRegister(h, reg, val));

   done:
   return retCode;
}


/******************************************************************************
 BWFE_P_SetAdcSampleFreq()
******************************************************************************/
BERR_Code BWFE_P_SetAdcSampleFreq(BWFE_ChannelHandle h, uint32_t freqKhz)
{
   BERR_Code retCode = BERR_SUCCESS;
   BWFE_ChannelHandle hChn0 = (BWFE_ChannelHandle)(h->pDevice->pChannels[0]);
   uint32_t ndiv_int, val;
   uint8_t pdiv = 1;    /* default pdiv */
   uint8_t outsel = 1;  /* select Fdco by default */
   uint8_t i;
   bool bPllLocked = false;

#if 0
   switch (freqKhz)
   {
      case BWFE_DEF_FS_ADC_KHZ:
         /* Fs_adc = F_ref / pdiv * ndiv_int *2 */
         /* calculate ndiv_int from freqKhz, ndiv_int = Fs_adc / (F_ref * 2) */
         ndiv_int = (freqKhz >> 1) / BWFE_XTAL_FREQ_KHZ;
         break;

      case BWFE_DEF_FS_ADC_KHZ >> 1:
         /* Fs_adc = F_ref / pdiv * ndiv_int */
         /* calculate ndiv_int from freqKhz, ndiv_int = Fs_adc / F_ref */
         ndiv_int = freqKhz / BWFE_XTAL_FREQ_KHZ;
         outsel = 0;    /* select Fdco/2 */
         break;

      default:
         return BERR_INVALID_PARAMETER;
   }
#else
   /* round to nearest freq step */
   ndiv_int = freqKhz / BWFE_XTAL_FREQ_KHZ;
   ndiv_int = (ndiv_int + 1) >> 1;  /* round to nearest n */
   if ((ndiv_int < 45) || (ndiv_int > 52))
      return BERR_INVALID_PARAMETER;
#endif

   BWFE_P_ReadModifyWriteRegister(h, BCHP_WFE_ANA_PLL_CNTL0, ~0x00000F70, 0x000005B0); /* program ki and kp */
   BWFE_P_WriteRegister(h, BCHP_WFE_ANA_PLL_CNTL2, 0x0A040000);   /* boost lc tank current */

   /* program pdiv and ndiv for channel */
   BWFE_P_ReadModifyWriteRegister(h, BCHP_WFE_ANA_PLL_CNTL0, ~0x003C0000, (pdiv & 0xF) << 18);
   BWFE_P_WriteRegister(h, BCHP_WFE_ANA_PLL_CNTL1, ndiv_int & 0x3FF);

   /* select pll output */
   BWFE_P_ReadModifyWriteRegister(h, BCHP_WFE_ANA_PLL_CNTL0, ~0x00007000, (outsel & 0x7) << 12);

   /* disable pll isolation to clock chan and sds, and to read pll status */
   BWFE_P_AndRegister(h, BCHP_WFE_ANA_CLK_CTRL, ~0x00000040);

   /* check ADC0 pll status */
   BWFE_P_ReadRegister(hChn0, BCHP_WFE_ANA_PLL_STAT, &val);
   if ((val & 0x00002000) == 0)
   {
      /* power up ADC0 pll */
      BWFE_P_OrRegister(hChn0, BCHP_WFE_ANA_SYS_CNTL, 0x00000001); /* power on ldo pll */
      BWFE_P_OrRegister(hChn0, BCHP_WFE_ANA_SYS_CNTL, 0x00000002); /* power on pll */

      BKNI_Delay(30);   /* wait 21us or more */

      BWFE_P_OrRegister(hChn0, BCHP_WFE_ANA_SYS_CNTL, 0x00010000); /* release pll reset */
      BWFE_P_OrRegister(hChn0, BCHP_WFE_ANA_SYS_CNTL, 0x00020000); /* release postdiv reset */

      for (i = 0; i < 20; i++)
      {
         /* wait for pll lock */
         BKNI_Delay(50);

         /* check pll status */
         BWFE_P_ReadRegister(hChn0, BCHP_WFE_ANA_PLL_STAT, &val);
         if (val & 0x00002000)
         {
            bPllLocked = true;
            break;
         }
      }

      if (!bPllLocked)
      {
         /* pll not locked */
         BDBG_WRN(("ADC0 pll NOT locked!"));
      }

      /* enable post-div channel 5 to clock CHAN registers */
      BWFE_P_AndRegister(hChn0, BCHP_WFE_ANA_PLL_CNTL5, ~0x00000020);
   }

   return retCode;
}


/******************************************************************************
 BWFE_P_GetAdcSampleFreq()
******************************************************************************/
BERR_Code BWFE_P_GetAdcSampleFreq(BWFE_ChannelHandle h, uint32_t *freqKhz)
{
   BERR_Code retCode = BERR_SUCCESS;
   BWFE_g3_P_ChannelHandle *hChn = (BWFE_g3_P_ChannelHandle *)h->pImpl;
   uint32_t val, pdiv, ndiv_int;

   /* read pdiv */
   BWFE_P_ReadRegister(h, BCHP_WFE_ANA_PLL_CNTL0, &val);
   pdiv = (val >> 18) & 0xF;

   /* read ndiv */
   BWFE_P_ReadRegister(h, BCHP_WFE_ANA_PLL_CNTL1, &val);
   ndiv_int = val & 0x3FF;

   /* Fs_adc = F_ref / pdiv * ndiv_int *2 */
   *freqKhz = (BWFE_XTAL_FREQ_KHZ * (ndiv_int << 1) + pdiv/2) / pdiv;   /* round by adding pdiv/2 */

   /* check pll output select */
   BWFE_P_ReadRegister(h, BCHP_WFE_ANA_PLL_CNTL0, &val);
   if ((val & 0x00007000) == 0)
   {
      *freqKhz = *freqKhz + 1;   /* round */
      *freqKhz >>= 1;
   }
   else if ((val & 0x00007000) == 0x00005000)
   {
      *freqKhz = *freqKhz + 2;   /* round */
      *freqKhz >>= 2;
   }

   hChn->adcSampleFreqKhz = *freqKhz;
   return retCode;
}


/******************************************************************************
 BWFE_P_SetDpmPilotFreq()
******************************************************************************/
BERR_Code BWFE_P_SetDpmPilotFreq(BWFE_ChannelHandle h, uint32_t freqKhz)
{
#if 0
   BERR_Code retCode = BERR_SUCCESS;
   BWFE_g3_P_ChannelHandle *hChn = (BWFE_g3_P_ChannelHandle *)h->pImpl;
   uint32_t loChan, val, freqRefKhz;
   uint32_t n_xtal, m_xtal, gcd;
   uint16_t n;
   uint8_t p, m, outsel;

   /* loPLL1 is the 1st stage PLL that generates CH5 CMOS reference shared between 2nd stage loPLL0 and loPLL2 */
   p = 1;
   n = 56;
   m = 59;
   outsel = 0; /* select CH5 postdiv output as output of master PLL */

   /* calculate stage1 reference freq = f_xtal / pdiv * ndiv_int / mdiv_ch5 */
   freqRefKhz = ((BWFE_XTAL_FREQ_KHZ << 1) * n) / p;
   freqRefKhz = ((freqRefKhz / m) + 1) >> 1;    /* round */

   /* set loPLL1 pdiv, ndiv, and outsel */
   BWFE_P_LoWriteReg(1, BCHP_PLL_LOD2_0_PLL_DIV, ((p & 0xF) << 10) | (n & 0x1FF));
   BWFE_P_LoWriteReg(1, BCHP_PLL_LOD2_0_PLL_OUTSEL_SEL, outsel);

   /* set loPLL1 mdiv */
   BWFE_P_LoReadReg(1, BCHP_PLL_LOD2_0_PLL_CHANNEL_CTRL_CH_5, &val);
   val &= ~0x000001FF;
   val |= m << 1;
   BWFE_P_LoWriteReg(1, BCHP_PLL_LOD2_0_PLL_CHANNEL_CTRL_CH_5, val);

   /* power up loPLL1 to 47.669MHz */
   BWFE_P_LoPowerUp(1);

   if (h->channel >= BWFE_NUM_CHANNELS/2)
      loChan = 0; /* use loPLL0 for ADC4-7 */
   else
      loChan = 2; /* use loPLL2 for ADC0-3 */

   /* search for target dpm freq based on stage1 reference, expect p=m=1, n=52, outsel=0 */
   retCode = BWFE_P_LoSearchDiv(freqKhz, freqRefKhz, &p, &n, &m, &outsel);
   /*BKNI_Printf(">>> p=%d, m=%d, n=%d, outsel=%d\n", p, m, n, outsel);*/
   if (retCode != BERR_SUCCESS)
      return retCode;

   /* set pdiv, ndiv, and outsel */
   /* To select FVCO/3 output, OUTPUT_SEL = 4 (first MUX), TEST_SEL = 5 (second MUX) */
   /* To select CH5 postdiv output, OUTPUT_SEL = 0 (first MUX), TEST_SEL = 3 (second MUX) */
   BWFE_P_LoWriteReg(loChan, BCHP_PLL_LOD2_0_PLL_DIV, ((p & 0xF) << 10) | (n & 0x1FF));
   BWFE_P_LoWriteReg(loChan, BCHP_PLL_LOD2_0_PLL_OUTSEL_SEL, outsel);

   /* select ch5 post-div, enable test buffer, power up loPLL1 */
   BWFE_P_LoWriteReg(loChan, BCHP_PLL_LOD2_0_PLL_TEST, 0x00000007);

   /* calculate QDDFS ratio */
   gcd = BWFE_P_GCF(BWFE_DEF_FS_ADC_KHZ, BWFE_XTAL_FREQ_KHZ);
   n_xtal = BWFE_DEF_FS_ADC_KHZ / gcd;
   m_xtal = BWFE_XTAL_FREQ_KHZ / gcd;

   /* M = N2 x N1 = 2912 */
   /* N = 100 x Mdiv1 x Mdiv2 = 5900 */
   hChn->dpmQddfsM = 56 * n * BWFE_LIC_L;
   hChn->dpmQddfsN = n_xtal * 59 * m;

   /* remove common divider */
   gcd = BWFE_P_GCF(hChn->dpmQddfsM, hChn->dpmQddfsN);
   if (gcd > 1)
   {
      hChn->dpmQddfsM /= gcd;
      hChn->dpmQddfsN /= gcd;
   }
   hChn->dpmQddfsM = hChn->dpmQddfsM % hChn->dpmQddfsN;
   /*BKNI_Printf("BWFE_P_SetDpmPilotFreq(%d KHz): dpmQddfsN=%d, dpmQddfsM=%d\n", freqKhz, hChn->dpmQddfsN, hChn->dpmQddfsM);*/

   return retCode;
#else
   BSTD_UNUSED(h);
   BSTD_UNUSED(freqKhz);
   return BERR_NOT_SUPPORTED;
#endif
}


/******************************************************************************
 BWFE_P_GetDpmPilotFreq()
******************************************************************************/
BERR_Code BWFE_P_GetDpmPilotFreq(BWFE_ChannelHandle h, uint32_t *freqKhz)
{
#if 0
   BWFE_g3_P_ChannelHandle *hChn = (BWFE_g3_P_ChannelHandle *)h->pImpl;
   uint32_t loChan, val;
   uint16_t ndiv;
   uint8_t pdiv, mdiv, outsel;

   /* loPLL1 is the 1st stage PLL that generates CH5 CMOS reference shared between 2nd stage loPLL0 and loPLL2 */
   BWFE_P_LoReadReg(1, BCHP_PLL_LOD2_0_PLL_DIV, &val);
   pdiv = (val >> 10) & 0xF;
   ndiv = val & 0x1FF;

   BWFE_P_LoReadReg(1, BCHP_PLL_LOD2_0_PLL_OUTSEL_SEL, &val);
   outsel = val & 0x7;
   BWFE_P_LoReadReg(1, BCHP_PLL_LOD2_0_PLL_CHANNEL_CTRL_CH_5, &val);
   mdiv = (val >> 1) & 0xFF;

   /* calculate stage1 reference freq = f_xtal / pdiv * ndiv_int / mdiv_ch5 */
   *freqKhz = ((BWFE_XTAL_FREQ_KHZ << 1) * ndiv) / pdiv;
   *freqKhz = ((*freqKhz / mdiv) + 1) >> 1;  /* round */

   if (h->channel >= BWFE_NUM_CHANNELS/2)
      loChan = 0; /* use loPLL0 for ADC4-7 */
   else
      loChan = 2; /* use loPLL2 for ADC0-3 */

   BWFE_P_LoReadReg(loChan, BCHP_PLL_LOD2_0_PLL_DIV, &val);
   pdiv = (val >> 10) & 0xF;
   ndiv = val & 0x1FF;

   BWFE_P_LoReadReg(loChan, BCHP_PLL_LOD2_0_PLL_OUTSEL_SEL, &val);
   outsel = val & 0x7;
   BWFE_P_LoReadReg(loChan, BCHP_PLL_LOD2_0_PLL_CHANNEL_CTRL_CH_5, &val);
   mdiv = (val >> 1) & 0xFF;
   /*BKNI_Printf("$$$%d: p=%d, m=%d, n=%d, outsel=%d\n", loChan, pdiv, mdiv, ndiv, outsel);*/

   *freqKhz = ((*freqKhz << 1) * ndiv) / pdiv;
   if (outsel == 0)
      *freqKhz >>= 1;
   else if (outsel == 4)
      *freqKhz /= 3;
   else if (outsel == 5)
      *freqKhz /= mdiv;

   hChn->dpmPilotFreqKhz = *freqKhz;
   return BERR_SUCCESS;
#else
   BSTD_UNUSED(h);
   BSTD_UNUSED(freqKhz);
   return BERR_NOT_SUPPORTED;
#endif
}


/******************************************************************************
 BWFE_P_EnableDpmPilot()
******************************************************************************/
BERR_Code BWFE_P_EnableDpmPilot(BWFE_ChannelHandle h)
{
#if 0
   uint32_t loChan;

   if (h->channel >= BWFE_NUM_CHANNELS/2)
      loChan = 0; /* use loPLL0 for ADC4-7 */
   else
      loChan = 2; /* use loPLL2 for ADC0-3 */

   BWFE_P_LoPowerUp(loChan);

   /* inject dpm tone to adc input */
   BWFE_P_OrRegister(h, BCHP_WFE_ANA_RFFE_WRITER01, 0x00000010);

   return BERR_SUCCESS;
#else
   BSTD_UNUSED(h);
   return BERR_NOT_SUPPORTED;
#endif
}


/******************************************************************************
 BWFE_P_DisableDpmPilot()
******************************************************************************/
BERR_Code BWFE_P_DisableDpmPilot(BWFE_ChannelHandle h)
{
#if 0
   uint32_t loChan;

   if (h->channel >= BWFE_NUM_CHANNELS/2)
      loChan = 0; /* use loPLL0 for ADC4-7 */
   else
      loChan = 2; /* use loPLL2 for ADC0-3 */

   BWFE_P_LoPowerDown(loChan);

   /* disable dpm tone injection */
   BWFE_P_AndRegister(h, BCHP_WFE_ANA_RFFE_WRITER01, ~0x00000010);

   return BERR_SUCCESS;
#else
   BSTD_UNUSED(h);
   return BERR_NOT_SUPPORTED;
#endif
}


/******************************************************************************
 BWFE_P_InitAdc()
******************************************************************************/
BERR_Code BWFE_P_InitAdc(BWFE_ChannelHandle h)
{
   BWFE_ChannelHandle hAdjChn;
   BWFE_ChannelHandle hPllChn = h;
   BWFE_g3_P_ChannelHandle *hChn = (BWFE_g3_P_ChannelHandle *)h->pImpl;
   uint32_t val;
   uint8_t i;
   bool bPllLocked = false;

   /* must control pll with even channel */
   if (h->channel & 1)
      hPllChn = h->pDevice->pChannels[h->channel - 1];

   /* determine if adjacent adc is on since pll shared */
   if (h->channel & 1)
      hAdjChn = h->pDevice->pChannels[h->channel - 1];
   else
      hAdjChn = h->pDevice->pChannels[h->channel + 1];

   /* hybrid settings */
   BWFE_P_WriteRegister(h, BCHP_WFE_ANA_ADC_CNTL0, 0x00000002);   /* was &h2 (4552 uses &h402) */
   BWFE_P_WriteRegister(h, BCHP_WFE_ANA_ADC_CNTL1, 0x5B492285);   /* was 5B492245  --> ext current = 100% (was 80%) */

   /* chip-specific adc settings for high and low sample rates */
   if (hChn->adcSampleFreqKhz > 4000000)
      BWFE_P_WriteRegister(h, BCHP_WFE_ANA_ADC_CNTL2, 0x55564924);
   else
      BWFE_P_WriteRegister(h, BCHP_WFE_ANA_ADC_CNTL2, 0x555649A6);

   BWFE_P_WriteRegister(h, BCHP_WFE_ANA_ADC_CNTL3, 0x14014000);
   BWFE_P_WriteRegister(h, BCHP_WFE_ANA_ADC_CNTL4, 0x06E1B6E0);
   BWFE_P_WriteRegister(h, BCHP_WFE_ANA_ADC_CNTL5, 0x45480000);   /* (orig: 02008000) 4552: both R5 and R8 are set to 22008008 */
   BWFE_P_WriteRegister(h, BCHP_WFE_ANA_ADC_CNTL6, 0x00000000);   /* M2 CAL  */
   BWFE_P_WriteRegister(h, BCHP_WFE_ANA_ADC_CNTL7, 0x1801001F);
   BWFE_P_WriteRegister(h, BCHP_WFE_ANA_ADC_CNTL8, 0x0A952A54);   /* (orig: 22008008) 4552: both R5 and R8 are set to 22008008 */
   BWFE_P_WriteRegister(h, BCHP_WFE_ANA_ADC_CNTL9, 0x00000000);
   BWFE_P_WriteRegister(h, BCHP_WFE_ANA_ADC_CNTL10, 0x77777777);  /* default coarse-fine timing */
   BWFE_P_WriteRegister(h, BCHP_WFE_ANA_ADC_CNTL11, 0x45480000);  /* ISBUF in regulator mode */
   BWFE_P_WriteRegister(h, BCHP_WFE_ANA_ADC_CNTL12, 0x00006020);  /* 6020 to set CK5G_dly_cntl_1p5 = 1000 */
   BWFE_P_WriteRegister(h, BCHP_WFE_ANA_ADC_CNTL13, 0x0A952A54);

#if 0
   /* low power adc settings */
   BWFE_P_WriteRegister(h, BCHP_WFE_ANA_ADC_CNTL1, 0x5B452285);   /* LDO amplitude = 950mV (Def=1V) */
   BWFE_P_WriteRegister(h, BCHP_WFE_ANA_ADC_CNTL3, 0x10014000);   /* REFBUF current = min  (incorrect RDB description) */
   BWFE_P_WriteRegister(h, BCHP_WFE_ANA_ADC_CNTL2, 0x555649A4);   /* MDAC=6 is ADC0_CNTL2[8:6] (incorrect RDB description) */

   BWFE_P_WriteRegister(h, BCHP_WFE_ANA_ADC_CNTL11, 0x49680000);  /* ISBUF1 REG = 1.15V, ISBUF1 half current */
   BWFE_P_WriteRegister(h, BCHP_WFE_ANA_ADC_CNTL5, 0x49680000);   /* ISBUF0 REG = 1.15V, ISBUF0 half current */

   BWFE_P_WriteRegister(h, BCHP_WFE_ANA_ADC_CNTL12, 0x00002024);  /* Tnov MDAC = 1 (Def=3), SAR Tearly = 74ps (Def=87ps) */
#endif

   BWFE_P_OrRegister(h, BCHP_WFE_ANA_CLK_CTRL, 0x00000031); /* enable wbadc, misc, mdac clock */

   if (hAdjChn->bEnabled)
      BWFE_P_AndRegister(h, BCHP_WFE_ANA_SYS_CNTL, ~0x03FCFFFC); /* do not touch pll if adj adc on */
   else
      BWFE_P_AndRegister(h, BCHP_WFE_ANA_SYS_CNTL, ~0x03FFFFFF); /* default power up state */

   BWFE_P_OrRegister(hPllChn, BCHP_WFE_ANA_SYS_CNTL, 0x00000001); /* power on ldo pll */
   BWFE_P_OrRegister(hPllChn, BCHP_WFE_ANA_SYS_CNTL, 0x00000002); /* power on pll */

   BWFE_P_OrRegister(h, BCHP_WFE_ANA_SYS_CNTL, 0x00000004); /* power on bandgap */
   BWFE_P_OrRegister(h, BCHP_WFE_ANA_SYS_CNTL, 0x00000008); /* power on adc clock */
   BWFE_P_OrRegister(h, BCHP_WFE_ANA_SYS_CNTL, 0x00000010); /* power up ADC */

   BKNI_Delay(30);   /* wait 21us or more */

   BWFE_P_OrRegister(hPllChn, BCHP_WFE_ANA_SYS_CNTL, 0x00010000); /* release pll reset */
   BWFE_P_OrRegister(hPllChn, BCHP_WFE_ANA_SYS_CNTL, 0x00020000); /* release postdiv reset */

   for (i = 0; i < 20; i++)
   {
      /* wait for pll lock */
      BKNI_Delay(50);

      /* check pll status */
      BWFE_P_ReadRegister(h, BCHP_WFE_ANA_PLL_STAT, &val);
      if (val & 0x00002000)
      {
         bPllLocked = true;
         break;
      }
   }

   if (!bPllLocked)
   {
      /* pll not locked */
      BDBG_WRN(("ADC%d pll NOT locked!", h->channel));
   }

   BWFE_P_OrRegister(h, BCHP_WFE_ANA_SYS_CNTL, 0x00040000); /* release ADC reset */
   BWFE_P_OrRegister(h, BCHP_WFE_ANA_SYS_CNTL, 0x00080000); /* release clkgen reset */
   BWFE_P_OrRegister(h, BCHP_WFE_ANA_SYS_CNTL, 0x00100000); /* release DGS reset */

   /* wait 1ms for ADC power up */
   BKNI_Sleep(1);

   /* enable ADC output, use positive edge */
   BWFE_P_OrRegister(h, BCHP_WFE_CORE_HDOFFCTL0, 0x00200000);
   BWFE_P_OrRegister(h, BCHP_WFE_CORE_DOUTCTL, 0x00000001);

   return BERR_SUCCESS;
}


/******************************************************************************
 BWFE_P_ShutdownAdc()
******************************************************************************/
BERR_Code BWFE_P_ShutdownAdc(BWFE_ChannelHandle h)
{
   BWFE_ChannelHandle hAdjChn;
   BWFE_ChannelHandle hPllChn = h;

   if (BWFE_P_IsAdcOn(h))
   {
      /* gate off adc output */
      BWFE_P_AndRegister(h, BCHP_WFE_CORE_HDOFFCTL0, ~0x00200000);
      BWFE_P_AndRegister(h, BCHP_WFE_CORE_DOUTCTL, ~0x00000001);
   }

   /* must control pll with even channel */
   if (h->channel & 1)
      hPllChn = h->pDevice->pChannels[h->channel - 1];

   /* determine if adjacent adc is on since shared pll */
   if (h->channel & 1)
      hAdjChn = h->pDevice->pChannels[h->channel - 1];
   else
      hAdjChn = h->pDevice->pChannels[h->channel + 1];

   /* reset and power off shared pll if adj adc off, cannot power down adc0 pll */
   if ((!hAdjChn->bEnabled) && (hPllChn->channel != 0))
      BWFE_P_AndRegister(hPllChn, BCHP_WFE_ANA_SYS_CNTL, ~0x00030003);

   /* power down ADC and hold in reset */
   BWFE_P_AndRegister(h, BCHP_WFE_ANA_SYS_CNTL, ~0x00080010);

   /* disable wbadc, misc, corr, and mdac clock */
   BWFE_P_AndRegister(h, BCHP_WFE_ANA_CLK_CTRL, ~0x00000039);

   return BERR_SUCCESS;
}


/******************************************************************************
 BWFE_P_IsAdcOn()
******************************************************************************/
bool BWFE_P_IsAdcOn(BWFE_ChannelHandle h)
{
   uint32_t val;

   BWFE_P_ReadRegister(h, BCHP_WFE_ANA_SYS_CNTL, &val);
   if (val & 0x10)
      h->bEnabled = true;
   else
      h->bEnabled = false;

   return h->bEnabled;
}


#ifndef BWFE_EXCLUDE_SPECTRUM_ANALYZER
/******************************************************************************
 BWFE_P_CalcCorrPower()
******************************************************************************/
BERR_Code BWFE_P_CalcCorrPower(BWFE_ChannelHandle h, int32_t *corrI, int32_t *corrQ, uint32_t *corrPowerDb)
{
   BWFE_g3_P_ChannelHandle *hChn = (BWFE_g3_P_ChannelHandle *)h->pImpl;

   uint32_t corrPower;
   int32_t vec[2], phase, tmp_i, tmp_q;
   int32_t cos_1, sin_1, cos_k, sin_k, cos_k1, sin_k1, cos_k2, sin_k2;
   uint32_t P_hi, P_lo, Q_hi, Q_lo;
   uint32_t R1_hi, R1_lo, R2_hi, R2_lo;
   uint8_t k;

   /* theta = Fc / Fadc */
   BMTH_HILO_32TO64_Mul((hChn->corrFreqHz / 500), 2147483648UL, &P_hi, &P_lo);   /* Fc scaled up by 2^32 */
   BMTH_HILO_64TO64_Div32(P_hi, P_lo, hChn->adcSampleFreqKhz, &Q_hi, &Q_lo);  /* div by Fadc */
   phase = Q_lo;
   BWFE_P_CordicRotationMode(vec, phase, true);
   cos_1 = vec[0];
   sin_1 = vec[1];

   /* phase0: corr[0] * exp(0*j*2pi*fc/fs) ... no rotation, just init I & Q total  */
   /* phase1: corr[1] * exp( 1*j*2pi*fc/fs), phase 15: corr[15] * exp(-1*j*2pi*fc/fs) ... negate sin term */
   /* phase2: corr[2] * exp(2*j*2pi*fc/fs), phase 14: corr[15] * exp(-2*j*2pi*fc/fs) ... negate sin term */
   /* phase3: corr[3] * exp(3*j*2pi*fc/fs), phase 13: corr[15] * exp(-3*j*2pi*fc/fs) ... negate sin term */
   /* phase4: corr[4] * exp(4*j*2pi*fc/fs), phase 12: corr[15] * exp(-4*j*2pi*fc/fs) ... negate sin term */
   /* phase5: corr[5] * exp(5*j*2pi*fc/fs), phase 11: corr[15] * exp(-5*j*2pi*fc/fs) ... negate sin term */
   /* phase6: corr[6] * exp(6*j*2pi*fc/fs), phase 10: corr[15] * exp(-6*j*2pi*fc/fs) ... negate sin term */
   /* phase7: corr[7] * exp(7*j*2pi*fc/fs), phase 9: corr[15] * exp(-7*j*2pi*fc/fs) ... negate sin term */
   /* phase8: corr[8] * exp(8*j*2pi*fc/fs) */

   /* k = 0, 1, -1 */
   tmp_i = corrI[7];
   /* tmp_i += ((corrI[6] + corrI[8]) * cos_k + (corrQ[6] - corrQ[8]) * sin_k) >> BWFE_CORDIC_SHIFT */
   BWFE_P_SumThenMultiply(corrI[6], corrI[8], cos_1, &R1_hi, &R1_lo);
   BWFE_P_SumThenMultiply(corrQ[6], -corrQ[8], sin_1, &R2_hi, &R2_lo);
   BMTH_HILO_64TO64_Add(R1_hi, R1_lo, R2_hi, R2_lo, &P_hi, &P_lo);
   tmp_i += (int32_t)((P_hi << (32 - BWFE_CORDIC_SHIFT)) | (P_lo >> BWFE_CORDIC_SHIFT));  /* undo cordic scale */

   tmp_q = corrQ[7];
   /* tmp_q = ((corrQ[8] + corrQ[6]) * cos_k + (corrI[8] - corrI[6]) * sin_k) >> BWFE_CORDIC_SHIFT */
   BWFE_P_SumThenMultiply(corrQ[8], corrQ[6], cos_1, &R1_hi, &R1_lo);
   BWFE_P_SumThenMultiply(corrI[8], -corrI[6], sin_1, &R2_hi, &R2_lo);
   BMTH_HILO_64TO64_Add(R1_hi, R1_lo, R2_hi, R2_lo, &P_hi, &P_lo);
   tmp_q += (int32_t)((P_hi << (32 - BWFE_CORDIC_SHIFT)) | (P_lo >> BWFE_CORDIC_SHIFT));  /* undo cordic scale */

   /* initial values for chebyshev */
   cos_k2 = 1 * BWFE_CORDIC_SCALE;  /* cos(k-2)x */
   sin_k2 = 0;                      /* sin(k-2)x */
   cos_k1 = cos_1;                  /* cos(k-1)x */
   sin_k1 = sin_1;                  /* sin(k-1)x */

   /*BDBG_MSG(("Fc=%d / Fs=%d000", h->corrFreqHz, h->pDevice->adcSampleFreqKhz));*/
   /*BDBG_MSG(("cos_1=%08X | sin_1=%08X", cos_1, sin_1));*/

   /* use chebyshev method to calculate k = 2, 3, 4, 5, 6, 7, -7, -6, -5, -4, -3, -2 */
   for (k = 2; k < BWFE_LIC_L / 2; k++)
   {
      /* cos(kx) = 2 * cos(x) * cos(k-1)x - cos(k-2)x */
      BWFE_P_SumThenMultiply(0, cos_1, cos_k1, &R1_hi, &R1_lo);
      cos_k = (R1_hi << (32 - BWFE_CORDIC_SHIFT + 1)) | (R1_lo >> (BWFE_CORDIC_SHIFT - 1));  /* undo double cordic scale, multiply by 2 */
      cos_k -= cos_k2;

      /* sin(kx) = 2 * cos(x) * sin(k-1)x - sin(k-2)x */
      BWFE_P_SumThenMultiply(0, cos_1, sin_k1, &R2_hi, &R2_lo);
      sin_k = (R2_hi << (32 - BWFE_CORDIC_SHIFT + 1)) | (R2_lo >> (BWFE_CORDIC_SHIFT - 1));  /* undo double cordic scale, multiply by 2 */
      sin_k -= sin_k2;

      /*BDBG_MSG(("cos_%d=%08X | sin_%d=%08X", k, cos_k, k, sin_k));*/

      /* rotate by phase */
      /* tmp_i += (corrI[k] + corrI[BWFE_LIC_L - k]) * cos_k + (corrQ[BWFE_LIC_L - k] - corrQ[k]) * sin_k */
      BWFE_P_SumThenMultiply(corrI[7-k], corrI[7+k], cos_k, &R1_hi, &R1_lo);
      BWFE_P_SumThenMultiply(corrQ[7-k], -corrQ[7+k], sin_k, &R2_hi, &R2_lo);
      BMTH_HILO_64TO64_Add(R1_hi, R1_lo, R2_hi, R2_lo, &P_hi, &P_lo);
      tmp_i += (int32_t)((P_hi << (32 - BWFE_CORDIC_SHIFT)) | (P_lo >> BWFE_CORDIC_SHIFT));  /* undo cordic scale */

      /* tmp_q += (corrQ[k] + corrQ[BWFE_LIC_L - k]) * cos_k + (corrI[k] - corrI[BWFE_LIC_L - k]) * sin_k */
      BWFE_P_SumThenMultiply(corrQ[7+k], corrQ[7-k], cos_k, &R1_hi, &R1_lo);
      BWFE_P_SumThenMultiply(corrI[7+k], -corrI[7-k], sin_k, &R2_hi, &R2_lo);
      BMTH_HILO_64TO64_Add(R1_hi, R1_lo, R2_hi, R2_lo, &P_hi, &P_lo);
      tmp_q += (int32_t)((P_hi << (32 - BWFE_CORDIC_SHIFT)) | (P_lo >> BWFE_CORDIC_SHIFT));  /* undo cordic scale */

      /* setup next iteration */
      cos_k2 = cos_k1;
      sin_k2 = sin_k1;
      cos_k1 = cos_k;
      sin_k1 = sin_k;
   }

   /* k = 8 */
   /* cos(8x) = 2 * cos(x) * cos(7x) - cos(6x) */
   BWFE_P_SumThenMultiply(0, cos_1, cos_k1, &R1_hi, &R1_lo);
   cos_k = (R1_hi << (32 - BWFE_CORDIC_SHIFT + 1)) | (R1_lo >> (BWFE_CORDIC_SHIFT - 1));  /* undo double cordic scale, multiply by 2 */
   cos_k -= cos_k2;

   /* sin(8x) = 2 * cos(x) * sin(7)x - sin(6)x */
   BWFE_P_SumThenMultiply(0, cos_1, sin_k1, &R2_hi, &R2_lo);
   sin_k = (R2_hi << (32 - BWFE_CORDIC_SHIFT + 1)) | (R2_lo >> (BWFE_CORDIC_SHIFT - 1));  /* undo double cordic scale, multiply by 2 */
   sin_k -= sin_k2;

   /*BDBG_MSG(("cos_8=%08X | sin_8=%08X", cos_k, sin_k));*/

   /* tmp_i += corrI[15] * cos_k - corrQ[15] * sin_k */
   BWFE_P_SumThenMultiply(0, corrI[15], cos_k, &R1_hi, &R1_lo);
   BWFE_P_SumThenMultiply(0, -corrQ[15], sin_k, &R2_hi, &R2_lo);
   BMTH_HILO_64TO64_Add(R1_hi, R1_lo, R2_hi, R2_lo, &P_hi, &P_lo);
   tmp_i += (int32_t)((P_hi << (32 - BWFE_CORDIC_SHIFT)) | (P_lo >> BWFE_CORDIC_SHIFT));  /* undo cordic scale */

   /* tmp_q += corrI[8] * sin_k + corrQ[8] * cos_k */
   BWFE_P_SumThenMultiply(0, corrQ[15], cos_k, &R1_hi, &R1_lo);
   BWFE_P_SumThenMultiply(0, corrI[15], sin_k, &R2_hi, &R2_lo);
   BMTH_HILO_64TO64_Add(R1_hi, R1_lo, R2_hi, R2_lo, &P_hi, &P_lo);
   tmp_q += (int32_t)((P_hi << (32 - BWFE_CORDIC_SHIFT)) | (P_lo >> BWFE_CORDIC_SHIFT));  /* undo cordic scale */

   /* corrPower = (tmp_i * tmp_i + tmp_q * tmp_q) */ /*TBD check scaling: scale by correlation period? */
   BWFE_P_SumThenMultiply(0, tmp_i, tmp_i, &R1_hi, &R1_lo);
   BWFE_P_SumThenMultiply(0, tmp_q, tmp_q, &R2_hi, &R2_lo);
   BMTH_HILO_64TO64_Add(R1_hi, R1_lo, R2_hi, R2_lo, &P_hi, &P_lo);
   corrPower = P_hi;

   /*BDBG_MSG(("tmp_i=%08X | tmp_q=%08X -> P=%08X", tmp_i, tmp_q, P_hi));*/

   /* BDBG_MSG(("tmp_i=%08X, tmp_q=%08X, corrPower=%08X", tmp_i, tmp_q, corrPower)); */
   *corrPowerDb = BMTH_2560log10(corrPower);

   return BERR_SUCCESS;
}

#endif

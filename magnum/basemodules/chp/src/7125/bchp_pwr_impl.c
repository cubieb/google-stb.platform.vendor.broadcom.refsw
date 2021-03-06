/***************************************************************************
 *     Copyright (c) 2006-2013, Broadcom Corporation
 *     All Rights Reserved
 *     Confidential Property of Broadcom Corporation
 *
 *  THIS SOFTWARE MAY ONLY BE USED SUBJECT TO AN EXECUTED SOFTWARE LICENSE
 *  AGREEMENT  BETWEEN THE USER AND BROADCOM.  YOU HAVE NO RIGHT TO USE OR
 *  EXPLOIT THIS MATERIAL EXCEPT SUBJECT TO THE TERMS OF SUCH AN AGREEMENT.
 *
 * $brcm_Workfile: $
 * $brcm_Revision: $
 * $brcm_Date:
 *
 * Module Description:
 *
 * Revision History:
 *
 * $brcm_Log: $
 *
 ***************************************************************************/
/***************************************************************
*
* This file maps the power resource control to register writes.
* The templates are auto-generated by generate_chp_pwr.pl,
* but must be filled-in manually.
*
***************************************************************/

#include "bchp.h"
#include "bchp_priv.h"
#include "bdbg.h"
#include "bkni.h"
#include "breg_mem.h"

#include "bchp_clkgen.h"
#include "bchp_avd_rgr_0.h"
#include "bchp_aio_misc.h"
#include "bchp_xpt_xmemif.h"
#include "bchp_hdmi_tx_phy.h"
#include "bchp_vcxo_ctl_misc.h"
#include "bchp_smartcard_pll.h"

BDBG_MODULE(BCHP_PWR_IMPL);

static void BCHP_PWR_P_HW_AVD0_Control(BCHP_Handle handle, bool activate)
{
    uint32_t mask;
    BDBG_MSG(("HW_AVD0: %s", activate?"on":"off"));

    if (activate) {
        /* PWRDN_CLOCK_108_CG_AVD GISB clock*/
        mask = BCHP_CLKGEN_AVD_CLK_PM_CTRL_DIS_CLK_108_MASK;
        BREG_AtomicUpdate32(handle->regHandle, BCHP_CLKGEN_AVD_CLK_PM_CTRL, mask, 0);

        /* PWRDN_CLOCK_216_CG_AVD SCB Memory clock */
        mask = BCHP_CLKGEN_AVD_CLK_PM_CTRL_DIS_CLK_216_MASK;
        BREG_AtomicUpdate32(handle->regHandle, BCHP_CLKGEN_AVD_CLK_PM_CTRL, mask, 0);

        /* AVD Coreclock */
        mask = BCHP_CLKGEN_AVD_CLK_PM_CTRL_DIS_CLK_250_MASK;
        BREG_AtomicUpdate32(handle->regHandle, BCHP_CLKGEN_AVD_CLK_PM_CTRL, mask, 0);
    }
    else {
        /* AVD Coreclock */
        mask = BCHP_CLKGEN_AVD_CLK_PM_CTRL_DIS_CLK_250_MASK;
        BREG_AtomicUpdate32(handle->regHandle, BCHP_CLKGEN_AVD_CLK_PM_CTRL, mask, mask);

        /* PWRDN_CLOCK_216_CG_AVD SCB Memory clock */
        mask = BCHP_CLKGEN_AVD_CLK_PM_CTRL_DIS_CLK_216_MASK;
        BREG_AtomicUpdate32(handle->regHandle, BCHP_CLKGEN_AVD_CLK_PM_CTRL, mask, mask);

        /* PWRDN_CLOCK_108_CG_AVD GISB clock*/
        mask = BCHP_CLKGEN_AVD_CLK_PM_CTRL_DIS_CLK_108_MASK;
        BREG_AtomicUpdate32(handle->regHandle, BCHP_CLKGEN_AVD_CLK_PM_CTRL, mask, mask);
    }
}

static void BCHP_PWR_P_HW_RAP_OPEN_Control(BCHP_Handle handle, bool activate)
{
    /* BRAP_Open() needs more than just the 108M clock.
       the 216M, 250M clocks, plus RAP_AVD_PLL_CHL1 are needed for AUD_DSP0_* register R/W */

    uint32_t val;
    BDBG_MSG(("HW_RAP_OPEN: %s", activate?"on":"off"));

    if (activate) {
        /* power up AIO clocks */
        val = BCHP_CLKGEN_RPTD_AIO_CLK_PM_CTRL_DIS_CLK_108_MASK;
        BREG_AtomicUpdate32(handle->regHandle, BCHP_CLKGEN_RPTD_AIO_CLK_PM_CTRL, val, 0);

        val = BCHP_CLKGEN_RPTD_AIO_CLK_PM_CTRL_DIS_CLK_216_MASK;
        BREG_AtomicUpdate32(handle->regHandle, BCHP_CLKGEN_RPTD_AIO_CLK_PM_CTRL, val, 0);

        val = BCHP_CLKGEN_RPTD_AIO_CLK_PM_CTRL_DIS_CLK_250_RPTD_MASK;
        BREG_AtomicUpdate32(handle->regHandle, BCHP_CLKGEN_RPTD_AIO_CLK_PM_CTRL, val, 0);
    }
    else {
        /* power down AIO clocks */
        val = BCHP_CLKGEN_RPTD_AIO_CLK_PM_CTRL_DIS_CLK_250_RPTD_MASK;
        BREG_AtomicUpdate32(handle->regHandle, BCHP_CLKGEN_RPTD_AIO_CLK_PM_CTRL, val, val);

        val = BCHP_CLKGEN_RPTD_AIO_CLK_PM_CTRL_DIS_CLK_216_MASK;
        BREG_AtomicUpdate32(handle->regHandle, BCHP_CLKGEN_RPTD_AIO_CLK_PM_CTRL, val, val);

        val = BCHP_CLKGEN_RPTD_AIO_CLK_PM_CTRL_DIS_CLK_108_MASK;
        BREG_AtomicUpdate32(handle->regHandle, BCHP_CLKGEN_RPTD_AIO_CLK_PM_CTRL, val, val);
    }
}

static void BCHP_PWR_P_HW_RAP_START_Control(BCHP_Handle handle, bool activate)
{
    uint32_t val;
    BDBG_MSG(("HW_RAP_START: %s", activate?"on":"off"));

    if (activate) {
        /* AC0 */
        val = BREG_Read32(handle->regHandle, BCHP_VCXO_CTL_MISC_AC0_CTRL);
        val &= ~(BCHP_VCXO_CTL_MISC_AC0_CTRL_ARESET_MASK |
                 BCHP_VCXO_CTL_MISC_AC0_CTRL_DRESET_MASK |
                 BCHP_VCXO_CTL_MISC_AC0_CTRL_POWERDOWN_MASK);
        BREG_Write32(handle->regHandle, BCHP_VCXO_CTL_MISC_AC0_CTRL, val);

        /* HifiDriver0 */
        val = BREG_Read32(handle->regHandle, BCHP_AIO_MISC_PWRDOWN);
        val &= ~BCHP_AIO_MISC_PWRDOWN_DAC0_MASK;
        BREG_Write32(handle->regHandle, BCHP_AIO_MISC_PWRDOWN, val);
    }
    else {
        /* HifiDriver0 */
        val = BREG_Read32(handle->regHandle, BCHP_AIO_MISC_PWRDOWN);
        val |= BCHP_AIO_MISC_PWRDOWN_DAC0_MASK;
        BREG_Write32(handle->regHandle, BCHP_AIO_MISC_PWRDOWN, val);

        /* AC0 */
        val = BREG_Read32(handle->regHandle, BCHP_VCXO_CTL_MISC_AC0_CTRL);
        val |= BCHP_VCXO_CTL_MISC_AC0_CTRL_ARESET_MASK |
               BCHP_VCXO_CTL_MISC_AC0_CTRL_DRESET_MASK |
               BCHP_VCXO_CTL_MISC_AC0_CTRL_POWERDOWN_MASK;
        BREG_Write32(handle->regHandle, BCHP_VCXO_CTL_MISC_AC0_CTRL, val);
    }
}

static void BCHP_PWR_P_HW_BVN_Control(BCHP_Handle handle, bool activate)
{
    uint32_t mask;
    BDBG_MSG(("HW_BVN: %s", activate?"on":"off"));
    mask = BCHP_CLKGEN_BVN_CLK_PM_CTRL_DIS_CLK_216_MASK;
    BREG_AtomicUpdate32(handle->regHandle, BCHP_CLKGEN_BVN_CLK_PM_CTRL, mask, activate ? 0 : mask);
}

static void BCHP_PWR_P_HW_BVN_108M_Control(BCHP_Handle handle, bool activate)
{
    uint32_t mask;
    BDBG_MSG(("HW_BVN: %s", activate?"on":"off"));
    mask = BCHP_CLKGEN_BVN_CLK_PM_CTRL_DIS_CLK_108_MASK;
    BREG_AtomicUpdate32(handle->regHandle, BCHP_CLKGEN_BVN_CLK_PM_CTRL, mask, activate ? 0 : mask);
}


static void BCHP_PWR_P_HW_VDC_TDAC0_Control(BCHP_Handle handle, bool activate)
{
    uint32_t mask;
    BDBG_MSG(("HW_VDC_TDAC0: %s", activate?"on":"off"));

    mask = BCHP_CLKGEN_TDAC0_CLK_PM_CTRL_DIS_CLK_216_MASK;
    BREG_AtomicUpdate32(handle->regHandle, BCHP_CLKGEN_TDAC0_CLK_PM_CTRL, mask, activate ? 0 : mask);
}

static void BCHP_PWR_P_HW_VDC_TDAC1_Control(BCHP_Handle handle, bool activate)
{
    uint32_t mask;
    BDBG_MSG(("HW_VDC_TDAC1: %s", activate?"on":"off"));

    mask = BCHP_CLKGEN_TDAC1_CLK_PM_CTRL_DIS_CLK_216_MASK;
    BREG_AtomicUpdate32(handle->regHandle, BCHP_CLKGEN_TDAC1_CLK_PM_CTRL, mask, activate ? 0 : mask);
}

static void BCHP_PWR_P_HW_VDC_VEC_Control(BCHP_Handle handle, bool activate)
{
    uint32_t mask;
    BDBG_MSG(("HW_VDC_VEC: %s", activate?"on":"off"));

    mask = BCHP_CLKGEN_VEC_CLK_PM_CTRL_DIS_CLK_108_MASK |
           BCHP_CLKGEN_VEC_CLK_PM_CTRL_DIS_CLK_216_MASK;

    BREG_AtomicUpdate32(handle->regHandle, BCHP_CLKGEN_VEC_CLK_PM_CTRL, mask, activate ? 0 : mask);

    mask = BCHP_VCXO_CTL_MISC_VC0_PM_DIS_CHL_1_DIS_CH_MASK;

    BREG_AtomicUpdate32(handle->regHandle, BCHP_VCXO_CTL_MISC_VC0_PM_DIS_CHL_1, mask, activate ? 0 : mask);
}

static void BCHP_PWR_P_HW_XPT_108M_Control(BCHP_Handle handle, bool activate)
{
    uint32_t mask;
    BDBG_MSG(("HW_XPT_108M: %s", activate?"on":"off"));
    mask = BCHP_CLKGEN_XPT_CLK_PM_CTRL_DIS_CLK_108_MASK;
    BREG_AtomicUpdate32(handle->regHandle, BCHP_CLKGEN_XPT_CLK_PM_CTRL, mask, activate ? 0 : mask);
}

static void BCHP_PWR_P_HW_XPT_XMEMIF_Control(BCHP_Handle handle, bool activate)
{
    uint32_t mask;
    BDBG_MSG(("HW_XPT_XMEMIF: %s", activate?"on":"off"));

    if (!activate) {
        /* a short delay (~500us) is needed before a power down of the XMEMIF clock */
        BKNI_Sleep(1);
    }
    /* the 216M clock controls XMEMIF */
    mask = BCHP_CLKGEN_XPT_CLK_PM_CTRL_DIS_CLK_216_MASK;
    BREG_AtomicUpdate32(handle->regHandle, BCHP_CLKGEN_XPT_CLK_PM_CTRL, mask, activate ? 0 : mask);
}

static void BCHP_PWR_P_HW_XPT_RMX_Control(BCHP_Handle handle, bool activate)
{
    uint32_t mask;
    BDBG_MSG(("HW_XPT_RMX: %s", activate?"on":"off"));

    /* 5 clocks are tied to RMX */
    mask = BCHP_CLKGEN_XPT_CLK_PM_CTRL_DIS_CLK_40P5_MASK |
        BCHP_CLKGEN_XPT_CLK_PM_CTRL_DIS_CLK_20P25_MASK |
        BCHP_CLKGEN_XPT_CLK_PM_CTRL_DIS_CLK_81_MASK |
        BCHP_CLKGEN_XPT_CLK_PM_CTRL_DIS_CLK_54_MASK |
        BCHP_CLKGEN_XPT_CLK_PM_CTRL_DIS_CLK_27_MASK;
    BREG_AtomicUpdate32(handle->regHandle, BCHP_CLKGEN_XPT_CLK_PM_CTRL, mask, activate ? 0 : mask);
}

static void BCHP_PWR_P_HW_HDMI_TX_CLK_Control(BCHP_Handle handle, bool activate)
{
    uint32_t mask, val;
    BDBG_MSG(("HW_HDMI_TX_CLK: %s", activate?"on":"off"));
    /* 3 clocks needed for TMDS */
    mask = BCHP_CLKGEN_DVP_HT_CLK_PM_CTRL_DIS_CLK_216_MASK;
    BREG_AtomicUpdate32(handle->regHandle, BCHP_CLKGEN_DVP_HT_CLK_PM_CTRL, mask, activate ? 0 : mask);

    mask = BCHP_CLKGEN_DVP_HT_CLK_PM_CTRL_DIS_CLK_250_MAX_MASK;
    BREG_AtomicUpdate32(handle->regHandle, BCHP_CLKGEN_DVP_HT_CLK_PM_CTRL, mask, activate ? 0 : mask);

    mask = BCHP_CLKGEN_DVP_HT_CLK_PM_CTRL_DIS_CLK_216_ALTERNATE_MASK;
    BREG_AtomicUpdate32(handle->regHandle, BCHP_CLKGEN_DVP_HT_CLK_PM_CTRL, mask, activate ? 0 : mask);

    /* power on/off analog core except CEC */
    val = BREG_Read32(handle->regHandle, BCHP_HDMI_TX_PHY_HDMI_TX_PHY_RESET_CTL);
    mask = (BCHP_HDMI_TX_PHY_HDMI_TX_PHY_RESET_CTL_PLL_PWRDN_MASK |
            BCHP_HDMI_TX_PHY_HDMI_TX_PHY_RESET_CTL_REF_COMP_PWRDN_MASK |
            BCHP_HDMI_TX_PHY_HDMI_TX_PHY_RESET_CTL_PWRDN_BG_MASK);
    if (activate) {
        val &= ~mask;
    }
    else {
        val |= mask;
    }
    BREG_Write32(handle->regHandle, BCHP_HDMI_TX_PHY_HDMI_TX_PHY_RESET_CTL, val);

    /* random bit block */
    val = BREG_Read32(handle->regHandle, BCHP_HDMI_TX_PHY_HDMI_TX_PHY_CTL_0);
    mask = BCHP_HDMI_TX_PHY_HDMI_TX_PHY_CTL_0_RND_PWRDN_MASK;
    if (activate) {
        val &= ~mask;
    }
    else {
        val |= mask;
    }
    BREG_Write32(handle->regHandle, BCHP_HDMI_TX_PHY_HDMI_TX_PHY_CTL_0, val);

    /* rate managers */
    val = BREG_Read32(handle->regHandle, BCHP_HDMI_TX_PHY_HDMI_TX_PHY_CTL_1);
    mask = BCHP_HDMI_TX_PHY_HDMI_TX_PHY_CTL_1_I_PWR_DN_CH1_MASK;
    if (activate) {
        val &= ~mask;
    }
    else {
        val |= mask;
    }
    BREG_Write32(handle->regHandle, BCHP_HDMI_TX_PHY_HDMI_TX_PHY_CTL_1, val);

    val = BREG_Read32(handle->regHandle, BCHP_HDMI_TX_PHY_HDMI_TX_PHY_CTL_2);
    mask = BCHP_HDMI_TX_PHY_HDMI_TX_PHY_CTL_2_I_PWRDN_CH2_MASK;
    if (activate) {
        val &= ~mask;
    }
    else {
        val |= mask;
    }
    BREG_Write32(handle->regHandle, BCHP_HDMI_TX_PHY_HDMI_TX_PHY_CTL_2, val);
}

static void BCHP_PWR_P_HW_HDMI_TX_CEC_Control(BCHP_Handle handle, bool activate)
{
    uint32_t mask, val;
    BDBG_MSG(("HW_HDMI_TX_CEC: %s", activate?"on":"off"));

    mask = BCHP_CLKGEN_DVP_HT_CLK_PM_CTRL_DIS_CLK_27X_PM_MASK;
    BREG_AtomicUpdate32(handle->regHandle, BCHP_CLKGEN_DVP_HT_CLK_PM_CTRL, mask, activate ? 0 : mask);
    /* note:  pwr/7125/bpwr_priv.c didn't include this one:  */
    mask = BCHP_CLKGEN_DVP_HT_CLK_PM_CTRL_DIS_CLK_27X_IIC_MASK;
    BREG_AtomicUpdate32(handle->regHandle, BCHP_CLKGEN_DVP_HT_CLK_PM_CTRL, mask, activate ? 0 : mask);
    /* CEC bit in analog core and refamp */
    val = BREG_Read32(handle->regHandle, BCHP_HDMI_TX_PHY_HDMI_TX_PHY_RESET_CTL);
    mask = (BCHP_HDMI_TX_PHY_HDMI_TX_PHY_RESET_CTL_PWRDN_CEC_MASK |
            BCHP_HDMI_TX_PHY_HDMI_TX_PHY_RESET_CTL_PWRDN_REFAMP_MASK);
    if (activate) {
        val &= ~mask;
    }
    else {
        val |= mask;
    }
    BREG_Write32(handle->regHandle, BCHP_HDMI_TX_PHY_HDMI_TX_PHY_RESET_CTL, val);
}

static void BCHP_PWR_P_HW_HDMI_TX_108M_Control(BCHP_Handle handle, bool activate)
{
    uint32_t mask;
    BDBG_MSG(("HW_HDMI_TX_108M: %s", activate?"on":"off"));

    /* 108M clock needed for register R/W */
    mask = BCHP_CLKGEN_DVP_HT_CLK_PM_CTRL_DIS_CLK_108_MASK |
           BCHP_CLKGEN_DVP_HT_CLK_PM_CTRL_DIS_CLK_108_ALTERNATE_MASK;
    BREG_AtomicUpdate32(handle->regHandle, BCHP_CLKGEN_DVP_HT_CLK_PM_CTRL, mask, activate ? 0 : mask);
}

static void BCHP_PWR_P_HW_M2MC_Control(BCHP_Handle handle, bool activate)
{
    uint32_t mask;
    BDBG_MSG(("HW_M2MC: %s", activate?"on":"off"));

    mask = BCHP_CLKGEN_GFX_CLK_PM_CTRL_DIS_CLK_216_MASK |
           BCHP_CLKGEN_GFX_CLK_PM_CTRL_DIS_CLK_108_MASK;
    BREG_AtomicUpdate32(handle->regHandle, BCHP_CLKGEN_GFX_CLK_PM_CTRL, mask, activate ? 0 : mask);
}

static void BCHP_PWR_P_HW_PX3D_Control(BCHP_Handle handle, bool activate)
{
    uint32_t mask;
    BDBG_MSG(("HW_PX3D: %s", activate?"on":"off"));
    mask = BCHP_CLKGEN_GFX_3D_OTP_CLK_PM_CTRL_DIS_CLK_216_3D_OTP_MASK;
    BREG_AtomicUpdate32(handle->regHandle, BCHP_CLKGEN_GFX_3D_OTP_CLK_PM_CTRL, mask, activate ? 0 : mask);
}

static void BCHP_PWR_P_HW_DMA_Control(BCHP_Handle handle, bool activate)
{
    uint32_t mask;
    BDBG_MSG(("HW_DMA: %s", activate?"on":"off"));

    mask = BCHP_CLKGEN_SECTOP_DMA_CLK_PM_CTRL_DIS_CLK_108_MASK |
           BCHP_CLKGEN_SECTOP_DMA_CLK_PM_CTRL_DIS_CLK_216_MASK;
    BREG_AtomicUpdate32(handle->regHandle, BCHP_CLKGEN_SECTOP_DMA_CLK_PM_CTRL, mask, activate ? 0 : mask);
}

static void BCHP_PWR_P_HW_DIGITAL_FRONTEND_Control(BCHP_Handle handle, bool activate)
{
    BDBG_MSG(("HW_DIGITAL_FRONTEND: %s", activate?"on":"off"));
    BSTD_UNUSED(handle);
    BSTD_UNUSED(activate);
}

static void BCHP_PWR_P_HW_SCD_Control(BCHP_Handle handle, bool activate)
{
    uint32_t mask;
    BDBG_MSG(("HW_SCD: %s", activate?"on":"off"));

    if (activate) {
        /* Power up clockgen smartcard output clocks */
        mask = BREG_Read32(handle->regHandle, BCHP_CLKGEN_SUN_SC_CLK_PM_CTRL);
        mask &= ~(BCHP_CLKGEN_SUN_SC_CLK_PM_CTRL_DIS_CLK_40_27X_SC1_MASK |
              BCHP_CLKGEN_SUN_SC_CLK_PM_CTRL_DIS_CLK_40_27X_SC0_MASK);
        BREG_Write32(handle->regHandle, BCHP_CLKGEN_SUN_SC_CLK_PM_CTRL, mask);

        /* Power up VCXO 0, channel 3 post divider. */
        mask = BREG_Read32(handle->regHandle, BCHP_VCXO_CTL_MISC_VC0_PM_DIS_CHL_3);
        mask &= ~BCHP_VCXO_CTL_MISC_VC0_PM_DIS_CHL_3_DIS_CH_MASK;
        BREG_Write32(handle->regHandle, BCHP_VCXO_CTL_MISC_VC0_PM_DIS_CHL_3, mask);

        /* Power up SmartCard_PLL */
        mask = BREG_Read32(handle->regHandle, BCHP_SMARTCARD_PLL_SC_CTRL);
        mask &= ~(BCHP_SMARTCARD_PLL_SC_CTRL_DRESET_MASK      |
                  BCHP_SMARTCARD_PLL_SC_CTRL_ARESET_MASK      |
                  BCHP_SMARTCARD_PLL_SC_CTRL_POWERDOWN_MASK);
        BREG_Write32(handle->regHandle, BCHP_SMARTCARD_PLL_SC_CTRL, mask);

        /* Power up SmartCard PLL clock output channel 1 */
        mask = BREG_Read32(handle->regHandle, BCHP_SMARTCARD_PLL_SC_PM_DIS_CHL_1);
        mask &= ~BCHP_SMARTCARD_PLL_SC_PM_DIS_CHL_1_DIS_CH_MASK;
        BREG_Write32(handle->regHandle, BCHP_SMARTCARD_PLL_SC_PM_DIS_CHL_1, mask);

        /* Smart card PLL clock outputs enable */
        mask = BREG_Read32(handle->regHandle, BCHP_SMARTCARD_PLL_SC_PM_CLOCK_ENA);
        mask |= BCHP_SMARTCARD_PLL_SC_PM_CLOCK_ENA_CLOCK_ENA_MASK;
        BREG_Write32(handle->regHandle, BCHP_SMARTCARD_PLL_SC_PM_CLOCK_ENA, mask);

    }
    else {
        /* disable PLL clock outputs */
        mask = BREG_Read32(handle->regHandle, BCHP_SMARTCARD_PLL_SC_PM_CLOCK_ENA);
        mask &= ~BCHP_SMARTCARD_PLL_SC_PM_CLOCK_ENA_CLOCK_ENA_MASK;
        BREG_Write32(handle->regHandle, BCHP_SMARTCARD_PLL_SC_PM_CLOCK_ENA, mask);

        /* Power down SmartCard PLL clock output channel 1 */
        mask = BREG_Read32(handle->regHandle, BCHP_SMARTCARD_PLL_SC_PM_DIS_CHL_1);
        mask |= BCHP_SMARTCARD_PLL_SC_PM_DIS_CHL_1_DIS_CH_MASK;
        BREG_Write32(handle->regHandle, BCHP_SMARTCARD_PLL_SC_PM_DIS_CHL_1, mask);

        /* power down VCXO smartcard PLL */
        mask = BREG_Read32(handle->regHandle, BCHP_SMARTCARD_PLL_SC_CTRL);
        mask |= (BCHP_SMARTCARD_PLL_SC_CTRL_POWERDOWN_MASK |
                 BCHP_SMARTCARD_PLL_SC_CTRL_ARESET_MASK    |
                 BCHP_SMARTCARD_PLL_SC_CTRL_DRESET_MASK);
        BREG_Write32(handle->regHandle, BCHP_SMARTCARD_PLL_SC_CTRL, mask);

        /* Power down clockgen smartcard output clocks */
        mask = BREG_Read32(handle->regHandle, BCHP_CLKGEN_SUN_SC_CLK_PM_CTRL);
        mask |= (BCHP_CLKGEN_SUN_SC_CLK_PM_CTRL_DIS_CLK_40_27X_SC1_MASK |
                 BCHP_CLKGEN_SUN_SC_CLK_PM_CTRL_DIS_CLK_40_27X_SC0_MASK);
        BREG_Write32(handle->regHandle, BCHP_CLKGEN_SUN_SC_CLK_PM_CTRL, mask);
    }
}

static void BCHP_PWR_P_HW_AVD_PLL_CH_Control(BCHP_Handle handle, bool activate)
{
    BDBG_MSG(("HW_AVD_PLL_CH: %s", activate?"on":"off"));

    if (activate) {
        BREG_AtomicUpdate32(handle->regHandle,  BCHP_VCXO_CTL_MISC_RAP_AVD_PLL_CHL_6,
                            /* clear these bits */
                            (BCHP_VCXO_CTL_MISC_RAP_AVD_PLL_CHL_6_EN_CMLBUF_MASK    |
                             BCHP_VCXO_CTL_MISC_RAP_AVD_PLL_CHL_6_DIS_CH_MASK |
                             BCHP_VCXO_CTL_MISC_RAP_AVD_PLL_CHL_6_CLOCK_ENA_MASK),
                            /* set these bits */
                            (BCHP_VCXO_CTL_MISC_RAP_AVD_PLL_CHL_6_EN_CMLBUF_MASK    |
                             BCHP_VCXO_CTL_MISC_RAP_AVD_PLL_CHL_6_CLOCK_ENA_MASK));
        BKNI_Sleep(1); /* wait for PLL to lock */
    }
    else {
        BREG_AtomicUpdate32(handle->regHandle,  BCHP_VCXO_CTL_MISC_RAP_AVD_PLL_CHL_6 ,
                            /* clear these bits */
                            (BCHP_VCXO_CTL_MISC_RAP_AVD_PLL_CHL_6_EN_CMLBUF_MASK    |
                             BCHP_VCXO_CTL_MISC_RAP_AVD_PLL_CHL_6_DIS_CH_MASK |
                             BCHP_VCXO_CTL_MISC_RAP_AVD_PLL_CHL_6_CLOCK_ENA_MASK),
                            /* set these bits */
                            BCHP_VCXO_CTL_MISC_RAP_AVD_PLL_CHL_6_DIS_CH_MASK);
    }

}

static void BCHP_PWR_P_HW_RAP_PLL_CH_Control(BCHP_Handle handle, bool activate)
{
    uint32_t val;
    BDBG_MSG(("HW_RAP_PLL_CH: %s", activate?"on":"off"));

    if (activate) {
        /* Power up VC1 */
        val = BREG_Read32(handle->regHandle, BCHP_VCXO_CTL_MISC_RAP_AVD_PLL_CHL_1);
        val |= BCHP_VCXO_CTL_MISC_RAP_AVD_PLL_CHL_1_CLOCK_ENA_MASK;
        val |= BCHP_VCXO_CTL_MISC_RAP_AVD_PLL_CHL_1_EN_CMLBUF_MASK;
        val &= ~BCHP_VCXO_CTL_MISC_RAP_AVD_PLL_CHL_1_DIS_CH_MASK;
        BREG_Write32(handle->regHandle, BCHP_VCXO_CTL_MISC_RAP_AVD_PLL_CHL_1, val);

        BKNI_Sleep(1); /* wait for PLL to lock */
    }
    else {
        /* Power down VC1 */
        val = BREG_Read32(handle->regHandle, BCHP_VCXO_CTL_MISC_RAP_AVD_PLL_CHL_1);
        val &= ~BCHP_VCXO_CTL_MISC_RAP_AVD_PLL_CHL_1_CLOCK_ENA_MASK;
        val &= ~BCHP_VCXO_CTL_MISC_RAP_AVD_PLL_CHL_1_EN_CMLBUF_MASK;
        val |= BCHP_VCXO_CTL_MISC_RAP_AVD_PLL_CHL_1_DIS_CH_MASK;
        BREG_Write32(handle->regHandle, BCHP_VCXO_CTL_MISC_RAP_AVD_PLL_CHL_1, val);
    }
}

static void BCHP_PWR_P_HW_ACX_PLL_CTRL_Control(BCHP_Handle handle, bool activate)
{
    uint32_t val;
    BDBG_MSG(("HW_ACX_PLL_CTRL: %s", activate?"on":"off"));

    if (activate) {
        val = BREG_Read32(handle->regHandle, BCHP_VCXO_CTL_MISC_AC0_CTRL);
        val &= ~(BCHP_VCXO_CTL_MISC_AC0_CTRL_ARESET_MASK |
                 BCHP_VCXO_CTL_MISC_AC0_CTRL_DRESET_MASK |
                 BCHP_VCXO_CTL_MISC_AC0_CTRL_POWERDOWN_MASK);
        BREG_Write32(handle->regHandle, BCHP_VCXO_CTL_MISC_AC0_CTRL, val);

        BKNI_Sleep(1); /* wait for PLL to lock */
    }
    else {
        val = BREG_Read32(handle->regHandle, BCHP_VCXO_CTL_MISC_AC0_CTRL);
        val |= BCHP_VCXO_CTL_MISC_AC0_CTRL_ARESET_MASK |
               BCHP_VCXO_CTL_MISC_AC0_CTRL_DRESET_MASK |
               BCHP_VCXO_CTL_MISC_AC0_CTRL_POWERDOWN_MASK;
        BREG_Write32(handle->regHandle, BCHP_VCXO_CTL_MISC_AC0_CTRL, val);
    }
}

static void BCHP_PWR_P_HW_VCX_PLL_CH2_Control(BCHP_Handle handle, bool activate)
{
    uint32_t val;
    BDBG_MSG(("HW_VCX_PLL_CH2: %s", activate?"on":"off"));

    if (activate) {
        val = BREG_Read32(handle->regHandle, BCHP_VCXO_CTL_MISC_VC0_PM_DIS_CHL_2);
        val &= ~BCHP_VCXO_CTL_MISC_VC0_PM_DIS_CHL_2_DIS_CH_MASK;
        BREG_Write32(handle->regHandle, BCHP_VCXO_CTL_MISC_VC0_PM_DIS_CHL_2, val);
    }
    else {
        val = BREG_Read32(handle->regHandle, BCHP_VCXO_CTL_MISC_VC0_PM_DIS_CHL_2);
        val |= BCHP_VCXO_CTL_MISC_VC0_PM_DIS_CHL_2_DIS_CH_MASK;
        BREG_Write32(handle->regHandle, BCHP_VCXO_CTL_MISC_VC0_PM_DIS_CHL_2, val);
    }
}

static void BCHP_PWR_P_HW_VCX_PLL_CH3_Control(BCHP_Handle handle, bool activate)
{
    uint32_t val;
    BDBG_MSG(("HW_VCX_PLL_CH3: %s", activate?"on":"off"));

    if (activate) {
        val = BREG_Read32(handle->regHandle, BCHP_VCXO_CTL_MISC_VC0_PM_DIS_CHL_3);
        val &= ~BCHP_VCXO_CTL_MISC_VC0_PM_DIS_CHL_3_DIS_CH_MASK;
        BREG_Write32(handle->regHandle, BCHP_VCXO_CTL_MISC_VC0_PM_DIS_CHL_3, val);
    }
    else {
        val = BREG_Read32(handle->regHandle, BCHP_VCXO_CTL_MISC_VC0_PM_DIS_CHL_3);
        val |= BCHP_VCXO_CTL_MISC_VC0_PM_DIS_CHL_3_DIS_CH_MASK;
        BREG_Write32(handle->regHandle, BCHP_VCXO_CTL_MISC_VC0_PM_DIS_CHL_3, val);
    }
}

static void BCHP_PWR_P_HW_VCX_PLL_CTRL_Control(BCHP_Handle handle, bool activate)
{
    uint32_t mask;

    BDBG_MSG(("HW_VCX_PLL_CTRL: %s", activate?"on":"off"));

    if (activate) {
        mask = (BCHP_VCXO_CTL_MISC_VC0_CTRL_DRESET_MASK |
                BCHP_VCXO_CTL_MISC_VC0_CTRL_ARESET_MASK |
                BCHP_VCXO_CTL_MISC_VC0_CTRL_POWERDOWN_MASK);
        BREG_AtomicUpdate32(handle->regHandle, BCHP_VCXO_CTL_MISC_VC0_CTRL, mask, 0);
    }
    else {
        mask = (BCHP_VCXO_CTL_MISC_VC0_CTRL_DRESET_MASK |
                BCHP_VCXO_CTL_MISC_VC0_CTRL_ARESET_MASK |
                BCHP_VCXO_CTL_MISC_VC0_CTRL_POWERDOWN_MASK);
        BREG_AtomicUpdate32(handle->regHandle, BCHP_VCXO_CTL_MISC_VC0_CTRL, mask, mask);
    }
}

static void BCHP_PWR_P_HW_SYS_PLL_0_CH3_Control(BCHP_Handle handle, bool activate)
{
    uint32_t mask;
    BDBG_MSG(("HW_SYS_PLL_0_CH3: %s", activate?"on":"off"));

    mask = BCHP_CLKGEN_PLL_MAIN_CH3_PM_CTRL_DIS_CH_MASK;
    BREG_AtomicUpdate32(handle->regHandle, BCHP_CLKGEN_PLL_MAIN_CH3_PM_CTRL, mask, activate ? 0 : mask);
}


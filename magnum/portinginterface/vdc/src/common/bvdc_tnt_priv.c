/***************************************************************************
 *     Copyright (c) 2004-2012, Broadcom Corporation
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
 **************************************************************************/
#include "bvdc_compositor_priv.h"
#include "bvdc_source_priv.h"
#include "bvdc_pep_priv.h"
#include "bvdc_hist_priv.h"
#if (BVDC_P_SUPPORT_PEP_VER == BVDC_P_SUPPORT_PEP_VER_4)
#include "bchp_vivid_cmp_0.h"
#endif
#if (BVDC_P_SUPPORT_TNT_VER >= 5)
#include "bchp_tnt_cmp_0_v0.h"
#endif
#include "bvdc_tnt.h"
#include "bvdc_tnt_priv.h"

BDBG_MODULE(BVDC_TNT);

#if (BVDC_P_SUPPORT_TNT)
#if(BVDC_P_SUPPORT_TNT_VER >= 6)
void BVDC_P_Tnt_BuildInit_isr
	( const BVDC_Window_Handle     hWindow,
	  BVDC_P_ListInfo             *pList )
{
	BDBG_ENTER(BVDC_P_Tnt_BuildInit_isr);
	BDBG_OBJECT_ASSERT(hWindow, BVDC_WIN);

#if (BVDC_P_SUPPORT_TNT_VER == 6)
	*pList->pulCurrent++ = BRDC_OP_IMMS_TO_REGS(3);
	*pList->pulCurrent++ = BRDC_REGISTER(BCHP_TNT_CMP_0_V0_LPEAK_INCORE_DIV_HIGHi_ARRAY_BASE);
	*pList->pulCurrent++ = 0x51e;
	*pList->pulCurrent++ = 0x1b4;
	*pList->pulCurrent++ = 0x4f;

	*pList->pulCurrent++ = BRDC_OP_IMM_TO_REG();
	*pList->pulCurrent++ = BRDC_REGISTER(BCHP_TNT_CMP_0_V0_LPEAK_OUT_CORE);
	*pList->pulCurrent++ =
		BCHP_FIELD_ENUM(TNT_CMP_0_V0_LPEAK_OUT_CORE, MODE,        TOTAL) |
		BCHP_FIELD_DATA(TNT_CMP_0_V0_LPEAK_OUT_CORE, LCORE_BAND2, 0x8  ) |
		BCHP_FIELD_DATA(TNT_CMP_0_V0_LPEAK_OUT_CORE, LCORE_BAND1, 0x8  );

	*pList->pulCurrent++ = BRDC_OP_IMM_TO_REG();
	*pList->pulCurrent++ = BRDC_REGISTER(BCHP_TNT_CMP_0_V0_LPEAK_CLIP_AVOID);
	*pList->pulCurrent++ =
		BCHP_FIELD_ENUM(TNT_CMP_0_V0_LPEAK_CLIP_AVOID, CLIPAVOID_EN, ENABLE) |
		BCHP_FIELD_DATA(TNT_CMP_0_V0_LPEAK_CLIP_AVOID, SLOPE2,       0x1)    |
		BCHP_FIELD_DATA(TNT_CMP_0_V0_LPEAK_CLIP_AVOID, SLOPE1,       0x1)    |
		BCHP_FIELD_DATA(TNT_CMP_0_V0_LPEAK_CLIP_AVOID, CLIPVAL2,     0x334)  |
		BCHP_FIELD_DATA(TNT_CMP_0_V0_LPEAK_CLIP_AVOID, CLIPVAL1,     0xc8);

	*pList->pulCurrent++ = BRDC_OP_IMM_TO_REG();
	*pList->pulCurrent++ = BRDC_REGISTER(BCHP_TNT_CMP_0_V0_LTI_FILTER);
	*pList->pulCurrent++ =
		BCHP_FIELD_ENUM(TNT_CMP_0_V0_LTI_FILTER, BLUR_EN,    ENABLE) |
		BCHP_FIELD_ENUM(TNT_CMP_0_V0_LTI_FILTER, H_FILT_SEL, TAP9);

	*pList->pulCurrent++ = BRDC_OP_IMM_TO_REG();
	*pList->pulCurrent++ = BRDC_REGISTER(BCHP_TNT_CMP_0_V0_LTI_INCORE_THR);
	*pList->pulCurrent++ =
		BCHP_FIELD_DATA(TNT_CMP_0_V0_LTI_INCORE_THR, T2, 0xc8) |
		BCHP_FIELD_DATA(TNT_CMP_0_V0_LTI_INCORE_THR, T1, 0x32);

	*pList->pulCurrent++ = BRDC_OP_IMMS_TO_REGS(3);
	*pList->pulCurrent++ = BRDC_REGISTER(BCHP_TNT_CMP_0_V0_LTI_INCORE_DIVi_ARRAY_BASE);
	*pList->pulCurrent++ = 0x51e;
	*pList->pulCurrent++ = 0x1b4;
	*pList->pulCurrent++ = 0x4f;

	*pList->pulCurrent++ = BRDC_OP_IMM_TO_REG();
	*pList->pulCurrent++ = BRDC_REGISTER(BCHP_TNT_CMP_0_V0_LTI_INCORE_GOFF);
	*pList->pulCurrent++ =
		BCHP_FIELD_DATA(TNT_CMP_0_V0_LTI_INCORE_GOFF, OFFSET4, 0x0) |
		BCHP_FIELD_DATA(TNT_CMP_0_V0_LTI_INCORE_GOFF, OFFSET3, 0x0) |
		BCHP_FIELD_DATA(TNT_CMP_0_V0_LTI_INCORE_GOFF, OFFSET2, 0xfffffffc) |
		BCHP_FIELD_DATA(TNT_CMP_0_V0_LTI_INCORE_GOFF, OFFSET1, 0xfffffffc);
#else
	BSTD_UNUSED(pList);
#endif

	BSTD_UNUSED(hWindow);
	BDBG_LEAVE(BVDC_P_Tnt_BuildInit_isr);
	return;
}

void BVDC_P_Tnt_BuildRul_isr
	( const BVDC_Window_Handle     hWindow,
	  BVDC_P_ListInfo             *pList )
{
	BVDC_P_Window_Info    *pCurInfo;

	BDBG_ENTER(BVDC_P_Tnt_BuildRul_isr);
	BDBG_OBJECT_ASSERT(hWindow, BVDC_WIN);
	/* Get current pointer to RUL */
	pCurInfo = &hWindow->stCurInfo;

	if(pCurInfo->bSharpnessEnable)
	{
		bool bIsInputSd;
		bool bIsOutputSd;
		uint32_t ulCtiHGain;

#if (BVDC_P_SUPPORT_TNT_VER == 6)
		uint32_t aulLPeakGain[4];
		uint32_t ulLPeakGoffLow;
		uint32_t ulLPeakGoffHigh;
		uint32_t ulLPeakIncoreThrLow;
		uint32_t aulPeakIncoreThrDivLow[3];
		uint32_t ulLPeakIncoreThrHigh;
		uint32_t ulCoreLevel;
		uint32_t ulGainA, ulGainB;
		uint32_t ulLtiGain;
#endif

		/* Treat both SD and ED as SD for TNT settings */
		bIsInputSd = VIDEO_FORMAT_IS_SD(pCurInfo->hSource->stCurInfo.pFmtInfo->eVideoFmt) ||
			VIDEO_FORMAT_IS_ED(pCurInfo->hSource->stCurInfo.pFmtInfo->eVideoFmt);
		bIsOutputSd = VIDEO_FORMAT_IS_SD(hWindow->hCompositor->stCurInfo.pFmtInfo->eVideoFmt) ||
			VIDEO_FORMAT_IS_ED(hWindow->hCompositor->stCurInfo.pFmtInfo->eVideoFmt);
		BDBG_MSG(("Building TNT RUL %s In %s Out",
			bIsInputSd ? "SD" : "HD", bIsOutputSd ? "SD" : "HD"));

		/* Setting up the demo mode register */
		if(pCurInfo->stSplitScreenSetting.eSharpness != BVDC_SplitScreenMode_eDisable)
		{
			uint32_t ulBoundary = hWindow->stAdjDstRect.ulWidth / 2;
			uint32_t ulDemoSide = (pCurInfo->stSplitScreenSetting.eSharpness == BVDC_SplitScreenMode_eLeft) ?
			                       BCHP_TNT_CMP_0_V0_DEMO_SETTING_DEMO_L_R_LEFT :
			                       BCHP_TNT_CMP_0_V0_DEMO_SETTING_DEMO_L_R_RIGHT;

			*pList->pulCurrent++ = BRDC_OP_IMM_TO_REG();
			*pList->pulCurrent++ = BRDC_REGISTER(BCHP_TNT_CMP_0_V0_DEMO_SETTING);
			*pList->pulCurrent++ =
				BCHP_FIELD_DATA(TNT_CMP_0_V0_DEMO_SETTING, DEMO_L_R, ulDemoSide) |
				BCHP_FIELD_DATA(TNT_CMP_0_V0_DEMO_SETTING, DEMO_BOUNDARY, ulBoundary) ;

			BDBG_MSG(("TNT Demo Mode: L_R = %s, BOUNDARY = %d",
			          ((ulDemoSide == BCHP_TNT_CMP_0_V0_DEMO_SETTING_DEMO_L_R_LEFT) ? "L" : "R"),
			          ulBoundary));
		}

		if(bIsInputSd && !bIsOutputSd)
		{
			/* SD in HD out => SD mode */
			BVDC_P_Sharpness_Calculate_Gain_Value_isr(pCurInfo->sSharpness, 0, 10, 20,
			                                      &ulCtiHGain);
#if (BVDC_P_SUPPORT_TNT_VER == 6)
			BVDC_P_Sharpness_Calculate_Gain_Value_isr(pCurInfo->sSharpness, 4, 12, 20,
			                                      &ulGainA);
			BVDC_P_Sharpness_Calculate_Gain_Value_isr(pCurInfo->sSharpness, 4, 12, 20,
			                                      &ulGainB);
			BVDC_P_Sharpness_Calculate_Gain_Value_isr(pCurInfo->sSharpness, 4, 12, 20,
			                                      &ulLtiGain);

			aulLPeakGain[0] = 0;
			aulLPeakGain[1] =
				BCHP_FIELD_DATA(TNT_CMP_0_V0_LPEAK_GAINSi, GAIN_NEG, ulGainA) |
				BCHP_FIELD_DATA(TNT_CMP_0_V0_LPEAK_GAINSi, GAIN_POS, ulGainA) ;
			aulLPeakGain[2] =
				BCHP_FIELD_DATA(TNT_CMP_0_V0_LPEAK_GAINSi, GAIN_NEG, ulGainB) |
				BCHP_FIELD_DATA(TNT_CMP_0_V0_LPEAK_GAINSi, GAIN_POS, ulGainB) ;
			aulLPeakGain[3] = 0;

			ulLPeakGoffLow =
				BCHP_FIELD_DATA(TNT_CMP_0_V0_LPEAK_INCORE_GOFF_LOW, OFFSET4, 0x0 ) |
				BCHP_FIELD_DATA(TNT_CMP_0_V0_LPEAK_INCORE_GOFF_LOW, OFFSET3, 0x0 ) |
				BCHP_FIELD_DATA(TNT_CMP_0_V0_LPEAK_INCORE_GOFF_LOW, OFFSET2, 0xfffffffc) |
				BCHP_FIELD_DATA(TNT_CMP_0_V0_LPEAK_INCORE_GOFF_LOW, OFFSET1, 0xfffffffc);

			ulLPeakGoffHigh =
				BCHP_FIELD_DATA(TNT_CMP_0_V0_LPEAK_INCORE_GOFF_HIGH, OFFSET4, 0x0 ) |
				BCHP_FIELD_DATA(TNT_CMP_0_V0_LPEAK_INCORE_GOFF_HIGH, OFFSET3, 0x0 ) |
				BCHP_FIELD_DATA(TNT_CMP_0_V0_LPEAK_INCORE_GOFF_HIGH, OFFSET2, 0x0 ) |
				BCHP_FIELD_DATA(TNT_CMP_0_V0_LPEAK_INCORE_GOFF_HIGH, OFFSET1, 0x0 );

			ulLPeakIncoreThrLow =
				BCHP_FIELD_DATA(TNT_CMP_0_V0_LPEAK_INCORE_THR_LOW, T2, 0xc8) |
				BCHP_FIELD_DATA(TNT_CMP_0_V0_LPEAK_INCORE_THR_LOW, T1, 0x32);

			aulPeakIncoreThrDivLow[0] = 0x51e;
			aulPeakIncoreThrDivLow[1] = 0x1b4;
			aulPeakIncoreThrDivLow[2] = 0x4f;

			ulLPeakIncoreThrHigh =
				BCHP_FIELD_DATA(TNT_CMP_0_V0_LPEAK_INCORE_THR_HIGH, T2, 0x0) |
				BCHP_FIELD_DATA(TNT_CMP_0_V0_LPEAK_INCORE_THR_HIGH, T1, 0x0);

			ulCoreLevel = 0x4;
#endif
		}
		else
		{
			/* SD in SD out => HD mode */
			/* HD in SD out => HD mode */
			/* HD in HD out => HD mode */
			BVDC_P_Sharpness_Calculate_Gain_Value_isr(pCurInfo->sSharpness, 0, 10, 20,
			                                      &ulCtiHGain);
#if (BVDC_P_SUPPORT_TNT_VER == 6)
			BVDC_P_Sharpness_Calculate_Gain_Value_isr(pCurInfo->sSharpness, 4, 12, 20,
			                                      &ulGainA);
			BVDC_P_Sharpness_Calculate_Gain_Value_isr(pCurInfo->sSharpness, 4, 12, 20,
			                                      &ulGainB);
			BVDC_P_Sharpness_Calculate_Gain_Value_isr(pCurInfo->sSharpness, 4, 12, 20,
			                                      &ulLtiGain);

			aulLPeakGain[0] = 0;
			aulLPeakGain[1] = 0;
			aulLPeakGain[2] =
				BCHP_FIELD_DATA(TNT_CMP_0_V0_LPEAK_GAINSi, GAIN_NEG, ulGainA) |
				BCHP_FIELD_DATA(TNT_CMP_0_V0_LPEAK_GAINSi, GAIN_POS, ulGainA) ;
			aulLPeakGain[3] =
				BCHP_FIELD_DATA(TNT_CMP_0_V0_LPEAK_GAINSi, GAIN_NEG, ulGainB) |
				BCHP_FIELD_DATA(TNT_CMP_0_V0_LPEAK_GAINSi, GAIN_POS, ulGainB) ;

			ulLPeakGoffLow =
				BCHP_FIELD_DATA(TNT_CMP_0_V0_LPEAK_INCORE_GOFF_LOW, OFFSET4, 0x0 ) |
				BCHP_FIELD_DATA(TNT_CMP_0_V0_LPEAK_INCORE_GOFF_LOW, OFFSET3, 0x0 ) |
				BCHP_FIELD_DATA(TNT_CMP_0_V0_LPEAK_INCORE_GOFF_LOW, OFFSET2, 0x0 ) |
				BCHP_FIELD_DATA(TNT_CMP_0_V0_LPEAK_INCORE_GOFF_LOW, OFFSET1, 0x0 );

			ulLPeakGoffHigh =
				BCHP_FIELD_DATA(TNT_CMP_0_V0_LPEAK_INCORE_GOFF_HIGH, OFFSET4, 0x0 ) |
				BCHP_FIELD_DATA(TNT_CMP_0_V0_LPEAK_INCORE_GOFF_HIGH, OFFSET3, 0x0 ) |
				BCHP_FIELD_DATA(TNT_CMP_0_V0_LPEAK_INCORE_GOFF_HIGH, OFFSET2, 0xfffffffc ) |
				BCHP_FIELD_DATA(TNT_CMP_0_V0_LPEAK_INCORE_GOFF_HIGH, OFFSET1, 0xfffffffc );

			ulLPeakIncoreThrLow =
				BCHP_FIELD_DATA(TNT_CMP_0_V0_LPEAK_INCORE_THR_LOW, T2, 0x0) |
				BCHP_FIELD_DATA(TNT_CMP_0_V0_LPEAK_INCORE_THR_LOW, T1, 0x0);

			aulPeakIncoreThrDivLow[0] = 0x0;
			aulPeakIncoreThrDivLow[1] = 0x0;
			aulPeakIncoreThrDivLow[2] = 0x0;

			ulLPeakIncoreThrHigh =
				BCHP_FIELD_DATA(TNT_CMP_0_V0_LPEAK_INCORE_THR_HIGH, T2, 0xc8) |
				BCHP_FIELD_DATA(TNT_CMP_0_V0_LPEAK_INCORE_THR_HIGH, T1, 0x32);

			ulCoreLevel = 0x4;
#endif
		}

#if (BVDC_P_SUPPORT_TNT_VER == 6)
		BDBG_MSG(("GainA=0x%x, GainB=0x%x", ulGainA, ulGainB));
		*pList->pulCurrent++ = BRDC_OP_IMMS_TO_REGS(4);
		*pList->pulCurrent++ = BRDC_REGISTER(BCHP_TNT_CMP_0_V0_LPEAK_GAINSi_ARRAY_BASE);
		BKNI_Memcpy((void*)pList->pulCurrent, (void*)&aulLPeakGain, 4 * sizeof(uint32_t));
		pList->pulCurrent += 4;

		*pList->pulCurrent++ = BRDC_OP_IMM_TO_REG();
		*pList->pulCurrent++ = BRDC_REGISTER(BCHP_TNT_CMP_0_V0_LPEAK_INCORE_GOFF_LOW);
		*pList->pulCurrent++ = ulLPeakGoffLow;

		*pList->pulCurrent++ = BRDC_OP_IMM_TO_REG();
		*pList->pulCurrent++ = BRDC_REGISTER(BCHP_TNT_CMP_0_V0_LPEAK_INCORE_GOFF_HIGH);
		*pList->pulCurrent++ = ulLPeakGoffHigh;

		*pList->pulCurrent++ = BRDC_OP_IMM_TO_REG();
		*pList->pulCurrent++ = BRDC_REGISTER(BCHP_TNT_CMP_0_V0_LPEAK_INCORE_THR_LOW);
		*pList->pulCurrent++ = ulLPeakIncoreThrLow;

		*pList->pulCurrent++ = BRDC_OP_IMMS_TO_REGS(3);
		*pList->pulCurrent++ = BRDC_REGISTER(BCHP_TNT_CMP_0_V0_LPEAK_INCORE_DIV_LOWi_ARRAY_BASE);
		BKNI_Memcpy((void*)pList->pulCurrent, (void*)&aulPeakIncoreThrDivLow, 3 * sizeof(uint32_t));
		pList->pulCurrent += 3;

		*pList->pulCurrent++ = BRDC_OP_IMM_TO_REG();
		*pList->pulCurrent++ = BRDC_REGISTER(BCHP_TNT_CMP_0_V0_LPEAK_INCORE_THR_HIGH);
		*pList->pulCurrent++ = ulLPeakIncoreThrHigh;

		*pList->pulCurrent++ = BRDC_OP_IMM_TO_REG();
		*pList->pulCurrent++ = BRDC_REGISTER(BCHP_TNT_CMP_0_V0_LTI_CONTROL);
		*pList->pulCurrent++ =
			BCHP_FIELD_ENUM(TNT_CMP_0_V0_LTI_CONTROL, LTI_INCORE_EN, ENABLE)|
			BCHP_FIELD_DATA(TNT_CMP_0_V0_LTI_CONTROL, GAIN,          ulLtiGain)  |
			BCHP_FIELD_DATA(TNT_CMP_0_V0_LTI_CONTROL, HAVOID,        0xc)   |
			BCHP_FIELD_DATA(TNT_CMP_0_V0_LTI_CONTROL, CORE_LEVEL,    ulCoreLevel);
#endif

		BDBG_MSG(("CtiHGain=0x%x", ulCtiHGain));
		*pList->pulCurrent++ = BRDC_OP_IMM_TO_REG();
		*pList->pulCurrent++ = BRDC_REGISTER(BCHP_TNT_CMP_0_V0_CTI_H);
		*pList->pulCurrent++ =
			BCHP_FIELD_ENUM(TNT_CMP_0_V0_CTI_H, FILT_SEL,   TAP7) |
			BCHP_FIELD_DATA(TNT_CMP_0_V0_CTI_H, GAIN,       ulCtiHGain) |
			BCHP_FIELD_DATA(TNT_CMP_0_V0_CTI_H, CORE_LEVEL, 0xa);
	}

	BDBG_LEAVE(BVDC_P_Tnt_BuildRul_isr);
	return;
}

void BVDC_P_Tnt_BuildVysncRul_isr
	( const BVDC_Window_Handle     hWindow,
	  BVDC_P_ListInfo             *pList )
{
	BVDC_P_Window_Info    *pCurInfo;

	BDBG_ENTER(BVDC_P_Tnt_BuildVysncRul_isr);
	BDBG_OBJECT_ASSERT(hWindow, BVDC_WIN);
	/* Get current pointer to RUL */
	pCurInfo = &hWindow->stCurInfo;

	if(pCurInfo->bSharpnessEnable)
	{
		/* TOP Control */
		*pList->pulCurrent++ = BRDC_OP_IMM_TO_REG();
		*pList->pulCurrent++ = BRDC_REGISTER(BCHP_TNT_CMP_0_V0_TOP_CONTROL);
		*pList->pulCurrent++ =
			BCHP_FIELD_ENUM(TNT_CMP_0_V0_TOP_CONTROL, UPDATE_SEL, NORMAL) |
			((pCurInfo->stSplitScreenSetting.eSharpness == BVDC_SplitScreenMode_eDisable) ?
			BCHP_FIELD_ENUM(TNT_CMP_0_V0_TOP_CONTROL, DEMO_MODE, DISABLE) :
			BCHP_FIELD_ENUM(TNT_CMP_0_V0_TOP_CONTROL, DEMO_MODE, ENABLE)) |
#if (BVDC_P_SUPPORT_TNT_VER == 6)
			BCHP_FIELD_ENUM(TNT_CMP_0_V0_TOP_CONTROL, LPEAK_INCORE_EN, ENABLE) |
			BCHP_FIELD_DATA(TNT_CMP_0_V0_TOP_CONTROL, H_WINDOW, 2) |
#endif
			BCHP_FIELD_ENUM(TNT_CMP_0_V0_TOP_CONTROL, MASTER_EN, ENABLE);
	}
	else
	{
		/* Bypass TNT */
		*pList->pulCurrent++ = BRDC_OP_IMM_TO_REG();
		*pList->pulCurrent++ = BRDC_REGISTER(BCHP_TNT_CMP_0_V0_TOP_CONTROL);
		*pList->pulCurrent++ =
#if (BVDC_P_SUPPORT_TNT_VER == 6)
			BCHP_FIELD_ENUM(TNT_CMP_0_V0_TOP_CONTROL, LPEAK_INCORE_EN, DISABLE) |
			BCHP_FIELD_DATA(TNT_CMP_0_V0_TOP_CONTROL, H_WINDOW,        2      ) |
#endif
			BCHP_FIELD_ENUM(TNT_CMP_0_V0_TOP_CONTROL, DEMO_MODE,       DISABLE) |
			BCHP_FIELD_ENUM(TNT_CMP_0_V0_TOP_CONTROL, UPDATE_SEL,      NORMAL ) |
			BCHP_FIELD_ENUM(TNT_CMP_0_V0_TOP_CONTROL, MASTER_EN,       DISABLE);
	}

	BDBG_LEAVE(BVDC_P_Tnt_BuildVysncRul_isr);
	return;
}
#else  /* TNT1 HW base */
void BVDC_P_Tnt_BuildInit_isr
	( const BVDC_Window_Handle     hWindow,
	  BVDC_P_ListInfo             *pList )
{
	BSTD_UNUSED(hWindow);
	BSTD_UNUSED(pList);
}

void BVDC_P_Tnt_BuildRul_isr
	( const BVDC_Window_Handle     hWindow,
	  BVDC_P_ListInfo             *pList )
{
	BVDC_P_Window_Info    *pCurInfo;

	BDBG_ENTER(BVDC_P_Tnt_BuildRul_isr);
	BDBG_OBJECT_ASSERT(hWindow, BVDC_WIN);
	/* Get current pointer to RUL */
	pCurInfo = &hWindow->stCurInfo;

	if(pCurInfo->bSharpnessEnable)
	{
		if(!pCurInfo->bUserSharpnessConfig)
		{
			bool bIsSd = VIDEO_FORMAT_IS_SD(hWindow->hCompositor->stCurInfo.pFmtInfo->eVideoFmt) ||
			             VIDEO_FORMAT_IS_SD(pCurInfo->hSource->stCurInfo.pFmtInfo->eVideoFmt);
			int16_t sCenterGain = (bIsSd) ? 0x1f : 0xf;
			BVDC_P_Sharpness_Calculate_Gain_Value_isr(pCurInfo->sSharpness, 0, sCenterGain, 0x3F,
			                                      &hWindow->stCurResource.hPep->ulLumaChromaGain);

			pCurInfo->stSharpnessConfig.ulLumaCtrlGain   = hWindow->stCurResource.hPep->ulLumaChromaGain;
			pCurInfo->stSharpnessConfig.ulChromaCtrlGain = hWindow->stCurResource.hPep->ulLumaChromaGain;
			pCurInfo->stSharpnessConfig.bLumaCtrlHOnly   =
				(hWindow->hCompositor->stCurInfo.pFmtInfo->bInterlaced) ? true : false;
			pCurInfo->stSharpnessConfig.bChromaCtrlHOnly =
				(hWindow->hCompositor->stCurInfo.pFmtInfo->bInterlaced) ? true : false;
		}

		/* Build RUL */
		*pList->pulCurrent++ = BRDC_OP_IMM_TO_REG();
		*pList->pulCurrent++ = BRDC_REGISTER(BCHP_TNT_CMP_0_V0_TOP_CONTROL);
		*pList->pulCurrent++ =
			BCHP_FIELD_ENUM(TNT_CMP_0_V0_TOP_CONTROL, UPDATE_SEL, EOP) |
			((pCurInfo->stSplitScreenSetting.eSharpness == BVDC_SplitScreenMode_eDisable) ?
			BCHP_FIELD_ENUM(TNT_CMP_0_V0_TOP_CONTROL, DEMO_MODE, DISABLE) :
			BCHP_FIELD_ENUM(TNT_CMP_0_V0_TOP_CONTROL, DEMO_MODE, ENABLE)) |
#if (BVDC_P_SUPPORT_TNT_VER == 2) || (BVDC_P_SUPPORT_TNT_VER >= 4)
			BCHP_FIELD_ENUM(TNT_CMP_0_V0_TOP_CONTROL, RING_SUPPION_MODE, NORMAL) |
			BCHP_FIELD_ENUM(TNT_CMP_0_V0_TOP_CONTROL, RING_SUPPION, DISABLE) |
#endif
			BCHP_FIELD_ENUM(TNT_CMP_0_V0_TOP_CONTROL, ENABLE, ENABLE);

		*pList->pulCurrent++ = BRDC_OP_IMM_TO_REG();
		*pList->pulCurrent++ = BRDC_REGISTER(BCHP_TNT_CMP_0_V0_LUMA_CONTROL);
		*pList->pulCurrent++ =
			BCHP_FIELD_DATA(TNT_CMP_0_V0_LUMA_CONTROL, SCRATCH, 0x0) |
			BCHP_FIELD_DATA(TNT_CMP_0_V0_LUMA_CONTROL, CORE,
				pCurInfo->stSharpnessConfig.ulLumaCtrlCore ) |
			BCHP_FIELD_DATA(TNT_CMP_0_V0_LUMA_CONTROL, GAIN,
				pCurInfo->stSharpnessConfig.ulLumaCtrlGain ) |
			BCHP_FIELD_DATA(TNT_CMP_0_V0_LUMA_CONTROL, BLUR,
				pCurInfo->stSharpnessConfig.ulLumaCtrlBlur )|
			BCHP_FIELD_DATA(TNT_CMP_0_V0_LUMA_CONTROL, SOFTEN,
				pCurInfo->stSharpnessConfig.bLumaCtrlSoften )|
			BCHP_FIELD_DATA(TNT_CMP_0_V0_LUMA_CONTROL, H_ONLY,
				pCurInfo->stSharpnessConfig.bLumaCtrlHOnly );

		*pList->pulCurrent++ = BRDC_OP_IMM_TO_REG();
		*pList->pulCurrent++ = BRDC_REGISTER(BCHP_TNT_CMP_0_V0_LUMA_PEAKING);
		*pList->pulCurrent++ =
			BCHP_FIELD_DATA(TNT_CMP_0_V0_LUMA_PEAKING, H_AVOID,
				pCurInfo->stSharpnessConfig.ulLumaPeakingHAvoid ) |
			BCHP_FIELD_DATA(TNT_CMP_0_V0_LUMA_PEAKING, V_AVOID,
				pCurInfo->stSharpnessConfig.ulLumaPeakingVAvoid ) |
			BCHP_FIELD_DATA(TNT_CMP_0_V0_LUMA_PEAKING, PEAK_LIMIT,
				pCurInfo->stSharpnessConfig.ulLumaPeakingPeakLimit ) |
			BCHP_FIELD_DATA(TNT_CMP_0_V0_LUMA_PEAKING, PEAK_VALUE,
				pCurInfo->stSharpnessConfig.ulLumaPeakingPeakValue ) ;

		*pList->pulCurrent++ = BRDC_OP_IMM_TO_REG();
		*pList->pulCurrent++ = BRDC_REGISTER(BCHP_TNT_CMP_0_V0_CHROMA_CONTROL);
		*pList->pulCurrent++ =
			BCHP_FIELD_DATA(TNT_CMP_0_V0_CHROMA_CONTROL, SCRATCH, 0x0) |
			BCHP_FIELD_DATA(TNT_CMP_0_V0_CHROMA_CONTROL, CORE,
				pCurInfo->stSharpnessConfig.ulChromaCtrlCore ) |
			BCHP_FIELD_DATA(TNT_CMP_0_V0_CHROMA_CONTROL, WIDE_CHROMA,
				pCurInfo->stSharpnessConfig.bChromaCtrlWideChroma ) |
			BCHP_FIELD_DATA(TNT_CMP_0_V0_CHROMA_CONTROL, FALSE_COLOR,
				pCurInfo->stSharpnessConfig.ulChromaCtrlFalseColor ) |
			BCHP_FIELD_DATA(TNT_CMP_0_V0_CHROMA_CONTROL, GAIN,
				pCurInfo->stSharpnessConfig.ulChromaCtrlGain ) |
			BCHP_FIELD_DATA(TNT_CMP_0_V0_CHROMA_CONTROL, H_ONLY,
				pCurInfo->stSharpnessConfig.bChromaCtrlHOnly );

		*pList->pulCurrent++ = BRDC_OP_IMM_TO_REG();
		*pList->pulCurrent++ = BRDC_REGISTER(BCHP_TNT_CMP_0_V0_LC_ALIGN_CONTROL);
		*pList->pulCurrent++ =
			BCHP_FIELD_ENUM(TNT_CMP_0_V0_LC_ALIGN_CONTROL, ALIGN_CR_CB, SEL_CB) |
			BCHP_FIELD_DATA(TNT_CMP_0_V0_LC_ALIGN_CONTROL, RESET_COUNTER, 0x0);

		*pList->pulCurrent++ = BRDC_OP_IMM_TO_REG();
		*pList->pulCurrent++ = BRDC_REGISTER(BCHP_TNT_CMP_0_V0_WIDE_LUMA_CONTROL );
		*pList->pulCurrent++ =
			BCHP_FIELD_DATA(TNT_CMP_0_V0_WIDE_LUMA_CONTROL, CORE,
				pCurInfo->stSharpnessConfig.ulWideLumaCtrlCore ) |
			BCHP_FIELD_DATA(TNT_CMP_0_V0_WIDE_LUMA_CONTROL, MODE,
				pCurInfo->stSharpnessConfig.ulWideLumaCtrlMode ) ;
#if (BVDC_P_SUPPORT_TNT_VER >= 3)
		*pList->pulCurrent++ = BRDC_OP_IMM_TO_REG();
		*pList->pulCurrent++ = BRDC_REGISTER(BCHP_TNT_CMP_0_V0_SIMPLE_LUMA_CORE_CTRL);
		*pList->pulCurrent++ =
			BCHP_FIELD_DATA(TNT_CMP_0_V0_SIMPLE_LUMA_CORE_CTRL , CORE,
				pCurInfo->stSharpnessConfig.ulSimpleLumaCtrlCore) |
			BCHP_FIELD_DATA(TNT_CMP_0_V0_SIMPLE_LUMA_CORE_CTRL , MODE,
				pCurInfo->stSharpnessConfig.bSimpleLumaCtrlMode);
#endif

		/* Setting up the demo mode register */
		if(pCurInfo->stSplitScreenSetting.eSharpness != BVDC_SplitScreenMode_eDisable)
		{
			uint32_t ulBoundary = hWindow->stAdjDstRect.ulWidth / 2;
			uint32_t ulDemoSide = (pCurInfo->stSplitScreenSetting.eSharpness == BVDC_SplitScreenMode_eLeft) ?
			                       BCHP_TNT_CMP_0_V0_DEMO_SETTING_DEMO_L_R_LEFT :
			                       BCHP_TNT_CMP_0_V0_DEMO_SETTING_DEMO_L_R_RIGHT;

			*pList->pulCurrent++ = BRDC_OP_IMM_TO_REG();
			*pList->pulCurrent++ = BRDC_REGISTER(BCHP_TNT_CMP_0_V0_DEMO_SETTING);
			*pList->pulCurrent++ =
				BCHP_FIELD_DATA(TNT_CMP_0_V0_DEMO_SETTING, DEMO_L_R, ulDemoSide) |
				BCHP_FIELD_DATA(TNT_CMP_0_V0_DEMO_SETTING, DEMO_BOUNDARY, ulBoundary) ;

			BDBG_MSG(("TNT Demo Mode: L_R = %s, BOUNDARY = %d",
			          ((ulDemoSide == BCHP_TNT_CMP_0_V0_DEMO_SETTING_DEMO_L_R_LEFT) ? "L" : "R"),
			          ulBoundary));
		}
	}
	else
	{
		/* Bypass TNT */
		BDBG_MSG(("Bypass TNT"));
		*pList->pulCurrent++ = BRDC_OP_IMM_TO_REG();
		*pList->pulCurrent++ = BRDC_REGISTER(BCHP_TNT_CMP_0_V0_TOP_CONTROL);
		*pList->pulCurrent++ =
			BCHP_FIELD_ENUM(TNT_CMP_0_V0_TOP_CONTROL, UPDATE_SEL, NORMAL) |
			BCHP_FIELD_ENUM(TNT_CMP_0_V0_TOP_CONTROL, DEMO_MODE, DISABLE) |
#if (BVDC_P_SUPPORT_TNT_VER == 2) || (BVDC_P_SUPPORT_TNT_VER >= 4)
			BCHP_FIELD_ENUM(TNT_CMP_0_V0_TOP_CONTROL, RING_SUPPION_MODE, NORMAL) |
			BCHP_FIELD_ENUM(TNT_CMP_0_V0_TOP_CONTROL, RING_SUPPION, DISABLE) |
#endif
			BCHP_FIELD_ENUM(TNT_CMP_0_V0_TOP_CONTROL, ENABLE, BYPASS);

#if (BVDC_P_SUPPORT_TNT_VER >= 3)
			*pList->pulCurrent++ = BRDC_OP_IMM_TO_REG();
			*pList->pulCurrent++ = BRDC_REGISTER(BCHP_TNT_CMP_0_V0_SIMPLE_LUMA_CORE_CTRL);
			*pList->pulCurrent++ =
				BCHP_FIELD_DATA(TNT_CMP_0_V0_SIMPLE_LUMA_CORE_CTRL , CORE, 0x0	 ) |
				BCHP_FIELD_ENUM(TNT_CMP_0_V0_SIMPLE_LUMA_CORE_CTRL , MODE, DISABLE);
#endif
	}

	BDBG_LEAVE(BVDC_P_Tnt_BuildRul_isr);
	return;
}

void BVDC_P_Tnt_BuildVysncRul_isr
	( const BVDC_Window_Handle     hWindow,
	  BVDC_P_ListInfo             *pList )
{
	BSTD_UNUSED(hWindow);
	BSTD_UNUSED(pList);
}
#endif /* TNT1 HW base */
#else  /* BVDC_P_SUPPORT_TNT == 0*/
void BVDC_P_Tnt_BuildInit_isr
	( const BVDC_Window_Handle     hWindow,
	  BVDC_P_ListInfo             *pList )
{
	BSTD_UNUSED(hWindow);
	BSTD_UNUSED(pList);
}
void BVDC_P_Tnt_BuildRul_isr
	( const BVDC_Window_Handle     hWindow,
	  BVDC_P_ListInfo             *pList )
{
	BSTD_UNUSED(hWindow);
	BSTD_UNUSED(pList);
}

void BVDC_P_Tnt_BuildVysncRul_isr
	( const BVDC_Window_Handle     hWindow,
	  BVDC_P_ListInfo             *pList )
{
	BSTD_UNUSED(hWindow);
	BSTD_UNUSED(pList);
}
#endif /* BVDC_P_SUPPORT_TNT */

/* End of File */

/***************************************************************************
 *     Copyright (c) 2003-2014, Broadcom Corporation
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
 * Module Description:
 *     Private module for setting up the modular Vec
 *
 * Revision History:
 *
 * $brcm_Log: $
 *
 ***************************************************************************/

#include "bstd.h"
#include "bdbg.h"
#include "bfmt.h"

/* Note: Tricky here!  bavc.h needs bchp_gfd_x.h defininitions.
 * The check here is to see if chips has more than one gfx feeder. */
#include "bchp_gfd_0.h"
#include "bchp_gfd_1.h"

#include "bavc.h"
#include "bvdc_compositor_priv.h"
#include "bvdc_displayfmt_priv.h"
#include "bvdc_displayvip_priv.h"
#include "bvdc_common_priv.h"

#include "bchp_sun_top_ctrl.h"
#include "bchp_misc.h"
#include "bchp_timer.h"

#include "bchp_it_0.h"

#if BVDC_P_SUPPORT_ITU656_OUT
#include "bchp_itu656_dtg_0.h"
#endif

#if BVDC_P_SUPPORT_DVI_OUT
#include "bchp_dvi_dtg_0.h"
#endif

/* VCXO_RM in the following chipsets need to be reserved since vec core
   reset would reset VCXO_RM also! */
#ifdef BCHP_VCXO_0_RM_REG_START
#include "bchp_vcxo_0_rm.h"
#define BVDC_P_VCXO_RM_REG_COUNT \
	((BCHP_VCXO_0_RM_REG_END - BCHP_VCXO_0_RM_REG_START) / sizeof(uint32_t) + 1)
#endif
#ifdef BCHP_VCXO_1_RM_REG_START
#include "bchp_vcxo_1_rm.h"
#endif
#ifdef BCHP_VCXO_2_RM_REG_START
#include "bchp_vcxo_2_rm.h"
#endif

BDBG_MODULE(BVDC_DISP);
BDBG_OBJECT_ID(BVDC_DSP);

#define HW7425_807_IS_FIXED 0

/***************** RM clock adjustment macroes *************/
#define BVDC_P_DISPLAY_RM_PHASE_INC_REG_OFFSET \
	((BCHP_RM_0_PHASE_INC - BCHP_RM_0_RATE_RATIO) / sizeof(uint32_t))


/*************************************************************************
 * BVDC_P_Display_Create
 *
 *************************************************************************/
BERR_Code BVDC_P_Display_Create
(
	BVDC_P_Context                  *pVdc,
	BVDC_Display_Handle             *phDisplay,
	BVDC_DisplayId                   eId
)
{
	BVDC_P_DisplayContext *pDisplay;

	BDBG_ENTER(BVDC_P_Display_Create);

	/* (1) Allocate display context */
	pDisplay = (BVDC_P_DisplayContext*)
		(BKNI_Malloc(sizeof(BVDC_P_DisplayContext)));
	if(!pDisplay)
	{
		return BERR_TRACE(BERR_OUT_OF_SYSTEM_MEMORY);
	}

	/* Initialize to zero */
	BKNI_Memset((void*)pDisplay, 0x0, sizeof(BVDC_P_DisplayContext));
	BDBG_OBJECT_SET(pDisplay, BVDC_DSP);

	/* Initialize non-changing states.  These are not to be changed by runtime. */
	pDisplay->ulRdcVarAddr      = BRDC_AllocScratchReg(pVdc->hRdc);
    BDBG_MSG(("Display %d allocates ulRdcVarAddr register 0x%x", eId, pDisplay->ulRdcVarAddr));
	if(pDisplay->ulRdcVarAddr == 0)
	{
		BDBG_ERR(("Not enough scratch registers for display	format switch!"));
		BKNI_Free((void*)pDisplay);
		return BERR_TRACE(BERR_INVALID_PARAMETER);
	}

#if (!BVDC_P_USE_RDC_TIMESTAMP)
	pDisplay->ulScratchTsAddr = BRDC_AllocScratchReg(pVdc->hRdc);
	if(pDisplay->ulScratchTsAddr == 0)
	{
		BDBG_ERR(("Not enough scratch registers for display Timestamp!"));
		BRDC_FreeScratchReg(pDisplay->hVdc->hRdc, pDisplay->ulRdcVarAddr);
		BKNI_Free((void*)pDisplay);
		return BERR_TRACE(BERR_INVALID_PARAMETER);
	}
#endif

#if (BVDC_P_STG_RUL_DELAY_WORKAROUND)
	/* Dummy register for RUL delay due to MADR BW issue */
	pDisplay->ulScratchDummyAddr = BRDC_AllocScratchReg(pVdc->hRdc);
	if(pDisplay->ulScratchDummyAddr == 0)
	{
		BDBG_ERR(("Not enough scratch registers for display Timestamp!"));
		BRDC_FreeScratchReg(pDisplay->hVdc->hRdc, pDisplay->ulRdcVarAddr);
#if (!BVDC_P_USE_RDC_TIMESTAMP)
		BRDC_FreeScratchReg(pDisplay->hVdc->hRdc, pDisplay->ulScratchTsAddr);
#endif
		BKNI_Free((void*)pDisplay);
		return BERR_TRACE(BERR_INVALID_PARAMETER);
	}
#endif

#if (!BVDC_P_USE_RDC_TIMESTAMP)
	pDisplay->hTimer            = pVdc->hTimer;
	BTMR_GetTimerRegisters(pDisplay->hTimer, &pDisplay->stTimerReg);
#endif

	pDisplay->eId               = eId;
	pDisplay->hVdc              = (BVDC_Handle)pVdc;
	pDisplay->bIsBypass         = pVdc->pFeatures->bCmpBIsBypass &&
		(BVDC_DisplayId_eDisplay2 == eId);

	pDisplay->aulMpaaDeciIfPortMask[BVDC_MpaaDeciIf_eHdmi]      = BVDC_Hdmi_0;
	pDisplay->aulMpaaDeciIfPortMask[BVDC_MpaaDeciIf_eComponent] = BVDC_Cmpnt_0;
	pDisplay->stMpaaComp.eState = BVDC_P_DisplayResource_eInactive;
	pDisplay->stMpaaComp.ulHwId = BVDC_P_HW_ID_INVALID;
	pDisplay->stMpaaHdmi.eState = BVDC_P_DisplayResource_eInactive;
	pDisplay->stMpaaHdmi.ulHwId = BVDC_P_HW_ID_INVALID;

#if DCS_SUPPORT /** { **/
#if 0
	BDBG_ASSERT (pDisplay->ulDcsScratch[0] = BRDC_AllocScratchReg(pVdc->hRdc));
	BDBG_ASSERT (pDisplay->ulDcsScratch[1] = BRDC_AllocScratchReg(pVdc->hRdc));
	BDBG_ASSERT (pDisplay->ulDcsScratch[2] = BRDC_AllocScratchReg(pVdc->hRdc));
	BDBG_ASSERT (pDisplay->ulDcsScratch[3] = BRDC_AllocScratchReg(pVdc->hRdc));
	printf ("\nDCS scratch registers for IT_%d: %08x %08x %08x %08x\n\n",
		pDisplay->eId,
		pDisplay->ulDcsScratch[0],
		pDisplay->ulDcsScratch[1],
		pDisplay->ulDcsScratch[2],
		pDisplay->ulDcsScratch[3]);
#endif
#endif /** } DCS_SUPPORT **/

	/* (2) create a AppliedDone event. */
	BKNI_CreateEvent(&pDisplay->hAppliedDoneEvent);

	/* (3) Save hDisplay in hVdc */
	pVdc->ahDisplay[pDisplay->eId] = (BVDC_Display_Handle)pDisplay;

	*phDisplay = (BVDC_Display_Handle)pDisplay;

	/* assert assumption for the shared usage of BVDC_P_GetVecCfgSrc() */
	BDBG_CASSERT(BCHP_VEC_CFG_IT_0_SOURCE_SOURCE_S_0 == BCHP_VEC_CFG_DVI_DTG_0_SOURCE_SOURCE_S_0);
#ifdef BCHP_VEC_CFG_ITU656_DTG_0_SOURCE_SOURCE_S_0
	BDBG_CASSERT(BCHP_VEC_CFG_IT_0_SOURCE_SOURCE_S_0 == BCHP_VEC_CFG_ITU656_DTG_0_SOURCE_SOURCE_S_0);
#endif
	BDBG_CASSERT(BCHP_VEC_CFG_IT_0_SOURCE_SOURCE_S_0 == BCHP_VEC_CFG_DECIM_0_SOURCE_SOURCE_S_0);
	BDBG_CASSERT(BCHP_VEC_CFG_IT_0_SOURCE_SOURCE_S_1 == BCHP_VEC_CFG_DVI_DTG_0_SOURCE_SOURCE_S_1);
#ifdef BCHP_VEC_CFG_ITU656_DTG_0_SOURCE_SOURCE_S_1
	BDBG_CASSERT(BCHP_VEC_CFG_IT_0_SOURCE_SOURCE_S_1 == BCHP_VEC_CFG_ITU656_DTG_0_SOURCE_SOURCE_S_1);
#endif
	BDBG_CASSERT(BCHP_VEC_CFG_IT_0_SOURCE_SOURCE_S_1 == BCHP_VEC_CFG_DECIM_0_SOURCE_SOURCE_S_1);
#if (BVDC_P_CMP_2_MAX_VIDEO_WINDOW_COUNT > 0)
	BDBG_CASSERT(BCHP_VEC_CFG_IT_0_SOURCE_SOURCE_S_2 == BCHP_VEC_CFG_DVI_DTG_0_SOURCE_SOURCE_S_2);
	BDBG_CASSERT(BCHP_VEC_CFG_IT_0_SOURCE_SOURCE_S_2 == BCHP_VEC_CFG_ITU656_DTG_0_SOURCE_SOURCE_S_2);
	BDBG_CASSERT(BCHP_VEC_CFG_IT_0_SOURCE_SOURCE_S_2 == BCHP_VEC_CFG_DECIM_0_SOURCE_SOURCE_S_2);
#endif
#if (BVDC_P_CMP_3_MAX_VIDEO_WINDOW_COUNT > 0)
	BDBG_CASSERT(BCHP_VEC_CFG_IT_0_SOURCE_SOURCE_S_3 == BCHP_VEC_CFG_DVI_DTG_0_SOURCE_SOURCE_S_3);
	BDBG_CASSERT(BCHP_VEC_CFG_IT_0_SOURCE_SOURCE_S_3 == BCHP_VEC_CFG_ITU656_DTG_0_SOURCE_SOURCE_S_3);
	BDBG_CASSERT(BCHP_VEC_CFG_IT_0_SOURCE_SOURCE_S_3 == BCHP_VEC_CFG_DECIM_0_SOURCE_SOURCE_S_3);
#endif
#if (BVDC_P_CMP_4_MAX_VIDEO_WINDOW_COUNT > 0)
	BDBG_CASSERT(BCHP_VEC_CFG_IT_0_SOURCE_SOURCE_S_4 == BCHP_VEC_CFG_DVI_DTG_0_SOURCE_SOURCE_S_4);
	BDBG_CASSERT(BCHP_VEC_CFG_IT_0_SOURCE_SOURCE_S_4 == BCHP_VEC_CFG_ITU656_DTG_0_SOURCE_SOURCE_S_4);
	BDBG_CASSERT(BCHP_VEC_CFG_IT_0_SOURCE_SOURCE_S_4 == BCHP_VEC_CFG_DECIM_0_SOURCE_SOURCE_S_4);
#endif
#if (BVDC_P_CMP_5_MAX_VIDEO_WINDOW_COUNT > 0)
	BDBG_CASSERT(BCHP_VEC_CFG_IT_0_SOURCE_SOURCE_S_5 == BCHP_VEC_CFG_DVI_DTG_0_SOURCE_SOURCE_S_5);
	BDBG_CASSERT(BCHP_VEC_CFG_IT_0_SOURCE_SOURCE_S_5 == BCHP_VEC_CFG_ITU656_DTG_0_SOURCE_SOURCE_S_5);
	BDBG_CASSERT(BCHP_VEC_CFG_IT_0_SOURCE_SOURCE_S_5 == BCHP_VEC_CFG_DECIM_0_SOURCE_SOURCE_S_5);
#endif

	BDBG_LEAVE(BVDC_P_Display_Create);
	return BERR_SUCCESS;
}


/***************************************************************************
 * {private}
 *
 */
void BVDC_P_Display_Init
	( BVDC_Display_Handle              hDisplay )
{
	uint32_t i;
	/* coverity[result_independent_of_operands: FALSE] */
	BVDC_P_CscCoeffs stIdentity = BVDC_P_MAKE_DVO_CSC
		(1.0000, 0.0000, 0.0000, 0.0000,
		 0.0000, 1.0000, 0.0000, 0.0000,
		 0.0000, 0.0000, 1.0000, 0.0000);
	uint32_t  ulLfsrCtrlT0, ulLfsrCtrlT1, ulLfsrCtrlT2, ulLfsrValue;
	BFMT_VideoInfo *pCustomFmtInfo = NULL;

	BDBG_ENTER(BVDC_P_Display_Init);
	BDBG_OBJECT_ASSERT(hDisplay, BVDC_DSP);

	BKNI_Memset((void*)&hDisplay->stNewInfo, 0x0, sizeof(BVDC_P_DisplayInfo));
	BKNI_Memset((void*)&hDisplay->stCurInfo, 0x0, sizeof(BVDC_P_DisplayInfo));
	BDBG_CASSERT(sizeof(hDisplay->stNewInfo.stDirty.stBits) <= sizeof(hDisplay->stNewInfo.stDirty.aulInts));

	hDisplay->stNewInfo.bErrorLastSetting = false;

	/* set default timebase for most common sand simplest usage:
	 * HD/SD simul displays  -> timebase 0 that tracks the single video input;
	 * Note:
	 *  There is no good default timebase for displays as it depends on the system usages.
	 *  NEXUS/App should configure display timebase according to the system config.
	 * Example system timebase config:
	 *  1) decoder 0 -> main windows of HD/SD simul displays -> timebase 0 that tracks decoder 0's live input PCR;
	 *  2) HDMI input -> PIP windows of HD/SD simul displays -> timebase 1 that tracks HDMI input's HSYNC time reference;
	 *  3) decoder 2 -> transcode window of encoder display 2 -> timebase 2 that is freerun if decoder 2's input comes from file playback. */
	hDisplay->stNewInfo.eTimeBase = BAVC_Timebase_e0;
	hDisplay->stNewInfo.stDirty.stBits.bTimeBase = BVDC_P_DIRTY;

	/* Default Dacs to unused */
	for(i=0; i < BVDC_P_MAX_DACS; i++)
	{
		hDisplay->stNewInfo.aDacOutput[i] = BVDC_DacOutput_eUnused;
	}
	hDisplay->stNewInfo.stDirty.stBits.bDacSetting = BVDC_P_DIRTY;
	hDisplay->stNewInfo.stDirty.stBits.bAcp        = BVDC_P_DIRTY;

#if	(BVDC_P_SUPPORT_IT_VER >= 2)
	hDisplay->stNewInfo.ulTriggerModuloCnt = 1;
#endif

	/* Init video format */
	hDisplay->stNewInfo.pFmtInfo   = BFMT_GetVideoFormatInfoPtr(hDisplay->hVdc->stSettings.eVideoFormat);
	hDisplay->stNewInfo.ulVertFreq = hDisplay->stNewInfo.pFmtInfo->ulVertFreq;
	hDisplay->stNewInfo.ulHeight   = (hDisplay->stNewInfo.pFmtInfo->bInterlaced) ?
		hDisplay->stNewInfo.pFmtInfo->ulHeight / BVDC_P_FIELD_PER_FRAME:
		hDisplay->stNewInfo.pFmtInfo->ulHeight;

	/*Init custom format */
	pCustomFmtInfo = &hDisplay->stNewInfo.stCustomFmt;
	pCustomFmtInfo->eVideoFmt = BFMT_VideoFmt_eCustom2;
	pCustomFmtInfo->ulDigitalWidth  = pCustomFmtInfo->ulScanWidth  = pCustomFmtInfo->ulWidth = 352;
	pCustomFmtInfo->ulDigitalHeight = pCustomFmtInfo->ulScanHeight = pCustomFmtInfo->ulWidth = 288;
	pCustomFmtInfo->ulTopActive = pCustomFmtInfo->ulActiveSpace
		= pCustomFmtInfo->ulTopMaxVbiPassThru = pCustomFmtInfo->ulBotMaxVbiPassThru = 0;
	pCustomFmtInfo->ulVertFreq     = 5000;
	pCustomFmtInfo->ulPxlFreqMask  = BFMT_PXL_27MHz;
	pCustomFmtInfo->bInterlaced    = false,
	pCustomFmtInfo->eAspectRatio   = BFMT_AspectRatio_e4_3,
	pCustomFmtInfo->eOrientation   = BFMT_Orientation_e2D,
	pCustomFmtInfo->ulPxlFreq      = 2700,
	pCustomFmtInfo->pchFormatStr   = BDBG_STRING("BFMT_VideoFmt_eCustom2");
	pCustomFmtInfo->pCustomInfo    = NULL;

	/* Init display aspect ratio */
	hDisplay->stNewInfo.eAspectRatio = hDisplay->stNewInfo.pFmtInfo->eAspectRatio;
	BVDC_P_CalcuPixelAspectRatio_isr(
		hDisplay->stNewInfo.eAspectRatio,
		hDisplay->stNewInfo.uiSampleAspectRatioX,
		hDisplay->stNewInfo.uiSampleAspectRatioY,
		hDisplay->stNewInfo.pFmtInfo->ulDigitalWidth, hDisplay->stNewInfo.pFmtInfo->ulDigitalHeight,
		&hDisplay->stNewInfo.stAspRatRectClip,
		&hDisplay->ulPxlAspRatio,
		&hDisplay->ulPxlAspRatio_x_y,
		BFMT_Orientation_e2D);
	hDisplay->stNewInfo.stDirty.stBits.bAspRatio = BVDC_P_DIRTY;

	/* Initialize output color space */
	hDisplay->stNewInfo.eAnlg_0_OutputColorSpace = BVDC_P_Output_eUnknown;
	hDisplay->stNewInfo.eAnlg_1_OutputColorSpace = BVDC_P_Output_eUnknown;

	/* Initialize analog dac masks */
	hDisplay->stNewInfo.ulAnlgChan0Mask = 0;
	hDisplay->stNewInfo.ulAnlgChan0Mask = 0;

	/* Initialize output mute flags */
	BKNI_Memset(hDisplay->stNewInfo.abOutputMute, false, sizeof(hDisplay->stNewInfo.abOutputMute));

	/* set default display input color space.
	 * NOTE: primary and secondary displays will always take HD color space input
	 * from compositors; while the bypass display input color space could be SD
	 * or HD depends on the VDEC source format. */
	hDisplay->stNewInfo.eCmpColorSpace = BVDC_P_CmpColorSpace_eHdYCrCb;

	/* Current display rate info, update at least once at initialization */
	hDisplay->stNewInfo.stRateInfo.ulPixelClkRate    = 0;
	hDisplay->stNewInfo.stRateInfo.ulPixelClockRate  = 0;
	hDisplay->stNewInfo.stRateInfo.ulVertRefreshRate = 0;
	hDisplay->stNewInfo.bFullRate =
		BVDC_P_IS_FULL_FRAMRATE(hDisplay->hVdc->stSettings.eDisplayFrameRate);

	/* the bFormat dirty bit covers the above info */
	hDisplay->stNewInfo.stDirty.stBits.bTiming = BVDC_P_DIRTY;
	hDisplay->stNewInfo.stDirty.stBits.bAcp    = BVDC_P_DIRTY;

	/* Initialize Rfm output */
	hDisplay->stNewInfo.eRfmOutput = BVDC_RfmOutput_eUnused;

	/* Set Hdmi default */
	hDisplay->stNewInfo.ulHdmi      = BVDC_Hdmi_0;
	hDisplay->stNewInfo.eHdmiOutput = BAVC_MatrixCoefficients_eUnknown;
	hDisplay->stNewInfo.bEnableHdmi = false;
	hDisplay->stNewInfo.stHdmiSettings.stSettings.eColorComponent = BAVC_Colorspace_eYCbCr444;

	/* Default Dvo CSC */
	hDisplay->stDvoCscMatrix.ulMin       = 0x0000;
	hDisplay->stDvoCscMatrix.ulMax       = 0x0fff;
	hDisplay->stDvoCscMatrix.stCscCoeffs = stIdentity;
	hDisplay->stNewInfo.bUserCsc         = false;

	/* Dvo CSC adjustment values */
	hDisplay->stNewInfo.lDvoAttenuationR = BMTH_FIX_SIGNED_ITOFIX(1, BVDC_P_CSC_DVO_CX_I_BITS, BVDC_P_CSC_DVO_CX_F_BITS);
	hDisplay->stNewInfo.lDvoAttenuationG = BMTH_FIX_SIGNED_ITOFIX(1, BVDC_P_CSC_DVO_CX_I_BITS, BVDC_P_CSC_DVO_CX_F_BITS);
	hDisplay->stNewInfo.lDvoAttenuationB = BMTH_FIX_SIGNED_ITOFIX(1, BVDC_P_CSC_DVO_CX_I_BITS, BVDC_P_CSC_DVO_CX_F_BITS);
	hDisplay->stNewInfo.lDvoOffsetR      = 0;
	hDisplay->stNewInfo.lDvoOffsetG      = 0;
	hDisplay->stNewInfo.lDvoOffsetB      = 0;

	/* Initialize analog channel ids */
	hDisplay->stAnlgChan_0.ulId          = 0;
	hDisplay->stAnlgChan_1.ulId          = 1;

	/* Initialize STG reg offset   */
	hDisplay->ulStgRegOffset             = 0;

#if BVDC_P_SUPPORT_STG
	hDisplay->eStgRampFmt = BFMT_VideoFmt_eMaxCount;
	hDisplay->stNewInfo.bEnableStg = hDisplay->stStgChan.bEnable;
#if (BVDC_P_SUPPORT_STG > 1)
	if(BVDC_P_DISPLAY_USED_STG(hDisplay->eMasterTg))
	hDisplay->ulStgRegOffset = (hDisplay->eMasterTg - BVDC_DisplayTg_eStg0) *
		(BCHP_VIDEO_ENC_STG_1_REG_START - BCHP_VIDEO_ENC_STG_0_REG_START);
#else
	hDisplay->ulStgRegOffset = 0;
#endif
	BKNI_EnterCriticalSection();
	BVDC_P_Stg_Init_isr(hDisplay);
	BKNI_LeaveCriticalSection();
#endif

	/* VF filters */
	BKNI_Memset(hDisplay->stNewInfo.abUserVfFilterCo, false, sizeof(hDisplay->stNewInfo.abUserVfFilterCo));
	BKNI_Memset(hDisplay->stNewInfo.abUserVfFilterCvbs, false, sizeof(hDisplay->stNewInfo.abUserVfFilterCvbs));
	BKNI_Memset(hDisplay->stNewInfo.aaulUserVfFilterCo, 0, sizeof(hDisplay->stNewInfo.aaulUserVfFilterCo));
	BKNI_Memset(hDisplay->stNewInfo.aaulUserVfFilterCvbs, 0, sizeof(hDisplay->stNewInfo.aaulUserVfFilterCvbs));
	BKNI_Memset(hDisplay->stAnlgChan_0.apVfFilter, 0, sizeof(hDisplay->stAnlgChan_0.apVfFilter));
	BKNI_Memset(hDisplay->stAnlgChan_1.apVfFilter, 0, sizeof(hDisplay->stAnlgChan_1.apVfFilter));

	/* Set 656 default */
	hDisplay->stNewInfo.bEnable656 = false;

	/* Callback */
	hDisplay->stNewInfo.pfGenericCallback = NULL;
	hDisplay->stNewInfo.pvGenericParm1    = NULL;
	hDisplay->stNewInfo.iGenericParm2     = 0;
	hDisplay->stNewInfo.stDirty.stBits.bCallback = BVDC_P_DIRTY;

	hDisplay->bSetEventPending  = false;
	BKNI_ResetEvent(hDisplay->hAppliedDoneEvent);

	/* Vec is not alive yet */
	hDisplay->eItState = BVDC_P_ItState_eNotActive;
	hDisplay->eState   = BVDC_P_State_eInactive;

	/* Game mode off */
	hDisplay->hWinGameMode = NULL;
	hDisplay->pRmTable     = NULL;
	hDisplay->bRmAdjusted = false;

	/* alignment off */
	hDisplay->eTimeStampPolarity   = BAVC_Polarity_eTopField;
	hDisplay->stNewInfo.hTargetDisplay = NULL;

	/* Dither init */
	/* PRIM_CSC_DITHER */

	/* DVI_CSC_DITHER */
	ulLfsrCtrlT0 = BVDC_P_DITHER_DISP_DVI_LFSR_CTRL_T0;
	ulLfsrCtrlT1 = BVDC_P_DITHER_DISP_DVI_LFSR_CTRL_T1;
	ulLfsrCtrlT2 = BVDC_P_DITHER_DISP_DVI_LFSR_CTRL_T2;
	ulLfsrValue  = BVDC_P_DITHER_DISP_DVI_LFSR_VALUE;
	BVDC_P_Dither_Init(&hDisplay->stDviDither,
		ulLfsrCtrlT0, ulLfsrCtrlT1, ulLfsrCtrlT2, ulLfsrValue);

	/* CSC_DITHER */
	BVDC_P_Dither_Init(&hDisplay->st656Dither,
		ulLfsrCtrlT0, ulLfsrCtrlT1, ulLfsrCtrlT2, ulLfsrValue);
	/* Special settings for 656. Default is always 1 */
	hDisplay->st656Dither.ulCh0Scale = BVDC_P_DITHER_DISP_CSC_SCALE_CH0;
	hDisplay->st656Dither.ulCh1Scale = BVDC_P_DITHER_DISP_CSC_SCALE_CH1;
	hDisplay->st656Dither.ulCh2Scale = BVDC_P_DITHER_DISP_CSC_SCALE_CH2;

	/* 4kx2k support */
	hDisplay->stNewInfo.stHdmiSettings.eHDMIFormat = BFMT_VideoFmt_eMaxCount;
	hDisplay->stNewInfo.stHdmiSettings.eMatchingFormat = BFMT_VideoFmt_eMaxCount;

	/* Same as new */
	hDisplay->stCurInfo = hDisplay->stNewInfo;

	hDisplay->pStgFmtInfo = NULL;

    hDisplay->ulVsyncCnt = 0;

    if (BVDC_P_DISPLAY_USED_DIGTRIG(hDisplay->eMasterTg))
    {
        if (BVDC_P_DISPLAY_USED_DVI(hDisplay->eMasterTg))
        {
            hDisplay->ulItLctrReg = BCHP_DVI_DTG_0_DTG_LCNTR + hDisplay->stDviChan.ulDviRegOffset;
        }
        else
        {
#if BVDC_P_SUPPORT_ITU656_OUT
            hDisplay->ulItLctrReg = BCHP_ITU656_DTG_0_DTG_LCNTR;
#else
            hDisplay->ulItLctrReg = 0x0;
            BDBG_WRN(("Creating 656 display object but chip doesn't support it."));
#endif
        }
    }
    else
    {
        hDisplay->ulItLctrReg = BCHP_IT_0_IT_LCNTR + hDisplay->stAnlgChan_0.ulItRegOffset;
    }

	BDBG_LEAVE(BVDC_P_Display_Init);
	return;
}


/***************************************************************************
 * {private}
 *
 */
void BVDC_P_Display_Destroy
	( BVDC_Display_Handle              hDisplay )
{
	BDBG_ENTER(BVDC_P_Display_Destroy);
	if(!hDisplay)
	{
		BDBG_LEAVE(BVDC_P_Display_Destroy);
		return;
	}

	BDBG_OBJECT_ASSERT(hDisplay, BVDC_DSP);
	BDBG_OBJECT_ASSERT(hDisplay->hVdc, BVDC_VDC);

	/* At this point application should have disabled all the
	 * callbacks &slots */

	/* [3] Remove display handle from main VDC handle */
	hDisplay->hVdc->ahDisplay[hDisplay->eId] = NULL;

	/* [2] Destroy event */
	BKNI_DestroyEvent(hDisplay->hAppliedDoneEvent);

	/* [1] Release RDC scratch register before release context */
#if (!BVDC_P_USE_RDC_TIMESTAMP)
	BRDC_FreeScratchReg(hDisplay->hVdc->hRdc, hDisplay->ulScratchTsAddr);
#endif
	BRDC_FreeScratchReg(hDisplay->hVdc->hRdc, hDisplay->ulRdcVarAddr);
#if (BVDC_P_STG_RUL_DELAY_WORKAROUND)
	BRDC_FreeScratchReg(hDisplay->hVdc->hRdc, hDisplay->ulScratchDummyAddr);
#endif

#if DCS_SUPPORT
#if 0
	BRDC_FreeScratchReg(hDisplay->hVdc->hRdc, hDisplay->ulDcsScratch[0]);
	BRDC_FreeScratchReg(hDisplay->hVdc->hRdc, hDisplay->ulDcsScratch[1]);
	BRDC_FreeScratchReg(hDisplay->hVdc->hRdc, hDisplay->ulDcsScratch[2]);
#endif
#endif

	BDBG_OBJECT_DESTROY(hDisplay, BVDC_DSP);
	/* [0] Release context in system memory */
	BKNI_Free((void*)hDisplay);

	BDBG_LEAVE(BVDC_P_Display_Destroy);
	return;
}


/*************************************************************************
 *
 */
void BVDC_P_ResetVec
	( BVDC_P_Context                  *pVdc )
{
#if 0
	uint32_t ulVbiPrimReg;
#if BVDC_P_SUPPORT_SEC_VEC
	uint32_t ulVbiSecReg;
#endif
#if BVDC_P_SUPPORT_TER_VEC
	uint32_t ulVbiTerReg;
#endif
#if (BVDC_P_SUPPORT_VBI_ENC_656)
	uint32_t ulVbiAncilReg;
#endif
#endif

#ifdef BCHP_VCXO_0_RM_REG_START
	uint32_t i;
	uint32_t ulVcxoRm0[BVDC_P_VCXO_RM_REG_COUNT];
#endif
#ifdef BCHP_VCXO_1_RM_REG_START
	uint32_t ulVcxoRm1[BVDC_P_VCXO_RM_REG_COUNT];
#endif
#ifdef BCHP_VCXO_2_RM_REG_START
	uint32_t ulVcxoRm2[BVDC_P_VCXO_RM_REG_COUNT];
#endif

	BDBG_ENTER(BVDC_P_ResetVec);

	/* prepare for software reset */
	BKNI_EnterCriticalSection();


#if 0 /* ToDo: Add 7420 VBI reset handling */
	/* before reset, get regsiters partially owned by VBI module */
	ulVbiPrimReg  = BREG_Read32(pVdc->hRegister, BCHP_VBI_ENC_PRIM_Control);
#if (BVDC_P_SUPPORT_VBI_ENC_656)
	ulVbiAncilReg = BREG_Read32(pVdc->hRegister, BCHP_VBI_ENC_656_Ancil_Control);
#endif

#if BVDC_P_SUPPORT_SEC_VEC
	ulVbiSecReg   = BREG_Read32(pVdc->hRegister, BCHP_VBI_ENC_SEC_Control);
#endif

#if BVDC_P_SUPPORT_TER_VEC
	ulVbiTerReg   = BREG_Read32(pVdc->hRegister, BCHP_VBI_ENC_TERT_Control);
#endif
#endif

	/* Save VCXO_RM settings before reset VEC core */
#ifdef BCHP_VCXO_0_RM_REG_START
	for(i = 0; i < BVDC_P_VCXO_RM_REG_COUNT; i++)
	{
		ulVcxoRm0[i] = BREG_Read32(pVdc->hRegister, BCHP_VCXO_0_RM_REG_START +
			i * sizeof(uint32_t));
	}
#endif

#ifdef BCHP_VCXO_1_RM_REG_START
	for(i = 0; i < BVDC_P_VCXO_RM_REG_COUNT; i++)
	{
		ulVcxoRm1[i] = BREG_Read32(pVdc->hRegister, BCHP_VCXO_1_RM_REG_START +
			i * sizeof(uint32_t));
	}
#endif

#ifdef BCHP_VCXO_2_RM_REG_START
	for(i = 0; i < BVDC_P_VCXO_RM_REG_COUNT; i++)
	{
		ulVcxoRm2[i] = BREG_Read32(pVdc->hRegister, BCHP_VCXO_2_RM_REG_START +
			i * sizeof(uint32_t));
	}
#endif

#if BVDC_P_SUPPORT_NEW_SW_INIT
	BREG_Write32(pVdc->hRegister, BCHP_SUN_TOP_CTRL_SW_INIT_0_SET,
	      BCHP_FIELD_DATA( SUN_TOP_CTRL_SW_INIT_0_SET, vec_sw_init, 1 ));
	BREG_Write32(pVdc->hRegister, BCHP_SUN_TOP_CTRL_SW_INIT_0_CLEAR,
	      BCHP_FIELD_DATA( SUN_TOP_CTRL_SW_INIT_0_CLEAR, vec_sw_init, 1 ));
#else
	/* Software Reset entire VEC block!  This will reset RM  */
	BREG_AtomicUpdate32_isr(pVdc->hRegister, BCHP_SUN_TOP_CTRL_SW_RESET,
		BCHP_MASK( SUN_TOP_CTRL_SW_RESET, vec_sw_reset),
		BCHP_FIELD_DATA( SUN_TOP_CTRL_SW_RESET, vec_sw_reset, 1 ));

	BREG_AtomicUpdate32_isr(pVdc->hRegister, BCHP_SUN_TOP_CTRL_SW_RESET,
		BCHP_MASK( SUN_TOP_CTRL_SW_RESET, vec_sw_reset),
		BCHP_FIELD_DATA( SUN_TOP_CTRL_SW_RESET, vec_sw_reset, 0 ));
#endif

#if BVDC_P_SUPPORT_VIP && BCHP_SUN_TOP_CTRL_SW_INIT_1_SET_vip_sw_init_MASK
	BREG_Write32(pVdc->hRegister, BCHP_SUN_TOP_CTRL_SW_INIT_1_SET,
	      BCHP_FIELD_DATA( SUN_TOP_CTRL_SW_INIT_1_SET, vip_sw_init, 1 ));
	BREG_Write32(pVdc->hRegister, BCHP_SUN_TOP_CTRL_SW_INIT_1_CLEAR,
	      BCHP_FIELD_DATA( SUN_TOP_CTRL_SW_INIT_1_CLEAR, vip_sw_init, 1 ));
#endif

#if 0 /* ToDo: Add 7420 VBI reset handling */

	/* PR 9338:
	   The VBI module owns most of the fields from these registers.
		All fields owned by VBI should be restored and the pass_through field
		of PRIM/SEC vbi encoders are set, while 656 vbi encoder's pass_through
		count is cleared. */
	ulVbiPrimReg  |= BCHP_VBI_ENC_PRIM_Control_ENABLE_PASS_THROUGH_MASK;
	BREG_Write32(pVdc->hRegister, BCHP_VBI_ENC_PRIM_Control, ulVbiPrimReg);
	BREG_Write32(pVdc->hRegister, BAVC_VBI_ENC_0_CTRL_SCRATCH, ulVbiPrimReg);
#if (BVDC_P_SUPPORT_VBI_ENC_656)
	ulVbiAncilReg &= ~BCHP_VBI_ENC_656_Ancil_Control_PASS_THROUGH_COUNT_MASK;
	BREG_Write32(pVdc->hRegister, BCHP_VBI_ENC_656_Ancil_Control, ulVbiAncilReg);
	BREG_Write32(pVdc->hRegister, BAVC_VBI_ENC_BP_CTRL_SCRATCH, ulVbiAncilReg);
#endif

#if (BVDC_P_SUPPORT_TER_VEC)
	ulVbiTerReg |= BCHP_VBI_ENC_PRIM_Control_ENABLE_PASS_THROUGH_MASK;
	BREG_Write32(pVdc->hRegister, BCHP_VBI_ENC_TERT_Control, ulVbiTerReg);
	BREG_Write32(pVdc->hRegister, BAVC_VBI_ENC_2_CTRL_SCRATCH, ulVbiTerReg);
#endif

#if (BVDC_P_SUPPORT_SEC_VEC)
	ulVbiSecReg   |= BCHP_VBI_ENC_PRIM_Control_ENABLE_PASS_THROUGH_MASK;
	BREG_Write32(pVdc->hRegister, BCHP_VBI_ENC_SEC_Control, ulVbiSecReg);
	BREG_Write32(pVdc->hRegister, BAVC_VBI_ENC_1_CTRL_SCRATCH, ulVbiSecReg);
#endif
#endif

	/* Restore VCXO_RM settings */
#ifdef BCHP_VCXO_0_RM_REG_START
	for(i = 0; i < BVDC_P_VCXO_RM_REG_COUNT; i++)
	{
		BREG_Write32(pVdc->hRegister, BCHP_VCXO_0_RM_REG_START +
			i * sizeof(uint32_t), ulVcxoRm0[i]);
	}
#endif

#ifdef BCHP_VCXO_1_RM_REG_START
	for(i = 0; i < BVDC_P_VCXO_RM_REG_COUNT; i++)
	{
		BREG_Write32(pVdc->hRegister, BCHP_VCXO_1_RM_REG_START +
			i * sizeof(uint32_t), ulVcxoRm1[i]);
	}
#endif

#ifdef BCHP_VCXO_2_RM_REG_START
	for(i = 0; i < BVDC_P_VCXO_RM_REG_COUNT; i++)
	{
		BREG_Write32(pVdc->hRegister, BCHP_VCXO_2_RM_REG_START +
			i * sizeof(uint32_t), ulVcxoRm2[i]);
	}
#endif

	/* init VEC MISC block registers */
	BVDC_P_Vec_Init_Misc_isr(pVdc);

	BKNI_LeaveCriticalSection();

	BDBG_LEAVE(BVDC_P_ResetVec);
	return ;
}


/*************************************************************************
 *
 */
void BVDC_P_Vec_Init_Misc_isr
	( BVDC_P_Context           *pVdc )
{
	uint32_t ulReg;
	uint32_t ulOffset;
	int i;
#if (BVDC_P_SUPPORT_TDAC_VER >= BVDC_P_SUPPORT_TDAC_VER_9)
	uint32_t target_val, plugout_thrsh;
#endif

	BDBG_ENTER(BVDC_P_Vec_Init_Misc_isr);

#if BVDC_P_SUPPORT_NEW_SW_INIT
	ulReg = BCHP_FIELD_DATA(VEC_CFG_SW_INIT_VEC_MISC, INIT, 1);
	BREG_Write32(pVdc->hRegister, BCHP_VEC_CFG_SW_INIT_VEC_MISC, ulReg);

	ulReg = BCHP_FIELD_DATA(VEC_CFG_SW_INIT_VEC_MISC, INIT, 0);
	BREG_Write32(pVdc->hRegister, BCHP_VEC_CFG_SW_INIT_VEC_MISC, ulReg);
#if (BVDC_P_SUPPORT_TDAC_VER >= BVDC_P_SUPPORT_TDAC_VER_11)
	ulReg = BCHP_FIELD_DATA(VEC_CFG_SW_INIT_CABLE_DETECT_0, INIT, 1);
	BREG_Write32(pVdc->hRegister, BCHP_VEC_CFG_SW_INIT_CABLE_DETECT_0, ulReg);

	ulReg = BCHP_FIELD_DATA(VEC_CFG_SW_INIT_CABLE_DETECT_0, INIT, 0);
	BREG_Write32(pVdc->hRegister, BCHP_VEC_CFG_SW_INIT_CABLE_DETECT_0, ulReg);
#endif
#else
	ulReg = BCHP_FIELD_DATA(VEC_CFG_SW_RESET_VEC_MISC, RESET, 1);
	BREG_Write32(pVdc->hRegister, BCHP_VEC_CFG_SW_RESET_VEC_MISC, ulReg);

	ulReg = BCHP_FIELD_DATA(VEC_CFG_SW_RESET_VEC_MISC, RESET, 0);
	BREG_Write32(pVdc->hRegister, BCHP_VEC_CFG_SW_RESET_VEC_MISC, ulReg);
#endif

#ifdef BCHP_MISC_DAC_BG_CTRL_0
	/* power off band gap*/
	ulReg =
		BCHP_FIELD_ENUM(MISC_DAC_BG_CTRL_0, PWRDN,        PWRDN     ) |
		BCHP_FIELD_ENUM(MISC_DAC_BG_CTRL_0, CORE_ADJ,     FOUR      ) |
		BCHP_FIELD_ENUM(MISC_DAC_BG_CTRL_0, BANDGAP_BYP,  BANDGAP   ) |
		BCHP_FIELD_ENUM(MISC_DAC_BG_CTRL_0, IREF_ADJ,     TWENTY_SIX) |
		BCHP_FIELD_ENUM(MISC_DAC_BG_CTRL_0, PWRDN_REFAMP, POWER_DOWN  );
	BREG_Write32(pVdc->hRegister, BCHP_MISC_DAC_BG_CTRL_0, ulReg);
#endif

#ifdef BCHP_MISC_DAC_BG_CTRL_1
	ulReg =
		BCHP_FIELD_ENUM(MISC_DAC_BG_CTRL_1, PWRDN,        PWRDN     ) |
		BCHP_FIELD_ENUM(MISC_DAC_BG_CTRL_1, CORE_ADJ,     FOUR      ) |
		BCHP_FIELD_ENUM(MISC_DAC_BG_CTRL_1, BANDGAP_BYP,  BANDGAP   ) |
		BCHP_FIELD_ENUM(MISC_DAC_BG_CTRL_1, IREF_ADJ,     TWENTY_SIX) |
		BCHP_FIELD_ENUM(MISC_DAC_BG_CTRL_1, PWRDN_REFAMP, POWER_DOWN  );
	BREG_Write32(pVdc->hRegister, BCHP_MISC_DAC_BG_CTRL_1, ulReg);
#endif

	/* power down each dac */
	for(i = 0; i < BVDC_P_MAX_DACS; i++)
	{
#ifdef BCHP_MISC_DAC_1_CFG
		ulOffset = (BCHP_MISC_DAC_1_CFG - BCHP_MISC_DAC_0_CFG) * i;
#else
		ulOffset= 0;
#endif
		ulReg =
			BCHP_FIELD_DATA(MISC_DAC_0_CFG, CONST,        0) |
			BCHP_FIELD_ENUM(MISC_DAC_0_CFG, SINC,       OFF) |
			BCHP_FIELD_DATA(MISC_DAC_0_CFG, DELAY,        0) |
			BCHP_FIELD_ENUM(MISC_DAC_0_CFG, SEL,      CONST);
		BREG_Write32(pVdc->hRegister, BCHP_MISC_DAC_0_CFG + ulOffset, ulReg);

#if (BVDC_P_SUPPORT_TDAC_VER >= BVDC_P_SUPPORT_TDAC_VER_11)
#ifdef BCHP_MISC_DAC_1_CTRL
		ulOffset = (BCHP_MISC_DAC_1_CTRL - BCHP_MISC_DAC_0_CTRL) * i;
		ulReg =
			BCHP_FIELD_DATA(MISC_DAC_0_CTRL, PWRDN, 1);

		BREG_Write32(pVdc->hRegister, BCHP_MISC_DAC_0_CTRL + ulOffset, ulReg);
#endif
#else
#ifdef BCHP_MISC_DAC_1_CTRL
		ulOffset = (BCHP_MISC_DAC_1_CTRL - BCHP_MISC_DAC_0_CTRL) * i;
		ulReg =
			BCHP_FIELD_ENUM(MISC_DAC_0_CTRL, PWRUP_BAIS, PWRDN) |
			BCHP_FIELD_ENUM(MISC_DAC_0_CTRL, PWRDN,      PWRDN);

		BREG_Write32(pVdc->hRegister, BCHP_MISC_DAC_0_CTRL + ulOffset, ulReg);
#endif
#endif
	}

#if (BVDC_P_SUPPORT_TDAC_VER >= BVDC_P_SUPPORT_TDAC_VER_9)
#if (BVDC_P_SUPPORT_TDAC_VER >= BVDC_P_SUPPORT_TDAC_VER_13)
	target_val = 0x300;
	plugout_thrsh = 0x190;
#else
	target_val = 0x2D8;
	plugout_thrsh = 0x21C;
#endif
	ulReg =
		BCHP_FIELD_DATA(MISC_DAC_CAL_CTRL_0, MAX_TARGET_DELTA,  0x2  ) |
		BCHP_FIELD_DATA(MISC_DAC_CAL_CTRL_0, ADC_MAX_VAL,       0x3FF) |
		BCHP_FIELD_DATA(MISC_DAC_CAL_CTRL_0, COUNT,             0x1  ) |
		BCHP_FIELD_DATA(MISC_DAC_CAL_CTRL_0, STEP_DLY,          0x0  ) |
		BCHP_FIELD_DATA(MISC_DAC_CAL_CTRL_0, TARGET_VAL, target_val  );
	BREG_Write32(pVdc->hRegister, BCHP_MISC_DAC_CAL_CTRL_0, ulReg);

	ulReg =
		BCHP_FIELD_DATA(MISC_DAC_DETECT_CTRL_0, PLUGIN_CNT,        0x2) |
		BCHP_FIELD_DATA(MISC_DAC_DETECT_CTRL_0, PLUGOUT_CNT,       0x2) |
		BCHP_FIELD_DATA(MISC_DAC_DETECT_CTRL_0, PLUGOUT_THRESHOLD, plugout_thrsh) |
		BCHP_FIELD_DATA(MISC_DAC_DETECT_CTRL_0, STEP_DLY,          0x2) |
		BCHP_FIELD_DATA(MISC_DAC_DETECT_CTRL_0, PLUGIN_THRESHOLD,  0xB3);
	BREG_Write32(pVdc->hRegister, BCHP_MISC_DAC_DETECT_CTRL_0, ulReg);

#if BVDC_P_VEC_CABLE_DETECT_SW_WORKAROUND
	ulReg =
		BCHP_FIELD_DATA(MISC_DAC_SQWAVE_LEVEL_0, HIGH,       0x1FF) |
		BCHP_FIELD_DATA(MISC_DAC_SQWAVE_LEVEL_0, LOW,        0x1FF);
	BREG_Write32(pVdc->hRegister, BCHP_MISC_DAC_SQWAVE_LEVEL_0, ulReg);

	ulReg =
		BCHP_FIELD_DATA(MISC_DAC_DETECT_TIMING_0, ADC_VALID_DLY,  0x1) |
		BCHP_FIELD_DATA(MISC_DAC_DETECT_TIMING_0, ADC_RST_DLY,   0xFF) |
		BCHP_FIELD_DATA(MISC_DAC_DETECT_TIMING_0, STRB_WIDTH,    0x40) |
		BCHP_FIELD_DATA(MISC_DAC_DETECT_TIMING_0, STRB_DLY,      0x1F);
	BREG_Write32(pVdc->hRegister, BCHP_MISC_DAC_DETECT_TIMING_0, ulReg);
#endif
#endif

	/* power down BG */
#if (BVDC_P_SUPPORT_TDAC_VER >= BVDC_P_SUPPORT_TDAC_VER_11)
	ulReg =
		BCHP_FIELD_DATA(MISC_DAC_INST_BIAS_CTRL_0, PWRDN, 1);
	BREG_Write32(pVdc->hRegister, BCHP_MISC_DAC_INST_BIAS_CTRL_0, ulReg);
#endif

	BDBG_LEAVE(BVDC_P_Vec_Init_Misc_isr);
	return;
}

/*************************************************************************
 *
 */
void BVDC_P_Vec_Update_OutMuxes_isr
	( BVDC_P_Context           *pVdc )
{
	BSTD_UNUSED(pVdc);
	return ;
}


/*************************************************************************
 *  {secret}
 * BVDC_P_Display_EnableTriggers_isr
 *  Re-enable trigger after vec reset.
 **************************************************************************/
void BVDC_P_Display_EnableTriggers_isr
	( BVDC_Display_Handle              hDisplay,
	  bool                             bEnable )
{
	uint32_t ulTrigger0;
	uint32_t ulTrigger1;

	BDBG_ENTER(BVDC_P_Display_EnableTriggers_isr);
	BDBG_OBJECT_ASSERT(hDisplay, BVDC_DSP);

	if(hDisplay->stDviChan.bEnable || hDisplay->stCurInfo.bHdmiRmd)
	{
		BDBG_ASSERT(hDisplay->stDviChan.ulDvi != BVDC_P_HW_ID_INVALID);

		/* Re-enable triggers. */
		ulTrigger0 = BREG_Read32_isr(hDisplay->hVdc->hRegister,
			BCHP_DVI_DTG_0_DTG_TRIGGER_0 + hDisplay->stDviChan.ulDviRegOffset);
		ulTrigger0 &= ~BCHP_DVI_DTG_0_DTG_TRIGGER_0_ENABLE_MASK;
		if(bEnable)
		{
			ulTrigger0 |= BCHP_DVI_DTG_0_DTG_TRIGGER_0_ENABLE_MASK;
		}
		BREG_Write32(hDisplay->hVdc->hRegister,
			BCHP_DVI_DTG_0_DTG_TRIGGER_0 + hDisplay->stDviChan.ulDviRegOffset, ulTrigger0);

		ulTrigger1 = BREG_Read32_isr(hDisplay->hVdc->hRegister,
			BCHP_DVI_DTG_0_DTG_TRIGGER_1 + hDisplay->stDviChan.ulDviRegOffset);
		ulTrigger1 &= ~BCHP_DVI_DTG_0_DTG_TRIGGER_1_ENABLE_MASK;
		if(bEnable)
		{
#if (BVDC_P_SUPPORT_IT_VER >= 2)
			ulTrigger1 |= (hDisplay->stCurInfo.pFmtInfo->bInterlaced || (1 != hDisplay->stCurInfo.ulTriggerModuloCnt))
				? BCHP_DVI_DTG_0_DTG_TRIGGER_1_ENABLE_MASK : 0;
#else
			ulTrigger1 |= (hDisplay->stCurInfo.pFmtInfo->bInterlaced)
				? BCHP_DVI_DTG_0_DTG_TRIGGER_1_ENABLE_MASK : 0;
#endif
		}
		BREG_Write32(hDisplay->hVdc->hRegister,
			BCHP_DVI_DTG_0_DTG_TRIGGER_1 + hDisplay->stDviChan.ulDviRegOffset, ulTrigger1);
	}
	else if(hDisplay->bAnlgEnable)
	{
		BDBG_ASSERT(hDisplay->stAnlgChan_0.ulIt != BVDC_P_HW_ID_INVALID);

		/* Re-enable triggers. */
		ulTrigger0 = BREG_Read32_isr(hDisplay->hVdc->hRegister,
			BCHP_IT_0_VEC_TRIGGER_0 + hDisplay->stAnlgChan_0.ulItRegOffset);
		ulTrigger0 &= ~BCHP_IT_0_VEC_TRIGGER_0_ENABLE_MASK;
		if(bEnable)
		{
			ulTrigger0 |= BCHP_IT_0_VEC_TRIGGER_0_ENABLE_MASK;
		}
		BREG_Write32_isr(hDisplay->hVdc->hRegister,
			BCHP_IT_0_VEC_TRIGGER_0 + hDisplay->stAnlgChan_0.ulItRegOffset, ulTrigger0);

		ulTrigger1 = BREG_Read32_isr(hDisplay->hVdc->hRegister,
			BCHP_IT_0_VEC_TRIGGER_1 + hDisplay->stAnlgChan_0.ulItRegOffset);
		ulTrigger1 &= ~BCHP_IT_0_VEC_TRIGGER_1_ENABLE_MASK;
		if(bEnable)
		{
#if	(BVDC_P_SUPPORT_IT_VER >= 2)
			ulTrigger1 |= (hDisplay->stCurInfo.pFmtInfo->bInterlaced || (1 != hDisplay->stCurInfo.ulTriggerModuloCnt))
				? BCHP_IT_0_VEC_TRIGGER_1_ENABLE_MASK : 0;
#else
			ulTrigger1 |= (hDisplay->stCurInfo.pFmtInfo->bInterlaced)
				? BCHP_IT_0_VEC_TRIGGER_1_ENABLE_MASK : 0;
#endif
		}

		BREG_Write32_isr(hDisplay->hVdc->hRegister,
			BCHP_IT_0_VEC_TRIGGER_1 + hDisplay->stAnlgChan_0.ulItRegOffset, ulTrigger1);

#if (BVDC_P_ORTHOGONAL_VEC_VER >=1)
		{
			uint32_t ulRegOffset, ulSrc;
			ulRegOffset = (hDisplay->hCompositor->eId - BVDC_CompositorId_eCompositor0) * sizeof(uint32_t);
			ulSrc       = BCHP_VEC_CFG_TRIGGER_SEL_0_SRC_IT_0 + hDisplay->stAnlgChan_0.ulId;

			BREG_Write32_isr(hDisplay->hVdc->hRegister, BCHP_VEC_CFG_TRIGGER_SEL_0 + ulRegOffset, ulSrc);
		}
#endif
	}
	else if(hDisplay->stCurInfo.bEnableStg)
	{
#if (BVDC_P_SUPPORT_STG)
		BVDC_P_Display_EnableSTGTriggers_isr(hDisplay, bEnable);
#endif
	}
	else if(hDisplay->st656Chan.bEnable)
	{
#if (BVDC_P_SUPPORT_ITU656_OUT)
		/* Re-enable triggers. */
		ulTrigger0 = BREG_Read32_isr(hDisplay->hVdc->hRegister,
			BCHP_ITU656_DTG_0_DTG_TRIGGER_0);
		ulTrigger0 &= ~BCHP_ITU656_DTG_0_DTG_TRIGGER_0_ENABLE_MASK;
		if(bEnable)
		{
			ulTrigger0 |= BCHP_ITU656_DTG_0_DTG_TRIGGER_0_ENABLE_MASK;
		}
		BREG_Write32(hDisplay->hVdc->hRegister,
			BCHP_ITU656_DTG_0_DTG_TRIGGER_0, ulTrigger0);

		ulTrigger1 = BREG_Read32_isr(hDisplay->hVdc->hRegister,
			BCHP_ITU656_DTG_0_DTG_TRIGGER_1);
		ulTrigger1 &= ~BCHP_ITU656_DTG_0_DTG_TRIGGER_1_ENABLE_MASK;
		if(bEnable)
		{
			ulTrigger1 |= (hDisplay->stCurInfo.pFmtInfo->bInterlaced)
				? BCHP_ITU656_DTG_0_DTG_TRIGGER_1_ENABLE_MASK : 0;
		}
		BREG_Write32(hDisplay->hVdc->hRegister,
			BCHP_ITU656_DTG_0_DTG_TRIGGER_1, ulTrigger1);
#endif
	}
	else
	{
			BDBG_ERR((" Invalid timing generator master %d, display id %d",
				hDisplay->eMasterTg, hDisplay->eId));
			BDBG_ASSERT(0);
	}

	BDBG_LEAVE(BVDC_P_Display_EnableTriggers_isr);
	return;
}


void BVDC_P_Display_GetAnlgChanByOutput_isr
	( BVDC_Display_Handle             hDisplay,
	  BVDC_P_DisplayInfo             *pDispInfo,
	  BVDC_DisplayOutput              eDisplayOutput,
	  BVDC_P_DisplayAnlgChan        **pstChan
	)
{
	*pstChan = NULL;

	if ((BVDC_P_DISP_IS_ANLG_CHAN_CO(&hDisplay->stAnlgChan_0, pDispInfo) && (eDisplayOutput == BVDC_DisplayOutput_eComponent)) ||
		(BVDC_P_DISP_IS_ANLG_CHAN_CVBS(&hDisplay->stAnlgChan_0, pDispInfo) && (eDisplayOutput == BVDC_DisplayOutput_eComposite)) ||
		(BVDC_P_DISP_IS_ANLG_CHAN_SVIDEO(&hDisplay->stAnlgChan_0, pDispInfo) && (eDisplayOutput == BVDC_DisplayOutput_eSVideo)))
	{
		*pstChan = &hDisplay->stAnlgChan_0;
	}
	else if ((BVDC_P_DISP_IS_ANLG_CHAN_CO(&hDisplay->stAnlgChan_1, pDispInfo) && (eDisplayOutput == BVDC_DisplayOutput_eComponent)) ||
		     (BVDC_P_DISP_IS_ANLG_CHAN_CVBS(&hDisplay->stAnlgChan_1, pDispInfo) && (eDisplayOutput == BVDC_DisplayOutput_eComposite)) ||
		     (BVDC_P_DISP_IS_ANLG_CHAN_SVIDEO(&hDisplay->stAnlgChan_1, pDispInfo) && (eDisplayOutput == BVDC_DisplayOutput_eSVideo)))
	{
		*pstChan = &hDisplay->stAnlgChan_1;
	}

	return;
}


static void BVDC_P_Display_AssignCSOutput
	( BVDC_P_DisplayInfo              *pNewInfo,
	  uint32_t                         ulChanMask,
	  BVDC_P_Output                   *peOutputCS )
{
	if((ulChanMask & BVDC_P_Dac_Mask_Cvbs) || (ulChanMask & BVDC_P_Dac_Mask_Svideo))
	{
		if(VIDEO_FORMAT_IS_NTSC_M(pNewInfo->pFmtInfo->eVideoFmt))
		{
			*peOutputCS = BVDC_P_Output_eYQI;
		}
		else if(VIDEO_FORMAT_IS_NTSC_J(pNewInfo->pFmtInfo->eVideoFmt))
		{
			*peOutputCS = BVDC_P_Output_eYQI_M;
		}
#if BVDC_P_SUPPORT_VEC_SECAM
		else if(VIDEO_FORMAT_IS_SECAM(pNewInfo->pFmtInfo->eVideoFmt))
		{
			if ((pNewInfo->pFmtInfo->eVideoFmt == BFMT_VideoFmt_eSECAM_L) ||
				(pNewInfo->pFmtInfo->eVideoFmt == BFMT_VideoFmt_eSECAM_D) ||
				(pNewInfo->pFmtInfo->eVideoFmt == BFMT_VideoFmt_eSECAM_K))
			{
				*peOutputCS = BVDC_P_Output_eYDbDr_LDK;
			}
			else if((pNewInfo->pFmtInfo->eVideoFmt == BFMT_VideoFmt_eSECAM_B) ||
					(pNewInfo->pFmtInfo->eVideoFmt == BFMT_VideoFmt_eSECAM_G))
			{
				*peOutputCS = BVDC_P_Output_eYDbDr_BG;
			}
			else /* BFMT_VideoFmt_eSECAM_H */
			{
				*peOutputCS = BVDC_P_Output_eYDbDr_H;
			}
		}
#endif
		else if(pNewInfo->pFmtInfo->eVideoFmt == BFMT_VideoFmt_ePAL_NC)
		{
			*peOutputCS = BVDC_P_Output_eYUV_NC;
		}
		else if(pNewInfo->pFmtInfo->eVideoFmt == BFMT_VideoFmt_ePAL_N)
		{
			*peOutputCS = BVDC_P_Output_eYUV_N;
		}
		else if(pNewInfo->pFmtInfo->eVideoFmt == BFMT_VideoFmt_ePAL_M)
		{
			*peOutputCS = BVDC_P_Output_eYUV_M;
		}
		else /* PAL */
		{
			*peOutputCS = BVDC_P_Output_eYUV;
		}
	}

	if(pNewInfo->bHsync)
	{
		*peOutputCS = BVDC_P_Output_eHsync;
	}

	if(ulChanMask & BVDC_P_Dac_Mask_RGB)
	{
		if (VIDEO_FORMAT_27Mhz(pNewInfo->pFmtInfo->ulPxlFreqMask))
		{
			*peOutputCS = BVDC_P_Output_eSDRGB;
		}
		else
		{
			*peOutputCS = BVDC_P_Output_eHDRGB;
		}
	}

	if(ulChanMask & BVDC_P_Dac_Mask_YPrPb)
	{
		if (VIDEO_FORMAT_27Mhz(pNewInfo->pFmtInfo->ulPxlFreqMask))
		{
			*peOutputCS = BVDC_P_Output_eSDYPrPb;
		}
		else
		{
			*peOutputCS = BVDC_P_Output_eHDYPrPb;
		}
	}
}

static BERR_Code BVDC_P_Display_ValidateDacSettings
	( BVDC_Display_Handle              ahDisplay[] )
{
	BERR_Code                 err = BERR_SUCCESS;
	int i, j;
	BVDC_Handle               hVdc=NULL;
	BVDC_Display_Handle       hDisplay = NULL;
	BVDC_P_DisplayInfo       *pNewInfo=NULL;
	BVDC_P_DisplayInfo       *pCurInfo=NULL;
	BVDC_DacOutput            aNewUsedDac[BVDC_P_MAX_DACS];
	uint32_t                  ulDacMask;
	uint32_t                  ulHdDacCnt = 0;
	uint32_t                  aulCurAnalogChan[BVDC_P_MAX_DISPLAY_COUNT * 2];
	uint32_t                  aulNewAnalogChan[BVDC_P_MAX_DISPLAY_COUNT * 2];

	BDBG_ENTER(BVDC_P_Display_ValidateDacSettings);

	/* Initialized */
	for(i = 0; i < BVDC_P_MAX_DACS; i++)
	{
		aNewUsedDac[i] = BVDC_DacOutput_eUnused;
	}
	for(i = 0; i < BVDC_P_MAX_DISPLAY_COUNT * 2; i++)
	{
		aulCurAnalogChan[i] = aulNewAnalogChan[i] = 0;
	}

	for(i = 0; i < BVDC_P_MAX_DISPLAY_COUNT; i++)
	{
		/* Only validate the create or active onces. */
		if(BVDC_P_STATE_IS_ACTIVE(ahDisplay[i]) ||
		   BVDC_P_STATE_IS_CREATE(ahDisplay[i]))
		{
			hDisplay = ahDisplay[i];
			BDBG_OBJECT_ASSERT(hDisplay, BVDC_DSP);
			hVdc = hDisplay->hVdc;
			BDBG_OBJECT_ASSERT(hVdc, BVDC_VDC);
			pNewInfo = &hDisplay->stNewInfo;
			pCurInfo = &hDisplay->stCurInfo;

			ulDacMask = 0;
			pNewInfo->bCvbs   = false;
			pNewInfo->bSvideo = false;
			pNewInfo->bHsync  = false;
			pNewInfo->bRgb    = false;
			pNewInfo->bYPrPb  = false;
			pNewInfo->bMultiRateAllow = true;

			/* if RFM is enable, treat it as CVBS */
			if(pNewInfo->eRfmOutput != BVDC_RfmOutput_eUnused)
			{
				pNewInfo->bCvbs = true;
			}

			for(j = 0; j < BVDC_P_MAX_DACS; j++)
			{
				/* Checking for duplicated use of DACs accross all displays */
				if(pNewInfo->aDacOutput[j] != BVDC_DacOutput_eUnused)
				{
					if(aNewUsedDac[j] != BVDC_DacOutput_eUnused)
					{
						BDBG_ERR(("Dac[%d] already used by Display[%d].",
							j, hDisplay->eId));
						return BERR_TRACE(BVDC_ERR_INVALID_DAC_SETTINGS);
					}
					else
					{
						aNewUsedDac[j] = pNewInfo->aDacOutput[j];
					}

					switch(pNewInfo->aDacOutput[j])
					{
						case BVDC_DacOutput_eFilteredCvbs:
						case BVDC_DacOutput_eComposite:
							ulDacMask |= BVDC_P_Dac_Mask_Cvbs;
							pNewInfo->bCvbs = true;
							break;
						case BVDC_DacOutput_eSVideo_Luma:
							ulDacMask |= BVDC_P_Dac_Mask_Luma;
							pNewInfo->bSvideo = true;
							break;
						case BVDC_DacOutput_eSVideo_Chroma:
							ulDacMask |= BVDC_P_Dac_Mask_Chroma;
							pNewInfo->bSvideo = true;
							break;
						case BVDC_DacOutput_eRed:
							ulDacMask |= BVDC_P_Dac_Mask_R;
							pNewInfo->bRgb = true;
							break;
						case BVDC_DacOutput_eGreen:
						case BVDC_DacOutput_eGreen_NoSync:
							ulDacMask |= BVDC_P_Dac_Mask_G;
							pNewInfo->bRgb = true;
							break;
						case BVDC_DacOutput_eBlue:
							ulDacMask |= BVDC_P_Dac_Mask_B;
							pNewInfo->bRgb = true;
							break;
						case BVDC_DacOutput_eY:
							ulDacMask |= BVDC_P_Dac_Mask_Y;
							pNewInfo->bYPrPb = true;
							break;
						case BVDC_DacOutput_ePr:
							ulDacMask |= BVDC_P_Dac_Mask_Pr;
							pNewInfo->bYPrPb = true;
							break;
						case BVDC_DacOutput_ePb:
							ulDacMask |= BVDC_P_Dac_Mask_Pb;
							pNewInfo->bYPrPb = true;
							break;
						case BVDC_DacOutput_eHsync:
							pNewInfo->bHsync = true;
							break;
						default:
							break;
							return BERR_TRACE(BVDC_ERR_INVALID_DAC_SETTINGS);
					} /* end of switch */
				}
			} /* end of MAX_DACS looping */

			/* Checking for valid DAC grouping */
			if(pNewInfo->bYPrPb && (ulDacMask & BVDC_P_Dac_Mask_YPrPb) != BVDC_P_Dac_Mask_YPrPb)
			{
				BDBG_ERR(("ulDacMask = 0x%x, BVDC_P_Dac_Mask_YPrPb = 0x%x", ulDacMask, BVDC_P_Dac_Mask_YPrPb));
				return BERR_TRACE(BVDC_ERR_INVALID_DAC_SETTINGS);
			}
			if(pNewInfo->bRgb && (ulDacMask & BVDC_P_Dac_Mask_RGB) != BVDC_P_Dac_Mask_RGB)
			{
				BDBG_ERR(("ulDacMask = 0x%x, BVDC_P_Dac_Mask_RGB = 0x%x", ulDacMask, BVDC_P_Dac_Mask_RGB));
				return BERR_TRACE(BVDC_ERR_INVALID_DAC_SETTINGS);
			}
			if(pNewInfo->bSvideo && (ulDacMask & BVDC_P_Dac_Mask_Svideo) != BVDC_P_Dac_Mask_Svideo)
			{
				BDBG_ERR(("ulDacMask = 0x%x, BVDC_P_Dac_Mask_Svideo = 0x%x", ulDacMask, BVDC_P_Dac_Mask_Svideo));
				return BERR_TRACE(BVDC_ERR_INVALID_DAC_SETTINGS);
			}

			/* Checking for valid display fmt with DAC setting */
			if((pNewInfo->bCvbs || pNewInfo->bSvideo) &&
			   (VIDEO_FORMAT_IS_HD(pNewInfo->pFmtInfo->eVideoFmt)))
			{
				return BERR_TRACE(BVDC_ERR_VIDEOFMT_OUTPUT_MISMATCH);
			}

			/* Checking for HDMI running with RMD with DAC */
#if BVDC_P_SUPPORT_DTG_RMD
			pNewInfo->bHdmiFmt =
				((pNewInfo->stHdmiSettings.eHDMIFormat != BFMT_VideoFmt_eMaxCount &&
				  pNewInfo->stHdmiSettings.eMatchingFormat == pNewInfo->pFmtInfo->eVideoFmt) &&
				 pNewInfo->bEnableHdmi);

			pNewInfo->bHdmiRmd =
				(pNewInfo->bHdmiFmt ||
				 (VIDEO_FORMAT_IS_4kx2k(pNewInfo->pFmtInfo->eVideoFmt) &&
				  pNewInfo->bEnableHdmi));

			if(pNewInfo->bHdmiRmd && ulDacMask != 0)
			{
				return BERR_TRACE(BVDC_ERR_VIDEOFMT_OUTPUT_MISMATCH);
			}

			if(pNewInfo->bHdmiRmd != pCurInfo->bHdmiRmd ||
			   pNewInfo->bHdmiFmt != pCurInfo->bHdmiFmt)
			{
				pNewInfo->stDirty.stBits.bHdmiSettings = BVDC_P_DIRTY;
				pNewInfo->stDirty.stBits.bTiming = BVDC_P_DIRTY;
				pNewInfo->stDirty.stBits.bTimeBase = BVDC_P_DIRTY;
				pNewInfo->stDirty.stBits.bDacSetting = BVDC_P_DIRTY;
				pNewInfo->stDirty.stBits.bAcp = BVDC_P_DIRTY;
			}

			if(VIDEO_FORMAT_IS_4kx2k(pNewInfo->pFmtInfo->eVideoFmt) && !pNewInfo->bHdmiRmd)
			{
				BDBG_ERR(("D%d: Need to enable HDMI output before setting 4kx2k format", hDisplay->eId));
				return BERR_TRACE(BVDC_ERR_VIDEO_FORMAT_NOT_SUPPORTED);
			}
#else
			if(VIDEO_FORMAT_IS_4kx2k(pNewInfo->pFmtInfo->eVideoFmt))
			{
				return BERR_TRACE(BVDC_ERR_VIDEO_FORMAT_NOT_SUPPORTED);
			}
#endif
			if(BVDC_P_DISPLAY_USED_DIGTRIG(hDisplay->eMasterTg) && (ulDacMask != 0))
			{
				BDBG_ERR(("Display[%d]: Analog outputs require analog eMasterTg.", hDisplay->eId));
				return BERR_TRACE(BVDC_ERR_VIDEOFMT_OUTPUT_MISMATCH);
			}

			/* Update HD Dac count */
			if(pNewInfo->bYPrPb && VIDEO_FORMAT_IS_HD(pNewInfo->pFmtInfo->eVideoFmt))
			{
				ulHdDacCnt++;
			}
			if(pNewInfo->bRgb && VIDEO_FORMAT_IS_HD(pNewInfo->pFmtInfo->eVideoFmt))
			{
				ulHdDacCnt++;
			}

			/*******/
			aulCurAnalogChan[i * 2] = pCurInfo->ulAnlgChan0Mask;
			aulCurAnalogChan[i * 2 + 1] = pCurInfo->ulAnlgChan1Mask;

			if(pNewInfo->bYPrPb && pNewInfo->bRgb)
			{
				/* if both YPrPb and Rgb, use both analog channels */
				aulNewAnalogChan[i * 2] |= BVDC_P_Dac_Mask_YPrPb;
				aulNewAnalogChan[i * 2 + 1] |= BVDC_P_Dac_Mask_RGB;
			}
			else if((pNewInfo->bYPrPb || pNewInfo->bRgb) &&
					!pNewInfo->bCvbs && !pNewInfo->bSvideo)
			{
				/* only component => if previously allocated on chan 1,
				   then use same channel */
				if((aulCurAnalogChan[i * 2 + 1] & BVDC_P_Dac_Mask_HD) ||
				   (hDisplay->stAnlgChan_1.eState == BVDC_P_DisplayResource_eResInactive))
				{
					aulNewAnalogChan[i * 2 + 1] |= (pNewInfo->bYPrPb) ? BVDC_P_Dac_Mask_YPrPb : 0;
					aulNewAnalogChan[i * 2 + 1] |= (pNewInfo->bRgb) ? BVDC_P_Dac_Mask_RGB : 0;
				}
				else
				{
					aulNewAnalogChan[i * 2] |= (pNewInfo->bYPrPb) ? BVDC_P_Dac_Mask_YPrPb : 0;
					aulNewAnalogChan[i * 2] |= (pNewInfo->bRgb) ? BVDC_P_Dac_Mask_RGB : 0;
				}
			}
			else if(pNewInfo->bYPrPb || pNewInfo->bRgb)
			{
				/* Both component and composite/svideo */
#if BVDC_P_VEC_STANDALONE_BUG_FIXED
				if((aulCurAnalogChan[i * 2 + 1] & BVDC_P_Dac_Mask_HD) ||
				   (aulCurAnalogChan[i * 2] & BVDC_P_Dac_Mask_SD))
#else
				/* either chan_0 or chan_1 is still around even with no DACs */
				/* need to match up the HD used one */
				if(hDisplay->stAnlgChan_1.ulHdsrc != BVDC_P_HW_ID_INVALID)
#endif
				{
					/* if previously allocated HD on chan 1 or SD on chan 0  */
					/* then use same channel */
					aulNewAnalogChan[i * 2 + 1] |= (pNewInfo->bYPrPb) ? BVDC_P_Dac_Mask_YPrPb : 0;
					aulNewAnalogChan[i * 2 + 1] |= (pNewInfo->bRgb) ? BVDC_P_Dac_Mask_RGB : 0;
					aulNewAnalogChan[i * 2] |= (pNewInfo->bCvbs) ? BVDC_P_Dac_Mask_Cvbs : 0;
					aulNewAnalogChan[i * 2] |= (pNewInfo->bSvideo) ? BVDC_P_Dac_Mask_Svideo : 0;
				}
				else
				{
					aulNewAnalogChan[i * 2] |= (pNewInfo->bYPrPb) ? BVDC_P_Dac_Mask_YPrPb : 0;
					aulNewAnalogChan[i * 2] |= (pNewInfo->bRgb) ? BVDC_P_Dac_Mask_RGB : 0;
					aulNewAnalogChan[i * 2 + 1] |= (pNewInfo->bCvbs) ? BVDC_P_Dac_Mask_Cvbs : 0;
					aulNewAnalogChan[i * 2 + 1] |= (pNewInfo->bSvideo) ? BVDC_P_Dac_Mask_Svideo : 0;
				}
			}
			else
			{
				/* Only composite or svideo */
				if((hDisplay->stAnlgChan_1.eState == BVDC_P_DisplayResource_eResInactive) ||
				   (aulCurAnalogChan[i * 2 + 1] & BVDC_P_Dac_Mask_SD))
				{
					aulNewAnalogChan[i * 2 + 1] |= (pNewInfo->bCvbs) ? BVDC_P_Dac_Mask_Cvbs : 0;
					aulNewAnalogChan[i * 2 + 1] |= (pNewInfo->bSvideo) ? BVDC_P_Dac_Mask_Svideo : 0;
				}
				else
				{
					aulNewAnalogChan[i * 2] |= (pNewInfo->bCvbs) ? BVDC_P_Dac_Mask_Cvbs : 0;
					aulNewAnalogChan[i * 2] |= (pNewInfo->bSvideo) ? BVDC_P_Dac_Mask_Svideo : 0;
				}
			}

			pNewInfo->ulAnlgChan0Mask = aulNewAnalogChan[i * 2];
			pNewInfo->ulAnlgChan1Mask = aulNewAnalogChan[i * 2 + 1];

			/* Initialize colorspace */
			pNewInfo->eAnlg_0_OutputColorSpace = BVDC_P_Output_eUnknown;
			pNewInfo->eAnlg_1_OutputColorSpace = BVDC_P_Output_eUnknown;

			BVDC_P_Display_AssignCSOutput(pNewInfo, pNewInfo->ulAnlgChan0Mask, &pNewInfo->eAnlg_0_OutputColorSpace);
			BVDC_P_Display_AssignCSOutput(pNewInfo, pNewInfo->ulAnlgChan1Mask, &pNewInfo->eAnlg_1_OutputColorSpace);

			/* evaluate bMultiRateAllow flag */
			/* To keep NTSC(cvbs/svideo) as 59.94hz and 480i can be 60.00hz or 59.94hz */
			/* Assumptions multiple of 24/15hz are capable of multirate capable display. */
			pNewInfo->bMultiRateAllow =
				(0 == (pNewInfo->pFmtInfo->ulVertFreq % (24 * BFMT_FREQ_FACTOR))) ||
				(0 == (pNewInfo->pFmtInfo->ulVertFreq % (20 * BFMT_FREQ_FACTOR))) ||
				(0 == (pNewInfo->pFmtInfo->ulVertFreq % (15 * BFMT_FREQ_FACTOR)));
			pNewInfo->bMultiRateAllow &= !(pNewInfo->bCvbs || pNewInfo->bSvideo);

			/* Multi-rate changes */
			if(pNewInfo->bMultiRateAllow != pCurInfo->bMultiRateAllow)
			{
				pNewInfo->stDirty.stBits.bSrcFrameRate = BVDC_P_DIRTY;
			}
		} /* end of active display	 */
	} /* end of DISPLAY looping  */

	/* Checking against HW limitation */
	if(ulHdDacCnt > BVDC_P_SUPPORT_HD_DAC)
	{
		return BERR_TRACE(BVDC_ERR_RESOURCE_NOT_AVAILABLE);
	}

	if(hVdc == NULL)
	{
		BDBG_LEAVE(BVDC_P_Display_ValidateDacSettings);
		return BERR_SUCCESS;
	}

	/* Handling DAC resource */
	BKNI_EnterCriticalSection();

	/* release cur first */
	for(i = 0; i < BVDC_P_MAX_DISPLAY_COUNT * 2; i++)
	{
		if(aulNewAnalogChan[i] != aulCurAnalogChan[i])
		{
			if(aulCurAnalogChan[i] != 0 && aulNewAnalogChan[i] == 0)
			{
				hDisplay = ahDisplay[i >> 1];
				BDBG_MSG(("D%d Release cur Dac resource for Chan%d: Cur = 0x%x, New = 0x%x",
					hDisplay->eId, (i & 0x1) ? 1 : 0,
					aulCurAnalogChan[i], aulNewAnalogChan[i]));
				if((i & 0x1) == 0)
				{
					hDisplay->stAnlgChan_0.eState = BVDC_P_DisplayResource_eDestroy;
					hDisplay->stNewInfo.stDirty.stBits.bChan0 = BVDC_P_DIRTY;
				}
				else
				{
						hDisplay->stAnlgChan_1.eState = BVDC_P_DisplayResource_eDestroy;
						hDisplay->stNewInfo.stDirty.stBits.bChan1 = BVDC_P_DIRTY;
					}
				}
			}
		}

	/* acquire new */
	for(i = 0; i < BVDC_P_MAX_DISPLAY_COUNT * 2; i++)
	{
		BVDC_P_DisplayAnlgChan *pstChan;
		uint32_t ulMask;
		bool bHwBugWorkAround = false;
		hDisplay = ahDisplay[i >> 1];

#if BVDC_P_VEC_STANDALONE_BUG_FIXED
		bHwBugWorkAround = false;
#else
		if(BVDC_P_STATE_IS_ACTIVE(hDisplay) ||
		   BVDC_P_STATE_IS_CREATE(hDisplay))
		{
			bHwBugWorkAround = (hDisplay->bAnlgEnable && /* analog master */
			                    /* and no DACs */
			                    (hDisplay->stNewInfo.ulAnlgChan0Mask == 0) &&
			                    (hDisplay->stNewInfo.ulAnlgChan1Mask == 0) &&
			                    (hDisplay->stAnlgChan_0.eState == BVDC_P_DisplayResource_eInactive) &&
			                    (hDisplay->stAnlgChan_1.eState == BVDC_P_DisplayResource_eInactive));
		}
#endif

		if(((aulNewAnalogChan[i] != aulCurAnalogChan[i]) &&
			(((aulNewAnalogChan[i] & BVDC_P_Dac_Mask_SD) && !(aulCurAnalogChan[i] & BVDC_P_Dac_Mask_SD)) ||
			 ((aulNewAnalogChan[i] & BVDC_P_Dac_Mask_HD) && !(aulCurAnalogChan[i] & BVDC_P_Dac_Mask_HD))))
			|| bHwBugWorkAround)
		{
			BDBG_MSG(("i=%d, bWA=%d, aulCurAnalogChan = 0x%x, aulNewAnalogChan = 0x%x",
				i, bHwBugWorkAround, aulCurAnalogChan[i], aulNewAnalogChan[i]));
			if((aulNewAnalogChan[i] != 0) || bHwBugWorkAround)
			{
				if((i & 0x1) == 0)
				{
					/* Chan 0 */
					pstChan = &hDisplay->stAnlgChan_0;
					ulMask = hDisplay->stNewInfo.ulAnlgChan0Mask;
				}
				else
				{
					/* Chan 1 */
					pstChan = &hDisplay->stAnlgChan_1;
					ulMask = hDisplay->stNewInfo.ulAnlgChan1Mask;
				}

				BDBG_MSG(("D%d Acquire new resource for Chan_%d", hDisplay->eId, (i & 0x1)));
				err = BVDC_P_AllocITResources(hVdc->hResource, hDisplay->eId * 2 + (i & 0x1), pstChan,
							hDisplay->stAnlgChan_0.ulIt);
				err |= BVDC_P_AllocAnalogChanResources(hVdc->hResource, hDisplay->eId * 2 + (i & 0x1), pstChan,
							(!(ulMask & BVDC_P_Dac_Mask_SD) && hDisplay->bHdCap) ? true : false ,
							(ulMask & BVDC_P_Dac_Mask_HD) ? true : false ,
							((ulMask & BVDC_P_Dac_Mask_SD) && (BVDC_P_NUM_SHARED_SECAM != 0) && (VIDEO_FORMAT_IS_SECAM(pNewInfo->pFmtInfo->eVideoFmt))) ? true : false);

				if(err)
				{
					BKNI_LeaveCriticalSection();
					BDBG_ERR(("Failed to add %s%s%soutput to display %d%s. Short of VEC hardware block. Check hardware capability.",
						     (ulMask & BVDC_P_Dac_Mask_HD) ? "component " : "",
						     (ulMask & BVDC_P_Dac_Mask_Cvbs) ? "composite " : "",
						     (ulMask & BVDC_P_Dac_Mask_Svideo) ? "S-Video " : "",
						     hDisplay->eId,
						     ((ulMask & BVDC_P_Dac_Mask_SD) && (BVDC_P_NUM_SHARED_SECAM != 0) && (VIDEO_FORMAT_IS_SECAM(pNewInfo->pFmtInfo->eVideoFmt))) ?
						     ", and being SECAM capable" : ""));
					BDBG_LEAVE(BVDC_P_Display_ValidateDacSettings);
					return BERR_TRACE(err);
				}

				/* Sanity check - CVBS won't work with HDSRC */
				if((ulMask & BVDC_P_Dac_Mask_SD) && (pstChan->ulHdsrc != BVDC_P_HW_ID_INVALID))
				{
					/* if not analog master, free IT resource */
					if(!hDisplay->bAnlgEnable)
						BVDC_P_FreeITResources_isr(hVdc->hResource, pstChan);
					BVDC_P_FreeAnalogChanResources_isr(hVdc->hResource, pstChan);
					BKNI_LeaveCriticalSection();
					BDBG_ERR(("Fail to assign HDSRC to %s%soutput for display %d",
						     (ulMask & BVDC_P_Dac_Mask_Cvbs) ? "composite " : "",
						     (ulMask & BVDC_P_Dac_Mask_Svideo) ? "S-Video " : "",
						     hDisplay->eId));
					BDBG_LEAVE(BVDC_P_Display_ValidateDacSettings);
					return BERR_TRACE(BVDC_ERR_RESOURCE_NOT_AVAILABLE);
				}

				pstChan->bEnable = true;
				pstChan->eState = BVDC_P_DisplayResource_eCreate;
				if((i & 0x1) == 0)
					hDisplay->stNewInfo.stDirty.stBits.bChan0 = BVDC_P_DIRTY;
				else
					hDisplay->stNewInfo.stDirty.stBits.bChan1 = BVDC_P_DIRTY;

#if !HW7425_807_IS_FIXED
				if((hDisplay->stAnlgChan_0.eState == BVDC_P_DisplayResource_eCreate && hDisplay->stNewInfo.ulAnlgChan1Mask != 0) ||
				   (hDisplay->stAnlgChan_1.eState == BVDC_P_DisplayResource_eCreate && hDisplay->stNewInfo.ulAnlgChan0Mask != 0))
				{
					BDBG_MSG(("Need to reset both Chan0 & Chan1"));
					hDisplay->stNewInfo.stDirty.stBits.bTiming = BVDC_P_DIRTY;
					hDisplay->stNewInfo.stDirty.stBits.bAcp    = BVDC_P_DIRTY;
				}
#endif

				if(bHwBugWorkAround)
				{
					BDBG_MSG(("All DACs OFF"));
				}
				else
				{
					if(aulNewAnalogChan[i] != 0 && aulCurAnalogChan[i] == 0)
					{
						BDBG_MSG(("Display %d Acquire new Dac resource for AnlgChan_%d", hDisplay->eId, (i & 0x1)));
						err = BVDC_P_AllocDacResources(hVdc->hResource, hDisplay, pstChan, aulNewAnalogChan[i]);
						if(err)
						{
							BKNI_LeaveCriticalSection();
							BDBG_ERR(("Failed to allocate DAC for display %d", hDisplay->eId));
							BDBG_LEAVE(BVDC_P_Display_ValidateDacSettings);
							return BERR_TRACE(err);
						}
					}
				}

#if (BVDC_P_SUPPORT_RFM_OUTPUT != 0)
				if(hDisplay->stCurInfo.eRfmOutput != BVDC_RfmOutput_eUnused)
				{
					hDisplay->stNewInfo.stDirty.stBits.bRfm = BVDC_P_DIRTY;
				}
#endif
			}
		}
	}
	BKNI_LeaveCriticalSection();

	/* Now aggregate the DAC assignment from all the display handle to a central place */
	BKNI_EnterCriticalSection();
	for (i = 0; i < BVDC_P_MAX_DACS; i++ )
	{
		hVdc->aDacOutput[i] = BVDC_DacOutput_eUnused;
		hVdc->aDacDisplay[i] = UINT32_C(-1);

		for(j = 0; j < BVDC_P_MAX_DISPLAY_COUNT; j++)
		{
			if((BVDC_P_STATE_IS_ACTIVE(ahDisplay[j]) || BVDC_P_STATE_IS_CREATE(ahDisplay[j]))
				&& (ahDisplay[j]->stNewInfo.aDacOutput[i] != BVDC_DacOutput_eUnused))
			{
				hVdc->aDacOutput[i] = ahDisplay[j]->stNewInfo.aDacOutput[i];
				hVdc->aDacDisplay[i] = (uint32_t)ahDisplay[j]->eId;
			}
		}
	}
	BKNI_LeaveCriticalSection();

	BKNI_EnterCriticalSection();
	for(i = 0; i < BVDC_P_MAX_DISPLAY_COUNT; i++)
	{
		/* Only validate the create or active onces. */
		if(BVDC_P_STATE_IS_ACTIVE(ahDisplay[i]) ||
		   BVDC_P_STATE_IS_CREATE(ahDisplay[i]))
		{
			hDisplay = ahDisplay[i];
			if(hDisplay->stNewInfo.stDirty.stBits.bDacSetting &
			  !(hDisplay->stNewInfo.stDirty.stBits.bChan0 ||
			    hDisplay->stNewInfo.stDirty.stBits.bChan1 ||
			    hDisplay->stNewInfo.stDirty.stBits.bTiming))
			{
				BDBG_MSG(("D%d Need program analog chan with DACS %d %d %d %d",
					hDisplay->eId,
					hDisplay->stNewInfo.stDirty.stBits.bDacSetting,
					hDisplay->stNewInfo.stDirty.stBits.bChan0,
					hDisplay->stNewInfo.stDirty.stBits.bChan1,
					hDisplay->stNewInfo.stDirty.stBits.bTiming));
				hDisplay->bDacProgAlone = true;
			}
			else
			{
				hDisplay->bDacProgAlone = false;
			}
		}
	}
	BKNI_LeaveCriticalSection();

#ifdef BCHP_PWR_RESOURCE_VDC_DAC
	for (i = 0; i < BVDC_P_MAX_DACS; i++ )
	{
		if(hVdc->aDacDisplay[i] != UINT32_C(-1))
		{
			hDisplay = ahDisplay[hVdc->aDacDisplay[i]];
			/* Dac is used, turn on PWR */
			if(hDisplay->ulDacPwrAcquire == 0)
			{
				BDBG_MSG(("DAC: Acquire BCHP_PWR_RESOURCE_VDC_DAC"));
				BCHP_PWR_AcquireResource(hDisplay->hVdc->hChip, BCHP_PWR_RESOURCE_VDC_DAC);
				hDisplay->ulDacPwrAcquire++;
			}
		}
	}
#endif

	BDBG_LEAVE(BVDC_P_Display_ValidateDacSettings);
	return BERR_SUCCESS;
}

/*************************************************************************
 *  {secret}
 * BVDC_P_Display_ValidateChanges
 *
 * Validates user's new settings for all displays
 **************************************************************************/
BERR_Code BVDC_P_Display_ValidateChanges
	( BVDC_Display_Handle              ahDisplay[] )
{
	BERR_Code                 err = BERR_SUCCESS;
	BVDC_Display_Handle       hDisplay;
	BVDC_Display_ValidateSetting validateSettingHandler;
	uint32_t i, j, limit;

	BDBG_ENTER(BVDC_P_Display_ValidateChanges);

	for (i=0; i < BVDC_P_MAX_DISPLAY_COUNT; i++)
	{
		if(BVDC_P_STATE_IS_ACTIVE(ahDisplay[i]) ||
		   BVDC_P_STATE_IS_CREATE(ahDisplay[i]))
		{
			ahDisplay[i]->stNewInfo.bErrorLastSetting = true;
		}
	}

	if ((err = BVDC_P_Display_ValidateDacSettings(ahDisplay)))
	{
		BDBG_ERR(("Invalid DAC settings, error 0x%x", err));
		return BERR_TRACE(err);
	}

	for (i=0; i < BVDC_P_MAX_DISPLAY_COUNT; i++)
	{
		hDisplay = ahDisplay[i];

		if(BVDC_P_STATE_IS_ACTIVE(hDisplay) ||
		   BVDC_P_STATE_IS_CREATE(hDisplay))
		{
			/*
			 * Edit out redundant dirty bits state. It would be nice to move
			 * this logic somewhere else, but I don't know where it should go.
			 */
			BVDC_P_DisplayInfo* pNewInfo = &(hDisplay->stNewInfo);
			if (pNewInfo->stDirty.stBits.bTiming == BVDC_P_DIRTY)
			{
				pNewInfo->stDirty.stBits.bAcp        = BVDC_P_CLEAN;
				pNewInfo->stDirty.stBits.bWidthTrim  = BVDC_P_CLEAN;
			}

			if (BVDC_P_IS_DIRTY(&(pNewInfo->stDirty)))
			{
				limit = BVDC_P_MIN(
					BVDC_P_astDisplayEventHndlTblSize,
					BVDC_P_NUM_DIRTY_BITS(&(pNewInfo->stDirty)));
				for (j=0 ; j < limit ; j++)
				{
					if (BVDC_P_DISPLAY_IS_BIT_DIRTY(&(pNewInfo->stDirty), j))
					{
						/* Get validation handler from display event handling table */
						validateSettingHandler = BVDC_P_astDisplayEventHndlTbl[j].validateSettingHandler;
						if (validateSettingHandler)
						{
							if ((err = validateSettingHandler(hDisplay)))
							{
								BDBG_ERR(("Invalid setting %d on display %d, err %d", j, i, err));
								return BERR_TRACE(err);
							}
						}
					}
				}
			}
		}
	}

	for (i=0; i < BVDC_P_MAX_DISPLAY_COUNT; i++)
	{
		if(BVDC_P_STATE_IS_ACTIVE(ahDisplay[i]) ||
		   BVDC_P_STATE_IS_CREATE(ahDisplay[i]))
		{
			ahDisplay[i]->stNewInfo.bErrorLastSetting = false;
		}
	}

	BDBG_LEAVE(BVDC_P_Display_ValidateChanges);
	return err;
}


/*************************************************************************
 *  {secret}
 *  BVDC_P_Display_ApplyChanges_isr
 *
 *  New requests have been validated. New user settings will be applied
 *  at next Display isr.
 **************************************************************************/
void BVDC_P_Display_ApplyChanges_isr
	( BVDC_Display_Handle              hDisplay )
{
	uint32_t i, limit;
	BVDC_Display_CopySetting copySettingHandler;

	BDBG_ENTER(BVDC_P_Display_ApplyChanges_isr);
	BDBG_OBJECT_ASSERT(hDisplay, BVDC_DSP);
	BDBG_OBJECT_ASSERT(hDisplay->hCompositor, BVDC_CMP);

	/* State transition for display/compositor. */
	if(BVDC_P_STATE_IS_CREATE(hDisplay))
	{
		BDBG_MSG(("Display%d activated.", hDisplay->eId));
		hDisplay->eState = BVDC_P_State_eActive;
		/* Re-enable callback in apply. */
		for(i = 0; i < BVDC_P_CMP_MAX_SLOT_COUNT; i++)
		{
			BINT_ClearCallback_isr(hDisplay->hCompositor->ahCallback[i]);
			BINT_EnableCallback_isr(hDisplay->hCompositor->ahCallback[i]);
		}

		/* Assign Trigger to slot.  Effectively enable slots. */
		BVDC_P_Compositor_AssignTrigger_isr(hDisplay->hCompositor,
			hDisplay->eTopTrigger, hDisplay->eBotTrigger);
	}
	else if(BVDC_P_STATE_IS_DESTROY(hDisplay))
	{
		BDBG_MSG(("Display%d de-activated.", hDisplay->eId));

		/* disable triggers to complete shutdown display callbacks. */
		BVDC_P_Display_EnableTriggers_isr(hDisplay, false);
		hDisplay->eState = BVDC_P_State_eInactive;
		for(i = 0; i < BVDC_P_CMP_MAX_SLOT_COUNT; i++)
		{
			BRDC_Slot_Disable_isr(hDisplay->hCompositor->ahSlot[i]);
		}

		for(i = 0; i < BVDC_P_CMP_MAX_SLOT_COUNT; i++)
		{
			BINT_DisableCallback_isr(hDisplay->hCompositor->ahCallback[i]);
			BINT_ClearCallback_isr(hDisplay->hCompositor->ahCallback[i]);
		}

		/* Free all the resources
		 * Note: The cores may still be up but triggers are
		 *       disabled. Next create will reset and restart
		 *       them.
		 *
		 *       If we want to shut the cores down, then RUL version
		 *       tear-down can not be used. This is because the RDC
		 *       slot has been disabled thus RUL won't get executed.
		 *       If we defer the RDC slot disable, a complicated scheme
		 *       may be needed here because there won't be ISR any more
		 *       since triggers are disabled.
		 *
		 *       One way to solve this dilemma is to create host write
		 *       version tear-down. For now we leave them as active since
		 *       the power consumption is small.
		 */
		if ((hDisplay->stAnlgChan_0.ulIt != BVDC_P_HW_ID_INVALID))
		{
			BREG_Write32(hDisplay->hVdc->hRegister,
				BCHP_VEC_CFG_IT_0_SOURCE + hDisplay->stAnlgChan_0.ulIt * 4, BCHP_VEC_CFG_IT_0_SOURCE_SOURCE_DISABLE);
		}
		BVDC_P_FreeITResources_isr(hDisplay->hCompositor->hVdc->hResource, &hDisplay->stAnlgChan_0);
		BVDC_P_FreeAnalogChanResources_isr(hDisplay->hCompositor->hVdc->hResource, &hDisplay->stAnlgChan_0);
		BVDC_P_FreeAnalogChanResources_isr(hDisplay->hCompositor->hVdc->hResource, &hDisplay->stAnlgChan_1);
		if ((hDisplay->stDviChan.ulDvi != BVDC_P_HW_ID_INVALID))
		{
			BREG_Write32(hDisplay->hVdc->hRegister,
				BCHP_VEC_CFG_DVI_DTG_0_SOURCE + hDisplay->stDviChan.ulDvi * 4, BCHP_VEC_CFG_DVI_DTG_0_SOURCE_SOURCE_DISABLE);
		}
		BVDC_P_FreeDviChanResources_isr(hDisplay->hCompositor->hVdc->hResource, &hDisplay->stDviChan);
		if (BVDC_P_HW_ID_INVALID != hDisplay->stMpaaComp.ulHwId ||
			BVDC_P_HW_ID_INVALID != hDisplay->stMpaaHdmi.ulHwId)
		{
			BREG_Write32(hDisplay->hVdc->hRegister,
				BCHP_VEC_CFG_DECIM_0_SOURCE, BCHP_VEC_CFG_DECIM_0_SOURCE_SOURCE_DISABLE);
		}
		BVDC_P_FreeMpaaResources_isr(hDisplay->hCompositor->hVdc->hResource, &hDisplay->stMpaaComp);
		BVDC_P_FreeMpaaResources_isr(hDisplay->hCompositor->hVdc->hResource, &hDisplay->stMpaaHdmi);
#ifdef BCHP_PWR_RESOURCE_VDC_HDMI_TX_PHY0
		if(hDisplay->ulHdmiPwrAcquire != 0)
		{
			hDisplay->ulHdmiPwrAcquire--;
			hDisplay->ulHdmiPwrRelease = 1;
			BDBG_MSG(("HDMI master mode destroy: Release pending BCHP_PWR_RESOURCE_VDC_HDMI_TX_PHY"));
		}
#endif
#ifdef BCHP_PWR_RESOURCE_VDC_DAC
		if(hDisplay->ulDacPwrAcquire != 0)
		{
			hDisplay->ulDacPwrAcquire--;
			hDisplay->ulDacPwrRelease = 1;
			BDBG_MSG(("DAC destroy: Release pending BCHP_PWR_RESOURCE_VDC_DAC"));
		}
#endif

#if BVDC_P_SUPPORT_ITU656_OUT
		if ((hDisplay->st656Chan.ul656 != BVDC_P_HW_ID_INVALID))
		{
			BREG_Write32(hDisplay->hVdc->hRegister,
				BCHP_VEC_CFG_ITU656_DTG_0_SOURCE, BCHP_VEC_CFG_ITU656_DTG_0_SOURCE_SOURCE_DISABLE);
		}
		BVDC_P_Free656ChanResources_isr(hDisplay->hCompositor->hVdc->hResource, hDisplay);

#ifdef BCHP_PWR_RESOURCE_VDC_656_OUT
		if(hDisplay->ul656PwrAcquire != 0)
		{
			hDisplay->ul656PwrAcquire--;
			hDisplay->ul656PwrRelease = 1;
			BDBG_MSG(("656 master mode destroy: Release pending BCHP_PWR_RESOURCE_VDC_656_OUT"));
		}
#endif
#endif

#if BVDC_P_SUPPORT_STG
		if ((hDisplay->stStgChan.ulStg != BVDC_P_HW_ID_INVALID))
		{
			uint32_t  ulRegOffset = 0;
			if(BVDC_P_DISPLAY_USED_STG(hDisplay->eMasterTg))
				ulRegOffset = (hDisplay->eMasterTg - BVDC_DisplayTg_eStg0) * sizeof(uint32_t);
			else /* Slave mode */
				ulRegOffset = hDisplay->stStgChan.ulStg * sizeof(uint32_t);
			BREG_Write32(hDisplay->hVdc->hRegister,
				BCHP_VEC_CFG_STG_0_SOURCE + ulRegOffset, BCHP_VEC_CFG_STG_0_SOURCE_SOURCE_DISABLE);
		}
		BVDC_P_FreeStgChanResources_isr(hDisplay->hCompositor->hVdc->hResource, hDisplay);
#if BVDC_P_SUPPORT_VIP
		if(hDisplay->hVip) /* put VIP back to auto drain mode */
		{
			#include "bchp_vice2_vip_0_0.h"
			BREG_Write32_isr(hDisplay->hVdc->hRegister, BCHP_VICE2_VIP_0_0_CONFIG + hDisplay->hVip->ulRegOffset, 0);
			hDisplay->stCurInfo.hVipHeap = NULL; /* to free vip buffers later */
		}
#endif
#endif

		/* Clear dirty bits */
		BVDC_P_CLEAN_ALL_DIRTY(&(hDisplay->stNewInfo.stDirty));
		BVDC_P_CLEAN_ALL_DIRTY(&(hDisplay->stCurInfo.stDirty));
		BVDC_P_CLEAN_ALL_DIRTY(&(hDisplay->stPrevDirty));

		return;
	}

	/**
	 * Reset IT state to not active for display with masterTg turned on, in order for apply
	 * changes to restart ISR.
	 */
	if(((hDisplay->st656Chan.bEnable) &&
	    (hDisplay->stNewInfo.bEnable656  && !hDisplay->stCurInfo.bEnable656)) ||
	   ((hDisplay->stStgChan.bEnable) &&
	    (hDisplay->stNewInfo.bEnableStg  && !hDisplay->stCurInfo.bEnableStg)) ||
	   ((hDisplay->stDviChan.bEnable) &&
	    (hDisplay->stNewInfo.bEnableHdmi && !hDisplay->stCurInfo.bEnableHdmi)))
	{
		hDisplay->eItState = BVDC_P_ItState_eNotActive;
		BDBG_MSG(("Display %d resets state to kick start", hDisplay->eId));
	}

	/* Copy all the new settings to CurInfo so that they can be applied
	 * to HW in BVDC_P_Vec_BuildRul_isr(). */
	if (BVDC_P_IS_DIRTY(&(hDisplay->stNewInfo.stDirty)))
	{
		limit = BVDC_P_MIN(
			BVDC_P_astDisplayEventHndlTblSize,
			BVDC_P_NUM_DIRTY_BITS(&(hDisplay->stNewInfo.stDirty)));
		for (i=0 ; i < limit ; i++)
		{
			if (BVDC_P_DISPLAY_IS_BIT_DIRTY(&(hDisplay->stNewInfo.stDirty), i))
			{
				/* Get copy handler from display event handling table */
				copySettingHandler = BVDC_P_astDisplayEventHndlTbl[i].copySettingHandler;
				if (copySettingHandler)
				{
					copySettingHandler(hDisplay);
				}

				/* Clear the dirty bit in new info */
				BVDC_P_DISPLAY_CLEAR_DIRTY_BIT(&(hDisplay->stNewInfo.stDirty), i);

				/* Set the dirty bit in current info */
				BVDC_P_DISPLAY_SET_DIRTY_BIT(&(hDisplay->stCurInfo.stDirty), i);
			}
		}

		/* Mark user changes pending. Wait for next vsync ISR to build RUL and
		 * clear the flags.
		 */
		BKNI_ResetEvent(hDisplay->hAppliedDoneEvent);
		hDisplay->bSetEventPending = true;
	}

	/* No RUL has been executed yet, we've no triggers activated.  Must
	 * force the initial top RUL here! */
	if((BVDC_P_ItState_eNotActive == hDisplay->eItState) &&
	   (!hDisplay->bIsBypass))
	{
		/* Start List */
		BVDC_P_ListInfo stList;

		/* Build Vec Top RUL and force it to execute immediately. */
		BRDC_List_Handle hList = BVDC_P_CMP_GET_LIST(hDisplay->hCompositor,
			BAVC_Polarity_eTopField);
		BRDC_Slot_Handle hSlot = BVDC_P_CMP_GET_SLOT(hDisplay->hCompositor,
			BAVC_Polarity_eTopField);

		BRDC_List_SetNumEntries_isr(hList, 0);
		BVDC_P_ReadListInfo_isr(&stList, hList);
		if(BVDC_P_DISPLAY_USED_STG(hDisplay->eMasterTg))
		{
			/* skip the intermediate states */
			hDisplay->eItState = BVDC_P_ItState_eActive;
			BVDC_P_Compositor_BuildSyncSlipRul_isr(hDisplay->hCompositor, &stList, BAVC_Polarity_eTopField, true);
		}
		else
		{
			BVDC_P_Vec_BuildRul_isr(hDisplay, &stList, BAVC_Polarity_eTopField);
		}
		BVDC_P_WriteListInfo_isr(&stList, hList);

		/* Assign Trigger to slot.	Effectively enable slots. */
#if (BVDC_P_ORTHOGONAL_VEC_VER < BVDC_P_ORTHOGONAL_VEC_VER_1)
		switch(hDisplay->eMasterTg)
		{
			case BVDC_DisplayTg_eDviDtg:
				hDisplay->eTopTrigger = BRDC_Trigger_eDvoTrig0;
				hDisplay->eBotTrigger = BRDC_Trigger_eDvoTrig1;
				break;

			case BVDC_DisplayTg_e656Dtg:
				hDisplay->eTopTrigger = BRDC_Trigger_eDtgTrig0;
				hDisplay->eBotTrigger = BRDC_Trigger_eDtgTrig1;
				break;

			case BVDC_DisplayTg_ePrimIt:
			case BVDC_DisplayTg_eSecIt:
			case BVDC_DisplayTg_eTertIt:
				switch(hDisplay->stAnlgChan_0.ulIt)
				{
					case 0:
						hDisplay->eTopTrigger = BRDC_Trigger_eVec0Trig0;
						hDisplay->eBotTrigger = BRDC_Trigger_eVec0Trig1;
						break;
					case 1:
						hDisplay->eTopTrigger = BRDC_Trigger_eVec1Trig0;
						hDisplay->eBotTrigger = BRDC_Trigger_eVec1Trig1;
						break;
					case 2:
						hDisplay->eTopTrigger = BRDC_Trigger_eVec2Trig0;
						hDisplay->eBotTrigger = BRDC_Trigger_eVec2Trig1;
						break;
					default:
						break;
				}
				break;

			case BVDC_DisplayTg_eStg0:
				hDisplay->eTopTrigger = BRDC_Trigger_eStg0Trig0;
				hDisplay->eBotTrigger = BRDC_Trigger_eStg0Trig1;
				break;
#if (BVDC_P_SUPPORT_STG > 1)
			case BVDC_DisplayTg_eStg1:
				break;
#endif
			default:
				break;
		}
#else
		switch(hDisplay->hCompositor->eId)
		{
			case BVDC_CompositorId_eCompositor0:
				hDisplay->eTopTrigger = BRDC_Trigger_eCmp_0Trig0;
				hDisplay->eBotTrigger = BRDC_Trigger_eCmp_0Trig1;
				break;

			case BVDC_CompositorId_eCompositor1:
				hDisplay->eTopTrigger = BRDC_Trigger_eCmp_1Trig0;
				hDisplay->eBotTrigger = BRDC_Trigger_eCmp_1Trig1;
				break;

			case BVDC_CompositorId_eCompositor2:
				hDisplay->eTopTrigger = BRDC_Trigger_eCmp_2Trig0;
				hDisplay->eBotTrigger = BRDC_Trigger_eCmp_2Trig1;
				break;

			case BVDC_CompositorId_eCompositor3:
				hDisplay->eTopTrigger = BRDC_Trigger_eCmp_3Trig0;
				hDisplay->eBotTrigger = BRDC_Trigger_eCmp_3Trig1;
				break;

			case BVDC_CompositorId_eCompositor4:
				hDisplay->eTopTrigger = BRDC_Trigger_eCmp_4Trig0;
				hDisplay->eBotTrigger = BRDC_Trigger_eCmp_4Trig1;
				break;

			case BVDC_CompositorId_eCompositor5:
				hDisplay->eTopTrigger = BRDC_Trigger_eCmp_5Trig0;
				hDisplay->eBotTrigger = BRDC_Trigger_eCmp_5Trig1;
				break;

			case BVDC_CompositorId_eCompositor6:
				hDisplay->eTopTrigger = BRDC_Trigger_eCmp_6Trig0;
				hDisplay->eBotTrigger = BRDC_Trigger_eCmp_6Trig1;
				break;

			default:
				break;
		}
#endif

		BVDC_P_Compositor_AssignTrigger_isr(hDisplay->hCompositor,
			hDisplay->eTopTrigger, hDisplay->eBotTrigger);

		BRDC_Slot_SetList_isr(hSlot, hList);
		BRDC_Slot_Execute_isr(hSlot);
	}

	BDBG_LEAVE(BVDC_P_Display_ApplyChanges_isr);
}

/***************************************************************************
 * {private}
 *
 */
void BVDC_P_Display_AbortChanges
	( BVDC_Display_Handle              hDisplay )
{
	BDBG_ENTER(BVDC_P_Display_AbortChanges);
	BDBG_OBJECT_ASSERT(hDisplay, BVDC_DSP);

	/* Cancel the setting user set to the new state. */
	hDisplay->stNewInfo = hDisplay->stCurInfo;

	/* SW7425-4609: restore validation value */
	hDisplay->stNewInfo.ulVertFreq = hDisplay->stNewInfo.pFmtInfo->ulVertFreq;

	BDBG_LEAVE(BVDC_P_Display_AbortChanges);
	return;
}

/*************************************************************************
 *  {secret}
 *  BVDC_P_Vec_BuildGameMode_isr
 **************************************************************************/
static void BVDC_P_Vec_BuildGameMode_isr
	( BVDC_Display_Handle              hDisplay,
	  BVDC_P_ListInfo                 *pList )
{
	uint32_t    ulRmOffset = hDisplay->stAnlgChan_0.ulRmRegOffset;

	/* set up game mode VEC RM */
	if(hDisplay->hWinGameMode && hDisplay->pRmTable &&
	   BVDC_P_STATE_IS_ACTIVE(hDisplay->hWinGameMode) &&
	   hDisplay->hWinGameMode->stCurInfo.stGameDelaySetting.bEnable &&
	   BVDC_P_IS_CLEAN(&hDisplay->hWinGameMode->stCurInfo.stDirty))
	{
		/* set rate */
		if(hDisplay->hWinGameMode->bAdjGameModeClock)
		{
			int32_t lAdj = (int32_t)hDisplay->pRmTable[BVDC_P_DISPLAY_RM_PHASE_INC_REG_OFFSET] /
				(1000 * ((hDisplay->hWinGameMode->lCurGameModeLag>0)? 1 : -1));

			/* PRIM_RM_PHASE_INC (RW) */
			*pList->pulCurrent++ = BRDC_OP_IMM_TO_REG();
			*pList->pulCurrent++ = BRDC_REGISTER(BCHP_RM_0_PHASE_INC + ulRmOffset);
			*pList->pulCurrent++ =
				BCHP_FIELD_DATA(RM_0_PHASE_INC, PHASE_INC,
				hDisplay->pRmTable[BVDC_P_DISPLAY_RM_PHASE_INC_REG_OFFSET] + lAdj);

			hDisplay->bRmAdjusted = true;
			BDBG_MSG(("Game mode delay: %d[usec]; to accelarate VEC%d RM? %d;",
				hDisplay->hWinGameMode->ulCurBufDelay, hDisplay->stAnlgChan_0.ulIt, lAdj));
		}
		else if(hDisplay->bRmAdjusted) /* restore */
		{
			/* PRIM_RM_PHASE_INC (RW) */
			*pList->pulCurrent++ = BRDC_OP_IMM_TO_REG();
			*pList->pulCurrent++ = BRDC_REGISTER(BCHP_RM_0_PHASE_INC + ulRmOffset);
			*pList->pulCurrent++ = BCHP_FIELD_DATA(RM_0_PHASE_INC, PHASE_INC,
				hDisplay->pRmTable[BVDC_P_DISPLAY_RM_PHASE_INC_REG_OFFSET]);
			hDisplay->bRmAdjusted = false;
		}
	}
	else if(hDisplay->bRmAdjusted) /* restore */
	{
		/* PRIM_RM_PHASE_INC (RW) */
		*pList->pulCurrent++ = BRDC_OP_IMM_TO_REG();
		*pList->pulCurrent++ = BRDC_REGISTER(BCHP_RM_0_PHASE_INC + ulRmOffset);
		*pList->pulCurrent++ = BCHP_FIELD_DATA(RM_0_PHASE_INC, PHASE_INC,
			hDisplay->pRmTable[BVDC_P_DISPLAY_RM_PHASE_INC_REG_OFFSET]);
		hDisplay->bRmAdjusted = false;
	}

}

/*************************************************************************
 *  {secret}
 *	BVDC_P_Vec_BuildVsync_isr
 *
 *	Adds Vec settings required for Vsync updates:
 *	VF_AGC_VALUES (for macrovision)
 *	IT_BVB_CONFIG[PSYNC] or DTG_BVB[PSYNC]
 **************************************************************************/
void BVDC_P_Vec_BuildVsync_isr
	( BVDC_Display_Handle              hDisplay,
	  BVDC_P_ListInfo                 *pList,
	  BAVC_Polarity                    eFieldPolarity )
{
	BVDC_P_DisplayInfo *pCurInfo;

	BDBG_ENTER(BVDC_P_Vec_BuildVsync_isr);
	BDBG_OBJECT_ASSERT(hDisplay, BVDC_DSP);

	pCurInfo = &hDisplay->stCurInfo;

    /* Update VSYNC counter */
    hDisplay->ulVsyncCnt++;

	/* Primary or Secondary path */
	if (!hDisplay->bIsBypass)
	{
		BVDC_P_Vec_BuildGameMode_isr(hDisplay, pList);
	}

#if DCS_SUPPORT /** { **/

	/* Execute DCS no-glitch transition, if any. */
	if ((hDisplay->stAnlgChan_0.bEnable) || (hDisplay->stAnlgChan_1.bEnable))
	{
		BVDC_P_DCS_StateUpdate_isr (hDisplay, eFieldPolarity, pList);
	}

#else /** } !DCS_SUPPORT { **/

	/* Update VF_POS_SYNC_VALUES for every frame for AGC cycling.
	 * Note: progressive format will not have Bottom Field interrupt. */
	if (((hDisplay->stAnlgChan_0.bEnable) || (hDisplay->stAnlgChan_1.bEnable))
		&&
	   pCurInfo->eMacrovisionType != BVDC_MacrovisionType_eNoProtection)
	{
		uint32_t ulVal = BVDC_P_GetPosSyncValue_isr(hDisplay, &pList->pulCurrent);
		if (hDisplay->stAnlgChan_0.bEnable)
		{
			BDBG_ASSERT(hDisplay->stAnlgChan_0.ulVf != BVDC_P_HW_ID_INVALID);

			*pList->pulCurrent++ = BRDC_OP_IMM_TO_REG();
			*pList->pulCurrent++ =
				BRDC_REGISTER(BCHP_VF_0_POS_SYNC_VALUES + hDisplay->stAnlgChan_0.ulVfRegOffset);
			*pList->pulCurrent++ = ulVal;
		}
		if (hDisplay->stAnlgChan_1.bEnable)
		{
			BDBG_ASSERT(hDisplay->stAnlgChan_1.ulVf != BVDC_P_HW_ID_INVALID);

			*pList->pulCurrent++ = BRDC_OP_IMM_TO_REG();
			*pList->pulCurrent++ =
				BRDC_REGISTER(BCHP_VF_0_POS_SYNC_VALUES + hDisplay->stAnlgChan_1.ulVfRegOffset);
			*pList->pulCurrent++ = ulVal;
		}
	}
	else
#endif /* } DCS_SUPPORT **/
	{
		/* Build a nop RUL to make RDC sanity check happy.  */
		*pList->pulCurrent++ = BRDC_OP_NOP();
	}

	/* Write the ariticial L2 interrupt bit */
	if(hDisplay->stCurInfo.bArtificialVsync)
	{
		*pList->pulCurrent++ = BRDC_OP_IMM_TO_REG();
		*pList->pulCurrent++ = BRDC_REGISTER(hDisplay->stCurInfo.ulArtificialVsyncRegAddr);
		*pList->pulCurrent++ = hDisplay->stNewInfo.ulArtificialVsyncMask;
	}

#if (BVDC_P_SUPPORT_TDAC_VER >= BVDC_P_SUPPORT_TDAC_VER_9)
	/* Read DAC detection status register */
	if(hDisplay->hVdc->bDacDetectionEnable)
	{
#if BVDC_P_VEC_CABLE_DETECT_SW_WORKAROUND
		if(hDisplay->eId == BVDC_DisplayId_eDisplay0)
		{
			BVDC_P_CableDetect_isr(hDisplay);
		}
#else
		uint32_t ulReg = 0;
		uint32_t ulDac;
#if (BVDC_P_SUPPORT_TDAC_VER < BVDC_P_SUPPORT_TDAC_VER_13)
		bool bCalibrated;

		ulReg = BREG_Read32_isr(hDisplay->hVdc->hRegister, BCHP_MISC_DAC_CABLE_STATUS_0);

		bCalibrated = BVDC_P_GET_FIELD(ulReg, MISC_DAC_CABLE_STATUS_0, CALIBRATED);
		if(bCalibrated != hDisplay->hVdc->bCalibrated)
		{
			BDBG_MSG(("Calibrate = %d", bCalibrated));
			hDisplay->hVdc->bCalibrated = bCalibrated;
			hDisplay->stCurInfo.stDirty.stBits.bDacSetting = BVDC_P_DIRTY;
		}
#else
		if(pCurInfo->pfGenericCallback && pCurInfo->stCallbackSettings.stMask.bCableDetect)
		{
			ulReg = BREG_Read32_isr(hDisplay->hVdc->hRegister, BCHP_MISC_DAC_CABLE_STATUS_0);
		}
#endif /* BVDC_P_SUPPORT_TDAC_VER < BVDC_P_SUPPORT_TDAC_VER_13 */

		/* When cable detection enabled and the HW detection status is working */
		/* read the status register to return when callback enabled */
		if(pCurInfo->pfGenericCallback && pCurInfo->stCallbackSettings.stMask.bCableDetect)
		{
			for(ulDac=0; ulDac<BVDC_P_MAX_DACS; ulDac++)
			{
				hDisplay->hVdc->aeDacStatus[ulDac] = (ulReg & (1 << ulDac)) ?
					BVDC_DacConnectionState_eConnected: BVDC_DacConnectionState_eDisconnected;
			}
		}

#endif /* BVDC_P_VEC_CABLE_DETECT_SW_WORKAROUND */
	}
#endif /* BVDC_P_SUPPORT_TDAC_VER >= BVDC_P_SUPPORT_TDAC_VER_9 */

	/* Display callback installed? */
	if (pCurInfo->pfGenericCallback)
	{
		BVDC_Display_CallbackData *pCbData = &hDisplay->stCallbackData;

		pCbData->eId = hDisplay->eId;
		pCbData->ePolarity = BVDC_P_NEXT_POLARITY(eFieldPolarity);

		/* Notify external modules of rate manager updated. */
		if((hDisplay->bRateManagerUpdated) &&
		   (pCurInfo->stCallbackSettings.stMask.bRateChange))
		{
			pCbData->stMask.bRateChange = 1;
			pCbData->sDisplayInfo = pCurInfo->stRateInfo;
			/* Clear rate change flag */
			hDisplay->bRateManagerUpdated = false;
		}
		else
		{
			pCbData->stMask.bRateChange = 0;
		}

		/* Notify external modules of vsync cadence */
		if((BVDC_P_ItState_eActive == hDisplay->eItState) &&
		   (pCurInfo->stCallbackSettings.stMask.bPerVsync))
		{
			pCbData->stMask.bPerVsync = 1;
		}
		else
		{
			pCbData->stMask.bPerVsync = 0;
		}

#if BVDC_P_SUPPORT_CMP_CRC
		if (pCurInfo->stCallbackSettings.stMask.bCrc
#if BVDC_P_SUPPORT_STG/* SW7445-2544: don't callback CRC for ignore picture in NRT mode */
		    && !(BVDC_P_DISPLAY_USED_STG(hDisplay->eMasterTg) &&
		         pCurInfo->bStgNonRealTime && hDisplay->hCompositor->bCrcIgnored)
#endif
		)
		{
			uint32_t ulReg;

			/* Get new CRC YCrCb values */
			ulReg = BREG_Read32_isr(hDisplay->hVdc->hRegister,
				BCHP_CMP_0_CRC_Y_STATUS + hDisplay->hCompositor->ulRegOffset);
			pCbData->ulCrcLuma = BVDC_P_GET_FIELD(ulReg, CMP_0_CRC_Y_STATUS, VALUE);

			ulReg = BREG_Read32_isr(hDisplay->hVdc->hRegister,
				BCHP_CMP_0_CRC_CR_STATUS + hDisplay->hCompositor->ulRegOffset);
			pCbData->ulCrcCr = BVDC_P_GET_FIELD(ulReg, CMP_0_CRC_CR_STATUS, VALUE);

			ulReg = BREG_Read32_isr(hDisplay->hVdc->hRegister,
				BCHP_CMP_0_CRC_CB_STATUS + hDisplay->hCompositor->ulRegOffset);
			pCbData->ulCrcCb= BVDC_P_GET_FIELD(ulReg, CMP_0_CRC_CB_STATUS, VALUE);

			pCbData->stMask.bCrc = 1;
			BDBG_MSG(("origPts=%#x, lumaCrc=%#x", hDisplay->hCompositor->ulOrigPTS, pCbData->ulCrcLuma));
}
		else
		{
			pCbData->stMask.bCrc = 0;
		}
#endif

		if (pCurInfo->stCallbackSettings.stMask.bStgPictureId &&
		   (hDisplay->hCompositor->ulPicId != pCbData->ulStgPictureId))
		{
			pCbData->ulDecodePictureId = hDisplay->hCompositor->ulDecodePictureId;
			pCbData->ulStgPictureId    = hDisplay->hCompositor->ulPicId;
			pCbData->sDisplayInfo      = pCurInfo->stRateInfo;
			pCbData->stMask.bStgPictureId = 1;
		}
		else
		{
			pCbData->stMask.bStgPictureId = 0;
		}

		if (pCurInfo->stCallbackSettings.stMask.bCableDetect)
		{
			/* TODO: move this to a seperate function in bvdc_displaycabledetect_priv.c */
			uint32_t i;
			bool bDacStatusChange = false;
			for(i=0; i<BVDC_P_MAX_DACS; i++)
			{
				if(pCbData->aeDacConnectionState[i] != hDisplay->hVdc->aeDacStatus[i] &&
				   pCurInfo->aDacOutput[i] != BVDC_DacOutput_eUnused)
				{
					pCbData->aeDacConnectionState[i] = hDisplay->hVdc->aeDacStatus[i];
					bDacStatusChange = true;
				}
				/* if remove dacs => status unknown */
				if(pCbData->aeDacConnectionState[i] == BVDC_DacConnectionState_eConnected &&
				   pCurInfo->aDacOutput[i] == BVDC_DacOutput_eUnused)
				{
					pCbData->aeDacConnectionState[i] = BVDC_DacConnectionState_eUnknown;
					bDacStatusChange = true;
				}
			}
			if(bDacStatusChange || hDisplay->bCallbackInit)
			{
				pCbData->stMask.bCableDetect = 1;
			}
			else
			{
				pCbData->stMask.bCableDetect = 0;
			}
		}
		else
		{
			pCbData->stMask.bCableDetect = 0;
		}

		if(hDisplay->bCallbackInit)
			hDisplay->bCallbackInit = false;

		if (BVDC_P_CB_IS_DIRTY_isr(&pCbData->stMask))
		{
			pCurInfo->pfGenericCallback(pCurInfo->pvGenericParm1,
				pCurInfo->iGenericParm2, (void*)pCbData);
		}
	}

	/* If the dirty bit(s) is from user applied changes,
	 * Set the event to unblock the thread waiting for the
	 * "hApppliedDoneEvent".
	 */
	{
		BVDC_P_Display_DirtyBits stDirty = hDisplay->stCurInfo.stDirty;
		/* in case of STG resolution rampup, clear format switch dirty bit as instantly applied and to prevent timeout
		   if ramp duration is long. */
#if BVDC_P_SUPPORT_STG
		if(pCurInfo->ulResolutionRampCount) {
			stDirty.stBits.bTiming = BVDC_P_CLEAN;
		}
#endif
		if(hDisplay->bSetEventPending && !BVDC_P_IS_DIRTY(&stDirty))
		{
			BDBG_MSG(("BuildVsync Set AppliedDoneEvent"));
			hDisplay->bSetEventPending = false;
			BKNI_SetEvent_isr(hDisplay->hAppliedDoneEvent);
		}
	}
	BDBG_LEAVE(BVDC_P_Vec_BuildVsync_isr);
}

/*************************************************************************
 *  {secret}
 *  BVDC_P_Vec_BuildRul
 *  Build the necessary Vec blocks.
 **************************************************************************/
void BVDC_P_Vec_BuildRul_isr
	( BVDC_Display_Handle              hDisplay,
	  BVDC_P_ListInfo                 *pList,
	  BAVC_Polarity                    eFieldPolarity )
{
	uint32_t i, limit;
	BVDC_Display_ApplySetting    applySettingHandler;
    bool bBuildFormatRul =
		(BVDC_P_ItState_eNotActive  == hDisplay->eItState) ||
		(BVDC_P_ItState_eSwitchMode == hDisplay->eItState);
	BDBG_ENTER(BVDC_P_Vec_BuildRul_isr);

	BDBG_OBJECT_ASSERT(hDisplay, BVDC_DSP);

#if DCS_SUPPORT
	/* Experimental */
	BVDC_P_DCS_Check_isr (hDisplay, eFieldPolarity, 0, pList);
#endif


	/* if bTiming is dirty, IT state _must_ be either switch or inactive mode;
	 * bDacSetting dirty bit seems to force setting TG_CONFIG to start TG;
	 * if IT state is active already, clear previous bTiming dirty bit to
	 * prevent source isr building VEC format RUL which may lock up display
	 * state machine!
	 */
	if(bBuildFormatRul)
	{   /* enforce format RUL to be built */
		hDisplay->stCurInfo.stDirty.stBits.bTiming = BVDC_P_DIRTY;
		hDisplay->stCurInfo.stDirty.stBits.bDacSetting = BVDC_P_DIRTY;
		hDisplay->stCurInfo.stDirty.stBits.bAcp        = BVDC_P_DIRTY;
	}
	else if(!hDisplay->stStgChan.bEnable)
	{   /* Clear previous bTiming dirty bit here.
	     * The reasoning is:
	     *   Display state can only be set to eActive by display_isr after it assured
	     * the VEC format RUL being executed by checking the display format switch
	     * marker. There is no sense to rely on stored bTiming dirty bit here. Plus
	     * the stored previous bTiming dirty bit could mislead VEC to unnecessary format
	     * switch RUL and possible lockup.
	     */
		hDisplay->stPrevDirty.stBits.bTiming = BVDC_P_CLEAN;
	}

	/* We store a copy of last current dirty bits and clear it only if
	* the RUL for the new settngs get executed. Otherwise, we will
	 * re-build the RUL to apply the new settings again.
	 */
	if (BVDC_P_IS_DIRTY(&hDisplay->stPrevDirty))
	{
		if(!pList->bLastExecuted)
		{
			BVDC_P_OR_ALL_DIRTY(&(hDisplay->stCurInfo.stDirty), &(hDisplay->stPrevDirty));
		}
		BVDC_P_CLEAN_ALL_DIRTY(&(hDisplay->stPrevDirty));
	}


	if (BVDC_P_IS_DIRTY(&(hDisplay->stCurInfo.stDirty)))
	{
		BVDC_P_VEC_MSG(("Display%d: CurDirty = 0x%x", hDisplay->eId, hDisplay->stCurInfo.stDirty));
		BVDC_P_VEC_MSG(("\t bChan0            = %d", hDisplay->stCurInfo.stDirty.stBits.bChan0));
		BVDC_P_VEC_MSG(("\t bChan1            = %d", hDisplay->stCurInfo.stDirty.stBits.bChan1));
		BVDC_P_VEC_MSG(("\t bTiming           = %d", hDisplay->stCurInfo.stDirty.stBits.bTiming));
		BVDC_P_VEC_MSG(("\t bAcp              = %d", hDisplay->stCurInfo.stDirty.stBits.bAcp));
		BVDC_P_VEC_MSG(("\t b3DSetting        = %d", hDisplay->stCurInfo.stDirty.stBits.b3DSetting));
		BVDC_P_VEC_MSG(("\t bDacSetting       = %d", hDisplay->stCurInfo.stDirty.stBits.bDacSetting));
		BVDC_P_VEC_MSG(("\t bTimeBase         = %d", hDisplay->stCurInfo.stDirty.stBits.bTimeBase));
		BVDC_P_VEC_MSG(("\t bCallback         = %d", hDisplay->stCurInfo.stDirty.stBits.bCallback));
		BVDC_P_VEC_MSG(("\t bCallbackFunc     = %d", hDisplay->stCurInfo.stDirty.stBits.bCallbackFunc));
		BVDC_P_VEC_MSG(("\t bWidthTrim        = %d", hDisplay->stCurInfo.stDirty.stBits.bWidthTrim));
		BVDC_P_VEC_MSG(("\t bInputCS          = %d", hDisplay->stCurInfo.stDirty.stBits.bInputCS));
		BVDC_P_VEC_MSG(("\t bSrcFrameRate     = %d", hDisplay->stCurInfo.stDirty.stBits.bSrcFrameRate));
		BVDC_P_VEC_MSG(("\t bDropFrame        = %d", hDisplay->stCurInfo.stDirty.stBits.bDropFrame));
#if (BVDC_P_SUPPORT_RFM_OUTPUT != 0)
		BVDC_P_VEC_MSG(("\t bRfm              = %d", hDisplay->stCurInfo.stDirty.stBits.bRfm));
#endif
		BVDC_P_VEC_MSG(("\t bHdmiEnable       = %d", hDisplay->stCurInfo.stDirty.stBits.bHdmiEnable));
		BVDC_P_VEC_MSG(("\t bHdmiCsc          = %d", hDisplay->stCurInfo.stDirty.stBits.bHdmiCsc));
#if (BVDC_P_SUPPORT_ITU656_OUT != 0)
		BVDC_P_VEC_MSG(("\t b656Enable        = %d", hDisplay->stCurInfo.stDirty.stBits.b656Enable));
#endif
		BVDC_P_VEC_MSG(("\t bMpaaComp         = %d", hDisplay->stCurInfo.stDirty.stBits.bMpaaComp));
		BVDC_P_VEC_MSG(("\t bMpaaHdmi         = %d", hDisplay->stCurInfo.stDirty.stBits.bMpaaHdmi));

		BVDC_P_VEC_MSG(("\t bTimeStamp        = %d", hDisplay->stCurInfo.stDirty.stBits.bTimeStamp));
		BVDC_P_VEC_MSG(("\t bAlignment        = %d", hDisplay->stCurInfo.stDirty.stBits.bAlignment));
		BVDC_P_VEC_MSG(("\t bHdmiDroplines    = %d", hDisplay->stCurInfo.stDirty.stBits.bHdmiDroplines));
		BVDC_P_VEC_MSG(("\t bHdmiXvYcc        = %d", hDisplay->stCurInfo.stDirty.stBits.bHdmiXvYcc));
		BVDC_P_VEC_MSG(("\t bHdmiSyncOnly     = %d", hDisplay->stCurInfo.stDirty.stBits.bHdmiSyncOnly));
		BVDC_P_VEC_MSG(("\t bHdmiSettings     = %d", hDisplay->stCurInfo.stDirty.stBits.bHdmiSettings));
		BVDC_P_VEC_MSG(("\t bAspRatio         = %d", hDisplay->stCurInfo.stDirty.stBits.bAspRatio));

#if (BVDC_P_SUPPORT_STG != 0)
		BVDC_P_VEC_MSG(("\t bStg              = %d", hDisplay->stCurInfo.stDirty.stBits.bStgEnable));
#endif
		BVDC_P_VEC_MSG(("\t bVfFilters        = %d", hDisplay->stCurInfo.stDirty.stBits.bVfFilter));
		BVDC_P_VEC_MSG(("\t bOutputMute       = %d", hDisplay->stCurInfo.stDirty.stBits.bOutputMute));
		BVDC_P_VEC_MSG(("\t bMiscCtrl         = %d", hDisplay->stCurInfo.stDirty.stBits.bMiscCtrl));

		/* Store a copy of current dirty bits */
		hDisplay->stPrevDirty = hDisplay->stCurInfo.stDirty;

		limit = BVDC_P_MIN(
			BVDC_P_astDisplayEventHndlTblSize,
			BVDC_P_NUM_DIRTY_BITS(&(hDisplay->stNewInfo.stDirty)));
		for (i=0 ; i < limit ; i++)
		{
			if (BVDC_P_DISPLAY_IS_BIT_DIRTY(&(hDisplay->stCurInfo.stDirty), i))
			{
				/* Get copy handler from display event handling table */
				applySettingHandler = BVDC_P_astDisplayEventHndlTbl[i].applySettingHandler;

				/* Each event should at least have a apply setting handler */
				BDBG_ASSERT(applySettingHandler);

				/* Each handler needs to clear its own dirty bit in stCurInfo.stDirty.
				 * This is because some settings may take more than one vsync to finish.
				 * So the handler for such an event will have a state machine and clears
				 * the dirty bit only if all the necessary steps are completed.
				 */
				applySettingHandler(hDisplay, pList, eFieldPolarity);
			}
		}
	}

#if (BVDC_P_SUPPORT_STG)
	if(hDisplay->stCurInfo.bEnableStg && !bBuildFormatRul)
	{
		BVDC_P_ProgrameStgMBox_isr(hDisplay, pList, eFieldPolarity);
	}
#endif
	if (BVDC_P_ItState_eActive == hDisplay->eItState)
	{

		BVDC_P_Vec_BuildVsync_isr(hDisplay, pList, eFieldPolarity);

		/* Alignment */
		BVDC_P_Display_Alignment_isr(hDisplay, pList);
	}

#if DCS_SUPPORT
	/* Experimental */
	BVDC_P_DCS_Check_isr (hDisplay, eFieldPolarity, 1, pList);
#endif

	BDBG_LEAVE(BVDC_P_Vec_BuildRul_isr);
}


/* API for compositor to pass in source picture related info
 */
void  BVDC_P_Display_SetSourceInfo_isr
	( BVDC_Display_Handle              hDisplay,
	  const BVDC_P_Display_SrcInfo    *pSrcInfo )
{
	BDBG_OBJECT_ASSERT(hDisplay, BVDC_DSP);
	if (hDisplay->stCurInfo.bWidthTrimmed != pSrcInfo->bWidthTrimmed)
	{
		if ((VIDEO_FORMAT_IS_NTSC(hDisplay->stCurInfo.pFmtInfo->eVideoFmt) &&
			(hDisplay->stCurInfo.eMacrovisionType < BVDC_MacrovisionType_eTest01) &&
			 pSrcInfo->bWidthTrimmed && (!hDisplay->stCurInfo.bWidthTrimmed)) ||
			 (hDisplay->stCurInfo.bWidthTrimmed && (!pSrcInfo->bWidthTrimmed)))
		{
			/* Enable/Disble width trimmed mode.
			 */
			hDisplay->stCurInfo.bWidthTrimmed = pSrcInfo->bWidthTrimmed;
			hDisplay->stCurInfo.stDirty.stBits.bWidthTrim = BVDC_P_DIRTY;
			hDisplay->stCurInfo.stDirty.stBits.bTimeBase = BVDC_P_DIRTY;
		}
	}

	if (hDisplay->stCurInfo.eCmpColorSpace != pSrcInfo->eCmpColorSpace)
	{
		hDisplay->stNewInfo.eCmpColorSpace = pSrcInfo->eCmpColorSpace;
		hDisplay->stCurInfo.eCmpColorSpace = pSrcInfo->eCmpColorSpace;
		hDisplay->stCurInfo.stDirty.stBits.bInputCS = BVDC_P_DIRTY;
	}

	if (hDisplay->stCurInfo.bFullRate!= pSrcInfo->bFullRate)
	{
		hDisplay->stCurInfo.bFullRate = pSrcInfo->bFullRate;
		hDisplay->stCurInfo.stDirty.stBits.bSrcFrameRate = BVDC_P_DIRTY;
	}
}


#if !B_REFSW_MINIMAL
BERR_Code BVDC_Display_GetItUcodeInfo
	( BVDC_Display_Handle              hDisplay,
	  BVDC_Display_ItUcodeInfo        *pInfo )
{
	BREG_Handle hReg;
	uint32_t iOffset = 0; /* TODO: need to find offset for display */

	BDBG_ENTER(BVDC_Display_GetItUcodeInfo);

	BDBG_OBJECT_ASSERT(hDisplay, BVDC_DSP);

	hReg = hDisplay->hVdc->hRegister;

	pInfo->ulAnalogTimestamp =
		BREG_Read32 (
			hReg,
			BCHP_IT_0_MICRO_INSTRUCTIONi_ARRAY_BASE +
				(sizeof(uint32_t)*BVDC_P_RAM_TABLE_TIMESTAMP_IDX) +
				iOffset);
	pInfo->ulAnalogChecksum =
		BREG_Read32 (
			hReg,
			BCHP_IT_0_MICRO_INSTRUCTIONi_ARRAY_BASE +
				(sizeof(uint32_t)*BVDC_P_RAM_TABLE_CHECKSUM_IDX) +
				iOffset);
#if (BVDC_P_ORTHOGONAL_VEC_VER <= BVDC_P_ORTHOGONAL_VEC_VER_1)
	pInfo->ulI656Timestamp =
		BREG_Read32 (
			hReg,
			BCHP_DTRAM_0_DMC_INSTRUCTIONi_ARRAY_BASE +
				(sizeof(uint32_t)*BVDC_P_DTRAM_TABLE_TIMESTAMP_IDX));
	pInfo->ulI656Checksum =
		BREG_Read32 (
			hReg,
			BCHP_DTRAM_0_DMC_INSTRUCTIONi_ARRAY_BASE +
				(sizeof(uint32_t)*BVDC_P_DTRAM_TABLE_CHECKSUM_IDX));
	pInfo->ulDviTimestamp =
		BREG_Read32 (
			hReg,
			BCHP_DTRAM_0_DMC_INSTRUCTIONi_ARRAY_BASE +
				(sizeof(uint32_t)*BVDC_P_DTRAM_TABLE_SIZE) +
				(sizeof(uint32_t)*BVDC_P_DTRAM_TABLE_TIMESTAMP_IDX));
	pInfo->ulDviChecksum =
		BREG_Read32 (
			hReg,
			BCHP_DTRAM_0_DMC_INSTRUCTIONi_ARRAY_BASE +
			(sizeof(uint32_t)*BVDC_P_DTRAM_TABLE_SIZE) +
			(sizeof(uint32_t)*BVDC_P_DTRAM_TABLE_CHECKSUM_IDX));
#else
	pInfo->ulI656Timestamp =
		BREG_Read32 (
			hReg,
			BCHP_ITU656_DTG_0_DMC_INSTRUCTIONi_ARRAY_BASE +
				(sizeof(uint32_t)*BVDC_P_DTRAM_TABLE_TIMESTAMP_IDX));
	pInfo->ulI656Checksum =
		BREG_Read32 (
			hReg,
			BCHP_ITU656_DTG_0_DMC_INSTRUCTIONi_ARRAY_BASE +
				(sizeof(uint32_t)*BVDC_P_DTRAM_TABLE_CHECKSUM_IDX));
	pInfo->ulDviTimestamp =
		BREG_Read32 (
			hReg,
			BCHP_DVI_DTG_0_DMC_INSTRUCTIONi_ARRAY_BASE +
				(sizeof(uint32_t)*BVDC_P_DTRAM_TABLE_TIMESTAMP_IDX));
	pInfo->ulDviChecksum =
		BREG_Read32 (
			hReg,
			BCHP_DVI_DTG_0_DMC_INSTRUCTIONi_ARRAY_BASE +
			(sizeof(uint32_t)*BVDC_P_DTRAM_TABLE_CHECKSUM_IDX));
#endif

	BDBG_LEAVE(BVDC_Display_GetItUcodeInfo);
	return BERR_SUCCESS;
}
#endif

BERR_Code BVDC_P_Display_GetRasterLineNumber
	( BVDC_Display_Handle              hDisplay,
	  uint32_t                        *pulRasterLineNumber )
{
    BREG_Handle hReg;

	BDBG_OBJECT_ASSERT(hDisplay, BVDC_DSP);
    hReg = hDisplay->hVdc->hRegister;

    *pulRasterLineNumber = BREG_Read32(hReg, hDisplay->ulItLctrReg);

    return BERR_SUCCESS;
}

/***************************************************************************
 *
 * BVDC_P_Display_GetFieldPolarity_isr
 * Determines the field polarity based on the LCNTR register for a given
 * timing generator for non-STG displays; otherwise, just use eFieldPolarity.
 * The polarity is then stored in BRDC_Variable_0.
 *
 ***************************************************************************/
BERR_Code BVDC_P_Display_GetFieldPolarity_isr
	( BVDC_Display_Handle              hDisplay,
	  uint32_t                       **ppulRulCur,
	  BAVC_Polarity                    eFieldPolarity )
{
	uint32_t  *pulRulCur;

	/* init RUL buffer pointers */
	pulRulCur = *ppulRulCur;

    if (BVDC_P_DISPLAY_USED_STG(hDisplay->eMasterTg))
    {
        *pulRulCur++ = BRDC_OP_IMM_TO_VAR(BRDC_Variable_0);
        *pulRulCur++ = eFieldPolarity;
    }
    else
    {
        BSTD_UNUSED(eFieldPolarity);

        /* for interlaced format, polarity_record = (bot)? 0 : 1 */
        *pulRulCur++ = BRDC_OP_REG_TO_VAR(BRDC_Variable_0);
        *pulRulCur++ = BRDC_REGISTER(hDisplay->ulItLctrReg);
        *pulRulCur++ = BRDC_OP_VAR_AND_IMM_TO_VAR(BRDC_Variable_0, BRDC_Variable_1);
        *pulRulCur++ = ~BVDC_P_TRIGGER_LINE;
        *pulRulCur++ = BRDC_OP_COND_SKIP(BRDC_Variable_1);
        *pulRulCur++ = 4; /* if bottom (non-zero), skip 2 dwords */
        *pulRulCur++ = BRDC_OP_IMM_TO_VAR(BRDC_Variable_0);
        *pulRulCur++ = 0x0;
        *pulRulCur++ = BRDC_OP_SKIP();
        *pulRulCur++ = 2;
        *pulRulCur++ = BRDC_OP_IMM_TO_VAR(BRDC_Variable_0);
        *pulRulCur++ = 0x1;
     }

    /* reset RUL buffer pointer */
	*ppulRulCur = pulRulCur;

    return BERR_SUCCESS;
}

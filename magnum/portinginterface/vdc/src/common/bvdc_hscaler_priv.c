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
 *
 * Revision History:
 *
 * $brcm_Log: $
 *
 ***************************************************************************/
#include "bstd.h"
#include "bkni.h"
#include "bvdc.h"
#include "brdc.h"
#include "bvdc_hscaler_priv.h"
#include "bvdc_buffer_priv.h"
#include "bvdc_source_priv.h"
#include "bvdc_window_priv.h"
#include "bvdc_pep_priv.h"
#include "bvdc_vnet_priv.h"
#include "bvdc_mad_priv.h"

#if BVDC_P_SUPPORT_HSCL_MAD_HARD_WIRED
#include "bchp_hscl_0.h"

#ifdef BCHP_HSCL_1_REG_START
#include "bchp_hscl_1.h"
#endif

BDBG_MODULE(BVDC_HSCL);
BDBG_OBJECT_ID(BVDC_HSL);

/***************************************************************************
 * {private}
 *
 */
BERR_Code BVDC_P_Hscaler_Create
	( BVDC_P_Hscaler_Handle            *phHscaler,
	  BVDC_P_HscalerId                  eHscalerId,
	  BVDC_P_Resource_Handle            hResource,
	  BREG_Handle                       hReg
)
{
	BVDC_P_HscalerContext *pHscaler;

	BDBG_ENTER(BVDC_P_Hscaler_Create);

	BDBG_ASSERT(phHscaler);

	/* Use: to see messages */
	/* BDBG_SetModuleLevel("BVDC_HSCL", BDBG_eMsg); */

	/* The handle will be NULL if create fails. */
	*phHscaler = NULL;

	/* Alloc the context. */
	pHscaler = (BVDC_P_HscalerContext*)
		(BKNI_Malloc(sizeof(BVDC_P_HscalerContext)));
	if(!pHscaler)
	{
		return BERR_TRACE(BERR_OUT_OF_SYSTEM_MEMORY);
	}

	/* Clear out the context and set defaults. */
	BKNI_Memset((void*)pHscaler, 0x0, sizeof(BVDC_P_HscalerContext));
	BDBG_OBJECT_SET(pHscaler, BVDC_HSL);

	pHscaler->eId          = eHscalerId;
	pHscaler->hReg         = hReg;
	pHscaler->ulRegOffset  = 0;

	pHscaler->ulRegOffset = BVDC_P_HSCL_GET_REG_OFFSET(eHscalerId);


	/* Init to the default filter coeffficient tables. */
	BVDC_P_GetFirCoeffs_isr(&pHscaler->pHorzFirCoeffTbl, NULL);
	BVDC_P_GetChromaFirCoeffs_isr(&pHscaler->pChromaHorzFirCoeffTbl, NULL);

	/* All done. now return the new fresh context to user. */
	*phHscaler = (BVDC_P_Hscaler_Handle)pHscaler;
	BSTD_UNUSED(hResource);

	BDBG_LEAVE(BVDC_P_Hscaler_Create);
	return BERR_SUCCESS;
}


/***************************************************************************
 * {private}
 *
 */
void BVDC_P_Hscaler_Destroy
	( BVDC_P_Hscaler_Handle             hHscaler )
{
	BDBG_ENTER(BVDC_P_Hscaler_Destroy);
	BDBG_OBJECT_ASSERT(hHscaler, BVDC_HSL);

	BDBG_OBJECT_DESTROY(hHscaler, BVDC_HSL);
	/* Release context in system memory */
	BKNI_Free((void*)hHscaler);

	BDBG_LEAVE(BVDC_P_Hscaler_Destroy);
	return;
}


/***************************************************************************
 * {private}
 *
 */
void BVDC_P_Hscaler_Init_isr
	( BVDC_P_Hscaler_Handle            hHscaler )
{
	uint32_t  ulReg;
	uint32_t  ulTaps;

	BDBG_ENTER(BVDC_P_Hscaler_Init_isr);
	BDBG_OBJECT_ASSERT(hHscaler, BVDC_HSL);

	/* Clear out shadow registers. */
	BKNI_Memset_isr((void*)hHscaler->aulRegs, 0x0, sizeof(hHscaler->aulRegs));

	hHscaler->ulPrevSrcWidth = 0xffffffff;
	/* one value is enough to cause re-setinfo
	hHscaler->lPrevHsclCutLeft = 0xffffffff;
	hHscaler->ulPrevHsclCutWidth = 0xffffffff;
	hHscaler->ulPrevOutWidth = 0xffffffff;
	hHscaler->ulPrevSrcHeight = 0xffffffff;*/

#if (BVDC_P_SUPPORT_HSCL_VER >= BVDC_P_SUPPORT_HSCL_VER_2)
	ulReg = BREG_Read32_isr(hHscaler->hReg, BCHP_HSCL_0_HW_CONFIGURATION + hHscaler->ulRegOffset);

	hHscaler->bDeringing = BCHP_GET_FIELD_DATA(ulReg, HSCL_0_HW_CONFIGURATION, DERINGING) ? true : false;
	ulTaps = BCHP_GET_FIELD_DATA(ulReg, HSCL_0_HW_CONFIGURATION, HORIZ_TAPS);
	switch(ulTaps)
	{
		case BCHP_HSCL_0_HW_CONFIGURATION_HORIZ_TAPS_HORIZ_8_TAPS:
			hHscaler->ulHorzTaps = BVDC_P_CT_8_TAP;
			break;
		case BCHP_HSCL_0_HW_CONFIGURATION_HORIZ_TAPS_HORIZ_12_TAPS:
			hHscaler->ulHorzTaps = BVDC_P_CT_12_TAP;
			break;
		case BCHP_HSCL_0_HW_CONFIGURATION_HORIZ_TAPS_HORIZ_16_TAPS:
			hHscaler->ulHorzTaps = BVDC_P_CT_16_TAP;
			break;
		default: break;
	}

#else
	hHscaler->ulHorzTaps = BVDC_P_CT_8_TAP;
	hHscaler->bDeringing = true;

	BSTD_UNUSED(ulReg);
	BSTD_UNUSED(ulTaps);
#endif

#ifdef BCHP_HSCL_0_DERINGING
	if(hHscaler->bDeringing)
	{
		BVDC_P_HSCL_GET_REG_DATA(HSCL_0_DERINGING) &=  ~(
#if (BVDC_P_SUPPORT_HSCL_VER >= BVDC_P_SUPPORT_HSCL_VER_6)
			BCHP_MASK(HSCL_0_DERINGING, HORIZ_CHROMA_PASS_FIRST_RING ) |
			BCHP_MASK(HSCL_0_DERINGING, HORIZ_LUMA_PASS_FIRST_RING ) |
#endif
			BCHP_MASK(HSCL_0_DERINGING, HORIZ_CHROMA_DERINGING ) |
			BCHP_MASK(HSCL_0_DERINGING, HORIZ_LUMA_DERINGING ));

		BVDC_P_HSCL_GET_REG_DATA(HSCL_0_DERINGING) |=  (
#if (BVDC_P_SUPPORT_HSCL_VER >= BVDC_P_SUPPORT_HSCL_VER_6)
			BCHP_FIELD_ENUM(HSCL_0_DERINGING, HORIZ_CHROMA_PASS_FIRST_RING, ENABLE ) |
			BCHP_FIELD_ENUM(HSCL_0_DERINGING, HORIZ_LUMA_PASS_FIRST_RING, ENABLE ) |
#endif
			BCHP_FIELD_ENUM(HSCL_0_DERINGING, HORIZ_CHROMA_DERINGING, ON ) |
			BCHP_FIELD_ENUM(HSCL_0_DERINGING, HORIZ_LUMA_DERINGING,   ON ));
	}
#endif

	hHscaler->ulSrcHrzAlign  = 2;

	/* Initialize state. */
	hHscaler->bInitial = true;

	BDBG_LEAVE(BVDC_P_Hscaler_Init_isr);
	return;
}


/***************************************************************************
 * {private}
 *
 */
void BVDC_P_Hscaler_BuildRul_SrcInit_isr
	( BVDC_P_Hscaler_Handle            hHscaler,
	  BVDC_P_ListInfo                 *pList )
{
	BDBG_OBJECT_ASSERT(hHscaler, BVDC_HSL);

	if(hHscaler->ulUpdateAll)
	{
		hHscaler->ulUpdateAll--;
	/* optimize scaler mute RUL */
		BVDC_P_HSCL_BLOCK_WRITE_TO_RUL(HSCL_0_HORIZ_CONTROL, HSCL_0_DEST_PIC_SIZE, pList->pulCurrent);
#if (BVDC_P_SUPPORT_HSCL_VER >= BVDC_P_SUPPORT_HSCL_VER_5)
		BVDC_P_HSCL_BLOCK_WRITE_TO_RUL(HSCL_0_SRC_PIC_HORIZ_PAN_SCAN, HSCL_0_HORIZ_DEST_PIC_REGION_3_END, pList->pulCurrent);
		BVDC_P_HSCL_WRITE_TO_RUL(HSCL_0_VIDEO_3D_MODE, pList->pulCurrent);
#else
		BVDC_P_HSCL_BLOCK_WRITE_TO_RUL(HSCL_0_SRC_PIC_HORIZ_PAN_SCAN, HSCL_0_HORIZ_DEST_PIC_REGION_2_END, pList->pulCurrent);
#endif

#ifdef BCHP_HSCL_0_DERINGING
		if(hHscaler->bDeringing)
		{
			BVDC_P_HSCL_WRITE_TO_RUL(HSCL_0_DERINGING, pList->pulCurrent);
		}
#endif

#if (BVDC_P_SUPPORT_HSCL_VER == BVDC_P_SUPPORT_HSCL_VER_1)
		BVDC_P_HSCL_BLOCK_WRITE_TO_RUL(HSCL_0_HORIZ_FIR_COEFF_PHASE0_00_01, HSCL_0_HORIZ_FIR_CHROMA_COEFF_PHASE7_06_07, pList->pulCurrent);
#elif (BVDC_P_SUPPORT_HSCL_VER == BVDC_P_SUPPORT_HSCL_VER_2) || (BVDC_P_SUPPORT_HSCL_VER == BVDC_P_SUPPORT_HSCL_VER_4)
		BVDC_P_HSCL_BLOCK_WRITE_TO_RUL(HSCL_0_HORIZ_FIR_LUMA_COEFF_PHASE0_00_01, HSCL_0_HORIZ_FIR_CHROMA_COEFF_PHASE7_02_03, pList->pulCurrent);
#elif (BVDC_P_SUPPORT_HSCL_VER == BVDC_P_SUPPORT_HSCL_VER_3) || (BVDC_P_SUPPORT_HSCL_VER >= BVDC_P_SUPPORT_HSCL_VER_5)
		BVDC_P_HSCL_BLOCK_WRITE_TO_RUL(HSCL_0_HORIZ_FIR_LUMA_COEFF_PHASE0_00_01, HSCL_0_HORIZ_FIR_CHROMA_COEFF_PHASE7_04_05, pList->pulCurrent);
#endif
		BVDC_P_HSCL_WRITE_TO_RUL(HSCL_0_TOP_CONTROL, pList->pulCurrent);
	}
}


/***************************************************************************
 * {private}
 *
 */
static void BVDC_P_Hscaler_SetFirCoeff_isr
	( BVDC_P_Hscaler_Handle            hHscaler,
	  const uint32_t                  *pulHorzFirCoeff )
{
	int i;

	BDBG_OBJECT_ASSERT(hHscaler, BVDC_HSL);
	/* write horiz entries into registers */
	for(i = 0; (pulHorzFirCoeff) && (*pulHorzFirCoeff != BVDC_P_HSCL_LAST); i++)
	{
#if (BVDC_P_SUPPORT_HSCL_VER == BVDC_P_SUPPORT_HSCL_VER_1)
		hHscaler->aulRegs[BVDC_P_HSCL_GET_REG_IDX(HSCL_0_HORIZ_FIR_COEFF_PHASE0_00_01) + i] =
			*pulHorzFirCoeff;
#else
		hHscaler->aulRegs[BVDC_P_HSCL_GET_REG_IDX(HSCL_0_HORIZ_FIR_LUMA_COEFF_PHASE0_00_01) + i] =
			*pulHorzFirCoeff;
#endif
		pulHorzFirCoeff++;
	}
}


/***************************************************************************
 * {private}
 *
 */
static void BVDC_P_Hscaler_SetChromaFirCoeff_isr
	( BVDC_P_Hscaler_Handle            hHscaler,
	  const uint32_t                  *pulHorzFirCoeff )
{
	int i;

	BDBG_OBJECT_ASSERT(hHscaler, BVDC_HSL);
	/* write 32 hor entries into registers */
	for(i = 0; (pulHorzFirCoeff) && (*pulHorzFirCoeff != BVDC_P_HSCL_LAST); i++)
	{
		hHscaler->aulRegs[BVDC_P_HSCL_GET_REG_IDX(HSCL_0_HORIZ_FIR_CHROMA_COEFF_PHASE0_00_01) + i] =
			*pulHorzFirCoeff;
		pulHorzFirCoeff++;
	}
}


/***************************************************************************
 * {private}
 *
 * The following notes illustrate the capabilities of the hscaler.  It
 * mainly shows different modes scaler operates to achieve the desire
 * scaling ratio with the best quality.
 *
 * Sx = in/out.  For example src=1920 dst=720 then Sx = 1920/720 or 2.66.
 * Hence this is what Sx means:
 *   Sx >  1 Scale down
 *   Sx <  1 Scale up
 *   Sx == 1 Unity.
 *
 * Actuall Sx tells how much we're scaling down.  For example
 * Sx = 4 means we're scaling down 4 times.
 *
 * There is no hard-wired filter in HSCL, so Sx is the value that goes into
 * horizontal FIR ratio register.
 *
 * Sx must be [32.0, 0.125].
 *
 *
 * [[ Conclusion ]]
 *  With the above information the theoretical scaling capacities are:
 *
 *  Sx = 32:1 to 1:32
 */
void BVDC_P_Hscaler_SetInfo_isr
	( BVDC_P_Hscaler_Handle            hHscaler,
	  BVDC_Window_Handle               hWindow,
	  const BVDC_P_PictureNodePtr      pPicture )
{
	uint32_t ulSrcHSize;               /* really scaled src width in pixel unit */
	uint32_t ulDstHSize;               /* Dst width in pixel unit */
	uint32_t ulDstVSize;               /* Dst height, in row unit */
	uint32_t ulAlgnSrcHSize;           /* src width into the 1st one of half band or FIR, pixel unit */
	uint32_t ulBvbInHSize;             /* input bvb width in pixel unit */
	uint32_t ulPicOffsetLeft = 0;      /* horizontal Pan/Scan part cut by PIC_OFFSET, pixel unit */
#if (BVDC_P_SUPPORT_HSCL_VER >= BVDC_P_SUPPORT_HSCL_VER_6)
	uint32_t ulPicOffsetLeft_R = 0;    /* horizontal Pan/Scan part cut by PIC_OFFSET_R, pixel unit */
#endif
	uint32_t ulPanScanLeft;            /* horizontal Pan/Scan vector in S11.6 format */
	const BVDC_P_FirCoeffTbl *pHorzFirCoeff;
	uint32_t ulNrmHrzStep;              /* Total horizontal src step per dest pixel, U11.21 */
	uint32_t ulFirHrzStep = 0;          /* FIR hrz src step per dest pixel, HW reg fmt, for coeff select */
	int32_t  lHrzPhsAccInit = 0;
	uint32_t ulMaxX;
	BVDC_P_Rect  *pHsclIn, *pHsclOut;

	BDBG_ENTER(BVDC_P_Hscaler_SetInfo_isr);
	BDBG_OBJECT_ASSERT(hHscaler, BVDC_HSL);
	BDBG_OBJECT_ASSERT(hWindow, BVDC_WIN);
	BDBG_OBJECT_ASSERT(hWindow->stCurInfo.hSource, BVDC_SRC);
	pHsclIn = pPicture->pHsclIn;
	pHsclOut = pPicture->pHsclOut;


	ulDstVSize = pHsclOut->ulHeight >> (BAVC_Polarity_eFrame!=pPicture->eSrcPolarity);
	/* any following info changed -> re-calculate SCL settings */
	if((hHscaler->ulPrevSrcWidth != pHsclIn->ulWidth) ||
	   (hHscaler->lPrevHsclCutLeft != pPicture->lHsclCutLeft) ||
	   (hHscaler->lPrevHsclCutLeft_R != pPicture->lHsclCutLeft_R) ||
	   (hHscaler->ulPrevHsclCutWidth != pPicture->ulHsclCutWidth) ||
	   (hHscaler->ulPrevOutWidth != pHsclOut->ulWidth) ||
	   (hHscaler->ulPrevSrcHeight != ulDstVSize) ||  /* no vrt scl */
#if (BVDC_P_SUPPORT_3D_VIDEO)
		(pPicture->eSrcOrientation != hHscaler->ePrevSrcOrientation)    ||
		(pPicture->eDispOrientation  != hHscaler->ePrevDispOrientation)   ||
#endif
	   (hWindow->stCurInfo.stCtIndex.ulHsclHorzLuma != hHscaler->ulPrevCtIndexLuma) ||
	   (hWindow->stCurInfo.stCtIndex.ulHsclHorzChroma != hHscaler->ulPrevCtIndexChroma) ||
	   (hWindow->stCurInfo.hSource->stCurInfo.eCtInputType != hHscaler->ePrevCtInputType) ||
	   !BVDC_P_HSCL_COMPARE_FIELD_DATA(HSCL_0_ENABLE, SCALER_ENABLE, 1) ||
	   (hHscaler->bChannelChange != pPicture->bChannelChange))
	{
		/* for next "dirty" check */
		hHscaler->ulPrevSrcWidth = pHsclIn->ulWidth;
		hHscaler->lPrevHsclCutLeft = pPicture->lHsclCutLeft;
		hHscaler->lPrevHsclCutLeft_R = pPicture->lHsclCutLeft_R;
		hHscaler->ulPrevHsclCutWidth = pPicture->ulHsclCutWidth;
		hHscaler->ulPrevOutWidth = pHsclOut->ulWidth;
		hHscaler->ulPrevSrcHeight = pHsclIn->ulHeight >> (BAVC_Polarity_eFrame!=pPicture->eSrcPolarity);
		hHscaler->ulPrevCtIndexLuma = hWindow->stCurInfo.stCtIndex.ulHsclHorzLuma;
		hHscaler->ulPrevCtIndexChroma = hWindow->stCurInfo.stCtIndex.ulHsclHorzChroma;
		hHscaler->ePrevCtInputType = hWindow->stCurInfo.hSource->stCurInfo.eCtInputType;

		hHscaler->ePrevSrcOrientation  = pPicture->eSrcOrientation;
		hHscaler->ePrevDispOrientation = pPicture->eDispOrientation;
		hHscaler->bChannelChange = pPicture->bChannelChange;

		hHscaler->ulUpdateAll = BVDC_P_RUL_UPDATE_THRESHOLD;
		/* -----------------------------------------------------------------------
		 * 1). Init some regitsers first, they might be modified later basing on
		 * specific conditions
		 */

		/* scaler panscan will be combined with init phase */
		BVDC_P_HSCL_GET_REG_DATA(HSCL_0_SRC_PIC_HORIZ_PAN_SCAN) &= ~(
			BCHP_MASK(HSCL_0_SRC_PIC_HORIZ_PAN_SCAN, OFFSET));

		/* Always re-enable after set info. */
		/* Horizontal scaler settings (and top control)!  Choose scaling order,
		 * and how much to decimate data. */
#if (BVDC_P_SUPPORT_HSCL_VER >= BVDC_P_SUPPORT_HSCL_VER_3)
#if (BVDC_P_SUPPORT_HSCL_VER >= BVDC_P_SUPPORT_HSCL_VER_7)
		BVDC_P_HSCL_GET_REG_DATA(HSCL_0_TOP_CONTROL) =
			BCHP_FIELD_ENUM(HSCL_0_TOP_CONTROL, ENABLE_CTRL,  ENABLE_BY_PICTURE);
#else
		BVDC_P_HSCL_GET_REG_DATA(HSCL_0_TOP_CONTROL) =	(
			BCHP_FIELD_ENUM(HSCL_0_TOP_CONTROL, UPDATE_SEL,   UPDATE_BY_PICTURE) |
			BCHP_FIELD_ENUM(HSCL_0_TOP_CONTROL, ENABLE_CTRL,  ENABLE_BY_PICTURE));
#endif
#else
		BVDC_P_HSCL_GET_REG_DATA(HSCL_0_TOP_CONTROL) =  (
			BCHP_FIELD_ENUM(HSCL_0_TOP_CONTROL, UPDATE_SEL,   UPDATE_BY_PICTURE) |
			BCHP_FIELD_ENUM(HSCL_0_TOP_CONTROL, ENABLE_CTRL,  ENABLE_BY_PICTURE));
#endif

		BVDC_P_HSCL_GET_REG_DATA(HSCL_0_ENABLE) =
			BCHP_FIELD_ENUM(HSCL_0_ENABLE, SCALER_ENABLE, ON);

		BVDC_P_HSCL_GET_REG_DATA(HSCL_0_HORIZ_CONTROL) &= ~(
			BCHP_MASK(HSCL_0_HORIZ_CONTROL, FIR_ENABLE          ) |
			BCHP_MASK(HSCL_0_HORIZ_CONTROL, MASK_HSCL_LONG_LINE ) |
			BCHP_MASK(HSCL_0_HORIZ_CONTROL, MASK_HSCL_SHORT_LINE) |
			BCHP_MASK(HSCL_0_HORIZ_CONTROL, STALL_DRAIN_ENABLE  ));

		BVDC_P_HSCL_GET_REG_DATA(HSCL_0_HORIZ_CONTROL) |=  (
			(((1 << BVDC_P_NRM_SRC_STEP_F_BITS) == pPicture->ulHsclNrmHrzSrcStep)?
			 BCHP_FIELD_ENUM(HSCL_0_HORIZ_CONTROL, FIR_ENABLE,          OFF) :
			 BCHP_FIELD_ENUM(HSCL_0_HORIZ_CONTROL, FIR_ENABLE,          ON ))|
			BCHP_FIELD_ENUM(HSCL_0_HORIZ_CONTROL, MASK_HSCL_LONG_LINE,  ON ) |
			BCHP_FIELD_ENUM(HSCL_0_HORIZ_CONTROL, MASK_HSCL_SHORT_LINE, ON ) |
			BCHP_FIELD_ENUM(HSCL_0_HORIZ_CONTROL, STALL_DRAIN_ENABLE,   OFF));

#if (BVDC_P_SUPPORT_HSCL_VER >= BVDC_P_SUPPORT_HSCL_VER_5)
		BVDC_P_HSCL_GET_REG_DATA(HSCL_0_VIDEO_3D_MODE) =
			BCHP_FIELD_DATA(HSCL_0_VIDEO_3D_MODE, BVB_VIDEO,
			BVDC_P_VNET_USED_HSCL_AT_WRITER(pPicture->stVnetMode) ?
			pPicture->eSrcOrientation : pPicture->eDispOrientation);
#endif

		/* -----------------------------------------------------------------------
		 * 2). Need to calculate the horizontal scaling factors before src width
		 * alignment and init phase can be decided
		 */

		/* output size */
		ulDstHSize = pHsclOut->ulWidth;

		BVDC_P_HSCL_GET_REG_DATA(HSCL_0_DEST_PIC_SIZE) &= ~(
			BCHP_MASK(HSCL_0_DEST_PIC_SIZE, HSIZE) |
			BCHP_MASK(HSCL_0_DEST_PIC_SIZE, VSIZE));
		BVDC_P_HSCL_GET_REG_DATA(HSCL_0_DEST_PIC_SIZE) |=  (
			BCHP_FIELD_DATA(HSCL_0_DEST_PIC_SIZE, HSIZE, ulDstHSize) |
			BCHP_FIELD_DATA(HSCL_0_DEST_PIC_SIZE, VSIZE, ulDstVSize));

		/* the src size really scaled and output */
		ulSrcHSize = pPicture->ulHsclCutWidth;

		/* pan scan:  left format S11.6, top format S11.14 */
		ulPanScanLeft = pPicture->lHsclCutLeft;

		/* separate the amount cut by HSCL_0_PIC_OFFSET and FIR_LUMA_SRC_PIC_OFFSET */
		ulPicOffsetLeft = (ulPanScanLeft >> 6) & ~(hHscaler->ulSrcHrzAlign - 1);
		ulPanScanLeft -= (ulPicOffsetLeft << 6);

#if (BVDC_P_SUPPORT_HSCL_VER >= BVDC_P_SUPPORT_HSCL_VER_6)
		ulPicOffsetLeft_R = (pPicture->lHsclCutLeft_R >> 6) & ~(hHscaler->ulSrcHrzAlign - 1);
#endif

		/* the src size that get into the first scaler sub-modules (e.g. HW half-band
		 * filter if it is scaled down a lot): it includes the FIR_LUMA_SRC_PIC_OFFSET,
		 * but not the HSCL_0_PIC_OFFSET, it has to be rounded-up for alignment */
		ulMaxX = ulPanScanLeft + (ulSrcHSize << 6);
		ulAlgnSrcHSize = ((ulMaxX + ((1<< 6) - 1)) >>  6);
		ulAlgnSrcHSize = BVDC_P_ALIGN_UP(ulAlgnSrcHSize, hHscaler->ulSrcHrzAlign);

		/* Init the input/output horizontal size of FIRs */
		/*ulFirSrcHSize = ulSrcHSize;*/

		/* HSCL only do linear scaling */
		/*if(0 == pPicture->ulNonlinearSclOutWidth)*/
		{
			/* Horizantal step HW reg uses U5.17 in older arch, U5.26 after smooth non-linear is
			 * suported. Since CPU uses 32 bits int, calc step with 26 bits frac needs special
			 * handling (see the delta calcu in the case of nonlinear scaling). It is the step
			 * delta and internal step accum reg, not the initial step value, that really need 26
			 * frac bits, therefore we use 21 bits for trade off */
			ulNrmHrzStep = pPicture->ulHsclNrmHrzSrcStep;    /* U11.21 */
			ulFirHrzStep = /*ulHrzStep =*/ BVDC_P_SCL_H_STEP_NRM_TO_SPEC(ulNrmHrzStep); /* U4.17, U5.17, U5.26 */

#if (BVDC_P_SUPPORT_SCL_VER >= BVDC_P_SUPPORT_SCL_VER_4)
			if (((1<<BVDC_P_NRM_SRC_STEP_F_BITS) == ulNrmHrzStep) &&
				(0 == ulPanScanLeft) && (ulSrcHSize == ulDstHSize))
			{
				/* unity scale and no phase shift, turn off FIR for accuracy */
				BVDC_P_HSCL_GET_REG_DATA(HSCL_0_HORIZ_CONTROL) &= ~(
					BCHP_MASK(HSCL_0_HORIZ_CONTROL, FIR_ENABLE));
				BVDC_P_HSCL_GET_REG_DATA(HSCL_0_HORIZ_CONTROL) |=  (
					BCHP_FIELD_ENUM(HSCL_0_HORIZ_CONTROL, FIR_ENABLE,  OFF));
			}
#endif
			/*ulFirHrzStepInit = ulFirHrzStep;*/

			/* set step size and region_0 end */
			BVDC_P_HSCL_SET_HORZ_RATIO(ulFirHrzStep);
			BVDC_P_HSCL_SET_HORZ_REGION02(0, ulDstHSize, 0)
		}

		/* -----------------------------------------------------------------------
		 * 3). Now we can set src size, offset and bvb size
		 */
		ulBvbInHSize = pHsclIn->ulWidth;

		/* in older chips, align ulBvbInHSize up if ulAlgnSrcHSize has been aligned
		 * up due to half-band.
		 * note: align ulBvbInHSize up might cause "short line" error, that is OK
		 * and scl input module would patch. If we don't align up, SCL might hang */
		if (1 != hHscaler->ulSrcHrzAlign)
			ulBvbInHSize  = BVDC_P_MAX(ulBvbInHSize, ulAlgnSrcHSize + ulPicOffsetLeft);
		else
			ulAlgnSrcHSize = BVDC_P_MIN(ulAlgnSrcHSize, ulBvbInHSize - ulPicOffsetLeft);

		/* without this we might see flash when we move up with dst cut if MAD is disabled? */
		/*ulBvbInVSize  = BVDC_P_MAX(ulBvbInVSize, ulAlgnSrcVSize + ulPicOffsetTop);*/

		BVDC_P_HSCL_GET_REG_DATA(HSCL_0_PIC_OFFSET) &= ~(
			BCHP_MASK(HSCL_0_PIC_OFFSET, HSIZE) |
			BCHP_MASK(HSCL_0_PIC_OFFSET, VSIZE));
		BVDC_P_HSCL_GET_REG_DATA(HSCL_0_PIC_OFFSET) |=  (
			BCHP_FIELD_DATA(HSCL_0_PIC_OFFSET, HSIZE, ulPicOffsetLeft) |
			BCHP_FIELD_DATA(HSCL_0_PIC_OFFSET, VSIZE, 0));

#if (BVDC_P_SUPPORT_HSCL_VER >= BVDC_P_SUPPORT_HSCL_VER_6)
		BVDC_P_HSCL_GET_REG_DATA(HSCL_0_PIC_OFFSET_R) &= ~(
			BCHP_MASK(HSCL_0_PIC_OFFSET_R, ENABLE) |
			BCHP_MASK(HSCL_0_PIC_OFFSET_R, HSIZE));
		BVDC_P_HSCL_GET_REG_DATA(HSCL_0_PIC_OFFSET_R) |=  (
			BCHP_FIELD_DATA(HSCL_0_PIC_OFFSET_R, ENABLE, (ulPicOffsetLeft != ulPicOffsetLeft_R)) |
			BCHP_FIELD_DATA(HSCL_0_PIC_OFFSET_R, HSIZE, ulPicOffsetLeft_R));
#endif

		BVDC_P_HSCL_GET_REG_DATA(HSCL_0_BVB_IN_SIZE) &= ~(
			BCHP_MASK(HSCL_0_BVB_IN_SIZE, HSIZE) |
			BCHP_MASK(HSCL_0_BVB_IN_SIZE, VSIZE));
		BVDC_P_HSCL_GET_REG_DATA(HSCL_0_BVB_IN_SIZE) |=  (
			BCHP_FIELD_DATA(HSCL_0_BVB_IN_SIZE, HSIZE, ulBvbInHSize) |
			BCHP_FIELD_DATA(HSCL_0_BVB_IN_SIZE, VSIZE, ulDstVSize));

		/* SRC_PIC_SIZE should include FIR_LUMA_SRC_PIC_OFFSET and align */
		BVDC_P_HSCL_GET_REG_DATA(HSCL_0_SRC_PIC_SIZE) &= ~(
			BCHP_MASK(HSCL_0_SRC_PIC_SIZE, HSIZE) |
			BCHP_MASK(HSCL_0_SRC_PIC_SIZE, VSIZE));
		BVDC_P_HSCL_GET_REG_DATA(HSCL_0_SRC_PIC_SIZE) |=  (
			BCHP_FIELD_DATA(HSCL_0_SRC_PIC_SIZE, HSIZE, ulAlgnSrcHSize) |
			BCHP_FIELD_DATA(HSCL_0_SRC_PIC_SIZE, VSIZE, ulDstVSize));

		/* -----------------------------------------------------------------------
		 * 4). set coeffs for both horizontal
		 */
		pHorzFirCoeff = BVDC_P_SelectFirCoeff_isr(hHscaler->pHorzFirCoeffTbl,
			hWindow->stCurInfo.stCtIndex.ulHsclHorzLuma,
			hWindow->stCurInfo.hSource->stCurInfo.eCtInputType,
			BVDC_P_CtOutput_eAny,
			pPicture->PicComRulInfo.eSrcOrigPolarity, ulFirHrzStep,
			hHscaler->ulHorzTaps, ulSrcHSize, ulDstHSize);
		BDBG_MSG(("Luma H Coeffs  : %s", pHorzFirCoeff->pchName));
		BVDC_P_Hscaler_SetFirCoeff_isr(hHscaler, pHorzFirCoeff->pulCoeffs);

		pHorzFirCoeff = BVDC_P_SelectFirCoeff_isr(hHscaler->pChromaHorzFirCoeffTbl,
			hWindow->stCurInfo.stCtIndex.ulHsclHorzChroma,
			hWindow->stCurInfo.hSource->stCurInfo.eCtInputType,
			BVDC_P_CtOutput_eAny,
			pPicture->PicComRulInfo.eSrcOrigPolarity, ulFirHrzStep,
			hHscaler->ulHorzTaps, ulSrcHSize, ulDstHSize);
		BDBG_MSG(("Chroma H Coeffs: %s", pHorzFirCoeff->pchName));
		BVDC_P_Hscaler_SetChromaFirCoeff_isr(
			hHscaler, pHorzFirCoeff->pulCoeffs);

		/* -----------------------------------------------------------------------
		 * 5). set init phase for horizontal
		 */
		/* Compute the phase accumulate intial value in S11.6 or S5.26 */
		lHrzPhsAccInit = BVDC_P_FIXED_A_MINUS_FIXED_B(
			BVDC_P_H_INIT_PHASE_RATIO_ADJ(ulFirHrzStep) / 2,
			BVDC_P_H_INIT_PHASE_0_POINT_5);

		BVDC_P_HSCL_GET_REG_DATA(HSCL_0_HORIZ_FIR_LUMA_SRC_PIC_OFFSET) &= ~(
			BCHP_MASK(HSCL_0_HORIZ_FIR_LUMA_SRC_PIC_OFFSET, VALUE));
		BVDC_P_HSCL_GET_REG_DATA(HSCL_0_HORIZ_FIR_CHROMA_SRC_PIC_OFFSET) &= ~(
			BCHP_MASK(HSCL_0_HORIZ_FIR_CHROMA_SRC_PIC_OFFSET, VALUE));
		BVDC_P_HSCL_GET_REG_DATA(HSCL_0_HORIZ_FIR_LUMA_SRC_PIC_OFFSET) |=  (
			BCHP_FIELD_DATA(HSCL_0_HORIZ_FIR_LUMA_SRC_PIC_OFFSET, VALUE,
			ulPanScanLeft));
		BVDC_P_HSCL_GET_REG_DATA(HSCL_0_HORIZ_FIR_CHROMA_SRC_PIC_OFFSET) |=  (
			BCHP_FIELD_DATA(HSCL_0_HORIZ_FIR_CHROMA_SRC_PIC_OFFSET, VALUE,
			ulPanScanLeft));

		BVDC_P_HSCL_GET_REG_DATA(HSCL_0_HORIZ_FIR_INIT_PHASE_ACC) &= ~(
			BCHP_MASK(HSCL_0_HORIZ_FIR_INIT_PHASE_ACC, SIZE));
		BVDC_P_HSCL_GET_REG_DATA(HSCL_0_HORIZ_FIR_INIT_PHASE_ACC) |=  (
			BCHP_FIELD_DATA(HSCL_0_HORIZ_FIR_INIT_PHASE_ACC, SIZE,
			lHrzPhsAccInit));

#if (BVDC_P_SUPPORT_HSCL_VER >= BVDC_P_SUPPORT_HSCL_VER_5)
		BVDC_P_HSCL_GET_REG_DATA(HSCL_0_HORIZ_FIR_INIT_PHASE_ACC_R) &= ~(
			BCHP_MASK(HSCL_0_HORIZ_FIR_INIT_PHASE_ACC_R, SIZE));
		BVDC_P_HSCL_GET_REG_DATA(HSCL_0_HORIZ_FIR_INIT_PHASE_ACC_R) |=  (
			BCHP_FIELD_DATA(HSCL_0_HORIZ_FIR_INIT_PHASE_ACC_R, SIZE,
			lHrzPhsAccInit));
#endif
	}

	/* Printing out ratio in float format would be nice, but PI
	 * code does permit float. */
	if(BVDC_P_RUL_UPDATE_THRESHOLD == hHscaler->ulUpdateAll)
	{
		BDBG_MSG(("-------------------------"));
		BDBG_MSG(("Hscaler[%d]         : %dx%d to %dx%d", hHscaler->eId,
			pHsclIn->ulWidth,  pHsclIn->ulHeight,
			pHsclOut->ulWidth, pHsclOut->ulHeight));
		BDBG_MSG(("Hscaler[%d]'clip    : left %d, width %d, left_R %d",
				hHscaler->eId, pPicture->lHsclCutLeft, pPicture->ulHsclCutWidth,
				pPicture->lHsclCutLeft_R));
		BDBG_MSG(("ulFirHrzStep      : %-8x", ulFirHrzStep));
		BDBG_MSG(("PIC_OFFSET_LEFT   : %-8x", ulPicOffsetLeft));
		BDBG_MSG(("H_InitPhase       : %-8x", lHrzPhsAccInit));

	}

	BDBG_LEAVE(BVDC_P_Hscaler_SetInfo_isr);
	return;
}

/***************************************************************************
 * {private}
 *
 */
void BVDC_P_Hscaler_SetEnable_isr
	( BVDC_P_Hscaler_Handle            hHscaler,
	  bool                             bEnable,
	  BVDC_P_ListInfo                  *pList)
{
	BDBG_OBJECT_ASSERT(hHscaler, BVDC_HSL);

	/* Turn on/off the scaler. */
	BVDC_P_HSCL_GET_REG_DATA(HSCL_0_ENABLE) &= ~(
		BCHP_MASK(HSCL_0_ENABLE, SCALER_ENABLE));

	BVDC_P_HSCL_GET_REG_DATA(HSCL_0_ENABLE) |=  (bEnable
		? BCHP_FIELD_ENUM(HSCL_0_ENABLE, SCALER_ENABLE, ON)
		: BCHP_FIELD_ENUM(HSCL_0_ENABLE, SCALER_ENABLE, OFF));

	BVDC_P_HSCL_WRITE_TO_RUL(HSCL_0_ENABLE, pList->pulCurrent);

	return;
}
#else
BERR_Code BVDC_P_Hscaler_Create
	( BVDC_P_Hscaler_Handle           *phHscaler,
	  BVDC_P_HscalerId                 eHscalerId,
	  BVDC_P_Resource_Handle           hResource,
	  BREG_Handle                      hReg )
{
	BSTD_UNUSED(phHscaler);
	BSTD_UNUSED(eHscalerId);
	BSTD_UNUSED(hResource);
	BSTD_UNUSED(hReg);
	return BERR_SUCCESS;
}

void BVDC_P_Hscaler_Destroy
	( BVDC_P_Hscaler_Handle            hHscaler )
{
	BSTD_UNUSED(hHscaler);
	return;
}

void BVDC_P_Hscaler_Init_isr
	( BVDC_P_Hscaler_Handle            hHscaler )
{
	BSTD_UNUSED(hHscaler);
	return;
}

void BVDC_P_Hscaler_BuildRul_SrcInit_isr
	( BVDC_P_Hscaler_Handle            hHscaler,
	  BVDC_P_ListInfo                 *pList )
{
	BSTD_UNUSED(hHscaler);
	BSTD_UNUSED(pList);
}

void BVDC_P_Hscaler_SetInfo_isr
	( BVDC_P_Hscaler_Handle            hHscaler,
	  BVDC_Window_Handle               hWindow,
	  const BVDC_P_PictureNodePtr      pPicture )
{
	BSTD_UNUSED(hHscaler);
	BSTD_UNUSED(hWindow);
	BSTD_UNUSED(pPicture);
	return;
}

void BVDC_P_Hscaler_SetEnable_isr
	( BVDC_P_Hscaler_Handle            hHscaler,
	  bool                             bEnable,
	  BVDC_P_ListInfo                  *pList)

{
	BSTD_UNUSED(hHscaler);
	BSTD_UNUSED(bEnable);
	BSTD_UNUSED(pList);
	return;
}
#endif  /* #if (BVDC_P_SUPPORT_HSCL) || (BVDC_P_SUPPORT_HSCL_MAD_HARD_WIRED) */

/* End of file. */

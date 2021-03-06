/***************************************************************************
*     Copyright (c) 2003-2013, Broadcom Corporation
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
* Module Description: Framework initialization header file
*
* Revision History:
*
* $brcm_Log: $
*
***************************************************************************/

#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "bstd.h"                /* standard types */
#include "bdbg.h"                /* Dbglib */
#include "bkni.h"                /* malloc */

#include "framework.h"

#include "brdc.h"
#include "bvdc.h"
#include "framework_board.h"
#include "framework_board_bvdc.h"

/* graphics */
#include "bavc.h"
#include "bvdc.h"
#include "bsur.h"
#include "bpxl.h"

BDBG_MODULE(SIMPLE_VDC);

/**************************************************************************/
#define __DISP_NAME(d)  #d
#define DISP_NAME(d)  __DISP_NAME(d)
#define DISP_DUAL    1
#define DISP_1       BVDC_DisplayId_eDisplay1
#define CMP_1        BVDC_CompositorId_eCompositor1

#define BTST_P_GFX_WIDTH             (300)
#define BTST_P_GFX_HEIGHT            (200)

#define TestError(e, str)	{\
	err = e;\
	if (err != BERR_SUCCESS)\
	{\
	BDBG_ERR(( str". %s: %d %x", __FILE__,__LINE__, e ));\
		goto Done;\
	}\
}

/**************************************************************************/
static void TestDisplayGfx(
	BMMA_Heap_Handle        hMmaHeap,
	BVDC_Handle             hVdc,
	BAVC_SourceId           eSrcId,
	BVDC_Compositor_Handle  hCompositor,
	BFMT_VideoInfo       *  pVideoFmtInfo
)
{
	BVDC_Window_Handle hGfxWin;
	BVDC_Source_Handle hGfxSrc;
	BPXL_Plane stSurface;
	BAVC_Gfx_Picture stGfxPic;
	uint8_t *pImage;
	BERR_Code err;

	TestError( BVDC_Source_Create(hVdc, &hGfxSrc, eSrcId, NULL),
			   "BVDC_Source_Create");

	BPXL_Plane_Init(&stSurface, BTST_P_GFX_WIDTH, BTST_P_GFX_HEIGHT, BPXL_eA8_R8_G8_B8);
	TestError( BPXL_Plane_AllocateBuffers(&stSurface, hMmaHeap),
			   "BPXL_Plane_AllocateBuffers: out of memory" );
	pImage = (uint8_t *)BMMA_Lock(stSurface.hPixels);
	BKNI_Memset((void*)pImage, 0xFF, stSurface.ulBufSize);
	BMMA_FlushCache(stSurface.hPixels, pImage, stSurface.ulBufSize);
	BMMA_Unlock(stSurface.hPixels, pImage);

	BKNI_Memset((void*)&stGfxPic, 0x0, sizeof(BAVC_Gfx_Picture));
	stGfxPic.pSurface = &stSurface;
	stGfxPic.eInOrientation = BFMT_Orientation_e2D;
	TestError( BVDC_Source_SetSurface (hGfxSrc, &stGfxPic),
			   "BVDC_Source_SetSurface" );

	TestError( BVDC_Window_Create(hCompositor, &hGfxWin, BVDC_WindowId_eGfx0, hGfxSrc, NULL),
			   "BVDC_Window_Create" );
	TestError( BVDC_Window_SetAlpha(hGfxWin, BVDC_ALPHA_MAX),
			   "BVDC_Window_SetAlpha" );
	TestError( BVDC_Window_SetBlendFactor(hGfxWin, BVDC_BlendFactor_eSrcAlpha, BVDC_BlendFactor_eOneMinusSrcAlpha, BVDC_ALPHA_MAX),
			   "BVDC_Window_SetBlendFactor" );
	TestError( BVDC_Window_SetZOrder(hGfxWin, 0),
			   "BVDC_Window_SetZOrder" );
	TestError( BVDC_Window_SetScalerOutput(hGfxWin, 0, 0, BTST_P_GFX_WIDTH, BTST_P_GFX_HEIGHT),
			   "BVDC_Window_SetScalerOutput" );
	TestError( BVDC_Window_SetDstRect(hGfxWin,
				   (pVideoFmtInfo->ulWidth - BTST_P_GFX_WIDTH)/2, (pVideoFmtInfo->ulHeight - BTST_P_GFX_HEIGHT)/2,
				   BTST_P_GFX_WIDTH, BTST_P_GFX_HEIGHT),
			   "BVDC_Window_SetDstRect" );
	TestError( BVDC_ApplyChanges(hVdc),
			   "BVDC_ApplyChanges" );

	TestError( BVDC_Window_SetVisibility(hGfxWin, true),
	"BVDC_Window_SetVisibility" );
	TestError( BVDC_ApplyChanges(hVdc),
			   "BVDC_ApplyChanges" );

  Done:
	return;

}

/**************************************************************************/
static void TestInitVdcCfg(
	BVDC_Settings          *pVdcConfig
)
{
	pVdcConfig->eVideoFormat = BFMT_VideoFmt_e480p;

	BKNI_Memset((void*)&pVdcConfig->stHeapSettings, 0x0, sizeof(BVDC_Heap_Settings));
}

/***************************************************************************
 * Main program (exposed API)
 *
 */
int app_main( int argc, char **argv )
{
	BSystem_Info sysInfo;
	BFramework_Info frmInfo;
	BVDC_Settings stVdcConfig;

	BRDC_Handle             hRdc;
	BVDC_Handle             hVdc;
	BVDC_Compositor_Handle  hCompositor0;
	BVDC_Compositor_Handle  hCompositor1;
	BVDC_Display_Handle     hDisplay0;
	BVDC_Display_Handle     hDisplay1;
	BVDC_CompositorId       eCmpId0;
	BVDC_DisplayId          eDisplayId0;
	BVDC_CompositorId       eCmpId1;
	BVDC_DisplayId          eDisplayId1;
	BFMT_VideoInfo          stVideoFmtInfo;
	BERR_Code               err;
	bool                    bDualDisplay;
	int                     iErr;
	BMMA_Heap_Handle        hGfxMem = NULL;

	eCmpId0 = BVDC_CompositorId_eCompositor0;
#if (BCHP_CHIP==7325) || (BCHP_CHIP==7335)
	eDisplayId0 = BVDC_DisplayId_eDisplay1;
#else
	eDisplayId0 = BVDC_DisplayId_eDisplay0;
#endif
	eCmpId1 = CMP_1;
	eDisplayId1 = DISP_1;
	err = BERR_SUCCESS;
	bDualDisplay = DISP_DUAL;

	/* System Init (interrupts/memory mapping) */
	iErr = BSystem_Init( argc, argv, &sysInfo );
	if ( iErr )
	{
		printf( "System init FAILED!\n" );
		return iErr;
	}

	/* Framework init (base modules) */
	iErr = BFramework_Init( &sysInfo, &frmInfo );
	if ( iErr )
	{
		printf( "Framework init FAILED!\n" );
		return iErr;
	}

#if 0
	BDBG_SetModuleLevel("BVDC", BDBG_eMsg);
	BDBG_SetModuleLevel("BVDC_DISP", BDBG_eMsg);
#endif

	/* open Register DMA */
#if (BCHP_CHIP==7445)
	TestError( BRDC_Open(&hRdc, frmInfo.hChp, frmInfo.hReg, frmInfo.hFrmWorkBoard->hMmaHeap2, NULL),
		"ERROR: BRDC_Open" );
#elif (BCHP_CHIP==7145)
	TestError( BRDC_Open(&hRdc, frmInfo.hChp, frmInfo.hReg, frmInfo.hFrmWorkBoard->hMmaHeap1, NULL),
		"ERROR: BRDC_Open" );
#else
	TestError( BRDC_Open(&hRdc, frmInfo.hChp, frmInfo.hReg, frmInfo.hMmaHeap, NULL),
		"ERROR: BRDC_Open" );
#endif

	/* open VDC */
	BVDC_GetDefaultSettings(frmInfo.hBox, &stVdcConfig);
	TestInitVdcCfg(&stVdcConfig);
	TestError( BVDC_Open(&hVdc,frmInfo.hChp, frmInfo.hReg, frmInfo.hMmaHeap,
		frmInfo.hInt, hRdc, frmInfo.hTmr, &stVdcConfig),
		"ERROR: BVDC_Open" );

	printf("Compositor %d -> Display %d (dspFmt %s)\n", eCmpId0, eDisplayId0, DISP_NAME(DISP_FORMAT0));

	/* create compositor handle */
	TestError( BVDC_Compositor_Create( hVdc, &hCompositor0, eCmpId0, NULL ),
		"ERROR: BVDC_Compositor_Create" );

	/* create display for our new compositor */
	TestError( BVDC_Display_Create( hCompositor0, &hDisplay0, eDisplayId0, NULL),
		"ERROR: BVDC_Display_Create" );

	/* Set display format */
	TestError( BVDC_Display_SetVideoFormat( hDisplay0, DISP_FORMAT0 ),
		"ERROR: BVDC_Display_SetVideoFormat" );

	/* Set the background color to red */
	TestError( BVDC_Compositor_SetBackgroundColor( hCompositor0,
		0xFF, 0x00, 0x00 ),
		"ERROR: BVDC_Compositor_SetBackgroundColor" );

	/* Set component DACs for all formats */
	TestError( BVDC_Display_SetDacConfiguration( hDisplay0,
		BFramework_Dac_Component_pr, BVDC_DacOutput_ePr),
		"ERROR: BVDC_Display_SetDacConfiguration" );
	TestError( BVDC_Display_SetDacConfiguration( hDisplay0,
		BFramework_Dac_Component_y, BVDC_DacOutput_eY),
		"ERROR: BVDC_Display_SetDacConfiguration" );
	TestError( BVDC_Display_SetDacConfiguration( hDisplay0,
		BFramework_Dac_Component_pb, BVDC_DacOutput_ePb),
		"ERROR: BVDC_Display_SetDacConfiguration" );

	/* set DAC configurations for specific display format */
	switch (DISP_FORMAT0)
	{
	case BFMT_VideoFmt_eNTSC:
	case BFMT_VideoFmt_eNTSC_J:
	case BFMT_VideoFmt_ePAL_G:
	case BFMT_VideoFmt_ePAL_H:
	case BFMT_VideoFmt_ePAL_K:
	case BFMT_VideoFmt_ePAL_B:
		if (!bDualDisplay &&
			((eDisplayId0 == BVDC_DisplayId_eDisplay1) ||
			((eDisplayId0 == BVDC_DisplayId_eAuto) && (eCmpId0 == BVDC_CompositorId_eCompositor1))))
		{
			printf("Svideo/Composite\n");
			TestError( BVDC_Display_SetDacConfiguration( hDisplay0,
				BFramework_Dac_Composite_0, BVDC_DacOutput_eComposite),
				"ERROR: BVDC_Display_SetDacConfiguration" );
#if (BCHP_CHIP != 7550) && (BCHP_CHIP != 7422) && \
    (BCHP_CHIP != 7344) && (BCHP_CHIP != 7346)
			TestError( BVDC_Display_SetDacConfiguration( hDisplay0,
				BFramework_Dac_Svideo_Chroma, BVDC_DacOutput_eSVideo_Chroma),
				"ERROR: BVDC_Display_SetDacConfiguration" );
			TestError( BVDC_Display_SetDacConfiguration( hDisplay0,
				BFramework_Dac_Svideo_Luma, BVDC_DacOutput_eSVideo_Luma),
				"ERROR: BVDC_Display_SetDacConfiguration" );
#endif
		}
		break;
	default:
		break;
	}

	/* add gfx display */
	TestError( BFMT_GetVideoFormatInfo( DISP_FORMAT0, &stVideoFmtInfo ),
			   "ERROR: BFMT_GetVideoFormatInfo" );

#if (BCHP_CHIP==7445)
	hGfxMem = frmInfo.hFrmWorkBoard->hMmaHeap2;
#elif (BCHP_CHIP==7145)
	hGfxMem = frmInfo.hFrmWorkBoard->hMmaHeap1;
#else
	hGfxMem = frmInfo.hMmaHeap;
#endif

	TestDisplayGfx(hGfxMem, hVdc, BAVC_SourceId_eGfx0, hCompositor0, &stVideoFmtInfo);

	if (bDualDisplay)
	{
		printf("Compositor %d -> Display %d (dspFmt %s)\n", eCmpId1, eDisplayId1, DISP_NAME(DISP_FORMAT1));

		/* create compositor handle */
		TestError( BVDC_Compositor_Create( hVdc, &hCompositor1, eCmpId1, NULL ),
			"ERROR: BVDC_Compositor_Create" );

		/* create display for our new compositor */
		TestError( BVDC_Display_Create( hCompositor1, &hDisplay1, eDisplayId1, NULL),
			"ERROR: BVDC_Display_Create" );

		/* Set display format */
		TestError( BVDC_Display_SetVideoFormat( hDisplay1, DISP_FORMAT1 ),
			"ERROR: BVDC_Display_SetVideoFormat" );

		/* Set the background color to green */
		TestError( BVDC_Compositor_SetBackgroundColor( hCompositor1,
			0x00, 0xFF, 0x0 ),
			"ERROR: BVDC_Compositor_SetBackgroundColor" );

		TestError( BVDC_Display_SetDacConfiguration( hDisplay1,
			BFramework_Dac_Composite_0, BVDC_DacOutput_eComposite),
			"ERROR: BVDC_Display_SetDacConfiguration" );
#if (BCHP_CHIP != 7550) && (BCHP_CHIP != 7422) && (BCHP_CHIP != 7425) && \
    (BCHP_CHIP != 7344) && (BCHP_CHIP != 7346)
		TestError( BVDC_Display_SetDacConfiguration( hDisplay1,
			BFramework_Dac_Svideo_Chroma, BVDC_DacOutput_eSVideo_Chroma),
			"ERROR: BVDC_Display_SetDacConfiguration" );
		TestError( BVDC_Display_SetDacConfiguration( hDisplay1,
			BFramework_Dac_Svideo_Luma, BVDC_DacOutput_eSVideo_Luma),
			"ERROR: BVDC_Display_SetDacConfiguration" );
#endif

		/* add gfx display */
		TestError( BFMT_GetVideoFormatInfo( DISP_FORMAT1, &stVideoFmtInfo ),
				   "ERROR: BFMT_GetVideoFormatInfo" );
#if (BCHP_CHIP==7445)
	hGfxMem = frmInfo.hFrmWorkBoard->hMmaHeap2;
#elif (BCHP_CHIP==7145)
	hGfxMem = frmInfo.hFrmWorkBoard->hMmaHeap1;
#else
	hGfxMem = frmInfo.hMmaHeap;
#endif
		TestDisplayGfx(hGfxMem, hVdc, BAVC_SourceId_eGfx1, hCompositor1, &stVideoFmtInfo);
	}

	/* apply changes */
	TestError( BVDC_ApplyChanges(hVdc),
		"ERROR:BVDC_ApplyChanges" );

	/* Wait for user */
	printf( "Hit 'q' to exit\n" );
	while(true)
	{
		char c;
		c = getchar();
		if (c=='q')
			break;
	}

	return BERR_SUCCESS;


  Done:
	return err;
}

/* End of file */

/***************************************************************************
 *     (c)2007-2014 Broadcom Corporation
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
 **************************************************************************/
#include "nexus_base.h"
#include "nexus_display_module.h"
#include "priv/nexus_core.h"
#include "bkni.h"
#include "priv/nexus_core_preinit.h"

BDBG_MODULE(nexus_display_module);
BDBG_FILE_MODULE(display_proc);

NEXUS_ModuleHandle g_NEXUS_displayModuleHandle = NULL;
NEXUS_DisplayModule_State g_NEXUS_DisplayModule_State;

static void NEXUS_P_SetDisplayCapabilities(void);
#define pVideo (&g_NEXUS_DisplayModule_State)

void
NEXUS_DisplayModule_GetDefaultSettings(const struct NEXUS_Core_PreInitState *preInitState, NEXUS_DisplayModuleSettings *pSettings)
{
    BVDC_Settings vdcCfg;
#if NEXUS_VBI_SUPPORT
    BVBI_Settings vbiCfg;
#endif
    unsigned i, j;

    BKNI_Memset(pSettings, 0, sizeof(*pSettings));
    BVDC_GetDefaultSettings(preInitState->hBox, &vdcCfg);

    pSettings->vecSwap = vdcCfg.bVecSwap;
    pSettings->dropFrame = true; /* without a video source, nexus graphics should default to 59.94/29.97/23.976 (i.e. drop frame) */

    /* verify API macros aren't below nexus_platform_features.h */
    BDBG_CASSERT(NEXUS_MAX_DISPLAYS >= NEXUS_NUM_DISPLAYS);
    BDBG_CASSERT(NEXUS_MAX_VIDEO_WINDOWS >= NEXUS_NUM_VIDEO_WINDOWS);

    BDBG_CASSERT(BVDC_MAX_DACS == NEXUS_MAX_VIDEO_DACS);
    for (i=0;i<NEXUS_MAX_VIDEO_DACS;i++) {
        pSettings->dacBandGapAdjust[i] = vdcCfg.aulDacBandGapAdjust[i];
    }
    BDBG_CASSERT(NEXUS_VideoDacDetection_eOn == (NEXUS_VideoDacDetection)BVDC_Mode_eOn);
    pSettings->dacDetection = vdcCfg.eDacDetection;

#if NEXUS_VBI_SUPPORT
    BVBI_GetDefaultSettings(&vbiCfg);
    pSettings->vbi.tteShiftDirMsb2Lsb = vbiCfg.tteShiftDirMsb2Lsb;
    pSettings->vbi.ccir656InputBufferSize = vbiCfg.in656bufferSize;
#endif

    /* default formats are based on typical usage. if you require a different use, please modify this in your platform or application. */
    pSettings->primaryDisplayHeapIndex = 0;
    pSettings->fullHdBuffers.format = NEXUS_VideoFormat_e1080p30hz;
    pSettings->fullHdBuffers.pixelFormat = NEXUS_PixelFormat_eY18_Cb8_Y08_Cr8;
    pSettings->hdBuffers.format = NEXUS_VideoFormat_e1080i;
    pSettings->hdBuffers.pixelFormat = NEXUS_PixelFormat_eY18_Cb8_Y08_Cr8;
    pSettings->sdBuffers.format = NEXUS_VideoFormat_ePalG;
    pSettings->sdBuffers.pixelFormat = NEXUS_PixelFormat_eY18_Cb8_Y08_Cr8;

    for (j=0;j<NEXUS_MAX_DISPLAYS;j++) {
        for (i=0;i<NEXUS_MAX_VIDEO_WINDOWS;i++) {
            pSettings->videoWindowHeapIndex[j][i] = NEXUS_MAX_HEAPS; /* unused unless specified */
            pSettings->deinterlacerHeapIndex[j][i] = NEXUS_MAX_HEAPS; /* unused unless specified */
        }
    }
    /* for non-memconfig platforms */
    pSettings->legacy.numDisplays = NEXUS_NUM_DISPLAYS;
    pSettings->legacy.numWindowsPerDisplay = NEXUS_NUM_VIDEO_WINDOWS;

    for(i=0;i<NEXUS_MAX_HEAPS;i++ )
    {
        pSettings->displayHeapSettings[i].quadHdBuffers.format = NEXUS_VideoFormat_e3840x2160p30hz;
        pSettings->displayHeapSettings[i].quadHdBuffers.pixelFormat = NEXUS_PixelFormat_eY18_Cb8_Y08_Cr8;
        pSettings->displayHeapSettings[i].fullHdBuffers.format = NEXUS_VideoFormat_e1080p30hz;
        pSettings->displayHeapSettings[i].fullHdBuffers.pixelFormat = NEXUS_PixelFormat_eY18_Cb8_Y08_Cr8;
        pSettings->displayHeapSettings[i].hdBuffers.format = NEXUS_VideoFormat_e1080i;
        pSettings->displayHeapSettings[i].hdBuffers.pixelFormat = NEXUS_PixelFormat_eY18_Cb8_Y08_Cr8;
        pSettings->displayHeapSettings[i].sdBuffers.format = NEXUS_VideoFormat_ePalG;
        pSettings->displayHeapSettings[i].sdBuffers.pixelFormat = NEXUS_PixelFormat_eY18_Cb8_Y08_Cr8;
    }

    return;
}

BERR_Code
NEXUS_P_DisplayTriState_ToMagnum(NEXUS_TristateEnable tristateEnable, BVDC_Mode *mtristateEnable)
{
    switch (tristateEnable) {
    case NEXUS_TristateEnable_eDisable:
        *mtristateEnable = BVDC_Mode_eOff;
        break;
    case NEXUS_TristateEnable_eEnable:
        *mtristateEnable = BVDC_Mode_eOn;
        break;
    case NEXUS_TristateEnable_eNotSet:
        *mtristateEnable = BVDC_Mode_eAuto;
        break;
    default:
        return BERR_TRACE(BERR_INVALID_PARAMETER);
    }
    return 0;
}

BERR_Code
NEXUS_P_DisplayAspectRatio_ToMagnum(NEXUS_DisplayAspectRatio aspectRatio, NEXUS_VideoFormat format, BFMT_AspectRatio *maspectRatio)
{
    switch (aspectRatio) {
    case NEXUS_DisplayAspectRatio_eAuto:
        {
        NEXUS_VideoFormatInfo formatInfo;
        NEXUS_VideoFormat_GetInfo(format, &formatInfo);
        *maspectRatio = (formatInfo.width > 720) ? BFMT_AspectRatio_e16_9 : BFMT_AspectRatio_e4_3;
        }
        break;
    case NEXUS_DisplayAspectRatio_e4x3:
        *maspectRatio = BFMT_AspectRatio_e4_3;
        break;
    case NEXUS_DisplayAspectRatio_e16x9:
        *maspectRatio = BFMT_AspectRatio_e16_9;
        break;
    case NEXUS_DisplayAspectRatio_eSar:
        *maspectRatio = BFMT_AspectRatio_eSAR;
        break;
    default:
        return BERR_TRACE(BERR_INVALID_PARAMETER);
    }
    return 0;
}

bool
NEXUS_P_Display_RectEqual(const NEXUS_Rect *r1,  const NEXUS_Rect *r2)
{
    BDBG_ASSERT(r1);
    BDBG_ASSERT(r2);
    return r1->x == r2->x && r1->width == r2->width && r1->y == r2->y && r1->height == r2->height;
}

static const NEXUS_Rect NEXUS_P_EmptyRect = {0,0,0,0};

NEXUS_Error NEXUS_Display_P_GetScalerRect(const NEXUS_VideoWindowSettings *pSettings, NEXUS_Rect *pRect)
{
    /* if the user set clipBase.x and .y, they probably don't understand the API. put out this warning so we can catch problems. */
    if (pSettings->clipBase.x || pSettings->clipBase.y) {
        BDBG_WRN(("clipBase.x and .y are unused but clipBase was set to %d,%d,%d,%d.", pSettings->clipBase.x, pSettings->clipBase.y, pSettings->clipBase.width, pSettings->clipBase.height));
    }

    if (NEXUS_P_Display_RectEqual(&NEXUS_P_EmptyRect, &pSettings->clipRect)) {
        /* no clipping */
        pRect->x = pRect->y = 0;
        pRect->width = pSettings->position.width;
        pRect->height = pSettings->position.height;
    }
    else if (pSettings->clipBase.width == 0 && pSettings->clipBase.height == 0) {
        /* if clipBase width & height are 0, pass clipRect directly into BVDC_Window_SetScalerOutput. This avoids
        the clipBase/clipRect transformation. for now, this is an undocumented feature until its usage can be clarified. */
        *pRect = pSettings->clipRect;
    }
    else {
        unsigned x,y, width, height;
        if(pSettings->clipRect.x < 0 ||  pSettings->clipRect.y < 0  ||
           pSettings->clipRect.width == 0 || pSettings->clipRect.height == 0 ||
           pSettings->clipBase.width == 0 || pSettings->clipBase.height == 0 ||
           pSettings->clipRect.width+pSettings->clipRect.x > pSettings->clipBase.width || pSettings->clipRect.height+pSettings->clipRect.y > pSettings->clipBase.height) {
            pRect->x = pRect->y = 0;
            pRect->width = pSettings->position.width;
            pRect->height = pSettings->position.height;
            return BERR_TRACE(BERR_INVALID_PARAMETER);
        }
        x = (((unsigned)pSettings->position.width)*pSettings->clipRect.x)/pSettings->clipRect.width;
        y = (((unsigned)pSettings->position.height)*pSettings->clipRect.y)/pSettings->clipRect.height;
        width = (((unsigned)pSettings->position.width)*pSettings->clipBase.width)/pSettings->clipRect.width;
        height = (((unsigned)pSettings->position.height)*pSettings->clipBase.height)/pSettings->clipRect.height;

        pRect->x = x;
        pRect->y = y;
        pRect->width = width;
        pRect->height = height;
    }

    return NEXUS_SUCCESS;
}

#if BRDC_USE_CAPTURE_BUFFER
#if NEXUS_BASE_OS_linuxuser
#define BRDC_USE_CAPTURE_BUFFER_FILE 1
#endif
#if BRDC_USE_CAPTURE_BUFFER_FILE
#include <stdio.h>
#endif
#include "brdc_dbg.h"
#include "bdbg_fifo.h"
#define NEXUS_RDC_CAPTURE_SIZE 4096
static BDBG_Fifo_Handle g_rdc_capture_fifo; /* see NEXUS_PlatformStatus.displayModuleStatus.rulCapture for BDBG_Fifo reader access */
static struct {
    NEXUS_TimerHandle timer;
    uint8_t mem[NEXUS_RDC_CAPTURE_SIZE*2];
    unsigned total; /* total buffered in mem */
    NEXUS_MemoryBlockHandle memory;
    unsigned bufferSize;
    unsigned refCnt;
} g_rdc_capture;

static void NEXUS_Display_P_RdcReadCapture(void *data)
{
    BRDC_Handle rdc = (BRDC_Handle)data;
    int total;
#if BRDC_USE_CAPTURE_BUFFER_FILE
    static FILE *file = NULL;
    static int filesize = 0;
    const char *filename = NEXUS_GetEnv("capture_ruls");
#endif

    g_rdc_capture.timer = NULL;

#if BRDC_USE_CAPTURE_BUFFER_FILE
    if(filename) {
        if (!file) {
            static int filecnt = 0;
            char buf[256];
            BKNI_Snprintf(buf, 256, "%s%d", filename, filecnt++);
            file = fopen(buf, "w+");
            BDBG_WRN(("opened rul log file %s", buf));
        }
    }
#endif

    if (rdc) {
        do {
            /* read from RDC is variable sized, write to disk is variables sized, write to BDBG_Fifo is fixed size */
            BKNI_EnterCriticalSection();
            BRDC_DBG_ReadCapture_isr(rdc, &g_rdc_capture.mem[g_rdc_capture.total], NEXUS_RDC_CAPTURE_SIZE, &total);
            BKNI_LeaveCriticalSection();

#if BRDC_USE_CAPTURE_BUFFER_FILE
            if(file) {
                fwrite(&g_rdc_capture.mem[g_rdc_capture.total], total, 1, file);
                filesize += total;
            }
#endif

            g_rdc_capture.total += total;
            if (g_rdc_capture.total >= NEXUS_RDC_CAPTURE_SIZE) {
                BDBG_Fifo_Token token;
                void *buffer = BDBG_Fifo_GetBuffer(g_rdc_capture_fifo, &token);
                if (buffer) {
                    BKNI_Memcpy(buffer, g_rdc_capture.mem, NEXUS_RDC_CAPTURE_SIZE);
                    BDBG_Fifo_CommitBuffer(&token);
                }
                if (g_rdc_capture.total > NEXUS_RDC_CAPTURE_SIZE) {
                    BKNI_Memmove(g_rdc_capture.mem, &g_rdc_capture.mem[NEXUS_RDC_CAPTURE_SIZE], g_rdc_capture.total - NEXUS_RDC_CAPTURE_SIZE);
                }
                g_rdc_capture.total -= NEXUS_RDC_CAPTURE_SIZE;
            }
       } while (total);
   }

#if BRDC_USE_CAPTURE_BUFFER_FILE
   if (!rdc || filesize >= 100*1024*1024) {
       if(file) fclose(file);
       file = NULL;
       filesize = 0;
       /* on the next write, a new file will be opened. */
   }
#endif

    if (rdc) {
        g_rdc_capture.timer = NEXUS_ScheduleTimer(1000, NEXUS_Display_P_RdcReadCapture, rdc);
    }
}

/* nexus_display_p_init_rdccapture cannot be called during NEXUS_DisplayModule_Init because it
creates a NEXUS_MemoryBlock which could be acquired by a client app and therefore could
be registered in the objdb. */
int nexus_display_p_init_rdccapture(void)
{
    int rc;
    BDBG_Fifo_CreateSettings settings;

    if (!NEXUS_GetEnv("capture_ruls")) return 0;

    /* reference count the rdc capture */
    if(g_rdc_capture.refCnt++ > 0) return 0;

    g_rdc_capture.bufferSize = NEXUS_RDC_CAPTURE_SIZE * 80;
    g_rdc_capture.memory = NEXUS_MemoryBlock_Allocate(NULL, g_rdc_capture.bufferSize, 0, NULL);
    if (!g_rdc_capture.memory) {rc = BERR_TRACE(NEXUS_OUT_OF_DEVICE_MEMORY); goto error;}

    BDBG_WRN(("starting rul capture: buffer %d", g_rdc_capture.bufferSize));
    BDBG_Fifo_GetDefaultCreateSettings(&settings);
    settings.elementSize = NEXUS_RDC_CAPTURE_SIZE;
    NEXUS_MemoryBlock_Lock(g_rdc_capture.memory, &settings.buffer);
    settings.bufferSize = g_rdc_capture.bufferSize;
    rc = BDBG_Fifo_Create(&g_rdc_capture_fifo, &settings);
    if (rc) {return BERR_TRACE(rc); goto error;}

    g_rdc_capture.timer = NEXUS_ScheduleTimer(1000, NEXUS_Display_P_RdcReadCapture, g_NEXUS_DisplayModule_State.rdc);
    if (!g_rdc_capture.timer) {rc = BERR_TRACE(NEXUS_UNKNOWN); goto error;}

    return 0;

error:
    if (g_rdc_capture.memory) {
        NEXUS_MemoryBlock_Free(g_rdc_capture.memory);
    }
    return rc;
}

void nexus_display_p_uninit_rdccapture(void)
{
    /* reference count the rdc capture */
    if(--g_rdc_capture.refCnt > 0) return;

    NEXUS_Display_P_RdcReadCapture(NULL); /* closes file */
    BDBG_ASSERT(!g_rdc_capture.timer);
    if (g_rdc_capture_fifo) {
        BDBG_Fifo_Destroy(g_rdc_capture_fifo);
        NEXUS_MemoryBlock_Free(g_rdc_capture.memory);
        g_rdc_capture_fifo = NULL;
    }
}
#else
int nexus_display_p_init_rdccapture(void)
{
    return 0;
}
void nexus_display_p_uninit_rdccapture(void)
{
}
#endif

void NEXUS_DisplayModule_Print(void)
{
#if BDBG_DEBUG_BUILD
    unsigned i;
    NEXUS_VideoInput_P_Link *input;
	BVDC_Window_DebugStatus winDbgInfo;
	BVDC_Source_DebugStatus srcDbgInfo;


    BDBG_MODULE_LOG(display_proc, ("DisplayModule:"));
    for (i=0;i<NEXUS_NUM_DISPLAYS;i++) {
        unsigned j;
        NEXUS_VideoOutput_P_Link *output;
        NEXUS_DisplayHandle display = g_NEXUS_DisplayModule_State.displays[i];
        NEXUS_VideoFormatInfo formatInfo;
        static const char *g_contentModeStr[NEXUS_VideoWindowContentMode_eMax] = {"zoom","box","panscan","full","nonlinear","panscan_no_corr"};

        if (!display) continue;

        NEXUS_VideoFormat_GetInfo(display->cfg.format, &formatInfo);

        BDBG_MODULE_LOG(display_proc, ("display %d: format=%dx%d%c(%d) %d.%02dhz", i,
            display->displayRect.width,display->displayRect.height,formatInfo.interlaced?'i':'p', display->cfg.format,
            display->status.refreshRate/1000, display->status.refreshRate%1000));
        BDBG_MODULE_LOG(display_proc, ("  graphics: %s fb=%p %dx%d pixelFormat=%d", display->graphics.windowVdc?"enabled":"disabled", (void *)display->graphics.frameBuffer3D.main,
            display->graphics.cfg.clip.width?display->graphics.cfg.clip.width:display->graphics.frameBufferWidth,
            display->graphics.cfg.clip.height?display->graphics.cfg.clip.height:display->graphics.frameBufferHeight,
            display->graphics.frameBufferPixelFormat));
        if (display->graphics.windowVdc) {
            BVDC_Dbg_Window_GetDebugStatus(display->graphics.windowVdc, &winDbgInfo);
            BDBG_MODULE_LOG(display_proc, ("            vsync count=%d, line=%d, errors=%d", winDbgInfo.ulVsyncCnt, winDbgInfo.ulLineNumber, winDbgInfo.ulNumErr));
        }

        for (j=0;j<NEXUS_NUM_VIDEO_WINDOWS;j++) {
            NEXUS_VideoWindowHandle window = &display->windows[j];
            if (!window->open) continue;
            BDBG_MODULE_LOG(display_proc, ("  window %d: visible=%c, position=%d,%d,%d,%d, zorder=%d, ar=%s, NEXUS_VideoInput=%p, sync%s",
                window->windowId,
                window->cfg.visible?'y':'n',
                window->cfg.position.x, window->cfg.position.y, window->cfg.position.width, window->cfg.position.height,
                window->cfg.zorder,
                g_contentModeStr[window->cfg.contentMode],
                (void *)window->input,
                window->status.isSyncLocked?"Lock":"Slip"));
            if (window->vdcState.window) {
                BVDC_Dbg_Window_GetDebugStatus(window->vdcState.window, &winDbgInfo);
                BDBG_MODULE_LOG(display_proc, ("            vsync count=%d, line=%d, errors=%d", winDbgInfo.ulVsyncCnt, winDbgInfo.ulLineNumber, winDbgInfo.ulNumErr));
            }
#if NEXUS_NUM_MOSAIC_DECODES
            {
                NEXUS_VideoWindowHandle child;
                for (child = BLST_S_FIRST(&window->mosaic.children); child; child = BLST_S_NEXT(child, mosaic.link)) {
                    BDBG_MODULE_LOG(display_proc, ("  mosaic %d: visible=%c, position=%d,%d,%d,%d, zorder=%d, NEXUS_VideoInput=%p",
                        child->mosaic.userIndex,
                        child->cfg.visible?'y':'n',
                        child->cfg.position.x, child->cfg.position.y, child->cfg.position.width, child->cfg.position.height,
                        child->cfg.zorder,
                        (void *)child->input));
                }
            }
#endif
        }

        for (output=BLST_D_FIRST(&display->outputs);output;output=BLST_D_NEXT(output, link)) {
            BDBG_MODULE_LOG(display_proc, ("  output %p: %s", (void *)output, g_videoOutputStr[output->output->type]));
        }
    }

    for (input=BLST_S_FIRST(&g_NEXUS_DisplayModule_State.inputs);input;input=BLST_S_NEXT(input, link)) {
        char buf[32];
        if (input->id <= BAVC_SourceId_eMpegMax) {
            BKNI_Snprintf(buf, 32, "eMpeg%d", input->id);
        }
        else if (input->id <= BAVC_SourceId_eGfxMax) {
            BKNI_Snprintf(buf, 32, "eGfx%d", input->id-BAVC_SourceId_eMpegMax);
        }
        else if (input->id <= BAVC_SourceId_eVfdMax) {
            BKNI_Snprintf(buf, 32, "eVfd%d", input->id-BAVC_SourceId_eGfxMax);
        }
        else {
            BKNI_Snprintf(buf, 32, "BAVC_SourceId %d", input->id);
        }
		BVDC_Dbg_Source_GetDebugStatus(input->sourceVdc, &srcDbgInfo);
        BDBG_MODULE_LOG(display_proc, ("NEXUS_VideoInput %p: link=%p, %s, %s, ref_cnt=%d, errors=%d",
            (void *)input->input, (void *)input, g_videoInputStr[input->input->type], buf, input->ref_cnt, srcDbgInfo.ulNumErr));
    }
#endif

}

NEXUS_ModuleHandle
NEXUS_DisplayModule_Init(const NEXUS_DisplayModuleSettings *pSettings)
{
    NEXUS_ModuleSettings moduleSettings;
    BERR_Code rc;
    BVDC_Settings vdcCfg;
    NEXUS_DisplayModule_State *state = &g_NEXUS_DisplayModule_State;
    BPXL_Format mPixelFormat;
    BFMT_VideoFmt mVideoFormat;
    unsigned i;

    if(!pSettings) {
        rc = BERR_TRACE(BERR_INVALID_PARAMETER);
        goto err_settings;
    }

    BKNI_Memset(state, 0, sizeof(*state));
    state->moduleSettings = *pSettings;
    state->pqDisabled = NEXUS_GetEnv("pq_disabled")!=NULL;

    if (pSettings->modules.surface == NULL) {
        rc = BERR_TRACE(BERR_INVALID_PARAMETER);
        goto err_settings;
    }
#if NEXUS_HAS_HDMI_INPUT
    if (pSettings->modules.hdmiInput == NULL) {
        rc = BERR_TRACE(BERR_INVALID_PARAMETER);
        goto err_settings;
    }
#endif
#if NEXUS_HAS_TRANSPORT
    if (pSettings->modules.transport == NULL) {
        rc = BERR_TRACE(BERR_INVALID_PARAMETER);
        goto err_settings;
    }
#endif

    NEXUS_Module_GetDefaultSettings(&moduleSettings);
    /* default priority */
    moduleSettings.dbgPrint = NEXUS_DisplayModule_Print;
    moduleSettings.dbgModules = "display_proc";
    g_NEXUS_displayModuleHandle = NEXUS_Module_Create("display", &moduleSettings);
    if(!g_NEXUS_displayModuleHandle) { rc = BERR_TRACE(BERR_OS_ERROR); goto err_module; }
    NEXUS_LockModule();

    if (pSettings->modules.videoDecoder) {
        NEXUS_UseModule(pSettings->modules.videoDecoder);
    }
    NEXUS_UseModule(pSettings->modules.surface);
#if NEXUS_HAS_HDMI_INPUT
    NEXUS_UseModule(pSettings->modules.hdmiInput);
#endif
#if NEXUS_HAS_HDMI_OUTPUT
    NEXUS_UseModule(pSettings->modules.hdmiOutput);
#endif
#if NEXUS_HAS_HDMI_DVO
    NEXUS_UseModule(pSettings->modules.hdmiDvo);
#endif
#if NEXUS_HAS_TRANSPORT
    NEXUS_UseModule(pSettings->modules.transport);
#endif
    BLST_S_INIT(&state->inputs);
    state->updateMode = NEXUS_DisplayUpdateMode_eAuto;
    state->lastUpdateFailed = false;
    state->modules = pSettings->modules;
    for(i=0;i<sizeof(state->displays)/sizeof(state->displays[0]);i++) {
        state->displays[i] = NULL;
    }
    {
        BTMR_TimerSettings sTmrSettings;
        BTMR_GetDefaultTimerSettings(&sTmrSettings);
        sTmrSettings.type = BTMR_Type_eSharedFreeRun;
        rc = BTMR_CreateTimer(g_pCoreHandles->tmr, &state->tmr, &sTmrSettings);
        if (rc) {rc = BERR_TRACE(rc); goto err_tmr;}
    }

    /* get heap settings from NEXUS_DisplayModuleSettings and apply to individual nexus heaps */
    for (i=0;i<NEXUS_MAX_HEAPS;i++) {
        NEXUS_HeapHandle heap = g_pCoreHandles->heap[i].nexus;
        if (heap) {
            NEXUS_Heap_SetDisplayHeapSettings(heap, &pSettings->displayHeapSettings[i]);
        }
    }

    /* open VDC */
    BVDC_GetDefaultSettings(g_pCoreHandles->box, &vdcCfg);

    vdcCfg.bVecSwap = pSettings->vecSwap;

    /*
     * For platforms with single VDC heap,check for the  HD and SD buffers count.
     * If all the buffer counts are zero, then the platform uses multiple VDC heaps.
     */
    if(pSettings->fullHdBuffers.count || pSettings->hdBuffers.count || pSettings->sdBuffers.count ||
       pSettings->fullHdBuffers.pipCount || pSettings->hdBuffers.pipCount || pSettings->sdBuffers.pipCount){
        (void)NEXUS_P_PixelFormat_ToMagnum_isrsafe(pSettings->fullHdBuffers.pixelFormat, &mPixelFormat);
        (void)NEXUS_P_VideoFormat_ToMagnum_isrsafe(pSettings->fullHdBuffers.format, &mVideoFormat);
        vdcCfg.stHeapSettings.ulBufferCnt_2HD = pSettings->fullHdBuffers.count;
        vdcCfg.stHeapSettings.ulBufferCnt_2HD_Pip = pSettings->fullHdBuffers.pipCount;
        vdcCfg.stHeapSettings.ePixelFormat_2HD = mPixelFormat;
        vdcCfg.stHeapSettings.eBufferFormat_2HD = mVideoFormat;

        (void)NEXUS_P_PixelFormat_ToMagnum_isrsafe(pSettings->hdBuffers.pixelFormat, &mPixelFormat);
        (void)NEXUS_P_VideoFormat_ToMagnum_isrsafe(pSettings->hdBuffers.format, &mVideoFormat);
        vdcCfg.stHeapSettings.ulBufferCnt_HD = pSettings->hdBuffers.count;
        vdcCfg.stHeapSettings.ulBufferCnt_HD_Pip = pSettings->hdBuffers.pipCount;
        vdcCfg.stHeapSettings.ePixelFormat_HD = mPixelFormat;
        vdcCfg.stHeapSettings.eBufferFormat_HD = mVideoFormat;

        /* set default format based on hdBuffer format */
        vdcCfg.eVideoFormat = mVideoFormat;

        (void)NEXUS_P_PixelFormat_ToMagnum_isrsafe(pSettings->sdBuffers.pixelFormat, &mPixelFormat);
        (void)NEXUS_P_VideoFormat_ToMagnum_isrsafe(pSettings->sdBuffers.format, &mVideoFormat);
        vdcCfg.stHeapSettings.ulBufferCnt_SD = pSettings->sdBuffers.count;
        vdcCfg.stHeapSettings.ulBufferCnt_SD_Pip = pSettings->sdBuffers.pipCount;
        vdcCfg.stHeapSettings.ePixelFormat_SD = mPixelFormat;
        vdcCfg.stHeapSettings.eBufferFormat_SD = mVideoFormat;
    }
    else{
        unsigned heapIndex = pSettings->primaryDisplayHeapIndex;

        (void)NEXUS_P_PixelFormat_ToMagnum_isrsafe(pSettings->displayHeapSettings[heapIndex].quadHdBuffers.pixelFormat, &mPixelFormat);
        (void)NEXUS_P_VideoFormat_ToMagnum_isrsafe(pSettings->displayHeapSettings[heapIndex].quadHdBuffers.format, &mVideoFormat);
        vdcCfg.stHeapSettings.ulBufferCnt_4HD = pSettings->displayHeapSettings[heapIndex].quadHdBuffers.count;
        vdcCfg.stHeapSettings.ulBufferCnt_4HD_Pip = pSettings->displayHeapSettings[heapIndex].quadHdBuffers.pipCount;
        vdcCfg.stHeapSettings.ePixelFormat_4HD = mPixelFormat;
        vdcCfg.stHeapSettings.eBufferFormat_4HD = mVideoFormat;
        (void)NEXUS_P_PixelFormat_ToMagnum_isrsafe(pSettings->displayHeapSettings[heapIndex].fullHdBuffers.pixelFormat, &mPixelFormat);
        (void)NEXUS_P_VideoFormat_ToMagnum_isrsafe(pSettings->displayHeapSettings[heapIndex].fullHdBuffers.format, &mVideoFormat);
        vdcCfg.stHeapSettings.ulBufferCnt_2HD = pSettings->displayHeapSettings[heapIndex].fullHdBuffers.count;
        vdcCfg.stHeapSettings.ulBufferCnt_2HD_Pip = pSettings->displayHeapSettings[heapIndex].fullHdBuffers.pipCount;
        vdcCfg.stHeapSettings.ePixelFormat_2HD = mPixelFormat;
        vdcCfg.stHeapSettings.eBufferFormat_2HD = mVideoFormat;
        (void)NEXUS_P_PixelFormat_ToMagnum_isrsafe(pSettings->displayHeapSettings[heapIndex].hdBuffers.pixelFormat, &mPixelFormat);
        (void)NEXUS_P_VideoFormat_ToMagnum_isrsafe(pSettings->displayHeapSettings[heapIndex].hdBuffers.format, &mVideoFormat);
        vdcCfg.stHeapSettings.ulBufferCnt_HD = pSettings->displayHeapSettings[heapIndex].hdBuffers.count;
        vdcCfg.stHeapSettings.ulBufferCnt_HD_Pip =pSettings->displayHeapSettings[heapIndex].hdBuffers.pipCount;
        vdcCfg.stHeapSettings.ePixelFormat_HD = mPixelFormat;
        vdcCfg.stHeapSettings.eBufferFormat_HD = mVideoFormat;

        /* set default format based on hdBuffer format */
        vdcCfg.eVideoFormat = mVideoFormat;

        (void)NEXUS_P_PixelFormat_ToMagnum_isrsafe(pSettings->displayHeapSettings[heapIndex].sdBuffers.pixelFormat, &mPixelFormat);
        (void)NEXUS_P_VideoFormat_ToMagnum_isrsafe(pSettings->displayHeapSettings[heapIndex].sdBuffers.format, &mVideoFormat);
        vdcCfg.stHeapSettings.ulBufferCnt_SD = pSettings->displayHeapSettings[heapIndex].sdBuffers.count;
        vdcCfg.stHeapSettings.ulBufferCnt_SD_Pip = pSettings->displayHeapSettings[heapIndex].sdBuffers.pipCount;
        vdcCfg.stHeapSettings.ePixelFormat_SD = mPixelFormat;
        vdcCfg.stHeapSettings.eBufferFormat_SD = mVideoFormat;
    }

    BDBG_MSG(("Creating main VDC heap: SD %u, HD %u, 2HD %u, 4HD %u, SD_PIP %u, HD_PIP %u, 2HD_PIP %u ,4HD_PIP %u",
              vdcCfg.stHeapSettings.ulBufferCnt_SD, vdcCfg.stHeapSettings.ulBufferCnt_HD,
              vdcCfg.stHeapSettings.ulBufferCnt_2HD,vdcCfg.stHeapSettings.ulBufferCnt_4HD,
              vdcCfg.stHeapSettings.ulBufferCnt_SD_Pip, vdcCfg.stHeapSettings.ulBufferCnt_HD_Pip,
              vdcCfg.stHeapSettings.ulBufferCnt_2HD_Pip, vdcCfg.stHeapSettings.ulBufferCnt_4HD_Pip));

    vdcCfg.eDisplayFrameRate = pSettings->dropFrame ? BAVC_FrameRateCode_e59_94 : BAVC_FrameRateCode_e60;

    BDBG_CASSERT(BVDC_MAX_DACS == NEXUS_MAX_VIDEO_DACS);
    for (i=0;i<NEXUS_MAX_VIDEO_DACS;i++) {
        vdcCfg.aulDacBandGapAdjust[i] = pSettings->dacBandGapAdjust[i];
    }
    vdcCfg.eDacDetection = pSettings->dacDetection;

    if (pSettings->primaryDisplayHeapIndex >= NEXUS_MAX_HEAPS || !g_pCoreHandles->heap[pSettings->primaryDisplayHeapIndex].nexus) {
        rc = BERR_TRACE(NEXUS_INVALID_PARAMETER);
        goto err_vdc;
    }

    state->heap = g_pCoreHandles->heap[pSettings->primaryDisplayHeapIndex].nexus;

#if !NEXUS_NUM_MOSAIC_DECODES
    vdcCfg.bDisableMosaic = true;
#endif
#if !NEXUS_NUM_656_INPUTS
    vdcCfg.bDisable656Input = true;
#endif
#if !NEXUS_NUM_HDDVI_INPUTS && !NEXUS_NUM_HDMI_INPUTS
    vdcCfg.bDisableHddviInput = true;
#endif
    NEXUS_P_SetDisplayCapabilities();
    NEXUS_UnlockModule();
    return g_NEXUS_displayModuleHandle;

#if NEXUS_VBI_SUPPORT
err_vbilist:
    BVBIlib_Close(state->vbilib);
err_vbilib:
    BVBI_Close(state->vbi);
err_vbi:
#endif
    BVDC_Close(state->vdc);
err_vdc:
    BRDC_Close(state->rdc);
err_rdc:
    BTMR_DestroyTimer(state->tmr);
err_tmr:
    NEXUS_UnlockModule();
    NEXUS_Module_Destroy(g_NEXUS_displayModuleHandle);
err_module:
err_settings:
    return NULL;
}

void NEXUS_DisplayModule_GetSettings( NEXUS_DisplayModuleSettings *pSettings )
{
    *pSettings = g_NEXUS_DisplayModule_State.moduleSettings;
}

void NEXUS_DisplayModule_Uninit(void)
{
    NEXUS_DisplayModule_State *state = &g_NEXUS_DisplayModule_State;
    BERR_Code rc;
    unsigned i;

    /* auto cleanup must run with module lock held */
    NEXUS_LockModule();
    for (i=0;i<sizeof(state->displays)/sizeof(state->displays[0]);i++) {
        if (state->displays[i]) {
            BDBG_WRN(("Implicit NEXUS_Display_Close(%d) called", i));
            NEXUS_OBJECT_UNREGISTER(NEXUS_Display, state->displays[i], Destroy);
            NEXUS_Display_Close(state->displays[i]);
        }
    }

    /* closing all displays should destroy all inputs and outputs */
    BDBG_ASSERT(!BLST_S_FIRST(&state->inputs));

#if NEXUS_VBI_SUPPORT
    BVBIlib_List_Destroy(state->vbilist);
    BVBIlib_Close(state->vbilib);
    BVBI_Close(state->vbi);
    if (g_NEXUS_DisplayModule_State.ttLines) {
        BKNI_Free(g_NEXUS_DisplayModule_State.ttLines);
        g_NEXUS_DisplayModule_State.ttLines = NULL;
    }
#endif

#if NEXUS_DISPLAY_EXTENSION_PQ_CUSTOMIZATION
    rc = NEXUS_CustomPq_Uninit();
    if (rc!=BERR_SUCCESS) { rc = BERR_TRACE(rc);}
#endif
    rc = BERR_SUCCESS;

    BTMR_DestroyTimer(state->tmr);

    for (i=0;i<MAX_VDC_HEAPS;i++) {
        if (state->vdcHeapMap[i].refcnt) {
            BDBG_ERR(("VDC heap %d not destroyed. Internal state problem.", i));
        }
    }

    NEXUS_UnlockModule();
    NEXUS_Module_Destroy(g_NEXUS_displayModuleHandle);
    return;
}

NEXUS_Error NEXUS_Display_P_ApplyChanges(void)
{
    if (g_NEXUS_DisplayModule_State.updateMode==NEXUS_DisplayUpdateMode_eAuto) {
        BERR_Code rc;
        rc = BVDC_ApplyChanges(g_NEXUS_DisplayModule_State.vdc);
        if (rc) return BERR_TRACE(rc);
    }
    return 0;
}

void NEXUS_Display_P_DestroyHeap(BVDC_Heap_Handle vdcHeap)
{
    NEXUS_DisplayModule_State *state = &g_NEXUS_DisplayModule_State;
    unsigned i;

    for (i=0;i<MAX_VDC_HEAPS;i++) {
        if (state->vdcHeapMap[i].vdcHeap == vdcHeap) {
            BDBG_ASSERT(state->vdcHeapMap[i].refcnt);
            if (--state->vdcHeapMap[i].refcnt == 0) {
                BVDC_Heap_Destroy(state->vdcHeapMap[i].vdcHeap);
                state->vdcHeapMap[i].vdcHeap = NULL;
                state->vdcHeapMap[i].nexusHeap = NULL;
            }
            return;
        }
    }
    BDBG_ERR(("Couldn't find heap"));
    BDBG_ASSERT(0);
}

BVDC_Heap_Handle NEXUS_Display_P_CreateHeap(NEXUS_HeapHandle heap)
{
    BVDC_Settings vdcCfg;
    BERR_Code rc;
    BPXL_Format mPixelFormat;
    BFMT_VideoFmt mVideoFormat;
    NEXUS_DisplayHeapSettings displayHeapSettings;
    int i, openSlot = -1;
    NEXUS_DisplayModule_State *state = &g_NEXUS_DisplayModule_State;

    NEXUS_Heap_GetDisplayHeapSettings(heap, &displayHeapSettings);

    if (!displayHeapSettings.fullHdBuffers.pixelFormat &&
        !displayHeapSettings.hdBuffers.pixelFormat &&
        !displayHeapSettings.sdBuffers.pixelFormat)
    {
        BDBG_ERR(("NEXUS_DisplayHeapSettings have not been set for heap %p", (void *)heap));
        return NULL;
    }

    for (i=0;i<MAX_VDC_HEAPS;i++) {
        if (state->vdcHeapMap[i].nexusHeap == heap) {
            BDBG_ASSERT(state->vdcHeapMap[i].vdcHeap);
            BDBG_ASSERT(state->vdcHeapMap[i].refcnt);
            BDBG_MSG(("Reusing VDC heap %d", i));
            state->vdcHeapMap[i].refcnt++;
            return state->vdcHeapMap[i].vdcHeap;
        }
        else if (openSlot == -1 && !state->vdcHeapMap[i].nexusHeap) {
            openSlot = i;
            BDBG_ASSERT(!state->vdcHeapMap[i].vdcHeap);
            BDBG_ASSERT(!state->vdcHeapMap[i].refcnt);
        }
    }
    if (openSlot == -1) {
        BDBG_ERR(("Increase MAX_VDC_HEAPS"));
        return NULL;
    }

    /* Replace NULL  with BOX handle */
    BVDC_GetDefaultSettings(NULL, &vdcCfg);

    rc = NEXUS_P_PixelFormat_ToMagnum_isrsafe(displayHeapSettings.quadHdBuffers.pixelFormat, &mPixelFormat);
    if (rc) {rc = BERR_TRACE(rc);goto error;}
    rc = NEXUS_P_VideoFormat_ToMagnum_isrsafe(displayHeapSettings.quadHdBuffers.format, &mVideoFormat);
    if (rc) {rc = BERR_TRACE(rc);goto error;}
    vdcCfg.stHeapSettings.ePixelFormat_4HD = mPixelFormat;
    vdcCfg.stHeapSettings.eBufferFormat_4HD = mVideoFormat;
    vdcCfg.stHeapSettings.ulBufferCnt_4HD = displayHeapSettings.quadHdBuffers.count;
    vdcCfg.stHeapSettings.ulBufferCnt_4HD_Pip = displayHeapSettings.quadHdBuffers.pipCount;

    rc = NEXUS_P_PixelFormat_ToMagnum_isrsafe(displayHeapSettings.fullHdBuffers.pixelFormat, &mPixelFormat);
    if (rc) {rc = BERR_TRACE(rc);goto error;}
    rc = NEXUS_P_VideoFormat_ToMagnum_isrsafe(displayHeapSettings.fullHdBuffers.format, &mVideoFormat);
    if (rc) {rc = BERR_TRACE(rc);goto error;}
    vdcCfg.stHeapSettings.ePixelFormat_2HD = mPixelFormat;
    vdcCfg.stHeapSettings.eBufferFormat_2HD = mVideoFormat;
    vdcCfg.stHeapSettings.ulBufferCnt_2HD = displayHeapSettings.fullHdBuffers.count;
    vdcCfg.stHeapSettings.ulBufferCnt_2HD_Pip = displayHeapSettings.fullHdBuffers.pipCount;

    rc = NEXUS_P_PixelFormat_ToMagnum_isrsafe(displayHeapSettings.hdBuffers.pixelFormat, &mPixelFormat);
    if (rc) {rc = BERR_TRACE(rc);goto error;}
    rc = NEXUS_P_VideoFormat_ToMagnum_isrsafe(displayHeapSettings.hdBuffers.format, &mVideoFormat);
    if (rc) {rc = BERR_TRACE(rc);goto error;}
    vdcCfg.stHeapSettings.ePixelFormat_HD = mPixelFormat;
    vdcCfg.stHeapSettings.eBufferFormat_HD = mVideoFormat;
    vdcCfg.stHeapSettings.ulBufferCnt_HD = displayHeapSettings.hdBuffers.count;
    vdcCfg.stHeapSettings.ulBufferCnt_HD_Pip = displayHeapSettings.hdBuffers.pipCount;

    rc = NEXUS_P_PixelFormat_ToMagnum_isrsafe(displayHeapSettings.sdBuffers.pixelFormat, &mPixelFormat);
    if (rc) {rc = BERR_TRACE(rc);goto error;}
    rc = NEXUS_P_VideoFormat_ToMagnum_isrsafe(displayHeapSettings.sdBuffers.format, &mVideoFormat);
    if (rc) {rc = BERR_TRACE(rc);goto error;}
    vdcCfg.stHeapSettings.ePixelFormat_SD = mPixelFormat;
    vdcCfg.stHeapSettings.eBufferFormat_SD = mVideoFormat;
    vdcCfg.stHeapSettings.ulBufferCnt_SD = displayHeapSettings.sdBuffers.count;
    vdcCfg.stHeapSettings.ulBufferCnt_SD_Pip = displayHeapSettings.sdBuffers.pipCount;

    BDBG_MSG(("Creating VDC heap %d: SD %u, HD %u, 2HD %u, SD_PIP %u, HD_PIP %u, 2HD_PIP %u",
              openSlot, vdcCfg.stHeapSettings.ulBufferCnt_SD, vdcCfg.stHeapSettings.ulBufferCnt_HD,
              vdcCfg.stHeapSettings.ulBufferCnt_2HD,vdcCfg.stHeapSettings.ulBufferCnt_SD_Pip,
              vdcCfg.stHeapSettings.ulBufferCnt_HD_Pip,vdcCfg.stHeapSettings.ulBufferCnt_2HD_Pip));

    rc = BVDC_Heap_Create(state->vdc, &state->vdcHeapMap[openSlot].vdcHeap,
        NEXUS_Heap_GetMmaHandle(heap), &vdcCfg.stHeapSettings);
    if (rc) {rc = BERR_TRACE(rc);goto error;}

    state->vdcHeapMap[openSlot].settings = displayHeapSettings;
    state->vdcHeapMap[openSlot].nexusHeap = heap;
    state->vdcHeapMap[openSlot].refcnt = 1;

    return state->vdcHeapMap[openSlot].vdcHeap;

error:
    BDBG_ERR(("Unable to create a display heap for this operation. User must call NEXUS_Heap_SetDisplayHeapSettings with correct settings beforehand."));
    return NULL;
}

/**************************
BBS VideoTool backdoor

These functions provide the BBS VideoTool raw access to VDC, REG, RDC and MEM along with a mutex which protects them.
This is not a public API and is subject to change.
**************************/

void BVideoTool_LockDisplay(void)
{
    NEXUS_Module_Lock(g_NEXUS_displayModuleHandle);
}

void BVideoTool_UnlockDisplay(void)
{
    NEXUS_Module_Unlock(g_NEXUS_displayModuleHandle);
}

typedef struct BVideoToolDisplayHandles {
    BVDC_Handle vdc;
    BRDC_Handle rdc;
    BREG_Handle reg;
    BMEM_Heap_Handle heap;
} BVideoToolDisplayHandles;

void BVideoTool_GetDisplayHandles(BVideoToolDisplayHandles *pDisplayHandles)
{
    pDisplayHandles->vdc = g_NEXUS_DisplayModule_State.vdc;
    pDisplayHandles->rdc = g_NEXUS_DisplayModule_State.rdc;
    pDisplayHandles->reg = g_pCoreHandles->reg;
    pDisplayHandles->heap = g_pCoreHandles->heap[g_NEXUS_DisplayModule_State.moduleSettings.primaryDisplayHeapIndex].mem;
}

/**
Summary:
Get the settings that were used in NEXUS_DisplayModule_Init.

Description:
These cannot be changed without calling NEXUS_DisplayModule_Uninit then NEXUS_DisplayModule_Init.
This is for informational purposes.
**/
NEXUS_Error NEXUS_DisplayModule_GetMemorySettings(
    unsigned configurationId,                           /* Configuration ID */
    uint32_t mask,                                      /* Must contain at least one window and at least one input */
    NEXUS_DisplayBufferTypeSettings *pFullHdBuffers,    /* [out] Full HD buffer requirements */
    NEXUS_DisplayBufferTypeSettings *pHdBuffers,        /* [out] HD buffer requirements */
    NEXUS_DisplayBufferTypeSettings *pSdBuffers,        /* [out] SD buffer requirements */
    unsigned *pHeapSize                                 /* [out] Heap size in bytes */
    )
{
    BSTD_UNUSED(configurationId);
    BSTD_UNUSED(mask);
    BSTD_UNUSED(pFullHdBuffers);
    BSTD_UNUSED(pHdBuffers);
    BSTD_UNUSED(pSdBuffers);
    BSTD_UNUSED(pHeapSize);
    return BERR_TRACE(BERR_NOT_SUPPORTED);
}

void NEXUS_DisplayModule_SetVideoDecoderModule( NEXUS_ModuleHandle videoDecoder )
{
    g_NEXUS_DisplayModule_State.modules.videoDecoder = videoDecoder;
}

NEXUS_Error NEXUS_DisplayModule_SetConfigurationId( unsigned configurationId )
{
    BSTD_UNUSED(configurationId);
    return BERR_TRACE(NEXUS_NOT_SUPPORTED);
}

const char *g_videoOutputStr[NEXUS_VideoOutputType_eMax] = {"composite", "svideo", "component", "rfm", "hdmi", "hdmi_dvo", "ccir656"};
const char *g_videoInputStr[NEXUS_VideoInputType_eMax] = {"decoder", "ccir656", "hdmi", "image", "hddvi"};

NEXUS_Error NEXUS_DisplayModule_GetStatus_priv(NEXUS_DisplayModuleStatus *pStatus)
{
    NEXUS_ASSERT_MODULE();
    BKNI_Memset(pStatus, 0, sizeof(*pStatus));
#if BRDC_USE_CAPTURE_BUFFER
    pStatus->rulCapture.memory = g_rdc_capture.memory;
    if (pStatus->rulCapture.memory) {
        NEXUS_OBJECT_REGISTER(NEXUS_MemoryBlock, pStatus->rulCapture.memory, Acquire);
    }
    pStatus->rulCapture.offset = 0; /* dedicated MemoryBlock */
    pStatus->rulCapture.size = g_rdc_capture.bufferSize;
    pStatus->rulCapture.elementSize = NEXUS_RDC_CAPTURE_SIZE;
#endif

    return 0;
}

static void NEXUS_P_SetDisplayCapabilities(void)
{
    NEXUS_DisplayCapabilities *pCapabilities = &pVideo->cap;
    BVDC_Display_Capabilities vdcDisplayCap;
    BVDC_Capabilities vdcCap;
    const NEXUS_DisplayModuleSettings *pSettings = &pVideo->moduleSettings;
    int rc;
    unsigned i, j;

    if (!g_pCoreHandles->boxConfig->stBox.ulBoxId) {
        if(pSettings->fullHdBuffers.count || pSettings->hdBuffers.count || pSettings->sdBuffers.count ||
           pSettings->fullHdBuffers.pipCount || pSettings->hdBuffers.pipCount || pSettings->sdBuffers.pipCount){
            /* for non-memconfig platforms */
            pCapabilities->numDisplays = pSettings->legacy.numDisplays;
            for (j=0;j<pCapabilities->numDisplays;j++) {
                pCapabilities->display[j].numVideoWindows = pSettings->legacy.numWindowsPerDisplay;
            }
        }
        else {
            /* use per-window heaps to determine runtime display/window support. assume packed arrays. */
            for (j=0;j<NEXUS_MAX_DISPLAYS;j++) {
                for (i=0;i<NEXUS_MAX_VIDEO_WINDOWS;i++) {
                    if (pSettings->videoWindowHeapIndex[j][i] >= NEXUS_MAX_HEAPS) break;
                    pCapabilities->display[j].numVideoWindows++;
                }
                if (i > 0) pCapabilities->numDisplays++;
            }
        }
        for (j=0;j<NEXUS_MAX_DISPLAYS;j++) {
/* hardcode pre-boxmode graphics limits here */
#if BCHP_CHIP == 7425 || BCHP_CHIP == 7400
            /* 7425 GFD2 (used with VCE 1) doesn't have GFD bandwidth */
            if (j != 2) {
                pCapabilities->display[j].graphics.width = 1920;
                pCapabilities->display[j].graphics.height = 1080;
            }
#else
            /* no box modes, so just put in 40nm max numbers */
            pCapabilities->display[j].graphics.width = 720;
            pCapabilities->display[j].graphics.height = 480;
#endif
        }
    }
    else {
        /* report based on box modes */
        for (j=0;j<NEXUS_MAX_DISPLAYS;j++) {
            const BBOX_Vdc_Source_Capabilities *sourceCap;
            for (i=0;i<NEXUS_NUM_VIDEO_WINDOWS;i++) {
                if (!g_pCoreHandles->boxConfig->stVdc.astDisplay[j].astWindow[i].bAvailable) break;
                pCapabilities->display[j].numVideoWindows++;
            }
            if (i > 0) pCapabilities->numDisplays++;
            sourceCap = &g_pCoreHandles->boxConfig->stVdc.astSource[BAVC_SourceId_eGfx0 + j];
            if (sourceCap->bAvailable) {
                if (sourceCap->stSizeLimits.ulWidth == BBOX_VDC_DISREGARD) {
                    /* BBOX_VDC_DISREGARD means "BBOX doesn't have info", so use hardcoded max numbers */
                    pCapabilities->display[j].graphics.width = 1920;
                    pCapabilities->display[j].graphics.height = 1080;
                }
                else {
                    pCapabilities->display[j].graphics.width =  sourceCap->stSizeLimits.ulWidth;
                    pCapabilities->display[j].graphics.height = sourceCap->stSizeLimits.ulHeight;
                }
            }
        }
    }
    rc = BVDC_Display_GetCapabilities(NULL /* generic capabilities */, &vdcDisplayCap);
    if (!rc) {
        unsigned i;
        for (i=0;i<BFMT_VideoFmt_eMaxCount;i++) {
            pCapabilities->displayFormatSupported[NEXUS_P_VideoFormat_FromMagnum_isrsafe(i)] = vdcDisplayCap.pfIsVidfmtSupported(i);
        }
    }
}

void NEXUS_GetDisplayCapabilities( NEXUS_DisplayCapabilities *pCapabilities )
{
    *pCapabilities = pVideo->cap;
}

bool NEXUS_Display_P_HasOutput_isr(NEXUS_DisplayHandle display, NEXUS_VideoOutputType type)
{
   BSTD_UNUSED(display);
   BSTD_UNUSED(type);
   return false;
}

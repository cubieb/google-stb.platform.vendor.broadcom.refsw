/******************************************************************************
 * Broadcom Proprietary and Confidential. (c) 2016 Broadcom. All rights reserved.
 *
 * This program is the proprietary software of Broadcom and/or its
 * licensors, and may only be used, duplicated, modified or distributed pursuant
 * to the terms and conditions of a separate, written license agreement executed
 * between you and Broadcom (an "Authorized License").  Except as set forth in
 * an Authorized License, Broadcom grants no license (express or implied), right
 * to use, or waiver of any kind with respect to the Software, and Broadcom
 * expressly reserves all rights in and to the Software and all intellectual
 * property rights therein.  IF YOU HAVE NO AUTHORIZED LICENSE, THEN YOU
 * HAVE NO RIGHT TO USE THIS SOFTWARE IN ANY WAY, AND SHOULD IMMEDIATELY
 * NOTIFY BROADCOM AND DISCONTINUE ALL USE OF THE SOFTWARE.
 *
 * Except as expressly set forth in the Authorized License,
 *
 * 1. This program, including its structure, sequence and organization,
 *    constitutes the valuable trade secrets of Broadcom, and you shall use all
 *    reasonable efforts to protect the confidentiality thereof, and to use
 *    this information only in connection with your use of Broadcom integrated
 *    circuit products.
 *
 * 2. TO THE MAXIMUM EXTENT PERMITTED BY LAW, THE SOFTWARE IS PROVIDED "AS IS"
 *    AND WITH ALL FAULTS AND BROADCOM MAKES NO PROMISES, REPRESENTATIONS OR
 *    WARRANTIES, EITHER EXPRESS, IMPLIED, STATUTORY, OR OTHERWISE, WITH RESPECT
 *    TO THE SOFTWARE.  BROADCOM SPECIFICALLY DISCLAIMS ANY AND ALL IMPLIED
 *    WARRANTIES OF TITLE, MERCHANTABILITY, NONINFRINGEMENT, FITNESS FOR A
 *    PARTICULAR PURPOSE, LACK OF VIRUSES, ACCURACY OR COMPLETENESS, QUIET
 *    ENJOYMENT, QUIET POSSESSION OR CORRESPONDENCE TO DESCRIPTION. YOU ASSUME
 *    THE ENTIRE RISK ARISING OUT OF USE OR PERFORMANCE OF THE SOFTWARE.
 *
 * 3. TO THE MAXIMUM EXTENT PERMITTED BY LAW, IN NO EVENT SHALL BROADCOM OR ITS
 *    LICENSORS BE LIABLE FOR (i) CONSEQUENTIAL, INCIDENTAL, SPECIAL, INDIRECT,
 *    OR EXEMPLARY DAMAGES WHATSOEVER ARISING OUT OF OR IN ANY WAY RELATING TO
 *    YOUR USE OF OR INABILITY TO USE THE SOFTWARE EVEN IF BROADCOM HAS BEEN
 *    ADVISED OF THE POSSIBILITY OF SUCH DAMAGES; OR (ii) ANY AMOUNT IN EXCESS
 *    OF THE AMOUNT ACTUALLY PAID FOR THE SOFTWARE ITSELF OR U.S. $1, WHICHEVER
 *    IS GREATER. THESE LIMITATIONS SHALL APPLY NOTWITHSTANDING ANY FAILURE OF
 *    ESSENTIAL PURPOSE OF ANY LIMITED REMEDY.
 *****************************************************************************/

#include "atlas_main.h"
#include "display.h"

BDBG_MODULE(atlas_main);

CAtlas::CAtlas(
        uint16_t      number,
        eAtlasMode    mode,
        CChannelMgr * pChannelMgr,
#if DVR_LIB_SUPPORT
        CDvrMgr *     pDvrMgr,
#endif
        CLua *        pLua
        ) :
    _pConfig(NULL),
    _pCfg(NULL),
    _pBoardResources(NULL),
    _pWidgetEngine(NULL),
    _number(number),
    _mode(mode),
    _pChannelMgr(pChannelMgr),
#if DVR_LIB_SUPPORT
    _pDvrMgr(pDvrMgr),
#endif
    _pLua(pLua),
    _pControl(NULL),
    _model("CAtlas::_model"),
    _pBackgroundScreen(NULL),
    _pMainScreen(NULL)
{
    BDBG_ASSERT(NULL != _pChannelMgr);
    _model.setId(this);
}

CAtlas::~CAtlas()
{
}

static void idle_callback(
        bwidget_engine_t engine,
        void *           context,
        int              param
        )
{
    CAtlas * pAtlas = (CAtlas *)context;

    BDBG_ASSERT(NULL != pAtlas);
    CControl * pControl = pAtlas->getControl();

    BSTD_UNUSED(param);
    BSTD_UNUSED(engine);

    /* controller will handle idle loop processing */
    pControl->onIdle();
}

CControl * CAtlas::controlCreate()
{
    return(new CControl("CAtlas::pControl"));
}

void CAtlas::controlDestroy(CControl * pControl)
{
    DEL(pControl);
}

CDisplay * CAtlas::displayCreate()
{
    eRet       ret      = eRet_Ok;
    CDisplay * pDisplay = NULL;

    pDisplay = (CDisplay *)_pBoardResources->checkoutResource(this, eBoardResource_display);
    CHECK_PTR_ERROR_GOTO("unable to checkout display", pDisplay, ret, eRet_NotAvailable, error);

    _model.addDisplay(pDisplay);

error:
    return(pDisplay);
}

void CAtlas::displayDestroy(CDisplay * pDisplay)
{
    if (NULL == pDisplay)
    {
        return;
    }

    _model.removeDisplay(pDisplay);
    _pBoardResources->checkinResource(pDisplay);
}

CDisplay * CAtlas::displayInitialize(NEXUS_VideoFormat videoFormat, uint32_t framebufferWidth, uint32_t framebufferHeight)
{
    CDisplay * pDisplay = NULL;
    eRet       ret      = eRet_Ok;

    pDisplay = displayCreate();
    CHECK_PTR_ERROR_GOTO("unable to checkout display", pDisplay, ret, eRet_NotAvailable, error);

    if ((true  == pDisplay->isReservedForEncoder()) || (false == pDisplay->isSupported()))
    {
        BDBG_WRN(("Display%d is NOT supported or is dedicated for encoder use only and will NOT be set up as a slave display", pDisplay->getNumber()));
        goto error;
    }

    /* set preferred video format */
    if ((NEXUS_VideoFormat_eUnknown == videoFormat) ||
        (NEXUS_VideoFormat_eMax == videoFormat))
    {
        BDBG_WRN(("Invalid video format given"));
        goto error;
    }

    pDisplay->setDefaultFormat(videoFormat);
    pDisplay->setMaxGraphicsGeometry(MRect(0, 0, framebufferWidth, framebufferHeight));
    pDisplay->setModel(&_model);

    ret = pDisplay->open();
    CHECK_ERROR_GOTO("display failed to open", ret, error);

    goto done;
error:
    displayUninitialize(&pDisplay);
done:
    return(pDisplay);
}

void CAtlas::displayUninitialize(CDisplay ** pDisplay)
{
    if ((NULL == pDisplay) || (NULL == *pDisplay))
    {
        return;
    }

    (*pDisplay)->close();
    displayDestroy(*pDisplay);
    *pDisplay = NULL;
}

CGraphics * CAtlas::graphicsCreate()
{
    eRet        ret       = eRet_Ok;
    CGraphics * pGraphics = NULL;

    pGraphics = (CGraphics *)_pBoardResources->checkoutResource(this, eBoardResource_graphics);
    CHECK_PTR_ERROR_GOTO("unable to checkout graphics", pGraphics, ret, eRet_NotAvailable, error);

    _model.addGraphics(pGraphics);
error:
    return(pGraphics);
}

void CAtlas::graphicsDestroy(CGraphics * pGraphics)
{
    if (NULL == pGraphics)
    {
        return;
    }

    _model.removeGraphics(pGraphics);
    _pBoardResources->checkinResource(pGraphics);
}

CGraphics * CAtlas::graphicsInitialize(CDisplay * pDisplayHD, CDisplay * pDisplaySD)
{
    eRet        ret       = eRet_Ok;
    CGraphics * pGraphics = NULL;

    /* open graphics resource */
    {
        pGraphics = graphicsCreate();

        ret = pGraphics->open(_pConfig);
        CHECK_ERROR_GOTO("graphics failed to open", ret, error);
        pGraphics->setModel(&_model);
        pGraphics->setDisplays(pDisplayHD, pDisplaySD);

        ret = pGraphics->initGraphics(GET_INT(_pCfg, GRAPHICS_SURFACE_WIDTH), GET_INT(_pCfg, GRAPHICS_SURFACE_HEIGHT));
        CHECK_ERROR_GOTO("graphics initialization failed", ret, error);
    }

    /* open bwidgets */
    {
        bwidget_engine_settings settings;
        settings.idle    = idle_callback;
        settings.context = this;
        settings.param   = 0;

        _pWidgetEngine = new CWidgetEngine("widgetEngine", _pCfg);
        CHECK_PTR_ERROR_GOTO("unable to allocate widget engine", _pWidgetEngine, ret, eRet_OutOfMemory, error);

        ret = _pWidgetEngine->open(pGraphics->getWinEngine(), &settings);
        CHECK_ERROR_GOTO("Unable to open widget engine", ret, error);
    }

    goto done;
error:
    graphicsUninitialize();
done:
    return(pGraphics);
}

void CAtlas::graphicsUninitialize()
{
    CGraphics * pGraphics = _model.getGraphics();

    if (NULL != _pWidgetEngine)
    {
        _pWidgetEngine->close();
        DEL(_pWidgetEngine);
    }
    if (NULL != pGraphics)
    {
        graphicsDestroy(pGraphics);
        pGraphics->close();
        pGraphics = NULL;
    }
}

CIrRemote * CAtlas::irRemoteCreate()
{
    eRet         ret        = eRet_Ok;
    CIrRemote * pIrRemote = NULL;

    pIrRemote = (CIrRemote *)_pBoardResources->checkoutResource(this, eBoardResource_irRemote);
    CHECK_PTR_ERROR_GOTO("unable to checkout Ir remote", pIrRemote, ret, eRet_NotAvailable, error);

    _model.addIrRemote(pIrRemote);
error:
    return(pIrRemote);
}

void CAtlas::irRemoteDestroy(CIrRemote * pRemote)
{
    if (NULL != pRemote)
    {
        _model.removeIrRemote(pRemote);
        _pBoardResources->checkinResource(pRemote);
        pRemote = NULL;
    }
}

CIrRemote * CAtlas::irRemoteInitialize()
{
    eRet        retIR     = eRet_Ok;
    CIrRemote * pIrRemote = NULL;

    /* open ir remote if reserved for us */
    pIrRemote = irRemoteCreate();
    if (NULL != pIrRemote)
    {
        retIR = pIrRemote->open(_pWidgetEngine);
        CHECK_ERROR_GOTO("ir remote failed to open", retIR, errorIR);
        pIrRemote->setMode(stringToIrRemoteType(GET_STR(_pCfg, REMOTE_TYPE_PRIMARY)));
    }

    goto doneIR;
errorIR:
    irRemoteDestroy(pIrRemote);
    pIrRemote = NULL;
doneIR:
    return(pIrRemote);
}

void CAtlas::irRemoteUninitialize()
{
    CIrRemote * pRemote = _model.getIrRemote();

    if (NULL == pRemote)
    {
        return;
    }

    pRemote->close();
    _model.removeIrRemote(pRemote);
    irRemoteDestroy(pRemote);
    pRemote = NULL;
}

#if RF4CE_SUPPORT
CRf4ceRemote * CAtlas::rf4ceRemoteCreate()
{
    eRet         ret        = eRet_Ok;
    CRf4ceRemote * pRf4ceRemote = NULL;

    pRf4ceRemote = (CRf4ceRemote *)_pBoardResources->checkoutResource(this, eBoardResource_rf4ceRemote);
    CHECK_PTR_ERROR_GOTO("unable to checkout Rf4ce remote", pRf4ceRemote, ret, eRet_NotAvailable, error);

    _model.addRf4ceRemote(pRf4ceRemote);
error:
    return(pRf4ceRemote);
}

void CAtlas::rf4ceRemoteDestroy(CRf4ceRemote * pRemote)
{
    if (NULL != pRemote)
    {
        _model.removeRf4ceRemote(pRemote);
        _pBoardResources->checkinResource(pRemote);
        pRemote = NULL;
    }
}

CRf4ceRemote * CAtlas::rf4ceRemoteInitialize()
{
    eRet           retRF4CE     = eRet_Ok;
    CRf4ceRemote * pRf4ceRemote = NULL;

    /* open rf4ce remote if reserved for us */
    pRf4ceRemote = rf4ceRemoteCreate();
    if (NULL != pRf4ceRemote)
    {
        retRF4CE = pRf4ceRemote->open(_pWidgetEngine);
        CHECK_ERROR_GOTO("rf4ce remote failed to open", retRF4CE, error);
    }

    goto done;
error:
    rf4ceRemoteDestroy(pRf4ceRemote);
    pRf4ceRemote = NULL;
done:
    return(pRf4ceRemote);
}

void CAtlas::rf4ceRemoteUninitialize()
{
    CRf4ceRemote * pRemote = _model.getRf4ceRemote();

    if (NULL == pRemote)
    {
        return;
    }

    pRemote->close();
    _model.removeRf4ceRemote(pRemote);
    rf4ceRemoteDestroy(pRemote);
    pRemote = NULL;
}
#endif

#if NEXUS_HAS_UHF_INPUT
CUhfRemote * CAtlas::uhfRemoteCreate()
{
    eRet         ret        = eRet_Ok;
    CUhfRemote * pUhfRemote = NULL;

    pUhfRemote = (CUhfRemote *)_pBoardResources->checkoutResource(this, eBoardResource_uhfRemote);
    CHECK_PTR_ERROR_GOTO("unable to checkout uhf remote", pUhfRemote, ret, eRet_NotAvailable, error);

    _model.addUhfRemote(pUhfRemote);
error:
    return(pUhfRemote);
}

void CAtlas::uhfRemoteDestroy(CUhfRemote * pRemote)
{
    if (NULL != pRemote)
    {
        _model.removeUhfRemote(pRemote);
        _pBoardResources->checkinResource(pRemote);
        pRemote = NULL;
    }
}

CUhfRemote * CAtlas::uhfRemoteInitialize()
{
    eRet         retUHF     = eRet_Ok;
    CUhfRemote * pUhfRemote = NULL;

    /* open uhf remote if reserved for us */
    pUhfRemote = uhfRemoteCreate();
    if (NULL != pUhfRemote)
    {
        pUhfRemote->setChannel(stringToUhfChannel(GET_STR(_pCfg, REMOTE_TYPE_SECONDARY)));
        retUHF = pUhfRemote->open(_pWidgetEngine);
        CHECK_ERROR_GOTO("Uhf remote failed to open", retUHF, error);
    }

    goto done;
error:
    uhfRemoteDestroy(pUhfRemote);
    pUhfRemote = NULL;
done:
    return(pUhfRemote);
}

void CAtlas::uhfRemoteUninitialize()
{
    CUhfRemote * pRemote = _model.getUhfRemote();

    if (NULL == pRemote)
    {
        return;
    }

    pRemote->close();
    _model.removeUhfRemote(pRemote);
    uhfRemoteDestroy(pRemote);
    pRemote = NULL;
}
#endif

CVideoWindow * CAtlas::videoWindowInitialize(CDisplay * pDisplay, CSimpleVideoDecode * pVideoDecode, eWindowType windowType)
{
    eRet           ret          = eRet_Ok;
    CVideoWindow * pVideoWindow = NULL;

    if ((NULL == pDisplay) || (NULL == pVideoDecode))
    {
        return(pVideoWindow);
    }

    /* connect decoder to display */
    pVideoWindow = pDisplay->checkoutVideoWindow();
    CHECK_PTR_ERROR_GOTO("unable to check out video window", pVideoWindow, ret, eRet_NotAvailable, error);

    ret = pVideoWindow->open();
    CHECK_ERROR_GOTO("video window failed to open", ret, error);
    ret = pVideoDecode->addVideoWindow(pVideoWindow);
    CHECK_ERROR_GOTO("unable to add video window to decoder", ret, error);
    pVideoWindow->setType(windowType);
    pVideoWindow->setVisible((eWindowType_Main == windowType) ? true : false);

    goto done;
error:
    videoWindowUninitialize(pDisplay, pVideoDecode, pVideoWindow);
    pVideoWindow = NULL;
done:
    return(pVideoWindow);
}

void CAtlas::videoWindowUninitialize(CDisplay * pDisplay, CSimpleVideoDecode * pVideoDecode, CVideoWindow * pVideoWindow)
{
    if ((NULL == pDisplay) || (NULL == pVideoDecode) || (NULL == pVideoWindow))
    {
        return;
    }

    pVideoDecode->removeVideoWindow(pVideoWindow);
    pVideoWindow->close();
    pDisplay->checkinVideoWindow(pVideoWindow);
    pVideoWindow = NULL;
}

CStc * CAtlas::stcInitialize(eWindowType windowType)
{
    eRet   ret  = eRet_Ok;
    CStc * pStc = NULL;

    /* open STC channel for a/v sync */
    pStc = (CStc *)_pBoardResources->checkoutResource(this, eBoardResource_stcChannel);
    CHECK_PTR_ERROR_GOTO("unable to checkout stc channel", pStc, ret, eRet_NotAvailable, error);

    ret = pStc->open();
    CHECK_ERROR_GOTO("stc failed to open", ret, error);

    _model.addStc(pStc, windowType);

    goto done;
error:
    stcUninitialize(&pStc, windowType);
done:
    return(pStc);
}

void CAtlas::stcUninitialize(
        CStc **     pStc,
        eWindowType windowType
        )
{
    if ((NULL == pStc) || (NULL == *pStc)|| (eWindowType_Max == windowType))
    {
        return;
    }

    _model.removeStc(windowType);
    (*pStc)->close();
    _pBoardResources->checkinResource(*pStc);
    *pStc = NULL;
}

CSimpleVideoDecode * CAtlas::videoDecodeCreate(eWindowType windowType)
{
    eRet                 ret          = eRet_Ok;
    CSimpleVideoDecode * pVideoDecode = NULL;

    pVideoDecode = (CSimpleVideoDecode *)_pBoardResources->checkoutResource(this, eBoardResource_simpleDecodeVideo);
    CHECK_PTR_ERROR_GOTO("unable to checkout simple video decoder", pVideoDecode, ret, eRet_NotAvailable, error);

    _model.addSimpleVideoDecode(pVideoDecode, windowType);
error:
    return(pVideoDecode);
}

void CAtlas::videoDecodeDestroy(eWindowType windowType)
{
    CSimpleVideoDecode * pVideoDecode = NULL;

    pVideoDecode = _model.getSimpleVideoDecode(windowType);
    _model.removeSimpleVideoDecode(windowType);

    _pBoardResources->checkinResource(pVideoDecode);
}

CSimpleVideoDecode * CAtlas::videoDecodeInitialize(CStc * pStc, eWindowType windowType)
{
    eRet                 ret          = eRet_Ok;
    CSimpleVideoDecode * pVideoDecode = NULL;

    if (NULL == pStc)
    {
        return(NULL);
    }

    /* add/setup  decode if available or reserved for us */
    pVideoDecode = videoDecodeCreate(windowType);
    CHECK_PTR_ERROR_GOTO("unable to checkout simple video decoder", pVideoDecode, ret, eRet_NotAvailable, error);

    pVideoDecode->setResources(this, _pBoardResources);
    pVideoDecode->setModel(&_model);
    pVideoDecode->setWindowType(windowType);

    ret = pVideoDecode->open(_pWidgetEngine, pStc);
    CHECK_ERROR_GOTO("video decode failed to open", ret, error);

    if (eWindowType_Main == windowType)
    {
        /* set color depth on main decoder only */
        pVideoDecode->setColorDepth(GET_INT(_pCfg, DECODER_COLOR_DEPTH));
    }

    goto done;
error:
    videoDecodeUninitialize(&pVideoDecode);
    pVideoDecode = NULL;
done:
    return(pVideoDecode);
}

void CAtlas::videoDecodeUninitialize(CSimpleVideoDecode ** pVideoDecode)
{
    if ((NULL == pVideoDecode) || (NULL == *pVideoDecode))
    {
        return;
    }

    (*pVideoDecode)->close();

    if (_model.getSimpleVideoDecode(eWindowType_Main) == *pVideoDecode)
    {
        videoDecodeDestroy(eWindowType_Main);
    }
    if (_model.getSimpleVideoDecode(eWindowType_Pip) == *pVideoDecode)
    {
        videoDecodeDestroy(eWindowType_Pip);
    }
    *pVideoDecode = NULL;
}

CSimpleAudioDecode * CAtlas::audioDecodeCreate(eWindowType windowType)
{
    eRet                 ret          = eRet_Ok;
    CSimpleAudioDecode * pAudioDecode = NULL;

    pAudioDecode = (CSimpleAudioDecode *)_pBoardResources->checkoutResource(this, eBoardResource_simpleDecodeAudio);
    CHECK_PTR_WARN_GOTO("unable to checkout simple audio decoder", pAudioDecode, ret, eRet_NotAvailable, error);

    /* add audio decode to model for main */
    _model.addSimpleAudioDecode(pAudioDecode, windowType);
error:
    return(pAudioDecode);
}

void CAtlas::audioDecodeDestroy(eWindowType windowType)
{
    CSimpleAudioDecode * pAudioDecode = NULL;

    pAudioDecode = _model.getSimpleAudioDecode(windowType);
    if (NULL != pAudioDecode)
    {
        _model.removeSimpleAudioDecode(windowType);
        _pBoardResources->checkinResource(pAudioDecode);
    }
}

CSimpleAudioDecode * CAtlas::audioDecodeInitialize(
            COutputHdmi *     pOutputHdmi,
            COutputSpdif *    pOutputSpdif,
            COutputAudioDac * pOutputAudioDac,
            COutputRFM *      pOutputRFM,
            CStc *            pStc,
            eWindowType       winType)
{
    eRet                 ret          = eRet_Ok;
    CSimpleAudioDecode * pAudioDecode = NULL;

    if (NULL == pStc)
    {
        return(NULL);
    }

    pAudioDecode = audioDecodeCreate(winType);
    CHECK_PTR_ERROR_GOTO("unable to create simple audio decoder", pAudioDecode, ret, eRet_NotAvailable, error);

    /* simple decoder will connect decoders and outputs */
    pAudioDecode->setResources(this, _pBoardResources);
    pAudioDecode->setModel(&_model);
    pAudioDecode->setWindowType(winType);

    /* give audio outputs to simple audio decoder */
    if (NULL != pOutputHdmi) { pAudioDecode->setOutputHdmi(pOutputHdmi); }
    if (NULL != pOutputSpdif) { pAudioDecode->setOutputSpdif(pOutputSpdif); }
    if (NULL != pOutputAudioDac) { pAudioDecode->setOutputDac(pOutputAudioDac); }
    if (NULL != pOutputRFM) { pAudioDecode->setOutputRFM(pOutputRFM); }

    ret = pAudioDecode->open(_pWidgetEngine, pStc);
    CHECK_ERROR_GOTO("audio decode failed to open", ret, error);

    goto done;
error:
    audioDecodeUninitialize(&pAudioDecode, winType);
done:
    return(pAudioDecode);
}

CSimpleAudioDecode * CAtlas::audioDecodeInitializePip(
            COutputHdmi *     pOutputHdmi,
            COutputSpdif *    pOutputSpdif,
            COutputAudioDac * pOutputAudioDac,
            COutputRFM *      pOutputRFM,
            CStc *            pStc,
            eWindowType       winType)
{
    BSTD_UNUSED(pOutputHdmi);
    BSTD_UNUSED(pOutputSpdif);
    BSTD_UNUSED(pOutputAudioDac);
    BSTD_UNUSED(pOutputRFM);
    BSTD_UNUSED(pStc);
    BSTD_UNUSED(winType);

    /* dedicated pip audio decoder only used in nxclient atlas mode.
       see CAtlasNx::audioDecodeInitializePip() */
    return(NULL);
}

void CAtlas::audioDecodeUninitialize(CSimpleAudioDecode ** pAudioDecode, eWindowType winType)
{
    if ((NULL == pAudioDecode) || (NULL == *pAudioDecode))
    {
        return;
    }

    (*pAudioDecode)->close();
    (*pAudioDecode)->setOutputHdmi(NULL);
    (*pAudioDecode)->setOutputSpdif(NULL);
    (*pAudioDecode)->setOutputDac(NULL);
    (*pAudioDecode)->setOutputRFM(NULL);

    audioDecodeDestroy(winType);
    *pAudioDecode = NULL;
}

#ifdef NETAPP_SUPPORT
eRet CAtlas::networkInitialize(void)
{
    eRet ret = eRet_Ok;
    CNetwork * pNetwork = NULL;

    pNetwork = (CNetwork *)_pBoardResources->checkoutResource(this, eBoardResource_network);
    if (NULL != pNetwork)
    {
        ret = pNetwork->open(_pWidgetEngine);
        CHECK_ERROR_GOTO("unable to open network object", ret, error);
        _pBoardResources->checkinResource(pNetwork);
    }
error:
    return(ret);
}

void CAtlas::networkUninitialize(void)
{
    CNetwork * pNetwork = NULL;

    pNetwork = (CNetwork *)_pBoardResources->checkoutResource(this, eBoardResource_network);
    if (NULL != pNetwork)
    {
        pNetwork->close();
        _pBoardResources->checkinResource(pNetwork);
        pNetwork = NULL;
    }

    return;
}

CBluetoothRemote * CAtlas::bluetoothRemoteInitialize(void)
{
    eRet               ret              = eRet_Ok;
    CBluetoothRemote * pBluetoothRemote = NULL;

    /* open bluetooth remote if reserved for us */
    pBluetoothRemote = (CBluetoothRemote *)_pBoardResources->checkoutResource(this, eBoardResource_bluetoothRemote);
    if (NULL != pBluetoothRemote)
    {
        /* add bluetooth remote to model */
        _model.addBluetoothRemote(pBluetoothRemote);

        ret = pBluetoothRemote->open(_pWidgetEngine);
        CHECK_ERROR_GOTO("bluetooth remote failed to open", ret, error);
    }

    goto done;
error:
    bluetoothRemoteUninitialize();
done:
    return(pBluetoothRemote);
}

void CAtlas::bluetoothRemoteUninitialize()
{
    CBluetoothRemote * pBluetoothRemote = _model.getBluetoothRemote();

    if (NULL == pBluetoothRemote)
    {
        return;
    }

    pBluetoothRemote->close();
    _model.removeBluetoothRemote(pBluetoothRemote);
    _pBoardResources->checkinResource(pBluetoothRemote);
    pBluetoothRemote = NULL;
}

CBluetooth * CAtlas::bluetoothCreate()
{
    eRet         ret        = eRet_Ok;
    CBluetooth * pBluetooth = NULL;

    pBluetooth = (CBluetooth *)_pBoardResources->checkoutResource(this, eBoardResource_bluetooth);
    CHECK_PTR_ERROR_GOTO("unable to checkout bluetooth", pBluetooth, ret, eRet_OutOfMemory, error);

error:
    return(pBluetooth);
}

void CAtlas::bluetoothDestroy(CBluetooth * pBluetooth)
{
    if (NULL != pBluetooth)
    {
        return;
    }

    _pBoardResources->checkinResource(pBluetooth);
}

CBluetooth * CAtlas::bluetoothInitialize()
{
    eRet         ret        = eRet_Ok;
    CBluetooth * pBluetooth = NULL;

    pBluetooth = bluetoothCreate();
    CHECK_PTR_ERROR_GOTO("unable to create bluetooth", pBluetooth, ret, eRet_OutOfMemory, error);

    ret = pBluetooth->open(_pWidgetEngine);
    CHECK_ERROR_GOTO("unable to open bluetooth object", ret, error);
    bluetoothDestroy(pBluetooth);

    goto done;
error:
    bluetoothUninitialize();
done:
    return(pBluetooth);
}

void CAtlas::bluetoothUninitialize()
{
    eRet         ret        = eRet_Ok;
    CBluetooth * pBluetooth = NULL;

    pBluetooth = bluetoothCreate();
    CHECK_PTR_ERROR_GOTO("unable to create bluetooth", pBluetooth, ret, eRet_OutOfMemory, error);

    pBluetooth->close();
    bluetoothDestroy(pBluetooth);
    pBluetooth = NULL;

error:
    return;
}

CAudioCapture * CAtlas::audioCaptureInitialize(CBluetooth * pBluetooth)
{
    BSTD_UNUSED(pBluetooth);
    return(NULL);
}

void CAtlas::audioCaptureUninitialize()
{
    return;
}
#endif /* NETAPP_SUPPORT */


#ifdef PLAYBACK_IP_SUPPORT
eRet CAtlas::ipServerInitialize()
{
    eRet ret = eRet_Ok;

    /* initialize server database */
    {
        CPlaylistDb * pPlaylistDb = NULL;
        pPlaylistDb = new CPlaylistDb("PlaylistDb", _pCfg);
        CHECK_PTR_ERROR_GOTO("unable to allocate Playlist database", pPlaylistDb, ret, eRet_OutOfMemory, error);

        pPlaylistDb->open(_pWidgetEngine);
        CHECK_ERROR_GOTO("unable to open playlist DB object", ret, error);
        _model.setPlaylistDb(pPlaylistDb);
    }

    /* initialize HTTP server */
    if (true == GET_BOOL(_pCfg, ATLAS_SERVER_ENABLED))
    {
        CServerMgr * pServerMgr = NULL;
        pServerMgr = new CServerMgr("CServerMgr", _pCfg);
        CHECK_PTR_ERROR_GOTO("unable to allocate server manager", pServerMgr, ret, eRet_OutOfMemory, error);

        ret = pServerMgr->open(_pWidgetEngine);
        CHECK_ERROR_GOTO("unable to open HTTP server object", ret, error);
        pServerMgr->setModel(&_model);
        _model.setServerMgr(pServerMgr);
    }
    /* intialize auto discovery client/server */
    {
        /* server */
        CAutoDiscoveryServer * pAutoDiscoveryServer = new CAutoDiscoveryServer("AutoDiscoveryServer", _pCfg);
        CHECK_PTR_ERROR_GOTO("unable to allocate auto discovery server", pAutoDiscoveryServer, ret, eRet_OutOfMemory, error);

        ret = pAutoDiscoveryServer->open(_pWidgetEngine);
        CHECK_ERROR_GOTO("unable to open auto discovery server object", ret, error);
        _model.setAutoDiscoveryServer(pAutoDiscoveryServer);

        /* client */
        CAutoDiscoveryClient * pAutoDiscoveryClient = new CAutoDiscoveryClient("AutoDiscoveryClient", _pCfg);
        CHECK_PTR_ERROR_GOTO("unable to allocate auto discovery client", pAutoDiscoveryClient, ret, eRet_OutOfMemory, error);

        ret = pAutoDiscoveryClient->open(_pWidgetEngine);
        CHECK_ERROR_GOTO("unable to open auto discovery client object", ret, error);
        pAutoDiscoveryClient->setModel(&_model);
        _model.setAutoDiscoveryClient(pAutoDiscoveryClient);
    }

    goto done;
error:
    ipServerUninitialize();
done:
    return(ret);
}

void CAtlas::ipServerUninitialize()
{
    CAutoDiscoveryClient * pAutoDiscoveryClient = _model.getAutoDiscoveryClient();
    CAutoDiscoveryServer * pAutoDiscoveryServer = _model.getAutoDiscoveryServer();
    CServerMgr *           pServerMgr           = _model.getServerMgr();
    CPlaylistDb *          pPlaylistDb          = _model.getPlaylistDb();

    if (NULL != pAutoDiscoveryClient)
    {
        _model.setAutoDiscoveryClient(NULL);
        pAutoDiscoveryClient->close();
        DEL(pAutoDiscoveryClient);
    }

    if (NULL != pAutoDiscoveryServer)
    {
        _model.setAutoDiscoveryServer(NULL);
        pAutoDiscoveryServer->close();
        DEL(pAutoDiscoveryServer);
    }

    if (NULL != pServerMgr)
    {
        _model.setServerMgr(NULL);
        pServerMgr->close();
        DEL(pServerMgr);
    }

    if (NULL != pPlaylistDb)
    {
        _model.setPlaylistDb(NULL);
        pPlaylistDb->close();
        DEL(pPlaylistDb);
    }
}

eRet CAtlas::ipServerStart()
{
    eRet                   ret                  = eRet_Ok;
    CServerMgr *           pServerMgr           = _model.getServerMgr();
    CAutoDiscoveryClient * pAutoDiscoveryClient = _model.getAutoDiscoveryClient();

    /* start atlas server manager */
    if (NULL != pServerMgr)
    {
        ret = pServerMgr->startHttpServer();
        CHECK_ERROR("unable to start ip http server", ret);
        ret = pServerMgr->startPlaylistServer();
        CHECK_ERROR("unable to start ip playlist server", ret);
    }

    /* start auto discovery client */
    if (NULL != pAutoDiscoveryClient)
    {
        ret = pAutoDiscoveryClient->start();
        CHECK_ERROR_GOTO("unable to start auto discovery client object", ret, error);
    }

error:
    return(ret);
}

eRet CAtlas::ipServerStop()
{
    eRet                   ret                  = eRet_Ok;
    CServerMgr *           pServerMgr           = _model.getServerMgr();
    CAutoDiscoveryClient * pAutoDiscoveryClient = _model.getAutoDiscoveryClient();

    /* stop atlas server manager */
    if (NULL != pServerMgr)
    {
        ret = pServerMgr->stopHttpServer();
        CHECK_ERROR("unable to stop ip http server", ret);
        ret = pServerMgr->stopPlaylistServer();
        CHECK_ERROR("unable to stop ip playlist server", ret);
    }

    /* stop auto discovery client */
    if (NULL != pAutoDiscoveryClient)
    {
        ret = pAutoDiscoveryClient->stop();
        CHECK_ERROR_GOTO("unable to stop auto discovery client object", ret, error);
    }

error:
    return(ret);
}
#endif

#ifdef SNMP_SUPPORT
eRet CAtlas::snmpInitialize()
{
    if (true == GET_BOOL(_pCfg, SNMP_ENABLED))
    {
        CSnmp * pSnmp = new CSnmp;
        pSnmp->snmp_save_control(_pControl);
        pSnmp->snmp_init(&_model);
        _model.addSnmp(pSnmp);
        return(eRet_Ok);
    }
    else
        return(eRet_NotSupported);
}

void CAtlas::snmpUninitialize()
{
    if (true == GET_BOOL(_pCfg, SNMP_ENABLED))
    {
        CSnmp * pSnmp = _model.getSnmp();
        if (NULL != pSnmp)
        {
            _model.removeSnmp(pSnmp);
            pSnmp->snmp_uninit();
            DEL(pSnmp);
        }
    }
}
#endif /* ifdef SNMP_SUPPORT */

eRet CAtlas::setPreferredVideoFormat(
                COutputHdmi *      pOutputHdmi,
                COutputComponent * pOutputComponent,
                COutputComposite * pOutputComposite,
                COutputRFM *       pOutputRFM)
{
    eRet        ret        = eRet_Ok;
    CDisplay *  pDisplayHD = _model.getDisplay(0);
    CDisplay *  pDisplaySD = _model.getDisplay(1);
    CGraphics * pGraphics  = _model.getGraphics();

    /* set preferred video format based on outputs - note that HDMI may override this on hotplug */
    if (NULL != pDisplayHD)
    {
        if (NULL != pOutputHdmi)
        {
            /* since we set the HD display default format before opening,
             * setting it again here will simply update the views (GUI) in this case */
            pDisplayHD->setFormat(pDisplayHD->getDefaultFormat(), pGraphics);

            /* force hotplug event (affects both HD and SD outputs) - will have no effect if HDMI is not connected */
            pOutputHdmi->triggerHotPlug();
        }
        else
        if (NULL != pOutputComponent)
        {
            pDisplayHD->setFormat(pOutputComponent->getPreferredVideoFormat(), pGraphics);
        }
    }

    if (NULL != pDisplaySD)
    {
        /* if hdmi does exists and is connected, then the HD and SD display format is set at the same time
         * so no need to set it again here */
        if ((NULL == pOutputHdmi) ||
            ((NULL != pOutputHdmi) && (false == pOutputHdmi->isConnected())))
        {
            /* no hdmi or disconnected, so set SD display format */
            if ((NULL != pOutputComposite) || (NULL != pOutputRFM))
            {
                pDisplaySD->setFormat(pOutputComposite->getPreferredVideoFormat(), pGraphics, false);
            }
        }

        /* update default vbi settings */
        {
            CDisplayVbiData data = pDisplaySD->getVbiSettings();
            pDisplaySD->setVbiSettings(&data);
        }
    }

    return(ret);
}

eRet CAtlas::guiInitialize(CConfig * pConfig, CGraphics * pGraphics)
{
    eRet ret = eRet_Ok;

    /* create full sized transparent background screen */
    _pBackgroundScreen = new CScreen("CAtlas::_pBackgroundScreen", _pWidgetEngine, pConfig, NULL, pGraphics->getWinFramebuffer());
    CHECK_PTR_ERROR_GOTO("background screen creation failed", _pBackgroundScreen, ret, eRet_OutOfMemory, error);
    ret = _pBackgroundScreen->initialize(&_model);
    CHECK_ERROR_GOTO("background screen failed to initialize", ret, error);
    _pBackgroundScreen->setBevel(0);

    /* create main window */
    _pMainScreen = new CScreenMain(_pWidgetEngine, pConfig, _pBackgroundScreen);
    CHECK_PTR_ERROR_GOTO("menu screen creation failed", _pMainScreen, ret, eRet_OutOfMemory, error);
    ret = _pMainScreen->initialize(&_model);
    CHECK_ERROR_GOTO("menu screen failed to initialize", ret, error);
    _pMainScreen->setBevel(0);

    _pControl->addView(_pMainScreen, "mainScreen");

    goto done;
error:
    guiUninitialize();
done:
    return(ret);
}

void CAtlas::guiUninitialize()
{
   _pControl->removeView(_pMainScreen);
   _pMainScreen->uninitialize();
   DEL(_pMainScreen);

   /* reparent pBackgroundScreen before destroying because all windows directly
    * descended from the framebuffer win don't seem to unlink automatically.
    * changing the parent win to NULL will force the unlink to occur before
    * destruction. */
   {
       _pBackgroundScreen->setParentWin(NULL);
       DEL(_pBackgroundScreen);
   }
}

#ifdef ESTB_CFG_SUPPORT
void CAtlas::estbInitialize()
{
    /* load the estb_cfg */
    B_Estb_cfg_Init((char*)"/perm");
    B_Estb_cfg_Init((char*)"/dyn");
    B_Estb_cfg_Init((char*)"/sys");
    B_Estb_cfg_Open((char*)"/perm", (char*)"./perm.bin");
    B_Estb_cfg_Open((char*)"/dyn", (char*)"./dyn.bin");
    B_Estb_cfg_Open((char*)"/sys", (char*)"./sys.bin");
}

void CAtlas::estbUninitialize()
{
    B_Estb_cfg_Close((char*)"/sys");
    B_Estb_cfg_Close((char*)"/dyn");
    B_Estb_cfg_Close((char*)"/perm");
    B_Estb_cfg_Uninit((char*)"/sys");
    B_Estb_cfg_Uninit((char*)"/dyn");
    B_Estb_cfg_Uninit((char*)"/perm");
}
#endif

#ifdef MPOD_SUPPORT
CCablecard * CAtlas::cableCardInitialize(void)
{
    eRet              ret         = eRet_Ok;
    CCablecard *      pCableCard  = NULL;
    cablecard_t       _cablecard;
    cablecard_setting mpod_setting;
    mpod_setting.oob_mode = NEXUS_FrontendOutOfBandMode_ePod_Dvs178Qpsk;
    mpod_setting.us_mode  = NEXUS_FrontendUpstreamMode_ePodDvs178;

    /* open cablecard */

    pCableCard = new CCablecard;
    CHECK_PTR_ERROR_GOTO("unable to allocate cable card", pCableCard, ret, eRet_OutOfMemory, error);

    _pChannelMgr->setWidgetEngine(_pWidgetEngine);
    _cablecard = pCableCard->cablecard_open(&mpod_setting, _pChannelMgr, &_model);

    if (_cablecard)
    {
        pCableCard->cablecard_set_mpeg_section_callback(_cablecard, CChannelMgr::scteEventCallback);
        pCableCard->cablecard_go(_cablecard);
    }

    /* add cablecard to model */
    _model.addCableCard(pCableCard);

    goto done;
error:
    cableCardUninitialize();
done:
    return(pCableCard);
}

void CAtlas::cableCardUninitialize(void)
{
    CCablecard * pCableCard = _model.getCableCard();

    if (NULL != pCableCard)
    {
        _model.addCableCard(NULL);
        pCableCard->cablecard_close();
        DEL(pCableCard);
    }
}
#endif

#ifdef CDL_SUPPORT
void CAtlas::commonDownloadInitialize(void)
{
    if (CDL_ENABLED == true)
    {
        B_Cdl_Settings cdl_params;
        B_Cdl_GetDefaultSettings(&cdl_params);
        B_Cdl_Init(&cdl_params);
        B_Cdl_Start();
        cdl_started = true;
    }
}

void CAtlas::commonDownloadUninitialize(void)
{
    if (CDL_ENABLED == true)
    {
        cdl_started = false;
        B_Cdl_Stop();
        B_Cdl_Uninit();
    }
}
#endif

#if DVR_LIB_SUPPORT
CTsb * CAtlas::dvrLibInitialize(void)
{
    CTsb * pTsb    = NULL;
    CTsb * pTsbPip = NULL;
    eRet ret       = eRet_Ok;

    pTsb = (CTsb *)_pBoardResources->checkoutResource(this, eBoardResource_tsb);
    CHECK_PTR_ERROR_GOTO("main tsb checkout failed", pTsb, ret, eRet_NotAvailable, error);
    _model.setTsb(pTsb, eWindowType_Main);
    pTsbPip = (CTsb *)_pBoardResources->checkoutResource(this, eBoardResource_tsb);
    CHECK_PTR_ERROR_GOTO("pip tsb checkout failed", pTsbPip, ret, eRet_NotAvailable, error);
    _model.setTsb(pTsbPip, eWindowType_Pip);

    goto done;
error:
    dvrLibUninitialize();
    pTsb = NULL;
done:
    return(pTsb);
}

void CAtlas::dvrLibUninitialize(void)
{
    CTsb * pTsb    = _model.getTsb(eWindowType_Main);
    CTsb * pTsbPip = _model.getTsb(eWindowType_Pip);

    _model.setTsb(NULL, eWindowType_Main);
    _pBoardResources->checkinResource(pTsb);
    _model.setTsb(NULL, eWindowType_Pip);
    _pBoardResources->checkinResource(pTsbPip);
}
#endif /* if DVR_LIB_SUPPORT */

#ifdef DCC_SUPPORT
eRet CAtlas::digitalClosedCaptionsInitialize(CConfig * pConfig)
{
    eRet             ret            = eRet_Ok;
    CClosedCaption * pClosedCaption = NULL;

    BDBG_ASSERT(NULL != pConfig);

    if (true == GET_BOOL(_pCfg, DCC_ENABLED))
    {
        pClosedCaption = new CClosedCaption;
        pClosedCaption->setId(this);
        ret = pClosedCaption->dcc_init(pConfig, &_model);
        CHECK_ERROR_GOTO("unable to initialize digital closed captioning", ret, error);

        _model.addClosedCaption(pClosedCaption);
    }
error:
    return(ret);
}

void CAtlas::digitalClosedCaptionsUninitialize()
{
    CClosedCaption * pClosedCaption = _model.getClosedCaption();

    if (NULL != pClosedCaption)
    {
        pClosedCaption->dcc_uninit();
        DEL(pClosedCaption);
    }
}
#endif /* ifdef DCC_SUPPORT */

CStillDecode * CAtlas::videoDecodeStillInitialize()
{
    eRet           ret               = eRet_Ok;
    CStillDecode * pVideoDecodeStill = NULL;
    CThumb *       pThumb            = NULL;

    pVideoDecodeStill = (CStillDecode *)_pBoardResources->checkoutResource(this, eBoardResource_decodeStill);
    CHECK_PTR_ERROR_GOTO("unable to checkout still decode", pVideoDecodeStill, ret, eRet_NotAvailable, error);

    /* set up still decode for use in thumbnail extractor */
    pVideoDecodeStill->setWidgetEngine(getWidgetEngine());
    _model.addStillDecode(pVideoDecodeStill);

    pThumb = new CThumb(_pCfg);
    CHECK_PTR_ERROR_GOTO("unable to allocate CThumb object", pThumb, ret, eRet_OutOfMemory, error);
    pThumb->setResources(this, _pBoardResources);
    pThumb->setModel(&_model);
    _model.setThumbExtractor(pThumb);

    goto done;
error:
    videoDecodeStillUninitialize();
    pVideoDecodeStill = NULL;
done:
    return(pVideoDecodeStill);
}

void CAtlas::videoDecodeStillUninitialize()
{
    CStillDecode * pVideoDecodeStill = _model.getStillDecode();
    CThumb *       pThumb            = _model.getThumbExtractor();

    _model.setThumbExtractor(NULL);
    DEL(pThumb);

    if (NULL != pVideoDecodeStill)
    {
        _model.removeStillDecode(pVideoDecodeStill);
        _pBoardResources->checkinResource(pVideoDecodeStill);
        pVideoDecodeStill = NULL;
    }
}

COutputHdmi * CAtlas::outputHdmiCreate()
{
    eRet          ret         = eRet_Ok;
    COutputHdmi * pOutputHdmi = NULL;

    /* add/setup HDMI output if in resource list */
    pOutputHdmi = (COutputHdmi *)_pBoardResources->checkoutResource(this, eBoardResource_outputHdmi);
    CHECK_PTR_ERROR_GOTO("unable to checkout hdmi output", pOutputHdmi, ret, eRet_NotAvailable, error);

    pOutputHdmi->setWidgetEngine(_pWidgetEngine);
    _model.addAudioOutput(pOutputHdmi);
error:
    return(pOutputHdmi);
}

void CAtlas::outputHdmiDestroy(COutputHdmi ** pOutputHdmi)
{
    if ((NULL != pOutputHdmi) || (NULL != *pOutputHdmi))
    {
        return;
    }

    _model.removeAudioOutput(*pOutputHdmi);
    (*pOutputHdmi)->setWidgetEngine(NULL);
    _pBoardResources->checkinResource(*pOutputHdmi);
    *pOutputHdmi = NULL;
}

COutputHdmi * CAtlas::outputHdmiInitialize(CDisplay * pDisplay)
{
    eRet                     ret         = eRet_Ok;
    COutputHdmi *            pOutputHdmi = NULL;
    NEXUS_Error              nerror      = NEXUS_SUCCESS;
    NEXUS_HdmiOutputSettings settings;

    if (NULL == pDisplay)
    {
        return(pOutputHdmi);
    }

    /* add/setup HDMI output if in resource list */
    pOutputHdmi = outputHdmiCreate();
    CHECK_PTR_ERROR_GOTO("unable to checkout hdmi output", pOutputHdmi, ret, eRet_NotAvailable, error);

    /* connect output to display */
    ret = pDisplay->addOutput(pOutputHdmi);
    CHECK_ERROR_GOTO("Error adding HDMI output", ret, error);

    NEXUS_HdmiOutput_GetSettings(pOutputHdmi->getOutput(), &settings);
    settings.autoColorSpace = false;
    settings.colorSpace     = NEXUS_ColorSpace_eRgb; /* or NEXUS_ColorSpace_eYCbCr444 */
    nerror                  = NEXUS_HdmiOutput_SetSettings(pOutputHdmi->getOutput(), &settings);
    CHECK_NEXUS_ERROR_GOTO("error setting hdmi output settings", ret, nerror, error);

    goto done;
error:
    outputHdmiUninitialize(pDisplay, &pOutputHdmi);
    pOutputHdmi = NULL;
done:
    return(pOutputHdmi);
}

void CAtlas::outputHdmiUninitialize(CDisplay * pDisplay, COutputHdmi ** pOutputHdmi)
{
    if ((NULL == pOutputHdmi) || (NULL == *pOutputHdmi))
    {
        return;
    }

    pDisplay->removeOutput(*pOutputHdmi);
    (*pOutputHdmi)->uninitialize();
    outputHdmiDestroy(pOutputHdmi);
}

COutputComponent * CAtlas::outputComponentInitialize(CDisplay * pDisplay)
{
    eRet                          ret              = eRet_Ok;
    COutputComponent *            pOutputComponent = NULL;
    NEXUS_Error                   nerror           = NEXUS_SUCCESS;
    NEXUS_ComponentOutputSettings settings;

    if (NULL == pDisplay)
    {
        return(pOutputComponent);
    }

    /* add/setup COMPONENT output if in resource list */
    pOutputComponent = (COutputComponent *)_pBoardResources->checkoutResource(this, eBoardResource_outputComponent);
    CHECK_PTR_ERROR_GOTO("unable to checkout component output", pOutputComponent, ret, eRet_NotAvailable, error);

    /* connect output to display */
    ret = pDisplay->addOutput(pOutputComponent);
    CHECK_ERROR_GOTO("Error adding component output", ret, error);

    NEXUS_ComponentOutput_GetSettings(pOutputComponent->getOutput(), &settings);
    settings.mpaaDecimationEnabled = GET_BOOL(_pCfg, MPAA_ENABLED);
    settings.type                  = pOutputComponent->getDesiredType();
    nerror                         = NEXUS_ComponentOutput_SetSettings(pOutputComponent->getOutput(), &settings);
    CHECK_NEXUS_ERROR_GOTO("error setting component output settings", ret, nerror, error);

    goto done;
error:
    outputComponentUninitialize(pDisplay, &pOutputComponent);
done:
    return(pOutputComponent);
}

void CAtlas::outputComponentUninitialize(CDisplay * pDisplay, COutputComponent ** pOutputComponent)
{
    if ((NULL == pOutputComponent) || (NULL == *pOutputComponent))
    {
        return;
    }

    pDisplay->removeOutput(*pOutputComponent);
    (*pOutputComponent)->disconnect();
    _pBoardResources->checkinResource(*pOutputComponent);
}

COutputComposite * CAtlas::outputCompositeInitialize(CDisplay * pDisplay)
{
    COutputComposite * pOutputComposite = NULL;
    eRet               ret              = eRet_Ok;

    if (NULL == pDisplay)
    {
        return(pOutputComposite);
    }

    /* add/setup COMPOSITE output if in resource list */
    pOutputComposite = (COutputComposite *)_pBoardResources->checkoutResource(this, eBoardResource_outputComposite);
    CHECK_PTR_ERROR_GOTO("unable to checkout composite output", pOutputComposite, ret, eRet_NotAvailable, error);

    /* connect output to display */
    ret = pDisplay->addOutput(pOutputComposite);
    CHECK_ERROR_GOTO("Error adding composite output", ret, error);

    goto done;
error:
    outputCompositeUninitialize(pDisplay, &pOutputComposite);
done:
    return(pOutputComposite);
}

void CAtlas::outputCompositeUninitialize(CDisplay * pDisplay, COutputComposite ** pOutputComposite)
{
    if ((NULL == pOutputComposite) || (NULL == *pOutputComposite))
    {
        return;
    }

    pDisplay->removeOutput(*pOutputComposite);
    (*pOutputComposite)->disconnect();
    _pBoardResources->checkinResource(*pOutputComposite);
    *pOutputComposite = NULL;
}

COutputRFM * CAtlas::outputRfmInitialize(CDisplay * pDisplay)
{
    COutputRFM * pOutputRfm = NULL;
    eRet         ret        = eRet_Ok;

    if (NULL == pDisplay)
    {
        return(pOutputRfm);
    }

    /* add/setup Rfm output if in resource list */
    pOutputRfm = (COutputRFM *)_pBoardResources->checkoutResource(this, eBoardResource_outputRFM);
    CHECK_PTR_ERROR_GOTO("unable to checkout RFM output", pOutputRfm, ret, eRet_NotAvailable, error);

    /* connect output to display */
    ret = pDisplay->addOutput(pOutputRfm);
    CHECK_ERROR_GOTO("Error adding RFM output", ret, error);

    goto done;
error:
    outputRfmUninitialize(pDisplay, &pOutputRfm);
done:
    return(pOutputRfm);
}

void CAtlas::outputRfmUninitialize(CDisplay * pDisplay, COutputRFM ** pOutputRfm)
{
    if ((NULL == pOutputRfm) || (NULL == *pOutputRfm))
    {
        return;
    }

    pDisplay->removeOutput(*pOutputRfm);
    (*pOutputRfm)->disconnect();
    _pBoardResources->checkinResource(*pOutputRfm);
    *pOutputRfm = NULL;
}

COutputSpdif * CAtlas::outputSpdifInitialize()
{
    COutputSpdif * pOutputSpdif = NULL;

    pOutputSpdif = (COutputSpdif *)_pBoardResources->checkoutResource(this, eBoardResource_outputSpdif);
    if (NULL != pOutputSpdif)
    {
        _model.addAudioOutput(pOutputSpdif);
    }

    return(pOutputSpdif);
}

void CAtlas::outputSpdifUninitialize(COutputSpdif ** pOutputSpdif)
{
    if ((NULL == pOutputSpdif) || (NULL == *pOutputSpdif))
    {
        return;
    }

    _model.removeAudioOutput(*pOutputSpdif);
    (*pOutputSpdif)->disconnect();
    _pBoardResources->checkinResource(*pOutputSpdif);
    *pOutputSpdif = NULL;
}

COutputAudioDac * CAtlas::outputDacInitialize()
{
    COutputAudioDac * pOutputAudioDac = NULL;

    pOutputAudioDac = (COutputAudioDac *)_pBoardResources->checkoutResource(this, eBoardResource_outputAudioDac);
    if (NULL != pOutputAudioDac)
    {
        _model.addAudioOutput(pOutputAudioDac);
    }
    else
    {
        pOutputAudioDac = (COutputAudioDac *)_pBoardResources->checkoutResource(this, eBoardResource_outputAudioDacI2s);
        if (NULL != pOutputAudioDac)
        {
            _model.addAudioOutput(pOutputAudioDac);
        }
    }

    return(pOutputAudioDac);
}

void CAtlas::outputDacUninitialize(COutputAudioDac ** pOutputAudioDac)
{
    if ((NULL == pOutputAudioDac) || (NULL == *pOutputAudioDac))
    {
        return;
    }

    _model.removeAudioOutput(*pOutputAudioDac);
    (*pOutputAudioDac)->disconnect();
    _pBoardResources->checkinResource(*pOutputAudioDac);
    *pOutputAudioDac = NULL;
}

void CAtlas::mvcRelationshipsInitialize(CConfig * pConfig)
{
    if (NULL != _pLua)
    {
        _pControl->addView(_pLua, "lua");
        _pLua->setModel(&_model);
    }

    _pControl->setModel(&_model);
    _pControl->setChannelMgr(_pChannelMgr);
#if DVR_LIB_SUPPORT
    _pControl->setDvrMgr(_pDvrMgr);
    _model.setDvrMgr(_pDvrMgr);
#endif
    _model.setChannelMgr(_pChannelMgr);
    _pChannelMgr->setModel(&_model);

    _model.setConfig(pConfig);
}

void CAtlas::mvcRelationshipsUninitialize()
{
    _model.setConfig(NULL);
    _pChannelMgr->setModel(NULL);
    _model.setChannelMgr(NULL);
#if DVR_LIB_SUPPORT
    _model.setDvrMgr(NULL);
    _pControl->setDvrMgr(NULL);
#endif
    _pControl->setChannelMgr(NULL);
    _pControl->setModel(NULL);
    if (NULL != _pLua)
    {
        _pLua->setModel(NULL);
        _pControl->removeView(_pLua);
    }

}

/* register observers for notification events */
void CAtlas::notificationsInitialize()
{
    CDisplay *           pDisplayHD        = _model.getDisplay(0);
    CDisplay *           pDisplaySD        = _model.getDisplay(1);
    CSimpleVideoDecode * pVideoDecodeMain  = _model.getSimpleVideoDecode(eWindowType_Main);
    CSimpleVideoDecode * pVideoDecodePip   = _model.getSimpleVideoDecode(eWindowType_Pip);
    CSimpleAudioDecode * pAudioDecodeMain  = _model.getSimpleAudioDecode(eWindowType_Main);
    CSimpleAudioDecode * pAudioDecodePip   = _model.getSimpleAudioDecode(eWindowType_Pip);
    CStillDecode *       pVideoDecodeStill = _model.getStillDecode();
    CPlaybackList *      pPlaybackList     = _model.getPlaybackList();
#ifdef PLAYBACK_IP_SUPPORT
    CPlaylistDb *          pPlaylistDb          = _model.getPlaylistDb();
    CAutoDiscoveryServer * pAutoDiscoveryServer = _model.getAutoDiscoveryServer();
    CAutoDiscoveryClient * pAutoDiscoveryClient = _model.getAutoDiscoveryClient();
    CServerMgr *           pServerMgr           = _model.getServerMgr();
#endif
#if RF4CE_SUPPORT
    CRf4ceRemote * pRf4ceRemote = _model.getRf4ceRemote();
#endif
#if NEXUS_HAS_UHF_INPUT
    CUhfRemote * pUhfRemote = _model.getUhfRemote();
#endif
    CIrRemote *        pIrRemote        = _model.getIrRemote(stringToIrRemoteType(GET_STR(_pCfg, REMOTE_TYPE_PRIMARY)));
    COutput *          pOutputHdmi      = _model.getAudioOutput(eBoardResource_outputHdmi);
#ifdef NETAPP_SUPPORT
    CBluetoothRemote * pBluetoothRemote = _model.getBluetoothRemote();
#endif

    CPower *    pPower      = (CPower *)_pBoardResources->checkoutResource(this, eBoardResource_power);
#ifdef NETAPP_SUPPORT
    CBluetooth * pBluetooth = (CBluetooth *)_pBoardResources->checkoutResource(this, eBoardResource_bluetooth);
    CNetwork *   pNetwork   = (CNetwork *)_pBoardResources->checkoutResource(this, eBoardResource_network);
#endif
#ifdef MPOD_SUPPORT
    CCablecard * pCableCard = _model.getCableCard();
#endif

    /* register observers of _pControl */
    if (NULL != _pControl)
    {
#ifdef NETAPP_SUPPORT
        if (NULL != pNetwork) { pNetwork->registerObserver(_pControl); }
        if (NULL != pBluetoothRemote) { pBluetoothRemote->registerObserver(_pControl); }
        if (NULL != pBluetooth) { pBluetooth->registerObserver(_pControl); }
#endif
#ifdef PLAYBACK_IP_SUPPORT
        if (NULL != pPlaylistDb) { pPlaylistDb->registerObserver(_pControl); }
#endif
#if RF4CE_SUPPORT
        if (NULL != pRf4ceRemote) { pRf4ceRemote->registerObserver(_pControl); }
#endif /* if RF4CE_SUPPORT */
#if NEXUS_HAS_UHF_INPUT
        if (NULL != pUhfRemote) { pUhfRemote->registerObserver(_pControl); }
#endif /* if NEXUS_HAS_UHF_INPUT */
        if (NULL != pIrRemote) { pIrRemote->registerObserver(_pControl); }
        if (NULL != pVideoDecodeMain) { pVideoDecodeMain->registerObserver(_pControl); }
        if (NULL != pVideoDecodePip) { pVideoDecodePip->registerObserver(_pControl); }
        if (NULL != pOutputHdmi) { pOutputHdmi->registerObserver(_pControl); }
        _pBoardResources->registerObserver(this, eBoardResource_streamer, _pControl);
        _pBoardResources->registerObserver(this, eBoardResource_decodeVideo, _pControl);
#if NEXUS_HAS_FRONTEND
        /* register control with tuners so control can monitor when scan completes */
        _pBoardResources->registerObserver(this, eBoardResource_frontendQam, _pControl);
        _pBoardResources->registerObserver(this, eBoardResource_frontendVsb, _pControl);
        _pBoardResources->registerObserver(this, eBoardResource_frontendSds, _pControl);
        _pBoardResources->registerObserver(this, eBoardResource_frontendOfdm, _pControl);
#endif /* if NEXUS_HAS_FRONTEND */
        if (NULL != _pChannelMgr)
        {
            _pChannelMgr->registerObserver(_pControl);
#ifdef MPOD_SUPPORT
            _pChannelMgr->registerObserver(_pControl);
#endif
        }
        if (NULL != _pMainScreen) { _pMainScreen->registerObserver(_pControl); }
        if (NULL != pDisplayHD) { pDisplayHD->registerObserver(_pControl); }
        if (NULL != _pLua) { _pLua->registerObserver(_pControl); }
    }

    /* register observers of _pMainScreen */
    if (NULL != _pMainScreen)
    {

        if (NULL != _pLua) { _pLua->registerObserver(_pMainScreen, eNotify_Debug); }
        if (NULL != pPower) { pPower->registerObserver(_pMainScreen); }
#ifdef NETAPP_SUPPORT
        if (NULL != pNetwork) { pNetwork->registerObserver(_pMainScreen); }
        if (NULL != pBluetooth) { pBluetooth->registerObserver(_pMainScreen); }
#endif /* ifdef NETAPP_SUPPORT */
#ifdef PLAYBACK_IP_SUPPORT
        if (NULL != pServerMgr) { pServerMgr->registerObserver(_pMainScreen); }
        if (NULL != pPlaylistDb) { pPlaylistDb->registerObserver(_pMainScreen); }
        if (NULL != pAutoDiscoveryServer) { pAutoDiscoveryServer->registerObserver(_pMainScreen); }
        if (NULL != pAutoDiscoveryClient) { pAutoDiscoveryClient->registerObserver(_pMainScreen); }
#endif /* ifdef PLAYBACK_IP_SUPPORT */
        if (NULL != pVideoDecodeMain)
        {
            pVideoDecodeMain->registerObserver(_pMainScreen);
            if (NULL != pVideoDecodeStill) { pVideoDecodeStill->registerObserver(_pMainScreen); }
        }
        if (NULL != pVideoDecodePip) { pVideoDecodePip->registerObserver(_pMainScreen); }
        if (NULL != _pChannelMgr) { _pChannelMgr->registerObserver(_pMainScreen); }

        _model.registerObserver(_pMainScreen);

        if (NULL != pDisplayHD) { pDisplayHD->registerObserver(_pMainScreen); }
        if (NULL != pDisplaySD)
        {
            pDisplaySD->registerObserver(_pMainScreen, eNotify_VbiSettingsChanged);
            pDisplaySD->registerObserver(_pMainScreen, eNotify_ErrorVbi);
            pDisplaySD->registerObserver(_pMainScreen, eNotify_ErrorVbiMacrovision);
            pDisplaySD->registerObserver(_pMainScreen, eNotify_ErrorVbiDcs);
        }

        if (NULL != pAudioDecodeMain) {  pAudioDecodeMain->registerObserver(_pMainScreen); }
        if (NULL != pAudioDecodePip) {  pAudioDecodePip->registerObserver(_pMainScreen); }
        if (NULL != pPlaybackList) { pPlaybackList->registerObserver(_pMainScreen); }

#ifdef MPOD_SUPPORT
        if (NULL != pCableCard) { pCableCard->registerObserver(_pMainScreen); }
#endif
        _pBoardResources->registerObserver(this, eBoardResource_outputSpdif, _pMainScreen);
        _pBoardResources->registerObserver(this, eBoardResource_outputAudioDac, _pMainScreen);
        _pBoardResources->registerObserver(this, eBoardResource_outputAudioDacI2s, _pMainScreen);
        _pBoardResources->registerObserver(this, eBoardResource_outputHdmi, _pMainScreen);
        _pBoardResources->registerObserver(this, eBoardResource_outputRFM, _pMainScreen);

#if NEXUS_HAS_FRONTEND
        _pBoardResources->registerObserver(this, eBoardResource_frontendQam, _pMainScreen);
        _pBoardResources->registerObserver(this, eBoardResource_frontendVsb, _pMainScreen);
        _pBoardResources->registerObserver(this, eBoardResource_frontendSds, _pMainScreen);
        _pBoardResources->registerObserver(this, eBoardResource_frontendOfdm, _pMainScreen);
#endif /* if NEXUS_HAS_FRONTEND */
        _pBoardResources->registerObserver(this, eBoardResource_playback, _pMainScreen);
        _pBoardResources->registerObserver(this, eBoardResource_record, _pMainScreen);
#if DVR_LIB_SUPPORT
        {
            CTsb * pTsb    = _model.getTsb(eWindowType_Main);
            CTsb * pTsbPip = _model.getTsb(eWindowType_Pip);
            if (NULL != pTsb)    { pTsb->registerObserver(_pMainScreen); }
            if (NULL != pTsbPip) { pTsbPip->registerObserver(_pMainScreen); }
        }
#endif
#if NEXUS_HAS_VIDEO_ENCODER
        _pBoardResources->registerObserver(this, eBoardResource_encode, _pMainScreen);
#endif
    }

    /* register observers of _pLua */
    if (NULL != _pLua)
    {
        if (NULL != pPower) { pPower->registerObserver(_pLua); }
#ifdef NETAPP_SUPPORT
        if (NULL != pNetwork) { pNetwork->registerObserver(_pLua); }
        if (NULL != pBluetooth) { pBluetooth->registerObserver(_pLua); }
#endif
#ifdef PLAYBACK_IP_SUPPORT
        if (NULL != pServerMgr) { pServerMgr->registerObserver(_pLua); }
        if (NULL != pPlaylistDb) { pPlaylistDb->registerObserver(_pLua); }
        if (NULL != pAutoDiscoveryServer) { pAutoDiscoveryServer->registerObserver(_pLua); }
        if (NULL != pAutoDiscoveryClient) { pAutoDiscoveryClient->registerObserver(_pLua); }
#endif

        _model.registerObserver(_pLua);
        if (NULL != pVideoDecodeMain) { pVideoDecodeMain->registerObserver(_pLua); }
        if (NULL != pVideoDecodePip) { pVideoDecodePip->registerObserver(_pLua); }
#if NEXUS_HAS_FRONTEND
        _pBoardResources->registerObserver(this, eBoardResource_frontendQam, _pLua);
        _pBoardResources->registerObserver(this, eBoardResource_frontendVsb, _pLua);
        _pBoardResources->registerObserver(this, eBoardResource_frontendSds, _pLua);
        _pBoardResources->registerObserver(this, eBoardResource_frontendOfdm, _pLua);
#endif /* if NEXUS_HAS_FRONTEND */
        if (NULL != _pChannelMgr) { _pChannelMgr->registerObserver(_pLua); }
        if (NULL != pDisplayHD) { pDisplayHD->registerObserver(_pLua); }
        if (NULL != pDisplaySD) { pDisplaySD->registerObserver(_pLua, eNotify_VbiSettingsChanged); }
        if (NULL != pAudioDecodeMain) { pAudioDecodeMain->registerObserver(_pLua); }
        if (NULL != pAudioDecodePip) { pAudioDecodePip->registerObserver(_pLua); }
        _pBoardResources->registerObserver(this, eBoardResource_playback, _pLua);
#if NEXUS_HAS_VIDEO_ENCODER
        _pBoardResources->registerObserver(this, eBoardResource_encode, _pLua);
#endif
        _pBoardResources->registerObserver(this, eBoardResource_record, _pLua);
        _pBoardResources->registerObserver(this, eBoardResource_outputSpdif, _pLua);
        _pBoardResources->registerObserver(this, eBoardResource_outputAudioDac, _pLua);
        _pBoardResources->registerObserver(this, eBoardResource_outputAudioDacI2s, _pLua);
        _pBoardResources->registerObserver(this, eBoardResource_outputHdmi, _pLua);
        _pBoardResources->registerObserver(this, eBoardResource_outputRFM, _pLua);
    }

    /* check appropriate resources back in */
    if (NULL != pPower) { _pBoardResources->checkinResource(pPower); }
#ifdef NETAPP_SUPPORT
    if (NULL != pNetwork) { _pBoardResources->checkinResource(pNetwork); }
    if (NULL != pBluetooth) { _pBoardResources->checkinResource(pBluetooth); }
#endif
}

void CAtlas::notificationsUninitialize()
{
    CDisplay *           pDisplayHD        = _model.getDisplay(0);
    CDisplay *           pDisplaySD        = _model.getDisplay(1);
    CSimpleVideoDecode * pVideoDecodeMain  = _model.getSimpleVideoDecode(eWindowType_Main);
    CSimpleVideoDecode * pVideoDecodePip   = _model.getSimpleVideoDecode(eWindowType_Pip);
    CSimpleAudioDecode * pAudioDecodeMain  = _model.getSimpleAudioDecode(eWindowType_Main);
    CSimpleAudioDecode * pAudioDecodePip   = _model.getSimpleAudioDecode(eWindowType_Pip);
    CStillDecode *       pVideoDecodeStill = _model.getStillDecode();
    CPlaybackList *      pPlaybackList     = _model.getPlaybackList();
#ifdef PLAYBACK_IP_SUPPORT
    CPlaylistDb *          pPlaylistDb          = _model.getPlaylistDb();
    CAutoDiscoveryServer * pAutoDiscoveryServer = _model.getAutoDiscoveryServer();
    CAutoDiscoveryClient * pAutoDiscoveryClient = _model.getAutoDiscoveryClient();
    CServerMgr *           pServerMgr           = _model.getServerMgr();
#endif
#if RF4CE_SUPPORT
    CRf4ceRemote * pRf4ceRemote = _model.getRf4ceRemote();
#endif
#if NEXUS_HAS_UHF_INPUT
    CUhfRemote * pUhfRemote = _model.getUhfRemote();
#endif
    CIrRemote * pIrRemote   = _model.getIrRemote(stringToIrRemoteType(GET_STR(_pCfg, REMOTE_TYPE_PRIMARY)));
    COutput *   pOutputHdmi = _model.getAudioOutput(eBoardResource_outputHdmi);

    CPower *    pPower      = (CPower *)_pBoardResources->checkoutResource(this, eBoardResource_power);
#ifdef NETAPP_SUPPORT
    CBluetooth *       pBluetooth       = (CBluetooth *)_pBoardResources->checkoutResource(this, eBoardResource_bluetooth);
    CBluetoothRemote * pBluetoothRemote = (CBluetoothRemote *)_pBoardResources->checkoutResource(this, eBoardResource_bluetoothRemote);
    CNetwork *         pNetwork         = (CNetwork *)_pBoardResources->checkoutResource(this, eBoardResource_network);
#endif
#ifdef MPOD_SUPPORT
    CCablecard * pCableCard = _model.getCableCard();
#endif

    /* register observers of _pControl */
    if (NULL != _pControl)
    {
#ifdef NETAPP_SUPPORT
        if (NULL != pNetwork) { pNetwork->unregisterObserver(_pControl); }
        if (NULL != pBluetoothRemote) { pBluetoothRemote->unregisterObserver(_pControl); }
        if (NULL != pBluetooth) { pBluetooth->unregisterObserver(_pControl); }
#endif
#ifdef PLAYBACK_IP_SUPPORT
        if (NULL != pPlaylistDb) { pPlaylistDb->unregisterObserver(_pControl); }
#endif
#if RF4CE_SUPPORT
        if (NULL != pRf4ceRemote) { pRf4ceRemote->unregisterObserver(_pControl); }
#endif /* if RF4CE_SUPPORT */
#if NEXUS_HAS_UHF_INPUT
        if (NULL != pUhfRemote) { pUhfRemote->unregisterObserver(_pControl); }
#endif /* if NEXUS_HAS_UHF_INPUT */
        if (NULL != pIrRemote) { pIrRemote->unregisterObserver(_pControl); }
        if (NULL != pVideoDecodeMain) { pVideoDecodeMain->unregisterObserver(_pControl); }
        if (NULL != pVideoDecodePip) { pVideoDecodePip->unregisterObserver(_pControl); }
        if (NULL != pOutputHdmi) { pOutputHdmi->unregisterObserver(_pControl); }
        _pBoardResources->unregisterObserver(this, eBoardResource_streamer, _pControl);
        _pBoardResources->unregisterObserver(this, eBoardResource_decodeVideo, _pControl);
#if NEXUS_HAS_FRONTEND
        /* register control with tuners so control can monitor when scan completes */
        _pBoardResources->unregisterObserver(this, eBoardResource_frontendQam, _pControl);
        _pBoardResources->unregisterObserver(this, eBoardResource_frontendVsb, _pControl);
        _pBoardResources->unregisterObserver(this, eBoardResource_frontendSds, _pControl);
        _pBoardResources->unregisterObserver(this, eBoardResource_frontendOfdm, _pControl);
#endif /* if NEXUS_HAS_FRONTEND */
        if (NULL != _pChannelMgr)
        {
            _pChannelMgr->unregisterObserver(_pControl);
#ifdef MPOD_SUPPORT
            _pChannelMgr->unregisterObserver(_pControl);
#endif
        }
        if (NULL != _pMainScreen) { _pMainScreen->unregisterObserver(_pControl); }
        if (NULL != pDisplayHD) { pDisplayHD->unregisterObserver(_pControl); }
        if (NULL != _pLua) { _pLua->unregisterObserver(_pControl); }
    }

    /* register observers of _pMainScreen */
    if (NULL != _pMainScreen)
    {
        if (NULL != pPower) { pPower->unregisterObserver(_pMainScreen); }
#ifdef NETAPP_SUPPORT
        if (NULL != pNetwork) { pNetwork->unregisterObserver(_pMainScreen); }
        if (NULL != pBluetooth) { pBluetooth->unregisterObserver(_pMainScreen); }
#endif /* ifdef NETAPP_SUPPORT */
#ifdef PLAYBACK_IP_SUPPORT
        if (NULL != pServerMgr) { pServerMgr->unregisterObserver(_pMainScreen); }
        if (NULL != pPlaylistDb) { pPlaylistDb->unregisterObserver(_pMainScreen); }
        if (NULL != pAutoDiscoveryServer) { pAutoDiscoveryServer->unregisterObserver(_pMainScreen); }
        if (NULL != pAutoDiscoveryClient) { pAutoDiscoveryClient->unregisterObserver(_pMainScreen); }
#endif /* ifdef PLAYBACK_IP_SUPPORT */
        if (NULL != pVideoDecodeMain)
        {
            pVideoDecodeMain->unregisterObserver(_pMainScreen);
            if (NULL != pVideoDecodeStill) { pVideoDecodeStill->unregisterObserver(_pMainScreen); }
        }
        if (NULL != pVideoDecodePip) { pVideoDecodePip->unregisterObserver(_pMainScreen); }
        if (NULL != _pChannelMgr) { _pChannelMgr->unregisterObserver(_pMainScreen); }

        _model.unregisterObserver(_pMainScreen);

        if (NULL != pDisplayHD) { pDisplayHD->unregisterObserver(_pMainScreen); }
        if (NULL != pDisplaySD)
        {
            pDisplaySD->unregisterObserver(_pMainScreen, eNotify_VbiSettingsChanged);
            pDisplaySD->unregisterObserver(_pMainScreen, eNotify_ErrorVbi);
            pDisplaySD->unregisterObserver(_pMainScreen, eNotify_ErrorVbiMacrovision);
            pDisplaySD->unregisterObserver(_pMainScreen, eNotify_ErrorVbiDcs);
        }

        if (NULL != pAudioDecodeMain) {  pAudioDecodeMain->unregisterObserver(_pMainScreen); }
        if (NULL != pAudioDecodePip) {  pAudioDecodePip->unregisterObserver(_pMainScreen); }
        if (NULL != pPlaybackList) { pPlaybackList->unregisterObserver(_pMainScreen); }

#ifdef MPOD_SUPPORT
        if (NULL != pCableCard) { pCableCard->unregisterObserver(_pMainScreen); }
#endif
        _pBoardResources->unregisterObserver(this, eBoardResource_outputSpdif, _pMainScreen);
        _pBoardResources->unregisterObserver(this, eBoardResource_outputAudioDac, _pMainScreen);
        _pBoardResources->unregisterObserver(this, eBoardResource_outputAudioDacI2s, _pMainScreen);
        _pBoardResources->unregisterObserver(this, eBoardResource_outputHdmi, _pMainScreen);
        _pBoardResources->unregisterObserver(this, eBoardResource_outputRFM, _pMainScreen);

#if NEXUS_HAS_FRONTEND
        _pBoardResources->unregisterObserver(this, eBoardResource_frontendQam, _pMainScreen);
        _pBoardResources->unregisterObserver(this, eBoardResource_frontendVsb, _pMainScreen);
        _pBoardResources->unregisterObserver(this, eBoardResource_frontendSds, _pMainScreen);
        _pBoardResources->unregisterObserver(this, eBoardResource_frontendOfdm, _pMainScreen);
#endif /* if NEXUS_HAS_FRONTEND */
        _pBoardResources->unregisterObserver(this, eBoardResource_playback, _pMainScreen);
        _pBoardResources->unregisterObserver(this, eBoardResource_record, _pMainScreen);
#if DVR_LIB_SUPPORT
        {
            CTsb * pTsb    = _model.getTsb(eWindowType_Main);
            CTsb * pTsbPip = _model.getTsb(eWindowType_Pip);
            if (NULL != pTsb)    { pTsb->unregisterObserver(_pMainScreen); }
            if (NULL != pTsbPip) { pTsbPip->unregisterObserver(_pMainScreen); }
        }
#endif
#if NEXUS_HAS_VIDEO_ENCODER
        _pBoardResources->unregisterObserver(this, eBoardResource_encode, _pMainScreen);
#endif
    }

    /* register observers of _pLua */
    if (NULL != _pLua)
    {
        if (NULL != pPower) { pPower->unregisterObserver(_pLua); }
#ifdef NETAPP_SUPPORT
        if (NULL != pNetwork) { pNetwork->unregisterObserver(_pLua); }
        if (NULL != pBluetooth) { pBluetooth->unregisterObserver(_pLua); }
#endif
#ifdef PLAYBACK_IP_SUPPORT
        if (NULL != pServerMgr) { pServerMgr->unregisterObserver(_pLua); }
        if (NULL != pPlaylistDb) { pPlaylistDb->unregisterObserver(_pLua); }
        if (NULL != pAutoDiscoveryServer) { pAutoDiscoveryServer->unregisterObserver(_pLua); }
        if (NULL != pAutoDiscoveryClient) { pAutoDiscoveryClient->unregisterObserver(_pLua); }
#endif

        _model.unregisterObserver(_pLua);
        if (NULL != pVideoDecodeMain) { pVideoDecodeMain->unregisterObserver(_pLua); }
        if (NULL != pVideoDecodePip) { pVideoDecodePip->unregisterObserver(_pLua); }
#if NEXUS_HAS_FRONTEND
        _pBoardResources->unregisterObserver(this, eBoardResource_frontendQam, _pLua);
        _pBoardResources->unregisterObserver(this, eBoardResource_frontendVsb, _pLua);
        _pBoardResources->unregisterObserver(this, eBoardResource_frontendSds, _pLua);
        _pBoardResources->unregisterObserver(this, eBoardResource_frontendOfdm, _pLua);
#endif /* if NEXUS_HAS_FRONTEND */
        if (NULL != _pChannelMgr) { _pChannelMgr->unregisterObserver(_pLua); }
        if (NULL != pDisplayHD) { pDisplayHD->unregisterObserver(_pLua); }
        if (NULL != pDisplaySD) { pDisplaySD->unregisterObserver(_pLua, eNotify_VbiSettingsChanged); }
        if (NULL != pAudioDecodeMain) { pAudioDecodeMain->unregisterObserver(_pLua); }
        if (NULL != pAudioDecodePip) { pAudioDecodePip->unregisterObserver(_pLua); }
        _pBoardResources->unregisterObserver(this, eBoardResource_playback, _pLua);
#if NEXUS_HAS_VIDEO_ENCODER
        _pBoardResources->unregisterObserver(this, eBoardResource_encode, _pLua);
#endif
        _pBoardResources->unregisterObserver(this, eBoardResource_record, _pLua);
        _pBoardResources->unregisterObserver(this, eBoardResource_outputSpdif, _pLua);
        _pBoardResources->unregisterObserver(this, eBoardResource_outputAudioDac, _pLua);
        _pBoardResources->unregisterObserver(this, eBoardResource_outputAudioDacI2s, _pLua);
        _pBoardResources->unregisterObserver(this, eBoardResource_outputHdmi, _pLua);
        _pBoardResources->unregisterObserver(this, eBoardResource_outputRFM, _pLua);
    }

    /* check appropriate resources back in */
    if (NULL != pPower) { _pBoardResources->checkinResource(pPower); }
#ifdef NETAPP_SUPPORT
    if (NULL != pNetwork) { _pBoardResources->checkinResource(pNetwork); }
    if (NULL != pBluetooth) { _pBoardResources->checkinResource(pBluetooth); }
#endif
}

eRet CAtlas::initialize(CConfig * pConfig)
{
    eRet                 ret               = eRet_Ok;
    CDisplay *           pDisplayHD        = NULL;
    CDisplay *           pDisplaySD        = NULL;
    CGraphics *          pGraphics         = NULL;
    CSimpleVideoDecode * pVideoDecodeMain  = NULL;
    CSimpleVideoDecode * pVideoDecodePip   = NULL;
    CStillDecode *       pVideoDecodeStill = NULL;
    CSimpleAudioDecode * pAudioDecodeMain  = NULL;
    CSimpleAudioDecode * pAudioDecodePip   = NULL;
    CStc *               pStcMain          = NULL;
    CStc *               pStcPip           = NULL;
    CIrRemote *          pIrRemote         = NULL;
    CPlaybackList *      pPlaybackList     = NULL;
    COutputComponent *   pOutputComponent  = NULL;
    COutputComposite *   pOutputComposite  = NULL;
    COutputRFM *         pOutputRFM        = NULL;
    COutputHdmi *        pOutputHdmi       = NULL;
    COutputSpdif *       pOutputSpdif      = NULL;
    COutputAudioDac *    pOutputAudioDac   = NULL;
#if RF4CE_SUPPORT
    CRf4ceRemote * pRf4ceRemote = NULL;
#endif
#ifdef NETAPP_SUPPORT
    CBluetoothRemote * pBluetoothRemote = NULL;
#endif
#if NEXUS_HAS_UHF_INPUT
    CUhfRemote * pUhfRemote = NULL;
#endif
#ifdef MPOD_SUPPORT
    CCablecard * pCableCard = NULL;
#endif

    _pConfig         = pConfig;
    _pCfg            = pConfig->getCfg();
    _pBoardResources = pConfig->getBoardResources();

    BDBG_WRN(("Board Name:%s", GET_STR(_pCfg, BOARD_NAME)));

    _pControl = controlCreate();
    CHECK_PTR_ERROR_GOTO("unable to allocate control object", _pControl, ret, eRet_OutOfMemory, error);

    mvcRelationshipsInitialize(pConfig);

    pDisplayHD = displayInitialize(
                        stringToVideoFormat(GET_STR(_pCfg, PREFERRED_FORMAT_HD)),
                        GET_INT(_pCfg, FRAMEBUFFER_SURFACE_WIDTH_HD),
                        GET_INT(_pCfg, FRAMEBUFFER_SURFACE_HEIGHT_HD));
    CHECK_PTR_ERROR("unable to create HD Display", pDisplayHD, ret, eRet_NotSupported);

    if ((true == _pBoardResources->findResource(this, eBoardResource_outputComposite)) ||
        (true == _pBoardResources->findResource(this, eBoardResource_outputRFM)))
    {

        pDisplaySD = displayInitialize(
                            stringToVideoFormat(GET_STR(_pCfg, PREFERRED_FORMAT_SD)),
                            GET_INT(_pCfg, FRAMEBUFFER_SURFACE_WIDTH_SD),
                            GET_INT(_pCfg, FRAMEBUFFER_SURFACE_HEIGHT_SD));
        CHECK_PTR_ERROR("unable to create SD Display", pDisplaySD, ret, eRet_NotSupported);
    }

    if ((NULL != pDisplayHD) || (NULL != pDisplaySD))
    {
        pGraphics = graphicsInitialize(pDisplayHD, pDisplaySD);
        CHECK_PTR_ERROR("unable to initialize graphics", pGraphics, ret, eRet_NotSupported);
    }

    _pControl->initialize(this, _pConfig, _pChannelMgr, _pWidgetEngine);

    pIrRemote    = irRemoteInitialize();
#if RF4CE_SUPPORT
    pRf4ceRemote = rf4ceRemoteInitialize();
#endif
#if NEXUS_HAS_UHF_INPUT
    pUhfRemote   = uhfRemoteInitialize();
#endif

#ifdef ESTB_CFG_SUPPORT
    estbInitialize();
#endif /* ifdef ESTB_CFG_SUPPORT */

#ifdef MPOD_SUPPORT
    pCableCard = cableCardInitialize();
    CHECK_PTR_ERROR("unable to initialize cable card", pCableCard, ret, eRet_NotSupported);
#endif /* ifdef MPOD_SUPPORT */

#ifdef CDL_SUPPORT
    commonDownloadInitialize();
#endif /* ifdef CDL_SUPPORT */

#if DVR_LIB_SUPPORT
    dvrLibInitialize();
#endif /* if DVR_LIB_SUPPORT */

    /* init main decode and video windows */
    {
        CVideoWindow * pVideoWindowHD = NULL;
        CVideoWindow * pVideoWindowSD = NULL;

        pStcMain = stcInitialize(eWindowType_Main);
        CHECK_PTR_ERROR_GOTO("unable to initialize main simple stc", pStcMain, ret, eRet_NotAvailable, errorDecodeMain);

        pVideoDecodeMain = videoDecodeInitialize(pStcMain, eWindowType_Main);
        CHECK_PTR_ERROR_GOTO("unable to initialize main video decode", pVideoDecodeMain, ret, eRet_NotAvailable, errorDecodeMain);

        pVideoWindowHD = videoWindowInitialize(pDisplayHD, pVideoDecodeMain, eWindowType_Main);
        CHECK_PTR_WARN("unable to initialize video window for HD display (main)", pVideoWindowHD, ret, eRet_NotAvailable);

        pVideoWindowSD = videoWindowInitialize(pDisplaySD, pVideoDecodeMain, eWindowType_Main);
        CHECK_PTR_WARN("unable to initialize video window for SD display (main)", pVideoWindowSD, ret, eRet_NotAvailable);

        goto doneDecodeMain;
errorDecodeMain: /* we can continue even if main decode cannot be initialized (headless) */
        if (NULL != pVideoWindowSD)
        {
            videoWindowUninitialize(pDisplaySD, pVideoDecodeMain, pVideoWindowSD);
        }
        if (NULL != pVideoWindowHD)
        {
            videoWindowUninitialize(pDisplayHD, pVideoDecodeMain, pVideoWindowHD);
        }
        if (NULL != pVideoDecodeMain)
        {
            videoDecodeUninitialize(&pVideoDecodeMain);
            pVideoDecodeMain = NULL;
        }
        if (NULL != pStcMain)
        {
            stcUninitialize(&pStcMain, eWindowType_Main);
        }
    }
doneDecodeMain:

    /* init pip decode and video windows */
    {
        CVideoWindow * pVideoWindowHD = NULL;
        CVideoWindow * pVideoWindowSD = NULL;

        _model.setPipEnabled(false);

        pStcPip = stcInitialize(eWindowType_Pip);
        CHECK_PTR_WARN_GOTO("unable to initialize pip simple stc", pStcPip, ret, eRet_NotAvailable, errorDecodePip);

        pVideoDecodePip = videoDecodeInitialize(pStcPip, eWindowType_Pip);
        CHECK_PTR_WARN_GOTO("unable to initialize pip video decode", pVideoDecodePip, ret, eRet_NotAvailable, errorDecodePip);

        pVideoWindowHD = videoWindowInitialize(pDisplayHD, pVideoDecodePip, eWindowType_Pip);
        CHECK_PTR_WARN("unable to initialize video window for HD display (pip)", pVideoWindowHD, ret, eRet_NotAvailable);

        pVideoWindowSD = videoWindowInitialize(pDisplaySD, pVideoDecodePip, eWindowType_Pip);
        CHECK_PTR_WARN("unable to initialize video window for SD display (pip)", pVideoWindowSD, ret, eRet_NotAvailable);

        _model.setPipEnabled(true);

        goto doneDecodePip;
errorDecodePip: /* we can continue even if pip decode cannot be initialized (headless) */
        if (NULL != pVideoWindowSD)
        {
            videoWindowUninitialize(pDisplaySD, pVideoDecodePip, pVideoWindowSD);
        }
        if (NULL != pVideoWindowHD)
        {
            videoWindowUninitialize(pDisplayHD, pVideoDecodePip, pVideoWindowHD);
        }
        if (NULL != pVideoDecodePip)
        {
            videoDecodeUninitialize(&pVideoDecodePip);
            pVideoDecodePip = NULL;
        }
        if (NULL != pStcPip)
        {
            stcUninitialize(&pStcPip, eWindowType_Pip);
        }
    }
doneDecodePip:
#ifdef DCC_SUPPORT
    ret = digitalClosedCaptionsInitialize(pConfig);
    CHECK_ERROR("digital closed captions failed to initialize", ret);
#endif

    if (NULL != pVideoDecodeMain)
    {
        pVideoDecodeStill = videoDecodeStillInitialize();
        CHECK_PTR_WARN("unable to initialize still decode", pVideoDecodeStill, ret, eRet_NotAvailable);
    }

    /* initialize video and audio outputs */
    pOutputHdmi = outputHdmiInitialize(pDisplayHD);
    CHECK_PTR_WARN("unable to initialize hdmi output - disabled", pOutputHdmi, ret, eRet_NotAvailable);
    pOutputComponent = outputComponentInitialize(pDisplayHD);
    CHECK_PTR_WARN("unable to initialize component output - disabled", pOutputComponent, ret, eRet_NotAvailable);
    pOutputComposite = outputCompositeInitialize(pDisplaySD);
    CHECK_PTR_WARN("unable to initialize composite output - disabled", pOutputComposite, ret, eRet_NotAvailable);
    pOutputRFM = outputRfmInitialize(pDisplaySD);
    CHECK_PTR_WARN("unable to initialize rfm output - disabled", pOutputRFM, ret, eRet_NotAvailable);
    pOutputSpdif = outputSpdifInitialize();
    CHECK_PTR_WARN("unable to initialize spdif output - disabled", pOutputSpdif, ret, eRet_NotAvailable);
    pOutputAudioDac = outputDacInitialize();
    CHECK_PTR_WARN("unable to initialize Dac output - disabled", pOutputAudioDac, ret, eRet_NotAvailable);

    /* initialize Main audio decoder */
    pAudioDecodeMain = audioDecodeInitialize(pOutputHdmi, pOutputSpdif, pOutputAudioDac, pOutputRFM, pStcMain, eWindowType_Main);
    CHECK_PTR_WARN("unable to initialize Main audio decode - disabled", pAudioDecodeMain, ret, eRet_NotAvailable);
    /* initialize Pip audio decoder */
    pAudioDecodePip = audioDecodeInitializePip(pOutputHdmi, pOutputSpdif, pOutputAudioDac, pOutputRFM, pStcPip, eWindowType_Pip);
    CHECK_PTR_WARN("unable to initialize Pip audio decode - disabled", pAudioDecodePip, ret, eRet_NotAvailable);

    pPlaybackList = new CPlaybackList(_pCfg);
    CHECK_PTR_ERROR_GOTO("unable to allocate playback list", pPlaybackList, ret, eRet_OutOfMemory, error);
    _model.setPlaybackList(pPlaybackList);

#ifdef NETAPP_SUPPORT
    ret = networkInitialize();
    CHECK_WARN("unable to initialize wifi networking support - disabled", ret);

    pBluetoothRemote = bluetoothRemoteInitialize();
    CHECK_PTR_WARN("unable to initialize bluetooth remote - disabled", pBluetoothRemote, ret, eRet_NotAvailable);

    {
        CBluetooth *    pBluetooth    = NULL;
        CAudioCapture * pAudioCapture = NULL;

        pBluetooth = bluetoothInitialize();
        CHECK_PTR_WARN_GOTO("unable to initialize bluetooth support - disabled", pBluetooth, ret, eRet_NotAvailable, errorBluetooth);

        /* pass in the bluetoothRemote object, so a hotplug can initiate blueoothRemote functionality */
        pBluetooth->setBluetoothRemote(pBluetoothRemote);

        /* audio capture is only supported in nxclient mode */
        pAudioCapture = audioCaptureInitialize(pBluetooth);
        CHECK_PTR_WARN_GOTO("unable to initialize audio capture support - disabled", pAudioCapture, ret, eRet_NotAvailable, errorAudioCapture);

    }
errorBluetooth:
errorAudioCapture:
#endif /* ifdef NETAPP_SUPPORT */

#ifdef PLAYBACK_IP_SUPPORT
    ret = ipServerInitialize();
    CHECK_WARN("unable to initialize IP client/server support - disabled", ret);
#endif /* ifdef PLAYBACK_IP_SUPPORT */

    ret = guiInitialize(pConfig, pGraphics);
    CHECK_ERROR_GOTO("Graphical User Interface failed to initialize", ret, error);

    /* register observers for allowed notification deliveries */
    notificationsInitialize();

    _pControl->updatePlaybackList();
#if NEXUS_HAS_FRONTEND
    _pControl->initializeTuners();
#endif

#ifdef PLAYBACK_IP_SUPPORT
    ret = ipServerStart();
    CHECK_WARN("unable to start IP server - disabled", ret);
#endif /* ifdef PLAYBACK_IP_SUPPORT */

#ifdef SNMP_SUPPORT
    ret = snmpInitialize();
    CHECK_WARN("unable to start SNMP - disabled", ret);
#endif /* ifdef SNMP_SUPPORT */

    _pMainScreen->show(true);

    ret = setPreferredVideoFormat(pOutputHdmi, pOutputComponent, pOutputComposite, pOutputRFM);
    CHECK_WARN("unable to set preferred video format", ret);

    /* initialize current channel */
    _model.setCurrentChannel(_pChannelMgr->getFirstChannel());

    /* initialize volume level */
    _pControl->setVolume(NEXUS_AUDIO_VOLUME_LINEAR_NORMAL);

    return(ret);

error:
    BDBG_ASSERT(false);
    return(ret);
} /* initialize */

void CAtlas::uninitialize()
{
    CDisplay *           pDisplayHD         = _model.getDisplay(0);
    CDisplay *           pDisplaySD         = _model.getDisplay(1);
    CPlaybackList *      pPlaybackList      = _model.getPlaybackList();
    CSimpleVideoDecode * pVideoDecodeMain   = _model.getSimpleVideoDecode(eWindowType_Main);
    CSimpleVideoDecode * pVideoDecodePip    = _model.getSimpleVideoDecode(eWindowType_Pip);
    CSimpleAudioDecode * pAudioDecodeMain   = _model.getSimpleAudioDecode(eWindowType_Main);
    CSimpleAudioDecode * pAudioDecodePip    = _model.getSimpleAudioDecode(eWindowType_Pip);
    CStc *               pStcMain           = _model.getStc(eWindowType_Main);
    CStc *               pStcPip            = _model.getStc(eWindowType_Pip);
    COutputAudioDac *    pOutputAudioDac    = (COutputAudioDac *)_model.getAudioOutput(eBoardResource_outputAudioDac);
    COutputSpdif *       pOutputSpdif       = (COutputSpdif *)_model.getAudioOutput(eBoardResource_outputSpdif);
    COutputHdmi *        pOutputHdmi        = NULL;
    COutputComponent *   pOutputComponent   = NULL;
    COutputComposite *   pOutputComposite   = NULL;
    COutputRFM *         pOutputRFM         = NULL;

    if (NULL != pDisplayHD)
    {
        pOutputHdmi      = (COutputHdmi *)pDisplayHD->getOutput(eBoardResource_outputHdmi);
        pOutputComponent = (COutputComponent *)pDisplayHD->getOutput(eBoardResource_outputComponent);
    }
    if (NULL != pDisplaySD)
    {
        pOutputComposite = (COutputComposite *)pDisplaySD->getOutput(eBoardResource_outputComposite);
        pOutputRFM       = (COutputRFM *)pDisplaySD->getOutput(eBoardResource_outputRFM);
    }

    _pMainScreen->show(false);

#ifdef SNMP_SUPPORT
    snmpUninitialize();
#endif

    notificationsUninitialize();
    guiUninitialize();

#ifdef PLAYBACK_IP_SUPPORT
    ipServerUninitialize();
#endif
#ifdef NETAPP_SUPPORT
    audioCaptureUninitialize();
    bluetoothUninitialize();
    networkUninitialize();
#endif
    DEL(pPlaybackList);

    audioDecodeUninitialize(&pAudioDecodePip, eWindowType_Pip);
    audioDecodeUninitialize(&pAudioDecodeMain, eWindowType_Main);

    outputDacUninitialize(&pOutputAudioDac);
    outputSpdifUninitialize(&pOutputSpdif);
    outputRfmUninitialize(pDisplaySD, &pOutputRFM);
    outputCompositeUninitialize(pDisplaySD, &pOutputComposite);
    /* component output can be connected to either the HD or SD display */
    if (NULL != pDisplayHD)
    {
        pOutputComponent = (COutputComponent *)pDisplayHD->getOutput(eBoardResource_outputComponent);
        if (NULL != pOutputComponent)
        {
            outputComponentUninitialize(pDisplayHD, &pOutputComponent);
        }
    }
    if (NULL != pDisplaySD)
    {
        pOutputComponent = (COutputComponent *)pDisplaySD->getOutput(eBoardResource_outputComponent);
        if (NULL != pOutputComponent)
        {
            outputComponentUninitialize(pDisplaySD, &pOutputComponent);
        }
    }
    outputHdmiUninitialize(pDisplayHD, &pOutputHdmi);

    if (NULL != pVideoDecodeMain)
    {
        videoDecodeStillUninitialize();
    }

#ifdef DCC_SUPPORT
    digitalClosedCaptionsUninitialize();
#endif

    _model.setPipEnabled(false);
    /* no need to uninitialize video windows - uninitialize display will take care of it */
    videoDecodeUninitialize(&pVideoDecodePip);
    stcUninitialize(&pStcPip, eWindowType_Pip);

    videoDecodeUninitialize(&pVideoDecodeMain);
    stcUninitialize(&pStcMain, eWindowType_Main);

#if DVR_LIB_SUPPORT
    dvrLibUninitialize();
#endif
#ifdef CDL_SUPPORT
    commonDownloadUninitialize();
#endif
#ifdef MPOD_SUPPORT
    cableCardUninitialize();
#endif /* ifdef MPOD_SUPPORT */
#ifdef ESTB_CFG_SUPPORT
    estbUninitialize();
#endif /* ifdef ESTB_CFG_SUPPORT */
#if NEXUS_HAS_UHF_INPUT
    uhfRemoteUninitialize();
#endif
#if RF4CE_SUPPORT
    rf4ceRemoteUninitialize();
#endif
    irRemoteUninitialize();
#ifdef NETAPP_SUPPORT
    bluetoothRemoteUninitialize();
#endif

    _pControl->uninitialize();
    controlDestroy(_pControl);

    graphicsUninitialize();

    displayUninitialize(&pDisplaySD);
    displayUninitialize(&pDisplayHD);

    mvcRelationshipsUninitialize();

} /* uninitialize */

bwin_engine_t CAtlas::getWinEngine()
{
    bwin_engine_t winEngine = NULL;
    CGraphics *   pGraphics = NULL;
    eRet          ret       = eRet_Ok;

    pGraphics = (CGraphics *)_pBoardResources->findCheckedoutResource(this, eBoardResource_graphics);
    CHECK_PTR_ERROR_GOTO("Cannot get bwin engine without a graphics.", pGraphics, ret, eRet_InvalidState, error);

    winEngine = pGraphics->getWinEngine();

error:
    return(winEngine);
}

eRet CAtlas::run()
{
    eRet ret = eRet_Ok;

    BDBG_ASSERT(NULL != _pWidgetEngine);

    /* start lua script engine if available */
    if (NULL != _pLua)
    {
        BDBG_WRN(("starting lua script engine for atlas number: %d", _number));
        _pLua->run(_pWidgetEngine);
    }

    _pWidgetEngine->start();

    if (NULL != _pLua)
    {
        _pLua->stop();
    }

    return(ret);
} /* run */

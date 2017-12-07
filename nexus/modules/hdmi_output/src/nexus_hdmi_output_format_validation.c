/******************************************************************************
 *  Copyright (C) 2017 Broadcom. The term "Broadcom" refers to Broadcom Limited and/or its subsidiaries.
 *
 *  This program is the proprietary software of Broadcom and/or its licensors,
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
 ******************************************************************************/

#include "nexus_hdmi_output_module.h"


BDBG_MODULE(nexus_hdmi_output_format_validation);

/* create the table */
typedef struct NEXUS_HdmiOutput_P_VideoSettings {
    NEXUS_ColorSpace colorSpace;
    NEXUS_HdmiColorDepth colorDepth;
} NEXUS_HdmiOutput_P_VideoSettings;

static const NEXUS_HdmiOutput_P_VideoSettings uhdVideoSettingsPriorityTable[] =
{
    { NEXUS_ColorSpace_eYCbCr422, NEXUS_HdmiColorDepth_e12bit },
    { NEXUS_ColorSpace_eYCbCr420, NEXUS_HdmiColorDepth_e12bit },
    { NEXUS_ColorSpace_eYCbCr420, NEXUS_HdmiColorDepth_e10bit },
    { NEXUS_ColorSpace_eYCbCr444, NEXUS_HdmiColorDepth_e8bit },
    { NEXUS_ColorSpace_eYCbCr420, NEXUS_HdmiColorDepth_e8bit }
};

static uint8_t numUhdVideoSettingsPriorityTableEntries =
    sizeof(uhdVideoSettingsPriorityTable) /
    sizeof(*uhdVideoSettingsPriorityTable) ;


static const NEXUS_HdmiOutput_P_VideoSettings nonUhdVideoSettingsPriorityTable[] =
{
    { NEXUS_ColorSpace_eYCbCr444, NEXUS_HdmiColorDepth_e10bit },
    { NEXUS_ColorSpace_eYCbCr422, NEXUS_HdmiColorDepth_e12bit },
    { NEXUS_ColorSpace_eYCbCr444, NEXUS_HdmiColorDepth_e12bit },
    { NEXUS_ColorSpace_eYCbCr444, NEXUS_HdmiColorDepth_e8bit },
};

static uint8_t numNonUhdVideoSettingsPriorityTableEntries =
    sizeof(nonUhdVideoSettingsPriorityTable) /
    sizeof(*nonUhdVideoSettingsPriorityTable) ;



static const char * NEXUS_ColorSpace_Text[NEXUS_ColorSpace_eMax] =  {
    "Auto",
    "Rgb",
    "YCbCr422",   /* 2 */
    "YCbCr444",
    "YCbCr420",   /* 4 */
} ;

static void NEXUS_HdmiOutput_SelectSafeFormat_priv(
    NEXUS_HdmiOutputVideoSettings *preferred /* [out] */
)
{
    BKNI_Memset(preferred, 0, sizeof(*preferred)) ;

    preferred->videoFormat = NEXUS_VideoFormat_eVesa640x480p60hz ;
    preferred->colorDepth = 8 ;
    preferred->colorSpace = NEXUS_ColorSpace_eRgb ;
}


void NEXUS_HdmiOutput_RestorePrevSettings_priv(NEXUS_HdmiOutputHandle hdmiOutput)
{
    NEXUS_HdmiOutputSettings *previousSettings ;

    previousSettings = BKNI_Malloc(sizeof(NEXUS_HdmiOutputSettings)) ;
    if (previousSettings == NULL)
    {
        BERR_TRACE(NEXUS_OUT_OF_SYSTEM_MEMORY) ;
        return ;
    }

    BDBG_WRN(("Unable to apply requested settings; restoring previous settings")) ;
    *previousSettings = hdmiOutput->previousSettings;

    hdmiOutput->formatChangeUpdate = true;
    NEXUS_HdmiOutput_SetSettings(hdmiOutput, previousSettings);
    BKNI_Free(previousSettings) ;
}


static NEXUS_Error NEXUS_HdmiOutput_SelectEdidPreferredFormat_priv(
    NEXUS_HdmiOutputHandle hdmiOutput,
    NEXUS_HdmiOutputVideoSettings *preferred /* [out] */
)
{
    NEXUS_Error errCode = NEXUS_SUCCESS ;
    NEXUS_HdmiOutputEdidData *edid = NULL ;
    BHDM_TxSupport platformHdmiOutputSupport ;

    /* set default to safe mode format in case of EDID errors */
    NEXUS_HdmiOutput_SelectSafeFormat_priv(preferred) ;

    edid = BKNI_Malloc(sizeof(*edid));
    if (!edid) {errCode = BERR_TRACE(NEXUS_OUT_OF_SYSTEM_MEMORY); goto done ;}

    /* Get the Capabilities of the attached Rx */
    errCode = NEXUS_HdmiOutput_GetEdidData(hdmiOutput, edid) ;
    if (errCode) {BERR_TRACE(errCode); goto done ;}

    /* Get the Capabilities of the Tx */
    errCode = BHDM_GetTxSupportStatus(hdmiOutput->hdmHandle, &platformHdmiOutputSupport) ;
    if (errCode) {BERR_TRACE(errCode); goto done ;}

    preferred->videoFormat = edid->basicData.preferredVideoFormat ;

    /* use 420 colorSpace if preferred format is 4K */
    if  (((preferred->videoFormat == NEXUS_VideoFormat_e3840x2160p60hz)
    || (preferred->videoFormat == NEXUS_VideoFormat_e3840x2160p50hz))
    && (platformHdmiOutputSupport.YCbCr420))  /* platform can support 4K) */
    {
        preferred->colorSpace = NEXUS_ColorSpace_eYCbCr420 ;
    }
    else {
        NEXUS_HdmiOutputEdidVideoFormatSupport stPreferredVideoFormatSupport  ;

        /* Get the supported features of the Rx/EDID's preferred format (colorspace, 3d support, etc.) */
        errCode = NEXUS_HdmiOutput_GetVideoFormatSupport(hdmiOutput,
            preferred->videoFormat, &stPreferredVideoFormatSupport) ;
        if (errCode) {BERR_TRACE(errCode); goto done ;}

        if (!stPreferredVideoFormatSupport.yCbCr444rgb444)  /* no standard HDMI 1.x 4:4:4 support */
        {
            preferred->videoFormat = NEXUS_VideoFormat_e1080p ;  /* TODO use 2nd Preferred Format */
            preferred->colorSpace = NEXUS_ColorSpace_eYCbCr444 ;
        }
    }

    if (!edid->hdmiVsdb.yCbCr422 && !edid->hdmiVsdb.yCbCr444)
        preferred->colorSpace = NEXUS_ColorSpace_eRgb ;

    BDBG_WRN(("Switching to EDID preferred format %s",
        NEXUS_P_VideoFormat_ToStr_isrsafe(preferred->videoFormat))) ;

    preferred->colorDepth = NEXUS_HdmiColorDepth_e8bit ;

done:
    if (edid)
        BKNI_Free(edid) ;

    return errCode ;
}


static void NEXUS_HdmiOutput_OverrideVideoSettings_priv(
    NEXUS_HdmiOutputHandle hdmiOutput,
    const NEXUS_HdmiOutputVideoSettings *requested,
    NEXUS_HdmiOutputVideoSettings *preferred)
{

    if ((preferred->colorSpace != requested->colorSpace)
    && (!hdmiOutput->displaySettings.overrideMatrixCoefficients))
    {
        BDBG_MSG(("Override requested color space of %s (%d) with %s (%d)",
            NEXUS_ColorSpace_Text[requested->colorSpace], requested->colorSpace,
            NEXUS_ColorSpace_Text[preferred->colorSpace], preferred->colorSpace)) ;

        /* set override flag if the override value is different than current setting */
        hdmiOutput->displaySettings.colorSpace = preferred->colorSpace ;
    }

    if (preferred->colorDepth != requested->colorDepth)
    {
        BDBG_MSG(("Override requested color depth of %d with %d",
            requested->colorDepth, preferred->colorDepth)) ;

        /* set override flag if the override value is different than current setting */
        hdmiOutput->displaySettings.colorDepth = preferred->colorDepth ;
    }
}


static NEXUS_Error NEXUS_HdmiOutput_VideoFormatTmdsBitRate_priv(
    NEXUS_HdmiOutputHandle hdmiOutput,
    const NEXUS_HdmiOutputVideoSettings *videoSettings,
    uint32_t *tmdsRate  /* [out] */
)

{
    NEXUS_Error errCode = NEXUS_SUCCESS ;
    BFMT_VideoFmt magnumFormat ;
    const BFMT_VideoInfo *pVideoFormatInfo ;

    BSTD_UNUSED(hdmiOutput) ;

    errCode = NEXUS_P_VideoFormat_ToMagnum_isrsafe(videoSettings->videoFormat, &magnumFormat) ;
    if ( errCode )
    {
        errCode = BERR_TRACE(errCode);
        return errCode ;
    }
    pVideoFormatInfo = BFMT_GetVideoFormatInfoPtr(magnumFormat) ;
    if (pVideoFormatInfo == NULL)
    {
        BDBG_ERR(("Unable to get valid BFMT Video Format Info pointer")) ;
        errCode = BERR_TRACE(NEXUS_NOT_INITIALIZED) ;
        return errCode ;
    }

    switch (videoSettings->colorSpace)
    {
    case NEXUS_ColorSpace_eRgb:
    case NEXUS_ColorSpace_eYCbCr444 :
        *tmdsRate = pVideoFormatInfo->ulPxlFreq * videoSettings->colorDepth / 8 ;
        break ;

    case NEXUS_ColorSpace_eYCbCr420 :
        *tmdsRate = pVideoFormatInfo->ulPxlFreq * (videoSettings->colorDepth / 8) / 2 ;
        break ;

    case NEXUS_ColorSpace_eYCbCr422 :
        *tmdsRate = pVideoFormatInfo->ulPxlFreq ;
        break ;

    default :
        BDBG_WRN(("AutoColor Space Selected; Use 422 to determine TMDS Rate")) ;
        *tmdsRate = pVideoFormatInfo->ulPxlFreq ;
        break ;
    }

    /* ulPxlFreq is stored as a multiple of BFMT_FREQ_FACTOR (100) */
    /* e.g. 74.25 x BFMT_FREQ_FACTOR = 7425 */
    *tmdsRate = *tmdsRate / BFMT_FREQ_FACTOR ;


    BDBG_MSG(("<%s> TMDS Rate of %d MHz calculated with Colorspace: %s  ColorDepth: %d  Pixel Freq: %d",
        pVideoFormatInfo->pchFormatStr,
        *tmdsRate, NEXUS_ColorSpace_Text[videoSettings->colorSpace],
        videoSettings->colorDepth,
        pVideoFormatInfo->ulPxlFreq / BFMT_FREQ_FACTOR)) ;

    return errCode ;
}


/**
Summary:
Check if the requested 4K 50/60 Hz Video Settings are supported by both the TV and the STB.
If not, reduce the settings to the best possible.
**/
static bool NEXUS_HdmiOutput_IsValid4KVideoSettings_priv(
    NEXUS_HdmiOutputHandle hdmiOutput,
    NEXUS_VideoFormat videoFormat,
    const NEXUS_HdmiOutput_P_VideoSettings *pEntry,
    const NEXUS_HdmiOutputEdidData *rXCapabilities,
    const BHDM_TxSupport *tXCapabilities
)
{
    NEXUS_Error errCode ;
    NEXUS_HdmiOutputEdidVideoFormatSupport rxVideoFormatSupport ;
    BHDM_TxSupport platformHdmiOutputSupport ;
    NEXUS_HdmiOutputVideoSettings videoSettings ;
    uint32_t tmdsRate ;
    bool supported ;


    supported = false ;
    errCode = BHDM_GetTxSupportStatus(hdmiOutput->hdmHandle, &platformHdmiOutputSupport) ;
    if (errCode) { BERR_TRACE(errCode); goto done ;}

    /* For the requested format, get the features supported by the attached Rx (colorspaces, 3d support, etc.) */
    errCode = NEXUS_HdmiOutput_GetVideoFormatSupport(hdmiOutput,
        videoFormat, &rxVideoFormatSupport) ;
    if (errCode) { BERR_TRACE(errCode); goto done ;}

    /*****************/
    /*  Color Space   */
    /*****************/
    switch (pEntry->colorSpace)
    {
    case NEXUS_ColorSpace_eYCbCr422:
        supported = (tXCapabilities->YCbCr422 && rxVideoFormatSupport.yCbCr444rgb444) ;
        break ;

    case NEXUS_ColorSpace_eYCbCr444:
        supported = (tXCapabilities->YCbCr422 && rxVideoFormatSupport.yCbCr444rgb444) ;
        break ;

    case NEXUS_ColorSpace_eYCbCr420:
        supported = (tXCapabilities->YCbCr420 && rxVideoFormatSupport.yCbCr420) ;
        break ;

    default:
        /* not valid for 4K */
        supported = false ;
    }

    if (!supported)
    {
        goto done ;
    }

    /* determine the TMDS Character Rate and make sure Rx can support */
    BKNI_Memset(&videoSettings, 0, sizeof(NEXUS_HdmiOutputVideoSettings)) ;

    tmdsRate = 0 ;
    videoSettings.videoFormat = videoFormat ;
    videoSettings.colorSpace = pEntry->colorSpace ;
    videoSettings.colorDepth = pEntry->colorDepth ;
    errCode = NEXUS_HdmiOutput_VideoFormatTmdsBitRate_priv(hdmiOutput, &videoSettings, &tmdsRate) ;
    if ((errCode) || (!tmdsRate))
    {
        supported = false ;
        BERR_TRACE(errCode) ;
        goto done ;
    }

    /* confirm support for video format tmds rate */
    supported =
          (((rXCapabilities->hdmiVsdb.valid) && (tmdsRate <= rXCapabilities->hdmiVsdb.maxTmdsClockRate))
        || ((rXCapabilities->hdmiForumVsdb.valid) && (tmdsRate <= rXCapabilities->hdmiForumVsdb.maxTMDSCharacterRate))) ;

    BDBG_MSG(("Video Format TMDS Rate: %d < HDMI Rx Max TMDS Rate: %d  --  %s",
        tmdsRate, rXCapabilities->hdmiForumVsdb.maxTMDSCharacterRate,
        supported ? "SUPPORTED" : "***NOT SUPPORTED***")) ;

    if (!supported)
    {
        goto done ;
    }

    /* the HDMI Rx Supports the clock rates for the selected video format */
    /* now confirm the colordepth support is explicitly declared in the VSDB blocks */

    /*****************/
    /*  Color Depth   */
    /*****************/
    switch( pEntry->colorDepth )
    {

    /*****  8 Bit *****/
    case NEXUS_HdmiColorDepth_e8bit:
        /* All 4K 50/60 colorSpaces support 8bit */
        supported = true ;
        break ;

    /***** 10 Bit *****/
    case NEXUS_HdmiColorDepth_e10bit:
        switch (pEntry->colorSpace)
        {
        case NEXUS_ColorSpace_eYCbCr422:
            /* Per HDMI spec, Colorspace YCbCr 4:2:2 is always 12 bit */
            /* colordepth setting of 10 is ignored */
            supported = true ;
            break ;

        case NEXUS_ColorSpace_eYCbCr420:
            supported = rXCapabilities->hdmiForumVsdb.deepColor420_30bit ;
            break ;

        case NEXUS_ColorSpace_eYCbCr444:
            /* 4Kp50/60 YCbCr 4:4:4 10 bit is not supported by HDMI 2.0 */
            /* 4Kp30/25/24 YCbCr 4:4:4 10 bit are supported */
            supported =
                ((videoFormat != NEXUS_VideoFormat_e3840x2160p50hz)
            && (videoFormat != NEXUS_VideoFormat_e3840x2160p60hz)) ;
            if (!supported)
            {
                BDBG_WRN(("2160p50/60 YCbCr 4:4:4 10 Bit is not supported")) ;
            }
            break ;

        default:
            supported = false ;
         }
        break ;

    /***** 12 Bit *****/
    case NEXUS_HdmiColorDepth_e12bit:
        switch (pEntry->colorSpace)
        {
        case NEXUS_ColorSpace_eYCbCr422:
            /* HDMI Colorspace YCbCr 4:2:2 is always 12 bit */
            supported = true ;
            break ;

        case NEXUS_ColorSpace_eYCbCr420:
            supported = rXCapabilities->hdmiForumVsdb.deepColor420_36bit ;
            break ;

        case NEXUS_ColorSpace_eYCbCr444:
            /* 4Kp50/60 YCbCr 4:4:4 12 bit is not supported by HDMI 2.0 */
            /* 4Kp30/25/24 YCbCr 4:4:4 12 bit are supported */
            supported =
                ((videoFormat != NEXUS_VideoFormat_e3840x2160p50hz)
            && (videoFormat != NEXUS_VideoFormat_e3840x2160p60hz)) ;
            if (!supported)
            {
                BDBG_WRN(("2160p50/60 YCbCr 4:4:4 12 Bit is not supported")) ;
            }
            break ;

        default:
            supported = false ;
        }
        break ;

    default:
        supported = false ;
    }


done:
    return( supported );
}


/**
Summary:
Check if the requested NEXUS_HdmiOutputVideoSettings are valid for 4Kp50/60 formats
This check does not include HDMI 1.4 4K formats 4Kp30, 4Kp25, and 4Kp24
NEXUS_HdmiOutputVideoSettings must be supported by both the TV and the STB.
If not, return the best possible preferred NEXUS_HdmiOutputVideoSettings
The validation does not include 4Kp30 and below
**/
static NEXUS_Error NEXUS_HdmiOutput_ValidateVideoSettings4K_priv(
    NEXUS_HdmiOutputHandle hdmiOutput,
    const NEXUS_HdmiOutputVideoSettings *requested,
    NEXUS_HdmiOutputVideoSettings *preferred /* [out] */
)
{
    NEXUS_Error rc = NEXUS_SUCCESS ;
    NEXUS_HdmiOutputEdidVideoFormatSupport stRequestedVideoFormatSupport  ;
    NEXUS_HdmiOutputEdidData *edid = NULL ;
    BHDM_TxSupport platformHdmiOutputSupport ;
    unsigned idx = 0;
    unsigned numEntries;
    bool matchFound;
    bool bUhdFormat ;
    NEXUS_HdmiOutputVideoSettings localRequested ;
    const NEXUS_HdmiOutput_P_VideoSettings *priorityTable;

    BKNI_Memset(preferred, 0, sizeof(*preferred));

    /* make/use a copy of the requested VideoSettings for validation */
    localRequested = *requested ;


    /* Get the Capabilities of the Tx */
    rc = BHDM_GetTxSupportStatus(hdmiOutput->hdmHandle, &platformHdmiOutputSupport) ;
    if (rc) {BERR_TRACE(rc); goto done ;}

    edid = BKNI_Malloc(sizeof(*edid));
    if (!edid) {rc = BERR_TRACE(NEXUS_OUT_OF_SYSTEM_MEMORY); goto done ;}

    /* Get the Capabilities of the attached Rx */
    rc = NEXUS_HdmiOutput_GetEdidData(hdmiOutput, edid);
    if (rc) {BERR_TRACE(rc); goto done ;}

    /* flag usage of invalid EDID */
    if (!edid->valid)
    {
        BDBG_ERR(("Validating 4K format against an invalid/unknown EDID; defaulting to VGA")) ;
        NEXUS_HdmiOutput_SelectSafeFormat_priv(preferred) ;
        goto overrideVideoSettings ;
    }

    if (localRequested.videoFormat == NEXUS_VideoFormat_eUnknown)
    {
        rc = NEXUS_HdmiOutput_SelectEdidPreferredFormat_priv(hdmiOutput, preferred) ;
        goto overrideVideoSettings ;
    }

    preferred->videoFormat = localRequested.videoFormat ;

    bUhdFormat =
        ((localRequested.videoFormat == NEXUS_VideoFormat_e3840x2160p50hz)
        || (localRequested.videoFormat == NEXUS_VideoFormat_e3840x2160p60hz)) ;

    /* can the platform support 420 */
    if (bUhdFormat && !platformHdmiOutputSupport.YCbCr420)
    {
        BDBG_WRN(("Platform does not support the 422/420 Colorspace required for 4K formats; selecting a preferred/alternate format instead")) ;
        rc = NEXUS_HdmiOutput_SelectEdidPreferredFormat_priv(hdmiOutput, preferred) ;
        goto overrideVideoSettings ;
    }

    /* can TV support a 4K format? */
    /* Get the supported features of the requested format (colorspace, 3d support, etc.) */
    rc = NEXUS_HdmiOutput_GetVideoFormatSupport(hdmiOutput,
        localRequested.videoFormat, &stRequestedVideoFormatSupport) ;
    if (rc)
    {
        BDBG_WRN(("Error detecting TV/EDID video format support; selecting a preferred/alternate format instead")) ;
        rc = BERR_TRACE(rc);
        rc = NEXUS_HdmiOutput_SelectEdidPreferredFormat_priv(hdmiOutput, preferred) ;
        goto overrideVideoSettings ;
    }

    if ((!stRequestedVideoFormatSupport.yCbCr420)
    &&  (!stRequestedVideoFormatSupport.yCbCr444rgb444))
    {
        BDBG_WRN(("HDMI Rx does not support 422/420 Colorspace required for 4K formats; selecting a preferred/alternate format instead")) ;
        rc = NEXUS_HdmiOutput_SelectEdidPreferredFormat_priv(hdmiOutput, preferred) ;
        goto overrideVideoSettings ;
    }


    if (bUhdFormat)
    {
        priorityTable = uhdVideoSettingsPriorityTable ;
        numEntries = numUhdVideoSettingsPriorityTableEntries ;
    }
    else
    {
        priorityTable = nonUhdVideoSettingsPriorityTable ;
        numEntries = numNonUhdVideoSettingsPriorityTableEntries ;
    }

#if BDBG_DEBUG_BUILD
    /* debug of priority table */
    BDBG_MSG((" ")) ;
    BDBG_MSG(("2160p %s Priority Table", bUhdFormat ? "50/60Hz" : "30Hz")) ;
    for (idx = 0; idx < numEntries ; idx++)
    {
        BDBG_MSG(("PriorityTable[%d] : ColorSpace: %s; ColorDepth: %d", idx,
            NEXUS_ColorSpace_Text[priorityTable[idx].colorSpace],
            priorityTable[idx].colorDepth)) ;
    }
    BDBG_MSG((" ")) ;

    BDBG_MSG(("Requested colorSpace: %s (%d)  colordepth: %d",
        NEXUS_ColorSpace_Text[localRequested.colorSpace], localRequested.colorSpace,
        localRequested.colorDepth)) ;
    BDBG_MSG(("EDID: SCDC Support %s; Max TMDS Character Rate: %d",
        edid->hdmiForumVsdb.scdc ? "Yes" : "No",
        edid->hdmiForumVsdb.maxTMDSCharacterRate)) ;
#endif


    matchFound = false ;

    /********************/
    /* Auto Color Space */
    /********************/
    if (localRequested.colorSpace == NEXUS_ColorSpace_eAuto)
    {
        if (bUhdFormat)
        {
            BDBG_MSG(("For 4K p50/60, Always use best colorspace YCbCr 4:2:2")) ;
            localRequested.colorSpace = NEXUS_ColorSpace_eYCbCr422 ;
        }
        else
        {
            BDBG_MSG(("For 4K up to p30, Always use best colorspace YCbCr 4:4:4")) ;
            localRequested.colorSpace = NEXUS_ColorSpace_eYCbCr444 ;
        }
    }

    /********************/
    /* Auto Color Depth */
    /********************/
    /* when getting Auto Color Depth always get the best supported for 4K formats */
    if (localRequested.colorDepth == NEXUS_HdmiColorDepth_eAuto)
    {
        BDBG_MSG(("For 4K formats, always use maximum color depth available")) ;
        localRequested.colorDepth = NEXUS_HdmiColorDepth_eAuto ;
    }

    if (( localRequested.colorDepth > NEXUS_HdmiColorDepth_e8bit)
    &&  (edid->hdmiForumVsdb.maxTMDSCharacterRate <= BHDM_HDMI_1_4_MAX_RATE))
    {
        BDBG_WRN(("Attached Rx cannot support Color Depth %d; default to 8",
            requested->colorDepth)) ;
        localRequested.colorDepth = 8 ;
    }

    /* YCbCr 422/444 requires SCDC support and HF-VSDB Max TMDS Rate > 297 */
    if ((bUhdFormat)
    && ((localRequested.colorSpace == NEXUS_ColorSpace_eYCbCr422)
        || (localRequested.colorSpace == NEXUS_ColorSpace_eYCbCr444))
    && ((!edid->hdmiForumVsdb.scdc)
        ||(edid->hdmiForumVsdb.maxTMDSCharacterRate <= BHDM_HDMI_1_4_MAX_RATE)))
    {
        BDBG_WRN(("Attached Rx cannot support Color Space YCbCr 422/444; default to YCbCr 4:2:0")) ;
        localRequested.colorSpace = NEXUS_ColorSpace_eYCbCr420 ;
    }

    if (localRequested.colorSpace == NEXUS_ColorSpace_eRgb)
    {

        /* when checking our priority table and RGB is requested; search using YCbCr 444 Colorspace
            since it is the same timing as RGB 444
        */
        localRequested.colorSpace = NEXUS_ColorSpace_eYCbCr444 ;
    }

    if ((localRequested.colorSpace != NEXUS_ColorSpace_eAuto)
    && (localRequested.colorDepth != NEXUS_HdmiColorDepth_eAuto))
    {
        NEXUS_HdmiOutput_P_VideoSettings videoSettings ;

        /* application specified colorSpace and colorDepth, validate requested settings */
        videoSettings.colorSpace = localRequested.colorSpace;
        videoSettings.colorDepth = localRequested.colorDepth;
        matchFound = NEXUS_HdmiOutput_IsValid4KVideoSettings_priv(hdmiOutput,
            requested->videoFormat, &videoSettings, edid, &platformHdmiOutputSupport) ;

        if (matchFound)
        {
             preferred->colorSpace = videoSettings.colorSpace;
             preferred->colorDepth = videoSettings.colorDepth;
        }
    }
    else if ((localRequested.colorSpace != NEXUS_ColorSpace_eAuto)
          && (localRequested.colorDepth == NEXUS_HdmiColorDepth_eAuto))
    {
        BDBG_MSG(("Requested Best/Max Color Depth (%d) for ColorSpace: %s (%d)",
            localRequested.colorDepth,
            NEXUS_ColorSpace_Text[localRequested.colorSpace],
            localRequested.colorSpace)) ;

        /* application specified colorSpace, not colorDepth, need to cycle through colorDepth */
        matchFound = false ;
        for (idx = 0; idx < numEntries ; idx++)
        {
            /* skip entries in the priority Table that have colorSpaces that were not requested */
            if (priorityTable[idx].colorSpace != localRequested.colorSpace)
            {
                continue ;
            }

            /* the first entry in the priority table with the requested colorSpace
               should contain the best/preferred colorDepth */
            matchFound = NEXUS_HdmiOutput_IsValid4KVideoSettings_priv(hdmiOutput,
                requested->videoFormat, &priorityTable[idx],
                edid, &platformHdmiOutputSupport) ;

            if (matchFound)
            {
                BDBG_MSG(("Use Video Settings Priority Table index %d", idx)) ;
                preferred->colorSpace = priorityTable[idx].colorSpace;
                preferred->colorDepth = priorityTable[idx].colorDepth;
                break ;
            }
        }
    }
    else if ((localRequested.colorSpace == NEXUS_ColorSpace_eAuto)
          && (localRequested.colorDepth != NEXUS_HdmiColorDepth_eAuto))
    {
        /* application specified colorDepth, not colorSpace, need to cycle through colorSpace */
        for (idx = 0; idx < numEntries ; idx++)
        {
            if (priorityTable[idx].colorSpace == localRequested.colorSpace)
            {
                matchFound = NEXUS_HdmiOutput_IsValid4KVideoSettings_priv(hdmiOutput,
                    requested->videoFormat, &priorityTable[idx],
                    edid, &platformHdmiOutputSupport) ;

                if (matchFound)
                {
                    preferred->colorSpace = priorityTable[idx].colorSpace;
                    preferred->colorDepth = priorityTable[idx].colorDepth;
                    break ;
                }
            }
        }
    }

    if (!matchFound)
    {
        /* now find the best available color parameter */
        for (idx = 0; idx < numEntries; idx++)
        {
            matchFound = NEXUS_HdmiOutput_IsValid4KVideoSettings_priv(hdmiOutput,
                requested->videoFormat, &priorityTable[idx],
                edid, &platformHdmiOutputSupport) ;

            if (matchFound)
            {
                preferred->colorSpace = priorityTable[idx].colorSpace;
                preferred->colorDepth = priorityTable[idx].colorDepth;
                BDBG_WRN(("Override with Priority Table index %d: Colorspace %d  ColorDepth: %d",
                    idx, preferred->colorSpace, preferred->colorDepth)) ;
                break ;
            }
        }
    }

    /* if requested colorspace was RGB (i.e. YCbCr was used just for timing look up */
    /* restore RGB as the preferred colorSpace  */
    if (requested->colorSpace == NEXUS_ColorSpace_eRgb)
    {
        preferred->colorSpace = NEXUS_ColorSpace_eRgb ;
    }

overrideVideoSettings :
    NEXUS_HdmiOutput_OverrideVideoSettings_priv(hdmiOutput, requested, preferred) ;

done:
    if (edid) {
        BKNI_Free(edid);
    }

    return rc ;
}



/**
Summary:
Check if the requested NEXUS_HdmiOutputVideoSettings are valid for non 4Kp50/60 formats.
This check includes HDMI 1.4 4K formats 4Kp30, 4Kp25, and 4Kp24
NEXUS_HdmiOutputVideoSettings must be supported by both the TV and the STB.
If not, return the best possible preferred NEXUS_HdmiOutputVideoSettings
**/
static NEXUS_Error NEXUS_HdmiOutput_ValidateVideoSettingsNon4K_priv(
    NEXUS_HdmiOutputHandle hdmiOutput,
    const NEXUS_HdmiOutputVideoSettings *requested,
    NEXUS_HdmiOutputVideoSettings *preferred /* [out] */
)
{
    NEXUS_Error rc = NEXUS_SUCCESS ;
    NEXUS_HdmiOutputEdidVideoFormatSupport stRequestedVideoFormatSupport  ;
    NEXUS_HdmiOutputEdidData *edid = NULL ;
    BHDM_TxSupport platformHdmiOutputSupport ;
    bool requestedColorDepthSupported ;


    if (requested->videoFormat == NEXUS_VideoFormat_eUnknown)
    {
        BDBG_ERR(("Validating an unknown format; defaulting to safe format")) ;
        NEXUS_HdmiOutput_SelectSafeFormat_priv(preferred) ;
        goto overrideVideoSettings ;
    }

    /* Get the Capabilities of the Tx */
    rc = BHDM_GetTxSupportStatus(hdmiOutput->hdmHandle, &platformHdmiOutputSupport) ;
    if (rc) {BERR_TRACE(rc); goto done ;}

    /* Get the Capabilities of the attached Rx */
    edid = BKNI_Malloc(sizeof(*edid));
    if (!edid) {rc= BERR_TRACE(NEXUS_OUT_OF_SYSTEM_MEMORY); goto done ;}

    rc = NEXUS_HdmiOutput_GetEdidData(hdmiOutput, edid);
    if (rc) {BERR_TRACE(rc); goto done ;}

    /* flag usage of invalid EDID */
    if (!edid->valid)
    {
        BDBG_ERR(("Validating Non4K format against an invalid/unknown EDID; defaulting to safe format")) ;
        NEXUS_HdmiOutput_SelectSafeFormat_priv(preferred) ;
        goto overrideVideoSettings ;
    }

    /* Check the requested format settings (colorspace, etc.) */
    rc = NEXUS_HdmiOutput_GetVideoFormatSupport(hdmiOutput,
        requested->videoFormat, &stRequestedVideoFormatSupport) ;
    if (rc)
    {
        BDBG_ERR(("Error detecting TV/EDID video format support; selecting a preferred/alternate format instead")) ;
        rc = BERR_TRACE(rc);
        rc = NEXUS_HdmiOutput_SelectEdidPreferredFormat_priv(hdmiOutput, preferred) ;
        goto overrideVideoSettings ;
    }

    preferred->videoFormat = requested->videoFormat ;
    /************/
    /* Color Space */
    /************/
    switch(requested->colorSpace)
    {
    case  NEXUS_ColorSpace_eYCbCr420 :
        BDBG_WRN(("4:2:0 Color Space is not supported for non 4K format %s; Use 4:4:4 instead",
			NEXUS_P_VideoFormat_ToStr_isrsafe(requested->videoFormat))) ;
        preferred->colorSpace = NEXUS_ColorSpace_eYCbCr444 ;
        break ;

    case  NEXUS_ColorSpace_eYCbCr422 :
        if (!platformHdmiOutputSupport.YCbCr422)
        {
            BDBG_WRN(("Platform does not support the 422/420 Colorspace required for non 4K formats; Use 4:4:4 instead")) ;
            preferred->colorSpace = NEXUS_ColorSpace_eYCbCr444 ;
        }
        else
        {
            preferred->colorSpace = NEXUS_ColorSpace_eYCbCr422 ;
        }
        break ;

    case  NEXUS_ColorSpace_eRgb :
        preferred->colorSpace = NEXUS_ColorSpace_eRgb ;
        break ;

    default : /* use 444 colorspace */
        preferred->colorSpace = NEXUS_ColorSpace_eYCbCr444 ;
        break ;
    }

    /* non-4K 50/60 formats using 444 colorspace cannot exceed 8 bits on Rxs that do not support it */
    requestedColorDepthSupported = ((edid->hdmiVsdb.valid)
        && (((requested->colorDepth == 10) && (edid->hdmiVsdb.deepColor30bit))
          || ((requested->colorDepth == 12) && (edid->hdmiVsdb.deepColor36bit))
          || ((requested->colorDepth == 16) && (edid->hdmiVsdb.deepColor48bit)))) ;

    if (((preferred->colorSpace == NEXUS_ColorSpace_eRgb) || (preferred->colorSpace == NEXUS_ColorSpace_eYCbCr444))
    &&  (requested->colorDepth > 8) && (!requestedColorDepthSupported))
    {
        BDBG_WRN(("Attached Rx cannot support Color Depth %d; default to 8", requested->colorDepth)) ;
        preferred->colorDepth = 8 ;
    }
    else
    {
        /***********/
        /*Color Depth */
        /***********/
        switch (requested->colorDepth)
        {
        default :
            BDBG_WRN(("Unknown requested Color Depth %d ; Using Auto Color Depth",
                requested->colorDepth)) ;

            /* FALL  THROUGH */

        case 0 : /* For non-4k auto colordepth(=0) */

            /* ***FALL THROUGH*** */

        case NEXUS_HdmiColorDepth_e16bit:
            BDBG_MSG(("16 bit Color Depth is not supported on this platform... checking lower color depths")) ;

            /* ***FALL THROUGH*** */

        case NEXUS_HdmiColorDepth_e12bit:
            if (edid->hdmiVsdb.deepColor36bit)
            {
                preferred->colorDepth = 12 ;
                break ;
            }
            BDBG_WRN(("12 bit Color Depth is not supported by <%s> Rx... checking lower color depths",
                edid->basicData.monitorName)) ;

            /* ***FALL THROUGH*** */

        case NEXUS_HdmiColorDepth_e10bit:
            if (edid->hdmiVsdb.deepColor30bit)
            {
                preferred->colorDepth = 10 ;
                break ;
            }
            BDBG_WRN(("10 bit Color Depth is not supported by <%s>... will use standard 8 bit Color",
                edid->basicData.monitorName)) ;

            /* ***FALL THROUGH*** */

        case NEXUS_HdmiColorDepth_e8bit :
            preferred->colorDepth = 8 ;
            break ;
        }
    }

    /* validate the requested colorspace if override not specified (overrideMatrixCoefficients) */
    if (!hdmiOutput->displaySettings.overrideMatrixCoefficients)
   {
        if (!edid->hdmiVsdb.valid)  /* No VSDB... DVI support only */
        {
	        preferred->colorSpace = NEXUS_ColorSpace_eRgb;
        }
        else if ((!edid->hdmiVsdb.yCbCr422) && (!edid->hdmiVsdb.yCbCr444)
        && ((requested->colorSpace == NEXUS_ColorSpace_eYCbCr444)
        ||  (requested->colorSpace == NEXUS_ColorSpace_eYCbCr422)
        ||  (requested->colorSpace == NEXUS_ColorSpace_eAuto)))
        {
            preferred->colorSpace = NEXUS_ColorSpace_eRgb;
        }
    }

overrideVideoSettings :
    NEXUS_HdmiOutput_OverrideVideoSettings_priv(hdmiOutput, requested, preferred) ;

done:
    if (edid)
        BKNI_Free(edid) ;

    return rc ;

}


NEXUS_Error NEXUS_HdmiOutput_ValidateVideoSettings_priv(
    NEXUS_HdmiOutputHandle hdmiOutput,
    const NEXUS_HdmiOutputVideoSettings *requested,
    NEXUS_HdmiOutputVideoSettings *preferred /* [out] */
)
{
    NEXUS_Error errCode ;
    uint8_t deviceAttached ;

    /* Check for device */
    errCode = BHDM_RxDeviceAttached(hdmiOutput->hdmHandle, &deviceAttached) ;
    BERR_TRACE(errCode) ;
    if (!deviceAttached)
    {
        BDBG_WRN(("HdmiOutput is not connected; Video Settings cannot be validated")) ;
        errCode = NEXUS_NOT_AVAILABLE ;
        goto done ;
    }


    BDBG_MSG(("===> Request Format: %s (%d)  Colorspace: %s (%d); Colordepth: %d",
        NEXUS_P_VideoFormat_ToStr_isrsafe(requested->videoFormat), requested->videoFormat,
        NEXUS_ColorSpace_Text[requested->colorSpace], requested->colorSpace,
        requested->colorDepth)) ;

    if ((requested->videoFormat == NEXUS_VideoFormat_e3840x2160p60hz)
    || (requested->videoFormat == NEXUS_VideoFormat_e3840x2160p50hz)
    || (requested->videoFormat == NEXUS_VideoFormat_e3840x2160p30hz)
    || (requested->videoFormat == NEXUS_VideoFormat_e3840x2160p25hz)
    || (requested->videoFormat == NEXUS_VideoFormat_e3840x2160p24hz))
    {
        /*****************/
        /* Validate 4K Format */
        /*****************/
        errCode = NEXUS_HdmiOutput_ValidateVideoSettings4K_priv(hdmiOutput, requested, preferred) ;
    }
    else
    {
        /*********************/
        /* Validate NON 4K Format */
        /*********************/
        errCode = NEXUS_HdmiOutput_ValidateVideoSettingsNon4K_priv(hdmiOutput, requested, preferred) ;
    }

    BDBG_MSG(("<=== Recommend Format: %s; Colorspace: (%d) %s; Colordepth: %d",
		NEXUS_P_VideoFormat_ToStr_isrsafe(preferred->videoFormat),
        preferred->colorSpace, NEXUS_ColorSpace_Text[preferred->colorSpace],
        preferred->colorDepth)) ;

done:
    return errCode ;
}

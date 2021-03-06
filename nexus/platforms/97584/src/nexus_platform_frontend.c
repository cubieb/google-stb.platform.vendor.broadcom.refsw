 /***************************************************************************
*     (c)2004-2014 Broadcom Corporation
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
* Module Description:
*
* Revision History:
*
* $brcm_Log: $
*
***************************************************************************/
#if ((NEXUS_PLATFORM == 97584) || (NEXUS_PLATFORM == 975845))

#include "nexus_types.h"
#include "nexus_platform.h"
#include "priv/nexus_core.h"
#include "nexus_platform_features.h"
#include "nexus_platform_priv.h"
#include "nexus_base.h"
#include "nexus_input_band.h"
#include "bchp_gio.h"

#if NEXUS_HAS_FRONTEND
#include "nexus_frontend.h"
#include "nexus_frontend_3128.h"
#endif
#ifdef NEXUS_FRONTEND_REVERSE_RMAGNUM_SUPPORT
#include "nexus_docsis.h"
#endif

BDBG_MODULE(nexus_platform_frontend);

#if NEXUS_HAS_FRONTEND

#define PLATFORM_MAX_TUNERS 1
NEXUS_TunerHandle tunerHandle[PLATFORM_MAX_TUNERS];
#ifdef NEXUS_FRONTEND_REVERSE_RMAGNUM_SUPPORT
NEXUS_FrontendDeviceHandle hDocsisFrontendDevice = NULL;
#endif

NEXUS_Error NEXUS_Platform_InitFrontend(void)
{
    NEXUS_Error rc = NEXUS_SUCCESS;
    NEXUS_PlatformConfiguration *pConfig = &g_NEXUS_platformHandles.config;
    unsigned i;
    bool outOfBandPrsent = false, ifDacPresent = false;
    NEXUS_FrontendDeviceRecalibrateSettings calibrateSettings;
    NEXUS_FrontendDeviceCapabilities capabilities;
    NEXUS_FrontendCapabilities tunerCapabilities;
    NEXUS_Frontend3128Settings st3128Settings;
    NEXUS_3128ProbeResults results;
    NEXUS_FrontendDevice3128OpenSettings deviceOpenSettings;
    NEXUS_FrontendUserParameters userParams;
    NEXUS_TunerOpen3128Settings tunerOpenSettings;
    NEXUS_FrontendDevice3128Settings deviceSettings;
#ifdef NEXUS_FRONTEND_REVERSE_RMAGNUM_SUPPORT
    NEXUS_DocsisOpenDeviceSettings openDeviceSettings;
#endif

    NEXUS_Frontend_GetDefault3128Settings(&st3128Settings);
    st3128Settings.type = NEXUS_3128ChannelType_eInBand;

    NEXUS_FrontendDevice_GetDefault3128OpenSettings(&deviceOpenSettings);
    deviceOpenSettings.inBandOpenDrain=true;
    deviceOpenSettings.loadAP = true;
    deviceOpenSettings.configureWatchdog = false;
    deviceOpenSettings.isrNumber = 95;
#if !NEXUS_USE_7584_WIFI
    deviceOpenSettings.externalFixedGain.total = 800;     /* These are platform specific values given by the board designer. */
    deviceOpenSettings.externalFixedGain.bypassable = 1500; /* These are platform specific values given by the board designer. */
#endif
    deviceOpenSettings.outOfBand.useWidebandAtoD = true;

    st3128Settings.device = NEXUS_FrontendDevice_Open3128(0, &deviceOpenSettings);
    if(st3128Settings.device == NULL){
        BDBG_ERR(("Unable to open onboard 7584 tuner/demodulator device"));
        return BERR_NOT_INITIALIZED;
    }

    NEXUS_FrontendDevice_GetDefaultRecalibrateSettings(&calibrateSettings);
    calibrateSettings.cppm.enabled = true;
    calibrateSettings.cppm.threshold = 260;
    calibrateSettings.cppm.thresholdHysteresis = 50;
    rc = NEXUS_FrontendDevice_Recalibrate(st3128Settings.device, &calibrateSettings);
    if(rc) return BERR_TRACE(BERR_NOT_INITIALIZED);

    rc = NEXUS_FrontendDevice_Get3128Settings(st3128Settings.device, &deviceSettings);
    if(rc) return BERR_TRACE(BERR_NOT_INITIALIZED);

    deviceSettings.outOfBand.outputMode = NEXUS_FrontendOutOfBandOutputMode_eFec;
    rc =  NEXUS_FrontendDevice_Set3128Settings(st3128Settings.device, &deviceSettings);
    if(rc) return BERR_TRACE(BERR_NOT_INITIALIZED);

    NEXUS_Frontend_Probe3128(&deviceOpenSettings, &results);
    BDBG_MSG(("chip.familyId = 0x%x", results.chip.familyId));
    BDBG_MSG(("chip.id = 0x%x", results.chip.id));
    BDBG_MSG(("version.major = 0x%x", results.chip.version.major ));
    BDBG_MSG(("version.minor = 0x%x", results.chip.version.minor ));

    NEXUS_FrontendDevice_GetCapabilities(st3128Settings.device, &capabilities);

    /* Open downstream tuners */
    for (i=0; i < capabilities.numTuners; i++)
    {
        BKNI_Memset(&tunerCapabilities, 0x0, sizeof(tunerCapabilities));
        NEXUS_FrontendDevice_GetTunerCapabilities(st3128Settings.device, i, &tunerCapabilities);
        if(tunerCapabilities.outOfBand) outOfBandPrsent = true;
        if(tunerCapabilities.ifdac) ifDacPresent = true;
        if(tunerCapabilities.qam){
            BDBG_WRN(("Waiting for frontend(%x_SFF) %d to initialize", results.chip.id, i));

            st3128Settings.channelNumber = i;

            pConfig->frontend[i] = NEXUS_Frontend_Open3128(&st3128Settings);
            if (NULL == pConfig->frontend[i])
            {
                BDBG_ERR(("Unable to open onboard 7584 tuner/demodulator %d", i));
                continue;
            }

            NEXUS_Frontend_GetUserParameters(pConfig->frontend[i], &userParams);
            userParams.isMtsif = deviceOpenSettings.isMtsif;
            if(deviceOpenSettings.isMtsif){
                userParams.param1 = st3128Settings.channelNumber;
            }
            else{
                switch(i)
                {
                case 0:
                    userParams.param1 =  NEXUS_InputBand_e0;
                    break;
                case 1:
                    userParams.param1 =  NEXUS_InputBand_e6;
                    break;
                case 2:
                    userParams.param1 =  NEXUS_InputBand_e7;
                    break;
                case 3:
                    userParams.param1 =  NEXUS_InputBand_e8;
                    break;
                default:
                    BDBG_ERR((" channel type not supported"));
                    return BERR_INVALID_PARAMETER;
                }
            }
            userParams.pParam2 = NULL;
            NEXUS_Frontend_SetUserParameters(pConfig->frontend[i], &userParams);
        }
    }

    if(ifDacPresent){
        BDBG_WRN(("Waiting for ifdac tuner channel to initialize."));
        NEXUS_Tuner_GetDefaultOpen3128Settings(&tunerOpenSettings);
        tunerOpenSettings.device = st3128Settings.device;
        tunerHandle[0] = NEXUS_Tuner_Open3128(0, &tunerOpenSettings);
        if (NULL == tunerHandle[0])
        {
           BDBG_ERR(("Unable to open onboard 7584 Ifdac tuner."));
           return BERR_NOT_INITIALIZED;
        }

#ifdef NEXUS_FRONTEND_REVERSE_RMAGNUM_SUPPORT
        NEXUS_Docsis_GetDefaultOpenDeviceSettings(&openDeviceSettings);
        openDeviceSettings.dataTuner[0] = tunerHandle[0];
        openDeviceSettings.rpcTimeOut = 1000;
        hDocsisFrontendDevice = NEXUS_Docsis_OpenDevice(0,&openDeviceSettings);
#endif
    }

    if(outOfBandPrsent){
        st3128Settings.type = NEXUS_3128ChannelType_eOutOfBand;
        BDBG_WRN(("Waiting for Oob channel to initialize"));
        pConfig->frontend[i] = NEXUS_Frontend_Open3128(&st3128Settings);
        if (NULL == pConfig->frontend[i])
        {
            BDBG_ERR(("Unable to open onboard 3128 Oob channel %d", i));
        }

        NEXUS_Frontend_GetUserParameters(pConfig->frontend[i], &userParams);
        userParams.isMtsif = false;
        userParams.param1 =  NEXUS_InputBand_e9;
        userParams.pParam2 = NULL;
        NEXUS_Frontend_SetUserParameters(pConfig->frontend[i], &userParams);
    }
    return BERR_SUCCESS;
}

void NEXUS_Platform_UninitFrontend(void)
{
    NEXUS_PlatformConfiguration *pConfig = &g_NEXUS_platformHandles.config;
    unsigned i=0, j=0;
    NEXUS_FrontendDeviceHandle tempHandle, deviceHandles[NEXUS_MAX_FRONTENDS];
    bool handleFound = false;

#ifdef NEXUS_FRONTEND_REVERSE_RMAGNUM_SUPPORT
    if(hDocsisFrontendDevice)
    {
        NEXUS_FrontendDevice_Close(hDocsisFrontendDevice);
        hDocsisFrontendDevice = NULL;
    }
#endif

    BKNI_Memset(deviceHandles, 0, sizeof(deviceHandles));

    for(i=0; i<PLATFORM_MAX_TUNERS; i++){
        if(tunerHandle[i]) {
            NEXUS_Tuner_Close(tunerHandle[i]);
            tunerHandle[i] = NULL;
        }
    }

    for (i=0; i<NEXUS_MAX_FRONTENDS; i++)
    {
        handleFound = false;
        if (pConfig->frontend[i])
        {
            tempHandle = NEXUS_Frontend_GetDevice(pConfig->frontend[i]);
            for( j = 0; j<i; j++){
                if(tempHandle == deviceHandles[j])
                handleFound = true;
            }
            if(!handleFound)
                deviceHandles[j] = tempHandle;
            NEXUS_Frontend_Close(pConfig->frontend[i]);
            pConfig->frontend[i] = NULL;
        }
    }

    for (i=0; i<NEXUS_MAX_FRONTENDS; i++)
    {
        if (deviceHandles[i])
        {
            NEXUS_FrontendDevice_Close(deviceHandles[i]);
            deviceHandles[i] = NULL;
        }
    }

    return;
}
#else
NEXUS_Error NEXUS_Platform_InitFrontend(void)
{
    return BERR_SUCCESS;
}

void NEXUS_Platform_UninitFrontend(void)
{
}
#endif

BTRC_MODULE(ChnChange_TuneStreamer, ENABLE);

NEXUS_Error
NEXUS_Platform_GetStreamerInputBand(unsigned index, NEXUS_InputBand *pInputBand)
{
    BDBG_ASSERT(pInputBand);
    if (index > 0) {
        BDBG_ERR(("Only 1 streamer input available"));
        return BERR_TRACE(BERR_INVALID_PARAMETER);
    }
    BTRC_TRACE(ChnChange_TuneStreamer, START);
    *pInputBand = NEXUS_InputBand_e4;
    BTRC_TRACE(ChnChange_TuneStreamer, STOP);
    return NEXUS_SUCCESS;
}

NEXUS_FrontendHandle NEXUS_Platform_OpenFrontend(
    unsigned id /* platform assigned ID for this frontend. See NEXUS_FrontendUserParameters.id.
                   See nexus_platform_frontend.c for ID assignment and/or see
                   nexus_platform_features.h for possible platform-specific macros.
                */
    )
{
    NEXUS_Error errCode = BERR_TRACE(BERR_NOT_SUPPORTED);
    BSTD_UNUSED(errCode);
    BSTD_UNUSED(id);
    return NULL;
}

#endif

/***************************************************************************
*     (c)2004-2013 Broadcom Corporation
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
* API Description:
*   API name: Platform Frontend
*    Platform Frontend Setup
*
* Revision History:
*
* $brcm_Log: $
*
***************************************************************************/
#include "nexus_platform_module.h"
#include "nexus_types.h"
#if NEXUS_HAS_I2C && NEXUS_HAS_FRONTEND
#include "priv/nexus_core.h"
#include "nexus_i2c.h"
#include "bfpga.h"
#include "bfpga_name.h"
#include "nexus_frontend.h"
#include "nexus_platform_features.h"
#include "nexus_platform.h"
#include "nexus_platform_priv.h"
#include "nexus_base.h"
#include "bchp_sun_top_ctrl.h"
#include "nexus_frontend_7346.h"

#if NEXUS_FRONTEND_3461
#include "nexus_input_band.h"
#include "nexus_frontend_3461.h"
#endif

#if NEXUS_FRONTEND_4506
#include "nexus_frontend_4506.h"
#endif

#if NEXUS_HAS_SPI
#include "nexus_spi.h"
#endif

BDBG_MODULE(nexus_platform_frontend);

/* i2c channel assignments */
#define I2C_DEVICE_FPGA_CH 2
#if (BCHP_CHIP==7344) || (BCHP_CHIP==7358)
#define I2C_DEVICE_VOLTAGE_REG_CH 1
#else /* 7346 */
#define I2C_DEVICE_VOLTAGE_REG_CH 3
#endif

#define ISL9492_CH0_I2C_ADDR 0x08
#define ISL9492_CH1_I2C_ADDR 0x09
#define FPGA_CHIP_ADDR 0xE

#if NEXUS_PLATFORM_97346_HR44
    static NEXUS_GpioHandle gpioHandle = NULL;
#endif

#if NEXUS_PLATFORM_7218TC2RSFF

#if NEXUS_PLATFORM_97218_3461_USES_SPI
NEXUS_SpiHandle frontendSpi; /* Uses HIF SPI channel 0. */
#else
#define TUNER_BSC (3) /* tuner/demod use ISC 3 */
#endif

#define TUNER_INPUTBAND NEXUS_InputBand_e2

NEXUS_GpioHandle tunerGpio[NEXUS_MAX_FRONTENDS];

NEXUS_Error NEXUS_Platform_InitFrontend(void)
{
    NEXUS_PlatformConfiguration *pConfig = &g_NEXUS_platformHandles.config;
    NEXUS_3461Settings st3461Settings;
    NEXUS_FrontendUserParameters userParams;
    NEXUS_3461ConfigSettings configSettings;
#if NEXUS_PLATFORM_97218_3461_USES_SPI
    NEXUS_SpiSettings spiSettings;
#endif

    NEXUS_Frontend_GetDefault3461Settings(&st3461Settings);
#if NEXUS_PLATFORM_97218_3461_USES_SPI
    BDBG_WRN(("Waiting for 3461 Downstream frontend to initialize HIF SPI channel 0. NOTE: It is not UPG SPI."));

    NEXUS_Spi_GetDefaultSettings(&spiSettings);
    spiSettings.clockActiveLow = true;
    spiSettings.ebiChipSelect = 2;
#if NEXUS_PLATFORM_7218TC2RSFF2L
    frontendSpi = NEXUS_Spi_Open(1, &spiSettings);
#else
#error HIF SPI not supported in refsw. Must build patch.
    frontendSpi = NEXUS_Spi_Open(NEXUS_SPI_INDEX(Hif,0), &spiSettings);
#endif
    BDBG_ASSERT(NULL != frontendSpi);
    
    st3461Settings.spiDevice = frontendSpi;
    st3461Settings.spiAddr = 0x40; /* only valid option on spi interface */
#else

    BDBG_WRN(("Waiting for 3461 Downstream frontend(755x_EUSFF) to initialize I2C:%d", TUNER_BSC));

    if (!pConfig->i2c[TUNER_BSC]) {
            BDBG_ERR(("Frontend cannot be initialized without first initializing ISC."));
            return BERR_NOT_INITIALIZED;
    }
    st3461Settings.i2cDevice = pConfig->i2c[TUNER_BSC];
    st3461Settings.i2cAddr = 0x6c;
#endif

    st3461Settings.isrNumber = 9;
    st3461Settings.type = NEXUS_3461ChannelType_eDvbt; /*REDUNDANT for now as there is only one instance of any demod running. */
    st3461Settings.channelNumber = 0;                    /*REDUNDANT for now. */
    st3461Settings.loadAP = true;

    pConfig->frontend[0] = NEXUS_Frontend_Open3461(&st3461Settings);
    if (NULL == pConfig->frontend[0])
    {
        BDBG_ERR(("Unable to open onboard 3461 dvbt2 tuner/demodulator "));
    }

    NEXUS_Frontend_GetUserParameters(pConfig->frontend[0], &userParams);
    userParams.param1 = TUNER_INPUTBAND;
    userParams.pParam2 = NULL;
    NEXUS_Frontend_SetUserParameters(pConfig->frontend[0], &userParams);

    NEXUS_Frontend_GetDefault3461ConfigSettings(&configSettings);
#if (NEXUS_ENABLE_EXTERNAL_LNA == 1)
    configSettings.rfDaisyChain = NEXUS_3461RfDaisyChain_eExternalLna;
    configSettings.rfInput = NEXUS_3461TunerRfInput_eExternalLna;
#else
    configSettings.rfDaisyChain = NEXUS_3461RfDaisyChain_eInternalLna;
    configSettings.rfInput = NEXUS_3461TunerRfInput_eInternalLna;
#endif
    configSettings.enableRfLoopThrough = true;
    NEXUS_Frontend_3461_SetConfigSettings(pConfig->frontend[0], &configSettings);

    return NEXUS_SUCCESS;
}

void NEXUS_Platform_UninitFrontend(void)
{
    NEXUS_PlatformConfiguration *pConfig = &g_NEXUS_platformHandles.config;
    unsigned i;

    for (i=0; i<NEXUS_MAX_FRONTENDS; i++)
    {
        if (pConfig->frontend[i])
             NEXUS_Frontend_Close(pConfig->frontend[i]);
    }
#if NEXUS_PLATFORM_97218_3461_USES_SPI
    if(frontendSpi) {
        NEXUS_Spi_Close(frontendSpi);
    }
#endif
    return;
}


#else
NEXUS_Error NEXUS_Platform_InitFrontend(void)
{
#if BCHP_CHIP == 7346   
    uint8_t  data_c, data_d, data_e, regaddr=0;
#endif
    NEXUS_7346FrontendSettings settings;
    NEXUS_FrontendUserParameters userParams;
    unsigned i;
    uint8_t data;
    BCHP_Info info;
#if NEXUS_PLATFORM_97346_SV || NEXUS_PLATFORM_97346_HR44
    unsigned j;
    NEXUS_4506Settings settings4506;
#if NEXUS_PLATFORM_97346_HR44
    NEXUS_GpioSettings gpioSettings;
#endif
#endif
    NEXUS_PlatformConfiguration *pConfig = &g_NEXUS_platformHandles.config;
    
    BCHP_GetInfo(g_pCoreHandles->chp, &info);
    if (info.productId == 0x7418){
        return BERR_SUCCESS;
    }

    NEXUS_Frontend_GetDefault7346Settings(&settings);

    /* Setup LNA configurations per-board. */
#if (BCHP_CHIP == 7346)
#if NEXUS_PLATFORM_97346_SFF
    settings.lnaSettings.out0 = NEXUS_7346LnaInput_eIn1;
    settings.lnaSettings.out1 = NEXUS_7346LnaInput_eIn1;
    settings.lnaSettings.daisy = NEXUS_7346LnaInput_eNone;
#elif NEXUS_PLATFORM_97346_HR44
    settings.isInternalLna = true;
    settings.lnaSettings.out0 = NEXUS_7346LnaInput_eIn0;
    settings.lnaSettings.out1 = NEXUS_7346LnaInput_eIn0;
    settings.lnaSettings.daisy = NEXUS_7346LnaInput_eIn0;
    settings.external3445Lna.enabled = true;
    settings.external3445Lna.i2cChannelNumber = 0; /* SDS0 */
    settings.external3445Lna.lnaOutput = NEXUS_3445LnaOutput_eOut1;
    settings.external3445Lna.settings.daisy = NEXUS_3445LnaInput_eIn2Vga;
    settings.external3445Lna.settings.out1  = NEXUS_3445LnaInput_eIn2Vga;
    settings.external3445Lna.settings.out2  = NEXUS_3445LnaInput_eIn2Vga;
#else
    settings.lnaSettings.out0 = NEXUS_7346LnaInput_eIn0;
    settings.lnaSettings.out1 = NEXUS_7346LnaInput_eIn1;
    settings.lnaSettings.daisy = NEXUS_7346LnaInput_eIn0;
#endif  
    settings.isInternalLna = true;
#elif (BCHP_CHIP == 7344) /* 7344 SFF and SV board */
    settings.lnaSettings.out0 = NEXUS_7346LnaInput_eIn0;
    settings.lnaSettings.out1 = NEXUS_7346LnaInput_eNone;
    settings.lnaSettings.daisy = NEXUS_7346LnaInput_eNone;
    settings.isInternalLna = true;
#else
#if (NEXUS_ENABLE_EXTERNAL_LNA == 1)
    settings.lnaSettings.out0 = NEXUS_7346LnaInput_eNone;
    settings.lnaSettings.out1 = NEXUS_7346LnaInput_eNone;
    settings.lnaSettings.daisy = NEXUS_7346LnaInput_eNone;
    settings.isInternalLna = false;
    settings.external3445Lna.enabled = true;
#else
    settings.lnaSettings.out0 = NEXUS_7346LnaInput_eIn0;
    settings.lnaSettings.out1 = NEXUS_7346LnaInput_eNone;
    settings.lnaSettings.daisy = NEXUS_7346LnaInput_eNone;
    settings.isInternalLna = true;
#endif
#endif

    /* Open 734x Demodulator Channels */
    for ( i = 0; i < (NEXUS_7346_MAX_FRONTEND_CHANNELS-1); i++ )
    {
        BDBG_WRN(("734x Trying to open frontend channel %d", i));
        settings.channelNumber = i;
        
        pConfig->frontend[i] = NEXUS_Frontend_Open7346(&settings);
        if ( pConfig->frontend[i] )
        {
            NEXUS_Frontend_GetUserParameters(pConfig->frontend[i], &userParams);
            switch (i)
            {
#if (BCHP_CHIP==7346)
                case 0: userParams.param1 = NEXUS_InputBand_e6; break;
                case 1: userParams.param1 = NEXUS_InputBand_e7; break;
                default: BDBG_ERR(("unsupported channel!"));
#else /* 97344 */
                case 0: userParams.param1 = NEXUS_InputBand_e3; break;
                case 1: userParams.param1 = NEXUS_InputBand_e2; break;
                default: BDBG_ERR(("unsupported channel!"));
#endif
                }
            userParams.pParam2 = NULL;
            NEXUS_Frontend_SetUserParameters(pConfig->frontend[i], &userParams);
        }
        else
        {
            BDBG_ERR(("NEXUS_Frontend_Open7346 Failed!"));
        }
    }

#if NEXUS_PLATFORM_97346_SV  || NEXUS_PLATFORM_97346_HR44
	
#if NEXUS_PLATFORM_97346_HR44
       NEXUS_Gpio_GetDefaultSettings(NEXUS_GpioType_eStandard, &gpioSettings);
       gpioSettings.mode = NEXUS_GpioMode_eOutputPushPull;
       gpioSettings.value = NEXUS_GpioValue_eHigh;
       gpioSettings.interruptMode = NEXUS_GpioInterrupt_eDisabled;
       gpioSettings.interrupt.callback = NULL;
       gpioHandle = NEXUS_Gpio_Open(NEXUS_GpioType_eStandard, 49, &gpioSettings);
       BDBG_ASSERT(NULL != gpioHandle);
       NEXUS_Gpio_Close(gpioHandle);
       gpioHandle = NEXUS_Gpio_Open(NEXUS_GpioType_eStandard, 65, &gpioSettings);
       BDBG_ASSERT(NULL != gpioHandle);
      
       /* delay for reset extension */
       BKNI_Sleep(200);
#endif

    /* Open 4505 has only one Demodulator Channel */
#if NEXUS_PLATFORM_97346_HR44
    for ( j = 0; j < NEXUS_4506_MAX_FRONTEND_CHANNELS ; j++, i++ )
    {
        BDBG_WRN(("4506 Trying to open frontend channel %d", i));
        /* Open on-board 4506 */
        NEXUS_Frontend_GetDefault4506Settings(&settings4506);
        settings4506.i2cDevice = pConfig->i2c[2];   
        if (!settings4506.i2cDevice) {
            BDBG_ERR(("Unable to initialize I2C"));
            return BERR_TRACE(BERR_INVALID_PARAMETER);
        }

        settings4506.isrNumber = 17;
        settings4506.i2cAddr = 0x69;
		settings4506.is3445ExternalLna = false;
        settings4506.channelNumber = j;
        pConfig->frontend[i] = NEXUS_Frontend_Open4506(&settings4506);
        if ( pConfig->frontend[i] )
        {
            NEXUS_Frontend_GetUserParameters(pConfig->frontend[i], &userParams);
            switch (j)
            {
                case 0: userParams.param1 = NEXUS_InputBand_e0; break;
                case 1: userParams.param1 = NEXUS_InputBand_e1; break;
                default: BDBG_ERR(("unsupported channel!"));
                }
            userParams.pParam2 = NULL;
            NEXUS_Frontend_SetUserParameters(pConfig->frontend[i], &userParams);
        }
        else
        {
            BDBG_ERR(("NEXUS_Frontend_Open4506 Failed!"));
        }
    }
#endif

    /* Open 4505 has only one Demodulator Channel */
#if NEXUS_PLATFORM_97346_HR44
    for ( j = 0; j < NEXUS_4506_MAX_FRONTEND_CHANNELS ; j++, i++ )
#else
    for ( j = 0; j < NEXUS_4506_MAX_FRONTEND_CHANNELS -1 ; j++, i++ )
#endif
    {
        BDBG_WRN(("4506 Trying to open frontend channel %d", i));
        /* Open on-board 4506 */
        NEXUS_Frontend_GetDefault4506Settings(&settings4506);
#if NEXUS_PLATFORM_97346_HR44       
        settings4506.i2cDevice = pConfig->i2c[3];   
#else
        settings4506.i2cDevice = pConfig->i2c[1];   
#endif
        if (!settings4506.i2cDevice) {
            BDBG_ERR(("Unable to initialize I2C"));
            return BERR_TRACE(BERR_INVALID_PARAMETER);
         }

        settings4506.isrNumber = 11;
        settings4506.i2cAddr = 0x69;
        /* As of now, only for 4506 daughter card, this need to be set true. Because the 4506 on the daughter card directly controls the external 3445 LNA. */
        settings4506.is3445ExternalLna = false;
        settings4506.channelNumber = j;
        pConfig->frontend[i] = NEXUS_Frontend_Open4506(&settings4506);
        if ( pConfig->frontend[i] )
        {
            NEXUS_Frontend_GetUserParameters(pConfig->frontend[i], &userParams);
            switch (j)
            {
                case 0: userParams.param1 = NEXUS_InputBand_e5; break;
#if NEXUS_PLATFORM_97346_HR44               
                case 1: userParams.param1 = NEXUS_InputBand_e3; break;
#else
                case 1: userParams.param1 = NEXUS_InputBand_e6; break;
#endif
                default: BDBG_ERR(("unsupported channel!"));
                }
            userParams.pParam2 = NULL;
            NEXUS_Frontend_SetUserParameters(pConfig->frontend[i], &userParams);
        }
        else
        {
            BDBG_ERR(("NEXUS_Frontend_Open External 4506  Failed!"));
        }
    }
#endif
    /* Tone generated internally according to EXTMpin */
    data = 0x20;
    NEXUS_I2c_Write(g_NEXUS_platformHandles.config.i2c[I2C_DEVICE_VOLTAGE_REG_CH], ISL9492_CH0_I2C_ADDR, 0x00, (const uint8_t *)&data, 1);
    /* Dynamic current limit */
    data = 0x44;
    NEXUS_I2c_Write(g_NEXUS_platformHandles.config.i2c[I2C_DEVICE_VOLTAGE_REG_CH], ISL9492_CH0_I2C_ADDR, 0x00,(const uint8_t *)&data, 1);
    /* Internal linear regulator is turned on and boost circuit is on */
    data = 0x78;
    NEXUS_I2c_Write(g_NEXUS_platformHandles.config.i2c[I2C_DEVICE_VOLTAGE_REG_CH], ISL9492_CH0_I2C_ADDR, 0x00,(const uint8_t *)&data, 1);
#if BCHP_CHIP==7346
    data = 0x20;
    NEXUS_I2c_Write(g_NEXUS_platformHandles.config.i2c[I2C_DEVICE_VOLTAGE_REG_CH], ISL9492_CH1_I2C_ADDR, 0x00,(const uint8_t *) &data, 1);
    data = 0x44;
    NEXUS_I2c_Write(g_NEXUS_platformHandles.config.i2c[I2C_DEVICE_VOLTAGE_REG_CH], ISL9492_CH1_I2C_ADDR, 0x00, (const uint8_t *) &data, 1);
    data = 0x78;
    NEXUS_I2c_Write(g_NEXUS_platformHandles.config.i2c[I2C_DEVICE_VOLTAGE_REG_CH], ISL9492_CH1_I2C_ADDR, 0x00, (const uint8_t *) &data, 1);
#endif

/* SET THE FPGA for STREAMER by DEFAULT */
    /* 7346 Board only */
 #if BCHP_CHIP == 7346
    BDBG_MSG(("fpga i2c %d %p", I2C_DEVICE_FPGA_CH , g_NEXUS_platformHandles.config.i2c[I2C_DEVICE_FPGA_CH]));
    (void)NEXUS_I2c_Read(g_NEXUS_platformHandles.config.i2c[I2C_DEVICE_FPGA_CH], FPGA_CHIP_ADDR, 0xc, &data_c, 1);
    (void)NEXUS_I2c_Read(g_NEXUS_platformHandles.config.i2c[I2C_DEVICE_FPGA_CH], FPGA_CHIP_ADDR, 0xd, &data_d, 1);
    (void)NEXUS_I2c_Read(g_NEXUS_platformHandles.config.i2c[I2C_DEVICE_FPGA_CH], FPGA_CHIP_ADDR, 0xe, &data_e, 1);
    
    BDBG_MSG(("FPGA version:  0x%02x", data_e));

    if ((data_c != 0x46) || (data_d != 0x73)) BDBG_ERR(("Reading of Transport FPGA yields CHIPID=0x%02x%02x", data_d, data_c));

    data = 0x80;
    (void)NEXUS_I2c_Write(g_NEXUS_platformHandles.config.i2c[I2C_DEVICE_FPGA_CH], FPGA_CHIP_ADDR, 4, &data, 1);

    if (NEXUS_GetEnv("NEXUS_ASI")) {
        regaddr = 2; /* value maybe 0?*/
        data = 0x10; /* Use streamer 1 for ASI, pkt interface 2 */
    } else {
        regaddr = 2;
        data = 0x00; /* Use streamer 0 for LVDS, pkt interface 0 */
    }
    (void)NEXUS_I2c_Write(g_NEXUS_platformHandles.config.i2c[I2C_DEVICE_FPGA_CH], FPGA_CHIP_ADDR, regaddr, &data, 1);
#endif

    /* Install frontend extensions */
#if 0 /* Do not create extensions */
#if BCHP_CHIP == 7344
    NEXUS_Frontend_GetDefault97344ExtensionSettings(&extensionSettings);
    extensionSettings.primary = g_frontends[0];
    NEXUS_Frontend_Create97344Extension(&extensionSettings, &extensionHandles);
    g_NEXUS_platformHandles.config.frontend[0] = extensionHandles.primary;
#else
    NEXUS_Frontend_GetDefault97346ExtensionSettings(&extensionSettings);
    extensionSettings.boardRev = boardRev;
    extensionSettings.primary = g_frontends[0];
#if (NEXUS_MAX_FRONTENDS > 1)
    extensionSettings.secondary = g_frontends[1];
#endif
    extensionSettings.isl6423I2cDevice = g_NEXUS_platformHandles.config.i2c[I2C_DEVICE_VOLTAGE_REG_CH];
    extensionSettings.fpgaI2cDevice = g_NEXUS_platformHandles.config.i2c[I2C_DEVICE_FPGA_CH];
    NEXUS_Frontend_Create97346Extension(&extensionSettings, &extensionHandles);
    g_NEXUS_platformHandles.config.frontend[0] = extensionHandles.primary;
#if (NEXUS_MAX_FRONTENDS > 1)
    g_NEXUS_platformHandles.config.frontend[1] = extensionHandles.secondary;
#endif
#endif
#endif /* if 0 */

    return BERR_SUCCESS;
}

void NEXUS_Platform_UninitFrontend(void)
{
	NEXUS_PlatformConfiguration *pConfig = &g_NEXUS_platformHandles.config;
	unsigned i=0, j=0;
	NEXUS_FrontendDeviceHandle tempHandle, deviceHandles[NEXUS_MAX_FRONTENDS];
	bool handleFound = false;

	BKNI_Memset(deviceHandles, 0, sizeof(deviceHandles));

	for (i=0; i<NEXUS_MAX_FRONTENDS; i++)
	{
		handleFound = false;
		/* Close extensions first */
		if (pConfig->frontend[i])
		{
			tempHandle = NEXUS_Frontend_GetDevice(pConfig->frontend[i]);
			if(tempHandle != NULL){
				for( j = 0; j<i; j++){
					if(tempHandle == deviceHandles[j])
					handleFound = true;
				}
				if(!handleFound)
					deviceHandles[j] = tempHandle;
		   }
			NEXUS_Frontend_Close(pConfig->frontend[i]);
			pConfig->frontend[i] = NULL;
		}
#if 0 /* Once SWM is in*/
		/* Close underlying demod */
		if ( pConfig->frontend[i] )
		{
			NEXUS_Frontend_Close(pConfig->frontend[i]);
		}
#endif
	}
		
	for (i=0; i<NEXUS_MAX_FRONTENDS; i++)
	{
		if (deviceHandles[i])
		{
			NEXUS_FrontendDevice_Close(deviceHandles[i]);
			deviceHandles[i] = NULL;
		}
	}

#if NEXUS_PLATFORM_97346_HR44   
    if(gpioHandle)
    {
        NEXUS_Gpio_Close(gpioHandle);
        gpioHandle = NULL;
    }
#endif  
    return;
}

#endif

BTRC_MODULE(ChnChange_TuneStreamer, ENABLE);

NEXUS_Error
NEXUS_Platform_GetStreamerInputBand(unsigned index, NEXUS_InputBand *pInputBand)
{

    BDBG_ASSERT(pInputBand);
    BTRC_TRACE(ChnChange_TuneStreamer, START);

#if BCHP_CHIP==7344

	switch (index)
	{
		case 0:
    		*pInputBand = NEXUS_InputBand_e0;
			break;
		case 1:
    		*pInputBand = NEXUS_InputBand_e1;
			break;
		default:
			BDBG_ERR(("index %d not supported", index));
			return NEXUS_NOT_SUPPORTED;	
	}

#else 
    BSTD_UNUSED(index);    
    *pInputBand = NEXUS_InputBand_e2;
	
#endif

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

#else
#endif /* NEXUS_HAS_I2C && NEXUS_HAS_FRONTEND */




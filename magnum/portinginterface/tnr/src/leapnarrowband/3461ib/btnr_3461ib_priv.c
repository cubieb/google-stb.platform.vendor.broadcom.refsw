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
 * Module Description:
 *
 * Revision History:  $
 *
 * $brcm_Log: $
 * 
 ***************************************************************************/
#include "bstd.h"
#include "bkni.h"
#include "btnr.h"
#include "btnr_priv.h"
#include "btnr_3461ib_priv.h"

BDBG_MODULE(btnr_3461_priv);

#define DEV_MAGIC_ID                    ((BERR_TNR_ID<<16) | 0xFACE)

#define CHK_RETCODE( rc, func )         \
do {                                        \
    if( (rc = BERR_TRACE(func)) != BERR_SUCCESS ) \
    {                                       \
        goto done;                          \
    }                                       \
} while(0)

/*******************************************************************************
*
*   Private Module Data
*
*******************************************************************************/
BERR_Code BTNR_3461_Close(
    BTNR_Handle hDev                    /* [in] Device handle */
    )
{
    BERR_Code retCode = BERR_SUCCESS;
    BTNR_3461_Handle btnr_3461_handle;
    BTNR_P_3461_Settings btnr_3461_settings;


    BDBG_ENTER(BTNR_3461_Close);
    BDBG_ASSERT( hDev );
    BDBG_ASSERT( hDev->magicId == DEV_MAGIC_ID );

    /* verify the handle is good before using it */
    btnr_3461_handle = (BTNR_3461_Handle) hDev->hDevImpl;
    btnr_3461_settings = btnr_3461_handle ->settings;

    hDev->magicId = 0x00;       /* clear it to catch inproper use */
    BKNI_Free( (void *) hDev->hDevImpl );
    BKNI_Free( (void *) hDev );

    BDBG_LEAVE(BTNR_3461_Close);
    return retCode;
}

BERR_Code BTNR_3461_SetRfFreq(
    BTNR_3461_Handle hDev,            /* [in] Device handle */
    uint32_t rfFreq,                    /* [in] Requested tuner freq., in Hertz */
    BTNR_TunerMode tunerMode            /* [in] Requested tuner mode */
    )
{
    BERR_Code retCode = BERR_SUCCESS;
    BTNR_P_3461_Settings *pTnrImplData;   
       
    uint8_t hab[17] = HAB_MSG_HDR(BTNR_ACQUIRE_PARAMS_WRITE, 0xC, BTNR_CORE_TYPE, BTNR_CORE_ID);
    uint8_t bandwidth = 0;
    BSTD_UNUSED(tunerMode);
    
    BDBG_ENTER(BTNR_3461_SetRfFreq);
    BDBG_ASSERT( hDev );
    BDBG_ASSERT( hDev->magicId == DEV_MAGIC_ID );
    pTnrImplData = &hDev->settings;

    hab[4] = pTnrImplData->std + 1;

    switch (pTnrImplData->bandwidth)
    {
        case 8000000:
            bandwidth = 1;
            break;
        case 7000000:
            bandwidth = 2;
            break;
        case 6000000:
            bandwidth = 3;
            break;
        case 5000000:
            bandwidth = 4;
            break;
        case 1700000:
            bandwidth = 5;
            break;            
        default:
            BDBG_ERR(("Invalid bandwidth, valid bandwidths are 8Mhz, 7Mhz, 6Mhz, 5Mhz and 1.7Mhz"));
    }
    
    hab[4] |= (bandwidth << 3);    
    hab[4] |= (BTNR_TunerApplication_eTerrestrial + 1) << 6;  
    hab[5] = 0x80;    
    hab[12] = (rfFreq >> 24);
    hab[13] = (rfFreq >> 16);
    hab[14] = (rfFreq >> 8);
    hab[15] = rfFreq;
    CHK_RETCODE(retCode, BHAB_SendHabCommand(hDev->hHab, hab, 17, hab, 0, false, true, 17));

done:
    BDBG_LEAVE(BTNR_3461_SetRfFreq);
    return retCode;
}
            
BERR_Code BTNR_3461_GetRfFreq(
    BTNR_3461_Handle hDev,            /* [in] Device handle */
    uint32_t *rfFreq,                   /* [output] Returns tuner freq., in Hertz */
    BTNR_TunerMode *tunerMode           /* [output] Returns tuner mode */
    )
{
    BERR_Code retCode = BERR_SUCCESS;
    BTNR_P_3461_Settings *pTnrImplData;


    BDBG_ENTER(BTNR_3461_GetRfFreq);
    BDBG_ASSERT( hDev );
    BDBG_ASSERT( hDev->magicId == DEV_MAGIC_ID );

    pTnrImplData = &hDev->settings;

    *rfFreq = pTnrImplData->rfFreq;
    *tunerMode = pTnrImplData->tunerMode;

    BDBG_LEAVE(BTNR_3461_GetRfFreq);
    return retCode;
}

BERR_Code BTNR_P_3461_GetAgcRegVal(
    BTNR_3461_Handle hDev,            /* [in] Device handle */
    uint32_t regOffset,                 /* [in] AGC register offset */
    uint32_t *agcVal                    /* [out] output value */
    )
{
    BERR_Code retCode = BERR_SUCCESS;
    BSTD_UNUSED(hDev);
    BSTD_UNUSED(regOffset);
    BSTD_UNUSED(agcVal);

    return retCode;
}

BERR_Code BTNR_3461_SetAgcRegVal(
    BTNR_3461_Handle hDev,            /* [in] Device handle */
    uint32_t regOffset,                 /* [in] AGC register offset */
    uint32_t *agcVal                    /* [in] input value */
    )
{
    BERR_Code retCode = BERR_SUCCESS;
    BSTD_UNUSED(hDev);
    BSTD_UNUSED(regOffset);
    BSTD_UNUSED(agcVal);
    
    return retCode;
}

BERR_Code BTNR_3461_GetInfo(
    BTNR_3461_Handle hDev,            /* [in] Device handle */
    BTNR_TunerInfo *tnrInfo             /* [out] Tuner information */
    )
{   
    BTNR_P_3461_Settings *pTnrImplData;
    BERR_Code retCode = BERR_SUCCESS;

    BDBG_ENTER(BTNR_3461_GetInfo);
    BDBG_ASSERT( hDev );
    BDBG_ASSERT( hDev->magicId == DEV_MAGIC_ID );

    pTnrImplData = &hDev->settings;
    tnrInfo->tunerMaker = BRCM_TUNER_MAKER_ID;
    tnrInfo->tunerId = 0x3461;
    tnrInfo->tunerMajorVer = pTnrImplData->iRevLetter;
    tnrInfo->tunerMinorVer = pTnrImplData->iRevNumber;

    BDBG_LEAVE(BTNR_3461_GetInfo);
    return retCode;
}

BERR_Code BTNR_3461_GetPowerSaver(
    BTNR_3461_Handle hDev,                    /* [in] Device handle */
    BTNR_PowerSaverSettings *pwrSettings        /* [in] Power saver settings. */
    )
{   
    BTNR_P_3461_Settings *pTnrImplData;
    BERR_Code retCode = BERR_SUCCESS;
    uint8_t hab[5] = HAB_MSG_HDR(BTNR_POWER_CTRL_READ, 0, BTNR_CORE_TYPE, BTNR_CORE_ID);
    
    BDBG_ENTER(BTNR_3461_GetPowerSaver);
    BDBG_ASSERT( hDev );
    BDBG_ASSERT( hDev->magicId == DEV_MAGIC_ID );  
    
    pTnrImplData = &hDev->settings;
  
    CHK_RETCODE(retCode, BHAB_SendHabCommand(hDev->hHab, hab, 5, hab, 9, false, true, 9 )); 
    
    if(hab[4] == 0xFF)
        pwrSettings->enable = 0;
    else
        pwrSettings->enable = 1;

done:    
    return retCode;
}

BERR_Code BTNR_3461_SetPowerSaver(
    BTNR_3461_Handle hDev,                    /* [in] Device handle */
    BTNR_PowerSaverSettings *pwrSettings /* [in] Power saver settings. */
    )
{   
    BERR_Code retCode = BERR_SUCCESS;
    uint8_t hab[5] = HAB_MSG_HDR(BTNR_POWER_CTRL_ON, 0x0, BTNR_CORE_TYPE, BTNR_CORE_ID);
    uint8_t hab1[5] = HAB_MSG_HDR(BTNR_POWER_CTRL_OFF, 0x0, BTNR_CORE_TYPE, BTNR_CORE_ID);

    BDBG_ENTER(BTNR_3461_SetPowerSaver);
    BDBG_ASSERT( hDev );
    BDBG_ASSERT( hDev->magicId == DEV_MAGIC_ID );    
 
    if(pwrSettings->enable) 
        CHK_RETCODE(retCode, BHAB_SendHabCommand(hDev->hHab, hab1, 5, hab1, 0, false, true, 5 ));
    else        
        CHK_RETCODE(retCode, BHAB_SendHabCommand(hDev->hHab, hab, 5, hab, 0, false, true, 5 ));       

done:    
    BDBG_LEAVE(BTNR_3461_SetPowerSaver);
    return retCode;
}

BERR_Code BTNR_3461_GetSettings(
    BTNR_3461_Handle hDev,    /* [in] Device handle */
    BTNR_Settings *settings     /* [out] TNR settings. */
    )
{   
    BTNR_P_3461_Settings *pTnrImplData;
    BERR_Code retCode = BERR_SUCCESS;

    BDBG_ENTER(BTNR_3461_GetSettings);
    BDBG_ASSERT( hDev );
    BDBG_ASSERT( hDev->magicId == DEV_MAGIC_ID );

    pTnrImplData = &hDev->settings;
    settings->std = pTnrImplData->std;   
    settings->bandwidth = pTnrImplData->bandwidth;

    BDBG_LEAVE(BTNR_3461_GetSettings);
    return retCode;
}

BERR_Code BTNR_3461_SetSettings(
    BTNR_3461_Handle hDev,    /* [in] Device handle */
    BTNR_Settings *settings     /* [in] TNR settings. */
    )

{  
    BTNR_P_3461_Settings *pTnrImplData;
    BERR_Code retCode = BERR_SUCCESS;

    BDBG_ENTER(BTNR_3461_SetSettings);
    BDBG_ASSERT( hDev );
    BDBG_ASSERT( hDev->magicId == DEV_MAGIC_ID );

    pTnrImplData = &hDev->settings;
    pTnrImplData->std = settings->std;   
    pTnrImplData->bandwidth = settings->bandwidth;

    BDBG_LEAVE(BTNR_3461_SetSettings);
    return retCode;
}

BERR_Code BTNR_3461_GetVersionInfo(
    BTNR_3461_Handle hDev,          /* [in] Device handle */
    BFEC_VersionInfo *pVersionInfo  /* [out] Returns version Info */
    )
{
    BERR_Code retCode = BERR_SUCCESS;
    uint8_t buf[29] = HAB_MSG_HDR(BTNR_SYS_VERSION, 0, BTNR_CORE_TYPE, BTNR_CORE_ID);

    BDBG_ENTER(BTNR_3461_GetVersionInfo);
    BDBG_ASSERT( hDev );
    BDBG_ASSERT( hDev->magicId == DEV_MAGIC_ID );

    CHK_RETCODE(retCode, BHAB_SendHabCommand(hDev->hHab, buf, 5, buf, 29, false, true, 29)); 
    pVersionInfo->majorVersion = (buf[4] << 8) | buf[5];
    pVersionInfo->minorVersion = (buf[6] << 8) | buf[7];
    pVersionInfo->buildType = (buf[8] << 8) | buf[9];
    pVersionInfo->buildId = (buf[10] << 8) | buf[11];
    
done:    
    BDBG_LEAVE(BTNR_3461_GetVersionInfo);
    return( retCode );
}

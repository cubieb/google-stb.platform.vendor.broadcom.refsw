/***************************************************************************
 * (c) 2002-2015 Broadcom Corporation
 *
 * This program is the proprietary software of Broadcom Corporation and/or its
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
 *
 *****************************************************************************/

#ifndef TUNER_VSB_H__
#define TUNER_VSB_H__

#include "atlas_cfg.h"
#include "atlas_os.h"
#include "resource.h"
#include "band.h"
#include "tuner.h"
#ifdef MPOD_SUPPORT
#include "tspsimgr.h"
#else
#include "tspsimgr2.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

class CTunerVsbScanData : public CTunerScanData
{
public:
    CTunerVsbScanData(
            bool     appendToChannelList = false,
            uint16_t majorStartNum = 1
            ) :
        CTunerScanData(eBoardResource_frontendVsb, appendToChannelList, majorStartNum),
        _bandwidth(6000000),
        _stepFreq(-1),
        _mode(-1) {}

    /* assignment operator overload */
    CTunerVsbScanData & operator =(const CTunerVsbScanData & rhs)
    {
        /* call base class '=' operator method */
        CTunerScanData::operator=(rhs);

        _bandwidth = rhs._bandwidth;
        _stepFreq  = rhs._stepFreq;
        _mode      = rhs._mode;

        return(*this);
    }

    void dump(void);

public:
    int _bandwidth; /* in Hz */

    /* optional parameters (-1 if unspecified) */
    int _stepFreq;
    int _mode;
};

class CTunerVsb : public CTuner
{
public:
    CTunerVsb(
            const char *     name,
            const uint16_t   number,
            CConfiguration * pCfg
            );

    virtual void saveScanData(CTunerScanData * pScanData);
    virtual void doScan(void);
    virtual eRet open(CWidgetEngine * pWidgetEngine);
    virtual void close(void);
    virtual void handleLockCallback(void);

    eRet                     tune(NEXUS_FrontendVsbSettings settings);
    void                     unTune(bool bFullUnTune = false);
    void                     getProperties(MStringHash * pProperties, bool bClear);
    NEXUS_FrontendLockStatus isLocked(void);

protected:
    CTunerVsbScanData _scanData;
};

#ifdef __cplusplus
}
#endif

#endif /* TUNER_VSB_H__ */
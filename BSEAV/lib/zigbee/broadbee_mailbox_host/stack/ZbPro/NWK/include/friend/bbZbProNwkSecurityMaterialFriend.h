/******************************************************************************
* (c) 2014 Broadcom Corporation
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
******************************************************************************/
/*****************************************************************************
*
* FILENAME: $Workfile: $
*
* DESCRIPTION:
*   NWK-NIB(security material) API friend interface.
*
* $Revision: $
* $Date: $
*
*****************************************************************************************/
#ifndef _ZBPRO_NWK_SECURITY_MATERIAL_STORAGE_FRIEND_H
#define _ZBPRO_NWK_SECURITY_MATERIAL_STORAGE_FRIEND_H


/************************* INCLUDES *****************************************************/
#include "bbZbProSsp.h"
#include "bbZbProNwkSapTypesIb.h"

/************************* PROTOTYPES ***************************************************/
/************************************************************************************//**
    \brief Returns NWK Key with specified sequence number.
    \param[in] keySeqNumber - sequence number of new active key.
    \return pointer to the key if operation was successful, NULL otherwise.
****************************************************************************************/
const ZbProSspKey_t *zbProNwkNibApiGetKey(const ZbProSspNwkKeySeqNum_t keySeqNumber);

/************************************************************************************//**
    \brief Sets up the specified NWK Key
    \param[in] keySeqNumber - sequence number of new active key.
    \param[in] ptrKey - pointer to the key.
    \return true if operation was successful, false otherwise.
****************************************************************************************/
bool zbProNwkNibApiSetKey(const ZbProSspNwkKeySeqNum_t keySeqNumber, const ZbProSspKey_t *key);

/************************************************************************************//**
    \brief Gets and increments the specified outgoing frame counter
    \param[in] keySeqNumber - sequence number of new active key.
    \return valid frame counter value (begins from 0) if operation was successful,
            ZBPRO_SSP_INVALID_FRAME_COUNTER otherwise.
****************************************************************************************/
ZbProSspFrameCnt_t zbProNwkNibApiGetTxFrameCounter(const ZbProSspNwkKeySeqNum_t keySeqNumber);

/************************************************************************************//**
    \brief Gets the specified Incoming frame counter.
    \param[in] keySeqNumber - sequence number of new active key.
    \param[in] extSrcAddr - extended address of device of interest.
    \return valid incoming frame counter value if operation was successful,
            ZBPRO_SSP_INVALID_FRAME_COUNTER otherwise.
****************************************************************************************/
ZbProSspFrameCnt_t zbProNwkNibApiGetRxFrameCounter(const ZbProSspNwkKeySeqNum_t keySeqNumber,
        const ZBPRO_NWK_ExtAddr_t *const extSrcAddr);

/************************************************************************************//**
    \brief Updates the specified Incoming frame counter.
    \param[in] keySeqNumber - sequence number of new active key.
    \param[in] extSrcAddr - extended address of device of interest.
    \param[in] frameCounter - new value of incoming counter.
    \return true if operation was successful, false otherwise.
****************************************************************************************/
bool zbProNwkNibApiSetRxFrameCounter(const ZbProSspNwkKeySeqNum_t keySeqNumber,
        const ZBPRO_NWK_ExtAddr_t *const extSrcAddr, const ZbProSspFrameCnt_t newFrameCounterVal);

/************************************************************************************//**
    \brief Validate an active key.
    \return True if valid and false otherwise.
****************************************************************************************/
bool zbProNwkNibApiIsActiveKeyValid(void);

#endif /* _ZBPRO_NWK_SECURITY_MATERIAL_STORAGE_FRIEND_H */
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
* FILENAME: $Workfile: trunk/stack/ZbPro/NWK/include/bbZbProNwkSapTypesDiscovery.h $
*
* DESCRIPTION:
*   Network Layer Management Entity Network Discovery primitive declarations
*
* $Revision: 1909 $
* $Date: 2014-03-25 22:27:13Z $
*
****************************************************************************************/
#ifndef _ZBPRO_NWK_SAP_DISCOVERY_H
#define _ZBPRO_NWK_SAP_DISCOVERY_H

/************************* INCLUDES ****************************************************/
#include "bbSysTypes.h"
#include "bbSysUtils.h"
#include "bbZbProNwkCommon.h"

/************************* TYPES *******************************************************/
/**//**
 * \brief Discovery primitive service field descriptor.
 */
typedef struct _ZbProNwkDiscoveryServiceField_t
{
    SYS_QueueElement_t  queueElement;
    bool (*beaconFilter)(const void*const);
    MAC_ScanType_t      scanType;
} ZbProNwkDiscoveryServiceField_t;

/**//**
 * \brief NLME-NETWORK-DISCOVERY request primitive structure, see
 * ZigBee Specification r20, 3.2.2.1
 */
typedef struct _ZbProNwkDiscoveryReqParams_t
{
    BitField32_t    scanChannels;
    uint8_t         scanDuration;
} ZbProNwkDiscoveryReqParams_t;

/**//**
 * \brief NetworkDescriptor parameter structure of the NLME-NETWORK-DISCOVERY
 * confirm primitive structure, see ZigBee Specification r20, 3.2.2.2
 */
typedef struct _ZBPRO_NWK_NetworkDescriptor_t
{
    ZBPRO_NWK_ExtPanId_t    extendedPANId;
    ZBPRO_NWK_Channel_t     logicalChannel;
    uint8_t     stackProfile;
    uint8_t     zigBeeVersion;
    uint8_t     beaconOrder;
    uint8_t     superframeOrder;
    Bool8_t     permitJoining;
    Bool8_t     routerCapacity;
    Bool8_t     endDeviceCapacity;
} ZBPRO_NWK_NetworkDescriptor_t;

/**//**
 * \brief NLME-NETWORK-DISCOVERY confirm primitive structure, see
 * ZigBee Specification r20, 3.2.2.2
 */
typedef struct _ZBPRO_NWK_NetworkDiscoveryConfParams_t
{
    ZBPRO_NWK_Status_t              status;
    uint8_t                         networkCount;
    SYS_DataPointer_t               payload; /* network descriptors  list */
} ZBPRO_NWK_NetworkDiscoveryConfParams_t;

/**//**
 * \brief NLME-NETWORK-DISCOVERY descriptor prototype.
 */
typedef struct _ZBPRO_NWK_NetworkDiscoveryReqDescr_t ZBPRO_NWK_NetworkDiscoveryReqDescr_t;

/**//**
 * \brief NLME-NETWORK-DISCOVERY confirm primitive callback function type
 */
typedef void (*ZBPRO_NWK_NetworkDiscoveryCallback_t)(ZBPRO_NWK_NetworkDiscoveryReqDescr_t *const reqDescr,
        ZBPRO_NWK_NetworkDiscoveryConfParams_t *const confParams);

/**//**
 * \brief NLME-NETWORK-DISCOVERY request descriptor type, see
 * ZigBee Specification r20, 3.2.2.1
 */
struct _ZBPRO_NWK_NetworkDiscoveryReqDescr_t
{
    ZbProNwkDiscoveryServiceField_t         service;
    ZbProNwkDiscoveryReqParams_t            params;
    ZBPRO_NWK_NetworkDiscoveryCallback_t    callback;
};

/**//**
 * \brief NLME-ED-SCAN.confirm parameters structure, see ZigBee Specification r20, 3.2.2.10.
 */
typedef struct _ZBPRO_NWK_EDScanConfParams_t
{
    /* Status of execution. */
    ZBPRO_NWK_Status_t status;
    /* Energy detect list. */
    SYS_DataPointer_t payload;
} ZBPRO_NWK_EDScanConfParams_t;

/**//**
 * \brief NLME-ED-SCAN.request descriptor data type declaration.
 */
typedef struct _ZBPRO_NWK_EDScanReqDescr_t  ZBPRO_NWK_EDScanReqDescr_t;

/**//**
 * \brief NLME-ED-SCAN.confirm primitive callback function type.
 */
typedef void (*ZBPRO_NWK_EDScanConfCallback_t)(ZBPRO_NWK_EDScanReqDescr_t *const reqDescr,
        ZBPRO_NWK_EDScanConfParams_t *const conf);

/**//**
 * \brief NLME-ED-SCAN.request primitive structure, see ZigBee Specification r20, 3.2.2.9.
 */
struct _ZBPRO_NWK_EDScanReqDescr_t
{
    ZbProNwkDiscoveryServiceField_t service;
    ZbProNwkDiscoveryReqParams_t    params;
    ZBPRO_NWK_EDScanConfCallback_t  callback;
};

/************************* PROTOTYPES **************************************************/
/**//**
 * \brief NLME-NETWORK-DISCOVERY request primitive function
 */
void ZBPRO_NWK_NetworkDiscoveryReq(ZBPRO_NWK_NetworkDiscoveryReqDescr_t *req);

/**//**
 * \brief NLME-ED-SCAN request primitive function
 */
void ZBPRO_NWK_EDScanReq(ZBPRO_NWK_EDScanReqDescr_t *req);

#endif /* _ZBPRO_NWK_SAP_DISCOVERY_H */
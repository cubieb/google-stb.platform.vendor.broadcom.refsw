//****************************************************************************
//
// Copyright (c) 2006-2012 Broadcom Corporation
//
// This program is the proprietary software of Broadcom Corporation and/or
// its licensors, and may only be used, duplicated, modified or distributed
// pursuant to the terms and conditions of a separate, written license
// agreement executed between you and Broadcom (an "Authorized License").
// Except as set forth in an Authorized License, Broadcom grants no license
// (express or implied), right to use, or waiver of any kind with respect to
// the Software, and Broadcom expressly reserves all rights in and to the
// Software and all intellectual property rights therein.  IF YOU HAVE NO
// AUTHORIZED LICENSE, THEN YOU HAVE NO RIGHT TO USE THIS SOFTWARE IN ANY WAY,
// AND SHOULD IMMEDIATELY NOTIFY BROADCOM AND DISCONTINUE ALL USE OF THE
// SOFTWARE.  
//
// Except as expressly set forth in the Authorized License,
//
// 1.     This program, including its structure, sequence and organization,
// constitutes the valuable trade secrets of Broadcom, and you shall use all
// reasonable efforts to protect the confidentiality thereof, and to use this
// information only in connection with your use of Broadcom integrated circuit
// products.
//
// 2.     TO THE MAXIMUM EXTENT PERMITTED BY LAW, THE SOFTWARE IS PROVIDED
// "AS IS" AND WITH ALL FAULTS AND BROADCOM MAKES NO PROMISES, REPRESENTATIONS
// OR WARRANTIES, EITHER EXPRESS, IMPLIED, STATUTORY, OR OTHERWISE, WITH
// RESPECT TO THE SOFTWARE.  BROADCOM SPECIFICALLY DISCLAIMS ANY AND ALL
// IMPLIED WARRANTIES OF TITLE, MERCHANTABILITY, NONINFRINGEMENT, FITNESS FOR
// A PARTICULAR PURPOSE, LACK OF VIRUSES, ACCURACY OR COMPLETENESS, QUIET
// ENJOYMENT, QUIET POSSESSION OR CORRESPONDENCE TO DESCRIPTION. YOU ASSUME
// THE ENTIRE RISK ARISING OUT OF USE OR PERFORMANCE OF THE SOFTWARE.
//
// 3.     TO THE MAXIMUM EXTENT PERMITTED BY LAW, IN NO EVENT SHALL BROADCOM
// OR ITS LICENSORS BE LIABLE FOR (i) CONSEQUENTIAL, INCIDENTAL, SPECIAL,
// INDIRECT, OR EXEMPLARY DAMAGES WHATSOEVER ARISING OUT OF OR IN ANY WAY
// RELATING TO YOUR USE OF OR INABILITY TO USE THE SOFTWARE EVEN IF BROADCOM
// HAS BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES; OR (ii) ANY AMOUNT IN
// EXCESS OF THE AMOUNT ACTUALLY PAID FOR THE SOFTWARE ITSELF OR U.S. $1,
// WHICHEVER IS GREATER. THESE LIMITATIONS SHALL APPLY NOTWITHSTANDING ANY
// FAILURE OF ESSENTIAL PURPOSE OF ANY LIMITED REMEDY.
//
//****************************************************************************
//
//  Filename:       SebCommandTable.h
//  Author:         Pinar Taskiran-Cyr
//  Creation Date:  July 22, 2011
//
//****************************************************************************
//  Description:
//      Sub-command table for testing of SEB API on eCM side.
//
//****************************************************************************

#ifndef SEB_COMMANDTABLE_H
#define SEB_COMMANDTABLE_H

//********************** Include Files ***************************************

// My base class.
#include "CommandTable.h"
#include "seb_api.h"
//********************** Global Types ****************************************

//********************** Global Constants ************************************

//********************** Global Variables ************************************

//********************** Forward Declarations ********************************
class BcmEcmSebServerThread;
class BcmIpAddress;
class BcmMacAddress;
//********************** Class Declaration ***********************************


class SebBfcCommandTable : public BcmCommandTable
{
public:

    // Default Constructor.  Creates the command table, adds all of the
    // commands to it and sets the command handler function.
    //
    // Parameters:  None.
    //
    // Returns:  N/A
    //
    SebBfcCommandTable(void);

    // Destructor.  Frees up any memory/objects allocated, cleans up internal
    // state.
    //
    // Parameters:  N/A
    //
    // Returns:  N/A
    //
    virtual ~SebBfcCommandTable();	

	static void SebTestJoinMulticastSession(uint32 multicastIpAddress);
	static void MapMcastIpAddressToMacAddress(BcmIpAddress &mcastIpaddress, BcmMacAddress *pMcastMac );
	static bool ClientSebRxTunnelDataHandler(void *data, int dataLen );
	static void ClientSebStatusDataHandler( SebEcmEventNotification eventCode, void *data, int dataLen );

	friend class BcmDavicApi;

private:

    // This is the entrypoint that is called whenever one of my commands is
    // entered.
    //
    // Parameters:
    //      pInstanceValue - the instance value to which the command should be
    //                       applied.  Instances must be registered with the
    //                       command table in order for them to receive the
    //                       command.
    //      command - the command (with parameters) that was entered by the user.
    //
    // Returns:  Nothing.
    //
    static void CommandHandler(void *pInstanceValue, const BcmCommand &command);

private:

    // Copy Constructor.  Not supported.
    //
    // Parameters:
    //      otherInstance - reference to the object to copy.
    //
    // Returns:  N/A
    //
    SebBfcCommandTable(const SebBfcCommandTable &otherInstance);

    // Assignment operator.  Not supported.
    //
    // Parameters:
    //      otherInstance - reference to the object to copy.
    //
    // Returns:
    //      A reference to "this" so that operator = can be chained.
    //
    SebBfcCommandTable & operator = (const SebBfcCommandTable &otherInstance);

};


//********************** Inline Method Implementations ***********************


#endif



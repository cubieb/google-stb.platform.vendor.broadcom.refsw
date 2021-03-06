/***************************************************************************
 *     Copyright (c) 2016, Broadcom Corporation
 *     All Rights Reserved
 *     Confidential Property of Broadcom Corporation
 *
 *  THIS SOFTWARE MAY ONLY BE USED SUBJECT TO AN EXECUTED SOFTWARE LICENSE
 *  AGREEMENT  BETWEEN THE USER AND BROADCOM.  YOU HAVE NO RIGHT TO USE OR
 *  EXPLOIT THIS MATERIAL EXCEPT SUBJECT TO THE TERMS OF SUCH AN AGREEMENT.
 *
 ***************************************************************/
#ifndef BTEE_INSTANCE_H__
#define BTEE_INSTANCE_H__

/*================== Module Overview =====================================

This defines the interface to create an instance of the BTEE module.  This
allows upper-layer code to link a trusted execution environment library or
3rd-party module into magnum indirectly and avoid any external dependencies.

========================================================================*/

#include "btee.h"

/***************************************************************************
Summary:
    Instance Creation Settings
***************************************************************************/
typedef struct BTEE_InstanceCreateSettings
{
    void *pInstanceData;     /* Private data passed to client create routine */
    BERR_Code (*ClientCreate)(void *pInstanceData, const char *pName ,const BTEE_ClientCreateSettings *pSettings, void **pClientPrivate);
    void (*ClientDestroy)(void *pClientPrivate);
    BERR_Code (*ClientReceiveMessage)(void *pClientPrivate, void **pConnection, void *pMessage, size_t maxLength, size_t *pLength, int timeoutMsec);
    BERR_Code (*ClientAlloc)(void *pClientPrivate, size_t size, void **pMemory);
    void (*ClientFree)(void *pClientPrivate, void *pMemory);
    BERR_Code (*ClientSecureAlloc)(void *pClientPrivate, size_t size, uint32_t *pAddress);
    void (*ClientSecureFree)(void *pClientPrivate, uint32_t address);
    BERR_Code (*ClientAddrToOffset)(void *pClientPrivate, void *pMemory, uint32_t *pOffset);
    BERR_Code (*ClientOffsetToAddr)(void *pClientPrivate, uint32_t offset, void **pMemory);
    BERR_Code (*ClientContextSwitch)(void *pClientPrivate);
    BERR_Code (*FileOpen)(void *pClientPrivate, const char *pPath, int flags, void **pFilePrivate);
    BERR_Code (*FileRead)(void *pFilePrivate, uint32_t address, size_t bytesToRead, size_t *pBytesRead);
    BERR_Code (*FileWrite)(void *pFilePrivate, uint32_t address, size_t bytesToWrite, size_t *pBytesWritten);
    void (*FileClose)(void *pFilePrivate);
    BERR_Code (*AppOpen)(void *pClientPrivate, const char *pName, const char *pPath, void **pAppPrivate);
    void (*AppClose)(void *pAppPrivate);
    BERR_Code (*ConnectionOpen)(void *pAppPrivate, const char *pServiceName, const BTEE_ConnectionSettings *pSettings, void **pConnectionPrivate);
    BERR_Code (*ConnectionSendMessage)(void *pConnectionPrivate, const void *pMessage, size_t messageLength);
    void (*ConnectionClose)(void *pConnectionPrivate);
} BTEE_InstanceCreateSettings;

/***************************************************************************
Summary:
    Get default TEE Instance settings
***************************************************************************/
void BTEE_Instance_GetDefaultCreateSettings(
    BTEE_InstanceCreateSettings *pSettings /* [out] default settings */
    );

/***************************************************************************
Summary:
    Create a TEE instance
***************************************************************************/
BERR_Code BTEE_Instance_Create(
    const BTEE_InstanceCreateSettings *pSettings,
    BTEE_InstanceHandle *pInstance /* [out] handle to instance */
    );

/***************************************************************************
Summary:
    Destroy a TEE instance
***************************************************************************/
void BTEE_Instance_Destroy(
    BTEE_InstanceHandle hInstance
    );

#endif /* BTEE_INSTANCE_H__ */

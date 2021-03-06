/******************************************************************************
 *  Broadcom Proprietary and Confidential. (c)2016 Broadcom. All rights reserved.
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
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "wv_cdm_constants.h"
#include "drm_wvoemcrypto_tl.h"
#include "bdbg.h"

#include "OEMCryptoCENC.h"

BDBG_MODULE(oemcrypto_brcm_TL);
#define LOGV BDBG_MSG
#define LOGD BDBG_MSG
#define LOGE BDBG_ERR
#define LOGW BDBG_WRN

#define KEY_CONTROL_SIZE  16
#define KEY_IV_SIZE  16
#define KEY_PAD_SIZE  16
#define KEY_SIZE  16
#define MAC_KEY_SIZE  32

typedef struct {
  uint8_t signature[MAC_KEY_SIZE];
  uint8_t context[MAC_KEY_SIZE];
  uint8_t iv[KEY_IV_SIZE];
  uint8_t enc_rsa_key[KEY_SIZE];
} WrappedRSAKey;

//uncomment the following to enable debug dumps
//#define DUMP_HEX

static void dump_hex(char* name, const uint8_t* vector, size_t length)
{
// CAUTION: Enabling this function causes crashes with SVP.
#ifdef DUMP_HEX
    size_t i;
    size_t buf_len = length * 2 + length / 32 + 1;
    char *buf, *ptr;
    LOGD(("%s (len=%d) =", name, length));
    if (vector == NULL || length == 0)
    {
        LOGD(("vector is NULL or length is 0"));
        return;
    }

   ptr = buf = (char*)malloc(buf_len);
   for (i = 0; i < length; i++)
   {
        if (i % 32 == 0 && i != 0)
        {
            sprintf(ptr++, "\n");
        }
        sprintf(ptr, "%02X", vector[i]);
        ptr += 2;
    }
    *ptr = '\0';

    LOGD(("%s", buf));

    free(buf);
#else
    BSTD_UNUSED(name);
    BSTD_UNUSED(vector);
    BSTD_UNUSED(length);
#endif
}

OEMCryptoResult OEMCrypto_Initialize(void)
{
    Drm_WVOemCryptoParamSettings_t WvOemCryptoParamSettings;
    OEMCryptoResult wvRc = OEMCrypto_SUCCESS;

    LOGD(("%s entered", __FUNCTION__));

    DRM_WVOEMCrypto_GetDefaultParamSettings(&WvOemCryptoParamSettings);
    DRM_WVOemCrypto_SetParamSettings(&WvOemCryptoParamSettings);

    if ((DRM_WVOemCrypto_Initialize(&WvOemCryptoParamSettings, (int*)&wvRc) != Drm_Success)||(wvRc!=OEMCrypto_SUCCESS))
    {
       LOGD(("%s: Initilaize failed",__FUNCTION__));
       return wvRc;
    }

    LOGD(("[OEMCrypto_Initialize(): success]"));
    return wvRc;
}

OEMCryptoResult OEMCrypto_Terminate(void)
{
    OEMCryptoResult wvRc = OEMCrypto_SUCCESS;

    LOGD(("%s entered", __FUNCTION__));

    if (DRM_WVOemCrypto_UnInit((int*)&wvRc) != Drm_Success)
    {
      LOGD(("%s: Terminate failed",__FUNCTION__));
      return wvRc;
    }

    LOGD(("[OEMCrypto_Terminate(): success =========]"));
    return wvRc;
}

OEMCryptoResult OEMCrypto_OpenSession(OEMCrypto_SESSION* session)
{
    OEMCryptoResult wvRc = OEMCrypto_SUCCESS;
    uint32_t session_id;

    LOGD(("%s entered", __FUNCTION__));

    if ((DRM_WVOemCrypto_OpenSession(&session_id, (int*)&wvRc) != Drm_Success)||(wvRc!=OEMCrypto_SUCCESS))
    {
        LOGD(("%s:Opensession failed",__FUNCTION__));
        return wvRc;
    }

    *session = (OEMCrypto_SESSION)session_id;
    LOGD(("[OEMCrypto_OpenSession(): SID=%08x]", session_id));
    return OEMCrypto_SUCCESS;
}

OEMCryptoResult OEMCrypto_CloseSession(OEMCrypto_SESSION session)
{
    OEMCryptoResult wvRc = OEMCrypto_SUCCESS;
    LOGD(("%s entered", __FUNCTION__));

    if (drm_WVOemCrypto_CloseSession(session, (int*)&wvRc) != Drm_Success)
    {
        LOGD(("[OEMCrypto_CloseSession(SID=%08X): failed]", session));
        return wvRc;
    }
    else
    {
        LOGD(("[OEMCrypto_CloseSession(SID=%08X): success]", session));
        return OEMCrypto_SUCCESS;
    }
}

OEMCryptoResult OEMCrypto_GenerateNonce(OEMCrypto_SESSION session, uint32_t* nonce)
{
    OEMCryptoResult wvRc = OEMCrypto_SUCCESS;
    LOGD(("%s entered", __FUNCTION__));

    // Prevent nonce flood.
    static time_t last_nonce_time = 0;
    static int nonce_count = 0;
    time_t now = time(NULL);
    if (now == last_nonce_time)
    {
        nonce_count++;
        if (nonce_count > 20)
        {
            LOGE(("[OEMCrypto_GenerateNonce(): Nonce Flood detected]"));
            return OEMCrypto_ERROR_UNKNOWN_FAILURE;
        }
    } else
    {
        nonce_count = 1;
        last_nonce_time = now;
    }

    if (drm_WVOemCrypto_GenerateNonce(session, nonce, (int*)&wvRc) != Drm_Success)
    {
        LOGD(("%s:nonce generation failed ",__FUNCTION__));
        return wvRc;
    }
    return OEMCrypto_SUCCESS;
}

OEMCryptoResult OEMCrypto_GenerateDerivedKeys(OEMCrypto_SESSION session,
    const uint8_t* mac_key_context, uint32_t mac_key_context_length,
    const uint8_t* enc_key_context, uint32_t enc_key_context_length)
{
    OEMCryptoResult wvRc = OEMCrypto_SUCCESS;
    LOGD(("%s entered", __FUNCTION__));

    if (drm_WVOemCrypto_GenerateDerivedKeys(session, mac_key_context,
        mac_key_context_length, enc_key_context, enc_key_context_length,
        (int*)&wvRc) != Drm_Success)
    {
        LOGD(("[OEMCrypto_GenerateDerivedKeys(SID=%08X): failed]", session));
        return wvRc;
    }

    LOGD(("[OEMCrypto_GenerateDerivedKeys(SID=%08X): success]", session));
    return OEMCrypto_SUCCESS;
}

OEMCryptoResult OEMCrypto_GenerateSignature(
    OEMCrypto_SESSION session, const uint8_t* message,
    size_t message_length, uint8_t* signature, size_t* signature_length)
{
    OEMCryptoResult wvRc= OEMCrypto_SUCCESS;

    LOGD(("%s entered", __FUNCTION__));
    LOGD(("message length is %d",message_length));

    if (*signature_length < SHA256_DIGEST_LENGTH)
    {
        *signature_length = SHA256_DIGEST_LENGTH;
        return OEMCrypto_ERROR_SHORT_BUFFER;
    }

    if (message == NULL || message_length == 0 ||
        signature == NULL || signature_length == 0)
    {
        LOGE(("[OEMCrypto_GenerateSignature(): OEMCrypto_ERROR_INVALID_CONTEXT]"));
        return OEMCrypto_ERROR_INVALID_CONTEXT;
    }


    if (drm_WVOemCrypto_GenerateSignature(session, message, message_length,
        signature, signature_length, (int*)&wvRc) != Drm_Success)
    {
        LOGD(("[OEMCrypto_GenerateSignature(SID=%08X): failed]", session));
        return wvRc;
    }

    LOGD(("[OEMCrypto_GenerateSignature(SID=%08X): success]", session));
    return OEMCrypto_SUCCESS;
}

bool RangeCheck(const uint8_t* message, uint32_t message_length,
    const uint8_t* field, uint32_t field_length, bool allow_null)
{
    if (field == NULL)
        return allow_null;
    if (field < message)
        return false;
    if (field + field_length > message + message_length)
        return false;
    return true;
}

OEMCryptoResult OEMCrypto_LoadKeys(OEMCrypto_SESSION session,
    const uint8_t* message, size_t message_length, const uint8_t* signature,
    size_t signature_length, const uint8_t* enc_mac_key_iv,
    const uint8_t* enc_mac_keys, size_t num_keys,
    const OEMCrypto_KeyObject* key_array, const uint8_t* pst, size_t pst_length)
{
    OEMCryptoResult wvRc= OEMCrypto_SUCCESS;
    unsigned int i;

    LOGD(("%s entered", __FUNCTION__));

    /*TODO:Validate keybox*/

    if (message == NULL || message_length == 0 ||
        signature == NULL || signature_length == 0 ||
        key_array == NULL || num_keys == 0)
    {
        LOGE(("[OEMCrypto_LoadKeys(): OEMCrypto_ERROR_INVALID_CONTEXT]"));
        return OEMCrypto_ERROR_INVALID_CONTEXT;
    }

    /* Range check*/
    if (!RangeCheck(message, message_length, enc_mac_keys, 2*MAC_KEY_SIZE, true) ||
        !RangeCheck(message, message_length, enc_mac_key_iv, KEY_IV_SIZE, true)||
        !RangeCheck(message, message_length, pst, pst_length, true))
    {
        LOGE(("[OEMCrypto_LoadKeys(): OEMCrypto_ERROR_SIGNATURE_FAILURE - range check (pst included).]"));
        return OEMCrypto_ERROR_SIGNATURE_FAILURE;
    }

    for (i = 0; i < num_keys; i++)
    {
        if (!RangeCheck(message, message_length, key_array[i].key_id,
            key_array[i].key_id_length, false) ||
            !RangeCheck(message, message_length, key_array[i].key_data,
            key_array[i].key_data_length, false) ||
            !RangeCheck(message, message_length, key_array[i].key_data_iv,
            KEY_IV_SIZE, false) ||
            !RangeCheck(message, message_length, key_array[i].key_control,
            KEY_CONTROL_SIZE, false) ||
            !RangeCheck(message, message_length, key_array[i].key_control_iv,
            KEY_IV_SIZE, false))
        {
            LOGE(("[OEMCrypto_LoadKeys(): OEMCrypto_ERROR_SIGNATURE_FAILURE -range check %d]", i));
            return OEMCrypto_ERROR_SIGNATURE_FAILURE;
        }
    }

    /*TODO: this needs to be done on sage side. once impleementted on sage side, will delete this
    session_ctx->StartTimer();
    */

    if (drm_WVOemCrypto_LoadKeys(session, message, message_length,
        signature, signature_length, enc_mac_key_iv, enc_mac_keys, num_keys,
        (void*)key_array, pst, pst_length, (int *)&wvRc) != Drm_Success)
    {
        LOGE(("[OEMCrypto_Loadkeys(SID=%08X): failed]", session));
        return wvRc;
    }

    return OEMCrypto_SUCCESS;
}

OEMCryptoResult OEMCrypto_RefreshKeys(OEMCrypto_SESSION session,
    const uint8_t* message, size_t message_length, const uint8_t* signature,
    size_t signature_length, size_t num_keys,
    const OEMCrypto_KeyRefreshObject* key_array)
{
    OEMCryptoResult wvRc= OEMCrypto_SUCCESS;
    unsigned int i;

    LOGD(("%s entered", __FUNCTION__));

    if (message == NULL || message_length == 0 || signature == NULL ||
        signature_length == 0 || num_keys == 0)
    {
        LOGE(("[OEMCrypto_RefreshKeys(): OEMCrypto_ERROR_INVALID_CONTEXT]"));
        return OEMCrypto_ERROR_INVALID_CONTEXT;
    }

    /* Range check*/
    for (i = 0; i < num_keys; i++) {
        if (!RangeCheck(message, message_length, key_array[i].key_id,
            key_array[i].key_id_length, true) ||
            !RangeCheck(message, message_length, key_array[i].key_control,
            KEY_CONTROL_SIZE, false) ||
            !RangeCheck(message, message_length, key_array[i].key_control_iv,
            KEY_IV_SIZE, true))
        {
            LOGE(("[OEMCrypto_RefreshKeys(): Range Check %d]", i));
            return OEMCrypto_ERROR_SIGNATURE_FAILURE;
        }
    }

    if (drm_WVOemCrypto_RefreshKeys(session, message, message_length, signature,
        signature_length, num_keys, (void*)key_array, (int*)&wvRc) != Drm_Success)
    {
        LOGD(("[OEMCrypto_Refresh(SID=%08X): failed with error rc=%d]", session,wvRc));
        return wvRc;
    }

    return OEMCrypto_SUCCESS;
}

OEMCryptoResult OEMCrypto_QueryKeyControl(OEMCrypto_SESSION session, const uint8_t* key_id,
                                          size_t key_id_length, uint8_t* key_control_block,
                                          size_t* key_control_block_length)
{
    OEMCryptoResult wvRc = OEMCrypto_SUCCESS;

    LOGV(("Entered OEMCrypto_QueryKeyControl"));
    dump_hex("key_id", key_id, key_id_length);

    if (Drm_WVOemCrypto_QueryKeyControl(session, key_id, key_id_length,key_control_block,
           key_control_block_length, (int*)&wvRc) != Drm_Success)
    {
        LOGD(("[OEMCrypto_QueryKeyControl(SID=%08X): failed] with error 0x%x", session,wvRc));
        return wvRc;
    }

    LOGV(("[OEMCrypto_QueryKeyControl(SID=%08X): passed]", session));
    dump_hex("key_ctrl_box", key_control_block, *key_control_block_length);
    return wvRc;

}


OEMCryptoResult OEMCrypto_SelectKey(const OEMCrypto_SESSION session,
    const uint8_t* key_id, size_t key_id_length)
{
    OEMCryptoResult wvRc = OEMCrypto_SUCCESS;

    //LOGD(("%s entered", __FUNCTION__));

    if (drm_WVOemCrypto_SelectKey(session, key_id, key_id_length, (int*)&wvRc) != Drm_Success)
    {
        LOGD(("[OEMCrypto_SelectKeys(SID=%08X): failed]", session));
        return wvRc;
    }

    LOGV(("[OEMCrypto_selectKeys(SID=%08X): passed]", session));
    return OEMCrypto_SUCCESS;
}

/*WV v10 changes*/

OEMCryptoResult SetDestination(OEMCrypto_DestBufferDesc* out_buffer,
                               size_t data_length, uint8_t** destination,
                               size_t* max_length,
                               Drm_WVOemCryptoBufferType_t *buffer_type)
{
    if (destination == NULL || data_length == 0 || out_buffer == NULL)
    {
        LOGE(("[SetDestination: OEMCrypto_ERROR_INVALID_CONTEXT]"));
        return OEMCrypto_ERROR_INVALID_CONTEXT;
    }
    switch (out_buffer->type)
    {
        case OEMCrypto_BufferType_Clear:
            LOGV(("%s: outbuffer is CLEAR",__FUNCTION__));
            *buffer_type = Drm_WVOEMCrypto_BufferType_Clear;
            *destination = out_buffer->buffer.clear.address;
            *max_length = out_buffer->buffer.clear.max_length;
            break;
        case OEMCrypto_BufferType_Secure:
             LOGV(("%s: outbuffer is Secure",__FUNCTION__));
            *buffer_type = Drm_WVOEMCrypto_BufferType_Secure;
            *destination = (uint8_t*)(out_buffer->buffer.secure.handle)
                           + out_buffer->buffer.secure.offset;
            *max_length = out_buffer->buffer.secure.max_length;
            break;
        default:
        case OEMCrypto_BufferType_Direct:
            *buffer_type = Drm_WVOEMCrypto_BufferType_Direct;
            *destination = NULL;
            break;
    }

    if (*buffer_type != Drm_WVOEMCrypto_BufferType_Direct && *max_length < data_length)
    {
        LOGE(("%s: OEMCrypto_ERROR_SHORT_BUFFER]",__FUNCTION__));
        return OEMCrypto_ERROR_SHORT_BUFFER;
    }

    if ((*buffer_type != Drm_WVOEMCrypto_BufferType_Direct) && (*destination == NULL))
    {
        return OEMCrypto_ERROR_INVALID_CONTEXT;
    }

    return OEMCrypto_SUCCESS;
}


OEMCryptoResult OEMCrypto_DecryptCTR(OEMCrypto_SESSION session,
                                    const uint8_t* data_addr,
                                    size_t data_length,
                                    bool is_encrypted,
                                    const uint8_t* iv,
                                    size_t block_offset,
                                    OEMCrypto_DestBufferDesc* out_buffer,
                                    uint8_t subsample_flags)
{
    Drm_WVOemCryptoBufferType_t buffer_type = Drm_WVOEMCrypto_BufferType_Direct;
    OEMCryptoResult wvRc = OEMCrypto_SUCCESS;
    uint8_t* destination = NULL;
    uint32_t out_sz;
    size_t max_length = 0;
    OEMCryptoResult sts = OEMCrypto_SUCCESS;

    sts = SetDestination(out_buffer, data_length, &destination,
                                       &max_length,&buffer_type);
    if (sts != OEMCrypto_SUCCESS)
    {
        LOGE(("%s:SetDestination() returned error \n",__FUNCTION__));
        return sts;
    }

    dump_hex((char*)"enc data:", data_addr, data_length);

    if (drm_WVOemCrypto_DecryptCTR(session, data_addr, data_length,
        is_encrypted, buffer_type, iv, block_offset, destination, &out_sz,
        subsample_flags, (int*)&wvRc) != Drm_Success)
    {
        LOGD(("[OEMCrypto_DecryptCTR(SID=%08X): failed]", session));
        return wvRc;
    }

    dump_hex((char*)"out_buffer->buffer.clear.address", out_buffer->buffer.clear.address, 256);

    return wvRc;
}


OEMCryptoResult OEMCrypto_IsKeyboxValid(void)
{
    OEMCryptoResult wvRc = OEMCrypto_SUCCESS;
    LOGD(("%s entered", __FUNCTION__));

    if (drm_WVOemCrypto_IsKeyboxValid((int*)&wvRc) != Drm_Success)
    {
        LOGD(("[OEMCrypto_IsKeyboxValid: failed]"));
        return wvRc;
    }
    return OEMCrypto_SUCCESS;
}

OEMCryptoResult OEMCrypto_GetDeviceID(uint8_t* deviceID, size_t* idLength)
{
    OEMCryptoResult wvRc = OEMCrypto_SUCCESS;

    LOGD(("%s entered", __FUNCTION__));

    if (drm_WVOemCrypto_GetDeviceID(deviceID, idLength, (int*)&wvRc) != Drm_Success)
    {
        LOGD(("[OEMCrypto_GetDeviceID: failed]"));
        return wvRc;
    }

    return OEMCrypto_SUCCESS;
}

OEMCryptoResult OEMCrypto_GetKeyData(uint8_t* keyData, size_t* keyDataLength)
{
    OEMCryptoResult wvRc = OEMCrypto_SUCCESS;

    LOGD(("%s entered", __FUNCTION__));

    if (drm_WVOemCrypto_GetKeyData(keyData, keyDataLength, (int *)&wvRc) != Drm_Success)
    {
        LOGD(("[OEMCrypto_GetKeyData: failed]"));
        return wvRc;
    }

    return wvRc;
}

OEMCryptoResult OEMCrypto_GetRandom(uint8_t* randomData, size_t dataLength)
{

    LOGD(("%s entered", __FUNCTION__));

    if (!randomData) {
        return OEMCrypto_ERROR_UNKNOWN_FAILURE;
    }

    if (drm_WVOemCrypto_GetRandom(randomData, dataLength) != Drm_Success)
    {
        LOGD(("[OEMCrypto_GetRandom: failed]"));
        return OEMCrypto_ERROR_UNKNOWN_FAILURE;
    }

    return OEMCrypto_SUCCESS;
}

OEMCryptoResult OEMCrypto_WrapKeybox(const uint8_t* keybox,
    size_t keyBoxLength, uint8_t* wrappedKeybox, size_t* wrappedKeyBoxLength,
    const uint8_t* transportKey, size_t transportKeyLength)
{
    //This is not needed for L1.
    BSTD_UNUSED(keybox);
    BSTD_UNUSED(keyBoxLength);
    BSTD_UNUSED(wrappedKeybox);
    BSTD_UNUSED(wrappedKeyBoxLength);
    BSTD_UNUSED(transportKey);
    BSTD_UNUSED(transportKeyLength);
    return OEMCrypto_SUCCESS;
}

OEMCryptoResult OEMCrypto_RewrapDeviceRSAKey(OEMCrypto_SESSION session,
    const uint8_t* message, size_t message_length, const uint8_t* signature,
    size_t signature_length, const uint32_t* nonce, const uint8_t* enc_rsa_key,
    size_t enc_rsa_key_length, const uint8_t* enc_rsa_key_iv,
    uint8_t* wrapped_rsa_key, size_t*  wrapped_rsa_key_length)
{
    OEMCryptoResult wvRc = OEMCrypto_SUCCESS;
    LOGD(("%s entered", __FUNCTION__));

    if (wrapped_rsa_key_length == NULL) {
        LOGE(("[OEMCrypto_RewrapDeviceRSAKey(): OEMCrypto_ERROR_INVALID_CONTEXT]"));
        return OEMCrypto_ERROR_INVALID_CONTEXT;
    }

    if (drm_WVOemCrypto_IsKeyboxValid((int *)&wvRc) != Drm_Success)
    {
        LOGE(("[OEMCrypto_RewrapDeviceRSAKey(): Invalid Key box !!]"));
        return wvRc;
    }

    if (message == NULL || message_length == 0 || signature == NULL ||
        signature_length == 0 || nonce == NULL || enc_rsa_key == NULL)
    {
        LOGE(("[OEMCrypto_RewrapDeviceRSAKey(): OEMCrypto_ERROR_INVALID_CONTEXT]"));
        return OEMCrypto_ERROR_INVALID_CONTEXT;
    }

    LOGD(("[OEMCrypto_RewrapDeviceRSAKey(): Range Check......]"));

    /* Range check*/
    if (!RangeCheck(message, message_length, (const uint8_t*)(nonce),
        sizeof(uint32_t), true) ||
        !RangeCheck(message, message_length, enc_rsa_key, enc_rsa_key_length, true) ||
        !RangeCheck(message, message_length, enc_rsa_key_iv, KEY_IV_SIZE, true))
    {
        LOGE(("[OEMCrypto_RewrapDeviceRSAKey():  - range check.]"));
        return OEMCrypto_ERROR_SIGNATURE_FAILURE;
    }

    LOGD(("[OEMCrypto_RewrapDeviceRSAKey(): Range Check done"));
    LOGD(("[OEMCrypto_RewrapDeviceRSAKey(): call thinlayer api......]"));

    if (drm_WVOemCrypto_RewrapDeviceRSAKey(session, message, message_length,
        signature, signature_length, nonce, enc_rsa_key, enc_rsa_key_length,
        enc_rsa_key_iv, wrapped_rsa_key, wrapped_rsa_key_length, (int *)&wvRc) != Drm_Success)
    {
        if (wvRc == OEMCrypto_ERROR_SHORT_BUFFER)
            LOGW(("[OEMCrypto_RewrapDeviceRSAKey(): drm_WVOemCrypto_RewrapDeviceRSAKey returned SHORT_BUFFER"));
        else
            LOGE(("[OEMCrypto_RewrapDeviceRSAKey(): drm_WVOemCrypto_RewrapDeviceRSAKey error rc=%d]",wvRc));

        return wvRc;
    }

    return OEMCrypto_SUCCESS;
}

OEMCryptoResult OEMCrypto_LoadDeviceRSAKey(OEMCrypto_SESSION session,
    const uint8_t* wrapped_rsa_key, size_t wrapped_rsa_key_length)
{
    OEMCryptoResult wvRc = OEMCrypto_SUCCESS;
    LOGD(("%s entered", __FUNCTION__));

    if (wrapped_rsa_key == NULL) {
        LOGE(("[OEMCrypto_LoadDeviceRSAKey(): OEMCrypto_ERROR_INVALID_CONTEXT]"));
        return OEMCrypto_ERROR_INVALID_CONTEXT;
    }

    if (drm_WVOemCrypto_LoadDeviceRSAKey(session, wrapped_rsa_key,
        wrapped_rsa_key_length, (int *)&wvRc) != Drm_Success)
    {
        return wvRc;
    }

    return OEMCrypto_SUCCESS;
}

OEMCryptoResult OEMCrypto_GenerateRSASignature(OEMCrypto_SESSION session,
    const uint8_t* message, size_t message_length, uint8_t* signature,
    size_t* signature_length, RSA_Padding_Scheme padding_scheme)
{
    OEMCryptoResult wvRc = OEMCrypto_SUCCESS;
    LOGD(("%s entered", __FUNCTION__));

    if (message == NULL || message_length == 0)
    {
        LOGE(("[OEMCrypto_GenerateRSASignature(): OEMCrypto_ERROR_INVALID_CONTEXT]"));
        return OEMCrypto_ERROR_INVALID_CONTEXT;
    }

    if (drm_WVOemCrypto_GenerateRSASignature(session, message, message_length,
       signature, signature_length, (WvOemCryptoRSA_Padding_Scheme)padding_scheme,
       (int *)&wvRc) != Drm_Success)
    {
        if (wvRc == OEMCrypto_ERROR_SHORT_BUFFER)
            LOGW(("%s: SHORT_BUFFER case", __FUNCTION__));
        else
            LOGE(("%s - ERROR: wvRc = 0x%08x", __FUNCTION__, wvRc));
    }

    LOGD(("%s - wvRc = 0x%08x", __FUNCTION__, wvRc));
    return wvRc;
}

OEMCryptoResult OEMCrypto_DeriveKeysFromSessionKey(
    OEMCrypto_SESSION session, const uint8_t* enc_session_key,
    size_t enc_session_key_length, const uint8_t* mac_key_context,
    size_t mac_key_context_length, const uint8_t* enc_key_context,
    size_t enc_key_context_length)
{
    OEMCryptoResult wvRc = OEMCrypto_SUCCESS;

    LOGD(("%s entered", __FUNCTION__));

    if (drm_WVOemCrypto_IsKeyboxValid((int *)&wvRc) != Drm_Success)
    {
        return wvRc;
    }

    if (drm_WVOemCrypto_DeriveKeysFromSessionKey(session, enc_session_key,
        enc_session_key_length, mac_key_context, mac_key_context_length,
        enc_key_context, enc_key_context_length, (int *)&wvRc) != Drm_Success)
    {
        LOGD(("%s - -- Error ********", __FUNCTION__));
    }

    return wvRc;
}

uint32_t OEMCrypto_APIVersion()
{
    return 10;
}

const char* OEMCrypto_SecurityLevel()
{
    return "L1";
}

OEMCryptoResult OEMCrypto_GetHDCPCapability(OEMCrypto_HDCP_Capability *current,
    OEMCrypto_HDCP_Capability *maximum)
{
    OEMCryptoResult wvRc = OEMCrypto_SUCCESS;;

    LOGD(("%s entered", __FUNCTION__));

    if (current == NULL)
        return OEMCrypto_ERROR_UNKNOWN_FAILURE;
    if (maximum == NULL)
        return OEMCrypto_ERROR_UNKNOWN_FAILURE;

    if (drm_WVOemCrypto_GetHDCPCapability((uint32_t*)current, (uint32_t*)maximum, (int*)&wvRc) != Drm_Success)
    {
        return  wvRc;
    }

    LOGD(("OEMCrypto_GetHDCPCapability: current=%u max=%u", *current, *maximum));
    return OEMCrypto_SUCCESS;
}

OEMCryptoResult OEMCrypto_Generic_Encrypt(OEMCrypto_SESSION session,
    const uint8_t* in_buffer, size_t buffer_length, const uint8_t* iv,
    OEMCrypto_Algorithm algorithm, uint8_t* out_buffer)
{
    OEMCryptoResult wvRc= OEMCrypto_SUCCESS;

    if (in_buffer == NULL || buffer_length == 0 ||
        iv == NULL || out_buffer == NULL)
    {
        LOGE(("[OEMCrypto_Generic_Enrypt(): OEMCrypto_ERROR_INVALID_CONTEXT]"));
        return OEMCrypto_ERROR_INVALID_CONTEXT;
    }

    if (drm_WVOemCrypto_Generic_Encrypt(session, in_buffer, buffer_length,
        iv, (Drm_WVOemCryptoAlgorithm)algorithm,
        out_buffer, (int*)&wvRc) != Drm_Success)
    {
        return  wvRc;
    }

    return OEMCrypto_SUCCESS;
}

OEMCryptoResult OEMCrypto_Generic_Decrypt(OEMCrypto_SESSION session,
    const uint8_t* in_buffer, size_t buffer_length, const uint8_t* iv,
    OEMCrypto_Algorithm algorithm, uint8_t* out_buffer)

{
    OEMCryptoResult wvRc = OEMCrypto_SUCCESS;

    if (in_buffer == NULL || buffer_length == 0 ||
        iv == NULL || out_buffer == NULL)
    {
        LOGE(("[OEMCrypto_Generic_Decrypt(): OEMCrypto_ERROR_INVALID_CONTEXT]"));
        return OEMCrypto_ERROR_INVALID_CONTEXT;
    }

    if (drm_WVOemCrypto_Generic_Decrypt(session, in_buffer, buffer_length,
        iv, (Drm_WVOemCryptoAlgorithm)algorithm,
        out_buffer, (int*)&wvRc) != Drm_Success)
    {
        LOGE(("[OEMCrypto_Generic_Decrypt(): failed]"));
        return wvRc;
    }

    return OEMCrypto_SUCCESS;
}

OEMCryptoResult OEMCrypto_Generic_Sign(OEMCrypto_SESSION session,
    const uint8_t* in_buffer, size_t buffer_length, OEMCrypto_Algorithm algorithm,
    uint8_t* signature, size_t* signature_length)
{
    OEMCryptoResult wvRc = OEMCrypto_SUCCESS;

    if (*signature_length < SHA256_DIGEST_LENGTH)
    {
        *signature_length = SHA256_DIGEST_LENGTH;
        LOGE(("[OEMCrypto_Generic_Sign(): OEMCrypto_ERROR_SHORT_BUFFER]"));
        return OEMCrypto_ERROR_SHORT_BUFFER;
    }

    if (in_buffer == NULL || buffer_length == 0 || signature == NULL)
    {
        LOGE(("[OEMCrypto_Generic_Sign(): OEMCrypto_ERROR_INVALID_CONTEXT]"));
        return OEMCrypto_ERROR_INVALID_CONTEXT;
    }

    if (drm_WVOemCrypto_Generic_Sign(session, in_buffer, buffer_length,
        algorithm, signature, signature_length, (int*)&wvRc) != Drm_Success)
    {
        LOGD(("[OEMCrypto_Generic_Sign(): failed"));
        return wvRc;
    }
    LOGD(("[OEMCrypto_Generic_Sign(): passed"));
    return OEMCrypto_SUCCESS;
}

OEMCryptoResult OEMCrypto_Generic_Verify(OEMCrypto_SESSION session,
    const uint8_t* in_buffer, size_t buffer_length, OEMCrypto_Algorithm algorithm,
    const uint8_t* signature, size_t signature_length)
{
    OEMCryptoResult wvRc = OEMCrypto_SUCCESS;

    if (signature_length != SHA256_DIGEST_LENGTH) {
        return OEMCrypto_ERROR_UNKNOWN_FAILURE;
    }
    if (in_buffer == NULL || buffer_length == 0 || signature == NULL) {
        LOGE(("[OEMCrypto_Generic_Verify(): OEMCrypto_ERROR_INVALID_CONTEXT]"));
        return OEMCrypto_ERROR_INVALID_CONTEXT;
    }
    if (drm_WVOemCrypto_Generic_Verify(session, in_buffer, buffer_length,
        algorithm, signature, signature_length, (int*)&wvRc) != Drm_Success)
    {
        return wvRc;
    }
    return OEMCrypto_SUCCESS;
}

/*
 * OEMCrypto_SupportsUsageTable()
 *
 * Description:
 *   This is used to determine if the device can support a usage table.  Since this
 *   function is spoofable, it is not relied on for security purposes.  It is for
 *   information only.  The usage table is described in the section above.
 *
 * Parameters:
 *   none
 *
 * Threading:
 *   This function may be called simultaneously with any other functions.
 *
 * Returns:
 *   Returns true if the device can maintain a usage table. Returns false otherwise.
 *
 * Version:
 *   This method changed in API version 9.
 */
bool OEMCrypto_SupportsUsageTable() {
    Sage_OEMCryptoResult wvRc = SAGE_OEMCrypto_SUCCESS;

    if (DRM_WVOemCrypto_SupportsUsageTable((int*)&wvRc) != Drm_Success)
    {
        LOGE(("[%s(): call FAILED (%d)]", __FUNCTION__, wvRc));
    }

    return (wvRc == SAGE_OEMCrypto_SUCCESS);
}

/*
 * OEMCrypto_UpdateUsageTable
 *
 * Description:
 *   OEMCrypto should propagate values from all open sessions to the Session Usage
 *   Table.  If any values have changed, increment the generation number, sign, and
 *   save the table.  During playback, this function will be called approximately
 *   once per minute.
 *
 *   Devices that do not implement a Session Usage Table may return
 *   OEMCrypto_ERROR_NOT_IMPLEMENTED.
 *
 * Parameters:
 *   none
 *
 * Threading:
 *   This function will not be called simultaneously with any session functions.
 *
 * Returns:
 *   OEMCrypto_SUCCESS success
 *   OEMCrypto_ERROR_NOT_IMPLEMENTED
 *   OEMCrypto_ERROR_UNKNOWN_FAILURE
 *
 * Version:
 *   This method changed in API version 9.
 */
OEMCryptoResult OEMCrypto_UpdateUsageTable()
{
    OEMCryptoResult wvRc = OEMCrypto_SUCCESS;

    if (DRM_WVOemCrypto_UpdateUsageTable((int*)&wvRc) != Drm_Success)
    {
        LOGE(("[%s(): call FAILED (%d)]", __FUNCTION__, wvRc));
    }

    return wvRc;
}

/*
 * OEMCrypto_DeactivateUsageEntry
 *
 * Description:
 *   Find the entry in the Usage Table with a matching PST.  Mark the status of
 *   that entry as “inactive�.  If it corresponds to an open session, the status of
 *   that session will also be marked as “inactive�.  Then OEMCrypto will increment
 *   Usage Table’s generation number, sign, encrypt, and save the Usage Table.
 *
 *   If no entry in the Usage Table has a matching PST, return the error
 *   OEMCrypto_ERROR_INVALID_CONTEXT.
 *
 *   Devices that do not implement a Session Usage Table may return
 *   OEMCrypto_ERROR_NOT_IMPLEMENTED.
 *
 * Parameters:
 *   pst (in) - pointer to memory containing Provider Session Token.
 *   pst_length (in) - length of the pst, in bytes.
 *
 * Threading:
 *   This function will not be called simultaneously with any session functions.
 *
 * Returns:
 *   OEMCrypto_SUCCESS success
 *   OEMCrypto_ERROR_INVALID_CONTEXT - no entry has matching PST.
 *   OEMCrypto_ERROR_NOT_IMPLEMENTED
 *   OEMCrypto_ERROR_UNKNOWN_FAILURE
 *
 * Version:
 *   This method changed in API version 9.
 */
OEMCryptoResult OEMCrypto_DeactivateUsageEntry(const uint8_t *pst, size_t pst_length)
{
    OEMCryptoResult wvRc = OEMCrypto_SUCCESS;

    if (DRM_WVOemCrypto_DeactivateUsageEntry((uint8_t *)pst, pst_length, (int*)&wvRc) != Drm_Success)
    {
        LOGE(("[%s(): call FAILED (%d)]", __FUNCTION__, wvRc));
    }

    return wvRc;
}

/*
 * OEMCrypto_ReportUsage
 *
 * Description:
 *   If the buffer_length is not sufficient to hold a report structure, set
 *   buffer_length and return OEMCrypto_ERROR_SHORT_BUFFER.
 *
 *   If no entry in the Usage Table has a matching PST, return the error
 *   OEMCrypto_ERROR_INVALID_CONTEXT.
 *
 *   OEMCrypto will increment Usage Table’s generation number, sign, encrypt, and
 *   save the Usage Table.  This is done, even though the table has not changed, so
 *   that a single rollback cannot undo a call to DeactivateUsageEntry and still
 *   report that license as inactive.
 *
 *   The pst_report is filled out by subtracting the times un the Usage Table from
 *   the current time on the secure clock.  This is done in case the secure clock
 *   is not using UTC time, but is instead using something like seconds since clock
 *   installed.
 *
 *   Valid values for status are:
 *     0 = kUnused -- the keys have not been used to decrypt.
 *     1 = kActive -- the keys have been used, and have not been deactivated.
 *     2 = kInactive -- the keys have been marked inactive.
 *
 *   The clock_security_level is reported as follows:
 *     0 = Insecure Clock - clock just uses system time.
 *     1 = Secure Timer - clock uses secure timer, which cannot be modified by user
 *     software, when OEMCrypto is active and the system time when OEMCrypto is
 *     inactive.
 *     2 = Software Secure Clock - clock cannot be modified by user software when
 *     OEMCrypto is active or inactive.
 *     3 = Hardware Secure Clock - clock cannot be modified by user software and
 *     there are security features that prevent the user from modifying the clock
 *     in hardware, such as a tamper proof battery.
 *
 *   After pst_report has been filled in, the HMAC SHA1 signature is computed for
 *   the buffer from bytes 20 to the end of the pst field.  The signature is
 *   computed using the client_mac_key which is stored in the usage table.  The
 *   HMAC SHA1 signature is used to prevent a rogue application from using
 *   OMECrypto_GenerateSignature to forge a Usage Report.
 *
 *   This function also copies the client_mac_key and server_mac_key from the Usage
 *   Table entry to the session.  They will be used to verify a signature in
 *   OEMCrypto_DeleteUsageEntry below.  This session will be associated with the
 *   entry in the Usage Table.
 *
 *   Devices that do not implement a Session Usage Table may return
 *   OEMCrypto_ERROR_NOT_IMPLEMENTED.
 *
 * Parameters:
 *   session (in) - handle for the session to be used.
 *   pst (in) - pointer to memory containing Provider Session Token.
 *   pst_length (in) - length of the pst, in bytes.
 *   buffer (out) - pointer to buffer in which usage report should be stored.   May
 *   be null on the first call in order to find required buffer size.
 *   buffer_length (in/out) - (in) length of the report buffer, in bytes.
 *                           (out) actual length of the report
 *
 * Threading:
 *   This function will not be called simultaneously with any session functions.
 *
 * Returns:
 *   OEMCrypto_SUCCESS success
 *   OEMCrypto_ERROR_SHORT_BUFFER if report buffer is not large enough to hold the
 *   output signature.
 *   OEMCrypto_ERROR_INVALID_SESSION no open session with that id.
 *   OEMCrypto_ERROR_INVALID_CONTEXT - no entry has matching PST.
 *   OEMCrypto_ERROR_NOT_IMPLEMENTED
 *   OEMCrypto_ERROR_UNKNOWN_FAILURE
 *
 * Version:
 *   This method changed in API version 9.
 */
OEMCryptoResult OEMCrypto_ReportUsage(OEMCrypto_SESSION session,
    const uint8_t *pst, size_t pst_length, OEMCrypto_PST_Report *buffer,
    size_t *buffer_length)
{
    OEMCryptoResult wvRc = OEMCrypto_SUCCESS;

    if (DRM_WVOemCrypto_ReportUsage(session, pst, pst_length, (WvOEMCryptoPstReport*)buffer, buffer_length, (int*)&wvRc) != Drm_Success)
    {
        LOGE(("[%s(): call FAILED (%d)]", __FUNCTION__, wvRc));
    }

    return wvRc;
}

/*
 * OEMCrypto_DeleteUsageEntry
 *
 * Description:
 *   This function verifies the signature of the given message using the sessions
 *   mac_key[server] and the algorithm HMAC-SHA256, and then deletes an entry from
 *   the session table.   The session should already be associated with the given
 *   entry, from a previous call to OEMCrypto_ReportUsage.
 *
 *   After performing all verification listed below, and deleting the entry from
 *   the Usage Table, OEMCrypto will increment Usage Table’s generation number, and
 *   then sign, encrypt, and save the Usage Table.
 *
 *   The signature verification shall use a constant-time algorithm (a signature
 *   mismatch will always take the same time as a successful comparison).
 *
 *   Devices that do not implement a Session Usage Table may return
 *   OEMCrypto_ERROR_NOT_IMPLEMENTED.
 *
 *   Verification:
 *   The following checks should be performed.  If any check fails, an error is
 *   returned.
 *   1. The pointer pst is not null, and points inside the message.  If not, return
 *   OEMCrypto_ERROR_UNKNOWN_FAILURE.
 *   2. The signature of the message shall be computed, and the API shall verify
 *   the computed signature matches the signature passed in.  The signature will be
 *   computed using HMAC-SHA256 and the mac_key_server.  If they do not match,
 *   return OEMCrypto_ERROR_SIGNATURE_FAILURE.
 *   3. If the session is not associated with an entry in the Usage Table,  return
 *   OEMCrypto_ERROR_UNKNOWN_FAILURE.
 *   4. If the pst passed in as a parameter does not match that in the Usage Table,
 *   return OEMCrypto_ERROR_UNKNOWN_FAILURE.
 *
 * Parameters:
 *   session (in) - handle for the session to be used.
 *   pst (in) - pointer to memory containing Provider Session Token.
 *   pst_length (in) - length of the pst, in bytes.
 *   message (in) - pointer to memory containing message to be verified.
 *   message_length (in) - length of the message, in bytes.
 *   signature (in) - pointer to memory containing the signature.
 *   signature_length (in) - length of the signature, in bytes.
 *
 * Threading:
 *   This function will not be called simultaneously with any session functions.
 *
 * Returns:
 *   OEMCrypto_SUCCESS success
 *   OEMCrypto_ERROR_INVALID_SESSION no open session with that id.
 *   OEMCrypto_ERROR_SIGNATURE_FAILURE
 *   OEMCrypto_ERROR_NOT_IMPLEMENTED
 *   OEMCrypto_ERROR_UNKNOWN_FAILURE
 *
 * Version:
 *   This method changed in API version 9.
 */
OEMCryptoResult OEMCrypto_DeleteUsageEntry(OEMCrypto_SESSION session,
    const uint8_t* pst, size_t pst_length, const uint8_t *message,
    size_t message_length, const uint8_t *signature, size_t signature_length)
{
    OEMCryptoResult wvRc = OEMCrypto_SUCCESS;

    if (!RangeCheck(message, message_length, pst, pst_length, false)) {
        LOGE(("[OEMCrypto_DeleteUsageEntry(): range check.]"));
        return OEMCrypto_ERROR_SIGNATURE_FAILURE;
    }

    if (DRM_WVOemCrypto_DeleteUsageEntry(session, pst, pst_length, message,
        message_length, signature, signature_length, (int*)&wvRc) != Drm_Success)
    {
        LOGE(("[%s(): call FAILED (%d)]", __FUNCTION__, wvRc));
    }

    return wvRc;
}

/*
 * OEMCrypto_DeleteUsageTable
 *
 * Description:
 *   This is called when the CDM system believes there are major problems or
 *   resource issues.  The entire table should be cleaned and a new table should be
 *   created.
 *
 * Parameters:
 *   none
 *
 * Threading:
 *   This function will not be called simultaneously with any session functions.
 *
 * Returns:
 *   OEMCrypto_SUCCESS success
 *   OEMCrypto_ERROR_NOT_IMPLEMENTED
 *   OEMCrypto_ERROR_UNKNOWN_FAILURE
 *
 * Version:
 *   This method changed in API version 9.
 */
OEMCryptoResult OEMCrypto_DeleteUsageTable()
{
    OEMCryptoResult wvRc = OEMCrypto_SUCCESS;

    if (DRM_WVOemCrypto_DeleteUsageTable((int*)&wvRc) != Drm_Success)
    {
        LOGE(("[%s(): call FAILED (%d)]", __FUNCTION__, wvRc));
    }

    return wvRc;
}


//WV10


OEMCryptoResult OEMCrypto_GetNumberOfOpenSessions(size_t* count)
{

    OEMCryptoResult wvRc = OEMCrypto_SUCCESS;
    uint32_t numOfOpenSessions = 0;
    LOGD(("%s entered", __FUNCTION__));

    if( count == NULL)
    {
        LOGE(("[OEMCrypto_GetNumberOfOpenSessions: OEMCrypto_ERROR_INVALID_CONTEXT, input param count == NULL]"));
        LOGV(("%s exiting..",__FUNCTION__));
        return OEMCrypto_ERROR_INVALID_CONTEXT;
    }

    if (DRM_WVOemCrypto_GetNumberOfOpenSessions(&numOfOpenSessions, (int*)&wvRc) != Drm_Success)
    {
        LOGD(("%s:Opensession failed",__FUNCTION__));
        return wvRc;
    }

    *count = (size_t)numOfOpenSessions;
    LOGD(("[OEMCrypto_GetNumberOfOpenSessions(): no. of Open sessions=%08x]", numOfOpenSessions));
    return OEMCrypto_SUCCESS;
}

OEMCryptoResult OEMCrypto_GetMaxNumberOfSessions(size_t* maximum)
{
    OEMCryptoResult wvRc = OEMCrypto_SUCCESS;
    uint32_t numOfMaxSessions = 0;
    LOGD(("%s entered", __FUNCTION__));

     if( maximum == NULL)
    {
        LOGE(("[OEMCrypto_GetMaxNumberOfSessions: OEMCrypto_ERROR_INVALID_CONTEXT, input param maximum == NULL]"));
        LOGV(("%s exiting..",__FUNCTION__));
        return OEMCrypto_ERROR_INVALID_CONTEXT;
    }

    if (DRM_WVOemCrypto_GetMaxNumberOfSessions(&numOfMaxSessions, (int*)&wvRc) != Drm_Success)
    {
        LOGD(("%s:Opensession failed",__FUNCTION__));
        return wvRc;
    }

    *maximum = (size_t)numOfMaxSessions;
    LOGD(("[OEMCrypto_GetMaxNumberOfSessions(): Max no. of  sessions supported=%08x]", numOfMaxSessions));
    return OEMCrypto_SUCCESS;}


bool OEMCrypto_IsAntiRollbackHwPresent()
{
    return true;
}

OEMCryptoResult OEMCrypto_CopyBuffer(const uint8_t *data_addr,
                                  size_t data_length,
                                  OEMCrypto_DestBufferDesc* out_buffer,
                                  uint8_t subsample_flags)
{
    uint8_t* destination = NULL;
    size_t max_length = 0;
    OEMCryptoResult sts = OEMCrypto_SUCCESS;
    Drm_WVOemCryptoBufferType_t buffer_type = Drm_WVOEMCrypto_BufferType_Direct;

    LOGV(("%s entered", __FUNCTION__));

    if (data_addr == NULL )
    {
        LOGE(("[OEMCrypto_CopyBuffer(): OEMCrypto_ERROR_INVALID_CONTEXT, data_addr ==NULL]"));
        LOGV(("%s exiting..",__FUNCTION__));
        return OEMCrypto_ERROR_INVALID_CONTEXT;
    }

    if(out_buffer == NULL)
    {
        LOGE(("[OEMCrypto_CopyBuffer(): OEMCrypto_ERROR_INVALID_CONTEXT, out_buffer ==NULL]"));
        LOGV(("%s exiting..",__FUNCTION__));
        return OEMCrypto_ERROR_INVALID_CONTEXT;
    }

    sts = SetDestination(out_buffer, data_length, &destination,
                                       &max_length,&buffer_type);
    if (sts != OEMCrypto_SUCCESS)
    {
        LOGV(("%s setdestination failed    exiting..",__FUNCTION__));
        return sts;
    }

    if (destination != NULL)
    {
        if ((Drm_WVOemCrypto_CopyBuffer(destination,data_addr, data_length) != Drm_Success))
       {
            LOGE(("[OEMCrypto_CopyBuffer(): failed]"));
            return OEMCrypto_ERROR_UNKNOWN_FAILURE;
       }
    }

    return OEMCrypto_SUCCESS;
}

OEMCryptoResult OEMCrypto_InstallKeybox(const uint8_t* keybox, size_t keyBoxLength)
{
    LOGD(("%s entered", __FUNCTION__));

    if (drm_WVOemCrypto_InstallKeybox(keybox, keyBoxLength) != Drm_Success)
    {
        return OEMCrypto_ERROR_WRITE_KEYBOX;
    }

    return OEMCrypto_SUCCESS;
}

//WV v10
OEMCryptoResult OEMCrypto_LoadTestKeybox()
{
  OEMCryptoResult wvRc = OEMCrypto_SUCCESS;
  LOGD(("-- OEMCryptoResult OEMCrypto_LoadTestKeybox()\n"));

 /* if ((drm_WVOemCrypto_LoadTestKeybox((int*)&wvRc) != Drm_Success) || (wvRc !=0) )
    {
        return wvRc;
    }*/
  LOGE(("[OEMCrypto_LoadTestKeybox(): OEMCrypto_LoadTestKeybox  rc=%d]",wvRc));
    return OEMCrypto_SUCCESS;

}

OEMCryptoResult OEMCrypto_ForceDeleteUsageEntry(const uint8_t* pst,
                                                size_t pst_length)
{
    OEMCryptoResult wvRc = OEMCrypto_SUCCESS;

    if ((pst == NULL )|| (pst_length == 0))
    {
        LOGE(("[OEMCrypto_ForceDeleteUsageEntry(): invalid params.]"));
        return OEMCrypto_ERROR_INVALID_CONTEXT;
    }

    if (DRM_WVOemCrypto_ForceDeleteUsageEntry( pst, pst_length,(int*)&wvRc) != Drm_Success)
    {
        LOGE(("[%s(): call FAILED (%d)]", __FUNCTION__, wvRc));
    }

    return wvRc;
}

OEMCryptoResult OEMCrypto_LoadTestRSAKey()
{
    return OEMCrypto_ERROR_NOT_IMPLEMENTED;
}

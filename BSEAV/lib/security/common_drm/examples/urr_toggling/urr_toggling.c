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
#define LOG_NDEBUG 0

#include "nexus_platform.h"
#include "nexus_video_decoder.h"
#include "nexus_stc_channel.h"
#include "nexus_display.h"
#include "nexus_video_window.h"
#include "nexus_video_input.h"
#include "nexus_spdif_output.h"
#include "nexus_component_output.h"
#include "nexus_video_adj.h"
#include "nexus_playback.h"
#include "nexus_core_utils.h"
#include "nexus_sage.h"

#include "common_crypto.h"
#include "drm_prdy_http.h"
#include "drm_prdy.h"
#include "drm_prdy_types.h"
#include "drm_playback.h"

#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "bstd.h"
#include "bkni.h"
#include "bkni_multi.h"
#include "bmp4_util.h"
#include "bbase64.h"
#include "piff_parser.h"
#include "bfile_stdio.h"
#include "bpiff.h"

#include "nxclient.h"
#include "nexus_surface_client.h"

#define DEBUG_OUTPUT_CAPTURE    0

#include <sage_srai.h>

#define REPACK_VIDEO_PES_ID 0xE0
#define REPACK_AUDIO_PES_ID 0xC0

#define BOX_HEADER_SIZE (8)
#define BUF_SIZE (1024 * 1024 * 2) /* 2MB */

#define CALCULATE_PTS(t)        (((uint64_t)(t) / 10000LL) * 45LL)

BDBG_MODULE(urr_toggling);

#include "bpiff.c"
#include "piff_parser.c"

typedef struct app_ctx {
    FILE *fp_piff;
    uint32_t piff_filesize;

    uint8_t *pPayload;
    uint8_t *pOutBuf;

    size_t outBufSize;

    uint64_t last_video_fragment_time;
    uint64_t last_audio_fragment_time;

    DRM_Prdy_DecryptContext_t decryptor;
} app_ctx;

#if DEBUG_OUTPUT_CAPTURE
/* Input file pointer */
FILE *fp_vid;
FILE *fp_aud;
#endif

#ifdef TEE
static bool   bIsSecureStopEnabled = false;
#endif

/* stream type */
int vc1_stream = 0;
typedef app_ctx * app_ctx_t;
static int video_decode_hdr;

static int gui_init( NEXUS_SurfaceClientHandle surfaceClient );

static int piff_playback_dma_buffer(CommonCryptoHandle commonCryptoHandle, void *dst,
        void *src, size_t size, bool flush)
{
    NEXUS_DmaJobBlockSettings blkSettings;
    CommonCryptoJobSettings cryptoJobSettings;

    BDBG_MSG(("%s: from=%p, to=%p, size=%u", __FUNCTION__, src, dst, size));

    NEXUS_DmaJob_GetDefaultBlockSettings(&blkSettings);
    blkSettings.pSrcAddr = src;
    blkSettings.pDestAddr = dst;
    blkSettings.blockSize = size;
    blkSettings.resetCrypto = true;
    blkSettings.scatterGatherCryptoStart = true;
    blkSettings.scatterGatherCryptoEnd = true;

    if (flush) {
        /* Need to flush manually the source buffer (non secure heap). We need to flush manually as soon as we copy data into
           the secure heap. Setting blkSettings[ii].cached = true would also try to flush the destination address in the secure heap
           which is not accessible. This would cause the whole memory to be flushed at once. */
        NEXUS_FlushCache(blkSettings.pSrcAddr, blkSettings.blockSize);
        blkSettings.cached = false; /* Prevent the DMA from flushing the buffers later on */
    }

    CommonCrypto_GetDefaultJobSettings(&cryptoJobSettings);
    CommonCrypto_DmaXfer(commonCryptoHandle,  &cryptoJobSettings, &blkSettings, 1);

    if (flush) {
        /* Need to flush manually the source buffer (non secure heap). We need to flush manually as soon as we copy data into
           the secure heap. Setting blkSettings[ii].cached = true would also try to flush the destination address in the secure heap
           which is not accessible. This would cause the whole memory to be flushed at once. */
        NEXUS_FlushCache(blkSettings.pSrcAddr, blkSettings.blockSize);
    }

    return 0;
}

static int parse_esds_config(bmedia_adts_hdr *hdr, bmedia_info_aac *info_aac, size_t payload_size)
{
    bmedia_adts_header adts_header;

    bmedia_adts_header_init_aac(&adts_header, info_aac);
    bmedia_adts_hdr_init(hdr, &adts_header, payload_size);

    return 0;
}

static int parse_avcc_config(uint8_t *avcc_hdr, size_t *hdr_len, size_t *nalu_len,
        uint8_t *cfg_data, size_t cfg_data_size)
{
    bmedia_h264_meta meta;
    unsigned int i, sps_len, pps_len;
    uint8_t *data;
    uint8_t *dst;

    bmedia_read_h264_meta(&meta, cfg_data, cfg_data_size);

    *nalu_len = meta.nalu_len;

    data = (uint8_t *)meta.sps.data;
    dst = avcc_hdr;
    *hdr_len = 0;

    for(i=0; i < meta.sps.no; i++) {
        sps_len = (((uint16_t)data[0]) <<8) | data[1];
        data += 2;
        /* Add NAL */
        BKNI_Memcpy(dst, bpiff_nal, sizeof(bpiff_nal)); dst += sizeof(bpiff_nal);
        /* Add SPS */
        BKNI_Memcpy(dst, data, sps_len);
        dst += sps_len;
        data += sps_len;
        *hdr_len += (sizeof(bpiff_nal) + sps_len);
    }

    data = (uint8_t *)meta.pps.data;
    for(i=0; i < meta.pps.no; i++) {
        pps_len = (((uint16_t)data[0]) <<8) | data[1];
        data += 2;
        /* Add NAL */
        BKNI_Memcpy(dst, bpiff_nal, sizeof(bpiff_nal));
        dst += sizeof(bpiff_nal);
        /* Add PPS */
        BKNI_Memcpy(dst, data, pps_len);
        dst += pps_len;
        data += pps_len;
        *hdr_len += (sizeof(bpiff_nal) + pps_len);
    }
    return 0;
}

static int secure_process_fragment(CommonCryptoHandle commonCryptoHandle, app_ctx *app,
        piff_parse_frag_info *frag_info, size_t payload_size,
        void *decoder_data, size_t decoder_len,
        NEXUS_PlaypumpHandle playpump, BKNI_EventHandle event)
{
    int rc = 0;
    uint32_t i, j, bytes_processed;
    bpiff_drm_mp4_box_se_sample *pSample;
    uint8_t pes_header[BMEDIA_PES_HEADER_MAX_SIZE];
    size_t pes_header_len;
    bmedia_pes_info pes_info;
    uint64_t frag_duration;
    uint8_t *pOutBuf = app->pOutBuf;
    size_t decrypt_offset = 0;
    NEXUS_PlaypumpStatus playpumpStatus;
    size_t fragment_size = payload_size;
    void *playpumpBuffer;
    size_t bufferSize;
    size_t outSize = 0;
    uint8_t *out;
    DRM_Prdy_AES_CTR_Info_t aesCtrInfo;

    /* Obtain secure playpump buffer */
    NEXUS_Playpump_GetStatus(playpump, &playpumpStatus);
    fragment_size += 512;   /* Provide headroom for PES and SPS/PPS headers */
    BDBG_ASSERT(fragment_size <= playpumpStatus.fifoSize);
    for(;;) {
        NEXUS_Playpump_GetBuffer(playpump, &playpumpBuffer, &bufferSize);
        if(bufferSize >= fragment_size) {
            break;
        }
        if(bufferSize==0) {
            BKNI_WaitForEvent(event, 100);
            continue;
        }
        if((uint8_t *)playpumpBuffer >= (uint8_t *)playpumpStatus.bufferBase +
                (playpumpStatus.fifoSize - fragment_size)) {
            NEXUS_Playpump_WriteComplete(playpump, bufferSize, 0); /* skip buffer what wouldn't be big enough */
        }
    }

    BDBG_MSG(("%s: NEXUS_Playpump_GetBuffer return buffer %p, size %u",
              __FUNCTION__, playpumpBuffer, bufferSize));

    app->outBufSize = 0;
    bytes_processed = 0;
    if (frag_info->samples_enc->sample_count != 0) {
        /* Iterate through the samples within the fragment */
        for (i = 0; i < frag_info->samples_enc->sample_count; i++) {
            size_t numOfByteDecrypted = 0;
            size_t sampleSize = 0;

            pSample = &frag_info->samples_enc->samples[i];
            sampleSize = frag_info->sample_info[i].size;

            if (frag_info->trackType == BMP4_SAMPLE_ENCRYPTED_VIDEO) {
                if (!vc1_stream) {
                    /* H.264 Decoder configuration parsing */
                    uint8_t avcc_hdr[BPIFF_MAX_PPS_SPS];
                    size_t avcc_hdr_size;
                    size_t nalu_len = 0;

                    pOutBuf = app->pOutBuf;
                    app->outBufSize = 0;

                    parse_avcc_config(avcc_hdr, &avcc_hdr_size, &nalu_len, decoder_data, decoder_len);

                    bmedia_pes_info_init(&pes_info, REPACK_VIDEO_PES_ID);
                    frag_duration = app->last_video_fragment_time +
                        frag_info->sample_info[i].composition_time_offset;
                    app->last_video_fragment_time += frag_info->sample_info[i].duration;

                    pes_info.pts_valid = true;
                    pes_info.pts = CALCULATE_PTS(frag_duration);
                    if (video_decode_hdr == 0) {
                        pes_header_len = bmedia_pes_header_init(pes_header,
                                (sampleSize + avcc_hdr_size - nalu_len + sizeof(bpiff_nal)), &pes_info);
                    } else {
                        pes_header_len = bmedia_pes_header_init(pes_header,
                                (sampleSize - nalu_len + sizeof(bpiff_nal)), &pes_info);
                    }

                    /* Copy PES header and SPS/PPS to intermediate buffer */
                    BKNI_Memcpy(pOutBuf, &pes_header, pes_header_len);
                    pOutBuf += pes_header_len;
                    app->outBufSize += pes_header_len;

                    /* Only add header once */
                    if (video_decode_hdr == 0) {
                        BKNI_Memcpy(pOutBuf, avcc_hdr, avcc_hdr_size);
                        pOutBuf += avcc_hdr_size;
                        app->outBufSize += avcc_hdr_size;
                        video_decode_hdr = 1;
                    }

                    decrypt_offset = nalu_len;

                    piff_playback_dma_buffer(commonCryptoHandle, (uint8_t *)playpumpBuffer + outSize,
                            app->pOutBuf, app->outBufSize, true);
                    outSize += app->outBufSize;
                }
            } else if (frag_info->trackType == BMP4_SAMPLE_ENCRYPTED_AUDIO) {
                if (!vc1_stream) {
                    /* AAC information parsing */
                    bmedia_adts_hdr hdr;
                    bmedia_info_aac *info_aac = (bmedia_info_aac *)decoder_data;

                    pOutBuf = app->pOutBuf;
                    app->outBufSize = 0;

                    parse_esds_config(&hdr, info_aac, sampleSize);

                    bmedia_pes_info_init(&pes_info, REPACK_AUDIO_PES_ID);
                    frag_duration = app->last_audio_fragment_time +
                        frag_info->sample_info[i].composition_time_offset;
                    app->last_audio_fragment_time += frag_info->sample_info[i].duration;

                    pes_info.pts_valid = true;
                    pes_info.pts = CALCULATE_PTS(frag_duration);

                    pes_header_len = bmedia_pes_header_init(pes_header,
                            (sampleSize + BMEDIA_ADTS_HEADER_SIZE), &pes_info);
                    BKNI_Memcpy(pOutBuf, &pes_header, pes_header_len);
                    BKNI_Memcpy(pOutBuf + pes_header_len, &hdr.adts, BMEDIA_ADTS_HEADER_SIZE);

                    pOutBuf += pes_header_len + BMEDIA_ADTS_HEADER_SIZE;
                    app->outBufSize += pes_header_len + BMEDIA_ADTS_HEADER_SIZE;

                    decrypt_offset = 0;

                    piff_playback_dma_buffer(commonCryptoHandle, (uint8_t *)playpumpBuffer + outSize,
                            app->pOutBuf, app->outBufSize, true);
                    outSize += app->outBufSize;
                }
            } else {
                BDBG_WRN(("%s Unsupported track type %d detected", __FUNCTION__, frag_info->trackType));
                return -1;
            }

            /* Process and decrypt samples */

            BKNI_Memcpy( &aesCtrInfo.qwInitializationVector,&pSample->iv[8],8);
            aesCtrInfo.qwBlockOffset = 0;
            aesCtrInfo.bByteOffset = 0;
            out = (uint8_t *)playpumpBuffer + outSize;

            if(frag_info->samples_enc->flags & 0x000002) {
                uint64_t     qwOffset = 0;

                for(j = 0; j < pSample->nbOfEntries; j++) {
                    uint32_t num_clear = pSample->entries[j].bytesOfClearData;
                    uint32_t num_enc = pSample->entries[j].bytesOfEncData;
                    int blk_idx = 0;
                    int k;
                    NEXUS_DmaJobBlockSettings blkSettings[2];
                    CommonCryptoJobSettings cryptoJobSettings;

                    /* Skip over clear units by offset amount */
                    BDBG_ASSERT(num_clear >= decrypt_offset);
                    batom_cursor_skip((batom_cursor *)&frag_info->cursor, decrypt_offset);

                    if (!vc1_stream) {
                        /* Append NAL Header */
                        BKNI_Memcpy(app->pOutBuf, bpiff_nal, sizeof(bpiff_nal));
                        NEXUS_DmaJob_GetDefaultBlockSettings(&blkSettings[blk_idx]);
                        blkSettings[blk_idx].pSrcAddr = app->pOutBuf;
                        blkSettings[blk_idx].pDestAddr = out;
                        blkSettings[blk_idx].blockSize = sizeof(bpiff_nal);
                        blkSettings[blk_idx].resetCrypto = true;
                        blkSettings[blk_idx].scatterGatherCryptoStart = true;
                        blkSettings[blk_idx].scatterGatherCryptoEnd = false;
                        blk_idx++;

                        out += sizeof(bpiff_nal);
                        outSize += sizeof(bpiff_nal);
                    }

                    NEXUS_DmaJob_GetDefaultBlockSettings(&blkSettings[blk_idx]);
                    blkSettings[blk_idx].pSrcAddr = (uint8_t *)frag_info->cursor.cursor;
                    blkSettings[blk_idx].pDestAddr = out;
                    blkSettings[blk_idx].blockSize = (num_enc + num_clear - decrypt_offset);
                    blkSettings[blk_idx].resetCrypto = blk_idx ? false : true;
                    blkSettings[blk_idx].scatterGatherCryptoStart = blk_idx ? false : true;
                    blkSettings[blk_idx].scatterGatherCryptoEnd = true;
                    blk_idx++;

                    for (k = 0; k < blk_idx; k++ ) {
                        NEXUS_FlushCache(blkSettings[k].pSrcAddr, blkSettings[k].blockSize);
                        blkSettings[k].cached = false; /* Prevent the DMA from flushing the buffers later on */
                    }

                    CommonCrypto_GetDefaultJobSettings(&cryptoJobSettings);
                    CommonCrypto_DmaXfer(commonCryptoHandle,  &cryptoJobSettings, blkSettings, blk_idx);

                    for (k = 0; k < blk_idx; k++ ) {
                        NEXUS_FlushCache(blkSettings[k].pSrcAddr, blkSettings[k].blockSize);
                    }

                    outSize += (num_enc + num_clear - decrypt_offset);

                    /* Skip over remaining clear units */
                    out += (num_clear - decrypt_offset);
                    batom_cursor_skip((batom_cursor *)&frag_info->cursor, (num_clear - decrypt_offset));

                    aesCtrInfo.qwBlockOffset = qwOffset / 16 ;
                    aesCtrInfo.bByteOffset = qwOffset % 16 ;

                    BDBG_MSG(("%s:%d: DRM_Prdy_Reader_Decrypt(..., ..., %p, %u)",
                              __FUNCTION__, __LINE__, out, num_enc));
                    if(DRM_Prdy_Reader_Decrypt(
                                &app->decryptor,
                                &aesCtrInfo,
                                (uint8_t *)out,
                                num_enc ) != DRM_Prdy_ok) {
                        BDBG_ERR(("%s Reader_Decrypt failed - %d", __FUNCTION__, __LINE__));
                        return -1;
                    }

                    out += num_enc;
                    batom_cursor_skip((batom_cursor *)&frag_info->cursor,num_enc);
                    qwOffset = num_enc;
                    numOfByteDecrypted  += (num_clear - decrypt_offset + num_enc);

                    if(numOfByteDecrypted > sampleSize) {
                        BDBG_WRN(("Wrong buffer size is detected while decrypting the ciphertext, bytes processed %d, sample size to decrypt %d",
                                    numOfByteDecrypted, sampleSize));
                        return -1;
                    }
                }
            } else {
                piff_playback_dma_buffer(commonCryptoHandle, out, (uint8_t *)frag_info->cursor.cursor,
                        sampleSize, true);
                outSize += sampleSize;

                BDBG_MSG(("%s:%d: DRM_Prdy_Reader_Decrypt(..., ..., %p, %u)",
                          __FUNCTION__, __LINE__, out, sampleSize));
                if(DRM_Prdy_Reader_Decrypt(
                            &app->decryptor,
                            &aesCtrInfo,
                            (uint8_t *)out,
                            sampleSize ) != DRM_Prdy_ok) {
                    BDBG_ERR(("%s Reader_Decrypt failed - %d", __FUNCTION__, __LINE__));
                    return -1;
                }

                batom_cursor_skip((batom_cursor *)&frag_info->cursor, sampleSize);
                numOfByteDecrypted = sampleSize;
            }

            bytes_processed += numOfByteDecrypted + decrypt_offset;
        }
        BDBG_MSG(("%s: NEXUS_Playpump_WriteComplete buffer %p, size %u",
                  __FUNCTION__, playpumpBuffer, bufferSize));
        NEXUS_Playpump_WriteComplete(playpump, 0, outSize);
    }

    if(bytes_processed != payload_size) {
        BDBG_WRN(("%s the number of bytes %d decrypted doesn't match the actual size %d of the payload, return failure...%d",__FUNCTION__,
                    bytes_processed, payload_size, __LINE__));
        rc = -1;
    }

    return rc;
}

static void play_callback(void *context, int param)
{
    BSTD_UNUSED(param);
    BKNI_SetEvent((BKNI_EventHandle)context);
}

static void
wait_for_drain(NEXUS_PlaypumpHandle videoPlaypump, NEXUS_SimpleVideoDecoderHandle videoDecoder,
               NEXUS_PlaypumpHandle audioPlaypump, NEXUS_SimpleAudioDecoderHandle audioDecoder)
{
    NEXUS_Error rc;
    NEXUS_PlaypumpStatus playpumpStatus;

    for(;;) {
        rc=NEXUS_Playpump_GetStatus(videoPlaypump, &playpumpStatus);
        if(rc!=NEXUS_SUCCESS)
            break;

        if(playpumpStatus.fifoDepth==0) {
            break;
        }
        BKNI_Sleep(100);
    }
    for(;;) {
        rc=NEXUS_Playpump_GetStatus(audioPlaypump, &playpumpStatus);
        if(rc!=NEXUS_SUCCESS)
            break;

        if(playpumpStatus.fifoDepth==0)
            break;

        BKNI_Sleep(100);
    }

    if(videoDecoder) {
        for(;;) {
            NEXUS_VideoDecoderStatus decoderStatus;
            rc=NEXUS_SimpleVideoDecoder_GetStatus(videoDecoder, &decoderStatus);
            if(rc!=NEXUS_SUCCESS)
                break;

            if(decoderStatus.queueDepth==0)
                break;

            BKNI_Sleep(100);
        }
    }
    if(audioDecoder) {
        for(;;) {
            NEXUS_AudioDecoderStatus decoderStatus;
            rc=NEXUS_SimpleAudioDecoder_GetStatus(audioDecoder, &decoderStatus);
            if(rc!=NEXUS_SUCCESS)
                break;

            if(decoderStatus.queuedFrames < 4)
                break;

            BKNI_Sleep(100);
        }
    }
    return;
}

static int complete_play_fragments(
        NEXUS_SimpleAudioDecoderHandle audioDecoder,
        NEXUS_SimpleVideoDecoderHandle videoDecoder,
        NEXUS_PlaypumpHandle videoPlaypump,
        NEXUS_PlaypumpHandle audioPlaypump,
        NEXUS_DisplayHandle display,
        NEXUS_PidChannelHandle audioPidChannel,
        NEXUS_PidChannelHandle videoPidChannel,
        NEXUS_VideoWindowHandle window,
        BKNI_EventHandle event)
{
    BSTD_UNUSED(window);
    BSTD_UNUSED(display);
    BSTD_UNUSED(event);
    wait_for_drain(videoPlaypump, videoDecoder, audioPlaypump, audioDecoder);

    if (event != NULL) BKNI_DestroyEvent(event);

    if (videoDecoder) {
        NEXUS_SimpleVideoDecoder_Stop(videoDecoder);
        NEXUS_Playpump_ClosePidChannel(videoPlaypump, videoPidChannel);
        NEXUS_Playpump_Stop(videoPlaypump);
        NEXUS_StopCallbacks(videoPlaypump);
    }
    if (audioDecoder) {
        NEXUS_SimpleAudioDecoder_Stop(audioDecoder);
        NEXUS_Playpump_ClosePidChannel(audioPlaypump, audioPidChannel);
        NEXUS_Playpump_Stop(audioPlaypump);
        NEXUS_StopCallbacks(audioPlaypump);
    }

    NEXUS_Playpump_Close(videoPlaypump);
    NEXUS_Playpump_Close(audioPlaypump);

    return 0;
}

void playback_piff( NEXUS_SimpleVideoDecoderHandle videoDecoder,
                    NEXUS_SimpleAudioDecoderHandle audioDecoder,
                    DRM_Prdy_Handle_t drm_context,
                    char *piff_file)
{

    uint8_t *pSecureVideoHeapBuffer = NULL;
    uint8_t *pSecureAudioHeapBuffer = NULL;
    NEXUS_ClientConfiguration clientConfig;
    NEXUS_MemoryAllocationSettings memSettings;
    NEXUS_SimpleStcChannelHandle stcChannel;
    NEXUS_SimpleVideoDecoderStartSettings videoProgram;
    NEXUS_SimpleAudioDecoderStartSettings audioProgram;
    NEXUS_PlaypumpOpenSettings videoplaypumpOpenSettings;
    NEXUS_PlaypumpOpenSettings audioplaypumpOpenSettings;
    NEXUS_SimpleStcChannelSettings stcSettings;
    NEXUS_PlaypumpSettings playpumpSettings;
    NEXUS_Error rc;
    CommonCryptoHandle commonCryptoHandle = NULL;
    CommonCryptoSettings  cmnCryptoSettings;

    NEXUS_DisplayHandle display = NULL;
    NEXUS_PidChannelHandle videoPidChannel = NULL;
    BKNI_EventHandle event = NULL;
    NEXUS_PlaypumpHandle videoPlaypump = NULL;
    NEXUS_PlaypumpHandle audioPlaypump = NULL;

    NEXUS_PidChannelHandle audioPidChannel = NULL;

    app_ctx app;
    bool moovBoxParsed = false;

    uint8_t resp_buffer[64*1024];
    char *pCh_url = NULL;
    char *pCh_data = NULL;
    uint8_t *pResponse = resp_buffer;
    size_t respLen;
    size_t respOffset;
    size_t urlLen;
    size_t chLen;
    piff_parser_handle_t piff_handle;
    bfile_io_read_t fd;
    uint8_t *pssh_data;
    uint32_t pssh_len;
    NEXUS_PlaypumpOpenPidChannelSettings video_pid_settings;

    BDBG_MSG(("%s - %d\n", __FUNCTION__, __LINE__));
    if(piff_file == NULL ) {
        goto clean_exit;
    }

    BDBG_MSG(("PIFF file: %s\n",piff_file));
    fflush(stdout);

    BKNI_Memset(&app, 0, sizeof( app_ctx));
    app.last_video_fragment_time = 0;
    app.last_audio_fragment_time = 0;

    app.fp_piff = fopen(piff_file, "rb");
    if(app.fp_piff == NULL){
        fprintf(stderr,"failed to open %s\n", piff_file);
        goto clean_exit;
    }

    fd = bfile_stdio_read_attach(app.fp_piff);

    piff_handle = piff_parser_create(fd);
    if (!piff_handle) {
        BDBG_ERR(("Unable to create PIFF parser context"));
        goto clean_exit;
    }

    fseek(app.fp_piff, 0, SEEK_END);
    app.piff_filesize = ftell(app.fp_piff);
    fseek(app.fp_piff, 0, SEEK_SET);

    if( drm_context == NULL)
    {
       BDBG_ERR(("drm_context is NULL, quitting...."));
       goto clean_exit ;
    }

    CommonCrypto_GetDefaultSettings(&cmnCryptoSettings);
    commonCryptoHandle = CommonCrypto_Open(&cmnCryptoSettings);

    NEXUS_Platform_GetClientConfiguration(&clientConfig);
    NEXUS_Memory_GetDefaultAllocationSettings(&memSettings);
    memSettings.heap = clientConfig.heap[1]; /* heap 1 is the eFull heap for the nxclient. */

    /* Show heaps info */
    {
        int g;
        BDBG_MSG(("NxClient Heaps Info -----------------"));
        for (g = NXCLIENT_DEFAULT_HEAP; g <= NXCLIENT_SECONDARY_GRAPHICS_HEAP; g++)
        {
            NEXUS_MemoryStatus status;
            NEXUS_Heap_GetStatus(clientConfig.heap[g], &status);

            BDBG_MSG(("Heap[%d]: memoryType=%u, heapType=%u, offset=%u, addr=%p, size=%u",
                      g, status.memoryType, status.heapType, (uint32_t)status.offset, status.addr, status.size));
        }
        BDBG_MSG(("-------------------------------------"));
    }

    app.pPayload = NULL;
    if( NEXUS_Memory_Allocate(BUF_SIZE, &memSettings, (void *)&app.pPayload) !=  NEXUS_SUCCESS) {
        fprintf(stderr,"NEXUS_Memory_Allocate failed");
        goto clean_up;
    }

    app.pOutBuf = NULL;
    if( NEXUS_Memory_Allocate(BUF_SIZE, &memSettings, (void *)&app.pOutBuf) !=  NEXUS_SUCCESS) {
        fprintf(stderr,"NEXUS_Memory_Allocate failed");
        goto clean_up;
    }

    /* Perform parsing of the movie information */
    moovBoxParsed = piff_parser_scan_movie_info(piff_handle);

    if(!moovBoxParsed) {
        BDBG_ERR(("Failed to parse moov box, can't continue..."));
        goto clean_up;
    }

    BDBG_MSG(("Successfully parsed the moov box, continue...\n\n"));

    /* EXTRACT AND PLAYBACK THE MDAT */

    NEXUS_Playpump_GetDefaultOpenSettings(&videoplaypumpOpenSettings);
    videoplaypumpOpenSettings.fifoSize *= 7;
    videoplaypumpOpenSettings.numDescriptors *= 7;

    videoplaypumpOpenSettings.dataNotCpuAccessible = true;
    pSecureVideoHeapBuffer = SRAI_Memory_Allocate(videoplaypumpOpenSettings.fifoSize,
            SRAI_MemoryType_SagePrivate);
    if ( pSecureVideoHeapBuffer == NULL ) {
        BDBG_ERR((" Failed to allocate from Secure Video heap"));
        BDBG_ASSERT( false );
    }
    videoplaypumpOpenSettings.memory = NEXUS_MemoryBlock_FromAddress(pSecureVideoHeapBuffer);

    videoPlaypump = NEXUS_Playpump_Open(NEXUS_ANY_ID, &videoplaypumpOpenSettings);
    if (!videoPlaypump) {
        BDBG_ERR(("@@@ Video Playpump Open FAILED----"));
        goto clean_up;
    }
    BDBG_ASSERT(videoPlaypump != NULL);

    NEXUS_Playpump_GetDefaultOpenSettings(&audioplaypumpOpenSettings);
    audioplaypumpOpenSettings.dataNotCpuAccessible = true;
    pSecureAudioHeapBuffer = SRAI_Memory_Allocate(audioplaypumpOpenSettings.fifoSize,
            SRAI_MemoryType_SagePrivate);
    if ( pSecureAudioHeapBuffer == NULL ) {
        BDBG_ERR((" Failed to allocate from Secure Audio heap"));
        goto clean_up;
    }
    BDBG_ASSERT( pSecureAudioHeapBuffer != NULL );
    audioplaypumpOpenSettings.memory = NEXUS_MemoryBlock_FromAddress(pSecureAudioHeapBuffer);

    audioPlaypump = NEXUS_Playpump_Open(NEXUS_ANY_ID, &audioplaypumpOpenSettings);
    if (!audioPlaypump) {
        BDBG_ERR(("@@@ Video Playpump Open FAILED----"));
        goto clean_up;
    }
    BDBG_ASSERT(audioPlaypump != NULL);

    stcChannel = NEXUS_SimpleStcChannel_Create(NULL);
    NEXUS_SimpleStcChannel_GetSettings(stcChannel, &stcSettings);
    stcSettings.mode = NEXUS_StcChannelMode_eAuto;
    rc = NEXUS_SimpleStcChannel_SetSettings(stcChannel, &stcSettings);
    if (rc) {
       BDBG_WRN(("@@@ Stc Set FAILED ---------------"));
    }

    BKNI_CreateEvent(&event);

    NEXUS_Playpump_GetSettings(videoPlaypump, &playpumpSettings);
    playpumpSettings.dataCallback.callback = play_callback;
    playpumpSettings.dataCallback.context = event;
    playpumpSettings.transportType = NEXUS_TransportType_eMpeg2Pes;
    NEXUS_Playpump_SetSettings(videoPlaypump, &playpumpSettings);

    NEXUS_Playpump_GetSettings(audioPlaypump, &playpumpSettings);
    playpumpSettings.dataCallback.callback = play_callback;
    playpumpSettings.dataCallback.context = event;
    playpumpSettings.transportType = NEXUS_TransportType_eMpeg2Pes;
    NEXUS_Playpump_SetSettings(audioPlaypump, &playpumpSettings);

    /* already connected in main */
    NEXUS_SimpleAudioDecoder_GetDefaultStartSettings(&audioProgram);
    NEXUS_SimpleVideoDecoder_GetDefaultStartSettings(&videoProgram);

    NEXUS_Playpump_Start(videoPlaypump);
    NEXUS_Playpump_Start(audioPlaypump);

    NEXUS_Playpump_GetDefaultOpenPidChannelSettings(&video_pid_settings);
    video_pid_settings.pidType = NEXUS_PidType_eVideo;

    videoPidChannel = NEXUS_Playpump_OpenPidChannel(videoPlaypump, REPACK_VIDEO_PES_ID, &video_pid_settings);
    NEXUS_SetPidChannelBypassKeyslot(videoPidChannel, NEXUS_BypassKeySlot_eGR2R);

    if ( !videoPidChannel )
      BDBG_WRN(("@@@ videoPidChannel NULL"));
    else
      BDBG_WRN(("@@@ videoPidChannel OK"));

    audioPidChannel = NEXUS_Playpump_OpenPidChannel(audioPlaypump, REPACK_AUDIO_PES_ID, NULL);
    NEXUS_SetPidChannelBypassKeyslot(audioPidChannel, NEXUS_BypassKeySlot_eGR2R);

    if ( !audioPidChannel )
      BDBG_WRN(("@@@ audioPidChannel NULL"));
    else
      BDBG_WRN(("@@@ audioPidChannel OK"));

    NEXUS_SimpleAudioDecoder_GetDefaultStartSettings(&audioProgram);
    NEXUS_SimpleVideoDecoder_GetDefaultStartSettings(&videoProgram);

    if ( vc1_stream ) {
       BDBG_MSG(("@@@ set video audio program for vc1"));
       videoProgram.settings.codec = NEXUS_VideoCodec_eVc1;
       audioProgram.primary.codec = NEXUS_AudioCodec_eWmaPro;
    } else {
       BDBG_MSG(("@@@ set video audio program for h264"));
       videoProgram.settings.codec = NEXUS_VideoCodec_eH264;
       audioProgram.primary.codec = NEXUS_AudioCodec_eAacAdts;
    }

    videoProgram.settings.pidChannel = videoPidChannel;
    NEXUS_SimpleVideoDecoder_Start(videoDecoder, &videoProgram);

    audioProgram.primary.pidChannel = audioPidChannel;
    NEXUS_SimpleAudioDecoder_Start(audioDecoder, &audioProgram);

    if (videoProgram.settings.pidChannel) {
        BDBG_WRN(("@@@ set stc channel video"));
        NEXUS_SimpleVideoDecoder_SetStcChannel(videoDecoder, stcChannel);
    }

    if (audioProgram.primary.pidChannel) {
        BDBG_WRN(("@@@ set stc channel audio"));
        NEXUS_SimpleAudioDecoder_SetStcChannel(audioDecoder, stcChannel);
    }

    /***********************
     * now ready to decrypt
     ***********************/
    pssh_data = piff_parser_get_pssh(piff_handle, &pssh_len);
    if (!pssh_data) {
        BDBG_ERR(("Failed to obtain pssh data"));
        goto clean_exit;
    }

    if( DRM_Prdy_Content_SetProperty(drm_context,
                DRM_Prdy_contentSetProperty_eAutoDetectHeader,
                pssh_data, pssh_len) != DRM_Prdy_ok) {
        BDBG_ERR(("Failed to SetProperty for the KID, exiting..."));
        goto clean_exit;
    }

    if( DRM_Prdy_Get_Buffer_Size( drm_context, DRM_Prdy_getBuffer_licenseAcq_challenge,
                NULL, 0, &urlLen, &chLen) != DRM_Prdy_ok ) {
        BDBG_ERR(("DRM_Prdy_Get_Buffer_Size() failed, exiting"));
        goto clean_exit;
    }

    pCh_url = BKNI_Malloc(urlLen);

    if(pCh_url == NULL) {
        BDBG_ERR(("BKNI_Malloc(urlent) failed, exiting..."));
        goto clean_exit;
    }

    pCh_data = BKNI_Malloc(chLen);
    if(pCh_data == NULL) {
        BDBG_ERR(("BKNI_Malloc(chLen) failed, exiting..."));
        goto clean_exit;
    }

    if(DRM_Prdy_LicenseAcq_GenerateChallenge(drm_context, NULL,
                0, pCh_url, &urlLen, pCh_data, &chLen) != DRM_Prdy_ok ) {
        BDBG_ERR(("DRM_Prdy_License_GenerateChallenge() failed, exiting"));
        goto clean_exit;
    }

    pCh_data[ chLen ] = 0;

    if(DRM_Prdy_http_client_license_post_soap(pCh_url, pCh_data, 1,
        150, (unsigned char **)&pResponse,64*1024, &respOffset, &respLen) != 0) {
        BDBG_ERR(("DRM_Prdy_http_client_license_post_soap() failed, exiting"));
        goto clean_exit;
    }

#ifdef TEE
  if (bIsSecureStopEnabled) {
    uint8_t   tmpSessionIdBuf[16];
    if( DRM_Prdy_LicenseAcq_ProcessResponseEx( drm_context,
                         (char *)&pResponse[respOffset],
                         respLen, tmpSessionIdBuf, NULL) != DRM_Prdy_ok )
    {
      BDBG_ERR(("DRM_Prdy_LicenseAcq_ProcessResponseEx() failed with SessionID buffer, exiting"));
      goto clean_exit;
    }
  }
  else {
    if( DRM_Prdy_LicenseAcq_ProcessResponseEx(drm_context, (char *)&pResponse[respOffset],
          respLen, NULL, NULL) != DRM_Prdy_ok ) {
      BDBG_ERR(("DRM_Prdy_LicenseAcq_ProcessResponseEx() failed, exiting"));
      goto clean_exit;
    }
  }
#else
    if( DRM_Prdy_LicenseAcq_ProcessResponse(drm_context, (char *)&pResponse[respOffset],
                respLen, NULL) != DRM_Prdy_ok ) {
        BDBG_ERR(("DRM_Prdy_LicenseAcq_ProcessResponse() failed, exiting"));
        goto clean_exit;
    }
#endif

    if( DRM_Prdy_Reader_Bind( drm_context,
                &app.decryptor)!= DRM_Prdy_ok ) {
        BDBG_ERR(("Failed to Bind the license, the license may not exist. Exiting..."));
        goto clean_exit;
    }

    if( DRM_Prdy_Reader_Commit(drm_context) != DRM_Prdy_ok ) {
        BDBG_ERR(("Failed to Commit the license after Reader_Bind, exiting..."));
        goto clean_exit;
    }

    /* now go back to the begining and get all the moof boxes */
    fseek(app.fp_piff, 0, SEEK_END);
    app.piff_filesize = ftell(app.fp_piff);
    fseek(app.fp_piff, 0, SEEK_SET);

    video_decode_hdr = 0;

    /* Start parsing the the file to look for MOOFs and MDATs */
    while(!feof(app.fp_piff))
    {
        piff_parse_frag_info frag_info;
        void *decoder_data;
        size_t decoder_len;

        if (!piff_parser_scan_movie_fragment(piff_handle, &frag_info, app.pPayload, BUF_SIZE)) {
            if (feof(app.fp_piff)) {
                BDBG_WRN(("Reached EOF"));
                break;
            } else {
                BDBG_ERR(("Unable to parse movie fragment"));
                goto clean_up;
            }
        }
        decoder_data = piff_parser_get_dec_data(piff_handle, &decoder_len, frag_info.trackId);


        if (frag_info.trackType == BMP4_SAMPLE_ENCRYPTED_VIDEO) {
            secure_process_fragment(commonCryptoHandle, &app, &frag_info, (frag_info.mdat_size - BOX_HEADER_SIZE),
                    decoder_data, decoder_len, videoPlaypump, event);

        } else if (frag_info.trackType == BMP4_SAMPLE_ENCRYPTED_AUDIO) {
            secure_process_fragment(commonCryptoHandle, &app, &frag_info, (frag_info.mdat_size - BOX_HEADER_SIZE),
                    decoder_data, decoder_len, audioPlaypump, event);
        }
    } /* while */

    complete_play_fragments(audioDecoder, videoDecoder, videoPlaypump,
            audioPlaypump, display, audioPidChannel, videoPidChannel, NULL, event);

clean_up:
    if(commonCryptoHandle) CommonCrypto_Close(commonCryptoHandle);
    if(pSecureVideoHeapBuffer) SRAI_Memory_Free(pSecureVideoHeapBuffer);
    if(pSecureAudioHeapBuffer) SRAI_Memory_Free(pSecureAudioHeapBuffer);
    if(app.decryptor.pDecrypt != NULL) DRM_Prdy_Reader_Close( &app.decryptor);
    if(app.pPayload) NEXUS_Memory_Free(app.pPayload);
    if(app.pOutBuf) NEXUS_Memory_Free(app.pOutBuf);

    if(piff_handle != NULL) piff_parser_destroy(piff_handle);

    bfile_stdio_read_detach(fd);
    if(app.fp_piff) fclose(app.fp_piff);

    if(pCh_url != NULL) BKNI_Free(pCh_url);
    if(pCh_data != NULL) BKNI_Free(pCh_data);

clean_exit:
    return;
}

#ifdef TEE
#define MAX_TIME_CHALLENGE_RESPONSE_LENGTH (1024*5)
#define MAX_URL_LENGTH (512)
int initSecureClock( DRM_Prdy_Handle_t drm)
{
    int                   rc = 0;
    uint8_t              *timeChResp = NULL;
    char                 *timeChURL = NULL;
    wchar_t              *pTimeURL=NULL;
    uint8_t              *timeCh_data=NULL;
    char                  timeURL_cstr[256] = {0};
    uint32_t              timeURL_len=0;
    uint32_t              timeCh_len=0;
    bool                  redirect = true;
    int32_t               petRC=0;
    uint32_t              petRespCode = 0;
    uint32_t              startOffset;
    uint32_t              length;
    uint32_t              post_ret;
    NEXUS_MemoryAllocationSettings allocSettings;

    if( DRM_Prdy_SecureClock_GenerateChallenge(drm,NULL,&timeURL_len,NULL,&timeCh_len) != DRM_Prdy_buffer_size)
    {
       BDBG_ERR(("DRM_Prdy_SecureClock_GenerateChallenge Failed, quitting....\n",__LINE__));
       return 0;
    }

    rc = NEXUS_Memory_Allocate(timeURL_len*sizeof(wchar_t), NULL, (void **)(&pTimeURL));
    if(rc != NEXUS_SUCCESS)
    {
        BDBG_ERR(("%d NEXUS_Memory_Allocate failed for the Time server URL buffer, rc = %d\n",__LINE__, rc));
        goto clean_exit;
    }

    rc = NEXUS_Memory_Allocate(timeCh_len+1, NULL, (void **)(&timeCh_data));
    if(rc != NEXUS_SUCCESS)
    {
        BDBG_ERR(("NEXUS_Memory_Allocate failed for the time challenge buffer, rc = %d\n",__LINE__, rc));
        goto clean_exit;
    }

    BKNI_Memset(pTimeURL, 0, timeURL_len);
    BKNI_Memset(timeCh_data, 0, timeCh_len+1);

    if( DRM_Prdy_SecureClock_GenerateChallenge(drm,pTimeURL,&timeURL_len,timeCh_data,&timeCh_len) != DRM_Prdy_ok)
    {
        BDBG_ERR(("%d DRM_Prdy_SecureClock_GenerateChallenge failed.\n",__LINE__));
        goto clean_exit;
    }

    timeURL_cstr[timeURL_len] = 0; /* null terminator */
    if( !DRM_Prdy_convertWStringToCString( pTimeURL, timeURL_cstr, timeURL_len))
    {
        BDBG_ERR(("%d DRM_Prdy_convertWStringToCString failed to convert URL from wchar to char *, can't procceed time challenge.\n",__LINE__));
        goto clean_exit;
    }

    timeCh_data[timeCh_len] = 0;

    NEXUS_Memory_GetDefaultAllocationSettings(&allocSettings);
    rc = NEXUS_Memory_Allocate(MAX_URL_LENGTH, &allocSettings, (void **)(&timeChURL ));
    if(rc != NEXUS_SUCCESS)
    {
        BDBG_ERR(("NEXUS_Memory_Allocate failed for time challenge response buffer, rc = %d\n",__LINE__, rc));
        goto clean_exit;
    }

    do
    {
           redirect = false;

           /* send the petition request to Microsoft with HTTP GET */
           petRC = DRM_Prdy_http_client_get_petition( timeURL_cstr,
                                                      &petRespCode,
                                                      (char**)&timeChURL);
           if( petRC != 0)
           {
               BDBG_ERR(("%d Secure Clock Petition request failed, rc = %d\n",__LINE__, petRC));
               rc = petRC;
               goto clean_exit;
           }

           /* we need to check if the Pettion responded with redirection */

           if( petRespCode == 200)
           {
               redirect = false;
           }
           else if( petRespCode == 302 || petRespCode == 301)
           {
               char * isHttps = NULL;

               redirect = true;

               memset(timeURL_cstr,0,timeURL_len);

               /* check if the URL is "https" */
               isHttps = strstr(timeChURL,"https");
               if( isHttps )
               {
                   strcpy(timeURL_cstr,"http");
                   strcpy(timeURL_cstr+4,isHttps+5);
               }
               else
               {
                   strcpy(timeURL_cstr,timeChURL);
               }

               memset(timeChURL,0,MAX_URL_LENGTH);
           }
           else
           {
               BDBG_ERR(("%d Secure Clock Petition responded with unsupported result, rc = %d, can't get the tiem challenge URL\n",__LINE__, petRespCode));
               rc = -1;
               goto clean_exit;
           }
    } while (redirect);


    NEXUS_Memory_GetDefaultAllocationSettings(&allocSettings);
    rc = NEXUS_Memory_Allocate(MAX_TIME_CHALLENGE_RESPONSE_LENGTH, &allocSettings, (void **)(&timeChResp ));
    if(rc != NEXUS_SUCCESS)
    {
        BDBG_ERR(("%d NEXUS_Memory_Allocate failed for time challenge response buffer, rc = %d\n",__LINE__, rc));
        goto clean_exit;
    }

    BKNI_Memset(timeChResp, 0, MAX_TIME_CHALLENGE_RESPONSE_LENGTH);
    post_ret = DRM_Prdy_http_client_time_challenge_post(timeChURL,
                                                        (char *)timeCh_data,
                                                        1,
                                                        150,
                                                        (unsigned char**)&(timeChResp),
							1024*5,
                                                        &startOffset,
                                                        &length);
    if( post_ret != 0)
    {
        BDBG_ERR(("%d Secure Clock Challenge request failed, rc = %d\n",__LINE__, post_ret));
        rc = post_ret;
        goto clean_exit;
    }

    if( DRM_Prdy_SecureClock_ProcessResponse( drm, (uint8_t *) timeChResp, length) != DRM_Prdy_ok)
    {
        BDBG_ERR(("%d Secure Clock Process Challenge response failed\n",__LINE__));
        rc = -1;
        goto clean_exit;
    }

    BDBG_LOG(("%d Initialized Playready Secure Clock success.",__LINE__));

    /* NOW testing the system time */

clean_exit:

    if( timeChResp   != NULL)
        NEXUS_Memory_Free(timeChResp );

    if( timeChURL    != NULL)
        NEXUS_Memory_Free(timeChURL  );

    if( pTimeURL  != NULL)
        NEXUS_Memory_Free(pTimeURL );

    if( timeCh_data  != NULL)
        NEXUS_Memory_Free(timeCh_data );

    return rc;
}
#endif

static void setHeapsSecure(bool markSecure)
{
    NEXUS_PlatformConfiguration platformConfig;
    int i;
    bool secure, picture;
    NEXUS_HeapRuntimeSettings heapSettings;
    NEXUS_MemoryStatus status;
    NEXUS_Error rc;

    NEXUS_Platform_GetConfiguration(&platformConfig);
    for (i=0;i<NEXUS_MAX_HEAPS;i++)
    {
        if(!platformConfig.heap[i])
            continue;

        rc=NEXUS_Heap_GetStatus(platformConfig.heap[i], &status);
        if(rc)
            continue;

        secure=(status.memoryType & NEXUS_MEMORY_TYPE_SECURE) ? true : false;
        picture=(status.heapType & NEXUS_HEAP_TYPE_PICTURE_BUFFERS) ? true : false;

        if((!secure)||(!picture))
            continue;

        /* This heap is a secure picture buffer heap, update it's status */
        NEXUS_Platform_GetHeapRuntimeSettings(platformConfig.heap[i], &heapSettings);

        if(heapSettings.secure==markSecure)
            continue;

        BDBG_WRN(("Updating HEAP[%d] from %s to %s", i,
                  heapSettings.secure ? "SECURE" : "CLEAR",
                  markSecure ? "SECURE" : "CLEAR"));

        heapSettings.secure=markSecure;
        rc=NEXUS_Platform_SetHeapRuntimeSettings(platformConfig.heap[i], &heapSettings);
        if(rc)
        {
            BDBG_ERR(("Failed NEXUS_Platform_SetHeapRuntimeSettings (0x%x)", rc));
        }
    }
}

int playback_svp(int argc, char* argv[])
{
    NxClient_JoinSettings joinSettings;
    NxClient_AllocSettings allocSettings;
    NxClient_AllocResults allocResults;
    NEXUS_Error rc;
    NEXUS_SageStatus sageStatus;

    NxClient_ConnectSettings connectSettings;
    unsigned connectId;
    NEXUS_SurfaceClientHandle surfaceClient = NULL;
    NEXUS_SurfaceClientHandle videoSurfaceClient = NULL;
    NEXUS_SimpleVideoDecoderHandle videoDecoder = NULL;
    NEXUS_SimpleAudioDecoderHandle audioDecoder = NULL;

    /* DRM_Prdy specific */
    DRM_Prdy_Init_t     prdyParamSettings;
    DRM_Prdy_Handle_t   drm_context;
#ifdef TEE
    uint32_t            secClkStatus; /* secure clock status */
#endif
    if (argc < 2) {
        BDBG_ERR(("Usage : %s <input_file> [-vc1]", argv[0]));
        return 0;
    }

    if ((argc == 3) && (strcmp(argv[2], "-vc1") == 0))
        vc1_stream = 1;

    BDBG_MSG(("@@@ MSG Check Point Start vc1_stream %d--", vc1_stream));

    NxClient_GetDefaultJoinSettings(&joinSettings);
    snprintf(joinSettings.name, NXCLIENT_MAX_NAME, "pr_piff_playback");
    joinSettings.mode = NEXUS_ClientMode_eVerified;
    rc = NxClient_Join(&joinSettings);
    if (rc)
        return -1;

    /* print heaps on server side */
    NEXUS_Memory_PrintHeaps();

    NxClient_GetDefaultAllocSettings(&allocSettings);
    allocSettings.simpleVideoDecoder = 1;
    allocSettings.simpleAudioDecoder = 1;
    allocSettings.surfaceClient = 1;
    rc = NxClient_Alloc(&allocSettings, &allocResults);
    if (rc)
        return BERR_TRACE(rc);

    DRM_Prdy_GetDefaultParamSettings(&prdyParamSettings);

    drm_context =  DRM_Prdy_Initialize( &prdyParamSettings);
    if( drm_context == NULL) {
       BDBG_ERR(("Failed to create drm_context, quitting...."));
       goto clean_exit ;
    }

#ifdef TEE
    /* Getting the current state of the secure clock*/
    if( DRM_Prdy_SecureClock_GetStatus(drm_context,&secClkStatus) !=  DRM_Prdy_ok)
    {
       BDBG_ERR(("%d Failed to get the Playready Secure Clock status, quitting....\n",__LINE__));
       goto clean_exit;
    }

    if( secClkStatus != DRM_PRDY_CLK_SET)
    {
       /* setup the Playready secure clock */
       if(initSecureClock(drm_context) != 0)
       {
           BDBG_ERR(("%d Failed to initiize Secure Clock, quitting....\n",__LINE__));
           goto clean_exit
       }
    }

  /* enable secure stop */
  if ( DRM_Prdy_TurnSecureStop(drm_context, 1) ) {
      printf("[FAILED] - %d Failed to enable Secure Stop \n",__LINE__);
  }
  else{
    bIsSecureStopEnabled = true;
  }
#endif

#if DEBUG_OUTPUT_CAPTURE
    fp_vid = fopen ("/video.out", "wb");
    fp_aud = fopen ("/audio.out", "wb");
#endif
    BDBG_MSG(("@@@ Check Point #01"));

    if (allocResults.simpleVideoDecoder[0].id) {
        BDBG_MSG(("@@@ to acquire video decoder"));
        videoDecoder = NEXUS_SimpleVideoDecoder_Acquire(allocResults.simpleVideoDecoder[0].id);
    }
    BDBG_ASSERT(videoDecoder);
    if (allocResults.simpleAudioDecoder.id) {
        BDBG_MSG(("@@@ to acquire audio decoder"));
        audioDecoder = NEXUS_SimpleAudioDecoder_Acquire(allocResults.simpleAudioDecoder.id);
    }
    BDBG_ASSERT(audioDecoder);
    if (allocResults.surfaceClient[0].id) {
        BDBG_MSG(("@@@ to acquire surfaceclient"));
        /* surfaceClient is the top-level graphics window in which video will fit.
        videoSurfaceClient must be "acquired" to associate the video window with surface compositor.
        Graphics do not have to be submitted to surfaceClient for video to work, but at least an
        "alpha hole" surface must be submitted to punch video through other client's graphics.
        Also, the top-level surfaceClient ID must be submitted to NxClient_ConnectSettings below. */
        surfaceClient = NEXUS_SurfaceClient_Acquire(allocResults.surfaceClient[0].id);
        videoSurfaceClient = NEXUS_SurfaceClient_AcquireVideoWindow(surfaceClient, 0);
    }
    NxClient_GetDefaultConnectSettings(&connectSettings);
    connectSettings.simpleVideoDecoder[0].id = allocResults.simpleVideoDecoder[0].id;
    connectSettings.simpleVideoDecoder[0].surfaceClientId = allocResults.surfaceClient[0].id;
    connectSettings.simpleVideoDecoder[0].decoderCapabilities.secureVideo = true;
    connectSettings.simpleAudioDecoder.id = allocResults.simpleAudioDecoder.id;
    rc = NxClient_Connect(&connectSettings, &connectId);
    if (rc) return BERR_TRACE(rc);

    gui_init( surfaceClient );

    /* DRM will toggle URR to "on"... tell nexus */
    setHeapsSecure(true);

    playback_piff(videoDecoder,
                  audioDecoder,
                  drm_context,
                  argv[1]);

#if DEBUG_OUTPUT_CAPTURE
    fclose (fp_vid);
    fclose (fp_aud);
#endif

    if (videoDecoder != NULL) {
        NEXUS_SimpleVideoDecoder_Release( videoDecoder );
    }

    if ( audioDecoder != NULL) {
        NEXUS_SimpleAudioDecoder_Release( audioDecoder );
    }

    if ( surfaceClient != NULL ) {
        NEXUS_SurfaceClient_Release( surfaceClient );
    }

    DRM_Prdy_Uninitialize(drm_context);

    do
    {
        BKNI_Sleep(100);
        rc=NEXUS_Sage_GetStatus(&sageStatus);
    }while(sageStatus.urr.secured&&!rc);

    /* DRM done toggle URR to "off"... tell nexus */
    setHeapsSecure(false);

    NxClient_Disconnect(connectId);
    NxClient_Free(&allocResults);
    NxClient_Uninit();

clean_exit:

    return 0;

}

#define FILE_NAME "videos/cnnticker.mpg"
#define VIDEO_CODEC NEXUS_VideoCodec_eMpeg2
#define VIDEO_PID 0x21

int playback_clear(void)
{
    NxClient_JoinSettings joinSettings;
    NxClient_AllocSettings allocSettings;
    NxClient_AllocResults allocResults;
    NxClient_ConnectSettings connectSettings;
    unsigned connectId;
    FILE *file;
    NEXUS_PlaypumpSettings playpumpSettings;
    NEXUS_PlaypumpHandle playpump;
    NEXUS_PlaypumpOpenSettings playpumpOpenSettings;
    BKNI_EventHandle event;
    NEXUS_SimpleStcChannelHandle stcChannel;
    NEXUS_PidChannelHandle videoPidChannel;
    NEXUS_SimpleVideoDecoderHandle videoDecoder;
    NEXUS_SimpleVideoDecoderStartSettings videoProgram;
    NEXUS_MemoryAllocationSettings memSettings;
    NEXUS_ClientConfiguration clientConfig;
    NEXUS_Error rc;

    const char *fname = FILE_NAME;
#define TOTAL_BUFFERS 10
    void *buf[TOTAL_BUFFERS];
    size_t buf_size = 128*1024;
    unsigned cur_buf;
    unsigned i;

    NxClient_GetDefaultJoinSettings(&joinSettings);
    snprintf(joinSettings.name, NXCLIENT_MAX_NAME, "clear_client");
    rc = NxClient_Join(&joinSettings);
    if (rc) {
        printf("cannot join: %d\n", rc);
        return -1;
    }

    BKNI_CreateEvent(&event);

    NEXUS_Playpump_GetDefaultOpenSettings(&playpumpOpenSettings);
    playpumpOpenSettings.fifoSize = 0;
    playpump = NEXUS_Playpump_Open(0, &playpumpOpenSettings);

    /* use stdio for file I/O to keep the example simple. */
    file = fopen(fname, "rb");
    if (!file) {
        fprintf(stderr, "can't open file:%s\n", fname);
        goto error;
    }

    NEXUS_Playpump_GetSettings(playpump, &playpumpSettings);
    playpumpSettings.dataCallback.callback = play_callback;
    playpumpSettings.dataCallback.context = event;
    playpumpSettings.dataNotCpuAccessible = true;
    /* setting mode = NEXUS_PlaypumpMode_eScatterGather is deprecated */
    NEXUS_Playpump_SetSettings(playpump, &playpumpSettings);

    NEXUS_Playpump_Start(playpump);

    stcChannel = NEXUS_SimpleStcChannel_Create(NULL);

    videoPidChannel = NEXUS_Playpump_OpenPidChannel(playpump, VIDEO_PID, NULL);

    NxClient_GetDefaultAllocSettings(&allocSettings);
    allocSettings.simpleVideoDecoder = 1;
    allocSettings.simpleAudioDecoder = 1;
    allocSettings.surfaceClient = 1;
    rc = NxClient_Alloc(&allocSettings, &allocResults);
    if (rc) {BDBG_WRN(("unable to alloc transcode resources")); return -1;}

    NxClient_GetDefaultConnectSettings(&connectSettings);
    connectSettings.simpleVideoDecoder[0].id = allocResults.simpleVideoDecoder[0].id;
    connectSettings.simpleVideoDecoder[0].surfaceClientId = allocResults.surfaceClient[0].id;
    connectSettings.simpleVideoDecoder[0].decoderCapabilities.secureVideo = true;
    connectSettings.simpleAudioDecoder.id = allocResults.simpleAudioDecoder.id;
    rc = NxClient_Connect(&connectSettings, &connectId);
    if (rc) {BDBG_WRN(("unable to connect transcode resources")); return -1;}

    videoDecoder = NEXUS_SimpleVideoDecoder_Acquire(allocResults.simpleVideoDecoder[0].id);
    NEXUS_SimpleVideoDecoder_SetStcChannel(videoDecoder, stcChannel);

    NEXUS_SimpleVideoDecoder_GetDefaultStartSettings(&videoProgram);
    videoProgram.settings.codec = VIDEO_CODEC;
    videoProgram.settings.pidChannel = videoPidChannel;
    NEXUS_SimpleVideoDecoder_Start(videoDecoder, &videoProgram);

    /* buffers must be from the nexus heap to be used by playpump; therefore use NEXUS_Memory_Allocate */
    NEXUS_Platform_GetClientConfiguration(&clientConfig);
    NEXUS_Memory_GetDefaultAllocationSettings(&memSettings);
    memSettings.heap = clientConfig.heap[1]; /* heap 1 is the eFull heap for the nxlient. heap 0 is the graphics heap */

    for (i=0;i<TOTAL_BUFFERS;i++) {
        NEXUS_Memory_Allocate(buf_size, &memSettings, &buf[i]);
    }

    for(cur_buf=0;;) {
        int n;
        NEXUS_Error rc;
        NEXUS_PlaypumpStatus status;

        rc = NEXUS_Playpump_GetStatus(playpump, &status);
        BDBG_ASSERT(!rc);
        if(status.descFifoDepth == TOTAL_BUFFERS) {
            /* every buffer is in use */
            BKNI_WaitForEvent(event, BKNI_INFINITE);
            continue;
        }

        n = fread(buf[cur_buf], 1, buf_size, file);
        if (n < 0) goto error;
        if (n == 0) {
            /* wait for the decoder to reach the end of the content before looping */
            while (1) {
                NEXUS_VideoDecoderStatus status;
                NEXUS_SimpleVideoDecoder_GetStatus(videoDecoder, &status);
                if (!status.queueDepth) break;
            }
            fseek(file, 0, SEEK_SET);
            NEXUS_Playpump_Flush(playpump);
            break;
        }
        else {
            NEXUS_PlaypumpScatterGatherDescriptor desc;
            unsigned numConsumed;
            desc.addr = buf[cur_buf];
            desc.length = n;
            if (playpumpSettings.dataNotCpuAccessible) {
                NEXUS_FlushCache(desc.addr, desc.length);
            }
            rc = NEXUS_Playpump_SubmitScatterGatherDescriptor(playpump, &desc, 1, &numConsumed);
            BDBG_ASSERT(!rc);
            BDBG_ASSERT(numConsumed==1); /* we've already checked that there are descriptors available*/
            cur_buf = (cur_buf + 1)%TOTAL_BUFFERS; /* use the next buffer */
        }
    }

    NxClient_Disconnect(connectId);
    NxClient_Free(&allocResults);
    NxClient_Uninit();
    return 0;

error:
    return 1;
}

int main(int argc, char* argv[])
{
    NxClient_JoinSettings joinSettings;
    NEXUS_Error rc;

    /* Nexus assumes heaps are secure at startup. Change to unsecure */
    /* After this, mark as secure before DRM, and clear when DRM complete */
    NxClient_GetDefaultJoinSettings(&joinSettings);
    snprintf(joinSettings.name, NXCLIENT_MAX_NAME, argv[0]);
    joinSettings.mode = NEXUS_ClientMode_eVerified;
    rc = NxClient_Join(&joinSettings);
    if (rc)
        return -1;

    setHeapsSecure(false);

    NxClient_Uninit();

    while(1){
        if(playback_svp(argc, argv) != 0){
            fprintf(stderr, "playback_svp failed");
        }
        if(playback_clear() != 0){
            fprintf(stderr, "playback_clear failed");
        }
    }

    return 0;
}

static int gui_init( NEXUS_SurfaceClientHandle surfaceClient )
{
    NEXUS_Graphics2DHandle gfx;
    NEXUS_SurfaceHandle surface;

    NEXUS_Graphics2DSettings gfxSettings;
    NEXUS_SurfaceCreateSettings createSettings;
    NEXUS_Graphics2DFillSettings fillSettings;
    int rc;

    if (!surfaceClient) return -1;

    BDBG_MSG(("@@@ gui_init surfaceclient %d", (int)surfaceClient));
    gfx = NEXUS_Graphics2D_Open(NEXUS_ANY_ID, NULL);
    NEXUS_Graphics2D_GetSettings(gfx, &gfxSettings);
    rc = NEXUS_Graphics2D_SetSettings(gfx, &gfxSettings);
    BDBG_ASSERT(!rc);

    NEXUS_Surface_GetDefaultCreateSettings(&createSettings);
    createSettings.pixelFormat = NEXUS_PixelFormat_eA8_R8_G8_B8;
    createSettings.width = 720;
    createSettings.height = 480;
    surface = NEXUS_Surface_Create(&createSettings);

    NEXUS_Graphics2D_GetDefaultFillSettings(&fillSettings);
    fillSettings.surface = surface;
    fillSettings.color = 0;
    rc = NEXUS_Graphics2D_Fill(gfx, &fillSettings);
    BDBG_ASSERT(!rc);

    rc = NEXUS_Graphics2D_Checkpoint(gfx, NULL); /* require to execute queue */

    rc = NEXUS_SurfaceClient_SetSurface(surfaceClient, surface);
    BDBG_ASSERT(!rc);

    return 0;
}

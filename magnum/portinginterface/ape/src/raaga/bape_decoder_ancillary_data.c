/***************************************************************************
 i     Copyright (c) 2006-2013, Broadcom Corporation
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
 * Module Description: Audio Decoder Interface
 *
 * Revision History:
 *
 * $brcm_Log: $
 * 
 ***************************************************************************/

#include "bape.h"
#include "bape_priv.h"

BDBG_MODULE(bape_decoder_ancillary_data);

void BAPE_Decoder_P_AdvanceAncDspRead(BAPE_DecoderHandle hDecoder, unsigned amount, void *pBase, void **pRead, unsigned *pNumBytes, unsigned *pNumWrapBytes)
{
    unsigned dspBytes, dspWrapBytes;
    BDBG_MSG(("Consuming %u bytes from DSP buffer (pre-wrap %u post-wrap %u)", amount, *pNumBytes, *pNumWrapBytes));
    BDBG_ASSERT(amount <= (*pNumBytes + *pNumWrapBytes));
    if ( amount >= *pNumBytes )
    {
        (void)BDSP_Queue_ConsumeData(hDecoder->hAncDataQueue, *pNumBytes);
        amount -= *pNumBytes;
        (void)BDSP_Queue_ConsumeData(hDecoder->hAncDataQueue, amount);
        dspBytes = *pNumWrapBytes - amount;
        dspWrapBytes = 0;
        *pRead = (uint8_t *)pBase + amount;
    }
    else
    {
        (void)BDSP_Queue_ConsumeData(hDecoder->hAncDataQueue, amount);
        dspBytes = *pNumBytes - amount;
        dspWrapBytes = *pNumWrapBytes;
        *pRead = (uint8_t *)*pRead + amount;
    }
    *pNumBytes = dspBytes;
    *pNumWrapBytes = dspWrapBytes;
}

BERR_Code BAPE_Decoder_P_ReadAncData(BAPE_DecoderHandle hDecoder, unsigned amount, void *pBuffer, const void *pBase, const void *pRead, unsigned numBytes, unsigned numWrapBytes)
{
    const uint32_t *pSrc = (const uint32_t *)pRead;
    uint32_t *pDest = (uint32_t *)pBuffer;

    BSTD_UNUSED(hDecoder);

    if ( amount > (numBytes + numWrapBytes) )
    {
        /* Intentionally omitted BERR_TRACE */
        return BERR_TIMEOUT;
    }
    BDBG_ASSERT(amount % 4 == 0);
    BDBG_ASSERT(numBytes % 4 == 0);
    BDBG_ASSERT(numWrapBytes % 4 == 0);

    while ( amount > 0 && numBytes > 0 )
    {
        *pDest++ = *pSrc++;
        amount -= 4;
        numBytes -= 4;
    }
    if ( amount > 0 && numWrapBytes > 0 )
    {
        pSrc = pBase;
        while ( amount > 0 && numWrapBytes > 0 )
        {
            *pDest++ = *pSrc++;
            amount -= 4;
            numWrapBytes -= 4;
        }
    }

    return BERR_SUCCESS;
}

static void BAPE_Decoder_P_WriteHostAncData(
    BAPE_DecoderHandle hDecoder, 
    const void *pData, 
    size_t dataSize, 
    size_t paddingBytes, 
    unsigned *pNumBytes, 
    unsigned *pNumWrapBytes
    )
{
    unsigned numAvail;

    BDBG_ASSERT((dataSize + paddingBytes) <= (unsigned)BAPE_P_FIFO_WRITE_LEFT(&hDecoder->ancDataFifo));

    BDBG_MSG(("WriteHost %lu/%lu", (unsigned long)dataSize, (unsigned long)paddingBytes));

    numAvail = BAPE_P_FIFO_WRITE_PEEK(&hDecoder->ancDataFifo);
    if ( dataSize > numAvail )
    {
        BKNI_Memcpy(BAPE_P_FIFO_WRITE(&hDecoder->ancDataFifo), pData, numAvail);
        pData = (const uint8_t *)pData + numAvail;
        BAPE_P_FIFO_WRITE_COMMIT(&hDecoder->ancDataFifo, numAvail);
        dataSize -= numAvail;
    }
    if ( dataSize > 0 )
    {
        BKNI_Memcpy(BAPE_P_FIFO_WRITE(&hDecoder->ancDataFifo), pData, dataSize);
        pData = (const uint8_t *)pData + dataSize;
        BAPE_P_FIFO_WRITE_COMMIT(&hDecoder->ancDataFifo, dataSize);
    }
    numAvail = BAPE_P_FIFO_WRITE_PEEK(&hDecoder->ancDataFifo);
    if ( paddingBytes > numAvail )
    {
        BKNI_Memset(BAPE_P_FIFO_WRITE(&hDecoder->ancDataFifo), 0, numAvail);
        BAPE_P_FIFO_WRITE_COMMIT(&hDecoder->ancDataFifo, numAvail);
        paddingBytes -= numAvail;
    }
    if ( paddingBytes > 0 )
    {
        BKNI_Memset(BAPE_P_FIFO_WRITE(&hDecoder->ancDataFifo), 0, paddingBytes);
        BAPE_P_FIFO_WRITE_COMMIT(&hDecoder->ancDataFifo, paddingBytes);
    }
    *pNumBytes = BAPE_P_FIFO_WRITE_PEEK(&hDecoder->ancDataFifo);
    *pNumWrapBytes = BAPE_P_FIFO_WRITE_LEFT(&hDecoder->ancDataFifo) - BAPE_P_FIFO_WRITE_PEEK(&hDecoder->ancDataFifo);
}

BERR_Code BAPE_Decoder_GetAncillaryDataBuffer(
    BAPE_DecoderHandle hDecoder,
    void **pBuffer, /* [out] pointer to ancillary data buffer */
    size_t *pSize   /* [out] size of data buffer in bytes */
    )
{
    unsigned dspBytes, dspWrapBytes, hostBytes, hostWrapBytes;
    BDSP_BufferDescriptor bufferDesc;
    void *pDspCached=NULL, *pDspWrapCached=NULL, *pHostCached;    
    uint32_t value;
    BDSP_Raaga_Audio_MpegAncDataPacket packet;
    BAPE_AncillaryDataHeader hostHeader;
    BERR_Code errCode;

    BDBG_OBJECT_ASSERT(hDecoder, BAPE_Decoder);
    BDBG_ASSERT(NULL != pBuffer);
    BDBG_ASSERT(NULL != pSize);

    *pBuffer = NULL;
    *pSize = 0;

    errCode = BMEM_ConvertAddressToCached(hDecoder->deviceHandle->memHandle, hDecoder->pAncDataHostBuffer, &pHostCached);
    if ( errCode )
    {        
        return BERR_TRACE(errCode);
    }
    errCode = BDSP_Queue_GetBuffer(hDecoder->hAncDataQueue, &bufferDesc);
    if ( errCode )
    {        
        return BERR_TRACE(errCode);
    }
    dspBytes = bufferDesc.bufferSize;
    dspWrapBytes = bufferDesc.wrapBufferSize;
    if ( dspBytes == 0 )
    {        
        return BERR_SUCCESS;
    }
    else
    {        
        errCode = BMEM_Heap_ConvertAddressToCached(hDecoder->deviceHandle->memHandle, bufferDesc.buffers[0].pBuffer, &pDspCached);
        if ( errCode )
        {            
            return BERR_TRACE(errCode);
        }
        (void)BMEM_Heap_FlushCache(hDecoder->deviceHandle->memHandle, pDspCached, bufferDesc.bufferSize);
    }
    if ( dspWrapBytes > 0 )
    {
        errCode = BMEM_Heap_ConvertAddressToCached(hDecoder->deviceHandle->memHandle, bufferDesc.buffers[0].pWrapBuffer, &pDspWrapCached);
        if ( errCode )
        {
            return BERR_TRACE(errCode);
        }
        (void)BMEM_Heap_FlushCache(hDecoder->deviceHandle->memHandle, pDspWrapCached, bufferDesc.wrapBufferSize);
    }
    /* These are offsets, not addresses */
    hostBytes = BAPE_P_FIFO_WRITE_PEEK(&hDecoder->ancDataFifo);
    hostWrapBytes = BAPE_P_FIFO_WRITE_LEFT(&hDecoder->ancDataFifo) - hostBytes;

    BDBG_MSG(("%u/%u bytes in host buffer", hostBytes, hostWrapBytes));
    
    while ( dspBytes > 0 && hostBytes > 0 )
    {
        unsigned numDataBytes;

        /* Read packet header into local memory */
        if ( BAPE_Decoder_P_ReadAncData(hDecoder, sizeof(packet), &packet, pDspWrapCached, pDspCached, dspBytes, dspWrapBytes) )
        {
            /* Insufficient Data.  Return. */
            BDBG_MSG(("Insufficient data in DSP buffer %lu bytes of %u/%u", (unsigned long)sizeof(packet), dspBytes, dspWrapBytes));
            goto done;
        }
#ifndef BDSP_AF_P_MPEG_ANC_DATA_SYNCWORD
#define BDSP_AF_P_MPEG_ANC_DATA_SYNCWORD (0x4d504547)
#endif
        /* See if syncword matches */
        if ( packet.ui32Syncword != BDSP_AF_P_MPEG_ANC_DATA_SYNCWORD )
        {
            /* Syncword mismatch.  Consume first word and retry */
            BDBG_MSG(("Syncword mismatch - expecting %#x got %#x", BDSP_AF_P_MPEG_ANC_DATA_SYNCWORD, packet.ui32Syncword));
            BAPE_Decoder_P_AdvanceAncDspRead(hDecoder, 4, pDspWrapCached, &pDspCached, &dspBytes, &dspWrapBytes);
            continue;
        }
        else
        {
            BDBG_MSG(("Syncword match"));
        }

        numDataBytes = (packet.ui32AncDataBitsWritten + 7) / 8;
        numDataBytes = (numDataBytes+3) & ~3; /* Round off to 32-bit boundary */
        BDBG_MSG(("Packet has %u bytes (%u bits)", numDataBytes, packet.ui32AncDataBitsWritten));
        /* There must be enough space in the DSP buffer to hold the packet header and all data bytes to continue.
           The DSP only updates the write pointer after all the DMA is done so this should always be true unless we have
           some corrupt packet header */
        if ( numDataBytes <= ((dspBytes + dspWrapBytes) - sizeof(packet)) )
        {
            unsigned blockSize, paddingBytes = 0;

            blockSize = sizeof(hostHeader) + numDataBytes;

            /* Make sure we can fit the current packet in the buffer */
            if ( (blockSize+sizeof(hostHeader)) > (hostBytes + hostWrapBytes) )
            {
                /* Insufficient free space for new data */
                break;
            }

            /* A packet can not straddle a wraparound point */
            if ( (blockSize+sizeof(hostHeader)) > hostBytes )
            {
                /* See if packet will fit */
                if ( blockSize > hostBytes )
                {
                    /* Packet won't fit */
                    BDBG_ASSERT(hostBytes >= sizeof(hostHeader));
                    hostHeader.blockSize = hostBytes;
                    hostHeader.payloadSize = 0;
                    hostHeader.payloadSizeBits = 0;
                    hostHeader.frameNumber = 0;
                    BDBG_MSG(("Dummy packet %u bytes", hostHeader.blockSize));
                    BAPE_Decoder_P_WriteHostAncData(hDecoder, &hostHeader, sizeof(hostHeader), hostHeader.blockSize-sizeof(hostHeader), &hostBytes, &hostWrapBytes);
                    continue;                    
                }
                else
                {
                    /* Packet will fit, but next header will not.  We must be at the end of the buffer to write this. */
                    if ( hostWrapBytes == 0 )
                    {
                        BDBG_MSG(("Insufficient space to fill remainder of buffer before wraparound"));
                        break;
                    }
                    paddingBytes = hostBytes-blockSize;
                    BDBG_MSG(("Adding %u stuffing bytes to handle wraparound", paddingBytes));
                    blockSize = hostBytes;
                }
            }

            /* Setup Header */
            hostHeader.blockSize = blockSize;
            hostHeader.payloadSize = (packet.ui32AncDataBitsWritten+7)/8;
            hostHeader.payloadSizeBits = packet.ui32AncDataBitsWritten;
            hostHeader.frameNumber = packet.ui32FrameNumber;

            /* consume packet header from dsp */
            BDBG_MSG(("Advance DSP Read %lu %p %p (%p) %u %u", (unsigned long)sizeof(BDSP_Raaga_Audio_MpegAncDataPacket), pDspWrapCached, (void *)&pDspCached, pDspCached, dspBytes, dspWrapBytes));
            BAPE_Decoder_P_AdvanceAncDspRead(hDecoder, sizeof(BDSP_Raaga_Audio_MpegAncDataPacket), pDspWrapCached, &pDspCached, &dspBytes, &dspWrapBytes);
            BDBG_MSG(("After Advance DSP Read %lu %p %p (%p) %u %u", (unsigned long)sizeof(BDSP_Raaga_Audio_MpegAncDataPacket), pDspWrapCached, (void *)&pDspCached, pDspCached, dspBytes, dspWrapBytes));
            /* Write host header */
            BDBG_MSG(("Host Payload Size %u bytes blockSize %u bytes", hostHeader.payloadSize, hostHeader.blockSize));
            BAPE_Decoder_P_WriteHostAncData(hDecoder, &hostHeader, sizeof(hostHeader), 0, &hostBytes, &hostWrapBytes);
            /* Get Data and write a bytestream */
            while ( numDataBytes > 0 )
            {
                unsigned i;
                (void)BAPE_Decoder_P_ReadAncData(hDecoder, 4, &value, pDspWrapCached, pDspCached, dspBytes, dspWrapBytes);
                BAPE_Decoder_P_AdvanceAncDspRead(hDecoder, 4, pDspWrapCached, &pDspCached, &dspBytes, &dspWrapBytes);
                for ( i = 0; i < 4; i++ )
                {
                    uint8_t dataByte;
                    dataByte = value>>24;
                    value <<= 8;
                    BAPE_Decoder_P_WriteHostAncData(hDecoder, &dataByte, 1, 0, &hostBytes, &hostWrapBytes);                        
                }
                numDataBytes-=4;
            }
            if ( paddingBytes > 0 )
            {
                /* Add padding bytes to fill remainder of buffer before wraparound */
                BAPE_Decoder_P_WriteHostAncData(hDecoder, &hostHeader, 0, paddingBytes, &hostBytes, &hostWrapBytes);
            }
            /* JDG - Temp */
            goto done;
        }
        else
        {
            BDBG_WRN(("Data payload (%u bytes/%u bits) not available in DSP buffer (%u/%u) - dropping packet", numDataBytes, packet.ui32AncDataBitsWritten, dspBytes, dspWrapBytes));
            BAPE_Decoder_P_AdvanceAncDspRead(hDecoder, 4, pDspWrapCached, &pDspCached, &dspBytes, &dspWrapBytes);
            continue;
        }
    }

done:
    *pBuffer = ((uint8_t *)BAPE_P_FIFO_READ(&hDecoder->ancDataFifo) - (uint8_t *)hDecoder->pAncDataHostCached)+(uint8_t *)hDecoder->pAncDataHostBuffer;
    hostBytes = BAPE_P_FIFO_READ_PEEK(&hDecoder->ancDataFifo);
    BDBG_MSG(("GetAncillaryData %u", hostBytes));
    *pSize = hostBytes;
    hDecoder->ancDataInit = false;
    return BERR_SUCCESS;
}

/***************************************************************************
Summary:
Consume Decoder Ancillary Data
***************************************************************************/
BERR_Code BAPE_Decoder_ConsumeAncillaryData(
    BAPE_DecoderHandle hDecoder,
    size_t numBytes
    )
{
    unsigned hostBytes, hostWrapBytes;

    BDBG_OBJECT_ASSERT(hDecoder, BAPE_Decoder);

    if ( hDecoder->ancDataInit )
    {
        /* The decoder has been restarted since GetBuffer was last called */
        return BERR_SUCCESS;
    }
    
    BDBG_MSG(("ConsumeAncillaryData %lu", (unsigned long)numBytes));

    hostBytes = BAPE_P_FIFO_READ_PEEK(&hDecoder->ancDataFifo);
    hostWrapBytes = BAPE_P_FIFO_READ_LEFT(&hDecoder->ancDataFifo) - hostBytes;
    
    if ( numBytes > hostBytes + hostWrapBytes )
    {
        BDBG_ERR(("Attempt to consume %lu ancillary data bytes but only %u are buffered", (unsigned long)numBytes, hostBytes + hostWrapBytes));
        return BERR_TRACE(BERR_INVALID_PARAMETER);
    }

    if ( numBytes > hostBytes )    
    {
        BAPE_P_FIFO_READ_COMMIT(&hDecoder->ancDataFifo, hostBytes);
        numBytes -= hostBytes;
    }
    BAPE_P_FIFO_READ_COMMIT(&hDecoder->ancDataFifo, numBytes);

    return BERR_SUCCESS;
}

/***************************************************************************
Summary:
Flush Decoder Ancillary Data
***************************************************************************/
void BAPE_Decoder_FlushAncillaryData(
    BAPE_DecoderHandle hDecoder
    )
{
    unsigned numBytes;

    BDBG_OBJECT_ASSERT(hDecoder, BAPE_Decoder);

    if ( hDecoder->ancDataBufferSize > 0 )
    {
        BDSP_Queue_Flush(hDecoder->hAncDataQueue);
        while ( (numBytes = BAPE_P_FIFO_READ_PEEK(&hDecoder->ancDataFifo)) )
        {
            BAPE_P_FIFO_READ_COMMIT(&hDecoder->ancDataFifo, numBytes);
        }
    }
}

void BAPE_Decoder_P_InitAncillaryDataBuffer(BAPE_DecoderHandle hDecoder)
{
    void *pFifoCached;
    BDBG_MSG(("InitAncillaryDataBuffer"));
    if ( hDecoder->pAncDataBufferDescriptor )
    {
        BDSP_Queue_Flush(hDecoder->hAncDataQueue);
    }
    (void)BMEM_Heap_ConvertAddressToCached(hDecoder->deviceHandle->memHandle, hDecoder->pAncDataHostBuffer, &pFifoCached);
    BAPE_P_FIFO_INIT(&hDecoder->ancDataFifo, pFifoCached, hDecoder->ancDataBufferSize);
    hDecoder->ancDataInit = true;
}


/***************************************************************************
 *     Copyright (c) 2006-2014, Broadcom Corporation
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

#include "bstd.h"
#include "bkni.h"
#include "bape.h"
#include "bape_priv.h"
#include "bdsp_raaga.h"

BDBG_MODULE(bape_decoder_status);

static BAPE_ChannelMode BAPE_Decoder_P_ChannelModeFromDsp(uint32_t dspMode)
{
    switch ( dspMode )
    {
    case 0:
        return BAPE_ChannelMode_e1_1;
    case 1:
        return BAPE_ChannelMode_e1_0;
    case 2:
        return BAPE_ChannelMode_e2_0;
    case 3:
        return BAPE_ChannelMode_e3_0;
    case 4:
        return BAPE_ChannelMode_e2_1;
    case 5:
        return BAPE_ChannelMode_e3_1;
    case 6:
        return BAPE_ChannelMode_e2_2;
    case 7:
        return BAPE_ChannelMode_e3_2;
    default:
        return BAPE_ChannelMode_eMax;
    }
}

static BERR_Code BAPE_Decoder_P_GetAc3Status(
    BAPE_DecoderHandle handle, 
    unsigned mode, 
    const BDSP_AudioBitRateChangeInfo *pBitRateInfo, 
    BAPE_DecoderStatus *pStatus
    )
{
    BERR_Code errCode;

    pStatus->codecStatus.ac3.acmod = mode;  /* Use the value from the interrupt.  The streamInfo value is last decoded frame not last parsed. */
    pStatus->codecStatus.ac3.channelMode = BAPE_Decoder_P_ChannelModeFromDsp(mode);
    pStatus->codecStatus.ac3.bitrate = pBitRateInfo->ui32BitRate/1024; /* FW reports in bps */

    if ( !handle->passthrough )
    {
        errCode = BDSP_Stage_GetStatus(handle->hPrimaryStage, &handle->streamInfo.ddp, sizeof(handle->streamInfo.ddp));
        if ( errCode )
        {
            return errCode;
        }

        switch(handle->streamInfo.ddp.ui32SamplingFrequency)
        {
            case 0:
                pStatus->codecStatus.ac3.samplingFrequency = 48000;
                break;
            case 1:
                pStatus->codecStatus.ac3.samplingFrequency = 44100;
                break;
            case 2:
                pStatus->codecStatus.ac3.samplingFrequency = 32000;
                break;
            default:
                pStatus->codecStatus.ac3.samplingFrequency = 0;
                break;
        }

        pStatus->codecStatus.ac3.bitstreamId = handle->streamInfo.ddp.ui32BitStreamIdentification;
        /* This enum is defined to match the AC3 spec */
        pStatus->codecStatus.ac3.bsmod = handle->streamInfo.ddp.ui32BsmodValue;
        /* This enum is defined to match the AC3 spec */
        switch ( handle->streamInfo.ddp.ui32DsurmodValue )
        {
        case 0:
            pStatus->codecStatus.ac3.dolbySurround = BAPE_Ac3DolbySurround_eNotIndicated;
            break;
        case 1:
            pStatus->codecStatus.ac3.dolbySurround = BAPE_Ac3DolbySurround_eNotEncoded;
            break;
        case 2:
            pStatus->codecStatus.ac3.dolbySurround = BAPE_Ac3DolbySurround_eEncoded;
            break;
        default:
            pStatus->codecStatus.ac3.dolbySurround = BAPE_Ac3DolbySurround_eReserved;
            break;
        }
        /* This enum is defined to match the AC3 spec */
        switch ( handle->streamInfo.ddp.ui32CmixLevel )
        {
        case 0:
            pStatus->codecStatus.ac3.centerMixLevel = BAPE_Ac3CenterMixLevel_e3;
            break;
        case 1:
            pStatus->codecStatus.ac3.centerMixLevel = BAPE_Ac3CenterMixLevel_e4_5;
            break;
        case 2:
            pStatus->codecStatus.ac3.centerMixLevel = BAPE_Ac3CenterMixLevel_e6;
            break;
        default:
            pStatus->codecStatus.ac3.centerMixLevel = BAPE_Ac3CenterMixLevel_eReserved;
            break;
        }
        /* This enum is defined to match the AC3 spec */
        switch ( handle->streamInfo.ddp.ui32SurmixLevel )
        {
        case 0:
            pStatus->codecStatus.ac3.centerMixLevel = BAPE_Ac3SurroundMixLevel_e3;
            break;
        case 1:
            pStatus->codecStatus.ac3.centerMixLevel = BAPE_Ac3SurroundMixLevel_e6;
            break;
        case 2:
            pStatus->codecStatus.ac3.centerMixLevel = BAPE_Ac3SurroundMixLevel_e0;
            break;
        default:
            pStatus->codecStatus.ac3.centerMixLevel = BAPE_Ac3SurroundMixLevel_eReserved;
            break;
        }
        /* TODO: Doesn't this have the same race condition as acmod? */
        pStatus->codecStatus.ac3.lfe = handle->streamInfo.ddp.ui32LfeOn?true:false;
        pStatus->codecStatus.ac3.copyright = handle->streamInfo.ddp.ui32CopyrightBit?true:false;
        pStatus->codecStatus.ac3.original = handle->streamInfo.ddp.ui32OriginalBitStream?true:false;
        pStatus->codecStatus.ac3.frameSizeCode = handle->streamInfo.ddp.ui32FrmSizeCod;
        pStatus->codecStatus.ac3.dependentFrameChannelMap = handle->streamInfo.ddp.ui32DepFrameChanmapMode;
        pStatus->codecStatus.ac3.dialnorm = handle->streamInfo.ddp.ui32CurrentDialNorm;
        pStatus->codecStatus.ac3.previousDialnorm = handle->streamInfo.ddp.ui32PreviousDialNorm;
        pStatus->framesDecoded = handle->streamInfo.ddp.ui32TotalFramesDecoded;
        pStatus->frameErrors = handle->streamInfo.ddp.ui32TotalFramesInError;
        pStatus->dummyFrames = handle->streamInfo.ddp.ui32TotalFramesDummy;
    }

    return BERR_SUCCESS;
}

static BERR_Code BAPE_Decoder_P_GetMpegStatus(
    BAPE_DecoderHandle handle, 
    unsigned mode, 
    const BDSP_AudioBitRateChangeInfo *pBitRateInfo, 
    BAPE_DecoderStatus *pStatus
    )
{
    BERR_Code errCode;

    pStatus->codecStatus.mpeg.bitRate = pBitRateInfo->ui32BitRate/1024; /* FW reports in bps */
    switch ( mode )
    {
    default:
        BDBG_MSG(("Unsupported MPEG channel mode value %u", mode));
        /* fall through */
    case 0:
    case 1:
        pStatus->codecStatus.mpeg.channelMode = BAPE_ChannelMode_e2_0;
        break;
    case 2:
        pStatus->codecStatus.mpeg.channelMode = BAPE_ChannelMode_e1_1;
        break;
    case 3:
        pStatus->codecStatus.mpeg.channelMode = BAPE_ChannelMode_e1_0;
        break;
    }
    pStatus->codecStatus.mpeg.mpegChannelMode = mode;                   /* This enum is defined to match the MPEG spec */

    if ( !handle->passthrough )
    {
        errCode = BDSP_Stage_GetStatus(handle->hPrimaryStage, &handle->streamInfo.mpeg, sizeof(handle->streamInfo.mpeg));
        if ( errCode )
        {
            return errCode;
        }
    
        pStatus->codecStatus.mpeg.original = handle->streamInfo.mpeg.ui32OriginalCopy?true:false;
        pStatus->codecStatus.mpeg.copyright = handle->streamInfo.mpeg.ui32Copyright?true:false;
        pStatus->codecStatus.mpeg.crcPresent = handle->streamInfo.mpeg.ui32CrcPresent?true:false;
        switch(handle->streamInfo.mpeg.ui32SamplingFreq)
        {
            case 0:
                pStatus->codecStatus.mpeg.samplingFrequency = 44100;
                break;
            case 1:
                pStatus->codecStatus.mpeg.samplingFrequency = 48000;
                break;
            case 2:
                pStatus->codecStatus.mpeg.samplingFrequency = 32000;
                break;
            default:
                pStatus->codecStatus.mpeg.samplingFrequency = 0;
                break;
        }

        switch ( handle->streamInfo.mpeg.ui32MpegLayer )
        {
        case 3:
            pStatus->codecStatus.mpeg.layer = 1;
            break;
        case 2:
            pStatus->codecStatus.mpeg.layer = 2;
            break;
        case 1:
            pStatus->codecStatus.mpeg.layer = 3;
            break;
        default:
            BDBG_WRN(("Unrecognized MPEG layer code %u", handle->streamInfo.mpeg.ui32MpegLayer));
            pStatus->codecStatus.mpeg.layer = 0;
            break;
        }
    
        pStatus->codecStatus.mpeg.emphasisMode = handle->streamInfo.mpeg.ui32Emphasis;   /* This enum is defined to match the MPEG spec */
        pStatus->framesDecoded = handle->streamInfo.mpeg.ui32TotalFramesDecoded;
        pStatus->frameErrors = handle->streamInfo.mpeg.ui32TotalFramesInError;
        pStatus->dummyFrames = handle->streamInfo.mpeg.ui32TotalFramesDummy;
    }
    
    return BERR_SUCCESS;
}

static BERR_Code BAPE_Decoder_P_GetAacStatus(
    BAPE_DecoderHandle handle, 
    unsigned mode, 
    const BDSP_AudioBitRateChangeInfo *pBitRateInfo, 
    BAPE_DecoderStatus *pStatus
    )
{
    BERR_Code errCode;

    pStatus->codecStatus.aac.channelMode = BAPE_Decoder_P_ChannelModeFromDsp(mode);
    pStatus->codecStatus.aac.bitRate = pBitRateInfo->ui32BitRate/1024; /* FW reports in bps */

    if ( !handle->passthrough )
    {
        errCode = BDSP_Stage_GetStatus(handle->hPrimaryStage, &handle->streamInfo.aac, sizeof(handle->streamInfo.aac));
        if ( errCode )
        {
            return errCode;
        }
        
        switch ( handle->streamInfo.aac.ui32SamplingFreq )
        {
        case 0:
            pStatus->codecStatus.aac.samplingFrequency = 96000;
            break;
        case 1:
            pStatus->codecStatus.aac.samplingFrequency = 88200;
            break;
        case 2:
            pStatus->codecStatus.aac.samplingFrequency = 64000;
            break;
        case 3:
            pStatus->codecStatus.aac.samplingFrequency = 48000;
            break;
        case 4:
            pStatus->codecStatus.aac.samplingFrequency = 44100;
            break;
        case 5:
            pStatus->codecStatus.aac.samplingFrequency = 32000;
            break;
        case 6:
            pStatus->codecStatus.aac.samplingFrequency = 24000;
            break;
        case 7:
            pStatus->codecStatus.aac.samplingFrequency = 22050;
            break;
        case 8:
            pStatus->codecStatus.aac.samplingFrequency = 16000;
            break;
        case 9:
            pStatus->codecStatus.aac.samplingFrequency = 12000;
            break;
        case 10:
            pStatus->codecStatus.aac.samplingFrequency = 11025;
            break;
        case 11:
            pStatus->codecStatus.aac.samplingFrequency = 8000;
            break;
        default:
            BDBG_WRN(("Unsupported AAC sample rate code %u", handle->streamInfo.aac.ui32SamplingFreq));
            pStatus->codecStatus.aac.samplingFrequency = 0;
            break;
        }
        
        pStatus->codecStatus.aac.profile = handle->streamInfo.aac.ui32Profile;  /* This enum is defined to match the spec */
        pStatus->codecStatus.aac.lfe = handle->streamInfo.aac.ui32LfeOn?true:false;
        pStatus->codecStatus.aac.pseudoSurround = handle->streamInfo.aac.ui32PseudoSurroundEnable?true:false;
        pStatus->codecStatus.aac.drc = handle->streamInfo.aac.ui32DrcPresent?true:false;

        pStatus->codecStatus.aac.channelMode = BAPE_Decoder_P_ChannelModeFromDsp(handle->streamInfo.aac.ui32AcmodValue);

#ifdef BDSP_MS10_SUPPORT
        pStatus->codecStatus.aac.dialnorm = handle->streamInfo.aac.ui32CurrentDialNorm;
        pStatus->codecStatus.aac.previousDialnorm = handle->streamInfo.aac.ui32PreviousDialNorm;
#endif
        pStatus->framesDecoded = handle->streamInfo.aac.ui32TotalFramesDecoded;
        pStatus->frameErrors = handle->streamInfo.aac.ui32TotalFramesInError;
        pStatus->dummyFrames = handle->streamInfo.aac.ui32TotalFramesDummy;
    }

    return BERR_SUCCESS;
}

static BERR_Code BAPE_Decoder_P_GetWmaStatus(
    BAPE_DecoderHandle handle, 
    unsigned mode, 
    const BDSP_AudioBitRateChangeInfo *pBitRateInfo, 
    BAPE_DecoderStatus *pStatus
    )
{
    BERR_Code errCode;

    pStatus->codecStatus.wma.channelMode = mode == 0 ? BAPE_ChannelMode_e1_0 : BAPE_ChannelMode_e2_0;
    pStatus->codecStatus.wma.bitRate = pBitRateInfo->ui32BitRate/1024; /* FW reports in bps */

    if ( !handle->passthrough )
    {
        errCode = BDSP_Stage_GetStatus(handle->hPrimaryStage, &handle->streamInfo.wma, sizeof(handle->streamInfo.wma));
        if ( errCode )
        {
            return errCode;
        }

        pStatus->codecStatus.wma.copyright = handle->streamInfo.wma.ui32Copyright ? true : false;
        pStatus->codecStatus.wma.original = handle->streamInfo.wma.ui32OriginalCopy ? true : false;
        pStatus->codecStatus.wma.crc = handle->streamInfo.wma.ui32CrcPresent ? true : false;
        pStatus->codecStatus.wma.version = handle->streamInfo.wma.ui32Version + 1;
        pStatus->codecStatus.wma.channelMode = handle->streamInfo.wma.ui32Acmod == 0 ? BAPE_ChannelMode_e1_0 : BAPE_ChannelMode_e2_0;
        pStatus->framesDecoded = handle->streamInfo.wma.ui32TotalFramesDecoded;
        pStatus->frameErrors = handle->streamInfo.wma.ui32TotalFramesInError;
        pStatus->dummyFrames = handle->streamInfo.wma.ui32TotalFramesDummy;
    }

    return BERR_SUCCESS;
}

static BERR_Code BAPE_Decoder_P_GetWmaProStatus(
    BAPE_DecoderHandle handle, 
    unsigned mode, 
    const BDSP_AudioBitRateChangeInfo *pBitRateInfo, 
    BAPE_DecoderStatus *pStatus
    )
{
    BERR_Code errCode;

    pStatus->codecStatus.wmaPro.channelMode = BAPE_Decoder_P_ChannelModeFromDsp(mode);
    pStatus->codecStatus.wmaPro.bitRate = pBitRateInfo->ui32BitRate/1024; /* FW reports in bps */

    if ( !handle->passthrough )
    {
        errCode = BDSP_Stage_GetStatus(handle->hPrimaryStage, &handle->streamInfo.wmaPro, sizeof(handle->streamInfo.wmaPro));
        if ( errCode )
        {
            return errCode;
        }

        pStatus->codecStatus.wmaPro.copyright = handle->streamInfo.wmaPro.ui32Copyright ? true : false;
        pStatus->codecStatus.wmaPro.original = handle->streamInfo.wmaPro.ui32OriginalCopy ? true : false;
        pStatus->codecStatus.wmaPro.crc = handle->streamInfo.wmaPro.ui32CrcPresent ? true : false;
        pStatus->codecStatus.wmaPro.lfe = handle->streamInfo.wmaPro.ui32LfeOn ? true : false;
        pStatus->codecStatus.wmaPro.version = handle->streamInfo.wmaPro.ui32Version + 1;

        switch ( handle->streamInfo.wmaPro.ui32Mode )
        {
        case 0:
            pStatus->codecStatus.wmaPro.stereoMode = BAPE_WmaProStereoMode_eAuto;
            break;
        case 1:
            pStatus->codecStatus.wmaPro.stereoMode = BAPE_WmaProStereoMode_eLtRt;
            break;
        case 2:
            pStatus->codecStatus.wmaPro.stereoMode = BAPE_WmaProStereoMode_eLoRo;
            break;
        default:
            pStatus->codecStatus.wmaPro.stereoMode = BAPE_WmaProStereoMode_eMax;
            break;
        }
        pStatus->codecStatus.wmaPro.channelMode = BAPE_Decoder_P_ChannelModeFromDsp(handle->streamInfo.wmaPro.ui32Acmod);
        pStatus->framesDecoded = handle->streamInfo.wmaPro.ui32TotalFramesDecoded;
        pStatus->frameErrors = handle->streamInfo.wmaPro.ui32TotalFramesInError;
        pStatus->dummyFrames = handle->streamInfo.wmaPro.ui32TotalFramesDummy;
    }

    return BERR_SUCCESS;
}

static BERR_Code BAPE_Decoder_P_GetDtsStatus(
    BAPE_DecoderHandle handle, 
    unsigned mode, 
    const BDSP_AudioBitRateChangeInfo *pBitRateInfo, 
    BAPE_DecoderStatus *pStatus
    )
{
    BERR_Code errCode;

    pStatus->codecStatus.dts.channelMode = BAPE_Decoder_P_ChannelModeFromDsp(mode);
    pStatus->codecStatus.dts.bitRate = pBitRateInfo->ui32BitRate/1024; /* FW reports in bps */

    if ( !handle->passthrough )
    {
        errCode = BDSP_Stage_GetStatus(handle->hPrimaryStage, &handle->streamInfo.dts, sizeof(handle->streamInfo.dts));
        if ( errCode )
        {
            return errCode;
        }

        pStatus->codecStatus.dts.amode = handle->streamInfo.dts.ui32Amode;
        pStatus->codecStatus.dts.pcmResolution = handle->streamInfo.dts.ui32PcmResolution;
        pStatus->codecStatus.dts.copyHistory = handle->streamInfo.dts.ui32CopyHist;
        pStatus->codecStatus.dts.extensionDescriptor = handle->streamInfo.dts.ui32ExtAudioId;
        pStatus->codecStatus.dts.version = handle->streamInfo.dts.ui32VerNum;
        pStatus->codecStatus.dts.esFormat = handle->streamInfo.dts.sDtsFrameInfo.ui32EsFlag ? true : false;
        pStatus->codecStatus.dts.lfe = handle->streamInfo.dts.sDtsFrameInfo.ui32LFEPresent ? true : false;
        pStatus->codecStatus.dts.extensionPresent = handle->streamInfo.dts.ui32ExtAudioFlag ? true : false;
        pStatus->codecStatus.dts.crc = handle->streamInfo.dts.ui32CrcFlag ? true : false;
        pStatus->codecStatus.dts.hdcdFormat = handle->streamInfo.dts.ui32HdcdFormat ? true : false;
        pStatus->codecStatus.dts.drc = handle->streamInfo.dts.ui32DynRangeCoeff;
        pStatus->codecStatus.dts.downmixCoefficients = handle->streamInfo.dts.ui32DownMix;
        pStatus->codecStatus.dts.neo = handle->streamInfo.dts.sDtsFrameInfo.ui32DTSNeoEnable;
        pStatus->codecStatus.dts.frameSize = handle->streamInfo.dts.ui32Fsize;
        pStatus->codecStatus.dts.numChannels = handle->streamInfo.dts.sDtsFrameInfo.ui32NumOfChannels;
        pStatus->codecStatus.dts.pcmFrameSize = handle->streamInfo.dts.sDtsFrameInfo.ui32PCMFrameSize;
        pStatus->codecStatus.dts.samplingFrequency = handle->streamInfo.dts.sDtsFrameInfo.ui32SampleRate;
        pStatus->codecStatus.dts.numPcmBlocks = handle->streamInfo.dts.ui32NBlocks;
        pStatus->framesDecoded = handle->streamInfo.dts.ui32TotalFramesDecoded;
        pStatus->frameErrors = handle->streamInfo.dts.ui32TotalFramesInError;
        pStatus->dummyFrames = handle->streamInfo.dts.ui32TotalFramesDummy;
    }

    return BERR_SUCCESS;
}

static BERR_Code BAPE_Decoder_P_GetDtsExpressStatus(
    BAPE_DecoderHandle handle, 
    unsigned mode, 
    const BDSP_AudioBitRateChangeInfo *pBitRateInfo, 
    BAPE_DecoderStatus *pStatus
    )
{
    BERR_Code errCode;

    pStatus->codecStatus.dts.channelMode = BAPE_Decoder_P_ChannelModeFromDsp(mode);
    pStatus->codecStatus.dts.bitRate = pBitRateInfo->ui32BitRate/1024; /* FW reports in bps */

    if ( !handle->passthrough )
    {
        errCode = BDSP_Stage_GetStatus(handle->hPrimaryStage, &handle->streamInfo.dtsExpress, sizeof(handle->streamInfo.dtsExpress));
        if ( errCode )
        {
            return errCode;
        }

        pStatus->framesDecoded = handle->streamInfo.dtsExpress.ui32TotalFramesDecoded;
        pStatus->frameErrors = handle->streamInfo.dtsExpress.ui32TotalFramesInError;
        pStatus->dummyFrames = handle->streamInfo.dtsExpress.ui32TotalFramesDummy;
    }

    return BERR_SUCCESS;
}

static BERR_Code BAPE_Decoder_P_GetPcmWavStatus(
    BAPE_DecoderHandle handle, 
    unsigned mode, 
    const BDSP_AudioBitRateChangeInfo *pBitRateInfo, 
    BAPE_DecoderStatus *pStatus
    )
{
    BERR_Code errCode;

    BSTD_UNUSED(mode);
    BSTD_UNUSED(pBitRateInfo);

    if ( !handle->passthrough )
    {
        errCode = BDSP_Stage_GetStatus(handle->hPrimaryStage, &handle->streamInfo.pcmwav, sizeof(handle->streamInfo.pcmwav));
        if ( errCode )
        {
            return errCode;
        }

        pStatus->codecStatus.pcmWav.numChannels = handle->streamInfo.pcmwav.ui32NumChannels;
        pStatus->codecStatus.pcmWav.samplingFrequency = handle->streamInfo.pcmwav.ui32SamplingFreq;
        pStatus->framesDecoded = handle->streamInfo.pcmwav.ui32TotalFramesDecoded;
        pStatus->frameErrors = handle->streamInfo.pcmwav.ui32TotalFramesInError;
        pStatus->dummyFrames = handle->streamInfo.pcmwav.ui32TotalFramesDummy;
    }

    return BERR_SUCCESS;
}

static BERR_Code BAPE_Decoder_P_GetAmrStatus(
    BAPE_DecoderHandle handle, 
    unsigned mode, 
    const BDSP_AudioBitRateChangeInfo *pBitRateInfo, 
    BAPE_DecoderStatus *pStatus
    )
{
    BERR_Code errCode;

    BSTD_UNUSED(mode);
    BSTD_UNUSED(pBitRateInfo);

    if ( !handle->passthrough )
    {
        errCode = BDSP_Stage_GetStatus(handle->hPrimaryStage, &handle->streamInfo.amr, sizeof(handle->streamInfo.amr));
        if ( errCode )
        {
            return errCode;
        }

        pStatus->codecStatus.amr.bitRate = handle->streamInfo.amr.ui32BitRate/1024; /* FW reports in bps */
        pStatus->framesDecoded = handle->streamInfo.amr.ui32TotalFramesDecoded;
        pStatus->frameErrors = handle->streamInfo.amr.ui32TotalFramesInError;
        pStatus->dummyFrames = handle->streamInfo.amr.ui32TotalFramesDummy;
    }

    return BERR_SUCCESS;
}

static BERR_Code BAPE_Decoder_P_GetAmrWbStatus(
    BAPE_DecoderHandle handle, 
    unsigned mode, 
    const BDSP_AudioBitRateChangeInfo *pBitRateInfo, 
    BAPE_DecoderStatus *pStatus
    )
{
    BERR_Code errCode;

    BSTD_UNUSED(mode);
    BSTD_UNUSED(pBitRateInfo);

    if ( !handle->passthrough )
    {
        errCode = BDSP_Stage_GetStatus(handle->hPrimaryStage, &handle->streamInfo.amrWb, sizeof(handle->streamInfo.amrWb));
        if ( errCode )
        {
            return errCode;
        }
        
        switch ( handle->streamInfo.amrWb.ui32BitRate )
        {
        default:
        case 0:
            pStatus->codecStatus.amr.bitRate = 4750;
            break;
        case 1:
            pStatus->codecStatus.amr.bitRate = 5150;
            break;
        case 2:
            pStatus->codecStatus.amr.bitRate = 5900;
            break;
        case 3:
            pStatus->codecStatus.amr.bitRate = 6700;
            break;
        case 4:
            pStatus->codecStatus.amr.bitRate = 7400;
            break;
        case 5:
            pStatus->codecStatus.amr.bitRate = 7950;
            break;
        case 6:
            pStatus->codecStatus.amr.bitRate = 10200;
            break;
        case 7:
            pStatus->codecStatus.amr.bitRate = 12200;
            break;
        case 8:
            pStatus->codecStatus.amr.bitRate = 0;
            break;
        }
        pStatus->framesDecoded = handle->streamInfo.amrWb.ui32TotalFramesDecoded;
        pStatus->frameErrors = handle->streamInfo.amrWb.ui32TotalFramesInError;
        pStatus->dummyFrames = handle->streamInfo.amrWb.ui32TotalFramesDummy;
    }

    return BERR_SUCCESS;
}

static BERR_Code BAPE_Decoder_P_GetDraStatus(
    BAPE_DecoderHandle handle, 
    unsigned mode, 
    const BDSP_AudioBitRateChangeInfo *pBitRateInfo, 
    BAPE_DecoderStatus *pStatus
    )
{
    BERR_Code errCode;

    pStatus->codecStatus.dra.channelMode = BAPE_Decoder_P_ChannelModeFromDsp(mode);
    BSTD_UNUSED(pBitRateInfo);

    if ( !handle->passthrough )
    {
        errCode = BDSP_Stage_GetStatus(handle->hPrimaryStage, &handle->streamInfo.dra, sizeof(handle->streamInfo.dra));
        if ( errCode )
        {
            return errCode;
        }

        pStatus->codecStatus.dra.frameSize = handle->streamInfo.dra.ui32FrameSize;
        pStatus->codecStatus.dra.numBlocks = handle->streamInfo.dra.ui32NumBlocks;

        switch (handle->streamInfo.dra.ui32AcmodValue)
        {
            case 1:
                pStatus->codecStatus.dra.acmod = BAPE_DraAcmod_e1_0_C;
                break;
            case 2:
                pStatus->codecStatus.dra.acmod = BAPE_DraAcmod_e2_0_LR;
                break;
            case 3:
                pStatus->codecStatus.dra.acmod = BAPE_DraAcmod_e2_1_LRS;
                break;
            case 4:
                pStatus->codecStatus.dra.acmod = BAPE_DraAcmod_e2_2_LRLrRr;
                break;
            case 5:
                pStatus->codecStatus.dra.acmod = BAPE_DraAcmod_e3_2_LRLrRrC;
                break;
            case 6:
                pStatus->codecStatus.dra.acmod = BAPE_DraAcmod_e3_3_LRLrRrCrC;
                break;
            case 7:
                pStatus->codecStatus.dra.acmod = BAPE_DraAcmod_e5_2_LRLrRrLsRsC;
                break;
            case 8:
                pStatus->codecStatus.dra.acmod = BAPE_DraAcmod_e5_3_LRLrRrLsRsCrC;
                break;
            default:
                pStatus->codecStatus.dra.acmod = BAPE_DraAcmod_eMax;
                break;
        }
        pStatus->codecStatus.dra.lfe = handle->streamInfo.dra.ui32LFEOn ? true : false;
        switch ( handle->streamInfo.dra.ui32OutputMode )
        {
        case 1:
            pStatus->codecStatus.dra.stereoMode = BAPE_DraStereoMode_eLoRo;
            break;
        case 2:
            pStatus->codecStatus.dra.stereoMode = BAPE_DraStereoMode_eLtRt;
            break;
        default:
            pStatus->codecStatus.dra.stereoMode = BAPE_DraStereoMode_eMax;
            break;
        }
        pStatus->framesDecoded = handle->streamInfo.dra.ui32TotalFramesDecoded;
        pStatus->frameErrors = handle->streamInfo.dra.ui32TotalFramesInError;
        pStatus->dummyFrames = handle->streamInfo.dra.ui32TotalFramesDummy;

        switch ( handle->streamInfo.dra.ui32SamplingFrequency )
        {
            case 0:
                pStatus->codecStatus.dra.samplingFrequency = 8000;
                break;
            case 1:
                pStatus->codecStatus.dra.samplingFrequency = 11025;
                break;
            case 2:
                pStatus->codecStatus.dra.samplingFrequency = 12000;
                break;
            case 3:
                pStatus->codecStatus.dra.samplingFrequency = 16000;
                break;
            case 4:
                pStatus->codecStatus.dra.samplingFrequency = 22050;
                break;
            case 5:
                pStatus->codecStatus.dra.samplingFrequency = 24000;
                break;
            case 6:
                pStatus->codecStatus.dra.samplingFrequency = 32000;
                break;
            case 7:
                pStatus->codecStatus.dra.samplingFrequency = 44100;
                break;
            case 8:
                pStatus->codecStatus.dra.samplingFrequency = 48000;
                break;
            case 9:
                pStatus->codecStatus.dra.samplingFrequency = 88200;
                break;
            case 10:
                pStatus->codecStatus.dra.samplingFrequency = 96000;
                break;
            case 11:
                pStatus->codecStatus.dra.samplingFrequency = 176400;
                break;
            case 12:
                pStatus->codecStatus.dra.samplingFrequency = 192000;
                break;
            default:
                pStatus->codecStatus.dra.samplingFrequency = 0;
                break;
        }
    }

    return BERR_SUCCESS;
}

static BERR_Code BAPE_Decoder_P_GetCookStatus(
    BAPE_DecoderHandle handle, 
    unsigned mode, 
    const BDSP_AudioBitRateChangeInfo *pBitRateInfo, 
    BAPE_DecoderStatus *pStatus
    )
{
    BERR_Code errCode;

    BSTD_UNUSED(mode);
    BSTD_UNUSED(pBitRateInfo);

    if ( !handle->passthrough )
    {
        errCode = BDSP_Stage_GetStatus(handle->hPrimaryStage, &handle->streamInfo.cook, sizeof(handle->streamInfo.cook));
        if ( errCode )
        {
            return errCode;
        }

        pStatus->codecStatus.cook.stereo = handle->streamInfo.cook.ui32StreamAcmod == 2 ? true : false;
        pStatus->codecStatus.cook.frameSize = handle->streamInfo.cook.ui32FrameSize;
        pStatus->codecStatus.cook.samplingFrequency = handle->streamInfo.cook.ui32SamplingFrequency;
        pStatus->framesDecoded = handle->streamInfo.cook.ui32TotalFramesDecoded;
        pStatus->frameErrors = handle->streamInfo.cook.ui32TotalFramesInError;
        pStatus->dummyFrames = handle->streamInfo.cook.ui32TotalFramesDummy;
    }

    return BERR_SUCCESS;
}

static BERR_Code BAPE_Decoder_P_GetLpcmStatus(
    BAPE_DecoderHandle handle, 
    unsigned mode, 
    const BDSP_AudioBitRateChangeInfo *pBitRateInfo, 
    BAPE_DecoderStatus *pStatus
    )
{
    BERR_Code errCode;

    BSTD_UNUSED(mode);
    BSTD_UNUSED(pBitRateInfo);

    if ( !handle->passthrough )
    {
        errCode = BDSP_Stage_GetStatus(handle->hPrimaryStage, &handle->streamInfo.lpcm, sizeof(handle->streamInfo.lpcm));
        if ( errCode )
        {
            return errCode;
        }

        pStatus->framesDecoded = handle->streamInfo.lpcm.ui32TotalFramesDecoded;
        pStatus->frameErrors = handle->streamInfo.lpcm.ui32TotalFramesInError;
        pStatus->dummyFrames = handle->streamInfo.lpcm.ui32TotalFramesDummy;
    }

    return BERR_SUCCESS;
}

static BERR_Code BAPE_Decoder_P_GetMlpStatus(
    BAPE_DecoderHandle handle, 
    unsigned mode, 
    const BDSP_AudioBitRateChangeInfo *pBitRateInfo, 
    BAPE_DecoderStatus *pStatus
    )
{
    BERR_Code errCode;

    BSTD_UNUSED(mode);
    BSTD_UNUSED(pBitRateInfo);

    if ( !handle->passthrough )
    {
        errCode = BDSP_Stage_GetStatus(handle->hPrimaryStage, &handle->streamInfo.mlp, sizeof(handle->streamInfo.mlp));
        if ( errCode )
        {
            return errCode;
        }

        pStatus->framesDecoded = handle->streamInfo.mlp.ui32TotalFramesDecoded;
        pStatus->frameErrors = handle->streamInfo.mlp.ui32TotalFramesInError;
        pStatus->dummyFrames = handle->streamInfo.mlp.ui32TotalFramesDummy;
    }

    return BERR_SUCCESS;
}

static BERR_Code BAPE_Decoder_P_GetAdpcmStatus(
    BAPE_DecoderHandle handle, 
    unsigned mode, 
    const BDSP_AudioBitRateChangeInfo *pBitRateInfo, 
    BAPE_DecoderStatus *pStatus
    )
{
    BERR_Code errCode;

    BSTD_UNUSED(mode);
    BSTD_UNUSED(pBitRateInfo);

    if ( !handle->passthrough )
    {
        errCode = BDSP_Stage_GetStatus(handle->hPrimaryStage, &handle->streamInfo.adpcm, sizeof(handle->streamInfo.adpcm));
        if ( errCode )
        {
            return errCode;
        }

        pStatus->framesDecoded = handle->streamInfo.adpcm.ui32TotalFramesDecoded;
        pStatus->frameErrors = handle->streamInfo.adpcm.ui32TotalFramesInError;
        pStatus->dummyFrames = handle->streamInfo.adpcm.ui32TotalFramesDummy;
    }

    return BERR_SUCCESS;
}

static BERR_Code BAPE_Decoder_P_GetG711G726Status(
    BAPE_DecoderHandle handle, 
    unsigned mode, 
    const BDSP_AudioBitRateChangeInfo *pBitRateInfo, 
    BAPE_DecoderStatus *pStatus
    )
{
    BERR_Code errCode;

    BSTD_UNUSED(mode);
    BSTD_UNUSED(pBitRateInfo);

    if ( !handle->passthrough )
    {
        errCode = BDSP_Stage_GetStatus(handle->hPrimaryStage, &handle->streamInfo.g711g726, sizeof(handle->streamInfo.g711g726));
        if ( errCode )
        {
            return errCode;
        }

        pStatus->framesDecoded = handle->streamInfo.g711g726.ui32TotalFramesDecoded;
        pStatus->frameErrors = handle->streamInfo.g711g726.ui32TotalFramesInError;
        pStatus->dummyFrames = handle->streamInfo.g711g726.ui32TotalFramesDummy;
    }

    return BERR_SUCCESS;
}

static BERR_Code BAPE_Decoder_P_GetG729Status(
    BAPE_DecoderHandle handle, 
    unsigned mode, 
    const BDSP_AudioBitRateChangeInfo *pBitRateInfo, 
    BAPE_DecoderStatus *pStatus
    )
{
    BERR_Code errCode;

    BSTD_UNUSED(mode);
    BSTD_UNUSED(pBitRateInfo);

    if ( !handle->passthrough )
    {
        errCode = BDSP_Stage_GetStatus(handle->hPrimaryStage, &handle->streamInfo.g729, sizeof(handle->streamInfo.g729));
        if ( errCode )
        {
            return errCode;
        }

        pStatus->framesDecoded = handle->streamInfo.g729.ui32TotalFramesDecoded;
        pStatus->frameErrors = handle->streamInfo.g729.ui32TotalFramesInError;
        pStatus->dummyFrames = handle->streamInfo.g729.ui32TotalFramesDummy;
    }

    return BERR_SUCCESS;
}

static BERR_Code BAPE_Decoder_P_GetG723_1Status(
    BAPE_DecoderHandle handle, 
    unsigned mode, 
    const BDSP_AudioBitRateChangeInfo *pBitRateInfo, 
    BAPE_DecoderStatus *pStatus
    )
{
    BERR_Code errCode;

    BSTD_UNUSED(mode);
    BSTD_UNUSED(pBitRateInfo);

    if ( !handle->passthrough )
    {
        errCode = BDSP_Stage_GetStatus(handle->hPrimaryStage, &handle->streamInfo.g723, sizeof(handle->streamInfo.g723));
        if ( errCode )
        {
            return errCode;
        }

        pStatus->framesDecoded = handle->streamInfo.g723.ui32TotalFramesDecoded;
        pStatus->frameErrors = handle->streamInfo.g723.ui32TotalFramesInError;
        pStatus->dummyFrames = handle->streamInfo.g723.ui32TotalFramesDummy;
    }

    return BERR_SUCCESS;
}

static BERR_Code BAPE_Decoder_P_GetVorbisStatus(
    BAPE_DecoderHandle handle, 
    unsigned mode, 
    const BDSP_AudioBitRateChangeInfo *pBitRateInfo, 
    BAPE_DecoderStatus *pStatus
    )
{
    BERR_Code errCode;

    BSTD_UNUSED(mode);
    BSTD_UNUSED(pBitRateInfo);

    if ( !handle->passthrough )
    {
        errCode = BDSP_Stage_GetStatus(handle->hPrimaryStage, &handle->streamInfo.vorbis, sizeof(handle->streamInfo.vorbis));
        if ( errCode )
        {
            return errCode;
        }

        pStatus->framesDecoded = handle->streamInfo.vorbis.ui32TotalFramesDecoded;
        pStatus->frameErrors = handle->streamInfo.vorbis.ui32TotalFramesInError;
        pStatus->dummyFrames = handle->streamInfo.vorbis.ui32TotalFramesDummy;
    }

    return BERR_SUCCESS;
}

static BERR_Code BAPE_Decoder_P_GetApeStatus(
    BAPE_DecoderHandle handle, 
    unsigned mode, 
    const BDSP_AudioBitRateChangeInfo *pBitRateInfo, 
    BAPE_DecoderStatus *pStatus
    )
{
    BERR_Code errCode;

    BSTD_UNUSED(mode);
    BSTD_UNUSED(pBitRateInfo);

    if ( !handle->passthrough )
    {
        errCode = BDSP_Stage_GetStatus(handle->hPrimaryStage, &handle->streamInfo.ape, sizeof(handle->streamInfo.ape));
        if ( errCode )
        {
            return errCode;
        }

        pStatus->framesDecoded = handle->streamInfo.ape.ui32TotalFramesDecoded;
        pStatus->frameErrors = handle->streamInfo.ape.ui32TotalFramesInError;
        pStatus->dummyFrames = handle->streamInfo.ape.ui32TotalFramesDummy;
    }

    return BERR_SUCCESS;
}

static BERR_Code BAPE_Decoder_P_GetFlacStatus(
    BAPE_DecoderHandle handle, 
    unsigned mode, 
    const BDSP_AudioBitRateChangeInfo *pBitRateInfo, 
    BAPE_DecoderStatus *pStatus
    )
{
    BERR_Code errCode;

    BSTD_UNUSED(mode);
    BSTD_UNUSED(pBitRateInfo);

    if ( !handle->passthrough )
    {
        errCode = BDSP_Stage_GetStatus(handle->hPrimaryStage, &handle->streamInfo.flac, sizeof(handle->streamInfo.flac));
        if ( errCode )
        {
            return errCode;
        }

        pStatus->framesDecoded = handle->streamInfo.flac.ui32TotalFramesDecoded;
        pStatus->frameErrors = handle->streamInfo.flac.ui32TotalFramesInError;
        pStatus->dummyFrames = handle->streamInfo.flac.ui32TotalFramesDummy;
    }

    return BERR_SUCCESS;
}

static BERR_Code BAPE_Decoder_P_GetGenericStatus(
    BAPE_DecoderHandle handle,
    unsigned mode,
    const BDSP_AudioBitRateChangeInfo *pBitRateInfo,
    BAPE_DecoderStatus *pStatus
    )
{
    BERR_Code errCode;

    BSTD_UNUSED(mode);
    BSTD_UNUSED(pBitRateInfo);

    if ( !handle->passthrough )
    {
        errCode = BDSP_Stage_GetStatus(handle->hPrimaryStage, &handle->streamInfo.generic, sizeof(handle->streamInfo.generic));

        if ( errCode )
        {
            return errCode;
        }

        pStatus->framesDecoded = handle->streamInfo.generic.ui32TotalFramesPassed;
        pStatus->dummyFrames = handle->streamInfo.generic.ui32TotalFramesDummy;
        pStatus->sampleRate = BAPE_P_BDSPSampleFrequencyToInt(handle->streamInfo.generic.ui32SamplingFreq);
    }
    return BERR_SUCCESS;
}

static BERR_Code BAPE_Decoder_P_GetIlbcStatus(
    BAPE_DecoderHandle handle, 
    unsigned mode, 
    const BDSP_AudioBitRateChangeInfo *pBitRateInfo, 
    BAPE_DecoderStatus *pStatus
    )
{
    BERR_Code errCode;

    BSTD_UNUSED(mode);
    BSTD_UNUSED(pBitRateInfo);

    if ( !handle->passthrough )
    {
        errCode = BDSP_Stage_GetStatus(handle->hPrimaryStage, &handle->streamInfo.ilbc, sizeof(handle->streamInfo.ilbc));
        if ( errCode )
        {
            return errCode;
        }

        pStatus->framesDecoded = handle->streamInfo.ilbc.ui32TotalFramesDecoded;
        pStatus->frameErrors = handle->streamInfo.ilbc.ui32TotalFramesInError;
        pStatus->dummyFrames = handle->streamInfo.ilbc.ui32TotalFramesDummy;
    }

    return BERR_SUCCESS;
}

static BERR_Code BAPE_Decoder_P_GetIsacStatus(
    BAPE_DecoderHandle handle, 
    unsigned mode, 
    const BDSP_AudioBitRateChangeInfo *pBitRateInfo, 
    BAPE_DecoderStatus *pStatus
    )
{
    BERR_Code errCode;

    BSTD_UNUSED(mode);
    BSTD_UNUSED(pBitRateInfo);

    if ( !handle->passthrough )
    {
        errCode = BDSP_Stage_GetStatus(handle->hPrimaryStage, &handle->streamInfo.isac, sizeof(handle->streamInfo.isac));
        if ( errCode )
        {
            return errCode;
        }

        pStatus->framesDecoded = handle->streamInfo.isac.ui32TotalFramesDecoded;
        pStatus->frameErrors = handle->streamInfo.isac.ui32TotalFramesInError;
        pStatus->dummyFrames = handle->streamInfo.isac.ui32TotalFramesDummy;
    }

    return BERR_SUCCESS;
}

static BERR_Code BAPE_Decoder_P_GetOpusStatus(
    BAPE_DecoderHandle handle,
    unsigned mode,
    const BDSP_AudioBitRateChangeInfo *pBitRateInfo,
    BAPE_DecoderStatus *pStatus
    )
{
    BERR_Code errCode;

    BSTD_UNUSED(mode);
    BSTD_UNUSED(pBitRateInfo);

    if ( !handle->passthrough )
    {
        errCode = BDSP_Stage_GetStatus(handle->hPrimaryStage, &handle->streamInfo.opus, sizeof(handle->streamInfo.opus));
        if ( errCode )
        {
            return errCode;
        }

        pStatus->framesDecoded = handle->streamInfo.opus.ui32TotalFramesDecoded;
        pStatus->frameErrors = handle->streamInfo.opus.ui32TotalFramesInError;
        pStatus->dummyFrames = handle->streamInfo.opus.ui32TotalFramesDummy;
    }

    return BERR_SUCCESS;
}

static BERR_Code BAPE_Decoder_P_GetAlsStatus(
    BAPE_DecoderHandle handle,
    unsigned mode,
    const BDSP_AudioBitRateChangeInfo *pBitRateInfo,
    BAPE_DecoderStatus *pStatus
    )
{
    BERR_Code errCode;

    BSTD_UNUSED(mode);
    BSTD_UNUSED(pBitRateInfo);

    if ( !handle->passthrough )
    {
        errCode = BDSP_Stage_GetStatus(handle->hPrimaryStage, &handle->streamInfo.als, sizeof(handle->streamInfo.als));
        if ( errCode )
        {
            return errCode;
        }

        pStatus->framesDecoded = handle->streamInfo.als.ui32TotalFramesDecoded;
        pStatus->frameErrors = handle->streamInfo.als.ui32TotalFramesInError;
        pStatus->dummyFrames = handle->streamInfo.als.ui32TotalFramesDummy;
    }
    return BERR_SUCCESS;
}

BERR_Code BAPE_Decoder_P_GetCodecStatus(BAPE_DecoderHandle handle, BAPE_DecoderStatus *pStatus)
{
    unsigned mode;
    BDSP_AudioBitRateChangeInfo bitRateInfo;

    BDBG_OBJECT_ASSERT(handle, BAPE_Decoder);
    BDBG_ASSERT(NULL != pStatus);

    if ( handle->state == BAPE_DecoderState_eStopped )
    {
        return BERR_SUCCESS;
    }

    /* Atomically save params updated at isr time */
    BKNI_EnterCriticalSection();
    mode = handle->mode;
    BKNI_Memcpy(&bitRateInfo, &handle->bitRateInfo, sizeof(bitRateInfo));
    BKNI_LeaveCriticalSection();

    pStatus->mode = BAPE_Decoder_P_ChannelModeFromDsp(mode);
    switch ( handle->startSettings.codec )
    {
    case BAVC_AudioCompressionStd_eMpegL1:
    case BAVC_AudioCompressionStd_eMpegL2:
    case BAVC_AudioCompressionStd_eMpegL3:
        return BAPE_Decoder_P_GetMpegStatus(handle, mode, &bitRateInfo, pStatus);
    case BAVC_AudioCompressionStd_eAc3:
    case BAVC_AudioCompressionStd_eAc3Plus:
        return BAPE_Decoder_P_GetAc3Status(handle, mode, &bitRateInfo, pStatus);
    case BAVC_AudioCompressionStd_eAacAdts:
    case BAVC_AudioCompressionStd_eAacLoas:
    case BAVC_AudioCompressionStd_eAacPlusAdts:
    case BAVC_AudioCompressionStd_eAacPlusLoas:
        return BAPE_Decoder_P_GetAacStatus(handle, mode, &bitRateInfo, pStatus);
    case BAVC_AudioCompressionStd_eWmaStd:
    case BAVC_AudioCompressionStd_eWmaStdTs:
        return BAPE_Decoder_P_GetWmaStatus(handle, mode, &bitRateInfo, pStatus);
    case BAVC_AudioCompressionStd_eWmaPro:
        return BAPE_Decoder_P_GetWmaProStatus(handle, mode, &bitRateInfo, pStatus);
    case BAVC_AudioCompressionStd_eDts:
    case BAVC_AudioCompressionStd_eDtsHd:
    case BAVC_AudioCompressionStd_eDtsCd:
        return BAPE_Decoder_P_GetDtsStatus(handle, mode, &bitRateInfo, pStatus);
    case BAVC_AudioCompressionStd_eDtsExpress:
        return BAPE_Decoder_P_GetDtsExpressStatus(handle, mode, &bitRateInfo, pStatus);
    case BAVC_AudioCompressionStd_ePcmWav:
        return BAPE_Decoder_P_GetPcmWavStatus(handle, mode, &bitRateInfo, pStatus);
    case BAVC_AudioCompressionStd_eAmrNb:
        return BAPE_Decoder_P_GetAmrStatus(handle, mode, &bitRateInfo, pStatus);
    case BAVC_AudioCompressionStd_eAmrWb:
        return BAPE_Decoder_P_GetAmrWbStatus(handle, mode, &bitRateInfo, pStatus);
    case BAVC_AudioCompressionStd_eDra:
        return BAPE_Decoder_P_GetDraStatus(handle, mode, &bitRateInfo, pStatus);
    case BAVC_AudioCompressionStd_eCook:
        return BAPE_Decoder_P_GetCookStatus(handle, mode, &bitRateInfo, pStatus);
    case BAVC_AudioCompressionStd_eLpcmDvd:
    case BAVC_AudioCompressionStd_eLpcmBd:
    case BAVC_AudioCompressionStd_eLpcm1394:
        return BAPE_Decoder_P_GetLpcmStatus(handle, mode, &bitRateInfo, pStatus);
    case BAVC_AudioCompressionStd_eAdpcm:
        return BAPE_Decoder_P_GetAdpcmStatus(handle, mode, &bitRateInfo, pStatus);
    case BAVC_AudioCompressionStd_eMlp:
        return BAPE_Decoder_P_GetMlpStatus(handle, mode, &bitRateInfo, pStatus);
    case BAVC_AudioCompressionStd_eG711:
    case BAVC_AudioCompressionStd_eG726:
        return BAPE_Decoder_P_GetG711G726Status(handle, mode, &bitRateInfo, pStatus);
    case BAVC_AudioCompressionStd_eG729:
        return BAPE_Decoder_P_GetG729Status(handle, mode, &bitRateInfo, pStatus);
    case BAVC_AudioCompressionStd_eG723_1:
        return BAPE_Decoder_P_GetG723_1Status(handle, mode, &bitRateInfo, pStatus);
    case BAVC_AudioCompressionStd_eVorbis:
        return BAPE_Decoder_P_GetVorbisStatus(handle, mode, &bitRateInfo, pStatus);
    case BAVC_AudioCompressionStd_eApe:
        return BAPE_Decoder_P_GetApeStatus(handle, mode, &bitRateInfo, pStatus);
    case BAVC_AudioCompressionStd_eFlac:
        return BAPE_Decoder_P_GetFlacStatus(handle, mode, &bitRateInfo, pStatus);
    case BAVC_AudioCompressionStd_ePcm:
        return BAPE_Decoder_P_GetGenericStatus(handle, mode, &bitRateInfo, pStatus);
    case BAVC_AudioCompressionStd_eIlbc:
        return BAPE_Decoder_P_GetIlbcStatus(handle, mode, &bitRateInfo, pStatus);
    case BAVC_AudioCompressionStd_eIsac:
        return BAPE_Decoder_P_GetIsacStatus(handle, mode, &bitRateInfo, pStatus);
    case BAVC_AudioCompressionStd_eOpus:
        return BAPE_Decoder_P_GetOpusStatus(handle, mode, &bitRateInfo, pStatus);
    case BAVC_AudioCompressionStd_eAls:
        return BAPE_Decoder_P_GetAlsStatus(handle, mode, &bitRateInfo, pStatus);
    default:
        return BERR_SUCCESS;
    }
}

BERR_Code BAPE_Decoder_P_GetDataSyncStatus_isr(BAPE_DecoderHandle handle, unsigned *underflowCount)
{
    BDSP_AudioTaskDatasyncStatus status;
    BERR_Code errCode;

    BDBG_OBJECT_ASSERT(handle, BAPE_Decoder);

    errCode = BDSP_AudioStage_GetDatasyncStatus_isr(handle->hPrimaryStage, &status);
    if (errCode)
    {
        *underflowCount = 0;
        return errCode;
    }

    if (status.ui32StatusValid == 0) /* ui32StatusValid of 0 means valid */
    {
        *underflowCount = status.ui32CDBUuderFlowCount;
    }
    else
    {
        *underflowCount = 0;
    }
    return BERR_SUCCESS;
}
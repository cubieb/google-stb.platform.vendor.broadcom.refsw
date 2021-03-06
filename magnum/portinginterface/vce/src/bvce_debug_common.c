/***************************************************************************
 *     Copyright (c) 2003-2014, Broadcom Corporation
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
 * [File Description:]
 *
 * Revision History:
 *
 * $brcm_Log: $
 *
 ***************************************************************************/

/* base modules */
#include "bstd.h"           /* standard types */
#include "berr.h"           /* error code */
#include "bdbg.h"           /* debug interface */

#include "bvce_debug_common.h"

const char* const BVCE_P_StatusLUT[] =
{
   BDBG_STRING_INLINE("ERR_OK"),
   BDBG_STRING_INLINE("ERR_UNKNOWN_COMMAND_ID"),
   BDBG_STRING_INLINE("ERR_NO_RESOURCES"),
   BDBG_STRING_INLINE("ERR_INVALID_CHANNEL_ID"),
   BDBG_STRING_INLINE("ERR_NULL_ADDRESS"),
   BDBG_STRING_INLINE("ERR_SECURE_BUFFER_SIZE_IS_TOO_SMALL"),
   BDBG_STRING_INLINE("ERR_IN_CDB_OR_ITB_BUFFER"),
   BDBG_STRING_INLINE("ERR_ENCODER_BUFFER_SIZE_IS_TOO_SMALL"),
   BDBG_STRING_INLINE("ERR_CHANNEL_IS_ALREADY_INITIALIZED"),
   BDBG_STRING_INLINE("ERR_CHANNEL_IS_ALREADY_OPENED"),
   BDBG_STRING_INLINE("ERR_CHANNEL_WAS_NOT_INITIALIZED"),
   BDBG_STRING_INLINE("ERR_CHANNEL_WAS_NOT_OPENED"),
   BDBG_STRING_INLINE("ERR_VICE_IS_IN_FLUSHING_MODE"),
   BDBG_STRING_INLINE("ERR_CHANNEL_IS_ALREADY_STARTED"),
   BDBG_STRING_INLINE("ERR_CHANNEL_WAS_NOT_CONFIGURED"),
   BDBG_STRING_INLINE("ERR_CHANNEL_WAS_NOT_STARTED"),
   BDBG_STRING_INLINE("ERR_CHANNEL_WAS_NOT_STOPPED"),
   BDBG_STRING_INLINE("ERR_UNSUPPORTED_FRAME_RATE"),
   BDBG_STRING_INLINE("ERR_UNSUPPORTED_DEE"),
   BDBG_STRING_INLINE("ERR_FRAMERATE_CHANGE_INVALID_IN_INTERLACE"),
   BDBG_STRING_INLINE("ERR_UNSUPPORTED_INTERLACED_TYPE_LOW_DELAY"),
   BDBG_STRING_INLINE("ERR_UNSUPPORTED_B_PICTURES_IN_LOW_DELAY"),
   BDBG_STRING_INLINE("ERR_UNSUPPORTED_B_PICTURES_IN_STD"),
   BDBG_STRING_INLINE("ERR_UNSUPPORTED_INTERLACED_IN_STD"),
   BDBG_STRING_INLINE("ERR_INVALID_DEBUG_COMMAND"),
   BDBG_STRING_INLINE("ERR_SG_CMD_BUFFER_SIZE_IS_TOO_SMALL"),
   BDBG_STRING_INLINE("ERR_MAX_RESOLUTION_ERROR"),
   BDBG_STRING_INLINE("ERR_MAX_FRAMERATE_LIMIT_TOO_LARGE"),
   BDBG_STRING_INLINE("ERR_MIN_FRAMERATE_LIMIT_TOO_SMALL"),
   BDBG_STRING_INLINE("ERR_MIN_BVN_FRAMERATE_LIMIT_TOO_SMALL"),
   BDBG_STRING_INLINE("ERR_FRAMERATE_LESS_THAN_LIMIT"),
   BDBG_STRING_INLINE("ERR_FRAMERATE_MORE_THAN_LIMIT"),
   BDBG_STRING_INLINE("ERR_WRONG_GOP_LENGTH"),
   BDBG_STRING_INLINE("ERR_DEBUG_COMMAND_USE_IN_INVALID_STATE"),
   BDBG_STRING_INLINE("ERR_MULTIPLE_SLICES_NOT_SUPPORTED"),
   BDBG_STRING_INLINE("ERR_INVALID_FORCE_INTRA_CONFIGURATION"),
   BDBG_STRING_INLINE("ERR_LOW_DELAY_SUPPORTED_ONLY_CHANNEL_0"),
   BDBG_STRING_INLINE("ERR_LOW_DELAY_UNSUPPORTED_ON_TARGET"),
   BDBG_STRING_INLINE("ERR_RESTART_GOP_SCENE_INVALID_GOP"),
   BDBG_STRING_INLINE("ERR_ITFP_INVALID_IN_LOW_DELAY"),
   BDBG_STRING_INLINE("ERR_TARGET_BITRATE_LARGER_MAX"),
   BDBG_STRING_INLINE("ERR_WRONG_NUM_PARALLEL_ENC"),
   BDBG_STRING_INLINE("ERR_UNSUPPORTED_FINITE_GOP_IN_LOW_DELAY"),
   BDBG_STRING_INLINE("ERR_MAX_NUM_CH_NOT_SUPPORTED"),
   BDBG_STRING_INLINE("ERR_MAX_NUM_CH_INCONSISTENT"),
   BDBG_STRING_INLINE("ERR_UNSUPPORTED_ENCODING_STD"),
   BDBG_STRING_INLINE("ERR_INVALID_OPEN_GOP_IN_GOP_STRUCTURE"),
   BDBG_STRING_INLINE("ERR_DCXV_NOT_SUPPORTED"),
   BDBG_STRING_INLINE("ERR_NON_SECURE_NOT_ALIGNED"),
   BDBG_STRING_INLINE("ERR_SECURE_NOT_ALIGNED"),
   BDBG_STRING_INLINE("ERR_CMD_BUFFER_NOT_ALIGNED"),
   BDBG_STRING_INLINE("ERR_VICE_IS_IN_CHANNEL_FLUSHING_MODE"),
   BDBG_STRING_INLINE("ERR_VICE_IS_IN_CABAC_FLUSHING_MODE"),
   BDBG_STRING_INLINE("ERR_VARIABLE_BITRATE_UNSUPPORTED"),
};

const char* const BVCE_P_ErrorLUT[32] =
{
   BDBG_STRING_INLINE("ERR_INVALID_INPUT_DIMENSION"),
   BDBG_STRING_INLINE("ERR_USER_DATA_LATE"),
   BDBG_STRING_INLINE("ERR_USER_DATA_DUPLICATE"),
   BDBG_STRING_INLINE("ERR_ADJUSTS_WRONG_FRAME_RATE"),
   BDBG_STRING_INLINE("ERR_UNSUPPORTED_BVN_FRAME_RATE"),
   BDBG_STRING_INLINE("ERR_UNSUPPORTED_RESOLUTION"),
   BDBG_STRING_INLINE("ERR_MISMATCH_BVN_MIN_FRAME_RATE"),
   BDBG_STRING_INLINE("ERR_MISMATCH_BVN_PIC_RESOLUTION"),
   BDBG_STRING_INLINE("ERR_MAX_BITRATE_EXCEEDED"),
   BDBG_STRING_INLINE("ERR_BIN_BUFFER_FULL"),
   BDBG_STRING_INLINE("ERR_CDB_FULL"),
   BDBG_STRING_INLINE("ERR_PICARC_TO_CABAC_DINO_BUFFER_FULL"),
   BDBG_STRING_INLINE("ERR_EBM_FULL"),
   BDBG_STRING_INLINE("ERR_MAX_NUM_SLICES_EXCEEDED"),
   BDBG_STRING_INLINE("ERR_MAX_NUM_ENTRIES_INTRACODED_EXCEEDED"),
   BDBG_STRING_INLINE("ERR_IBBP_NOT_SUPPORTED_FOR_RESOLUTION"),
   BDBG_STRING_INLINE("ERR_MBARC_BOOT_FAILURE"),
   BDBG_STRING_INLINE("ERR_MEASURED_ENCODER_DELAY_TOO_LONG"),
   BDBG_STRING_INLINE("ERR_CRITICAL"),
   BDBG_STRING_INLINE("ERR_UNSUPPORTED_DISPLAY_FMT_IN_3_CH_MODE"),
   BDBG_STRING_INLINE("ERR_UNSUPPORTED_DISPLAY_FMT_IN_2_CH_MODE"),
   BDBG_STRING_INLINE("ERR_RESOLUTION_IS_TOO_HIGH_FOR_THIS_LEVEL"),
};

const char* const BVCE_P_EventLUT[32] =
{
   BDBG_STRING_INLINE("INPUT_CHANGE"),
   BDBG_STRING_INLINE("EOS"),
};

const BVCE_P_CommandDebug BVCE_P_CommandLUT[] =
{
   {
    VICE_CMD_INITIALIZE,
    {
      BDBG_STRING_INLINE("Command (Init)"),
      BDBG_STRING_INLINE("API version"),
      BDBG_STRING_INLINE("Endianess"),
      BDBG_STRING_INLINE("CABAC Command Buffer Base"),
      BDBG_STRING_INLINE("CABAC Command Buffer Size"),
      BDBG_STRING_INLINE("Verification Mode"),
      BDBG_STRING_INLINE("Stripe Width"),
      BDBG_STRING_INLINE("X"),
      BDBG_STRING_INLINE("Y"),
      BDBG_STRING_INLINE("MEMC Type"),
      BDBG_STRING_INLINE("Bank Type"),
      BDBG_STRING_INLINE("Page Size"),
    },
    {
      BDBG_STRING_INLINE("Response (Init)"),
      BDBG_STRING_INLINE("Status"),
      BDBG_STRING_INLINE("Firmware Version"),
      BDBG_STRING_INLINE("Debug Buffer Info Base (PicArc)"),
      BDBG_STRING_INLINE("Debug Buffer Info Base (MBArc)"),
      BDBG_STRING_INLINE("Channel Error Status Base"),
      BDBG_STRING_INLINE("FW API Version"),
      BDBG_STRING_INLINE("Version String"),
      BDBG_STRING_INLINE("BVN API Version"),
      BDBG_STRING_INLINE("Watchdog Error Code Base (PicArc)"),
      BDBG_STRING_INLINE("Watchdog Error Code Base (MBArc)"),
    },
    sizeof( ViceCmdInit_t )/sizeof( uint32_t ),
    sizeof( ViceCmdInitResponse_t )/sizeof( uint32_t )
   },

   {
    VICE_CMD_OPEN_CHANNEL,
    {
      BDBG_STRING_INLINE("Command (Open)"),
      BDBG_STRING_INLINE("Channel ID"),
      BDBG_STRING_INLINE("Non-Secure Buffer Base"),
      BDBG_STRING_INLINE("Non-Secure Buffer Size"),
      BDBG_STRING_INLINE("Secure Buffer Base"),
      BDBG_STRING_INLINE("Secure Buffer Size"),
      BDBG_STRING_INLINE("Max Number of Channels"),
    },
    {
      BDBG_STRING_INLINE("Response (Open)"),
      BDBG_STRING_INLINE("Status"),
      BDBG_STRING_INLINE("User Data Queue Info Base"),
    },
    sizeof( ViceCmdOpenChannel_t )/sizeof( uint32_t ) ,
    sizeof( ViceCmdOpenChannelResponse_t )/sizeof( uint32_t )
   },

   {
    VICE_CMD_START_CHANNEL,
    {
      BDBG_STRING_INLINE("Command (Start)"),
      BDBG_STRING_INLINE("Channel ID"),
    },
    {
      BDBG_STRING_INLINE("Response (Start)"),
      BDBG_STRING_INLINE("Status"),
    },
    sizeof( ViceCmdStartChannel_t )/sizeof( uint32_t ),
    2
   },

   {
    VICE_CMD_STOP_CHANNEL,
    {
      BDBG_STRING_INLINE("Command (Stop)"),
      BDBG_STRING_INLINE("Channel ID"),
      BDBG_STRING_INLINE("Flags"),
    },
    {
      BDBG_STRING_INLINE("Response (Stop)"),
      BDBG_STRING_INLINE("Status"),
    },
    sizeof( ViceCmdStopChannel_t )/sizeof( uint32_t ),
    2
   },

   {
    VICE_CMD_CLOSE_CHANNEL,
    {
      BDBG_STRING_INLINE("Command (Close)"),
      BDBG_STRING_INLINE("Channel ID"),
    },
    {
      BDBG_STRING_INLINE("Response (Close)"),
      BDBG_STRING_INLINE("Status"),
    },
    sizeof( ViceCmdCloseChannel_t )/sizeof( uint32_t ),
    2
   },

   {
    VICE_CMD_CONFIG_CHANNEL,
    {
      BDBG_STRING_INLINE("Command (Config)"),
      BDBG_STRING_INLINE("Channel ID"),
      BDBG_STRING_INLINE("Protocol"),
      BDBG_STRING_INLINE("Profile"),
      BDBG_STRING_INLINE("Level"),
      BDBG_STRING_INLINE("Frame Rate"),
      BDBG_STRING_INLINE("Bit Rate (Max)"),
      BDBG_STRING_INLINE("GOP Structure"),
      BDBG_STRING_INLINE("GOP Length"),
      BDBG_STRING_INLINE("Mode"),
      BDBG_STRING_INLINE("Input Type"),
      BDBG_STRING_INLINE("Event Mask"),
      BDBG_STRING_INLINE("Flags"),
      BDBG_STRING_INLINE("STC Index"),
      BDBG_STRING_INLINE("Context ID"),
      BDBG_STRING_INLINE("ITB Buffer Offset"),
      BDBG_STRING_INLINE("ITB Buffer Size"),
      BDBG_STRING_INLINE("CDB Buffer Offset"),
      BDBG_STRING_INLINE("CDB Buffer Size"),
      BDBG_STRING_INLINE("A2P Delay"),
      BDBG_STRING_INLINE("Min/Max Frame Rate"),
      BDBG_STRING_INLINE("Rate Buffer Delay"),
      BDBG_STRING_INLINE("BVN Frame Rate"),
      BDBG_STRING_INLINE("Max Width/Height"),
      BDBG_STRING_INLINE("Max GOP Structure"),
      BDBG_STRING_INLINE("Number of Slices Per Picture"),
      BDBG_STRING_INLINE("Force Intra Mode Settings"),
      BDBG_STRING_INLINE("Bit Rate (Target)"),
      BDBG_STRING_INLINE("Number of Parallel Encodes (FNRT)"),
      BDBG_STRING_INLINE("Segment Duration"),
      BDBG_STRING_INLINE("Segment Settings"),
    },
    {
      BDBG_STRING_INLINE("Response (Config)"),
      BDBG_STRING_INLINE("Status"),
    },
    sizeof( ViceCmdConfigChannel_t )/sizeof( uint32_t ),
    2
   },

   {
    VICE_CMD_DEBUG_CHANNEL,
    {
      BDBG_STRING_INLINE("Command (Debug)"),
      BDBG_STRING_INLINE("Channel ID"),
      BDBG_STRING_INLINE("Arc ID"),
      BDBG_STRING_INLINE("Command[0..32]"),
    },
    {
      BDBG_STRING_INLINE("Response (Debug)"),
      BDBG_STRING_INLINE("Status"),
    },
    sizeof( ViceCmdDebugChannel_t )/sizeof( uint32_t ),
    2
   },

   {
    VICE_CMD_GET_CHANNEL_STATUS,
    {
      BDBG_STRING_INLINE("Command (Status)"),
      BDBG_STRING_INLINE("Channel ID"),
    },
    {
      BDBG_STRING_INLINE("Response (Status)"),
      BDBG_STRING_INLINE("Status"),
      BDBG_STRING_INLINE("Status Info: Error Flags"),
      BDBG_STRING_INLINE("Status Info: Total Errors"),
      BDBG_STRING_INLINE("Status Info: Pics Encoded"),
      BDBG_STRING_INLINE("Status Info: Pics Configured"),
      BDBG_STRING_INLINE("Status Info: Pics Dropped (FRC)"),
      BDBG_STRING_INLINE("Status Info: Pics Dropped (Performance)"),
      BDBG_STRING_INLINE("Status Info: Pics Dropped (Not Started)"),
      BDBG_STRING_INLINE("Status Info: Last Picture ID Encoded"),
      BDBG_STRING_INLINE("Status Info: FW State"),
      BDBG_STRING_INLINE("Status Info: Picture Loop Status"),
      BDBG_STRING_INLINE("Status Info: STC Snapshot (LSB)"),
      BDBG_STRING_INLINE("Status Info: STC Snapshot (MSB)"),
      BDBG_STRING_INLINE("Status Info: Pics Dropped (HRD Underflow)"),
      BDBG_STRING_INLINE("Status Info: ETS/DTS Offset"),
      BDBG_STRING_INLINE("Status Info: Throughput"),
    },
    sizeof( ViceCmdGetChannelStatus_t )/sizeof( uint32_t ),
    sizeof( ViceCmdGetChannelStatusResponse_t )/sizeof( uint32_t ),
   },
};
const unsigned int BVCE_P_CommandLUT_size = sizeof( BVCE_P_CommandLUT );

const char* const BVCE_P_Debug_EntryTypeLUT[BVCE_DebugFifo_EntryType_eMax] =
{
   BDBG_STRING_INLINE("CFG"),
   BDBG_STRING_INLINE("STS"),
   BDBG_STRING_INLINE("BUF"),
   BDBG_STRING_INLINE("MTA"),
   BDBG_STRING_INLINE("ITB"),
   BDBG_STRING_INLINE("CMD"),
   BDBG_STRING_INLINE("RSP"),
   BDBG_STRING_INLINE("TRC"),
};

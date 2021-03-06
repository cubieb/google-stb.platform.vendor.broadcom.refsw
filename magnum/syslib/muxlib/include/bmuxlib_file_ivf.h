/******************************************************************************
 * (c) 2010-2015 Broadcom Corporation
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


#ifndef BMUXLIB_FILE_IVF_H__
#define BMUXLIB_FILE_IVF_H__

/* Includes */
#include "bmuxlib.h"
#include "bmuxlib_file.h"
#include "bmuxlib_output.h"

#ifdef __cplusplus
extern "C" {
#endif

/****************************
*      D E F I N E S        *
****************************/

/****************************
*        T Y P E S          *
****************************/

typedef struct
{
   uint32_t uiSignature;                     /* [DO NOT MODIFY] Populated by BMUXlib_File_IVF_GetDefaultCreateSettings() */
} BMUXlib_File_IVF_CreateSettings;

typedef struct
{
   uint32_t uiSignature;                     /* [DO NOT MODIFY] Populated by BMUXlib_File_IVF_GetDefaultStartSettings() */

   BMUXlib_VideoEncoderInterface stInterface;

   /*
      Output Interface:
   */
   BMUXlib_StorageObjectInterface stOutput;  /* final destination output "file" */
} BMUXlib_File_IVF_StartSettings;

typedef struct
{
   uint32_t uiSignature;                     /* [DO NOT MODIFY] Populated by BMUXlib_File_IVF_GetDefaultStartSettings() */

   BMUXlib_FinishMode eFinishMode;           /* mode of finish (e.g. "finalize file" or "immediate stop", etc) */
} BMUXlib_File_IVF_FinishSettings;

/* Handle to IVF File Mux instance */
typedef struct BMUXlib_File_IVF_P_Context *BMUXlib_File_IVF_Handle;

/****************************
*   P R O T O T Y P E S     *
****************************/

/*
   Function:
      BMUXlib_File_IVF_GetDefaultCreateSettings

   Description:
      Return the default settings for the Create() API in the
      location pointed to by pCreateSettings.

   Returns:
      None
*/
void BMUXlib_File_IVF_GetDefaultCreateSettings(
            BMUXlib_File_IVF_CreateSettings  *pCreateSettings);/* [out] location to write the default create settings */

/*
   Function:
      BMUXlib_File_IVF_Create

   Description:
      Create a new "instance" of the IVF file-based software mux, using the
      settings indicated by the structure pointed to by pCreateSettings.

      Handle to the created instance returned in the location pointed to by phIVFMux.
      This location will be set to NULL upon failure.

      Mux will be placed in the initial state of "stopped"

   Returns:
      BERR_SUCCESS               - Mux instance successfully created
      BERR_OUT_OF_SYSTEM_MEMORY  - no memory to allocate internal storage
      BERR_INVALID_PARAMETER     - bad Create Setting (minimum space requirements not met)
*/
BERR_Code BMUXlib_File_IVF_Create(
            BMUXlib_File_IVF_Handle          *phIVFMux,        /* [out] location to write the created IVF Mux Handle */
      const BMUXlib_File_IVF_CreateSettings  *pCreateSettings);/* [in] configuration settings */

/*
   Function:
      BMUXlib_File_IVF_Destroy

   Description:
      Deallocates heap memory utilized by this mux instance, then frees the
      instance.  The caller should set hIVFMux to NULL after this API returns.

   Returns:
      None
*/
void BMUXlib_File_IVF_Destroy(
            BMUXlib_File_IVF_Handle          hIVFMux);         /* [in] Handle of the mux to destroy */

/*
   Function:
      BMUXlib_File_IVF_GetDefaultStartSettings

   Description:
      Returns the default settings for the Start() API in the location
      indicated by pStartSettings.

   Returns:
      None
*/
void BMUXlib_File_IVF_GetDefaultStartSettings(
            BMUXlib_File_IVF_StartSettings  *pStartSettings);  /* [out] location to write the default start settings */

/*
   Function:
      BMUXlib_File_IVF_Start

   Description:
      Start the mux ready for processing of incoming data from the encoders
      using the configuration parameters specified in pStartSettings.  This
      call will transition the mux to the "started" state.

      Start settings define the configuration of the mux prior to starting the
      muxing process, and do not change thereafter.
      They also provide information about the encoder that is connected to the
      specific input channel, the output destination, etc.

   Returns:
      BERR_SUCCESS               - mux successfully started
      BERR_INVALID_PARAMETER     - bad start setting (currently no settings will generate this)
      BERR_NOT_SUPPORTED         - Start() invoked from invalid state (must be invoked
                                   from "stopped" state).
*/
BERR_Code BMUXlib_File_IVF_Start(
            BMUXlib_File_IVF_Handle          hIVFMux,          /* [in] Handle of the mux */
      const BMUXlib_File_IVF_StartSettings  *pStartSettings);  /* [in] Settings to use for muxing */

/*
   Function:
      BMUXlib_File_IVF_GetDefaultFinishSettings

   Description:
      Returns the default settings for the Finish() API in the location
      indicated by pFinishSettings.

   Returns:
      None
*/
void BMUXlib_File_IVF_GetDefaultFinishSettings(
            BMUXlib_File_IVF_FinishSettings *pFinishSettings); /* [out] location to write default finish settings */

/*
   Function:
      BMUXlib_File_IVF_Finish

   Description:
      Request the Mux to finish the muxing process.
      If the finish mode is "prepare for stop", then this call will transition the mux to the
      "finishing_input" state and DoMux will continue to process remaining data and will
      subsequently transition to the "finishing_output" state when it finalizes the file
      (i.e. writes the moov) and finally will transition to the "finished" state when done.
      This is the normal mode of behaviour.

      NOTE: The contents of the final output are NOT valid until the mux reaches the
      "finished" state.

   Returns:
      BERR_SUCCESS            - mux "finishing"
      BERR_INVALID_PARAMETER  - bad finish setting
      BERR_NOT_SUPPORTED      - finish called in invalid state
*/
BERR_Code BMUXlib_File_IVF_Finish(
            BMUXlib_File_IVF_Handle          hIVFMux,          /* [in] handle of the mux */
      const BMUXlib_File_IVF_FinishSettings *pFinishSettings); /* [in] Settings to use to finish the mux */

/*
   Function:
      BMUXlib_File_IVF_Stop

   Description:
      Stop the mux, and return the internal state to default values
      (effectively reset everything).  This can be called when the mux is in
      any state.

      For a clean stop, this should only be called after the
      "finished" event occurs after calling BMUXlib_File_IVF_Finish()

      This function may need to be called without BMUXlib_File_IVF_Finish()
      in cases where an abrupt stop is needed.
      If this is done, then DoMux will immediately halt muxing, and
      any remaining data will be discarded (mux will move directly to "stopped" state.
      Under these conditions, the IVF will not be completed, and will be invalid.
      Immediate Stop implies hardware not available (external storage ejected, for example)
      or some other condition that needs the stop to be performed without delay.

   Returns:
      BERR_SUCCESS   - always successful
*/
BERR_Code BMUXlib_File_IVF_Stop(
            BMUXlib_File_IVF_Handle          hIVFMux);         /* [in] Handle of the mux */


/*
   Events:          |  Mux states:
                    |     Stopped        Started           Finishing_Input   Finishing_Output     Finished
======================================================================================================
   Start            |     Started        Invalid           Invalid           Invalid              Invalid
   Finish           |     Invalid        Finishing_Input   Invalid           Invalid              Invalid
   Input_Done       |     Invalid        Invalid           Finishing_Output  Invalid              Invalid
   Output_Done      |     Invalid        Invalid           Invalid           Finished             Invalid
   Stop             |     (1)            Stopped           Stopped           Stopped              Stopped

   Invalid Event = Error + No change in state
   (1) A stop in the stopped state simply resets everything
*/

/*
   Function:
      BMUXlib_File_IVF_DoMux

   Description:
      Main processing routine for performing the muxing operation.

      DoMux must not block - once an I/O transaction is scheduled, if there is nothing that
      can be done until the I/O completes then this must return and the domux will not be
      scheduled again until at least one I/O operation is complete (the application can monitor
      the status of the storage system passed into the mux via the hStorage handle to determine
      if I/O is waiting or not for any of the I/O streams opened for this mux)

      Returns the current state of the muxing process in the location pointed to by pStatus

      The muxing is complete when in the "finished" or "stopped" state.  The output is not
      valid unless the "finished" state is reached.
      Note that the encoder can be "unhitched" from the mux once the "finishing_output" state
      is reached (no more input data to process) - this signifies an EOS on all input streams
      has been seen.

      It is expected that mux will be rescheduled once output is not busy (if mux quit due to
      output) or after the indicated execution time (if mux quit due to lack of input data).

   Returns:
      BERR_SUCCESS            - mux run successfully
      BERR_NOT_SUPPORTED      - bad mux state detected
*/
BERR_Code BMUXlib_File_IVF_DoMux(
            BMUXlib_File_IVF_Handle          hIVFMux,          /* [in] Handle of the mux */
            BMUXlib_DoMux_Status            *pStatus);         /* [out] location to write mux status */

#ifdef __cplusplus
}
#endif

#endif /* BMUXLIB_FILE_IVF_H__ */

/*****************************************************************************
* EOF
******************************************************************************/

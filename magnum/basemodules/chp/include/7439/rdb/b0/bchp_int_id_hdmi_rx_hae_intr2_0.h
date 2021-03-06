/****************************************************************************
 *     Copyright (c) 1999-2014, Broadcom Corporation
 *     All Rights Reserved
 *     Confidential Property of Broadcom Corporation
 *
 *
 * THIS SOFTWARE MAY ONLY BE USED SUBJECT TO AN EXECUTED SOFTWARE LICENSE
 * AGREEMENT  BETWEEN THE USER AND BROADCOM.  YOU HAVE NO RIGHT TO USE OR
 * EXPLOIT THIS MATERIAL EXCEPT SUBJECT TO THE TERMS OF SUCH AN AGREEMENT.
 *
 * Module Description:
 *                     DO NOT EDIT THIS FILE DIRECTLY
 *
 * This module was generated magically with RDB from a source description
 * file. You must edit the source file for changes to be made to this file.
 *
 *
 * Date:           Generated on               Thu Jan 22 15:24:45 2015
 *                 Full Compile MD5 Checksum  9e27b6ad4c64ff5a28f048a17a7bb056
 *                     (minus title and desc)
 *                 MD5 Checksum               a1a4b86f7693c062faaafa50c5ca64ce
 *
 * Compiled with:  RDB Utility                unknown
 *                 RDB.pm                     15572
 *                 generate_int_id.pl         1.0
 *                 Perl Interpreter           5.014001
 *                 Operating System           linux
 *
 *
 ***************************************************************************/

#include "bchp.h"
#include "bchp_hdmi_rx_hae_intr2_0.h"

#ifndef BCHP_INT_ID_HDMI_RX_HAE_INTR2_0_H__
#define BCHP_INT_ID_HDMI_RX_HAE_INTR2_0_H__

#define BCHP_INT_ID_HDMI_RX_HAE_INTR2_0_CPU_STATUS_AES_FRAME_NUMBER_ROLLOVER BCHP_INT_ID_CREATE(BCHP_HDMI_RX_HAE_INTR2_0_CPU_STATUS, BCHP_HDMI_RX_HAE_INTR2_0_CPU_STATUS_AES_FRAME_NUMBER_ROLLOVER_SHIFT)
#define BCHP_INT_ID_HDMI_RX_HAE_INTR2_0_CPU_STATUS_EXCESSIVE_PACKET_ERRORS BCHP_INT_ID_CREATE(BCHP_HDMI_RX_HAE_INTR2_0_CPU_STATUS, BCHP_HDMI_RX_HAE_INTR2_0_CPU_STATUS_EXCESSIVE_PACKET_ERRORS_SHIFT)
#define BCHP_INT_ID_HDMI_RX_HAE_INTR2_0_CPU_STATUS_HDCP1_I2C_ACCESS_ERR BCHP_INT_ID_CREATE(BCHP_HDMI_RX_HAE_INTR2_0_CPU_STATUS, BCHP_HDMI_RX_HAE_INTR2_0_CPU_STATUS_HDCP1_I2C_ACCESS_ERR_SHIFT)
#define BCHP_INT_ID_HDMI_RX_HAE_INTR2_0_CPU_STATUS_HDCP2_I2C_ACCESS_ERR BCHP_INT_ID_CREATE(BCHP_HDMI_RX_HAE_INTR2_0_CPU_STATUS, BCHP_HDMI_RX_HAE_INTR2_0_CPU_STATUS_HDCP2_I2C_ACCESS_ERR_SHIFT)
#define BCHP_INT_ID_HDMI_RX_HAE_INTR2_0_CPU_STATUS_MAILBOX_UPDATE_0 BCHP_INT_ID_CREATE(BCHP_HDMI_RX_HAE_INTR2_0_CPU_STATUS, BCHP_HDMI_RX_HAE_INTR2_0_CPU_STATUS_MAILBOX_UPDATE_0_SHIFT)
#define BCHP_INT_ID_HDMI_RX_HAE_INTR2_0_CPU_STATUS_MAILBOX_UPDATE_1 BCHP_INT_ID_CREATE(BCHP_HDMI_RX_HAE_INTR2_0_CPU_STATUS, BCHP_HDMI_RX_HAE_INTR2_0_CPU_STATUS_MAILBOX_UPDATE_1_SHIFT)
#define BCHP_INT_ID_HDMI_RX_HAE_INTR2_0_CPU_STATUS_READ_FIFO_ERR BCHP_INT_ID_CREATE(BCHP_HDMI_RX_HAE_INTR2_0_CPU_STATUS, BCHP_HDMI_RX_HAE_INTR2_0_CPU_STATUS_READ_FIFO_ERR_SHIFT)
#define BCHP_INT_ID_HDMI_RX_HAE_INTR2_0_CPU_STATUS_READ_MESSAGE_COMPLETE BCHP_INT_ID_CREATE(BCHP_HDMI_RX_HAE_INTR2_0_CPU_STATUS, BCHP_HDMI_RX_HAE_INTR2_0_CPU_STATUS_READ_MESSAGE_COMPLETE_SHIFT)
#define BCHP_INT_ID_HDMI_RX_HAE_INTR2_0_CPU_STATUS_READ_MESSAGE_START BCHP_INT_ID_CREATE(BCHP_HDMI_RX_HAE_INTR2_0_CPU_STATUS, BCHP_HDMI_RX_HAE_INTR2_0_CPU_STATUS_READ_MESSAGE_START_SHIFT)
#define BCHP_INT_ID_HDMI_RX_HAE_INTR2_0_CPU_STATUS_READ_TOO_FEW_BYTES BCHP_INT_ID_CREATE(BCHP_HDMI_RX_HAE_INTR2_0_CPU_STATUS, BCHP_HDMI_RX_HAE_INTR2_0_CPU_STATUS_READ_TOO_FEW_BYTES_SHIFT)
#define BCHP_INT_ID_HDMI_RX_HAE_INTR2_0_CPU_STATUS_TIMEOUT BCHP_INT_ID_CREATE(BCHP_HDMI_RX_HAE_INTR2_0_CPU_STATUS, BCHP_HDMI_RX_HAE_INTR2_0_CPU_STATUS_TIMEOUT_SHIFT)
#define BCHP_INT_ID_HDMI_RX_HAE_INTR2_0_CPU_STATUS_WRITE_FIFO_ERR BCHP_INT_ID_CREATE(BCHP_HDMI_RX_HAE_INTR2_0_CPU_STATUS, BCHP_HDMI_RX_HAE_INTR2_0_CPU_STATUS_WRITE_FIFO_ERR_SHIFT)
#define BCHP_INT_ID_HDMI_RX_HAE_INTR2_0_CPU_STATUS_WRITE_MESSAGE_RDY BCHP_INT_ID_CREATE(BCHP_HDMI_RX_HAE_INTR2_0_CPU_STATUS, BCHP_HDMI_RX_HAE_INTR2_0_CPU_STATUS_WRITE_MESSAGE_RDY_SHIFT)
#define BCHP_INT_ID_HDMI_RX_HAE_INTR2_0_CPU_STATUS_WRITE_MESSAGE_START BCHP_INT_ID_CREATE(BCHP_HDMI_RX_HAE_INTR2_0_CPU_STATUS, BCHP_HDMI_RX_HAE_INTR2_0_CPU_STATUS_WRITE_MESSAGE_START_SHIFT)

#endif /* #ifndef BCHP_INT_ID_HDMI_RX_HAE_INTR2_0_H__ */

/* End of File */

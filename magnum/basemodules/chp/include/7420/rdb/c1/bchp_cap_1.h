/***************************************************************************
 *     Copyright (c) 1999-2010, Broadcom Corporation
 *     All Rights Reserved
 *     Confidential Property of Broadcom Corporation
 *
 *
 * THIS SOFTWARE MAY ONLY BE USED SUBJECT TO AN EXECUTED SOFTWARE LICENSE
 * AGREEMENT  BETWEEN THE USER AND BROADCOM.  YOU HAVE NO RIGHT TO USE OR
 * EXPLOIT THIS MATERIAL EXCEPT SUBJECT TO THE TERMS OF SUCH AN AGREEMENT.
 *
 * $brcm_Workfile: $
 * $brcm_Revision: $
 * $brcm_Date: $
 *
 * Module Description:
 *                     DO NOT EDIT THIS FILE DIRECTLY
 *
 * This module was generated magically with RDB from a source description
 * file. You must edit the source file for changes to be made to this file.
 *
 *
 * Date:           Generated on         Thu Apr 22 17:16:07 2010
 *                 MD5 Checksum         e645cb91be669b614b9400e5da71f4fa
 *
 * Compiled with:  RDB Utility          combo_header.pl
 *                 RDB Parser           3.0
 *                 unknown              unknown
 *                 Perl Interpreter     5.008008
 *                 Operating System     linux
 *
 * Revision History:
 *
 * $brcm_Log: $
 * 
 ***************************************************************************/

#ifndef BCHP_CAP_1_H__
#define BCHP_CAP_1_H__

/***************************************************************************
 *CAP_1 - Capture 1 Registers
 ***************************************************************************/
#define BCHP_CAP_1_REVISION                      0x00788200 /* Capture Engine Revision ID */
#define BCHP_CAP_1_PIC_SIZE                      0x00788204 /* Capture Vertical and Horizontal Size */
#define BCHP_CAP_1_PIC_OFFSET                    0x00788208 /* Capture Vertical and Horizontal Start Offset */
#define BCHP_CAP_1_BVB_IN_SIZE                   0x0078820c /* Capture BVB Source Vertical and Horizontal Size */
#define BCHP_CAP_1_MSTART                        0x00788210 /* Capture Memory Buffer Starting Address */
#define BCHP_CAP_1_PITCH                         0x00788214 /* Capture Memory Buffer Pitch */
#define BCHP_CAP_1_CTRL                          0x00788218 /* Capture Control */
#define BCHP_CAP_1_BYTE_ORDER                    0x00788224 /* Capture Byte Order Control */
#define BCHP_CAP_1_RX_CTRL                       0x00788228 /* Capture BVB Receiver Control */
#define BCHP_CAP_1_TRIG_CTRL                     0x0078822c /* Capture RDMA Trigger Control */
#define BCHP_CAP_1_BVB_TRIG_0_CFG                0x00788230 /* Capture BVB Trigger 0 Configuration */
#define BCHP_CAP_1_BVB_TRIG_1_CFG                0x00788234 /* Capture BVB Trigger 1 Configuration */
#define BCHP_CAP_1_LINE_CMP_TRIG_0_CFG           0x00788238 /* Capture Line Compare Trigger 0 Configuration */
#define BCHP_CAP_1_LINE_CMP_TRIG_1_CFG           0x0078823c /* Capture Line Compare Trigger 1 Configuration */
#define BCHP_CAP_1_STATUS                        0x00788240 /* Capture Engine Status */
#define BCHP_CAP_1_BVB_STATUS                    0x00788244 /* Capture BVB Status */
#define BCHP_CAP_1_BVB_STATUS_CLEAR              0x00788248 /* Capture BVB Status Clear */
#define BCHP_CAP_1_FIFO_STATUS                   0x0078824c /* Capture FIFO Status */
#define BCHP_CAP_1_FIFO_STATUS_CLEAR             0x00788250 /* Capture FIFO Status Clear */
#define BCHP_CAP_1_SCRATCH                       0x0078827c /* Scratch Register */

#endif /* #ifndef BCHP_CAP_1_H__ */

/* End of File */

 /****************************************************************************
*  
*  Copyright (c) 2010-2011 Broadcom Corporation
*
*  This program is the proprietary software of Broadcom Corporation and/or
*  its licensors, and may only be used, duplicated, modified or distributed
*  pursuant to the terms and conditions of a separate, written license
*  agreement executed between you and Broadcom (an "Authorized License").
*  Except as set forth in an Authorized License, Broadcom grants no license
*  (express or implied), right to use, or waiver of any kind with respect to
*  the Software, and Broadcom expressly reserves all rights in and to the
*  Software and all intellectual property rights therein.  IF YOU HAVE NO
*  AUTHORIZED LICENSE, THEN YOU HAVE NO RIGHT TO USE THIS SOFTWARE IN ANY WAY,
*  AND SHOULD IMMEDIATELY NOTIFY BROADCOM AND DISCONTINUE ALL USE OF THE
*  SOFTWARE.  
*
*  Except as expressly set forth in the Authorized License,
*
*  1.     This program, including its structure, sequence and organization,
*  constitutes the valuable trade secrets of Broadcom, and you shall use all
*  reasonable efforts to protect the confidentiality thereof, and to use this
*  information only in connection with your use of Broadcom integrated circuit
*  products.
*
*  2.     TO THE MAXIMUM EXTENT PERMITTED BY LAW, THE SOFTWARE IS PROVIDED
*  "AS IS" AND WITH ALL FAULTS AND BROADCOM MAKES NO PROMISES, REPRESENTATIONS
*  OR WARRANTIES, EITHER EXPRESS, IMPLIED, STATUTORY, OR OTHERWISE, WITH
*  RESPECT TO THE SOFTWARE.  BROADCOM SPECIFICALLY DISCLAIMS ANY AND ALL
*  IMPLIED WARRANTIES OF TITLE, MERCHANTABILITY, NONINFRINGEMENT, FITNESS FOR
*  A PARTICULAR PURPOSE, LACK OF VIRUSES, ACCURACY OR COMPLETENESS, QUIET
*  ENJOYMENT, QUIET POSSESSION OR CORRESPONDENCE TO DESCRIPTION. YOU ASSUME
*  THE ENTIRE RISK ARISING OUT OF USE OR PERFORMANCE OF THE SOFTWARE.
*
*  3.     TO THE MAXIMUM EXTENT PERMITTED BY LAW, IN NO EVENT SHALL BROADCOM
*  OR ITS LICENSORS BE LIABLE FOR (i) CONSEQUENTIAL, INCIDENTAL, SPECIAL,
*  INDIRECT, OR EXEMPLARY DAMAGES WHATSOEVER ARISING OUT OF OR IN ANY WAY
*  RELATING TO YOUR USE OF OR INABILITY TO USE THE SOFTWARE EVEN IF BROADCOM
*  HAS BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES; OR (ii) ANY AMOUNT IN
*  EXCESS OF THE AMOUNT ACTUALLY PAID FOR THE SOFTWARE ITSELF OR U.S. $1,
*  WHICHEVER IS GREATER. THESE LIMITATIONS SHALL APPLY NOTWITHSTANDING ANY
*  FAILURE OF ESSENTIAL PURPOSE OF ANY LIMITED REMEDY.
*
****************************************************************************
*
*  Filename: bcmvenet.h 
*
****************************************************************************
* Description: This is the network interface driver for the virtual Ethernet 
*              interface between 7xxx and 3383.
****************************************************************************/
#ifndef __BCMVENET_H__
#define __BCMVENET_H__

/*
 * Ioctl definitions.
 */

#define SIOCGETMBOX         (SIOCDEVPRIVATE + 0)
#define SIOCPUTWINDOW       (SIOCDEVPRIVATE + 1)
#define SIOCGETWINDOW       (SIOCDEVPRIVATE + 2)


#define MBOX_MSG_MASK           0xe0000000
#define MBOX_NULL               0x00000000
#define MBOX_RESET_DOCSIS       0x20000000
#define MBOX_DMA_READY 			0x40000000
#define MBOX_REBOOTING          0x60000000
#define MBOX_XFER_BLOCK         0x80000000

typedef struct BcmVEnet_ioctlparms {
    unsigned int from;
    unsigned int to;
    unsigned int length;
} BcmVEnet_ioctlparms;

typedef struct BcmVEnet_blockparms {
    unsigned int offset;
    unsigned int length;
    unsigned int to;
    unsigned int fileId;
} BcmVEnet_blockparms;

#define FID_BOOTLOADER  0
#define FID_DOCSIS      1
#define FID_PERM_NONVOL 2
#define FID_DYN_NONVOL  3

#endif /* __BCMVENET_H__ */

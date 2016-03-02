/***************************************************************************
 *     Copyright (c) 2005-2014, Broadcom Corporation
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
 * Broadcom Security Processor Code
 ***************************************************************************/
#ifndef BSP_S_HW_7400_H__
#define BSP_S_HW_7400_H__


/* multi2 system keys supported by hardware*/
#define BCMD_MULTI2_MAXSYSKEY                     64
/* Total number of pid channels supported */
#define BCMD_TOTAL_PIDCHANNELS                    1024  /* For Zeus 4.0, previously 512 */
/* RAM User Key size (in bytes) */
#define BCMD_KEYLADDER_KEYRAM_SIZE                32       /* in bytes (256 bits per key)*/
#define BCMD_HDCP22_HDMI_KS_SIZE                  (128/8)  /* in bytes */
#define BCMD_HDCP22_HDMI_RIV_SIZE                 (64/8)
#define BCMD_HDCP22_MIRACAST_KEY_SIZE             (128/8)


#define BCMD_MAX_M2M_KEY_SLOT  (0)  /*there are no dedicated M2M keyslots on Zeus4.*/


#define BHSM_IN_BUF1_ADDR       BCHP_BSP_CMDBUF_DMEMi_ARRAY_BASE
#define BHSM_OUT_BUF1_ADDR      BCHP_BSP_CMDBUF_DMEMi_ARRAY_BASE + (BCMD_BUFFER_BYTE_SIZE * 1)
#define BHSM_IN_BUF2_ADDR       BCHP_BSP_CMDBUF_DMEMi_ARRAY_BASE + (BCMD_BUFFER_BYTE_SIZE * 2)
#define BHSM_OUT_BUF2_ADDR      BCHP_BSP_CMDBUF_DMEMi_ARRAY_BASE + (BCMD_BUFFER_BYTE_SIZE * 3)

#define BHSM_MAX_ARCH_PER_MEMC (12) /* Max # ARCH per MEMC */


#endif  /* BSP_S_HW_7400_H__ end of header file*/

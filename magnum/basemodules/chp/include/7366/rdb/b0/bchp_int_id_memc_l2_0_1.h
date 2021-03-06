/***************************************************************************
 *     Copyright (c) 1999-2013, Broadcom Corporation
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
 * Date:           Generated on              Mon Dec 23 13:22:27 2013
 *                 Full Compile MD5 Checksum e5d1378cc1475b750905e70cb70c73d9
 *                   (minus title and desc)  
 *                 MD5 Checksum              aa943f3142a624837db5321711723fcf
 *
 * Compiled with:  RDB Utility               unknown
 *                 RDB Parser                3.0
 *                 generate_int_id.pl        1.0
 *                 Perl Interpreter          5.008008
 *                 Operating System          linux
 *
 * Revision History:
 *
 * $brcm_Log: $
 * 
 ***************************************************************************/

#include "bchp.h"
#include "bchp_memc_l2_0_1.h"

#ifndef BCHP_INT_ID_MEMC_L2_0_1_H__
#define BCHP_INT_ID_MEMC_L2_0_1_H__

#define BCHP_INT_ID_MEMC_L2_0_1_ARC_4_INTR    BCHP_INT_ID_CREATE(BCHP_MEMC_L2_0_1_CPU_STATUS, BCHP_MEMC_L2_0_1_CPU_STATUS_ARC_4_INTR_SHIFT)
#define BCHP_INT_ID_MEMC_L2_0_1_ARC_5_INTR    BCHP_INT_ID_CREATE(BCHP_MEMC_L2_0_1_CPU_STATUS, BCHP_MEMC_L2_0_1_CPU_STATUS_ARC_5_INTR_SHIFT)
#define BCHP_INT_ID_MEMC_L2_0_1_ARC_6_INTR    BCHP_INT_ID_CREATE(BCHP_MEMC_L2_0_1_CPU_STATUS, BCHP_MEMC_L2_0_1_CPU_STATUS_ARC_6_INTR_SHIFT)
#define BCHP_INT_ID_MEMC_L2_0_1_ARC_7_INTR    BCHP_INT_ID_CREATE(BCHP_MEMC_L2_0_1_CPU_STATUS, BCHP_MEMC_L2_0_1_CPU_STATUS_ARC_7_INTR_SHIFT)
#define BCHP_INT_ID_MEMC_L2_0_1_GSIZE_VIOL_INTR_PFRI_4 BCHP_INT_ID_CREATE(BCHP_MEMC_L2_0_1_CPU_STATUS, BCHP_MEMC_L2_0_1_CPU_STATUS_GSIZE_VIOL_INTR_PFRI_4_SHIFT)
#define BCHP_INT_ID_MEMC_L2_0_1_LMB0_ATW_INTR BCHP_INT_ID_CREATE(BCHP_MEMC_L2_0_1_CPU_STATUS, BCHP_MEMC_L2_0_1_CPU_STATUS_LMB0_ATW_INTR_SHIFT)
#define BCHP_INT_ID_MEMC_L2_0_1_LMB1_ATW_INTR BCHP_INT_ID_CREATE(BCHP_MEMC_L2_0_1_CPU_STATUS, BCHP_MEMC_L2_0_1_CPU_STATUS_LMB1_ATW_INTR_SHIFT)
#define BCHP_INT_ID_MEMC_L2_0_1_LMB2_ATW_INTR BCHP_INT_ID_CREATE(BCHP_MEMC_L2_0_1_CPU_STATUS, BCHP_MEMC_L2_0_1_CPU_STATUS_LMB2_ATW_INTR_SHIFT)
#define BCHP_INT_ID_MEMC_L2_0_1_LMB3_ATW_INTR BCHP_INT_ID_CREATE(BCHP_MEMC_L2_0_1_CPU_STATUS, BCHP_MEMC_L2_0_1_CPU_STATUS_LMB3_ATW_INTR_SHIFT)
#define BCHP_INT_ID_MEMC_L2_0_1_MISSING_EOG_INTR_PFRI_4 BCHP_INT_ID_CREATE(BCHP_MEMC_L2_0_1_CPU_STATUS, BCHP_MEMC_L2_0_1_CPU_STATUS_MISSING_EOG_INTR_PFRI_4_SHIFT)
#define BCHP_INT_ID_MEMC_L2_0_1_MISSING_SOG_INTR_PFRI_4 BCHP_INT_ID_CREATE(BCHP_MEMC_L2_0_1_CPU_STATUS, BCHP_MEMC_L2_0_1_CPU_STATUS_MISSING_SOG_INTR_PFRI_4_SHIFT)
#define BCHP_INT_ID_MEMC_L2_0_1_MIXED_TYPE_VIOL_INTR_PFRI_0 BCHP_INT_ID_CREATE(BCHP_MEMC_L2_0_1_CPU_STATUS, BCHP_MEMC_L2_0_1_CPU_STATUS_MIXED_TYPE_VIOL_INTR_PFRI_0_SHIFT)
#define BCHP_INT_ID_MEMC_L2_0_1_MIXED_TYPE_VIOL_INTR_PFRI_1 BCHP_INT_ID_CREATE(BCHP_MEMC_L2_0_1_CPU_STATUS, BCHP_MEMC_L2_0_1_CPU_STATUS_MIXED_TYPE_VIOL_INTR_PFRI_1_SHIFT)
#define BCHP_INT_ID_MEMC_L2_0_1_MIXED_TYPE_VIOL_INTR_PFRI_2 BCHP_INT_ID_CREATE(BCHP_MEMC_L2_0_1_CPU_STATUS, BCHP_MEMC_L2_0_1_CPU_STATUS_MIXED_TYPE_VIOL_INTR_PFRI_2_SHIFT)
#define BCHP_INT_ID_MEMC_L2_0_1_MIXED_TYPE_VIOL_INTR_PFRI_3 BCHP_INT_ID_CREATE(BCHP_MEMC_L2_0_1_CPU_STATUS, BCHP_MEMC_L2_0_1_CPU_STATUS_MIXED_TYPE_VIOL_INTR_PFRI_3_SHIFT)
#define BCHP_INT_ID_MEMC_L2_0_1_MIXED_TYPE_VIOL_INTR_PFRI_4 BCHP_INT_ID_CREATE(BCHP_MEMC_L2_0_1_CPU_STATUS, BCHP_MEMC_L2_0_1_CPU_STATUS_MIXED_TYPE_VIOL_INTR_PFRI_4_SHIFT)
#define BCHP_INT_ID_MEMC_L2_0_1_MIXED_TYPE_VIOL_INTR_PFRI_5 BCHP_INT_ID_CREATE(BCHP_MEMC_L2_0_1_CPU_STATUS, BCHP_MEMC_L2_0_1_CPU_STATUS_MIXED_TYPE_VIOL_INTR_PFRI_5_SHIFT)
#define BCHP_INT_ID_MEMC_L2_0_1_MIXED_TYPE_VIOL_INTR_PFRI_6 BCHP_INT_ID_CREATE(BCHP_MEMC_L2_0_1_CPU_STATUS, BCHP_MEMC_L2_0_1_CPU_STATUS_MIXED_TYPE_VIOL_INTR_PFRI_6_SHIFT)
#define BCHP_INT_ID_MEMC_L2_0_1_MIXED_TYPE_VIOL_INTR_PFRI_7 BCHP_INT_ID_CREATE(BCHP_MEMC_L2_0_1_CPU_STATUS, BCHP_MEMC_L2_0_1_CPU_STATUS_MIXED_TYPE_VIOL_INTR_PFRI_7_SHIFT)
#define BCHP_INT_ID_MEMC_L2_0_1_PAGE_BREAK_INTR_PFRI_4 BCHP_INT_ID_CREATE(BCHP_MEMC_L2_0_1_CPU_STATUS, BCHP_MEMC_L2_0_1_CPU_STATUS_PAGE_BREAK_INTR_PFRI_4_SHIFT)
#define BCHP_INT_ID_MEMC_L2_0_1_UBUS_ARC_0_INTR BCHP_INT_ID_CREATE(BCHP_MEMC_L2_0_1_CPU_STATUS, BCHP_MEMC_L2_0_1_CPU_STATUS_UBUS_ARC_0_INTR_SHIFT)
#define BCHP_INT_ID_MEMC_L2_0_1_UBUS_ARC_1_INTR BCHP_INT_ID_CREATE(BCHP_MEMC_L2_0_1_CPU_STATUS, BCHP_MEMC_L2_0_1_CPU_STATUS_UBUS_ARC_1_INTR_SHIFT)
#define BCHP_INT_ID_MEMC_L2_0_1_UBUS_ARC_2_INTR BCHP_INT_ID_CREATE(BCHP_MEMC_L2_0_1_CPU_STATUS, BCHP_MEMC_L2_0_1_CPU_STATUS_UBUS_ARC_2_INTR_SHIFT)
#define BCHP_INT_ID_MEMC_L2_0_1_UBUS_ARC_3_INTR BCHP_INT_ID_CREATE(BCHP_MEMC_L2_0_1_CPU_STATUS, BCHP_MEMC_L2_0_1_CPU_STATUS_UBUS_ARC_3_INTR_SHIFT)
#define BCHP_INT_ID_MEMC_L2_0_1_UBUS_ARC_4_INTR BCHP_INT_ID_CREATE(BCHP_MEMC_L2_0_1_CPU_STATUS, BCHP_MEMC_L2_0_1_CPU_STATUS_UBUS_ARC_4_INTR_SHIFT)
#define BCHP_INT_ID_MEMC_L2_0_1_UBUS_ARC_5_INTR BCHP_INT_ID_CREATE(BCHP_MEMC_L2_0_1_CPU_STATUS, BCHP_MEMC_L2_0_1_CPU_STATUS_UBUS_ARC_5_INTR_SHIFT)
#define BCHP_INT_ID_MEMC_L2_0_1_UBUS_ARC_6_INTR BCHP_INT_ID_CREATE(BCHP_MEMC_L2_0_1_CPU_STATUS, BCHP_MEMC_L2_0_1_CPU_STATUS_UBUS_ARC_6_INTR_SHIFT)
#define BCHP_INT_ID_MEMC_L2_0_1_UBUS_ARC_7_INTR BCHP_INT_ID_CREATE(BCHP_MEMC_L2_0_1_CPU_STATUS, BCHP_MEMC_L2_0_1_CPU_STATUS_UBUS_ARC_7_INTR_SHIFT)
#define BCHP_INT_ID_MEMC_L2_0_1_UBUS_ATW_INTR BCHP_INT_ID_CREATE(BCHP_MEMC_L2_0_1_CPU_STATUS, BCHP_MEMC_L2_0_1_CPU_STATUS_UBUS_ATW_INTR_SHIFT)
#define BCHP_INT_ID_MEMC_L2_0_1_UBUS_HDR_FIFO_OVERFLOW_INTR BCHP_INT_ID_CREATE(BCHP_MEMC_L2_0_1_CPU_STATUS, BCHP_MEMC_L2_0_1_CPU_STATUS_UBUS_HDR_FIFO_OVERFLOW_INTR_SHIFT)
#define BCHP_INT_ID_MEMC_L2_0_1_UBUS_WRDATA_FIFO_OVERFLOW_INTR BCHP_INT_ID_CREATE(BCHP_MEMC_L2_0_1_CPU_STATUS, BCHP_MEMC_L2_0_1_CPU_STATUS_UBUS_WRDATA_FIFO_OVERFLOW_INTR_SHIFT)

#endif /* #ifndef BCHP_INT_ID_MEMC_L2_0_1_H__ */

/* End of File */

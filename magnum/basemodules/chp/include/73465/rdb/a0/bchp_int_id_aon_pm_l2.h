/****************************************************************************
 *     Copyright (c) 1999-2015, Broadcom Corporation
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
 * Date:           Generated on               Tue Aug 25 10:47:41 2015
 *                 Full Compile MD5 Checksum  add20cb7888302c2ee8be1277223a4e4
 *                     (minus title and desc)
 *                 MD5 Checksum               f64b4ec86ad9ad7523e5d75b1dc732c5
 *
 * Compiled with:  RDB Utility                unknown
 *                 RDB.pm                     126
 *                 generate_int_id.pl         1.0
 *                 Perl Interpreter           5.008008
 *                 Operating System           linux
 *                 Script Source              /tools/dvtsw/current/Linux/generate_int_id.pl
 *                 DVTSWVER                   current
 *
 *
 ***************************************************************************/

#include "bchp.h"
#include "bchp_aon_pm_l2.h"

#ifndef BCHP_INT_ID_AON_PM_L2_H__
#define BCHP_INT_ID_AON_PM_L2_H__

#define BCHP_INT_ID_AON_PM_L2_MOCA            BCHP_INT_ID_CREATE(BCHP_AON_PM_L2_CPU_STATUS, BCHP_AON_PM_L2_CPU_STATUS_MOCA_SHIFT)
#define BCHP_INT_ID_BOUNDARY_SCAN_REQ         BCHP_INT_ID_CREATE(BCHP_AON_PM_L2_CPU_STATUS, BCHP_AON_PM_L2_CPU_STATUS_BOUNDARY_SCAN_REQ_SHIFT)
#define BCHP_INT_ID_CEC_INTR                  BCHP_INT_ID_CREATE(BCHP_AON_PM_L2_CPU_STATUS, BCHP_AON_PM_L2_CPU_STATUS_CEC_INTR_SHIFT)
#define BCHP_INT_ID_FP_RESET                  BCHP_INT_ID_CREATE(BCHP_AON_PM_L2_CPU_STATUS, BCHP_AON_PM_L2_CPU_STATUS_FP_RESET_SHIFT)
#define BCHP_INT_ID_FTM                       BCHP_INT_ID_CREATE(BCHP_AON_PM_L2_CPU_STATUS, BCHP_AON_PM_L2_CPU_STATUS_FTM_SHIFT)
#define BCHP_INT_ID_GPIO                      BCHP_INT_ID_CREATE(BCHP_AON_PM_L2_CPU_STATUS, BCHP_AON_PM_L2_CPU_STATUS_GPIO_SHIFT)
#define BCHP_INT_ID_IRR_INTR                  BCHP_INT_ID_CREATE(BCHP_AON_PM_L2_CPU_STATUS, BCHP_AON_PM_L2_CPU_STATUS_IRR_INTR_SHIFT)
#define BCHP_INT_ID_KPD_INTR                  BCHP_INT_ID_CREATE(BCHP_AON_PM_L2_CPU_STATUS, BCHP_AON_PM_L2_CPU_STATUS_KPD_INTR_SHIFT)
#define BCHP_INT_ID_NMI_B_INTR                BCHP_INT_ID_CREATE(BCHP_AON_PM_L2_CPU_STATUS, BCHP_AON_PM_L2_CPU_STATUS_NMI_B_INTR_SHIFT)
#define BCHP_INT_ID_SDS0_AFEC                 BCHP_INT_ID_CREATE(BCHP_AON_PM_L2_CPU_STATUS, BCHP_AON_PM_L2_CPU_STATUS_SDS0_AFEC_SHIFT)
#define BCHP_INT_ID_SDS0_RCVR_0               BCHP_INT_ID_CREATE(BCHP_AON_PM_L2_CPU_STATUS, BCHP_AON_PM_L2_CPU_STATUS_SDS0_RCVR_0_SHIFT)
#define BCHP_INT_ID_SDS0_RCVR_1               BCHP_INT_ID_CREATE(BCHP_AON_PM_L2_CPU_STATUS, BCHP_AON_PM_L2_CPU_STATUS_SDS0_RCVR_1_SHIFT)
#define BCHP_INT_ID_SDS0_TFEC                 BCHP_INT_ID_CREATE(BCHP_AON_PM_L2_CPU_STATUS, BCHP_AON_PM_L2_CPU_STATUS_SDS0_TFEC_SHIFT)
#define BCHP_INT_ID_SDS1_AFEC                 BCHP_INT_ID_CREATE(BCHP_AON_PM_L2_CPU_STATUS, BCHP_AON_PM_L2_CPU_STATUS_SDS1_AFEC_SHIFT)
#define BCHP_INT_ID_SDS1_RCVR_0               BCHP_INT_ID_CREATE(BCHP_AON_PM_L2_CPU_STATUS, BCHP_AON_PM_L2_CPU_STATUS_SDS1_RCVR_0_SHIFT)
#define BCHP_INT_ID_SDS1_RCVR_1               BCHP_INT_ID_CREATE(BCHP_AON_PM_L2_CPU_STATUS, BCHP_AON_PM_L2_CPU_STATUS_SDS1_RCVR_1_SHIFT)
#define BCHP_INT_ID_SDS1_TFEC                 BCHP_INT_ID_CREATE(BCHP_AON_PM_L2_CPU_STATUS, BCHP_AON_PM_L2_CPU_STATUS_SDS1_TFEC_SHIFT)
#define BCHP_INT_ID_SPARE_WAKEUP_EVENT_0      BCHP_INT_ID_CREATE(BCHP_AON_PM_L2_CPU_STATUS, BCHP_AON_PM_L2_CPU_STATUS_SPARE_WAKEUP_EVENT_0_SHIFT)
#define BCHP_INT_ID_TIMER_INTR                BCHP_INT_ID_CREATE(BCHP_AON_PM_L2_CPU_STATUS, BCHP_AON_PM_L2_CPU_STATUS_TIMER_INTR_SHIFT)
#define BCHP_INT_ID_UHFR                      BCHP_INT_ID_CREATE(BCHP_AON_PM_L2_CPU_STATUS, BCHP_AON_PM_L2_CPU_STATUS_UHFR_SHIFT)
#define BCHP_INT_ID_USB0                      BCHP_INT_ID_CREATE(BCHP_AON_PM_L2_CPU_STATUS, BCHP_AON_PM_L2_CPU_STATUS_USB0_SHIFT)
#define BCHP_INT_ID_USB1                      BCHP_INT_ID_CREATE(BCHP_AON_PM_L2_CPU_STATUS, BCHP_AON_PM_L2_CPU_STATUS_USB1_SHIFT)
#define BCHP_INT_ID_WOL_ENET                  BCHP_INT_ID_CREATE(BCHP_AON_PM_L2_CPU_STATUS, BCHP_AON_PM_L2_CPU_STATUS_WOL_ENET_SHIFT)
#define BCHP_INT_ID_WOL_MOCA                  BCHP_INT_ID_CREATE(BCHP_AON_PM_L2_CPU_STATUS, BCHP_AON_PM_L2_CPU_STATUS_WOL_MOCA_SHIFT)
#define BCHP_INT_ID_XPT_PMU                   BCHP_INT_ID_CREATE(BCHP_AON_PM_L2_CPU_STATUS, BCHP_AON_PM_L2_CPU_STATUS_XPT_PMU_SHIFT)

#endif /* #ifndef BCHP_INT_ID_AON_PM_L2_H__ */

/* End of File */

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
 * Date:           Generated on               Tue Mar 10 09:36:56 2015
 *                 Full Compile MD5 Checksum  283335a9f9b39f3b588b04c7b60c5ff3
 *                     (minus title and desc)
 *                 MD5 Checksum               241d7af91b1c4184b3f0cfa9382cdd95
 *
 * Compiled with:  RDB Utility                unknown
 *                 RDB.pm                     15839
 *                 generate_int_id.pl         1.0
 *                 Perl Interpreter           5.008008
 *                 Operating System           linux
 *
 *
 ***************************************************************************/

#include "bchp.h"
#include "bchp_mpm_cpu_l2.h"

#ifndef BCHP_INT_ID_MPM_CPU_L2_H__
#define BCHP_INT_ID_MPM_CPU_L2_H__

#define BCHP_INT_ID_HOST_CLEARED_INTR         BCHP_INT_ID_CREATE(BCHP_MPM_CPU_L2_STATUS0, BCHP_MPM_CPU_L2_STATUS0_HOST_CLEARED_INTR_SHIFT)
#define BCHP_INT_ID_MPM_CPU_L2_A2R_BAD_SIZE_INTR BCHP_INT_ID_CREATE(BCHP_MPM_CPU_L2_STATUS0, BCHP_MPM_CPU_L2_STATUS0_A2R_BAD_SIZE_INTR_SHIFT)
#define BCHP_INT_ID_MPM_CPU_L2_A2R_TIMEOUT_INTR BCHP_INT_ID_CREATE(BCHP_MPM_CPU_L2_STATUS0, BCHP_MPM_CPU_L2_STATUS0_A2R_TIMEOUT_INTR_SHIFT)
#define BCHP_INT_ID_MPM_CPU_L2_MPM_INTR_SPARE0 BCHP_INT_ID_CREATE(BCHP_MPM_CPU_L2_STATUS0, BCHP_MPM_CPU_L2_STATUS0_MPM_INTR_SPARE0_SHIFT)
#define BCHP_INT_ID_MPM_CPU_L2_MPM_INTR_SPARE1 BCHP_INT_ID_CREATE(BCHP_MPM_CPU_L2_STATUS0, BCHP_MPM_CPU_L2_STATUS0_MPM_INTR_SPARE1_SHIFT)
#define BCHP_INT_ID_MPM_CPU_L2_MPM_INTR_SPARE2 BCHP_INT_ID_CREATE(BCHP_MPM_CPU_L2_STATUS0, BCHP_MPM_CPU_L2_STATUS0_MPM_INTR_SPARE2_SHIFT)
#define BCHP_INT_ID_MPM_CPU_L2_MPM_INTR_SPARE3 BCHP_INT_ID_CREATE(BCHP_MPM_CPU_L2_STATUS0, BCHP_MPM_CPU_L2_STATUS0_MPM_INTR_SPARE3_SHIFT)
#define BCHP_INT_ID_MPM_CPU_L2_MSPI_INTR_0    BCHP_INT_ID_CREATE(BCHP_MPM_CPU_L2_STATUS0, BCHP_MPM_CPU_L2_STATUS0_MSPI_INTR_0_SHIFT)
#define BCHP_INT_ID_MPM_CPU_L2_MSPI_INTR_1    BCHP_INT_ID_CREATE(BCHP_MPM_CPU_L2_STATUS0, BCHP_MPM_CPU_L2_STATUS0_MSPI_INTR_1_SHIFT)
#define BCHP_INT_ID_MPM_CPU_L2_SW_INTR_0      BCHP_INT_ID_CREATE(BCHP_MPM_CPU_L2_STATUS0, BCHP_MPM_CPU_L2_STATUS0_SW_INTR_0_SHIFT)
#define BCHP_INT_ID_MPM_CPU_L2_SW_INTR_1      BCHP_INT_ID_CREATE(BCHP_MPM_CPU_L2_STATUS0, BCHP_MPM_CPU_L2_STATUS0_SW_INTR_1_SHIFT)
#define BCHP_INT_ID_MPM_CPU_L2_SW_INTR_2      BCHP_INT_ID_CREATE(BCHP_MPM_CPU_L2_STATUS0, BCHP_MPM_CPU_L2_STATUS0_SW_INTR_2_SHIFT)
#define BCHP_INT_ID_MPM_CPU_L2_SW_INTR_3      BCHP_INT_ID_CREATE(BCHP_MPM_CPU_L2_STATUS0, BCHP_MPM_CPU_L2_STATUS0_SW_INTR_3_SHIFT)
#define BCHP_INT_ID_MPM_CPU_L2_SW_INTR_4      BCHP_INT_ID_CREATE(BCHP_MPM_CPU_L2_STATUS0, BCHP_MPM_CPU_L2_STATUS0_SW_INTR_4_SHIFT)
#define BCHP_INT_ID_MPM_CPU_L2_SW_INTR_5      BCHP_INT_ID_CREATE(BCHP_MPM_CPU_L2_STATUS0, BCHP_MPM_CPU_L2_STATUS0_SW_INTR_5_SHIFT)
#define BCHP_INT_ID_STOP_REQUEST              BCHP_INT_ID_CREATE(BCHP_MPM_CPU_L2_STATUS0, BCHP_MPM_CPU_L2_STATUS0_STOP_REQUEST_SHIFT)
#define BCHP_INT_ID_TX_READY                  BCHP_INT_ID_CREATE(BCHP_MPM_CPU_L2_STATUS0, BCHP_MPM_CPU_L2_STATUS0_TX_READY_SHIFT)
#define BCHP_INT_ID_UART_ERR_INTR             BCHP_INT_ID_CREATE(BCHP_MPM_CPU_L2_STATUS0, BCHP_MPM_CPU_L2_STATUS0_UART_ERR_INTR_SHIFT)
#define BCHP_INT_ID_UART_INTR                 BCHP_INT_ID_CREATE(BCHP_MPM_CPU_L2_STATUS0, BCHP_MPM_CPU_L2_STATUS0_UART_INTR_SHIFT)
#define BCHP_INT_ID_UART_MS_INTR              BCHP_INT_ID_CREATE(BCHP_MPM_CPU_L2_STATUS0, BCHP_MPM_CPU_L2_STATUS0_UART_MS_INTR_SHIFT)
#define BCHP_INT_ID_UART_RT_INTR              BCHP_INT_ID_CREATE(BCHP_MPM_CPU_L2_STATUS0, BCHP_MPM_CPU_L2_STATUS0_UART_RT_INTR_SHIFT)
#define BCHP_INT_ID_UART_RX_INTR              BCHP_INT_ID_CREATE(BCHP_MPM_CPU_L2_STATUS0, BCHP_MPM_CPU_L2_STATUS0_UART_RX_INTR_SHIFT)
#define BCHP_INT_ID_UART_TX_INTR              BCHP_INT_ID_CREATE(BCHP_MPM_CPU_L2_STATUS0, BCHP_MPM_CPU_L2_STATUS0_UART_TX_INTR_SHIFT)
#define BCHP_INT_ID_WDOG_INTR                 BCHP_INT_ID_CREATE(BCHP_MPM_CPU_L2_STATUS0, BCHP_MPM_CPU_L2_STATUS0_WDOG_INTR_SHIFT)

#endif /* #ifndef BCHP_INT_ID_MPM_CPU_L2_H__ */

/* End of File */

/******************************************************************************
 *  Copyright (C) 2017 Broadcom. The term "Broadcom" refers to Broadcom Limited and/or its subsidiaries.
 *
 *  This program is the proprietary software of Broadcom and/or its licensors,
 *  and may only be used, duplicated, modified or distributed pursuant to the terms and
 *  conditions of a separate, written license agreement executed between you and Broadcom
 *  (an "Authorized License").  Except as set forth in an Authorized License, Broadcom grants
 *  no license (express or implied), right to use, or waiver of any kind with respect to the
 *  Software, and Broadcom expressly reserves all rights in and to the Software and all
 *  intellectual property rights therein.  IF YOU HAVE NO AUTHORIZED LICENSE, THEN YOU
 *  HAVE NO RIGHT TO USE THIS SOFTWARE IN ANY WAY, AND SHOULD IMMEDIATELY
 *  NOTIFY BROADCOM AND DISCONTINUE ALL USE OF THE SOFTWARE.
 *
 *  Except as expressly set forth in the Authorized License,
 *
 *  1.     This program, including its structure, sequence and organization, constitutes the valuable trade
 *  secrets of Broadcom, and you shall use all reasonable efforts to protect the confidentiality thereof,
 *  and to use this information only in connection with your use of Broadcom integrated circuit products.
 *
 *  2.     TO THE MAXIMUM EXTENT PERMITTED BY LAW, THE SOFTWARE IS PROVIDED "AS IS"
 *  AND WITH ALL FAULTS AND BROADCOM MAKES NO PROMISES, REPRESENTATIONS OR
 *  WARRANTIES, EITHER EXPRESS, IMPLIED, STATUTORY, OR OTHERWISE, WITH RESPECT TO
 *  THE SOFTWARE.  BROADCOM SPECIFICALLY DISCLAIMS ANY AND ALL IMPLIED WARRANTIES
 *  OF TITLE, MERCHANTABILITY, NONINFRINGEMENT, FITNESS FOR A PARTICULAR PURPOSE,
 *  LACK OF VIRUSES, ACCURACY OR COMPLETENESS, QUIET ENJOYMENT, QUIET POSSESSION
 *  OR CORRESPONDENCE TO DESCRIPTION. YOU ASSUME THE ENTIRE RISK ARISING OUT OF
 *  USE OR PERFORMANCE OF THE SOFTWARE.
 *
 *  3.     TO THE MAXIMUM EXTENT PERMITTED BY LAW, IN NO EVENT SHALL BROADCOM OR ITS
 *  LICENSORS BE LIABLE FOR (i) CONSEQUENTIAL, INCIDENTAL, SPECIAL, INDIRECT, OR
 *  EXEMPLARY DAMAGES WHATSOEVER ARISING OUT OF OR IN ANY WAY RELATING TO YOUR
 *  USE OF OR INABILITY TO USE THE SOFTWARE EVEN IF BROADCOM HAS BEEN ADVISED OF
 *  THE POSSIBILITY OF SUCH DAMAGES; OR (ii) ANY AMOUNT IN EXCESS OF THE AMOUNT
 *  ACTUALLY PAID FOR THE SOFTWARE ITSELF OR U.S. $1, WHICHEVER IS GREATER. THESE
 *  LIMITATIONS SHALL APPLY NOTWITHSTANDING ANY FAILURE OF ESSENTIAL PURPOSE OF
 *  ANY LIMITED REMEDY.
 *
 * Module Description:
 *                     DO NOT EDIT THIS FILE DIRECTLY
 *
 * This module was generated magically with RDB from a source description
 * file. You must edit the source file for changes to be made to this file.
 *
 * The launch point for all information concerning RDB is found at:
 *   http://bcgbu.broadcom.com/RDB/SitePages/Home.aspx
 *
 * Date:           Generated on               Thu Apr 20 17:11:23 2017
 *                 Full Compile MD5 Checksum  dc03e648a7ebf1a0b7abbfbfa3ccef09
 *                     (minus title and desc)
 *                 MD5 Checksum               f759be95fb54a0b6722f215ae332c1ed
 *
 * lock_release:   r_1255
 * Compiled with:  RDB Utility                unknown
 *                 RDB.pm                     1395
 *                 generate_int_id.pl         1.0
 *                 Perl Interpreter           5.008008
 *                 Operating System           linux
 *                 Script Source              home/pntruong/sbin/generate_int_id.pl
 *                 DVTSWVER                   LOCAL home/pntruong/sbin/generate_int_id.pl
 *
 *
********************************************************************************/

#include "bchp.h"
#include "bchp_upg_bsc_aon_irq.h"

#ifndef BCHP_INT_ID_UPG_BSC_AON_IRQ_H__
#define BCHP_INT_ID_UPG_BSC_AON_IRQ_H__

#define BCHP_INT_ID_UPG_BSC_AON_IRQ_spare_00  BCHP_INT_ID_CREATE(BCHP_UPG_BSC_AON_IRQ_CPU_STATUS, BCHP_UPG_BSC_AON_IRQ_CPU_STATUS_spare_00_SHIFT)
#define BCHP_INT_ID_iicb                      BCHP_INT_ID_CREATE(BCHP_UPG_BSC_AON_IRQ_CPU_STATUS, BCHP_UPG_BSC_AON_IRQ_CPU_STATUS_iicb_SHIFT)
#define BCHP_INT_ID_iicc                      BCHP_INT_ID_CREATE(BCHP_UPG_BSC_AON_IRQ_CPU_STATUS, BCHP_UPG_BSC_AON_IRQ_CPU_STATUS_iicc_SHIFT)
#define BCHP_INT_ID_iicd                      BCHP_INT_ID_CREATE(BCHP_UPG_BSC_AON_IRQ_CPU_STATUS, BCHP_UPG_BSC_AON_IRQ_CPU_STATUS_iicd_SHIFT)

#endif /* #ifndef BCHP_INT_ID_UPG_BSC_AON_IRQ_H__ */

/* End of File */

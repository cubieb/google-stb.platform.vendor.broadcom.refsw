/***************************************************************************
*     (c)2008-2014 Broadcom Corporation
*
*  This program is the proprietary software of Broadcom Corporation and/or its licensors,
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
* $brcm_Workfile: $
* $brcm_Revision: $
* $brcm_Date: $
*
* Module Description:
*
* Revision History:
*
* $brcm_Log: $
*
***************************************************************************/
#include "nexus_gpio_module.h"
#include "bchp_sun_top_ctrl.h"
#include "bchp_aon_pin_ctrl.h"
#include "bchp_gio.h"
#include "bchp_gio_aon.h"
#include "priv/nexus_core.h"

BDBG_MODULE(nexus_gpio_table);

typedef struct NEXUS_GpioTable
{
    uint32_t addr;
    unsigned mask;
    unsigned shift;
} NEXUS_GpioTable;


static const NEXUS_GpioTable g_gpioTable[] = {

/*0*/   {BCHP_SUN_TOP_CTRL_PIN_MUX_CTRL_2, BCHP_SUN_TOP_CTRL_PIN_MUX_CTRL_2_onoff_gpio_000_MASK, BCHP_SUN_TOP_CTRL_PIN_MUX_CTRL_2_onoff_gpio_000_SHIFT},
        {BCHP_SUN_TOP_CTRL_PIN_MUX_CTRL_3, BCHP_SUN_TOP_CTRL_PIN_MUX_CTRL_3_onoff_gpio_001_MASK, BCHP_SUN_TOP_CTRL_PIN_MUX_CTRL_3_onoff_gpio_001_SHIFT},
        {BCHP_SUN_TOP_CTRL_PIN_MUX_CTRL_3, BCHP_SUN_TOP_CTRL_PIN_MUX_CTRL_3_onoff_gpio_002_MASK, BCHP_SUN_TOP_CTRL_PIN_MUX_CTRL_3_onoff_gpio_002_SHIFT},
        {BCHP_SUN_TOP_CTRL_PIN_MUX_CTRL_3, BCHP_SUN_TOP_CTRL_PIN_MUX_CTRL_3_onoff_gpio_003_MASK, BCHP_SUN_TOP_CTRL_PIN_MUX_CTRL_3_onoff_gpio_003_SHIFT},
        {BCHP_SUN_TOP_CTRL_PIN_MUX_CTRL_3, BCHP_SUN_TOP_CTRL_PIN_MUX_CTRL_3_onoff_gpio_004_MASK, BCHP_SUN_TOP_CTRL_PIN_MUX_CTRL_3_onoff_gpio_004_SHIFT},
        {BCHP_SUN_TOP_CTRL_PIN_MUX_CTRL_3, BCHP_SUN_TOP_CTRL_PIN_MUX_CTRL_3_onoff_gpio_005_MASK, BCHP_SUN_TOP_CTRL_PIN_MUX_CTRL_3_onoff_gpio_005_SHIFT},
        {BCHP_SUN_TOP_CTRL_PIN_MUX_CTRL_3, BCHP_SUN_TOP_CTRL_PIN_MUX_CTRL_3_onoff_gpio_006_MASK, BCHP_SUN_TOP_CTRL_PIN_MUX_CTRL_3_onoff_gpio_006_SHIFT},
        {BCHP_SUN_TOP_CTRL_PIN_MUX_CTRL_3, BCHP_SUN_TOP_CTRL_PIN_MUX_CTRL_3_onoff_gpio_007_MASK, BCHP_SUN_TOP_CTRL_PIN_MUX_CTRL_3_onoff_gpio_007_SHIFT},
        {BCHP_SUN_TOP_CTRL_PIN_MUX_CTRL_3, BCHP_SUN_TOP_CTRL_PIN_MUX_CTRL_3_onoff_gpio_008_MASK, BCHP_SUN_TOP_CTRL_PIN_MUX_CTRL_3_onoff_gpio_008_SHIFT},

        {BCHP_SUN_TOP_CTRL_PIN_MUX_CTRL_4, BCHP_SUN_TOP_CTRL_PIN_MUX_CTRL_4_onoff_gpio_009_MASK, BCHP_SUN_TOP_CTRL_PIN_MUX_CTRL_4_onoff_gpio_009_SHIFT},
/*10*/  {BCHP_SUN_TOP_CTRL_PIN_MUX_CTRL_4, BCHP_SUN_TOP_CTRL_PIN_MUX_CTRL_4_onoff_gpio_010_MASK, BCHP_SUN_TOP_CTRL_PIN_MUX_CTRL_4_onoff_gpio_010_SHIFT},
        {BCHP_SUN_TOP_CTRL_PIN_MUX_CTRL_4, BCHP_SUN_TOP_CTRL_PIN_MUX_CTRL_4_onoff_gpio_011_MASK, BCHP_SUN_TOP_CTRL_PIN_MUX_CTRL_4_onoff_gpio_011_SHIFT},
        {BCHP_SUN_TOP_CTRL_PIN_MUX_CTRL_4, BCHP_SUN_TOP_CTRL_PIN_MUX_CTRL_4_onoff_gpio_012_MASK, BCHP_SUN_TOP_CTRL_PIN_MUX_CTRL_4_onoff_gpio_012_SHIFT},
        {BCHP_SUN_TOP_CTRL_PIN_MUX_CTRL_4, BCHP_SUN_TOP_CTRL_PIN_MUX_CTRL_4_onoff_gpio_013_MASK, BCHP_SUN_TOP_CTRL_PIN_MUX_CTRL_4_onoff_gpio_013_SHIFT},
        {BCHP_SUN_TOP_CTRL_PIN_MUX_CTRL_4, BCHP_SUN_TOP_CTRL_PIN_MUX_CTRL_4_onoff_gpio_014_MASK, BCHP_SUN_TOP_CTRL_PIN_MUX_CTRL_4_onoff_gpio_014_SHIFT},
        {BCHP_SUN_TOP_CTRL_PIN_MUX_CTRL_4, BCHP_SUN_TOP_CTRL_PIN_MUX_CTRL_4_onoff_gpio_015_MASK, BCHP_SUN_TOP_CTRL_PIN_MUX_CTRL_4_onoff_gpio_015_SHIFT},
        {BCHP_SUN_TOP_CTRL_PIN_MUX_CTRL_4, BCHP_SUN_TOP_CTRL_PIN_MUX_CTRL_4_onoff_gpio_016_MASK, BCHP_SUN_TOP_CTRL_PIN_MUX_CTRL_4_onoff_gpio_016_SHIFT},

        {BCHP_SUN_TOP_CTRL_PIN_MUX_CTRL_5, BCHP_SUN_TOP_CTRL_PIN_MUX_CTRL_5_onoff_gpio_017_MASK, BCHP_SUN_TOP_CTRL_PIN_MUX_CTRL_5_onoff_gpio_017_SHIFT},
        {BCHP_SUN_TOP_CTRL_PIN_MUX_CTRL_5, BCHP_SUN_TOP_CTRL_PIN_MUX_CTRL_5_onoff_gpio_018_MASK, BCHP_SUN_TOP_CTRL_PIN_MUX_CTRL_5_onoff_gpio_018_SHIFT},
        {BCHP_SUN_TOP_CTRL_PIN_MUX_CTRL_5, BCHP_SUN_TOP_CTRL_PIN_MUX_CTRL_5_onoff_gpio_019_MASK, BCHP_SUN_TOP_CTRL_PIN_MUX_CTRL_5_onoff_gpio_019_SHIFT},
/*20*/  {BCHP_SUN_TOP_CTRL_PIN_MUX_CTRL_5, BCHP_SUN_TOP_CTRL_PIN_MUX_CTRL_5_onoff_gpio_020_MASK, BCHP_SUN_TOP_CTRL_PIN_MUX_CTRL_5_onoff_gpio_020_SHIFT},
        {BCHP_SUN_TOP_CTRL_PIN_MUX_CTRL_5, BCHP_SUN_TOP_CTRL_PIN_MUX_CTRL_5_onoff_gpio_021_MASK, BCHP_SUN_TOP_CTRL_PIN_MUX_CTRL_5_onoff_gpio_021_SHIFT},
        {BCHP_SUN_TOP_CTRL_PIN_MUX_CTRL_5, BCHP_SUN_TOP_CTRL_PIN_MUX_CTRL_5_onoff_gpio_022_MASK, BCHP_SUN_TOP_CTRL_PIN_MUX_CTRL_5_onoff_gpio_022_SHIFT},
        {BCHP_SUN_TOP_CTRL_PIN_MUX_CTRL_5, BCHP_SUN_TOP_CTRL_PIN_MUX_CTRL_5_onoff_gpio_023_MASK, BCHP_SUN_TOP_CTRL_PIN_MUX_CTRL_5_onoff_gpio_023_SHIFT},
        {BCHP_SUN_TOP_CTRL_PIN_MUX_CTRL_5, BCHP_SUN_TOP_CTRL_PIN_MUX_CTRL_5_onoff_gpio_024_MASK, BCHP_SUN_TOP_CTRL_PIN_MUX_CTRL_5_onoff_gpio_024_SHIFT},

        {BCHP_SUN_TOP_CTRL_PIN_MUX_CTRL_6, BCHP_SUN_TOP_CTRL_PIN_MUX_CTRL_6_onoff_gpio_025_MASK, BCHP_SUN_TOP_CTRL_PIN_MUX_CTRL_6_onoff_gpio_025_SHIFT},
        {BCHP_SUN_TOP_CTRL_PIN_MUX_CTRL_6, BCHP_SUN_TOP_CTRL_PIN_MUX_CTRL_6_onoff_gpio_026_MASK, BCHP_SUN_TOP_CTRL_PIN_MUX_CTRL_6_onoff_gpio_026_SHIFT},
        {BCHP_SUN_TOP_CTRL_PIN_MUX_CTRL_6, BCHP_SUN_TOP_CTRL_PIN_MUX_CTRL_6_onoff_gpio_027_MASK, BCHP_SUN_TOP_CTRL_PIN_MUX_CTRL_6_onoff_gpio_027_SHIFT},
        {BCHP_SUN_TOP_CTRL_PIN_MUX_CTRL_6, BCHP_SUN_TOP_CTRL_PIN_MUX_CTRL_6_onoff_gpio_028_MASK, BCHP_SUN_TOP_CTRL_PIN_MUX_CTRL_6_onoff_gpio_028_SHIFT},
        {BCHP_SUN_TOP_CTRL_PIN_MUX_CTRL_6, BCHP_SUN_TOP_CTRL_PIN_MUX_CTRL_6_onoff_gpio_029_MASK, BCHP_SUN_TOP_CTRL_PIN_MUX_CTRL_6_onoff_gpio_029_SHIFT},
/*30*/  {BCHP_SUN_TOP_CTRL_PIN_MUX_CTRL_6, BCHP_SUN_TOP_CTRL_PIN_MUX_CTRL_6_onoff_gpio_030_MASK, BCHP_SUN_TOP_CTRL_PIN_MUX_CTRL_6_onoff_gpio_030_SHIFT},
        {BCHP_SUN_TOP_CTRL_PIN_MUX_CTRL_6, BCHP_SUN_TOP_CTRL_PIN_MUX_CTRL_6_onoff_gpio_031_MASK, BCHP_SUN_TOP_CTRL_PIN_MUX_CTRL_6_onoff_gpio_031_SHIFT},
        {BCHP_SUN_TOP_CTRL_PIN_MUX_CTRL_6, BCHP_SUN_TOP_CTRL_PIN_MUX_CTRL_6_onoff_gpio_032_MASK, BCHP_SUN_TOP_CTRL_PIN_MUX_CTRL_6_onoff_gpio_032_SHIFT},

        {BCHP_SUN_TOP_CTRL_PIN_MUX_CTRL_7, BCHP_SUN_TOP_CTRL_PIN_MUX_CTRL_7_onoff_gpio_033_MASK, BCHP_SUN_TOP_CTRL_PIN_MUX_CTRL_7_onoff_gpio_033_SHIFT},
        {BCHP_SUN_TOP_CTRL_PIN_MUX_CTRL_7, BCHP_SUN_TOP_CTRL_PIN_MUX_CTRL_7_onoff_gpio_034_MASK, BCHP_SUN_TOP_CTRL_PIN_MUX_CTRL_7_onoff_gpio_034_SHIFT},
        {BCHP_SUN_TOP_CTRL_PIN_MUX_CTRL_7, BCHP_SUN_TOP_CTRL_PIN_MUX_CTRL_7_onoff_gpio_035_MASK, BCHP_SUN_TOP_CTRL_PIN_MUX_CTRL_7_onoff_gpio_035_SHIFT},
        {BCHP_SUN_TOP_CTRL_PIN_MUX_CTRL_7, BCHP_SUN_TOP_CTRL_PIN_MUX_CTRL_7_onoff_gpio_036_MASK, BCHP_SUN_TOP_CTRL_PIN_MUX_CTRL_7_onoff_gpio_036_SHIFT},
        {BCHP_SUN_TOP_CTRL_PIN_MUX_CTRL_7, BCHP_SUN_TOP_CTRL_PIN_MUX_CTRL_7_onoff_gpio_037_MASK, BCHP_SUN_TOP_CTRL_PIN_MUX_CTRL_7_onoff_gpio_037_SHIFT},
        {BCHP_SUN_TOP_CTRL_PIN_MUX_CTRL_7, BCHP_SUN_TOP_CTRL_PIN_MUX_CTRL_7_onoff_gpio_038_MASK, BCHP_SUN_TOP_CTRL_PIN_MUX_CTRL_7_onoff_gpio_038_SHIFT},
        {BCHP_SUN_TOP_CTRL_PIN_MUX_CTRL_7, BCHP_SUN_TOP_CTRL_PIN_MUX_CTRL_7_onoff_gpio_039_MASK, BCHP_SUN_TOP_CTRL_PIN_MUX_CTRL_7_onoff_gpio_039_SHIFT},
/*40*/  {BCHP_SUN_TOP_CTRL_PIN_MUX_CTRL_7, BCHP_SUN_TOP_CTRL_PIN_MUX_CTRL_7_onoff_gpio_040_MASK, BCHP_SUN_TOP_CTRL_PIN_MUX_CTRL_7_onoff_gpio_040_SHIFT},

        {BCHP_SUN_TOP_CTRL_PIN_MUX_CTRL_8, BCHP_SUN_TOP_CTRL_PIN_MUX_CTRL_8_onoff_rsvd_gpio_041_MASK, BCHP_SUN_TOP_CTRL_PIN_MUX_CTRL_8_onoff_rsvd_gpio_041_SHIFT},
        {BCHP_SUN_TOP_CTRL_PIN_MUX_CTRL_8, BCHP_SUN_TOP_CTRL_PIN_MUX_CTRL_8_onoff_gpio_042_MASK, BCHP_SUN_TOP_CTRL_PIN_MUX_CTRL_8_onoff_gpio_042_SHIFT},
        {BCHP_SUN_TOP_CTRL_PIN_MUX_CTRL_8, BCHP_SUN_TOP_CTRL_PIN_MUX_CTRL_8_onoff_gpio_043_MASK, BCHP_SUN_TOP_CTRL_PIN_MUX_CTRL_8_onoff_gpio_043_SHIFT},
        {BCHP_SUN_TOP_CTRL_PIN_MUX_CTRL_8, BCHP_SUN_TOP_CTRL_PIN_MUX_CTRL_8_onoff_gpio_044_MASK, BCHP_SUN_TOP_CTRL_PIN_MUX_CTRL_8_onoff_gpio_044_SHIFT},
        {BCHP_SUN_TOP_CTRL_PIN_MUX_CTRL_8, BCHP_SUN_TOP_CTRL_PIN_MUX_CTRL_8_onoff_gpio_045_MASK, BCHP_SUN_TOP_CTRL_PIN_MUX_CTRL_8_onoff_gpio_045_SHIFT},
        {BCHP_SUN_TOP_CTRL_PIN_MUX_CTRL_8, BCHP_SUN_TOP_CTRL_PIN_MUX_CTRL_8_onoff_gpio_046_MASK, BCHP_SUN_TOP_CTRL_PIN_MUX_CTRL_8_onoff_gpio_046_SHIFT},
        {BCHP_SUN_TOP_CTRL_PIN_MUX_CTRL_8, BCHP_SUN_TOP_CTRL_PIN_MUX_CTRL_8_onoff_gpio_047_MASK, BCHP_SUN_TOP_CTRL_PIN_MUX_CTRL_8_onoff_gpio_047_SHIFT},
        {BCHP_SUN_TOP_CTRL_PIN_MUX_CTRL_8, BCHP_SUN_TOP_CTRL_PIN_MUX_CTRL_8_onoff_gpio_048_MASK, BCHP_SUN_TOP_CTRL_PIN_MUX_CTRL_8_onoff_gpio_048_SHIFT},
        {BCHP_SUN_TOP_CTRL_PIN_MUX_CTRL_9, BCHP_SUN_TOP_CTRL_PIN_MUX_CTRL_9_onoff_gpio_049_MASK, BCHP_SUN_TOP_CTRL_PIN_MUX_CTRL_9_onoff_gpio_049_SHIFT},
/*50*/  {BCHP_SUN_TOP_CTRL_PIN_MUX_CTRL_9, BCHP_SUN_TOP_CTRL_PIN_MUX_CTRL_9_onoff_gpio_050_MASK, BCHP_SUN_TOP_CTRL_PIN_MUX_CTRL_9_onoff_gpio_050_SHIFT},
        {0,0,0},
        {0,0,0},
        {0,0,0},
        {0,0,0},
        {0,0,0},
        {0,0,0},
        {0,0,0},
        {0,0,0},
        {0,0,0},
/*60*/  {0,0,0},
        {0,0,0},
        {0,0,0},
        {0,0,0},
        {0,0,0},
        {0,0,0},
        {0,0,0},
        {0,0,0},
        {0,0,0},
        {0,0,0},
/*70*/  {0,0,0},
        {0,0,0},
        {0,0,0},
        {0,0,0},
        {0,0,0},
        {0,0,0},
        {0,0,0},
        {0,0,0},
        {0,0,0},
        {0,0,0},
/*80*/  {0,0,0},
        {0,0,0},
        {BCHP_SUN_TOP_CTRL_PIN_MUX_CTRL_9, BCHP_SUN_TOP_CTRL_PIN_MUX_CTRL_9_onoff_gpio_082_MASK, BCHP_SUN_TOP_CTRL_PIN_MUX_CTRL_9_onoff_gpio_082_SHIFT},
        {BCHP_SUN_TOP_CTRL_PIN_MUX_CTRL_9, BCHP_SUN_TOP_CTRL_PIN_MUX_CTRL_9_onoff_gpio_083_MASK, BCHP_SUN_TOP_CTRL_PIN_MUX_CTRL_9_onoff_gpio_083_SHIFT},
        {BCHP_SUN_TOP_CTRL_PIN_MUX_CTRL_9, BCHP_SUN_TOP_CTRL_PIN_MUX_CTRL_9_onoff_gpio_084_MASK, BCHP_SUN_TOP_CTRL_PIN_MUX_CTRL_9_onoff_gpio_084_SHIFT},
        {BCHP_SUN_TOP_CTRL_PIN_MUX_CTRL_9, BCHP_SUN_TOP_CTRL_PIN_MUX_CTRL_9_onoff_gpio_085_MASK, BCHP_SUN_TOP_CTRL_PIN_MUX_CTRL_9_onoff_gpio_085_SHIFT},
        {BCHP_SUN_TOP_CTRL_PIN_MUX_CTRL_9, BCHP_SUN_TOP_CTRL_PIN_MUX_CTRL_9_onoff_gpio_086_MASK, BCHP_SUN_TOP_CTRL_PIN_MUX_CTRL_9_onoff_gpio_086_SHIFT},
        {BCHP_SUN_TOP_CTRL_PIN_MUX_CTRL_9, BCHP_SUN_TOP_CTRL_PIN_MUX_CTRL_9_onoff_gpio_087_MASK, BCHP_SUN_TOP_CTRL_PIN_MUX_CTRL_9_onoff_gpio_087_SHIFT},

        {BCHP_SUN_TOP_CTRL_PIN_MUX_CTRL_10, BCHP_SUN_TOP_CTRL_PIN_MUX_CTRL_10_onoff_gpio_088_MASK, BCHP_SUN_TOP_CTRL_PIN_MUX_CTRL_10_onoff_gpio_088_SHIFT},
        {BCHP_SUN_TOP_CTRL_PIN_MUX_CTRL_10, BCHP_SUN_TOP_CTRL_PIN_MUX_CTRL_10_onoff_gpio_089_MASK, BCHP_SUN_TOP_CTRL_PIN_MUX_CTRL_10_onoff_gpio_089_SHIFT},
/*90*/  {0,0,0},
        {0,0,0},
        {0,0,0},
        {0,0,0},
        {BCHP_SUN_TOP_CTRL_PIN_MUX_CTRL_10, BCHP_SUN_TOP_CTRL_PIN_MUX_CTRL_10_onoff_rsvd_gpio_094_MASK, BCHP_SUN_TOP_CTRL_PIN_MUX_CTRL_10_onoff_rsvd_gpio_094_SHIFT},
        {BCHP_SUN_TOP_CTRL_PIN_MUX_CTRL_10, BCHP_SUN_TOP_CTRL_PIN_MUX_CTRL_10_onoff_rsvd_gpio_095_MASK, BCHP_SUN_TOP_CTRL_PIN_MUX_CTRL_10_onoff_rsvd_gpio_095_SHIFT},
        {BCHP_SUN_TOP_CTRL_PIN_MUX_CTRL_10, BCHP_SUN_TOP_CTRL_PIN_MUX_CTRL_10_onoff_rsvd_gpio_096_MASK, BCHP_SUN_TOP_CTRL_PIN_MUX_CTRL_10_onoff_rsvd_gpio_096_SHIFT},
        {BCHP_SUN_TOP_CTRL_PIN_MUX_CTRL_10, BCHP_SUN_TOP_CTRL_PIN_MUX_CTRL_10_onoff_rsvd_gpio_097_MASK, BCHP_SUN_TOP_CTRL_PIN_MUX_CTRL_10_onoff_rsvd_gpio_097_SHIFT},
        {BCHP_SUN_TOP_CTRL_PIN_MUX_CTRL_10, BCHP_SUN_TOP_CTRL_PIN_MUX_CTRL_10_onoff_gpio_098_MASK, BCHP_SUN_TOP_CTRL_PIN_MUX_CTRL_10_onoff_gpio_098_SHIFT},
        {BCHP_SUN_TOP_CTRL_PIN_MUX_CTRL_10, BCHP_SUN_TOP_CTRL_PIN_MUX_CTRL_10_onoff_gpio_099_MASK, BCHP_SUN_TOP_CTRL_PIN_MUX_CTRL_10_onoff_gpio_099_SHIFT},

/*100*/ {BCHP_SUN_TOP_CTRL_PIN_MUX_CTRL_11, BCHP_SUN_TOP_CTRL_PIN_MUX_CTRL_11_onoff_gpio_100_MASK, BCHP_SUN_TOP_CTRL_PIN_MUX_CTRL_11_onoff_gpio_100_SHIFT},
        {BCHP_SUN_TOP_CTRL_PIN_MUX_CTRL_11, BCHP_SUN_TOP_CTRL_PIN_MUX_CTRL_11_onoff_gpio_101_MASK, BCHP_SUN_TOP_CTRL_PIN_MUX_CTRL_11_onoff_gpio_101_SHIFT},
        {BCHP_SUN_TOP_CTRL_PIN_MUX_CTRL_11, BCHP_SUN_TOP_CTRL_PIN_MUX_CTRL_11_onoff_gpio_102_MASK, BCHP_SUN_TOP_CTRL_PIN_MUX_CTRL_11_onoff_gpio_102_SHIFT},
        {BCHP_SUN_TOP_CTRL_PIN_MUX_CTRL_11, BCHP_SUN_TOP_CTRL_PIN_MUX_CTRL_11_onoff_gpio_103_MASK, BCHP_SUN_TOP_CTRL_PIN_MUX_CTRL_11_onoff_gpio_103_SHIFT},
        {BCHP_SUN_TOP_CTRL_PIN_MUX_CTRL_11, BCHP_SUN_TOP_CTRL_PIN_MUX_CTRL_11_onoff_gpio_104_MASK, BCHP_SUN_TOP_CTRL_PIN_MUX_CTRL_11_onoff_gpio_104_SHIFT},
        {BCHP_SUN_TOP_CTRL_PIN_MUX_CTRL_11, BCHP_SUN_TOP_CTRL_PIN_MUX_CTRL_11_onoff_gpio_105_MASK, BCHP_SUN_TOP_CTRL_PIN_MUX_CTRL_11_onoff_gpio_105_SHIFT},
        {BCHP_SUN_TOP_CTRL_PIN_MUX_CTRL_11, BCHP_SUN_TOP_CTRL_PIN_MUX_CTRL_11_onoff_gpio_106_MASK, BCHP_SUN_TOP_CTRL_PIN_MUX_CTRL_11_onoff_gpio_106_SHIFT},
        {BCHP_SUN_TOP_CTRL_PIN_MUX_CTRL_11, BCHP_SUN_TOP_CTRL_PIN_MUX_CTRL_11_onoff_gpio_107_MASK, BCHP_SUN_TOP_CTRL_PIN_MUX_CTRL_11_onoff_gpio_107_SHIFT},

        {BCHP_SUN_TOP_CTRL_PIN_MUX_CTRL_12, BCHP_SUN_TOP_CTRL_PIN_MUX_CTRL_12_onoff_gpio_108_MASK, BCHP_SUN_TOP_CTRL_PIN_MUX_CTRL_12_onoff_gpio_108_SHIFT},
        {BCHP_SUN_TOP_CTRL_PIN_MUX_CTRL_12, BCHP_SUN_TOP_CTRL_PIN_MUX_CTRL_12_onoff_gpio_109_MASK, BCHP_SUN_TOP_CTRL_PIN_MUX_CTRL_12_onoff_gpio_109_SHIFT},
/*110*/ {BCHP_SUN_TOP_CTRL_PIN_MUX_CTRL_12, BCHP_SUN_TOP_CTRL_PIN_MUX_CTRL_12_onoff_gpio_110_MASK, BCHP_SUN_TOP_CTRL_PIN_MUX_CTRL_12_onoff_gpio_110_SHIFT},
        {BCHP_SUN_TOP_CTRL_PIN_MUX_CTRL_12, BCHP_SUN_TOP_CTRL_PIN_MUX_CTRL_12_onoff_gpio_111_MASK, BCHP_SUN_TOP_CTRL_PIN_MUX_CTRL_12_onoff_gpio_111_SHIFT},
        {BCHP_SUN_TOP_CTRL_PIN_MUX_CTRL_12, BCHP_SUN_TOP_CTRL_PIN_MUX_CTRL_12_onoff_gpio_112_MASK, BCHP_SUN_TOP_CTRL_PIN_MUX_CTRL_12_onoff_gpio_112_SHIFT},
        {BCHP_SUN_TOP_CTRL_PIN_MUX_CTRL_12, BCHP_SUN_TOP_CTRL_PIN_MUX_CTRL_12_onoff_gpio_113_MASK, BCHP_SUN_TOP_CTRL_PIN_MUX_CTRL_12_onoff_gpio_113_SHIFT},
        {BCHP_SUN_TOP_CTRL_PIN_MUX_CTRL_12, BCHP_SUN_TOP_CTRL_PIN_MUX_CTRL_12_onoff_gpio_114_MASK, BCHP_SUN_TOP_CTRL_PIN_MUX_CTRL_12_onoff_gpio_114_SHIFT},
        {BCHP_SUN_TOP_CTRL_PIN_MUX_CTRL_12, BCHP_SUN_TOP_CTRL_PIN_MUX_CTRL_12_onoff_gpio_115_MASK, BCHP_SUN_TOP_CTRL_PIN_MUX_CTRL_12_onoff_gpio_115_SHIFT},

        {BCHP_SUN_TOP_CTRL_PIN_MUX_CTRL_13, BCHP_SUN_TOP_CTRL_PIN_MUX_CTRL_13_onoff_gpio_116_MASK, BCHP_SUN_TOP_CTRL_PIN_MUX_CTRL_13_onoff_gpio_116_SHIFT},
        {BCHP_SUN_TOP_CTRL_PIN_MUX_CTRL_13, BCHP_SUN_TOP_CTRL_PIN_MUX_CTRL_13_onoff_gpio_117_MASK, BCHP_SUN_TOP_CTRL_PIN_MUX_CTRL_13_onoff_gpio_117_SHIFT},
        {BCHP_SUN_TOP_CTRL_PIN_MUX_CTRL_13, BCHP_SUN_TOP_CTRL_PIN_MUX_CTRL_13_onoff_gpio_118_MASK, BCHP_SUN_TOP_CTRL_PIN_MUX_CTRL_13_onoff_gpio_118_SHIFT},
        {0,0,0},
/*120*/ {0,0,0},
        {0,0,0},
        {0,0,0},
        {0,0,0},
        {BCHP_SUN_TOP_CTRL_PIN_MUX_CTRL_13, BCHP_SUN_TOP_CTRL_PIN_MUX_CTRL_13_onoff_gpio_124_MASK, BCHP_SUN_TOP_CTRL_PIN_MUX_CTRL_13_onoff_gpio_124_SHIFT},
};

static const NEXUS_GpioTable g_sgpioTable[] = {
    {BCHP_SUN_TOP_CTRL_PIN_MUX_CTRL_2, BCHP_SUN_TOP_CTRL_PIN_MUX_CTRL_2_onoff_sgpio_00_MASK, BCHP_SUN_TOP_CTRL_PIN_MUX_CTRL_2_onoff_sgpio_00_SHIFT},
    {BCHP_SUN_TOP_CTRL_PIN_MUX_CTRL_2, BCHP_SUN_TOP_CTRL_PIN_MUX_CTRL_2_onoff_sgpio_01_MASK, BCHP_SUN_TOP_CTRL_PIN_MUX_CTRL_2_onoff_sgpio_01_SHIFT},
};

static const NEXUS_GpioTable g_aonGpioTable[] = {
    {BCHP_AON_PIN_CTRL_PIN_MUX_CTRL_0, BCHP_AON_PIN_CTRL_PIN_MUX_CTRL_0_aon_gpio_00_MASK, BCHP_AON_PIN_CTRL_PIN_MUX_CTRL_0_aon_gpio_00_SHIFT},
    {BCHP_AON_PIN_CTRL_PIN_MUX_CTRL_0, BCHP_AON_PIN_CTRL_PIN_MUX_CTRL_0_aon_gpio_01_MASK, BCHP_AON_PIN_CTRL_PIN_MUX_CTRL_0_aon_gpio_01_SHIFT},
    {BCHP_AON_PIN_CTRL_PIN_MUX_CTRL_0, BCHP_AON_PIN_CTRL_PIN_MUX_CTRL_0_aon_gpio_02_MASK, BCHP_AON_PIN_CTRL_PIN_MUX_CTRL_0_aon_gpio_02_SHIFT},
    {BCHP_AON_PIN_CTRL_PIN_MUX_CTRL_0, BCHP_AON_PIN_CTRL_PIN_MUX_CTRL_0_aon_gpio_03_MASK, BCHP_AON_PIN_CTRL_PIN_MUX_CTRL_0_aon_gpio_03_SHIFT},
    {BCHP_AON_PIN_CTRL_PIN_MUX_CTRL_0, BCHP_AON_PIN_CTRL_PIN_MUX_CTRL_0_aon_gpio_04_MASK, BCHP_AON_PIN_CTRL_PIN_MUX_CTRL_0_aon_gpio_04_SHIFT},
    {BCHP_AON_PIN_CTRL_PIN_MUX_CTRL_0, BCHP_AON_PIN_CTRL_PIN_MUX_CTRL_0_aon_gpio_05_MASK, BCHP_AON_PIN_CTRL_PIN_MUX_CTRL_0_aon_gpio_05_SHIFT},
    {BCHP_AON_PIN_CTRL_PIN_MUX_CTRL_0, BCHP_AON_PIN_CTRL_PIN_MUX_CTRL_0_aon_gpio_06_MASK, BCHP_AON_PIN_CTRL_PIN_MUX_CTRL_0_aon_gpio_06_SHIFT},
    {BCHP_AON_PIN_CTRL_PIN_MUX_CTRL_0, BCHP_AON_PIN_CTRL_PIN_MUX_CTRL_0_aon_gpio_07_MASK, BCHP_AON_PIN_CTRL_PIN_MUX_CTRL_0_aon_gpio_07_SHIFT},

    {BCHP_AON_PIN_CTRL_PIN_MUX_CTRL_1, BCHP_AON_PIN_CTRL_PIN_MUX_CTRL_1_aon_gpio_08_MASK, BCHP_AON_PIN_CTRL_PIN_MUX_CTRL_1_aon_gpio_08_SHIFT},
    {BCHP_AON_PIN_CTRL_PIN_MUX_CTRL_1, BCHP_AON_PIN_CTRL_PIN_MUX_CTRL_1_aon_gpio_09_MASK, BCHP_AON_PIN_CTRL_PIN_MUX_CTRL_1_aon_gpio_09_SHIFT},
    {BCHP_AON_PIN_CTRL_PIN_MUX_CTRL_1, BCHP_AON_PIN_CTRL_PIN_MUX_CTRL_1_aon_gpio_10_MASK, BCHP_AON_PIN_CTRL_PIN_MUX_CTRL_1_aon_gpio_10_SHIFT},
    {BCHP_AON_PIN_CTRL_PIN_MUX_CTRL_1, BCHP_AON_PIN_CTRL_PIN_MUX_CTRL_1_aon_gpio_11_MASK, BCHP_AON_PIN_CTRL_PIN_MUX_CTRL_1_aon_gpio_11_SHIFT},
    {BCHP_AON_PIN_CTRL_PIN_MUX_CTRL_1, BCHP_AON_PIN_CTRL_PIN_MUX_CTRL_1_aon_gpio_12_MASK, BCHP_AON_PIN_CTRL_PIN_MUX_CTRL_1_aon_gpio_12_SHIFT},
    {BCHP_AON_PIN_CTRL_PIN_MUX_CTRL_1, BCHP_AON_PIN_CTRL_PIN_MUX_CTRL_1_aon_gpio_13_MASK, BCHP_AON_PIN_CTRL_PIN_MUX_CTRL_1_aon_gpio_13_SHIFT},
    {BCHP_AON_PIN_CTRL_PIN_MUX_CTRL_1, BCHP_AON_PIN_CTRL_PIN_MUX_CTRL_1_aon_gpio_14_MASK, BCHP_AON_PIN_CTRL_PIN_MUX_CTRL_1_aon_gpio_14_SHIFT},
    {BCHP_AON_PIN_CTRL_PIN_MUX_CTRL_1, BCHP_AON_PIN_CTRL_PIN_MUX_CTRL_1_aon_gpio_15_MASK, BCHP_AON_PIN_CTRL_PIN_MUX_CTRL_1_aon_gpio_15_SHIFT},

};
static const NEXUS_GpioTable g_aonSgpioTable[] = {
    {BCHP_AON_PIN_CTRL_PIN_MUX_CTRL_2, BCHP_AON_PIN_CTRL_PIN_MUX_CTRL_2_aon_sgpio_00_MASK, BCHP_AON_PIN_CTRL_PIN_MUX_CTRL_2_aon_sgpio_00_SHIFT},
    {BCHP_AON_PIN_CTRL_PIN_MUX_CTRL_2, BCHP_AON_PIN_CTRL_PIN_MUX_CTRL_2_aon_sgpio_01_MASK, BCHP_AON_PIN_CTRL_PIN_MUX_CTRL_2_aon_sgpio_01_SHIFT},
    {BCHP_AON_PIN_CTRL_PIN_MUX_CTRL_2, BCHP_AON_PIN_CTRL_PIN_MUX_CTRL_2_aon_sgpio_02_MASK, BCHP_AON_PIN_CTRL_PIN_MUX_CTRL_2_aon_sgpio_02_SHIFT},
    {BCHP_AON_PIN_CTRL_PIN_MUX_CTRL_2, BCHP_AON_PIN_CTRL_PIN_MUX_CTRL_2_aon_sgpio_03_MASK, BCHP_AON_PIN_CTRL_PIN_MUX_CTRL_2_aon_sgpio_03_SHIFT},
    {BCHP_AON_PIN_CTRL_PIN_MUX_CTRL_2, BCHP_AON_PIN_CTRL_PIN_MUX_CTRL_2_aon_sgpio_04_MASK, BCHP_AON_PIN_CTRL_PIN_MUX_CTRL_2_aon_sgpio_04_SHIFT},
    {BCHP_AON_PIN_CTRL_PIN_MUX_CTRL_2, BCHP_AON_PIN_CTRL_PIN_MUX_CTRL_2_aon_sgpio_05_MASK, BCHP_AON_PIN_CTRL_PIN_MUX_CTRL_2_aon_sgpio_05_SHIFT},
};


/* if these NEXUS_NUM gpio macros are defined in nexus_platform_features.h, it is only for application convenience.
this internal definition is more reliable for implementation. */
#undef NEXUS_NUM_GPIO_PINS
#define NEXUS_NUM_GPIO_PINS (sizeof(g_gpioTable)/sizeof(g_gpioTable[0]))
#undef NEXUS_NUM_SGPIO_PINS
#define NEXUS_NUM_SGPIO_PINS (sizeof(g_sgpioTable)/sizeof(g_sgpioTable[0]))
#undef NEXUS_NUM_AON_GPIO_PINS
#define NEXUS_NUM_AON_GPIO_PINS (sizeof(g_aonGpioTable)/sizeof(g_aonGpioTable[0]))
#undef NEXUS_NUM_AON_SGPIO_PINS
#define NEXUS_NUM_AON_SGPIO_PINS (sizeof(g_aonSgpioTable)/sizeof(g_aonSgpioTable[0]))

/* These functions must be implemented per-chip */
NEXUS_Error NEXUS_Gpio_P_GetPinMux(NEXUS_GpioType type, unsigned pin, uint32_t *pAddr, uint32_t *pMask, unsigned *pShift )
{
    const NEXUS_GpioTable *pEntry=NULL;

    switch (type)
    {
        case NEXUS_GpioType_eStandard:
            if ( pin >= NEXUS_NUM_GPIO_PINS || (pEntry = g_gpioTable+pin)->addr == 0)
            {
                return BERR_TRACE(BERR_INVALID_PARAMETER);
            }
            break;
        case NEXUS_GpioType_eSpecial:
            if ( pin >= NEXUS_NUM_SGPIO_PINS ||  (pEntry = g_sgpioTable+pin)->addr == 0 )
            {
                return BERR_TRACE(BERR_INVALID_PARAMETER);
            }
            break;
        case NEXUS_GpioType_eAonStandard:
            if ( pin >= NEXUS_NUM_AON_GPIO_PINS || (pEntry = g_aonGpioTable+pin)->addr == 0 )
            {
                return BERR_TRACE(BERR_INVALID_PARAMETER);
            }
            break;
        case NEXUS_GpioType_eAonSpecial:
            if ( pin >= NEXUS_NUM_AON_SGPIO_PINS || (pEntry = g_aonSgpioTable+pin)->addr == 0 )
            {
                return BERR_TRACE(BERR_INVALID_PARAMETER);
            }
            break;
        default:
            return BERR_TRACE(BERR_INVALID_PARAMETER);
    }


    *pAddr = pEntry->addr;
    *pMask = pEntry->mask;
    *pShift = pEntry->shift;

    return BERR_SUCCESS;
}

NEXUS_Error NEXUS_Gpio_P_CheckPinmux(NEXUS_GpioType type, unsigned pin)
{
    uint32_t addr, mask, shift, val;
    NEXUS_Error rc;

    rc = NEXUS_Gpio_P_GetPinMux(type, pin, &addr, &mask, &shift);
    if (rc) return BERR_TRACE(rc);

    val = BREG_Read32(g_pCoreHandles->reg, addr);
    if ( val & mask )
    {
        /* Pin is not configured as GPIO */
        BDBG_ERR(("Pin mux register for %u is not properly configured - value %u should be 0",
                   pin, val>>shift));
        return BERR_TRACE(BERR_INVALID_PARAMETER);
    }

    return BERR_SUCCESS;
}

NEXUS_Error NEXUS_Gpio_P_GetPinData(NEXUS_GpioType type, unsigned pin, uint32_t *pAddress, uint32_t *pShift)
{

    switch (type)
            /* SGPIO Pins 9..0 are in ODEN_EXT */
    {
        case NEXUS_GpioType_eStandard:
        if ( pin < 32 )
        {
            /* GPIO Pins 31..0 are in ODEN_LO */
            *pAddress = BCHP_GIO_ODEN_LO;
            *pShift = pin;
        }
        else if ( pin < 64 )
        {
            /* GPIO Pins 63..32 are in ODEN_HI */
            *pAddress = BCHP_GIO_ODEN_HI;
            *pShift = pin-32;
        }
        else if ( pin < 96 )
        {
            /* GPIO Pins 95..64 are in ODEN_EXT_HI */
            *pAddress = BCHP_GIO_ODEN_EXT_HI;
            *pShift = pin-64;
        }
        else if ( pin < 124 )
        {
            /* GPIO Pins 123..96 are in ODEN_EXT2 */
            *pAddress = BCHP_GIO_ODEN_EXT2;
            *pShift = pin-96;
        }
        else
        {
            return BERR_TRACE(BERR_INVALID_PARAMETER);
        }
            break;
        case NEXUS_GpioType_eSpecial:
            if ( pin >= NEXUS_NUM_SGPIO_PINS)
            {
                return BERR_TRACE(BERR_INVALID_PARAMETER);
            }
            else
            {
                *pAddress = BCHP_GIO_ODEN_EXT;
                *pShift = pin;
            }
            break;
        case NEXUS_GpioType_eAonStandard:
            if ( pin >= NEXUS_NUM_AON_GPIO_PINS)
            {
                return BERR_TRACE(BERR_INVALID_PARAMETER);
            }
            else
            {
                *pAddress = BCHP_GIO_AON_ODEN_LO;
                *pShift = pin;
            }
            break;
        case NEXUS_GpioType_eAonSpecial:
            if ( pin >= NEXUS_NUM_AON_SGPIO_PINS)
            {
                return BERR_TRACE(BERR_INVALID_PARAMETER);
            }
            else
            {
                *pAddress = BCHP_GIO_AON_ODEN_EXT;
                *pShift = pin-2; /* GENERAL PURPOSE I/O DATA FOR AON_SGPIO[5:2] */
            }
            break;
        default:
            return BERR_TRACE(BERR_INVALID_PARAMETER);
    }
    return BERR_SUCCESS;
}

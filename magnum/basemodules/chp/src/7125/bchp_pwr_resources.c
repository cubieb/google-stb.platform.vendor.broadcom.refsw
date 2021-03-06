/***************************************************************************
*     Copyright (c) 2006-2014, Broadcom Corporation*
*     All Rights Reserved*
*     Confidential Property of Broadcom Corporation*
*
*  THIS SOFTWARE MAY ONLY BE USED SUBJECT TO AN EXECUTED SOFTWARE LICENSE
*  AGREEMENT  BETWEEN THE USER AND BROADCOM.  YOU HAVE NO RIGHT TO USE OR
*  EXPLOIT THIS MATERIAL EXCEPT SUBJECT TO THE TERMS OF SUCH AN AGREEMENT.
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
/***************************************************************
*
* This file is auto-generated by generate_chp_pwr.pl, based on
* bchp_pwr_resources.txt.
*
* This file contains a coded representation of power resource
* nodes and their dependencies.
*
***************************************************************/

#include "bchp_pwr.h"
#include "bchp_pwr_resources.h"
#include "bchp_pwr_resources_priv.h"

/* Resource definitions */
const BCHP_PWR_P_Resource BCHP_PWR_P_Resource_AVD[] = {{
    BCHP_PWR_P_ResourceType_eNonLeaf,
    BCHP_PWR_RESOURCE_AVD,
    "AVD"
}};

const BCHP_PWR_P_Resource BCHP_PWR_P_Resource_AVD0[] = {{
    BCHP_PWR_P_ResourceType_eNonLeaf,
    BCHP_PWR_RESOURCE_AVD0,
    "AVD0"
}};

const BCHP_PWR_P_Resource BCHP_PWR_P_Resource_RAP[] = {{
    BCHP_PWR_P_ResourceType_eNonLeaf,
    BCHP_PWR_RESOURCE_RAP,
    "RAP"
}};

const BCHP_PWR_P_Resource BCHP_PWR_P_Resource_RAP_OPEN[] = {{
    BCHP_PWR_P_ResourceType_eNonLeaf,
    BCHP_PWR_RESOURCE_RAP_OPEN,
    "RAP_OPEN"
}};

const BCHP_PWR_P_Resource BCHP_PWR_P_Resource_RAP_START[] = {{
    BCHP_PWR_P_ResourceType_eNonLeaf,
    BCHP_PWR_RESOURCE_RAP_START,
    "RAP_START"
}};

const BCHP_PWR_P_Resource BCHP_PWR_P_Resource_VDC[] = {{
    BCHP_PWR_P_ResourceType_eNonLeaf,
    BCHP_PWR_RESOURCE_VDC,
    "VDC"
}};

const BCHP_PWR_P_Resource BCHP_PWR_P_Resource_BVN[] = {{
    BCHP_PWR_P_ResourceType_eNonLeaf,
    BCHP_PWR_RESOURCE_BVN,
    "BVN"
}};

const BCHP_PWR_P_Resource BCHP_PWR_P_Resource_VDC_DAC[] = {{
    BCHP_PWR_P_ResourceType_eNonLeaf,
    BCHP_PWR_RESOURCE_VDC_DAC,
    "VDC_DAC"
}};

const BCHP_PWR_P_Resource BCHP_PWR_P_Resource_VDC_VEC[] = {{
    BCHP_PWR_P_ResourceType_eNonLeaf,
    BCHP_PWR_RESOURCE_VDC_VEC,
    "VDC_VEC"
}};

const BCHP_PWR_P_Resource BCHP_PWR_P_Resource_XPT[] = {{
    BCHP_PWR_P_ResourceType_eNonLeaf,
    BCHP_PWR_RESOURCE_XPT,
    "XPT"
}};

const BCHP_PWR_P_Resource BCHP_PWR_P_Resource_XPT_PARSER[] = {{
    BCHP_PWR_P_ResourceType_eNonLeaf,
    BCHP_PWR_RESOURCE_XPT_PARSER,
    "XPT_PARSER"
}};

const BCHP_PWR_P_Resource BCHP_PWR_P_Resource_XPT_PLAYBACK[] = {{
    BCHP_PWR_P_ResourceType_eNonLeaf,
    BCHP_PWR_RESOURCE_XPT_PLAYBACK,
    "XPT_PLAYBACK"
}};

const BCHP_PWR_P_Resource BCHP_PWR_P_Resource_XPT_RAVE[] = {{
    BCHP_PWR_P_ResourceType_eNonLeaf,
    BCHP_PWR_RESOURCE_XPT_RAVE,
    "XPT_RAVE"
}};

const BCHP_PWR_P_Resource BCHP_PWR_P_Resource_XPT_PACKETSUB[] = {{
    BCHP_PWR_P_ResourceType_eNonLeaf,
    BCHP_PWR_RESOURCE_XPT_PACKETSUB,
    "XPT_PACKETSUB"
}};

const BCHP_PWR_P_Resource BCHP_PWR_P_Resource_XPT_REMUX[] = {{
    BCHP_PWR_P_ResourceType_eNonLeaf,
    BCHP_PWR_RESOURCE_XPT_REMUX,
    "XPT_REMUX"
}};

const BCHP_PWR_P_Resource BCHP_PWR_P_Resource_XPT_108M[] = {{
    BCHP_PWR_P_ResourceType_eNonLeaf,
    BCHP_PWR_RESOURCE_XPT_108M,
    "XPT_108M"
}};

const BCHP_PWR_P_Resource BCHP_PWR_P_Resource_XPT_XMEMIF[] = {{
    BCHP_PWR_P_ResourceType_eNonLeaf,
    BCHP_PWR_RESOURCE_XPT_XMEMIF,
    "XPT_XMEMIF"
}};

const BCHP_PWR_P_Resource BCHP_PWR_P_Resource_HDMI_TX[] = {{
    BCHP_PWR_P_ResourceType_eNonLeaf,
    BCHP_PWR_RESOURCE_HDMI_TX,
    "HDMI_TX"
}};

const BCHP_PWR_P_Resource BCHP_PWR_P_Resource_HDMI_TX_CLK[] = {{
    BCHP_PWR_P_ResourceType_eNonLeaf,
    BCHP_PWR_RESOURCE_HDMI_TX_CLK,
    "HDMI_TX_CLK"
}};

const BCHP_PWR_P_Resource BCHP_PWR_P_Resource_HDMI_TX_CEC[] = {{
    BCHP_PWR_P_ResourceType_eNonLeaf,
    BCHP_PWR_RESOURCE_HDMI_TX_CEC,
    "HDMI_TX_CEC"
}};

const BCHP_PWR_P_Resource BCHP_PWR_P_Resource_M2MC[] = {{
    BCHP_PWR_P_ResourceType_eNonLeaf,
    BCHP_PWR_RESOURCE_M2MC,
    "M2MC"
}};

const BCHP_PWR_P_Resource BCHP_PWR_P_Resource_GRAPHICS3D[] = {{
    BCHP_PWR_P_ResourceType_eNonLeaf,
    BCHP_PWR_RESOURCE_GRAPHICS3D,
    "GRAPHICS3D"
}};

const BCHP_PWR_P_Resource BCHP_PWR_P_Resource_HSM[] = {{
    BCHP_PWR_P_ResourceType_eNonLeaf,
    BCHP_PWR_RESOURCE_HSM,
    "HSM"
}};

const BCHP_PWR_P_Resource BCHP_PWR_P_Resource_DMA[] = {{
    BCHP_PWR_P_ResourceType_eNonLeaf,
    BCHP_PWR_RESOURCE_DMA,
    "DMA"
}};

const BCHP_PWR_P_Resource BCHP_PWR_P_Resource_DIGITAL_FRONTEND[] = {{
    BCHP_PWR_P_ResourceType_eNonLeaf,
    BCHP_PWR_RESOURCE_DIGITAL_FRONTEND,
    "DIGITAL_FRONTEND"
}};

const BCHP_PWR_P_Resource BCHP_PWR_P_Resource_SMARTCARD[] = {{
    BCHP_PWR_P_ResourceType_eNonLeaf,
    BCHP_PWR_RESOURCE_SMARTCARD,
    "SMARTCARD"
}};

const BCHP_PWR_P_Resource BCHP_PWR_P_Resource_BINT_OPEN[] = {{
    BCHP_PWR_P_ResourceType_eNonLeaf,
    BCHP_PWR_RESOURCE_BINT_OPEN,
    "BINT_OPEN"
}};

const BCHP_PWR_P_Resource BCHP_PWR_P_Resource_MAGNUM_CONTROLLED[] = {{
    BCHP_PWR_P_ResourceType_eNonLeaf,
    BCHP_PWR_RESOURCE_MAGNUM_CONTROLLED,
    "MAGNUM_CONTROLLED"
}};

const BCHP_PWR_P_Resource BCHP_PWR_P_Resource_HW_BVN[] = {{
    BCHP_PWR_P_ResourceType_eLeaf,
    BCHP_PWR_HW_BVN,
    "HW_BVN"
}};

const BCHP_PWR_P_Resource BCHP_PWR_P_Resource_HW_BVN_108M[] = {{
    BCHP_PWR_P_ResourceType_eLeaf,
    BCHP_PWR_HW_BVN_108M,
    "HW_BVN_108M"
}};

const BCHP_PWR_P_Resource BCHP_PWR_P_Resource_HW_VDC_TDAC0[] = {{
    BCHP_PWR_P_ResourceType_eLeaf,
    BCHP_PWR_HW_VDC_TDAC0,
    "HW_VDC_TDAC0"
}};

const BCHP_PWR_P_Resource BCHP_PWR_P_Resource_HW_VDC_TDAC1[] = {{
    BCHP_PWR_P_ResourceType_eLeaf,
    BCHP_PWR_HW_VDC_TDAC1,
    "HW_VDC_TDAC1"
}};

const BCHP_PWR_P_Resource BCHP_PWR_P_Resource_HW_VDC_VEC[] = {{
    BCHP_PWR_P_ResourceType_eLeaf,
    BCHP_PWR_HW_VDC_VEC,
    "HW_VDC_VEC"
}};

const BCHP_PWR_P_Resource BCHP_PWR_P_Resource_HW_XPT_XMEMIF[] = {{
    BCHP_PWR_P_ResourceType_eLeaf,
    BCHP_PWR_HW_XPT_XMEMIF,
    "HW_XPT_XMEMIF"
}};

const BCHP_PWR_P_Resource BCHP_PWR_P_Resource_HW_XPT_RMX[] = {{
    BCHP_PWR_P_ResourceType_eLeaf,
    BCHP_PWR_HW_XPT_RMX,
    "HW_XPT_RMX"
}};

const BCHP_PWR_P_Resource BCHP_PWR_P_Resource_HW_HDMI_TX_108M[] = {{
    BCHP_PWR_P_ResourceType_eLeaf,
    BCHP_PWR_HW_HDMI_TX_108M,
    "HW_HDMI_TX_108M"
}};

const BCHP_PWR_P_Resource BCHP_PWR_P_Resource_HW_M2MC[] = {{
    BCHP_PWR_P_ResourceType_eLeaf,
    BCHP_PWR_HW_M2MC,
    "HW_M2MC"
}};

const BCHP_PWR_P_Resource BCHP_PWR_P_Resource_HW_PX3D[] = {{
    BCHP_PWR_P_ResourceType_eLeaf,
    BCHP_PWR_HW_PX3D,
    "HW_PX3D"
}};

const BCHP_PWR_P_Resource BCHP_PWR_P_Resource_HW_DMA[] = {{
    BCHP_PWR_P_ResourceType_eLeaf,
    BCHP_PWR_HW_DMA,
    "HW_DMA"
}};

const BCHP_PWR_P_Resource BCHP_PWR_P_Resource_HW_DIGITAL_FRONTEND[] = {{
    BCHP_PWR_P_ResourceType_eLeaf,
    BCHP_PWR_HW_DIGITAL_FRONTEND,
    "HW_DIGITAL_FRONTEND"
}};

const BCHP_PWR_P_Resource BCHP_PWR_P_Resource_HW_AVD_PLL_CH[] = {{
    BCHP_PWR_P_ResourceType_eLeaf,
    BCHP_PWR_HW_AVD_PLL_CH,
    "HW_AVD_PLL_CH"
}};

const BCHP_PWR_P_Resource BCHP_PWR_P_Resource_HW_RAP_PLL_CH[] = {{
    BCHP_PWR_P_ResourceType_eLeaf,
    BCHP_PWR_HW_RAP_PLL_CH,
    "HW_RAP_PLL_CH"
}};

const BCHP_PWR_P_Resource BCHP_PWR_P_Resource_HW_VCX_PLL_CTRL[] = {{
    BCHP_PWR_P_ResourceType_eLeaf,
    BCHP_PWR_HW_VCX_PLL_CTRL,
    "HW_VCX_PLL_CTRL"
}};

const BCHP_PWR_P_Resource BCHP_PWR_P_Resource_HW_SYS_PLL_0_CH3[] = {{
    BCHP_PWR_P_ResourceType_eLeaf,
    BCHP_PWR_HW_SYS_PLL_0_CH3,
    "HW_SYS_PLL_0_CH3"
}};

const BCHP_PWR_P_Resource BCHP_PWR_P_Resource_HW_AVD0[] = {{
    BCHP_PWR_P_ResourceType_eNonLeafHw,
    BCHP_PWR_HW_AVD0,
    "HW_AVD0"
}};

const BCHP_PWR_P_Resource BCHP_PWR_P_Resource_HW_RAP_OPEN[] = {{
    BCHP_PWR_P_ResourceType_eNonLeafHw,
    BCHP_PWR_HW_RAP_OPEN,
    "HW_RAP_OPEN"
}};

const BCHP_PWR_P_Resource BCHP_PWR_P_Resource_HW_RAP_START[] = {{
    BCHP_PWR_P_ResourceType_eNonLeafHw,
    BCHP_PWR_HW_RAP_START,
    "HW_RAP_START"
}};

const BCHP_PWR_P_Resource BCHP_PWR_P_Resource_HW_XPT_108M[] = {{
    BCHP_PWR_P_ResourceType_eNonLeafHw,
    BCHP_PWR_HW_XPT_108M,
    "HW_XPT_108M"
}};

const BCHP_PWR_P_Resource BCHP_PWR_P_Resource_HW_HDMI_TX_CLK[] = {{
    BCHP_PWR_P_ResourceType_eNonLeafHw,
    BCHP_PWR_HW_HDMI_TX_CLK,
    "HW_HDMI_TX_CLK"
}};

const BCHP_PWR_P_Resource BCHP_PWR_P_Resource_HW_HDMI_TX_CEC[] = {{
    BCHP_PWR_P_ResourceType_eNonLeafHw,
    BCHP_PWR_HW_HDMI_TX_CEC,
    "HW_HDMI_TX_CEC"
}};

const BCHP_PWR_P_Resource BCHP_PWR_P_Resource_HW_SCD[] = {{
    BCHP_PWR_P_ResourceType_eNonLeafHw,
    BCHP_PWR_HW_SCD,
    "HW_SCD"
}};

const BCHP_PWR_P_Resource BCHP_PWR_P_Resource_HW_ACX_PLL_CTRL[] = {{
    BCHP_PWR_P_ResourceType_eNonLeafHw,
    BCHP_PWR_HW_ACX_PLL_CTRL,
    "HW_ACX_PLL_CTRL"
}};

const BCHP_PWR_P_Resource BCHP_PWR_P_Resource_HW_VCX_PLL_CH2[] = {{
    BCHP_PWR_P_ResourceType_eNonLeafHw,
    BCHP_PWR_HW_VCX_PLL_CH2,
    "HW_VCX_PLL_CH2"
}};

const BCHP_PWR_P_Resource BCHP_PWR_P_Resource_HW_VCX_PLL_CH3[] = {{
    BCHP_PWR_P_ResourceType_eNonLeafHw,
    BCHP_PWR_HW_VCX_PLL_CH3,
    "HW_VCX_PLL_CH3"
}};

/* List of resources */
const BCHP_PWR_P_Resource* const BCHP_PWR_P_ResourceList[BCHP_PWR_P_NUM_ALLNODES] = {
    BCHP_PWR_P_Resource_AVD,
    BCHP_PWR_P_Resource_AVD0,
    BCHP_PWR_P_Resource_RAP,
    BCHP_PWR_P_Resource_RAP_OPEN,
    BCHP_PWR_P_Resource_RAP_START,
    BCHP_PWR_P_Resource_VDC,
    BCHP_PWR_P_Resource_BVN,
    BCHP_PWR_P_Resource_VDC_DAC,
    BCHP_PWR_P_Resource_VDC_VEC,
    BCHP_PWR_P_Resource_XPT,
    BCHP_PWR_P_Resource_XPT_PARSER,
    BCHP_PWR_P_Resource_XPT_PLAYBACK,
    BCHP_PWR_P_Resource_XPT_RAVE,
    BCHP_PWR_P_Resource_XPT_PACKETSUB,
    BCHP_PWR_P_Resource_XPT_REMUX,
    BCHP_PWR_P_Resource_XPT_108M,
    BCHP_PWR_P_Resource_XPT_XMEMIF,
    BCHP_PWR_P_Resource_HDMI_TX,
    BCHP_PWR_P_Resource_HDMI_TX_CLK,
    BCHP_PWR_P_Resource_HDMI_TX_CEC,
    BCHP_PWR_P_Resource_M2MC,
    BCHP_PWR_P_Resource_GRAPHICS3D,
    BCHP_PWR_P_Resource_HSM,
    BCHP_PWR_P_Resource_DMA,
    BCHP_PWR_P_Resource_DIGITAL_FRONTEND,
    BCHP_PWR_P_Resource_SMARTCARD,
    BCHP_PWR_P_Resource_BINT_OPEN,
    BCHP_PWR_P_Resource_MAGNUM_CONTROLLED,
    BCHP_PWR_P_Resource_HW_AVD0,
    BCHP_PWR_P_Resource_HW_RAP_OPEN,
    BCHP_PWR_P_Resource_HW_RAP_START,
    BCHP_PWR_P_Resource_HW_BVN,
    BCHP_PWR_P_Resource_HW_BVN_108M,
    BCHP_PWR_P_Resource_HW_VDC_TDAC0,
    BCHP_PWR_P_Resource_HW_VDC_TDAC1,
    BCHP_PWR_P_Resource_HW_VDC_VEC,
    BCHP_PWR_P_Resource_HW_XPT_108M,
    BCHP_PWR_P_Resource_HW_XPT_XMEMIF,
    BCHP_PWR_P_Resource_HW_XPT_RMX,
    BCHP_PWR_P_Resource_HW_HDMI_TX_CLK,
    BCHP_PWR_P_Resource_HW_HDMI_TX_108M,
    BCHP_PWR_P_Resource_HW_HDMI_TX_CEC,
    BCHP_PWR_P_Resource_HW_M2MC,
    BCHP_PWR_P_Resource_HW_PX3D,
    BCHP_PWR_P_Resource_HW_DMA,
    BCHP_PWR_P_Resource_HW_DIGITAL_FRONTEND,
    BCHP_PWR_P_Resource_HW_SCD,
    BCHP_PWR_P_Resource_HW_AVD_PLL_CH,
    BCHP_PWR_P_Resource_HW_RAP_PLL_CH,
    BCHP_PWR_P_Resource_HW_ACX_PLL_CTRL,
    BCHP_PWR_P_Resource_HW_VCX_PLL_CH2,
    BCHP_PWR_P_Resource_HW_VCX_PLL_CH3,
    BCHP_PWR_P_Resource_HW_VCX_PLL_CTRL,
    BCHP_PWR_P_Resource_HW_SYS_PLL_0_CH3,
};

/* Coded dependencies */
static const BCHP_PWR_P_Resource* const BCHP_PWR_P_Depend_AVD[] = {
    BCHP_PWR_P_Resource_AVD0,
    NULL
};

static const BCHP_PWR_P_Resource* const BCHP_PWR_P_Depend_AVD0[] = {
    BCHP_PWR_P_Resource_HW_AVD0,
    NULL
};

static const BCHP_PWR_P_Resource* const BCHP_PWR_P_Depend_RAP[] = {
    BCHP_PWR_P_Resource_RAP_OPEN,
    BCHP_PWR_P_Resource_RAP_START,
    NULL
};

static const BCHP_PWR_P_Resource* const BCHP_PWR_P_Depend_RAP_OPEN[] = {
    BCHP_PWR_P_Resource_HW_RAP_OPEN,
    NULL
};

static const BCHP_PWR_P_Resource* const BCHP_PWR_P_Depend_RAP_START[] = {
    BCHP_PWR_P_Resource_HW_RAP_START,
    NULL
};

static const BCHP_PWR_P_Resource* const BCHP_PWR_P_Depend_VDC[] = {
    BCHP_PWR_P_Resource_BVN,
    BCHP_PWR_P_Resource_VDC_DAC,
    BCHP_PWR_P_Resource_VDC_VEC,
    NULL
};

static const BCHP_PWR_P_Resource* const BCHP_PWR_P_Depend_BVN[] = {
    BCHP_PWR_P_Resource_HW_BVN,
    BCHP_PWR_P_Resource_HW_BVN_108M,
    NULL
};

static const BCHP_PWR_P_Resource* const BCHP_PWR_P_Depend_VDC_DAC[] = {
    BCHP_PWR_P_Resource_HW_VDC_TDAC0,
    BCHP_PWR_P_Resource_HW_VDC_TDAC1,
    NULL
};

static const BCHP_PWR_P_Resource* const BCHP_PWR_P_Depend_VDC_VEC[] = {
    BCHP_PWR_P_Resource_HW_VDC_VEC,
    NULL
};

static const BCHP_PWR_P_Resource* const BCHP_PWR_P_Depend_XPT[] = {
    BCHP_PWR_P_Resource_HW_XPT_108M,
    BCHP_PWR_P_Resource_HW_XPT_XMEMIF,
    BCHP_PWR_P_Resource_HW_XPT_RMX,
    NULL
};

static const BCHP_PWR_P_Resource* const BCHP_PWR_P_Depend_XPT_PARSER[] = {
    BCHP_PWR_P_Resource_HW_XPT_108M,
    BCHP_PWR_P_Resource_HW_XPT_XMEMIF,
    NULL
};

static const BCHP_PWR_P_Resource* const BCHP_PWR_P_Depend_XPT_PLAYBACK[] = {
    BCHP_PWR_P_Resource_HW_XPT_108M,
    BCHP_PWR_P_Resource_HW_XPT_XMEMIF,
    NULL
};

static const BCHP_PWR_P_Resource* const BCHP_PWR_P_Depend_XPT_RAVE[] = {
    BCHP_PWR_P_Resource_HW_XPT_108M,
    BCHP_PWR_P_Resource_HW_XPT_XMEMIF,
    NULL
};

static const BCHP_PWR_P_Resource* const BCHP_PWR_P_Depend_XPT_PACKETSUB[] = {
    BCHP_PWR_P_Resource_HW_XPT_108M,
    BCHP_PWR_P_Resource_HW_XPT_XMEMIF,
    NULL
};

static const BCHP_PWR_P_Resource* const BCHP_PWR_P_Depend_XPT_REMUX[] = {
    BCHP_PWR_P_Resource_HW_XPT_108M,
    BCHP_PWR_P_Resource_HW_XPT_RMX,
    NULL
};

static const BCHP_PWR_P_Resource* const BCHP_PWR_P_Depend_XPT_108M[] = {
    BCHP_PWR_P_Resource_HW_XPT_108M,
    NULL
};

static const BCHP_PWR_P_Resource* const BCHP_PWR_P_Depend_XPT_XMEMIF[] = {
    BCHP_PWR_P_Resource_HW_XPT_XMEMIF,
    NULL
};

static const BCHP_PWR_P_Resource* const BCHP_PWR_P_Depend_HDMI_TX[] = {
    BCHP_PWR_P_Resource_HDMI_TX_CLK,
    BCHP_PWR_P_Resource_HDMI_TX_CEC,
    NULL
};

static const BCHP_PWR_P_Resource* const BCHP_PWR_P_Depend_HDMI_TX_CLK[] = {
    BCHP_PWR_P_Resource_HW_HDMI_TX_CLK,
    NULL
};

static const BCHP_PWR_P_Resource* const BCHP_PWR_P_Depend_HDMI_TX_CEC[] = {
    BCHP_PWR_P_Resource_HW_HDMI_TX_CEC,
    NULL
};

static const BCHP_PWR_P_Resource* const BCHP_PWR_P_Depend_M2MC[] = {
    BCHP_PWR_P_Resource_HW_M2MC,
    NULL
};

static const BCHP_PWR_P_Resource* const BCHP_PWR_P_Depend_GRAPHICS3D[] = {
    BCHP_PWR_P_Resource_HW_M2MC,
    BCHP_PWR_P_Resource_HW_PX3D,
    NULL
};

static const BCHP_PWR_P_Resource* const BCHP_PWR_P_Depend_HSM[] = {
    BCHP_PWR_P_Resource_DMA,
    NULL
};

static const BCHP_PWR_P_Resource* const BCHP_PWR_P_Depend_DMA[] = {
    BCHP_PWR_P_Resource_HW_XPT_108M,
    BCHP_PWR_P_Resource_HW_XPT_XMEMIF,
    BCHP_PWR_P_Resource_HW_DMA,
    NULL
};

static const BCHP_PWR_P_Resource* const BCHP_PWR_P_Depend_DIGITAL_FRONTEND[] = {
    BCHP_PWR_P_Resource_HW_DIGITAL_FRONTEND,
    NULL
};

static const BCHP_PWR_P_Resource* const BCHP_PWR_P_Depend_SMARTCARD[] = {
    BCHP_PWR_P_Resource_HW_SCD,
    NULL
};

static const BCHP_PWR_P_Resource* const BCHP_PWR_P_Depend_BINT_OPEN[] = {
    BCHP_PWR_P_Resource_RAP,
    BCHP_PWR_P_Resource_VDC,
    BCHP_PWR_P_Resource_XPT,
    BCHP_PWR_P_Resource_HDMI_TX,
    BCHP_PWR_P_Resource_M2MC,
    NULL
};

static const BCHP_PWR_P_Resource* const BCHP_PWR_P_Depend_MAGNUM_CONTROLLED[] = {
    BCHP_PWR_P_Resource_AVD,
    BCHP_PWR_P_Resource_RAP,
    BCHP_PWR_P_Resource_VDC,
    BCHP_PWR_P_Resource_XPT,
    BCHP_PWR_P_Resource_HDMI_TX,
    BCHP_PWR_P_Resource_SMARTCARD,
    NULL
};

static const BCHP_PWR_P_Resource* const BCHP_PWR_P_Depend_HW_AVD0[] = {
    BCHP_PWR_P_Resource_HW_AVD_PLL_CH,
    NULL
};

static const BCHP_PWR_P_Resource* const BCHP_PWR_P_Depend_HW_RAP_OPEN[] = {
    BCHP_PWR_P_Resource_HW_RAP_PLL_CH,
    NULL
};

static const BCHP_PWR_P_Resource* const BCHP_PWR_P_Depend_HW_RAP_START[] = {
    BCHP_PWR_P_Resource_HW_RAP_OPEN,
    BCHP_PWR_P_Resource_HW_ACX_PLL_CTRL,
    BCHP_PWR_P_Resource_HW_SYS_PLL_0_CH3,
    NULL
};

static const BCHP_PWR_P_Resource* const BCHP_PWR_P_Depend_HW_XPT_108M[] = {
    BCHP_PWR_P_Resource_HW_VCX_PLL_CH2,
    NULL
};

static const BCHP_PWR_P_Resource* const BCHP_PWR_P_Depend_HW_HDMI_TX_CLK[] = {
    BCHP_PWR_P_Resource_HW_HDMI_TX_108M,
    BCHP_PWR_P_Resource_HW_BVN_108M,
    NULL
};

static const BCHP_PWR_P_Resource* const BCHP_PWR_P_Depend_HW_HDMI_TX_CEC[] = {
    BCHP_PWR_P_Resource_HW_HDMI_TX_108M,
    BCHP_PWR_P_Resource_HW_BVN_108M,
    NULL
};

static const BCHP_PWR_P_Resource* const BCHP_PWR_P_Depend_HW_SCD[] = {
    BCHP_PWR_P_Resource_HW_VCX_PLL_CH3,
    BCHP_PWR_P_Resource_HW_SYS_PLL_0_CH3,
    NULL
};

static const BCHP_PWR_P_Resource* const BCHP_PWR_P_Depend_HW_ACX_PLL_CTRL[] = {
    BCHP_PWR_P_Resource_HW_VCX_PLL_CH3,
    NULL
};

static const BCHP_PWR_P_Resource* const BCHP_PWR_P_Depend_HW_VCX_PLL_CH2[] = {
    BCHP_PWR_P_Resource_HW_VCX_PLL_CTRL,
    NULL
};

static const BCHP_PWR_P_Resource* const BCHP_PWR_P_Depend_HW_VCX_PLL_CH3[] = {
    BCHP_PWR_P_Resource_HW_VCX_PLL_CTRL,
    NULL
};

/* List of coded dependencies */
const BCHP_PWR_P_Resource* const * const BCHP_PWR_P_DependList[BCHP_PWR_P_NUM_ALLNODES] = {
    BCHP_PWR_P_Depend_AVD,
    BCHP_PWR_P_Depend_AVD0,
    BCHP_PWR_P_Depend_RAP,
    BCHP_PWR_P_Depend_RAP_OPEN,
    BCHP_PWR_P_Depend_RAP_START,
    BCHP_PWR_P_Depend_VDC,
    BCHP_PWR_P_Depend_BVN,
    BCHP_PWR_P_Depend_VDC_DAC,
    BCHP_PWR_P_Depend_VDC_VEC,
    BCHP_PWR_P_Depend_XPT,
    BCHP_PWR_P_Depend_XPT_PARSER,
    BCHP_PWR_P_Depend_XPT_PLAYBACK,
    BCHP_PWR_P_Depend_XPT_RAVE,
    BCHP_PWR_P_Depend_XPT_PACKETSUB,
    BCHP_PWR_P_Depend_XPT_REMUX,
    BCHP_PWR_P_Depend_XPT_108M,
    BCHP_PWR_P_Depend_XPT_XMEMIF,
    BCHP_PWR_P_Depend_HDMI_TX,
    BCHP_PWR_P_Depend_HDMI_TX_CLK,
    BCHP_PWR_P_Depend_HDMI_TX_CEC,
    BCHP_PWR_P_Depend_M2MC,
    BCHP_PWR_P_Depend_GRAPHICS3D,
    BCHP_PWR_P_Depend_HSM,
    BCHP_PWR_P_Depend_DMA,
    BCHP_PWR_P_Depend_DIGITAL_FRONTEND,
    BCHP_PWR_P_Depend_SMARTCARD,
    BCHP_PWR_P_Depend_BINT_OPEN,
    BCHP_PWR_P_Depend_MAGNUM_CONTROLLED,
    BCHP_PWR_P_Depend_HW_AVD0,
    BCHP_PWR_P_Depend_HW_RAP_OPEN,
    BCHP_PWR_P_Depend_HW_RAP_START,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    BCHP_PWR_P_Depend_HW_XPT_108M,
    NULL,
    NULL,
    BCHP_PWR_P_Depend_HW_HDMI_TX_CLK,
    NULL,
    BCHP_PWR_P_Depend_HW_HDMI_TX_CEC,
    NULL,
    NULL,
    NULL,
    NULL,
    BCHP_PWR_P_Depend_HW_SCD,
    NULL,
    NULL,
    BCHP_PWR_P_Depend_HW_ACX_PLL_CTRL,
    BCHP_PWR_P_Depend_HW_VCX_PLL_CH2,
    BCHP_PWR_P_Depend_HW_VCX_PLL_CH3,
    NULL,
    NULL,
};

#include "bchp_pwr_impl.c"

void BCHP_PWR_P_HW_ControlId(BCHP_Handle handle, unsigned id, bool activate)
{
    switch(id) {
        case BCHP_PWR_HW_AVD0:
            BCHP_PWR_P_HW_AVD0_Control(handle, activate);
            break;
        case BCHP_PWR_HW_RAP_OPEN:
            BCHP_PWR_P_HW_RAP_OPEN_Control(handle, activate);
            break;
        case BCHP_PWR_HW_RAP_START:
            BCHP_PWR_P_HW_RAP_START_Control(handle, activate);
            break;
        case BCHP_PWR_HW_BVN:
            BCHP_PWR_P_HW_BVN_Control(handle, activate);
            break;
        case BCHP_PWR_HW_BVN_108M:
            BCHP_PWR_P_HW_BVN_108M_Control(handle, activate);
            break;
        case BCHP_PWR_HW_VDC_TDAC0:
            BCHP_PWR_P_HW_VDC_TDAC0_Control(handle, activate);
            break;
        case BCHP_PWR_HW_VDC_TDAC1:
            BCHP_PWR_P_HW_VDC_TDAC1_Control(handle, activate);
            break;
        case BCHP_PWR_HW_VDC_VEC:
            BCHP_PWR_P_HW_VDC_VEC_Control(handle, activate);
            break;
        case BCHP_PWR_HW_XPT_108M:
            BCHP_PWR_P_HW_XPT_108M_Control(handle, activate);
            break;
        case BCHP_PWR_HW_XPT_XMEMIF:
            BCHP_PWR_P_HW_XPT_XMEMIF_Control(handle, activate);
            break;
        case BCHP_PWR_HW_XPT_RMX:
            BCHP_PWR_P_HW_XPT_RMX_Control(handle, activate);
            break;
        case BCHP_PWR_HW_HDMI_TX_CLK:
            BCHP_PWR_P_HW_HDMI_TX_CLK_Control(handle, activate);
            break;
        case BCHP_PWR_HW_HDMI_TX_108M:
            BCHP_PWR_P_HW_HDMI_TX_108M_Control(handle, activate);
            break;
        case BCHP_PWR_HW_HDMI_TX_CEC:
            BCHP_PWR_P_HW_HDMI_TX_CEC_Control(handle, activate);
            break;
        case BCHP_PWR_HW_M2MC:
            BCHP_PWR_P_HW_M2MC_Control(handle, activate);
            break;
        case BCHP_PWR_HW_PX3D:
            BCHP_PWR_P_HW_PX3D_Control(handle, activate);
            break;
        case BCHP_PWR_HW_DMA:
            BCHP_PWR_P_HW_DMA_Control(handle, activate);
            break;
        case BCHP_PWR_HW_DIGITAL_FRONTEND:
            BCHP_PWR_P_HW_DIGITAL_FRONTEND_Control(handle, activate);
            break;
        case BCHP_PWR_HW_SCD:
            BCHP_PWR_P_HW_SCD_Control(handle, activate);
            break;
        case BCHP_PWR_HW_AVD_PLL_CH:
            BCHP_PWR_P_HW_AVD_PLL_CH_Control(handle, activate);
            break;
        case BCHP_PWR_HW_RAP_PLL_CH:
            BCHP_PWR_P_HW_RAP_PLL_CH_Control(handle, activate);
            break;
        case BCHP_PWR_HW_ACX_PLL_CTRL:
            BCHP_PWR_P_HW_ACX_PLL_CTRL_Control(handle, activate);
            break;
        case BCHP_PWR_HW_VCX_PLL_CH2:
            BCHP_PWR_P_HW_VCX_PLL_CH2_Control(handle, activate);
            break;
        case BCHP_PWR_HW_VCX_PLL_CH3:
            BCHP_PWR_P_HW_VCX_PLL_CH3_Control(handle, activate);
            break;
        case BCHP_PWR_HW_VCX_PLL_CTRL:
            BCHP_PWR_P_HW_VCX_PLL_CTRL_Control(handle, activate);
            break;
        case BCHP_PWR_HW_SYS_PLL_0_CH3:
            BCHP_PWR_P_HW_SYS_PLL_0_CH3_Control(handle, activate);
            break;
        default:
            BDBG_ASSERT(0);
            break;
    }
}

void BCHP_PWR_P_HW_Control(BCHP_Handle handle, const BCHP_PWR_P_Resource *resource, bool activate)
{
    BCHP_PWR_P_HW_ControlId(handle, resource->id, activate);
}

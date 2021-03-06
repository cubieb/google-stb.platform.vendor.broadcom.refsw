/***************************************************************************
 *     Copyright (c) 2003-2013, Broadcom Corporation
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
 *
 * Module Description:
 *
 * Revision History:
 *
 * $brcm_Log: $
 *
 ***************************************************************************/
#ifndef BVDC_DISPLAYFMT_PRIV_H__
#define BVDC_DISPLAYFMT_PRIV_H__

#include "bvdc.h"
#include "bvdc_priv.h"
#include "bvdc_display_priv.h"

#ifdef __cplusplus
extern "C" {
#endif

/****************************************************************
 *  Defines
 ****************************************************************/
#define BVDC_P_480i_DROP_TABLE_SIZE      2
#define BVDC_P_480p_DROP_TABLE_SIZE      4
#define BVDC_P_480i_DROP_LINES_MAX       2
#define BVDC_P_480p_DROP_LINES_MAX       3

/* SW7445-1841 optimizing direct/integral gain for VEC/HDMI RMs */
#define BVDC_P_RM_INTEGRAL_GAIN         (4)
#define BVDC_P_RM_DIRECT_GAIN           (1)

#ifdef BVDC_TEST_FORMAT
	/* update below macros */
#endif

/****************************************************************
 *  Macros
 ****************************************************************/
/* Video format is PAL */
#define VIDEO_FORMAT_IS_PAL_BB1D1G(fmt) \
	((BFMT_VideoFmt_ePAL_B == (fmt)) || (BFMT_VideoFmt_ePAL_B1 == (fmt)) || \
	(BFMT_VideoFmt_ePAL_D1 == (fmt)) || (BFMT_VideoFmt_ePAL_G == (fmt)))

#define VIDEO_FORMAT_IS_PAL(fmt) \
	(VIDEO_FORMAT_IS_PAL_BB1D1G(fmt) || (BFMT_VideoFmt_ePAL_H == (fmt)) || \
	 (BFMT_VideoFmt_ePAL_I == (fmt)) || (BFMT_VideoFmt_ePAL_D == (fmt)) || \
	 (BFMT_VideoFmt_ePAL_K == (fmt)) || (BFMT_VideoFmt_ePAL_M == (fmt)) || \
	 (BFMT_VideoFmt_ePAL_N == (fmt)) || (BFMT_VideoFmt_ePAL_NC == (fmt)) || \
	 (BFMT_VideoFmt_ePAL_60 == (fmt)))

#define VIDEO_FORMAT_IS_PAL_443(fmt) \
	(VIDEO_FORMAT_IS_PAL_BB1D1G(fmt) || (BFMT_VideoFmt_ePAL_H == (fmt)) || \
	 (BFMT_VideoFmt_ePAL_I == (fmt)) || (BFMT_VideoFmt_ePAL_D == (fmt)) || \
	 (BFMT_VideoFmt_ePAL_K == (fmt)) ||  (BFMT_VideoFmt_ePAL_N == (fmt)))

/* Video format is NTSC-J for Japan */
#define VIDEO_FORMAT_IS_NTSC_J(fmt) \
	((BFMT_VideoFmt_eNTSC_J == (fmt)) || (BFMT_VideoFmt_e720x482_NTSC_J == (fmt)))

/* Video format is NTSC-M for North America */
#define VIDEO_FORMAT_IS_NTSC_M(fmt) \
	((BFMT_VideoFmt_eNTSC == (fmt)) || (BFMT_VideoFmt_e720x482_NTSC == (fmt)) || \
	 (BFMT_VideoFmt_eNTSC_443 == (fmt)))

/* Video format is NTSC */
#define VIDEO_FORMAT_IS_NTSC(fmt) \
	(VIDEO_FORMAT_IS_NTSC_J(fmt) || VIDEO_FORMAT_IS_NTSC_M(fmt))

/* Video format is NTSC */
#define VIDEO_FORMAT_IS_480P(fmt) \
	((BFMT_VideoFmt_e480p == (fmt)) || (BFMT_VideoFmt_e720x483p == (fmt)))

/* Video format is SECAM */
#define VIDEO_FORMAT_IS_SECAM(fmt) \
	((BFMT_VideoFmt_eSECAM_B == (fmt)) || (BFMT_VideoFmt_eSECAM_D == (fmt)) || \
	 (BFMT_VideoFmt_eSECAM_G == (fmt)) || (BFMT_VideoFmt_eSECAM_H == (fmt)) || \
	 (BFMT_VideoFmt_eSECAM_K == (fmt)) || (BFMT_VideoFmt_eSECAM_L == (fmt)))

/* 525-lines video format */
#define VIDEO_FORMAT_IS_525_LINES(fmt) \
	(VIDEO_FORMAT_IS_NTSC(fmt) || \
	 (BFMT_VideoFmt_ePAL_M == (fmt)) || (BFMT_VideoFmt_ePAL_60 == (fmt)))

/* 625-lines video format */
#define VIDEO_FORMAT_IS_625_LINES(fmt) \
	(VIDEO_FORMAT_IS_PAL_BB1D1G(fmt)|| (BFMT_VideoFmt_ePAL_H == (fmt)) || \
	 (BFMT_VideoFmt_ePAL_I == (fmt)) || (BFMT_VideoFmt_ePAL_D == (fmt)) || \
	 (BFMT_VideoFmt_ePAL_K == (fmt)) || (BFMT_VideoFmt_ePAL_N == (fmt)) || \
	 (BFMT_VideoFmt_ePAL_NC == (fmt)) || VIDEO_FORMAT_IS_SECAM(fmt))

#if BFMT_LEGACY_3DTV_SUPPORT
/* 3D 1080p video formats */
#define VIDEO_FORMAT_IS_CUSTOM_1080P3D(fmt) \
	((BFMT_VideoFmt_eCUSTOM1920x2160i_48Hz == (fmt)) || \
	 (BFMT_VideoFmt_eCUSTOM1920x2160i_60Hz == (fmt)))

/* 3D 1080p video formats that too large and require legacy BVN to take
 * TOP in Over/Under 3d format. */
#define VIDEO_FORMAT_IS_1080P_3DOU_AS(fmt) \
	((BFMT_VideoFmt_e1080p_24Hz_3DOU_AS == (fmt)) || \
	 (BFMT_VideoFmt_e1080p_30Hz_3DOU_AS == (fmt)))
#endif

/* 4K formats 50/*/
#define VIDEO_FORMAT_IS_4kx2k(fmt) \
	(VIDEO_FORMAT_IS_4kx2k_50_60HZ(fmt) || \
	 VIDEO_FORMAT_IS_4kx2k_24_25_30HZ(fmt))

#define VIDEO_FORMAT_IS_4kx2k_50_60HZ(fmt) \
	((BFMT_VideoFmt_e3840x2160p_50Hz == (fmt)) || \
	 (BFMT_VideoFmt_e3840x2160p_60Hz == (fmt)) || \
	 (BFMT_VideoFmt_e4096x2160p_50Hz == (fmt)) || \
	 (BFMT_VideoFmt_e4096x2160p_60Hz == (fmt)))

#define VIDEO_FORMAT_IS_4kx2k_24_25_30HZ(fmt) \
	((BFMT_VideoFmt_e3840x2160p_24Hz == (fmt)) || \
	 (BFMT_VideoFmt_e3840x2160p_25Hz == (fmt)) || \
	 (BFMT_VideoFmt_e3840x2160p_30Hz == (fmt)) || \
	 (BFMT_VideoFmt_e1080p_100Hz == (fmt)) || \
	 (BFMT_VideoFmt_e1080p_120Hz == (fmt)) || \
	 (BFMT_VideoFmt_e4096x2160p_24Hz == (fmt)) || \
	 (BFMT_VideoFmt_e4096x2160p_25Hz == (fmt)) || \
	 (BFMT_VideoFmt_e4096x2160p_30Hz == (fmt)))

/* Special format with for DCR/Blank level */
#define VIDEO_FORMAT_IS_SPECIAL_BLANKLEVEL(fmt) \
	(VIDEO_FORMAT_IS_NTSC(fmt) || \
	 (BFMT_VideoFmt_ePAL_M == fmt) || (BFMT_VideoFmt_ePAL_N == fmt) || \

/* Video format is PROGRESSIVE */
#define VIDEO_FORMAT_IS_PROGRESSIVE(fmt) \
	(BVDC_P_GetFormatInfo_isrsafe(fmt)->bProgressive)

/* Video format is SD */
#define VIDEO_FORMAT_IS_SD(fmt) \
	(BVDC_P_GetFormatInfo_isrsafe(fmt)->bSd)

#define VIDEO_FORMAT_IS_ED(fmt) \
	(BVDC_P_GetFormatInfo_isrsafe(fmt)->bEd)

/* Video format is HD (inlusion of Ed and Hd). */
#define VIDEO_FORMAT_IS_HD(fmt) \
	(BVDC_P_GetFormatInfo_isrsafe(fmt)->bHd || BVDC_P_GetFormatInfo_isrsafe(fmt)->bEd)

/* Video format is UHD (4k formats). */
#define VIDEO_FORMAT_IS_UHD(fmt) \
	((BFMT_VideoFmt_e3840x2160p_24Hz <= (fmt)) && ((fmt) <= BFMT_VideoFmt_e4096x2160p_60Hz))

/* Video format is HD (inlusion of Ed and Hd). */
#define VIDEO_FORMAT_IS_VESA(fmt) \
	(BVDC_P_GetFormatInfo_isrsafe(fmt)->bVesa)

/* Video format runs @ 27Mhz */
#define VIDEO_FORMAT_27Mhz(pxl_freq_bit_mask) \
	(BFMT_PXL_27MHz & (pxl_freq_bit_mask))

 /* Video format supports HDMI */
#define VIDEO_FORMAT_IS_HDMI(fmt) \
	(BVDC_P_GetFormatInfo_isrsafe(fmt)->bHdmi)

/* Video format supports macrovision */
#define VIDEO_FORMAT_SUPPORTS_MACROVISION(fmt) \
	(BVDC_P_GetFormatInfo_isrsafe(fmt)->bMacrovision)

/* Video format supports DCS */
#define VIDEO_FORMAT_SUPPORTS_DCS(fmt) \
	(BVDC_P_GetFormatInfo_isrsafe(fmt)->bDcs)

/* Video format supports drop (line) table */
#define VIDEO_FORMAT_SUPPORTS_DROP_LINE(fmt) \
	(BVDC_P_GetFormatInfo_isrsafe(fmt)->bUseDropTbl)

/* Register manipulation helper macros */
#if BVDC_P_ORTHOGONAL_VEC
#define BVDC_P_SRC_FIELD_ENUM(Register, Field, Name) \
 	BCHP_FIELD_ENUM(SDSRC_0_##Register,Field, Name)

#define BVDC_P_IT_FIELD_ENUM(Register, Field, Name) \
 	BCHP_FIELD_ENUM(IT_0_##Register,Field, Name)

#define BVDC_P_IT_FIELD_DATA(Register, Field, Data) \
 	BCHP_FIELD_DATA(IT_0_##Register,Field, Data)

#define BVDC_P_RM_FIELD_DATA(Register, Field, Data) \
	BCHP_FIELD_DATA(RM_0_##Register,Field, Data)

#define BVDC_P_VF_FIELD_ENUM(Register, Field, Name) \
	BCHP_FIELD_ENUM(VF_0_##Register,Field, Name)

#define BVDC_P_VF_FIELD_DATA(Register, Field, Data) \
	BCHP_FIELD_DATA(VF_0_##Register,Field, Data)

#define BVDC_P_VF_MASK(Register, Field) \
	BCHP_MASK(VF_0_##Register,Field)

#define BVDC_P_SM_FIELD_ENUM(Register, Field, Name) \
	BCHP_FIELD_ENUM(SM_0_##Register,Field, Name)

#define BVDC_P_SM_FIELD_DATA(Register, Field, Data) \
	BCHP_FIELD_DATA(SM_0_##Register,Field, Data)
#else
#define BVDC_P_SRC_FIELD_ENUM(Register, Field, Name) \
	BCHP_FIELD_ENUM(PRIM_SRC_##Register,Field, Name)

#define BVDC_P_IT_FIELD_ENUM(Register, Field, Name) \
 	BCHP_FIELD_ENUM(PRIM_IT_##Register,Field, Name)

#define BVDC_P_IT_FIELD_DATA(Register, Field, Data) \
	BCHP_FIELD_DATA(PRIM_IT_##Register,Field, Data)

#define BVDC_P_RM_FIELD_DATA(Register, Field, Data) \
	BCHP_FIELD_DATA(PRIM_RM_##Register,Field, Data)

#define BVDC_P_VF_FIELD_ENUM(Register, Field, Name) \
	BCHP_FIELD_ENUM(PRIM_VF_##Register,Field, Name)

#define BVDC_P_VF_FIELD_DATA(Register, Field, Data) \
	BCHP_FIELD_DATA(PRIM_VF_##Register,Field, Data)

#define BVDC_P_VF_MASK(Register, Field) \
	BCHP_MASK(PRIM_VF_##Register,Field)

#define BVDC_P_SM_FIELD_ENUM(Register, Field, Name) \
	BCHP_FIELD_ENUM(PRIM_SM_##Register,Field, Name)

#define BVDC_P_SM_FIELD_DATA(Register, Field, Data) \
	BCHP_FIELD_DATA(PRIM_SM_##Register,Field, Data)
#endif


/***************************************************************************/

#define BVDC_P_MAKE_IT_ADDR(mc3, mc2, mc1, mc0, mc6, mc5, mc4) \
	BVDC_P_IT_FIELD_DATA(ADDR_0_3,MC_3_START_ADDR, mc3) |   \
	BVDC_P_IT_FIELD_DATA(ADDR_0_3,MC_2_START_ADDR, mc2) |   \
	BVDC_P_IT_FIELD_DATA(ADDR_0_3,MC_1_START_ADDR, mc1) |   \
	BVDC_P_IT_FIELD_DATA(ADDR_0_3,MC_0_START_ADDR, mc0),    \
	BVDC_P_IT_FIELD_DATA(ADDR_4_6,MC_6_START_ADDR, mc6) |   \
	BVDC_P_IT_FIELD_DATA(ADDR_4_6,MC_5_START_ADDR, mc5) |   \
	BVDC_P_IT_FIELD_DATA(ADDR_4_6,MC_4_START_ADDR, mc4)

#define BVDC_P_MAKE_IT_STACK(reg1, reg0, reg3, reg2, reg5, reg4, reg7, reg6) \
	BVDC_P_IT_FIELD_DATA(STACK_reg_0_1, REG_1, reg1) | \
	BVDC_P_IT_FIELD_DATA(STACK_reg_0_1, REG_0, reg0),  \
	BVDC_P_IT_FIELD_DATA(STACK_reg_2_3, REG_3, reg3) | \
	BVDC_P_IT_FIELD_DATA(STACK_reg_2_3, REG_2, reg2),  \
	BVDC_P_IT_FIELD_DATA(STACK_reg_4_5, REG_5, reg5) | \
	BVDC_P_IT_FIELD_DATA(STACK_reg_4_5, REG_4, reg4),  \
	BVDC_P_IT_FIELD_DATA(STACK_reg_6_7, REG_7, reg7) | \
	BVDC_P_IT_FIELD_DATA(STACK_reg_6_7, REG_6, reg6)

#define BVDC_P_MAKE_IT_EVENT(mc6, mc5, mc4, mc3, mc2, mc1) \
	BVDC_P_IT_FIELD_DATA(EVENT_SELECTION, MC_6, mc6) | \
	BVDC_P_IT_FIELD_DATA(EVENT_SELECTION, MC_5, mc5) | \
	BVDC_P_IT_FIELD_DATA(EVENT_SELECTION, MC_4, mc4) | \
	BVDC_P_IT_FIELD_DATA(EVENT_SELECTION, MC_3, mc3) | \
	BVDC_P_IT_FIELD_DATA(EVENT_SELECTION, MC_2, mc2) | \
	BVDC_P_IT_FIELD_DATA(EVENT_SELECTION, MC_1, mc1)

#define BVDC_P_MAKE_IT_PCL_0(mux_sel, term_4, term_3, term_2, term_1,     \
	term_0, mux_e, mux_d, mux_4, mux_3)                                   \
	BVDC_P_IT_FIELD_ENUM(PCL_0, VBI_DATA_ACTIVE_ENABLE,          ON) | \
	BVDC_P_IT_FIELD_DATA(PCL_0, VBI_DATA_ACTIVE_MUX_SELECT, mux_sel) | \
	BVDC_P_IT_FIELD_ENUM(PCL_0, NEGSYNC_AND_TERM_4 ,         term_4) | \
	BVDC_P_IT_FIELD_ENUM(PCL_0, NEGSYNC_AND_TERM_3 ,         term_3) | \
	BVDC_P_IT_FIELD_ENUM(PCL_0, NEGSYNC_AND_TERM_2 ,         term_2) | \
	BVDC_P_IT_FIELD_ENUM(PCL_0, NEGSYNC_AND_TERM_1 ,         term_1) | \
	BVDC_P_IT_FIELD_ENUM(PCL_0, NEGSYNC_AND_TERM_0 ,         term_0) | \
	BVDC_P_IT_FIELD_DATA(PCL_0, NEGSYNC_MUX_E_SELECT,         mux_e) | \
	BVDC_P_IT_FIELD_DATA(PCL_0, NEGSYNC_MUX_D_SELECT,         mux_d) | \
	BVDC_P_IT_FIELD_DATA(PCL_0, NEGSYNC_MUX_4_SELECT,         mux_4) | \
	BVDC_P_IT_FIELD_DATA(PCL_0, NEGSYNC_MUX_3_SELECT,         mux_3)

#define BVDC_P_MAKE_IT_PCL_1(term_2, term_1, term_0)                     \
	BVDC_P_IT_FIELD_DATA(PCL_1, reserved0,                0)        | \
	BVDC_P_IT_FIELD_ENUM(PCL_1, BOTTLES_ENABLE,           DISABLED) | \
	BVDC_P_IT_FIELD_DATA(PCL_1, BOTTLES_MUX_A_SELECT,     2)        | \
	BVDC_P_IT_FIELD_DATA(PCL_1, BOTTLES_MUX_0_SELECT,     2)        | \
	BVDC_P_IT_FIELD_DATA(PCL_1, reserved1,                0)        | \
	BVDC_P_IT_FIELD_ENUM(PCL_1, COLOR_BURST_AND_TERM_2 ,  term_2)   | \
	BVDC_P_IT_FIELD_ENUM(PCL_1, COLOR_BURST_AND_TERM_1 ,  term_1)   | \
	BVDC_P_IT_FIELD_ENUM(PCL_1, COLOR_BURST_AND_TERM_0 ,  term_0)   | \
	BVDC_P_IT_FIELD_DATA(PCL_1, COLOR_BURST_MUX_C_SELECT, 1)        | \
	BVDC_P_IT_FIELD_DATA(PCL_1, COLOR_BURST_MUX_B_SELECT, 0)        | \
	BVDC_P_IT_FIELD_DATA(PCL_1, COLOR_BURST_MUX_2_SELECT, 2)        | \
	BVDC_P_IT_FIELD_DATA(PCL_1, COLOR_BURST_MUX_1_SELECT, 0)

#define BVDC_P_MAKE_IT_PCL_2_3(v_flip_en, v_mux_a, v_mux_0,                \
	sec_neg_sync, u_flip_en, u_mux_a, u_mux_0, new_line)                   \
	BVDC_P_IT_FIELD_DATA(PCL_2, reserved0 ,                        0) | \
	BVDC_P_IT_FIELD_ENUM(PCL_2, V_FLIP_ENABLE,             v_flip_en) | \
	BVDC_P_IT_FIELD_DATA(PCL_2, V_FLIP_MUX_A_SELECT ,        v_mux_a) | \
	BVDC_P_IT_FIELD_DATA(PCL_2, V_FLIP_MUX_0_SELECT ,        v_mux_0) | \
	BVDC_P_IT_FIELD_ENUM(PCL_2, SEC_NEG_SYNC_ENABLE,    sec_neg_sync) | \
	BVDC_P_IT_FIELD_DATA(PCL_2, SEC_NEG_SYNC_MUX_A_SELECT,         0) | \
	BVDC_P_IT_FIELD_DATA(PCL_2, SEC_NEG_SYNC_MUX_0_SELECT,         0) | \
	BVDC_P_IT_FIELD_ENUM(PCL_2, EXT_VSYNC_ENABLE,                 ON) | \
	BVDC_P_IT_FIELD_DATA(PCL_2, EXT_VSYNC_MUX_SELECT,              0) | \
	BVDC_P_IT_FIELD_ENUM(PCL_2, EXT_HSYNC_ENABLE,                 ON) | \
	BVDC_P_IT_FIELD_DATA(PCL_2, EXT_HSYNC_MUX_SELECT,              0) | \
	BVDC_P_IT_FIELD_ENUM(PCL_2, U_FLIP_ENABLE,             u_flip_en) | \
	BVDC_P_IT_FIELD_DATA(PCL_2, U_FLIP_MUX_A_SELECT ,        u_mux_a) | \
	BVDC_P_IT_FIELD_DATA(PCL_2, U_FLIP_MUX_0_SELECT ,        u_mux_0),  \
	BVDC_P_IT_FIELD_DATA(PCL_3, reserved0,                      0)    | \
	BVDC_P_IT_FIELD_ENUM(PCL_3, LINE_COUNT_CLEAR_ENABLE,       ON)    | \
	BVDC_P_IT_FIELD_DATA(PCL_3, LINE_COUNT_CLEAR_SELECT,        1)    | \
	BVDC_P_IT_FIELD_ENUM(PCL_3, NEW_LINE_ENABLE,               ON)    | \
	BVDC_P_IT_FIELD_DATA(PCL_3, NEW_LINE_MUX_SELECT,     new_line)    | \
	BVDC_P_IT_FIELD_ENUM(PCL_3, V_ACTIVE_ENABLE,               ON)    | \
	BVDC_P_IT_FIELD_DATA(PCL_3, V_ACTIVE_MUX_SELECT,            1)    | \
	BVDC_P_IT_FIELD_ENUM(PCL_3, H_ACTIVE_ENABLE,               ON)    | \
	BVDC_P_IT_FIELD_DATA(PCL_3, H_ACTIVE_MUX_SELECT,            1)    | \
	BVDC_P_IT_FIELD_ENUM(PCL_3, ODD_EVEN_ENABLE,               ON)    | \
	BVDC_P_IT_FIELD_DATA(PCL_3, ODD_EVEN_MUX_SELECT,            3)    | \
	BVDC_P_IT_FIELD_ENUM(PCL_3, VSYNC_ENABLE,                  ON)    | \
	BVDC_P_IT_FIELD_DATA(PCL_3, VSYNC_MUX_SELECT,               0)    | \
	BVDC_P_IT_FIELD_ENUM(PCL_3, VBLANK_ENABLE,                 ON)    | \
	BVDC_P_IT_FIELD_DATA(PCL_3, VBLANK_MUX_SELECT,              3)

#define BVDC_P_MAKE_IT_PCL_4(psa_1, psa_0, psa_mux_b, psa_mux_a,  \
	psa_mux_1, psa_mux_0, psb_2, psb_1, psb_0, psb_mux_c,         \
	psb_mux_b, psb_mux_2, psb_mux_1)                              \
	BVDC_P_IT_FIELD_DATA(PCL_4, reserved0,                0) | \
	BVDC_P_IT_FIELD_ENUM(PCL_4, PSA_AND_TERM_1,       psa_1) | \
	BVDC_P_IT_FIELD_ENUM(PCL_4, PSA_AND_TERM_0,       psa_0) | \
	BVDC_P_IT_FIELD_DATA(PCL_4, PSA_MUX_B_SELECT, psa_mux_b) | \
	BVDC_P_IT_FIELD_DATA(PCL_4, PSA_MUX_A_SELECT, psa_mux_a) | \
	BVDC_P_IT_FIELD_DATA(PCL_4, PSA_MUX_1_SELECT, psa_mux_1) | \
	BVDC_P_IT_FIELD_DATA(PCL_4, PSA_MUX_0_SELECT, psa_mux_0) | \
	BVDC_P_IT_FIELD_DATA(PCL_4, reserved1,                0) | \
	BVDC_P_IT_FIELD_ENUM(PCL_4, PSB_AND_TERM_2,       psb_2) | \
	BVDC_P_IT_FIELD_ENUM(PCL_4, PSB_AND_TERM_1,       psb_1) | \
	BVDC_P_IT_FIELD_ENUM(PCL_4, PSB_AND_TERM_0,       psb_0) | \
	BVDC_P_IT_FIELD_DATA(PCL_4, PSB_MUX_C_SELECT, psb_mux_c) | \
	BVDC_P_IT_FIELD_DATA(PCL_4, PSB_MUX_B_SELECT, psb_mux_b) | \
	BVDC_P_IT_FIELD_DATA(PCL_4, PSB_MUX_2_SELECT, psb_mux_2) | \
	BVDC_P_IT_FIELD_DATA(PCL_4, PSB_MUX_1_SELECT, psb_mux_1)

#define BVDC_P_MAKE_IT_TG(cycle_cnt, mc_en, line_phase)                    \
	BVDC_P_IT_FIELD_DATA(TG_CONFIG, TRIGGER_CNT_CLR_COND,          0) | \
	BVDC_P_IT_FIELD_DATA(TG_CONFIG, BVB_FRAME_CYCLE_COUNT, cycle_cnt) | \
	BVDC_P_IT_FIELD_DATA(TG_CONFIG, BVB_PHASE_SYNC,                0) | \
	BVDC_P_IT_FIELD_DATA(TG_CONFIG, MC_VIDEO_STREAM_SELECT,        0) | \
	BVDC_P_IT_FIELD_DATA(TG_CONFIG, INPUT_STREAM_ENABLE,           1) | \
	BVDC_P_IT_FIELD_DATA(TG_CONFIG, MC_ENABLES,                mc_en) | \
	BVDC_P_IT_FIELD_DATA(TG_CONFIG, SLAVE_MODE,                    0) | \
	BVDC_P_IT_FIELD_DATA(TG_CONFIG, LINE_PHASE,           line_phase) | \
	BVDC_P_IT_FIELD_DATA(TG_CONFIG, ARBITER_LATENCY,              11)

#define BVDC_P_MAKE_VF_FORMAT_ADDER(nsync, mode, c2_psync, c2_comp, c2_offset, \
	c1_psync, c1_comp, c1_offset, c0_psync, c0_comp, c0_sync, sync, offset)    \
	BVDC_P_VF_FIELD_DATA(FORMAT_ADDER, reserved0,                0) | \
	BVDC_P_VF_FIELD_DATA(FORMAT_ADDER, SECOND_NEGATIVE_SYNC, nsync) | \
	BVDC_P_VF_FIELD_DATA(FORMAT_ADDER, CLAMP_MODE,            mode) | \
	BVDC_P_VF_FIELD_DATA(FORMAT_ADDER, C2_POSITIVESYNC,   c2_psync) | \
	BVDC_P_VF_FIELD_DATA(FORMAT_ADDER, C2_COMP,            c2_comp) | \
	BVDC_P_VF_FIELD_DATA(FORMAT_ADDER, C2_OFFSET,        c2_offset) | \
	BVDC_P_VF_FIELD_DATA(FORMAT_ADDER, C1_POSITIVESYNC,   c1_psync) | \
	BVDC_P_VF_FIELD_DATA(FORMAT_ADDER, C1_COMP,            c1_comp) | \
	BVDC_P_VF_FIELD_DATA(FORMAT_ADDER, C1_OFFSET,        c1_offset) | \
	BVDC_P_VF_FIELD_DATA(FORMAT_ADDER, C0_POSITIVESYNC,   c0_psync) | \
	BVDC_P_VF_FIELD_DATA(FORMAT_ADDER, C0_COMP,            c0_comp) | \
	BVDC_P_VF_FIELD_DATA(FORMAT_ADDER, C0_SYNC,            c0_sync) | \
	BVDC_P_VF_FIELD_DATA(FORMAT_ADDER, ADD_SYNC_TO_OFFSET,    sync) | \
	BVDC_P_VF_FIELD_DATA(FORMAT_ADDER, OFFSET,              offset)

#ifdef BVDC_P_WSE_VER3 /** { **/
#define BVDC_P_MAKE_VF_MISC(sum_taps, upsample, sav_remove, vbi_pre, vbi_en) \
	BVDC_P_VF_FIELD_DATA(MISC, reserved0,               0) | \
	BVDC_P_VF_FIELD_ENUM(MISC, VF_ENABLE,              ON) | \
	BVDC_P_VF_FIELD_ENUM(MISC, SUM_OF_TAPS,      sum_taps) | \
	BVDC_P_VF_FIELD_ENUM(MISC, UPSAMPLE2X,       upsample) | \
	BVDC_P_VF_FIELD_DATA(MISC, BVB_SAV_REMOVE, sav_remove) | \
	BVDC_P_VF_FIELD_ENUM(MISC, VBI_PREFERRED,     vbi_pre) | \
	BVDC_P_VF_FIELD_ENUM(MISC, VBI_ENABLE,            OFF) | \
	BVDC_P_VF_FIELD_ENUM(MISC, C2_RAMP,      SYNC_TRANS_1) | \
	BVDC_P_VF_FIELD_ENUM(MISC, C1_RAMP,      SYNC_TRANS_1) | \
	BVDC_P_VF_FIELD_ENUM(MISC, C0_RAMP,      SYNC_TRANS_0)
#else /** } { **/
#define BVDC_P_MAKE_VF_MISC(sum_taps, upsample, sav_remove, vbi_pre, vbi_en) \
	BVDC_P_VF_FIELD_DATA(MISC, reserved0,               0) | \
	BVDC_P_VF_FIELD_ENUM(MISC, VF_ENABLE,              ON) | \
	BVDC_P_VF_FIELD_ENUM(MISC, SUM_OF_TAPS,      sum_taps) | \
	BVDC_P_VF_FIELD_ENUM(MISC, UPSAMPLE2X,       upsample) | \
	BVDC_P_VF_FIELD_DATA(MISC, BVB_SAV_REMOVE, sav_remove) | \
	BVDC_P_VF_FIELD_ENUM(MISC, VBI_PREFERRED,     vbi_pre) | \
	BVDC_P_VF_FIELD_ENUM(MISC, VBI_ENABLE,         vbi_en) | \
	BVDC_P_VF_FIELD_ENUM(MISC, C2_RAMP,      SYNC_TRANS_1) | \
	BVDC_P_VF_FIELD_ENUM(MISC, C1_RAMP,      SYNC_TRANS_1) | \
	BVDC_P_VF_FIELD_ENUM(MISC, C0_RAMP,      SYNC_TRANS_0)
#endif /** } BVDC_P_WSE_VER3 **/

#if (BVDC_P_SUPPORT_VEC_VF_VER >= 2)
	#define BVDC_P_MAKE_VF_SYNC(n2, n1, n0, p1, p0)         \
		BVDC_P_VF_FIELD_DATA(NEG_SYNC_VALUES, VALUE1, n1) | \
		BVDC_P_VF_FIELD_DATA(NEG_SYNC_VALUES, VALUE0, n0),  \
		BVDC_P_VF_FIELD_DATA(POS_SYNC_VALUES, VALUE1, p1) | \
		BVDC_P_VF_FIELD_DATA(POS_SYNC_VALUES, VALUE0, p0)
	#define BVDC_P_MAKE_VF_SYNC_EXTN(seld,n3,n2) \
		BVDC_P_VF_FIELD_DATA(NEG_SYNC_AMPLITUDE_EXTN, SEL_D_SYNC, seld) | \
		BVDC_P_VF_FIELD_DATA(NEG_SYNC_AMPLITUDE_EXTN,     VALUE3,   n3) | \
		BVDC_P_VF_FIELD_DATA(NEG_SYNC_AMPLITUDE_EXTN,     VALUE2,   n2)
#elif (BVDC_P_SUPPORT_VEC_VF_VER == 1)
	#define BVDC_P_MAKE_VF_SYNC(n2, n1, n0, p1, p0)         \
		BVDC_P_VF_FIELD_DATA(NEG_SYNC_VALUES, VALUE2, n2) | \
		BVDC_P_VF_FIELD_DATA(NEG_SYNC_VALUES, VALUE1, n1) | \
		BVDC_P_VF_FIELD_DATA(NEG_SYNC_VALUES, VALUE0, n0),  \
		BVDC_P_VF_FIELD_DATA(POS_SYNC_VALUES, VALUE1, p1) | \
		BVDC_P_VF_FIELD_DATA(POS_SYNC_VALUES, VALUE0, p0)
	#define BVDC_P_MAKE_VF_SYNC_EXTN(seld,n3,n2) \
		BVDC_P_VF_FIELD_DATA(NEG_SYNC_AMPLITUDE_EXTN, SEL_D_SYNC, seld) | \
		BVDC_P_VF_FIELD_DATA(NEG_SYNC_AMPLITUDE_EXTN,     VALUE3,   n3)
#else
	#define BVDC_P_MAKE_VF_SYNC(n2, n1, n0, p1, p0)         \
		BVDC_P_VF_FIELD_DATA(NEG_SYNC_VALUES, VALUE2, n2) | \
		BVDC_P_VF_FIELD_DATA(NEG_SYNC_VALUES, VALUE1, n1) | \
		BVDC_P_VF_FIELD_DATA(NEG_SYNC_VALUES, VALUE0, n0),  \
		BVDC_P_VF_FIELD_DATA(POS_SYNC_VALUES, VALUE1, p1) | \
		BVDC_P_VF_FIELD_DATA(POS_SYNC_VALUES, VALUE0, p0)
	#define BVDC_P_MAKE_VF_SYNC_EXTN(seld,n3,n2) \
		0
#endif

#define BVDC_P_MAKE_VF_SYNC_TRANS(trans, tap3, tap2, tap1, tap0) \
	BVDC_P_VF_FIELD_DATA(SYNC_TRANS_##trans, TAP3, tap3) | \
	BVDC_P_VF_FIELD_DATA(SYNC_TRANS_##trans, TAP2, tap2) | \
	BVDC_P_VF_FIELD_DATA(SYNC_TRANS_##trans, TAP1, tap1) | \
	BVDC_P_VF_FIELD_DATA(SYNC_TRANS_##trans, TAP0, tap0)


/***************************************************************************
 * Structures
 ***************************************************************************/
typedef struct BVDC_P_FormatInfo
{
	BFMT_VideoFmt               eVideoFmt;
	bool                        bHd; /* High Definition 720p/1080i/PC/HDMI formats */
	bool                        bEd; /* Extended Defination NTSCP/PALP progessive. */
	bool                        bSd; /* Standard Definition NTSC/PAL interlaced */
	bool                        bVesa;/* VESA standard */
	bool                        bProgressive;
	bool                        bMacrovision;
	bool                        bDcs;
	bool                        bHdmi;
	bool                        bUseDropTbl;
	BVDC_P_Display_ShaperSettings  stShaper;
} BVDC_P_FormatInfo;

typedef struct BVDC_P_FormatData
{
	BFMT_VideoFmt               eVideoFmt;
	const uint32_t             *pRamBVBInput;
	const uint32_t             *pDtRamBVBInput;
	const uint32_t             * const * apDtRamBVBInput_DropTbl;
	const uint32_t             *pItTable;
	const uint32_t             *pulItConfig;
} BVDC_P_FormatData;

typedef struct BVDC_P_SmTableInfo
{
	BFMT_VideoFmt               eVideoFmt;
	const uint32_t             *pSmTable;
} BVDC_P_SmTableInfo;

typedef struct BVDC_P_FilterTableInfo
{
	BVDC_P_OutputFilter        eOutputFilter;
	const uint32_t             *pChFilter_Ch0;
	const uint32_t             *pChFilter_Ch1;
	const uint32_t             *pChFilter_Ch2;
} BVDC_P_FilterTableInfo;

typedef struct BVDC_P_SrcControlInfo
{
	BFMT_VideoFmt               eVideoFmt;
	const uint32_t             *pulSrcControl;
} BVDC_P_SrcControlInfo;

typedef struct BVDC_P_VfTableInfo
{
	BFMT_VideoFmt               eVideoFmt;
	const uint32_t             *pVfTable;
} BVDC_P_VfTableInfo;

typedef struct BVDC_P_RmTableInfo
{
	uint64_t                    ulPixelClkRate;
	const uint32_t             *pRmTable;
	const char                 *pString;
} BVDC_P_RmTableInfo;

typedef struct BVDC_P_ColorSpaceData
{
	BVDC_P_Output                 eOutputColorSpace;
	const BVDC_P_SmTableInfo     *pSmTable_Tbl;
	const BVDC_P_OutputFilter     eSdOutputFilter;
	const BVDC_P_OutputFilter     eHdOutputFilter;
	const BVDC_P_VfTableInfo     *pSdVfTable_Tbl;
	const BVDC_P_VfTableInfo     *pHdVfTable_Tbl;
} BVDC_P_ColorSpaceData;

#if BVDC_P_ORTHOGONAL_VEC
typedef struct BVDC_P_EnvelopGeneratorSetting
{
	BFMT_VideoFmt               eVideoFmt;
	const uint32_t              ulSetting;
} BVDC_P_EnvelopGeneratorSetting;

typedef struct BVDC_P_EnvelopGeneratorInfo
{
	BVDC_P_Output                          eOutputCS;
	const BVDC_P_EnvelopGeneratorSetting  *pEG_Tbl;
} BVDC_P_EnvelopGeneratorInfo;
#endif

/***************************************************************************
 * Display private functions
 ***************************************************************************/
const uint32_t* BVDC_P_GetRamTable_isr
(
	const BVDC_P_DisplayInfo *pDispInfo,
	bool                     bArib480p
);

const uint32_t* BVDC_P_GetRamTableSub_isr
(
	const BVDC_P_DisplayInfo *pDispInfo,
	bool                     bArib480p
);

const uint32_t* BVDC_P_GetItTable_isr
(
	const BVDC_P_DisplayInfo *pDispInfo
);

const uint32_t* BVDC_P_GetItTableSub_isr
(
	const BVDC_P_DisplayInfo *pDispInfo
);

uint32_t BVDC_P_GetItConfigSub_isr
(
	const BVDC_P_DisplayInfo *pDispInfo
);

uint32_t BVDC_P_GetItConfig_isr
(
	const BVDC_P_DisplayInfo *pDispInfo
);

const uint32_t* BVDC_P_GetDtramTable_isr
(
	const BVDC_P_DisplayInfo    *pDispInfo,
	const BFMT_VideoInfo        *pFmtInfo,
	bool                         bArib480p
);

const uint32_t* BVDC_P_Get656DtramTable_isr
(
	const BVDC_P_DisplayInfo *pDispInfo
);

const uint32_t* BVDC_P_GetSmTable_isr
(
	const BVDC_P_DisplayInfo *pDispInfo,
	BVDC_P_Output			  eOutputCS
);

BERR_Code BVDC_P_GetChFilters_isr
(
	const BVDC_P_DisplayInfo *pDispInfo,
	BVDC_P_Output             eOutputColorSpace,
	const uint32_t          **ppChFilter_Ch0,
	const uint32_t          **ppChFilter_Ch1,
	const uint32_t          **ppChFilter_Ch2
);

uint32_t BVDC_P_GetSrcControl_isr
(
	BVDC_P_Output eOutputCS
);

void BVDC_P_FillVfTable_isr
(
	const BVDC_P_DisplayInfo *pDispInfo,
	BVDC_P_Output             eOutputColorSpace,
	uint32_t                 *pTable,
	uint32_t                 *pulNsaeReg,
	BVDC_P_Display_ShaperSettings *pstShaperSettings
);

#if BVDC_P_ORTHOGONAL_VEC
uint32_t BVDC_P_GetVfEnvelopGenerator_isr
(
	const BVDC_P_DisplayInfo *pDispInfo,
	BVDC_P_Output             eOutputCS
);
#endif

BERR_Code BVDC_P_GetRmTable_isr
(
	const BVDC_P_DisplayInfo *pDispInfo,
	const BFMT_VideoInfo     *pFmtInfo,
	const uint32_t          **ppTable,
	bool                      bFullRate,
	BAVC_VdcDisplay_Info     *pRateInfo
);

const char* BVDC_P_GetRmString_isr
(
	const BVDC_P_DisplayInfo *pDispInfo,
	const BFMT_VideoInfo     *pFmtInfo
);

const BVDC_P_RateInfo* BVDC_P_HdmiRmTable_isr
(
	BFMT_VideoFmt             eVideoFmt,
	uint64_t                  ulPixelClkRate,
	BAVC_HDMI_BitsPerPixel    eHdmiColorDepth,
	BAVC_HDMI_PixelRepetition eHdmiPixelRepetition,
	BAVC_Colorspace           eColorComponent
);

#if BVDC_P_SUPPORT_MHL
uint64_t BVDC_P_PxlFreqToMhlFreq_isr
	( uint64_t ulPxlFreq);
#endif

const BVDC_P_FormatInfo* BVDC_P_GetFormatInfo_isrsafe
(
	BFMT_VideoFmt                      eVideoFmt
);

void BVDC_P_Display_GetCscTable_isr
	( const BVDC_P_DisplayInfo        *pDispInfo,
	  BVDC_P_Output                    eOutputColorSpace,
	  const BVDC_P_DisplayCscMatrix  **ppCscTable );

void BVDC_P_Display_GetDviCscTable_isr
	( const BVDC_P_DisplayInfo        *pDispInfo,
	  const BVDC_P_DisplayCscMatrix  **ppCscTable );

void BVDC_P_Display_Get656CscTable_isr
	( const BVDC_P_DisplayInfo        *pDispInfo,
	  bool                             bBypass,
	  const BVDC_P_DisplayCscMatrix  **ppCscTable );

/* Returns H, then V. */
const uint32_t* BVDC_P_GetDviDtgToggles_isr
(
	const BVDC_P_DisplayInfo *pDispInfo
);

#ifdef BVDC_P_DISPLAY_DUMP
void BVDC_P_Display_Dump_aulVfTable (const char* name, const uint32_t* table);
void BVDC_P_Display_Dump_aulChFilterTbl (
	const char* name, const uint32_t* table);
void BVDC_P_Display_Dump_aulRmTable (const char* name, const uint32_t* table);
void BVDC_P_Display_Dump_aulItTable (const char* name, const uint32_t* table);
void BVDC_P_Display_Dump_ulItConfig (const char* name, uint32_t value);
void BVDC_P_Display_Dump_aulSmTable (const char* name, const uint32_t* table);
#endif

#ifdef __cplusplus
}
#endif

#endif /* #ifndef BVDC_DISPLAYFMT_PRIV_H__ */
/* End of file. */

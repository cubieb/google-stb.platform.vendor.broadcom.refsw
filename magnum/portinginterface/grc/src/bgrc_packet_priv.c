/***************************************************************************
 *     Copyright (c) 2010-2014, Broadcom Corporation
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
 * Module Description: GRC Packet Private API
 *
 * Revision History:
 *
 * $brcm_Log: $
 *
 ***************************************************************************/

#include "bchp_common.h"
#include "bchp_m2mc.h"
#ifdef BCHP_M2MC1_REG_START
#include "bchp_m2mc1.h"
#endif

#include "bgrc.h"
#include "bgrc_packet.h"
#include "bgrc_packet_priv.h"
#include "bgrc_private.h"

BDBG_MODULE(BGRC);

#if !B_REFSW_MINIMAL
/***************************************************************************/
void BGRC_PACKET_P_PrintRegisters( BGRC_Handle hGrc )
{
	BSTD_UNUSED(hGrc);
	BDBG_ERR(( "LIST_CTRL                       %08x", BGRC_P_ReadReg32( hGrc->hRegister, LIST_CTRL ) ));
	BDBG_ERR(( "LIST_STATUS                     %08x", BGRC_P_ReadReg32( hGrc->hRegister, LIST_STATUS ) ));
	BDBG_ERR(( "LIST_FIRST_PKT_ADDR             %08x", BGRC_P_ReadReg32( hGrc->hRegister, LIST_FIRST_PKT_ADDR ) ));
	BDBG_ERR(( "LIST_CURR_PKT_ADDR              %08x", BGRC_P_ReadReg32( hGrc->hRegister, LIST_CURR_PKT_ADDR ) ));
	BDBG_ERR(( "BLIT_STATUS                     %08x", BGRC_P_ReadReg32( hGrc->hRegister, BLIT_STATUS ) ));
	BDBG_ERR(( "BLIT_SRC_ADDRESS                %08x", BGRC_P_ReadReg32( hGrc->hRegister, BLIT_SRC_ADDRESS ) ));
	BDBG_ERR(( "BLIT_DEST_ADDRESS               %08x", BGRC_P_ReadReg32( hGrc->hRegister, BLIT_DEST_ADDRESS ) ));
	BDBG_ERR(( "BLIT_OUTPUT_ADDRESS             %08x", BGRC_P_ReadReg32( hGrc->hRegister, BLIT_OUTPUT_ADDRESS ) ));
	BDBG_ERR(( "BLIT_MEM_HI                     %08x", BGRC_P_ReadReg32( hGrc->hRegister, BLIT_MEM_HI ) ));
	BDBG_ERR(( "BLIT_MEM_LO                     %08x", BGRC_P_ReadReg32( hGrc->hRegister, BLIT_MEM_LO ) ));
	BDBG_ERR(( "SRC_FEEDER_ENABLE               %08x", BGRC_P_ReadReg32( hGrc->hRegister, SRC_FEEDER_ENABLE ) ));
	BDBG_ERR(( "SRC_SURFACE_ADDR_0              %08x", BGRC_P_ReadReg32( hGrc->hRegister, SRC_SURFACE_ADDR_0 ) ));
	BDBG_ERR(( "SRC_SURFACE_STRIDE_0            %08x", BGRC_P_ReadReg32( hGrc->hRegister, SRC_SURFACE_STRIDE_0 ) ));
	BDBG_ERR(( "SRC_SURFACE_ADDR_1              %08x", BGRC_P_ReadReg32( hGrc->hRegister, SRC_SURFACE_ADDR_1 ) ));
	BDBG_ERR(( "SRC_SURFACE_STRIDE_1            %08x", BGRC_P_ReadReg32( hGrc->hRegister, SRC_SURFACE_STRIDE_1 ) ));
	BDBG_ERR(( "SRC_SURFACE_FORMAT_DEF_1        %08x", BGRC_P_ReadReg32( hGrc->hRegister, SRC_SURFACE_FORMAT_DEF_1 ) ));
	BDBG_ERR(( "SRC_SURFACE_FORMAT_DEF_2        %08x", BGRC_P_ReadReg32( hGrc->hRegister, SRC_SURFACE_FORMAT_DEF_2 ) ));
	BDBG_ERR(( "SRC_SURFACE_FORMAT_DEF_3        %08x", BGRC_P_ReadReg32( hGrc->hRegister, SRC_SURFACE_FORMAT_DEF_3 ) ));
	BDBG_ERR(( "SRC_SURFACE_1_FORMAT_DEF_1      %08x", BGRC_P_ReadReg32( hGrc->hRegister, SRC_SURFACE_1_FORMAT_DEF_1 ) ));
	BDBG_ERR(( "SRC_SURFACE_1_FORMAT_DEF_2      %08x", BGRC_P_ReadReg32( hGrc->hRegister, SRC_SURFACE_1_FORMAT_DEF_2 ) ));
	BDBG_ERR(( "SRC_SURFACE_1_FORMAT_DEF_3      %08x", BGRC_P_ReadReg32( hGrc->hRegister, SRC_SURFACE_1_FORMAT_DEF_3 ) ));
	BDBG_ERR(( "SRC_W_ALPHA                     %08x", BGRC_P_ReadReg32( hGrc->hRegister, SRC_W_ALPHA ) ));
	BDBG_ERR(( "SRC_CONSTANT_COLOR              %08x", BGRC_P_ReadReg32( hGrc->hRegister, SRC_CONSTANT_COLOR ) ));
	BDBG_ERR(( "DEST_FEEDER_ENABLE              %08x", BGRC_P_ReadReg32( hGrc->hRegister, DEST_FEEDER_ENABLE ) ));
	BDBG_ERR(( "DEST_SURFACE_ADDR_0             %08x", BGRC_P_ReadReg32( hGrc->hRegister, DEST_SURFACE_ADDR_0 ) ));
	BDBG_ERR(( "DEST_SURFACE_STRIDE_0           %08x", BGRC_P_ReadReg32( hGrc->hRegister, DEST_SURFACE_STRIDE_0 ) ));
	BDBG_ERR(( "DEST_SURFACE_ADDR_1             %08x", BGRC_P_ReadReg32( hGrc->hRegister, DEST_SURFACE_ADDR_1 ) ));
	BDBG_ERR(( "DEST_SURFACE_STRIDE_1           %08x", BGRC_P_ReadReg32( hGrc->hRegister, DEST_SURFACE_STRIDE_1 ) ));
	BDBG_ERR(( "DEST_SURFACE_FORMAT_DEF_1       %08x", BGRC_P_ReadReg32( hGrc->hRegister, DEST_SURFACE_FORMAT_DEF_1 ) ));
	BDBG_ERR(( "DEST_SURFACE_FORMAT_DEF_2       %08x", BGRC_P_ReadReg32( hGrc->hRegister, DEST_SURFACE_FORMAT_DEF_2 ) ));
	BDBG_ERR(( "DEST_SURFACE_FORMAT_DEF_3       %08x", BGRC_P_ReadReg32( hGrc->hRegister, DEST_SURFACE_FORMAT_DEF_3 ) ));
	BDBG_ERR(( "DEST_W_ALPHA                    %08x", BGRC_P_ReadReg32( hGrc->hRegister, DEST_W_ALPHA ) ));
	BDBG_ERR(( "DEST_CONSTANT_COLOR             %08x", BGRC_P_ReadReg32( hGrc->hRegister, DEST_CONSTANT_COLOR ) ));
	BDBG_ERR(( "OUTPUT_FEEDER_ENABLE            %08x", BGRC_P_ReadReg32( hGrc->hRegister, OUTPUT_FEEDER_ENABLE ) ));
	BDBG_ERR(( "OUTPUT_SURFACE_ADDR_0           %08x", BGRC_P_ReadReg32( hGrc->hRegister, OUTPUT_SURFACE_ADDR_0 ) ));
	BDBG_ERR(( "OUTPUT_SURFACE_STRIDE_0         %08x", BGRC_P_ReadReg32( hGrc->hRegister, OUTPUT_SURFACE_STRIDE_0 ) ));
	BDBG_ERR(( "OUTPUT_SURFACE_ADDR_1           %08x", BGRC_P_ReadReg32( hGrc->hRegister, OUTPUT_SURFACE_ADDR_1 ) ));
	BDBG_ERR(( "OUTPUT_SURFACE_STRIDE_1         %08x", BGRC_P_ReadReg32( hGrc->hRegister, OUTPUT_SURFACE_STRIDE_1 ) ));
	BDBG_ERR(( "OUTPUT_SURFACE_FORMAT_DEF_1     %08x", BGRC_P_ReadReg32( hGrc->hRegister, OUTPUT_SURFACE_FORMAT_DEF_1 ) ));
	BDBG_ERR(( "OUTPUT_SURFACE_FORMAT_DEF_2     %08x", BGRC_P_ReadReg32( hGrc->hRegister, OUTPUT_SURFACE_FORMAT_DEF_2 ) ));
	BDBG_ERR(( "OUTPUT_SURFACE_FORMAT_DEF_3     %08x", BGRC_P_ReadReg32( hGrc->hRegister, OUTPUT_SURFACE_FORMAT_DEF_3 ) ));
	BDBG_ERR(( "BLIT_HEADER                     %08x", BGRC_P_ReadReg32( hGrc->hRegister, BLIT_HEADER ) ));
	BDBG_ERR(( "BLIT_SRC_TOP_LEFT               %08x", BGRC_P_ReadReg32( hGrc->hRegister, BLIT_SRC_TOP_LEFT ) ));
	BDBG_ERR(( "BLIT_SRC_SIZE                   %08x", BGRC_P_ReadReg32( hGrc->hRegister, BLIT_SRC_SIZE ) ));
	BDBG_ERR(( "BLIT_SRC_TOP_LEFT_1             %08x", BGRC_P_ReadReg32( hGrc->hRegister, BLIT_SRC_TOP_LEFT_1 ) ));
	BDBG_ERR(( "BLIT_SRC_SIZE_1                 %08x", BGRC_P_ReadReg32( hGrc->hRegister, BLIT_SRC_SIZE_1 ) ));
	BDBG_ERR(( "BLIT_SRC_STRIPE_HEIGHT_WIDTH_0  %08x", BGRC_P_ReadReg32( hGrc->hRegister, BLIT_SRC_STRIPE_HEIGHT_WIDTH_0 ) ));
	BDBG_ERR(( "BLIT_SRC_STRIPE_HEIGHT_WIDTH_1  %08x", BGRC_P_ReadReg32( hGrc->hRegister, BLIT_SRC_STRIPE_HEIGHT_WIDTH_1 ) ));
	BDBG_ERR(( "BLIT_DEST_TOP_LEFT              %08x", BGRC_P_ReadReg32( hGrc->hRegister, BLIT_DEST_TOP_LEFT ) ));
	BDBG_ERR(( "BLIT_DEST_SIZE                  %08x", BGRC_P_ReadReg32( hGrc->hRegister, BLIT_DEST_SIZE ) ));
	BDBG_ERR(( "BLIT_OUTPUT_TOP_LEFT            %08x", BGRC_P_ReadReg32( hGrc->hRegister, BLIT_OUTPUT_TOP_LEFT ) ));
	BDBG_ERR(( "BLIT_OUTPUT_SIZE                %08x", BGRC_P_ReadReg32( hGrc->hRegister, BLIT_OUTPUT_SIZE ) ));
	BDBG_ERR(( "BLIT_INPUT_STRIPE_WIDTH         %08x", BGRC_P_ReadReg32( hGrc->hRegister, BLIT_INPUT_STRIPE_WIDTH ) ));
	BDBG_ERR(( "BLIT_INPUT_STRIPE_WIDTH_1       %08x", BGRC_P_ReadReg32( hGrc->hRegister, BLIT_INPUT_STRIPE_WIDTH_1 ) ));
	BDBG_ERR(( "BLIT_OUTPUT_STRIPE_WIDTH        %08x", BGRC_P_ReadReg32( hGrc->hRegister, BLIT_OUTPUT_STRIPE_WIDTH ) ));
	BDBG_ERR(( "BLIT_STRIPE_OVERLAP             %08x", BGRC_P_ReadReg32( hGrc->hRegister, BLIT_STRIPE_OVERLAP ) ));
	BDBG_ERR(( "BLIT_STRIPE_OVERLAP_1           %08x", BGRC_P_ReadReg32( hGrc->hRegister, BLIT_STRIPE_OVERLAP_1 ) ));
	BDBG_ERR(( "BLIT_CTRL                       %08x", BGRC_P_ReadReg32( hGrc->hRegister, BLIT_CTRL ) ));
	BDBG_ERR(( "SCALER_CTRL                     %08x", BGRC_P_ReadReg32( hGrc->hRegister, SCALER_CTRL ) ));
	BDBG_ERR(( "HORIZ_AVERAGER_COUNT            %08x", BGRC_P_ReadReg32( hGrc->hRegister, HORIZ_AVERAGER_COUNT ) ));
	BDBG_ERR(( "HORIZ_AVERAGER_COEFF            %08x", BGRC_P_ReadReg32( hGrc->hRegister, HORIZ_AVERAGER_COEFF ) ));
	BDBG_ERR(( "VERT_AVERAGER_COUNT             %08x", BGRC_P_ReadReg32( hGrc->hRegister, VERT_AVERAGER_COUNT ) ));
	BDBG_ERR(( "VERT_AVERAGER_COEFF             %08x", BGRC_P_ReadReg32( hGrc->hRegister, VERT_AVERAGER_COEFF ) ));
	BDBG_ERR(( "HORIZ_SCALER_INITIAL_PHASE      %08x", BGRC_P_ReadReg32( hGrc->hRegister, HORIZ_SCALER_INITIAL_PHASE ) ));
	BDBG_ERR(( "HORIZ_SCALER_STEP               %08x", BGRC_P_ReadReg32( hGrc->hRegister, HORIZ_SCALER_STEP ) ));
	BDBG_ERR(( "HORIZ_SCALER_1_INITIAL_PHASE    %08x", BGRC_P_ReadReg32( hGrc->hRegister, HORIZ_SCALER_1_INITIAL_PHASE ) ));
	BDBG_ERR(( "HORIZ_SCALER_1_STEP             %08x", BGRC_P_ReadReg32( hGrc->hRegister, HORIZ_SCALER_1_STEP ) ));
	BDBG_ERR(( "VERT_SCALER_INITIAL_PHASE       %08x", BGRC_P_ReadReg32( hGrc->hRegister, VERT_SCALER_INITIAL_PHASE ) ));
	BDBG_ERR(( "VERT_SCALER_STEP                %08x", BGRC_P_ReadReg32( hGrc->hRegister, VERT_SCALER_STEP ) ));
	BDBG_ERR(( "VERT_SCALER_1_INITIAL_PHASE     %08x", BGRC_P_ReadReg32( hGrc->hRegister, VERT_SCALER_1_INITIAL_PHASE ) ));
	BDBG_ERR(( "VERT_SCALER_1_STEP              %08x", BGRC_P_ReadReg32( hGrc->hRegister, VERT_SCALER_1_STEP ) ));
	BDBG_ERR(( "BLEND_COLOR_OP                  %08x", BGRC_P_ReadReg32( hGrc->hRegister, BLEND_COLOR_OP ) ));
	BDBG_ERR(( "BLEND_ALPHA_OP                  %08x", BGRC_P_ReadReg32( hGrc->hRegister, BLEND_ALPHA_OP ) ));
	BDBG_ERR(( "BLEND_CONSTANT_COLOR            %08x", BGRC_P_ReadReg32( hGrc->hRegister, BLEND_CONSTANT_COLOR ) ));
	BDBG_ERR(( "BLEND_COLOR_KEY_ACTION          %08x", BGRC_P_ReadReg32( hGrc->hRegister, BLEND_COLOR_KEY_ACTION ) ));
	BDBG_ERR(( "ROP_OPERATION                   %08x", BGRC_P_ReadReg32( hGrc->hRegister, ROP_OPERATION ) ));
	BDBG_ERR(( "ROP_PATTERN_TOP                 %08x", BGRC_P_ReadReg32( hGrc->hRegister, ROP_PATTERN_TOP ) ));
	BDBG_ERR(( "ROP_PATTERN_BOTTOM              %08x", BGRC_P_ReadReg32( hGrc->hRegister, ROP_PATTERN_BOTTOM ) ));
	BDBG_ERR(( "ROP_PATTERN_COLOR_0             %08x", BGRC_P_ReadReg32( hGrc->hRegister, ROP_PATTERN_COLOR_0 ) ));
	BDBG_ERR(( "ROP_PATTERN_COLOR_1             %08x", BGRC_P_ReadReg32( hGrc->hRegister, ROP_PATTERN_COLOR_1 ) ));
	BDBG_ERR(( "SRC_COLOR_KEY_HIGH              %08x", BGRC_P_ReadReg32( hGrc->hRegister, SRC_COLOR_KEY_HIGH ) ));
	BDBG_ERR(( "SRC_COLOR_KEY_LOW               %08x", BGRC_P_ReadReg32( hGrc->hRegister, SRC_COLOR_KEY_LOW ) ));
	BDBG_ERR(( "SRC_COLOR_KEY_MASK              %08x", BGRC_P_ReadReg32( hGrc->hRegister, SRC_COLOR_KEY_MASK ) ));
	BDBG_ERR(( "SRC_COLOR_KEY_REPLACEMENT       %08x", BGRC_P_ReadReg32( hGrc->hRegister, SRC_COLOR_KEY_REPLACEMENT ) ));
	BDBG_ERR(( "SRC_COLOR_KEY_REPLACEMENT_MASK  %08x", BGRC_P_ReadReg32( hGrc->hRegister, SRC_COLOR_KEY_REPLACEMENT_MASK ) ));
	BDBG_ERR(( "DEST_COLOR_KEY_HIGH             %08x", BGRC_P_ReadReg32( hGrc->hRegister, DEST_COLOR_KEY_HIGH ) ));
	BDBG_ERR(( "DEST_COLOR_KEY_LOW              %08x", BGRC_P_ReadReg32( hGrc->hRegister, DEST_COLOR_KEY_LOW ) ));
	BDBG_ERR(( "DEST_COLOR_KEY_MASK             %08x", BGRC_P_ReadReg32( hGrc->hRegister, DEST_COLOR_KEY_MASK ) ));
	BDBG_ERR(( "DEST_COLOR_KEY_REPLACEMENT      %08x", BGRC_P_ReadReg32( hGrc->hRegister, DEST_COLOR_KEY_REPLACEMENT ) ));
	BDBG_ERR(( "DEST_COLOR_KEY_REPLACEMENT_MASK %08x", BGRC_P_ReadReg32( hGrc->hRegister, DEST_COLOR_KEY_REPLACEMENT_MASK ) ));
	BDBG_ERR(( "SRC_CM_C00_C01                  %08x", BGRC_P_ReadReg32( hGrc->hRegister, SRC_CM_C00_C01 ) ));
	BDBG_ERR(( "SRC_CM_C02_C03                  %08x", BGRC_P_ReadReg32( hGrc->hRegister, SRC_CM_C02_C03 ) ));
	BDBG_ERR(( "SRC_CM_C04                      %08x", BGRC_P_ReadReg32( hGrc->hRegister, SRC_CM_C04 ) ));
	BDBG_ERR(( "SRC_CM_C10_C11                  %08x", BGRC_P_ReadReg32( hGrc->hRegister, SRC_CM_C10_C11 ) ));
	BDBG_ERR(( "SRC_CM_C12_C13                  %08x", BGRC_P_ReadReg32( hGrc->hRegister, SRC_CM_C12_C13 ) ));
	BDBG_ERR(( "SRC_CM_C14                      %08x", BGRC_P_ReadReg32( hGrc->hRegister, SRC_CM_C14 ) ));
	BDBG_ERR(( "SRC_CM_C20_C21                  %08x", BGRC_P_ReadReg32( hGrc->hRegister, SRC_CM_C20_C21 ) ));
	BDBG_ERR(( "SRC_CM_C22_C23                  %08x", BGRC_P_ReadReg32( hGrc->hRegister, SRC_CM_C22_C23 ) ));
	BDBG_ERR(( "SRC_CM_C24                      %08x", BGRC_P_ReadReg32( hGrc->hRegister, SRC_CM_C24 ) ));
	BDBG_ERR(( " " ));
}
#endif

/***************************************************************************/
#define M2MC_FT_Default       (0L << BGRC_M2MC(SRC_SURFACE_FORMAT_DEF_1_FORMAT_TYPE_SHIFT))
#define M2MC_FT_WRGB1555      (1L << BGRC_M2MC(SRC_SURFACE_FORMAT_DEF_1_FORMAT_TYPE_SHIFT))
#define M2MC_FT_WRGB1565      (2L << BGRC_M2MC(SRC_SURFACE_FORMAT_DEF_1_FORMAT_TYPE_SHIFT))
#define M2MC_FT_Palette       (3L << BGRC_M2MC(SRC_SURFACE_FORMAT_DEF_1_FORMAT_TYPE_SHIFT))
#define M2MC_FT_YCbCr422      (4L << BGRC_M2MC(SRC_SURFACE_FORMAT_DEF_1_FORMAT_TYPE_SHIFT))
#define M2MC_FT_Alpha         (5L << BGRC_M2MC(SRC_SURFACE_FORMAT_DEF_1_FORMAT_TYPE_SHIFT))
#define M2MC_FT_YCbCr422_10   (6L << BGRC_M2MC(SRC_SURFACE_FORMAT_DEF_1_FORMAT_TYPE_SHIFT))
#define M2MC_FT_YCbCr420      (7L << BGRC_M2MC(SRC_SURFACE_FORMAT_DEF_1_FORMAT_TYPE_SHIFT))
#define M2MC_FT_YCbCr444_10   (8L << BGRC_M2MC(SRC_SURFACE_FORMAT_DEF_1_FORMAT_TYPE_SHIFT))
#define M2MC_FT_YCbCr420_10   (9L << BGRC_M2MC(SRC_SURFACE_FORMAT_DEF_1_FORMAT_TYPE_SHIFT))
#define M2MC_FT_CompressedARGB8888    (10L << BGRC_M2MC(SRC_SURFACE_FORMAT_DEF_1_FORMAT_TYPE_SHIFT))
#define M2MC_FT_YCbCr420_10_Striped   (14L << BGRC_M2MC(SRC_SURFACE_FORMAT_DEF_1_FORMAT_TYPE_SHIFT))
#define M2MC_FT_YCbCr420_Striped      (15L << BGRC_M2MC(SRC_SURFACE_FORMAT_DEF_1_FORMAT_TYPE_SHIFT))

#define M2MC_DISABLE_SHIFT    BGRC_M2MC(SRC_SURFACE_FORMAT_DEF_3_CH0_DISABLE_SHIFT)
#define M2MC_CHANNEL_MASK     ((1L << BGRC_M2MC(SRC_SURFACE_FORMAT_DEF_1_FORMAT_TYPE_SHIFT)) - 1)

/***************************************************************************/
static const uint32_t s_BGRC_PACKET_P_DevicePixelFormats[][3] =
{
	{ 0x00000000, 0x00000000, 0x00000000 }, /* Unknown */
	{ 0x00000565 | M2MC_FT_Default,            0x000B0500, 0x00000008 << M2MC_DISABLE_SHIFT }, /* R5_G6_B5 */
	{ 0x00000565 | M2MC_FT_Default,            0x0000050B, 0x00000008 << M2MC_DISABLE_SHIFT }, /* B5_G6_R5 */
	{ 0x00001555 | M2MC_FT_Default,            0x0F0A0500, 0x00000000 << M2MC_DISABLE_SHIFT }, /* A1_R5_G5_B5 */
	{ 0x00001555 | M2MC_FT_Default,            0x0F0A0500, 0x00000008 << M2MC_DISABLE_SHIFT }, /* X1_R5_G5_B5 */
	{ 0x00001555 | M2MC_FT_Default,            0x0F00050A, 0x00000000 << M2MC_DISABLE_SHIFT }, /* A1_B5_G5_R5 */
	{ 0x00001555 | M2MC_FT_Default,            0x0F00050A, 0x00000008 << M2MC_DISABLE_SHIFT }, /* X1_B5_G5_R5 */
	{ 0x00001555 | M2MC_FT_Default,            0x000B0601, 0x00000000 << M2MC_DISABLE_SHIFT }, /* R5_G5_B5_A1 */
	{ 0x00001555 | M2MC_FT_Default,            0x000B0601, 0x00000008 << M2MC_DISABLE_SHIFT }, /* R5_G5_B5_X1 */
	{ 0x00001555 | M2MC_FT_Default,            0x0001060B, 0x00000000 << M2MC_DISABLE_SHIFT }, /* B5_G5_R5_A1 */
	{ 0x00001555 | M2MC_FT_Default,            0x0001060B, 0x00000008 << M2MC_DISABLE_SHIFT }, /* B5_G5_R5_X1 */
	{ 0x00004444 | M2MC_FT_Default,            0x0C080400, 0x00000000 << M2MC_DISABLE_SHIFT }, /* A4_R4_G4_B4 */
	{ 0x00004444 | M2MC_FT_Default,            0x0C080400, 0x00000008 << M2MC_DISABLE_SHIFT }, /* X4_R4_G4_B4 */
	{ 0x00004444 | M2MC_FT_Default,            0x0C000408, 0x00000000 << M2MC_DISABLE_SHIFT }, /* A4_B4_G4_R4 */
	{ 0x00004444 | M2MC_FT_Default,            0x0C000408, 0x00000008 << M2MC_DISABLE_SHIFT }, /* X4_B4_G4_R4 */
	{ 0x00004444 | M2MC_FT_Default,            0x000C0804, 0x00000000 << M2MC_DISABLE_SHIFT }, /* R4_G4_B4_A4 */
	{ 0x00004444 | M2MC_FT_Default,            0x000C0804, 0x00000008 << M2MC_DISABLE_SHIFT }, /* R4_G4_B4_X4 */
	{ 0x00004444 | M2MC_FT_Default,            0x0004080C, 0x00000000 << M2MC_DISABLE_SHIFT }, /* B4_G4_R4_A4 */
	{ 0x00004444 | M2MC_FT_Default,            0x0004080C, 0x00000008 << M2MC_DISABLE_SHIFT }, /* B4_G4_R4_X4 */
	{ 0x00008888 | M2MC_FT_Default,            0x18100800, 0x00000000 << M2MC_DISABLE_SHIFT }, /* A8_R8_G8_B8 */
	{ 0x00008888 | M2MC_FT_Default,            0x18100800, 0x00000008 << M2MC_DISABLE_SHIFT }, /* X8_R8_G8_B8 */
	{ 0x00008888 | M2MC_FT_Default,            0x18000810, 0x00000000 << M2MC_DISABLE_SHIFT }, /* A8_B8_G8_R8 */
	{ 0x00008888 | M2MC_FT_Default,            0x18000810, 0x00000008 << M2MC_DISABLE_SHIFT }, /* X8_B8_G8_R8 */
	{ 0x00008888 | M2MC_FT_Default,            0x00181008, 0x00000000 << M2MC_DISABLE_SHIFT }, /* R8_G8_B8_A8 */
	{ 0x00008888 | M2MC_FT_Default,            0x00181008, 0x00000008 << M2MC_DISABLE_SHIFT }, /* R8_G8_B8_X8 */
	{ 0x00008888 | M2MC_FT_Default,            0x00081018, 0x00000000 << M2MC_DISABLE_SHIFT }, /* B8_G8_R8_A8 */
	{ 0x00008888 | M2MC_FT_Default,            0x00081018, 0x00000008 << M2MC_DISABLE_SHIFT }, /* B8_G8_R8_X8 */
	{ 0x00008000 | M2MC_FT_Alpha,              0x00000000, 0x00000007 << M2MC_DISABLE_SHIFT }, /* A8 */
	{ 0x00004000 | M2MC_FT_Alpha,              0x00000000, 0x00000007 << M2MC_DISABLE_SHIFT }, /* A4 */
	{ 0x00002000 | M2MC_FT_Alpha,              0x00000000, 0x00000007 << M2MC_DISABLE_SHIFT }, /* A2 */
	{ 0x00001000 | M2MC_FT_Alpha,              0x00000000, 0x00000007 << M2MC_DISABLE_SHIFT }, /* A1 */
	{ 0x00001000 | M2MC_FT_WRGB1565,           0x00000000, 0x00000007 << M2MC_DISABLE_SHIFT }, /* W1 */
	{ 0x00008008 | M2MC_FT_Palette,            0x08000000, 0x00000006 << M2MC_DISABLE_SHIFT }, /* A8_P8 */
	{ 0x00000008 | M2MC_FT_Palette,            0x00000000, 0x0000000E << M2MC_DISABLE_SHIFT }, /* P8 */
	{ 0x00000004 | M2MC_FT_Palette,            0x00000000, 0x0000000E << M2MC_DISABLE_SHIFT }, /* P4 */
	{ 0x00000002 | M2MC_FT_Palette,            0x00000000, 0x0000000E << M2MC_DISABLE_SHIFT }, /* P2 */
	{ 0x00000001 | M2MC_FT_Palette,            0x00000000, 0x0000000E << M2MC_DISABLE_SHIFT }, /* P1 */
	{ 0x00000808 | M2MC_FT_Palette,            0x00080000, 0x0000000A << M2MC_DISABLE_SHIFT }, /* Y8_P8 */
	{ 0x00008800 | M2MC_FT_YCbCr420,           0x08000000, 0x00000003 << M2MC_DISABLE_SHIFT }, /* A8_Y8 */
	{ 0x00000080 | M2MC_FT_Default,            0x00000000, 0x0000000D << M2MC_DISABLE_SHIFT }, /* Cb8 */
	{ 0x00000008 | M2MC_FT_Default,            0x00000000, 0x0000000E << M2MC_DISABLE_SHIFT }, /* Cr8 */
	{ 0x00000800 | M2MC_FT_YCbCr420,           0x00000000, 0x0000000B << M2MC_DISABLE_SHIFT }, /* Y8 */
	{ 0x00000088 | M2MC_FT_YCbCr420,           0x00000800, 0x0000000C << M2MC_DISABLE_SHIFT }, /* Cb8_Cr8 */
	{ 0x00000088 | M2MC_FT_YCbCr420,           0x00000008, 0x0000000C << M2MC_DISABLE_SHIFT }, /* Cr8_Cb8 */
	{ 0x00000A00 | M2MC_FT_YCbCr420_10,        0x00000000, 0x0000000B << M2MC_DISABLE_SHIFT }, /* Y10 */
	{ 0x000000AA | M2MC_FT_YCbCr420_10,        0x00000A00, 0x0000000C << M2MC_DISABLE_SHIFT }, /* Cb10_Cr10 */
	{ 0x000000AA | M2MC_FT_YCbCr420_10,        0x0000000A, 0x0000000C << M2MC_DISABLE_SHIFT }, /* Cr10_Cb10 */
	{ 0x00008888 | M2MC_FT_YCbCr422,           0x18081000, 0x00000000 << M2MC_DISABLE_SHIFT }, /* Y08_Cb8_Y18_Cr8 */
	{ 0x00008888 | M2MC_FT_YCbCr422,           0x18080010, 0x00000000 << M2MC_DISABLE_SHIFT }, /* Y08_Cr8_Y18_Cb8 */
	{ 0x00008888 | M2MC_FT_YCbCr422,           0x08181000, 0x00000000 << M2MC_DISABLE_SHIFT }, /* Y18_Cb8_Y08_Cr8 */
	{ 0x00008888 | M2MC_FT_YCbCr422,           0x08180010, 0x00000000 << M2MC_DISABLE_SHIFT }, /* Y18_Cr8_Y08_Cb8 */
	{ 0x00008888 | M2MC_FT_YCbCr422,           0x10001808, 0x00000000 << M2MC_DISABLE_SHIFT }, /* Cb8_Y08_Cr8_Y18 */
	{ 0x00008888 | M2MC_FT_YCbCr422,           0x00101808, 0x00000000 << M2MC_DISABLE_SHIFT }, /* Cb8_Y18_Cr8_Y08 */
	{ 0x00008888 | M2MC_FT_YCbCr422,           0x00100818, 0x00000000 << M2MC_DISABLE_SHIFT }, /* Cr8_Y18_Cb8_Y08 */
	{ 0x00008888 | M2MC_FT_YCbCr422,           0x10000818, 0x00000000 << M2MC_DISABLE_SHIFT }, /* Cr8_Y08_Cb8_Y18 */
	{ 0x00002AAA | M2MC_FT_YCbCr444_10,        0x1E0A0014, 0x00000008 << M2MC_DISABLE_SHIFT }, /* X2_Cr10_Y10_Cb10 */
	{ 0x00008888 | M2MC_FT_Default,            0x18100800, 0x00000000 << M2MC_DISABLE_SHIFT }, /* A8_Y8_Cb8_Cr8 */
	{ 0x00008888 | M2MC_FT_Default,            0x18000810, 0x00000000 << M2MC_DISABLE_SHIFT }, /* A8_Cr8_Cb8_Y8 */
	{ 0x00008888 | M2MC_FT_Default,            0x00081018, 0x00000000 << M2MC_DISABLE_SHIFT }, /* Cr8_Cb8_Y8_A8 */
	{ 0x00008888 | M2MC_FT_Default,            0x00181008, 0x00000000 << M2MC_DISABLE_SHIFT }, /* Y8_Cb8_Cr8_A8 */
	{ 0x0000AAAA | M2MC_FT_YCbCr422_10,        0x1E0A1400, 0x00000000 << M2MC_DISABLE_SHIFT }, /* Y010_Cb10_Y110_Cr10 */
	{ 0x0000AAAA | M2MC_FT_YCbCr422_10,        0x1E0A0014, 0x00000000 << M2MC_DISABLE_SHIFT }, /* Y010_Cr10_Y110_Cb10 */
	{ 0x0000AAAA | M2MC_FT_YCbCr422_10,        0x0A1E1400, 0x00000000 << M2MC_DISABLE_SHIFT }, /* Y110_Cb10_Y010_Cr10 */
	{ 0x0000AAAA | M2MC_FT_YCbCr422_10,        0x0A1E0014, 0x00000000 << M2MC_DISABLE_SHIFT }, /* Y110_Cr10_Y010_Cb10 */
	{ 0x0000AAAA | M2MC_FT_YCbCr422_10,        0x14001E0A, 0x00000000 << M2MC_DISABLE_SHIFT }, /* Cb10_Y010_Cr10_Y110 */
	{ 0x0000AAAA | M2MC_FT_YCbCr422_10,        0x00141E0A, 0x00000000 << M2MC_DISABLE_SHIFT }, /* Cb10_Y110_Cr10_Y010 */
	{ 0x0000AAAA | M2MC_FT_YCbCr422_10,        0x00140A1E, 0x00000000 << M2MC_DISABLE_SHIFT }, /* Cr10_Y110_Cb10_Y010 */
	{ 0x0000AAAA | M2MC_FT_YCbCr422_10,        0x14000A1E, 0x00000000 << M2MC_DISABLE_SHIFT }, /* Cr10_Y010_Cb10_Y110 */
	{ 0x00000008 | M2MC_FT_Default,            0x00000000, 0x00000000 << M2MC_DISABLE_SHIFT }, /* L8 */
	{ 0x00004004 | M2MC_FT_Default,            0x00000004, 0x00000000 << M2MC_DISABLE_SHIFT }, /* L4_A4 */
	{ 0x00008008 | M2MC_FT_Default,            0x00000008, 0x00000000 << M2MC_DISABLE_SHIFT }, /* L8_A8 */
	{ 0x00006055 | M2MC_FT_Default,            0x00000B06, 0x00000000 << M2MC_DISABLE_SHIFT }, /* L15_L05_A6 */

	{ 0x00008888 | M2MC_FT_CompressedARGB8888, 0x18100800, 0x00000000 << M2MC_DISABLE_SHIFT }, /* Compressed_A8_R8_G8_B8 */
	{ 0x00000000, 0x00000000, 0x00000000 }, /* Max */
};

/***************************************************************************/
static const uint32_t s_BGRC_PACKET_P_DeviceStripedPixelFormats[] =
{
	0x00000800 | M2MC_FT_YCbCr420_Striped,     /* Y8 */
	0x00000088 | M2MC_FT_YCbCr420_Striped,     /* Cb8_Cr8 */
	0x00000088 | M2MC_FT_YCbCr420_Striped,     /* Cr8_Cb8 */
	0x00000A00 | M2MC_FT_YCbCr420_10_Striped,  /* Y10 */
	0x000000AA | M2MC_FT_YCbCr420_10_Striped,  /* Cb10_Cr10 */
	0x000000AA | M2MC_FT_YCbCr420_10_Striped,  /* Cr10_Cb10 */
};

/***************************************************************************
 * note: since only blit sw pkt will generate hw pkt, all hw pkt header will
 * have BCHP_M2MC_LIST_PACKET_HEADER_1_BLIT_GRP_CNTRL_MASK bit on */
static const uint32_t s_BGRC_PACKET_P_DeviceGroupHeaderMasks[] =
{
	0,                                                              /* EndOfBuffer */
	BCHP_M2MC_LIST_PACKET_HEADER_1_SRC_FEEDER_GRP_CNTRL_MASK,       /* SourceFeeder */
	BCHP_M2MC_LIST_PACKET_HEADER_1_SRC_FEEDER_GRP_CNTRL_MASK,       /* SourceFeeders */
	BCHP_M2MC_LIST_PACKET_HEADER_1_SRC_FEEDER_GRP_CNTRL_MASK,       /* StripedSourceFeeders */
	BCHP_M2MC_LIST_PACKET_HEADER_1_SRC_FEEDER_GRP_CNTRL_MASK,       /* SourceColor */
	BCHP_M2MC_LIST_PACKET_HEADER_1_SRC_FEEDER_GRP_CNTRL_MASK,       /* SourceNone */
	BCHP_M2MC_LIST_PACKET_HEADER_1_SRC_FEEDER_GRP_CNTRL_MASK,       /* SourceControl */
	BCHP_M2MC_LIST_PACKET_HEADER_1_DST_FEEDER_GRP_CNTRL_MASK,       /* DestinationFeeder */
	BCHP_M2MC_LIST_PACKET_HEADER_1_DST_FEEDER_GRP_CNTRL_MASK,       /* DestinationColor */
	BCHP_M2MC_LIST_PACKET_HEADER_1_DST_FEEDER_GRP_CNTRL_MASK,       /* DestinationNone */
	BCHP_M2MC_LIST_PACKET_HEADER_1_DST_FEEDER_GRP_CNTRL_MASK,       /* DestinationControl */
	BCHP_M2MC_LIST_PACKET_HEADER_1_OUTPUT_FEEDER_GRP_CNTRL_MASK,    /* OutputFeeder */
	BCHP_M2MC_LIST_PACKET_HEADER_1_OUTPUT_FEEDER_GRP_CNTRL_MASK,    /* OutputControl */
	BCHP_M2MC_LIST_PACKET_HEADER_1_BLEND_PARAM_GRP_CNTRL_MASK,      /* Blend */
	BCHP_M2MC_LIST_PACKET_HEADER_1_BLEND_PARAM_GRP_CNTRL_MASK,      /* BlendColor */
	BCHP_M2MC_LIST_PACKET_HEADER_1_ROP_GRP_CNTRL_MASK,              /* Rop */
	BCHP_M2MC_LIST_PACKET_HEADER_1_SRC_COLOR_KEY_GRP_CNTRL_MASK,    /* SourceColorkey */
	BCHP_M2MC_LIST_PACKET_HEADER_1_BLEND_PARAM_GRP_CNTRL_MASK,      /* SourceColorkeyEnable */
	BCHP_M2MC_LIST_PACKET_HEADER_1_DST_COLOR_KEY_GRP_CNTRL_MASK,    /* DestinationColorkey */
	BCHP_M2MC_LIST_PACKET_HEADER_1_BLEND_PARAM_GRP_CNTRL_MASK,      /* DestinationColorkeyEnable */
	BCHP_M2MC_LIST_PACKET_HEADER_1_SCALE_COEF_GRP_CNTRL_MASK,       /* Filter */
	BCHP_M2MC_LIST_PACKET_HEADER_1_SCALE_PARAM_GRP_CNTRL_MASK,      /* FilterEnable */
	BCHP_M2MC_LIST_PACKET_HEADER_1_SCALE_PARAM_GRP_CNTRL_MASK,      /* FilterControl */
	BCHP_M2MC_LIST_PACKET_HEADER_1_SRC_COLOR_MATRIX_GRP_CNTRL_MASK, /* SourceColorMatrix */
	0,                                                              /* SourceColorMatrixEnable */
	BCHP_M2MC_LIST_PACKET_HEADER_1_SRC_CLUT_GRP_CNTRL_MASK,         /* SourcePalette */
	BCHP_M2MC_LIST_PACKET_HEADER_1_SCALE_PARAM_GRP_CNTRL_MASK,      /* AlphaPremultiply */
	0,                                                              /* AlphaDemultiply */
	0,                                                              /* DestAlphaPremultiply */
	0,                                                              /* Mirror */
	0,                                                              /* FixedScale */
	0,                                                              /* DestripeFixedScale */
	BCHP_M2MC_LIST_PACKET_HEADER_1_BLIT_GRP_CNTRL_MASK,             /* FillBlit */
	BCHP_M2MC_LIST_PACKET_HEADER_1_BLIT_GRP_CNTRL_MASK,             /* CopyBlit */
	BCHP_M2MC_LIST_PACKET_HEADER_1_BLIT_GRP_CNTRL_MASK,             /* BlendBlit */
	BCHP_M2MC_LIST_PACKET_HEADER_1_BLIT_GRP_CNTRL_MASK |            /* ScaleBlit */
	BCHP_M2MC_LIST_PACKET_HEADER_1_SCALE_PARAM_GRP_CNTRL_MASK,
	BCHP_M2MC_LIST_PACKET_HEADER_1_BLIT_GRP_CNTRL_MASK |            /* ScaleBlendBlit */
	BCHP_M2MC_LIST_PACKET_HEADER_1_SCALE_PARAM_GRP_CNTRL_MASK,
	BCHP_M2MC_LIST_PACKET_HEADER_1_BLIT_GRP_CNTRL_MASK |            /* UpdateScaleBlit */
	BCHP_M2MC_LIST_PACKET_HEADER_1_SCALE_PARAM_GRP_CNTRL_MASK,
	BCHP_M2MC_LIST_PACKET_HEADER_1_BLIT_GRP_CNTRL_MASK |            /* DestripeBlit */
	BCHP_M2MC_LIST_PACKET_HEADER_1_SCALE_PARAM_GRP_CNTRL_MASK,
	BGRC_PACKET_P_DEVICE_GROUP_MASK_FULL,                           /* Reset */
	0,                                                              /* Save */
	0                                                               /* Restore */
};

/***************************************************************************/
static const uint32_t s_BGRC_PACKET_P_DeviceGroupSizes[] =
{
	0,
	sizeof (uint32_t),
	0,
	0,
	BGRC_M2MC(SRC_CM_C34) - BGRC_M2MC(SRC_CM_C00_C01) + sizeof (uint32_t),
	BGRC_M2MC(SRC_CM_C00_C01) - BGRC_M2MC(HORIZ_FIR_0_COEFF_PHASE0_01),
	BGRC_M2MC(HORIZ_FIR_0_COEFF_PHASE0_01) - BGRC_M2MC(DEST_COLOR_KEY_HIGH),
	BGRC_M2MC(DEST_COLOR_KEY_HIGH) - BGRC_M2MC(SRC_COLOR_KEY_HIGH),
	BGRC_M2MC(SRC_COLOR_KEY_HIGH) - BGRC_M2MC(ROP_OPERATION),
	BGRC_M2MC(ROP_OPERATION) - BGRC_M2MC(BLEND_COLOR_OP),
	BGRC_M2MC(BLEND_COLOR_OP) - BGRC_M2MC(SCALER_CTRL),
#if ((BGRC_M2MC(SCALER_CTRL) - BGRC_M2MC(BLIT_CTRL)) == 8) && !defined(BCHP_M2MC_DCEG_CFG)
	BGRC_M2MC(SCALER_CTRL) - 4 - BGRC_M2MC(BLIT_HEADER),
#else
	BGRC_M2MC(SCALER_CTRL) - BGRC_M2MC(BLIT_HEADER),
#endif
	BGRC_M2MC(BLIT_HEADER) - BGRC_M2MC(OUTPUT_FEEDER_ENABLE),
	BGRC_M2MC(OUTPUT_FEEDER_ENABLE) - BGRC_M2MC(DEST_FEEDER_ENABLE),
	BGRC_M2MC(DEST_FEEDER_ENABLE) - BGRC_M2MC(SRC_FEEDER_ENABLE)
};

/***************************************************************************/
static const uint32_t s_BGRC_PACKET_P_DeviceRegisterOffsets[] =
{
	0,
	BGRC_M2MC(SRC_CLUT_ENTRY_i_ARRAY_BASE) - BGRC_M2MC(SRC_FEEDER_ENABLE),
	0,
	0,
	BGRC_M2MC(SRC_CM_C00_C01) - BGRC_M2MC(SRC_FEEDER_ENABLE),
	BGRC_M2MC(HORIZ_FIR_0_COEFF_PHASE0_01) - BGRC_M2MC(SRC_FEEDER_ENABLE),
	BGRC_M2MC(DEST_COLOR_KEY_HIGH) - BGRC_M2MC(SRC_FEEDER_ENABLE),
	BGRC_M2MC(SRC_COLOR_KEY_HIGH) - BGRC_M2MC(SRC_FEEDER_ENABLE),
	BGRC_M2MC(ROP_OPERATION) - BGRC_M2MC(SRC_FEEDER_ENABLE),
	BGRC_M2MC(BLEND_COLOR_OP) - BGRC_M2MC(SRC_FEEDER_ENABLE),
	BGRC_M2MC(SCALER_CTRL) - BGRC_M2MC(SRC_FEEDER_ENABLE),
	BGRC_M2MC(BLIT_HEADER) - BGRC_M2MC(SRC_FEEDER_ENABLE),
	BGRC_M2MC(OUTPUT_FEEDER_ENABLE) - BGRC_M2MC(SRC_FEEDER_ENABLE),
	BGRC_M2MC(DEST_FEEDER_ENABLE) - BGRC_M2MC(SRC_FEEDER_ENABLE),
	BGRC_M2MC(SRC_FEEDER_ENABLE) - BGRC_M2MC(SRC_FEEDER_ENABLE)
};

#if defined(BGRC_PACKET_P_DEBUG_DESC) || defined(BGRC_PACKET_P_DEBUG_SW_PKT)
/***************************************************************************/
static const char *s_BGRC_PACKET_P_DESCR_GRP_NAME[] =
{
	"             DST_CLUT",
	"             SRC_CLUT_ENTRY_i_ARRAY_BASE",
	"             OUTPUT_COLOR_MATRIX",
	"             DST_COLOR_MATRIX",
	"             SRC_CM_C00_C01",
	"             HORIZ_FIR_0_COEFF_PHASE0_01",
	"             DEST_COLOR_KEY_HIGH",
	"             SRC_COLOR_KEY_HIGH",
	"             ROP_OPERATION",
	"             BLEND_COLOR_OP",
	"             SCALER_CTRL",
	"             BLIT_HEADER",
	"             OUTPUT_FEEDER_ENABLE",
	"             DEST_FEEDER_ENABLE",
	"             SRC_FEEDER_ENABLE"
};
#endif

/***************************************************************************/
static const BM2MC_PACKET_FilterCoeffs s_BGRC_PACKET_P_DeviceFilter_PointSample =
{
#if defined(BCHP_M2MC_HORIZ_FIR_COEFF_PHASE0_2_COEFF_2_SHIFT)
	{ { 0x0000, 0x0000, 0x0100 }, { 0x0000, 0x0000, 0x0100 } }
#else
{
	{ 0x0000, 0x0000, 0x0000, 0x0000, 0x1000, 0x0000, 0x000, 0x00000 },
	{ 0x0000, 0x0000, 0x0000, 0x0000, 0x1000, 0x0000, 0x000, 0x00000 },
	{ 0x0000, 0x0000, 0x0000, 0x0000, 0x1000, 0x0000, 0x000, 0x00000 },
	{ 0x0000, 0x0000, 0x0000, 0x0000, 0x1000, 0x0000, 0x000, 0x00000 },
	{ 0x0000, 0x0000, 0x0000, 0x0000, 0x1000, 0x0000, 0x000, 0x00000 },
	{ 0x0000, 0x0000, 0x0000, 0x0000, 0x1000, 0x0000, 0x000, 0x00000 },
	{ 0x0000, 0x0000, 0x0000, 0x0000, 0x1000, 0x0000, 0x000, 0x00000 },
	{ 0x0000, 0x0000, 0x0000, 0x0000, 0x1000, 0x0000, 0x000, 0x00000 }
}
#endif
};

static const BM2MC_PACKET_FilterCoeffs s_BGRC_PACKET_P_DeviceFilter_Bilinear =
{
#if defined(BCHP_M2MC_HORIZ_FIR_COEFF_PHASE0_2_COEFF_2_SHIFT)
	{ { 0x0000, 0x0000, 0x0100 }, { 0x0000, 0x0000, 0x0080 } }
#else
{
	{ 0x0000, 0x0000, 0x0000, 0x0000, 0x1000, 0x0000, 0x0000, 0x0000 },
	{ 0x0000, 0x0000, 0x0000, 0x0200, 0x0E00, 0x0000, 0x0000, 0x0000 },
	{ 0x0000, 0x0000, 0x0000, 0x0400, 0x0C00, 0x0000, 0x0000, 0x0000 },
	{ 0x0000, 0x0000, 0x0000, 0x0600, 0x0A00, 0x0000, 0x0000, 0x0000 },
	{ 0x0000, 0x0000, 0x0000, 0x0800, 0x0800, 0x0000, 0x0000, 0x0000 },
	{ 0x0000, 0x0000, 0x0000, 0x0A00, 0x0600, 0x0000, 0x0000, 0x0000 },
	{ 0x0000, 0x0000, 0x0000, 0x0C00, 0x0400, 0x0000, 0x0000, 0x0000 },
	{ 0x0000, 0x0000, 0x0000, 0x0E00, 0x0200, 0x0000, 0x0000, 0x0000 }
}
#endif
};

static const BM2MC_PACKET_FilterCoeffs s_BGRC_PACKET_P_DeviceFilter_Anisotropic[] =
{
#if defined(BCHP_M2MC_HORIZ_FIR_COEFF_PHASE0_2_COEFF_2_SHIFT)
	{ { { 0x0000, 0x0000, 0x0100 }, { 0x0000, 0x0000, 0x0080 } } },     /* 1 to 1 */
	{ { { 0x0000, 0x0000, 0x0100 }, { 0x0000, 0x0000, 0x0080 } } },     /* 2 to 1 */
	{ { { 0x0000, 0x0055, 0x0056 }, { 0x0000, 0x002b, 0x0055 } } },     /* 3 to 1 */
	{ { { 0x0000, 0x0055, 0x0056 }, { 0x0000, 0x002b, 0x0055 } } },     /* 4 to 1 */
	{ { { 0x0033, 0x0033, 0x0034 }, { 0x001a, 0x0033, 0x0033 } } },     /* 5 to 1 */
	{ { { 0x0033, 0x0033, 0x0034 }, { 0x002a, 0x002b, 0x002b } } },     /* 6 to 1 */
	{ { { 0x0033, 0x0033, 0x0034 }, { 0x002a, 0x002b, 0x002b } } },     /* 7 to 1 */
	{ { { 0x0033, 0x0033, 0x0034 }, { 0x002a, 0x002b, 0x002b } } }      /* 8 to 1 */
#else
{ {
	{ 0x0000, 0x0000, 0x0000, 0x0000, 0x1000, 0x0000, 0x0000, 0x0000 }, /* 1 to 1 */
	{ 0x0000, 0x0000, 0x0000, 0x0200, 0x0E00, 0x0000, 0x0000, 0x0000 },
	{ 0x0000, 0x0000, 0x0000, 0x0400, 0x0C00, 0x0000, 0x0000, 0x0000 },
	{ 0x0000, 0x0000, 0x0000, 0x0600, 0x0A00, 0x0000, 0x0000, 0x0000 },
	{ 0x0000, 0x0000, 0x0000, 0x0800, 0x0800, 0x0000, 0x0000, 0x0000 },
	{ 0x0000, 0x0000, 0x0000, 0x0A00, 0x0600, 0x0000, 0x0000, 0x0000 },
	{ 0x0000, 0x0000, 0x0000, 0x0C00, 0x0400, 0x0000, 0x0000, 0x0000 },
	{ 0x0000, 0x0000, 0x0000, 0x0E00, 0x0200, 0x0000, 0x0000, 0x0000 }
} },{ {
	{ 0x0000, 0x0000, 0x0000, 0x0000, 0x0800, 0x0800, 0x0000, 0x0000 }, /* 2 to 1 */
	{ 0x0000, 0x0000, 0x0000, 0x0100, 0x0800, 0x0700, 0x0000, 0x0000 },
	{ 0x0000, 0x0000, 0x0000, 0x0200, 0x0800, 0x0600, 0x0000, 0x0000 },
	{ 0x0000, 0x0000, 0x0000, 0x0300, 0x0800, 0x0500, 0x0000, 0x0000 },
	{ 0x0000, 0x0000, 0x0000, 0x0400, 0x0800, 0x0400, 0x0000, 0x0000 },
	{ 0x0000, 0x0000, 0x0000, 0x0500, 0x0800, 0x0300, 0x0000, 0x0000 },
	{ 0x0000, 0x0000, 0x0000, 0x0600, 0x0800, 0x0200, 0x0000, 0x0000 },
	{ 0x0000, 0x0000, 0x0000, 0x0700, 0x0800, 0x0100, 0x0000, 0x0000 }
} },{ {
	{ 0x0000, 0x0000, 0x0000, 0x0554, 0x0558, 0x0554, 0x0000, 0x0000 }, /* 3 to 1 */
	{ 0x0000, 0x0000, 0x00AC, 0x0554, 0x0554, 0x04AC, 0x0000, 0x0000 },
	{ 0x0000, 0x0000, 0x0154, 0x0554, 0x0558, 0x0400, 0x0000, 0x0000 },
	{ 0x0000, 0x0000, 0x0200, 0x0554, 0x0558, 0x0354, 0x0000, 0x0000 },
	{ 0x0000, 0x0000, 0x02AC, 0x0554, 0x0554, 0x02AC, 0x0000, 0x0000 },
	{ 0x0000, 0x0000, 0x0354, 0x0554, 0x0558, 0x0200, 0x0000, 0x0000 },
	{ 0x0000, 0x0000, 0x0400, 0x0554, 0x0558, 0x0154, 0x0000, 0x0000 },
	{ 0x0000, 0x0000, 0x04AC, 0x0554, 0x0554, 0x00AC, 0x0000, 0x0000 }
} },{ {
	{ 0x0000, 0x0000, 0x0000, 0x0400, 0x0400, 0x0400, 0x0400, 0x0000 }, /* 4 to 1 */
	{ 0x0000, 0x0000, 0x0080, 0x0400, 0x0400, 0x0400, 0x0380, 0x0000 },
	{ 0x0000, 0x0000, 0x0100, 0x0400, 0x0400, 0x0400, 0x0300, 0x0000 },
	{ 0x0000, 0x0000, 0x0180, 0x0400, 0x0400, 0x0400, 0x0280, 0x0000 },
	{ 0x0000, 0x0000, 0x0200, 0x0400, 0x0400, 0x0400, 0x0200, 0x0000 },
	{ 0x0000, 0x0000, 0x0280, 0x0400, 0x0400, 0x0400, 0x0180, 0x0000 },
	{ 0x0000, 0x0000, 0x0300, 0x0400, 0x0400, 0x0400, 0x0100, 0x0000 },
	{ 0x0000, 0x0000, 0x0380, 0x0400, 0x0400, 0x0400, 0x0080, 0x0000 }
} },{ {
	{ 0x0000, 0x0000, 0x0334, 0x0334, 0x0334, 0x0334, 0x0330, 0x0000 }, /* 5 to 1 */
	{ 0x0000, 0x0068, 0x0334, 0x0334, 0x0334, 0x0334, 0x02C8, 0x0000 },
	{ 0x0000, 0x00CC, 0x0334, 0x0334, 0x0334, 0x0334, 0x0264, 0x0000 },
	{ 0x0000, 0x0134, 0x0334, 0x0334, 0x0334, 0x0334, 0x01FC, 0x0000 },
	{ 0x0000, 0x0198, 0x0334, 0x0334, 0x0334, 0x0334, 0x0198, 0x0000 },
	{ 0x0000, 0x0200, 0x0334, 0x0334, 0x0334, 0x0334, 0x0134, 0x0000 },
	{ 0x0000, 0x0264, 0x0334, 0x0334, 0x0334, 0x0334, 0x00CC, 0x0000 },
	{ 0x0000, 0x02C8, 0x0334, 0x0334, 0x0334, 0x0334, 0x0068, 0x0000 }
} },{ {
	{ 0x0000, 0x0000, 0x02A8, 0x02AC, 0x02AC, 0x02AC, 0x02AC, 0x02A8 }, /* 6 to 1 */
	{ 0x0000, 0x0054, 0x02AC, 0x02AC, 0x02AC, 0x02AC, 0x02AC, 0x0250 },
	{ 0x0000, 0x00A8, 0x02AC, 0x02AC, 0x02AC, 0x02AC, 0x02AC, 0x01FC },
	{ 0x0000, 0x00FC, 0x02AC, 0x02AC, 0x02AC, 0x02AC, 0x02AC, 0x01A8 },
	{ 0x0000, 0x0154, 0x02AC, 0x02AC, 0x02AC, 0x02AC, 0x02AC, 0x0150 },
	{ 0x0000, 0x01A8, 0x02AC, 0x02AC, 0x02AC, 0x02AC, 0x02AC, 0x00FC },
	{ 0x0000, 0x01FC, 0x02AC, 0x02AC, 0x02AC, 0x02AC, 0x02AC, 0x00A8 },
	{ 0x0000, 0x0250, 0x02AC, 0x02AC, 0x02AC, 0x02AC, 0x02AC, 0x0054 }
} },{ {
	{ 0x0000, 0x0248, 0x0248, 0x024C, 0x024C, 0x0248, 0x0248, 0x0248 }, /* 7 to 1 */
	{ 0x0048, 0x0248, 0x0248, 0x024C, 0x024C, 0x0248, 0x0248, 0x0200 },
	{ 0x0094, 0x0248, 0x0248, 0x0248, 0x024C, 0x0248, 0x0248, 0x01B8 },
	{ 0x00DC, 0x0248, 0x0248, 0x024C, 0x024C, 0x0248, 0x0248, 0x016C },
	{ 0x0124, 0x0248, 0x0248, 0x024C, 0x024C, 0x0248, 0x0248, 0x0124 },
	{ 0x016C, 0x0248, 0x0248, 0x024C, 0x024C, 0x0248, 0x0248, 0x00DC },
	{ 0x01B8, 0x0248, 0x0248, 0x0248, 0x024C, 0x0248, 0x0248, 0x0094 },
	{ 0x0200, 0x0248, 0x0248, 0x024C, 0x024C, 0x0248, 0x0248, 0x0048 }
} },{ {
	{ 0x0200, 0x0200, 0x0200, 0x0200, 0x0200, 0x0200, 0x0200, 0x0200 }, /* 8 to 1 */
	{ 0x0200, 0x0200, 0x0200, 0x0200, 0x0200, 0x0200, 0x0200, 0x0200 },
	{ 0x0200, 0x0200, 0x0200, 0x0200, 0x0200, 0x0200, 0x0200, 0x0200 },
	{ 0x0200, 0x0200, 0x0200, 0x0200, 0x0200, 0x0200, 0x0200, 0x0200 },
	{ 0x0200, 0x0200, 0x0200, 0x0200, 0x0200, 0x0200, 0x0200, 0x0200 },
	{ 0x0200, 0x0200, 0x0200, 0x0200, 0x0200, 0x0200, 0x0200, 0x0200 },
	{ 0x0200, 0x0200, 0x0200, 0x0200, 0x0200, 0x0200, 0x0200, 0x0200 },
	{ 0x0200, 0x0200, 0x0200, 0x0200, 0x0200, 0x0200, 0x0200, 0x0200 }
} }
#endif
};

static const BM2MC_PACKET_FilterCoeffs s_BGRC_PACKET_P_DeviceFilter_Sharp[] =
{
#if defined(BCHP_M2MC_HORIZ_FIR_COEFF_PHASE0_2_COEFF_2_SHIFT)
	{ { { 0x000f, 0x0041, 0x0060 }, { 0x0006, 0x0024, 0x0056 } } },     /* 8 to 1 */
	{ { { 0x000b, 0x0040, 0x006a }, { 0x0004, 0x0020, 0x005c } } },     /* 8 to 2 */
	{ { { 0x0006, 0x003f, 0x0076 }, { 0x0000, 0x001a, 0x0066 } } },     /* 8 to 3 */
	{ { { 0x0000, 0x003b, 0x008a }, {-0x0002, 0x0010, 0x0072 } } },     /* 8 to 4 */
	{ { {-0x0005, 0x0033, 0x00a4 }, {-0x0003, 0x0003, 0x0080 } } },     /* 8 to 5 */
	{ { {-0x0007, 0x0026, 0x00c2 }, {-0x0001,-0x0009, 0x008a } } },     /* 8 to 6 */
	{ { {-0x0004, 0x0014, 0x00e0 }, { 0x0002,-0x0012, 0x0090 } } },     /* 8 to 7 */
	{ { {-0x0001, 0x0000, 0x0100 }, { 0x0002,-0x0015, 0x0093 } } },     /* 8 to 8 */
	{ { { 0x0000,-0x0001, 0x0102 }, { 0x0002,-0x0015, 0x0093 } } },     /* 8 to 9 */
	{ { {-0x0006, 0x001f, 0x00ce }, { 0x0000,-0x000d, 0x008d } } }      /* 1 to N */
#else
{ {
	{ 0x0000, 0x009C, 0x01E8, 0x036C, 0x041C, 0x036C, 0x01E8, 0x009C }, /* 8 to 1 */
	{ 0x0038, 0x00B8, 0x0214, 0x0388, 0x0408, 0x0338, 0x01B0, 0x0080 },
	{ 0x0038, 0x00DC, 0x0248, 0x03A8, 0x0400, 0x030C, 0x0180, 0x006C },
	{ 0x0040, 0x0100, 0x027C, 0x03C8, 0x03F4, 0x02DC, 0x0154, 0x0058 },
	{ 0x004C, 0x0128, 0x02AC, 0x03E0, 0x03E0, 0x02AC, 0x0128, 0x004C },
	{ 0x0058, 0x0154, 0x02DC, 0x03F4, 0x03C8, 0x027C, 0x0100, 0x0040 },
	{ 0x006C, 0x0180, 0x030C, 0x0400, 0x03A8, 0x0248, 0x00DC, 0x0038 },
	{ 0x0080, 0x01B0, 0x0338, 0x0408, 0x0388, 0x0214, 0x00B8, 0x0038 }
} },{ {
	{ 0x0000, 0x0048, 0x0198, 0x03B8, 0x04D4, 0x03B8, 0x0198, 0x0048 }, /* 8 to 2 */
	{ 0x0004, 0x0060, 0x01D4, 0x03F4, 0x04CC, 0x0378, 0x015C, 0x0034 },
	{ 0x0008, 0x007C, 0x0218, 0x042C, 0x04C0, 0x0334, 0x0124, 0x0024 },
	{ 0x000C, 0x009C, 0x0260, 0x045C, 0x04A8, 0x02EC, 0x00F0, 0x0018 },
	{ 0x0010, 0x00C4, 0x02A4, 0x0488, 0x0488, 0x02A4, 0x00C4, 0x0010 },
	{ 0x0018, 0x00F0, 0x02EC, 0x04A8, 0x045C, 0x0260, 0x009C, 0x000C },
	{ 0x0024, 0x0124, 0x0334, 0x04C0, 0x042C, 0x0218, 0x007C, 0x0008 },
	{ 0x0034, 0x015C, 0x0378, 0x04CC, 0x03F4, 0x01D4, 0x0060, 0x0004 }
} },{ {
	{ 0x0000, 0x3FE4, 0x00F0, 0x041C, 0x0620, 0x041C, 0x00F0, 0x3FE4 }, /* 8 to 3 */
	{ 0x3FE8, 0x3FE8, 0x0140, 0x048C, 0x0620, 0x03B4, 0x00B0, 0x3FE0 },
	{ 0x3FE8, 0x3FF8, 0x0198, 0x04F0, 0x0604, 0x0340, 0x0074, 0x3FE0 },
	{ 0x3FE4, 0x0004, 0x01FC, 0x054C, 0x05D4, 0x02D0, 0x0048, 0x3FE0 },
	{ 0x3FE4, 0x0020, 0x0264, 0x0598, 0x0598, 0x0264, 0x0020, 0x3FE4 },
	{ 0x3FE0, 0x0048, 0x02D0, 0x05D4, 0x054C, 0x01FC, 0x0004, 0x3FE4 },
	{ 0x3FE0, 0x0074, 0x0340, 0x0604, 0x04F0, 0x0198, 0x3FF8, 0x3FE8 },
	{ 0x3FE0, 0x00B0, 0x03B4, 0x0620, 0x048C, 0x0140, 0x3FE8, 0x3FE8 }
} },{ {
	{ 0x0000, 0x3FB0, 0x0000, 0x0454, 0x07F4, 0x0454, 0x0000, 0x3FB0 }, /* 8 to 4 */
	{ 0x3FFC, 0x3FA0, 0x004C, 0x050C, 0x07E4, 0x03A0, 0x3FC8, 0x3FC0 },
	{ 0x3FF8, 0x3F90, 0x00AC, 0x05BC, 0x07B0, 0x02F0, 0x3FA4, 0x3FD0 },
	{ 0x3FF0, 0x3F88, 0x0120, 0x065C, 0x075C, 0x0244, 0x3F90, 0x3FDC },
	{ 0x3FE8, 0x3F84, 0x01AC, 0x06E8, 0x06E8, 0x01AC, 0x3F84, 0x3FE8 },
	{ 0x3FDC, 0x3F90, 0x0244, 0x075C, 0x065C, 0x0120, 0x3F88, 0x3FF0 },
	{ 0x3FD0, 0x3FA4, 0x02F0, 0x07B0, 0x05BC, 0x00AC, 0x3F90, 0x3FF8 },
	{ 0x3FC0, 0x3FC8, 0x03A0, 0x07E4, 0x050C, 0x004C, 0x3FA0, 0x3FFC }
} },{ {
	{ 0x0000, 0x3FE4, 0x3F14, 0x0408, 0x0A04, 0x0408, 0x3F14, 0x3FE4 }, /* 8 to 5 */
	{ 0x0018, 0x3FC8, 0x3F38, 0x0518, 0x09D4, 0x02F8, 0x3F0C, 0x3FF8 },
	{ 0x0018, 0x3FA4, 0x3F80, 0x062C, 0x0978, 0x0204, 0x3F18, 0x0004 },
	{ 0x0018, 0x3F7C, 0x3FE8, 0x0734, 0x08E4, 0x012C, 0x3F34, 0x000C },
	{ 0x0014, 0x3F58, 0x0074, 0x0820, 0x0820, 0x0074, 0x3F58, 0x0014 },
	{ 0x000C, 0x3F34, 0x012C, 0x08E4, 0x0734, 0x3FE8, 0x3F7C, 0x0018 },
	{ 0x0004, 0x3F18, 0x0204, 0x0978, 0x062C, 0x3F80, 0x3FA4, 0x0018 },
	{ 0x3FF8, 0x3F0C, 0x02F8, 0x09D4, 0x0518, 0x3F38, 0x3FC8, 0x0018 }
} },{ {
	{ 0x0000, 0x0038, 0x3EB4, 0x0314, 0x0C00, 0x0314, 0x3EB4, 0x0038 }, /* 8 to 6 */
	{ 0x0008, 0x002C, 0x3E8C, 0x048C, 0x0BC8, 0x01C0, 0x3EF0, 0x0038 },
	{ 0x0010, 0x0018, 0x3E88, 0x0618, 0x0B2C, 0x009C, 0x3F38, 0x0034 },
	{ 0x0018, 0x3FF4, 0x3EB4, 0x079C, 0x0A3C, 0x3FBC, 0x3F80, 0x002C },
	{ 0x0020, 0x3FC0, 0x3F18, 0x0908, 0x0908, 0x3F18, 0x3FC0, 0x0020 },
	{ 0x002C, 0x3F80, 0x3FBC, 0x0A3C, 0x079C, 0x3EB4, 0x3FF4, 0x0018 },
	{ 0x0034, 0x3F38, 0x009C, 0x0B2C, 0x0618, 0x3E88, 0x0018, 0x0010 },
	{ 0x0038, 0x3EF0, 0x01C0, 0x0BC8, 0x048C, 0x3E8C, 0x002C, 0x0008 }
} },{ {
	{ 0x0000, 0x004C, 0x3F14, 0x01A8, 0x0DEC, 0x01A8, 0x3F14, 0x004C }, /* 8 to 7 */
	{ 0x3FE8, 0x0064, 0x3EA0, 0x0378, 0x0DB4, 0x002C, 0x3F88, 0x0030 },
	{ 0x3FEC, 0x0074, 0x3E3C, 0x0580, 0x0CD0, 0x3F14, 0x3FE8, 0x0018 },
	{ 0x3FF0, 0x0074, 0x3E04, 0x0798, 0x0B68, 0x3E60, 0x0030, 0x0004 },
	{ 0x3FFC, 0x0060, 0x3E08, 0x099C, 0x099C, 0x3E08, 0x0060, 0x3FFC },
	{ 0x0004, 0x0030, 0x3E60, 0x0B68, 0x0798, 0x3E04, 0x0074, 0x3FF0 },
	{ 0x0018, 0x3FE8, 0x3F14, 0x0CD0, 0x0580, 0x3E3C, 0x0074, 0x3FEC },
	{ 0x0030, 0x3F88, 0x002C, 0x0DB4, 0x0378, 0x3EA0, 0x0064, 0x3FE8 }
} },{ {
	{ 0x0000, 0x0000, 0x0000, 0x0000, 0x1000, 0x0000, 0x0000, 0x0000 }, /* 8 to 8 */
	{ 0x3FF8, 0x0024, 0x3F6C, 0x01F8, 0x0F94, 0x3E94, 0x006C, 0x3FE8 },
	{ 0x3FEC, 0x0054, 0x3EC0, 0x0468, 0x0E50, 0x3DC0, 0x00AC, 0x3FDC },
	{ 0x3FE4, 0x0088, 0x3E1C, 0x071C, 0x0C50, 0x3D74, 0x00C0, 0x3FD8 },
	{ 0x3FDC, 0x00B0, 0x3DA0, 0x09D4, 0x09D4, 0x3DA0, 0x00B0, 0x3FDC },
	{ 0x3FD8, 0x00C0, 0x3D74, 0x0C50, 0x071C, 0x3E1C, 0x0088, 0x3FE4 },
	{ 0x3FDC, 0x00AC, 0x3DC0, 0x0E50, 0x0468, 0x3EC0, 0x0054, 0x3FEC },
	{ 0x3FE8, 0x006C, 0x3E94, 0x0F94, 0x01F8, 0x3F6C, 0x0024, 0x3FF8 }
} },{ {
	{ 0x0000, 0x3FB4, 0x00EC, 0x3E54, 0x1214, 0x3E54, 0x00EC, 0x3FB4 }, /* 8 to 9 */
	{ 0x0018, 0x3FC0, 0x0084, 0x0040, 0x1158, 0x3D40, 0x010C, 0x3FC0 },
	{ 0x0010, 0x3FE0, 0x3FD4, 0x02EC, 0x0F98, 0x3CF4, 0x00F4, 0x3FD0 },
	{ 0x0008, 0x0014, 0x3EF4, 0x0628, 0x0CE4, 0x3D48, 0x00B0, 0x3FE8 },
	{ 0x3FFC, 0x0060, 0x3E08, 0x099C, 0x099C, 0x3E08, 0x0060, 0x3FFC },
	{ 0x3FE8, 0x00B0, 0x3D48, 0x0CE4, 0x0628, 0x3EF4, 0x0014, 0x0008 },
	{ 0x3FD0, 0x00F4, 0x3CF4, 0x0F98, 0x02EC, 0x3FD4, 0x3FE0, 0x0010 },
	{ 0x3FC0, 0x010C, 0x3D40, 0x1158, 0x0040, 0x0084, 0x3FC0, 0x0018 }
} },{ {
	{ 0x0000, 0x0030, 0x3EE0, 0x0320, 0x0CE0, 0x01A0, 0x3F20, 0x0030 }, /* 1 to N */
	{ 0x0000, 0x0030, 0x3EA0, 0x04D0, 0x0C60, 0x0070, 0x3F70, 0x0020 },
	{ 0x0000, 0x0030, 0x3E80, 0x06A0, 0x0B60, 0x3F80, 0x3FB0, 0x0020 },
	{ 0x0010, 0x0010, 0x3E90, 0x0860, 0x0A10, 0x3EE0, 0x3FF0, 0x0010 },
	{ 0x0010, 0x3FF0, 0x3EE0, 0x0A10, 0x0860, 0x3E90, 0x0010, 0x0010 },
	{ 0x0020, 0x3FB0, 0x3F80, 0x0B60, 0x06A0, 0x3E80, 0x0030, 0x0000 },
	{ 0x0020, 0x3F70, 0x0070, 0x0C60, 0x04D0, 0x3EA0, 0x0030, 0x0000 },
	{ 0x0030, 0x3F20, 0x01A0, 0x0CE0, 0x0320, 0x3EE0, 0x0030, 0x0000 }
} }
#endif
};

static const BM2MC_PACKET_FilterCoeffs s_BGRC_PACKET_P_DeviceFilter_Sharper =
{
#if defined(BCHP_M2MC_HORIZ_FIR_COEFF_PHASE0_2_COEFF_2_SHIFT)
	{ { 0x0000, 0x0000, 0x0100 }, { 0x0003,-0x0015, 0x0092 } }
#else
{
	{ 0x0000, 0x0000, 0x0000, 0x0000, 0x1000, 0x0000, 0x0000, 0x0000 },
	{ 0x3FD0, 0x0060, 0x3F30, 0x0220, 0x0FC0, 0x3E60, 0x00B0, 0x3FB0 },
	{ 0x3FA0, 0x00D0, 0x3E50, 0x04B0, 0x0EA0, 0x3D50, 0x0130, 0x3F70 },
	{ 0x3F70, 0x0130, 0x3D80, 0x0780, 0x0CC0, 0x3CE0, 0x0170, 0x3F50 },
	{ 0x3F60, 0x0170, 0x3CF0, 0x0A40, 0x0A40, 0x3CF0, 0x0170, 0x3F60 },
	{ 0x3F50, 0x0170, 0x3CE0, 0x0CC0, 0x0780, 0x3D80, 0x0130, 0x3F70 },
	{ 0x3F70, 0x0130, 0x3D50, 0x0EA0, 0x04B0, 0x3E50, 0x00D0, 0x3FA0 },
	{ 0x3FB0, 0x00B0, 0x3E60, 0x0FC0, 0x0220, 0x3F30, 0x0060, 0x3FD0 }
}
#endif
};

static const BM2MC_PACKET_FilterCoeffs s_BGRC_PACKET_P_DeviceFilter_Blurry =
{
#if defined(BCHP_M2MC_HORIZ_FIR_COEFF_PHASE0_2_COEFF_2_SHIFT)
	{ { 0x0000, 0x0055, 0x0056 }, { 0x0000, 0x002b, 0x0055 } }
#else
{
	{ 0x0000, 0x0000, 0x0000, 0x0554, 0x0558, 0x0554, 0x0000, 0x0000 },
	{ 0x0000, 0x0000, 0x00AC, 0x0554, 0x0554, 0x04AC, 0x0000, 0x0000 },
	{ 0x0000, 0x0000, 0x0154, 0x0554, 0x0558, 0x0400, 0x0000, 0x0000 },
	{ 0x0000, 0x0000, 0x0200, 0x0554, 0x0558, 0x0354, 0x0000, 0x0000 },
	{ 0x0000, 0x0000, 0x02AC, 0x0554, 0x0554, 0x02AC, 0x0000, 0x0000 },
	{ 0x0000, 0x0000, 0x0354, 0x0554, 0x0558, 0x0200, 0x0000, 0x0000 },
	{ 0x0000, 0x0000, 0x0400, 0x0554, 0x0558, 0x0154, 0x0000, 0x0000 },
	{ 0x0000, 0x0000, 0x04AC, 0x0554, 0x0554, 0x00AC, 0x0000, 0x0000 }
}
#endif
};

static const BM2MC_PACKET_FilterCoeffs s_BGRC_PACKET_P_DeviceFilter_AntiFlutter =
{
#if defined(BCHP_M2MC_HORIZ_FIR_COEFF_PHASE0_2_COEFF_2_SHIFT)
	{ { 0x0000, 0x0040, 0x0080 }, { 0x0000, 0x0000, 0x0080 } }
#else
{
	{ 0x0000, 0x0000, 0x0000, 0x0400, 0x0800, 0x0400, 0x0000, 0x0000 },
	{ 0x0000, 0x0000, 0x0000, 0x0400, 0x0800, 0x0400, 0x0000, 0x0000 },
	{ 0x0000, 0x0000, 0x0000, 0x0400, 0x0800, 0x0400, 0x0000, 0x0000 },
	{ 0x0000, 0x0000, 0x0000, 0x0400, 0x0800, 0x0400, 0x0000, 0x0000 },
	{ 0x0000, 0x0000, 0x0000, 0x0400, 0x0800, 0x0400, 0x0000, 0x0000 },
	{ 0x0000, 0x0000, 0x0000, 0x0400, 0x0800, 0x0400, 0x0000, 0x0000 },
	{ 0x0000, 0x0000, 0x0000, 0x0400, 0x0800, 0x0400, 0x0000, 0x0000 },
	{ 0x0000, 0x0000, 0x0000, 0x0400, 0x0800, 0x0400, 0x0000, 0x0000 }
}
#endif
};

static const BM2MC_PACKET_FilterCoeffs s_BGRC_PACKET_P_DeviceFilter_AntiFlutterScale =
{
#if defined(BCHP_M2MC_HORIZ_FIR_COEFF_PHASE0_2_COEFF_2_SHIFT)
	{ { 0x0000, 0x0040, 0x0080 }, { 0x0000, 0x0018, 0x0068 } }
#else
{
	{ 0x0000, 0x0000, 0x0030, 0x04C0, 0x07B0, 0x0360, 0x0000, 0x0000 },
	{ 0x0000, 0x0000, 0x0090, 0x0560, 0x0760, 0x02B0, 0x0000, 0x0000 },
	{ 0x0000, 0x0000, 0x00F0, 0x0600, 0x0710, 0x0200, 0x0000, 0x0000 },
	{ 0x0000, 0x0000, 0x0178, 0x0688, 0x0688, 0x0170, 0x0000, 0x0000 },
	{ 0x0000, 0x0000, 0x0200, 0x0710, 0x0600, 0x00F0, 0x0000, 0x0000 },
	{ 0x0000, 0x0000, 0x02B0, 0x0760, 0x0560, 0x0090, 0x0000, 0x0000 },
	{ 0x0000, 0x0000, 0x0360, 0x07B0, 0x04C0, 0x0030, 0x0000, 0x0000 },
	{ 0x0000, 0x0000, 0x01C8, 0x0638, 0x0638, 0x01C8, 0x0000, 0x0000 }
}
#endif
};

static const BM2MC_PACKET_FilterCoeffs s_BGRC_PACKET_P_DeviceFilter_AntiFlutterBlurry =
{
#if defined(BCHP_M2MC_HORIZ_FIR_COEFF_PHASE0_2_COEFF_2_SHIFT)
	{ { 0x0000, 0x0050, 0x0060 }, { 0x0000, 0x0020, 0x0060 } }
#else
{
	{ 0x0000, 0x0000, 0x0000, 0x0500, 0x0600, 0x0500, 0x0000, 0x0000 },
	{ 0x0000, 0x0000, 0x0000, 0x0500, 0x0600, 0x0500, 0x0000, 0x0000 },
	{ 0x0000, 0x0000, 0x0000, 0x0500, 0x0600, 0x0500, 0x0000, 0x0000 },
	{ 0x0000, 0x0000, 0x0000, 0x0500, 0x0600, 0x0500, 0x0000, 0x0000 },
	{ 0x0000, 0x0000, 0x0000, 0x0500, 0x0600, 0x0500, 0x0000, 0x0000 },
	{ 0x0000, 0x0000, 0x0000, 0x0500, 0x0600, 0x0500, 0x0000, 0x0000 },
	{ 0x0000, 0x0000, 0x0000, 0x0500, 0x0600, 0x0500, 0x0000, 0x0000 },
	{ 0x0000, 0x0000, 0x0000, 0x0500, 0x0600, 0x0500, 0x0000, 0x0000 }
}
#endif
};

static const BM2MC_PACKET_FilterCoeffs s_BGRC_PACKET_P_DeviceFilter_AntiFlutterSharp =
{
#if defined(BCHP_M2MC_HORIZ_FIR_COEFF_PHASE0_2_COEFF_2_SHIFT)
	{ { 0x0000, 0x0028, 0x00b0 }, { 0x0000, 0x0000, 0x0080 } }
#else
{
	{ 0x0000, 0x0000, 0x0000, 0x0280, 0x0B00, 0x0280, 0x0000, 0x0000 },
	{ 0x0000, 0x0000, 0x0000, 0x0280, 0x0B00, 0x0280, 0x0000, 0x0000 },
	{ 0x0000, 0x0000, 0x0000, 0x0280, 0x0B00, 0x0280, 0x0000, 0x0000 },
	{ 0x0000, 0x0000, 0x0000, 0x0280, 0x0B00, 0x0280, 0x0000, 0x0000 },
	{ 0x0000, 0x0000, 0x0000, 0x0280, 0x0B00, 0x0280, 0x0000, 0x0000 },
	{ 0x0000, 0x0000, 0x0000, 0x0280, 0x0B00, 0x0280, 0x0000, 0x0000 },
	{ 0x0000, 0x0000, 0x0000, 0x0280, 0x0B00, 0x0280, 0x0000, 0x0000 },
	{ 0x0000, 0x0000, 0x0000, 0x0280, 0x0B00, 0x0280, 0x0000, 0x0000 }
}
#endif
};

/***************************************************************************/
void BGRC_P_CheckTableMismach( void )
{
	/* is s_BGRC_PACKET_P_DeviceGroupHeaderMasks updated according to BM2MC_PACKET_PacketType enum define? */
	if (sizeof(s_BGRC_PACKET_P_DeviceGroupHeaderMasks) / 4 != BM2MC_PACKET_PacketType_eMax)
	{
		BDBG_ERR(("s_BGRC_PACKET_P_DeviceGroupHeaderMasks does NOT matches BM2MC_PACKET_PacketType"));
		BDBG_ASSERT(false);
	}
}

#define SUR_TYPE_SRC  0
#define SUR_TYPE_DST  1
#define SUR_TYPE_OUT  2
static void BGRC_PACKET_P_ValidateSurCompression( BGRC_PacketContext_Handle hContext, uint32_t ulType, uint32_t ulAddr, uint32_t ulWidth, uint32_t ulPitch )
{
#if defined(BCHP_M2MC_BSTC_COMPRESS_CONTROL)
	if ((ulAddr & 0x1F) || /* 32 = 0x1F + 1 is the size of a BSTC compressed 4x4 area */
		(ulPitch & 0x7) || (ulPitch < ulWidth * 2))
	{
		if (SUR_TYPE_OUT==ulType)
		{
			hContext->stSurInvalid.stBits.bOut = 1;
			if (ulAddr & 0x1F)
				BDBG_ERR(("Compressed out surface with bad addr 0x%0x. Following blit is likely dropped", ulAddr));
			else
				BDBG_ERR(("Compressed out surface with bad (pitch 0x%0x, width 0x%x). Following blit is likely dropped", ulPitch, ulWidth));
		}
		else if (SUR_TYPE_DST==ulType)
		{
			hContext->stSurInvalid.stBits.bDst = 1;
			if (ulAddr & 0x1F)
				BDBG_ERR(("Compressed dst surface with bad addr 0x%0x. Following blit is likely dropped", ulAddr));
			else
				BDBG_ERR(("Compressed dst surface with bad (pitch 0x%0x, width 0x%x). Following blit is likely dropped", ulPitch, ulWidth));
		}
		else /* src */
		{
			hContext->stSurInvalid.stBits.bSrc = 1;
			if (ulAddr & 0x1F)
				BDBG_ERR(("Compressed src surface with bad addr 0x%0x. Following blit is dropped", ulAddr));
			else
				BDBG_ERR(("Compressed src surface with bad (pitch 0x%0x, width 0x%x). Following blit is likely dropped", ulPitch, ulWidth));
		}
	}
#elif defined(BCHP_M2MC_DCEG_CFG)
	if (SUR_TYPE_OUT!=ulType)
	{
		if (SUR_TYPE_DST==ulType)
		{
			hContext->stSurInvalid.stBits.bDst = 1;
			BDBG_ERR(("No support for compressed dst surface. Following blit is likely dropped"));
		}
		else /* src */
		{
			hContext->stSurInvalid.stBits.bSrc = 1;
			BDBG_ERR(("No support for compressed src surface. Following blit is likely dropped"));
		}
	}
	else if ((ulWidth < 16) || (ulWidth > 4096))
	{
		hContext->stSurInvalid.stBits.bOut = 1;
		BDBG_ERR(("Compressed out surface with bad width %d. Following blit is likly dropped", ulWidth));
	}
	BSTD_UNUSED(ulAddr);
	BSTD_UNUSED(ulPitch);
#else  /* no compression support */
	if (SUR_TYPE_OUT==ulType)
	{
		hContext->stSurInvalid.stBits.bOut = 1;
		BDBG_ERR(("No support for compressed out surface. Following blit is likely dropped"));
	}
	else if (SUR_TYPE_DST==ulType)
	{
		hContext->stSurInvalid.stBits.bDst = 1;
		BDBG_ERR(("No support for compressed dst surface. Following blit is likely dropped"));
	}
	else /* src */
	{
		hContext->stSurInvalid.stBits.bSrc = 1;
		BDBG_ERR(("No support for compressed src surface. Following blit is likely dropped"));
	}
	BSTD_UNUSED(ulAddr);
	BSTD_UNUSED(ulWidth);
	BSTD_UNUSED(ulPitch);
#endif
}

/***************************************************************************/
#define BGRC_PACKET_P_DEFAULT_SOURCE_SURFACE_FORMAT_DEF_3 ( \
	(8L << BGRC_M2MC(SRC_SURFACE_0_FORMAT_DEF_3_RANGE_EXP_MAP_SCALE_FACTOR_C_SHIFT)) | \
	(8L << BGRC_M2MC(SRC_SURFACE_0_FORMAT_DEF_3_RANGE_EXP_MAP_SCALE_FACTOR_Y_SHIFT)) | \
	BGRC_M2MC(SRC_SURFACE_0_FORMAT_DEF_3_PALETTE_BYPASS_DONT_LOOKUP))

#define BGRC_PACKET_P_SRC_SURFACE_FORMAT_DEF_3_MASK ( \
	BGRC_M2MC(SRC_SURFACE_FORMAT_DEF_3_ZERO_PAD_MASK) | BGRC_M2MC(SRC_SURFACE_FORMAT_DEF_3_CHROMA_FILTER_MASK))
#define BGRC_PACKET_P_DEST_SURFACE_FORMAT_DEF_3_MASK ( \
	BGRC_M2MC(DEST_SURFACE_FORMAT_DEF_3_ZERO_PAD_MASK) | BGRC_M2MC(DEST_SURFACE_FORMAT_DEF_3_CHROMA_FILTER_MASK))
#define BGRC_PACKET_P_OUTPUT_SURFACE_FORMAT_DEF_3_MASK ( \
	BGRC_M2MC(OUTPUT_SURFACE_FORMAT_DEF_3_DITHER_ENABLE_MASK) | BGRC_M2MC(OUTPUT_SURFACE_FORMAT_DEF_3_CHROMA_FILTER_MASK))

#define BGRC_PACKET_P_DISABLE_SURFACE_CHANNELS( sur ) ( \
	BGRC_M2MC(sur##_FORMAT_DEF_3_CH0_DISABLE_MASK) | BGRC_M2MC(sur##_FORMAT_DEF_3_CH1_DISABLE_MASK) | \
	BGRC_M2MC(sur##_FORMAT_DEF_3_CH2_DISABLE_MASK) | BGRC_M2MC(sur##_FORMAT_DEF_3_CH3_DISABLE_MASK))

/***************************************************************************/
static void BGRC_PACKET_P_ProcSwPktSourceFeeder( BGRC_PacketContext_Handle hContext, BM2MC_PACKET_Header *header )
{
	BM2MC_PACKET_PacketSourceFeeder *packet = (BM2MC_PACKET_PacketSourceFeeder *) header;
	uint32_t format00 = s_BGRC_PACKET_P_DevicePixelFormats[packet->plane.format][0];
	uint32_t format01 = s_BGRC_PACKET_P_DevicePixelFormats[packet->plane.format][1];
	uint32_t format02 = s_BGRC_PACKET_P_DevicePixelFormats[packet->plane.format][2] | BGRC_PACKET_P_DEFAULT_SOURCE_SURFACE_FORMAT_DEF_3;
	uint32_t format12 = BGRC_PACKET_P_DISABLE_SURFACE_CHANNELS(SRC_SURFACE) | BGRC_PACKET_P_DEFAULT_SOURCE_SURFACE_FORMAT_DEF_3;
	uint32_t palette_lookup = 0;
	uint32_t ulPitch = packet->plane.pitch;

	hContext->src_format0 = format00;
	hContext->b420Src = false;
	if( BGRC_P_COMPARE_FIELD_DATA(hContext->src_format0, SRC_SURFACE_FORMAT_DEF_1, FORMAT_TYPE, M2MC_FT_Palette) )
	{
		if( BGRC_P_COMPARE_FIELD_DATA(hContext->out_format0, OUTPUT_SURFACE_FORMAT_DEF_1, FORMAT_TYPE, M2MC_FT_Palette) )
			format00 &= M2MC_CHANNEL_MASK;
		else
			palette_lookup = BCHP_M2MC_SRC_SURFACE_FORMAT_DEF_3_PALETTE_BYPASS_MASK;
	}
	hContext->stSurInvalid.stBits.bSrc = 0;
	if (BM2MC_PACKET_PixelFormat_eCompressed_A8_R8_G8_B8 == packet->plane.format)
	{
		BGRC_PACKET_P_ValidateSurCompression( hContext, SUR_TYPE_SRC, packet->plane.address & 0xFFFFFFFF, packet->plane.width, packet->plane.pitch);
#if defined(BCHP_M2MC_BSTC_COMPRESS_CONTROL)
		ulPitch *= 4; /* 4 lines */
#endif
	}

	BGRC_PACKET_P_DEBUG_PRINT_CTX( "-- SrcFeeder          " );
	BGRC_PACKET_P_STORE_REG( SRC_FEEDER_ENABLE, packet->plane.address ? 1 : 0 );
	BGRC_PACKET_P_STORE_REG( SRC_SURFACE_ADDR_0, (uint32_t)(packet->plane.address & 0xFFFFFFFF));
	BGRC_PACKET_P_STORE_REG( SRC_SURFACE_STRIDE_0, ulPitch );
	BGRC_PACKET_P_STORE_REG( SRC_SURFACE_ADDR_1, 0 );
	BGRC_PACKET_P_STORE_REG( SRC_SURFACE_STRIDE_1, 0 );

	BGRC_PACKET_P_STORE_REG( SRC_SURFACE_FORMAT_DEF_1, format00 );
	BGRC_PACKET_P_STORE_REG( SRC_SURFACE_FORMAT_DEF_2, format01 );
	BGRC_PACKET_P_STORE_REG_MASK( SRC_SURFACE_FORMAT_DEF_3, format02 | palette_lookup, BGRC_PACKET_P_SRC_SURFACE_FORMAT_DEF_3_MASK );

	BGRC_PACKET_P_STORE_REG( SRC_SURFACE_1_FORMAT_DEF_1, 0 );
	BGRC_PACKET_P_STORE_REG( SRC_SURFACE_1_FORMAT_DEF_2, 0 );
	BGRC_PACKET_P_STORE_REG_MASK( SRC_SURFACE_1_FORMAT_DEF_3, format12, BGRC_PACKET_P_SRC_SURFACE_FORMAT_DEF_3_MASK );

	BGRC_PACKET_P_STORE_REG( SRC_W_ALPHA, packet->color >> 24 );
	BGRC_PACKET_P_STORE_REG( SRC_CONSTANT_COLOR, packet->color );

#if defined(BCHP_M2MC_SRC_SURFACE_ADDR_0_MSB_ADDR_MSB_MASK)
	BGRC_PACKET_P_STORE_REG( SRC_SURFACE_ADDR_0_MSB, (uint32_t)(packet->plane.address >> 32) );
#endif

#if defined(BCHP_M2MC_BLIT_CTRL_READ_420_AS_FIELDS_MASK)
	BGRC_PACKET_P_STORE_REG_FIELD( BLIT_CTRL, READ_420_AS_FIELDS, DISABLE );
#endif

	BGRC_PACKET_P_DEBUG_PRINT( "\n" );

#if BGRC_PACKET_P_VERIFY_SURFACE_RECTANGLE && BDBG_DEBUG_BUILD
	hContext->SRC_surface_width = packet->plane.width;
	hContext->SRC_surface_height = packet->plane.height;
	hContext->SRC_surface_format = packet->plane.format;
	hContext->SRC_surface_pitch = (BM2MC_PACKET_PixelFormat_eCompressed_A8_R8_G8_B8 == packet->plane.format)? 0 : packet->plane.pitch;
#endif
}

/***************************************************************************/
static void BGRC_PACKET_P_ProcSwPktSourceFeeders( BGRC_PacketContext_Handle hContext, BM2MC_PACKET_Header *header )
{
	BM2MC_PACKET_PacketSourceFeeders *packet = (BM2MC_PACKET_PacketSourceFeeders *) header;
	uint32_t format01 = s_BGRC_PACKET_P_DevicePixelFormats[packet->plane0.format][1];
	uint32_t format02 = s_BGRC_PACKET_P_DevicePixelFormats[packet->plane0.format][2] | BGRC_PACKET_P_DEFAULT_SOURCE_SURFACE_FORMAT_DEF_3;
	uint32_t format10 = s_BGRC_PACKET_P_DevicePixelFormats[packet->plane1.format][0];
	uint32_t format11 = s_BGRC_PACKET_P_DevicePixelFormats[packet->plane1.format][1];
	uint32_t format12 = s_BGRC_PACKET_P_DevicePixelFormats[packet->plane1.format][2] | BGRC_PACKET_P_DEFAULT_SOURCE_SURFACE_FORMAT_DEF_3;
	hContext->src_format0 = s_BGRC_PACKET_P_DevicePixelFormats[packet->plane0.format][0];
	hContext->b420Src = ((packet->plane1.format >= BM2MC_PACKET_PixelFormat_eCb8_Cr8) &&
						 (packet->plane1.format <= BM2MC_PACKET_PixelFormat_eCr10_Cb10));
	hContext->stSurInvalid.stBits.bSrc = 0;
	if (BM2MC_PACKET_PixelFormat_eCompressed_A8_R8_G8_B8 == packet->plane0.format)
	{
		hContext->stSurInvalid.stBits.bSrc = 1;
		BDBG_ERR(("Bad compressed format with PacketSourceFeeders"));
	}

	BGRC_PACKET_P_DEBUG_PRINT_CTX( "-- SrcFeeders         " );
	BGRC_PACKET_P_STORE_REG( SRC_FEEDER_ENABLE, packet->plane0.address ? 1 : 0 );
	BGRC_PACKET_P_STORE_REG( SRC_SURFACE_ADDR_0, (uint32_t)(packet->plane0.address & 0xFFFFFFFF));
	BGRC_PACKET_P_STORE_REG( SRC_SURFACE_STRIDE_0, packet->plane0.pitch );
	BGRC_PACKET_P_STORE_REG( SRC_SURFACE_ADDR_1, (uint32_t)(packet->plane1.address & 0xFFFFFFFF));
	BGRC_PACKET_P_STORE_REG( SRC_SURFACE_STRIDE_1, packet->plane1.pitch );

	BGRC_PACKET_P_STORE_REG( SRC_SURFACE_FORMAT_DEF_1, hContext->src_format0 );
	BGRC_PACKET_P_STORE_REG( SRC_SURFACE_FORMAT_DEF_2, format01 );
	BGRC_PACKET_P_STORE_REG_MASK( SRC_SURFACE_FORMAT_DEF_3, format02, BGRC_PACKET_P_SRC_SURFACE_FORMAT_DEF_3_MASK );

	BGRC_PACKET_P_STORE_REG( SRC_SURFACE_1_FORMAT_DEF_1, format10 );
	BGRC_PACKET_P_STORE_REG( SRC_SURFACE_1_FORMAT_DEF_2, format11 );
	BGRC_PACKET_P_STORE_REG_MASK( SRC_SURFACE_1_FORMAT_DEF_3, format12, BGRC_PACKET_P_SRC_SURFACE_FORMAT_DEF_3_MASK );

	BGRC_PACKET_P_STORE_REG( SRC_W_ALPHA, (packet->color >> 24) | 0xFF0000 );
	BGRC_PACKET_P_STORE_REG( SRC_CONSTANT_COLOR, packet->color );

#if defined(BCHP_M2MC_SRC_SURFACE_ADDR_0_MSB_ADDR_MSB_MASK)
	BGRC_PACKET_P_STORE_REG( SRC_SURFACE_ADDR_0_MSB, (uint32_t)(packet->plane0.address >> 32) );
	BGRC_PACKET_P_STORE_REG( SRC_SURFACE_ADDR_1_MSB, (uint32_t)(packet->plane1.address >> 32) );
#endif

#if defined(BCHP_M2MC_BLIT_CTRL_READ_420_AS_FIELDS_MASK)
	BGRC_PACKET_P_STORE_REG_FIELD( BLIT_CTRL, READ_420_AS_FIELDS, DISABLE );
#endif

	BGRC_PACKET_P_DEBUG_PRINT( "\n" );

#if BGRC_PACKET_P_VERIFY_SURFACE_RECTANGLE && BDBG_DEBUG_BUILD
	hContext->SRC_surface_width = packet->plane0.width;
	hContext->SRC_surface_height = packet->plane0.height;
	hContext->SRC_surface_format = packet->plane0.format;
	hContext->SRC_surface_pitch = packet->plane0.pitch;
#endif
}

/***************************************************************************/
static void BGRC_PACKET_P_ProcSwPktStripedSourceFeeders( BGRC_PacketContext_Handle hContext, BM2MC_PACKET_Header *header )
{
	BM2MC_PACKET_PacketStripedSourceFeeders *packet = (BM2MC_PACKET_PacketStripedSourceFeeders *) header;
	uint32_t format01 = s_BGRC_PACKET_P_DevicePixelFormats[packet->plane.luma_format][1];
	uint32_t format02 = s_BGRC_PACKET_P_DevicePixelFormats[packet->plane.luma_format][2] | BGRC_PACKET_P_DEFAULT_SOURCE_SURFACE_FORMAT_DEF_3;
	uint32_t format10 = s_BGRC_PACKET_P_DeviceStripedPixelFormats[packet->plane.chroma_format - BM2MC_PACKET_PixelFormat_eY8];
	uint32_t format11 = s_BGRC_PACKET_P_DevicePixelFormats[packet->plane.chroma_format][1];
	uint32_t format12 = s_BGRC_PACKET_P_DevicePixelFormats[packet->plane.chroma_format][2] | BGRC_PACKET_P_DEFAULT_SOURCE_SURFACE_FORMAT_DEF_3;
	hContext->src_format0 = s_BGRC_PACKET_P_DeviceStripedPixelFormats[packet->plane.luma_format - BM2MC_PACKET_PixelFormat_eY8];
	hContext->b420Src = true;
	hContext->stSurInvalid.stBits.bSrc = 0;

	BGRC_PACKET_P_DEBUG_PRINT_CTX( "-- StripedSrcFeeders         " );
	BGRC_PACKET_P_STORE_REG( SRC_FEEDER_ENABLE, 1 );
	BGRC_PACKET_P_STORE_REG( SRC_SURFACE_ADDR_0, (uint32_t)(packet->plane.luma_address & 0xFFFFFFFF) );
	BGRC_PACKET_P_STORE_REG( SRC_SURFACE_STRIDE_0, packet->plane.stripe_pitch );
	BGRC_PACKET_P_STORE_REG( SRC_SURFACE_ADDR_1, (uint32_t)(packet->plane.chroma_address & 0xFFFFFFFF));
	BGRC_PACKET_P_STORE_REG( SRC_SURFACE_STRIDE_1, packet->plane.stripe_pitch );
#if defined(BCHP_M2MC_SRC_SURFACE_ADDR_0_BOT_FLD)
	BGRC_PACKET_P_STORE_REG( SRC_SURFACE_ADDR_0_BOT_FLD, (uint32_t)(packet->plane.bottom_field_luma_address & 0xFFFFFFFF));
	BGRC_PACKET_P_STORE_REG( SRC_SURFACE_ADDR_1_BOT_FLD, (uint32_t)(packet->plane.bottom_field_chroma_address & 0xFFFFFFFF));
	BGRC_PACKET_P_STORE_REG_FIELD_COMP( BLIT_CTRL, READ_420_AS_FIELDS, DISABLE, ENABLE, packet->plane.bottom_field_luma_address );
#endif

	BGRC_PACKET_P_STORE_REG( SRC_SURFACE_FORMAT_DEF_1, hContext->src_format0 );
	BGRC_PACKET_P_STORE_REG( SRC_SURFACE_FORMAT_DEF_2, format01 );
	BGRC_PACKET_P_STORE_REG_MASK( SRC_SURFACE_FORMAT_DEF_3, format02, BGRC_PACKET_P_SRC_SURFACE_FORMAT_DEF_3_MASK );

	BGRC_PACKET_P_STORE_REG( SRC_SURFACE_1_FORMAT_DEF_1, format10 );
	BGRC_PACKET_P_STORE_REG( SRC_SURFACE_1_FORMAT_DEF_2, format11 );
	BGRC_PACKET_P_STORE_REG_MASK( SRC_SURFACE_1_FORMAT_DEF_3, format12, BGRC_PACKET_P_SRC_SURFACE_FORMAT_DEF_3_MASK );

	BGRC_PACKET_P_STORE_REG( SRC_W_ALPHA, (packet->color >> 24) | 0xFF0000 );
	BGRC_PACKET_P_STORE_REG( SRC_CONSTANT_COLOR, packet->color );

#if defined(BCHP_M2MC_SRC_SURFACE_ADDR_0_MSB_ADDR_MSB_MASK)
	BGRC_PACKET_P_STORE_REG( SRC_SURFACE_ADDR_0_MSB, (uint32_t)(packet->plane.luma_address >> 32) );
	BGRC_PACKET_P_STORE_REG( SRC_SURFACE_ADDR_1_MSB, (uint32_t)(packet->plane.chroma_address >> 32) );
#endif

#if defined(BCHP_M2MC_SRC_SURFACE_ADDR_0_MSB_ADDR_BOT_FLD_MSB_MASK)
	BGRC_PACKET_P_STORE_REG( SRC_SURFACE_ADDR_0_BOT_FLD_MSB, (uint32_t)(packet->plane.bottom_field_luma_address >> 32) );
	BGRC_PACKET_P_STORE_REG( SRC_SURFACE_ADDR_1_BOT_FLD_MSB, (uint32_t)(packet->plane.bottom_field_chroma_address >> 32) );
#endif

	BGRC_PACKET_P_STORE_REG( BLIT_SRC_STRIPE_HEIGHT_WIDTH_0, (packet->plane.stripe_width>>7) |
		(packet->plane.luma_stripe_height << BGRC_M2MC(BLIT_SRC_STRIPE_HEIGHT_WIDTH_0_STRIPE_HEIGHT_SHIFT)) );
	BGRC_PACKET_P_STORE_REG( BLIT_SRC_STRIPE_HEIGHT_WIDTH_1, (packet->plane.stripe_width>>7) |
		(packet->plane.chroma_stripe_height << BGRC_M2MC(BLIT_SRC_STRIPE_HEIGHT_WIDTH_1_STRIPE_HEIGHT_SHIFT)) );

	BGRC_PACKET_P_DEBUG_PRINT( "\n" );

#if BGRC_PACKET_P_VERIFY_SURFACE_RECTANGLE && BDBG_DEBUG_BUILD
	hContext->SRC_surface_width = packet->plane.width;
	hContext->SRC_surface_height = packet->plane.height;
	hContext->SRC_surface_format = packet->plane.luma_format;
	hContext->SRC_surface_pitch = 0;
#endif
}

/***************************************************************************/
#if ((BCHP_CHIP==7400) || (BCHP_CHIP==7405) || (BCHP_CHIP==7325) || (BCHP_CHIP==7335) || (BCHP_CHIP==7336) || \
	 (BCHP_CHIP==7340) || (BCHP_CHIP==7342) || (BCHP_CHIP==7550) || (BCHP_CHIP==7420) || (BCHP_CHIP==7125) || \
	 (BCHP_CHIP==7468) || (BCHP_CHIP==7408))
/* older chips */
#define BGRC_PACKET_P_SRC_FEEDER_ENABLE_DISABLE     0
#else
/* newer chips */
#define BGRC_PACKET_P_SRC_FEEDER_ENABLE_DISABLE     1
#endif
#define BGRC_PACKET_P_SURFACE_FORMAT_DEF_1_DISABLE  0
#define BGRC_PACKET_P_SURFACE_FORMAT_DEF_2_DISABLE  0

/***************************************************************************/
static void BGRC_PACKET_P_ProcSwPktSourceColor( BGRC_PacketContext_Handle hContext, BM2MC_PACKET_Header *header )
{
	BM2MC_PACKET_PacketSourceColor *packet = (BM2MC_PACKET_PacketSourceColor *) header;
	uint32_t format2 = BGRC_PACKET_P_DISABLE_SURFACE_CHANNELS(SRC_SURFACE) | BGRC_PACKET_P_DEFAULT_SOURCE_SURFACE_FORMAT_DEF_3;
	hContext->src_format0 = 0;
	hContext->b420Src = false;
	hContext->stSurInvalid.stBits.bSrc = 0;

	BGRC_PACKET_P_DEBUG_PRINT_CTX( "-- SrcColor           " );
	BGRC_PACKET_P_STORE_REG( SRC_FEEDER_ENABLE, 1 );
	BGRC_PACKET_P_STORE_REG( SRC_SURFACE_ADDR_0, 0 );
	BGRC_PACKET_P_STORE_REG( SRC_SURFACE_STRIDE_0, 0 );
	BGRC_PACKET_P_STORE_REG( SRC_SURFACE_ADDR_1, 0 );
	BGRC_PACKET_P_STORE_REG( SRC_SURFACE_STRIDE_1, 0 );

	BGRC_PACKET_P_STORE_REG( SRC_SURFACE_FORMAT_DEF_1, BGRC_PACKET_P_SURFACE_FORMAT_DEF_1_DISABLE );
	BGRC_PACKET_P_STORE_REG( SRC_SURFACE_FORMAT_DEF_2, BGRC_PACKET_P_SURFACE_FORMAT_DEF_2_DISABLE );
	BGRC_PACKET_P_STORE_REG_MASK( SRC_SURFACE_FORMAT_DEF_3, format2, BGRC_PACKET_P_SRC_SURFACE_FORMAT_DEF_3_MASK );

	BGRC_PACKET_P_STORE_REG( SRC_SURFACE_1_FORMAT_DEF_1, 0 );
	BGRC_PACKET_P_STORE_REG( SRC_SURFACE_1_FORMAT_DEF_2, 0 );
	BGRC_PACKET_P_STORE_REG_MASK( SRC_SURFACE_1_FORMAT_DEF_3, format2, BGRC_PACKET_P_SRC_SURFACE_FORMAT_DEF_3_MASK );

	BGRC_PACKET_P_STORE_REG( SRC_W_ALPHA, packet->color >> 24 );
	BGRC_PACKET_P_STORE_REG( SRC_CONSTANT_COLOR, packet->color );

#if defined(BCHP_M2MC_SRC_SURFACE_ADDR_0_MSB_ADDR_MSB_MASK)
	BGRC_PACKET_P_STORE_REG( SRC_SURFACE_ADDR_0_MSB, 0 );
#endif

#if defined(BCHP_M2MC_BLIT_CTRL_READ_420_AS_FIELDS_MASK)
	BGRC_PACKET_P_STORE_REG_FIELD( BLIT_CTRL, READ_420_AS_FIELDS, DISABLE );
#endif

#if BGRC_PACKET_P_VERIFY_SURFACE_RECTANGLE && BDBG_DEBUG_BUILD
	hContext->SRC_surface_width = 0;
	hContext->SRC_surface_height = 0;
#endif

	BGRC_PACKET_P_DEBUG_PRINT( "\n" );
}

/***************************************************************************/
static void BGRC_PACKET_P_ProcSwPktSourceNone( BGRC_PacketContext_Handle hContext, BM2MC_PACKET_Header *header )
{
	uint32_t format2 = BGRC_PACKET_P_DISABLE_SURFACE_CHANNELS(SRC_SURFACE) | BGRC_PACKET_P_DEFAULT_SOURCE_SURFACE_FORMAT_DEF_3;
	hContext->src_format0 = 0;
	hContext->b420Src = false;
	hContext->stSurInvalid.stBits.bSrc = 0;

	BSTD_UNUSED(header);
	BGRC_PACKET_P_DEBUG_PRINT_CTX( "-- SrcNone            " );
	BGRC_PACKET_P_STORE_REG( SRC_FEEDER_ENABLE, BGRC_PACKET_P_SRC_FEEDER_ENABLE_DISABLE );
	BGRC_PACKET_P_STORE_REG( SRC_SURFACE_ADDR_0, 0 );
	BGRC_PACKET_P_STORE_REG( SRC_SURFACE_STRIDE_0, 0 );
	BGRC_PACKET_P_STORE_REG( SRC_SURFACE_ADDR_1, 0 );
	BGRC_PACKET_P_STORE_REG( SRC_SURFACE_STRIDE_1, 0 );

	BGRC_PACKET_P_STORE_REG( SRC_SURFACE_FORMAT_DEF_1, BGRC_PACKET_P_SURFACE_FORMAT_DEF_1_DISABLE );
	BGRC_PACKET_P_STORE_REG( SRC_SURFACE_FORMAT_DEF_2, BGRC_PACKET_P_SURFACE_FORMAT_DEF_2_DISABLE );
	BGRC_PACKET_P_STORE_REG_MASK( SRC_SURFACE_FORMAT_DEF_3, format2, BGRC_PACKET_P_SRC_SURFACE_FORMAT_DEF_3_MASK );

	BGRC_PACKET_P_STORE_REG( SRC_SURFACE_1_FORMAT_DEF_1, 0 );
	BGRC_PACKET_P_STORE_REG( SRC_SURFACE_1_FORMAT_DEF_2, 0 );
	BGRC_PACKET_P_STORE_REG_MASK( SRC_SURFACE_1_FORMAT_DEF_3, format2, BGRC_PACKET_P_SRC_SURFACE_FORMAT_DEF_3_MASK );

	BGRC_PACKET_P_STORE_REG( SRC_W_ALPHA, 0 );
	BGRC_PACKET_P_STORE_REG( SRC_CONSTANT_COLOR, 0 );

#if defined(BCHP_M2MC_SRC_SURFACE_ADDR_0_MSB_ADDR_MSB_MASK)
	BGRC_PACKET_P_STORE_REG( SRC_SURFACE_ADDR_0_MSB, 0 );
#endif

#if defined(BCHP_M2MC_BLIT_CTRL_READ_420_AS_FIELDS_MASK)
	BGRC_PACKET_P_STORE_REG_FIELD( BLIT_CTRL, READ_420_AS_FIELDS, DISABLE );
#endif

#if BGRC_PACKET_P_VERIFY_SURFACE_RECTANGLE && BDBG_DEBUG_BUILD
	hContext->SRC_surface_width = 0;
	hContext->SRC_surface_height = 0;
#endif

	BGRC_PACKET_P_DEBUG_PRINT( "\n" );
}

/***************************************************************************/
static void BGRC_PACKET_P_ProcSwPktSourceControl( BGRC_PacketContext_Handle hContext, BM2MC_PACKET_Header *header )
{
	BM2MC_PACKET_PacketSourceControl *packet = (BM2MC_PACKET_PacketSourceControl *) header;

	BGRC_PACKET_P_DEBUG_PRINT_CTX( "-- SrcControl            " );
	BGRC_PACKET_P_STORE_REG_FIELD_COMP( SRC_SURFACE_FORMAT_DEF_3, ZERO_PAD, REPLICATE, ZERO_PAD, packet->zero_pad );
	BGRC_PACKET_P_STORE_REG_FIELD_COMP( SRC_SURFACE_FORMAT_DEF_3, CHROMA_FILTER, REPLICATE, FILTER, packet->chroma_filter );
#ifdef BCHP_M2MC_SRC_SURFACE_1_FORMAT_DEF_3
	BGRC_PACKET_P_STORE_REG_FIELD_COMP( SRC_SURFACE_1_FORMAT_DEF_3, ZERO_PAD, REPLICATE, ZERO_PAD, packet->zero_pad );
	BGRC_PACKET_P_STORE_REG_FIELD_COMP( SRC_SURFACE_1_FORMAT_DEF_3, CHROMA_FILTER, REPLICATE, FILTER, packet->chroma_filter );
#endif
	BGRC_PACKET_P_DEBUG_PRINT( "\n" );
}

/***************************************************************************/
static void BGRC_PACKET_P_ProcSwPktDestinationFeeder( BGRC_PacketContext_Handle hContext, BM2MC_PACKET_Header *header )
{
	BM2MC_PACKET_PacketDestinationFeeder *packet = (BM2MC_PACKET_PacketDestinationFeeder *) header;
	uint32_t format0 = s_BGRC_PACKET_P_DevicePixelFormats[packet->plane.format][0];
	uint32_t format2 = s_BGRC_PACKET_P_DevicePixelFormats[packet->plane.format][2];
	uint32_t palette_lookup = 0;
	uint32_t ulPitch = packet->plane.pitch;

	hContext->dst_format0 = format0;
	if( BGRC_P_COMPARE_FIELD_DATA(hContext->dst_format0, DEST_SURFACE_FORMAT_DEF_1, FORMAT_TYPE, M2MC_FT_Palette) )
	{
		if( BGRC_P_COMPARE_FIELD_DATA(hContext->out_format0, OUTPUT_SURFACE_FORMAT_DEF_1, FORMAT_TYPE, M2MC_FT_Palette) )
			format0 &= M2MC_CHANNEL_MASK;
		else
			palette_lookup = BCHP_M2MC_SRC_SURFACE_FORMAT_DEF_3_PALETTE_BYPASS_MASK;
	}
	hContext->bDestForceDisabled = false;
	hContext->stSurInvalid.stBits.bDst = 0;
	if (BM2MC_PACKET_PixelFormat_eCompressed_A8_R8_G8_B8 == packet->plane.format)
	{
		BGRC_PACKET_P_ValidateSurCompression( hContext, SUR_TYPE_DST, packet->plane.address & 0xFFFFFFFF, packet->plane.width, packet->plane.pitch);
#if defined(BCHP_M2MC_BSTC_COMPRESS_CONTROL)
		ulPitch *= 4; /* 4 lines */
#endif
	}

	BGRC_PACKET_P_DEBUG_PRINT_CTX( "-- DstFeeder          " );
	BGRC_PACKET_P_STORE_REG( DEST_FEEDER_ENABLE, packet->plane.address ? 1 : 0 );
	BGRC_PACKET_P_STORE_REG( DEST_SURFACE_ADDR_0, (uint32_t)(packet->plane.address & 0xFFFFFFFF));
	BGRC_PACKET_P_STORE_REG( DEST_SURFACE_STRIDE_0, ulPitch );
	BGRC_PACKET_P_STORE_REG( DEST_SURFACE_ADDR_1, 0 );
	BGRC_PACKET_P_STORE_REG( DEST_SURFACE_STRIDE_1, 0 );
	BGRC_PACKET_P_STORE_REG( DEST_SURFACE_FORMAT_DEF_1, format0 );
	BGRC_PACKET_P_STORE_REG( DEST_SURFACE_FORMAT_DEF_2, s_BGRC_PACKET_P_DevicePixelFormats[packet->plane.format][1] );
	BGRC_PACKET_P_STORE_REG_MASK( DEST_SURFACE_FORMAT_DEF_3, format2 | palette_lookup, BGRC_PACKET_P_DEST_SURFACE_FORMAT_DEF_3_MASK );
	BGRC_PACKET_P_STORE_REG( DEST_W_ALPHA, packet->color >> 24 );
	BGRC_PACKET_P_STORE_REG( DEST_CONSTANT_COLOR, packet->color );

#if defined(BCHP_M2MC_DEST_SURFACE_ADDR_0_MSB_ADDR_MSB_MASK)
	BGRC_PACKET_P_STORE_REG( DEST_SURFACE_ADDR_0_MSB, (uint32_t)(packet->plane.address >> 32) );
#endif

	BGRC_PACKET_P_DEBUG_PRINT( "\n" );

#if BGRC_PACKET_P_VERIFY_SURFACE_RECTANGLE && BDBG_DEBUG_BUILD
	hContext->DEST_surface_width = packet->plane.width;
	hContext->DEST_surface_height = packet->plane.height;
	hContext->DEST_surface_format = packet->plane.format;
	hContext->DEST_surface_pitch = (BM2MC_PACKET_PixelFormat_eCompressed_A8_R8_G8_B8 == packet->plane.format)? 0 : packet->plane.pitch;
#endif
}

/***************************************************************************/
static void BGRC_PACKET_P_ProcSwPktDestinationColor( BGRC_PacketContext_Handle hContext, BM2MC_PACKET_Header *header )
{
	BM2MC_PACKET_PacketDestinationColor *packet = (BM2MC_PACKET_PacketDestinationColor *) header;
	uint32_t format2 = BGRC_PACKET_P_DISABLE_SURFACE_CHANNELS(DEST_SURFACE);
	hContext->dst_format0 = 0;
	hContext->bDestForceDisabled = false;
	hContext->stSurInvalid.stBits.bDst = 0;

	BGRC_PACKET_P_DEBUG_PRINT_CTX( "-- DstColor           " );
	BGRC_PACKET_P_STORE_REG( DEST_FEEDER_ENABLE, 1 );
	BGRC_PACKET_P_STORE_REG( DEST_SURFACE_ADDR_0, 0 );
	BGRC_PACKET_P_STORE_REG( DEST_SURFACE_STRIDE_0, 0 );
	BGRC_PACKET_P_STORE_REG( DEST_SURFACE_ADDR_1, 0 );
	BGRC_PACKET_P_STORE_REG( DEST_SURFACE_STRIDE_1, 0 );
	BGRC_PACKET_P_STORE_REG( DEST_SURFACE_FORMAT_DEF_1, BGRC_PACKET_P_SURFACE_FORMAT_DEF_1_DISABLE );
	BGRC_PACKET_P_STORE_REG( DEST_SURFACE_FORMAT_DEF_2, BGRC_PACKET_P_SURFACE_FORMAT_DEF_2_DISABLE );
	BGRC_PACKET_P_STORE_REG_MASK( DEST_SURFACE_FORMAT_DEF_3, format2, BGRC_PACKET_P_DEST_SURFACE_FORMAT_DEF_3_MASK );
	BGRC_PACKET_P_STORE_REG( DEST_W_ALPHA, packet->color >> 24 );
	BGRC_PACKET_P_STORE_REG( DEST_CONSTANT_COLOR, packet->color );

#if defined(BCHP_M2MC_DEST_SURFACE_ADDR_0_MSB_ADDR_MSB_MASK)
	BGRC_PACKET_P_STORE_REG( DEST_SURFACE_ADDR_0_MSB, 0 );
#endif

	BGRC_PACKET_P_DEBUG_PRINT( "\n" );
}

/***************************************************************************/
static void BGRC_PACKET_P_ProcSwPktDestinationNone( BGRC_PacketContext_Handle hContext, BM2MC_PACKET_Header *header )
{
	uint32_t format2 = BGRC_PACKET_P_DISABLE_SURFACE_CHANNELS(DEST_SURFACE);
	hContext->dst_format0 = 0;
	hContext->bDestForceDisabled = false;
	hContext->stSurInvalid.stBits.bDst = 0;

	BSTD_UNUSED(header);
	BGRC_PACKET_P_DEBUG_PRINT_CTX( "-- DstNone            " );
	BGRC_PACKET_P_STORE_REG( DEST_FEEDER_ENABLE, 0 );
	BGRC_PACKET_P_STORE_REG( DEST_SURFACE_ADDR_0, 0 );
	BGRC_PACKET_P_STORE_REG( DEST_SURFACE_STRIDE_0, 0 );
	BGRC_PACKET_P_STORE_REG( DEST_SURFACE_ADDR_1, 0 );
	BGRC_PACKET_P_STORE_REG( DEST_SURFACE_STRIDE_1, 0 );
	BGRC_PACKET_P_STORE_REG( DEST_SURFACE_FORMAT_DEF_1, 0 );
	BGRC_PACKET_P_STORE_REG( DEST_SURFACE_FORMAT_DEF_2, 0 );
	BGRC_PACKET_P_STORE_REG_MASK( DEST_SURFACE_FORMAT_DEF_3, format2, BGRC_PACKET_P_DEST_SURFACE_FORMAT_DEF_3_MASK );
	BGRC_PACKET_P_STORE_REG( DEST_W_ALPHA, 0 );
	BGRC_PACKET_P_STORE_REG( DEST_CONSTANT_COLOR, 0 );

#if defined(BCHP_M2MC_DEST_SURFACE_ADDR_0_MSB_ADDR_MSB_MASK)
	BGRC_PACKET_P_STORE_REG( DEST_SURFACE_ADDR_0_MSB, 0 );
#endif

	BGRC_PACKET_P_DEBUG_PRINT( "\n" );
}

/***************************************************************************/
static void BGRC_PACKET_P_ProcSwPktDestinationControl( BGRC_PacketContext_Handle hContext, BM2MC_PACKET_Header *header )
{
	BM2MC_PACKET_PacketDestinationControl *packet = (BM2MC_PACKET_PacketDestinationControl *) header;

	BGRC_PACKET_P_DEBUG_PRINT_CTX( "-- DstControl            " );
	BGRC_PACKET_P_STORE_REG_FIELD_COMP( DEST_SURFACE_FORMAT_DEF_3, ZERO_PAD, REPLICATE, ZERO_PAD, packet->zero_pad );
	BGRC_PACKET_P_STORE_REG_FIELD_COMP( DEST_SURFACE_FORMAT_DEF_3, CHROMA_FILTER, REPLICATE, FILTER, packet->chroma_filter );
	BGRC_PACKET_P_DEBUG_PRINT( "\n" );
}

/***************************************************************************/
static void BGRC_PACKET_P_ProcSwPktOutputFeeder( BGRC_PacketContext_Handle hContext, BM2MC_PACKET_Header *header )
{
	BM2MC_PACKET_PacketOutputFeeder *packet = (BM2MC_PACKET_PacketOutputFeeder *) header;
	uint32_t out_format0 = s_BGRC_PACKET_P_DevicePixelFormats[packet->plane.format][0];
	uint32_t out_format2 = s_BGRC_PACKET_P_DevicePixelFormats[packet->plane.format][2];
	uint32_t format_type = out_format0 & BGRC_M2MC(OUTPUT_SURFACE_FORMAT_DEF_1_FORMAT_TYPE_MASK);
	uint32_t format0 = ((format_type == M2MC_FT_Palette) || (format_type == M2MC_FT_YCbCr420)) ? out_format0 & M2MC_CHANNEL_MASK : out_format0;
	uint32_t ulPitch = packet->plane.pitch;

	if( (format0 & BGRC_M2MC(SRC_SURFACE_FORMAT_DEF_1_FORMAT_TYPE_MASK)) == M2MC_FT_WRGB1565 )
		format0 &= ~BGRC_M2MC(SRC_SURFACE_FORMAT_DEF_1_FORMAT_TYPE_MASK);
	hContext->stSurInvalid.stBits.bOut = 0;
	if (BM2MC_PACKET_PixelFormat_eCompressed_A8_R8_G8_B8 == packet->plane.format)
	{
		BGRC_PACKET_P_ValidateSurCompression( hContext, SUR_TYPE_OUT, packet->plane.address & 0xFFFFFFFF, packet->plane.width, packet->plane.pitch);
#if defined(BCHP_M2MC_BSTC_COMPRESS_CONTROL)
		ulPitch *= 4;  /* 4 lines */
#endif
	}

	hContext->out_format0 = out_format0;
	BGRC_PACKET_P_DEBUG_PRINT_CTX( "-- OutFeeder          " );
	BGRC_PACKET_P_STORE_REG( OUTPUT_FEEDER_ENABLE, packet->plane.address ? 1 : 0 );
	BGRC_PACKET_P_STORE_REG( OUTPUT_SURFACE_ADDR_0, (uint32_t)(packet->plane.address & 0xFFFFFFFF));
	BGRC_PACKET_P_STORE_REG( OUTPUT_SURFACE_STRIDE_0, ulPitch );
	BGRC_PACKET_P_STORE_REG( OUTPUT_SURFACE_ADDR_1, 0 );
	BGRC_PACKET_P_STORE_REG( OUTPUT_SURFACE_STRIDE_1, 0 );
	BGRC_PACKET_P_STORE_REG( OUTPUT_SURFACE_FORMAT_DEF_1, format0 );
	BGRC_PACKET_P_STORE_REG( OUTPUT_SURFACE_FORMAT_DEF_2, s_BGRC_PACKET_P_DevicePixelFormats[packet->plane.format][1] );
	BGRC_PACKET_P_STORE_REG_MASK( OUTPUT_SURFACE_FORMAT_DEF_3, out_format2, BGRC_PACKET_P_OUTPUT_SURFACE_FORMAT_DEF_3_MASK );

	/* check if source is palette */
	if( BGRC_P_COMPARE_FIELD_DATA(hContext->src_format0, SRC_SURFACE_FORMAT_DEF_1, FORMAT_TYPE, M2MC_FT_Palette) )
	{
		uint32_t def1 = BGRC_PACKET_P_GET_REG(SRC_SURFACE_FORMAT_DEF_1);
		uint32_t def3 = BGRC_PACKET_P_GET_REG(SRC_SURFACE_FORMAT_DEF_3);

		if( BGRC_P_COMPARE_FIELD_DATA(hContext->out_format0, OUTPUT_SURFACE_FORMAT_DEF_1, FORMAT_TYPE, M2MC_FT_Palette) )
		{
			BGRC_PACKET_P_STORE_REG( SRC_SURFACE_FORMAT_DEF_1, hContext->src_format0 & M2MC_CHANNEL_MASK );
			BGRC_PACKET_P_STORE_REG_FIELD( SRC_SURFACE_FORMAT_DEF_3, PALETTE_BYPASS, DONT_LOOKUP );
		}
		else
		{
			BGRC_PACKET_P_STORE_REG( SRC_SURFACE_FORMAT_DEF_1, hContext->src_format0 );
			BGRC_PACKET_P_STORE_REG_FIELD( SRC_SURFACE_FORMAT_DEF_3, PALETTE_BYPASS, LOOKUP );
		}

		if( (def1 != BGRC_PACKET_P_GET_REG(SRC_SURFACE_FORMAT_DEF_1)) || (def3 != BGRC_PACKET_P_GET_REG(SRC_SURFACE_FORMAT_DEF_3)) )
			hContext->ulGroupMask |= BGRC_M2MC(LIST_PACKET_HEADER_1_SRC_FEEDER_GRP_CNTRL_MASK);
	}

	/* check if dest is palette */
	if( BGRC_P_COMPARE_FIELD_DATA(hContext->dst_format0, DEST_SURFACE_FORMAT_DEF_1, FORMAT_TYPE, M2MC_FT_Palette) )
	{
		uint32_t def1 = BGRC_PACKET_P_GET_REG(DEST_SURFACE_FORMAT_DEF_1);
		uint32_t def3 = BGRC_PACKET_P_GET_REG(DEST_SURFACE_FORMAT_DEF_3);

		if( BGRC_P_COMPARE_FIELD_DATA(hContext->out_format0, OUTPUT_SURFACE_FORMAT_DEF_1, FORMAT_TYPE, M2MC_FT_Palette) )
		{
			BGRC_PACKET_P_STORE_REG( DEST_SURFACE_FORMAT_DEF_1, hContext->dst_format0 & M2MC_CHANNEL_MASK );
			BGRC_PACKET_P_STORE_REG_FIELD( DEST_SURFACE_FORMAT_DEF_3, PALETTE_BYPASS, DONT_LOOKUP );
		}
		else
		{
			BGRC_PACKET_P_STORE_REG( DEST_SURFACE_FORMAT_DEF_1, hContext->dst_format0 );
			BGRC_PACKET_P_STORE_REG_FIELD( DEST_SURFACE_FORMAT_DEF_3, PALETTE_BYPASS, LOOKUP );
		}

		if( (def1 != BGRC_PACKET_P_GET_REG(DEST_SURFACE_FORMAT_DEF_1)) || (def3 != BGRC_PACKET_P_GET_REG(DEST_SURFACE_FORMAT_DEF_3)) )
			hContext->ulGroupMask |= BGRC_M2MC(LIST_PACKET_HEADER_1_DST_FEEDER_GRP_CNTRL_MASK);
	}

#if defined(BCHP_M2MC_OUTPUT_SURFACE_ADDR_0_MSB_ADDR_MSB_MASK)
	BGRC_PACKET_P_STORE_REG( OUTPUT_SURFACE_ADDR_0_MSB, (uint32_t)(packet->plane.address >> 32) );
#endif

	BGRC_PACKET_P_DEBUG_PRINT( "\n" );

#if BGRC_PACKET_P_VERIFY_SURFACE_RECTANGLE && BDBG_DEBUG_BUILD
	hContext->OUTPUT_surface_width = packet->plane.width;
	hContext->OUTPUT_surface_height = packet->plane.height;
	hContext->OUTPUT_surface_format = packet->plane.format;
	hContext->OUTPUT_surface_pitch = (BM2MC_PACKET_PixelFormat_eCompressed_A8_R8_G8_B8 == packet->plane.format)? 0 : packet->plane.pitch;
#endif
}

/***************************************************************************/
static void BGRC_PACKET_P_ProcSwPktOutputControl( BGRC_PacketContext_Handle hContext, BM2MC_PACKET_Header *header )
{
	BM2MC_PACKET_PacketOutputControl *packet = (BM2MC_PACKET_PacketOutputControl *) header;

	BGRC_PACKET_P_DEBUG_PRINT_CTX( "-- OutControl            " );
	BGRC_PACKET_P_STORE_REG_FIELD_COMP( OUTPUT_SURFACE_FORMAT_DEF_3, DITHER_ENABLE, DISABLE, ENABLE, packet->dither );
	BGRC_PACKET_P_STORE_REG_FIELD_COMP( OUTPUT_SURFACE_FORMAT_DEF_3, CHROMA_FILTER, FIRST, FILTER, packet->chroma_filter );
	BGRC_PACKET_P_DEBUG_PRINT( "\n" );
}

/***************************************************************************/
static const bool s_BGRC_PACKET_P_NeedDestForBlend[] =
{
	false, /* BM2MC_PACKET_BlendFactor_eZero = 0*/
	false, /* BM2MC_PACKET_BlendFactor_eHalf */
	false, /* BM2MC_PACKET_BlendFactor_eOne */
	false, /* BM2MC_PACKET_BlendFactor_eSourceColor */
	false, /* BM2MC_PACKET_BlendFactor_eInverseSourceColor */
	false, /* BM2MC_PACKET_BlendFactor_eSourceAlpha */
	false, /* BM2MC_PACKET_BlendFactor_eInverseSourceAlpha */
	true,  /* BM2MC_PACKET_BlendFactor_eDestinationColor */
	true,  /* BM2MC_PACKET_BlendFactor_eInverseDestinationColor */
	true,  /* BM2MC_PACKET_BlendFactor_eDestinationAlpha */
	true,  /* BM2MC_PACKET_BlendFactor_eInverseDestinationAlpha */
	false, /* BM2MC_PACKET_BlendFactor_eConstantColor */
	false, /* BM2MC_PACKET_BlendFactor_eInverseConstantColor */
	false, /* BM2MC_PACKET_BlendFactor_eConstantAlpha */
	false  /* BM2MC_PACKET_BlendFactor_eInverseConstantAlpha */
};

/***************************************************************************/
#define BGRC_PACKET_P_NEED_DEST_FOR_BLEND( equation ) ( \
	s_BGRC_PACKET_P_NeedDestForBlend[(equation).a] || \
	s_BGRC_PACKET_P_NeedDestForBlend[(equation).b] || \
	s_BGRC_PACKET_P_NeedDestForBlend[(equation).c] || \
	s_BGRC_PACKET_P_NeedDestForBlend[(equation).d] || \
	s_BGRC_PACKET_P_NeedDestForBlend[(equation).e])

/***************************************************************************/
static const uint32_t s_BGRC_PACKET_P_BlendOps[] =
{
	BGRC_M2MC(BLEND_COLOR_OP_OP_D_ZERO),
	BGRC_M2MC(BLEND_COLOR_OP_OP_A_HALF),
	BGRC_M2MC(BLEND_COLOR_OP_OP_A_ZERO) | BGRC_M2MC(BLEND_COLOR_OP_OP_A_INV_MASK),
	BGRC_M2MC(BLEND_COLOR_OP_OP_A_SOURCE_COLOR),
	BGRC_M2MC(BLEND_COLOR_OP_OP_A_SOURCE_COLOR) | BGRC_M2MC(BLEND_COLOR_OP_OP_A_INV_MASK),
	BGRC_M2MC(BLEND_COLOR_OP_OP_A_SOURCE_ALPHA),
	BGRC_M2MC(BLEND_COLOR_OP_OP_A_SOURCE_ALPHA) | BGRC_M2MC(BLEND_COLOR_OP_OP_A_INV_MASK),
	BGRC_M2MC(BLEND_COLOR_OP_OP_A_DEST_COLOR),
	BGRC_M2MC(BLEND_COLOR_OP_OP_A_DEST_COLOR) | BGRC_M2MC(BLEND_COLOR_OP_OP_A_INV_MASK),
	BGRC_M2MC(BLEND_COLOR_OP_OP_A_DEST_ALPHA),
	BGRC_M2MC(BLEND_COLOR_OP_OP_A_DEST_ALPHA) | BGRC_M2MC(BLEND_COLOR_OP_OP_A_INV_MASK),
	BGRC_M2MC(BLEND_COLOR_OP_OP_A_CONSTANT_COLOR),
	BGRC_M2MC(BLEND_COLOR_OP_OP_A_CONSTANT_COLOR) | BGRC_M2MC(BLEND_COLOR_OP_OP_A_INV_MASK),
	BGRC_M2MC(BLEND_COLOR_OP_OP_A_CONSTANT_ALPHA),
	BGRC_M2MC(BLEND_COLOR_OP_OP_A_CONSTANT_ALPHA) | BGRC_M2MC(BLEND_COLOR_OP_OP_A_INV_MASK)
};

/***************************************************************************/
#define BGRC_PACKET_P_CONVERT_BLEND( equation ) ( \
	(s_BGRC_PACKET_P_BlendOps[(equation).a] << BGRC_M2MC(BLEND_COLOR_OP_OP_A_SHIFT)) | \
	(s_BGRC_PACKET_P_BlendOps[(equation).b] << BGRC_M2MC(BLEND_COLOR_OP_OP_B_SHIFT)) | \
	((equation).sub_cd << BGRC_M2MC(BLEND_COLOR_OP_SUBTRACT_CD_SHIFT)) | \
	(s_BGRC_PACKET_P_BlendOps[(equation).c] << BGRC_M2MC(BLEND_COLOR_OP_OP_C_SHIFT)) | \
	(s_BGRC_PACKET_P_BlendOps[(equation).d] << BGRC_M2MC(BLEND_COLOR_OP_OP_D_SHIFT)) | \
	((equation).sub_e << BGRC_M2MC(BLEND_COLOR_OP_SUBTRACT_E_SHIFT)) | \
	(s_BGRC_PACKET_P_BlendOps[(equation).e] << BGRC_M2MC(BLEND_COLOR_OP_OP_E_SHIFT)))

#if 1 /* syang */
#define BGRC_PACKET_P_SRC_COLOR_KEY_ACTION ( \
	(BGRC_M2MC(BLEND_COLOR_KEY_ACTION_ACTION_NOT_SRC_NOT_DEST_TAKE_ROP)  << BGRC_M2MC(BLEND_COLOR_KEY_ACTION_ACTION_NOT_SRC_NOT_DEST_SHIFT)) | \
	(BGRC_M2MC(BLEND_COLOR_KEY_ACTION_ACTION_NOT_SRC_DEST_TAKE_ROP)      << BGRC_M2MC(BLEND_COLOR_KEY_ACTION_ACTION_NOT_SRC_DEST_SHIFT)) | \
	(BGRC_M2MC(BLEND_COLOR_KEY_ACTION_ACTION_SRC_NOT_DEST_TAKE_DEST)     << BGRC_M2MC(BLEND_COLOR_KEY_ACTION_ACTION_SRC_NOT_DEST_SHIFT)) | \
	(BGRC_M2MC(BLEND_COLOR_KEY_ACTION_ACTION_SRC_DEST_TAKE_DEST)         << BGRC_M2MC(BLEND_COLOR_KEY_ACTION_ACTION_SRC_DEST_SHIFT)))

#define BGRC_PACKET_P_DST_COLOR_KEY_ACTION ( \
	(BGRC_M2MC(BLEND_COLOR_KEY_ACTION_ACTION_NOT_SRC_NOT_DEST_TAKE_DEST) << BGRC_M2MC(BLEND_COLOR_KEY_ACTION_ACTION_NOT_SRC_NOT_DEST_SHIFT)) | \
	(BGRC_M2MC(BLEND_COLOR_KEY_ACTION_ACTION_NOT_SRC_DEST_TAKE_ROP)      << BGRC_M2MC(BLEND_COLOR_KEY_ACTION_ACTION_NOT_SRC_DEST_SHIFT)) | \
	(BGRC_M2MC(BLEND_COLOR_KEY_ACTION_ACTION_SRC_NOT_DEST_TAKE_DEST)     << BGRC_M2MC(BLEND_COLOR_KEY_ACTION_ACTION_SRC_NOT_DEST_SHIFT)) | \
	(BGRC_M2MC(BLEND_COLOR_KEY_ACTION_ACTION_SRC_DEST_TAKE_ROP)          << BGRC_M2MC(BLEND_COLOR_KEY_ACTION_ACTION_SRC_DEST_SHIFT)))

#define BGRC_PACKET_P_BLEND_COLOR_KEY_ACTION ( \
	(BGRC_M2MC(BLEND_COLOR_KEY_ACTION_ACTION_NOT_SRC_NOT_DEST_TAKE_DEST) << BGRC_M2MC(BLEND_COLOR_KEY_ACTION_ACTION_NOT_SRC_NOT_DEST_SHIFT)) | \
	(BGRC_M2MC(BLEND_COLOR_KEY_ACTION_ACTION_NOT_SRC_DEST_TAKE_DEST)     << BGRC_M2MC(BLEND_COLOR_KEY_ACTION_ACTION_NOT_SRC_DEST_SHIFT)) | \
	(BGRC_M2MC(BLEND_COLOR_KEY_ACTION_ACTION_SRC_NOT_DEST_TAKE_ROP)      << BGRC_M2MC(BLEND_COLOR_KEY_ACTION_ACTION_SRC_NOT_DEST_SHIFT)) | \
	(BGRC_M2MC(BLEND_COLOR_KEY_ACTION_ACTION_SRC_DEST_TAKE_ROP)          << BGRC_M2MC(BLEND_COLOR_KEY_ACTION_ACTION_SRC_DEST_SHIFT)))

#define BGRC_PACKET_P_SET_COLORKEY_ACTION() \
{ \
	if( BGRC_PACKET_P_GET_REG_FIELD(BLIT_HEADER, SRC_COLOR_KEY_ENABLE) && \
		BGRC_PACKET_P_GET_REG_FIELD(BLIT_HEADER, DEST_COLOR_KEY_ENABLE) ) \
	{ \
		BGRC_PACKET_P_STORE_REG( BLEND_COLOR_KEY_ACTION, BGRC_PACKET_P_BLEND_COLOR_KEY_ACTION ); \
	} \
	else if( BGRC_PACKET_P_GET_REG_FIELD(BLIT_HEADER, DEST_COLOR_KEY_ENABLE) ) \
	{ \
		BGRC_PACKET_P_STORE_REG( BLEND_COLOR_KEY_ACTION, BGRC_PACKET_P_DST_COLOR_KEY_ACTION ); \
	} \
	else \
	{ \
		BGRC_PACKET_P_STORE_REG( BLEND_COLOR_KEY_ACTION, BGRC_PACKET_P_SRC_COLOR_KEY_ACTION ); \
	} \
}
#else
#define BGRC_PACKET_P_COLOR_KEY_ACTION ( \
	(BGRC_M2MC(BLEND_COLOR_KEY_ACTION_ACTION_NOT_SRC_NOT_DEST_TAKE_ROP) << BGRC_M2MC(BLEND_COLOR_KEY_ACTION_ACTION_NOT_SRC_NOT_DEST_SHIFT)) | \
	(BGRC_M2MC(BLEND_COLOR_KEY_ACTION_ACTION_NOT_SRC_DEST_TAKE_ROP)     << BGRC_M2MC(BLEND_COLOR_KEY_ACTION_ACTION_NOT_SRC_DEST_SHIFT)) | \
	(BGRC_M2MC(BLEND_COLOR_KEY_ACTION_ACTION_SRC_NOT_DEST_TAKE_ROP)     << BGRC_M2MC(BLEND_COLOR_KEY_ACTION_ACTION_SRC_NOT_DEST_SHIFT)) | \
	(BGRC_M2MC(BLEND_COLOR_KEY_ACTION_ACTION_SRC_DEST_TAKE_ROP)         << BGRC_M2MC(BLEND_COLOR_KEY_ACTION_ACTION_SRC_DEST_SHIFT)))
#define BGRC_PACKET_P_SET_COLORKEY_ACTION() \
	BGRC_PACKET_P_STORE_REG( BLEND_COLOR_KEY_ACTION, BGRC_PACKET_P_COLOR_KEY_ACTION );
#endif

/***************************************************************************/
static void BGRC_PACKET_P_ProcSwPktBlend( BGRC_PacketContext_Handle hContext, BM2MC_PACKET_Header *header )
{
	BM2MC_PACKET_PacketBlend *packet = (BM2MC_PACKET_PacketBlend *) header;
	BGRC_PACKET_P_DEBUG_PRINT_CTX( "-- Blend              " );
	BGRC_PACKET_P_STORE_REG( BLEND_COLOR_OP, BGRC_PACKET_P_CONVERT_BLEND(packet->color_blend) );
	BGRC_PACKET_P_STORE_REG( BLEND_ALPHA_OP, BGRC_PACKET_P_CONVERT_BLEND(packet->alpha_blend) );
	BGRC_PACKET_P_STORE_REG( BLEND_CONSTANT_COLOR, packet->color );

	hContext->bNeedDestForBlend = (BGRC_PACKET_P_NEED_DEST_FOR_BLEND(packet->color_blend) ||
	                               BGRC_PACKET_P_NEED_DEST_FOR_BLEND(packet->alpha_blend));
	BGRC_PACKET_P_SET_COLORKEY_ACTION();
	BGRC_PACKET_P_DEBUG_PRINT( "\n" );
}

/***************************************************************************/
static void BGRC_PACKET_P_ProcSwPktBlendColor( BGRC_PacketContext_Handle hContext, BM2MC_PACKET_Header *header )
{
	BM2MC_PACKET_PacketBlendColor *packet = (BM2MC_PACKET_PacketBlendColor *) header;
	BGRC_PACKET_P_DEBUG_PRINT_CTX( "-- BlendColor         " );
	BGRC_PACKET_P_STORE_REG( BLEND_CONSTANT_COLOR, packet->color );
	BGRC_PACKET_P_DEBUG_PRINT( "\n" );
}

/***************************************************************************/
static void BGRC_PACKET_P_ProcSwPktRop( BGRC_PacketContext_Handle hContext, BM2MC_PACKET_Header *header )
{
	BM2MC_PACKET_PacketRop *packet = (BM2MC_PACKET_PacketRop *) header;
	BGRC_PACKET_P_DEBUG_PRINT_CTX( "-- Rop                " );
	BGRC_PACKET_P_STORE_REG( ROP_OPERATION, packet->rop );
	BGRC_PACKET_P_STORE_REG( ROP_PATTERN_TOP, packet->pattern0 );
	BGRC_PACKET_P_STORE_REG( ROP_PATTERN_BOTTOM, packet->pattern1 );
	BGRC_PACKET_P_STORE_REG( ROP_PATTERN_COLOR_0, packet->color0 );
	BGRC_PACKET_P_STORE_REG( ROP_PATTERN_COLOR_1, packet->color1 );
	BGRC_PACKET_P_DEBUG_PRINT( "\n" );
}

/***************************************************************************/
static void BGRC_PACKET_P_ProcSwPktSourceColorkey( BGRC_PacketContext_Handle hContext, BM2MC_PACKET_Header *header )
{
	BM2MC_PACKET_PacketSourceColorkey *packet = (BM2MC_PACKET_PacketSourceColorkey *) header;
	BGRC_PACKET_P_DEBUG_PRINT_CTX( "-- SrcColorkey        " );
	BGRC_PACKET_P_STORE_REG( SRC_COLOR_KEY_HIGH, packet->high );
	BGRC_PACKET_P_STORE_REG( SRC_COLOR_KEY_LOW, packet->low );
	BGRC_PACKET_P_STORE_REG( SRC_COLOR_KEY_MASK, packet->mask );
	BGRC_PACKET_P_STORE_REG( SRC_COLOR_KEY_REPLACEMENT, packet->replacement );
	BGRC_PACKET_P_STORE_REG( SRC_COLOR_KEY_REPLACEMENT_MASK, packet->replacement_mask );
	BGRC_PACKET_P_DEBUG_PRINT( "\n" );
}

/***************************************************************************/
static void BGRC_PACKET_P_ProcSwPktSourceColorkeyEnable( BGRC_PacketContext_Handle hContext, BM2MC_PACKET_Header *header )
{
	BM2MC_PACKET_PacketSourceColorkeyEnable *packet = (BM2MC_PACKET_PacketSourceColorkeyEnable *) header;
	if( packet->enable )
	{
		BGRC_PACKET_P_DEBUG_PRINT_CTX( "-- SrcColorkeyEnable  " );
		BGRC_PACKET_P_STORE_REG_FIELD( BLIT_HEADER, SRC_COLOR_KEY_ENABLE, ENABLE );
	}
	else
	{
		BGRC_PACKET_P_DEBUG_PRINT_CTX( "-- SrcColorkeyDisable " );
		BGRC_PACKET_P_STORE_REG_FIELD( BLIT_HEADER, SRC_COLOR_KEY_ENABLE, DISABLE );
	}

	BGRC_PACKET_P_SET_COLORKEY_ACTION();
	BGRC_PACKET_P_DEBUG_PRINT( "\n" );
}

/***************************************************************************/
static void BGRC_PACKET_P_ProcSwPktDestinationColorkey( BGRC_PacketContext_Handle hContext, BM2MC_PACKET_Header *header )
{
	BM2MC_PACKET_PacketDestinationColorkey *packet = (BM2MC_PACKET_PacketDestinationColorkey *) header;
	BGRC_PACKET_P_DEBUG_PRINT_CTX( "-- DstColorkey        " );
	BGRC_PACKET_P_STORE_REG( DEST_COLOR_KEY_HIGH, packet->high );
	BGRC_PACKET_P_STORE_REG( DEST_COLOR_KEY_LOW, packet->low );
	BGRC_PACKET_P_STORE_REG( DEST_COLOR_KEY_MASK, packet->mask );
	BGRC_PACKET_P_STORE_REG( DEST_COLOR_KEY_REPLACEMENT, packet->replacement );
	BGRC_PACKET_P_STORE_REG( DEST_COLOR_KEY_REPLACEMENT_MASK, packet->replacement_mask );
	BGRC_PACKET_P_DEBUG_PRINT( "\n" );
}

/***************************************************************************/
static void BGRC_PACKET_P_ProcSwPktDestinationColorkeyEnable( BGRC_PacketContext_Handle hContext, BM2MC_PACKET_Header *header )
{
	BM2MC_PACKET_PacketDestinationColorkeyEnable *packet = (BM2MC_PACKET_PacketDestinationColorkeyEnable *) header;
	if( packet->enable )
	{
		BGRC_PACKET_P_DEBUG_PRINT_CTX( "-- DstColorkeyEnable  " );
		BGRC_PACKET_P_STORE_REG_FIELD( BLIT_HEADER, DEST_COLOR_KEY_ENABLE, ENABLE );
	}
	else
	{
		BGRC_PACKET_P_DEBUG_PRINT_CTX( "-- DstColorkeyDisable " );
		BGRC_PACKET_P_STORE_REG_FIELD( BLIT_HEADER, DEST_COLOR_KEY_ENABLE, DISABLE );
	}

	BGRC_PACKET_P_SET_COLORKEY_ACTION();
	BGRC_PACKET_P_DEBUG_PRINT( "\n" );
}

#if defined(BCHP_M2MC_HORIZ_FIR_COEFF_PHASE0_2_COEFF_2_SHIFT)
/***************************************************************************/
#define BGRC_PACKET_P_CONVERT_COEFFS_1( coeff ) \
	((((uint32_t) (coeff)) << BGRC_M2MC(HORIZ_FIR_0_COEFF_PHASE0_2_COEFF_2_SHIFT)) & BGRC_M2MC(HORIZ_FIR_0_COEFF_PHASE0_2_COEFF_2_MASK))

#define BGRC_PACKET_P_CONVERT_COEFFS_2( coeff0, coeff1 ) \
	((((uint32_t) (coeff0)) << BGRC_M2MC(HORIZ_FIR_0_COEFF_PHASE0_01_COEFF_0_SHIFT)) & BGRC_M2MC(HORIZ_FIR_0_COEFF_PHASE0_01_COEFF_0_MASK)) | \
	((((uint32_t) (coeff1)) << BGRC_M2MC(HORIZ_FIR_0_COEFF_PHASE0_01_COEFF_1_SHIFT)) & BGRC_M2MC(HORIZ_FIR_0_COEFF_PHASE0_01_COEFF_1_MASK))

/***************************************************************************/
static void BGRC_PACKET_P_ProcSwPktFilter( BGRC_PacketContext_Handle hContext, BM2MC_PACKET_Header *header )
{
	/* TODO: 420 src CbCr needs diff fir coeff */
	BM2MC_PACKET_PacketFilter *packet = (BM2MC_PACKET_PacketFilter *) header;
	uint32_t hor_coeffs0 = BGRC_PACKET_P_CONVERT_COEFFS_2(packet->hor.coeffs[0][0], packet->hor.coeffs[0][1]);
	uint32_t hor_coeffs1 = BGRC_PACKET_P_CONVERT_COEFFS_1(packet->hor.coeffs[0][2]);
	uint32_t hor_coeffs2 = BGRC_PACKET_P_CONVERT_COEFFS_2(packet->hor.coeffs[1][0], packet->hor.coeffs[1][1]);
	uint32_t hor_coeffs3 = BGRC_PACKET_P_CONVERT_COEFFS_1(packet->hor.coeffs[1][2]);
	uint32_t ver_coeffs0 = BGRC_PACKET_P_CONVERT_COEFFS_2(packet->ver.coeffs[0][0], packet->ver.coeffs[0][1]);
	uint32_t ver_coeffs1 = BGRC_PACKET_P_CONVERT_COEFFS_1(packet->ver.coeffs[0][2]);
	uint32_t ver_coeffs2 = BGRC_PACKET_P_CONVERT_COEFFS_2(packet->ver.coeffs[1][0], packet->ver.coeffs[1][1]);
	uint32_t ver_coeffs3 = BGRC_PACKET_P_CONVERT_COEFFS_1(packet->ver.coeffs[1][2]);
	BGRC_PACKET_P_DEBUG_PRINT_CTX( "-- Filter             " );
	BGRC_PACKET_P_STORE_REG( HORIZ_FIR_0_COEFF_PHASE0_01, hor_coeffs0 );
	BGRC_PACKET_P_STORE_REG( HORIZ_FIR_0_COEFF_PHASE0_2,  hor_coeffs1 );
	BGRC_PACKET_P_STORE_REG( HORIZ_FIR_0_COEFF_PHASE1_01, hor_coeffs2 );
	BGRC_PACKET_P_STORE_REG( HORIZ_FIR_0_COEFF_PHASE1_2,  hor_coeffs3 );
	BGRC_PACKET_P_STORE_REG( HORIZ_FIR_1_COEFF_PHASE0_01, hor_coeffs0 );
	BGRC_PACKET_P_STORE_REG( HORIZ_FIR_1_COEFF_PHASE0_2,  hor_coeffs1 );
	BGRC_PACKET_P_STORE_REG( HORIZ_FIR_1_COEFF_PHASE1_01, hor_coeffs2 );
	BGRC_PACKET_P_STORE_REG( HORIZ_FIR_1_COEFF_PHASE1_2,  hor_coeffs3 );
	BGRC_PACKET_P_STORE_REG( VERT_FIR_0_COEFF_PHASE0_01, ver_coeffs0 );
	BGRC_PACKET_P_STORE_REG( VERT_FIR_0_COEFF_PHASE0_2,  ver_coeffs1 );
	BGRC_PACKET_P_STORE_REG( VERT_FIR_0_COEFF_PHASE1_01, ver_coeffs2 );
	BGRC_PACKET_P_STORE_REG( VERT_FIR_0_COEFF_PHASE1_2,  ver_coeffs3 );
	BGRC_PACKET_P_STORE_REG( VERT_FIR_1_COEFF_PHASE0_01, ver_coeffs0 );
	BGRC_PACKET_P_STORE_REG( VERT_FIR_1_COEFF_PHASE0_2,  ver_coeffs1 );
	BGRC_PACKET_P_STORE_REG( VERT_FIR_1_COEFF_PHASE1_01, ver_coeffs2 );
	BGRC_PACKET_P_STORE_REG( VERT_FIR_1_COEFF_PHASE1_2,  ver_coeffs3 );
	BGRC_PACKET_P_DEBUG_PRINT( "\n" );
}
#else
/***************************************************************************/
#define BGRC_PACKET_P_CONVERT_COEFFS( coeff0, coeff1 ) \
	(((uint32_t) (coeff0) << 16) & BGRC_M2MC(HORIZ_FIR_COEFF_PHASE0_01_COEFF_0_MASK)) | \
	(((uint32_t) (coeff1)) & BGRC_M2MC(HORIZ_FIR_COEFF_PHASE0_01_COEFF_1_MASK))

/***************************************************************************/
static void BGRC_PACKET_P_ProcSwPktFilter( BGRC_PacketContext_Handle hContext, BM2MC_PACKET_Header *header )
{
	BM2MC_PACKET_PacketFilter *packet = (BM2MC_PACKET_PacketFilter *) header;
	BGRC_PACKET_P_DEBUG_PRINT_CTX( "-- Filter             " );
	BGRC_PACKET_P_STORE_REG( HORIZ_FIR_COEFF_PHASE0_01, BGRC_PACKET_P_CONVERT_COEFFS(packet->hor.coeffs[0][0], packet->hor.coeffs[0][1]) );
	BGRC_PACKET_P_STORE_REG( HORIZ_FIR_COEFF_PHASE0_23, BGRC_PACKET_P_CONVERT_COEFFS(packet->hor.coeffs[0][2], packet->hor.coeffs[0][3]) );
	BGRC_PACKET_P_STORE_REG( HORIZ_FIR_COEFF_PHASE0_45, BGRC_PACKET_P_CONVERT_COEFFS(packet->hor.coeffs[0][4], packet->hor.coeffs[0][5]) );
	BGRC_PACKET_P_STORE_REG( HORIZ_FIR_COEFF_PHASE0_67, BGRC_PACKET_P_CONVERT_COEFFS(packet->hor.coeffs[0][6], packet->hor.coeffs[0][7]) );
	BGRC_PACKET_P_STORE_REG( HORIZ_FIR_COEFF_PHASE1_01, BGRC_PACKET_P_CONVERT_COEFFS(packet->hor.coeffs[1][0], packet->hor.coeffs[1][1]) );
	BGRC_PACKET_P_STORE_REG( HORIZ_FIR_COEFF_PHASE1_23, BGRC_PACKET_P_CONVERT_COEFFS(packet->hor.coeffs[1][2], packet->hor.coeffs[1][3]) );
	BGRC_PACKET_P_STORE_REG( HORIZ_FIR_COEFF_PHASE1_45, BGRC_PACKET_P_CONVERT_COEFFS(packet->hor.coeffs[1][4], packet->hor.coeffs[1][5]) );
	BGRC_PACKET_P_STORE_REG( HORIZ_FIR_COEFF_PHASE1_67, BGRC_PACKET_P_CONVERT_COEFFS(packet->hor.coeffs[1][6], packet->hor.coeffs[1][7]) );
	BGRC_PACKET_P_STORE_REG( HORIZ_FIR_COEFF_PHASE2_01, BGRC_PACKET_P_CONVERT_COEFFS(packet->hor.coeffs[2][0], packet->hor.coeffs[2][1]) );
	BGRC_PACKET_P_STORE_REG( HORIZ_FIR_COEFF_PHASE2_23, BGRC_PACKET_P_CONVERT_COEFFS(packet->hor.coeffs[2][2], packet->hor.coeffs[2][3]) );
	BGRC_PACKET_P_STORE_REG( HORIZ_FIR_COEFF_PHASE2_45, BGRC_PACKET_P_CONVERT_COEFFS(packet->hor.coeffs[2][4], packet->hor.coeffs[2][5]) );
	BGRC_PACKET_P_STORE_REG( HORIZ_FIR_COEFF_PHASE2_67, BGRC_PACKET_P_CONVERT_COEFFS(packet->hor.coeffs[2][6], packet->hor.coeffs[2][7]) );
	BGRC_PACKET_P_STORE_REG( HORIZ_FIR_COEFF_PHASE3_01, BGRC_PACKET_P_CONVERT_COEFFS(packet->hor.coeffs[3][0], packet->hor.coeffs[3][1]) );
	BGRC_PACKET_P_STORE_REG( HORIZ_FIR_COEFF_PHASE3_23, BGRC_PACKET_P_CONVERT_COEFFS(packet->hor.coeffs[3][2], packet->hor.coeffs[3][3]) );
	BGRC_PACKET_P_STORE_REG( HORIZ_FIR_COEFF_PHASE3_45, BGRC_PACKET_P_CONVERT_COEFFS(packet->hor.coeffs[3][4], packet->hor.coeffs[3][5]) );
	BGRC_PACKET_P_STORE_REG( HORIZ_FIR_COEFF_PHASE3_67, BGRC_PACKET_P_CONVERT_COEFFS(packet->hor.coeffs[3][6], packet->hor.coeffs[3][7]) );
	BGRC_PACKET_P_STORE_REG( HORIZ_FIR_COEFF_PHASE4_01, BGRC_PACKET_P_CONVERT_COEFFS(packet->hor.coeffs[4][0], packet->hor.coeffs[4][1]) );
	BGRC_PACKET_P_STORE_REG( HORIZ_FIR_COEFF_PHASE4_23, BGRC_PACKET_P_CONVERT_COEFFS(packet->hor.coeffs[4][2], packet->hor.coeffs[4][3]) );
	BGRC_PACKET_P_STORE_REG( HORIZ_FIR_COEFF_PHASE4_45, BGRC_PACKET_P_CONVERT_COEFFS(packet->hor.coeffs[4][4], packet->hor.coeffs[4][5]) );
	BGRC_PACKET_P_STORE_REG( HORIZ_FIR_COEFF_PHASE4_67, BGRC_PACKET_P_CONVERT_COEFFS(packet->hor.coeffs[4][6], packet->hor.coeffs[4][7]) );
	BGRC_PACKET_P_STORE_REG( HORIZ_FIR_COEFF_PHASE5_01, BGRC_PACKET_P_CONVERT_COEFFS(packet->hor.coeffs[5][0], packet->hor.coeffs[5][1]) );
	BGRC_PACKET_P_STORE_REG( HORIZ_FIR_COEFF_PHASE5_23, BGRC_PACKET_P_CONVERT_COEFFS(packet->hor.coeffs[5][2], packet->hor.coeffs[5][3]) );
	BGRC_PACKET_P_STORE_REG( HORIZ_FIR_COEFF_PHASE5_45, BGRC_PACKET_P_CONVERT_COEFFS(packet->hor.coeffs[5][4], packet->hor.coeffs[5][5]) );
	BGRC_PACKET_P_STORE_REG( HORIZ_FIR_COEFF_PHASE5_67, BGRC_PACKET_P_CONVERT_COEFFS(packet->hor.coeffs[5][6], packet->hor.coeffs[5][7]) );
	BGRC_PACKET_P_STORE_REG( HORIZ_FIR_COEFF_PHASE6_01, BGRC_PACKET_P_CONVERT_COEFFS(packet->hor.coeffs[6][0], packet->hor.coeffs[6][1]) );
	BGRC_PACKET_P_STORE_REG( HORIZ_FIR_COEFF_PHASE6_23, BGRC_PACKET_P_CONVERT_COEFFS(packet->hor.coeffs[6][2], packet->hor.coeffs[6][3]) );
	BGRC_PACKET_P_STORE_REG( HORIZ_FIR_COEFF_PHASE6_45, BGRC_PACKET_P_CONVERT_COEFFS(packet->hor.coeffs[6][4], packet->hor.coeffs[6][5]) );
	BGRC_PACKET_P_STORE_REG( HORIZ_FIR_COEFF_PHASE6_67, BGRC_PACKET_P_CONVERT_COEFFS(packet->hor.coeffs[6][6], packet->hor.coeffs[6][7]) );
	BGRC_PACKET_P_STORE_REG( HORIZ_FIR_COEFF_PHASE7_01, BGRC_PACKET_P_CONVERT_COEFFS(packet->hor.coeffs[7][0], packet->hor.coeffs[7][1]) );
	BGRC_PACKET_P_STORE_REG( HORIZ_FIR_COEFF_PHASE7_23, BGRC_PACKET_P_CONVERT_COEFFS(packet->hor.coeffs[7][2], packet->hor.coeffs[7][3]) );
	BGRC_PACKET_P_STORE_REG( HORIZ_FIR_COEFF_PHASE7_45, BGRC_PACKET_P_CONVERT_COEFFS(packet->hor.coeffs[7][4], packet->hor.coeffs[7][5]) );
	BGRC_PACKET_P_STORE_REG( HORIZ_FIR_COEFF_PHASE7_67, BGRC_PACKET_P_CONVERT_COEFFS(packet->hor.coeffs[7][6], packet->hor.coeffs[7][7]) );

	BGRC_PACKET_P_STORE_REG( VERT_FIR_COEFF_PHASE0_01, BGRC_PACKET_P_CONVERT_COEFFS(packet->ver.coeffs[0][0], packet->ver.coeffs[0][1]) );
	BGRC_PACKET_P_STORE_REG( VERT_FIR_COEFF_PHASE0_23, BGRC_PACKET_P_CONVERT_COEFFS(packet->ver.coeffs[0][2], packet->ver.coeffs[0][3]) );
	BGRC_PACKET_P_STORE_REG( VERT_FIR_COEFF_PHASE0_45, BGRC_PACKET_P_CONVERT_COEFFS(packet->ver.coeffs[0][4], packet->ver.coeffs[0][5]) );
	BGRC_PACKET_P_STORE_REG( VERT_FIR_COEFF_PHASE0_67, BGRC_PACKET_P_CONVERT_COEFFS(packet->ver.coeffs[0][6], packet->ver.coeffs[0][7]) );
	BGRC_PACKET_P_STORE_REG( VERT_FIR_COEFF_PHASE1_01, BGRC_PACKET_P_CONVERT_COEFFS(packet->ver.coeffs[1][0], packet->ver.coeffs[1][1]) );
	BGRC_PACKET_P_STORE_REG( VERT_FIR_COEFF_PHASE1_23, BGRC_PACKET_P_CONVERT_COEFFS(packet->ver.coeffs[1][2], packet->ver.coeffs[1][3]) );
	BGRC_PACKET_P_STORE_REG( VERT_FIR_COEFF_PHASE1_45, BGRC_PACKET_P_CONVERT_COEFFS(packet->ver.coeffs[1][4], packet->ver.coeffs[1][5]) );
	BGRC_PACKET_P_STORE_REG( VERT_FIR_COEFF_PHASE1_67, BGRC_PACKET_P_CONVERT_COEFFS(packet->ver.coeffs[1][6], packet->ver.coeffs[1][7]) );
	BGRC_PACKET_P_STORE_REG( VERT_FIR_COEFF_PHASE2_01, BGRC_PACKET_P_CONVERT_COEFFS(packet->ver.coeffs[2][0], packet->ver.coeffs[2][1]) );
	BGRC_PACKET_P_STORE_REG( VERT_FIR_COEFF_PHASE2_23, BGRC_PACKET_P_CONVERT_COEFFS(packet->ver.coeffs[2][2], packet->ver.coeffs[2][3]) );
	BGRC_PACKET_P_STORE_REG( VERT_FIR_COEFF_PHASE2_45, BGRC_PACKET_P_CONVERT_COEFFS(packet->ver.coeffs[2][4], packet->ver.coeffs[2][5]) );
	BGRC_PACKET_P_STORE_REG( VERT_FIR_COEFF_PHASE2_67, BGRC_PACKET_P_CONVERT_COEFFS(packet->ver.coeffs[2][6], packet->ver.coeffs[2][7]) );
	BGRC_PACKET_P_STORE_REG( VERT_FIR_COEFF_PHASE3_01, BGRC_PACKET_P_CONVERT_COEFFS(packet->ver.coeffs[3][0], packet->ver.coeffs[3][1]) );
	BGRC_PACKET_P_STORE_REG( VERT_FIR_COEFF_PHASE3_23, BGRC_PACKET_P_CONVERT_COEFFS(packet->ver.coeffs[3][2], packet->ver.coeffs[3][3]) );
	BGRC_PACKET_P_STORE_REG( VERT_FIR_COEFF_PHASE3_45, BGRC_PACKET_P_CONVERT_COEFFS(packet->ver.coeffs[3][4], packet->ver.coeffs[3][5]) );
	BGRC_PACKET_P_STORE_REG( VERT_FIR_COEFF_PHASE3_67, BGRC_PACKET_P_CONVERT_COEFFS(packet->ver.coeffs[3][6], packet->ver.coeffs[3][7]) );
	BGRC_PACKET_P_STORE_REG( VERT_FIR_COEFF_PHASE4_01, BGRC_PACKET_P_CONVERT_COEFFS(packet->ver.coeffs[4][0], packet->ver.coeffs[4][1]) );
	BGRC_PACKET_P_STORE_REG( VERT_FIR_COEFF_PHASE4_23, BGRC_PACKET_P_CONVERT_COEFFS(packet->ver.coeffs[4][2], packet->ver.coeffs[4][3]) );
	BGRC_PACKET_P_STORE_REG( VERT_FIR_COEFF_PHASE4_45, BGRC_PACKET_P_CONVERT_COEFFS(packet->ver.coeffs[4][4], packet->ver.coeffs[4][5]) );
	BGRC_PACKET_P_STORE_REG( VERT_FIR_COEFF_PHASE4_67, BGRC_PACKET_P_CONVERT_COEFFS(packet->ver.coeffs[4][6], packet->ver.coeffs[4][7]) );
	BGRC_PACKET_P_STORE_REG( VERT_FIR_COEFF_PHASE5_01, BGRC_PACKET_P_CONVERT_COEFFS(packet->ver.coeffs[5][0], packet->ver.coeffs[5][1]) );
	BGRC_PACKET_P_STORE_REG( VERT_FIR_COEFF_PHASE5_23, BGRC_PACKET_P_CONVERT_COEFFS(packet->ver.coeffs[5][2], packet->ver.coeffs[5][3]) );
	BGRC_PACKET_P_STORE_REG( VERT_FIR_COEFF_PHASE5_45, BGRC_PACKET_P_CONVERT_COEFFS(packet->ver.coeffs[5][4], packet->ver.coeffs[5][5]) );
	BGRC_PACKET_P_STORE_REG( VERT_FIR_COEFF_PHASE5_67, BGRC_PACKET_P_CONVERT_COEFFS(packet->ver.coeffs[5][6], packet->ver.coeffs[5][7]) );
	BGRC_PACKET_P_STORE_REG( VERT_FIR_COEFF_PHASE6_01, BGRC_PACKET_P_CONVERT_COEFFS(packet->ver.coeffs[6][0], packet->ver.coeffs[6][1]) );
	BGRC_PACKET_P_STORE_REG( VERT_FIR_COEFF_PHASE6_23, BGRC_PACKET_P_CONVERT_COEFFS(packet->ver.coeffs[6][2], packet->ver.coeffs[6][3]) );
	BGRC_PACKET_P_STORE_REG( VERT_FIR_COEFF_PHASE6_45, BGRC_PACKET_P_CONVERT_COEFFS(packet->ver.coeffs[6][4], packet->ver.coeffs[6][5]) );
	BGRC_PACKET_P_STORE_REG( VERT_FIR_COEFF_PHASE6_67, BGRC_PACKET_P_CONVERT_COEFFS(packet->ver.coeffs[6][6], packet->ver.coeffs[6][7]) );
	BGRC_PACKET_P_STORE_REG( VERT_FIR_COEFF_PHASE7_01, BGRC_PACKET_P_CONVERT_COEFFS(packet->ver.coeffs[7][0], packet->ver.coeffs[7][1]) );
	BGRC_PACKET_P_STORE_REG( VERT_FIR_COEFF_PHASE7_23, BGRC_PACKET_P_CONVERT_COEFFS(packet->ver.coeffs[7][2], packet->ver.coeffs[7][3]) );
	BGRC_PACKET_P_STORE_REG( VERT_FIR_COEFF_PHASE7_45, BGRC_PACKET_P_CONVERT_COEFFS(packet->ver.coeffs[7][4], packet->ver.coeffs[7][5]) );
	BGRC_PACKET_P_STORE_REG( VERT_FIR_COEFF_PHASE7_67, BGRC_PACKET_P_CONVERT_COEFFS(packet->ver.coeffs[7][6], packet->ver.coeffs[7][7]) );
	BGRC_PACKET_P_DEBUG_PRINT( "\n" );
}
#endif

/***************************************************************************/
static void BGRC_PACKET_P_ProcSwPktFilterEnable( BGRC_PacketContext_Handle hContext, BM2MC_PACKET_Header *header )
{
#if 0
	BSTD_UNUSED(hContext);
	BSTD_UNUSED(header);
#else
	/* Theoretically filter-enable should not affect CLUT_SCALE_MODE setting, but without it
	 * Android tests show that gfx is vertically filtered even with point-sampling. We program this
	 * way until we know why and have a solution */
	BM2MC_PACKET_PacketFilterEnable *packet = (BM2MC_PACKET_PacketFilterEnable *) header;
	if( packet->enable )
	{
		BGRC_PACKET_P_DEBUG_PRINT_CTX( "-- FilterEnable       \n" );
		BGRC_PACKET_P_STORE_REG_FIELD( SCALER_CTRL, CLUT_SCALE_MODE, DISABLE );
	}
	else
	{
		BGRC_PACKET_P_DEBUG_PRINT_CTX( "-- FilterDisable      \n" );
		BGRC_PACKET_P_STORE_REG_FIELD( SCALER_CTRL, CLUT_SCALE_MODE, ENABLE );
	}
#endif
}

/***************************************************************************/
static void BGRC_PACKET_P_ProcSwPktFilterControl( BGRC_PacketContext_Handle hContext, BM2MC_PACKET_Header *header )
{
	BM2MC_PACKET_PacketFilterControl *packet = (BM2MC_PACKET_PacketFilterControl *) header;
	BSTD_UNUSED(hContext);

	BGRC_PACKET_P_DEBUG_PRINT_CTX( "-- FilterControl\n" );
	BGRC_PACKET_P_STORE_REG_FIELD_COMP( SCALER_CTRL, ROUNDING_MODE, TRUNCATE, NEAREST, packet->round );

#if defined(BCHP_M2MC_SCALER_CTRL_ALPHA_PRE_MULTIPLY_OFFSET_EN_MASK)
	BGRC_PACKET_P_STORE_REG_FIELD_COMP( SCALER_CTRL, ALPHA_PRE_MULTIPLY_OFFSET_EN, DISABLE, ENABLE, packet->adjust_color );
#endif

#if defined(BCHP_M2MC_SCALER_CTRL_OFFSET_ADJUST_MASK)
	BGRC_PACKET_P_STORE_REG_FIELD_COMP( SCALER_CTRL, OFFSET_ADJUST, DISABLE, ENABLE, packet->sub_alpha );
#endif

#if defined(BCHP_M2MC_BLIT_HEADER_CBAR_SRC_COLOR_MASK)
	BGRC_PACKET_P_STORE_REG_FIELD_DATA( BLIT_HEADER, CBAR_SRC_COLOR, packet->order );
#endif

#if defined(BCHP_M2MC_BLIT_CTRL_DEST_ALPHA_PRE_MULTIPLY_OFFSET_EN_MASK)
	BGRC_PACKET_P_STORE_REG_FIELD_COMP( BLIT_CTRL, DEST_ALPHA_PRE_MULTIPLY_OFFSET_EN, DISABLE, ENABLE, packet->adjust_color );
#endif

#if defined(BCHP_M2MC_BLIT_CTRL_DEST_CBAR_SELECT_MASK)
	BGRC_PACKET_P_STORE_REG_FIELD_COMP( BLIT_CTRL, DEST_CBAR_SELECT, CKEY_THEN_ALPHA_PREMULT, ALPHA_PREMULT_THEN_CKEY, \
		packet->order==BM2MC_PACKET_eFilterOrder_FilterColorkeyMatrix || packet->order==BM2MC_PACKET_eFilterOrder_FilterMatrixColorkey || \
		packet->order==BM2MC_PACKET_eFilterOrder_MatrixFilterColorkey );
#endif
}

/***************************************************************************/
static void BGRC_PACKET_P_ProcSwPktSourceColorMatrix( BGRC_PacketContext_Handle hContext, BM2MC_PACKET_Header *header )
{
	BM2MC_PACKET_PacketSourceColorMatrix *packet = (BM2MC_PACKET_PacketSourceColorMatrix *) header;
	BGRC_PACKET_P_DEBUG_PRINT_CTX( "-- ColorMatrix        " );
	BGRC_PACKET_P_STORE_REG( SRC_CM_C00_C01, packet->matrix.m[0][1] | (packet->matrix.m[0][0] << BGRC_M2MC(SRC_CM_C00_C01_CM_C00_SHIFT)) );
	BGRC_PACKET_P_STORE_REG( SRC_CM_C02_C03, packet->matrix.m[0][3] | (packet->matrix.m[0][2] << BGRC_M2MC(SRC_CM_C02_C03_CM_C02_SHIFT)) );
	BGRC_PACKET_P_STORE_REG( SRC_CM_C04,     packet->matrix.m[0][4] );
	BGRC_PACKET_P_STORE_REG( SRC_CM_C10_C11, packet->matrix.m[1][1] | (packet->matrix.m[1][0] << BGRC_M2MC(SRC_CM_C10_C11_CM_C10_SHIFT)) );
	BGRC_PACKET_P_STORE_REG( SRC_CM_C12_C13, packet->matrix.m[1][3] | (packet->matrix.m[1][2] << BGRC_M2MC(SRC_CM_C12_C13_CM_C12_SHIFT)) );
	BGRC_PACKET_P_STORE_REG( SRC_CM_C14,     packet->matrix.m[1][4] );
	BGRC_PACKET_P_STORE_REG( SRC_CM_C20_C21, packet->matrix.m[2][1] | (packet->matrix.m[2][0] << BGRC_M2MC(SRC_CM_C20_C21_CM_C20_SHIFT)) );
	BGRC_PACKET_P_STORE_REG( SRC_CM_C22_C23, packet->matrix.m[2][3] | (packet->matrix.m[2][2] << BGRC_M2MC(SRC_CM_C22_C23_CM_C22_SHIFT)) );
	BGRC_PACKET_P_STORE_REG( SRC_CM_C24,     packet->matrix.m[2][4] );
	BGRC_PACKET_P_STORE_REG( SRC_CM_C30_C31, packet->matrix.m[3][1] | (packet->matrix.m[3][0] << BGRC_M2MC(SRC_CM_C30_C31_CM_C30_SHIFT)) );
	BGRC_PACKET_P_STORE_REG( SRC_CM_C32_C33, packet->matrix.m[3][3] | (packet->matrix.m[3][2] << BGRC_M2MC(SRC_CM_C32_C33_CM_C32_SHIFT)) );
	BGRC_PACKET_P_STORE_REG( SRC_CM_C34,     packet->matrix.m[3][4] );
	BGRC_PACKET_P_DEBUG_PRINT( "\n" );
}

/***************************************************************************/
static void BGRC_PACKET_P_ProcSwPktSourceColorMatrixEnable( BGRC_PacketContext_Handle hContext, BM2MC_PACKET_Header *header )
{
	BM2MC_PACKET_PacketSourceColorMatrixEnable *packet = (BM2MC_PACKET_PacketSourceColorMatrixEnable *) header;
	if( packet->enable )
	{
		BGRC_PACKET_P_DEBUG_PRINT_CTX( "-- ColorMatrixEnable  \n" );
		BGRC_PACKET_P_STORE_REG_FIELD( BLIT_HEADER, SRC_COLOR_MATRIX_ENABLE, ENABLE );
	}
	else
	{
		BGRC_PACKET_P_DEBUG_PRINT_CTX( "-- ColorMatrixDisable \n" );
		BGRC_PACKET_P_STORE_REG_FIELD( BLIT_HEADER, SRC_COLOR_MATRIX_ENABLE, DISABLE );
	}
}

/***************************************************************************/
static void BGRC_PACKET_P_ProcSwPktSourcePalette( BGRC_PacketContext_Handle hContext, BM2MC_PACKET_Header *header )
{
	BM2MC_PACKET_PacketSourcePalette *packet = (BM2MC_PACKET_PacketSourcePalette *) header;
#if (BCHP_CHIP==7420)
	if( packet->address >= 0x60000000 )
		BDBG_ERR(("7420 M2MC cannot access palette on MEMC1"));
#endif

	if (packet->address)
	{
		BGRC_PACKET_P_DEBUG_PRINT_CTX( "-- Palette            " );
		BGRC_PACKET_P_STORE_REG( SRC_CLUT_ENTRY_i_ARRAY_BASE, packet->address );
		hContext->ulGroupMask |= BCHP_M2MC_LIST_PACKET_HEADER_1_SRC_CLUT_GRP_CNTRL_MASK;
		BGRC_PACKET_P_DEBUG_PRINT( "\n" );
	}
}

/***************************************************************************/
static void BGRC_PACKET_P_ProcSwPktMirror( BGRC_PacketContext_Handle hContext, BM2MC_PACKET_Header *header )
{
	BM2MC_PACKET_PacketMirror *packet = (BM2MC_PACKET_PacketMirror *) header;
	BGRC_PACKET_P_DEBUG_PRINT_CTX( "-- Mirror             " );
	BGRC_PACKET_P_STORE_REG_FIELD_COMP( BLIT_CTRL, SRC_H_DIRECTION, LEFT_TO_RIGHT, RIGHT_TO_LEFT, packet->src_hor );
	BGRC_PACKET_P_STORE_REG_FIELD_COMP( BLIT_CTRL, SRC_V_DIRECTION, TOP_TO_BOTTOM, BOTTOM_TO_TOP, packet->src_ver );
	BGRC_PACKET_P_STORE_REG_FIELD_COMP( BLIT_CTRL, DEST_H_DIRECTION, LEFT_TO_RIGHT, RIGHT_TO_LEFT, packet->dst_hor );
	BGRC_PACKET_P_STORE_REG_FIELD_COMP( BLIT_CTRL, DEST_V_DIRECTION, TOP_TO_BOTTOM, BOTTOM_TO_TOP, packet->dst_ver );
	BGRC_PACKET_P_STORE_REG_FIELD_COMP( BLIT_CTRL, OUTPUT_H_DIRECTION, LEFT_TO_RIGHT, RIGHT_TO_LEFT, packet->out_hor );
	BGRC_PACKET_P_STORE_REG_FIELD_COMP( BLIT_CTRL, OUTPUT_V_DIRECTION, TOP_TO_BOTTOM, BOTTOM_TO_TOP, packet->out_ver );
	BGRC_PACKET_P_DEBUG_PRINT( "\n" );
}

/***************************************************************************/
static void BGRC_PACKET_P_ProcSwPktFixedScale( BGRC_PacketContext_Handle hContext, BM2MC_PACKET_Header *header )
{
	BM2MC_PACKET_PacketFixedScale *packet = (BM2MC_PACKET_PacketFixedScale *) header;
	BGRC_PACKET_P_DEBUG_PRINT_CTX( "-- FixedScale         " );
	BGRC_PACKET_P_DEBUG_PRINT_VALUE( packet->hor_phase );
	BGRC_PACKET_P_DEBUG_PRINT_VALUE( packet->ver_phase );
	BGRC_PACKET_P_DEBUG_PRINT_VALUE( packet->hor_step );
	BGRC_PACKET_P_DEBUG_PRINT_VALUE( packet->ver_step );
	BGRC_PACKET_P_DEBUG_PRINT_VALUE( packet->shift );
	hContext->fixed_scale = *packet;
	BGRC_PACKET_P_DEBUG_PRINT( "\n" );
}

/***************************************************************************/
static void BGRC_PACKET_P_ProcSwPktDestripeFixedScale( BGRC_PacketContext_Handle hContext, BM2MC_PACKET_Header *header )
{
	BM2MC_PACKET_PacketDestripeFixedScale *packet = (BM2MC_PACKET_PacketDestripeFixedScale *) header;
	BGRC_PACKET_P_DEBUG_PRINT_CTX( "-- DestripeFixedScale         " );
	hContext->destripe_fixed_scale = *packet;
	BGRC_PACKET_P_DEBUG_PRINT( "\n" );
}

/***************************************************************************/
static void BGRC_PACKET_P_ProcSwPktAlphaPremultiply( BGRC_PacketContext_Handle hContext, BM2MC_PACKET_Header *header )
{
	BM2MC_PACKET_PacketAlphaPremultiply *packet = (BM2MC_PACKET_PacketAlphaPremultiply *) header;
	if( packet->enable )
	{
		BGRC_PACKET_P_DEBUG_PRINT_CTX( "-- AlphaPremulEnable  \n" );
		BGRC_PACKET_P_STORE_REG_FIELD( SCALER_CTRL, ALPHA_PRE_MULTIPLY_ENABLE, ENABLE );
	}
	else
	{
		BGRC_PACKET_P_DEBUG_PRINT_CTX( "-- AlphaPremulDisable \n" );
		BGRC_PACKET_P_STORE_REG_FIELD( SCALER_CTRL, ALPHA_PRE_MULTIPLY_ENABLE, DISABLE );
	}
}

/***************************************************************************/
static void BGRC_PACKET_P_ProcSwPktAlphaDemultiply( BGRC_PacketContext_Handle hContext, BM2MC_PACKET_Header *header )
{
#if defined(BCHP_M2MC_BLIT_CTRL_ALPHA_DE_MULTIPLY_ENABLE_MASK)
	BM2MC_PACKET_PacketAlphaPremultiply *packet = (BM2MC_PACKET_PacketAlphaPremultiply *) header;
	if( packet->enable )
	{
		BGRC_PACKET_P_DEBUG_PRINT_CTX( "-- AlphaDemulEnable   \n" );
		BGRC_PACKET_P_STORE_REG_FIELD( BLIT_CTRL, ALPHA_DE_MULTIPLY_ENABLE, ENABLE );
	}
	else
	{
		BGRC_PACKET_P_DEBUG_PRINT_CTX( "-- AlphaDemulDisable  \n" );
		BGRC_PACKET_P_STORE_REG_FIELD( BLIT_CTRL, ALPHA_DE_MULTIPLY_ENABLE, DISABLE );
	}
#else
	BSTD_UNUSED(hContext);
	BSTD_UNUSED(header);
#endif
}

/***************************************************************************/
static void BGRC_PACKET_P_ProcSwPktDestAlphaPremultiply( BGRC_PacketContext_Handle hContext, BM2MC_PACKET_Header *header )
{
#if defined(BCHP_M2MC_BLIT_CTRL_DEST_ALPHA_PRE_MULTIPLY_ENABLE_MASK)
	BM2MC_PACKET_PacketAlphaPremultiply *packet = (BM2MC_PACKET_PacketAlphaPremultiply *) header;
	if( packet->enable )
	{
		BGRC_PACKET_P_DEBUG_PRINT_CTX( "-- DestAlphaPreEnable \n" );
		BGRC_PACKET_P_STORE_REG_FIELD( BLIT_CTRL, DEST_ALPHA_PRE_MULTIPLY_ENABLE, ENABLE );
	}
	else
	{
		BGRC_PACKET_P_DEBUG_PRINT_CTX( "-- DestAlphaPreDisable\n" );
		BGRC_PACKET_P_STORE_REG_FIELD( BLIT_CTRL, DEST_ALPHA_PRE_MULTIPLY_ENABLE, DISABLE );
	}
#else
	BSTD_UNUSED(hContext);
	BSTD_UNUSED(header);
#endif
}

/***************************************************************************/
static void BGRC_PACKET_P_CheckAndForceDestDisable( BGRC_PacketContext_Handle hContext )
{
	if ( BGRC_PACKET_P_GET_REG( DEST_FEEDER_ENABLE ) )
	{
		if (!hContext->bNeedDestForBlend &&
		    !BGRC_PACKET_P_GET_REG_FIELD(BLIT_HEADER, SRC_COLOR_KEY_ENABLE) &&
		    !BGRC_PACKET_P_GET_REG_FIELD(BLIT_HEADER, DEST_COLOR_KEY_ENABLE))
		{
			/* both blend and color key do NOT need dest, force to disable it */
			BGRC_PACKET_P_STORE_REG( DEST_FEEDER_ENABLE, 0 );
			hContext->ulGroupMask |= BCHP_M2MC_LIST_PACKET_HEADER_1_DST_FEEDER_GRP_CNTRL_MASK;
			hContext->bDestForceDisabled = true;
			BGRC_P_FORCEDSTDISABLE_MSG(("force to disable dest"));
		}
	}
	else
	{
		if (hContext->bNeedDestForBlend ||
		    BGRC_PACKET_P_GET_REG_FIELD(BLIT_HEADER, SRC_COLOR_KEY_ENABLE) ||
		    BGRC_PACKET_P_GET_REG_FIELD(BLIT_HEADER, DEST_COLOR_KEY_ENABLE))
		{
			if (hContext->bDestForceDisabled)
			{
				BGRC_PACKET_P_STORE_REG( DEST_FEEDER_ENABLE, 1 );
				hContext->ulGroupMask |= BCHP_M2MC_LIST_PACKET_HEADER_1_DST_FEEDER_GRP_CNTRL_MASK;
				hContext->bDestForceDisabled = false;
				BGRC_P_FORCEDSTDISABLE_MSG(("recover dest en"));
			}
#if BGRC_PACKET_P_DEBUG_FORCEDSTDISABLE
			else
			{
				BDBG_ERR(("Dest is NOT set, but needed for %s", hContext->bNeedDestForBlend? "blend" : "color key"));
			}
#endif
		}
	}
}

#ifdef BCHP_M2MC_DCEG_CFG
static void BGRC_PACKET_P_SetDcegCompression( BGRC_PacketContext_Handle hContext )
{
	/* note: OUTPUT_SURFACE_FORMAT_DEF_1_FORMAT_TYPE_MASK = 0x7, not enough to keep M2MC_FT_CompressedARGB8888 */
	if ((hContext->out_format0 & 0x00FF0000) == M2MC_FT_CompressedARGB8888)
	{
		/* this chip uses M2MC_DCEG_CFG.ENABLE, not OUTPUT_SURFACE_FORMAT_DEF_1.FORMAT_TYPE */
		BGRC_PACKET_P_STORE_REG_FIELD_DATA( OUTPUT_SURFACE_FORMAT_DEF_1, FORMAT_TYPE, M2MC_FT_Default );
		if (BGRC_PACKET_P_GET_REG_FIELD(BLIT_HEADER, SRC_SCALER_ENABLE))
		{
			hContext->bBlitInvalid = true;
			BGRC_PACKET_P_STORE_REG( DCEG_CFG, 0 );
			BDBG_ERR(("This chip can not compress output with scale (%d, %d)->(%d, %d), blit dropped",
				BGRC_PACKET_P_GET_REG_FIELD_SHIFT(BLIT_SRC_SIZE, SURFACE_WIDTH),
				BGRC_PACKET_P_GET_REG_FIELD_SHIFT(BLIT_SRC_SIZE, SURFACE_HEIGHT),
				BGRC_PACKET_P_GET_REG_FIELD_SHIFT(BLIT_OUTPUT_SIZE, SURFACE_WIDTH),
				BGRC_PACKET_P_GET_REG_FIELD_SHIFT(BLIT_OUTPUT_SIZE, SURFACE_HEIGHT)));
		}
		else
		{
			/* really enable output compression */
			BGRC_PACKET_P_STORE_REG( DCEG_CFG,
				BCHP_FIELD_ENUM(M2MC_DCEG_CFG, ENABLE, Enable) |
				BCHP_FIELD_ENUM(M2MC_DCEG_CFG, APPLY_QERR, Apply_Qerr ) |
				BCHP_FIELD_ENUM(M2MC_DCEG_CFG, FIXED_RATE, Fixed ) |
				BCHP_FIELD_ENUM(M2MC_DCEG_CFG, COMPRESSION, BPP_16p5 ) );
			/* to avoid confusion during debug */
			BGRC_PACKET_P_STORE_REG( BLIT_INPUT_STRIPE_WIDTH_0, 0);
			BGRC_PACKET_P_STORE_REG( BLIT_INPUT_STRIPE_WIDTH_1, 0);
			BGRC_PACKET_P_STORE_REG( BLIT_OUTPUT_STRIPE_WIDTH, 0);
			BGRC_PACKET_P_STORE_REG( BLIT_STRIPE_OVERLAP_0, 0);
			BGRC_PACKET_P_STORE_REG( BLIT_STRIPE_OVERLAP_1, 0);
		}
	}
	else
	{
		/* disable compression */
		BGRC_PACKET_P_STORE_REG( DCEG_CFG, 0 );
	}
}
#endif

/***************************************************************************/
static void BGRC_PACKET_P_ProcSwPktFillBlit( BGRC_PacketContext_Handle hContext, BM2MC_PACKET_Header *header )
{
	BM2MC_PACKET_PacketFillBlit *packet = (BM2MC_PACKET_PacketFillBlit *) header;
	uint32_t pos = packet->rect.x | ((uint32_t) packet->rect.y << BGRC_M2MC(BLIT_OUTPUT_TOP_LEFT_TOP_SHIFT));
	uint32_t size = packet->rect.height | ((uint32_t) packet->rect.width << BGRC_M2MC(BLIT_OUTPUT_SIZE_SURFACE_WIDTH_SHIFT));

	BGRC_PACKET_P_DEBUG_PRINT_CTX( "-- FillBlit           " );
	BGRC_PACKET_P_STORE_REG_FIELD( BLIT_HEADER, SRC_SCALER_ENABLE, DISABLE );
	BGRC_PACKET_P_STORE_RECT_REGS( pos, size, 0, 0, pos, size, pos, size );
	BGRC_PACKET_P_STORE_REG_FIELD( BLIT_CTRL, STRIPE_ENABLE, DISABLE );
	BGRC_PACKET_P_STORE_REG_FIELD( SCALER_CTRL, HORIZ_SCALER_ENABLE, DISABLE );
	BGRC_PACKET_P_STORE_REG_FIELD( SCALER_CTRL, VERT_SCALER_ENABLE, DISABLE );
	BGRC_PACKET_P_STORE_REG_FIELD( SCALER_CTRL, SCALER_ORDER, VERT_THEN_HORIZ );

#ifdef BCHP_M2MC_DCEG_CFG
	BGRC_PACKET_P_SetDcegCompression(hContext);
#endif
	BGRC_PACKET_P_CheckAndForceDestDisable( hContext );
	BGRC_PACKET_P_DEBUG_PRINT( "\n" );
}

#if 0/*def BGRC_M2MC(BLIT_CTRL_BLOCK_AUTO_SPLIT_FIFO_MASK)*/
#define BGRC_PACKET_P_BLOCK_SPLIT_FIFO_FIX_1_SRC( x0, w0 ) \
	BGRC_PACKET_P_STORE_REG_FIELD_COMP( BLIT_CTRL, BLOCK_AUTO_SPLIT_FIFO, DISABLE, ENABLE, \
		(x0 & 7) && (w0 >= 57) && (w0 <= 64) )
#define BGRC_PACKET_P_BLOCK_SPLIT_FIFO_FIX_2_SRC( x0, w0, x1, w1 ) \
	BGRC_PACKET_P_STORE_REG_FIELD_COMP( BLIT_CTRL, BLOCK_AUTO_SPLIT_FIFO, DISABLE, ENABLE, ( \
		(x0 & 7) && (w0 >= 57) && (w0 <= 64)) || ( \
		(x1 & 7) && (w1 >= 57) && (w1 <= 64)) )
#else
#define BGRC_PACKET_P_BLOCK_SPLIT_FIFO_FIX_1_SRC( x0, w0 )
#define BGRC_PACKET_P_BLOCK_SPLIT_FIFO_FIX_2_SRC( x0, w0, x1, w1 )
#endif

#if defined(BCHP_M2MC_HORIZ_SCALER_0_STEP_reserved0_SHIFT)
#else
#define BCHP_M2MC_HORIZ_SCALER_0_STEP_reserved0_SHIFT   BCHP_M2MC_HORIZ_SCALER_STEP_reserved0_SHIFT
#endif

#define BGRC_PACKET_P_SCALER_STEP_FRAC_BITS       (BGRC_M2MC(HORIZ_SCALER_0_STEP_reserved0_SHIFT) - 4)
#define BGRC_PACKET_P_SCALER_STEP_FRAC_ONE        (1 << BGRC_PACKET_P_SCALER_STEP_FRAC_BITS)
#define BGRC_PACKET_P_SCALER_STEP_FRAC_MASK       (BGRC_PACKET_P_SCALER_STEP_FRAC_ONE - 1)
#define BGRC_PACKET_P_SCALER_STRIPE_MAX           128
#define BGRC_PACKET_P_SCALER_STEP_TO_WIDTH_SHIFT  (BGRC_PACKET_P_SCALER_STEP_FRAC_BITS - 16)
#define BGRC_PACKET_P_SCALER_WIDTH_TO_INT_SHIFT   (BGRC_PACKET_P_SCALER_STEP_FRAC_BITS - BGRC_PACKET_P_SCALER_STEP_TO_WIDTH_SHIFT)
#define BGRC_PACKET_P_SCALER_HALF_SIZE            4095

#define BGRC_PACKET_P_FIXED_SHIFT_RIGHT( data, shift ) \
	(((data) >> (shift)) | (((data) & 0x80000000) ? ~(0xFFFFFFFF >> (shift)) : 0))

#define BGRC_PACKET_P_SCALER_STRIPE_OVERLAP       3
#define BGRC_PACKET_P_SCALER_STRIPE_OVERLAP_BASE  4

#define BGRC_PACKET_P_NEG(a)                      (~(a) + 1)

/***************************************************************************/
static void BGRC_PACKET_P_SetScaler( BGRC_PacketContext_Handle hContext,
	BM2MC_PACKET_Rectangle *src_rect, BM2MC_PACKET_Rectangle *out_rect )
{
	BGRC_PACKET_P_Scaler *scaler = &hContext->scaler;
	uint32_t h_step, abs_h_phase;
	uint32_t hor_shift_adjust = (src_rect->width > BGRC_PACKET_P_SCALER_HALF_SIZE) ? 1 : 0;
	uint32_t ver_shift_adjust = (src_rect->height > BGRC_PACKET_P_SCALER_HALF_SIZE) ? 1 : 0;

	if (hContext->bBlitInvalid)
	{
		/* avoid dividing by 0 */
		return;
	}

	BGRC_PACKET_P_DEBUG_PRINT( "          .. SetScaler\n" );

	/* calculate scaler steps and initial phases */
	/* HW limit 1: abs(phase) < src_step */
	h_step = (((uint32_t) src_rect->width << (BGRC_PACKET_P_SCALER_STEP_FRAC_BITS - hor_shift_adjust)) / out_rect->width) << hor_shift_adjust;
	scaler->hor_phase = BGRC_PACKET_P_FIXED_SHIFT_RIGHT(h_step - BGRC_PACKET_P_SCALER_STEP_FRAC_ONE, 1);
	abs_h_phase = (h_step >= BGRC_PACKET_P_SCALER_STEP_FRAC_ONE)?
		(h_step - BGRC_PACKET_P_SCALER_STEP_FRAC_ONE) >> 1 : (BGRC_PACKET_P_SCALER_STEP_FRAC_ONE - h_step) >> 1;

	scaler->ver_step = (((uint32_t) src_rect->height << (BGRC_PACKET_P_SCALER_STEP_FRAC_BITS - ver_shift_adjust)) / out_rect->height) << ver_shift_adjust;
	scaler->ver_phase = BGRC_PACKET_P_FIXED_SHIFT_RIGHT(scaler->ver_step - BGRC_PACKET_P_SCALER_STEP_FRAC_ONE, 1);

	/* the following usage of fixed_scale is going to be obsolete */
	if (hContext->fixed_scale.hor_phase || hContext->fixed_scale.hor_step)
	{
		uint32_t shift = hContext->fixed_scale.shift;
		h_step = (hContext->fixed_scale.hor_step << (BGRC_PACKET_P_SCALER_STEP_FRAC_BITS - shift)) & ~BM2MC_PACKET_FIXED_SCALE_STEP_ZERO;
		scaler->hor_phase = hContext->fixed_scale.hor_phase << (BGRC_PACKET_P_SCALER_STEP_FRAC_BITS - shift);
		abs_h_phase = (scaler->hor_phase > 0)? scaler->hor_phase : BGRC_PACKET_P_NEG(scaler->hor_phase);
	}
	if (hContext->fixed_scale.ver_phase || hContext->fixed_scale.ver_step)
	{
		uint32_t shift = hContext->fixed_scale.shift;
		scaler->ver_step = (hContext->fixed_scale.ver_step << (BGRC_PACKET_P_SCALER_STEP_FRAC_BITS - shift)) & ~BM2MC_PACKET_FIXED_SCALE_STEP_ZERO;
		scaler->ver_phase = hContext->fixed_scale.ver_phase << (BGRC_PACKET_P_SCALER_STEP_FRAC_BITS - shift);
	}

	/* check if striping is required:
	 * note: experiment shows that we still need to use stripe even if vertical scl is not used */
	if( (src_rect->width > BGRC_PACKET_P_SCALER_STRIPE_MAX) && (out_rect->width > BGRC_PACKET_P_SCALER_STRIPE_MAX) )
	{
		uint32_t overlap_base, stripe_overlap, stripe_w, in_stripe_w, out_stripe_w, last_stripe_w;
		uint32_t  scale_factor;

		/* calculate stripe overlap */
		if(h_step <= 0x2*BGRC_PACKET_P_SCALER_STEP_FRAC_ONE) overlap_base = 4;
		else if (h_step <= 0x4*BGRC_PACKET_P_SCALER_STEP_FRAC_ONE) overlap_base = 3;
		else if (h_step <= 0x6*BGRC_PACKET_P_SCALER_STEP_FRAC_ONE) overlap_base = 2;
		else /* if (h_step > 0x6*BGRC_PACKET_P_SCALER_STEP_FRAC_ONE) */ overlap_base = 1;
		stripe_overlap =
			(abs_h_phase >> BGRC_PACKET_P_SCALER_STEP_FRAC_BITS) + overlap_base;

		/* calculate stripe width: adjust them so that HW limits are satisfied */
		stripe_w = BGRC_PACKET_P_SCALER_STRIPE_MAX - stripe_overlap * 2;
		out_stripe_w = ( src_rect->width >= out_rect->width )? stripe_w :
			(stripe_w << BGRC_PACKET_P_SCALER_STEP_FRAC_BITS) / h_step;
		out_stripe_w &= 0xFFFFFFFE;
		in_stripe_w = (out_stripe_w * h_step) >> BGRC_PACKET_P_SCALER_STEP_TO_WIDTH_SHIFT;
		last_stripe_w = ((uint32_t)src_rect->width << 16) % in_stripe_w;
		scale_factor = (BGRC_PACKET_P_SCALER_STEP_FRAC_ONE << 2) / h_step + 1;
		while( (in_stripe_w) && (out_stripe_w > 2) &&
			   (((((uint32_t)src_rect->width<<16) + in_stripe_w - 1) / in_stripe_w !=
				 (out_rect->width + out_stripe_w - 1) / out_stripe_w) ||
#ifdef BCHP_M2MC_BLIT_CTRL_BLOCK_AUTO_SPLIT_FIFO_MASK
				/* the following 2 limits are from Glenn's code, test shows that
				 * 7445 does not need any of them, but 7231 really needs them */
				((out_rect->width % out_stripe_w) < 4) ||
				/* glenn: make sure last stripe is less pixels than the rest */
				((out_rect->width % out_stripe_w) >= out_stripe_w - scale_factor) ||
#endif
				(last_stripe_w && (last_stripe_w < (stripe_overlap <<16)))) )
		{
			out_stripe_w -= 2;
			in_stripe_w = (out_stripe_w * h_step) >> BGRC_PACKET_P_SCALER_STEP_TO_WIDTH_SHIFT;
			last_stripe_w = ((uint32_t)src_rect->width << 16) % in_stripe_w;
		}

		scaler->output_stripe_width = out_stripe_w;
		scaler->input_stripe_width = in_stripe_w;
		scaler->stripe_overlap = stripe_overlap;
		scaler->stripe_count = (0 == out_stripe_w)? 1 : (out_rect->width + out_stripe_w - 1) / out_stripe_w;

#if (BDBG_DEBUG_BUILD)
		if (in_stripe_w < (110<<16) || out_stripe_w < 110)
		{
			BDBG_WRN(("info: in_w %d, in_stripe_w 0x%x(%d), out_w %d, out_stripe_w %d",
				src_rect->width , in_stripe_w, in_stripe_w>>16, out_rect->width, out_stripe_w));
			if ((((uint32_t)src_rect->width<<16) + in_stripe_w - 1) / in_stripe_w !=
				(out_rect->width + out_stripe_w - 1) / out_stripe_w)
				BDBG_WRN(("# of in stripes != # of out stripes: in_w %d, in_stripe_w 0x%x(%d), out_w %d, out_stripe_w %d",
					src_rect->width , in_stripe_w, in_stripe_w>>16, out_rect->width, out_stripe_w));
			if (last_stripe_w && (last_stripe_w < (stripe_overlap <<16)))
				BDBG_WRN(("last stripe in_w too small: in_w %d, in_stripe_w 0x%x(%d), out_w %d, out_stripe_w %d, last_stripe_in %d, min %d",
					src_rect->width , in_stripe_w, in_stripe_w>>16, out_rect->width, out_stripe_w, last_stripe_w, stripe_overlap <<16));
			if ((out_rect->width % out_stripe_w) < 4)
				BDBG_WRN(("last stripe out_w < 4: in_w %d, in_stripe_w 0x%x(%d), out_w %d, out_stripe_w %d, last_stripe_out %d",
					src_rect->width , in_stripe_w, in_stripe_w>>16, out_rect->width, out_stripe_w, out_rect->width % out_stripe_w));
			if ((out_rect->width % out_stripe_w) >= out_stripe_w - scale_factor)
				BDBG_WRN(("last stripe out_w too big: in_w %d, in_stripe_w 0x%x(%d), out_w %d, out_stripe_w %d, last_stripe_out %d >= %d",
					src_rect->width , in_stripe_w, in_stripe_w>>16, out_rect->width, out_stripe_w, out_rect->width % out_stripe_w, out_stripe_w - scale_factor));
		}
#endif /* (BDBG_DEBUG_BUILD) */
	}
	else
	{
		scaler->stripe_overlap = 0;
		scaler->output_stripe_width = 0;
		scaler->input_stripe_width = 0;
		scaler->stripe_count = 1;
	}
	scaler->hor_step = h_step;
	scaler->stripe_num = 0;
}

/***************************************************************************/
static void BGRC_PACKET_P_SetScaleFor420Src(BGRC_PacketContext_Handle hContext)
{
	uint32_t h_step_1, h_phase_1, abs_h_phase_1;
	uint32_t stripe_overlap_1, overlap_base_1;
	uint32_t v_step_1, v_phase_1;

	if (hContext->bBlitInvalid)
	{
		/* avoid dividing by 0 */
		return;
	}

	BGRC_PACKET_P_DEBUG_PRINT( "          .. SetScaleFor420Src\n" );

	/* TODO: since scale ratio is not the same, 420 CbCr might affect the scaler stripe width? */
	if (0 == BGRC_PACKET_P_GET_REG_FIELD( BLIT_HEADER, SRC_SCALER_ENABLE ))
	{
		/* must have no luma scale */
		BGRC_PACKET_P_STORE_REG_FIELD_COMP( BLIT_CTRL, STRIPE_ENABLE, DISABLE, ENABLE, hContext->scaler.stripe_count > 1 );
		BGRC_PACKET_P_STORE_REG( BLIT_INPUT_STRIPE_WIDTH, hContext->scaler.input_stripe_width );
		BGRC_PACKET_P_STORE_REG( BLIT_OUTPUT_STRIPE_WIDTH, hContext->scaler.output_stripe_width );
		BGRC_PACKET_P_STORE_REG( BLIT_STRIPE_OVERLAP, hContext->scaler.stripe_overlap );

		BGRC_PACKET_P_STORE_REG_FIELD( BLIT_HEADER, SRC_SCALER_ENABLE, ENABLE );
		BGRC_PACKET_P_STORE_REG_FIELD( SCALER_CTRL, HORIZ_SCALER_ENABLE, ENABLE );
		BGRC_PACKET_P_STORE_REG_FIELD( SCALER_CTRL, VERT_SCALER_ENABLE, ENABLE );
		BGRC_PACKET_P_STORE_REG_FIELD( SCALER_CTRL, SCALER_ORDER, VERT_THEN_HORIZ ); /* likely hor scale up */
		BGRC_PACKET_P_STORE_SCALE_REGS( HORIZ, 0, hContext->scaler.hor_phase, hContext->scaler.hor_step );
		BGRC_PACKET_P_STORE_SCALE_REGS( VERT, 0, hContext->scaler.ver_phase, hContext->scaler.ver_step );
	}

	/* note: 420 CbCr was sampled at 2*x + 0.5 horizontally in luma coordinates (the same location as even pixel luma),
	 * and at 2*y + 1 vertically in luma coordinates (diff from luma), i.e. at (x + 0.25, y + 0.5) in chroma coordinates.
	 * Therefore, theortically horizontal chroma initial phase h_phase_1 = (0.5 * h_step_1 - 0.25).
	 */
	h_step_1 = hContext->scaler.hor_step / 2;
#if 0
	h_phase_1 = BGRC_PACKET_P_FIXED_SHIFT_RIGHT(h_step_1 - (BGRC_PACKET_P_SCALER_STEP_FRAC_ONE>>1), 1);
	abs_h_phase_1 = (h_step_1 >= (BGRC_PACKET_P_SCALER_STEP_FRAC_ONE>>1))?
		(h_step_1 - (BGRC_PACKET_P_SCALER_STEP_FRAC_ONE>>1)) >> 1:
		((BGRC_PACKET_P_SCALER_STEP_FRAC_ONE>>1) - h_step_1) >> 1;
#else
	/* But with this value Android tests show that ourput chroma is left shited. And HW team suggest to use
	 * (0.5 * h_step_1 - 0.5), this value makes Android tests look correct. This is how we program now. */
	h_phase_1 = BGRC_PACKET_P_FIXED_SHIFT_RIGHT(h_step_1 - BGRC_PACKET_P_SCALER_STEP_FRAC_ONE, 1);
	abs_h_phase_1 = (h_step_1 >= BGRC_PACKET_P_SCALER_STEP_FRAC_ONE)?
		(h_step_1 - BGRC_PACKET_P_SCALER_STEP_FRAC_ONE) >> 1:
		(BGRC_PACKET_P_SCALER_STEP_FRAC_ONE - h_step_1) >> 1;
#endif

	if (h_step_1 <= 0x2*BGRC_PACKET_P_SCALER_STEP_FRAC_ONE) overlap_base_1 = 4;
	else if (h_step_1 <= 0x4*BGRC_PACKET_P_SCALER_STEP_FRAC_ONE) overlap_base_1 = 3;
	else if (h_step_1 <= 0x6*BGRC_PACKET_P_SCALER_STEP_FRAC_ONE) overlap_base_1 = 2;
	else /* if (h_step_1 > 0x6*BGRC_PACKET_P_SCALER_STEP_FRAC_ONE) */ overlap_base_1 = 1;
	stripe_overlap_1 =
		(abs_h_phase_1 >> BGRC_PACKET_P_SCALER_STEP_FRAC_BITS) + overlap_base_1;

	v_step_1 = hContext->scaler.ver_step / 2;
	v_phase_1 = BGRC_PACKET_P_FIXED_SHIFT_RIGHT(v_step_1 - BGRC_PACKET_P_SCALER_STEP_FRAC_ONE, 1);

	BGRC_PACKET_P_STORE_REG( BLIT_INPUT_STRIPE_WIDTH_1, hContext->scaler.input_stripe_width / 2 );
	BGRC_PACKET_P_STORE_REG( BLIT_STRIPE_OVERLAP_1, stripe_overlap_1 );
	BGRC_PACKET_P_STORE_SCALE_REGS( HORIZ, 1, h_phase_1, h_step_1 );
	BGRC_PACKET_P_STORE_SCALE_REGS( VERT,  1, v_phase_1, v_step_1 );
}

/***************************************************************************/
static void BGRC_PACKET_P_ProcSwPktCopyBlit( BGRC_PacketContext_Handle hContext, BM2MC_PACKET_Header *header )
{
	BM2MC_PACKET_PacketCopyBlit *packet = (BM2MC_PACKET_PacketCopyBlit *) header;
	uint32_t src_pos = packet->src_rect.x | ((uint32_t) packet->src_rect.y << BGRC_M2MC(BLIT_OUTPUT_TOP_LEFT_TOP_SHIFT));
	uint32_t out_pos = packet->out_point.x | ((uint32_t) packet->out_point.y << BGRC_M2MC(BLIT_OUTPUT_TOP_LEFT_TOP_SHIFT));
	uint32_t size = packet->src_rect.height | ((uint32_t) packet->src_rect.width << BGRC_M2MC(BLIT_OUTPUT_SIZE_SURFACE_WIDTH_SHIFT));

	BGRC_PACKET_P_BLOCK_SPLIT_FIFO_FIX_1_SRC( packet->src_rect.x, packet->src_rect.width );

	BGRC_PACKET_P_DEBUG_PRINT_CTX( "-- CopyBlit           " );
	BGRC_PACKET_P_STORE_REG_FIELD( BLIT_HEADER, SRC_SCALER_ENABLE, DISABLE );
	BGRC_PACKET_P_STORE_RECT_REGS( src_pos, size, src_pos, size, out_pos, size, out_pos, size );
	BGRC_PACKET_P_STORE_REG_FIELD( BLIT_CTRL, STRIPE_ENABLE, DISABLE );

	if (hContext->b420Src)
	{
		BGRC_PACKET_P_SetScaler( hContext, &packet->src_rect, &packet->src_rect );
		BGRC_PACKET_P_SetScaleFor420Src(hContext);
	}

#ifdef BCHP_M2MC_DCEG_CFG
	BGRC_PACKET_P_SetDcegCompression(hContext);
#endif

	BGRC_PACKET_P_CheckAndForceDestDisable( hContext );
	BGRC_PACKET_P_DEBUG_PRINT( "\n" );
}

/***************************************************************************/
static void BGRC_PACKET_P_ProcSwPktBlendBlit( BGRC_PacketContext_Handle hContext, BM2MC_PACKET_Header *header )
{
	BM2MC_PACKET_PacketBlendBlit *packet = (BM2MC_PACKET_PacketBlendBlit *) header;
	uint32_t src_pos = packet->src_rect.x | ((uint32_t) packet->src_rect.y << BGRC_M2MC(BLIT_OUTPUT_TOP_LEFT_TOP_SHIFT));
	uint32_t out_pos = packet->out_point.x | ((uint32_t) packet->out_point.y << BGRC_M2MC(BLIT_OUTPUT_TOP_LEFT_TOP_SHIFT));
	uint32_t dst_pos = packet->dst_point.x | ((uint32_t) packet->dst_point.y << BGRC_M2MC(BLIT_OUTPUT_TOP_LEFT_TOP_SHIFT));
	uint32_t size = packet->src_rect.height | ((uint32_t) packet->src_rect.width << BGRC_M2MC(BLIT_OUTPUT_SIZE_SURFACE_WIDTH_SHIFT));

	BGRC_PACKET_P_BLOCK_SPLIT_FIFO_FIX_2_SRC( packet->src_rect.x, packet->src_rect.width, packet->dst_point.x, packet->src_rect.width );

	BGRC_PACKET_P_DEBUG_PRINT_CTX( "-- BlendBlit          " );
	BGRC_PACKET_P_STORE_REG_FIELD( BLIT_HEADER, SRC_SCALER_ENABLE, DISABLE );
	BGRC_PACKET_P_STORE_RECT_REGS( src_pos, size, src_pos, size, dst_pos, size, out_pos, size );
	BGRC_PACKET_P_STORE_REG_FIELD( BLIT_CTRL, STRIPE_ENABLE, DISABLE );

	if (hContext->b420Src)
	{
		BGRC_PACKET_P_SetScaler( hContext, &packet->src_rect, &packet->src_rect );
		BGRC_PACKET_P_SetScaleFor420Src(hContext);
	}

#ifdef BCHP_M2MC_DCEG_CFG
	BGRC_PACKET_P_SetDcegCompression(hContext);
#endif

	BGRC_PACKET_P_CheckAndForceDestDisable( hContext );
	BGRC_PACKET_P_DEBUG_PRINT( "\n" );
}


/***************************************************************************/
static void BGRC_PACKET_P_SetStriping( BGRC_PacketContext_Handle hContext,
	BM2MC_PACKET_Rectangle *src_rect, BM2MC_PACKET_Rectangle *out_rect,  BM2MC_PACKET_Point *dst_point,
	BGRC_PACKET_P_Stripe *stripe)
{
	BGRC_PACKET_P_Scaler *scaler = &hContext->scaler;
	uint32_t stripe_num = hContext->scaler.stripe_num;
	stripe->hor_phase = scaler->hor_phase;
	stripe->src_x = src_rect->x;
	stripe->dst_x = dst_point->x;
	stripe->out_x = out_rect->x;

	if( scaler->stripe_count <= 1 )
	{
		stripe->src_width = src_rect->width;
		stripe->out_width = out_rect->width;
	}
	else
	{
		/* adjust phase and positions for all but the first stripe */
		if( stripe_num > 0 )
		{
			uint32_t input_stripe_start = scaler->input_stripe_width * stripe_num;
			uint32_t output_stripe_start = scaler->output_stripe_width * stripe_num;
			uint32_t fixed_phase = BGRC_PACKET_P_FIXED_SHIFT_RIGHT(stripe->hor_phase, BGRC_PACKET_P_SCALER_STEP_TO_WIDTH_SHIFT);
			uint32_t fixed_left = fixed_phase + input_stripe_start;
			uint32_t pad_left = BGRC_PACKET_P_SCALER_STRIPE_OVERLAP;

			stripe->src_x += BGRC_PACKET_P_FIXED_SHIFT_RIGHT(fixed_left, BGRC_PACKET_P_SCALER_WIDTH_TO_INT_SHIFT) - BGRC_PACKET_P_SCALER_STRIPE_OVERLAP;
			stripe->dst_x += output_stripe_start;
			stripe->out_x += output_stripe_start;

			stripe->hor_phase += input_stripe_start << BGRC_PACKET_P_SCALER_STEP_TO_WIDTH_SHIFT;
			stripe->hor_phase &= BGRC_PACKET_P_SCALER_STEP_FRAC_MASK;
			stripe->hor_phase += pad_left << BGRC_PACKET_P_SCALER_STEP_FRAC_BITS;
		}

		/* adjust widths */
		if( stripe_num < scaler->stripe_count - 1 )
		{
			stripe->src_width = (scaler->input_stripe_width >> BGRC_PACKET_P_SCALER_WIDTH_TO_INT_SHIFT) + BGRC_PACKET_P_SCALER_STRIPE_OVERLAP;
			if( stripe_num > 0 )
				stripe->src_width += BGRC_PACKET_P_SCALER_STRIPE_OVERLAP;
			stripe->out_width = scaler->output_stripe_width;
		}
		else
		{
			stripe->src_width = src_rect->width - (stripe->src_x - src_rect->x);
			stripe->out_width = out_rect->width - scaler->output_stripe_width * (scaler->stripe_count - 1);
		}
		/* adjust source x for horizontal source mirroring */
		if( BGRC_PACKET_P_GET_REG(BLIT_CTRL) & BGRC_M2MC(BLIT_CTRL_SRC_H_DIRECTION_MASK) )
		{
			stripe->src_x = src_rect->x;
			if( stripe_num < scaler->stripe_count - 1 )
				stripe->src_x += src_rect->width - (scaler->input_stripe_width * (scaler->stripe_count - 1) >> BGRC_PACKET_P_SCALER_WIDTH_TO_INT_SHIFT) - BGRC_PACKET_P_SCALER_STRIPE_OVERLAP;
			if( stripe_num < scaler->stripe_count - 2 )
				stripe->src_x += (scaler->input_stripe_width * (scaler->stripe_count - stripe_num - 2) >> BGRC_PACKET_P_SCALER_WIDTH_TO_INT_SHIFT) - BGRC_PACKET_P_SCALER_STRIPE_OVERLAP;
		}

		/* adjust output x for horizontal output mirroring */
		if( BGRC_PACKET_P_GET_REG(BLIT_CTRL) & BGRC_M2MC(BLIT_CTRL_OUTPUT_H_DIRECTION_MASK) )
		{
			stripe->out_x = out_rect->x;
			if( stripe_num < scaler->stripe_count - 1 )
				stripe->out_x += out_rect->width - scaler->output_stripe_width * (scaler->stripe_count - 1);
			if( stripe_num < scaler->stripe_count - 2 )
				stripe->out_x += scaler->output_stripe_width * (scaler->stripe_count - stripe_num - 2);
		}

		/* adjust destination x for horizontal destination mirroring */
		if( BGRC_PACKET_P_GET_REG(BLIT_CTRL) & BGRC_M2MC(BLIT_CTRL_DEST_H_DIRECTION_MASK) )
		{
			stripe->dst_x = dst_point->x;
			if( stripe_num < scaler->stripe_count - 1 )
				stripe->dst_x += out_rect->width - scaler->output_stripe_width * (scaler->stripe_count - 1);
			if( stripe_num < scaler->stripe_count - 2 )
				stripe->dst_x += scaler->output_stripe_width * (scaler->stripe_count - stripe_num - 2);
		}
	}

	/* need even stripe width for YCbCr422 surfaces */
	if( (stripe->src_x & 1) && (BGRC_PACKET_P_GET_REG_FIELD(SRC_SURFACE_FORMAT_DEF_1, FORMAT_TYPE) == M2MC_FT_YCbCr422) )
	{
		stripe->src_x--;
		stripe->hor_phase += 1L << BGRC_PACKET_P_SCALER_STEP_FRAC_BITS;
		stripe->src_width++;
	}

    BDBG_ASSERT(stripe->src_x + stripe->src_width <= src_rect->x + src_rect->width);
    BDBG_ASSERT(stripe->out_x + stripe->out_width <= out_rect->x + out_rect->width);
}

/***************************************************************************/
static void BGRC_PACKET_P_ProcSwPktScaleBlit( BGRC_PacketContext_Handle hContext, BM2MC_PACKET_Header *header )
{
	BM2MC_PACKET_PacketScaleBlit *packet = (BM2MC_PACKET_PacketScaleBlit *) header;
	uint32_t out_pos = packet->out_rect.x | ((uint32_t) packet->out_rect.y << BGRC_M2MC(BLIT_OUTPUT_TOP_LEFT_TOP_SHIFT));
	uint32_t out_size = packet->out_rect.height | ((uint32_t) packet->out_rect.width << BGRC_M2MC(BLIT_OUTPUT_SIZE_SURFACE_WIDTH_SHIFT));
	uint32_t src_pos, src_size, src_pos1, src_size1;

	hContext->scaler_header = header;

	BGRC_PACKET_P_BLOCK_SPLIT_FIFO_FIX_1_SRC( packet->src_rect.x, packet->src_rect.width );

	BGRC_PACKET_P_DEBUG_PRINT_CTX( "-- ScaleBlit          " );
	BGRC_PACKET_P_STORE_REG_FIELD_COMP( BLIT_CTRL, STRIPE_ENABLE, DISABLE, ENABLE, hContext->scaler.stripe_count > 1 );
#ifdef BCHP_M2MC_BLIT_CTRL_READ_420_AS_FIELDS_MASK
	if(BGRC_PACKET_P_GET_REG_FIELD(BLIT_CTRL, READ_420_AS_FIELDS))
	{
		src_pos = packet->src_rect.x | ((uint32_t) (packet->src_rect.y/2) << BGRC_M2MC(BLIT_OUTPUT_TOP_LEFT_TOP_SHIFT));
		src_size = (packet->src_rect.height/2) | ((uint32_t) packet->src_rect.width << BGRC_M2MC(BLIT_OUTPUT_SIZE_SURFACE_WIDTH_SHIFT));
		src_pos1 = (packet->src_rect.x/2)| ((uint32_t) (packet->src_rect.y/4) << BGRC_M2MC(BLIT_OUTPUT_TOP_LEFT_TOP_SHIFT));
		src_size1 = (packet->src_rect.height/4) | ((uint32_t) (packet->src_rect.width/2) << BGRC_M2MC(BLIT_OUTPUT_SIZE_SURFACE_WIDTH_SHIFT));
	}
	else
#endif
	{
		src_pos = packet->src_rect.x | ((uint32_t) packet->src_rect.y << BGRC_M2MC(BLIT_OUTPUT_TOP_LEFT_TOP_SHIFT));
		src_size = packet->src_rect.height | ((uint32_t) packet->src_rect.width << BGRC_M2MC(BLIT_OUTPUT_SIZE_SURFACE_WIDTH_SHIFT));
		if (hContext->b420Src)
		{
			src_pos1 = (packet->src_rect.x/2)| ((uint32_t) (packet->src_rect.y/2) << BGRC_M2MC(BLIT_OUTPUT_TOP_LEFT_TOP_SHIFT));
			src_size1 = (packet->src_rect.height/2) | ((uint32_t) (packet->src_rect.width/2) << BGRC_M2MC(BLIT_OUTPUT_SIZE_SURFACE_WIDTH_SHIFT));
		}
		else
		{
			src_pos1 = src_pos;
			src_size1 = src_size;
		}
	}

	BGRC_PACKET_P_STORE_RECT_REGS( src_pos, src_size, src_pos1, src_size1, out_pos, out_size, out_pos, out_size );
	BGRC_PACKET_P_STORE_REG( BLIT_INPUT_STRIPE_WIDTH, hContext->scaler.input_stripe_width );
	BGRC_PACKET_P_STORE_REG( BLIT_OUTPUT_STRIPE_WIDTH, hContext->scaler.output_stripe_width );
	BGRC_PACKET_P_STORE_REG( BLIT_STRIPE_OVERLAP, hContext->scaler.stripe_overlap );
	BGRC_PACKET_P_STORE_REG_FIELD( BLIT_HEADER, SRC_SCALER_ENABLE, ENABLE );
	BGRC_PACKET_P_DEBUG_PRINT( "\n                      " );
	BGRC_PACKET_P_STORE_REG_FIELD( SCALER_CTRL, HORIZ_SCALER_ENABLE, ENABLE );
	BGRC_PACKET_P_STORE_REG_FIELD( SCALER_CTRL, VERT_SCALER_ENABLE, ENABLE );
	BGRC_PACKET_P_STORE_REG_FIELD_COMP( SCALER_CTRL, SCALER_ORDER, VERT_THEN_HORIZ, HORIZ_THEN_VERT, packet->src_rect.width >= packet->out_rect.width );
	BGRC_PACKET_P_STORE_SCALE_REGS( HORIZ, 0, hContext->scaler.hor_phase, hContext->scaler.hor_step );
	BGRC_PACKET_P_STORE_SCALE_REGS( VERT, 0, hContext->scaler.ver_phase, hContext->scaler.ver_step );

	if (hContext->b420Src)
	{
		BGRC_PACKET_P_SetScaleFor420Src(hContext);
	}
	else
	{
		/* likely for W1R5G6B5 */
		BGRC_PACKET_P_STORE_REG( BLIT_INPUT_STRIPE_WIDTH_1, hContext->scaler.input_stripe_width );
		BGRC_PACKET_P_STORE_REG( BLIT_STRIPE_OVERLAP_1, hContext->scaler.stripe_overlap );
		BGRC_PACKET_P_STORE_SCALE_REGS( HORIZ, 1, hContext->scaler.hor_phase, hContext->scaler.hor_step );
		BGRC_PACKET_P_STORE_SCALE_REGS( VERT, 1, hContext->scaler.ver_phase, hContext->scaler.ver_step );
	}

#ifdef BCHP_M2MC_DCEG_CFG
	BGRC_PACKET_P_SetDcegCompression(hContext);
#endif

	BGRC_PACKET_P_CheckAndForceDestDisable( hContext );
	BGRC_PACKET_P_DEBUG_PRINT( "\n" );
}

/**************************************************************************
 * software mimic hw stripe
 */
static void BGRC_PACKET_P_ProcSwPktStripeBlit( BGRC_PacketContext_Handle hContext,
	BM2MC_PACKET_Rectangle *src_rect, BM2MC_PACKET_Rectangle *out_rect,  BM2MC_PACKET_Point *dst_point )
{
	BGRC_PACKET_P_Stripe stripe;
	BGRC_PACKET_P_SetStriping( hContext, src_rect, out_rect, dst_point, &stripe );
	hContext->scaler.stripe_num++;

	{
		uint32_t src_pos = stripe.src_x | ((uint32_t) src_rect->y << BGRC_M2MC(BLIT_OUTPUT_TOP_LEFT_TOP_SHIFT));
		uint32_t out_pos = stripe.out_x | ((uint32_t) out_rect->y << BGRC_M2MC(BLIT_OUTPUT_TOP_LEFT_TOP_SHIFT));
		uint32_t dst_pos = stripe.dst_x | ((uint32_t) dst_point->y << BGRC_M2MC(BLIT_OUTPUT_TOP_LEFT_TOP_SHIFT));
		uint32_t src_size = src_rect->height | ((uint32_t) stripe.src_width << BGRC_M2MC(BLIT_OUTPUT_SIZE_SURFACE_WIDTH_SHIFT));
		uint32_t out_size = out_rect->height | ((uint32_t) stripe.out_width << BGRC_M2MC(BLIT_OUTPUT_SIZE_SURFACE_WIDTH_SHIFT));

		BGRC_PACKET_P_BLOCK_SPLIT_FIFO_FIX_2_SRC( stripe.src_x, stripe.src_width, stripe.dst_x, stripe.out_width );

		BGRC_PACKET_P_DEBUG_PRINT( "-- StripeBlit         " );
		BGRC_PACKET_P_STORE_REG_FIELD( BLIT_CTRL, STRIPE_ENABLE, DISABLE );
		BGRC_PACKET_P_STORE_RECT_REGS( src_pos, src_size, src_pos, src_size, dst_pos, out_size, out_pos, out_size );
		BGRC_PACKET_P_STORE_REG_FIELD( BLIT_HEADER, SRC_SCALER_ENABLE, ENABLE );
		BGRC_PACKET_P_DEBUG_PRINT( "\n                      " );
		BGRC_PACKET_P_STORE_REG_FIELD( SCALER_CTRL, HORIZ_SCALER_ENABLE, ENABLE );
		BGRC_PACKET_P_STORE_REG_FIELD( SCALER_CTRL, VERT_SCALER_ENABLE, ENABLE );
		BGRC_PACKET_P_STORE_REG_FIELD_COMP( SCALER_CTRL, SCALER_ORDER, VERT_THEN_HORIZ, HORIZ_THEN_VERT, stripe.src_width >= stripe.out_width );
		BGRC_PACKET_P_STORE_SCALE_REGS( HORIZ, 0, stripe.hor_phase, hContext->scaler.hor_step );
		BGRC_PACKET_P_STORE_SCALE_REGS( HORIZ, 1, stripe.hor_phase, hContext->scaler.hor_step );
		BGRC_PACKET_P_STORE_SCALE_REGS( VERT, 0, hContext->scaler.ver_phase, hContext->scaler.ver_step );
		BGRC_PACKET_P_STORE_SCALE_REGS( VERT, 1, hContext->scaler.ver_phase, hContext->scaler.ver_step );
#ifdef BCHP_M2MC_DCEG_CFG
		BGRC_PACKET_P_SetDcegCompression(hContext);
#endif
		BGRC_PACKET_P_CheckAndForceDestDisable( hContext );
		BGRC_PACKET_P_DEBUG_PRINT( "\n" );
	}
}

/***************************************************************************/
static void BGRC_PACKET_P_ProcSwPktScaleBlendBlit( BGRC_PacketContext_Handle hContext, BM2MC_PACKET_Header *header )
{
	BM2MC_PACKET_PacketScaleBlendBlit *packet = (BM2MC_PACKET_PacketScaleBlendBlit *) header;

	BGRC_PACKET_P_DEBUG_PRINT_CTX( "-- ScaleBlendBlit       " );
	if( hContext->scaler.stripe_num == 0 )
	{
		BGRC_PACKET_P_SetScaler( hContext, &packet->src_rect, &packet->out_rect );
		hContext->scaler_header = header;
	}

	/* syang: why we can not use BGRC_PACKET_P_ProcSwPktScaleBlit( hContext, header ); */
	BGRC_PACKET_P_ProcSwPktStripeBlit( hContext, &packet->src_rect, &packet->out_rect, &packet->dst_point );

#ifdef BCHP_M2MC_DCEG_CFG
	BGRC_PACKET_P_SetDcegCompression(hContext);
#endif

	BGRC_PACKET_P_CheckAndForceDestDisable( hContext );
	BGRC_PACKET_P_DEBUG_PRINT( "\n                      " );
}

/***************************************************************************/
static void BGRC_PACKET_P_ProcSwPktUpdateScaleBlit( BGRC_PacketContext_Handle hContext, BM2MC_PACKET_Header *header )
{
	BM2MC_PACKET_PacketUpdateScaleBlit *packet = (BM2MC_PACKET_PacketUpdateScaleBlit *) header;
	uint32_t shift = BGRC_PACKET_P_SCALER_STEP_FRAC_BITS;

	uint32_t hor_step = ((uint32_t) packet->src_rect.width << shift) / packet->out_rect.width;
	uint32_t ver_step = ((uint32_t) packet->src_rect.height << shift) / packet->out_rect.height;

	uint32_t offset_x = packet->update_rect.x * hor_step;
	uint32_t offset_y = packet->update_rect.y * ver_step;

	uint32_t src_x0 = packet->src_rect.x;
	uint32_t src_y0 = packet->src_rect.y;
	uint32_t src_x1 = packet->src_rect.x + packet->src_rect.width;
	uint32_t src_y1 = packet->src_rect.y + packet->src_rect.height;

	uint32_t scale_x0 = ((uint32_t) packet->update_rect.x * hor_step) >> shift;
	uint32_t scale_y0 = ((uint32_t) packet->update_rect.y * ver_step) >> shift;
	uint32_t scale_x1 = ((uint32_t) (packet->update_rect.x + packet->update_rect.width) * hor_step) >> shift;
	uint32_t scale_y1 = ((uint32_t) (packet->update_rect.y + packet->update_rect.height) * ver_step) >> shift;

	uint32_t pad = 2;
	uint32_t pad_x0 = ((scale_x0 > src_x0 + pad) ? scale_x0 - pad : src_x0);
	uint32_t pad_y0 = ((scale_y0 > src_y0 + pad) ? scale_y0 - pad : src_y0);
	uint32_t pad_x1 = ((scale_x1 + pad < src_x1) ? scale_x1 + pad : src_x1);
	uint32_t pad_y1 = ((scale_y1 + pad < src_y1) ? scale_y1 + pad : src_y1);

	uint32_t hor_phase = (((uint32_t) scale_x0 - pad_x0) << shift) + (offset_x & BGRC_PACKET_P_SCALER_STEP_FRAC_MASK) +
		BGRC_PACKET_P_FIXED_SHIFT_RIGHT(hor_step - BGRC_PACKET_P_SCALER_STEP_FRAC_ONE, 1);
	uint32_t ver_phase = (((uint32_t) scale_y0 - pad_y0) << shift) + (offset_y & BGRC_PACKET_P_SCALER_STEP_FRAC_MASK) +
		BGRC_PACKET_P_FIXED_SHIFT_RIGHT(ver_step - BGRC_PACKET_P_SCALER_STEP_FRAC_ONE, 1);

	bool adjust_ver = (packet->update_rect.height == 1) && ((ver_phase >> BGRC_PACKET_P_SCALER_STEP_FRAC_BITS) >= 3);
	uint32_t new_pad_y0 = pad_y0 + (adjust_ver ? 1 : 0);

	uint32_t src_pos = pad_x0 | (new_pad_y0 << BGRC_M2MC(BLIT_OUTPUT_TOP_LEFT_TOP_SHIFT));
	uint32_t out_pos = packet->update_rect.x | ((uint32_t) packet->update_rect.y << BGRC_M2MC(BLIT_OUTPUT_TOP_LEFT_TOP_SHIFT));
	uint32_t src_size = (pad_y1 - new_pad_y0) | ((pad_x1 - pad_x0) << BGRC_M2MC(BLIT_OUTPUT_SIZE_SURFACE_WIDTH_SHIFT));
	uint32_t out_size = packet->update_rect.height | ((uint32_t) packet->update_rect.width << BGRC_M2MC(BLIT_OUTPUT_SIZE_SURFACE_WIDTH_SHIFT));

	BM2MC_PACKET_Rectangle src_rect;
	src_rect.x = pad_x0;
	src_rect.y = pad_y0;
	src_rect.width = pad_x1 - pad_x0;
	src_rect.height = pad_y1 - new_pad_y0;

	BGRC_PACKET_P_SetScaler( hContext, &src_rect, &packet->update_rect );
	hContext->scaler_header = header;

	hContext->scaler.input_stripe_width += 0x7FFF;
	hContext->scaler.input_stripe_width &= ~0x7FFF;

	BGRC_PACKET_P_BLOCK_SPLIT_FIFO_FIX_2_SRC( pad_x, pad_w, packet->update_rect.x, packet->update_rect.width );

	BGRC_PACKET_P_DEBUG_PRINT_CTX( "-- UpdateScaleBlit    " );
	BGRC_PACKET_P_STORE_REG_FIELD_COMP( BLIT_CTRL, STRIPE_ENABLE, DISABLE, ENABLE, hContext->scaler.stripe_count > 1 );
	BGRC_PACKET_P_STORE_RECT_REGS( src_pos, src_size, src_pos, src_size, out_pos, out_size, out_pos, out_size );
	BGRC_PACKET_P_STORE_REG( BLIT_INPUT_STRIPE_WIDTH, hContext->scaler.input_stripe_width );
	BGRC_PACKET_P_STORE_REG( BLIT_INPUT_STRIPE_WIDTH_1, hContext->scaler.input_stripe_width );
	BGRC_PACKET_P_STORE_REG( BLIT_OUTPUT_STRIPE_WIDTH, hContext->scaler.output_stripe_width );
	BGRC_PACKET_P_STORE_REG( BLIT_STRIPE_OVERLAP, hContext->scaler.stripe_overlap );
	BGRC_PACKET_P_STORE_REG( BLIT_STRIPE_OVERLAP_1, hContext->scaler.stripe_overlap );
	BGRC_PACKET_P_STORE_REG_FIELD( BLIT_HEADER, SRC_SCALER_ENABLE, ENABLE );
	BGRC_PACKET_P_DEBUG_PRINT( "\n                      " );
	BGRC_PACKET_P_STORE_REG_FIELD( SCALER_CTRL, HORIZ_SCALER_ENABLE, ENABLE );
	BGRC_PACKET_P_STORE_REG_FIELD( SCALER_CTRL, VERT_SCALER_ENABLE, ENABLE );
	BGRC_PACKET_P_STORE_REG_FIELD_COMP( SCALER_CTRL, SCALER_ORDER, VERT_THEN_HORIZ, HORIZ_THEN_VERT, packet->src_rect.width >= packet->out_rect.width );
	BGRC_PACKET_P_STORE_SCALE_REGS( HORIZ, 0, hor_phase, hor_step );
	BGRC_PACKET_P_STORE_SCALE_REGS( HORIZ, 1, hor_phase, hor_step );
	BGRC_PACKET_P_STORE_SCALE_REGS( VERT, 0, ver_phase, ver_step );
	BGRC_PACKET_P_STORE_SCALE_REGS( VERT, 1, ver_phase, ver_step );
	BGRC_PACKET_P_CheckAndForceDestDisable( hContext );
	BGRC_PACKET_P_DEBUG_PRINT( "\n" );
}

/***************************************************************************/
#if BCHP_CHIP==7400
#define BGRC_PACKET_P_SW_DESTRIPE
#endif

/***************************************************************************/
static void BGRC_PACKET_P_ProcSwPktDestripeBlit( BGRC_PacketContext_Handle hContext, BM2MC_PACKET_Header *header )
{
#ifdef BGRC_PACKET_P_SW_DESTRIPE
	BM2MC_PACKET_PacketDestripeBlit *packet = (BM2MC_PACKET_PacketDestripeBlit *) header;
	BGRC_PACKET_P_Stripe stripe;

	if( hContext->scaler.stripe_num == 0 )
	{
		BGRC_PACKET_P_SetScaler( hContext, &packet->src_rect, &packet->out_rect );
		hContext->scaler_header = header;
	}

	BGRC_PACKET_P_SetStriping( hContext, &packet->src_rect, &packet->out_rect, &packet->dst_point, &stripe );
	hContext->scaler.stripe_num++;

	{
		uint32_t src_pos0 = stripe.src_x | ((uint32_t) packet->src_rect.y << BGRC_M2MC(BLIT_OUTPUT_TOP_LEFT_TOP_SHIFT));
		uint32_t src_pos1 = (stripe.src_x / 2) | ((uint32_t) (packet->src_rect.y / 2) << BGRC_M2MC(BLIT_OUTPUT_TOP_LEFT_TOP_SHIFT));
		uint32_t out_pos = stripe.out_x | ((uint32_t) packet->out_rect.y << BGRC_M2MC(BLIT_OUTPUT_TOP_LEFT_TOP_SHIFT));
		uint32_t dst_pos = stripe.dst_x | ((uint32_t) packet->dst_point.y << BGRC_M2MC(BLIT_OUTPUT_TOP_LEFT_TOP_SHIFT));
		uint32_t src_size0 = packet->src_rect.height | ((uint32_t) stripe.src_width << BGRC_M2MC(BLIT_OUTPUT_SIZE_SURFACE_WIDTH_SHIFT));
		uint32_t src_size1 = ((packet->src_rect.height + 1) / 2) | ((uint32_t) ((stripe.src_width + 1) / 2) << BGRC_M2MC(BLIT_OUTPUT_SIZE_SURFACE_WIDTH_SHIFT));
		uint32_t out_size = packet->out_rect.height | ((uint32_t) stripe.out_width << BGRC_M2MC(BLIT_OUTPUT_SIZE_SURFACE_WIDTH_SHIFT));
		uint32_t stripe_width = packet->source_stripe_width >> 7;

		uint32_t format00 = s_BGRC_PACKET_P_DeviceStripedPixelFormats[BM2MC_PACKET_PixelFormat_eY8 - BM2MC_PACKET_PixelFormat_eY8];
		uint32_t format10 = s_BGRC_PACKET_P_DeviceStripedPixelFormats[BM2MC_PACKET_PixelFormat_eCb8_Cr8 - BM2MC_PACKET_PixelFormat_eY8];

		BGRC_PACKET_P_DEBUG_PRINT_CTX( "-- DestripeBlit       " );
		BGRC_PACKET_P_STORE_REG( SRC_SURFACE_FORMAT_DEF_1, format00 );
		BGRC_PACKET_P_STORE_REG( SRC_SURFACE_1_FORMAT_DEF_1, format10 ); /* same value for eCb8_Cr8 and eCr8_Cb8 */
		BGRC_PACKET_P_STORE_REG_FIELD( BLIT_CTRL, STRIPE_ENABLE, DISABLE );
		BGRC_PACKET_P_STORE_RECT_REGS( src_pos0, src_size0, src_pos1, src_size1, dst_pos, out_size, out_pos, out_size );
		BGRC_PACKET_P_STORE_REG( BLIT_SRC_STRIPE_HEIGHT_WIDTH_0, stripe_width |
			(packet->luma_stripe_height << BGRC_M2MC(BLIT_SRC_STRIPE_HEIGHT_WIDTH_0_STRIPE_HEIGHT_SHIFT)) );
		BGRC_PACKET_P_STORE_REG( BLIT_SRC_STRIPE_HEIGHT_WIDTH_1, stripe_width |
			(packet->chroma_stripe_height << BGRC_M2MC(BLIT_SRC_STRIPE_HEIGHT_WIDTH_1_STRIPE_HEIGHT_SHIFT)) );
		BGRC_PACKET_P_STORE_REG_FIELD( BLIT_HEADER, SRC_SCALER_ENABLE, ENABLE );
		BGRC_PACKET_P_DEBUG_PRINT( "\n                      " );
		BGRC_PACKET_P_STORE_REG_FIELD( SCALER_CTRL, HORIZ_SCALER_ENABLE, ENABLE );
		BGRC_PACKET_P_STORE_REG_FIELD( SCALER_CTRL, VERT_SCALER_ENABLE, ENABLE );
		BGRC_PACKET_P_STORE_REG_FIELD_COMP( SCALER_CTRL, SCALER_ORDER, VERT_THEN_HORIZ, HORIZ_THEN_VERT, stripe.src_width >= stripe.out_width );
		BGRC_PACKET_P_STORE_SCALE_REGS( HORIZ, 0, stripe.hor_phase, hContext->scaler.hor_step );
		BGRC_PACKET_P_STORE_SCALE_REGS( HORIZ, 1, stripe.hor_phase / 2, hContext->scaler.hor_step / 2 );
		BGRC_PACKET_P_STORE_SCALE_REGS( VERT, 0, hContext->scaler.ver_phase, hContext->scaler.ver_step );
		BGRC_PACKET_P_STORE_SCALE_REGS( VERT, 1, hContext->scaler.ver_phase / 2, hContext->scaler.ver_step / 2 );
		BGRC_PACKET_P_CheckAndForceDestDisable( hContext );
		BGRC_PACKET_P_DEBUG_PRINT( "\n" );
	}

#else /* #ifdef BGRC_PACKET_P_SW_DESTRIPE */
	BM2MC_PACKET_PacketDestripeBlit *packet = (BM2MC_PACKET_PacketDestripeBlit *) header;
	uint32_t src_x0 = packet->src_rect.x;
	uint32_t src_y0 = packet->src_rect.y;
	uint32_t src_x1 = src_x0 / 2;
	uint32_t src_y1 = src_y0 / 2;
	uint32_t src_width0 = packet->src_rect.width;
	uint32_t src_height0 = packet->src_rect.height;
	uint32_t src_width1 = (src_width0 > 1) ? src_width0 / 2 : 1;
	uint32_t src_height1 = (src_height0 > 1) ? src_height0 / 2 : 1;

	uint32_t src_pos0 = src_x0 | (src_y0 << BGRC_M2MC(BLIT_OUTPUT_TOP_LEFT_TOP_SHIFT));
	uint32_t src_pos1 = src_x1 | (src_y1 << BGRC_M2MC(BLIT_OUTPUT_TOP_LEFT_TOP_SHIFT));
	uint32_t out_pos = packet->out_rect.x | ((uint32_t) packet->out_rect.y << BGRC_M2MC(BLIT_OUTPUT_TOP_LEFT_TOP_SHIFT));
	uint32_t dst_pos = packet->dst_point.x | ((uint32_t) packet->dst_point.y << BGRC_M2MC(BLIT_OUTPUT_TOP_LEFT_TOP_SHIFT));
	uint32_t src_size0 = src_height0 | (src_width0 << BGRC_M2MC(BLIT_OUTPUT_SIZE_SURFACE_WIDTH_SHIFT));
	uint32_t src_size1 = src_height1 | (src_width1 << BGRC_M2MC(BLIT_OUTPUT_SIZE_SURFACE_WIDTH_SHIFT));
	uint32_t out_size = packet->out_rect.height | ((uint32_t) packet->out_rect.width << BGRC_M2MC(BLIT_OUTPUT_SIZE_SURFACE_WIDTH_SHIFT));
	uint32_t stripe_width = packet->source_stripe_width >> 7;
	uint32_t format00 = s_BGRC_PACKET_P_DeviceStripedPixelFormats[BM2MC_PACKET_PixelFormat_eY8 - BM2MC_PACKET_PixelFormat_eY8];
	uint32_t format10 = s_BGRC_PACKET_P_DeviceStripedPixelFormats[BM2MC_PACKET_PixelFormat_eCb8_Cr8 - BM2MC_PACKET_PixelFormat_eY8];

	hContext->b420Src = true;
	BGRC_PACKET_P_SetScaler( hContext, &packet->src_rect, &packet->out_rect );

	BGRC_PACKET_P_DEBUG_PRINT_CTX( "-- DestripeBlit       " );
	BGRC_PACKET_P_STORE_REG( SRC_SURFACE_FORMAT_DEF_1, format00 );
	BGRC_PACKET_P_STORE_REG( SRC_SURFACE_1_FORMAT_DEF_1, format10 ); /* same value for eCb8_Cr8 and eCr8_Cb8 */
	BGRC_PACKET_P_STORE_REG_FIELD_COMP( BLIT_CTRL, STRIPE_ENABLE, DISABLE, ENABLE, hContext->scaler.stripe_count > 1 );
	BGRC_PACKET_P_STORE_RECT_REGS( src_pos0, src_size0, src_pos1, src_size1, dst_pos, out_size, out_pos, out_size );
	BGRC_PACKET_P_STORE_REG( BLIT_SRC_STRIPE_HEIGHT_WIDTH_0, stripe_width |
		(packet->luma_stripe_height << BGRC_M2MC(BLIT_SRC_STRIPE_HEIGHT_WIDTH_0_STRIPE_HEIGHT_SHIFT)) );
	BGRC_PACKET_P_STORE_REG( BLIT_SRC_STRIPE_HEIGHT_WIDTH_1, stripe_width |
		(packet->chroma_stripe_height << BGRC_M2MC(BLIT_SRC_STRIPE_HEIGHT_WIDTH_1_STRIPE_HEIGHT_SHIFT)) );
	BGRC_PACKET_P_STORE_REG( BLIT_INPUT_STRIPE_WIDTH, hContext->scaler.input_stripe_width );
	BGRC_PACKET_P_STORE_REG( BLIT_OUTPUT_STRIPE_WIDTH, hContext->scaler.output_stripe_width );
	BGRC_PACKET_P_STORE_REG( BLIT_STRIPE_OVERLAP, hContext->scaler.stripe_overlap );
	BGRC_PACKET_P_STORE_REG_FIELD( BLIT_HEADER, SRC_SCALER_ENABLE, ENABLE );
	BGRC_PACKET_P_DEBUG_PRINT( "\n                      " );
	BGRC_PACKET_P_STORE_REG_FIELD( SCALER_CTRL, HORIZ_SCALER_ENABLE, ENABLE );
	BGRC_PACKET_P_STORE_REG_FIELD( SCALER_CTRL, VERT_SCALER_ENABLE, ENABLE );
	BGRC_PACKET_P_STORE_REG_FIELD_COMP( SCALER_CTRL, SCALER_ORDER, VERT_THEN_HORIZ, HORIZ_THEN_VERT, packet->src_rect.width >= packet->out_rect.width );
	BGRC_PACKET_P_STORE_SCALE_REGS( HORIZ, 0, hContext->scaler.hor_phase, hContext->scaler.hor_step );
	BGRC_PACKET_P_STORE_SCALE_REGS( VERT, 0, hContext->scaler.ver_phase, hContext->scaler.ver_step );
	BGRC_PACKET_P_SetScaleFor420Src(hContext);
	BGRC_PACKET_P_CheckAndForceDestDisable( hContext );
	BGRC_PACKET_P_DEBUG_PRINT( "\n" );
#endif /* #ifdef BGRC_PACKET_P_SW_DESTRIPE */
}

/***************************************************************************/
#define BGRC_PACKET_P_RESET_COLOR_BLEND { \
	BM2MC_PACKET_BlendFactor_eSourceColor, BM2MC_PACKET_BlendFactor_eOne, false, \
	BM2MC_PACKET_BlendFactor_eZero, BM2MC_PACKET_BlendFactor_eZero, false, BM2MC_PACKET_BlendFactor_eZero }

#define BGRC_PACKET_P_RESET_ALPHA_BLEND { \
	BM2MC_PACKET_BlendFactor_eSourceAlpha, BM2MC_PACKET_BlendFactor_eOne, false, \
	BM2MC_PACKET_BlendFactor_eZero, BM2MC_PACKET_BlendFactor_eZero, false, BM2MC_PACKET_BlendFactor_eZero }

#define BGRC_PACKET_P_RESET_ROP_VECTOR    0xCC

/***************************************************************************/
void BGRC_PACKET_P_ResetState( BGRC_PacketContext_Handle hContext )
{
	BM2MC_PACKET_PacketSourceNone src_packet;
	BM2MC_PACKET_PacketSourceControl src_control_packet;
	BM2MC_PACKET_PacketDestinationNone dst_packet;
	BM2MC_PACKET_PacketDestinationControl dst_control_packet;
	BM2MC_PACKET_PacketOutputFeeder out_packet;
	BM2MC_PACKET_PacketBlend blend_packet;
	BM2MC_PACKET_PacketRop rop_packet;
	BM2MC_PACKET_PacketFilter filter_packet;
	BM2MC_PACKET_PacketSourcePalette palette_packet;
	BM2MC_PACKET_PacketFillBlit fill_packet;
	BM2MC_PACKET_Blend color_blend = BGRC_PACKET_P_RESET_COLOR_BLEND;
	BM2MC_PACKET_Blend alpha_blend = BGRC_PACKET_P_RESET_ALPHA_BLEND;

	/* Using sw pkts to set the shadow registers to defaut values.
	 * Note: no hw pkt is caused because we will not set execute bit
	 */

	BGRC_PACKET_P_DEBUG_PRINT_CTX( "-- Reset              \n" );
	BKNI_Memset( hContext->stored_registers, 0, sizeof (uint32_t) * BGRC_PACKET_P_REGISTER_COUNT );

	/* set default surfaces */
	BM2MC_PACKET_INIT( &src_packet, SourceNone, false );
	BGRC_PACKET_P_ProcSwPktSourceNone( hContext, (BM2MC_PACKET_Header *) &src_packet );

	BM2MC_PACKET_INIT( &src_control_packet, SourceControl, false );
	src_control_packet.zero_pad = false;
	src_control_packet.chroma_filter = true;
	src_control_packet.linear_destripe = false;
	BGRC_PACKET_P_ProcSwPktSourceControl( hContext, (BM2MC_PACKET_Header *) &src_control_packet );

	BM2MC_PACKET_INIT( &dst_packet, DestinationNone, false );
	BGRC_PACKET_P_ProcSwPktDestinationNone( hContext, (BM2MC_PACKET_Header *) &dst_packet );

	BM2MC_PACKET_INIT( &dst_control_packet, DestinationControl, false );
	dst_control_packet.zero_pad = false;
	dst_control_packet.chroma_filter = true;
	BGRC_PACKET_P_ProcSwPktDestinationControl( hContext, (BM2MC_PACKET_Header *) &dst_control_packet );

	BM2MC_PACKET_INIT( &out_packet, OutputFeeder, false );
	out_packet.plane.address = 0; /*ulDummySurOffset;*/
	out_packet.plane.pitch = 4;
	out_packet.plane.format = BM2MC_PACKET_PixelFormat_eA8_R8_G8_B8;
	out_packet.plane.width = 1;
	out_packet.plane.height = 1;
	BGRC_PACKET_P_ProcSwPktOutputFeeder( hContext, (BM2MC_PACKET_Header *) &out_packet );

	/* set default blend - source pixel */
	BM2MC_PACKET_INIT( &blend_packet, Blend, false );
	blend_packet.color_blend = color_blend;
	blend_packet.alpha_blend = alpha_blend;
	blend_packet.color = 0;
	BGRC_PACKET_P_ProcSwPktBlend( hContext, (BM2MC_PACKET_Header *) &blend_packet );

	/* set default ROP - source copy */
	BM2MC_PACKET_INIT( &rop_packet, Rop, false );
	rop_packet.rop = BGRC_PACKET_P_RESET_ROP_VECTOR;
	rop_packet.pattern0 = 0;
	rop_packet.pattern1 = 0;
	rop_packet.color0 = 0;
	rop_packet.color1 = 0;
	BGRC_PACKET_P_ProcSwPktRop( hContext, (BM2MC_PACKET_Header *) &rop_packet );

	/* set default filter - bilinear */
	BM2MC_PACKET_INIT( &filter_packet, Filter, false );
	filter_packet.hor = s_BGRC_PACKET_P_DeviceFilter_Bilinear;
	filter_packet.ver = s_BGRC_PACKET_P_DeviceFilter_Bilinear;
	BGRC_PACKET_P_ProcSwPktFilter( hContext, (BM2MC_PACKET_Header *) &filter_packet );

	/* set default palette */
	BM2MC_PACKET_INIT( &palette_packet, SourcePalette, false );
	palette_packet.address = 0;
	BGRC_PACKET_P_ProcSwPktSourcePalette( hContext, (BM2MC_PACKET_Header *) &palette_packet );

	/* set default rectangle*/
	BM2MC_PACKET_INIT( &fill_packet, FillBlit, false );
	fill_packet.rect.x = 0;
	fill_packet.rect.y = 0;
	fill_packet.rect.width = 1;
	fill_packet.rect.height = 1;
	BGRC_PACKET_P_ProcSwPktFillBlit( hContext, (BM2MC_PACKET_Header *) &fill_packet );

	BKNI_Memset( &hContext->destripe_fixed_scale, 0, sizeof (BM2MC_PACKET_PacketDestripeFixedScale) );
	BKNI_Memset( &hContext->fixed_scale, 0, sizeof (BM2MC_PACKET_PacketFixedScale) );

	hContext->src_format0 = 0;
	hContext->out_format0 = 0;
	hContext->b420Src = false;
	hContext->bResetState = true;

#if defined(BCHP_M2MC_BLIT_CTRL_BLOCK_AUTO_SPLIT_FIFO_MASK)
	BGRC_PACKET_P_STORE_REG_FIELD( BLIT_CTRL, BLOCK_AUTO_SPLIT_FIFO, ENABLE );
#endif
}

/***************************************************************************/
static void BGRC_PACKET_P_ProcSwPktResetState( BGRC_PacketContext_Handle hContext, BM2MC_PACKET_Header *header )
{
	BSTD_UNUSED(header);
	BGRC_PACKET_P_ResetState( hContext );
}

/***************************************************************************/
static void BGRC_PACKET_P_ProcSwPktSaveState( BGRC_PacketContext_Handle hContext, BM2MC_PACKET_Header *header )
{
	BSTD_UNUSED(header);
	BKNI_Memcpy( hContext->saved_registers, hContext->stored_registers, BGRC_PACKET_P_REGISTER_COUNT * sizeof (uint32_t) );
	hContext->saved_destripe_fixed_scale = hContext->destripe_fixed_scale;
	hContext->saved_fixed_scale = hContext->fixed_scale;
	hContext->saved_src_format0 = hContext->src_format0;
	hContext->saved_out_format0 = hContext->out_format0;
	hContext->saved_b420Src = hContext->b420Src;
	hContext->saved_bDestForceDisabled = hContext->bDestForceDisabled;
	hContext->saved_bNeedDestForBlend = hContext->bNeedDestForBlend;
	hContext->saved_bBlitInvalid = hContext->bBlitInvalid;
	hContext->saved_stSurInvalid.ulInts = hContext->stSurInvalid.ulInts;

#if BGRC_PACKET_P_VERIFY_SURFACE_RECTANGLE && BDBG_DEBUG_BUILD
	hContext->saved_SRC_surface_width = hContext->SRC_surface_width;
	hContext->saved_SRC_surface_height = hContext->SRC_surface_height;
	hContext->saved_SRC_surface_format = hContext->SRC_surface_format;
	hContext->saved_SRC_surface_pitch = hContext->SRC_surface_pitch;
	hContext->saved_DEST_surface_width = hContext->DEST_surface_width;
	hContext->saved_DEST_surface_height = hContext->DEST_surface_height;
	hContext->saved_DEST_surface_format = hContext->DEST_surface_format;
	hContext->saved_DEST_surface_pitch = hContext->DEST_surface_pitch;
	hContext->saved_OUTPUT_surface_width = hContext->OUTPUT_surface_width;
	hContext->saved_OUTPUT_surface_height = hContext->OUTPUT_surface_height;
	hContext->saved_OUTPUT_surface_format = hContext->OUTPUT_surface_format;
	hContext->saved_OUTPUT_surface_pitch = hContext->OUTPUT_surface_pitch;
#endif
}

/***************************************************************************/
static void BGRC_PACKET_P_ProcSwPktRestoreState( BGRC_PacketContext_Handle hContext, BM2MC_PACKET_Header *header )
{
	BSTD_UNUSED(header);
	BKNI_Memcpy( hContext->stored_registers, hContext->saved_registers, BGRC_PACKET_P_REGISTER_COUNT * sizeof (uint32_t) );
	hContext->destripe_fixed_scale = hContext->saved_destripe_fixed_scale;
	hContext->fixed_scale = hContext->saved_fixed_scale;
	hContext->src_format0 = hContext->saved_src_format0;
	hContext->out_format0 = hContext->saved_out_format0;
	hContext->b420Src = hContext->saved_b420Src;
	hContext->bResetState = true;
	hContext->bDestForceDisabled = hContext->saved_bDestForceDisabled;
	hContext->bNeedDestForBlend = hContext->saved_bNeedDestForBlend;
	hContext->bBlitInvalid = hContext->saved_bBlitInvalid;
	hContext->stSurInvalid.ulInts = hContext->saved_stSurInvalid.ulInts;

#if BGRC_PACKET_P_VERIFY_SURFACE_RECTANGLE && BDBG_DEBUG_BUILD
	hContext->SRC_surface_width = hContext->saved_SRC_surface_width;
	hContext->SRC_surface_height = hContext->saved_SRC_surface_height;
	hContext->SRC_surface_format = hContext->saved_SRC_surface_format;
	hContext->SRC_surface_pitch = hContext->saved_SRC_surface_pitch;
	hContext->DEST_surface_width = hContext->saved_DEST_surface_width;
	hContext->DEST_surface_height = hContext->saved_DEST_surface_height;
	hContext->DEST_surface_format = hContext->saved_DEST_surface_format;
	hContext->DEST_surface_pitch = hContext->saved_DEST_surface_pitch;
	hContext->OUTPUT_surface_width = hContext->saved_OUTPUT_surface_width;
	hContext->OUTPUT_surface_height = hContext->saved_OUTPUT_surface_height;
	hContext->OUTPUT_surface_format = hContext->saved_OUTPUT_surface_format;
	hContext->OUTPUT_surface_pitch = hContext->saved_OUTPUT_surface_pitch;
#endif
}

/***************************************************************************/
static uint32_t *BGRC_PACKET_P_ProcessSwPaket(
	BGRC_PacketContext_Handle hContext,
	BM2MC_PACKET_Header *pHeader,
	bool *bSoftwareStriping )
{
	uint32_t *pPacket = (uint32_t *) pHeader;
	*bSoftwareStriping = false;

	switch( pHeader->type )
	{
	case 0:
		BDBG_ASSERT(false);
		BGRC_PACKET_P_DEBUG_PRINT( "-- EndOfBuffer        \n" );
		pPacket = (uint32_t *) (hContext->pSwPktFifoBase - pHeader->size * sizeof (uint32_t));
		break;
	case BM2MC_PACKET_PacketType_eSourceFeeder:
		BGRC_PACKET_P_ProcSwPktSourceFeeder( hContext, pHeader );
		break;
	case BM2MC_PACKET_PacketType_eSourceFeeders:
		BGRC_PACKET_P_ProcSwPktSourceFeeders( hContext, pHeader );
		break;
	case BM2MC_PACKET_PacketType_eStripedSourceFeeders:
		BGRC_PACKET_P_ProcSwPktStripedSourceFeeders( hContext, pHeader );
		break;
	case BM2MC_PACKET_PacketType_eSourceColor:
		BGRC_PACKET_P_ProcSwPktSourceColor( hContext, pHeader );
		break;
	case BM2MC_PACKET_PacketType_eSourceNone:
		BGRC_PACKET_P_ProcSwPktSourceNone( hContext, pHeader );
		break;
	case BM2MC_PACKET_PacketType_eSourceControl:
		BGRC_PACKET_P_ProcSwPktSourceControl( hContext, pHeader );
		break;
	case BM2MC_PACKET_PacketType_eDestinationFeeder:
		BGRC_PACKET_P_ProcSwPktDestinationFeeder( hContext, pHeader );
		break;
	case BM2MC_PACKET_PacketType_eDestinationColor:
		BGRC_PACKET_P_ProcSwPktDestinationColor( hContext, pHeader );
		break;
	case BM2MC_PACKET_PacketType_eDestinationNone:
		BGRC_PACKET_P_ProcSwPktDestinationNone( hContext, pHeader );
		break;
	case BM2MC_PACKET_PacketType_eDestinationControl:
		BGRC_PACKET_P_ProcSwPktDestinationControl( hContext, pHeader );
		break;
	case BM2MC_PACKET_PacketType_eOutputFeeder:
		BGRC_PACKET_P_ProcSwPktOutputFeeder( hContext, pHeader );
		break;
	case BM2MC_PACKET_PacketType_eOutputControl:
		BGRC_PACKET_P_ProcSwPktOutputControl( hContext, pHeader );
		break;
	case BM2MC_PACKET_PacketType_eBlend:
		BGRC_PACKET_P_ProcSwPktBlend( hContext, pHeader );
		break;
	case BM2MC_PACKET_PacketType_eBlendColor:
		BGRC_PACKET_P_ProcSwPktBlendColor( hContext, pHeader );
		break;
	case BM2MC_PACKET_PacketType_eRop:
		BGRC_PACKET_P_ProcSwPktRop( hContext, pHeader );
		break;
	case BM2MC_PACKET_PacketType_eSourceColorkey:
		BGRC_PACKET_P_ProcSwPktSourceColorkey( hContext, pHeader );
		break;
	case BM2MC_PACKET_PacketType_eSourceColorkeyEnable:
		BGRC_PACKET_P_ProcSwPktSourceColorkeyEnable( hContext, pHeader );
		break;
	case BM2MC_PACKET_PacketType_eDestinationColorkey:
		BGRC_PACKET_P_ProcSwPktDestinationColorkey( hContext, pHeader );
		break;
	case BM2MC_PACKET_PacketType_eDestinationColorkeyEnable:
		BGRC_PACKET_P_ProcSwPktDestinationColorkeyEnable( hContext, pHeader );
		break;
	case BM2MC_PACKET_PacketType_eFilter:
		BGRC_PACKET_P_ProcSwPktFilter( hContext, pHeader );
		break;
	case BM2MC_PACKET_PacketType_eFilterEnable:
		BGRC_PACKET_P_ProcSwPktFilterEnable( hContext, pHeader );
		break;
	case BM2MC_PACKET_PacketType_eFilterControl:
		BGRC_PACKET_P_ProcSwPktFilterControl( hContext, pHeader );
		break;
	case BM2MC_PACKET_PacketType_eSourceColorMatrix:
		BGRC_PACKET_P_ProcSwPktSourceColorMatrix( hContext, pHeader );
		break;
	case BM2MC_PACKET_PacketType_eSourceColorMatrixEnable:
		BGRC_PACKET_P_ProcSwPktSourceColorMatrixEnable( hContext, pHeader );
		break;
	case BM2MC_PACKET_PacketType_eSourcePalette:
		BGRC_PACKET_P_ProcSwPktSourcePalette( hContext, pHeader );
		break;
	case BM2MC_PACKET_PacketType_eMirror:
		BGRC_PACKET_P_ProcSwPktMirror( hContext, pHeader );
		break;
	case BM2MC_PACKET_PacketType_eFixedScale:
		BGRC_PACKET_P_ProcSwPktFixedScale( hContext, pHeader );
		break;
	case BM2MC_PACKET_PacketType_eDestripeFixedScale:
		BGRC_PACKET_P_ProcSwPktDestripeFixedScale( hContext, pHeader );
		break;
	case BM2MC_PACKET_PacketType_eAlphaPremultiply:
		BGRC_PACKET_P_ProcSwPktAlphaPremultiply( hContext, pHeader );
		break;
	case BM2MC_PACKET_PacketType_eAlphaDemultiply:
		BGRC_PACKET_P_ProcSwPktAlphaDemultiply( hContext, pHeader );
		break;
	case BM2MC_PACKET_PacketType_eDestAlphaPremultiply:
		BGRC_PACKET_P_ProcSwPktDestAlphaPremultiply( hContext, pHeader );
		break;
	case BM2MC_PACKET_PacketType_eFillBlit:
	    {
			BM2MC_PACKET_PacketFillBlit *pPacket = (BM2MC_PACKET_PacketFillBlit *) pHeader;
			hContext->bBlitInvalid = false;
			BGRC_PACKET_P_OUT_PXL_ALIGN(pPacket->rect.x, pPacket->rect.width, pPacket->rect.y, pPacket->rect.height);
			if ((!hContext->bBlitInvalid) && (0==hContext->stSurInvalid.ulInts)) {
				BGRC_PACKET_P_ProcSwPktFillBlit( hContext, pHeader );
			}
			break;
		}
	case BM2MC_PACKET_PacketType_eCopyBlit:
	    {
			BM2MC_PACKET_PacketCopyBlit *pPacket = (BM2MC_PACKET_PacketCopyBlit *) pHeader;
			hContext->bBlitInvalid = false;
			BGRC_PACKET_P_SRC_OUT_PXL_ALIGN(pPacket->src_rect.x, pPacket->src_rect.width, pPacket->out_point.x,
				pPacket->src_rect.y, pPacket->src_rect.height, pPacket->out_point.y);
			if ((!hContext->bBlitInvalid) && (0==hContext->stSurInvalid.ulInts)) {
				BGRC_PACKET_P_ProcSwPktCopyBlit( hContext, pHeader );
			}
			break;
		}
	case BM2MC_PACKET_PacketType_eBlendBlit:
	    {
			BM2MC_PACKET_PacketBlendBlit *pPacket = (BM2MC_PACKET_PacketBlendBlit *) pHeader;
			hContext->bBlitInvalid = false;
			BGRC_PACKET_P_SRC_DST_OUT_PXL_ALIGN(pPacket->src_rect.x, pPacket->src_rect.width, pPacket->dst_point.x, pPacket->out_point.x,
				pPacket->src_rect.y, pPacket->src_rect.height, pPacket->dst_point.y, pPacket->out_point.y);
			if ((!hContext->bBlitInvalid) && (0==hContext->stSurInvalid.ulInts)) {
				BGRC_PACKET_P_ProcSwPktBlendBlit( hContext, pHeader );
			}
			break;
		}
	case BM2MC_PACKET_PacketType_eScaleBlit:
		{
			BM2MC_PACKET_PacketScaleBlit *pPacket = (BM2MC_PACKET_PacketScaleBlit *) pHeader;
			hContext->bBlitInvalid = false;
			if (pPacket->src_rect.width < BGRC_P_MIN_WIDTH_WITH_VERT_SCALE && pPacket->src_rect.height != pPacket->out_rect.height ) {
				BDBG_WRN(("ScaleBlit with source width %d < %d, might output bad pixels!", pPacket->src_rect.width, BGRC_P_MIN_WIDTH_WITH_VERT_SCALE));
			}
			BGRC_PACKET_P_SRC_PXL_ALIGN(pPacket->src_rect.x, pPacket->src_rect.width, pPacket->src_rect.y, pPacket->src_rect.height);
			BGRC_PACKET_P_OUT_PXL_ALIGN(pPacket->out_rect.x, pPacket->out_rect.width, pPacket->out_rect.y, pPacket->out_rect.height);
			if ((!hContext->bBlitInvalid) && (0==hContext->stSurInvalid.ulInts)) {
				BGRC_PACKET_P_SetScaler( hContext, &pPacket->src_rect, &pPacket->out_rect );
				/* use sw striping if scale down max exceeded */
				if ((!hContext->b420Src) &&
					((BGRC_PACKET_P_GET_REG_FIELD(SRC_SURFACE_FORMAT_DEF_1, FORMAT_TYPE) == M2MC_FT_YCbCr422) ||
					 (BGRC_PACKET_P_GET_REG(BLIT_CTRL) & BGRC_M2MC(BLIT_CTRL_OUTPUT_H_DIRECTION_MASK)) ||
					 (hContext->scaler.ver_step > (4 << BGRC_PACKET_P_SCALER_STEP_FRAC_BITS))))
				{
					BGRC_PACKET_P_ProcSwPktStripeBlit( hContext, &pPacket->src_rect, &pPacket->out_rect,
						(BM2MC_PACKET_Point *) (void *) &pPacket->out_rect );
					hContext->scaler_header = pHeader;
					*bSoftwareStriping = true;
				}
				else {
					BGRC_PACKET_P_ProcSwPktScaleBlit( hContext, pHeader );
				}
			}
		}
		break;
	case BM2MC_PACKET_PacketType_eScaleBlendBlit:
	{
		BM2MC_PACKET_PacketScaleBlendBlit *pPacket = (BM2MC_PACKET_PacketScaleBlendBlit *) pHeader;
		hContext->bBlitInvalid = false;
		if (pPacket->src_rect.width < BGRC_P_MIN_WIDTH_WITH_VERT_SCALE && pPacket->src_rect.height != pPacket->out_rect.height ) {
			BDBG_WRN(("ScaleBlendBlit with source width %d < %d, might output bad pixels!", pPacket->src_rect.width, BGRC_P_MIN_WIDTH_WITH_VERT_SCALE));
		}
		BGRC_PACKET_P_SRC_PXL_ALIGN(pPacket->src_rect.x,  pPacket->src_rect.width, pPacket->src_rect.y,  pPacket->src_rect.height);
		BGRC_PACKET_P_DST_OUT_PXL_ALIGN(pPacket->out_rect.x, pPacket->out_rect.width, pPacket->dst_point.x,
			pPacket->out_rect.y, pPacket->out_rect.height, pPacket->dst_point.y);
		if (!hContext->bBlitInvalid && (0==hContext->stSurInvalid.ulInts)) {
			BGRC_PACKET_P_ProcSwPktScaleBlendBlit( hContext, pHeader );
		}
		break;
	}
	case BM2MC_PACKET_PacketType_eUpdateScaleBlit:
	{
		BM2MC_PACKET_PacketUpdateScaleBlit *pPacket = (BM2MC_PACKET_PacketUpdateScaleBlit *) pHeader;
		hContext->bBlitInvalid = false;
		BGRC_PACKET_P_SRC_PXL_ALIGN(pPacket->src_rect.x, pPacket->src_rect.width, pPacket->src_rect.y, pPacket->src_rect.height);
		BGRC_PACKET_P_OUT_PXL_ALIGN(pPacket->out_rect.x, pPacket->out_rect.width, pPacket->out_rect.y, pPacket->out_rect.height);
		if (!hContext->bBlitInvalid && (0==hContext->stSurInvalid.ulInts)) {
			BGRC_PACKET_P_ProcSwPktUpdateScaleBlit( hContext, pHeader );
		}
		break;
	}
	case BM2MC_PACKET_PacketType_eDestripeBlit:
		/* Deprecated */
		BGRC_PACKET_P_ProcSwPktDestripeBlit( hContext, pHeader );
		break;
	case BM2MC_PACKET_PacketType_eResetState:
		BGRC_PACKET_P_ProcSwPktResetState( hContext, pHeader );
		break;
	case BM2MC_PACKET_PacketType_eSaveState:
		BGRC_PACKET_P_ProcSwPktSaveState( hContext, pHeader );
		break;
	case BM2MC_PACKET_PacketType_eRestoreState:
		BGRC_PACKET_P_ProcSwPktRestoreState( hContext, pHeader );
		break;
	default:
		break;
	}

	return (uint32_t *) ((uint8_t *) pPacket + pHeader->size * sizeof (uint32_t));
}

#if BGRC_PACKET_P_VERIFY_SURFACE_RECTANGLE && BDBG_DEBUG_BUILD

/***************************************************************************/
#define BGRC_PACKET_P_GET_SURFACE_BPP( surface ) (( \
	BGRC_PACKET_P_GET_REG_FIELD_SHIFT(surface##_FORMAT_DEF_1, CH0_NUM_BITS) + \
	BGRC_PACKET_P_GET_REG_FIELD_SHIFT(surface##_FORMAT_DEF_1, CH1_NUM_BITS) + \
	BGRC_PACKET_P_GET_REG_FIELD_SHIFT(surface##_FORMAT_DEF_1, CH2_NUM_BITS) + \
	BGRC_PACKET_P_GET_REG_FIELD_SHIFT(surface##_FORMAT_DEF_1, CH3_NUM_BITS)) / \
	((BGRC_PACKET_P_GET_REG_FIELD(surface##_FORMAT_DEF_1, FORMAT_TYPE) == M2MC_FT_YCbCr422) ? 2 : 1))

/***************************************************************************/
#define BGRC_PACKET_P_VERIFY_RECTANGLE_SCALE() \
{ \
	if( hContext->scaler.hor_step > (BGRC_P_SCALE_DOWN_MAX_X << BGRC_PACKET_P_SCALER_STEP_FRAC_BITS) ) \
	{ \
		BDBG_WRN(( "Horizontal down scale factor larger than %dx (%d->%d)", BGRC_P_SCALE_DOWN_MAX_X, \
			BGRC_PACKET_P_GET_REG(BLIT_SRC_SIZE) >> BGRC_M2MC(BLIT_OUTPUT_SIZE_SURFACE_WIDTH_SHIFT), \
			BGRC_PACKET_P_GET_REG(BLIT_OUTPUT_SIZE) >> BGRC_M2MC(BLIT_OUTPUT_SIZE_SURFACE_WIDTH_SHIFT) )); \
		hContext->scaler.hor_step = BGRC_P_SCALE_DOWN_MAX_X << BGRC_PACKET_P_SCALER_STEP_FRAC_BITS; \
		BGRC_PACKET_P_STORE_REG( HORIZ_SCALER_STEP, BGRC_P_SCALE_DOWN_MAX_X << BGRC_PACKET_P_SCALER_STEP_FRAC_BITS ); \
		/* hContext->bBlitInvalid = true; */\
	} \
	if( hContext->scaler.ver_step > (BGRC_P_SCALE_DOWN_MAX_Y << BGRC_PACKET_P_SCALER_STEP_FRAC_BITS) ) \
	{ \
		BDBG_WRN(( "Vertical down scale factor larger than %dx (%d->%d)", BGRC_P_SCALE_DOWN_MAX_Y, \
			BGRC_PACKET_P_GET_REG(BLIT_SRC_SIZE) & 0xFFFF, BGRC_PACKET_P_GET_REG(BLIT_OUTPUT_SIZE) & 0xFFFF)); \
		hContext->scaler.ver_step = BGRC_P_SCALE_DOWN_MAX_Y << BGRC_PACKET_P_SCALER_STEP_FRAC_BITS; \
		BGRC_PACKET_P_STORE_REG( VERT_SCALER_STEP, BGRC_P_SCALE_DOWN_MAX_Y << BGRC_PACKET_P_SCALER_STEP_FRAC_BITS ); \
		/* hContext->bBlitInvalid = true; */\
	} \
	if( BGRC_PACKET_P_GET_REG(BLIT_SRC_SIZE) & (~(BGRC_M2MC(BLIT_OUTPUT_SIZE_SURFACE_WIDTH_MASK) | BGRC_M2MC(BLIT_OUTPUT_SIZE_SURFACE_HEIGHT_MASK))) ) \
	{ \
		BDBG_ERR(( "Source surface rectangle is larger than 8191 (%dx%d), blit dropped", \
			BGRC_PACKET_P_GET_REG(BLIT_SRC_SIZE) >> BGRC_M2MC(BLIT_OUTPUT_SIZE_SURFACE_WIDTH_SHIFT), \
			BGRC_PACKET_P_GET_REG(BLIT_SRC_SIZE) & 0xFFFF )); \
		hContext->bBlitInvalid = true; \
	} \
	if( BGRC_PACKET_P_GET_REG(BLIT_OUTPUT_SIZE) & (~(BGRC_M2MC(BLIT_OUTPUT_SIZE_SURFACE_WIDTH_MASK) | BGRC_M2MC(BLIT_OUTPUT_SIZE_SURFACE_HEIGHT_MASK))) ) \
	{ \
		BDBG_ERR(( "Output surface rectangle is larger than 8191 (%dx%d), blit dropped", \
			BGRC_PACKET_P_GET_REG(BLIT_OUTPUT_SIZE) >> BGRC_M2MC(BLIT_OUTPUT_SIZE_SURFACE_WIDTH_SHIFT), \
			BGRC_PACKET_P_GET_REG(BLIT_OUTPUT_SIZE) & 0xFFFF )); \
		hContext->bBlitInvalid = true; \
	} \
}

/***************************************************************************/
#define BGRC_PACKET_P_VERIFY_RECTANGLE_WITH_BOUNDS( surface, num, pos, dim, mask ) \
{ \
	if( BGRC_PACKET_P_GET_REG(surface##_FEEDER_ENABLE) ) \
	{ \
		uint32_t surface_offset = BGRC_PACKET_P_GET_REG(surface##_SURFACE_ADDR_0); \
		if( surface_offset != hGrc->ulDummySurOffset ) \
		{ \
			if( surface_offset ) \
			{ \
				uint32_t pitch = hContext->surface##_surface_pitch; \
				uint32_t x = BGRC_PACKET_P_GET_REG_FIELD_SHIFT(BLIT_##surface##_##pos, LEFT); \
				uint32_t y = BGRC_PACKET_P_GET_REG_FIELD_SHIFT(BLIT_##surface##_##pos, TOP); \
				uint32_t w = BGRC_PACKET_P_GET_REG_FIELD_SHIFT(BLIT_##surface##_##dim, SURFACE_WIDTH); \
				uint32_t h = BGRC_PACKET_P_GET_REG_FIELD_SHIFT(BLIT_##surface##_##dim, SURFACE_HEIGHT); \
				uint32_t start_offset = surface_offset + y * pitch; \
				uint32_t end_offset = surface_offset + (y + h) * pitch; \
\
				if( start_offset < hContext->create_settings.memory_bounds.offset ) \
				{ \
					BDBG_ERR(( "%6s context memory violation (bounds=0x%lx-0x%lx start=%08x)   sur (off=%08x x=%4d y=%4d w=%4d h=%4d), blit dropped", \
						#surface, (unsigned long)hContext->create_settings.memory_bounds.offset, \
						(unsigned long)(hContext->create_settings.memory_bounds.offset) + hContext->create_settings.memory_bounds.size, \
						start_offset, surface_offset, x, y, w, h )); \
					hContext->bBlitInvalid = true; \
				} \
\
				if( end_offset > hContext->create_settings.memory_bounds.offset + hContext->create_settings.memory_bounds.size ) \
				{ \
					BDBG_ERR(( "%6s context memory violation (bounds=0x%lx-0x%lx   end=%08x)   sur (off=%08x x=%4d y=%4d w=%4d h=%4d), blit dropped", \
						#surface, (unsigned long)hContext->create_settings.memory_bounds.offset, \
						(unsigned long)(hContext->create_settings.memory_bounds.offset) + hContext->create_settings.memory_bounds.size, \
						end_offset, surface_offset, x, y, w, h )); \
					hContext->bBlitInvalid = true; \
				} \
			} \
			else if( (mask) ) \
			{ \
				if( (BGRC_PACKET_P_GET_REG(surface##_SURFACE_FORMAT_DEF_3) & (mask)) != (mask) ) \
				{ \
					BDBG_ERR(( "%6s feeder violates memory at offset 0, blit dropped", #surface )); \
					hContext->bBlitInvalid = true; \
				} \
			} \
		} \
	} \
}

/***************************************************************************/
#define BGRC_PACKET_P_VERIFY_RECTANGLE_WITH_SURFACE( surface ) \
{ \
	if( BGRC_PACKET_P_GET_REG(surface##_FEEDER_ENABLE) ) \
	{ \
		uint32_t surface_offset = BGRC_PACKET_P_GET_REG(surface##_SURFACE_ADDR_0); \
		if( surface_offset && (surface_offset != hGrc->ulDummySurOffset) ) \
		{ \
			uint32_t bpp = BGRC_PACKET_P_GET_SURFACE_BPP(surface##_SURFACE); \
			uint32_t x = BGRC_PACKET_P_GET_REG_FIELD_SHIFT(BLIT_##surface##_TOP_LEFT, LEFT); \
			uint32_t y = BGRC_PACKET_P_GET_REG_FIELD_SHIFT(BLIT_##surface##_TOP_LEFT, TOP); \
			uint32_t w = BGRC_PACKET_P_GET_REG_FIELD_SHIFT(BLIT_##surface##_SIZE, SURFACE_WIDTH); \
			uint32_t h = BGRC_PACKET_P_GET_REG_FIELD_SHIFT(BLIT_##surface##_SIZE, SURFACE_HEIGHT); \
\
			if( (x+w > hContext->surface##_surface_width) || (y+h > hContext->surface##_surface_height) ) \
			{ \
				BDBG_ERR(( "%6s rectangle invalid: rect(%d, %d, %d, %d), surface size(%d, %d), blit dropped", \
					#surface, x, y, w, h, hContext->surface##_surface_width, hContext->surface##_surface_height )); \
				hContext->bBlitInvalid = true; \
			} \
\
			if ( hContext->surface##_surface_pitch && (hContext->surface##_surface_width * bpp > hContext->surface##_surface_pitch * 8 /* for 8 bits per byte */) ) \
			{ \
				BDBG_WRN(( "%6s pitch invalid: bpp %d, width %d, pitch %d", \
					#surface, bpp, hContext->surface##_surface_width, hContext->surface##_surface_pitch )); \
				/* hContext->bBlitInvalid = true; */ \
			} \
\
			if( hContext->surface##_surface_format >= BM2MC_PACKET_PixelFormat_eMax ) \
			{ \
				BDBG_ERR(( "%6s surface format %d invalid, blit dropped", \
					#surface, hContext->surface##_surface_format)); \
				hContext->bBlitInvalid = true; \
			} \
		} \
	} \
}
#endif

/***************************************************************************/
void BGRC_PACKET_P_Isr( void *pvParam1, int iParam2 )
{
	BGRC_Handle hGrc = (BGRC_Handle) pvParam1;
	BSTD_UNUSED(iParam2);
	(*hGrc->callback_isr)( hGrc, hGrc->callback_data );
}

/***************************************************************************/
#define BGRC_P_HW_PKT_CROSSED_OVER(pkt_exed, pkt, pkt_cur) \
	(((pkt_exed)<=(pkt)) && ((pkt)<(pkt_cur)))

#define BGRC_P_HW_PKT_WRAPPED_OVER(pkt_exed, pkt, pkt_cur) \
	(((pkt)>=(pkt_exed)) || ((pkt)<(pkt_cur)))  /* assume hw wrappped */

/***************************************************************************/
void BGRC_P_CheckHwStatus(
	BGRC_Handle hGrc)
{
	uint32_t ulBlitStatus = 255;
	uint32_t ulListStatus = 255;
	uint32_t ulCurExeHwPkt;
	uint32_t ulLastHwPktOffset;
	uint32_t ulPrevHwPktOffsetExecuted;
	BGRC_PacketContext_Handle hContext;
	bool bHwIdle = false;

	if ( hGrc->pLastHwPktPtr )
	{
		ulCurExeHwPkt = BGRC_P_ReadReg32( hGrc->hRegister, LIST_CURR_PKT_ADDR );
		ulLastHwPktOffset = (hGrc->pLastHwPktPtr - hGrc->pHwPktFifoBase) + hGrc->ulHwPktFifoBaseOffset;
		if (ulCurExeHwPkt == ulLastHwPktOffset)
		{
			ulBlitStatus = BGRC_P_ReadReg32( hGrc->hRegister, BLIT_STATUS );
			ulListStatus = BGRC_P_ReadReg32( hGrc->hRegister, LIST_STATUS );
			if(	(ulBlitStatus == BGRC_M2MC(BLIT_STATUS_STATUS_IDLE)) &&
				(ulListStatus == BGRC_M2MC(LIST_STATUS_FINISHED_MASK)) )
			{
				bHwIdle = true;
				hGrc->pLastHwPktPtr = NULL;
			}
		}
	}
	else
	{
		/* correct value needed for BGRC_PACKET_P_OkToWriteHwPkt */
		ulCurExeHwPkt = hGrc->ulHwPktOffsetExecuted;
		bHwIdle = true;
	}

	/* since this function will loop through all contexts, we are willing to spend
	 * more code space to trade for efficiency */
	ulPrevHwPktOffsetExecuted = hGrc->ulHwPktOffsetExecuted;
	hContext = BLST_D_FIRST(&hGrc->context_list);
	if ( bHwIdle )
	{
		while( hContext )
		{
			if ( BGRC_PACKET_P_SyncState_eQueuedInHw == hContext->eSyncState )
			{
				hContext->eSyncState = BGRC_PACKET_P_SyncState_eSynced;
			}
			hContext = BLST_D_NEXT(hContext, context_link);
		}
	}
	else if (ulCurExeHwPkt >= ulPrevHwPktOffsetExecuted)
	{
		/* regular case */
		while( hContext )
		{
			if ( BGRC_PACKET_P_SyncState_eQueuedInHw == hContext->eSyncState )
			{
				BDBG_ASSERT(hContext->ulSyncHwPktOffset);
				if (BGRC_P_HW_PKT_CROSSED_OVER(ulPrevHwPktOffsetExecuted, hContext->ulSyncHwPktOffset, ulCurExeHwPkt))
				{
					hContext->eSyncState = BGRC_PACKET_P_SyncState_eSynced;
				}
			}
			hContext = BLST_D_NEXT(hContext, context_link);
		}
	}
	else
	{
		/* HW wrapped around */
		while( hContext )
		{
			if ( BGRC_PACKET_P_SyncState_eQueuedInHw == hContext->eSyncState )
			{
				BDBG_ASSERT(hContext->ulSyncHwPktOffset);
				if (BGRC_P_HW_PKT_WRAPPED_OVER(ulPrevHwPktOffsetExecuted, hContext->ulSyncHwPktOffset, ulCurExeHwPkt))
				{
					hContext->eSyncState = BGRC_PACKET_P_SyncState_eSynced;
				}
			}
			hContext = BLST_D_NEXT(hContext, context_link);
		}
	}
	hGrc->ulHwPktOffsetExecuted = ulCurExeHwPkt;
}

/***************************************************************************/
#define BGRC_PACKET_P_PKT_BUF_READY( wtr, rdr, pkt_size, end ) \
    (((wtr) + (pkt_size) < (rdr)) || \
     (((wtr) >= (rdr)) && ((wtr) + (pkt_size) <= (end))))

/***************************************************************************/
static bool BGRC_PACKET_P_OkToWriteHwPkt(
	BGRC_Handle hGrc )
{
	uint32_t ulHwPktWritePtrOffset;
	uint32_t ulHwPktOffsetExecuted = hGrc->ulHwPktOffsetExecuted;
	uint32_t ulHwPktBufEnd = hGrc->ulHwPktFifoBaseOffset + hGrc->ulHwPktFifoSize;

	hGrc->pHwPktWritePtr = BGRC_PACKET_P_ALIGN_HW_PKT(hGrc->pHwPktWritePtr);
	ulHwPktWritePtrOffset = (hGrc->pHwPktWritePtr - hGrc->pHwPktFifoBase) + hGrc->ulHwPktFifoBaseOffset;

	/* this is the absolute majority case, we have to optimize for its efficiency */
	if (BGRC_PACKET_P_PKT_BUF_READY(ulHwPktWritePtrOffset, ulHwPktOffsetExecuted,
									BGRC_PACKET_P_BLIT_GROUP_SIZE_MAX, ulHwPktBufEnd))
	{
		return true;
	}
	/* try wrap around */
	else if ((ulHwPktWritePtrOffset >= ulHwPktOffsetExecuted) &&
			 (hGrc->ulHwPktFifoBaseOffset + BGRC_PACKET_P_BLIT_GROUP_SIZE_MAX < ulHwPktOffsetExecuted))
	{
		hGrc->pHwPktWritePtr = hGrc->pHwPktFifoBase;
		return true;
	}
	return false;
}

/***************************************************************************/
static bool BGRC_PACKET_P_HwPktBufAvailable(
	BGRC_Handle hGrc )
{
	/* this is the absolute majority case, we have to optimize for its efficiency */
	if (BGRC_PACKET_P_OkToWriteHwPkt(hGrc))
		return true;

	/* to see if HW has executed more pkts and released buf */
	BGRC_P_CheckHwStatus(hGrc);
	return BGRC_PACKET_P_OkToWriteHwPkt(hGrc);
}

/***************************************************************************/
static void BGRC_PACKET_P_FlushHwPktBuf( BGRC_Handle hGrc, uint8_t *pHwPktFlushPtr )
{
	int flush_size;
	if( hGrc->pHwPktWritePtr > pHwPktFlushPtr )
	{
		/* flush unwrapped buf */
		flush_size = hGrc->pHwPktWritePtr - pHwPktFlushPtr;
		BMEM_FlushCache( hGrc->hMemory, pHwPktFlushPtr, flush_size+4 );
	}
	else if( hGrc->pHwPktWritePtr < pHwPktFlushPtr )
	{
		/* flush wrapped buf */
		flush_size =  hGrc->ulHwPktFifoSize - (pHwPktFlushPtr - hGrc->pHwPktFifoBase);
		BMEM_FlushCache( hGrc->hMemory, pHwPktFlushPtr, flush_size+4);

		flush_size = hGrc->pHwPktWritePtr - hGrc->pHwPktFifoBase;
		BMEM_FlushCache( hGrc->hMemory, hGrc->pHwPktFifoBase, flush_size+4);
	}
}

/***************************************************************************/
void BGRC_PACKET_P_WriteHwPkt(
	BGRC_Handle hGrc,
	BGRC_PacketContext_Handle hContext,
	uint32_t ulGroupMask )
{
	uint32_t *pHwPktWritePtr = (uint32_t *)hGrc->pHwPktWritePtr;
	uint32_t ulHwPktWritePtrOffset = (hGrc->pHwPktWritePtr - hGrc->pHwPktFifoBase) + hGrc->ulHwPktFifoBaseOffset;
	int groups = sizeof s_BGRC_PACKET_P_DeviceGroupSizes / sizeof (uint32_t);
	int ii, jj;

	/* write group header */
	BGRC_PACKET_P_DEBUG_PRINT_CTX( "** Desc group header: " );
	BGRC_PACKET_P_WRITE_DATA( *pHwPktWritePtr++, BCHP_M2MC_LIST_PACKET_HEADER_0_LAST_PKT_IND_MASK );
	BGRC_PACKET_P_WRITE_DATA( *pHwPktWritePtr++, ulGroupMask );
	BGRC_PACKET_P_DEBUG_PRINT( "\n" );
	BGRC_PACKET_P_PRINT_DESC("Desc group header:");
	BGRC_PACKET_P_PRINT_DESC_VALUE( ulGroupMask );

	/* write groups */
	for( ii = groups - 1; ii >= 0; --ii )
	{
		uint32_t ulMask = ulGroupMask & (1 << ii);
		if( ulMask )
		{
			int count = s_BGRC_PACKET_P_DeviceGroupSizes[ii] / sizeof (uint32_t);
			int index = s_BGRC_PACKET_P_DeviceRegisterOffsets[ii] / sizeof (uint32_t);

			/* store last blit header to possibly set interrupt later */
			if( ulMask & BGRC_M2MC(LIST_PACKET_HEADER_1_BLIT_GRP_CNTRL_MASK) )
			{
				hContext->pLastBlitHeaderPtr = pHwPktWritePtr;
				hContext->pLastHwPktPtr = hGrc->pHwPktWritePtr;
				hGrc->pLastHwPktPtr = hGrc->pHwPktWritePtr;
			}

			/* write group registers */
			BGRC_PACKET_P_DEBUG_PRINT( s_BGRC_PACKET_P_DESCR_GRP_NAME[ii] );
			BGRC_PACKET_P_DEBUG_PRINT( " ");
			BGRC_PACKET_P_PRINT_DESC(s_BGRC_PACKET_P_DESCR_GRP_NAME[ii]);
			for( jj = 0; jj < count; ++jj )
			{
				BGRC_PACKET_P_WRITE_REG( *pHwPktWritePtr++, index + jj );
				BGRC_PACKET_P_PRINT_DESC_VALUE(hContext->stored_registers[index + jj]);
			}
			BGRC_PACKET_P_DEBUG_PRINT( "\n" );
		}
	}

	/* found that fill might hang HW if CBAR_SRC_COLOR is SCALE_THEN_KEY_THEN_MATRIX,
	 * Maulshree suggest to use KEY_THEN_MATRIX_THEN_SCALE for fill */
	if((0 == BGRC_PACKET_P_GET_REG(SRC_SURFACE_FORMAT_DEF_1)) &&
	   !(BGRC_P_COMPARE_FIELD_NAME(*hContext->pLastBlitHeaderPtr, BLIT_HEADER, CBAR_SRC_COLOR, BYPASS_ALL)))
	{
		if((BGRC_P_COMPARE_FIELD_NAME(*hContext->pLastBlitHeaderPtr, BLIT_HEADER, SRC_COLOR_MATRIX_ENABLE, ENABLE)) &&
		   (BGRC_P_COMPARE_FIELD_NAME(*hContext->pLastBlitHeaderPtr, BLIT_HEADER, SRC_COLOR_KEY_ENABLE, ENABLE)))
		{
			if((BGRC_P_COMPARE_FIELD_NAME(*hContext->pLastBlitHeaderPtr, BLIT_HEADER, CBAR_SRC_COLOR, SCALE_THEN_KEY_THEN_MATRIX)) ||
			   (BGRC_P_COMPARE_FIELD_NAME(*hContext->pLastBlitHeaderPtr, BLIT_HEADER, CBAR_SRC_COLOR, KEY_THEN_SCALE_THEN_MATRIX)))
			{
				BGRC_P_WRITE_FIELD_NAME(*hContext->pLastBlitHeaderPtr, BLIT_HEADER, CBAR_SRC_COLOR, KEY_THEN_MATRIX_THEN_SCALE);
			}
			else if((BGRC_P_COMPARE_FIELD_NAME(*hContext->pLastBlitHeaderPtr, BLIT_HEADER, CBAR_SRC_COLOR, SCALE_THEN_MATRIX_THEN_KEY)) ||
					(BGRC_P_COMPARE_FIELD_NAME(*hContext->pLastBlitHeaderPtr, BLIT_HEADER, CBAR_SRC_COLOR, MATRIX_THEN_SCALE_THEN_KEY)))
			{
				BGRC_P_WRITE_FIELD_NAME(*hContext->pLastBlitHeaderPtr, BLIT_HEADER, CBAR_SRC_COLOR, MATRIX_THEN_KEY_THEN_SCALE);
			}
		}
		else
		{
			BGRC_P_WRITE_FIELD_NAME(*hContext->pLastBlitHeaderPtr, BLIT_HEADER, CBAR_SRC_COLOR, KEY_THEN_MATRIX_THEN_SCALE);
		}
	}

	/* link this hw pkt to the previous unsubmitted one */
	if( hGrc->pHwPktPrevWritePtr )
	{
		BGRC_PACKET_P_DEBUG_PRINT_CTX( "-- NEXT               " );
		BGRC_PACKET_P_WRITE_DATA( *(uint32_t *)hGrc->pHwPktPrevWritePtr, ulHwPktWritePtrOffset );
		BGRC_PACKET_P_DEBUG_PRINT( "\n" );
	}
	hGrc->pHwPktPrevWritePtr = hGrc->pHwPktWritePtr;
	hGrc->pHwPktWritePtr = (uint8_t *) pHwPktWritePtr;

	/* so no more LUT table loading */
	BGRC_PACKET_P_STORE_REG( SRC_CLUT_ENTRY_i_ARRAY_BASE, 0x0 );
}

/***************************************************************************/
static void BGRC_PACKET_P_SubmitHwPktsToHw(
	BGRC_Handle hGrc,
	BGRC_PacketContext_Handle hContext,
	uint8_t *pStartHwPkt )
{
	uint32_t ulStartHwPktOffset = (pStartHwPkt - hGrc->pHwPktFifoBase) + hGrc->ulHwPktFifoBaseOffset;

	/* enable interrupt with the last blit to keep pipe line advancing */
	*(hContext->pLastBlitHeaderPtr) = *(hContext->pLastBlitHeaderPtr) | BGRC_M2MC(BLIT_HEADER_INTERRUPT_ENABLE_MASK);

	/* flush hw pkt buf */
	BGRC_PACKET_P_FlushHwPktBuf( hGrc, pStartHwPkt );

	/* submit this hw pkt series to HW */
	if( hGrc->pHwPktSubmitLinkPtr )
	{
		/* append this hw pkt series to the tail of previously submitted */
		BGRC_PACKET_P_DEBUG_PRINT_CTX( "** NEXT               " );
		BGRC_PACKET_P_WRITE_DATA( *(uint32_t *)hGrc->pHwPktSubmitLinkPtr, ulStartHwPktOffset );
		BGRC_PACKET_P_DEBUG_PRINT( "\n" );

		/* flush "next offset" from previous blits */
		BMEM_FlushCache( hGrc->hMemory, hGrc->pHwPktSubmitLinkPtr, sizeof (uint32_t) + 4 );

		BGRC_P_WriteReg32( hGrc->hRegister, LIST_CTRL,
			BCHP_FIELD_ENUM( M2MC_LIST_CTRL, WAKE, WakeUp ) |
			BCHP_FIELD_ENUM( M2MC_LIST_CTRL, RUN, Run ) |
			BCHP_FIELD_ENUM( M2MC_LIST_CTRL, WAKE_MODE, ResumeFromLast ) );
	}
	else
	{
		BGRC_P_WriteReg32( hGrc->hRegister, LIST_FIRST_PKT_ADDR, ulStartHwPktOffset );
		BGRC_P_WriteReg32( hGrc->hRegister, LIST_CTRL,
			BCHP_FIELD_ENUM( M2MC_LIST_CTRL, WAKE, Ack ) |
			BCHP_FIELD_ENUM( M2MC_LIST_CTRL, RUN, Run ) |
			BCHP_FIELD_ENUM( M2MC_LIST_CTRL, WAKE_MODE, ResumeFromFirst ) );
	}

	hGrc->pHwPktSubmitLinkPtr = hGrc->pHwPktPrevWritePtr;
	hGrc->pHwPktPrevWritePtr = NULL;
}

/***************************************************************************/
void BGRC_PACKET_P_ProcessSwPktFifo(
	BGRC_Handle hGrc,
	BGRC_PacketContext_Handle hContext )
{
	/* get first packet and group header */
	uint32_t *pSwPacket = (uint32_t *) hContext->pSwPktReadPtr;
	uint8_t  *pStartHwPkt = NULL;
	uint32_t *pNextSwPkt = pSwPacket;
	uint32_t ulSwPktSize;
	uint32_t ii;
	BM2MC_PACKET_Header *pHeader;
	bool bSoftwareStriping;
	bool bBlitSwPkt;

	BDBG_ASSERT((uint8_t *)pSwPacket < hContext->pSwPktWrapPtr);

#if defined(BCHP_M2MC_DCEG_CFG) && BGRC_PACKET_P_WORK_AROUND_DCEG_HW_ISSUE
  BGRC_PACKET_P_ProcessSwPktFifo__:
#endif

	/* reload every thing as context switch or reset */
	if( (hGrc->hContext != hContext) || (hContext->bResetState) )
	{
		hGrc->hContext = hContext;
		hContext->bResetState = false;
		hContext->ulGroupMask = BGRC_PACKET_P_DEVICE_GROUP_MASK_FULL;
		if (0 != BGRC_PACKET_P_GET_REG(SRC_CLUT_ENTRY_i_ARRAY_BASE))
		{
			hContext->ulGroupMask |= BCHP_M2MC_LIST_PACKET_HEADER_1_SRC_CLUT_GRP_CNTRL_MASK;
		}
	}

	/* clear scaler's stripe counts */
	hContext->scaler.stripe_count = 0;
	hContext->scaler.stripe_num = 0;

	/* loop through sw packets until the sw packet fifo is empty or the HW packet fifo is full */
	while( hContext->ulSwPktSizeToProc )
	{
		pHeader = (BM2MC_PACKET_Header *) pSwPacket;
		bSoftwareStriping = false;

		if (pHeader->type != BM2MC_PACKET_PacketType_eSourcePalette)
		{
			hContext->ulGroupMask |= s_BGRC_PACKET_P_DeviceGroupHeaderMasks[pHeader->type];
		}
		bBlitSwPkt = ( (pHeader->type >= BM2MC_PACKET_PacketType_eFillBlit) && (pHeader->type <= BM2MC_PACKET_PacketType_eDestripeBlit) );

		/* proc this sw pkt later if it needs to write a hw pkt and we don't have he pkt buf */
		if( pHeader->execute && bBlitSwPkt)
		{
			if( !BGRC_PACKET_P_HwPktBufAvailable( hGrc ) )
			{
				break;
			}
		}

		/* process sw packet and write the setting into shadow registers */
		pNextSwPkt = BGRC_PACKET_P_ProcessSwPaket( hContext, pHeader, &bSoftwareStriping );
		ulSwPktSize = pHeader->size * sizeof (uint32_t);
		hContext->ulSwPktSizeToProc -= ulSwPktSize;
		hGrc->ulSwPktSizeToProc -= ulSwPktSize;

		/* store last header type for a blit packet */
		if( (pHeader->type >= BM2MC_PACKET_PacketType_eFillBlit) && (pHeader->type <= BM2MC_PACKET_PacketType_eDestripeBlit) )
			hContext->last_blit_type = pHeader->type;

		if( pHeader->execute && bBlitSwPkt)
		{
#if BGRC_PACKET_P_VERIFY_SURFACE_RECTANGLE && BDBG_DEBUG_BUILD
			BGRC_PACKET_P_VERIFY_RECTANGLE_SCALE();

			/* bounds check memory */
			if( hContext->create_settings.memory_bounds.offset && hContext->create_settings.memory_bounds.size )
			{
				uint32_t disable_mask =
					BGRC_M2MC(DEST_SURFACE_FORMAT_DEF_3_CH0_DISABLE_MASK) | BGRC_M2MC(DEST_SURFACE_FORMAT_DEF_3_CH1_DISABLE_MASK) |
					BGRC_M2MC(DEST_SURFACE_FORMAT_DEF_3_CH2_DISABLE_MASK) | BGRC_M2MC(DEST_SURFACE_FORMAT_DEF_3_CH3_DISABLE_MASK);

				BGRC_PACKET_P_VERIFY_RECTANGLE_WITH_BOUNDS( SRC, SURFACE, TOP_LEFT, SIZE, disable_mask );
				BGRC_PACKET_P_VERIFY_RECTANGLE_WITH_BOUNDS( DEST, SURFACE, TOP_LEFT, SIZE, disable_mask );
				BGRC_PACKET_P_VERIFY_RECTANGLE_WITH_BOUNDS( OUTPUT, SURFACE, TOP_LEFT, SIZE, 0 );
			}

			BGRC_PACKET_P_VERIFY_RECTANGLE_WITH_SURFACE( SRC );
			BGRC_PACKET_P_VERIFY_RECTANGLE_WITH_SURFACE( DEST );
			BGRC_PACKET_P_VERIFY_RECTANGLE_WITH_SURFACE( OUTPUT );
#endif
			if ((!hContext->bBlitInvalid) && (0==hContext->stSurInvalid.ulInts))
			{
				/* store first hw pkt offset in order to issue this hw pkt list to HW later */
				if( NULL == pStartHwPkt)
					pStartHwPkt = hGrc->pHwPktWritePtr;

				/* write one blit / hw-packet */
				BGRC_PACKET_P_WriteHwPkt( hGrc, hContext, hContext->ulGroupMask );
				hContext->ulGroupMask= 0;

#if 1 /* syang: according to Maulshree, no need to do sw stripe */
				/* write scaler stripe blits */
				if( bSoftwareStriping ||
#ifdef BGRC_PACKET_P_SW_DESTRIPE
					(hContext->last_blit_type == BM2MC_PACKET_PacketType_eDestripeBlit) ||
#endif
					(hContext->last_blit_type == BM2MC_PACKET_PacketType_eScaleBlendBlit) )
				{
					for( ii = 1; ii < hContext->scaler.stripe_count; ++ii )
					{
						hGrc->pHwPktWritePtr = BGRC_PACKET_P_ALIGN_HW_PKT( hGrc->pHwPktWritePtr );

						if( hContext->scaler_header->type == BM2MC_PACKET_PacketType_eScaleBlendBlit )
						{
							BM2MC_PACKET_PacketScaleBlendBlit *scale_packet = (BM2MC_PACKET_PacketScaleBlendBlit *) hContext->scaler_header;
							BGRC_PACKET_P_ProcSwPktStripeBlit( hContext, &scale_packet->src_rect, &scale_packet->out_rect, &scale_packet->dst_point );
						}
#ifdef BGRC_PACKET_P_SW_DESTRIPE
						else if( hContext->scaler_header->type == BM2MC_PACKET_PacketType_eDestripeBlit )
						{
							BGRC_PACKET_P_ProcSwPktDestripeBlit( hContext, hContext->scaler_header );
						}
#endif
						else
						{
							BM2MC_PACKET_PacketScaleBlit *scale_packet = (BM2MC_PACKET_PacketScaleBlit *) hContext->scaler_header;
							BGRC_PACKET_P_ProcSwPktStripeBlit( hContext, &scale_packet->src_rect, &scale_packet->out_rect,
								(BM2MC_PACKET_Point*) (void *) &scale_packet->out_rect );
						}

						BGRC_PACKET_P_WriteHwPkt( hGrc, hContext,
							BGRC_M2MC(LIST_PACKET_HEADER_1_BLIT_GRP_CNTRL_MASK) | BGRC_M2MC(LIST_PACKET_HEADER_1_SCALE_PARAM_GRP_CNTRL_MASK) );
					}
				}
#endif

				/* handle sync blit */
				if( pHeader->sync && (BGRC_PACKET_P_SyncState_eQueuedInSw == hContext->eSyncState) )
				{
					if (hContext->pLastHwPktPtr)
					{
						hContext->ulSyncHwPktOffset = (hGrc->pHwPktPrevWritePtr - hGrc->pHwPktFifoBase) + hGrc->ulHwPktFifoBaseOffset;
						hContext->eSyncState = BGRC_PACKET_P_SyncState_eQueuedInHw;
						/**hContext->pLastBlitHeaderPtr = *hContext->pLastBlitHeaderPtr | BGRC_M2MC(BLIT_HEADER_INTERRUPT_ENABLE_MASK);*/
					}
					else /* prev sw packets in this context have not generated blit yet */
					{
						hContext->eSyncState = BGRC_PACKET_P_SyncState_eSynced;
					}
				}
			}

			/* clear scaler's stripe counts */
			hContext->scaler.stripe_count = 0;
			hContext->scaler.stripe_num = 0;

		} /* if( pHeader->execute && bBlitSwPkt) */

		/* handle the sync request using BGRC_Packet_SyncPackets */
		if (BGRC_PACKET_P_SyncState_eRequested == hContext->eSyncState)
		{
			if ((hContext->ulSwPktSizeBeforeSync > hContext->ulSwPktSizeToProc + ulSwPktSize) ||
			    (hContext->ulSwPktSizeBeforeSync < ulSwPktSize))
			{
				BDBG_ERR(("ulSwPktSizeBeforeSync %d, ulSwPktSizeToProc %d, ulSwPktSize %d", hContext->ulSwPktSizeBeforeSync, hContext->ulSwPktSizeToProc, ulSwPktSize));
				BDBG_ASSERT(false);
			}
			hContext->ulSwPktSizeBeforeSync -= ulSwPktSize;
			if (0 == hContext->ulSwPktSizeBeforeSync)
			{
				/**(hContext->pLastBlitHeaderPtr) = *(hContext->pLastBlitHeaderPtr) | BGRC_M2MC(BLIT_HEADER_INTERRUPT_ENABLE_MASK);*/
				if (hContext->pLastHwPktPtr)
				{
					hContext->ulSyncHwPktOffset = (hContext->pLastHwPktPtr - hGrc->pHwPktFifoBase) + hGrc->ulHwPktFifoBaseOffset;
					hContext->eSyncState = BGRC_PACKET_P_SyncState_eQueuedInHw;
				}
				else /* prev sw packets in this context have not generated blit yet */
				{
					hContext->eSyncState = BGRC_PACKET_P_SyncState_eSynced;
				}
			}
		}

		if ((uint8_t *)pNextSwPkt >= hContext->pSwPktWrapPtr)
		{
			/* reached the last sw pkt in this round */
			BDBG_ASSERT((uint8_t *)pNextSwPkt == hContext->pSwPktWrapPtr);
			pSwPacket = (uint32_t *)hContext->pSwPktFifoBase;
			hContext->pSwPktWrapPtr = hContext->pSwPktFifoBase + hContext->ulSwPktFifoSize;
			BGRC_P_SWPKT_MSG(("ctx[%d] sw pkt proc:  wraping %p > wptr %p", hContext->ulId, pNextSwPkt, hContext->pSwPktWritePtr));
		}
		else
		{
			pSwPacket = pNextSwPkt;
		}

#if defined(BCHP_M2MC_DCEG_CFG) && BGRC_PACKET_P_WORK_AROUND_DCEG_HW_ISSUE
		if ((BGRC_PACKET_P_GET_REG_FIELD(DCEG_CFG, ENABLE)) && (NULL != pStartHwPkt))
		{
			break;
		}
#endif
	} /* while( hContext->ulSwPktSizeToProc ) */

	/* record buffer offset for future call */
	hContext->pSwPktReadPtr = (uint8_t *) pSwPacket;

	/* if there is at least one hw pkt generated, submit this hw pkt list to HW */
	if( pStartHwPkt )
	{
		BGRC_PACKET_P_SubmitHwPktsToHw( hGrc, hContext, pStartHwPkt );
	}

#if defined(BCHP_M2MC_DCEG_CFG) && BGRC_PACKET_P_WORK_AROUND_DCEG_HW_ISSUE
	if ((BGRC_PACKET_P_GET_REG_FIELD(DCEG_CFG, ENABLE)) && (NULL != pStartHwPkt))
	{
		BGRC_PACKET_P_DEBUG_PRINT_CTX( ".. compress -> " );
		BGRC_PACKET_P_InsertFlushBlit(hGrc, hGrc->hDummyCtx);
		if (hContext->ulSwPktSizeToProc > 0)
		{
			pStartHwPkt = 0;
			goto BGRC_PACKET_P_ProcessSwPktFifo__;
		}
	}
#endif
}

/***************************************************************************/
#define BGRC_PACKET_P_FLUSH_COLOR_BLEND { \
	BM2MC_PACKET_BlendFactor_eConstantColor, BM2MC_PACKET_BlendFactor_eOne, false, \
	BM2MC_PACKET_BlendFactor_eZero, BM2MC_PACKET_BlendFactor_eZero, false, BM2MC_PACKET_BlendFactor_eZero }

#define BGRC_PACKET_P_FLUSH_ALPHA_BLEND { \
	BM2MC_PACKET_BlendFactor_eConstantAlpha, BM2MC_PACKET_BlendFactor_eOne, false, \
	BM2MC_PACKET_BlendFactor_eZero, BM2MC_PACKET_BlendFactor_eZero, false, BM2MC_PACKET_BlendFactor_eZero }

/***************************************************************************/
void BGRC_PACKET_P_InsertFlushBlit(
	BGRC_Handle hGrc,
	BGRC_PacketContext_Handle hContext)
{
	void *buffer;
	size_t size_out;
	BERR_Code rc;
	BGRC_PacketContext_Handle hDummyCtx = hGrc->hDummyCtx;

	BGRC_PACKET_P_DEBUG_PRINT_CTX( ".. InsertFlushBlit\n" );

	/* assume hContext->ulSwPktSizeToProc is already 0!!! */
	BGRC_P_BACK_OUT(hGrc);
	rc = BGRC_Packet_GetPacketMemory( hGrc, hContext, &buffer, &size_out, BGRC_PACKET_P_FLUSH_PACKET_SIZE );
	BGRC_P_RE_ENTER(hGrc);
	BDBG_ASSERT((!rc) && (NULL!=buffer) && (size_out>=BGRC_PACKET_P_FLUSH_PACKET_SIZE));
	{
		BM2MC_PACKET_PacketSaveState *save_packet = (BM2MC_PACKET_PacketSaveState *) ((uint8_t *) buffer);
		BM2MC_PACKET_PacketSourceNone *src_packet = (BM2MC_PACKET_PacketSourceNone *) (save_packet + 1);
		BM2MC_PACKET_PacketDestinationNone *dst_packet = (BM2MC_PACKET_PacketDestinationNone *) (src_packet + 1);
		BM2MC_PACKET_PacketOutputFeeder *out_packet = (BM2MC_PACKET_PacketOutputFeeder *) (dst_packet + 1);
		BM2MC_PACKET_PacketBlend *blend_packet = (BM2MC_PACKET_PacketBlend *) (out_packet + 1);
		BM2MC_PACKET_PacketRop *rop_packet = (BM2MC_PACKET_PacketRop *) (blend_packet + 1);
		BM2MC_PACKET_PacketSourceColorkeyEnable *src_key_packet = (BM2MC_PACKET_PacketSourceColorkeyEnable *) (rop_packet + 1);
		BM2MC_PACKET_PacketDestinationColorkeyEnable *dst_key_packet = (BM2MC_PACKET_PacketDestinationColorkeyEnable *) (src_key_packet + 1);
		BM2MC_PACKET_PacketFilterEnable *filter_packet = (BM2MC_PACKET_PacketFilterEnable *) (dst_key_packet + 1);
		BM2MC_PACKET_PacketFilterControl *control_packet = (BM2MC_PACKET_PacketFilterControl *) (filter_packet + 1);
		BM2MC_PACKET_PacketSourceColorMatrixEnable *matrix_packet = (BM2MC_PACKET_PacketSourceColorMatrixEnable *) (control_packet + 1);
		BM2MC_PACKET_PacketAlphaPremultiply *premult_packet = (BM2MC_PACKET_PacketAlphaPremultiply *) (matrix_packet + 1);
		BM2MC_PACKET_PacketAlphaDemultiply *demult_packet = (BM2MC_PACKET_PacketAlphaDemultiply *) (premult_packet + 1);
		BM2MC_PACKET_PacketDestAlphaPremultiply *destpremult_packet = (BM2MC_PACKET_PacketDestAlphaPremultiply *) (demult_packet + 1);
		BM2MC_PACKET_PacketMirror *mirror_packet = (BM2MC_PACKET_PacketMirror *) (destpremult_packet + 1);
		BM2MC_PACKET_PacketFillBlit *fill_packet = (BM2MC_PACKET_PacketFillBlit *) (mirror_packet + 1);
		BM2MC_PACKET_PacketRestoreState *restore_packet = (BM2MC_PACKET_PacketRestoreState *) (fill_packet + 1);
		BM2MC_PACKET_Blend color_blend = BGRC_PACKET_P_FLUSH_COLOR_BLEND;
		BM2MC_PACKET_Blend alpha_blend = BGRC_PACKET_P_FLUSH_ALPHA_BLEND;

		/* write packets */
		BM2MC_PACKET_INIT( save_packet, SaveState, false );

		BM2MC_PACKET_INIT( src_packet, SourceNone, false );
		BM2MC_PACKET_INIT( dst_packet, DestinationNone, false );
		BM2MC_PACKET_INIT( out_packet, OutputFeeder, false );
		out_packet->plane.address = hGrc->ulDummySurOffset;
		out_packet->plane.pitch = sizeof (uint32_t);
		out_packet->plane.format = BM2MC_PACKET_PixelFormat_eA8_R8_G8_B8;
		out_packet->plane.width = BGRC_PACKET_FLUSH_BLIT_WIDTH;
		out_packet->plane.height = 1;

		BM2MC_PACKET_INIT( blend_packet, Blend, false );
		blend_packet->color_blend = color_blend;
		blend_packet->alpha_blend = alpha_blend;
		if (hContext != hDummyCtx)
		{
			/* not extra flush blit */
			if (++hGrc->ulSyncCntr >= 0x7FFFFFFE)
			{
				hGrc->ulSyncCntr = 1;  /* wrap around */
			}
			hContext->ulSyncCntr = hGrc->ulSyncCntr;
			hGrc->hLastSyncCtx = hContext;
			hGrc->ulExtraFlushCntr = 0;
		}
		/* else we are adding an extra dummy flush after the sync blit */
		blend_packet->color = hGrc->ulSyncCntr;

		BM2MC_PACKET_INIT( rop_packet, Rop, false );
		rop_packet->rop = BGRC_PACKET_P_RESET_ROP_VECTOR;
		rop_packet->pattern0 = 0;
		rop_packet->pattern1 = 0;
		rop_packet->color0 = 0;
		rop_packet->color1 = 0;

		BM2MC_PACKET_INIT( src_key_packet, SourceColorkeyEnable, false );
		src_key_packet->enable = false;
		BM2MC_PACKET_INIT( dst_key_packet, DestinationColorkeyEnable, false );
		dst_key_packet->enable = false;
		BM2MC_PACKET_INIT( filter_packet, FilterEnable, false );
		filter_packet->enable = true;

		BM2MC_PACKET_INIT( control_packet, FilterControl, false );
		control_packet->round = true;
		control_packet->adjust_color = false;
		control_packet->sub_alpha = false;
		control_packet->order = BM2MC_PACKET_eFilterOrder_FilterColorkeyMatrix;

		BM2MC_PACKET_INIT( matrix_packet, SourceColorMatrixEnable, false );
		matrix_packet->enable = false;
		BM2MC_PACKET_INIT( premult_packet, AlphaPremultiply, false );
		premult_packet->enable = false;
		BM2MC_PACKET_INIT( demult_packet, AlphaDemultiply, false );
		demult_packet->enable = false;
		BM2MC_PACKET_INIT( destpremult_packet, DestAlphaPremultiply, false );
		destpremult_packet->enable = false;

		BM2MC_PACKET_INIT( mirror_packet, Mirror, false );
		mirror_packet->src_hor = false;
		mirror_packet->src_ver = false;
		mirror_packet->dst_hor = false;
		mirror_packet->dst_ver = false;
		mirror_packet->out_hor = false;
		mirror_packet->out_ver = false;

		BM2MC_PACKET_INIT( fill_packet, FillBlit, true );
		fill_packet->header.sync = false;
		fill_packet->rect.x = 0;
		fill_packet->rect.y = 0;
		fill_packet->rect.width = BGRC_PACKET_FLUSH_BLIT_WIDTH;
		fill_packet->rect.height = 1;

		BM2MC_PACKET_INIT( restore_packet, RestoreState, false );

		BGRC_P_BACK_OUT(hGrc);
		rc = BGRC_Packet_SubmitPackets( hGrc, hContext, BGRC_PACKET_P_FLUSH_PACKET_SIZE );
		BGRC_P_RE_ENTER(hGrc);
		BDBG_ASSERT((BERR_SUCCESS == rc) || (BGRC_PACKET_MSG_PACKETS_INCOMPLETE == rc));

		if (hContext != hDummyCtx)
		{
			/* not an extra flush blit */
			hContext->ulSyncHwPktOffset = (hContext->pLastHwPktPtr - hGrc->pHwPktFifoBase) + hGrc->ulHwPktFifoBaseOffset;
			hContext->eSyncState = BGRC_PACKET_P_SyncState_eQueuedInHw;
		}
		while( hContext->ulSwPktSizeToProc )
		{
			BGRC_PACKET_P_ProcessSwPktFifo( hGrc, hContext );
			BGRC_P_CheckHwStatus( hGrc );
		}
		/* the dummy flush blit is now inserted into HW pkt fifo and submitted to HW */
	}
#if !(BDBG_DEBUG_BUILD)
	BSTD_UNUSED(rc);
#endif
}

/***************************************************************************/
void BGRC_PACKET_P_CheckFlush(
	BGRC_Handle hGrc )
{
	uint8_t  *pLastHwPktPtr;
	uint32_t ulLastHwPktOffset;
	BGRC_PacketContext_Handle hLastSyncCtx;

	if (hGrc->ulSwPktSizeToProc)
	{
		pLastHwPktPtr = hGrc->pLastHwPktPtr;
		BGRC_P_BACK_OUT(hGrc);
		BGRC_Packet_AdvancePackets( hGrc, NULL );
		BGRC_P_RE_ENTER(hGrc);
		if (pLastHwPktPtr != hGrc->pLastHwPktPtr)
		{
			/* some hw pkt generated */
			return;
		}
	}

	hLastSyncCtx = hGrc->hLastSyncCtx;
	if ((NULL != hLastSyncCtx) &&
		(BGRC_PACKET_P_SyncState_eCleared != hLastSyncCtx->eSyncState))
	{
		/* if the last sync blit is not synced yet, and no more hw pkt in engine,
		   add one more flush blit to keep flushing and to generate one more _isr
		   to keep system rolling */
		ulLastHwPktOffset = (hGrc->pLastHwPktPtr - hGrc->pHwPktFifoBase) + hGrc->ulHwPktFifoBaseOffset;
		if ((NULL == hGrc->pLastHwPktPtr) ||
			(ulLastHwPktOffset == hGrc->ulHwPktOffsetExecuted))
		{
			hGrc->ulExtraFlushCntr ++;
			if ((BGRC_PACKET_P_SyncState_eSynced == hLastSyncCtx->eSyncState) &&
				(hGrc->ulExtraFlushCntr > BGRC_P_EXTRA_FLUSH_THRESH))
			{
				/* waited too long, make it to be cleared */
#if BGRC_PACKET_P_DEBUG_EXTRA_FLUSH
				BDBG_WRN(("Force cleared for ctx[%d]: lastOff 0x%x, syncOff 0x%x, syncCtr 0x%x, mem 0x%x",
						  hLastSyncCtx->ulId, (hGrc->pLastHwPktPtr)? ulLastHwPktOffset : 0,
						  hLastSyncCtx->ulSyncHwPktOffset, hLastSyncCtx->ulSyncCntr, *(uint32_t *)hGrc->pDummySurBase));
#endif
				*(uint32_t *)hGrc->pDummySurBase = hLastSyncCtx->ulSyncCntr;
				hGrc->ulExtraFlushCntr = 0;
			}

			/* insert a dummy flush blit only, it is not a sync blit */
#if BGRC_PACKET_P_DEBUG_EXTRA_FLUSH
			BDBG_WRN(("ExtraFlushBlit(%d) for ctx[%d]: lastOff 0x%x, syncOff 0x%x, syncSate %d, syncCtr 0x%x, mem 0x%x",
			          hGrc->ulExtraFlushCntr, hLastSyncCtx->ulId, (hGrc->pLastHwPktPtr)? ulLastHwPktOffset : 0,
					  hLastSyncCtx->ulSyncHwPktOffset, hLastSyncCtx->eSyncState, hLastSyncCtx->ulSyncCntr, *(uint32_t *)hGrc->pDummySurBase));
#endif
			BGRC_PACKET_P_InsertFlushBlit( hGrc, hGrc->hDummyCtx );
		}
	}
}

/***************************************************************************/
BM2MC_PACKET_PixelFormat BGRC_PACKET_P_ConvertPixelFormat( BPXL_Format format )
{
	switch( format )
	{
	case BPXL_eR5_G6_B5:               return BM2MC_PACKET_PixelFormat_eR5_G6_B5;
	case BPXL_eB5_G6_R5:               return BM2MC_PACKET_PixelFormat_eB5_G6_R5;
	case BPXL_eA1_R5_G5_B5:            return BM2MC_PACKET_PixelFormat_eA1_R5_G5_B5;
	case BPXL_eX1_R5_G5_B5:            return BM2MC_PACKET_PixelFormat_eX1_R5_G5_B5;
	case BPXL_eA1_B5_G5_R5:            return BM2MC_PACKET_PixelFormat_eA1_B5_G5_R5;
	case BPXL_eX1_B5_G5_R5:            return BM2MC_PACKET_PixelFormat_eX1_B5_G5_R5;
	case BPXL_eR5_G5_B5_A1:            return BM2MC_PACKET_PixelFormat_eR5_G5_B5_A1;
	case BPXL_eR5_G5_B5_X1:            return BM2MC_PACKET_PixelFormat_eR5_G5_B5_X1;
	case BPXL_eB5_G5_R5_A1:            return BM2MC_PACKET_PixelFormat_eB5_G5_R5_A1;
	case BPXL_eB5_G5_R5_X1:            return BM2MC_PACKET_PixelFormat_eB5_G5_R5_X1;
	case BPXL_eA4_R4_G4_B4:            return BM2MC_PACKET_PixelFormat_eA4_R4_G4_B4;
	case BPXL_eX4_R4_G4_B4:            return BM2MC_PACKET_PixelFormat_eX4_R4_G4_B4;
	case BPXL_eA4_B4_G4_R4:            return BM2MC_PACKET_PixelFormat_eA4_B4_G4_R4;
	case BPXL_eX4_B4_G4_R4:            return BM2MC_PACKET_PixelFormat_eX4_B4_G4_R4;
	case BPXL_eR4_G4_B4_A4:            return BM2MC_PACKET_PixelFormat_eR4_G4_B4_A4;
	case BPXL_eR4_G4_B4_X4:            return BM2MC_PACKET_PixelFormat_eR4_G4_B4_X4;
	case BPXL_eB4_G4_R4_A4:            return BM2MC_PACKET_PixelFormat_eB4_G4_R4_A4;
	case BPXL_eB4_G4_R4_X4:            return BM2MC_PACKET_PixelFormat_eB4_G4_R4_X4;
	case BPXL_eA8_R8_G8_B8:            return BM2MC_PACKET_PixelFormat_eA8_R8_G8_B8;
	case BPXL_eX8_R8_G8_B8:            return BM2MC_PACKET_PixelFormat_eX8_R8_G8_B8;
	case BPXL_eA8_B8_G8_R8:            return BM2MC_PACKET_PixelFormat_eA8_B8_G8_R8;
	case BPXL_eX8_B8_G8_R8:            return BM2MC_PACKET_PixelFormat_eX8_B8_G8_R8;
	case BPXL_eR8_G8_B8_A8:            return BM2MC_PACKET_PixelFormat_eR8_G8_B8_A8;
	case BPXL_eR8_G8_B8_X8:            return BM2MC_PACKET_PixelFormat_eR8_G8_B8_X8;
	case BPXL_eB8_G8_R8_A8:            return BM2MC_PACKET_PixelFormat_eB8_G8_R8_A8;
	case BPXL_eB8_G8_R8_X8:            return BM2MC_PACKET_PixelFormat_eB8_G8_R8_X8;
	case BPXL_eA8:                     return BM2MC_PACKET_PixelFormat_eA8;
	case BPXL_eA4:                     return BM2MC_PACKET_PixelFormat_eA4;
	case BPXL_eA2:                     return BM2MC_PACKET_PixelFormat_eA2;
	case BPXL_eA1:                     return BM2MC_PACKET_PixelFormat_eA1;
	case BPXL_eW1:                     return BM2MC_PACKET_PixelFormat_eW1;
	case BPXL_eA8_P8:                  return BM2MC_PACKET_PixelFormat_eA8_P8;
	case BPXL_eP8:                     return BM2MC_PACKET_PixelFormat_eP8;
	case BPXL_eP4:                     return BM2MC_PACKET_PixelFormat_eP4;
	case BPXL_eP2:                     return BM2MC_PACKET_PixelFormat_eP2;
	case BPXL_eP1:                     return BM2MC_PACKET_PixelFormat_eP1;
	case BPXL_eY8_P8:                  return BM2MC_PACKET_PixelFormat_eY8_P8;
	case BPXL_eY8:                     return BM2MC_PACKET_PixelFormat_eY8;
	case BPXL_eA8_Y8:                  return BM2MC_PACKET_PixelFormat_eA8_Y8;
	case BPXL_eCb8_Cr8:                return BM2MC_PACKET_PixelFormat_eCb8_Cr8;
	case BPXL_eCr8_Cb8:                return BM2MC_PACKET_PixelFormat_eCr8_Cb8;
	case BPXL_eCb8:                    return BM2MC_PACKET_PixelFormat_eCb8;
	case BPXL_eCr8:                    return BM2MC_PACKET_PixelFormat_eCr8;
	case BPXL_eY08_Cb8_Y18_Cr8:        return BM2MC_PACKET_PixelFormat_eY08_Cb8_Y18_Cr8;
	case BPXL_eY08_Cr8_Y18_Cb8:        return BM2MC_PACKET_PixelFormat_eY08_Cr8_Y18_Cb8;
	case BPXL_eY18_Cb8_Y08_Cr8:        return BM2MC_PACKET_PixelFormat_eY18_Cb8_Y08_Cr8;
	case BPXL_eY18_Cr8_Y08_Cb8:        return BM2MC_PACKET_PixelFormat_eY18_Cr8_Y08_Cb8;
	case BPXL_eCb8_Y08_Cr8_Y18:        return BM2MC_PACKET_PixelFormat_eCb8_Y08_Cr8_Y18;
	case BPXL_eCb8_Y18_Cr8_Y08:        return BM2MC_PACKET_PixelFormat_eCb8_Y18_Cr8_Y08;
	case BPXL_eCr8_Y18_Cb8_Y08:        return BM2MC_PACKET_PixelFormat_eCr8_Y18_Cb8_Y08;
	case BPXL_eCr8_Y08_Cb8_Y18:        return BM2MC_PACKET_PixelFormat_eCr8_Y08_Cb8_Y18;
	case BPXL_eX2_Cr10_Y10_Cb10:       return BM2MC_PACKET_PixelFormat_eX2_Cr10_Y10_Cb10;
	case BPXL_eA8_Y8_Cb8_Cr8:          return BM2MC_PACKET_PixelFormat_eA8_Y8_Cb8_Cr8;
	case BPXL_eA8_Cr8_Cb8_Y8:          return BM2MC_PACKET_PixelFormat_eA8_Cr8_Cb8_Y8;
	case BPXL_eCr8_Cb8_Y8_A8:          return BM2MC_PACKET_PixelFormat_eCr8_Cb8_Y8_A8;
	case BPXL_eY8_Cb8_Cr8_A8:          return BM2MC_PACKET_PixelFormat_eY8_Cb8_Cr8_A8;
	case BPXL_eY010_Cb10_Y110_Cr10:    return BM2MC_PACKET_PixelFormat_eY010_Cb10_Y110_Cr10;
	case BPXL_eY010_Cr10_Y110_Cb10:    return BM2MC_PACKET_PixelFormat_eY010_Cr10_Y110_Cb10;
	case BPXL_eY110_Cb10_Y010_Cr10:    return BM2MC_PACKET_PixelFormat_eY110_Cb10_Y010_Cr10;
	case BPXL_eY110_Cr10_Y010_Cb10:    return BM2MC_PACKET_PixelFormat_eY110_Cr10_Y010_Cb10;
	case BPXL_eCb10_Y010_Cr10_Y110:    return BM2MC_PACKET_PixelFormat_eCb10_Y010_Cr10_Y110;
	case BPXL_eCb10_Y110_Cr10_Y010:    return BM2MC_PACKET_PixelFormat_eCb10_Y110_Cr10_Y010;
	case BPXL_eCr10_Y110_Cb10_Y010:    return BM2MC_PACKET_PixelFormat_eCr10_Y110_Cb10_Y010;
	case BPXL_eCr10_Y010_Cb10_Y110:    return BM2MC_PACKET_PixelFormat_eCr10_Y010_Cb10_Y110;
	case BPXL_eL15_L05_A6:             return BM2MC_PACKET_PixelFormat_eL15_L05_A6;
	case BPXL_eCompressed_A8_R8_G8_B8: return BM2MC_PACKET_PixelFormat_eCompressed_A8_R8_G8_B8;

	default: BDBG_ERR(("Unkown BPXL_Format 0x%x", format)); return BM2MC_PACKET_PixelFormat_eUnknown;
	}
}

/***************************************************************************/
void BGRC_PACKET_P_ConvertFilterCoeffs( BM2MC_PACKET_FilterCoeffs *coeffs, BGRC_FilterCoeffs filter, size_t src_size, size_t out_size )
{
	const BM2MC_PACKET_FilterCoeffs *pcoeffs = NULL;
	int iIndex;
	int iIndexMax;

	switch( filter )
	{
		case BGRC_FilterCoeffs_ePointSample:
			pcoeffs = &s_BGRC_PACKET_P_DeviceFilter_PointSample;
			break;

		case BGRC_FilterCoeffs_eBilinear:
			pcoeffs = &s_BGRC_PACKET_P_DeviceFilter_Bilinear;
			break;

		case BGRC_FilterCoeffs_eAnisotropic:
			iIndexMax = (sizeof s_BGRC_PACKET_P_DeviceFilter_Anisotropic / sizeof (BM2MC_PACKET_FilterCoeffs)) - 1;
			iIndex = out_size ? ((src_size << BGRC_PACKET_P_SCALER_STEP_FRAC_BITS) / out_size) >> BGRC_PACKET_P_SCALER_STEP_FRAC_BITS : 0;
			iIndex = (iIndex > iIndexMax) ? iIndexMax : iIndex;
			pcoeffs = &s_BGRC_PACKET_P_DeviceFilter_Anisotropic[iIndex];
			break;

		case BGRC_FilterCoeffs_eSharp:
			iIndexMax = (sizeof s_BGRC_PACKET_P_DeviceFilter_Sharp / sizeof (BM2MC_PACKET_FilterCoeffs)) - 1;
			iIndex = src_size ? (out_size * 8) / src_size : 0;
			iIndex = (iIndex > iIndexMax) ? iIndexMax : iIndex;
			pcoeffs = &s_BGRC_PACKET_P_DeviceFilter_Sharp[iIndex];
			break;

		case BGRC_FilterCoeffs_eSharper:
			pcoeffs = &s_BGRC_PACKET_P_DeviceFilter_Sharper;
			break;

		case BGRC_FilterCoeffs_eBlurry:
			pcoeffs = &s_BGRC_PACKET_P_DeviceFilter_Blurry;
			break;

		case BGRC_FilterCoeffs_eAntiFlutter:
			if( src_size == out_size )
				pcoeffs = &s_BGRC_PACKET_P_DeviceFilter_AntiFlutter;
			else
				pcoeffs = &s_BGRC_PACKET_P_DeviceFilter_AntiFlutterScale;
			break;

		case BGRC_FilterCoeffs_eAntiFlutterBlurry:
			if( src_size == out_size )
				pcoeffs = &s_BGRC_PACKET_P_DeviceFilter_AntiFlutterBlurry;
			else
				pcoeffs = &s_BGRC_PACKET_P_DeviceFilter_AntiFlutterScale;
			break;

		case BGRC_FilterCoeffs_eAntiFlutterSharp:
			if( src_size == out_size )
				pcoeffs = &s_BGRC_PACKET_P_DeviceFilter_AntiFlutterSharp;
			else
				pcoeffs = &s_BGRC_PACKET_P_DeviceFilter_AntiFlutterScale;
			break;
	}

	if( coeffs && pcoeffs )
		BKNI_Memcpy( coeffs, pcoeffs, sizeof (BM2MC_PACKET_FilterCoeffs) );
}

/***************************************************************************/
#define BGRC_PACKET_P_MATRIX_FRAC_BITS          10

#define BGRC_PACKET_P_MATRIX_FRAC_ADD_BITS      4

#define BGRC_PACKET_P_GET_MATRIX_ENTRY( entry, left, right ) (int16_t) \
	((((((entry) * (((entry) < 0) ? -1 : 1)) << (left)) >> (right)) * (((entry) < 0) ? -1 : 1)) & BGRC_M2MC(SRC_CM_C00_C01_CM_C01_MASK))

/***************************************************************************/
void BGRC_PACKET_P_ConvertColorMatrix( BM2MC_PACKET_ColorMatrix *matrix_out, const int32_t *matrix_in, size_t shift )
{
	int ii;
	for( ii = 0; ii < 4; ++ii )
	{
		matrix_out->m[ii][0] = BGRC_PACKET_P_GET_MATRIX_ENTRY(matrix_in[ii*5+0], BGRC_PACKET_P_MATRIX_FRAC_BITS, shift);
		matrix_out->m[ii][1] = BGRC_PACKET_P_GET_MATRIX_ENTRY(matrix_in[ii*5+1], BGRC_PACKET_P_MATRIX_FRAC_BITS, shift);
		matrix_out->m[ii][2] = BGRC_PACKET_P_GET_MATRIX_ENTRY(matrix_in[ii*5+2], BGRC_PACKET_P_MATRIX_FRAC_BITS, shift);
		matrix_out->m[ii][3] = BGRC_PACKET_P_GET_MATRIX_ENTRY(matrix_in[ii*5+3], BGRC_PACKET_P_MATRIX_FRAC_BITS, shift);
		matrix_out->m[ii][4] = BGRC_PACKET_P_GET_MATRIX_ENTRY(matrix_in[ii*5+4], BGRC_PACKET_P_MATRIX_FRAC_ADD_BITS, shift);
	}
}

/******************************************************************************
 * (c) 2003-2015 Broadcom Corporation
 *
 * This program is the proprietary software of Broadcom Corporation and/or its
 * licensors, and may only be used, duplicated, modified or distributed pursuant
 * to the terms and conditions of a separate, written license agreement executed
 * between you and Broadcom (an "Authorized License").  Except as set forth in
 * an Authorized License, Broadcom grants no license (express or implied), right
 * to use, or waiver of any kind with respect to the Software, and Broadcom
 * expressly reserves all rights in and to the Software and all intellectual
 * property rights therein.  IF YOU HAVE NO AUTHORIZED LICENSE, THEN YOU
 * HAVE NO RIGHT TO USE THIS SOFTWARE IN ANY WAY, AND SHOULD IMMEDIATELY
 * NOTIFY BROADCOM AND DISCONTINUE ALL USE OF THE SOFTWARE.
 *
 * Except as expressly set forth in the Authorized License,
 *
 * 1. This program, including its structure, sequence and organization,
 *    constitutes the valuable trade secrets of Broadcom, and you shall use all
 *    reasonable efforts to protect the confidentiality thereof, and to use
 *    this information only in connection with your use of Broadcom integrated
 *    circuit products.
 *
 * 2. TO THE MAXIMUM EXTENT PERMITTED BY LAW, THE SOFTWARE IS PROVIDED "AS IS"
 *    AND WITH ALL FAULTS AND BROADCOM MAKES NO PROMISES, REPRESENTATIONS OR
 *    WARRANTIES, EITHER EXPRESS, IMPLIED, STATUTORY, OR OTHERWISE, WITH RESPECT
 *    TO THE SOFTWARE.  BROADCOM SPECIFICALLY DISCLAIMS ANY AND ALL IMPLIED
 *    WARRANTIES OF TITLE, MERCHANTABILITY, NONINFRINGEMENT, FITNESS FOR A
 *    PARTICULAR PURPOSE, LACK OF VIRUSES, ACCURACY OR COMPLETENESS, QUIET
 *    ENJOYMENT, QUIET POSSESSION OR CORRESPONDENCE TO DESCRIPTION. YOU ASSUME
 *    THE ENTIRE RISK ARISING OUT OF USE OR PERFORMANCE OF THE SOFTWARE.
 *
 * 3. TO THE MAXIMUM EXTENT PERMITTED BY LAW, IN NO EVENT SHALL BROADCOM OR ITS
 *    LICENSORS BE LIABLE FOR (i) CONSEQUENTIAL, INCIDENTAL, SPECIAL, INDIRECT,
 *    OR EXEMPLARY DAMAGES WHATSOEVER ARISING OUT OF OR IN ANY WAY RELATING TO
 *    YOUR USE OF OR INABILITY TO USE THE SOFTWARE EVEN IF BROADCOM HAS BEEN
 *    ADVISED OF THE POSSIBILITY OF SUCH DAMAGES; OR (ii) ANY AMOUNT IN EXCESS
 *    OF THE AMOUNT ACTUALLY PAID FOR THE SOFTWARE ITSELF OR U.S. $1, WHICHEVER
 *    IS GREATER. THESE LIMITATIONS SHALL APPLY NOTWITHSTANDING ANY FAILURE OF
 *    ESSENTIAL PURPOSE OF ANY LIMITED REMEDY.
 *
 *****************************************************************************/

#include "bstd.h"
#include "bint_7271.h"
#include "bkni.h"
/* Include interrupt definitions from RDB */
#include "bchp_hif_cpu_intr1.h"

/* Standard L2 stuff */
#include "bchp_aud_inth.h"
#include "bchp_hvd_intr2_0.h"
#include "bchp_bsp_control_intr2.h"
#include "bchp_bvnb_intr2.h"
#include "bchp_bvnb_intr2_1.h"
#include "bchp_bvnf_intr2_0.h"
#include "bchp_bvnf_intr2_1.h"
#include "bchp_bvnf_intr2_3.h"
#include "bchp_bvnf_intr2_5.h"
#include "bchp_bvnf_intr2_9.h"
#include "bchp_bvnf_intr2_16.h"
#include "bchp_bvnm_intr2_0.h"
#include "bchp_clkgen_intr2.h"
#include "bchp_dvp_hr_intr2.h"
#include "bchp_m2mc_l2.h"
#include "bchp_hdmi_rx_intr2_0.h"
#include "bchp_hdmi_tx_intr2.h"
#include "bchp_hdmi_tx_scdc_intr2_0.h"
#include "bchp_hdmi_tx_hae_intr2_0.h"
#include "bchp_dvp_ht.h"
#include "bchp_dvp_hr.h"
#include "bchp_memc_l2_0_0.h"
#include "bchp_memc_l2_0_1.h"
#include "bchp_memc_l2_0_2.h"
#include "bchp_raaga_dsp_inth.h"
#include "bchp_raaga_dsp_fw_inth.h"
#include "bchp_sun_l2.h"
#include "bchp_aon_l2.h"
#include "bchp_aon_pm_l2.h"
#include "bchp_upg_bsc_irq.h"
#include "bchp_upg_bsc_aon_irq.h"
#include "bchp_sid_l2.h"
#include "bchp_upg_aux_aon_intr2.h"
#include "bchp_v3d_ctl_0.h"
#include "bchp_v3d_hub_ctl.h"
#include "bchp_video_enc_intr2.h"

/* MHL */
#include "bchp_mpm_host_l2.h"
#include "bchp_mpm_pm_l2.h"
#include "bchp_cbus_intr2_0.h"
#include "bchp_cbus_intr2_1.h"

/* XPT */
#include "bchp_xpt_fe.h"
#include "bchp_xpt_bus_if.h"
#include "bchp_xpt_dpcr0.h"
#include "bchp_xpt_dpcr1.h"
#include "bchp_xpt_dpcr2.h"
#include "bchp_xpt_dpcr3.h"
#include "bchp_xpt_dpcr4.h"
#include "bchp_xpt_dpcr5.h"
#include "bchp_xpt_rave.h"
#include "bchp_xpt_msg.h"

#include "bchp_xpt_msg_buf_dat_rdy_intr_00_31_l2.h"
#include "bchp_xpt_msg_buf_dat_rdy_intr_32_63_l2.h"
#include "bchp_xpt_msg_buf_dat_rdy_intr_64_95_l2.h"
#include "bchp_xpt_msg_buf_dat_rdy_intr_96_127_l2.h"

#include "bchp_xpt_msg_buf_ovfl_intr_00_31_l2.h"
#include "bchp_xpt_msg_buf_ovfl_intr_32_63_l2.h"
#include "bchp_xpt_msg_buf_ovfl_intr_64_95_l2.h"
#include "bchp_xpt_msg_buf_ovfl_intr_96_127_l2.h"

#include "bchp_xpt_msg_dat_err_intr_l2.h"
#include "bchp_xpt_pcroffset.h"
#include "bchp_xpt_wakeup.h"
#include "bchp_xpt_full_pid_parser.h"
#include "bchp_xpt_mcpb_cpu_intr_aggregator.h"
#include "bchp_xpt_mcpb_desc_done_intr_l2.h"
#include "bchp_xpt_mcpb_misc_asf_compressed_data_received_intr_l2.h"
#include "bchp_xpt_mcpb_misc_asf_len_err_intr_l2.h"
#include "bchp_xpt_mcpb_misc_asf_padding_len_err_intr_l2.h"
#include "bchp_xpt_mcpb_misc_asf_protocol_err_intr_l2.h"
#include "bchp_xpt_mcpb_misc_crc_compare_error_intr_l2.h"
#include "bchp_xpt_mcpb_misc_data_tagid_mismatch_intr_l2.h"
#include "bchp_xpt_mcpb_misc_desc_tagid_mismatch_intr_l2.h"
#include "bchp_xpt_mcpb_misc_false_wake_intr_l2.h"
#include "bchp_xpt_mcpb_misc_oos_intr_l2.h"
#include "bchp_xpt_mcpb_misc_pause_after_group_packets_intr_l2.h"
#include "bchp_xpt_mcpb_misc_pause_at_desc_end_intr_l2.h"
#include "bchp_xpt_mcpb_misc_pause_at_desc_read_intr_l2.h"
#include "bchp_xpt_mcpb_misc_pes_next_ts_range_err_intr_l2.h"
#include "bchp_xpt_mcpb_misc_tei_intr_l2.h"
#include "bchp_xpt_mcpb_misc_ts_parity_err_intr_l2.h"
#include "bchp_xpt_mcpb_misc_ts_range_err_intr_l2.h"
#include "bchp_xpt_rave_misc_l2_intr.h"
#include "bchp_xpt_rave_cdb_overflow_cx00_31_l2_intr.h"
#include "bchp_xpt_rave_itb_overflow_cx00_31_l2_intr.h"
#include "bchp_xpt_rave_emu_error_cx00_31_l2_intr.h"
#include "bchp_xpt_rave_pusi_error_cx00_31_l2_intr.h"
#include "bchp_xpt_rave_tei_error_cx00_31_l2_intr.h"
#include "bchp_xpt_rave_cc_error_cx00_31_l2_intr.h"
#include "bchp_xpt_rave_cdb_upper_thresh_cx00_31_l2_intr.h"
#include "bchp_xpt_rave_itb_upper_thresh_cx00_31_l2_intr.h"
#include "bchp_xpt_wdma_btp_intr_l2.h"
#include "bchp_xpt_wdma_overflow_intr_l2.h"
#include "bchp_xpt_wdma_desc_done_intr_l2.h"
#include "bchp_xpt_rave_cdb_lower_thresh_cx00_31_l2_intr.h"
#include "bchp_xpt_rave_itb_lower_thresh_cx00_31_l2_intr.h"
#include "bchp_xpt_tsio_intr_l2.h"
#include "bchp_xpt_rave_tsio_dma_end_cx00_31_l2_intr.h"
#include "bchp_scpu_host_intr2.h"
#include "bchp_timer.h"
#include "bchp_scirq0.h"

BDBG_MODULE(interruptinterface_7271);
#if 0
#define BINT_P_IRQ0_CASES \
    case BCHP_IRQ0_IRQEN:

#define BINT_P_IRQ0_ENABLE      0
#define BINT_P_IRQ0_STATUS      4
#endif

#if 0
#define BINT_P_IRQ0_AON_CASES \
    case BCHP_IRQ0_AON_IRQEN:

#define BINT_P_IRQ0_AON_ENABLE      0
#define BINT_P_IRQ0_AON_STATUS      4
#endif

#define BINT_P_XPT_STATUS           0x00
#define BINT_P_XPT_ENABLE           0x04

#define BINT_P_XPT_STATUS_CASES \
    case BCHP_XPT_BUS_IF_INTR_STATUS_REG: \
    case BCHP_XPT_BUS_IF_INTR_STATUS2_REG: \
    case BCHP_XPT_BUS_IF_INTR_STATUS3_REG: \
    case BCHP_XPT_BUS_IF_INTR_STATUS4_REG: \
    case BCHP_XPT_BUS_IF_INTR_STATUS5_REG: \
    case BCHP_XPT_FE_INTR_STATUS0_REG: \
    case BCHP_XPT_FE_INTR_STATUS1_REG: \
    case BCHP_XPT_FE_INTR_STATUS2_REG: \
    case BCHP_XPT_FULL_PID_PARSER_IBP_PCC_INTR_STATUS_REG: \
    case BCHP_XPT_FULL_PID_PARSER_PBP_PCC_INTR_STATUS_REG: \
    case BCHP_XPT_FULL_PID_PARSER_IBP_SCC_INTR_STATUS_REG: \
    case BCHP_XPT_FULL_PID_PARSER_PBP_SCC_INTR_STATUS_REG: \
    case BCHP_XPT_FULL_PID_PARSER_IBP_PSG_PROTOCOL_INTR_STATUS_REG: \
    case BCHP_XPT_FULL_PID_PARSER_PBP_PSG_PROTOCOL_INTR_STATUS_REG: \
    case BCHP_XPT_FULL_PID_PARSER_IBP_TRANSPORT_ERROR_INTR_STATUS_REG: \
    case BCHP_XPT_FULL_PID_PARSER_PBP_TRANSPORT_ERROR_INTR_STATUS_REG: \
    case BCHP_XPT_DPCR0_INTR_STATUS_REG: \
    case BCHP_XPT_DPCR1_INTR_STATUS_REG: \
    case BCHP_XPT_DPCR2_INTR_STATUS_REG: \
    case BCHP_XPT_DPCR3_INTR_STATUS_REG: \
    case BCHP_XPT_DPCR4_INTR_STATUS_REG: \
    case BCHP_XPT_DPCR5_INTR_STATUS_REG:

#define BINT_P_PCROFFSET_CASES \
    case BCHP_XPT_PCROFFSET_INTERRUPT0_STATUS: \
    case BCHP_XPT_PCROFFSET_INTERRUPT1_STATUS: \
    case BCHP_XPT_PCROFFSET_INTERRUPT2_STATUS: \
    case BCHP_XPT_PCROFFSET_INTERRUPT3_STATUS: \
    case BCHP_XPT_PCROFFSET_STC_INTERRUPT_STATUS:

#define BINT_P_PCROFFSET_STATUS     0x00
#define BINT_P_PCROFFSET_ENABLE     0x04

/* There is no constant address mapping from RAVE status to RAVE enable registers. */
#define BINT_P_RAVE_STATUS          0x00


#define BINT_P_XPT_RAVE_CASES \
    case BCHP_XPT_RAVE_INT_CX0: \
    case BCHP_XPT_RAVE_INT_CX1: \
    case BCHP_XPT_RAVE_INT_CX2: \
    case BCHP_XPT_RAVE_INT_CX3: \
    case BCHP_XPT_RAVE_INT_CX4: \
    case BCHP_XPT_RAVE_INT_CX5: \
    case BCHP_XPT_RAVE_INT_CX6: \
    case BCHP_XPT_RAVE_INT_CX7: \
    case BCHP_XPT_RAVE_INT_CX8: \
    case BCHP_XPT_RAVE_INT_CX9: \
    case BCHP_XPT_RAVE_INT_CX10: \
    case BCHP_XPT_RAVE_INT_CX11: \
    case BCHP_XPT_RAVE_INT_CX12: \
    case BCHP_XPT_RAVE_INT_CX13: \
    case BCHP_XPT_RAVE_INT_CX14: \
    case BCHP_XPT_RAVE_INT_CX15: \
    case BCHP_XPT_RAVE_INT_CX16: \
    case BCHP_XPT_RAVE_INT_CX17: \
    case BCHP_XPT_RAVE_INT_CX18: \
    case BCHP_XPT_RAVE_INT_CX19: \
    case BCHP_XPT_RAVE_INT_CX20: \
    case BCHP_XPT_RAVE_INT_CX21: \
    case BCHP_XPT_RAVE_INT_CX22: \
    case BCHP_XPT_RAVE_INT_CX23: \

#define BINT_P_XPT_BUF_STATUS       0x00
#define BINT_P_XPT_BUF_ENABLE       0x10

#define BINT_P_XPT_BUF_CASES \
    case BCHP_XPT_MSG_BUF_ERR_00_31: \
    case BCHP_XPT_MSG_BUF_ERR_32_63: \
    case BCHP_XPT_MSG_BUF_ERR_64_95: \
    case BCHP_XPT_MSG_BUF_ERR_96_127: \
    case BCHP_XPT_MSG_BUF_DAT_AVAIL_00_31: \
    case BCHP_XPT_MSG_BUF_DAT_AVAIL_32_63: \
    case BCHP_XPT_MSG_BUF_DAT_AVAIL_64_95: \
    case BCHP_XPT_MSG_BUF_DAT_AVAIL_96_127: \

#define BINT_P_XPT_MSG_ERR_STATUS   ( 0x00 )
#define BINT_P_XPT_MSG_ERR_ENABLE   ( 0x04 )

/* BINT_P_UPGSC_ENABLE was defined as -4 for BCHP_SCIRQ0_SCIRQSTAT.
 * Since we are using BCHP_SCIRQ0_SCIRQEN, it is not needed but
 * to minimize the change, it is kept and set to 0
 */
#define BINT_P_UPGSC_ENABLE (0)

#define BINT_P_UPGSC_CASES \
    case BCHP_SCIRQ0_SCIRQEN:

#define BINT_P_TIMER_STATUS     0x00
#define BINT_P_TIMER_MASK       0x04

#define BINT_P_TIMER_CASES \
    case BCHP_TIMER_TIMER_IS:

#define BINT_P_V3D_CTL_INT_STATUS 0x00
#define BINT_P_V3D_CTL_INT_MASK   0x0C
#define BINT_P_V3D_CTL_INT_CASES \
    case BCHP_V3D_CTL_0_INT_STS:

#define BCHP_INT_ID_V3D_INTR              BCHP_INT_ID_CREATE(BCHP_V3D_CTL_0_INT_STS, 0)

#define BINT_P_V3D_HUB_CTL_INT_STATUS 0x00
#define BINT_P_V3D_HUB_CTL_INT_MASK   0x0C
#define BINT_P_V3D_HUB_CTL_INT_CASES \
    case BCHP_V3D_HUB_CTL_INT_STS:

#define BCHP_INT_ID_V3D_HUB_INTR          BCHP_INT_ID_CREATE(BCHP_V3D_HUB_CTL_INT_STS, 0)

#define BINT_P_STAT_TIMER_TICKS_PER_USEC 27


static void BINT_P_7271_ClearInt( BREG_Handle regHandle, uint32_t baseAddr, int shift );
static void BINT_P_7271_SetMask( BREG_Handle regHandle, uint32_t baseAddr, int shift );
static void BINT_P_7271_ClearMask( BREG_Handle regHandle, uint32_t baseAddr, int shift );

static uint32_t BINT_P_7271_ReadStatus( BREG_Handle regHandle, uint32_t baseAddr );
static uint32_t GetRaveIntEnableOffset( uint32_t BaseAddr );

#if NEXUS_WEBCPU_core1_server
static const BINT_P_IntMap bint_7271[] =
{
    { BCHP_HIF_CPU_INTR1_INTR_W3_STATUS_M2MC1_CPU_INTR_SHIFT + 96,          BCHP_M2MC1_L2_CPU_STATUS,              0,                   "M2MC1"},
    { -1, 0, 0, NULL}
};
#else
static const BINT_P_IntMap bint_7271[] =
{
    BINT_MAP_STD(0, BSP, BSP_CONTROL_INTR2_CPU),
    BINT_MAP_STD(0, SCPU, SCPU_HOST_INTR2_CPU),
    BINT_MAP_STD(0, AIO, AUD_INTH_R5F),
    BINT_MAP_STD(0, GFX, M2MC_L2_CPU),
    BINT_MAP_STD(0, VEC, VIDEO_ENC_INTR2_CPU),
    BINT_MAP_STD(0, BVNB_0, BVNB_INTR2_CPU),
    BINT_MAP_STD(0, BVNF_0, BVNF_INTR2_0_R5F),
    BINT_MAP_STD(0, BVNF_1, BVNF_INTR2_1_R5F),
    BINT_MAP_STD(0, BVNF_5, BVNF_INTR2_5_R5F),
    BINT_MAP_STD(0, BVNF_9, BVNF_INTR2_9_R5F),
    BINT_MAP_STD(0, BVNF_16, BVNF_INTR2_16_R5F),
    BINT_MAP_STD(0, BVNM_0, BVNM_INTR2_0_R5F),
    BINT_MAP_STD(0, BVNB_1, BVNB_INTR2_1_CPU),
    BINT_MAP_STD(0, CLKGEN, CLKGEN_INTR2_CPU),
    BINT_MAP_STD(0, DVP_HR, DVP_HR_INTR2_CPU),
    BINT_MAP_STD(0, HDMI_TX, HDMI_TX_INTR2_CPU),
    BINT_MAP_STD(0, HDMI_RX_0, HDMI_RX_INTR2_0_CPU),
#if 0
    BINT_MAP_STD(0, HDMI_TX, HDMI_TX_SCDC_INTR2_0_CPU),
    BINT_MAP_STD(0, HDMI_TX, HDMI_TX_HAE_INTR2_0_CPU),
#endif
    BINT_MAP_STD(3, CBUS, CBUS_INTR2_0_CPU),
    BINT_MAP_STD(3, CBUS, CBUS_INTR2_1_CPU),
    BINT_MAP_STD(1, HVD0_0, HVD_INTR2_0_CPU),
    BINT_MAP_STD(1, RAAGA, RAAGA_DSP_INTH_HOST),
    BINT_MAP_STD(1, RAAGA_FW, RAAGA_DSP_FW_INTH_HOST),
    BINT_MAP_STD(1, MEMC0, MEMC_L2_0_0_CPU),
    BINT_MAP_STD(1, MEMC0, MEMC_L2_0_1_CPU),
    BINT_MAP_STD(1, MEMC0, MEMC_L2_0_2_CPU),
    BINT_MAP_STD(1, SYS_AON, AON_L2_CPU),
    BINT_MAP_STD(1, UPG_AUX_AON, UPG_AUX_AON_INTR2_CPU),
    BINT_MAP_STD(1, SYS_PM, AON_PM_L2_CPU),
    BINT_MAP_STD(1, UPG_BSC, UPG_BSC_IRQ_CPU),

    BINT_MAP_STD(2, UPG_BSC_AON, UPG_BSC_AON_IRQ_CPU),
    /*BINT_MAP(2, UPG_MAIN, "" , UPG_MAIN_IRQ, REGULAR, MASK, 0xFFFFF1C7),*/
    /*BINT_MAP_STD(2, UPG_MAIN_AON, UPG_MAIN_AON_IRQ_CPU),*/
    BINT_MAP(2, UPG_SC, "", SCIRQ0_SCIRQEN, REGULAR, ALL, 0),
    BINT_MAP(2, UPG_TMR, "", TIMER_TIMER_IS, REGULAR, ALL, 0),
    BINT_MAP(2, V3D, "_INT", V3D_CTL_0_INT_STS, REGULAR, NONE, 0),
    BINT_MAP(2, V3D_HUB, "_INT", V3D_HUB_CTL_INT_STS, REGULAR, NONE, 0),
    BINT_MAP(2, XPT_FE, "_STATUS0", XPT_FE_INTR_STATUS0_REG, REGULAR, ALL, 0),
    BINT_MAP(2, XPT_FE, "_STATUS1", XPT_FE_INTR_STATUS1_REG, REGULAR, ALL, 0),
    BINT_MAP(2, XPT_FE, "_IBP_PCC", XPT_FULL_PID_PARSER_IBP_PCC_INTR_STATUS_REG, REGULAR, ALL, 0),
    BINT_MAP(2, XPT_FE, "_PBP_PCC", XPT_FULL_PID_PARSER_PBP_PCC_INTR_STATUS_REG, REGULAR, ALL, 0),
    BINT_MAP(2, XPT_FE, "_IBP_SCC", XPT_FULL_PID_PARSER_IBP_SCC_INTR_STATUS_REG, REGULAR, ALL, 0),
    BINT_MAP(2, XPT_FE, "_PBP_SCC", XPT_FULL_PID_PARSER_PBP_SCC_INTR_STATUS_REG, REGULAR, ALL, 0),
    BINT_MAP(2, XPT_FE, "_IBP_PSG", XPT_FULL_PID_PARSER_IBP_PSG_PROTOCOL_INTR_STATUS_REG,   REGULAR, ALL, 0),
    BINT_MAP(2, XPT_FE, "_PBP_PSG", XPT_FULL_PID_PARSER_PBP_PSG_PROTOCOL_INTR_STATUS_REG, REGULAR, ALL, 0  ),
    BINT_MAP(2, XPT_FE, "_IBP_TRANSPORT_ERROR", XPT_FULL_PID_PARSER_IBP_TRANSPORT_ERROR_INTR_STATUS_REG, REGULAR, ALL, 0),
    BINT_MAP(2, XPT_FE, "_PBP_TRANSPORT_ERROR", XPT_FULL_PID_PARSER_PBP_TRANSPORT_ERROR_INTR_STATUS_REG, REGULAR, ALL, 0),
    BINT_MAP_STD( 2, XPT_OVFL, XPT_MSG_BUF_OVFL_INTR_00_31_L2_W8_CPU ),
    BINT_MAP_STD( 2, XPT_OVFL, XPT_MSG_BUF_OVFL_INTR_32_63_L2_W9_CPU ),
    BINT_MAP_STD( 2, XPT_OVFL, XPT_MSG_BUF_OVFL_INTR_64_95_L2_W10_CPU ),
    BINT_MAP_STD( 2, XPT_OVFL, XPT_MSG_BUF_OVFL_INTR_96_127_L2_W11_CPU ),
    BINT_MAP_STD(2, XPT_MSG_STAT, XPT_MSG_DAT_ERR_INTR_L2_CPU),
    BINT_MAP_STD( 2, XPT_MSG, XPT_MSG_BUF_DAT_RDY_INTR_00_31_L2_W0_CPU ),
    BINT_MAP_STD( 2, XPT_MSG, XPT_MSG_BUF_DAT_RDY_INTR_32_63_L2_W1_CPU ),
    BINT_MAP_STD( 2, XPT_MSG, XPT_MSG_BUF_DAT_RDY_INTR_64_95_L2_W2_CPU ),
    BINT_MAP_STD( 2, XPT_MSG, XPT_MSG_BUF_DAT_RDY_INTR_96_127_L2_W3_CPU ),
    BINT_MAP(2, XPT_PCR, "XPT_DPCR0", XPT_DPCR0_INTR_STATUS_REG, REGULAR, ALL, 0),
    BINT_MAP(2, XPT_PCR, "XPT_DPCR1", XPT_DPCR1_INTR_STATUS_REG, REGULAR, ALL, 0),
    BINT_MAP(2, XPT_PCR, "XPT_DPCR2", XPT_DPCR2_INTR_STATUS_REG, REGULAR, ALL, 0),
    BINT_MAP(2, XPT_PCR, "XPT_DPCR3", XPT_DPCR3_INTR_STATUS_REG, REGULAR, ALL, 0),
    BINT_MAP(2, XPT_PCR, "XPT_DPCR4", XPT_DPCR4_INTR_STATUS_REG, REGULAR, ALL, 0),
    BINT_MAP(2, XPT_PCR, "XPT_DPCR5", XPT_DPCR5_INTR_STATUS_REG, REGULAR, ALL, 0),
    BINT_MAP(2, XPT_PCR, "XPT_PCROFF0", XPT_PCROFFSET_INTERRUPT0_STATUS, REGULAR, ALL, 0),
    BINT_MAP(2, XPT_PCR, "XPT_PCROFF1", XPT_PCROFFSET_INTERRUPT1_STATUS, REGULAR, ALL, 0),
    BINT_MAP(2, XPT_PCR, "XPT_PCROFF2", XPT_PCROFFSET_INTERRUPT2_STATUS, REGULAR, ALL, 0),
    BINT_MAP(2, XPT_PCR, "XPT_PCROFF3", XPT_PCROFFSET_INTERRUPT3_STATUS, REGULAR, ALL, 0),
    BINT_MAP(2, XPT_PCR, "XPT_PCROFF_STC", XPT_PCROFFSET_STC_INTERRUPT_STATUS, REGULAR, ALL, 0),
    BINT_MAP(2, XPT_RAV, "CDB_OVERFLOW_CX00_31", XPT_RAVE_CDB_OVERFLOW_CX00_31_L2_INTR_CPU_STATUS_0_31, STANDARD, ALL, 0),
    BINT_MAP(2, XPT_RAV, "ITB_OVERFLOW_CX00_31", XPT_RAVE_ITB_OVERFLOW_CX00_31_L2_INTR_CPU_STATUS_0_31, STANDARD, ALL, 0),
    BINT_MAP(2, XPT_RAV, "EMU_ERROR_CX00_31", XPT_RAVE_EMU_ERROR_CX00_31_L2_INTR_CPU_STATUS_0_31, STANDARD, ALL, 0),
    BINT_MAP(2, XPT_RAV, "PUSI_ERROR_CX00_31", XPT_RAVE_PUSI_ERROR_CX00_31_L2_INTR_CPU_STATUS_0_31, STANDARD, ALL, 0),
    BINT_MAP(2, XPT_RAV, "TEI_ERROR_CX00_31", XPT_RAVE_TEI_ERROR_CX00_31_L2_INTR_CPU_STATUS_0_31, STANDARD, ALL, 0),
    BINT_MAP(2, XPT_RAV, "CC_ERROR_CX00_31", XPT_RAVE_CC_ERROR_CX00_31_L2_INTR_CPU_STATUS_0_31, STANDARD, ALL, 0),
    BINT_MAP(2, XPT_RAV, "CDB_UPPER_THRESH_00_31", XPT_RAVE_CDB_UPPER_THRESH_CX00_31_L2_INTR_CPU_STATUS_0_31, STANDARD, ALL, 0),
    BINT_MAP(2, XPT_RAV, "ITB_UPPER_THRESH_00_31", XPT_RAVE_ITB_UPPER_THRESH_CX00_31_L2_INTR_CPU_STATUS_0_31, STANDARD, ALL, 0),
    BINT_MAP(2, XPT_RAV, "CDB_LOWER_THRESH_00_31", XPT_RAVE_CDB_LOWER_THRESH_CX00_31_L2_INTR_CPU_STATUS_0_31, STANDARD, ALL, 0),
    BINT_MAP(2, XPT_RAV, "ITB_LOWER_THRESH_00_31", XPT_RAVE_ITB_LOWER_THRESH_CX00_31_L2_INTR_CPU_STATUS_0_31, STANDARD, ALL, 0),
    BINT_MAP(2, XPT_RAV, "DMA_END_CX00_31", XPT_RAVE_TSIO_DMA_END_CX00_31_L2_INTR_CPU_STATUS_0_31, STANDARD, ALL, 0),
    BINT_MAP(2, XPT_STATUS, "_BUS", XPT_BUS_IF_INTR_STATUS_REG,   REGULAR, ALL, 0),
    BINT_MAP(2, XPT_STATUS, "_BUS2", XPT_BUS_IF_INTR_STATUS2_REG, REGULAR, ALL, 0),
    BINT_MAP(2, XPT_STATUS, "_BUS3", XPT_BUS_IF_INTR_STATUS3_REG,   REGULAR, ALL, 0),
    BINT_MAP(2, XPT_STATUS, "_BUS4", XPT_BUS_IF_INTR_STATUS4_REG, REGULAR, ALL, 0),
    BINT_MAP(2, XPT_STATUS, "_BUS5", XPT_BUS_IF_INTR_STATUS5_REG, REGULAR, ALL, 0),
    BINT_MAP(2, XPT_STATUS, "_WAKEUP", XPT_WAKEUP_INTR_STATUS_REG, REGULAR, ALL, 0),
    BINT_MAP_STD(2, XPT_MCPB,  XPT_MCPB_DESC_DONE_INTR_L2_CPU),
    BINT_MAP_STD(2, XPT_MCPB,  XPT_MCPB_MISC_FALSE_WAKE_INTR_L2_CPU),
    BINT_MAP_STD(2, XPT_MCPB,  XPT_MCPB_MISC_OOS_INTR_L2_CPU),
    BINT_MAP_STD(2, XPT_MCPB,  XPT_MCPB_MISC_TS_PARITY_ERR_INTR_L2_CPU),
    BINT_MAP_STD(2, XPT_MCPB,  XPT_MCPB_MISC_TEI_INTR_L2_CPU),
    BINT_MAP_STD(2, XPT_MCPB,  XPT_MCPB_MISC_ASF_LEN_ERR_INTR_L2_CPU),
    BINT_MAP_STD(2, XPT_MCPB,  XPT_MCPB_MISC_ASF_COMPRESSED_DATA_RECEIVED_INTR_L2_CPU),
    BINT_MAP_STD(2, XPT_MCPB,  XPT_MCPB_MISC_ASF_PROTOCOL_ERR_INTR_L2_CPU),
    BINT_MAP_STD(2, XPT_MCPB,  XPT_MCPB_MISC_ASF_PADDING_LEN_ERR_INTR_L2_CPU),
    BINT_MAP_STD(2, XPT_MCPB,  XPT_MCPB_MISC_TS_RANGE_ERR_INTR_L2_CPU),
    BINT_MAP_STD(2, XPT_MCPB,  XPT_MCPB_MISC_PES_NEXT_TS_RANGE_ERR_INTR_L2_CPU),
    BINT_MAP_STD(2, XPT_MCPB,  XPT_MCPB_MISC_PAUSE_AT_DESC_READ_INTR_L2_CPU),
    BINT_MAP_STD(2, XPT_MCPB,  XPT_MCPB_MISC_PAUSE_AT_DESC_END_INTR_L2_CPU),
    BINT_MAP_STD(2, XPT_MCPB,  XPT_MCPB_MISC_PAUSE_AFTER_GROUP_PACKETS_INTR_L2_CPU),
    BINT_MAP_STD(2, XPT_MCPB,  XPT_MCPB_MISC_DESC_TAGID_MISMATCH_INTR_L2_CPU),
    BINT_MAP_STD(2, XPT_MCPB,  XPT_MCPB_MISC_DATA_TAGID_MISMATCH_INTR_L2_CPU),
    BINT_MAP_STD(2, XPT_MCPB,  XPT_MCPB_MISC_CRC_COMPARE_ERROR_INTR_L2_CPU),
    BINT_MAP_STD(2, XPT_WMDMA,XPT_WDMA_BTP_INTR_L2_CPU),
    BINT_MAP_STD(2, XPT_WMDMA, XPT_WDMA_OVERFLOW_INTR_L2_CPU),
    BINT_MAP_STD(2, XPT_WMDMA, XPT_WDMA_DESC_DONE_INTR_L2_CPU),
    BINT_MAP_STD(2, XPT_EXTCARD, XPT_TSIO_INTR_L2_CPU),
    BINT_MAP_STD(3, SID0_0, SID_L2_CPU),
    BINT_MAP_STD(3, MPM_TOP, MPM_HOST_L2_CPU),

    BINT_MAP_LAST()
};
#endif

static const BINT_Settings bint_7271Settings =
{
    NULL,
    BINT_P_7271_ClearInt,
    BINT_P_7271_SetMask,
    BINT_P_7271_ClearMask,
    NULL,
    BINT_P_7271_ReadStatus,
    bint_7271,
    "7271"
};


/* On some parts, the relative location of the status and enable regs changed. */
static uint32_t getXptFeIntEnableRegAddr( uint32_t baseAddr )
{
    uint32_t enableRegAddr = baseAddr + BINT_P_XPT_ENABLE;

    switch( baseAddr )
    {
        case BCHP_XPT_FE_INTR_STATUS0_REG:
            enableRegAddr = BCHP_XPT_FE_INTR_STATUS0_REG_EN;
            break;
        case BCHP_XPT_FE_INTR_STATUS1_REG:
            enableRegAddr = BCHP_XPT_FE_INTR_STATUS1_REG_EN;
            break;
        case BCHP_XPT_FE_INTR_STATUS2_REG:
            enableRegAddr = BCHP_XPT_FE_INTR_STATUS2_REG_EN;
            break;
        default:
            break;
    }

    return enableRegAddr;
}

static void BINT_P_7271_ClearInt( BREG_Handle regHandle, uint32_t baseAddr, int shift )
{
    BDBG_MSG(("ClearInt %#x:%d", baseAddr, shift));
    switch( baseAddr )
    {

        BINT_P_XPT_STATUS_CASES
            BREG_Write32( regHandle, baseAddr + BINT_P_XPT_STATUS, ~(1ul<<shift));
            break;
        BINT_P_XPT_RAVE_CASES
            BREG_Write32( regHandle, baseAddr + BINT_P_RAVE_STATUS, (1ul<<shift));
            break;
        BINT_P_XPT_BUF_CASES
            BREG_Write32( regHandle, baseAddr + BINT_P_XPT_BUF_STATUS, ~(1ul<<shift));
            break;
        BINT_P_TIMER_CASES
            BREG_Write32( regHandle, baseAddr + BINT_P_TIMER_STATUS, 1ul<<shift);
            break;
        BINT_P_UPGSC_CASES
/*
        BINT_P_IRQ0_CASES
        BINT_P_IRQ0_AON_CASES

 */
            /* Has to cleared at the source */
            break;
        BINT_P_PCROFFSET_CASES
            /* Write 0 to clear the int bit. Writing 1's are ingored. */
            BREG_Write32( regHandle, baseAddr + BINT_P_PCROFFSET_STATUS, ~( 1ul << shift ) );
            break;
       BINT_P_V3D_CTL_INT_CASES
       BINT_P_V3D_HUB_CTL_INT_CASES
            /* Has to cleared at the source */
            break;
        default:
            /* Other types of interrupts do not support clearing of interrupts (condition must be cleared) */
            break;
    }
}

static void BINT_P_7271_SetMask( BREG_Handle regHandle, uint32_t baseAddr, int shift )
{
    uint32_t intEnable;

    uint32_t RaveEnReg = 0;

    BDBG_MSG(("SetMask %#x:%d", baseAddr, shift));


    switch( baseAddr )
    {

    BINT_P_XPT_STATUS_CASES
        intEnable = BREG_Read32( regHandle, getXptFeIntEnableRegAddr(baseAddr));
        intEnable &= ~(1ul<<shift);
        BREG_Write32( regHandle, getXptFeIntEnableRegAddr(baseAddr), intEnable);
        break;
    BINT_P_XPT_RAVE_CASES
        RaveEnReg = GetRaveIntEnableOffset( baseAddr );
        intEnable = BREG_Read32( regHandle, RaveEnReg );
        intEnable &= ~(1ul<<shift);
        BREG_Write32( regHandle, RaveEnReg, intEnable);
        break;
    BINT_P_XPT_BUF_CASES
        intEnable = BREG_Read32( regHandle, baseAddr + BINT_P_XPT_BUF_ENABLE);
        intEnable &= ~(1ul<<shift);
        BREG_Write32( regHandle, baseAddr + BINT_P_XPT_BUF_ENABLE, intEnable);
        break;
    BINT_P_TIMER_CASES
        intEnable = BREG_Read32( regHandle, baseAddr + BINT_P_TIMER_MASK);
        intEnable &= ~(1ul<<shift);
        BREG_Write32( regHandle, baseAddr + BINT_P_TIMER_MASK, intEnable);
        break;
#if 0
    BINT_P_IRQ0_CASES
        intEnable = BREG_Read32( regHandle, baseAddr + BINT_P_IRQ0_ENABLE);
        intEnable &= ~(1ul<<shift);
        BREG_Write32( regHandle, baseAddr + BINT_P_IRQ0_ENABLE, intEnable);
        break;
    BINT_P_IRQ0_AON_CASES
        intEnable = BREG_Read32( regHandle, baseAddr + BINT_P_IRQ0_AON_ENABLE);
        intEnable &= ~(1ul<<shift);
        BREG_Write32( regHandle, baseAddr + BINT_P_IRQ0_AON_ENABLE, intEnable);
        break;
#endif
    BINT_P_UPGSC_CASES
        intEnable = BREG_Read32( regHandle, baseAddr + BINT_P_UPGSC_ENABLE );
        intEnable &= ~(1ul<<shift);
        BREG_Write32( regHandle, baseAddr + BINT_P_UPGSC_ENABLE, intEnable );
        break;

    BINT_P_PCROFFSET_CASES
        intEnable = BREG_Read32( regHandle, baseAddr + BINT_P_PCROFFSET_ENABLE );
        intEnable &= ~( 1ul << shift );
        BREG_Write32( regHandle, baseAddr + BINT_P_PCROFFSET_ENABLE, intEnable);
        break;
    BINT_P_V3D_CTL_INT_CASES
    BINT_P_V3D_HUB_CTL_INT_CASES
        /* Dont support setting the v3d L2 via this interface */
        break;
    default:
       BDBG_ERR(("NOT SUPPORTED baseAddr 0x%08x ,regHandel %p,  shift %d",
                         baseAddr, regHandle, shift));

        /* Unhandled interrupt base address */
        BDBG_ASSERT( false );
        break;
    }
}

static void BINT_P_7271_ClearMask( BREG_Handle regHandle, uint32_t baseAddr, int shift )
{
    uint32_t intEnable;

    uint32_t RaveEnReg = 0;

    BDBG_MSG(("ClearMask %#x:%d", baseAddr, shift));
    switch( baseAddr )
    {

    BINT_P_XPT_STATUS_CASES
        intEnable = BREG_Read32( regHandle, getXptFeIntEnableRegAddr(baseAddr));
        intEnable |= 1ul<<shift;
        BREG_Write32( regHandle, getXptFeIntEnableRegAddr(baseAddr), intEnable);
        break;
    BINT_P_XPT_RAVE_CASES
        RaveEnReg = GetRaveIntEnableOffset( baseAddr );
        intEnable = BREG_Read32( regHandle, RaveEnReg );
        intEnable |= (1ul<<shift);
        BREG_Write32( regHandle, RaveEnReg, intEnable);
        break;
    BINT_P_XPT_BUF_CASES
        intEnable = BREG_Read32( regHandle, baseAddr + BINT_P_XPT_BUF_ENABLE);
        intEnable |= 1ul<<shift;
        BREG_Write32( regHandle, baseAddr + BINT_P_XPT_BUF_ENABLE, intEnable);
        break;
#if 0
    BINT_P_IRQ0_CASES
        intEnable = BREG_Read32( regHandle, baseAddr + BINT_P_IRQ0_ENABLE);
        intEnable |= (1ul<<shift);
        BREG_Write32( regHandle, baseAddr + BINT_P_IRQ0_ENABLE, intEnable );
        break;
    BINT_P_IRQ0_AON_CASES
        intEnable = BREG_Read32( regHandle, baseAddr + BINT_P_IRQ0_AON_ENABLE);
        intEnable |= (1ul<<shift);
        BREG_Write32( regHandle, baseAddr + BINT_P_IRQ0_AON_ENABLE, intEnable );
        break;
#endif
    BINT_P_UPGSC_CASES
        intEnable = BREG_Read32( regHandle, baseAddr + BINT_P_UPGSC_ENABLE );
        intEnable |= 1ul<<shift;
        BREG_Write32( regHandle, baseAddr + BINT_P_UPGSC_ENABLE, intEnable );
        break;
    BINT_P_TIMER_CASES
        intEnable = BREG_Read32( regHandle, baseAddr + BINT_P_TIMER_MASK );
        intEnable |= (1ul<<shift);
        BREG_Write32( regHandle, baseAddr + BINT_P_TIMER_MASK, intEnable );
        break;

    BINT_P_PCROFFSET_CASES
        intEnable = BREG_Read32( regHandle, baseAddr + BINT_P_PCROFFSET_ENABLE );
        intEnable |= ( 1ul << shift );
        BREG_Write32( regHandle, baseAddr + BINT_P_PCROFFSET_ENABLE, intEnable);
        break;
    BINT_P_V3D_CTL_INT_CASES
    BINT_P_V3D_HUB_CTL_INT_CASES
        /* Dont support setting the v3d L2 via this interface */
        break;
    default:
        /* Unhandled interrupt base address */
        BDBG_ASSERT( false );
        break;
    }
}


static uint32_t BINT_P_7271_ReadStatus( BREG_Handle regHandle, uint32_t baseAddr )
{
    BDBG_MSG(("ReadStatus %#x", baseAddr));
    switch( baseAddr )
    {
    BINT_P_XPT_STATUS_CASES
        return BREG_Read32( regHandle, baseAddr + BINT_P_XPT_STATUS );
    BINT_P_XPT_RAVE_CASES
        return BREG_Read32( regHandle, baseAddr + BINT_P_RAVE_STATUS );
    BINT_P_XPT_BUF_CASES
        return BREG_Read32( regHandle, baseAddr + BINT_P_XPT_BUF_STATUS );
    BINT_P_TIMER_CASES
        return BREG_Read32( regHandle, baseAddr + BINT_P_TIMER_STATUS );
#if 0
    BINT_P_IRQ0_CASES
        return BREG_Read32( regHandle, baseAddr + BINT_P_IRQ0_STATUS );
    BINT_P_IRQ0_AON_CASES
        return BREG_Read32( regHandle, baseAddr + BINT_P_IRQ0_AON_STATUS );
#endif
    BINT_P_UPGSC_CASES
        return BREG_Read32( regHandle, baseAddr + BINT_P_UPGSC_ENABLE );
    BINT_P_PCROFFSET_CASES
        return BREG_Read32( regHandle, baseAddr + BINT_P_PCROFFSET_STATUS );
    BINT_P_V3D_CTL_INT_CASES
        {
            uint32_t flags;
            flags  = BREG_Read32( regHandle, baseAddr + BINT_P_V3D_CTL_INT_MASK );
            flags &= BREG_Read32( regHandle, baseAddr + BINT_P_V3D_CTL_INT_STATUS );
            return flags;
        }
        break;
    BINT_P_V3D_HUB_CTL_INT_CASES
        {
            uint32_t flags;
            flags  = BREG_Read32( regHandle, baseAddr + BINT_P_V3D_HUB_CTL_INT_MASK );
            flags &= BREG_Read32( regHandle, baseAddr + BINT_P_V3D_HUB_CTL_INT_STATUS );
            return flags;
        }
        break;
    default:
        /* Unhandled interrupt base address */
        BDBG_ASSERT( false );
        return 0;
    }
}

const BINT_Settings *BINT_7271_GetSettings( void )
{
    return &bint_7271Settings;
}


static uint32_t GetRaveIntEnableOffset(
    uint32_t BaseAddr
    )
{
    uint32_t EnableAddr = 0;

    switch( BaseAddr )
    {
        case BCHP_XPT_RAVE_INT_CX0: EnableAddr =   BCHP_XPT_RAVE_CX0_AV_INTERRUPT_ENABLES; break;
        case BCHP_XPT_RAVE_INT_CX1: EnableAddr =   BCHP_XPT_RAVE_CX1_AV_INTERRUPT_ENABLES; break;
        case BCHP_XPT_RAVE_INT_CX2: EnableAddr =   BCHP_XPT_RAVE_CX2_AV_INTERRUPT_ENABLES; break;
        case BCHP_XPT_RAVE_INT_CX3: EnableAddr =   BCHP_XPT_RAVE_CX3_AV_INTERRUPT_ENABLES; break;
        case BCHP_XPT_RAVE_INT_CX4: EnableAddr =   BCHP_XPT_RAVE_CX4_AV_INTERRUPT_ENABLES; break;
        case BCHP_XPT_RAVE_INT_CX5: EnableAddr =   BCHP_XPT_RAVE_CX5_AV_INTERRUPT_ENABLES; break;
        case BCHP_XPT_RAVE_INT_CX6: EnableAddr =   BCHP_XPT_RAVE_CX6_AV_INTERRUPT_ENABLES; break;
        case BCHP_XPT_RAVE_INT_CX7: EnableAddr =   BCHP_XPT_RAVE_CX7_AV_INTERRUPT_ENABLES; break;
        case BCHP_XPT_RAVE_INT_CX8: EnableAddr =   BCHP_XPT_RAVE_CX8_AV_INTERRUPT_ENABLES; break;
        case BCHP_XPT_RAVE_INT_CX9: EnableAddr =   BCHP_XPT_RAVE_CX9_AV_INTERRUPT_ENABLES; break;
        case BCHP_XPT_RAVE_INT_CX10: EnableAddr =  BCHP_XPT_RAVE_CX10_AV_INTERRUPT_ENABLES; break;
        case BCHP_XPT_RAVE_INT_CX11: EnableAddr =  BCHP_XPT_RAVE_CX11_AV_INTERRUPT_ENABLES; break;
        case BCHP_XPT_RAVE_INT_CX12: EnableAddr =  BCHP_XPT_RAVE_CX12_AV_INTERRUPT_ENABLES; break;
        case BCHP_XPT_RAVE_INT_CX13: EnableAddr =  BCHP_XPT_RAVE_CX13_AV_INTERRUPT_ENABLES; break;
        case BCHP_XPT_RAVE_INT_CX14: EnableAddr =  BCHP_XPT_RAVE_CX14_AV_INTERRUPT_ENABLES; break;
        case BCHP_XPT_RAVE_INT_CX15: EnableAddr =  BCHP_XPT_RAVE_CX15_AV_INTERRUPT_ENABLES; break;
        case BCHP_XPT_RAVE_INT_CX16: EnableAddr =  BCHP_XPT_RAVE_CX16_AV_INTERRUPT_ENABLES; break;
        case BCHP_XPT_RAVE_INT_CX17: EnableAddr =  BCHP_XPT_RAVE_CX17_AV_INTERRUPT_ENABLES; break;
        case BCHP_XPT_RAVE_INT_CX18: EnableAddr =  BCHP_XPT_RAVE_CX18_AV_INTERRUPT_ENABLES; break;
        case BCHP_XPT_RAVE_INT_CX19: EnableAddr =  BCHP_XPT_RAVE_CX19_AV_INTERRUPT_ENABLES; break;
        case BCHP_XPT_RAVE_INT_CX20: EnableAddr =  BCHP_XPT_RAVE_CX20_AV_INTERRUPT_ENABLES; break;
        case BCHP_XPT_RAVE_INT_CX21: EnableAddr =  BCHP_XPT_RAVE_CX21_AV_INTERRUPT_ENABLES; break;
        case BCHP_XPT_RAVE_INT_CX22: EnableAddr =  BCHP_XPT_RAVE_CX22_AV_INTERRUPT_ENABLES; break;
        case BCHP_XPT_RAVE_INT_CX23: EnableAddr =  BCHP_XPT_RAVE_CX23_AV_INTERRUPT_ENABLES; break;
        default:
        /* Unhandled interrupt base address */
        BDBG_ASSERT( false );
        break;
    }

    return EnableAddr;
}


/* End of file */

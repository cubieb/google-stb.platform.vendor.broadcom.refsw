/***************************************************************************
 *	   Copyright (c) 2003-2013, Broadcom Corporation
 *	   All Rights Reserved
 *	   Confidential Property of Broadcom Corporation
 *
 *	THIS SOFTWARE MAY ONLY BE USED SUBJECT TO AN EXECUTED SOFTWARE LICENSE
 *	AGREEMENT  BETWEEN THE USER AND BROADCOM.  YOU HAVE NO RIGHT TO USE OR
 *	EXPLOIT THIS MATERIAL EXCEPT SUBJECT TO THE TERMS OF SUCH AN AGREEMENT.
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
#include "bstd.h"
#include "bint_7543.h"
#include "bchp_7543.h"

/* Include interrupt definitions from RDB */
#include "bchp_hif_cpu_intr1.h"

/* Standard L2 stuff */
#include "bchp_aio_inth.h"
#include "bchp_avd_intr2_0.h"
#if 0
#include "bchp_bsp_control_intr2.h"
#endif
#include "bchp_bvnb_intr2.h"
#include "bchp_bvnf_intr2_0.h"
#include "bchp_bvnf_intr2_1.h"
#include "bchp_bvnf_intr2_3.h"
#include "bchp_bvnf_intr2_4.h"
#include "bchp_bvnf_intr2_5.h"
#include "bchp_bvnm_intr2_0.h"
#include "bchp_hdmi_tx_intr2.h"
#include "bchp_memc_l2_0.h"
#if 0
#include "bchp_raaga_dsp_inth.h"
#include "bchp_raaga_dsp_fw_inth.h"
#endif
#include "bchp_sm_l2.h"
#include "bchp_sun_l2.h"
#include "bchp_aon_l2.h"
#include "bchp_aon_pm_l2.h"
#include "bchp_video_enc_intr2.h"
#include "bchp_m2mc_top_l2.h"
#include "bchp_clkgen_intr2.h"
#include "bchp_upg_aux_aon_intr2.h"
#include "bchp_rfm_l2.h"
#include "bchp_ipi0_intr2.h"
#include "bchp_ipi1_intr2.h"

/* XPT */
#include "bchp_xpt_fe.h"
#include "bchp_xpt_bus_if.h"
#include "bchp_xpt_dpcr0.h"
#include "bchp_xpt_dpcr1.h"
#include "bchp_xpt_pb0.h"
#include "bchp_xpt_pb1.h"
#include "bchp_xpt_rave.h"
#include "bchp_xpt_pcroffset.h"
#include "bchp_xpt_wakeup.h"
#include "bchp_xpt_full_pid_parser.h"

/* UARTs, keypad, I2C */
#include "bchp_irq0.h"
#include "bchp_irq0_aon.h"
#include "bchp_upg_aux_aon_intr2.h"

/* Smartcard interrupts. */
#include "bchp_scirq0.h"

/* Timer */
#include "bchp_timer.h"

/* new for 7543 */
#include "bchp_mem_dma_0.h"
#include "bchp_dfe_miscdec.h"

BDBG_MODULE(interruptinterface_7543);

#define	BINT_P_IRQ0_CASES \
	case BCHP_IRQ0_IRQEN:

#define BINT_P_IRQ0_ENABLE		0
#define BINT_P_IRQ0_STATUS		4


#define	BINT_P_IRQ0_AON_CASES \
	case BCHP_IRQ0_AON_IRQEN:

#define BINT_P_IRQ0_AON_ENABLE		0
#define BINT_P_IRQ0_AON_STATUS		4


#define BINT_P_XPT_STATUS			0x00
#define BINT_P_XPT_ENABLE			0x04

#define BINT_P_XPT_STATUS_CASES \
	case BCHP_XPT_BUS_IF_INTR_STATUS_REG: \
	case BCHP_XPT_BUS_IF_INTR_STATUS2_REG: \
	case BCHP_XPT_BUS_IF_INTR_STATUS3_REG: \
	case BCHP_XPT_BUS_IF_INTR_STATUS4_REG: \
	case BCHP_XPT_BUS_IF_INTR_STATUS5_REG: \
	case BCHP_XPT_PB0_INTR: \
	case BCHP_XPT_FE_INTR_STATUS0_REG: \
	case BCHP_XPT_FE_INTR_STATUS1_REG: \
	case BCHP_XPT_DPCR0_INTR_STATUS_REG: \
	case BCHP_XPT_DPCR1_INTR_STATUS_REG: \
	case BCHP_XPT_FULL_PID_PARSER_IBP_PCC_INTR_STATUS_REG: \
	case BCHP_XPT_FULL_PID_PARSER_PBP_PCC_INTR_STATUS_REG: \
	case BCHP_XPT_FULL_PID_PARSER_IBP_SCC_INTR_STATUS_REG: \
	case BCHP_XPT_FULL_PID_PARSER_PBP_SCC_INTR_STATUS_REG: \
	case BCHP_XPT_FULL_PID_PARSER_IBP_PSG_PROTOCOL_INTR_STATUS_REG: \
	case BCHP_XPT_FULL_PID_PARSER_PBP_PSG_PROTOCOL_INTR_STATUS_REG: \
	case BCHP_XPT_FULL_PID_PARSER_IBP_TRANSPORT_ERROR_INTR_STATUS_REG: \
	case BCHP_XPT_FULL_PID_PARSER_PBP_TRANSPORT_ERROR_INTR_STATUS_REG: \
	case BCHP_XPT_WAKEUP_INTR_STATUS_REG:


#define BINT_P_PCROFFSET_CASES \
	case BCHP_XPT_PCROFFSET_INTERRUPT0_STATUS: \
	case BCHP_XPT_PCROFFSET_INTERRUPT1_STATUS: \
	case BCHP_XPT_PCROFFSET_INTERRUPT2_STATUS: \
	case BCHP_XPT_PCROFFSET_INTERRUPT3_STATUS:

#define BINT_P_PCROFFSET_STATUS		0x00
#define BINT_P_PCROFFSET_ENABLE 	0x04

/* There is no constant address mapping from RAVE status to RAVE enable registers. */
#define BINT_P_RAVE_STATUS			0x00

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
    case BCHP_XPT_RAVE_INT_CX23:

#define BINT_P_XPT_BUF_STATUS		0x00
#define BINT_P_XPT_BUF_ENABLE		0x10

/* DFE interrupt cases */
#define BINT_P_DFE_STATUS  (0)
#define BINT_P_DFE_MASK  (-4)
#define BINT_P_DFE_CLEAR   (4)    
#define BINT_P_DFE_L2_CASES \
    case BCHP_DFE_MISCDEC_MISC_DFE_INT_STATUS:

/* BINT_P_UPGSC_ENABLE was defined as -4 for BCHP_SCIRQ0_SCIRQSTAT.
 * Since we are using BCHP_SCIRQ0_SCIRQEN, it is not needed but
 * to minimize the change, it is kept and set to 0
 */
#define BINT_P_UPGSC_ENABLE (0)

#define BINT_P_UPGSC_CASES \
	case BCHP_SCIRQ0_SCIRQEN:

#define BINT_P_TIMER_STATUS		0x00
#define BINT_P_TIMER_MASK		0x04

#define BINT_P_TIMER_CASES \
	case BCHP_TIMER_TIMER_IS:

#define BINT_P_STAT_TIMER_TICKS_PER_USEC 27

static void BINT_P_7543_SetInt( BREG_Handle regHandle, uint32_t baseAddr, int shift );
static void BINT_P_7543_ClearInt( BREG_Handle regHandle, uint32_t baseAddr, int shift );
static void BINT_P_7543_SetMask( BREG_Handle regHandle, uint32_t baseAddr, int shift );
static void BINT_P_7543_ClearMask( BREG_Handle regHandle, uint32_t baseAddr, int shift );
static uint32_t BINT_P_7543_ReadStatus( BREG_Handle regHandle, uint32_t baseAddr );
static uint32_t GetRaveIntEnableOffset( uint32_t BaseAddr );

static const BINT_P_IntMap bint_7543[] =
{
	/* W0 interrupt bit configuration */
    BINT_MAP_STD(0, AIO, AIO_INTH_R5F),
	/* SPARE_22_CPU_INTR */
    BINT_MAP_STD(0, BVNB_0, BVNB_INTR2_CPU),
    BINT_MAP_STD(0, BVNF_0, BVNF_INTR2_0_R5F),
    BINT_MAP_STD(0, BVNF_1, BVNF_INTR2_1_R5F),
    BINT_MAP_STD(0, BVNF_5, BVNF_INTR2_5_R5F),
    BINT_MAP_STD(0, BVNM_0, BVNM_INTR2_0_R5F),
    BINT_MAP_STD(0, CLKGEN, CLKGEN_INTR2_CPU),
	/* EXT_IRQ_00_CPU_INTR - EXT_IRQ_14_CPU_INTR is not mapped */
	/* SPARE_23_CPU_INTR - SPARE_25_CPU_INTR are not mapped */
	/* SPARE_00_CPU_INTR - SPARE_01_CPU_INTR are not mapped */
    BINT_MAP_STD(0, M2MC, M2MC_TOP_L2_CPU),
    BINT_MAP_STD(0, HDMI_TX, HDMI_TX_INTR2_CPU),

	/* W1 interrupt bit configuration */
    BINT_MAP_STD(1, IPI0, IPI0_INTR2_CPU),
    BINT_MAP_STD(1, IPI1, IPI1_INTR2_CPU),
    BINT_MAP_STD(1, MEMC_0, MEMC_L2_0_R5F),
    /* SPARE_02_CPU_INTR is not mapped */
    /* NMI_PIN_CPU_INTR is not mapped */
    /* SPARE_26_CPU_INTR - SPARE_31_CPU_INTR are not mapped */
    /* SPARE_03_CPU_INTR - SPARE_06_CPU_INTR are not mapped */
    /* SPARE_32_CPU_INTR is not mapped */
    BINT_MAP_STD(1, SYS, SUN_L2_CPU),
    BINT_MAP_STD(1, SYS_AON, AON_L2_CPU),
    BINT_MAP(1, SYS_PM, "", AON_PM_L2_CPU_STATUS, REGULAR, NONE, 0),
    /* SPARE_07_CPU_INTR - SPARE_08_CPU_INTR are not mapped */
    BINT_MAP_STD(1, UPG_AUX_AON, UPG_AUX_AON_INTR2_CPU),
    BINT_MAP(1, UPG_BSC, "", IRQ0_IRQEN, REGULAR, MASK, 0xF8FFFFFF),
    BINT_MAP(1, UPG_BSC_AON, "", IRQ0_AON_IRQEN, REGULAR, MASK, 0xF7FFFFFF),
    BINT_MAP(1, UPG_MAIN, "", IRQ0_IRQEN, REGULAR, MASK, 0xFFFFFC00),
    BINT_MAP(1, UPG_MAIN_AON, "", IRQ0_AON_IRQEN, REGULAR, MASK, 0xFFFFFE1C),
    BINT_MAP(1, UPG_SC, "", SCIRQ0_SCIRQEN, REGULAR, MASK, /*0xFFFFFFFC*/ 0xFFFFF27C),
    BINT_MAP(1, UPG_SPI, "", IRQ0_AON_IRQEN, REGULAR, MASK, 0xFFEFFFFF),
    BINT_MAP(1, UPG_TMR, "", TIMER_TIMER_IS, REGULAR, ALL, 0),
    /* UPG_UART0_CPU_INTR, UPG_UART1_CPU_INTR, UPG_UART2_CPU_INTR are not mapped */

	/* W2 interrupt bit configuration */
    /* do we need to configure USB ? */
	/* SPARE_09_CPU_INTR - SPARE_15_CPU_INTR are not mapped */
    BINT_MAP_STD(2, VEC, VIDEO_ENC_INTR2_CPU),

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

    BINT_MAP(2, XPT_PCR, "0", XPT_DPCR0_INTR_STATUS_REG, REGULAR, ALL, 0),
    BINT_MAP(2, XPT_PCR, "1", XPT_DPCR1_INTR_STATUS_REG, REGULAR, ALL, 0),

    BINT_MAP(2, XPT_PCR, "OFF0", XPT_PCROFFSET_INTERRUPT0_STATUS, REGULAR, ALL, 0),
    BINT_MAP(2, XPT_PCR, "OFF1", XPT_PCROFFSET_INTERRUPT1_STATUS, REGULAR, ALL, 0),
    BINT_MAP(2, XPT_PCR, "OFF2", XPT_PCROFFSET_INTERRUPT2_STATUS, REGULAR, ALL, 0),
    BINT_MAP(2, XPT_PCR, "OFF3", XPT_PCROFFSET_INTERRUPT3_STATUS, REGULAR, ALL, 0),

    BINT_MAP(2, XPT_RAV, "_CX0", XPT_RAVE_INT_CX0, WEAK_MASK, ALL, 0),
    BINT_MAP(2, XPT_RAV, "_CX1", XPT_RAVE_INT_CX1, WEAK_MASK, ALL, 0),
    BINT_MAP(2, XPT_RAV, "_CX2", XPT_RAVE_INT_CX2, WEAK_MASK, ALL, 0),
    BINT_MAP(2, XPT_RAV, "_CX3", XPT_RAVE_INT_CX3, WEAK_MASK, ALL, 0),
    BINT_MAP(2, XPT_RAV, "_CX4", XPT_RAVE_INT_CX4, WEAK_MASK, ALL, 0),
    BINT_MAP(2, XPT_RAV, "_CX5", XPT_RAVE_INT_CX5, WEAK_MASK, ALL, 0),
    BINT_MAP(2, XPT_RAV, "_CX6", XPT_RAVE_INT_CX6, WEAK_MASK, ALL, 0),
    BINT_MAP(2, XPT_RAV, "_CX7", XPT_RAVE_INT_CX7, WEAK_MASK, ALL, 0),
    BINT_MAP(2, XPT_RAV, "_CX8", XPT_RAVE_INT_CX8, WEAK_MASK, ALL, 0),
    BINT_MAP(2, XPT_RAV, "_CX9", XPT_RAVE_INT_CX9, WEAK_MASK, ALL, 0),
    BINT_MAP(2, XPT_RAV, "_CX10", XPT_RAVE_INT_CX10, WEAK_MASK, ALL, 0),
    BINT_MAP(2, XPT_RAV, "_CX11", XPT_RAVE_INT_CX11, WEAK_MASK, ALL, 0),
    BINT_MAP(2, XPT_RAV, "_CX12", XPT_RAVE_INT_CX12, WEAK_MASK, ALL, 0),
    BINT_MAP(2, XPT_RAV, "_CX13", XPT_RAVE_INT_CX13, WEAK_MASK, ALL, 0),
    BINT_MAP(2, XPT_RAV, "_CX14", XPT_RAVE_INT_CX14, WEAK_MASK, ALL, 0),
    BINT_MAP(2, XPT_RAV, "_CX15", XPT_RAVE_INT_CX15, WEAK_MASK, ALL, 0),
    BINT_MAP(2, XPT_RAV, "_CX16", XPT_RAVE_INT_CX16, WEAK_MASK, ALL, 0),
    BINT_MAP(2, XPT_RAV, "_CX17", XPT_RAVE_INT_CX17, WEAK_MASK, ALL, 0),
    BINT_MAP(2, XPT_RAV, "_CX18", XPT_RAVE_INT_CX18, WEAK_MASK, ALL, 0),
    BINT_MAP(2, XPT_RAV, "_CX19", XPT_RAVE_INT_CX19, WEAK_MASK, ALL, 0),
    BINT_MAP(2, XPT_RAV, "_CX20", XPT_RAVE_INT_CX20, WEAK_MASK, ALL, 0),
    BINT_MAP(2, XPT_RAV, "_CX21", XPT_RAVE_INT_CX21, WEAK_MASK, ALL, 0),
    BINT_MAP(2, XPT_RAV, "_CX22", XPT_RAVE_INT_CX22, WEAK_MASK, ALL, 0),
    BINT_MAP(2, XPT_RAV, "_CX23", XPT_RAVE_INT_CX23, WEAK_MASK, ALL, 0),
    /* don't process it for now */
    /*BINT_MAP(2, XPT_RAV, "_MISC", XPT_RAVE_INT_MISC, REGULAR, NONE, 0),*/

    BINT_MAP(2, XPT_STATUS, "" , XPT_BUS_IF_INTR_STATUS_REG, REGULAR, ALL, 0 ),
    BINT_MAP(2, XPT_STATUS, "2", XPT_BUS_IF_INTR_STATUS2_REG, REGULAR, ALL, 0),
    BINT_MAP(2, XPT_STATUS, "3", XPT_BUS_IF_INTR_STATUS3_REG, REGULAR, ALL, 0),
    BINT_MAP(2, XPT_STATUS, "4", XPT_BUS_IF_INTR_STATUS4_REG, REGULAR, ALL, 0),
    BINT_MAP(2, XPT_STATUS, "5", XPT_BUS_IF_INTR_STATUS5_REG, REGULAR, ALL, 0),
    BINT_MAP(2, XPT_STATUS, "_PB0", XPT_PB0_INTR, REGULAR, ALL, 0),
    BINT_MAP(2, XPT_STATUS, "_WAKEUP", XPT_WAKEUP_INTR_STATUS_REG, REGULAR, ALL, 0),
    /* SDIO0_0_CPU_INTR do we need for PVR */
	/* SPARE_16_CPU_INTR is not mapped */
    BINT_MAP_STD(2, AVD0_0, AVD_INTR2_0_CPU),
	/* SPARE_17_CPU_INTR - SPARE_18_CPU_INTR are not mapped */
	/* SPARE_33_CPU_INTR - SPARE_38_CPU_INTR are not mapped */
    BINT_MAP_STD(2, MEM_DMA_0, MEM_DMA_0),
#if 0    
    BINT_MAP_STD(2, DFE, DFE_MISCDEC_MISC_DFE_INT),
#else    
    BINT_MAP(2, DFE, "", DFE_MISCDEC_MISC_DFE_INT_STATUS, REGULAR, ALL, 0),    
#endif    
	/* SPARE_21_CPU_INTR is not mapped */
    BINT_MAP_LAST()
};

static const BINT_Settings bint_7543Settings =
{
	BINT_P_7543_SetInt,
	BINT_P_7543_ClearInt,
	BINT_P_7543_SetMask,
	BINT_P_7543_ClearMask,
	NULL,
	BINT_P_7543_ReadStatus,
	bint_7543,
	"7543"
};

static void BINT_P_7543_SetInt( BREG_Handle regHandle, uint32_t baseAddr, int shift )
{
	/* TODO */
	BSTD_UNUSED(regHandle);
	BSTD_UNUSED(baseAddr);
	BSTD_UNUSED(shift);

	switch( baseAddr )
	{
#if 0 /* AT */	
    BINT_P_DFE_L2_CASES
		BREG_Write32( regHandle, baseAddr + BINT_P_STD_SET, 1ul<<shift);
		break;
#endif
		default:
	/* Only standard L2 interrupts support setting of interrupts */
	break;
	}
}

static void BINT_P_7543_ClearInt( BREG_Handle regHandle, uint32_t baseAddr, int shift )
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
#if 0
		BINT_P_XPT_BUF_CASES
			BREG_Write32( regHandle, baseAddr + BINT_P_XPT_BUF_STATUS, ~(1ul<<shift));
			break;
#endif
		BINT_P_TIMER_CASES
			BREG_Write32( regHandle, baseAddr + BINT_P_TIMER_STATUS, 1ul<<shift);
			break;
		BINT_P_UPGSC_CASES
		BINT_P_IRQ0_CASES
		BINT_P_IRQ0_AON_CASES
			/* Has to cleared at the source */
			break;
		BINT_P_PCROFFSET_CASES
			/* Write 0 to clear the int bit. Writing 1's are ingored. */
			BREG_Write32( regHandle, baseAddr + BINT_P_PCROFFSET_STATUS, ~( 1ul << shift ) );
			break;
        BINT_P_DFE_L2_CASES
            /* Write 1 to clear the int bit.  Writing 0's are ignored. */
            BREG_Write32( regHandle, baseAddr + BINT_P_DFE_CLEAR, (1ul << shift) );
            break;

		default:
			/* Other types of interrupts do not support clearing of interrupts (condition must be cleared) */
			break;
	}
}

static void BINT_P_7543_SetMask( BREG_Handle regHandle, uint32_t baseAddr, int shift )
{
	uint32_t intEnable;

	uint32_t RaveEnReg = 0;

	BDBG_MSG(("SetMask %#x:%d", baseAddr, shift));

	switch( baseAddr )
	{
	BINT_P_XPT_STATUS_CASES
		intEnable = BREG_Read32( regHandle, baseAddr + BINT_P_XPT_ENABLE);
		intEnable &= ~(1ul<<shift);
		BREG_Write32( regHandle, baseAddr + BINT_P_XPT_ENABLE, intEnable);
		break;
	BINT_P_XPT_RAVE_CASES
		RaveEnReg = GetRaveIntEnableOffset( baseAddr );
		intEnable = BREG_Read32( regHandle, RaveEnReg );
		intEnable &= ~(1ul<<shift);
		BREG_Write32( regHandle, RaveEnReg, intEnable);
		break;
#if 0
	BINT_P_XPT_BUF_CASES
		intEnable = BREG_Read32( regHandle, baseAddr + BINT_P_XPT_BUF_ENABLE);
		intEnable &= ~(1ul<<shift);
		BREG_Write32( regHandle, baseAddr + BINT_P_XPT_BUF_ENABLE, intEnable);
		break;
#endif
	BINT_P_TIMER_CASES
		intEnable = BREG_Read32( regHandle, baseAddr + BINT_P_TIMER_MASK);
		intEnable &= ~(1ul<<shift);
		BREG_Write32( regHandle, baseAddr + BINT_P_TIMER_MASK, intEnable);
		break;
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

		BINT_P_DFE_L2_CASES
			/* DFE uses enable logic - 0 = masked, 1 = not masked */
            intEnable = BREG_Read32( regHandle, baseAddr + BINT_P_DFE_MASK);
            intEnable &= ~( 1ul << shift );
            BREG_Write32( regHandle, baseAddr + BINT_P_DFE_MASK, intEnable );
        	break;

		default:
		/* Unhandled interrupt base address */
		BDBG_ASSERT( false );
		break;
	}
}

static void BINT_P_7543_ClearMask( BREG_Handle regHandle, uint32_t baseAddr, int shift )
{
	uint32_t intEnable;

	uint32_t RaveEnReg = 0;

	BDBG_MSG(("ClearMask %#x:%d", baseAddr, shift));
	switch( baseAddr )
	{
	BINT_P_XPT_STATUS_CASES
		intEnable = BREG_Read32( regHandle, baseAddr + BINT_P_XPT_ENABLE);
		intEnable |= 1ul<<shift;
		BREG_Write32( regHandle, baseAddr + BINT_P_XPT_ENABLE, intEnable);
		break;
	BINT_P_XPT_RAVE_CASES
		RaveEnReg = GetRaveIntEnableOffset( baseAddr );
		intEnable = BREG_Read32( regHandle, RaveEnReg );
		intEnable |= (1ul<<shift);
		BREG_Write32( regHandle, RaveEnReg, intEnable);
		break;
#if 0
	BINT_P_XPT_BUF_CASES
		intEnable = BREG_Read32( regHandle, baseAddr + BINT_P_XPT_BUF_ENABLE);
		intEnable |= 1ul<<shift;
		BREG_Write32( regHandle, baseAddr + BINT_P_XPT_BUF_ENABLE, intEnable);
		break;
#endif
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

		BINT_P_DFE_L2_CASES
            /* AP uses ennble logic - 0 = masked, 1 = not masked */
            intEnable = BREG_Read32( regHandle, baseAddr + BINT_P_DFE_MASK );
            intEnable |= ( 1ul << shift );
            BREG_Write32( regHandle, baseAddr + BINT_P_DFE_MASK, intEnable );
        	break;

		default:
		/* Unhandled interrupt base address */
		BDBG_ASSERT( false );
		break;
	}
}

static uint32_t BINT_P_7543_ReadStatus( BREG_Handle regHandle, uint32_t baseAddr )
{
	BDBG_MSG(("ReadStatus %#x", baseAddr));
	switch( baseAddr )
	{
	BINT_P_XPT_STATUS_CASES
		return BREG_Read32( regHandle, baseAddr + BINT_P_XPT_STATUS );
	BINT_P_XPT_RAVE_CASES
		return BREG_Read32( regHandle, baseAddr + BINT_P_RAVE_STATUS );
#if 0
	BINT_P_XPT_BUF_CASES
		return BREG_Read32( regHandle, baseAddr + BINT_P_XPT_BUF_STATUS );
#endif
	BINT_P_TIMER_CASES
		return BREG_Read32( regHandle, baseAddr + BINT_P_TIMER_STATUS );
	BINT_P_IRQ0_CASES
		return BREG_Read32( regHandle, baseAddr + BINT_P_IRQ0_STATUS );
	BINT_P_IRQ0_AON_CASES
		return BREG_Read32( regHandle, baseAddr + BINT_P_IRQ0_AON_STATUS );
	BINT_P_UPGSC_CASES
		return BREG_Read32( regHandle, baseAddr + BINT_P_UPGSC_ENABLE );
	BINT_P_PCROFFSET_CASES
		return BREG_Read32( regHandle, baseAddr + BINT_P_PCROFFSET_STATUS );

	    BINT_P_DFE_L2_CASES
            /* AP uses enable logic - 0 = masked, 1 = not masked */
            return BREG_Read32( regHandle, baseAddr + BINT_P_DFE_STATUS );

	default:
		/* Unhandled interrupt base address */
		BDBG_ASSERT( false );
		return 0;
	}
}

const BINT_Settings *BINT_7543_GetSettings( void )
{
	return &bint_7543Settings;
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


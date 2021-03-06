/***************************************************************************
 *     Copyright (c) 2006-2013, Broadcom Corporation
 *     All Rights Reserved
 *     Confidential Property of Broadcom Corporation
 *
 *  THIS SOFTWARE MAY ONLY BE USED SUBJECT TO AN EXECUTED SOFTWARE LICENSE
 *  AGREEMENT  BETWEEN THE USER AND BROADCOM.  YOU HAVE NO RIGHT TO USE OR
 *  EXPLOIT THIS MATERIAL EXCEPT SUBJECT TO THE TERMS OF SUCH AN AGREEMENT.
 *
 * $brcm_Workfile: $
 * $brcm_Revision: $
 * $brcm_Date:  
 *
 * Module Description:
 *   See Module Overview below.
 *
 * Revision History:
 *
 * $brcm_Log: $
 * 
 ***************************************************************************/

#include "bstd.h"
#include "bdbg.h"
#include "bkni.h"
#include "breg_mem.h"
#include "bchp.h"
#include "bchp_priv.h"
#include "bchp_7408.h"
#include "bchp_sun_top_ctrl.h"
#include "bchp_decode_sd_0.h"
#include "bchp_decode_ip_shim_0.h"
#include "bchp_sun_gisb_arb.h"
#include "bchp_memc_ddr23_shim_addr_cntl.h"
#include "bchp_memc_ddr_0.h"
#include "bchp_clk.h"
#include "bchp_pwr.h"

BDBG_MODULE(BCHP);

/* Miscellaneous macros. */
#define BCHP_P_MAJOR_REV_SHIFT          (4)

/* Chip info and features */
typedef struct BCHP_P_7408_Info
{
    uint32_t      ulChipIdReg; /* index into the table. */

    /* Chip Id */
    uint16_t      usChipId;

    /* Major revision */
    uint16_t      usMajor;

    /* Minor revision */
    uint16_t      usMinor;

    /* TODO: Other features or infos if needed */
} BCHP_P_7408_Info;


/* Lookup table for chip features and etc.
 * The are many times when the chip device id register
 * not conforming to the standard numbering convention. We do 
 * it this way to work-around those problems. 
 * 
 * TODO: Update this table to support new revisions.
 */
static const BCHP_P_7408_Info s_aChipInfoTable[] =
{
#if BCHP_VER == BCHP_VER_A0 
    /* A0 code will run on A0 and A1 */
    {0x74080000, BCHP_BCM7408, BCHP_MAJOR_A, BCHP_MINOR_0},  
#elif BCHP_VER == BCHP_VER_B0
    {0x74080010, BCHP_BCM7408, BCHP_MAJOR_B, BCHP_MINOR_0},  
#else
    #error "Port required"
#endif
};


/* Chip context */
typedef struct BCHP_P_7408_Context
{
    uint32_t                           ulBlackMagic;
    BREG_Handle                        hRegister;
    const BCHP_P_7408_Info            *pChipInfo;
	bool                               tracking;
} BCHP_P_7408_Context;

/* Max entry of lookup table */
#define BCHP_P_CHIP_INFO_MAX_ENTRY \
    (sizeof(s_aChipInfoTable) / sizeof(BCHP_P_7408_Info))

/* This macro checks for a validity of a handle, and
 * cast to context pointer. */
#define BCHP_P_GET_CONTEXT(handle, context) \
{ \
    if(!(handle) || \
       !((handle)->chipHandle) || \
       (((BCHP_P_7408_Context*)((handle)->chipHandle))->ulBlackMagic != \
       sizeof(BCHP_P_7408_Context))) \
    { \
        BDBG_ERR(("Corrupted context handle\n")); \
        (context) = NULL; \
    } \
    else \
    { \
        (context) = (BCHP_P_7408_Context*)((handle)->chipHandle); \
    } \
    BDBG_ASSERT(context); \
}

/* Static function prototypes */
static BERR_Code BCHP_P_Close7408
    ( BCHP_Handle                      hChip );

static BERR_Code BCHP_P_GetChipInfoComformWithBaseClass
    ( const BCHP_Handle                hChip,
      uint16_t                        *pusChipId,
      uint16_t                        *pusChipRev );

static BERR_Code BCHP_P_GetChipInfo
    ( const BCHP_Handle                hChip,
      uint16_t                        *pusChipId,
      uint16_t                        *pusChipMajorRev,
      uint16_t                        *pusChipMinorRev );

static BERR_Code BCHP_P_GetFeature
    ( const BCHP_Handle                hChip,
      const BCHP_Feature               eFeature,
      void                            *pFeatureValue );

static void BCHP_P_MonitorPvt
    ( BCHP_Handle                      hChip,
      BCHP_AvsSettings                *pSettings );

static BERR_Code BCHP_P_GetAvsData
    ( BCHP_Handle                      hChip,
      BCHP_AvsData                    *pData );

/***************************************************************************
 * Open BCM7408 Chip.
 *
 */
BERR_Code BCHP_Open7408
    ( BCHP_Handle                     *phChip,
      BREG_Handle                      hRegister )
{
    BCHP_P_Context *pChip;
    BCHP_P_7408_Context *p7408Chip;
    uint32_t ulChipIdReg;
    uint32_t ulIdx;
    uint32_t ulReg;
    uint32_t bankHeight=0, stripeWidth=0, dataWidth=0;
    uint32_t ddr0Device=0;
    bool ddr3=false;
    BERR_Code rc;

    BDBG_ENTER(BCHP_Open7408);

    if((!phChip) ||
       (!hRegister))
    {
        BDBG_ERR(("Invalid parameter\n"));
        return BERR_TRACE(BERR_INVALID_PARAMETER);
    }
    
    /* If error ocurr user get a NULL *phChip */
    *phChip = NULL;

    /* Alloc the base chip context. */
    pChip = (BCHP_P_Context*)(BKNI_Malloc(sizeof(BCHP_P_Context)));
    if(!pChip)
    {
        return BERR_TRACE(BERR_OUT_OF_SYSTEM_MEMORY);
    }

    /* Clear out the context and set defaults. */
    BKNI_Memset((void*)pChip, 0x0, sizeof(BCHP_P_Context));

    p7408Chip = (BCHP_P_7408_Context*)
        (BKNI_Malloc(sizeof(BCHP_P_7408_Context)));
    if(!p7408Chip)
    {
        BKNI_Free(pChip);
        return BERR_TRACE(BERR_OUT_OF_SYSTEM_MEMORY);
    }

    /* Clear out the context and set defaults. */
    BKNI_Memset((void*)p7408Chip, 0x0, sizeof(BCHP_P_7408_Context));

    /* Fill up the base chip context. */
    pChip->chipHandle       = (void*)p7408Chip;
    pChip->regHandle        = hRegister;
    pChip->pCloseFunc       = BCHP_P_Close7408;
    pChip->pGetChipInfoFunc = BCHP_P_GetChipInfoComformWithBaseClass;
    pChip->pGetFeatureFunc  = BCHP_P_GetFeature;
    pChip->pMonitorPvtFunc  = BCHP_P_MonitorPvt;
	pChip->pGetAvsDataFunc  = BCHP_P_GetAvsData;

    /* Fill up the chip context. */
    p7408Chip->ulBlackMagic = sizeof(BCHP_P_7408_Context);
    p7408Chip->hRegister    = hRegister;

    /* Open BCHP_PWR */
    rc = BCHP_PWR_Open(&pChip->pwrManager, pChip); 
    if (rc) {
        BKNI_Free(pChip);
        BKNI_Free(p7408Chip);
        return BERR_TRACE(rc);
    }

    /* Register id is use for indexing into the table. */
    ulChipIdReg = BREG_Read32(hRegister, BCHP_SUN_TOP_CTRL_PROD_REVISION);

/* decompose 32 bit chip id for use with printf format string %x%c%d
Example: 0x74010020 becomes "7401C0" */
#define PRINT_CHIP(CHIPID) \
    ((CHIPID)>>16), ((((CHIPID)&0xF0)>>4)+'A'), ((CHIPID)&0x0F)
            
    for(ulIdx = 0; ulIdx < BCHP_P_CHIP_INFO_MAX_ENTRY; ulIdx++) 
    {
        BDBG_MSG(("supported revision: %x%c%d", PRINT_CHIP(s_aChipInfoTable[ulIdx].ulChipIdReg)));
    }

    /* Lookup corresponding chip id. */
    for(ulIdx = 0; ulIdx < BCHP_P_CHIP_INFO_MAX_ENTRY; ulIdx++)
    {
        const BCHP_P_7408_Info *compareChipInfo = &s_aChipInfoTable[ulIdx];

        if(compareChipInfo->ulChipIdReg == ulChipIdReg)
        {
            /* Chip Information. */
            p7408Chip->pChipInfo = compareChipInfo;
            break;
        }
        else if (ulIdx == BCHP_P_CHIP_INFO_MAX_ENTRY - 1 && compareChipInfo->usMajor == (ulChipIdReg&0xF0)>>4)
        {
            /* This is a future minor revision. We will allow it with a WRN. */
            BDBG_WRN(("An unknown minor revision %x%c%d has been detected. Certain operations may result in erratic behavior. Please confirm this chip revision is supported with this software.",
                PRINT_CHIP(ulChipIdReg)));
            p7408Chip->pChipInfo = compareChipInfo;
            break;
        }
    }

    if(!p7408Chip->pChipInfo)
    {
        BKNI_Free(p7408Chip);
        BKNI_Free(pChip);
        BDBG_ERR(("unsupported revision: %x%c%d", PRINT_CHIP(ulChipIdReg)));
        return BERR_TRACE(BERR_INVALID_PARAMETER);
    }
    BDBG_MSG(("found %x%c%d", PRINT_CHIP(p7408Chip->pChipInfo->ulChipIdReg)));

    /* All done. now return the new fresh context to user. */
    *phChip = (BCHP_Handle)pChip;

    {
    /* Reset some cores. This is needed to avoid L1 interrupts before BXXX_Open can be called per core. */
    const uint32_t mask =
        BCHP_MASK( SUN_TOP_CTRL_SW_RESET, xpt_sw_reset)
        | BCHP_MASK( SUN_TOP_CTRL_SW_RESET, avd0_sw_reset)
        | BCHP_MASK( SUN_TOP_CTRL_SW_RESET, vec_sw_reset)
        | BCHP_MASK( SUN_TOP_CTRL_SW_RESET, bvn_sw_reset)
        | BCHP_MASK( SUN_TOP_CTRL_SW_RESET, aio_sw_reset);
     BREG_AtomicUpdate32(hRegister, BCHP_SUN_TOP_CTRL_SW_RESET, mask,
			BCHP_FIELD_DATA( SUN_TOP_CTRL_SW_RESET, xpt_sw_reset, 1 )
			| BCHP_FIELD_DATA( SUN_TOP_CTRL_SW_RESET, avd0_sw_reset, 1 )
			| BCHP_FIELD_DATA( SUN_TOP_CTRL_SW_RESET, vec_sw_reset, 1 )
			| BCHP_FIELD_DATA( SUN_TOP_CTRL_SW_RESET, bvn_sw_reset, 1 )
			| BCHP_FIELD_DATA( SUN_TOP_CTRL_SW_RESET, aio_sw_reset, 1 ));


    /* Now clear the reset. */
    BREG_AtomicUpdate32(hRegister, BCHP_SUN_TOP_CTRL_SW_RESET, mask, 0);
    }


    /* read the strap registers and program system stripe width and pfri bank height */
    ulReg = BREG_Read32(hRegister, BCHP_MEMC_DDR_0_CNTRLR_CONFIG);
    ddr0Device = BCHP_GET_FIELD_DATA(ulReg, MEMC_DDR_0_CNTRLR_CONFIG, DEVICE_TECH);

    BDBG_MSG(("Strap ddr0 Device Tech %x, ",ddr0Device));

    /* read the strap registers and program system stripe width and pfri bank height */
    ulReg = BREG_Read32(hRegister, BCHP_MEMC_DDR_0_DRAM_INIT_CNTRL);
    ddr3 = BCHP_GET_FIELD_DATA(ulReg, MEMC_DDR_0_DRAM_INIT_CNTRL, DDR_TECH);
    BDBG_MSG(("ddr%1d detected",ddr3 ? 3:2));


    /* Table to Determine Stripe Width and Bank Height based on Device Tech */ 
    dataWidth =0; /* dram width 16 bytes */
    {
	    switch(ddr0Device)
	    {
	    case 0: /* 256 Mbits Device Tech*/
		    stripeWidth =0; /* 64 bytes */
		    bankHeight = 0; /* 2 Mblks */
		    break;
	    case 1: /* 512 Mbits Device Tech*/
		    stripeWidth =0; /* 128 bytes */
		    bankHeight = 1; /* 2 Mblks */
		    break;
	    case 2: /* 1024 Mbits Device Tech*/
		    stripeWidth =0; /* 128 bytes */
		    bankHeight = 1; /* 2 Mblks */
		    break;
	    case 3: /* 2048 Mbits Device Tech*/
		    stripeWidth =0; /* 128 bytes */
		    bankHeight = 1; /* 2 Mblks */
		    break;
	    case 4: /* 4096 Mbits Device Tech*/
		    stripeWidth =0; /* 128 bytes */
		    bankHeight = 1; /* 2 Mblks */
		    break;
	    default:
		    BDBG_ERR(("Unknown Value in DDR Device Config Register"));
		    break;
	    }
	    
    }

#if BCHP_PWR_RESOURCE_AVD0
    BCHP_PWR_AcquireResource(pChip, BCHP_PWR_RESOURCE_AVD0);
#endif

    BREG_AtomicUpdate32(hRegister, 
			BCHP_DECODE_SD_0_REG_SD_PFRI_DATA_WIDTH, 
			BCHP_MASK(DECODE_SD_0_REG_SD_PFRI_DATA_WIDTH, pfri_data_width) |
			BCHP_MASK(DECODE_SD_0_REG_SD_PFRI_DATA_WIDTH, ddr3_mode),
			BCHP_FIELD_DATA( DECODE_SD_0_REG_SD_PFRI_DATA_WIDTH, pfri_data_width, dataWidth ) |
			BCHP_FIELD_DATA( DECODE_SD_0_REG_SD_PFRI_DATA_WIDTH, ddr3_mode, ddr3 )
			);

    BREG_AtomicUpdate32(hRegister, 
			BCHP_DECODE_SD_0_REG_SD_STRIPE_WIDTH,
			BCHP_MASK( DECODE_SD_0_REG_SD_STRIPE_WIDTH, pfri_bank_height) |
			BCHP_MASK( DECODE_SD_0_REG_SD_STRIPE_WIDTH, Stripe_Width),
			BCHP_FIELD_DATA( DECODE_SD_0_REG_SD_STRIPE_WIDTH, pfri_bank_height, bankHeight ) |
			BCHP_FIELD_DATA( DECODE_SD_0_REG_SD_STRIPE_WIDTH, Stripe_Width, stripeWidth )
			);

#if BCHP_PWR_RESOURCE_AVD0    
    BCHP_PWR_ReleaseResource(pChip, BCHP_PWR_RESOURCE_AVD0);
#endif
    
    BDBG_MSG(("data width=%#x, stripe width=%#x,pfri bank height=%#x",dataWidth,stripeWidth,bankHeight));

    /*
     *  Refer to SWCFE-294 for explanation on why the below 
     *  power down and power up is required.
     */

    /* TODO: this could be replaced with a simple BCHP_PWR_Acquire/Release call */
    /* Power down AVD clocks */
    ulReg = (BCHP_CLK_AVD0_CLK_PM_CTRL_DIS_108M_CLK_MASK |
             BCHP_CLK_AVD0_CLK_PM_CTRL_DIS_216M_CLK_MASK |
             BCHP_CLK_AVD0_CLK_PM_CTRL_DIS_AVD0_PROG_CLK_MASK);
    BREG_AtomicUpdate32(hRegister, BCHP_CLK_AVD0_CLK_PM_CTRL,ulReg,ulReg);

    /* Power up AVD clocks */
    ulReg = (BCHP_CLK_AVD0_CLK_PM_CTRL_DIS_108M_CLK_MASK |
             BCHP_CLK_AVD0_CLK_PM_CTRL_DIS_216M_CLK_MASK |
             BCHP_CLK_AVD0_CLK_PM_CTRL_DIS_AVD0_PROG_CLK_MASK);
    BREG_AtomicUpdate32(hRegister, BCHP_CLK_AVD0_CLK_PM_CTRL,ulReg,0);
    BDBG_LEAVE(BCHP_Open7408);
    return BERR_SUCCESS;
}


/***************************************************************************
 * {private}
 *
 */
static BERR_Code BCHP_P_Close7408
    ( BCHP_Handle                      hChip )
{
    BCHP_P_7408_Context *p7408Chip;

    BDBG_ENTER(BCHP_P_Close7408);
    
    BCHP_P_GET_CONTEXT(hChip, p7408Chip);

    if(!p7408Chip)
    {
        return BERR_TRACE(BERR_INVALID_PARAMETER);
    }

    BCHP_PWR_Close(hChip->pwrManager);

    /* Invalidate the magic number. */
    p7408Chip->ulBlackMagic = 0;

    BKNI_Free((void*)p7408Chip);
    BKNI_Free((void*)hChip);

    BDBG_LEAVE(BCHP_P_Close7408);
    return BERR_SUCCESS;
}


/***************************************************************************
 * {private}
 *
 */
static BERR_Code BCHP_P_GetChipInfoComformWithBaseClass
    ( const BCHP_Handle                hChip,
      uint16_t                        *pusChipId,
      uint16_t                        *pusChipRev )

{
    BERR_Code eStatus;
    uint16_t usMajor=0;
    uint16_t usMinor=0;

    eStatus = BERR_TRACE(BCHP_P_GetChipInfo(hChip, pusChipId,
        &usMajor, &usMinor));
    if(BERR_SUCCESS != eStatus)
    {
        return eStatus;
    }

    if(pusChipRev)
    {
        *pusChipRev = ((usMajor << BCHP_P_MAJOR_REV_SHIFT) + usMinor);
    }

    return BERR_SUCCESS;
}


/***************************************************************************
 * {private}
 *
 */
static BERR_Code BCHP_P_GetChipInfo
    ( const BCHP_Handle                hChip,
      uint16_t                        *pusChipId,
      uint16_t                        *pusChipMajorRev,
      uint16_t                        *pusChipMinorRev )
{
    const BCHP_P_7408_Context *p7408Chip;

    BDBG_ENTER(BCHP_P_GetChipInfo);

    BCHP_P_GET_CONTEXT(hChip, p7408Chip);

    if(!p7408Chip)
    {
        return BERR_TRACE(BERR_INVALID_PARAMETER);
    }

    if(pusChipId)
    {
        *pusChipId = p7408Chip->pChipInfo->usChipId;
    }

    if(pusChipMajorRev)
    {
        *pusChipMajorRev = p7408Chip->pChipInfo->usMajor;
    }

    if(pusChipMinorRev)
    {
        *pusChipMinorRev = p7408Chip->pChipInfo->usMinor;
    }

    BDBG_LEAVE(BCHP_P_GetChipInfo);
    return BERR_SUCCESS;
}

/***************************************************************************
 * {private}
 *
 */
static BERR_Code BCHP_P_GetFeature
    ( const BCHP_Handle                hChip,
      const BCHP_Feature               eFeature,
      void                            *pFeatureValue )
{
    BERR_Code            rc = BERR_UNKNOWN;
    BCHP_P_7408_Context *p7408Chip;
    uint32_t             ulBondStatus;

    BDBG_ENTER(BCHP_P_GetFeature);
    
    /* get base context */
    BCHP_P_GET_CONTEXT(hChip, p7408Chip);

    /* read bond-out status common for many features */
    ulBondStatus = BREG_Read32(p7408Chip->hRegister,
			       BCHP_SUN_TOP_CTRL_OTP_OPTION_STATUS_0);
        
    /* which feature? */
    switch (eFeature)
    {
    case BCHP_Feature_e3DGraphicsCapable:
	    /* 3D capable? (bool) */
	    *(bool *)pFeatureValue = BCHP_GET_FIELD_DATA(ulBondStatus,SUN_TOP_CTRL_OTP_OPTION_STATUS_0, 
							 otp_option_3d_disable ) ? false : true;
	    rc = BERR_SUCCESS;
	    rc = BERR_SUCCESS;
	    break;

    case BCHP_Feature_eDvoPortCapable:
	    /* dvo port capable? (bool) */
	    *(bool *)pFeatureValue = false;
	    rc = BERR_SUCCESS;
	    break;
	    
    case BCHP_Feature_eMacrovisionCapable:
	    /* macrovision capable? (bool) */
	    *(bool *)pFeatureValue = BCHP_GET_FIELD_DATA(ulBondStatus,SUN_TOP_CTRL_OTP_OPTION_STATUS_0,
							 otp_option_macrovision_enable ) ? true : false;
	    rc = BERR_SUCCESS;
	    break;
        
    case BCHP_Feature_eMpegDecoderCount:
	    /* number of MPEG decoders (int) */
	    *(int *)pFeatureValue = 1;
	    rc = BERR_SUCCESS;
	    break;
	    
    case BCHP_Feature_eHdcpCapable:
	    /* HDCP capable? (bool) */
	    *(bool *)pFeatureValue = BCHP_GET_FIELD_DATA(ulBondStatus,SUN_TOP_CTRL_OTP_OPTION_STATUS_0,
							 otp_option_hdcp_disable ) ? false : true;
	    rc = BERR_SUCCESS;
	    break;
        
    case BCHP_Feature_e3desCapable:
	    /* 3DES capable? (bool) */
	    *(bool *)pFeatureValue = true;
	    rc = BERR_SUCCESS;
	    break;

    case BCHP_Feature_e1080pCapable:
	    /* 1080p Capable? (bool) */
	    *(bool *)pFeatureValue = false;
	    rc = BERR_SUCCESS;
	    break;      
        
    default:
        rc = BCHP_P_GetDefaultFeature(hChip, eFeature, pFeatureValue);
        break;
    }
    
    /* return result */
    BDBG_LEAVE(BCHP_P_GetFeature);
    return rc;
}


#define REF_KHZ            108000
#define MIN_REF_CLK_TICKS  5000
#define NUM_RING_OSC       12

#define OSC_MAX_KHZ 3670 
#define OSC_MIN_KHZ 2380

#define OSC_HYST_KHZ 120        /* 5% of the Vdd min */

#define HARD_STOP_DEFAULT		-11

static uint32_t BCHP_P_PvtViewClk(BREG_Handle hRegister, int osc_idx)
{
	uint32_t cnt, freq, reg;

	/* stop counters & reset */
	reg = BREG_Read32(hRegister, 
			  BCHP_CLK_STOP_COUNTER);
	reg |= 
	  BCHP_FIELD_DATA(CLK_STOP_COUNTER, stop_ref_clock_cntr, 1) |
	  BCHP_FIELD_DATA(CLK_STOP_COUNTER, stop_view_clock_cntr, 1);
	BREG_Write32(hRegister, 
		     BCHP_CLK_STOP_COUNTER,  
		     reg);		     

	reg = BREG_Read32(hRegister, 
			  BCHP_CLK_RESET_COUNTER);
	reg |= 
	  BCHP_FIELD_DATA(CLK_RESET_COUNTER, reset_counter, 1) |
	  BCHP_FIELD_DATA(CLK_RESET_COUNTER, reset_full_ref_count_done, 1);
        BREG_Write32(hRegister, 
		     BCHP_CLK_RESET_COUNTER, 
		     reg);

	reg &= ~(
		 BCHP_MASK(CLK_RESET_COUNTER, reset_counter) |
		 BCHP_MASK(CLK_RESET_COUNTER, reset_full_ref_count_done)
		 );
	BREG_Write32(hRegister, 
		     BCHP_CLK_RESET_COUNTER, 
		     reg);

	/* enable selected ring osc */
        BREG_Write32(hRegister, BCHP_CLK_RING_OSC_ENABLE, 0x1 << osc_idx);  

 	/* select view clock */     
	reg = BREG_Read32(hRegister, 
			  BCHP_CLK_VIEW_CLOCK_SELECT);
	reg &= ~(
		 BCHP_MASK(CLK_VIEW_CLOCK_SELECT, view_clock_select)
		 );
	reg |= BCHP_FIELD_DATA(CLK_VIEW_CLOCK_SELECT, view_clock_select, (osc_idx+16));
	BREG_Write32(hRegister, BCHP_CLK_VIEW_CLOCK_SELECT, reg);

	/* start the clocks */
	reg = BREG_Read32(hRegister, 
			  BCHP_CLK_STOP_COUNTER);
	reg &= ~(
		 BCHP_MASK(CLK_STOP_COUNTER, stop_ref_clock_cntr) |
		 BCHP_MASK(CLK_STOP_COUNTER, stop_view_clock_cntr)
		 );
	BREG_Write32(hRegister, 
		     BCHP_CLK_STOP_COUNTER,  
		     reg);
	
	while ( (cnt = BREG_Read32(hRegister, BCHP_CLK_REF_CLOCK_COUNTER)) < MIN_REF_CLK_TICKS ) {}	    	

        /* stop the clocks */
	reg |= 
	  BCHP_FIELD_DATA(CLK_STOP_COUNTER, stop_ref_clock_cntr, 1) |
	  BCHP_FIELD_DATA(CLK_STOP_COUNTER, stop_view_clock_cntr, 1);
	BREG_Write32(hRegister, 
		     BCHP_CLK_STOP_COUNTER,  
		     reg);

	/* disable ring oscs */
        BREG_Write32(hRegister, BCHP_CLK_RING_OSC_ENABLE, 0x0); 
	
	freq = (REF_KHZ * BREG_Read32(hRegister, BCHP_CLK_VIEW_CLOCK_COUNTER))
	  / BREG_Read32(hRegister, BCHP_CLK_REF_CLOCK_COUNTER);

	return freq;
}

	/* The Output voltage selection is 1.00125V -> 1.40V in steps of 12.5mV (where 0=1.2V skipped entry at 16 where 1.2V would be) */
	/* [0=1.2V] 1=1.0125V, 2=1.025V, ... 15=0xf=1.1875V, [] 16=0x10=1.12125V, 17=11=0x11=1.1225V, ... 30=0x1E=1.3875, 31=0x1F=1.40V */
	/* When stepping up we jump from 15 to 0 then to 16. When stepping down we jump from 16 to 0 and then to 15. */

static void BCHP_P_PvtStepUp(BREG_Handle hRegister)
{
	uint32_t	reg = 0;
	uint32_t	sw_reg_value = 0;

	reg = BREG_Read32(hRegister, BCHP_CLK_SWREG_VALUE);
	sw_reg_value = BCHP_GET_FIELD_DATA(reg, CLK_SWREG_VALUE, swreg_vselect);

	if (sw_reg_value < 0x1F) {
	    if(sw_reg_value == 0) {
		 sw_reg_value = 0x10;
	    } else if(sw_reg_value == 0xF) {
		 sw_reg_value = 0;
	    } else {
		 sw_reg_value++;
	    }	
	    reg &= ~(
		     BCHP_MASK(CLK_SWREG_VALUE, swreg_vselect)
		     );
	    reg |= BCHP_FIELD_DATA(CLK_SWREG_VALUE, swreg_vselect, sw_reg_value);
	    BREG_Write32(hRegister, BCHP_CLK_SWREG_VALUE, reg);
	}
}

static void BCHP_P_PvtStepDown(BREG_Handle hRegister)	
{
	uint32_t	reg = 0;
	uint32_t	sw_reg_value = 0;

	reg = BREG_Read32(hRegister, BCHP_CLK_SWREG_VALUE);
	sw_reg_value = BCHP_GET_FIELD_DATA(reg, CLK_SWREG_VALUE, swreg_vselect);
	
	if(sw_reg_value == 0){
		sw_reg_value = 0xF;
	} else if(sw_reg_value == 0x10) {
		sw_reg_value = 0;
	} else  if (sw_reg_value > 0x1){
		sw_reg_value--;	
	}	 
	reg &= ~(
		 BCHP_MASK(CLK_SWREG_VALUE, swreg_vselect)
		 );
	reg |= BCHP_FIELD_DATA(CLK_SWREG_VALUE, swreg_vselect, sw_reg_value);
	BREG_Write32(hRegister, BCHP_CLK_SWREG_VALUE, reg);	
}

/* returns an offset value between -15 and +16 where -15=1.0215V, 0=1.2V, and 16=1.40V */
static int BCHP_P_PvtGetVoltageOffset(BREG_Handle hRegister)
{
	uint32_t  reg = 0;
	int       offset = 0;
	reg = BREG_Read32(hRegister, BCHP_CLK_SWREG_VALUE);
	reg = BCHP_GET_FIELD_DATA(reg, CLK_SWREG_VALUE, swreg_vselect);

	if(reg == 0) { 
	    offset = 0;
	} else if (reg < 0x10) {
	    offset = reg - 0x10;
	} else {
	    offset = reg - 0xF;
	}
	    
	return offset;
}

/* returns an integer representation of the voltage based on the accuracy factor */
static int BCHP_P_GetIntegerVoltage( BCHP_P_7408_Context *p7408Chip )
{
#define ACCURACY 10000 /* rely on the pre-processor to do the floating point math before compile */
	return (1.2*ACCURACY) + BCHP_P_PvtGetVoltageOffset(p7408Chip->hRegister) * (.0125*ACCURACY);
}
#if 0
/* returns a floating point value of the current voltage */
static float BCHP_P_GetFloatVoltage( BCHP_P_7408_Context *p7408Chip )
{
	return 1.2 + BCHP_P_PvtGetVoltageOffset(p7408Chip->hRegister) * .0125;
}
#endif

static void BCHP_P_MonitorPvt( BCHP_Handle hChip, BCHP_AvsSettings *pSettings )
{
    uint32_t	freq[NUM_RING_OSC], min_freq, max_freq, min_idx, max_idx;
    int 	i, hardStop, maxVStop;
    BCHP_P_7408_Context *p7408Chip;

    BDBG_ENTER(BCHP_Monitor_Pvt);

    BCHP_P_GET_CONTEXT(hChip, p7408Chip);
    
    hardStop = HARD_STOP_DEFAULT + pSettings->hardStopOffset;
    BDBG_MSG(("PVT: hardstop = %d, hardStopOffset = %d", hardStop, pSettings->hardStopOffset ));

    maxVStop = 16 - pSettings->maxVoltageStopOffset;
    BDBG_MSG(("PVT: maxVstop = %d, maxVoltageStopOffset = %d", maxVStop, pSettings->maxVoltageStopOffset ));

    min_freq = 1000000;
    max_freq = 0;
    min_idx  = 0;
    max_idx  = 0;          
    
    /* sample each ring osc and record freq, min & max */
    for (i=0; i<NUM_RING_OSC; i++) {
	
	freq[i] = BCHP_P_PvtViewClk(p7408Chip->hRegister, i);
	
	if (freq[i] < min_freq) {
	    min_idx = i;
	    min_freq = freq[i];
	}		
      
	if (freq[i] > max_freq) {
	    max_idx=i;
	    max_freq = freq[i];
	}
                          
    }

    BDBG_MSG(("PVT: Local values %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d", 
	      freq[0], freq[1], freq[2], freq[3], freq[4], freq[5], 
	      freq[6], freq[7], freq[8], freq[9], freq[10], freq[11]));
    BDBG_MSG(("PVT: Min[%d]= %d, Max[%d]= %d", min_idx, min_freq, max_idx, max_freq));
    

    if(max_freq > OSC_MAX_KHZ){
	BCHP_P_PvtStepDown(p7408Chip->hRegister);
	BDBG_MSG(("PVT: Step down: idx = %d  min_freq = %d offset = %d", min_idx, min_freq, BCHP_P_PvtGetVoltageOffset(p7408Chip->hRegister) ));
    } else if (min_freq < OSC_MIN_KHZ) {    
	if ( BCHP_P_PvtGetVoltageOffset(p7408Chip->hRegister) == maxVStop) {
	    BDBG_MSG(("PVT: reached maxVStop = %d", BCHP_P_PvtGetVoltageOffset(p7408Chip->hRegister) ));
	}
	else {
	    BCHP_P_PvtStepUp(p7408Chip->hRegister);	
	    BDBG_MSG(("PVT: Step up: idx = %d  min_freq = %d offset = %d", min_idx, min_freq, BCHP_P_PvtGetVoltageOffset(p7408Chip->hRegister) ));    
	}
    }
    else {
	/* step up if we are under hard stop (this should never occur)*/
	if (BCHP_P_PvtGetVoltageOffset(p7408Chip->hRegister) < hardStop) {	  
    	            BCHP_P_PvtStepUp(p7408Chip->hRegister);	
    	            BDBG_MSG(("PVT: offset = %d", BCHP_P_PvtGetVoltageOffset(p7408Chip->hRegister) ));
	}
	
	/* not to fast or too slow so reduce until "hard_stop"  plus some hysteries*/
	if ((BCHP_P_PvtGetVoltageOffset(p7408Chip->hRegister) > hardStop) && (min_freq > (OSC_MIN_KHZ + OSC_HYST_KHZ))){
	    BCHP_P_PvtStepDown(p7408Chip->hRegister);	
	    BDBG_MSG(("PVT: offset = %d", BCHP_P_PvtGetVoltageOffset(p7408Chip->hRegister) ));
	}
    }

	p7408Chip->tracking = true; /* if we've been run at least once then we should be tracking */
}

static BERR_Code BCHP_P_GetAvsData( BCHP_Handle hChip, BCHP_AvsData *pData )
{
    BCHP_P_7408_Context *p7408Chip;

    BDBG_ENTER(BCHP_P_GetAvsData);

    BCHP_P_GET_CONTEXT(hChip, p7408Chip);

    BDBG_ASSERT(pData);

#if 1
    pData->voltage = BCHP_P_GetIntegerVoltage(p7408Chip) / 10; /* return data as milli-volts */
    pData->temperature = 0; /* this part doesn't have a means to measure the temperature */
    pData->enabled = false; /* until code is added to CFE this can be assumed to be non-valid */
    pData->tracking = p7408Chip->tracking;
    return BERR_SUCCESS;
#else
    return BERR_TRACE(BERR_INVALID_PARAMETER);
#endif
}

/* End of File */

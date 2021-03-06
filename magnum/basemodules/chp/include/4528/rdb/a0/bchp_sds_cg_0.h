/***************************************************************************
 *     Copyright (c) 1999-2011, Broadcom Corporation
 *     All Rights Reserved
 *     Confidential Property of Broadcom Corporation
 *
 *
 * THIS SOFTWARE MAY ONLY BE USED SUBJECT TO AN EXECUTED SOFTWARE LICENSE
 * AGREEMENT  BETWEEN THE USER AND BROADCOM.  YOU HAVE NO RIGHT TO USE OR
 * EXPLOIT THIS MATERIAL EXCEPT SUBJECT TO THE TERMS OF SUCH AN AGREEMENT.
 *
 * $brcm_Workfile: $
 * $brcm_Revision: $
 * $brcm_Date: $
 *
 * Module Description:
 *                     DO NOT EDIT THIS FILE DIRECTLY
 *
 * This module was generated magically with RDB from a source description
 * file. You must edit the source file for changes to be made to this file.
 *
 *
 * Date:           Generated on         Wed Jan 12 18:41:18 2011
 *                 MD5 Checksum         6e6727f6c827233acdd395c9a9032c98
 *
 * Compiled with:  RDB Utility          combo_header.pl
 *                 RDB Parser           3.0
 *                 unknown              unknown
 *                 Perl Interpreter     5.008008
 *                 Operating System     linux
 *
 * Revision History:
 *
 * $brcm_Log: $
 * 
 ***************************************************************************/

#ifndef BCHP_SDS_CG_0_H__
#define BCHP_SDS_CG_0_H__

/***************************************************************************
 *SDS_CG_0 - SDS Clockgen Register Set 0
 ***************************************************************************/
#define BCHP_SDS_CG_0_RSTCTL                     0x000b0000 /* Reset Control */
#define BCHP_SDS_CG_0_CGDIV00                    0x000b0010 /* Clock Generator Divider register 0 (Formerly,CGDIV4,CGDIV3,CGDIV7[7:4],CGMISC,CGCTRL) */
#define BCHP_SDS_CG_0_CGDIV01                    0x000b0014 /* Clock Generator Divider register 1 (Formerly,CGDIV11,CGDIV10,CGDIV9,CGDIV8) */
#define BCHP_SDS_CG_0_SPLL_NPDIV                 0x000b0020 /* Sample Clock PLL Feedback Divider Control */
#define BCHP_SDS_CG_0_SPLL_MDIV_CTRL             0x000b0024 /* Sample Clock PLL Post-divider Control */
#define BCHP_SDS_CG_0_SPLL_CTRL                  0x000b0028 /* Sample Clock PLL Control */
#define BCHP_SDS_CG_0_SPLL_SSC_CTRL1             0x000b002c /* Sample Clock PLL Spread Spectrum Control 1 */
#define BCHP_SDS_CG_0_SPLL_SSC_CTRL0             0x000b0030 /* Sample Clock PLL Spread Spectrum Control 0 */
#define BCHP_SDS_CG_0_SPLL_STATUS                0x000b0034 /* Sample Clock PLL Status */
#define BCHP_SDS_CG_0_SPLL_PWRDN_RST             0x000b0038 /* Sample Clock PLL Power Down and Reset Control */

/***************************************************************************
 *RSTCTL - Reset Control
 ***************************************************************************/
/* SDS_CG_0 :: RSTCTL :: reserved0 [31:08] */
#define BCHP_SDS_CG_0_RSTCTL_reserved0_MASK                        0xffffff00
#define BCHP_SDS_CG_0_RSTCTL_reserved0_SHIFT                       8

/* SDS_CG_0 :: RSTCTL :: reserved_for_eco1 [07:01] */
#define BCHP_SDS_CG_0_RSTCTL_reserved_for_eco1_MASK                0x000000fe
#define BCHP_SDS_CG_0_RSTCTL_reserved_for_eco1_SHIFT               1

/* SDS_CG_0 :: RSTCTL :: rcvr_dp_rst [00:00] */
#define BCHP_SDS_CG_0_RSTCTL_rcvr_dp_rst_MASK                      0x00000001
#define BCHP_SDS_CG_0_RSTCTL_rcvr_dp_rst_SHIFT                     0

/***************************************************************************
 *CGDIV00 - Clock Generator Divider register 0 (Formerly,CGDIV4,CGDIV3,CGDIV7[7:4],CGMISC,CGCTRL)
 ***************************************************************************/
/* SDS_CG_0 :: CGDIV00 :: reserved0 [31:16] */
#define BCHP_SDS_CG_0_CGDIV00_reserved0_MASK                       0xffff0000
#define BCHP_SDS_CG_0_CGDIV00_reserved0_SHIFT                      16

/* SDS_CG_0 :: CGDIV00 :: delsig_div_chng [15:15] */
#define BCHP_SDS_CG_0_CGDIV00_delsig_div_chng_MASK                 0x00008000
#define BCHP_SDS_CG_0_CGDIV00_delsig_div_chng_SHIFT                15

/* SDS_CG_0 :: CGDIV00 :: reserved_for_eco1 [14:12] */
#define BCHP_SDS_CG_0_CGDIV00_reserved_for_eco1_MASK               0x00007000
#define BCHP_SDS_CG_0_CGDIV00_reserved_for_eco1_SHIFT              12

/* SDS_CG_0 :: CGDIV00 :: delsig_div [11:08] */
#define BCHP_SDS_CG_0_CGDIV00_delsig_div_MASK                      0x00000f00
#define BCHP_SDS_CG_0_CGDIV00_delsig_div_SHIFT                     8

/* SDS_CG_0 :: CGDIV00 :: reserved_for_eco2 [07:02] */
#define BCHP_SDS_CG_0_CGDIV00_reserved_for_eco2_MASK               0x000000fc
#define BCHP_SDS_CG_0_CGDIV00_reserved_for_eco2_SHIFT              2

/* SDS_CG_0 :: CGDIV00 :: pll_clk_sel [01:01] */
#define BCHP_SDS_CG_0_CGDIV00_pll_clk_sel_MASK                     0x00000002
#define BCHP_SDS_CG_0_CGDIV00_pll_clk_sel_SHIFT                    1

/* SDS_CG_0 :: CGDIV00 :: und2x [00:00] */
#define BCHP_SDS_CG_0_CGDIV00_und2x_MASK                           0x00000001
#define BCHP_SDS_CG_0_CGDIV00_und2x_SHIFT                          0

/***************************************************************************
 *CGDIV01 - Clock Generator Divider register 1 (Formerly,CGDIV11,CGDIV10,CGDIV9,CGDIV8)
 ***************************************************************************/
/* SDS_CG_0 :: CGDIV01 :: reserved_for_eco0 [31:27] */
#define BCHP_SDS_CG_0_CGDIV01_reserved_for_eco0_MASK               0xf8000000
#define BCHP_SDS_CG_0_CGDIV01_reserved_for_eco0_SHIFT              27

/* SDS_CG_0 :: CGDIV01 :: i2c_div1 [26:16] */
#define BCHP_SDS_CG_0_CGDIV01_i2c_div1_MASK                        0x07ff0000
#define BCHP_SDS_CG_0_CGDIV01_i2c_div1_SHIFT                       16

/* SDS_CG_0 :: CGDIV01 :: reserved_for_eco1 [15:11] */
#define BCHP_SDS_CG_0_CGDIV01_reserved_for_eco1_MASK               0x0000f800
#define BCHP_SDS_CG_0_CGDIV01_reserved_for_eco1_SHIFT              11

/* SDS_CG_0 :: CGDIV01 :: i2c_div2 [10:00] */
#define BCHP_SDS_CG_0_CGDIV01_i2c_div2_MASK                        0x000007ff
#define BCHP_SDS_CG_0_CGDIV01_i2c_div2_SHIFT                       0

/***************************************************************************
 *SPLL_NPDIV - Sample Clock PLL Feedback Divider Control
 ***************************************************************************/
/* SDS_CG_0 :: SPLL_NPDIV :: ndiv_int [31:24] */
#define BCHP_SDS_CG_0_SPLL_NPDIV_ndiv_int_MASK                     0xff000000
#define BCHP_SDS_CG_0_SPLL_NPDIV_ndiv_int_SHIFT                    24

/* SDS_CG_0 :: SPLL_NPDIV :: ndiv_frac [23:04] */
#define BCHP_SDS_CG_0_SPLL_NPDIV_ndiv_frac_MASK                    0x00fffff0
#define BCHP_SDS_CG_0_SPLL_NPDIV_ndiv_frac_SHIFT                   4

/* SDS_CG_0 :: SPLL_NPDIV :: reserved_for_eco0 [03:03] */
#define BCHP_SDS_CG_0_SPLL_NPDIV_reserved_for_eco0_MASK            0x00000008
#define BCHP_SDS_CG_0_SPLL_NPDIV_reserved_for_eco0_SHIFT           3

/* SDS_CG_0 :: SPLL_NPDIV :: pdiv [02:00] */
#define BCHP_SDS_CG_0_SPLL_NPDIV_pdiv_MASK                         0x00000007
#define BCHP_SDS_CG_0_SPLL_NPDIV_pdiv_SHIFT                        0

/***************************************************************************
 *SPLL_MDIV_CTRL - Sample Clock PLL Post-divider Control
 ***************************************************************************/
/* SDS_CG_0 :: SPLL_MDIV_CTRL :: reserved0 [31:24] */
#define BCHP_SDS_CG_0_SPLL_MDIV_CTRL_reserved0_MASK                0xff000000
#define BCHP_SDS_CG_0_SPLL_MDIV_CTRL_reserved0_SHIFT               24

/* SDS_CG_0 :: SPLL_MDIV_CTRL :: reserved_for_eco1 [23:20] */
#define BCHP_SDS_CG_0_SPLL_MDIV_CTRL_reserved_for_eco1_MASK        0x00f00000
#define BCHP_SDS_CG_0_SPLL_MDIV_CTRL_reserved_for_eco1_SHIFT       20

/* SDS_CG_0 :: SPLL_MDIV_CTRL :: pll_ctrl_msb [19:11] */
#define BCHP_SDS_CG_0_SPLL_MDIV_CTRL_pll_ctrl_msb_MASK             0x000ff800
#define BCHP_SDS_CG_0_SPLL_MDIV_CTRL_pll_ctrl_msb_SHIFT            11

/* SDS_CG_0 :: SPLL_MDIV_CTRL :: channel_en [10:10] */
#define BCHP_SDS_CG_0_SPLL_MDIV_CTRL_channel_en_MASK               0x00000400
#define BCHP_SDS_CG_0_SPLL_MDIV_CTRL_channel_en_SHIFT              10

/* SDS_CG_0 :: SPLL_MDIV_CTRL :: channel_hold [09:09] */
#define BCHP_SDS_CG_0_SPLL_MDIV_CTRL_channel_hold_MASK             0x00000200
#define BCHP_SDS_CG_0_SPLL_MDIV_CTRL_channel_hold_SHIFT            9

/* SDS_CG_0 :: SPLL_MDIV_CTRL :: channel_load_en [08:08] */
#define BCHP_SDS_CG_0_SPLL_MDIV_CTRL_channel_load_en_MASK          0x00000100
#define BCHP_SDS_CG_0_SPLL_MDIV_CTRL_channel_load_en_SHIFT         8

/* SDS_CG_0 :: SPLL_MDIV_CTRL :: mdiv [07:00] */
#define BCHP_SDS_CG_0_SPLL_MDIV_CTRL_mdiv_MASK                     0x000000ff
#define BCHP_SDS_CG_0_SPLL_MDIV_CTRL_mdiv_SHIFT                    0

/***************************************************************************
 *SPLL_CTRL - Sample Clock PLL Control
 ***************************************************************************/
/* SDS_CG_0 :: SPLL_CTRL :: Kp [31:28] */
#define BCHP_SDS_CG_0_SPLL_CTRL_Kp_MASK                            0xf0000000
#define BCHP_SDS_CG_0_SPLL_CTRL_Kp_SHIFT                           28

/* SDS_CG_0 :: SPLL_CTRL :: Ki [27:25] */
#define BCHP_SDS_CG_0_SPLL_CTRL_Ki_MASK                            0x0e000000
#define BCHP_SDS_CG_0_SPLL_CTRL_Ki_SHIFT                           25

/* SDS_CG_0 :: SPLL_CTRL :: Ka [24:22] */
#define BCHP_SDS_CG_0_SPLL_CTRL_Ka_MASK                            0x01c00000
#define BCHP_SDS_CG_0_SPLL_CTRL_Ka_SHIFT                           22

/* SDS_CG_0 :: SPLL_CTRL :: refclk_sel [21:21] */
#define BCHP_SDS_CG_0_SPLL_CTRL_refclk_sel_MASK                    0x00200000
#define BCHP_SDS_CG_0_SPLL_CTRL_refclk_sel_SHIFT                   21

/* SDS_CG_0 :: SPLL_CTRL :: pll_ctrl [20:00] */
#define BCHP_SDS_CG_0_SPLL_CTRL_pll_ctrl_MASK                      0x001fffff
#define BCHP_SDS_CG_0_SPLL_CTRL_pll_ctrl_SHIFT                     0

/***************************************************************************
 *SPLL_SSC_CTRL1 - Sample Clock PLL Spread Spectrum Control 1
 ***************************************************************************/
/* SDS_CG_0 :: SPLL_SSC_CTRL1 :: reserved0 [31:16] */
#define BCHP_SDS_CG_0_SPLL_SSC_CTRL1_reserved0_MASK                0xffff0000
#define BCHP_SDS_CG_0_SPLL_SSC_CTRL1_reserved0_SHIFT               16

/* SDS_CG_0 :: SPLL_SSC_CTRL1 :: ssc_step [15:00] */
#define BCHP_SDS_CG_0_SPLL_SSC_CTRL1_ssc_step_MASK                 0x0000ffff
#define BCHP_SDS_CG_0_SPLL_SSC_CTRL1_ssc_step_SHIFT                0

/***************************************************************************
 *SPLL_SSC_CTRL0 - Sample Clock PLL Spread Spectrum Control 0
 ***************************************************************************/
/* SDS_CG_0 :: SPLL_SSC_CTRL0 :: reserved0 [31:24] */
#define BCHP_SDS_CG_0_SPLL_SSC_CTRL0_reserved0_MASK                0xff000000
#define BCHP_SDS_CG_0_SPLL_SSC_CTRL0_reserved0_SHIFT               24

/* SDS_CG_0 :: SPLL_SSC_CTRL0 :: reserved_for_eco1 [23:23] */
#define BCHP_SDS_CG_0_SPLL_SSC_CTRL0_reserved_for_eco1_MASK        0x00800000
#define BCHP_SDS_CG_0_SPLL_SSC_CTRL0_reserved_for_eco1_SHIFT       23

/* SDS_CG_0 :: SPLL_SSC_CTRL0 :: ssc_mode [22:22] */
#define BCHP_SDS_CG_0_SPLL_SSC_CTRL0_ssc_mode_MASK                 0x00400000
#define BCHP_SDS_CG_0_SPLL_SSC_CTRL0_ssc_mode_SHIFT                22

/* SDS_CG_0 :: SPLL_SSC_CTRL0 :: ssc_limit [21:00] */
#define BCHP_SDS_CG_0_SPLL_SSC_CTRL0_ssc_limit_MASK                0x003fffff
#define BCHP_SDS_CG_0_SPLL_SSC_CTRL0_ssc_limit_SHIFT               0

/***************************************************************************
 *SPLL_STATUS - Sample Clock PLL Status
 ***************************************************************************/
/* SDS_CG_0 :: SPLL_STATUS :: reserved0 [31:13] */
#define BCHP_SDS_CG_0_SPLL_STATUS_reserved0_MASK                   0xffffe000
#define BCHP_SDS_CG_0_SPLL_STATUS_reserved0_SHIFT                  13

/* SDS_CG_0 :: SPLL_STATUS :: lock [12:12] */
#define BCHP_SDS_CG_0_SPLL_STATUS_lock_MASK                        0x00001000
#define BCHP_SDS_CG_0_SPLL_STATUS_lock_SHIFT                       12

/* SDS_CG_0 :: SPLL_STATUS :: stat_out [11:00] */
#define BCHP_SDS_CG_0_SPLL_STATUS_stat_out_MASK                    0x00000fff
#define BCHP_SDS_CG_0_SPLL_STATUS_stat_out_SHIFT                   0

/***************************************************************************
 *SPLL_PWRDN_RST - Sample Clock PLL Power Down and Reset Control
 ***************************************************************************/
/* SDS_CG_0 :: SPLL_PWRDN_RST :: reserved0 [31:08] */
#define BCHP_SDS_CG_0_SPLL_PWRDN_RST_reserved0_MASK                0xffffff00
#define BCHP_SDS_CG_0_SPLL_PWRDN_RST_reserved0_SHIFT               8

/* SDS_CG_0 :: SPLL_PWRDN_RST :: reserved_for_eco1 [07:03] */
#define BCHP_SDS_CG_0_SPLL_PWRDN_RST_reserved_for_eco1_MASK        0x000000f8
#define BCHP_SDS_CG_0_SPLL_PWRDN_RST_reserved_for_eco1_SHIFT       3

/* SDS_CG_0 :: SPLL_PWRDN_RST :: pwrdn [02:02] */
#define BCHP_SDS_CG_0_SPLL_PWRDN_RST_pwrdn_MASK                    0x00000004
#define BCHP_SDS_CG_0_SPLL_PWRDN_RST_pwrdn_SHIFT                   2

/* SDS_CG_0 :: SPLL_PWRDN_RST :: dreset [01:01] */
#define BCHP_SDS_CG_0_SPLL_PWRDN_RST_dreset_MASK                   0x00000002
#define BCHP_SDS_CG_0_SPLL_PWRDN_RST_dreset_SHIFT                  1

/* SDS_CG_0 :: SPLL_PWRDN_RST :: areset [00:00] */
#define BCHP_SDS_CG_0_SPLL_PWRDN_RST_areset_MASK                   0x00000001
#define BCHP_SDS_CG_0_SPLL_PWRDN_RST_areset_SHIFT                  0

#endif /* #ifndef BCHP_SDS_CG_0_H__ */

/* End of File */

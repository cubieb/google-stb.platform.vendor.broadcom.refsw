/***************************************************************************
 *     Copyright (c) 1999-2010, Broadcom Corporation
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
 * Date:           Generated on         Fri May  7 20:18:23 2010
 *                 MD5 Checksum         9170aeef162fecc7d1a70fbd8134c303
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

#ifndef BCHP_PM_H__
#define BCHP_PM_H__

/***************************************************************************
 *PM - Peripheral Module Configuration
 ***************************************************************************/
#define BCHP_PM_CONFIG                           0x00306180 /* PERIPHERAL MODULE CONFIGURATION REGISTER */
#define BCHP_PM_CLK_CTRL                         0x00306184 /* UPG Clock control register */

/***************************************************************************
 *CONFIG - PERIPHERAL MODULE CONFIGURATION REGISTER
 ***************************************************************************/
/* PM :: CONFIG :: reserved0 [31:23] */
#define BCHP_PM_CONFIG_reserved0_MASK                              0xff800000
#define BCHP_PM_CONFIG_reserved0_SHIFT                             23

/* PM :: CONFIG :: uart_disable_busy_wr [22:22] */
#define BCHP_PM_CONFIG_uart_disable_busy_wr_MASK                   0x00400000
#define BCHP_PM_CONFIG_uart_disable_busy_wr_SHIFT                  22

/* PM :: CONFIG :: uart_enable_busy_detect [21:21] */
#define BCHP_PM_CONFIG_uart_enable_busy_detect_MASK                0x00200000
#define BCHP_PM_CONFIG_uart_enable_busy_detect_SHIFT               21

/* PM :: CONFIG :: reserved1 [20:16] */
#define BCHP_PM_CONFIG_reserved1_MASK                              0x001f0000
#define BCHP_PM_CONFIG_reserved1_SHIFT                             16

/* PM :: CONFIG :: uart_clk_sel [15:15] */
#define BCHP_PM_CONFIG_uart_clk_sel_MASK                           0x00008000
#define BCHP_PM_CONFIG_uart_clk_sel_SHIFT                          15

/* PM :: CONFIG :: uart_sw_reset [14:14] */
#define BCHP_PM_CONFIG_uart_sw_reset_MASK                          0x00004000
#define BCHP_PM_CONFIG_uart_sw_reset_SHIFT                         14

/* PM :: CONFIG :: reserved2 [13:10] */
#define BCHP_PM_CONFIG_reserved2_MASK                              0x00003c00
#define BCHP_PM_CONFIG_reserved2_SHIFT                             10

/* PM :: CONFIG :: mcif_sw_reset [09:09] */
#define BCHP_PM_CONFIG_mcif_sw_reset_MASK                          0x00000200
#define BCHP_PM_CONFIG_mcif_sw_reset_SHIFT                         9

/* PM :: CONFIG :: sc_late_sw_reset [08:08] */
#define BCHP_PM_CONFIG_sc_late_sw_reset_MASK                       0x00000100
#define BCHP_PM_CONFIG_sc_late_sw_reset_SHIFT                      8

/* PM :: CONFIG :: sc_sw_reset [07:07] */
#define BCHP_PM_CONFIG_sc_sw_reset_MASK                            0x00000080
#define BCHP_PM_CONFIG_sc_sw_reset_SHIFT                           7

/* PM :: CONFIG :: reserved3 [06:00] */
#define BCHP_PM_CONFIG_reserved3_MASK                              0x0000007f
#define BCHP_PM_CONFIG_reserved3_SHIFT                             0

/***************************************************************************
 *CLK_CTRL - UPG Clock control register
 ***************************************************************************/
/* PM :: CLK_CTRL :: reserved_for_eco0 [31:17] */
#define BCHP_PM_CLK_CTRL_reserved_for_eco0_MASK                    0xfffe0000
#define BCHP_PM_CLK_CTRL_reserved_for_eco0_SHIFT                   17

/* PM :: CLK_CTRL :: timer_clk_ctrl [16:16] */
#define BCHP_PM_CLK_CTRL_timer_clk_ctrl_MASK                       0x00010000
#define BCHP_PM_CLK_CTRL_timer_clk_ctrl_SHIFT                      16

/* PM :: CLK_CTRL :: gpio_clk_ctrl [15:15] */
#define BCHP_PM_CLK_CTRL_gpio_clk_ctrl_MASK                        0x00008000
#define BCHP_PM_CLK_CTRL_gpio_clk_ctrl_SHIFT                       15

/* PM :: CLK_CTRL :: reserved1 [14:12] */
#define BCHP_PM_CLK_CTRL_reserved1_MASK                            0x00007000
#define BCHP_PM_CLK_CTRL_reserved1_SHIFT                           12

/* PM :: CLK_CTRL :: kbd1_clk_ctrl [11:11] */
#define BCHP_PM_CLK_CTRL_kbd1_clk_ctrl_MASK                        0x00000800
#define BCHP_PM_CLK_CTRL_kbd1_clk_ctrl_SHIFT                       11

/* PM :: CLK_CTRL :: icap_clk_ctrl [10:10] */
#define BCHP_PM_CLK_CTRL_icap_clk_ctrl_MASK                        0x00000400
#define BCHP_PM_CLK_CTRL_icap_clk_ctrl_SHIFT                       10

/* PM :: CLK_CTRL :: reserved2 [09:09] */
#define BCHP_PM_CLK_CTRL_reserved2_MASK                            0x00000200
#define BCHP_PM_CLK_CTRL_reserved2_SHIFT                           9

/* PM :: CLK_CTRL :: pwma_clk_ctrl [08:08] */
#define BCHP_PM_CLK_CTRL_pwma_clk_ctrl_MASK                        0x00000100
#define BCHP_PM_CLK_CTRL_pwma_clk_ctrl_SHIFT                       8

/* PM :: CLK_CTRL :: reserved3 [07:04] */
#define BCHP_PM_CLK_CTRL_reserved3_MASK                            0x000000f0
#define BCHP_PM_CLK_CTRL_reserved3_SHIFT                           4

/* PM :: CLK_CTRL :: bscb_clk_ctrl [03:03] */
#define BCHP_PM_CLK_CTRL_bscb_clk_ctrl_MASK                        0x00000008
#define BCHP_PM_CLK_CTRL_bscb_clk_ctrl_SHIFT                       3

/* PM :: CLK_CTRL :: bsca_clk_ctrl [02:02] */
#define BCHP_PM_CLK_CTRL_bsca_clk_ctrl_MASK                        0x00000004
#define BCHP_PM_CLK_CTRL_bsca_clk_ctrl_SHIFT                       2

/* PM :: CLK_CTRL :: ldk_clk_ctrl [01:01] */
#define BCHP_PM_CLK_CTRL_ldk_clk_ctrl_MASK                         0x00000002
#define BCHP_PM_CLK_CTRL_ldk_clk_ctrl_SHIFT                        1

/* PM :: CLK_CTRL :: reserved4 [00:00] */
#define BCHP_PM_CLK_CTRL_reserved4_MASK                            0x00000001
#define BCHP_PM_CLK_CTRL_reserved4_SHIFT                           0

#endif /* #ifndef BCHP_PM_H__ */

/* End of File */

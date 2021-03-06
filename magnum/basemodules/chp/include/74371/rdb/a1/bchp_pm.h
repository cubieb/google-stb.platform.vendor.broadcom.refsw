/****************************************************************************
 *     Copyright (c) 1999-2014, Broadcom Corporation
 *     All Rights Reserved
 *     Confidential Property of Broadcom Corporation
 *
 *
 * THIS SOFTWARE MAY ONLY BE USED SUBJECT TO AN EXECUTED SOFTWARE LICENSE
 * AGREEMENT  BETWEEN THE USER AND BROADCOM.  YOU HAVE NO RIGHT TO USE OR
 * EXPLOIT THIS MATERIAL EXCEPT SUBJECT TO THE TERMS OF SUCH AN AGREEMENT.
 *
 * Module Description:
 *                     DO NOT EDIT THIS FILE DIRECTLY
 *
 * This module was generated magically with RDB from a source description
 * file. You must edit the source file for changes to be made to this file.
 *
 *
 * Date:           Generated on               Fri Feb 20 00:05:24 2015
 *                 Full Compile MD5 Checksum  f4a546a20d0bd1f244e0d6a139e85ce0
 *                     (minus title and desc)
 *                 MD5 Checksum               a9d9eeea3a1c30a122d08de69d07786c
 *
 * Compiled with:  RDB Utility                combo_header.pl
 *                 RDB.pm                     15715
 *                 unknown                    unknown
 *                 Perl Interpreter           5.008008
 *                 Operating System           linux
 *
 *
 ***************************************************************************/

#ifndef BCHP_PM_H__
#define BCHP_PM_H__

/***************************************************************************
 *PM - Peripheral Module Configuration
 ***************************************************************************/
#define BCHP_PM_CONFIG                           0x00406180 /* [RW] PERIPHERAL MODULE CONFIGURATION REGISTER */
#define BCHP_PM_CLK_CTRL                         0x00406184 /* [RW] UPG Clock control register */
#define BCHP_PM_RST_CTRL                         0x00406188 /* [RW] UPG reset control register */

/***************************************************************************
 *CONFIG - PERIPHERAL MODULE CONFIGURATION REGISTER
 ***************************************************************************/
/* PM :: CONFIG :: reserved0 [31:14] */
#define BCHP_PM_CONFIG_reserved0_MASK                              0xffffc000
#define BCHP_PM_CONFIG_reserved0_SHIFT                             14

/* PM :: CONFIG :: irb_out_sel [13:12] */
#define BCHP_PM_CONFIG_irb_out_sel_MASK                            0x00003000
#define BCHP_PM_CONFIG_irb_out_sel_SHIFT                           12
#define BCHP_PM_CONFIG_irb_out_sel_DEFAULT                         0x00000000

/* PM :: CONFIG :: uart_dma_sw_init [11:11] */
#define BCHP_PM_CONFIG_uart_dma_sw_init_MASK                       0x00000800
#define BCHP_PM_CONFIG_uart_dma_sw_init_SHIFT                      11
#define BCHP_PM_CONFIG_uart_dma_sw_init_DEFAULT                    0x00000000

/* PM :: CONFIG :: uart_dma_sw_reset [10:10] */
#define BCHP_PM_CONFIG_uart_dma_sw_reset_MASK                      0x00000400
#define BCHP_PM_CONFIG_uart_dma_sw_reset_SHIFT                     10
#define BCHP_PM_CONFIG_uart_dma_sw_reset_DEFAULT                   0x00000000

/* PM :: CONFIG :: uart_enable_busy_detect [09:09] */
#define BCHP_PM_CONFIG_uart_enable_busy_detect_MASK                0x00000200
#define BCHP_PM_CONFIG_uart_enable_busy_detect_SHIFT               9
#define BCHP_PM_CONFIG_uart_enable_busy_detect_DEFAULT             0x00000000

/* PM :: CONFIG :: uart_disable_busy_wr [08:08] */
#define BCHP_PM_CONFIG_uart_disable_busy_wr_MASK                   0x00000100
#define BCHP_PM_CONFIG_uart_disable_busy_wr_SHIFT                  8
#define BCHP_PM_CONFIG_uart_disable_busy_wr_DEFAULT                0x00000000

/* PM :: CONFIG :: uart_sw_reset [07:07] */
#define BCHP_PM_CONFIG_uart_sw_reset_MASK                          0x00000080
#define BCHP_PM_CONFIG_uart_sw_reset_SHIFT                         7
#define BCHP_PM_CONFIG_uart_sw_reset_DEFAULT                       0x00000000

/* PM :: CONFIG :: uart_clk_sel [06:06] */
#define BCHP_PM_CONFIG_uart_clk_sel_MASK                           0x00000040
#define BCHP_PM_CONFIG_uart_clk_sel_SHIFT                          6
#define BCHP_PM_CONFIG_uart_clk_sel_DEFAULT                        0x00000000

/* PM :: CONFIG :: mcif1_sw_init [05:05] */
#define BCHP_PM_CONFIG_mcif1_sw_init_MASK                          0x00000020
#define BCHP_PM_CONFIG_mcif1_sw_init_SHIFT                         5
#define BCHP_PM_CONFIG_mcif1_sw_init_DEFAULT                       0x00000000

/* PM :: CONFIG :: mcif1_sw_reset [04:04] */
#define BCHP_PM_CONFIG_mcif1_sw_reset_MASK                         0x00000010
#define BCHP_PM_CONFIG_mcif1_sw_reset_SHIFT                        4
#define BCHP_PM_CONFIG_mcif1_sw_reset_DEFAULT                      0x00000000

/* PM :: CONFIG :: mcif_sw_init [03:03] */
#define BCHP_PM_CONFIG_mcif_sw_init_MASK                           0x00000008
#define BCHP_PM_CONFIG_mcif_sw_init_SHIFT                          3
#define BCHP_PM_CONFIG_mcif_sw_init_DEFAULT                        0x00000000

/* PM :: CONFIG :: mcif_sw_reset [02:02] */
#define BCHP_PM_CONFIG_mcif_sw_reset_MASK                          0x00000004
#define BCHP_PM_CONFIG_mcif_sw_reset_SHIFT                         2
#define BCHP_PM_CONFIG_mcif_sw_reset_DEFAULT                       0x00000000

/* PM :: CONFIG :: sc_late_sw_reset [01:01] */
#define BCHP_PM_CONFIG_sc_late_sw_reset_MASK                       0x00000002
#define BCHP_PM_CONFIG_sc_late_sw_reset_SHIFT                      1
#define BCHP_PM_CONFIG_sc_late_sw_reset_DEFAULT                    0x00000000

/* PM :: CONFIG :: sc_sw_reset [00:00] */
#define BCHP_PM_CONFIG_sc_sw_reset_MASK                            0x00000001
#define BCHP_PM_CONFIG_sc_sw_reset_SHIFT                           0
#define BCHP_PM_CONFIG_sc_sw_reset_DEFAULT                         0x00000000

/***************************************************************************
 *CLK_CTRL - UPG Clock control register
 ***************************************************************************/
/* PM :: CLK_CTRL :: reserved0 [31:11] */
#define BCHP_PM_CLK_CTRL_reserved0_MASK                            0xfffff800
#define BCHP_PM_CLK_CTRL_reserved0_SHIFT                           11

/* PM :: CLK_CTRL :: mcif1 [10:10] */
#define BCHP_PM_CLK_CTRL_mcif1_MASK                                0x00000400
#define BCHP_PM_CLK_CTRL_mcif1_SHIFT                               10
#define BCHP_PM_CLK_CTRL_mcif1_DEFAULT                             0x00000000

/* PM :: CLK_CTRL :: mcif [09:09] */
#define BCHP_PM_CLK_CTRL_mcif_MASK                                 0x00000200
#define BCHP_PM_CLK_CTRL_mcif_SHIFT                                9
#define BCHP_PM_CLK_CTRL_mcif_DEFAULT                              0x00000001

/* PM :: CLK_CTRL :: irb [08:08] */
#define BCHP_PM_CLK_CTRL_irb_MASK                                  0x00000100
#define BCHP_PM_CLK_CTRL_irb_SHIFT                                 8
#define BCHP_PM_CLK_CTRL_irb_DEFAULT                               0x00000001

/* PM :: CLK_CTRL :: gpio [07:07] */
#define BCHP_PM_CLK_CTRL_gpio_MASK                                 0x00000080
#define BCHP_PM_CLK_CTRL_gpio_SHIFT                                7
#define BCHP_PM_CLK_CTRL_gpio_DEFAULT                              0x00000001

/* PM :: CLK_CTRL :: timers [06:06] */
#define BCHP_PM_CLK_CTRL_timers_MASK                               0x00000040
#define BCHP_PM_CLK_CTRL_timers_SHIFT                              6
#define BCHP_PM_CLK_CTRL_timers_DEFAULT                            0x00000001

/* PM :: CLK_CTRL :: pwmb [05:05] */
#define BCHP_PM_CLK_CTRL_pwmb_MASK                                 0x00000020
#define BCHP_PM_CLK_CTRL_pwmb_SHIFT                                5
#define BCHP_PM_CLK_CTRL_pwmb_DEFAULT                              0x00000001

/* PM :: CLK_CTRL :: pwma [04:04] */
#define BCHP_PM_CLK_CTRL_pwma_MASK                                 0x00000010
#define BCHP_PM_CLK_CTRL_pwma_SHIFT                                4
#define BCHP_PM_CLK_CTRL_pwma_DEFAULT                              0x00000001

/* PM :: CLK_CTRL :: bscf [03:03] */
#define BCHP_PM_CLK_CTRL_bscf_MASK                                 0x00000008
#define BCHP_PM_CLK_CTRL_bscf_SHIFT                                3
#define BCHP_PM_CLK_CTRL_bscf_DEFAULT                              0x00000001

/* PM :: CLK_CTRL :: bsce [02:02] */
#define BCHP_PM_CLK_CTRL_bsce_MASK                                 0x00000004
#define BCHP_PM_CLK_CTRL_bsce_SHIFT                                2
#define BCHP_PM_CLK_CTRL_bsce_DEFAULT                              0x00000001

/* PM :: CLK_CTRL :: bscb [01:01] */
#define BCHP_PM_CLK_CTRL_bscb_MASK                                 0x00000002
#define BCHP_PM_CLK_CTRL_bscb_SHIFT                                1
#define BCHP_PM_CLK_CTRL_bscb_DEFAULT                              0x00000001

/* PM :: CLK_CTRL :: bsca [00:00] */
#define BCHP_PM_CLK_CTRL_bsca_MASK                                 0x00000001
#define BCHP_PM_CLK_CTRL_bsca_SHIFT                                0
#define BCHP_PM_CLK_CTRL_bsca_DEFAULT                              0x00000001

/***************************************************************************
 *RST_CTRL - UPG reset control register
 ***************************************************************************/
/* PM :: RST_CTRL :: reserved0 [31:09] */
#define BCHP_PM_RST_CTRL_reserved0_MASK                            0xfffffe00
#define BCHP_PM_RST_CTRL_reserved0_SHIFT                           9

/* PM :: RST_CTRL :: irb [08:08] */
#define BCHP_PM_RST_CTRL_irb_MASK                                  0x00000100
#define BCHP_PM_RST_CTRL_irb_SHIFT                                 8
#define BCHP_PM_RST_CTRL_irb_DEFAULT                               0x00000000

/* PM :: RST_CTRL :: gpio [07:07] */
#define BCHP_PM_RST_CTRL_gpio_MASK                                 0x00000080
#define BCHP_PM_RST_CTRL_gpio_SHIFT                                7
#define BCHP_PM_RST_CTRL_gpio_DEFAULT                              0x00000000

/* PM :: RST_CTRL :: timers [06:06] */
#define BCHP_PM_RST_CTRL_timers_MASK                               0x00000040
#define BCHP_PM_RST_CTRL_timers_SHIFT                              6
#define BCHP_PM_RST_CTRL_timers_DEFAULT                            0x00000000

/* PM :: RST_CTRL :: pwmb [05:05] */
#define BCHP_PM_RST_CTRL_pwmb_MASK                                 0x00000020
#define BCHP_PM_RST_CTRL_pwmb_SHIFT                                5
#define BCHP_PM_RST_CTRL_pwmb_DEFAULT                              0x00000000

/* PM :: RST_CTRL :: pwma [04:04] */
#define BCHP_PM_RST_CTRL_pwma_MASK                                 0x00000010
#define BCHP_PM_RST_CTRL_pwma_SHIFT                                4
#define BCHP_PM_RST_CTRL_pwma_DEFAULT                              0x00000000

/* PM :: RST_CTRL :: bscf [03:03] */
#define BCHP_PM_RST_CTRL_bscf_MASK                                 0x00000008
#define BCHP_PM_RST_CTRL_bscf_SHIFT                                3
#define BCHP_PM_RST_CTRL_bscf_DEFAULT                              0x00000000

/* PM :: RST_CTRL :: bsce [02:02] */
#define BCHP_PM_RST_CTRL_bsce_MASK                                 0x00000004
#define BCHP_PM_RST_CTRL_bsce_SHIFT                                2
#define BCHP_PM_RST_CTRL_bsce_DEFAULT                              0x00000000

/* PM :: RST_CTRL :: bscb [01:01] */
#define BCHP_PM_RST_CTRL_bscb_MASK                                 0x00000002
#define BCHP_PM_RST_CTRL_bscb_SHIFT                                1
#define BCHP_PM_RST_CTRL_bscb_DEFAULT                              0x00000000

/* PM :: RST_CTRL :: bsca [00:00] */
#define BCHP_PM_RST_CTRL_bsca_MASK                                 0x00000001
#define BCHP_PM_RST_CTRL_bsca_SHIFT                                0
#define BCHP_PM_RST_CTRL_bsca_DEFAULT                              0x00000000

#endif /* #ifndef BCHP_PM_H__ */

/* End of File */

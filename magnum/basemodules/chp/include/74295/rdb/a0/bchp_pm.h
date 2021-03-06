/****************************************************************************
 *     Copyright (c) 1999-2015, Broadcom Corporation
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
 * Date:           Generated on               Thu May 14 18:20:31 2015
 *                 Full Compile MD5 Checksum  2c0afe5af8c5001bc7ee85f3b37a072f
 *                     (minus title and desc)
 *                 MD5 Checksum               ff107b9f712c3c7698da495b543748f9
 *
 * Compiled with:  RDB Utility                combo_header.pl
 *                 RDB.pm                     16137
 *                 unknown                    unknown
 *                 Perl Interpreter           5.008008
 *                 Operating System           linux
 *                 Script Source              /tools/dvtsw/current/Linux/combo_header.pl
 *                 DVTSWVER                   current
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
/* PM :: CONFIG :: reserved_for_eco0 [31:24] */
#define BCHP_PM_CONFIG_reserved_for_eco0_MASK                      0xff000000
#define BCHP_PM_CONFIG_reserved_for_eco0_SHIFT                     24
#define BCHP_PM_CONFIG_reserved_for_eco0_DEFAULT                   0x00000000

/* PM :: CONFIG :: uart_dma_sw_reset [23:23] */
#define BCHP_PM_CONFIG_uart_dma_sw_reset_MASK                      0x00800000
#define BCHP_PM_CONFIG_uart_dma_sw_reset_SHIFT                     23
#define BCHP_PM_CONFIG_uart_dma_sw_reset_DEFAULT                   0x00000000

/* PM :: CONFIG :: uart_enable_busy_detect [22:22] */
#define BCHP_PM_CONFIG_uart_enable_busy_detect_MASK                0x00400000
#define BCHP_PM_CONFIG_uart_enable_busy_detect_SHIFT               22
#define BCHP_PM_CONFIG_uart_enable_busy_detect_DEFAULT             0x00000000

/* PM :: CONFIG :: uart_disable_busy_wr [21:21] */
#define BCHP_PM_CONFIG_uart_disable_busy_wr_MASK                   0x00200000
#define BCHP_PM_CONFIG_uart_disable_busy_wr_SHIFT                  21
#define BCHP_PM_CONFIG_uart_disable_busy_wr_DEFAULT                0x00000000

/* PM :: CONFIG :: irb_out_sel [20:19] */
#define BCHP_PM_CONFIG_irb_out_sel_MASK                            0x00180000
#define BCHP_PM_CONFIG_irb_out_sel_SHIFT                           19
#define BCHP_PM_CONFIG_irb_out_sel_DEFAULT                         0x00000000

/* PM :: CONFIG :: reserved1 [18:16] */
#define BCHP_PM_CONFIG_reserved1_MASK                              0x00070000
#define BCHP_PM_CONFIG_reserved1_SHIFT                             16

/* PM :: CONFIG :: uart_clk_sel [15:15] */
#define BCHP_PM_CONFIG_uart_clk_sel_MASK                           0x00008000
#define BCHP_PM_CONFIG_uart_clk_sel_SHIFT                          15
#define BCHP_PM_CONFIG_uart_clk_sel_DEFAULT                        0x00000000

/* PM :: CONFIG :: uart_sw_reset [14:14] */
#define BCHP_PM_CONFIG_uart_sw_reset_MASK                          0x00004000
#define BCHP_PM_CONFIG_uart_sw_reset_SHIFT                         14
#define BCHP_PM_CONFIG_uart_sw_reset_DEFAULT                       0x00000000

/* PM :: CONFIG :: reserved_for_eco2 [13:12] */
#define BCHP_PM_CONFIG_reserved_for_eco2_MASK                      0x00003000
#define BCHP_PM_CONFIG_reserved_for_eco2_SHIFT                     12
#define BCHP_PM_CONFIG_reserved_for_eco2_DEFAULT                   0x00000000

/* PM :: CONFIG :: uart_dma_sw_init [11:11] */
#define BCHP_PM_CONFIG_uart_dma_sw_init_MASK                       0x00000800
#define BCHP_PM_CONFIG_uart_dma_sw_init_SHIFT                      11
#define BCHP_PM_CONFIG_uart_dma_sw_init_DEFAULT                    0x00000000

/* PM :: CONFIG :: mcif_sw_init [10:10] */
#define BCHP_PM_CONFIG_mcif_sw_init_MASK                           0x00000400
#define BCHP_PM_CONFIG_mcif_sw_init_SHIFT                          10
#define BCHP_PM_CONFIG_mcif_sw_init_DEFAULT                        0x00000000

/* PM :: CONFIG :: mcif_sw_reset [09:09] */
#define BCHP_PM_CONFIG_mcif_sw_reset_MASK                          0x00000200
#define BCHP_PM_CONFIG_mcif_sw_reset_SHIFT                         9
#define BCHP_PM_CONFIG_mcif_sw_reset_DEFAULT                       0x00000000

/* PM :: CONFIG :: sc_late_sw_reset [08:08] */
#define BCHP_PM_CONFIG_sc_late_sw_reset_MASK                       0x00000100
#define BCHP_PM_CONFIG_sc_late_sw_reset_SHIFT                      8
#define BCHP_PM_CONFIG_sc_late_sw_reset_DEFAULT                    0x00000000

/* PM :: CONFIG :: sc_sw_reset [07:07] */
#define BCHP_PM_CONFIG_sc_sw_reset_MASK                            0x00000080
#define BCHP_PM_CONFIG_sc_sw_reset_SHIFT                           7
#define BCHP_PM_CONFIG_sc_sw_reset_DEFAULT                         0x00000000

/* PM :: CONFIG :: reserved_for_eco3 [06:00] */
#define BCHP_PM_CONFIG_reserved_for_eco3_MASK                      0x0000007f
#define BCHP_PM_CONFIG_reserved_for_eco3_SHIFT                     0
#define BCHP_PM_CONFIG_reserved_for_eco3_DEFAULT                   0x00000000

/***************************************************************************
 *CLK_CTRL - UPG Clock control register
 ***************************************************************************/
/* PM :: CLK_CTRL :: reserved0 [31:17] */
#define BCHP_PM_CLK_CTRL_reserved0_MASK                            0xfffe0000
#define BCHP_PM_CLK_CTRL_reserved0_SHIFT                           17

/* PM :: CLK_CTRL :: timer [16:16] */
#define BCHP_PM_CLK_CTRL_timer_MASK                                0x00010000
#define BCHP_PM_CLK_CTRL_timer_SHIFT                               16
#define BCHP_PM_CLK_CTRL_timer_DEFAULT                             0x00000001

/* PM :: CLK_CTRL :: gpio [15:15] */
#define BCHP_PM_CLK_CTRL_gpio_MASK                                 0x00008000
#define BCHP_PM_CLK_CTRL_gpio_SHIFT                                15
#define BCHP_PM_CLK_CTRL_gpio_DEFAULT                              0x00000001

/* PM :: CLK_CTRL :: reserved_for_eco1 [14:09] */
#define BCHP_PM_CLK_CTRL_reserved_for_eco1_MASK                    0x00007e00
#define BCHP_PM_CLK_CTRL_reserved_for_eco1_SHIFT                   9
#define BCHP_PM_CLK_CTRL_reserved_for_eco1_DEFAULT                 0x00000000

/* PM :: CLK_CTRL :: pwm [08:08] */
#define BCHP_PM_CLK_CTRL_pwm_MASK                                  0x00000100
#define BCHP_PM_CLK_CTRL_pwm_SHIFT                                 8
#define BCHP_PM_CLK_CTRL_pwm_DEFAULT                               0x00000001

/* PM :: CLK_CTRL :: reserved_for_eco2 [07:07] */
#define BCHP_PM_CLK_CTRL_reserved_for_eco2_MASK                    0x00000080
#define BCHP_PM_CLK_CTRL_reserved_for_eco2_SHIFT                   7
#define BCHP_PM_CLK_CTRL_reserved_for_eco2_DEFAULT                 0x00000000

/* PM :: CLK_CTRL :: bsce [06:06] */
#define BCHP_PM_CLK_CTRL_bsce_MASK                                 0x00000040
#define BCHP_PM_CLK_CTRL_bsce_SHIFT                                6
#define BCHP_PM_CLK_CTRL_bsce_DEFAULT                              0x00000001

/* PM :: CLK_CTRL :: bscd [05:05] */
#define BCHP_PM_CLK_CTRL_bscd_MASK                                 0x00000020
#define BCHP_PM_CLK_CTRL_bscd_SHIFT                                5
#define BCHP_PM_CLK_CTRL_bscd_DEFAULT                              0x00000001

/* PM :: CLK_CTRL :: reserved_for_eco3 [04:01] */
#define BCHP_PM_CLK_CTRL_reserved_for_eco3_MASK                    0x0000001e
#define BCHP_PM_CLK_CTRL_reserved_for_eco3_SHIFT                   1
#define BCHP_PM_CLK_CTRL_reserved_for_eco3_DEFAULT                 0x00000000

/* PM :: CLK_CTRL :: irb [00:00] */
#define BCHP_PM_CLK_CTRL_irb_MASK                                  0x00000001
#define BCHP_PM_CLK_CTRL_irb_SHIFT                                 0
#define BCHP_PM_CLK_CTRL_irb_DEFAULT                               0x00000001

/***************************************************************************
 *RST_CTRL - UPG reset control register
 ***************************************************************************/
/* PM :: RST_CTRL :: reserved0 [31:17] */
#define BCHP_PM_RST_CTRL_reserved0_MASK                            0xfffe0000
#define BCHP_PM_RST_CTRL_reserved0_SHIFT                           17

/* PM :: RST_CTRL :: timer [16:16] */
#define BCHP_PM_RST_CTRL_timer_MASK                                0x00010000
#define BCHP_PM_RST_CTRL_timer_SHIFT                               16
#define BCHP_PM_RST_CTRL_timer_DEFAULT                             0x00000000

/* PM :: RST_CTRL :: gpio [15:15] */
#define BCHP_PM_RST_CTRL_gpio_MASK                                 0x00008000
#define BCHP_PM_RST_CTRL_gpio_SHIFT                                15
#define BCHP_PM_RST_CTRL_gpio_DEFAULT                              0x00000000

/* PM :: RST_CTRL :: reserved_for_eco1 [14:09] */
#define BCHP_PM_RST_CTRL_reserved_for_eco1_MASK                    0x00007e00
#define BCHP_PM_RST_CTRL_reserved_for_eco1_SHIFT                   9
#define BCHP_PM_RST_CTRL_reserved_for_eco1_DEFAULT                 0x00000000

/* PM :: RST_CTRL :: pwm [08:08] */
#define BCHP_PM_RST_CTRL_pwm_MASK                                  0x00000100
#define BCHP_PM_RST_CTRL_pwm_SHIFT                                 8
#define BCHP_PM_RST_CTRL_pwm_DEFAULT                               0x00000000

/* PM :: RST_CTRL :: reserved_for_eco2 [07:07] */
#define BCHP_PM_RST_CTRL_reserved_for_eco2_MASK                    0x00000080
#define BCHP_PM_RST_CTRL_reserved_for_eco2_SHIFT                   7
#define BCHP_PM_RST_CTRL_reserved_for_eco2_DEFAULT                 0x00000000

/* PM :: RST_CTRL :: bsce [06:06] */
#define BCHP_PM_RST_CTRL_bsce_MASK                                 0x00000040
#define BCHP_PM_RST_CTRL_bsce_SHIFT                                6
#define BCHP_PM_RST_CTRL_bsce_DEFAULT                              0x00000000

/* PM :: RST_CTRL :: bscd [05:05] */
#define BCHP_PM_RST_CTRL_bscd_MASK                                 0x00000020
#define BCHP_PM_RST_CTRL_bscd_SHIFT                                5
#define BCHP_PM_RST_CTRL_bscd_DEFAULT                              0x00000000

/* PM :: RST_CTRL :: reserved_for_eco3 [04:01] */
#define BCHP_PM_RST_CTRL_reserved_for_eco3_MASK                    0x0000001e
#define BCHP_PM_RST_CTRL_reserved_for_eco3_SHIFT                   1
#define BCHP_PM_RST_CTRL_reserved_for_eco3_DEFAULT                 0x00000000

/* PM :: RST_CTRL :: irb [00:00] */
#define BCHP_PM_RST_CTRL_irb_MASK                                  0x00000001
#define BCHP_PM_RST_CTRL_irb_SHIFT                                 0
#define BCHP_PM_RST_CTRL_irb_DEFAULT                               0x00000000

#endif /* #ifndef BCHP_PM_H__ */

/* End of File */

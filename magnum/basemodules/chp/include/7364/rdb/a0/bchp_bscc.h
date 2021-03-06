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
 * Date:           Generated on               Fri Aug 15 15:20:55 2014
 *                 Full Compile MD5 Checksum  a68bc62e9dd3be19fcad480c369d60fd
 *                     (minus title and desc)
 *                 MD5 Checksum               14382795d76d8497c2dd1bcf3f5d36da
 *
 * Compiled with:  RDB Utility                combo_header.pl
 *                 RDB.pm                     14541
 *                 unknown                    unknown
 *                 Perl Interpreter           5.008008
 *                 Operating System           linux
 *
 *
 ***************************************************************************/

#ifndef BCHP_BSCC_H__
#define BCHP_BSCC_H__

/***************************************************************************
 *BSCC - Broadcom Serial Control Master C
 ***************************************************************************/
#define BCHP_BSCC_CHIP_ADDRESS                   0x00417200 /* [RW] BSC Chip Address And Read/Write Control */
#define BCHP_BSCC_DATA_IN0                       0x00417204 /* [RW] BSC Write Data Register 0 */
#define BCHP_BSCC_DATA_IN1                       0x00417208 /* [RW] BSC Write Data Register 1 */
#define BCHP_BSCC_DATA_IN2                       0x0041720c /* [RW] BSC Write Data Register 2 */
#define BCHP_BSCC_DATA_IN3                       0x00417210 /* [RW] BSC Write Data Register 3 */
#define BCHP_BSCC_DATA_IN4                       0x00417214 /* [RW] BSC Write Data Register 4 */
#define BCHP_BSCC_DATA_IN5                       0x00417218 /* [RW] BSC Write Data Register 5 */
#define BCHP_BSCC_DATA_IN6                       0x0041721c /* [RW] BSC Write Data Register 6 */
#define BCHP_BSCC_DATA_IN7                       0x00417220 /* [RW] BSC Write Data Register 7 */
#define BCHP_BSCC_CNT_REG                        0x00417224 /* [RW] BSC Transfer Count Register */
#define BCHP_BSCC_CTL_REG                        0x00417228 /* [RW] BSC Control Register */
#define BCHP_BSCC_IIC_ENABLE                     0x0041722c /* [RW] BSC Read/Write Enable And Interrupt */
#define BCHP_BSCC_DATA_OUT0                      0x00417230 /* [RO] BSC Read Data Register 0 */
#define BCHP_BSCC_DATA_OUT1                      0x00417234 /* [RO] BSC Read Data Register 1 */
#define BCHP_BSCC_DATA_OUT2                      0x00417238 /* [RO] BSC Read Data Register 2 */
#define BCHP_BSCC_DATA_OUT3                      0x0041723c /* [RO] BSC Read Data Register 3 */
#define BCHP_BSCC_DATA_OUT4                      0x00417240 /* [RO] BSC Read Data Register 4 */
#define BCHP_BSCC_DATA_OUT5                      0x00417244 /* [RO] BSC Read Data Register 5 */
#define BCHP_BSCC_DATA_OUT6                      0x00417248 /* [RO] BSC Read Data Register 6 */
#define BCHP_BSCC_DATA_OUT7                      0x0041724c /* [RO] BSC Read Data Register 7 */
#define BCHP_BSCC_CTLHI_REG                      0x00417250 /* [RW] BSC Control Register */
#define BCHP_BSCC_SCL_PARAM                      0x00417254 /* [RW] BSC SCL Parameter Register */

#endif /* #ifndef BCHP_BSCC_H__ */

/* End of File */

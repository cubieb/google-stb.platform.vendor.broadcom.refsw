/***************************************************************************
 *     Copyright (c) 1999-2013, Broadcom Corporation
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
 * Date:           Generated on              Mon Dec 23 13:19:21 2013
 *                 Full Compile MD5 Checksum e5d1378cc1475b750905e70cb70c73d9
 *                   (minus title and desc)  
 *                 MD5 Checksum              aa943f3142a624837db5321711723fcf
 *
 * Compiled with:  RDB Utility               combo_header.pl
 *                 RDB Parser                3.0
 *                 unknown                   unknown
 *                 Perl Interpreter          5.008008
 *                 Operating System          linux
 *
 * Revision History:
 *
 * $brcm_Log: $
 * 
 ***************************************************************************/

#ifndef BCHP_SDS_DSEC_1_H__
#define BCHP_SDS_DSEC_1_H__

/***************************************************************************
 *SDS_DSEC_1 - SDS DSEC Register Set
 ***************************************************************************/
#define BCHP_SDS_DSEC_1_DSRST                    0x01219000 /* DiSEqC Reset Control */
#define BCHP_SDS_DSEC_1_DSCGDIV                  0x01219004 /* DiSEqC Clock Divider Control */
#define BCHP_SDS_DSEC_1_DSCTL00                  0x01219010 /* DiSEqC Control 00 (Formerly, DSCTL4,DSCTL3,DSCTL2,DSCTL1) */
#define BCHP_SDS_DSEC_1_DSCTL01                  0x01219014 /* DiSEqC Control 01 (Formerly, DSCTL8,DSCTL7,DSCTL6,DSCTL5) */
#define BCHP_SDS_DSEC_1_DSCTL02                  0x01219018 /* DiSEqC Control 02 (Formerly, DSCTL11,DSCTL10,7'b0,DSCTL9[8:0]) */
#define BCHP_SDS_DSEC_1_DSCTL03                  0x0121901c /* DiSEqC Control 03 (Formerly, DSCTL14,DSCTL13,DSCTL12) */
#define BCHP_SDS_DSEC_1_DSCMD                    0x01219020 /* DiSEqC Command Data */
#define BCHP_SDS_DSEC_1_DSRPLY                   0x01219024 /* DiSEqC Receive Data */
#define BCHP_SDS_DSEC_1_DSCMEMADR                0x01219028 /* DiSEqC FIR Filter Coefficient Memory Start Address */
#define BCHP_SDS_DSEC_1_DSCMEMDAT                0x0121902c /* DiSEqC FIR Filter Coefficient Register */
#define BCHP_SDS_DSEC_1_DSFIRCTL                 0x01219030 /* DiSEqC FIR Filter Control Register */
#define BCHP_SDS_DSEC_1_DS_MISC_CONTROL          0x01219034 /* DiSEqC Misc. Control */
#define BCHP_SDS_DSEC_1_DS_PARITY                0x01219038 /* DiSEqC Misc. Control */
#define BCHP_SDS_DSEC_1_ADCTL                    0x01219040 /* RX A/D Control. */
#define BCHP_SDS_DSEC_1_Q15T                     0x01219044 /* Quiet 15ms and auto control word timing */
#define BCHP_SDS_DSEC_1_Q15T_TB                  0x01219048 /* Quiet 15ms for ToneBurst */
#define BCHP_SDS_DSEC_1_TB_LENGTH                0x0121904c /* ToneBurst Length */
#define BCHP_SDS_DSEC_1_TPWC                     0x01219050 /* Tone absent timing, TX PWK period and one/zero on counts */
#define BCHP_SDS_DSEC_1_RXBT                     0x01219054 /* RX bit max/min timing */
#define BCHP_SDS_DSEC_1_RXRT                     0x01219058 /* RX max cycle and reply timing */
#define BCHP_SDS_DSEC_1_RBDT                     0x0121905c /* RX low duty min and bit timing */
#define BCHP_SDS_DSEC_1_SLEW                     0x01219060 /* Slew rate control and TOA to TOD timing */
#define BCHP_SDS_DSEC_1_RERT                     0x01219064 /* RX end reply timing and voltage top/bottom levels */
#define BCHP_SDS_DSEC_1_DSCT                     0x01219068 /* misc diseqc controls */
#define BCHP_SDS_DSEC_1_DTCT                     0x0121906c /* voltage count and the TX frequency control word */
#define BCHP_SDS_DSEC_1_DDIO                     0x01219070 /* diseqc general purpose I/O control */
#define BCHP_SDS_DSEC_1_RTDC1                    0x01219074 /* RX clip thresholds and testport control */
#define BCHP_SDS_DSEC_1_RTDC2                    0x01219078 /* RX noise integration control */
#define BCHP_SDS_DSEC_1_TCTL                     0x0121907c /* TOA/TOD control */
#define BCHP_SDS_DSEC_1_CICC                     0x01219080 /* CIC length */
#define BCHP_SDS_DSEC_1_FCIC                     0x01219084 /* CIC1 threshold and majority vote control */
#define BCHP_SDS_DSEC_1_SCIC                     0x01219088 /* CIC2 threshold and majority vote control */
#define BCHP_SDS_DSEC_1_TSTM                     0x0121908c /* TOA/TOD or testport status */
#define BCHP_SDS_DSEC_1_DST1                     0x01219090 /* diseqc status 1 */
#define BCHP_SDS_DSEC_1_DST2                     0x01219094 /* diseqc status 2 */
#define BCHP_SDS_DSEC_1_DS_SAR_THRSH             0x012190a0 /* DiSEqC SAR Status Thresh Control */
#define BCHP_SDS_DSEC_1_DS_SAR_DATA_OUT          0x012190a4 /* DiSEqC SAR Data Output */
#define BCHP_SDS_DSEC_1_DS_SAR_DC_OFFSET         0x012190a8 /* DiSEqC SAR DC Offset Calibration */
#define BCHP_SDS_DSEC_1_DS_SAR_LPF_INT           0x012190ac /* DiSEqC SAR Low-pass Filter Integrator */
#define BCHP_SDS_DSEC_1_DS_SAR_CONTROL           0x012190b0 /* DiSEqC SAR Control */
#define BCHP_SDS_DSEC_1_DS_COMMON_CONTROL        0x012190b4 /* DiSEqC Common Control */
#define BCHP_SDS_DSEC_1_DSTMRCTL                 0x012190c0 /* DiSEqC Timer Control */
#define BCHP_SDS_DSEC_1_DSGENTMR1                0x012190c4 /* DiSEqC General Timer 1 */
#define BCHP_SDS_DSEC_1_DSGENTMR2                0x012190c8 /* DiSEqC General Timer 2 */
#define BCHP_SDS_DSEC_1_DS_IDLE_TIMEOUT_CTL      0x012190cc /* DiSEqC Idle Timeout Control */
#define BCHP_SDS_DSEC_1_DS_IDLE_TIMEOUT_STS      0x012190d0 /* DiSEqC Idle Timeout Status */
#define BCHP_SDS_DSEC_1_DS_LOCK                  0x012190d4 /* DiSEqC Register Lock */

#endif /* #ifndef BCHP_SDS_DSEC_1_H__ */

/* End of File */

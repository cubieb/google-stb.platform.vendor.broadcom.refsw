/***************************************************************************
 *     Copyright (c) 1999-2012, Broadcom Corporation
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
 * Date:           Generated on         Tue Jan 17 13:26:48 2012
 *                 MD5 Checksum         d41d8cd98f00b204e9800998ecf8427e
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

#ifndef BCHP_VICE2_VIP1_0_H__
#define BCHP_VICE2_VIP1_0_H__

/***************************************************************************
 *VICE2_VIP1_0 - Video Input Processing 1 Registers 0
 ***************************************************************************/
#define BCHP_VICE2_VIP1_0_FW_CONTROL             0x00703800 /* VIP FW Control */
#define BCHP_VICE2_VIP1_0_CONFIG                 0x00703804 /* VIP Configure */
#define BCHP_VICE2_VIP1_0_INPUT_PICTURE_SIZE     0x00703808 /* Current Expected Input Picture Size */
#define BCHP_VICE2_VIP1_0_OUTPUT_PICTURE_SIZE    0x0070380c /* Current Picture Size */
#define BCHP_VICE2_VIP1_0_LUMA_ADDR              0x00703810 /* Current Picture Luma Frame/Top/Bottom Buffer Address */
#define BCHP_VICE2_VIP1_0_LUMA_NMBY              0x00703814 /* Current Picture Luma Frame/Top/Bottom Buffer NMBY and Line Stride */
#define BCHP_VICE2_VIP1_0_2H1V_ADDR              0x00703818 /* Current Picture 2:1 Decimated Luma Frame/Top/Bottom Buffer Address */
#define BCHP_VICE2_VIP1_0_2H1V_NMBY              0x0070381c /* Current Picture 2:1 Decimated Luma Frame/Top/Bottom Buffer NMBY and Line Stride */
#define BCHP_VICE2_VIP1_0_2H2V_ADDR              0x00703820 /* Current Picture 4:1 Decimated Luma Frame/Top/Bottom Buffer Address */
#define BCHP_VICE2_VIP1_0_2H2V_NMBY              0x00703824 /* Current Picture 4:1 Decimated Luma Frame/Top/Bottom Buffer NMBY and Line Stride */
#define BCHP_VICE2_VIP1_0_420_CHROMA_ADDR        0x00703828 /* Current Picture 420 Chroma Frame/Top/Bottom Buffer Address */
#define BCHP_VICE2_VIP1_0_420_CHROMA_NMBY        0x0070382c /* Current Picture 420 Chroma Frame/Top/Bottom Buffer NMBY and Line Stride */
#define BCHP_VICE2_VIP1_0_SHIFT_CHROMA_ADDR      0x00703830 /* Current Picture Shifted Chroma Frame/Top/Bottom Buffer Address */
#define BCHP_VICE2_VIP1_0_SHIFT_CHROMA_NMBY      0x00703834 /* Current Picture Shifted Chroma Frame/Top/Bottom Buffer NMBY and Line Stride */
#define BCHP_VICE2_VIP1_0_PCC_LUMA_ADDR          0x00703838 /* Previous Picture Frame/Top/Bottom Buffer Address for PCC */
#define BCHP_VICE2_VIP1_0_HIST_LUMA_ADDR         0x0070383c /* Previous Picture Frame/Top/Bottom Buffer Address for Histogram */
#define BCHP_VICE2_VIP1_0_PCC_LINE_RANGE         0x00703840 /* PCC Line Range */
#define BCHP_VICE2_VIP1_0_PCC_CORE_VALUE         0x00703844 /* PCC Core Value */
#define BCHP_VICE2_VIP1_0_HIST_LINE_RANGE        0x00703848 /* Histogram Line Range */
#define BCHP_VICE2_VIP1_0_HIST_THRESHOLD_0       0x0070384c /* Histogram Threshold 0~1 and SCAD Core Value */
#define BCHP_VICE2_VIP1_0_HIST_THRESHOLD_1       0x00703850 /* Histogram Threshold 2~4 */
#define BCHP_VICE2_VIP1_0_BVB_PADDING_DATA       0x00703854 /* BVB PADDING DATA */
#define BCHP_VICE2_VIP1_0_BVB_STATUS_CLEAR       0x00703858 /* BVB Status Clear */
#define BCHP_VICE2_VIP1_0_BVB_STATUS             0x0070385c /* BVB Status */
#define BCHP_VICE2_VIP1_0_SCRATCH                0x00703860 /* Scratch Register */
#define BCHP_VICE2_VIP1_0_HIST_STATUS_0          0x00703864 /* Histogram Status 0 */
#define BCHP_VICE2_VIP1_0_HIST_STATUS_1          0x00703868 /* Histogram Status 1 */
#define BCHP_VICE2_VIP1_0_HIST_STATUS_2          0x0070386c /* Histogram Status 2 */
#define BCHP_VICE2_VIP1_0_HIST_STATUS_3          0x00703870 /* Histogram Status 3 */
#define BCHP_VICE2_VIP1_0_HIST_STATUS_4          0x00703874 /* Histogram Status 4 */
#define BCHP_VICE2_VIP1_0_SCAD_STATUS            0x00703878 /* SCAD Status */
#define BCHP_VICE2_VIP1_0_SINGLE_PCC_STATUS      0x0070387c /* PCC Status 0 */
#define BCHP_VICE2_VIP1_0_DOUBLE_PCC_STATUS      0x00703880 /* PCC Status 1 */
#define BCHP_VICE2_VIP1_0_STATUS                 0x00703884 /* VIP Status */
#define BCHP_VICE2_VIP1_0_REG_STATUS             0x00703888 /* REG Status */
#define BCHP_VICE2_VIP1_0_DEBUG                  0x0070388c /* DEBUG */
#define BCHP_VICE2_VIP1_0_BVB_STATUS_ENABLE      0x00703890 /* BVB_STATUS_ENABLE */
#define BCHP_VICE2_VIP1_0_ERR_STATUS_ENABLE      0x00703894 /* ERR_STATUS_ENABLE */
#define BCHP_VICE2_VIP1_0_ERR_STATUS_CLR         0x00703898 /* ERR_STATUS_CLR */
#define BCHP_VICE2_VIP1_0_BVN_CRC_CTRL           0x0070389c /* BVN CRC Control Register */
#define BCHP_VICE2_VIP1_0_BVN_CRC_Y_STATUS       0x007038a0 /* BVN CRC Luma Status Register */
#define BCHP_VICE2_VIP1_0_BVN_CRC_C_STATUS       0x007038a4 /* BVN CRC Chroma Status Register */
#define BCHP_VICE2_VIP1_0_TPG_FW_CONTROL         0x00703a00 /* TPG FW Control */
#define BCHP_VICE2_VIP1_0_TPG_CONFIG             0x00703a04 /* TPG Configure */
#define BCHP_VICE2_VIP1_0_TPG_PICTURE_SIZE       0x00703a08 /* Active Picture Size */
#define BCHP_VICE2_VIP1_0_BLANKING_SIZE          0x00703a0c /* Blanking Period Size */
#define BCHP_VICE2_VIP1_0_PATTERN_SIZE           0x00703a10 /* Pattern Size */
#define BCHP_VICE2_VIP1_0_STEP_SIZE              0x00703a14 /* Step Size */
#define BCHP_VICE2_VIP1_0_YCrCb_VALUE            0x00703a18 /* YCrCb value */
#define BCHP_VICE2_VIP1_0_PIC_RDY_INTR_DLY       0x00703a1c /* Picture ready interrupt to ARC delay value */
#define BCHP_VICE2_VIP1_0_NUMBER_OF_PICS         0x00703a20 /* Number of pictures the TPG will generate */
#define BCHP_VICE2_VIP1_0_TPG_STATUS             0x00703a24 /* TPG status */

#endif /* #ifndef BCHP_VICE2_VIP1_0_H__ */

/* End of File */

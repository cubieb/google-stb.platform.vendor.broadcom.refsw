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
 * Date:           Generated on         Wed Jan 12 18:40:28 2011
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

#ifndef BCHP_GIO_H__
#define BCHP_GIO_H__

/***************************************************************************
 *GIO - GPIO
 ***************************************************************************/
#define BCHP_GIO_RSVDO                           0x00091100 /* RESERVED0 */
#define BCHP_GIO_RSVD1                           0x00091104 /* RESERVED1 */
#define BCHP_GIO_RSVD2                           0x00091108 /* RESERVED2 */
#define BCHP_GIO_EC_LO                           0x0009110c /* GENERAL PURPOSE I/O EDGE CONFIGURATION */
#define BCHP_GIO_EI_LO                           0x00091110 /* GENERAL PURPOSE I/O EDGE INSENSITIVE */
#define BCHP_GIO_MASK_LO                         0x00091114 /* GENERAL PURPOSE I/O INTERRUPT MASK */
#define BCHP_GIO_LEVEL_LO                        0x00091118 /* GENERAL PURPOSE I/O INTERRUPT TYPE */
#define BCHP_GIO_STAT_LO                         0x0009111c /* GENERAL PURPOSE I/O INTERRUPT STATUS */

/***************************************************************************
 *RSVDO - RESERVED0
 ***************************************************************************/
/* GIO :: RSVDO :: reserved0 [31:00] */
#define BCHP_GIO_RSVDO_reserved0_MASK                              0xffffffff
#define BCHP_GIO_RSVDO_reserved0_SHIFT                             0

/***************************************************************************
 *RSVD1 - RESERVED1
 ***************************************************************************/
/* GIO :: RSVD1 :: reserved0 [31:00] */
#define BCHP_GIO_RSVD1_reserved0_MASK                              0xffffffff
#define BCHP_GIO_RSVD1_reserved0_SHIFT                             0

/***************************************************************************
 *RSVD2 - RESERVED2
 ***************************************************************************/
/* GIO :: RSVD2 :: reserved0 [31:00] */
#define BCHP_GIO_RSVD2_reserved0_MASK                              0xffffffff
#define BCHP_GIO_RSVD2_reserved0_SHIFT                             0

/***************************************************************************
 *EC_LO - GENERAL PURPOSE I/O EDGE CONFIGURATION
 ***************************************************************************/
/* GIO :: EC_LO :: reserved0 [31:26] */
#define BCHP_GIO_EC_LO_reserved0_MASK                              0xfc000000
#define BCHP_GIO_EC_LO_reserved0_SHIFT                             26

/* GIO :: EC_LO :: edge_config [25:00] */
#define BCHP_GIO_EC_LO_edge_config_MASK                            0x03ffffff
#define BCHP_GIO_EC_LO_edge_config_SHIFT                           0

/***************************************************************************
 *EI_LO - GENERAL PURPOSE I/O EDGE INSENSITIVE
 ***************************************************************************/
/* GIO :: EI_LO :: reserved0 [31:26] */
#define BCHP_GIO_EI_LO_reserved0_MASK                              0xfc000000
#define BCHP_GIO_EI_LO_reserved0_SHIFT                             26

/* GIO :: EI_LO :: edge_insensitive [25:00] */
#define BCHP_GIO_EI_LO_edge_insensitive_MASK                       0x03ffffff
#define BCHP_GIO_EI_LO_edge_insensitive_SHIFT                      0

/***************************************************************************
 *MASK_LO - GENERAL PURPOSE I/O INTERRUPT MASK
 ***************************************************************************/
/* GIO :: MASK_LO :: reserved0 [31:26] */
#define BCHP_GIO_MASK_LO_reserved0_MASK                            0xfc000000
#define BCHP_GIO_MASK_LO_reserved0_SHIFT                           26

/* GIO :: MASK_LO :: irq_mask [25:00] */
#define BCHP_GIO_MASK_LO_irq_mask_MASK                             0x03ffffff
#define BCHP_GIO_MASK_LO_irq_mask_SHIFT                            0

/***************************************************************************
 *LEVEL_LO - GENERAL PURPOSE I/O INTERRUPT TYPE
 ***************************************************************************/
/* GIO :: LEVEL_LO :: reserved0 [31:26] */
#define BCHP_GIO_LEVEL_LO_reserved0_MASK                           0xfc000000
#define BCHP_GIO_LEVEL_LO_reserved0_SHIFT                          26

/* GIO :: LEVEL_LO :: level [25:00] */
#define BCHP_GIO_LEVEL_LO_level_MASK                               0x03ffffff
#define BCHP_GIO_LEVEL_LO_level_SHIFT                              0

/***************************************************************************
 *STAT_LO - GENERAL PURPOSE I/O INTERRUPT STATUS
 ***************************************************************************/
/* GIO :: STAT_LO :: reserved0 [31:26] */
#define BCHP_GIO_STAT_LO_reserved0_MASK                            0xfc000000
#define BCHP_GIO_STAT_LO_reserved0_SHIFT                           26

/* GIO :: STAT_LO :: irq_status [25:00] */
#define BCHP_GIO_STAT_LO_irq_status_MASK                           0x03ffffff
#define BCHP_GIO_STAT_LO_irq_status_SHIFT                          0

#endif /* #ifndef BCHP_GIO_H__ */

/* End of File */

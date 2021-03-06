/***************************************************************************
 *     Copyright (c) 1999-2008, Broadcom Corporation
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
 * Date:           Generated on         Wed Jan  9 08:59:12 2008
 *                 MD5 Checksum         847dc12a9d71c4c68a648bbf19a883e3
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

#ifndef BCHP_TERT_IT_H__
#define BCHP_TERT_IT_H__

/***************************************************************************
 *TERT_IT - Primary Input and Timing Control
 ***************************************************************************/
#define BCHP_TERT_IT_IT_REV_ID                   0x00181800 /* Revision ID register */
#define BCHP_TERT_IT_TG_CONFIG                   0x00181808 /* Timing Generator Configuration Register */
#define BCHP_TERT_IT_ADDR_0_3                    0x0018180c /* Timing Generator Address 0-3 Register */
#define BCHP_TERT_IT_ADDR_4_6                    0x00181810 /* Timing Generator Address 4-6 Register */
#define BCHP_TERT_IT_STACK_reg_0_1               0x00181814 /* General Lookup Registers 0&1 Register */
#define BCHP_TERT_IT_STACK_reg_2_3               0x00181818 /* General Lookup Registers 2&3 Register */
#define BCHP_TERT_IT_STACK_reg_4_5               0x0018181c /* General Lookup Registers 4&5 Register */
#define BCHP_TERT_IT_STACK_reg_6_7               0x00181820 /* General Lookup Registers 6&7 Register */
#define BCHP_TERT_IT_EVENT_SELECTION             0x00181824 /* Timing Generator Event Selection Register. */
#define BCHP_TERT_IT_PCL_0                       0x00181828 /* External Digital H/V Syncs and Negative Sync PCL Register. */
#define BCHP_TERT_IT_PCL_1                       0x0018182c /* Color Burst and Bottles PCL Register. */
#define BCHP_TERT_IT_PCL_2                       0x00181830 /* External Digital H/V Syncs and U and V flip PCL Register. */
#define BCHP_TERT_IT_PCL_3                       0x00181834 /* VSync, VBlank, Active Video and Odd/Even Field PCL Register. */
#define BCHP_TERT_IT_PCL_4                       0x00181838 /* Positive Sync A/B PCL Register. */
#define BCHP_TERT_IT_PCL_5                       0x0018183c /* Patten Generation PCL Register. */
#define BCHP_TERT_IT_BVB_SIZE                    0x00181850 /* BVB Size Register. */
#define BCHP_TERT_IT_BVB_RSTATUS                 0x00181854 /* BVB status read Register. */
#define BCHP_TERT_IT_BVB_CSTATUS                 0x00181858 /* BVB status clear Register. */
#define BCHP_TERT_IT_VEC_TRIGGER_0               0x0018185c /* VEC Trigger Register 0 */
#define BCHP_TERT_IT_VEC_TRIGGER_1               0x00181860 /* VEC Trigger Register 1 */
#define BCHP_TERT_IT_VEC_CTRL_STAT               0x00181864 /* VEC Control BUS Status Register */
#define BCHP_TERT_IT_IT_LCNTR                    0x00181868 /* Line Counter Register */
#define BCHP_TERT_IT_ALT_RM_CNTRL                0x0018186c /* ALTERNATE RATE MANAGER CONTROL REGISTER */

/***************************************************************************
 *MICRO_INSTRUCTION%i - Timing Generator RAM Register at location 0..255
 ***************************************************************************/
#define BCHP_TERT_IT_MICRO_INSTRUCTIONi_ARRAY_BASE                 0x00181880
#define BCHP_TERT_IT_MICRO_INSTRUCTIONi_ARRAY_START                0
#define BCHP_TERT_IT_MICRO_INSTRUCTIONi_ARRAY_END                  255
#define BCHP_TERT_IT_MICRO_INSTRUCTIONi_ARRAY_ELEMENT_SIZE         32

/***************************************************************************
 *MICRO_INSTRUCTION%i - Timing Generator RAM Register at location 0..255
 ***************************************************************************/
/* TERT_IT :: MICRO_INSTRUCTIONi :: reserved0 [31:24] */
#define BCHP_TERT_IT_MICRO_INSTRUCTIONi_reserved0_MASK             0xff000000
#define BCHP_TERT_IT_MICRO_INSTRUCTIONi_reserved0_SHIFT            24

/* TERT_IT :: MICRO_INSTRUCTIONi :: OPCODE [23:21] */
#define BCHP_TERT_IT_MICRO_INSTRUCTIONi_OPCODE_MASK                0x00e00000
#define BCHP_TERT_IT_MICRO_INSTRUCTIONi_OPCODE_SHIFT               21
#define BCHP_TERT_IT_MICRO_INSTRUCTIONi_OPCODE_NOP                 0
#define BCHP_TERT_IT_MICRO_INSTRUCTIONi_OPCODE_SCOUNT              1
#define BCHP_TERT_IT_MICRO_INSTRUCTIONi_OPCODE_ECOUNT              2
#define BCHP_TERT_IT_MICRO_INSTRUCTIONi_OPCODE_CALL                3
#define BCHP_TERT_IT_MICRO_INSTRUCTIONi_OPCODE_JUMP                4
#define BCHP_TERT_IT_MICRO_INSTRUCTIONi_OPCODE_RELOAD              5
#define BCHP_TERT_IT_MICRO_INSTRUCTIONi_OPCODE_LOAD                6

/* TERT_IT :: MICRO_INSTRUCTIONi :: RETURN_FLAG [20:20] */
#define BCHP_TERT_IT_MICRO_INSTRUCTIONi_RETURN_FLAG_MASK           0x00100000
#define BCHP_TERT_IT_MICRO_INSTRUCTIONi_RETURN_FLAG_SHIFT          20

/* TERT_IT :: MICRO_INSTRUCTIONi :: FLAGS_OR_ADDR [19:12] */
#define BCHP_TERT_IT_MICRO_INSTRUCTIONi_FLAGS_OR_ADDR_MASK         0x000ff000
#define BCHP_TERT_IT_MICRO_INSTRUCTIONi_FLAGS_OR_ADDR_SHIFT        12

/* union - case ECOUNT [11:00] */
/* TERT_IT :: MICRO_INSTRUCTIONi :: ECOUNT :: EVENT_EDGE [11:11] */
#define BCHP_TERT_IT_MICRO_INSTRUCTIONi_ECOUNT_EVENT_EDGE_MASK     0x00000800
#define BCHP_TERT_IT_MICRO_INSTRUCTIONi_ECOUNT_EVENT_EDGE_SHIFT    11

/* TERT_IT :: MICRO_INSTRUCTIONi :: ECOUNT :: COUNT [10:00] */
#define BCHP_TERT_IT_MICRO_INSTRUCTIONi_ECOUNT_COUNT_MASK          0x000007ff
#define BCHP_TERT_IT_MICRO_INSTRUCTIONi_ECOUNT_COUNT_SHIFT         0

/* union - case SCOUNT [11:00] */
/* TERT_IT :: MICRO_INSTRUCTIONi :: SCOUNT :: COUNT [11:00] */
#define BCHP_TERT_IT_MICRO_INSTRUCTIONi_SCOUNT_COUNT_MASK          0x00000fff
#define BCHP_TERT_IT_MICRO_INSTRUCTIONi_SCOUNT_COUNT_SHIFT         0

/* union - case CALL [11:00] */
/* TERT_IT :: MICRO_INSTRUCTIONi :: CALL :: COUNT [11:00] */
#define BCHP_TERT_IT_MICRO_INSTRUCTIONi_CALL_COUNT_MASK            0x00000fff
#define BCHP_TERT_IT_MICRO_INSTRUCTIONi_CALL_COUNT_SHIFT           0

/* union - case JUMP [11:00] */
/* TERT_IT :: MICRO_INSTRUCTIONi :: JUMP :: reserved0 [11:08] */
#define BCHP_TERT_IT_MICRO_INSTRUCTIONi_JUMP_reserved0_MASK        0x00000f00
#define BCHP_TERT_IT_MICRO_INSTRUCTIONi_JUMP_reserved0_SHIFT       8

/* TERT_IT :: MICRO_INSTRUCTIONi :: JUMP :: STACK_SELECT [07:00] */
#define BCHP_TERT_IT_MICRO_INSTRUCTIONi_JUMP_STACK_SELECT_MASK     0x000000ff
#define BCHP_TERT_IT_MICRO_INSTRUCTIONi_JUMP_STACK_SELECT_SHIFT    0

/* union - case LOAD [11:00] */
/* TERT_IT :: MICRO_INSTRUCTIONi :: LOAD :: reserved0 [11:08] */
#define BCHP_TERT_IT_MICRO_INSTRUCTIONi_LOAD_reserved0_MASK        0x00000f00
#define BCHP_TERT_IT_MICRO_INSTRUCTIONi_LOAD_reserved0_SHIFT       8

/* TERT_IT :: MICRO_INSTRUCTIONi :: LOAD :: STACK_SELECT [07:00] */
#define BCHP_TERT_IT_MICRO_INSTRUCTIONi_LOAD_STACK_SELECT_MASK     0x000000ff
#define BCHP_TERT_IT_MICRO_INSTRUCTIONi_LOAD_STACK_SELECT_SHIFT    0

/* union - case RELOAD [11:00] */
/* TERT_IT :: MICRO_INSTRUCTIONi :: RELOAD :: reserved0 [11:08] */
#define BCHP_TERT_IT_MICRO_INSTRUCTIONi_RELOAD_reserved0_MASK      0x00000f00
#define BCHP_TERT_IT_MICRO_INSTRUCTIONi_RELOAD_reserved0_SHIFT     8

/* TERT_IT :: MICRO_INSTRUCTIONi :: RELOAD :: STACK_SELECT [07:00] */
#define BCHP_TERT_IT_MICRO_INSTRUCTIONi_RELOAD_STACK_SELECT_MASK   0x000000ff
#define BCHP_TERT_IT_MICRO_INSTRUCTIONi_RELOAD_STACK_SELECT_SHIFT  0

/* union - case default [11:00] */
/* TERT_IT :: MICRO_INSTRUCTIONi :: default :: reserved0 [11:00] */
#define BCHP_TERT_IT_MICRO_INSTRUCTIONi_default_reserved0_MASK     0x00000fff
#define BCHP_TERT_IT_MICRO_INSTRUCTIONi_default_reserved0_SHIFT    0


#endif /* #ifndef BCHP_TERT_IT_H__ */

/* End of File */

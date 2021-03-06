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
 * Date:           Generated on               Thu Feb 12 15:15:53 2015
 *                 Full Compile MD5 Checksum  ca339b82db08da0250a17ca09932699d
 *                     (minus title and desc)
 *                 MD5 Checksum               502556bfbdc2f4341f93db8b4326b3ab
 *
 * Compiled with:  RDB Utility                combo_header.pl
 *                 RDB.pm                     15653
 *                 unknown                    unknown
 *                 Perl Interpreter           5.008008
 *                 Operating System           linux
 *
 *
 ***************************************************************************/

#ifndef BCHP_XPT_WDMA_RAMS_H__
#define BCHP_XPT_WDMA_RAMS_H__

/***************************************************************************
 *XPT_WDMA_RAMS
 ***************************************************************************/
#define BCHP_XPT_WDMA_RAMS_FIRST_DESC_ADDR       0x00a6a000 /* [RW] First Descriptor Address */
#define BCHP_XPT_WDMA_RAMS_NEXT_DESC_ADDR        0x00a6a004 /* [RW] Next Descriptor Address */
#define BCHP_XPT_WDMA_RAMS_COMPLETED_DESC_ADDRESS 0x00a6a008 /* [RW] Completed Descriptor Address */
#define BCHP_XPT_WDMA_RAMS_BTP_PACKET_GROUP_ID   0x00a6a00c /* [RW] Packet Group ID reported per BTP command */
#define BCHP_XPT_WDMA_RAMS_RUN_VERSION_CONFIG    0x00a6a010 /* [RW] RUN_VERSION configuration */
#define BCHP_XPT_WDMA_RAMS_OVERFLOW_REASONS      0x00a6a014 /* [RW] Overflow Reason */
#define BCHP_XPT_WDMA_RAMS_DMQ_CONTROL_STRUCT    0x00a6a018 /* [RO] Descriptor Memory Queue Control Structure */
#define BCHP_XPT_WDMA_RAMS_DRAM_BUFF_BASE_PTR_HI 0x00a6a080 /* [RW] DRAM Buffer Base Pointer - Upper bits */
#define BCHP_XPT_WDMA_RAMS_DRAM_BUFF_BASE_PTR    0x00a6a084 /* [RW] DRAM Buffer Base Pointer - Lower 32 bits */
#define BCHP_XPT_WDMA_RAMS_DRAM_BUFF_END_PTR_HI  0x00a6a088 /* [RW] DRAM Buffer End Pointer - Upper bits */
#define BCHP_XPT_WDMA_RAMS_DRAM_BUFF_END_PTR     0x00a6a08c /* [RW] DRAM Buffer End Pointer - Lower 32 bits */
#define BCHP_XPT_WDMA_RAMS_DRAM_BUFF_RD_PTR_HI   0x00a6a090 /* [RW] DRAM Buffer Read Pointer - Upper bits */
#define BCHP_XPT_WDMA_RAMS_DRAM_BUFF_RD_PTR      0x00a6a094 /* [RW] DRAM Buffer Read Pointer - Lower 32 bits */
#define BCHP_XPT_WDMA_RAMS_DRAM_BUFF_WR_PTR_HI   0x00a6a098 /* [RW] DRAM Buffer Write Pointer - Upper bits */
#define BCHP_XPT_WDMA_RAMS_DRAM_BUFF_WR_PTR      0x00a6a09c /* [RW] DRAM Buffer Write Pointer - Lower 32 bits */
#define BCHP_XPT_WDMA_RAMS_DRAM_BUFF_VALID_PTR_HI 0x00a6a0a0 /* [RW] DRAM Buffer Valid Pointer - Upper bits */
#define BCHP_XPT_WDMA_RAMS_DRAM_BUFF_VALID_PTR   0x00a6a0a4 /* [RW] DRAM Buffer Valid Pointer - Lower 32 bits */
#define BCHP_XPT_WDMA_RAMS_DRAM_BUFF_LOWER_THRESHOLD_HI 0x00a6a0a8 /* [RW] DRAM Buffer Lower Threshold - Upper bits */
#define BCHP_XPT_WDMA_RAMS_DRAM_BUFF_LOWER_THRESHOLD 0x00a6a0ac /* [RW] DRAM Buffer Lower Threshold - Lower 32 bits */
#define BCHP_XPT_WDMA_RAMS_DRAM_BUFF_UPPER_THRESHOLD_HI 0x00a6a0b0 /* [RW] DRAM Buffer Upper Threshold - Upper bits */
#define BCHP_XPT_WDMA_RAMS_DRAM_BUFF_UPPER_THRESHOLD 0x00a6a0b4 /* [RW] DRAM Buffer Upper Threshold - Lower 32 bits */
#define BCHP_XPT_WDMA_RAMS_DRAM_BUFF_STATUS      0x00a6a0b8 /* [RW] DRAM Buffer Status */
#define BCHP_XPT_WDMA_RAMS_DRAM_BUFF_CONTROL     0x00a6a0bc /* [RW] DRAM Buffer Control */
#define BCHP_XPT_WDMA_RAMS_DMQ_0_0               0x00a6a0c0 /* [RW] DMQ descriptor 0 - Write Address, Upper bits */
#define BCHP_XPT_WDMA_RAMS_DMQ_0_1               0x00a6a0c4 /* [RW] DMQ descriptor 0 - Write Address, lower 32 bits */
#define BCHP_XPT_WDMA_RAMS_DMQ_0_2               0x00a6a0c8 /* [RW] DMQ descriptor 0 - Transfer Size */
#define BCHP_XPT_WDMA_RAMS_DMQ_0_3               0x00a6a0cc /* [RW] DMQ descriptor 0 - Current Descriptor Address and Control */
#define BCHP_XPT_WDMA_RAMS_DMQ_1_0               0x00a6a0d0 /* [RW] DMQ descriptor 1 - Write Address, Upper bits */
#define BCHP_XPT_WDMA_RAMS_DMQ_1_1               0x00a6a0d4 /* [RW] DMQ descriptor 1 - Write Address, lower 32 bits */
#define BCHP_XPT_WDMA_RAMS_DMQ_1_2               0x00a6a0d8 /* [RW] DMQ descriptor 1 - Transfer Size */
#define BCHP_XPT_WDMA_RAMS_DMQ_1_3               0x00a6a0dc /* [RW] DMQ descriptor 1 - Current Descriptor Address and Control */
#define BCHP_XPT_WDMA_RAMS_DMQ_2_0               0x00a6a0e0 /* [RW] DMQ descriptor 2 - Write Address, Upper bits */
#define BCHP_XPT_WDMA_RAMS_DMQ_2_1               0x00a6a0e4 /* [RW] DMQ descriptor 2 - Write Address, lower 32 bits */
#define BCHP_XPT_WDMA_RAMS_DMQ_2_2               0x00a6a0e8 /* [RW] DMQ descriptor 2 - Transfer Size */
#define BCHP_XPT_WDMA_RAMS_DMQ_2_3               0x00a6a0ec /* [RW] DMQ descriptor 2 - Current Descriptor Address and Control */
#define BCHP_XPT_WDMA_RAMS_DMQ_3_0               0x00a6a0f0 /* [RW] DMQ descriptor 3 - Write Address, Upper bits */
#define BCHP_XPT_WDMA_RAMS_DMQ_3_1               0x00a6a0f4 /* [RW] DMQ descriptor 3 - Write Address, lower 32 bits */
#define BCHP_XPT_WDMA_RAMS_DMQ_3_2               0x00a6a0f8 /* [RW] DMQ descriptor 3 - Transfer Size */
#define BCHP_XPT_WDMA_RAMS_DMQ_3_3               0x00a6a0fc /* [RW] DMQ descriptor 3 - Current Descriptor Address and Control */
#define BCHP_XPT_WDMA_RAMS_CHAN_OFFSET           0x00a6a100 /* [RO] This is here so we know the offset of channel 1 relative to channel 0. */
#define BCHP_XPT_WDMA_RAMS_RDB_MEM_RESIZER       0x00a6bffc /* [RO] This is here so that enough space is reserved by RDB for the actual memory, which contains 32 per-channel portions, with offsets to one another as indicated by the offset of the CHAN_OFFSET register */

/***************************************************************************
 *FIRST_DESC_ADDR - First Descriptor Address
 ***************************************************************************/
/* XPT_WDMA_RAMS :: FIRST_DESC_ADDR :: FIRST_DESC_ADDRESS [31:04] */
#define BCHP_XPT_WDMA_RAMS_FIRST_DESC_ADDR_FIRST_DESC_ADDRESS_MASK 0xfffffff0
#define BCHP_XPT_WDMA_RAMS_FIRST_DESC_ADDR_FIRST_DESC_ADDRESS_SHIFT 4

/* XPT_WDMA_RAMS :: FIRST_DESC_ADDR :: reserved0 [03:00] */
#define BCHP_XPT_WDMA_RAMS_FIRST_DESC_ADDR_reserved0_MASK          0x0000000f
#define BCHP_XPT_WDMA_RAMS_FIRST_DESC_ADDR_reserved0_SHIFT         0

/***************************************************************************
 *NEXT_DESC_ADDR - Next Descriptor Address
 ***************************************************************************/
/* XPT_WDMA_RAMS :: NEXT_DESC_ADDR :: NEXT_DESC_ADDR [31:04] */
#define BCHP_XPT_WDMA_RAMS_NEXT_DESC_ADDR_NEXT_DESC_ADDR_MASK      0xfffffff0
#define BCHP_XPT_WDMA_RAMS_NEXT_DESC_ADDR_NEXT_DESC_ADDR_SHIFT     4

/* XPT_WDMA_RAMS :: NEXT_DESC_ADDR :: reserved0 [03:00] */
#define BCHP_XPT_WDMA_RAMS_NEXT_DESC_ADDR_reserved0_MASK           0x0000000f
#define BCHP_XPT_WDMA_RAMS_NEXT_DESC_ADDR_reserved0_SHIFT          0

/***************************************************************************
 *COMPLETED_DESC_ADDRESS - Completed Descriptor Address
 ***************************************************************************/
/* XPT_WDMA_RAMS :: COMPLETED_DESC_ADDRESS :: COMPLETED_DESC_ADDRESS [31:04] */
#define BCHP_XPT_WDMA_RAMS_COMPLETED_DESC_ADDRESS_COMPLETED_DESC_ADDRESS_MASK 0xfffffff0
#define BCHP_XPT_WDMA_RAMS_COMPLETED_DESC_ADDRESS_COMPLETED_DESC_ADDRESS_SHIFT 4

/* XPT_WDMA_RAMS :: COMPLETED_DESC_ADDRESS :: reserved0 [03:00] */
#define BCHP_XPT_WDMA_RAMS_COMPLETED_DESC_ADDRESS_reserved0_MASK   0x0000000f
#define BCHP_XPT_WDMA_RAMS_COMPLETED_DESC_ADDRESS_reserved0_SHIFT  0

/***************************************************************************
 *BTP_PACKET_GROUP_ID - Packet Group ID reported per BTP command
 ***************************************************************************/
/* XPT_WDMA_RAMS :: BTP_PACKET_GROUP_ID :: reserved0 [31:08] */
#define BCHP_XPT_WDMA_RAMS_BTP_PACKET_GROUP_ID_reserved0_MASK      0xffffff00
#define BCHP_XPT_WDMA_RAMS_BTP_PACKET_GROUP_ID_reserved0_SHIFT     8

/* XPT_WDMA_RAMS :: BTP_PACKET_GROUP_ID :: BTP_PACKET_GROUP_ID [07:00] */
#define BCHP_XPT_WDMA_RAMS_BTP_PACKET_GROUP_ID_BTP_PACKET_GROUP_ID_MASK 0x000000ff
#define BCHP_XPT_WDMA_RAMS_BTP_PACKET_GROUP_ID_BTP_PACKET_GROUP_ID_SHIFT 0

/***************************************************************************
 *RUN_VERSION_CONFIG - RUN_VERSION configuration
 ***************************************************************************/
/* XPT_WDMA_RAMS :: RUN_VERSION_CONFIG :: reserved0 [31:05] */
#define BCHP_XPT_WDMA_RAMS_RUN_VERSION_CONFIG_reserved0_MASK       0xffffffe0
#define BCHP_XPT_WDMA_RAMS_RUN_VERSION_CONFIG_reserved0_SHIFT      5

/* XPT_WDMA_RAMS :: RUN_VERSION_CONFIG :: RUN_VERSION [04:00] */
#define BCHP_XPT_WDMA_RAMS_RUN_VERSION_CONFIG_RUN_VERSION_MASK     0x0000001f
#define BCHP_XPT_WDMA_RAMS_RUN_VERSION_CONFIG_RUN_VERSION_SHIFT    0

/***************************************************************************
 *OVERFLOW_REASONS - Overflow Reason
 ***************************************************************************/
/* XPT_WDMA_RAMS :: OVERFLOW_REASONS :: reserved0 [31:05] */
#define BCHP_XPT_WDMA_RAMS_OVERFLOW_REASONS_reserved0_MASK         0xffffffe0
#define BCHP_XPT_WDMA_RAMS_OVERFLOW_REASONS_reserved0_SHIFT        5

/* XPT_WDMA_RAMS :: OVERFLOW_REASONS :: PACKET_SYNC_ERROR [04:04] */
#define BCHP_XPT_WDMA_RAMS_OVERFLOW_REASONS_PACKET_SYNC_ERROR_MASK 0x00000010
#define BCHP_XPT_WDMA_RAMS_OVERFLOW_REASONS_PACKET_SYNC_ERROR_SHIFT 4

/* XPT_WDMA_RAMS :: OVERFLOW_REASONS :: RING_BUFFER_FULL [03:03] */
#define BCHP_XPT_WDMA_RAMS_OVERFLOW_REASONS_RING_BUFFER_FULL_MASK  0x00000008
#define BCHP_XPT_WDMA_RAMS_OVERFLOW_REASONS_RING_BUFFER_FULL_SHIFT 3

/* XPT_WDMA_RAMS :: OVERFLOW_REASONS :: RUN_NOT_SET [02:02] */
#define BCHP_XPT_WDMA_RAMS_OVERFLOW_REASONS_RUN_NOT_SET_MASK       0x00000004
#define BCHP_XPT_WDMA_RAMS_OVERFLOW_REASONS_RUN_NOT_SET_SHIFT      2

/* XPT_WDMA_RAMS :: OVERFLOW_REASONS :: SLEEP_NO_WAKE [01:01] */
#define BCHP_XPT_WDMA_RAMS_OVERFLOW_REASONS_SLEEP_NO_WAKE_MASK     0x00000002
#define BCHP_XPT_WDMA_RAMS_OVERFLOW_REASONS_SLEEP_NO_WAKE_SHIFT    1

/* XPT_WDMA_RAMS :: OVERFLOW_REASONS :: DATA_STALL_TIMEOUT [00:00] */
#define BCHP_XPT_WDMA_RAMS_OVERFLOW_REASONS_DATA_STALL_TIMEOUT_MASK 0x00000001
#define BCHP_XPT_WDMA_RAMS_OVERFLOW_REASONS_DATA_STALL_TIMEOUT_SHIFT 0

/***************************************************************************
 *DMQ_CONTROL_STRUCT - Descriptor Memory Queue Control Structure
 ***************************************************************************/
/* XPT_WDMA_RAMS :: DMQ_CONTROL_STRUCT :: reserved0 [31:06] */
#define BCHP_XPT_WDMA_RAMS_DMQ_CONTROL_STRUCT_reserved0_MASK       0xffffffc0
#define BCHP_XPT_WDMA_RAMS_DMQ_CONTROL_STRUCT_reserved0_SHIFT      6

/* XPT_WDMA_RAMS :: DMQ_CONTROL_STRUCT :: FULL [05:05] */
#define BCHP_XPT_WDMA_RAMS_DMQ_CONTROL_STRUCT_FULL_MASK            0x00000020
#define BCHP_XPT_WDMA_RAMS_DMQ_CONTROL_STRUCT_FULL_SHIFT           5

/* XPT_WDMA_RAMS :: DMQ_CONTROL_STRUCT :: EMPTY [04:04] */
#define BCHP_XPT_WDMA_RAMS_DMQ_CONTROL_STRUCT_EMPTY_MASK           0x00000010
#define BCHP_XPT_WDMA_RAMS_DMQ_CONTROL_STRUCT_EMPTY_SHIFT          4

/* XPT_WDMA_RAMS :: DMQ_CONTROL_STRUCT :: WRITE_PTR [03:02] */
#define BCHP_XPT_WDMA_RAMS_DMQ_CONTROL_STRUCT_WRITE_PTR_MASK       0x0000000c
#define BCHP_XPT_WDMA_RAMS_DMQ_CONTROL_STRUCT_WRITE_PTR_SHIFT      2

/* XPT_WDMA_RAMS :: DMQ_CONTROL_STRUCT :: READ_PTR [01:00] */
#define BCHP_XPT_WDMA_RAMS_DMQ_CONTROL_STRUCT_READ_PTR_MASK        0x00000003
#define BCHP_XPT_WDMA_RAMS_DMQ_CONTROL_STRUCT_READ_PTR_SHIFT       0

/***************************************************************************
 *DRAM_BUFF_BASE_PTR_HI - DRAM Buffer Base Pointer - Upper bits
 ***************************************************************************/
/* XPT_WDMA_RAMS :: DRAM_BUFF_BASE_PTR_HI :: reserved0 [31:08] */
#define BCHP_XPT_WDMA_RAMS_DRAM_BUFF_BASE_PTR_HI_reserved0_MASK    0xffffff00
#define BCHP_XPT_WDMA_RAMS_DRAM_BUFF_BASE_PTR_HI_reserved0_SHIFT   8

/* XPT_WDMA_RAMS :: DRAM_BUFF_BASE_PTR_HI :: BASE_PTR_HI [07:00] */
#define BCHP_XPT_WDMA_RAMS_DRAM_BUFF_BASE_PTR_HI_BASE_PTR_HI_MASK  0x000000ff
#define BCHP_XPT_WDMA_RAMS_DRAM_BUFF_BASE_PTR_HI_BASE_PTR_HI_SHIFT 0

/***************************************************************************
 *DRAM_BUFF_BASE_PTR - DRAM Buffer Base Pointer - Lower 32 bits
 ***************************************************************************/
/* XPT_WDMA_RAMS :: DRAM_BUFF_BASE_PTR :: BASE_PTR [31:00] */
#define BCHP_XPT_WDMA_RAMS_DRAM_BUFF_BASE_PTR_BASE_PTR_MASK        0xffffffff
#define BCHP_XPT_WDMA_RAMS_DRAM_BUFF_BASE_PTR_BASE_PTR_SHIFT       0

/***************************************************************************
 *DRAM_BUFF_END_PTR_HI - DRAM Buffer End Pointer - Upper bits
 ***************************************************************************/
/* XPT_WDMA_RAMS :: DRAM_BUFF_END_PTR_HI :: reserved0 [31:08] */
#define BCHP_XPT_WDMA_RAMS_DRAM_BUFF_END_PTR_HI_reserved0_MASK     0xffffff00
#define BCHP_XPT_WDMA_RAMS_DRAM_BUFF_END_PTR_HI_reserved0_SHIFT    8

/* XPT_WDMA_RAMS :: DRAM_BUFF_END_PTR_HI :: END_PTR_HI [07:00] */
#define BCHP_XPT_WDMA_RAMS_DRAM_BUFF_END_PTR_HI_END_PTR_HI_MASK    0x000000ff
#define BCHP_XPT_WDMA_RAMS_DRAM_BUFF_END_PTR_HI_END_PTR_HI_SHIFT   0

/***************************************************************************
 *DRAM_BUFF_END_PTR - DRAM Buffer End Pointer - Lower 32 bits
 ***************************************************************************/
/* XPT_WDMA_RAMS :: DRAM_BUFF_END_PTR :: END_PTR [31:00] */
#define BCHP_XPT_WDMA_RAMS_DRAM_BUFF_END_PTR_END_PTR_MASK          0xffffffff
#define BCHP_XPT_WDMA_RAMS_DRAM_BUFF_END_PTR_END_PTR_SHIFT         0

/***************************************************************************
 *DRAM_BUFF_RD_PTR_HI - DRAM Buffer Read Pointer - Upper bits
 ***************************************************************************/
/* XPT_WDMA_RAMS :: DRAM_BUFF_RD_PTR_HI :: reserved0 [31:08] */
#define BCHP_XPT_WDMA_RAMS_DRAM_BUFF_RD_PTR_HI_reserved0_MASK      0xffffff00
#define BCHP_XPT_WDMA_RAMS_DRAM_BUFF_RD_PTR_HI_reserved0_SHIFT     8

/* XPT_WDMA_RAMS :: DRAM_BUFF_RD_PTR_HI :: RD_PTR_HI [07:00] */
#define BCHP_XPT_WDMA_RAMS_DRAM_BUFF_RD_PTR_HI_RD_PTR_HI_MASK      0x000000ff
#define BCHP_XPT_WDMA_RAMS_DRAM_BUFF_RD_PTR_HI_RD_PTR_HI_SHIFT     0

/***************************************************************************
 *DRAM_BUFF_RD_PTR - DRAM Buffer Read Pointer - Lower 32 bits
 ***************************************************************************/
/* XPT_WDMA_RAMS :: DRAM_BUFF_RD_PTR :: RD_PTR [31:00] */
#define BCHP_XPT_WDMA_RAMS_DRAM_BUFF_RD_PTR_RD_PTR_MASK            0xffffffff
#define BCHP_XPT_WDMA_RAMS_DRAM_BUFF_RD_PTR_RD_PTR_SHIFT           0

/***************************************************************************
 *DRAM_BUFF_WR_PTR_HI - DRAM Buffer Write Pointer - Upper bits
 ***************************************************************************/
/* XPT_WDMA_RAMS :: DRAM_BUFF_WR_PTR_HI :: reserved0 [31:08] */
#define BCHP_XPT_WDMA_RAMS_DRAM_BUFF_WR_PTR_HI_reserved0_MASK      0xffffff00
#define BCHP_XPT_WDMA_RAMS_DRAM_BUFF_WR_PTR_HI_reserved0_SHIFT     8

/* XPT_WDMA_RAMS :: DRAM_BUFF_WR_PTR_HI :: WR_PTR_HI [07:00] */
#define BCHP_XPT_WDMA_RAMS_DRAM_BUFF_WR_PTR_HI_WR_PTR_HI_MASK      0x000000ff
#define BCHP_XPT_WDMA_RAMS_DRAM_BUFF_WR_PTR_HI_WR_PTR_HI_SHIFT     0

/***************************************************************************
 *DRAM_BUFF_WR_PTR - DRAM Buffer Write Pointer - Lower 32 bits
 ***************************************************************************/
/* XPT_WDMA_RAMS :: DRAM_BUFF_WR_PTR :: WR_PTR [31:00] */
#define BCHP_XPT_WDMA_RAMS_DRAM_BUFF_WR_PTR_WR_PTR_MASK            0xffffffff
#define BCHP_XPT_WDMA_RAMS_DRAM_BUFF_WR_PTR_WR_PTR_SHIFT           0

/***************************************************************************
 *DRAM_BUFF_VALID_PTR_HI - DRAM Buffer Valid Pointer - Upper bits
 ***************************************************************************/
/* XPT_WDMA_RAMS :: DRAM_BUFF_VALID_PTR_HI :: reserved0 [31:08] */
#define BCHP_XPT_WDMA_RAMS_DRAM_BUFF_VALID_PTR_HI_reserved0_MASK   0xffffff00
#define BCHP_XPT_WDMA_RAMS_DRAM_BUFF_VALID_PTR_HI_reserved0_SHIFT  8

/* XPT_WDMA_RAMS :: DRAM_BUFF_VALID_PTR_HI :: VALID_PTR_HI [07:00] */
#define BCHP_XPT_WDMA_RAMS_DRAM_BUFF_VALID_PTR_HI_VALID_PTR_HI_MASK 0x000000ff
#define BCHP_XPT_WDMA_RAMS_DRAM_BUFF_VALID_PTR_HI_VALID_PTR_HI_SHIFT 0

/***************************************************************************
 *DRAM_BUFF_VALID_PTR - DRAM Buffer Valid Pointer - Lower 32 bits
 ***************************************************************************/
/* XPT_WDMA_RAMS :: DRAM_BUFF_VALID_PTR :: VALID_PTR_HI [31:00] */
#define BCHP_XPT_WDMA_RAMS_DRAM_BUFF_VALID_PTR_VALID_PTR_HI_MASK   0xffffffff
#define BCHP_XPT_WDMA_RAMS_DRAM_BUFF_VALID_PTR_VALID_PTR_HI_SHIFT  0

/***************************************************************************
 *DRAM_BUFF_LOWER_THRESHOLD_HI - DRAM Buffer Lower Threshold - Upper bits
 ***************************************************************************/
/* XPT_WDMA_RAMS :: DRAM_BUFF_LOWER_THRESHOLD_HI :: reserved0 [31:08] */
#define BCHP_XPT_WDMA_RAMS_DRAM_BUFF_LOWER_THRESHOLD_HI_reserved0_MASK 0xffffff00
#define BCHP_XPT_WDMA_RAMS_DRAM_BUFF_LOWER_THRESHOLD_HI_reserved0_SHIFT 8

/* XPT_WDMA_RAMS :: DRAM_BUFF_LOWER_THRESHOLD_HI :: LOWER_THRESHOLD_HI [07:00] */
#define BCHP_XPT_WDMA_RAMS_DRAM_BUFF_LOWER_THRESHOLD_HI_LOWER_THRESHOLD_HI_MASK 0x000000ff
#define BCHP_XPT_WDMA_RAMS_DRAM_BUFF_LOWER_THRESHOLD_HI_LOWER_THRESHOLD_HI_SHIFT 0

/***************************************************************************
 *DRAM_BUFF_LOWER_THRESHOLD - DRAM Buffer Lower Threshold - Lower 32 bits
 ***************************************************************************/
/* XPT_WDMA_RAMS :: DRAM_BUFF_LOWER_THRESHOLD :: LOWER_THRESHOLD [31:00] */
#define BCHP_XPT_WDMA_RAMS_DRAM_BUFF_LOWER_THRESHOLD_LOWER_THRESHOLD_MASK 0xffffffff
#define BCHP_XPT_WDMA_RAMS_DRAM_BUFF_LOWER_THRESHOLD_LOWER_THRESHOLD_SHIFT 0

/***************************************************************************
 *DRAM_BUFF_UPPER_THRESHOLD_HI - DRAM Buffer Upper Threshold - Upper bits
 ***************************************************************************/
/* XPT_WDMA_RAMS :: DRAM_BUFF_UPPER_THRESHOLD_HI :: reserved0 [31:08] */
#define BCHP_XPT_WDMA_RAMS_DRAM_BUFF_UPPER_THRESHOLD_HI_reserved0_MASK 0xffffff00
#define BCHP_XPT_WDMA_RAMS_DRAM_BUFF_UPPER_THRESHOLD_HI_reserved0_SHIFT 8

/* XPT_WDMA_RAMS :: DRAM_BUFF_UPPER_THRESHOLD_HI :: UPPER_THRESHOLD_HI [07:00] */
#define BCHP_XPT_WDMA_RAMS_DRAM_BUFF_UPPER_THRESHOLD_HI_UPPER_THRESHOLD_HI_MASK 0x000000ff
#define BCHP_XPT_WDMA_RAMS_DRAM_BUFF_UPPER_THRESHOLD_HI_UPPER_THRESHOLD_HI_SHIFT 0

/***************************************************************************
 *DRAM_BUFF_UPPER_THRESHOLD - DRAM Buffer Upper Threshold - Lower 32 bits
 ***************************************************************************/
/* XPT_WDMA_RAMS :: DRAM_BUFF_UPPER_THRESHOLD :: LOWER_THRESHOLD [31:00] */
#define BCHP_XPT_WDMA_RAMS_DRAM_BUFF_UPPER_THRESHOLD_LOWER_THRESHOLD_MASK 0xffffffff
#define BCHP_XPT_WDMA_RAMS_DRAM_BUFF_UPPER_THRESHOLD_LOWER_THRESHOLD_SHIFT 0

/***************************************************************************
 *DRAM_BUFF_STATUS - DRAM Buffer Status
 ***************************************************************************/
/* XPT_WDMA_RAMS :: DRAM_BUFF_STATUS :: reserved0 [31:08] */
#define BCHP_XPT_WDMA_RAMS_DRAM_BUFF_STATUS_reserved0_MASK         0xffffff00
#define BCHP_XPT_WDMA_RAMS_DRAM_BUFF_STATUS_reserved0_SHIFT        8

/* XPT_WDMA_RAMS :: DRAM_BUFF_STATUS :: reserved_for_eco1 [07:02] */
#define BCHP_XPT_WDMA_RAMS_DRAM_BUFF_STATUS_reserved_for_eco1_MASK 0x000000fc
#define BCHP_XPT_WDMA_RAMS_DRAM_BUFF_STATUS_reserved_for_eco1_SHIFT 2

/* XPT_WDMA_RAMS :: DRAM_BUFF_STATUS :: RING_BUFFER_FULL [01:01] */
#define BCHP_XPT_WDMA_RAMS_DRAM_BUFF_STATUS_RING_BUFFER_FULL_MASK  0x00000002
#define BCHP_XPT_WDMA_RAMS_DRAM_BUFF_STATUS_RING_BUFFER_FULL_SHIFT 1

/* XPT_WDMA_RAMS :: DRAM_BUFF_STATUS :: RING_BUFFER_EMPTY [00:00] */
#define BCHP_XPT_WDMA_RAMS_DRAM_BUFF_STATUS_RING_BUFFER_EMPTY_MASK 0x00000001
#define BCHP_XPT_WDMA_RAMS_DRAM_BUFF_STATUS_RING_BUFFER_EMPTY_SHIFT 0

/***************************************************************************
 *DRAM_BUFF_CONTROL - DRAM Buffer Control
 ***************************************************************************/
/* XPT_WDMA_RAMS :: DRAM_BUFF_CONTROL :: CURRENT_DESC_ADDRESS [31:04] */
#define BCHP_XPT_WDMA_RAMS_DRAM_BUFF_CONTROL_CURRENT_DESC_ADDRESS_MASK 0xfffffff0
#define BCHP_XPT_WDMA_RAMS_DRAM_BUFF_CONTROL_CURRENT_DESC_ADDRESS_SHIFT 4

/* XPT_WDMA_RAMS :: DRAM_BUFF_CONTROL :: SWAP_HWORDS [03:03] */
#define BCHP_XPT_WDMA_RAMS_DRAM_BUFF_CONTROL_SWAP_HWORDS_MASK      0x00000008
#define BCHP_XPT_WDMA_RAMS_DRAM_BUFF_CONTROL_SWAP_HWORDS_SHIFT     3

/* XPT_WDMA_RAMS :: DRAM_BUFF_CONTROL :: STRAP_INVERT [02:02] */
#define BCHP_XPT_WDMA_RAMS_DRAM_BUFF_CONTROL_STRAP_INVERT_MASK     0x00000004
#define BCHP_XPT_WDMA_RAMS_DRAM_BUFF_CONTROL_STRAP_INVERT_SHIFT    2

/* XPT_WDMA_RAMS :: DRAM_BUFF_CONTROL :: INT_EN [01:01] */
#define BCHP_XPT_WDMA_RAMS_DRAM_BUFF_CONTROL_INT_EN_MASK           0x00000002
#define BCHP_XPT_WDMA_RAMS_DRAM_BUFF_CONTROL_INT_EN_SHIFT          1

/* XPT_WDMA_RAMS :: DRAM_BUFF_CONTROL :: reserved_for_eco0 [00:00] */
#define BCHP_XPT_WDMA_RAMS_DRAM_BUFF_CONTROL_reserved_for_eco0_MASK 0x00000001
#define BCHP_XPT_WDMA_RAMS_DRAM_BUFF_CONTROL_reserved_for_eco0_SHIFT 0

/***************************************************************************
 *DMQ_0_0 - DMQ descriptor 0 - Write Address, Upper bits
 ***************************************************************************/
/* XPT_WDMA_RAMS :: DMQ_0_0 :: reserved_for_eco0 [31:08] */
#define BCHP_XPT_WDMA_RAMS_DMQ_0_0_reserved_for_eco0_MASK          0xffffff00
#define BCHP_XPT_WDMA_RAMS_DMQ_0_0_reserved_for_eco0_SHIFT         8

/* XPT_WDMA_RAMS :: DMQ_0_0 :: WRITE_ADDRESS_HI [07:00] */
#define BCHP_XPT_WDMA_RAMS_DMQ_0_0_WRITE_ADDRESS_HI_MASK           0x000000ff
#define BCHP_XPT_WDMA_RAMS_DMQ_0_0_WRITE_ADDRESS_HI_SHIFT          0

/***************************************************************************
 *DMQ_0_1 - DMQ descriptor 0 - Write Address, lower 32 bits
 ***************************************************************************/
/* XPT_WDMA_RAMS :: DMQ_0_1 :: WRITE_ADDRESS [31:00] */
#define BCHP_XPT_WDMA_RAMS_DMQ_0_1_WRITE_ADDRESS_MASK              0xffffffff
#define BCHP_XPT_WDMA_RAMS_DMQ_0_1_WRITE_ADDRESS_SHIFT             0

/***************************************************************************
 *DMQ_0_2 - DMQ descriptor 0 - Transfer Size
 ***************************************************************************/
/* XPT_WDMA_RAMS :: DMQ_0_2 :: TXFER_SIZE [31:00] */
#define BCHP_XPT_WDMA_RAMS_DMQ_0_2_TXFER_SIZE_MASK                 0xffffffff
#define BCHP_XPT_WDMA_RAMS_DMQ_0_2_TXFER_SIZE_SHIFT                0

/***************************************************************************
 *DMQ_0_3 - DMQ descriptor 0 - Current Descriptor Address and Control
 ***************************************************************************/
/* XPT_WDMA_RAMS :: DMQ_0_3 :: CURRENT_DESC_ADDRESS [31:04] */
#define BCHP_XPT_WDMA_RAMS_DMQ_0_3_CURRENT_DESC_ADDRESS_MASK       0xfffffff0
#define BCHP_XPT_WDMA_RAMS_DMQ_0_3_CURRENT_DESC_ADDRESS_SHIFT      4

/* XPT_WDMA_RAMS :: DMQ_0_3 :: SWAP_HWORDS [03:03] */
#define BCHP_XPT_WDMA_RAMS_DMQ_0_3_SWAP_HWORDS_MASK                0x00000008
#define BCHP_XPT_WDMA_RAMS_DMQ_0_3_SWAP_HWORDS_SHIFT               3

/* XPT_WDMA_RAMS :: DMQ_0_3 :: STRAP_INVERT [02:02] */
#define BCHP_XPT_WDMA_RAMS_DMQ_0_3_STRAP_INVERT_MASK               0x00000004
#define BCHP_XPT_WDMA_RAMS_DMQ_0_3_STRAP_INVERT_SHIFT              2

/* XPT_WDMA_RAMS :: DMQ_0_3 :: INT_EN [01:01] */
#define BCHP_XPT_WDMA_RAMS_DMQ_0_3_INT_EN_MASK                     0x00000002
#define BCHP_XPT_WDMA_RAMS_DMQ_0_3_INT_EN_SHIFT                    1

/* XPT_WDMA_RAMS :: DMQ_0_3 :: LAST [00:00] */
#define BCHP_XPT_WDMA_RAMS_DMQ_0_3_LAST_MASK                       0x00000001
#define BCHP_XPT_WDMA_RAMS_DMQ_0_3_LAST_SHIFT                      0

/***************************************************************************
 *DMQ_1_0 - DMQ descriptor 1 - Write Address, Upper bits
 ***************************************************************************/
/* XPT_WDMA_RAMS :: DMQ_1_0 :: reserved_for_eco0 [31:08] */
#define BCHP_XPT_WDMA_RAMS_DMQ_1_0_reserved_for_eco0_MASK          0xffffff00
#define BCHP_XPT_WDMA_RAMS_DMQ_1_0_reserved_for_eco0_SHIFT         8

/* XPT_WDMA_RAMS :: DMQ_1_0 :: WRITE_ADDRESS_HI [07:00] */
#define BCHP_XPT_WDMA_RAMS_DMQ_1_0_WRITE_ADDRESS_HI_MASK           0x000000ff
#define BCHP_XPT_WDMA_RAMS_DMQ_1_0_WRITE_ADDRESS_HI_SHIFT          0

/***************************************************************************
 *DMQ_1_1 - DMQ descriptor 1 - Write Address, lower 32 bits
 ***************************************************************************/
/* XPT_WDMA_RAMS :: DMQ_1_1 :: WRITE_ADDRESS [31:00] */
#define BCHP_XPT_WDMA_RAMS_DMQ_1_1_WRITE_ADDRESS_MASK              0xffffffff
#define BCHP_XPT_WDMA_RAMS_DMQ_1_1_WRITE_ADDRESS_SHIFT             0

/***************************************************************************
 *DMQ_1_2 - DMQ descriptor 1 - Transfer Size
 ***************************************************************************/
/* XPT_WDMA_RAMS :: DMQ_1_2 :: TXFER_SIZE [31:00] */
#define BCHP_XPT_WDMA_RAMS_DMQ_1_2_TXFER_SIZE_MASK                 0xffffffff
#define BCHP_XPT_WDMA_RAMS_DMQ_1_2_TXFER_SIZE_SHIFT                0

/***************************************************************************
 *DMQ_1_3 - DMQ descriptor 1 - Current Descriptor Address and Control
 ***************************************************************************/
/* XPT_WDMA_RAMS :: DMQ_1_3 :: CURRENT_DESC_ADDRESS [31:04] */
#define BCHP_XPT_WDMA_RAMS_DMQ_1_3_CURRENT_DESC_ADDRESS_MASK       0xfffffff0
#define BCHP_XPT_WDMA_RAMS_DMQ_1_3_CURRENT_DESC_ADDRESS_SHIFT      4

/* XPT_WDMA_RAMS :: DMQ_1_3 :: SWAP_HWORDS [03:03] */
#define BCHP_XPT_WDMA_RAMS_DMQ_1_3_SWAP_HWORDS_MASK                0x00000008
#define BCHP_XPT_WDMA_RAMS_DMQ_1_3_SWAP_HWORDS_SHIFT               3

/* XPT_WDMA_RAMS :: DMQ_1_3 :: STRAP_INVERT [02:02] */
#define BCHP_XPT_WDMA_RAMS_DMQ_1_3_STRAP_INVERT_MASK               0x00000004
#define BCHP_XPT_WDMA_RAMS_DMQ_1_3_STRAP_INVERT_SHIFT              2

/* XPT_WDMA_RAMS :: DMQ_1_3 :: INT_EN [01:01] */
#define BCHP_XPT_WDMA_RAMS_DMQ_1_3_INT_EN_MASK                     0x00000002
#define BCHP_XPT_WDMA_RAMS_DMQ_1_3_INT_EN_SHIFT                    1

/* XPT_WDMA_RAMS :: DMQ_1_3 :: LAST [00:00] */
#define BCHP_XPT_WDMA_RAMS_DMQ_1_3_LAST_MASK                       0x00000001
#define BCHP_XPT_WDMA_RAMS_DMQ_1_3_LAST_SHIFT                      0

/***************************************************************************
 *DMQ_2_0 - DMQ descriptor 2 - Write Address, Upper bits
 ***************************************************************************/
/* XPT_WDMA_RAMS :: DMQ_2_0 :: reserved_for_eco0 [31:08] */
#define BCHP_XPT_WDMA_RAMS_DMQ_2_0_reserved_for_eco0_MASK          0xffffff00
#define BCHP_XPT_WDMA_RAMS_DMQ_2_0_reserved_for_eco0_SHIFT         8

/* XPT_WDMA_RAMS :: DMQ_2_0 :: WRITE_ADDRESS_HI [07:00] */
#define BCHP_XPT_WDMA_RAMS_DMQ_2_0_WRITE_ADDRESS_HI_MASK           0x000000ff
#define BCHP_XPT_WDMA_RAMS_DMQ_2_0_WRITE_ADDRESS_HI_SHIFT          0

/***************************************************************************
 *DMQ_2_1 - DMQ descriptor 2 - Write Address, lower 32 bits
 ***************************************************************************/
/* XPT_WDMA_RAMS :: DMQ_2_1 :: WRITE_ADDRESS [31:00] */
#define BCHP_XPT_WDMA_RAMS_DMQ_2_1_WRITE_ADDRESS_MASK              0xffffffff
#define BCHP_XPT_WDMA_RAMS_DMQ_2_1_WRITE_ADDRESS_SHIFT             0

/***************************************************************************
 *DMQ_2_2 - DMQ descriptor 2 - Transfer Size
 ***************************************************************************/
/* XPT_WDMA_RAMS :: DMQ_2_2 :: TXFER_SIZE [31:00] */
#define BCHP_XPT_WDMA_RAMS_DMQ_2_2_TXFER_SIZE_MASK                 0xffffffff
#define BCHP_XPT_WDMA_RAMS_DMQ_2_2_TXFER_SIZE_SHIFT                0

/***************************************************************************
 *DMQ_2_3 - DMQ descriptor 2 - Current Descriptor Address and Control
 ***************************************************************************/
/* XPT_WDMA_RAMS :: DMQ_2_3 :: CURRENT_DESC_ADDRESS [31:04] */
#define BCHP_XPT_WDMA_RAMS_DMQ_2_3_CURRENT_DESC_ADDRESS_MASK       0xfffffff0
#define BCHP_XPT_WDMA_RAMS_DMQ_2_3_CURRENT_DESC_ADDRESS_SHIFT      4

/* XPT_WDMA_RAMS :: DMQ_2_3 :: SWAP_HWORDS [03:03] */
#define BCHP_XPT_WDMA_RAMS_DMQ_2_3_SWAP_HWORDS_MASK                0x00000008
#define BCHP_XPT_WDMA_RAMS_DMQ_2_3_SWAP_HWORDS_SHIFT               3

/* XPT_WDMA_RAMS :: DMQ_2_3 :: STRAP_INVERT [02:02] */
#define BCHP_XPT_WDMA_RAMS_DMQ_2_3_STRAP_INVERT_MASK               0x00000004
#define BCHP_XPT_WDMA_RAMS_DMQ_2_3_STRAP_INVERT_SHIFT              2

/* XPT_WDMA_RAMS :: DMQ_2_3 :: INT_EN [01:01] */
#define BCHP_XPT_WDMA_RAMS_DMQ_2_3_INT_EN_MASK                     0x00000002
#define BCHP_XPT_WDMA_RAMS_DMQ_2_3_INT_EN_SHIFT                    1

/* XPT_WDMA_RAMS :: DMQ_2_3 :: LAST [00:00] */
#define BCHP_XPT_WDMA_RAMS_DMQ_2_3_LAST_MASK                       0x00000001
#define BCHP_XPT_WDMA_RAMS_DMQ_2_3_LAST_SHIFT                      0

/***************************************************************************
 *DMQ_3_0 - DMQ descriptor 3 - Write Address, Upper bits
 ***************************************************************************/
/* XPT_WDMA_RAMS :: DMQ_3_0 :: reserved_for_eco0 [31:08] */
#define BCHP_XPT_WDMA_RAMS_DMQ_3_0_reserved_for_eco0_MASK          0xffffff00
#define BCHP_XPT_WDMA_RAMS_DMQ_3_0_reserved_for_eco0_SHIFT         8

/* XPT_WDMA_RAMS :: DMQ_3_0 :: WRITE_ADDRESS_HI [07:00] */
#define BCHP_XPT_WDMA_RAMS_DMQ_3_0_WRITE_ADDRESS_HI_MASK           0x000000ff
#define BCHP_XPT_WDMA_RAMS_DMQ_3_0_WRITE_ADDRESS_HI_SHIFT          0

/***************************************************************************
 *DMQ_3_1 - DMQ descriptor 3 - Write Address, lower 32 bits
 ***************************************************************************/
/* XPT_WDMA_RAMS :: DMQ_3_1 :: WRITE_ADDRESS [31:00] */
#define BCHP_XPT_WDMA_RAMS_DMQ_3_1_WRITE_ADDRESS_MASK              0xffffffff
#define BCHP_XPT_WDMA_RAMS_DMQ_3_1_WRITE_ADDRESS_SHIFT             0

/***************************************************************************
 *DMQ_3_2 - DMQ descriptor 3 - Transfer Size
 ***************************************************************************/
/* XPT_WDMA_RAMS :: DMQ_3_2 :: TXFER_SIZE [31:00] */
#define BCHP_XPT_WDMA_RAMS_DMQ_3_2_TXFER_SIZE_MASK                 0xffffffff
#define BCHP_XPT_WDMA_RAMS_DMQ_3_2_TXFER_SIZE_SHIFT                0

/***************************************************************************
 *DMQ_3_3 - DMQ descriptor 3 - Current Descriptor Address and Control
 ***************************************************************************/
/* XPT_WDMA_RAMS :: DMQ_3_3 :: CURRENT_DESC_ADDRESS [31:04] */
#define BCHP_XPT_WDMA_RAMS_DMQ_3_3_CURRENT_DESC_ADDRESS_MASK       0xfffffff0
#define BCHP_XPT_WDMA_RAMS_DMQ_3_3_CURRENT_DESC_ADDRESS_SHIFT      4

/* XPT_WDMA_RAMS :: DMQ_3_3 :: SWAP_HWORDS [03:03] */
#define BCHP_XPT_WDMA_RAMS_DMQ_3_3_SWAP_HWORDS_MASK                0x00000008
#define BCHP_XPT_WDMA_RAMS_DMQ_3_3_SWAP_HWORDS_SHIFT               3

/* XPT_WDMA_RAMS :: DMQ_3_3 :: STRAP_INVERT [02:02] */
#define BCHP_XPT_WDMA_RAMS_DMQ_3_3_STRAP_INVERT_MASK               0x00000004
#define BCHP_XPT_WDMA_RAMS_DMQ_3_3_STRAP_INVERT_SHIFT              2

/* XPT_WDMA_RAMS :: DMQ_3_3 :: INT_EN [01:01] */
#define BCHP_XPT_WDMA_RAMS_DMQ_3_3_INT_EN_MASK                     0x00000002
#define BCHP_XPT_WDMA_RAMS_DMQ_3_3_INT_EN_SHIFT                    1

/* XPT_WDMA_RAMS :: DMQ_3_3 :: LAST [00:00] */
#define BCHP_XPT_WDMA_RAMS_DMQ_3_3_LAST_MASK                       0x00000001
#define BCHP_XPT_WDMA_RAMS_DMQ_3_3_LAST_SHIFT                      0

/***************************************************************************
 *CHAN_OFFSET - This is here so we know the offset of channel 1 relative to channel 0.
 ***************************************************************************/
/* XPT_WDMA_RAMS :: CHAN_OFFSET :: reserved0 [31:00] */
#define BCHP_XPT_WDMA_RAMS_CHAN_OFFSET_reserved0_MASK              0xffffffff
#define BCHP_XPT_WDMA_RAMS_CHAN_OFFSET_reserved0_SHIFT             0

/***************************************************************************
 *RDB_MEM_RESIZER - This is here so that enough space is reserved by RDB for the actual memory, which contains 32 per-channel portions, with offsets to one another as indicated by the offset of the CHAN_OFFSET register
 ***************************************************************************/
/* XPT_WDMA_RAMS :: RDB_MEM_RESIZER :: reserved0 [31:00] */
#define BCHP_XPT_WDMA_RAMS_RDB_MEM_RESIZER_reserved0_MASK          0xffffffff
#define BCHP_XPT_WDMA_RAMS_RDB_MEM_RESIZER_reserved0_SHIFT         0

#endif /* #ifndef BCHP_XPT_WDMA_RAMS_H__ */

/* End of File */

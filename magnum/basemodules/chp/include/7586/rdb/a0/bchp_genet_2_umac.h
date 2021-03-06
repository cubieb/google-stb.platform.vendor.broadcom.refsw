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
 * Date:           Generated on               Wed Feb 11 10:13:59 2015
 *                 Full Compile MD5 Checksum  f7f4bd55341805fcfe958ba5e47e65f4
 *                     (minus title and desc)
 *                 MD5 Checksum               95b679a9655597a92593cae55222c397
 *
 * Compiled with:  RDB Utility                combo_header.pl
 *                 RDB.pm                     15653
 *                 unknown                    unknown
 *                 Perl Interpreter           5.008008
 *                 Operating System           linux
 *
 *
 ***************************************************************************/

#ifndef BCHP_GENET_2_UMAC_H__
#define BCHP_GENET_2_UMAC_H__

/***************************************************************************
 *GENET_2_UMAC
 ***************************************************************************/
#define BCHP_GENET_2_UMAC_UMAC_DUMMY             0x00ba0800 /* [RO] UniMAC Dummy Register */
#define BCHP_GENET_2_UMAC_HD_BKP_CNTL            0x00ba0804 /* [RW] UniMAC Half Duplex Backpressure Control Register */
#define BCHP_GENET_2_UMAC_CMD                    0x00ba0808 /* [RW] UniMAC Command Register */
#define BCHP_GENET_2_UMAC_MAC0                   0x00ba080c /* [RW] UniMAC MAC 0 */
#define BCHP_GENET_2_UMAC_MAC1                   0x00ba0810 /* [RW] UniMAC MAC 1 */
#define BCHP_GENET_2_UMAC_FRM_LEN                0x00ba0814 /* [RW] UniMAC Frame Length */
#define BCHP_GENET_2_UMAC_PAUSE_QUNAT            0x00ba0818 /* [RW] UniMAC Pause Quanta */
#define BCHP_GENET_2_UMAC_SFD_OFFSET             0x00ba0840 /* [RO] UniMAC EFM Preamble Length */
#define BCHP_GENET_2_UMAC_MODE                   0x00ba0844 /* [RO] UniMAC Mode */
#define BCHP_GENET_2_UMAC_FRM_TAG0               0x00ba0848 /* [RW] UniMAC Preamble Outer TAG 0 */
#define BCHP_GENET_2_UMAC_FRM_TAG1               0x00ba084c /* [RW] UniMAC Preamble Outer TAG 1 */
#define BCHP_GENET_2_UMAC_TX_IPG_LEN             0x00ba085c /* [RW] UniMAC Inter Packet Gap */
#define BCHP_GENET_2_UMAC_EEE_CTRL               0x00ba0864 /* [RW] UniMAC EEE Control */
#define BCHP_GENET_2_UMAC_EEE_LPI_TIMER          0x00ba0868 /* [RW] UniMAC EEE  LPI Timer */
#define BCHP_GENET_2_UMAC_EEE_WAKE_TIMER         0x00ba086c /* [RW] UniMAC EEE  Wake Timer */
#define BCHP_GENET_2_UMAC_EEE_REF_COUNT          0x00ba0870 /* [RW] UniMAC EEE Reference Count */
#define BCHP_GENET_2_UMAC_RX_PKT_DROP_STATUS     0x00ba0878 /* [RW] UniMAC Rx Pkt Drop Status */
#define BCHP_GENET_2_UMAC_SYMMETRIC_IDLE_THRESHOLD 0x00ba087c /* [RW] UniMAC Symmetric Idle Threshold */
#define BCHP_GENET_2_UMAC_MACSEC_PROG_TX_CRC     0x00ba0b10 /* [RW] UniMAC Programmable CRC value */
#define BCHP_GENET_2_UMAC_MACSEC_CNTRL           0x00ba0b14 /* [RW] UniMAC Misc. MACSEC Control Register */
#define BCHP_GENET_2_UMAC_TS_STATUS_CNTRL        0x00ba0b18 /* [RO] UniMAC Timestamp Status */
#define BCHP_GENET_2_UMAC_TX_TS_DATA             0x00ba0b1c /* [RO] UniMAC Timestamp Data */
#define BCHP_GENET_2_UMAC_PAUSE_CNTRL            0x00ba0b30 /* [RW] UniMAC Repetitive Pause Control in TX direction */
#define BCHP_GENET_2_UMAC_TXFIFO_FLUSH           0x00ba0b34 /* [RW] UniMAC TX Flush */
#define BCHP_GENET_2_UMAC_RXFIFO_STAT            0x00ba0b38 /* [RO] UniMAC RX FIFO Status */
#define BCHP_GENET_2_UMAC_TXFIFO_STAT            0x00ba0b3c /* [RO] UniMAC TX FIFO Status */
#define BCHP_GENET_2_UMAC_PPP_CNTRL              0x00ba0b40 /* [RW] UniMAC PPP Control */
#define BCHP_GENET_2_UMAC_PPP_REFRESH_CNTRL      0x00ba0b44 /* [RW] UniMAC Refresh Control */
#define BCHP_GENET_2_UMAC_TX_PAUSE_PREL0         0x00ba0b48 /* [RO] UniMAC TX Pause PRBL[31:0] */
#define BCHP_GENET_2_UMAC_TX_PAUSE_PREL1         0x00ba0b4c /* [RO] UniMAC TX Pause PRBL[63:32] */
#define BCHP_GENET_2_UMAC_TX_PAUSE_PREL2         0x00ba0b50 /* [RO] UniMAC TX Pause PRBL[95:64] */
#define BCHP_GENET_2_UMAC_TX_PAUSE_PREL3         0x00ba0b54 /* [RO] UniMAC TX Pause PRBL[127:96] */
#define BCHP_GENET_2_UMAC_RX_PAUSE_PREL0         0x00ba0b58 /* [RO] UniMAC RX Pause PRBL[31:0] */
#define BCHP_GENET_2_UMAC_RX_PAUSE_PREL1         0x00ba0b5c /* [RO] UniMAC RX Pause PRBL[63:32] */
#define BCHP_GENET_2_UMAC_RX_PAUSE_PREL2         0x00ba0b60 /* [RO] UniMAC RX Pause PRBL[95:64] */
#define BCHP_GENET_2_UMAC_RX_PAUSE_PREL3         0x00ba0b64 /* [RO] UniMAC RX Pause PRBL[127:96] */
#define BCHP_GENET_2_UMAC_GR64                   0x00ba0c00 /* [RW] Receive 64B Frame Counter */
#define BCHP_GENET_2_UMAC_GR127                  0x00ba0c04 /* [RW] Receive 65B to 127B Frame Counter */
#define BCHP_GENET_2_UMAC_GR255                  0x00ba0c08 /* [RW] Receive 128B to 255B Frame Counter */
#define BCHP_GENET_2_UMAC_GR511                  0x00ba0c0c /* [RW] Receive 256B to 511B Frame Counter */
#define BCHP_GENET_2_UMAC_GR1023                 0x00ba0c10 /* [RW] Receive 512B to 1023B Frame Counter */
#define BCHP_GENET_2_UMAC_GR1518                 0x00ba0c14 /* [RW] Receive 1024B to 1518B Frame Counter */
#define BCHP_GENET_2_UMAC_GRMGV                  0x00ba0c18 /* [RW] Receive 1519B to 1522B Good VLAN Frame Counter */
#define BCHP_GENET_2_UMAC_GR2047                 0x00ba0c1c /* [RW] Receive 1519B to 2047B Frame Counter */
#define BCHP_GENET_2_UMAC_GR4095                 0x00ba0c20 /* [RW] Receive 2048B to 4095B Frame Counter */
#define BCHP_GENET_2_UMAC_GR9216                 0x00ba0c24 /* [RW] Receive 4096B to 9216B Frame Counter */
#define BCHP_GENET_2_UMAC_GRPKT                  0x00ba0c28 /* [RW] Receive Packet Counter */
#define BCHP_GENET_2_UMAC_GRBYT                  0x00ba0c2c /* [RW] Receive Byte Counter */
#define BCHP_GENET_2_UMAC_GRMCA                  0x00ba0c30 /* [RW] Receive Multicast Frame Counter */
#define BCHP_GENET_2_UMAC_GRBCA                  0x00ba0c34 /* [RW] Receive Broadcast Frame Counter */
#define BCHP_GENET_2_UMAC_GRFCS                  0x00ba0c38 /* [RW] Receive FCS Error Counter */
#define BCHP_GENET_2_UMAC_GRXCF                  0x00ba0c3c /* [RW] Receive Control Frame Packet Counter */
#define BCHP_GENET_2_UMAC_GRXPF                  0x00ba0c40 /* [RW] Receive Pause Frame Packet Counter */
#define BCHP_GENET_2_UMAC_GRXUO                  0x00ba0c44 /* [RW] Receive Unknown OP Code Packet Counter */
#define BCHP_GENET_2_UMAC_GRALN                  0x00ba0c48 /* [RW] Receive Alignmenet Error Counter */
#define BCHP_GENET_2_UMAC_GRFLR                  0x00ba0c4c /* [RW] Receive Frame Length Out Of Range Counter */
#define BCHP_GENET_2_UMAC_GRCDE                  0x00ba0c50 /* [RW] Receive Code Error Packet Counter */
#define BCHP_GENET_2_UMAC_GRFCR                  0x00ba0c54 /* [RW] Receive Carrier Sense Error Packet Counter */
#define BCHP_GENET_2_UMAC_GROVR                  0x00ba0c58 /* [RW] Receive Oversize Packet Counter */
#define BCHP_GENET_2_UMAC_GRJBR                  0x00ba0c5c /* [RW] Receive Jabber Counter */
#define BCHP_GENET_2_UMAC_GRMTUE                 0x00ba0c60 /* [RW] Receive MTU Error Packet Counter */
#define BCHP_GENET_2_UMAC_GRPOK                  0x00ba0c64 /* [RW] Receive Good Packet Counter */
#define BCHP_GENET_2_UMAC_GRUC                   0x00ba0c68 /* [RW] Receive Unicast Packet Counter */
#define BCHP_GENET_2_UMAC_GRPPP                  0x00ba0c6c /* [RW] Receive PPP Packet Counter */
#define BCHP_GENET_2_UMAC_GRCRC                  0x00ba0c70 /* [RW] Receive CRC Match Packet Counter */
#define BCHP_GENET_2_UMAC_TR64                   0x00ba0c80 /* [RW] Transmit 64B Frame Counter */
#define BCHP_GENET_2_UMAC_TR127                  0x00ba0c84 /* [RW] Transmit 65B to 127B Frame Counter */
#define BCHP_GENET_2_UMAC_TR255                  0x00ba0c88 /* [RW] Transmit 128B to 255B Frame Counter */
#define BCHP_GENET_2_UMAC_TR511                  0x00ba0c8c /* [RW] Transmit 256B to 511B Frame Counter */
#define BCHP_GENET_2_UMAC_TR1023                 0x00ba0c90 /* [RW] Transmit 512B to 1023B Frame Counter */
#define BCHP_GENET_2_UMAC_TR1518                 0x00ba0c94 /* [RW] Transmit 1024B to 1518B Frame Counter */
#define BCHP_GENET_2_UMAC_TRMGV                  0x00ba0c98 /* [RW] Transmit 1519B to 1522B Good VLAN Frame Counter */
#define BCHP_GENET_2_UMAC_TR2047                 0x00ba0c9c /* [RW] Transmit 1519B to 2047B Frame Counter */
#define BCHP_GENET_2_UMAC_TR4095                 0x00ba0ca0 /* [RW] Transmit 2048B to 4095B Frame Counter */
#define BCHP_GENET_2_UMAC_TR9216                 0x00ba0ca4 /* [RW] Transmit 4096B to 9216B Frame Counter */
#define BCHP_GENET_2_UMAC_GTPKT                  0x00ba0ca8 /* [RW] Transmit Packet Counter */
#define BCHP_GENET_2_UMAC_GTMCA                  0x00ba0cac /* [RW] Transmit Multicast Packet Counter */
#define BCHP_GENET_2_UMAC_GTBCA                  0x00ba0cb0 /* [RW] Transmit Broadcast Packet Counter */
#define BCHP_GENET_2_UMAC_GTXPF                  0x00ba0cb4 /* [RW] Transmit Pause Frame Packet Counter */
#define BCHP_GENET_2_UMAC_GTXCF                  0x00ba0cb8 /* [RW] Transmit Control Frame Packet Counter */
#define BCHP_GENET_2_UMAC_GTFCS                  0x00ba0cbc /* [RW] Transmit FCS Error Counter */
#define BCHP_GENET_2_UMAC_GTOVR                  0x00ba0cc0 /* [RW] Transmit Oversize Packet Counter */
#define BCHP_GENET_2_UMAC_GTDRF                  0x00ba0cc4 /* [RW] Transmit Deferral Packet Counter */
#define BCHP_GENET_2_UMAC_GTEDF                  0x00ba0cc8 /* [RW] Transmit Excessive Deferral Packet Counter */
#define BCHP_GENET_2_UMAC_GTSCL                  0x00ba0ccc /* [RW] Transmit Single Collision Packet Counter */
#define BCHP_GENET_2_UMAC_GTMCL                  0x00ba0cd0 /* [RW] Transmit Multiple Collision Packet Counter */
#define BCHP_GENET_2_UMAC_GTLCL                  0x00ba0cd4 /* [RW] Transmit Late Collision Packet Counter */
#define BCHP_GENET_2_UMAC_GTXCL                  0x00ba0cd8 /* [RW] Transmit Excessive Collision Packet Counter */
#define BCHP_GENET_2_UMAC_GTFRG                  0x00ba0cdc /* [RW] Transmit Fragments Packet Counter */
#define BCHP_GENET_2_UMAC_GTNCL                  0x00ba0ce0 /* [RW] Transmit Total Collision Counter */
#define BCHP_GENET_2_UMAC_GTJBR                  0x00ba0ce4 /* [RW] Transmit Jabber Counter */
#define BCHP_GENET_2_UMAC_GTBYT                  0x00ba0ce8 /* [RW] Transmit Byte Counter */
#define BCHP_GENET_2_UMAC_GTPOK                  0x00ba0cec /* [RW] Transmit Good Packet Counter */
#define BCHP_GENET_2_UMAC_GTUC                   0x00ba0cf0 /* [RW] Transmit Unicast Packet Counter */
#define BCHP_GENET_2_UMAC_RRPKT                  0x00ba0d00 /* [RW] Receive RUNT Packet Counter */
#define BCHP_GENET_2_UMAC_RRUND                  0x00ba0d04 /* [RW] Receive RUNT Packet And Contain A Valid FCS */
#define BCHP_GENET_2_UMAC_RRFRG                  0x00ba0d08 /* [RW] Receive RUNT Packet And Contain Invalid FCS or Alignment Error */
#define BCHP_GENET_2_UMAC_RRBYT                  0x00ba0d0c /* [RW] Receive RUNT Packet Byte Counter */
#define BCHP_GENET_2_UMAC_MIB_CNTRL              0x00ba0d80 /* [RW] MIB Control Register */
#define BCHP_GENET_2_UMAC_BKPU_CNTRL             0x00ba0e00 /* [RW] UniMAC Backpressure Control Register */
#define BCHP_GENET_2_UMAC_RXERR_MASK             0x00ba0e04 /* [RW] UniMAC RXERR Mask Register */
#define BCHP_GENET_2_UMAC_RX_MAX_PKT_SIZE        0x00ba0e08 /* [RW] UniMAC RX MAX packet Size Register */
#define BCHP_GENET_2_UMAC_VLAN_TAG               0x00ba0e0c /* [RW] RBUF VLAN Tag Register */
#define BCHP_GENET_2_UMAC_MDIO_CMD               0x00ba0e14 /* [RW] MDIO Command Register */
#define BCHP_GENET_2_UMAC_MDIO_CFG               0x00ba0e18 /* [RW] MDIO Configuration Register */
#define BCHP_GENET_2_UMAC_MPD_CTRL               0x00ba0e20 /* [RW] Magic Packet Control Registers */
#define BCHP_GENET_2_UMAC_PSW_MS                 0x00ba0e24 /* [RW] Magic Packet Optional password byte 0 and 1 */
#define BCHP_GENET_2_UMAC_PSW_LS                 0x00ba0e28 /* [RW] Magic Packet Optional password byte 2 ~ 5 */
#define BCHP_GENET_2_UMAC_MDF_CNT                0x00ba0e38 /* [RO] MDF Discard Packet Counter */
#define BCHP_GENET_2_UMAC_DIAG_SEL               0x00ba0e4c /* [RW] Diag Select Register */
#define BCHP_GENET_2_UMAC_MDF_CNTRL              0x00ba0e50 /* [RW] MDF Control Register */
#define BCHP_GENET_2_UMAC_MDF_ADDR0              0x00ba0e54 /* [RW] MDF Address Register 0 */
#define BCHP_GENET_2_UMAC_MDF_ADDR1              0x00ba0e58 /* [RW] MDF Address Register 1 */
#define BCHP_GENET_2_UMAC_MDF_ADDR2              0x00ba0e5c /* [RW] MDF Address Register 2 */
#define BCHP_GENET_2_UMAC_MDF_ADDR3              0x00ba0e60 /* [RW] MDF Address Register 3 */
#define BCHP_GENET_2_UMAC_MDF_ADDR4              0x00ba0e64 /* [RW] MDF Address Register 4 */
#define BCHP_GENET_2_UMAC_MDF_ADDR5              0x00ba0e68 /* [RW] MDF Address Register 5 */
#define BCHP_GENET_2_UMAC_MDF_ADDR6              0x00ba0e6c /* [RW] MDF Address Register 6 */
#define BCHP_GENET_2_UMAC_MDF_ADDR7              0x00ba0e70 /* [RW] MDF Address Register 7 */
#define BCHP_GENET_2_UMAC_MDF_ADDR8              0x00ba0e74 /* [RW] MDF Address Register 8 */
#define BCHP_GENET_2_UMAC_MDF_ADDR9              0x00ba0e78 /* [RW] MDF Address Register 9 */
#define BCHP_GENET_2_UMAC_MDF_ADDR10             0x00ba0e7c /* [RW] MDF Address Register 10 */
#define BCHP_GENET_2_UMAC_MDF_ADDR11             0x00ba0e80 /* [RW] MDF Address Register 11 */
#define BCHP_GENET_2_UMAC_MDF_ADDR12             0x00ba0e84 /* [RW] MDF Address Register 12 */
#define BCHP_GENET_2_UMAC_MDF_ADDR13             0x00ba0e88 /* [RW] MDF Address Register 13 */
#define BCHP_GENET_2_UMAC_MDF_ADDR14             0x00ba0e8c /* [RW] MDF Address Register 14 */
#define BCHP_GENET_2_UMAC_MDF_ADDR15             0x00ba0e90 /* [RW] MDF Address Register 15 */
#define BCHP_GENET_2_UMAC_MDF_ADDR16             0x00ba0e94 /* [RW] MDF Address Register 16 */
#define BCHP_GENET_2_UMAC_MDF_ADDR17             0x00ba0e98 /* [RW] MDF Address Register 17 */
#define BCHP_GENET_2_UMAC_MDF_ADDR18             0x00ba0e9c /* [RW] MDF Address Register 18 */
#define BCHP_GENET_2_UMAC_MDF_ADDR19             0x00ba0ea0 /* [RW] MDF Address Register 19 */
#define BCHP_GENET_2_UMAC_MDF_ADDR20             0x00ba0ea4 /* [RW] MDF Address Register 20 */
#define BCHP_GENET_2_UMAC_MDF_ADDR21             0x00ba0ea8 /* [RW] MDF Address Register 21 */
#define BCHP_GENET_2_UMAC_MDF_ADDR22             0x00ba0eac /* [RW] MDF Address Register 22 */
#define BCHP_GENET_2_UMAC_MDF_ADDR23             0x00ba0eb0 /* [RW] MDF Address Register 23 */
#define BCHP_GENET_2_UMAC_MDF_ADDR24             0x00ba0eb4 /* [RW] MDF Address Register 24 */
#define BCHP_GENET_2_UMAC_MDF_ADDR25             0x00ba0eb8 /* [RW] MDF Address Register 25 */
#define BCHP_GENET_2_UMAC_MDF_ADDR26             0x00ba0ebc /* [RW] MDF Address Register 26 */
#define BCHP_GENET_2_UMAC_MDF_ADDR27             0x00ba0ec0 /* [RW] MDF Address Register 27 */
#define BCHP_GENET_2_UMAC_MDF_ADDR28             0x00ba0ec4 /* [RW] MDF Address Register 28 */
#define BCHP_GENET_2_UMAC_MDF_ADDR29             0x00ba0ec8 /* [RW] MDF Address Register 29 */
#define BCHP_GENET_2_UMAC_MDF_ADDR30             0x00ba0ecc /* [RW] MDF Address Register 30 */
#define BCHP_GENET_2_UMAC_MDF_ADDR31             0x00ba0ed0 /* [RW] MDF Address Register 31 */
#define BCHP_GENET_2_UMAC_MDF_ADDR32             0x00ba0ed4 /* [RW] MDF Address Register 32 */
#define BCHP_GENET_2_UMAC_MDF_ADDR33             0x00ba0ed8 /* [RW] MDF Address Register 33 */

#endif /* #ifndef BCHP_GENET_2_UMAC_H__ */

/* End of File */

#
# d11shm.tpl  make file - Geneates d11 shm files
#
# $Copyright (C) 2002-2004 Broadcom Corporation$
# <<Broadcom-WL-IPTag/Proprietary:>>
# $Id: d11shm.tpl $
# comments for M_COREMASK_xxx:
# Txcore Mask related parameters 5 locations (BPHY, OFDM, 1-streams ~ 3-Streams) for WOWL
# The base address is different than normal ucode(offset is the same), but same name
FEATURE_BEGIN[common_base]
	M_SSID
	M_PRS_FRM_BYTESZ
	M_SSID_BYTESZ
	M_PMQADDINT_THSD	# AIBSS
	M_RT_BBRSMAP_A		#Rate table offsets
	M_RT_BBRSMAP_B
	M_FIFOSIZE0			# TX fifo sizes
	M_FIFOSIZE1
	M_FIFOSIZE2
	M_FIFOSIZE3
	M_MBURST_TXOP		# max frameburst TXOP in unit of us
	M_MBURST_SIZE		# max frames in a frameburst
	M_MODE_CORE			#Phy mode setting for ucode
	M_WLCX_CONFIG		#bitmap for the feature
	M_WLCX_GPIO_CONFIG	#GPIO to be used for 5357/43235
	M_DOT11_DTIMPERIOD
	M_TIMBC_OFFSET		# TIMBC offset value: wnm
	M_CCKBOOST_ADJ
	M_EDCF_BLKS
	M_LNA_ROUT
	M_RXGAIN_HI
	M_LPFGAIN_HI
	M_CUR_TXF_INDEX
	M_COREMASK_BLK
	M_COREMASK_BPHY
	M_COREMASK_BFM
	M_COREMASK_BFM1
	M_COREMASK_BTRESP
	M_PS_MORE_DTIM_TBTT		# pm
	M_POSTDTIM0_NOSLPTIME	# pm
	M_BCMC_FID
	M_AMT_INFO_PTR
	M_PRS_MAXTIME		# Probe response related parameters
	M_PRETBTT
	M_BCN_TXTSF_OFFSET	# beacon related parameters
	M_TIMBPOS_INBEACON	# beacon related parameters
	M_AGING_THRSH		# max time waiting for medium before tx
	M_SYNTHPU_DELAY		# pre-wakeup for synthpu, default: 500
	M_PHYVER
	M_PHYTYPE
	M_MAX_ANTCNT		# antenna swap threshold
	M_MACHW_VER			# Location where the ucode expects the corerev
	M_MACHW_CAP_L		# Location where the ucode expects the MAC capabilities
	M_MACHW_CAP_H		# Location where the ucode expects the MAC capabilities
	M_SFRMTXCNTFBRTHSD	# Beacon-related parameters
	M_LFRMTXCNTFBRTHSD	# Beacon-related parameters
	M_TXDC_BYTESZ		# ACK/CTS related params
	M_TXFL_BMAP			# selectively flushing of transmit fifo's
	M_JSSI_AUX
	M_DOT11_SLOT		# stf/PS-mode related parameters
	M_DUTY_STRTRATE
	M_SECRSSI0_MIN
	M_SECRSSI1_MIN
	M_MIMO_ANTSEL_RXDFLT	#Antenna Diversity Testing
	M_MIMO_ANTSEL_TXDFLT
	M_ANTSEL_CLKDIV
	M_BOM_REV_MAJOR	# PSM SHM variable offsets
	M_BOM_REV_MINOR
	M_HOST_FLAGS	# Host flags to turn on ucode options
	M_HOST_FLAGS2	# Host flags to turn on ucode options
	M_HOST_FLAGS3	# Host flags to turn on ucode options
	M_HOST_FLAGS4	# Host flags to turn on ucode options
	M_HOST_FLAGS5	# Host flags to turn on ucode options
	M_REV_L
	M_REV_H
	M_UCODE_FEATURES
	M_ULP_STATUS
	M_EDCF_QINFO1_OFFSET
	M_MYMAC_ADDR
	M_TXFRAME_CNT
	M_RXSTRT_CNT
	M_RXCRSGLITCH_CNT
	M_BPHYGLITCH_CNT
	M_RXBADFCS_CNT
	M_RXBADPLCP_CNT
	M_RXBPHY_BADPLCP_CNT
	M_AC_TXLMT_BLK
	M_MAXRXFRM_LEN
	M_RXCORE_STATE
FEATURE_END
FEATURE_BEGIN[proxd]
IF[defined(WL_PROXDETECT)]
	M_TOF_BLK_PTR			#Block Pointer
	M_TOF_CMD_OFFSET		#command txed from fw to ucode
	M_TOF_RSP_OFFSET		#response from ucode to fw
	M_TOF_CHNSM_0_OFFSET	#Channel smoothing 0
	M_TOF_DOT11DUR_OFFSET	#802.11 reseved dur value
	M_TOF_PHYCTL0_OFFSET	#PHYCTL0 value
	M_TOF_PHYCTL1_OFFSET	#PHYCTL1 value
	M_TOF_PHYCTL2_OFFSET	#PHYCTL2 value
	M_TOF_LSIG_OFFSET		#LSIG value
	M_TOF_VHTA0_OFFSET		#VHTA0 value
	M_TOF_VHTA1_OFFSET		#VHTA1 value
	M_TOF_VHTA2_OFFSET		#VHTA2 value
	M_TOF_VHTB0_OFFSET		#VHTB0 value
	M_TOF_VHTB1_OFFSET		#VHTB1 value
	M_TOF_AMPDU_CTL_OFFSET	#AMPDU_CTL value
	M_TOF_AMPDU_DLIM_OFFSET	#AMPDU_DLIM value
	M_TOF_AMPDU_LEN_OFFSET	#AMPDU length
	M_TOF_FLAGS_OFFSET	#Flag to process FTM frames
FEATURE_END
FEATURE_BEGIN[mcnx]
	M_P2P_BLK_PTR
	M_P2P_PERBSS_BLK
	M_P2P_INTF_BLK
	M_ADDR_BMP_BLK_OFFSET
	M_P2P_INTR_BLK
	M_P2P_HPS
	M_P2P_HPS_OFFSET
	M_P2P_TSF_OFFSET_BLK
	M_P2P_GO_CHANNEL
	M_P2P_GO_IND_BMP
	M_P2P_PRETBTT_BLK
	M_P2P_TSF_DRIFT_WD0
FEATURE_END

FEATURE_BEGIN[p2p]
	M_SHM_BYT_CNT
FEATURE_END

FEATURE_BEGIN[mfgtest]
	M_MFGTEST_FRMCNT_LO	# Lower word of tx frmcnt/rx lostcnt
	M_MFGTEST_FRMCNT_HI	# Upper word of tx frmcnt/rx lostcnt
	M_MFGTEST_NUM		# PER test mode., old name: M_PKTENG_CTRL
	M_MFGTEST_IO1		# IFS for TX mode., old name: M_PKTENG_IFS
	M_RXSTATS_BLK_PTR	# PKTENG Rx Stats Block
	M_MFGTEST_UOTARXTEST
	M_MFGTEST_RXAVGPWR_ANT0
	M_MFGTEST_RXAVGPWR_ANT1
	M_MFGTEST_RXAVGPWR_ANT2
FEATURE_END

FEATURE_BEGIN[km]
	M_TKMICKEYS_PTR
	M_WAPIMICKEYS_PTR
	M_SECKEYS_PTR
	M_SECKINDX_PTR
	M_TKIP_TTAK_PTR
	M_SECKINDXALGO_BLK
	M_TKIP_TSC_TTAK
FEATURE_END

# shm location for TXBF
FEATURE_BEGIN[txbf]
	M_BFCFG_PTR
	M_BFI_REFRESH_THR_OFFSET
FEATURE_END

# macstat1 counters : corerev >= 40 only
FEATURE_BEGIN[macstat]
	M_PSM2HOST_STATS	# macstat counters
	M_PSM2HOST_EXT_PTR	# will be named in driver as M_UCODE_MACSTAT1_PTR
	M_UCODE_DBGST		# UCODE debug status
	M_BCN0_FRM_BYTESZ	# Bcn 0 template length
	M_BCN1_FRM_BYTESZ	# Bcn 1 template length
	M_DEBUGBLK_PTR
	M_TXERR_NOWRITE_OFFSET
	M_TXERR_REASON_OFFSET
	M_TXERR_CTXTST_OFFSET
	M_TXERR_PCTL0_OFFSET
	M_TXERR_PCTL1_OFFSET
	M_TXERR_PCTL2_OFFSET
	M_TXERR_LSIG0_OFFSET
	M_TXERR_LSIG1_OFFSET
	M_TXERR_PLCP0_OFFSET
	M_TXERR_PLCP1_OFFSET
	M_TXERR_PLCP2_OFFSET
	M_TXERR_SIGB0_OFFSET
	M_TXERR_SIGB1_OFFSET
	M_TXERR_RXESTATS2_OFFSET
	M_TXNDPA_CNT
	M_TXNDP_CNT
	M_TXBFPOLL_CNT
	M_TXSF_CNT
	M_TXCWRTS_CNT
	M_TXCWCTS_CNT
	M_TXBFM_CNT
	M_RXNDPAUCAST_CNT
	M_RXNDPAMCAST_CNT
	M_RXBFPOLLUCAST_CNT
	M_BFERPTRDY_CNT
	M_RXSFUCAST_CNT
	M_RXCWRTSUCAST_CNT
	M_RXCWCTSUCAST_CNT
	M_RXDROP20S_CNT
	M_RX20S_CNT
	M_MACSUSP_CNT
FEATURE_END

# MBSS shared memory address definitions; see [MultiBSSUcode] Twiki
FEATURE_BEGIN[mbssid]
	M_MBSSID_BLK
	M_MBS_BSSID0
	M_MBS_BSSID1
	M_MBS_BSSID2
	M_MBS_NBCN
	M_MBS_PRQBASE
	M_MBS_PRETBTT
	M_MBS_BSSIDNUM
	M_MBS_PIO_BCBMP
	M_MBS_PRS_TPLPTR
	M_MBS_PRSLEN_BLK
	M_MBS_BCFID_BLK
	M_MBS_SSIDLEN_BLK
	M_MBS_SSID_1
	M_PRQFIFO_RPTR
	M_PRQFIFO_WPTR
FEATURE_END

FEATURE_BEGIN[physim]
	M_RFLDO_ON_L
	M_RFLDO_ON_H
	M_PAPDOFF_MCS
	M_LPF_PASSIVE_RC_OFDM
	M_LPF_PASSIVE_RC_CCK
	M_SMPL_COL_BMP			#Trigger bitmap for sample collect
	M_SMPL_COL_CTL			#Sample collect type
	M_RT_DIRMAP_A
	M_RT_DIRMAP_B
	M_CTS_DURATION
	M_TSSI_0
	M_TSSI_1
	M_IFS_PRICRS		# see M_IFSCTL1 also
	M_TSSI_OFDM_0
	M_TSSI_OFDM_1
	M_CURCHANNEL		#Current channel number plus upper bits
	M_PWRIND_BLKS		#Index of attenuations used during ucode power control
	M_PWRIND_MAP0
	M_PWRIND_MAP1
	M_PWRIND_MAP2
	M_PWRIND_MAP3
	M_PWRIND_MAP4
	M_PWRIND_MAP5
	M_HWACI_STATUS
	M_HWACI_EN_IND
	M_FCBS_BLK
	M_FCBS_TEMPLATE_LENS
	M_FCBS_BPHY_CTRL
	M_FCBS_TEMPLATE_PTR
	M_AFEOVR_PTR		#XXX adress tone jammer WAR block
	M_RXGAININFO_ANT0_OFFSET
	M_RXAUXGAININFO_ANT0_OFFSET
FEATURE_END

FEATURE_BEGIN[ulpphysim]
	M_RADIOPWRUP_PTR
	M_RADIOPWRDWN_PTR
	M_EXT_AVAIL3
	M_HOST_FLAGS6
	M_TXPWR_MAX
	M_TXPWR_CUR
	M_BCMC_TIMEOUT				#max time waiting for BCMC in PM
	M_BCMCROLL_TMOUT			#max time waiting for BCMC MoreData=0 in PM
	M_TXPWR_M
	M_TXPWR_TARGET
	M_USEQ_PWRUP_PTR
	M_USEQ_PWRDN_PTR
	M_SLP_RDY_INT
	M_TPCNNUM_INTG_LOG2
	M_TSSI_SENS_LMT1
	M_TSSI_SENS_LMT2
FEATURE_END
FEATURE_BEGIN[btcx]
	M_BTCX_BLK_PTR
	M_BTCX_PRED_PER
	M_BTCX_LAST_SCO
	M_BTCX_LAST_SCO_H
	M_BTCX_BLE_SCAN_GRANT_THRESH
	M_BTCX_NEXT_SCO
	M_BTCX_REQ_START
	M_BTCX_REQ_START_H
	M_BTCX_LAST_DATA
	M_BTCX_BT_TYPE
	M_BTCX_LAST_A2DP
	M_BTCX_PRI_MAP_LO
	M_BTCX_HOLDSCO_LIMIT_OFFSET
	M_BTCX_SCO_GRANT_HOLD_RATIO_OFFSET
	M_BTCX_PRED_COUNT
	M_BTCX_PROT_RSSI_THRESH_OFFSET
	M_BTCX_PROT_RSSI_THRESH
	M_BTCX_HOST_FLAGS_OFFSET
	M_BTCX_HOST_FLAGS
	M_BTCX_RSSI
	M_BTCX_BT_TXPWR
	M_BTCX_HIGH_THRESH
	M_BTCX_LOW_THRESH
	M_BTCX_CONFIG_OFFSET
	M_BTCX_CONFIG
	M_BTCX_NUM_TASKS_OFFSET
	M_BTCX_NUM_TASKS
	M_BTCXDBG_BLK
	M_BTCX_RFSWMSK_BT_OFFSET
	M_BTCX_RFSWMSK_BT
	M_BTCX_RFSWMSK_WL_OFFSET
	M_BTCX_RFSWMSK_WL
	M_BTCX_AGG_OFF_BM
	M_BTCX_PKTABORTCTL_VAL
FEATURE_END

#LTECX shares BTCX shmem block
FEATURE_BEGIN[ltecx]
	M_LTECX_FLAGS
	M_LTECX_FLAGS_OFFSET
	M_LTECX_STATE_OFFSET
	M_LTECX_HOST_FLAGS_OFFSET
	M_LTECX_TX_LOOKAHEAD_DUR_OFFSET
	M_LTECX_PROT_ADV_TIME_OFFSET
	M_LTECX_WCI2_TST_LPBK_NBYTES_TX_OFFSET
	M_LTECX_WCI2_TST_LPBK_NBYTES_ERR_OFFSET
	M_LTECX_WCI2_TST_LPBK_NBYTES_RX_OFFSET
	M_LTECX_RX_REAGGR_OFFSET
	M_LTECX_ACTUALTX_DURATION_OFFSET
	M_LTECX_CRTI_MSG_OFFSET
	M_LTECX_CRTI_INTERVAL_OFFSET
	M_LTECX_CRTI_REPEATS_OFFSET
	M_LTECX_WCI2_TST_MSG_OFFSET
	M_LTECX_RXPRI_THRESH_OFFSET
	M_LTECX_MWSSCAN_BM_LO_OFFSET
	M_LTECX_MWSSCAN_BM_HI_OFFSET
	M_LTECX_PWRCP_C0_OFFSET
	M_LTECX_PWRCP_C0_FS_OFFSET
	M_LTECX_PWRCP_C0_FSANT_OFFSET
	M_LTECX_PWRCP_C1_OFFSET
	M_LTECX_PWRCP_C1_FS_OFFSET
	M_LTECX_FS_OFFSET
	M_LTECX_TXNOISE_CNT
	M_LTECX_NOISE_DELTA
FEATURE_END

FEATURE_BEGIN[ccastat]
	M_CCASTATS_PTR
	M_CCA_STATS_BLK
	M_CCA_TXDUR_L_OFFSET
	M_CCA_TXDUR_H_OFFSET
	M_CCA_INBSS_L_OFFSET
	M_CCA_INBSS_H_OFFSET
	M_CCA_OBSS_L_OFFSET
	M_CCA_OBSS_H_OFFSET
	M_CCA_NOCTG_L_OFFSET
	M_CCA_NOCTG_H_OFFSET
	M_CCA_NOPKT_L_OFFSET
	M_CCA_NOPKT_H_OFFSET
	M_MAC_SLPDUR_L_OFFSET
	M_MAC_SLPDUR_H_OFFSET
	M_CCA_TXOP_L_OFFSET
	M_CCA_TXOP_H_OFFSET
	M_CCA_GDTXDUR_L_OFFSET
	M_CCA_GDTXDUR_H_OFFSET
	M_CCA_BDTXDUR_L_OFFSET
	M_CCA_BDTXDUR_H_OFFSET
	M_CCA_TXDUR_L
	M_CCA_TXDUR_H
	M_CCA_INBSS_L
	M_CCA_INBSS_H
	M_CCA_OBSS_L
	M_CCA_OBSS_H
	M_CCA_NOCTG_L
	M_CCA_NOCTG_H
	M_CCA_NOPKT_L
	M_CCA_NOPKT_H
	M_MAC_SLPDUR_L
	M_MAC_SLPDUR_H
	M_CCA_TXOP_L
	M_CCA_TXOP_H
	M_CCA_GDTXDUR_L
	M_CCA_GDTXDUR_H
	M_CCA_BDTXDUR_L
	M_CCA_BDTXDUR_H
	M_CCA_RXPRI_LO
	M_CCA_RXPRI_HI
	M_CCA_RXSEC20_LO
	M_CCA_RXSEC20_HI
	M_CCA_RXSEC40_LO
	M_CCA_RXSEC40_HI
	M_CCA_RXSEC80_LO
	M_CCA_RXSEC80_HI
	M_CCA_SUSP_L
	M_CCA_SUSP_H
	M_SECRSSI0
	M_SECRSSI1
	M_SECRSSI2
	M_SISO_RXDUR_L
	M_SISO_RXDUR_H
	M_SISO_TXOP_L
	M_SISO_TXOP_H
	M_MIMO_RXDUR_L
	M_MIMO_RXDUR_H
	M_MIMO_TXOP_L
	M_MIMO_TXOP_H
	M_MIMO_TXDUR_1X_L
	M_MIMO_TXDUR_1X_H
	M_MIMO_TXDUR_2X_L
	M_MIMO_TXDUR_2X_H
	M_MIMO_TXDUR_3X_L
	M_MIMO_TXDUR_3X_H
	M_SISO_SIFS_L
	M_SISO_SIFS_H
	M_MIMO_SIFS_L
	M_MIMO_SIFS_H
FEATURE_END

FEATURE_BEGIN[ampdu]
	M_TXFS_PTR
	M_AMP_STATS_PTR
	M_MIMO_MAXSYM
	M_WATCHDOG_8TU
FEATURE_END

FEATURE_BEGIN[btamp]
	M_BTAMP_GAIN_DELTA	# offset to the target txpwr
FEATURE_END

# following is put for shm's present in rev > 40 but NOT present in rev < 40.
FEATURE_BEGIN[rev_ge_40]
	M_BCN_TXPCTL0
	M_BCN_TXPCTL1
	M_BCN_TXPCTL2
	M_TXDUTY_RATIOX16_CCK	# idle busy ratio to duty_cycle requirement
	M_TXDUTY_RATIOX16_OFDM	# idle busy ratio to duty_cycle requirement
FEATURE_END
# following is put for shms present in rev < 40 but NOT present in rev > 40.
# note for M_LCNXN_SWCTRL_MASK : # PR 108019: CLB bug WAR - clb_rf_sw_ctrl_mask_ctrl mask -
#	- for WLAN to defer control to BT

FEATURE_BEGIN[rev_lt_40]
	M_BCN_PCTLWD
	M_BCN_PCTL1WD
	M_SWDIV_SWCTRL_REG
	M_LCNXN_SWCTRL_MASK # see above note
	M_4324_RXTX_WAR_PTR
	M_TX_MODE_0xb0_OFFSET
	M_TX_MODE_0x14d_OFFSET
	M_TX_MODE_0xb1_OFFSET
	M_TX_MODE_0x14e_OFFSET
	M_TX_MODE_0xb4_OFFSET
	M_TX_MODE_0x151_OFFSET
	M_RX_MODE_0xb0_OFFSET
	M_RX_MODE_0x14d_OFFSET
	M_RX_MODE_0xb1_OFFSET
	M_RX_MODE_0x14e_OFFSET
	M_RX_MODE_0xb4_OFFSET
	M_RX_MODE_0x151_OFFSET
	M_CHIP_CHECK_OFFSET
	M_CTXPRS_BLK
	M_RADIO_PWR
	M_IFSCTL1	# XXX address of stored default ifs_ctl1 value. M_IFS_PRICRS for ge40
	M_TX_IDLE_BUSY_RATIO_X_16_CCK	# idle busy ratio to duty_cycle requirement
	M_TX_IDLE_BUSY_RATIO_X_16_OFDM	# idle busy ratio to duty_cycle requirement
	M_RSP_PCTLWD
FEATURE_END

FEATURE_BEGIN[bcntrim]
	M_BCNTRIM_CNT
	M_BCNTRIM_RSSI
	M_BCNTRIM_CHAN
	M_BCNTRIM_PER
	M_BCNTRIM_TIMEND
	M_BCNTRIM_TSFLMT
	M_BCNTRIM_CUR
	M_BCNTRIM_PREVLEN
	M_BCNTRIM_TIMLEN
	M_BCNTRIM_DUR
	M_BCNTRIM_RXMBSS
	M_BCNTRIM_CANTRIM
	M_BCNTRIM_LENCHG
	M_BCNTRIM_TSFDRF
	M_BCNTRIM_NOTIM
FEATURE_END

FEATURE_BEGIN[rev_sslp_lt_40]
	M_PHY_NOISE
	M_RSSI_LOCK_OFFSET
	M_RSSI_LOGNSAMPS_OFFSET
	M_RSSI_NSAMPS_OFFSET
	M_RSSI_IQEST_EN_OFFSET
	M_RSSI_BOARDATTEN_DBG_OFFSET
	M_RSSI_IQPWR_DBG_OFFSET
	M_RSSI_IQPWR_DB_DBG_OFFSET
	M_NOISE_IQPWR
	M_NOISE_IQPWR_OFFSET
	M_NOISE_IQPWR_DB_OFFSET
	M_NOISE_LOGNSAMPS
	M_NOISE_LOGNSAMPS_OFFSET
	M_NOISE_NSAMPS
	M_NOISE_NSAMPS_OFFSET
	M_NOISE_IQEST_EN_OFFSET
	M_NOISE_IQEST_PENDING
	M_NOISE_IQEST_PENDING_OFFSET
	M_RSSI_IQEST_PENDING_OFFSET
	M_NOISE_LTE_ON
	M_NOISE_LTE_IQPWR_DB_OFFSET
	M_SSLPN_RSSI_0_OFFSET
	M_SSLPN_SNR_0_logchPowAccOut_OFFSET
	M_SSLPN_SNR_0_errAccOut_OFFSET
	M_SSLPN_RSSI_1_OFFSET
	M_SSLPN_SNR_1_logchPowAccOut_OFFSET
	M_SSLPN_SNR_1_errAccOut_OFFSET
	M_SSLPN_RSSI_2_OFFSET
	M_SSLPN_SNR_2_logchPowAccOut_OFFSET
	M_SSLPN_SNR_2_errAccOut_OFFSET
	M_SSLPN_RSSI_3_OFFSET
	M_SSLPN_SNR_3_logchPowAccOut_OFFSET
	M_SSLPN_SNR_3_errAccOut_OFFSET
	M_RSSI_QDB_0_OFFSET
	M_RSSI_QDB_1_OFFSET
	M_RSSI_QDB_2_OFFSET
	M_RSSI_QDB_3_OFFSET
FEATURE_END

FEATURE_BEGIN[wowl]
	M_WOWL_TEST_CYCLE  # Time to wakeup in seconds
	M_WOWL_TMR_L       # lower TSF LSB to be passed to ucode
	M_WOWL_TMR_ML      # Lower TSF MSB to be passed to ucode
	M_KEYRC_LAST       # Last good key replay counter
	M_NETPAT_BLK_PTR   # address for location of pattern 1
	M_WOWL_GPIOSEL     #GPIO Sel for 11AC Chips
	M_NETPAT_NUM
	M_AESTABLES_PTR
	M_AID_NBIT
	M_HOST_WOWLBM
	M_GROUPKEY_UPBM   #Last rotated key index
	M_WOWL_OFFLOADCFG_PTR
	M_CTX_GTKMSG2     #Tx descriptor for offloaded templates
	M_TXPHYERR_CNT
	M_SECSUITE
	M_TSCPN_BLK
	M_WAKEEVENT_IND
	M_EAPOLMICKEY_BLK
	M_RXFRM_SRA0
	M_RXFRM_SRA1
	M_RXFRM_SRA2
	M_RXFRM_RA0
	M_RXFRM_RA1
	M_RXFRM_RA2
	M_TXPSPFRM_CNT
FEATURE_END

FEATURE_BEGIN[bcmulp]
	M_DRVR_UCODE_IF_PTR
	M_ULP_FEATURES_OFFSET
	M_DRIVER_BLOCK_OFFSET
	M_CRX_BLK          #rxstatus corr to pkt in M_RXFRM_BASE_ADDR
	M_RXFRM_BASE_ADDR  #location of Rxpkt received which caused ULP bailout
	M_SAVERESTORE_4335_BLK
	M_ILP_PER_H_OFFSET
	M_ILP_PER_L_OFFSET
	M_DRIVER_BLOCK
	M_FCBS_DS1_MAC_INIT_BLOCK_OFFSET
	M_FCBS_DS1_PHY_RADIO_BLOCK_OFFSET
	M_FCBS_DS1_RADIO_PD_BLOCK_OFFSET
	M_FCBS_DS1_EXIT_BLOCK_OFFSET
	M_FCBS_DS0_RADIO_PU_BLOCK_OFFSET
	M_FCBS_DS0_RADIO_PD_BLOCK_OFFSET
	M_ULP_WAKE_IND
	M_ILP_PER_H
	M_ILP_PER_L
	M_DS1_CTRL_SDIO_PIN
	M_DS1_CTRL_SDIO
	M_RXBEACONMBSS_CNT
	M_FRRUN_LBCN_CNT
	M_FCBS_DS0_RADIO_PU_BLOCK
	M_FCBS_DS0_RADIO_PD_BLOCK
FEATURE_END

FEATURE_BEGIN[tsync]
	M_TS_SYNC_GPIO
	M_TS_SYNC_TSF_L
	M_TS_SYNC_TSF_ML
	M_TS_SYNC_AVB_L
	M_TS_SYNC_AVB_H
	M_TS_SYNC_PMU_L
	M_TS_SYNC_PMU_H
	M_TS_SYNC_TXTSF_ML
	M_TS_SYNC_GPIOMINDLY
	M_TS_SYNC_GPIOREALDLY
FEATURE_END

# following is put for shm's present in rev >= 64
FEATURE_BEGIN[rev_ge_64]
	M_UCODE_MACSTAT
	M_UCODE_MACSTAT1_PTR
	M_SYNTHPU_DLY
	MX_PSM_SOFT_REGS
	MX_BOM_REV_MAJOR
	MX_BOM_REV_MINOR
	MX_UCODE_DATE
	MX_UCODE_TIME
	MX_UCODE_DBGST
	MX_WATCHDOG_8TU
	MX_MACHW_VER
	MX_PHYVER
	MX_PHYTYPE
	MX_HOST_FLAGS0
	MX_HOST_FLAGS1
	MX_HOST_FLAGS2
	MX_UCX2R_FLAGS
	MX_BFI_BLK_PTR
	MX_MUSND_PER
FEATURE_END

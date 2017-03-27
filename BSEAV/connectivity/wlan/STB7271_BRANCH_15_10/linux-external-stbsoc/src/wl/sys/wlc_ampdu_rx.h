/*
 * A-MPDU Rx (with extended Block Ack) related header file
 *
 * Broadcom Proprietary and Confidential. Copyright (C) 2017,
 * All Rights Reserved.
 * 
 * This is UNPUBLISHED PROPRIETARY SOURCE CODE of Broadcom;
 * the contents of this file may not be disclosed to third parties, copied
 * or duplicated in any form, in whole or in part, without the prior
 * written permission of Broadcom.
 *
 *
 * <<Broadcom-WL-IPTag/Proprietary:>>
 *
 * $Id$
*/


#ifndef _wlc_ampdu_rx_h_
#define _wlc_ampdu_rx_h_

#if defined(WL_LINKSTAT)
#include <wlc_linkstats.h>
#endif

extern ampdu_rx_info_t *wlc_ampdu_rx_attach(wlc_info_t *wlc);
extern void wlc_ampdu_rx_detach(ampdu_rx_info_t *ampdu_rx);
extern void scb_ampdu_rx_flush(ampdu_rx_info_t *ampdu_rx, struct scb *scb);

extern int wlc_ampdu_rx_set(ampdu_rx_info_t *ampdu_rx, bool on);
extern void wlc_ampdu_rx_set_bsscfg_aggr_override(ampdu_rx_info_t *ampdu_rx,
	wlc_bsscfg_t *bsscfg, int8 rxaggr);
extern void wlc_ampdu_rx_set_bsscfg_aggr(ampdu_rx_info_t *ampdu_rx, wlc_bsscfg_t *bsscfg,
	bool rxaggr, uint16 conf_TID_bmap);
extern void wlc_ampdu_shm_upd(ampdu_rx_info_t *ampdu_rx);

extern void ampdu_cleanup_tid_resp(ampdu_rx_info_t *ampdu_rx, struct scb *scb,
	uint8 tid);

extern void wlc_ampdu_recvdata(ampdu_rx_info_t *ampdu_rx, struct scb *scb, struct wlc_frminfo *f);

extern void wlc_ampdu_clear_rx_dump(ampdu_rx_info_t *ampdu_rx);
#if defined(BCMDBG) || defined(BCMDBG_DUMP) || defined(BCMDBG_AMPDU)
extern int wlc_ampdu_rx_dump(ampdu_rx_info_t *ampdu_rx, struct bcmstrbuf *b);
#if defined(EVENT_LOG_COMPILE)
extern int wlc_ampdu_rxmcs_counter_report(ampdu_rx_info_t *ampdu_rx, uint16 tag);
#ifdef ECOUNTERS
extern int wlc_ampdu_ecounter_rx_dump(ampdu_rx_info_t *ampdu_rx, uint16 tag);
#endif
#endif /* EVENT_LOG_COMPILE */
#endif 

extern int wlc_send_addba_resp(wlc_info_t *wlc, struct scb *scb, uint16 status,
	uint8 token, uint16 timeout, uint16 param_set);
extern void wlc_ampdu_recv_addba_req_resp(ampdu_rx_info_t *ampdu_rx, struct scb *scb,
	dot11_addba_req_t *addba_req, int body_len);
extern void wlc_ampdu_recv_bar(ampdu_rx_info_t *ampdu_rx, struct scb *scb, uint8 *body,
	int body_len);

#define AMPDU_RESP_NO_BAPOLICY_TIMEOUT	3	/* # of sec rcving ampdu wo bapolicy */

extern bool wlc_ampdu_rx_cap(ampdu_rx_info_t *ampdu_rx);
extern bool wlc_ampdu_rxba_enable(ampdu_rx_info_t *ampdu_rx, uint8 tid);
extern uint8 wlc_ampdu_get_rx_factor(wlc_info_t *wlc);
extern void wlc_ampdu_update_rx_factor(wlc_info_t *wlc, int vhtmode);
extern void wlc_ampdu_update_ie_param(ampdu_rx_info_t *ampdu_rx);

extern uint8 wlc_ampdu_rx_get_mpdu_density(ampdu_rx_info_t *ampdu_rx);
extern void wlc_ampdu_rx_set_mpdu_density(ampdu_rx_info_t *ampdu_rx, uint8 mpdu_density);
extern void wlc_ampdu_rx_set_ba_rx_wsize(ampdu_rx_info_t *ampdu_rx, uint8 wsize);
extern uint8 wlc_ampdu_rx_get_ba_rx_wsize(ampdu_rx_info_t *ampdu_rx);
extern uint8 wlc_ampdu_rx_get_ba_max_rx_wsize(ampdu_rx_info_t *ampdu_rx);
extern void wlc_ampdu_rx_recv_delba(ampdu_rx_info_t *ampdu_rx, struct scb *scb, uint8 tid,
	uint8 category, uint16 initiator, uint16 reason);
extern void wlc_ampdu_rx_send_delba(ampdu_rx_info_t *ampdu_rx, struct scb *scb, uint8 tid,
	uint16 initiator, uint16 reason);
extern int wlc_ampdu_rx_queued_pkts(ampdu_rx_info_t * ampdu_rx,
	struct scb * scb, int tid, uint * timestamp);
extern void wlc_ampdu_rx_dump_queued_pkts(ampdu_rx_info_t * ampdu_rx,
	struct scb * scb, int tid, struct bcmstrbuf *b);
#if defined(PKTC) || defined(PKTC_DONGLE)
extern bool wlc_ampdu_chainable(ampdu_rx_info_t *ampdu_rx, void *p, struct scb *scb,
	uint16 seq, uint16 tid);
#endif

void wlc_ampdu_update_rxcounters(ampdu_rx_info_t *ampdu_rx, uint32 ft, struct scb *scb,
	struct dot11_header *h, void *p, uint8 prio);

#ifdef WL_FRWD_REORDER
extern void *wlc_ampdu_frwd_handle_host_reorder(ampdu_rx_info_t *ampdu_rx, void *pkt, bool forward);
#endif

extern void wlc_ampdu_agg_state_update_rx_all(wlc_info_t *wlc, bool aggr);

#if defined(WL_LINKSTAT)
void wlc_ampdu_rxrates_get(ampdu_rx_info_t *ampdu_rx, wifi_rate_stat_t *rate, int i, bool vht);
#endif
extern bool wlc_scb_ampdurx_on_tid(struct scb *scb, uint8 prio);

#endif /* _wlc_ampdu_rx_h_ */

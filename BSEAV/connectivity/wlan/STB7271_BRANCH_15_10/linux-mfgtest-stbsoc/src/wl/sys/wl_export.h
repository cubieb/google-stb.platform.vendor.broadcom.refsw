/*
 * Required functions exported by the port-specific (os-dependent) driver
 * to common (os-independent) driver code.
 *
 * Copyright (C) 2017, Broadcom. All Rights Reserved.
 * 
 * Permission to use, copy, modify, and/or distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY
 * SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION
 * OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN
 * CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 *
 *
 * <<Broadcom-WL-IPTag/Open:>>
 *
 * $Id$
 */

#ifndef _wl_export_h_
#define _wl_export_h_

/* misc callbacks */
struct wl_info;
struct wl_if;
struct wlc_if;
struct wlc_event;
struct wl_timer;
struct wl_rxsts;
struct wl_txsts;
struct reorder_rxcpl_id_list;

/** wl_init() is called upon fault ('big hammer') conditions and as part of a 'wlc up' */
extern void wl_init(struct wl_info *wl);
extern uint wl_reset(struct wl_info *wl);
extern void wl_intrson(struct wl_info *wl);
extern uint32 wl_intrsoff(struct wl_info *wl);
extern void wl_intrsrestore(struct wl_info *wl, uint32 macintmask);
extern int wl_up(struct wl_info *wl);
extern void wl_down(struct wl_info *wl);
extern void wl_dump_ver(struct wl_info *wl, struct bcmstrbuf *b);
extern void wl_txflowcontrol(struct wl_info *wl, struct wl_if *wlif, bool state, int prio);
extern void wl_set_copycount_bytes(struct wl_info *wl, uint16 copycount,
	uint16 d11rxoffset);

extern bool wl_alloc_dma_resources(struct wl_info *wl, uint dmaddrwidth);

#ifdef TKO
extern void * wl_get_tko(struct wl_info *wl, struct wl_if *wlif);
#endif	/* TKO */
#ifdef ICMP
extern void * wl_get_icmp(struct wl_info *wl, struct wl_if *wlif);
#endif	/* ICMP */
/* timer functions */
extern struct wl_timer *wl_init_timer(struct wl_info *wl, void (*fn)(void* arg), void *arg,
	const char *name);
extern void wl_free_timer(struct wl_info *wl, struct wl_timer *timer);
/* Add timer guarantees the callback fn will not be called until AT LEAST ms later.  In the
 *  case of a periodic timer, this guarantee is true of consecutive callback fn invocations.
 *  As a result, the period may not average ms duration and the callbacks may "drift".
 *
 * A periodic timer must have a non-zero ms delay.
 */
extern void wl_add_timer(struct wl_info *wl, struct wl_timer *timer, uint ms, int periodic);
extern bool wl_del_timer(struct wl_info *wl, struct wl_timer *timer);

#ifdef WLATF_DONGLE
int wlfc_upd_flr_weight(struct wl_info *wl, uint8 mac_handle, uint8 tid, void* params);
int wlfc_enab_fair_fetch_scheduling(struct wl_info *wl, uint32 enab);
int wlfc_get_fair_fetch_scheduling(struct wl_info *wl, uint32 *status);
#endif /* WLATF_DONGLE */

/* data receive and interface management functions */
extern void wl_sendup(struct wl_info *wl, struct wl_if *wlif, void *p, int numpkt);
extern void wl_sendup_event(struct wl_info *wl, struct wl_if *wlif, void *pkt);
extern void wl_event(struct wl_info *wl, char *ifname, struct wlc_event *e);
extern void wl_event_sync(struct wl_info *wl, char *ifname, struct wlc_event *e);
extern void wl_event_sendup(struct wl_info *wl, const struct wlc_event *e, uint8 *data, uint32 len);

/* interface manipulation functions */
extern char *wl_ifname(struct wl_info *wl, struct wl_if *wlif);
extern struct wl_if *wl_add_if(struct wl_info *wl, struct wlc_if* wlcif, uint unit,
	struct ether_addr *remote);
extern void wl_del_if(struct wl_info *wl, struct wl_if *wlif);
/* RSDB specific interface update function */
extern void wl_update_if(struct wl_info *from_wl, struct wl_info *to_wl, struct wl_if *from_wlif,
	struct wlc_if *to_wlcif);
int wl_find_if(struct wl_if *wlif);
extern int wl_rebind_if(struct wl_if *wlif, int idx, bool rebind);

/* contexts in wlif structure. Currently following are valid */
#define IFCTX_ARPI	(1)
#define IFCTX_NDI	(2)
#define IFCTX_NETDEV	(3)
extern void *wl_get_ifctx(struct wl_info *wl, int ctx_id, struct wl_if *wlif);

/* pcie root complex operations
	op == 0: get link capability in configuration space
	op == 1: hot reset
*/
extern int wl_osl_pcie_rc(struct wl_info *wl, uint op, int param);

/* monitor mode functions */
extern void wl_monitor(struct wl_info *wl, struct wl_rxsts *rxsts, void *p);
extern void wl_set_monitor(struct wl_info *wl, int val);
#ifdef WLTXMONITOR
extern void wl_tx_monitor(struct wl_info *wl, struct wl_txsts *txsts, void *p);
#endif

#if defined(MACOSX) && defined(WL_BSSLISTSORT)
struct wlc_bss_info;
extern bool wl_sort_bsslist(struct wl_info *wl, struct wlc_bss_info **bip, uint nbip);
#else
#define wl_sort_bsslist(a, b, c) FALSE
#endif

#ifdef WL_WOWL_MEDIA
extern void wl_wowl_dngldown(struct wl_info *wl);
extern void wl_down_postwowlenab(struct wl_info *wl);
#endif

#if defined(WLVASIP)
extern uint32 wl_pcie_bar1(struct wl_info *wl, uchar** addr);
extern uint32 wl_pcie_bar2(struct wl_info *wl, uchar** addr);
#endif

#if defined(D0_COALESCING)
extern void wl_sendup_no_filter(struct wl_info *wl, struct wl_if *wlif, void *p, int numpkt);
#endif

#ifdef LINUX_CRYPTO
struct wlc_key_info;
extern int wl_tkip_miccheck(struct wl_info *wl, void *p, int hdr_len, bool group_key, int id);
extern int wl_tkip_micadd(struct wl_info *wl, void *p, int hdr_len);
extern int wl_tkip_encrypt(struct wl_info *wl, void *p, int hdr_len);
extern int wl_tkip_decrypt(struct wl_info *wl, void *p, int hdr_len, bool group_key);
extern void wl_tkip_printstats(struct wl_info *wl, bool group_key);
#ifdef BCMINTDBG
extern int wl_tkip_keydump(struct wl_info *wl, bool group);
#endif /*  BCMINTDBG */
extern int wl_tkip_keyset(struct wl_info *wl, const struct wlc_key_info *key_info,
	const uint8 *key_data, size_t key_len, const uint8 *rx_seq, size_t rx_seq_len);
#endif /* LINUX_CRYPTO */

#ifdef DONGLEBUILD
#define wl_init_timer(wl, fn, arg, name)	wl_init_timer(wl, fn, arg, NULL)
extern int wl_busioctl(struct wl_info *wl, uint32 cmd, void *buf, int len, int *used,
	int *needed, int set);
extern void wl_isucodereclaimed(uint8 *value);
extern void wl_reclaim(void);
extern void wl_reclaim_postattach(void);
extern bool wl_dngl_is_ss(struct wl_info *wl);
extern void wl_sendctl_tx(struct wl_info *wl, uint8 type, uint32 op, void *opdata);
extern void wl_flowring_ctl(struct wl_info *wl, uint32 op, void *opdata);
extern void wl_indicate_maccore_state(struct wl_info *wl, uint8 state);
extern void wl_flush_rxreorderqeue_flow(struct wl_info *wl, struct reorder_rxcpl_id_list *list);
extern uint32 wl_chain_rxcomplete_id(struct reorder_rxcpl_id_list *list, uint16 id, bool head);
extern void wl_chain_rxcompletions_amsdu(osl_t *osh, void *p, bool norxcpl);
extern void wl_timesync_add_rx_timestamp(struct wl_info *wl, void *p,
		uint32 ts_low, uint32 ts_high);
extern void wl_timesync_add_tx_timestamp(struct wl_info *wl, void *p,
		uint32 ts_low, uint32 ts_high);

#define wl_chain_rxcomplete_id_tail(a, b) wl_chain_rxcomplete_id(a, b, FALSE)
#define wl_chain_rxcomplete_id_head(a, b) wl_chain_rxcomplete_id(a, b, TRUE)
extern void wl_inform_additional_buffers(struct wl_info *wl, uint16 buf_cnts);
#else
#define wl_indicate_maccore_state(a, b) do { } while (0)
#define wl_flush_rxreorderqeue_flow(a, b) do { } while (0)
#define wl_chain_rxcomplete_id_tail(a, b) 0
#define wl_chain_rxcomplete_id_head(a, b) 0
#define wl_chain_rxcompletions_amsdu(a, b, c) do {} while (0)
#define wl_inform_additional_buffers(a, b) do { } while (0)
#endif /* DONGLEBUILD */

extern int wl_fatal_error(void * wl, int rc);

#ifdef NEED_HARD_RESET
extern int wl_powercycle(void * wl);
extern bool wl_powercycle_inprogress(void * wl);
#else
#define wl_powercycle(a)
#define wl_powercycle_inprogress(a) (0)
#endif /* NEED_HARD_RESET */

void *wl_create_fwdpkt(struct wl_info *wl, void *p, struct wl_if *wlif);

#ifdef BCMFRWDPOOLREORG
void wl_upd_frwd_resrv_bufcnt(struct wl_info *wl);
#endif /* BCMFRWDPOOLREORG */

#ifdef WL_NATOE
void wl_natoe_notify_pktc(struct wl_info *wl, uint8 action);
#endif /* WL_NATOE */

#ifdef ENABLE_CORECAPTURE
extern int wl_log_system_state(void * wl, const char * reason, bool capture);
#else
#define wl_log_system_state(a, b, c)
#endif

#define WL_DUMP_MEM_SOCRAM	1
#define WL_DUMP_MEM_UCM		2

extern void wl_dump_mem(char *addr, int len, int type);

#ifdef HEALTH_CHECK
typedef int (*wl_health_check_fn)(uint8 *buffer, uint16 length, void *context,
		int16 *bytes_written);
typedef struct health_check_info health_check_info_t;
typedef struct health_check_client_info health_check_client_info_t;

/* WL wrapper to health check APIs. */
extern health_check_client_info_t* wl_health_check_module_register(struct wl_info *wl,
	const char* name, wl_health_check_fn fn, void *context, int module_id);

extern void wl_health_check_execute(void *wl);

extern int wl_health_check_execute_clients(struct wl_info *wl,
	health_check_client_info_t** modules, uint16 num_modules);

/* Following are not implemented in dongle health check */
extern int wl_health_check_deinit(struct wl_info *wl);
extern int wl_health_check_module_unregister(struct wl_info *wl,
	health_check_client_info_t *client);
#endif /* HEALTH_CHECK */

#endif	/* _wl_export_h_ */

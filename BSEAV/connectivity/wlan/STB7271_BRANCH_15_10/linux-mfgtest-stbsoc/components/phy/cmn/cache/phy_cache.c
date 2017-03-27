/*
 * CACHE module implementation
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

#include <phy_cfg.h>
#include <typedefs.h>
#include <bcmutils.h>
#include <bcmwifi_channels.h>
#include <phy_dbg.h>
#include <phy_mem.h>
#include <phy_api.h>
#include <phy_chanmgr_notif.h>
#include "phy_cache_cfg.h"
#include <phy_type_cache.h>
#include <phy_cache_api.h>
#include <wlc_chctx_reg.h>

/* This is temporary. Need to modularize the members of calcache */
typedef struct {
	ch_calcache_t phy_calcache;
	acphy_ram_calcache_t ram_cache;
} phy_calcache_mem_t;

/* cache control entry */
typedef struct {
	chanspec_t chanspec;
	uint8 state;
	uint8 ctxid;	/* ctx id */
	uint8 *bufp;	/* storage */
} phy_cache_ctl_t;

/* state */
#define CTL_ST_USED	(1<<0)

/* module private states */
struct phy_cache_info {
	phy_info_t *pi;
	phy_type_cache_fns_t *fns;	/* PHY specific function ptrs */

	wlc_chctx_reg_t *chctx;		/* channel context management module handle */

	/* global states */
	phy_cache_cubby_id_t ccid;	/* cache cubby ID */

	/* context size */
	uint16 bufsz;

	/* cache control */
	uint8 ctl_sz;
	phy_cache_ctl_t *ctl;
};

/* module private states memory layout */
typedef struct {
	phy_cache_info_t info;
	phy_cache_ctl_t ctl[PHY_CACHE_SZ];
	phy_type_cache_fns_t fns;
} phy_cache_mem_t;


/* local function declaration */
#if defined(PHYCAL_CACHING)
static int phy_cache_chspec_notif(phy_chanmgr_notif_ctx_t *ctx, phy_chanmgr_notif_data_t *data);
static int phy_cache_restore(phy_cache_info_t *ci, chanspec_t chanspec);
static void phy_cache_free(phy_cache_info_t *ci);
#endif /* PHYCAL_CACHING */

#if defined(BCMDBG) || defined(BCMDBG_DUMP)
static int phy_cache_dump(void *ctx, struct bcmstrbuf *b);
#endif
#if defined(BCMDBG) || defined(BCMDBG_DUMP) || defined(WLTEST)
static int wlc_phydump_phycal(void *ctx, struct bcmstrbuf *b);
#endif

#if defined(PHYCAL_CACHING)
static void phy_cache_init_ctx(phy_cache_ctx_t *ctx, void *unused, uint8 *buf);
static int phy_cache_save_ctx(phy_cache_ctx_t *ctx, void *unused, uint8 *buf);
static int phy_cache_restore_ctx(phy_cache_ctx_t *ctx, void *unused, uint8 *buf);
#endif /* PHYCAL_CACHING */

//#undef PHY_TRACE
//#define PHY_TRACE(x) printf x
//#undef PHY_CAL
//#define PHY_CAL(x) printf x

/* attach/detach */
phy_cache_info_t *
BCMATTACHFN(phy_cache_attach)(phy_info_t *pi)
{
	phy_cache_info_t *info;
#if defined(PHYCAL_CACHING)
	uint16 events = (PHY_CHANMGR_NOTIF_OPCHCTX_OPEN | PHY_CHANMGR_NOTIF_OPCHCTX_CLOSE |
	                 PHY_CHANMGR_NOTIF_OPCH_CHG);
#endif /* PHYCAL_CACHING */

	PHY_TRACE(("%s\n", "phy_cache_attach"));

	/* allocate attach info storage */
	if ((info = phy_malloc(pi, sizeof(phy_cache_mem_t))) == NULL) {
		PHY_ERROR(("%s: phy_malloc failed\n", __FUNCTION__));
		goto fail;
	}
	info->pi = pi;

	info->ctl = ((phy_cache_mem_t *)info)->ctl;
	info->ctl_sz = PHY_CACHE_SZ;

	info->fns = &((phy_cache_mem_t *)info)->fns;

#ifdef PHYCAL_CACHING
	if ((info->chctx = wlc_chctx_reg_attach(pi->sh->osh, 0, WLC_CHCTX_REG_V_TYPE,
			PHY_CACHE_REG_SZ, PHY_CACHE_REG_SZ, PHY_CACHE_SZ)) == NULL) {
		PHY_ERROR(("%s: wlc_chctx_reg_attach failed\n", __FUNCTION__));
		goto fail;
	}

	/* Reserve some space in cache: This is temporary.
	 * We need to modularize the members of calcache to use the new calmgr.
	 * It is Important to note that this cache cubby is reserved first.
	 * The offset 0 is thus used to index into the buffer for calcache.
	 */
	if (phy_cache_reserve_cubby(info, phy_cache_init_ctx,
	                phy_cache_save_ctx, phy_cache_restore_ctx, NULL, info,
	                sizeof(phy_calcache_mem_t), &info->ccid) != BCME_OK) {
		PHY_ERROR(("%s: phy_cache_reserve_cubby failed\n", __FUNCTION__));
		goto fail;
	}

	/* register chspec notification callback */
	if (phy_chanmgr_notif_add_interest(pi->chanmgr_notifi,
	                phy_cache_chspec_notif, info, PHY_CHANMGR_NOTIF_ORDER_CACHE,
	                events) != BCME_OK) {
		PHY_ERROR(("%s: phy_chanmgr_notif_add_interest failed\n", __FUNCTION__));
		goto fail;
	}
#endif /* PHYCAL_CACHING */

#if defined(BCMDBG) || defined(BCMDBG_DUMP)
	/* register dump callback */
	phy_dbg_add_dump_fn(pi, "phycache", phy_cache_dump, info);
#endif
#if defined(BCMDBG) || defined(BCMDBG_DUMP) || defined(WLTEST)
	phy_dbg_add_dump_fn(pi, "phycal", wlc_phydump_phycal, info);
#endif

	return info;

	/* error */
fail:
	phy_cache_detach(info);
	return NULL;
}

void
BCMATTACHFN(phy_cache_detach)(phy_cache_info_t *info)
{
	phy_info_t *pi;

	PHY_TRACE(("%s\n", "phy_cache_detach"));

	if (info == NULL) {
		PHY_INFORM(("%s: null cache module\n", __FUNCTION__));
		return;
	}

	pi = info->pi;

#ifdef PHYCAL_CACHING
	/* free cache entries */
	phy_cache_free(info);

	if (info->chctx != NULL) {
		wlc_chctx_reg_detach(info->chctx);
	}
#endif

	phy_mfree(pi, info, sizeof(phy_cache_mem_t));
}

/* register phy type specific implementations */
int
BCMATTACHFN(phy_cache_register_impl)(phy_cache_info_t *ci, phy_type_cache_fns_t *fns)
{
	PHY_TRACE(("%s\n", "phy_cache_register_impl"));


	*ci->fns = *fns;
	return BCME_OK;
}

void
BCMATTACHFN(phy_cache_unregister_impl)(phy_cache_info_t *ci)
{
	PHY_TRACE(("%s\n", "phy_cache_unregister_impl"));
}

#ifdef PHYCAL_CACHING
/*
 * Reserve cubby in cache entry and register operation callbacks for the cubby.
 */
int
BCMATTACHFN(phy_cache_reserve_cubby)(phy_cache_info_t *ci, phy_cache_init_fn_t init,
	phy_cache_save_fn_t save, phy_cache_restore_fn_t restore, phy_cache_dump_fn_t dump,
	phy_cache_ctx_t *ctx, uint16 size, phy_cache_cubby_id_t *ccid)
{
	wlc_chctx_client_fn_t fns;
	int clntid;
	int cid;
	int err;

	PHY_TRACE(("%s: size %u\n", "phy_cache_reserve_cubby", size));

	fns.init = init;
	fns.save = save;
	fns.restore = restore;
	fns.dump = dump;

	if ((clntid = wlc_chctx_reg_add_client(ci->chctx, &fns, ctx)) < 0) {
		PHY_ERROR(("%s: wlc_chctx_reg_add_client failed %d\n", __FUNCTION__, clntid));
		err = clntid;
		goto fail;
	}
	if ((cid = wlc_chctx_reg_add_cubby(ci->chctx, clntid, NULL, size, NULL)) < 0) {
		PHY_ERROR(("%s: wlc_chctx_reg_add_cubby failed %d\n", __FUNCTION__, cid));
		err = cid;
		goto fail;
	}

	/* sanity check */
	ASSERT(init != NULL);
	/* ASSERT(save != NULL); Is this reqd? */
	ASSERT(restore != NULL);
	ASSERT(size > 0);

	/* account for the size and round it up to the next pointer */
	ci->bufsz += ROUNDUP(size, sizeof(void *));

	/* use the registry index as the cubby ID */
	*ccid = (phy_cache_cubby_id_t)cid;

	return BCME_OK;

fail:
	return err;
}

/* Find the control struct index (same as cache entry index) for 'chanspec' */
static int
phy_cache_find_ctl(phy_cache_info_t *ci, chanspec_t chanspec)
{
	int ctl;

	/* TODO: change to some faster search when necessary */

	for (ctl = 0; ctl < (int)ci->ctl_sz; ctl ++) {
		if ((ci->ctl[ctl].state & CTL_ST_USED) &&
		    wf_chspec_coexist(ci->ctl[ctl].chanspec, chanspec)) {
			return ctl;
		}
	}

	return BCME_NOTFOUND;
}

/*
 * Save the client states through the registered 'save' callbacks.
 */
static int
_phy_cache_save(phy_cache_info_t *ci)
{
	wlc_chctx_notif_t notif;

	PHY_TRACE(("_phy_cache_save:\n"));

	notif.event = WLC_CHCTX_LEAVE_CHAN;
	notif.chanspec = 0;

	return wlc_chctx_reg_notif(ci->chctx, &notif);
}

/*
 * Create a cache entry for the 'chanspec' if one doesn't exist.
 */
static int
phy_cache_add_entry(phy_cache_info_t *ci, chanspec_t chanspec)
{
	phy_info_t *pi = ci->pi;
	int ctl;
	int ctxid;
	wlc_chctx_notif_t notif;

	PHY_CAL(("phy_cache_add_entry: chanspec 0x%x, curr 0x%x, num %d\n", chanspec,
		pi->radio_chanspec, pi->phy_calcache_num));

	if ((ctl = phy_cache_find_ctl(ci, chanspec)) >= 0) {
		ASSERT(ci->ctl[ctl].bufp != NULL);
		return BCME_OK;
	}

	/* TODO: change to some faster search when necessary */

	/* find an empty entry */
	for (ctl = 0; ctl < (int)ci->ctl_sz; ctl ++) {
		if (ci->ctl[ctl].state & CTL_ST_USED)
			continue;
		goto init;
	}
	PHY_ERROR(("No cache available\n"));
	ASSERT(0);

	return BCME_NORESOURCE;

init:
	ASSERT(ctl >= 0 && ctl < (int)ci->ctl_sz);

	/* phy_malloc_fatal() never returns if fail */
	ci->ctl[ctl].bufp = phy_malloc_fatal(pi, ci->bufsz);
	ASSERT(ci->ctl[ctl].bufp != NULL);

	if ((ctxid =
	     wlc_chctx_reg_add_entry(ci->chctx, chanspec, ci->ctl[ctl].bufp, ci->bufsz)) < 0) {
		PHY_ERROR(("%s: wlc_chctx_reg_add_entry failed\n", __FUNCTION__));
		phy_mfree(pi, ci->ctl[ctl].bufp, ci->bufsz);
		ci->ctl[ctl].bufp = NULL;
		return ctxid;
	}
	ci->ctl[ctl].ctxid = (uint8)ctxid;
	ci->ctl[ctl].chanspec = chanspec;
	ci->ctl[ctl].state |= CTL_ST_USED;

	pi->phy_calcache_num++; /* Could be moved to cache info */

	notif.event = WLC_CHCTX_OPEN_CHAN;
	notif.chanspec = chanspec;

	wlc_chctx_reg_notif(ci->chctx, &notif);

	if (chanspec == pi->radio_chanspec) {
		/* Take care of condition where cache is created after channel switch */
		phy_cache_restore(ci, chanspec);
	}

	PHY_INFORM(("wl%d: %s ctx %d created for Ch %d\n",
		PI_INSTANCE(pi), __FUNCTION__,
		pi->phy_calcache_num,
		CHSPEC_CHANNEL(chanspec)));

	return BCME_OK;
}

/*
 * Delete the cache entry for 'chanspec' if one exists.
 */
static int
phy_cache_del_entry(phy_cache_info_t *ci, chanspec_t chanspec)
{
	phy_info_t *pi = ci->pi;
	int ctl;
	wlc_chctx_notif_t notif;

	PHY_CAL(("phy_cache_del_entry: chanspec 0x%x, curr 0x%x, num %d\n", chanspec,
		pi->radio_chanspec, pi->phy_calcache_num));

	if ((ctl = phy_cache_find_ctl(ci, chanspec)) < 0) {
		PHY_TRACE(("Cache Not Found for chanspec 0x%x\n", chanspec));
		return ctl;
	}
	ASSERT(ci->ctl[ctl].bufp != NULL);

	if (chanspec == pi->radio_chanspec) {
		_phy_cache_save(ci);
	}

	notif.event = WLC_CHCTX_CLOSE_CHAN;
	notif.chanspec = chanspec;

	wlc_chctx_reg_notif(ci->chctx, &notif);

	wlc_chctx_reg_del_entry(ci->chctx, ci->ctl[ctl].ctxid);

	phy_mfree(pi, ci->ctl[ctl].bufp, ci->bufsz);
	pi->phy_calcache_num--;

	bzero(&ci->ctl[ctl], sizeof(ci->ctl[ctl]));

	return BCME_OK;
}

/*
 * Set the cache entry associated with 'chanspec' as the current and
 * restore client states through the registered 'restore' callbacks.
 */
static int
phy_cache_restore(phy_cache_info_t *ci, chanspec_t chanspec)
{
	wlc_chctx_notif_t notif;

	PHY_TRACE(("phy_cache_restore: 0x%x Current: 0x%x\n", chanspec,
		ci->pi->radio_chanspec));

	notif.event = WLC_CHCTX_ENTER_CHAN;
	notif.chanspec = chanspec;

	return wlc_chctx_reg_notif(ci->chctx, &notif);
}

/* init cache states */
static void
phy_cache_init_ctx(phy_cache_ctx_t *ctx, void *unused, uint8 *buf)
{
	phy_cache_info_t *ci = (phy_cache_info_t *)ctx;
	phy_info_t *pi = ci->pi;

	phy_calcache_mem_t *cache_mem = (phy_calcache_mem_t *) buf;
	ch_calcache_t *cache = &(cache_mem->phy_calcache);

	PHY_CAL(("phy_cache_init_ctx\n"));

	/* Initialize ram cache pointer */
	cache->u_ram_cache.acphy_ram_calcache = &(cache_mem->ram_cache);

	cache->creation_time = pi->sh->now;
	cache->cal_info.last_cal_temp = -50;
	cache->cal_info.txcal_numcmds = pi->def_cal_info->txcal_numcmds;
	cache->in_use = TRUE;

	pi->cal_info = &(((ch_calcache_t *) buf)->cal_info);
}

static int
phy_cache_save_ctx(phy_cache_ctx_t *ctx, void *unused, uint8 *buf)
{
	phy_cache_info_t *ci = (phy_cache_info_t *)ctx;
	phy_info_t *pi = ci->pi;

	PHY_CAL(("phy_cache_save_ctx\n"));

	pi->cal_info = pi->def_cal_info;
	/* De-initialize cache pointer */

	return BCME_OK;
}

static int
phy_cache_restore_ctx(phy_cache_ctx_t *ctx, void *unused, uint8 *buf)
{
	phy_cache_info_t *ci = (phy_cache_info_t *)ctx;
	phy_info_t *pi = ci->pi;

	PHY_CAL(("phy_cache_restore_ctx: phy_cache_restore_cal\n"));

	/* we're on a channel we don't know about */
	if (buf == NULL) {
		pi->cal_info = pi->def_cal_info;
		return BCME_OK;
	}

	/* Retrieve the multi-phase info from the context */
	pi->cal_info = &(((ch_calcache_t *) buf)->cal_info);

	/* Switched the context so restart a pending MPHASE cal, else clear the state */
	if (phy_cache_restore_cal(pi) == BCME_ERROR) {
		PHY_CAL(("%s cal cache restore on chanspec 0x%x Failed\n",
			__FUNCTION__, pi->radio_chanspec));
	}

	return BCME_OK;
}

/* chspec notification callback */
static int
phy_cache_chspec_notif(phy_chanmgr_notif_ctx_t *ctx, phy_chanmgr_notif_data_t *data)
{
	phy_cache_info_t *ci = (phy_cache_info_t *)ctx;
	int status;

	PHY_TRACE(("%s: event = %d chanspec = 0x%x\n", "phy_cache_chspec_notif",
	           data->event, data->new));

	if (wf_chspec_malformed(data->new)) {
		return BCME_BADARG;
	}

	switch (data->event) {
	case PHY_CHANMGR_NOTIF_OPCHCTX_OPEN:
		status = phy_cache_add_entry(ci, data->new);
		break;
	case PHY_CHANMGR_NOTIF_OPCHCTX_CLOSE:
		status = phy_cache_del_entry(ci, data->new);
		break;
	case PHY_CHANMGR_NOTIF_OPCH_CHG:
		status = phy_cache_restore(ci, data->new);
		break;
	default:
		status = BCME_ERROR;
		ASSERT(0);
		break;
	}

	return status;
}

static void
phy_cache_free(phy_cache_info_t *ci)
{
	uint i;

	PHY_TRACE(("%s\n", __FUNCTION__));

	if (ci == NULL) {
		PHY_INFORM(("%s: null cache module\n", __FUNCTION__));
		return;
	}

	/* free cache entries */
	for (i = 0; i < ci->ctl_sz; i ++) {
		if (ci->ctl[i].state & CTL_ST_USED) {
			phy_cache_del_entry(ci, ci->ctl[i].chanspec);
		}
	}
}
#endif /* PHYCAL_CACHING */

#if defined(BCMDBG) || defined(BCMDBG_DUMP)
static int
phy_cache_dump(void *ctx, struct bcmstrbuf *b)
{
	phy_cache_info_t *ci = (phy_cache_info_t *)ctx;
	uint i;

	bcm_bprintf(b, "bufsz %u\n", ci->bufsz);

	bcm_bprintf(b, "ctl: sz %u\n", ci->ctl_sz);
	for (i = 0; i < ci->ctl_sz; i ++) {
		bcm_bprintf(b, "  idx %u: state 0x%x chan %u buf %p\n",
		            i, ci->ctl[i].state, ci->ctl[i].chanspec, ci->ctl[i].bufp);
	}

	return wlc_chctx_reg_dump(ci->chctx, b);
}
#endif /* BCMDBG || BCMDBG_DUMP */

#if defined(PHYCAL_CACHING)
int
wlc_phy_cal_cache_init(wlc_phy_t *ppi)
{
	return 0;
}

void
wlc_phy_cal_cache_deinit(wlc_phy_t *ppi)
{
	phy_info_t *pi = (phy_info_t *)ppi;

	phy_cache_free(pi->cachei);

	/* No more per-channel contexts, switch in the default one */
	pi->cal_info = pi->def_cal_info;
	ASSERT(pi->cal_info != NULL);
	if (pi->cal_info != NULL) {
		/* Reset the parameters */
		pi->cal_info->last_cal_temp = -50;
		pi->cal_info->last_cal_time = 0;
		pi->cal_info->last_temp_cal_time = 0;
	}
}

void
wlc_phy_cal_cache_set(wlc_phy_t *ppi, bool state)
{
	phy_info_t *pi = (phy_info_t *)ppi;
	pi->phy_calcache_on = state;
	if (!state)
		wlc_phy_cal_cache_deinit(ppi);
}

bool
wlc_phy_cal_cache_get(wlc_phy_t *ppi)
{
	phy_info_t *pi = (phy_info_t *)ppi;
	return pi->phy_calcache_on;
}

void
phy_cache_cal(phy_info_t *pi)
{
	phy_type_cache_fns_t * fns = pi->cachei->fns;
	phy_type_cache_ctx_t * cache_ctx = (phy_type_cache_ctx_t *)pi;

	ASSERT(pi != NULL);

	if (fns->cal_cache != NULL) {
		fns->cal_cache(cache_ctx);
	}
}

int
phy_cache_restore_cal(phy_info_t *pi)
{
	phy_type_cache_fns_t *fns = pi->cachei->fns;
	phy_type_cache_ctx_t * cache_ctx = (phy_type_cache_ctx_t *)pi;

	ASSERT(pi != NULL);

	/* TODO: Implement other phy types after ac_phy */
	if (fns->restore != NULL) {
		return fns->restore(cache_ctx);
	}
	else
		return BCME_UNSUPPORTED;
}

#if defined(BCMDBG) || defined(WLTEST)
static void
wlc_phydump_chanctx(phy_info_t *phi, struct bcmstrbuf *b)
{
	phy_cache_info_t * cachei = phi->cachei;
	phy_type_cache_fns_t *fns = cachei->fns;
	phy_type_cache_ctx_t * cache_ctx = (phy_type_cache_ctx_t *)phi;
	int ctl;

	ASSERT(phi != NULL);

	if (phi->HW_FCBS) {
		return;
	}

	bcm_bprintf(b, "Current chanspec: 0x%x\n", phi->radio_chanspec);

	for (ctl = 0; ctl < (int)cachei->ctl_sz; ctl ++) {
		if (cachei->ctl[ctl].state & CTL_ST_USED) {
			if (fns->dump_chanctx != NULL) {
				fns->dump_chanctx(cache_ctx,
					(ch_calcache_t *) cachei->ctl[ctl].bufp, b);
			}
		}
	}
}
#endif /* BCMDBG || WLTEST */
#endif /* PHYCAL_CACHING */

#if defined(BCMDBG) || defined(BCMDBG_DUMP) || defined(WLTEST)
static int
wlc_phydump_phycal(void *ctx, struct bcmstrbuf *b)
{
	phy_cache_info_t *cachei = (phy_cache_info_t *)ctx;
	phy_info_t *pi = cachei->pi;
	phy_type_cache_fns_t *fns = cachei->fns;
	phy_type_cache_ctx_t * cache_ctx = (phy_type_cache_ctx_t *)pi;

	ASSERT(pi != NULL);

	if (!pi->sh->up)
		return BCME_NOTUP;

	if (fns->dump_cal != NULL) {
		fns->dump_cal(cache_ctx, b);
	}
	else
		return BCME_UNSUPPORTED;

#if defined(PHYCAL_CACHING) && (defined(BCMDBG) || defined(WLTEST))
	wlc_phydump_chanctx(pi, b);
#endif /* defined(PHYCAL_CACHING) && (defined(BCMDBG) || defined(WLTEST)) */

	return BCME_OK;
}
#endif /* defined(BCMDBG) || defined(BCMDBG_DUMP) || defined(WLTEST) */

#if defined(PHYCAL_CACHING)
int
wlc_phy_invalidate_chanctx(wlc_phy_t *ppi, chanspec_t chanspec)
{
	phy_info_t *pi = (phy_info_t *)ppi;
	int ctl;
	phy_cache_info_t *ci = pi->cachei;

	if ((ctl = phy_cache_find_ctl(ci, chanspec)) >= 0) {
		ch_calcache_t *ctx = (ch_calcache_t *) ci->ctl[ctl].bufp;
		ctx->valid = FALSE;
		ctx->cal_info.last_cal_time = 0;
		ctx->cal_info.last_cal_temp = -50;
		ctx->cal_info.last_temp_cal_time = 0;
	}
	return 0;
}

/*   This function will try and reuse the existing ctx:
	return 0 --> couldn't find any ctx
	return 1 --> channel ctx exist
	return 2 --> grabbed an invalid ctx // No longer valid
*/
int
wlc_phy_reuse_chanctx(wlc_phy_t *ppi, chanspec_t chanspec)
{
	phy_info_t *pi = (phy_info_t *)ppi;

	PHY_CAL(("wlc_phy_reuse_chanctx: wlc_phy_get_chanctx\n"));

	/* Check for existing */
	if (wlc_phy_get_chanctx(pi, chanspec)) {
		PHY_INFORM(("wl%d: %s | using existing chanctx for Ch %d\n",
			PI_INSTANCE(pi), __FUNCTION__,
			CHSPEC_CHANNEL(chanspec)));
		return 1;
	}

	PHY_INFORM(("wl%d: %s | couldn't find any ctx for Ch %d\n",
		PI_INSTANCE(pi), __FUNCTION__,
		CHSPEC_CHANNEL(chanspec)));

	return BCME_OK;
}

void
wlc_phy_update_chctx_glacial_time(wlc_phy_t *ppi, chanspec_t chanspec)
{
	ch_calcache_t *ctx;
	phy_info_t *pi = (phy_info_t *)ppi;

	PHY_CAL(("wlc_phy_update_chctx_glacial_time: wlc_phy_get_chanctx\n"));

	if ((ctx = wlc_phy_get_chanctx((phy_info_t *)ppi, chanspec)))
		ctx->cal_info.last_cal_time = pi->sh->now - pi->sh->glacial_timer;
}

ch_calcache_t *
wlc_phy_get_chanctx(phy_info_t *pi, chanspec_t chanspec)
{
	phy_cache_info_t *ci = pi->cachei;
	int ctl = phy_cache_find_ctl(ci, chanspec);

	PHY_TRACE(("wlc_phy_get_chanctx: 0x%x, Current 0x%x\n",
		chanspec, pi->radio_chanspec));

	if (ctl >= 0) {
		/* We require non-current access for updating glacial timer */
		/* It is Important to note that this cache cubby is reserved first.
		 * The offset 0 is thus used to index into the buffer for calcache.
		 */
		return (ch_calcache_t *) ci->ctl[ctl].bufp;
	} else {
		return NULL;
	}

}

void
wlc_phy_get_all_cached_ctx(wlc_phy_t *ppi, chanspec_t *chanlist)
{
	phy_info_t *pi = (phy_info_t *)ppi;
	phy_cache_info_t *ci = pi->cachei;
	int ctl;
	int i = 0;

	/* TODO: change to some faster search when necessary */

	for (ctl = 0; ctl < (int)ci->ctl_sz; ctl ++) {
		if (ci->ctl[ctl].state & CTL_ST_USED) {
			*(chanlist+i) = ci->ctl[ctl].chanspec;
			i ++;
		}
	}
}

uint32
wlc_phy_get_current_cachedchans(wlc_phy_t *ppi)
{
	phy_info_t *pi = (phy_info_t *)ppi;
	if (pi) {
#if defined(PHYCAL_CACHING)|| defined(WL_MODESW)
		return pi->phy_calcache_num;
#endif
	}
	return 0;
}

#endif /* PHYCAL_CACHING */

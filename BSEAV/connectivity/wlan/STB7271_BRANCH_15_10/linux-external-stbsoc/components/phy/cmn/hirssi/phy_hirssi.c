/*
 * HiRSSI eLNA Bypass module implementation.
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
#include <bcmdefs.h>
#include <bcmutils.h>
#include <phy_dbg.h>
#include <phy_mem.h>
#include <phy_type_hirssi.h>
#include <phy_hirssi.h>

/* module private states */
struct phy_hirssi_info {
	phy_info_t *pi;
	phy_type_hirssi_fns_t *fns;
};

/* module private states memory layout */
typedef struct {
	phy_hirssi_info_t info;
	phy_type_hirssi_fns_t fns;
/* add other variable size variables here at the end */
} phy_hirssi_mem_t;

/* local function declaration */
static int phy_hirssi_init(phy_init_ctx_t *ctx);

/* attach/detach */
phy_hirssi_info_t *
BCMATTACHFN(phy_hirssi_attach)(phy_info_t *pi)
{
	phy_hirssi_info_t *info;

	PHY_TRACE(("%s\n", __FUNCTION__));

	/* allocate attach info storage */
	if ((info = phy_malloc(pi, sizeof(phy_hirssi_mem_t))) == NULL) {
		PHY_ERROR(("%s: phy_malloc failed\n", __FUNCTION__));
		goto fail;
	}
	info->pi = pi;
	info->fns = &((phy_hirssi_mem_t *)info)->fns;

	/* register init fn */

	/* Register callbacks */

	/* register init fn */
	if (phy_init_add_init_fn(pi->initi, phy_hirssi_init, info, PHY_INIT_HIRSSI) != BCME_OK) {
		PHY_ERROR(("%s: phy_init_add_init_fn failed\n", __FUNCTION__));
		goto fail;
	}

	return info;

	/* error */
fail:
	phy_hirssi_detach(info);
	return NULL;
}

void
BCMATTACHFN(phy_hirssi_detach)(phy_hirssi_info_t *info)
{
	phy_info_t *pi;

	PHY_TRACE(("%s\n", __FUNCTION__));

	if (info == NULL) {
		PHY_INFORM(("%s: null hirssi module\n", __FUNCTION__));
		return;
	}

	pi = info->pi;

	phy_mfree(pi, info, sizeof(phy_hirssi_mem_t));
}

/* register phy type specific implementations */
int
BCMATTACHFN(phy_hirssi_register_impl)(phy_hirssi_info_t *hri, phy_type_hirssi_fns_t *fns)
{

	PHY_TRACE(("%s\n", __FUNCTION__));

	*hri->fns = *fns;

	return BCME_OK;
}

void
BCMATTACHFN(phy_hirssi_unregister_impl)(phy_hirssi_info_t *hri)
{
	PHY_TRACE(("%s\n", __FUNCTION__));
}

/* High Received Signal Strength Indicator eLow Noise Amplifier Bypass Initialization */
static int
WLBANDINITFN(phy_hirssi_init)(phy_init_ctx_t *ctx)
{
	phy_hirssi_info_t *hirssii = (phy_hirssi_info_t *)ctx;
	phy_type_hirssi_fns_t *fns = hirssii->fns;

	PHY_TRACE(("%s\n", __FUNCTION__));

	if (fns->init_hirssi != NULL) {
		return (fns->init_hirssi)(fns->ctx);
	}
	return BCME_OK;
}

int
phy_hirssi_get_period(phy_info_t *pi, int32 *period)
{
	phy_type_hirssi_fns_t *fns = pi->hirssii->fns;
	int err = BCME_UNSUPPORTED;
	PHY_TRACE(("%s\n", __FUNCTION__));
	if (fns->getperiod != NULL) {
		err = (fns->getperiod)(fns->ctx, period);
	}
	return err;
}

int
phy_hirssi_set_period(phy_info_t *pi, int32 period)
{
	phy_type_hirssi_fns_t *fns = pi->hirssii->fns;
	int err = BCME_UNSUPPORTED;
	PHY_TRACE(("%s\n", __FUNCTION__));
	if (fns->setperiod != NULL) {
		err = (fns->setperiod)(fns->ctx, period);
	}
	return err;
}

int
phy_hirssi_get_en(phy_info_t *pi, int32 *enable)
{
	phy_type_hirssi_fns_t *fns = pi->hirssii->fns;
	int err = BCME_UNSUPPORTED;
	PHY_TRACE(("%s\n", __FUNCTION__));
	if (fns->geten != NULL) {
		err = (fns->geten)(fns->ctx, enable);
	}
	return err;
}

int
phy_hirssi_set_en(phy_info_t *pi, int32 enable)
{
	phy_type_hirssi_fns_t *fns = pi->hirssii->fns;
	int err = BCME_UNSUPPORTED;
	PHY_TRACE(("%s\n", __FUNCTION__));
	if (fns->seten != NULL) {
		err = (fns->seten)(fns->ctx, enable);
	}
	return err;
}

int
phy_hirssi_get_rssi(phy_info_t *pi, int32 *rssi, phy_hirssi_t opt)
{
	phy_type_hirssi_fns_t *fns = pi->hirssii->fns;
	int err = BCME_UNSUPPORTED;
	PHY_TRACE(("%s_%s\n", __FUNCTION__, opt == PHY_HIRSSI_BYP ? "byp" : "res"));
	if (fns->getrssi != NULL) {
		err = (fns->getrssi)(fns->ctx, rssi, opt);
	}
	return err;
}

int
phy_hirssi_set_rssi(phy_info_t *pi, int32 rssi, phy_hirssi_t opt)
{
	phy_type_hirssi_fns_t *fns = pi->hirssii->fns;
	int err = BCME_UNSUPPORTED;
	PHY_TRACE(("%s_%s\n", __FUNCTION__, opt == PHY_HIRSSI_BYP ? "byp" : "res"));
	if (fns->setrssi != NULL) {
		err = (fns->setrssi)(fns->ctx, rssi, opt);
	}
	return err;
}

int
phy_hirssi_get_cnt(phy_info_t *pi, int32 *cnt, phy_hirssi_t opt)
{
	phy_type_hirssi_fns_t *fns = pi->hirssii->fns;
	int err = BCME_UNSUPPORTED;
	PHY_TRACE(("%s_%s\n", __FUNCTION__, opt == PHY_HIRSSI_BYP ? "byp" : "res"));
	if (fns->getcnt != NULL) {
		err = (fns->getcnt)(fns->ctx, cnt, opt);
	}
	return err;
}

int
phy_hirssi_set_cnt(phy_info_t *pi, int32 cnt, phy_hirssi_t opt)
{
	phy_type_hirssi_fns_t *fns = pi->hirssii->fns;
	int err = BCME_UNSUPPORTED;
	PHY_TRACE(("%s_%s\n", __FUNCTION__, opt == PHY_HIRSSI_BYP ? "byp" : "res"));
	if (fns->setcnt != NULL) {
		err = (fns->setcnt)(fns->ctx, cnt, opt);
	}
	return err;
}

int
phy_hirssi_get_status(phy_info_t *pi, int32 *status)
{
	phy_type_hirssi_fns_t *fns = pi->hirssii->fns;
	int err = BCME_UNSUPPORTED;
	PHY_TRACE(("%s\n", __FUNCTION__));
	if (fns->getstatus != NULL) {
		err = (fns->getstatus)(fns->ctx, status);
	}
	return err;
}

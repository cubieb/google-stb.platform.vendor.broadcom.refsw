/*
 * HTPHY TxPowerCtrl module implementation
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

#include <typedefs.h>
#include <bcmdefs.h>
#include <phy_dbg.h>
#include <phy_mem.h>
#include "phy_type_tpc.h"
#include <phy_ht.h>
#include <phy_ht_tpc.h>
#include <phy_tpc_api.h>
#include <phy_ht_info.h>
#include <phy_utils_reg.h>

#ifndef ALL_NEW_PHY_MOD
/* < TODO: all these are going away... */
#include <wlc_phy_int.h>
/* TODO: all these are going away... > */
#endif

/* module private states */
struct phy_ht_tpc_info {
	phy_info_t *pi;
	phy_ht_info_t *hti;
	phy_tpc_info_t *ti;
};

/* local functions */
static void phy_ht_tpc_recalc_tgt(phy_type_tpc_ctx_t *ctx);
static void wlc_phy_txpower_recalc_target_ht_big(phy_type_tpc_ctx_t *ctx, ppr_t *tx_pwr_target,
    ppr_t *srom_max_txpwr, ppr_t *reg_txpwr_limit, ppr_t *txpwr_targets);
static void wlc_phy_txpower_sromlimit_get_htphy(phy_type_tpc_ctx_t *ctx, chanspec_t chanspec,
    ppr_t *max_pwr, uint8 core);
static bool phy_ht_tpc_hw_ctrl_get(phy_type_tpc_ctx_t *ctx);
static void phy_ht_tpc_set_flags(phy_type_tpc_ctx_t *ctx, phy_tx_power_t *power);
static void phy_ht_tpc_set_max(phy_type_tpc_ctx_t *ctx, phy_tx_power_t *power);

static int phy_ht_tpc_txpower_core_offset_set(phy_type_tpc_ctx_t *ctx,
        struct phy_txcore_pwr_offsets *offsets);
static int phy_ht_tpc_txpower_core_offset_get(phy_type_tpc_ctx_t *ctx,
	struct phy_txcore_pwr_offsets *offsets);
static int phy_ht_tpc_get_est_pout(phy_type_tpc_ctx_t *ctx,
	uint8* est_Pout, uint8* est_Pout_adj, uint8* est_Pout_cck);
#ifdef BCMDBG
static void phy_ht_tpc_dump_txpower_limits(phy_type_tpc_ctx_t *ctx, ppr_t* txpwr);
#endif /* BCMDBG */
static void phy_ht_tpc_set_hw_ctrl(phy_type_tpc_ctx_t *ctx, bool hwpwrctrl);

/* Register/unregister HTPHY specific implementation to common layer. */
phy_ht_tpc_info_t *
BCMATTACHFN(phy_ht_tpc_register_impl)(phy_info_t *pi, phy_ht_info_t *hti, phy_tpc_info_t *ti)
{
	phy_ht_tpc_info_t *info;
	phy_type_tpc_fns_t fns;

	PHY_TRACE(("%s\n", __FUNCTION__));

	/* allocate all storage in once */
	if ((info = phy_malloc(pi, sizeof(phy_ht_tpc_info_t))) == NULL) {
		PHY_ERROR(("%s: phy_malloc failed\n", __FUNCTION__));
		goto fail;
	}
	bzero(info, sizeof(phy_ht_tpc_info_t));
	info->pi = pi;
	info->hti = hti;
	info->ti = ti;

	/* Register PHY type specific implementation */
	bzero(&fns, sizeof(fns));
	fns.recalc = phy_ht_tpc_recalc_tgt;
	fns.recalc_target = wlc_phy_txpower_recalc_target_ht_big;
	fns.get_sromlimit = wlc_phy_txpower_sromlimit_get_htphy;
	fns.get_hwctrl = phy_ht_tpc_hw_ctrl_get;
	fns.setflags = phy_ht_tpc_set_flags;
	fns.setmax = phy_ht_tpc_set_max;
	fns.txcorepwroffsetset = phy_ht_tpc_txpower_core_offset_set;
	fns.txcorepwroffsetget = phy_ht_tpc_txpower_core_offset_get;
	fns.get_est_pout = phy_ht_tpc_get_est_pout;
#ifdef BCMDBG
	fns.dump_txpower_limits = phy_ht_tpc_dump_txpower_limits;
#endif /* BCMDBG */
	fns.set_hwctrl = phy_ht_tpc_set_hw_ctrl;
	fns.ctx = info;

	phy_tpc_register_impl(ti, &fns);

	return info;

fail:
	if (info != NULL)
		phy_mfree(pi, info, sizeof(phy_ht_tpc_info_t));
	return NULL;
}

void
BCMATTACHFN(phy_ht_tpc_unregister_impl)(phy_ht_tpc_info_t *info)
{
	phy_info_t *pi = info->pi;
	phy_tpc_info_t *ti = info->ti;

	PHY_TRACE(("%s\n", __FUNCTION__));

	phy_tpc_unregister_impl(ti);

	phy_mfree(pi, info, sizeof(phy_ht_tpc_info_t));
}

/* *************************************** */
/*                    Internal Functions                                 */
/* *************************************** */

/* recalc target txpwr and apply to h/w */
static void
phy_ht_tpc_recalc_tgt(phy_type_tpc_ctx_t *ctx)
{
	phy_ht_tpc_info_t *info = (phy_ht_tpc_info_t *)ctx;
	phy_info_t *pi = info->pi;

	PHY_TRACE(("%s\n", __FUNCTION__));

	wlc_phy_txpower_recalc_target_htphy(pi);
}

/* TODO: The code could be optimized by moving the common code to phy/cmn */
/* [PHY_RE_ARCH] There are two functions: Bigger function wlc_phy_txpower_recalc_target
 * and smaller function phy_tpc_recalc_tgt which in turn call their phy specific functions
 * which are named in a haphazard manner. This needs to be cleaned up.
 */
static void
wlc_phy_txpower_recalc_target_ht_big(phy_type_tpc_ctx_t *ctx, ppr_t *tx_pwr_target,
    ppr_t *srom_max_txpwr, ppr_t *reg_txpwr_limit, ppr_t *txpwr_targets)
{
	phy_ht_tpc_info_t *info = (phy_ht_tpc_info_t *)ctx;
	phy_info_t *pi = info->pi;
	int8 tx_pwr_max = 0;
	int8 tx_pwr_min = 255;
	uint8 mintxpwr = 0;
	uint8 core;
	chanspec_t chspec = pi->radio_chanspec;
	/* Combine user target, regulatory limit, SROM/HW/board limit and power
	 * percentage to get a tx power target for each rate.
	 */
	FOREACH_CORE(pi, core) {
		/* The user target is the starting point for determining the transmit
		 * power.  If pi->txoverride is true, then use the user target as the
		 * tx power target.
		 */
		ppr_set_cmn_val(tx_pwr_target, info->ti->data->tx_user_target);

#if defined(WL_EXPORT_TXPOWER)
		/* Only allow tx power override for internal or test builds. */
		if (!info->ti->data->txpwroverride)
#endif
		{
			/* Get board/hw limit */
			wlc_phy_txpower_sromlimit((wlc_phy_t *)pi, chspec,
			    &mintxpwr, srom_max_txpwr, core);

			/* Common Code Start */
			/* Choose minimum of provided regulatory and board/hw limits */
			ppr_compare_min(srom_max_txpwr, reg_txpwr_limit);

			/* Subtract 4 (1.0db) for 4313(IPA) as we are doing PA trimming
			 * otherwise subtract 6 (1.5 db)
			 * to ensure we don't go over
			 * the limit given a noisy power detector.  The result
			 * is now a target, not a limit.
			 */
			ppr_minus_cmn_val(srom_max_txpwr, pi->tx_pwr_backoff);

			/* Choose least of user and now combined regulatory/hw targets */
			ppr_compare_min(tx_pwr_target, srom_max_txpwr);

			/* Board specific fix reduction */

			/* Apply power output percentage */
			if (pi->tpci->data->txpwr_percent < 100) {
				ppr_multiply_percentage(tx_pwr_target,
					pi->tpci->data->txpwr_percent);
			}
			/* Common Code End */

#ifdef WL_SARLIMIT
			ppr_apply_max(tx_pwr_target, info->ti->data->sarlimit[core]);
			/* find each core TP of all rates */
			pi->txpwr_max_percore[core] = ppr_get_max(tx_pwr_target);
#endif /* WL_SARLIMIT */

			/* Enforce min power and save result as power target.
			 * LCNPHY references off the minimum so this is not appropriate for it.
			 */
			ppr_apply_min(tx_pwr_target, mintxpwr);
		}

		ppr_apply_max(tx_pwr_target, wlc_phy_txpwr_max_est_pwr_get_htphy(pi));

		tx_pwr_max = ppr_get_max(tx_pwr_target);

		if (tx_pwr_max < (pi->min_txpower * WLC_TXPWR_DB_FACTOR)) {
			tx_pwr_max = pi->min_txpower * WLC_TXPWR_DB_FACTOR;
		}
		tx_pwr_min = ppr_get_min(tx_pwr_target, mintxpwr);

#ifdef WL_SARLIMIT
		tx_pwr_max = MIN(tx_pwr_max, pi->txpwr_max_percore[core]);
#endif

		/* Common Code Start */
		/* Now calculate the tx_power_offset and update the hardware... */
		pi->tx_power_max_per_core[core] = tx_pwr_max;
		pi->tx_power_min_per_core[core] = tx_pwr_min;

#ifdef WLTXPWR_CACHE
		if (wlc_phy_txpwr_cache_is_cached(pi->txpwr_cache, pi->radio_chanspec) == TRUE) {
			wlc_phy_set_cached_pwr_min(pi->txpwr_cache, pi->radio_chanspec, core,
				tx_pwr_min);
			wlc_phy_set_cached_pwr_max(pi->txpwr_cache, pi->radio_chanspec, core,
				tx_pwr_max);
		}
#endif
		pi->openlp_tx_power_min = tx_pwr_min;
		info->ti->data->txpwrnegative = 0;

		PHY_NONE(("wl%d: %s: min %d max %d\n", pi->sh->unit, __FUNCTION__,
		    tx_pwr_min, tx_pwr_max));

		/* determinate the txpower offset by either of the following 2 methods:
		 * txpower_offset = txpower_max - txpower_target OR
		 * txpower_offset = txpower_target - txpower_min
		 * return curpower for last core loop since we are now checking
		 * MIN_cores(MAX_rates(power)) for rate disabling
		 * Only the last core loop info is valid
		 */
		if (core == PHYCORENUM((pi)->pubpi->phy_corenum) - 1) {
			info->ti->data->curpower_display_core =
				PHYCORENUM((pi)->pubpi->phy_corenum) - 1;
			if (txpwr_targets != NULL)
				ppr_copy_struct(tx_pwr_target, txpwr_targets);
		}
		/* Common Code End */

		ppr_cmn_val_minus(tx_pwr_target, pi->tx_power_max_per_core[core]);

		ppr_compare_max(pi->tx_power_offset, tx_pwr_target);
	}	/* CORE loop */

	/* Common Code Start */
#ifdef WLTXPWR_CACHE
	if (wlc_phy_txpwr_cache_is_cached(pi->txpwr_cache, pi->radio_chanspec) == TRUE) {
		wlc_phy_set_cached_pwr(pi->sh->osh, pi->txpwr_cache, pi->radio_chanspec,
			TXPWR_CACHE_POWER_OFFSETS, pi->tx_power_offset);
	}
#endif
	/*
	 * PHY_ERROR(("#####The final power offset limit########\n"));
	 * ppr_mcs_printf(pi->tx_power_offset);
	 */
	/* Common Code End */
}

static void
wlc_phy_txpower_sromlimit_get_htphy(phy_type_tpc_ctx_t *ctx, chanspec_t chanspec, ppr_t *max_pwr,
    uint8 core)
{
	phy_ht_tpc_info_t *info = (phy_ht_tpc_info_t *)ctx;
	phy_info_t *pi = info->pi;
	srom_pwrdet_t	*pwrdet  = pi->pwrdet;
	uint8 chan_freq_range;
	uint8 tmp_max_pwr = 0;
	uint8 chan = CHSPEC_CHANNEL(chanspec);

	ASSERT(core < PHY_CORE_MAX);
	ASSERT(max_pwr);
	chan_freq_range = wlc_phy_get_chan_freq_range_htphy(pi, chan);

	tmp_max_pwr = pwrdet->max_pwr[0][chan_freq_range];
	if (PHYCORENUM(pi->pubpi->phy_corenum) > 1)
		tmp_max_pwr = MIN(tmp_max_pwr, pwrdet->max_pwr[1][chan_freq_range]);
	if (PHYCORENUM(pi->pubpi->phy_corenum) > 2)
		tmp_max_pwr = MIN(tmp_max_pwr, pwrdet->max_pwr[2][chan_freq_range]);

	wlc_phy_txpwr_apply_srom9(pi, chan_freq_range, chanspec, tmp_max_pwr, max_pwr);

	if (pwrdet->max_pwr[core][chan_freq_range] > tmp_max_pwr)
		ppr_plus_cmn_val(max_pwr, (pwrdet->max_pwr[core][chan_freq_range] - tmp_max_pwr));

	switch (chan_freq_range) {
	case WL_CHAN_FREQ_RANGE_2G:
	case WL_CHAN_FREQ_RANGE_5G_BAND0:
	case WL_CHAN_FREQ_RANGE_5G_BAND1:
	case WL_CHAN_FREQ_RANGE_5G_BAND2:
	case WL_CHAN_FREQ_RANGE_5G_BAND3:
		ppr_apply_max(max_pwr, pwrdet->max_pwr[core][chan_freq_range]);
		break;
	}
}

static bool
phy_ht_tpc_hw_ctrl_get(phy_type_tpc_ctx_t *ctx)
{
	phy_ht_tpc_info_t *info = (phy_ht_tpc_info_t *)ctx;
	phy_info_t *pi = info->pi;
	return pi->txpwrctrl;
}

static void
phy_ht_tpc_set_flags(phy_type_tpc_ctx_t *ctx, phy_tx_power_t *power)
{
	phy_ht_tpc_info_t *info = (phy_ht_tpc_info_t *)ctx;
	phy_info_t *pi = info->pi;
	power->rf_cores = PHYCORENUM(pi->pubpi->phy_corenum);
	power->flags |= (WL_TX_POWER_F_MIMO);
	if (pi->txpwrctrl == PHY_TPC_HW_ON)
		power->flags |= (WL_TX_POWER_F_ENABLED | WL_TX_POWER_F_HW);
}

static void
phy_ht_tpc_set_max(phy_type_tpc_ctx_t *ctx, phy_tx_power_t *power)
{
	uint8 core;
	phy_ht_tpc_info_t *info = (phy_ht_tpc_info_t *)ctx;
	phy_info_t *pi = info->pi;
	/* Store the maximum target power among all rates */
	FOREACH_CORE(pi, core) {
		power->tx_power_max[core] = pi->tx_power_max_per_core[core];
#ifdef WL_SARLIMIT
		power->SARLIMIT[core] = WLC_TXPWR_MAX;
#endif
	}
}

static int
phy_ht_tpc_txpower_core_offset_set(phy_type_tpc_ctx_t *ctx, struct phy_txcore_pwr_offsets *offsets)
{
	int8 core_offset;
	int core, offset_changed;

	phy_ht_tpc_info_t *info = (phy_ht_tpc_info_t *)ctx;
	phy_info_t *pi = info->pi;
	phy_info_htphy_t *pi_ht = (phy_info_htphy_t *)pi->u.pi_htphy;

	offset_changed = FALSE;

	FOREACH_CORE(pi, core) {
		core_offset = offsets->offset[core];
		if (core_offset != 0 && core > pi->pubpi->phy_corenum) {
			return BCME_BADARG;
		}

		if (pi_ht->txpwr_offset[core] != core_offset) {
			offset_changed = TRUE;
			pi_ht->txpwr_offset[core] = core_offset;
		}
	}

	/* Apply the new per-core targets to the hw */
	if (pi->sh->clk && offset_changed) {
		wlapi_suspend_mac_and_wait(pi->sh->physhim);
		wlc_phy_txpower_recalc_target_htphy(pi);
		wlapi_enable_mac(pi->sh->physhim);
	}

	return BCME_OK;
}

static int
phy_ht_tpc_txpower_core_offset_get(phy_type_tpc_ctx_t *ctx, struct phy_txcore_pwr_offsets *offsets)
{
	int core;

	phy_ht_tpc_info_t *info = (phy_ht_tpc_info_t *)ctx;
	phy_info_t *pi = info->pi;
	phy_info_htphy_t *pi_ht = (phy_info_htphy_t *)pi->u.pi_htphy;

	memset(offsets, 0, sizeof(struct phy_txcore_pwr_offsets));

	FOREACH_CORE(pi, core) {
		offsets->offset[core] = pi_ht->txpwr_offset[core];
	}

	return BCME_OK;
}


static int
phy_ht_tpc_get_est_pout(phy_type_tpc_ctx_t *ctx,
	uint8* est_Pout, uint8* est_Pout_adj, uint8* est_Pout_cck)
{
	phy_ht_tpc_info_t *tpc_info = (phy_ht_tpc_info_t *) ctx;
	phy_info_t *pi = tpc_info->pi;

	*est_Pout_cck = 0;

	/* Get power estimates */
	wlapi_suspend_mac_and_wait(pi->sh->physhim);
	phy_utils_phyreg_enter(pi);
	wlc_phy_txpwr_est_pwr_htphy(pi, est_Pout, est_Pout_adj);
	phy_utils_phyreg_exit(pi);
	wlapi_enable_mac(pi->sh->physhim);

	return BCME_OK;
}

#ifdef BCMDBG
static void
phy_ht_tpc_dump_txpower_limits(phy_type_tpc_ctx_t *ctx, ppr_t* txpwr)
{
	int i;
	char fraction[4][4] = {"   ", ".25", ".5 ", ".75"};
	ppr_dsss_rateset_t dsss_limits;
	ppr_ofdm_rateset_t ofdm_limits;
	ppr_ht_mcs_rateset_t mcs_limits;
	bool phy_specific_log = TRUE;

	printf("%s", phy_specific_log ? "20MHz 1 Nsts to 1 Tx " : "20MHz MCS 0-7 SISO   ");
	ppr_get_ht_mcs(txpwr, WL_TX_BW_20, WL_TX_NSS_1, WL_TX_MODE_NONE, WL_TX_CHAINS_1,
		&mcs_limits);
	for (i = 0; i < WL_RATESET_SZ_HT_MCS; i++) {
		printf(" %2d%s", mcs_limits.pwr[i]/ WLC_TXPWR_DB_FACTOR,
			fraction[mcs_limits.pwr[i] % WLC_TXPWR_DB_FACTOR]);
	}
	printf("\n");

	printf("%s", phy_specific_log ? "20MHz 1 Nsts to 2 Tx " : "20MHz MCS 0-7 CDD    ");
	ppr_get_ht_mcs(txpwr, WL_TX_BW_20, WL_TX_NSS_1, WL_TX_MODE_CDD, WL_TX_CHAINS_2,
		&mcs_limits);
	for (i = 0; i < WL_RATESET_SZ_HT_MCS; i++) {
		printf(" %2d%s", mcs_limits.pwr[i]/ WLC_TXPWR_DB_FACTOR,
			fraction[mcs_limits.pwr[i] % WLC_TXPWR_DB_FACTOR]);
	}
	printf("\n");

	if (phy_specific_log) {
		printf("20MHz 1 Nsts to 3 Tx ");
		ppr_get_ht_mcs(txpwr, WL_TX_BW_20, WL_TX_NSS_1, WL_TX_MODE_CDD, WL_TX_CHAINS_3,
			&mcs_limits);
	} else {
		printf("20MHz MCS 0-7 STBC   ");
		ppr_get_ht_mcs(txpwr, WL_TX_BW_20, WL_TX_NSS_2, WL_TX_MODE_STBC, WL_TX_CHAINS_2,
			&mcs_limits);
	}
	for (i = 0; i < WL_RATESET_SZ_HT_MCS; i++) {
		printf(" %2d%s", mcs_limits.pwr[i]/ WLC_TXPWR_DB_FACTOR,
			fraction[mcs_limits.pwr[i] % WLC_TXPWR_DB_FACTOR]);
	}
	printf("\n");

	printf("%s", phy_specific_log ? "20MHz 2 Nsts to 2 Tx " : "20MHz MCS 8-15 SDM   ");
	ppr_get_ht_mcs(txpwr, WL_TX_BW_20, WL_TX_NSS_2, WL_TX_MODE_NONE, WL_TX_CHAINS_2,
		&mcs_limits);
	for (i = 0; i < WL_RATESET_SZ_HT_MCS; i++) {
		printf(" %2d%s", mcs_limits.pwr[i]/ WLC_TXPWR_DB_FACTOR,
			fraction[mcs_limits.pwr[i] % WLC_TXPWR_DB_FACTOR]);
	}
	printf("\n");

	if (phy_specific_log) {
		printf("20MHz 2 Nsts to 3 Tx ");
		ppr_get_ht_mcs(txpwr, WL_TX_BW_20, WL_TX_NSS_2, WL_TX_MODE_NONE, WL_TX_CHAINS_3,
			&mcs_limits);
		for (i = 0; i < WL_RATESET_SZ_HT_MCS; i++) {
			printf(" %2d%s", mcs_limits.pwr[i]/ WLC_TXPWR_DB_FACTOR,
				fraction[mcs_limits.pwr[i] % WLC_TXPWR_DB_FACTOR]);
		}
		printf("\n");

		printf("20MHz 3 Nsts to 3 Tx ");
		ppr_get_ht_mcs(txpwr, WL_TX_BW_20, WL_TX_NSS_3, WL_TX_MODE_NONE, WL_TX_CHAINS_3,
			&mcs_limits);
		for (i = 0; i < WL_RATESET_SZ_HT_MCS; i++) {
			printf(" %2d%s", mcs_limits.pwr[i]/ WLC_TXPWR_DB_FACTOR,
				fraction[mcs_limits.pwr[i] % WLC_TXPWR_DB_FACTOR]);
		}
		printf("\n");
	}


	printf("40MHz OFDM SISO      ");
	ppr_get_ofdm(txpwr, WL_TX_BW_40, WL_TX_MODE_NONE, WL_TX_CHAINS_1, &ofdm_limits);
	for (i = 0; i < WL_RATESET_SZ_OFDM; i++) {
		printf(" %2d%s", ofdm_limits.pwr[i]/ WLC_TXPWR_DB_FACTOR,
			fraction[ofdm_limits.pwr[i] % WLC_TXPWR_DB_FACTOR]);
	}
	printf("\n");

	printf("40MHz OFDM CDD       ");
	ppr_get_ofdm(txpwr, WL_TX_BW_40, WL_TX_MODE_CDD, WL_TX_CHAINS_2, &ofdm_limits);
	for (i = 0; i < WL_RATESET_SZ_OFDM; i++) {
		printf(" %2d%s", ofdm_limits.pwr[i]/ WLC_TXPWR_DB_FACTOR,
			fraction[ofdm_limits.pwr[i] % WLC_TXPWR_DB_FACTOR]);
	}
	printf("\n");

	printf("%s", phy_specific_log ? "40MHz 1 Nsts to 1 Tx " : "40MHz MCS 0-7 SISO   ");
	ppr_get_ht_mcs(txpwr, WL_TX_BW_40, WL_TX_NSS_1, WL_TX_MODE_NONE, WL_TX_CHAINS_1,
		&mcs_limits);
	for (i = 0; i < WL_RATESET_SZ_HT_MCS; i++) {
		printf(" %2d%s", mcs_limits.pwr[i]/ WLC_TXPWR_DB_FACTOR,
			fraction[mcs_limits.pwr[i] % WLC_TXPWR_DB_FACTOR]);
	}
	printf("\n");

	printf("%s", phy_specific_log ? "40MHz 1 Nsts to 2 Tx " : "40MHz MCS 0-7 CDD    ");
	ppr_get_ht_mcs(txpwr, WL_TX_BW_40, WL_TX_NSS_1, WL_TX_MODE_CDD, WL_TX_CHAINS_2,
		&mcs_limits);
	for (i = 0; i < WL_RATESET_SZ_HT_MCS; i++) {
		printf(" %2d%s", mcs_limits.pwr[i]/ WLC_TXPWR_DB_FACTOR,
			fraction[mcs_limits.pwr[i] % WLC_TXPWR_DB_FACTOR]);
	}
	printf("\n");

	printf("%s", phy_specific_log ? "40MHz 1 Nsts to 3 Tx " : "40MHz MCS 0-7 CDD    ");
	ppr_get_ht_mcs(txpwr, WL_TX_BW_40, WL_TX_NSS_1, WL_TX_MODE_CDD, WL_TX_CHAINS_3,
		&mcs_limits);
	for (i = 0; i < WL_RATESET_SZ_HT_MCS; i++) {
		printf(" %2d%s", mcs_limits.pwr[i]/ WLC_TXPWR_DB_FACTOR,
			fraction[mcs_limits.pwr[i] % WLC_TXPWR_DB_FACTOR]);
	}
	printf("\n");

	printf("%s", phy_specific_log ? "40MHz 2 Nsts to 2 Tx " : "40MHz MCS8-15 SDM    ");
	ppr_get_ht_mcs(txpwr, WL_TX_BW_40, WL_TX_NSS_2, WL_TX_MODE_NONE, WL_TX_CHAINS_2,
		&mcs_limits);
	for (i = 0; i < WL_RATESET_SZ_HT_MCS; i++) {
		printf(" %2d%s", mcs_limits.pwr[i]/ WLC_TXPWR_DB_FACTOR,
			fraction[mcs_limits.pwr[i] % WLC_TXPWR_DB_FACTOR]);
	}
	printf("\n");

	if (phy_specific_log) {
		printf("40MHz 2 Nsts to 3 Tx ");
		ppr_get_ht_mcs(txpwr, WL_TX_BW_40, WL_TX_NSS_2, WL_TX_MODE_NONE, WL_TX_CHAINS_3,
			&mcs_limits);
		for (i = 0; i < WL_RATESET_SZ_HT_MCS; i++) {
			printf(" %2d%s", mcs_limits.pwr[i]/ WLC_TXPWR_DB_FACTOR,
				fraction[mcs_limits.pwr[i] % WLC_TXPWR_DB_FACTOR]);
		}
		printf("\n");

		printf("40MHz 3 Nsts to 3 Tx ");
		ppr_get_ht_mcs(txpwr, WL_TX_BW_40, WL_TX_NSS_3, WL_TX_MODE_NONE, WL_TX_CHAINS_3,
			&mcs_limits);
		for (i = 0; i < WL_RATESET_SZ_HT_MCS; i++) {
			printf(" %2d%s", mcs_limits.pwr[i]/ WLC_TXPWR_DB_FACTOR,
				fraction[mcs_limits.pwr[i] % WLC_TXPWR_DB_FACTOR]);
		}
		printf("\n");
	}

	if (!phy_specific_log)
		return;

	printf("20MHz UL CCK         ");
	ppr_get_dsss(txpwr, WL_TX_BW_20IN40, WL_TX_CHAINS_1, &dsss_limits);
	for (i = 0; i < WL_RATESET_SZ_DSSS; i++) {
		printf(" %2d%s", dsss_limits.pwr[i]/ WLC_TXPWR_DB_FACTOR,
			fraction[dsss_limits.pwr[i] % WLC_TXPWR_DB_FACTOR]);
	}
	printf("\n");

	printf("20MHz UL OFDM SISO   ");
	ppr_get_ofdm(txpwr, WL_TX_BW_20IN40, WL_TX_MODE_NONE, WL_TX_CHAINS_1, &ofdm_limits);
	for (i = 0; i < WL_RATESET_SZ_OFDM; i++) {
		printf(" %2d%s", ofdm_limits.pwr[i]/ WLC_TXPWR_DB_FACTOR,
			fraction[ofdm_limits.pwr[i] % WLC_TXPWR_DB_FACTOR]);
	}
	printf("\n");

	printf("20MHz UL OFDM CDD    ");
	ppr_get_ofdm(txpwr, WL_TX_BW_20IN40, WL_TX_MODE_CDD, WL_TX_CHAINS_2, &ofdm_limits);
	for (i = 0; i < WL_RATESET_SZ_OFDM; i++) {
		printf(" %2d%s", ofdm_limits.pwr[i]/ WLC_TXPWR_DB_FACTOR,
			fraction[ofdm_limits.pwr[i] % WLC_TXPWR_DB_FACTOR]);
	}
	printf("\n");

	printf("20UL 1 Nsts to 1 Tx  ");
	ppr_get_ht_mcs(txpwr, WL_TX_BW_20IN40, WL_TX_NSS_1, WL_TX_MODE_NONE, WL_TX_CHAINS_1,
		&mcs_limits);
	for (i = 0; i < WL_RATESET_SZ_HT_MCS; i++) {
		printf(" %2d%s", mcs_limits.pwr[i]/ WLC_TXPWR_DB_FACTOR,
			fraction[mcs_limits.pwr[i] % WLC_TXPWR_DB_FACTOR]);
	}
	printf("\n");

	printf("20UL 1 Nsts to 2 Tx  ");
	ppr_get_ht_mcs(txpwr, WL_TX_BW_20IN40, WL_TX_NSS_1, WL_TX_MODE_CDD, WL_TX_CHAINS_2,
		&mcs_limits);
	for (i = 0; i < WL_RATESET_SZ_HT_MCS; i++) {
		printf(" %2d%s", mcs_limits.pwr[i]/ WLC_TXPWR_DB_FACTOR,
			fraction[mcs_limits.pwr[i] % WLC_TXPWR_DB_FACTOR]);
	}
	printf("\n");

	printf("20UL 1 Nsts to 3 Tx  ");
	ppr_get_ht_mcs(txpwr, WL_TX_BW_20IN40, WL_TX_NSS_1, WL_TX_MODE_CDD, WL_TX_CHAINS_3,
		&mcs_limits);
	for (i = 0; i < WL_RATESET_SZ_HT_MCS; i++) {
		printf(" %2d%s", mcs_limits.pwr[i]/ WLC_TXPWR_DB_FACTOR,
			fraction[mcs_limits.pwr[i] % WLC_TXPWR_DB_FACTOR]);
	}
	printf("\n");

	printf("20UL 2 Nsts to 2 Tx  ");
	ppr_get_ht_mcs(txpwr, WL_TX_BW_20IN40, WL_TX_NSS_2, WL_TX_MODE_NONE, WL_TX_CHAINS_2,
		&mcs_limits);
	for (i = 0; i < WL_RATESET_SZ_HT_MCS; i++) {
		printf(" %2d%s", mcs_limits.pwr[i]/ WLC_TXPWR_DB_FACTOR,
			fraction[mcs_limits.pwr[i] % WLC_TXPWR_DB_FACTOR]);
	}
	printf("\n");

	printf("20UL 2 Nsts to 3 Tx  ");
	ppr_get_ht_mcs(txpwr, WL_TX_BW_20IN40, WL_TX_NSS_2, WL_TX_MODE_NONE, WL_TX_CHAINS_3,
		&mcs_limits);
	for (i = 0; i < WL_RATESET_SZ_HT_MCS; i++) {
		printf(" %2d%s", mcs_limits.pwr[i]/ WLC_TXPWR_DB_FACTOR,
			fraction[mcs_limits.pwr[i] % WLC_TXPWR_DB_FACTOR]);
	}
	printf("\n");

	printf("20UL 3 Nsts to 3 Tx  ");
	ppr_get_ht_mcs(txpwr, WL_TX_BW_20IN40, WL_TX_NSS_3, WL_TX_MODE_NONE, WL_TX_CHAINS_3,
		&mcs_limits);
	for (i = 0; i < WL_RATESET_SZ_HT_MCS; i++) {
		printf(" %2d%s", mcs_limits.pwr[i]/ WLC_TXPWR_DB_FACTOR,
			fraction[mcs_limits.pwr[i] % WLC_TXPWR_DB_FACTOR]);
	}
	printf("\n");
}
#endif /* BCMDBG */

static void
phy_ht_tpc_set_hw_ctrl(phy_type_tpc_ctx_t *ctx, bool hwpwrctrl)
{
	phy_ht_tpc_info_t *tpc_info = (phy_ht_tpc_info_t *) ctx;
	phy_info_t *pi = tpc_info->pi;

	wlapi_suspend_mac_and_wait(pi->sh->physhim);

	/* turn on/off power control */
	wlc_phy_txpwrctrl_enable_htphy(pi, pi->txpwrctrl);

	wlapi_enable_mac(pi->sh->physhim);
}
/* *************************************** */
/*                    External Functions                                 */
/* *************************************** */

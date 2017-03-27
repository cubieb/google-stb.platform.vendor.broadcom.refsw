/*
 * TSSI Cal module interface (to other PHY modules).
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

#ifndef _phy_tssical_h_
#define _phy_tssical_h_

#include <typedefs.h>
#include <phy_api.h>

typedef int phy_tssical_entry_id_t;

/* forward declaration */
typedef struct phy_tssical_info phy_tssical_info_t;

/* attach/detach */
phy_tssical_info_t *phy_tssical_attach(phy_info_t *pi);
void phy_tssical_detach(phy_tssical_info_t *cmn_info);

/* down */
int phy_tssical_down(phy_tssical_info_t *cmn_info);

int phy_tssical_do_dummy_tx(phy_info_t *pi, bool ofdm, bool pa_on);

/* phy txcal power tssi LUT */
typedef struct txcal_pwr_tssi_lut {
	wl_txcal_power_tssi_t *txcal_pwr_tssi;
	struct txcal_pwr_tssi_lut *next_chan;
} txcal_pwr_tssi_lut_t;

typedef struct txcal_root_pwr_tssi {
	txcal_pwr_tssi_lut_t *root_pwr_tssi_lut_2G;
	txcal_pwr_tssi_lut_t *root_pwr_tssi_lut_5G20;
	txcal_pwr_tssi_lut_t *root_pwr_tssi_lut_5G40;
	txcal_pwr_tssi_lut_t *root_pwr_tssi_lut_5G80;
} txcal_root_pwr_tssi_t;

#ifdef WLC_TXCAL
bool phy_tssical_get_pwr_tssi_tbl_in_use(phy_tssical_info_t *tssicali);
bool phy_tssical_get_olpc_idx_valid_in_use(phy_tssical_info_t *tssicali);
uint8 phy_tssical_get_olpc_idx_valid(phy_tssical_info_t *tssicali);
int8 phy_tssical_get_olpc_anchor2g(phy_tssical_info_t *tssicali);
void phy_tssical_set_olpc_anchor2g(phy_tssical_info_t *tssicali, int8 anchor2g);
int8 phy_tssical_get_olpc_anchor5g(phy_tssical_info_t *tssicali);
void phy_tssical_set_olpc_anchor5g(phy_tssical_info_t *tssicali, int8 anchor5g);
int8 phy_tssical_get_olpc_anchor(phy_tssical_info_t *tssicali);
int8 phy_tssical_get_olpc_threshold(phy_tssical_info_t *tssicali);
void phy_tssical_set_olpc_threshold_val(phy_tssical_info_t *tssicali, int8 olpc_threshold);
int16 phy_tssical_get_last_calc_temp(phy_tssical_info_t *tssicali);
void phy_tssical_set_last_calc_temp(phy_tssical_info_t *tssicali, int16 last_calc_temp);
int8 phy_tssical_get_disable_olpc(phy_tssical_info_t *tssicali);
void phy_tssical_set_disable_olpc(phy_tssical_info_t *tssicali, int8 disable_olpc);
void phy_tssical_get_set_olpc_offset(phy_tssical_info_t *tssicali, int8 *olpc_offset, uint8 set);
void phy_tssical_set_measured_pwr(phy_tssical_info_t *tssicali, wl_txcal_meas_percore_t *per_core);
void phy_tssical_compute_olpc_idx(phy_tssical_info_t *tssicali);
txcal_root_pwr_tssi_t * phy_tssical_get_root_pwr_tssi_tbl(phy_tssical_info_t *tssicali);
void phy_tssical_set_olpc_idx_valid(phy_tssical_info_t *tssicali, uint8 val);
uint8 phy_tssical_get_olpc_idx_in_use(phy_tssical_info_t *tssicali);
void phy_tssical_set_olpc_anchor_threshold(phy_tssical_info_t *tssicali);
int16 phy_tssical_get_olpc_tempslope(phy_tssical_info_t *tssicali, uint8 core);
int8 phy_tssical_get_olpc_offset(phy_tssical_info_t *tssicali, int8 chan_freq_range);
uint8 phy_tssical_get_olpc_anchor_idx(phy_tssical_info_t *tssicali, uint8 core);
void phy_tssical_set_olpc_anchor_idx(phy_tssical_info_t *tssicali, uint8 core, uint8 val);
int16 phy_tssical_get_olpc_tempsense(phy_tssical_info_t *tssicali, uint8 core);
void phy_tssical_set_olpc_tempsense(phy_tssical_info_t *tssicali, uint8 core, int16 val);
void phy_tssical_iov_set_olpc_threshold(phy_tssical_info_t *tssicali, int8 olpc_threshold);
bool phy_tssical_get_pwr_tssi_tbl_in_use(phy_tssical_info_t *tssicali);
void phy_tssical_set_pwr_tssi_tbl_in_use(phy_tssical_info_t *tssicali, bool val);
uint8 phy_tssical_get_txcal_status(phy_tssical_info_t *tssicali);
void phy_tssical_set_txcal_status(phy_tssical_info_t *tssicali, uint8 val);
int phy_tssical_iovar_adjusted_tssi(phy_tssical_info_t *tssicali,
		int32 *ret_int_ptr, uint8 int_val);
int phy_tssical_copy_get_gainsweep_meas(phy_tssical_info_t *tssicali,
		wl_txcal_meas_ncore_t * txcal_meas);
int phy_tssical_gainsweep(phy_tssical_info_t *tssicali, wl_txcal_params_t *txcal_params);
int phy_tssical_generate_pwr_tssi_tbl(phy_tssical_info_t *tssicali);
int phy_tssical_set_pwr_tssi_tbl(phy_tssical_info_t *tssicali, void *p);
int phy_tssical_copy_get_pwr_tssi_tbl(phy_tssical_info_t *tssicali,
		wl_txcal_power_tssi_ncore_t * txcal_tssi);
int phy_tssical_get_olpc_pwr(phy_tssical_info_t *tssicali, void *p, void *a);
int phy_tssical_alloc_pwr_tssi_lut(phy_tssical_info_t *tssicali, txcal_pwr_tssi_lut_t** LUT);
int phy_tssical_copy_set_pwr_tssi_tbl_gentbl(wl_txcal_power_tssi_t *pi_txcal_pwr_tssi,
		wl_txcal_power_tssi_ncore_t *txcal_tssi);
int phy_tssical_copy_set_pwr_tssi_tbl_storetbl(wl_txcal_power_tssi_t *pi_txcal_pwr_tssi,
		wl_txcal_power_tssi_ncore_t *txcal_tssi);
void phy_tssical_copy_rsdb_pwr_tssi_tbl(phy_tssical_info_t *tssicali);
int phy_tssical_get_pwr_tssi_tbl(phy_tssical_info_t *tssicali, uint8 channel);
int phy_tssical_store_pwr_tssi_tbl(phy_tssical_info_t *tssicali);
int phy_tssical_iov_apply_pwr_tssi_tbl(phy_tssical_info_t *tssicali, int int_val);
int phy_tssical_iov_read_est_pwr_lut(phy_tssical_info_t *tssicali, void *a, int int_val);
int phy_tssical_set_olpc_pwr(phy_tssical_info_t *tssicali, void *p, void *a);
int phy_tssical_generate_estpwr_lut(wl_txcal_power_tssi_t *txcal_pwr_tssi,
		uint16 *estpwr, uint8 core);
int phy_tssical_apply_pa_params(phy_tssical_info_t *tssicali);
int phy_tssical_apply_pwr_tssi_tbl(phy_tssical_info_t *tssicali,
		wl_txcal_power_tssi_t *txcal_pwr_tssi);
void phy_tssical_set_olpc_idx_in_use(phy_tssical_info_t *tssicali, uint8 val);
void phy_tssical_set_olpc_threshold(phy_tssical_info_t *tssicali);
#endif /* WLC_TXCAL */


#endif /* _phy_tssical_h_ */

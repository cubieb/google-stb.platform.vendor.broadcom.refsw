/*
 * wl lq command module
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
 * $Id: wluc_lq.c 458728 2014-02-27 18:15:25Z $
 */

#ifdef WIN32
#include <windows.h>
#endif

#include <wlioctl.h>


/* Because IL_BIGENDIAN was removed there are few warnings that need
 * to be fixed. Windows was not compiled earlier with IL_BIGENDIAN.
 * Hence these warnings were not seen earlier.
 * For now ignore the following warnings
 */
#ifdef WIN32
#pragma warning(push)
#pragma warning(disable : 4244)
#pragma warning(disable : 4761)
#endif

#include <bcmutils.h>
#include <bcmendian.h>
#include "wlu_common.h"
#include "wlu.h"

static cmd_func_t wl_rssi_event, wl_chan_qual_event;
static cmd_func_t wl_chanim_state, wl_chanim_mode;
static cmd_func_t wl_chanim_acs_record;
static cmd_func_t wl_chanim_stats;

static cmd_t wl_lq_cmds[] = {
	{ "rssi_event", wl_rssi_event, WLC_GET_VAR, WLC_SET_VAR,
	"Set parameters associated with RSSI event notification\n"
	"\tusage: wl rssi_event <rate_limit> <rssi_levels>\n"
	"\trate_limit: Number of events posted to application will be limited"
	" to 1 per this rate limit. Set to 0 to disable rate limit.\n"
	"\trssi_levels: Variable number of RSSI levels (maximum 8) "
	" in increasing order (e.g. -85 -70 -60). An event will be posted"
	" each time the RSSI of received beacons/packets crosses a level."},
	{ "chq_event", wl_chan_qual_event, WLC_GET_VAR, WLC_SET_VAR,
	"Set parameters associated with channel quality  event notification\n"
	"\tusage: wl chq_event <rate_limit> <cca_levels> <nf_levels> <nf_lte_levels>\n"
	"\trate_limit: Number of events posted to application will be limited"
	" to 1 per this rate limit. Set to 0 to disable rate limit.\n"
	"\tcsa/nf/nf_lte levels: Variable number of threshold levels (maximum 8)"
	" in pairs of hi-to-low/lo-to-hi, and in increasing order (e.g. -90 -85 -80)."
	" A 0 0 pair terminates level array for one metric."
	" An event will be posted whenever a threshold is being crossed."},
	{"chanim_state", wl_chanim_state, WLC_GET_VAR, -1,
	"get channel interference state\n"
	"\tUsage: wl chanim_state channel\n"
	"\tValid channels: 1 - 14\n"
	"\treturns: 0 - Acceptable; 1 - Severe"
	},
	{"chanim_mode", wl_chanim_mode, WLC_GET_VAR, WLC_SET_VAR,
	"get/set channel interference measure (chanim) mode\n"
	"\tUsage: wl chanim_mode <value>\n"
	"\tvalue: 0 - disabled; 1 - detection only; 2 - detection and avoidance"
	},
	{"chanim_acs_record", wl_chanim_acs_record, WLC_GET_VAR, -1,
	"get the auto channel scan record. \n"
	"\t Usage: wl acs_record"
	},
	{"chanim_stats", wl_chanim_stats, WLC_GET_VAR, -1,
	"get chanim stats \n"
	"\t Usage: wl chanim_stats"
	},
	{ NULL, NULL, 0, 0, NULL }
};

static char *buf;

/* module initialization */
void
wluc_lq_module_init(void)
{
	/* get the global buf */
	buf = wl_get_buf();

	/* register lq commands */
	wl_module_cmds_register(wl_lq_cmds);
}

static int
wl_chan_qual_event(void *wl, cmd_t *cmd, char **argv)
{
	int ret;
	const char *CHAN_QUAL_NAME[WL_CHAN_QUAL_TOTAL] = {"   CCA", "    NF", "NF_LTE"};

	if (!*++argv) {
		/* get */
		void *ptr = NULL;
		wl_chan_qual_event_t chq;
		uint i, j;

		if ((ret = wlu_var_getbuf(wl, cmd->name, NULL, 0, &ptr)) < 0)
			return ret;

		memcpy(&chq, ptr, sizeof(chq));
		chq.rate_limit_msec = dtoh32(chq.rate_limit_msec);

		printf("rate per %dms\n", chq.rate_limit_msec);
		for (i = 0; i < WL_CHAN_QUAL_TOTAL; i++) {
			printf("%s[%d]:", CHAN_QUAL_NAME[i], chq.metric[i].id);
			for (j = 0; (j < chq.metric[i].num_levels) &&
				(j < MAX_CHAN_QUAL_LEVELS); j++) {
				printf(" (%d, %d)", chq.metric[i].htol[j], chq.metric[i].ltoh[j]);
			}
			printf("\n");
		}
	} else {
		/* set */
		wl_chan_qual_event_t chq;
		uint i;

		memset(&chq, 0, sizeof(wl_chan_qual_event_t));
		chq.rate_limit_msec = atoi(*argv++);
		chq.rate_limit_msec = htod32(chq.rate_limit_msec);
		chq.num_metrics = htod16(WL_CHAN_QUAL_TOTAL);

		for (i = 0; i < WL_CHAN_QUAL_TOTAL; i++) {
			chq.metric[i].id = i;
			while (argv[0] && argv[1]) {
				int16 htol, ltoh;
				htol = htod16(atoi(*argv++));
				ltoh = htod16(atoi(*argv++));

				/* double zeros terminate one metric */
				if ((htol == 0) && (ltoh == 0))
					break;

				/* make sure that ltoh >= htol */
				if (ltoh < htol)
					return -1;

				/* ignore extra thresholds */
				if (chq.metric[i].num_levels >= MAX_CHAN_QUAL_LEVELS)
					continue;

				chq.metric[i].htol[chq.metric[i].num_levels] = htol;
				chq.metric[i].ltoh[chq.metric[i].num_levels] = ltoh;

				/* all metric threshold levels must be in increasing order */
				if (chq.metric[i].num_levels > 0) {
					if ((chq.metric[i].htol[chq.metric[i].num_levels] <=
						chq.metric[i].htol[chq.metric[i].num_levels - 1]) ||
					    (chq.metric[i].ltoh[chq.metric[i].num_levels] <=
						chq.metric[i].ltoh[chq.metric[i].num_levels - 1])) {
						return -1;
					}
				}

				(chq.metric[i].num_levels)++;
			}
		}

		if (*argv) {
			/* too many parameters */
			return -1;
		}

		ret = wlu_var_setbuf(wl, cmd->name, &chq, sizeof(chq));
	}
	return ret;
}

static int
wl_rssi_event(void *wl, cmd_t *cmd, char **argv)
{
	int ret;

	if (!*++argv) {
		/* get */
		void *ptr = NULL;
		wl_rssi_event_t rssi;
		uint i;

		if ((ret = wlu_var_getbuf(wl, cmd->name, NULL, 0, &ptr)) < 0)
			return ret;

		memcpy(&rssi, ptr, sizeof(rssi));
		rssi.rate_limit_msec = dtoh32(rssi.rate_limit_msec);

		printf("%d", rssi.rate_limit_msec);
		for (i = 0; i < rssi.num_rssi_levels; i++) {
			printf(" %d", rssi.rssi_levels[i]);
		}
		printf("\n");
	} else {
		/* set */
		wl_rssi_event_t rssi;

		memset(&rssi, 0, sizeof(wl_rssi_event_t));
		rssi.rate_limit_msec = atoi(*argv);

		while (*++argv && rssi.num_rssi_levels < MAX_RSSI_LEVELS) {
			rssi.rssi_levels[rssi.num_rssi_levels++] = atoi(*argv);
			if (rssi.num_rssi_levels > 1) {
				if (rssi.rssi_levels[rssi.num_rssi_levels - 1] <=
					rssi.rssi_levels[rssi.num_rssi_levels - 2]) {
					/* rssi levels must be in increasing order */
					return BCME_USAGE_ERROR;
				}
			}
		}

		if (*argv) {
			/* too many parameters */
			return BCME_USAGE_ERROR;
		}

		rssi.rate_limit_msec = htod32(rssi.rate_limit_msec);
		ret = wlu_var_setbuf(wl, cmd->name, &rssi, sizeof(rssi));
	}
	return ret;
}

static int
wl_chanim_state(void *wl, cmd_t *cmd, char **argv)
{
	uint32 chanspec;
	int argc = 0;
	int ret, val;

	argv++;

	/* find the arg count */
	while (argv[argc])
		argc++;

	if (argc != 1)
		return BCME_USAGE_ERROR;

	chanspec = wf_chspec_aton(*argv);
	chanspec = wl_chspec32_to_driver(chanspec);
	if (chanspec == INVCHANSPEC) {
		return BCME_USAGE_ERROR;
	}

	ret = wlu_iovar_getbuf(wl, cmd->name, &chanspec, sizeof(chanspec),
	                       buf, WLC_IOCTL_SMLEN);
	if (ret < 0)
		return ret;
	val = *(int*)buf;
	val = dtoh32(val);

	printf("%d\n", val);
	return 0;
}

static int
wl_chanim_mode(void *wl, cmd_t *cmd, char **argv)
{
	int ret;
	int val;
	char *endptr;
	int mode;

	if (!*++argv) {
		if (cmd->get < 0)
			return -1;
		if ((ret = wlu_iovar_getint(wl, cmd->name, &mode)) < 0)
			return ret;

		switch (mode) {
		case CHANIM_DISABLE:
			printf("CHANIM mode: disabled.\n");
			break;
		case CHANIM_DETECT:
			printf("CHANIM mode: detect only.\n");
			break;
		case CHANIM_EXT:
			printf("CHANIM mode: external (acsd).\n");
			break;
		case CHANIM_ACT:
			printf("CHANIM mode: detect + act.\n");
			break;
		}
		return 0;
	} else {
		mode = CHANIM_DETECT;
		val = strtol(*argv, &endptr, 0);
		if (*endptr != '\0')
			return BCME_USAGE_ERROR;

		switch (val) {
			case 0:
				mode = CHANIM_DISABLE;
				break;
			case 1:
				mode = CHANIM_DETECT;
				break;
			case 2:
				mode = CHANIM_EXT;
				break;
			case 3:
				mode = CHANIM_ACT;
				break;
			default:
				return BCME_BADARG;
		}

		mode = htod32(mode);
		return wlu_iovar_setint(wl, cmd->name, mode);
	}
}

static int
wl_chanim_acs_record(void *wl, cmd_t *cmd, char **argv)
{
	void *ptr = NULL;
	int err = 0, i;
	wl_acs_record_t *result;

	/* need to add to this str if new acs trigger type is added */
	const char *trig_str[] = {"None", "IOCTL", "CHANIM", "TIMER", "BTA"};

	UNUSED_PARAMETER(argv);

	if ((err = wlu_var_getbuf(wl, cmd->name, NULL, 0, &ptr)) < 0)
		return err;

	result = (wl_acs_record_t *) ptr;

	if (!result->count) {
		printf("There is no ACS recorded\n");
		return err;
	}

	printf("current timestamp: %u (ms)\n", result->timestamp);

	printf("Timestamp(ms)  ACS Trigger  Selected Channel  Glitch Count  CCA Count\n");
	for (i = 0; i < result->count; i++) {
		uint8 idx = CHANIM_ACS_RECORD - result->count + i;
		chanim_acs_record_t * record = &result->acs_record[idx];

		record->selected_chspc = wl_chspec_from_driver(record->selected_chspc);

		printf("%10u \t%s \t%10d \t%12d \t%8d\n", record->timestamp,
		   trig_str[record->trigger], wf_chspec_ctlchan(record->selected_chspc),
		   record->glitch_cnt, record->ccastats);
	}
	return err;
}

static int
wl_chanim_stats(void *wl, cmd_t *cmd, char **argv)
{
	wl_chanim_stats_t *stats;
	int stats_size;
	int i, err;
	void *ptr;

	UNUSED_PARAMETER(argv);

	/* get fw chanim stats version */
	stats_size = WL_CHANIM_STATS_FIXED_LEN +
		MAX(sizeof(chanim_stats_t), sizeof(chanim_stats_v2_t));
	stats = (wl_chanim_stats_t *)malloc(stats_size);
	if (stats == NULL) {
		fprintf(stderr, "memory alloc failure\n");
		return BCME_NOMEM;
	}
	memset(stats, 0, stats_size);

	stats->buflen = htod32(stats_size);
	if ((err = wlu_var_getbuf(wl, cmd->name, stats, stats_size, &ptr)) < 0) {
		printf("failed to get chanim results");
		free(stats);
		return err;
	}
	memcpy(stats, ptr, stats_size);

	stats->version = dtoh32(stats->version);
	if (!((stats->version == WL_CHANIM_STATS_VERSION) ||
		(stats->version == WL_CHANIM_STATS_V2))) {
		printf("Sorry, your driver has wl_chanim_stats version %d "
			"but this program supports only version %d and %d.\n",
			stats->version, WL_CHANIM_STATS_V2, WL_CHANIM_STATS_VERSION);
		free(stats);
		return 0;
	}

	/* get fw chanim stats */
	stats->buflen = htod32(stats_size);
	stats->count = htod32(WL_CHANIM_COUNT_ONE);
	if ((err = wlu_var_getbuf(wl, cmd->name, stats, stats_size, &ptr)) < 0) {
		printf("failed to get chanim results");
		free(stats);
		return err;
	}
	memcpy(stats, ptr, stats_size);
	stats->version = dtoh32(stats->version);
	stats->buflen = dtoh32(stats->buflen);
	stats->count = dtoh32(stats->count);

	printf("version: %d \n", stats->version);

	if (stats->version == WL_CHANIM_STATS_VERSION) {
		chanim_stats_t *stats_v3 = (chanim_stats_t *)stats->stats;
		stats_v3->glitchcnt = dtoh32(stats_v3->glitchcnt);
		stats_v3->badplcp = dtoh32(stats_v3->badplcp);
		stats_v3->chanspec = dtoh16(stats_v3->chanspec);
		stats_v3->timestamp = dtoh32(stats_v3->timestamp);

		printf("chanspec tx   inbss   obss   nocat   nopkt   doze     txop     "
				"goodtx  badtx   glitch   badplcp  knoise  idle  timestamp\n");
		printf("0x%4x\t", stats_v3->chanspec);
		for (i = 0; i < CCASTATS_MAX; i++) {
			printf("%d\t", stats_v3->ccastats[i]);
		}
		printf("%d\t%d\t%d\t%d\t%d", stats_v3->glitchcnt, stats_v3->badplcp,
				stats_v3->bgnoise, stats_v3->chan_idle, stats_v3->timestamp);
		printf("\n");
	} else if (stats->version == WL_CHANIM_STATS_V2) {
		chanim_stats_v2_t *stats_v2 = (chanim_stats_v2_t *)stats->stats;
		stats_v2->glitchcnt = dtoh32(stats_v2->glitchcnt);
		stats_v2->badplcp = dtoh32(stats_v2->badplcp);
		stats_v2->chanspec = dtoh16(stats_v2->chanspec);
		stats_v2->timestamp = dtoh32(stats_v2->timestamp);

		printf("chanspec tx   inbss   obss   nocat   nopkt   doze     txop     "
				"goodtx  badtx   glitch   badplcp  knoise  idle  timestamp\n");
		printf("0x%4x\t", stats_v2->chanspec);
		for (i = 0; i < CCASTATS_V2_MAX; i++) {
			 printf("%d\t", stats_v2->ccastats[i]);
		}
		printf("%d\t%d\t%d\t%d\t%d", stats_v2->glitchcnt, stats_v2->badplcp,
				stats_v2->bgnoise, stats_v2->chan_idle, stats_v2->timestamp);
		printf("\n");
	}

	free(stats);
	return (err);
}

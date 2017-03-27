/*
 * Application-specific portion of EAPD
 * (drsdbd)
 *
 * Broadcom Proprietary and Confidential. Copyright (C) 2017,
 * All Rights Reserved.
 * 
 * This is UNPUBLISHED PROPRIETARY SOURCE CODE of Broadcom;
 * the contents of this file may not be disclosed to third parties, copied
 * or duplicated in any form, in whole or in part, without the prior
 * written permission of Broadcom.
 *
 * $Id: drsdbd_eap.c 04-04-2015  arkumark$
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <net/if.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <typedefs.h>
#include <bcmutils.h>
#include <proto/ethernet.h>
#include <proto/eapol.h>
#include <proto/eap.h>
#include <bcmendian.h>
#include <wlutils.h>
#include <eapd.h>
#include <shutils.h>
#include <UdpLib.h>
#include <security_ipc.h>

void drsdbd_app_recv_handler(eapd_wksp_t *nwksp, eapd_cb_t *from,
		uint8 *pData, int *pLen)
{

}

void
drsdbd_app_set_eventmask(eapd_app_t *app)
{
	memset(app->bitvec, 0, sizeof(app->bitvec));

	setbit(app->bitvec, WLC_E_ASSOC_IND);
	setbit(app->bitvec, WLC_E_AUTH_IND);
	setbit(app->bitvec, WLC_E_DISASSOC_IND);
	setbit(app->bitvec, WLC_E_DEAUTH_IND);
	setbit(app->bitvec, WLC_E_DEAUTH);
	setbit(app->bitvec, WLC_E_REASSOC_IND);
	setbit(app->bitvec, WLC_E_PROBREQ_MSG);
	return;
}

int drsdbd_app_init(eapd_wksp_t *nwksp)
{
	int reuse = 1;
	eapd_drsdbd_t *drsdbd;
	eapd_cb_t *cb;
	struct sockaddr_in addr;


	if (nwksp == NULL)
		return -1;

	drsdbd = &nwksp->drsdbd;
	drsdbd->appSocket = -1;

	cb = drsdbd->cb;
	if (cb == NULL) {
		EAPD_INFO("No any DRSDBD application need to run.\n");
		return 0;
	}

	while (cb) {
		EAPD_INFO("drsdbd: init brcm interface %s \n", cb->ifname);
		cb->brcmSocket = eapd_add_brcm(nwksp, cb->ifname);
		if (!cb->brcmSocket)
			return -1;
		/* set this brcmSocket have DRSDBD capability */
		cb->brcmSocket->flag |= EAPD_CAP_DRSDBD;

		cb = cb->next;
	}

	/* appSocket for drsdbd */
	drsdbd->appSocket = socket(AF_INET, SOCK_DGRAM, 0);
	if (drsdbd->appSocket < 0) {
		EAPD_ERROR("UDP Open failed.\n");
		return -1;
	}
	if (setsockopt(drsdbd->appSocket, SOL_SOCKET, SO_REUSEADDR, (char*)&reuse,
		sizeof(reuse)) < 0) {
		EAPD_ERROR("UDP setsockopt failed.\n");
		close(drsdbd->appSocket);
		drsdbd->appSocket = -1;
		return -1;
	}

	memset(&addr, 0, sizeof(struct sockaddr_in));
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = INADDR_ANY;
	addr.sin_port = htons(EAPD_WKSP_DRSDBD_UDP_RPORT);
	if (bind(drsdbd->appSocket, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
		EAPD_ERROR("UDP Bind failed, close drsdbd appSocket %d\n", drsdbd->appSocket);
		close(drsdbd->appSocket);
		drsdbd->appSocket = -1;
		return -1;
	}
	EAPD_INFO("DRSDBD appSocket %d opened\n", drsdbd->appSocket);

	return 0;
}

int drsdbd_app_deinit(eapd_wksp_t *nwksp)
{
	eapd_drsdbd_t *drsdbd;
	eapd_cb_t *cb, *tmp_cb;

	if (nwksp == NULL) {
		EAPD_ERROR("Wrong argument...\n");
		return -1;
	}

	drsdbd = &nwksp->drsdbd;
	cb = drsdbd->cb;
	while (cb) {
		/* close  brcm drvSocket */
		if (cb->brcmSocket) {
			EAPD_INFO("close drsdbd brcmSocket %d\n", cb->brcmSocket->drvSocket);
			eapd_del_brcm(nwksp, cb->brcmSocket);
		}

		tmp_cb = cb;
		cb = cb->next;
		free(tmp_cb);
	}

	/* close  appSocke */
	if (drsdbd->appSocket >= 0) {
		EAPD_INFO("close drsdbd appSocket %d\n", drsdbd->appSocket);
		close(drsdbd->appSocket);
		drsdbd->appSocket = -1;
	}

	return 0;
}

int drsdbd_app_sendup(eapd_wksp_t *nwksp, uint8 *pData, int pLen, char *from)
{
	eapd_drsdbd_t *drsdbd;

	if (nwksp == NULL) {
		EAPD_ERROR("Wrong argument...\n");
		return -1;
	}

	drsdbd = &nwksp->drsdbd;
	if (drsdbd->appSocket >= 0) {
		/* send to drsdbd */
		int sentBytes = 0;
		struct sockaddr_in to;

		to.sin_addr.s_addr = inet_addr(EAPD_WKSP_UDP_ADDR);
		to.sin_family = AF_INET;
		to.sin_port = htons(EAPD_WKSP_DRSDBD_UDP_SPORT);

		sentBytes = sendto(drsdbd->appSocket, pData, pLen, 0,
			(struct sockaddr *)&to, sizeof(struct sockaddr_in));

		if (sentBytes != pLen) {
			EAPD_ERROR("UDP send failed; sentBytes = %d\n", sentBytes);
		}
		else {
			/* EAPD_ERROR("Send %d bytes to drsdbd\n", sentBytes); */
		}
	}
	else {
		EAPD_ERROR("drsdbd appSocket not created\n");
	}
	return 0;
}

#if EAPD_WKSP_AUTO_CONFIG
int drsdbd_app_enabled(char *name)
{
	char value[128], comb[32],  prefix[8];
	char os_name[IFNAMSIZ];
	int unit;

	memset(os_name, 0, sizeof(os_name));

	if (nvifname_to_osifname(name, os_name, sizeof(os_name)))
		return 0;
	if (wl_probe(os_name) ||
		wl_ioctl(os_name, WLC_GET_INSTANCE, &unit, sizeof(unit)))
		return 0;
	if (osifname_to_nvifname(name, prefix, sizeof(prefix)))
		return 0;

	strcat(prefix, "_");
	/* ignore if disabled */
	eapd_safe_get_conf(value, sizeof(value), strcat_r(prefix, "radio", comb));
	if (atoi(value) == 0) {
		EAPD_INFO("DRSDBD:ignored interface %s. radio disabled\n", os_name);
		return 0;
	}

	/* ignore if BSS is disabled */
	eapd_safe_get_conf(value, sizeof(value), strcat_r(prefix, "bss_enabled", comb));
	if (atoi(value) == 0) {
		EAPD_INFO("DRSDBD: ignored interface %s, %s is disabled \n", os_name, comb);
		return 0;
	}

	/* if come to here return enabled */
	return 1;
}
#endif /* EAPD_WKSP_AUTO_CONFIG */

int drsdbd_app_handle_event(eapd_wksp_t *nwksp, uint8 *pData, int Len, char *from)
{
	int type;
	eapd_drsdbd_t *drsdbd;
	eapd_cb_t *cb;
	bcm_event_t *dpkt = (bcm_event_t *) pData;
	wl_event_msg_t *event = &(dpkt->event);

	type = ntohl(event->event_type);

	drsdbd = &nwksp->drsdbd;
	cb = drsdbd->cb;
	while (cb) {
		if (isset(drsdbd->bitvec, type) &&
			!strcmp(cb->ifname, from)) {

			/* prepend ifname,  we reserved IFNAMSIZ length already */
			pData -= IFNAMSIZ;
			Len += IFNAMSIZ;
			memcpy(pData, event->ifname, IFNAMSIZ);

			/* send to drsdbd use cb->ifname */
			drsdbd_app_sendup(nwksp, pData, Len, cb->ifname);
			break;
		}
		cb = cb->next;
	}

	return 0;
}

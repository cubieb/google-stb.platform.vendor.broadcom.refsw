/*
 * VASIP init declarations for Broadcom 802.11
 * Networking Adapter Device Driver.
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

/* vasip code and inits */

extern CONST uint32 d11vasipcode_major;
extern CONST uint32 d11vasipcode_minor;

extern CONST uint32 d11vasip0[];
extern CONST uint d11vasip0sz;

#ifdef VASIP_SPECTRUM_ANALYSIS
extern CONST uint32 d11vasip_tbl[];
extern CONST uint d11vasip_tbl_sz;
#endif

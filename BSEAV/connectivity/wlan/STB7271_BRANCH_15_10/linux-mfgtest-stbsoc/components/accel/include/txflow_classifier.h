/*
 * txflow_classifier.h
 *
 * Common interface for TX Flow Classification module
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
 *
 */
#ifndef _txflow_classifier_h
#define _txflow_classifier_h

#include <typedefs.h>
#include <osl.h>

struct txflow_class_info;	/* opaque type */
typedef struct txflow_class_info txflow_class_info_t;

txflow_class_info_t *txflow_classifier_attach(osl_t *osh);
void txflow_classifier_detach(txflow_class_info_t *flow_classifieri);

#define FLOW_ID_VALID(flowID)	((flowID) > 0 && (flowID) < 0xFFF)

/* The interface type corresponding to dot11 BSS type */
#define IF_TYPE_IBSS	0U
#define IF_TYPE_STA	1U
#define IF_TYPE_AP	2U
#define IF_TYPE_WDS	3U
#define IF_TYPE_NONE	255U

/*
 * Associate an interface type with an interface index.
 *
 * Inputs:
 *	flow_classifieri: flow classifier module handle (returned from txflow_classifier_attach)
 *	ifidx           : the interface index (0 - 15)
 *	if_type         : the interface type associated with the given index (0 - 3)
 */
void txflow_classifier_set_if_type(txflow_class_info_t *flow_classifieri,
                                   uint8 ifidx, uint8 if_type);

/*
 * Add a TX classification (given flowID and packet header)
 *
 * Inputs:
 *	flow_classifieri: flow classifier module handle (returned from txflow_classifier_attach)
 *	txhdr           : packet's tx ether header
 *	ifidx           : packet's interface index
 *	priority        : packet's priority
 *	flowID          : the ID of the flow to add to the classification table
 * Output:
 *	BCME_OK if success, or BCME_NORESOURCE if table is full
 */
int txflow_classifier_add(txflow_class_info_t *flow_classifieri,
                          const uint8 txhdr[], uint8 ifidx, uint8 priority, uint16 flowID);

/*
 * Delete a TX classifiction (given flowID).
 *
 * Inputs:
 *	flow_classifieri: flow classifier module handle (returned from txflow_classifier_attach)
 *	flowID          : the ID of the flow that we no longer use
 * Output:
 *	BCME_OK or flowID BCME_NOTFOUND
 */
int txflow_classifier_delete(txflow_class_info_t *flow_classifieri, uint16 flowID);


/*
 * Find a matching Flow from the given packet (based on match bitmask)
 *
 * Inputs:
 *	flow_classifieri: flow classifier module handle (returned from txflow_classifier_attach)
 *	txhdr           : packet's tx ether header
 *	ifidx           : packet's interface index
 *	priority        : packet's priority
 * Output:
 *	flowID          : if BCME_OK, the ID of the flow if found match in the classification table
 *	BCME_OK or BCME_NOTFOUND
 */
int txflow_classifier_get_flow(txflow_class_info_t *flow_classifieri,
                               const uint8 txhdr[], uint8 ifidx, uint8 priority, uint16 *flowID);

#if defined(BCMDBG) || defined(BCMDBG_DUMP)
/*
 * Dump the internals (in human readable form) to the given buffer
 *
 * Inputs:
 *	flow_classifieri: flow classifier module handle (returned from txflow_classifier_attach)
 *	b               : string buffer to fill with info (need to use bcm_binit before use)
 */
void txflow_classifier_dump(txflow_class_info_t *flow_classifieri, struct bcmstrbuf *b);
#endif /* BCMDBG || BCMDBG_DUMP */

#endif /* _txflow_classifier_h */

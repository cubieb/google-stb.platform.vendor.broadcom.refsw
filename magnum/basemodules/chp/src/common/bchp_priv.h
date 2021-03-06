/***************************************************************************
 *     Copyright (c) 2003-2013, Broadcom Corporation
 *     All Rights Reserved
 *     Confidential Property of Broadcom Corporation
 *
 *  THIS SOFTWARE MAY ONLY BE USED SUBJECT TO AN EXECUTED SOFTWARE LICENSE
 *  AGREEMENT  BETWEEN THE USER AND BROADCOM.  YOU HAVE NO RIGHT TO USE OR
 *  EXPLOIT THIS MATERIAL EXCEPT SUBJECT TO THE TERMS OF SUCH AN AGREEMENT.
 *
 * $brcm_Workfile: $
 * $brcm_Revision: $
 * $brcm_Date: $
 *
 * Module Description:
 *
 * Revision History:
 *
 * $brcm_Log: $
 *
 ***************************************************************************/
#ifndef BCHP_PRIV_H__
#define BCHP_PRIV_H__

#include "bstd.h"
#include "bchp.h"
#include "breg_mem.h"
#include "bkni_multi.h"
#include "bchp_avs.h"

#ifdef __cplusplus
extern "C" {
#endif

/***************************************************************************
Summary:
	This typedef defines the pointer to chip Close function.

Description:
	If the close function pointer is used, then open function pointer must
	also exist.

See Also:
	BCHP_Close()

****************************************************************************/
typedef BERR_Code (*BCHP_CloseFunc)(
	BCHP_Handle hChip						/* [in] Chip handle */
	);

/***************************************************************************
Summary:
	This typedef defines the pointer to chip GetChipInfo function.

Description:
	This function pointer is provided for chips that requires specific needs
	when BCHP_GetChipInfo() is called.

See Also:
	BCHP_GetChipInfo()

****************************************************************************/
typedef BERR_Code (*BCHP_GetChipInfoFunc)(
	const BCHP_Handle hChip,				/* [in] Chip handle */
	uint16_t *pChipId,						/* [out] Chip Id */
	uint16_t *pChipRev						/* [out] Chip Rev. */
	);

/***************************************************************************
Summary:
	This typedef defines the pointer to chip GetFeature function.

Description:
	This function pointer is provided for chips that have specific features
	that need to be queried.

See Also:
	BCHP_GetFeature()

****************************************************************************/
typedef BERR_Code (*BCHP_GetFeatureFunc)(
	const BCHP_Handle hChip,				/* [in] Chip handle. */
	const BCHP_Feature eFeature,			/* [in] Feature to be queried. */
	void *pFeatureValue						/* [out] Feature value .*/
	);

/***************************************************************************
Summary:
	This typedef defines the pointer to chip MonitorPvt function.

Description:
	This function pointer is provided for chips that have AVS

See Also:
	BCHP_MonitorPvt()

****************************************************************************/
typedef void (*BCHP_MonitorPvtFunc)(
	const BCHP_Handle hChip,	    /* [in] Chip handle. */
	BCHP_AvsSettings *pSettings     /* [in] AVS settings. */
	);


/***************************************************************************
Summary:
	This typedef defines the pointer to chip GetAvsData function.

Description:
	This function pointer is provided for chips that have AVS.

See Also:
	BCHP_GetAvsData()

****************************************************************************/
typedef BERR_Code (*BCHP_GetAvsDataFunc)(
	const BCHP_Handle hChip,	    /* [in] Chip handle */
	BCHP_AvsData *pData             /* [out] pointer to location to return data */
	);

/***************************************************************************
Summary:
	This typedef defines the pointer to chip StandbyMode function.

Description:
	This function pointer is provided for chips that support changing power modes.

See Also:
	BCHP_StandbyMode()

****************************************************************************/
typedef BERR_Code (*BCHP_StandbyModeFunc)(
	const BCHP_Handle hChip,  /* [in] Chip handle. */
	bool activate             /* [in] true to activate standby mode */
	);


typedef struct BCHP_PWR_P_Context {
    BKNI_MutexHandle lock; /* for internal sync */

    unsigned *pubRefcnt;   /* public refcnt is non-recursive and enforces that you only release
                              what you've previously acquired. only applies to nonleaf nodes */

    unsigned *privRefcnt;  /* private refcnt is recursive. applies to all nodes */
    bool *init;            /* every HW node must be initialized before it can be acquired/released.
                              initialized means powered down */
    bool initComplete;     /* true if BCHP_PWR_P_Init() has completed */
    bool *magnumCtrl;      /* true if MAGNUM_CONTROLLED HW_ node */
    bool *sharedCtrl;      /* true if HW_ node has at least one HW_ node parent that is
                              MAGNUM_CONTROLLED and one that is not */
    bool *secureCtrl;      /* true if SECURE_ACCESS HW_ node */
} BCHP_PWR_P_Context;

typedef struct BCHP_PWR_P_Context *BCHP_PWR_Handle;
typedef struct BCHP_AVS_P_Context *BCHP_AVS_Handle;

#if BCHP_UNIFIED_IMPL
struct BCHP_P_Info
{
    uint32_t      ulChipFamilyIdReg; /* family id including rev */
};
BCHP_Handle BCHP_P_Open(const BCHP_OpenSettings *pSettings, const struct BCHP_P_Info *pChipInfo);
#endif

BDBG_OBJECT_ID_DECLARE(BCHP);
typedef struct BCHP_P_Context
{
    BDBG_OBJECT(BCHP)
	BCHP_MemoryInfo memoryInfo;
	bool memoryInfoSet;
	BREG_Handle regHandle;					/* register handle */
	BCHP_CloseFunc pCloseFunc;				/* ptr to Close func. */
	BCHP_GetChipInfoFunc pGetChipInfoFunc;	/* ptr to GetChipInfo func. */
	BCHP_GetFeatureFunc pGetFeatureFunc;	/* ptr to GetFeature func. */
	BCHP_MonitorPvtFunc pMonitorPvtFunc;	/* ptr to MonitorPvtFunc func. */
	BCHP_GetAvsDataFunc pGetAvsDataFunc;	/* ptr to GetAvsDataFunc func. */
	BCHP_StandbyModeFunc pStandbyModeFunc;  /* ptr to StandbyModeFunc func. */
	BCHP_PWR_Handle pwrManager;				/* BCHP_PWR handle */
	BCHP_AVS_Handle avsHandle;				/* BCHP_AVS handle */
	BCHP_Info info;
#if BCHP_UNIFIED_IMPL
	const struct BCHP_P_Info *pChipInfo;
	BCHP_P_AvsHandle hAvsHandle;
	BCHP_OpenSettings openSettings;
#else
	void *chipHandle;						/* Chip Specific handle */
	bool infoSet; /* there's no generic open, but every chip does memset(0), so a bool tells if 'info' is set */
#endif
} BCHP_P_Context;

typedef enum BCHP_PWR_P_ResourceType {
    BCHP_PWR_P_ResourceType_eLeaf,      /* a leaf node is always a HW_ node */
    BCHP_PWR_P_ResourceType_eNonLeaf,   /* a non-leaf node that is not a HW_ node */
    BCHP_PWR_P_ResourceType_eNonLeafHw, /* a non-leaf node that is also a HW_ node.
                                          these nodes can only have other HW_ nodes as dependencies */
    BCHP_PWR_P_ResourceType_eMux,
    BCHP_PWR_P_ResourceType_eDiv
} BCHP_PWR_P_ResourceType;

struct BCHP_PWR_P_Resource {
    BCHP_PWR_P_ResourceType type;
    unsigned id; /* the #define number */
    const char *name;
};

typedef struct BCHP_PWR_P_Resource BCHP_PWR_P_Resource;

typedef struct BCHP_PWR_P_DivTable {
    unsigned mult;
    unsigned prediv;
    unsigned postdiv;
} BCHP_PWR_P_DivTable;

typedef struct BCHP_PWR_P_FreqMap {
    unsigned id; /* Resource id */
    const BCHP_PWR_P_DivTable *pDivTable;
} BCHP_PWR_P_FreqMap;


BERR_Code BCHP_PWR_Open(
    BCHP_PWR_Handle *pHandle, /* [out] */
    BCHP_Handle chp           /* [in] */
    );

void BCHP_PWR_Close(
    BCHP_PWR_Handle handle   /* [in] */
    );

BERR_Code BCHP_P_GetDefaultFeature
    ( const BCHP_Handle                hChip,
      const BCHP_Feature               eFeature,
      void                            *pFeatureValue );

#ifdef __cplusplus
}
#endif

#endif /*BCHP_PRIV_H__*/


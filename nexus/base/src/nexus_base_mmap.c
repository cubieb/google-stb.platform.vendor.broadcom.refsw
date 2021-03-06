/***************************************************************************
*     (c)2008-2013 Broadcom Corporation
*
*  This program is the proprietary software of Broadcom Corporation and/or its licensors,
*  and may only be used, duplicated, modified or distributed pursuant to the terms and
*  conditions of a separate, written license agreement executed between you and Broadcom
*  (an "Authorized License").  Except as set forth in an Authorized License, Broadcom grants
*  no license (express or implied), right to use, or waiver of any kind with respect to the
*  Software, and Broadcom expressly reserves all rights in and to the Software and all
*  intellectual property rights therein.  IF YOU HAVE NO AUTHORIZED LICENSE, THEN YOU
*  HAVE NO RIGHT TO USE THIS SOFTWARE IN ANY WAY, AND SHOULD IMMEDIATELY
*  NOTIFY BROADCOM AND DISCONTINUE ALL USE OF THE SOFTWARE.
*
*  Except as expressly set forth in the Authorized License,
*
*  1.     This program, including its structure, sequence and organization, constitutes the valuable trade
*  secrets of Broadcom, and you shall use all reasonable efforts to protect the confidentiality thereof,
*  and to use this information only in connection with your use of Broadcom integrated circuit products.
*
*  2.     TO THE MAXIMUM EXTENT PERMITTED BY LAW, THE SOFTWARE IS PROVIDED "AS IS"
*  AND WITH ALL FAULTS AND BROADCOM MAKES NO PROMISES, REPRESENTATIONS OR
*  WARRANTIES, EITHER EXPRESS, IMPLIED, STATUTORY, OR OTHERWISE, WITH RESPECT TO
*  THE SOFTWARE.  BROADCOM SPECIFICALLY DISCLAIMS ANY AND ALL IMPLIED WARRANTIES
*  OF TITLE, MERCHANTABILITY, NONINFRINGEMENT, FITNESS FOR A PARTICULAR PURPOSE,
*  LACK OF VIRUSES, ACCURACY OR COMPLETENESS, QUIET ENJOYMENT, QUIET POSSESSION
*  OR CORRESPONDENCE TO DESCRIPTION. YOU ASSUME THE ENTIRE RISK ARISING OUT OF
*  USE OR PERFORMANCE OF THE SOFTWARE.
*
*  3.     TO THE MAXIMUM EXTENT PERMITTED BY LAW, IN NO EVENT SHALL BROADCOM OR ITS
*  LICENSORS BE LIABLE FOR (i) CONSEQUENTIAL, INCIDENTAL, SPECIAL, INDIRECT, OR
*  EXEMPLARY DAMAGES WHATSOEVER ARISING OUT OF OR IN ANY WAY RELATING TO YOUR
*  USE OF OR INABILITY TO USE THE SOFTWARE EVEN IF BROADCOM HAS BEEN ADVISED OF
*  THE POSSIBILITY OF SUCH DAMAGES; OR (ii) ANY AMOUNT IN EXCESS OF THE AMOUNT
*  ACTUALLY PAID FOR THE SOFTWARE ITSELF OR U.S. $1, WHICHEVER IS GREATER. THESE
*  LIMITATIONS SHALL APPLY NOTWITHSTANDING ANY FAILURE OF ESSENTIAL PURPOSE OF
*  ANY LIMITED REMEDY.
*
* $brcm_Workfile: $
* $brcm_Revision: $
* $brcm_Date: $
*
* API Description:
*
* Revision History:
*
* $brcm_Log: $
*
***************************************************************************/
#include "nexus_base.h"
#include "nexus_base_mmap.h"

BDBG_MODULE(nexus_base_mmap);

typedef struct NEXUS_P_MemoryMap {
    size_t length;
    NEXUS_Addr offset;
    bool fake_uncached;
    bool fake_cached;
    void *cached;
    void *uncached;
} NEXUS_P_MemoryMap;

static NEXUS_P_MemoryMap g_NEXUS_P_MemoryMap[16];

#define B_IS_INTERSECT(off1, len1, off2, len2) ((off1) <= ((off2)+(len2)-1) && (off2) <= ((off1)+(len1)-1))

bool NEXUS_P_CpuAccessibleAddress( const void *address )
{
/* TODO: for nfe image, kernel mode must be passed in as runtime param. see also nexus_platform_core.c. */
#if NEXUS_BASE_OS_ucos_ii || NEXUS_BASE_OS_no_os || NEXUS_BASE_OS_wince || B_REFSW_SYSTEM_MODE_CLIENT
    /* no fake addressing. all virtual addresses are mmapped; therefore, accessible. */
    BSTD_UNUSED(address);
    return true;
#elif NEXUS_MODE_driver || NEXUS_BASE_OS_linuxkernel
    /* kernel mode address is valid */
    return ((unsigned)address >= NEXUS_KERNEL_MODE_VIRTUAL_ADDRESS_BASE);
#else
    /* user mode address is valid */
    return ((unsigned long)address < NEXUS_KERNEL_MODE_VIRTUAL_ADDRESS_BASE);
#endif
}

NEXUS_Error
NEXUS_P_AddMap(NEXUS_Addr offset, void *cached, void *uncached, size_t length)
{
    unsigned i;

#if !NEXUS_BASE_OS_linuxemu
    /* offset==0 is normal in emulation environments */
    if (offset==0) {
        return BERR_TRACE(BERR_INVALID_PARAMETER);
    }
#endif
    if (uncached==NULL && cached==NULL) {
        return BERR_TRACE(BERR_INVALID_PARAMETER);
    }

    for(i=0;i<sizeof(g_NEXUS_P_MemoryMap)/sizeof(*g_NEXUS_P_MemoryMap);i++) {
        NEXUS_P_MemoryMap *map = g_NEXUS_P_MemoryMap+i;
        if(map->length==0) {
            BDBG_MSG(("NEXUS_P_AddMap offset=" BDBG_UINT64_FMT " length=%#x(%uMBytes) cached_addr=%p..%p uncached_addr=%p..%p",
                BDBG_UINT64_ARG(offset), (unsigned)length, (unsigned)(length/(1024*1024)), cached, (uint8_t *)cached + length, uncached, (uint8_t *)uncached + length));
            map->length = length;
            map->offset = offset;
            map->cached = cached;
            map->fake_cached = !NEXUS_P_CpuAccessibleAddress(cached);
            map->uncached = uncached;
            map->fake_uncached = !NEXUS_P_CpuAccessibleAddress(uncached);
            return BERR_SUCCESS;
        }
        if(  B_IS_INTERSECT(offset,length, map->offset,map->length) ||
             B_IS_INTERSECT((uint8_t *)cached, length, (uint8_t *)map->cached, map->length) ||
            (uncached &&  B_IS_INTERSECT((uint8_t *)uncached, length, (uint8_t *)map->uncached, map->length)) ||
             B_IS_INTERSECT((uint8_t *)cached, length, (uint8_t *)map->uncached, map->length) ||
             (uncached && B_IS_INTERSECT((uint8_t *)uncached, length, (uint8_t *)map->cached, map->length)) 
             ) {
            BDBG_ERR(("duplicated map: (" BDBG_UINT64_FMT ",%p,%p):%u and (" BDBG_UINT64_FMT ",%p,%p):%u %s %s %s", BDBG_UINT64_ARG(offset), cached, uncached, (unsigned)length, BDBG_UINT64_ARG(map->offset), map->cached, map->uncached, (unsigned)map->length, B_IS_INTERSECT(offset,length, map->offset,map->length)?"O":"", B_IS_INTERSECT((uint8_t *)cached, length, (uint8_t *)map->cached, map->length)?"C":"",  B_IS_INTERSECT((uint8_t *)uncached, length, (uint8_t *)map->uncached, map->length)?"U":""));
            /* BDBG_ASSERT(0); */
        }
    }
    return BERR_TRACE(NEXUS_UNKNOWN);
}

NEXUS_Addr
NEXUS_AddrToOffset(const void *addr)
{
    unsigned i;
    const NEXUS_P_MemoryMap *map = g_NEXUS_P_MemoryMap;
    for(i=0;i<sizeof(g_NEXUS_P_MemoryMap)/sizeof(*g_NEXUS_P_MemoryMap);i++) {
        if(map[i].length==0) {
            break;
        }
        if( (uint8_t *)addr>=(uint8_t *)map[i].cached &&
            (uint8_t *)addr<((uint8_t *)map[i].cached + map[i].length) &&
            map[i].cached != NULL
            ) {
            return map[i].offset + ((uint8_t *)addr - (uint8_t *)map[i].cached);
        }
        if( (uint8_t *)addr>=(uint8_t *)map[i].uncached &&
            (uint8_t *)addr<((uint8_t *)map[i].uncached + map[i].length) &&
            map[i].uncached != NULL) {
            return map[i].offset + ((uint8_t *)addr - (uint8_t *)map[i].uncached);
        }
    }
    BDBG_WRN(("NEXUS_AddrToOffset: unknown address %#lx", (unsigned long)addr));
    return 0;
}

NEXUS_AddrType NEXUS_GetAddrType(const void *addr)
{
    unsigned i;
    const NEXUS_P_MemoryMap *map = g_NEXUS_P_MemoryMap;
    for(i=0;i<sizeof(g_NEXUS_P_MemoryMap)/sizeof(*g_NEXUS_P_MemoryMap);i++) {
        if(map[i].length==0) {
            break;
        }
        if( (uint8_t *)addr>=(uint8_t *)map[i].cached &&
            (uint8_t *)addr<((uint8_t *)map[i].cached + map[i].length) &&
            map[i].cached != NULL
            ) {
            return map[i].fake_cached?NEXUS_AddrType_eFake:NEXUS_AddrType_eCached;
        }
        if( (uint8_t *)addr>=(uint8_t *)map[i].uncached &&
            (uint8_t *)addr<((uint8_t *)map[i].uncached + map[i].length) &&
            map[i].uncached != NULL) {
            return map[i].fake_uncached?NEXUS_AddrType_eFake:NEXUS_AddrType_eUncached;
        }
    }
    return NEXUS_AddrType_eUnknown;
}

void *
NEXUS_OffsetToCachedAddr(NEXUS_Addr offset)
{
    unsigned i;
    const NEXUS_P_MemoryMap *map = g_NEXUS_P_MemoryMap;
    for(i=0;i<sizeof(g_NEXUS_P_MemoryMap)/sizeof(*g_NEXUS_P_MemoryMap);i++) {
        if(map[i].length==0) {
            break;
        }
        if( offset>=map[i].offset &&
            offset<(map[i].offset + map[i].length)) {
            uint8_t *addr;

            if(map[i].cached) {
                addr = map[i].cached;
            } else {
                addr = map[i].uncached;
            }
            return addr + (offset - map[i].offset);
        }
    }
    BDBG_WRN(("NEXUS_OffsetToCachedAddr: unknown address " BDBG_UINT64_FMT "", BDBG_UINT64_ARG(offset)));
    for(i=0;i<sizeof(g_NEXUS_P_MemoryMap)/sizeof(*g_NEXUS_P_MemoryMap);i++) {
        if(map[i].length==0) {
            break;
        }
        BDBG_LOG(("%u: " BDBG_UINT64_FMT " -> " BDBG_UINT64_FMT ":%u", i, BDBG_UINT64_ARG(offset), BDBG_UINT64_ARG(map[i].offset), (unsigned)map[i].length));
    }
    return NULL;
}

void *
NEXUS_OffsetToUncachedAddr(NEXUS_Addr offset)
{
    unsigned i;
    const NEXUS_P_MemoryMap *map = g_NEXUS_P_MemoryMap;

    for(i=0;i<sizeof(g_NEXUS_P_MemoryMap)/sizeof(*g_NEXUS_P_MemoryMap);i++) {
        if(map[i].length==0) {
            break;
        }
        if( offset>=map[i].offset &&
            offset<(map[i].offset + map[i].length)) {
            return (uint8_t *)map[i].uncached + (offset - map[i].offset);
        }
    }
    BDBG_WRN(("NEXUS_OffsetToUncachedAddr: unknown address %#lx", (unsigned long)offset));
    return NULL;
}

void
NEXUS_P_MapInit(void)
{
    unsigned i;
    NEXUS_P_MemoryMap *map = g_NEXUS_P_MemoryMap;
    for(i=0;i<sizeof(g_NEXUS_P_MemoryMap)/sizeof(*g_NEXUS_P_MemoryMap);i++) {
        map[i].length = 0;
        map[i].offset = 0;
        map[i].cached = NULL;
        map[i].uncached = NULL;
    }
    return ;
}


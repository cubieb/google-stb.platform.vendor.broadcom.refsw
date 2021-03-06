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
 * Implementatation of the Magnum KNI for user space Linux applications.
 *
 * Revision History:
 *
 * $brcm_Log: $ *
 * 
 ***************************************************************************/

#include "bstd.h"
#include "bkni.h"
#include "bkni_multi.h"
#include "bkni_metrics.h"
#include "bkni_event_group.h"
#include "blst_list.h"
#include "blst_queue.h"

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <errno.h>
#include <pthread.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <sys/time.h>

#if defined(__mips__) && defined(B_REFSW_ANDROID)
/* Android's bionic C on MIPS does not have NPTL */
#else
#ifndef HAS_NPTL
/* may require -lrt on older toolchains */
#define HAS_NPTL 1
#endif
#endif

BDBG_MODULE(kernelinterface);

BDBG_OBJECT_ID(BKNI_EventGroup);
BDBG_OBJECT_ID(BKNI_Event);
BDBG_OBJECT_ID(BKNI_Mutex);

static unsigned long BKNI_P_GetMicrosecondTick(void);
static int BKNI_P_SetTargetTime(struct timespec *target, int timeoutMsec);

#if BKNI_DEBUG_MUTEX_TRACKING
static void BKNI_P_ForceReleaseMutex(void *);
typedef struct BKNI_P_HeartBeatTimer  {
    pthread_t thread;
    pthread_mutex_t lock;
    pthread_cond_t cond;
    bool exit;
    bool started;
} BKNI_P_HeartBeatTimer;

static BERR_Code BKNI_P_HeartBeatTimer_Init(BKNI_P_HeartBeatTimer *timer)
{
    pthread_condattr_t attr;
    int rc;
    
    rc = pthread_condattr_init(&attr);
    if (rc!=0) {
        return BERR_TRACE(BERR_OS_ERROR);
    }

#if HAS_NPTL
    rc = pthread_condattr_setclock(&attr, CLOCK_MONOTONIC);
    if (rc!=0) {
        return BERR_TRACE(BERR_OS_ERROR);
    }
#endif

    timer->exit = false;
    timer->started = false;
    pthread_mutex_init(&timer->lock, NULL);
    pthread_cond_init(&timer->cond, &attr);
    return BERR_SUCCESS;
}

static void BKNI_P_HeartBeatTimer_Uninit(BKNI_P_HeartBeatTimer *timer)
{
    if(timer->started) {
        timer->exit = true;
        pthread_cond_signal(&timer->cond);
        pthread_join(timer->thread, NULL);
    }
    pthread_cond_destroy(&timer->cond);
    pthread_mutex_destroy(&timer->lock);
    return;
}

static void *BKNI_P_HeartBeatTimer_Thread(BKNI_P_HeartBeatTimer *h, void (*timer)(void), unsigned delayms)
{
    int rc;
    rc = pthread_mutex_lock(&h->lock);
    BDBG_ASSERT(rc == 0);
    h->started = true;
    for(;;) {
        struct timespec target;
        BKNI_P_SetTargetTime(&target, (int)delayms);
        pthread_cond_timedwait(&h->cond, &h->lock, &target);
        if(h->exit) {
            break;
        }
        timer();
    }
    pthread_mutex_unlock(&h->lock);
    return NULL;
}
#endif /* if BKNI_DEBUG_MUTEX_TRACKING */

#define BKNI_P_MUTEXTRACKING_HEARTBEAT_TYPE BKNI_P_HeartBeatTimer
#define BKNI_P_MUTEXTRACKING_HEARTBEAT_INIT(x) BKNI_P_HeartBeatTimer_Init(x)
#define BKNI_P_MUTEXTRACKING_HEARTBEAT_UNINIT(x) BKNI_P_HeartBeatTimer_Uninit(x)
#define BKNI_P_MUTEXTRACKING_HEARTBEAT_LOCK(x) pthread_mutex_lock(&(x)->lock)
#define BKNI_P_MUTEXTRACKING_HEARTBEAT_UNLOCK(x) pthread_mutex_unlock(&(x)->lock)
#define BKNI_P_MUTEXTRACKING_HEARTBEAT_DECLARE(x,heartBeat,delayms) static void *BKNI_P_MutexTracking_HeartBeatThread(void *h) {return BKNI_P_HeartBeatTimer_Thread(h, x, delayms);}
#define BKNI_P_MUTEXTRACKING_HEARTBEAT_START(x) pthread_create(&(x)->thread, NULL, BKNI_P_MutexTracking_HeartBeatThread, x)
#define BKNI_P_MUTEXTRACKING_TICK_TYPE  unsigned long
#define BKNI_P_MUTEXTRACKING_TICK_GET(x) *(x) = BKNI_P_GetMicrosecondTick()
#define BKNI_P_MUTEXTRACKING_TICK_DIFF_MS(x1,x2) (*(x1) - *(x2))/1000
#define BKNI_P_MUTEXTRACKING_FORCE_RELEASE(x) BKNI_P_ForceReleaseMutex(x)

#include "bkni_mutex_tracking.inc"

struct BKNI_MutexObj
{
    BKNI_P_MutexTracking tracking; /* must be first */
    BDBG_OBJECT(BKNI_Mutex)
    pthread_mutex_t mutex;
    BKNI_MutexSettings settings;
};

#if BKNI_DEBUG_MUTEX_TRACKING
static void BKNI_P_ForceReleaseMutex(void *x)
{
   pthread_mutex_unlock(&((struct BKNI_MutexObj *)x)->mutex);
   return;
}
#endif

void * BKNI_Malloc_tagged(size_t size, const char *file, unsigned line);
void BKNI_Free_tagged(void *ptr, const char *file, unsigned line);


struct BKNI_GroupObj
{
    BDBG_OBJECT(BKNI_EventGroup)
    BLST_D_HEAD(group, BKNI_EventObj) members;
    pthread_mutex_t lock;            /* mutex for protecting signal and conditional variables */
    pthread_cond_t  cond;           /* condition to wake up from event*/
};

struct BKNI_EventObj
{
    BDBG_OBJECT(BKNI_Event)
    BLST_D_ENTRY(BKNI_EventObj) list;
    struct BKNI_GroupObj *group;
    pthread_mutex_t lock;            /* mutex for protecting signal and conditional variables */
    pthread_cond_t  cond;           /* condition to wake up from event*/
    bool signal;
};

static pthread_mutex_t g_csMutex = PTHREAD_MUTEX_INITIALIZER;

#if BDBG_DEBUG_BUILD

static pthread_t g_csOwner;

#define SET_CRITICAL() do { g_csOwner = pthread_self(); } while (0)
#define CLEAR_CRITICAL() do { g_csOwner = (pthread_t)0; } while (0)
#define CHECK_CRITICAL() ( g_csOwner == pthread_self() )

#define ASSERT_CRITICAL() do \
{\
    if ( !CHECK_CRITICAL() )\
    {\
        BDBG_P_PrintString("Error, must be in critical section to call %s\n", __FUNCTION__);\
        BKNI_Fail();\
    }\
} while (0)

#define ASSERT_NOT_CRITICAL() do \
{\
    if ( CHECK_CRITICAL() )\
    {\
        BDBG_P_PrintString("Error, must not be in critical section to call %s\n", __FUNCTION__);\
        BKNI_Fail();\
    }\
} while (0)

#else

#define ASSERT_CRITICAL() (void)0
#define ASSERT_NOT_CRITICAL() (void)0
#define SET_CRITICAL() (void)0
#define CLEAR_CRITICAL() (void)0
#define CHECK_CRITICAL() 0

#endif

#if BKNI_TRACK_MALLOCS
static pthread_mutex_t g_alloc_state_mutex = PTHREAD_MUTEX_INITIALIZER;
#endif

#define B_TRACK_ALLOC_LOCK() pthread_mutex_lock(&g_alloc_state_mutex)
#define B_TRACK_ALLOC_UNLOCK() pthread_mutex_unlock(&g_alloc_state_mutex)
#define B_TRACK_ALLOC_ALLOC(size) malloc(size)
#define B_TRACK_ALLOC_FREE(ptr) free(ptr)
#define B_TRACK_ALLOC_OS "linuxuser"

#include "bkni_track_mallocs.inc"

#if BKNI_DEBUG_CS_TIMING
#define BKNI_DEBUG_CS_TIMING_TIME_NODES 16
/* microseconds */
#define BKNI_P_STATS_TIME_THRESHOLD 2

BLST_Q_HEAD(BKNI_P_TimeList, BKNI_P_TimeNode);
typedef struct BKNI_P_TimeList BKNI_P_TimeList;

typedef struct BKNI_P_TimeNodeData {
    unsigned long time;
    unsigned line;
    const char *file;
} BKNI_P_TimeNodeData;

typedef struct BKNI_P_TimeNode {
    BLST_Q_ENTRY(BKNI_P_TimeNode) link;
    BKNI_P_TimeNodeData data;
} BKNI_P_TimeNode;

typedef struct BKNI_P_TimeAggregate {
    unsigned count;
    unsigned long totalTime;
    unsigned long maxTime;
} BKNI_P_TimeAggregate;

/* set it to zero to disable stats */
#define BKNI_P_STATS_CS_SITES   256

#if BKNI_P_STATS_CS_SITES
#include "blst_aa_tree.h"

typedef struct BKNI_P_SiteKey {
    const char *file;
    unsigned line;
    long totalTime;
    unsigned count;
    unsigned long maxTime;
} BKNI_P_SiteKey;

BLST_AA_TREE_HEAD(BKNI_P_SiteInstanceTree, KNI_P_SiteNode);
BLST_AA_TREE_HEAD(BKNI_P_SiteTotalTimeTree, KNI_P_SiteNode);

typedef struct BKNI_P_SiteNode {
    BKNI_P_SiteKey key;
    BLST_AA_TREE_ENTRY(BKNI_P_SiteInstanceTree) instanceNode;
    BLST_AA_TREE_ENTRY(BKNI_P_SiteTotalTimeTree) totalTimeNode;
} BKNI_P_SiteNode;

static int BKNI_P_SiteNode_InstanceCompare(const BKNI_P_SiteNode *node, const BKNI_P_SiteKey *key)
{
    if(node->key.file != key->file) { return node->key.file > (char *)key->file? 1 : -1;}
    else return (int)node->key.line- (int)key->line;
}

BLST_AA_TREE_GENERATE_INSERT(BKNI_P_SiteInstanceTree, const BKNI_P_SiteKey *, BKNI_P_SiteNode, instanceNode, BKNI_P_SiteNode_InstanceCompare)
BLST_AA_TREE_GENERATE_FIND(BKNI_P_SiteInstanceTree, const BKNI_P_SiteKey *, BKNI_P_SiteNode, instanceNode, BKNI_P_SiteNode_InstanceCompare)
BLST_AA_TREE_GENERATE_REMOVE(BKNI_P_SiteInstanceTree, BKNI_P_SiteNode, instanceNode)

static int BKNI_P_SiteNode_TotalTimeCompare(const BKNI_P_SiteNode *node, const BKNI_P_SiteKey *key)
{
    if(node->key.totalTime != key->totalTime)  {return node->key.totalTime > key->totalTime ? 1 : -1;}
    else return BKNI_P_SiteNode_InstanceCompare(node, key);
}

BLST_AA_TREE_GENERATE_INSERT(BKNI_P_SiteTotalTimeTree, const BKNI_P_SiteKey *, BKNI_P_SiteNode, totalTimeNode, BKNI_P_SiteNode_TotalTimeCompare)
BLST_AA_TREE_GENERATE_REMOVE(BKNI_P_SiteTotalTimeTree, BKNI_P_SiteNode, totalTimeNode)
BLST_AA_TREE_GENERATE_FIRST(BKNI_P_SiteTotalTimeTree, BKNI_P_SiteNode, totalTimeNode)
BLST_AA_TREE_GENERATE_LAST(BKNI_P_SiteTotalTimeTree, BKNI_P_SiteNode, totalTimeNode)
BLST_AA_TREE_GENERATE_NEXT(BKNI_P_SiteTotalTimeTree, BKNI_P_SiteNode, totalTimeNode)

#endif /* BKNI_P_STATS_CS_SITES */


typedef struct BKNI_P_StatsState {
    struct {
        BKNI_P_TimeList list;
        BKNI_P_TimeAggregate aggregate;
        struct {
            BKNI_P_TimeAggregate aggregate;
            BKNI_P_TimeNodeData data[BKNI_DEBUG_CS_TIMING_TIME_NODES]; /* same as above but without linked list */
        } printCopy;
        BKNI_P_TimeNode nodes[BKNI_DEBUG_CS_TIMING_TIME_NODES];
    }csTime;
#if BKNI_P_STATS_CS_SITES
    struct {
        struct BKNI_P_SiteInstanceTree instanceTree;
        struct BKNI_P_SiteTotalTimeTree totalTimeTree;
        unsigned nextFree; /* indicates next free node that could be inserted into the trees */
        struct {
            BKNI_P_SiteKey data[BKNI_DEBUG_CS_TIMING_TIME_NODES];  /* that's right use BKNI_DEBUG_CS_TIMING_TIME_NODES (expected to be small amount of nodes used for printing) */
        } printCopy;
        BKNI_P_SiteNode nodes[BKNI_P_STATS_CS_SITES];
    } csSites;
#endif
} BKNI_P_StatsState;
static BKNI_P_StatsState g_BKNI_P_StatsState;

static void BKNI_P_StatsState_Init(void)
{
    unsigned i;
    BKNI_P_StatsState *state = &g_BKNI_P_StatsState;

    BKNI_Memset(state, 0, sizeof(*state));
    BLST_Q_INIT(&state->csTime.list);
    state->csTime.aggregate.count = 0;
    state->csTime.aggregate.totalTime = 0;
    state->csTime.aggregate.maxTime = 0;
    for(i=0;i<BKNI_DEBUG_CS_TIMING_TIME_NODES;i++) {
        BKNI_P_TimeNode *node = state->csTime.nodes+i;
        node->data.line = 0;
        node->data.time = 0;
        BLST_Q_INSERT_TAIL(&state->csTime.list, node, link);
    }
#if BKNI_P_STATS_CS_SITES
    BLST_AA_TREE_INIT(BKNI_P_SiteInstanceTree, &state->csSites.instanceTree);
    BLST_AA_TREE_INIT(BKNI_P_SiteTotalTimeTree, &state->csSites.totalTimeTree);
    state->csSites.nextFree = 0;
#endif
}

static void BKNI_P_TimeList_ReplaceSorted(BKNI_P_TimeList *list, BKNI_P_TimeNode *node)
{
    BKNI_P_TimeNode *n;
    unsigned long time = node->data.time;

    BDBG_ASSERT(node == BLST_Q_FIRST(list));
    BLST_Q_REMOVE_HEAD(list, link);
    for(n=BLST_Q_LAST(list);;n=BLST_Q_PREV(n,link)) {
        if(n==NULL) {
            BLST_Q_INSERT_HEAD(list, node, link);
            break;
        }
        if(time>=n->data.time) {
            BLST_Q_INSERT_AFTER(list, n, node, link);
            break;
        }
    }
    return;
}


static void BKNI_P_StatsState_Insert(unsigned long time, const char *file, unsigned line)
{
    BKNI_P_StatsState *state = &g_BKNI_P_StatsState;
    state->csTime.aggregate.count++;
    state->csTime.aggregate.totalTime += time;
    state->csTime.aggregate.maxTime = time > state->csTime.aggregate.maxTime ? time : state->csTime.aggregate.maxTime;
    if(time>BKNI_P_STATS_TIME_THRESHOLD) {
        BKNI_P_TimeNode *node = BLST_Q_FIRST(&state->csTime.list);
        if(time>node->data.time) {
            node->data.time = time;
            node->data.file = file;
            node->data.line = line;
            BKNI_P_TimeList_ReplaceSorted(&state->csTime.list,node);
        }
    }
#if BKNI_P_STATS_CS_SITES
    {
        BKNI_P_SiteNode *node;
        BKNI_P_SiteKey key;
        key.file = file;
        key.line = line;
        node = BLST_AA_TREE_FIND(BKNI_P_SiteInstanceTree, &state->csSites.instanceTree, &key);
        if(node) {
            BLST_AA_TREE_REMOVE(BKNI_P_SiteTotalTimeTree, &state->csSites.totalTimeTree, node);
            node->key.count ++;
            node->key.totalTime += time;
            node->key.maxTime = time > node->key.maxTime ? time: node->key.maxTime;
            BLST_AA_TREE_INSERT(BKNI_P_SiteTotalTimeTree, &state->csSites.totalTimeTree, &node->key, node);
        } else /* node==NULL */ {
            if(state->csSites.nextFree<BKNI_P_STATS_CS_SITES) {/* found unused entry */
                node = state->csSites.nodes + state->csSites.nextFree;
                state->csSites.nextFree++;
            } else { /* find entry with smallest totalTime */
                node = BLST_AA_TREE_LAST(BKNI_P_SiteTotalTimeTree, &state->csSites.totalTimeTree);
                BLST_AA_TREE_REMOVE(BKNI_P_SiteTotalTimeTree, &state->csSites.totalTimeTree, node);
                BLST_AA_TREE_REMOVE(BKNI_P_SiteInstanceTree, &state->csSites.instanceTree, node);
            }
            node->key.file = file;
            node->key.line = line;
            node->key.count = 1;
            node->key.totalTime = time == 0? 1 : time; /* rounging up totalTime to 1 */
            node->key.maxTime = time;
            BLST_AA_TREE_INSERT(BKNI_P_SiteInstanceTree, &state->csSites.instanceTree, &node->key, node);
            BLST_AA_TREE_INSERT(BKNI_P_SiteTotalTimeTree, &state->csSites.totalTimeTree, &node->key, node);
        }
    }
#endif /* BKNI_P_STATS_CS_SITES */
    return;
}

const char *
BKNI_P_PrepareFileName(const char *pFileName)
{
    const char *s;
    unsigned i;

    if(pFileName==NULL) {
        return "unknown";
    }
    for(s=pFileName;*s != '\0';s++) { } /* search forward */

    for(i=0;s!=pFileName;s--) { /* search backward */
        if(*s=='/' || *s=='\\') {
            i++;
            if(i>3) {
                return s+1;
            }
        }
    }
    return pFileName;
}

BDBG_FILE_MODULE(bkni_statistics_cs);
void BKNI_P_Stats_Print(void)
{
    BKNI_P_TimeNode *node;
    BKNI_P_StatsState *state = &g_BKNI_P_StatsState;
    unsigned i;

    pthread_mutex_lock(&g_csMutex);
    state->csTime.printCopy.aggregate.count = state->csTime.aggregate.count;
    state->csTime.printCopy.aggregate.maxTime = state->csTime.aggregate.maxTime;
    state->csTime.printCopy.aggregate.totalTime = state->csTime.aggregate.totalTime;
    state->csTime.aggregate.count = 0;
    state->csTime.aggregate.maxTime = 0;
    state->csTime.aggregate.totalTime = 0;
    /* acquire critical section only to copy statistics */
    for(node = BLST_Q_LAST(&state->csTime.list), i=0;i<BKNI_DEBUG_CS_TIMING_TIME_NODES;i++,node=BLST_Q_PREV(node, link)) {
        BKNI_P_TimeNodeData *data = state->csTime.printCopy.data+i;
        BDBG_ASSERT(node);
        data->time = node->data.time;
        data->file = node->data.file;
        data->line = node->data.line;
        node->data.time = 0; /* clear nodes in the sorted list, but don't reinsert it's not required */
        node->data.line = 0;
        if(data->time<=BKNI_P_STATS_TIME_THRESHOLD) { /* stop copying data that wouldn't get printed */
            break;
        }
    }
#if BKNI_P_STATS_CS_SITES
    {
        BKNI_P_SiteNode *node;
        for(    i=0, node=BLST_AA_TREE_FIRST(BKNI_P_SiteTotalTimeTree, &state->csSites.totalTimeTree);
                node && i<BKNI_DEBUG_CS_TIMING_TIME_NODES;
                i++, node=BLST_AA_TREE_NEXT(BKNI_P_SiteTotalTimeTree, &state->csSites.totalTimeTree, node)) {
            BKNI_P_SiteKey *data = state->csSites.printCopy.data + i;

            if(node->key.totalTime <= BKNI_P_STATS_TIME_THRESHOLD) {
                data->totalTime = 0; /* mark it as the last */
                break;
            }
            *data =  node->key; /* copy data */
        }
        BLST_AA_TREE_INIT(BKNI_P_SiteInstanceTree, &state->csSites.instanceTree);
        BLST_AA_TREE_INIT(BKNI_P_SiteTotalTimeTree, &state->csSites.totalTimeTree);
        state->csSites.nextFree = 0;
    }
#endif /* BKNI_P_STATS_CS_SITES */
    pthread_mutex_unlock(&g_csMutex);
    if(state->csTime.printCopy.aggregate.count==0) {
        return;
    }
    BDBG_MODULE_MSG(bkni_statistics_cs, ("---- Critical Section Statistics: count:%u  total:%u max:%u avg:%u microsec ---", (unsigned)state->csTime.printCopy.aggregate.count, (unsigned)state->csTime.printCopy.aggregate.totalTime, (unsigned)state->csTime.printCopy.aggregate.maxTime, (unsigned)(state->csTime.printCopy.aggregate.totalTime/state->csTime.printCopy.aggregate.count)));
    for(i=0;i<BKNI_DEBUG_CS_TIMING_TIME_NODES;i++) {
        BKNI_P_TimeNodeData *data = state->csTime.printCopy.data+i;
        if(data->time <= BKNI_P_STATS_TIME_THRESHOLD) {
            break;
        }
       if(data->line) {
            BDBG_MODULE_MSG(bkni_statistics_cs,("%s:%u %u microsec", BKNI_P_PrepareFileName(data->file), data->line, data->time));
        }
    }
#if BKNI_P_STATS_CS_SITES
    for(i=0;i<BKNI_DEBUG_CS_TIMING_TIME_NODES;i++) {
        BKNI_P_SiteKey *data = state->csSites.printCopy.data + i;
        if(data->totalTime <= BKNI_P_STATS_TIME_THRESHOLD) {
            break;
        }
        BDBG_MODULE_MSG(bkni_statistics_cs,("%s:%u count:%u total:%u max:%u avg:%u microsec", BKNI_P_PrepareFileName(data->file), data->line, data->count, data->totalTime, data->maxTime, data->totalTime/data->count));
    }
#endif
    return;
}
#else
#define BKNI_P_StatsState_Init()
void BKNI_P_Stats_Print(void)
{
}

#endif /* BKNI_DEBUG_CS_TIMING */

static unsigned g_refcnt = 0;

BERR_Code BKNI_Init(void)
{
    BERR_Code result;
#if BDBG_DEBUG_BUILD
    if (pthread_self() == 0) {
        /* If this fails, a library outside of magnum has failed. KNI requires this to work. */
        BKNI_Fail();
    }
#endif

    if (g_refcnt++ == 0) {
        result = BKNI_P_MutexTrackingState_Init();
        BKNI_P_StatsState_Init();
        BKNI_P_TrackAlloc_Init();
    }
    else {
        result = 0;
    }

    return result;
}

/* coverity[+kill]  */
void BKNI_Fail(void)
{
    /* Derefering 0 will cause a SIGSEGV will usually produce a core dump. */
    BDBG_P_PrintString("BKNI_Fail is intentionally causing a segfault. Please inspect any prior error messages or get a core dump stack trace to determine the cause of failure.\n");
    *(volatile unsigned char *)0;
    abort();
}

BERR_Code BKNI_CreateMutex_tagged(BKNI_MutexHandle *handle, const char *file, int line)
{
    BKNI_MutexHandle mutex;
    ASSERT_NOT_CRITICAL();

    mutex = (BKNI_MutexHandle)BKNI_Malloc_tagged(sizeof(**handle), file, line);
    if (mutex==NULL) {
        return BERR_TRACE(BERR_OS_ERROR);
    }
    BDBG_OBJECT_SET(mutex, BKNI_Mutex);
    mutex->settings.suspended = false;

    /* WARNING: Do not make BKNI_MutexHandle a recursive mutex. The usual motivation for doing this is to allow recursive calls back into
    Nexus or Magnum from custom callouts. That would be a violation of Nexus and Magnum architecture and will cause catastrophic failure.
    If your application needs its own recursive mutex, please create your own function and leave this unmodified. */
    if (pthread_mutex_init(&mutex->mutex, NULL)) {
        BDBG_OBJECT_DESTROY(*handle, BKNI_Mutex);
        free(mutex);
        return BERR_TRACE(BERR_OS_ERROR);
    }
    *handle = mutex;
    BKNI_P_MutexTracking_Init(&mutex->tracking, file, line);
    return BERR_SUCCESS;
}

void
BKNI_DestroyMutex_tagged(BKNI_MutexHandle handle, const char *file, int line)
{
    ASSERT_NOT_CRITICAL();
    BDBG_OBJECT_ASSERT(handle, BKNI_Mutex);

    BKNI_P_MutexTracking_Uninit(&handle->tracking);
    pthread_mutex_destroy(&handle->mutex);
    BDBG_OBJECT_DESTROY(handle, BKNI_Mutex);
    BKNI_Free_tagged(handle, file, line);
    return ;
}

#undef BKNI_CreateMutex
BERR_Code BKNI_CreateMutex(BKNI_MutexHandle *handle)
{
    return BKNI_CreateMutex_tagged(handle, NULL, 0);
}

#undef BKNI_DestroyMutex
void BKNI_DestroyMutex(BKNI_MutexHandle handle)
{
    BKNI_DestroyMutex_tagged(handle, NULL, 0);
}

BERR_Code
BKNI_TryAcquireMutex_tagged(BKNI_MutexHandle handle, const char *file, int line)
{
    int rc;

    ASSERT_NOT_CRITICAL();
    BDBG_OBJECT_ASSERT(handle, BKNI_Mutex);

    rc = pthread_mutex_trylock(&handle->mutex);
    if (rc==0) {
        BKNI_P_MutexTracking_AfterAcquire(&handle->tracking, file, line);
        return BERR_SUCCESS;
    } else if (rc==EBUSY) {
        return BERR_TIMEOUT;
    } else {
        return BERR_TRACE(BERR_OS_ERROR);
    }
}

#undef BKNI_TryAcquireMutex
BERR_Code BKNI_TryAcquireMutex(BKNI_MutexHandle handle)
{
    return BKNI_TryAcquireMutex_tagged(handle, NULL, 0);
}

BERR_Code
BKNI_AcquireMutex_tagged(BKNI_MutexHandle handle, const char *file, int line)
{
    ASSERT_NOT_CRITICAL();
    BDBG_OBJECT_ASSERT(handle, BKNI_Mutex);

    if (pthread_mutex_lock(&handle->mutex)==0) {
        BKNI_P_MutexTracking_AfterAcquire(&handle->tracking, file, line);
        return BERR_SUCCESS;
    } else {
        return BERR_TRACE(BERR_OS_ERROR);
    }
}

#undef BKNI_AcquireMutex
BERR_Code BKNI_AcquireMutex(BKNI_MutexHandle handle)
{
    return BKNI_AcquireMutex_tagged(handle, NULL, 0);
}

void
BKNI_ReleaseMutex(BKNI_MutexHandle handle)
{
    ASSERT_NOT_CRITICAL();
    BDBG_OBJECT_ASSERT(handle, BKNI_Mutex);

    BKNI_P_MutexTracking_BeforeRelease(&handle->tracking);
    if (pthread_mutex_unlock(&handle->mutex)) {
        BDBG_ERR(("pthread_mutex_unlock failed"));
        BDBG_ASSERT(false);
    }
    return ;
}

void BKNI_GetMutexSettings(BKNI_MutexHandle mutex, BKNI_MutexSettings *pSettings)
{
    BDBG_OBJECT_ASSERT(mutex, BKNI_Mutex);
    *pSettings = mutex->settings;
    return;
}

BERR_Code BKNI_SetMutexSettings(BKNI_MutexHandle mutex, const BKNI_MutexSettings *pSettings)
{
    BDBG_OBJECT_ASSERT(mutex, BKNI_Mutex);
    mutex->settings = *pSettings;
#if BKNI_DEBUG_MUTEX_TRACKING
    mutex->tracking.settings = *pSettings;
#endif
    return BERR_SUCCESS;
}

#if BKNI_DEBUG_CS_TIMING
static unsigned long g_csTimeStart;
static const char *g_csFile;
static int g_csLine;
#endif


/* BKNI_CS_PRIORITY_ESCALATION is a simple form of priority inheritence.
In linux user mode, critical sections can be pre-empted and priority inversion problems can result.
Instead of actually inheriting, this sets any thread entering a critical section to be highest priority & policy for pthreads.
It currently defaults off. */
/* #define BKNI_CS_PRIORITY_ESCALATION 1 */
#if BKNI_CS_PRIORITY_ESCALATION
static int g_cs_policy = -1;
static struct sched_param g_cs_sched_param;
#endif

void BKNI_EnterCriticalSection_tagged(const char *file, unsigned line)
{
#if BKNI_CS_PRIORITY_ESCALATION
      int local_policy;
      struct sched_param local_sched_param, new_sched_param;
#endif

    ASSERT_NOT_CRITICAL();

#if BKNI_CS_PRIORITY_ESCALATION
      pthread_getschedparam(pthread_self(), &local_policy, &local_sched_param);
      memcpy(&new_sched_param, &local_sched_param, sizeof(new_sched_param));
      new_sched_param.sched_priority = 99;

      /* Temporarily increase thread priority to highest. Do this before trying to lock the mutex. */
      pthread_setschedparam(pthread_self(), SCHED_FIFO, &new_sched_param);
#endif

    /* WARNING: Do not make g_csMutex a recursive mutex. The usual motivation for doing this is to allow ISR code to call
    into non-ISR code. That would be a violation of Magnum architecture and will cause catastrophic failure. If your application
    needs its own recursive critical section, please create your own function and leave this unmodified. */
    if (pthread_mutex_lock(&g_csMutex)!=0)
    {
        BDBG_ERR(("pthread_mutex_lock failed"));
        BDBG_ASSERT(false);
        return;
    }

#if BKNI_CS_PRIORITY_ESCALATION
    /* now that we have the CS mutex, we can store the local values into the global state */
    g_cs_policy = local_policy;
    g_cs_sched_param = local_sched_param;
#endif

    SET_CRITICAL();

#if BKNI_DEBUG_CS_TIMING
    g_csTimeStart = BKNI_P_GetMicrosecondTick();
    g_csFile = file;
    g_csLine = line;
#else
    BSTD_UNUSED(file);
    BSTD_UNUSED(line);
#endif
}

void
BKNI_LeaveCriticalSection_tagged(const char *file, unsigned line)
{
#if BKNI_DEBUG_CS_TIMING
    uint32_t currentCount, elapsedCount;
#endif
#if BKNI_CS_PRIORITY_ESCALATION
    /* copy escalated thread priority/policy into local storage before releasing the CS mutex */
    int local_policy = g_cs_policy;
    struct sched_param local_sched_param = g_cs_sched_param;
#endif

#if BKNI_DEBUG_CS_TIMING
    /* Snapshot time */
    currentCount = BKNI_P_GetMicrosecondTick();
    elapsedCount = currentCount - g_csTimeStart; /* this would handle wrap around by nature of modular math */
    if ( elapsedCount > 10 * 1000 ) /* 10 milliseconds */
    {
        BDBG_P_PrintString("Long CS detected (%u.%u ms).\nEntered: %s:%d\nLeaving %s:%d\n",
               elapsedCount/1000, elapsedCount%1000, g_csFile, g_csLine, file, line);
    }
    BKNI_P_StatsState_Insert(elapsedCount, file, line);
#else
    BSTD_UNUSED(file);
    BSTD_UNUSED(line);
#endif

    ASSERT_CRITICAL();
    CLEAR_CRITICAL();

    if (pthread_mutex_unlock(&g_csMutex))
    {
        BDBG_ERR(("pthread_mutex_unlock failed"));
        BDBG_ASSERT(false);
    }

#if BKNI_CS_PRIORITY_ESCALATION
    /* restore this thread's settings from before the EnterCriticalSection */
    pthread_setschedparam(pthread_self(), local_policy, &local_sched_param);
#endif

    return;
}

#if !BKNI_DEBUG_CS_TIMING
void BKNI_EnterCriticalSection() { BKNI_EnterCriticalSection_tagged(NULL, 0); }
void BKNI_LeaveCriticalSection() { BKNI_LeaveCriticalSection_tagged(NULL, 0); }
#endif

int
BKNI_Printf(const char *fmt, ...)
{
    va_list arglist;
    int rc;

    va_start( arglist, fmt );
    rc = BKNI_Vprintf(fmt, arglist);
    va_end(arglist);

    return rc;
}


int
BKNI_Snprintf(char *str, size_t len, const char *fmt, ...)
{
    va_list arglist;
    int rc;

    va_start( arglist, fmt );
    rc = vsnprintf(str, len, fmt, arglist);
    va_end(arglist);

    return rc;
}

#if B_REFSW_ANDROID
#include <cutils/log.h>
#endif

int
BKNI_Vprintf(const char *fmt, va_list ap)
{
#if B_REFSW_ANDROID
    return LOG_PRI_VA(ANDROID_LOG_WARN, "BKNI", fmt, ap);
#else
    return vfprintf(stderr, fmt, ap);
#endif
}

static unsigned long BKNI_P_GetMicrosecondTick(void)
{
#if !HAS_NPTL
    int rc;
    struct timeval now;
    rc = gettimeofday(&now, NULL);
    if (rc) {
        rc = BERR_TRACE(BERR_OS_ERROR);
        return 0;
    }
    return now.tv_sec * 1000000 + now.tv_usec;
#else
    int rc;
    struct timespec now;
    /* It's ok to use clock_gettime even without NPTL. */
    rc = clock_gettime(CLOCK_MONOTONIC, &now);
    if (rc) {
        rc = BERR_TRACE(BERR_OS_ERROR);
        return 0;
    }
    return now.tv_sec * 1000000 + now.tv_nsec / 1000;
#endif
}

/**
BKNI_Delay impl notes:
This is an incredibly inefficient implementation...which is exactly
the point. Because the linux scheduler has a 10 milisecond clock tick,
this function should not hit the scheduler. It must use a busy loop.
sleep and usleep use the scheduler. nanasleep will use the scheduler
unless the pthread priority is high, which we cannot assume in this function.
Therefore a busy loop with a fine-grain time syscall does the job.
*/
void
BKNI_Delay(unsigned int microsec)
{
    unsigned long start;
    unsigned long diff;
    start = BKNI_P_GetMicrosecondTick();
    do {
        diff = BKNI_P_GetMicrosecondTick() - start;
    } while (diff < microsec);
    return;
}

BERR_Code
BKNI_Sleep(unsigned int millisec)
{
    struct timespec delay;
    struct timespec rem;
    int rc;

    ASSERT_NOT_CRITICAL();

    delay.tv_sec = millisec/1000;
    delay.tv_nsec = 1000 * 1000 * (millisec%1000);

    for(;;) {
        rc = nanosleep(&delay, &rem); /* [u]sleep can't be used because it uses SIGALRM */
        if (rc!=0) {
            if (errno==EINTR) {
                delay = rem; /* sleep again */
                continue;
            }
            return BERR_TRACE(BERR_OS_ERROR);
        }
        break; /* done */
    }

    return BERR_SUCCESS;
}


BERR_Code
BKNI_CreateEvent_tagged(BKNI_EventHandle *pEvent, const char *file, int line)
{
    BKNI_EventHandle event;
    int rc;
    BERR_Code result=BERR_SUCCESS;
    /* coverity[var_decl: FALSE] */
    pthread_condattr_t attr;

    ASSERT_NOT_CRITICAL();

    event = BKNI_Malloc_tagged(sizeof(*event), file, line);
    *pEvent = event;
    if ( !event) {
        result = BERR_TRACE(BERR_OS_ERROR);
        goto err_no_memory;
    }
    BDBG_OBJECT_SET(event, BKNI_Event);

    rc = pthread_mutex_init (&event->lock, NULL /* default attributes */);
    if (rc!=0) {
        result = BERR_TRACE(BERR_OS_ERROR);
        goto err_mutex;
    }

    /* coverity[uninit_use_in_call: FALSE] */
    rc = pthread_condattr_init(&attr);
    if (rc!=0) {
        result = BERR_TRACE(BERR_OS_ERROR);
        goto err_condvar;
    }

#if HAS_NPTL
    rc = pthread_condattr_setclock(&attr, CLOCK_MONOTONIC);
    if (rc!=0) {
        result = BERR_TRACE(BERR_OS_ERROR);
        goto err_condvar;
    }
#endif

    rc = pthread_cond_init( &event->cond, &attr);
    if (rc!=0) {
        result = BERR_TRACE(BERR_OS_ERROR);
        goto err_condvar;
    }
    /* coverity[missing_lock: FALSE] */
    event->signal = false;
    /* coverity[missing_lock: FALSE] */
    event->group = NULL;

    return result;

err_condvar:
    pthread_mutex_destroy(&event->lock);
err_mutex:
    BDBG_OBJECT_DESTROY(event, BKNI_Event);
    free(event);
err_no_memory:
    return result;
}

void
BKNI_DestroyEvent_tagged(BKNI_EventHandle event, const char *file, int line)
{
    int rc;
    BKNI_EventGroupHandle group;

    ASSERT_NOT_CRITICAL();
    BDBG_OBJECT_ASSERT(event, BKNI_Event);
    group = event->group;
    /* At this point, we may have been removed from the group and event->group is NULL.
    This would be poor application code, but KNI should protect itself. */

    if (group) {
        BDBG_WRN(("Event %#x still in the group %#x, removing it", (unsigned)(unsigned long)event, (unsigned)(unsigned long)group));
        rc = pthread_mutex_lock(&group->lock);
        if (rc!=0) {
            BDBG_ERR(("pthread_mutex_lock %d", rc));
            BDBG_ASSERT(false);
        }
        /* if the group does not match, then the caller needs to fix their code. we can't have an event being added & removed from various
        groups and being destroyed at the same time. */
        BDBG_ASSERT(event->group == group);
        BLST_D_REMOVE(&group->members, event, list);
        pthread_mutex_unlock(&group->lock);
    }
    rc = pthread_mutex_destroy(&event->lock);
    if (rc!=0) {
        BDBG_ERR(("pthread_mutex_destroy: %d", rc));
        BDBG_ASSERT(false);
    }
    rc = pthread_cond_destroy(&event->cond);
    if (rc!=0) {
        BDBG_ERR(("pthread_cond_destroy: %d", rc));
        BDBG_ASSERT(false);
    }
    BDBG_OBJECT_DESTROY(event, BKNI_Event);
    BKNI_Free_tagged(event, file, line);
    return ;
}

#undef BKNI_CreateEvent
BERR_Code BKNI_CreateEvent(BKNI_EventHandle *pEvent)
{
    return BKNI_CreateEvent_tagged(pEvent, NULL, 0);
}

#undef BKNI_DestroyEvent
void BKNI_DestroyEvent(BKNI_EventHandle event)
{
    BKNI_DestroyEvent_tagged(event, NULL, 0);
}

/* return a timespec which is the current time plus an increment */
static int BKNI_P_SetTargetTime(struct timespec *target, int timeoutMsec)
{
    int rc;
#if !HAS_NPTL
    /* Unless pthread can set CLOCK_MONOTONIC, we cannot use clock_gettime(CLOCK_MONOTONIC). This is only available with NPTL linux. */
    struct timeval now;
    rc = gettimeofday(&now, NULL);
    if (rc!=0) {
        return BERR_TRACE(BERR_OS_ERROR);
    }
    target->tv_nsec = now.tv_usec * 1000 + (timeoutMsec%1000)*1000000;
    target->tv_sec = now.tv_sec + (timeoutMsec/1000);
    if (target->tv_nsec >= 1000000000) {
        target->tv_nsec -=  1000000000;
        target->tv_sec ++;
    }
#else
    struct timespec now;
    rc = clock_gettime(CLOCK_MONOTONIC, &now);
    if (rc!=0) {
        return BERR_TRACE(BERR_OS_ERROR);
    }
    target->tv_nsec = now.tv_nsec + (timeoutMsec%1000)*1000000;
    target->tv_sec = now.tv_sec + (timeoutMsec/1000);
    if (target->tv_nsec >= 1000000000) {
        target->tv_nsec -=  1000000000;
        target->tv_sec ++;
    }
#endif
    return 0;
}

BERR_Code
BKNI_WaitForEvent(BKNI_EventHandle event, int timeoutMsec)
{
    int rc;
    BERR_Code result = BERR_SUCCESS;
    struct timespec target;

    if ( timeoutMsec != 0 )
    {
        ASSERT_NOT_CRITICAL();
    }
    BDBG_OBJECT_ASSERT(event, BKNI_Event);

    if (timeoutMsec!=0 && timeoutMsec!=BKNI_INFINITE) {
        if (timeoutMsec<0) {
            /* If your app is written to allow negative values to this function, then it's highly likely you would allow -1, which would
            result in an infinite hang. We recommend that you only pass positive values to this function unless you definitely mean BKNI_INFINITE. */
            BDBG_WRN(("BKNI_WaitForEvent given negative timeout. Possible infinite hang if timeout happens to be -1 (BKNI_INFINITE)."));
        }
        if (timeoutMsec < 16) {
            timeoutMsec = 16; /* This is used to achieve consistency between different OS's. */
        }
        rc = BKNI_P_SetTargetTime(&target, timeoutMsec);
        if (rc) {
            return BERR_TRACE(BERR_OS_ERROR);
        }
    }

    rc = pthread_mutex_lock(&event->lock);
    if (rc!=0) {
        return BERR_TRACE(BERR_OS_ERROR);
    }
    if (event->signal) {
        event->signal = false;
        goto done;
    }
    if (timeoutMsec == 0) { /* wait without timeout */
        /* It is normal that BKNI_WaitForEvent could time out. Do not use BERR_TRACE. */
        result = BERR_TIMEOUT;
        goto done;
    }
    do {
        if (timeoutMsec == BKNI_INFINITE) {
            rc = pthread_cond_wait(&event->cond, &event->lock);
        } else {
            rc = pthread_cond_timedwait(&event->cond, &event->lock, &target);
            if (event->signal) {
                /* even if we timed out, if the signal was set, we succeed. this allows magnum to
                be resilient to large OS scheduler delays */
                result = BERR_SUCCESS;
                break;
            }
            if (rc==ETIMEDOUT) {
                BDBG_MSG(("BKNI_WaitForEvent(%#x): timeout", (unsigned)(unsigned long)event));
                result = BERR_TIMEOUT;
                goto done;
            }
        }
        if(rc==EINTR) {
            BDBG_MSG(("BKNI_WaitForEvent(%#x): interrupted", (unsigned)(unsigned long)event));
            continue;
        }
        if (rc!=0) {
            result = BERR_TRACE(BERR_OS_ERROR);
            goto done;
        }
    } while(!event->signal);  /* we might have been wokenup and then event has been cleared */

    event->signal = false;
done:
    pthread_mutex_unlock(&event->lock);
    return result;
}

void
BKNI_SetEvent(BKNI_EventHandle event)
{
    int rc;
    BKNI_EventGroupHandle group;

    BDBG_OBJECT_ASSERT(event, BKNI_Event);
    group = event->group;
    /* At this point, we may have been removed from the group and event->group is NULL.
    This is a real possibility because BKNI_SetEvent can be called from an ISR.
    Caching the group pointer allows us to safely unlock still. */

    if (group) {
        rc = pthread_mutex_lock(&group->lock);
        BDBG_ASSERT(0 == rc);
    }
    rc = pthread_mutex_lock(&event->lock);
    if (rc!=0) {
        BDBG_ERR(("pthread_mutex_lock: %d", rc));
        BDBG_ASSERT(false);
    }
    event->signal = true;
    rc = pthread_cond_signal(&event->cond);
    if (rc!=0) {
        BDBG_ERR(("pthread_cond_signal: %d", rc));
        BDBG_ASSERT(false);
    }
    if (group) {
        rc = pthread_cond_signal(&group->cond);
        if (rc!=0) {
            BDBG_ERR(("pthread_cond_signal: %d, ignored", rc));
        }
    }
    rc = pthread_mutex_unlock(&event->lock);
    if (rc!=0) {
        BDBG_ERR(("pthread_mutex_unlock: %d", rc));
        BDBG_ASSERT(false);
    }
    if (group) {
        pthread_mutex_unlock(&group->lock);
    }
    return ;
}

void
BKNI_ResetEvent(BKNI_EventHandle event)
{
    int rc;

    BDBG_OBJECT_ASSERT(event, BKNI_Event);
    rc = pthread_mutex_lock(&event->lock);
    if (rc!=0) {
        BDBG_ERR(("pthread_mutex_lock: %d", rc));
        BDBG_ASSERT(false);
    }
    event->signal = false ;
    rc = pthread_mutex_unlock(&event->lock);
    if (rc!=0) {
        BDBG_ERR(("pthread_mutex_unlock: %d", rc));
        BDBG_ASSERT(false);
    }
    return ;
}

int
BKNI_Vsnprintf(char *s, size_t n, const char *fmt, va_list ap)
{
    return vsnprintf(s, n, fmt, ap);
}

BERR_Code
BKNI_CreateEventGroup(BKNI_EventGroupHandle *pGroup)
{
    int rc;
    BKNI_EventGroupHandle group;
    BERR_Code result;
    /* coverity[var_decl: FALSE] */
    pthread_condattr_t attr;

    ASSERT_NOT_CRITICAL();

    group = malloc(sizeof(*group));
    if (!group) {
        result = BERR_TRACE(BERR_OUT_OF_SYSTEM_MEMORY);
        goto err_no_memory;
    }
    BDBG_OBJECT_SET(group, BKNI_EventGroup);

    BLST_D_INIT(&group->members);
    rc = pthread_mutex_init (&group->lock, NULL /* default attributes */);
    if (rc!=0) {
        result = BERR_TRACE(BERR_OS_ERROR);
        goto err_mutex;
    }

    /* coverity[uninit_use_in_call: FALSE] */
    rc = pthread_condattr_init(&attr);
    if (rc!=0) {
        result = BERR_TRACE(BERR_OS_ERROR);
        goto err_condvar;
    }

#if HAS_NPTL
    rc = pthread_condattr_setclock(&attr, CLOCK_MONOTONIC);
    if (rc!=0) {
        result = BERR_TRACE(BERR_OS_ERROR);
        goto err_condvar;
    }
#endif

    rc = pthread_cond_init( &group->cond, &attr);
    if (rc!=0) {
        result = BERR_TRACE(BERR_OS_ERROR);
        goto err_condvar;
    }
    *pGroup = group;

    return BERR_SUCCESS;

err_condvar:
    pthread_mutex_destroy(&group->lock);
err_mutex:
    BDBG_OBJECT_DESTROY(group, BKNI_EventGroup);
    free(group);
err_no_memory:
    return result;
}

void
BKNI_DestroyEventGroup(BKNI_EventGroupHandle group)
{
    int rc;
    BKNI_EventHandle event;

    ASSERT_NOT_CRITICAL();
    BDBG_OBJECT_ASSERT(group, BKNI_EventGroup);

    rc = pthread_mutex_lock(&group->lock);
    if (rc<0) {
        BDBG_ERR(("pthread_mutex_lock failed, rc=%d", rc));
        BDBG_ASSERT(false);
    }

    while(NULL != (event=BLST_D_FIRST(&group->members)) ) {
        BDBG_ASSERT(event->group == group);
        event->group = NULL;
        BLST_D_REMOVE_HEAD(&group->members, list);
    }
    pthread_mutex_unlock(&group->lock);
    /* NOTE: to avoid this race condition, app must ensure that no SetEvent for this group is pending at this time */
    pthread_mutex_destroy(&group->lock);
    pthread_cond_destroy(&group->cond);
    BDBG_OBJECT_DESTROY(group, BKNI_EventGroup);
    free(group);
    return;
}


BERR_Code
BKNI_AddEventGroup(BKNI_EventGroupHandle group, BKNI_EventHandle event)
{
    int rc;
    BERR_Code result = BERR_SUCCESS;

    ASSERT_NOT_CRITICAL();
    BDBG_OBJECT_ASSERT(group, BKNI_EventGroup);
    BDBG_OBJECT_ASSERT(event, BKNI_Event);

    /* IMPORTANT: group lock shall be acquired before event lock */
    rc = pthread_mutex_lock(&group->lock);
    if (rc!=0) {
        BDBG_ERR(("pthread_mutex_lock failed, rc=%d", rc));
        BDBG_ASSERT(false);
    }
    rc = pthread_mutex_lock(&event->lock);
    if (rc!=0) {
        BDBG_ERR(("pthread_mutex_lock failed, rc=%d", rc));
        BDBG_ASSERT(false);
    }
    if (event->group != NULL) {
        BDBG_ERR(("Event %#x already connected to the group %#x", (unsigned)(unsigned long)event, (unsigned)(unsigned long)group));
        result = BERR_TRACE(BERR_OS_ERROR);
    } else {
        BLST_D_INSERT_HEAD(&group->members, event, list);
        event->group = group;
        if (event->signal) {
            /* signal condition if signal already set */
            pthread_cond_signal(&group->cond);
        }
    }
    rc = pthread_mutex_unlock(&event->lock);
    if (rc!=0) {
        BDBG_ERR(("pthread_mutex_unlock failed, rc=%d", rc));
        BDBG_ASSERT(false);
    }
    rc = pthread_mutex_unlock(&group->lock);
    if (rc!=0) {
        BDBG_ERR(("pthread_mutex_unlock failed, rc=%d", rc));
        BDBG_ASSERT(false);
    }
    return result;
}

BERR_Code
BKNI_RemoveEventGroup(BKNI_EventGroupHandle group, BKNI_EventHandle event)
{
    int rc;
    BERR_Code result = BERR_SUCCESS;

    ASSERT_NOT_CRITICAL();
    BDBG_OBJECT_ASSERT(group, BKNI_EventGroup);
    BDBG_OBJECT_ASSERT(event, BKNI_Event);

    rc = pthread_mutex_lock(&group->lock);
    if (rc!=0) {
        BDBG_ERR(("pthread_mutex_lock failed, rc=%d", rc));
        BDBG_ASSERT(false);
    }
    rc = pthread_mutex_lock(&event->lock);
    if (rc!=0) {
        BDBG_ERR(("pthread_mutex_lock failed, rc=%d", rc));
        BDBG_ASSERT(false);
    }
    if (event->group != group) {
        BDBG_ERR(("Event %p doesn't belong to the group %p", (void *)event, (void *)group));
        result = BERR_TRACE(BERR_OS_ERROR);
    } else {
        BLST_D_REMOVE(&group->members, event, list);
        event->group = NULL;
    }
    rc = pthread_mutex_unlock(&event->lock);
    if (rc!=0) {
        BDBG_ERR(("pthread_mutex_unlock failed, rc=%d", rc));
        BDBG_ASSERT(false);
    }
    rc = pthread_mutex_unlock(&group->lock);
    if (rc!=0) {
        BDBG_ERR(("pthread_mutex_unlock failed, rc=%d", rc));
        BDBG_ASSERT(false);
    }
    return result;
}

static unsigned
group_get_events(BKNI_EventGroupHandle group, BKNI_EventHandle *events, unsigned max_events)
{
    BKNI_EventHandle ev;
    int rc;
    unsigned event;

    BDBG_OBJECT_ASSERT(group, BKNI_EventGroup);

    for(event=0, ev=BLST_D_FIRST(&group->members); ev && event<max_events ; ev=BLST_D_NEXT(ev, list)) {
        BDBG_OBJECT_ASSERT(ev, BKNI_Event);
        rc = pthread_mutex_lock(&ev->lock);
        if (rc!=0) {
            BDBG_ERR(("pthread_mutex_lock failed, rc=%d", rc));
            BDBG_ASSERT(false);
        }
        if (ev->signal) {
            ev->signal = false;
            events[event] = ev;
            event++;
        }
        rc = pthread_mutex_unlock(&ev->lock);
        if (rc!=0) {
            BDBG_ERR(("pthread_mutex_unlock failed, rc=%d", rc));
            BDBG_ASSERT(false);
        }
    }
    return event;
}

BERR_Code
BKNI_WaitForGroup(BKNI_EventGroupHandle group, int timeoutMsec, BKNI_EventHandle *events, unsigned max_events, unsigned *nevents)
{
    int rc;
    struct timespec target;
    BERR_Code result = BERR_SUCCESS;

    ASSERT_NOT_CRITICAL();
    BDBG_OBJECT_ASSERT(group, BKNI_EventGroup);

    if (max_events<1) {
        return BERR_TRACE(BERR_INVALID_PARAMETER);
    }
    if (timeoutMsec!=0 && timeoutMsec!=BKNI_INFINITE) {
        if (timeoutMsec<0) {
            /* If your app is written to allow negative values to this function, then it's highly likely you would allow -1, which would
            result in an infinite hang. We recommend that you only pass positive values to this function unless you definitely mean BKNI_INFINITE. */
            BDBG_WRN(("BKNI_WaitForGroup given negative timeout. Possible infinite hang if timeout happens to be -1 (BKNI_INFINITE)."));
        }
        if (timeoutMsec < 16) {
            timeoutMsec = 16; /* This is used to achieve consistency between different OS's. */
        }
        rc = BKNI_P_SetTargetTime(&target, timeoutMsec);
        if (rc) {
            return BERR_TRACE(BERR_OS_ERROR);
        }
    }
    rc = pthread_mutex_lock(&group->lock);
    if (rc!=0) {
        BDBG_ERR(("pthread_mutex_lock failed, rc=%d", rc));
        BDBG_ASSERT(false);
    }
    for(;;) {
        *nevents = group_get_events(group, events, max_events);
        if (*nevents) {
            goto done;
        }
        if (timeoutMsec == 0) {
            result = BERR_TIMEOUT;
            goto done;
        }
        else if (timeoutMsec == BKNI_INFINITE) {
            rc = pthread_cond_wait(&group->cond, &group->lock);
        }
        else {
            rc = pthread_cond_timedwait(&group->cond, &group->lock, &target);
            if (rc==ETIMEDOUT) {
                BDBG_MSG(("BKNI_WaitForGroup(%#x): timeout", (unsigned)(unsigned long)group));
                result = BERR_TIMEOUT;
                goto done;
            }
        }
        if(rc==EINTR) {
            BDBG_MSG(("BKNI_WaitForGroup(%#x): interrupted", (unsigned)(unsigned long)group));
            continue;
        }
        if (rc!=0) {
            BDBG_ERR(("%s() returned %d",(timeoutMsec == BKNI_INFINITE) ? "pthread_cond_wait":"pthread_cond_timedwait",rc));
            result = BERR_TRACE(BERR_OS_ERROR);
            goto done;
        }
    }

done:
    rc = pthread_mutex_unlock(&group->lock);
    if (rc!=0) {
        BDBG_ERR(("pthread_mutex_unlock failed, rc=%d", rc));
        BDBG_ASSERT(false);
    }
    return result;
}

void *
BKNI_Memset(void *b, int c, size_t len)
{
    return memset(b, c, len);
}

void *
BKNI_Memcpy(void *dst, const void *src, size_t len)
{
    return memcpy(dst, src, len);
}

int
BKNI_Memcmp(const void *b1, const void *b2, size_t len)
{
    return memcmp(b1, b2, len);
}

void *
BKNI_Memchr(const void *b, int c, size_t len)
{
    return memchr(b, c, len);

}

void *
BKNI_Memmove(void *dst, const void *src, size_t len)
{
    return memmove(dst, src, len);
}

void
BKNI_AssertIsrContext_isr(const char *filename, unsigned lineno)
{
    if ( !CHECK_CRITICAL() ) {
        BDBG_P_AssertFailed("Not in critical section", filename, lineno);
    }
}

void
BKNI_AssertTaskContext(const char *filename, unsigned lineno)
{
    if ( CHECK_CRITICAL() ) {
        BDBG_P_AssertFailed("Must not be in critical section", filename, lineno);
    }
}

void BKNI_Uninit(void)
{
    if (--g_refcnt == 0) {
        BKNI_P_MutexTrackingState_Uninit();
        BKNI_P_TrackAlloc_Uninit();
    }
    return;
}





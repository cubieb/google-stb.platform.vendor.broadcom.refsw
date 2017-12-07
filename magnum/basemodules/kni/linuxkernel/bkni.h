/***************************************************************************
 *  Copyright (C) 2003-2017 Broadcom.  The term "Broadcom" refers to Broadcom Limited and/or its subsidiaries.
 *
 *  This program is the proprietary software of Broadcom and/or its licensors,
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
 ***************************************************************************/
#ifndef BKNI_H__
#define BKNI_H__

/* No Linux include files are permitted here. Magnum code cannot depend on Linux
kernel header files. The only place where Linux kernel header files are allowed is inside
BKNI .c files. */

typedef struct BKNI_EventObj *BKNI_EventHandle;
#define BKNI_INFINITE -1

BERR_Code BKNI_Init(void);
void BKNI_Uninit(void);
void BKNI_Fail(void) __attribute__ ((noreturn));

void *BKNI_Memset(void *mem, int ch, size_t n);
void *BKNI_Memcpy(void *dest, const void *src, size_t n);
int BKNI_Memcmp(const void *s1, const void *s2, size_t n);
void *BKNI_Memchr(const void *mem, int ch, size_t n);
void *BKNI_Memmove(void *dest, const void *src, size_t n);
int BKNI_Printf(const char *fmt, ...);
int BKNI_Snprintf(char *s, size_t n, const char *fmt, ...);
int BKNI_Vprintf(const char *fmt, va_list ap);
int BKNI_Vsnprintf(char *s, size_t n, const char *fmt, va_list ap);

/**
BKNI_TRACK_MALLOCS is a simple way to track BKNI_Malloc memory leaks and bad BKNI_Frees.
It can also help find the location of bad BKNI_EventHandle and BKNI_MutexHandle instances.
**/
#ifndef BKNI_TRACK_MALLOCS
#define BKNI_TRACK_MALLOCS 1
#endif

/**
BKNI_DEBUG_CS_TIMING can find critical sections which execute too long. This might happen because
of poorly written code or context switching on an overly busy system or a system with misconfigured
real-time threads.
**/
#define BKNI_DEBUG_CS_TIMING 0

/**
BKNI_DEBUG_MUTEX_TRACKING can find mutex objects thate were acquired for long time. Usually this condition
symptom and/or cause of a deadlock condition
**/
#ifndef BKNI_DEBUG_MUTEX_TRACKING
#define BKNI_DEBUG_MUTEX_TRACKING 0
#endif

#if BKNI_TRACK_MALLOCS
#define BKNI_Malloc(SIZE)			BKNI_Malloc_tagged(SIZE,__FILE__,__LINE__)
void *BKNI_Malloc_tagged(size_t size, const char *file, unsigned line);
#else
void *BKNI_Malloc(size_t size);
#endif


#if BKNI_TRACK_MALLOCS
#define BKNI_Free(MEM) 				BKNI_Free_tagged(MEM,__FILE__,__LINE__)
void BKNI_Free_tagged(void *mem, const char *file, unsigned line);
#else
void BKNI_Free(void *mem);
#endif


#define BKNI_Sleep(MILLISEC)		BKNI_Sleep_tagged(MILLISEC,__FILE__,__LINE__)
BERR_Code BKNI_Sleep_tagged(unsigned millisec, const char *file, unsigned line);

#define BKNI_Delay(MICROSEC)		BKNI_Delay_tagged(MICROSEC,__FILE__,__LINE__)
void BKNI_Delay_tagged(unsigned int microsec, const char *file, unsigned line);

#if BKNI_TRACK_MALLOCS
#define BKNI_CreateEvent(EVENT) BKNI_CreateEvent_tagged(EVENT, __FILE__, __LINE__)
BERR_Code BKNI_CreateEvent_tagged(BKNI_EventHandle *p_event, const char *file, unsigned line);

#define BKNI_DestroyEvent(EVENT) BKNI_DestroyEvent_tagged(EVENT, __FILE__, __LINE__)
void BKNI_DestroyEvent_tagged(BKNI_EventHandle event, const char *file, unsigned line);
#else
BERR_Code BKNI_CreateEvent(BKNI_EventHandle *p_event);
void BKNI_DestroyEvent(BKNI_EventHandle event);
#endif

#define BKNI_SetEvent(EVENT)		BKNI_SetEvent_tagged(EVENT,__FILE__,__LINE__)
void BKNI_SetEvent_tagged(BKNI_EventHandle event, const char *file, unsigned line);

#define BKNI_WaitForEvent(EVENT,TIMEOUT)	BKNI_WaitForEvent_tagged(EVENT,TIMEOUT,__FILE__,__LINE__)
BERR_Code BKNI_WaitForEvent_tagged(BKNI_EventHandle event, int timeoutMsec, const char *file, unsigned line);

#define BKNI_ResetEvent(EVENT) BKNI_ResetEvent_tagged(EVENT, __FILE__, __LINE__)
void BKNI_ResetEvent_tagged(BKNI_EventHandle event, const char *file, unsigned line);

#define BKNI_EnterCriticalSection()	BKNI_EnterCriticalSection_tagged(__FILE__,__LINE__)
void BKNI_EnterCriticalSection_tagged(const char *file, unsigned line);

#define BKNI_LeaveCriticalSection()	BKNI_LeaveCriticalSection_tagged(__FILE__,__LINE__)
void BKNI_LeaveCriticalSection_tagged(const char *file, unsigned line);

/***************************************************************************
Summary:
	Provide a tasklet pointer to KNI to allow finer-grain locking for
	BKNI_EnterCriticalSection.

Description:
    This allows BKNI_EnterCriticalSection to only stop the specified tasklet
	from executing during critical sections and does not require masking
	interrupts or disabling all bottom-halves on the system.  This call is
	optional and specific only to the linuxkernel implementation.

	A (struct tasklet_struct *) is expected to be passed as a parameter
	to this function or NULL will cause KNI to revert to broader locking.

	This function does not need to be implemented or called unless your
	application desires this finer-grain locking.

Returns:
	BERR_SUCCESS - The tasklet handle has been changed.
	BERR_NOT_SUPPORTED - This feature is not supported.
****************************************************************************/
BERR_Code BKNI_LinuxKernel_SetIsrTasklet(void *pTasklet);

#ifdef BDBG_DEBUG_BUILD
#define BKNI_ASSERT_TASK_CONTEXT() BKNI_AssertTaskContext(__FILE__, __LINE__)
#else
#define BKNI_ASSERT_TASK_CONTEXT() (void)0
#endif
void BKNI_AssertTaskContext(const char *filename, unsigned lineno);


#ifdef BDBG_DEBUG_BUILD
#define BKNI_ASSERT_ISR_CONTEXT() BKNI_AssertIsrContext_isr(__FILE__, __LINE__)
#else
#define BKNI_ASSERT_ISR_CONTEXT() (void)0
#endif
void BKNI_AssertIsrContext_isr(const char *filename, unsigned lineno);


/* lines below provides aliases for functions safe to call from the interrupt handler */
#define BKNI_Memset_isr BKNI_Memset
#define BKNI_Memcpy_isr BKNI_Memcpy
#define BKNI_Memcmp_isr BKNI_Memcmp
#define BKNI_Memchr_isr BKNI_Memchr
#define BKNI_Memmove_isr BKNI_Memmove
#define BKNI_Delay_isr BKNI_Delay
#define BKNI_SetEvent_isr BKNI_SetEvent
#define BKNI_ResetEvent_isr BKNI_ResetEvent

typedef struct BKNI_MallocEntryInfo {
    const void *mem;

    size_t size;
    const char *malloc_file;
    unsigned malloc_line;
    bool alive; /* sets to true if block is still allocated */
    const char *free_file;
    unsigned free_line;
} BKNI_MallocEntryInfo;

/* Called from DBG, and should only be used for the debug purposes */
BERR_Code BKNI_GetMallocEntryInfo_isrsafe(
    const void *memory, /* pointer memory allocated by BKNI_Malloc */
    BKNI_MallocEntryInfo *info
    );

#define BKNI_GetTrackMallocEntry_isr BKNI_GetTrackMallocEntry

#endif /* BKNI_H__ */

/******************************************************************************
 * (c) 2014 Broadcom Corporation
 *
 * This program is the proprietary software of Broadcom Corporation and/or its
 * licensors, and may only be used, duplicated, modified or distributed pursuant
 * to the terms and conditions of a separate, written license agreement executed
 * between you and Broadcom (an "Authorized License").  Except as set forth in
 * an Authorized License, Broadcom grants no license (express or implied), right
 * to use, or waiver of any kind with respect to the Software, and Broadcom
 * expressly reserves all rights in and to the Software and all intellectual
 * property rights therein.  IF YOU HAVE NO AUTHORIZED LICENSE, THEN YOU
 * HAVE NO RIGHT TO USE THIS SOFTWARE IN ANY WAY, AND SHOULD IMMEDIATELY
 * NOTIFY BROADCOM AND DISCONTINUE ALL USE OF THE SOFTWARE.
 *
 * Except as expressly set forth in the Authorized License,
 *
 * 1. This program, including its structure, sequence and organization,
 *    constitutes the valuable trade secrets of Broadcom, and you shall use all
 *    reasonable efforts to protect the confidentiality thereof, and to use
 *    this information only in connection with your use of Broadcom integrated
 *    circuit products.
 *
 * 2. TO THE MAXIMUM EXTENT PERMITTED BY LAW, THE SOFTWARE IS PROVIDED "AS IS"
 *    AND WITH ALL FAULTS AND BROADCOM MAKES NO PROMISES, REPRESENTATIONS OR
 *    WARRANTIES, EITHER EXPRESS, IMPLIED, STATUTORY, OR OTHERWISE, WITH RESPECT
 *    TO THE SOFTWARE.  BROADCOM SPECIFICALLY DISCLAIMS ANY AND ALL IMPLIED
 *    WARRANTIES OF TITLE, MERCHANTABILITY, NONINFRINGEMENT, FITNESS FOR A
 *    PARTICULAR PURPOSE, LACK OF VIRUSES, ACCURACY OR COMPLETENESS, QUIET
 *    ENJOYMENT, QUIET POSSESSION OR CORRESPONDENCE TO DESCRIPTION. YOU ASSUME
 *    THE ENTIRE RISK ARISING OUT OF USE OR PERFORMANCE OF THE SOFTWARE.
 *
 * 3. TO THE MAXIMUM EXTENT PERMITTED BY LAW, IN NO EVENT SHALL BROADCOM OR ITS
 *    LICENSORS BE LIABLE FOR (i) CONSEQUENTIAL, INCIDENTAL, SPECIAL, INDIRECT,
 *    OR EXEMPLARY DAMAGES WHATSOEVER ARISING OUT OF OR IN ANY WAY RELATING TO
 *    YOUR USE OF OR INABILITY TO USE THE SOFTWARE EVEN IF BROADCOM HAS BEEN
 *    ADVISED OF THE POSSIBILITY OF SUCH DAMAGES; OR (ii) ANY AMOUNT IN EXCESS
 *    OF THE AMOUNT ACTUALLY PAID FOR THE SOFTWARE ITSELF OR U.S. $1, WHICHEVER
 *    IS GREATER. THESE LIMITATIONS SHALL APPLY NOTWITHSTANDING ANY FAILURE OF
 *    ESSENTIAL PURPOSE OF ANY LIMITED REMEDY.
 *
 *****************************************************************************/

#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <unistd.h>
#include <sys/time.h>
#include <errno.h>
#include <signal.h>
#include <assert.h>
#include "bstd.h"
#include "bmemperf_server.h"
#include "bmemperf_cgi.h"
#include "bmemperf_utils.h"
#include "nexus_platform.h"
#include "bchp_common.h"

#define PRINTF2                      noprintf
#define MAXHOSTNAME                  80
#define PERF_FILE_FULL_PATH_LEN      64
#define SATA_USB_FILE_FULL_PATH_LEN  64
#define LINUX_TOP_FILE_FULL_PATH_LEN 64

static void reusePort( int sock );

static unsigned char Quit = 0;

static bool                    initializationDone = false;
static unsigned int            g_client_list[BMEMPERF_NUM_MEMC][BMEMPERF_MAX_SUPPORTED_CLIENTS]; /* BMEMPERF_CGI_INVALID indicates no client id is desired */
static bmemperf_client_data    g_savedClientDataSorted[BMEMPERF_NUM_MEMC][BMEMPERF_MAX_NUM_CLIENT];
static bmemperf_irq_data       g_savedIrqData;
static unsigned long int       g_ContextSwitchesPrev = 0;
static unsigned long int       g_ContextSwitchesDelta = 0;
static bmemperf_boxmode_source g_boxmodeSource = {0, 0};
int   g_MegaBytes           = 0; /* set to 1 when user wants data displayed in megabytes instead of megabits (default) */
int   g_MegaBytesDivisor[2] = {1, 8};
char *g_MegaBytesStr[2] = {"Mbps", "MBps"};

typedef struct
{
    char deviceName[32];
} bmemperf_device_name;

typedef struct
{
    long int          uptime;
    unsigned int      major;
    unsigned int      minor;
    unsigned long int readsCompletedSuccessfully;
    unsigned long int readsMerged;
    unsigned long int readsSectors;
    unsigned long int readsMilliseconds;
    unsigned long int writesCompletedSuccessfully;
    unsigned long int writesMerged;
    unsigned long int writesSectors;
    unsigned long int writesMilliseconds;
} bmemperf_device_data;

typedef struct
{
    float readMbps;
    float writeMbps;
} bmemperf_device_mbps;

#define BMEMPERF_SATA_USB_HISTORY_MAX 10
static pthread_t         gSataUsbThreadId = 0;
static bool              gSataUsbFirstPassAfterInit = false;
static unsigned long int gSataUsbTimeout  = 0; /* gather function increments it; request function clears it out; if we reach 5, stop gathering */
bmemperf_device_name     gSataUsbDeviceNames[BMEMPERF_SATA_USB_MAX];
bmemperf_device_data     gSataUsbDataPrev[BMEMPERF_SATA_USB_MAX];
bmemperf_device_data     gSataUsbDataNow[BMEMPERF_SATA_USB_MAX];
bmemperf_device_mbps     gSataUsbMbps[BMEMPERF_SATA_USB_MAX];
bmemperf_device_mbps     gSataUsbMbpsHistory[BMEMPERF_SATA_USB_MAX][BMEMPERF_SATA_USB_HISTORY_MAX];
unsigned int             gSataUsbMbpsHistoryIdx = 0;
pthread_mutex_t          gSataUsbMutex;

/**
 *  Function: This function will initialize the specified mutex variable.
 **/
int Bmemperf_Server_InitMutex(
    pthread_mutex_t *mutex
    )
{
    if (pthread_mutex_init( mutex, NULL ))
    {
        printf( "%s: pthread_mutex_init failure; \n", __FUNCTION__ );
        return( 1 );
    }
    else
    {
        return( 0 );
    }
}

/**
 *  Function: This function will lock the specified mutex variable.
 **/
int Bmemperf_Server_LockMutex(
   pthread_mutex_t *mutex
    )
{
    int rc = 0;

    rc = pthread_mutex_lock( mutex );
    return( rc );
}

/**
 *  Function: This function will unlock the specified mutex variable.
 **/
void Bmemperf_Server_UnlockMutex(
   pthread_mutex_t *mutex
    )
{
    if (pthread_mutex_unlock( mutex ))
    {
        fprintf( stderr, "pthread_mutex_unlock failed" );
        assert( 0 );
    }
    return;
}

/**
 *  Function: This function will uninit the specified mutex variable.
 **/
void Bmemperf_Server_UninitMutex(
   pthread_mutex_t *mutex
    )
{
    pthread_mutex_destroy( mutex );
    return;
}

/**
 *  Function: This function is the prototype for Bmemperf_ReadRequest() API.
 **/
static int Bmemperf_ReadRequest(
    int                psd,
    struct sockaddr_in from,
    bmemperf_request  *pRequest,
    bmemperf_response *pResponse
    );

/**
 *  Function: This function will close the specified socket and exit the app.
 **/
static int CloseAndExit(
    int         socketFd,
    const char *reason
    )
{
    PRINTF( "%s: socket %d; reason (%s)\n", __FUNCTION__, socketFd, reason );
    if (socketFd>0) {close( socketFd ); }
    exit( 0 );
}

/**
 *  Function: This function will open a connection to a specific port that will be used to receive and send data
 *  from the user's browser.
 **/
static int startServer(
    void
    )
{
    int                fromlen;
    int                struct_length;
    int                pn;
    int                sd           = 0, psd = 0;
    unsigned long int  requestCount = 0;
    struct sockaddr_in server;
    struct sockaddr_in from;
    bmemperf_request   request;
    bmemperf_response  response;

    /* initialize the boxmode information (i.e. does it come from env variable or /proc file system */
    memset( &g_boxmodeSource, 0, sizeof( g_boxmodeSource ));
    get_boxmode( &g_boxmodeSource );
    printf( "Changing boxmode to %d\n", g_boxmodeSource.boxmode );
    bmemperf_boxmode_init( g_boxmodeSource.boxmode );

    /* Construct name of socket */
    server.sin_family      = AF_INET;
    server.sin_addr.s_addr = htonl( INADDR_ANY );
    pn                     = htons( BMEMPERF_SERVER_PORT );
    server.sin_port        = pn;

    /* Create socket on which to send and receive */

    sd = socket( AF_INET, SOCK_STREAM, IPPROTO_TCP );

    if (sd < 0)
    {
        perror( "opening stream socket" );
        exit( -1 );
    }

    /* this allows the server to re-start quickly instead of fully wait for TIME_WAIT which can be as large as 2 minutes */
    reusePort( sd );

    if (bind( sd, (struct sockaddr *)&server, sizeof( server )) < 0)
    {
        CloseAndExit( sd, "binding name to stream socket" );
    }

    /* get port information and  prints it out */
    struct_length = sizeof( server );

    if (getsockname( sd, (struct sockaddr *)&server, (unsigned int *)&struct_length ))
    {
        CloseAndExit( sd,  "getting socket name" );
    }
    PRINTF( "%s - Server Port is: %d\n", __FUNCTION__, ntohs( server.sin_port ));

    /* accept TCP connections from clients and fork a process to serve each */
    listen( sd, 4 );
    fromlen = sizeof( from );

    while (Quit == 0) {
        PRINTF( "%s - Waiting to accept socket connections; Quit %u; requestCount %lu\n", __FUNCTION__, Quit, requestCount );
        psd = accept( sd, (struct sockaddr *)&from, (unsigned int *)&fromlen );
        requestCount++;
        memset( &request, 0, sizeof( request ));
        memset( &response, 0, sizeof( response ));
        Bmemperf_ReadRequest( psd, from, &request, &response );
    }

    CloseAndExit( sd, "quit detected" );

    return( 0 );
} /* startServer */

static int addClientIdToList(
    unsigned int client_id,
    unsigned int request_memc
    )
{
    unsigned int client;

    if (( request_memc < BMEMPERF_NUM_MEMC ) && ( client_id < BMEMPERF_MAX_NUM_CLIENT ))
    {
        /* loop through global list to add the user's request */
        for (client = 0; client<BMEMPERF_MAX_SUPPORTED_CLIENTS; client++)
        {
            PRINTF( "%s: g_client_list[%u][%u] is %u\n", __FUNCTION__, request_memc, client, g_client_list[request_memc][client] );
            /* if client id is already in the table */
            if (g_client_list[request_memc][client] == client_id)
            {
                PRINTF( "%s: for memc %u, client_id %u is already in the global table at idx %u\n", __FUNCTION__, request_memc, client_id, client );
                break;
            }
            else if (g_client_list[request_memc][client] == BMEMPERF_CGI_INVALID)
            {
                PRINTF( "%s: for memc %u, client_id %u added to the global table at idx %u\n", __FUNCTION__, request_memc, client_id, client );
                g_client_list[request_memc][client] = client_id;
                break;
            }
        }
    }
    else
    {
        printf( "%s: memc (%u) or client_id (%u) is invalid\n", __FUNCTION__, request_memc, client_id );
    }
    return( 0 );
} /* addClientIdToList */

static int deleteClientIdFromList(
    unsigned int client_id,
    unsigned int request_memc
    )
{
    unsigned int client, remaining_client;

    if (( request_memc < BMEMPERF_NUM_MEMC ) && ( client_id < BMEMPERF_MAX_NUM_CLIENT ))
    {
        /* loop through global list to delete the user's request */
        for (client = 0; client<BMEMPERF_MAX_SUPPORTED_CLIENTS; client++)
        {
            PRINTF( "%s: g_client_list[%u][%u] is %u\n", __FUNCTION__, request_memc, client, g_client_list[request_memc][client] );
            /* if client id is already in the table */
            if (g_client_list[request_memc][client] == client_id)
            {
                g_client_list[request_memc][client] = BMEMPERF_CGI_INVALID;
                PRINTF( "%s: for memc %u, client_id %u has been deleted from the global table at idx %u\n", __FUNCTION__, request_memc,
                    client_id, client );

                /* now move any remaining clients up one row*/
                for (remaining_client = client; remaining_client<BMEMPERF_MAX_SUPPORTED_CLIENTS-1; remaining_client++)
                {
                    PRINTF( "%s: g_client_list[%u][%u] replaced with %u\n", __FUNCTION__, request_memc, remaining_client,
                        g_client_list[request_memc][remaining_client+1] );
                    g_client_list[request_memc][remaining_client] = g_client_list[request_memc][remaining_client+1];
                }
                /* tag the last entry as unused */
                g_client_list[request_memc][BMEMPERF_MAX_SUPPORTED_CLIENTS-1] = BMEMPERF_CGI_INVALID;
                PRINTF( "%s: g_client_list[%u][%u] replaced with %u\n", __FUNCTION__, request_memc, BMEMPERF_MAX_SUPPORTED_CLIENTS-1, BMEMPERF_CGI_INVALID );

                /* we found the one to delete; don't look any further in the list */
                break;
            }
            else if (g_client_list[request_memc][client] == BMEMPERF_CGI_INVALID)
            {
                /* no need to look any further */
                break;
            }
        }
        PRINTF( "%s: after deletion: ", __FUNCTION__ );
        for (client = 0; client<BMEMPERF_MAX_SUPPORTED_CLIENTS; client++)
        {
            int temp = g_client_list[request_memc][client];
            PRINTF( "%u:%-3d ", client, temp );
        }
        PRINTF( "\n" );
    }
    else
    {
        printf( "%s: memc (%u) or client_id (%u) is invalid\n", __FUNCTION__, request_memc, client_id );
    }
    return( 0 );
} /* deleteClientIdFromList */

static unsigned char setClientErrCnt(
    unsigned int  memc,
    unsigned int  client_id,
    unsigned char newValue
    )
{
    unsigned int client;

    for (client = 0; client<BMEMPERF_MAX_NUM_CLIENT; client++)
    {
        if (g_savedClientDataSorted[memc][client].client_id == client_id)
        {
            PRINTF( "%s: match -> g_savedClientDataSorted[%u][%u] <- %u for client_id %u\n", __FUNCTION__, memc, client, newValue, client_id );
            g_savedClientDataSorted[memc][client].err_cnt = newValue;
            return( 0 );
        }
    }

    return( 0 );
}

/**
 *  Function: This function will determine if the specified client had a block out error in the previous pass.
 *  If an error is detected, its error counter will be incremented. The error count will max out at UCHAR_MAX.
 **/
static int updateClientErrCnt(
    unsigned int client2,
    unsigned int memc
    )
{
    if (bmemperf_get_arb_err( g_savedClientDataSorted[memc][client2].client_id, memc ))
    {
        if (( g_savedClientDataSorted[memc][client2].err_cnt < UCHAR_MAX ) && ( g_savedClientDataSorted[memc][client2].rr == 0 ))
        {
            g_savedClientDataSorted[memc][client2].err_cnt++;
            #if 0
            printf( "error detected for client %3u in memc %u; client_id %3u; bo_val %u (%p)\n", client2, memc, g_savedClientDataSorted[memc][client2].client_id,
                g_savedClientDataSorted[memc][client2].block_out, &( g_savedClientDataSorted[memc][client2].err_cnt ));
            #endif
        }
    }

    return( 0 );
}

/**
 *  Function: When the web page is first displayed, we display a list of clients based on the bandwidth values
 *  during that first pass. Subsequent passes, we want to display the client list in the same order as this
 *  first pass through. In order to keep this first-pass list, we have to search the first-pass list for the
 *  client that we are needing to update.
 **/
static int updateClient(
    unsigned int          client_id,
    unsigned int          memc,
    bmemperf_client_data *pClientData
    )
{
    unsigned int client2;

    /* find this client's entry in the saved array */
    for (client2 = 0; client2<BMEMPERF_MAX_NUM_CLIENT; client2++)
    {
        if (g_savedClientDataSorted[memc][client2].client_id == client_id)
        {
            g_savedClientDataSorted[memc][client2].bw          = pClientData->bw;
            g_savedClientDataSorted[memc][client2].is_detailed = pClientData->is_detailed;
            g_savedClientDataSorted[memc][client2].rr          = pClientData->rr;
            g_savedClientDataSorted[memc][client2].block_out   = pClientData->block_out;

            updateClientErrCnt( client2, memc );

            return( 0 );
        }
    }

    PRINTF( "%s: client_id %u not found in saved array\n", __FUNCTION__, client_id );

    /* if we get here, then the client_id was not found in the previous saved list; add it to the end */
    for (client2 = 0; client2<BMEMPERF_MAX_NUM_CLIENT; client2++)
    {
        if (g_savedClientDataSorted[memc][client2].client_id == BMEMPERF_CGI_INVALID)
        {
            g_savedClientDataSorted[memc][client2] = *pClientData;
            PRINTF( "new memc%u:%u id %u; bw %u; \n", memc, client2, client_id, pClientData->bw );

            updateClientErrCnt( client2, memc );

            return( 0 );
        }
        else
        {
            PRINTF( "%s: for memc %u, saved element %u taken by id %u\n", __FUNCTION__, memc, client2, g_savedClientDataSorted[memc][client2].client_id );
        }
    }

    return( 0 );
} /* updateClient */

/**
 *  Function: This function will call get_interrupt_counts() API to copy the interrupt counts to a local
 *  structure. This local structure will be used to determine the delta counts from the last pass through.
 **/
static int bmemperf_computeIrqData(
    unsigned int       numActiveCpus,
    bmemperf_irq_data *pIrqData
    )
{
    unsigned int             cpu = 0;
    unsigned int             irq = 0;
    bmemperf_irq_data        irqDataNow;
    float                    uptimeDelta = 0;
    unsigned long int        irqTotal    = 0;
    static float             irqAvg      = 0;
    static unsigned long int irqAvgCount = 0;
    static unsigned long int irqAvgFirst = 0;
    bmemperf_proc_stat_info  lProcStatInfo;

    memset( &irqDataNow, 0, sizeof( irqDataNow ));
    memset( &lProcStatInfo, 0, sizeof( lProcStatInfo ));

    getUptime( &irqDataNow.uptime );
    PRINTF( "%5.3f - %5.3f = %5.3f\n", irqDataNow.uptime, g_savedIrqData.uptime, irqDataNow.uptime - g_savedIrqData.uptime );

    /* calculate the cummulative number of interrupts that happened since we booted up */
    get_interrupt_counts( &irqDataNow );

    PRINTF( "%s: numCpus %u: ", __FUNCTION__, numActiveCpus );
    /* subtract off the number of interrupts that we saw the last pass through */
    for (cpu = 0; cpu < numActiveCpus; cpu++)
    {
        PRINTF2( "%u:", cpu );
        /* if no data has been saved previously, return 0; otherwise, the returned value could be a very very large number */
        if (g_savedIrqData.irqCount[cpu] == 0)
        {
            pIrqData->irqCount[cpu] = 0;
        }
        else
        {
            if (g_savedIrqData.uptime > 0)
            {
                uptimeDelta = 1.0 * irqDataNow.irqCount[cpu];
                /*printf("%5.1f ", uptimeDelta );*/
                uptimeDelta -= 1.0 * g_savedIrqData.irqCount[cpu];
                /*printf("%5.1f ", uptimeDelta );*/
                /*uptimeDelta *= ( irqDataNow.uptime - g_savedIrqData.uptime ); */ /* adjust the value to account for 99 jiffies this second versus 100 this second */
                PRINTF( "(%5.1f)", uptimeDelta );
                pIrqData->irqCount[cpu] = uptimeDelta;
                PRINTF( "->%lu (%lu)\t", pIrqData->irqCount[cpu], irqDataNow.irqCount[cpu] - g_savedIrqData.irqCount[cpu] );
            }
            else
            {
                pIrqData->irqCount[cpu] = irqDataNow.irqCount[cpu] - g_savedIrqData.irqCount[cpu];
            }
        }
        PRINTF( "%-5lu ", pIrqData->irqCount[cpu] );
    }

    /* read interrupt data and context switch data from /proc/stat file */
    get_proc_stat_info( &lProcStatInfo );

    PRINTF("%s: delta (%lu) = now (%lu) - prev (%lu)\n", __FUNCTION__,  g_ContextSwitchesDelta, lProcStatInfo.contextSwitches, g_ContextSwitchesPrev );
    g_ContextSwitchesDelta = lProcStatInfo.contextSwitches - g_ContextSwitchesPrev;
    g_ContextSwitchesPrev = lProcStatInfo.contextSwitches;

    /* the irqTotal is computed from the file /proc/stat and not from adding entries from /proc/interrupts */
    irqDataNow.irqTotal = irqTotal = lProcStatInfo.irqTotal;

    /* adjust value to account for 99 jiffies per second versus 100 or 101 or 102 etc. */
    uptimeDelta = ( irqDataNow.uptime - g_savedIrqData.uptime );

    pIrqData->irqTotal = irqDataNow.irqTotal - g_savedIrqData.irqTotal;
    if (irqAvgFirst == 0)
    {
        irqAvgFirst = irqDataNow.irqTotal;
    }
    /* don't adjust the delta count if the uptime delta is way off */
    if (( uptimeDelta > 0 ) && ( uptimeDelta < 1.5 ))
    {
        float temp = 1.0 /*uptimeDelta*/;
        PRINTF2( "irqTotal was %-5lu (%-5lu - %-5lu); ", pIrqData->irqTotal, irqDataNow.irqTotal, g_savedIrqData.irqTotal );
        temp              *= pIrqData->irqTotal;
        pIrqData->irqTotal = temp;
        PRINTF2( "mul %5.2f is %-5lu;    ", 1.0 /*uptimeDelta*/, pIrqData->irqTotal );
        {
            float             delta    = pIrqData->irqTotal;
            float             oldAvg   = irqAvg;
            unsigned long int oldCount = irqAvgCount;

            irqAvg = ( irqAvg*irqAvgCount ) + delta;
            irqAvgCount++;
            irqAvg /= irqAvgCount;

            PRINTF2( " 2222 avg (%5.1f * %lu) + %5.1f = %5.1f; first (%lu - %lu)/%lu = %lu\n", oldAvg, oldCount, delta, irqAvg, irqDataNow.irqTotal, irqAvgFirst, irqAvgCount,
                ( irqDataNow.irqTotal - irqAvgFirst )/irqAvgCount );
        }
    }
    PRINTF( "irqTotal %-3lu (%lu - %lu); adj %5.1f\n", pIrqData->irqTotal, irqDataNow.irqTotal, g_savedIrqData.irqTotal, uptimeDelta );

    /* copy the IRQ details to the response buffer */
    PRINTF( "%s: memcpy to irqDetails ... %u bytes 1; %u bytes 2\n", __FUNCTION__,  sizeof( pIrqData->irqDetails ), sizeof( pIrqData->irqDetails ));
    memcpy( &pIrqData->irqDetails, &irqDataNow.irqDetails, sizeof( pIrqData->irqDetails ));

    /* copy the previous counts into the response buffer */
    for (cpu = 0; cpu < numActiveCpus; cpu++)
    {
        for (irq = 0; irq < BMEMPERF_IRQ_MAX_TYPES; irq++)
        {
            pIrqData->irqDetails[irq].irqCountPrev[cpu] = g_savedIrqData.irqDetails[irq].irqCount[cpu];
        }
    }
    /* save the current values to be used to compute the delta the next pass through */
    g_savedIrqData = irqDataNow;

    return( 0 );
} /* bmemperf_computeIrqData */

/**
 *  Function: This function will perform a 10-second perf record. It will run as a separate thread until the perf record
 *  operation is complete.
 **/
static void *bmemperf_perf_record_thread(
    void *data
    )
{
    char               line[MAX_LINE_LENGTH];
    unsigned long int *pduration = (unsigned long int *)data;
    char               perfFilename[PERF_FILE_FULL_PATH_LEN];

    PrependTempDirectory( perfFilename, sizeof( perfFilename ), PERF_REPORT_OUTPUT_FILE );

    if (data == NULL)
    {
        printf( "%s: arg1 cannot be NULL\n", __FUNCTION__ );
        exit( EXIT_FAILURE );
    }

    sprintf( line, "ulimit -c unlimited && %s/perf record -a -g sleep %ld > %s 2>&1", BIN_DIR, *pduration, perfFilename );
    printf( "%s: issuing system(%s)\n", __FUNCTION__, line );

    system( line );

    printf( "%s: complete.\n", __FUNCTION__ );

    pthread_exit( 0 );
} /* bmemperf_perf_record_thread */

/**
 *  Function: This function will start a new thread that will run until the perf record operation is complete.
 **/
static int bmemperf_start_perf_record(
    unsigned long int duration
    )
{
    pthread_t                perfRecordThreadId = 0;
    void                    *(*threadFunc)( void * );
    static unsigned long int threadOption = 0;

    threadFunc   = bmemperf_perf_record_thread;
    threadOption = duration;

    if (pthread_create( &perfRecordThreadId, NULL, threadFunc, (void *)&threadOption ))
    {
        printf( "%s: could not create thread for perf record; %s\n", __FUNCTION__, strerror( errno ));
    }

    return( 0 );
} /* bmemperf_start_perf_record */

/**
 *  Function: This function will perform a 10-second perf stat. It will run as a separate thread until the perf
 *  stat operation is complete.
 **/
static void *bmemperf_perf_stat_thread(
    void *data
    )
{
    char               line[MAX_LINE_LENGTH];
    unsigned long int *pduration = (unsigned long int *)data;
    char               perfFilename[PERF_FILE_FULL_PATH_LEN];

    PrependTempDirectory( perfFilename, sizeof( perfFilename ), PERF_STAT_OUTPUT_FILE );

    if (data == NULL)
    {
        printf( "%s: arg1 cannot be NULL\n", __FUNCTION__ );
        exit( EXIT_FAILURE );
    }

    /* activate perf with limit to top 20 */
    sprintf( line, "%s/perf stat -a -e bus-cycles,cycles,instructions,cache-references,cache-misses,L1-dcache-loads,"
                   "L1-dcache-load-misses,L1-dcache-stores,L1-dcache-store-misses,L1-icache-loads,L1-icache-load-misses,"
                   "LLC-loads,LLC-load-misses,LLC-stores,LLC-store-misses,dTLB-load-misses,dTLB-store-misses,iTLB-load-misses,"
                   "iTLB-load-misses sleep %ld > %s 2>&1", BIN_DIR, *pduration, perfFilename );
    printf( "%s: issuing system(%s)\n", __FUNCTION__, line );

    system( line );

    printf( "%s: complete.\n", __FUNCTION__ );

    pthread_exit( 0 );
} /* get_perfreport_data */

static int bmemperf_sata_usb_array_update(
    bmemperf_device_data *lSataUsbDataNow,
    const char           *lDeviceName
    )
{
    unsigned int idx;

    for (idx = 0; idx<BMEMPERF_SATA_USB_MAX; idx++)
    {
        /* if we find a slot that does not have a device name in it, the one we are searching for does not exist in the array */
        if (strlen( gSataUsbDeviceNames[idx].deviceName ) == 0)
        {
            break;
        }
        else if (strcmp( gSataUsbDeviceNames[idx].deviceName, lDeviceName ) == 0)
        {
            /*printf( "adding sata_usb data to idx %u for (%s)\n", idx, lSataUsbDataNow->deviceName );*/
            gSataUsbDataNow[idx] = *lSataUsbDataNow;
            return( 0 );
        }
    }

    printf( "Could not find deviceName (%s) in gSataUsbDeviceNames.\n", lDeviceName );
    return( 0 );
} /* bmemperf_sata_usb_array_update */

static bool bmemperf_linux_top_stop = false; /* set to true when CMD_STOP_LINUX_TOP is detected */
/**
 *  Function: This function will handle the signal SIGTERM. This signal is caught when the server is
 *            attempting to pthread_kill() the thread that is performing the Linux Top command.
 *            When the user unchecks the LinuxTop checkbox on the web page, a command is sent to the
 *            server which in turn signals the controlling thread to stop performing the Linux Top
 *            command.
 **/
static void bmemperf_linux_top_sigterm(
    int signum
    )
{
    bmemperf_linux_top_stop = true;
    PRINTF( "%s: got signal %d; bmemperf_linux_top_stop now is %d\n", __FUNCTION__, signum, bmemperf_linux_top_stop );
    return;
}

/**
 *  Function: This function will call the 'top' utility until ordered to stop.
 **/
static void *bmemperf_linux_top_thread(
    void *data
    )
{
    char cmd[128];
    char linuxTopFilename[LINUX_TOP_FILE_FULL_PATH_LEN];

    BSTD_UNUSED( data );

    PrependTempDirectory( linuxTopFilename, sizeof( linuxTopFilename ), LINUX_TOP_OUTPUT_FILE );
    PRINTF( "%s: filename (%s)\n", __FUNCTION__, linuxTopFilename );

    sprintf( cmd, "%s/top -b -d.1 -n 1 > %s", BIN_DIR, linuxTopFilename );

    /* collect data until the user un-checks the LinuxTop Stats box */
    while (bmemperf_linux_top_stop == false)
    {
        PRINTF( "issuing cmd (%s)\n", cmd );
        system( cmd );

        usleep( 1000 * 500 ); /* 500 milliseconds */
    }

    printf( "%s: pthread_exit()\n", __FUNCTION__ );
    pthread_exit( 0 );
} /* bmemperf_linux_top_thread */

/**
 *  Function: This function will use the 'df' utility to scan for currently mounted devices. Only these devices
 *  will be searched for in the /proc/diskstats file during the one-second gathering.
 **/
static void bmemperf_sata_usb_scan(
    void
    )
{
    FILE *cmd = NULL;
    char  line[MAX_LENGTH_CPU_STATUS];
    int   gSataUsbDeviceNamesIdx = 0;

    strncpy( line, "df | grep \"^/dev/\" ", sizeof ( line ) - 1 );
    cmd = popen( line, "r" );

    do
    {
        memset( line, 0, sizeof( line ));

        fgets( line, MAX_LENGTH_CPU_STATUS, cmd ); /* /dev/sda4            958852568    917028 909919940   0% /data */

        if (strlen( line ))
        {
            char *pos = strchr( &line[1], '/' ); /* find the beginning of the unique device name (skipping over the first slash) */
            if (pos)
            {
                char *posspace = NULL;
                pos++;
                posspace = strchr( pos, ' ' ); /* find the first space after the device name */
                if (posspace)
                {
                    *posspace = '\0'; /* null-terminate the device name */
                    /* if there is space to add this device name to the list */
                    if (gSataUsbDeviceNamesIdx < BMEMPERF_SATA_USB_MAX)
                    {
                        strncpy( gSataUsbDeviceNames[gSataUsbDeviceNamesIdx].deviceName, pos, sizeof( gSataUsbDeviceNames[gSataUsbDeviceNamesIdx].deviceName ) - 1 );
                        PRINTF( "%s: added gSataUsbDeviceNames[%d]:(%s)\n", __FUNCTION__, gSataUsbDeviceNamesIdx, gSataUsbDeviceNames[gSataUsbDeviceNamesIdx].deviceName );
                        gSataUsbDeviceNamesIdx++;
                    }
                }
            }
        }
    } while (strlen( line ));
    PRINTF( "\n" );

    pclose( cmd );
    return;
} /* getCpuOnline */

/**
 *  Function: This function will read the /proc/diskstats file to gather statistics for SATA and USB drives.
 **/
static void *bmemperf_sata_usb_thread(
    void *data
    )
{
    if (data == NULL)
    {
        printf( "%s: arg1 cannot be NULL\n", __FUNCTION__ );
        exit( EXIT_FAILURE );
    }

    Bmemperf_Server_LockMutex( &gSataUsbMutex );

    printf( "%s: clearing gSataUsb arrays. \n", __FUNCTION__ );
    memset( &gSataUsbDataPrev, 0, sizeof( gSataUsbDataPrev ));
    memset( &gSataUsbDeviceNames, 0, sizeof( gSataUsbDeviceNames ));
    memset( &gSataUsbMbpsHistory, 0, sizeof( gSataUsbMbpsHistory ));
    gSataUsbMbpsHistoryIdx = 0;
    gSataUsbFirstPassAfterInit = true;

    /* scan for currently-mounted device names */
    bmemperf_sata_usb_scan(); /* function updates gSataUsbDeviceNames[] array */

    Bmemperf_Server_UnlockMutex( &gSataUsbMutex );

    /* collect data until no one has requested USB/SATA for 5 seconds */
    while (gSataUsbTimeout <  5)
    {
        unsigned int         idx      = 0;
        char                *pos      = NULL;
        char                *posEol   = NULL;
        char                *posBol   = NULL;
        char                *contents = NULL;
        char                 cmd[128];
        unsigned char        differenceFound = 0;
        bmemperf_device_data lSataUsbDataNow;
        char                 sataUsbFilename[SATA_USB_FILE_FULL_PATH_LEN];

        gSataUsbTimeout++; /* request function should zero this out every time a request comes in; if we reach time, stop gathering */
        if (gSataUsbTimeout > 1)
        {
            printf( "%s: gSataUsbTimeout (%ld)\n", __FUNCTION__, gSataUsbTimeout );
        }

        PrependTempDirectory( sataUsbFilename, sizeof( sataUsbFilename ), SATA_USB_OUTPUT_FILE );
        PRINTF( "%s: filename (%s)\n", __FUNCTION__, sataUsbFilename );

        differenceFound = 0;

        memset( &gSataUsbDataNow, 0, sizeof( gSataUsbDataNow ));
        memset( &lSataUsbDataNow, 0, sizeof( lSataUsbDataNow ));

        sprintf( cmd, "cp -f /proc/diskstats %s", sataUsbFilename );
        /*printf( "issuing cmd (%s)\n", cmd );*/
        system( cmd );

        contents = GetFileContents( sataUsbFilename );

        if (contents == NULL)
        {
            printf( "file (%s) had no contents\n", sataUsbFilename );
            continue;
        }

        /* loop through known devices and find the matching line in the diskstats contents */
        for (idx = 0; idx<BMEMPERF_SATA_USB_MAX; idx++)
        {
            if (strlen( gSataUsbDeviceNames[idx].deviceName ) == 0)
            {
                /* we have reached the end of known devices */
                break;
            }

            pos = strstr( contents, gSataUsbDeviceNames[idx].deviceName );
            /*printf("%s: found device (%s) at offset %d\n", __FUNCTION__, gSataUsbDeviceNames[idx].deviceName, pos - contents );*/

            /* if the device name was found in diskstats file */
            if (pos)
            {
                char lDeviceName[32];

                posEol = strchr( pos, '\n' );
                /*printf("%s: for device (%s) posEol %p\n", __FUNCTION__, gSataUsbDeviceNames[idx].deviceName, posEol );*/
                if (posEol)
                {
                    posEol[0] = '\0'; /* null-terminate the line */
                }

                posBol = pos - 12;

                /*printf("%s: for device (%s) line (%s)\n", __FUNCTION__, gSataUsbDeviceNames[idx].deviceName, posBol );*/
                /*
                   8       0 sda 70715 13758 8161780 6120 4 1 5 0 0 2950 6120
                   8       1 sda1 70714 13758 8161772 6090 4 1 5 0 0 2920 6090
                  31      10 mtdblock10 0 0 0 0 0 0 0 0 0 0 0
                 179       0 mmcblk0 170 9048 9257 610 0 0 0 0 0 330 610
                 179       1 mmcblk0p1 169 9048 9249 600 0 0 0 0 0 320 600
                */

                sscanf( posBol, "%u %u %s %lu %lu %lu %lu %lu %lu %lu %lu ", &lSataUsbDataNow.major, &lSataUsbDataNow.minor, &lDeviceName[0],
                    &lSataUsbDataNow.readsCompletedSuccessfully, &lSataUsbDataNow.readsMerged, &lSataUsbDataNow.readsSectors, &lSataUsbDataNow.readsMilliseconds,
                    &lSataUsbDataNow.writesCompletedSuccessfully, &lSataUsbDataNow.writesMerged, &lSataUsbDataNow.writesSectors, &lSataUsbDataNow.writesMilliseconds );
                bmemperf_sata_usb_array_update( &lSataUsbDataNow, lDeviceName );

                /* debug */
                if (( lSataUsbDataNow.readsSectors != gSataUsbDataPrev[idx].readsSectors ) || ( lSataUsbDataNow.writesSectors != gSataUsbDataPrev[idx].writesSectors ))
                {
                    PRINTF( "%s: /dev/%s: rd %-8lu, wr %-8lu\n", __FUNCTION__, lDeviceName, lSataUsbDataNow.readsSectors, lSataUsbDataNow.writesSectors );
                }
                if (posEol)
                {
                    posEol[0] = '\n'; /* restore the newline character */
                }
            }
        } /* end for each device name */

        free( contents );

        Bmemperf_Server_LockMutex( &gSataUsbMutex );
        /* for each I/O device */
        for (idx = 0; idx<sizeof( gSataUsbDataNow )/sizeof( gSataUsbDataNow[0] ); idx++)
        {
            unsigned long int deltaSectors = 0;
            if (( gSataUsbDataNow[idx].readsSectors > gSataUsbDataPrev[idx].readsSectors ) || ( gSataUsbDataNow[idx].writesSectors > gSataUsbDataPrev[idx].writesSectors ))
            {
                differenceFound            = 1;
                deltaSectors               = gSataUsbDataNow[idx].readsSectors - gSataUsbDataPrev[idx].readsSectors;
                gSataUsbMbps[idx].readMbps = deltaSectors * 512.0 * 8.0 / 1024.0 / 1024.0;
                /*if (strlen( gSataUsbDataPrev[idx].deviceName ))*/
                {
                    PRINTF( "device[%u] (%-4s) %6.2f Mbps ", idx, gSataUsbDeviceNames[idx].deviceName, gSataUsbMbps[idx].readMbps );
                }

                deltaSectors                = gSataUsbDataNow[idx].writesSectors - gSataUsbDataPrev[idx].writesSectors;
                gSataUsbMbps[idx].writeMbps = deltaSectors * 512.0 * 8.0 / 1024.0 / 1024.0;
                /*if (strlen( gSataUsbDataPrev[idx].deviceName ))*/
                {
                    PRINTF( "%6.2f Mbps\n", gSataUsbMbps[idx].writeMbps );
                }
            }
            else
            {
                gSataUsbMbps[idx].readMbps  = 0;
                gSataUsbMbps[idx].writeMbps = 0;
                PRINTF( "device[%u] zero; ", idx );
            }

            /* save for 10-second history */
            if ( gSataUsbFirstPassAfterInit == false )
            {
                gSataUsbMbpsHistory[idx][gSataUsbMbpsHistoryIdx].readMbps  = gSataUsbMbps[idx].readMbps;
                gSataUsbMbpsHistory[idx][gSataUsbMbpsHistoryIdx].writeMbps = gSataUsbMbps[idx].writeMbps;
            }
        }

        /* the first pass through, the previous numbers are zero but the current readSectors/writeSectors are very large; skip the first pass */
        gSataUsbFirstPassAfterInit = false;

        gSataUsbMbpsHistoryIdx++;
        if (gSataUsbMbpsHistoryIdx >= BMEMPERF_SATA_USB_HISTORY_MAX) /* wrap around to zero if it's time to */
        {
            gSataUsbMbpsHistoryIdx = 0;
        }

        Bmemperf_Server_UnlockMutex( &gSataUsbMutex );
        PRINTF( "\n" );

        if (differenceFound)
        {
            Bmemperf_Server_LockMutex( &gSataUsbMutex );
            memcpy( &gSataUsbDataPrev, &gSataUsbDataNow, sizeof( gSataUsbDataNow ));
            Bmemperf_Server_UnlockMutex( &gSataUsbMutex );
        }

        /*remove( sataUsbFilename );*/

        sleep( 1 );
    }

    Bmemperf_Server_LockMutex( &gSataUsbMutex );
    printf( "%s: clearing gSataUsb arrays. \n", __FUNCTION__ );
    memset( &gSataUsbDataPrev, 0, sizeof( gSataUsbDataPrev ));
    memset( &gSataUsbDeviceNames, 0, sizeof( gSataUsbDeviceNames ));
    memset( &gSataUsbMbpsHistory, 0, sizeof( gSataUsbMbpsHistory ));
    gSataUsbMbpsHistoryIdx = 0;
    gSataUsbFirstPassAfterInit = true;
    Bmemperf_Server_UnlockMutex( &gSataUsbMutex );

    gSataUsbThreadId = 0;

    printf( "%s: complete.\n", __FUNCTION__ );

    pthread_exit( 0 );
} /* bmemperf_sata_usb_thread */

/**
 *  Function: This function will start a new thread that will run until the perf stat operation is complete.
 **/
static int bmemperf_start_perf_cache(
    unsigned long int duration
    )
{
    pthread_t                perfRecordThreadId = 0;
    void                    *(*threadFunc)( void * );
    static unsigned long int threadOption = 0;

    threadFunc   = bmemperf_perf_stat_thread;
    threadOption = duration;

    if (pthread_create( &perfRecordThreadId, NULL, threadFunc, (void *)&threadOption ))
    {
        printf( "%s: could not create thread for perf stat; %s\n", __FUNCTION__, strerror( errno ));
    }

    return( 0 );
}

/**
 *  Function: This function will compute the 10-second average in Mbps for data reads and writes to the
 *  various SATA and USB devices.
 **/
float bmemperf_sata_usb_compute_average(
    unsigned int deviceIdx,
    unsigned int readOrWrite /* 0: readMbps; 1: writeMbps */
    )
{
    unsigned int idx     = 0;
    float        average = 0.0;

    /* if the deviceName is invalid, stop computing */
    if (gSataUsbDeviceNames[deviceIdx].deviceName[0] == '\0')
    {
        return( average );
    }

    #ifdef DEBUG
    if ( deviceIdx == 0 ) printf( "%s: device[%u].%-5s: idx %d: %-5s ", __FUNCTION__, deviceIdx,
                                  gSataUsbDeviceNames[deviceIdx].deviceName, gSataUsbMbpsHistoryIdx,
                                  ( readOrWrite==0 ) ? "read" : "write" );
    #endif
    for (idx = 0; idx<BMEMPERF_SATA_USB_HISTORY_MAX; idx++)
    {
        if (readOrWrite == 0 /* user requested readMbps */)
        {
            average += gSataUsbMbpsHistory[deviceIdx][idx].readMbps;
            #ifdef DEBUG
            if ( deviceIdx == 0 ) printf("%-5.2f ", gSataUsbMbpsHistory[deviceIdx][idx].readMbps );
            #endif
        }
        else
        {
            average += gSataUsbMbpsHistory[deviceIdx][idx].writeMbps;
            #ifdef DEBUG
            if ( deviceIdx == 0 ) printf("%-5.2f ", gSataUsbMbpsHistory[deviceIdx][idx].writeMbps );
            #endif
        }
    }
    average /= BMEMPERF_SATA_USB_HISTORY_MAX;
    #ifdef DEBUG
    if ( deviceIdx == 0 ) printf( "... avg %5.2f Mbps \n", average );
    #endif
    return( average );
} /* bmemperf_sata_usb_compute_average */

/**
 *  Function: This function will gather the SATA and USB data that is collected by a separate thread and save
 *  the data into the response buffer being prepared to send back to the client.
 **/
static int bmemperf_sata_usb_gather(
    bmemperf_response *pResponse
    )
{
    unsigned int idx = 0;

    if (pResponse == NULL)
    {
        return( -1 );
    }

    gSataUsbTimeout = 0;

    for (idx = 0; idx<sizeof( gSataUsbDeviceNames )/sizeof( gSataUsbDeviceNames[0] ); idx++)
    {
        /* the first time we reach an empty device name, stop looking for data */
        if (gSataUsbDeviceNames[idx].deviceName[0] == '\0')
        {
            break;
        }
        strncpy( pResponse->response.cpuIrqData.sataUsbData[idx].deviceName, gSataUsbDeviceNames[idx].deviceName,
            sizeof( pResponse->response.cpuIrqData.sataUsbData[0].deviceName ) - 1 );
        #ifdef INSTANT_RESPONSE
        pResponse->response.cpuIrqData.sataUsbData[idx].readMbps  = gSataUsbMbps[idx].readMbps;
        pResponse->response.cpuIrqData.sataUsbData[idx].writeMbps = gSataUsbMbps[idx].writeMbps;
        #else /* use 10-second average */
        pResponse->response.cpuIrqData.sataUsbData[idx].readMbps  = bmemperf_sata_usb_compute_average( idx, 0 /* compute readMbps */ );
        pResponse->response.cpuIrqData.sataUsbData[idx].writeMbps = bmemperf_sata_usb_compute_average( idx, 1 /* compute writeMbps */ );
        #endif /* if defined INSTANT_RESPONE */
    }

    return( 0 );
} /* bmemperf_sata_usb_gather */

/**
 *  Function: This function will start a new thread that will gather the SATA and USB bandwidth statistics.
 **/
static int bmemperf_sata_usb_start(
    unsigned long int option
    )
{
    void                    *(*threadFunc)( void * );
    static unsigned long int threadOption = 0;

    /* if the thread has not already been started, start it now */
    if (( gSataUsbThreadId == 0 ) && ( option == BMEMPERF_CMD_START_SATA_USB ))
    {
        threadFunc   = bmemperf_sata_usb_thread;
        threadOption = 0;

        if (pthread_create( &gSataUsbThreadId, NULL, threadFunc, (void *)&threadOption ))
        {
            printf( "%s: could not create thread for sataUsb; %s\n", __FUNCTION__, strerror( errno ));
        }
        else
        {
            printf( "%s: Thread for SATA/USB started successfully; id %lx\n", __FUNCTION__, (long int) gSataUsbThreadId );
        }
    }
    else
    {
        PRINTF( "%s: Thread for SATA/USB already started; id %lx\n", __FUNCTION__, (long int) gSataUsbThreadId );
        if (option == BMEMPERF_CMD_STOP_SATA_USB)
        {
            /* gSataUsbThreadId = 0; thread will timeout by itself after 5 seconds of inactivity */
        }
    }

    return( 0 );
} /* bmemperf_sata_usb_start */

/**
 *  Function: This function will start a new thread that will save he output from the "top" utility.
 **/
static int bmemperf_start_linux_top(
    unsigned long int option
    )
{
    static pthread_t         linuxTopThreadId = 0;
    void                    *(*threadFunc)( void * );
    static unsigned long int threadOption = 0;

    /* if the thread has not already been started, start it now */
    if (( linuxTopThreadId == 0 ) && ( option == BMEMPERF_CMD_START_LINUX_TOP ))
    {
        threadFunc   = bmemperf_linux_top_thread;
        threadOption = 0;

        bmemperf_linux_top_stop = false;

        signal( SIGTERM, bmemperf_linux_top_sigterm );

        if (pthread_create( &linuxTopThreadId, NULL, threadFunc, (void *)&threadOption ))
        {
            printf( "%s: could not create thread for linuxTop; %s\n", __FUNCTION__, strerror( errno ));
        }
        else
        {
            PRINTF( "%s: Thread for LinuxTop started successfully; id %lx\n", __FUNCTION__, (long int) linuxTopThreadId );
        }
    }
    else
    {
        PRINTF( "%s: Thread for LinuxTop already started; id %lx\n", __FUNCTION__, (long int) linuxTopThreadId );
        if (option == BMEMPERF_CMD_STOP_LINUX_TOP)
        {
            PRINTF( "%s: Stopping LinuxTop; id %lx\n", __FUNCTION__, (long int) linuxTopThreadId );
            bmemperf_linux_top_stop = true;
            if (linuxTopThreadId)
            {
                PRINTF( "%s: pthread_kill ( %lx ) \n", __FUNCTION__, (long int) linuxTopThreadId );
                pthread_kill( linuxTopThreadId, SIGTERM );
                linuxTopThreadId = 0;
            }
        }
    }

    return( 0 );
} /* bmemperf_start_linux_top */

/**
 *  Function: This function will read the user's request coming in from the browser
 **/
static int Bmemperf_ReadRequest(
    int                psd,
    struct sockaddr_in from,
    bmemperf_request  *pRequest,
    bmemperf_response *pResponse
    )
{
    int         rc;
    static bool bFirstPass = true;

    PRINTF( "%s - %u Started new thread serving %s\n", __FUNCTION__, ntohs( from.sin_port ), inet_ntoa( from.sin_addr ));

    if (initializationDone == false)
    {
        PRINTF( "%s: memset(g_client_list to 0xff\n", __FUNCTION__ );
        memset( g_client_list, 0xFF, sizeof( g_client_list ));
        initializationDone = true;
    }
    /* get data from  clients and send it back */

    PRINTF( "%u Server is reading request (%u bytes) from client ... \n", ntohs( from.sin_port ), sizeof( *pRequest ));

    if (( rc = recv( psd, pRequest, sizeof( *pRequest ), 0 )) < 0)
    {
        PRINTF( "%u ", ntohs( from.sin_port ));
        CloseAndExit( psd, "receiving stream  message" );
    }

    if (rc > 0)
    {
        PRINTF( "%u %s: Received: from TCP/Client (%s); cmd (%u) \n", ntohs( from.sin_port ), DateYyyyMmDdHhMmSs(), inet_ntoa( from.sin_addr ), pRequest->cmd );
        PRINTF( "%s: cmd %u; cmdSecondary %u; cmdOption %lu\n", __FUNCTION__, pRequest->cmd, pRequest->cmdSecondary, pRequest->cmdSecondaryOption );
        switch (pRequest->cmd) {
            case BMEMPERF_CMD_RESET_ARB_ERRORS:
            {
                unsigned int memc, client;

                reset_error_counts();

                for (memc = 0; memc<BMEMPERF_NUM_MEMC; memc++)
                {
                    for (client = 0; client<BMEMPERF_MAX_NUM_CLIENT; client++)
                    {
                        g_savedClientDataSorted[memc][client].err_cnt = 0;
                    }
                }
                break;
            }
            case BMEMPERF_CMD_GET_OVERALL_STATS:
            {
                unsigned int memc, client;

                sprintf( pResponse->padding, "====================this is response; boxmode %d ============================", g_boxmodeSource.boxmode );
                pResponse->cmd = pRequest->cmd;

                PRINTF( "BMEMPERF_CMD_GET_OVERALL_STATS: boxmode request %d; prev %d\n", pRequest->boxmode, g_boxmodeSource.boxmode );
                /* check to see if the user has requested a boxmode change */
                if (pRequest->boxmode != g_boxmodeSource.boxmode)
                {
                    int memc;
                    int client;

                    printf( "Changing boxmode from %d to %d\n", g_boxmodeSource.boxmode, pRequest->boxmode );
                    bmemperf_boxmode_init( pRequest->boxmode );
                    g_boxmodeSource.boxmode = pRequest->boxmode;
                    g_boxmodeSource.source  = BOXMODE_BROWSER;
                    for (memc = 0; memc<BMEMPERF_NUM_MEMC; memc++)
                    {
                        for (client = 0; client<BMEMPERF_MAX_SUPPORTED_CLIENTS; client++)
                        {
                            g_client_list[memc][client] = BMEMPERF_CGI_INVALID;
                        }
                    }
                }

                pResponse->boxmode = g_boxmodeSource.boxmode;
                pResponse->source  = g_boxmodeSource.source;

                /* transfer requests to global server's structure; this allows multiple browser clients to make requests */
                for (memc = 0; memc<BMEMPERF_NUM_MEMC; memc++)
                {
                    for (client = 0; client<BMEMPERF_MAX_SUPPORTED_CLIENTS; client++)
                    {
                        if (pRequest->request.client_stats_data.client_list[memc][client] != BMEMPERF_CGI_INVALID)
                        {
                            PRINTF( "\n\n%s: action reqeusted for 0x%x: client_id %u for memc %u\n", __FUNCTION__,
                                pRequest->request.client_stats_data.client_list[memc][client],
                                pRequest->request.client_stats_data.client_list[memc][client] & 0xFF, memc );
                            /* if we are enabling the client id */
                            if (pRequest->request.client_stats_data.client_list[memc][client] & 0x100)
                            {
                                PRINTF( "%s: enable client_id %u for memc %u\n", __FUNCTION__, pRequest->request.client_stats_data.client_list[memc][client] & 0xFF, memc );
                                addClientIdToList( pRequest->request.client_stats_data.client_list[memc][client] & 0xFF, memc );
                            }
                            else
                            {
                                PRINTF( "%s: DISABLE client_id %u for memc %u\n", __FUNCTION__, pRequest->request.client_stats_data.client_list[memc][client] & 0xFF, memc );
                                deleteClientIdFromList( pRequest->request.client_stats_data.client_list[memc][client] & 0xFF, memc );
                            }
                        }
                    }
                }

                /* this sets the client list */
                bmemperf_getOverallStats( &pResponse->response.overallStats );

                /* set flag if one or more of the top 10 clients is also being detailed */
                for (memc = 0; memc<BMEMPERF_NUM_MEMC; memc++)
                {
                    for (client = 0; client<BMEMPERF_MAX_SUPPORTED_CLIENTS; client++)
                    {
                        /* if client_id is being detailed */
                        if (g_client_list[memc][client] != BMEMPERF_CGI_INVALID)
                        {
                            unsigned int client256;
                            for (client256 = 0; client256<BMEMPERF_MAX_NUM_CLIENT; client256++)
                            {
                                if (pResponse->response.overallStats.clientOverallStats[memc].clientData[client256].client_id == g_client_list[memc][client])
                                {
                                    pResponse->response.overallStats.clientOverallStats[memc].clientData[client256].is_detailed = true;
                                    PRINTF( "%s: pResponse->response.overallStats.clientOverallStats[%u].clientData[%-3u].is_detailed - %u\n", __FUNCTION__, memc,
                                        client256, pResponse->response.overallStats.clientOverallStats[memc].clientData[client256].client_id );
                                    break;
                                }
                            }
                        }
                    }
                }

                PRINTF( "%s: bFirstPass %u\n", __FUNCTION__, bFirstPass );
                if (( bFirstPass == true ))
                {
                    unsigned int memc, client;
                    bFirstPass = false;
                    PRINTF( "%s: saving client array sized [%u][%u] to g_savedClientDataSorted array; saved size %u; src size %u\n", __FUNCTION__, BMEMPERF_NUM_MEMC,
                        BMEMPERF_MAX_NUM_CLIENT, sizeof( g_savedClientDataSorted[memc][client] ),
                        sizeof( pResponse->response.overallStats.clientOverallStats[memc].clientData[client] ));
                    for (memc = 0; memc<BMEMPERF_NUM_MEMC; memc++)
                    {
                        for (client = 0; client<BMEMPERF_MAX_NUM_CLIENT; client++)
                        {
                            g_savedClientDataSorted[memc][client] = pResponse->response.overallStats.clientOverallStats[memc].clientData[client];
                        }
                    }
                }
                else
                {
                    unsigned int memc, client;
                    /* clear out previous bw values (for this pass, client may not have any bw usage in the past second ) */
                    for (memc = 0; memc<BMEMPERF_NUM_MEMC; memc++)
                    {
                        for (client = 0; client<BMEMPERF_MAX_NUM_CLIENT; client++)
                        {
                            g_savedClientDataSorted[memc][client].bw = 0;
                        }
                    }

                    /* update or add current data with saved data */
                    for (memc = 0; memc<BMEMPERF_NUM_MEMC; memc++)
                    {
                        for (client = 0; client<BMEMPERF_MAX_NUM_CLIENT; client++)
                        {
                            if (pResponse->response.overallStats.clientOverallStats[memc].clientData[client].client_id != BMEMPERF_CGI_INVALID)
                            {
                                updateClient( pResponse->response.overallStats.clientOverallStats[memc].clientData[client].client_id, memc,
                                    &pResponse->response.overallStats.clientOverallStats[memc].clientData[client] );
                            }
                        }

                        bmemperf_clear_arb_err( memc );
                    }

                    memcpy( &pResponse->response.overallStats.clientOverallStats, &g_savedClientDataSorted, sizeof( g_savedClientDataSorted ));
                }

                bmemperf_computeIrqData( pResponse->response.overallStats.cpuData.numActiveCpus, &pResponse->response.overallStats.irqData );

                bmemperf_getCpuUtilization( &pResponse->response.overallStats.cpuData );

                PRINTF( "%s: sending cmd (%u); %u bytes\n", __FUNCTION__, pResponse->cmd, sizeof( *pResponse ));
                if (send( psd, pResponse, sizeof( *pResponse ), 0 ) < 0)
                {
                    CloseAndExit( psd, "sending response cmd" );
                }
                break;
            }
            case BMEMPERF_CMD_GET_CLIENT_STATS:
            {
                pResponse->cmd = pRequest->cmd;

#if defined ( BMEMPERF_CGI_DEBUG )
                {
                    unsigned int memc = 0, client = 0;
                    int          temp;
                    for (memc = 0; memc<NEXUS_NUM_MEMC; memc++)
                    {
                        printf( "%s: step1 memc %u: ", __FUNCTION__, memc );
                        for (client = 0; client<BMEMPERF_MAX_SUPPORTED_CLIENTS; client++)
                        {
                            temp = g_client_list[memc][client];
                            printf( "%3u:%-4d ", client, temp );
                        }
                        printf( "\n" );
                    }
                }
#endif /* ifdef BMEMPERF_CGI_DEBUG */

                setClientList( g_client_list );

#if defined ( BMEMPERF_CGI_DEBUG )
                {
                    unsigned int memc = 0, client = 0;
                    for (memc = 0; memc<NEXUS_NUM_MEMC; memc++)
                    {
                        printf( "%s: step2 memc %u: ", __FUNCTION__, memc );
                        for (client = 0; client<BMEMPERF_MAX_SUPPORTED_CLIENTS; client++)
                        {
                            printf( "%3u:%-4u ", pResponse->response.clientDetailStats.clientStats[memc].perClientStats[client].clientId,
                                pResponse->response.clientDetailStats.clientStats[memc].perClientStats[client].clientDataBW );
                        }
                        printf( "\n" );
                    }
                }
#endif /* ifdef BMEMPERF_CGI_DEBUG */

                bmemperf_getClientStats( &pResponse->response.clientDetailStats );

#if defined ( BMEMPERF_CGI_DEBUG )
                {
                    unsigned int memc = 0, client = 0;
                    for (memc = 0; memc<NEXUS_NUM_MEMC; memc++)
                    {
                        printf( "%s: step3 memc %u: ", __FUNCTION__, memc );
                        for (client = 0; client<BMEMPERF_MAX_SUPPORTED_CLIENTS; client++)
                        {
                            printf( "%3u:%-4u ", pResponse->response.clientDetailStats.clientStats[memc].perClientStats[client].clientId,
                                pResponse->response.clientDetailStats.clientStats[memc].perClientStats[client].clientDataBW );
                        }
                        printf( "\n" );
                    }
                }
#endif /* ifdef BMEMPERF_CGI_DEBUG */

                PRINTF( "%s: sending cmd (%u); %u bytes\n", __FUNCTION__, pResponse->cmd, sizeof( *pResponse ));
                if (send( psd, pResponse, sizeof( *pResponse ), 0 ) < 0)
                {
                    CloseAndExit( psd, "sending response cmd" );
                }
                break;
            }
            case BMEMPERF_CMD_SET_CLIENT_BOVAL_RRFLAG:
            {
                pResponse->cmd = pRequest->cmd;
#ifdef BMEMPERF_CGI_DEBUG
                printf( "%s: client_id = %u, memc_index= %u, block_out = %u, rr = %u \n", __FUNCTION__,
                    pRequest->request.client_rts_setting.client_id, pRequest->request.client_rts_setting.memc_index, pRequest->request.client_rts_setting.block_out,
                    pRequest->request.client_rts_setting.rr );
#endif
                setRTSForClient( &( pRequest->request.client_rts_setting ));
                if (pRequest->request.client_rts_setting.block_out != BMEMPERF_CGI_INVALID)
                {
                    setClientErrCnt( pRequest->request.client_rts_setting.memc_index, pRequest->request.client_rts_setting.client_id, 0 );
                }

#ifdef BMEMPERF_CGI_DEBUG
                printf( "%s: setting BO_VAL = %d and RR_FLAG = %d for client = %u and memc = %u; err_cnt %u\n", __FUNCTION__,
                    pRequest->request.client_rts_setting.block_out,
                    pRequest->request.client_rts_setting.rr,
                    pRequest->request.client_rts_setting.client_id,
                    pRequest->request.client_rts_setting.memc_index,
                    g_savedClientDataSorted[pRequest->request.client_rts_setting.memc_index][pRequest->request.client_rts_setting.client_id].err_cnt );
#endif /* ifdef BMEMPERF_CGI_DEBUG */
                break;
            }

            case BMEMPERF_CMD_GET_CPU_IRQ_INFO:
            {
                pResponse->cmd = pRequest->cmd;
                bmemperf_getCpuUtilization( &pResponse->response.cpuIrqData.cpuData );

                PRINTF( "%s: detected BMEMPERF_CMD_GET_CPU_IRQ_INFO (%u); numCpus %u\n", __FUNCTION__, pResponse->cmd,
                    pResponse->response.cpuIrqData.cpuData.numActiveCpus );
                bmemperf_computeIrqData( pResponse->response.cpuIrqData.cpuData.numActiveCpus, &pResponse->response.cpuIrqData.irqData );

                if (( pRequest->cmdSecondary == BMEMPERF_CMD_START_PERF_DEEP ) && ( pRequest->cmdSecondaryOption > 0 ) && ( pRequest->cmdSecondaryOption < 61 ))
                {
                    bmemperf_start_perf_record( pRequest->cmdSecondaryOption );
                }
                else if (( pRequest->cmdSecondary == BMEMPERF_CMD_START_PERF_CACHE ) && ( pRequest->cmdSecondaryOption > 0 ) && ( pRequest->cmdSecondaryOption < 61 ))
                {
                    bmemperf_start_perf_cache( pRequest->cmdSecondaryOption );
                }
                else if (( pRequest->cmdSecondary == BMEMPERF_CMD_START_SATA_USB ) || ( pRequest->cmdSecondary == BMEMPERF_CMD_STOP_SATA_USB ))
                {
                    bmemperf_sata_usb_start( pRequest->cmdSecondaryOption );

                    bmemperf_sata_usb_gather( pResponse );
                }
                else if (( pRequest->cmdSecondary == BMEMPERF_CMD_START_LINUX_TOP ) || ( pRequest->cmdSecondary == BMEMPERF_CMD_STOP_LINUX_TOP ))
                {
                    bmemperf_start_linux_top( pRequest->cmdSecondaryOption );
                }

                pResponse->response.overallStats.contextSwitches = g_ContextSwitchesDelta;

                PRINTF( "%s: sending cmd (%u); %u bytes\n", __FUNCTION__, pResponse->cmd, sizeof( *pResponse ));
                if (send( psd, pResponse, sizeof( *pResponse ), 0 ) < 0)
                {
                    CloseAndExit( psd, "sending response cmd" );
                }

                break;
            }

            case BMEMPERF_CMD_QUIT:
            {
                Quit = 1;
                break;
            }
            default:
            {
                printf( "Server: unknown request %d\n", pRequest->cmd );
                break;
            }
        } /* switch */
    }
    else
    {
        PRINTF( "%u TCP/Client: %s\n", ntohs( from.sin_port ), inet_ntoa( from.sin_addr ));
        PRINTF( "%u Disconnected..\n", ntohs( from.sin_port ));
    }

    close( psd );

    return( 0 );
} /* Bmemperf_ReadRequest */

/**
 *  Function: This function will configure the socket so that the address can be re-used without a long timeout.
 **/
static void reusePort(
    int s
    )
{
    int one = 1;

    if (setsockopt( s, SOL_SOCKET, SO_REUSEADDR, (char *)&one, sizeof( one )) == -1)
    {
        printf( "error in setsockopt,SO_REUSEPORT \n" );
        exit( -1 );
    }
}

/**
 *  Function: This function is the main function that controls the logic of the app.
 **/
int main(
    int   argc,
    char *argv[]
    )
{
    pthread_t dataGatheringThreadId = 0;
    void     *(*threadFunc)( void * );

    BSTD_UNUSED( argc );

    memset( &g_savedClientDataSorted, 0, sizeof( g_savedClientDataSorted ));
    memset( &g_savedIrqData, 0, sizeof( g_savedIrqData ));
    memset( &gSataUsbMbps, 0, sizeof( gSataUsbMbps ));

    Bmemperf_Server_InitMutex( &gSataUsbMutex );

    printf( "%s: bmemperf_response size %d\n", __FUNCTION__, sizeof( bmemperf_response ));
    threadFunc = dataFetchThread;
    if (pthread_create( &dataGatheringThreadId, NULL, threadFunc, (void *)NULL ))
    {
        printf( "%s: could not create thread for data gathering; %s\n", __FUNCTION__, strerror( errno ));
    }
    else
    {
        startServer();
        {
            unsigned int idx = 0;
            for (idx = 0; idx<5000; idx++) {
                PRINTF( "%s: sleep(1000)\n", argv[0] );
                sleep( 1000 );
            }
        }
    }

    PRINTF( "%s exiting.\n", argv[0] );

    return( 0 );
} /* main */

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
#ifndef __BMEMPERF_UTILS_H__
#define __BMEMPERF_UTILS_H__

#include <sys/socket.h>
#include "bmemperf.h"
#include "bmemperf_lib.h"

#define MAJOR_VERSION                  0
#define MINOR_VERSION                  10
/*
    0.10  Added contextSwitches to response
*/
#define PRINTF                         noprintf
#define FPRINTF                        nofprintf
#define BMEMPERF_MAX_SUPPORTED_CLIENTS 10
#define BACKGROUND_WHITE               "style='background-color:white;color:black;' "
#define BACKGROUND_YELLOW              "style='background-color:yellow;' "
#define BACKGROUND_RED                 "style='background-color:red;' "
#define BOXMODE_RTS_FILE               "/proc/device-tree/bolt/rts"
#define BOXMODE_SOURCES_NUM            3
#define PERF_REPORT_OUTPUT_FILE        "PerfReport.txt"
#define PERF_STAT_OUTPUT_FILE          "PerfStat.txt"
#define SATA_USB_OUTPUT_FILE           "satausb.txt"
#define LINUX_TOP_OUTPUT_FILE          "linuxtop.txt"
#define MAX_LINE_LENGTH                512
#define TEMP_FILE_FULL_PATH_LEN        64
#define BMEMPERF_SATA_USB_MAX          12 /* maximum number of devices like sda1, sda2, sda3, sda4, sdb1, sdc1 */

#ifdef B_ANDROID_BUILD
#define BIN_DIR "/system/bin"
#define SBIN_DIR "/sbin"
#define IFCONFIG_UTILITY "/system/bin/netcfg"
#else
#define BIN_DIR "/bin"
#define SBIN_DIR "/sbin"
#define IFCONFIG_UTILITY "/sbin/ifconfig"
#endif

typedef enum
{
    BOXMODE_ENV,
    BOXMODE_RTS,
    BOXMODE_BROWSER
} bmemperf_boxmode_sources;
typedef struct
{
    int boxmode;
    bmemperf_boxmode_sources source;
} bmemperf_boxmode_source;

/* command */
typedef enum
{
    BMEMPERF_CMD_GET_OVERALL_STATS = 101, /* over all stats for all the memcs and memory bw consumers, sorted list */
    BMEMPERF_CMD_GET_CLIENT_STATS,        /* detailed stats for individual clients */
    BMEMPERF_CMD_SET_CLIENT_BOVAL_RRFLAG,
    BMEMPERF_CMD_RESET_ARB_ERRORS,
    BMEMPERF_CMD_START_PERF_DEEP,
    BMEMPERF_CMD_START_PERF_CACHE,
    BMEMPERF_CMD_START_SATA_USB,
    BMEMPERF_CMD_STOP_SATA_USB,
    BMEMPERF_CMD_START_LINUX_TOP,
    BMEMPERF_CMD_STOP_LINUX_TOP,
    BMEMPERF_CMD_QUIT,
    BMEMPERF_CMD_GET_CPU_IRQ_INFO,
    BMEMPERF_CMD_MAX
} bmemperf_cmd;

typedef enum
{
    BMEMPERF_COLUMN_ID = 1,
    BMEMPERF_COLUMN_NAME,
    BMEMPERF_COLUMN_BW,
    BMEMPERF_COLUMN_MAX
} bmemperf_columnTypes;

typedef struct
{
    unsigned int clientIds[NEXUS_NUM_MEMC][BMEMPERF_MAX_SUPPORTED_CLIENTS];   /* ids of the x clients for which the user can request details */
} bmemperf_clientInfo;

typedef struct  bmemperf_cmd_overall_stats_data
{
    unsigned int dummy;
} bmemperf_cmd_overall_stats_data;

typedef struct bmemperf_cmd_set_client_rts
{
    unsigned int client_id;
    unsigned int memc_index;
    unsigned int rr;        /** If not set then this should be BMEMPERF_CGI_INVALID **/
    unsigned int block_out; /** If not set then this should be BMEMPERF_CGI_INVALID **/
} bmemperf_cmd_set_client_rts;

typedef struct bmemperf_cmd_get_client_stats_data
{
    unsigned int         client_list[BMEMPERF_NUM_MEMC][BMEMPERF_MAX_SUPPORTED_CLIENTS]; /* BMEMPERF_CGI_INVALID indicates no client id is desired */
    bmemperf_columnTypes sortColumn[BMEMPERF_NUM_MEMC];
} bmemperf_cmd_get_client_stats_data;

typedef struct bmemperf_request
{
    bmemperf_cmd             cmd;
    bmemperf_cmd             cmdSecondary;
    unsigned long int        cmdSecondaryOption;
    int                      boxmode;
    bmemperf_boxmode_sources source;
    union {
        bmemperf_cmd_overall_stats_data    overall_stats_data;
        bmemperf_cmd_get_client_stats_data client_stats_data;
        bmemperf_cmd_set_client_rts        client_rts_setting;
    } request;
} bmemperf_request;

/* response */
typedef struct bmemperf_client_data
{
    unsigned int  client_id;
    unsigned int  bw;
    unsigned int  rr;
    unsigned int  block_out;
    bool          is_detailed; /* true if this client id has details being accumulated for it */
    unsigned char err_cnt;
} bmemperf_client_data;

typedef struct bmemperf_system_stats
{
    /** Normal mode overall service data **/
    unsigned int dataBW;        /** In Mbps **/
    unsigned int transactionBW; /** In Mbps **/
    unsigned int idleBW;        /** In Mbps **/
    float        dataUtil;
    unsigned int ddrFreqMhz;
    unsigned int scbFreqMhz;
} bmemperf_system_stats;

typedef struct
{
    float readMbps;
    float writeMbps;
    char  deviceName[32];
} bmemperf_sata_usb_data;

typedef struct
{
    bmemperf_cpu_percent   cpuData;
    bmemperf_irq_data      irqData;
    bmemperf_sata_usb_data sataUsbData[BMEMPERF_SATA_USB_MAX]; /* expect no more than 6 SATA and USB devices */
} bmemperf_cpu_irq;

typedef struct
{
    bool isActive[BMEMPERF_MAX_NUM_CPUS];
} bmemperf_cpu_status;

typedef struct bmemperf_overall_stats
{
    bmemperf_system_stats systemStats[BMEMPERF_NUM_MEMC];
    struct {
        bmemperf_client_data clientData[BMEMPERF_MAX_NUM_CLIENT];
    } clientOverallStats[BMEMPERF_NUM_MEMC];
    bmemperf_columnTypes sortColumn[BMEMPERF_NUM_MEMC];
    bmemperf_cpu_percent cpuData;
    bmemperf_irq_data    irqData;
    unsigned long int    contextSwitches;
} bmemperf_overall_stats;

typedef struct bmemperf_per_client_stats
{
    unsigned int clientId;
    unsigned int clientDataBW;
    unsigned int clientRdTransInPerc;
    unsigned int clientWrTransInPerc;
    unsigned int avgClientDataSizeInBits;
    float        clientDataUtil;
    unsigned int clientTransBW; /** In Mbps **/
} bmemperf_per_client_stats;

typedef struct bmemperf_client_stats
{
    struct {
        bmemperf_per_client_stats perClientStats[BMEMPERF_MAX_SUPPORTED_CLIENTS];
    } clientStats[BMEMPERF_NUM_MEMC];
} bmemperf_client_stats;

typedef struct bmemperf_response
{
    char                     padding[100]; /* used to make size of struct an even multiple of 256 */
    bmemperf_cmd             cmd;
    int                      boxmode;
    bmemperf_boxmode_sources source;
    unsigned long int        timestamp;
    union {
        bmemperf_overall_stats overallStats;
        bmemperf_client_stats  clientDetailStats;
        bmemperf_cpu_irq       cpuIrqData; /* bsysperf uses this structure to get cpu and irq information */
    } response;
} bmemperf_response;

typedef struct
{
    unsigned char majorVersion; /* changes if structure size changes */
    unsigned char minorVersion;
    unsigned int  sizeOfResponse;
    char          platform[8];
    char          platVersion[4];
} bmemperf_version_info;

const char *nofprintf(
    FILE       *stdsomething,
    const char *format,
    ...
    );
char *getClientName( int client_index );

pid_t daemonize( void );

char *decodeFilename( const char *filename );
int   sendFileToBrowser(
    const char *filename
    );
int readFileFromBrowser(
    const char       *contentType,
    const char       *contentLength,
    char             *sFilename,
    unsigned long int lFilenameLen
    );
int sort_on_id(
    const void *a,
    const void *b
    );
int sort_on_id_rev(
    const void *a,
    const void *b
    );
int sort_on_bw(
    const void *a,
    const void *b
    );
int sort_on_bw_rev(
    const void *a,
    const void *b
    );
int changeFileExtension(
    char       *destFilename,
    int         sizeofDestFilename,
    const char *srcFilename,
    const char *fromext,
    const char *toext
    );
int clientListCheckboxes(
    unsigned int top10Number
    );
int get_interrupt_counts(
    bmemperf_irq_data *irqData
    );
int getCpuOnline(
    bmemperf_cpu_status *pCpuStatus
    );
int getUptime(
    float *uptime
    );
int setUptime(
    void
    );
int get_proc_stat_info(
    bmemperf_proc_stat_info *pProcStatInfo
    );
char *GetFileContents(
    const char *filename
    );
int bmemperf_boxmode_init(
    long int boxmode
    );
int getBoxModeHtml(
    char *buf,
    int   len,
    int   boxmodePlatform
    );
int overall_stats_html(
    bmemperf_response *pResponse
    );
int top10_html(
    bmemperf_response *pResponse,
    unsigned int       top10Number
    );
int get_boxmode(
    bmemperf_boxmode_source *boxmode_info
    );
char *GetTempDirectoryStr(
    void
    );
void PrependTempDirectory(
    char       *filenamePath,
    int         filenamePathLen,
    const char *filename
    );
bool hasNumeric(
    const char *mystring
    );
#endif /*__BMEMPERF_UTILS_H__ */

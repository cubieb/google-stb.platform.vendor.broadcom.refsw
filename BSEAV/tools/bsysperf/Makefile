############################################################
#	  (c)2003-2014 Broadcom Corporation
#
#  This program is the proprietary software of Broadcom Corporation and/or its licensors,
#  and may only be used, duplicated, modified or distributed pursuant to the terms and
#  conditions of a separate, written license agreement executed between you and Broadcom
#  (an "Authorized License").  Except as set forth in an Authorized License, Broadcom grants
#  no license (express or implied), right to use, or waiver of any kind with respect to the
#  Software, and Broadcom expressly reserves all rights in and to the Software and all
#  intellectual property rights therein.  IF YOU HAVE NO AUTHORIZED LICENSE, THEN YOU
#  HAVE NO RIGHT TO USE THIS SOFTWARE IN ANY WAY, AND SHOULD IMMEDIATELY
#  NOTIFY BROADCOM AND DISCONTINUE ALL USE OF THE SOFTWARE.
#
#  Except as expressly set forth in the Authorized License,
#
#  1.	  This program, including its structure, sequence and organization, constitutes the valuable trade
#  secrets of Broadcom, and you shall use all reasonable efforts to protect the confidentiality thereof,
#  and to use this information only in connection with your use of Broadcom integrated circuit products.
#
#  2.	  TO THE MAXIMUM EXTENT PERMITTED BY LAW, THE SOFTWARE IS PROVIDED "AS IS"
#  AND WITH ALL FAULTS AND BROADCOM MAKES NO PROMISES, REPRESENTATIONS OR
#  WARRANTIES, EITHER EXPRESS, IMPLIED, STATUTORY, OR OTHERWISE, WITH RESPECT TO
#  THE SOFTWARE.  BROADCOM SPECIFICALLY DISCLAIMS ANY AND ALL IMPLIED WARRANTIES
#  OF TITLE, MERCHANTABILITY, NONINFRINGEMENT, FITNESS FOR A PARTICULAR PURPOSE,
#  LACK OF VIRUSES, ACCURACY OR COMPLETENESS, QUIET ENJOYMENT, QUIET POSSESSION
#  OR CORRESPONDENCE TO DESCRIPTION. YOU ASSUME THE ENTIRE RISK ARISING OUT OF
#  USE OR PERFORMANCE OF THE SOFTWARE.
#
#  3.	  TO THE MAXIMUM EXTENT PERMITTED BY LAW, IN NO EVENT SHALL BROADCOM OR ITS
#  LICENSORS BE LIABLE FOR (i) CONSEQUENTIAL, INCIDENTAL, SPECIAL, INDIRECT, OR
#  EXEMPLARY DAMAGES WHATSOEVER ARISING OUT OF OR IN ANY WAY RELATING TO YOUR
#  USE OF OR INABILITY TO USE THE SOFTWARE EVEN IF BROADCOM HAS BEEN ADVISED OF
#  THE POSSIBILITY OF SUCH DAMAGES; OR (ii) ANY AMOUNT IN EXCESS OF THE AMOUNT
#  ACTUALLY PAID FOR THE SOFTWARE ITSELF OR U.S. $1, WHICHEVER IS GREATER. THESE
#  LIMITATIONS SHALL APPLY NOTWITHSTANDING ANY FAILURE OF ESSENTIAL PURPOSE OF
#  ANY LIMITED REMEDY.
#
# $brcm_Workfile: $
# $brcm_Revision: $
# $brcm_Date: $
#
# Module Description:
#
# Revision History:
#
# Created: 08/28/2007 by Jon Garrett
#
# $brcm_Log: $
#
############################################################
# Nexus examples
B_THIS_DIR:=BSEAV/tools/bsysperf
PHONY := all boa clean clean_apps install nexus_headers clean_boa
.PHONY: ${PHONY}
.NOTPARALLEL: apps boa

ifeq ($(LINUXDIR),)
LINUXDIR = $(LINUX)
endif

THEAPPS = \
	bsysperf.cgi \
    bsysperf_server

NEXUS_PLATFORM ?= $(PLATFORM)
ifndef NEXUS_PLATFORM
$(error NEXUS_PLATFORM is not defined)
endif

ifeq ($(B_REFSW_REAL_MAKE),)
NEXUS_TOP ?= $(subst /${B_THIS_DIR},,$(CURDIR))/nexus

B_REFSW_OBJ_DIR ?= obj.${NEXUS_PLATFORM}
B_REFSW_OBJ_ROOT ?= ${NEXUS_TOP}/../${B_REFSW_OBJ_DIR}
BINDIR := ${B_REFSW_OBJ_ROOT}/nexus/bsysperf

${PHONY} ${THEAPPS}: ${BINDIR}/exists
	@${MAKE} -C ${BINDIR} B_REFSW_REAL_NEXUS_TOP=${NEXUS_TOP} B_REFSW_REAL_MAKE=1 -f ${CURDIR}/Makefile ${MAKECMDGOALS}

${BINDIR}/exists:
	@mkdir -p $@

else # B_REFSW_REAL_MAKE
NEXUS_TOP?=${B_REFSW_REAL_NEXUS_TOP}

include $(NEXUS_TOP)/examples/Makefile_prologue.inc

APPS = $(THEAPPS)
APPS ?= $(APP)

vpath %.c ${NEXUS_TOP}/../BSEAV/tools/bsysperf

all: apps

apps: $(APPS)

LDFLAGS += -lpthread
MAIN_OBJS = ${NEXUS_TOP}/../${B_THIS_DIR}/bsysperf.c ${NEXUS_TOP}/../${B_THIS_DIR}/bheaps.c
SERVER_OBJS = ${NEXUS_TOP}/../${B_THIS_DIR}/bsysperf_server.c
EXTRA_OBJS += ${NEXUS_TOP}/../BSEAV/tools/bmemperf/common/bmemperf_lib.c ### ${NEXUS_TOP}/../BSEAV/tools/bmemperf/common/bmemperf_utils.c
CLKGEN_PATH = ${NEXUS_TOP}/../magnum/basemodules/chp/src/common

# This cleans nexus and local apps
clean: clean_apps clean_boa

boa:
	$(MAKE) -C $(NEXUS_TOP)/../BSEAV/lib/boa
clean_boa:
	$(MAKE) -C $(NEXUS_TOP)/../BSEAV/lib/boa clean

clean_apps:
	@-$(RM) $(APPS) *.d *.o *.out
	@-$(RM) ${NEXUS_BIN_DIR}/bsysperf.html
	@-$(RM) ${NEXUS_BIN_DIR}/bsysperf.js
	@-$(RM) ${NEXUS_BIN_DIR}/bsysperf.png
	@-$(RM) ${NEXUS_BIN_DIR}/bsysperf.cgi
	@-$(RM) ${NEXUS_BIN_DIR}/bsysperf.sh
	@-$(RM) ${NEXUS_BIN_DIR}/bsysperf_server

# This is the minimum needed to compile and link with Nexus
CFLAGS += $(NEXUS_CFLAGS) $(addprefix -I,$(NEXUS_APP_INCLUDE_PATHS)) $(addprefix -D,$(NEXUS_APP_DEFINES))
CFLAGS += -I${NEXUS_TOP}/../BSEAV/tools/bmemperf/include
CFLAGS += -I${LINUXDIR}/include
CFLAGS += -I${NEXUS_BIN_DIR}
CFLAGS += -Wimplicit-function-declaration -Wall -lm
ifeq ($(ANDROID_BUILD),y)
CFLAGS += -D_LARGEFILE_SOURCE -D_FILE_OFFSET_BITS=64 -DB_ANDROID_BUILD
endif

# Always build with debug
CFLAGS += -g

# Implicit rule for building local apps
bsysperf.cgi: boa $(MAIN_OBJS) $(EXTRA_OBJS)
	@echo [Building ... $@]
	$(Q_)$(CC) -o ${NEXUS_BIN_DIR}/$@ $(MAIN_OBJS) $(EXTRA_OBJS) $(CFLAGS) ${CDEP_FLAG} $(LDFLAGS)
	$(Q_)$(CP) -f ${NEXUS_TOP}/../${B_THIS_DIR}/bsysperf.html  ${NEXUS_BIN_DIR}
	$(Q_)$(CP) -f ${NEXUS_TOP}/../${B_THIS_DIR}/bsysperf.js    ${NEXUS_BIN_DIR}
	$(Q_)$(CP) -f ${NEXUS_TOP}/../${B_THIS_DIR}/bsysperf.png   ${NEXUS_BIN_DIR}
	$(Q_)rm -f ${NEXUS_BIN_DIR}/bsysperf.d

bsysperf_server: $(SERVER_OBJS)
	@echo [Building ... $@]
	$(Q_)$(CC) -c $(SERVER_OBJS) $(CFLAGS) ${CDEP_FLAG}
	$(Q_)$(CC) -o ${NEXUS_BIN_DIR}/$@ $(SERVER_OBJS) $(EXTRA_OBJS) $(CFLAGS) ${CDEP_FLAG} $(LDFLAGS)
	$(Q_)$(CP) -f ${NEXUS_TOP}/../${B_THIS_DIR}/bsysperf.sh   ${NEXUS_BIN_DIR}

-include *.d

install: all
	@echo [Installing to ... ${NEXUS_BIN_DIR}]
	$(Q_)$(CP) -f ${APPS} ${NEXUS_BIN_DIR}

endif # B_REFSW_REAL_MAKE

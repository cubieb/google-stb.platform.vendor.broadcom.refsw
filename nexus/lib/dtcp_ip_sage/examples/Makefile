############################################################
#     (c)2008-2015 Broadcom Corporation
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
#  1.     This program, including its structure, sequence and organization, constitutes the valuable trade
#  secrets of Broadcom, and you shall use all reasonable efforts to protect the confidentiality thereof,
#  and to use this information only in connection with your use of Broadcom integrated circuit products.
#
#  2.     TO THE MAXIMUM EXTENT PERMITTED BY LAW, THE SOFTWARE IS PROVIDED "AS IS"
#  AND WITH ALL FAULTS AND BROADCOM MAKES NO PROMISES, REPRESENTATIONS OR
#  WARRANTIES, EITHER EXPRESS, IMPLIED, STATUTORY, OR OTHERWISE, WITH RESPECT TO
#  THE SOFTWARE.  BROADCOM SPECIFICALLY DISCLAIMS ANY AND ALL IMPLIED WARRANTIES
#  OF TITLE, MERCHANTABILITY, NONINFRINGEMENT, FITNESS FOR A PARTICULAR PURPOSE,
#  LACK OF VIRUSES, ACCURACY OR COMPLETENESS, QUIET ENJOYMENT, QUIET POSSESSION
#  OR CORRESPONDENCE TO DESCRIPTION. YOU ASSUME THE ENTIRE RISK ARISING OUT OF
#  USE OR PERFORMANCE OF THE SOFTWARE.
#
#  3.     TO THE MAXIMUM EXTENT PERMITTED BY LAW, IN NO EVENT SHALL BROADCOM OR ITS
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
#
# Module Description: Makefile for DTCP IP example apps
#
# Revision History:
#
# $brcm_Log:
#
############################################################

ifdef COMSPEC
# Any DOS environment
NEXUS_TOP := $(shell cd ../../../../nexus && cd)
else
NEXUS_TOP := $(shell cd ../../../../nexus ; pwd)
endif

# If NEXUS_PLATFORM not defined, populate it from PLATFORM
NEXUS_PLATFORM ?= $(PLATFORM)
ifndef NEXUS_PLATFORM
    $(error NEXUS_PLATFORM is not defined)
endif

SSL_CERT_FILE := host.cert

# include cross-compiler definitions
include $(NEXUS_TOP)/platforms/$(NEXUS_PLATFORM)/build/platform_app.inc

BSEAV := $(NEXUS_TOP)/../BSEAV

ifeq ($(B_REFSW_ARCH),)
B_REFSW_ARCH=mipsel-linux
export B_REFSW_ARCH
endif

B_REFSW_DEBUG ?= y
ifeq ($(B_REFSW_DEBUG),y)
DEBUG_SUFFIX=debug
else
DEBUG_SUFFIX=release
endif

ifeq ($(DTCP_IP_SAGE_SUPPORT),y)
ifeq ($(SSL_SUPPORT),n)
$(error SSL_SUPPORT is disabled, cannot enable DTCP_IP_SAGE_SUPPORT)
endif #SSL_SUPPORT
export SSL_SUPPORT=y

ifneq ($(DTCP_IP_HARDWARE_DECRYPTION),n)
export DTCP_IP_HARDWARE_DECRYPTION=y
endif #DTCP_IP_HARDWARE_DECRYPTION

ifneq ($(DTCP_IP_HARDWARE_ENCRYPTION),n)
export DTCP_IP_HARDWARE_ENCRYPTION=y
endif #DTCP_IP_HARDWARE_ENCRYPTION
endif #DTCP_IP_SAGE_SUPPORT



# Get OpenSSl make defines
#include $(BSEAV)/lib/openssl/openssl.inc
#include applib definitions
#include $(NEXUS_TOP)/lib/playback_ip/b_playback_ip_lib.inc
include $(NEXUS_TOP)/lib/dtcp_ip_sage/dtcp_ip_lib.inc
DTCP_IP_APPLIB_TEST_LDFLAGS += -lpthread $(B_DTCP_IP_LIB_LDFLAGS)
CFLAGS += $(B_DTCP_IP_LIB_CFLAGS)

DTCP_IP_APPLIB_TEST_SRC_PATH = .
DTCP_IP_APPLIB_TEST_INCLUDE_PATH = .
DTCP_IP_APPLIB_TEST_ODIR = $(NEXUS_PLATFORM).$(B_REFSW_ARCH)

DTCP_IP_APPLIB_TEST_INCLUDE_PATH += \
	$(NEXUS_APP_INCLUDE_PATHS) \
	$(NEXUS_TOP)/lib/dtcp_ip_sage/include \

DTCP_IP_APPLIB_TEST_DEFINES := $(NEXUS_APP_DEFINES)
DTCP_IP_APPLIB_TEST_DEFINES += LINUX BCM_DEBUG
DTCP_IP_APPLIB_TEST_DEFINES += MAJOR_VERSION=0 MINOR_VERSION=0 SUB_VERSION=1

DTCP_IP_CLIENT_APP = dtcp_startup
DTCP_IP_CLIENT_SRCS = \
	dtcp_startup.c

DTCP_IP_HTTP_CLIENT_APP = http_client
DTCP_IP_HTTP_CLIENT_SRCS = \
	http_client.c

DTCP_IP_HTTP_SERVER_APP = http_server
DTCP_IP_HTTP_SERVER_SRCS = \
	http_server.c

vpath %.cpp $(DTCP_IP_APPLIB_TEST_SRC_PATH)
vpath %.c $(DTCP_IP_APPLIB_TEST_SRC_PATH)

.PHONY: api clean install all

all: $(DTCP_IP_CLIENT_APP) $(DTCP_IP_HTTP_CLIENT_APP) $(DTCP_IP_HTTP_SERVER_APP)

# For linux builds, link to the correct libraries
ifeq ($(B_REFSW_OS),linuxkernel)
LDFLAGS := ${NEXUS_LDFLAGS}
else
ifneq ($(findstring linux,$(B_REFSW_OS)),)
LDFLAGS := -lnexus -L${NEXUS_BIN_DIR} -lm  $(EXTRA_DRM_OBJS) -lb_os
ifeq ($(NXCLIENT_SUPPORT),y)
Library: nxclient
include $(NEXUS_TOP)/nxclient/include/nxclient.inc
CFLAGS += ${NXCLIENT_CFLAGS}
LDFLAGS += ${NXCLIENT_LDFLAGS}
endif
endif
endif

api:

ifneq ($(REFSW_BUILD),y)
	$(Q_)$(MAKE) -C $(NEXUS_TOP)/build
endif #REFSW_BUILD

ifeq ($(DTCP_IP_SAGE_SUPPORT),y)
	$(Q_)$(MAKE) -C $(NEXUS_TOP)/lib/dtcp_ip_sage install
endif #DTCP_IP_SAGE_SUPPORT

# This cleans nexus and local apps
clean:
ifneq ($(REFSW_BUILD),y)
	$(Q_)$(MAKE) -C $(NEXUS_TOP)/build clean
endif
	$(Q_)$(RM) $(BSEAV)/bin/$(DTCP_IP_CLIENT_APP) $(BSEAV)/bin/$(DTCP_IP_HTTP_CLIENT_APP) $(BSEAV)/bin/$(DTCP_IP_HTTP_SERVER_APP) $(DTCP_IP_APPLIB_TEST_ODIR)/*.d $(DTCP_IP_APPLIB_TEST_ODIR)/*.o $(DTCP_IP_APPLIB_TEST_ODIR)/*.out;
	$(Q_)$(RM) $(DTCP_IP_APPLIB_TEST_ODIR)/$(DTCP_IP_CLIENT_APP) $(DTCP_IP_APPLIB_TEST_ODIR)/$(DTCP_IP_HTTP_CLIENT_APP) $(DTCP_IP_APPLIB_TEST_ODIR)/$(DTCP_IP_HTTP_SERVER_APP)
ifeq ($(DTCP_IP_SAGE_SUPPORT),y)
	$(Q_)$(MAKE) -C $(NEXUS_TOP)/lib/dtcp_ip_sage clean
endif #DTCP_IP_SAGE_SUPPORT

# This is the minimum needed to compile and link with Nexus
CFLAGS += $(NEXUS_CFLAGS) $(addprefix -I,$(DTCP_IP_APPLIB_TEST_INCLUDE_PATH)) $(addprefix -D,$(DTCP_IP_APPLIB_TEST_DEFINES))

# Always build with debug
CFLAGS += -MD -g

C_ONLY_FLAGS := -std=c99 -Wstrict-prototypes
CPPFLAGS := -fno-rtti -fno-exceptions

#ifeq ($(SSL_SUPPORT),y)
#.PHONY:  openssl_lib
#openssl_lib:
##	@echo [Build..... OpenSSL]
#	$(Q_)$(MAKE) -C $(B_OPENSSL_BUILD_DIR)
#endif #SSL_SUPPORT

#
# Implicit rule for building local app

$(DTCP_IP_CLIENT_APP): %: %.c $(DTCP_IP_APPLIB_TEST_ODIR) $(DTCP_IP_CLIENT_SRCS) api
	@echo [Compile... $<]
	$(Q_)$(CC) -o $(DTCP_IP_APPLIB_TEST_ODIR)/$@ $(DTCP_IP_CLIENT_SRCS) $(DTCP_IP_APPLIB_TEST_LDFLAGS) $(CFLAGS) $(C_ONLY_FLAGS) $(PLAYBACK_IP_CFLAGS) $(LDFLAGS)
	$(Q_)cp -f $(DTCP_IP_APPLIB_TEST_ODIR)/$(DTCP_IP_CLIENT_APP) $(NEXUS_BIN_DIR)
	@if [ -d $(BSEAV)/bin ]; then \
		cp -f $(DTCP_IP_APPLIB_TEST_ODIR)/$(DTCP_IP_CLIENT_APP) $(BSEAV)/bin/ ; \
	fi

$(DTCP_IP_HTTP_CLIENT_APP): %: %.c $(DTCP_IP_APPLIB_TEST_ODIR) $(DTCP_IP_HTTP_CLIENT_SRCS) api
	@echo [Compile... $<]
	$(Q_)$(CC) -o $(DTCP_IP_APPLIB_TEST_ODIR)/$@ $(DTCP_IP_HTTP_CLIENT_SRCS) $(DTCP_IP_APPLIB_TEST_LDFLAGS) $(CFLAGS) $(C_ONLY_FLAGS) $(PLAYBACK_IP_CFLAGS) $(LDFLAGS)
	$(Q_)cp -f $(DTCP_IP_APPLIB_TEST_ODIR)/$(DTCP_IP_HTTP_CLIENT_APP) $(NEXUS_BIN_DIR)
	@if [ -d $(BSEAV)/bin ]; then \
		cp -f $(DTCP_IP_APPLIB_TEST_ODIR)/$(DTCP_IP_HTTP_CLIENT_APP) $(BSEAV)/bin/ ; \
	fi

$(DTCP_IP_HTTP_SERVER_APP): %: %.c $(DTCP_IP_APPLIB_TEST_ODIR) $(DTCP_IP_HTTP_SERVER_SRCS) api
	@echo [Compile... $<]
	$(Q_)$(CC) -o $(DTCP_IP_APPLIB_TEST_ODIR)/$@ $(DTCP_IP_HTTP_SERVER_SRCS) $(DTCP_IP_APPLIB_TEST_LDFLAGS) $(CFLAGS) $(C_ONLY_FLAGS) $(PLAYBACK_IP_CFLAGS) $(LDFLAGS)
	$(Q_)cp -f $(DTCP_IP_APPLIB_TEST_ODIR)/$(DTCP_IP_HTTP_SERVER_APP) $(NEXUS_BIN_DIR)
	@if [ -d $(BSEAV)/bin ]; then \
		cp -f $(DTCP_IP_APPLIB_TEST_ODIR)/$(DTCP_IP_HTTP_SERVER_APP) $(BSEAV)/bin/ ; \
	fi

$(DTCP_IP_APPLIB_TEST_ODIR) :
	-@if [ ! -d $(DTCP_IP_APPLIB_TEST_ODIR) ]; then mkdir $(DTCP_IP_APPLIB_TEST_ODIR); fi


install: all

ifeq ($(DTCP_IP_SAGE_SUPPORT),y)
	@cp -f $(BSEAV)/lib/security/common_drm/lib/$(CMNDRM_DIR)/libcmndrm.so $(NEXUS_BIN_DIR)
	@cp -f $(BSEAV)/lib/security/common_drm/lib/$(CMNDRM_DIR)/libcmndrm_tl.so $(NEXUS_BIN_DIR)
#	@cp -f $(BSEAV)/lib/drmrootfs/lib/linuxuser/libdrmrootfs.so $(NEXUS_BIN_DIR)
endif #DTCP_IP_SAGE_SUPPORT

ifeq ($(SSL_SUPPORT),y)
ifneq ($(B_REFSW_OPENSSL_IS_EXTERNAL),y)
	@cp -f -P $(B_OPENSSL_LIB_INSTALL_DIR)/libcrypto.so* $(NEXUS_BIN_DIR)
	@cp -f -P $(B_OPENSSL_LIB_INSTALL_DIR)/libssl.so* $(NEXUS_BIN_DIR)
	@cp -f $(NEXUS_TOP)/lib/playback_ip/apps/$(SSL_CERT_FILE) $(NEXUS_BIN_DIR)
	@if [ -d $(BSEAV)/bin ]; then \
		cp -f $(NEXUS_TOP)/lib/playback_ip/apps/$(SSL_CERT_FILE) $(BSEAV)/bin ;\
	fi
endif   #  ifeq ($(B_REFSW_OPENSSL_IS_EXTERNAL),y)
endif

	@if [ -d $(BSEAV)/bin ]; then \
	cp -f $(NEXUS_BIN_DIR)/*.so* $(BSEAV)/bin; \
	cp -f $(NEXUS_BIN_DIR)/*.a $(BSEAV)/bin; \
	cp -f $(NEXUS_BIN_DIR)/ip_* $(BSEAV)/bin; \
	fi

ifneq ($(INSTALL_DIR),$(NEXUS_BIN_DIR))
ifneq ($(INSTALL_DIR),)
	@if [ -d $(INSTALL_DIR) ]; then \
	cp -f $(NEXUS_BIN_DIR)/*.so* $(INSTALL_DIR); \
	cp -f $(NEXUS_BIN_DIR)/*.a  $(INSTALL_DIR); \
	cp -f $(NEXUS_BIN_DIR)/ip_* $(INSTALL_DIR); \
	fi
endif
endif


-include $(DTCP_IP_APPLIB_TEST_ODIR)/*.d

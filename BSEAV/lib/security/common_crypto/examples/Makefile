############################################################
#    (c)2015 Broadcom Corporation
# 
# This program is the proprietary software of Broadcom Corporation and/or its licensors,
# and may only be used, duplicated, modified or distributed pursuant to the terms and
# conditions of a separate, written license agreement executed between you and Broadcom
# (an "Authorized License").  Except as set forth in an Authorized License, Broadcom grants
# no license (express or implied), right to use, or waiver of any kind with respect to the
# Software, and Broadcom expressly reserves all rights in and to the Software and all
# intellectual property rights therein.  IF YOU HAVE NO AUTHORIZED LICENSE, THEN YOU
# HAVE NO RIGHT TO USE THIS SOFTWARE IN ANY WAY, AND SHOULD IMMEDIATELY
# NOTIFY BROADCOM AND DISCONTINUE ALL USE OF THE SOFTWARE.  
#  
# Except as expressly set forth in the Authorized License,
#  
# 1.     This program, including its structure, sequence and organization, constitutes the valuable trade
# secrets of Broadcom, and you shall use all reasonable efforts to protect the confidentiality thereof,
# and to use this information only in connection with your use of Broadcom integrated circuit products.
#  
# 2.     TO THE MAXIMUM EXTENT PERMITTED BY LAW, THE SOFTWARE IS PROVIDED "AS IS" 
# AND WITH ALL FAULTS AND BROADCOM MAKES NO PROMISES, REPRESENTATIONS OR 
# WARRANTIES, EITHER EXPRESS, IMPLIED, STATUTORY, OR OTHERWISE, WITH RESPECT TO 
# THE SOFTWARE.  BROADCOM SPECIFICALLY DISCLAIMS ANY AND ALL IMPLIED WARRANTIES 
# OF TITLE, MERCHANTABILITY, NONINFRINGEMENT, FITNESS FOR A PARTICULAR PURPOSE, 
# LACK OF VIRUSES, ACCURACY OR COMPLETENESS, QUIET ENJOYMENT, QUIET POSSESSION 
# OR CORRESPONDENCE TO DESCRIPTION. YOU ASSUME THE ENTIRE RISK ARISING OUT OF 
# USE OR PERFORMANCE OF THE SOFTWARE.
# 
# 3.     TO THE MAXIMUM EXTENT PERMITTED BY LAW, IN NO EVENT SHALL BROADCOM OR ITS 
# LICENSORS BE LIABLE FOR (i) CONSEQUENTIAL, INCIDENTAL, SPECIAL, INDIRECT, OR 
# EXEMPLARY DAMAGES WHATSOEVER ARISING OUT OF OR IN ANY WAY RELATING TO YOUR 
# USE OF OR INABILITY TO USE THE SOFTWARE EVEN IF BROADCOM HAS BEEN ADVISED OF 
# THE POSSIBILITY OF SUCH DAMAGES; OR (ii) ANY AMOUNT IN EXCESS OF THE AMOUNT 
# ACTUALLY PAID FOR THE SOFTWARE ITSELF OR U.S. $1, WHICHEVER IS GREATER. THESE 
# LIMITATIONS SHALL APPLY NOTWITHSTANDING ANY FAILURE OF ESSENTIAL PURPOSE OF 
# ANY LIMITED REMEDY.
#
# $brcm_Workfile: $
# $brcm_Revision: $
# $brcm_Date: $
# 
# Module Description:
# 
# Revision History:
# 
############################################################

NEXUS_TOP := $(shell cd ../../../../../nexus; pwd)
BSEAV_TOP := $(shell cd ../../../../../BSEAV; pwd)

APPS = test_common_crypto 
SRCS = test_common_crypto.c
OBJS = ${SRCS:.c=.o}
TARGET_DIR := BSEAV/lib/security/common_crypto/examples

# include cross-compiler definitions
include $(NEXUS_TOP)/platforms/$(NEXUS_PLATFORM)/build/platform_app.inc

ifeq ($(APPS),)
$(error Must define APPS)
endif

# create 'target' dir in out of source dir
$(shell mkdir -p ${B_REFSW_OBJ_ROOT}/${TARGET_DIR})

.PHONY: all clean nexus_lib

all: $(APPS)

nexus_lib:
	@${MAKE} -C ${NEXUS_TOP}/build ${MAKECMDGOALS}

LDFLAGS := -L$(NEXUS_BIN_DIR)/ -lnexus$(NEXUS_LIB_SUFFIX) -L$(NEXUS_BIN_DIR)/ -lpthread -lm

ifeq (${DISABLE_EXTERNAL_KEY_IV_TESTS}, y)
$(warning Disabling external key and iv tests)
CFLAGS += -DDISABLE_EXTERNAL_KEY_IV_TESTS
endif

# Always build with debug
# common crypto include path
CFLAGS += -I${BSEAV_TOP}/lib/security/common_crypto/include

#$(error XXX $(CFLAGS))

# This cleans nexus and local apps
clean: nexus_lib
	-$(RM) ${B_REFSW_OBJ_ROOT}/${TARGET_DIR}/${APPS} ${B_REFSW_OBJ_ROOT}/${TARGET_DIR}/*.d ${B_REFSW_OBJ_ROOT}/${TARGET_DIR}/*.o ${B_REFSW_OBJ_ROOT}/${TARGET_DIR}/*.out;

# This is the minimum needed to compile and link with Nexus
CFLAGS += $(NEXUS_CFLAGS) $(addprefix -I,$(NEXUS_APP_INCLUDE_PATHS)) $(addprefix -D,$(NEXUS_APP_DEFINES))



# Implicit rule for building local apps
$(APPS): $(OBJS) nexus_lib
	@echo [Link... $@]
	@echo "NEXUS_TOP=$(NEXUS_TOP)"
	@echo "LDFLAGS=$(LDFLAGS)"
	${Q_} $(CC) -o ${B_REFSW_OBJ_ROOT}/${TARGET_DIR}/$@ ${B_REFSW_OBJ_ROOT}/${TARGET_DIR}/$@.o $(LDFLAGS)
	@echo [Copying executables...]
	cp ${B_REFSW_OBJ_ROOT}/${TARGET_DIR}/$@ $(NEXUS_BIN_DIR)/

.c.o:
	@echo [Compile... $<]
	${Q_}$(CC) -c -o ${B_REFSW_OBJ_ROOT}/${TARGET_DIR}/$@ $< $(CFLAGS)

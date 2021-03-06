############################################################
#     (c)2003-2014 Broadcom Corporation
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
############################################################

.PHONY: install_sage

# Supported SAGE secure mode:
#     Secure mode 1 (default): Disable URR and HDCP enforcement
#     Secure mode 5          : Enable URR (with URR toggling) and HDCP enforcement (standard mode). Available on Zeus 4.2 only.
#     Secure mode 6          : Enable URR and HDCP enforcement (standard mode). Available on Zeus 4.2 only.
#     Secure mode 9          : Enable URR and HDCP enforcement (strict mode). Available on Zeus 4.2 only.
SAGE_SECURE_MODE_DEFAULT := 1

ifeq ($(SAGE_SECURE_MODE),)
# Use default mode when it is not specified.
SAGE_SECURE_MODE := $(SAGE_SECURE_MODE_DEFAULT)
endif

SAGE_BL_BINARY_PATH := $(BSEAV)/lib/security/sage/bin/$(BCHP_CHIP)$(BCHP_VER)
SAGE_APP_BINARY_PATH := $(SAGE_BL_BINARY_PATH)/securemode$(SAGE_SECURE_MODE)

# Search for supported modes for the specified platform
ifneq (, $(wildcard $(SAGE_BL_BINARY_PATH)/securemode1))
SAGE_SECURE_MODE_LIST += 1
endif
ifneq (, $(wildcard $(SAGE_BL_BINARY_PATH)/securemode5))
SAGE_SECURE_MODE_LIST += 5
endif
ifneq (, $(wildcard $(SAGE_BL_BINARY_PATH)/securemode6))
SAGE_SECURE_MODE_LIST += 6
endif
ifneq (, $(wildcard $(SAGE_BL_BINARY_PATH)/securemode9))
SAGE_SECURE_MODE_LIST += 9
endif

ifneq ($(SAGE_BINARIES_AVAILABLE),y)
ifeq ($(findstring $(SAGE_SECURE_MODE),$(SAGE_SECURE_MODE_LIST)),)
    $(error SAGE secure mode $(SAGE_SECURE_MODE) is not supported. Update SAGE_SECURE_MODE with a supported mode: $(SAGE_SECURE_MODE_LIST))
endif
endif

install_sage:

ifeq ($(SAGE_BINARIES_AVAILABLE),y)
	@echo [Please install your own SAGE binaries under $(NEXUS_BIN_DIR)]
else

	@echo [Install... SAGE binaries]
ifeq (, $(wildcard $(SAGE_BL_BINARY_PATH)/sage_bl.bin))
	@echo "[$(SAGE_BL_BINARY_PATH)/sage_bl.bin does not exist. Please advise!]"
else
	${Q_}$(CP) -f $(SAGE_BL_BINARY_PATH)/sage_bl.bin ${NEXUS_BIN_DIR}
endif

ifeq (, $(wildcard $(SAGE_APP_BINARY_PATH)/sage_os_app.bin))
	@echo "[$(SAGE_APP_BINARY_PATH)/sage_os_app.bin does not exist. Please advise!]"
else
	${Q_}$(CP) -f $(SAGE_APP_BINARY_PATH)/sage_os_app.bin ${NEXUS_BIN_DIR}
endif

ifeq (, $(wildcard $(SAGE_BL_BINARY_PATH)/sage_bl_dev.bin))
	@echo "[$(SAGE_BL_BINARY_PATH)/sage_bl_dev.bin does not exist. Please advise!]"
else
	${Q_}$(CP) -f $(SAGE_BL_BINARY_PATH)/sage_bl_dev.bin ${NEXUS_BIN_DIR}
endif

ifeq (, $(wildcard $(SAGE_APP_BINARY_PATH)/sage_os_app_dev.bin))
	@echo "[$(SAGE_APP_BINARY_PATH)/sage_os_app_dev.bin does not exist. Please advise!]"
else
	${Q_}$(CP) -f $(SAGE_APP_BINARY_PATH)/sage_os_app_dev.bin ${NEXUS_BIN_DIR}
endif

endif

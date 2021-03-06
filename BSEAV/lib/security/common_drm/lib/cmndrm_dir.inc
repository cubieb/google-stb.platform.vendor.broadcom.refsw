#############################################################################
#    (c)2011 Broadcom Corporation
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
# $brcm_Log: $
# 
#############################################################################
ifeq ($(BCHP_CHIP),)
$(error BCHP_CHIP is not defined! Your Makefile should include nexus/platforms/<NEXUS_PLATFORM>/build/platform_app.inc)
endif

ifeq ($(B_REFSW_DEBUG), n)
BUILD_MODE = retail
else
ifeq ($(B_REFSW_DEBUG), minimal)
BUILD_MODE = minimal
else
ifeq ($(B_REFSW_DEBUG), no_error_messages)
BUILD_MODE = noerrors
else
BUILD_MODE = debug
endif
endif
endif

ifeq ($(filter $(BCHP_CHIP), 7400 7401 7405 7413 7325 7335 7125 7340 7342 7410 7420 7468), $(BCHP_CHIP))
ifeq ($(ANDROID_BUILD),y)
CMNDRM_DIR := 65nm-askm/android/${BUILD_MODE}
else
CMNDRM_DIR := 65nm-askm/${BUILD_MODE}
CFLAGS += -DCOMMON_DRM_65NM_CHIP=1
endif
endif

ifeq ($(findstring $(BCHP_CHIP), 7425 7231 7344 7346 73465 7358 7418 7429 74295 7552 7563 75635 7362 73625 75525), $(BCHP_CHIP))
ifeq ($(ANDROID_BUILD),y)
CMNDRM_DIR := Zeus20/android/${BUILD_MODE}
else
CMNDRM_DIR := Zeus20/${BUILD_MODE}
endif
endif

ifeq ($(findstring $(BCHP_CHIP), 7435 7584 75845), $(BCHP_CHIP))
ifeq ($(ANDROID_BUILD),y)
CMNDRM_DIR := Zeus30/android/${BUILD_MODE}
else
CMNDRM_DIR := Zeus30/${BUILD_MODE}
endif
endif


ifeq ($(findstring $(BCHP_CHIP), 7145 7252 7445 7439 74371 7250 7366 7364), $(BCHP_CHIP))
ifeq ($(ANDROID_BUILD),y)
CMNDRM_DIR := Zeus4x/android/${BUILD_MODE}
else
CMNDRM_DIR := Zeus4x/${BUILD_MODE}
endif
endif

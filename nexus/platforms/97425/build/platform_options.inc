#############################################################################
#    (c)2013-2014 Broadcom Corporation
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
#
# this file is included by nexus/platform/common/build/platform_modules.inc
# you can define your platform's options here

ifeq ($(NEXUS_USE_FRONTEND_DAUGHTER_CARD),y)
    NEXUS_USE_FRONTEND_DAUGHTER_CARD := y
endif
ifeq ($(NEXUS_PLATFORM_7425_DBS),y)
    NEXUS_FRONTEND_4506 := y
    NEXUS_FRONTEND_4506_VER := A1
endif

ifeq ($(NEXUS_USE_7425_SV_BOARD),y)
    NEXUS_FRONTEND_3112 := y
    NEXUS_PLATFORM_7425_CABLE := y
    NEXUS_KEYPAD_SUPPORT ?= n
else
    ifeq ($(NEXUS_USE_7425_VMS_SFF),y)
        NEXUS_PLATFORM_7425_CABLE := y
        ifeq ($(NEXUS_USE_FRONTEND_3461_DAUGHTER_CARD),y)
            NEXUS_FRONTEND_3461 := y
        else
            ifeq ($(NEXUS_PLATFORM_DOCSIS_PLUS_BCM3128_IB_SUPPORT),y)
                ifeq ($(NEXUS_PLATFORM_DOCSIS_BCM33843_SUPPORT),y)
                    NEXUS_FRONTEND_DOCSIS := y
                else
                    NEXUS_FRONTEND_3383 := y
                endif
                NEXUS_FRONTEND_3128 := y
                NEXUS_FRONTEND_312x := NEXUS_FRONTEND_3128
            endif
            ifeq ($(NEXUS_PLATFORM_DOCSIS_IB_SUPPORT),y)
                ifeq ($(NEXUS_PLATFORM_DOCSIS_BCM33843_SUPPORT),y)
                    NEXUS_FRONTEND_DOCSIS := y
                else
                    NEXUS_FRONTEND_3383 := y
                endif
            else
                NEXUS_FRONTEND_3128 := y
            endif
            ifeq ($(NEXUS_PLATFORM_DOCSIS_OOB_SUPPORT),y)
                ifeq ($(NEXUS_PLATFORM_DOCSIS_BCM33843_SUPPORT),y)
                    NEXUS_FRONTEND_DOCSIS := y
                else
                    NEXUS_FRONTEND_3383 := y
                endif
            else
                NEXUS_FRONTEND_312x_OOB := y
            endif
        endif
    else
        ifeq ($(NEXUS_PLATFORM_7425_CABLE),y)
            NEXUS_FRONTEND_3114 := y
            NEXUS_FRONTEND_3112 := y
       endif
    endif
endif

ifeq ($(NEXUS_PLATFORM_7425_CABLE),y)
    ifeq ($(NEXUS_FRONTEND_312x_VER),)
        NEXUS_FRONTEND_312x_VER := C0
    else
        NEXUS_FRONTEND_312x_VER := $(NEXUS_FRONTEND_312x_VER)
    endif

    ifeq ($(NEXUS_FRONTEND_3112_VER),)
        NEXUS_FRONTEND_31xx_VER := B0
    else
        NEXUS_FRONTEND_31xx_VER := $(NEXUS_FRONTEND_3112_VER)
    endif
    ifeq ($(NEXUS_FRONTEND_3114_VER),)
        NEXUS_FRONTEND_31xx_VER := B0
    else
        NEXUS_FRONTEND_31xx_VER := $(NEXUS_FRONTEND_3114_VER)
    endif
    ifeq ($(NEXUS_FRONTEND_3117_VER),)
        NEXUS_FRONTEND_31xx_VER := B0
    else
        NEXUS_FRONTEND_31xx_VER := $(NEXUS_FRONTEND_3117_VER)
    endif
endif

ifeq ($(NEXUS_PLATFORM_4517_DBS),y)
    NEXUS_FRONTEND_4517 := y
    NEXUS_FRONTEND_4517_VER := A0
endif
ifeq ($(NEXUS_PLATFORM_4528_DBS),y)
    NEXUS_FRONTEND_4528 := y
    NEXUS_FRONTEND_4528_VER := A0
endif
ifeq ($(NEXUS_PLATFORM_4538_DBS),y)
    NEXUS_FRONTEND_4538 := y
    NEXUS_FRONTEND_4538_VER := A0
endif

VIDEO_ENCODER_SUPPORT ?= y

ifeq ($(NEXUS_PLATFORM_97435_1STB1T),y)
NEXUS_PLATFORM_DEFINES += NEXUS_PLATFORM_97435_1STB1T=1
BXVD_SVD_USE_MEMC0 :=y
endif

ifeq ($(NEXUS_PLATFORM_7425_DBS),y)
NEXUS_PLATFORM_DEFINES += NEXUS_PLATFORM_7425_DBS=1
endif
ifeq ($(NEXUS_PLATFORM_4528_DBS),y)
NEXUS_PLATFORM_DEFINES += NEXUS_PLATFORM_4528_DBS=1
endif
ifeq ($(NEXUS_USE_7425_SATIPSW),y)
NEXUS_PLATFORM_DEFINES += NEXUS_USE_7425_SATIPSW=1
endif
ifeq ($(NEXUS_PLATFORM_7425_CABLE),y)
NEXUS_PLATFORM_DEFINES += NEXUS_PLATFORM_7425_CABLE=1
ifeq ($(NEXUS_PLATFORM_DOCSIS_PLUS_BCM3128_IB_SUPPORT),y)
NEXUS_PLATFORM_DEFINES += NEXUS_PLATFORM_DOCSIS_PLUS_BCM3128_IB_SUPPORT=1
endif
ifeq ($(NEXUS_PLATFORM_DOCSIS_BCM33843_SUPPORT),y)
NEXUS_PLATFORM_DEFINES += NEXUS_PLATFORM_DOCSIS_BCM33843_SUPPORT=1
endif
ifeq ($(NEXUS_PLATFORM_DOCSIS_OOB_SUPPORT),y)
NEXUS_PLATFORM_DEFINES += NEXUS_PLATFORM_DOCSIS_OOB_SUPPORT=1
endif
ifeq ($(NEXUS_PLATFORM_DOCSIS_IB_SUPPORT),y)
NEXUS_PLATFORM_DEFINES += NEXUS_PLATFORM_DOCSIS_IB_SUPPORT=1
endif
ifeq ($(NEXUS_USE_7425_SV_BOARD),y)
NEXUS_PLATFORM_DEFINES += NEXUS_USE_7425_SV_BOARD=1
endif
ifeq ($(NEXUS_USE_7425_VMS_SFF),y)
NEXUS_PLATFORM_DEFINES += NEXUS_USE_7425_VMS_SFF=1
ifeq ($(NEXUS_USE_FRONTEND_3461_DAUGHTER_CARD),y)
NEXUS_PLATFORM_DEFINES += NEXUS_USE_FRONTEND_3461_DAUGHTER_CARD=1
endif
endif
endif

#
# by default, we include the following
#
include $(NEXUS_TOP)/platforms/common/build/platform_generic_options.inc

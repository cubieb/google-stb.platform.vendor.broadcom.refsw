############################################################
#     (c)2003-2013 Broadcom Corporation
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
# Module Description:
#
# Revision History:
#
# Created: 08/28/2007 by Jon Garrett
#
# $brcm_Log: $
#
############################################################

#
# Conditional Options for this Makefile
#

######################
# Define this module #
######################
NEXUS_MODULES += BASE

##################
# Module Options #
##################

###################
# Module Includes #
###################
NEXUS_BASE_PUBLIC_INCLUDES = \
    $(NEXUS_TOP)/base/include \
    $(NEXUS_TOP)/base/include/public
    
NEXUS_BASE_PRIVATE_INCLUDES = \
    $(MAGNUM)/../BSEAV/lib/utils \
    $(NEXUS_TOP)/base/src/$(B_REFSW_OS) \
    $(NEXUS_TOP)/base/src
    
##################
# Module Sources #
##################
NEXUS_BASE_SOURCES = \
    $(NEXUS_TOP)/base/src/nexus_base.c \
    $(NEXUS_TOP)/base/src/nexus_base_object.c \
    $(NEXUS_TOP)/base/src/nexus_base_mmap.c \
    $(NEXUS_TOP)/base/src/nexus_base_scheduler.c \
    $(NEXUS_TOP)/base/src/nexus_base_stackcheck.c \
    $(NEXUS_TOP)/base/src/nexus_base_statistics.c

ifeq ($(filter $(B_REFSW_OS),ucos ucos_ii ucos_iii),$(B_REFSW_OS))
NEXUS_BASE_SOURCES += \
    $(NEXUS_TOP)/base/src/ucos/nexus_base_os.c
else
NEXUS_BASE_SOURCES += \
    $(NEXUS_TOP)/base/src/$(B_REFSW_OS)/nexus_base_os.c
endif

ifeq ($(B_REFSW_OS),linuxemu)
NEXUS_BASE_PUBLIC_INCLUDES += $(NEXUS_TOP)/base/include/linuxuser
else
ifeq ($(B_REFSW_OS),bare)
NEXUS_BASE_PUBLIC_INCLUDES += $(NEXUS_TOP)/base/include/linuxkernel
else
ifeq ($(filter $(B_REFSW_OS), ucos ucos_ii ucos_iii), $(B_REFSW_OS))
NEXUS_BASE_PUBLIC_INCLUDES += $(NEXUS_TOP)/base/include/ucos
else
NEXUS_BASE_PUBLIC_INCLUDES += $(NEXUS_TOP)/base/include/$(B_REFSW_OS)
endif
endif
endif

##################
# Module Defines #
##################
NEXUS_BASE_DEFINES :=  NEXUS_BASE_OS_$(B_REFSW_OS)=1
ifeq ($(NEXUS_MODE),proxy)
NEXUS_BASE_DEFINES += NEXUS_BASE_MODE_PROXY=1
endif
ifeq ($(B_REFSW_OS),bare)
NEXUS_BASE_DEFINES += NEXUS_BASE_MODE_PROXY=1
endif

ifneq (${B_REFSW_SYSTEM_MODE},CLIENT)
ifeq  ($(filter $(B_REFSW_ARCH), arm-linux aarch64-linux), $(B_REFSW_ARCH))
NEXUS_BASE_DEFINES += NEXUS_CPU_ARM=1
NEXUS_BASE_PRIVATE_INCLUDES += $(NEXUS_TOP)/../BSEAV/linux/driver/usermode
endif
endif

ifeq ($(NEXUS_NO_EXTERNAL_SCHEDULER),y)
NEXUS_BASE_DEFINES += NEXUS_NO_EXTERNAL_SCHEDULER=1
endif

#######################
# Module Dependencies #
#######################
# Base has no module dependencies
NEXUS_BASE_DEPENDENCIES :=

##################
# Magnum Modules #
##################
NEXUS_BASE_MAGNUM_MODULES := \
    $(MAGNUM)/basemodules/chp/build/bchp.inc \
    $(MAGNUM)/basemodules/dbg/bdbg.inc \
    $(MAGNUM)/basemodules/err/berr.inc \
    $(MAGNUM)/basemodules/kni/bkni.inc \
    $(MAGNUM)/basemodules/std/bstd.inc \
    $(MAGNUM)/commonutils/lst/blst.inc \
    $(MAGNUM)/basemodules/reg/breg.inc

NEXUS_EXTRA_MODULES += BAA_TREE 


#############################################################################
#
#       Copyright (c) 2005-2008, Broadcom Corporation.
#       All rights reserved.
#       Confidential Property of Broadcom Corporation.
# 
#  THIS SOFTWARE MAY ONLY BE USED SUBJECT TO AN EXECUTED SOFTWARE LICENSE
#  AGREEMENT  BETWEEN THE USER AND BROADCOM.  YOU HAVE NO RIGHT TO USE OR
#  EXPLOIT THIS MATERIAL EXCEPT SUBJECT TO THE TERMS OF SUCH AN AGREEMENT.
#
# $brcm_Workfile: $
# $brcm_Revision: $
# $brcm_Date: $
#
# File Description:
#
# Revision History:
#
# $brcm_Log: $
# 
#############################################################################

# Requires the use of the 'plat' script which defines the following:
#   PLATFORM (97038, 97398, ...)
#   BCHP_VER (B0, B1, C0, ...)
#   BCHP_7411_VER (C0, D0, ...) plus versions for other secondary chipsets
#   DEBUG
#   LINUX
#   ARCH
#   TOOLCHAIN

# Target O/S (can be one of the following: linuxuser)
TARGET_OS = linuxuser

# Directories relative to location of makefile
MAGNUM_DIR = ../../../../magnum
ROCKFORD_DIR = ../../../../rockford
FRAMEWORK_DIR = $(ROCKFORD_DIR)/appframework

# Name of application
APP = synclib

# Application source file list, include path, C flags, and link
# flags
APP_SOURCES= ./app.c
APP_INCLUDES = ./
APP_CFLAGS=
APP_LDFLAGS=

BSYSLIB_IMPL = linuxuser
APP_INCLUDES += $(BSYSLIB_IMPL_INCLUDES)
APP_SOURCES += $(BSYSLIB_IMPL_SOURCES)

# Must define ENDIAN to be either big or little
ENDIAN = little

# Want to see details (y/n)?
VERBOSE = n

# Debug (y/n)?
DEBUG = y

# Include object file list, include path, and C flags for common utilities and base modules 
# (sets MAGNUM_SOURCES, MAGNUM_INCLUDES, MAGNUM_CFLAGS, and MAGNUM_MODULE_DIR)
include $(FRAMEWORK_DIR)/build/magnum.inc

# Include object file list, include path, and C flags for other magnum modules required
# by this application (adds to MAGNUM_SOURCES, MAGNUM_INCLUDES, and MAGNUM_CFLAGS).
# Here is where you also define module specific makefile defines
include $(MAGNUM_DIR)/syslib/framework/build/bsyslib.inc
include $(MAGNUM_DIR)/syslib/synclib/build/bsynclib.inc

# At this point, user can add additional files, include paths, and C flags to 
# MAGNUM_SOURCES, MAGNUM_INCLUDES, and MAGNUM_CFLAGS (optional).

# Include other common modules (adds to COMMON_SOURCES, COMMON_INCLUDES, and
# COMMON_CFLAGS)
#include $(FRAMEWORK_DIR)/build/modules/common/fpga.inc

include $(ROCKFORD_DIR)/unittests/syslib/framework/build/build.inc

# Specifies how magnum files and application files are built.
include $(FRAMEWORK_DIR)/build/$(TARGET_OS)/build.inc


############################################################
#     Copyright (c) 2003-2012, Broadcom Corporation
#     All Rights Reserved
#     Confidential Property of Broadcom Corporation
#
#  THIS SOFTWARE MAY ONLY BE USED SUBJECT TO AN EXECUTED SOFTWARE LICENSE
#  AGREEMENT  BETWEEN THE USER AND BROADCOM.  YOU HAVE NO RIGHT TO USE OR
#  EXPLOIT THIS MATERIAL EXCEPT SUBJECT TO THE TERMS OF SUCH AN AGREEMENT.
#
# $brcm_Workfile: $
# $brcm_Revision: $
# $brcm_Date: $
#
# Module Description:
#
# Revision History:
#
# Created:
#
# $brcm_Log: $
#
############################################################

#
# Conditional Options for this Makefile
#
# N/A
#
# B0 and C0 have identical box mode files
BCHP_VER_LOWER_OVERRIDE:=c0

BBOX_SOURCES += \
	$(MAGNUM)/commonutils/box/src/$(BCHP_CHIP)/$(BCHP_VER_LOWER_OVERRIDE)/bbox_priv.c \
	$(MAGNUM)/commonutils/box/src/$(BCHP_CHIP)/$(BCHP_VER_LOWER_OVERRIDE)/bbox_priv_vce.c \
	$(MAGNUM)/commonutils/box/src/$(BCHP_CHIP)/$(BCHP_VER_LOWER_OVERRIDE)/bbox_memc_box1_config.c \
	$(MAGNUM)/commonutils/box/src/$(BCHP_CHIP)/$(BCHP_VER_LOWER_OVERRIDE)/bbox_memc_box2_config.c \
	$(MAGNUM)/commonutils/box/src/$(BCHP_CHIP)/$(BCHP_VER_LOWER_OVERRIDE)/bbox_memc_box3_config.c \
	$(MAGNUM)/commonutils/box/src/$(BCHP_CHIP)/$(BCHP_VER_LOWER_OVERRIDE)/bbox_memc_box4_config.c \
	$(MAGNUM)/commonutils/box/src/$(BCHP_CHIP)/$(BCHP_VER_LOWER_OVERRIDE)/bbox_memc_box5_config.c \
	$(MAGNUM)/commonutils/box/src/$(BCHP_CHIP)/$(BCHP_VER_LOWER_OVERRIDE)/bbox_memc_box6_config.c

#
# End of file
#

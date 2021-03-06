############################################################
#     Copyright (c) 2003-2013, Broadcom Corporation
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
# Created: 01/09/2007 by Jon Garrett
#
# $brcm_Log: $
# 
############################################################

#
# Conditional Options for this Makefile
#
# N/A
#

# Define this module
MAGNUM_MODULES += BAST

# Add dependency on BFEC
BAST_INCLUDES += $(MAGNUM)/commonutils/fec/include


##############################
# Handle 4501
##############################
ifeq ($(findstring 4501,$(BAST_CHIP)),4501)

# If the chip version is not specified, select a default
ifeq ($(BAST_4501_VER),)
BAST_4501_VER := C0
endif

BAST_4501_VER_UPPER := $(strip $(BAST_4501_VER))
BAST_4501_VER_UPPER := $(subst a,A,$(BAST_4501_VER_UPPER))
BAST_4501_VER_UPPER := $(subst b,B,$(BAST_4501_VER_UPPER))
BAST_4501_VER_UPPER := $(subst c,C,$(BAST_4501_VER_UPPER))

BAST_4501_VER_LOWER := $(strip $(BAST_4501_VER))
BAST_4501_VER_LOWER := $(subst A,a,$(BAST_4501_VER_LOWER))
BAST_4501_VER_LOWER := $(subst B,b,$(BAST_4501_VER_LOWER))
BAST_4501_VER_LOWER := $(subst C,c,$(BAST_4501_VER_LOWER))

# Source needs to know which revision
BAST_DEFINES += BAST_4501_VER=BCHP_VER_$(BAST_4501_VER_UPPER)

# Module Includes
BAST_INCLUDES += $(MAGNUM)/basemodules/chp/include/4501/common
BAST_INCLUDES += \
	$(MAGNUM)/portinginterface/ast/include/common \
	$(MAGNUM)/portinginterface/ast/include/4501 \
	$(MAGNUM)/portinginterface/ast/src/common \
	$(MAGNUM)/portinginterface/ast/src/4501
# Module Sources
BAST_SOURCES += \
	$(MAGNUM)/portinginterface/ast/src/common/bast.c \
	$(MAGNUM)/portinginterface/ast/src/4501/bast_4501.c \
	$(MAGNUM)/portinginterface/ast/src/4501/bast_4501_priv.c \
	$(MAGNUM)/portinginterface/ast/src/4501/bast_4501_fw.c
endif


##############################
# Handle 4506
##############################
ifeq ($(findstring 4506,$(BAST_CHIP)),4506)

# If the chip version is not specified, select a default
ifeq ($(BAST_4506_VER),)
BAST_4506_VER := A1
endif

BAST_4506_VER_UPPER := $(strip $(BAST_4506_VER))
BAST_4506_VER_UPPER := $(subst a,A,$(BAST_4506_VER_UPPER))
BAST_4506_VER_UPPER := $(subst b,B,$(BAST_4506_VER_UPPER))
BAST_4506_VER_UPPER := $(subst c,C,$(BAST_4506_VER_UPPER))

BAST_4506_VER_LOWER := $(strip $(BAST_4506_VER))
BAST_4506_VER_LOWER := $(subst A,a,$(BAST_4506_VER_LOWER))
BAST_4506_VER_LOWER := $(subst B,b,$(BAST_4506_VER_LOWER))
BAST_4506_VER_LOWER := $(subst C,c,$(BAST_4506_VER_LOWER))

# Source needs to know which revision
BAST_DEFINES += BAST_4506_VER=BCHP_VER_$(BAST_4506_VER_UPPER)

# Module Includes
BAST_INCLUDES += $(MAGNUM)/basemodules/chp/include/4506/common
BAST_INCLUDES += \
	$(MAGNUM)/portinginterface/ast/include/common \
	$(MAGNUM)/portinginterface/ast/include/4506 \
	$(MAGNUM)/portinginterface/ast/src/common \
	$(MAGNUM)/portinginterface/ast/src/4506
# Module Sources
BAST_SOURCES += \
	$(MAGNUM)/portinginterface/ast/src/common/bast.c \
	$(MAGNUM)/portinginterface/ast/src/4506/bast_4506.c \
	$(MAGNUM)/portinginterface/ast/src/4506/bast_4506_priv.c \
	$(MAGNUM)/portinginterface/ast/src/4506/bast_4506_fw.c
endif


##############################
# Handle 4517
##############################
ifeq ($(findstring 4517,$(BAST_CHIP)),4517)

# If the chip version is not specified, select a default
ifeq ($(BAST_4517_VER),)
BAST_4517_VER := B0
endif

BAST_4517_VER_UPPER := $(strip $(BAST_4517_VER))
BAST_4517_VER_UPPER := $(subst a,A,$(BAST_4517_VER_UPPER))
BAST_4517_VER_UPPER := $(subst b,B,$(BAST_4517_VER_UPPER))
BAST_4517_VER_UPPER := $(subst c,C,$(BAST_4517_VER_UPPER))

BAST_4517_VER_LOWER := $(strip $(BAST_4517_VER))
BAST_4517_VER_LOWER := $(subst A,a,$(BAST_4517_VER_LOWER))
BAST_4517_VER_LOWER := $(subst B,b,$(BAST_4517_VER_LOWER))
BAST_4517_VER_LOWER := $(subst C,c,$(BAST_4517_VER_LOWER))

# Source needs to know which revision
BAST_DEFINES += BAST_4517_VER=BCHP_VER_$(BAST_4517_VER_UPPER)

# Module Includes
BAST_INCLUDES += $(MAGNUM)/basemodules/chp/include/4517/common
BAST_INCLUDES += $(MAGNUM)/basemodules/chp/include/4517/rdb/hab/$(BAST_4517_VER_LOWER)
BAST_INCLUDES += $(MAGNUM)/basemodules/hab/include/common
BAST_INCLUDES += $(MAGNUM)/basemodules/hab/include/4517
BAST_INCLUDES += \
	$(MAGNUM)/portinginterface/ast/include/common \
	$(MAGNUM)/portinginterface/ast/include/4517 \
	$(MAGNUM)/portinginterface/ast/src/common \
	$(MAGNUM)/portinginterface/ast/src/4517
# Module Sources
BAST_SOURCES += \
	$(MAGNUM)/portinginterface/ast/src/common/bast.c \
	$(MAGNUM)/portinginterface/ast/src/4517/bast_4517.c \
	$(MAGNUM)/portinginterface/ast/src/4517/bast_4517_priv.c
endif


##############################
# Handle 4528
##############################
ifeq ($(findstring 4528,$(BAST_CHIP)),4528)

# If the chip version is not specified, select a default
ifeq ($(BAST_4528_VER),)
BAST_4528_VER := A0
endif

BAST_4528_VER_UPPER := $(strip $(BAST_4528_VER))
BAST_4528_VER_UPPER := $(subst a,A,$(BAST_4528_VER_UPPER))
BAST_4528_VER_UPPER := $(subst b,B,$(BAST_4528_VER_UPPER))
BAST_4528_VER_UPPER := $(subst c,C,$(BAST_4528_VER_UPPER))

BAST_4528_VER_LOWER := $(strip $(BAST_4528_VER))
BAST_4528_VER_LOWER := $(subst A,a,$(BAST_4528_VER_LOWER))
BAST_4528_VER_LOWER := $(subst B,b,$(BAST_4528_VER_LOWER))
BAST_4528_VER_LOWER := $(subst C,c,$(BAST_4528_VER_LOWER))

# Source needs to know which revision
BAST_DEFINES += BAST_4528_VER=BCHP_VER_$(BAST_4528_VER_UPPER)

# Module Includes
BAST_INCLUDES += $(MAGNUM)/basemodules/chp/include/4528/common
BAST_INCLUDES += $(MAGNUM)/basemodules/chp/include/4528/rdb/hab/$(BAST_4528_VER_LOWER)
BAST_INCLUDES += $(MAGNUM)/basemodules/hab/include/common
BAST_INCLUDES += $(MAGNUM)/basemodules/hab/include/4528
BAST_INCLUDES += \
	$(MAGNUM)/portinginterface/ast/include/common \
	$(MAGNUM)/portinginterface/ast/include/4528 \
	$(MAGNUM)/portinginterface/ast/src/common \
	$(MAGNUM)/portinginterface/ast/src/4528
# Module Sources
BAST_SOURCES += \
	$(MAGNUM)/portinginterface/ast/src/common/bast.c \
	$(MAGNUM)/portinginterface/ast/src/4528/bast_4528.c \
	$(MAGNUM)/portinginterface/ast/src/4528/bast_4528_priv.c
endif


##############################
# Handle 4538
##############################
ifeq ($(findstring 4538,$(BAST_CHIP)),4538)

# If the chip version is not specified, select a default
ifeq ($(BAST_4538_VER),)
BAST_4538_VER := A0
endif

BAST_4538_VER_UPPER := $(strip $(BAST_4538_VER))
BAST_4538_VER_UPPER := $(subst a,A,$(BAST_4538_VER_UPPER))
BAST_4538_VER_UPPER := $(subst b,B,$(BAST_4538_VER_UPPER))
BAST_4538_VER_UPPER := $(subst c,C,$(BAST_4538_VER_UPPER))

BAST_4538_VER_LOWER := $(strip $(BAST_4538_VER))
BAST_4538_VER_LOWER := $(subst A,a,$(BAST_4538_VER_LOWER))
BAST_4538_VER_LOWER := $(subst B,b,$(BAST_4538_VER_LOWER))
BAST_4538_VER_LOWER := $(subst C,c,$(BAST_4538_VER_LOWER))

# Source needs to know which revision
BAST_DEFINES += BAST_4538_VER=BCHP_VER_$(BAST_4538_VER_UPPER)

# Module Includes
BAST_INCLUDES += $(MAGNUM)/basemodules/chp/include/4538/common
BAST_INCLUDES += $(MAGNUM)/basemodules/chp/include/4538/rdb/hab/$(BAST_4538_VER_LOWER)
BAST_INCLUDES += $(MAGNUM)/basemodules/hab/include/common
BAST_INCLUDES += $(MAGNUM)/basemodules/hab/include/4538
BAST_INCLUDES += \
	$(MAGNUM)/portinginterface/ast/include/common \
	$(MAGNUM)/portinginterface/ast/include/4538 \
	$(MAGNUM)/portinginterface/ast/src/common \
	$(MAGNUM)/portinginterface/ast/src/4538
# Module Sources
BAST_SOURCES += \
	$(MAGNUM)/portinginterface/ast/src/common/bast.c \
	$(MAGNUM)/portinginterface/ast/src/4538/bast_4538.c \
	$(MAGNUM)/portinginterface/ast/src/4538/bast_4538_priv.c
endif


##############################
# Handle G2
##############################
ifeq ($(findstring $(BCHP_CHIP), 7325 7335 7342 7340), $(BCHP_CHIP))
# Module Includes
BAST_INCLUDES += \
	$(MAGNUM)/portinginterface/ast/include/common \
	$(MAGNUM)/portinginterface/ast/include/g2 \
	$(MAGNUM)/portinginterface/ast/src/common \
	$(MAGNUM)/portinginterface/ast/src/g2/common \
	$(MAGNUM)/portinginterface/ast/src/g2/$(BCHP_CHIP)
# Module Sources
BAST_SOURCES += \
	$(MAGNUM)/portinginterface/ast/src/common/bast.c \
	$(MAGNUM)/portinginterface/ast/src/g2/common/bast_g2.c \
	$(MAGNUM)/portinginterface/ast/src/g2/common/bast_g2_priv.c \
	$(MAGNUM)/portinginterface/ast/src/g2/common/bast_g2_priv_diseqc.c \
	$(MAGNUM)/portinginterface/ast/src/g2/common/bast_g2_priv_ftm.c \
	$(MAGNUM)/portinginterface/ast/src/g2/common/bast_g2_priv_ldpc.c \
	$(MAGNUM)/portinginterface/ast/src/g2/common/bast_g2_priv_lna.c \
	$(MAGNUM)/portinginterface/ast/src/g2/common/bast_g2_priv_mi2c.c \
	$(MAGNUM)/portinginterface/ast/src/g2/common/bast_g2_priv_qpsk.c \
	$(MAGNUM)/portinginterface/ast/src/g2/common/bast_g2_priv_sds.c \
	$(MAGNUM)/portinginterface/ast/src/g2/common/bast_g2_priv_tuner.c \
	$(MAGNUM)/portinginterface/ast/src/g2/common/bast_g2_priv_turbo.c \
	$(MAGNUM)/portinginterface/ast/src/g2/$(BCHP_CHIP)/bast_$(BCHP_CHIP)_priv.c

ifeq ($(BAST_AFEC_CORE_DISABLED),y)
BAST_DEFINES += BAST_AFEC_CORE_DISABLED
endif

endif


##############################
# Handle G3
##############################
ifeq ($(findstring $(BCHP_CHIP), 7344 7346 7358 7360 7362 7228 73625 73465), $(BCHP_CHIP))
# Module Includes
BAST_INCLUDES += \
	$(MAGNUM)/portinginterface/ast/include/common \
	$(MAGNUM)/portinginterface/ast/include/g3 \
	$(MAGNUM)/portinginterface/ast/src/common \
	$(MAGNUM)/portinginterface/ast/src/g3/common \
	$(MAGNUM)/portinginterface/ast/src/g3/$(BCHP_CHIP)
# Module Sources
BAST_SOURCES += \
	$(MAGNUM)/portinginterface/ast/src/common/bast.c \
	$(MAGNUM)/portinginterface/ast/src/g3/common/bast_g3.c	\
	$(MAGNUM)/portinginterface/ast/src/g3/common/bast_g3_priv.c \
	$(MAGNUM)/portinginterface/ast/src/g3/common/bast_g3_priv_acq.c \
	$(MAGNUM)/portinginterface/ast/src/g3/common/bast_g3_priv_dft.c \
	$(MAGNUM)/portinginterface/ast/src/g3/common/bast_g3_priv_diseqc.c \
	$(MAGNUM)/portinginterface/ast/src/g3/common/bast_g3_priv_ftm.c \
	$(MAGNUM)/portinginterface/ast/src/g3/common/bast_g3_priv_hp.c \
	$(MAGNUM)/portinginterface/ast/src/g3/common/bast_g3_priv_ldpc.c \
	$(MAGNUM)/portinginterface/ast/src/g3/common/bast_g3_priv_mi2c.c \
	$(MAGNUM)/portinginterface/ast/src/g3/common/bast_g3_priv_plc.c \
	$(MAGNUM)/portinginterface/ast/src/g3/common/bast_g3_priv_cwc.c \
	$(MAGNUM)/portinginterface/ast/src/g3/common/bast_g3_priv_qpsk.c \
	$(MAGNUM)/portinginterface/ast/src/g3/common/bast_g3_priv_snr.c \
	$(MAGNUM)/portinginterface/ast/src/g3/common/bast_g3_priv_timer.c \
	$(MAGNUM)/portinginterface/ast/src/g3/common/bast_g3_priv_tuner.c \
	$(MAGNUM)/portinginterface/ast/src/g3/common/bast_g3_priv_turbo.c \
	$(MAGNUM)/portinginterface/ast/src/g3/common/bast_g3_priv_lna.c \
	$(MAGNUM)/portinginterface/ast/src/g3/$(BCHP_CHIP)/bast_$(BCHP_CHIP)_priv.c
endif

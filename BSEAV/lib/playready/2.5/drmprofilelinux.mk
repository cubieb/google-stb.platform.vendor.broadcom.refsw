#**@@@+++@@@@******************************************************************
#*
#* Microsoft PlayReady
#* Copyright (c) Microsoft Corporation. All rights reserved.
#*
#**@@@---@@@@******************************************************************

!if "$(DRM_BUILD_PROFILE)" != "LINUX"
!error DRM_BUILD_PROFILE must be Linux to use drmprofilelinux.mk
!endif

!INCLUDE "drmprofilempr.mk"

DRM_ACTIVATION_PLATFORM_VIA_PROFILE=0
_DRM_BUILD_PROFILE_INT_VIA_PROFILE=900
DRM_SUPPORT_ACTIVATION_VIA_PROFILE=0
DRM_SUPPORT_ANTIROLLBACK_CLOCK_VIA_PROFILE=1
DRM_SUPPORT_APP_POLICY_VIA_PROFILE=0
DRM_SUPPORT_APPREVOCATION_VIA_PROFILE=1
DRM_SUPPORT_BBXLEGACY_VIA_PROFILE=0
DRM_SUPPORT_BBXSLK_VIA_PROFILE=0
DRM_SUPPORT_CERTCACHE_VIA_PROFILE=1
DRM_SUPPORT_CERTPARSERCACHE_VIA_PROFILE=0
DRM_SUPPORT_CLEANSTORE_VIA_PROFILE=1
DRM_SUPPORT_COPYOPL_VIA_PROFILE=1
DRM_SUPPORT_CRT_VIA_PROFILE=1
DRM_SUPPORT_DEVCERTKEYGEN_VIA_PROFILE=1
DRM_SUPPORT_DEVICEASSETS_VIA_PROFILE=1
DRM_SUPPORT_DEVICEREVOCATION_VIA_PROFILE=1
DRM_SUPPORT_DEVICESTORE_VIA_PROFILE=1
DRM_SUPPORT_DLA_VIA_PROFILE=0
DRM_SUPPORT_DOMAIN_VIA_PROFILE=1
DRM_SUPPORT_ECCPROFILING_VIA_PROFILE=1
DRM_SUPPORT_EMBEDDED_CERTS_VIA_PROFILE=0
DRM_SUPPORT_HDSBLOCKHEADERCACHE_VIA_PROFILE=1
DRM_SUPPORT_INLINEDWORDCPY_VIA_PROFILE=1
DRM_SUPPORT_LICENSE_SYNC_VIA_PROFILE=1
DRM_SUPPORT_LICGEN_VIA_PROFILE=1
DRM_SUPPORT_LOCKING_VIA_PROFILE=1
DRM_SUPPORT_M2TSENCRYPTOR_VIA_PROFILE=1
DRM_SUPPORT_METERING_VIA_PROFILE=1
DRM_SUPPORT_MODELREVOCATION_VIA_PROFILE=0
DRM_SUPPORT_MOVE_VIA_PROFILE=1
DRM_SUPPORT_MULTI_THREADING_VIA_PROFILE=1
DRM_SUPPORT_NONVAULTSIGNING_VIA_PROFILE=1
DRM_SUPPORT_PERFORMANCE_VIA_PROFILE=1
DRM_SUPPORT_PRECOMPUTE_GTABLE_VIA_PROFILE=1
DRM_SUPPORT_PRIVATE_KEY_CACHE_VIA_PROFILE=0
DRM_SUPPORT_PRNDTX_VIA_PROFILE=1
DRM_SUPPORT_PRNDRX_VIA_PROFILE=1
DRM_SUPPORT_REACTIVATION_VIA_PROFILE=0
DRM_SUPPORT_SECURE_CLOCK_VIA_PROFILE=1
DRM_SUPPORT_SECUREOEMHAL_VIA_PROFILE=1
DRM_SUPPORT_SECUREOEMHAL_PLAY_ONLY_VIA_PROFILE=0
DRM_SUPPORT_SYMOPT_VIA_PROFILE=0
DRM_SUPPORT_THUMBNAIL_VIA_PROFILE=1
DRM_SUPPORT_VIEWRIGHTS_VIA_PROFILE=1
DRM_SUPPORT_WMDRM_VIA_PROFILE=0
DRM_SUPPORT_WMDRMNET_VIA_PROFILE=1
DRM_SUPPORT_XMLHASH_VIA_PROFILE=1

DRM_USE_IOCTL_HAL_GET_DEVICE_INFO_VIA_PROFILE=0
DRM_TEST_SUPPORT_NET_IO_VIA_PROFILE=0
DRM_TEST_SUPPORT_ACTIVATION_VIA_PROFILE=0

_ADDLICENSE_WRITE_THRU_VIA_PROFILE=0


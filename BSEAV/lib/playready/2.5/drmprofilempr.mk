#**@@@+++@@@@******************************************************************
#*
#* Microsoft PlayReady
#* Copyright (c) Microsoft Corporation. All rights reserved.
#*
#**@@@---@@@@******************************************************************

#*
#* This is NOT a complete profile!
#*

#*
#* 1. It includes those macros shared by all implementations
#*  that use MPR obfuscation technology.
#*
!INCLUDE "DrmProfileSHARED.mk"

DRM_SUPPORT_ASSEMBLY_VIA_PROFILE=0
DRM_SUPPORT_DEVICE_SIGNING_KEY_VIA_PROFILE=1
DRM_SUPPORT_FORCE_ALIGN_VIA_PROFILE=1

#*
#* For x86 and amd64 builds PK is built with namespaces
#* if we want to link something to PK libraries, we need
#* namespaces. For other builds, where extern "C" APIs
#* are needed, we do not use namespaces.
#*
DRM_SUPPORT_TEST_SETTINGS_VIA_PROFILE=0
!if "$(_BUILDARCH)" != "ia64"
USE_PK_NAMESPACES_VIA_PROFILE=1
!else
USE_PK_NAMESPACES_VIA_PROFILE=0
!endif

DRM_INCLUDE_PK_NAMESPACE_USING_STATEMENT_VIA_PROFILE=1

#*
#* 2. It sets all values NECESSARY to compile PK code,
#*  but only if they are not already set by a profile
#*  that includes this file.
#*

!IF "$(_DRM_BUILD_PROFILE_INT_VIA_PROFILE)"==""
_DRM_BUILD_PROFILE_INT_VIA_PROFILE=1000
!ENDIF

!IF "$(DRM_SUPPORT_LOCKING_VIA_PROFILE)"==""
DRM_SUPPORT_LOCKING_VIA_PROFILE=0
!ENDIF

!IF "$(DRM_SUPPORT_MULTI_THREADING_VIA_PROFILE)"==""
DRM_SUPPORT_MULTI_THREADING_VIA_PROFILE=0
!ENDIF

!IF "$(DRM_SUPPORT_PRECOMPUTE_GTABLE_VIA_PROFILE)"==""
DRM_SUPPORT_PRECOMPUTE_GTABLE_VIA_PROFILE=0
!ENDIF

!IF "$(DRM_SUPPORT_DEVCERTKEYGEN_VIA_PROFILE)"==""
DRM_SUPPORT_DEVCERTKEYGEN_VIA_PROFILE=0
!ENDIF

!IF "$(DRM_SUPPORT_PRIVATE_KEY_CACHE_VIA_PROFILE)"==""
DRM_SUPPORT_PRIVATE_KEY_CACHE_VIA_PROFILE=0
!ENDIF

!IF "$(DRM_SUPPORT_ECCPROFILING_VIA_PROFILE)"==""
DRM_SUPPORT_ECCPROFILING_VIA_PROFILE=0
!ENDIF

!IF "$(DRM_SUPPORT_EMBEDDED_CERTS_VIA_PROFILE)"==""
DRM_SUPPORT_EMBEDDED_CERTS_VIA_PROFILE=0
!ENDIF

!IF "$(DRM_SUPPORT_INLINEDWORDCPY_VIA_PROFILE)"==""
DRM_SUPPORT_INLINEDWORDCPY_VIA_PROFILE=0
!ENDIF

!IF "$(DRM_SUPPORT_NONVAULTSIGNING_VIA_PROFILE)"==""
DRM_SUPPORT_NONVAULTSIGNING_VIA_PROFILE=0
!ENDIF

!IF "$(DRM_SUPPORT_REACTIVATION_VIA_PROFILE)" == ""
DRM_SUPPORT_REACTIVATION_VIA_PROFILE=0
!ENDIF

!IF "$(DRM_SUPPORT_SECUREOEMHAL_VIA_PROFILE)"==""
DRM_SUPPORT_SECUREOEMHAL_VIA_PROFILE=0
!ENDIF

!IF "$(DRM_SUPPORT_SECUREOEMHAL_PLAY_ONLY_VIA_PROFILE)"==""
DRM_SUPPORT_SECUREOEMHAL_PLAY_ONLY_VIA_PROFILE=0
!ENDIF

!IF "$(DRM_USE_IOCTL_HAL_GET_DEVICE_INFO_VIA_PROFILE)"==""
DRM_USE_IOCTL_HAL_GET_DEVICE_INFO_VIA_PROFILE=0
!ENDIF

#!IF "$(_DATASTORE_WRITE_THRU_VIA_PROFILE)"==""
#_DATASTORE_WRITE_THRU_VIA_PROFILE=0
#!ENDIF

!IF "$(_ADDLICENSE_WRITE_THRU_VIA_PROFILE)"==""
_ADDLICENSE_WRITE_THRU_VIA_PROFILE=0
!ENDIF

!IF "$(DRM_TEST_SUPPORT_NET_IO_VIA_PROFILE)"==""
DRM_TEST_SUPPORT_NET_IO_VIA_PROFILE=0
!ENDIF

!IF "$(DRM_TEST_SUPPORT_ACTIVATION_VIA_PROFILE)"==""
DRM_TEST_SUPPORT_ACTIVATION_VIA_PROFILE=0
!ENDIF

DRM_KEYFILE_VERSION_VIA_PROFILE=3

#*
#* 3. It intentionally does NOT set anything else.
#*  This means modules for link-time settings
#*  will NOT be included when using just this profile.
#*


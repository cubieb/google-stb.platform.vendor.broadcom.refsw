/*=============================================================================
Copyright (c) 2014 Broadcom Europe Limited.
All rights reserved.

Project  :  GPUMonitor Hook
Module   :  API function table

FILE DESCRIPTION
API function table
=============================================================================*/

#ifndef __API_H__
#define __API_H__

#include <GLES3/gl32.h>
#include <GLES3/gl3ext.h>
#include <GLES3/gl3ext_brcm.h>
#include <GLES2/gl2ext.h>

#undef GL_TRUE
#undef GL_FALSE

#include <EGL/egl.h>
#include <EGL/eglext.h>
#include <EGL/eglext_brcm.h>
#include <GLES/gl.h>
#include <GLES/glext.h>

#ifdef BCG_ABSTRACT_PLATFORM
/* These entry points are only available with BCG's runtime loadable platforms */
struct BEGL_SchedInterface;
struct BEGL_DisplayInterface;
struct BEGL_MemoryInterface;
#endif

typedef struct {

// This table content is auto-generated by running ./gen_hook_tables.py in v3dv3/tools/v3d/hook_codegen
#include "apih.inc"

#ifdef BCG_ABSTRACT_PLATFORM
   /* These entry points are only available with BCG's runtime loadable platforms */
   void          (*real_BEGL_RegisterSchedInterface)(BEGL_SchedInterface *iface);
   void          (*real_BEGL_RegisterDisplayInterface)(BEGL_DisplayInterface *iface);
   void          (*real_BEGL_RegisterMemoryInterface)(BEGL_MemoryInterface *iface);
#endif
} REAL_GL_API_TABLE;

extern bool fill_real_func_table(REAL_GL_API_TABLE *table);

#endif /* __API_H__ */

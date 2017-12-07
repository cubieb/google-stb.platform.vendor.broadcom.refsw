/******************************************************************************
 *  Copyright (C) 2016 Broadcom. The term "Broadcom" refers to Broadcom Limited and/or its subsidiaries.
 ******************************************************************************/
#pragma once

#include "interface/khronos/include/EGL/egl.h"
#include "interface/khronos/include/EGL/eglext.h"
#include "interface/khronos/egl/egl_int.h"

#include "interface/khronos/common/khrn_client_platform.h"

typedef enum {
   WINDOW,
   PBUFFER,
   PIXMAP
} EGL_SURFACE_TYPE_T;

typedef enum {
   SRGB,
   LINEAR
} EGL_SURFACE_COLORSPACE_T;

typedef enum {
   NONPRE,
   PRE
} EGL_SURFACE_ALPHAFORMAT_T;

typedef struct {
   EGLSurface name;

   /*
      type

      Invariants:

      (EGL_SURFACE_TYPE)
      type in {WINDOW, PBUFFER, PIXMAP}
   */
   EGL_SURFACE_TYPE_T type;

   /*
      colorspace

      Invariants:

      (EGL_SURFACE_COLORSPACE)
      colorspace in {SRGB, LINEAR}
   */
   EGL_SURFACE_COLORSPACE_T colorspace;

   /*
      alphaformat

      Invariants:

      (EGL_SURFACE_ALPHAFORMAT)
      alphaformat in {NONPRE, PRE}
   */
   EGL_SURFACE_ALPHAFORMAT_T alphaformat;

   /*
      config

      Invariants:

      (EGL_SURFACE_CONFIG)
      config is a valid EGLConfig
   */
   EGLConfig config;

   uint32_t base_width;
   uint32_t base_height;

   /*
      buffers

      Usually 1 or 3.

      Invariants:

      (EGL_SURFACE_BUFFERS)
      1 <= buffers <= EGL_MAX_BUFFERS
   */
   uint32_t buffers;

   /*
      width

      Invariants:

      (EGL_SURFACE_WIDTH)
      1 <= width <= EGL_CONFIG_MAX_WIDTH
   */
   uint32_t width;

   /*
      height

      Invariants:

      (EGL_SURFACE_HEIGHT)
      1 <= height <= EGL_CONFIG_MAX_HEIGHT
   */
   uint32_t height;

   EGL_SURFACE_ID_T serverbuffer;

   /*
      context_binding_count

      Invariant:

      (EGL_SURFACE_BINDING_COUNT)
      If we are current, how many times we are bound to the current context. Otherwise 0.
   */
   uint32_t context_binding_count;
   struct CLIENT_THREAD_STATE *thread;    // If we are current, which the EGL client state for the thread are we associated with.

#if EGL_KHR_lock_surface
   EGLBoolean is_locked;
   void *mapped_buffer;
#endif

   /*
      is_destroyed

      Invariant:

      (EGL_SURFACE_IS_DESTROYED)
      Iff true, is not a member of the CLIENT_PROCESS_STATE_T.surfaces
   */
   bool is_destroyed;

   /*
      swap_behavior

      Invariant:

      (EGL_SURFACE_SWAP_BEHAVIOUR)
      swap_behavior in {EGL_BUFFER_DESTROYED, EGL_BUFFER_PRESERVED}
   */
   EGLint swap_behavior;

   /*
      multisample_resolve

      Invariant:

      (EGL_SURFACE_MULTISAMPLE_RESOLVE)
      multisample_resolve == EGL_MULTISAMPLE_RESOLVE_DEFAULT
   */
   EGLint multisample_resolve;

   /* For WINDOW types only */

   /*
      win

      Validity:
      type == WINDOW
   */
   EGLNativeWindowType win;

   /*
      largest_pbuffer

      Validity:
      type == PBUFFER
   */
   bool largest_pbuffer;

   /*
      mipmap_texture

      Validity:
      type == PBUFFER
   */
   bool mipmap_texture;

   /*
      mipmap_level

      Validity:
      type == PBUFFER
   */
   uint32_t mipmap_level;

   /*
      texture_format

      Validity:
      type == PBUFFER

      Invariant:
      texture_format in {EGL_NO_TEXTURE, EGL_TEXTURE_RGB, EGL_TEXTURE_RGBA}
   */
   EGLenum texture_format;

   /*
      texture_target

      Validity:
      type == PBUFFER

      Invariant:
      texture_target in {EGL_NO_TEXTURE, EGL_TEXTURE_2D}
   */
   EGLenum texture_target;

   /* For PIXMAP types only */

   /*
      pixmap

      Validity:
      type == PIXMAP

      Invariant:
      pixmap is a valid client-side pixmap handle for pixmap P
   */
   EGLNativePixmapType pixmap;
} EGL_SURFACE_T;

extern EGLint egl_surface_check_attribs(
   EGL_SURFACE_TYPE_T type,
   const EGLint *attrib_list,
   bool *linear,
   bool *premult,
   int *width,
   int *height,
   bool *largest_pbuffer,
   EGLenum *texture_format,
   EGLenum *texture_target,
   bool *mipmap_texture,
   bool *secure
);
struct CLIENT_PROCESS_STATE;

extern EGL_SURFACE_T *egl_surface_create(
   EGLSurface name,
   EGL_SURFACE_TYPE_T type,
   EGL_SURFACE_COLORSPACE_T colorspace,
   EGL_SURFACE_ALPHAFORMAT_T alphaformat,
   bool secure,
   uint32_t buffers,
   uint32_t width,
   uint32_t height,
   EGLConfig config,
   EGLNativeWindowType win,
   uintptr_t serverwin,
   bool largest_pbuffer,
   bool mipmap_texture,
   EGLenum texture_format,
   EGLenum texture_target,
   EGLNativePixmapType pixmap);

extern void egl_surface_free(EGL_SURFACE_T *surface);

extern EGLBoolean egl_surface_get_attrib(EGL_SURFACE_T *surface, EGLint attrib, EGLint *value);
extern EGLint egl_surface_set_attrib(EGL_SURFACE_T *surface, EGLint attrib, EGLint value);
extern EGLint egl_surface_get_render_buffer(EGL_SURFACE_T *surface);

#if EGL_KHR_lock_surface
extern EGLint egl_surface_get_mapped_buffer_attrib(EGL_SURFACE_T *surface, EGLint attrib, EGLint *value);
#endif
extern void egl_surface_maybe_free(EGL_SURFACE_T *surface);

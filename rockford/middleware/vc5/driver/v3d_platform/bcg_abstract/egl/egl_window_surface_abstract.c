/*=============================================================================
Copyright (c) 2013 Broadcom Europe Limited.
All rights reserved.

Project  :  khronos

FILE DESCRIPTION
=============================================================================*/

#include "vcos.h"
#include "middleware/khronos/egl/egl_display.h"
#include "middleware/khronos/egl/egl_surface.h"
#include "middleware/khronos/egl/egl_surface_base.h"
#include "middleware/khronos/egl/egl_thread.h"
#include "middleware/khronos/egl/egl_context_gl.h"

#include "bcm_sched_api.h"
#include "middleware/khronos/common/khrn_process.h"
#include "middleware/khronos/common/khrn_fmem.h"

#include "gmem.h"
#include "v3d_scheduler.h"

#include "egl_platform_abstract.h"
#include "egl_surface_common_abstract.h"

/* Our own representation of an egl_window_surface */
struct egl_window_surface
{
   EGL_SURFACE_T base;                       /* The driver's internal surface data */
   KHRN_IMAGE_T  *active_image;              /* The current back buffer as a KHRN_IMAGE_T */
   void          *native_back_buffer;        /* The current back buffer surface (opaque) */
   void          *native_window_state;       /* Opaque data that the platform ties to the native window */
};

static EGL_SURFACE_METHODS_T fns;

static bool dequeue_buffer(EGL_WINDOW_SURFACE_T *surf)
{
   int                           fence = -1;
   BEGL_DisplayInterface         *platform = &g_bcgPlatformData.displayInterface;
   BEGL_BufferFormat             format, actualFormat;
   GFX_LFMT_T                    gfx_format;

   /* What color format does the config request? */
   GFX_LFMT_T color_format = egl_config_colorformat(surf->base.config,
      surf->base.colorspace,
      surf->base.alpha_format);
   actualFormat = format = get_begl_format_abstract(color_format);

   /* Get our initial buffer */
   assert(platform->GetNextSurface);
   if (platform->GetNextSurface(platform->context, surf->native_window_state, format,
                                &actualFormat, &surf->native_back_buffer, &fence) != BEGL_Success)
      return false;

   surf->active_image = image_from_surface_abstract(surf->native_back_buffer, true);

   if (surf->active_image == NULL)
   {
      assert(platform->CancelSurface);
      platform->CancelSurface(platform->context, surf->native_window_state,
            surf->native_back_buffer, fence);
      return false;
   }

   /* window surfaces need to be renderable */
   gfx_format = khrn_image_get_lfmt(surf->active_image, 0);
   if (!egl_can_render_format(gfx_format))
   {
      platform->CancelSurface(platform->context, surf->native_window_state,
            surf->native_back_buffer, fence);
      KHRN_MEM_ASSIGN(surf->active_image, NULL);
      return false;
   }

   if (fence == -1)
      return true;

   egl_context_add_fence(NULL, &surf->base, fence);

   return true;
}

static void dump_gmem_status(void)
{
   static int  s_count = -1;
   static int  s_limit = 30;

   if (s_count == -1)
   {
      char value[VCOS_PROPERTY_VALUE_MAX];
      vcos_property_get("debug.gmem.dump_every_n_frames", value, sizeof(value), "30");
      if (value != NULL)
         s_limit = atoi(value);

      s_count = s_limit;   /* Trigger dump on this first swap */
   }

   s_count++;
   if (s_count >= s_limit)
   {
      gmem_print_level(VCOS_LOG_INFO); /* Dump the gmem status if info level is enabled */
      s_count = 0;
   }
}

/* See eglSwapbuffers. If preserve, then the new back buffer should be
 * initialized with the contents of the previous back buffer. */
static egl_swap_result_t swap_buffers(EGL_SURFACE_T *surface, bool preserve)
{
   EGL_WINDOW_SURFACE_T          *surf = (EGL_WINDOW_SURFACE_T *) surface;
   BEGL_DisplayInterface         *platform = &g_bcgPlatformData.displayInterface;

   if (surf->active_image)
   {
      v3d_scheduler_deps *out_deps = egl_surface_flush_rendering(surface);
      int fence = v3d_scheduler_create_fence(out_deps, V3D_SCHED_DEPS_COMPLETED);

      assert(platform->DisplaySurface);
      if (platform->DisplaySurface(platform->context, surf->native_window_state, surf->native_back_buffer, fence) != BEGL_Success)
         return EGL_SWAP_SWAPPED;

      KHRN_MEM_ASSIGN(surf->active_image, NULL);

      dump_gmem_status();
   }

   return dequeue_buffer(surf) ? EGL_SWAP_SWAPPED : EGL_SWAP_NO_MEMORY;

}

static void get_dimensions(EGL_SURFACE_T *surface, unsigned *width, unsigned *height)
{
   BEGL_DisplayInterface *platform = &g_bcgPlatformData.displayInterface;
   BEGL_WindowInfo       winInfo;

   if (platform->WindowGetInfo)
   {
      EGL_WINDOW_SURFACE_T *surf = (EGL_WINDOW_SURFACE_T *)surface;

      platform->WindowGetInfo(platform->context, surf->native_window_state, BEGL_WindowInfoWidth | BEGL_WindowInfoHeight, &winInfo);
      *width = winInfo.width;
      *height = winInfo.height;
   }
   else
   {
      *width = 0;
      *height = 0;
   }
}

/* Get the buffer to draw to */
static KHRN_IMAGE_T *get_back_buffer(const EGL_SURFACE_T *surface)
{
   EGL_WINDOW_SURFACE_T *surf = (EGL_WINDOW_SURFACE_T *) surface;

   if (surf->active_image == NULL)
      dequeue_buffer(surf);

   return surf->active_image;
}

static void delete_fn(EGL_SURFACE_T *surface)
{
   EGL_WINDOW_SURFACE_T    *surf = (EGL_WINDOW_SURFACE_T *) surface;
   BEGL_DisplayInterface   *platform = &g_bcgPlatformData.displayInterface;

   if (!surface)
      return;

   if (surf->native_window_state)
   {
      if (surf->native_back_buffer)
      {
         int fence =  -1;

         /* we need to cancel with a fence for already flushed operations  + original
          * fence when we dequeued the surface */
         if (surf->active_image)
         {
            const v3d_scheduler_deps   *deps = NULL;

            egl_context_gl_lock();

            KHRN_RES_INTERLOCK_T *res_i;
            res_i = khrn_image_get_res_interlock(surf->active_image);
            /* we should have flushed by now (when the surface stopped being current) */
            assert(khrn_interlock_get_actions(&res_i->interlock, NULL) == ACTION_NONE);
            deps = khrn_interlock_get_sync(&res_i->interlock, true);

            egl_context_gl_unlock();

            if (deps->n != 0)
               fence = v3d_scheduler_create_fence(deps, V3D_SCHED_DEPS_COMPLETED);

            /* release the image only after we used the deps, since deps is a
             * pointer inside the image */
            KHRN_MEM_ASSIGN(surf->active_image, NULL);
         }

         assert(platform->CancelSurface);
         platform->CancelSurface(platform->context, surf->native_window_state,
            surf->native_back_buffer, fence);
      }
      if (platform->WindowPlatformStateDestroy != NULL)
         platform->WindowPlatformStateDestroy(platform->context, surf->native_window_state);
   }

   assert(surf->active_image == NULL);

   egl_surface_base_destroy(surface);
   free(surface);
}

static EGLSurface egl_create_window_surface_impl(EGLDisplay dpy, EGLConfig config,
      EGLNativeWindowType win, const void *attrib_list,
      EGL_AttribType attrib_type)
{
   EGLint                     error = EGL_BAD_ALLOC;
   EGL_WINDOW_SURFACE_T       *surface;
   EGLSurface                 ret = EGL_NO_SURFACE;
   BEGL_WindowInfo            winInfo;
   unsigned int               width, height;
   BEGL_DisplayInterface      *platform = &g_bcgPlatformData.displayInterface;

   memset(&winInfo, 0, sizeof(BEGL_WindowInfo));

   if (!egl_initialized(dpy, true))
      return EGL_NO_SURFACE;

   surface = calloc(1, sizeof(*surface));
   if (!surface)
      goto end;

   /* Even though the config will be checked for validity in egl_surface_base_init
    * we check it here first so that dEQP doesn't fail us. We'll return a different
    * error if we leave it until egl_surface_base_init is called. */
   if (!egl_config_is_valid(config))
   {
      error = EGL_BAD_CONFIG;
      goto end;
   }

   /* Validate the window surface - this is an opaque structure, so just check the pointer right now */
   if (win == NULL || win == (EGLNativeWindowType)0xFFFFFFFF)
   {
      error = EGL_BAD_NATIVE_WINDOW;
      goto end;
   }

   surface->base.fns = &fns;

   /* Let the platform attach it's own data to the native window if required */
   if (platform->WindowPlatformStateCreate != NULL)
      surface->native_window_state = platform->WindowPlatformStateCreate(platform->context, (void*)win);
   else
      surface->native_window_state = (void*)win;

   if (surface->native_window_state == NULL)
   {
      error = EGL_BAD_NATIVE_WINDOW;
      goto end;
   }

   /* Determine size of the underlying native window */
   get_dimensions(&surface->base, &width, &height);

   if (width == 0 || height == 0)
   {
      error = EGL_BAD_MATCH;
      goto end;
   }

   surface->base.type = EGL_SURFACE_TYPE_NATIVE_WINDOW;

   error = egl_surface_base_init(&surface->base, &fns, config, attrib_list,
         attrib_type, width, height, win, NULL);
   if (error != EGL_SUCCESS)
      goto end;

   ret = egl_map_surface((EGL_SURFACE_T *) surface);
   if (!ret || ret == EGL_NO_SURFACE)
      goto end;

   error = EGL_SUCCESS;
end:
   if (error != EGL_SUCCESS)
   {
      egl_unmap_surface(ret);
      delete_fn((EGL_SURFACE_T *) surface);
      ret = EGL_NO_SURFACE;
   }
   egl_thread_set_error(error);
   return ret;
}

EGLAPI EGLSurface EGLAPIENTRY eglCreateWindowSurface(EGLDisplay dpy,
      EGLConfig config, EGLNativeWindowType win, const EGLint *attrib_list)
{
   return egl_create_window_surface_impl(dpy, config, win, attrib_list,
         attrib_EGLint);
}

EGLAPI EGLSurface EGLAPIENTRY eglCreatePlatformWindowSurface(EGLDisplay dpy,
      EGLConfig config, void *native_window, const EGLAttrib *attrib_list)
{
   return egl_create_window_surface_impl(dpy, config,
         (EGLNativeWindowType)native_window, attrib_list, attrib_EGLAttrib);
}

EGLAPI EGLSurface EGLAPIENTRY eglCreatePlatformWindowSurfaceEXT(EGLDisplay dpy,
      EGLConfig config, void *native_window, const EGLint *attrib_list)
{
   return egl_create_window_surface_impl(dpy, config,
         (EGLNativeWindowType)native_window, attrib_list, attrib_EGLint);
}

/* Set the swap interval (see eglSwapInterval). It's up to the implementation to clamp
 * interval to whatever range it can support. */
static void swap_interval(EGL_SURFACE_T *surface, int interval)
{
   EGL_WINDOW_SURFACE_T          *surf = (EGL_WINDOW_SURFACE_T *)surface;
   BEGL_DisplayInterface         *platform = &g_bcgPlatformData.displayInterface;

   if (platform->SetSwapInterval)
      platform->SetSwapInterval(platform->context, surf->native_window_state, interval);
}

static bool get_attrib(const EGL_SURFACE_T *surface, EGLint attrib,
      EGLAttribKHR *value)
{
   return egl_surface_base_get_attrib(surface, attrib, value);
}

static EGLint set_attrib(EGL_SURFACE_T *surface, EGLint attrib,
      EGLAttribKHR value)
{
   return egl_surface_base_set_attrib(surface, attrib, value);
}


static EGL_SURFACE_METHODS_T fns =
{
   get_back_buffer,
   swap_buffers,
   swap_interval,
   get_dimensions,
   get_attrib,
   set_attrib,
   delete_fn
};

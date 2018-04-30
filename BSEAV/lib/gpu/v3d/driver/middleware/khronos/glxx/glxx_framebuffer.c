/******************************************************************************
 *  Copyright (C) 2017 Broadcom. The term "Broadcom" refers to Broadcom Limited and/or its subsidiaries.
 ******************************************************************************/
#include "interface/khronos/common/khrn_int_common.h"

#include "middleware/khronos/glxx/glxx_framebuffer.h"
#include "middleware/khronos/glxx/glxx_renderbuffer.h"

#include "middleware/khronos/glxx/glxx_texture.h"

#include "middleware/khronos/common/khrn_mem.h"

static void attachment_info_init(GLXX_ATTACHMENT_INFO_T *attachment)
{
   assert(attachment);

   /*
      we never re-init a program structure, so this
      should be shiny and new
   */

   assert(attachment->object == NULL);

   attachment->type = GL_NONE;
   attachment->target = 0;
   attachment->level = 0;
}

void glxx_framebuffer_init(GLXX_FRAMEBUFFER_T *framebuffer, int32_t name)
{
   assert(framebuffer);

   framebuffer->name = name;

   attachment_info_init(&framebuffer->attachments.color);
   attachment_info_init(&framebuffer->attachments.depth);
   attachment_info_init(&framebuffer->attachments.stencil);
}

static void attachment_info_term(GLXX_ATTACHMENT_INFO_T *attachment)
{
   assert(attachment);

   // If it is a texture 2D and it is a multisample attachment
   if ((attachment->target == GL_TEXTURE_2D) && (attachment->samples != 0))
   {
      // Delete the multisample buffer allocated when attached
      GLXX_TEXTURE_T *texture = attachment->object;
      if ((texture) && (texture->ms_image != NULL))
         KHRN_MEM_ASSIGN(texture->ms_image, NULL);
   }
   KHRN_MEM_ASSIGN(attachment->object, NULL);
}

void glxx_framebuffer_term(void *p)
{
   GLXX_FRAMEBUFFER_T *framebuffer = p;
   attachment_info_term(&framebuffer->attachments.color);
   attachment_info_term(&framebuffer->attachments.depth);
   attachment_info_term(&framebuffer->attachments.stencil);
}

vcos_static_assert(GL_TEXTURE_CUBE_MAP_NEGATIVE_X == GL_TEXTURE_CUBE_MAP_POSITIVE_X + 1);
vcos_static_assert(GL_TEXTURE_CUBE_MAP_POSITIVE_Y == GL_TEXTURE_CUBE_MAP_NEGATIVE_X + 1);
vcos_static_assert(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y == GL_TEXTURE_CUBE_MAP_POSITIVE_Y + 1);
vcos_static_assert(GL_TEXTURE_CUBE_MAP_POSITIVE_Z == GL_TEXTURE_CUBE_MAP_NEGATIVE_Y + 1);
vcos_static_assert(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z == GL_TEXTURE_CUBE_MAP_POSITIVE_Z + 1);

KHRN_IMAGE_T *glxx_attachment_info_get_images(GLXX_ATTACHMENT_INFO_T *attachment, KHRN_IMAGE_T **ms_image)
{
   KHRN_IMAGE_T *result = NULL;

   switch (attachment->type) {
   case GL_NONE:
      result = NULL;
      break;
   case GL_TEXTURE:
   {
      GLXX_TEXTURE_T *texture = attachment->object;

      switch (attachment->target) {
      case GL_TEXTURE_2D:
         result = glxx_texture_share_mipmap(texture, TEXTURE_BUFFER_TWOD, attachment->level);
         if (ms_image)
            *ms_image = texture->ms_image;
         break;
      case GL_TEXTURE_CUBE_MAP_POSITIVE_X:
      case GL_TEXTURE_CUBE_MAP_NEGATIVE_X:
      case GL_TEXTURE_CUBE_MAP_POSITIVE_Y:
      case GL_TEXTURE_CUBE_MAP_NEGATIVE_Y:
      case GL_TEXTURE_CUBE_MAP_POSITIVE_Z:
      case GL_TEXTURE_CUBE_MAP_NEGATIVE_Z:
         assert(attachment->level == 0);

         result = glxx_texture_share_mipmap(texture, TEXTURE_BUFFER_POSITIVE_X + attachment->target - GL_TEXTURE_CUBE_MAP_POSITIVE_X, attachment->level);
         break;
      default:
         UNREACHABLE();
      }
      break;
   }
   case GL_RENDERBUFFER:
   {
      GLXX_RENDERBUFFER_T *renderbuffer = attachment->object;
      result = renderbuffer->storage;
      if (ms_image)
         *ms_image = renderbuffer->ms_storage;
      break;
   }
   default:
      UNREACHABLE();
   }

   return result;
}

bool glxx_framebuffer_hw_support(KHRN_IMAGE_FORMAT_T format)
{
#ifdef BIG_ENDIAN_CPU
   // one of the suppored formats
   return ((format == RGBA_8888_TF) ||
      (format == RGBX_8888_TF) ||
#else
   return ((format == ABGR_8888_TF) ||
      (format == XBGR_8888_TF) ||
#endif
      (format == RGB_565_TF) ||
      (format == DEPTH_32_TLBD) ||
      (format == DEPTH_COL_64_TLBD));
}

/*
   The framebuffer attachment point attachment is said to be framebuffer attachment complete if the value
   of FRAMEBUFFER ATTACHMENT OBJECT TYPE for attachment is NONE (i.e., no image is attached), or if all
   of the following conditions are true:

   - <image> is a component of an existing object with the name specified by FRAMEBUFFER ATTACHMENT -
     OBJECT NAME, and of the type specified by FRAMEBUFFER ATTACHMENT OBJECT TYPE.
   - The width and height of <image> must be non-zero.
   - If attachment is COLOR ATTACHMENT0, then image must have a color-renderable internal format.
   - If attachment is DEPTH ATTACHMENT, then image must have a depth-renderable internal format.
   - If attachment is STENCIL ATTACHMENT, then image must have a stencil-renderable internal format.

   The framebuffer object target is said to be framebuffer complete if it is the window-system-provided
   framebuffer, or if all the following conditons are true:

   - All framebuffer attachment points are framebuffer attachment complete. FRAMEBUFFER INCOMPLETE ATTACHMENT
   - There is at least one image attached to the framebuffer. FRAMEBUFFER INCOMPLETE MISSING ATTACHMENT
   - All attached images have the same width and height. FRAMEBUFFER INCOMPLETE DIMENSIONS
   - The combination of internal formats of the attached images does not violate an implementationdependent
     set of restrictions. FRAMEBUFFER UNSUPPORTED

   The enums in bold after each clause of the framebuffer completeness rules specifies the return value of
   CheckFramebufferStatus that is generated when that clause is violated. If more than one clause is violated,
   it is implementation-dependent as to exactly which enum will be returned by CheckFramebufferStatus.
*/

typedef enum
{
   ATTACHMENT_MISSING,                    // Attachment type is NONE, therefore complete
   ATTACHMENT_BROKEN,                     // Attachment is incomplete
   ATTACHMENT_COLOR,                      // Attachment type is COLOR and is complete
   ATTACHMENT_DEPTH16,                    // Attachment type is DEPTH, is complete and the image is 16bpp
   ATTACHMENT_DEPTH24,                    // Attachment type is DEPTH, is complete and the image is 24bpp
   ATTACHMENT_STENCIL,                    // Attachment type is STENCIL and is complete
   ATTACHMENT_DEPTH_STENCIL,              // Attachment type is DEPTH_STENCIL and is complete
   ATTACHMENT_UNSUPPORTED = -1            // Attachment type is valid but rendering is not supported
} ATTACHMENT_STATUS_T;

static ATTACHMENT_STATUS_T attachment_get_status(GLXX_ATTACHMENT_INFO_T *attachment,
   uint32_t *width, uint32_t *height, uint32_t *samples, bool *secure)
{
   switch (attachment->type) {
   case GL_NONE:
      return ATTACHMENT_MISSING;
   case GL_RENDERBUFFER:
   {
      GLXX_RENDERBUFFER_T *renderbuffer = attachment->object;
      ATTACHMENT_STATUS_T result = ATTACHMENT_BROKEN;

      // Multisample?
      *samples = renderbuffer->samples;

      switch (renderbuffer->type) {
      case RB_NEW_T:
         result = ATTACHMENT_BROKEN; break;
      case RB_COLOR_T:
         result = ATTACHMENT_COLOR; break;
      case RB_DEPTH16_T:
         result = ATTACHMENT_DEPTH16; break;
      case RB_DEPTH24_T:
         result = ATTACHMENT_DEPTH24; break;
      case RB_STENCIL_T:
         result = ATTACHMENT_STENCIL; break;
      case RB_DEPTH24_STENCIL8_T:
         result = ATTACHMENT_DEPTH_STENCIL; break;
      default:
         UNREACHABLE();
      }
      if (((renderbuffer->storage == NULL) && (*samples == 0)) ||     // non-multisample and invalid handle for non-multisample
          ((renderbuffer->ms_storage == NULL) && (*samples != 0)))    // multisample and invalid handle for multisample
      {
         *width = 0;
         *height = 0;
      } else {
         KHRN_IMAGE_FORMAT_T format;
         KHRN_IMAGE_T *image;
         if ((*samples != 0) && (result != ATTACHMENT_COLOR))   // If it is multisample and depth/stencil buffer
         {
            image = renderbuffer->ms_storage;
            *width = image->width / 2;
            *height = image->height / 2;
            *secure = image->secure;
            format = image->format;
         }
         else
         {  // if a non-multisample or a colour attachment
            // (colour attachments have a resolve buffer but not depth/stencil attachment)
            // For colour attachment we take the resolved version as it has the correct colour format
            // which is checked by glxx_framebuffer_hw_support few lines below
            image = renderbuffer->storage;
            *width = image->width;
            *height = image->height;
            *secure = image->secure;
            format = image->format;
         }

         format = image->format;
         if (!glxx_framebuffer_hw_support(format))
            result = ATTACHMENT_UNSUPPORTED;
      }
      if (*width == 0 || *height == 0)
         result = ATTACHMENT_BROKEN;
      return result;
   }
   case GL_TEXTURE:
   {
      KHRN_IMAGE_T *image = glxx_attachment_info_get_images(attachment, NULL);
      ATTACHMENT_STATUS_T result = ATTACHMENT_BROKEN;
      if (image == NULL) {
         *width = 0;
         *height = 0;
         *secure = false;
         *samples = 0;
      } else {
         KHRN_IMAGE_FORMAT_T format = image->format;
         switch (format)
         {
#ifndef BIG_ENDIAN_CPU
         case ABGR_8888_TF:
         case XBGR_8888_TF:
#if GL_EXT_texture_format_BGRA8888
         case ARGB_8888_TF:
#endif
#endif
#ifdef BIG_ENDIAN_CPU
         case RGBA_8888_TF:
         case RGBX_8888_TF:
#if GL_EXT_texture_format_BGRA8888
         case BGRA_8888_TF:
#endif
#endif
         case RGB_565_TF:
         case ABGR_8888_LT:
         case XBGR_8888_LT:
         case RGB_565_LT:
         case ABGR_8888_RSO:
         case ARGB_8888_RSO:
         case XBGR_8888_RSO:
         case XRGB_8888_RSO:
         case RGB_565_RSO:
            result = ATTACHMENT_COLOR;
            break;
         case RGBA_4444_TF:
         case RGBA_5551_TF:
         case RGBA_4444_LT:
         case RGBA_5551_LT:
            result = ATTACHMENT_UNSUPPORTED;
            break;
         default:  //other texture formats or IMAGE_FORMAT_INVALID
            result = ATTACHMENT_BROKEN;
         }
         *width = image->width;
         *height = image->height;
         *secure = image->secure;
         *samples = attachment->samples;
      }
      if (*width == 0 || *height == 0)
         result = ATTACHMENT_BROKEN;
      return result;
   }
   default:
      UNREACHABLE();
      return ATTACHMENT_BROKEN;
   }
}

GLenum glxx_framebuffer_check_status(GLXX_FRAMEBUFFER_T *framebuffer)
{
   ATTACHMENT_STATUS_T ca, da, sa;
   bool csecure = false, dsecure = false, ssecure = false;
   //          width,   height,  sample
   uint32_t    cw = 0,  ch = 0,  cs = 0;
   uint32_t    dw = 0,  dh = 0,  ds = 0;
   uint32_t    sw = 0,  sh = 0,  ss = 0;
   GLenum result = GL_FRAMEBUFFER_COMPLETE;

   assert(framebuffer);

   // color/depth/stencil attachment/width/height
   // If attachment is NONE or BROKEN, width and height should be ignored

   ca = attachment_get_status(&framebuffer->attachments.color, &cw, &ch, &cs, &csecure);
   da = attachment_get_status(&framebuffer->attachments.depth, &dw, &dh, &ds, &dsecure);
   sa = attachment_get_status(&framebuffer->attachments.stencil, &sw, &sh, &ss, &ssecure);

   if (ca == ATTACHMENT_MISSING && da == ATTACHMENT_MISSING && sa == ATTACHMENT_MISSING)
      result = GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT;
   else if (ca == ATTACHMENT_UNSUPPORTED || da == ATTACHMENT_UNSUPPORTED || sa == ATTACHMENT_UNSUPPORTED)
      result = GL_FRAMEBUFFER_UNSUPPORTED;
   else {
      if (ca == ATTACHMENT_MISSING)
         result = GL_FRAMEBUFFER_UNSUPPORTED;
      else if (da == ATTACHMENT_DEPTH16 && sa != ATTACHMENT_MISSING)
         result = GL_FRAMEBUFFER_UNSUPPORTED;
      else {
         bool color_complete = (ca == ATTACHMENT_MISSING || ca == ATTACHMENT_COLOR);
         bool depth_complete = (da == ATTACHMENT_MISSING || da == ATTACHMENT_DEPTH16 ||
                                da == ATTACHMENT_DEPTH24 || da == ATTACHMENT_DEPTH_STENCIL);
         bool stencil_complete = (sa == ATTACHMENT_MISSING || sa == ATTACHMENT_STENCIL ||
                                  sa == ATTACHMENT_DEPTH_STENCIL);

         if (!color_complete || !depth_complete || !stencil_complete)
            result = GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT;
         else {
            /*
               at this point we know we have

               - a complete color buffer
               - a complete depth buffer (if present)
               - a complete stencil buffer (if present)

               we need to check whether we have a depth buffer, and if so whether it has the same size as the color buffer
               similarly for stencil

               If it is a multisample FBO we need to check that the number of sample is the same for all the attachments
            */

            if (da != ATTACHMENT_MISSING && (cw != dw || ch != dh))
               result = GL_FRAMEBUFFER_INCOMPLETE_DIMENSIONS;
            else if (sa != ATTACHMENT_MISSING && (cw != sw || ch != sh))
               result = GL_FRAMEBUFFER_INCOMPLETE_DIMENSIONS;

            if (da != ATTACHMENT_MISSING && (csecure != dsecure))
               result = GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT;
            else if (sa != ATTACHMENT_MISSING && (csecure != ssecure))
               result = GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT;

            /* check that the sample depths match for all valid attachments */
            /* color is always valid here, so this is the 'base' format, so check
               this against valid depth/stencil */
            if ((cs != ((da != ATTACHMENT_MISSING) ? ds : cs)) ||
                (cs != ((sa != ATTACHMENT_MISSING) ? ss : cs)))
            {
               result = GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE_EXT;
            }
         }
      }
   }

   return result;
}

/*=============================================================================
Copyright (c) 2014 Broadcom Europe Limited.
All rights reserved.

Project  :  helpers
Module   :

FILE DESCRIPTION
=============================================================================*/

#include "helpers/gfx/gfx_lfmt_translate_gl.h"

#include "GLES3/gl31.h"
#include "GLES2/gl2ext.h"
#include "GLES3/gl3ext_brcm.h"

/* Note: nothing in this file has anything to do with how a particular GL
   implementation stores these textures internally. Try
   khronos/glxx/glxx_texture_utils for that. */

/* TODO some conversions don't have anything to do with lfmt - should they be moved to
 * another module? */

static bool is_subset_of(gfx_lfmt_translate_gl_ext_t a, gfx_lfmt_translate_gl_ext_t b)
{
   return (a & b) == a;
}

/*===========================================================================*/
/*
   Bijective mapping of GL "external format" <-> lfmt (format only).

   By "external format" I mean the format of the client data supplied to functions
   like glTexImage. This can be determined from "format" + "type" (+
   "internalformat" for sRGB-ness only - a spec oddity)
*/

typedef struct {
   GLenum format;
   GLenum type;
   GFX_LFMT_T src_lfmt;
} FORMAT_TYPE_LFMT_T;

static const FORMAT_TYPE_LFMT_T gl_to_lfmt_map[] = {
   /* format and type from GL ES spec 3.0.2, Table 3.2 "Valid combinations of
      format, type, and sized internalformat." */
   {GL_RGBA,                 GL_UNSIGNED_BYTE,               GFX_LFMT_R8_G8_B8_A8_UNORM},
   {GL_RGBA,                 GL_BYTE,                        GFX_LFMT_R8_G8_B8_A8_SNORM},
   {GL_RGBA,                 GL_UNSIGNED_SHORT_4_4_4_4,      GFX_LFMT_A4B4G4R4_UNORM},
   {GL_RGBA,                 GL_UNSIGNED_SHORT_5_5_5_1,      GFX_LFMT_A1B5G5R5_UNORM},
   {GL_RGBA,                 GL_UNSIGNED_INT_2_10_10_10_REV, GFX_LFMT_R10G10B10A2_UNORM},
   {GL_RGBA,                 GL_HALF_FLOAT,                  GFX_LFMT_R16_G16_B16_A16_FLOAT},
   {GL_RGBA,                 GL_FLOAT,                       GFX_LFMT_R32_G32_B32_A32_FLOAT},
   {GL_RGBA_INTEGER,         GL_UNSIGNED_BYTE,               GFX_LFMT_R8_G8_B8_A8_UINT},
   {GL_RGBA_INTEGER,         GL_BYTE,                        GFX_LFMT_R8_G8_B8_A8_INT},
   {GL_RGBA_INTEGER,         GL_UNSIGNED_SHORT,              GFX_LFMT_R16_G16_B16_A16_UINT},
   {GL_RGBA_INTEGER,         GL_SHORT,                       GFX_LFMT_R16_G16_B16_A16_INT},
   {GL_RGBA_INTEGER,         GL_UNSIGNED_INT,                GFX_LFMT_R32_G32_B32_A32_UINT},
   {GL_RGBA_INTEGER,         GL_INT,                         GFX_LFMT_R32_G32_B32_A32_INT},
   {GL_RGBA_INTEGER,         GL_UNSIGNED_INT_2_10_10_10_REV, GFX_LFMT_R10G10B10A2_UINT},
   {GL_RGB,                  GL_UNSIGNED_BYTE,               GFX_LFMT_R8_G8_B8_UNORM},
   {GL_RGB,                  GL_BYTE,                        GFX_LFMT_R8_G8_B8_SNORM},
   {GL_RGB,                  GL_UNSIGNED_SHORT_5_6_5,        GFX_LFMT_B5G6R5_UNORM},
   {GL_RGB,                  GL_UNSIGNED_INT_10F_11F_11F_REV,GFX_LFMT_R11G11B10_UFLOAT},
   {GL_RGB,                  GL_UNSIGNED_INT_5_9_9_9_REV,    GFX_LFMT_R9G9B9SHAREDEXP5_UFLOAT},
   {GL_RGB,                  GL_HALF_FLOAT,                  GFX_LFMT_R16_G16_B16_FLOAT},
   {GL_RGB,                  GL_FLOAT,                       GFX_LFMT_R32_G32_B32_FLOAT},
   {GL_RGB_INTEGER,          GL_UNSIGNED_BYTE,               GFX_LFMT_R8_G8_B8_UINT},
   {GL_RGB_INTEGER,          GL_BYTE,                        GFX_LFMT_R8_G8_B8_INT},
   {GL_RGB_INTEGER,          GL_UNSIGNED_SHORT,              GFX_LFMT_R16_G16_B16_UINT},
   {GL_RGB_INTEGER,          GL_SHORT,                       GFX_LFMT_R16_G16_B16_INT},
   {GL_RGB_INTEGER,          GL_UNSIGNED_INT,                GFX_LFMT_R32_G32_B32_UINT},
   {GL_RGB_INTEGER,          GL_INT,                         GFX_LFMT_R32_G32_B32_INT},
   {GL_RG,                   GL_UNSIGNED_BYTE,               GFX_LFMT_R8_G8_UNORM},
   {GL_RG,                   GL_BYTE,                        GFX_LFMT_R8_G8_SNORM},
   {GL_RG,                   GL_HALF_FLOAT,                  GFX_LFMT_R16_G16_FLOAT},
   {GL_RG,                   GL_FLOAT,                       GFX_LFMT_R32_G32_FLOAT},
   {GL_RG_INTEGER,           GL_UNSIGNED_BYTE,               GFX_LFMT_R8_G8_UINT},
   {GL_RG_INTEGER,           GL_BYTE,                        GFX_LFMT_R8_G8_INT},
   {GL_RG_INTEGER,           GL_UNSIGNED_SHORT,              GFX_LFMT_R16_G16_UINT},
   {GL_RG_INTEGER,           GL_SHORT,                       GFX_LFMT_R16_G16_INT},
   {GL_RG_INTEGER,           GL_UNSIGNED_INT,                GFX_LFMT_R32_G32_UINT},
   {GL_RG_INTEGER,           GL_INT,                         GFX_LFMT_R32_G32_INT},
   {GL_RED,                  GL_UNSIGNED_BYTE,               GFX_LFMT_R8_UNORM},
   {GL_RED,                  GL_BYTE,                        GFX_LFMT_R8_SNORM},
   {GL_RED,                  GL_HALF_FLOAT,                  GFX_LFMT_R16_FLOAT},
   {GL_RED,                  GL_FLOAT,                       GFX_LFMT_R32_FLOAT},
   {GL_RED_INTEGER,          GL_UNSIGNED_BYTE,               GFX_LFMT_R8_UINT},
   {GL_RED_INTEGER,          GL_BYTE,                        GFX_LFMT_R8_INT},
   {GL_RED_INTEGER,          GL_UNSIGNED_SHORT,              GFX_LFMT_R16_UINT},
   {GL_RED_INTEGER,          GL_SHORT,                       GFX_LFMT_R16_INT},
   {GL_RED_INTEGER,          GL_UNSIGNED_INT,                GFX_LFMT_R32_UINT},
   {GL_RED_INTEGER,          GL_INT,                         GFX_LFMT_R32_INT},
   {GL_DEPTH_COMPONENT,      GL_UNSIGNED_SHORT,              GFX_LFMT_D16_UNORM},
   {GL_DEPTH_COMPONENT,      GL_UNSIGNED_INT,                GFX_LFMT_D32_UNORM},
   {GL_DEPTH_COMPONENT,      GL_FLOAT,                       GFX_LFMT_D32_FLOAT},
   {GL_DEPTH_STENCIL,        GL_UNSIGNED_INT_24_8,           GFX_LFMT_S8D24_UINT_UNORM},
   {GL_DEPTH_STENCIL,        GL_FLOAT_32_UNSIGNED_INT_24_8_REV,GFX_LFMT_D32_S8X24_FLOAT_UINT},

#if GL_BRCM_texture_norm16
   {GL_RED,                  GL_UNSIGNED_SHORT,              GFX_LFMT_R16_UNORM},
   {GL_RG,                   GL_UNSIGNED_SHORT,              GFX_LFMT_R16_G16_UNORM},
   {GL_RGBA,                 GL_UNSIGNED_SHORT,              GFX_LFMT_R16_G16_B16_A16_UNORM},
   {GL_RED,                  GL_SHORT,                       GFX_LFMT_R16_SNORM},
   {GL_RG,                   GL_SHORT,                       GFX_LFMT_R16_G16_SNORM},
   {GL_RGBA,                 GL_SHORT,                       GFX_LFMT_R16_G16_B16_A16_SNORM},
#endif

   /* GL ES spec 3.0.2, Table 3.3 "Valid combinations of format, type, and unsized
      internalformat." (overlaps with above) */
   {GL_LUMINANCE_ALPHA,      GL_UNSIGNED_BYTE,               GFX_LFMT_L8_A8_UNORM},
   {GL_LUMINANCE,            GL_UNSIGNED_BYTE,               GFX_LFMT_L8_UNORM},
   {GL_ALPHA,                GL_UNSIGNED_BYTE,               GFX_LFMT_A8_UNORM},

   /* OES_texture_stencil8 */
   {GL_STENCIL_INDEX,        GL_UNSIGNED_BYTE,               GFX_LFMT_S8_UINT},

#if GL_EXT_texture_format_BGRA8888
   {GL_BGRA_EXT,             GL_UNSIGNED_BYTE,               GFX_LFMT_B8_G8_R8_A8_UNORM},
#endif
};

static const FORMAT_TYPE_LFMT_T gl_to_lfmt_map_srgb[] = {
   {GL_RGBA,   GL_UNSIGNED_BYTE, GFX_LFMT_R8_G8_B8_A8_SRGB_SRGB_SRGB_UNORM},
   {GL_RGB,    GL_UNSIGNED_BYTE, GFX_LFMT_R8_G8_B8_SRGB},
   {GL_RG,     GL_UNSIGNED_BYTE, GFX_LFMT_R8_G8_SRGB},
   {GL_RED,    GL_UNSIGNED_BYTE, GFX_LFMT_R8_SRGB}};

static bool is_internalformat_srgb(GLenum internalformat)
{
   switch (internalformat) {
   case GL_SRGB8_ALPHA8:
   case GL_SRGB8:
   case GL_SRG8_EXT:
   case GL_SR8_EXT:
      return true;
   default:
      return false;
   }
}

GFX_LFMT_T gfx_lfmt_from_externalformat(GLenum format, GLenum type, GLenum internalformat)
{
   return gfx_lfmt_from_format_type(format, type,
      is_internalformat_srgb(internalformat));
}

GFX_LFMT_T gfx_lfmt_from_format_type(GLenum format, GLenum type, bool is_dst_srgb)
{
   const FORMAT_TYPE_LFMT_T *map = is_dst_srgb ? gl_to_lfmt_map_srgb : gl_to_lfmt_map;
   size_t map_count = is_dst_srgb ? vcos_countof(gl_to_lfmt_map_srgb) : vcos_countof(gl_to_lfmt_map);

   for (size_t i=0; i<map_count; ++i)
   {
      if (map[i].format == format && map[i].type == type)
         return map[i].src_lfmt;
   }

   unreachable();
   return GFX_LFMT_NONE;
}

void gfx_lfmt_to_format_type_maybe(GLenum *format, GLenum *type, GFX_LFMT_T lfmt)
{
   GFX_LFMT_T fmt = gfx_lfmt_fmt(lfmt);
   unsigned int i;

   *format = GL_NONE;
   *type = GL_NONE;

   /* format+type have no notion of srgb */
   fmt = gfx_lfmt_srgb_to_unorm(fmt);

   for (i = 0; i != vcos_countof(gl_to_lfmt_map); ++i) {
      FORMAT_TYPE_LFMT_T entry = gl_to_lfmt_map[i];
      if (entry.src_lfmt == fmt) {
         *format = entry.format; *type = entry.type;
         break;
      }
   }
}

void gfx_lfmt_to_format_type(GLenum *format, GLenum *type, GFX_LFMT_T lfmt)
{
   gfx_lfmt_to_format_type_maybe(format, type, lfmt);
   assert((*format != GL_NONE) && (*type != GL_NONE));
}


/*===========================================================================*/
/*
   map sized internalformat -> lfmt ("api fmt" - format only).

   Although an lfmt is primarily used to describe the precise arrangement of
   pixel data in memory, this is not the intention here. Instead, it is used to
   give a higher-level description of what data an interal image exposes to a
   higher level API (like OpenGL or EGL).

   Each internalformat maps to one lfmt (no splitting into planes) and it has
   no X channels, if possible (sometimes an X is necessary to pad up to word
   size, e.g. D24X8). The resulting lfmt is almost the same as that of the
   "natural" external format one would use to upload to a texture of this
   internalformat, but there is at least one special case where that is not an
   option: GL_DEPTH_COMPONENT24.
*/

typedef struct {
   gfx_lfmt_translate_gl_ext_t required_exts; /* Entry is valid iff all of these extensions are enabled */
   GLenum sized_internalformat;
   GFX_LFMT_T lfmt;
} SIZED_INTERNALFORMAT_LFMT_T;

static const SIZED_INTERNALFORMAT_LFMT_T sized_internalformat_to_lfmt_map[] = {
   /* GL ES spec 3.0.2, Table 3.2 "Valid combinations of format, type, and
      sized internalformat." */
   {0,                                    GL_R8,                  GFX_LFMT_R8_UNORM},
   {0,                                    GL_R8_SNORM,            GFX_LFMT_R8_SNORM},
   {0,                                    GL_RG8,                 GFX_LFMT_R8_G8_UNORM},
   {0,                                    GL_RG8_SNORM,           GFX_LFMT_R8_G8_SNORM},
   {0,                                    GL_RGB8,                GFX_LFMT_R8_G8_B8_UNORM},
   {0,                                    GL_RGB8_SNORM,          GFX_LFMT_R8_G8_B8_SNORM},
   {0,                                    GL_RGB565,              GFX_LFMT_B5G6R5_UNORM},
   {0,                                    GL_RGBA4,               GFX_LFMT_A4B4G4R4_UNORM},
   {0,                                    GL_RGB5_A1,             GFX_LFMT_A1B5G5R5_UNORM},
   {0,                                    GL_RGBA8,               GFX_LFMT_R8_G8_B8_A8_UNORM},
   {0,                                    GL_RGBA8_SNORM,         GFX_LFMT_R8_G8_B8_A8_SNORM},
   {0,                                    GL_RGB10_A2,            GFX_LFMT_R10G10B10A2_UNORM},
   {0,                                    GL_RGB10_A2UI,          GFX_LFMT_R10G10B10A2_UINT},
   {GFX_LFMT_TRANSLATE_GL_EXT_SR8_SRG8,   GL_SR8_EXT,             GFX_LFMT_R8_SRGB},
   {GFX_LFMT_TRANSLATE_GL_EXT_SR8_SRG8,   GL_SRG8_EXT,            GFX_LFMT_R8_G8_SRGB},
   {0,                                    GL_SRGB8,               GFX_LFMT_R8_G8_B8_SRGB},
   {0,                                    GL_SRGB8_ALPHA8,        GFX_LFMT_R8_G8_B8_A8_SRGB_SRGB_SRGB_UNORM},
   {0,                                    GL_R16F,                GFX_LFMT_R16_FLOAT},
   {0,                                    GL_RG16F,               GFX_LFMT_R16_G16_FLOAT},
   {0,                                    GL_RGB16F,              GFX_LFMT_R16_G16_B16_FLOAT},
   {0,                                    GL_RGBA16F,             GFX_LFMT_R16_G16_B16_A16_FLOAT},
   {0,                                    GL_R32F,                GFX_LFMT_R32_FLOAT},
   {0,                                    GL_RG32F,               GFX_LFMT_R32_G32_FLOAT},
   {0,                                    GL_RGB32F,              GFX_LFMT_R32_G32_B32_FLOAT},
   {0,                                    GL_RGBA32F,             GFX_LFMT_R32_G32_B32_A32_FLOAT},
   {0,                                    GL_R11F_G11F_B10F,      GFX_LFMT_R11G11B10_UFLOAT},
   {0,                                    GL_RGB9_E5,             GFX_LFMT_R9G9B9SHAREDEXP5_UFLOAT},
   {0,                                    GL_R8I,                 GFX_LFMT_R8_INT},
   {0,                                    GL_R8UI,                GFX_LFMT_R8_UINT},
   {0,                                    GL_R16I,                GFX_LFMT_R16_INT},
   {0,                                    GL_R16UI,               GFX_LFMT_R16_UINT},
   {0,                                    GL_R32I,                GFX_LFMT_R32_INT},
   {0,                                    GL_R32UI,               GFX_LFMT_R32_UINT},
   {0,                                    GL_RG8I,                GFX_LFMT_R8_G8_INT},
   {0,                                    GL_RG8UI,               GFX_LFMT_R8_G8_UINT},
   {0,                                    GL_RG16I,               GFX_LFMT_R16_G16_INT},
   {0,                                    GL_RG16UI,              GFX_LFMT_R16_G16_UINT},
   {0,                                    GL_RG32I,               GFX_LFMT_R32_G32_INT},
   {0,                                    GL_RG32UI,              GFX_LFMT_R32_G32_UINT},
   {0,                                    GL_RGB8I,               GFX_LFMT_R8_G8_B8_INT},
   {0,                                    GL_RGB8UI,              GFX_LFMT_R8_G8_B8_UINT},
   {0,                                    GL_RGB16I,              GFX_LFMT_R16_G16_B16_INT},
   {0,                                    GL_RGB16UI,             GFX_LFMT_R16_G16_B16_UINT},
   {0,                                    GL_RGB32I,              GFX_LFMT_R32_G32_B32_INT},
   {0,                                    GL_RGB32UI,             GFX_LFMT_R32_G32_B32_UINT},
   {0,                                    GL_RGBA8I,              GFX_LFMT_R8_G8_B8_A8_INT},
   {0,                                    GL_RGBA8UI,             GFX_LFMT_R8_G8_B8_A8_UINT},
   {0,                                    GL_RGBA16I,             GFX_LFMT_R16_G16_B16_A16_INT},
   {0,                                    GL_RGBA16UI,            GFX_LFMT_R16_G16_B16_A16_UINT},
   {0,                                    GL_RGBA32I,             GFX_LFMT_R32_G32_B32_A32_INT},
   {0,                                    GL_RGBA32UI,            GFX_LFMT_R32_G32_B32_A32_UINT},
   {0,                                    GL_DEPTH_COMPONENT16,   GFX_LFMT_D16_UNORM},
   {0,                                    GL_DEPTH_COMPONENT24,   GFX_LFMT_D24X8_UNORM},
   {0,                                    GL_DEPTH_COMPONENT32F,  GFX_LFMT_D32_FLOAT},
   {0,                                    GL_DEPTH24_STENCIL8,    GFX_LFMT_S8D24_UINT_UNORM},
   {0,                                    GL_DEPTH32F_STENCIL8,   GFX_LFMT_D32_S8X24_FLOAT_UINT},

#if GL_BRCM_texture_norm16
   {0,                                    GL_R16_BRCM,            GFX_LFMT_R16_UNORM},
   {0,                                    GL_RG16_BRCM,           GFX_LFMT_R16_G16_UNORM},
   {0,                                    GL_RGBA16_BRCM,         GFX_LFMT_R16_G16_B16_A16_UNORM},
   {0,                                    GL_R16_SNORM_BRCM,      GFX_LFMT_R16_SNORM},
   {0,                                    GL_RG16_SNORM_BRCM,     GFX_LFMT_R16_G16_SNORM},
   {0,                                    GL_RGBA16_SNORM_BRCM,   GFX_LFMT_R16_G16_B16_A16_SNORM},
#endif

   /* See GL ES spec 3.0.2 "Required Renderbuffer Formats" and OES_texture_stencil8 */
   {0,                                    GL_STENCIL_INDEX8,      GFX_LFMT_S8_UINT},
};


typedef struct {
   GLenum unsized_internalformat;
   GFX_LFMT_T lfmt;
} UNSIZED_INTERNALFORMAT_LFMT_T;

static const UNSIZED_INTERNALFORMAT_LFMT_T unsized_internalformat_to_lfmt_map[] = {
   /* GL ES spec 3.0.2, Table 3.3 "Valid combinations of format, type, and
   internalformat." */
   {                                      GL_RGBA,                GFX_LFMT_R8_G8_B8_A8_UNORM },
   {                                      GL_RGBA,                GFX_LFMT_A4B4G4R4_UNORM },
   {                                      GL_RGBA,                GFX_LFMT_A1B5G5R5_UNORM },
   {                                      GL_RGBA,                GFX_LFMT_A1B5G5R5_UNORM },
   {                                      GL_RGB,                 GFX_LFMT_R8_G8_B8_UNORM },
   {                                      GL_RGB,                 GFX_LFMT_B5G6R5_UNORM },
   {                                      GL_LUMINANCE_ALPHA,     GFX_LFMT_L8_A8_UNORM },
   {                                      GL_LUMINANCE,           GFX_LFMT_L8_UNORM },
   {                                      GL_ALPHA,               GFX_LFMT_A8_UNORM },

#if GL_EXT_texture_format_BGRA8888
   {                                      GL_BGRA_EXT,            GFX_LFMT_B8_G8_R8_A8_UNORM },
#endif

   /*
   * OES_packed_depth_stencil:
   * DEPTH_STENCIL_OES Accepted by the <format> parameter of TexImage2D and TexSubImage2D and by the
   <internalformat> parameter of TexImage2D:
   */
   {                                      GL_DEPTH_STENCIL,       GFX_LFMT_S8D24_UINT_UNORM },
};

/* return GFX_LFMT_NONE if not a sized internalformat. */
GFX_LFMT_T gfx_api_fmt_from_sized_internalformat_maybe(gfx_lfmt_translate_gl_ext_t exts, GLenum internalformat)
{
   GFX_LFMT_T lfmt = GFX_LFMT_NONE;
   size_t i;

   for (i = 0; i != vcos_countof(sized_internalformat_to_lfmt_map); ++i)
   {
      const SIZED_INTERNALFORMAT_LFMT_T *entry = &sized_internalformat_to_lfmt_map[i];
      if (is_subset_of(entry->required_exts, exts) && (entry->sized_internalformat == internalformat))
      {
         lfmt = entry->lfmt;
         break;
      }
   }

   return lfmt;
}

GLenum gfx_sized_internalformat_from_api_fmt_maybe(GFX_LFMT_T api_fmt)
{
   size_t i;

   for (i=0; i!=vcos_countof(sized_internalformat_to_lfmt_map); ++i)
   {
      SIZED_INTERNALFORMAT_LFMT_T entry = sized_internalformat_to_lfmt_map[i];
      if (entry.lfmt == api_fmt) return entry.sized_internalformat;
   }
   return GL_NONE;
}

GLenum gfx_unsized_internalformat_from_api_fmt_maybe(GFX_LFMT_T api_fmt)
{
   for (size_t i = 0; i != vcos_countof(unsized_internalformat_to_lfmt_map); ++i)
   {
      UNSIZED_INTERNALFORMAT_LFMT_T entry = unsized_internalformat_to_lfmt_map[i];
      if (entry.lfmt == api_fmt) return entry.unsized_internalformat;
   }
   return GL_NONE;
}

GLenum gfx_internalformat_from_api_fmt_maybe(GFX_LFMT_T api_fmt)
{
   GLenum internalfmt;
   internalfmt = gfx_sized_internalformat_from_api_fmt_maybe(api_fmt);
   if (internalfmt != GL_NONE)
      return internalfmt;

   internalfmt = gfx_unsized_internalformat_from_api_fmt_maybe(api_fmt);
   return internalfmt;
}

/* Don't call this function if this is a compressed api fmt */
GLenum gfx_internalformat_from_api_fmt(GFX_LFMT_T api_fmt)
{
   GLenum internalfmt;
   internalfmt = gfx_internalformat_from_api_fmt_maybe(api_fmt);
   assert(internalfmt != GL_NONE);
   return internalfmt;
}

GFX_LFMT_T gfx_api_fmt_from_sized_internalformat(gfx_lfmt_translate_gl_ext_t exts, GLenum internalformat)
{
   GFX_LFMT_T lfmt = gfx_api_fmt_from_sized_internalformat_maybe(exts, internalformat);
   assert(lfmt != GFX_LFMT_NONE);
   return lfmt;
}

/* sized or unsized internalformat -> api fmt */
GFX_LFMT_T gfx_api_fmt_from_internalformat(
   gfx_lfmt_translate_gl_ext_t exts,
   GLenum type /* type only needed for unsized internalformats */,
   GLenum internalformat)
{
   GFX_LFMT_T fmt;

   if (gfx_gl_is_unsized_internalformat(internalformat))
      /*
         GL ES spec 3.0.2, Table 3.3 "Valid combinations of format, type, and
         unsized internalformat". We set api fmt to external format, so re-use
         the external format -> fmt code. Notice that for all rows, format ==
         internalformat, so no need to pass format in here.
      */
      fmt = gfx_lfmt_from_externalformat(internalformat, type, internalformat);
   else
      fmt = gfx_api_fmt_from_sized_internalformat(exts, internalformat);

   return fmt;
}

bool gfx_gl_is_sized_internalformat(gfx_lfmt_translate_gl_ext_t exts, GLenum internalformat)
{
   return gfx_api_fmt_from_sized_internalformat_maybe(exts, internalformat) != GFX_LFMT_NONE;
}

bool gfx_gl_is_unsized_internalformat(GLenum internalformat)
{
   switch (internalformat)
   {
   /* GL ES spec 3.0.2, Table 3.3 "Valid combinations of format, type, and unsized
      internalformat." */
   case GL_RGBA:
   case GL_RGB:
   case GL_LUMINANCE_ALPHA:
   case GL_LUMINANCE:
   case GL_ALPHA:
#if GL_EXT_texture_format_BGRA8888
   case GL_BGRA_EXT:
#endif
   case GL_DEPTH_STENCIL:  /* OES_packed_depth_stencil */
      return true;
   default:
      return false;
   }
}

/*===========================================================================*/
/*
   compressed texture formats
*/

typedef struct {
   gfx_lfmt_translate_gl_ext_t required_exts; /* Entry is valid iff all of these extensions are enabled */
   GLenum internalformat;
   GFX_LFMT_T lfmt;
} COMPRESSED_FORMAT_LFMT_T;

static const COMPRESSED_FORMAT_LFMT_T gfx_compressed_format_lfmt_map[] =
{
   {0,                              GL_ETC1_RGB8_OES,                               GFX_LFMT_ETC1_RGB_UNORM},
   {0,                              GL_COMPRESSED_R11_EAC,                          GFX_LFMT_EAC_R_UNORM},
   {0,                              GL_COMPRESSED_SIGNED_R11_EAC,                   GFX_LFMT_EAC_R_SNORM},
   {0,                              GL_COMPRESSED_RG11_EAC,                         GFX_LFMT_EAC_EAC_RG_UNORM},
   {0,                              GL_COMPRESSED_SIGNED_RG11_EAC,                  GFX_LFMT_EAC_EAC_RG_SNORM},
   {0,                              GL_COMPRESSED_RGB8_ETC2,                        GFX_LFMT_ETC2_RGB_UNORM},
   {0,                              GL_COMPRESSED_SRGB8_ETC2,                       GFX_LFMT_ETC2_RGB_SRGB},
   {0,                              GL_COMPRESSED_RGB8_PUNCHTHROUGH_ALPHA1_ETC2,    GFX_LFMT_PUNCHTHROUGH_ETC2_RGBA_UNORM},
   {0,                              GL_COMPRESSED_SRGB8_PUNCHTHROUGH_ALPHA1_ETC2,   GFX_LFMT_PUNCHTHROUGH_ETC2_RGBA_SRGB_SRGB_SRGB_UNORM},
   {0,                              GL_COMPRESSED_RGBA8_ETC2_EAC,                   GFX_LFMT_ETC2_EAC_RGBA_UNORM},
   {0,                              GL_COMPRESSED_SRGB8_ALPHA8_ETC2_EAC,            GFX_LFMT_ETC2_EAC_RGBA_SRGB_SRGB_SRGB_UNORM},
   {0,                              GL_PALETTE4_RGB8_OES,                           GFX_LFMT_BASE_P4BE_R8G8B8   | GFX_LFMT_TYPE_UNORM | GFX_LFMT_CHANNELS_RGB  },
   {0,                              GL_PALETTE4_RGBA8_OES,                          GFX_LFMT_BASE_P4BE_R8G8B8A8 | GFX_LFMT_TYPE_UNORM | GFX_LFMT_CHANNELS_RGBA },
   {0,                              GL_PALETTE4_R5_G6_B5_OES,                       GFX_LFMT_BASE_P4BE_B5G6R5   | GFX_LFMT_TYPE_UNORM | GFX_LFMT_CHANNELS_RGB  },
   {0,                              GL_PALETTE4_RGBA4_OES,                          GFX_LFMT_BASE_P4BE_A4B4G4R4 | GFX_LFMT_TYPE_UNORM | GFX_LFMT_CHANNELS_RGBA },
   {0,                              GL_PALETTE4_RGB5_A1_OES,                        GFX_LFMT_BASE_P4BE_A1B5G5R5 | GFX_LFMT_TYPE_UNORM | GFX_LFMT_CHANNELS_RGBA },
   {0,                              GL_PALETTE8_RGB8_OES,                           GFX_LFMT_BASE_P8_R8G8B8     | GFX_LFMT_TYPE_UNORM | GFX_LFMT_CHANNELS_RGB  },
   {0,                              GL_PALETTE8_RGBA8_OES,                          GFX_LFMT_BASE_P8_R8G8B8A8   | GFX_LFMT_TYPE_UNORM | GFX_LFMT_CHANNELS_RGBA },
   {0,                              GL_PALETTE8_R5_G6_B5_OES,                       GFX_LFMT_BASE_P8_B5G6R5     | GFX_LFMT_TYPE_UNORM | GFX_LFMT_CHANNELS_RGB  },
   {0,                              GL_PALETTE8_RGBA4_OES,                          GFX_LFMT_BASE_P8_A4B4G4R4   | GFX_LFMT_TYPE_UNORM | GFX_LFMT_CHANNELS_RGBA },
   {0,                              GL_PALETTE8_RGB5_A1_OES,                        GFX_LFMT_BASE_P8_A1B5G5R5   | GFX_LFMT_TYPE_UNORM | GFX_LFMT_CHANNELS_RGBA },
   {GFX_LFMT_TRANSLATE_GL_EXT_ASTC, GL_COMPRESSED_RGBA_ASTC_4x4_KHR,                GFX_LFMT_ASTC4X4_RGBA_UNORM},
   {GFX_LFMT_TRANSLATE_GL_EXT_ASTC, GL_COMPRESSED_RGBA_ASTC_5x4_KHR,                GFX_LFMT_ASTC5X4_RGBA_UNORM},
   {GFX_LFMT_TRANSLATE_GL_EXT_ASTC, GL_COMPRESSED_RGBA_ASTC_5x5_KHR,                GFX_LFMT_ASTC5X5_RGBA_UNORM},
   {GFX_LFMT_TRANSLATE_GL_EXT_ASTC, GL_COMPRESSED_RGBA_ASTC_6x5_KHR,                GFX_LFMT_ASTC6X5_RGBA_UNORM},
   {GFX_LFMT_TRANSLATE_GL_EXT_ASTC, GL_COMPRESSED_RGBA_ASTC_6x6_KHR,                GFX_LFMT_ASTC6X6_RGBA_UNORM},
   {GFX_LFMT_TRANSLATE_GL_EXT_ASTC, GL_COMPRESSED_RGBA_ASTC_8x5_KHR,                GFX_LFMT_ASTC8X5_RGBA_UNORM},
   {GFX_LFMT_TRANSLATE_GL_EXT_ASTC, GL_COMPRESSED_RGBA_ASTC_8x6_KHR,                GFX_LFMT_ASTC8X6_RGBA_UNORM},
   {GFX_LFMT_TRANSLATE_GL_EXT_ASTC, GL_COMPRESSED_RGBA_ASTC_8x8_KHR,                GFX_LFMT_ASTC8X8_RGBA_UNORM},
   {GFX_LFMT_TRANSLATE_GL_EXT_ASTC, GL_COMPRESSED_RGBA_ASTC_10x5_KHR,               GFX_LFMT_ASTC10X5_RGBA_UNORM},
   {GFX_LFMT_TRANSLATE_GL_EXT_ASTC, GL_COMPRESSED_RGBA_ASTC_10x6_KHR,               GFX_LFMT_ASTC10X6_RGBA_UNORM},
   {GFX_LFMT_TRANSLATE_GL_EXT_ASTC, GL_COMPRESSED_RGBA_ASTC_10x8_KHR,               GFX_LFMT_ASTC10X8_RGBA_UNORM},
   {GFX_LFMT_TRANSLATE_GL_EXT_ASTC, GL_COMPRESSED_RGBA_ASTC_10x10_KHR,              GFX_LFMT_ASTC10X10_RGBA_UNORM},
   {GFX_LFMT_TRANSLATE_GL_EXT_ASTC, GL_COMPRESSED_RGBA_ASTC_12x10_KHR,              GFX_LFMT_ASTC12X10_RGBA_UNORM},
   {GFX_LFMT_TRANSLATE_GL_EXT_ASTC, GL_COMPRESSED_RGBA_ASTC_12x12_KHR,              GFX_LFMT_ASTC12X12_RGBA_UNORM},
   {GFX_LFMT_TRANSLATE_GL_EXT_ASTC, GL_COMPRESSED_SRGB8_ALPHA8_ASTC_4x4_KHR,        GFX_LFMT_ASTC4X4_RGBA_SRGB_SRGB_SRGB_UNORM},
   {GFX_LFMT_TRANSLATE_GL_EXT_ASTC, GL_COMPRESSED_SRGB8_ALPHA8_ASTC_5x4_KHR,        GFX_LFMT_ASTC5X4_RGBA_SRGB_SRGB_SRGB_UNORM},
   {GFX_LFMT_TRANSLATE_GL_EXT_ASTC, GL_COMPRESSED_SRGB8_ALPHA8_ASTC_5x5_KHR,        GFX_LFMT_ASTC5X5_RGBA_SRGB_SRGB_SRGB_UNORM},
   {GFX_LFMT_TRANSLATE_GL_EXT_ASTC, GL_COMPRESSED_SRGB8_ALPHA8_ASTC_6x5_KHR,        GFX_LFMT_ASTC6X5_RGBA_SRGB_SRGB_SRGB_UNORM},
   {GFX_LFMT_TRANSLATE_GL_EXT_ASTC, GL_COMPRESSED_SRGB8_ALPHA8_ASTC_6x6_KHR,        GFX_LFMT_ASTC6X6_RGBA_SRGB_SRGB_SRGB_UNORM},
   {GFX_LFMT_TRANSLATE_GL_EXT_ASTC, GL_COMPRESSED_SRGB8_ALPHA8_ASTC_8x5_KHR,        GFX_LFMT_ASTC8X5_RGBA_SRGB_SRGB_SRGB_UNORM},
   {GFX_LFMT_TRANSLATE_GL_EXT_ASTC, GL_COMPRESSED_SRGB8_ALPHA8_ASTC_8x6_KHR,        GFX_LFMT_ASTC8X6_RGBA_SRGB_SRGB_SRGB_UNORM},
   {GFX_LFMT_TRANSLATE_GL_EXT_ASTC, GL_COMPRESSED_SRGB8_ALPHA8_ASTC_8x8_KHR,        GFX_LFMT_ASTC8X8_RGBA_SRGB_SRGB_SRGB_UNORM},
   {GFX_LFMT_TRANSLATE_GL_EXT_ASTC, GL_COMPRESSED_SRGB8_ALPHA8_ASTC_10x5_KHR,       GFX_LFMT_ASTC10X5_RGBA_SRGB_SRGB_SRGB_UNORM},
   {GFX_LFMT_TRANSLATE_GL_EXT_ASTC, GL_COMPRESSED_SRGB8_ALPHA8_ASTC_10x6_KHR,       GFX_LFMT_ASTC10X6_RGBA_SRGB_SRGB_SRGB_UNORM},
   {GFX_LFMT_TRANSLATE_GL_EXT_ASTC, GL_COMPRESSED_SRGB8_ALPHA8_ASTC_10x8_KHR,       GFX_LFMT_ASTC10X8_RGBA_SRGB_SRGB_SRGB_UNORM},
   {GFX_LFMT_TRANSLATE_GL_EXT_ASTC, GL_COMPRESSED_SRGB8_ALPHA8_ASTC_10x10_KHR,      GFX_LFMT_ASTC10X10_RGBA_SRGB_SRGB_SRGB_UNORM},
   {GFX_LFMT_TRANSLATE_GL_EXT_ASTC, GL_COMPRESSED_SRGB8_ALPHA8_ASTC_12x10_KHR,      GFX_LFMT_ASTC12X10_RGBA_SRGB_SRGB_SRGB_UNORM},
   {GFX_LFMT_TRANSLATE_GL_EXT_ASTC, GL_COMPRESSED_SRGB8_ALPHA8_ASTC_12x12_KHR,      GFX_LFMT_ASTC12X12_RGBA_SRGB_SRGB_SRGB_UNORM},
};

unsigned int gfx_compressed_format_enumerate(GLenum *formats, gfx_lfmt_translate_gl_ext_t exts)
{
   unsigned count = 0;

   for (const COMPRESSED_FORMAT_LFMT_T *entry = gfx_compressed_format_lfmt_map;
      entry != gfx_compressed_format_lfmt_map + vcos_countof(gfx_compressed_format_lfmt_map);
      ++entry)
   {
      if (is_subset_of(entry->required_exts, exts))
      {
         ++count;
         if (formats)
            *(formats++) = entry->internalformat;
      }
   }

   return count;
}

GFX_LFMT_T gfx_lfmt_from_compressed_internalformat_maybe(gfx_lfmt_translate_gl_ext_t exts, GLenum internalformat)
{
   for (const COMPRESSED_FORMAT_LFMT_T *entry = gfx_compressed_format_lfmt_map;
      entry != gfx_compressed_format_lfmt_map + vcos_countof(gfx_compressed_format_lfmt_map);
      ++entry)
   {
      if (is_subset_of(entry->required_exts, exts) && (entry->internalformat == internalformat))
         return entry->lfmt;
   }

   return GFX_LFMT_NONE;
}

GLenum gfx_compressed_internalformat_from_api_fmt_maybe(GFX_LFMT_T api_fmt)
{
   for (unsigned i = 0; i < vcos_countof(gfx_compressed_format_lfmt_map); ++i)
   {
      const COMPRESSED_FORMAT_LFMT_T *entry = &gfx_compressed_format_lfmt_map[i];
      if (entry->lfmt == api_fmt)
         return entry->internalformat;
   }
   return GL_NONE;
}

/*===========================================================================*/
/*
   valid combinations of (format, type, internalformat) for glTexImage
*/

typedef struct {
   gfx_lfmt_translate_gl_ext_t required_exts; /* Entry is valid iff all of these extensions are enabled */
   GLenum format;
   GLenum type;
   GLenum internalformat;
} FORMAT_TYPE_INTERNALFORMAT_T;

/* note order is important: see gfx_lfmt_gl_format_type_to_internalformat */
/* note valid_format below is derived from this table and the two should
   be changed in tandem */
static const FORMAT_TYPE_INTERNALFORMAT_T valid_format_type_internalformat_combinations[] = {
   /* GL ES spec 3.0.2, Table 3.2 "Valid combinations of format, type, and
      sized internalformat." */
   {0,                                    GL_RGBA,             GL_UNSIGNED_BYTE,                   GL_RGBA8},
   {0,                                    GL_RGBA,             GL_UNSIGNED_BYTE,                   GL_RGB5_A1},
   {0,                                    GL_RGBA,             GL_UNSIGNED_BYTE,                   GL_RGBA4},
   {0,                                    GL_RGBA,             GL_UNSIGNED_BYTE,                   GL_SRGB8_ALPHA8},
   {0,                                    GL_RGBA,             GL_BYTE,                            GL_RGBA8_SNORM},
   {0,                                    GL_RGBA,             GL_UNSIGNED_SHORT_4_4_4_4,          GL_RGBA4},
   {0,                                    GL_RGBA,             GL_UNSIGNED_SHORT_5_5_5_1,          GL_RGB5_A1},
   {0,                                    GL_RGBA,             GL_UNSIGNED_INT_2_10_10_10_REV,     GL_RGB10_A2},
   {0,                                    GL_RGBA,             GL_UNSIGNED_INT_2_10_10_10_REV,     GL_RGB5_A1},
   {0,                                    GL_RGBA,             GL_HALF_FLOAT,                      GL_RGBA16F},
   {0,                                    GL_RGBA,             GL_FLOAT,                           GL_RGBA32F},
   {0,                                    GL_RGBA,             GL_FLOAT,                           GL_RGBA16F},
   {0,                                    GL_RGBA_INTEGER,     GL_UNSIGNED_BYTE,                   GL_RGBA8UI},
   {0,                                    GL_RGBA_INTEGER,     GL_BYTE,                            GL_RGBA8I},
   {0,                                    GL_RGBA_INTEGER,     GL_UNSIGNED_SHORT,                  GL_RGBA16UI},
   {0,                                    GL_RGBA_INTEGER,     GL_SHORT,                           GL_RGBA16I},
   {0,                                    GL_RGBA_INTEGER,     GL_UNSIGNED_INT,                    GL_RGBA32UI},
   {0,                                    GL_RGBA_INTEGER,     GL_INT,                             GL_RGBA32I},
   {0,                                    GL_RGBA_INTEGER,     GL_UNSIGNED_INT_2_10_10_10_REV,     GL_RGB10_A2UI},
   {0,                                    GL_RGB,              GL_UNSIGNED_BYTE,                   GL_RGB8},
   {0,                                    GL_RGB,              GL_UNSIGNED_BYTE,                   GL_RGB565},
   {0,                                    GL_RGB,              GL_UNSIGNED_BYTE,                   GL_SRGB8},
   {0,                                    GL_RGB,              GL_BYTE,                            GL_RGB8_SNORM},
   {0,                                    GL_RGB,              GL_UNSIGNED_SHORT_5_6_5,            GL_RGB565},
   {0,                                    GL_RGB,              GL_UNSIGNED_INT_10F_11F_11F_REV,    GL_R11F_G11F_B10F},
   {0,                                    GL_RGB,              GL_UNSIGNED_INT_5_9_9_9_REV,        GL_RGB9_E5},
   {0,                                    GL_RGB,              GL_HALF_FLOAT,                      GL_RGB16F},
   {0,                                    GL_RGB,              GL_HALF_FLOAT,                      GL_R11F_G11F_B10F},
   {0,                                    GL_RGB,              GL_HALF_FLOAT,                      GL_RGB9_E5},
   {0,                                    GL_RGB,              GL_FLOAT,                           GL_RGB32F},
   {0,                                    GL_RGB,              GL_FLOAT,                           GL_RGB16F},
   {0,                                    GL_RGB,              GL_FLOAT,                           GL_R11F_G11F_B10F},
   {0,                                    GL_RGB,              GL_FLOAT,                           GL_RGB9_E5},
   {0,                                    GL_RGB_INTEGER,      GL_UNSIGNED_BYTE,                   GL_RGB8UI},
   {0,                                    GL_RGB_INTEGER,      GL_BYTE,                            GL_RGB8I},
   {0,                                    GL_RGB_INTEGER,      GL_UNSIGNED_SHORT,                  GL_RGB16UI},
   {0,                                    GL_RGB_INTEGER,      GL_SHORT,                           GL_RGB16I},
   {0,                                    GL_RGB_INTEGER,      GL_UNSIGNED_INT,                    GL_RGB32UI},
   {0,                                    GL_RGB_INTEGER,      GL_INT,                             GL_RGB32I},
   {0,                                    GL_RG,               GL_UNSIGNED_BYTE,                   GL_RG8},
   {GFX_LFMT_TRANSLATE_GL_EXT_SR8_SRG8,   GL_RG,               GL_UNSIGNED_BYTE,                   GL_SRG8_EXT},
   {0,                                    GL_RG,               GL_BYTE,                            GL_RG8_SNORM},
   {0,                                    GL_RG,               GL_HALF_FLOAT,                      GL_RG16F},
   {0,                                    GL_RG,               GL_FLOAT,                           GL_RG32F},
   {0,                                    GL_RG,               GL_FLOAT,                           GL_RG16F},
   {0,                                    GL_RG_INTEGER,       GL_UNSIGNED_BYTE,                   GL_RG8UI},
   {0,                                    GL_RG_INTEGER,       GL_BYTE,                            GL_RG8I},
   {0,                                    GL_RG_INTEGER,       GL_UNSIGNED_SHORT,                  GL_RG16UI},
   {0,                                    GL_RG_INTEGER,       GL_SHORT,                           GL_RG16I},
   {0,                                    GL_RG_INTEGER,       GL_UNSIGNED_INT,                    GL_RG32UI},
   {0,                                    GL_RG_INTEGER,       GL_INT,                             GL_RG32I},
   {0,                                    GL_RED,              GL_UNSIGNED_BYTE,                   GL_R8},
   {GFX_LFMT_TRANSLATE_GL_EXT_SR8_SRG8,   GL_RED,              GL_UNSIGNED_BYTE,                   GL_SR8_EXT},
   {0,                                    GL_RED,              GL_BYTE,                            GL_R8_SNORM},
   {0,                                    GL_RED,              GL_HALF_FLOAT,                      GL_R16F},
   {0,                                    GL_RED,              GL_FLOAT,                           GL_R32F},
   {0,                                    GL_RED,              GL_FLOAT,                           GL_R16F},
   {0,                                    GL_RED_INTEGER,      GL_UNSIGNED_BYTE,                   GL_R8UI},
   {0,                                    GL_RED_INTEGER,      GL_BYTE,                            GL_R8I},
   {0,                                    GL_RED_INTEGER,      GL_UNSIGNED_SHORT,                  GL_R16UI},
   {0,                                    GL_RED_INTEGER,      GL_SHORT,                           GL_R16I},
   {0,                                    GL_RED_INTEGER,      GL_UNSIGNED_INT,                    GL_R32UI},
   {0,                                    GL_RED_INTEGER,      GL_INT,                             GL_R32I},
   {0,                                    GL_DEPTH_COMPONENT,  GL_UNSIGNED_SHORT,                  GL_DEPTH_COMPONENT16},
   {0,                                    GL_DEPTH_COMPONENT,  GL_UNSIGNED_INT,                    GL_DEPTH_COMPONENT24},
   {0,                                    GL_DEPTH_COMPONENT,  GL_UNSIGNED_INT,                    GL_DEPTH_COMPONENT16},
   {0,                                    GL_DEPTH_COMPONENT,  GL_FLOAT,                           GL_DEPTH_COMPONENT32F},
   {0,                                    GL_DEPTH_STENCIL,    GL_UNSIGNED_INT_24_8,               GL_DEPTH24_STENCIL8},
   {0,                                    GL_DEPTH_STENCIL,    GL_FLOAT_32_UNSIGNED_INT_24_8_REV,  GL_DEPTH32F_STENCIL8},

   /* GL ES spec 3.0.2, Table 3.3 "Valid combinations of format, type, and unsized
      internalformat." */
   {0,                                    GL_RGBA,             GL_UNSIGNED_BYTE,                   GL_RGBA},
   {0,                                    GL_RGBA,             GL_UNSIGNED_SHORT_4_4_4_4,          GL_RGBA},
   {0,                                    GL_RGBA,             GL_UNSIGNED_SHORT_5_5_5_1,          GL_RGBA},
   {0,                                    GL_RGB,              GL_UNSIGNED_BYTE,                   GL_RGB},
   {0,                                    GL_RGB,              GL_UNSIGNED_SHORT_5_6_5,            GL_RGB},
   {0,                                    GL_LUMINANCE_ALPHA,  GL_UNSIGNED_BYTE,                   GL_LUMINANCE_ALPHA},
   {0,                                    GL_LUMINANCE,        GL_UNSIGNED_BYTE,                   GL_LUMINANCE},
   {0,                                    GL_ALPHA,            GL_UNSIGNED_BYTE,                   GL_ALPHA},

#if GL_BRCM_texture_norm16
   {0,                                    GL_RED,              GL_UNSIGNED_SHORT,                  GL_R16_BRCM},
   {0,                                    GL_RG,               GL_UNSIGNED_SHORT,                  GL_RG16_BRCM},
   {0,                                    GL_RGBA,             GL_UNSIGNED_SHORT,                  GL_RGBA16_BRCM},
   {0,                                    GL_RED,              GL_SHORT,                           GL_R16_SNORM_BRCM},
   {0,                                    GL_RG,               GL_SHORT,                           GL_RG16_SNORM_BRCM},
   {0,                                    GL_RGBA,             GL_SHORT,                           GL_RGBA16_SNORM_BRCM},
#endif

#if GL_EXT_texture_format_BGRA8888
   {0,                                    GL_BGRA_EXT,         GL_UNSIGNED_BYTE,                   GL_BGRA_EXT},
#endif

   /*
    * OES_packed_depth_stencil:
    * DEPTH_STENCIL_OES Accepted by the <format> parameter of TexImage2D and TexSubImage2D and by the
       <internalformat> parameter of TexImage2D:
    */
   {0,                                    GL_DEPTH_STENCIL,    GL_UNSIGNED_INT_24_8,               GL_DEPTH_STENCIL},

   /* OES_texture_stencil8 */
   {0,                                    GL_STENCIL_INDEX,    GL_UNSIGNED_BYTE,                   GL_STENCIL_INDEX8},
};

/* Check that ths combination of format, type and internalformat are valid */
bool gfx_lfmt_gl_format_type_internalformat_combination_valid(
   gfx_lfmt_translate_gl_ext_t exts,
   GLenum format, GLenum type, GLenum internalformat)
{
   for (const FORMAT_TYPE_INTERNALFORMAT_T *entry = valid_format_type_internalformat_combinations;
      entry != valid_format_type_internalformat_combinations + vcos_countof(valid_format_type_internalformat_combinations);
      ++entry)
   {
      if (is_subset_of(entry->required_exts, exts) &&
            (entry->format == format) && (entry->type == type) && (entry->internalformat == internalformat))
         return true;
   }

   return false;
}

/* Check that all of the given enums are valid only - the combination may still be invalid */
bool gfx_lfmt_gl_format_type_internalformat_valid_enums(
   gfx_lfmt_translate_gl_ext_t exts,
   GLenum format, GLenum type, GLenum internalformat)
{
   bool format_ok = false;
   bool type_ok = false;
   bool internalformat_ok = false;

   for (const FORMAT_TYPE_INTERNALFORMAT_T *entry = valid_format_type_internalformat_combinations;
      entry != valid_format_type_internalformat_combinations + vcos_countof(valid_format_type_internalformat_combinations);
      ++entry)
   {
      if (is_subset_of(entry->required_exts, exts))
      {
         format_ok = format_ok || (entry->format == format);
         type_ok = type_ok || (entry->type == type);
         internalformat_ok = internalformat_ok || (entry->internalformat == internalformat);

         // The format enums are also valid unsized internalformat enums so, for the purpose
         // of enum checking, we must include those too
         internalformat_ok = internalformat_ok || (entry->format == internalformat);

         if (format_ok && type_ok && internalformat_ok)
            return true;
      }
   }

   return false;
}

bool gfx_gl_format_type_combination_valid(
   gfx_lfmt_translate_gl_ext_t exts,
   GLenum format, GLenum type)
{
   for (const FORMAT_TYPE_INTERNALFORMAT_T *entry = valid_format_type_internalformat_combinations;
      entry != valid_format_type_internalformat_combinations + vcos_countof(valid_format_type_internalformat_combinations);
      ++entry)
   {
      if (is_subset_of(entry->required_exts, exts) && (entry->format == format) && (entry->type == type))
         return true;
   }

   return false;
}

bool gfx_gl_format_type_valid_enums(gfx_lfmt_translate_gl_ext_t exts, GLenum format, GLenum type)
{
   bool format_ok = false;
   bool type_ok = false;

   for (const FORMAT_TYPE_INTERNALFORMAT_T *entry = valid_format_type_internalformat_combinations;
      entry != valid_format_type_internalformat_combinations + vcos_countof(valid_format_type_internalformat_combinations);
      ++entry)
   {
      if (is_subset_of(entry->required_exts, exts))
      {
         format_ok = format_ok || (entry->format == format);
         type_ok = type_ok || (entry->type == type);

         if (format_ok && type_ok)
            return true;
      }
   }

   return false;
}
/*
return an internalformat compatible with (format,type). Moreover, return the
one that results in no loss of precision.

assumes non-srgb.
*/
GLenum gfx_lfmt_gl_format_type_to_internalformat(gfx_lfmt_translate_gl_ext_t exts, GLenum format, GLenum type)
{
   for (const FORMAT_TYPE_INTERNALFORMAT_T *entry = valid_format_type_internalformat_combinations;
      entry != valid_format_type_internalformat_combinations + vcos_countof(valid_format_type_internalformat_combinations);
      ++entry)
   {
      if (is_subset_of(entry->required_exts, exts) && (entry->format == format) && (entry->type == type))
         return entry->internalformat;
   }
   unreachable();
   return GL_NONE;
}

/* return true if internalformat is a valid enum to pass to gl*TexImage*() */
bool gfx_gl_is_texture_internalformat(gfx_lfmt_translate_gl_ext_t exts, GLenum internalformat)
{
   for (const FORMAT_TYPE_INTERNALFORMAT_T *entry = valid_format_type_internalformat_combinations;
      entry != valid_format_type_internalformat_combinations + vcos_countof(valid_format_type_internalformat_combinations);
      ++entry)
   {
      if (is_subset_of(entry->required_exts, exts) && (entry->internalformat == internalformat))
         return true;
   }

   return false;
}

void gfx_gl_sizedinternalformat_to_format_type(gfx_lfmt_translate_gl_ext_t exts, GLenum sizedinternalformat,
      GLenum *format, GLenum *type)
{
   for (const FORMAT_TYPE_INTERNALFORMAT_T *entry = valid_format_type_internalformat_combinations;
      entry != valid_format_type_internalformat_combinations + vcos_countof(valid_format_type_internalformat_combinations);
      ++entry)
   {
      if (is_subset_of(entry->required_exts, exts) &&
          (entry->internalformat == sizedinternalformat))
      {
         *format = entry->format;
         *type = entry->type;
         return;
      }
   }
   unreachable();
   return;
}

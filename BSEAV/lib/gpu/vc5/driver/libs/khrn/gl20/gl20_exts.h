/******************************************************************************
 *  Copyright (C) 2017 Broadcom. The term "Broadcom" refers to Broadcom Limited and/or its subsidiaries.
 ******************************************************************************/
/* Auto-generated by running gen_hook_tables.py
 * DO NOT EDIT!
 */
#include <string.h>
#include "libs/core/v3d/v3d_ver.h"
#include "../glxx/gl_public_api.h"
#include "../glxx/glxx_int_config.h"
#include "../common/khrn_process.h"
#define GL20_EXTS_STR_MAX_SIZE 2050
static inline char *gl20_exts_str(char *s_in)
{
   char *s = s_in;
#if V3D_VER_AT_LEAST(4,2,13,0)
   memcpy(s, "GL_BRCM_image_formats", 21);
   s += 21;
   *(s++) = ' ';
#endif
   memcpy(s, "GL_BRCM_mirror_clamp_to_edge", 28);
   s += 28;
   *(s++) = ' ';
#if V3D_VER_AT_LEAST(4,1,34,0)
   memcpy(s, "GL_BRCM_no_perspective", 22);
   s += 22;
   *(s++) = ' ';
#endif
   memcpy(s, "GL_BRCM_polygon_mode", 20);
   s += 20;
   *(s++) = ' ';
#if V3D_VER_AT_LEAST(3,3,0,0)
   memcpy(s, "GL_BRCM_provoking_vertex", 24);
   s += 24;
   *(s++) = ' ';
#endif
#if V3D_VER_AT_LEAST(4,0,2,0)
   memcpy(s, "GL_BRCM_sampler_fetch", 21);
   s += 21;
   *(s++) = ' ';
#endif
#if V3D_VER_AT_LEAST(4,0,2,0)
   memcpy(s, "GL_BRCM_shader_framebuffer_fetch_depth_stencil", 46);
   s += 46;
   *(s++) = ' ';
#endif
#if V3D_VER_AT_LEAST(4,0,2,0)
   memcpy(s, "GL_BRCM_texture_1D", 18);
   s += 18;
   *(s++) = ' ';
#endif
#if V3D_VER_AT_LEAST(3,3,0,0)
   memcpy(s, "GL_BRCM_texture_gather_lod", 26);
   s += 26;
   *(s++) = ' ';
#endif
   memcpy(s, "GL_BRCM_texture_norm16", 22);
   s += 22;
   *(s++) = ' ';
#if V3D_VER_AT_LEAST(4,0,2,0)
   memcpy(s, "GL_BRCM_texture_unnormalised_coords", 35);
   s += 35;
   *(s++) = ' ';
#endif
#if V3D_VER_AT_LEAST(4,0,2,0)
   memcpy(s, "GL_EXT_base_instance", 20);
   s += 20;
   *(s++) = ' ';
#endif
   memcpy(s, "GL_EXT_color_buffer_float", 25);
   s += 25;
   *(s++) = ' ';
   memcpy(s, "GL_EXT_copy_image", 17);
   s += 17;
   *(s++) = ' ';
   memcpy(s, "GL_EXT_debug_marker", 19);
   s += 19;
   *(s++) = ' ';
   memcpy(s, "GL_EXT_discard_framebuffer", 26);
   s += 26;
   *(s++) = ' ';
#if V3D_VER_AT_LEAST(4,0,2,0)
   memcpy(s, "GL_EXT_draw_buffers_indexed", 27);
   s += 27;
   *(s++) = ' ';
#endif
   memcpy(s, "GL_EXT_draw_elements_base_vertex", 32);
   s += 32;
   *(s++) = ' ';
#if GLXX_HAS_TNG
   memcpy(s, "GL_EXT_geometry_point_size", 26);
   s += 26;
   *(s++) = ' ';
#endif
#if GLXX_HAS_TNG
   memcpy(s, "GL_EXT_geometry_shader", 22);
   s += 22;
   *(s++) = ' ';
#endif
#if V3D_VER_AT_LEAST(4,0,2,0)
   memcpy(s, "GL_EXT_gpu_shader5", 18);
   s += 18;
   *(s++) = ' ';
#endif
#if V3D_VER_AT_LEAST(3,3,0,0)
   memcpy(s, "GL_EXT_multi_draw_indirect", 26);
   s += 26;
   *(s++) = ' ';
#endif
   memcpy(s, "GL_EXT_multisampled_render_to_texture", 37);
   s += 37;
   *(s++) = ' ';
#if V3D_VER_AT_LEAST(4,1,34,0)
   memcpy(s, "GL_EXT_polygon_offset_clamp", 27);
   s += 27;
   *(s++) = ' ';
#endif
#if V3D_VER_AT_LEAST(3,3,0,0)
   memcpy(s, "GL_EXT_primitive_bounding_box", 29);
   s += 29;
   *(s++) = ' ';
#endif
   memcpy(s, "GL_EXT_protected_textures", 25);
   s += 25;
   *(s++) = ' ';
   memcpy(s, "GL_EXT_robustness", 17);
   s += 17;
   *(s++) = ' ';
   memcpy(s, "GL_EXT_shader_integer_mix", 25);
   s += 25;
   *(s++) = ' ';
#if GLXX_HAS_TNG
   memcpy(s, "GL_EXT_shader_io_blocks", 23);
   s += 23;
   *(s++) = ' ';
#endif
   memcpy(s, "GL_EXT_shader_texture_lod", 25);
   s += 25;
   *(s++) = ' ';
#if GLXX_HAS_TNG
   memcpy(s, "GL_EXT_tessellation_point_size", 30);
   s += 30;
   *(s++) = ' ';
#endif
#if GLXX_HAS_TNG
   memcpy(s, "GL_EXT_tessellation_shader", 26);
   s += 26;
   *(s++) = ' ';
#endif
#if V3D_VER_AT_LEAST(4,0,2,0)
   memcpy(s, "GL_EXT_texture_border_clamp", 27);
   s += 27;
   *(s++) = ' ';
#endif
#if V3D_VER_AT_LEAST(4,1,34,0)
   memcpy(s, "GL_EXT_texture_buffer", 21);
   s += 21;
   *(s++) = ' ';
#endif
#if V3D_VER_AT_LEAST(4,0,2,0)
   memcpy(s, "GL_EXT_texture_cube_map_array", 29);
   s += 29;
   *(s++) = ' ';
#endif
   memcpy(s, "GL_EXT_texture_filter_anisotropic", 33);
   s += 33;
   *(s++) = ' ';
   memcpy(s, "GL_EXT_texture_format_BGRA8888", 30);
   s += 30;
   *(s++) = ' ';
#if V3D_VER_AT_LEAST(3,3,0,0)
   memcpy(s, "GL_EXT_texture_sRGB_R8", 22);
   s += 22;
   *(s++) = ' ';
#endif
#if V3D_VER_AT_LEAST(3,3,0,0)
   memcpy(s, "GL_EXT_texture_sRGB_RG8", 23);
   s += 23;
   *(s++) = ' ';
#endif
   memcpy(s, "GL_EXT_texture_sRGB_decode", 26);
   s += 26;
   *(s++) = ' ';
   memcpy(s, "GL_KHR_blend_equation_advanced", 30);
   s += 30;
   *(s++) = ' ';
   memcpy(s, "GL_KHR_blend_equation_advanced_coherent", 39);
   s += 39;
   *(s++) = ' ';
   memcpy(s, "GL_KHR_debug", 12);
   s += 12;
   *(s++) = ' ';
   memcpy(s, "GL_KHR_robustness", 17);
   s += 17;
   *(s++) = ' ';
   if (khrn_get_has_astc())
   {
      memcpy(s, "GL_KHR_texture_compression_astc_ldr", 35);
      s += 35;
      *(s++) = ' ';
   }
   memcpy(s, "GL_OES_EGL_image", 16);
   s += 16;
   *(s++) = ' ';
   memcpy(s, "GL_OES_EGL_image_external", 25);
   s += 25;
   *(s++) = ' ';
   memcpy(s, "GL_OES_EGL_sync", 15);
   s += 15;
   *(s++) = ' ';
   memcpy(s, "GL_OES_compressed_ETC1_RGB8_texture", 35);
   s += 35;
   *(s++) = ' ';
   memcpy(s, "GL_OES_compressed_paletted_texture", 34);
   s += 34;
   *(s++) = ' ';
   memcpy(s, "GL_OES_copy_image", 17);
   s += 17;
   *(s++) = ' ';
   memcpy(s, "GL_OES_depth24", 14);
   s += 14;
   *(s++) = ' ';
#if V3D_VER_AT_LEAST(4,0,2,0)
   memcpy(s, "GL_OES_draw_buffers_indexed", 27);
   s += 27;
   *(s++) = ' ';
#endif
   memcpy(s, "GL_OES_draw_elements_base_vertex", 32);
   s += 32;
   *(s++) = ' ';
#if GLXX_HAS_TNG
   memcpy(s, "GL_OES_geometry_point_size", 26);
   s += 26;
   *(s++) = ' ';
#endif
#if GLXX_HAS_TNG
   memcpy(s, "GL_OES_geometry_shader", 22);
   s += 22;
   *(s++) = ' ';
#endif
#if V3D_VER_AT_LEAST(4,0,2,0)
   memcpy(s, "GL_OES_gpu_shader5", 18);
   s += 18;
   *(s++) = ' ';
#endif
   memcpy(s, "GL_OES_mapbuffer", 16);
   s += 16;
   *(s++) = ' ';
   memcpy(s, "GL_OES_packed_depth_stencil", 27);
   s += 27;
   *(s++) = ' ';
#if V3D_VER_AT_LEAST(3,3,0,0)
   memcpy(s, "GL_OES_primitive_bounding_box", 29);
   s += 29;
   *(s++) = ' ';
#endif
   memcpy(s, "GL_OES_rgb8_rgba8", 17);
   s += 17;
   *(s++) = ' ';
#if V3D_VER_AT_LEAST(4,0,2,0)
   memcpy(s, "GL_OES_sample_shading", 21);
   s += 21;
   *(s++) = ' ';
#endif
#if V3D_VER_AT_LEAST(4,1,34,0)
   memcpy(s, "GL_OES_sample_variables", 23);
   s += 23;
   *(s++) = ' ';
#endif
   memcpy(s, "GL_OES_shader_image_atomic", 26);
   s += 26;
   *(s++) = ' ';
#if GLXX_HAS_TNG
   memcpy(s, "GL_OES_shader_io_blocks", 23);
   s += 23;
   *(s++) = ' ';
#endif
#if KHRN_GLES32_DRIVER && V3D_VER_AT_LEAST(4,0,2,0)
   memcpy(s, "GL_OES_shader_multisample_interpolation", 39);
   s += 39;
   *(s++) = ' ';
#endif
   memcpy(s, "GL_OES_standard_derivatives", 27);
   s += 27;
   *(s++) = ' ';
   memcpy(s, "GL_OES_surfaceless_context", 26);
   s += 26;
   *(s++) = ' ';
#if GLXX_HAS_TNG
   memcpy(s, "GL_OES_tessellation_point_size", 30);
   s += 30;
   *(s++) = ' ';
#endif
#if GLXX_HAS_TNG
   memcpy(s, "GL_OES_tessellation_shader", 26);
   s += 26;
   *(s++) = ' ';
#endif
#if V3D_VER_AT_LEAST(4,0,2,0)
   memcpy(s, "GL_OES_texture_border_clamp", 27);
   s += 27;
   *(s++) = ' ';
#endif
#if V3D_VER_AT_LEAST(4,1,34,0)
   memcpy(s, "GL_OES_texture_buffer", 21);
   s += 21;
   *(s++) = ' ';
#endif
#if V3D_VER_AT_LEAST(4,0,2,0)
   memcpy(s, "GL_OES_texture_cube_map_array", 29);
   s += 29;
   *(s++) = ' ';
#endif
   memcpy(s, "GL_OES_texture_npot", 19);
   s += 19;
   *(s++) = ' ';
   memcpy(s, "GL_OES_texture_stencil8", 23);
   s += 23;
   *(s++) = ' ';
#if V3D_VER_AT_LEAST(3,3,0,0)
   memcpy(s, "GL_OES_texture_storage_multisample_2d_array", 43);
   s += 43;
   *(s++) = ' ';
#endif
   memcpy(s, "GL_OES_vertex_array_object", 26);
   s += 26;
   *(s++) = ' ';
   memcpy(s, "GL_OES_vertex_half_float", 24);
   s += 24;
   *(s++) = ' ';
   if (s != s_in)
      --s;
   *s = '\0';
   return s;
}
#define GL20_MAX_EXTS 78
static inline unsigned gl20_exts(const char **e_in)
{
   const char **e = e_in;
#if V3D_VER_AT_LEAST(4,2,13,0)
   *(e++) = "GL_BRCM_image_formats";
#endif
   *(e++) = "GL_BRCM_mirror_clamp_to_edge";
#if V3D_VER_AT_LEAST(4,1,34,0)
   *(e++) = "GL_BRCM_no_perspective";
#endif
   *(e++) = "GL_BRCM_polygon_mode";
#if V3D_VER_AT_LEAST(3,3,0,0)
   *(e++) = "GL_BRCM_provoking_vertex";
#endif
#if V3D_VER_AT_LEAST(4,0,2,0)
   *(e++) = "GL_BRCM_sampler_fetch";
#endif
#if V3D_VER_AT_LEAST(4,0,2,0)
   *(e++) = "GL_BRCM_shader_framebuffer_fetch_depth_stencil";
#endif
#if V3D_VER_AT_LEAST(4,0,2,0)
   *(e++) = "GL_BRCM_texture_1D";
#endif
#if V3D_VER_AT_LEAST(3,3,0,0)
   *(e++) = "GL_BRCM_texture_gather_lod";
#endif
   *(e++) = "GL_BRCM_texture_norm16";
#if V3D_VER_AT_LEAST(4,0,2,0)
   *(e++) = "GL_BRCM_texture_unnormalised_coords";
#endif
#if V3D_VER_AT_LEAST(4,0,2,0)
   *(e++) = "GL_EXT_base_instance";
#endif
   *(e++) = "GL_EXT_color_buffer_float";
   *(e++) = "GL_EXT_copy_image";
   *(e++) = "GL_EXT_debug_marker";
   *(e++) = "GL_EXT_discard_framebuffer";
#if V3D_VER_AT_LEAST(4,0,2,0)
   *(e++) = "GL_EXT_draw_buffers_indexed";
#endif
   *(e++) = "GL_EXT_draw_elements_base_vertex";
#if GLXX_HAS_TNG
   *(e++) = "GL_EXT_geometry_point_size";
#endif
#if GLXX_HAS_TNG
   *(e++) = "GL_EXT_geometry_shader";
#endif
#if V3D_VER_AT_LEAST(4,0,2,0)
   *(e++) = "GL_EXT_gpu_shader5";
#endif
#if V3D_VER_AT_LEAST(3,3,0,0)
   *(e++) = "GL_EXT_multi_draw_indirect";
#endif
   *(e++) = "GL_EXT_multisampled_render_to_texture";
#if V3D_VER_AT_LEAST(4,1,34,0)
   *(e++) = "GL_EXT_polygon_offset_clamp";
#endif
#if V3D_VER_AT_LEAST(3,3,0,0)
   *(e++) = "GL_EXT_primitive_bounding_box";
#endif
   *(e++) = "GL_EXT_protected_textures";
   *(e++) = "GL_EXT_robustness";
   *(e++) = "GL_EXT_shader_integer_mix";
#if GLXX_HAS_TNG
   *(e++) = "GL_EXT_shader_io_blocks";
#endif
   *(e++) = "GL_EXT_shader_texture_lod";
#if GLXX_HAS_TNG
   *(e++) = "GL_EXT_tessellation_point_size";
#endif
#if GLXX_HAS_TNG
   *(e++) = "GL_EXT_tessellation_shader";
#endif
#if V3D_VER_AT_LEAST(4,0,2,0)
   *(e++) = "GL_EXT_texture_border_clamp";
#endif
#if V3D_VER_AT_LEAST(4,1,34,0)
   *(e++) = "GL_EXT_texture_buffer";
#endif
#if V3D_VER_AT_LEAST(4,0,2,0)
   *(e++) = "GL_EXT_texture_cube_map_array";
#endif
   *(e++) = "GL_EXT_texture_filter_anisotropic";
   *(e++) = "GL_EXT_texture_format_BGRA8888";
#if V3D_VER_AT_LEAST(3,3,0,0)
   *(e++) = "GL_EXT_texture_sRGB_R8";
#endif
#if V3D_VER_AT_LEAST(3,3,0,0)
   *(e++) = "GL_EXT_texture_sRGB_RG8";
#endif
   *(e++) = "GL_EXT_texture_sRGB_decode";
   *(e++) = "GL_KHR_blend_equation_advanced";
   *(e++) = "GL_KHR_blend_equation_advanced_coherent";
   *(e++) = "GL_KHR_debug";
   *(e++) = "GL_KHR_robustness";
   if (khrn_get_has_astc())
      *(e++) = "GL_KHR_texture_compression_astc_ldr";
   *(e++) = "GL_OES_EGL_image";
   *(e++) = "GL_OES_EGL_image_external";
   *(e++) = "GL_OES_EGL_sync";
   *(e++) = "GL_OES_compressed_ETC1_RGB8_texture";
   *(e++) = "GL_OES_compressed_paletted_texture";
   *(e++) = "GL_OES_copy_image";
   *(e++) = "GL_OES_depth24";
#if V3D_VER_AT_LEAST(4,0,2,0)
   *(e++) = "GL_OES_draw_buffers_indexed";
#endif
   *(e++) = "GL_OES_draw_elements_base_vertex";
#if GLXX_HAS_TNG
   *(e++) = "GL_OES_geometry_point_size";
#endif
#if GLXX_HAS_TNG
   *(e++) = "GL_OES_geometry_shader";
#endif
#if V3D_VER_AT_LEAST(4,0,2,0)
   *(e++) = "GL_OES_gpu_shader5";
#endif
   *(e++) = "GL_OES_mapbuffer";
   *(e++) = "GL_OES_packed_depth_stencil";
#if V3D_VER_AT_LEAST(3,3,0,0)
   *(e++) = "GL_OES_primitive_bounding_box";
#endif
   *(e++) = "GL_OES_rgb8_rgba8";
#if V3D_VER_AT_LEAST(4,0,2,0)
   *(e++) = "GL_OES_sample_shading";
#endif
#if V3D_VER_AT_LEAST(4,1,34,0)
   *(e++) = "GL_OES_sample_variables";
#endif
   *(e++) = "GL_OES_shader_image_atomic";
#if GLXX_HAS_TNG
   *(e++) = "GL_OES_shader_io_blocks";
#endif
#if KHRN_GLES32_DRIVER && V3D_VER_AT_LEAST(4,0,2,0)
   *(e++) = "GL_OES_shader_multisample_interpolation";
#endif
   *(e++) = "GL_OES_standard_derivatives";
   *(e++) = "GL_OES_surfaceless_context";
#if GLXX_HAS_TNG
   *(e++) = "GL_OES_tessellation_point_size";
#endif
#if GLXX_HAS_TNG
   *(e++) = "GL_OES_tessellation_shader";
#endif
#if V3D_VER_AT_LEAST(4,0,2,0)
   *(e++) = "GL_OES_texture_border_clamp";
#endif
#if V3D_VER_AT_LEAST(4,1,34,0)
   *(e++) = "GL_OES_texture_buffer";
#endif
#if V3D_VER_AT_LEAST(4,0,2,0)
   *(e++) = "GL_OES_texture_cube_map_array";
#endif
   *(e++) = "GL_OES_texture_npot";
   *(e++) = "GL_OES_texture_stencil8";
#if V3D_VER_AT_LEAST(3,3,0,0)
   *(e++) = "GL_OES_texture_storage_multisample_2d_array";
#endif
   *(e++) = "GL_OES_vertex_array_object";
   *(e++) = "GL_OES_vertex_half_float";
   return e - e_in;
}

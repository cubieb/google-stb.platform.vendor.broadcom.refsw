/*=============================================================================
Copyright (c) 2013 Broadcom Europe Limited.
All rights reserved.
=============================================================================*/

#include "interface/khronos/glxx/gl_public_api.h"
#include "interface/khronos/common/khrn_int_common.h"
#include "middleware/khronos/glxx/glxx_server.h"
#include "middleware/khronos/glxx/glxx_log.h"
#include "interface/khronos/tools/dglenum/dglenum.h"
#include "middleware/khronos/glxx/glxx_draw.h"

#if GL_BRCM_multi_draw_indirect
GL_APICALL void GL_APIENTRY glMultiDrawArraysIndirectBRCM(
   GLenum mode,
   const void *indirect,
   GLsizei num_indirect,
   GLsizei indirect_stride
)
{
   GLXX_SERVER_STATE_T *state = GL31_LOCK_SERVER_STATE();
   if (!state)
      return;

   vcos_logc_trace((&glxx_draw_log), "glMultiDrawArraysIndirectBRCM");
   GLXX_DRAW_RAW_T draw = {
      GLXX_DRAW_RAW_DEFAULTS,
      .mode = mode,
      .is_draw_arrays = true,
      .is_indirect = true,
      .num_indirect = num_indirect,
      .indirect_stride = indirect_stride,
      .indirect = indirect};
   glintDrawArraysOrElements(state, &draw);

   GL31_UNLOCK_SERVER_STATE();
}

GL_APICALL void GL_APIENTRY glMultiDrawElementsIndirectBRCM(
   GLenum mode,
   GLenum index_type,
   const void *indirect,
   GLsizei num_indirect,
   GLsizei indirect_stride
)
{
   GLXX_SERVER_STATE_T *state = GL31_LOCK_SERVER_STATE();
   if (!state)
      return;

   vcos_logc_trace((&glxx_draw_log), "glMultiDrawElementsIndirectBRCM");
   GLXX_DRAW_RAW_T draw = {
      GLXX_DRAW_RAW_DEFAULTS,
      .mode = mode,
      .index_type = index_type,
      .is_indirect = true,
      .num_indirect = num_indirect,
      .indirect_stride = indirect_stride,
      .indirect = indirect};
   glintDrawArraysOrElements(state, &draw);

   GL31_UNLOCK_SERVER_STATE();
}

#endif

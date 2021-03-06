/*=============================================================================
Copyright (c) 2010 Broadcom Europe Limited.
All rights reserved.

Project  :  khronos
Module   :  Blitting/filtering

FILE DESCRIPTION
On 2707b, all functions declared in this file must only be called on the second
VPU.
=============================================================================*/

#ifndef KHRN_BF_4_H
#define KHRN_BF_4_H

#include "middleware/khronos/common/khrn_image.h"

typedef enum {
   BF_TILE_MASK = 0x3 << 0,

   BF_TILE_FILL    = 0 << 0,
   BF_TILE_PAD     = 1 << 0,
   BF_TILE_REPEAT  = 2 << 0,
   BF_TILE_REFLECT = 3 << 0,

   /* internal */
   BF_TILE_X                  = 1 << 2,
   BF_TILE_Y                  = 1 << 3,
   BF_TILE_UNPACK_AND_CONVERT = 1 << 4
} KHRN_BF_TILE_T;

extern void khrn_bf_color_matrix_prepare(
   int16_t *matrix, int32_t *bias, int32_t *shift, const float *matrix_in); /* matrix_in needs to be clean_float()ed */
extern void khrn_bf_color_matrix(
   KHRN_IMAGE_WRAP_T *dst, uint32_t dst_x, uint32_t dst_y,
   uint32_t width, uint32_t height,
   const KHRN_IMAGE_WRAP_T *src, uint32_t src_x, uint32_t src_y,
   uint32_t channel_mask, KHRN_IMAGE_FORMAT_T format, KHRN_IMAGE_CONV_T conv,
   const int16_t *matrix, const int32_t *bias, int32_t shift);

extern void khrn_bf_lookup(
   KHRN_IMAGE_WRAP_T *dst, uint32_t dst_x, uint32_t dst_y,
   uint32_t width, uint32_t height,
   const KHRN_IMAGE_WRAP_T *src, uint32_t src_x, uint32_t src_y,
   uint32_t channel_mask, KHRN_IMAGE_FORMAT_T format, KHRN_IMAGE_CONV_T conv,
   const uint8_t *red_lut,
   const uint8_t *green_lut,
   const uint8_t *blue_lut,
   const uint8_t *alpha_lut,
   KHRN_IMAGE_FORMAT_T output_format);

extern void khrn_bf_lookup_single(
   KHRN_IMAGE_WRAP_T *dst, uint32_t dst_x, uint32_t dst_y,
   uint32_t width, uint32_t height,
   const KHRN_IMAGE_WRAP_T *src, uint32_t src_x, uint32_t src_y,
   uint32_t channel_mask, KHRN_IMAGE_FORMAT_T format, KHRN_IMAGE_CONV_T conv,
   uint32_t source_channel,
   const uint32_t *lut,
   KHRN_IMAGE_FORMAT_T output_format);

extern void khrn_bf_sconv_init(void);
extern void khrn_bf_sconv_term(void);
extern bool khrn_bf_sconv_prepare(
   int16_t *kernel_y, int32_t *interm_bias, int32_t *interm_shift,
   int16_t *kernel_x, int64_t *bias, int32_t *shift,
   const int16_t *kernel_x_in, uint32_t kernel_width,
   const int16_t *kernel_y_in, uint32_t kernel_height,
   float scale, float bias_in); /* returns interm_16 */
extern bool khrn_bf_sconv(
   KHRN_IMAGE_WRAP_T *dst, uint32_t dst_x, uint32_t dst_y, uint32_t dst_width, uint32_t dst_height,
   const KHRN_IMAGE_WRAP_T *src, uint32_t src_x, uint32_t src_y, uint32_t src_width, uint32_t src_height,
   uint32_t channel_mask, KHRN_IMAGE_FORMAT_T format, KHRN_IMAGE_CONV_T conv,
   KHRN_BF_TILE_T tile, uint32_t tile_fill_rgba,
   int32_t shift_x, int32_t shift_y,
   bool interm_16,
   const int16_t *kernel_y, uint32_t kernel_height, int32_t interm_bias, int32_t interm_shift,
   const int16_t *kernel_x, uint32_t kernel_width, int64_t bias, int32_t shift);

extern void khrn_bf_conv_prepare(
   int16_t *kernel, int32_t *bias, int32_t *shift,
   const int16_t *kernel_in, uint32_t kernel_width, uint32_t kernel_height,
   float scale, float bias_in);
extern void khrn_bf_conv(
   KHRN_IMAGE_WRAP_T *dst, uint32_t dst_x, uint32_t dst_y, uint32_t dst_width, uint32_t dst_height,
   const KHRN_IMAGE_WRAP_T *src, uint32_t src_x, uint32_t src_y, uint32_t src_width, uint32_t src_height,
   uint32_t channel_mask, KHRN_IMAGE_FORMAT_T format, KHRN_IMAGE_CONV_T conv,
   KHRN_BF_TILE_T tile, uint32_t tile_fill_rgba,
   int32_t shift_x, int32_t shift_y,
   const int16_t *kernel, uint32_t kernel_width, uint32_t kernel_height, int32_t bias, int32_t shift);

#endif

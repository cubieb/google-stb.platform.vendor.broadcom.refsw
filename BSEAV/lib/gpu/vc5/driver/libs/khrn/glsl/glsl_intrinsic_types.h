/******************************************************************************
 *  Copyright (C) 2017 Broadcom. The term "Broadcom" refers to Broadcom Limited and/or its subsidiaries.
 ******************************************************************************/
#pragma once

typedef enum glsl_intrinsic_index_e {
   INTRINSIC_TEXTURE,
   INTRINSIC_TEXTURE_SIZE,
   INTRINSIC_RSQRT,
   INTRINSIC_RCP,
   INTRINSIC_LOG2,
   INTRINSIC_EXP2,
   INTRINSIC_CEIL,
   INTRINSIC_FLOOR,
   INTRINSIC_TRUNC,
   INTRINSIC_NEAREST,
   INTRINSIC_MIN,
   INTRINSIC_MAX,
   INTRINSIC_ABS,
   INTRINSIC_FDX,
   INTRINSIC_FDY,
   INTRINSIC_CLZ,
   INTRINSIC_ROR,
   INTRINSIC_REINTERPF,
   INTRINSIC_REINTERPI,
   INTRINSIC_REINTERPU,
   INTRINSIC_FPACK,
   INTRINSIC_FUNPACKA,
   INTRINSIC_FUNPACKB,
   INTRINSIC_SIN,
   INTRINSIC_COS,
   INTRINSIC_TAN,
   INTRINSIC_ISNAN,
   INTRINSIC_ATOMIC_LOAD,
   INTRINSIC_ATOMIC_ADD,
   INTRINSIC_ATOMIC_SUB,
   INTRINSIC_ATOMIC_MIN,
   INTRINSIC_ATOMIC_MAX,
   INTRINSIC_ATOMIC_AND,
   INTRINSIC_ATOMIC_OR,
   INTRINSIC_ATOMIC_XOR,
   INTRINSIC_ATOMIC_XCHG,
   INTRINSIC_ATOMIC_CMPXCHG,
   INTRINSIC_IMAGE_STORE,
   INTRINSIC_IMAGE_ADD,
   INTRINSIC_IMAGE_MIN,
   INTRINSIC_IMAGE_MAX,
   INTRINSIC_IMAGE_AND,
   INTRINSIC_IMAGE_OR,
   INTRINSIC_IMAGE_XOR,
   INTRINSIC_IMAGE_XCHG,
   INTRINSIC_IMAGE_CMPXCHG,
   INTRINSIC_COUNT, // MARKER
} glsl_intrinsic_index_t;

typedef struct glsl_intrinsic_data_s {
   const char *name;
   glsl_intrinsic_index_t index;
} glsl_intrinsic_data_t;

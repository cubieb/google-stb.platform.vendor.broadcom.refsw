/*=============================================================================
Copyright (c) 2008 Broadcom Europe Limited.
All rights reserved.

Project  :  khronos
Module   :  Memory management

FILE DESCRIPTION
Khronos memory management API - backed by either reloc heap or malloc
=============================================================================*/
#include "middleware/khronos/common/khrn_mem.h"
#include "vcos.h"
#include "interface/khronos/common/khrn_int_util.h"

KHRN_MEM_HANDLE_T khrn_mem_handle_zero_size;
KHRN_MEM_HANDLE_T khrn_mem_handle_empty_string;

KHRN_MEM_HANDLE_T khrn_mem_alloc_ex(size_t size, const char *desc, bool init, bool resizeable, bool discardable)
{
   uint8_t *alloc;
   KHRN_MEM_HEADER_T *header;
   void *result;

   /* Ignore resizeable and discardable */

   alloc = malloc(size + sizeof(KHRN_MEM_HEADER_T));
   if (!alloc)
   {
      return KHRN_MEM_HANDLE_INVALID;
   }

   header = (KHRN_MEM_HEADER_T *)alloc;
   header->magic = KHRN_MEM_HEADER_MAGIC;
   header->ref_count = 1;
   header->term = NULL;
   header->size = size;

   result = (uint8_t *)alloc + sizeof(KHRN_MEM_HEADER_T);
   if (init)
   {
      khrn_memset(result, 0, size);
   }

   assert(header == khrn_mem_header(result));

   return result;
}

void khrn_mem_release(KHRN_MEM_HANDLE_T handle)
{
   int before_dec;
   KHRN_MEM_HEADER_T *header;

   if (handle == KHRN_MEM_HANDLE_INVALID)
      return;

   header = khrn_mem_header(handle);
   before_dec = vcos_atomic_dec(&header->ref_count);
   assert(before_dec > 0);

   if (before_dec == 1)
   {
      if (header->term)
         header->term(handle, header->size);

      free(header);
   }
}

bool khrn_mem_try_release(KHRN_MEM_HANDLE_T handle)
{
   KHRN_MEM_HEADER_T *header;

   if (handle == KHRN_MEM_HANDLE_INVALID)
      return false;

   header = khrn_mem_header(handle);
   assert(header->ref_count > 0);
   if (header->ref_count == 1)
      return false;

   header->ref_count--;
   return true;
}

bool khrn_mem_resize(KHRN_MEM_HANDLE_T *handle_inout, size_t size)
{
   KHRN_MEM_HEADER_T *header;
   size_t old_size;
   KHRN_MEM_HANDLE_T new_handle;
   KHRN_MEM_HANDLE_T handle = *handle_inout;
   void *src, *dst;

   assert(handle != KHRN_MEM_HANDLE_INVALID);

   header = khrn_mem_header(handle);
   assert(header->ref_count == 1);
   old_size = header->size;

   if (old_size == size)
      return true;

   /* TODO: realloc? */
   new_handle = khrn_mem_alloc_ex(size, "realloc", false, true, false);
   if (new_handle == KHRN_MEM_HANDLE_INVALID)
      return false;

   src = khrn_mem_lock(handle);
   dst = khrn_mem_lock(new_handle);
   if (size > old_size)
   {
      khrn_memcpy(dst, src, old_size);
      khrn_memset((uint8_t *)dst + old_size, 0, size - old_size);
   }
   else
   {
      khrn_memcpy(dst, src, size);
   }
   khrn_mem_unlock(handle);
   khrn_mem_unlock(new_handle);
   khrn_mem_release(handle);
   *handle_inout = new_handle;
   return true;
}

bool khrn_mem_init(void)
{
   khrn_mem_handle_zero_size = khrn_mem_alloc_ex(0, "KHRN_MEM_HANDLE_ZERO_SIZE", false, false, false);
   if (khrn_mem_handle_zero_size == KHRN_MEM_HANDLE_INVALID)
      goto fail0;

   khrn_mem_handle_empty_string = khrn_mem_strdup("");
   if (khrn_mem_handle_empty_string == KHRN_MEM_HANDLE_INVALID)
      goto fail1;

   return true;

fail1:
   khrn_mem_release(khrn_mem_handle_zero_size);
fail0:
   return false;
}

void khrn_mem_term(void)
{
   khrn_mem_release(khrn_mem_handle_zero_size);
   khrn_mem_release(khrn_mem_handle_empty_string);
}

KHRN_MEM_HANDLE_T khrn_mem_strdup(const char *str)
{
   KHRN_MEM_HANDLE_T handle = khrn_mem_alloc_ex(strlen(str) + 1, "khrn_mem_strdup", false, false, false);
   if (handle == KHRN_MEM_HANDLE_INVALID)
      return KHRN_MEM_HANDLE_INVALID;

   vcos_safe_strcpy((char*)khrn_mem_lock(handle), str, strlen(str)+1, 0);
   khrn_mem_unlock(handle);
   return handle;
}

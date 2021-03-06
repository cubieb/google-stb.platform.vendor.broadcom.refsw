/*=============================================================================
Copyright (c) 2015 Broadcom Europe Limited.
All rights reserved.
=============================================================================*/

#ifndef V3D_PRINTER_H
#define V3D_PRINTER_H

/* TODO Move this stuff into another library? It doesn't feel like it really
 * belongs here. */

#include <stdio.h>
#include "vcos_logging.h"

VCOS_EXTERN_C_BEGIN

typedef enum
{
   V3D_PRINTER_STRUCT,
   V3D_PRINTER_ARRAY,
   V3D_PRINTER_UNION
} v3d_printer_container_type_t;

struct v3d_printer_vtbl;

struct v3d_printer
{
   const struct v3d_printer_vtbl *vtbl;
};

struct v3d_printer_vtbl
{
   void (*begin)(struct v3d_printer *root, v3d_printer_container_type_t type, const char *name, bool hidden);
   void (*end)(struct v3d_printer *root);
   void (*field)(struct v3d_printer *root, const char *name, const char *value_format, ...);
   void (*addr_field)(struct v3d_printer *root, const char *name, v3d_addr_t value);
   void (*boolean_field)(struct v3d_printer *root, const char *name, bool value);
};

#define V3D_PRINTER_VTBL_INIT(CLASS)      \
   .begin = CLASS##_begin,                \
   .end = CLASS##_end,                    \
   .field = CLASS##_field,                \
   .addr_field = CLASS##_addr_field,      \
   .boolean_field = CLASS##_boolean_field

extern void v3d_printer_addr_field(struct v3d_printer *root, const char *name, v3d_addr_t value);
extern void v3d_printer_boolean_field(struct v3d_printer *root, const char *name, bool value);

/** v3d_basic_printer */

/* Prints each field on a line of its own as name = value.
 * Not usable directly; use one of the subclasses (v3d_basic_file_printer,
 * v3d_basic_logc_printer, etc). */

struct v3d_basic_printer_line
{
   size_t offset;
   char buf[256];
};

struct v3d_basic_printer_container
{
   v3d_printer_container_type_t type;
   const char *name;
   bool hidden;

   uint32_t indent; /* How many levels to indent children of this container */
   uint32_t skip; /* When printing child names, start at this index in container stack */
};

struct v3d_basic_printer
{
   struct v3d_printer base;

   const char *line_prefix; /* Each line is prefixed with this */
   bool inline_arrays; /* Print arrays of basic types on one line, like array = {0,1,2,3}, rather than one line per elem? */
   size_t name_len_limit; /* Indent and drop container prefix when container name is longer than this */

   struct v3d_basic_printer_container containers[64];
   uint32_t num_containers;

   bool top_c_empty; /* true = no fields/sub-containers in top container yet */

   bool inline_array; /* Top container is array. Printing elements on one line (ia_line). */
   struct v3d_basic_printer_line ia_line;
};

struct v3d_basic_printer_vtbl
{
   struct v3d_printer_vtbl base;
   void (*line)(struct v3d_basic_printer *root, const char *line); /* line does not end with \n */
};

#define V3D_BASIC_PRINTER_VTBL_INIT(CLASS)   \
   .base = {V3D_PRINTER_VTBL_INIT(CLASS)},   \
   .line = CLASS##_line

extern void v3d_basic_printer_begin(struct v3d_printer *root, v3d_printer_container_type_t type, const char *name, bool hidden);
extern void v3d_basic_printer_end(struct v3d_printer *root);
extern void v3d_basic_printer_field(struct v3d_printer *root, const char *name, const char *value_format, ...);
#define v3d_basic_printer_addr_field      v3d_printer_addr_field
#define v3d_basic_printer_boolean_field   v3d_printer_boolean_field

/* Will not setup vtbl. You cannot use v3d_basic_printer directly. Use one of
 * the subclasses instead. */
extern void v3d_basic_printer_init(struct v3d_basic_printer *p,
   const char *line_prefix);

/** v3d_basic_file_printer */

struct v3d_basic_file_printer
{
   struct v3d_basic_printer base;
   FILE *f;
};

#define v3d_basic_file_printer_begin         v3d_basic_printer_begin
#define v3d_basic_file_printer_end           v3d_basic_printer_end
#define v3d_basic_file_printer_field         v3d_basic_printer_field
#define v3d_basic_file_printer_addr_field    v3d_basic_printer_addr_field
#define v3d_basic_file_printer_boolean_field v3d_basic_printer_boolean_field
extern void v3d_basic_file_printer_line(struct v3d_basic_printer *root, const char *line);

extern void v3d_basic_file_printer_init(struct v3d_basic_file_printer *p,
   FILE *f, const char *line_prefix);

/** v3d_basic_logc_printer */

struct v3d_basic_logc_printer
{
   struct v3d_basic_printer base;
   VCOS_LOG_CAT_T *cat;
   VCOS_LOG_LEVEL_T level;
};

#define v3d_basic_logc_printer_begin         v3d_basic_printer_begin
#define v3d_basic_logc_printer_end           v3d_basic_printer_end
#define v3d_basic_logc_printer_field         v3d_basic_printer_field
#define v3d_basic_logc_printer_addr_field    v3d_basic_printer_addr_field
#define v3d_basic_logc_printer_boolean_field v3d_basic_printer_boolean_field
extern void v3d_basic_logc_printer_line(struct v3d_basic_printer *root, const char *line);

extern void v3d_basic_logc_printer_init(struct v3d_basic_logc_printer *p,
   VCOS_LOG_CAT_T *cat, VCOS_LOG_LEVEL_T level, const char *line_prefix);

/** v3d_basic_string_printer */

struct v3d_basic_string_printer
{
   struct v3d_basic_printer base;
   char *buf;
   size_t buf_size;
   size_t offset;
};

#define v3d_basic_string_printer_begin          v3d_basic_printer_begin
#define v3d_basic_string_printer_end            v3d_basic_printer_end
#define v3d_basic_string_printer_field          v3d_basic_printer_field
#define v3d_basic_string_printer_addr_field     v3d_basic_printer_addr_field
#define v3d_basic_string_printer_boolean_field  v3d_basic_printer_boolean_field
extern void v3d_basic_string_printer_line(struct v3d_basic_printer *root, const char *line);

extern void v3d_basic_string_printer_init(struct v3d_basic_string_printer *p,
   char *buf, size_t buf_size, size_t offset);

VCOS_EXTERN_C_END

#endif

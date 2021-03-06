/*=============================================================================
Copyright (c) 2014 Broadcom Europe Limited.
All rights reserved.

Project  :  glsl
Module   :

FILE DESCRIPTION
=============================================================================*/

#ifndef GLSL_SYMBOLS_H
#define GLSL_SYMBOLS_H

#include <stdlib.h>
#include <string.h>

#include "interface/khronos/glxx/gl_public_api.h"

#include "glsl_const_types.h"
#include "glsl_dataflow.h"
#include "glsl_basic_block.h"
#include "glsl_intrinsic_types.h"
#include "glsl_primitive_type_index.auto.h"
#include "glsl_uniform_layout.h"
#include "glsl_precision.h"
#include "glsl_map.h"
#include "glsl_nast.h"

// Defines the representation of symbols.
// Symbols bind names to either _types_ or _instances_.
// e.g. in "int x", "int" and "x" are symbols,
// with "int" a symbol type and "x" a symbol instance.

// SymbolType represents types exclusively.
// Symbol represents types or instances:
// - for instances it has a pointer to a SymbolType struct defining the underlying type, and some metadata;
// - for types it has a pointer to the SymbolType struct defining the new type, and the metadata is invalid.

/* Types. */

typedef enum
{
   SYMBOL_PRIMITIVE_TYPE, // these are canonical - can do pointer match
   SYMBOL_STRUCT_TYPE,    // these are also canonical
   SYMBOL_BLOCK_TYPE,
   SYMBOL_ARRAY_TYPE,     // these are NOT canonical - cannot do pointer match
   SYMBOL_FUNCTION_TYPE,  // these are also NOT canonical
} SymbolTypeFlavour;

typedef struct
{
   PrimitiveTypeIndex index;     /* Can be used to get information from the primitive* arrays */
} PrimitiveType;

typedef struct {
   PrecisionQualifier prec;
   LayoutQualifier *layout;
   SymbolType *type;
   const char *name;
} StructMember;

typedef struct
{
   unsigned int member_count;
   StructMember *member;
} StructType;

typedef struct
{
   unsigned int member_count;
   StructMember *member;

   LayoutQualifier *lq;

   MEMBER_LAYOUT_T *layout;

   bool has_named_instance;
} BlockType;

typedef struct
{
   unsigned int member_count;
   SymbolType *member_type;
} ArrayType;

typedef struct
{
   SymbolType *return_type;
   unsigned int param_count;
   /* params[i]->flavour == SYMBOL_PARAM_INSTANCE for 0 <= i < param_count */
   Symbol **params;
} FunctionType;

/*
   Definition of a 'compile time instance' ptr of a SymbolType t

   ptr must point to a block of size t->scalar_count * sizeof(const_value)
      ...which must be greater than zero

   If t is one of the following primitive types then ptr must point the corresponding C type:
   PRIM_BOOL -> const_bool
   PRIM_BVEC2 -> const_bvec2
   PRIM_BVEC3 -> const_bvec3
   PRIM_BVEC4 -> const_bvec4
   PRIM_INT -> const_int
   PRIM_IVEC2 -> const_ivec2
   PRIM_IVEC3 -> const_ivec3
   PRIM_IVEC4 -> const_ivec4
   PRIM_UINT -> const_uint
   PRIM_UVEC2 -> const_uvec2
   PRIM_UVEC3 -> const_uvec3
   PRIM_UVEC4 -> const_uvec4
   PRIM_FLOAT -> const_float
   PRIM_VEC2 -> const_vec2
   PRIM_VEC3 -> const_vec3
   PRIM_VEC4 -> const_vec4
   PRIM_MAT2 -> const_mat2
   PRIM_MAT3 -> const_mat3
   PRIM_MAT4 -> const_mat4

   If t is an array type then ptr must point to an array of t->member_count compile
   time instances of t->u.array_type.member_type

   If t is a structure type then ptr must point to compile time instances of each of
   t->u.struct_type.member_types
*/

struct _SymbolType
{
   SymbolTypeFlavour flavour;
   const char *name;

   // The number of scalar components in this type, or 0 if not a numeric or bool type.
   unsigned int scalar_count;

   union
   {
      PrimitiveType primitive_type; /* If flavour == SYMBOL_PRIMITIVE_TYPE */
      StructType struct_type;       /* If flavour == SYMBOL_STRUCT_TYPE */
      BlockType block_type;         /* If flavour == SYMBOL_BLOCK_TYPE */
      ArrayType array_type;         /* If flavour == SYMBOL_ARRAY_TYPE */
      FunctionType function_type;   /* If flavour == SYMBOL_FUNCTION_TYPE */
   } u;
};

/* Check that a type conversion from one type to another is valid */
bool glsl_conversion_valid(PrimitiveTypeIndex from, PrimitiveTypeIndex to);

/* Converts a single value between types */
const_value glsl_single_scalar_type_conversion(PrimitiveTypeIndex to_index, PrimitiveTypeIndex from_index, const_value from_val);

// Returns whether the two types are a match.
// This is to be used within a single shader.
bool glsl_shallow_match_nonfunction_types(const SymbolType* a, const SymbolType* b);

// As above but also between shaders where we cannot rely on canonicality.
bool glsl_deep_match_nonfunction_types(const SymbolType *a, const SymbolType *b, bool check_prec);

// Finds the function symbol in a Symbol chain that matches the argument types.
// Note array sizes are part of the type and there is no automatic promotion.
// Returns NULL if none found.
Symbol* glsl_resolve_overload_using_arguments(Symbol* head, ExprChain* args);

// Finds the function symbol in a Symbol chain that matches the declaration.
// Overload resolution is, like glsl_resolve_overload_using_arguments() and as per the GLSL rules,
// based purely on argument types. However, parameter qualifiers and return type
// have to match once an overload is found.
// Returns NULL if none found.
Symbol* glsl_resolve_overload_using_prototype(Symbol* head, SymbolType* prototype);

// Returns whether there is a sampler or an array anywhere in the type t */
bool glsl_type_contains(SymbolType *t, PRIMITIVE_TYPE_FLAGS_T f);
bool glsl_type_contains_opaque(SymbolType *t);
bool glsl_type_contains_array(SymbolType *t);

// There are type->scalar_count scalars in this type.
// Gets the PrimitiveTypeIndex of scalar n.
PrimitiveTypeIndex glsl_get_scalar_value_type_index(const SymbolType* type, unsigned int n);

//
// Symbols.
//

typedef enum
{
   SYMBOL_TYPE,              // named type, used by the lexer to return TYPE_NAME
   SYMBOL_INTERFACE_BLOCK,   // interface block
   SYMBOL_VAR_INSTANCE,      // normal variable (instance of primitive/array/struct)
   SYMBOL_PARAM_INSTANCE,    // function parameter (instance of primitive/array/struct)
   SYMBOL_FUNCTION_INSTANCE, // function definition (or declaration, to be later upgraded to definition)
   SYMBOL_TEMPORARY // intermediate compiler values
} SymbolFlavour;

typedef void (*FoldingFunction)(void);

struct _Symbol
{
   const char *name;
   int line_num;
   SymbolFlavour flavour;

   /*
      Defined for types, instances and members, though the semantics are slightly different

      If flavour in {SYMBOL_VAR_INSTANCE, SYMBOL_PARAM_INSTANCE} then
         type->flavour in {SYMBOL_PRIMITIVE_TYPE,SYMBOL_STRUCT_TYPE,SYMBOL_ARRAY_TYPE}

      If flavour == SYMBOL_FUNCTION_INSTANCE then
         type->flavour == SYMBOL_FUNCTION_TYPE
   */
   SymbolType *type;

   union
   {
      /* Validity: flavour == SYMBOL_VAR_INSTANCE */
      struct
      {
         int  layout_location;
         bool layout_loc_specified;

         int  layout_binding;
         bool layout_bind_specified;

         int offset;
         int offset_specified;

         TypeQualifier      type_qual;
         StorageQualifier   storage_qual;
         PrecisionQualifier prec_qual;

         /* For const var_instances points to compile time value, otherwise NULL */
         const_value *compile_time_value;

         bool block_info_valid;
         struct
         {
            /* If this is a default-block uniform then block_symbol is NULL  *
             * otherwise it points to the entry in the interface block table */
            Symbol *block_symbol;

            /* For default-block this points to a dummy */
            MEMBER_LAYOUT_T *layout;
         } block_info;
      } var_instance;

      /* Validity: flavour == SYMBOL_PARAM_INSTANCE */
      struct
      {
         StorageQualifier   storage_qual; /* Only NONE or CONST */
         ParamQualifier     param_qual;
         PrecisionQualifier prec_qual;
         MemoryQualifier    mem_qual;
      } param_instance;

      /* Validity: flavour == SYMBOL_FUNCTION_INSTANCE */
      struct
      {
         /* A function to constant fold this invocation, or NULL if we can't constant fold it */
         FoldingFunction folding_function;
         /* AST function definition: as STATEMENT_FUNCTION_DEF, or NULL for declarations */
         Statement      *function_def;
         /* ES2 requires at most 1 declaration that is not a definition */
         bool            has_prototype;
         /* NSTMT_FUNCTION_DEF */
         const NStmt    *function_norm_def;
         /* The next overload of this function - a SYMBOL_FUNCTION_INSTANCE, or NULL if none */
         Symbol         *next_overload;
      } function_instance;

      struct {
         StorageQualifier sq;

         int  layout_binding;
         bool layout_bind_specified;
      } interface_block;
   } u;
};

//
// Symbol constructors.
//

void glsl_symbol_construct_type(Symbol* result, SymbolType* type);
void glsl_symbol_construct_interface_block(Symbol *result, const char *name, FullySpecType *fs_type);
void glsl_symbol_construct_var_instance(Symbol* result, const char* name, FullySpecType* fs_type, void* compile_time_value, Symbol* block_symbol);
void glsl_symbol_construct_param_instance(Symbol *result, const char *name, SymbolType *type, StorageQualifier sq, ParamQualifier pq);
void glsl_symbol_construct_function_instance(Symbol *result, const char *name, SymbolType *type, FoldingFunction folding_function, Symbol *next_overload, bool has_prototype);
void glsl_symbol_construct_struct_member(Symbol* result, const char* name, FullySpecType* fs_type);
void glsl_symbol_construct_block_member(Symbol* result, const char* name, FullySpecType* fs_type);
Symbol* glsl_symbol_construct_temporary(SymbolType* type);

Dataflow** glsl_symbol_get_default_scalar_values(const Symbol* symbol);

//
// Function call metadata.
//

typedef enum
{
   CALL_CONTEXT_FUNCTION,
   CALL_CONTEXT_CONSTRUCTOR,
   CALL_CONTEXT_INTRINSIC
} CallContextFlavour;

struct _CallContext
{
   CallContextFlavour flavour;

   union {
      struct {
         Symbol *symbol;
      } function;

      struct {
         SymbolType *type;
      } constructor;

      struct {
         glsl_intrinsic_index_t flavour;
      } intrinsic;
   } u;
};


typedef struct _SymbolListNode {
   Symbol *s;
   struct _SymbolListNode *prev;
   struct _SymbolListNode *next;
} SymbolListNode;

typedef struct _SymbolList {
   SymbolListNode *head;
   SymbolListNode *tail;
} SymbolList;

SymbolList *glsl_symbol_list_new(void);
void glsl_symbol_list_append(SymbolList *list, Symbol *s);
void glsl_symbol_list_pop(SymbolList *list);
bool glsl_symbol_list_contains(const SymbolList *list, Symbol *value);


#endif // SYMBOLS_H

/**
 *  process with: bison -v -d -o glsl_parser.c glsl_parser.y
 *  (-v for debugging, not needed for release).
 *  (-d to produce glsl_parser.h, NEEDED for release).
 */

%{
   #include <stdlib.h>
   #include <stdio.h>
   #include <string.h>
   #include <limits.h>
   #include <assert.h>

   #include "vcos_string.h"

   #include "glsl_common.h"
   #include "glsl_symbols.h"
   #include "glsl_errors.h"
   #include "glsl_intern.h"
   #include "glsl_globals.h"
   #include "glsl_builders.h"
   #include "glsl_extensions.h"
   #include "glsl_intrinsic.h"
   #include "glsl_ast.h"
   #include "glsl_ast_visitor.h"
   #include "glsl_symbol_table.h"
   #include "glsl_primitive_types.auto.h"

   #include "glsl_stdlib.auto.h"
   #include "glsl_unique_index_queue.h"

   #include "glsl_quals.h"
   #include "glsl_layout.h"

   // External declaration of glsl_parse_ast(). This is hacky, but putting it in the right place (glsl_parser.h)
   // fails due to windows/windef.h namespace conflicts.
   #include "glsl_compiler.h"

   #include "prepro/glsl_prepro_token.h"
   #include "prepro/glsl_prepro_expand.h"
   #include "prepro/glsl_prepro_directive.h"

   // for 'malloc_fast'
   #include "glsl_fastmem.h"

   #define PS ((struct parse_state *)state)

   extern void glsl_init_preprocessor (void);

   bool glsl_find_version(int sourcec, const char *const *sourcev, int *version);

   void glsl_init_lexer (int sourcec, const char * const *sourcev);
   void glsl_term_lexer (void);
   const char* glsl_keyword_to_string(TokenType token);

   struct parse_state {
      Statement *astp;
      bool in_struct;

      SymbolTable *symbol_table;

      LayoutQualifier *buffer_default_lq;
      LayoutQualifier *uniform_default_lq;
      unsigned int atomic_buffer_offset[GLXX_CONFIG_MAX_ATOMIC_COUNTER_BUFFER_BINDINGS];
      FunctionBuilder function_builder;

      PrecisionTable *precision_table;
   };

   int yyparse (void *state);

   static TokenSeq *seq;

   static bool force_identifier;
   static bool user_code;

   static void find_stdlib_function_calls(Expr *e, void *data) {
      GLSL_UNIQUE_INDEX_QUEUE_T *q = data;
      if (e->flavour == EXPR_FUNCTION_CALL) {
         Symbol *function = e->u.function_call.function;
         if (glsl_stdlib_is_stdlib_symbol(function)) {
            glsl_unique_index_queue_add(q, glsl_stdlib_function_index(function));
         }
      }
   }

   Statement *glsl_parse_ast (ShaderFlavour flavour, int sourcec, const char * const *sourcev)
   {
      struct parse_state state;   /* TODO: Contains lots of nastiness, but this beats global */
      int user_version;
      GLSL_UNIQUE_INDEX_QUEUE_T *stdlib_functions;

      g_ShaderFlavour = flavour;
      if (!glsl_find_version(sourcec, sourcev, &g_ShaderVersion))
         glsl_compile_error(ERROR_PREPROCESSOR, 5, -1, "Invalid or unsupported version");

      state.symbol_table = glsl_symbol_table_new();

      g_ShaderInterfaces = glsl_shader_interfaces_new();
      g_InGlobalScope = true;

      glsl_symbol_table_populate(state.symbol_table, g_ShaderFlavour, g_ShaderVersion);

      state.in_struct = false;
      glsl_reinit_function_builder(&state.function_builder);

      /* Set up the root precision table with default precisions */
      state.precision_table = NULL;
      state.precision_table = glsl_prec_add_table( state.precision_table );
      glsl_prec_set_defaults( state.precision_table, g_ShaderVersion, g_ShaderFlavour );

      state.buffer_default_lq = malloc_fast(sizeof(LayoutQualifier));
      state.buffer_default_lq->qualified = UNIF_QUALED;
      state.buffer_default_lq->unif_bits = LAYOUT_SHARED | LAYOUT_COLUMN_MAJOR;

      state.uniform_default_lq = malloc_fast(sizeof(LayoutQualifier));
      state.uniform_default_lq->qualified = UNIF_QUALED;
      state.uniform_default_lq->unif_bits = LAYOUT_SHARED | LAYOUT_COLUMN_MAJOR;

      for (int i=0; i<GLXX_CONFIG_MAX_ATOMIC_COUNTER_BUFFER_BINDINGS; i++)
         state.atomic_buffer_offset[i] = 0;

      force_identifier = false;

      seq = NULL;

      glsl_compile_error_reset();

      stdlib_functions = glsl_unique_index_queue_alloc(GLSL_STDLIB_FUNCTION_COUNT);
      user_code = true;

      glsl_init_preprocessor();
      glsl_init_lexer(sourcec, sourcev);
      yyparse(&state);
      glsl_term_lexer();

      Statement *ast = state.astp;

      /* Now process the standard library functions that we've used */
      glsl_symbol_table_exit_scope(state.symbol_table);
      glsl_directive_reset_macros();
      user_version    = g_ShaderVersion;
      g_ShaderVersion = GLSL_SHADER_VERSION(3, 10, 1);
      user_code = false;

      glsl_statement_accept_postfix(ast, stdlib_functions, NULL, find_stdlib_function_calls);

      /* Gather the actual sources here, then run yyparse again */
      while(!glsl_unique_index_queue_empty(stdlib_functions)) {
         const char *srcp[GLSL_STDLIB_FUNCTION_COUNT+1];
         int srcc = 0;

         /* XXX We process the stdlib setup multiple times here. This is wasteful but should work */
         if(glsl_stdlib_setup != NULL) srcp[srcc++] = glsl_stdlib_setup;
         while (!glsl_unique_index_queue_empty(stdlib_functions))
            srcp[srcc++] = glsl_stdlib_function_bodies[glsl_unique_index_queue_remove(stdlib_functions)];

         glsl_init_lexer(srcc,srcp);
         yyparse(&state);
         glsl_term_lexer();

         glsl_statement_accept_postfix(state.astp, stdlib_functions, NULL, find_stdlib_function_calls);

         /* Hackily append the declaration to the ast decls chain */
         StatementChain *c = ast->u.ast.decls;
         StatementChainNode *n = state.astp->u.ast.decls->first;
         while (n != NULL) {
            glsl_statement_chain_append(c, n->statement);
            n = n->next;
         }
      }

      g_ShaderVersion = user_version;
      // This is a bit nasty, but means that future ast constructions
      // will not appear to be from the last line.
      g_LineNumber = LINE_NUMBER_UNDEFINED;

      return ast;
   }

   bool glsl_parsing_user_code() { return user_code && glsl_lexer_in_user_code(); }

   static void yyerror (void *state, const char *s)
   {
      if (strcmp(s, "syntax error") == 0) {
         // Catch syntax errors and redirect them.
         glsl_compile_error(ERROR_LEXER_PARSER, 1, g_LineNumber, NULL);
      } else {
         glsl_compile_error(ERROR_UNKNOWN, 0, g_LineNumber, "%s", s);
      }
   }

   static int yylex (YYSTYPE *yylvalp, SymbolTable *main_symbol_table)
   {
      TokenType type = 0;
      TokenData data;

      do
      {
         if(!seq)
         {
            seq = glsl_expand(NULL, false);
            if(!seq)
               return 0;
         }

         type = seq->token->type;
         data = seq->token->data;
         seq = seq->next;
      } while (type==WHITESPACE);

      if (type == INVALID_CHAR)
         glsl_compile_error(ERROR_LEXER_PARSER, 1, g_LineNumber, "invalid characters: %s", data.s);

      /* detect uses of reserved keywords (anything from the list, or anything containing '__') */
      if (KEYWORDS_BEGIN < type && type < KEYWORDS_END) {
         KeywordFlags keyword_flag, reserved_flag;
         switch(g_ShaderVersion) {
            case GLSL_SHADER_VERSION(1, 0, 1):
               keyword_flag = GLSL_ES_1_KEYWORD; reserved_flag = GLSL_ES_1_RESERVED;
               break;
            case GLSL_SHADER_VERSION(3, 0, 1):
               keyword_flag = GLSL_ES_3_KEYWORD; reserved_flag = GLSL_ES_3_RESERVED;
               break;
            case GLSL_SHADER_VERSION(3, 10, 1):
               keyword_flag = GLSL_ES_31_KEYWORD; reserved_flag = GLSL_ES_31_RESERVED;
               break;
            case GLSL_SHADER_VERSION(3, 20, 1):
               keyword_flag = GLSL_ES_32_KEYWORD; reserved_flag = GLSL_ES_32_RESERVED;
               break;
            default: UNREACHABLE();
         }

         if (data.flags & reserved_flag)
            glsl_compile_error(ERROR_LEXER_PARSER, 3, g_LineNumber, "%s", glsl_keyword_to_string(type));
         if (!(data.flags & keyword_flag)) {
            // it is not keyword in this GLSL version, convert it back to identifier
            data.s = glsl_keyword_to_string(type);
            type = IDENTIFIER;
         }
      }

      /* detokenize tokens which were meaningful to the preprocessor */
      if (KEYWORDS_BEGIN < type && type < KEYWORDS_END && (data.flags & PREPROC_KEYWORD) != 0)
      {
         data.s = glsl_keyword_to_string(type);
         type = IDENTIFIER;
      }
      else if (type == PPNUMBER)
      {
         Token *token = glsl_lex_ppnumber(glsl_token_construct(type, data));
         type = token->type;
         data = token->data;
      }

      switch (type) {
      case IDENTIFIER:
      {
         Symbol *sym = glsl_symbol_table_lookup(main_symbol_table, data.s);
         yylvalp->lookup.symbol = sym;
         yylvalp->lookup.name = data.s;
         /* If this names a type return TYPE_NAME unless identifier is forced */
         if (sym && sym->flavour == SYMBOL_TYPE) {
            if(!force_identifier) type = TYPE_NAME;
         }
         break;
      }
      case INTRINSIC:
      {
         if(glsl_parsing_user_code()) {
            glsl_compile_error(ERROR_LEXER_PARSER, 1, g_LineNumber, "invalid character");
         } else {
            /* lookup must always succeed, since this is in the stdlib */
            const glsl_intrinsic_data_t *lookup = glsl_intrinsic_lookup(data.s, strlen(data.s));
            yylvalp->intrinsic = lookup->index;
         }
         break;
      }
      case BOOLCONSTANT:
      case INTCONSTANT:
      case UINTCONSTANT:
      case FLOATCONSTANT:
         yylvalp->v = data.v;
         break;
      default:
         break;
      }

      return type;
   }

   #define YYMALLOC yymalloc
   #define YYFREE yyfree

   void *yymalloc (size_t bytes) { return malloc_fast(bytes); }
   void  yyfree   (void *ptr)    { UNUSED(ptr); }

   static void enter_scope(struct parse_state *state)
   {
      glsl_symbol_table_enter_scope(state->symbol_table);
      state->precision_table = glsl_prec_add_table( state->precision_table );
   }

   static void exit_scope(struct parse_state *state)
   {
      glsl_symbol_table_exit_scope(state->symbol_table);
      state->precision_table = glsl_prec_delete_table( state->precision_table );
   }

   static void validate_symbol_lookup(const Symbol *s, const char *name) {
      if(!s)
         glsl_compile_error(ERROR_LEXER_PARSER, 2, g_LineNumber, "%s", name);
   }

   static Statement *process_block_decl(struct parse_state *state, QualList *quals, const char *block_name,
                                        StatementChain *type_members, const char *instance_name, ExprChain *array_size)
   {
      FullySpecType  fs_type;
      Qualifiers     q;
      qualifiers_from_list(&q, quals);
      if (q.sq == STORAGE_UNIFORM)
         q.lq = glsl_create_mixed_lq(q.lq, state->uniform_default_lq);
      if (q.sq == STORAGE_BUFFER)
         q.lq = glsl_create_mixed_lq(q.lq, state->buffer_default_lq);

      fs_type.type  = glsl_build_block_type(&q, block_name, type_members);
      fs_type.quals = q;
      if (array_size != NULL)
         fs_type.type = glsl_build_array_type(fs_type.type, array_size);

      Symbol *block_symbol = glsl_commit_block_type(state->symbol_table, &fs_type);

      if (instance_name) {
         Symbol *instance_symbol = glsl_commit_var_instance(state->symbol_table, instance_name, &fs_type, NULL, NULL);
         return glsl_statement_construct_var_decl(quals, fs_type.type, instance_symbol, NULL);
      } else {
         glsl_commit_anonymous_block_members(state->symbol_table, block_symbol);
         return glsl_statement_construct(STATEMENT_NULL);
      }
   }

#define main_symbol_table (PS->symbol_table)
%}

// Create a reentrant, pure parser:
%define api.pure
%lex-param { SymbolTable *main_symbol_table }
%parse-param { void *state }
//%token-table       // for debugging: include token table:
%verbose             // for debugging: emit *.output file with parser states
%expect 1            // 1 shift/reduce conflict (if/else, default behaviour's fine)

%start translation_unit

// Yacc's value stack type.
%union {
   const char* s;
   const_value v;
   struct { const char* name; Symbol* symbol; } lookup;
   Symbol *symbol;
   SymbolList *symbol_list;
   CallContext call_context;
   struct { const char *name; SymbolType *type; } func_proto;
   ExprFlavour expr_flavour;
   Expr *expr;
   ExprChain *expr_chain;
   glsl_intrinsic_index_t intrinsic;
   struct { QualList *quals; SymbolType *type; Statement *s; } decl;
   struct { QualList *quals; SymbolType *type; StatementChain *ch; } decl_chain;
   Statement *statement;
   StatementChain *statement_chain;
   struct { Statement *t; Statement *f; } selection_rest;
   struct { Statement *cond_or_decl; Expr *iter; } for_rest;
   SymbolType *type;
   QualList  *qual_list;
   Qualifier *qualifier;
   StorageQualifier       storage_qual;
   AuxiliaryQualifier     auxiliary_qual;
   MemoryQualifier        memory_qual;
   PrecisionQualifier     prec_qual;
   InterpolationQualifier interp_qual;
   struct { const char *name; ExprChain *size; } declarator;
   struct { const char *name; ExprChain *size; Expr *init; } init_declarator;
   LayoutQualifier *layout_qual;
   LayoutID *lq_id;
   LayoutIDList *lq_id_list;
   struct { QualList *quals; SymbolType *type; } fs_type;
}

%token KEYWORDS_BEGIN // mark; not a real token

// list of keywords from GLSL ES Specification 1.0.17 and GLSL ES Specification 3.00.4
// keywords "true" and "false" are lexed as BOOLCONSTANT
%token ACTIVE
%token ASM
%token ATOMIC_UINT
%token ATTRIBUTE
%token BOOL
%token BREAK
%token BUFFER
%token BVEC2
%token BVEC3
%token BVEC4
%token CASE
%token CAST
%token CENTROID
%token CLASS
%token COHERENT
%token COMMON
%token CONST
%token CONTINUE
%token DEFAULT
%token DISCARD
%token DMAT2
%token DMAT2X2
%token DMAT2X3
%token DMAT2X4
%token DMAT3
%token DMAT3X2
%token DMAT3X3
%token DMAT3X4
%token DMAT4
%token DMAT4X2
%token DMAT4X3
%token DMAT4X4
%token DO
%token DOUBLE
%token DVEC2
%token DVEC3
%token DVEC4
%token ELSE
%token ENUM
%token EXTERN
%token EXTERNAL
%token FILTER
%token FIXED
%token FLAT
%token FLOAT
%token FOR
%token FVEC2
%token FVEC3
%token FVEC4
%token GOTO
%token HALF
%token HIGH_PRECISION
%token HVEC2
%token HVEC3
%token HVEC4
%token IF
%token IIMAGE1D
%token IIMAGE1DARRAY
%token IIMAGE2D
%token IIMAGE2DARRAY
%token IIMAGE2DMS
%token IIMAGE2DMSARRAY
%token IIMAGE2DRECT
%token IIMAGE3D
%token IIMAGEBUFFER
%token IIMAGECUBE
%token IIMAGECUBEARRAY
%token IMAGE1D
%token IMAGE1DARRAY
%token IMAGE1DARRAYSHADOW
%token IMAGE1DSHADOW
%token IMAGE2D
%token IMAGE2DARRAY
%token IMAGE2DMS
%token IMAGE2DMSARRAY
%token IMAGE2DRECT
%token IMAGE2DARRAYSHADOW
%token IMAGE2DSHADOW
%token IMAGE3D
%token IMAGEBUFFER
%token IMAGECUBE
%token IMAGECUBEARRAY
%token IN
%token _INLINE
%token INOUT
%token INPUT
%token INT
%token INTERFACE
%token INVARIANT
%token ISAMPLER1D
%token ISAMPLER1DARRAY
%token ISAMPLER2D
%token ISAMPLER2DARRAY
%token ISAMPLER2DMS
%token ISAMPLER2DMSARRAY
%token ISAMPLER2DRECT
%token ISAMPLER3D
%token ISAMPLERBUFFER
%token ISAMPLERCUBE
%token ISAMPLERCUBEARRAY
%token IVEC2
%token IVEC3
%token IVEC4
%token LAYOUT
%token LONG
%token LOW_PRECISION
%token MAT2
%token MAT2X2
%token MAT2X3
%token MAT2X4
%token MAT3
%token MAT3X2
%token MAT3X3
%token MAT3X4
%token MAT4
%token MAT4X2
%token MAT4X3
%token MAT4X4
%token MEDIUM_PRECISION
%token NAMESPACE
%token NOINLINE
%token NOPERSPECTIVE
%token OUT
%token OUTPUT
%token PACKED
%token PARTITION
%token PATCH
%token PRECISE
%token PRECISION
%token PUBLIC
%token READONLY
%token RESOURCE
%token RESTRICT
%token RETURN
%token SAMPLE
%token SAMPLER1D
%token SAMPLER1DARRAY
%token SAMPLER1DARRAYSHADOW
%token SAMPLER1DSHADOW
%token SAMPLER2D
%token SAMPLER2DARRAY
%token SAMPLER2DARRAYSHADOW
%token SAMPLER2DMS
%token SAMPLER2DMSARRAY
%token SAMPLER2DRECT
%token SAMPLER2DRECTSHADOW
%token SAMPLER2DSHADOW
%token SAMPLER3D
%token SAMPLER3DRECT
%token SAMPLERBUFFER
%token SAMPLERCUBE
%token SAMPLERCUBEARRAY
%token SAMPLERCUBEARRAYSHADOW
%token SAMPLERCUBESHADOW
%token SHARED
%token SHORT
%token SIZEOF
%token SMOOTH
%token STATIC
%token STRUCT
%token SUBROUTINE
%token SUPERP
%token SWITCH
%token TEMPLATE
%token THIS
%token TYPEDEF
%token UIMAGE1D
%token UIMAGE1DARRAY
%token UIMAGE2D
%token UIMAGE2DARRAY
%token UIMAGE2DMS
%token UIMAGE2DMSARRAY
%token UIMAGE2DRECT
%token UIMAGE3D
%token UIMAGEBUFFER
%token UIMAGECUBE
%token UIMAGECUBEARRAY
%token UINT
%token UNIFORM
%token UNION
%token UNSIGNED
%token USAMPLER1D
%token USAMPLER1DARRAY
%token USAMPLER2D
%token USAMPLER2DARRAY
%token USAMPLER2DMS
%token USAMPLER2DMSARRAY
%token USAMPLER2DRECT
%token USAMPLER3D
%token USAMPLERBUFFER
%token USAMPLERCUBE
%token USAMPLERCUBEARRAY
%token USING
%token UVEC2
%token UVEC3
%token UVEC4
%token VARYING
%token VEC2
%token VEC3
%token VEC4
%token VOID
%token VOLATILE
%token WHILE
%token WRITEONLY
// end of specification keywords

// Extension keywords
%token SAMPLEREXTERNAL

// Preprocessor-only keywords
%token DEFINE
%token UNDEF
%token IFDEF
%token IFNDEF
%token ELIF
%token ENDIF
%token ERROR
%token PRAGMA
%token EXTENSION
%token VERSION
%token LINE
%token ALL
%token REQUIRE
%token ENABLE
%token WARN
%token DISABLE

%token KEYWORDS_END // mark; not a real token

%token IDENTIFIER TYPE_NAME FLOATCONSTANT INTCONSTANT UINTCONSTANT BOOLCONSTANT
// -- not parseable using a LR parser, we use IDENTIFIER instead: %token FIELD_SELECTION
%token LEFT_OP RIGHT_OP
%token INC_OP DEC_OP LE_OP GE_OP EQ_OP NE_OP
%token AND_OP OR_OP XOR_OP MUL_ASSIGN DIV_ASSIGN ADD_ASSIGN
%token MOD_ASSIGN LEFT_ASSIGN RIGHT_ASSIGN AND_ASSIGN XOR_ASSIGN OR_ASSIGN
%token SUB_ASSIGN
%token LEFT_PAREN RIGHT_PAREN LEFT_BRACKET RIGHT_BRACKET LEFT_BRACE RIGHT_BRACE DOT
%token COMMA COLON EQUAL SEMICOLON BANG DASH TILDE PLUS STAR SLASH PERCENT
%token LEFT_ANGLE RIGHT_ANGLE VERTICAL_BAR CARET AMPERSAND QUESTION

// intrinsics
%token INTRINSIC

%type<lookup> IDENTIFIER
%type<v> INTCONSTANT UINTCONSTANT FLOATCONSTANT BOOLCONSTANT

/* preprocessor tokens: */
%token HASH
%token WHITESPACE
%token NEWLINE
%token PPNUMBER
%token BACKSLASH
%token INVALID_CHAR

%type<lookup> TYPE_NAME
%type<lookup> variable_identifier
%type<lookup> identifier_or_typename

%type<call_context> function_identifier

%type<expr_chain> function_argument_list
%type<expr_chain> assignment_expression_list

%type<expr> primary_expression postfix_expression integer_expression
%type<expr> function_call
%type<expr> unary_expression
%type<expr> multiplicative_expression
%type<expr> additive_expression
%type<expr> shift_expression
%type<expr> relational_expression
%type<expr> equality_expression
%type<expr> and_expression
%type<expr> exclusive_or_expression
%type<expr> inclusive_or_expression
%type<expr> logical_and_expression
%type<expr> logical_xor_expression
%type<expr> logical_or_expression
%type<expr> conditional_expression
%type<expr> assignment_expression
%type<expr> initializer
%type<expr> expression
%type<expr> constant_expression

%type<expr_flavour> assignment_operator
%type<intrinsic> INTRINSIC

%type<func_proto> function_prototype

%type<decl> single_declaration
%type<init_declarator> init_declarator
%type<decl_chain> init_declarator_list
%type<symbol_list> identifier_list

%type<statement> declaration
%type<statement> declaration_statement
%type<statement> simple_statement
%type<statement> statement
%type<statement> statement_no_new_scope
%type<statement> compound_statement_no_new_scope
%type<statement_chain> statement_list switch_statement_list
%type<statement> expression_statement
%type<statement> selection_statement
%type<statement> iteration_statement
%type<statement> switch_statement
%type<statement> case_label
%type<statement> jump_statement
%type<statement> translation_unit external_declaration function_definition
%type<statement> statement_with_scope compound_statement_with_scope
%type<statement> for_init_statement
%type<statement> condition
%type<statement> conditionopt

%type<selection_rest> selection_rest_statement
%type<for_rest> for_rest_statement

%type<statement_chain> struct_declaration_list struct_declaration_list_inner struct_declarator_list
%type<statement> struct_declaration

%type<type> struct_specifier type_specifier type_specifier_nonarray
%type<expr_chain> array_specifier

%type<storage_qual>   storage_qualifier
%type<auxiliary_qual> auxiliary_qualifier
%type<memory_qual>    memory_qualifier
%type<interp_qual>    interpolation_qualifier
%type<prec_qual>      precision_qualifier
%type<lq_id>          layout_qualifier_id
%type<lq_id_list>     layout_qualifier_id_list
%type<lq_id_list>     layout_qualifier

%type<qualifier> single_type_qualifier
%type<qual_list> type_qualifier

%type<declarator> declarator

%type<fs_type> fully_specified_type

%type<v> unary_operator

%%

variable_identifier
   : IDENTIFIER
   ;

primary_expression
   : variable_identifier                { validate_symbol_lookup($1.symbol, $1.name);
                                          $$ = glsl_expr_construct_instance($1.symbol); }
   | INTCONSTANT                        { $$ = glsl_expr_construct_const_value(PRIM_INT,  $1); }
   | UINTCONSTANT                       { $$ = glsl_expr_construct_const_value(PRIM_UINT, $1); }
   | FLOATCONSTANT                      { $$ = glsl_expr_construct_const_value(PRIM_FLOAT,$1); }
   | BOOLCONSTANT                       { $$ = glsl_expr_construct_const_value(PRIM_BOOL, $1); }
   | LEFT_PAREN expression RIGHT_PAREN  { $$ = $2; }
   ;

postfix_expression
   : primary_expression
   | postfix_expression LEFT_BRACKET integer_expression RIGHT_BRACKET
                                                      { $$ = glsl_expr_construct_subscript($1, $3); }
   | function_call
// -- not parseable using an LR parser, we use IDENTIFIER instead:
// | postfix_expression DOT FIELD_SELECTION         { $$ = glsl_expr_construct_field_selector($1, $3); }
/* We need to force the lexer to return IDENTIFIER in case struct/block members have the same names as types:
   ('force_identifier' is placed before DOT to ensure its semantic action is taken before IDENTIFIER is lexed as the lookahead token.) */
   | postfix_expression force_identifier DOT IDENTIFIER unforce_identifier { $$ = glsl_expr_construct_field_selector($1, $4.name); }
   | postfix_expression INC_OP                                             { $$ = glsl_expr_construct_unary_op(EXPR_POST_INC, $1); }
   | postfix_expression DEC_OP                                             { $$ = glsl_expr_construct_unary_op(EXPR_POST_DEC, $1); }
   ;

integer_expression
   : expression
   ;

function_call
   : function_identifier LEFT_PAREN function_argument_list RIGHT_PAREN {
      switch($1.flavour) {
      case CALL_CONTEXT_FUNCTION:
         $$ = glsl_expr_construct_function_call   ($1.u.function.symbol,   $3);
         break;
      case CALL_CONTEXT_CONSTRUCTOR:
         $$ = glsl_expr_construct_constructor_call($1.u.constructor.type,  $3);
         break;
      case CALL_CONTEXT_INTRINSIC:
         $$ = glsl_intrinsic_construct_expr       ($1.u.intrinsic.flavour, $3);
         break;
      default:
         UNREACHABLE();
         break;
      }
   }
   /* Here 'force_identifier' and 'unforce_identifier' are needed to avoid a
      conflict with the third derivation rule for 'postfix_expression' */
   | postfix_expression force_identifier DOT function_identifier unforce_identifier LEFT_PAREN RIGHT_PAREN {
       $$ = glsl_expr_construct_method_call($1, &($4));
   }
   ;

force_identifier
   : { force_identifier = true; }
   ;

unforce_identifier
   : { force_identifier = false; }
   ;

function_argument_list
   : /* empty */                 { $$ = glsl_expr_chain_create(); }
   | VOID                        { $$ = glsl_expr_chain_create(); }
   | assignment_expression_list  { $$ = $1; }
   ;

assignment_expression_list
   : assignment_expression            { $$ = glsl_expr_chain_append(glsl_expr_chain_create(), $1); }
   | assignment_expression_list COMMA assignment_expression { $$ = glsl_expr_chain_append($1, $3); }
   ;

/* Grammar Note: Constructors look like functions, but lexical analysis recognized most of them as */
/* keywords. They are now recognized through type_specifier. */
function_identifier
   : type_specifier                                   { $$.flavour             = CALL_CONTEXT_CONSTRUCTOR;
                                                        $$.u.constructor.type  = $1;
                                                      }
   | IDENTIFIER  /* or FIELD_SELECTION */             { $$.flavour             = CALL_CONTEXT_FUNCTION;
                                                        $$.u.function.symbol   = $1.symbol;
                                                      }
   | INTRINSIC   /* Extensions: */                    { $$.flavour             = CALL_CONTEXT_INTRINSIC;
                                                        $$.u.intrinsic.flavour = $1;
                                                      }
   ;

unary_expression
   : postfix_expression
   | INC_OP unary_expression                          { $$ = glsl_expr_construct_unary_op(EXPR_PRE_INC, $2); }
   | DEC_OP unary_expression                          { $$ = glsl_expr_construct_unary_op(EXPR_PRE_DEC, $2); }
   | unary_operator unary_expression                  { $$ = glsl_expr_construct_unary_op($1, $2); }
   /* Grammar Note: No traditional style type casts. */
   ;

unary_operator
   : PLUS                                             { $$ = EXPR_ADD; }
   | DASH                                             { $$ = EXPR_ARITH_NEGATE; }
   | BANG                                             { $$ = EXPR_LOGICAL_NOT; }
   | TILDE                                            { $$ = EXPR_BITWISE_NOT; }
   /* Grammar Note: No '*' or '&' unary ops. Pointers are not supported. */
   ;

multiplicative_expression
   : unary_expression
   | multiplicative_expression STAR unary_expression  { $$ = glsl_expr_construct_binary_op_arithmetic(EXPR_MUL, $1, $3); }
   | multiplicative_expression SLASH unary_expression { $$ = glsl_expr_construct_binary_op_arithmetic(EXPR_DIV, $1, $3); }
   | multiplicative_expression PERCENT unary_expression { $$ = glsl_expr_construct_binary_op_arithmetic(EXPR_REM, $1, $3); }
   ;

additive_expression
   : multiplicative_expression
   | additive_expression PLUS multiplicative_expression { $$ = glsl_expr_construct_binary_op_arithmetic(EXPR_ADD, $1, $3); }
   | additive_expression DASH multiplicative_expression { $$ = glsl_expr_construct_binary_op_arithmetic(EXPR_SUB, $1, $3); }
   ;

shift_expression
   : additive_expression
   | shift_expression LEFT_OP additive_expression     { $$ = glsl_expr_construct_binary_op_shift(EXPR_SHL, $1, $3); }
   | shift_expression RIGHT_OP additive_expression    { $$ = glsl_expr_construct_binary_op_shift(EXPR_SHR, $1, $3); }
   ;

relational_expression
   : shift_expression
   | relational_expression LEFT_ANGLE shift_expression { $$ = glsl_expr_construct_binary_op_relational(EXPR_LESS_THAN, $1, $3); }
   | relational_expression RIGHT_ANGLE shift_expression { $$ = glsl_expr_construct_binary_op_relational(EXPR_GREATER_THAN, $1, $3); }
   | relational_expression LE_OP shift_expression { $$ = glsl_expr_construct_binary_op_relational(EXPR_LESS_THAN_EQUAL, $1, $3); }
   | relational_expression GE_OP shift_expression { $$ = glsl_expr_construct_binary_op_relational(EXPR_GREATER_THAN_EQUAL, $1, $3); }
   ;

equality_expression
   : relational_expression
   | equality_expression EQ_OP relational_expression { $$ = glsl_expr_construct_binary_op_equality(EXPR_EQUAL, $1, $3); }
   | equality_expression NE_OP relational_expression { $$ = glsl_expr_construct_binary_op_equality(EXPR_NOT_EQUAL, $1, $3); }
   ;

and_expression
   : equality_expression
   | and_expression AMPERSAND equality_expression     { $$ = glsl_expr_construct_binary_op_bitwise(EXPR_BITWISE_AND, $1, $3); }
   ;

exclusive_or_expression
   : and_expression
   | exclusive_or_expression CARET and_expression     { $$ = glsl_expr_construct_binary_op_bitwise(EXPR_BITWISE_XOR, $1, $3); }
   ;

inclusive_or_expression
   : exclusive_or_expression
   | inclusive_or_expression VERTICAL_BAR exclusive_or_expression { $$ = glsl_expr_construct_binary_op_bitwise(EXPR_BITWISE_OR, $1, $3); }
   ;

logical_and_expression
   : inclusive_or_expression
   | logical_and_expression AND_OP inclusive_or_expression { $$ = glsl_expr_construct_binary_op_logical(EXPR_LOGICAL_AND, $1, $3); }
   ;

logical_xor_expression
   : logical_and_expression
   | logical_xor_expression XOR_OP logical_and_expression { $$ = glsl_expr_construct_binary_op_logical(EXPR_LOGICAL_XOR, $1, $3); }
   ;

logical_or_expression
   : logical_xor_expression
   | logical_or_expression OR_OP logical_xor_expression { $$ = glsl_expr_construct_binary_op_logical(EXPR_LOGICAL_OR, $1, $3); }
   ;

conditional_expression
   : logical_or_expression
   | logical_or_expression QUESTION expression COLON assignment_expression { $$ = glsl_expr_construct_cond_op($1, $3, $5); }
   ;

assignment_expression
   : conditional_expression
   | unary_expression assignment_operator assignment_expression
      {
         Expr* expr;
         switch ($2)
         {
            case EXPR_MUL:
            case EXPR_DIV:
            case EXPR_REM:
            case EXPR_ADD:
            case EXPR_SUB:
               expr = glsl_expr_construct_binary_op_arithmetic($2, $1, $3);
               break;
            case EXPR_SHL:
            case EXPR_SHR:
               expr = glsl_expr_construct_binary_op_shift($2, $1, $3);
               break;
            case EXPR_BITWISE_AND:
            case EXPR_BITWISE_XOR:
            case EXPR_BITWISE_OR:
               expr = glsl_expr_construct_binary_op_bitwise($2, $1, $3);
               break;
            case EXPR_ASSIGN:
               expr = $3;
               break;
            default:
               UNREACHABLE();
         }
         $$ = glsl_expr_construct_assign_op($1, expr);
      }
   ;

assignment_operator
   : EQUAL         { $$ = EXPR_ASSIGN; }
   | MUL_ASSIGN    { $$ = EXPR_MUL; }
   | DIV_ASSIGN    { $$ = EXPR_DIV; }
   | MOD_ASSIGN    { $$ = EXPR_REM; }
   | ADD_ASSIGN    { $$ = EXPR_ADD; }
   | SUB_ASSIGN    { $$ = EXPR_SUB; }
   | LEFT_ASSIGN   { $$ = EXPR_SHL; }
   | RIGHT_ASSIGN  { $$ = EXPR_SHR; }
   | AND_ASSIGN    { $$ = EXPR_BITWISE_AND; }
   | XOR_ASSIGN    { $$ = EXPR_BITWISE_XOR; }
   | OR_ASSIGN     { $$ = EXPR_BITWISE_OR; }
   ;

expression
   : assignment_expression
   | expression COMMA assignment_expression { $$ = glsl_expr_construct_sequence($1, $3); }
   ;

constant_expression
   : conditional_expression
   ;

declaration
   : function_prototype SEMICOLON           {  glsl_commit_singleton_function_declaration(PS->symbol_table, $1.name, $1.type, false);
                                               // Don't store these in the AST.
                                               $$ = glsl_statement_construct(STATEMENT_NULL);
                                            }
   | init_declarator_list SEMICOLON         { $$ = glsl_statement_construct_decl_list($1.ch); }
   | PRECISION precision_qualifier type_specifier SEMICOLON
                                            { /* update precision table entry */
                                               glsl_prec_modify_prec( PS->precision_table, $3, $2 );
                                               $$ = glsl_statement_construct_precision($2, $3);
                                            }
   | type_qualifier IDENTIFIER LEFT_BRACE struct_declaration_list RIGHT_BRACE SEMICOLON
      { $$ = process_block_decl(PS, $1, $2.name, $4, NULL, NULL); }
   | type_qualifier IDENTIFIER LEFT_BRACE struct_declaration_list RIGHT_BRACE IDENTIFIER SEMICOLON
      { $$ = process_block_decl(PS, $1, $2.name, $4, $6.name, NULL); }
   | type_qualifier IDENTIFIER LEFT_BRACE struct_declaration_list RIGHT_BRACE IDENTIFIER array_specifier SEMICOLON
      { $$ = process_block_decl(PS, $1, $2.name, $4, $6.name, $7); }
   | type_qualifier SEMICOLON
      {
         $$ = glsl_statement_construct_qualifier_default($1);
         qualifiers_process_default($1, PS->symbol_table, &PS->uniform_default_lq, &PS->buffer_default_lq);
      }
   | type_qualifier identifier_list SEMICOLON
      { $$ = glsl_statement_construct_qualifier_augment($1, $2); }
   ;

identifier_list
   : IDENTIFIER
      {
         validate_symbol_lookup($1.symbol, $1.name);
         $$ = glsl_symbol_list_new();
         glsl_symbol_list_append($$, $1.symbol);
      }
   | identifier_list COMMA IDENTIFIER
      {
         validate_symbol_lookup($3.symbol, $3.name);
         glsl_symbol_list_append($1, $3.symbol);
      }
   ;

function_prototype
   : fully_specified_type IDENTIFIER LEFT_PAREN parameter_declaration_list_opt RIGHT_PAREN
      {
         $$.name = $2.name;
         $$.type = glsl_build_function_type($1.quals, $1.type, &PS->function_builder);

         glsl_reinit_function_builder(&PS->function_builder);
      }
   ;

parameter_declaration_list_opt
   : /* empty */
   | parameter_declaration_list
   ;

parameter_declaration_list
   : parameter_declaration
   | parameter_declaration_list COMMA parameter_declaration
   ;

declarator
   : identifier_or_typename                 { $$.name = $1.name; $$.size = NULL; }
   | identifier_or_typename array_specifier { $$.name = $1.name; $$.size = $2; }
   ;

identifier_or_typename
   : IDENTIFIER
   | TYPE_NAME
   ;

parameter_declaration
   : fully_specified_type declarator
      { glsl_commit_function_param(&PS->function_builder, $2.name, $1.type, $1.quals, $2.size); }
   | fully_specified_type
      { glsl_commit_function_param(&PS->function_builder, NULL, $1.type, $1.quals, NULL); }
   ;

init_declarator
   : declarator                   { $$.name = $1.name; $$.size = $1.size; $$.init = NULL; }
   | declarator EQUAL initializer { $$.name = $1.name; $$.size = $1.size; $$.init = $3; }
   ;

init_declarator_list
   : single_declaration
      {
         $$.quals       = $1.quals;
         $$.type        = $1.type;
         $$.ch = glsl_statement_chain_create();
         if ($1.s != NULL)
            $$.ch = glsl_statement_chain_append($$.ch, $1.s);
      }
   | init_declarator_list COMMA init_declarator
      {
         Symbol *symbol = glsl_commit_variable_instance(PS->symbol_table, PS->precision_table, PS->atomic_buffer_offset,
                                                        $1.quals, $1.type, $3.name, $3.size, $3.init);
         $$.quals       = $1.quals;
         $$.type        = $1.type;
         $$.ch          = glsl_statement_chain_append($1.ch,
                                                      glsl_statement_construct_var_decl($1.quals, $1.type, symbol, $3.init));
      }
   ;

single_declaration
   : fully_specified_type     // This matches struct declarations, but also admits rubbish like "int , x".
      {
         $$.quals = $1.quals;
         $$.type  = $1.type;

         Symbol *symbol = glsl_commit_variable_instance(PS->symbol_table, PS->precision_table, PS->atomic_buffer_offset,
                                                        $1.quals, $1.type, NULL, NULL, NULL);
         assert(symbol == NULL);
         $$.s = NULL;
      }
   | fully_specified_type init_declarator
      {
         $$.quals = $1.quals;
         $$.type  = $1.type;

         Symbol *symbol = glsl_commit_variable_instance(PS->symbol_table, PS->precision_table, PS->atomic_buffer_offset,
                                                        $1.quals, $1.type, $2.name, $2.size, $2.init);
         $$.s           = glsl_statement_construct_var_decl($1.quals, $1.type, symbol, $2.init);
      }
   /* Grammar Note: No 'enum', or 'typedef'. */
   ;

fully_specified_type
   : type_specifier                { $$.quals = NULL; $$.type = $1; }
   | type_qualifier type_specifier { $$.quals = $1;   $$.type = $2; }
   ;

invariant_qualifier
   : INVARIANT
   ;

precise_qualifier
   : PRECISE
   ;

interpolation_qualifier
   : SMOOTH { $$ = INTERP_SMOOTH; }
   | FLAT   { $$ = INTERP_FLAT;   }
   ;

layout_qualifier
   : LAYOUT LEFT_PAREN layout_qualifier_id_list RIGHT_PAREN    { $$ = $3; }
   ;

layout_qualifier_id_list
   : layout_qualifier_id                                 { $$ = glsl_lq_id_list_new($1); }
   | layout_qualifier_id_list COMMA layout_qualifier_id  { $$ = glsl_lq_id_list_append($1, $3); }
   ;

layout_qualifier_id
   : IDENTIFIER
      {
         $$ = malloc_fast(sizeof(LayoutID));
         $$->flavour = LQ_FLAVOUR_PLAIN;
         const struct layout_data *d = glsl_layout_lookup($1.name, strlen($1.name));
         if (d == NULL)
            glsl_compile_error(ERROR_CUSTOM, 15, g_LineNumber, "layout \'%s\' not valid", $1.name);
         $$->id = d->lq;
      }
   | IDENTIFIER EQUAL INTCONSTANT
      {
         $$ = malloc_fast(sizeof(LayoutID));
         $$->flavour = LQ_FLAVOUR_INT;
         $$->argument = $3;
         const struct layout_data *d = glsl_layout_lookup($1.name, strlen($1.name));
         if (d == NULL)
            glsl_compile_error(ERROR_CUSTOM, 15, g_LineNumber, "layout \'%s\' not valid", $1.name);
         $$->id = d->lq;
      }
   | IDENTIFIER EQUAL UINTCONSTANT
      {
         $$ = malloc_fast(sizeof(LayoutID));
         $$->flavour = LQ_FLAVOUR_UINT;
         $$->argument = $3;
         const struct layout_data *d = glsl_layout_lookup($1.name, strlen($1.name));
         if (d == NULL)
            glsl_compile_error(ERROR_CUSTOM, 15, g_LineNumber, "layout \'%s\' not valid", $1.name);
         $$->id = d->lq;
      }
   | SHARED
      {
         $$ = malloc_fast(sizeof(LayoutID));
         $$->flavour = LQ_FLAVOUR_PLAIN;
         $$->id = LQ_SHARED;
      }
   ;

type_qualifier
   : single_type_qualifier                { $$ = qual_list_new($1); }
   | type_qualifier single_type_qualifier { $$ = qual_list_append($1, $2); }
   ;

single_type_qualifier
   : storage_qualifier        { $$ = new_qual_storage($1); }
   | auxiliary_qualifier      { $$ = new_qual_auxiliary($1); }
   | memory_qualifier         { $$ = new_qual_memory($1); }
   | layout_qualifier         { $$ = new_qual_layout($1); }
   | precision_qualifier      { $$ = new_qual_prec($1); }
   | interpolation_qualifier  { $$ = new_qual_interp($1); }
   | invariant_qualifier      { $$ = new_qual_invariant(); }
   | precise_qualifier        { $$ = new_qual_precise(); }
   ;

storage_qualifier
   : CONST           { $$ = STORAGE_CONST; }
   | IN              { $$ = STORAGE_IN; }
   | OUT             { $$ = STORAGE_OUT; }
   | INOUT           { $$ = STORAGE_INOUT; }
   | UNIFORM         { $$ = STORAGE_UNIFORM; }
   | BUFFER          { $$ = STORAGE_BUFFER; }
   | SHARED          { $$ = STORAGE_SHARED; }
   /* These became reserved keywords in GLSL_300ES. To handle GLSL_100ES, we deviate from the spec grammar: */
   | ATTRIBUTE
      {
         assert(g_ShaderVersion == GLSL_SHADER_VERSION(1,0,1));

         if (g_ShaderFlavour != SHADER_VERTEX)
            glsl_compile_error(ERROR_LEXER_PARSER, 1, g_LineNumber, "\"attribute\" only valid in vertex shaders");
         else
            $$ = STORAGE_IN;
      }
   | VARYING
      {
         assert(g_ShaderVersion == GLSL_SHADER_VERSION(1,0,1));
         assert(g_ShaderFlavour == SHADER_VERTEX || g_ShaderFlavour == SHADER_FRAGMENT);

         if (g_ShaderFlavour == SHADER_VERTEX)
            $$ = STORAGE_OUT;
         else
            $$ = STORAGE_IN;
      }
   ;

auxiliary_qualifier
   : CENTROID  { $$ = AUXILIARY_CENTROID; }
   | PATCH     { $$ = AUXILIARY_PATCH; }
   | SAMPLE    { $$ = AUXILIARY_SAMPLE; }
   ;

memory_qualifier
   : COHERENT  { $$ = MEMORY_COHERENT; }
   | VOLATILE  { $$ = MEMORY_VOLATILE; }
   | RESTRICT  { $$ = MEMORY_RESTRICT; }
   | READONLY  { $$ = MEMORY_READONLY; }
   | WRITEONLY { $$ = MEMORY_WRITEONLY; }
   ;

type_specifier
   : type_specifier_nonarray
   | type_specifier_nonarray array_specifier { $$ = glsl_build_array_type($1, $2); }
   ;

array_specifier
   : LEFT_BRACKET RIGHT_BRACKET                                     { $$ = glsl_expr_chain_append(glsl_expr_chain_create(), NULL); }
   | LEFT_BRACKET constant_expression RIGHT_BRACKET                 { $$ = glsl_expr_chain_append(glsl_expr_chain_create(), $2); }
   | array_specifier LEFT_BRACKET RIGHT_BRACKET                     { $$ = glsl_expr_chain_append($1, NULL); }
   | array_specifier LEFT_BRACKET constant_expression RIGHT_BRACKET { $$ = glsl_expr_chain_append($1, $3); }
   ;

type_specifier_nonarray
   : VOID                    { $$ = &primitiveTypes[PRIM_VOID]; }
   | FLOAT                   { $$ = &primitiveTypes[PRIM_FLOAT]; }
   | INT                     { $$ = &primitiveTypes[PRIM_INT]; }
   | UINT                    { $$ = &primitiveTypes[PRIM_UINT]; }
   | BOOL                    { $$ = &primitiveTypes[PRIM_BOOL]; }
   | VEC2                    { $$ = &primitiveTypes[PRIM_VEC2]; }
   | VEC3                    { $$ = &primitiveTypes[PRIM_VEC3]; }
   | VEC4                    { $$ = &primitiveTypes[PRIM_VEC4]; }
   | BVEC2                   { $$ = &primitiveTypes[PRIM_BVEC2]; }
   | BVEC3                   { $$ = &primitiveTypes[PRIM_BVEC3]; }
   | BVEC4                   { $$ = &primitiveTypes[PRIM_BVEC4]; }
   | IVEC2                   { $$ = &primitiveTypes[PRIM_IVEC2]; }
   | IVEC3                   { $$ = &primitiveTypes[PRIM_IVEC3]; }
   | IVEC4                   { $$ = &primitiveTypes[PRIM_IVEC4]; }
   | UVEC2                   { $$ = &primitiveTypes[PRIM_UVEC2]; }
   | UVEC3                   { $$ = &primitiveTypes[PRIM_UVEC3]; }
   | UVEC4                   { $$ = &primitiveTypes[PRIM_UVEC4]; }
   | MAT2                    { $$ = &primitiveTypes[PRIM_MAT2]; }
   | MAT3                    { $$ = &primitiveTypes[PRIM_MAT3]; }
   | MAT4                    { $$ = &primitiveTypes[PRIM_MAT4]; }
   | MAT2X2                  { $$ = &primitiveTypes[PRIM_MAT2]; }
   | MAT2X3                  { $$ = &primitiveTypes[PRIM_MAT2X3]; }
   | MAT2X4                  { $$ = &primitiveTypes[PRIM_MAT2X4]; }
   | MAT3X2                  { $$ = &primitiveTypes[PRIM_MAT3X2]; }
   | MAT3X3                  { $$ = &primitiveTypes[PRIM_MAT3]; }
   | MAT3X4                  { $$ = &primitiveTypes[PRIM_MAT3X4]; }
   | MAT4X2                  { $$ = &primitiveTypes[PRIM_MAT4X2]; }
   | MAT4X3                  { $$ = &primitiveTypes[PRIM_MAT4X3]; }
   | MAT4X4                  { $$ = &primitiveTypes[PRIM_MAT4]; }
   | ATOMIC_UINT             { $$ = &primitiveTypes[PRIM_ATOMIC_UINT]; }
   | SAMPLER2D               { $$ = &primitiveTypes[PRIM_SAMPLER2D]; }
   | SAMPLER3D               { $$ = &primitiveTypes[PRIM_SAMPLER3D]; }
   | SAMPLERCUBE             { $$ = &primitiveTypes[PRIM_SAMPLERCUBE]; }
   | SAMPLER2DSHADOW         { $$ = &primitiveTypes[PRIM_SAMPLER2DSHADOW]; }
   | SAMPLERCUBESHADOW       { $$ = &primitiveTypes[PRIM_SAMPLERCUBESHADOW]; }
   | SAMPLER2DARRAY          { $$ = &primitiveTypes[PRIM_SAMPLER2DARRAY]; }
   | SAMPLER2DARRAYSHADOW    { $$ = &primitiveTypes[PRIM_SAMPLER2DARRAYSHADOW]; }
   | ISAMPLER2D              { $$ = &primitiveTypes[PRIM_ISAMPLER2D]; }
   | ISAMPLER3D              { $$ = &primitiveTypes[PRIM_ISAMPLER3D]; }
   | ISAMPLERCUBE            { $$ = &primitiveTypes[PRIM_ISAMPLERCUBE]; }
   | ISAMPLER2DARRAY         { $$ = &primitiveTypes[PRIM_ISAMPLER2DARRAY]; }
   | USAMPLER2D              { $$ = &primitiveTypes[PRIM_USAMPLER2D]; }
   | USAMPLER3D              { $$ = &primitiveTypes[PRIM_USAMPLER3D]; }
   | USAMPLERCUBE            { $$ = &primitiveTypes[PRIM_USAMPLERCUBE]; }
   | USAMPLER2DARRAY         { $$ = &primitiveTypes[PRIM_USAMPLER2DARRAY]; }
   | SAMPLER2DMS             { $$ = &primitiveTypes[PRIM_SAMPLER2DMS]; }
   | ISAMPLER2DMS            { $$ = &primitiveTypes[PRIM_ISAMPLER2DMS]; }
   | USAMPLER2DMS            { $$ = &primitiveTypes[PRIM_USAMPLER2DMS]; }
   | IMAGE2D                 { $$ = &primitiveTypes[PRIM_IMAGE2D]; }
   | IIMAGE2D                { $$ = &primitiveTypes[PRIM_IIMAGE2D]; }
   | UIMAGE2D                { $$ = &primitiveTypes[PRIM_UIMAGE2D]; }
   | IMAGE3D                 { $$ = &primitiveTypes[PRIM_IMAGE3D]; }
   | IIMAGE3D                { $$ = &primitiveTypes[PRIM_IIMAGE3D]; }
   | UIMAGE3D                { $$ = &primitiveTypes[PRIM_UIMAGE3D]; }
   | IMAGECUBE               { $$ = &primitiveTypes[PRIM_IMAGECUBE]; }
   | IIMAGECUBE              { $$ = &primitiveTypes[PRIM_IIMAGECUBE]; }
   | UIMAGECUBE              { $$ = &primitiveTypes[PRIM_UIMAGECUBE]; }
   | IMAGE2DARRAY            { $$ = &primitiveTypes[PRIM_IMAGE2DARRAY]; }
   | IIMAGE2DARRAY           { $$ = &primitiveTypes[PRIM_IIMAGE2DARRAY]; }
   | UIMAGE2DARRAY           { $$ = &primitiveTypes[PRIM_UIMAGE2DARRAY]; }
   | SAMPLEREXTERNAL         { $$ = &primitiveTypes[PRIM_SAMPLEREXTERNALOES]; }
   | SAMPLER1D               { $$ = &primitiveTypes[PRIM_SAMPLER1D]; }
   | SAMPLER1DARRAY          { $$ = &primitiveTypes[PRIM_SAMPLER1DARRAY]; }
   | ISAMPLER1D              { $$ = &primitiveTypes[PRIM_ISAMPLER1D]; }
   | ISAMPLER1DARRAY         { $$ = &primitiveTypes[PRIM_ISAMPLER1DARRAY]; }
   | USAMPLER1D              { $$ = &primitiveTypes[PRIM_USAMPLER1D]; }
   | USAMPLER1DARRAY         { $$ = &primitiveTypes[PRIM_USAMPLER1DARRAY]; }
   | struct_specifier
   | TYPE_NAME               { $$ = $1.symbol->type; }
   // Note that yylex returns token TYPE_NAME iff $1.symbol->flavour==SYMBOL_TYPE.
   // It's NOT context-free information whether an IDENTIFIER is the name of a
   // type or of something else (e.g. a variable).
   ;

precision_qualifier
   : HIGH_PRECISION        { $$ = PREC_HIGHP;   }
   | MEDIUM_PRECISION      { $$ = PREC_MEDIUMP; }
   | LOW_PRECISION         { $$ = PREC_LOWP;    }
   ;

struct_specifier
   : STRUCT IDENTIFIER LEFT_BRACE struct_declaration_list RIGHT_BRACE
         { $$ = glsl_build_struct_type($2.name, $4); glsl_commit_struct_type(PS->symbol_table, $$); }
   | STRUCT LEFT_BRACE struct_declaration_list RIGHT_BRACE
         { $$ = glsl_build_struct_type(NULL, $3); }
   ;

struct_declaration_list
   :  { if(PS->in_struct)
           glsl_compile_error(ERROR_CUSTOM, 17, g_LineNumber, NULL);
        PS->in_struct = true;
      }
      struct_declaration_list_inner
      { PS->in_struct = false;
        $$ = $2;
      }
   ;

struct_declaration_list_inner
   : struct_declaration                               { $$ = glsl_statement_chain_append(glsl_statement_chain_create(), $1); }
   | struct_declaration_list_inner struct_declaration { $$ = glsl_statement_chain_append($1, $2); }
   ;

struct_declaration
   : type_specifier struct_declarator_list SEMICOLON
      { $$ = glsl_statement_construct_struct_decl($1, NULL, $2); }
   | type_qualifier type_specifier struct_declarator_list SEMICOLON
      { $$ = glsl_statement_construct_struct_decl($2, $1, $3); }
   ;

struct_declarator_list
   : declarator                              { $$ = glsl_statement_chain_append(glsl_statement_chain_create(),
                                                            glsl_statement_construct_struct_member_decl($1.name, $1.size)); }
   | struct_declarator_list COMMA declarator { $$ = glsl_statement_chain_append($1,
                                                            glsl_statement_construct_struct_member_decl($3.name, $3.size)); }
   ;

initializer
   : assignment_expression
   ;

declaration_statement
   : declaration
   ;

statement
   : compound_statement_with_scope
   | simple_statement
   ;

statement_no_new_scope
   : compound_statement_no_new_scope
   | simple_statement
   ;

statement_with_scope
   : { enter_scope(state); } compound_statement_no_new_scope { exit_scope(state); $$ = $2; }
   | { enter_scope(state); } simple_statement                { exit_scope(state); $$ = $2; }
   ;

/* Grammar Note: labeled statements for SWITCH only; 'goto' is not supported. */

simple_statement
   : declaration_statement
   | expression_statement
   | selection_statement
   | switch_statement
   | case_label
   | iteration_statement
   | jump_statement
   ;

compound_statement_with_scope
   : LEFT_BRACE RIGHT_BRACE                            { $$ = glsl_statement_construct_compound(glsl_statement_chain_create()); }
   | LEFT_BRACE { enter_scope(state); } statement_list RIGHT_BRACE { exit_scope(state); $$ = glsl_statement_construct_compound($3); }
   ;

compound_statement_no_new_scope
   : LEFT_BRACE RIGHT_BRACE                { $$ = glsl_statement_construct_compound(glsl_statement_chain_create()); }
   | LEFT_BRACE statement_list RIGHT_BRACE { $$ = glsl_statement_construct_compound($2); }
   ;

statement_list
   : statement                            { $$ = glsl_statement_chain_append(glsl_statement_chain_create(), $1); }
   | statement_list statement             { $$ = glsl_statement_chain_append($1, $2); }
   ;

expression_statement
   : SEMICOLON                                         { $$ = glsl_statement_construct(STATEMENT_NULL); }
   | expression SEMICOLON                              { $$ = glsl_statement_construct_expr($1); }
   ;

selection_statement
   : IF LEFT_PAREN expression RIGHT_PAREN selection_rest_statement { $$ = glsl_statement_construct_selection($3, $5.t, $5.f); }
   ;

selection_rest_statement
   : statement_with_scope ELSE statement_with_scope    { $$.t = $1; $$.f = $3; }
   | statement_with_scope                              { $$.t = $1; $$.f = NULL; }
   ;

condition
   : expression                                        { $$ = glsl_statement_construct_expr($1); }
   | fully_specified_type IDENTIFIER EQUAL initializer
      {
         Symbol *symbol = glsl_commit_variable_instance(PS->symbol_table, PS->precision_table, PS->atomic_buffer_offset,
                                                        $1.quals, $1.type, $2.name, NULL, $4);
         $$ = glsl_statement_construct_var_decl($1.quals, $1.type, symbol, $4);
      }
   ;

switch_statement
   : SWITCH LEFT_PAREN expression RIGHT_PAREN { enter_scope(state); } LEFT_BRACE switch_statement_list RIGHT_BRACE
                                              { exit_scope(state); $$ = glsl_statement_construct_switch($3, $7); }
   ;

switch_statement_list
   : /* nothing */   { $$ = glsl_statement_chain_create(); }
   | statement_list
   ;

case_label
   : CASE expression COLON                             { $$ = glsl_statement_construct_case($2); }
   | DEFAULT COLON                                     { $$ = glsl_statement_construct(STATEMENT_DEFAULT); }
   ;

iteration_statement
   : WHILE LEFT_PAREN { enter_scope(state); } condition RIGHT_PAREN statement_no_new_scope { exit_scope(state); $$ = glsl_statement_construct_iterator_while($4, $6); }
   | DO statement_with_scope WHILE LEFT_PAREN expression RIGHT_PAREN SEMICOLON { $$ = glsl_statement_construct_iterator_do_while($2, $5); }
   | FOR LEFT_PAREN { enter_scope(state); } for_init_statement for_rest_statement RIGHT_PAREN statement_no_new_scope { exit_scope(state); $$ = glsl_statement_construct_iterator_for($4, $5.cond_or_decl, $5.iter, $7); }
   ;

for_init_statement
   : expression_statement
   | declaration_statement
   ;

conditionopt
   : condition
   | /* empty */                                   { $$ = NULL; }
   ;

for_rest_statement
   : conditionopt SEMICOLON                        { $$.cond_or_decl = $1; $$.iter = NULL; }
   | conditionopt SEMICOLON expression             { $$.cond_or_decl = $1; $$.iter = $3; }
   ;

jump_statement
   : CONTINUE SEMICOLON                            { $$ = glsl_statement_construct(STATEMENT_CONTINUE); }
   | BREAK SEMICOLON                               { $$ = glsl_statement_construct(STATEMENT_BREAK); }
   | RETURN SEMICOLON                              { $$ = glsl_statement_construct(STATEMENT_RETURN); }
   | RETURN expression SEMICOLON                   { $$ = glsl_statement_construct_return_expr($2); }
   | DISCARD SEMICOLON /* Fragment shader only. */ { $$ = glsl_statement_construct(STATEMENT_DISCARD); }
   /* Grammar Note: No 'goto'. Gotos are not supported. */
   ;

translation_unit
   : external_declaration                     {
                                                 StatementChain* chain = glsl_statement_chain_create();
                                                 glsl_statement_chain_append(chain, $1);
                                                 $$ = glsl_statement_construct_ast(chain);
                                                 PS->astp = $$; // Save for calling function.
                                              }
   | translation_unit external_declaration    {
                                                 StatementChain* chain = $1->u.ast.decls;
                                                 glsl_statement_chain_append(chain, $2);
                                                 $$ = $1;
                                                 PS->astp = $$; // Save for calling function.
                                              }
   ;

external_declaration
   : function_definition
   | declaration
   ;

function_definition
   : function_prototype
      {
         enter_scope(state);
         g_InGlobalScope = false;
         glsl_instantiate_function_params(PS->symbol_table, $1.type);
         if (g_ShaderVersion == GLSL_SHADER_VERSION(1, 0, 1)) enter_scope(state);
      }
                        compound_statement_no_new_scope
      {
         if (g_ShaderVersion == GLSL_SHADER_VERSION(1, 0, 1)) exit_scope(state);
         exit_scope(state);
         g_InGlobalScope = true;
         Symbol *f = glsl_commit_singleton_function_declaration(PS->symbol_table, $1.name, $1.type, true);
         $$ = glsl_statement_construct_function_def(f, $3);
         glsl_insert_function_definition($$);
      }
   ;

%%

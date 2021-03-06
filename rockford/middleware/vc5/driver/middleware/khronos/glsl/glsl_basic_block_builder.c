/*=============================================================================
Copyright (c) 2015 Broadcom Europe Limited.
All rights reserved.

Project  :  glsl
Module   :

FILE DESCRIPTION
=============================================================================*/

#include "glsl_common.h"
#include "glsl_basic_block.h"
#include "glsl_basic_block_builder.h"
#include "glsl_dataflow_builder.h"
#include "glsl_nast.h"
#include "glsl_symbols.h"
#include "glsl_globals.h"
#include "glsl_primitive_types.auto.h"
#include "glsl_stdlib.auto.h"
#include "glsl_stackmem.h"

typedef struct {
   // The currently active basic block. Use basic_block_start and basic_block_end to set it.
   BasicBlock *current_basic_block;

   // The head of the list determines where return/break/continue statement jumps
   BasicBlockList *break_targets;
   BasicBlockList *continue_targets;
   BasicBlockList *return_targets;
   SymbolList *return_symbols; // temporary symbol to store function return value
} builder_context_t;

static void build_statement(builder_context_t *ctx, const NStmt *stmt);

// Start processing of given basic block.
// It should be new clean basic block.
static void basic_block_start(builder_context_t *ctx, BasicBlock *basic_block)
{
   assert(ctx->current_basic_block == NULL);
   assert(basic_block->branch_cond == NULL);
   assert(basic_block->branch_target == NULL);
   assert(basic_block->fallthrough_target == NULL);
   ctx->current_basic_block = basic_block;
}

// End processing of given basic block and set its successors.
// This is the only place where the successors are set.
// The basic block should not be further modified after this.
static void basic_block_end(builder_context_t *ctx, Dataflow *branch_cond, BasicBlock *branch_target, BasicBlock *fallthough_target)
{
   assert(ctx->current_basic_block->branch_cond == NULL);
   assert(ctx->current_basic_block->branch_target == NULL);
   assert(ctx->current_basic_block->fallthrough_target == NULL);
   ctx->current_basic_block->branch_cond = branch_cond;
   ctx->current_basic_block->branch_target = branch_target;
   ctx->current_basic_block->fallthrough_target = fallthough_target;
   ctx->current_basic_block = NULL;
}

static inline Dataflow **alloc_dataflow(size_t amount) {
   return glsl_stack_malloc(sizeof(Dataflow *), amount);
}

static inline void free_dataflow(Dataflow **dflow) {
   glsl_stack_free(dflow);
}

// Assign dataflow to lvalue if cond is true (the condition is used for dynamic array writes)
static void assign(builder_context_t *ctx, Expr *lvalue, int offset, Dataflow **scalar_values, unsigned int scalar_count, Dataflow *cond)
{
   switch (lvalue->flavour) {
   case EXPR_INSTANCE: {
      Symbol *symbol = lvalue->u.instance.symbol;

      assert(symbol->flavour == SYMBOL_VAR_INSTANCE   ||
             symbol->flavour == SYMBOL_PARAM_INSTANCE ||
             symbol->flavour == SYMBOL_TEMPORARY );

      if (symbol->flavour == SYMBOL_VAR_INSTANCE && symbol->u.var_instance.storage_qual == STORAGE_BUFFER) {
         glsl_compile_error(WARNING, 3, -1, "Writes to buffer blocks not yet implemented");
      }

      if (offset == 0 && scalar_count == symbol->type->scalar_count && cond == NULL) {
         glsl_basic_block_set_scalar_values(ctx->current_basic_block, symbol, scalar_values);
      } else {
         for (unsigned int i = 0; i < scalar_count; i++) {
            Dataflow *scalar_value = scalar_values[i];
            if (cond) {
               Dataflow *old_value = glsl_basic_block_get_scalar_value(ctx->current_basic_block, symbol, offset + i);
               scalar_value = glsl_dataflow_construct_ternary_op(DATAFLOW_CONDITIONAL, cond, scalar_value, old_value);
            }
            glsl_basic_block_set_scalar_value(ctx->current_basic_block, symbol, offset + i, scalar_value);
         }
      }
      break;
   }
   case EXPR_SUBSCRIPT: {
      Expr *aggregate = lvalue->u.subscript.aggregate;
      Dataflow *subscript;
      unsigned int member_scalar_count;

      assert(lvalue->u.subscript.subscript->type->scalar_count == 1);
      glsl_expr_calculate_dataflow(ctx->current_basic_block, &subscript, lvalue->u.subscript.subscript);
      assert(glsl_dataflow_is_integral_type(subscript));

      switch (aggregate->type->flavour) {
      case SYMBOL_PRIMITIVE_TYPE:
         member_scalar_count = primitiveTypeSubscriptTypes[aggregate->type->u.primitive_type.index]->scalar_count;
         break;
      case SYMBOL_ARRAY_TYPE:
         member_scalar_count = aggregate->type->u.array_type.member_type->scalar_count;
         break;
      default:
         member_scalar_count = 0;
         UNREACHABLE();
         break;
      }

      if (subscript->flavour == DATAFLOW_CONST) {
         unsigned int element_offset = subscript->u.constant.value * member_scalar_count;
         if (element_offset < aggregate->type->scalar_count)
            assign(ctx, aggregate, offset + element_offset, scalar_values, scalar_count, cond);
      } else {
         unsigned int element_offset;
         unsigned int element_index;
         for (element_offset = 0, element_index = 0; element_offset < aggregate->type->scalar_count; element_offset += member_scalar_count, element_index++) {
            Dataflow *element_cond = glsl_dataflow_construct_binary_op(DATAFLOW_EQUAL, subscript, glsl_dataflow_construct_const_value(subscript->type, element_index));
            if (cond)
               element_cond = glsl_dataflow_construct_binary_op(DATAFLOW_LOGICAL_AND, cond, element_cond);
            assign(ctx, aggregate, offset + element_offset, scalar_values, scalar_count, element_cond);
         }
      }
      break;
   }
   case EXPR_FIELD_SELECTOR: {
      Expr *aggregate = lvalue->u.field_selector.aggregate;
      int field_offset = 0;

      if (aggregate->type->flavour == SYMBOL_BLOCK_TYPE) {
         /* We drop these. Obviously broken */
         glsl_compile_error(WARNING, 3, -1, "Writes to buffer blocks not yet implemented");
         break;
      }

      assert(aggregate->type->flavour == SYMBOL_STRUCT_TYPE);
      for (int i = 0; i < lvalue->u.field_selector.field_no; i++)
         field_offset += aggregate->type->u.struct_type.member[i].type->scalar_count;

      assign(ctx, aggregate, offset + field_offset, scalar_values, scalar_count, cond);
      break;
   }
   case EXPR_SWIZZLE: {
      Expr *aggregate = lvalue->u.swizzle.aggregate;
      assert(aggregate->type->scalar_count <= 4);
      assert(offset + scalar_count <= 4);
      for (unsigned int i = 0; i < scalar_count; i++) {
         unsigned char swizzle_slot = lvalue->u.swizzle.swizzle_slots[offset + i];
         assert(swizzle_slot != SWIZZLE_SLOT_UNUSED);
         assign(ctx, aggregate, swizzle_slot, &scalar_values[i], 1, cond);
      }
      break;
   }
   default:
      UNREACHABLE();
      break;
   }
}

static void build_statement_list(builder_context_t *ctx, NStmtList *stmts)
{
   if (stmts) {
      for (NStmtListNode *node = stmts->head; node; node = node->next)
         build_statement(ctx, node->v);
   }
}

static void build_var_decl_statement(builder_context_t *ctx, const NStmt *stmt)
{
   Symbol *var = stmt->u.var_decl.var;
   // If there's an initializer, and the variable is non-const,
   // save the dataflow graphs (for each scalar value in the initializer) in the variable.
   assert(var->flavour == SYMBOL_VAR_INSTANCE);
   if (stmt->u.var_decl.initializer && var->u.var_instance.storage_qual != STORAGE_CONST) {
      Dataflow **scalar_values = alloc_dataflow(var->type->scalar_count);
      glsl_expr_calculate_dataflow(ctx->current_basic_block, scalar_values, stmt->u.var_decl.initializer);
      glsl_basic_block_set_scalar_values(ctx->current_basic_block, var, scalar_values);
      free_dataflow(scalar_values);
   }
}

static void build_assign_statement(builder_context_t *ctx, const NStmt *stmt)
{
   unsigned int scalar_count = stmt->u.assign.rvalue->type->scalar_count;
   Dataflow **scalar_values = alloc_dataflow(scalar_count);
   glsl_expr_calculate_dataflow(ctx->current_basic_block, scalar_values, stmt->u.assign.rvalue);
   // lvalue is evaluated after rvalue (parts of it potentially multiple times)
   // but that is fine, because the lvalue should be side-effect free by now.
   assign(ctx, stmt->u.assign.lvalue, 0, scalar_values, scalar_count, NULL);
   free_dataflow(scalar_values);
}

static void build_selection_statement(builder_context_t *ctx, const NStmt *stmt)
{
   bool has_false = (stmt->u.selection.if_false && stmt->u.selection.if_false->head);
   BasicBlock *true_block = glsl_basic_block_construct();
   BasicBlock *false_block = glsl_basic_block_construct();
   BasicBlock *end_block = glsl_basic_block_construct();

   Dataflow *cond;
   glsl_expr_calculate_dataflow(ctx->current_basic_block, &cond, stmt->u.selection.cond);
   basic_block_end(ctx, cond, true_block, has_false ? false_block : end_block);

   basic_block_start(ctx, true_block);
   build_statement_list(ctx, stmt->u.selection.if_true);
   basic_block_end(ctx, NULL, NULL, end_block);

   if (has_false) {
      basic_block_start(ctx, false_block);
      build_statement_list(ctx, stmt->u.selection.if_false);
      basic_block_end(ctx, NULL, NULL, end_block);
   }

   basic_block_start(ctx, end_block);
}

static void build_switch_statement(builder_context_t *ctx, const NStmt *stmt)
{
   Symbol *switch_value_symbol = glsl_symbol_construct_temporary(stmt->u.switch_stmt.cond->type);
   BasicBlock *default_block = NULL;
   BasicBlock *end_block = glsl_basic_block_construct();
   Map *case_to_basic_block = glsl_map_new();
   NStmtListNode *node;

   {
      Dataflow *switch_value;
      glsl_expr_calculate_dataflow(ctx->current_basic_block, &switch_value, stmt->u.switch_stmt.cond);
      glsl_basic_block_set_scalar_value(ctx->current_basic_block, switch_value_symbol, 0, switch_value);
   }

   // If the switch statement is empty then we're done
   if (stmt->u.switch_stmt.statements->head == NULL) return;

   glsl_basic_block_list_add(&ctx->break_targets, end_block);

   // Create list of conditions which find the right case to branch to
   // The basic blocks for the cases are created here, but they are not populated yet
   for (node = stmt->u.switch_stmt.statements->head; node; node = node->next) {
      if(node->v->flavour == NSTMT_CASE) {
         Dataflow *switch_value = glsl_basic_block_get_scalar_value(ctx->current_basic_block, switch_value_symbol, 0);
         Dataflow *scalar_value;
         BasicBlock *case_block = glsl_basic_block_construct();
         BasicBlock *next_block = glsl_basic_block_construct();
         glsl_map_put(case_to_basic_block, node, case_block);
         glsl_expr_calculate_dataflow(ctx->current_basic_block, &scalar_value, node->v->u.case_stmt.expr);
         scalar_value = glsl_dataflow_construct_binary_op(DATAFLOW_EQUAL, switch_value, scalar_value);
         basic_block_end(ctx, scalar_value, case_block, next_block);
         basic_block_start(ctx, next_block);
      } else if (node->v->flavour == NSTMT_DEFAULT) {
         default_block = glsl_basic_block_construct();
         glsl_map_put(case_to_basic_block, node, default_block);
      }
   }
   // If none of the cases was taken, branch to the default case (if we have one)
   basic_block_end(ctx, NULL, NULL, default_block ? default_block : end_block);

   // Fill the basic blocks for cases.
   // Note: code before the first label will be generated but will be unreachable
   basic_block_start(ctx, glsl_basic_block_construct());
   for (node = stmt->u.switch_stmt.statements->head; node; node = node->next) {
      if(node->v->flavour == NSTMT_CASE || node->v->flavour == NSTMT_DEFAULT) {
         BasicBlock *case_block = glsl_map_get(case_to_basic_block, node);
         // Terminate the previous case (fallthrough is allowed)
         basic_block_end(ctx, NULL, NULL, case_block);
         // Start the basic bloc for this case
         basic_block_start(ctx, case_block);
      } else {
         build_statement(ctx, node->v);
      }
   }
   // The last case falls through to the end
   basic_block_end(ctx, NULL, NULL, end_block);

   glsl_basic_block_list_pop(&ctx->break_targets);
   basic_block_start(ctx, end_block);
}

static void build_iterator_statement(builder_context_t *ctx, const NStmt *stmt)
{
   bool has_post_cond = (stmt->u.iterator.post_cond_stmts || stmt->u.iterator.post_cond_expr);
   Dataflow *scalar_value;
   BasicBlock *pre_cond_block = glsl_basic_block_construct();
   BasicBlock *body_block = glsl_basic_block_construct();
   BasicBlock *post_cond_block = glsl_basic_block_construct();
   BasicBlock *iter_block = glsl_basic_block_construct();
   BasicBlock *end_block = glsl_basic_block_construct();
   glsl_basic_block_list_add(&ctx->break_targets, end_block);
   glsl_basic_block_list_add(&ctx->continue_targets, post_cond_block);

   basic_block_end(ctx, NULL, NULL, pre_cond_block);

   // Loop pre-condition
   basic_block_start(ctx, pre_cond_block);
   ctx->current_basic_block->loop_index = stmt->u.iterator.loop_index; // unguarded init
   build_statement_list(ctx, stmt->u.iterator.pre_cond_stmts);
   if (stmt->u.iterator.pre_cond_expr) {
      glsl_expr_calculate_dataflow(ctx->current_basic_block, &scalar_value, stmt->u.iterator.pre_cond_expr);
   } else {
      scalar_value = glsl_dataflow_construct_const_bool(true);
   }
   basic_block_end(ctx, scalar_value, body_block, end_block);

   // Loop body
   basic_block_start(ctx, body_block);
   build_statement_list(ctx, stmt->u.iterator.body);
   basic_block_end(ctx, NULL, NULL, has_post_cond ? post_cond_block : iter_block);

   // Loop post-condition
   basic_block_start(ctx, post_cond_block);
   if (has_post_cond) {
      build_statement_list(ctx, stmt->u.iterator.post_cond_stmts);
      if (stmt->u.iterator.post_cond_expr) {
         glsl_expr_calculate_dataflow(ctx->current_basic_block, &scalar_value, stmt->u.iterator.post_cond_expr);
      } else {
         scalar_value = glsl_dataflow_construct_const_bool(true);
      }
      basic_block_end(ctx, scalar_value, iter_block, end_block);
   } else {
      basic_block_end(ctx, glsl_dataflow_construct_const_bool(true), iter_block, end_block);
   }

   // Loop increment
   basic_block_start(ctx, iter_block);
   iter_block->loop_index = stmt->u.iterator.loop_index; // unguarded increment
   build_statement_list(ctx, stmt->u.iterator.increment);
   basic_block_end(ctx, NULL, NULL, pre_cond_block);

   glsl_basic_block_list_pop(&ctx->break_targets);
   glsl_basic_block_list_pop(&ctx->continue_targets);

   basic_block_start(ctx, end_block);
}

static void build_function_call_statement(builder_context_t *ctx, const NStmt *stmt)
{
   Expr *lvalue = stmt->u.function_call.lvalue;
   Symbol *function = stmt->u.function_call.function;
   const NStmt *function_def = function->u.function_instance.function_norm_def;
   Symbol *return_value = glsl_symbol_construct_temporary(lvalue->type);

   // Evaluate and assign function arguments
   glsl_expr_calculate_function_call_args(ctx->current_basic_block, stmt->u.function_call.function, stmt->u.function_call.args);

   // Evaluate function body
   {
      BasicBlock *start_block = ctx->current_basic_block;
      BasicBlock *end_block = glsl_basic_block_construct();
      glsl_basic_block_list_add(&ctx->return_targets, end_block);
      glsl_symbol_list_append(ctx->return_symbols, return_value);

      build_statement_list(ctx, function_def->u.function_def.body);

      glsl_basic_block_list_pop(&ctx->return_targets);
      glsl_symbol_list_pop(ctx->return_symbols);
      basic_block_end(ctx, NULL, NULL, end_block);
      basic_block_start(ctx, end_block);

      // do not create extra basic block if we do not have to
      if (start_block->fallthrough_target == end_block && start_block->branch_target == NULL) {
         start_block->fallthrough_target = NULL;
         ctx->current_basic_block = start_block;
      }
   }

   // Marshall output arguments
   ExprChainNode *node = stmt->u.function_call.args->first;
   for (unsigned i = 0; i < function->type->u.function_type.param_count; i++, node = node->next) {
      Symbol *formal = function->type->u.function_type.params[i];
      Expr *actual = node->expr;
      if (formal->u.param_instance.param_qual == PARAM_QUAL_OUT || formal->u.param_instance.param_qual == PARAM_QUAL_INOUT) {
         Dataflow **scalar_values = glsl_basic_block_get_scalar_values(ctx->current_basic_block, formal);
         assign(ctx, actual, 0, scalar_values, formal->type->scalar_count, NULL);
      }
   }

   // Marshall return value
   Dataflow **scalar_values = glsl_basic_block_get_scalar_values(ctx->current_basic_block, return_value);
   assign(ctx, lvalue, 0, scalar_values, lvalue->type->scalar_count, NULL);
}

static void build_return_expr_statement(builder_context_t *ctx, const NStmt *stmt)
{
   Dataflow **scalar_values = alloc_dataflow(stmt->u.return_expr.expr->type->scalar_count);
   glsl_expr_calculate_dataflow(ctx->current_basic_block, scalar_values, stmt->u.return_expr.expr);
   glsl_basic_block_set_scalar_values(ctx->current_basic_block, ctx->return_symbols->tail->s, scalar_values);
   free_dataflow(scalar_values);

   basic_block_end(ctx, NULL, NULL, ctx->return_targets->v);
   basic_block_start(ctx, glsl_basic_block_construct());
}

static void build_statement(builder_context_t *ctx, const NStmt *stmt)
{
   switch (stmt->flavour) {
   case NSTMT_FUNCTION_DEF:
      /* We only care about the definition of 'main' everything else is done at call time */
      if (strcmp(stmt->u.function_def.header->name, "main") == 0)
         build_statement_list(ctx, stmt->u.function_def.body);
      break;

   case NSTMT_VAR_DECL:
      build_var_decl_statement(ctx, stmt);
      break;

   case NSTMT_ASSIGN:
      build_assign_statement(ctx, stmt);
      break;

   case NSTMT_FUNCTION_CALL:
      build_function_call_statement(ctx, stmt);
      break;

   case NSTMT_SELECTION:
      build_selection_statement(ctx, stmt);
      break;

   case NSTMT_SWITCH:
      build_switch_statement(ctx, stmt);
      break;

   case NSTMT_ITERATOR:
      build_iterator_statement(ctx, stmt);
      break;

   case NSTMT_CONTINUE:
      basic_block_end(ctx, NULL, NULL, ctx->continue_targets->v);
      basic_block_start(ctx, glsl_basic_block_construct());
      break;

   case NSTMT_RETURN:
      basic_block_end(ctx, NULL, NULL, ctx->return_targets->v);
      basic_block_start(ctx, glsl_basic_block_construct());
      break;

   case NSTMT_BREAK:
      basic_block_end(ctx, NULL, NULL, ctx->break_targets->v);
      basic_block_start(ctx, glsl_basic_block_construct());
      break;

   case NSTMT_DISCARD: {
      Symbol *discard = glsl_stdlib_get_variable(GLSL_STDLIB_VAR__OUT__BOOL____DISCARD);
      glsl_basic_block_set_scalar_value(ctx->current_basic_block, discard, 0, glsl_dataflow_construct_const_bool(true));
      break;
   }
   case NSTMT_RETURN_EXPR:
      build_return_expr_statement(ctx, stmt);
      break;

   // These should not be reached:
   // (Should be handled in the switch case, otherwise they are improperly nested).
   case NSTMT_CASE:
   case NSTMT_DEFAULT:
      glsl_compile_error(ERROR_CUSTOM, 7, stmt->line_num, "case and default labels may only appear inside switches");
      break;

   case NSTMT_FLAVOUR_COUNT:
      UNREACHABLE();
      break;
   }
}

BasicBlock *glsl_basic_block_build(NStmtList *nast)
{
   builder_context_t ctx = { 0 };
   ctx.return_symbols = glsl_symbol_list_new();
   BasicBlock *entry_block = glsl_basic_block_construct();
   BasicBlock *end_block = glsl_basic_block_construct();
   int df_stack_leaks;

   glsl_dataflow_reset_age();
   glsl_basic_block_list_add(&ctx.return_targets, end_block);

   basic_block_start(&ctx, entry_block);
   build_statement_list(&ctx, nast);
   basic_block_end(&ctx, NULL, NULL, end_block);

   glsl_basic_block_list_pop(&ctx.return_targets);
   assert(ctx.return_targets == NULL && ctx.break_targets == NULL && ctx.continue_targets == NULL);

   df_stack_leaks = glsl_stack_cleanup();
   assert(df_stack_leaks == 0);

   return entry_block;
}

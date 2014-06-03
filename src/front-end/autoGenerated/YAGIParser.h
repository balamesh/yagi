/** \file
 *  This C header file was generated by $ANTLR version 3.5.2
 *
 *     -  From the grammar source file : ./src/front-end/grammar/YAGI.g
 *     -                            On : 2014-06-03 15:06:33
 *     -                for the parser : YAGIParserParser
 *
 * Editing it, at least manually, is not wise.
 *
 * C language generator and runtime by Jim Idle, jimi|hereisanat|idle|dotgoeshere|ws.
 *
 *
 * The parser 
YAGIParser

has the callable functions (rules) shown below,
 * which will invoke the code for the associated rule in the source grammar
 * assuming that the input stream is pointing to a token/text stream that could begin
 * this rule.
 *
 * For instance if you call the first (topmost) rule in a parser grammar, you will
 * get the results of a full parse, but calling a rule half way through the grammar will
 * allow you to pass part of a full token stream to the parser, such as for syntax checking
 * in editors and so on.
 *
 * The parser entry points are called indirectly (by function pointer to function) via
 * a parser context typedef pYAGIParser, which is returned from a call to YAGIParserNew().
 *
 * The methods in pYAGIParser are  as follows:
 *
 *  - 
 YAGIParser_program_return
      pYAGIParser->program(pYAGIParser)
 *  - 
 YAGIParser_block_return
      pYAGIParser->block(pYAGIParser)
 *  - 
 YAGIParser_declaration_return
      pYAGIParser->declaration(pYAGIParser)
 *  - 
 YAGIParser_fluent_decl_return
      pYAGIParser->fluent_decl(pYAGIParser)
 *  - 
 YAGIParser_fact_decl_return
      pYAGIParser->fact_decl(pYAGIParser)
 *  - 
 YAGIParser_domain_return
      pYAGIParser->domain(pYAGIParser)
 *  - 
 YAGIParser_action_decl_return
      pYAGIParser->action_decl(pYAGIParser)
 *  - 
 YAGIParser_effect_return
      pYAGIParser->effect(pYAGIParser)
 *  - 
 YAGIParser_active_sensing_return
      pYAGIParser->active_sensing(pYAGIParser)
 *  - 
 YAGIParser_var_list_return
      pYAGIParser->var_list(pYAGIParser)
 *  - 
 YAGIParser_proc_decl_return
      pYAGIParser->proc_decl(pYAGIParser)
 *  - 
 YAGIParser_passive_sensing_decl_return
      pYAGIParser->passive_sensing_decl(pYAGIParser)
 *  - 
 YAGIParser_assignment_return
      pYAGIParser->assignment(pYAGIParser)
 *  - 
 YAGIParser_statement_return
      pYAGIParser->statement(pYAGIParser)
 *  - 
 YAGIParser_action_exec_return
      pYAGIParser->action_exec(pYAGIParser)
 *  - 
 YAGIParser_value_list_return
      pYAGIParser->value_list(pYAGIParser)
 *  - 
 YAGIParser_test_return
      pYAGIParser->test(pYAGIParser)
 *  - 
 YAGIParser_choose_return
      pYAGIParser->choose(pYAGIParser)
 *  - 
 YAGIParser_pick_return
      pYAGIParser->pick(pYAGIParser)
 *  - 
 YAGIParser_for_loop_return
      pYAGIParser->for_loop(pYAGIParser)
 *  - 
 YAGIParser_conditional_return
      pYAGIParser->conditional(pYAGIParser)
 *  - 
 YAGIParser_while_loop_return
      pYAGIParser->while_loop(pYAGIParser)
 *  - 
 YAGIParser_search_return
      pYAGIParser->search(pYAGIParser)
 *  - 
 YAGIParser_assign_return
      pYAGIParser->assign(pYAGIParser)
 *  - 
 YAGIParser_ass_op_return
      pYAGIParser->ass_op(pYAGIParser)
 *  - 
 YAGIParser_for_loop_assign_return
      pYAGIParser->for_loop_assign(pYAGIParser)
 *  - 
 YAGIParser_conditional_assign_return
      pYAGIParser->conditional_assign(pYAGIParser)
 *  - 
 YAGIParser_formula_outerMost_return
      pYAGIParser->formula_outerMost(pYAGIParser)
 *  - 
 YAGIParser_formula_return
      pYAGIParser->formula(pYAGIParser)
 *  - 
 YAGIParser_formula_connective_return
      pYAGIParser->formula_connective(pYAGIParser)
 *  - 
 YAGIParser_atom_return
      pYAGIParser->atom(pYAGIParser)
 *  - 
 YAGIParser_atom_connector_return
      pYAGIParser->atom_connector(pYAGIParser)
 *  - 
 YAGIParser_set_return
      pYAGIParser->set(pYAGIParser)
 *  - 
 YAGIParser_setexpr_return
      pYAGIParser->setexpr(pYAGIParser)
 *  - 
 YAGIParser_tuple_return
      pYAGIParser->tuple(pYAGIParser)
 *  - 
 YAGIParser_tuple_val_return
      pYAGIParser->tuple_val(pYAGIParser)
 *  - 
 YAGIParser_var_return
      pYAGIParser->var(pYAGIParser)
 *  - 
 YAGIParser_value_return
      pYAGIParser->value(pYAGIParser)
 *  - 
 YAGIParser_valexpr_return
      pYAGIParser->valexpr(pYAGIParser)
 *  - 
 YAGIParser_expr_op_return
      pYAGIParser->expr_op(pYAGIParser)
 *
 * The return type for any particular rule is of course determined by the source
 * grammar file.
 */
// [The "BSD license"]
// Copyright (c) 2005-2009 Jim Idle, Temporal Wave LLC
// http://www.temporal-wave.com
// http://www.linkedin.com/in/jimidle
//
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions
// are met:
// 1. Redistributions of source code must retain the above copyright
//    notice, this list of conditions and the following disclaimer.
// 2. Redistributions in binary form must reproduce the above copyright
//    notice, this list of conditions and the following disclaimer in the
//    documentation and/or other materials provided with the distribution.
// 3. The name of the author may not be used to endorse or promote products
//    derived from this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
// IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
// OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
// IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
// INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
// NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
// THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#ifndef	_YAGIParser_H
#define _YAGIParser_H
/* =============================================================================
 * Standard antlr3 C runtime definitions
 */
#include    <antlr3.h>

/* End of standard antlr 3 runtime definitions
 * =============================================================================
 */

#ifdef __cplusplus
extern "C" {
#endif

// Forward declare the context typedef so that we can use it before it is
// properly defined. Delegators and delegates (from import statements) are
// interdependent and their context structures contain pointers to each other
// C only allows such things to be declared if you pre-declare the typedef.
//
typedef struct YAGIParser_Ctx_struct YAGIParser, * pYAGIParser;



    #define _empty NULL


#ifdef	ANTLR3_WINDOWS
// Disable: Unreferenced parameter,							- Rules with parameters that are not used
//          constant conditional,							- ANTLR realizes that a prediction is always true (synpred usually)
//          initialized but unused variable					- tree rewrite variables declared but not needed
//          Unreferenced local variable						- lexer rule declares but does not always use _type
//          potentially unitialized variable used			- retval always returned from a rule
//			unreferenced local function has been removed	- susually getTokenNames or freeScope, they can go without warnigns
//
// These are only really displayed at warning level /W4 but that is the code ideal I am aiming at
// and the codegen must generate some of these warnings by necessity, apart from 4100, which is
// usually generated when a parser rule is given a parameter that it does not use. Mostly though
// this is a matter of orthogonality hence I disable that one.
//
#pragma warning( disable : 4100 )
#pragma warning( disable : 4101 )
#pragma warning( disable : 4127 )
#pragma warning( disable : 4189 )
#pragma warning( disable : 4505 )
#pragma warning( disable : 4701 )
#endif
typedef struct YAGIParser_program_return_struct
{
    /** Generic return elements for ANTLR3 rules that are not in tree parsers or returning trees
     */
    pANTLR3_COMMON_TOKEN    start;
    pANTLR3_COMMON_TOKEN    stop;
    pANTLR3_BASE_TREE	tree;

}
    YAGIParser_program_return;



typedef struct YAGIParser_block_return_struct
{
    /** Generic return elements for ANTLR3 rules that are not in tree parsers or returning trees
     */
    pANTLR3_COMMON_TOKEN    start;
    pANTLR3_COMMON_TOKEN    stop;
    pANTLR3_BASE_TREE	tree;

}
    YAGIParser_block_return;



typedef struct YAGIParser_declaration_return_struct
{
    /** Generic return elements for ANTLR3 rules that are not in tree parsers or returning trees
     */
    pANTLR3_COMMON_TOKEN    start;
    pANTLR3_COMMON_TOKEN    stop;
    pANTLR3_BASE_TREE	tree;

}
    YAGIParser_declaration_return;



typedef struct YAGIParser_fluent_decl_return_struct
{
    /** Generic return elements for ANTLR3 rules that are not in tree parsers or returning trees
     */
    pANTLR3_COMMON_TOKEN    start;
    pANTLR3_COMMON_TOKEN    stop;
    pANTLR3_BASE_TREE	tree;

}
    YAGIParser_fluent_decl_return;



typedef struct YAGIParser_fact_decl_return_struct
{
    /** Generic return elements for ANTLR3 rules that are not in tree parsers or returning trees
     */
    pANTLR3_COMMON_TOKEN    start;
    pANTLR3_COMMON_TOKEN    stop;
    pANTLR3_BASE_TREE	tree;

}
    YAGIParser_fact_decl_return;



typedef struct YAGIParser_domain_return_struct
{
    /** Generic return elements for ANTLR3 rules that are not in tree parsers or returning trees
     */
    pANTLR3_COMMON_TOKEN    start;
    pANTLR3_COMMON_TOKEN    stop;
    pANTLR3_BASE_TREE	tree;

}
    YAGIParser_domain_return;



typedef struct YAGIParser_action_decl_return_struct
{
    /** Generic return elements for ANTLR3 rules that are not in tree parsers or returning trees
     */
    pANTLR3_COMMON_TOKEN    start;
    pANTLR3_COMMON_TOKEN    stop;
    pANTLR3_BASE_TREE	tree;

}
    YAGIParser_action_decl_return;



typedef struct YAGIParser_effect_return_struct
{
    /** Generic return elements for ANTLR3 rules that are not in tree parsers or returning trees
     */
    pANTLR3_COMMON_TOKEN    start;
    pANTLR3_COMMON_TOKEN    stop;
    pANTLR3_BASE_TREE	tree;

}
    YAGIParser_effect_return;



typedef struct YAGIParser_active_sensing_return_struct
{
    /** Generic return elements for ANTLR3 rules that are not in tree parsers or returning trees
     */
    pANTLR3_COMMON_TOKEN    start;
    pANTLR3_COMMON_TOKEN    stop;
    pANTLR3_BASE_TREE	tree;

}
    YAGIParser_active_sensing_return;



typedef struct YAGIParser_var_list_return_struct
{
    /** Generic return elements for ANTLR3 rules that are not in tree parsers or returning trees
     */
    pANTLR3_COMMON_TOKEN    start;
    pANTLR3_COMMON_TOKEN    stop;
    pANTLR3_BASE_TREE	tree;

}
    YAGIParser_var_list_return;



typedef struct YAGIParser_proc_decl_return_struct
{
    /** Generic return elements for ANTLR3 rules that are not in tree parsers or returning trees
     */
    pANTLR3_COMMON_TOKEN    start;
    pANTLR3_COMMON_TOKEN    stop;
    pANTLR3_BASE_TREE	tree;

}
    YAGIParser_proc_decl_return;



typedef struct YAGIParser_passive_sensing_decl_return_struct
{
    /** Generic return elements for ANTLR3 rules that are not in tree parsers or returning trees
     */
    pANTLR3_COMMON_TOKEN    start;
    pANTLR3_COMMON_TOKEN    stop;
    pANTLR3_BASE_TREE	tree;

}
    YAGIParser_passive_sensing_decl_return;



typedef struct YAGIParser_assignment_return_struct
{
    /** Generic return elements for ANTLR3 rules that are not in tree parsers or returning trees
     */
    pANTLR3_COMMON_TOKEN    start;
    pANTLR3_COMMON_TOKEN    stop;
    pANTLR3_BASE_TREE	tree;

}
    YAGIParser_assignment_return;



typedef struct YAGIParser_statement_return_struct
{
    /** Generic return elements for ANTLR3 rules that are not in tree parsers or returning trees
     */
    pANTLR3_COMMON_TOKEN    start;
    pANTLR3_COMMON_TOKEN    stop;
    pANTLR3_BASE_TREE	tree;

}
    YAGIParser_statement_return;



typedef struct YAGIParser_action_exec_return_struct
{
    /** Generic return elements for ANTLR3 rules that are not in tree parsers or returning trees
     */
    pANTLR3_COMMON_TOKEN    start;
    pANTLR3_COMMON_TOKEN    stop;
    pANTLR3_BASE_TREE	tree;

}
    YAGIParser_action_exec_return;



typedef struct YAGIParser_value_list_return_struct
{
    /** Generic return elements for ANTLR3 rules that are not in tree parsers or returning trees
     */
    pANTLR3_COMMON_TOKEN    start;
    pANTLR3_COMMON_TOKEN    stop;
    pANTLR3_BASE_TREE	tree;

}
    YAGIParser_value_list_return;



typedef struct YAGIParser_test_return_struct
{
    /** Generic return elements for ANTLR3 rules that are not in tree parsers or returning trees
     */
    pANTLR3_COMMON_TOKEN    start;
    pANTLR3_COMMON_TOKEN    stop;
    pANTLR3_BASE_TREE	tree;

}
    YAGIParser_test_return;



typedef struct YAGIParser_choose_return_struct
{
    /** Generic return elements for ANTLR3 rules that are not in tree parsers or returning trees
     */
    pANTLR3_COMMON_TOKEN    start;
    pANTLR3_COMMON_TOKEN    stop;
    pANTLR3_BASE_TREE	tree;

}
    YAGIParser_choose_return;



typedef struct YAGIParser_pick_return_struct
{
    /** Generic return elements for ANTLR3 rules that are not in tree parsers or returning trees
     */
    pANTLR3_COMMON_TOKEN    start;
    pANTLR3_COMMON_TOKEN    stop;
    pANTLR3_BASE_TREE	tree;

}
    YAGIParser_pick_return;



typedef struct YAGIParser_for_loop_return_struct
{
    /** Generic return elements for ANTLR3 rules that are not in tree parsers or returning trees
     */
    pANTLR3_COMMON_TOKEN    start;
    pANTLR3_COMMON_TOKEN    stop;
    pANTLR3_BASE_TREE	tree;

}
    YAGIParser_for_loop_return;



typedef struct YAGIParser_conditional_return_struct
{
    /** Generic return elements for ANTLR3 rules that are not in tree parsers or returning trees
     */
    pANTLR3_COMMON_TOKEN    start;
    pANTLR3_COMMON_TOKEN    stop;
    pANTLR3_BASE_TREE	tree;

}
    YAGIParser_conditional_return;



typedef struct YAGIParser_while_loop_return_struct
{
    /** Generic return elements for ANTLR3 rules that are not in tree parsers or returning trees
     */
    pANTLR3_COMMON_TOKEN    start;
    pANTLR3_COMMON_TOKEN    stop;
    pANTLR3_BASE_TREE	tree;

}
    YAGIParser_while_loop_return;



typedef struct YAGIParser_search_return_struct
{
    /** Generic return elements for ANTLR3 rules that are not in tree parsers or returning trees
     */
    pANTLR3_COMMON_TOKEN    start;
    pANTLR3_COMMON_TOKEN    stop;
    pANTLR3_BASE_TREE	tree;

}
    YAGIParser_search_return;



typedef struct YAGIParser_assign_return_struct
{
    /** Generic return elements for ANTLR3 rules that are not in tree parsers or returning trees
     */
    pANTLR3_COMMON_TOKEN    start;
    pANTLR3_COMMON_TOKEN    stop;
    pANTLR3_BASE_TREE	tree;

}
    YAGIParser_assign_return;



typedef struct YAGIParser_ass_op_return_struct
{
    /** Generic return elements for ANTLR3 rules that are not in tree parsers or returning trees
     */
    pANTLR3_COMMON_TOKEN    start;
    pANTLR3_COMMON_TOKEN    stop;
    pANTLR3_BASE_TREE	tree;

}
    YAGIParser_ass_op_return;



typedef struct YAGIParser_for_loop_assign_return_struct
{
    /** Generic return elements for ANTLR3 rules that are not in tree parsers or returning trees
     */
    pANTLR3_COMMON_TOKEN    start;
    pANTLR3_COMMON_TOKEN    stop;
    pANTLR3_BASE_TREE	tree;

}
    YAGIParser_for_loop_assign_return;



typedef struct YAGIParser_conditional_assign_return_struct
{
    /** Generic return elements for ANTLR3 rules that are not in tree parsers or returning trees
     */
    pANTLR3_COMMON_TOKEN    start;
    pANTLR3_COMMON_TOKEN    stop;
    pANTLR3_BASE_TREE	tree;

}
    YAGIParser_conditional_assign_return;



typedef struct YAGIParser_formula_outerMost_return_struct
{
    /** Generic return elements for ANTLR3 rules that are not in tree parsers or returning trees
     */
    pANTLR3_COMMON_TOKEN    start;
    pANTLR3_COMMON_TOKEN    stop;
    pANTLR3_BASE_TREE	tree;

}
    YAGIParser_formula_outerMost_return;



typedef struct YAGIParser_formula_return_struct
{
    /** Generic return elements for ANTLR3 rules that are not in tree parsers or returning trees
     */
    pANTLR3_COMMON_TOKEN    start;
    pANTLR3_COMMON_TOKEN    stop;
    pANTLR3_BASE_TREE	tree;

}
    YAGIParser_formula_return;



typedef struct YAGIParser_formula_connective_return_struct
{
    /** Generic return elements for ANTLR3 rules that are not in tree parsers or returning trees
     */
    pANTLR3_COMMON_TOKEN    start;
    pANTLR3_COMMON_TOKEN    stop;
    pANTLR3_BASE_TREE	tree;

}
    YAGIParser_formula_connective_return;



typedef struct YAGIParser_atom_return_struct
{
    /** Generic return elements for ANTLR3 rules that are not in tree parsers or returning trees
     */
    pANTLR3_COMMON_TOKEN    start;
    pANTLR3_COMMON_TOKEN    stop;
    pANTLR3_BASE_TREE	tree;

}
    YAGIParser_atom_return;



typedef struct YAGIParser_atom_connector_return_struct
{
    /** Generic return elements for ANTLR3 rules that are not in tree parsers or returning trees
     */
    pANTLR3_COMMON_TOKEN    start;
    pANTLR3_COMMON_TOKEN    stop;
    pANTLR3_BASE_TREE	tree;

}
    YAGIParser_atom_connector_return;



typedef struct YAGIParser_set_return_struct
{
    /** Generic return elements for ANTLR3 rules that are not in tree parsers or returning trees
     */
    pANTLR3_COMMON_TOKEN    start;
    pANTLR3_COMMON_TOKEN    stop;
    pANTLR3_BASE_TREE	tree;

}
    YAGIParser_set_return;



typedef struct YAGIParser_setexpr_return_struct
{
    /** Generic return elements for ANTLR3 rules that are not in tree parsers or returning trees
     */
    pANTLR3_COMMON_TOKEN    start;
    pANTLR3_COMMON_TOKEN    stop;
    pANTLR3_BASE_TREE	tree;

}
    YAGIParser_setexpr_return;



typedef struct YAGIParser_tuple_return_struct
{
    /** Generic return elements for ANTLR3 rules that are not in tree parsers or returning trees
     */
    pANTLR3_COMMON_TOKEN    start;
    pANTLR3_COMMON_TOKEN    stop;
    pANTLR3_BASE_TREE	tree;

}
    YAGIParser_tuple_return;



typedef struct YAGIParser_tuple_val_return_struct
{
    /** Generic return elements for ANTLR3 rules that are not in tree parsers or returning trees
     */
    pANTLR3_COMMON_TOKEN    start;
    pANTLR3_COMMON_TOKEN    stop;
    pANTLR3_BASE_TREE	tree;

}
    YAGIParser_tuple_val_return;



typedef struct YAGIParser_var_return_struct
{
    /** Generic return elements for ANTLR3 rules that are not in tree parsers or returning trees
     */
    pANTLR3_COMMON_TOKEN    start;
    pANTLR3_COMMON_TOKEN    stop;
    pANTLR3_BASE_TREE	tree;

}
    YAGIParser_var_return;



typedef struct YAGIParser_value_return_struct
{
    /** Generic return elements for ANTLR3 rules that are not in tree parsers or returning trees
     */
    pANTLR3_COMMON_TOKEN    start;
    pANTLR3_COMMON_TOKEN    stop;
    pANTLR3_BASE_TREE	tree;

}
    YAGIParser_value_return;



typedef struct YAGIParser_valexpr_return_struct
{
    /** Generic return elements for ANTLR3 rules that are not in tree parsers or returning trees
     */
    pANTLR3_COMMON_TOKEN    start;
    pANTLR3_COMMON_TOKEN    stop;
    pANTLR3_BASE_TREE	tree;

}
    YAGIParser_valexpr_return;



typedef struct YAGIParser_expr_op_return_struct
{
    /** Generic return elements for ANTLR3 rules that are not in tree parsers or returning trees
     */
    pANTLR3_COMMON_TOKEN    start;
    pANTLR3_COMMON_TOKEN    stop;
    pANTLR3_BASE_TREE	tree;

}
    YAGIParser_expr_op_return;




/** Context tracking structure for 
YAGIParser

 */
struct YAGIParser_Ctx_struct
{
    /** Built in ANTLR3 context tracker contains all the generic elements
     *  required for context tracking.
     */
    pANTLR3_PARSER   pParser;

     YAGIParser_program_return
     (*program)	(struct YAGIParser_Ctx_struct * ctx);

     YAGIParser_block_return
     (*block)	(struct YAGIParser_Ctx_struct * ctx);

     YAGIParser_declaration_return
     (*declaration)	(struct YAGIParser_Ctx_struct * ctx);

     YAGIParser_fluent_decl_return
     (*fluent_decl)	(struct YAGIParser_Ctx_struct * ctx);

     YAGIParser_fact_decl_return
     (*fact_decl)	(struct YAGIParser_Ctx_struct * ctx);

     YAGIParser_domain_return
     (*domain)	(struct YAGIParser_Ctx_struct * ctx);

     YAGIParser_action_decl_return
     (*action_decl)	(struct YAGIParser_Ctx_struct * ctx);

     YAGIParser_effect_return
     (*effect)	(struct YAGIParser_Ctx_struct * ctx);

     YAGIParser_active_sensing_return
     (*active_sensing)	(struct YAGIParser_Ctx_struct * ctx);

     YAGIParser_var_list_return
     (*var_list)	(struct YAGIParser_Ctx_struct * ctx);

     YAGIParser_proc_decl_return
     (*proc_decl)	(struct YAGIParser_Ctx_struct * ctx);

     YAGIParser_passive_sensing_decl_return
     (*passive_sensing_decl)	(struct YAGIParser_Ctx_struct * ctx);

     YAGIParser_assignment_return
     (*assignment)	(struct YAGIParser_Ctx_struct * ctx);

     YAGIParser_statement_return
     (*statement)	(struct YAGIParser_Ctx_struct * ctx);

     YAGIParser_action_exec_return
     (*action_exec)	(struct YAGIParser_Ctx_struct * ctx);

     YAGIParser_value_list_return
     (*value_list)	(struct YAGIParser_Ctx_struct * ctx);

     YAGIParser_test_return
     (*test)	(struct YAGIParser_Ctx_struct * ctx);

     YAGIParser_choose_return
     (*choose)	(struct YAGIParser_Ctx_struct * ctx);

     YAGIParser_pick_return
     (*pick)	(struct YAGIParser_Ctx_struct * ctx);

     YAGIParser_for_loop_return
     (*for_loop)	(struct YAGIParser_Ctx_struct * ctx);

     YAGIParser_conditional_return
     (*conditional)	(struct YAGIParser_Ctx_struct * ctx);

     YAGIParser_while_loop_return
     (*while_loop)	(struct YAGIParser_Ctx_struct * ctx);

     YAGIParser_search_return
     (*search)	(struct YAGIParser_Ctx_struct * ctx);

     YAGIParser_assign_return
     (*assign)	(struct YAGIParser_Ctx_struct * ctx);

     YAGIParser_ass_op_return
     (*ass_op)	(struct YAGIParser_Ctx_struct * ctx);

     YAGIParser_for_loop_assign_return
     (*for_loop_assign)	(struct YAGIParser_Ctx_struct * ctx);

     YAGIParser_conditional_assign_return
     (*conditional_assign)	(struct YAGIParser_Ctx_struct * ctx);

     YAGIParser_formula_outerMost_return
     (*formula_outerMost)	(struct YAGIParser_Ctx_struct * ctx);

     YAGIParser_formula_return
     (*formula)	(struct YAGIParser_Ctx_struct * ctx);

     YAGIParser_formula_connective_return
     (*formula_connective)	(struct YAGIParser_Ctx_struct * ctx);

     YAGIParser_atom_return
     (*atom)	(struct YAGIParser_Ctx_struct * ctx);

     YAGIParser_atom_connector_return
     (*atom_connector)	(struct YAGIParser_Ctx_struct * ctx);

     YAGIParser_set_return
     (*set)	(struct YAGIParser_Ctx_struct * ctx);

     YAGIParser_setexpr_return
     (*setexpr)	(struct YAGIParser_Ctx_struct * ctx);

     YAGIParser_tuple_return
     (*tuple)	(struct YAGIParser_Ctx_struct * ctx);

     YAGIParser_tuple_val_return
     (*tuple_val)	(struct YAGIParser_Ctx_struct * ctx);

     YAGIParser_var_return
     (*var)	(struct YAGIParser_Ctx_struct * ctx);

     YAGIParser_value_return
     (*value)	(struct YAGIParser_Ctx_struct * ctx);

     YAGIParser_valexpr_return
     (*valexpr)	(struct YAGIParser_Ctx_struct * ctx);

     YAGIParser_expr_op_return
     (*expr_op)	(struct YAGIParser_Ctx_struct * ctx);
    // Delegated rules

    const char * (*getGrammarFileName)();
    void            (*reset)  (struct YAGIParser_Ctx_struct * ctx);
    void	    (*free)   (struct YAGIParser_Ctx_struct * ctx);
/* @headerFile.members() */
pANTLR3_BASE_TREE_ADAPTOR	adaptor;
pANTLR3_VECTOR_FACTORY		vectors;
/* End @headerFile.members() */
};

// Function protoypes for the constructor functions that external translation units
// such as delegators and delegates may wish to call.
//
ANTLR3_API pYAGIParser YAGIParserNew         (
pANTLR3_COMMON_TOKEN_STREAM
 instream);
ANTLR3_API pYAGIParser YAGIParserNewSSD      (
pANTLR3_COMMON_TOKEN_STREAM
 instream, pANTLR3_RECOGNIZER_SHARED_STATE state);

/** Symbolic definitions of all the tokens that the 
parser
 will work with.
 * \{
 *
 * Antlr will define EOF, but we can't use that as it it is too common in
 * in C header files and that would be confusing. There is no way to filter this out at the moment
 * so we just undef it here for now. That isn't the value we get back from C recognizers
 * anyway. We are looking for ANTLR3_TOKEN_EOF.
 */
#ifdef	EOF
#undef	EOF
#endif
#ifdef	Tokens
#undef	Tokens
#endif
#define EOF      -1
#define COMMENT      4
#define ID      5
#define INT      6
#define IT_ACTION_DECL      7
#define IT_ACTION_EXEC      8
#define IT_ADD_ASSIGN      9
#define IT_ALL      10
#define IT_AND      11
#define IT_ASSIGN      12
#define IT_ASSIGN_ALL      13
#define IT_ATOM_SETEXPR      14
#define IT_ATOM_VALEXPR      15
#define IT_BLOCK      16
#define IT_CHOOSE      17
#define IT_CONDITIONAL      18
#define IT_EFFECT      19
#define IT_EQ      20
#define IT_EXISTS      21
#define IT_FACT_DECL      22
#define IT_FLUENT_DECL      23
#define IT_FORALL      24
#define IT_FORMULA      25
#define IT_GE      26
#define IT_GT      27
#define IT_IF_ASSIGN      28
#define IT_IMPLIES      29
#define IT_IN      30
#define IT_LE      31
#define IT_LT      32
#define IT_MINUS      33
#define IT_NEQ      34
#define IT_NOT      35
#define IT_OR      36
#define IT_PASS_SENS      37
#define IT_PICK      38
#define IT_PLUS      39
#define IT_PROC_DECL      40
#define IT_PROGRAM      41
#define IT_REMOVE_ASSIGN      42
#define IT_SEARCH      43
#define IT_SENSING      44
#define IT_SIGNAL      45
#define IT_STRING_SET      46
#define IT_TEST      47
#define IT_TUPLE      48
#define IT_TUPLE_SET      49
#define IT_VALUE_LIST      50
#define IT_VAR      51
#define IT_VAR_LIST      52
#define IT_WHILE      53
#define STRING      54
#define TOKEN_ACTION      55
#define TOKEN_ADD_ASSIGN      56
#define TOKEN_ALL      57
#define TOKEN_AND      58
#define TOKEN_ASSIGN      59
#define TOKEN_ASSIGN_ALL      60
#define TOKEN_CHOOSE      61
#define TOKEN_CLOSE_PAREN      62
#define TOKEN_COLON      63
#define TOKEN_COMMA      64
#define TOKEN_DO      65
#define TOKEN_DOMAIN_END      66
#define TOKEN_DOMAIN_INT      67
#define TOKEN_DOMAIN_START      68
#define TOKEN_DOMAIN_STR      69
#define TOKEN_EFFECT      70
#define TOKEN_ELSE      71
#define TOKEN_END_ACTION      72
#define TOKEN_END_CHOOSE      73
#define TOKEN_END_FOR      74
#define TOKEN_END_IF      75
#define TOKEN_END_PASSIVE_SENSING      76
#define TOKEN_END_PICK      77
#define TOKEN_END_PROC      78
#define TOKEN_END_SEARCH      79
#define TOKEN_END_WHILE      80
#define TOKEN_EOL      81
#define TOKEN_EQUALS      82
#define TOKEN_EXISTS      83
#define TOKEN_FACT      84
#define TOKEN_FALSE      85
#define TOKEN_FLUENT      86
#define TOKEN_FOR_ALL      87
#define TOKEN_FROM      88
#define TOKEN_GE      89
#define TOKEN_GT      90
#define TOKEN_IF      91
#define TOKEN_IMPLIES      92
#define TOKEN_IN      93
#define TOKEN_LE      94
#define TOKEN_LT      95
#define TOKEN_MINUS      96
#define TOKEN_NEQUALS      97
#define TOKEN_NOT      98
#define TOKEN_OPEN_PAREN      99
#define TOKEN_OR      100
#define TOKEN_PASSIVE_SENSING      101
#define TOKEN_PATTERN_MATCHING      102
#define TOKEN_PICK      103
#define TOKEN_PLUS      104
#define TOKEN_PRECOND      105
#define TOKEN_PROC      106
#define TOKEN_REMOVE_ASSIGN      107
#define TOKEN_SEARCH      108
#define TOKEN_SENSING      109
#define TOKEN_SET_END      110
#define TOKEN_SET_START      111
#define TOKEN_SIGNAL      112
#define TOKEN_SUCH      113
#define TOKEN_TEST      114
#define TOKEN_THEN      115
#define TOKEN_TRUE      116
#define TOKEN_VAR_DECL_START      117
#define TOKEN_WHILE      118
#define WHITESPACE      119
#ifdef	EOF
#undef	EOF
#define	EOF	ANTLR3_TOKEN_EOF
#endif

#ifndef TOKENSOURCE
#define TOKENSOURCE(lxr) lxr->pLexer->rec->state->tokSource
#endif

/* End of token definitions for YAGIParser
 * =============================================================================
 */
/** } */

#ifdef __cplusplus
}
#endif

#endif

/* END - Note:Keep extra line feed to satisfy UNIX systems */

//******************************************************************************
//Treegrammar for the YAGI programming language
//Author: Christopher Maier
//Date: 2014-05-19
//******************************************************************************
tree grammar YAGITreeWalker;

options 
{
    tokenVocab	    = YAGI;
    language	    = C;
    ASTLabelType    = pANTLR3_BASE_TREE;
}

@header {
    #include "../cppInterfaceClasses/CToCppBridge.h"
}

//******************************************************************************
//Basic program structure
//******************************************************************************
program	
	: ^(IT_PROGRAM declaration* statement*)
	{
	    ADD_PROGRAM();
        }
	
	;
	
block	
	: ^(IT_BLOCK ({ADD_BLOCK();}) (statement {CONSUME_STATEMENT();})+)
	;
	
//******************************************************************************
//Declarations
//******************************************************************************
declaration
	:	fluent_decl
	|	fact_decl
	|	action_decl
	| 	proc_decl
    	|   	exo_event_decl
    	|	sensing_decl
	;

fluent_decl
	: ^(IT_FLUENT_DECL ID ({ADD_FLUENT_DECL($ID->toString($ID));}) (domain {CONSUME_DOMAIN();})*) 
	;	
	
fact_decl
	: ^(IT_FACT_DECL ID ({ADD_FACT_DECL($ID->toString($ID));}) (domain {CONSUME_DOMAIN();})*) 
	;
	
domain	
	: TOKEN_DOMAIN_STR {ADD_DOMAIN_STRING();}
	| ^(IT_STRING_SET {ADD_DOMAIN_STRING_ELEMENTS();} (st=STRING {ADD_DOMAIN_ELEMENT($st->toString($st));})+)
	;
	
action_decl
	: ^(IT_ACTION_DECL ID ^(IT_VAR_LIST {ADD_VAR_LIST();} var_list?) (^(IT_EXTERNAL_VARS {ADD_VAR_LIST();} var_list))? formula_outerMost? effect (^(IT_SIGNAL valexpr))? ) 	
	{
	    ADD_ACTION_DECL($ID->toString($ID));
        }
	
	;
	
effect	
	: ^(IT_EFFECT block)
	{
	  ADD_EFFECT();
	}
	;
	
var_list
	: (var {CONSUME_VAR();})+
	;
	

proc_decl
	: ^(IT_PROC_DECL ID (^(IT_VAR_LIST {ADD_VAR_LIST();} var_list))? block)
	
	{
	  ADD_PROC_DECL($ID->toString($ID));
	}
	;	

exo_event_decl
	: ^(IT_EXO_EVENT ID ^(IT_VAR_LIST {ADD_VAR_LIST();} var_list) block)
	
	{
	  ADD_EXO_EVENT_DECL($ID->toString($ID));
	}
	;	
	
sensing_decl	
	: ^(IT_SENSING ID ^(IT_VAR_LIST {ADD_VAR_LIST();} var_list?) (^(IT_VAR_LIST {ADD_VAR_LIST();} var_list))? formula)
	
	{
	  ADD_SENSING_DECL($ID->toString($ID));
	}
	;
	
//******************************************************************************
//Statements
//******************************************************************************
statement
	:	id_term
	|	var_assign
	|	test
	|	choose
	| 	pick
	|	for_loop
	|	conditional
	|	while_loop
    	| 	search
	;

id_term
	:	
	^(IT_PROC_EXEC ID (^(IT_VALUE_LIST value_list))?) { ADD_PROC_EXEC($ID->toString($ID));}
	|	^(IT_FLUENT_QUERY ID) 	{ ADD_FLUENT_QUERY($ID->toString($ID));}
	| 	^(ass_op ID setexpr) {ADD_ID_ASSIGN($ID->toString($ID));}
	;	
	
value_list	
	: ({ADD_VALUE_LIST();}) (value {CONSUME_VALUE();})+
	;
	
test	
	: ^(IT_TEST formula)
	
	{
	  ADD_TEST();
	}
	;	
	
choose	
	: ^(IT_CHOOSE ({ADD_CHOOSE();}) (block {CONSUME_BLOCK();})+)
	;	
	
pick	
	: ^(IT_PICK tuple setexpr block)
	
	{
	  ADD_PICK();
	}
	
	;	
	
for_loop	
	: ^(IT_FORALL tuple setexpr block)
	
	{
	  ADD_FOR_LOOP();
	}
	;

conditional
	: ^(IT_CONDITIONAL formula block block?)
	
	{
	  ADD_CONDITIONAL();
	}
	
	;
	
while_loop
	: ^(IT_WHILE formula block)
	
	{
	  ADD_WHILE_LOOP();
	}
	;	
	
search	
	: ^(IT_SEARCH block)

	{
	  ADD_SEARCH();
	}
	
	;
	
	
//******************************************************************************
//Assignments
//******************************************************************************
var_assign	
	:	^(IT_ASSIGN var value) {ADD_VAR_ASSIGN();}
	;
	
ass_op  
	:	(IT_ASSIGN {ADD_ASSIGN_OP("=");}
                  | IT_ADD_ASSIGN {ADD_ASSIGN_OP("+=");}
                  | IT_REMOVE_ASSIGN {ADD_ASSIGN_OP("-=");}
                )
        ;
    
//******************************************************************************
//Formulas
//******************************************************************************
formula_outerMost
	: ^(IT_FORMULA formula)
	;

formula	
	:	atom {ADD_ATOM();}
	|	^(IT_NOT formula) {ADD_NEGATION();}
	|	^(formula_connective atom ({ADD_ATOM();}) formula) {ADD_CONNECTED_FORMULA();}
	|	^(IT_EXISTS tuple setexpr formula?) {ADD_EXISTS();} 
	|	^(IT_ALL tuple setexpr formula?) {ADD_ALL();}
	|	^(IT_IN tuple setexpr) {ADD_IN();}
	;
	
formula_connective
	:	IT_AND {ADD_FORMULA_CONNECTIVE("&&");}
	| 	IT_OR {ADD_FORMULA_CONNECTIVE("||");}
	|    	IT_IMPLIES {ADD_FORMULA_CONNECTIVE("->");}
	;

atom
	:	^(IT_ATOM_VALEXPR ^(atom_connector value value))
	|	^(IT_ATOM_SETEXPR ^(atom_connector setexpr setexpr))
	|	(TOKEN_TRUE {ADD_CONSTANT("true");} | TOKEN_FALSE {ADD_CONSTANT("false");})
	;
	
atom_connector
	:	IT_EQ {ADD_ATOM_CONNECTIVE("==");}
	|  	IT_NEQ {ADD_ATOM_CONNECTIVE("!=");}
	| 	IT_LE {ADD_ATOM_CONNECTIVE("<=");}
	| 	IT_GE {ADD_ATOM_CONNECTIVE(">=");}
	| 	IT_LT {ADD_ATOM_CONNECTIVE("<");}
	| 	IT_GT {ADD_ATOM_CONNECTIVE(">");}
	;
	
//******************************************************************************
//Sets
//******************************************************************************
setexpr	:	^(expr_op setexpr setexpr) {ADD_SETEXPR();}
	|	^(IT_TUPLE_SET ({ADD_TUPLE_SET();}) (tuple {CONSUME_TUPLE();})*)
	|	ID {ADD_ID($ID->toString($ID));}
	;
	
	
//******************************************************************************
//Tuples
//****************************************************************************** 
tuple	
	:	^(IT_TUPLE ({ADD_TUPLE();}) (tuple_val {CONSUME_TUPLE_VAL();})*)
	;
	
tuple_val 
	:	STRING {ADD_STRING($STRING->toString($STRING));}
	|     	TOKEN_PATTERN_MATCHING {ADD_PATTERN_MATCH();}
	|	TOKEN_INCOMPLETE_KNOWLEDGE {ADD_INCOMPLETE_KNOWLEDGE();}
	|     	var
	;
	
//******************************************************************************
//Variables
//******************************************************************************
var	
	:	^(IT_VAR ID)
	{
	  ADD_VAR($ID->toString($ID));
	}
	;

value	
	:	STRING {ADD_STRING($STRING->toString($STRING));}
	|	var
	;

valexpr	
	:	^(expr_op valexpr valexpr) {ADD_VALEXPR();}
	|	STRING {ADD_STRING($STRING->toString($STRING));}
	|	var
	;

expr_op
	:	IT_PLUS {ADD_EXPR_OP("+");}
	| 	IT_MINUS {ADD_EXPR_OP("-");}
	;
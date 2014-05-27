//******************************************************************************
//Treegrammar for the YAGI programming language
//Author: Christopher Maier
//Date: 2014-05-19
//Version: 0.1
//Changelog:
//  - 0.1: Initial version
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
	: ^(IT_BLOCK statement+)
	;
	
//******************************************************************************
//Declarations
//******************************************************************************
declaration
	:	fluent_decl
	|	fact_decl
	|	action_decl
	| 	proc_decl
    	|   	passive_sensing_decl
	|	assignment
	;

fluent_decl
	: ^(IT_FLUENT_DECL ID ({ADD_FLUENT_DECL($ID->toString($ID));}) (domain {CONSUME_DOMAIN();})+) 
	;	
	
fact_decl
	: ^(IT_FACT_DECL ID ({ADD_FACT_DECL($ID->toString($ID));}) (domain {CONSUME_DOMAIN();})+) 
	;
	
domain	
	:	TOKEN_DOMAIN_INT {ADD_DOMAIN_INTEGER();}
		  | TOKEN_DOMAIN_STR {ADD_DOMAIN_STRING();}
		  | ^(IT_STRING_SET {ADD_DOMAIN_STRING_ELEMENTS();} (st=STRING {ADD_DOMAIN_ELEMENT($st->toString($st));})+)
	;
	
action_decl
	: ^(IT_ACTION_DECL ID ^(IT_VAR_LIST var_list) formula_outerMost? effect? active_sensing? (^(IT_SIGNAL valexpr))? )
	
	{
	    ADD_ACTION_DECL($ID->toString($ID));
        }
	
	;
	
effect	
	: ^(IT_EFFECT ^(IT_BLOCK assignment+))
	
	{
	    ADD_EFFECT();
        }
	;
	
active_sensing	
	: ^(IT_SENSING ^(IT_VAR_LIST var_list) ^(IT_BLOCK assignment+))
	
	{
	    ADD_ACTIVE_SENSING();
        }	
	;
	
	
var_list
	: var+
	
	{
	  ADD_VAR_LIST();
	}
	;
	

proc_decl
	: ^(IT_PROC_DECL ID (^(IT_VAR_LIST var_list))? block)
	;	
	
passive_sensing_decl
	: ^(IT_PASS_SENS ID ^(IT_VAR_LIST var_list) ^(IT_BLOCK assignment+))
                
	;	
	
assignment
	:	assign
	|	for_loop_assign
	|	conditional_assign
	;
	
	
//******************************************************************************
//Statements
//******************************************************************************
statement
	:	action_exec
	|	test
	|	choose
	| 	pick
	|	for_loop
	|	conditional
	|	while_loop
    	| 	search
	;

action_exec
	: ^(IT_ACTION_EXEC ID ^(IT_VALUE_LIST value_list))
	;	
	
value_list	
	: value+
	;
	
test	
	: ^(IT_TEST formula)
	;	
	
choose	
	: ^(IT_CHOOSE block block+)
	;	
	
pick	
	: ^(IT_PICK tuple setexpr block)
	;	
	
for_loop	
	: ^(IT_FORALL tuple setexpr block)
	;

conditional
	: ^(IT_CONDITIONAL formula ^(IT_BLOCK block) block?)
	;
	
while_loop
	: ^(IT_WHILE formula block)
	;	
	
search	
	: ^(IT_SEARCH block)
	;
	
	
//******************************************************************************
//Assignments
//******************************************************************************
assign	
	:	^(IT_ASSIGN var valexpr) {ADD_VAR_ASSIGN();}
	|	^(ass_op ID setexpr)
	;
	
ass_op  
	:	(IT_ASSIGN {printf("bli\n");}
                  | IT_ADD_ASSIGN {printf("bla\n");}
                  | IT_REMOVE_ASSIGN {printf("blo\n");}
                )
        ;
        
for_loop_assign
	: ^(IT_ASSIGN_ALL tuple setexpr ^(IT_BLOCK assignment+))
	;
	
conditional_assign
	: ^(IT_IF_ASSIGN formula ^(IT_BLOCK assignment+) (^(IT_BLOCK assignment+))?)
	;


//******************************************************************************
//Formulas
//******************************************************************************
formula_outerMost
	: ^(IT_FORMULA formula)
	;

formula	
	:	atom
	|	^(IT_NOT formula)
	|	^(formular_connective atom formula)
	|	^(IT_EXISTS tuple setexpr formula?)
	|	^(IT_ALL tuple setexpr formula?)
	|	^(IT_IN tuple setexpr)
	;
	
formular_connective
	:	IT_AND {printf("bliz\n");}
	| 	IT_OR {printf("blaz\n");}
	|    	IT_IMPLIES {printf("bloz\n");}
	;

atom
	:	^(IT_ATOM_VALEXPR ^(atom_connector valexpr valexpr))
	|	^(IT_ATOM_SETEXPR ^(atom_connector setexpr setexpr))
	|	(TOKEN_TRUE | TOKEN_FALSE)
	;
	
atom_connector
	:	IT_EQ {printf("arrr\n");}
	|  	IT_NEQ {printf("brrr\n");}
	| 	IT_LE {printf("crrr\n");}
	| 	IT_GE {printf("drrr\n");}
	| 	IT_LT {printf("errr\n");}
	| 	IT_GT {printf("frrr\n");}
	;
	
//******************************************************************************
//Sets
//******************************************************************************
setexpr	:	^(expr_op setexpr setexpr) 
	|	^(IT_TUPLE_SET tuple+)
	|	ID
	;
	
	
//******************************************************************************
//Tuples
//******************************************************************************	
tuple	
	:	^(IT_TUPLE tuple_val+)
	;
	
tuple_val 
	:	STRING {ADD_STRING($STRING->toString($STRING));}
	|     	TOKEN_PATTERN_MATCHING
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
	:	INT {ADD_INT($INT->toString($INT));}
	|	STRING {ADD_STRING($STRING->toString($STRING));}
	|	var
	;

valexpr	
	:	^(expr_op valexpr valexpr) {ADD_VALEXPR();}
	|	INT {ADD_INT($INT->toString($INT));}
	|	STRING {ADD_STRING($STRING->toString($STRING));}
	|	var
	;

expr_op
	:	IT_PLUS {ADD_EXPR_OP("+");}
	| 	IT_MINUS {ADD_EXPR_OP("-");}
	;
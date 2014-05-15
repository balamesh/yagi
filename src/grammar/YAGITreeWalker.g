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
program	:       (declaration | block)+
	;

block   :       (statement)+;

//******************************************************************************
//Declarations
//******************************************************************************
declaration
	:	fluent_decl EOL
	|	fact_decl EOL
	|	action_decl
	|	proc_decl
	|	passive_sensing_decl
	|	assignment
	;

fluent_decl
	:	^(FLUENT ID set) 
	  {
	    ADD_FLUENT_DECL($ID->toString($ID));
          }
	;

fact_decl
	:	FACT ID (DOMAIN_START set DOMAIN_END)* 
	;

action_decl
	:	ACTION ID (ARG_LIST_START varlist ARG_LIST_END)?
		(PRECOND COLON formula_outerMost)?
		(effect | sensing)?
		(SIGNAL COLON valexpr EOL)?
		END ACTION
	;

effect :        EFFECT COLON (assignment)*
        ;

sensing :       SENSING ARG_LIST_START varlist ARG_LIST_END COLON (assignment* | case_line*)
        ;

passive_sensing_decl    : PASSIVE_SENSING ID (ARG_LIST_START varlist 
                          ARG_LIST_END)? (assignment* | case_line*) END PASSIVE_SENSING   
                        ;

case_line :     CASE formula COLON (assignment)* BREAK
          ;

proc_decl
	:	PROC ID (ARG_LIST_START varlist ARG_LIST_END)? block END PROC
	;
	
varlist
	:	
	|	var ( LIST_SEPERATOR var )*
        |       /* epsilon */ 
	;
	
//******************************************************************************
//Statements
//******************************************************************************
//pick decl fehlt!
//while loop fehlt
statement
	:	action_exec EOL
	|	pick
	|	test EOL
	|	for_loop
	|	if_then_else
	|	choose
        |   search
	;

action_exec
	:	ID ARG_LIST_START arglist ARG_LIST_END
	;

arglist
	:	
	|	value ( LIST_SEPERATOR value )*
	;

	
	;

test	:	TEST formula EOF
	;

for_loop:	FOR tuple IN setexpr DO block END FOR;

if_then_else
	:	IF ARG_LIST_START formula ARG_LIST_END THEN block (ELSE block)? END IF
	;

choose	:	CHOOSE block ( LOGIC_OR block )+ END CHOOSE
	;

search  :       SEARCH block END SEARCH
        ;
	
//******************************************************************************
//Assignments
//******************************************************************************
assignment
	:	assign EOL
	|	for_loop_assign
	|	conditional_assign
	;

for_loop_assign
	:	FOR tuple IN setexpr DO (assignment)* END FOR
	;
	
conditional_assign
	:	IF formula THEN (assignment)* (ELSE (assignment)*)? END IF
	;

assign	
        : var assign_op valexpr
//        | term assign_op setexpr    201403: is term used for anything except assign? is at[x] = ... still a valid assignment? 
	;

assign_op
	:	SET_ASSIGN
	| 	SET_ADD
	| 	SET_REMOVE
	;

//******************************************************************************
//Formulas
//******************************************************************************
formula_outerMost: formula EOL;

formula	:	atom
	|	LOGIC_NOT ARG_LIST_START formula ARG_LIST_END
	|	ARG_LIST_START atom connective formula ARG_LIST_END
	|	LOGIC_EXISTS tuple IN setexpr (SUCH formula)?
	|	LOGIC_ALL tuple IN setexpr (SUCH formula)?
	;
	
//implies!
connective
	:	LOGIC_AND
	|	LOGIC_OR
	;	

atom
	:	valexpr comp_op valexpr
	|	setexpr comp_op setexpr
	|	(LOGIC_TRUE | LOGIC_FALSE)
	;

comp_op
	:	MATH_EQUALS
	|	MATH_NEQUALS
	|	MATH_LE
	|	MATH_GE	
	|	MATH_LT
	|	MATH_GT
	;
	
//******************************************************************************
//Sets
//******************************************************************************
//only tuple_list, remove term
set  
	:	^(BREAK id_set) {ADD_ID_SET();}
	;

tuple_set :     tuple (LIST_SEPERATOR tuple)*;

//id_list
id_set :     (id=ID 
	  { 
	    ADD_ID($id->toString($id)); 
	  })+
       ;

//remove value, value_set
value_set :     value (LIST_SEPERATOR value )*;

setexpr	:	set ((MATH_OP_PLUS | MATH_OP_MINUS) set)*
	;
	
//******************************************************************************
//Tuples
//******************************************************************************
//modify with var_list, id_list
tuple   :       MATH_LT (ID | var) ( LIST_SEPERATOR (ID | var))* MATH_GT;


//******************************************************************************
//Variables
//******************************************************************************
var
	:	VAR_DECL_START ID
	;

//******************************************************************************
//Terms and Values
//******************************************************************************
//remove term?
term
 	:	ID ( DOMAIN_START value DOMAIN_END )*
	;

valexpr	:	value ((MATH_OP_PLUS | MATH_OP_MINUS) value)*
	;

value
	:   (INT | STRING)
	|	var
	;
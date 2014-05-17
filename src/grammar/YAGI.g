grammar YAGI;

options {
    language = C;
    output = AST;
    ASTLabelType=pANTLR3_BASE_TREE;
}

//imaginary tokens
tokens  
{ 
  IT_FLUENT_DECL; 
  IT_STRING_SET;
  IT_TUPLE_SET;
  IT_FACT_DECL;
  IT_PROGRAM;
  IT_ASSIGN;
  IT_ADD_ADDASSIGN;
  IT_REMOVE_ASSIGN;
  IT_PLUS;
  IT_MINUS;
  IT_TUPLE;
  IT_VAR;
} 

@header {
    #define _empty NULL
}

program	:	(declaration | statement)+ -> ^(IT_PROGRAM declaration* statement*)
	;
	
block	:	statement+
	;
	
declaration
	:	fluent_decl
	|	fact_decl
	|	action_decl
	| 	proc_decl
    	|   	passive_sensing_decl
	|	assignment
	;
	
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
	
	
var	:	TOKEN_VAR_DECL_START ID -> ^(IT_VAR ID)
	;
	
value	:	INT|STRING|var
	;
	
valexpr	:	value ((TOKEN_PLUS | TOKEN_MINUS) value)*
	;

tuple	:	TOKEN_LT (
		  tuple_val (TOKEN_COMMA tuple_val)* -> ^(IT_TUPLE tuple_val+)
	 	) TOKEN_GT
	;
	
tuple_val : 	STRING
	  |     TOKEN_PATTERN_MATCHING
	  |     var
          ;
	
set	:	TOKEN_SET_START tuple (TOKEN_COMMA tuple)* TOKEN_SET_END -> ^(IT_TUPLE_SET tuple+)
	|	ID
	;
	
setexpr	:	set (expr_op set)* -> ^(set ^(expr_op set)*) 
	;
	
expr_op:	TOKEN_PLUS -> IT_PLUS 
	      | TOKEN_MINUS -> IT_MINUS
       ;
	
fluent_decl
	:	TOKEN_FLUENT ID (TOKEN_DOMAIN_START domain TOKEN_DOMAIN_END)+ TOKEN_EOL -> ^(IT_FLUENT_DECL ID domain+) 
	;
	
domain: 	TOKEN_DOMAIN_INT -> TOKEN_DOMAIN_INT
		  | TOKEN_DOMAIN_STR -> TOKEN_DOMAIN_STR
		  | TOKEN_SET_START STRING (TOKEN_COMMA STRING)* TOKEN_SET_END -> ^(IT_STRING_SET STRING+)
	;
		 

fact_decl
	:	TOKEN_FACT ID (TOKEN_DOMAIN_START domain TOKEN_DOMAIN_END)+ TOKEN_EOL -> ^(IT_FACT_DECL ID domain+) 
	;

action_decl
	:	 TOKEN_ACTION ID (TOKEN_OPEN_PAREN (var (TOKEN_COMMA var)* | /*eps*/) TOKEN_CLOSE_PAREN)
		(TOKEN_PRECOND formula_outerMost)?
		(effect | sensing)
		(TOKEN_SIGNAL valexpr TOKEN_EOL)?
		TOKEN_END_ACTION
	;

formula_outerMost
	:	 formula TOKEN_EOL
	;

formula	:	atom
	|	TOKEN_NOT TOKEN_OPEN_PAREN formula TOKEN_CLOSE_PAREN
	|	TOKEN_OPEN_PAREN atom (TOKEN_AND | TOKEN_OR | TOKEN_IMPLIES) formula TOKEN_CLOSE_PAREN
	|	TOKEN_EXISTS tuple TOKEN_IN setexpr (TOKEN_SUCH formula)?
	|	TOKEN_ALL tuple TOKEN_IN setexpr (TOKEN_SUCH formula)?
	|	tuple TOKEN_IN setexpr
	;

atom
	:	valexpr (TOKEN_EQUALS |  TOKEN_NEQUALS | TOKEN_LE | TOKEN_GE | TOKEN_LT | TOKEN_GT) valexpr
	|	setexpr (TOKEN_EQUALS |  TOKEN_NEQUALS | TOKEN_LE | TOKEN_GE | TOKEN_LT | TOKEN_GT) setexpr
	|	(TOKEN_TRUE | TOKEN_FALSE)
	;

effect	:	TOKEN_EFFECT assignment*
	;
	
sensing	:	TOKEN_SENSING TOKEN_OPEN_PAREN var (TOKEN_COMMA var)* TOKEN_CLOSE_PAREN TOKEN_COLON assignment+
	;
	
passive_sensing_decl
	:	TOKEN_PASSIVE_SENSING ID TOKEN_OPEN_PAREN var (TOKEN_COMMA var)* 
		TOKEN_CLOSE_PAREN assignment+  TOKEN_END_PASSIVE_SENSING   
                        
	;
	
assignment
	:	assign TOKEN_EOL
	|	for_loop_assign
	|	conditional_assign
	;

for_loop_assign
	:	TOKEN_ASSIGN_ALL tuple TOKEN_IN setexpr assignment+ TOKEN_END_FOR
	;
	
conditional_assign
	:	TOKEN_IF formula TOKEN_THEN (assignment)+ (TOKEN_ELSE assignment+)? TOKEN_END_IF
	;

assign	:	var TOKEN_ASSIGN valexpr -> ^(IT_ASSIGN var valexpr)
	|	ID ass_op setexpr -> ^(ass_op ID setexpr)
	;
	
ass_op  :	(TOKEN_ASSIGN -> IT_ASSIGN 
                  | TOKEN_ADD_ASSIGN -> IT_ADD_ADDASSIGN 
                  | TOKEN_REMOVE_ASSIGN -> IT_REMOVE_ASSIGN
                )
        ;

action_exec
	:	ID TOKEN_OPEN_PAREN (value (TOKEN_COMMA value)*)? TOKEN_CLOSE_PAREN TOKEN_EOL
	;

test	:	TOKEN_TEST formula TOKEN_EOL
	;

choose	:	TOKEN_CHOOSE block ( TOKEN_OR block )+ TOKEN_END_CHOOSE
	;

pick	:	 TOKEN_PICK tuple TOKEN_FROM setexpr TOKEN_SUCH block TOKEN_END_PICK
	;

conditional
	:	TOKEN_IF TOKEN_OPEN_PAREN formula TOKEN_CLOSE_PAREN TOKEN_THEN block 
		(TOKEN_ELSE block)? TOKEN_END_IF
	;

while_loop
	:	 TOKEN_WHILE formula TOKEN_DO block TOKEN_END_WHILE
	;
	
for_loop	:	 TOKEN_FOR_ALL tuple TOKEN_IN setexpr TOKEN_DO block TOKEN_END_FOR
	;

search	:	 TOKEN_SEARCH block TOKEN_END_SEARCH
	;

proc_decl
	:	TOKEN_PROC ID (TOKEN_OPEN_PAREN var (TOKEN_COMMA var)* 
		TOKEN_CLOSE_PAREN)? block TOKEN_END_PROC
	;
	
	
//******************************************************************************
//Tokens
//******************************************************************************
TOKEN_EOL : ';';
TOKEN_COLON : ':';

TOKEN_PICK : 'pick';
TOKEN_END_PICK
	:	'end pick'
	;

TOKEN_FROM : 'from';
TOKEN_SUCH : 'such';

TOKEN_TEST : 'test';
TOKEN_IN : 'in';
TOKEN_DO : 'do';

TOKEN_IF : 'if';
TOKEN_END_IF
	:	'end if'
	;

TOKEN_THEN : 'then';
TOKEN_ELSE : 'else';

TOKEN_CHOOSE : 'choose';
TOKEN_END_CHOOSE
	:	'end choose'
	;

TOKEN_WHILE
	:	'while'
	;
	
TOKEN_END_WHILE
	:	'end while'
	;

TOKEN_END_FOR
	:	'end for'
	;

TOKEN_DOMAIN_INT
	:	'Integer'
	;

TOKEN_DOMAIN_STR
	:	'String'
	;

TOKEN_ACTION : 'action';
TOKEN_END_ACTION
	:	'end action'
	;

TOKEN_PRECOND : 'precondition:';
TOKEN_EFFECT : 'effect:';
TOKEN_SIGNAL : 'signal:';
TOKEN_SENSING : 'sensing';

TOKEN_PASSIVE_SENSING : 'passive-sensing';
TOKEN_END_PASSIVE_SENSING
	:	'end passive-sensing'
	;

TOKEN_NOT: 'not';
TOKEN_EXISTS: 'exists';
TOKEN_ALL: 'all';
TOKEN_IMPLIES: 'implies';

TOKEN_ASSIGN : '=';
TOKEN_ADD_ASSIGN: '+=';
TOKEN_REMOVE_ASSIGN: '-=';

TOKEN_EQUALS: '==';
TOKEN_NEQUALS: '!=';
TOKEN_LE: '<=';
TOKEN_GE: '>=';
TOKEN_LT: '<';
TOKEN_GT: '>';
TOKEN_PLUS : '+';
TOKEN_MINUS : '-';

TOKEN_AND: 'and';
TOKEN_OR: 'or';
TOKEN_TRUE: 'true';
TOKEN_FALSE: 'false';

TOKEN_PATTERN_MATCHING 
	:	 '_';

TOKEN_SET_START: '{';
TOKEN_SET_END: '}';

TOKEN_DOMAIN_START: '[';
TOKEN_DOMAIN_END: ']';

TOKEN_VAR_DECL_START: '$';
TOKEN_FLUENT : 'fluent';


TOKEN_END_SEARCH
	:	'end search';

TOKEN_SEARCH
	:	'search'
	;

TOKEN_OPEN_PAREN
	:	'('
	;
	
TOKEN_CLOSE_PAREN
	:	')';
	
TOKEN_COMMA
	:	','
	;

TOKEN_END_PROC
	:	'end proc';

TOKEN_PROC : 	'proc'
	  ; 

TOKEN_FACT
	:	'fact'
	;
	
TOKEN_FOR_ALL
	:	'for all'
	;

TOKEN_ASSIGN_ALL
	:	'assign all'
	;
	
WHITESPACE : ( '\t' | ' ' | '\r' | '\n'| '\u000C' )+    {$channel=HIDDEN;} ;

ID  :	('a'..'z'|'A'..'Z'|'_') ('a'..'z'|'A'..'Z'|'0'..'9'|'_')*
    ;

INT :	('0'..'9')+
    ;

STRING
    :  '"' ( ~('\\'|'"') )* '"'
    ;

COMMENT
    :	'//' ~('\n'|'\r')* '\r'? '\n' {$channel=HIDDEN;}
    ;
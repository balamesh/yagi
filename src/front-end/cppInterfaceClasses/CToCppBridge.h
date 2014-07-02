/*
 * CToCppBridge.h
 *
 *  Created on: Apr 23, 2014
 *      Author: cmaier
 */
#ifndef CTOCPPBRIDGE_H_
#define CTOCPPBRIDGE_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include    <antlr3.h>

  struct YAGICallbackCollection
  {
      //Basic program structure
      void (*addProgramCallback)();
      void (*addBlockCallback)();
      void (*consumeBlockCallback)();

      //Declarations
      void (*addFluentDeclCallback)(pANTLR3_STRING fluentName);
      void (*addFactDeclCallback)(pANTLR3_STRING factName);
      void (*addActionDeclCallback)(pANTLR3_STRING actionName);
      void (*addProcDeclCallback)(pANTLR3_STRING procName);
      void (*addExoEventDeclCallback)(pANTLR3_STRING exoEventName);
      void (*addSensingDeclCallback)(pANTLR3_STRING sensingName);

      //Domains
      void (*addDomainElementCallback)(pANTLR3_STRING domainElement);
      void (*addDomainStringCallback)();
      void (*addDomainStringElementsCallback)();
      void (*consumeDomainCallback)();

      //Effect
      void (*addEffectCallback)();

      //Varlist
      void (*addVarListCallback)();

      //Assignment
      void (*addVarAssignCallback)();
      void (*addPatternMatchCallback)();
      void (*addFluentAssignCallback)(pANTLR3_STRING fluentName);
      void (*addAssignOpCallback)(char* op);
      void (*consumeAssignmentCallback)();
      void (*addForLoopAssignCallback)();
      void (*addConditionalAssignCallback)();
      void (*addConditionalAssignElseCallback)();
      void (*addIncompleteKnowledgeCallback)();

      //Statements
      void (*addProcExecCallback)(pANTLR3_STRING procName);
      void (*addFluentQueryCallback)(pANTLR3_STRING fluentName);
      void (*addTestCallback)();
      void (*addChooseCallback)();
      void (*addPickCallback)();
      void (*addForLoopCallback)();
      void (*addConditionalCallback)();
      void (*addWhileLoopCallback)();
      void (*addSearchCallback)();
      void (*consumeStatementCallback)();

      //ValueList
      void (*addValueListCallback)();

      //Formulas
      void (*addFormulaConnectiveCallback)(char* conn);
      void (*addAtomConnectiveCallback)(char* conn);
      void (*addConstantCallback)(char* constant);
      void (*addAtomCallback)();
      void (*addNegationCallback)();
      void (*addConnectedFormulaCallback)();
      void (*addExistsCallback)();
      void (*addAllCallback)();
      void (*addInCallback)();

      //Sets
      void (*addTupleSetCallback)();
      void (*addSetExprCallback)();

      //Tuples
      void (*addTupleCallback)();
      void (*consumeTupleValCallback)();
      void (*consumeTupleCallback)();

      //Variables, Types, ID, Values
      void (*addVarCallback)(pANTLR3_STRING varName);
      void (*consumeVariableCallback)();
      void (*addStringCallback)(pANTLR3_STRING stringVal);
      void (*addIDCallback)(pANTLR3_STRING id);

      //Values, ValExpr
      void (*addValueExpressionCallback)();
      void (*consumeValueCallback)();
      void (*addExprOperatorCallback)(char* op);

  };

  extern struct YAGICallbackCollection yagiCallbackCollection;

//Basic program structure
#define ADD_PROGRAM() yagiCallbackCollection.addProgramCallback()
#define ADD_BLOCK() yagiCallbackCollection.addBlockCallback()
#define CONSUME_BLOCK() yagiCallbackCollection.consumeBlockCallback()

//Declarations
#define ADD_FLUENT_DECL(x) yagiCallbackCollection.addFluentDeclCallback(x)
#define ADD_FACT_DECL(x) yagiCallbackCollection.addFactDeclCallback(x)
#define ADD_ACTION_DECL(x) yagiCallbackCollection.addActionDeclCallback(x)
#define ADD_PROC_DECL(x) yagiCallbackCollection.addProcDeclCallback(x)
#define ADD_EXO_EVENT_DECL(x) yagiCallbackCollection.addExoEventDeclCallback(x)
#define ADD_SENSING_DECL(x) yagiCallbackCollection.addSensingDeclCallback(x)

//Domains
#define ADD_DOMAIN_ELEMENT(x) yagiCallbackCollection.addDomainElementCallback(x)
#define ADD_DOMAIN_STRING() yagiCallbackCollection.addDomainStringCallback()
#define ADD_DOMAIN_STRING_ELEMENTS() yagiCallbackCollection.addDomainStringElementsCallback()
#define CONSUME_DOMAIN() yagiCallbackCollection.consumeDomainCallback()

//Effect
#define ADD_EFFECT() yagiCallbackCollection.addEffectCallback()

//Varlist
#define ADD_VAR_LIST() yagiCallbackCollection.addVarListCallback()

//Assignment
#define ADD_VAR_ASSIGN() yagiCallbackCollection.addVarAssignCallback()
#define ADD_PATTERN_MATCH() yagiCallbackCollection.addPatternMatchCallback()
#define ADD_FLUENT_ASSIGN(x) yagiCallbackCollection.addFluentAssignCallback(x)
#define ADD_ASSIGN_OP(x) yagiCallbackCollection.addAssignOpCallback(x)
#define CONSUME_ASSIGNMENT() yagiCallbackCollection.consumeAssignmentCallback()
#define ADD_FOR_LOOP_ASSIGN() yagiCallbackCollection.addForLoopAssignCallback()
#define ADD_CONDITIONAL_ASSIGN() yagiCallbackCollection.addConditionalAssignCallback()
#define ADD_CONDITIONAL_ASSIGN_ELSE() yagiCallbackCollection.addConditionalAssignElseCallback()
#define ADD_INCOMPLETE_KNOWLEDGE() yagiCallbackCollection.addIncompleteKnowledgeCallback()

//Statements
#define ADD_PROC_EXEC(x) yagiCallbackCollection.addProcExecCallback(x)
#define ADD_FLUENT_QUERY(x) yagiCallbackCollection.addFluentQueryCallback(x)
#define ADD_TEST() yagiCallbackCollection.addTestCallback()
#define ADD_CHOOSE() yagiCallbackCollection.addChooseCallback()
#define ADD_PICK() yagiCallbackCollection.addPickCallback()
#define ADD_FOR_LOOP() yagiCallbackCollection.addForLoopCallback()
#define ADD_CONDITIONAL() yagiCallbackCollection.addConditionalCallback()
#define ADD_WHILE_LOOP() yagiCallbackCollection.addWhileLoopCallback()
#define ADD_SEARCH() yagiCallbackCollection.addSearchCallback()
#define CONSUME_STATEMENT() yagiCallbackCollection.consumeStatementCallback()

//ValueList
#define ADD_VALUE_LIST() yagiCallbackCollection.addValueListCallback()

//Formulas
#define ADD_ATOM_CONNECTIVE(x) yagiCallbackCollection.addAtomConnectiveCallback(x)
#define ADD_FORMULA_CONNECTIVE(x) yagiCallbackCollection.addFormulaConnectiveCallback(x)
#define ADD_CONSTANT(x) yagiCallbackCollection.addConstantCallback(x)
#define ADD_ATOM() yagiCallbackCollection.addAtomCallback()
#define ADD_NEGATION() yagiCallbackCollection.addNegationCallback()
#define ADD_CONNECTED_FORMULA() yagiCallbackCollection.addConnectedFormulaCallback()
#define ADD_EXISTS() yagiCallbackCollection.addExistsCallback()
#define ADD_ALL() yagiCallbackCollection.addAllCallback()
#define ADD_IN() yagiCallbackCollection.addInCallback()

//Sets
#define ADD_TUPLE_SET() yagiCallbackCollection.addTupleSetCallback()
#define ADD_SETEXPR() yagiCallbackCollection.addSetExprCallback()

//Tuples
#define ADD_TUPLE() yagiCallbackCollection.addTupleCallback()
#define CONSUME_TUPLE_VAL() yagiCallbackCollection.consumeTupleValCallback()
#define CONSUME_TUPLE() yagiCallbackCollection.consumeTupleCallback()

//Variables, Types, ID
#define ADD_VAR(x) yagiCallbackCollection.addVarCallback(x)
#define CONSUME_VAR() yagiCallbackCollection.consumeVariableCallback()
#define ADD_STRING(x) yagiCallbackCollection.addStringCallback(x)
#define ADD_ID(x) yagiCallbackCollection.addIDCallback(x)

//Values, ValExpr
#define ADD_EXPR_OP(x) yagiCallbackCollection.addExprOperatorCallback(x)
#define ADD_VALEXPR() yagiCallbackCollection.addValueExpressionCallback()
#define CONSUME_VALUE() yagiCallbackCollection.consumeValueCallback()

#ifdef __cplusplus
}
#endif

#endif /* CTOCPPBRIDGE_H_ */

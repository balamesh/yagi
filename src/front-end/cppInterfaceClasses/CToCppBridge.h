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
      void (*addDomainElementCallback)(pANTLR3_STRING domainElement);
      void (*addDomainIntegerCallback)();
      void (*addDomainStringCallback)();
      void (*addDomainStringElementsCallback)();
      void (*consumeDomainCallback)();

      void (*addProgramCallback)();
      void (*addFluentDeclCallback)(pANTLR3_STRING fluentName);
      void (*addFactDeclCallback)(pANTLR3_STRING factName);

      void (*addActionDeclCallback)(pANTLR3_STRING actionName);

      void (*addVarCallback)(pANTLR3_STRING varName);
      void (*addVarListCallback)();
      void (*addIntCallback)(pANTLR3_STRING intVal);
      void (*addStringCallback)(pANTLR3_STRING stringVal);

      void (*addActiveSensingCallback)();
      void (*addEffectCallback)();

      //Expression
      void (*addValueExpressionCallback)();
      void (*addExprOperatorCallback)(char* op);

      //Assignment
      void (*addVarAssignCallback)();
      void (*addPatternMatchCallback)();
      void (*addFluentAssignCallback)(pANTLR3_STRING fluentName);
      void (*addAssignOpCallback)(char* op);

      //Tuples
      void (*addTupleCallback)();
      void (*consumeTupleValCallback)();
      void (*consumeTupleCallback)();

      //Sets
      void (*addTupleSetCallback)();
      void (*addSetExprCallback)();

      //Formulas
      void (*addConnectiveCallback)(char* conn);
      void (*addConstantCallback)(char* constant);
      void (*addAtomCallback)();
      void (*addNegationCallback)();
      void (*addConnectedFormulaCallback)();
      void (*addExistsCallback)();
      void (*addAllCallback)();
      void (*addInCallback)();
  };

  extern struct YAGICallbackCollection yagiCallbackCollection;

//Program Structure
#define ADD_PROGRAM() yagiCallbackCollection.addProgramCallback()

//Declarations
#define ADD_FLUENT_DECL(x) yagiCallbackCollection.addFluentDeclCallback(x)
#define ADD_FACT_DECL(x) yagiCallbackCollection.addFactDeclCallback(x)
#define ADD_ACTION_DECL(x) yagiCallbackCollection.addActionDeclCallback(x)

//Domains
#define ADD_DOMAIN_ELEMENT(x) yagiCallbackCollection.addDomainElementCallback(x)
#define ADD_DOMAIN_INTEGER() yagiCallbackCollection.addDomainIntegerCallback()
#define ADD_DOMAIN_STRING() yagiCallbackCollection.addDomainStringCallback()
#define ADD_DOMAIN_STRING_ELEMENTS() yagiCallbackCollection.addDomainStringElementsCallback()
#define CONSUME_DOMAIN() yagiCallbackCollection.consumeDomainCallback()


//Variables
#define ADD_VAR(x) yagiCallbackCollection.addVarCallback(x)
#define ADD_VAR_LIST() yagiCallbackCollection.addVarListCallback()
#define ADD_INT(x) yagiCallbackCollection.addIntCallback(x)
#define ADD_STRING(x) yagiCallbackCollection.addStringCallback(x)

//Expression
#define ADD_EXPR_OP(x) yagiCallbackCollection.addExprOperatorCallback(x)
#define ADD_VALEXPR() yagiCallbackCollection.addValueExpressionCallback()

//Assignment
#define ADD_VAR_ASSIGN() yagiCallbackCollection.addVarAssignCallback()
#define ADD_PATTERN_MATCH() yagiCallbackCollection.addPatternMatchCallback()
#define ADD_FLUENT_ASSIGN(x) yagiCallbackCollection.addFluentAssignCallback(x)
#define ADD_ASSIGN_OP(x) yagiCallbackCollection.addAssignOpCallback(x)

//Tuples
#define ADD_TUPLE() yagiCallbackCollection.addTupleCallback()
#define CONSUME_TUPLE_VAL() yagiCallbackCollection.consumeTupleValCallback()
#define CONSUME_TUPLE() yagiCallbackCollection.consumeTupleCallback()

//Sets
#define ADD_TUPLE_SET() yagiCallbackCollection.addTupleSetCallback()
#define ADD_SETEXPR() yagiCallbackCollection.addSetExprCallback()

//Action Decl Stuff
#define ADD_ACTIVE_SENSING() yagiCallbackCollection.addActiveSensingCallback()
#define ADD_EFFECT() yagiCallbackCollection.addEffectCallback()

//Formulas
#define ADD_CONNECTIVE(x) yagiCallbackCollection.addConnectiveCallback(x)
#define ADD_CONSTANT(x) yagiCallbackCollection.addConstantCallback(x)
#define ADD_ATOM() yagiCallbackCollection.addAtomCallback()
#define ADD_NEGATION() yagiCallbackCollection.addNegationCallback()
#define ADD_CONNECTED_FORMULA() yagiCallbackCollection.addConnectedFormulaCallback()
#define ADD_EXISTS() yagiCallbackCollection.addExistsCallback()
#define ADD_ALL() yagiCallbackCollection.addAllCallback()
#define ADD_IN() yagiCallbackCollection.addInCallback()

#ifdef __cplusplus
}
#endif

#endif /* CTOCPPBRIDGE_H_ */

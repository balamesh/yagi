/*
 * CCallbackConsumer.h
 *
 *  Created on: Apr 24, 2014
 *      Author: cmaier
 */

#ifndef CCALLBACKCONSUMER_H_
#define CCALLBACKCONSUMER_H_

#include <string>
#include <antlr3.h>
#include "ASTBuilder.h"
#include "../cppInterfaceClasses/CToCppBridge.h"

extern "C"
{
  YAGICallbackCollection yagiCallbackCollection;
}

namespace YAGICallbackConnector
{

  void addDomainElement(pANTLR3_STRING domainElement)
  {
    ASTBuilder::getInstance().addDomainElement((char*) domainElement->chars);
  }

  void addDomainString()
  {
    ASTBuilder::getInstance().addDomainStringNode();
  }

  void addDomainInteger()
  {
    ASTBuilder::getInstance().addDomainIntegerNode();
  }

  void addDomainStringElements()
  {
    ASTBuilder::getInstance().addDomainStringElementsNode();
  }

  void consumeDomain()
  {
    ASTBuilder::getInstance().consumeDomain();
  }

  void addFluent(pANTLR3_STRING fluentName)
  {
    ASTBuilder::getInstance().addFluentDeclNode((char*) fluentName->chars);
  }

  void addFact(pANTLR3_STRING factName)
  {
    ASTBuilder::getInstance().addFactDeclNode((char*) factName->chars);
  }

  void addVar(pANTLR3_STRING varName)
  {
    ASTBuilder::getInstance().addVarNode((char*) varName->chars);
  }

  void consumeVariable()
  {
    ASTBuilder::getInstance().consumeVarNode();
  }

  void addValueExpression()
  {
    ASTBuilder::getInstance().addValueExpressionNode();
  }

  void addExprOperator(char* op)
  {
    ASTBuilder::getInstance().addExprOperator(op);
  }

  void addVarAssignCallback()
  {
    ASTBuilder::getInstance().addVarAssign();
  }

  void addInt(pANTLR3_STRING intVal)
  {
    ASTBuilder::getInstance().addIntNode((char*) intVal->chars);
  }

  void addString(pANTLR3_STRING stringVal)
  {
    ASTBuilder::getInstance().addStringNode((char*) stringVal->chars);
  }

  void addVarAssign()
  {
    ASTBuilder::getInstance().addVarAssign();
  }

  void addAction(pANTLR3_STRING actionName)
  {
    ASTBuilder::getInstance().addActionDeclNode((char*) actionName->chars);
  }

  void addID(pANTLR3_STRING id)
    {
      ASTBuilder::getInstance().addID((char*) id->chars);
    }

  void addEffect()
  {
    ASTBuilder::getInstance().addEffect();
  }

  void addVarList()
  {
    ASTBuilder::getInstance().addVarListNode();
  }

  void addProgram()
  {
    ASTBuilder::getInstance().addProgram();
  }

  void addPatternMatch()
  {
    ASTBuilder::getInstance().addPatternMatch();
  }

  void addTuple()
  {
    ASTBuilder::getInstance().addTuple();
  }
  void consumeTuple()
  {
    ASTBuilder::getInstance().consumeTuple();
  }
  void consumeTupleVal()
  {
    ASTBuilder::getInstance().consumeTupleVal();
  }

  void addSet()
  {
    ASTBuilder::getInstance().addSet();
  }
  void addSetExpr()
  {
    ASTBuilder::getInstance().addSetExpr();
  }

  void addAssignOp(char* op)
  {
    ASTBuilder::getInstance().addAssignmentOp(op);
  }

  void addFluentAssign(pANTLR3_STRING fluentName)
  {
    ASTBuilder::getInstance().addFluentAssign((char*) fluentName->chars);
  }

  void consumeAssignment()
  {
    ASTBuilder::getInstance().consumeAssignment();
  }

  void addAtomConnective(char* connective)
  {
    ASTBuilder::getInstance().addAtomConnective(connective);
  }

  void addFormulaConnective(char* connective)
  {
    ASTBuilder::getInstance().addFormulaConnective(connective);
  }

  void addConstant(char* constant)
  {
    ASTBuilder::getInstance().addConstant(constant);
  }
  void addAtom()
  {
    ASTBuilder::getInstance().addAtom();
  }
  void addNegation()
  {
    ASTBuilder::getInstance().addNegation();
  }
  void addConnectedFormula()
  {
    ASTBuilder::getInstance().addConnectedFormula();
  }
  void addExists()
  {
    ASTBuilder::getInstance().addExists();
  }
  void addAll()
  {
    ASTBuilder::getInstance().addAll();
  }
  void addIn()
  {
    ASTBuilder::getInstance().addIn();
  }

  void connectCallbacks()
  {
    yagiCallbackCollection.addFluentDeclCallback = addFluent;
    yagiCallbackCollection.addDomainStringCallback = addDomainString;
    yagiCallbackCollection.addDomainIntegerCallback = addDomainInteger;
    yagiCallbackCollection.addDomainElementCallback = addDomainElement;
    yagiCallbackCollection.addDomainStringElementsCallback =
        addDomainStringElements;
    yagiCallbackCollection.consumeDomainCallback = consumeDomain;

    yagiCallbackCollection.addProgramCallback = addProgram;
    yagiCallbackCollection.addFactDeclCallback = addFact;

    //Action Decl
    yagiCallbackCollection.addActionDeclCallback = addAction;
    yagiCallbackCollection.addEffectCallback = addEffect;

    //Variables
    yagiCallbackCollection.addVarCallback = addVar;
    yagiCallbackCollection.addVarListCallback = addVarList;
    yagiCallbackCollection.addIntCallback = addInt;
    yagiCallbackCollection.addStringCallback = addString;
    yagiCallbackCollection.consumeVariableCallback = consumeVariable;
    yagiCallbackCollection.addIDCallback = addID;

    //Expressions
    yagiCallbackCollection.addValueExpressionCallback = addValueExpression;
    yagiCallbackCollection.addExprOperatorCallback = addExprOperator;

    //Assignment
    yagiCallbackCollection.addVarAssignCallback = addVarAssign;
    yagiCallbackCollection.addPatternMatchCallback = addPatternMatch;
    yagiCallbackCollection.addFluentAssignCallback = addFluentAssign;
    yagiCallbackCollection.addAssignOpCallback = addAssignOp;
    yagiCallbackCollection.consumeAssignmentCallback = consumeAssignment;

    //Tuples
    yagiCallbackCollection.addTupleCallback = addTuple;
    yagiCallbackCollection.consumeTupleCallback = consumeTuple;
    yagiCallbackCollection.consumeTupleValCallback = consumeTupleVal;

    //Sets
    yagiCallbackCollection.addTupleSetCallback = addSet;
    yagiCallbackCollection.addSetExprCallback = addSetExpr;

    //Formulas
    yagiCallbackCollection.addFormulaConnectiveCallback = addFormulaConnective;
    yagiCallbackCollection.addAtomConnectiveCallback = addAtomConnective;
    yagiCallbackCollection.addConstantCallback = addConstant;
    yagiCallbackCollection.addAtomCallback = addAtom;
    yagiCallbackCollection.addNegationCallback = addNegation;
    yagiCallbackCollection.addConnectedFormulaCallback = addConnectedFormula;
    yagiCallbackCollection.addExistsCallback = addExists;
    yagiCallbackCollection.addAllCallback = addAll;
    yagiCallbackCollection.addInCallback = addIn;

  }

}

#endif /* CCALLBACKCONSUMER_H_ */

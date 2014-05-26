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

  void addVarList()
  {
    ASTBuilder::getInstance().addVarListNode();
  }

  void addProgram()
  {
    ASTBuilder::getInstance().addProgram();
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

    yagiCallbackCollection.addActionDeclCallback = addAction;

    //Variables
    yagiCallbackCollection.addVarCallback = addVar;
    yagiCallbackCollection.addVarListCallback = addVarList;
    yagiCallbackCollection.addIntCallback = addInt;
    yagiCallbackCollection.addStringCallback = addString;

    //Expressions
    yagiCallbackCollection.addValueExpressionCallback = addValueExpression;
    yagiCallbackCollection.addExprOperatorCallback = addExprOperator;

    //Assignment
    yagiCallbackCollection.addVarAssignCallback = addVarAssign;
  }

}

#endif /* CCALLBACKCONSUMER_H_ */

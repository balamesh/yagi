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

  void addExoEvent(pANTLR3_STRING exoEventName)
  {
    ASTBuilder::getInstance().addExoEventDeclNode((char*) exoEventName->chars);
  }

  void addSensingDecl(pANTLR3_STRING sensingName)
  {
    ASTBuilder::getInstance().addSensingDeclNode((char*) sensingName->chars);
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

  void addString(pANTLR3_STRING stringVal)
  {
    ASTBuilder::getInstance().addStringNode((char*) stringVal->chars);
  }

  void addVarAssign()
  {
    ASTBuilder::getInstance().addVarAssign();
  }

  void addForLoopAssign()
  {
    ASTBuilder::getInstance().addForLoopAssign();
  }
  void addConditionalAssign()
  {
    ASTBuilder::getInstance().addConditionalAssign();
  }
  void addConditionalAssignElse()
  {
    ASTBuilder::getInstance().addConditionalAssignElse();
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

  void addIncompleteKnowledge()
  {
    ASTBuilder::getInstance().addIncompleteKnowledge();
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

  void addBlock()
  {
    ASTBuilder::getInstance().addBlock();
  }

  void consumeStatement()
  {
    ASTBuilder::getInstance().consumeStatement();
  }

  void addProcDecl(pANTLR3_STRING procName)
  {
    ASTBuilder::getInstance().addProcDecl((char*) procName->chars);
  }

  void consumeValue()
  {
    ASTBuilder::getInstance().consumeValue();
  }

  void addValueList()
  {
    ASTBuilder::getInstance().addValueList();
  }

  void addProcExec(pANTLR3_STRING procName)
  {
    ASTBuilder::getInstance().addProcExec((char*) procName->chars);
  }

  void addFluentQuery(pANTLR3_STRING fluentName)
  {
    ASTBuilder::getInstance().addFluentQuery((char*) fluentName->chars);
  }

  void addTest()
  {
    ASTBuilder::getInstance().addTest();
  }

  void addChoose()
  {
    ASTBuilder::getInstance().addChoose();
  }

  void consumeBlock()
  {
    ASTBuilder::getInstance().consumeBlock();
  }

  void addPick()
  {
    ASTBuilder::getInstance().addPick();
  }

  void addForLoop()
  {
    ASTBuilder::getInstance().addForLoop();
  }

  void addConditional()
  {
    ASTBuilder::getInstance().addConditional();
  }

  void addWhileLoop()
  {
    ASTBuilder::getInstance().addWhileLoop();
  }

  void addSearch()
  {
    ASTBuilder::getInstance().addSearch();
  }

  void connectCallbacks()
  {
    yagiCallbackCollection.addFluentDeclCallback = addFluent;
    yagiCallbackCollection.addProcDeclCallback = addProcDecl;

    yagiCallbackCollection.addDomainStringCallback = addDomainString;
    yagiCallbackCollection.addDomainElementCallback = addDomainElement;
    yagiCallbackCollection.addDomainStringElementsCallback = addDomainStringElements;
    yagiCallbackCollection.consumeDomainCallback = consumeDomain;

    yagiCallbackCollection.addProgramCallback = addProgram;
    yagiCallbackCollection.addFactDeclCallback = addFact;
    yagiCallbackCollection.addSensingDeclCallback = addSensingDecl;

    //Action Decl
    yagiCallbackCollection.addActionDeclCallback = addAction;
    yagiCallbackCollection.addEffectCallback = addEffect;
    yagiCallbackCollection.addExoEventDeclCallback = addExoEvent;

    //Variables
    yagiCallbackCollection.addVarCallback = addVar;
    yagiCallbackCollection.addVarListCallback = addVarList;
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
    yagiCallbackCollection.addForLoopAssignCallback = addForLoopAssign;
    yagiCallbackCollection.addConditionalAssignCallback = addConditionalAssign;
    yagiCallbackCollection.addConditionalAssignElseCallback = addConditionalAssignElse;
    yagiCallbackCollection.addIncompleteKnowledgeCallback = addIncompleteKnowledge;

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

    //Statements
    yagiCallbackCollection.addBlockCallback = addBlock;
    yagiCallbackCollection.consumeStatementCallback = consumeStatement;
    yagiCallbackCollection.consumeValueCallback = consumeValue;
    yagiCallbackCollection.addValueListCallback = addValueList;
    yagiCallbackCollection.addProcExecCallback = addProcExec;
    yagiCallbackCollection.addFluentQueryCallback = addFluentQuery;
    yagiCallbackCollection.addTestCallback = addTest;
    yagiCallbackCollection.addChooseCallback = addChoose;
    yagiCallbackCollection.consumeBlockCallback = consumeBlock;
    yagiCallbackCollection.addPickCallback = addPick;
    yagiCallbackCollection.addForLoopCallback = addForLoop;
    yagiCallbackCollection.addConditionalCallback = addConditional;
    yagiCallbackCollection.addWhileLoopCallback = addWhileLoop;
    yagiCallbackCollection.addSearchCallback = addSearch;

  }

}

#endif /* CCALLBACKCONSUMER_H_ */

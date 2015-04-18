/**
 * @file   YAGICallbackConnector.h
 * @author Christopher Maier (cmaier@student.tugraz.at)
 * @date   January 2015
 *
 * Responsible for connecting the callbacks fired from the antlr tree walker with the
 * AST builder who builds the C++ AST structure.
 *
 * !!No more antlr-specific datatypes (e.g. pANTLR3_STRING) beyond this point!!
 */

/*
 This file is part of YAGI.

 YAGI is free software; you can redistribute it and/or
 modify it under the terms of the GNU Lesser General Public
 License as published by the Free Software Foundation; either
 version 3.0 of the License, or (at your option) any later version.

 YAGI is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 Lesser General Public License for more details.

 You should have received a copy of the GNU Lesser General Public
 License along with YAGI.
*/


#ifndef CCALLBACKCONSUMER_H_
#define CCALLBACKCONSUMER_H_

#include <string>
#include <antlr3.h>
#include "ASTBuilder.h"
#include "../cppInterfaceClasses/CToCppBridge.h"

extern "C" {
YAGICallbackCollection yagiCallbackCollection;
}

namespace YAGICallbackConnector {

/**
 * Adds a string domain element to the AST
 * @param domainElement The string element
 */
void addDomainElement(pANTLR3_STRING domainElement)
{
  ASTBuilder::getInstance().addDomainElement((char*) domainElement->chars);
}

/**
 * Adds a string-domain to the AST
 */
void addDomainString()
{
  ASTBuilder::getInstance().addDomainStringNode();
}

/**
 * Adds a single string element to a domain
 */
void addDomainStringElements()
{
  ASTBuilder::getInstance().addDomainStringElementsNode();
}

/**
 * Consumes domain
 */
void consumeDomain()
{
  ASTBuilder::getInstance().consumeDomain();
}

/**
 * Adds fluent
 * @param fluentName Name of the fluent
 */
void addFluent(pANTLR3_STRING fluentName)
{
  ASTBuilder::getInstance().addFluentDeclNode((char*) fluentName->chars);
}

/**
 * Adds exogenous event
 * @param exoEventName Name of the exo event
 */
void addExoEvent(pANTLR3_STRING exoEventName)
{
  ASTBuilder::getInstance().addExoEventDeclNode((char*) exoEventName->chars);
}

/**
 * Adds sensing declaration
 * @param sensingName Name of the sensing action
 */
void addSensingDecl(pANTLR3_STRING sensingName)
{
  ASTBuilder::getInstance().addSensingDeclNode((char*) sensingName->chars);
}

/**
 * Adds fact
 * @param factName Name of the fact
 */
void addFact(pANTLR3_STRING factName)
{
  ASTBuilder::getInstance().addFactDeclNode((char*) factName->chars);
}

/**
 * Adds variable
 * @param varName variable name
 */
void addVar(pANTLR3_STRING varName)
{
  ASTBuilder::getInstance().addVarNode((char*) varName->chars);
}

/**
 * Consumes variable
 */
void consumeVariable()
{
  ASTBuilder::getInstance().consumeVarNode();
}

/**
 * Adds value expression
 */
void addValueExpression()
{
  ASTBuilder::getInstance().addValueExpressionNode();
}

/**
 * Adds expression operator
 * @param op Operator string
 */
void addExprOperator(char* op)
{
  ASTBuilder::getInstance().addExprOperator(op);
}

/**
 * Adds variable assignment
 */
void addVarAssignCallback()
{
  ASTBuilder::getInstance().addVarAssign();
}

/**
 * Adds string value
 * @param stringVal The string value
 */
void addString(pANTLR3_STRING stringVal)
{
  ASTBuilder::getInstance().addStringNode((char*) stringVal->chars);
}

/**
 * Adds variable assignment
 */
void addVarAssign()
{
  ASTBuilder::getInstance().addVarAssign();
}

/**
 * Adds action declaration
 * @param actionName Name of the action
 */
void addAction(pANTLR3_STRING actionName)
{
  ASTBuilder::getInstance().addActionDeclNode((char*) actionName->chars);
}

/**
 * Adds identifier
 * @param id The identifier string
 */
void addID(pANTLR3_STRING id)
{
  ASTBuilder::getInstance().addID((char*) id->chars);
}

/**
 * Adds action effect
 */
void addEffect()
{
  ASTBuilder::getInstance().addEffect();
}

/**
 * Adds variable list
 */
void addVarList()
{
  ASTBuilder::getInstance().addVarListNode();
}

/**
 * Adds program
 */
void addProgram()
{
  ASTBuilder::getInstance().addProgram();
}

/**
 * Adds pattern matching
 */
void addPatternMatch()
{
  ASTBuilder::getInstance().addPatternMatch();
}

/**
 * Adds incomplete knowledge
 */
void addIncompleteKnowledge()
{
  ASTBuilder::getInstance().addIncompleteKnowledge();
}

/**
 * Adds tuple
 */
void addTuple()
{
  ASTBuilder::getInstance().addTuple();
}

/**
 * Consumes tuple
 */
void consumeTuple()
{
  ASTBuilder::getInstance().consumeTuple();
}

/**
 * Consumes tuple value
 */
void consumeTupleVal()
{
  ASTBuilder::getInstance().consumeTupleVal();
}

/**
 * Adds set
 */
void addSet()
{
  ASTBuilder::getInstance().addSet();
}

/**
 * Adds set expression
 */
void addSetExpr()
{
  ASTBuilder::getInstance().addSetExpr();
}

/**
 * Adds assignment operator
 * @param op The operator string
 */
void addAssignOp(char* op)
{
  ASTBuilder::getInstance().addAssignmentOp(op);
}

/**
 * Adds assignment to an identifier
 * @param id The name of the ID
 */
void addIDAssign(pANTLR3_STRING id)
{
  ASTBuilder::getInstance().addIDAssign((char*) id->chars);
}

/**
 * Adds atom connective
 * @param connective The atom connective string
 */
void addAtomConnective(char* connective)
{
  ASTBuilder::getInstance().addAtomConnective(connective);
}

/**
 * Adds formula connective
 * @param connective The formula connective
 */
void addFormulaConnective(char* connective)
{
  ASTBuilder::getInstance().addFormulaConnective(connective);
}

/**
 * Adds constant
 * @param constant The string of the constant
 */
void addConstant(char* constant)
{
  ASTBuilder::getInstance().addConstant(constant);
}

/**
 * Adds atom
 */
void addAtom()
{
  ASTBuilder::getInstance().addAtom();
}

/**
 * Adds negation
 */
void addNegation()
{
  ASTBuilder::getInstance().addNegation();
}

/**
 * Adds connected formula
 */
void addConnectedFormula()
{
  ASTBuilder::getInstance().addConnectedFormula();
}

/**
 * Adds exists quantor
 */
void addExists()
{
  ASTBuilder::getInstance().addExists();
}

/**
 * Adds all quantor
 */
void addAll()
{
  ASTBuilder::getInstance().addAll();
}

/**
 * Adds 'in' operator
 */
void addIn()
{
  ASTBuilder::getInstance().addIn();
}

/**
 * Adds block
 */
void addBlock()
{
  ASTBuilder::getInstance().addBlock();
}

/**
 * Consumes statement
 */
void consumeStatement()
{
  ASTBuilder::getInstance().consumeStatement();
}

/**
 * Adds procedure declaration
 * @param procName Name of the procedure
 */
void addProcDecl(pANTLR3_STRING procName)
{
  ASTBuilder::getInstance().addProcDecl((char*) procName->chars);
}

/**
 * Consumes value
 */
void consumeValue()
{
  ASTBuilder::getInstance().consumeValue();
}

/**
 * Adds value list
 */
void addValueList()
{
  ASTBuilder::getInstance().addValueList();
}

/**
 * Adds procedure execution
 * @param procName Name of the procedure to execute
 */
void addProcExec(pANTLR3_STRING procName)
{
  ASTBuilder::getInstance().addProcExec((char*) procName->chars);
}

/**
 * Adds fluent query
 * @param fluentName The name of the fluent to query
 */
void addFluentQuery(pANTLR3_STRING fluentName)
{
  ASTBuilder::getInstance().addFluentQuery((char*) fluentName->chars);
}

/**
 * Adds test statement
 */
void addTest()
{
  ASTBuilder::getInstance().addTest();
}

/**
 * Adds choose statement
 */
void addChoose()
{
  ASTBuilder::getInstance().addChoose();
}

/**
 * Consumes block
 */
void consumeBlock()
{
  ASTBuilder::getInstance().consumeBlock();
}

/**
 * Adds pick statement
 */
void addPick()
{
  ASTBuilder::getInstance().addPick();
}

/**
 * Adds for-loop
 */
void addForLoop()
{
  ASTBuilder::getInstance().addForLoop();
}

/**
 * Adds conditional
 */
void addConditional()
{
  ASTBuilder::getInstance().addConditional();
}

/**
 * Adds while loop
 */
void addWhileLoop()
{
  ASTBuilder::getInstance().addWhileLoop();
}

/**
 * Adds search
 */
void addSearch()
{
  ASTBuilder::getInstance().addSearch();
}

/**
 * Adds include
 */
void addInclude()
{
  ASTBuilder::getInstance().addInclude();
}

/**
 * Connects the callbacks from the C implementation (antlr) to the C++ implementation (ASTBuilder)
 */
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
  yagiCallbackCollection.addIDAssignCallback = addIDAssign;
  yagiCallbackCollection.addAssignOpCallback = addAssignOp;
  //yagiCallbackCollection.consumeAssignmentCallback = consumeAssignment;
  //yagiCallbackCollection.addForLoopAssignCallback = addForLoopAssign;
  //yagiCallbackCollection.addConditionalAssignCallback = addConditionalAssign;
  //yagiCallbackCollection.addConditionalAssignElseCallback = addConditionalAssignElse;
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

  yagiCallbackCollection.addIncludeCallback = addInclude;
}

}

#endif /* CCALLBACKCONSUMER_H_ */

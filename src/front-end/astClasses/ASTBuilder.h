/*
 * ASTBuilder.h
 *
 *  Created on: Apr 24, 2014
 *      Author: cmaier
 */

#ifndef ASTBUILDER_H_
#define ASTBUILDER_H_

#include <string>
#include <memory>
#include <iostream>
#include <stack>
#include <algorithm>

#include "../../common/ASTNodeTypes/ASTNodeBase.h"
#include "../../common/ASTNodeTypes/Identifier/NodeID.h"
#include "../../common/ASTNodeTypes/Domains/NodeDomainStringElements.h"
#include "../../common/ASTNodeTypes/Declarations/FluentDecl/NodeFluentDecl.h"
#include "../../common/ASTNodeTypes/ProgramStructure/NodeProgram.h"
#include "../../common/ASTNodeTypes/Domains/NodeDomainInteger.h"
#include "../../common/ASTNodeTypes/Domains/NodeDomainString.h"
#include "../../common/ASTNodeTypes/Declarations/FactDecl/NodeFactDecl.h"
#include "../../common/ASTNodeTypes/Variables/NodeVariable.h"
#include "../../common/ASTNodeTypes/DataTypes/NodeString.h"
#include "../../common/ASTNodeTypes/Expressions/NodeValueExpressionOperator.h"
#include "../../common/ASTNodeTypes/Expressions/NodeValueExpression.h"
#include "../../common/ASTNodeTypes/Statements/NodeVariableAssignment.h"
#include "../../common/ASTNodeTypes/Expressions/NodeSetExpressionOperator.h"
#include "../../common/ASTNodeTypes/Expressions/NodeSetExpression.h"
#include "../../common/ASTNodeTypes/Tuple/NodeTuple.h"
#include "../../common/ASTNodeTypes/Statements/NodeIDAssignment.h"
#include "../../common/ASTNodeTypes/Formula/NodeAtomConnective.h"
#include "../../common/ASTNodeTypes/Formula/NodeFormulaConnective.h"
#include "../../common/ASTNodeTypes/Formula/NodeFormulaBase.h"
#include "../../common/ASTNodeTypes/Formula/NodeAtom.h"
#include "../../common/ASTNodeTypes/Formula/NodeConstant.h"
#include "../../common/ASTNodeTypes/Formula/NodeNegation.h"
#include "../../common/ASTNodeTypes/Formula/NodeCompoundFormula.h"
#include "../../common/ASTNodeTypes/Formula/NodeQuantifiedFormula.h"
#include "../../common/ASTNodeTypes/Formula/NodeOperatorIn.h"
#include "../../common/ASTNodeTypes/Variables/NodeVarList.h"
#include "../../common/ASTNodeTypes/Declarations/ActionDecl/NodeActionDecl.h"
#include "../../common/ASTNodeTypes/Declarations/SensingDecl/NodeSensingDecl.h"
#include "../../common/ASTNodeTypes/Declarations/ActionDecl/NodeActionEffect.h"
#include "../../common/ASTNodeTypes/Declarations/ActionDecl/NodeActionPrecondition.h"
#include "../../common/ASTNodeTypes/Declarations/ActionDecl/NodeSignal.h"
#include "../../common/ASTNodeTypes/Declarations/ExogenousEventDecl/NodeExogenousEventDecl.h"
#include "../../common/ASTNodeTypes/Statements/NodeBlock.h"
#include "../../common/ASTNodeTypes/Declarations/ProcDecl/NodeProcDecl.h"
#include "../../common/ASTNodeTypes/DataTypes/NodeValueList.h"
#include "../../common/ASTNodeTypes/Statements/NodeProcExecution.h"
#include "../../common/ASTNodeTypes/Statements/NodeFluentQuery.h"
#include "../../common/ASTNodeTypes/Statements/NodeTest.h"
#include "../../common/ASTNodeTypes/Statements/NodeChoose.h"
#include "../../common/ASTNodeTypes/Statements/NodePick.h"
#include "../../common/ASTNodeTypes/Statements/NodeForLoop.h"
#include "../../common/ASTNodeTypes/Statements/NodeConditional.h"
#include "../../common/ASTNodeTypes/Statements/NodeWhileLoop.h"
#include "../../common/ASTNodeTypes/Statements/NodeSearch.h"
#include "../../common/ASTNodeTypes/DataTypes/NodePatternMatching.h"
#include "../../common/ASTNodeTypes/DataTypes/NodeIncompleteKnowledge.h"


class ASTBuilder
{
  private:
    void addQuantifiedFormula(Quantifier quant);

    template<typename T> std::shared_ptr<T> getFrontElement()
    {
      if (ast.size())
      {
        //if ast is empty behaviour is (potentially) undefined!!
        return std::dynamic_pointer_cast<T>(ast.top());
      }
      else
      {
        return nullptr;
      }
    }

  public:
    static ASTBuilder& getInstance()
    {
      static ASTBuilder instance;
      return instance;
    }

    void reset()
    {
      while (!ast.empty())
      {
        ast.pop();
      }
    }

    void addDomainElement(const std::string& domainElement);
    void addDomainStringElementsNode();
    void addDomainStringNode();
    void addDomainIntegerNode();
    void consumeDomain();

    void addFluentDeclNode(const std::string& fluentName);
    void addProgram();
    void addFactDeclNode(const std::string& factName);
    void addExoEventDeclNode(const std::string& passSensName);
    void addVarNode(const std::string& varName);
    void addVarListNode();
    void addID(const std::string& id);
    void addProcDecl(const std::string& procName);
    void addSensingDeclNode(const std::string& sensingName);

    //Action Decl
    void addActionDeclNode(const std::string& actionName);
    void addEffect();

    //Variables
    void addIntNode(const std::string& intVal);
    void addStringNode(const std::string& stringVal);
    void consumeVarNode();

    //Expressions
    void addValueExpressionNode();
    void addExprOperator(const std::string& op);

    //Assignment
    void addVarAssign();
    //void consumeAssignment();
    //void addForLoopAssign();
    //void addConditionalAssign();
    //void addConditionalAssignElse();

    void addPatternMatch();
    void addIncompleteKnowledge();
    void addTuple();
    void consumeTuple();
    void consumeTupleVal();
    void addSet();
    void addSetExpr();
    void addIDAssign(const std::string& identifier);
    void addAssignmentOp(const std::string& op);

    //Formulas
    void addAtomConnective(const std::string& connective);
    void addFormulaConnective(const std::string& connective);
    void addConstant(const std::string& constant);
    void addAtom();
    void addNegation();
    void addConnectedFormula();
    void addExists();
    void addAll();
    void addIn();

    //Statements
    void addBlock();
    void consumeStatement();
    void consumeValue();
    void addValueList();
    void addProcExec(const std::string& procName);
    void addFluentQuery(const std::string& fluentName);
    void addTest();
    void addChoose();
    void consumeBlock();
    void addPick();
    void addForLoop();
    void addConditional();
    void addWhileLoop();
    void addSearch();

    std::shared_ptr<ASTNodeBase<>> getAST()
    {
      return (ast.size() > 0 ? ast.top() : nullptr);
    }

  private:
    ASTBuilder(ASTBuilder const&);
    void operator=(ASTBuilder const&);

    ASTBuilder();
    virtual ~ASTBuilder();

    std::stack<std::shared_ptr<ASTNodeBase<>>> ast;
};

#endif /* ASTBUILDER_H_ */

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
#include <deque>
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
#include "../../common/ASTNodeTypes/DataTypes/NodeInteger.h"
#include "../../common/ASTNodeTypes/DataTypes/NodeString.h"
#include "../../common/ASTNodeTypes/Expressions/NodeValueExpressionOperator.h"
#include "../../common/ASTNodeTypes/Expressions/NodeValueExpression.h"
#include "../../common/ASTNodeTypes/Assignment/NodeVariableAssignment.h"

class ASTBuilder
{
  public:
    static ASTBuilder& getInstance()
    {
      static ASTBuilder instance;
      return instance;
    }

    void addDomainElement(const std::string& domainElement);
    void addDomainStringElementsNode();
    void addDomainStringNode();
    void addDomainIntegerNode();
    void consumeDomain();

    void addFluentDeclNode(const std::string& fluentName);
    void addProgram();
    void addFactDeclNode(const std::string& factName);
    void addVarNode(const std::string& varName);
    void addVarListNode();
    void addActionDeclNode(const std::string& actionName);

    //Variables
    void addIntNode(const std::string& intVal);
    void addStringNode(const std::string& stringVal);

    //Expressions
    void addValueExpressionNode();
    void addExprOperator(const std::string& op);

    //Assignment
    void addVarAssign();

    void addPatternMatch();
    void addTuple();
    void consumeTuple();
    void consumeTupleVal();
    void addSet();
    void addSetExpr();
    void addFluentAssign(const std::string& fluentName);
    void addAssignmentOp(const std::string& op);

    std::shared_ptr<ASTNodeBase> getAST()
    {
      return (ast.size() > 0 ? ast.front() : nullptr);
    }

  private:
    ASTBuilder(ASTBuilder const&);
    void operator=(ASTBuilder const&);

    ASTBuilder();
    virtual ~ASTBuilder();

    std::deque<std::shared_ptr<ASTNodeBase>> ast;
};

#endif /* ASTBUILDER_H_ */

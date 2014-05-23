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
    void addFluentDeclNode(const std::string& fluentName);
    void addProgram();
    void addFactDeclNode(const std::string& factName);
    void addVarNode(const std::string& varName);
    void addVarListNode();
    void addActionDeclNode(const std::string& actionName);

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

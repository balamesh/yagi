/*
 * ToStringVisitor.h
 *
 *  Created on: May 22, 2014
 *      Author: cmaier
 */

#ifndef TOSTRINGVISITOR_H_
#define TOSTRINGVISITOR_H_

#include <iostream>

#include "../../common/ASTNodeVisitorBase.h"
#include "../../common/ASTNodeTypes/Domains/NodeDomainStringElements.h"
#include "../../common/ASTNodeTypes/Declarations/FluentDecl/NodeFluentDecl.h"
#include "../../common/ASTNodeTypes/Identifier/NodeID.h"
#include "../../common/ASTNodeTypes/ProgramStructure/NodeProgram.h"
#include "../../common/ASTNodeTypes/DataTypes/NodeString.h"
#include "../../common/ASTNodeTypes/Domains/NodeDomainInteger.h"
#include "../../common/ASTNodeTypes/Domains/NodeDomainString.h"
#include "../../common/ASTNodeTypes/Declarations/FactDecl/NodeFactDecl.h"
#include "../../common/ASTNodeTypes/Declarations/ActionDecl/NodeActionDecl.h"

class ToStringVisitor: public ASTNodeVisitorBase
{
  private:
    std::string outString{""};

  public:
    ToStringVisitor();
    virtual ~ToStringVisitor();

    virtual void visit(NodeDomainStringElements* domainStringElements) override;
    virtual void visit(NodeFluentDecl* fluentDecl) override;
    virtual void visit(NodeID* id) override;
    virtual void visit(NodeProgram* program) override;
    virtual void visit(NodeString* string) override;
    virtual void visit(NodeDomainInteger* domainInt) override;
    virtual void visit(NodeDomainString* domainString) override;

    virtual void visit(NodeFactDecl* factDecl) override;
    virtual void visit(NodeActionDecl* actionDecl) override;

    virtual void visit(NodeInteger* integer) override;
    virtual void visit(NodeValueExpression* expr) override;
    virtual void visit(NodeValueExpressionOperator* exprOp) override;
    virtual void visit(NodeVariableAssignment* ass) override;

    virtual void visit(NodeVariable* var) override;
};

#endif /* TOSTRINGVISITOR_H_ */

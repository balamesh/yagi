/*
 * ToStringVisitor.h
 *
 *  Created on: May 22, 2014
 *      Author: cmaier
 */

#ifndef TOSTRINGVISITOR_H_
#define TOSTRINGVISITOR_H_

#include "ASTNodeVisitorBase.h"
#include "../astClasses/NodeDomainStringElements.h"
#include "../astClasses/NodeFluentDecl.h"
#include "../astClasses/NodeID.h"
#include "../astClasses/NodeProgram.h"
#include "../astClasses/NodeString.h"

class ToStringVisitor: public ASTNodeVisitorBase
{
  private:
    std::string outString{"C++ AST: "};

  public:
    ToStringVisitor();
    virtual ~ToStringVisitor();

    virtual void visit(NodeDomainStringElements* domainStringElements) override;
    virtual void visit(NodeFluentDecl* fluentDecl) override;
    virtual void visit(NodeID* id) override;
    virtual void visit(NodeProgram* program) override;
    virtual void visit(NodeString* string) override;
};

#endif /* TOSTRINGVISITOR_H_ */

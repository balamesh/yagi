/*
 * TypeCheckVisitor.h
 *
 *  Created on: Jun 7, 2014
 *      Author: cmaier
 */

#ifndef TYPECHECKVISITOR_H_
#define TYPECHECKVISITOR_H_

#include <vector>
#include <algorithm>

#include "../../common/ASTNodeVisitorBase.h"
#include "../../common/ASTNodeTypes/Domains/NodeDomainStringElements.h"
#include "../../common/ASTNodeTypes/Declarations/FluentDecl/NodeFluentDecl.h"
#include "../../common/ASTNodeTypes/Identifier/NodeID.h"
#include "../../common/ASTNodeTypes/ProgramStructure/NodeProgram.h"
#include "../../common/ASTNodeTypes/DataTypes/NodeString.h"
#include "../../common/ASTNodeTypes/Declarations/ActionDecl/NodeActionDecl.h"
#include "../../common/ASTNodeTypes/Domains/NodeDomainString.h"
#include "../../common/ASTNodeTypes/Declarations/FactDecl/NodeFactDecl.h"
#include "../../common/ASTNodeTypes/Statements/NodeIDAssignment.h"

using namespace yagi::container;

class TypeCheckVisitor: public ASTNodeVisitorBase, public Visitor<NodeIDAssignment>, public Visitor<
    NodeActionDecl>
{
  private:
    bool hasTypeError_ = false;
    std::vector<std::string> errorTexts_;

  public:

    TypeCheckVisitor();

    Any visit(NodeIDAssignment& nodeIDAssignment);
    Any visit(NodeActionDecl& nodeActionDecl);

    const std::vector<std::string>& getErrorTexts() const
    {
      return errorTexts_;
    }

    bool hasTypeError() const
    {
      return hasTypeError_;
    }
};

#endif /* TYPECHECKVISITOR_H_ */

/*
 * InterpretationVisitor.h
 *
 *  Created on: Jul 9, 2014
 *      Author: cmaier
 */

#ifndef INTERPRETATIONVISITOR_H_
#define INTERPRETATIONVISITOR_H_

#include "../Database/SQLiteConnector.h"
#include "../../utils/make_unique.h"
#include <memory>

#include "../../common/ASTNodeVisitorBase.h"
#include "../../common/ASTNodeTypes/Domains/NodeDomainStringElements.h"
#include "../../common/ASTNodeTypes/Declarations/FluentDecl/NodeFluentDecl.h"
#include "../../common/ASTNodeTypes/Identifier/NodeID.h"
#include "../../common/ASTNodeTypes/ProgramStructure/NodeProgram.h"
#include "../../common/ASTNodeTypes/DataTypes/NodeString.h"
#include "../../common/ASTNodeTypes/Domains/NodeDomainInteger.h"
#include "../../common/ASTNodeTypes/Domains/NodeDomainString.h"
#include "../../common/ASTNodeTypes/Declarations/FactDecl/NodeFactDecl.h"

using namespace yagi::database;

class InterpretationVisitor: public ASTNodeVisitorBase,
    public Visitor<NodeFluentDecl>,
    public Visitor<NodeProgram>
{
  private:
    std::unique_ptr<SQLiteConnector> db_;

  public:
    InterpretationVisitor();
    virtual ~InterpretationVisitor();

    container::Any visit(NodeProgram& program)
    {
      std::for_each(program.getProgram().begin(), program.getProgram().end(),
          [this](std::shared_ptr<ASTNodeBase<>> stmt)
          {
            stmt->accept(*this);
          });

      return container::Any { };
    }

    container::Any visit(NodeFluentDecl& fluentDecl)
    {


      return container::Any { };
    }
};

#endif /* INTERPRETATIONVISITOR_H_ */

/*
 * ToStringVisitor.h
 *
 *  Created on: May 22, 2014
 *      Author: cmaier
 */

#ifndef TOSTRINGVISITOR_H_
#define TOSTRINGVISITOR_H_

#include <iostream>
#include <memory>
#include <vector>

#include "../../common/ASTNodeVisitorBase.h"
#include "../../common/ASTNodeTypes/Domains/NodeDomainStringElements.h"
#include "../../common/ASTNodeTypes/Declarations/FluentDecl/NodeFluentDecl.h"
#include "../../common/ASTNodeTypes/Identifier/NodeID.h"
#include "../../common/ASTNodeTypes/ProgramStructure/NodeProgram.h"
#include "../../common/ASTNodeTypes/DataTypes/NodeString.h"
#include "../../common/ASTNodeTypes/Domains/NodeDomainInteger.h"
#include "../../common/ASTNodeTypes/Domains/NodeDomainString.h"
#include "../../common/ASTNodeTypes/Declarations/FactDecl/NodeFactDecl.h"
//#include "../../common/ASTNodeTypes/Declarations/ActionDecl/NodeActionDecl.h"
//#include "../../common/ASTNodeTypes/Formula/NodeAtom.h"
//#include "../../common/ASTNodeTypes/Formula/NodeAtomConnective.h"
//#include "../../common/ASTNodeTypes/Formula/NodeCompoundFormula.h"
//#include "../../common/ASTNodeTypes/Formula/NodeFormulaConnective.h"
//#include "../../common/ASTNodeTypes/Formula/NodeNegation.h"
//#include "../../common/ASTNodeTypes/Formula/NodeOperatorIn.h"
//#include "../../common/ASTNodeTypes/Formula/NodeQuantifiedFormula.h"
//#include "../../common/ASTNodeTypes/Formula/NodeConstant.h"
//#include "../../common/ASTNodeTypes/Variables/NodeVarList.h"
//#include "../../common/ASTNodeTypes/Declarations/ActionDecl/NodeSignal.h"
//#include "../../common/ASTNodeTypes/Declarations/ActionDecl/NodeActionEffect.h"
//#include "../../common/ASTNodeTypes/Declarations/ActionDecl/NodeActionPrecondition.h"
//#include "../../common/ASTNodeTypes/Declarations/PassiveSensing/NodePassiveSensingDecl.h"
//#include "../../common/ASTNodeTypes/Declarations/ProcDecl/NodeProcDecl.h"
//#include "../../common/ASTNodeTypes/Statements/NodeActionExecution.h"
//#include "../../common/ASTNodeTypes/Statements/NodeBlock.h"
//#include "../../common/ASTNodeTypes/Statements/NodeChoose.h"
//#include "../../common/ASTNodeTypes/Statements/NodeConditional.h"
//#include "../../common/ASTNodeTypes/Statements/NodeForLoop.h"
//#include "../../common/ASTNodeTypes/Statements/NodePick.h"
//#include "../../common/ASTNodeTypes/Statements/NodeSearch.h"
//#include "../../common/ASTNodeTypes/Statements/NodeTest.h"
//#include "../../common/ASTNodeTypes/Statements/NodeWhileLoop.h"

class ToStringVisitor: public ASTNodeVisitorBase,
    public Visitor<NodeFluentDecl>,
    public Visitor<NodeDomainInteger>,
    public Visitor<NodeDomainString>,
    public Visitor<NodeDomainStringElements>,
    public Visitor<NodeID>,
    public Visitor<NodeProgram>,
    public Visitor<NodeString>,
    public Visitor<NodeFactDecl>
{
  public:
    container::Any visit(NodeProgram& program)
    {
      std::string astString = "";
      std::for_each(program.getProgram().begin(), program.getProgram().end(),
          [this, &astString](std::shared_ptr<ASTNodeBase<>> stmt)
          {
            //safety net to check if only valid YAGI lines and not any
            //garbage resulting from a bug is considered a line...
//            if (!TypeOk(stmt))
//            {
//              throw std::runtime_error("Invalid node type left on program-level of AST!");
//            }
            astString += "^(" + stmt->accept(*this).get<std::string>() + ")";
          });

      return container::Any {astString };
    }

    container::Any visit(NodeFluentDecl& fluentDecl)
    {
      std::string astString = "[FluentDecl] ";
      fluentDecl.getFluentName()->accept(*this);

      std::for_each(std::begin(fluentDecl.getDomains()), std::end(fluentDecl.getDomains()),
          [this, &astString](std::shared_ptr<ASTNodeBase<>> domain)
          {
            astString += domain->accept(*this).get<std::string>();
          });

      return container::Any { astString };
    }

    container::Any visit(NodeFactDecl& factDecl)
    {
      std::string astString = "[FactDecl] ";

      factDecl.getFactName()->accept(*this);

      std::for_each(std::begin(factDecl.getDomains()), std::end(factDecl.getDomains()),
          [this, &astString](std::shared_ptr<ASTNodeBase<>> domain)
          {
            astString += domain->accept(*this).get<std::string>();
          });

      return container::Any { astString };
    }

    container::Any visit(NodeDomainInteger& domainInt)
    {
      return container::Any { std::string { "[Domain INTEGER] " } };
    }

    container::Any visit(NodeDomainString& domainString)
    {
      return container::Any { std::string { "[Domain STRING] " } };
    }

    container::Any visit(NodeID& id)
    {
      return container::Any { "[ID=" + id.getId() + "] " };
    }

    container::Any visit(NodeString& str)
    {
      return container::Any { "[String=" + str.getString() + "] " };
    }

    container::Any visit(NodeDomainStringElements& domainStringElems)
    {
      std::string astString = "^([Domain] ";

      std::for_each(std::begin(domainStringElems.getDomainElements()),
          std::end(domainStringElems.getDomainElements()),
          [this, &astString](std::shared_ptr<ASTNodeBase<>>elem)
          {
            astString += elem->accept(*this).get<std::string>();
          });

      return container::Any { astString };
    }
};

#endif /* TOSTRINGVISITOR_H_ */

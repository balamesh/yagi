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

#include "../common/ASTNodeVisitorBase.h"
#include "../common/ASTNodeTypes/Domains/NodeDomainStringElements.h"
#include "../common/ASTNodeTypes/Declarations/FluentDecl/NodeFluentDecl.h"
#include "../common/ASTNodeTypes/Identifier/NodeID.h"
#include "../common/ASTNodeTypes/ProgramStructure/NodeProgram.h"
#include "../common/ASTNodeTypes/DataTypes/NodeString.h"
#include "../common/ASTNodeTypes/Domains/NodeDomainInteger.h"
#include "../common/ASTNodeTypes/Domains/NodeDomainString.h"
#include "../common/ASTNodeTypes/Declarations/FactDecl/NodeFactDecl.h"
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

class TypeCheckVisitor: public ASTNodeVisitorBase,
    public Visitor<NodeFluentDecl>,
    public Visitor<NodeDomainStringElements>,
    public Visitor<NodeProgram>,
    public Visitor<NodeFactDecl>
{
  private:
    bool hasTypeError_;
    std::string errorText;

  public:

    void visit(NodeProgram& program)
    {
      hasTypeError_ = false;

      std::for_each(program.getProgram().begin(), program.getProgram().end(),
          [this](std::shared_ptr<ASTNodeBase<>> stmt)
          {
            stmt->accept(*this);
          });
    }

    void visit(NodeFluentDecl& fluentDecl)
    {
      std::for_each(std::begin(fluentDecl.getDomains()), std::end(fluentDecl.getDomains()),
          [this,&fluentDecl](std::shared_ptr<NodeDomainBase> domain)
          {
            domain->accept(*this);
          });
    }

    void visit(NodeFactDecl& factDecl)
    {
      std::for_each(std::begin(factDecl.getDomains()), std::end(factDecl.getDomains()),
          [this,&factDecl](std::shared_ptr<NodeDomainBase> domain)
          {
            domain->accept(*this);
          });
    }

    void visit(NodeDomainStringElements& domain) override
    {
      std::vector<std::string> vals;

      //TODO: just a dummy to check if it all works as expected
      if (domain.getDomainElements().size() <= 3)
      {
        hasTypeError_ = true;
        errorText = "A domain with all elements enumerated has to have more than 3 values! ;-)";
      }
    }

    const std::string& getErrorText() const
    {
      return errorText;
    }

    bool hasTypeError() const
    {
      return hasTypeError_;
    }
};

#endif /* TYPECHECKVISITOR_H_ */

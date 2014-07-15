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
#include "../../common/ASTNodeTypes/Statements/NodeFluentQuery.h"
#include "../../common/ASTNodeTypes/Statements/NodeIDAssignment.h"
#include "../../common/ASTNodeTypes/Expressions/NodeSetExpressionOperator.h"
#include "../../common/ASTNodeTypes/Expressions/NodeSetExpression.h"
#include "../../common/ASTNodeTypes/Set/NodeSet.h"
#include "../../common/ASTNodeTypes/Tuple/NodeTuple.h"
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

using namespace yagi::container;

class ToStringVisitor: public ASTNodeVisitorBase,
    public Visitor<NodeFluentDecl>,
    public Visitor<NodeDomainInteger>,
    public Visitor<NodeDomainString>,
    public Visitor<NodeDomainStringElements>,
    public Visitor<NodeID>,
    public Visitor<NodeProgram>,
    public Visitor<NodeString>,
    public Visitor<NodeFactDecl>,
    public Visitor<NodeFluentQuery>,
    public Visitor<NodeIDAssignment>,
    public Visitor<NodeSetExpressionOperator>,
    public Visitor<NodeSetExpression>,
    public Visitor<NodeSet>,
    public Visitor<NodeTuple>
{
  public:
    Any visit(NodeProgram& program)
    {
      std::string astString = "";
      std::for_each(program.getProgram().begin(), program.getProgram().end(),
          [this, &astString](std::shared_ptr<ASTNodeBase<>> stmt)
          {
            auto ret = stmt->accept(*this);
            if (!ret.empty()) astString += "^(" + ret.get<std::string>() + ")";
          });

      return Any { astString };
    }

    Any visit(NodeFluentDecl& fluentDecl)
    {
      std::string astString = "[FluentDecl] ";
      Any fname = fluentDecl.getFluentName()->accept(*this);

      if (!fname.empty())
        astString += fname.get<std::string>();

      std::for_each(std::begin(fluentDecl.getDomains()), std::end(fluentDecl.getDomains()),
          [this, &astString](std::shared_ptr<ASTNodeBase<>> domain)
          {
            auto ret = domain->accept(*this);
            if (!ret.empty()) astString += ret.get<std::string>();
          });

      return Any { astString };
    }

    Any visit(NodeFactDecl& factDecl)
    {
      std::string astString = "[FactDecl] ";

      Any ret = factDecl.getFactName()->accept(*this);
      astString += ret.get<std::string>();

      std::for_each(std::begin(factDecl.getDomains()), std::end(factDecl.getDomains()),
          [this, &astString](std::shared_ptr<ASTNodeBase<>> domain)
          {
            auto ret = domain->accept(*this);
            if (!ret.empty()) astString += ret.get<std::string>();
          });

      return Any { astString };
    }

    Any visit(NodeDomainInteger& domainInt)
    {
      return Any { std::string { "[Domain INTEGER] " } };
    }

    Any visit(NodeDomainString& domainString)
    {
      return Any { std::string { "[Domain STRING] " } };
    }

    Any visit(NodeID& id)
    {
      return Any { "[ID=" + id.getId() + "] " };
    }

    Any visit(NodeString& str)
    {
      return Any { "[String=" + str.getString() + "] " };
    }

    Any visit(NodeDomainStringElements& domainStringElems)
    {
      std::string astString = "^([Domain] ";

      std::for_each(std::begin(domainStringElems.getDomainElements()),
          std::end(domainStringElems.getDomainElements()),
          [this, &astString](std::shared_ptr<ASTNodeBase<>>elem)
          {
            auto ret = elem->accept(*this);
            if (!ret.empty()) astString += ret.get<std::string>();
          });

      return Any { astString };
    }

    Any visit(NodeFluentQuery& fluentQuery)
    {
      std::string astString = "[FluentQuery] ";
      Any fname = fluentQuery.getFluentToQueryName()->accept(*this);
      if (!fname.empty())
        astString += fname.get<std::string>();

      return Any { astString };
    }

    Any visit(NodeIDAssignment& fluentAss)
    {
      std::string astString = "[FluentAssignment] ";
      Any fname = fluentAss.getFluentName()->accept(*this);
      astString += fname.get<std::string>();

      astString += " ^(";
      Any op = fluentAss.getOperator()->accept(*this);
      if (!op.empty())
        astString += op.get<std::string>();

      Any setexpr = fluentAss.getSetExpr()->accept(*this);
      if (!setexpr.empty())
        astString += setexpr.get<std::string>();

      astString += ") ";
      return Any { astString };
    }

    Any visit(NodeSetExpressionOperator& setExprOp)
    {
      std::string astString = "[ExprOp = ";

      astString += setExprOp.toString() + "] ";

      return Any { astString };
    }

    Any visit(NodeSetExpression& setExpr)
    {
      std::string astString = "";
      auto op = setExpr.getOperator();
      auto lhs = setExpr.getLhs();
      auto rhs = setExpr.getRhs();

      if (op != nullptr)
      {
        auto opString = op->accept(*this);
        if (!opString.empty())
          astString += opString.get<std::string>();
      }

      astString += "[Lhs] ";
      if (lhs != nullptr)
      {
        auto lhsString = lhs->accept(*this);
        if (!lhsString.empty())
          astString += lhsString.get<std::string>();
      }
      else astString += "<empty> ";

      astString += "[Rhs] ";
      if (rhs != nullptr)
      {
        auto rhsString = rhs->accept(*this);
        if (!rhsString.empty())
          astString += rhsString.get<std::string>();
      }
      else astString += "<empty> ";

      return Any { astString };
    }

    Any visit(NodeSet& set)
    {
      std::string astString = "^([Set] ";
      auto tuples = set.getTuples();

      std::for_each(std::begin(tuples), std::end(tuples),
          [this, &astString](std::shared_ptr<NodeTuple> tuple)
          {
            Any ret = tuple->accept(*this);
            if (!ret.empty()) astString += ret.get<std::string>();
          });

      astString += ") ";

      return Any { astString };
    }

    Any visit(NodeTuple& tuple)
    {
      std::string astString = "^([Tuple] ";
      auto tupleVals = tuple.getTupleValues();

      std::for_each(std::begin(tupleVals), std::end(tupleVals),
          [this, &astString](std::shared_ptr<ASTNodeBase<>> val)
          {
            Any ret = val->accept(*this);
            if (!ret.empty()) astString += ret.get<std::string>();
          });

      astString += ") ";

      return Any { astString };
    }

};

#endif /* TOSTRINGVISITOR_H_ */

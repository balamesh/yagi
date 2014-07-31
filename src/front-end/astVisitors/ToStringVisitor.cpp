/*
 * ToStringVisitor.cpp
 *
 *  Created on: May 22, 2014
 *      Author: cmaier
 */

#include "ToStringVisitor.h"

Any ToStringVisitor::visit(NodeProgram& program)
{
  std::string astString = "";
  auto prog = program.getProgram();

  std::for_each(std::begin(prog), std::end(prog),
      [this, &astString](std::shared_ptr<ASTNodeBase<>> stmt)
      {
        astString += "^(" + stmt->accept(*this).tryGetCopy<std::string>("<unknown>") + ")";
      });

  return Any { astString };
}

Any ToStringVisitor::visit(NodeFluentDecl& fluentDecl)
{
  std::string astString = "[FluentDecl] ";
  astString += fluentDecl.getFluentName()->accept(*this).tryGetCopy<std::string>("<unknown>");

  std::for_each(std::begin(fluentDecl.getDomains()), std::end(fluentDecl.getDomains()),
      [this, &astString](std::shared_ptr<ASTNodeBase<>> domain)
      {
        astString += domain->accept(*this).tryGetCopy<std::string>("<unknown>");
      });

  return Any { astString };
}

Any ToStringVisitor::visit(NodeFactDecl& factDecl)
{
  std::string astString = "[FactDecl] ";
  astString += factDecl.getFactName()->accept(*this).tryGetCopy<std::string>("<unknown>");

  std::for_each(std::begin(factDecl.getDomains()), std::end(factDecl.getDomains()),
      [this, &astString](std::shared_ptr<ASTNodeBase<>> domain)
      {
        astString += domain->accept(*this).tryGetCopy<std::string>("<unknown>");
      });

  return Any { astString };
}

Any ToStringVisitor::visit(NodeDomainString& domainString)
{
  return Any { std::string { "[Domain STRING] " } };
}

Any ToStringVisitor::visit(NodeDomainStringElements& domainStringElems)
{
  std::string astString = "^([Domain] ";

  std::for_each(std::begin(domainStringElems.getDomainElements()),
      std::end(domainStringElems.getDomainElements()),
      [this, &astString](std::shared_ptr<ASTNodeBase<>>elem)
      {
        astString += elem->accept(*this).tryGetCopy<std::string>("<unknown>");
      });

  return Any { astString };
}

Any ToStringVisitor::visit(NodeID& id)
{
  return Any { "[ID=" + id.getId() + "] " };
}

Any ToStringVisitor::visit(NodeString& str)
{
  return Any { "[String=" + str.getString() + "] " };
}

Any ToStringVisitor::visit(NodeFluentQuery& fluentQuery)
{
  std::string astString = "[FluentQuery] ";
  Any fname = fluentQuery.getFluentToQueryName()->accept(*this);
  if (!fname.empty())
    astString += fname.get<std::string>();

  return Any { astString };
}

Any ToStringVisitor::visit(NodeIDAssignment& fluentAss)
{
  std::string astString = "^([FluentAssignment] ";
  astString += fluentAss.getFluentName()->accept(*this).tryGetCopy<std::string>("<unknown>");

  astString += " ^(";
  astString += fluentAss.getOperator()->accept(*this).tryGetCopy<std::string>("<unknown>");
  astString += fluentAss.getSetExpr()->accept(*this).tryGetCopy<std::string>("<unknown>");

  return Any { astString + ") ) " };
}

Any ToStringVisitor::visit(NodeAssignmentOperator& setExprOp)
{
  std::string astString = "[ExprOp = ";

  astString += setExprOp.toString() + "] ";

  return Any { astString };
}

Any ToStringVisitor::visit(NodeSetExpression& setExpr)
{
  std::string astString = "^(";

  if (auto op = setExpr.getOperator())
  {
    astString += op->accept(*this).tryGetCopy<std::string>("<unknown>");
  }

  astString += "[Lhs] ";
  if (auto lhs = setExpr.getLhs())
  {
    astString += lhs->accept(*this).tryGetCopy<std::string>("<empty>");
  }

  astString += "[Rhs] ";
  if (auto rhs = setExpr.getRhs())
  {
    astString += rhs->accept(*this).tryGetCopy<std::string>("<empty>");
  }

  return Any { astString + ") " };
}

Any ToStringVisitor::visit(NodeSet& set)
{
  std::string astString = "^([Set] ";
  auto tuples = set.getTuples();

  std::for_each(std::begin(tuples), std::end(tuples),
      [this, &astString](std::shared_ptr<NodeTuple> tuple)
      {
        astString += tuple->accept(*this).tryGetCopy<std::string>("<unknown>");
      });

  astString += ") ";

  return Any { astString };
}

Any ToStringVisitor::visit(NodeTuple& tuple)
{
  std::string astString = "^([Tuple] ";
  auto tupleVals = tuple.getTupleValues();

  std::for_each(std::begin(tupleVals), std::end(tupleVals),
      [this, &astString](std::shared_ptr<ASTNodeBase<>> val)
      {
        astString += val->accept(*this).tryGetCopy<std::string>("<unknown>");
      });

  astString += ") ";

  return Any { astString };
}

Any ToStringVisitor::visit(NodeConstant& constant)
{
  return Any { std::string("[CONSTANT=") + (constant.getTruthValue() ? "true" : "false") + "] " };

}

Any ToStringVisitor::visit(NodeActionDecl& actionDecl)
{
  std::string astString = "[ACTION DECL] ";

  astString += actionDecl.getActionName()->accept(*this).tryGetCopy<std::string>("<unknown>");

  if (auto varList = actionDecl.getVarList())
  {
    astString += varList->accept(*this).tryGetCopy<std::string>();
  }

  if (auto settingVarList = actionDecl.getSettingVarList())
  {
    astString += settingVarList->accept(*this).tryGetCopy<std::string>();
  }

  if (auto precond = actionDecl.getActionPrecondition())
  {
    astString += precond->accept(*this).tryGetCopy<std::string>();

  }
  if (auto actionEffect = actionDecl.getActionEffect())
  {
    astString += actionEffect->accept(*this).tryGetCopy<std::string>();
  }

  if (auto signalStmt = actionDecl.getSignal())
  {
    astString += signalStmt->accept(*this).tryGetCopy<std::string>();
  }

  return Any { astString };
}
Any ToStringVisitor::visit(NodeActionPrecondition& precondition)
{
  return Any { std::string("^([AP] ")
      + precondition.getFormula()->accept(*this).tryGetCopy<std::string>("<unknown>") + ")" };
}

Any ToStringVisitor::visit(NodeActionEffect& effect)
{
  return Any { std::string("^([Effect] ")
      + effect.getBlock()->accept(*this).tryGetCopy<std::string>("<unknown>") + ") " };
}

Any ToStringVisitor::visit(NodeIncompleteKnowledge& incompleteKnowledge)
{
  return Any { std::string("[Incomplete Knowledge]") };
}

Any ToStringVisitor::visit(NodePatternMatching& patternMatching)
{
  return Any { std::string("[Pattern matching]") };
}

Any ToStringVisitor::visit(NodeValueList& valueList)
{
  std::string astString = "^([Value List] ";

  auto values = valueList.getValues();

  std::for_each(std::begin(values), std::end(values),
      [this, &astString](std::shared_ptr<ASTNodeBase<>> val)
      {
        astString += val->accept(*this).tryGetCopy<std::string>("<unknown>");
      });

  astString += ") ";

  return Any { astString };
}

Any ToStringVisitor::visit(NodeSignal& signal)
{
  return Any { std::string("^([Signal] ")
      + signal.getSignalData()->accept(*this).tryGetCopy<std::string>("<unknown>") + ") " };
}

Any ToStringVisitor::visit(NodeExogenousEventDecl& exoEvent)
{
  std::string astString = "[Exogenous Event] ";

  astString += exoEvent.getExogenousEventName()->accept(*this).tryGetCopy<std::string>("<unknown>");
  astString += exoEvent.getArgList()->accept(*this).tryGetCopy<std::string>("<unknown>");
  astString += exoEvent.getBlock()->accept(*this).tryGetCopy<std::string>("<unknown>");

  return Any { astString };
}

Any ToStringVisitor::visit(NodeProcDecl& procDecl)
{
  std::string astString = "[Proc Decl] ";

  astString += procDecl.getProcName()->accept(*this).tryGetCopy<std::string>("<unknown>");

  if (auto argList = procDecl.getArgList())
  {
    astString += argList->accept(*this).tryGetCopy<std::string>("<unknown>");
  }

  astString += procDecl.getBlock()->accept(*this).tryGetCopy<std::string>("<unknown>");

  return Any { astString };
}

Any ToStringVisitor::visit(NodeSensingDecl& sensingDecl)
{
  std::string astString = "[Sensing Decl] ";

  astString += sensingDecl.getSensingName()->accept(*this).tryGetCopy<std::string>("<unknown>");

  if (auto varList = sensingDecl.getVarList())
  {
    astString += varList->accept(*this).tryGetCopy<std::string>("<unknown>");
  }

  if (auto settingVarList = sensingDecl.getSettingVarList())
  {
    astString += settingVarList->accept(*this).tryGetCopy<std::string>("<unknown>");
  }

  astString += sensingDecl.getFormula()->accept(*this).tryGetCopy<std::string>("<unknown>");

  return Any { astString };
}

Any ToStringVisitor::visit(NodeExpressionOperator& valExprOp)
{
  std::string astString = "[ExprOp = ";

  astString += valExprOp.toString() + "] ";

  return Any { astString };
}

Any ToStringVisitor::visit(NodeValueExpression& valExpr)
{
  std::string astString = "^(";

  if (auto op = valExpr.getOperator())
  {
    astString += op->accept(*this).tryGetCopy<std::string>("<unknown>");
  }

  astString += "[Lhs] ";
  if (auto lhs = valExpr.getLhs())
  {
    astString += lhs->accept(*this).tryGetCopy<std::string>("<empty>");
  }

  astString += "[Rhs] ";
  if (auto rhs = valExpr.getRhs())
  {
    astString += rhs->accept(*this).tryGetCopy<std::string>("<empty>");
  }

  return Any { astString + ") " };
}

Any ToStringVisitor::visit(NodeAtom& atom)
{
  std::string astString = "^(";

  if (auto conn = atom.getConnective())
  {
    astString += conn->accept(*this).tryGetCopy<std::string>("<unknown>");
  }

  astString += "[Lhs] ";
  if (auto lhs = atom.getLeftOperand())
  {
    astString += lhs->accept(*this).tryGetCopy<std::string>("<empty>");
  }

  astString += "[Rhs] ";
  if (auto rhs = atom.getRightOperand())
  {
    astString += rhs->accept(*this).tryGetCopy<std::string>("<empty>");
  }

  return Any { astString + ") " };
}

Any ToStringVisitor::visit(NodeAtomConnective& connective)
{
  std::string astString = "[Connective = ";

  astString += connective.toString() + "] ";

  return Any { astString };
}

Any ToStringVisitor::visit(NodeCompoundFormula& compoundFormula)
{
  std::string astString = "^(";

  if (auto conn = compoundFormula.getConnective())
  {
    astString += conn->accept(*this).tryGetCopy<std::string>("<unknown>");
  }

  astString += "[Lhs] ";
  if (auto lhs = compoundFormula.getLeftOperand())
  {
    astString += lhs->accept(*this).tryGetCopy<std::string>("<empty>");
  }

  astString += "[Rhs] ";
  if (auto rhs = compoundFormula.getRightOperand())
  {
    astString += rhs->accept(*this).tryGetCopy<std::string>("<empty>");
  }

  return Any { astString + ") " };
}

Any ToStringVisitor::visit(NodeFormulaConnective& connective)
{
  std::string astString = "[Connective = ";

  astString += connective.toString() + "] ";

  return Any { astString };
}

Any ToStringVisitor::visit(NodeNegation& negation)
{
  return Any { std::string("[Negation] ") };

}

Any ToStringVisitor::visit(NodeOperatorIn& inFormula)
{
  std::string astString = "^([In] ";
  astString += inFormula.getTuple()->accept(*this).tryGetCopy<std::string>("<unknown>");
  astString += inFormula.getSetExpr()->accept(*this).tryGetCopy<std::string>("<unknown>");

  return Any { astString + ") " };
}

Any ToStringVisitor::visit(NodeQuantifiedFormula& quantifiedFormula)
{
  std::string astString = "^([QuantifiedFormula quantifier= ";
  astString += quantifiedFormula.getQuantifierText() + "] ";

  astString += quantifiedFormula.getTuple()->accept(*this).tryGetCopy<std::string>("<unknown>");
  astString += quantifiedFormula.getSetExpr()->accept(*this).tryGetCopy<std::string>("<unknown>");

  if (auto suchFormula = quantifiedFormula.getSuchFormula())
  {
    astString += suchFormula->accept(*this).tryGetCopy<std::string>("<empty>");
  }

  return Any { astString + ") " };
}

Any ToStringVisitor::visit(NodeVariable& variable)
{
  return Any { std::string("[Variable '") + variable.getVarName() + "']" };
}

Any ToStringVisitor::visit(NodeVarList& varList)
{
  std::string astString = "^([Variable List] ";

  auto variables = varList.getVariables();

  std::for_each(std::begin(variables), std::end(variables),
      [this, &astString](std::shared_ptr<NodeVariable> var)
      {
        astString += var->accept(*this).tryGetCopy<std::string>("<unknown>");
      });

  return Any { astString + ") " };
}

Any ToStringVisitor::visit(NodeBlock& block)
{
  std::string astString = "^([Block] ";

  std::for_each(std::begin(block.getStatements()), std::end(block.getStatements()),
      [this, &astString](std::shared_ptr<NodeStatementBase> stmt)
      {
        astString += stmt->accept(*this).tryGetCopy<std::string>("<unknown>");
      });

  return Any { astString + ") " };
}

Any ToStringVisitor::visit(NodeChoose& choose)
{
  std::string astString = "^([Choose] ";

  std::for_each(std::begin(choose.getBlocks()), std::end(choose.getBlocks()),
      [this, &astString](std::shared_ptr<NodeBlock> block)
      {
        astString += block->accept(*this).tryGetCopy<std::string>("<unknown>");
      });

  return Any { astString + ") " };
}
Any ToStringVisitor::visit(NodeConditional& conditional)
{
  std::string astString = "^([Conditional] ";

  astString += conditional.getFormula()->accept(*this).tryGetCopy<std::string>("<unknown>");
  astString += conditional.getIfBlock()->accept(*this).tryGetCopy<std::string>("<unknown>");

  if (auto elseBlock = conditional.getElseBlock())
  {
    astString += elseBlock->accept(*this).tryGetCopy<std::string>("<unknown>");
  }

  return Any { astString + ") " };
}

Any ToStringVisitor::visit(NodeForLoop& forLoop)
{
  std::string astString = "^([ForLoop] ";

  astString += forLoop.getTuple()->accept(*this).tryGetCopy<std::string>("<unknown>");
  astString += forLoop.getSetExpr()->accept(*this).tryGetCopy<std::string>("<unknown>");
  astString += forLoop.getBlock()->accept(*this).tryGetCopy<std::string>("<unknown>");

  return Any { astString + ") " };
}

Any ToStringVisitor::visit(NodePick& pick)
{
  std::string astString = "^([Pick] ";

  astString += pick.getTuple()->accept(*this).tryGetCopy<std::string>("<unknown>");
  astString += pick.getSetExpr()->accept(*this).tryGetCopy<std::string>("<unknown>");
  astString += pick.getBlock()->accept(*this).tryGetCopy<std::string>("<unknown>");

  return Any { astString + ") " };
}

Any ToStringVisitor::visit(NodeProcExecution& procExec)
{
  std::string astString = "^([Proc Exec] ";

  astString += procExec.getProcToExecName()->accept(*this).tryGetCopy<std::string>("<unknown>");

  if (auto params = procExec.getParameters())
  {
    astString += params->accept(*this).tryGetCopy<std::string>("<unknown>");
  }

  return Any { astString + ") " };
}

Any ToStringVisitor::visit(NodeSearch& search)
{
  std::string astString = "^([Search] ";

  astString += search.getBlock()->accept(*this).tryGetCopy<std::string>("<unknown>");

  return Any { astString + ") " };
}

Any ToStringVisitor::visit(NodeTest& test)
{
  std::string astString = "^([Test] ";

  astString += test.getFormula()->accept(*this).tryGetCopy<std::string>("<unknown>");

  return Any { astString + ") " };
}

Any ToStringVisitor::visit(NodeVariableAssignment& varAssignment)
{
  std::string astString = "^([Var Assignment] ";

  astString += varAssignment.getVariable()->accept(*this).tryGetCopy<std::string>("<unknown>");
  astString += varAssignment.getValue()->accept(*this).tryGetCopy<std::string>("<unknown>");

  return Any { astString + ") " };
}

Any ToStringVisitor::visit(NodeWhileLoop& whileLoop)
{
  std::string astString = "^([While Loop] ";

  astString += whileLoop.getFormula()->accept(*this).tryGetCopy<std::string>("<unknown>");
  astString += whileLoop.getBlock()->accept(*this).tryGetCopy<std::string>("<unknown>");

  return Any { astString + ") " };
}

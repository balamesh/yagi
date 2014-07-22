/*
 * ExecutionVisitor.cpp
 *
 *  Created on: Jul 19, 2014
 *      Author: cmaier
 */

#include "ExecutionVisitor.h"

namespace yagi {
namespace execution {

ExecutionVisitor::ExecutionVisitor() :
    formulaEvaluator_(nullptr), db_(nullptr)
{

}

ExecutionVisitor::ExecutionVisitor(std::shared_ptr<IFormulaEvaluator> formulaEvaluator,
    std::shared_ptr<DatabaseConnectorBase> db) :
    formulaEvaluator_(formulaEvaluator), db_(db)
{

}

ExecutionVisitor::~ExecutionVisitor()
{

}

Any ExecutionVisitor::visit(NodeActionPrecondition& ap)
{
  return Any { ap.getFormula()->accept(*this) };
}

Any ExecutionVisitor::visit(NodeConstant& formulaConstant)
{
  return Any { formulaEvaluator_->evaluateConstant(&formulaConstant) };
}

Any ExecutionVisitor::visit(NodeActionDecl& actionDecl)
{
  //TODO: if there is a <signal> block execute it first
  bool apHolds = actionDecl.getActionPrecondition()->accept(*this).tryGetCopy<bool>(false);
  if (!apHolds)
  {
    std::cout << "--> AP for action [" + actionDecl.getActionName()->getId() + "] does NOT hold."
        << std::endl;

    return Any { };
  }

  std::cout << "--> AP for action [" + actionDecl.getActionName()->getId() + "] holds." << std::endl;

  auto block = actionDecl.getActionEffect()->getBlock();
  auto statements = block->getStatements();

  std::for_each(std::begin(statements), std::end(statements),
      [this](std::shared_ptr<NodeStatementBase> stmt)
      {
        stmt->accept(*this);
      });

  return Any { };
}

Any ExecutionVisitor::visit(NodeProcExecution& procExec)
{
  if (!formulaEvaluator_)
    throw std::runtime_error("No FormulaEvaluator passed to InterpretationVisitor!");

  if (!db_)
    throw std::runtime_error("No Database passed to InterpretationVisitor!");

  auto actionToExecute = ExecutableElementsContainer::getInstance().getAction(
      procExec.getProcToExecName()->getId());

  if (actionToExecute)
  {
    actionToExecute->accept(*this);
  }

  return Any { };
}

Any ExecutionVisitor::visit(NodeIDAssignment& fluentAss)
{
  //TODO: copy&paste from InterpretationVisitor, refactor it out!!
//  auto db = db_;
//  auto lhs = fluentAss.getFluentName().get()->getId();
//  auto rhs = fluentAss.getSetExpr();
//  auto op = fluentAss.getOperator();
//
//  if (op->getOperator() == AssignmentOperator::Unknown)
//  {
//    throw std::runtime_error("Unknown set expr. assign operator!");
//  }
//
//  if (op->getOperator() == AssignmentOperator::Assign)
//  {
//    db_->executeNonQuery(
//        SQLGenerator::getInstance().getSqlStringClearTable(lhs));
//  }
//
//  std::vector<std::string> sqlStrings;
//
//  //Simplest case: rhs is a <set>
//  if (auto set = std::dynamic_pointer_cast<NodeSet>(rhs->getRhs()))
//  {
//    sqlStrings = SQLGenerator::getInstance().getSqlStringsForFluentSetAssign(lhs, set,
//        op->getOperator());
//
//  } //It can also be another ID, i.e. another fluent
//  else if (auto id = std::dynamic_pointer_cast<NodeID>(rhs->getRhs()))
//  {
//    auto colCount = db_->executeQuery(
//        SQLGenerator::getInstance().getSqlStringNumberOfColumnsInTable(id->getId())).size();
//
//    sqlStrings = SQLGenerator::getInstance().getSqlStringsForFluentFluentAssign(lhs, id->getId(),
//        op->getOperator(), colCount);
//  }
//
//  std::for_each(std::begin(sqlStrings), std::end(sqlStrings), [this](const std::string& stmt)
//  {
//    db_->executeNonQuery(stmt);
//  });

  return Any { };
}

} /* namespace execution */
} /* namespace yagi */

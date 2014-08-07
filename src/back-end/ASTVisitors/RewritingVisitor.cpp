/*
 * RewritingVisitor.cpp
 *
 *  Created on: Jul 24, 2014
 *      Author: cmaier
 */

#include "RewritingVisitor.h"

#include "../SQLGenerator.h"
namespace yagi {
namespace execution {

RewritingVisitor::RewritingVisitor()
{
}

RewritingVisitor::~RewritingVisitor()
{
}

Any RewritingVisitor::visit(NodeActionDecl& actionDecl)
{
  //actionDecl.getActionEffect()->accept(*this);
  return Any { };
}

Any RewritingVisitor::visit(NodeActionEffect& effect)
{
//  std::shared_ptr<NodeBlock> newBlock;
//
//  auto block = effect.getBlock();
//  auto stmts = block->getStatements();
//
//  for (const auto& stmt : stmts)
//  {
//    auto ret = stmt->accept(*this);
//    if (!ret.empty())
//    {
//      auto newStmts = ret.get<std::vector<std::shared_ptr<ASTNodeBase<>>> >();
//
//      for (const auto& newStmt : newStmts)
//      {
//        newBlock->addStatement(std::dynamic_pointer_cast<NodeStatementBase>(newStmt));
//      }
//    }
//    else
//    {
//      newBlock->addStatement(stmt);
//    }
//  }
//
//  effect.setBlock(newBlock);

  return Any { };
}

std::shared_ptr<NodeForLoop> RewritingVisitor::buildAssignmentRewritingLoop(
    std::string lhsFluentName, SitCalcActionType actionType, std::string rhsFluentName)
{
  //Build foreach AST for fluent  assignment
  auto loop = std::make_shared<NodeForLoop>();

  //ActionProcedureInterpretationVisitor apiv(DatabaseManager::getInstance().getMainDB());
  auto newSetExpr = std::make_shared<NodeSetExpression>();
  newSetExpr->setLhs(std::make_shared<NodeID>(rhsFluentName));
  loop->setSetExpr(newSetExpr);

  ///Deduce variable tuple for for-loop from (shadow) fluent
  auto tupleCount = DatabaseManager::getInstance().getMainDB()->executeQuery(
      SQLGenerator::getInstance().getSqlStringNumberOfColumnsInTable(rhsFluentName)).size();

  auto tuple = std::make_shared<NodeTuple>();
  auto sitcalcActionExec = std::make_shared<NodeSitCalcActionExecution>();
  auto functionArgList = std::make_shared<NodeValueList>();

  for (int i = 0; i < tupleCount; i++)
  {
    auto var = std::make_shared<NodeVariable>("x" + std::to_string(i));
    tuple->addTupleValue(var);
    functionArgList->addValue(var);
  }
  loop->setTuple(tuple);

  sitcalcActionExec->setActionType(actionType);
  sitcalcActionExec->setParameters(functionArgList);
  sitcalcActionExec->setFluentName(std::make_shared<NodeID>(lhsFluentName));

  auto block = std::make_shared<NodeBlock>();
  block->addStatement(sitcalcActionExec);
  loop->setBlock(block);

  return loop;
}

Any RewritingVisitor::visit(NodeIDAssignment& idAssignment)
{
//  std::vector<std::shared_ptr<ASTNodeBase<>>>newNodes
//  {};
//
//  ActionProcedureInterpretationVisitor apiv(DatabaseManager::getInstance().getMainDB());
//  auto rhsFluentName = apiv.visit(*idAssignment.getSetExpr().get()).get<std::string>();
//  auto assOp = apiv.visit(*idAssignment.getOperator().get()).get<AssignmentOperator>();
//  auto lhsFluentName = apiv.visit(*idAssignment.getFluentName()).get<std::string>();
//
//  //Depending on the assignment operator we need to build different node sequences
//  switch (assOp)
//  {
//    case AssignmentOperator::AddAssign:
//    newNodes.push_back(
//        std::static_pointer_cast<ASTNodeBase<>>(
//            buildAssignmentRewritingLoop(lhsFluentName, SitCalcActionType::AddAssign, rhsFluentName))); break;
//    break;
//
//    case AssignmentOperator::RemoveAssign:
//    newNodes.push_back(
//        std::static_pointer_cast<ASTNodeBase<>>(
//            buildAssignmentRewritingLoop(lhsFluentName, SitCalcActionType::RemoveAssign, rhsFluentName)));
//    break;
//
//    //F = F' is specified as F -= F; followed by F += F'
//    case AssignmentOperator::Assign:
//    newNodes.push_back(
//        std::static_pointer_cast<ASTNodeBase<>>(
//            buildAssignmentRewritingLoop(lhsFluentName, SitCalcActionType::RemoveAssign, lhsFluentName)));
//    newNodes.push_back(
//        std::static_pointer_cast<ASTNodeBase<>>(
//            buildAssignmentRewritingLoop(lhsFluentName, SitCalcActionType::AddAssign, rhsFluentName)));
//    break;
//
//    default:
//    throw std::runtime_error("Unknown assignment operator!");
//  }
//
//  return Any
//  { newNodes};
  return Any {};
}

}
/* namespace execution */
} /* namespace yagi */

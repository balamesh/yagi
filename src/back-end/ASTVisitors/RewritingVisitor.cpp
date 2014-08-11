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

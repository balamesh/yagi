/*
 * RewritingVisitor.cpp
 *
 *  Created on: Jul 24, 2014
 *      Author: cmaier
 */

#include "RewritingVisitor.h"

namespace yagi {
namespace execution {

RewritingVisitor::RewritingVisitor()
{
}

RewritingVisitor::~RewritingVisitor()
{
}

//Any RewritingVisitor::visit(NodeProgram& program)
//{
//  std::unordered_map<int, std::shared_ptr<NodeForLoop>> repl;
//  int idx = 0;
//
//  std::for_each(program.getProgram().begin(), program.getProgram().end(),
//      [this,&idx,&repl](std::shared_ptr<ASTNodeBase<>> stmt)
//      {
//        auto ret = stmt->accept(*this);
//
//        if (ret.hasType<std::shared_ptr<NodeForLoop>>())
//        {
//          repl.insert(std::make_pair(idx,ret.get<std::shared_ptr<NodeForLoop>>()));
//        }
//
//        idx++;
//      });
//
//  std::for_each(std::begin(repl), std::end(repl),
//      [&program](const std::pair<int, std::shared_ptr<NodeForLoop>> pair)
//      {
//        program.replaceStatement(pair.second,pair.first);
//      });
//
//  return Any { };
//}
//
//Any RewritingVisitor::visit(NodeActionDecl& actionDecl)
//{
//  actionDecl.getActionEffect()->accept(*this);
//  return Any { };
//}
//
//Any RewritingVisitor::visit(NodeActionEffect& effect)
//{
//  effect.getBlock()->accept(*this);
//  return Any { };
//}
//
//Any RewritingVisitor::visit(NodeBlock& block)
//{
//  auto statements = block.getStatements();
//
//  std::for_each(std::begin(statements), std::end(statements),
//      [this](std::shared_ptr<NodeStatementBase> stmt)
//      {
//        auto ret = stmt->accept(*this);
//      });
//
//  return Any { };
//}
//
//Any RewritingVisitor::visit(NodeForLoop& forLoopAssign)
//{
//
//  return Any { };
//}

Any RewritingVisitor::visit(NodeIDAssignment& idAssignment)
{
//  //Build foreach AST for fluent  assignment
//  auto loop = std::make_shared<NodeForLoop>();
//
//  //Build the (shadow) fluent for the <setexpr>
//  ActionProcedureInterpretationVisitor apiv(DatabaseManager::getInstance().getMainDB());
//  auto fluentName = apiv.visit(*idAssignment.getSetExpr().get()).get<std::string>();
//  auto newSetExpr = std::make_shared<NodeSetExpression>();
//  newSetExpr->setLhs(std::make_shared<NodeID>(fluentName));
//  loop->setSetExpr(newSetExpr);
//
//  ///Deduce variable tuple for for-loop from (shadow) fluent
//  auto tupleCount = DatabaseManager::getInstance().getMainDB()->executeQuery(
//      SQLGenerator::getInstance().getSqlStringNumberOfColumnsInTable(fluentName)).size();
//
//  auto tuple = std::make_shared<NodeTuple>();
//  auto fcall = std::make_shared<NodeProcExecution>();
//  auto functionArgList = std::make_shared<NodeValueList>();
//
//  for (int i = 0; i < tupleCount; i++)
//  {
//    auto var = std::make_shared<NodeVariable>("x" + std::to_string(i));
//    tuple->addTupleValue(var);
//    functionArgList->addValue(var);
//  }
//  loop->setTuple(tuple);
//
//  //Depending on the assignment operator use different function name
//  //which is definitely not colliding with any user-defined action/proc
//  auto assOp = apiv.visit(*idAssignment.getOperator().get()).get<AssignmentOperator>();
//  std::string actionName { };
//
//  switch (assOp)
//  {
//    case AssignmentOperator::AddAssign:
//      actionName = "+=";
//    break;
//
//    case AssignmentOperator::Assign:
//      actionName = "=";
//    break;
//
//    case AssignmentOperator::RemoveAssign:
//      actionName = "-=";
//    break;
//
//    default:
//      throw std::runtime_error("Unknown assignment operator!");
//  }
//
//  fcall->setProcToExecName(std::make_shared<NodeID>(actionName));
//  fcall->setParameters(functionArgList);
//
//  auto block = std::make_shared<NodeBlock>();
//  block->addStatement(fcall);
//  loop->setBlock(block);
//
//  return Any { std::static_pointer_cast<ASTNodeBase<>>(loop) };
  return Any { };
}

Any RewritingVisitor::visit(NodeTuple& tuple)
{
  ActionProcedureInterpretationVisitor apiv;
  return apiv.visit(tuple);
}

} /* namespace execution */
} /* namespace yagi */

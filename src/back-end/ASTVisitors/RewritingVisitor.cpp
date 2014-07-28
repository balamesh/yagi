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
  //Build foreach AST for id assignment
  auto loop = std::make_shared<NodeForLoop>();
  loop->setSetExpr(idAssignment.getSetExpr());

  auto tuple = std::make_shared<NodeTuple>();
  tuple->addTupleValue(std::make_shared<NodeVariable>("x1"));
  tuple->addTupleValue(std::make_shared<NodeVariable>("x2"));
  loop->setTuple(tuple);

  auto fcall = std::make_shared<NodeProcExecution>();
  fcall->setProcToExecName(std::make_shared<NodeID>("+g"));

  auto valList = std::make_shared<NodeValueList>();
  valList->addValue(std::make_shared<NodeVariable>("x1"));
  valList->addValue(std::make_shared<NodeVariable>("x2"));
  fcall->setParameters(valList);

  auto block = std::make_shared<NodeBlock>();
  block->addStatement(fcall);
  loop->setBlock(block);

  return Any { loop };
}

} /* namespace execution */
} /* namespace yagi */

/*
 * RewritingVisitor.cpp
 *
 *  Created on: Jul 24, 2014
 *      Author: cmaier
 */

#include "RewritingVisitor.h"
#include "../../utils/DateTimeHelper.h"

#include "../../common/ASTNodeTypes/Statements/NodeAssignmentOperator.h"
#include "../../front-end/astVisitors/ToStringVisitor.h"
#include "../SQLGenerator.h"
namespace yagi {
namespace execution {

RewritingVisitor::RewritingVisitor() :
    PATTERN_MATCH_ID("\"")
{
}

RewritingVisitor::~RewritingVisitor()
{
}

Any RewritingVisitor::visit(NodeActionDecl& actionDecl)
{
  if (auto effect = actionDecl.getActionEffect())
  {
    effect->accept(*this);
  }
  return Any { };
}

Any RewritingVisitor::visit(NodeActionEffect& effect)
{
  auto block = effect.getBlock();
  auto stmts = block->getStatements();

  for (int i = 0; i < stmts.size(); i++)
  {
    auto ret = stmts[i]->accept(*this);
    if (!ret.empty())
    {
      auto forLoop = ret.get<std::shared_ptr<NodeForLoop>>();
      if (forLoop != nullptr)
      {
        auto loop = std::dynamic_pointer_cast<NodeStatementBase>(forLoop);
        block->replaceStatement(loop, i);

        ToStringVisitor tsv;
        auto ret = loop->accept(tsv).get<std::string>();
        std::cout << "Replaced pattern match for loop : " << ret << std::endl;
      }
    }
  }

  return Any { };
}

Any RewritingVisitor::visit(NodeIDAssignment& idAssignment)
{
  ActionProcedureInterpretationVisitor apiv;
  std::string fluentName = apiv.visit(*idAssignment.getFluentName().get()).get<std::string>();
  auto assOp = apiv.visit(*idAssignment.getOperator().get()).get<AssignmentOperator>();

  auto tupleSet = idAssignment.getSetExpr()->accept(*this).get<
      std::vector<std::vector<std::string>>>();

  std::shared_ptr<NodeForLoop> forLoop = nullptr;
  for (const auto& tuple : tupleSet)
  {
    if (isPatternMatchingTuple(tuple))
    {
      forLoop = rewritePatternMatching(fluentName, assOp, tuple);
    }
  }

  return Any { forLoop };
}

Any RewritingVisitor::visit(NodeSetExpression& nodeSetExpr)
{
  return nodeSetExpr.getLhs()->accept(*this);
}

std::shared_ptr<NodeForLoop> RewritingVisitor::rewritePatternMatching(const std::string& fluentName,
    AssignmentOperator assOp, const std::vector<std::string>& tuple)
{
  std::vector<std::shared_ptr<NodeForLoop>> loops;
  auto assTuple = std::make_shared<NodeTuple>();

  for (int i = 0; i < tuple.size(); i++)
  {
    if (tuple[i] == PATTERN_MATCH_ID)
    {
      auto loop = std::make_shared<NodeForLoop>();

      auto domainValues = DatabaseManager::getInstance().getMainDB()->executeQuery(
          SQLGenerator::getInstance().getSqlStringGetDomainElements(fluentName, i + 1))[0];

      auto shadowFluentName = "shadow" + std::to_string(getNowTicks());

      //Build shadow fluent
      NodeFluentDecl shadowFluentNode;
      shadowFluentNode.setFluentName(std::make_shared<NodeID>(shadowFluentName));

      auto domainNode = std::make_shared<NodeDomainStringElements>();
      for (const auto& str : domainValues)
      {
        domainNode->addStringToDomain(std::make_shared<NodeString>(str));
      }
      shadowFluentNode.addDomain(domainNode);

      ActionProcedureInterpretationVisitor apiv(DatabaseManager::getInstance().getMainDB());
      shadowFluentNode.accept(apiv);

      //assign
      std::vector<std::vector<std::string>> vec;
      for (const auto& val : domainValues)
      {
        vec.push_back(std::vector<std::string> { val });
      }

      auto sqlStrings = SQLGenerator::getInstance().getSqlStringsForIDAssign(shadowFluentName, vec,
          AssignmentOperator::Assign);

      for (const auto& stmt : sqlStrings)
      {
        DatabaseManager::getInstance().getMainDB()->executeNonQuery(stmt);
      }

      auto newSetExpr = std::make_shared<NodeSetExpression>();
      newSetExpr->setLhs(std::make_shared<NodeID>(shadowFluentName));
      loop->setSetExpr(newSetExpr);

      //Build foreach AST for fluent  assignment
      auto loopTupleNode = std::make_shared<NodeTuple>();

      auto patternMatchVar = std::make_shared<NodeVariable>(
          "$_chi" + std::to_string(i) + "_" + std::to_string(getNowTicks()));

      loopTupleNode->addTupleValue(patternMatchVar);
      assTuple->addTupleValue(patternMatchVar);

      loop->setTuple(loopTupleNode);
      loops.push_back(loop);
    }
    else if (tuple[i][0] == '$')
    {
      assTuple->addTupleValue(std::make_shared<NodeVariable>(tuple[i]));
    }
    else
    {
      assTuple->addTupleValue(std::make_shared<NodeString>(tuple[i]));
    }
  }

  auto innermostLoop = loops[loops.size() - 1];
  auto nodeAssign = std::make_shared<NodeIDAssignment>();

  nodeAssign->setFluentName(std::make_shared<NodeID>(fluentName));
  auto op = std::make_shared<NodeAssignmentOperator>();
  op->fromString("+="); //TODO
  nodeAssign->setOperator(op);
  auto set = std::make_shared<NodeSet>();

//  for (const auto& loop : loops)
//  {
//    for (const auto& val : loop->getTuple()->getTupleValues())
//      assTuple->addTupleValue(val);
//  }
  set->addTuple(assTuple);

  auto setExpr = std::make_shared<NodeSetExpression>();
  setExpr->setLhs(set);
  nodeAssign->setSetExpr(setExpr);
  auto block = std::make_shared<NodeBlock>();
  block->addStatement(nodeAssign);
  innermostLoop->setBlock(block);

  //After all loops have been created "melt" them together and build the assignment statement
  while (loops.size() >= 2)
  {
    auto block = std::make_shared<NodeBlock>();
    block->addStatement(loops[loops.size() - 1]);
    loops[loops.size() - 2]->setBlock(block);
    loops.erase(std::end(loops) - 1);
  }

  return loops[0];
}

Any RewritingVisitor::visit(NodeSet& nodeSet)
{
  auto tuples = nodeSet.getTuples();
  std::vector<std::vector<std::string>> tupleSet;

  for (const auto& nodeTuple : tuples)
  {
    auto tuple = nodeTuple->accept(*this).get<std::vector<std::string>>();
    tupleSet.push_back(tuple);
  }

  return Any { tupleSet };
}

bool RewritingVisitor::isPatternMatchingTuple(const std::vector<std::string>& tupleElements)
{
  for (const auto& tupleVal : tupleElements)
  {
    if (tupleVal == PATTERN_MATCH_ID)
    {
      return true;
    }
  }

  return false;
}

Any RewritingVisitor::visit(NodeTuple& nodeTuple)
{
//Build vector with tuple values
  std::vector<std::string> tupleVals;

  auto values = nodeTuple.getTupleValues();

  for (const auto& value : values)
  {
    auto val = value->accept(*this).get<std::string>();
    tupleVals.push_back(val);
  }

  return Any { tupleVals };
}

Any RewritingVisitor::visit(NodeVariable& variable)
{
  return Any { variable.getVarName() };
}

Any RewritingVisitor::visit(NodePatternMatching& nodePatternMatching)
{
  return Any { PATTERN_MATCH_ID };
}

Any RewritingVisitor::visit(NodeString& nodeString)
{
  return Any { nodeString.getString() };
}

} /* namespace execution */
} /* namespace yagi */

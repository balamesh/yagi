/*
 * TypeCheckVisitor.cpp
 *
 *  Created on: Jun 7, 2014
 *      Author: cmaier
 */

#include "TypeCheckVisitor.h"
#include "../../back-end/Database/DatabaseManager.h"
#include "../../back-end/SQLGenerator.h"
#include "../../back-end/Database/DBHelper.h"
#include "../../back-end/ExecutableElementsContainer.h"

using namespace yagi::database;
using namespace yagi::execution;

TypeCheckVisitor::TypeCheckVisitor()
{

}

Any TypeCheckVisitor::visit(NodeIDAssignment& nodeIDAssignment)
{
  auto fluentName = nodeIDAssignment.getFluentName()->getId();

  //does fact/fluent exist?
  if (!DatabaseManager::getInstance().getMainDB()->executeQuery(
      SQLGenerator::getInstance().getSqlStringExistsTable(fluentName)).size())
  {
    hasTypeError_ = true;
    errorTexts_.push_back("Fluent/Fact '" + fluentName + "' does not exist!");
    return Any { };
  }

  //if it's a fact, allow assignment once and only once
  if (isFactTable(fluentName, *DatabaseManager::getInstance().getMainDB().get()))
  {
    if (DatabaseManager::getInstance().getMainDB()->executeQuery(
        SQLGenerator::getInstance().getSqlStringSelectAll(fluentName)).size())
    {
      hasTypeError_ = true;
      errorTexts_.push_back("Re-assignment of fact '" + fluentName + "' is not permitted!");
      return Any { };
    }
  }

  return Any { };
}

Any TypeCheckVisitor::visit(NodeProcDecl& nodeProcDecl)
{
  auto procName = nodeProcDecl.getProcName()->getId();
  int arity = 0;

  if (auto argList = nodeProcDecl.getArgList())
  {
    arity = argList->getVariables().size();
  }

  if (ExecutableElementsContainer::getInstance().procExists(procName, arity))
  {
    hasWarnings_ = true;
    warningTexts_.push_back(
        "Procedure with name '" + procName + "' and arity " + std::to_string(arity)
            + " already exists and is being replaced!");
  }

  return Any { };

}

Any TypeCheckVisitor::visit(NodeExogenousEventDecl& nodeExoEventDecl)
{
  auto exoName = nodeExoEventDecl.getExogenousEventName()->getId();
  int arity = 0;

  if (auto argList = nodeExoEventDecl.getArgList())
  {
    arity = argList->getVariables().size();
  }

  if (ExecutableElementsContainer::getInstance().exoEventExists(exoName, arity))
  {
    hasWarnings_ = true;
    warningTexts_.push_back(
        "Exogenous event with name '" + exoName + "' and arity " + std::to_string(arity)
            + " already exists and is being replaced!");
  }

  return Any { };

}

Any TypeCheckVisitor::visit(NodeActionDecl& nodeActionDecl)
{

  auto actionName = nodeActionDecl.getActionName()->getId();
  int arity = 0;

  if (auto argList = nodeActionDecl.getVarList())
  {
    arity = argList->getVariables().size();
  }

  if (ExecutableElementsContainer::getInstance().actionExists(actionName, arity))
  {
    hasWarnings_ = true;
    warningTexts_.push_back(
        "Action with name '" + actionName + "' and arity " + std::to_string(arity)
            + " already exists and is being replaced!");
  }

  if (auto effect = nodeActionDecl.getActionEffect())
  {
    for (const auto& stmt : effect->getBlock()->getStatements())
    {
      stmt->accept(*this);
    }
  }

  return Any { };
}

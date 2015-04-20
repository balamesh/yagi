/**
 * @file   TypeCheckVisitor.cpp
 * @author Christopher Maier (cmaier@student.tugraz.at)
 * @date   January 2015
 *
 * Performs typechecking on the AST of the YAGI program.
 * !!Typechecking is still very rudimentary, i.e. very little type checking is performed!!
 */

/*
 This file is part of YAGI.

 YAGI is free software; you can redistribute it and/or
 modify it under the terms of the GNU Lesser General Public
 License as published by the Free Software Foundation; either
 version 3.0 of the License, or (at your option) any later version.

 YAGI is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 Lesser General Public License for more details.

 You should have received a copy of the GNU Lesser General Public
 License along with YAGI.
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

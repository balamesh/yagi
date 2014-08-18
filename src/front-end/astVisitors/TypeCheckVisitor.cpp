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

using namespace yagi::database;

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

Any TypeCheckVisitor::visit(NodeActionDecl& nodeActionDecl)
{
  if (auto effect = nodeActionDecl.getActionEffect())
  {
    for (const auto& stmt : effect->getBlock()->getStatements())
    {
      stmt->accept(*this);
    }
  }

  return Any { };
}

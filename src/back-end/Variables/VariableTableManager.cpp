/*
 * VariableTableManager.cpp
 *
 *  Created on: Jul 21, 2014
 *      Author: cmaier
 */

#include "VariableTableManager.h"

namespace yagi {
namespace execution {

VariableTableManager::VariableTableManager() :
    MAIN_VAR_TABLE_ID("Main")
{
}

VariableTableManager::~VariableTableManager()
{
}

VariableTable& VariableTableManager::getVariableTable(const std::string& identifier)
{
  auto table = variableTables_.find(identifier);
  bool exists = table != std::end(variableTables_);

  if (exists)
    return table->second;

  VariableTable t;
  variableTables_[identifier] = t;

  return variableTables_[identifier];
}

VariableTable& VariableTableManager::getCloneWithNewName(const std::string& tableToClone,
    const std::string& newTableName)
{
  auto table = variableTables_.find(tableToClone);
  bool exists = table != std::end(variableTables_);

  if (!exists)
  {
    throw std::runtime_error("Table to clone '" + tableToClone + "' does not exist!");
  }

  VariableTable newTable = variableTables_[tableToClone].clone();
  variableTables_[newTableName] = newTable;
  return variableTables_[newTableName];
}

VariableTable& VariableTableManager::getMainVariableTable()
{
  return getVariableTable(MAIN_VAR_TABLE_ID);
}

void VariableTableManager::deleteVariableTable(const std::string& varTableName)
{
  variableTables_.erase(varTableName);
}

} /* namespace execution */
} /* namespace yagi */

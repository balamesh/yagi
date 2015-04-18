/**
 * @file   VariableTableManager.cpp
 * @author Christopher Maier (cmaier.business@gmail.com)
 * @date   April 2015
 *
 * Manages different variable table instances, similar to DatabaseManager class
 * XXX Maybe templatize DBManager and VarTableManager to Manager<T>
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


#include "VariableTableManager.h"

#include <mutex>

namespace yagi {
namespace execution {

std::mutex varTableManagerMutex;

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

  VariableTable t(identifier);
  variableTables_[identifier] = t;

  return variableTables_[identifier];
}

VariableTable& VariableTableManager::getCloneWithNewName(const std::string& tableToClone,
    const std::string& newTableName)
{
  {
    std::lock_guard<std::mutex> lk(varTableManagerMutex);

    auto table = variableTables_.find(tableToClone);
    bool exists = table != std::end(variableTables_);

    if (!exists)
    {
      throw std::runtime_error("Table to clone '" + tableToClone + "' does not exist!");
    }

    variableTables_[newTableName] = variableTables_[tableToClone].clone(newTableName);
    return variableTables_[newTableName];
  }
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

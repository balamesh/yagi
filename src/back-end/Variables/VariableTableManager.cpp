/*
 * VariableTableManager.cpp
 *
 *  Created on: Jul 21, 2014
 *      Author: cmaier
 */

#include "VariableTableManager.h"

namespace yagi {
namespace execution {

VariableTableManager::VariableTableManager()
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

} /* namespace execution */
} /* namespace yagi */

/*
 * VariableTable.cpp
 *
 *  Created on: Jul 21, 2014
 *      Author: cmaier
 */

#include "VariableTable.h"

namespace yagi {
namespace execution {

VariableTable::VariableTable()
{
}

VariableTable::~VariableTable()
{
}

bool VariableTable::variableExists(const std::string& varName) const
{
  return variables_.find(varName) != std::end(variables_);
}

void VariableTable::addOrReplaceVariable(const std::string& varName, std::string value)
{
  variables_[varName] = std::make_tuple(value, true);
}

void VariableTable::addOrReplaceVariable(const std::string& varName)
{
  variables_[varName] = std::make_tuple("", false);
}
std::string VariableTable::getVariableValue(const std::string& varName) const
{
  bool isInitialized = false;
  std::string value = "";

  if (!variableExists(varName))
  {
    throw std::runtime_error("Variable '" + varName + "' does not exist!");
  }

  std::tie(value, isInitialized) = variables_.find(varName)->second;

  if (!isInitialized)
  {
    throw std::runtime_error("Variable '" + varName + "' is not initialized!");
  }

  return value;
}

bool VariableTable::isVariableInitialized(const std::string& varName) const
{
  if (!variableExists(varName))
  {
    throw std::runtime_error("Variable '" + varName + "' does not exist!");
  }

  return std::get<1>(variables_.find(varName)->second);
}

void VariableTable::setVariable(const std::string& varName, const std::string& value)
{
  if (!variableExists(varName))
  {
    throw std::runtime_error("Variable '" + varName + "' does not exist!");
  }

  std::get<0>(variables_[varName]) = value;

}

void VariableTable::removeVariableIfExists(const std::string& varName)
{
  if (variableExists(varName))
  {
    variables_.erase(varName);
  }
}

} /* namespace execution */
} /* namespace yagi */

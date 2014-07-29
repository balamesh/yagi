/*
 * VariableTable.cpp
 *
 *  Created on: Jul 21, 2014
 *      Author: cmaier
 */

#include "VariableTable.h"

namespace yagi {
namespace execution {

VariableTable::VariableTable() :
    showDiagnosisOutput(true)
{
}

VariableTable::~VariableTable()
{
}

bool VariableTable::variableExists(const std::string& varName) const
{
  return variables_.find(varName) != std::end(variables_);
}

void VariableTable::addVariable(const std::string& varName, std::string value)
{
  if (showDiagnosisOutput)
    std::cout << "Adding variable '" << varName << "', value=" << value << std::endl;

  variables_[varName].push(std::make_tuple(value, true));
}

void VariableTable::addVariable(const std::string& varName)
{
  if (showDiagnosisOutput)
    std::cout << "Adding variable '" << varName << "', no value" << std::endl;

  variables_[varName].push(std::make_tuple("", false));
}
std::string VariableTable::getVariableValue(const std::string& varName) const
{
  if (showDiagnosisOutput)
    std::cout << "Getting value for variable '" << varName << "'" << std::endl;

  bool isInitialized = false;
  std::string value = "";

  if (!variableExists(varName))
  {
    throw std::runtime_error("Variable '" + varName + "' does not exist!");
  }

  std::tie(value, isInitialized) = variables_.find(varName)->second.top();

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

  return std::get<1>(variables_.find(varName)->second.top());
}

void VariableTable::setVariable(const std::string& varName, const std::string& value)
{
  if (showDiagnosisOutput)
    std::cout << "Setting value for variable '" << varName << "' value=" << value << std::endl;

  if (!variableExists(varName))
  {
    throw std::runtime_error("Variable '" + varName + "' does not exist!");
  }

  std::get<0>(variables_[varName].top()) = value;
  std::get<1>(variables_[varName].top()) = true;
}

void VariableTable::removeVariableIfExists(const std::string& varName)
{
  if (variableExists(varName))
  {
    if (showDiagnosisOutput)
      std::cout << "Removing variable '" << varName << std::endl;

    variables_.erase(varName);
  }
}

void VariableTable::shrinkVaribleStacksToDepth(int depthAfterShrink)
{
  if (showDiagnosisOutput)
    std::cout << "Shrinking variable stacks to size '" << depthAfterShrink << std::endl;

  for (auto& var : variables_)
  {
    while (var.second.size() > depthAfterShrink)
    {
      var.second.pop();
    }
  }
}

void VariableTable::shrinkVaribleStacksOneLevel()
{
  if (showDiagnosisOutput)
    std::cout << "Shrinking stack for variables one level" << std::endl;

  for (auto& var : variables_)
  {
    if (var.second.size() > 0)
    {
      var.second.pop();
    }
  }
}

int VariableTable::getCurrentDepth() const
{
  int maxDepth = 0;
  for (auto& var : variables_)
  {
    auto size = var.second.size();
    if (size > maxDepth)
    {
      maxDepth = size;
    }
  }

  if (showDiagnosisOutput)
    std::cout << "Getting current variable depth: " << maxDepth << std::endl;

  return maxDepth;
}

} /* namespace execution */
} /* namespace yagi */

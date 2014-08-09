/*
 * VariableTable.cpp
 *
 *  Created on: Jul 21, 2014
 *      Author: cmaier
 */

#include "VariableTable.h"

#include "../../utils/CommandLineArgsContainer.h"
namespace yagi {
namespace execution {

std::string VariableTable::BARRIER_SYMBOL = "#";
static int lvl = 0;

VariableTable::VariableTable() :
    showDiagnosisOutput(
        yagi::container::CommandLineArgsContainer::getInstance().getShowDebugMessages())
{
}

VariableTable::~VariableTable()
{
}

bool VariableTable::variableExists(const std::string& varName) const
{
  auto ret = variables_.find(varName);
  return ret != std::end(variables_);
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

std::string VariableTable::getVariableValue(const std::string& varName)
{
  if (showDiagnosisOutput)
    std::cout << "Getting value for variable '" << varName << "'" << std::endl;

  if (!variableExists(varName))
  {
    throw std::runtime_error("Variable '" + varName + "' does not exist!");
  }

  int cnt = 0;
  std::string retVal;

  while (true)
  {
    auto& tuple = variables_[varName].top();
    if (std::get<0>(tuple) == BARRIER_SYMBOL)
    {
      variables_[varName].pop();
      cnt++;
    }
    else
    {
      if (!std::get<1>(tuple))
      {
        throw std::runtime_error("Variable '" + varName + "' is not initialized!");
      }

      retVal = std::get<0>(tuple);
      break;
    }
  }

  while (cnt > 0)
  {
    variables_[varName].push(std::make_pair(BARRIER_SYMBOL, true));
    cnt--;
  }

  return retVal;
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

    if (!variables_[varName].size())
    {
      variables_.erase(varName);
    }
    else
    {
      variables_[varName].pop();
    }
  }
}

void VariableTable::addScope()
{
  if (showDiagnosisOutput)
  {
    lvl++;
    std::cout << "Adding new scope... Level=" << lvl << std::endl;
  }

  for (auto& var : variables_)
  {
    var.second.push(std::make_tuple(BARRIER_SYMBOL, true));
  }

}

void VariableTable::removeScope()
{
  if (showDiagnosisOutput)
  {
    lvl--;
    std::cout << "Removing scope... Level=" << lvl << std::endl;
  }

  std::vector<std::string> removeList { };
  for (auto& var : variables_)
  {
    while (var.second.size() > 0 && std::get<0>(var.second.top()) != BARRIER_SYMBOL)
    {
      var.second.pop();
    }

    //Pop barrier symbol
    if (var.second.size() > 0)
    {
      var.second.pop();
    }

    //Remove variable from map if there are no values on the stack
    if (var.second.size() == 0)
    {
      removeList.push_back(var.first);
    }
  }

  for (const auto& varName : removeList)
  {
    variables_.erase(varName);
  }
}

VariableTable VariableTable::clone()
{
  VariableTable clone;

//  for (const auto& tuple : variables_)
//  {
//    clone.
//  }

  clone.setVariables(this->variables_); //TODO: is this a shallow copy?
  return clone;
}

} /* namespace execution */
} /* namespace yagi */

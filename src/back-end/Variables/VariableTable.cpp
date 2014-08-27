/*
 * VariableTable.cpp
 *
 *  Created on: Jul 21, 2014
 *      Author: cmaier
 */

#include "VariableTable.h"

#include "../../utils/CommandLineArgsContainer.h"

#include <stdexcept>

namespace yagi {
namespace execution {

std::string VariableTable::BARRIER_SYMBOL = "#";

VariableTable::VariableTable(std::string name) :
    showDiagnosisOutput(
        yagi::container::CommandLineArgsContainer::getInstance().getShowDebugMessages()), name_(
        name), prefix_("[" + name_ + "]: ")
{
}

VariableTable::VariableTable() :
    showDiagnosisOutput(
        yagi::container::CommandLineArgsContainer::getInstance().getShowDebugMessages()), name_(
        "<unknown>"), prefix_("[" + name_ + "]: ")
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
    std::cout << prefix_ << "Adding variable '" << varName << "', value=" << value << std::endl;

  variables_[varName].push(std::make_tuple(value, true));
}

void VariableTable::addVariable(const std::string& varName)
{
  if (showDiagnosisOutput)
    std::cout << prefix_ << "Adding variable '" << varName << "', no value" << std::endl;

  variables_[varName].push(std::make_tuple("", false));
}

bool VariableTable::isVariableInCurrentScope(const std::string& varName)
{
  if (showDiagnosisOutput)
    std::cout << prefix_ << "Checking if variable '" << varName << "' is in current scope..." << std::endl;

  if (!variableExists(varName))
  {
    throw std::runtime_error("Variable '" + varName + "' does not exist!");
  }

  bool isInCurrentScope = !(std::get<0>(variables_[varName].top()) == BARRIER_SYMBOL);

  if (showDiagnosisOutput)
    std::cout << prefix_ << "Variable '" << varName << "' is " << (isInCurrentScope ? "" : "NOT ")
        << "in current scope." << std::endl;

  return isInCurrentScope;
}

std::string VariableTable::getVariableValue(const std::string& varName)
{
  if (showDiagnosisOutput)
    std::cout << prefix_ << "Getting value for variable '" << varName << "'" << std::endl;

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
    std::cout << prefix_ << "Setting value for variable '" << varName << "' value=" << value << std::endl;

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
      std::cout << prefix_ << "Removing variable '" << varName << std::endl;

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
    std::cout << prefix_ << "Adding new scope... Level=" << lvl << std::endl;
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
    std::cout << prefix_ << "Removing scope... Level=" << lvl << std::endl;
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

VariableTable VariableTable::clone(const std::string& name)
{
  VariableTable clone(name);

  clone.setVariables(this->variables_); //TODO: is this a shallow copy?
  return clone;
}

} /* namespace execution */
} /* namespace yagi */

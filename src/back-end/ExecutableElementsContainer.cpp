/**
 * @file   ExecutableElementsContainer.cpp
 * @author Christopher Maier (cmaier.business@gmail.com)
 * @date   April 2015
 *
 * Stores everything that is executable in YAGI, i.e actions, procedures and exo. events
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


#include "ExecutableElementsContainer.h"

namespace yagi {
namespace execution {

ExecutableElementsContainer::ExecutableElementsContainer()
{
}

ExecutableElementsContainer::~ExecutableElementsContainer()
{
}

void ExecutableElementsContainer::addOrReplaceAction(const NodeActionDecl& actionDecl)
{
  ExecElementKey k;
  k.name_ = actionDecl.getActionName()->getId();

  if (auto argList = actionDecl.getVarList())
  {
    k.arity_ = argList->getVariables().size();
  }

  actions_[k] = std::make_shared<NodeActionDecl>(actionDecl);

  if (action_names_.find(k.name_) != action_names_.end())
    action_names_[k.name_].insert(k);
  else
  {
    std::unordered_set<ExecElementKey> mapped_k;
    mapped_k.insert(k);
    action_names_[k.name_] = mapped_k;
  }
}

std::shared_ptr<NodeActionDecl> ExecutableElementsContainer::getAction(
    const std::string& actionName, int arity)
{
  ExecElementKey k;
  k.name_ = actionName;
  k.arity_ = arity;

  if (actionExists(actionName, arity))
  {
    return actions_[k];
  }
  return nullptr;
}

void ExecutableElementsContainer::addOrReplaceProcedure(const NodeProcDecl& procDecl)
{
  ExecElementKey k;
  k.name_ = procDecl.getProcName()->getId();

  if (auto argList = procDecl.getArgList())
  {
    k.arity_ = argList->getVariables().size();
  }

  procedures_[k] = std::make_shared<NodeProcDecl>(procDecl);

  if (procedure_names_.find(k.name_) != procedure_names_.end())
    procedure_names_[k.name_].insert(k);
  else
  {
    std::unordered_set<ExecElementKey> mapped_k;
    mapped_k.insert(k);
    procedure_names_[k.name_] = mapped_k;
  }
}

std::shared_ptr<NodeProcDecl> ExecutableElementsContainer::getProcedure(const std::string& procName,
    int arity)
{
  ExecElementKey k;
  k.name_ = procName;
  k.arity_ = arity;

  if (procExists(procName, arity))
  {
    return procedures_[k];
  }

  return nullptr;
}

void ExecutableElementsContainer::addOrReplaceExoEvent(const NodeExogenousEventDecl& exoEventDecl)
{
  ExecElementKey k;
  k.name_ = exoEventDecl.getExogenousEventName()->getId();

  if (auto argList = exoEventDecl.getArgList())
  {
    k.arity_ = argList->getVariables().size();
  }

  exoEvents_[k] = std::make_shared<NodeExogenousEventDecl>(exoEventDecl);

  if (exoEvents_names_.find(k.name_) != exoEvents_names_.end())
    exoEvents_names_[k.name_].insert(k);
  else
  {
    std::unordered_set<ExecElementKey> mapped_k;
    mapped_k.insert(k);
    exoEvents_names_[k.name_] = mapped_k;
  }
}

std::shared_ptr<NodeExogenousEventDecl> ExecutableElementsContainer::getExoEvent(
    const std::string& exoEventName, int arity)
{
  ExecElementKey k;
  k.name_ = exoEventName;
  k.arity_ = arity;

  if (exoEventExists(exoEventName, arity))
  {
    return exoEvents_[k];
  }
  return nullptr;
}

bool ExecutableElementsContainer::exoEventExists(const std::string& exoEventName, int arity)
{
  ExecElementKey k;
  k.name_ = exoEventName;
  k.arity_ = arity;

  auto val = exoEvents_.find(k);
  if (val != std::end(exoEvents_))
  {
    return true;
  }

  return false;
}

bool ExecutableElementsContainer::actionExists(const std::string& actionName, int arity)
{
  ExecElementKey k;
  k.name_ = actionName;
  k.arity_ = arity;

  auto val = actions_.find(k);
  if (val != std::end(actions_))
  {
    return true;
  }

  return false;
}

bool ExecutableElementsContainer::procExists(const std::string& procName, int arity)
{
  ExecElementKey k;
  k.name_ = procName;
  k.arity_ = arity;

  auto val = procedures_.find(k);
  if (val != std::end(procedures_))
  {
    return true;
  }

  return false;
}

bool ExecutableElementsContainer::actionNameExists(const std::string& actionName)
{
  return action_names_.find(actionName) != action_names_.end();
}

std::unordered_set<ExecElementKey> ExecutableElementsContainer::actionDeclerations(
    const std::string& actionName)
{
  if (action_names_.find(actionName) != action_names_.end())
    return action_names_[actionName];

  return std::unordered_set<ExecElementKey>();
}

bool ExecutableElementsContainer::procNameExists(const std::string& actionName)
{
  return procedure_names_.find(actionName) != procedure_names_.end();
}

std::unordered_set<ExecElementKey> ExecutableElementsContainer::procDeclerations(
    const std::string& actionName)
{
  if (procedure_names_.find(actionName) != procedure_names_.end())
    return procedure_names_[actionName];

  return std::unordered_set<ExecElementKey>();
}

bool ExecutableElementsContainer::exoEventNameExists(const std::string& actionName)
{
  return exoEvents_names_.find(actionName) != exoEvents_names_.end();
}

std::unordered_set<ExecElementKey> ExecutableElementsContainer::exoEventDeclerations(
    const std::string& actionName)
{
  if (exoEvents_names_.find(actionName) != exoEvents_names_.end())
    return exoEvents_names_[actionName];

  return std::unordered_set<ExecElementKey>();
}

} /* namespace execution */
} /* namespace yagi */

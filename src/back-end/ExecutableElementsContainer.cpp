/*
 * ExecutableElementsContainer.cpp
 *
 *  Created on: Jul 17, 2014
 *      Author: cmaier
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

} /* namespace execution */
} /* namespace yagi */

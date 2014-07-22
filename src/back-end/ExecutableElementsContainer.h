/*
 * ExecutableElementsContainer.h
 *
 *  Created on: Jul 17, 2014
 *      Author: cmaier
 */

#ifndef EXECUTABLEELEMENTSCONTAINER_H_
#define EXECUTABLEELEMENTSCONTAINER_H_

#include <unordered_map>
#include <map>
#include <string>

#include "../common/ASTNodeTypes/Declarations/ActionDecl/NodeActionDecl.h"
#include "../common/ASTNodeTypes/Declarations/ProcDecl/NodeProcDecl.h"

namespace yagi {
namespace execution {

class ExecutableElementsContainer
{
  private:
    ExecutableElementsContainer(ExecutableElementsContainer const&);
    void operator=(ExecutableElementsContainer const&);
    ExecutableElementsContainer();
    virtual ~ExecutableElementsContainer();

    std::unordered_map<std::string, std::shared_ptr<NodeActionDecl>> actions_;
    std::unordered_map<std::string, std::shared_ptr<NodeProcDecl>> procedures_;

  public:
    static ExecutableElementsContainer& getInstance()
    {
      static ExecutableElementsContainer instance;
      return instance;
    }

    void addOrReplaceAction(const NodeActionDecl& actionDecl)
    {
      actions_[actionDecl.getActionName()->getId()] = std::make_shared<NodeActionDecl>(actionDecl);
    }

    std::shared_ptr<NodeActionDecl> getAction(const std::string& actionName)
    {
      auto val = actions_.find(actionName);
      if (val != std::end(actions_))
      {
        return actions_[actionName];
      }
      return nullptr;
    }

};

} /* namespace execution */
} /* namespace yagi */

#endif /* EXECUTABLEELEMENTSCONTAINER_H_ */

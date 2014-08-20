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
#include "../common/ASTNodeTypes/Declarations/ExogenousEventDecl/NodeExogenousEventDecl.h"

//inspired by http://stackoverflow.com/questions/17016175/c-unordered-map-using-a-custom-class-type-as-the-key
struct ExecElementKey
{
    std::string name_;
    int arity_ = 0;

    bool operator==(const ExecElementKey &other) const
    {
      return (name_ == other.name_ && arity_ == other.arity_);
    }
};

template<>
struct std::hash<ExecElementKey>
{
    std::size_t operator()(const ExecElementKey& k) const
    {
      using std::size_t;
      using std::hash;
      using std::string;

      // Compute individual hash values for first,
      // second and third and combine them using XOR
      // and bit shifting:
      return (hash<string>()(k.name_) ^ (hash<int>()(k.arity_) << 1));
    }
};

namespace yagi {
namespace execution {

class ExecutableElementsContainer
  final
  {
    private:
      ExecutableElementsContainer(ExecutableElementsContainer const&);
      void operator=(ExecutableElementsContainer const&);
      ExecutableElementsContainer();
      ~ExecutableElementsContainer();

      std::unordered_map<ExecElementKey, std::shared_ptr<NodeActionDecl>> actions_;
      std::unordered_map<ExecElementKey, std::shared_ptr<NodeProcDecl>> procedures_;
      std::unordered_map<ExecElementKey, std::shared_ptr<NodeExogenousEventDecl>> exoEvents_;

    public:
      static ExecutableElementsContainer& getInstance()
      {
        static ExecutableElementsContainer instance;
        return instance;
      }

      void addOrReplaceAction(const NodeActionDecl& actionDecl);
      std::shared_ptr<NodeActionDecl> getAction(const std::string& actionName, int arity);
      bool actionExists(const std::string& actionName, int arity);

      void addOrReplaceProcedure(const NodeProcDecl& procDecl);
      std::shared_ptr<NodeProcDecl> getProcedure(const std::string& procName, int arity);
      bool procExists(const std::string& procName, int arity);

      void addOrReplaceExoEvent(const NodeExogenousEventDecl& exoEventDecl);
      std::shared_ptr<NodeExogenousEventDecl> getExoEvent(const std::string& exoEventName,
          int arity);
      bool exoEventExists(const std::string& exoEventName, int arity);
  };

  } /* namespace execution */
  } /* namespace yagi */

#endif /* EXECUTABLEELEMENTSCONTAINER_H_ */

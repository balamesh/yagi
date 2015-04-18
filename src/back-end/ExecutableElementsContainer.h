/**
 * @file   ExecutableElementsContainer.h
 * @author Christopher Maier (cmaier.business@gmail.com)
 * @date   April 2015
 *
 * Stores everything that is executable in YAGI, i.e actions, procedures and exo. events
 */

#ifndef EXECUTABLEELEMENTSCONTAINER_H_
#define EXECUTABLEELEMENTSCONTAINER_H_

#include <unordered_map>
#include <map>
#include <string>
#include <unordered_set>

#include "../common/ASTNodeTypes/Declarations/ActionDecl/NodeActionDecl.h"
#include "../common/ASTNodeTypes/Declarations/ProcDecl/NodeProcDecl.h"
#include "../common/ASTNodeTypes/Declarations/ExogenousEventDecl/NodeExogenousEventDecl.h"

/**
 * Structure used for key in map
 * Inspired by http://stackoverflow.com/questions/17016175/c-unordered-map-using-a-custom-class-type-as-the-key
 */
struct ExecElementKey
{
    std::string name_;
    int arity_ = 0;

    bool operator==(const ExecElementKey &other) const
    {
      return (name_ == other.name_ && arity_ == other.arity_);
    }
};

namespace std {
template<>

/**
 * Hash impl for key in map
 * Inspired by http://stackoverflow.com/questions/17016175/c-unordered-map-using-a-custom-class-type-as-the-key
 */
struct hash<ExecElementKey>
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
}

namespace yagi {
namespace execution {

/**
 * Container class for executable YAGI language constructs
 */
class ExecutableElementsContainer
  final
  {
    private:

      /**
       * Copy ctor
       * @param The container to copy
       */
      ExecutableElementsContainer(ExecutableElementsContainer const&);

      /**
       * Assignment operator
       * @param  The instance to assign
       */
      void operator=(ExecutableElementsContainer const&);

      /**
       * Default ctor
       */
      ExecutableElementsContainer();

      /**
       * Default dtor
       */
      ~ExecutableElementsContainer();

      /**
       * Stores YAGI actions
       */
      std::unordered_map<ExecElementKey, std::shared_ptr<NodeActionDecl>> actions_;

      /**
       * Stores action names
       */
      std::unordered_map<std::string, std::unordered_set<ExecElementKey>> action_names_;

      /**
       * Stores procedures
       */
      std::unordered_map<ExecElementKey, std::shared_ptr<NodeProcDecl>> procedures_;

      /**
       * Stores procedures names
       */
      std::unordered_map<std::string, std::unordered_set<ExecElementKey>> procedure_names_;

      /**
       * Stores exo events
       */
      std::unordered_map<ExecElementKey, std::shared_ptr<NodeExogenousEventDecl>> exoEvents_;

      /**
       * Stores exo event names
       */
      std::unordered_map<std::string, std::unordered_set<ExecElementKey>> exoEvents_names_;

    public:

      /**
       * Singleton impl
       * @return Return instance
       */
      static ExecutableElementsContainer& getInstance()
      {
        static ExecutableElementsContainer instance;
        return instance;
      }

      /**
       * Add or replace a specific action
       * @param actionDecl The action to add
       */
      void addOrReplaceAction(const NodeActionDecl& actionDecl);

      /**
       * Gets a specific action
       * @param actionName The name of the action
       * @param arity The arity of the action
       * @return The action node
       */
      std::shared_ptr<NodeActionDecl> getAction(const std::string& actionName, int arity);

      /**
       * Checks whether or not an action exists
       * @param actionName The name of the action
       * @param arity The arity of the action
       * @return True if action exists, false otherwise
       */
      bool actionExists(const std::string& actionName, int arity);

      /**
       * Checks whether or an action with a specific name already exists
       * @param actionName The name to check
       * @return True if action exists, false otherwise
       */
      bool actionNameExists(const std::string& actionName);

      /**
       * Get all action declarations with a specific name
       * @param actionName The name of the action
       * @return All declared actions
       */
      std::unordered_set<ExecElementKey> actionDeclerations(const std::string& actionName);

      /**
       * Add or replace a specific procedure
       * @param procDecl The procedure to add
       */
      void addOrReplaceProcedure(const NodeProcDecl& procDecl);

      /**
       * Gets a specific procedure
       * @param procName The name of the procedure
       * @param arity The arity of the procedure
       * @return The procedure node
       */
      std::shared_ptr<NodeProcDecl> getProcedure(const std::string& procName, int arity);

      /**
       * Checks whether or not a proc exists
       * @param procName The name of the proc
       * @param arity The arity of the proc
       * @return True if proc exists, false otherwise
       */
      bool procExists(const std::string& procName, int arity);

      /**
       * Checks whether or a proc with a specific name already exists
       * @param actionName The name to check
       * @return True if proc exists, false otherwise
       */
      bool procNameExists(const std::string& actionName);

      /**
       * Get all proc declarations with a specific name
       * @param actionName The name of the proc
       * @return All declared procs
       */
      std::unordered_set<ExecElementKey> procDeclerations(const std::string& actionName);

      /**
       * Add or replace a specific exo event
       * @param exoEventDecl The exo event to add
       */
      void addOrReplaceExoEvent(const NodeExogenousEventDecl& exoEventDecl);

      /**
       * Gets a specific exo event
       * @param exoEventName The name of the exo event
       * @param arity The arity of the exo vent
       * @return The exo event node
       */
      std::shared_ptr<NodeExogenousEventDecl> getExoEvent(const std::string& exoEventName,
          int arity);

      /**
       * Checks whether or not an exo event exists
       * @param exoEventName The name of the exo event
       * @param arity The arity of the exo event
       * @return True if exo event exists, false otherwise
       */
      bool exoEventExists(const std::string& exoEventName, int arity);

      /**
       * Checks whether or an exo event with a specific name already exists
       * @param actionName The name to check
       * @return True if exo event exists, false otherwise
       */
      bool exoEventNameExists(const std::string& actionName);

      /**
       * Get all exo event declarations with a specific name
       * @param actionName The name of the exo event
       * @return All declared exo events
       */
      std::unordered_set<ExecElementKey> exoEventDeclerations(const std::string& actionName);
  };

  } /* namespace execution */
  } /* namespace yagi */

#endif /* EXECUTABLEELEMENTSCONTAINER_H_ */

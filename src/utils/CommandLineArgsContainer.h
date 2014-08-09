/*
 * CommandLineArgsContainer.h
 *
 *  Created on: Aug 9, 2014
 *      Author: cmaier
 */

#ifndef COMMANDLINEARGSCONTAINER_H_
#define COMMANDLINEARGSCONTAINER_H_

namespace yagi {
namespace container {

class CommandLineArgsContainer
  final
  {
    private:
      CommandLineArgsContainer();
      ~CommandLineArgsContainer() {};
      CommandLineArgsContainer(CommandLineArgsContainer const&);
      void operator=(CommandLineArgsContainer const&);

      bool showDebugMessages_;

    public:
      static CommandLineArgsContainer& getInstance()
      {
        static CommandLineArgsContainer instance;
        return instance;
      }

      bool getShowDebugMessages() const
      {
        return showDebugMessages_;
      }

      void setShowDebugMessages(bool showDebugMessages)
      {
        showDebugMessages_ = showDebugMessages;
      }
  };

  }
  }

#endif /* COMMANDLINEARGSCONTAINER_H_ */

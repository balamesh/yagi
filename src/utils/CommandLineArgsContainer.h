/*
 * CommandLineArgsContainer.h
 *
 *  Created on: Aug 9, 2014
 *      Author: cmaier
 */

#ifndef COMMANDLINEARGSCONTAINER_H_
#define COMMANDLINEARGSCONTAINER_H_

#include <string>

namespace yagi {
namespace container {

class CommandLineArgsContainer
  final
  {
    private:
      CommandLineArgsContainer();
      ~CommandLineArgsContainer()
      {
      }
      ;
      CommandLineArgsContainer(CommandLineArgsContainer const&);
      void operator=(CommandLineArgsContainer const&);

      bool showDebugMessages_;
      bool measurePerformance_;
      std::string fileName_;

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

      bool measurePerformance() const
      {
        return measurePerformance_;
      }

      void setMeasurePerformance(bool measurePerformance)
      {
        measurePerformance_ = measurePerformance;
      }

      const std::string& getFileName() const
      {
        return fileName_;
      }

      void setFileName(const std::string& fileName)
      {
        fileName_ = fileName;
      }
  };

  }
  }

#endif /* COMMANDLINEARGSCONTAINER_H_ */

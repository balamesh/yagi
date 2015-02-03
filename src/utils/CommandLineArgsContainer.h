/**
 * @file   CommandLineArgsContainer.h
 * @author Christopher Maier
 * @date   January 2015
 *
 * Container the stores the parameters passed via the commandline
 * to the application.
 */

#ifndef COMMANDLINEARGSCONTAINER_H_
#define COMMANDLINEARGSCONTAINER_H_

#include <string>

namespace yagi {
namespace container {

/**
 * Container the stores the parameters passed via the commandline
 * to the application.
 */
class CommandLineArgsContainer
  final
  {
    private:
      /**
       * Default ctor
       */
      CommandLineArgsContainer();

      /**
       * Default dtor
       */
      ~CommandLineArgsContainer()
      {
      }
      ;
      /**
       * Copy ctor
       */
      CommandLineArgsContainer(CommandLineArgsContainer const&);

      /**
       * Assignment Operator
       */
      void operator=(CommandLineArgsContainer const&);

      /**
       * Show debug messages?
       */
      bool showDebugMessages_;

      /**
       * Measure runtime performance?
       */
      bool measurePerformance_;

      /**
       * Input YAGI program file
       */
      std::string inputFileName_;

      /**
       * Output filename for runtime data
       */
      std::string outputFileName_;

      /**
       * Output filename for runtime data
       */
      std::string backendPlugin_;

    public:
      /**
       * Getter for singleton
       * @return Singleton instance
       */
      static CommandLineArgsContainer& getInstance()
      {
        static CommandLineArgsContainer instance;
        return instance;
      }

      /**
       * Getter for debug messages flag
       * @return True if debug messages should be shown, false otherwise
       */
      bool getShowDebugMessages() const
      {
        return showDebugMessages_;
      }

      /**
       * Setter for debug message flag
       * @param showDebugMessages True if debug messages should be shown, false otherwise
       */
      void setShowDebugMessages(bool showDebugMessages)
      {
        showDebugMessages_ = showDebugMessages;
      }

      /**
       * Should performance be measured?
       * @return True if performance should be measured, false otherwise.
       */
      bool measurePerformance() const
      {
        return measurePerformance_;
      }

      /**
       * Setter for performance measurement flag
       * @param measurePerformance True if performance should be measured, false otherwise
       */
      void setMeasurePerformance(bool measurePerformance)
      {
        measurePerformance_ = measurePerformance;
      }

      /**
       * Getter for input file name
       * @return The name of the YAGI input file to use
       */
      const std::string& getInputFileName() const
      {
        return inputFileName_;
      }

      /**
       * Setter for the input file name
       * @param fileName The name of the YAGI input file to use
       */
      void setInputFileName(const std::string& fileName)
      {
        inputFileName_ = fileName;
      }

      /**
       * Getter for the performance output file name
       * @return The name of the output file.
       */
      const std::string& getOutputFileName() const
      {
        return outputFileName_;
      }

      /**
       * Setter for the output file name
       * @param outputFileName The name of the performance output file.
       */
      void setOutputFileName(const std::string& outputFileName)
      {
        outputFileName_ = outputFileName;
      }

      /**
       * Getter for the backend plugin file name
       * @return The name of the backend plugin file.
       */
      const std::string& getBackendPlugin() const
      {
        return backendPlugin_;
      }

      /**
       * Setter for the backend plugin file name
       * @param outputFileName The name of the backend plugin file.
       */
      void setBackendPlugin(const std::string& backendPlugin)
      {
        backendPlugin_ = backendPlugin;
      }

  };

  }
  }

#endif /* COMMANDLINEARGSCONTAINER_H_ */

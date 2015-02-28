/**
 * @file   CommandLineArgsContainer.cpp
 * @author Christopher Maier
 * @date   January 2015
 *
 * Container the stores the parameters passed via the commandline
 * to the application.
 */

#include "CommandLineArgsContainer.h"

namespace yagi {
namespace container {

CommandLineArgsContainer::CommandLineArgsContainer() :
    showDebugMessages_(false), measurePerformance_(false), inputFileName_(""), outputFileName_(""), backendPlugin_("")
{

}

}
}

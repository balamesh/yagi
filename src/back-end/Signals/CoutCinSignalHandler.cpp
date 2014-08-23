/*
 * PrintOutSignalReceiver.cpp
 *
 *  Created on: Jul 23, 2014
 *      Author: cmaier
 */

#include "CoutCinSignalHandler.h"

#include <mutex>
namespace yagi {
namespace execution {

std::mutex signalMutex;

CoutCinSignalHandler::CoutCinSignalHandler()
{
}

CoutCinSignalHandler::~CoutCinSignalHandler()
{
}

std::unordered_map<std::string, std::string> CoutCinSignalHandler::signal(
    const std::string& content, const std::vector<std::string>& variables)
{
  //no variables passed => no setting actions, just print whatever
  //there is to print
  if (!variables.size())
  {
    {
      std::lock_guard<std::mutex> lk(signalMutex);
      std::cout << ">>>> " << (!isSearch_ ? "[Signal] " : "[Search] [Signal] ") << content
          << std::endl;
    }
    return std::unordered_map<std::string, std::string> { };
  }
  else //print and wait for input
  {
    std::unordered_map<std::string, std::string> retVals { };
    std::cout << ">>>> "
        << (!isSearch_ ? "[Setting Action Signal] " : "[Search] [Setting Action Signal] ")
        << content << std::endl;

    char* buffer = nullptr;

    for (const auto& var : variables)
    {
      buffer = readline((">>>> Enter string-value for variable " + var + ": ").c_str());
      retVals[var] = buffer;
    }

    return retVals;
  }
}

} /* namespace execution */
} /* namespace yagi */

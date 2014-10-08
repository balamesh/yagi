/*
 * PrintOutSignalReceiver.cpp
 *
 *  Created on: Jul 23, 2014
 *      Author: cmaier
 */

#include "AsraelSignalHandler.h"

#include <mutex>
namespace yagi {
namespace execution {

std::mutex signalMutexAsrael;

AsraelSignalHandler::AsraelSignalHandler()
{
    //connectSimulator();
}

AsraelSignalHandler::~AsraelSignalHandler()
{
}

std::vector<std::string> AsraelSignalHandler::chopParameters(std::string params)
{
    std::vector<std::string> plist;

    std::size_t found = params.find_first_of("_");

    while (found!=std::string::npos)
    {
        std::string p = params.substr(0,found);
        std::string p1 = params.substr(found+1);
        plist.push_back(p);
        params = p1;
        found = params.find_first_of("_");
    }
    plist.push_back(params);
    return plist;
}

int AsraelSignalHandler::connectSimulator(std::string level)
{
    AsrealRemoteCommandResponse response = client.loadLevel(level);
    std::cout << "level loaded " << level << std::endl;
    return response.code_;
}

std::unordered_map<std::string, std::string> AsraelSignalHandler::signal(
    const std::string& content, const std::vector<std::string>& variables)
{
  //no variables passed => no setting actions, just print whatever
  //there is to print
  if (!variables.size())
  {
    {
      std::lock_guard<std::mutex> lk(signalMutexAsrael);
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

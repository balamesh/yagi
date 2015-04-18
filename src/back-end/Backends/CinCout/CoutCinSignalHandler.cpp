/**
 * @file   CoutCinSignalHandler.cpp
 * @author Christopher Maier (cmaier.business@gmail.com)
 * @date   April 2015
 *
 * Simple signal handler implementation that uses cin/cout.
 */

/*
 This file is part of YAGI.

 YAGI is free software; you can redistribute it and/or
 modify it under the terms of the GNU Lesser General Public
 License as published by the Free Software Foundation; either
 version 3.0 of the License, or (at your option) any later version.

 YAGI is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 Lesser General Public License for more details.

 You should have received a copy of the GNU Lesser General Public
 License along with YAGI.
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

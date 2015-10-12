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


#include "WumpusSignalHandler.h"
#include <mutex>
#include <chrono>
#include <thread>

namespace yagi {
namespace execution {

std::mutex signalMutex;

WumpusSignalHandler::WumpusSignalHandler() : io_service(), resolver(io_service), socket(io_service)
{
	boost::asio::ip::tcp::resolver::query query{"localhost", "9002"};	
	boost::asio::ip::tcp::resolver::iterator endpoint_iterator = resolver.resolve(query); 
	boost::asio::connect(socket, endpoint_iterator);
}

WumpusSignalHandler::~WumpusSignalHandler()
{
}

std::unordered_map<std::string, std::string> WumpusSignalHandler::signal(
    const std::string& content, const std::vector<std::string>& variables)
{

  std::this_thread::sleep_for(std::chrono::milliseconds(1000));

  //no variables passed => no setting actions, just print whatever
  //there is to print
  if (!variables.size())
  {

    boost::system::error_code ignored_error;
    boost::asio::write(socket, boost::asio::buffer(content + "\n"), ignored_error);

    return std::unordered_map<std::string, std::string> { };
  }
  else //print and wait for input
  {
    std::unordered_map<std::string, std::string> retVals { };

    boost::system::error_code ignored_error;
    boost::asio::write(socket, boost::asio::buffer(content + "\n"), ignored_error);

    boost::asio::streambuf response;
    boost::asio::read_until(socket, response, "\n");

    std::istream is(&response);
    std::string str;
    is >> str;

    std::cout << str << std::endl;

    for (const auto& var : variables)
    {

       if (var=="$g" && str.find("G") != std::string::npos)
         retVals[var] = "true";
       else
         retVals[var] = "false";
       if (var=="$s" && str.find("S") != std::string::npos)
         retVals[var] = "true";
       else
         retVals[var] = "false";
       if (var=="$r" && str.find("R") != std::string::npos)
         retVals[var] = "true";
       else
         retVals[var] = "false";
       if (var=="$b" && str.find("B") != std::string::npos)
         retVals[var] = "true";
       else
         retVals[var] = "false";

       std::cout << str << " " << var << " " << retVals[var] << std::endl;
    }

    return retVals;
  }
}

} /* namespace execution */
} /* namespace yagi */

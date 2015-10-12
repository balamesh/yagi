/**
 * @file   CoutCinSignalHandler.h
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


#ifndef WUMPUSSIGNALHANDLER_H_
#define WUMPUSSIGNALHANDLER_H_

#include "../../Signals/IYAGISignalHandler.h"
#include <iostream>
#include <readline/readline.h>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio.hpp>

namespace yagi {
namespace execution {

/**
 * Responsible for connecting YAGI signals with Wumpus Applet
 */
class WumpusSignalHandler: public IYAGISignalHandler
{
  boost::asio::io_service io_service;
  boost::asio::ip::tcp::resolver resolver;
  boost::asio::ip::tcp::socket socket;

  public:
    /**
     * Default ctor
     */
    WumpusSignalHandler();

    /**
     * Default dtor
     */
    virtual ~WumpusSignalHandler();

    /**
     * Processes a YAGI signal
     * @param content The signaled content
     * @param variables The involved variables in case of 'setting'
     * @return The 'setting' values in case it was a setting action signal
     */
    std::unordered_map<std::string, std::string> signal(const std::string& content,
        const std::vector<std::string>& variables) override;
};

} /* namespace execution */
} /* namespace yagi */

#endif /* WUMPUSSIGNALHANDLER_H_ */

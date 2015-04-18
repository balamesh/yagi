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


#ifndef COUTCINSIGNALHANDLER_H_
#define COUTCINSIGNALHANDLER_H_

#include "../../Signals/IYAGISignalHandler.h"
#include <iostream>
#include <readline/readline.h>

namespace yagi {
namespace execution {

/**
 * Responsible for displaying YAGI signals via cout and reading data via cin
 */
class CoutCinSignalHandler: public IYAGISignalHandler
{
  public:
    /**
     * Default ctor
     */
    CoutCinSignalHandler();

    /**
     * Default dtor
     */
    virtual ~CoutCinSignalHandler();

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

#endif /* COUTCINSIGNALHANDLER_H_ */

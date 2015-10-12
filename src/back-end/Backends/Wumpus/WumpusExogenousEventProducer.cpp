/**
 * @file   FileExogenousEventProducer.cpp
 * @author Christopher Maier (cmaier.business@gmail.com)
 * @date   April 2015
 *
 * Implements exogenous events via a simple file watch approach.
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


#include "WumpusExogenousEventProducer.h"
#include <fstream>
#include <iostream>
#include <string.h>
#include <stdio.h>

using std::ifstream;
using std::ofstream;

namespace yagi {
namespace execution {

WumpusExogenousEventProducer::WumpusExogenousEventProducer()
{
}

bool WumpusExogenousEventProducer::eventAvailable()
{

    return false;
}

std::vector<std::pair<std::string, std::unordered_map<std::string, std::string> > > WumpusExogenousEventProducer::getEvent()
{
    std::vector<std::pair<std::string, std::unordered_map<std::string, std::string> > > result;
    return result;
}

} /* namespace execution */
} /* namespace yagi */

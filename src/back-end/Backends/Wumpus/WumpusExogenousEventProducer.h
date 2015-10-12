/**
 * @file   FileExogenousEventProducer.h
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


#ifndef WUMPUSEXOGENOUSEVENTPRODUCER_H_
#define WUMPUSEXOGENOUSEVENTPRODUCER_H_

#include "../../ExogenousEvents/IExogenousEventProducer.h"
#include <chrono>

namespace yagi {
namespace execution {

/**
 * Incorporates exogenous events from Wumpus Applet
 */
class WumpusExogenousEventProducer: public IExogenousEventProducer
{

  public:

    /**
     * Default ctor
     */
    WumpusExogenousEventProducer();

    /**
     * New event available?
     * @return
     */
    bool eventAvailable() override;

    /**
     * Get event + data
     * @return Event + data
     */
    std::vector<std::pair<std::string, std::unordered_map<std::string, std::string> > > getEvent()
        override;
};

} /* namespace execution */
} /* namespace yagi */

#endif /* WUMPUSEXOGENOUSEVENTPRODUCER_H_ */

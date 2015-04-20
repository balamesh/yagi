/**
 * @file   IExogenousEventProducer.cpp
 * @author Christopher Maier (cmaier.business@gmail.com)
 * @date   April 2015
 *
 * Basic description of an exogenous event producer
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


#include "IExogenousEventProducer.h"

namespace yagi {
namespace execution {

IExogenousEventProducer::IExogenousEventProducer()
{
}

IExogenousEventProducer::~IExogenousEventProducer()
{
}

void IExogenousEventProducer::initialize()
{ }

void IExogenousEventProducer::finalize()
{ }

bool IExogenousEventProducer::eventAvailable()
{
    return true;
}

} /* namespace execution */
} /* namespace yagi */

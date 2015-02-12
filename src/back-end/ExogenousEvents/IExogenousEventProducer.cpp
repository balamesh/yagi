/*
 * IExogenousEventProducer.cpp
 *
 *  Created on: Aug 18, 2014
 *      Author: cmaier
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

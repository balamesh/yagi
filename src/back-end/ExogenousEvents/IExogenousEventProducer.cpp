/*
 * IExogenousEventProducer.cpp
 *
 *  Created on: Aug 18, 2014
 *      Author: cmaier
 */

#include "IExogenousEventProducer.h"

namespace yagi {
namespace execution {

IExogenousEventProducer::IExogenousEventProducer(IExogenousEventConsumer* consumer) :
    consumer_(consumer)
{
}

IExogenousEventProducer::~IExogenousEventProducer()
{
}

} /* namespace execution */
} /* namespace yagi */

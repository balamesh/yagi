/**
 * @file   IExogenousEventProducer.cpp
 * @author Christopher Maier (cmaier.business@gmail.com)
 * @date   April 2015
 *
 * Basic description of an exogenous event producer
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

/*
 * ExoEventProducerSimulator.h
 *
 *  Created on: Aug 18, 2014
 *      Author: cmaier
 */

#ifndef EXOEVENTPRODUCERSIMULATOR_H_
#define EXOEVENTPRODUCERSIMULATOR_H_

#include "IExogenousEventProducer.h"

namespace yagi {
namespace execution {

class ExoEventProducerSimulator: public IExogenousEventProducer
{
  public:
    ExoEventProducerSimulator(IExogenousEventConsumer* consumer);
    virtual ~ExoEventProducerSimulator();
};

} /* namespace execution */
} /* namespace yagi */

#endif /* EXOEVENTPRODUCERSIMULATOR_H_ */

/*
 * IExogenousEventProducer.h
 *
 *  Created on: Aug 18, 2014
 *      Author: cmaier
 */

#ifndef IEXOGENOUSEVENTPRODUCER_H_
#define IEXOGENOUSEVENTPRODUCER_H_
#include <unordered_map>

#include "IExogenousEventConsumer.h"

namespace yagi {
namespace execution {

class IExogenousEventProducer
{
  protected:
    IExogenousEventConsumer* consumer_;

  public:
    IExogenousEventProducer(IExogenousEventConsumer* consumer);
    virtual ~IExogenousEventProducer();
};

} /* namespace execution */
} /* namespace yagi */

#endif /* IEXOGENOUSEVENTPRODUCER_H_ */

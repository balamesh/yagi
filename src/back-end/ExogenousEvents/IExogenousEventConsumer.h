/*
 * IExogenousEventConsumer.h
 *
 *  Created on: Aug 18, 2014
 *      Author: cmaier
 */

#ifndef IEXOGENOUSEVENTCONSUMER_H_
#define IEXOGENOUSEVENTCONSUMER_H_

#include <unordered_map>

namespace yagi {
namespace execution {

class IExogenousEventConsumer
{
  public:
    IExogenousEventConsumer();
    virtual ~IExogenousEventConsumer();

    virtual void consumeExoEventData(const std::string& eventName,
        const std::unordered_map<std::string, std::string>& variablesAndValues) = 0;
};

} /* namespace execution */
} /* namespace yagi */

#endif /* IEXOGENOUSEVENTCONSUMER_H_ */

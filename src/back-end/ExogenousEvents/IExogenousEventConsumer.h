/**
 * @file   IExogenousEventConsumer.h
 * @author Christopher Maier (cmaier.business@gmail.com)
 * @date   April 2015
 *
 * Basic description of an exogenous event consumer
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


#ifndef IEXOGENOUSEVENTCONSUMER_H_
#define IEXOGENOUSEVENTCONSUMER_H_

#include <unordered_map>

namespace yagi {
namespace execution {

/**
 * Abstract class for exogenous event consumers
 */
class IExogenousEventConsumer
{
  protected:

    /**
     * The name of the consumer
     */
    std::string exoEventConsumerName_ = "<unknown>";

  public:

    /**
     * Default ctor
     */
    IExogenousEventConsumer();

    /**
     * Default dtor
     */
    virtual ~IExogenousEventConsumer();

    /**
     * Consume data from an exogenous event
     * @param eventName The name of the event
     * @param variablesAndValues Variable names and values from the event
     */
    virtual void consumeExoEventData(const std::string& eventName,
        const std::unordered_map<std::string, std::string>& variablesAndValues) = 0;

    /**
     * Getter for the exo event consumer name
     * @return The name of the consumer
     */
    const std::string& getExoEventConsumerName() const
    {
      return exoEventConsumerName_;
    }

    /**
     * Setter for the exo event consumer name
     * @param exoEventConsumerName The name of the consumer
     */
    void setExoEventConsumerName(const std::string& exoEventConsumerName)
    {
      exoEventConsumerName_ = exoEventConsumerName;
    }
};

} /* namespace execution */
} /* namespace yagi */

#endif /* IEXOGENOUSEVENTCONSUMER_H_ */

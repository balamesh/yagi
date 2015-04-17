/**
 * @file   IExogenousEventConsumer.h
 * @author Christopher Maier (cmaier.business@gmail.com)
 * @date   April 2015
 *
 * Basic description of an exogenous event consumer
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

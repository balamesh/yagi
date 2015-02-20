/*
 * ExoEventNotifier.cpp
 *
 *  Created on: Aug 26, 2014
 *      Author: cmaier
 */

#include "ExoEventNotifier.h"
#include <fstream>
#include <iostream>
#include <string.h>
#include <stdio.h>
#include "../BackendFactory.h"
#include "IExogenousEventProducer.h"

#include "../../utils/fileExists.h"
using std::ifstream;
using std::ofstream;

namespace yagi {
namespace execution {

ExoEventNotifier::ExoEventNotifier() : sleep_duration_(100)
{

}

ExoEventNotifier::~ExoEventNotifier()
{
  stopListen_ = true;
  if (t.joinable()) t.join();
}

bool ExoEventNotifier::isConsumerRegistered(IExogenousEventConsumer* consumer)
{
  auto storedConsumer = exoEventConsumers_.find(consumer->getExoEventConsumerName());
  return storedConsumer != std::end(exoEventConsumers_);
}

void ExoEventNotifier::registerEventConsumer(IExogenousEventConsumer* consumer)
{
  if (isConsumerRegistered(consumer))
  {
    throw std::runtime_error(
        "Exogenous event consumer with name '" + consumer->getExoEventConsumerName()
            + "' is already registered!");
  }

  exoEventConsumers_[consumer->getExoEventConsumerName()] = consumer;

  if (!threadRunning_)
  {
    waitForExoEventData();
    threadRunning_ = true;
  }
}

void ExoEventNotifier::registerEventConsumerIfNotRegistered(IExogenousEventConsumer* consumer)
{
  if (isConsumerRegistered(consumer))
  {
    return;
  }

  exoEventConsumers_[consumer->getExoEventConsumerName()] = consumer;

  if (!threadRunning_)
  {
    waitForExoEventData();
    threadRunning_ = true;
  }
}

void ExoEventNotifier::unRegisterEventConsumer(IExogenousEventConsumer* consumer)
{
  if (isConsumerRegistered(consumer))
  {
    exoEventConsumers_.erase(consumer->getExoEventConsumerName());
  }
}

void ExoEventNotifier::waitForExoEventData()
{
  std::shared_ptr<IExogenousEventProducer> event_producer =
    BackendFactory::getInstance().getBackend()->getExogenousEventProducer();
  if (! event_producer) {
    return;
  }

  t = std::thread([event_producer, this]()
  {

    event_producer->initialize();

    while (true)
    {
        if (stopListen_)
        {
          break;
        }

        std::this_thread::sleep_for(sleep_duration_);

        if (stopListen_)
        {
          break;
        }

        if(event_producer->eventAvailable())
        {
            std::vector<std::pair<std::string, std::unordered_map<std::string, std::string> > > events =
	      event_producer->getEvent();

            for(const auto& e : events)
            {
                for (const auto& kv : exoEventConsumers_)
                {
                  kv.second->consumeExoEventData(e.first, e.second);
                }
            }
        }
    }

    event_producer->finalize();
  });
}


} /* namespace execution */
} /* namespace yagi */

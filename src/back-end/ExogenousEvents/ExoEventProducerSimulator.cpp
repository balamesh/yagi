/*
 * ExoEventProducerSimulator.cpp
 *
 *  Created on: Aug 18, 2014
 *      Author: cmaier
 */

#include "ExoEventProducerSimulator.h"

#include "../ExecutableElementsContainer.h"
namespace yagi {
namespace execution {

ExoEventProducerSimulator::ExoEventProducerSimulator(IExogenousEventConsumer* consumer) :
    IExogenousEventProducer(consumer)
{

  if (ExecutableElementsContainer::getInstance().exoEventExists("testExoEvent",2))
  {
    //TODO: Test for a specific exo event!
    //Implementation needs to be generalized!
    consumer_->consumeExoEventData("testExoEvent", std::unordered_map<std::string, std::string> {
        std::make_pair("$x", "a"), std::make_pair("$y", "b") });

    consumer_->consumeExoEventData("testExoEvent", std::unordered_map<std::string, std::string> {
        std::make_pair("$x", "b"), std::make_pair("$y", "a") });
  }

}

ExoEventProducerSimulator::~ExoEventProducerSimulator()
{

}

} /* namespace execution */
} /* namespace yagi */

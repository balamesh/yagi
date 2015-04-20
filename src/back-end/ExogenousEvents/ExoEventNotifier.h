/**
 * @file   ExoEventNotifier.h
 * @author Christopher Maier (cmaier.business@gmail.com)
 * @date   April 2015
 *
 * Notifies registered subscribers if exogenous events occurred.
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


#ifndef EXOEVENTNOTIFIER_H_
#define EXOEVENTNOTIFIER_H_

#include <atomic>
#include "IExogenousEventConsumer.h"

#include <unordered_map>
#include <mutex>
#include <thread>
#include <vector>

namespace yagi {
namespace execution {

/**
 * Mutex instance for singleton impl
 */
static std::mutex exoEventNotifierMutex_;

/**
 * Notifies registered subscribers if exogenous events occurred.
 */
class ExoEventNotifier
{
  private:
    /**
     * Copy ctor
     * @param Instance to copy
     */
    ExoEventNotifier(ExoEventNotifier const&);

    /**
     * Assignment operator
     * @param Instance to assign
     */
    void operator=(ExoEventNotifier const&);

    /**
     * Default ctor
     */
    ExoEventNotifier();

    /**
     * Default dtor
     */
    ~ExoEventNotifier();

    /**
     * Stop listening for exo events if set
     */
    bool stopListen_ = false;

    /**
     * Thread main loop variable
     */
    bool threadRunning_ = false;

    /**
     * Registered name-consumer mapping
     */
    std::unordered_map<std::string, IExogenousEventConsumer*> exoEventConsumers_;

    /**
     * Responsible for (asynchronously) waiting for exogenous data
     */
    void waitForExoEventData();

    /**
     * Thread instance for exo data consumption
     */
    std::thread t;

    /**
     * Sleeping duration for thread
     */
    std::chrono::milliseconds sleep_duration_;

  public:

    /**
     * Singleton impl
     * @return The instance
     */
    static ExoEventNotifier& getInstance()
    {
      std::lock_guard<std::mutex> lk(exoEventNotifierMutex_);

      static ExoEventNotifier instance;
      return instance;
    }

    /**
     * Register a new exo. event consumer
     * @param consumer The consumer to register
     */
    void registerEventConsumer(IExogenousEventConsumer* consumer);

    /**
     * Registers a new exo. event consumer if it is not already registered
     * @param consumer The consumer to register
     */
    void registerEventConsumerIfNotRegistered(IExogenousEventConsumer* consumer);

    /**
     * Unregisters exo. event consumer
     * @param consumer The consumer to unregister
     */
    void unRegisterEventConsumer(IExogenousEventConsumer* consumer);bool isConsumerRegistered(
        IExogenousEventConsumer* consumer);
};

} /* namespace execution */
} /* namespace yagi */

#endif /* EXOEVENTNOTIFIER_H_ */

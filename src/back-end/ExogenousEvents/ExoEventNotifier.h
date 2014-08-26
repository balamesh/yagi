/*
 * ExoEventNotifier.h
 *
 *  Created on: Aug 26, 2014
 *      Author: cmaier
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

static std::mutex exoEventNotifierMutex_;

class ExoEventNotifier
{
  private:
    ExoEventNotifier(ExoEventNotifier const&);
    void operator=(ExoEventNotifier const&);
    ExoEventNotifier();
    ~ExoEventNotifier();

    bool stopListen_ = false;
    bool threadRunning_ = false;
    std::unordered_map<std::string, IExogenousEventConsumer*> exoEventConsumers_;
    std::vector<std::tuple<std::string, std::string, std::string>> splitFileLines(
        std::vector<std::string> lines);

    void waitForExoEventData();
    std::vector<std::string> readLinesFromFile();
    std::thread t;
    const std::string fileName = "exoEventData.txt";

  public:
    static ExoEventNotifier& getInstance()
    {
      std::lock_guard<std::mutex> lk(exoEventNotifierMutex_);

      static ExoEventNotifier instance;
      return instance;
    }

    void registerEventConsumer(IExogenousEventConsumer* consumer);
    void registerEventConsumerIfNotRegistered(IExogenousEventConsumer* consumer);
    void unRegisterEventConsumer(IExogenousEventConsumer* consumer);
    bool isConsumerRegistered(IExogenousEventConsumer* consumer);
};

} /* namespace execution */
} /* namespace yagi */

#endif /* EXOEVENTNOTIFIER_H_ */

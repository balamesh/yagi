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

#include "../../utils/fileExists.h"
using std::ifstream;
using std::ofstream;

namespace yagi {
namespace execution {

ExoEventNotifier::ExoEventNotifier()
{

}

ExoEventNotifier::~ExoEventNotifier()
{
  stopListen_ = true;
  t.join();
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
  t = std::thread([&]()
  {
    while (true)
    {
      while (!fileExists(fileName))
      {
        std::chrono::milliseconds dura(50);
        std::this_thread::sleep_for(dura);

        if (stopListen_)
        {
          break;
        }
      }

      //let the file "settle"
      std::chrono::milliseconds dura(250);
      std::this_thread::sleep_for(dura);

      if (stopListen_)
      {
        break;
      }

      auto lines = readLinesFromFile();
      auto values = splitFileLines(lines);

      std::unordered_map<std::string, std::string> variablesAndValues;

      //TODO: we assume we have just data for 1 exo event in the file
      //and all the var names are unique!
      std::string eventName = "<unknown>";
      for (const auto& tuple : values)
      {
        variablesAndValues[std::get<1>(tuple)] = std::get<2>(tuple);
        eventName = std::get<0>(tuple);
      }

      for (const auto& kv : exoEventConsumers_)
      {
        kv.second->consumeExoEventData(eventName, variablesAndValues);
      }
    }
  });
}

std::vector<std::string> ExoEventNotifier::readLinesFromFile()
{
  std::vector<std::string> lines;
  std::string line;
  ifstream myfile(fileName);
  if (myfile.is_open())
  {
    while (getline(myfile, line))
    {
      lines.push_back(line);
    }
    myfile.close();

    remove(fileName.c_str());
  }
  else
    std::cout << "Unable to open exo event data file";

  return lines;
}

std::vector<std::tuple<std::string, std::string, std::string>> ExoEventNotifier::splitFileLines(
    std::vector<std::string> lines)
{
  std::string delimiter = ";";
  std::vector<std::tuple<std::string, std::string, std::string>> values;

  for (auto line : lines)
  {
    size_t pos = 0;
    std::string token;

    std::vector<std::string> lineValues;
    while ((pos = line.find(delimiter)) != std::string::npos)
    {
      lineValues.push_back(line.substr(0, pos));
      line.erase(0, pos + delimiter.length());
    }

    if (lineValues.size() == 3)
    {
      values.push_back(std::make_tuple(lineValues[0], lineValues[1], lineValues[2]));
    }
    else
    {
      std::cout
          << "[WARNING] Invalid line in exogenous event file! Must have exactly 3 values, ';' separated!"
          << std::endl;
    }
  }

  return values;
}

} /* namespace execution */
} /* namespace yagi */

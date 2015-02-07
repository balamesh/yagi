/*
 * PrintOutSignalReceiver.h
 *
 *  Created on: Jul 23, 2014
 *      Author: cmaier
 */

#ifndef ASRAELSIGNALHANDLER_H_
#define ASRAELSIGNALHANDLER_H_

#include "IYAGISignalHandler.h"
#include <iostream>
#include <readline/readline.h>

#ifdef ASRAEL

#include <asrael/asrael_remote_control_client.h>

namespace yagi {
namespace execution {

class AsraelSignalHandler: public IYAGISignalHandler
{
  public:
    AsraelSignalHandler();
    virtual ~AsraelSignalHandler();

    std::unordered_map<std::string, std::string> signal(const std::string& content,
        const std::vector<std::string>& variables) override;
private:
    int connectSimulator(std::string level = "Kitchen");
    std::vector<std::string> chopParameters(std::string params);

    AsraelRemoteControlClient client;
};

} /* namespace execution */
} /* namespace yagi */

#endif

#endif /* ASRAELSIGNALHANDLER_H_ */

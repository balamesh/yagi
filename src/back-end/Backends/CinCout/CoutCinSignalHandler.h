/*
 * PrintOutSignalReceiver.h
 *
 *  Created on: Jul 23, 2014
 *      Author: cmaier
 */

#ifndef COUTCINSIGNALHANDLER_H_
#define COUTCINSIGNALHANDLER_H_

#include "../../Signals/IYAGISignalHandler.h"
#include <iostream>
#include <readline/readline.h>

namespace yagi {
namespace execution {

class CoutCinSignalHandler: public IYAGISignalHandler
{
  public:
    CoutCinSignalHandler();
    virtual ~CoutCinSignalHandler();

    std::unordered_map<std::string, std::string> signal(const std::string& content,
        const std::vector<std::string>& variables) override;
};

} /* namespace execution */
} /* namespace yagi */

#endif /* COUTCINSIGNALHANDLER_H_ */

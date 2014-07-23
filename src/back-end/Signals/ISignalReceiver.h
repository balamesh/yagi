/*
 * ISignalReceiver.h
 *
 *  Created on: Jul 23, 2014
 *      Author: cmaier
 */

#ifndef ISIGNALRECEIVER_H_
#define ISIGNALRECEIVER_H_

#include <string>

namespace yagi {
namespace execution {

class ISignalReceiver
{
  public:
    ISignalReceiver();
    virtual ~ISignalReceiver();

    virtual void signal(const std::string& content) = 0;
};

} /* namespace execution */
} /* namespace yagi */

#endif /* ISIGNALRECEIVER_H_ */

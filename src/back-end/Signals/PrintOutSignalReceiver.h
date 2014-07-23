/*
 * PrintOutSignalReceiver.h
 *
 *  Created on: Jul 23, 2014
 *      Author: cmaier
 */

#ifndef PRINTOUTSIGNALRECEIVER_H_
#define PRINTOUTSIGNALRECEIVER_H_

#include "ISignalReceiver.h"
#include <iostream>

namespace yagi {
namespace execution {

class PrintOutSignalReceiver: public ISignalReceiver
{
  public:
    PrintOutSignalReceiver();
    virtual ~PrintOutSignalReceiver();

    void signal(const std::string& content) override;
};

} /* namespace execution */
} /* namespace yagi */

#endif /* PRINTOUTSIGNALRECEIVER_H_ */

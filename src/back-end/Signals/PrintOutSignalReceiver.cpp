/*
 * PrintOutSignalReceiver.cpp
 *
 *  Created on: Jul 23, 2014
 *      Author: cmaier
 */

#include "PrintOutSignalReceiver.h"

namespace yagi {
namespace execution {

PrintOutSignalReceiver::PrintOutSignalReceiver()
{
}

PrintOutSignalReceiver::~PrintOutSignalReceiver()
{
}

void PrintOutSignalReceiver::signal(const std::string& content)
{
  std::cout << "[Signal] " << content << std::endl;
}

} /* namespace execution */
} /* namespace yagi */

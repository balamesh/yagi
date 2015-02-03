#ifndef BACKEND_H
#define BACKEND_H

#include "Signals/IYAGISignalHandler.h"
#include "ExogenousEvents/IExogenousEventConsumer.h"

namespace yagi {
namespace execution {

class Backend : public IYAGISignalHandler
{

};


} /* namespace execution */
} /* namespace yagi */

#endif // BACKEND_H

#ifndef BACKEND_H
#define BACKEND_H

#include <memory>
#include "Signals/IYAGISignalHandler.h"
#include "ExogenousEvents/IExogenousEventConsumer.h"

namespace yagi {
namespace execution {

class Backend
{
    std::shared_ptr<IYAGISignalHandler> signal_handler_ = nullptr;

public:

    std::shared_ptr<IYAGISignalHandler> getSignalHandler()
    {
        return signal_handler_;
    }


};


} /* namespace execution */
} /* namespace yagi */

#endif // BACKEND_H

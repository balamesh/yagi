#ifndef BACKEND_H
#define BACKEND_H

#include <memory>
#include "Signals/IYAGISignalHandler.h"
// #include "ExogenousEvents/IExogenousEventConsumer.h"
#include <Pluma/Pluma.hpp>

namespace yagi {
namespace execution {

class Backend
{
protected:
    std::shared_ptr<IYAGISignalHandler> signal_handler_ = nullptr;

    virtual void creatSignalHandler() = 0;

public:

    Backend();

    std::shared_ptr<IYAGISignalHandler> getSignalHandler()
    {
        if(!signal_handler_)
            creatSignalHandler();

        return signal_handler_;
    }


};

PLUMA_PROVIDER_HEADER(Backend)
} /* namespace execution */
} /* namespace yagi */
#endif // BACKEND_H

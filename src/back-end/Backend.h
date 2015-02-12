#ifndef BACKEND_H
#define BACKEND_H

#include <memory>
#include "Signals/IYAGISignalHandler.h"
#include "ExogenousEvents/IExogenousEventProducer.h"
#include <Pluma/Pluma.hpp>

namespace yagi {
namespace execution {

class Backend
{
protected:
    std::shared_ptr<IYAGISignalHandler> signal_handler_ = nullptr;
    std::shared_ptr<IExogenousEventProducer> exogenious_event_producer_ = nullptr;

    virtual void creatSignalHandler() = 0;
    virtual void createExogenousEventProducer();

public:

    Backend();

    std::shared_ptr<IYAGISignalHandler> getSignalHandler()
    {
        if(!signal_handler_)
            creatSignalHandler();

        return signal_handler_;
    }

    std::shared_ptr<IExogenousEventProducer> getExogenousEventProducer()
    {
        if(!exogenious_event_producer_)
            createExogenousEventProducer();

        return exogenious_event_producer_;
    }


};

PLUMA_PROVIDER_HEADER(Backend)
} /* namespace execution */
} /* namespace yagi */
#endif // BACKEND_H

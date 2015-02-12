#include "Backend.h"
#include "ExogenousEvents/DefaultExogenousEventProducer.h"

namespace yagi {
namespace execution {

    Backend::Backend()
    {
    }

    void Backend::createExogenousEventProducer()
    {
        exogenious_event_producer_ = std::make_shared<DefaultExogenousEventProducer>();
    }

    PLUMA_PROVIDER_SOURCE(Backend, 1, 1)
} /* namespace execution */
} /* namespace yagi */

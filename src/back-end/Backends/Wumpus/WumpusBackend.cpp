#include "WumpusBackend.h"
#include "WumpusSignalHandler.h"
#include "WumpusExogenousEventProducer.h"

namespace yagi {
namespace execution {
WumpusBackend::WumpusBackend()
{
    std::cout << "WumpusBackend constructed ..." << std::endl;
}

void WumpusBackend::creatSignalHandler()
{
    std::cout << "WumpusBackend signal handler created ..." << std::endl;
    signal_handler_ = std::make_shared<WumpusSignalHandler>();
}
void WumpusBackend::createExogenousEventProducer()
{
    std::cout << "WumpusBackend exogenous events producer created ..." << std::endl;
    exogenious_event_producer_ = std::make_shared<WumpusExogenousEventProducer>();
}

} /* namespace execution */
} /* namespace yagi */

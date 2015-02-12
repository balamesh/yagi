#include "CinCoutBackend.h"
#include "CoutCinSignalHandler.h"
#include "FileExogenousEventProducer.h"

namespace yagi {
namespace execution {
CinCoutBackend::CinCoutBackend()
{
    std::cout << "CinCoutBackend constructed ..." << std::endl;
}

void CinCoutBackend::creatSignalHandler()
{
    std::cout << "CinCoutBackend signal handler created ..." << std::endl;
    signal_handler_ = std::make_shared<CoutCinSignalHandler>();
}

void CinCoutBackend::createExogenousEventProducer()
{
    std::cout << "CinCoutBackend exogenous events producer created ..." << std::endl;
    exogenious_event_producer_ = std::make_shared<FileExogenousEventProducer>();
}

} /* namespace execution */
} /* namespace yagi */

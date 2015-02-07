#include "CinCoutBackend.h"
#include "CoutCinSignalHandler.h"

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

} /* namespace execution */
} /* namespace yagi */

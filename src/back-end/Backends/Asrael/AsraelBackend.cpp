#include "AsraelBackend.h"
#include "AsraelSignalHandler.h"

namespace yagi {
namespace execution {
AsraelBackend::AsraelBackend()
{
    std::cout << "AsraelBackend constructed ..." << std::endl;
}

void AsraelBackend::creatSignalHandler()
{
    std::cout << "AsraelBackend signal handler created ..." << std::endl;
    signal_handler_ = std::make_shared<AsraelSignalHandler>();
}

} /* namespace execution */
} /* namespace yagi */

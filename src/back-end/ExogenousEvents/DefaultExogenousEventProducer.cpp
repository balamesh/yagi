

#include "DefaultExogenousEventProducer.h"

namespace yagi {
namespace execution {

bool DefaultExogenousEventProducer::eventAvailable()
{
    return false;
}
std::vector<std::pair<std::string, std::unordered_map<std::string, std::string> > > DefaultExogenousEventProducer::getEvent()
{
    return std::vector<std::pair<std::string, std::unordered_map<std::string, std::string> > >();
}

} /* namespace execution */
} /* namespace yagi */

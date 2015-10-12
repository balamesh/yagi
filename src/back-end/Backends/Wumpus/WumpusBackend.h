#ifndef WUMPUSBACKEND_H
#define WUMPUSBACKEND_H

#include "../../Backend.h"
#include <iostream>

namespace yagi {
namespace execution {
class WumpusBackend: public Backend
{

protected:
    void creatSignalHandler() override;
    void createExogenousEventProducer() override;

public:
    WumpusBackend();

};


PLUMA_INHERIT_PROVIDER(WumpusBackend, Backend)

} /* namespace execution */
} /* namespace yagi */

#endif // WUMPUSBACKEND_H

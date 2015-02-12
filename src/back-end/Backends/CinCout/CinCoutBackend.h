#ifndef CINCOUTBACKEND_H
#define CINCOUTBACKEND_H

#include "../../Backend.h"
#include <iostream>

namespace yagi {
namespace execution {
class CinCoutBackend: public Backend
{

protected:
    void creatSignalHandler() override;
    void createExogenousEventProducer() override;

public:
    CinCoutBackend();

};


PLUMA_INHERIT_PROVIDER(CinCoutBackend, Backend)

} /* namespace execution */
} /* namespace yagi */

#endif // CINCOUTBACKEND_H

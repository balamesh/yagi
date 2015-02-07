#ifndef ASRAELBACKEND_H
#define ASRAELBACKEND_H

#include "../../Backend.h"
#include <iostream>

namespace yagi {
namespace execution {
class AsraelBackend: public Backend
{

protected:
    virtual void creatSignalHandler();

public:
    AsraelBackend();

};


PLUMA_INHERIT_PROVIDER(AsraelBackend, Backend)

} /* namespace execution */
} /* namespace yagi */

#endif // CINCOUTBACKEND_H

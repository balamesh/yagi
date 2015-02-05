#ifndef BACKENDFACTORY_H
#define BACKENDFACTORY_H

#include "Backend.h"
#include "CinCoutBackend.h"
#include <memory>
#include <iostream>

namespace yagi {
namespace execution {

class BackendFactory final
{
    std::shared_ptr<Backend> backend_ = nullptr;

public:

    void initBackend(std::string backend_str)
    {
        std::cout << "initializing backend " << backend_str << std::endl;

        if (!backend_str.compare("CinCoutBackend"))
        {
            backend_ = std::make_shared<CinCoutBackend>();
        }
    }

    static BackendFactory & getInstance()
    {
      static BackendFactory instance;
      return instance;
    }

    std::shared_ptr<Backend> getBackend()
    {
        if (backend_ == nullptr)
        {

        }
        return backend_;
    }
};

}
}

#endif // BACKENDFACTORY_H

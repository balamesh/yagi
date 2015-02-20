#ifndef BACKENDFACTORY_H
#define BACKENDFACTORY_H

#include "Backend.h"
#include <Pluma/Pluma.hpp>
#include <memory>
#include <iostream>

namespace yagi {
namespace execution {

class BackendFactory final
{
    std::shared_ptr<Backend> backend_ = nullptr;

    pluma::Pluma pluma_;
    BackendFactory()
    {
        pluma_.acceptProviderType<BackendProvider>();
    }

    virtual ~BackendFactory()
    {
        backend_.reset();
    }

public:

    void initBackend(std::string backend_str)
    {
        std::cout << "initializing backend " << backend_str << std::endl;

        pluma_.load("./", "lib" + backend_str);

        std::vector<BackendProvider*> providers;
        pluma_.getProviders(providers);

        if(providers.size() != 1)
        {
            std::cerr << "no backend plugin" << std::endl;
            std::terminate();
        }

        backend_ = std::shared_ptr<Backend>(providers[0]->create());
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
		//FIXME make it thread safe
        }
        return backend_;
    }
};

} /* namespace execution */
} /* namespace yagi */

#endif // BACKENDFACTORY_H

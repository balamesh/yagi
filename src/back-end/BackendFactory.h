#ifndef BACKENDFACTORY_H
#define BACKENDFACTORY_H

#include "Backend.h"
#include <Pluma/Pluma.hpp>
#include <memory>
#include <iostream>
#include <mutex>
#include <condition_variable>

namespace yagi {
namespace execution {

class BackendFactory final
{
    std::shared_ptr<Backend> backend_ = nullptr;
    std::mutex the_lock_;
    std::condition_variable lock_notifier_;

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
        std::unique_lock<std::mutex> lock(the_lock_);
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
        lock_notifier_.notify_all();
    }

    static BackendFactory & getInstance()
    {
      static BackendFactory instance;
      return instance;
    }

    std::shared_ptr<Backend> getBackend()
    {
        std::unique_lock<std::mutex> lock(the_lock_);
        while (backend_ == nullptr)
        {
            std::cout << "[WARNING]: wait till backend is initlized" << std::endl;
            lock_notifier_.wait(lock);
        }
        return backend_;
    }
};

} /* namespace execution */
} /* namespace yagi */

#endif // BACKENDFACTORY_H

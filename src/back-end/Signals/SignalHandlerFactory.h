/*
 * SignalHandlerFactory.h
 *
 *  Created on: Oct 8, 2014
 *      Author: cmaier
 */

#ifndef SIGNALHANDLERFACTORY_H_
#define SIGNALHANDLERFACTORY_H_

#include <memory>
#ifndef ASRAEL
#include "CoutCinSignalHandler.h"
#define SignalHandler CoutCinSignalHandler
#else
#include "AsraelSignalHandler.h"
#define SignalHandler AsraelSignalHandler
#endif

namespace yagi {
namespace execution {
class IYAGISignalHandler;
} /* namespace execution */
} /* namespace yagi */

namespace yagi {
namespace execution {

class SignalHandlerFactory final
{
  private:
    using ConcreteSignalHandlerType = SignalHandler;

    SignalHandlerFactory();
    ~SignalHandlerFactory();

    SignalHandlerFactory(SignalHandlerFactory const&);
    void operator=(SignalHandlerFactory const&);

    std::shared_ptr<IYAGISignalHandler> signalHandler_ = nullptr;

  public:
    static SignalHandlerFactory& getInstance()
    {
      static SignalHandlerFactory instance;
      return instance;
    }

   std::shared_ptr<IYAGISignalHandler> getSignalHandler()
   {
     if (signalHandler_ == nullptr)
     {
       signalHandler_ = std::make_shared<ConcreteSignalHandlerType>();
     }
     return signalHandler_;
   }

};

} /* namespace execution */
} /* namespace yagi */

#endif /* SIGNALHANDLERFACTORY_H_ */

#ifndef IDEFAULTEXOGENOUSEVENTPRODUCER_H_
#define IDEFAULTEXOGENOUSEVENTPRODUCER_H_

#include "IExogenousEventProducer.h"

namespace yagi {
namespace execution {

class DefaultExogenousEventProducer : public IExogenousEventProducer
{
public:
    virtual bool eventAvailable();
    virtual std::vector<std::pair<std::string, std::unordered_map<std::string, std::string> > > getEvent();
};

} /* namespace execution */
} /* namespace yagi */

#endif /* IDEFAULTEXOGENOUSEVENTPRODUCER_H_ */

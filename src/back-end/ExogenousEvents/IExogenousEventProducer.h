/*
 * IExogenousEventProducer.h
 *
 *  Created on: Aug 18, 2014
 *      Author: cmaier
 */

#ifndef IEXOGENOUSEVENTPRODUCER_H_
#define IEXOGENOUSEVENTPRODUCER_H_
#include <unordered_map>
#include <vector>

namespace yagi {
namespace execution {

class IExogenousEventProducer
{
  public:
    IExogenousEventProducer();
    virtual ~IExogenousEventProducer();

    /*!
     * \brief initialize the exogenious event producer at thread start up
     * this function is called after the thread processing exogenious events is started
     * the function return if the initialization is finished completely
     */
    virtual void initialize();

    /*!
     * \brief finalize the exogenious event producer at the thread take down
     * this function is called before the thread processing exogenious events is stoped
     */
    virtual void finalize();

    /*!
     * \brief eventAvailable return true if a event is available
     * the function is called every time before the producer is queried for the events
     * if the function is not overritten it always return true
     * \return true if a event is available
     */
    virtual bool eventAvailable();

    /*!
     * \brief getEvent retrieve the events which are accumulated since the last call of this function
     * the function return a vector of <exogenious event name, argument vector>
     * the function should return all events which have occured since the last call of this function
     * the function must not block and should return imidiatly
     * \return the events since the last call of the function
     */
    virtual std::vector<std::pair<std::string, std::unordered_map<std::string, std::string> > > getEvent() = 0;
};

} /* namespace execution */
} /* namespace yagi */

#endif /* IEXOGENOUSEVENTPRODUCER_H_ */

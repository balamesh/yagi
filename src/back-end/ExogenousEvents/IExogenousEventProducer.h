/**
 * @file   IExogenousEventProducer.h
 * @author Christopher Maier (cmaier.business@gmail.com)
 * @date   April 2015
 *
 * Basic description of an exogenous event producer
 */

/*
 This file is part of YAGI.

 YAGI is free software; you can redistribute it and/or
 modify it under the terms of the GNU Lesser General Public
 License as published by the Free Software Foundation; either
 version 3.0 of the License, or (at your option) any later version.

 YAGI is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 Lesser General Public License for more details.

 You should have received a copy of the GNU Lesser General Public
 License along with YAGI.
*/


#ifndef IEXOGENOUSEVENTPRODUCER_H_
#define IEXOGENOUSEVENTPRODUCER_H_
#include <unordered_map>
#include <vector>

namespace yagi {
namespace execution {

/**
 * Abstract class for exogenous event producers
 */
class IExogenousEventProducer
{
  public:
    /**
     * Default ctor
     */
    IExogenousEventProducer();

    /**
     * Default dtor
     */
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

/*
 * make_unique.h
 *
 *  Created on: Apr 24, 2014
 *      Author: cmaier
 */

#ifndef MAKE_UNIQUE_H_
#define MAKE_UNIQUE_H_

#include <utility>

//provided by herb sutter
template<typename T, typename ...Args>
std::unique_ptr<T> make_unique(Args&& ...args)
{
    return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
}


#endif /* MAKE_UNIQUE_H_ */

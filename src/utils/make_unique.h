/**
 * @file   make_unique.h
 * @author Christopher Maier
 * @date   January 2015
 *
 * Implementation of make_unique provided by Herb Sutter, see http://herbsutter.com/gotw/_102/
 */

#ifndef MAKE_UNIQUE_H_
#define MAKE_UNIQUE_H_

#include <utility>

/**
 * Implementation of make_unique
 * @param args Arguments for unique_ptr
 * @return unique_ptr that encapsulates given arguments.
 */
template<typename T, typename ...Args>
std::unique_ptr<T> make_unique(Args&& ...args)
{
  return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
}

#endif /* MAKE_UNIQUE_H_ */

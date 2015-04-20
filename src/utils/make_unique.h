/**
 * @file   make_unique.h
 * @author Christopher Maier
 * @date   January 2015
 *
 * Implementation of make_unique provided by Herb Sutter, see http://herbsutter.com/gotw/_102/
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

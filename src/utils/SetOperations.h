/**
 * @file   SetOperations.h
 * @author Christopher Maier
 * @date   January 2015
 *
 * Mathematical set operations for YAGI sets.
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


#ifndef SETOPERATIONS_H_
#define SETOPERATIONS_H_

#include <vector>
#include <string>
#include <algorithm>
#include "CustomComparers.h"

namespace yagi {
namespace operations {

/**
 * Returns a union of 2 YAGI sets
 */
std::vector<std::vector<std::string>> buildUnion(std::vector<std::vector<std::string>> v1,
    std::vector<std::vector<std::string>> v2);

/**
 * Returns a complement of 2 YAGI sets
 */
std::vector<std::vector<std::string>> buildComplement(std::vector<std::vector<std::string>> v1,
    std::vector<std::vector<std::string>> v2);

}
}

#endif /* SETOPERATIONS_H_ */

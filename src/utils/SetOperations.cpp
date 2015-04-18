/**
 * @file   SetOperations.cpp
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


#include "SetOperations.h"

namespace yagi {
namespace operations {

std::vector<std::vector<std::string>> buildUnion(std::vector<std::vector<std::string>> v1,
    std::vector<std::vector<std::string>> v2)
{
  std::vector<std::vector<std::string>> dest;
  std::sort(std::begin(v1), std::end(v1), yagi::comparers::tupleLessThan);
  std::sort(std::begin(v2), std::end(v2), yagi::comparers::tupleLessThan);

  std::set_union(v1.begin(), v1.end(), v2.begin(), v2.end(), std::back_inserter(dest),
      yagi::comparers::tupleLessThan);

  return dest;
}

std::vector<std::vector<std::string>> buildComplement(std::vector<std::vector<std::string>> v1,
    std::vector<std::vector<std::string>> v2)
{

  std::vector<std::vector<std::string>> dest;
  std::set_difference(v1.begin(), v1.end(), v2.begin(), v2.end(), std::back_inserter(dest),
      yagi::comparers::tupleLessThan);

  return dest;
}

}
}


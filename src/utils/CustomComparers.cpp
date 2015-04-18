/**
 * @file   CustomComparers.cpp
 * @author Christopher Maier
 * @date   January 2015
 *
 * Custom comparing functions for YAGI tuples.
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


#include "CustomComparers.h"

namespace yagi {
namespace comparers {

bool tupleLessThan(const std::vector<std::string>& v1, const std::vector<std::string>& v2)
{
  if (v1.size() < v2.size())
  {
    return true;
  }
  else if (v1.size() > v2.size())
  {
    return false;
  }
  else
  {
    std::string s1 = "";
    std::string s2 = "";
    int idx = 0;

    std::for_each(std::begin(v1), std::end(v1), [&s1,&s2,&v2,&idx](const std::string& s)
    {
      s1 += s;
      s2 += v2[idx];
      idx++;
    });

    return s1 < s2;
  }
}

bool tuplesEqual(const std::vector<std::string>& v1, const std::vector<std::string>& v2)
{
  return !tupleLessThan(v1, v2) && !tupleLessThan(v2, v1);
}

}
}


/*
 * CustomComparers.cpp
 *
 *  Created on: Jul 22, 2014
 *      Author: cmaier
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


/*
 * ToStringHelper.cpp
 *
 *  Created on: Jul 24, 2014
 *      Author: cmaier
 */
#include "ToStringHelper.h"

namespace yagi {

std::string fluentDBDataToString(std::vector<std::vector<std::string>> data)
{
  std::string str = "{";

  std::for_each(std::begin(data), std::end(data), [&str](const std::vector<std::string>& row)
  {
    str += "<";

    std::for_each(std::begin(row), std::end(row), [&str](const std::string& col)
        {
          str += "\"" + col + "\",";
        });

    str = str.substr(0,str.length()-1);
    str += ">, ";
  });

  if (str.length() > 1)
    return str.substr(0, str.length() - 2) + "}";
  else
    return "[EMPTY]";
}

std::string tupleToString(const std::vector<std::string>& tuple)
{
  std::string ret = "<";
  std::for_each(std::begin(tuple), std::end(tuple), [&ret](const std::string& val)
  {
    ret += "\"" + val + "\", ";
  });

  return ret.substr(0,ret.size() - 2) + ">";
}

}


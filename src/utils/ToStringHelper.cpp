/**
 * @file   ToStringHelper.cpp
 * @author Christopher Maier
 * @date   January 2015
 *
 * Pretty printing helper functions that convert YAGI constructs to printable strings.
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

  return ret.substr(0, ret.size() - 2) + ">";
}

}


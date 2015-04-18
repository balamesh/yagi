/**
 * @file   NumericStringCompare.h
 * @author Christopher Maier (cmaier.business@gmail.com)
 * @date   April 2015
 *
 * Implements special comparison for strings that include/consist of numeric values.
 * Purely lexicographic comparison would lead to unintuitive behavior in some examples
 * like the elevator sample. This method is more intuitive.
 * Taken from http://stackoverflow.com/questions/4622516/sorting-stdstrings-with-numbers-in-them
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


#include <algorithm>
#include <sstream>
#include <string>

namespace yagi {
namespace formula {

/**
 * Check whether or not a char represents a digit
 * @param c The char to check
 * @return True if it's a digit, false otherwise
 */
bool is_not_digit(char c)
{
  return !std::isdigit(c);
}

/**
 * Implements the numerical string comparison
 * @param s1 First string
 * @param s2 Second string
 * @return True if comparison holds, false otherwise
 */
bool numeric_string_compare(const std::string& s1, const std::string& s2)
{
  // handle empty strings...

  std::string::const_iterator it1 = s1.begin(), it2 = s2.begin();

  if (std::isdigit(s1[0]) && std::isdigit(s2[0]))
  {
    int n1, n2;
    std::stringstream ss(s1);
    ss >> n1;
    ss.clear();
    ss.str(s2);
    ss >> n2;

    if (n1 != n2)
      return n1 < n2;

    it1 = std::find_if(s1.begin(), s1.end(), is_not_digit);
    it2 = std::find_if(s2.begin(), s2.end(), is_not_digit);
  }

  return std::lexicographical_compare(it1, s1.end(), it2, s2.end());
}

}
}

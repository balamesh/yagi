/**
 * @file   StringManipulationHelper.h
 * @author Christopher Maier
 * @date   January 2015
 *
 * Basic string trimming functions and other string manipulation helpers.
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


#ifndef STRINGMANIPULATIONHELPER_H_
#define STRINGMANIPULATIONHELPER_H_

#include <algorithm>
#include <functional>
#include <cctype>
#include <locale>

/**
 * Trims the beginning of a string
 * @param s The string to trim
 * @return The trimmed string
 */
static inline std::string &ltrim(std::string &s)
{
  s.erase(s.begin(),
      std::find_if(s.begin(), s.end(), std::not1(std::ptr_fun<int, int>(std::isspace))));
  return s;
}

/**
 * Trims the end of a string.
 * @param s The string to trim.
 * @return The trimmed string.
 */
static inline std::string &rtrim(std::string &s)
{
  s.erase(
      std::find_if(s.rbegin(), s.rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(),
      s.end());
  return s;
}

/**
 * Trims both ends of a string
 * @param s The string to trim.
 * @return The trimmed string.
 */
static inline std::string &trim(std::string &s)
{
  return ltrim(rtrim(s));
}

#endif /* STRINGMANIPULATIONHELPER_H_ */

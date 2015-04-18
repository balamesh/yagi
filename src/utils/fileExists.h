/**
 * @file   fileExists.h
 * @author Christopher Maier
 * @date   January 2015
 *
 * Encapsulates checking whether or not a specific file exists.
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


#ifndef FILEEXISTS_H_
#define FILEEXISTS_H_

/**
 * Checks whether or not a file exists.
 * @param name The name of the file.
 * @return True if the file exists, false otherwise.
 */
inline bool fileExists(const std::string& name)
{
  if (FILE *file = fopen(name.c_str(), "r"))
  {
    fclose(file);
    return true;
  }
  else
  {
    return false;
  }
}

#endif /* FILEEXISTS_H_ */

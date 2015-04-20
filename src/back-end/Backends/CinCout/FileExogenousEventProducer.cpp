/**
 * @file   FileExogenousEventProducer.cpp
 * @author Christopher Maier (cmaier.business@gmail.com)
 * @date   April 2015
 *
 * Implements exogenous events via a simple file watch approach.
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


#include "FileExogenousEventProducer.h"
#include <fstream>
#include <iostream>
#include <string.h>
#include <stdio.h>

#include "../../../utils/fileExists.h"

using std::ifstream;
using std::ofstream;

namespace yagi {
namespace execution {

FileExogenousEventProducer::FileExogenousEventProducer() : file_exists_(false)
{
}

bool FileExogenousEventProducer::eventAvailable()
{
    if(file_exists_)
    {
        if((time_point_file_found_ + std::chrono::milliseconds(250)) < std::chrono::system_clock::now())
        {
            file_exists_ = false;
            return true;
        }
    }
    else if(fileExists(fileName))
    {
        file_exists_ = true;
        time_point_file_found_ = std::chrono::system_clock::now();
    }

    return false;
}

std::vector<std::pair<std::string, std::unordered_map<std::string, std::string> > > FileExogenousEventProducer::getEvent()
{
    auto lines = readLinesFromFile();
    auto values = splitFileLines(lines);

    std::unordered_map<std::string, std::string> variablesAndValues;

    //TODO: we assume we have just data for 1 exo event in the file
    //and all the var names are unique!
    std::string eventName = "<unknown>";
    for (const auto& tuple : values)
    {
      variablesAndValues[std::get<1>(tuple)] = std::get<2>(tuple);
      eventName = std::get<0>(tuple);
    }

    std::vector<std::pair<std::string, std::unordered_map<std::string, std::string> > > result;
    result.push_back(std::pair<std::string, std::unordered_map<std::string, std::string> >(eventName, variablesAndValues));

    return result;
}

std::vector<std::string> FileExogenousEventProducer::readLinesFromFile()
{
  std::vector<std::string> lines;
  std::string line;
  ifstream myfile(fileName);
  if (myfile.is_open())
  {
    while (getline(myfile, line))
    {
      lines.push_back(line);
    }
    myfile.close();

    remove(fileName.c_str());
  }
  else
    std::cout << "Unable to open exo event data file";

  return lines;
}

std::vector<std::tuple<std::string, std::string, std::string>> FileExogenousEventProducer::splitFileLines(
    std::vector<std::string> lines)
{
  std::string delimiter = ";";
  std::vector<std::tuple<std::string, std::string, std::string>> values;

  for (auto line : lines)
  {
    size_t pos = 0;
    std::string token;

    std::vector<std::string> lineValues;
    while ((pos = line.find(delimiter)) != std::string::npos)
    {
      lineValues.push_back(line.substr(0, pos));
      line.erase(0, pos + delimiter.length());
    }

    if (lineValues.size() == 3)
    {
      values.push_back(std::make_tuple(lineValues[0], lineValues[1], lineValues[2]));
    }
    else
    {
      std::cout
          << "[WARNING] Invalid line in exogenous event file! Must have exactly 3 values, ';' separated!"
          << std::endl;
    }
  }

  return values;
}

} /* namespace execution */
} /* namespace yagi */

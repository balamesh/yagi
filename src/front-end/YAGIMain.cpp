/**
 * @file   YAGIMain.cpp
 * @author Christopher Maier (cmaier@student.tugraz.at)
 * @date   January 2015
 *
 * The main entry point of the YAGI interpreter commandline.
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


#include "YAGIInterpreter.h"

#include <iostream>
#include <readline/history.h>
#include <readline/readline.h>
#include <readline/rltypedefs.h>
#include <string>

#include "../back-end/BackendFactory.h"
#include "../utils/CommandLineArgsContainer.h"
#include "astClasses/YAGICallbackConnector.h"

/**
 * Main method of the YAGI interpreter shell
 * @param argc Number of parameters
 * @param argv Parameters
 * @return Success or error
 */
int main(int argc, char * argv[])
{

  try
  {
    YAGIInterpreter::parseCommandLineArgs(argc, argv);
  }
  catch (const std::exception& ex)
  {
    std::cerr << "Can't parse command line args! Error: " + std::string { ex.what() } << std::endl;
    exit(EXIT_FAILURE);
  }

  yagi::execution::BackendFactory::getInstance().initBackend(
      yagi::container::CommandLineArgsContainer::getInstance().getBackendPlugin());

  rl_bind_keyseq("\\C-n", YAGIInterpreter::addMultilineCommand);

  YAGICallbackConnector::connectCallbacks();

  YAGIInterpreter::displayWelcome();

  //if a filename was passed run its content directly
  if (!yagi::container::CommandLineArgsContainer::getInstance().getInputFileName().empty())
  {
    YAGIInterpreter::execute(
        yagi::container::CommandLineArgsContainer::getInstance().getInputFileName(), true);

    if (yagi::container::CommandLineArgsContainer::getInstance().measurePerformance())
    {
      return EXIT_SUCCESS;
    }
  }

  std::string line;

  do
  {
    char* buffer = nullptr;

    buffer = readline("YAGI>> ");

    if (buffer == nullptr)
      break;
    else
    {
      line = std::string(buffer);

      if (YAGIInterpreter::isExit(line))
        break;

      add_history(line.c_str());

      if (YAGIInterpreter::isFromFile(line))
      {
        std::string fname = YAGIInterpreter::parseFileName(line);

        YAGIInterpreter::execute(fname, true);
        continue;
      }

      YAGIInterpreter::execute(line, false);
    }
  }
  while (true);

  return EXIT_SUCCESS;
}

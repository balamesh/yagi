/**
 * @file   UnitTestMain.cpp
 * @author Christopher Maier (cmaier@student.tugraz.at)
 * @date   January 2015
 *
 * This file provides the main function that executes all unit tests.
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


#include "../../gtest_src/include/gtest/gtest.h"
#include "../front-end/astClasses/YAGICallbackConnector.h"
#include "../back-end/BackendFactory.h"

/**
 * Initializes gtest stuff and runs unit tests
 * @param argc Number of arguments
 * @param argv arguments
 * @return Returns 0 if tests succeed, return code otherwise
 */
int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);

  //Init YAGI parsing stuff
  YAGICallbackConnector::connectCallbacks();

  yagi::execution::BackendFactory::getInstance().initBackend("CinCoutBackend");

  return RUN_ALL_TESTS();
}

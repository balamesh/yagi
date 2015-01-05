/**
 * @file   UnitTestMain.cpp
 * @author Christopher Maier (cmaier@student.tugraz.at)
 * @date   January 2015
 *
 * This file provides the main function that executes all unit tests.
 */

#include "../../gtest_src/include/gtest/gtest.h"
#include "../front-end/astClasses/YAGICallbackConnector.h"

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

  return RUN_ALL_TESTS();
}

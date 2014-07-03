/*
 * UnitTestMain.cpp
 *
 *  Created on: Jul 1, 2014
 *      Author: cmaier
 */
#include "../../gtest_src/include/gtest/gtest.h"
#include "../front-end/astClasses/YAGICallbackConnector.h"

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);

  //Init YAGI parsing stuff
  YAGICallbackConnector::connectCallbacks();

  return RUN_ALL_TESTS();
}

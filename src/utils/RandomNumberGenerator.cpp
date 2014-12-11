/*
 * RandomNumberGenerator.cpp
 *
 *  Created on: Jul 30, 2014
 *      Author: cmaier
 */
#include "RandomNumberGenerator.h"
#include <chrono>

namespace yagi {

RandomNumberGenerator::RandomNumberGenerator()
{
  initialize();
}
void RandomNumberGenerator::initialize()
{
  auto seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
  rng.seed(seed);
}

int RandomNumberGenerator::getRandomNumber(int lowerBound, int upperBound)
{
  std::uniform_int_distribution<uint32_t> uniformDist(lowerBound, upperBound);
  return uniformDist(rng);
}

}


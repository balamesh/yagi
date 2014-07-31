/*
 * RandomNumberGenerator.cpp
 *
 *  Created on: Jul 30, 2014
 *      Author: cmaier
 */
#include "RandomNumberGenerator.h"

namespace yagi {

RandomNumberGenerator::RandomNumberGenerator()
{
  initialize();
}
void RandomNumberGenerator::initialize()
{
  rng.seed(yagi::getNowTicks()); //Not cryptographcially secure, but good enough for us...
}

int RandomNumberGenerator::getRandomNumber(int lowerBound, int upperBound)
{
  std::uniform_int_distribution<uint32_t> uniformDist(lowerBound, upperBound);
  return uniformDist(rng);
}

}


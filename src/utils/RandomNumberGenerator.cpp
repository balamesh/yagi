/**
 * @file   RandomNumberGenerator.cpp
 * @author Christopher Maier
 * @date   January 2015
 *
 * Encapsulates generation of uniformly distributed random numbers.
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


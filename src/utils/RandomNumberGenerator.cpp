/**
 * @file   RandomNumberGenerator.cpp
 * @author Christopher Maier
 * @date   January 2015
 *
 * Encapsulates generation of uniformly distributed random numbers.
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


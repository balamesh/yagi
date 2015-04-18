/**
 * @file   RandomNumberGenerator.h
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


#ifndef RANDOMNUMBERGENERATOR_H_
#define RANDOMNUMBERGENERATOR_H_

#include <random>
#include "DateTimeHelper.h"

namespace yagi {

/**
 * Encapsulates generation of uniformly distributed random numbers.
 * Inspired by http://stackoverflow.com/questions/7114043/random-number-generation-in-c11-how-to-generate-how-do-they-work
 */
class RandomNumberGenerator
{
  private:
    /**
     * Mersenne-Twister RNG type
     */
    typedef std::mt19937 RNG;

    /**
     * The RNG
     */
    RNG rng;

    /**
     * Initializes the RNG.
     */
    void initialize();
  public:
    /**
     * Default ctor
     */
    RandomNumberGenerator();

    /**
     * Generate a random number
     * @param lowerBound Lower bound of the generated random number.
     * @param upperBound Upper bound of the generated random number.
     * @return The random number.
     */
    int getRandomNumber(int lowerBound, int upperBound);

};

}
#endif /* RANDOMNUMBERGENERATOR_H_ */

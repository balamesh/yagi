/*
 * RandomNumberGenerator.h
 *
 *  Created on: Jul 30, 2014
 *      Author: cmaier
 */

#ifndef RANDOMNUMBERGENERATOR_H_
#define RANDOMNUMBERGENERATOR_H_

#include <random>
#include "DateTimeHelper.h"

namespace yagi {

//inspired by //from http://stackoverflow.com/questions/7114043/random-number-generation-in-c11-how-to-generate-how-do-they-work
class RandomNumberGenerator
{
  private:
    typedef std::mt19937 RNG;
    RNG rng;

    void initialize();
  public:
    RandomNumberGenerator();
    int getRandomNumber(int lowerBound, int upperBound);

};

}
#endif /* RANDOMNUMBERGENERATOR_H_ */

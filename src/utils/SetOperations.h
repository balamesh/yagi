/*
 * SetOperations.h
 *
 *  Created on: Jul 23, 2014
 *      Author: cmaier
 */

#ifndef SETOPERATIONS_H_
#define SETOPERATIONS_H_

#include <vector>
#include <string>
#include <algorithm>
#include "CustomComparers.h"

namespace yagi {
namespace operations {

std::vector<std::vector<std::string>> buildUnion(std::vector<std::vector<std::string>> v1,
    std::vector<std::vector<std::string>> v2);
std::vector<std::vector<std::string>> buildComplement(std::vector<std::vector<std::string>> v1,
    std::vector<std::vector<std::string>> v2);

}
}

#endif /* SETOPERATIONS_H_ */

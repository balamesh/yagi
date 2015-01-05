/**
 * @file   SetOperations.h
 * @author Christopher Maier
 * @date   January 2015
 *
 * Mathematical set operations for YAGI sets.
 */

#ifndef SETOPERATIONS_H_
#define SETOPERATIONS_H_

#include <vector>
#include <string>
#include <algorithm>
#include "CustomComparers.h"

namespace yagi {
namespace operations {

/**
 * Returns a union of 2 YAGI sets
 */
std::vector<std::vector<std::string>> buildUnion(std::vector<std::vector<std::string>> v1,
    std::vector<std::vector<std::string>> v2);

/**
 * Returns a complement of 2 YAGI sets
 */
std::vector<std::vector<std::string>> buildComplement(std::vector<std::vector<std::string>> v1,
    std::vector<std::vector<std::string>> v2);

}
}

#endif /* SETOPERATIONS_H_ */

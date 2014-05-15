/*
 * ASTNodeBase.h
 *
 *  Created on: Apr 24, 2014
 *      Author: cmaier
 */

#ifndef ASTNODEBASE_H_
#define ASTNODEBASE_H_

#include <string>
#include <stdexcept>

class ASTNodeBase {
public:
	ASTNodeBase();
	virtual ~ASTNodeBase();

	virtual std::string toString() = 0; //{throw std::logic_error("never instantiate this!");};
};

#endif /* ASTNODEBASE_H_ */

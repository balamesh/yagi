/*
 * NodeIDSet.h
 *
 *  Created on: Apr 24, 2014
 *      Author: cmaier
 */

#ifndef NODEIDSET_H_
#define NODEIDSET_H_

#include<vector>


#include "ASTNodeBase.h"
#include "NodeID.h"

class NodeIDSet: public ASTNodeBase
{
private:
	std::vector<NodeID*> idNodes_;

public:
	NodeIDSet() {}

	void addID(NodeID* idNode) {idNodes_.push_back(idNode); }

	virtual ~NodeIDSet();
	virtual std::string toString()
	{
		std::string ret{"{"};

		bool first = true;
		for (const auto& id : idNodes_)
		{
			if (!first) ret += "," + id->toString();
			else
			{
				ret += id->toString();
				first = false;
			}
		}

		return ret += "}";
	}
};

#endif /* NODEIDSET_H_ */

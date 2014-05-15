/*
 * NodeFluentDecl.h
 *
 *  Created on: Apr 24, 2014
 *      Author: cmaier
 */

#ifndef NODEFLUENTDECL_H_
#define NODEFLUENTDECL_H_

#include <string>

#include "ASTNodeBase.h"
#include "NodeID.h"
#include "NodeIDSet.h"

class NodeFluentDecl: public ASTNodeBase {

private:
	NodeID* fluentName_;
	NodeIDSet* domain_;

public:
	NodeFluentDecl();
	virtual ~NodeFluentDecl();

	void setFluentName(NodeID* fluentName) {
		fluentName_ = fluentName;
	}
	void setDomain(NodeIDSet* domain) {
		domain_ = domain;
	}

	virtual std::string toString() {
		return std::string(
				std::string("Fluent '") + fluentName_->toString() + "' Domain: "
						+ domain_->toString());
	}

};

#endif /* NODEFLUENTDECL_H_ */

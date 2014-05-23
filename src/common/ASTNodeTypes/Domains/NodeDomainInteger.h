/*
 * NodeDomainInteger.h
 *
 *  Created on: May 22, 2014
 *      Author: cmaier
 */

#ifndef NODEDOMAININTEGER_H_
#define NODEDOMAININTEGER_H_

#include "NodeDomainBase.h"

class NodeDomainInteger: public NodeDomainBase
{
  public:
    NodeDomainInteger();
    virtual ~NodeDomainInteger();

    virtual void accept(ASTNodeVisitorBase* visitor) override
    {
      visitor->visit(this);
    }
};

#endif /* NODEDOMAININTEGER_H_ */

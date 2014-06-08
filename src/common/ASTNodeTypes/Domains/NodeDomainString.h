/*
 * NodeDomainString.h
 *
 *  Created on: May 22, 2014
 *      Author: cmaier
 */

#ifndef NODEDOMAINSTRING_H_
#define NODEDOMAINSTRING_H_

#include "NodeDomainBase.h"

class NodeDomainString: public NodeDomainBase
{
  public:
    DEFINE_VISITABLE()
    NodeDomainString();
    virtual ~NodeDomainString();

//    virtual void accept(ASTNodeVisitorBase* visitor) override
//    {
//      visitor->visit(this);
//    }
};

#endif /* NODEDOMAINSTRING_H_ */

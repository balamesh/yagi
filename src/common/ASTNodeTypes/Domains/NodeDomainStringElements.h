/*
 * NodeIDSet.h
 *
 *  Created on: Apr 24, 2014
 *      Author: cmaier
 */

#ifndef NODEDOMAINSTRINGELEMENTS_H_
#define NODEDOMAINSTRINGELEMENTS_H_

#include<vector>
#include<algorithm>
#include <memory>

#include "../Identifier/NodeID.h"
#include "../DataTypes/NodeString.h"
#include "../Domains/NodeDomainBase.h"

class NodeDomainStringElements: public NodeDomainBase
{
  private:
    std::vector<std::shared_ptr<NodeString>> domainElements_;

  public:
    DEFINE_VISITABLE()
    NodeDomainStringElements()
    {
    }
    virtual ~NodeDomainStringElements();

    void addStringToDomain(std::shared_ptr<NodeString> domainElement)
    {
      domainElements_.push_back(domainElement);
    }

//    virtual void accept(ASTNodeVisitorBase* visitor) override
//    {
//      std::for_each(std::begin(domainElements_), std::end(domainElements_),
//          [&visitor](std::shared_ptr<NodeString> str)
//          { str->accept(visitor);});
//
//      visitor->visit(this);
//    }

    const std::vector<std::shared_ptr<NodeString> >& getDomainElements() const
    {
      return domainElements_;
    }
};

#endif /* NODEDOMAINSTRINGELEMENTS_H_ */

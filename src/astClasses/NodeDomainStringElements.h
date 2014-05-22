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

#include "ASTNodeBase.h"
#include "NodeID.h"
#include "NodeString.h"

class NodeDomainStringElements: public ASTNodeBase
{
  private:
    std::vector<std::shared_ptr<NodeString>> domainElements_;

  public:
    NodeDomainStringElements()
    {
    }
    virtual ~NodeDomainStringElements();

    //std::vector<std::string> getDomainElements() {return domainElements_;};

    void addStringToDomain(std::shared_ptr<NodeString> domainElement)
    {
      domainElements_.push_back(domainElement);
    }

    virtual void accept(ASTNodeVisitorBase* visitor) override
    {
      std::for_each(std::begin(domainElements_), std::end(domainElements_),
          [&visitor](std::shared_ptr<NodeString> str)
          { str->accept(visitor);});

      visitor->visit(this);
    }
};

#endif /* NODEDOMAINSTRINGELEMENTS_H_ */

/*
 * NodeFactDecl.h
 *
 *  Created on: May 23, 2014
 *      Author: cmaier
 */

#ifndef NODEFACTDECL_H_
#define NODEFACTDECL_H_

#include <string>
#include <memory>
#include <vector>
#include <algorithm>

#include "../../ASTNodeBase.h"
#include "../../Identifier/NodeID.h"
#include "../../Domains/NodeDomainBase.h"

class NodeFactDecl: public ASTNodeBase
{

  private:
    std::shared_ptr<NodeID> factName_;
    std::vector<std::shared_ptr<NodeDomainBase>> domains_;

  public:
    NodeFactDecl();
    virtual ~NodeFactDecl();

    void setFactName(std::shared_ptr<NodeID> factName)
    {
      factName_ = factName;
    }

    void addDomain(std::shared_ptr<NodeDomainBase> domain)
    {
      domains_.push_back(domain);
    }

    virtual void accept(ASTNodeVisitorBase* visitor) override
    {
      visitor->visit(this);

      factName_->accept(visitor);

      std::for_each(std::begin(domains_), std::end(domains_),
          [&visitor](std::shared_ptr<NodeDomainBase> domain)
          {
            domain->accept(visitor);
          });
    }
};

#endif /* NODEFACTDECL_H_ */

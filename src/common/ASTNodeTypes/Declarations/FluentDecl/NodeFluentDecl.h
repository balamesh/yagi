/*
 * NodeFluentDecl.h
 *
 *  Created on: Apr 24, 2014
 *      Author: cmaier
 */

#ifndef NODEFLUENTDECL_H_
#define NODEFLUENTDECL_H_

#include <string>
#include <memory>
#include <vector>
#include <algorithm>

#include "../../ASTNodeBase.h"
#include "../../Identifier/NodeID.h"
#include "../../Domains/NodeDomainBase.h"

class NodeFluentDecl: public ASTNodeBase
{

  private:
    std::shared_ptr<NodeID> fluentName_;
    std::vector<std::shared_ptr<NodeDomainBase>> domains_;

  public:
    NodeFluentDecl();
    virtual ~NodeFluentDecl();

    void addDomain(std::shared_ptr<NodeDomainBase> domain)
    {
      domains_.push_back(domain);
    }

    virtual void accept(ASTNodeVisitorBase* visitor) override
    {
      fluentName_->accept(visitor);

      std::for_each(std::begin(domains_), std::end(domains_),
          [&visitor](std::shared_ptr<NodeDomainBase> domain)
          {
            domain->accept(visitor);
          });

      visitor->visit(this);
    }

    const std::vector<std::shared_ptr<NodeDomainBase> >& getDomains() const
    {
      return domains_;
    }

    const std::shared_ptr<NodeID>& getFluentName() const
    {
      return fluentName_;
    }

    void setFluentName(const std::shared_ptr<NodeID>& fluentName)
    {
      fluentName_ = fluentName;
    }
};

#endif /* NODEFLUENTDECL_H_ */

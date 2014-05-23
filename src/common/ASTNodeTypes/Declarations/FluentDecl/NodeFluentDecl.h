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

    void setFluentName(std::shared_ptr<NodeID> fluentName)
    {
      fluentName_ = fluentName;
    }

    void addDomain(std::shared_ptr<NodeDomainBase> domain)
    {
      domains_.push_back(domain);
    }

    virtual void accept(ASTNodeVisitorBase* visitor) override
    {
      visitor->visit(this);

      fluentName_->accept(visitor);

      std::for_each(std::begin(domains_), std::end(domains_),
          [&visitor](std::shared_ptr<NodeDomainBase> domain)
          {
            domain->accept(visitor);
          });
    }
};

#endif /* NODEFLUENTDECL_H_ */

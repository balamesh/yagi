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

#include "ASTNodeBase.h"
#include "NodeID.h"
#include "NodeDomainStringElements.h"

class NodeFluentDecl: public ASTNodeBase
{

  private:
    std::shared_ptr<NodeID> fluentName_;
    std::shared_ptr<NodeDomainStringElements> domain_;

  public:
    NodeFluentDecl();
    virtual ~NodeFluentDecl();

    void setFluentName(std::shared_ptr<NodeID> fluentName)
    {
      fluentName_ = fluentName;
    }
    void setDomain(std::shared_ptr<NodeDomainStringElements> domain)
    {
      domain_ = domain;
    }

    virtual void accept(ASTNodeVisitorBase* visitor) override
    {
fluentName_->accept(visitor);
domain_->accept(visitor);
      //visitor->visit(fluentName_.get());
      //visitor->visit(domain_.get());

      visitor->visit(this);
    }
};

#endif /* NODEFLUENTDECL_H_ */

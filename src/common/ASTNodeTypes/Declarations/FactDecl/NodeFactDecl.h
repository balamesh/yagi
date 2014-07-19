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

class NodeFactDecl: public ASTNodeBase<>
{

  private:
    std::shared_ptr<NodeID> factName_;
    std::vector<std::shared_ptr<NodeDomainBase>> domains_;

  public:
    DEFINE_VISITABLE()
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

    const std::vector<std::shared_ptr<NodeDomainBase> >& getDomains() const
    {
      return domains_;
    }

    const std::shared_ptr<NodeID>& getFactName() const
    {
      return factName_;
    }
};

#endif /* NODEFACTDECL_H_ */

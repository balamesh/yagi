/**
 * @file   NodeFactDecl.h
 * @author Christopher Maier (cmaier.business@gmail.com)
 * @date   April 2015
 *
 * AST node for fact declarations.
 */

/*
 This file is part of YAGI.

 YAGI is free software; you can redistribute it and/or
 modify it under the terms of the GNU Lesser General Public
 License as published by the Free Software Foundation; either
 version 3.0 of the License, or (at your option) any later version.

 YAGI is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 Lesser General Public License for more details.

 You should have received a copy of the GNU Lesser General Public
 License along with YAGI.
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

/**
 * AST node class for fact declarations
 */
class NodeFactDecl: public ASTNodeBase<>
{

  private:
    /**
     * Name of the fact
     */
    std::shared_ptr<NodeID> factName_;

    /**
     * Domains of the fact
     */
    std::vector<std::shared_ptr<NodeDomainBase>> domains_;

  public:
    DEFINE_VISITABLE()

    /**
     * Default ctor
     */
    NodeFactDecl();

    /**
     * Default dtor
     */
    virtual ~NodeFactDecl();

    /**
     * Setter for fact name
     * @param factName The fact name AST node
     */
    void setFactName(std::shared_ptr<NodeID> factName)
    {
      factName_ = factName;
    }

    /**
     * Adds domain to domains of the fact
     * @param domain Domain node to add
     */
    void addDomain(std::shared_ptr<NodeDomainBase> domain)
    {
      domains_.push_back(domain);
    }

    /**
     * Getter for the domains of the fact
     * @return The domains of the fact
     */
    const std::vector<std::shared_ptr<NodeDomainBase> >& getDomains() const
    {
      return domains_;
    }

    /**
     * Getter for the fact name
     * @return The name of the fact
     */
    const std::shared_ptr<NodeID>& getFactName() const
    {
      return factName_;
    }
};

#endif /* NODEFACTDECL_H_ */

/**
 * @file   NodeDomainStringElements.h
 * @author Christopher Maier (cmaier.business@gmail.com)
 * @date   April 2015
 *
 * AST node for the domain of finite number of string elements
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


#ifndef NODEDOMAINSTRINGELEMENTS_H_
#define NODEDOMAINSTRINGELEMENTS_H_

#include<vector>
#include<algorithm>
#include <memory>

#include "../Identifier/NodeID.h"
#include "../DataTypes/NodeString.h"
#include "../Domains/NodeDomainBase.h"

/**
 * AST node class for the domain of finite number of string elements
 */
class NodeDomainStringElements: public NodeDomainBase
{
  private:
    /**
     * List of domain elements
     */
    std::vector<std::shared_ptr<NodeString>> domainElements_;

  public:
    DEFINE_VISITABLE()

    /**
     * Default ctor
     */
    NodeDomainStringElements()
    {
    }

    /**
     * Default dtor
     */
    virtual ~NodeDomainStringElements();

    /**
     * Adds string element to domain
     * @param domainElement The element to add
     */
    void addStringToDomain(std::shared_ptr<NodeString> domainElement)
    {
      domainElements_.push_back(domainElement);
    }

    /**
     * Getter for domain elements
     * @return Returns the domain elements
     */
    const std::vector<std::shared_ptr<NodeString> >& getDomainElements() const
    {
      return domainElements_;
    }
};

#endif /* NODEDOMAINSTRINGELEMENTS_H_ */

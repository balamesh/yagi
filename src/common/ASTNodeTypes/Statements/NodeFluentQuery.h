/**
 * @file   NodeFluentQuery.h
 * @author Christopher Maier (cmaier.business@gmail.com)
 * @date   April 2015
 *
 * AST node for a fluent query
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


#ifndef NODEFLUENTQUERY_H_
#define NODEFLUENTQUERY_H_

#include <memory>

#include "NodeStatementBase.h"
#include "../Identifier/NodeID.h"

/**
 * AST node class for a fluent query
 */
class NodeFluentQuery: public NodeStatementBase
{
  private:

    /**
     * The name of the fluent to be queried
     */
    std::shared_ptr<NodeID> fluentToQueryName_;

  public:
    DEFINE_VISITABLE()

    /**
     * Default ctor
     */
    NodeFluentQuery();

    /**
     * Default dtor
     */
    virtual ~NodeFluentQuery();

    /**
     * Getter for the name of the fluent to be queried
     * @return The ID of the fluent
     */
    const std::shared_ptr<NodeID>& getFluentToQueryName() const
    {
      return fluentToQueryName_;
    }

    /**
     * Setter for the name of the fluent to be queried
     * @param fluentToQueryName The ID of the fluent
     */
    void setFluentToQueryName(const std::shared_ptr<NodeID>& fluentToQueryName)
    {
      fluentToQueryName_ = fluentToQueryName;
    }
};

#endif /* NODEFLUENTQUERY_H_ */

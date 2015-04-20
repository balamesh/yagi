/**
 * @file   NodeID.h
 * @author Christopher Maier (cmaier.business@gmail.com)
 * @date   April 2015
 *
 * AST node for identifiers
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


#ifndef NODEID_H_
#define NODEID_H_

#include "../ASTNodeBase.h"
#include <string>

/**
 * AST node class for identifiers
 */
class NodeID: public ASTNodeBase<>
{
  private:

    /**
     * The name of the identifier
     */
    std::string id_;

  public:
    DEFINE_VISITABLE()

    /**
     * ctor
     */
    NodeID(const std::string& id);

    /**
     * Default dtor
     */
    virtual ~NodeID();

    /**
     * Getter for the identifier
     * @return The name of the identifier
     */
    const std::string& getId() const
    {
      return id_;
    }
};

#endif /* NODEID_H_ */

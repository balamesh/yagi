/**
 * @file   ASTNodeVisitorBase.h
 * @author Christopher Maier (cmaier@student.tugraz.at)
 * @date   January 2015
 *
 * Alexandrescu's implementation of the visitor pattern from
 * Modern C++ Design: Generic Programming and Design Patterns Applied book.
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


#ifndef ASTNODEVISITORBASE_H_
#define ASTNODEVISITORBASE_H_

#include <string>
#include "../utils/Any.h"

using namespace yagi::container;

/**
 * Visitor base class.
 */
class ASTNodeVisitorBase
{
  public:
    /**
     * Default dtor
     */
    virtual ~ASTNodeVisitorBase()
    {
    }
    ;
};

/**
 * Visitor class
 */
template<class T, typename R = Any>
class Visitor
{
  public:
    typedef R ReturnType; // Available for clients

    /**
     * visit method for visitor pattern
     * @param Type to visit
     * @return Any container of whatever the concrete visitor returns.
     */
    virtual ReturnType visit(T&) = 0;

    /**
     * Default dtor
     */
    virtual ~Visitor()
    {
    }
    ;
};

#endif /* ASTNODEVISITORBASE_H_ */

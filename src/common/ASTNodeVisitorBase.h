/**
 * @file   ASTNodeVisitorBase.h
 * @author Christopher Maier (cmaier@student.tugraz.at)
 * @date   January 2015
 *
 * Alexandrescu's implementation of the visitor pattern from
 * Modern C++ Design: Generic Programming and Design Patterns Applied book.
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

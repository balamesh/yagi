/*
 * ASTNodeVisitorBase.h
 *
 *  Created on: May 22, 2014
 *      Author: cmaier
 */
//Alexandrescu's implementation of the visitor pattern

#ifndef ASTNODEVISITORBASE_H_
#define ASTNODEVISITORBASE_H_

#include <string>
#include "../utils/Any.h"

using namespace yagi::container;

class ASTNodeVisitorBase
{
  public:
    virtual ~ASTNodeVisitorBase()
    {
    }
    ;
};

template<class T, typename R = Any>
class Visitor
{
  public:
    typedef R ReturnType; // Available for clients
    virtual ReturnType visit(T&) = 0;
    virtual ~Visitor() {};
};

#endif /* ASTNODEVISITORBASE_H_ */

/*
 * ASTNodeBase.h
 *
 *  Created on: Apr 24, 2014
 *      Author: cmaier
 */
//Alexandrescu's implementation of the visitor pattern
#ifndef ASTNODEBASE_H_
#define ASTNODEBASE_H_

#include "../../common/ASTNodeVisitorBase.h"

template<class R, class Visited>
struct DefaultCatchAll
{
    static R OnUnknownVisitor(Visited& node, ASTNodeVisitorBase& visitor)
    {
      return R();
    }
};

template<typename R = void, template<typename, class > class CatchAll = DefaultCatchAll>
class ASTNodeBase
{
  public:
    typedef R ReturnType;
    virtual ~ASTNodeBase()
    {
    }
    ;
    virtual R accept(ASTNodeVisitorBase &) = 0;
  protected:
    template<class T>
    static ReturnType acceptImpl(T& visited, ASTNodeVisitorBase& guest)
    {
      // Apply the Acyclic Visitor
      if (Visitor<T>* p = dynamic_cast<Visitor<T>*>(&guest))
      {
        return p->visit(visited);
      }
      return CatchAll<R, T>::OnUnknownVisitor(visited, guest);
    }
};

#define DEFINE_VISITABLE() \
virtual ReturnType accept(ASTNodeVisitorBase& guest) \
{  return acceptImpl(*this, guest); }

#endif /* ASTNODEBASE_H_ */

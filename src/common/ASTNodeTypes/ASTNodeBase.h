/**
 * @file   ASTNodeBase.h
 * @author Christopher Maier (cmaier.business@gmail.com)
 * @date   April 2015
 *
 * AST node base class based on Alexandrescu's implementation of the visitor pattern from
 * Modern C++ Design: Generic Programming and Design Patterns Applied book.
 */

#ifndef ASTNODEBASE_H_
#define ASTNODEBASE_H_

#include "../../common/ASTNodeVisitorBase.h"
#include <mutex>

using namespace yagi::container;

/**
 * Catch-all implementation for everything that is not specifically implemented
 */
template<class R, class Visited>
struct DefaultCatchAll
{
    /**
     * For everything unknown do nothing
     * @param node The visited node
     * @param visitor The concrete visitor
     * @return default
     */
    static R OnUnknownVisitor(Visited& node, ASTNodeVisitorBase& visitor)
    {
      return R();
    }
};

/**
 * The ASTNode base class according to Alexandrescu's implementation of the visitor pattern from
 * Modern C++ Design: Generic Programming and Design Patterns Applied book.
 */
template<typename R = Any, template<typename, class > class CatchAll = DefaultCatchAll>
class ASTNodeBase
{
  public:
    typedef R ReturnType;
    virtual ~ASTNodeBase()
    {
    }

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

/**
 * @file   NodeDomainString.h
 * @author Christopher Maier (cmaier.business@gmail.com)
 * @date   April 2015
 *
 * AST node for the domain of string (Kleene closure over alphabet, potentially countably infinite)
 */

#ifndef NODEDOMAINSTRING_H_
#define NODEDOMAINSTRING_H_

#include "NodeDomainBase.h"

/**
 * AST node class for the domain of string
 */
class NodeDomainString: public NodeDomainBase
{
  public:
    DEFINE_VISITABLE()

    /**
     * Default ctor
     */
    NodeDomainString();

    /**
     * Default dtor
     */
    virtual ~NodeDomainString();
};

#endif /* NODEDOMAINSTRING_H_ */

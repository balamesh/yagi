/**
 * @file   NodeID.h
 * @author Christopher Maier (cmaier.business@gmail.com)
 * @date   April 2015
 *
 * AST node for identifiers
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

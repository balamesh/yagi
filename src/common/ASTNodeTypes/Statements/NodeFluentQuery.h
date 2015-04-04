/**
 * @file   NodeFluentQuery.h
 * @author Christopher Maier (cmaier.business@gmail.com)
 * @date   April 2015
 *
 * AST node for a fluent query
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

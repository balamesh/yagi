/*
 * NodeFluentQuery.h
 *
 *  Created on: Jul 7, 2014
 *      Author: cmaier
 */

#ifndef NODEFLUENTQUERY_H_
#define NODEFLUENTQUERY_H_

#include <memory>

#include "NodeStatementBase.h"
#include "../Identifier/NodeID.h"

class NodeFluentQuery: public NodeStatementBase
{
  private:
    std::shared_ptr<NodeID> fluentToQueryName_;

  public:
    DEFINE_VISITABLE()
    NodeFluentQuery();
    virtual ~NodeFluentQuery();

    const std::shared_ptr<NodeID>& getFluentToQueryName() const
    {
      return fluentToQueryName_;
    }

    void setFluentToQueryName(const std::shared_ptr<NodeID>& fluentToQueryName)
    {
      fluentToQueryName_ = fluentToQueryName;
    }
};

#endif /* NODEFLUENTQUERY_H_ */

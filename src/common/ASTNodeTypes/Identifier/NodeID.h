/*
 * NodeID.h
 *
 *  Created on: Apr 24, 2014
 *      Author: cmaier
 */

#ifndef NODEID_H_
#define NODEID_H_

#include "../ASTNodeBase.h"
#include <string>

class NodeID: public ASTNodeBase<>
{
  private:
    std::string id_;

  public:
    DEFINE_VISITABLE()
    NodeID(const std::string& id) :
        id_(id)
    {
    }
    virtual ~NodeID();

//    virtual void accept(ASTNodeVisitorBase* visitor) override
//    {
//      visitor->visit(this);
//    }

    const std::string& getId() const
    {
      return id_;
    }
};

#endif /* NODEID_H_ */

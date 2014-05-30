/*
 * NodeSignal.h
 *
 *  Created on: May 23, 2014
 *      Author: cmaier
 */

#ifndef NODESIGNAL_H_
#define NODESIGNAL_H_

#include <string>
#include <memory>

#include "../../ASTNodeBase.h"

class NodeSignal: public ASTNodeBase
{
  private:
    std::shared_ptr<ASTNodeBase> signalData_;
  public:
    NodeSignal();
    NodeSignal(const std::shared_ptr<ASTNodeBase>& signalExpr) :
        signalData_(signalExpr)
    {
    }

    virtual ~NodeSignal();

    const std::shared_ptr<ASTNodeBase>& getSignalData() const
    {
      return signalData_;
    }

    void setSignalData(const std::shared_ptr<ASTNodeBase>& signalData)
    {
      signalData_ = signalData;
    }

    virtual void accept(ASTNodeVisitorBase* visitor) override
    {
      visitor->visit(this);

      signalData_->accept(visitor);
    }
};

#endif /* NODESIGNAL_H_ */

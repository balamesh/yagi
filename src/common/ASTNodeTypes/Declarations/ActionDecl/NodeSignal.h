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
#include "../../Expressions/NodeValueExpression.h"

class NodeSignal: public ASTNodeBase<>
{
  private:
    std::shared_ptr<NodeValueExpression> signalData_;
  public:
    DEFINE_VISITABLE()
    NodeSignal();
    NodeSignal(const std::shared_ptr<NodeValueExpression>& signalExpr);

    virtual ~NodeSignal();

    const std::shared_ptr<NodeValueExpression>& getSignalData() const
    {
      return signalData_;
    }

    void setSignalData(const std::shared_ptr<NodeValueExpression>& signalData)
    {
      signalData_ = signalData;
    }
};

#endif /* NODESIGNAL_H_ */

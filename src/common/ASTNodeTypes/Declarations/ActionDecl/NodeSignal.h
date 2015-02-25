/**
 * @file   NodeSignal.h
 * @author Christopher Maier (cmaier@student.tugraz.at)
 * @date   January 2015
 *
 * AST node for action signal.
 */

#ifndef NODESIGNAL_H_
#define NODESIGNAL_H_

#include <string>
#include <memory>

#include "../../ASTNodeBase.h"
#include "../../Expressions/NodeValueExpression.h"

/**
 * AST node class for action signal.
 */
class NodeSignal: public ASTNodeBase<>
{
  private:
    /**
     * The signal expression
     */
    std::shared_ptr<NodeValueExpression> signalData_;
  public:
    DEFINE_VISITABLE()

    /**
     * Default ctor
     */
    NodeSignal();

    /**
     * Ctor with signal expression
     * @param signalExpr The signal expression node
     */
    NodeSignal(const std::shared_ptr<NodeValueExpression>& signalExpr);

    /**
     * Default dtor
     */
    virtual ~NodeSignal();

    /**
     * Getter for the signal expression
     * @return The signal expression node
     */
    const std::shared_ptr<NodeValueExpression>& getSignalData() const
    {
      return signalData_;
    }

    /**
     * Setter for the signal expression
     * @param signalData The signal expression node
     */
    void setSignalData(const std::shared_ptr<NodeValueExpression>& signalData)
    {
      signalData_ = signalData;
    }
};

#endif /* NODESIGNAL_H_ */

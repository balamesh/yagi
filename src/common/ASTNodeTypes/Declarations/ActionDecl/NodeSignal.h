/**
 * @file   NodeSignal.h
 * @author Christopher Maier (cmaier@student.tugraz.at)
 * @date   January 2015
 *
 * AST node for action signal.
 */

/*
 This file is part of YAGI.

 YAGI is free software; you can redistribute it and/or
 modify it under the terms of the GNU Lesser General Public
 License as published by the Free Software Foundation; either
 version 3.0 of the License, or (at your option) any later version.

 YAGI is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 Lesser General Public License for more details.

 You should have received a copy of the GNU Lesser General Public
 License along with YAGI.
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

/*
 * NodeInteger.h
 *
 *  Created on: May 26, 2014
 *      Author: cmaier
 */

#ifndef NODEINTEGER_H_
#define NODEINTEGER_H_

#include <string>

#include "../ASTNodeBase.h"

class NodeInteger: public ASTNodeBase<>
{
  private:
    int value_;

  public:
    DEFINE_VISITABLE()
    NodeInteger();
    virtual ~NodeInteger();

    int getValue() const
    {
      return value_;
    }

    void setValue(int value)
    {
      value_ = value;
    }

    void setValueFromString(std::string val)
    {
      value_ = std::stoi(val);
    }
};

#endif /* NODEINTEGER_H_ */

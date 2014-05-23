/*
 * InterpretationVisitor.h
 *
 *  Created on: May 23, 2014
 *      Author: cmaier
 */

#ifndef INTERPRETATIONVISITOR_H_
#define INTERPRETATIONVISITOR_H_

#include "../common/ASTNodeVisitorBase.h"

class InterpretationVisitor: public ASTNodeVisitorBase
{
  public:
    InterpretationVisitor();
    virtual ~InterpretationVisitor();
};

#endif /* INTERPRETATIONVISITOR_H_ */

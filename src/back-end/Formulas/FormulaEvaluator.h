/*
 * FormulaEvaluator.h
 *
 *  Created on: Jul 17, 2014
 *      Author: cmaier
 */

#ifndef FORMULAEVALUATOR_H_
#define FORMULAEVALUATOR_H_

#include <iostream>

#include "IFormulaEvaluator.h"


namespace yagi {
namespace formula {

class FormulaEvaluator : public IFormulaEvaluator
{
  public:
    FormulaEvaluator();
    virtual ~FormulaEvaluator();

    virtual bool evaluateConstant(NodeConstant* constant) override;
    virtual bool evaluateAtom(NodeAtom* atom) override;
};

} /* namespace formula */
} /* namespace yagi */

#endif /* FORMULAEVALUATOR_H_ */

/*
 * IFormulaEvaluator.h
 *
 *  Created on: Jul 17, 2014
 *      Author: cmaier
 */

#ifndef IFORMULAEVALUATOR_H_
#define IFORMULAEVALUATOR_H_

#include "../common/ASTNodeTypes/Formula/NodeConstant.h"
#include "../common/ASTNodeTypes/Formula/NodeAtom.h"
#include <memory>

namespace yagi {
namespace formula {

class IFormulaEvaluator
{
  protected:
    bool printFormulaEvaluationResults_;

  public:
    IFormulaEvaluator();
    virtual ~IFormulaEvaluator();

    virtual bool evaluateConstant(NodeConstant* constant) = 0;
    virtual bool evaluateAtom(NodeAtom* atom) = 0;
};

} /* namespace formula */
} /* namespace yagi */

#endif /* IFORMULAEVALUATOR_H_ */

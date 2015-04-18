/**
 * @file   IFormulaEvaluator.cpp
 * @author Christopher Maier (cmaier.business@gmail.com)
 * @date   April 2015
 *
 * Basic structure for evaluating YAGI formulas, more precisely logic sentences
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


#include "IFormulaEvaluator.h"

namespace yagi {
namespace formula {

IFormulaEvaluator::IFormulaEvaluator() :
    printFormulaEvaluationResults_(true), ctx_(nullptr)
{
}

IFormulaEvaluator::IFormulaEvaluator(ASTNodeVisitorBase* ctx) :
    printFormulaEvaluationResults_(true), ctx_(ctx)
{
}

IFormulaEvaluator::~IFormulaEvaluator()
{
}

} /* namespace formula */
} /* namespace yagi */

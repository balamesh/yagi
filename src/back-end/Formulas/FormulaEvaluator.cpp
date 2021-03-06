/**
 * @file   FormulaEvaluator.cpp
 * @author Christopher Maier (cmaier.business@gmail.com)
 * @date   April 2015
 *
 * Responsible for evaluating YAGI formulas, more precisely logic sentences
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


#include "FormulaEvaluator.h"

#include "../../utils/CustomComparers.h"
#include "../../utils/ToStringHelper.h"
#include "../Database/DBHelper.h"
#include "../SQLGenerator.h"
#include "../TreeHelper.h"
#include "../Variables/VariableTable.h"
#include "../../utils/CommandLineArgsContainer.h"
#include "NumericStringCompare.h"

namespace yagi {
namespace formula {

FormulaEvaluator::FormulaEvaluator(yagi::execution::VariableTable* varTable,
    yagi::database::DatabaseConnectorBase* db) :
    varTable_(varTable), db_(db)
{
  printFormulaEvaluationResults_ =
      yagi::container::CommandLineArgsContainer::getInstance().getShowDebugMessages();
}

FormulaEvaluator::~FormulaEvaluator()
{
}

bool FormulaEvaluator::evaluateNegation(NodeNegation* negation)
{
  auto ret = !negation->getFormula()->accept(*ctx_).get<bool>();

  if (printFormulaEvaluationResults_)
  {
    std::cout << "[Formula] Negation" << std::endl;
    std::cout << "[Result] " << ret << std::endl;
  }

  return ret;
}

bool FormulaEvaluator::evaluateCompoundFormula(NodeCompoundFormula* compoundFormula)
{
  auto lhsResult = compoundFormula->getLeftOperand()->accept(*ctx_).get<bool>();
  auto rhsResult = compoundFormula->getRightOperand()->accept(*ctx_).get<bool>();
  auto connective = compoundFormula->getConnective()->accept(*ctx_).get<FormulaConnective>();

  bool ret = false;
  switch (connective)
  {
    case FormulaConnective::And:
      ret = lhsResult && rhsResult;
    break;

    case FormulaConnective::Or:
      ret = lhsResult || rhsResult;
    break;

    case FormulaConnective::Implies:
      ret = !lhsResult || rhsResult;
    break;

    default:
      throw std::runtime_error("Unknown formula connective!");
  }

  if (printFormulaEvaluationResults_)
  {
    NodeFormulaConnective conn;
    conn.setFormulaConnective(connective);
    std::cout << "[Formula] Compound Operator '" << conn.toString() << "'" << std::endl;
    std::cout << "[Result] " << ret << std::endl;
  }

  return ret;
}

bool FormulaEvaluator::evaluateInFormula(NodeOperatorIn* inFormula)
{
  auto tuple = inFormula->getTuple()->accept(*ctx_).get<std::vector<std::string>>();

  for (size_t i = 0; i != tuple.size(); i++)
  {
    if (tuple[i][0] == '$') //it's a variable
    {
      tuple[i] = varTable_->getVariableValue(tuple[i]);
    }
  }

  auto setExprFluentName = inFormula->getSetExpr()->accept(*ctx_).get<std::string>();

  auto set = db_->executeQuery(
      SQLGenerator::getInstance().getSqlStringSelectAll(setExprFluentName));

  bool ret = std::any_of(std::begin(set), std::end(set),
      [&tuple](const std::vector<std::string>& elem)
      {
        return yagi::comparers::tuplesEqual(tuple,elem);
      });

  if (printFormulaEvaluationResults_)
  {
    std::cout << "[Formula] Operator 'in' Formula: " << yagi::tupleToString(tuple) << " in "
        << yagi::fluentDBDataToString(set) << std::endl;
    std::cout << "[Result] " << ret << std::endl;
  }

//Cleanup shadow fluent in case it is one
  if (isShadowFluent(setExprFluentName, *db_))
  {
    cleanupShadowFluent(setExprFluentName, *db_);
  }

  return ret;
}

bool FormulaEvaluator::evaluateQuantifiedFormula(NodeQuantifiedFormula* quantifiedFormula)
{

  auto quantifier = quantifiedFormula->getQuantifier();
  auto tuple = quantifiedFormula->getTuple()->accept(*ctx_).get<std::vector<std::string>>();
  auto setExprFluentName = quantifiedFormula->getSetExpr()->accept(*ctx_).get<std::string>();
  auto suchFormula = quantifiedFormula->getSuchFormula();

  auto set = db_->executeQuery(
      SQLGenerator::getInstance().getSqlStringSelectAll(setExprFluentName));

  bool truthVal = false;

  switch (quantifier)
  {
    case Quantifier::exists:
      for (size_t i = 0; i != set.size(); i++)
      {
        bool should_skip = false;
        for (size_t j = 0; j != tuple.size(); j++)
        {
          if(varTable_->variableExists(tuple[j]) && varTable_->isVariableInitialized(tuple[j]))
          {
            if(varTable_->getVariableValue(tuple[j]) != set[i][j])
            {
              should_skip = true;
              break;
            }
          }
        }

        if(should_skip)
          continue;

        varTable_->addScope();
        //get binding for i-th tuple in the set
        // use already bound variables
        for (size_t j = 0; j != tuple.size(); j++)
        {
          if(!varTable_->variableExists(tuple[j]) || !varTable_->isVariableInitialized(tuple[j]))
            varTable_->addVariable(tuple[j], set[i][j]);
        }

        //evaluate formula, if any
        if (suchFormula)
        {
          truthVal = suchFormula->accept(*ctx_).get<bool>();
          if (truthVal)
          {
            varTable_->removeScope();
            break;
          }
        }
        else
        {
          //if there's no 'such' formula the result is true if there is at least 1
          //element in the set, i.e. we enter this loop at least once
          truthVal = true;
        }
        varTable_->removeScope();
      }
    break;

    case Quantifier::all:
      truthVal = true;
      for (size_t i = 0; i != set.size(); i++)
      {
        bool should_skip = false;
        for (size_t j = 0; j != tuple.size(); j++)
        {
          if(varTable_->variableExists(tuple[j]) && varTable_->isVariableInitialized(tuple[j]))
          {
            if(varTable_->getVariableValue(tuple[j]) != set[i][j])
            {
              should_skip = true;
              break;
            }
          }
        }

        varTable_->addScope();
        //get binding for i-th tuple in the set
        for (size_t j = 0; j != tuple.size(); j++)
        {
          if(!varTable_->variableExists(tuple[j]) || !varTable_->isVariableInitialized(tuple[j]))
            varTable_->addVariable(tuple[j], set[i][j]);
        }

        //evaluate formula, if any
        if (suchFormula)
        {
          truthVal = truthVal && suchFormula->accept(*ctx_).get<bool>();
          if (!truthVal)
          {
            varTable_->removeScope();
            break;
          }
        }
        else
        {
          //if there's no 'such' formula the result is true if there is at least 1
          //element in the set, i.e. we enter this loop at least once
          truthVal = true;
        }
        varTable_->removeScope();
      }
    break;

    default:
      throw std::runtime_error("Unknown formula quantifier!");

  }

  if (printFormulaEvaluationResults_)
  {
    std::cout << "[Formula] Quantified Formula "
        << (quantifier == Quantifier::all ? "all " : "exists ") << yagi::tupleToString(tuple)
        << " in " << yagi::fluentDBDataToString(set) << std::endl;
    std::cout << "[Result] " << truthVal << std::endl;
  }

//Cleanup shadow fluent in case it is one
  if (isShadowFluent(setExprFluentName, *db_))
  {
    cleanupShadowFluent(setExprFluentName, *db_);
  }

  return truthVal;
}

bool FormulaEvaluator::evaluateConstant(NodeConstant* constant)
{
  auto ret = constant->getTruthValue();

  if (printFormulaEvaluationResults_)
  {
    std::cout << "[Formula] Constant" << std::endl;
    std::cout << "[Result] " << ret << std::endl;
  }

  return ret;
}

bool FormulaEvaluator::evaluateAtom(NodeAtom* atom)
{
  AtomConnective connective = AtomConnective::Unknown;
  auto lhs = atom->getLeftOperand();
  auto rhs = atom->getRightOperand();

  if (auto conn = atom->getConnective())
  {
    connective = conn->accept(*ctx_).get<AtomConnective>();
  }
  else //no operator ==> it's only a constant, we're done!
  {
    return lhs->accept(*ctx_).get<bool>();
  }

  bool ret = false;

//either both rhs and lhs are <values>...
  if (yagi::treeHelper::isValueNode(lhs.get()) && yagi::treeHelper::isValueNode(rhs.get()))
  {
    auto lhsResult = lhs->accept(*ctx_).get<std::string>();
    auto rhsResult = rhs->accept(*ctx_).get<std::string>();

    if (lhsResult[0] == '$') //it's a variable
    {
      lhsResult = varTable_->getVariableValue(lhsResult);
    }

    if (rhsResult[0] == '$') //it's a variable
    {
      rhsResult = varTable_->getVariableValue(rhsResult);
    }

    ret = performValueValueComparison(lhsResult, rhsResult, connective);
  } //or <setexpr>
  else if (std::dynamic_pointer_cast<NodeSetExpression>(lhs)
      && std::dynamic_pointer_cast<NodeSetExpression>(rhs))
  {
    auto lhsShadowFluent = lhs->accept(*ctx_).get<std::string>();
    auto rhsShadowFluent = rhs->accept(*ctx_).get<std::string>();

    //get data form db
    auto lhsResult = db_->executeQuery(
        SQLGenerator::getInstance().getSqlStringSelectAll(lhsShadowFluent));
    auto rhsResult = db_->executeQuery(
        SQLGenerator::getInstance().getSqlStringSelectAll(rhsShadowFluent));

    ret = performSetSetComparison(lhsResult, rhsResult, connective);

    //Cleanup shadow fluents in case they are no persistent fluents
    if (isShadowFluent(lhsShadowFluent, *db_))
    {
      cleanupShadowFluent(lhsShadowFluent, *db_);
    }

    if (isShadowFluent(rhsShadowFluent, *db_))
    {
      cleanupShadowFluent(rhsShadowFluent, *db_);
    }
  }
  else
    throw std::runtime_error("no clue how to evaluate this atom!");

  if (printFormulaEvaluationResults_)
  {
    std::cout << "[Result] " << ret << std::endl;
  }

  return ret;
}

bool FormulaEvaluator::performValueValueComparison(const std::string& lhs, const std::string& rhs,
    AtomConnective connective)
{
  if (printFormulaEvaluationResults_)
  {
    NodeAtomConnective conn;
    conn.setAtomConnective(connective);
    std::cout << "[Formula] Atom: " << lhs << conn.toString() << rhs << std::endl;
  }

  switch (connective)
  {
    case AtomConnective::Eq:
      return lhs == rhs;

    case AtomConnective::Ge:
      return !numeric_string_compare(lhs,rhs) || lhs == rhs;

    case AtomConnective::Gt:
      return !numeric_string_compare(lhs,rhs) && lhs != rhs;

    case AtomConnective::Le:
      return numeric_string_compare(lhs,rhs) || lhs == rhs;

    case AtomConnective::Lt:
      return numeric_string_compare(lhs,rhs);

    case AtomConnective::Neq:
      return lhs != rhs;

    default:
      throw std::runtime_error("unknown atom connective for formula evaluation!");
  }
}

bool FormulaEvaluator::performSetSetComparison(std::vector<std::vector<std::string>>& lhs,
    std::vector<std::vector<std::string>>& rhs, AtomConnective connective)
{
  if (printFormulaEvaluationResults_)
  {
    NodeAtomConnective conn;
    conn.setAtomConnective(connective);
    std::cout << "[Formula] Atom: " << yagi::fluentDBDataToString(lhs)
        << " " + conn.toString() + " " << yagi::fluentDBDataToString(rhs) << std::endl;
  }

  std::sort(std::begin(lhs), std::end(lhs), yagi::comparers::tupleLessThan);
  std::sort(std::begin(rhs), std::end(rhs), yagi::comparers::tupleLessThan);

  switch (connective)
  {
    //sets are equal
    case AtomConnective::Eq:
      return std::equal(std::begin(lhs), std::end(lhs), std::begin(rhs),
          yagi::comparers::tuplesEqual);

      //lhs is superset of rhs
    case AtomConnective::Ge:
      return std::includes(std::begin(lhs), std::end(lhs), std::begin(rhs), std::end(rhs),
          yagi::comparers::tupleLessThan);

      //lhs is a proper superset of rhs
    case AtomConnective::Gt:
      return (std::includes(std::begin(lhs), std::end(lhs), std::begin(rhs), std::end(rhs),
          yagi::comparers::tupleLessThan)
          && !std::equal(std::begin(lhs), std::end(lhs), std::begin(rhs),
              yagi::comparers::tuplesEqual));

      //lhs is subset of rhs
    case AtomConnective::Le:
      return std::includes(std::begin(rhs), std::end(rhs), std::begin(lhs), std::end(lhs),
          yagi::comparers::tupleLessThan);

      //lhs is a proper subset of rhs
    case AtomConnective::Lt:
      return (std::includes(std::begin(rhs), std::end(rhs), std::begin(lhs), std::end(lhs),
          yagi::comparers::tupleLessThan)
          && !std::equal(std::begin(lhs), std::end(lhs), std::begin(rhs),
              yagi::comparers::tuplesEqual));

      //sets are not equal
    case AtomConnective::Neq:
      return !std::equal(std::begin(lhs), std::end(lhs), std::begin(rhs),
          yagi::comparers::tuplesEqual);

    default:
      throw std::runtime_error("unknown atom connective for formula evaluation!");
  }
}

} /* namespace formula */
} /* namespace yagi */

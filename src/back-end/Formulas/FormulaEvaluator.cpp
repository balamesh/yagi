/*
 * FormulaEvaluator.cpp
 *
 *  Created on: Jul 17, 2014
 *      Author: cmaier
 */

#include "FormulaEvaluator.h"

namespace yagi {
namespace formula {

FormulaEvaluator::FormulaEvaluator()
{
}

FormulaEvaluator::~FormulaEvaluator()
{
}

bool FormulaEvaluator::evaluateConstant(NodeConstant* constant)
{
  auto ret = constant->getTruthValue();

  if (printFormulaEvaluationResults_)
    std::cout << "[Formula] Constant: " << (ret ? "true" : "false") << std::endl;

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

  //either both rhs and lhs are <values>...
  if (yagi::treeHelper::isValueNode(lhs.get()) && yagi::treeHelper::isValueNode(rhs.get()))
  {
    auto lhsResult = lhs->accept(*ctx_).get<std::string>();
    auto rhsResult = rhs->accept(*ctx_).get<std::string>();

    return performValueValueComparison(lhsResult, rhsResult, connective);
  }
  else if (std::dynamic_pointer_cast<NodeSetExpression>(lhs)
      && std::dynamic_pointer_cast<NodeSetExpression>(rhs))
  {
    auto lhsResult = lhs->accept(*ctx_).get<std::vector<std::vector<std::string>>>();
    auto rhsResult = rhs->accept(*ctx_).get<std::vector<std::vector<std::string>>>();

    return performSetSetComparison(lhsResult, rhsResult, connective);
  }
  else
  throw std::runtime_error("no clue how to evaluate this atom!");

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
      return lhs.size() >= rhs.size();

    case AtomConnective::Gt:
      return lhs.size() > rhs.size();

    case AtomConnective::Le:
      return lhs.size() <= rhs.size();

    case AtomConnective::Lt:
      return lhs.size() < rhs.size();

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

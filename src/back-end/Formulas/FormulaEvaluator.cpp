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

  for (auto i = 0; i != tuple.size(); i++)
  {
    if (tuple[i][0] == '$') //it's a variable
    {
      tuple[i] = VariableTableManager::getInstance().getMainVariableTable().getVariableValue(
          tuple[i]);
    }
  }

  auto setExprfluentName = inFormula->getSetExpr()->accept(*ctx_).get<std::string>();

  auto set = DatabaseManager::getInstance().getMainDB()->executeQuery(
      SQLGenerator::getInstance().getSqlStringSelectAll(setExprfluentName));

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

  return ret;
}

bool FormulaEvaluator::evaluateQuantifiedFormula(NodeQuantifiedFormula* quantifiedFormula)
{
  auto quantifier = quantifiedFormula->getQuantifier();
  auto tuple = quantifiedFormula->getTuple()->accept(*ctx_).get<std::vector<std::string>>();
  auto setExprFluentName = quantifiedFormula->getSetExpr()->accept(*ctx_).get<std::string>();
  auto suchFormula = quantifiedFormula->getSuchFormula();

  auto set = DatabaseManager::getInstance().getMainDB()->executeQuery(
      SQLGenerator::getInstance().getSqlStringSelectAll(setExprFluentName));

  bool truthVal = false;
  auto& varTable = VariableTableManager::getInstance().getMainVariableTable();
  varTable.addScope();

  switch (quantifier)
  {
    case Quantifier::exists:
      for (auto i = 0; i != set.size(); i++)
      {
        //get binding for i-th tuple in the set
        for (auto j = 0; j != tuple.size(); j++)
        {
          varTable.addVariable(tuple[j], set[i][j]);
        }

        //evaluate formula, if any
        if (suchFormula)
        {
          truthVal = suchFormula->accept(*ctx_).get<bool>();
          if (truthVal)
          {
            break;
          }
        }
        else
        {
          //if there's no 'such' formula the result is true if there is at least 1
          //element in the set, i.e. we enter this loop at least once
          truthVal = true;
        }
      }
    break;

    case Quantifier::all:
      truthVal = true;
      for (auto i = 0; i != set.size(); i++)
      {
        //get binding for i-th tuple in the set
        for (auto j = 0; j != tuple.size(); j++)
        {
          varTable.addVariable(tuple[j], set[i][j]);
        }

        //evaluate formula, if any
        if (suchFormula)
        {
          truthVal = truthVal && suchFormula->accept(*ctx_).get<bool>();
          if (!truthVal)
          {
            break;
          }
        }
        else
        {
          //if there's no 'such' formula the result is true if there is at least 1
          //element in the set, i.e. we enter this loop at least once
          truthVal = true;
        }
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

  varTable.removeScope();

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
      lhsResult = VariableTableManager::getInstance().getMainVariableTable().getVariableValue(
          lhsResult);
    }

    if (rhsResult[0] == '$') //it's a variable
    {
      rhsResult = VariableTableManager::getInstance().getMainVariableTable().getVariableValue(
          rhsResult);
    }

    ret = performValueValueComparison(lhsResult, rhsResult, connective);
  } //or <setexpr>
  else if (std::dynamic_pointer_cast<NodeSetExpression>(lhs)
      && std::dynamic_pointer_cast<NodeSetExpression>(rhs))
  {
    auto lhsShadowFluent = lhs->accept(*ctx_).get<std::string>();
    auto rhsShadowFluent = rhs->accept(*ctx_).get<std::string>();

    //get data form db
    auto db = DatabaseManager::getInstance().getMainDB();
    auto lhsResult = db->executeQuery(
        SQLGenerator::getInstance().getSqlStringSelectAll(lhsShadowFluent));
    auto rhsResult = db->executeQuery(
        SQLGenerator::getInstance().getSqlStringSelectAll(rhsShadowFluent));

    ret = performSetSetComparison(lhsResult, rhsResult, connective);
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

  //TODO: clarify semantics!
  switch (connective)
  {
    case AtomConnective::Eq:
      return lhs == rhs;

    case AtomConnective::Ge:
      return lhs >= rhs;

    case AtomConnective::Gt:
      return lhs > rhs;

    case AtomConnective::Le:
      return lhs <= rhs;

    case AtomConnective::Lt:
      return lhs < rhs;

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

/*
 * InterpretationVisitor.cpp
 *
 *  Created on: Jul 9, 2014
 *      Author: cmaier
 */

#include "InterpretationVisitor.h"

namespace yagi {
namespace execution {

InterpretationVisitor::InterpretationVisitor()
{

}

InterpretationVisitor::~InterpretationVisitor()
{

}

Any InterpretationVisitor::visit(NodeID& id)
{
  return Any { id.getId() };
}

Any InterpretationVisitor::visit(NodeProgram& program)
{
  std::for_each(program.getProgram().begin(), program.getProgram().end(),
      [this](std::shared_ptr<ASTNodeBase<>> stmt)
      {
        //safety net to check if only valid YAGI lines and not any
        //garbage resulting from a bug is considered a line...
        if (!TypeOk(stmt))
        {
          throw std::runtime_error("Invalid node type left on program-level of AST in InterpretationVisitor!");
        }

        stmt->accept(*this);
      });

  return Any { };
}

Any InterpretationVisitor::visit(NodeFluentDecl& fluentDecl)
{
  auto db = DatabaseManager::getInstance().getMainDB();
  db->executeNonQuery(
      SQLGenerator::getInstance().getSqlStringCreateTable(fluentDecl.getFluentName()->getId(),
          fluentDecl.getDomains().size()));
  return Any { };
}

Any InterpretationVisitor::visit(NodeFactDecl& factDecl)
{
  auto db = DatabaseManager::getInstance().getMainDB();
  db->executeNonQuery(
      SQLGenerator::getInstance().getSqlStringCreateTable(factDecl.getFactName()->getId(),
          factDecl.getDomains().size()));

  //store in db that it is a fact
  if (!db->executeQuery(
      SQLGenerator::getInstance().getSqlStringExistsTable(
          SQLGenerator::getInstance().FACTS_TABLE_NAME_)).size())
  {
    db->executeNonQuery(SQLGenerator::getInstance().getSqlStringCreateFactsTable());
  }
  db->executeNonQuery(SQLGenerator::getInstance().getSqlStringAddFact(factDecl));

  return Any { };
}

Any InterpretationVisitor::visit(NodeFluentQuery& fluentQuery)
{
  auto db = DatabaseManager::getInstance().getMainDB();
  auto fluentName = fluentQuery.getFluentToQueryName().get()->getId();

  if (!db->executeQuery(SQLGenerator::getInstance().getSqlStringExistsTable(fluentName)).size())
  {
    std::cout << "<<<< Fluent/Fact '" + fluentName + "' does not exist!" << std::endl;
  }
  else
  {
    auto fluentState = db->executeQuery(
        SQLGenerator::getInstance().getSqlStringSelectAll(fluentName));
    auto str = fluentDBDataToString(fluentState);

    std::cout << "<<<< " << fluentName << " = " << str << std::endl;
  }

  return Any { };
}

Any InterpretationVisitor::visit(NodeIDAssignment& fluentAss)
{
  auto db = DatabaseManager::getInstance().getMainDB();
  auto id = fluentAss.getFluentName().get()->getId();
  auto set = fluentAss.getSetExpr()->accept(*this).get<std::vector<std::vector<std::string>>>();
  auto assignOp = fluentAss.getOperator();

  if (assignOp->getOperator() == AssignmentOperator::Unknown)
  {
    throw std::runtime_error("Unknown assign operator!");
  }

  if (assignOp->getOperator() == AssignmentOperator::Assign)
  {
    DatabaseManager::getInstance().getMainDB()->executeNonQuery(
        SQLGenerator::getInstance().getSqlStringClearTable(id));
  }

  //the rhs of the assignment is a vector of vectors of strings that represents
  //the list of tuples. The visitor methods of the rhs took care of the different cases
  //of possible rhs types, i.e. fluent, shadow fluent.
  auto sqlStrings = SQLGenerator::getInstance().getSqlStringsForIDAssign(id, set,
      assignOp->getOperator());

  std::for_each(std::begin(sqlStrings), std::end(sqlStrings), [](const std::string& stmt)
  {
    DatabaseManager::getInstance().getMainDB()->executeNonQuery(stmt);
  });

  return Any { };
}

Any InterpretationVisitor::visit(NodeActionDecl& actionDecl)
{
  ExecutableElementsContainer::getInstance().addOrReplaceAction(actionDecl);

  return Any { };
}

Any InterpretationVisitor::visit(NodeProcExecution& procExec)
{
  auto actionToExecute = ExecutableElementsContainer::getInstance().getAction(
      procExec.getProcToExecName()->getId());

  if (actionToExecute)
  {
    ExecutionVisitor exe(std::make_shared<yagi::formula::FormulaEvaluator>(),
        DatabaseManager::getInstance().getMainDB());
    actionToExecute->accept(exe);
  }

  return Any { };
}

Any InterpretationVisitor::visit(NodeSet& set)
{
  //Build set with tuples
  std::vector<std::vector<std::string>> valueSet;

  auto tuples = set.getTuples();

  std::for_each(std::begin(tuples), std::end(tuples),
      [this, &valueSet](const std::shared_ptr<NodeTuple>& nodeTuple)
      {
        valueSet.push_back(nodeTuple->accept(*this).get<std::vector<std::string>>());
      });

  return Any { valueSet };
}

Any InterpretationVisitor::visit(NodeTuple& tuple)
{
  //Build vector with tuple values
  std::vector<std::string> tupleVals;

  auto values = tuple.getTupleValues();

  std::for_each(std::begin(values), std::end(values),
      [this, &tupleVals](const std::shared_ptr<ASTNodeBase<>>& value)
      {
        tupleVals.push_back(value->accept(*this).get<std::string>());
      });

  return Any { tupleVals };
}

Any InterpretationVisitor::visit(NodeVariable& variable)
{
  //TODO: get variable value from variable table and return the value
  return Any { };
}

Any InterpretationVisitor::visit(NodeString& str)
{
  return Any { str.getString() };
}

Any InterpretationVisitor::visit(NodeSetExpression& setExpr)
{
  std::vector<std::vector<std::string>> lhsResultVector, rhsResultVector;
  ExprOperator exprOp = ExprOperator::Unknown;

  if (auto lhs = setExpr.getLhs())
  {
    auto lhsResult = lhs->accept(*this);

    //lhs is a <set>
    if (lhsResult.hasType<std::vector<std::vector<std::string>>>())
    {
      lhsResultVector = lhsResult.get<std::vector<std::vector<std::string>>>();
    }
    else if (lhsResult.hasType<std::string>()) //lhs is an ID, i.e. another <fluent>
    {
      //get data from fluent
      lhsResultVector = lhsResult.get<std::vector<std::vector<std::string>>>();
    }
  }

  if (auto rhs = setExpr.getRhs())
  {
    rhsResultVector = rhs->accept(*this).get<std::vector<std::vector<std::string>>>();
  }

  if (auto op = setExpr.getOperator())
  {
    exprOp = op->getOperator();
  }
  else
  {
    return Any { lhsResultVector };
  }

  if (exprOp == ExprOperator::Plus)
  {
    return Any { buildUnion(lhsResultVector, rhsResultVector) };
  }
  else if (exprOp == ExprOperator::Minus)
  {
    return Any { buildComplement(lhsResultVector, rhsResultVector) };
  }
  else
    throw std::runtime_error("Unknown <setexpr> operator!");

}

std::string InterpretationVisitor::fluentDBDataToString(std::vector<std::vector<std::string>> data)
{
  std::string str = "{";

  std::for_each(std::begin(data), std::end(data), [&str](const std::vector<std::string>& row)
  {
    str += "<";

    std::for_each(std::begin(row), std::end(row), [&str](const std::string& col)
        {
          str += "\"" + col + "\",";
        });

    str = str.substr(0,str.length()-1);
    str += ">, ";
  });

  if (str.length() > 1)
    return str.substr(0, str.length() - 2) + "}";
  else
    return "[EMPTY]";
}

std::vector<std::vector<std::string>> InterpretationVisitor::buildUnion(
    std::vector<std::vector<std::string>> v1, std::vector<std::vector<std::string>> v2)
{
  std::vector<std::vector<std::string>> dest;
  std::sort(std::begin(v1), std::end(v1), yagi::comparers::tupleLessThan);
  std::sort(std::begin(v2), std::end(v2), yagi::comparers::tupleLessThan);

  std::set_union(v1.begin(), v1.end(), v2.begin(), v2.end(), std::back_inserter(dest),
      yagi::comparers::tupleLessThan);

  return dest;
}

std::vector<std::vector<std::string>> InterpretationVisitor::buildComplement(
    std::vector<std::vector<std::string>> v1, std::vector<std::vector<std::string>> v2)
{

  std::vector<std::vector<std::string>> dest;
  std::set_difference(v1.begin(), v1.end(), v2.begin(), v2.end(), std::back_inserter(dest),
      yagi::comparers::tupleLessThan);

  return dest;
}

} /* namespace execution */
} /* namespace yagi */


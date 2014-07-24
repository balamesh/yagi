/*
 * ActionProcedureInterpretationVisitor.cpp
 *
 *  Created on: Jul 19, 2014
 *      Author: cmaier
 */

#include "ActionProcedureInterpretationVisitor.h"

namespace yagi {
namespace execution {

ActionProcedureInterpretationVisitor::ActionProcedureInterpretationVisitor() :
    formulaEvaluator_(nullptr), db_(nullptr), signalReceiver_(nullptr)
{

}

ActionProcedureInterpretationVisitor::ActionProcedureInterpretationVisitor(
    std::shared_ptr<DatabaseConnectorBase> db) :
    formulaEvaluator_(nullptr), db_(db), signalReceiver_(nullptr)
{
}

ActionProcedureInterpretationVisitor::ActionProcedureInterpretationVisitor(
    std::shared_ptr<IFormulaEvaluator> formulaEvaluator, std::shared_ptr<DatabaseConnectorBase> db,
    std::shared_ptr<ISignalReceiver> signalReceiver) :
    formulaEvaluator_(formulaEvaluator), db_(db), signalReceiver_(signalReceiver)
{
  formulaEvaluator_->setContext(this);
}

ActionProcedureInterpretationVisitor::~ActionProcedureInterpretationVisitor()
{

}

Any ActionProcedureInterpretationVisitor::visit(NodeID& id)
{
  return Any { id.getId() };
}

Any ActionProcedureInterpretationVisitor::visit(NodeActionPrecondition& ap)
{
  return Any { ap.getFormula()->accept(*this) };
}

Any ActionProcedureInterpretationVisitor::visit(NodeConstant& formulaConstant)
{
  return Any { formulaEvaluator_->evaluateConstant(&formulaConstant) };
}

Any ActionProcedureInterpretationVisitor::visit(NodeAtom& atom)
{
  return Any { formulaEvaluator_->evaluateAtom(&atom) };
}

Any ActionProcedureInterpretationVisitor::visit(NodeSignal& signal)
{
  if (!signalReceiver_)
  {
    throw std::runtime_error("Want to send <signal> with no signal receiver set!");
  }

  auto signalData = signal.getSignalData()->accept(*this).get<std::string>();
  signalReceiver_->signal(signalData);

  return Any { };

}

Any ActionProcedureInterpretationVisitor::visit(NodeActionDecl& actionDecl)
{
  auto actionName = actionDecl.getActionName()->accept(*this).get<std::string>();

  if (auto signal = actionDecl.getSignal())
  {
    signal->accept(*this);
  }

  bool apHolds = actionDecl.getActionPrecondition()->accept(*this).tryGetCopy<bool>(false);
  if (!apHolds)
  {
    std::cout << "--> AP for action [" + actionName + "] does NOT hold." << std::endl;

    return Any { };
  }

  std::cout << "--> AP for action [" + actionName + "] holds." << std::endl;

  auto statements = actionDecl.getActionEffect()->getBlock()->getStatements();

  std::for_each(std::begin(statements), std::end(statements),
      [this](std::shared_ptr<NodeStatementBase> stmt)
      {
        stmt->accept(*this);
      });

  return Any { };
}

Any ActionProcedureInterpretationVisitor::visit(NodeProcExecution& procExec)
{
  if (!formulaEvaluator_)
    throw std::runtime_error("No FormulaEvaluator passed to InterpretationVisitor!");

  if (!db_)
    throw std::runtime_error("No Database passed to InterpretationVisitor!");

  auto actionOrProcName = procExec.getProcToExecName()->accept(*this).get<std::string>();
  auto actionToExecute = ExecutableElementsContainer::getInstance().getAction(actionOrProcName);

  if (actionToExecute)
  {
    actionToExecute->accept(*this);
  }

  return Any { };
}

Any ActionProcedureInterpretationVisitor::visit(NodeAssignmentOperator& assOp)
{
  return Any { assOp.getOperator() };
}

Any ActionProcedureInterpretationVisitor::visit(NodeIDAssignment& idAssign)
{
  auto id = idAssign.getFluentName()->accept(*this).get<std::string>();
  auto set = idAssign.getSetExpr()->accept(*this).get<std::vector<std::vector<std::string>>>();
  auto assignOp = idAssign.getOperator()->accept(*this).get<AssignmentOperator>();

  if (assignOp == AssignmentOperator::Unknown)
  {
    throw std::runtime_error("Unknown assign operator!");
  }

  if (assignOp == AssignmentOperator::Assign)
  {
    db_->executeNonQuery(SQLGenerator::getInstance().getSqlStringClearTable(id));
  }

  //the rhs of the assignment is a vector of vectors of strings that represents
  //the list of tuples. The visitor methods of the rhs took care of the different cases
  //of possible rhs types, i.e. fluent, shadow fluent.
  auto sqlStrings = SQLGenerator::getInstance().getSqlStringsForIDAssign(id, set, assignOp);

  std::for_each(std::begin(sqlStrings), std::end(sqlStrings), [this](const std::string& stmt)
  {
    db_->executeNonQuery(stmt);
  });

  return Any { };
}

Any ActionProcedureInterpretationVisitor::visit(NodeSet& set)
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

Any ActionProcedureInterpretationVisitor::visit(NodeTuple& tuple)
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

Any ActionProcedureInterpretationVisitor::visit(NodeVariable& variable)
{
  return Any { variable.getVarName() };
}

Any ActionProcedureInterpretationVisitor::visit(NodeString& str)
{
  auto ret = str.getString();
  return Any { ret.substr(1, ret.size() - 2) };
}

Any ActionProcedureInterpretationVisitor::visit(NodeAtomConnective& atomConnective)
{
  return Any { atomConnective.getAtomConnective() };
}

Any ActionProcedureInterpretationVisitor::visit(NodeValueExpression& valExpr)
{
  std::string lhsResult = "", rhsResult = "";
  ExprOperator exprOp = ExprOperator::Unknown;

  if (auto lhs = valExpr.getLhs())
  {
    lhsResult = yagi::treeHelper::getValueFromValueNode(lhs.get(), *this);
  }

  if (auto rhs = valExpr.getRhs())
  {
    rhsResult = yagi::treeHelper::getValueFromValueNode(rhs.get(), *this);
  }

  if (auto op = valExpr.getOperator())
  {
    exprOp = op->getOperator();
  }
  else
  {
    return Any { lhsResult };
  }

  if (exprOp == ExprOperator::Plus)
  {
    return Any { lhsResult + rhsResult };
  }
  else
    throw std::runtime_error("Unknown <setexpr> operator!");

}

Any ActionProcedureInterpretationVisitor::visit(NodeSetExpression& setExpr)
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
    return Any { yagi::operations::buildUnion(lhsResultVector, rhsResultVector) };
  }
  else if (exprOp == ExprOperator::Minus)
  {
    return Any { yagi::operations::buildComplement(lhsResultVector, rhsResultVector) };
  }
  else
    throw std::runtime_error("Unknown <setexpr> operator!");
}

Any ActionProcedureInterpretationVisitor::visit(NodeVariableAssignment& varAss)
{
  auto val = yagi::treeHelper::getValueFromValueNode(varAss.getValue().get(), *this);
  auto varName = varAss.getVariable()->accept(*this).get<std::string>();

  VariableTableManager::getInstance().getMainVariableTable().addOrReplaceVariable(varName, val);

  return Any { };
}

} /* namespace execution */
} /* namespace yagi */

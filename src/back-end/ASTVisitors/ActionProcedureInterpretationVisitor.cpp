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

Any ActionProcedureInterpretationVisitor::visit(NodeNegation& negation)
{
  return Any { formulaEvaluator_->evaluateNegation(&negation) };
}

Any ActionProcedureInterpretationVisitor::visit(NodeCompoundFormula& compoundFormula)
{
  return Any { formulaEvaluator_->evaluateCompoundFormula(&compoundFormula) };
}

Any ActionProcedureInterpretationVisitor::visit(NodeFormulaConnective& formulaConnective)
{
  return Any { formulaConnective.getFormulaConnective() };
}

Any ActionProcedureInterpretationVisitor::visit(NodeAtom& atom)
{
  return Any { formulaEvaluator_->evaluateAtom(&atom) };
}

Any ActionProcedureInterpretationVisitor::visit(NodeQuantifiedFormula& quantifiedFormula)
{
  return Any { formulaEvaluator_->evaluateQuantifiedFormula(&quantifiedFormula) };
}

Any ActionProcedureInterpretationVisitor::visit(NodeOperatorIn& inFormula)
{
  return Any { formulaEvaluator_->evaluateInFormula(&inFormula) };
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
    std::cout << "--> AP for action '" + actionName + "' does NOT hold." << std::endl;

    return Any { };
  }

  std::cout << "--> AP for action '" + actionName + "' holds." << std::endl;

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
  auto lhs = idAssign.getFluentName()->accept(*this).get<std::string>();

  //the rhs is a (shadow-)fluent/fact for sure, so we get the name here
  auto rhs = idAssign.getSetExpr()->accept(*this).get<std::string>();
  auto assignOp = idAssign.getOperator()->accept(*this).get<AssignmentOperator>();

  if (assignOp == AssignmentOperator::Unknown)
  {
    throw std::runtime_error("Unknown assign operator!");
  }

  if (assignOp == AssignmentOperator::Assign)
  {
    db_->executeNonQuery(SQLGenerator::getInstance().getSqlStringClearTable(lhs));
  }

  //get data from rhs
  auto data = db_->executeQuery(SQLGenerator::getInstance().getSqlStringSelectAll(rhs));
  auto sqlStrings = SQLGenerator::getInstance().getSqlStringsForIDAssign(lhs, data, assignOp);

  std::for_each(std::begin(sqlStrings), std::end(sqlStrings), [this](const std::string& stmt)
  {
    db_->executeNonQuery(stmt);
  });

  return Any { };
}

Any ActionProcedureInterpretationVisitor::visit(NodeFluentDecl& fluentDecl)
{
  auto tableName = fluentDecl.getFluentName()->accept(*this).get<std::string>();

  db_->executeNonQuery(
      SQLGenerator::getInstance().getSqlStringCreateTable(tableName,
          fluentDecl.getDomains().size()));
  return Any { };
}

Any ActionProcedureInterpretationVisitor::visit(NodeSet& set)
{
  //Build shadow fluent for set
  std::vector<std::vector<std::string>> valueSet;
  std::vector<std::vector<std::string>> domains;

  auto tuples = set.getTuples();

  //build strings to add to the DB and deduce domains
  bool first = true;
  std::for_each(std::begin(tuples), std::end(tuples),
      [this, &valueSet, &domains, &first](const std::shared_ptr<NodeTuple>& nodeTuple)
      {
        auto tupleVals = nodeTuple->accept(*this).get<std::vector<std::string>>();
        valueSet.push_back(tupleVals);

        int idx=0;

        //add values to respective domains
        std::for_each(std::begin(tupleVals), std::end(tupleVals),
            [&domains,&idx,&first](const std::string& str)
            {
              if (!first)
              {
                domains[idx].push_back(str);
              }
              else
              {
                domains.push_back(
                    { str});
              }

              idx++;
            });

        first = false;
      });

  //save shadow fluent to db
  auto shadowFluentName = "shadow" + std::to_string(getNowTicks());

  NodeFluentDecl shadowFluentNode;
  shadowFluentNode.setFluentName(std::make_shared<NodeID>(shadowFluentName));

  std::for_each(std::begin(domains), std::end(domains),
      [this, &shadowFluentNode](const std::vector<std::string>& domain)
      {
        auto domainNode = std::make_shared<NodeDomainStringElements>();

        std::for_each(std::begin(domain), std::end(domain),
            [&domainNode](const std::string& str)
            {
              domainNode->addStringToDomain(std::make_shared<NodeString>(str));
            });

        shadowFluentNode.addDomain(domainNode);
      });

  visit(shadowFluentNode);

  //assign
  auto sqlStrings = SQLGenerator::getInstance().getSqlStringsForIDAssign(shadowFluentName, valueSet,
      AssignmentOperator::Assign);

  std::for_each(std::begin(sqlStrings), std::end(sqlStrings), [this](const std::string& stmt)
  {
    db_->executeNonQuery(stmt);
  });

  //add the info the the fluent is a shadow fluent
  if (!db_->executeQuery(
      SQLGenerator::getInstance().getSqlStringExistsTable(
          SQLGenerator::getInstance().SHADOW_FLUENTS_TABLE_NAME_)).size())
  {
    db_->executeNonQuery(SQLGenerator::getInstance().getSqlStringCreateShadowFluentsTable());
  }

  db_->executeNonQuery(
      SQLGenerator::getInstance().getSqlStringMakeTableShadowFluent(shadowFluentName));

  return Any { shadowFluentName };
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

  //strip trailing and leading " if neccessary
  if (ret[0] == '"' && ret[ret.size() - 1] == '"')
  {
    return Any { ret.substr(1, ret.size() - 2) };
  }
  else
  {
    return Any { ret };
  }
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

  auto lhs = setExpr.getLhs();
  auto lhsResult = lhs->accept(*this);

  //get data from (shadow-) fluent
  lhsResultVector = db_->executeQuery(
      SQLGenerator::getInstance().getSqlStringSelectAll(lhsResult.get<std::string>()));

  if (auto rhs = setExpr.getRhs())
  {
    auto rhsResult = rhs->accept(*this);

    //get data from (shadow-) fluent
    rhsResultVector = db_->executeQuery(
        SQLGenerator::getInstance().getSqlStringSelectAll(rhsResult.get<std::string>()));
  }

  if (auto op = setExpr.getOperator())
  {
    exprOp = op->getOperator();
  }
  else //it's just a set and no full <setexpr>, so we return the (shadow-) fluent name
  {
    return Any { lhsResult.get<std::string>() };
  }

  std::vector<std::vector<std::string>> result;
  if (exprOp == ExprOperator::Plus)
  {
    result = yagi::operations::buildUnion(lhsResultVector, rhsResultVector);
  }
  else if (exprOp == ExprOperator::Minus)
  {
    result = yagi::operations::buildComplement(lhsResultVector, rhsResultVector);
  }
  else
    throw std::runtime_error("Unknown <setexpr> operator!");

  //Build new <set> and shadow fluent
  NodeSet nodeResult;

  std::for_each(std::begin(result), std::end(result),
      [this, &nodeResult](const std::vector<std::string>& tupleString)
      {
        auto tupleNode = std::make_shared<NodeTuple>();

        std::for_each(std::begin(tupleString), std::end(tupleString),
            [&tupleNode](const std::string& str)
            {
              tupleNode->addTupleValue(std::make_shared<NodeString>(str));
            });

        nodeResult.addTuple(tupleNode);
      });

  auto newShadowFluentName = visit(nodeResult).get<std::string>();
  return Any { newShadowFluentName };
}

Any ActionProcedureInterpretationVisitor::visit(NodeVariableAssignment & varAss)
{
  auto val = yagi::treeHelper::getValueFromValueNode(varAss.getValue().get(), *this);
  auto varName = varAss.getVariable()->accept(*this).get<std::string>();

  VariableTableManager::getInstance().getMainVariableTable().addOrReplaceVariable(varName, val);

  return Any { };
}

} /* namespace execution */
} /* namespace yagi */

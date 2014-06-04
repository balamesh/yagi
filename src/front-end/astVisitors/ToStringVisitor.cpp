/*
 * ToStringVisitor.cpp
 *
 *  Created on: May 22, 2014
 *      Author: cmaier
 */

#include "ToStringVisitor.h"

#include <algorithm>

ToStringVisitor::ToStringVisitor()
{
  // TODO Auto-generated constructor stub

}

ToStringVisitor::~ToStringVisitor()
{
  // TODO Auto-generated destructor stub
}

void ToStringVisitor::visit(NodeString* string)
{
  outString += "[STRING=" + string->getString() + "] ";
}

void ToStringVisitor::visit(NodeDomainStringElements* domainStringElements)
{
  outString += "[DomainRoot] ";
}

void ToStringVisitor::visit(NodeFluentDecl* fluentDecl)
{
  outString += "[FluentDecl] ";
}

void ToStringVisitor::visit(NodeFactDecl* factDecl)
{
  outString += "[FactDecl] ";
}

void ToStringVisitor::visit(NodeActionDecl* actionDecl)
{
  outString += "[Action Decl] ";
}

void ToStringVisitor::visit(NodeID* id)
{
  outString += "[ID=" + id->getId() + "] ";
}

void ToStringVisitor::visit(NodeProgram* program)
{
  std::cout << "--Program--" << std::endl;
  std::cout << outString << std::endl;
}

void ToStringVisitor::visit(NodeDomainInteger* domainInt)
{
  outString += "[DomainInteger] ";
}

void ToStringVisitor::visit(NodeDomainString* domainString)
{
  outString += "[DomainString] ";
}

void ToStringVisitor::visit(NodeInteger* integer)
{
  outString += "[Integer=" + std::to_string(integer->getValue()) + "] ";
}
void ToStringVisitor::visit(NodeValueExpression* expr)
{
  outString += "[ValueExpression] ";
}
void ToStringVisitor::visit(NodeValueExpressionOperator* exprOp)
{
  outString += std::string { "[ExprOp=" }
      + (exprOp->getOperator() == ValueExprOperator::Plus ? "+" : "-") + "] ";
}
void ToStringVisitor::visit(NodeVariableAssignment* ass)
{
  outString += "[VariableAss] ";
}

void ToStringVisitor::visit(NodeVariable* var)
{
  outString += "[Var=" + var->getVarName() + "] ";
}

void ToStringVisitor::visit(NodeSetExpressionOperator* setExprOp)
{
  std::string opString { "" };

  switch (setExprOp->getOperator())
  {
    case SetExprOperator::Assign:
      opString = "=";
    break;

    case SetExprOperator::AddAssign:
      opString = "+=";
    break;

    case SetExprOperator::RemoveAssign:
      opString = "-=";
    break;

    case SetExprOperator::Unknown:
    default:
      opString = "??";
    break;
  }

  outString += "[SetExprOp = '" + opString + "'] ";
}
void ToStringVisitor::visit(NodeFluentAssignment* fluentAss)
{
  outString += "[FluentAss] ";
}
void ToStringVisitor::visit(NodeSet* set)
{
  outString += "[Set] ";
}
void ToStringVisitor::visit(NodeSetExpression* setExpr)
{
  outString += "[SetExpr] ";
}
void ToStringVisitor::visit(NodeTuple* tuple)
{
  outString += "[Tuple] ";
}

void ToStringVisitor::visit(NodeAtom* atom)
{
  outString += "[Atom] ";
}
void ToStringVisitor::visit(NodeAtomConnective* atomConnective)
{
  outString += "[Atom Connective = ";

  std::string connString;

  switch (atomConnective->getAtomConnective())
  {
    case AtomConnective::Eq:
      connString = "==";
    break;
    case AtomConnective::Neq:
      connString = "!=";
    break;
    case AtomConnective::Le:
      connString = "<=";
    break;
    case AtomConnective::Ge:
      connString = ">=";
    break;
    case AtomConnective::Lt:
      connString = "<";
    break;
    case AtomConnective::Gt:
      connString = ">";
    break;
    case AtomConnective::Unknown:
    default:
      connString = "??";
    break;
  }

  outString += connString + "] ";
}
void ToStringVisitor::visit(NodeCompoundFormula* compoundFormula)
{
  outString += "[Compound Formula] ";
}
void ToStringVisitor::visit(NodeFormulaConnective* formulaConnective)
{
  outString += "[Formula Connective = ";

  switch (formulaConnective->getFormularConnective())
  {
    case FormulaConnective::And:
      outString += "&&";
    break;

    case FormulaConnective::Or:
      outString += "||";
    break;

    case FormulaConnective::Implies:
      outString += "->";
    break;

    case FormulaConnective::Unknown:
    default:
      outString += "??";
    break;
  }

  outString += "] ";
}
void ToStringVisitor::visit(NodeNegation* negation)
{
  outString += "[Negation]";
}
void ToStringVisitor::visit(NodeOperatorIn* operatorIn)
{
  outString += "[Operator In]";
}
void ToStringVisitor::visit(NodeQuantifiedFormula* quantifiedFormula)
{
  outString += "[Quantified Formula '";

  switch (quantifiedFormula->getQuantifier())
  {
    case Quantifier::all:
      outString += "forall";
    break;
    case Quantifier::exists:
      outString += "exists";
    break;

    case Quantifier::unknown:
    default:
      outString += "??";
    break;
  }

  outString += "'] ";
}
void ToStringVisitor::visit(NodeConstant* constant)
{
  outString += std::string("[Constant = ") + (constant->getTruthValue() == true ? "true" : "false")
      + "] ";
}
void ToStringVisitor::visit(NodeSignal* signal)
{
  outString += "[Signal] ";
}
void ToStringVisitor::visit(NodeActionEffect* actionEffect)
{
  outString += "[Effect] ";
}
void ToStringVisitor::visit(NodeActionPrecondition* actionPrecondition)
{
  outString += "[AP] ";
}

void ToStringVisitor::visit(NodeVarList* varList)
{
  outString += "[VarList] ";
}

void ToStringVisitor::visit(NodeActiveSensing* activeSensing)
{
  outString += "[ActiveSensing] ";
}

void ToStringVisitor::visit(NodeForLoopAssignment* ass)
{
  outString += "[ForLoopAssignment] ";
}

void ToStringVisitor::visit(NodeConditionalAssignment* ass)
{
  outString += "[ConditionalAssignment] ";
}

void ToStringVisitor::visit(NodePassiveSensingDecl* passiveSensingDecl)
{
  outString += "[PassiveSensing] ";
}

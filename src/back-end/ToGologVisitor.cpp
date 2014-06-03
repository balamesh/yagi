/*
 * InterpretationVisitor.cpp
 *
 *  Created on: May 23, 2014
 *      Author: cmaier
 */

#include "ToGologVisitor.h"

ToGologVisitor::ToGologVisitor()
{
  // TODO Auto-generated constructor stub

}

ToGologVisitor::~ToGologVisitor()
{
  // TODO Auto-generated destructor stub
}

void ToGologVisitor::visit(NodeString* string)
{
  stringValues_.push_back(string->getString());
}

void ToGologVisitor::visit(NodeDomainStringElements* domainStringElements)
{

}

void ToGologVisitor::visit(NodeFluentDecl* fluentDecl)
{
  //In S0, the fluent is false forall possible values
  //=> nothing to do.

  //Create initial SSA for

}

void ToGologVisitor::visit(NodeFactDecl* factDecl)
{

}

void ToGologVisitor::visit(NodeActionDecl* actionDecl)
{

}

void ToGologVisitor::visit(NodeID* id)
{

}

void ToGologVisitor::visit(NodeProgram* program)
{

}

void ToGologVisitor::visit(NodeDomainInteger* domainInt)
{

}

void ToGologVisitor::visit(NodeDomainString* domainString)
{

}

void ToGologVisitor::visit(NodeInteger* integer)
{

}
void ToGologVisitor::visit(NodeValueExpression* expr)
{

}
void ToGologVisitor::visit(NodeValueExpressionOperator* exprOp)
{

}
void ToGologVisitor::visit(NodeVariableAssignment* ass)
{

}

void ToGologVisitor::visit(NodeVariable* var)
{

}

void ToGologVisitor::visit(NodeSetExpressionOperator* setExprOp)
{

}
void ToGologVisitor::visit(NodeFluentAssignment* fluentAss)
{

}
void ToGologVisitor::visit(NodeSet* set)
{

}
void ToGologVisitor::visit(NodeSetExpression* setExpr)
{

}
void ToGologVisitor::visit(NodeTuple* tuple)
{

}

void ToGologVisitor::visit(NodeAtom* atom)
{

}
void ToGologVisitor::visit(NodeAtomConnective* atomConnective)
{

}
void ToGologVisitor::visit(NodeCompoundFormula* compoundFormula)
{

}
void ToGologVisitor::visit(NodeFormulaConnective* formulaConnective)
{

}
void ToGologVisitor::visit(NodeNegation* negation)
{

}
void ToGologVisitor::visit(NodeOperatorIn* operatorIn)
{

}
void ToGologVisitor::visit(NodeQuantifiedFormula* quantifiedFormula)
{

}
void ToGologVisitor::visit(NodeConstant* constant)
{

}
void ToGologVisitor::visit(NodeSignal* signal)
{

}
void ToGologVisitor::visit(NodeActionEffect* actionEffect)
{

}
void ToGologVisitor::visit(NodeActionPrecondition* actionPrecondition)
{

}

void ToGologVisitor::visit(NodeVarList* varList)
{

}



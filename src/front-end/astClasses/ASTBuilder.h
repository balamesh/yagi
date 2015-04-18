/**
 * @file   ASTBuilder.h
 * @author Christopher Maier (cmaier@student.tugraz.at)
 * @date   January 2015
 *
 * Responsible for building the C++ AST with the data provided from the C callbacks.
 * Therefore, it either adds new C++ AST nodes to the stack of nodes or consumes (i.e. pops) nodes
 * from the node stack to build new nodes. Ultimately, the stack has only 1 single node left, which
 * is the root node of the AST. All other nodes are children of the root node, implemented
 * via the composite design pattern.
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


#ifndef ASTBUILDER_H_
#define ASTBUILDER_H_

#include <string>
#include <memory>
#include <iostream>
#include <stack>
#include <algorithm>

#include "../../common/ASTNodeTypes/ASTNodeBase.h"
#include "../../common/ASTNodeTypes/Identifier/NodeID.h"
#include "../../common/ASTNodeTypes/Domains/NodeDomainStringElements.h"
#include "../../common/ASTNodeTypes/Declarations/FluentDecl/NodeFluentDecl.h"
#include "../../common/ASTNodeTypes/ProgramStructure/NodeProgram.h"
#include "../../common/ASTNodeTypes/Domains/NodeDomainString.h"
#include "../../common/ASTNodeTypes/Declarations/FactDecl/NodeFactDecl.h"
#include "../../common/ASTNodeTypes/Variables/NodeVariable.h"
#include "../../common/ASTNodeTypes/DataTypes/NodeString.h"
#include "../../common/ASTNodeTypes/Expressions/NodeExpressionOperator.h"
#include "../../common/ASTNodeTypes/Expressions/NodeValueExpression.h"
#include "../../common/ASTNodeTypes/Statements/NodeVariableAssignment.h"
#include "../../common/ASTNodeTypes/Statements/NodeAssignmentOperator.h"
#include "../../common/ASTNodeTypes/Expressions/NodeSetExpression.h"
#include "../../common/ASTNodeTypes/Tuple/NodeTuple.h"
#include "../../common/ASTNodeTypes/Statements/NodeIDAssignment.h"
#include "../../common/ASTNodeTypes/Formula/NodeAtomConnective.h"
#include "../../common/ASTNodeTypes/Formula/NodeFormulaConnective.h"
#include "../../common/ASTNodeTypes/Formula/NodeFormulaBase.h"
#include "../../common/ASTNodeTypes/Formula/NodeAtom.h"
#include "../../common/ASTNodeTypes/Formula/NodeConstant.h"
#include "../../common/ASTNodeTypes/Formula/NodeNegation.h"
#include "../../common/ASTNodeTypes/Formula/NodeCompoundFormula.h"
#include "../../common/ASTNodeTypes/Formula/NodeQuantifiedFormula.h"
#include "../../common/ASTNodeTypes/Formula/NodeOperatorIn.h"
#include "../../common/ASTNodeTypes/Variables/NodeVarList.h"
#include "../../common/ASTNodeTypes/Declarations/ActionDecl/NodeActionDecl.h"
#include "../../common/ASTNodeTypes/Declarations/SensingDecl/NodeSensingDecl.h"
#include "../../common/ASTNodeTypes/Declarations/ActionDecl/NodeActionEffect.h"
#include "../../common/ASTNodeTypes/Declarations/ActionDecl/NodeActionPrecondition.h"
#include "../../common/ASTNodeTypes/Declarations/ActionDecl/NodeSignal.h"
#include "../../common/ASTNodeTypes/Declarations/ExogenousEventDecl/NodeExogenousEventDecl.h"
#include "../../common/ASTNodeTypes/Statements/NodeBlock.h"
#include "../../common/ASTNodeTypes/Declarations/ProcDecl/NodeProcDecl.h"
#include "../../common/ASTNodeTypes/DataTypes/NodeValueList.h"
#include "../../common/ASTNodeTypes/Statements/NodeProcExecution.h"
#include "../../common/ASTNodeTypes/Statements/NodeFluentQuery.h"
#include "../../common/ASTNodeTypes/Statements/NodeTest.h"
#include "../../common/ASTNodeTypes/Statements/NodeChoose.h"
#include "../../common/ASTNodeTypes/Statements/NodePick.h"
#include "../../common/ASTNodeTypes/Statements/NodeForLoop.h"
#include "../../common/ASTNodeTypes/Statements/NodeConditional.h"
#include "../../common/ASTNodeTypes/Statements/NodeWhileLoop.h"
#include "../../common/ASTNodeTypes/Statements/NodeSearch.h"
#include "../../common/ASTNodeTypes/DataTypes/NodePatternMatching.h"
#include "../../common/ASTNodeTypes/DataTypes/NodeIncompleteKnowledge.h"
#include "../../common/ASTNodeTypes/ProgramStructure/NodeInclude.h"

/**
 * Responsible for building the C++ AST with the data provided from the C callbacks
 */
class ASTBuilder
  final
  {
    private:
      /**
       * Default ctor
       */
      ASTBuilder()
      {
      }

      /**
       * Adds quantified formula with a given quantor
       * @param quant The quantor
       */
      void addQuantifiedFormula(Quantifier quant);

      /**
       * Returns the first element of the AST node stack casted into type T
       * @return First element of the AST node collection if it is of type T, nullptr otherwise
       */
      template<typename T> std::shared_ptr<T> getFrontElement();
    public:
      /**
       * Singleton instance getter
       * @return The singleton instance
       */
      static ASTBuilder& getInstance()
      {
        static ASTBuilder instance;
        return instance;
      }

      /**
       * Clears the AST node collection
       */
      void reset()
      {
        while (!ast.empty())
        {
          ast.pop();
        }
      }

      /**
       * Adds a domain element node to the AST node collection
       * @param domainElement The domain element
       */
      void addDomainElement(const std::string& domainElement);

      /**
       * Adds a domain of string elements node to the collection
       */
      void addDomainStringElementsNode();

      /**
       * Adds the domain node 'string' to the collection
       */
      void addDomainStringNode();

      /**
       * Adds an integer domain node to the collection
       * not used atm since we don't support integer domains
       */
      void addDomainIntegerNode();

      /**
       * Consumes domain node from AST node collection
       */
      void consumeDomain();

      /**
       * Adds include node to collection
       */
      void addInclude();

      /**
       * Adds fluent decl node to the collection
       * @param fluentName The name of the fluent
       */
      void addFluentDeclNode(const std::string& fluentName);

      /**
       * Adds program root note to the collection
       */
      void addProgram();

      /**
       * Adds fact declaration node to the collection
       * @param factName The name of the fact
       */
      void addFactDeclNode(const std::string& factName);

      /**
       * Adds exogenous event declaration node to the collection
       * @param exoEventName The name of the exo event
       */
      void addExoEventDeclNode(const std::string& exoEventName);

      /**
       * Adds variable node to the collection
       * @param varName Name of the variable
       */
      void addVarNode(const std::string& varName);

      /**
       * Adds variable list node to the collection
       */
      void addVarListNode();

      /**
       * Adds identifier node to the collection
       * @param id Name of the identifier
       */
      void addID(const std::string& id);

      /**
       * Adds procedure declaration node to the collection
       * @param procName The name of the procedure
       */
      void addProcDecl(const std::string& procName);

      /**
       * Adds sensing declaration node to the collection
       * @param sensingName Name of the sensing action
       */
      void addSensingDeclNode(const std::string& sensingName);

      /**
       * Adds action declaration node to the collection
       * @param actionName Name of the action
       */
      void addActionDeclNode(const std::string& actionName);

      /**
       * Adds effect node to the collection
       */
      void addEffect();

      /**
       * Adds integer value node to the collection (currently not used)
       * @param intVal The integer value as string
       */
      void addIntNode(const std::string& intVal);

      /**
       * Adds string value node to the collection
       * @param stringVal The string value
       */
      void addStringNode(const std::string& stringVal);

      /**
       * Consumes variable node from the collection
       */
      void consumeVarNode();

      /**
       * Adds value expression node
       */
      void addValueExpressionNode();

      /**
       * Adds expression operator node
       * @param op The operator string
       */
      void addExprOperator(const std::string& op);

      /**
       * Adds assignment to variable node to the collection
       */
      void addVarAssign();

      /**
       * Adds pattern matching node to the collection
       */
      void addPatternMatch();

      /**
       * Adds incomplete knowledge node to the collection
       */
      void addIncompleteKnowledge();

      /**
       * Adds tuple node to the collection
       */
      void addTuple();

      /**
       * Consumes tuple from the collection
       */
      void consumeTuple();

      /**
       * Consumes tuple value from the collection
       */
      void consumeTupleVal();

      /**
       * Adds set node to the collection
       */
      void addSet();

      /**
       * Adds set expression node to the collection
       */
      void addSetExpr();

      /**
       * Adds ID assignment node to the collection
       * @param identifier the name of the ID
       */
      void addIDAssign(const std::string& identifier);

      /**
       * Adds assignment operator node to the collection
       * @param op The assignment operator string
       */
      void addAssignmentOp(const std::string& op);

      /**
       * Adds atom connective node to the collection
       * @param connective The connective string
       */
      void addAtomConnective(const std::string& connective);

      /**
       * Adds formula connective node to the collection
       * @param connective The connective string
       */
      void addFormulaConnective(const std::string& connective);

      /**
       * Adds constant (true,false) node to the collection
       * @param constant The string version of the constant
       */
      void addConstant(const std::string& constant);

      /**
       * Adds atom node to the collection
       */
      void addAtom();

      /**
       * Adds negation node to the collection
       */
      void addNegation();

      /**
       * Adds connected formula node to the collection.
       */
      void addConnectedFormula();

      /**
       * Adds exists quantifier node to the collection
       */
      void addExists();

      /**
       * Adds all quantifier node to the collection
       */
      void addAll();

      /**
       * Adds 'in' operator node to the collection
       */
      void addIn();

      /**
       * Adds block node to the collection
       */
      void addBlock();

      /**
       * Consumes statement node from the collection
       */
      void consumeStatement();

      /**
       * Consumes value node from the collection
       */
      void consumeValue();

      /**
       * Adds value list node to the collection
       */
      void addValueList();

      /**
       * Adds procedure execution node to the collection
       * @param procName Name of the procedure to execute
       */
      void addProcExec(const std::string& procName);

      /**
       * Adds fluent query node to collection
       * @param fluentName Name of the fluent to query
       */
      void addFluentQuery(const std::string& fluentName);

      /**
       * Adds test statement node to collection
       */
      void addTest();

      /**
       * Adds choose statement node to collection
       */
      void addChoose();

      /**
       * Consumes block from the collection
       */
      void consumeBlock();

      /**
       * Adds pick statement to the collection
       */
      void addPick();

      /**
       * Adds a for loop node to the collection
       */
      void addForLoop();

      /**
       * Adds a conditional node to the collection
       */
      void addConditional();

      /**
       * Adds a while loop node to the collection
       */
      void addWhileLoop();

      /**
       * Adds a search node to the collection
       */
      void addSearch();

      /**
       * Getter for the root node of the AST
       * @return the root of the AST, or nullptr if there are no nodes
       */
      std::shared_ptr<ASTNodeBase<>> getAST()
      {
        return (ast.size() > 0 ? ast.top() : nullptr);
      }

    private:
      /**
       * Copy ctor
       */
      ASTBuilder(ASTBuilder const&);

      /**
       * Assignment operator
       */
      void operator=(ASTBuilder const&);

      /**
       * Stack of AST Nodes which are used to build the ast
       */
      std::stack<std::shared_ptr<ASTNodeBase<>>>ast;
    };

#endif /* ASTBUILDER_H_ */

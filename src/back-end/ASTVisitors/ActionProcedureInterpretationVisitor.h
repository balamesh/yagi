/**
 * @file   ActionProcedureInterpretationVisitor.h
 * @author Christopher Maier (cmaier.business@gmail.com)
 * @date   April 2015
 *
 * Responsible for executing a YAGI program, i.e. traversing the AST via the implemented
 * visitor methods and executing the appropriate actions.
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


#ifndef ACTIONPROCEDUREINTERPRETATIONVISITOR_H_
#define ACTIONPROCEDUREINTERPRETATIONVISITOR_H_

#include <memory>
#include <mutex>
#include <string>
#include <vector>
#include <stack>
#include <queue>
#include <atomic>

#include "../../common/ASTNodeTypes/DataTypes/NodeString.h"
#include "../../common/ASTNodeTypes/DataTypes/NodeValueList.h"
#include "../../common/ASTNodeTypes/Declarations/ActionDecl/NodeActionDecl.h"
#include "../../common/ASTNodeTypes/Declarations/ActionDecl/NodeActionPrecondition.h"
#include "../../common/ASTNodeTypes/Declarations/ActionDecl/NodeSignal.h"
#include "../../common/ASTNodeTypes/Declarations/FluentDecl/NodeFluentDecl.h"
#include "../../common/ASTNodeTypes/Declarations/ProcDecl/NodeProcDecl.h"
#include "../../common/ASTNodeTypes/Expressions/NodeSetExpression.h"
#include "../../common/ASTNodeTypes/Expressions/NodeValueExpression.h"
#include "../../common/ASTNodeTypes/Formula/NodeAtom.h"
#include "../../common/ASTNodeTypes/Formula/NodeAtomConnective.h"
#include "../../common/ASTNodeTypes/Formula/NodeCompoundFormula.h"
#include "../../common/ASTNodeTypes/Formula/NodeConstant.h"
#include "../../common/ASTNodeTypes/Formula/NodeFormulaConnective.h"
#include "../../common/ASTNodeTypes/Formula/NodeNegation.h"
#include "../../common/ASTNodeTypes/Formula/NodeOperatorIn.h"
#include "../../common/ASTNodeTypes/Formula/NodeQuantifiedFormula.h"
#include "../../common/ASTNodeTypes/Identifier/NodeID.h"
#include "../../common/ASTNodeTypes/Set/NodeSet.h"
#include "../../common/ASTNodeTypes/Statements/NodeAssignmentOperator.h"
#include "../../common/ASTNodeTypes/Statements/NodeChoose.h"
#include "../../common/ASTNodeTypes/Statements/NodeConditional.h"
#include "../../common/ASTNodeTypes/Statements/NodeForLoop.h"
#include "../../common/ASTNodeTypes/Statements/NodeIDAssignment.h"
#include "../../common/ASTNodeTypes/Statements/NodePick.h"
#include "../../common/ASTNodeTypes/Statements/NodeProcExecution.h"
#include "../../common/ASTNodeTypes/Statements/NodeSitCalcActionExecution.h"
#include "../../common/ASTNodeTypes/Statements/NodeTest.h"
#include "../../common/ASTNodeTypes/Statements/NodeVariableAssignment.h"
#include "../../common/ASTNodeTypes/Statements/NodeWhileLoop.h"
#include "../../common/ASTNodeTypes/Tuple/NodeTuple.h"
#include "../../common/ASTNodeTypes/Variables/NodeVariable.h"
#include "../../common/ASTNodeTypes/Variables/NodeVarList.h"
#include "../../common/ASTNodeVisitorBase.h"
#include "../../common/ASTNodeTypes/Statements/NodeSearch.h"
#include "../../common/ASTNodeTypes/Statements/NodeBlock.h"
#include "../../common/ASTNodeTypes/DataTypes/NodePatternMatching.h"
#include "../../common/ASTNodeTypes/DataTypes/NodeIncompleteKnowledge.h"
#include "../../common/ASTNodeTypes/Declarations/ExogenousEventDecl/NodeExogenousEventDecl.h"
#include "../../common/ASTNodeTypes/Domains/NodeDomainString.h"
#include "../../common/ASTNodeTypes/Domains/NodeDomainStringElements.h"
#include "../ExogenousEvents/IExogenousEventConsumer.h"
#include "../ExogenousEvents/IExogenousEventProducer.h"
#include "../BfsDataContainer.h"

namespace yagi {
namespace execution {
class VariableTable;
} /* namespace execution */
} /* namespace yagi */

namespace yagi {
namespace database {
class DatabaseConnectorBase;
} /* namespace database */
namespace execution {
class IYAGISignalHandler;
} /* namespace execution */
namespace formula {
class IFormulaEvaluator;
} /* namespace formula */
} /* namespace yagi */

namespace yagi {
namespace execution {

/**
 * Responsible for executing a YAGI program, i.e. traversing the AST via the implemented
 * visitor methods and executing the appropriate actions.
 */
class ActionProcedureInterpretationVisitor: public IExogenousEventConsumer,
    public ASTNodeVisitorBase,
    public Visitor<NodeActionDecl>,
    public Visitor<NodeConstant>,
    public Visitor<NodeProcExecution>,
    public Visitor<NodeActionPrecondition>,
    public Visitor<NodeIDAssignment>,
    public Visitor<NodeID>,
    public Visitor<NodeSet>,
    public Visitor<NodeSetExpression>,
    public Visitor<NodeTuple>,
    public Visitor<NodeVariable>,
    public Visitor<NodeString>,
    public Visitor<NodeVariableAssignment>,
    public Visitor<NodeAssignmentOperator>,
    public Visitor<NodeSignal>,
    public Visitor<NodeValueExpression>,
    public Visitor<NodeAtomConnective>,
    public Visitor<NodeAtom>,
    public Visitor<NodeNegation>,
    public Visitor<NodeCompoundFormula>,
    public Visitor<NodeFormulaConnective>,
    public Visitor<NodeQuantifiedFormula>,
    public Visitor<NodeOperatorIn>,
    public Visitor<NodeFluentDecl>,
    public Visitor<NodeForLoop>,
    public Visitor<NodeConditional>,
    public Visitor<NodeVarList>,
    public Visitor<NodeProcDecl>,
    public Visitor<NodeValueList>,
    public Visitor<NodePick>,
    public Visitor<NodeChoose>,
    public Visitor<NodeWhileLoop>,
    public Visitor<NodeTest>,
    public Visitor<NodeSitCalcActionExecution>,
    public Visitor<NodeSearch>,
    public Visitor<NodeBlock>,
    public Visitor<NodeIncompleteKnowledge>,
    public Visitor<NodePatternMatching>,
    public Visitor<NodeDomainString>,
    public Visitor<NodeDomainStringElements>,
    public Visitor<NodeExogenousEventDecl>
{
  private:
    /**
     * Responsible for formula evaluation
     */
    std::shared_ptr<yagi::formula::IFormulaEvaluator> formulaEvaluator_;

    /**
     * Responsible for database connection
     */
    std::shared_ptr<yagi::database::DatabaseConnectorBase> db_;

    /**
     * Responsible for dealing with signals
     */
    std::shared_ptr<IYAGISignalHandler> signalReceiver_;

    /**
     * Table of variables
     */
    yagi::execution::VariableTable* varTable_;

    /**
     * Triggers a YAGI signal
     * @param signal The signal node
     * @param settingVariables The variables that will be set
     * @return Variables and values that got set
     */
    Any triggerYagiSignal(NodeSignal& signal, std::vector<std::string> settingVariables);

    /**
     * Helper function that runs a YAGI block with a picked tuple
     * @param pickNode The pick node that is being executed
     * @param set The stringified values
     * @param tupleIndex The index of the picked tuple
     * @param ctx Current context
     * @return True if exeuction was successful, false otherwise
     */
    Any runBlockForPickedTuple(const NodePick& pickNode, std::vector<std::vector<std::string>> set,
        int tupleIndex, ActionProcedureInterpretationVisitor& ctx);

    /**
     * Rewrites a YAGI assignment into a corresponding loop according to the specification
     * @param lhsFluentName The fluent a set gets assigned to
     * @param actionType The type of assignment (add or remove)
     * @param rhsFluentName The fluent at the rhs of the assignment
     * @return The for-loop that expresses the assignment
     */
    std::shared_ptr<NodeForLoop> buildAssignmentRewritingLoop(std::string lhsFluentName,
        SitCalcActionType actionType, std::string rhsFluentName);

    /**
     * Applies the data generated from exogenous events
     */
    void applyExoEventData();

    /**
     * Is this instance a search visitor?
     */
    bool isSearch_ = false;

    /**
     * Message prefix for outputting messages
     */
    std::string msgPrefix_ = "";

    /**
     * Name of the visitor
     */
    std::string name_ = "<main>";

    /**
     * Flag that signals whether or not search has been canceled
     */
    std::atomic_bool cancelled_ { false };

    /**
     * Signals that search should do the next step
     */
    std::atomic_bool doStep_ { false };

    /**
     * Signals that the next search step is done
     */
    std::atomic_bool stepDone_ { false };

    /**
     * Wait for next search step until this variable is true
     */
    std::atomic_bool waitForNextStep { false };

    /**
     * Buffers the data generated via exogenous events
     */
    std::queue<std::tuple<std::string, std::unordered_map<std::string, std::string>>>exoEventDataBuffer_;

    /**
     * Mutex for synchronization of the exogenous event data buffer
     */
    std::mutex exoEventDataBufferMutex_;

    public:

    /**
     * Stores breadth-first search states
     * TODO XXX Should be refactored!
     */
    static std::shared_ptr<std::vector<std::shared_ptr<BfsDataContainer>>> bfsStatesQueue;

    /**
     * Stores the search choices (pick/choose indices)
     * TODO XXX Should be refactored!
     */
    std::vector<int> choices_;

    /**
     * Combines all search choices of a valid trace for online execution
     * TODO XXX Should be refactored
     */
    std::vector<int> choicesForOnlineExecution;

    /**
     * Run search process
     * TODO XXX Should be refactored
     */
    std::atomic<bool> run
    { false};

    /**
     * Execution visitor children generated during search
     * TODO XXX Should be refactored
     */
    std::vector<std::shared_ptr<ActionProcedureInterpretationVisitor>> children_;

    /**
     * Default ctor
     */
    ActionProcedureInterpretationVisitor();

    /**
     * Constructs visitor with all neccessary stuff needed for execution
     * @param formulaEvaluator A formula evaluator
     * @param db A database connector
     * @param signalReceiver A signal receiver
     * @param varTable A variable table
     * @param isSearch True if it is a search instance, false otherwise
     * @param name Name of the visitor
     */
    ActionProcedureInterpretationVisitor(
        std::shared_ptr<yagi::formula::IFormulaEvaluator> formulaEvaluator,
        std::shared_ptr<yagi::database::DatabaseConnectorBase> db,
        std::shared_ptr<IYAGISignalHandler> signalReceiver, VariableTable& varTable, bool isSearch =
        false, const std::string& name = "<main>");

    /**
     * Constructs visitor with only a database instance
     * @param db A database instance
     */
    ActionProcedureInterpretationVisitor(std::shared_ptr<yagi::database::DatabaseConnectorBase> db);

    /**
     * Constructs visitor with only a variable table
     * @param varTable A variable table
     */
    ActionProcedureInterpretationVisitor(VariableTable& varTable);

    /**
     * Default dtor
     */
    virtual ~ActionProcedureInterpretationVisitor();

    /**
     * Consumes data from an exogenous event
     * @param eventName The name of the exogenous event
     * @param variablesAndValues Variables and corresponding values from the exo event
     */
    virtual void consumeExoEventData(const std::string& eventName,
        const std::unordered_map<std::string, std::string>& variablesAndValues) override;

    /**
     * Identifier for a domain that ranges over the full range of string
     */
    static const std::string DOMAIN_STRING_ID;

    /**
     * Visit method for action decl
     * @param actionDecl The action decl node
     * @return True if execution successful, false otherwise
     */
    Any visit(NodeActionDecl& actionDecl);

    /**
     * Visit method for a constant (true/false)
     * @param formulaConstant The constant node
     * @return True or false
     */
    Any visit(NodeConstant& formulaConstant);

    /**
     * Visit method for a YAGI procedure execution
     * @param procExec The proc node to execute
     * @return True if proc execution successful, false otherwise
     */
    Any visit(NodeProcExecution& procExec);

    /**
     * Visit method for a YAGI action precondition
     * @param ap The action precondition node
     * @return True if AP holds, false otherwise
     */
    Any visit(NodeActionPrecondition& ap);

    /**
     * Visit method for an assignment to a fluent
     * @param idAssign The assignment node
     * @return Nothing
     */
    Any visit(NodeIDAssignment& idAssign);

    /**
     * Visit method for an identifier
     * @param id The identifier node
     * @return The name of the identifier
     */
    Any visit(NodeID& id);

    /**
     * Visit method for a YAGI set of tuples
     * @param set The set of tuples
     * @return The name of the shadow fluent built out of the set
     */
    Any visit(NodeSet& set);

    /**
     * Visit method for a YAGI set-expression
     * @param setExpr The set-expression node
     * @return The name of the (generated shadow) fluent
     */
    Any visit(NodeSetExpression& setExpr);

    /**
     * Visit method for a YAGI tuple
     * @param tuple The tuple node
     * @return Vector of strings that represents the tuple
     */
    Any visit(NodeTuple& tuple);

    /**
     * Visit method for a variable
     * @param variable A YAGI variable
     * @return The name of the variable
     */
    Any visit(NodeVariable& variable);

    /**
     * Visit method for a YAGI string
     * @param str The string node
     * @return The string value without leading/trailing double quote characters
     */
    Any visit(NodeString& str);

    /**
     * Visit method for a varible assignment
     * @param varAss The assignment node
     * @return Nothing
     */
    Any visit(NodeVariableAssignment& varAss);

    /**
     * Visit method for an assignment operator
     * @param assOp The operator node
     * @return The assignment operator
     */
    Any visit(NodeAssignmentOperator& assOp);

    /**
     * Visit method for a YAGI signal
     * @param signal The signal node
     * @return Nothing
     */
    Any visit(NodeSignal& signal);

    /**
     * Visit method for a value expression
     * @param valExpr The val. expr. node
     * @return String that represents result of val. expr.
     */
    Any visit(NodeValueExpression& valExpr);

    /**
     * Visit method for atom connective
     * @param atomConnective The connective node
     * @return The atom connective
     */
    Any visit(NodeAtomConnective& atomConnective);

    /**
     * Visit method for atom
     * @param atom The atom node
     * @return True or false
     */
    Any visit(NodeAtom& atom);

    /**
     * Visit method for formula negation
     * @param negation The negation node
     * @return True or false
     */
    Any visit(NodeNegation& negation);

    /**
     * Visit method for a compound formula
     * @param compoundFormula The compound formula node
     * @return True or false
     */
    Any visit(NodeCompoundFormula& compoundFormula);

    /**
     * Visit method for a formula connective
     * @param formulaConnective The connective node
     * @return The formula connective
     */
    Any visit(NodeFormulaConnective& formulaConnective);

    /**
     * Visit method for a quantified formula
     * @param quantifiedFormula The quantified formula node
     * @return True or false
     */
    Any visit(NodeQuantifiedFormula& quantifiedFormula);

    /**
     * Visit method for a 'in' formula
     * @param inFormula The 'in'-formula node
     * @return True or false
     */
    Any visit(NodeOperatorIn& inFormula);

    /**
     * Visit method for a fluent declaration
     * @param fluentDecl The fluent decl. node
     * @return Nothing
     */
    Any visit(NodeFluentDecl& fluentDecl);

    /**
     * Visit method for a YAGI for loop
     * @param forLoop The for loop node
     * @return Nothing
     */
    Any visit(NodeForLoop& forLoop);

    /**
     * Visit method for a YAGI conditional
     * @param conditional The conditional node
     * @return True if execution successful, false otherwise
     */
    Any visit(NodeConditional& conditional);

    /**
     * Visit method for a list of variables
     * @param varList The var. list node
     * @return List of strings that represent the variable names
     */
    Any visit(NodeVarList& varList);

    /**
     * Visit method for EXECUTING a YAGI procedure
     * @param procDecl The proc. decl. node
     * @return True if exection successful, false otherwise
     */
    Any visit(NodeProcDecl& procDecl);

    /**
     * Visit method for a list of values
     * @param valueList The list of values node
     * @return String values of the YAGI 'values'
     */
    Any visit(NodeValueList& valueList);

    /**
     * Visit method for the YAGI pick statement
     * XXX Needs to be re-designed for search!!
     * @param pick The pick statement node
     * @return True if successful, false otherwise
     */
    Any visit(NodePick& pick);

    /**
     * Visit method for the YAGI choose statement
     * XXX Needs to be re-designed for search!!
     * @param choose The choose statement node
     * @return True if successful, false otherwise
     */
    Any visit(NodeChoose& choose);

    /**
     * Visit method for the YAGI while loop
     * XXX Needs to be re-designed for search!!
     * @param whileLoop The while loop node
     * @return Nothing when in search block, truth value otherwise
     */
    Any visit(NodeWhileLoop& whileLoop);

    /**
     * Visit method for the YAGI test statement
     * @param test The test node
     * @return True if the formula under test holds, false otherwise
     */
    Any visit(NodeTest& test);

    /**
     * Visit method for sit calc action, i.e. addX or removeX for fluent X
     * @param sitCalcAction The action node
     * @return Nothing
     */
    Any visit(NodeSitCalcActionExecution& sitCalcAction);

    /**
     * Visit method for YAGI search block
     * @param search The search node
     * @return Nothing
     */
    Any visit(NodeSearch& search);

    /**
     * Visit method for an arbitrary YAGI block
     * @param block The block node
     * @return True if block has been executed successfully, false otherwise
     */
    Any visit(NodeBlock& block);

    /**
     * Visit method for incomplete knowledge
     * XXX Always throws exception! Implement as soon as specification exists!
     * @param incompleteKnowledge The node for incomplete knowledge
     * @return Nothing
     */
    Any visit(NodeIncompleteKnowledge& incompleteKnowledge);

    /**
     * Visit method for pattern matching
     * Always throws exception since pattern matching should have been
     * rewritten at this stage of execution
     * @param patternMatching The pattern matching node
     * @return Nothing
     */
    Any visit(NodePatternMatching& patternMatching);

    /**
     * Visit method for string domain
     * @param nodeDomainString The domain node
     * @return Unique identifier saying 'this is a string domain'
     */
    Any visit(NodeDomainString& nodeDomainString);

    /**
     * Visit method for string domain elements
     * @param nodeDomainStringElements The string domain node
     * @return Vector of string elements in the domain
     */
    Any visit(NodeDomainStringElements& nodeDomainStringElements);

    /**
     * Visit method for exogenous events declarations
     * @param nodeExoEventDecl The exo. event decl. node
     * @return True
     */
    Any visit(NodeExogenousEventDecl& nodeExoEventDecl);

    /**
     * Getter for the database instance
     * @return The current database instance
     */
    std::shared_ptr<yagi::database::DatabaseConnectorBase>& getDb()
    {
      return db_;
    }

    /**
     * Getter for the variable table
     * @return The current variable table
     */
    yagi::execution::VariableTable*& getVarTable()
    {
      return varTable_;
    }

    /**
     * Getter for the name o the visitor instance; used for debugging/visualization purposes
     * @return The name of the visitor instance
     */
    const std::string& getName() const
    {
      return name_;
    }
  };

}
/* namespace execution */
} /* namespace yagi */

#endif /* ACTIONPROCEDUREINTERPRETATIONVISITOR_H_ */

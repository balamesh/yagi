/*
 * RewritingVisitor.h
 *
 *  Created on: Jul 24, 2014
 *      Author: cmaier
 */

#ifndef REWRITINGVISITOR_H_
#define REWRITINGVISITOR_H_

#include <memory>
#include <vector>
#include <algorithm>
#include <unordered_map>

#include "../../utils/Any.h"
#include "../../common/ASTNodeVisitorBase.h"
#include "../../common/ASTNodeTypes/Declarations/ActionDecl/NodeActionDecl.h"
#include "../../common/ASTNodeTypes/Declarations/ActionDecl/NodeActionEffect.h"
#include "../../common/ASTNodeTypes/Statements/NodeForLoop.h"
#include "../../common/ASTNodeTypes/Statements/NodeBlock.h"
#include "../../common/ASTNodeTypes/Statements/NodeIDAssignment.h"
#include "../../common/ASTNodeTypes/ProgramStructure/NodeProgram.h"
#include "../../common/ASTNodeTypes/Statements/NodeProcExecution.h"
#include "../../common/ASTNodeTypes/Statements/NodeSitCalcActionExecution.h"
#include "ActionProcedureInterpretationVisitor.h"
#include "../Database/DatabaseManager.h"

using namespace yagi::database;

namespace yagi {
namespace execution {

class RewritingVisitor: public ASTNodeVisitorBase, public Visitor<NodeIDAssignment>, public Visitor<
    NodeActionDecl>, public Visitor<NodeActionEffect>
{
  private:
    std::shared_ptr<NodeForLoop> buildAssignmentRewritingLoop(std::string lhsFluentName,
        SitCalcActionType actionType, std::string rhsFluentName);

  public:
    RewritingVisitor();
    virtual ~RewritingVisitor();

    Any visit(NodeActionDecl& actionDecl);
    Any visit(NodeActionEffect& effect);
    Any visit(NodeIDAssignment& idAssignment);
};

}
/* namespace execution */
} /* namespace yagi */

#endif /* REWRITINGVISITOR_H_ */

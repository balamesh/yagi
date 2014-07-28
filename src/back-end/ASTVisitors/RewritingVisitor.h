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

namespace yagi {
namespace execution {

//class RewritingVisitor: public ASTNodeVisitorBase, public Visitor<NodeActionDecl>, public Visitor<
//    NodeActionEffect>, public Visitor<NodeForLoop>, public Visitor<NodeBlock>, public Visitor<
//    NodeIDAssignment>, public Visitor<NodeProgram>
class RewritingVisitor: public ASTNodeVisitorBase, public Visitor<NodeIDAssignment>
{
  public:
    RewritingVisitor();
    virtual ~RewritingVisitor();

//    Any visit(NodeActionDecl& actionDecl);
//    Any visit(NodeActionEffect& effect);
//    Any visit(NodeForLoop& forLoopAssign);
//    Any visit(NodeBlock& block);
    Any visit(NodeIDAssignment& idAssignment);
//    Any visit(NodeProgram& program);
};

}
/* namespace execution */
} /* namespace yagi */

#endif /* REWRITINGVISITOR_H_ */

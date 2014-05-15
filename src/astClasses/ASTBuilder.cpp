/*
 * ASTBuilder.cpp
 *
 *  Created on: Apr 24, 2014
 *      Author: cmaier
 */

#include "ASTBuilder.h"
#include <assert.h>

ASTBuilder::ASTBuilder() {
	// TODO Auto-generated constructor stub
}

ASTBuilder::~ASTBuilder() {
	// TODO Auto-generated destructor stub
}

void ASTBuilder::addIDNode(std::string id) {
	ast.push_front(new NodeID(id));

}
void ASTBuilder::addIDSetNode() {
	NodeIDSet* idSet = new NodeIDSet();

	while (!ast.empty() && dynamic_cast<NodeID*>(ast.front()) != nullptr)
	{
		idSet->addID(dynamic_cast<NodeID*>(ast.front()));
		ast.pop_front();
	}

	ast.push_front(idSet);
}
void ASTBuilder::addFluentDeclNode(std::string fluentName) {
	NodeFluentDecl* fluentDeclNode = new NodeFluentDecl();

    fluentDeclNode->setFluentName(new NodeID(fluentName));
    fluentDeclNode->setDomain(dynamic_cast<NodeIDSet*>(ast.front()));
    ast.pop_front();

	ast.push_front(fluentDeclNode);

	assert(ast.size() == 1);
}

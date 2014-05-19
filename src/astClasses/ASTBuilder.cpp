/*
 * ASTBuilder.cpp
 *
 *  Created on: Apr 24, 2014
 *      Author: cmaier
 */

#include "ASTBuilder.h"
#include <assert.h>
#include "../utils/make_unique.h"

ASTBuilder::ASTBuilder() {
	// TODO Auto-generated constructor stub
}

ASTBuilder::~ASTBuilder() {
	// TODO Auto-generated destructor stub
}

void ASTBuilder::addDomainElement(std::string domainElement)
{
	auto domain = std::static_pointer_cast<NodeDomainStringElements>(ast.front());
    domain->addStringToDomain(domainElement);
}
void ASTBuilder::addDomainStringElementsNode()
{
	auto domainStringElements = std::make_shared<NodeDomainStringElements>();


	/*while (!ast.empty() && dynamic_cast<NodeID*>(ast.front()) != nullptr)
	{
		idSet->addID(dynamic_cast<NodeID*>(ast.front()));
		ast.pop_front();
	}*/

	ast.push_front(domainStringElements);

}

void ASTBuilder::addDomainIntegerNode()
{

}

void ASTBuilder::addDomainStringNode()
{

}

void ASTBuilder::addFluentDeclNode(std::string fluentName)
{
	auto fluentDeclNode = std::make_shared<NodeFluentDecl>();

    fluentDeclNode->setFluentName(std::make_shared<NodeID>(fluentName));
    fluentDeclNode->setDomain(std::static_pointer_cast<NodeDomainStringElements>(ast.front()));
    ast.pop_front();

	ast.push_front(fluentDeclNode);

	assert(ast.size() == 1);
}

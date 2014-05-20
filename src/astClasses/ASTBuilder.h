/*
 * ASTBuilder.h
 *
 *  Created on: Apr 24, 2014
 *      Author: cmaier
 */

#ifndef ASTBUILDER_H_
#define ASTBUILDER_H_

#include <string>
#include <memory>
#include <iostream>
#include <deque>
#include <algorithm>

#include "ASTNodeBase.h"
#include "NodeID.h"
#include "NodeDomainStringElements.h"
#include "NodeFluentDecl.h"
#include "NodeProgram.h"

class ASTBuilder {
public:
    static ASTBuilder& getInstance()
    {
        static ASTBuilder instance;
        return instance;
    }

    void addDomainElement(std::string domainElement);
    void addDomainStringElementsNode();
    void addDomainStringNode();
    void addDomainIntegerNode();
    void addFluentDeclNode(std::string fluentName);
    void addProgram();

    std::shared_ptr<ASTNodeBase> getAST() {return (ast.size() > 0 ? ast.front() : nullptr);}

private:
    ASTBuilder(ASTBuilder const&);
    void operator=(ASTBuilder const&);

	ASTBuilder();
	virtual ~ASTBuilder();

	std::deque<std::shared_ptr<ASTNodeBase>> ast;
};

#endif /* ASTBUILDER_H_ */

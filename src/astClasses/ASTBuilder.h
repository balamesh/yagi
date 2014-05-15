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

#include "ASTNodeBase.h"
#include "NodeID.h"
#include "NodeIDSet.h"
#include "NodeFluentDecl.h"

class ASTBuilder {
public:
    static ASTBuilder& getInstance()
    {
        static ASTBuilder instance;
        return instance;
    }

    void addIDNode(std::string id);
    void addIDSetNode();
    void addFluentDeclNode(std::string fluentName);

    ASTNodeBase* getAST() {return (ast.size() > 0 ? ast.front() : nullptr);}

private:
    ASTBuilder(ASTBuilder const&);
    void operator=(ASTBuilder const&);

	ASTBuilder();
	virtual ~ASTBuilder();

	std::deque<ASTNodeBase*> ast;
};

#endif /* ASTBUILDER_H_ */

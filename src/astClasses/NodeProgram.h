#ifndef NODEPROGRAM_H
#define NODEPROGRAM_H

#include<vector>
#include<memory>

#include "ASTNodeBase.h"
#include <algorithm>

class NodeProgram : public ASTNodeBase
{
    private:
        std::vector<std::shared_ptr<ASTNodeBase>> program;

    public:
        void addStatementToProgram(std::shared_ptr<ASTNodeBase> statement) {program.push_back(statement);}

        NodeProgram();
        virtual ~NodeProgram();

        virtual std::string toString()
        {
            std::string astText {"C++ AST: "};

            std::for_each(program.begin(), program.end(), [&astText](std::shared_ptr<ASTNodeBase> statement)
            {
                astText += statement->toString();
            });

            return astText;
        }
};

#endif // NODEPROGRAM_H

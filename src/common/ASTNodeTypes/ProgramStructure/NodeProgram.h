/**
 * @file   NodeProgram.h
 * @author Christopher Maier (cmaier.business@gmail.com)
 * @date   April 2015
 *
 * AST node of the YAGI program root node
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


#ifndef NODEPROGRAM_H
#define NODEPROGRAM_H

#include<vector>
#include<memory>

#include "../ASTNodeBase.h"

/**
 * AST node class of the YAGI program root node
 */
class NodeProgram: public ASTNodeBase<>
{
  private:
    /**
     * The set of statements that represent a YAGI program
     */
    std::vector<std::shared_ptr<ASTNodeBase<>>>program;

    public:

    /**
     * Default ctor
     */
    NodeProgram();

    /**
     * Default dtor
     */
    virtual ~NodeProgram();

    DEFINE_VISITABLE()

    /**
     * Adds a statement to the YAGI program
     */
    void addStatementToProgram(std::shared_ptr<ASTNodeBase<>> statement)
    {
      program.insert(std::begin(program), statement);
    }

    /**
     * Replaces a statement in the YAGI program with another one
     * @param statement The statement that is the replacement
     * @param idx The index of the statement that should be replaced
     */
    void replaceStatement(std::shared_ptr<ASTNodeBase<>> statement, int idx)
    {
      program[idx] = statement;
    }

    /**
     * Inserts a set of statements into the program structure
     * @param statements The set of statements to be inserted
     * @param idx The position of the insertion
     */
    void insertStatements(std::vector<std::shared_ptr<ASTNodeBase<>>> statements, int idx)
    {
      for (const auto& stmt : statements)
      {
        program.insert(std::begin(program)+idx, stmt);
        idx++;
      }
    }

    /**
     * Getter for the YAGI program
     * @return The YAGI program
     */
    const std::vector<std::shared_ptr<ASTNodeBase<> > >& getProgram() const
    {
      return program;
    }
  };

#endif // NODEPROGRAM_H

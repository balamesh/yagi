/*
 * InterpretationVisitor.h
 *
 *  Created on: Jul 9, 2014
 *      Author: cmaier
 */

#ifndef INTERPRETATIONVISITOR_H_
#define INTERPRETATIONVISITOR_H_

#include "../Database/DatabaseConnectorBase.h"
#include "../Database/DatabaseManager.h"
#include <memory>

#include "../../common/ASTNodeVisitorBase.h"
#include "../../common/ASTNodeTypes/Domains/NodeDomainStringElements.h"
#include "../../common/ASTNodeTypes/Declarations/FluentDecl/NodeFluentDecl.h"
#include "../../common/ASTNodeTypes/Declarations/FactDecl/NodeFactDecl.h"
#include "../../common/ASTNodeTypes/Identifier/NodeID.h"
#include "../../common/ASTNodeTypes/ProgramStructure/NodeProgram.h"
#include "../../common/ASTNodeTypes/DataTypes/NodeString.h"
#include "../../common/ASTNodeTypes/Domains/NodeDomainInteger.h"
#include "../../common/ASTNodeTypes/Domains/NodeDomainString.h"
#include "../../common/ASTNodeTypes/Declarations/FactDecl/NodeFactDecl.h"
#include "../../common/ASTNodeTypes/Statements/NodeFluentQuery.h"

using namespace yagi::database;
using namespace yagi::container;

class InterpretationVisitor: public ASTNodeVisitorBase,
    public Visitor<NodeFluentDecl>,
    public Visitor<NodeFactDecl>,
    public Visitor<NodeProgram>,
    public Visitor<NodeFluentQuery>
{
  private:
    std::string fluentDBDataToString(std::vector<std::vector<std::string>> data)
    {
      std::string str = "{";

      std::for_each(std::begin(data), std::end(data), [&str](const std::vector<std::string>& row)
      {
        str += "<";

        std::for_each(std::begin(row), std::end(row), [&str](const std::string& col)
            {
              str += "\"" + col + "\",";
            });

        str = str.substr(0,str.length()-1);
        str += ">, ";
      });

      if (str.length() > 1)
        return str.substr(0, str.length() - 1);
      else
        return "[EMPTY]";
    }

  public:
    InterpretationVisitor();
    virtual ~InterpretationVisitor();

    Any visit(NodeProgram& program)
    {
      std::for_each(program.getProgram().begin(), program.getProgram().end(),
          [this](std::shared_ptr<ASTNodeBase<>> stmt)
          {
            stmt->accept(*this);
          });

      return Any { };
    }

    Any visit(NodeFluentDecl& fluentDecl)
    {
      auto db = DatabaseManager::getInstance().getMainDB();
      db.get()->createTable(fluentDecl);
      return Any { };
    }

    Any visit(NodeFactDecl& factDecl)
    {
      auto db = DatabaseManager::getInstance().getMainDB();
      db.get()->createTable(factDecl);
      return Any { };
    }

    Any visit(NodeFluentQuery& fluentQuery)
    {
      auto db = DatabaseManager::getInstance().getMainDB();
      auto fluentName = fluentQuery.getFluentToQueryName().get()->getId();

      if (!db.get()->existsTable(fluentName))
      {
        std::cout << "<<<< Fluent '" + fluentName + "' does not exist!" << std::endl;
      }
      else
      {
        auto fluentState = db.get()->select(fluentName);
        auto str = fluentDBDataToString(fluentState);

        std::cout << "<<<< " << fluentName << " = " << str << std::endl;
      }

      return Any { };
    }
};

#endif /* INTERPRETATIONVISITOR_H_ */

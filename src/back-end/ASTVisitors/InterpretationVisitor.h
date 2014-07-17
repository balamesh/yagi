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
#include "../SQLGenerator.h"
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
#include "../../common/ASTNodeTypes/Statements/NodeIDAssignment.h"

using namespace yagi::database;
using namespace yagi::container;

class InterpretationVisitor: public ASTNodeVisitorBase,
    public Visitor<NodeFluentDecl>,
    public Visitor<NodeFactDecl>,
    public Visitor<NodeProgram>,
    public Visitor<NodeFluentQuery>,
    public Visitor<NodeIDAssignment>
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
        return str.substr(0, str.length() - 2) + "}";
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
      db->executeNonQuery(SQLGenerator::getInstance().createTableFromFluent(fluentDecl));
      return Any { };
    }

    Any visit(NodeFactDecl& factDecl)
    {
      auto db = DatabaseManager::getInstance().getMainDB();
      db->executeNonQuery(SQLGenerator::getInstance().createTableFromFact(factDecl));

      //store in db that it is a fact
      if (!db->executeQuery(
          SQLGenerator::getInstance().existsTable(SQLGenerator::getInstance().FACTS_TABLE_NAME_)).size())
      {
        db->executeNonQuery(SQLGenerator::getInstance().getSqlStringCreateFactsTable());
      }
      db->executeNonQuery(SQLGenerator::getInstance().getSqlStringAddFact(factDecl));

      return Any { };
    }

    Any visit(NodeFluentQuery& fluentQuery)
    {
      auto db = DatabaseManager::getInstance().getMainDB();
      auto fluentName = fluentQuery.getFluentToQueryName().get()->getId();

      if (!db->executeQuery(SQLGenerator::getInstance().existsTable(fluentName)).size())
      {
        std::cout << "<<<< Fluent/Fact '" + fluentName + "' does not exist!" << std::endl;
      }
      else
      {
        auto fluentState = db->executeQuery(SQLGenerator::getInstance().selectAll(fluentName));
        auto str = fluentDBDataToString(fluentState);

        std::cout << "<<<< " << fluentName << " = " << str << std::endl;
      }

      return Any { };
    }

    Any visit(NodeIDAssignment& fluentAss)
    {
      auto db = DatabaseManager::getInstance().getMainDB();
      auto lhs = fluentAss.getFluentName().get()->getId();
      auto rhs = fluentAss.getSetExpr();
      auto op = fluentAss.getOperator();

      if (op->getOperator() == SetExprOperator::Unknown)
      {
        throw std::runtime_error("Unknown set expr. assign operator!");
      }

      if (op->getOperator() == SetExprOperator::Assign)
      {
        DatabaseManager::getInstance().getMainDB()->executeNonQuery(
            SQLGenerator::getInstance().getSqlStringClearTable(lhs));
      }

      std::vector<std::string> sqlStrings;

      //Simplest case: rhs is a <set>
      if (auto set = std::dynamic_pointer_cast<NodeSet>(rhs->getRhs()))
      {
        sqlStrings = SQLGenerator::getInstance().getSqlStringsForFluentSetAssign(lhs, set,
            op->getOperator());

      } //It can also be another ID, i.e. another fluent
      else if (auto id = std::dynamic_pointer_cast<NodeID>(rhs->getRhs()))
      {
        auto colCount = DatabaseManager::getInstance().getMainDB()->executeQuery(
            SQLGenerator::getInstance().getSqlStringNumberOfColumnsInTable(id->getId())).size();

        sqlStrings = SQLGenerator::getInstance().getSqlStringsForFluentFluentAssign(lhs,
            id->getId(), op->getOperator(), colCount);
      }

      std::for_each(std::begin(sqlStrings), std::end(sqlStrings), [](const std::string& stmt)
      {
        DatabaseManager::getInstance().getMainDB()->executeNonQuery(stmt);
      });

      return Any { };
    }
};

#endif /* INTERPRETATIONVISITOR_H_ */

#include <iostream>
#include <cstring>
#include <string>
#include <vector>
#include <assert.h>
#include <algorithm>
#include <memory>
#include <fstream>
#include <streambuf>
#include <readline/readline.h>
#include <readline/history.h>

#include "astClasses/YAGICallbackConnector.h"
#include "../common/ASTNodeTypes/ASTNodeBase.h"
#include "astVisitors/ToStringVisitor.h"
#include "../back-end/TypeCheckVisitor.h"
#include "ANTLRParser.h"

//#pragma GCC diagnostic error "-Wuninitialized"
//    foo(a);         /* error is given for this one */
//#pragma GCC diagnostic push
//#pragma GCC diagnostic ignored "-Wuninitialized"
//    foo(b);         /* no diagnostic for this one */
//#pragma GCC diagnostic pop
//   foo(c);         /* error is given for this one */
//#pragma GCC diagnostic pop
//    foo(d);         /* depends on command line options *

bool execute(const std::string&);
std::string parseFileName(const std::string&);

int main(int argc, char * argv[])
{
  YAGICallbackConnector::connectCallbacks();

  std::string line;
  do
  {
    line = readline("YAGI>> ");
    add_history(line.c_str());
  }
  while (execute(line));

  return EXIT_SUCCESS;
}

bool isPrefixOf(const std::string& potentialPrefix, const std::string& text)
{
  auto res = std::mismatch(std::begin(potentialPrefix), std::end(potentialPrefix),
      std::begin(text));

  return (res.first == std::end(potentialPrefix));
}

bool execute(const std::string& line)
{
  if (line == "exit")
  {
    return false;
  }

  std::shared_ptr<ASTNodeBase<>> ast;

  if (isPrefixOf(std::string { "import" }, line))
  {
    std::string fname = parseFileName(line);

    try
    {
      ast = ANTLRParser::parseYAGICodeFromFile(fname);
    }
    catch (std::runtime_error& error)
    {
      std::cout << "[INTERNAL ERROR]: " << error.what() << std::endl;
      return true;
    }
  }
  else
  {
    try
    {
      ast = ANTLRParser::parseYAGICodeFromText(line);
    }
    catch (std::runtime_error& error)
    {
      std::cout << "[INTERNAL ERROR]: " << error.what() << std::endl;
      return true;
    }
  }

  //Invalid YAGI code...
  if (ast == nullptr) return true;

  ToStringVisitor toStringVisitor;
  ast->accept(toStringVisitor);
  std::cout << "C++ AST: " << toStringVisitor.getAstString() << std::endl;

  TypeCheckVisitor typeCheck;
  ast->accept(typeCheck);

  if (typeCheck.hasTypeError())
    std::cout << "Typechecker: " << typeCheck.getErrorText() << std::endl;
  else
    std::cout << "Typechecker: No typechecking errors! :-)" << std::endl;

  ASTBuilder::getInstance().reset();

  return true;
}

std::string parseFileName(const std::string& importCmd)
{
  int first = importCmd.find_first_of('\"');
  int last = importCmd.find_last_of('\"');

  return importCmd.substr(first + 1, last - first - 1);
}

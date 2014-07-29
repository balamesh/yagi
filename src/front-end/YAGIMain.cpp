#include <iostream>
#include <cstring>
#include <string>
#include <vector>
#include <assert.h>
#include <algorithm>
#include <memory>
#include <fstream>
#include <streambuf>
#include <signal.h>
#include <readline/readline.h>
#include <readline/history.h>

#include "astClasses/YAGICallbackConnector.h"
#include "../common/ASTNodeTypes/ASTNodeBase.h"
#include "astVisitors/ToStringVisitor.h"
#include "astVisitors/TypeCheckVisitor.h"
#include "../back-end/ASTVisitors/MainInterpretationVisitor.h"
#include "ANTLRParser.h"
#include "../back-end/Formulas/FormulaEvaluator.h"
#include "../back-end/ASTVisitors/RewritingVisitor.h"

using namespace yagi::formula;
using namespace yagi::execution;

//#pragma GCC diagnostic error "-Wuninitialized"
//    foo(a);         /* error is given for this one */
//#pragma GCC diagnostic push
//#pragma GCC diagnostic ignored "-Wuninitialized"
//    foo(b);         /* no diagnostic for this one */
//#pragma GCC diagnostic pop
//   foo(c);         /* error is given for this one */
//#pragma GCC diagnostic pop
//    foo(d);         /* depends on command line options *

bool execute(const std::string&, bool);
std::string parseFileName(const std::string&);
bool isFromFile(const std::string&);
bool isExit(const std::string&);
void displayWelcome();

std::vector<std::string> lines;
bool sigTriggered = true;
void executeProgram(int sig)
{
  sigTriggered = true;

  std::string program = "";
  std::for_each(std::begin(lines), std::end(lines), [&program](const std::string& line)
  { program += " " + line;});

  add_history(program.c_str());

  execute(program, false);

  lines.clear();
}

int main(int argc, char * argv[])
{
  YAGICallbackConnector::connectCallbacks();
  signal(SIGINT, executeProgram);
  displayWelcome();

  std::string line;

  do
  {
    char* buffer = nullptr;
    if (sigTriggered)
    {
      buffer = readline("YAGI>> ");
      sigTriggered = false;
    }
    else
      buffer = readline(".......");

    if (buffer == nullptr)
      break;
    else
      line = buffer;

    lines.push_back(line);

    if (isExit(line))
      break;

    if (isFromFile(line))
    {
      std::string fname = parseFileName(line);
      execute(fname, true);
      sigTriggered = true;
    }
  }
  while (true);

  return EXIT_SUCCESS;
}

bool isExit(const std::string& line)
{
  return (line == "exit"); //todo: trim etc. to make it more robust
}

bool isPrefixOf(const std::string& potentialPrefix, const std::string& text)
{
  auto res = std::mismatch(std::begin(potentialPrefix), std::end(potentialPrefix),
      std::begin(text));

  return (res.first == std::end(potentialPrefix));
}

bool isFromFile(const std::string& line)
{
  return isPrefixOf(std::string { "import" }, line); //TODO: rethink that!
}

bool execute(const std::string& line, bool isFileName)
{
  std::cout << "(working...)" << std::endl << std::flush;

  std::shared_ptr<ASTNodeBase<>> ast;

  if (isFileName)
  {
    try
    {
      ast = ANTLRParser::parseYAGICodeFromFile(line, true);
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
      ast = ANTLRParser::parseYAGICodeFromText(line, true);
    }
    catch (std::runtime_error& error)
    {
      std::cout << "[INTERNAL ERROR]: " << error.what() << std::endl;
      return true;
    }
  }

  //Invalid YAGI code...
  if (ast == nullptr)
    return true;

  ASTBuilder::getInstance().reset();

  auto prog = std::dynamic_pointer_cast<NodeProgram>(ast);
  if (!prog)
    throw std::runtime_error("AST root is no program!");

  auto stmts = prog->getProgram();
  for (const auto& stmt : stmts)
  {
    ToStringVisitor toStringVisitor;
    std::cout << "C++ AST: " << stmt->accept(toStringVisitor).get<std::string>() << std::endl;

    TypeCheckVisitor typeCheck;
    stmt->accept(typeCheck);

    if (typeCheck.hasTypeError())
    {
      std::string errorText = "";
      auto errors = typeCheck.getErrorTexts();
      std::for_each(std::begin(errors), std::end(errors), [&errorText](const std::string& error)
      {
        errorText += "[ERROR] " + error + "\n";
      });

      std::cout << "Typechecker: " << errorText << std::endl;
      return true;
    }

//    RewritingVisitor rewriter;
//    auto newStmt = stmt->accept(rewriter);
//
    MainInterpretationVisitor interpreter;
//    if (newStmt && !newStmt.empty())
//    {
//      auto rewrittenStmt = newStmt.get<std::shared_ptr<NodeForLoop>>();
//      ToStringVisitor toStringVisitorAfterRewrite;
//      std::cout << "C++ AST (Rewritten): "
//          << rewrittenStmt->accept(toStringVisitorAfterRewrite).get<std::string>() << std::endl;
//
//      rewrittenStmt->accept(interpreter);
//    }
//    else
//    {
      stmt->accept(interpreter);
//    }

  }

  return true;
}

std::string parseFileName(const std::string& importCmd)
{
  int first = importCmd.find_first_of('\"');
  int last = importCmd.find_last_of('\"');

  return importCmd.substr(first + 1, last - first - 1);
}

void displayWelcome()
{
  std::cout << "*************************************************************" << std::endl;
  std::cout << "*Welcome to the YAGI Shell!                                 *" << std::endl;
  std::cout << "*You can enter multiline statements by pressing [ENTER].    *" << std::endl;
  std::cout << "*Press [CTRL+C] to execute the entered command              *" << std::endl;
  std::cout << "*Press [CTRL+D] (or enter 'exit') to quit the application   *" << std::endl;
  std::cout << "*************************************************************" << std::endl;
}

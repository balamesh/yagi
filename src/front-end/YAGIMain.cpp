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
#include <exception>
#include <readline/readline.h>
#include <readline/history.h>
#include <tclap/CmdLine.h>

#include "astClasses/YAGICallbackConnector.h"
#include "../common/ASTNodeTypes/ASTNodeBase.h"
#include "astVisitors/ToStringVisitor.h"
#include "astVisitors/TypeCheckVisitor.h"
#include "../back-end/ASTVisitors/MainInterpretationVisitor.h"
#include "ANTLRParser.h"
#include "../back-end/Formulas/FormulaEvaluator.h"
#include "../back-end/ASTVisitors/RewritingVisitor.h"
#include "../utils/CommandLineArgsContainer.h"
#include "../utils/StringManipulationHelper.h"

#include <chrono>

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

void parseCommandLineArgs(int argc, char* argv[]);
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

  try
  {
    parseCommandLineArgs(argc, argv);
  }
  catch (const std::exception& ex)
  {
    std::cerr << "Can't parse command line args! Error: " + std::string { ex.what() } << std::endl;
    exit(EXIT_FAILURE);
  }

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
      lines.clear();
    }
  }
  while (true);

  return EXIT_SUCCESS;
}

void parseCommandLineArgs(int argc, char* argv[])
{
  TCLAP::CmdLine cmd("YAGI Interpreter Shell", ' ', "1.0");
  TCLAP::SwitchArg debugMsg("s", "showDebugMsg", "Shows all the debug messages during runtime.",
  false);
  cmd.add(debugMsg);

  TCLAP::SwitchArg noMsg("n", "showNoMsg", "Shows no messages at all. Primarily for runtime measurements.",
    false);
  cmd.add(noMsg);

  cmd.parse(argc, argv);

  yagi::container::CommandLineArgsContainer::getInstance().setShowDebugMessages(
      debugMsg.getValue());

  yagi::container::CommandLineArgsContainer::getInstance().setShowNoMessages(
       noMsg.getValue());
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

bool isSuffixOf(const std::string& potentialSuffix, const std::string& text)
{
  auto res = std::mismatch(potentialSuffix.rbegin(), potentialSuffix.rend(),
      text.rbegin());

  return (res.first == potentialSuffix.rend());
}

bool isFromFile(const std::string& line)
{
  std::string tmp{line};

  //c++11 regex is still not available in this compiler version, so this must suffice for the moment.
  return isPrefixOf(std::string { "import(" }, trim(tmp)) && isSuffixOf(std::string{");"}, trim(tmp));
}

bool execute(const std::string& line, bool isFileName)
{
  std::cout << "(working...)" << std::endl << std::flush;

  std::shared_ptr<ASTNodeBase<>> ast;

  if (isFileName)
  {
    try
    {
      ast = ANTLRParser::parseYAGICodeFromFile(line,
          yagi::container::CommandLineArgsContainer::getInstance().getShowDebugMessages());
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
      ast = ANTLRParser::parseYAGICodeFromText(line,
          yagi::container::CommandLineArgsContainer::getInstance().getShowDebugMessages());
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

  typedef std::chrono::high_resolution_clock Clock;
  auto t1 = Clock::now();

  for (const auto& stmt : stmts)
  {
    if (yagi::container::CommandLineArgsContainer::getInstance().getShowDebugMessages())
    {
      ToStringVisitor toStringVisitor;
      std::cout << "C++ AST: " << stmt->accept(toStringVisitor).get<std::string>() << std::endl;
    }

    TypeCheckVisitor typeCheck;
    stmt->accept(typeCheck);

    if (typeCheck.hasWarnings())
    {
      std::string warningText = "";
      auto warnings = typeCheck.getWarningTexts();
      for (const auto& warning : warnings)
      {
        warningText += "[WARNING] " + warning + "\n";
      }

      std::cout << warningText << std::endl;
    }

    if (typeCheck.hasTypeError())
    {
      std::string errorText = "";
      auto errors = typeCheck.getErrorTexts();
      for (const auto& error : errors)
      {
        errorText += "[ERROR] " + error + "\n";
      }

      std::cout << errorText << std::endl;
      return true;
    }

    RewritingVisitor rewriter;
    auto newStmt = stmt->accept(rewriter);

    MainInterpretationVisitor interpreter;
    auto rewrittenStmt = newStmt ? newStmt.get<std::shared_ptr<NodeForLoop>>() : nullptr;

    if (rewrittenStmt)
    {
      if (yagi::container::CommandLineArgsContainer::getInstance().getShowDebugMessages())
      {
        ToStringVisitor toStringVisitorAfterRewrite;
        std::cout << "C++ AST (Rewritten): "
            << rewrittenStmt->accept(toStringVisitorAfterRewrite).get<std::string>() << std::endl;
      }

      try
      {
        rewrittenStmt->accept(interpreter);
      }
      catch (const std::exception& ex)
      {
        std::cerr << "ERROR: " << ex.what() << std::endl;
      }
    }
    else
    {
      try
      {
        stmt->accept(interpreter);
      }
      catch (const std::exception& ex)
      {
        std::cerr << "UNEXPECTED ERROR: " << ex.what() << std::endl;
      }
    }
  }

  auto t2 = Clock::now();
  auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(t2-t1);
  std::cout << "Execution Time [ms]: " << ms.count() << std::endl;


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
  std::cout << "*Write 'import(\"myFile.txt\");' to load a YAGI src file      *" << std::endl;
  std::cout << "*************************************************************" << std::endl;
}

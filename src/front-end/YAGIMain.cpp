/**
 * @file   YAGIMain.cpp
 * @author Christopher Maier (cmaier@student.tugraz.at)
 * @date   January 2015
 *
 * The main entry point of the YAGI interpreter commandline.
 */

#include <readline/history.h>
#include <readline/readline.h>
#include <readline/rltypedefs.h>
#include <tclap/CmdLine.h>
#include <tclap/SwitchArg.h>
#include <tclap/ValueArg.h>
#include <algorithm>
#include <chrono>
#include <cstdbool>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <iterator>
#include <memory>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

#include "../back-end/ASTVisitors/MainInterpretationVisitor.h"
#include "../back-end/ASTVisitors/RewritingVisitor.h"
#include "../common/ASTNodeTypes/ASTNodeBase.h"
#include "../common/ASTNodeTypes/ProgramStructure/NodeInclude.h"
#include "../common/ASTNodeTypes/ProgramStructure/NodeProgram.h"
#include "../common/ASTNodeTypes/Statements/NodeForLoop.h"
#include "../utils/Any.h"
#include "../utils/CommandLineArgsContainer.h"
#include "../utils/StringManipulationHelper.h"
#include "astClasses/ASTBuilder.h"
#include "astClasses/YAGICallbackConnector.h"
#include "astVisitors/ToStringVisitor.h"
#include "astVisitors/TypeCheckVisitor.h"
#include "ANTLRParser.h"

using std::ofstream;
using namespace yagi::formula;
using namespace yagi::execution;

void parseCommandLineArgs(int argc, char* argv[]);
bool execute(const std::string&, bool);
std::string parseFileName(const std::string&);
bool isFromFile(const std::string&);
bool isExit(const std::string&);
void displayWelcome();

/**
 * Callback method for readline that handles multine YAGI code.
 * @return success
 */
int addMultilineCommand(int, int)
{
  printf("\n.......");
  rl_done = 0;
  return 0;
}

/**
 * Main method of the YAGI interpreter shell
 * @param argc Number of parameters
 * @param argv Parameters
 * @return Success or error
 */
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

  rl_command_func_t addMultilineCommand;
  rl_bind_keyseq("\\C-n", addMultilineCommand);

  YAGICallbackConnector::connectCallbacks();

  displayWelcome();

  //if a filename was passed run its content directly
  if (!yagi::container::CommandLineArgsContainer::getInstance().getInputFileName().empty())
  {
    execute(yagi::container::CommandLineArgsContainer::getInstance().getInputFileName(), true);

    if (yagi::container::CommandLineArgsContainer::getInstance().measurePerformance())
    {
      return EXIT_SUCCESS;
    }
  }

  std::string line;

  do
  {
    char* buffer = nullptr;

    buffer = readline("YAGI>> ");

    if (buffer == nullptr)
      break;
    else
    {
      line = std::string(buffer);

      if (isExit(line))
        break;

      add_history(line.c_str());

      if (isFromFile(line))
      {
        std::string fname = parseFileName(line);

        execute(fname, true);
        continue;
      }

      execute(line, false);
    }
  }
  while (true);

  return EXIT_SUCCESS;
}

/**
 * Parses command line args using TCLAP.
 * @param argc Number of args
 * @param argv Arguments
 */
void parseCommandLineArgs(int argc, char* argv[])
{
  TCLAP::CmdLine cmd("YAGI Interpreter Shell", ' ', "1.0");
  TCLAP::SwitchArg debugMsg("s", "showDebugMsg", "Shows all the debug messages during runtime.",
  false);
  cmd.add(debugMsg);

  TCLAP::SwitchArg doPerfMeas("p", "perf", "Measure and save performance stats.", false);
  cmd.add(doPerfMeas);

  TCLAP::ValueArg<std::string> useThisFileAsInput("f", "ifile", "Use this YAGI file as input.",
  false, "", "");
  cmd.add(useThisFileAsInput);

  TCLAP::ValueArg<std::string> useThisFileAsOutput("o", "ofile",
      "Use this YAGI file to store perf outputs.",
      false, "", "");
  cmd.add(useThisFileAsOutput);

  cmd.parse(argc, argv);

  yagi::container::CommandLineArgsContainer::getInstance().setShowDebugMessages(
      debugMsg.getValue());

  yagi::container::CommandLineArgsContainer::getInstance().setMeasurePerformance(
      doPerfMeas.getValue());

  yagi::container::CommandLineArgsContainer::getInstance().setInputFileName(
      useThisFileAsInput.getValue());

  yagi::container::CommandLineArgsContainer::getInstance().setOutputFileName(
      useThisFileAsOutput.getValue());
}

/**
 * Checks if an exit command has been entered
 * @param line The line that should be checked
 * @return true If exit, else otherwise
 */
bool isExit(const std::string& line)
{
  return (line == "exit"); //todo: trim etc. to make it more robust
}

/**
 * Checks if a string is prefix of another string
 * @param potentialPrefix The potential prefix
 * @param text The text to check
 * @return True If prefix, false otherwise
 */
bool isPrefixOf(const std::string& potentialPrefix, const std::string& text)
{
  auto res = std::mismatch(std::begin(potentialPrefix), std::end(potentialPrefix),
      std::begin(text));

  return (res.first == std::end(potentialPrefix));
}

/**
 * Checks if a string is a suffix of another string
 * @param potentialSuffix Potential suffix string
 * @param text Text to be checked
 * @return true If suffix, false otherwise
 */
bool isSuffixOf(const std::string& potentialSuffix, const std::string& text)
{
  auto res = std::mismatch(potentialSuffix.rbegin(), potentialSuffix.rend(), text.rbegin());

  return (res.first == potentialSuffix.rend());
}

/**
 * Checks if the input command is a 'load from file' command
 * @param line Input command to check
 * @return true If it is 'import' command, false otherwise
 */
bool isFromFile(const std::string& line)
{
  std::string tmp { line };

  //c++11 regex is still not available in this compiler version, so this must suffice for the moment.
  return isPrefixOf(std::string { "import(" }, trim(tmp))
      && isSuffixOf(std::string { ");" }, trim(tmp));
}

/**
 * Executes a YAGI program.
 * @param line The program to execute
 * @param isFileName Flag that indicates whether or not it line is a filename
 * @return True if execution successful, false otherwise
 */
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

  //check for imports: if any import nodes present replace the node with the important
  //AST from the file
  auto stmts = prog->getProgram();

  int idx = 0;
  for (const auto& stmt : stmts)
  {
    if (auto include = std::dynamic_pointer_cast<NodeInclude>(stmt))
    {
      try
      {
        auto includeAst = ANTLRParser::parseYAGICodeFromFile(include->getIncludeFileName(),
            yagi::container::CommandLineArgsContainer::getInstance().getShowDebugMessages());

        auto includedProg = std::dynamic_pointer_cast<NodeProgram>(includeAst);
        if (!includedProg)
          throw std::runtime_error("Included AST root is no program!");

        prog->insertStatements(includedProg->getProgram(), idx);
      }
      catch (std::runtime_error& error)
      {
        std::cout << "[INTERNAL ERROR]: " << error.what() << std::endl;
        return true;
      }
    }

    idx++;
  }

  stmts = prog->getProgram();

  typedef std::chrono::high_resolution_clock Clock;
  auto t1 = Clock::now();

  if (yagi::container::CommandLineArgsContainer::getInstance().measurePerformance())
  {
    auto fileName = yagi::container::CommandLineArgsContainer::getInstance().getOutputFileName();
    if (fileName.empty())
    {
      fileName = "perfStats.txt";
    }

    ofstream perfStatsFile;
    perfStatsFile.open(fileName, std::ofstream::app);
    perfStatsFile << "Starting testcase..." << std::endl;
    perfStatsFile.close();
  }

  bool success = true;
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
        auto ret = rewrittenStmt->accept(interpreter);

        if (ret.hasType<bool>() && !ret.get<bool>())
        {
          success = false;
        }

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
        auto ret = stmt->accept(interpreter);

        if (ret.hasType<bool>() && !ret.get<bool>())
        {
          success = false;
        }
      }
      catch (const std::exception& ex)
      {
        std::cerr << "UNEXPECTED ERROR: " << ex.what() << std::endl;
      }
    }
  }

  if (yagi::container::CommandLineArgsContainer::getInstance().measurePerformance())
  {
    auto t2 = Clock::now();
    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1);

    auto fileName = yagi::container::CommandLineArgsContainer::getInstance().getOutputFileName();
    if (fileName.empty())
    {
      fileName = "perfStats.txt";
    }

    ofstream perfStatsFile;
    perfStatsFile.open(fileName, std::ofstream::app);
    perfStatsFile << (success ? 1 : 0) << ";" << ms.count() << "ms" << std::endl;
    perfStatsFile.close();
  }

  return true;
}

/**
 * Parses the filename from an import command
 * @param importCmd The import command string
 * @return The filename
 */
std::string parseFileName(const std::string& importCmd)
{
  int first = importCmd.find_first_of('\"');
  int last = importCmd.find_last_of('\"');

  return importCmd.substr(first + 1, last - first - 1);
}

/**
 * Displays the YAGI welcome message.
 */
void displayWelcome()
{
  std::cout << "***********************************************************" << std::endl;
  std::cout << "*Welcome to the YAGI Shell!                               *" << std::endl;
  std::cout << "*You can enter multiline statements by pressing [ctrl-n]. *" << std::endl;
  std::cout << "*Press [ENTER] to execute the entered command             *" << std::endl;
  std::cout << "*Enter 'exit' to quit the application                     *" << std::endl;
  std::cout << "*Write 'import(\"myFile.txt\");' to load a YAGI src file    *" << std::endl;
  std::cout << "***********************************************************" << std::endl;
}

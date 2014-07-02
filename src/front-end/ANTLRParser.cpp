/*
 * ANTLRParser.cpp
 *
 *  Created on: Jul 2, 2014
 *      Author: cmaier
 */

#include "ANTLRParser.h"

std::shared_ptr<ASTNodeBase<>> ANTLRParser::parseYAGICodeFromFile(const std::string& file)
{
  pANTLR3_INPUT_STREAM input = nullptr;

  input = antlr3FileStreamNew((pANTLR3_UINT8) file.c_str(), ANTLR3_ENC_8BIT);

  if (input == nullptr)
  {
    throw std::runtime_error("Can't load file '" + file + "'!");
  }

  return parse(input);
}

std::shared_ptr<ASTNodeBase<>> ANTLRParser::parseYAGICodeFromText(const std::string& yagiCode)
{
  pANTLR3_INPUT_STREAM input = nullptr;
  using BufferType = std::unique_ptr<char[], std::function<void(char*)>>;
  BufferType antlrInputBuffer;

  antlrInputBuffer = BufferType(strdup(yagiCode.c_str()), [](char* ptr)
  { free(ptr);});

  input = antlr3StringStreamNew((unsigned char*) antlrInputBuffer.get(),
  ANTLR3_ENC_8BIT, strlen(antlrInputBuffer.get()), (unsigned char*) "yagi-shell-input");

  return parse(input);
}

std::shared_ptr<ASTNodeBase<>> ANTLRParser::parse(const pANTLR3_INPUT_STREAM& input)
{
  pYAGILexer lxr = YAGILexerNew(input);
  if (lxr == nullptr)
  {
    throw std::runtime_error("Can't create lexer!");
  }

  pANTLR3_COMMON_TOKEN_STREAM tstream = antlr3CommonTokenStreamSourceNew(
  ANTLR3_SIZE_HINT, TOKENSOURCE(lxr));

  if (tstream == nullptr)
  {
    throw std::runtime_error("Can't create token stream!");
  }

  pYAGIParser psr = YAGIParserNew(tstream);
  if (psr == nullptr)
  {
    throw std::runtime_error("Can't create parser!");
  }

  auto langAST = psr->program(psr);

  pYAGITreeWalker treePsr = nullptr;
  pANTLR3_COMMON_TREE_NODE_STREAM nodes = nullptr;

  if (psr->pParser->rec->state->errorCount > 0)
  {
    return nullptr;
  }
  else
  {
    std::cout << "C AST: " << langAST.tree->toStringTree(langAST.tree)->chars << std::endl;

    nodes = antlr3CommonTreeNodeStreamNewTree(langAST.tree, ANTLR3_SIZE_HINT);

    treePsr = YAGITreeWalkerNew(nodes);
    treePsr->program(treePsr);

    return ASTBuilder::getInstance().getAST();
  }

}


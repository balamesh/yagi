/*
 * ANTLRParser.cpp
 *
 *  Created on: Jul 2, 2014
 *      Author: cmaier
 */

#include "ANTLRParser.h"

std::shared_ptr<ASTNodeBase<>> ANTLRParser::parseYAGICodeFromFile(const std::string& file,
    bool printCAST)
{
  using InputStreamType = std::unique_ptr<std::remove_pointer<pANTLR3_INPUT_STREAM>::type, std::function<void(pANTLR3_INPUT_STREAM)>>;
  InputStreamType input = InputStreamType(
      antlr3FileStreamNew((pANTLR3_UINT8) file.c_str(), ANTLR3_ENC_8BIT),
      [](pANTLR3_INPUT_STREAM stream)
      { stream->close(stream);});

  if (!input)
  {
    throw std::runtime_error("Can't load file '" + file + "'!");
  }

  return parse(input.get(), printCAST);
}

std::shared_ptr<ASTNodeBase<>> ANTLRParser::parseYAGICodeFromText(const std::string& yagiCode,
    bool printCAST)
{

  using BufferType = std::unique_ptr<char[], std::function<void(char*)>>;
  BufferType antlrInputBuffer = BufferType(strdup(yagiCode.c_str()), [](char* ptr)
  { free(ptr);});

  using InputStreamType = std::unique_ptr<std::remove_pointer<pANTLR3_INPUT_STREAM>::type, std::function<void(pANTLR3_INPUT_STREAM)>>;
  InputStreamType input = InputStreamType(
      antlr3StringStreamNew((unsigned char*) antlrInputBuffer.get(),
      ANTLR3_ENC_8BIT, strlen(antlrInputBuffer.get()), (unsigned char*) "yagi-shell-input"),
      [](pANTLR3_INPUT_STREAM stream)
      { stream->close(stream);});

  return parse(input.get(), printCAST);
}

std::shared_ptr<ASTNodeBase<>> ANTLRParser::parse(const pANTLR3_INPUT_STREAM& input,
    bool printCAST)
{
  using LexerType = std::unique_ptr<std::remove_pointer<pYAGILexer>::type, std::function<void(pYAGILexer)>>;
  LexerType lxr = LexerType(YAGILexerNew(input), [](pYAGILexer lxr)
  { lxr->free(lxr);});

  if (!lxr)
  {
    throw std::runtime_error("Can't create lexer!");
  }

  using StreamType = std::unique_ptr<std::remove_pointer<pANTLR3_COMMON_TOKEN_STREAM>::type, std::function<void(pANTLR3_COMMON_TOKEN_STREAM)>>;
  StreamType tstream = StreamType(antlr3CommonTokenStreamSourceNew(
  ANTLR3_SIZE_HINT, TOKENSOURCE(lxr)), [](pANTLR3_COMMON_TOKEN_STREAM stream)
  { stream->free(stream);});

  if (!tstream)
  {
    throw std::runtime_error("Can't create token stream!");
  }

  using ParserType = std::unique_ptr<std::remove_pointer<pYAGIParser>::type, std::function<void(pYAGIParser)>>;
  ParserType psr = ParserType(YAGIParserNew(tstream.get()), [](pYAGIParser psr)
  { psr->free(psr);});

  if (!psr)
  {
    throw std::runtime_error("Can't create parser!");
  }

  auto langAST = psr.get()->program(psr.get());

  using TreeWalkerType = std::unique_ptr<std::remove_pointer<pYAGITreeWalker>::type, std::function<void(pYAGITreeWalker)>>;
  using NodeStreamType = std::unique_ptr<std::remove_pointer<pANTLR3_COMMON_TREE_NODE_STREAM>::type, std::function<void(pANTLR3_COMMON_TREE_NODE_STREAM)>>;

  TreeWalkerType treePsr = nullptr;
  NodeStreamType nodes = nullptr;

  if (psr->pParser->rec->state->errorCount > 0)
  {
    return nullptr;
  }
  else
  {
    if (printCAST)
    {
      std::cout << "C AST: " << langAST.tree->toStringTree(langAST.tree)->chars << std::endl;
    }

    nodes = NodeStreamType(antlr3CommonTreeNodeStreamNewTree(langAST.tree, ANTLR3_SIZE_HINT),
        [](pANTLR3_COMMON_TREE_NODE_STREAM nodeStream)
        { nodeStream->free(nodeStream);});

    treePsr = TreeWalkerType(YAGITreeWalkerNew(nodes.get()), [](pYAGITreeWalker walker)
    { walker->free(walker);});
    treePsr.get()->program(treePsr.get());

    return ASTBuilder::getInstance().getAST();
  }

}


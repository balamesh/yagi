/**
 * @file   NodeInclude.h
 * @author Christopher Maier (cmaier.business@gmail.com)
 * @date   April 2015
 *
 * AST node for the include statement
 */

#ifndef NODEINCLUDE_H_
#define NODEINCLUDE_H_

#include <string>
#include "../ASTNodeBase.h"

/**
 * AST node class for the include statement
 */
class NodeInclude: public ASTNodeBase<>
{
  private:
    /**
     * The YAGI file to be included
     */
    std::string includeFileName_;

  public:
    DEFINE_VISITABLE()

    /**
     * Default ctor
     */
    NodeInclude();

    /**
     * Default dtor
     */
    virtual ~NodeInclude();

    /**
     * Getter for the include filename
     * @return The YAGI file to be included
     */
    const std::string& getIncludeFileName() const
    {
      return includeFileName_;
    }

    /**
     * Setter for the include file name
     * @param includeFileName The YAGI file to be included
     */
    void setIncludeFileName(const std::string& includeFileName)
    {
      //strip trailing and leading " if neccessary
      if (includeFileName[0] == '"' && includeFileName[includeFileName.size() - 1] == '"')
      {
        includeFileName_ = includeFileName.substr(1, includeFileName.size() - 2);
      }
      else
      {
        includeFileName_ = includeFileName;
      }
    }
};

#endif /* NODEINCLUDE_H_ */

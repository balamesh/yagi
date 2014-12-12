/*
 * NodeInclude.h
 *
 *  Created on: Dec 12, 2014
 *      Author: cmaier
 */

#ifndef NODEINCLUDE_H_
#define NODEINCLUDE_H_

#include <string>
#include "../ASTNodeBase.h"

class NodeInclude: public ASTNodeBase<>
{
  private:
    std::string includeFileName_;

  public:
    DEFINE_VISITABLE()
    NodeInclude();
    virtual ~NodeInclude();

    const std::string& getIncludeFileName() const
    {
      return includeFileName_;
    }

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

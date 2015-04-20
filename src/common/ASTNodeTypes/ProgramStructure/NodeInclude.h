/**
 * @file   NodeInclude.h
 * @author Christopher Maier (cmaier.business@gmail.com)
 * @date   April 2015
 *
 * AST node for the include statement
 */

/*
 This file is part of YAGI.

 YAGI is free software; you can redistribute it and/or
 modify it under the terms of the GNU Lesser General Public
 License as published by the Free Software Foundation; either
 version 3.0 of the License, or (at your option) any later version.

 YAGI is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 Lesser General Public License for more details.

 You should have received a copy of the GNU Lesser General Public
 License along with YAGI.
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

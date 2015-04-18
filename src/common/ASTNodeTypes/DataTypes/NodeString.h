/**
 * @file   NodeString.h
 * @author Christopher Maier (cmaier@student.tugraz.at)
 * @date   January 2015
 *
 * AST node for string elements.
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


#ifndef NODESTRING_H_
#define NODESTRING_H_

#include<string>

#include "../ASTNodeBase.h"

/**
 * AST node class for string elements.
 */
class NodeString: public ASTNodeBase<>
{
  private:
    /**
     * The actual string value
     */
    std::string string_;

  public:
    DEFINE_VISITABLE()
    /**
     * Default ctor
     */
    NodeString();

    /**
     * Creates node from given string value
     * @param str The given string value
     */
    NodeString(const std::string& str);

    /**
     * Default dtor
     */
    virtual ~NodeString();

    /**
     * Getter for the actual string value
     * @return The actual string value
     */
    const std::string& getString() const
    {
      return string_;
    }

    /**
     * Setter for the actual string value
     * @param string The actual string value
     */
    void setString(const std::string& string)
    {
      string_ = string;
    }
};

#endif /* NODESTRING_H_ */

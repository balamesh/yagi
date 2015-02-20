/**
 * @file   NodeString.h
 * @author Christopher Maier (cmaier@student.tugraz.at)
 * @date   January 2015
 *
 * AST node for string elements.
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

/**
 * @file   NodeSensingDecl.h
 * @author Christopher Maier (cmaier.business@gmail.com)
 * @date   April 2015
 *
 * AST node for sensing declarations.
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


#ifndef NODESENSINGDECL_H_
#define NODESENSINGDECL_H_

#include <string>
#include <memory>

#include "../../Variables/NodeVarList.h"
#include "../../Identifier/NodeID.h"
#include "../../Formula/NodeFormulaBase.h"

/**
 * AST node class for sensing declarations.
 */
class NodeSensingDecl: public ASTNodeBase<>
{
  private:
    /**
     * Name of the sensing action
     */
    std::shared_ptr<NodeID> sensingName_;

    /**
     * Argument list
     */
    std::shared_ptr<NodeVarList> varList_;

    /**
     * Setting variables list
     */
    std::shared_ptr<NodeVarList> settingVarList_;

    /**
     * Formula to be evaluated
     */
    std::shared_ptr<NodeFormulaBase> formula_;

  public:
    DEFINE_VISITABLE()

    /**
     * Default ctor
     */
    NodeSensingDecl();

    /**
     * Default dtor
     */
    virtual ~NodeSensingDecl();

    /**
     * Getter for the sensing formula
     * @return The formula to be evaluated
     */
    const std::shared_ptr<NodeFormulaBase>& getFormula() const
    {
      return formula_;
    }

    /**
     * Setter for the sensing formula
     * @param formula The formula to be evaluated
     */
    void setFormula(const std::shared_ptr<NodeFormulaBase>& formula)
    {
      formula_ = formula;
    }

    /**
     * Getter for the name of the sensing action
     * @return The name of the sensing action
     */
    const std::shared_ptr<NodeID>& getSensingName() const
    {
      return sensingName_;
    }

    /**
     * Setter for the name of the sensing action
     * @param sensingName The name of the sensing action
     */
    void setSensingName(const std::shared_ptr<NodeID>& sensingName)
    {
      sensingName_ = sensingName;
    }

    /**
     * Getter for the setting var list
     * @return The setting var list
     */
    const std::shared_ptr<NodeVarList>& getSettingVarList() const
    {
      return settingVarList_;
    }

    /**
     * Setter for the setting var list
     * @param settingVarList The setting var list
     */
    void setSettingVarList(const std::shared_ptr<NodeVarList>& settingVarList)
    {
      settingVarList_ = settingVarList;
    }

    /**
     * Getter for the argument var list
     * @return The argument var list
     */
    const std::shared_ptr<NodeVarList>& getVarList() const
    {
      return varList_;
    }

    /**
     * Setter for the argument var list
     * @param varList The argument var list
     */
    void setVarList(const std::shared_ptr<NodeVarList>& varList)
    {
      varList_ = varList;
    }
};

#endif /* NODESENSINGDECL_H_ */

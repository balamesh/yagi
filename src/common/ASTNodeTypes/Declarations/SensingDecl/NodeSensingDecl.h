/*
 * NodeSensingDecl.h
 *
 *  Created on: Jul 7, 2014
 *      Author: cmaier
 */

#ifndef NODESENSINGDECL_H_
#define NODESENSINGDECL_H_

#include <string>
#include <memory>

#include "../../Variables/NodeVarList.h"
#include "../../Identifier/NodeID.h"
#include "../../Formula/NodeFormulaBase.h"

class NodeSensingDecl : public ASTNodeBase<>
{
  private:
    std::shared_ptr<NodeID> sensingName_;
    std::shared_ptr<NodeVarList> varList_;
    std::shared_ptr<NodeVarList> settingVarList_;
    std::shared_ptr<NodeFormulaBase> formula_;

  public:
    DEFINE_VISITABLE()
    NodeSensingDecl();
    virtual ~NodeSensingDecl();

    const std::shared_ptr<NodeFormulaBase>& getFormula() const
    {
      return formula_;
    }

    void setFormula(const std::shared_ptr<NodeFormulaBase>& formula)
    {
      formula_ = formula;
    }

    const std::shared_ptr<NodeID>& getSensingName() const
    {
      return sensingName_;
    }

    void setSensingName(const std::shared_ptr<NodeID>& sensingName)
    {
      sensingName_ = sensingName;
    }

    const std::shared_ptr<NodeVarList>& getSettingVarList() const
    {
      return settingVarList_;
    }

    void setSettingVarList(const std::shared_ptr<NodeVarList>& settingVarList)
    {
      settingVarList_ = settingVarList;
    }

    const std::shared_ptr<NodeVarList>& getVarList() const
    {
      return varList_;
    }

    void setVarList(const std::shared_ptr<NodeVarList>& varList)
    {
      varList_ = varList;
    }
};

#endif /* NODESENSINGDECL_H_ */

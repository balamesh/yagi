/**
 * @file   NodeFactDecl.h
 * @author Christopher Maier (cmaier.business@gmail.com)
 * @date   April 2015
 *
 * AST node for fact declarations.
 */

#ifndef NODEFACTDECL_H_
#define NODEFACTDECL_H_

#include <string>
#include <memory>
#include <vector>
#include <algorithm>

#include "../../ASTNodeBase.h"
#include "../../Identifier/NodeID.h"
#include "../../Domains/NodeDomainBase.h"

/**
 * AST node class for fact declarations
 */
class NodeFactDecl: public ASTNodeBase<>
{

  private:
    /**
     * Name of the fact
     */
    std::shared_ptr<NodeID> factName_;

    /**
     * Domains of the fact
     */
    std::vector<std::shared_ptr<NodeDomainBase>> domains_;

  public:
    DEFINE_VISITABLE()

    /**
     * Default ctor
     */
    NodeFactDecl();

    /**
     * Default dtor
     */
    virtual ~NodeFactDecl();

    /**
     * Setter for fact name
     * @param factName The fact name AST node
     */
    void setFactName(std::shared_ptr<NodeID> factName)
    {
      factName_ = factName;
    }

    /**
     * Adds domain to domains of the fact
     * @param domain Domain node to add
     */
    void addDomain(std::shared_ptr<NodeDomainBase> domain)
    {
      domains_.push_back(domain);
    }

    /**
     * Getter for the domains of the fact
     * @return The domains of the fact
     */
    const std::vector<std::shared_ptr<NodeDomainBase> >& getDomains() const
    {
      return domains_;
    }

    /**
     * Getter for the fact name
     * @return The name of the fact
     */
    const std::shared_ptr<NodeID>& getFactName() const
    {
      return factName_;
    }
};

#endif /* NODEFACTDECL_H_ */

/**
 * @file   NodeFluentDecl.h
 * @author Christopher Maier (cmaier.business@gmail.com)
 * @date   April 2015
 *
 * AST node for fluent declarations.
 */

#ifndef NODEFLUENTDECL_H_
#define NODEFLUENTDECL_H_

#include <string>
#include <memory>
#include <vector>
#include <algorithm>

#include "../../ASTNodeBase.h"
#include "../../Identifier/NodeID.h"
#include "../../Domains/NodeDomainBase.h"

/**
 * AST node class for fluent declarations
 */
class NodeFluentDecl: public ASTNodeBase<>
{

  private:
    /**
     * Name of the fluent
     */
    std::shared_ptr<NodeID> fluentName_;

    /**
     * Domains of the fluent
     */
    std::vector<std::shared_ptr<NodeDomainBase>> domains_;

  public:
    DEFINE_VISITABLE()

    /**
     * Default ctor
     */
    NodeFluentDecl();

    /**
     * Default dtor
     */
    virtual ~NodeFluentDecl();

    /**
     * Adds domain to the fluent domains
     * @param domain The domain to add
     */
    void addDomain(std::shared_ptr<NodeDomainBase> domain)
    {
      domains_.push_back(domain);
    }

    /**
     * Getter for the fluent domains
     * @return The domains of the fluent
     */
    const std::vector<std::shared_ptr<NodeDomainBase> >& getDomains() const
    {
      return domains_;
    }

    /**
     * Getter for the fluent name
     * @return The name of the fluent
     */
    const std::shared_ptr<NodeID>& getFluentName() const
    {
      return fluentName_;
    }

    /**
     * Setter for the fluent name
     * @param fluentName The name of the fluent
     */
    void setFluentName(const std::shared_ptr<NodeID>& fluentName)
    {
      fluentName_ = fluentName;
    }
};

#endif /* NODEFLUENTDECL_H_ */

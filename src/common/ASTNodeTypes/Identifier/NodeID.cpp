/**
 * @file   NodeID.cpp
 * @author Christopher Maier (cmaier.business@gmail.com)
 * @date   April 2015
 *
 * AST node for identifiers
 */

#include "NodeID.h"

NodeID::NodeID(const std::string& id) :
    id_(id)
{
}

NodeID::~NodeID()
{

}


/*
 * NodeConnective.cpp
 *
 *  Created on: May 28, 2014
 *      Author: cmaier
 */

#include "NodeAtomConnective.h"

NodeAtomConnective::NodeAtomConnective() :
    atomConnective_(AtomConnective::Unknown)
{
}

NodeAtomConnective::~NodeAtomConnective()
{
}

void NodeAtomConnective::fromString(const std::string& connString)
{
  if (connString == "==")
    atomConnective_ = AtomConnective::Eq;
  else if (connString == "!=")
    atomConnective_ = AtomConnective::Neq;
  else if (connString == "<=")
    atomConnective_ = AtomConnective::Le;
  else if (connString == ">=")
    atomConnective_ = AtomConnective::Ge;
  else if (connString == "<")
    atomConnective_ = AtomConnective::Lt;
  else if (connString == ">")
    atomConnective_ = AtomConnective::Gt;
  else
    throw std::runtime_error("Invalid atom connective string '" + connString + "'!");
}

std::string NodeAtomConnective::toString()
{
  if (atomConnective_ == AtomConnective::Eq)
    return "==";
  else if (atomConnective_ == AtomConnective::Neq)
    return "!=";
  else if (atomConnective_ == AtomConnective::Le)
    return "<=";
  else if (atomConnective_ == AtomConnective::Ge)
    return ">=";
  else if (atomConnective_ == AtomConnective::Lt)
    return "<";
  else if (atomConnective_ == AtomConnective::Gt)
    return ">";
  else
    throw std::runtime_error("Unknown atom connective!");
}

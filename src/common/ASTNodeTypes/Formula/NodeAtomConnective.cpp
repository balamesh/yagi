/**
 * @file   NodeAtomConnective.cpp
 * @author Christopher Maier (cmaier.business@gmail.com)
 * @date   April 2015
 *
 * AST node for atom connectives
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

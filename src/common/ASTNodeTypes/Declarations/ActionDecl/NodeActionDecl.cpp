/*
 * NodeActionDecl.cpp
 *
 *  Created on: May 23, 2014
 *      Author: cmaier
 */

#include "NodeActionDecl.h"

NodeActionDecl::NodeActionDecl()
{
  // TODO Auto-generated constructor stub
  actionName_ = nullptr;
  varList_ = nullptr;
  actionPrecondition_ = nullptr;
  actionEffect_ = nullptr;
  activeSensing_ = nullptr;
  signal_ = nullptr;
}

NodeActionDecl::~NodeActionDecl()
{
  // TODO Auto-generated destructor stub
}


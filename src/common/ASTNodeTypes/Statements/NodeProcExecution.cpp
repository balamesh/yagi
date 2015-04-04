/**
 * @file   NodeProcExecution.cpp
 * @author Christopher Maier (cmaier.business@gmail.com)
 * @date   April 2015
 *
 * AST node for a YAGI procedure execution
 */

#include "NodeProcExecution.h"

NodeProcExecution::NodeProcExecution() :
    procToExecName_(nullptr), parameters_(nullptr)
{
}

NodeProcExecution::~NodeProcExecution()
{
}


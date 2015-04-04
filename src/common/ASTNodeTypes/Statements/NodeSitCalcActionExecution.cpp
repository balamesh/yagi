/**
 * @file   NodeSitCalcActionExecution.cpp
 * @author Christopher Maier (cmaier.business@gmail.com)
 * @date   April 2015
 *
 * AST node for a sit calc simple action execution
 */

#include "NodeSitCalcActionExecution.h"

NodeSitCalcActionExecution::NodeSitCalcActionExecution() :
    parameters_(nullptr), actionType_(SitCalcActionType::Unknown), fluentName_(nullptr)
{

}

NodeSitCalcActionExecution::~NodeSitCalcActionExecution()
{

}


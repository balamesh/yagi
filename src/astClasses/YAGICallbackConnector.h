/*
 * CCallbackConsumer.h
 *
 *  Created on: Apr 24, 2014
 *      Author: cmaier
 */

#ifndef CCALLBACKCONSUMER_H_
#define CCALLBACKCONSUMER_H_

#include <string>
#include <antlr3.h>
#include "ASTBuilder.h"
#include "../cppInterfaceClasses/CToCppBridge.h"

extern "C"
{
    YAGICallbackCollection yagiCallbackCollection;
}

namespace YAGICallbackConnector
{

void addDomainElement(pANTLR3_STRING domainElement)
{
    ASTBuilder::getInstance().addDomainElement((char*) domainElement->chars);
}

void addDomainString()
{
    ASTBuilder::getInstance().addDomainStringNode();
}

void addDomainInteger()
{
    ASTBuilder::getInstance().addDomainIntegerNode();
}

void addDomainStringElements()
{
    ASTBuilder::getInstance().addDomainStringElementsNode();
}

void addFluent(pANTLR3_STRING fluentName)
{
    ASTBuilder::getInstance().addFluentDeclNode((char*) fluentName->chars);
}

void connectCallbacks()
{
    yagiCallbackCollection.addFluentDeclCallback = addFluent;
    yagiCallbackCollection.addDomainStringCallback = addDomainString;
    yagiCallbackCollection.addDomainIntegerCallback = addDomainInteger;
    yagiCallbackCollection.addDomainElementCallback = addDomainElement;
    yagiCallbackCollection.addDomainStringElementsCallback = addDomainStringElements;

}

}

#endif /* CCALLBACKCONSUMER_H_ */

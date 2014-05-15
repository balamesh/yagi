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
/*
extern "C" {
YAGICallbackCollection yagiCallbackCollection;
}

namespace YAGICallbackConnector {
void addID(pANTLR3_STRING id) {
	ASTBuilder::getInstance().addIDNode((char*) id->chars);
}
void addIDSet() {
	ASTBuilder::getInstance().addIDSetNode();
}
void addFluent(pANTLR3_STRING fluentName) {
	ASTBuilder::getInstance().addFluentDeclNode((char*) fluentName->chars);
}

void connectCallbacks() {
	yagiCallbackCollection.addFluentDeclCallback = addFluent;
	yagiCallbackCollection.addIDSetCallback = addIDSet;
	yagiCallbackCollection.addIDCallback = addID;
}

}
*/
#endif /* CCALLBACKCONSUMER_H_ */

/*
 * CToCppBridge.h
 *
 *  Created on: Apr 23, 2014
 *      Author: cmaier
 */
#ifndef CTOCPPBRIDGE_H_
#define CTOCPPBRIDGE_H_

#ifdef __cplusplus
extern "C" {
#endif

#include    <antlr3.h>

struct YAGICallbackCollection
{
  void (*addIDCallback)(pANTLR3_STRING id);
  void (*addIDSetCallback)();
  void (*addFluentDeclCallback)(pANTLR3_STRING fluentName);
};

extern struct YAGICallbackCollection yagiCallbackCollection;

#define ADD_ID(x) yagiCallbackCollection.addIDCallback(x)
#define ADD_ID_SET() yagiCallbackCollection.addIDSetCallback()
#define ADD_FLUENT_DECL(x) yagiCallbackCollection.addFluentDeclCallback(x)

#ifdef __cplusplus
}
#endif

#endif /* CTOCPPBRIDGE_H_ */

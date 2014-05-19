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
  void (*addDomainElementCallback)(pANTLR3_STRING domainElement);
  void (*addDomainIntegerCallback)();
  void (*addDomainStringCallback)();
  void (*addDomainStringElementsCallback)();
  void (*addFluentDeclCallback)(pANTLR3_STRING fluentName);
};

extern struct YAGICallbackCollection yagiCallbackCollection;

#define ADD_DOMAIN_ELEMENT(x) yagiCallbackCollection.addDomainElementCallback(x)
#define ADD_DOMAIN_INTEGER() yagiCallbackCollection.addDomainIntegerCallback()
#define ADD_DOMAIN_STRING() yagiCallbackCollection.addDomainStringCallback()
#define ADD_FLUENT_DECL(x) yagiCallbackCollection.addFluentDeclCallback(x)
#define ADD_DOMAIN_STRING_ELEMENTS() yagiCallbackCollection.addDomainStringElementsCallback()

#ifdef __cplusplus
}
#endif

#endif /* CTOCPPBRIDGE_H_ */

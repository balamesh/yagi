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
  void (*addProgramCallback)();
  void (*addFluentDeclCallback)(pANTLR3_STRING fluentName);
  void (*addFactDeclCallback)(pANTLR3_STRING factName);

  void (*addActionDeclCallback)(pANTLR3_STRING actionName);
  void (*addVarCallback)(pANTLR3_STRING varName);
  void (*addVarListCallback)();

  void (*addActiveSensingCallback)();
  void (*addEffectCallback) ();
};

extern struct YAGICallbackCollection yagiCallbackCollection;

//Program Structure
#define ADD_PROGRAM() yagiCallbackCollection.addProgramCallback()

//Declarations
#define ADD_FLUENT_DECL(x) yagiCallbackCollection.addFluentDeclCallback(x)
#define ADD_FACT_DECL(x) yagiCallbackCollection.addFactDeclCallback(x)
#define ADD_ACTION_DECL(x) yagiCallbackCollection.addActionDeclCallback(x)

//Domains
#define ADD_DOMAIN_ELEMENT(x) yagiCallbackCollection.addDomainElementCallback(x)
#define ADD_DOMAIN_INTEGER() yagiCallbackCollection.addDomainIntegerCallback()
#define ADD_DOMAIN_STRING() yagiCallbackCollection.addDomainStringCallback()
#define ADD_DOMAIN_STRING_ELEMENTS() yagiCallbackCollection.addDomainStringElementsCallback()

//Variables
#define ADD_VAR(x) yagiCallbackCollection.addVarCallback(x)
#define ADD_VAR_LIST() yagiCallbackCollection.addVarListCallback()

//Action Decl Stuff
#define ADD_ACTIVE_SENSING() yagiCallbackCollection.addActiveSensingCallback()
#define ADD_EFFECT() yagiCallbackCollection.addEffectCallback()

#ifdef __cplusplus
}
#endif

#endif /* CTOCPPBRIDGE_H_ */

#ifndef __NEONEXTION_NEXTIONVARIABLENUMERIC
#define __NEONEXTION_NEXTIONVARIABLENUMERIC

#include "Nextion.h"
#include "INextionNumericalValued.h"

class NextionVariableNumeric : public INextionNumericalValued
{
public:
  NextionVariableNumeric(Nextion &nex, uint8_t page, uint8_t component,
                         const char *name)
      : INextionWidget(nex, page, component, name)
      , INextionNumericalValued(nex, page, component, name)
  {
  }
};

#endif

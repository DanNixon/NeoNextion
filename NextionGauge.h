#ifndef __NEONEXTION_NEXTIONGAUGE
#define __NEONEXTION_NEXTIONGAUGE

#include "Nextion.h"
#include "INextionTouchable.h"
#include "INextionColourable.h"
#include "INextionNumericalValued.h"

class NextionGauge : public INextionTouchable,
                     public INextionColourable,
                     public INextionNumericalValued
{
public:
  NextionGauge(Nextion &nex, uint8_t page, uint8_t component, const char *name)
      : INextionWidget(nex, page, component, name)
      , INextionTouchable(nex, page, component, name)
      , INextionColourable(nex, page, component, name)
      , INextionNumericalValued(nex, page, component, name)
  {
  }
};

#endif

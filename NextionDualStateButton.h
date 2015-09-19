#ifndef __NEONEXTION_NEXTIONDUALSTATEBUTTON
#define __NEONEXTION_NEXTIONDUALSTATEBUTTON

#include "Nextion.h"
#include "INextionTouchable.h"
#include "INextionColourable.h"
#include "INextionNumericalValued.h"

class NextionDualStateButton : public INextionTouchable,
                               public INextionColourable,
                               private INextionNumericalValued
{
public:
  NextionDualStateButton(Nextion &nex, uint8_t page, uint8_t component,
                         const char *name)
      : INextionWidget(nex, page, component, name)
      , INextionTouchable(nex, page, component, name)
      , INextionColourable(nex, page, component, name)
      , INextionNumericalValued(nex, page, component, name)
  {
  }

  bool isActive()
  {
    return getValue();
  }

  bool setActive(bool active)
  {
    return setValue((uint32_t)active);
  }
};

#endif

#ifndef __NEONEXTION_NEXTIONBUTTON
#define __NEONEXTION_NEXTIONBUTTON

#include <Arduino.h>
#include "Nextion.h"
#include "INextionTouchable.h"
#include "INextionColourable.h"
#include "INextionStringValued.h"

class NextionText: public INextionTouchable, public INextionColourable, public INextionStringValued
{
  public:
    NextionText(Nextion* nex, uint8_t page, uint8_t component, const char *name):
      INextionWidget(nex, page, component, name),
      INextionTouchable(nex, page, component, name),
      INextionColourable(nex, page, component, name),
      INextionStringValued(nex, page, component, name)
    {}

};

#endif

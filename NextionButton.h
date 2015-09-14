#ifndef __NEONEXTION_NEXTIONTEXT
#define __NEONEXTION_NEXTIONTEXT

#include <Arduino.h>
#include "Nextion.h"
#include "INextionTouchable.h"
#include "INextionColourable.h"
#include "INextionStringValued.h"

class NextionButton: public INextionTouchable, public INextionColourable, public INextionStringValued
{
  public:
    NextionButton(Nextion* nex, uint8_t page, uint8_t component, const char *name):
      INextionWidget(nex, page, component, name),
      INextionTouchable(nex, page, component, name),
      INextionColourable(nex, page, component, name),
      INextionStringValued(nex, page, component, name)
    {}

};

#endif

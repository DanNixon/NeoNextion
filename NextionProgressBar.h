#ifndef __NEONEXTION_NEXTIONPROGRESSBAR
#define __NEONEXTION_NEXTIONPROGRESSBAR

#include <Arduino.h>
#include "Nextion.h"
#include "INextionTouchable.h"
#include "INextionColourable.h"

class NextionProgressBar: public INextionTouchable, public INextionColourable
{
  public:
    NextionProgressBar(Nextion* nex, uint8_t page, uint8_t component, const char *name);

    uint32_t getValue();
    bool setValue(uint32_t value);

};

#endif

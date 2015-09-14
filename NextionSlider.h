#ifndef __NEONEXTION_NEXTIONSLIDER
#define __NEONEXTION_NEXTIONSLIDER

#include <Arduino.h>
#include "Nextion.h"
#include "INextionTouchable.h"

class NextionSlider: public INextionTouchable
{
  public:
    NextionSlider(Nextion* nex, uint8_t page, uint8_t component, const char *name);

    uint32_t getValue();
    bool setValue(uint32_t value);

};

#endif

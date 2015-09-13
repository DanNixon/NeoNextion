#ifndef __NEONEXTION_NEXTIONGAUGE
#define __NEONEXTION_NEXTIONGAUGE

#include <Arduino.h>
#include "Nextion.h"
#include "INextionTouchable.h"

class NextionGauge: public virtual INextionTouchable
{
  public:
    NextionGauge(Nextion* nex, uint8_t page, uint8_t component, const char *name);

    uint32_t getValue();
    bool setValue(uint32_t value);

};

#endif

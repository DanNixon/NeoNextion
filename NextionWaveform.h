#ifndef __NEONEXTION_NEXTIONWAVEFORM
#define __NEONEXTION_NEXTIONWAVEFORM

#include <Arduino.h>
#include "Nextion.h"
#include "INextionTouchable.h"

class NextionWaveform: public INextionTouchable
{
  public:
    NextionWaveform(Nextion* nex, uint8_t page, uint8_t component, const char *name);

    bool addValue(uint8_t channel, uint8_t value);

};

#endif

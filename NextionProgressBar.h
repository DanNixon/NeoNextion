#ifndef __NEONEXTION_NEXTIONPROGRESSBAR
#define __NEONEXTION_NEXTIONPROGRESSBAR

#include <Arduino.h>
#include "Nextion.h"
#include "INextionWidget.h"

class NextionProgressBar: public virtual INextionWidget
{
  public:
    NextionProgressBar(Nextion* nex, uint8_t page, uint8_t component, const char *name);

    uint32_t getValue();
    bool setValue(uint32_t value);

};

#endif

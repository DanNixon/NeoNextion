#ifndef __NEONEXTION_NEXTIONTEXT
#define __NEONEXTION_NEXTIONTEXT

#include <Arduino.h>
#include "Nextion.h"
#include "INextionTouchable.h"

class NextionText: public virtual INextionTouchable
{
  public:
    NextionText(Nextion* nex, uint8_t page, uint8_t component, const char *name);

    size_t getText(char *buffer, size_t len);
    bool setText(const char *buffer);

};

#endif

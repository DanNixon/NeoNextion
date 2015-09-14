#ifndef __NEONEXTION_NEXTIONBUTTON
#define __NEONEXTION_NEXTIONBUTTON

#include <Arduino.h>
#include "Nextion.h"
#include "INextionTouchable.h"
#include "INextionColourable.h"

class NextionText: public INextionTouchable, public INextionColourable
{
  public:
    NextionText(Nextion* nex, uint8_t page, uint8_t component, const char *name);

    size_t getText(char *buffer, size_t len);
    bool setText(char *buffer);

};

#endif

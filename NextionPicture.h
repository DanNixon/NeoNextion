#ifndef __NEONEXTION_NEXTIONPICTURE
#define __NEONEXTION_NEXTIONPICTURE

#include <Arduino.h>
#include "Nextion.h"
#include "INextionTouchable.h"

class NextionPicture: public virtual INextionTouchable
{
  public:
    NextionPicture(Nextion* nex, uint8_t page, uint8_t component, const char *name);

    uint16_t getPictureID();
    bool setPictureID(uint16_t id);

};

#endif

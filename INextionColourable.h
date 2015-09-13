#ifndef __NEONEXTION_INEXTIONCOLOURABLE
#define __NEONEXTION_INEXTIONCOLOURABLE

#include <Arduino.h>
#include "Nextion.h"
#include "INextionWidget.h"

enum NextionColour
{
  BLACK   = 0,
  WHITE   = 65535,
  RED     = 63488,
  GREEN   = 2016,
  BLUE    = 31,
  GRAY    = 33840,
  BROWN   = 48192,
  YELLOW  = 65504
};

class INextionColourable: public virtual INextionWidget
{
  public:
    INextionColourable(Nextion* nex, uint8_t page, uint8_t component, const char *name):
      INextionWidget(nex, page, component, name)
    {
    }

  bool setForegroundColour(uint16_t colour, bool refresh=true);
  bool setEventForegroundColour(uint16_t colour, bool refresh=true);
  
  bool setBackgroundColour(uint16_t colour, bool refresh=true);
  bool setEventBackgroundColour(uint16_t colour, bool refresh=true);
  
  bool afterSet(bool refresh);

};

#endif

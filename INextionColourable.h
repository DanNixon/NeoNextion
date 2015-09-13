#ifndef __NEONEXTION_INEXTIONCOLOURABLE
#define __NEONEXTION_INEXTIONCOLOURABLE

#include <Arduino.h>
#include "Nextion.h"
#include "INextionWidget.h"
#include "NextionTypes.h"

class INextionColourable: public virtual INextionWidget
{
  public:
    INextionColourable(Nextion* nex, uint8_t page, uint8_t component, const char *name):
      INextionWidget(nex, page, component, name)
    {
    }

  bool setForegroundColour(uint32_t colour, bool refresh=true);
  bool setEventForegroundColour(uint32_t colour, bool refresh=true);
  
  bool setBackgroundColour(uint32_t colour, bool refresh=true);
  bool setEventBackgroundColour(uint32_t colour, bool refresh=true);
  
  bool afterSet(bool refresh);

};

#endif

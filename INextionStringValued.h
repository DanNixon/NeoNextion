#ifndef __NEONEXTION_INEXTIONSTRINGVALUED
#define __NEONEXTION_INEXTIONSTRINGVALUED

#include <Arduino.h>
#include "Nextion.h"
#include "INextionWidget.h"
#include "NextionTypes.h"

class INextionStringValued : public virtual INextionWidget
{
public:
  INextionStringValued(Nextion &nex, uint8_t page,
                       uint8_t component, const char *name)
    : INextionWidget(nex, page, component, name)
  {
  }

  size_t getText(char *buffer, size_t len)
  {
    return getStringProperty("txt", buffer, len);
  }
  
  bool setText(char *buffer)
  {
    return setStringProperty("txt", buffer);
  }
};

#endif

#ifndef __NEONEXTION_INEXTIONSTRINGVALUED
#define __NEONEXTION_INEXTIONSTRINGVALUED

#include <Arduino.h>
#include "Nextion.h"
#include "INextionWidget.h"
#include "NextionTypes.h"

class INextionStringValued : public virtual INextionWidget
{
public:
  INextionStringValued(Nextion &nex, uint8_t page, uint8_t component,
                       const char *name)
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
  
  bool setTextAsNumber(uint32_t value)
  {
    char buffer[8];
    snprintf(buffer, 8, "%ld", value);
    return setStringProperty("txt", buffer);
  }
  
  uint32_t getTextAsNumber()
  {
    char buffer[8];
    if (getStringProperty("txt", buffer, 8))
    {
      uint32_t value;
      sscanf(buffer, "%ld", &value);
      return value;
    }
    else
      return 0;
  }
};

#endif

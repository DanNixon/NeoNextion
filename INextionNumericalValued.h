#ifndef __NEONEXTION_INEXTIONNUMERICALVALUED
#define __NEONEXTION_INEXTIONNUMERICALVALUED

#include "Nextion.h"
#include "INextionWidget.h"
#include "NextionTypes.h"

class INextionNumericalValued : public virtual INextionWidget
{
public:
  INextionNumericalValued(Nextion &nex, uint8_t page, uint8_t component,
                          const char *name)
      : INextionWidget(nex, page, component, name)
  {
  }

  uint32_t getValue()
  {
    return getNumberProperty("val");
  }

  bool setValue(uint32_t value)
  {
    return setNumberProperty("val", value);
  }
};

#endif

#ifndef __NEONEXTION_INEXTIONWIDGET
#define __NEONEXTION_INEXTIONWIDGET

#include <Arduino.h>
#include "Nextion.h"

class INextionWidget
{
public:
  INextionWidget(Nextion *nex, uint8_t page, uint8_t component,
                 const char *name)
      : m_nextion(nex)
      , m_pageID(page)
      , m_componentID(component)
      , m_name(name)
  {
  }

protected:
  Nextion *m_nextion;
  uint8_t m_pageID;
  uint8_t m_componentID;
  const char *m_name;
};

#endif

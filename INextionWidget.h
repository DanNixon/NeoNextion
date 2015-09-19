#ifndef __NEONEXTION_INEXTIONWIDGET
#define __NEONEXTION_INEXTIONWIDGET

#include "Nextion.h"

class INextionWidget
{
public:
  INextionWidget(Nextion &nex, uint8_t page, uint8_t component,
                 const char *name);
  
  uint8_t getPageID();
  uint8_t getComponentID();

  bool setNumberProperty(char *propertyName, uint32_t value);
  uint32_t getNumberProperty(char *propertyName);
  bool setStringProperty(char *propertyName, char *value);
  size_t getStringProperty(char *propertyName, char *value, size_t len);

protected:
  Nextion &m_nextion;
  uint8_t m_pageID;
  uint8_t m_componentID;
  const char *m_name;
};

#endif

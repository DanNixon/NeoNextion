#include "INextionWidget.h"

INextionWidget::INextionWidget(Nextion *nex, uint8_t page, uint8_t component,
                               const char *name)
    : m_nextion(nex)
    , m_pageID(page)
    , m_componentID(component)
    , m_name(name)
{
}

bool INextionWidget::setNumberProperty(char *propertyName, uint32_t value)
{
  size_t commandLen = 8 + strlen(m_name) + strlen(propertyName);
  char comandBuffer[commandLen];
  snprintf(comandBuffer, commandLen, "%s.%s=%ld", m_name, propertyName, value);
  m_nextion->sendCommand(comandBuffer);
  return m_nextion->checkCommandComplete();
}

uint32_t INextionWidget::getNumberProperty(char *propertyName)
{
  size_t commandLen = 6 + strlen(m_name) + strlen(propertyName);
  char comandBuffer[commandLen];
  snprintf(comandBuffer, commandLen, "get %s.%s", m_name, propertyName);
  m_nextion->sendCommand(comandBuffer);
  uint32_t id;
  if (m_nextion->receiveNumber(&id))
    return id;
  else
    return 0;
}

bool INextionWidget::setStringProperty(char *propertyName, char *value)
{
  size_t commandLen = 7 + strlen(m_name) + strlen(propertyName) + strlen(value);
  char command[commandLen];
  snprintf(command, commandLen, "%s.%s=\"%s\"", m_name, propertyName, value);
  m_nextion->sendCommand(command);
  return m_nextion->checkCommandComplete();
}

size_t INextionWidget::getStringProperty(char *propertyName, char *value,
                                         size_t len)
{
  size_t commandLen = 6 + strlen(m_name) + strlen(propertyName);
  char command[commandLen];
  snprintf(command, commandLen, "get %s.%s", m_name, propertyName);
  m_nextion->sendCommand(command);
  return m_nextion->receiveString(value, len);
}

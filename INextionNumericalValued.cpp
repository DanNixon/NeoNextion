#include "INextionNumericalValued.h"

uint32_t INextionNumericalValued::getValue()
{
  size_t commandLen = 9 + strlen(m_name);
  char comandBuffer[commandLen];
  snprintf(comandBuffer, commandLen, "get %s.val", m_name);
  m_nextion->sendCommand(comandBuffer);
  uint32_t id;
  if(m_nextion->receiveNumber(&id))
    return id;
  else
    return 0;
}

bool INextionNumericalValued::setValue(uint32_t value)
{
  size_t commandLen = 11 + strlen(m_name);
  char comandBuffer[commandLen];
  snprintf(comandBuffer, commandLen, "%s.val=%d", m_name, value);
  m_nextion->sendCommand(comandBuffer);
  return m_nextion->checkCommandComplete();
}

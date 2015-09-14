#include "INextionColourable.h"

bool INextionColourable::setForegroundColour(uint32_t colour, bool refresh)
{
  size_t commandLen = 11 + strlen(m_name);
  char comandBuffer[commandLen];
  snprintf(comandBuffer, commandLen, "%s.pco=%ld", m_name, colour);
  m_nextion->sendCommand(comandBuffer);
  return afterSet(refresh);
}

bool INextionColourable::setEventForegroundColour(uint32_t colour, bool refresh)
{
  size_t commandLen = 11 + strlen(m_name);
  char comandBuffer[commandLen];
  snprintf(comandBuffer, commandLen, "%s.pco2=%ld", m_name, colour);
  m_nextion->sendCommand(comandBuffer);
  return afterSet(refresh);
}

bool INextionColourable::setBackgroundColour(uint32_t colour, bool refresh)
{
  size_t commandLen = 11 + strlen(m_name);
  char comandBuffer[commandLen];
  snprintf(comandBuffer, commandLen, "%s.bco=%ld", m_name, colour);
  m_nextion->sendCommand(comandBuffer);
  return afterSet(refresh);
}

bool INextionColourable::setEventBackgroundColour(uint32_t colour, bool refresh)
{
  size_t commandLen = 11 + strlen(m_name);
  char comandBuffer[commandLen];
  snprintf(comandBuffer, commandLen, "%s.bco2=%ld", m_name, colour);
  m_nextion->sendCommand(comandBuffer);
  return afterSet(refresh);
}

bool INextionColourable::afterSet(bool refresh)
{
  if(m_nextion->checkCommandComplete())
  {
    if(refresh)
    {
      m_nextion->refresh(m_name);
      return m_nextion->checkCommandComplete();
    }
    else
      return true;
  }
}

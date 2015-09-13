#include "INextionColourable.h"

bool INextionColourable::setForegroundColour(uint16_t colour, bool refresh)
{
  size_t commandLen = 10 + strlen(m_name);
  char comandBuffer[commandLen];
  snprintf(comandBuffer, commandLen, "%s.pco=%d", m_name, colour);
  m_nextion->sendCommand(comandBuffer);
  return afterSet(refresh);
}

bool INextionColourable::setEventForegroundColour(uint16_t colour, bool refresh)
{
  size_t commandLen = 10 + strlen(m_name);
  char comandBuffer[commandLen];
  snprintf(comandBuffer, commandLen, "%s.pco2=%d", m_name, colour);
  m_nextion->sendCommand(comandBuffer);
  return afterSet(refresh);
}
  
bool INextionColourable::setBackgroundColour(uint16_t colour, bool refresh)
{
  size_t commandLen = 10 + strlen(m_name);
  char comandBuffer[commandLen];
  snprintf(comandBuffer, commandLen, "%s.bco=%d", m_name, colour);
  m_nextion->sendCommand(comandBuffer);
  return afterSet(refresh);
}

bool INextionColourable::setEventBackgroundColour(uint16_t colour, bool refresh)
{
  size_t commandLen = 10 + strlen(m_name);
  char comandBuffer[commandLen];
  snprintf(comandBuffer, commandLen, "%s.bco2=%d", m_name, colour);
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
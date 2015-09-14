#include "INextionColourable.h"

INextionColourable::INextionColourable(Nextion* nex, uint8_t page, uint8_t component, const char *name):
  INextionWidget(nex, page, component, name)
{
}

bool INextionColourable::setForegroundColour(uint32_t colour, bool refresh)
{
  size_t commandLen = 11 + strlen(m_name);
  char comandBuffer[commandLen];
  snprintf(comandBuffer, commandLen, "%s.pco=%ld", m_name, colour);
  m_nextion->sendCommand(comandBuffer);
  return afterSet(refresh);
}

uint32_t INextionColourable::getForegroundColour()
{
  size_t commandLen = 9 + strlen(m_name);
  char comandBuffer[commandLen];
  snprintf(comandBuffer, commandLen, "get %s.pco", m_name);
  m_nextion->sendCommand(comandBuffer);
  uint32_t colour;
  if(m_nextion->receiveNumber(&colour))
    return colour;
  else
    return NEX_COL_BLACK;
}

bool INextionColourable::setEventForegroundColour(uint32_t colour, bool refresh)
{
  size_t commandLen = 11 + strlen(m_name);
  char comandBuffer[commandLen];
  snprintf(comandBuffer, commandLen, "%s.pco2=%ld", m_name, colour);
  m_nextion->sendCommand(comandBuffer);
  return afterSet(refresh);
}

uint32_t INextionColourable::getEventForegroundColour()
{
  size_t commandLen = 10 + strlen(m_name);
  char comandBuffer[commandLen];
  snprintf(comandBuffer, commandLen, "get %s.pco2", m_name);
  m_nextion->sendCommand(comandBuffer);
  uint32_t colour;
  if(m_nextion->receiveNumber(&colour))
    return colour;
  else
    return NEX_COL_BLACK;
}

bool INextionColourable::setBackgroundColour(uint32_t colour, bool refresh)
{
  size_t commandLen = 11 + strlen(m_name);
  char comandBuffer[commandLen];
  snprintf(comandBuffer, commandLen, "%s.bco=%ld", m_name, colour);
  m_nextion->sendCommand(comandBuffer);
  return afterSet(refresh);
}

uint32_t INextionColourable::getBackgroundColour()
{
  size_t commandLen = 9 + strlen(m_name);
  char comandBuffer[commandLen];
  snprintf(comandBuffer, commandLen, "get %s.bco", m_name);
  m_nextion->sendCommand(comandBuffer);
  uint32_t colour;
  if(m_nextion->receiveNumber(&colour))
    return colour;
  else
    return NEX_COL_BLACK;
}

bool INextionColourable::setEventBackgroundColour(uint32_t colour, bool refresh)
{
  size_t commandLen = 11 + strlen(m_name);
  char comandBuffer[commandLen];
  snprintf(comandBuffer, commandLen, "%s.bco2=%ld", m_name, colour);
  m_nextion->sendCommand(comandBuffer);
  return afterSet(refresh);
}

uint32_t INextionColourable::getEventBackgroundColour()
{
  size_t commandLen = 10 + strlen(m_name);
  char comandBuffer[commandLen];
  snprintf(comandBuffer, commandLen, "get %s.bco2", m_name);
  m_nextion->sendCommand(comandBuffer);
  uint32_t colour;
  if(m_nextion->receiveNumber(&colour))
    return colour;
  else
    return NEX_COL_BLACK;
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

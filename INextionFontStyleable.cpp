#include "INextionFontStyleable.h"

INextionFontStyleable::INextionFontStyleable(Nextion* nex, uint8_t page, uint8_t component, const char *name):
  INextionWidget(nex, page, component, name)
{
}

bool INextionFontStyleable::setFont(uint8_t id, bool refresh)
{
  size_t commandLen = 12 + strlen(m_name);
  char comandBuffer[commandLen];
  snprintf(comandBuffer, commandLen, "%s.font=%d", m_name, id);
  m_nextion->sendCommand(comandBuffer);
  return afterSet(refresh);
}

uint8_t INextionFontStyleable::getFont()
{
  size_t commandLen = 10 + strlen(m_name);
  char comandBuffer[commandLen];
  snprintf(comandBuffer, commandLen, "get %s.font", m_name);
  m_nextion->sendCommand(comandBuffer);
  uint32_t id;
  if(m_nextion->receiveNumber(&id))
    return id;
  else
    return NEX_FA_NONE;
}
    
bool INextionFontStyleable::setHAlignment(NextionFontAlignment align, bool refresh)
{
  size_t commandLen = 12 + strlen(m_name);
  char comandBuffer[commandLen];
  snprintf(comandBuffer, commandLen, "%s.xcen=%d", m_name, align);
  m_nextion->sendCommand(comandBuffer);
  return afterSet(refresh);
}

NextionFontAlignment INextionFontStyleable::getHAlignment()
{
  size_t commandLen = 10 + strlen(m_name);
  char comandBuffer[commandLen];
  snprintf(comandBuffer, commandLen, "get %s.xcen", m_name);
  m_nextion->sendCommand(comandBuffer);
  uint32_t align;
  if(m_nextion->receiveNumber(&align))
    return (NextionFontAlignment) align;
  else
    return NEX_FA_NONE;
}
    
bool INextionFontStyleable::setVAlignment(NextionFontAlignment align, bool refresh)
{
  size_t commandLen = 12 + strlen(m_name);
  char comandBuffer[commandLen];
  snprintf(comandBuffer, commandLen, "%s.ycen=%d", m_name, align);
  m_nextion->sendCommand(comandBuffer);
  return afterSet(refresh);
}

NextionFontAlignment INextionFontStyleable::getVAlignment()
{
  size_t commandLen = 10 + strlen(m_name);
  char comandBuffer[commandLen];
  snprintf(comandBuffer, commandLen, "get %s.ycen", m_name);
  m_nextion->sendCommand(comandBuffer);
  uint32_t align;
  if(m_nextion->receiveNumber(&align))
    return (NextionFontAlignment) align;
  else
    return NEX_FA_NONE;
}

bool INextionFontStyleable::afterSet(bool refresh)
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

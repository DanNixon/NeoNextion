#include "INextionFontStyleable.h"

INextionFontStyleable::INextionFontStyleable(Nextion &nex, uint8_t page,
                                             uint8_t component,
                                             const char *name)
    : INextionWidget(nex, page, component, name)
{
}

bool INextionFontStyleable::setFont(uint8_t id, bool refresh)
{
  return afterSet(setNumberProperty("font", id), refresh);
}

uint8_t INextionFontStyleable::getFont()
{
  return getNumberProperty("font");
}

bool INextionFontStyleable::setHAlignment(NextionFontAlignment align,
                                          bool refresh)
{
  return afterSet(setNumberProperty("xcen", align), refresh);
}

NextionFontAlignment INextionFontStyleable::getHAlignment()
{
  size_t commandLen = 10 + strlen(m_name);
  char commandBuffer[commandLen];
  snprintf(commandBuffer, commandLen, "get %s.xcen", m_name);
  m_nextion.sendCommand(commandBuffer);
  uint32_t align;
  if (m_nextion.receiveNumber(&align))
    return (NextionFontAlignment)align;
  else
    return NEX_FA_NONE;
}

bool INextionFontStyleable::setVAlignment(NextionFontAlignment align,
                                          bool refresh)
{
  return afterSet(setNumberProperty("ycen", align), refresh);
}

NextionFontAlignment INextionFontStyleable::getVAlignment()
{
  size_t commandLen = 10 + strlen(m_name);
  char commandBuffer[commandLen];
  snprintf(commandBuffer, commandLen, "get %s.ycen", m_name);
  m_nextion.sendCommand(commandBuffer);
  uint32_t align;
  if (m_nextion.receiveNumber(&align))
    return (NextionFontAlignment)align;
  else
    return NEX_FA_NONE;
}

bool INextionFontStyleable::afterSet(bool result, bool refresh)
{
  if (result)
  {
    if (refresh)
    {
      m_nextion.refresh(m_name);
      return m_nextion.checkCommandComplete();
    }
    else
      return true;
  }
  else
    return false;
}

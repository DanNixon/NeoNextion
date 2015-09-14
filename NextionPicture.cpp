#include "NextionPicture.h"
#include "INextionWidget.h"

NextionPicture::NextionPicture(Nextion *nex, uint8_t page, uint8_t component,
                               const char *name)
    : INextionWidget(nex, page, component, name)
    , INextionTouchable(nex, page, component, name)
{
}

uint16_t NextionPicture::getPictureID()
{
  size_t commandLen = 8 + strlen(m_name);
  char comandBuffer[commandLen];
  snprintf(comandBuffer, commandLen, "get %s.pic", m_name);
  m_nextion->sendCommand(comandBuffer);
  uint32_t id;
  if (m_nextion->receiveNumber(&id))
    return id;
  else
    return 0;
}

bool NextionPicture::setPictureID(uint16_t id)
{
  size_t commandLen = 10 + strlen(m_name);
  char comandBuffer[commandLen];
  snprintf(comandBuffer, commandLen, "%s.pic=%d", m_name, id);
  m_nextion->sendCommand(comandBuffer);
  return m_nextion->checkCommandComplete();
}

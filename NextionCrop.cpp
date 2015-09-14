#include "NextionCrop.h"
#include "INextionWidget.h"

NextionCrop::NextionCrop(Nextion *nex, uint8_t page, uint8_t component,
                         const char *name)
    : INextionWidget(nex, page, component, name)
    , INextionTouchable(nex, page, component, name)
{
}

uint16_t NextionCrop::getPictureID()
{
  size_t commandLen = 9 + strlen(m_name);
  char comandBuffer[commandLen];
  snprintf(comandBuffer, commandLen, "get %s.picc", m_name);
  m_nextion->sendCommand(comandBuffer);
  uint32_t id;
  if (m_nextion->receiveNumber(&id))
    return id;
  else
    return 0;
}

bool NextionCrop::setPictureID(uint16_t id)
{
  size_t commandLen = 11 + strlen(m_name);
  char comandBuffer[commandLen];
  snprintf(comandBuffer, commandLen, "%s.picc=%d", m_name, id);
  m_nextion->sendCommand(comandBuffer);
  return m_nextion->checkCommandComplete();
}

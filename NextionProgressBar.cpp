#include "NextionProgressBar.h"
#include "INextionWidget.h"

NextionProgressBar::NextionProgressBar(Nextion* nex, uint8_t page, uint8_t component, const char *name):
  INextionWidget(nex, page, component, name),
  INextionTouchable(nex, page, component, name),
  INextionColourable(nex, page, component, name)
{
}

uint32_t NextionProgressBar::getValue()
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

bool NextionProgressBar::setValue(uint32_t value)
{
  size_t commandLen = 11 + strlen(m_name);
  char comandBuffer[commandLen];
  snprintf(comandBuffer, commandLen, "%s.val=%d", m_name, value);
  m_nextion->sendCommand(comandBuffer);
  return m_nextion->checkCommandComplete();
}

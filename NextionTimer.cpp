#include "NextionTimer.h"

NextionTimer::NextionTimer(Nextion &nex, uint8_t page, uint8_t component,
                           const char *name)
    : INextionWidget(nex, page, component, name)
    , INextionTouchable(nex, page, component, name)
{
}

uint32_t NextionTimer::getCycle()
{
  size_t commandLen = 9 + strlen(m_name);
  char commandBuffer[commandLen];
  snprintf(commandBuffer, commandLen, "get %s.tim", m_name);
  m_nextion.sendCommand(commandBuffer);
  uint32_t id;
  if (m_nextion.receiveNumber(&id))
    return id;
  else
    return 0;
}

bool NextionTimer::setCycle(uint32_t cycle)
{
  if (cycle < 50)
    return false;

  size_t commandLen = 11 + strlen(m_name);
  char commandBuffer[commandLen];
  snprintf(commandBuffer, commandLen, "%s.tim=%d", m_name, cycle);
  m_nextion.sendCommand(commandBuffer);
  return m_nextion.checkCommandComplete();
}

bool NextionTimer::enable()
{
  size_t commandLen = 6 + strlen(m_name);
  char commandBuffer[commandLen];
  snprintf(commandBuffer, commandLen, "%s.en=1", m_name);
  m_nextion.sendCommand(commandBuffer);
  m_nextion.checkCommandComplete();
}

bool NextionTimer::disable()
{
  size_t commandLen = 6 + strlen(m_name);
  char commandBuffer[commandLen];
  snprintf(commandBuffer, commandLen, "%s.en=0", m_name);
  m_nextion.sendCommand(commandBuffer);
  m_nextion.checkCommandComplete();
}

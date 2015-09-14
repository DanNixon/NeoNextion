#include "NextionTimer.h"

NextionTimer::NextionTimer(Nextion *nex, uint8_t page, uint8_t component,
                           const char *name)
    : INextionWidget(nex, page, component, name)
    , INextionTouchable(nex, page, component, name)
{
}

// TODO: The callbacks are not working

bool NextionTimer::attachEvent(NextionCallback cb)
{
  return attachReleaseEvent(cb);
}

void NextionTimer::detachEvent()
{
  detachReleaseEvent();
}

uint32_t NextionTimer::getCycle()
{
  size_t commandLen = 9 + strlen(m_name);
  char comandBuffer[commandLen];
  snprintf(comandBuffer, commandLen, "get %s.tim", m_name);
  m_nextion->sendCommand(comandBuffer);
  uint32_t id;
  if (m_nextion->receiveNumber(&id))
    return id;
  else
    return 0;
}

bool NextionTimer::setCycle(uint32_t cycle)
{
  if (cycle < 50)
    return false;

  size_t commandLen = 11 + strlen(m_name);
  char comandBuffer[commandLen];
  snprintf(comandBuffer, commandLen, "%s.tim=%d", m_name, cycle);
  m_nextion->sendCommand(comandBuffer);
  return m_nextion->checkCommandComplete();
}

bool NextionTimer::enable()
{
  size_t commandLen = 6 + strlen(m_name);
  char comandBuffer[commandLen];
  snprintf(comandBuffer, commandLen, "%s.en=1", m_name);
  m_nextion->sendCommand(comandBuffer);
  m_nextion->checkCommandComplete();
}

bool NextionTimer::disable()
{
  size_t commandLen = 6 + strlen(m_name);
  char comandBuffer[commandLen];
  snprintf(comandBuffer, commandLen, "%s.en=0", m_name);
  m_nextion->sendCommand(comandBuffer);
  m_nextion->checkCommandComplete();
}

#include "NextionWaveform.h"
#include "INextionWidget.h"

NextionWaveform::NextionWaveform(Nextion* nex, uint8_t page, uint8_t component, const char *name):
  INextionWidget(nex, page, component, name),
  INextionTouchable(nex, page, component, name)
{
}

bool NextionWaveform::addValue(uint8_t channel, uint8_t value)
{
  if(channel > 3)
    return false;

  //TODO: This does not seem to be working
  size_t commandLen = 22;
  char comandBuffer[commandLen];
  snprintf(comandBuffer, commandLen, "add %d,%d,%d",
           m_componentID, channel, value);
  Serial.println(comandBuffer);
  m_nextion->sendCommand(comandBuffer);
  return m_nextion->checkCommandComplete();
}

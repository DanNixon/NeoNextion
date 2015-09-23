#include "NextionWaveform.h"
#include "INextionWidget.h"

NextionWaveform::NextionWaveform(Nextion &nex, uint8_t page, uint8_t component,
                                 const char *name)
    : INextionWidget(nex, page, component, name)
    , INextionTouchable(nex, page, component, name)
    , INextionColourable(nex, page, component, name)
{
}

bool NextionWaveform::addValue(uint8_t channel, uint8_t value)
{
  if (channel > 3)
    return false;

  size_t commandLen = 22;
  char commandBuffer[commandLen];
  snprintf(commandBuffer, commandLen, "add %d,%d,%d", m_componentID, channel,
           value);
  m_nextion.sendCommand(commandBuffer);

  /* TODO: this check still fails but the command does actually work */
  /* return m_nextion.checkCommandComplete(); */
  return true;
}

bool NextionWaveform::setChannelColour(uint8_t channel, uint32_t colour,
                                       bool refresh)
{
  char buffer[5];
  snprintf(buffer, 5, "pco%d", channel);
  return setColour(buffer, colour, refresh);
}

uint32_t NextionWaveform::getChannelColour(uint8_t channel)
{
  char buffer[5];
  snprintf(buffer, 5, "pco%d", channel);
  return getColour(buffer);
}

bool NextionWaveform::setGridColour(uint32_t colour, bool refresh)
{
  return setColour("gdc", colour, refresh);
}

uint32_t NextionWaveform::getGridColour()
{
  return getColour("gdc");
}

bool NextionWaveform::setGridWidth(uint16_t width)
{
  return setNumberProperty("gdw", width);
}

uint16_t NextionWaveform::getGridWidth()
{
  return getNumberProperty("gdw");
}

bool NextionWaveform::setGridHeight(uint16_t height)
{
  return setNumberProperty("gdh", height);
}

uint16_t NextionWaveform::getGridHeight()
{
  return getNumberProperty("gdh");
}

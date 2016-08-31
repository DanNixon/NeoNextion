/*! \file */

#include "NextionSlidingText.h"

/*!
 * \copydoc INextionWidget::INextionWidget
 */
NextionSlidingText::NextionSlidingText(Nextion &nex, uint8_t page,
                                       uint8_t component, const char *name)
    : INextionWidget(nex, page, component, name)
    , INextionTouchable(nex, page, component, name)
    , INextionColourable(nex, page, component, name)
    , INextionStringValued(nex, page, component, name)
    , INextionFontStyleable(nex, page, component, name)
{
}

bool NextionSlidingText::setScrolling(bool scroll)
{
  size_t commandLen = 10 + strlen(m_name);
  char commandBuffer[commandLen];
  snprintf(commandBuffer, commandLen, "%s.en=%d", m_name, scroll);
  return sendCommand(commandBuffer);
}

bool NextionSlidingText::isScrolling()
{
  size_t commandLen = 8 + strlen(m_name);
  char commandBuffer[commandLen];
  snprintf(commandBuffer, commandLen, "get %s.en", m_name);
  sendCommand(commandBuffer, false);
  uint32_t en;
  if (m_nextion.receiveNumber(&en))
    return (bool)en;
  else
    return 0;
}

bool NextionSlidingText::setScrollDirection(NextionScrollDirection direction)
{
  size_t commandLen = 11 + strlen(m_name);
  char commandBuffer[commandLen];
  snprintf(commandBuffer, commandLen, "%s.dir=%d", m_name, direction);
  return sendCommand(commandBuffer);
}

NextionScrollDirection NextionSlidingText::getScrollDirection()
{
  size_t commandLen = 9 + strlen(m_name);
  char commandBuffer[commandLen];
  snprintf(commandBuffer, commandLen, "get %s.dir", m_name);
  sendCommand(commandBuffer, false);
  uint32_t val;
  if (m_nextion.receiveNumber(&val))
    return (NextionScrollDirection)val;
  else
    return NEX_SCROLL_NONE;
}

bool NextionSlidingText::setScrollDistance(uint32_t distance)
{
  size_t commandLen = 11 + strlen(m_name);
  char commandBuffer[commandLen];
  snprintf(commandBuffer, commandLen, "%s.dis=%d", m_name, distance);
  return sendCommand(commandBuffer);
}

uint32_t NextionSlidingText::getScrollDistance()
{
  size_t commandLen = 9 + strlen(m_name);
  char commandBuffer[commandLen];
  snprintf(commandBuffer, commandLen, "get %s.dis", m_name);
  sendCommand(commandBuffer, false);
  uint32_t val;
  if (m_nextion.receiveNumber(&val))
    return val;
  else
    return 0;
}

bool NextionSlidingText::setScrollDelay(uint32_t delay)
{
  size_t commandLen = 11 + strlen(m_name);
  char commandBuffer[commandLen];
  snprintf(commandBuffer, commandLen, "%s.tim=%d", m_name, delay);
  return sendCommand(commandBuffer);
}

uint32_t NextionSlidingText::getScrollDelay()
{
  size_t commandLen = 9 + strlen(m_name);
  char commandBuffer[commandLen];
  snprintf(commandBuffer, commandLen, "get %s.tim", m_name);
  sendCommand(commandBuffer, false);
  uint32_t val;
  if (m_nextion.receiveNumber(&val))
    return val;
  else
    return 0;
}
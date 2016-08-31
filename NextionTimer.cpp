/*! \file */

#include "NextionTimer.h"

/*!
 * \copydoc INextionWidget::INextionWidget
 */
NextionTimer::NextionTimer(Nextion &nex, uint8_t page, uint8_t component,
                           const char *name)
    : INextionWidget(nex, page, component, name)
    , INextionTouchable(nex, page, component, name)
{
}

/*!
 * \brief Gets the cycle time of the timer.
 * \return Time in ms (may also return 0 in case of error)
 */
uint32_t NextionTimer::getCycle()
{
  size_t commandLen = 9 + strlen(m_name);
  char commandBuffer[commandLen];
  snprintf(commandBuffer, commandLen, "get %s.tim", m_name);
  sendCommand(commandBuffer, false);
  uint32_t id;
  if (m_nextion.receiveNumber(&id))
    return id;
  else
    return 0;
}

/*!
 * \brief Sets the cycle time of the timer.
 * \param cycle Time in ms
 * \return True if successful
 */
bool NextionTimer::setCycle(uint32_t cycle)
{
  if (cycle < 50)
    return false;

  size_t commandLen = 11 + strlen(m_name);
  char commandBuffer[commandLen];
  snprintf(commandBuffer, commandLen, "%s.tim=%d", m_name, cycle);
  return sendCommand(commandBuffer);
}

/*!
 * \brief Enable/start the timer.
 * \return True if successful
 */
bool NextionTimer::enable()
{
  size_t commandLen = 6 + strlen(m_name);
  char commandBuffer[commandLen];
  snprintf(commandBuffer, commandLen, "%s.en=1", m_name);
  return sendCommand(commandBuffer);
}

/*!
 * \brief Disable/stop the timer.
 * \return True if successful
 */
bool NextionTimer::disable()
{
  size_t commandLen = 6 + strlen(m_name);
  char commandBuffer[commandLen];
  snprintf(commandBuffer, commandLen, "%s.en=0", m_name);
  return sendCommand(commandBuffer);
}

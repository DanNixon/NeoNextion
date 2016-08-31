/*! \file */

#include "INextionWidget.h"

/*!
 * \brief Create a new widget adapter.
 * \param nex Reference to the Nextion driver
 * \param page ID of page this widget is on
 * \param component Component ID of this widget
 * \param name Name of this widget
 */
INextionWidget::INextionWidget(Nextion &nex, uint8_t page, uint8_t component,
                               const char *name)
    : m_nextion(nex)
    , m_pageID(page)
    , m_componentID(component)
    , m_name(name)
{
}

/*!
 * \brief Gets the ID of the page this widget resides on.
 * \return Page ID
 */
uint8_t INextionWidget::getPageID()
{
  return m_pageID;
}

/*!
 * \brief Gets the component ID of this widget.
 * \return Component ID
 */
uint8_t INextionWidget::getComponentID()
{
  return m_componentID;
}

/*!
 * \brief Sets the value of a numerical property of this widget.
 * \param propertyName Name of the property
 * \param value Value
 * \return True if successful
 */
bool INextionWidget::setNumberProperty(char *propertyName, uint32_t value)
{
  size_t commandLen = 8 + strlen(m_name) + strlen(propertyName);
  char commandBuffer[commandLen];
  snprintf(commandBuffer, commandLen, "%s.%s=%ld", m_name, propertyName, value);
  return sendCommand(commandBuffer);
}

/*!
 * \brief Gets the value of a numerical property of this widget.
 * \param propertyName Name of the property
 * \return Value (may also return 0 in case of error)
 */
uint32_t INextionWidget::getNumberProperty(char *propertyName)
{
  size_t commandLen = 7 + strlen(m_name) + strlen(propertyName);
  char commandBuffer[commandLen];
  snprintf(commandBuffer, commandLen, "get %s.%s", m_name, propertyName);
  sendCommand(commandBuffer, false);
  uint32_t id;
  if (m_nextion.receiveNumber(&id))
    return id;
  else
    return 0;
}

/*!
 * \brief Sets the value of a string property of this widget.
 * \param propertyName Name of the property
 * \param value Value
 * \return True if successful
 */
bool INextionWidget::setStringProperty(char *propertyName, char *value)
{
  size_t commandLen = 7 + strlen(m_name) + strlen(propertyName) + strlen(value);
  char command[commandLen];
  snprintf(command, commandLen, "%s.%s=\"%s\"", m_name, propertyName, value);
  return sendCommand(command);
}

/*!
 * \brief Gets the value of a string property of this widget.
 * \param propertyName Name of the property
 * \param value Pointer to char array to store result in
 * \param len Maximum length of value
 * \return Actual length of value
 */
size_t INextionWidget::getStringProperty(char *propertyName, char *value,
                                         size_t len)
{
  size_t commandLen = 6 + strlen(m_name) + strlen(propertyName);
  char command[commandLen];
  snprintf(command, commandLen, "get %s.%s", m_name, propertyName);
  sendCommand(command, false);
  return m_nextion.receiveString(value, len);
}

bool INextionWidget::sendCommand(char *commandStr, bool checkComplete)
{
  if (m_pageID != m_nextion.getCurrentPage())
    return false;

  m_nextion.sendCommand(commandStr);

  if (checkComplete)
    return m_nextion.checkCommandComplete();
  else
    return true;
}

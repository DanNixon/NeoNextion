/*! \file */

#ifndef __NEONEXTION_INEXTIONSTRINGVALUED
#define __NEONEXTION_INEXTIONSTRINGVALUED

#include "Nextion.h"
#include "INextionWidget.h"
#include "NextionTypes.h"

/*!
 * \class INextionStringValued
 * \brief Interface for widgets that hold a string value.
 *
 * Assumes that the string value is a property named "txt".
 */
class INextionStringValued : public virtual INextionWidget
{
public:
  /*!
   * \copydoc INextionWidget::INextionWidget
   */
  INextionStringValued(Nextion &nex, uint8_t page, uint8_t component,
                       const char *name)
      : INextionWidget(nex, page, component, name)
  {
  }

  /*!
   * \brief Gets the value of the string.
   * \param buffer Pointer to storage to strore string in
   * \param len Maximum length of string
   * \return Actual length of string
   * \see INextionStringValued::setText
   */
  size_t getText(char *buffer, size_t len)
  {
    return getStringProperty("txt", buffer, len);
  }

  /*!
   * \brief Sets the value of the string.
   * \param buffer Value
   * \return True if successful
   * \see INextionStringValued::getText
   */
  bool setText(char *buffer)
  {
    return setStringProperty("txt", buffer);
  }

  /*!
   * \brief Sets the text by a numercal value.
   * \param value Numerical value
   * \return True if successful
   * \see INextionStringValued::getTextAsNumber
   */
  bool setTextAsNumber(uint32_t value)
  {
    char buffer[8];
    snprintf(buffer, 8, "%ld", value);
    return setStringProperty("txt", buffer);
  }

  /*!
   * \brief Gets the text parsed as a number.
   * \return Numerical value
   * \see INextionStringValued::setTextAsNumber
   */
  uint32_t getTextAsNumber()
  {
    char buffer[8];
    if (getStringProperty("txt", buffer, 8))
    {
      uint32_t value;
      sscanf(buffer, "%ld", &value);
      return value;
    }
    else
      return 0;
  }
};

#endif

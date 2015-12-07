/*! \file */

#ifndef __NEONEXTION_NEXTIONDUALSTATEBUTTON
#define __NEONEXTION_NEXTIONDUALSTATEBUTTON

#include "Nextion.h"
#include "INextionTouchable.h"
#include "INextionColourable.h"
#include "INextionNumericalValued.h"

/*!
 * \class NextionDualStateButton
 * \brief Represents a dual state button widget.
 */
class NextionDualStateButton : public INextionTouchable,
                               public INextionColourable,
                               private INextionNumericalValued
{
public:
  /*!
   * \copydoc INextionWidget::INextionWidget
   */
  NextionDualStateButton(Nextion &nex, uint8_t page, uint8_t component,
                         const char *name)
      : INextionWidget(nex, page, component, name)
      , INextionTouchable(nex, page, component, name)
      , INextionColourable(nex, page, component, name)
      , INextionNumericalValued(nex, page, component, name)
  {
  }

  /*!
   * \brief Determines if the button is currently in the enabled/pressed state.
   * \return True if enabled/pressed
   */
  bool isActive()
  {
    return getValue();
  }

  /*!
   * \brief Sets the enabled/pressed state of the button.
   * \param active State
   * \return True if successful
   */
  bool setActive(bool active)
  {
    return setValue((uint32_t)active);
  }
};

#endif

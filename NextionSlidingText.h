/*! \file */

#ifndef __NEONEXTION_NEXTIONSLIDINGTEXT
#define __NEONEXTION_NEXTIONSLIDINGTEXT

#include "Nextion.h"
#include "INextionTouchable.h"
#include "INextionColourable.h"
#include "INextionStringValued.h"
#include "INextionFontStyleable.h"

/*!
 * \class NextionSlidingText
 * \brief Represents a sliding text widget.
 */
class NextionSlidingText : public INextionTouchable,
                           public INextionColourable,
                           public INextionStringValued,
                           public INextionFontStyleable
{
public:
  /*!
   * \copydoc INextionWidget::INextionWidget
   */
  NextionSlidingText(Nextion &nex, uint8_t page, uint8_t component,
                     const char *name)
      : INextionWidget(nex, page, component, name)
      , INextionTouchable(nex, page, component, name)
      , INextionColourable(nex, page, component, name)
      , INextionStringValued(nex, page, component, name)
      , INextionFontStyleable(nex, page, component, name)
  {
  }

  bool setScrolling(bool scroll);
  bool isScrolling();

  bool setScrollDistance(uint32_t distance);
  uint32_t getScrollDistance();

  bool setScrollDelay(uint32_t delay);
  uint32_t getScrollDelay();
};

#endif

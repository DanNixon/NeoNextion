/*! \file */

#ifndef __NEONEXTION_NEXTIONPAGE
#define __NEONEXTION_NEXTIONPAGE

#include "Nextion.h"
#include "INextionTouchable.h"

/*!
 * \class NextionPage
 * \brief Represents a page of widgets.
 */
class NextionPage : public INextionTouchable
{
public:
  NextionPage(Nextion &nex, uint8_t page, uint8_t component, const char *name);

  bool show();
  bool isShown();
};

#endif

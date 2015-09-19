#ifndef __NEONEXTION_NEXTIONPROGRESSBAR
#define __NEONEXTION_NEXTIONPROGRESSBAR

#include "Nextion.h"
#include "INextionTouchable.h"
#include "INextionColourable.h"
#include "INextionNumericalValued.h"

class NextionProgressBar : public INextionTouchable,
                           public INextionColourable,
                           public INextionNumericalValued
{
public:
  NextionProgressBar(Nextion &nex, uint8_t page, uint8_t component,
                     const char *name)
      : INextionWidget(nex, page, component, name)
      , INextionTouchable(nex, page, component, name)
      , INextionColourable(nex, page, component, name)
      , INextionNumericalValued(nex, page, component, name)
  {
  }
};

#endif

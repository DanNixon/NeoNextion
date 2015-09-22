#ifndef __NEONEXTION_INEXTIONCALLBACK
#define __NEONEXTION_INEXTIONCALLBACK

#include "INextionTouchable.h"

class INextionCallback
{
public:
  INextionCallback()
  {
  }

  virtual void handleNextionEvent(NextionEventType type,
                                  INextionTouchable *widget) = 0;
};

#endif

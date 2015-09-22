#ifndef __NEONEXTION_NEXTIONCALLBACKFUNCTIONHANDLER
#define __NEONEXTION_NEXTIONCALLBACKFUNCTIONHANDLER

#include "INextionCallback.h"

class NextionCallbackFunctionHandler : public INextionCallback
{
public:
  typedef void (*NextionFunction)(NextionEventType, INextionTouchable *);

  NextionCallbackFunctionHandler(NextionFunction f)
      : m_function(f)
  {
  }

  void handleNextionEvent(NextionEventType type, INextionTouchable *item)
  {
    if (m_function != NULL)
      m_function(type, item);
  }

private:
  NextionFunction m_function;
};

#endif

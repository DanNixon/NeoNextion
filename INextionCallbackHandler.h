#ifndef __NEONEXTION_INEXTIONCALLBACKHANDLER
#define __NEONEXTION_INEXTIONCALLBACKHANDLER

#include "Nextion.h"
#include "INextionCallback.h"

class NextionCallbackHandler
{
public:
  typedef void (*NextionFunction)(INextionTouchable *);

  NextionCallbackHandler(INextionCallback *obj, NextionEventType type):
    m_object(obj), m_function(NULL), m_type(type)
  {
  }
  
  NextionCallbackHandler(NextionFunction f, NextionEventType type):
    m_object(NULL), m_function(f), m_type(type)
  {
  }

  void operator()(INextionTouchable *item)
  {
    if(m_object == NULL)
      m_function(item);
    else
      m_object->handleNextionEvent(m_type, item);
  }

private:
  INextionCallback *m_object;
  NextionFunction m_function;
  NextionEventType m_type;
};

#endif
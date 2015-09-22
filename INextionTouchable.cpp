#include "INextionTouchable.h"

INextionTouchable::INextionTouchable(Nextion &nex, uint8_t page,
                                     uint8_t component, const char *name)
    : INextionWidget(nex, page, component, name)
    , m_callback(NULL)
{
  nex.registerTouchable(this);
}

bool INextionTouchable::processEvent(uint8_t pageID, uint8_t componentID,
                                     uint8_t eventType)
{
  if (pageID != m_pageID)
    return false;

  if (componentID != m_componentID)
    return false;

  switch (eventType)
  {
  case NEX_EVENT_PUSH:
    if (m_callback)
      m_callback->handleNextionEvent((NextionEventType) eventType, this);
    return true;

  case NEX_EVENT_POP:
    if (m_callback)
      m_callback->handleNextionEvent((NextionEventType) eventType, this);
    return true;

  default:
    return false;
  }
}

bool INextionTouchable::attachCallback(
    NextionCallbackFunctionHandler::NextionFunction function)
{
  if (!function)
    return false;

  if (m_callback != NULL)
    detachCallback();

  m_callback = new NextionCallbackFunctionHandler(function);
  return true;
}

bool INextionTouchable::attachCallback(INextionCallback *handler)
{
  if (!handler)
    return false;

  if (m_callback != NULL)
    detachCallback();

  m_callback = handler;
  return true;
}

void INextionTouchable::detachCallback()
{
  m_callback = NULL;
}

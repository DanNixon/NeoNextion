#include "INextionTouchable.h"

bool INextionTouchable::processEvent(uint8_t pageID, uint8_t componentID, uint8_t eventType)
{	
  if(pageID != m_pageID)
    return false;

  if(componentID != m_componentID)
    return false;

  switch(eventType)
  {
    case NEX_EVENT_PUSH:
	  if(m_pressEvent)
        m_pressEvent(this);
      return true;

    case NEX_EVENT_POP:
	  if(m_releaseEvent)
        m_releaseEvent(this);
      return true;

    default:
      return false;
  }
}

bool INextionTouchable::attachPressEvent(NextionCallback cb)
{
  if(!cb)
    return false;

  m_pressEvent = cb;
  return true;
}

void INextionTouchable::detachPressEvent()
{
  m_pressEvent = NULL;
}

bool INextionTouchable::attachReleaseEvent(NextionCallback cb)
{
  if(!cb)
    return false;

  m_releaseEvent = cb;
  return true;
}

void INextionTouchable::detachReleaseEvent()
{
  m_releaseEvent = NULL;
}

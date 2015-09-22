#ifndef __NEONEXTION_INEXTIONTOUCHABLE
#define __NEONEXTION_INEXTIONTOUCHABLE

#include "Nextion.h"
#include "INextionWidget.h"
#include "NextionCallbackHandler.h"

class INextionTouchable : public virtual INextionWidget
{
public:
  INextionTouchable(Nextion &nex, uint8_t page, uint8_t component,
                    const char *name);

  bool processEvent(uint8_t pageID, uint8_t componentID, uint8_t eventType);

  bool attachPressEvent(NextionCallbackHandler::NextionFunction cb);
  bool attachPressEvent(INextionCallback *obj);
  void detachPressEvent();

  bool attachReleaseEvent(NextionCallbackHandler::NextionFunction cb);
  bool attachReleaseEvent(INextionCallback *obj);
  void detachReleaseEvent();

private:
  NextionCallbackHandler *m_pressEvent;
  NextionCallbackHandler *m_releaseEvent;
};

#endif

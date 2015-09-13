#ifndef __NEONEXTION_INEXTIONTOUCHABLE
#define __NEONEXTION_INEXTIONTOUCHABLE

#include <Arduino.h>
#include "Nextion.h"
#include "INextionWidget.h"

#define NEX_EVENT_PUSH  (0x01)
#define NEX_EVENT_POP   (0x00)

typedef void (* NextionCallback)(INextionTouchable *);

class INextionTouchable: public virtual INextionWidget
{
  public:
    INextionTouchable(Nextion* nex, uint8_t page, uint8_t component, const char *name):
      INextionWidget(nex, page, component, name)
    {
      nex->registerTouchable(this);
    }

    bool processEvent(uint8_t pageID, uint8_t componentID, uint8_t eventType);

    bool attachPressEvent(NextionCallback cb);
    void detachPressEvent();

    bool attachReleaseEvent(NextionCallback cb);
    void detachReleaseEvent();

  private:
    NextionCallback m_pressEvent;
    NextionCallback m_releaseEvent;

};

#endif

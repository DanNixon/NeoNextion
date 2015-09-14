#ifndef __NEONEXTION_NEXTIONTIMER
#define __NEONEXTION_NEXTIONTIMER

#include <Arduino.h>
#include "Nextion.h"
#include "INextionTouchable.h"

class NextionTimer: public virtual INextionTouchable
{
  public:
    NextionTimer(Nextion* nex, uint8_t page, uint8_t component, const char *name);

    void attachTimer(NextionCallback cb);
    void detachTimer();

    uint32_t getCycle();
    bool setCycle(uint32_t cycle);

    bool enable();
    bool disable();
};

#endif

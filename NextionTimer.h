#ifndef __NEONEXTION_NEXTIONTIMER
#define __NEONEXTION_NEXTIONTIMER

#include <Arduino.h>
#include "Nextion.h"
#include "INextionTouchable.h"

class NextionTimer : public INextionTouchable
{
public:
  NextionTimer(Nextion *nex, uint8_t page, uint8_t component, const char *name);

  bool attachEvent(NextionCallback cb);
  void detachEvent();

  uint32_t getCycle();
  bool setCycle(uint32_t cycle);

  bool enable();
  bool disable();
};

#endif

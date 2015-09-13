#ifndef __NEONEXTION_NEXTIONPAGE
#define __NEONEXTION_NEXTIONPAGE

#include <Arduino.h>
#include "Nextion.h"
#include "INextionWidget.h"

class NextionPage: public virtual INextionWidget
{
  public:
    NextionPage(Nextion* nex, uint8_t page, uint8_t component, const char *name);

    bool show();
    bool isShown();

};

#endif
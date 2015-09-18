#include "NextionCrop.h"
#include "INextionWidget.h"

NextionCrop::NextionCrop(Nextion &nex, uint8_t page, uint8_t component,
                         const char *name)
    : INextionWidget(nex, page, component, name)
    , INextionTouchable(nex, page, component, name)
{
}

uint16_t NextionCrop::getPictureID()
{
  return getNumberProperty("pic");
}

bool NextionCrop::setPictureID(uint16_t id)
{
  return setNumberProperty("pic", id);
}

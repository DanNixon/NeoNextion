#include "NextionPicture.h"
#include "INextionWidget.h"

NextionPicture::NextionPicture(Nextion &nex, uint8_t page, uint8_t component,
                               const char *name)
    : INextionWidget(nex, page, component, name)
    , INextionTouchable(nex, page, component, name)
{
}

uint16_t NextionPicture::getPictureID()
{
  return getNumberProperty("pic");
}

bool NextionPicture::setPictureID(uint16_t id)
{
  return setNumberProperty("pic", id);
}

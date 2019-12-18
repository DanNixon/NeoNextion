/*! \file */

#include "NextionCrop.h"
#include "INextionWidget.h"

/*!
 * \copydoc INextionWidget::INextionWidget
 */
NextionCrop::NextionCrop(Nextion &nex, uint8_t page, uint8_t component,
                         const char *name)
    : INextionWidget(nex, page, component, name)
    , INextionTouchable(nex, page, component, name)
{
}

/*!
 * \copydoc NextionPicture::getPictureID
 */
uint16_t NextionCrop::getPictureID()
{
  return getNumberProperty("picc");
}

/*!
 * \copydoc NextionPicture::setPictureID
 */
bool NextionCrop::setPictureID(uint16_t id)
{
  return setNumberProperty("picc", id);
}

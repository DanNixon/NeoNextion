#include "INextionColourable.h"

INextionColourable::INextionColourable(Nextion &nex, uint8_t page,
                                       uint8_t component, const char *name)
    : INextionWidget(nex, page, component, name)
{
}

bool INextionColourable::setForegroundColour(uint32_t colour, bool refresh)
{
  return afterSet(setNumberProperty("pco", colour), refresh);
}

uint32_t INextionColourable::getForegroundColour()
{
  return getNumberProperty("pco");
}

bool INextionColourable::setEventForegroundColour(uint32_t colour, bool refresh)
{
  return afterSet(setNumberProperty("pco2", colour), refresh);
}

uint32_t INextionColourable::getEventForegroundColour()
{
  return getNumberProperty("pco2");
}

bool INextionColourable::setBackgroundColour(uint32_t colour, bool refresh)
{
  return afterSet(setNumberProperty("bco", colour), refresh);
}

uint32_t INextionColourable::getBackgroundColour()
{
  return getNumberProperty("bco");
}

bool INextionColourable::setEventBackgroundColour(uint32_t colour, bool refresh)
{
  return afterSet(setNumberProperty("bco2", colour), refresh);
}

uint32_t INextionColourable::getEventBackgroundColour()
{
  return getNumberProperty("bco2");
}

bool INextionColourable::afterSet(bool result, bool refresh)
{
  if (result)
  {
    if (refresh)
    {
      m_nextion.refresh(m_name);
      return m_nextion.checkCommandComplete();
    }
    else
      return true;
  }
  else
    return false;
}

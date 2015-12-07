/*! \file */

#include "INextionColourable.h"

INextionColourable::INextionColourable(Nextion &nex, uint8_t page,
                                       uint8_t component, const char *name)
    : INextionWidget(nex, page, component, name)
{
}

bool INextionColourable::setForegroundColour(uint32_t colour, bool refresh)
{
  return setColour("pco", colour, refresh);
}

uint32_t INextionColourable::getForegroundColour()
{
  return getColour("pco");
}

bool INextionColourable::setEventForegroundColour(uint32_t colour, bool refresh)
{
  return setColour("pco2", colour, refresh);
}

uint32_t INextionColourable::getEventForegroundColour()
{
  return getColour("pco2");
}

bool INextionColourable::setBackgroundColour(uint32_t colour, bool refresh)
{
  return setColour("bco", colour, refresh);
}

uint32_t INextionColourable::getBackgroundColour()
{
  return getColour("bco");
}

bool INextionColourable::setEventBackgroundColour(uint32_t colour, bool refresh)
{
  return setColour("bco2", colour, refresh);
}

uint32_t INextionColourable::getEventBackgroundColour()
{
  return getColour("bco2");
}

bool INextionColourable::setColour(char *type, uint32_t colour, bool refresh)
{
  return afterSet(setNumberProperty(type, colour), refresh);
}

uint32_t INextionColourable::getColour(char *type)
{
  return getNumberProperty(type);
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

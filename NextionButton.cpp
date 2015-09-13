#include "NextionButton.h"

NextionButton::NextionButton(Nextion* nex, uint8_t page, uint8_t component, const char *name):
  INextionWidget(nex, page, component, name),
  INextionTouchable(nex, page, component, name),
  INextionColourable(nex, page, component, name)
{
}

size_t NextionButton::getText(char *buffer, size_t len)
{
  size_t commandLen = 9 + strlen(m_name);
  char command[commandLen];
  snprintf(command, commandLen, "get %s.txt", m_name);
  m_nextion->sendCommand(command);
  return m_nextion->receiveString(buffer, len);
}

bool NextionButton::setText(char *buffer)
{
  size_t commandLen = 8 + strlen(m_name) + strlen(buffer);
  char command[commandLen];
  snprintf(command, commandLen, "%s.txt=\"%s\"", m_name, buffer);
  m_nextion->sendCommand(command);
  return m_nextion->checkCommandComplete();
}

#include "NextionPage.h"

NextionPage::NextionPage(Nextion &nex, uint8_t page, uint8_t component,
                         const char *name)
    : INextionWidget(nex, page, component, name)
{
}

bool NextionPage::show()
{
  size_t commandLen = 6 + strlen(m_name);
  char command[commandLen];
  snprintf(command, commandLen, "page %s", m_name);
  m_nextion.sendCommand(command);
  return m_nextion.checkCommandComplete();
}

bool NextionPage::isShown()
{
  return m_nextion.getCurrentPage() == m_pageID;
}

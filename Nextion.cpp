#include "Nextion.h"
#include "INextionTouchable.h"

Nextion::Nextion(Stream &stream, bool flushSerialBeforeTx)
    : m_serialPort(stream)
    , m_timeout(1000)
    , m_flushSerialBeforeTx(flushSerialBeforeTx)
    , m_touchableList(NULL)
{
  m_serialPort.setTimeout(m_timeout);
}

bool Nextion::init()
{
  sendCommand("");

  sendCommand("bkcmd=1");
  bool result1 = checkCommandComplete();

  sendCommand("page 0");
  bool result2 = checkCommandComplete();

  return (result1 && result2);
}

void Nextion::poll()
{
  while (m_serialPort.available())
  {
    if (m_serialPort.peek() == 0xFF)
      m_serialPort.read();

    if (m_serialPort.peek() == NEX_RET_EVENT_TOUCH_HEAD)
    {
      m_serialPort.read();
      processTouchMessage();
    }
  }
}

bool Nextion::refresh()
{
  sendCommand("ref 0");
  return checkCommandComplete();
}

bool Nextion::refresh(const char *objectName)
{
  size_t commandLen = 4 + strlen(objectName);
  char commandBuffer[commandLen];
  snprintf(commandBuffer, commandLen, "ref %s", objectName);
  sendCommand(commandBuffer);
  return checkCommandComplete();
}

bool Nextion::sleep()
{
  sendCommand("sleep=1");
  return checkCommandComplete();
}

bool Nextion::wake()
{
  sendCommand("sleep=0");
  return checkCommandComplete();
}

uint16_t Nextion::getBrightness()
{
  sendCommand("get dim");
  uint32_t val;
  if (receiveNumber(&val))
    return val;
  else
    return 0;
}

bool Nextion::setBrightness(uint16_t val, bool persist)
{
  size_t commandLen = 10;
  char commandBuffer[commandLen];
  if (persist)
    snprintf(commandBuffer, commandLen, "dims=%d", val);
  else
    snprintf(commandBuffer, commandLen, "dim=%d", val);
  sendCommand(commandBuffer);
  return checkCommandComplete();
}

uint8_t Nextion::getCurrentPage()
{
  sendCommand("sendme");

  uint8_t id[1] = {0};
  bool ok = waitForMessage(NEX_RET_CURRENT_PAGE_ID_HEAD);

  if (ok)
    ok = getMessagePayload(id, 1) == 1;

  if (ok)
    return id[0];
  else
    return 0;
}

bool Nextion::clear(uint32_t colour)
{
  size_t commandLen = 9;
  char commandBuffer[commandLen];
  snprintf(commandBuffer, commandLen, "cls %ld", colour);
  sendCommand(commandBuffer);
  return checkCommandComplete();
}

bool Nextion::drawPicture(uint16_t x, uint16_t y, uint8_t id)
{
  size_t commandLen = 21;
  char commandBuffer[commandLen];
  snprintf(commandBuffer, commandLen, "pic %d,%d,%d", x, y, id);
  sendCommand(commandBuffer);
  return checkCommandComplete();
}

bool Nextion::drawPicture(uint16_t x, uint16_t y, uint16_t w, uint16_t h,
                          uint8_t id)
{
  size_t commandLen = 35;
  char commandBuffer[commandLen];
  snprintf(commandBuffer, commandLen, "picq %d,%d,%d,%d,%d", x, y, w, h, id);
  sendCommand(commandBuffer);
  return checkCommandComplete();
}

bool Nextion::drawStr(uint16_t x, uint16_t y, uint16_t w, uint16_t h,
                      uint8_t fontID, char *str, uint32_t bgColour,
                      uint32_t fgColour, uint8_t bgType,
                      NextionFontAlignment xCentre,
                      NextionFontAlignment yCentre)
{
  size_t commandLen = 65 + strlen(str);
  char commandBuffer[commandLen];
  snprintf(commandBuffer, commandLen, "xstr %d,%d,%d,%d,%d,%ld,%ld,%d,%d,%d,%s",
           x, y, w, h, fontID, fgColour, bgColour, xCentre, yCentre, bgType,
           str);
  sendCommand(commandBuffer);
  return checkCommandComplete();
}

bool Nextion::drawLine(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2,
                       uint32_t colour)
{
  size_t commandLen = 35;
  char commandBuffer[commandLen];
  snprintf(commandBuffer, commandLen, "line %d,%d,%d,%d,%ld", x1, y1, x2, y2,
           colour);
  sendCommand(commandBuffer);
  return checkCommandComplete();
}

bool Nextion::drawRect(uint16_t x, uint16_t y, uint16_t w, uint16_t h,
                       bool filled, uint32_t colour)
{
  size_t commandLen = 35;
  char commandBuffer[commandLen];
  if (filled)
    snprintf(commandBuffer, commandLen, "draw %d,%d,%d,%d,%ld", x, y, x + w,
             y + h, colour);
  else
    snprintf(commandBuffer, commandLen, "fill %d,%d,%d,%d,%ld", x, y, w, h,
             colour);
  sendCommand(commandBuffer);
  return checkCommandComplete();
}

bool Nextion::drawCircle(uint16_t x, uint16_t y, uint16_t r, uint32_t colour)
{
  size_t commandLen = 27;
  char commandBuffer[commandLen];
  snprintf(commandBuffer, commandLen, "cir %d,%d,%d,%ld", x, y, r, colour);
  sendCommand(commandBuffer);
  return checkCommandComplete();
}

void Nextion::registerTouchable(INextionTouchable *touchable)
{
  ITouchableListItem *newListItem = new ITouchableListItem;
  newListItem->item = touchable;
  newListItem->next = NULL;

  if (m_touchableList == NULL)
    m_touchableList = newListItem;
  else
  {
    ITouchableListItem *item = m_touchableList;
    while(item->next != NULL)
      item = item->next;
    item->next = newListItem;
  }
}

void Nextion::sendCommand(char *command)
{
  if (m_flushSerialBeforeTx)
    m_serialPort.flush();

  m_serialPort.print(command);
  m_serialPort.write(0xFF);
  m_serialPort.write(0xFF);
  m_serialPort.write(0xFF);
}

bool Nextion::checkCommandComplete()
{
  bool ok = waitForMessage(NEX_RET_CMD_FINISHED);

  if (ok)
    getMessagePayload(NULL, 0);

  return ok;
}

bool Nextion::receiveNumber(uint32_t *number)
{
  uint8_t temp[4] = {0};

  bool ok = waitForMessage(NEX_RET_NUMBER_HEAD);

  if (ok && (getMessagePayload(temp, 4) == 4))
  {
    *number = (temp[3] << 24) | (temp[2] << 16) | (temp[1] << 8) | (temp[0]);
    return true;
  }

  return false;
}

size_t Nextion::receiveString(char *buffer, size_t len)
{
  memset(buffer, 0, len);
  size_t read = 0;

  bool ok = waitForMessage(NEX_RET_STRING_HEAD);

  if (ok)
  {
    read = getMessagePayload((uint8_t *)buffer, len - 1);
    buffer[read] = '\0';
  }

  return read;
}

bool Nextion::processTouchMessage()
{
  uint8_t buffer[3];
  if (getMessagePayload(buffer, 3) == 3)
  {
    ITouchableListItem *item = m_touchableList;
    while (item != NULL)
    {
      item->item->processEvent(buffer[0], buffer[1], buffer[2]);
      item = item->next;
    }
  }

  delay(10);
}

bool Nextion::waitForMessage(uint8_t header, bool pollWhileWait, uint32_t timeout)
{
  if (timeout == 0)
    timeout = m_timeout;

  uint32_t start = millis();
  while (millis() - start < timeout)
  {
    if (pollWhileWait)
      poll();

    if (m_serialPort.peek() == 0xFF)
      m_serialPort.read();

    if (m_serialPort.peek() == header)
    {
      m_serialPort.read();
      return true;
    }
  }

  return false;
}

size_t Nextion::getMessagePayload(uint8_t *buffer, size_t len)
{
  size_t i = 0;

  if (buffer && (len > 0))
  {
    while (m_serialPort.peek() != 0xFF && m_serialPort.peek() != 0xFFFFFF)
    {
      buffer[i] = m_serialPort.read();
      i++;

      if (i >= len)
        break;
    }
  }

  while (m_serialPort.peek() == 0xFF)
    m_serialPort.read();

  return i;
}

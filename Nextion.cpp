#include "Nextion.h"
#include "INextionTouchable.h"

Nextion::Nextion(Stream &stream, bool flushSerialBeforeTx)
    : m_serialPort(stream)
    , m_timeout(500)
    , m_flushSerialBeforeTx(flushSerialBeforeTx)
    , m_touchableList(NULL)
{
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
  while (m_serialPort.available() > 0)
  {
    char c = m_serialPort.read();

    if (c == NEX_RET_EVENT_TOUCH_HEAD)
    {
      delay(10);

      if (m_serialPort.available() >= 6)
      {
        static uint8_t buffer[8];
        buffer[0] = c;

        uint8_t i;
        for (i = 1; i < 7; i++)
          buffer[i] = m_serialPort.read();
        buffer[i] = 0x00;

        if (buffer[4] == 0xFF && buffer[5] == 0xFF && buffer[6] == 0xFF)
        {
          ITouchableListItem *item = m_touchableList;
          while (item != NULL)
          {
            item->item->processEvent(buffer[1], buffer[2], buffer[3]);
            item = item->next;
          }
        }
      }
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

  uint8_t temp[5] = {0};

  if (sizeof(temp) != m_serialPort.readBytes((char *)temp, sizeof(temp)))
    return 0;

  if (temp[0] == NEX_RET_CURRENT_PAGE_ID_HEAD && temp[2] == 0xFF &&
      temp[3] == 0xFF && temp[4] == 0xFF)
    return temp[1];

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
  bool ret = false;
  uint8_t temp[4] = {0};

  if (sizeof(temp) != m_serialPort.readBytes((char *)temp, sizeof(temp)))
    ret = false;

  if (temp[0] == NEX_RET_CMD_FINISHED && temp[1] == 0xFF && temp[2] == 0xFF &&
      temp[3] == 0xFF)
    ret = true;

  return ret;
}

bool Nextion::receiveNumber(uint32_t *number)
{
  uint8_t temp[8] = {0};

  if (!number)
    return false;

  if (sizeof(temp) != m_serialPort.readBytes((char *)temp, sizeof(temp)))
    return false;

  if (temp[0] == NEX_RET_NUMBER_HEAD && temp[5] == 0xFF && temp[6] == 0xFF &&
      temp[7] == 0xFF)
  {
    *number = (temp[4] << 24) | (temp[3] << 16) | (temp[2] << 8) | (temp[1]);
    return true;
  }

  return false;
}

size_t Nextion::receiveString(char *buffer, size_t len)
{
  memset(buffer, 0, len);

  bool have_header_flag = false;
  uint8_t flag_count = 0;
  size_t pos = 0;

  if (!buffer || len == 0)
    return false;

  uint32_t start = millis();
  while (millis() - start <= m_timeout)
  {
    while (m_serialPort.available())
    {
      char c = m_serialPort.read();
      if (have_header_flag)
      {
        if (c == 0xFF || c == 0xFFFFFFFF)
        {
          flag_count++;
          if (flag_count >= 3)
            break;
        }
        else
        {
          buffer[pos] = c;
          pos++;
          if (pos == len - 1)
            break;
        }
      }
      else if (c == NEX_RET_STRING_HEAD)
        have_header_flag = true;
    }

    if (flag_count >= 3)
      break;
  }

  pos++;
  buffer[pos] = '\0';
  return pos;
}

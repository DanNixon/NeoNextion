#include "Nextion.h"
#include "INextionTouchable.h"

Nextion::Nextion(Stream &stream):
  m_serialPort(stream),
  m_timeout(500),
  m_touchableList(NULL)
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
  while(m_serialPort.available() > 0)
  {
    char c = m_serialPort.read();

    if(c == NEX_RET_EVENT_TOUCH_HEAD)
	{
      delay(10);
	  
      if(m_serialPort.available() >= 6)
      {
        static uint8_t buffer[8];
        buffer[0] = c;

        uint8_t i;
        for(i = 1; i < 7; i++)
          buffer[i] = m_serialPort.read();
        buffer[i] = 0x00;

        if(buffer[4] == 0xFF &&
		   buffer[5] == 0xFF &&
		   buffer[6] == 0xFF)
        {
          ITouchableListItem *item = m_touchableList;
          while(item != NULL)
          {
            item->item->processEvent(buffer[1], buffer[2], buffer[3]);
            item = item->next;
          }
        }
      }
    }
  }
}

void Nextion::registerTouchable(INextionTouchable *touchable)
{
  ITouchableListItem *newListItem = new ITouchableListItem;
  newListItem->item = touchable;
  newListItem->next = NULL;

  if(m_touchableList == NULL)
    m_touchableList = newListItem;
  else
    m_touchableList->next = newListItem;
}

void Nextion::sendCommand(char *command)
{
  while(m_serialPort.available())
    m_serialPort.read();

  m_serialPort.print(command);
  m_serialPort.write(0xFF);
  m_serialPort.write(0xFF);
  m_serialPort.write(0xFF);
}

bool Nextion::checkCommandComplete()
{
  bool ret = false;
  uint8_t temp[4] = {0};

  if(sizeof(temp) != m_serialPort.readBytes((char *)temp, sizeof(temp)))
    ret = false;

  if(temp[0] == NEX_RET_CMD_FINISHED &&
     temp[1] == 0xFF &&
     temp[2] == 0xFF &&
     temp[3] == 0xFF)
    ret = true;

  return ret;
}

bool Nextion::receiveNumber(uint32_t *number)
{
  uint8_t temp[8] = {0};

  if(!number)
    return false;

  if(sizeof(temp) != m_serialPort.readBytes((char *)temp, sizeof(temp)))
    return false;

  if(temp[0] == NEX_RET_NUMBER_HEAD &&
     temp[5] == 0xFF &&
     temp[6] == 0xFF &&
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

  if(!buffer || len == 0)
    return false;

  uint32_t start = millis();
  while (millis() - start <= m_timeout)
  {
    while(m_serialPort.available())
    {
      char c = m_serialPort.read();
      if(have_header_flag)
      {
        if(c == 0xFF || c == 0xFFFFFFFF)
        {
          flag_count++;
          if (flag_count >= 3)
            break;
        }
        else
		{
          buffer[pos] = c;
		  pos++;
		  if(pos == len-1)
            break;
		}
      }
      else if(c == NEX_RET_STRING_HEAD)
        have_header_flag = true;
    }

    if(flag_count >= 3)
      break;
  }
  
  pos++;
  buffer[pos] = '\0';
  return pos;
}

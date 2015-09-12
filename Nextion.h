#ifndef __NEONEXTION_NEXTION
#define __NEONEXTION_NEXTION

#include <Arduino.h>

#define NEX_RET_CMD_FINISHED                (0x01)
#define NEX_RET_EVENT_LAUNCHED              (0x88)
#define NEX_RET_EVENT_UPGRADED              (0x89)
#define NEX_RET_EVENT_TOUCH_HEAD            (0x65)
#define NEX_RET_EVENT_POSITION_HEAD         (0x67)
#define NEX_RET_EVENT_SLEEP_POSITION_HEAD   (0x68)
#define NEX_RET_CURRENT_PAGE_ID_HEAD        (0x66)
#define NEX_RET_STRING_HEAD                 (0x70)
#define NEX_RET_NUMBER_HEAD                 (0x71)
#define NEX_RET_INVALID_CMD                 (0x00)
#define NEX_RET_INVALID_COMPONENT_ID        (0x02)
#define NEX_RET_INVALID_PAGE_ID             (0x03)
#define NEX_RET_INVALID_PICTURE_ID          (0x04)
#define NEX_RET_INVALID_FONT_ID             (0x05)
#define NEX_RET_INVALID_BAUD                (0x11)
#define NEX_RET_INVALID_VARIABLE            (0x1A)
#define NEX_RET_INVALID_OPERATION           (0x1B)

class INextionTouchable;

struct ITouchableListItem
{
  INextionTouchable *item;
  ITouchableListItem *next;
};


class Nextion
{
  public:
    Nextion(Stream &stream);

    bool init();
    void poll();
    void registerTouchable(INextionTouchable *touchable);

    void sendCommand(char *command);
    bool checkCommandComplete();
    bool receiveNumber(uint32_t *number);
    size_t receiveString(char *buffer, size_t len);

  private:
    Stream &m_serialPort;
    uint32_t m_timeout;
    ITouchableListItem *m_touchableList;

};

#endif

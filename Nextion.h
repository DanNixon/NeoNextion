#ifndef __NEONEXTION_NEXTION
#define __NEONEXTION_NEXTION

#include <Arduino.h>
#include "NextionColour.h"

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
	
    bool refresh();
    bool refresh(const char *objectName);
    
    bool sleep();
    bool wake();
    
    uint16_t getBrightness();
    bool setBrightness(uint16_t val, bool persist=false);
    
    bool clear(uint32_t colour=WHITE);
    bool drawPicture(uint16_t x, uint16_t y, uint8_t id);
    bool drawPicture(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint8_t id);
    bool drawStr(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint8_t fontID, char * str, uint8_t xCentre, uint8_t yCentre, uint32_t bgColour, uint32_t fgColour, uint8_t bgType);
    bool drawLine(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint32_t colour);
    bool drawRect(uint16_t x, uint16_t y, uint16_t w, uint16_t h, bool filled, uint32_t colour);
    bool drawCircle(uint16_t x, uint16_t y, uint16_t r, uint32_t colour);

    uint8_t getCurrentPage();
    
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

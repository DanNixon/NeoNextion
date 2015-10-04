#ifndef __NEONEXTION_NEXTION
#define __NEONEXTION_NEXTION

#include <Arduino.h>

#include "NextionTypes.h"

class INextionTouchable;

struct ITouchableListItem
{
  INextionTouchable *item;
  ITouchableListItem *next;
};

class Nextion
{
public:
  Nextion(Stream &stream, bool flushSerialBeforeTx = true);

  bool init();
  void poll();

  bool refresh();
  bool refresh(const char *objectName);

  bool sleep();
  bool wake();

  uint16_t getBrightness();
  bool setBrightness(uint16_t val, bool persist = false);

  uint8_t getCurrentPage();

  bool clear(uint32_t colour = NEX_COL_WHITE);
  bool drawPicture(uint16_t x, uint16_t y, uint8_t id);
  bool drawPicture(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint8_t id);
  bool drawStr(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint8_t fontID,
               char *str, uint32_t bgColour = NEX_COL_BLACK,
               uint32_t fgColour = NEX_COL_WHITE,
               uint8_t bgType = NEX_BG_SOLIDCOLOUR,
               NextionFontAlignment xCentre = NEX_FA_CENTRE,
               NextionFontAlignment yCentre = NEX_FA_CENTRE);
  bool drawLine(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2,
                uint32_t colour);
  bool drawRect(uint16_t x, uint16_t y, uint16_t w, uint16_t h, bool filled,
                uint32_t colour);
  bool drawCircle(uint16_t x, uint16_t y, uint16_t r, uint32_t colour);

  void registerTouchable(INextionTouchable *touchable);
  void sendCommand(char *command);
  bool checkCommandComplete();
  bool receiveNumber(uint32_t *number);
  size_t receiveString(char *buffer, size_t len);

private:
  bool processTouchMessage();
  bool waitForMessage(uint8_t header, bool pollWhileWait = false, uint32_t timeout = 0);
  size_t getMessagePayload(uint8_t *buffer, size_t len);

  Stream &m_serialPort;
  uint32_t m_timeout;
  bool m_flushSerialBeforeTx;
  ITouchableListItem *m_touchableList;
};

#endif

#include <Nextion.h>
#include <INextionColourable.h>

#define NEXTION_PORT Serial1

Nextion nex(NEXTION_PORT);

void setup()
{
  Serial.begin(9600);

  NEXTION_PORT.begin(9600);
  nex.init();

  Serial.println(nex.clear(NEX_COL_BLUE));

  Serial.println(nex.drawCircle(50, 30, 10, NEX_COL_WHITE));
  Serial.println(nex.drawRect(70, 40, 15, 5, false, NEX_COL_GREEN));
  Serial.println(nex.drawRect(20, 60, 15, 5, true, NEX_COL_RED));
  Serial.println(nex.drawLine(150, 150, 200, 180, NEX_COL_YELLOW));
  Serial.println(nex.drawPicture(180, 180, 0));
  /* Serial.println(nex.drawPicture(50, 180, 10, 10, 0)); */
  Serial.println(nex.drawStr(50, 80, 200, 30, 0, "Hello, world!"));
}

void loop()
{
  nex.poll();
}

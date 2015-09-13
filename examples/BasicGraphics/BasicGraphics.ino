#include <Nextion.h>
#include <INextionColourable.h>

#define NEXTION_PORT Serial

Nextion nex(NEXTION_PORT);

void setup()
{
  pinMode(13, OUTPUT);
  
  Serial.begin(9600);
  
  NEXTION_PORT.begin(9600);  
  nex.init();
  
  nex.clear(NEX_COL_BLUE);
  
  nex.drawCircle(50, 30, 10, NEX_COL_WHITE);
  nex.drawRect(70, 40, 15, 5, false, NEX_COL_GREEN);
  nex.drawRect(20, 60, 15, 5, true, NEX_COL_RED);
  nex.drawLine(150, 150, 200, 180, NEX_COL_YELLOW);
  nex.drawPicture(180, 180, 0);
  //nex.drawPicture(50, 180, 10, 10, 0);
  nex.drawStr(50, 80, 200, 30, 0, "Hello, world!");
}

void loop()
{
  nex.poll();
}
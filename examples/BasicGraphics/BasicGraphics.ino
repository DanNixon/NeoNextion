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
  
  nex.clear(BLUE);
  
  nex.drawCircle(50, 30, 10, WHITE);
  nex.drawRect(70, 40, 15, 5, false, GREEN);
  nex.drawRect(20, 60, 15, 5, true, RED);
  nex.drawLine(150, 150, 200, 180, YELLOW);
  nex.drawPicture(180, 180, 0);
  //nex.drawPicture(50, 180, 10, 10, 0);
  nex.drawStr(50, 80, 200, 30, 0, "Hello, world!");
}

void loop()
{
  nex.poll();
}
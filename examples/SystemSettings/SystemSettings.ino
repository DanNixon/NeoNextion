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

  nex.sleep();
  delay(1000);
  nex.wake();
  delay(1000);
  nex.setBrightness(50);
  delay(1000);
  nex.setBrightness(20, true);
}

void loop()
{
  nex.poll();
}

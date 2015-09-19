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

  Serial.println(nex.sleep());
  delay(1000);
  Serial.println(nex.wake());
  delay(1000);
  Serial.println(nex.setBrightness(50));
	Serial.println(nex.getBrightness());
  delay(1000);
  Serial.println(nex.setBrightness(20, true));
	Serial.println(nex.getBrightness());
}

void loop()
{
  nex.poll();
}

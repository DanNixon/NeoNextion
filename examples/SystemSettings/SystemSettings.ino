#include <Nextion.h>
#include <INextionColourable.h>
#include <SoftwareSerial.h>

SoftwareSerial nextionSerial(10, 11); // RX, TX

Nextion nex(nextionSerial);

void setup()
{
  Serial.begin(9600);

  nextionSerial.begin(9600);
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

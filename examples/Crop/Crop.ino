#include <Nextion.h>
#include <NextionPage.h>
#include <NextionCrop.h>
#include <SoftwareSerial.h>

SoftwareSerial nextionSerial(10, 11); // RX, TX

Nextion nex(nextionSerial);
NextionPage pgCrop(nex, 4, 0, "pgCrop");
NextionCrop crop(nex, 4, 2, "crExCrop");

void setup()
{
  Serial.begin(9600);
  pinMode(13, OUTPUT);

  nextionSerial.begin(9600);
  nex.init();

  Serial.println(pgCrop.show());

  Serial.println(crop.attachCallback(&callback));
}

void loop()
{
  nex.poll();
}

void callback(NextionEventType type, INextionTouchable *widget)
{
  if (type == NEX_EVENT_PUSH)
    digitalWrite(13, HIGH);
  else if (type == NEX_EVENT_POP)
    digitalWrite(13, LOW);
}

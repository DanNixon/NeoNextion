#include <Nextion.h>
#include <NextionPage.h>
#include <NextionHotspot.h>
#include <SoftwareSerial.h>

SoftwareSerial nextionSerial(10, 11); // RX, TX

Nextion nex(nextionSerial);
NextionPage pgHotspot(nex, 5, 0, "pgHotspot");
NextionHotspot hotspot(nex, 5, 2, "hsExHotspot");

void setup()
{
  Serial.begin(9600);
  pinMode(13, OUTPUT);

  nextionSerial.begin(9600);
  nex.init();

  Serial.println(pgHotspot.show());

  Serial.println(hotspot.attachCallback(&callback));
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

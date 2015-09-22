#include <Nextion.h>
#include <NextionPage.h>
#include <NextionDualStateButton.h>
#include <SoftwareSerial.h>

SoftwareSerial nextionSerial(10, 11); // RX, TX

Nextion nex(nextionSerial);
NextionPage pgDsButton(nex, 11, 0, "pgDsButton");
NextionDualStateButton button(nex, 11, 2, "bExDsButton");

void setup()
{
  Serial.begin(9600);
  pinMode(13, OUTPUT);

  nextionSerial.begin(9600);
  nex.init();

  Serial.println(pgDsButton.show());

  Serial.println(button.attachCallback(&callback));

  Serial.println(button.isActive());
  Serial.println(button.setActive(true));
  Serial.println(button.isActive());
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
  {
    Serial.println(button.isActive());
    digitalWrite(13, LOW);
  }
}

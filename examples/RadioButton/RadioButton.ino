#include <Nextion.h>
#include <NextionPage.h>
#include <NextionRadioButton.h>
#include <SoftwareSerial.h>

SoftwareSerial nextionSerial(10, 11); // RX, TX

Nextion nex(nextionSerial);
NextionPage pgRadioButton(nex, 14, 0, "pgRadioButton");
NextionRadioButton radioButton(nex, 14, 2, "rbExRadButton");

void setup()
{
  Serial.begin(9600);
  pinMode(13, OUTPUT);

  nextionSerial.begin(9600);
  nex.init();

  Serial.println(pgRadioButton.show());

  Serial.println(radioButton.attachCallback(&callback));

  Serial.println(radioButton.isActive());
  Serial.println(radioButton.setActive(true));
  Serial.println(radioButton.isActive());
}

void loop()
{
  nex.poll();
}

void callback(NextionEventType type, INextionTouchable *widget)
{
  if (type == NEX_EVENT_PUSH)
  {
    digitalWrite(13, HIGH);
  }
  else if (type == NEX_EVENT_POP)
  {
    Serial.println(radioButton.isActive());
    digitalWrite(13, LOW);
  }
}

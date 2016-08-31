#include <Nextion.h>
#include <NextionPage.h>
#include <NextionCheckbox.h>
#include <SoftwareSerial.h>

SoftwareSerial nextionSerial(10, 11); // RX, TX

Nextion nex(nextionSerial);
NextionPage pgCheckbox(nex, 13, 0, "pgCheckbox");
NextionCheckbox checkbox(nex, 13, 2, "cbExCheckbox");

void setup()
{
  Serial.begin(9600);
  pinMode(13, OUTPUT);

  nextionSerial.begin(9600);
  nex.init();

  Serial.println(pgCheckbox.show());

  Serial.println(checkbox.attachCallback(&callback));

  Serial.println(checkbox.isActive());
  Serial.println(checkbox.setActive(true));
  Serial.println(checkbox.isActive());
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
    Serial.println(checkbox.isActive());
    digitalWrite(13, LOW);
  }
}

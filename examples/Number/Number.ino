#include <Nextion.h>
#include <NextionPage.h>
#include <NextionNumber.h>
#include <SoftwareSerial.h>

SoftwareSerial nextionSerial(10, 11); // RX, TX

Nextion nex(nextionSerial);
NextionPage pgNumber(nex, 12, 0, "pgNumber");
NextionNumber number(nex, 12, 2, "nExNumber");

void setup()
{
  Serial.begin(9600);
  pinMode(13, OUTPUT);

  nextionSerial.begin(9600);
  nex.init();

  Serial.println(pgNumber.show());

  Serial.println(number.attachCallback(&callback));

  Serial.println(number.setValue(42));

  Serial.println(number.setBackgroundColour(NEX_COL_BLUE));
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
    number.setValue(12345);
  }
  else if (type == NEX_EVENT_POP)
  {
    digitalWrite(13, LOW);
    number.setValue(99);
  }
}

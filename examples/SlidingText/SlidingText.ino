#include <Nextion.h>
#include <NextionPage.h>
#include <NextionSlidingText.h>
#include <SoftwareSerial.h>

SoftwareSerial nextionSerial(10, 11); // RX, TX

Nextion nex(nextionSerial);
NextionPage pgScrollingText(nex, 15, 0, "pgScrollText");
NextionSlidingText text(nex, 15, 2, "stExScrollText");

void setup()
{
  Serial.begin(9600);
  pinMode(13, OUTPUT);

  nextionSerial.begin(9600);
  nex.init();

  Serial.println(pgScrollingText.show());

  Serial.println(text.attachCallback(&callback));

  Serial.println(text.setText("Press me!"));
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
    text.setText("Hyah!");
  }
  else if (type == NEX_EVENT_POP)
  {
    digitalWrite(13, LOW);
    text.setText("You pressed me");
  }
}

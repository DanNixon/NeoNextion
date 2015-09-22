#include <Nextion.h>
#include <NextionPage.h>
#include <NextionPicture.h>
#include <SoftwareSerial.h>

SoftwareSerial nextionSerial(10, 11); // RX, TX

Nextion nex(nextionSerial);
NextionPage pgPicture(nex, 3, 0, "pgPicture");
NextionPicture picture(nex, 3, 2, "pExPicture");

void setup()
{
  Serial.begin(9600);
  pinMode(13, OUTPUT);

  nextionSerial.begin(9600);
  nex.init();

  Serial.println(pgPicture.show());

  Serial.println(picture.attachCallback(&callback));

  Serial.println(picture.getPictureID());
  Serial.println(picture.setPictureID(1));
  Serial.println(picture.getPictureID());
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

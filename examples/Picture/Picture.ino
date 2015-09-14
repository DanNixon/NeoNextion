#include <Nextion.h>
#include <NextionPage.h>
#include <NextionPicture.h>
#include <SoftwareSerial.h>

SoftwareSerial nextionSerial(10, 11); // RX, TX

Nextion nex(nextionSerial);
NextionPage pgPicture(&nex, 3, 0, "pgPicture");
NextionPicture picture(&nex, 3, 2, "pExPicture");

void setup()
{
	Serial.begin(9600);
  pinMode(13, OUTPUT);

  nextionSerial.begin(9600);
  nex.init();

  Serial.println(pgPicture.show());

  Serial.println(picture.attachPressEvent(&press_callback));
  Serial.println(picture.attachReleaseEvent(&release_callback));

  Serial.println(picture.setPictureID(1));
}

void loop()
{
  nex.poll();
}

void press_callback(INextionTouchable *widget)
{
  digitalWrite(13, HIGH);
}

void release_callback(INextionTouchable *widget)
{
  digitalWrite(13, LOW);
}

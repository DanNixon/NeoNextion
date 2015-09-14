#include <Nextion.h>
#include <NextionPage.h>
#include <NextionCrop.h>
#include <SoftwareSerial.h>

SoftwareSerial nextionSerial(10, 11); // RX, TX

Nextion nex(nextionSerial);
NextionPage pgCrop(&nex, 4, 0, "pgCrop");
NextionCrop crop(&nex, 4, 2, "crExCrop");

void setup()
{
	Serial.begin(9600);
  pinMode(13, OUTPUT);

  nextionSerial.begin(9600);
  nex.init();

  Serial.println(pgCrop.show());

  Serial.println(crop.attachPressEvent(&press_callback));
  Serial.println(crop.attachReleaseEvent(&release_callback));
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

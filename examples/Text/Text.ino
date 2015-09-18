#include <Nextion.h>
#include <NextionPage.h>
#include <NextionText.h>
#include <SoftwareSerial.h>

SoftwareSerial nextionSerial(10, 11); // RX, TX

Nextion nex(nextionSerial);
NextionPage pgText(nex, 1, 0, "pgText");
NextionText text(nex, 1, 2, "tExText");

void setup()
{
	Serial.begin(9600);
  pinMode(13, OUTPUT);

  nextionSerial.begin(9600);
  nex.init();

  Serial.println(pgText.show());

  Serial.println(text.attachPressEvent(&press_callback));
  Serial.println(text.attachReleaseEvent(&release_callback));

  Serial.println(text.setText("Press me!"));

  Serial.println(text.setBackgroundColour(NEX_COL_BLUE));
}

void loop()
{
  nex.poll();
}

void press_callback(INextionTouchable *widget)
{
  digitalWrite(13, HIGH);
  text.setText("Hyah!");
}

void release_callback(INextionTouchable *widget)
{
  digitalWrite(13, LOW);
  text.setText("You pressed me");
}

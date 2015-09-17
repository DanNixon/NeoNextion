#include <Nextion.h>
#include <NextionPage.h>
#include <NextionSlider.h>
#include <SoftwareSerial.h>

SoftwareSerial nextionSerial(10, 11); // RX, TX

Nextion nex(nextionSerial);
NextionPage pgSlider(&nex, 8, 0, "pgSlider");
NextionSlider slider(&nex, 8, 2, "sExSlider");

void setup()
{
	Serial.begin(9600);
  pinMode(13, OUTPUT);

  nextionSerial.begin(9600);
  nex.init();

  Serial.println(pgSlider.show());

  Serial.println(slider.setBackgroundColour(NEX_COL_BLUE));
  Serial.println(slider.setForegroundColour(NEX_COL_YELLOW));
	
	Serial.println(slider.getBackgroundColour());
  Serial.println(slider.getForegroundColour());

  Serial.println(slider.attachPressEvent(&press_callback));
  Serial.println(slider.attachReleaseEvent(&release_callback));
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
  Serial.println(slider.getValue());
}

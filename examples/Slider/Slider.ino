#include <Nextion.h>
#include <NextionPage.h>
#include <NextionSlider.h>

#define NEXTION_PORT Serial

Nextion nex(NEXTION_PORT);
NextionPage pgSlider(&nex, 8, 0, "pgSlider");
NextionSlider slider(&nex, 8, 2, "sExSlider");

void setup()
{
  pinMode(13, OUTPUT);

  NEXTION_PORT.begin(9600);
  nex.init();

  /* Serial.begin(9600); */

  pgSlider.show();

  slider.setBackgroundColour(NEX_COL_BLUE);
  slider.setForegroundColour(NEX_COL_YELLOW);

  slider.attachPressEvent(&press_callback);
  slider.attachReleaseEvent(&release_callback);
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

  /* Serial.println(slider.getValue()); */
}

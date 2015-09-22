#include <Nextion.h>
#include <NextionPage.h>
#include <NextionSlider.h>

#define NEXTION_PORT Serial1

Nextion nex(NEXTION_PORT);
NextionPage pgSlider(nex, 8, 0, "pgSlider");
NextionSlider slider(nex, 8, 2, "sExSlider");

void setup()
{
  Serial.begin(9600);
  pinMode(13, OUTPUT);

  NEXTION_PORT.begin(9600);
  nex.init();

  Serial.println(pgSlider.show());

  Serial.println(slider.setBackgroundColour(NEX_COL_BLUE));
  Serial.println(slider.setForegroundColour(NEX_COL_YELLOW));

  Serial.println(slider.attachCallback(&callback));
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
  {
    Serial.println(slider.getValue());
    digitalWrite(13, LOW);
  }
}

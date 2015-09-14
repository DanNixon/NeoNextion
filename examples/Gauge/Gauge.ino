#include <Nextion.h>
#include <NextionPage.h>
#include <NextionGauge.h>

#define NEXTION_PORT Serial

Nextion nex(NEXTION_PORT);
NextionPage pgGauge(&nex, 6, 0, "pgGauge");
NextionGauge gauge(&nex, 6, 2, "gExGauge");

uint32_t startTime = 0;

void setup()
{
  pinMode(13, OUTPUT);

  NEXTION_PORT.begin(9600);
  nex.init();

  pgGauge.show();

  gauge.attachPressEvent(&press_callback);
  gauge.attachReleaseEvent(&release_callback);

  gauge.setBackgroundColour(NEX_COL_BLACK);
  gauge.setForegroundColour(NEX_COL_RED);

  startTime = millis();
}

void loop()
{
  nex.poll();

  if (millis() - startTime > 500)
  {
    uint16_t value = gauge.getValue();
    value += 10;
    if (value > 400)
      value = 0;
    gauge.setValue(value);
    startTime = millis();
  }
}

void press_callback(INextionTouchable *widget)
{
  digitalWrite(13, HIGH);
}

void release_callback(INextionTouchable *widget)
{
  digitalWrite(13, LOW);
}

#include <Nextion.h>
#include <NextionPage.h>
#include <NextionGauge.h>
#include <SoftwareSerial.h>

SoftwareSerial nextionSerial(10, 11); // RX, TX

Nextion nex(nextionSerial);
NextionPage pgGauge(nex, 6, 0, "pgGauge");
NextionGauge gauge(nex, 6, 2, "gExGauge");

uint32_t startTime = 0;

void setup()
{
  Serial.begin(9600);
  pinMode(13, OUTPUT);

  nextionSerial.begin(9600);
  nex.init();

  Serial.println(pgGauge.show());

  Serial.println(gauge.attachCallback(&callback));

  Serial.println(gauge.setBackgroundColour(NEX_COL_BLACK));
  Serial.println(gauge.setForegroundColour(NEX_COL_RED));

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

void callback(NextionEventType type, INextionTouchable *widget)
{
  if (type == NEX_EVENT_PUSH)
    digitalWrite(13, HIGH);
  else if (type == NEX_EVENT_POP)
    digitalWrite(13, LOW);
}

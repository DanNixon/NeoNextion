#include <Nextion.h>
#include <NextionPage.h>
#include <NextionProgressBar.h>
#include <SoftwareSerial.h>

SoftwareSerial nextionSerial(10, 11); // RX, TX

Nextion nex(nextionSerial);
NextionPage pgProgressBar(nex, 2, 0, "pgProgressBar");
NextionProgressBar progressBar(nex, 2, 2, "pbExProgBar");

uint32_t startTime = 0;

void setup()
{
  Serial.begin(9600);
  pinMode(13, OUTPUT);

  nextionSerial.begin(9600);
  nex.init();

  Serial.println(pgProgressBar.show());

  Serial.println(progressBar.attachCallback(&callback));

  Serial.println(progressBar.setBackgroundColour(NEX_COL_YELLOW));
  Serial.println(progressBar.setForegroundColour(NEX_COL_BLACK));

  startTime = millis();
}

void loop()
{
  nex.poll();

  if (millis() - startTime > 500)
  {
    uint16_t value = progressBar.getValue();
    value += 10;
    if (value > 100)
      value = 0;
    progressBar.setValue(value);
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

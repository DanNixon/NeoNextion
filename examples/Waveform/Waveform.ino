#include <Nextion.h>
#include <NextionPage.h>
#include <NextionWaveform.h>
#include <SoftwareSerial.h>

SoftwareSerial nextionSerial(10, 11); // RX, TX

Nextion nex(nextionSerial);
NextionPage pgWaveform(nex, 7, 0, "pgWaveform");
NextionWaveform waveform(nex, 7, 2, "wExWaveform");

void setup()
{
  Serial.begin(9600);
  pinMode(13, OUTPUT);

  nextionSerial.begin(9600);
  nex.init();

  Serial.println(pgWaveform.show());

  Serial.println(waveform.attachCallback(&callback));

  Serial.println(waveform.setGridWidth(5));
  Serial.println(waveform.getGridWidth());

  Serial.println(waveform.setGridHeight(10));
  Serial.println(waveform.getGridHeight());

  Serial.println(waveform.setChannelColour(0, NEX_COL_WHITE));

  for (uint16_t i = 0; i < 100; i++)
  {
    waveform.addValue(0, i);
    waveform.addValue(1, i + 10);
    waveform.addValue(2, i + 20);
    waveform.addValue(3, i + 30);
  }
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

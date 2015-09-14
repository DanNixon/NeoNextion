#include <Nextion.h>
#include <NextionPage.h>
#include <NextionWaveform.h>

#define NEXTION_PORT Serial

Nextion nex(NEXTION_PORT);
NextionPage pgWaveform(&nex, 7, 0, "pgWaveform");
NextionWaveform waveform(&nex, 7, 2, "wExWaveform");

void setup()
{
  pinMode(13, OUTPUT);

  NEXTION_PORT.begin(9600);
  nex.init();

  pgWaveform.show();

  waveform.attachPressEvent(&press_callback);
  waveform.attachReleaseEvent(&release_callback);

  /* Serial.begin(9600); */
  /* Serial.println(waveform.addValue(0, 5)); */
  /* Serial.println(waveform.addValue(1, 2)); */
  /* Serial.println(waveform.addValue(2, 4)); */
  /* Serial.println(waveform.addValue(3, 2)); */
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

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

  Serial.println(waveform.attachPressEvent(&press_callback));
  Serial.println(waveform.attachReleaseEvent(&release_callback));

  Serial.println(waveform.addValue(0, 5));
  Serial.println(waveform.addValue(1, 2));
  Serial.println(waveform.addValue(2, 4));
  Serial.println(waveform.addValue(3, 2));
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

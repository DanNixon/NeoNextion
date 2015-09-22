#include <Nextion.h>
#include <NextionPage.h>
#include <SoftwareSerial.h>

SoftwareSerial nextionSerial(10, 11); // RX, TX

Nextion nex(nextionSerial);

NextionPage pgButton      (nex, 0,  0, "pgButton");
NextionPage pgText        (nex, 1,  0, "pgText");
NextionPage pgProgressBar (nex, 2,  0, "pgProgressBar");
NextionPage pgPicture     (nex, 3,  0, "pgPicture");
NextionPage pgCrop        (nex, 4,  0, "pgCrop");
NextionPage pgHotspot     (nex, 5,  0, "pgHotspot");
NextionPage pgGauge       (nex, 6,  0, "pgGauge");
NextionPage pgWaveform    (nex, 7,  0, "pgWaveform");
NextionPage pgSlider      (nex, 8,  0, "pgSlider");
NextionPage pgTimer       (nex, 9,  0, "pgTimer");
NextionPage pgVariable    (nex, 10, 0, "pgVariable");

void setup()
{
  Serial.begin(9600);

  nextionSerial.begin(9600);
  nex.init();

  Serial.println(pgGauge.show());

  Serial.println(nex.getCurrentPage());
  Serial.println(pgGauge.isShown());
  Serial.println(pgButton.isShown());
}

void loop()
{
  nex.poll();
}

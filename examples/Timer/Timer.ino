#include <Nextion.h>
#include <NextionPage.h>
#include <NextionTimer.h>
#include <SoftwareSerial.h>

SoftwareSerial nextionSerial(10, 11); // RX, TX

Nextion nex(nextionSerial);
NextionPage pgTimer(nex, 9, 0, "pgTimer");
NextionTimer timer(nex, 9, 2, "tmExTimer");

void setup()
{
  Serial.begin(9600);
  pinMode(13, OUTPUT);

  nextionSerial.begin(9600);
  nex.init();

  Serial.println(pgTimer.show());

  // Serial.println(timer.attachEvent(&timer_callback));
  Serial.println(timer.setCycle(1000));
  Serial.println(timer.enable());
}

void loop()
{
  nex.poll();
}

void timer_callback(NextionEventType type, INextionTouchable *widget)
{
  digitalWrite(13, !digitalRead(13));
}

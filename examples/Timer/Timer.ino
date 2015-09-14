#include <Nextion.h>
#include <NextionPage.h>
#include <NextionTimer.h>

#define NEXTION_PORT Serial

Nextion nex(NEXTION_PORT);
NextionPage pgTimer(&nex, 9, 0, "pgTimer");
NextionTimer timer(&nex, 9, 2, "tmExTimer");

void setup()
{
  pinMode(13, OUTPUT);

  NEXTION_PORT.begin(9600);
  nex.init();

  pgTimer.show();

  timer.attachEvent(&timer_callback);
  timer.setCycle(1000);
  timer.enable();
}

void loop()
{
  nex.poll();
}

void timer_callback(INextionTouchable *widget)
{
  digitalWrite(13, !digitalRead(13));
}

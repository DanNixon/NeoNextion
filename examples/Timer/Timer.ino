#include <Nextion.h>
#include <NextionPage.h>
#include <NextionHotspot.h>

#define NEXTION_PORT Serial

Nextion nex(NEXTION_PORT);
NextionPage pgHotspot(&nex, 5, 0, "pgHotspot");
NextionHotspot hotspot(&nex, 5, 2, "hsExHotspot");

void setup()
{
  pinMode(13, OUTPUT);
  
  NEXTION_PORT.begin(9600);  
  nex.init();
  
  pgHotspot.show();

  hotspot.attachPressEvent(&press_callback);
  hotspot.attachReleaseEvent(&release_callback);
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
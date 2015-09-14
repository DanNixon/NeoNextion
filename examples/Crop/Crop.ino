#include <Nextion.h>
#include <NextionPage.h>
#include <NextionCrop.h>

#define NEXTION_PORT Serial

Nextion nex(NEXTION_PORT);
NextionPage pgCrop(&nex, 4, 0, "pgCrop");
NextionCrop crop(&nex, 4, 2, "crExCrop");

void setup()
{
  pinMode(13, OUTPUT);

  NEXTION_PORT.begin(9600);
  nex.init();

  pgCrop.show();

  crop.attachPressEvent(&press_callback);
  crop.attachReleaseEvent(&release_callback);
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

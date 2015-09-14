#include <Nextion.h>
#include <NextionPage.h>
#include <NextionPicture.h>

#define NEXTION_PORT Serial

Nextion nex(NEXTION_PORT);
NextionPage pgPicture(&nex, 3, 0, "pgPicture");
NextionPicture picture(&nex, 3, 2, "pExPicture");

void setup()
{
  pinMode(13, OUTPUT);

  NEXTION_PORT.begin(9600);
  nex.init();

  pgPicture.show();

  picture.attachPressEvent(&press_callback);
  picture.attachReleaseEvent(&release_callback);

  picture.setPictureID(1);
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

#include <Nextion.h>
#include <NextionPage.h>
#include <NextionText.h>

#define NEXTION_PORT Serial

Nextion nex(NEXTION_PORT);
NextionPage pgText(&nex, 1, 0, "pgText");
NextionText text(&nex, 1, 2, "tExText");

void setup()
{
  pinMode(13, OUTPUT);

  NEXTION_PORT.begin(9600);
  nex.init();

  pgText.show();

  text.attachPressEvent(&press_callback);
  text.attachReleaseEvent(&release_callback);

  text.setText("Press me!");

  text.setBackgroundColour(NEX_COL_BLUE);
}

void loop()
{
  nex.poll();
}

void press_callback(INextionTouchable *widget)
{
  digitalWrite(13, HIGH);
  text.setText("Hyah!");
}

void release_callback(INextionTouchable *widget)
{
  digitalWrite(13, LOW);
  text.setText("You pressed me");
}

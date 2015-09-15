#include <Nextion.h>
#include <NextionPage.h>
#include <NextionButton.h>

#define NEXTION_PORT Serial1

Nextion nex(NEXTION_PORT);
NextionPage pgButton(&nex, 0, 0, "pgButton");
NextionButton button(&nex, 0, 1, "bEgButton");

void setup()
{
	Serial.begin(9600);
	pinMode(13, OUTPUT);

  NEXTION_PORT.begin(9600);
  nex.init();

  Serial.println(pgButton.show());

  Serial.println(button.attachPressEvent(&press_callback));
  Serial.println(button.attachReleaseEvent(&release_callback));

  Serial.println(button.setHAlignment(NEX_FA_LEFT_UP));
  Serial.println(button.setVAlignment(NEX_FA_LEFT_UP));
  Serial.println(button.setFont(1));
  Serial.println(button.setText("Press me!"));

  char buffer[50];
  button.getText(buffer, 50);
  Serial.println(buffer);

  Serial.println(button.setBackgroundColour(NEX_COL_BLUE));
}

void loop()
{
  nex.poll();
}

void press_callback(INextionTouchable *widget)
{
  digitalWrite(13, HIGH);
  button.setText("Hyah!");
}

void release_callback(INextionTouchable *widget)
{
  digitalWrite(13, LOW);
  button.setText("You pressed me");
}

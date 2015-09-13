#include <Nextion.h>
#include <NextionButton.h>

#define NEXTION_PORT Serial

Nextion nex(NEXTION_PORT);
NextionButton button(&nex, 0, 1, "button1");

void setup()
{
  pinMode(13, OUTPUT);
  
  NEXTION_PORT.begin(9600);  
  nex.init();

  button.attachPressEvent(&press_callback);
  button.attachReleaseEvent(&release_callback);
  
  button.setText("Press me!");
  
  /* Serial.begin(9600); */
  char buffer[50];
  button.getText(buffer, 50);
  /* Serial.println(buffer); */
  
  button.setBackgroundColour(BLUE);
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
#include <Nextion.h>
#include <NextionPage.h>
#include <NextionVariableNumeric.h>
#include <NextionVariableString.h>

#define NEXTION_PORT Serial

Nextion nex(NEXTION_PORT);
NextionPage pgVariable(&nex, 10, 0, "pgVariable");
NextionVariableNumeric var1(&nex, 10, 2, "vaExVariableN");
NextionVariableString var2(&nex, 10, 3, "vaExVariableS");

void setup()
{
  pinMode(13, OUTPUT);

  NEXTION_PORT.begin(9600);
  nex.init();

  pgVariable.show();

  /* Serial.begin(9600); */

  var1.setValue(4);
  /* Serial.println(var1.getValue()); */

  var2.setText("Hello!");
  /* char buffer[20]; */
  /* if(var2.getText(buffer, 20)) */
    /* Serial.println(buffer); */
}

void loop()
{
  nex.poll();
}

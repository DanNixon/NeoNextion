#include <Nextion.h>
#include <NextionPage.h>
#include <NextionProgressBar.h>

#define NEXTION_PORT Serial

Nextion nex(NEXTION_PORT);
NextionPage pgProgressBar(&nex, 2, 0, "pgProgressBar");
NextionProgressBar progressBar(&nex, 2, 2, "pbExProgBar");

uint32_t startTime = 0;

void setup()
{
  pinMode(13, OUTPUT);

  NEXTION_PORT.begin(9600);
  nex.init();

  pgProgressBar.show();

  progressBar.attachPressEvent(&press_callback);
  progressBar.attachReleaseEvent(&release_callback);

  progressBar.setBackgroundColour(NEX_COL_YELLOW);
  progressBar.setForegroundColour(NEX_COL_BLACK);

  startTime = millis();
}

void loop()
{
  nex.poll();

  if(millis() - startTime > 500)
  {
    uint16_t value = progressBar.getValue();
    value += 10;
    if(value > 100)
      value = 0;
    progressBar.setValue(value);
    startTime= millis();
  }
}

void press_callback(INextionTouchable *widget)
{
  digitalWrite(13, HIGH);
}

void release_callback(INextionTouchable *widget)
{
  digitalWrite(13, LOW);
}

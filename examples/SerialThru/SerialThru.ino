/*
 * A simple script to allow programming and debugging
 * of a display device using the Nextion editor when
 * the display its self is still connected in situ.
 */

#include <SoftwareSerial.h>

SoftwareSerial nextionSerial(10, 11); // RX, TX

#define HOST_PORT Serial

#define BAUD 9600

void setup()
{
  HOST_PORT.begin(BAUD);
  nextionSerial.begin(BAUD);
}

void loop()
{
  while(HOST_PORT.available())
    nextionSerial.write(HOST_PORT.read());

  while(nextionSerial.available())
    HOST_PORT.write(nextionSerial.read());
}

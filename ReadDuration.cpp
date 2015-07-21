/**
 * ReadDuration class
 * version 2.3
 * 
 * returns 0 during normal ops
 * returns 1 once, and ends, if button is pressed
 * returns -1 if duration is reached without button press
 * 
 * Written by ZAT Lab - Todd Zebert and son, 2015
 * GNU General Public License (GPL) version 3
 */

#include <Arduino.h>
#include "ReadDuration.h"

ReadDuration::ReadDuration () {
 // nothing to do here?
};

void ReadDuration::Begin (int p, unsigned long rT) // pin, readTime
{
  buttonPin = p;
  readTime = rT;
  lastUpdate = millis();
  r = 0;
};

int ReadDuration::Update ()
{
  currentMs = millis();
  
  if ((currentMs - lastUpdate) >= readTime) {
    r = -1;
  } else {
    i = digitalRead(buttonPin);
    if (i == HIGH) {
      r = 1;
    }
  }

  return r;
};

/*
int ReadDuration::Hault ();
{
}
*/

unsigned long ReadDuration::GetElapsedTime ()
{
  currentMs = millis();
  
  return currentMs - lastUpdate;
}


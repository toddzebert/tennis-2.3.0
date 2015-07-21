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
 
#ifndef ReadDuration_h
#define ReadDuration_h

#include <Arduino.h>

class ReadDuration
{
private:
  unsigned long currentMs;
  unsigned long lastUpdate;
  unsigned long readTime;
  int buttonPin;
  int r;
  int i;

public:
  ReadDuration ();

  void Begin (int p, unsigned long rT); // pin, readTime

  int Update ();

  // int Hault ();

  unsigned long GetElapsedTime ();

};

#endif

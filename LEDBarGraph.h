/*
 * LED Bar Graph
 * version 2.3
 * 
 * Turn on some number of LEDs of a series, starting from first or last, for some amount of time
 * 
 * Written by ZAT Lab - Todd Zebert and son, 2015
 * GNU General Public License (GPL) version 3
 */
 
#ifndef LEDBarGraph_h
#define LEDBarGraph_h

#include <Arduino.h>

class LEDBarGraph
{

private:

  // enum state_t { START, ON, PAUSING, DONE };
  // state_t state;

  unsigned long currentMs;
  unsigned long lastUpdate;
  unsigned long onTime, pauseTime;
  

  int i;
  int r;

  int * pins;
  int pinsLen;
  // int num;
  // int start;
  // int delta;
  bool hault;

  void AllLow ();

public:
  LEDBarGraph (int * p);

  void Begin (int delta, int num, unsigned long oT); // Direction, Number, OnTime

  int Update ();

  int Hault ();
};

#endif


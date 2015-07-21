/*
 * LED Sequence
 * version 2.3
 * 
 * Steps through illuminating LEDs in order
 * 
 * Written by ZAT Lab - Todd Zebert and son, 2015
 * GNU General Public License (GPL) version 3
 */
 
#ifndef LEDSequence_h
#define LEDSequence_h

#include <Arduino.h>

class LEDSequence
{

private:
  enum state_t { START, ON, PAUSING, DONE };
  state_t state;

  unsigned long currentMs;
  unsigned long lastUpdate;
  unsigned long onTime, pauseTime;

  int i;
  int r;

  int * pins;
  int maxPin;
  int delta;
  bool hault;

public:
  LEDSequence (int * p);

  void Begin (int d, unsigned long oT, unsigned long pT);

  int Update ();

  int Hault ();
};

#endif


/*
 * LED Flasher
 * version 2.3
 * 
 * flash an LED an odd number of half-cycles, with a fixed time per half-cycle, ie: on off on (off, but no wait)
 * 
 * set phaseTime of 0 and it'll always remain lit
 * 
 * Written by ZAT Lab - Todd Zebert and son, 2015
 * GNU General Public License (GPL) version 3
 */
 
#ifndef LEDFlasher_h
#define LEDFlasher_h

#include <Arduino.h>

class LEDFlasher
{

private:
  enum state_t { START, ON, PAUSING, DONE };
  state_t state;

  unsigned long currentMs;
  unsigned long lastUpdate;
  unsigned long phaseTime;
  
  int i;
  
  int pin = 0;
  int num;
  bool hault;

public:
  LEDFlasher ();

  void Begin (int p, int n, unsigned long pt); // LED pin, number of flashes, phase time (each 1/2 cycle)

  int Update ();

  int Hault ();
};

#endif


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

#include <Arduino.h>
#include "LEDFlasher.h"

LEDFlasher::LEDFlasher ()
{
};


void LEDFlasher::Begin (int p, int n, unsigned long pT) // LED pin, number of flashes, time of each 1/2 cycle
{
  state = ON;
  phaseTime = pT;
  num = n;
  pin = p;
  i = 1;
  lastUpdate = millis();
  
  digitalWrite(pin, HIGH);
};


int LEDFlasher::Update ()
{
  currentMs = millis();
  
  // 
  switch (state) {
    case ON:
      if (phaseTime && ((currentMs - lastUpdate) >= phaseTime)) {
        digitalWrite(pin, LOW);
        if (i == num) { // are we done?
          state = DONE; // there is no final "pausing" state - that could be a future option @TODO
        } else {
          lastUpdate = millis();
          state = PAUSING;
        };
      };
      break;

    case PAUSING:
      if ((currentMs - lastUpdate) >= phaseTime) {
        lastUpdate = millis();
        digitalWrite(pin, HIGH);
        i++;
        state = ON;
      };
      break;

    // case DONE: no need
  }

};


int LEDFlasher::Hault ()
{
  if (pin) { // in case Hault called before Begin
    state = DONE;
    digitalWrite(pin, LOW);
  }
}


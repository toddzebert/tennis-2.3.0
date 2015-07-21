/*
 * LED Sequence
 * version 2.3
 * 
 * Steps through illuminating LEDs in order
 * 
 * Written by ZAT Lab - Todd Zebert and son, 2015
 * GNU General Public License (GPL) version 3
 */

#include <Arduino.h>
#include "LEDSequence.h"

// pass in pins (array)
LEDSequence::LEDSequence (int * p)
{
  pins = p;
  
  // find last valid pin
  maxPin = 0;
  while (pins[maxPin+1] != -1) {
    maxPin++;
  }
};


// delta {-1, 1}. onTime (ms), pauseTime (ms)
void LEDSequence::Begin (int d, unsigned long oT, unsigned long pT)
{
  delta = d;
  
  i = 0; // first, assume d > 0
  // if not, find correct i
  if (d < 0) { 
    i = maxPin;
  }
  
  onTime = oT;
  pauseTime = pT;
  hault = false;
  state = START;
  r = 0;
};


int LEDSequence::Update ()
{
  currentMs = millis();
  
  switch (state) {
    case START: 
      if (hault) {
        state = DONE;
        r = 1;
      } else if (i <= maxPin && i >= 0) {
        digitalWrite(pins[i], HIGH);
        lastUpdate = millis();
        state = ON;
      } else {
        state = DONE;
        r = 1;
      }
      break;
      
    case ON:
      if ((currentMs - lastUpdate) >= onTime) {
        digitalWrite(pins[i], LOW); 
        lastUpdate = currentMs;
        state = PAUSING;
      }
      break;
      
    case PAUSING:
      if ((currentMs - lastUpdate) >= pauseTime) {
        i += delta;
        state = START;
      }
      break;

    // case DONE:  // not needed
    
  } // switch

  return r;
}; // .update

int LEDSequence::Hault ()
{
  hault = true;
  digitalWrite(pins[i], LOW); // turn off pin in case it's on
  
  return i; // return pin number in case it's needed
};


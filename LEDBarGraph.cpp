/*
 * LED Bar Graph
 * version 2.3
 * 
 * Turn on some number of LEDs of a series, starting from first or last, for some amount of time
 * 
 * Written by ZAT Lab - Todd Zebert and son, 2015
 * GNU General Public License (GPL) version 3
 */

#include <Arduino.h>
#include "LEDBarGraph.h"

// pass in pins (array)
LEDBarGraph::LEDBarGraph (int * p)
{
  pins = p;

  // find pinLen by finding last valid index
  i = 0;
  while (pins[i+1] != -1) {
    i++;
  }
  pinsLen = i;
};


void LEDBarGraph::Begin (int delta, int num, unsigned long oT) // dir aka delta {-1, 1}, Number, OnTime
{
  onTime = oT;
  hault = false;
  
  if (num > (pinsLen + 1)) { // pins array starts at 0
    // pinsLen = -1; // not sure why I would have wanted to do that
    return; // this is an error.  @TODO report it with an actual return value?
  }

  lastUpdate = millis();
  
  if (delta > 0) {
    for (i = 0; i < num; i += delta) {
      digitalWrite(pins[i], HIGH);
    }
  } else if (delta < 0) {
    for (i = pinsLen; i > (pinsLen - num); i += delta) {
      digitalWrite(pins[i], HIGH);
    }
  }

  r = 0;
};

// part of the loop()
int LEDBarGraph::Update ()
{
  currentMs = millis();

  // the !r part is in case we've already haulted (r=0) but yet somebody called ::Update again...
  if (!r && ((currentMs - lastUpdate) >= onTime)) {
    AllLow();
    r = 1;
  } else {
    r = 0;
  }

  return r;
}; // .update


// finish if requested
int LEDBarGraph::Hault ()
{
  hault = true;
  AllLow();
};


// Somewhat of a cheat, instead of just turning off what we turned on, turn all off
void LEDBarGraph::AllLow ()
{
  for (i = 0; i <= pinsLen; i += 1) {
    digitalWrite(pins[i], LOW);
  }
};


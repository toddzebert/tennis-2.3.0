/**
 * Music class
 * version 2.3
 * 
 * returns 0 during normal ops
 * returns 1 once, when finished
 * 
 * Written by ZAT Lab - Todd Zebert and son, 2015
 * GNU General Public License (GPL) version 3
 */

#include <Arduino.h>
#include "Music.h"
 
Music::Music (int sp, int * t, int * tD)
{
  speakerPin = sp;
  tones = t;
  tonesDur = tD;
};

void Music::Begin () {
   pinMode(speakerPin, OUTPUT);
   state = PLAY;
   i = 0;
   r = 0;
}

int Music::Update ()
{
  currentMs = millis();
  
  switch (state) {
    case PLAY: 
      if (tones[i] != -1) {
        // start tone
        tone(speakerPin, tones[i]);
        toneStartMs = currentMs;
        state = PLAYING;
        playDur = 1000/tonesDur[i];
        pauseDur = 333/tonesDur[i];
      } else {
        state = DONE;
        r = 1;
      }
      break;
      
    case PLAYING:
      if ((currentMs - toneStartMs) >= playDur) {
        // end tone
        noTone(speakerPin);
        toneStartMs = currentMs;
        state = PAUSING;
      }
      break;
      
    case PAUSING:
      if ((currentMs - toneStartMs) >= pauseDur) {
        i++;
        state = PLAY;
      }
      break;

    // case DONE:  // no action
    
  } // switch

  return r;
}; // .update

unsigned long Music::getTotalDur ()
{
  int j = 0;
  totalDur = 0;
  
  while (tones[j] != -1) { 
    totalDur += 1000/tonesDur[j];
    totalDur += 333/tonesDur[j];
    j++;
  }

  return totalDur;
}

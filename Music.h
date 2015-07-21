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
 
#ifndef Music_h
#define Music_h

#include <Arduino.h>

class Music
{
private:
  enum state_t { PLAY, PLAYING, PAUSING, DONE };
  state_t state;
  
  int * tones, * tonesDur;
  
  int i;
  int r;
  int speakerPin;
  
  unsigned long lastUpdate;
  unsigned long currentMs;
  unsigned long toneStartMs;
  unsigned long playDur, pauseDur, totalDur;


public:
  Music (int sp, int * t, int * tD);

  void Begin ();
  
  int Update ();

  unsigned long getTotalDur ();
    
}; // Music

#endif

/**
 * Class Tennis
 * version 2.3
 * 
 * Or "pong"
 * 
 * Written by ZAT Lab - Todd Zebert and son, 2015
 * GNU General Public License (GPL) version 3
 */
 
#ifndef Tennis_h
#define Tennis_h

#include <Arduino.h>
#include "Music.h"
#include "LEDSequence.h"
#include "LEDBarGraph.h"
#include "ReadDuration.h"
#include "LEDFlasher.h"

class Tennis
{

private:
  // @NOTE static int 
  int travelPins[7] = {11, 10, 9, 6, 5, 3, -1};
  int travelPinsLen = (sizeof(travelPins) / sizeof(int)); // sizeOf counts bytes
  
  int speakerPin = 8;

  int startTones[11] =    {261, 277, 294, 311, -1}; // ,  330, 349, 370, 392, 415, 440, -1};
  int startTonesDur[10] = {3,   2,   3,   3}; // ,     3,   3,   3,   3,   3,   3  };
  
  int failTones[3] =    {415, 392, -1}; // Bb (A#) 466, then A 440, then Ab (G#), then G
  int failTonesDur[2] = {2,   3/2};
  
  int winTones[6] =     {1397, 880, 1397, 1568, 2093, -1}; // F / A / F / G / C
  int winTonesDur[5] =  {2,    2,   2,    2,    2};
  
  char inputButtonState;
  int i;
  int dir;
  int button;
  int player2score, player12score;
  // int fault;
  int x;

  const int player2InputPin = 2;
  const int player12InputPin = 12;
  const int player2FaultPin = 4;
  const int player12FaultPin = 13;

  unsigned long travelEndTime;
  // const unsigned long hitTimeMax = 500; // was 1000;
  const unsigned long hitTimeMult = 3;
  unsigned long scoreDisplayTime;

  unsigned long travelWait; // was = 100;
  const unsigned long travelWaitMin = 40; // 70;
  const unsigned long travelWaitMax = 300; // 140;

  enum state_t { INTRO, SERVE, TRAVEL, RETURN, SCORE, SCORE_UPDATE, DONE, DONE_UPDATE };
  state_t state;

  enum fault_t { NONE, EARLY, LATE };
  fault_t returnFault;

  int faultPin;

  Music introMusic;

  Music faultMusic;

  Music winMusic;

  LEDSequence travel;

  LEDBarGraph scoreDisplay;

  ReadDuration returnButton;

  LEDFlasher faultLED;
  
public:
  Tennis ();

  void Begin ();
  
  int Update ();
}; // Tennis

#endif

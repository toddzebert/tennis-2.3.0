/**
 * Class Tennis
 * version 2.3
 * 
 * Or "pong"
 * 
 * Written by ZAT Lab - Todd Zebert and son, 2015
 * GNU General Public License (GPL) version 3
 */
 
 #include <Arduino.h>
#include "Music.h"
#include "Tennis.h"
#include "LEDSequence.h"
#include "LEDBarGraph.h"
#include "ReadDuration.h"
#include "LEDFlasher.h"

#define SERIAL_DEBUG true
#define SERIAL_COMMENTARY true

Tennis::Tennis ()
  : introMusic(speakerPin, startTones, startTonesDur)
  , faultMusic(speakerPin, failTones, failTonesDur)
  , winMusic(speakerPin, winTones, winTonesDur)
  , travel(travelPins)
  , returnButton()
  , scoreDisplay(travelPins)
  , faultLED()
{

  player2score = 0;
  player12score = 0;

  scoreDisplayTime = faultMusic.getTotalDur();

};

void Tennis::Begin ()
{
  Serial.begin(9600);
  
    #if defined SERIAL_DEBUG
    Serial.print("Score, past faultMusic.getTotalDur:");
    Serial.println(scoreDisplayTime);
    #endif

  // travel LEDs
  pinMode(9, OUTPUT); // Initialize Arduino Digital Pins 9 PWM as output
  pinMode(10, OUTPUT); // Initialize Arduino Digital Pins 10 PWM as output
  pinMode(11, OUTPUT); // Initialize Arduino Digital Pins 11 PWM as output
  pinMode(6, OUTPUT); // Initialize Arduino Digital Pins 11 PWM as output
  pinMode(5, OUTPUT); // Initialize Arduino Digital Pins 11 PWM as output
  pinMode(3, OUTPUT); // Initialize Arduino Digital Pins 11 PWM as output

  // player inputs
  pinMode(player2InputPin,INPUT); // Initialize Arduino Digital Pins 2 as input for connecting Pushbutton
  pinMode(player12InputPin,INPUT); // Initialize Arduino Digital Pins 12 as input for connecting Pushbutton

  // player faults
  pinMode(player2FaultPin, OUTPUT);  // Initialize Arduino Digital Pins 4 as output
  pinMode(player12FaultPin, OUTPUT);  // Initialize Arduino Digital Pins 4 as output

  // get random eed (from analog noise) and determine starting direction {0, 1}
  randomSeed(analogRead(0));
  dir = random(2); // {0, 1}
  dir = (dir - 0.5) * 2; // {-1, 1}

  travelWait = (travelWaitMin + travelWaitMax) / 2;
  
  state = INTRO;
  returnFault = NONE;
  introMusic.Begin();
  digitalWrite(player2FaultPin, HIGH);
  digitalWrite(player12FaultPin, HIGH);
};


int Tennis::Update ()
{
  switch (state) {
    case INTRO:
      if (introMusic.Update()) {
        state = SERVE;
        digitalWrite(player2FaultPin, LOW);
        digitalWrite(player12FaultPin, LOW);
      }
      break;

    case SERVE:
        #if defined SERIAL_COMMENTARY
        Serial.println("Serving...");
        #endif

      // clear any previous fault
      faultLED.Hault();

      scoreDisplay.Hault();
      // faultMusic.Hault() unneded as that's what we watch for actual completed return val
      
      if (dir == -1) {
        button = player12InputPin;
      } else if (dir == 1) {
        button = player2InputPin;
      }
      
      travel.Begin(dir, travelWait, 0);
      state = TRAVEL;
      break;

    case TRAVEL:
      if (travel.Update()) {
        // travel is complete
        state = RETURN;
        returnButton.Begin(button, travelWait * hitTimeMult);

          #if defined SERIAL_COMMENTARY
          Serial.println("Travel complete");
          #endif
          
      } else {
        // travel is ongoing
        inputButtonState = digitalRead(button);
        if (inputButtonState == HIGH) {
          returnFault = EARLY;
          travel.Hault();
          state = SCORE;
            
            #if defined SERIAL_COMMENTARY
            Serial.println("Fault:early");
            #endif
        }
      }
      break;

    case RETURN:
        x = returnButton.Update();
        if (x == -1) {
          // no button push
          returnFault = LATE;
          state = SCORE;
          
            #if defined SERIAL_COMMENTARY
            Serial.println("Fault:late");
            #endif
            
        } else if (x == 1) {
          // button pushed on time
          dir = dir * -1; // reverse direction
          travelWait = returnButton.GetElapsedTime();
          travelWait = map(travelWait, 0, travelWaitMax * hitTimeMult, travelWaitMin, travelWaitMax);
          
            #if defined SERIAL_DEBUG
            Serial.println(travelWait);
            #endif
            
          state = SERVE; // serve back
            #if defined SERIAL_COMMENTARY
            Serial.println("Return serve");
            #endif
        };
      break;

    case SCORE:
        #if defined SERIAL_DEBUG
        Serial.println("Score, begin");
        #endif
        
      faultMusic.Begin();
      
      // assign point
      if (dir == -1) {
        player2score ++;
        faultPin = player12FaultPin;
        scoreDisplay.Begin(dir, player2score, scoreDisplayTime); // Direction, Number, OnTime
      } else if (dir == 1) {
        player12score ++;
        faultPin = player2FaultPin;
        scoreDisplay.Begin(dir, player12score, scoreDisplayTime); // Direction, Number, OnTime
      };

        #if defined SERIAL_COMMENTARY
        Serial.print("Score: ");
        Serial.print(player2score);
        Serial.print(" to ");
        Serial.println(player12score);
        #endif

      switch (returnFault) {
        case EARLY:
          // this will flash twice and an equal spaced pause in the middle
          faultLED.Begin(faultPin, 2, scoreDisplayTime / 3); 
          break;
        case LATE:
          faultLED.Begin(faultPin, 1, scoreDisplayTime);
          break;
      };
      
      returnFault = NONE;
      state = SCORE_UPDATE;

        #if defined SERIAL_DEBUG
        Serial.println("Score, end");
        #endif
        
      break;

    case SCORE_UPDATE:
      faultLED.Update();
      scoreDisplay.Update();
      if (faultMusic.Update()) {

          #if defined SERIAL_DEBUG
          Serial.println("Score_update, faultMusic over");
          #endif
          
        state = SERVE; // re-serve
        
        // but first check for winning score
        if (dir == -1) {
          if (player2score == travelPinsLen) {
            state = DONE;
          };
        } else {
          if (player12score == travelPinsLen) {
            state = DONE;
          };
        };
      };
        
      break;

    case DONE:
      
        #if defined SERIAL_COMMENTARY
        Serial.println("Done");
        #endif
        
      // clear any previous fault
      faultLED.Hault();
      // last param 0 means stay lit forever, so middle param doesn't mean anything
      faultLED.Begin(faultPin, 1, 0);
      scoreDisplay.Hault();

      winMusic.Begin();
      state = DONE_UPDATE;
      break;

    case DONE_UPDATE:
      winMusic.Update();
      break;
  }
};


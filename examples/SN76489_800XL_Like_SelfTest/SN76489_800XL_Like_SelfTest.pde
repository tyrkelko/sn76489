/***************************************************************************
***** SN76489 ATARI 800XL style self test                              *****
***** by Kobi Tyrkel                                                   *****
***** Demostrates how to play sound with the SN76489 library           *****
***** Created 16 July 2019                                             *****
***************************************************************************/
#include <SN76489.h>
#include "Pitches.h"

#define PIN_NotWE 2

// Define FREQUENCY according to the frequency in your hardware setup
#define FREQUENCY 4000000.0

// Either directly interface with SN76489 with 9 pins (8bit + NotWE) or use a 595 Shift Register with 4 pins (3 for 595 + NotWE)
// Comment / Uncomment the relevant setup below to choose your HW setup

/***************************************************************************
***** Directly interface SN76489 IC with the following PIN definitions *****
***** and by calling 8-bit constractor                                 *****
***** The SN76489 pinout considered for this library is as follows:    *****
*****                                                                  *****
*****                        ========                                  *****
*****        D2       --> [ 1]  ()  [16] <-- VCC                       *****
*****        D1       --> [ 2]      [15] <-- D3                        *****
*****        D0       --> [ 3]  7   [14] <-- CLOCK OSC                 *****
*****     READY       <-- [ 4]  6   [13] <-- D4                        *****
*****    NOT WE       --> [ 5]  4   [12] <-- D5                        *****
*****    NOT CE       --> [ 6]  8   [11] <-- D6                        *****
***** AUDIO OUT       <-- [ 7]  9   [10] <-- D7                        *****
*****       GND       --> [ 8]      [ 9] --- N.C.                      *****
*****                        ========                                  *****
***************************************************************************/
//#define PIN_D0 13
//#define PIN_D1 12
//#define PIN_D2 A5
//#define PIN_D3 A4
//#define PIN_D4 A3
//#define PIN_D5 A2
//#define PIN_D6 A1
//#define PIN_D7 A0
//SN76489 mySN76489 = SN76489(PIN_NotWE, PIN_D0, PIN_D1, PIN_D2, PIN_D3, PIN_D4, PIN_D5, PIN_D6, PIN_D7, FREQUENCY);


/***************************************************************************
***** Interface SN76489 IC with 595 Shift Register and PIN definitions *****
***** and by calling 3 PIN constractor                                 *****
***** 595 Shift Register pins connection with SN76489 is as follows:   *****
*****                                                                  *****
*****                        ========                                  *****
*****       D6 <-- Q1 <-- [ 1]  ()  [16] <-- VCC                       *****
*****       D5 <-- Q2 <-- [ 2]      [15] --> Q0     --> D7             *****
*****       D4 <-- Q3 <-- [ 3]  5   [14] <-- SER    <-- PIN_SER        *****
*****       D3 <-- Q4 <-- [ 4]  9   [13] <-- Not CE <-- GND            *****
*****       D2 <-- Q5 <-- [ 5]  5   [12] <-- CLOCK  <-- PIN_CLK        *****
*****       D1 <-- Q6 <-- [ 6]      [11] <-- LATCH  <-- PIN_LATCH      *****
*****       D0 <-- Q7 <-- [ 7]      [10] <-- Not MR <-- VCC            *****
*****             GND --> [ 8]      [ 9] --- Q7'    --- Not used       *****
*****                        ========                                  *****
***************************************************************************/
#define PIN_SER   7
#define PIN_LATCH 6
#define PIN_CLK   5

SN76489 mySN76489 = SN76489(PIN_NotWE, PIN_SER, PIN_LATCH, PIN_CLK, FREQUENCY);

/***************************************************************************
***** Melody and tempo data                                            *****
***************************************************************************/

uint16_t melody[] = {NOTE_G4, NOTE_F4, NOTE_AS4, NOTE_C5, NOTE_F5, NOTE_D5};
uint8_t tempo[] = {4, 4, 4, 8, 8, 4};

/***************************************************************************
***** Setup                                                            *****
***** Set 3 sound generators and noise to silence                      *****
***************************************************************************/
void setup() {
  mySN76489.setAttenuation(0, 0xF);
  mySN76489.setAttenuation(1, 0xF);
  mySN76489.setAttenuation(2, 0xF);
  mySN76489.setAttenuation(3, 0xF);
}

/***************************************************************************
***** Loop                                                             *****
***** Play melody on each of the 3 tone generators                     *****
***** and then play all noises on the noise generator                  *****
***************************************************************************/
void loop()
{
  static uint8_t toneGenerator = 0;
  static uint8_t noteIndex = 0;
  for (uint8_t toneGenerator = 0; toneGenerator < 3; toneGenerator++) {
    mySN76489.setAttenuation(toneGenerator, 0x0);
    for (uint8_t noteIndex = 0; noteIndex < sizeof(melody) / sizeof(uint16_t); noteIndex++) {
      mySN76489.setFrequency(toneGenerator, melody[noteIndex]);
      delay(2000 / tempo[noteIndex]);
    }
    mySN76489.setAttenuation(toneGenerator, 0xF);
    delay(2000);
  }  
  mySN76489.setAttenuation(3, 0x0);
  for (uint8_t fbIndex = 0; fbIndex < 2; fbIndex++) {
    for (uint8_t nfIndex = 0; nfIndex < 4; nfIndex++) {
      mySN76489.setNoise(fbIndex, nfIndex);
      delay(500);
    }
  }
  mySN76489.setAttenuation(3, 0xF);
  delay(2000);
}


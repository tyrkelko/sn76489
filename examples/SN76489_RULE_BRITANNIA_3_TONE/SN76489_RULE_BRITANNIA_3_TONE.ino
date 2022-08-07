/***************************************************************************
***** SN76489 ATARI 800XL style self test                              *****
***** by Kobi Tyrkel                                                   *****
***** Demostrates how to play sound with the SN76489 library           *****
***** Created 16 July 2019                                             *****
***************************************************************************/
#include <SN76489.h>
#include "Pitches.h"

#define SILENCE   0
#define TEMPO 4000        // millis per 4/4

#define TEMPO_LED_PIN 13  // toggle beat led every 1/4

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
//#define PIN_D0 A7
//#define PIN_D1 A6
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
#define PIN_LATCH 5
#define PIN_CLK   6

SN76489 mySN76489 = SN76489(PIN_NotWE, PIN_SER, PIN_LATCH, PIN_CLK, FREQUENCY);

/***************************************************************************
***** Melody and tempo data                                            *****
***** RULE BRITANNIA 3 TONE MUSIC                                      *****
***** If you're my age, you might know it as the Blue Max game theme   *****
***************************************************************************/

const uint16_t singer1[] PROGMEM = 
    // singer #1

    {
  
      //// 1
      
      SILENCE, 2,
      SILENCE, 4,
      SILENCE, 8,
      NOTE_D4, 8,
    
      //// 2
      
      NOTE_G4, 4,
      NOTE_G4, 4,
      NOTE_G4, 16,
      NOTE_A4, 16,
      NOTE_B4, 16,
      NOTE_C5, 16,
      NOTE_D5, 8,
      NOTE_G4, 8,
    
      //// 3
    
      NOTE_A4, 4,
      NOTE_D4, 8,
      NOTE_B4, 16,
      NOTE_C5, 16,
      NOTE_B4, 4,
      SILENCE, 8,
      NOTE_D4, 8,
    
      //// 4
    
      NOTE_G4, 16,
      NOTE_A4, 16,
      NOTE_G4, 16,
      NOTE_A4, 16,
      NOTE_B4, 16,
      NOTE_C5, 16,
      NOTE_B4, 16,
      NOTE_C5, 16,
      NOTE_D5, 8,
      NOTE_A4, 8,
      NOTE_G4, 8,
      NOTE_A4, 8,
    
      //// 5
      
      NOTE_G4, 8,
      NOTE_A4, 16,
      NOTE_B4, 16,
      NOTE_A4, 8,
      NOTE_G4, 8,
      NOTE_FS4, 4,
      SILENCE, 8,
      NOTE_D4, 8,
    
      //// 6
    
      NOTE_FS4, 8,
      NOTE_D4, 8,
      NOTE_A4, 8,
      NOTE_FS4, 8,
      NOTE_D5, 8,
      NOTE_CS5, 16,
      NOTE_B4, 16,
      NOTE_A4, 8,
      NOTE_G4, 8,
    
      //// 7
    
      NOTE_FS4, 4,
      NOTE_E4, 8,
      SILENCE, 16,
      NOTE_D4, 16,
      NOTE_C3, 4,
      SILENCE, 4,
    
      //// 8
    
      NOTE_G4, 4,
      NOTE_G4, 8,
      SILENCE, 16,
      NOTE_D4, 16,
      NOTE_E4, 8,
      NOTE_C3, 8,
      SILENCE, 8,
      NOTE_G4, 8,
    
      //// 9
    
      NOTE_C5, 8,
      NOTE_B4, 8,
      NOTE_A4, 8,
      NOTE_G4, 8,
      NOTE_FS4, 4,
      SILENCE, 8,
      NOTE_A4, 8,
    
      //// 10
    
      NOTE_D5, 4,
      NOTE_C5, 4,
      NOTE_B4, 16,
      NOTE_G4, 16,
      NOTE_C5, 16,
      NOTE_A4, 16,
      NOTE_D5, 8,
      NOTE_C5, 8,
    
      //// 11
    
      NOTE_B4, 4,
      NOTE_A4, 4,
      NOTE_G4, 4,
      SILENCE, 4,
    
      //// 12
    
      NOTE_B4, 4,
      SILENCE, 8,
      NOTE_B4, 8,
      NOTE_C5, 8,
      NOTE_C5, 8,
      SILENCE, 8,
      NOTE_B4, 8,
    
      //// 13
    
      NOTE_C5, 8,
      SILENCE, 16,
      NOTE_B4, 16,
      NOTE_A4, 8,
      NOTE_G4, 8,
      NOTE_FS4, 2,
    
      //// 14
    
      NOTE_D5, 4,
      NOTE_C5, 4,
      NOTE_B4, 16,
      NOTE_G4, 16,
      NOTE_C5, 16,
      NOTE_A4, 16,
      NOTE_D5, 8,
      NOTE_C5, 8,
    
      //// 15
    
      NOTE_B4, 4,
      NOTE_A4, 4,
      NOTE_C3, 8,
      NOTE_G4, 3,

      //// 16

      SILENCE, 1
    };

    // singer #2
    
const uint16_t singer2[] PROGMEM = 
    {

      //// 1
    
      SILENCE, 1,
    
      //// 2
      
      NOTE_G3, 4,
      NOTE_B3, 4,
      NOTE_E3, 4,
      NOTE_B2, 4,
    
      //// 3
    
      NOTE_C3, 4,
      NOTE_D3, 4,
      NOTE_G2, 4,
      SILENCE, 4,
    
      //// 4
    
      SILENCE, 8,
      NOTE_D3, 8,
      NOTE_G3, 16,
      NOTE_A3, 16,
      NOTE_G3, 16,
      NOTE_A3, 16,
      NOTE_B3, 8,
      NOTE_FS3,8,
      NOTE_G3, 8,
      NOTE_FS3,8,
    
      //// 5
    
      NOTE_E3, 4,
      NOTE_A2, 4,
      NOTE_D3, 4,
      SILENCE, 4,
    
      //// 6
    
      SILENCE, 8,
      NOTE_D3, 8,
      NOTE_FS3,8,
      NOTE_CS3,8,
      NOTE_B2, 4,
      NOTE_FS2,8,
      NOTE_G2, 8,
    
      //// 7
    
      NOTE_A2, 4,
      NOTE_A2, 4,
      NOTE_D3, 4,
      SILENCE, 4,
    
      //// 8
    
      NOTE_B2, 4,
      NOTE_G2, 4,
      NOTE_C3, 8,
      NOTE_E3, 8,
      SILENCE, 8,
      NOTE_B2, 8,
    
      //// 9
    
      NOTE_A2, 8,
      NOTE_B2, 8,
      NOTE_C3, 8,
      NOTE_CS3,8,
      NOTE_D3, 8,
      NOTE_E3, 8,
      NOTE_D3, 8,
      NOTE_C3, 8,
    
      //// 10
    
      NOTE_B2, 4,
      NOTE_A2, 8,
      NOTE_A3, 8,
      NOTE_G3, 8,
      NOTE_A3, 8,
      NOTE_B3, 8,
      NOTE_C3, 8,
    
      //// 11
    
      NOTE_D3, 4,
      NOTE_D3, 4,
      NOTE_G3, 4,
      SILENCE, 4,
    
      //// 12
    
      NOTE_G3, 4,
      SILENCE, 8,
      NOTE_F3, 8,
      NOTE_E3, 8,
      NOTE_C4, 8,
      SILENCE, 8,
      NOTE_E3, 8,
    
      //// 13
    
      NOTE_A2, 8,
      SILENCE, 16,
      NOTE_B2, 16,
      NOTE_C3, 8,
      NOTE_CS3,8,
      NOTE_D3, 4,
      NOTE_C3, 4,
    
      //// 14
    
      NOTE_B2, 8,
      NOTE_B3, 8,
      NOTE_A3, 8,
      NOTE_A2, 8,
      NOTE_G2, 8,
      NOTE_A2, 8,
      NOTE_B2, 8,
      NOTE_C2, 8,
    
      //// 15
    
      NOTE_D3, 4,
      NOTE_D2, 4,
      NOTE_FS2,3,
      SILENCE, 8,

      //// 16

      SILENCE, 1
    };


    // singer #3
    
const uint16_t singer3[] PROGMEM = 
    {

      //// 1
    
      SILENCE, 1,
    
      //// 2
      
      NOTE_B3, 4,
      NOTE_G3, 8,
      NOTE_FS3,8,
      NOTE_B3, 4,
      NOTE_G3, 4,
    
      //// 3
    
      NOTE_G3, 4,
      NOTE_FS3,4,
      NOTE_G3, 4,
      SILENCE, 4,
    
      //// 4
    
      SILENCE, 2,
      SILENCE, 8,
      NOTE_D4, 4,
      NOTE_D4, 8,
    
      //// 5
    
      NOTE_D4, 4,
      NOTE_CS4,4,
      NOTE_D4, 4,
      SILENCE, 8,
      NOTE_D4, 8,
    
      //// 6
    
      SILENCE, 4,
      NOTE_D4, 4,
      NOTE_FS4,4,
      NOTE_D4, 8,
      NOTE_B3, 8,
      
      //// 7
    
      NOTE_D4, 4,
      NOTE_G3, 4,
      NOTE_FS3,4,
      SILENCE, 4,
    
      //// 8
    
      NOTE_G3, 4,
      NOTE_G3, 4,
      NOTE_G3, 8,
      SILENCE, 4,
      SILENCE, 8,
    
      //// 9
    
      NOTE_E4, 4,
      NOTE_E4, 4,
      NOTE_D4, 4,
      SILENCE, 4,
      
      //// 10
    
      NOTE_G3, 4,
      NOTE_D4, 4,
      NOTE_D4, 8,
      NOTE_FS4,8,
      NOTE_G4, 8,
      NOTE_E4, 8,
    
      //// 11
    
      NOTE_G4, 4,
      NOTE_FS4,4,
      NOTE_D4, 4,
      SILENCE, 4,
    
      //// 12
    
      NOTE_D4, 4,
      SILENCE, 8,
      NOTE_D4, 8,
      NOTE_C4, 8,
      NOTE_E3, 8,
      SILENCE, 8,
      NOTE_E4, 8,
    
      //// 13
    
      NOTE_E4, 4,
      NOTE_E4, 4,
      NOTE_D4, 2,
    
      //// 14
    
      NOTE_D4, 4,
      NOTE_D4, 4,
      NOTE_D4, 16,
      SILENCE, 16,
      NOTE_FS4,16,
      SILENCE, 16,
      NOTE_D4, 8,
      NOTE_E4, 8,
    
      //// 15
    
      NOTE_B4, 4,
      NOTE_FS4,4,
      NOTE_B3, 3,
      SILENCE, 8,

      //// 16

      SILENCE, 1
    };

// array of pointers to singers array
uint16_t *singer[] = {
  singer1, 
  singer2,
  singer3
  };

// array of singers size
uint8_t singer_size[] = {
  sizeof(singer1)/sizeof(singer1[0]), 
  sizeof(singer2)/sizeof(singer2[0]),
  sizeof(singer3)/sizeof(singer3[0])
  };

// get a value from singer array
uint16_t getSingerValue(uint8_t toneGenerator, uint8_t singer_index) {
  return pgm_read_word_near ((singer[toneGenerator] + singer_index));
}

// return the singer size
uint8_t getSingerSize(uint8_t toneGenerator) {
  return singer_size[toneGenerator];
}

/***************************************************************************
***** Setup                                                            *****
***** Set 3 sound generators and noise to silence                      *****
***************************************************************************/
void setup() {
  Serial.begin(115200);
  Serial.println("starting...");
  // set beat led pin
  pinMode(TEMPO_LED_PIN, OUTPUT);
  // set silence
  mySN76489.setAttenuation(0, 0xF);
  mySN76489.setAttenuation(1, 0xF);
  mySN76489.setAttenuation(2, 0xF);
  mySN76489.setAttenuation(3, 0xF);
  Serial.println("started!");
}

/***************************************************************************
***** Loop                                                             *****
***** Play melody on each of the 3 tone generators                     *****
***************************************************************************/
void loop()
{
  uint32_t ms = millis();                                       // keep track of time
  static uint32_t singer_wait_till[] = {0, 0, 0};               // keep singers next update time
  static uint32_t beat_wait_till = 0;                           // keep next tempo led update
  static boolean beat = true;                                   // tempo led status
  static uint8_t singer_index[] = {0, 0, 0};                    // keep singers indexes
  static uint16_t singer_tone[] = {SILENCE, SILENCE, SILENCE};  // keep singers current tone
  static uint16_t singer_tempo[] = {0, 0, 0};                   // keep singers current tempo
  uint8_t toneGenerators = sizeof(singer) / sizeof(singer[0]);  // number of singers to loop on
  boolean resetSingers = false;                                 // end of (any) singer flag

  if (beat_wait_till <= ms) {
    digitalWrite(TEMPO_LED_PIN, (beat ? HIGH : LOW));
    beat_wait_till = ms + TEMPO / 8; 
    beat = !beat;
  }

  // loop for each singer
  for (uint8_t toneGenerator = 0; toneGenerator < toneGenerators; toneGenerator++) {
    if (singer_wait_till[toneGenerator] <= ms) {                // get new tone and tempo on time sync
      singer_tone[toneGenerator] = getSingerValue(toneGenerator, singer_index[toneGenerator]);
      singer_tempo[toneGenerator] = getSingerValue(toneGenerator, singer_index[toneGenerator] + 1);
      singer_index[toneGenerator]+=2;                           // update singer index
      if (singer_index[toneGenerator] >= getSingerSize(toneGenerator)) {
        resetSingers = true;                                    // set reset flag if singer reached end of data
      }
      if (singer_tone[toneGenerator] == SILENCE) {              // handle silence note
        mySN76489.setAttenuation(toneGenerator, 0xF);
      } else {                                                  // handle note
        mySN76489.setAttenuation(toneGenerator, 0x0);
        mySN76489.setFrequency(toneGenerator, singer_tone[toneGenerator]);        
      }
      
      singer_wait_till[toneGenerator] = ms + TEMPO / singer_tempo[toneGenerator]; // set next singer update
    }
  }
  
  if (resetSingers) {                                           // reset singers per reset flag
    for (uint8_t toneGenerator = 0; toneGenerator < toneGenerators; toneGenerator++) {
      singer_wait_till[toneGenerator] = 0;
      singer_index[toneGenerator] = 0;
      singer_tone[toneGenerator] = 0;
      singer_tempo[toneGenerator] = 0;
      beat_wait_till = 0;
    }
  } 
}

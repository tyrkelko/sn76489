/*
  SN76489.cpp - SN76489 library for interfacing SN76489 Sound Generator Chip directly or using 595 shift register - implementation
  Version 0.1, July 2019
  Copyright (c) 2019 Kobi Tyrkel.  All right reserved.
*/

// include this library's description file
#include "SN76489.h"

// include description files for other libraries used (if any)

// Constructor /////////////////////////////////////////////////////////////////
// Function that handles the creation and setup of instances
// For SN76489 pinout mapping refer to readme.txt file in this library

// Constructor for SN76489 with 8 data pins, Ready and !RW
SN76489::SN76489(uint8_t PIN_NotWE,uint8_t PIN_D0,uint8_t PIN_D1,uint8_t PIN_D2,uint8_t PIN_D3,uint8_t PIN_D4,uint8_t PIN_D5,uint8_t PIN_D6,uint8_t PIN_D7,float N,uint8_t PIN_Ready)
{
  // initialize this instance's variables
  _PIN_NotWE = PIN_NotWE;
  _PIN_D0    = PIN_D0;
  _PIN_D1    = PIN_D1;
  _PIN_D2    = PIN_D2;
  _PIN_D3    = PIN_D3;
  _PIN_D4    = PIN_D4;
  _PIN_D5    = PIN_D5;
  _PIN_D6    = PIN_D6;
  _PIN_D7    = PIN_D7;
  _N         = N;

  // do whatever is required to initialize the library

  // Set R/W pin mode
  pinMode(_PIN_NotWE, OUTPUT);
  digitalWrite(_PIN_NotWE, HIGH);

  // initialize instance's _PIN_Ready variables
  _PIN_Ready = PIN_Ready;


  // initialize instance's _PIN_Ready variables
  // Currently not used
  // TODO: Implement utilizing the Ready PIN and avoid possible timing issues
  if (_PIN_Ready != 255) pinMode(_PIN_Ready, INPUT);

  // Set up the Data I/O pins
  pinMode(_PIN_D0, OUTPUT);
  pinMode(_PIN_D1, OUTPUT);
  pinMode(_PIN_D2, OUTPUT);
  pinMode(_PIN_D3, OUTPUT);
  pinMode(_PIN_D4, OUTPUT);
  pinMode(_PIN_D5, OUTPUT);
  pinMode(_PIN_D6, OUTPUT);
  pinMode(_PIN_D7, OUTPUT);
}

// Constructor for SN76489 with 8 data pins and !RW
SN76489::SN76489(uint8_t PIN_NotWE,uint8_t PIN_D0,uint8_t PIN_D1,uint8_t PIN_D2,uint8_t PIN_D3,uint8_t PIN_D4,uint8_t PIN_D5,uint8_t PIN_D6,uint8_t PIN_D7,float N) : SN76489(PIN_NotWE,PIN_D0,PIN_D1,PIN_D2,PIN_D3,PIN_D4,PIN_D5,PIN_D6,PIN_D7,N,255) {}

// Constructor for 595 Shift Register driving SN76489 with SER, LATCH, Clock and !RW
SN76489::SN76489(uint8_t PIN_NotWE,uint8_t PIN_SER,uint8_t PIN_LATCH,uint8_t PIN_CLK,float N, uint8_t PIN_Ready) 
{
  // initialize this instance's variables
  _PIN_NotWE = PIN_NotWE;
  _PIN_D0    = PIN_SER;
  _PIN_D1    = PIN_LATCH;
  _PIN_D2    = PIN_CLK;
  _PIN_D3    = 255;
  _N         = N;

  // do whatever is required to initialize the library

  // Set R/W pin mode
  pinMode(_PIN_NotWE, OUTPUT);
  digitalWrite(_PIN_NotWE, HIGH);

  // initialize instance's _PIN_Ready variables
  // Currently not used
  // TODO: Implement utilizing the Ready PIN and avoid possible timing issues
  _PIN_Ready = PIN_Ready;

  // Set Ready pin mode
  if (_PIN_Ready != 255) pinMode(_PIN_Ready, INPUT);

  // Set up the Data I/O pins
  pinMode(_PIN_D0, OUTPUT);
  pinMode(_PIN_D1, OUTPUT);
  pinMode(_PIN_D2, OUTPUT);
}


// Constructor for 595 Shift Register driving SN76489 with SER, LATCH, Clock and !RW
SN76489::SN76489(uint8_t PIN_NotWE,uint8_t PIN_SER,uint8_t PIN_LATCH,uint8_t PIN_CLK,float N) : SN76489(PIN_NotWE,PIN_SER,PIN_LATCH,PIN_CLK,N,999) {}



// Public Methods //////////////////////////////////////////////////////////////
// Functions available in Wiring sketches, this library, and other libraries

// The frequency can be calculated by the following: ////////////////////////////
//
// f = N / 32n
// where N = ref clock in Hz
// n = 10 bit binary number
//
// 1	R2	R1	R0	F9	F8	F7	F6	Update frequency (double byte transfer)
// 0	x	F5	F4	F3	F2	F1	F0

void SN76489::setFrequency(uint8_t toneGenerator, uint16_t freq) {
  byte n0;
  byte n1 = 0;

  uint32_t n = _N / (32.0 * freq);

  n0 = 128 + controlRegister(toneGenerator, true) 
  + 8 * ((n & 0b0000000000001000) ? 1 : 0)
  + 4 * ((n & 0b0000000000000100) ? 1 : 0)
  + 2 * ((n & 0b0000000000000010) ? 1 : 0)
  + 1 * ((n & 0b0000000000000001) ? 1 : 0);

  n1 = 32 * ((n & 0b0000001000000000) ? 1 : 0)
  + 16 * ((n & 0b0000000100000000) ? 1 : 0)
  + 8 * ((n & 0b0000000010000000) ? 1 : 0)
  + 4 * ((n & 0b0000000001000000) ? 1 : 0)
  + 2 * ((n & 0b0000000000100000) ? 1 : 0)
  + 1 * ((n & 0b0000000000010000) ? 1 : 0);
    
  SendByteToSoundChip(n0);
  SendByteToSoundChip(n1);
}

// The output of the frequency flip-flop feeds into a four stage attenuator.
// ATTENUATION CONTROL BIT POSITION
//
// A3...0	Attenuation weight / dB
// 0001		2
// 0010		4
// 0100		8
// 1000		16
// 1111		Off
// The formats required to transfer data are shown below.
// _7	_6	_5	_4	_3	_2	_1	_0	<- Conventional data bus bits (D7=MSB on Left, D0=LSB on Right)
// 1	R2	R1	R0	A3	A2	A1	A0	Update attenuator (single byte transfer)
void SN76489::setAttenuation(uint8_t toneGenerator, uint8_t attn) {
  SendByteToSoundChip(128 + controlRegister(toneGenerator, false) + min(attn, 15));
}

// The Noise Generator consists of a noise source and an attenuator.
// The noise source is a shift register with an exclusive OR feedback network.
// The feedback network has provisions to protect the shift register from being locked in the zero state.
// The formats required to transfer data are shown below.
// _7	_6	_5	_4	_3	_2	_1	_0	<- Conventional data bus bits (D7=MSB on Left, D0=LSB on Right)
// 1	R2	R1	R0	x	FB	NF1	NF0     Update noise source (single byte transfer)
void SN76489::setNoise(uint8_t feedbackControl, uint8_t frequencyControl) {
  SendByteToSoundChip(128 + controlRegister(3, false) + (feedbackControl==0 ? 0:4) + min(frequencyControl, 3));
}

// Private Methods /////////////////////////////////////////////////////////////
// Functions only available to other functions in this library

byte SN76489::controlRegister(uint8_t toneGenerator, boolean freq) {
  return 32 * toneGenerator + (freq ? 0 : 16);
}

// Split the byte to send onto individual I/O pins of the IC 8 bit data bus either directly or using the shift register
void SN76489::SendByteToSoundChip(byte b)
{
  if (_PIN_D3 != 255) {  
    digitalWrite(_PIN_D7, (b&1)?HIGH:LOW);
    digitalWrite(_PIN_D6, (b&2)?HIGH:LOW);
    digitalWrite(_PIN_D5, (b&4)?HIGH:LOW);
    digitalWrite(_PIN_D4, (b&8)?HIGH:LOW);
    digitalWrite(_PIN_D3, (b&16)?HIGH:LOW);
    digitalWrite(_PIN_D2, (b&32)?HIGH:LOW);
    digitalWrite(_PIN_D1, (b&64)?HIGH:LOW);
    digitalWrite(_PIN_D0, (b&128)?HIGH:LOW);
  } else {
    digitalWrite(_PIN_D1, LOW);  // prepare shift register for data
    shiftOut(_PIN_D0, _PIN_D2, MSBFIRST, b); // send data
    digitalWrite(_PIN_D1, HIGH); // update display
  }


  // Pulse write enable low for one millisecond as the R/W on SN76489 is inverted
  // then return it high for normal read operation.
  digitalWrite(_PIN_NotWE, LOW);
  delay(1);
  digitalWrite(_PIN_NotWE, HIGH);
}

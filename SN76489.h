/*
  SN76489.h - SN76489 library for interfacing SN76489 Sound Generator Chip directly or using 595 shift register - description
  Version 0.1, July 2019
  Copyright (c) 2019 Kobi Tyrkel.  All right reserved.
*/

#ifndef SN76489_h
#define SN76489_h

#include <stdlib.h>
#if ARDUINO >= 100
  #include <Arduino.h>
#else
  #include <wiring.h>
#endif

// library interface description
class SN76489
{
  // user-accessible "public" interface
  public:
    SN76489(uint8_t,uint8_t,uint8_t,uint8_t,uint8_t,uint8_t,uint8_t,uint8_t,uint8_t,float,uint8_t);
    SN76489(uint8_t,uint8_t,uint8_t,uint8_t,uint8_t,uint8_t,uint8_t,uint8_t,uint8_t,float);
    SN76489(uint8_t,uint8_t,uint8_t,uint8_t,float,uint8_t);
    SN76489(uint8_t,uint8_t,uint8_t,uint8_t,float);
    void setFrequency(uint8_t, uint16_t);
    void setAttenuation(uint8_t, uint8_t);
    void setNoise(uint8_t, uint8_t);

  // library-accessible "private" interface
  private:
    byte controlRegister(uint8_t, boolean);
    void SendByteToSoundChip(byte);
    uint8_t _PIN_NotWE;
    uint8_t _PIN_Ready;
    uint8_t _PIN_D0;
    uint8_t _PIN_D1;
    uint8_t _PIN_D2;
    uint8_t _PIN_D3;
    uint8_t _PIN_D4;
    uint8_t _PIN_D5;
    uint8_t _PIN_D6;
    uint8_t _PIN_D7;
    float _N;
};

#endif

